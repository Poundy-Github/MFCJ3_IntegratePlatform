/*===============================================================================*/
/*                                                                               */
/*                               BOOT Layers                                     */
/*                                                                               */
/* ----------------------------------------------------------------------------- */
/*                                                                               */
/*                               PROG layer                                      */
/*                                                                               */
/*===============================================================================*/
/*%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%                                        */
/*%%   _____________________________   %%  \file PROG_Cbk.c                      */
/*%%  |                             |  %%  \brief PROG layer source plugin file  */
/*%%  |   &&&&&   &&&&&             |  %%  Module version: 2.47.0 BL3 */
/*%%  |   &       &    &            |  %%                                        */
/*%%  |   &&&&    &&&&&             |  %%                                        */
/*%%  |   &       &    &            |  %%                                        */
/*%%  |   &&&&&   &&&&&             |  %%                                        */
/*%%  |_____________________________|  %%                                        */
/*%%                                   %%                                        */
/*%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%                                        */
/*===============================================================================*/
/* Copyright 2015 by Elektrobit Automotive GmbH                                  */
/* All rights exclusively reserved for Elektrobit Automotive GmbH,               */
/* unless expressly agreed to otherwise.                                         */
/*===============================================================================*/

/*=============================== FILE INCLUSION ================================*/
/*                                                                               */
#include "EB_Prj.h"
#include "PROG_Priv.h"
#include "board.h"
#include "TSMem.h"
#include "md5.h"
#include "verify.h"
#include "log.h"

#define PROG_SIG  0x5AA5A55AU
#define PROG_SIG_CLEAR 0x0U

#define PROG_FLASH_STATUS_OFFSET 0U
#define PROG_FLASH_STATUS_SIZE   32U
#define PROG_FINGER_PRINT_OFFSET 0x100U
#define PROG_FINGER_PRINT_SIZE   9U
#define PROG_FINGER_PRINT_NUM    10U

#define PROG_ENTRY_OFFSET        0x2000U

#define PROG_SIGNATURE_AREA_SIZE        32U
#define PROG_SIGNATURE_LENGTH           16U
#define PROG_MAC_KEY_LENGTH             16U
#define PROG_HASH_LENGTH                16U
#define PROG_HASH_CALC_SIZE             64U

#define PROG_BOOT_SIGNATURE_CHECK_COUNT      0x03U

#define PROG_COHERENCY_READY                 0x00U
#define PROG_COHERENCY_READ_SIGNATURE        0x01U
#define PROG_COHERENCY_HASH_START            0x02U
#define PROG_COHERENCY_HASH_UPDATE           0x03U
#define PROG_COHERENCY_HASH_FINISH           0x04U
#define PROG_COHERENCY_VERIFY                0x05U
#define PROG_COHERENCY_WRITE_FLASH_STATUS    0x06U
#define PROG_COHERENCY_CHECK_FLASH_STATUS    0x07U
#define PROG_COHERENCY_EXCHANGE              0x08U
#define PROG_COHERENCY_SUCCESS               0x09U
#define PROG_COHERENCY_FAILURE               0x0AU

typedef struct
{
    u32  ulStatus;
    u32  ulDummy;
    u32  ulStartAddress;
    u32  ulSize;
    u8   ubSignature[PROG_SIGNATURE_LENGTH];
}tSignatureInfo;

NCS_PRI_VAR u8 m_ubWriteFingerprintStatus = PROG_E_NOT_OK;
NCS_PRI_VAR u8 m_aubFingerPrint[PROG_FINGER_PRINT_NUM][PROG_FINGER_PRINT_SIZE];
NCS_PRI_VAR tSignatureInfo m_stSignatureInfo;
NCS_PRI_VAR u8 m_ubCoherencyStatus;
NCS_PRI_VAR u8 m_ubSegmentId;
NCS_PRI_VAR u8 m_aubHash[PROG_HASH_LENGTH];
NCS_PRI_VAR mbedtls_md5_context m_Md5Ctx;

#define PROG_REPROG_FLAG_START_SEC_VAR_NO_INIT_8
#include <MemMap.h>
NCS_PRI_VAR volatile u32 m_ulProgSig;
#define PROG_REPROG_FLAG_STOP_SEC_VAR_NO_INIT_8
#include <MemMap.h>

NCS_PRI_VAR volatile u32 m_ulBluSig;

tContextRestore stBLUContextRestore =
{
    1,
    {
        {
            0x31,
            0x01,
            0xFF,
            0x01,
        },
        0x4
    }
};

tUdsStatus PROG_ReadFingerprint(u16 *puwLen, u8 *aubUdsData);
tProgStatus PROG_CheckFlashStatus(u8 ubLogicalSegmentId);
static tProgStatus PROG_EraseFlashStatus(u8 ubLogicalSegmentId);
static tProgStatus PROG_WriteFlashStatus(u8 ubLogicalSegmentId);
static tProgStatus PROG_BackupFingerprint(u8 ubLogicalSegmentId);
static tProgStatus PROG_SaveFingerprint(u8 ubLogicalSegmentId);
static tProgStatus PROG_CheckBootSignature(u8 ubLogicalSegmentId);
static tProgStatus PROG_CheckFlashDriverSignature(u8 ubLogicalSegmentId);

/*=============================== IMPLEMENTATION ================================*/
/*                                                                               */


/** \brief API that check if a programming request has been received by the application
 **
 ** Callback is called: at Bootloader startup to know if a programming request has
 **                     been received in Application
 **
 ** Callback shall implement: get information from application if a programming
 **                          request has been received (e.g: read a flag from
 **                          noinit RAM shared between Bootloader and
 **                           Application)
 **
 ** \return Result of check
 ** \retval PROG_BOOT_REPROG Reprogramming request has been received
 ** \retval PROG_BOOT_NO_REPROG No reprogramming request received
 **/
u8 PROG_CheckProgRequest(void)
{
    u8 ubRetVal = PROG_BOOT_NOREPROG;

    LOG(LOG_LEVEL_INFO, "ProgSig 0x%08X", m_ulProgSig);

    /* Check if the signature is set */
    if (m_ulProgSig == PROG_SIG)
    {
        /* comming from application must stay in boot */
        ubRetVal = PROG_BOOT_REPROG;
    }
    else
    {
        /* Prog signature is clear must jump in application after tested it */
    }

    /* Clear the prog signature*/
    m_ulProgSig = PROG_SIG_CLEAR;

    return ubRetVal;
}

/** \brief Callback performing jump to application software
 **
 ** Callback is called: at Bootloader startup if application is valid and shall
 **                    be executed
 **
 ** Callback shall implement: jump to application start address
 **
 **/
void PROG_JumpToApplication(void)
{
    u8 ubApplicationRunningArea;
    ptAPPL_START_ADDR pAPPL_START_ADDR;
 
    ubApplicationRunningArea = APP_GetApplicationRunningArea();
    pAPPL_START_ADDR = (ptAPPL_START_ADDR)(stConfigSegment[ubApplicationRunningArea].ulStartAddress + PROG_ENTRY_OFFSET);

    /* Jump to application */
    LOG(LOG_LEVEL_INFO, "jump to application %c start address 0x%X", 'A' + ubApplicationRunningArea, pAPPL_START_ADDR);
    pAPPL_START_ADDR();
    LOG(LOG_LEVEL_ERROR, "application start address error");
}

