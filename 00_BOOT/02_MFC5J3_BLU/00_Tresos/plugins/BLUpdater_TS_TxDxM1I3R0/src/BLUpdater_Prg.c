/*===============================================================================*/
/*                                                                               */
/*                               BOOT Layers                                     */
/*                                                                               */
/* ----------------------------------------------------------------------------- */
/*                                                                               */
/*                               BLUpdater layer                                 */
/*                                                                               */
/*===============================================================================*/
/*%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%                                        */
/*%%   _____________________________   %%  \file BLUpdater_Prg.c                 */
/*%%  |                             |  %%  \brief BLUpdater layer include plugin file */
/*%%  |   &&&&&   &&&&&             |  %%  Module version: 1.3.0 BL3                */
/*%%  |   &       &    &            |  %%  Variant: OsekCore                  */
/*%%  |   &&&&    &&&&&             |  %%                                        */
/*%%  |   &       &    &            |  %%                                        */
/*%%  |   &&&&&   &&&&&             |  %%                                        */
/*%%  |_____________________________|  %%                                        */
/*%%                                   %%                                        */
/*%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%                                        */
/*===============================================================================*/
/* Copyright 2010 by Elektrobit Automotive GmbH                                  */
/* All rights exclusively reserved for Elektrobit Automotive GmbH,               */
/* unless expressly agreed to otherwise.                                         */
/*===============================================================================*/
/*
 * MISRA-C:2012 Deviation List
 *
 * MISRAC2012-1) Deviated Rule: 11.4 (advisory)
 * A cast shall not be performed between a pointer to object type and a pointer to a different
 * object type.
 *
 *   Reason:
 * The memory routines are optimized for dealing with aligned memory
 * and the correct alignment has been checked before converting
 * to different object types
 *
 * MISRAC2012-2) Deviated Rule: 8.4 (required)
 * A compatible declaration shall be visible when an object or function with external
 * linkage is defined
 *
 *   Reason:
 * This variable need to be used in test environment
 */

/*=================================[inclusions]==================================*/
#include "EB_Prj.h"
#include "BLUpdater_Priv.h"
#include "BLUpdater_Trace.h"
#include "board.h"
/*============================= PUBLIC DEFINITIONS ==============================*/
/*                                                                               */
/*-------------------------------------------------------------------------------*/
/* - Public Variables                                                            */

/*-------------------------------------------------------------------------------*/
/* - Public Function Prototypes                                                  */

/*-------------------------------------------------------------------------------*/
/* - Public Callback Prototypes                                                  */

/*                                                                               */
/*===============================================================================*/

/*============================ PRIVATE DEFINITIONS ==============================*/
/*                                                                               */
/*-------------------------------------------------------------------------------*/
/* - Private Constants                                                           */

/*-------------------------------------------------------------------------------*/
/* - Private Types                                                               */

/*-------------------------------------------------------------------------------*/
/* - Private Variables                                                           */
#if (BLU_COMMUNICATION_SUPPORT ==STD_ON)
/* Pdu Tx Identifier on which to send periodic NRC 78 frames */
NCS_PRI_VAR PduIdType m_uwtxPduId;
/* Counter for triggering periodically NRC 78 */
NCS_PRI_VAR u16 m_uwCount;
/* Contains request information */
NCS_PRI_VAR PduInfoType m_stDiagMessageInfo;
/* Deviation MISRAC2012-2 */
/* Data to send for NRC 78 on Routine Control */
NCS_PRI_VAR u8 m_aubData[8U] = {0x03, 0x7F, 0x31, 0x78, 0x00, 0x00, 0x00, 0x00};
#endif /* (BLU_COMMUNICATION_SUPPORT ==STD_ON) */

/* Global status of different operations asked to Flash driver */
NCS_PRI_VAR tFlashStatus m_ubFlashStatus;
/* Global status of current operation in progress (Write, Erase, Compare) */
NCS_PRI_VAR tBLUOperation m_ubCurrentBLUOperation;