/** \brief API that returns information if a programming request has been received by the application
 **
 ** Callback is called: at reception of a request in BlPduR module to ignore the request if Rx simulation  
 **                           request is ongoing (programming request has been received by the application)
 **
 ** Callback shall implement: returns information from application if a programming
 **                          request has been received or not (e.g: from PROG_CheckProgRequest API)
 **
 ** \return Information checked in PROG_CheckProgRequest API
 ** \retval TRUE Reprogramming request has been received in Application
 ** \retval FALSE Reprogramming request has not been received in Application
 **/
tProgBoolean PROG_ReturnsIsReProgRequestFromAppli(void)
{
    return FALSE;
}

/** \brief Callback that shall disable ECC if needed
 ** Callback is called: When Bootloader perform read access on Flash that can be
 **                     unprogrammed and can cause ECC error
 **
 ** Callback shall implement: If needed, disabling of ECC check
 **                           Hardware specific)
 **/
void PROG_DisableECCCheck(void)
{
  BoardDisableECCCheck();
}

/** \brief Callback that shall enable ECC if needed
 ** Callback is called: After Bootloader has performed a read access on Flash
 **                    that can be unprogrammed and can cause ECC error
 **
 ** Callback shall implement: If needed, enabling of ECC check
 **                          (Hardware specific)
 **/
void PROG_EnableECCCheck(void)
{
  BoardEnableECCCheck();
}

/** \brief Callback checking if the application is valid or not
 **
 ** Callback is called: at startup and on some routine.
 **
 ** Callback shall implement: It shall verify that the application
 ** with all its dependencies are correctly flashed
 ** and return the result of the check
 **
 ** \return Result of check
 ** \retval TRUE Application is valid
 ** \retval FALSE Application is not valid or not present
 **/
tProgBoolean PROG_IsValidApplication(void)
{
    tProgBoolean eProgBoolean;
    tProgStatus eProgStatus;
    u8 ubLogicalSegmentId;

    eProgBoolean = PROG_TRUE;

    /* Get application running area */
    ubLogicalSegmentId = APP_GetApplicationRunningArea();

    LOG(LOG_LEVEL_INFO, "current application %c", 'A' + ubLogicalSegmentId);

    /* Check current application status */
    eProgStatus = PROG_CheckFlashStatus(ubLogicalSegmentId);

    if (PROG_E_OK == eProgStatus)
    {
        /* Application status is vaild, check boot signature */
        eProgStatus = PROG_CheckBootSignature(ubLogicalSegmentId);

        if (PROG_E_OK != eProgStatus)
        {
            /* Boot signature error, write secure boot error flag */
            LOG(LOG_LEVEL_ERROR, "application %c signature error", 'A' + ubLogicalSegmentId);
            APP_WriteSecureBootError(ubLogicalSegmentId);
        }
    }
    else
    {
        /* Application status is invaild */
        LOG(LOG_LEVEL_ERROR, "application %c status error", 'A' + ubLogicalSegmentId);
    }

    if (PROG_E_OK != eProgStatus)
    {
        /* Check another application status */
        ubLogicalSegmentId = (ubLogicalSegmentId + 1U) % 2U;
        eProgStatus = PROG_CheckFlashStatus(ubLogicalSegmentId);

        if (PROG_E_OK == eProgStatus)
        {
            /* Another application status is vaild, check boot signature */
            eProgStatus = PROG_CheckBootSignature(ubLogicalSegmentId);

            if (PROG_E_OK == eProgStatus)
            {
                /* Boot signature OK, change to another application */
                eProgBoolean = APP_ChangeToApplicationRunningArea(ubLogicalSegmentId);
                if (PROG_TRUE == eProgBoolean)
                {
                    LOG(LOG_LEVEL_INFO, "change to application %c success", 'A' + ubLogicalSegmentId);
                }
                else
                {
                    LOG(LOG_LEVEL_ERROR, "change to application %c failure", 'A' + ubLogicalSegmentId);
                }
            }
            else
            {
                /* Boot signature error, write secure boot error flag */
                LOG(LOG_LEVEL_ERROR, "application %c signature error", 'A' + ubLogicalSegmentId);
                APP_WriteSecureBootError(ubLogicalSegmentId);
            }
        }
        else
        {
            /* Another application status is invaild */
            LOG(LOG_LEVEL_ERROR, "application %c status error", 'A' + ubLogicalSegmentId);
        }
    }

    if (PROG_E_OK != eProgStatus)
    {
        eProgBoolean = PROG_FALSE;
    }

    return eProgBoolean;
}

/** \brief Callback invalidating the application markers
 **
 ** Callback is called: On Erase routine reception
 **
 ** Callback shall implement: 1- customer code that shall be executed before
 **                           performing an erasing
 **
 **                           2- It shall invalidate the application or the current erased section
 **                           to make sure no jump to the application will be done if an error occurred
 **                           and the application is not fully erased or reprogrammed
 **
 ** \param[in] ulStartAddress Erased Start address of the segment that will be erased
 ** \param[in] ulEraseLength requested erase length
 ** \param[out] ErrorCode UDS error code that shall be return in case of error during API treatment
 **
 ** \return Result application invalidation
 ** \retval PROG_E_OK Treatment finish successfully
 ** \retval PROG_E_NOT_OK Error happened during treatment (ErrorCode shall be filled in this case)
 **/
tProgStatus PROG_InvalidateSection(tProgAddressType ulStartAddress, u32 ulEraseLength, tUdsStatus * ErrorCode)
{
    tProgStatus eProgStatus;
    u8 ubLogicalSegmentId;

    eProgStatus = PROG_GetSegmentByAddress(ulStartAddress, ulEraseLength, PROG_MEM_OPERATION_TYPE_ERASE, &ubLogicalSegmentId);

    if (eProgStatus == PROG_E_OK)
    {
        LOG(LOG_LEVEL_INFO, "set segment %d invalidate", ubLogicalSegmentId);

        if (stConfigSegment[ubLogicalSegmentId].ePartitionType == PROG_APPLICATION_PARTITION)
        {
            ubLogicalSegmentId = ubLogicalSegmentId % 2U;
        }

        /* Check flash status erasing */
        eProgStatus = PROG_MemCheckPageErasing(
                m_astCfgMemory[stConfigSegment[ubLogicalSegmentId].ubMemoryIdx].eMemoryType,
                (u32) (stConfigSegment[ubLogicalSegmentId].ulEraseStartAddress + PROG_FLASH_STATUS_OFFSET));

        //Not erased status
        if (eProgStatus != PROG_E_OK)
        {
            /* Backup Finger Print */
            eProgStatus = PROG_BackupFingerprint(ubLogicalSegmentId);

            if (eProgStatus == PROG_E_OK)
            {
                /* Erase flash status */
                eProgStatus = PROG_EraseFlashStatus(ubLogicalSegmentId);
            }

            if (eProgStatus == PROG_E_OK)
            {
                /* Writer Finger Print */
                eProgStatus = PROG_SaveFingerprint(ubLogicalSegmentId);
            }

            if (eProgStatus == PROG_E_OK)
            {
                /* Erase secure boot error flag */
                APP_EraseSecureBootError();
            }
        }
    }

    if (eProgStatus != PROG_E_OK)
    {
        *ErrorCode = UDS_NRC_72;
    }

    return eProgStatus;
}

/** \brief Called before Bootloader perform a jump to application
 **
 ** Callback is called: Before jumping to Application
 **
 **  Callback shall implement: customer code that shall be executed before
 **  jumping to application
 **/
void PROG_SwitchApplicationModeInd(void)
{
    /* Before jumping to Application, disable interrupts */
    BoardDisableInterrupts();
}

/** \brief Get the status of the suppress positive response bit from the last reprogramming request in application
 **
 ** Callback is called: At startup when Bootloader shall send a response to a request that
 **                     has been received in application
 **
 ** Callback shall implement: get from application information if the
 **                          suppressPositiveResponse bit was set in the
 **                           received request (e.g: read a flag from noinit RAM
 **                           shared between Bootloader and  Application)
 **
 ** \return Suppression bit value
 ** \retval TRUE The suppress positive response bit was set (response will not be sent)
 ** \retval FALSE The suppress positive response bit was not set (response will be sent)
 **/
u8 PROG_GetSuppressBitFromAppli(void)
{
    return FALSE;
}

/** \brief Start the Fingerprint Writing
 **
 ** Callback is called: On reception of WriteDataByIdentifier service for Fingerprint
 **                     DID
 **
 ** Callback shall implement:
 **
 **                           1- Check the validity of FingerPrint data
 **
 **                           2- the writing in non-volatile memory of the
 **                            Fingerprint data (pubRamBuffer points on the
 **                            dataIdentifier field of the WriteDataByIdentifier
 **                            request)
 **                            Asynchronous management can be implemented, in this case
 **                            PROG_E_BUSY value is returned and further call to
 **                            PROG_CustomGetWriteFingerprintStatus will allow
 **                            Bootloader to get writing status
 **
 ** \param[in] pubRamBuffer pointer to a RAM buffer where the DID identifier and fingerprint data
 **                         are located
 **
 ** \return Result
 ** \retval PROG_E_OK Write Fingerprint ok
 ** \retval PROG_E_NOT_OK Write Fingerprint failed
 ** \retval PROG_E_BUSY Write Fingerprint in progress
 **/
tProgStatus PROG_CustomWriteFingerprint(u8 * pubRamBuffer)
{
    /* Check the validity of FingerPrint data */
    if ((pubRamBuffer[2] > 99U) || 
        (pubRamBuffer[3] == 0U) || 
        (pubRamBuffer[3] > 12U) || 
        (pubRamBuffer[4] == 0U) || 
        (pubRamBuffer[4] > 31U))
    {
        /* FingerPrint data is invalid */
        m_ubWriteFingerprintStatus = PROG_E_CHECK_FAILED;
    }
    else
    {
        /* FingerPrint data is valid */
        TS_MemCpy(&m_aubFingerPrint[0U][0U], &pubRamBuffer[2U], PROG_FINGER_PRINT_SIZE);
        m_ubWriteFingerprintStatus = PROG_E_OK;
    }

    return m_ubWriteFingerprintStatus;
}

/** \brief Get the status of the fingerprint writing
 **
 ** Callback is called: After PROG_CustomWriteFingerprint returns PROG_E_BUSY, this
 **                     callback is called periodically until getting a status
 **                     different from PROG_E_BUSY
 **
 ** Callback shall implement: provide status of the fingerprint writing
 **
 ** \return Result
 ** \retval PROG_E_OK Write Fingerprint ok
 ** \retval PROG_E_NOT_OK Write Fingerprint failed
 ** \retval PROG_E_BUSY Write Fingerprint in progress
 **/
tProgStatus PROG_CustomGetWriteFingerprintStatus(void)
{
    return m_ubWriteFingerprintStatus;
}

/** \brief Check if all the programming pre-conditions are met
 **
 ** Callback is called: On Programming precondition check
 **
 ** Callback shall implement: programming precondition check. Inform Bootloader
 **                           if the ECU is in a state where programming can be
 **                           performed. It shall check for the error condition Security access 
 **                           if locked and update error list (m_aubPreProgErrorList).
 **                           If condition are not correct programming will be rejected by Bootloader 
 **                           and negative response will be sent on the network.
 **
 ** \return state
 ** \retval PROG_E_OK All the programming pre-conditions are met
 ** \retval PROG_E_NOT_OK At least one programming pre-condition is NOT met
 **
 **/
tProgStatus PROG_CustCheckProgPrecond(tUdsStatus * ubDiagStatus)
{
    tProgStatus eProgStatus = PROG_E_OK;

    /* update attempt downloading counter */
    (void)APP_WriteSecureUpdatingLog(ATTEMPT_DOWNLOADING_COUNTER);

    OSC_PARAM_UNUSED(ubDiagStatus);

    return eProgStatus;
}

/** \brief Callback called after comparing the expected checksum or signature and the calculated one.
 **
 ** Callback is called: After a successful or unsuccessful download verification
 **
 ** Callback shall implement: update the external global variable m_aubBlockDownloadStatus for the logical block validity status
 **                           If Dual bank feature is used, this call back can be used to know that a complete, 
 **                           and successful application download happened and therefore allow bank swaps
 **
 ** \param[in] ubLogicalBlockId The id of the logical block for which the compare was done
 ** \param[in] ubLogicalSegmentId The id of the logical segment  for which the compare was done
 **            (ignore if the full logical block is verified)
 ** \param[in] ubCompareSuccess TRUE if the 2 elements of the comparison are identical
 **
 ** \return state
 ** \retval PROG_E_OK Treatment finish successfully
 ** \retval PROG_E_NOT_OK Error happened during treatment
 **/
tProgStatus PROG_CustomSetDownloadVerificationSuccess(u8 ubLogicalBlockId, u8 ubLogicalSegmentId, tProgBoolean ubCompareSuccess)
{
    tProgStatus eProgStatus;
    tAppBoolean eAppBoolean;

    eProgStatus = PROG_E_OK;

    if (stConfigSegment[ubLogicalSegmentId].ePartitionType == PROG_FLASH_ROUTINES_PARTITION)
    {
        if (PROG_TRUE == ubCompareSuccess)
        {
            /* Check flash driver signature */
            LOG(LOG_LEVEL_INFO, "check flash driver signature");
            eProgStatus = PROG_CheckFlashDriverSignature(ubLogicalSegmentId);
            if(PROG_E_OK == eProgStatus)
            {
                /* check flash driver coherency */
                LOG(LOG_LEVEL_INFO, "check flash driver coherency");
                eAppBoolean = APP_CheckFlashDriverCoherency();
                if (APP_TRUE == eAppBoolean)
                {
                    /* check flash driver success, update driver activated successfully counter */
                    (void)APP_WriteSecureUpdatingLog(FLASH_DRIVER_ACTIVATED_SUCCESSFULLY_COUNTER);
                    LOG(LOG_LEVEL_INFO, "check flash driver success");
                }
                else
                {
                    /* Flash driver coherency error */
                    LOG(LOG_LEVEL_ERROR, "flash driver coherency error");
                    eProgStatus = PROG_E_NOT_OK;
                }
            }
            else
            {
                /* Flash driver signature error */
                LOG(LOG_LEVEL_ERROR, "flash driver signature error");
            }
        }
    }

    m_ubCoherencyStatus = PROG_COHERENCY_READY;

    OSC_PARAM_UNUSED(ubLogicalBlockId);

    return eProgStatus;
}

/** \brief Callback for CRC storage
 **
 ** Callback is called: After CRC calculation
 **
 ** Callback shall implement: storage of the CRC value for further use
 **
 ** \param[in] ulCrcVal CRC value
 **
 **/
void PROG_CustomWriteCRC(u32 ulCrcVal)
{
    OSC_PARAM_UNUSED(ulCrcVal);
}