/*===============================================================================*/

/*-------------------------------------------------------------------------------*/
/* - Private Macros                                                              */
/*-------------------------------------------------------------------------------*/
/* - Private Function Prototypes                                                */
NCS_PRI_FCT tBLUStatus BLU_Write(void);
NCS_PRI_FCT tBLUStatus BLU_Erase(void);
NCS_PRI_FCT tBLUStatus BLU_Compare(void);
NCS_PRI_FCT tBLUStatus BLU_SecureBootUpdate(void);
NCS_PRI_FCT tBLUStatus BLU_MemCmp(u8* pubMemoryAddress1, u8* pubMemoryAddress2, u32 ulMemorySize);
#if (BLU_COMMUNICATION_SUPPORT ==STD_ON)
NCS_PRI_FCT void BLU_Triggering_NRC78(void);
#endif /* (BLU_COMMUNICATION_SUPPORT ==STD_ON) */
NCS_PRI_FCT void BLU_Reset(tBLUBoolean eBLUValidity);
/*                                                                               */
/*===============================================================================*/

/*=============================== IMPLEMENTATION ================================*/
/*                                                                               */


/*----------------------------------------------------------------------------*/
/*          Erasing the old bootloader area                                   */
/*-----------------------------{BLU_Erase}------------------------------------*/
NCS_PRI_FCT tBLUStatus BLU_Erase(void)
{
    u32 ulBootReprogSize;
    tBLUStatus eBLUStatus;

    DBG_BLU_ERASE_ENTRY();

    eBLUStatus = BLU_E_OK;
    ulBootReprogSize = stConfigBootReprog.ulEndAddress - stConfigBootReprog.ulStartAddress + 1;
    /* Trigger the Erasing job */
    m_ubFlashStatus = FLASH_Erase(stConfigBootReprog.ulStartAddress, ulBootReprogSize);

    /* If an error occurred during the operation */
    if ((m_ubFlashStatus != FLASH_BUSY) && (m_ubFlashStatus != FLASH_NO_ERROR))
    {
        /* Indicate that an error is occurred during the Erase */
        eBLUStatus = BLU_E_NOT_OK;
    }
    else
    {
        /* Do Nothing */
    }

    /* Set the next operation */
    m_ubCurrentBLUOperation = BLU_WRITE;

    DBG_BLU_ERASE_EXIT();

    return eBLUStatus;
}
/*-----------------------------{end BLU_Erase}--------------------------------*/
/*                        Write the New Boot Image                            */
/*-----------------------------{BLU_Write}------------------------------------*/
NCS_PRI_FCT tBLUStatus BLU_Write(void)
{
    u32 ulNewBootImageSize;
    tBLUStatus eBLUStatus;

    DBG_BLU_WRITE_ENTRY();

    eBLUStatus = BLU_E_OK;

    ulNewBootImageSize = stConfigNewBootImage.ulEndAddress - stConfigNewBootImage.ulStartAddress + 1;
    /* Trigger the Writing job */
    /* Deviation MISRAC2012-1 */
    m_ubFlashStatus = FLASH_WriteBuffer((stConfigBootReprog.ulStartAddress), ulNewBootImageSize,
                                   (u8*)(stConfigNewBootImage.ulStartAddress));

    /* If an error occurred during the operation */
    if ((m_ubFlashStatus != FLASH_BUSY) && (m_ubFlashStatus != FLASH_NO_ERROR))
    {
        /* Indicate that an error is occurred during the Write */
        eBLUStatus = BLU_E_NOT_OK;
    }
    else
    {
        /* Do Nothing */
    }

    /* Set the next operation */
    m_ubCurrentBLUOperation = BLU_COMPARE;

    DBG_BLU_WRITE_EXIT();

    return eBLUStatus;
}
/*-----------------------------{end BLU_Write}----------------------------------*/
/*-----------------------------{BLU_MemCmp}-------------------------------------*/
NCS_PRI_FCT tBLUStatus BLU_MemCmp(u8* pubMemoryAddress1, u8* pubMemoryAddress2, u32 ulMemorySize)
{
    u32 ulIndex;
    tBLUStatus eBLUStatus;

    DBG_BLU_MEMCMP_ENTRY(pubMemoryAddress1, pubMemoryAddress2, ulMemorySize);

    eBLUStatus = BLU_E_OK;

    for (ulIndex = 0U; ((ulIndex < ulMemorySize) && (eBLUStatus != BLU_E_NOT_OK)); ulIndex++)
    {
        if (pubMemoryAddress1[ulIndex] != pubMemoryAddress2[ulIndex])
        {
            eBLUStatus = BLU_E_NOT_OK;
        }
        else
        {
            /* Do Nothing */
        }
    }

    DBG_BLU_MEMCMP_EXIT(eBLUStatus);

    return eBLUStatus;
}
/*-----------------------------{end BLU_memcmp}------------------------------------*/
/*             Verification that image is properly written                         */
/*-----------------------------{BLU_Compare}---------------------------------------*/
NCS_PRI_FCT tBLUStatus BLU_Compare(void)
{
    u32 ulNewBootImageSize;
    tBLUStatus eBLUStatus;

    DBG_BLU_COMPARE_ENTRY();

    ulNewBootImageSize = stConfigNewBootImage.ulEndAddress - stConfigNewBootImage.ulStartAddress + 1;
    /* Deviation MISRAC2012-1 */
    eBLUStatus = BLU_MemCmp((u8*)stConfigBootReprog.ulStartAddress, (u8*)stConfigNewBootImage.ulStartAddress, ulNewBootImageSize);

    /* Set the next operation */
#if (BLU_SECURE_BOOT == STD_ON)
    m_ubCurrentBLUOperation = BLU_SECUREBOOT_UPDATE;
#else
    m_ubCurrentBLUOperation = BLU_FINISH;
#endif

    DBG_BLU_COMPARE_EXIT();

    return eBLUStatus;
}
/*-----------------------------{end BLU_Compare}-----------------------------------*/