/** \brief This API is called  to do the coherency check treatment
 **
 ** Callback is called: on the coherency check request reception
 **
 ** Callback shall implement: the algorithm performing the coherency check of the previously programmed blocks (E.g.: checking of blocks versions compatibility).
 **
 ** \param[out] eCohChkResult The result of the coherency check.
 **             Can be: 0-correct, 1-incorrect, 2-incorrect error SW-HW, 3-incorrect error SW-SW, 4-incorrect other error
 **
 ** \return Coherency Check result
 ** \retval PROG_E_OK when the check has finished
 ** \retval PROG_E_BUSY if the check is on going
 **/
tProgStatus PROG_CustomCoherencyCheck(tProgCohChkResult* eCohChkResult)
{
    tProgStatus eProgStatus;
    tAppBoolean eAppBoolean;
    int ret;
    u32 ulCalcLength;
    u8 aubHashValue[PROG_HASH_CALC_SIZE];
    u8 ubApplicationRunningArea;

    eProgStatus = PROG_E_NOT_OK;

    switch (m_ubCoherencyStatus)
    {
        case PROG_COHERENCY_READY:
            if (stConfigSegment[m_stCurrentSegment.ubSegmentId].ePartitionType == PROG_APPLICATION_PARTITION)
            {
                /* Check application signature */
                m_ubSegmentId = m_stCurrentSegment.ubSegmentId % 2U;
                LOG(LOG_LEVEL_INFO, "check application %c coherency", 'A' + m_ubSegmentId);
                m_ubCoherencyStatus = PROG_COHERENCY_READ_SIGNATURE;
                eProgStatus = PROG_E_BUSY;
            }
            else if (stConfigSegment[m_stCurrentSegment.ubSegmentId].ePartitionType == PROG_BLU_PARTITION)
            {
                /* Check new bootloader signature */
                m_ubSegmentId = PROG_SEG_BOOTLOADERBACKUP;
                LOG(LOG_LEVEL_INFO, "check bootloader updater coherency");
                m_ubCoherencyStatus = PROG_COHERENCY_READ_SIGNATURE;
                eProgStatus = PROG_E_BUSY;
            }
            else
            {
                /* Invalid case */
                LOG(LOG_LEVEL_ERROR, "check coherency segment %d failure", m_stCurrentSegment.ubSegmentId);
                m_ubCoherencyStatus = PROG_COHERENCY_FAILURE;
                eProgStatus = PROG_E_NOT_OK;
            }
            break;

        case PROG_COHERENCY_READ_SIGNATURE:
            /* Read signature information */
            eProgStatus = PROG_MemDataAccess(
                    m_astCfgMemory[stConfigSegment[m_ubSegmentId].ubMemoryIdx].eMemoryType,
                    PROG_MEM_OPERATION_TYPE_READ,
                    stConfigSegment[m_ubSegmentId].ulStartAddress,
                    PROG_SIGNATURE_AREA_SIZE,
                    (u8*)&m_stSignatureInfo);

            if (PROG_E_OK == eProgStatus)
            {
                //check signature pattern
                if (m_stSignatureInfo.ulStatus == PROG_SIG)
                {
                    m_stSignatureInfo.ulStartAddress = stConfigSegment[m_ubSegmentId].ulStartAddress + PROG_SIGNATURE_AREA_SIZE;
                    m_stSignatureInfo.ulSize = stConfigSegment[m_ubSegmentId].ulEndAddress - stConfigSegment[m_ubSegmentId].ulStartAddress + 1U - PROG_SIGNATURE_AREA_SIZE;
                    m_ubCoherencyStatus = PROG_COHERENCY_HASH_START;
                    eProgStatus = PROG_E_BUSY;
                }
                else
                {
                    /* Signature info is invalid */
                    LOG(LOG_LEVEL_ERROR, "signature info is invalid");
                    m_ubCoherencyStatus = PROG_COHERENCY_FAILURE;
                    eProgStatus = PROG_E_NOT_OK;
                }
            }
            break;

        case PROG_COHERENCY_HASH_START:
            /* Start calculate MD5 */
            mbedtls_md5_init(&m_Md5Ctx);
            ret = mbedtls_md5_starts_ret(&m_Md5Ctx);
            if (E_OK == ret)
            {
                m_ubCoherencyStatus = PROG_COHERENCY_HASH_UPDATE;
                eProgStatus = PROG_E_BUSY;
            }
            else
            {
                /* MD5 start failure */
                LOG(LOG_LEVEL_ERROR, "md5 start failure");
                mbedtls_md5_free(&m_Md5Ctx);
                m_ubCoherencyStatus = PROG_COHERENCY_FAILURE;
                eProgStatus = PROG_E_NOT_OK;
            }
            break;

        case PROG_COHERENCY_HASH_UPDATE:
            if (m_stSignatureInfo.ulSize == 0U)
            {
                if (stConfigSegment[m_stCurrentSegment.ubSegmentId].ePartitionType == PROG_APPLICATION_PARTITION)
                {
                    m_ubSegmentId += 2U;
                    if (m_ubSegmentId < PROG_SEGMENT_NB)
                    {
                        /* Calculate next APP segment */
                        if (stConfigSegment[m_ubSegmentId].ePartitionType == PROG_APPLICATION_PARTITION)
                        {
                            m_stSignatureInfo.ulStartAddress = stConfigSegment[m_ubSegmentId].ulStartAddress;
                            m_stSignatureInfo.ulSize = stConfigSegment[m_ubSegmentId].ulEndAddress - stConfigSegment[m_ubSegmentId].ulStartAddress + 1U;
                        }
                    }
                    else
                    {
                        /* All APP segment calculated */
                        m_ubCoherencyStatus = PROG_COHERENCY_HASH_FINISH;
                    }

                    eProgStatus = PROG_E_BUSY;
                }
                else if (stConfigSegment[m_stCurrentSegment.ubSegmentId].ePartitionType == PROG_BLU_PARTITION)
                {
                    /* BLU segment calculated */
                    m_ubCoherencyStatus = PROG_COHERENCY_HASH_FINISH;
                    eProgStatus = PROG_E_BUSY;
                }
                else
                {
                    /* Invalid case */
                    m_ubCoherencyStatus = PROG_COHERENCY_FAILURE;
                    eProgStatus = PROG_E_NOT_OK;
                }
                break;
            }

            if (m_stSignatureInfo.ulSize >= PROG_HASH_CALC_SIZE)
            {
                ulCalcLength = PROG_HASH_CALC_SIZE;
            }
            else
            {
                ulCalcLength = m_stSignatureInfo.ulSize;
            }

            eProgStatus = PROG_MemDataAccess(
                    m_astCfgMemory[stConfigSegment[m_ubSegmentId].ubMemoryIdx].eMemoryType,
                    PROG_MEM_OPERATION_TYPE_READ,
                    m_stSignatureInfo.ulStartAddress,
                    ulCalcLength,
                    aubHashValue);

            if (PROG_E_OK == eProgStatus)
            {
                ret = mbedtls_md5_update_ret(&m_Md5Ctx, aubHashValue, ulCalcLength);
                if (E_OK == ret)
                {
                    m_stSignatureInfo.ulStartAddress += ulCalcLength;
                    m_stSignatureInfo.ulSize -= ulCalcLength;
                    eProgStatus = PROG_E_BUSY;
                }
                else
                {
                    /* MD5 update failure */
                    LOG(LOG_LEVEL_ERROR, "md5 update failure");
                    mbedtls_md5_free(&m_Md5Ctx);
                    m_ubCoherencyStatus = PROG_COHERENCY_FAILURE;
                    eProgStatus = PROG_E_NOT_OK;
                }
            }
            else
            {
               /* Read data failure */
                LOG(LOG_LEVEL_ERROR, "read 0x%08X failure", m_stSignatureInfo.ulStartAddress);
                mbedtls_md5_free(&m_Md5Ctx);
                m_ubCoherencyStatus = PROG_COHERENCY_FAILURE;
                eProgStatus = PROG_E_NOT_OK;
            }
            break;

        case PROG_COHERENCY_HASH_FINISH:
            /* Finish calculate MD5 */
            ret = mbedtls_md5_finish_ret(&m_Md5Ctx, m_aubHash);
            mbedtls_md5_free(&m_Md5Ctx);
            if (E_OK == ret)
            {
                m_ubCoherencyStatus = PROG_COHERENCY_VERIFY;
                eProgStatus = PROG_E_BUSY;
            }
            else
            {
                /* MD5 finish failure */
                LOG(LOG_LEVEL_ERROR, "md5 finish failure");
                m_ubCoherencyStatus = PROG_COHERENCY_FAILURE;
                eProgStatus = PROG_E_NOT_OK;
            }
            break;

        case PROG_COHERENCY_VERIFY:
            /* Verify signature */
            
            ret = mbedtls_verify(m_aubHash, m_stSignatureInfo.ubSignature);
            // ret = TS_MemCmp(m_aubHash,m_stSignatureInfo.ubSignature,PROG_HASH_LENGTH);
            if (E_OK == ret)
            {
                /* Verify success */
                if (m_ubSegmentId == PROG_SEG_BOOTLOADERBACKUP)
                {
                    /* Check bootloader updater signature */
                    m_ubSegmentId = PROG_SEG_BOOTLOADERUPDATER;
                    m_ubCoherencyStatus = PROG_COHERENCY_READ_SIGNATURE;
                    LOG(LOG_LEVEL_INFO, "Signature verify Bakeup FBL OK !");
                }
                else
                {
                    m_ubCoherencyStatus = PROG_COHERENCY_WRITE_FLASH_STATUS;
                    if (m_ubSegmentId == PROG_SEG_BOOTLOADERUPDATER)
                    {
                        LOG(LOG_LEVEL_INFO, "Signature verify BLU OK !");
                    }
                }

                eProgStatus = PROG_E_BUSY;
                
            }

            #if defined(RELEASE_VERSION)
            else
            {
                /* Verify failure */
                m_ubCoherencyStatus = PROG_COHERENCY_FAILURE;
                eProgStatus = PROG_E_NOT_OK;

                if (m_ubSegmentId == PROG_SEG_BOOTLOADERUPDATER)
                {
                    LOG(LOG_LEVEL_ERROR, "Signature verify BLU ERROR !");
                }
                else if (m_ubSegmentId == PROG_SEG_BOOTLOADERBACKUP)
                {
                    LOG(LOG_LEVEL_ERROR, "Signature verify Bakeup FBL ERROR !");
                }
                else 
                {
                    LOG(LOG_LEVEL_ERROR, "Signature verify APP ERROR !");
                }
            }
            #else
            else
            {
                /* Verify success */
                if (m_ubSegmentId == PROG_SEG_BOOTLOADERBACKUP)
                {
                    /* Check bootloader updater signature */
                    m_ubSegmentId = PROG_SEG_BOOTLOADERUPDATER;
                    m_ubCoherencyStatus = PROG_COHERENCY_READ_SIGNATURE;
                }
                else
                {
                    m_ubCoherencyStatus = PROG_COHERENCY_WRITE_FLASH_STATUS;
                }
                LOG(LOG_LEVEL_INFO, "DEBUG verify success !");
                eProgStatus = PROG_E_BUSY;
            }
            #endif
            
            break;

        case PROG_COHERENCY_WRITE_FLASH_STATUS:

            if (stConfigSegment[m_stCurrentSegment.ubSegmentId].ePartitionType == PROG_APPLICATION_PARTITION)
            {
                m_ubSegmentId = m_stCurrentSegment.ubSegmentId % 2U;
                LOG(LOG_LEVEL_INFO, "Set APP %c flash status valid", 'A' + m_ubSegmentId);
            }
            else if (stConfigSegment[m_stCurrentSegment.ubSegmentId].ePartitionType == PROG_BLU_PARTITION)
            {
                m_ubSegmentId = PROG_SEG_BOOTLOADERUPDATER;
                LOG(LOG_LEVEL_INFO, "Set bootloader BLU flash status");
            }
            else
            {
            }

            /* Write flash status */
            eProgStatus = PROG_WriteFlashStatus(m_ubSegmentId);
            if (PROG_E_OK == eProgStatus)
            {
                m_ubCoherencyStatus = PROG_COHERENCY_CHECK_FLASH_STATUS;
                eProgStatus = PROG_E_BUSY;
            }
            else
            {
                LOG(LOG_LEVEL_ERROR, "write flash status failure");
                m_ubCoherencyStatus = PROG_COHERENCY_FAILURE;
                eProgStatus = PROG_E_NOT_OK;
            }
            break;

        case PROG_COHERENCY_CHECK_FLASH_STATUS:
            /* Check flash status */
            eProgStatus = PROG_CheckFlashStatus(m_ubSegmentId);
            if (PROG_E_OK == eProgStatus)
            {
                m_ubCoherencyStatus = PROG_COHERENCY_SUCCESS;
                eProgStatus = PROG_E_BUSY;
            }
            else
            {
                LOG(LOG_LEVEL_ERROR, "check flash status failure");
                m_ubCoherencyStatus = PROG_COHERENCY_FAILURE;
                eProgStatus = PROG_E_NOT_OK;
            }
            break;

        // case PROG_COHERENCY_EXCHANGE:
        //     if (stConfigSegment[m_stCurrentSegment.ubSegmentId].ePartitionType == PROG_APPLICATION_PARTITION)
        //     {
        //         ubApplicationRunningArea = APP_GetApplicationRunningArea();
        //         if(ubApplicationRunningArea == (m_stCurrentSegment.ubSegmentId % 2U)) 
        //         {
        //             LOG(LOG_LEVEL_INFO, "running area and download area is same");
        //             m_ubCoherencyStatus = PROG_COHERENCY_SUCCESS;
        //             eProgStatus = PROG_E_BUSY;
        //         }
        //         else
        //         {
        //             eAppBoolean = APP_ChangeToApplicationRunningArea(m_stCurrentSegment.ubSegmentId % 2U);
        //             if (PROG_TRUE == eAppBoolean)
        //             {
        //                 LOG(LOG_LEVEL_INFO, "change to application %c success", 'A' + (m_stCurrentSegment.ubSegmentId % 2U));
        //                 m_ubCoherencyStatus = PROG_COHERENCY_SUCCESS;
        //                 eProgStatus = PROG_E_BUSY;
        //             }
        //             else
        //             {
        //                 LOG(LOG_LEVEL_ERROR, "change to application %c failure", 'A' + (m_stCurrentSegment.ubSegmentId % 2U));
        //                 m_ubCoherencyStatus = PROG_COHERENCY_FAILURE;
        //                 eProgStatus = PROG_E_NOT_OK;
        //             }
        //         }
        //     }
        //     else
        //     {
        //         m_ubCoherencyStatus = PROG_COHERENCY_SUCCESS;
        //         eProgStatus = PROG_E_BUSY;
        //     }
        //     break;

        case PROG_COHERENCY_SUCCESS:
            if (stConfigSegment[m_stCurrentSegment.ubSegmentId].ePartitionType == PROG_BLU_PARTITION)
            {
                /* Update FBL downloaded successfully counter */
                (void)APP_WriteSecureUpdatingLog(FBL_DOWNLOADED_SUCCESSFULLY_COUNTER);

                /* Set FBL download flag */
                PROG_CustomSetBLUDownloadInProgress(PROG_TRUE);

                /* perform software reset */
                BoardPerformSwReset();
                eProgStatus = PROG_E_BUSY;
            }
            else
            {
                /* Update APP downloaded successfully counter */
                (void)APP_WriteSecureUpdatingLog(APP_DOWNLOADED_SUCCESSFULLY_COUNTER);
                eProgStatus = PROG_E_OK;
            }
            break;

        case PROG_COHERENCY_FAILURE:
            LOG(LOG_LEVEL_WARNING, "COHERENCY CHECK FAILURE!!! ");
            eProgStatus = PROG_E_NOT_OK;
            break;

        default :
            break;
    }

    OSC_PARAM_UNUSED(eCohChkResult);

    return eProgStatus;
}

/** \brief This API is called to store the computed Application checksum in non-volatile memory
 **
 ** Callback is called:  Before sending response to CheckMemory request for authenticated block
 **
 ** Callback shall implement: store in non-volatile memory the Application checksum (will be
 ** compare at next startup with one calculated by application). It shall also update the checksum
 ** computed by application.
 **
 ** \param[in] pubComputedChecksum Pointer to Application checksum to store.
 ** \param[in] uwBlockIdentifier Block Identifier.
 **
 **/
void PROG_CustomSetApplicationChecksum(u8 * pubComputedChecksum, u16 uwBlockIdentifier)
{
    OSC_PARAM_UNUSED(pubComputedChecksum);
    OSC_PARAM_UNUSED(uwBlockIdentifier);
}

/** \brief Notification of a download event
 **
 ** Callback is called: On reception of RequestDownload routine
 **
 ** Callback shall implement: provide information that the Flash Memory was programmed and should be erased before 
                            a new writing and customer specific implementation on download event
 **
 ** \param[in] ulStartAddress received start address value
 ** \param[in] ulMemorySize received memory size value
 **
 ** \return eProgStatus success of the operation
 ** \retval PROG_E_OK
 ** \retval PROG_E_NOT_OK
 **/
tProgStatus PROG_CustomDownloadNotification(u32 ulStartAddress, u32 ulMemorySize)
{
    OSC_PARAM_UNUSED(ulStartAddress);
    OSC_PARAM_UNUSED(ulMemorySize);

    return PROG_E_OK;
}