#if (BLU_SECURE_BOOT == STD_ON)
/*-----------------------------{BLU_SecureBootUpdate}---------------------------------------*/
NCS_PRI_FCT tBLUStatus BLU_SecureBootUpdate(void)
{
    tBLUStatus eBLUStatus;

    DBG_BLU_SECUREBOOTUPDATE_ENTRY();

    /* Update new Bootloader checksum */
    eBLUStatus = BLU_CustomBootChecksumUpdate(BLU_BOOT_START_ADDR, BLU_BOOT_LENGTH);

    if (BLU_E_OK == eBLUStatus)
    {
        /* If no error occurred and not busy, the operation is finish*/
        m_ubCurrentBLUOperation = BLU_FINISH;
    }
    else
    {
        /* Do Nothing */
    }

    DBG_BLU_SECUREBOOTUPDATE_EXIT();

    return eBLUStatus;
}
/*-----------------------------{end BLU_SecureBootUpdate}-----------------------------------*/
#endif

#if (BLU_COMMUNICATION_SUPPORT ==STD_ON)
/*-----------------------------{BLU_Triggering_NRC78}-------------------------------------*/
NCS_PRI_FCT void BLU_Triggering_NRC78(void)
{
    Std_ReturnType retVal;

    DBG_BLU_TRIGGERING_NRC78_ENTRY();

    /* If period is over */
    if (m_uwCount <= 0U)
    {
        /* Reset the counter */
        m_uwCount = BLU_NRC78_SENDING_PERIOD;

        /* Get the txPduId */
        BLU_CustomGetPduID(&m_uwtxPduId);

        /* Send the frame NRC78 on a Routine Control (initialized in BLU_Init) */
        retVal = PduR_BLUpdaterTransmit(m_uwtxPduId, &m_stDiagMessageInfo);

        /* If transmission returned an error */
        if (E_NOT_OK == retVal)
        {
            /* Set to valid the Bootloader Updater before performing a reset */
            BLU_Reset(BLU_TRUE);
        }
        else
        {
            /* Do Nothing */
        }
    }
    else
    {
        /* Decrement the counter */
        m_uwCount--;
    }
    DBG_BLU_TRIGGERING_NRC78_EXIT();
}
/*-----------------------------{end BLU_Triggering_NRC78}--------------------------------*/
#endif /* (BLU_COMMUNICATION_SUPPORT ==STD_ON) */
/*-----------------------------{BLU_Init}-----------------------------------------------*/
void BLU_Init(void)
{
    Std_ReturnType retVal;
    DBG_BLU_INIT_ENTRY();
#if (BLU_COMMUNICATION_SUPPORT ==STD_ON)
    m_uwCount               = BLU_NRC78_SENDING_PERIOD;
#else
    OSC_PARAM_UNUSED(retVal);
#endif /* (BLU_COMMUNICATION_SUPPORT ==STD_ON) */

    m_ubFlashStatus         = FLASH_NO_ERROR;
    m_ubCurrentBLUOperation = BLU_ERASE;

    /* Initialization of Flash driver */
    FLASH_Init();

#if (BLU_COMMUNICATION_SUPPORT ==STD_ON)
    BLU_Custom_Com_Init();

    /* Prepare data for NRC 78 on a Routine Control */
    m_stDiagMessageInfo.SduDataPtr = m_aubData;
    m_stDiagMessageInfo.SduLength = 8U;

    /* Call BLU_CustomGetPduID callback to obtain PduID from Bootloader */
    BLU_CustomGetPduID(&m_uwtxPduId);

    /* Send the frame NRC78 on a Routine Control */
    retVal = PduR_BLUpdaterTransmit(m_uwtxPduId, &m_stDiagMessageInfo);

    /* If transmission returned an error */
    if (E_NOT_OK == retVal)
    {
        /* Set to valid the Bootloader Updater before performing a reset */
        BLU_Reset(BLU_TRUE);
    }
    else
    {
        /* Do Nothing */
    }
#endif /* (BLU_COMMUNICATION_SUPPORT ==STD_ON) */
    DBG_BLU_INIT_EXIT();
}
/*-----------------------------{end BLU_Init}-------------------------------------------*/
/*-----------------------------{BLU_Manage}-----------------------------------------------*/
void BLU_Manage(void)
{
    DBG_BLU_MANAGE_ENTRY();
#if (BLU_COMMUNICATION_SUPPORT ==STD_ON)
    /* Manage the triggering of the send of NRC 78 to Routine Control */
    BLU_Triggering_NRC78();
#endif /* (BLU_COMMUNICATION_SUPPORT ==STD_ON) */

    DBG_BLU_MANAGE_EXIT();
}
/*-----------------------------{end BLU_Manage}-------------------------------------------*/
/*-----------------------------{BLU_Start}-----------------------------------------------*/
void BLU_Start(void)
{
    tBLUStatus eBLUStatus;

    DBG_BLU_START_ENTRY();

    eBLUStatus = BLU_E_OK;

    /* If no operation are in progress */
    if (FLASH_NO_ERROR == m_ubFlashStatus)
    {
        switch (m_ubCurrentBLUOperation)
        {
            case BLU_ERASE :
                /* If current operation is erase */
                /* Call Erase function */
                eBLUStatus = BLU_Erase();
                break;

            case BLU_WRITE :
                /* If current operation is writing in memory */
                /* Call Write function */
                eBLUStatus = BLU_Write();
                break;

            case BLU_COMPARE :
                /* If current operation is comparison */
                /* Compare New BL with BL Image and Check Validity and Invalidity of New BL */
                eBLUStatus = BLU_Compare();
                break;

#if (BLU_SECURE_BOOT == STD_ON)
            case BLU_SECUREBOOT_UPDATE :
                /* If current operation is SecureBoot Update */
                /* Update the SecureBoot with the New BL*/
                eBLUStatus = BLU_SecureBootUpdate();
                break;
#endif

            case BLU_FINISH :
                /* Invalidate the Bootloader Updater before performing a reset */
                (void)BLU_CustomSetValidityNewBootloader(BLU_TRUE);
                BLU_Reset(BLU_FALSE);
                break;

            default:
                /* Nothing to do */
                break;
        }
    }
    /* If job is pending */
    else if (FLASH_BUSY == m_ubFlashStatus)
    {
        /* Trigger job */
        FLASH_MainFunction();

        /* Get status */
        m_ubFlashStatus = FLASH_GetJobStatus();

        if ((m_ubFlashStatus != FLASH_BUSY) && (m_ubFlashStatus != FLASH_NO_ERROR))
        {
            /* Errors happened */
            eBLUStatus = BLU_E_NOT_OK;
        }
        else
        {
            /* Do Nothing */
        }
        /* Call BLU_CustomTriggerWatchdog callback to trigger watchdog */
        BLU_CustomTriggerWatchdog();
    }
    /* No error happened */
    else
    {
        /* Do Nothing */
    }

    if (BLU_E_NOT_OK == eBLUStatus)
    {
        /* Errors happened */
        /* Validate the Bootloader Updater before performing a reset */
        BLU_Reset(BLU_TRUE);
    }
    else
    {
        /* Do Nothing */
    }

    DBG_BLU_START_EXIT();
}
/*-----------------------------{end BLU_Start}-------------------------------------------*/