/** \brief Notification of memory access to allow customers to place their routines
 **
 ** Callback is called: After successful memory data access
 **
 ** Callback shall implement: Operation that need to be performed after a memory data access
 **
 ** \param[in] eMemType Memory type (RAM, Flash and Flash Ext)
 ** \param[in] eOperationType Operation type (Read, write and erase)
 ** \param[in] uMemAddress Start address
 ** \param[in] ulLength Data length
 ** \param[in] paubDataBuffer Data buffer
 **
 ** \return eProgStatus success of the operation(s)
 ** \retval PROG_E_OK
 ** \retval PROG_E_NOT_OK
 **/
tProgStatus PROG_CustomMemoryAccessNotification
(
    tProgMemType eMemType,
    tOperationType eOperationType,
    tProgAddressType uMemAddress,
    tDataLength ulLength,
    tDataBufferType PROG_FAR_POINTER paubDataBuffer
)
{
    OSC_PARAM_UNUSED(eMemType);
    OSC_PARAM_UNUSED(eOperationType);
    OSC_PARAM_UNUSED(uMemAddress);
    OSC_PARAM_UNUSED(ulLength);
    OSC_PARAM_UNUSED(paubDataBuffer);

    return PROG_E_OK;
}

/** \brief This API is called to set a flag which indicate that the BLU donwload is in progress
 **
 ** Callback is called: After a BLU sucessfull download
 **
 ** \param[in] ubBLUDownload indicating if BLU download is in progress
 **
 ** Callback shall implement: set the flag in a non-volatile memory
 **
 ** \return void
 **
 **/
void PROG_CustomSetBLUDownloadInProgress(tProgBoolean ubBLUDownload)
{
    LOG(LOG_LEVEL_INFO, "Custom set BLU status %s", ubBLUDownload == TRUE?" VALID!":"INVALID!");

    if (PROG_TRUE == ubBLUDownload)
    {
        /* Set the flag */
        m_ulBluSig = PROG_SIG;
    }
    else
    {
        /* Clear the flag */
        m_ubBMTimeoutCount = 0U;
        m_ulBluSig = PROG_SIG_CLEAR;
    }
}

/** \brief This API is called to get a flag which indicate if the BLU donwload is in progress
 **
 ** Callback is called: during the reset to check if BLU donwload is in progress, if true resume the BLU download
 **
 ** Callback shall implement: read of the flag from a non-volatile memory
 **
 ** \return BLU Download status
 ** \retval PROG_TRUE if BLU Download is in progress
 ** \retval PROG_FALSE if BLU Download isn't in progress
 **/
tProgBoolean PROG_CustomIsBLUDownloadInProgress(void)
{
    tProgBoolean eProgBoolean;

    LOG(LOG_LEVEL_INFO, "BluSig 0x%08X ,BLU is %s", m_ulBluSig,(m_ulBluSig == PROG_SIG)?"IN PROGRESS!":"NOT IN PROGRESS!");

    /* Check if the signature is set */
    if (m_ulBluSig == PROG_SIG)
    {
        /* BLU Download is in progress */
        eProgBoolean = PROG_TRUE;
    }
    else
    {
        /* BLU Download isn't in progress */
        eProgBoolean = PROG_FALSE;
    }

    return eProgBoolean;
}

/** \brief This API is called to check if the current block/segment is BLUpdater
 **
 ** Callback is called: After a successful or unsuccessful block/segment verification of the BLUpdater
 **
 ** Callback shall implement: read on the flashed data the area of the BLU marker and check it if it matches the BLU pattern
 **
 ** \param[in] ubLogicalBlockId The id of the logical block for which the presence of BLU pattern is checked
 ** \param[in] ubLogicalSegmentId The id of the logical segment  for which the presence of BLU pattern is checked
 **            (ignore if the full logical block is verified)
 **
 ** \return BLU Pattern presence
 ** \retval PROG_TRUE if BLU Pattern is present
 ** \retval PROG_FALSE if BLU Pattern is absent
 **/
tProgBoolean PROG_CustomIsBLUPatternPresent(u8 ubLogicalBlockId, u8 ubLogicalSegmentId)
{
    OSC_PARAM_UNUSED(ubLogicalBlockId);
    OSC_PARAM_UNUSED(ubLogicalSegmentId);
    return PROG_FALSE;
}

/** \brief Callback used for BLUpdater download, called after comparing the expected CRC and the calculated one.
 **
 ** Callback is called: After a successful or unsuccessful block/segment verification of the BLUpdater
 **
 ** Callback shall implement: update of the logical block validity status
 **
 ** \param[in] ubCompareSuccess TRUE if the 2 elements of the comparison are identical
 **
 ** \return state
 ** \retval PROG_E_OK Treatment finished successfully
 ** \retval PROG_E_NOT_OK Error happened during treatment
 **/
tProgStatus PROG_CustomSetBLUVerificationSuccess(tProgBoolean ubCompareSuccess)
{
    OSC_PARAM_UNUSED(ubCompareSuccess);
    return PROG_E_OK;
}