/*-----------------------------{BLU_Reset}-----------------------------------------------*/
void BLU_Reset(tBLUBoolean eBLUValidity)
{
    DBG_BLU_RESET_ENTRY();

    /* Call BLU_CustomInvalidateBLUpdaterStatus callback for notifying invalidity marker and to invalidate BLU */
    (void)BLU_CustomSetValidityBLUpdater(eBLUValidity);

    /* Reset */
    BoardPerformSwReset();

    DBG_BLU_RESET_EXIT();
}
/*-----------------------------{end BLU_Reset}-------------------------------------------*/

/*-----------------------------{BLUpdater_PduRIfTxConfirmation}-----------------------------------------------*/
#if (BLU_COMMUNICATION_SUPPORT ==STD_ON)
void BLUpdater_PduRIfTxConfirmation(PduIdType TxPduId)
{
    DBG_BLUPDATER_PDURIFTXCONFIRMATION_ENTRY(TxPduId);

    OSC_PARAM_UNUSED(TxPduId);

    DBG_BLUPDATER_PDURIFTXCONFIRMATION_EXIT();
}
#endif
/*-----------------------------{end BLUpdater_PduRIfTxConfirmation}-----------------------------------------------*/

/*-----------------------------{BLUpdater_PduRIfRxIndication}-----------------------------------------------*/
#if (BLU_COMMUNICATION_SUPPORT ==STD_ON)
void BLUpdater_PduRIfRxIndication(PduIdType RxPduId, P2VAR(PduInfoType, AUTOMATIC, PDUR_APPL_DATA) PduInfoPtr)
{
    DBG_BLUPDATER_PDURIFRXINDICATION_ENTRY(RxPduId,PduInfoPtr);

    OSC_PARAM_UNUSED(RxPduId);
    OSC_PARAM_UNUSED(PduInfoPtr);

    DBG_BLUPDATER_PDURIFRXINDICATION_EXIT();
}
#endif
/*-----------------------------{end BLUpdater_PduRIfRxIndication}-----------------------------------------------*/