/** \brief This API is called to do the flash status check treatment
 **
 ** \param[in] ubLogicalSegmentId The id of the logical segment for which the check was done
 **
 ** \return Check result
 ** \retval PROG_E_OK Flash status flag is set
 ** \retval PROG_E_NOT_OK Flash status flag is not set
 **/
tProgStatus PROG_CheckFlashStatus(u8 ubLogicalSegmentId)
{
    tProgStatus eProgStatus;
    u8 ubIdx;
    u32 aulFlashStatusValue[PROG_FLASH_STATUS_SIZE / 4U];

    /* Read flash status flag */
    eProgStatus = PROG_MemDataAccess(
            m_astCfgMemory[stConfigSegment[ubLogicalSegmentId].ubMemoryIdx].eMemoryType,
            PROG_MEM_OPERATION_TYPE_READ,
            (u32) (stConfigSegment[ubLogicalSegmentId].ulEraseStartAddress + PROG_FLASH_STATUS_OFFSET),
            PROG_FLASH_STATUS_SIZE,
            (u8*)aulFlashStatusValue);

    if (PROG_E_OK == eProgStatus)
    {
        for (ubIdx = 0U; ubIdx < PROG_FLASH_STATUS_SIZE / 4U; ubIdx++)
        {
            if(aulFlashStatusValue[ubIdx] != PROG_SIG)
            {
                eProgStatus = PROG_E_CHECK_FAILED;
                break;
            }
        }
    }

    if (PROG_E_OK == eProgStatus)
    {
       LOG(LOG_LEVEL_INFO, "check segment %d flash status success", ubLogicalSegmentId);
    }
    else
    {
       LOG(LOG_LEVEL_WARNING, "check segment %d flash status failure", ubLogicalSegmentId);
    }

    return eProgStatus;
}

/** \brief This API is called to do the flash status erase treatment
 **
 ** \param[in] ubLogicalSegmentId The id of the logical segment for which the erase was done
 **
 ** \return Erase result
 ** \retval PROG_E_OK Erase flash status success
 ** \retval PROG_E_NOT_OK Erase flash status failure
 **/
tProgStatus PROG_EraseFlashStatus(u8 ubLogicalSegmentId)
{
    tProgStatus eProgStatus;

    /* Erase flash status flag */
    eProgStatus = PROG_MemDataAccess(
            m_astCfgMemory[stConfigSegment[ubLogicalSegmentId].ubMemoryIdx].eMemoryType,
            PROG_MEM_OPERATION_TYPE_ERASE,
            (u32)(stConfigSegment[ubLogicalSegmentId].ulEraseStartAddress + PROG_FLASH_STATUS_OFFSET),
            PROG_FLASH_STATUS_SIZE,
            NULL_PTR);

    if (PROG_E_OK == eProgStatus)
    {
       LOG(LOG_LEVEL_INFO, "erase segment %d flash status success", ubLogicalSegmentId);
    }
    else
    {
       LOG(LOG_LEVEL_ERROR, "erase segment %d flash status failure", ubLogicalSegmentId);
    }

    return eProgStatus;
}

/** \brief This API is called to do the flash status write treatment
 **
 ** \param[in] ubLogicalSegmentId The id of the logical segment for which the write was done
 **
 ** \return Write result
 ** \retval PROG_E_OK Write flash status success
 ** \retval PROG_E_NOT_OK Write flash status failure
 **/
tProgStatus PROG_WriteFlashStatus(u8 ubLogicalSegmentId)
{
    tProgStatus eProgStatus;
    u8 ubIdx;
    u32 aulFlashStatusValue[PROG_FLASH_STATUS_SIZE / 4U];

    for (ubIdx = 0U; ubIdx < PROG_FLASH_STATUS_SIZE / 4U; ubIdx ++)
    {
        aulFlashStatusValue[ubIdx] = PROG_SIG;
    }

    /* Write flash status flag */
    eProgStatus = PROG_MemDataAccess(
            m_astCfgMemory[stConfigSegment[ubLogicalSegmentId].ubMemoryIdx].eMemoryType,
            PROG_MEM_OPERATION_TYPE_WRITE,
            (u32) (stConfigSegment[ubLogicalSegmentId].ulEraseStartAddress + PROG_FLASH_STATUS_OFFSET),
            PROG_FLASH_STATUS_SIZE,
            (u8*)aulFlashStatusValue);

    if (PROG_E_OK == eProgStatus)
    {
       LOG(LOG_LEVEL_INFO, "write segment %d flash status success", ubLogicalSegmentId);
    }
    else
    {
       LOG(LOG_LEVEL_ERROR, "write segment %d flash status failure", ubLogicalSegmentId);
    }

    return eProgStatus;
}

tProgStatus PROG_BackupFingerprint(u8 ubLogicalSegmentId)
{
    tProgStatus eProgStatus;

    eProgStatus = PROG_MemDataAccess(
            m_astCfgMemory[stConfigSegment[ubLogicalSegmentId].ubMemoryIdx].eMemoryType,
            PROG_MEM_OPERATION_TYPE_READ,
            //0x80100000 + 0x100 or 0x80200000 + 0x100
            (u32) (stConfigSegment[ubLogicalSegmentId].ulEraseStartAddress + PROG_FINGER_PRINT_OFFSET),
            (PROG_FINGER_PRINT_NUM - 1U) * PROG_FINGER_PRINT_SIZE,
            &m_aubFingerPrint[1U][0U]);

    if (PROG_E_OK == eProgStatus)
    {
       LOG(LOG_LEVEL_INFO, "backup segment %d finger print success", ubLogicalSegmentId);
    }
    else
    {
       LOG(LOG_LEVEL_ERROR, "backup segment %d finger print failure", ubLogicalSegmentId);
    }

    return eProgStatus;
}

/** \brief This API is called to do the finger print write treatment
 **
 ** \param[in] ubLogicalSegmentId The id of the logical segment for which the write was done
 **
 ** \return Write result
 ** \retval PROG_E_OK Write finger print success
 ** \retval PROG_E_NOT_OK Write finger print failure
 **/
tProgStatus PROG_SaveFingerprint(u8 ubLogicalSegmentId)
{
    tProgStatus eProgStatus;

    /* Write finger print */
    eProgStatus = PROG_MemDataAccess(
            m_astCfgMemory[stConfigSegment[ubLogicalSegmentId].ubMemoryIdx].eMemoryType,
            PROG_MEM_OPERATION_TYPE_WRITE,
            (u32) (stConfigSegment[ubLogicalSegmentId].ulEraseStartAddress + PROG_FINGER_PRINT_OFFSET),
            PROG_FINGER_PRINT_SIZE * PROG_FINGER_PRINT_NUM,
            &m_aubFingerPrint[0U][0U]);

    if (PROG_E_OK == eProgStatus)
    {
       LOG(LOG_LEVEL_INFO, "save segment %d finger print success", ubLogicalSegmentId);
    }
    else
    {
       LOG(LOG_LEVEL_ERROR, "save segment %d finger print failure", ubLogicalSegmentId);
    }

    return eProgStatus;
}

/** \brief Callback for the diagnostic request (configuration) 
 **
 ** The diagnostic request is valid (filtering completed).
 ** The callback configured for this service is used.
 ** 
 ** \param[in,out] puwLen pointer on data length
 ** \param[in,out] aubUdsData pointer on data
 ** 
 ** \return Diagnostic response status
 ** \retval UDS_ACK     Positive response
 ** \retval UDS_NRC_xxx Negative response code.
 **
 **/
tUdsStatus PROG_ReadFingerprint(u16 *puwLen, u8 *aubUdsData)
{
    tUdsStatus   eUdsStatus;
    tProgStatus  eProgStatus;
    u8 ubLocalSegmentId;

    /* Get application running area */
    ubLocalSegmentId = APP_GetApplicationRunningArea();

    /* Check application status */
    eProgStatus = PROG_CheckFlashStatus(ubLocalSegmentId);
    if (eProgStatus == PROG_E_OK)
    {
        /* Application is vaild, read finger print form application area */
        eProgStatus = PROG_MemDataAccess(
                m_astCfgMemory[stConfigSegment[ubLocalSegmentId].ubMemoryIdx].eMemoryType,
                PROG_MEM_OPERATION_TYPE_READ,
                (u32)(stConfigSegment[ubLocalSegmentId].ulEraseStartAddress + PROG_FINGER_PRINT_OFFSET),
                PROG_FINGER_PRINT_SIZE,
                &aubUdsData[3U]);
         
        if (PROG_E_OK == eProgStatus)
        {
            *puwLen = 3U + PROG_FINGER_PRINT_SIZE;
            eUdsStatus = UDS_ACK;
        }
        else
        {
            /* error during reading */
            eUdsStatus = UDS_NRC_72;
        }
    }
    else
    {
        /* Application is not vaild, response default value */
        TS_MemSet(&aubUdsData[3U], 0xFFU, PROG_FINGER_PRINT_SIZE);
        *puwLen = 3U + PROG_FINGER_PRINT_SIZE;
        eUdsStatus = UDS_ACK;
    }

    return eUdsStatus;
}

/** \brief This API is called to do the boot signature check treatment
 **
 ** \param[in] ubLogicalSegmentId The id of the logical segment for which the check was done
 **
 ** \return Check result
 ** \retval PROG_E_OK Boot signature is OK
 ** \retval PROG_E_NOT_OK Boot signature is error
 **/
tProgStatus PROG_CheckBootSignature(u8 ubLogicalSegmentId)
{
    tProgStatus eProgStatus;
    int ret;
    u8 ubIdx;
#if defined(RELEASE_VERSION)

    eProgStatus = PROG_E_NOT_OK;

    for (ubIdx = 0U; ((ubIdx < PROG_BOOT_SIGNATURE_CHECK_COUNT) && (PROG_E_OK != eProgStatus)); ubIdx++)
    {
        /* Read signature information */
        eProgStatus = PROG_MemDataAccess(
                m_astCfgMemory[stConfigSegment[ubLogicalSegmentId].ubMemoryIdx].eMemoryType,
                PROG_MEM_OPERATION_TYPE_READ,
                (u32)(stConfigSegment[ubLogicalSegmentId].ulStartAddress + PROG_SIGNATURE_AREA_SIZE),
                PROG_SIGNATURE_AREA_SIZE,
                (u8*)&m_stSignatureInfo);

        if (PROG_E_OK == eProgStatus)
        {
            if ((m_stSignatureInfo.ulStatus != PROG_SIG) || (m_stSignatureInfo.ulSize == 0))
            {
                /* Signature information is invalid */
                eProgStatus = PROG_E_NOT_OK;
            }
        }

        if (PROG_E_OK == eProgStatus)
        {
            /* Calculate MD5 */
            ret = mbedtls_md5_ret((u8*)(m_stSignatureInfo.ulStartAddress), m_stSignatureInfo.ulSize, m_aubHash);
            if (ret != E_OK)
            {
                eProgStatus = PROG_E_NOT_OK;
            }
        }

        if (PROG_E_OK == eProgStatus)
        {
            #if defined(RELEASE_VERSION)
            /* Verify signature */
            ret = mbedtls_verify(m_aubHash, m_stSignatureInfo.ubSignature);
            // ret = TS_MemCmp(m_aubHash,m_stSignatureInfo.ubSignature,PROG_HASH_LENGTH);
            if (ret != E_OK)
            {
                eProgStatus = PROG_E_NOT_OK;
            }
            #else
            eProgStatus = PROG_E_OK;
            #endif
        }
    }

#else
    eProgStatus = PROG_E_OK;
#endif


    return eProgStatus;
}

/** \brief This API is called to do the flash driver signature check treatment
 **
 ** \param[in] ubLogicalSegmentId The id of the logical segment for which the check was done
 **
 ** \return Check result
 ** \retval PROG_E_OK Flash driver signature is right
 ** \retval PROG_E_NOT_OK Flash driver signature is wrong
 **/
tProgStatus PROG_CheckFlashDriverSignature(u8 ubLogicalSegmentId)
{
    tProgStatus eProgStatus;
    int ret;

    /* Read signature information */
    eProgStatus = PROG_MemDataAccess(
            m_astCfgMemory[stConfigSegment[ubLogicalSegmentId].ubMemoryIdx].eMemoryType,
            PROG_MEM_OPERATION_TYPE_READ,
            (u32)(stConfigSegment[ubLogicalSegmentId].ulStartAddress),
            PROG_SIGNATURE_AREA_SIZE,
            (u8*)&m_stSignatureInfo);

    if (PROG_E_OK == eProgStatus)
    {
        if (m_stSignatureInfo.ulStatus == PROG_SIG)
        {   
            //all flash driver will be verified
            m_stSignatureInfo.ulStartAddress = stConfigSegment[ubLogicalSegmentId].ulStartAddress + PROG_SIGNATURE_AREA_SIZE;
            m_stSignatureInfo.ulSize = stConfigSegment[ubLogicalSegmentId].ulEndAddress - stConfigSegment[ubLogicalSegmentId].ulStartAddress + 1U - PROG_SIGNATURE_AREA_SIZE;
        }
        else
        {
            /* Signature information is invalid */
            eProgStatus = PROG_E_NOT_OK;
        }
    }

    if (PROG_E_OK == eProgStatus)
    {
        /* Calculate MD5 */
        ret = mbedtls_md5_ret((u8*)(m_stSignatureInfo.ulStartAddress), m_stSignatureInfo.ulSize, m_aubHash);
        if (ret != E_OK)
        {
            eProgStatus = PROG_E_NOT_OK;
        }
    }

    if (PROG_E_OK == eProgStatus)
    {
        #if defined(RELEASE_VERSION)
        /* Verify signature */
        ret = mbedtls_verify(m_aubHash, m_stSignatureInfo.ubSignature);
        // ret = TS_MemCmp(m_aubHash,m_stSignatureInfo.ubSignature,PROG_HASH_LENGTH);
        if (ret != E_OK)
        { 
            eProgStatus = PROG_E_NOT_OK;
        }
        #else
        eProgStatus = PROG_E_OK;
        #endif
    }

    return eProgStatus;
}

/*---------------Start PROG_CustomSegmentCheck,check mutex in case programming area----*/ 
tProgStatus PROG_CustomSegmentCheck(u8 ubLogicalSegmentId)
{
    tProgStatus eProgStatus;
    u8 ubApplicationRunningArea;
    u8 ubApplicationDownloadArea;

    eProgStatus = PROG_E_OK;

    if (stConfigSegment[ubLogicalSegmentId].ePartitionType == PROG_APPLICATION_PARTITION)
    {
        ubApplicationDownloadArea = ubLogicalSegmentId % 2U;
        ubApplicationRunningArea = APP_GetApplicationRunningArea();

        if(ubApplicationRunningArea == ubApplicationDownloadArea) 
        {
            LOG(LOG_LEVEL_ERROR, "running area and download area is same");
            eProgStatus = PROG_E_NOT_OK;
        }
    }

    return eProgStatus;
}

/*---------------------End PROG_CustomSegmentCheck-----------------------------------*/