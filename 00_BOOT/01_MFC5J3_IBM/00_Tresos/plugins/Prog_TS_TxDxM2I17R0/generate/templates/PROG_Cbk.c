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
/*%%  |   &&&&&   &&&&&             |  %%  Module version: 2.17.0 BL-3.X */
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
#include "PROG_Hsm.h"
#include "PROG_HsmPROG.h"
#include "board.h"
[!AUTOSPACING!]
/*=============================== IMPLEMENTATION ================================*/
/*                                                                               */
[!IF "node:exists(as:modconf('ProgJLR')) and as:modconf('ProgJLR')/General/PROG_JLR_VARIANT='PBL'
        or node:exists(as:modconf('ProgGM')) or node:exists(as:modconf('ProgFCA')) or node:exists(as:modconf('ProgVCC'))
        or node:exists(as:modconf('ProgVAG')) or node:exists(as:modconf('ProgDAG'))
        or node:exists(as:modconf('ProgOEMInd'))"!]


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
    return 0U;
}
[!ENDIF!]

[!IF "node:exists(as:modconf('ProgJLR')) and as:modconf('ProgJLR')/General/PROG_JLR_VARIANT='PBL'
    or node:exists(as:modconf('ProgGM')) or node:exists(as:modconf('ProgFCA'))
    or node:exists(as:modconf('ProgVAG')) or node:exists(as:modconf('ProgDAG'))
    or node:exists(as:modconf('ProgOEMInd'))"!]
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

}

[!ENDIF!]

/** \brief Callback that shall disable ECC if needed
 ** Callback is called: When Bootloader perform read access on Flash that can be
 **                     unprogrammed and can cause ECC error
 **
 ** Callback shall implement: If needed, disabling of ECC check
 **                           Hardware specific)
 **/
void PROG_DisableECCCheck(void)
{

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

}

[!IF "Decryption/Enable_Decryption = 'true'"!]
/** \brief Callback that shall request data decryption before writing them to memory
 ** Callback is called: receiving a TransferData before the decompression (if activated)
 **
 ** Callback shall implement: If needed, it shall decrypt the received data according to the EncryptingMethod.
 **
 ** \param[in] ubEncryptionMethod Encrypting method  indicator (from RequestDownload dataFormatIdentifier field)
 ** \param[in,out] pubData received data pointer (points to the encrypted data and callback implementation shall copy decrypted data at the same location than the encrypted one.)
 ** \param[in] DataLength received data length
 **
 ** \return Result of the decryption
 ** \retval PROG_E_OK Decryption finish successfully
 ** \retval PROG_E_NOT_OK Error happened during decryption
 **/
tProgStatus PROG_CustomDecryptData(u8 ubEncryptionMethod, u8 * pubData, u16 DataLength)
{
    OSC_PARAM_UNUSED(ubEncryptionMethod);
    OSC_PARAM_UNUSED(pubData);
    OSC_PARAM_UNUSED(DataLength);

    return PROG_E_OK;
}
[!ENDIF!]

[!IF "(node:exists(as:modconf('ProgJLR'))
    and (as:modconf('ProgJLR')/General/PROG_JLR_VARIANT='PBL' or as:modconf('ProgJLR')/General/PROG_JLR_VARIANT='SBL'))
    or node:exists(as:modconf('ProgFCA')) or node:exists(as:modconf('ProgVAG')) or (node:exists(as:modconf('ProgOEMInd'))
    and (./OemInd/Application_Validity_Algo='Custom'))
    or node:exists(as:modconf('ProgDAG'))"!]

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
    return FALSE;
}
[!ENDIF!]

[!IF "(node:exists(as:modconf('ProgJLR'))
    and (as:modconf('ProgJLR')/General/PROG_JLR_VARIANT='PBL' or as:modconf(ProgJLR)/General/PROG_JLR_VARIANT='SBL'))"!]
/** \brief Callback verifying the application is correctly downloaded and setting the application validity marker
 **
 ** Callback is called: on CheckApplicationValidation routine at the end of the programming sequence.
 **
 ** Callback shall implement: verification that each segment is fully programmed and setting of
 ** the validity marker if necessary. It then returns the status of the check.
 **
 ** \return Result of check
 ** \retval TRUE Application is valid
 ** \retval FALSE Application is not valid or not present
 **/
tProgCompleteStatus PROG_VerifySectionCrc(void)
{
    return 0U;
}
[!ENDIF!]

[!IF "node:exists(as:modconf('ProgJLR')) and as:modconf('ProgJLR')/General/PROG_JLR_VARIANT='SBL'
    or (node:exists(as:modconf('ProgOEMInd')) and (./OemInd/Application_Validity_Algo='Custom') and (./OemInd/Erase_Mode != 'All'))
    or (node:exists(as:modconf('ProgFCA')) and as:modconf('ProgFCA')/General/PROG_FCA_VARIANT='Atlantis_Mid')"!]
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
    OSC_PARAM_UNUSED(ulStartAddress);
    OSC_PARAM_UNUSED(ulEraseLength);
    OSC_PARAM_UNUSED(ErrorCode);

    return PROG_E_OK;
}
[!ENDIF!]

[!IF "node:exists(as:modconf('ProgVAG')) or node:exists(as:modconf('ProgDAG')) or
    (node:exists(as:modconf('ProgOEMInd')) and (./OemInd/Erase_Mode = 'All')) or
    (node:exists(as:modconf('ProgFCA')) and as:modconf('ProgFCA')/General/PROG_FCA_VARIANT='Atlantis_High')"!]
/** \brief API that invalidate the application marker
 **
 ** Callback is called: On Erase routine reception
 **
 ** Callback shall implement: 1- customer code that shall be executed before
 **                           performing an erasing of a logical block
 **
 **                           2- It shall invalidate the logical block that will be erased
 **                           to make sure no jump to the application will be done if an error occurred
 **                           and the application is not fully erased or reprogrammed
 **
 ** \param[in] ubBlockId The ID of the block that will be erased
 **
 ** \return Result application invalidation
 ** \retval PROG_E_OK Treatment finish successfully
 ** \retval PROG_E_NOT_OK Error happened during treatment
 **/
tProgStatus PROG_InvalidateSection_BlockID(u8 ubBlockId)
{
    OSC_PARAM_UNUSED(ubBlockId);

    return PROG_E_OK;
}
[!ENDIF!]


/** \brief Called before Bootloader perform a jump to application
 **
 ** Callback is called: Before jumping to Application
 **
 **  Callback shall implement: customer code that shall be executed before
 **  jumping to application
 **/
void PROG_SwitchApplicationModeInd(void)
{

}

[!IF "(node:exists(as:modconf('ProgGM')) and (as:modconf('Prog')/Segments/*/Partition_Type='PROG_HSM_PARTITION'))"!]
/** \brief  Request to HSM Processor for Update
 **
 ** Callback is called: To Send Request to HSM Processor for Update
 **
 ** Callback shall implement: the reading of status to check if the HSM Processor allowed the Update
 **
 ** \return Result
 ** \retval PROG_E_OK HSM Processor Update Allowed
 ** \retval PROG_E_NOT_OK HSM Processor Update Not Allowed
 **/
tProgStatus PROG_HSMRequestUpdate(void)
{
    return PROG_E_OK;
}
[!ENDIF!]

[!IF "(node:exists(as:modconf('ProgGM')) and (as:modconf('Prog')/Segments/*/Partition_Type='PROG_HSM_PARTITION'))"!]
/** \brief  Request to HSM Processor for Update
 **
 ** Callback is called: To transfer Data from buffer to HSM Processor
 **
 ** Callback shall implement: the reading of status to check if the HSM Processor Read Data From buffer
 **
 ** \return Result
 ** \retval PROG_E_OK Read Data From buffer by HSM Processor succeeded
 ** \retval PROG_E_NOT_OK Read Data From buffer by HSM Processor Failed
 ** \retval PROG_E_BUSY HSM Read Data From buffer by HSM Processor InProgress
 **/
tProgStatus Prog_HSMTransferData(u8* paubHsmBuffer,u16 uwHsmBufferLength, u16* uwHsmPEC)
{
	OSC_PARAM_UNUSED(paubHsmBuffer);
	OSC_PARAM_UNUSED(uwHsmBufferLength);
	OSC_PARAM_UNUSED(uwHsmPEC);
    return PROG_E_OK;
}
[!ENDIF!]

[!IF "(node:exists(as:modconf('ProgGM')) and (as:modconf('Prog')/Segments/*/Partition_Type='PROG_HSM_PARTITION'))"!]
/** \brief  Request to HSM Processor for Update
 **
 ** Callback is called: To Inform HSM Processor with Last of Data received
 **
 ** Callback shall implement: the reading of status to check if the HSM Processor Received last data
 **
 ** \return Result
 ** \retval PROG_PEC_NO_ERROR HSM Processor Received the last Data
 ** \retval ERROR_CODE HSM Processor Update Failed
 **/
tProgPECError PROG_HSMLastDataReceived(void)
{
    return PROG_E_OK;
}
[!ENDIF!]

[!IF "node:exists(as:modconf('ProgGM'))"!]
/** \brief Callback retrieving the Key NBID value stored in memory
 **
 ** Callback is called: during reprogramming process to get the key NBID of the current
 **                     application stored in NVM.
 **
 ** It will be used to know if the new download application can be accepted or not
 **
 ** Callback shall implement: reading from non volatile memory of the Key NBID
 **                           value
 **
 ** \return Key NBID value on 16 bits
 **/
u16 PROG_GetKeyNBIDValue(void)
{
    return 0x0000U;
}
[!ENDIF!]
[!IF "node:exists(as:modconf('ProgGM'))"!]
/** \brief Callback retrieving the NBID value store in memory
 **
 ** Callback is called: during reprogramming process to get the NBID of the current
 **                     application stored in NVM.
 **
 ** It will be used to know if the new download application can be accepted or not
 **
 ** Callback shall implement: reading from non volatile memory of the NBID
 **                           value
 **
 ** \return NBID value on 16 bits
 **/
u16 PROG_GetNBIDValue(void)
{
    return 0x0000U;
}
[!ENDIF!]
[!IF "node:exists(as:modconf('ProgGM'))"!]
/** \brief Retrieve the Key NBID value store in memory
 **
 ** Callback is called: during reprogramming process to update the key NBID
 **                     of the downloaded application stored in NVM.
 **
 ** Callback shall implement: Writting in non volatile memory of the Key NBID
 **                          value
 **
 ** \param[in] uwKeyNBID New value of the Key NBID to be store in memory
 **
 **/
void PROG_SetKeyNBIDValue(u16 uwKeyNBID)
{
    OSC_PARAM_UNUSED(uwKeyNBID);
}
[!ENDIF!]
[!IF "node:exists(as:modconf('ProgGM'))"!]
/** \brief Retrieve the NBID value store in memory
 **
 ** Callback is called: during reprogramming process to update the NBID
 **                     of the downloaded application stored in NVM.
 **
 ** Callback shall implement: Writting in non volatile memory of the NBID
 **                          value
 **
 ** \param[in] uwNBID New value of the NBID to be store in memory
 **
 **/
void PROG_SetNBIDValue(u16 uwNBID)
{
    OSC_PARAM_UNUSED(uwNBID);
}
[!ENDIF!]
[!IF "node:exists(as:modconf('ProgGM'))"!]
/** \brief Set the SBI flag value in secure memory
**
** Callback is called: during startup to update the SBI flag
**                     for the SBA ticket stored in Secure RAM.
**
** Callback shall implement: Writing in secure volatile memory of the SBI flag
**                          value
**
** \param[in] ubSBI New value of the SBI flag to be stored in memory
**
**/
void PROG_SetSBIFlagValue(u8 ubSBI)
{
   OSC_PARAM_UNUSED(ubSBI);
}
/** \brief Retrieve the SBI flag value stored in memory
**
** Callback is called: during reprogrammimg process to update the SBI flag
**                     for the SBA ticket stored in Secure RAM.
**
** Callback shall implement: Reading in secure volatile memory of the SBI flag
**                          value
**
** \return SBI flag value on 8 bits
**
**/
u8 PROG_GetSBIFlagValue(void)
{
  return 0x00;
}
[!ENDIF!]
[!IF "not(node:exists(as:modconf('ProgVCC'))) and General/Dsc_Prog_Response = 'true'"!]
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
[!ENDIF!]

[!IF "node:exists(as:modconf('ProgGM'))"!]
/** \brief Copy the SBA ticket to the provided RAM buffer
 **
 ** Callback is called: On Bootloader startup during SBA check
 **
 ** Callback shall implement: the reading from non volatile memory of the SBA
 **                           ticket (822 bytes long, starting with the data
 **                          type)
 **
 ** \param[out] pubRamBuffer pointer to a RAM buffer where to copy the SBA ticket
 **
 ** \return Result
 ** \retval PROG_E_OK Copy ok
 ** \retval PROG_E_NOT_OK Copy failed
 **/
tProgStatus PROG_CopySBATicket(u8 * pubRamBuffer)
{
    OSC_PARAM_UNUSED(pubRamBuffer);

    return PROG_E_OK;
}

/** \brief get additional programming conditional flags
 **
 ** This API is called during the processing of the check programming dependencies routine
 **
 ** \param[out] pubFlag pointer to a variable to get the additional programming conditional flag
 **
 ** \return void
 **/
void Prog_CustomGetAdditionalProgrammingConditionalFlags(u8 * pubFlag)
{
    *pubFlag = 0x0;
}
/*------------------------{end Prog_CustomGetAdditionalProgrammingConditionalFlags}--------------------------*/


/** \brief get the ecu internal programming flags
 **
 ** This API is called during the processing of the check programming dependencies routine
 **
 ** \param[out] pubFlag pointer to a variable to get the ecu internal programming flags
 **
 ** \return void
 **/
void Prog_CustomGetProgrammingConditionsFlag(u8 * pubFlag)
{
    *pubFlag = 0x1;
}
/*------------------------{end Prog_CustomGetProgrammingConditionsFlag}--------------------------*/

/** \brief get the programming tolerant conditions flag
 **
 ** This API is called during the processing of the check programming dependencies routine
 **
 ** \param[out] pubFlag pointer to a variable to get the programming tolerant conditions flag
 **
 ** \return void
 **/
void Prog_CustomGetProgrammingTolerantConditionsFlag(u8 * pubFlag)
{
    *pubFlag = 0x1;
}
/*------------------------{end Prog_CustomGetProgrammingTolerantConditionsFlag}--------------------------*/

/** \brief get the programming conditions flag
 **
 ** This API is called during the processing of the check programming dependencies routine
 **
 ** \param[out] pubFlag pointer to a variable to get the programming conditions flag
 **
 ** \return void
 **/
void Prog_CustomGetECUInternalProgrammingFlag(u8 * pubFlag)
{
    *pubFlag = 0x1;
}
/*------------------------{end Prog_CustomGetECUInternalProgrammingFlag}--------------------------*/
[!ENDIF!]
[!IF "node:exists(as:modconf('Uds'))
    and  ( (node:exists(as:modconf('ProgOEMInd')) and ./OemInd/Application_Validity_Algo='Custom')
    or not(node:exists(as:modconf('ProgOEMInd'))) )"!]
[!VAR "FINGERPRINT_USE" = "0"!]
    [!LOOP " as:modconf('Uds')/Service_DID/*"!]
        [!IF "Callback = 'PROG_WriteFingerprint'"!]
            [!VAR "FINGERPRINT_USE" = "1"!]
        [!ENDIF!]
    [!ENDLOOP!]
    [!IF "$FINGERPRINT_USE = 1"!]
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
    tProgStatus eProgStatus = PROG_E_OK;
    OSC_PARAM_UNUSED(pubRamBuffer);
    return eProgStatus;
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
    tProgStatus eProgStatus = PROG_E_OK;
    return eProgStatus;
}
    [!ENDIF!]
[!ENDIF!]

[!IF "(node:exists(as:modconf('ProgFCA')) and as:modconf('ProgFCA')/General/PROG_FCA_VARIANT='Atlantis_Mid')"!]
/** \brief Initialization of the Custom Checksum calculation
 **
 ** Callback is called: On start of a checksum calculation
 **
 ** Callback shall implement: Initialization of checksum calculation.
 **                          Checksum calculation is customer specific (Checksum,
 **                          CRC16,...)
 **/
void PROG_CustomStartChecksumCalc(void)
{
}
[!ENDIF!]
[!IF "(node:exists(as:modconf('ProgFCA')) and as:modconf('ProgFCA')/General/PROG_FCA_VARIANT='Atlantis_Mid')"!]

/** \brief Update (transfer data blocks) for Custom Checksum calculation
 **
 ** Callback is called: After a PROG_CustomStartChecksumCalc call and when data to be
 **                     used for checksum calculation have been read from Flash memory
 **
 ** Callback shall implement: Checksum calculation.
 **                           Checksum calculation is customer specific (Checksum,
 **                          CRC16,...)
 **
 ** \param[in] pubData pointer to the data to compute
 ** \param[in] ulDataSize Length of data to compute
 **
 **/
void PROG_CustomUpdateChecksumCalc(u8* pubData, u32 ulDataSize)
{
    OSC_PARAM_UNUSED(pubData);
    OSC_PARAM_UNUSED(ulDataSize);
}
[!ENDIF!]
[!IF "(node:exists(as:modconf('ProgFCA')) and as:modconf('ProgFCA')/General/PROG_FCA_VARIANT='Atlantis_Mid')"!]

/** \brief Get result of checksum calculation
 **
 ** Callback is called: To get result of a checksum calculation, after
 **                    PROG_CustomStartChecksumCalc/PROG_CustomUpdateChecksumCalc
 **                    calls
 **
 ** Callback shall implement: Provide result of checksum calculation.
 **                           Checksum calculation is customer specific (Checksum,
 **                           CRC16,...)
 **
 ** \param[out] puwCalculatedCks pointer to calculated checksum
 **
 ** \return state
 ** \retval PROG_E_OK Calculation finished successfully
 ** \retval PROG_E_BUSY Calculation in progress
 ** \retval PROG_E_NOT_OK Calculation finished on error
 **
 **/
tProgStatus PROG_CustomChecksumCalc(u16* puwCalculatedCks)
{
    tProgStatus eProgStatus = PROG_E_OK;
    OSC_PARAM_UNUSED(puwCalculatedCks);
    return eProgStatus;
}
[!ENDIF!]
[!IF "(node:exists(as:modconf('ProgFCA')) and as:modconf('ProgFCA')/General/PROG_FCA_VARIANT='Atlantis_Mid')"!]

/** \brief Set the Application Validity
 **
 ** Callback is called: After Checksum computation has succeeded
 **
 ** Callback shall implement: Update the application validity flag as valid
 **                           (additional customer coherency check can be required
 **                           to conclude on application validity)
 **
 ** \param[in] ulAddress Start address of sector on which the CRC has succeeded
 ** \param[in] ulEndAddress End address of sector on which the CRC has succeeded
 **
 **/
void PROG_CustomSetAppValidity(u32 ulAddress, u32 ulEndAddress)
{
    OSC_PARAM_UNUSED(ulAddress);
    OSC_PARAM_UNUSED(ulEndAddress);
}
[!ENDIF!]
[!IF "(node:exists(as:modconf('ProgFCA')) and as:modconf('ProgFCA')/General/PROG_FCA_VARIANT='Atlantis_Mid')"!]

/** \brief Callback storing the programming status structure
 **
 ** Callback is called: After Programming status update
 **
 ** Callback shall implement: Storage of Programming status in RAM. The storage in
 **                           non-volatile memory shall be done before the ECU is
 **
 ** \param[in] ulProgrammingStatus Programming Status (4 Bytes)
 **
 **/
void PROG_CustomWriteProgStatus(u32 ulProgrammingStatus)
{
    OSC_PARAM_UNUSED(ulProgrammingStatus);
}
[!ENDIF!]
[!IF "(node:exists(as:modconf('ProgVAG'))) or (node:exists(as:modconf('ProgDAG'))) or (as:modconf('Prog')/General/Transmit_Response_Before_Reset = 'false')"!]
/** \brief Store the reset cause and the need of response
 **
 ** Callback is called: Before Bootloader perform a reset to set reset cause
 **                     (UDS request that has caused the reset).
 **
 ** Callback shall implement: storage of the reset cause (UDS request)
 **
 ** \param[in] ubResetCause the reset cause
 ** \param[in] ubSendResp the need of response according to suppressPositiveResponse bit
 **            from the request
 **
 **/
void PROG_CustomStoreResetCause(tProgResCause ubResetCause, tProgBoolean ubSendResp)
{
    OSC_PARAM_UNUSED(ubResetCause);
    OSC_PARAM_UNUSED(ubSendResp);
}
/** \brief Restore the reset cause and the need of response
 **
 ** Callback is called: At Bootloader startup to get the UDS request that has caused
 **                    the reset.
 **
 ** Callback shall implement: provide the cause of the reset (UDS request) that has been
 **                           set by application or Bootloader (by call to
 **                           PROG_CustomStoreResetCause)
 **
 ** \param[out] pubResetCause pointer to the reset cause
 ** \param[out] pubSendResp Provide information if positive response shall be sent
 **             depending of the value of the suppressPositiveResponse bit from the request
 **             TRUE: response shall be sent / FALSE: no response shall be sent
 **
 **/
void PROG_CustomGetResetCause(tProgResCause* pubResetCause, tProgBoolean* pubSendResp)
{
    OSC_PARAM_UNUSED(pubResetCause);
    OSC_PARAM_UNUSED(pubSendResp);
}
[!ENDIF!]
[!IF "(node:exists(as:modconf('ProgVAG'))) or (node:exists(as:modconf('ProgDAG')))
    or (node:exists(as:modconf('ProgOEMInd')))"!]
[!IF "General/Check_Programming_PreConditions = 'true'"!]
/** \brief Check if all the programming pre-conditions are met
 **
 ** Callback is called: On Programming precondition check
 **
 ** Callback shall implement: programming precondition check. Inform Bootloader
 **                           if the ECU is in a state where programming can be
 **                           performed. If condition are not correct programming
 **                           will be rejected by Bootloader and negative response
 **                           will be sent on the network.
 **
 ** \return state
 ** \retval PROG_E_OK All the programming pre-conditions are met
 ** \retval PROG_E_NOT_OK At least one programming pre-condition is NOT met
 **
 **/
tProgStatus PROG_CustCheckProgPrecond(void)
{
    tProgStatus eProgStatus = PROG_E_OK;
    return eProgStatus;
}
[!ENDIF!]
[!ENDIF!]
[!IF "(node:exists(as:modconf('ProgFCA')) and as:modconf('ProgFCA')/General/PROG_FCA_VARIANT='Atlantis_High')"!]
[!IF "General/Check_Programming_PreConditions = 'true'"!]
/** \brief Check if all the programming pre-conditions are met
 **
 ** Callback is called: On Programming precondition check
 **
 ** Callback shall implement: programming precondition check. Inform Bootloader
 **                           if the ECU is in a state where programming can be
 **                           performed. If condition are not correct programming
 **                           will be rejected by Bootloader and negative response
 **                           will be sent on the network.
 **
 ** \param[out] pubProgrammingConditionNumber Number of failed Programming Conditions
 **                                          that shall be returned in the response
 **
 ** \param[out] paubConditionList List of failed conditions
 **
 **
 **/
void PROG_CustCheckProgPrecondList(u8 * pubProgrammingConditionNumber, u8 * paubConditionList)
{
    *pubProgrammingConditionNumber = 0;
    OSC_PARAM_UNUSED(paubConditionList);
    /*
        In case of condition failure set pubProgrammingConditionNumber to failure number
        and list failure in paubConditionList: e.g paubConditionList[0]=0x07
    */
}
[!ENDIF!]
[!ENDIF!]
[!IF "node:exists(as:modconf('ProgVAG')) or node:exists(as:modconf('ProgDAG')) or node:exists(as:modconf('ProgVCC'))
        or (node:exists(as:modconf('ProgFCA')) and as:modconf('ProgFCA')/General/PROG_FCA_VARIANT='Atlantis_High')
        or (node:exists(as:modconf('ProgOEMInd')) and (./OemInd/Application_Validity_Algo='Custom'))"!]
/** \brief Callback called after comparing the expected checksum or signature and the calculated one.
 **
 ** Callback is called: After a successful or unsuccessful download verification
 **
 ** Callback shall implement: update of the logical block validity status
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
    OSC_PARAM_UNUSED(ubLogicalBlockId);
    OSC_PARAM_UNUSED(ubLogicalSegmentId);
    OSC_PARAM_UNUSED(ubCompareSuccess);

    return PROG_E_OK;
}
[!ENDIF!]

[!IF "(node:exists(as:modconf('ProgVAG')) and General/Expected_Crc_Location = 'Application')
    or (node:exists(as:modconf('ProgDAG')) and General/Expected_Crc_Location = 'Application')"!]

/** \brief This API is called in order to get the expected CRC corresponding to the required logical block,
 ** if this one is not found in the request.
 **
 ** Callback is called: During CRC verification
 **
 ** Callback shall implement: extract from downloaded software the expected CRC value
 **
 ** \param[in] ubLogicalBlockId The logical block on which corresponding CRC is required
 ** \param[out] pulExpectedCrc The expected CRC
 **
 **/
void PROG_CustomGetExpectedCrc(u8 ubLogicalBlockId, u32* pulExpectedCrc)
{
    OSC_PARAM_UNUSED(ubLogicalBlockId);
    OSC_PARAM_UNUSED(pulExpectedCrc);
}
[!ENDIF!]

[!IF "(node:exists(as:modconf('ProgVAG')) )
    or (node:exists(as:modconf('ProgDAG')))
    or (node:exists(as:modconf('ProgOEMInd')))"!]
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
[!ENDIF!]

[!IF "DownloadVerification/CVN_Verification = 'true'"!]
/** \brief Callback for CVN check
 **
 ** Callback is called: on reception of verify partial sw
 **
 ** Callback shall implement: the check of CVN value
 **
 ** \param[in] ubLogicalBlockId Block identifier value
 ** \param[in] paubExpectedCvn CVN value
 **
 ** \return state
 ** \retval PROG_E_OK Treatment finish successfully
 ** \retval PROG_E_BUSY Treatment is in progress
 ** \retval PROG_E_NOT_OK Error happened during treatment
 **/
tProgStatus PROG_CustomCvnVerification(u8 ubLogicalBlockId, const u8* paubExpectedCvn)
{
    OSC_PARAM_UNUSED(ubLogicalBlockId);
    OSC_PARAM_UNUSED(paubExpectedCvn);
    return PROG_E_OK;
}

/** \brief Callback for CVN check
 **
 ** Callback is called: on reception of verify partial sw
 **
 ** Callback shall implement: the return of CVN status check updated in the verification callback
 **
 ** \return state
 ** \retval PROG_E_OK Treatment finish successfully
 ** \retval PROG_E_BUSY Treatment is in progress
 ** \retval PROG_E_NOT_OK Error happened during treatment
 **/
tProgStatus PROG_CustomCvnVerificationStatus(void)
{
    return PROG_E_OK;
}
[!ENDIF!]

[!IF "(node:exists(as:modconf('ProgVAG')))
    or (node:exists(as:modconf('ProgDAG')))
    or (node:exists(as:modconf('ProgFCA')) and as:modconf('ProgFCA')/General/PROG_FCA_VARIANT='Atlantis_High')
    or (node:exists(as:modconf('ProgOEMInd')))"!]
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
    OSC_PARAM_UNUSED(eCohChkResult);
    return PROG_E_OK;
}
[!ENDIF!]

[!IF "node:exists(as:modconf('Uds'))"!]
[!VAR "COHERENCY_PRE_CHECK_USE" = "0"!]
    [!LOOP " as:modconf('Uds')/Routine_Control/*"!]
        [!IF "Callback = 'PROG_CoherencyPreCheck'"!]
            [!VAR "COHERENCY_PRE_CHECK_USE" = "1"!]
        [!ENDIF!]
    [!ENDLOOP!]
    [!IF "$COHERENCY_PRE_CHECK_USE = 1"!]
/** \brief This API is called to perform the Pre Check Coherency on data passed in parameter
 **
 ** Callback is called: on the reception of the Pre Check Programming Dependencies Routine
 **
 ** Callback shall implement the algorithm performing the Pre Check Programming Dependencies.
 **
 ** \param[in]  paubUdsData Pointer to the data on which Pre Check shall be performed
 ** \param[in]  puwlen      Number of bytes of the data
 ** \param[out] eUdsStatus  The result of the pre check coherency.
 **             Can be: UDS_ACK, UDS_NRC_XX (XX can take the values defined in ISO 14429 -  Annex A - Negative Response codes)
 **
 ** \return Coherency Pre Check Status Record
 ** \retval 0-No Failure
 ** \retval 1-Internal Error
 ** \retval 2-Error HW-SW
 ** \retval 3-Error SW-SW
 **/
tProgCohPreChkResult PROG_CustomComputeCoherencyPreCheck(u8* paubUdsData, u16 puwlen, tUdsStatus* eUdsStatus)
{
    OSC_PARAM_UNUSED(paubUdsData);
    OSC_PARAM_UNUSED(puwlen);
    OSC_PARAM_UNUSED(eUdsStatus);
    return PROG_E_COHPRECHK_CORRECT;
}
    [!ENDIF!]
[!ENDIF!]


[!IF "node:exists(as:modconf('ProgGM'))"!]
[!IF "GM/EcuId_Source = 'User_Callback'"!]
/** \brief API to be called in order to get the ECU Id from a custom location
 **
 ** This API is called to get the ECU ID during the TransferData. The implementation of this API shall permit
 ** to give the EcuId to the bootloader from a custom location (Flash, RAM, custom configuration, etc.).
 **
 ** \param[out] paubEcuId Pointer to ECU Id
 **
 **/
/*---------------------------{PROG_CustomGetEcuId}-----------------------------*/
void PROG_CustomGetEcuId(u8* paubEcuId)
{
    OSC_PARAM_UNUSED(paubEcuId);
}
/*------------------------{end PROG_CustomGetEcuId}--------------------------*/
[!ENDIF!]
[!ENDIF!]

[!IF "(node:exists(as:modconf('ProgVAG'))
    or (node:exists(as:modconf('ProgDAG')))
    or ( (node:exists(as:modconf('ProgFCA'))) and (as:modconf('ProgFCA')/General/PROG_FCA_VARIANT='Atlantis_High')) )"!]
/** \brief API to get the stored value of the programming counter.
 **
 ** \param[in] ubBlockId BlockID
 **
 ** Callback is called: Before erasing the block
 **
 ** Callback shall implement: return the current value of the programming counter
 **
 ** \return programming counter on 16 bits
 **/
/*---------------------------{PROG_CustomGetProgCounter}-----------------------------*/
u16 PROG_CustomGetProgCounter(u8 ubBlockId)
{
    OSC_PARAM_UNUSED(ubBlockId);
    return 0x0000U;
}
/*------------------------{end PROG_CustomGetProgCounter}--------------------------*/


/** \brief API to increment the programming counter for the erased logical block.
 **
 ** This API is called to increment the programming counter of the block.
 ** The maximum value shall be limited at 0xFFFF and it shall not overflow.
 **
 ** \param[in] ubBlockId BlockID
 **
 ** Callback is called: Before erasing the block
 **
 ** Callback shall implement: increment the current value of the programming counter
 **
 ** \return Result of incrementation operation
 ** \retval PROG_E_OK incrementation operation finished successfully
 ** \retval PROG_E_NOT_OK incrementation operation error happened
 **
 **/
/*---------------------------{PROG_CustomIncrementProgCounter}-----------------------------*/
tProgStatus PROG_CustomIncrementProgCounter(u8 ubBlockId)
{
    OSC_PARAM_UNUSED(ubBlockId);
    return PROG_E_OK;
}
/*------------------------{end PROG_CustomIncrementProgCounter}--------------------------*/
[!ENDIF!]

[!IF "node:exists(as:modconf('Uds'))"!]
    [!VAR "PARTIAL_VERIFY_CRC_USE" = "0"!]
    [!LOOP " as:modconf('Uds')/Routine_Control/*"!]
        [!IF "Callback = 'PROG_PartialVerificationCrc'"!]
            [!VAR "PARTIAL_VERIFY_CRC_USE" = "1"!]
        [!ENDIF!]
    [!ENDLOOP!]
    [!IF "$PARTIAL_VERIFY_CRC_USE = 1"!]

/** \brief This API allows the integrator to store the informations regarding the partial software download for a specific blockId.
        The callback is called after each successful CheckMemory routine processing.
 **
 ** \param[in] ubBlockId block Id for which the information is stored
 ** \param[out] aulSegProgSize pointer to an array containing the size of programmed data for each segment in the block
 ** \param[out] ubSegNbr number of the segments programmed
 **
 **/
/*---------------------------{PROG_CustomGetPartProgSegList}-----------------------------*/
void PROG_CustomGetPartProgSegList(u8 ubBlockId,u32* aulSegProgSize,u8* ubSegNbr)
{
    OSC_PARAM_UNUSED(ubBlockId);
    OSC_PARAM_UNUSED(aulSegProgSize);
    OSC_PARAM_UNUSED(ubSegNbr);
}
/*------------------------{end PROG_CustomGetPartProgSegList}--------------------------*/

/** \brief This API allows the integrator to store the informations regarding the partial software download for a specific blockId.
        The callback is called after each successful CheckMemory routine processing.
 **
 ** \param[in] ubBlockId block Id for which the information is stored
 ** \param[in] aulSegProgSize pointer to an array containing the size of programmed data for each segment in the block
 ** \param[in] ubSegNbr number of the segments programmed
 **
 **/
/*---------------------------{PROG_CustomSetPartProgSegList}-----------------------------*/
void PROG_CustomSetPartProgSegList(u8 ubBlockId,u32* aulSegProgSize,u8* ubSegNbr)
{
    OSC_PARAM_UNUSED(ubBlockId);
    OSC_PARAM_UNUSED(aulSegProgSize);
    OSC_PARAM_UNUSED(ubSegNbr);
}
/*------------------------{end PROG_CustomSetPartProgSegList}--------------------------*/

/** \brief This API allows the integrator to clear the informations stored in the non-volatile memory regarding the partial software download for a specific block.
        The callback is called at every block erase
 **
 ** \param[in] ubBlockId block Id for which the information is stored
 **
 **/
/*---------------------------{PROG_CustomClearPartProgSegList}-----------------------------*/
void PROG_CustomClearPartProgSegList(u8 ubBlockId)
{
    OSC_PARAM_UNUSED(ubBlockId);
}
/*------------------------{end PROG_CustomClearPartProgSegList}--------------------------*/

    [!ENDIF!]
[!ENDIF!]

[!IF "node:exists(as:modconf('Csm'))"!]
[!IF "(node:exists(as:modconf('ProgGM'))
      or node:exists(as:modconf('ProgVCC'))
    or (node:exists(as:modconf('ProgDAG')))
    or (node:exists(as:modconf('ProgFCA')) and as:modconf('ProgFCA')/General/PROG_FCA_VARIANT='Atlantis_High')
    or (node:exists(as:modconf('ProgVAG')))
    or (node:exists(as:modconf('ProgOEMInd')))
    )"!]
[!IF "(node:exists(as:modconf('ProgGM'))
    or (node:exists(as:modconf('ProgDAG')))
    )"!]
/*Public Key:EC172B93AD5E563BF4932C70E1245034C35467EF2EFD4D64EBF819683467E2BF*/

const u32 m_ulPROGPublicExponent = 0UL;

const u8 m_aubPROGPublicModulus[32] =
    {
        0xEC, 0x17, 0x2B, 0x93, 0xAD, 0x5E, 0x56, 0x3B,
        0xF4, 0x93, 0x2C, 0x70, 0xE1, 0x24, 0x50, 0x34,
        0xC3, 0x54, 0x67, 0xEF, 0x2E, 0xFD, 0x4D, 0x64,
        0xEB, 0xF8, 0x19, 0x68, 0x34, 0x67, 0xE2, 0xBF,
    };

[!ENDIF!]

[!IF "((node:exists(as:modconf('ProgVAG')))
      or node:exists(as:modconf('ProgVCC'))
    or (node:exists(as:modconf('ProgOEMInd')))
    or (node:exists(as:modconf('ProgFCA')) and as:modconf('ProgFCA')/General/PROG_FCA_VARIANT='Atlantis_High')
    )"!]
/*Example for 3072 bit key:
Modulus: 9c213ea373631f572e5e46225b95a0f5ea8ab0a5ec7090a3b0181c5906dc22fd1bd73d11471242a2ed1824e601017f5b5354b92fdb43d4da00a82427d05366a4d552c40d69d200485d5d5db83cf523e61a834b40ccd401087fbb93d81dbed7b2ee2381a1241ac68f2afc02157ee0c73cc66c02a6c6eb2dc35145ae55d7708412a3410f204c492376d6315cedf253af91f31dcab34f72c206ad81e800509864fe9255d046ac25dbdf4954d2350324722e73c1f25d089f87542ad907fb37eceaefb330f4325e97f5eabc04096a8fabba978589e355445d9543274c1c38ff849ba8c2911f07030634c132ccaf4e4f57a5ad9244f5df0ee25af8ef2fc7b29fdf7cc18404e20efaaffa451ec41ab838d594906ff2cad52dcbd0e9a68ef7b06c253710e1318d09ad07012767a89124177df50d1684679e14306889d9a7ac5143d4861b7d6ae77992efa73e0aba9da0ad9a6888bc804dbd07bc26a8a5dfbd292a0efa96867fdb92e845c36e3433cf292e0e31662480257fcf466f7f65d814bb3e33992f
Public exponent: 00efabb9
*/

const u32 m_ulPROGPublicExponent = 0x00EFABB9UL;

const u8 m_aubPROGPublicModulus[384] =
    {
        0x9C, 0x21, 0x3E, 0xA3, 0x73, 0x63, 0x1F, 0x57,
        0x2E, 0x5E, 0x46, 0x22, 0x5B, 0x95, 0xA0, 0xF5,
        0xEA, 0x8A, 0xB0, 0xA5, 0xEC, 0x70, 0x90, 0xA3,
        0xB0, 0x18, 0x1C, 0x59, 0x06, 0xDC, 0x22, 0xFD,
        0x1B, 0xD7, 0x3D, 0x11, 0x47, 0x12, 0x42, 0xA2,
        0xED, 0x18, 0x24, 0xE6, 0x01, 0x01, 0x7F, 0x5B,
        0x53, 0x54, 0xB9, 0x2F, 0xDB, 0x43, 0xD4, 0xDA,
        0x00, 0xA8, 0x24, 0x27, 0xD0, 0x53, 0x66, 0xA4,
        0xD5, 0x52, 0xC4, 0x0D, 0x69, 0xD2, 0x00, 0x48,
        0x5D, 0x5D, 0x5D, 0xB8, 0x3C, 0xF5, 0x23, 0xE6,
        0x1A, 0x83, 0x4B, 0x40, 0xCC, 0xD4, 0x01, 0x08,
        0x7F, 0xBB, 0x93, 0xD8, 0x1D, 0xBE, 0xD7, 0xB2,
        0xEE, 0x23, 0x81, 0xA1, 0x24, 0x1A, 0xC6, 0x8F,
        0x2A, 0xFC, 0x02, 0x15, 0x7E, 0xE0, 0xC7, 0x3C,
        0xC6, 0x6C, 0x02, 0xA6, 0xC6, 0xEB, 0x2D, 0xC3,
        0x51, 0x45, 0xAE, 0x55, 0xD7, 0x70, 0x84, 0x12,
        0xA3, 0x41, 0x0F, 0x20, 0x4C, 0x49, 0x23, 0x76,
        0xD6, 0x31, 0x5C, 0xED, 0xF2, 0x53, 0xAF, 0x91,
        0xF3, 0x1D, 0xCA, 0xB3, 0x4F, 0x72, 0xC2, 0x06,
        0xAD, 0x81, 0xE8, 0x00, 0x50, 0x98, 0x64, 0xFE,
        0x92, 0x55, 0xD0, 0x46, 0xAC, 0x25, 0xDB, 0xDF,
        0x49, 0x54, 0xD2, 0x35, 0x03, 0x24, 0x72, 0x2E,
        0x73, 0xC1, 0xF2, 0x5D, 0x08, 0x9F, 0x87, 0x54,
        0x2A, 0xD9, 0x07, 0xFB, 0x37, 0xEC, 0xEA, 0xEF,
        0xB3, 0x30, 0xF4, 0x32, 0x5E, 0x97, 0xF5, 0xEA,
        0xBC, 0x04, 0x09, 0x6A, 0x8F, 0xAB, 0xBA, 0x97,
        0x85, 0x89, 0xE3, 0x55, 0x44, 0x5D, 0x95, 0x43,
        0x27, 0x4C, 0x1C, 0x38, 0xFF, 0x84, 0x9B, 0xA8,
        0xC2, 0x91, 0x1F, 0x07, 0x03, 0x06, 0x34, 0xC1,
        0x32, 0xCC, 0xAF, 0x4E, 0x4F, 0x57, 0xA5, 0xAD,
        0x92, 0x44, 0xF5, 0xDF, 0x0E, 0xE2, 0x5A, 0xF8,
        0xEF, 0x2F, 0xC7, 0xB2, 0x9F, 0xDF, 0x7C, 0xC1,
        0x84, 0x04, 0xE2, 0x0E, 0xFA, 0xAF, 0xFA, 0x45,
        0x1E, 0xC4, 0x1A, 0xB8, 0x38, 0xD5, 0x94, 0x90,
        0x6F, 0xF2, 0xCA, 0xD5, 0x2D, 0xCB, 0xD0, 0xE9,
        0xA6, 0x8E, 0xF7, 0xB0, 0x6C, 0x25, 0x37, 0x10,
        0xE1, 0x31, 0x8D, 0x09, 0xAD, 0x07, 0x01, 0x27,
        0x67, 0xA8, 0x91, 0x24, 0x17, 0x7D, 0xF5, 0x0D,
        0x16, 0x84, 0x67, 0x9E, 0x14, 0x30, 0x68, 0x89,
        0xD9, 0xA7, 0xAC, 0x51, 0x43, 0xD4, 0x86, 0x1B,
        0x7D, 0x6A, 0xE7, 0x79, 0x92, 0xEF, 0xA7, 0x3E,
        0x0A, 0xBA, 0x9D, 0xA0, 0xAD, 0x9A, 0x68, 0x88,
        0xBC, 0x80, 0x4D, 0xBD, 0x07, 0xBC, 0x26, 0xA8,
        0xA5, 0xDF, 0xBD, 0x29, 0x2A, 0x0E, 0xFA, 0x96,
        0x86, 0x7F, 0xDB, 0x92, 0xE8, 0x45, 0xC3, 0x6E,
        0x34, 0x33, 0xCF, 0x29, 0x2E, 0x0E, 0x31, 0x66,
        0x24, 0x80, 0x25, 0x7F, 0xCF, 0x46, 0x6F, 0x7F,
        0x65, 0xD8, 0x14, 0xBB, 0x3E, 0x33, 0x99, 0x2F,
    };
[!ENDIF!]

/** \brief Get the public key modulus and exponent when using asymmetric cryptography. Used in SA_InitCrypto
 **
 ** \param[out] paubPublicModulus Pointer to asymmetric cryptography public key modulus array
 ** \param[out] pulPublicExponent Pointer to asymmetric cryptography public key exponent
 **
 **/
/*---------------------------{PROG_CustomGetAsymPublicKey}-----------------------------*/
void PROG_CustomGetAsymPublicKey(const u8** paubPublicModulus, u32* pulPublicExponent)
{
    *paubPublicModulus = m_aubPROGPublicModulus;
    *pulPublicExponent = m_ulPROGPublicExponent;
}
/*------------------------{end PROG_CustomGetAsymPublicKey}--------------------------*/
[!ENDIF!]
[!ENDIF!]

[!IF "(as:modconf('BM')/Security/SecureBoot/SECURE_AUTHENTICATED_BOOT ='Authenticated') and
    (as:modconf('BM')/Security/SecureBoot/BOOT_VERIFICATION ='ON')"!]
/** \brief This API is called to get the computed Bootloader checksum stored in non-volatile memory
 **
 ** Callback is called: Before starting Bootloader to verify the computed checksum
 **
 ** Callback shall implement: get from non-volatile memory the Bootloader checksum and
 **                           copy it to the provided pointer
 **
 ** \param[out] pubComputedChecksum Pointer where to copy the checksum.
 **
 **/
void PROG_CustomGetComputedBootloaderChecksum(u8 * pubComputedChecksum)
{
    OSC_PARAM_UNUSED(pubComputedChecksum);
}

/** \brief This API is called to know if the stored Bootloader checksum is valid
 **
 ** Callback is called: Before reading the bootloader checksum
 **
 ** Callback shall implement: get from non-volatile memory the Bootloader checksum status
 **
 ** \return Validity status
 ** \retval PROG_E_OK Checksum is valid
 ** \retval PROG_E_NOT_OK Checksum is invalid
 **
 **/
tProgBoolean PROG_CustomIsValidBootloaderChecksum(void)
{
    return PROG_TRUE;
}
[!ENDIF!]

[!IF "((not((as:modconf('BM')/Security/SecureBoot/SECURE_AUTHENTICATED_BOOT = 'OFF') and (as:modconf('Prog')/Security/Secure_Checksum_computation = 'false'))) and
    (node:exists(as:modconf('ProgDAG')) or (node:exists(as:modconf('ProgFCA')) and as:modconf('ProgFCA')/General/PROG_FCA_VARIANT='Atlantis_High')))
    or ((as:modconf('Prog')/Security/Secure_Checksum_computation = 'true') and (node:exists(as:modconf('ProgVCC'))) and (as:modconf('ProgVCC')/General/PROG_VCC_VARIANT='SBL'))"!]
[!IF "((as:modconf('Prog')/General/Use_CSM_ASR430_DemoWrapper = 'false') and (contains(as:modconf('Prog')/Security/ProgCsmSecureConfigId, '/Csm/Csm/CsmMacGenerate/') =  'true')) or
((as:modconf('Prog')/General/Use_CSM_ASR430_DemoWrapper = 'true') and (node:exists(node:ref(node:ref(as:modconf('Prog')/Security/ProgCsmSecureConfigId)/CsmJobPrimitiveRef)/CsmMacGenerate)) )"!]
const u32 m_ulMacKeyKength = 0x00000010UL;

const u8 m_aubKeyData[16U] =
{
    0xEBU, 0xEBU, 0xEBU, 0xEBU,
    0xEBU, 0xEBU, 0xEBU, 0xEBU,
    0xEBU, 0xEBU, 0xEBU, 0xEBU,
    0xEBU, 0xEBU, 0xEBU, 0xEBU
};

void PROG_CustomGetMacKey(const u8** paubKeyData, u32* pulKeyLength)
{
    *paubKeyData   = m_aubKeyData;
    *pulKeyLength  = m_ulMacKeyKength;
}
[!ENDIF!]

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
[!ENDIF!]

[!IF "(as:modconf('BM')/Security/SecureBoot/SECURE_AUTHENTICATED_BOOT='Authenticated')"!]
/** \brief This API is called to set the Bootloader checksum as invalid
 **
 ** Callback is called: After Bootloader checksum computation, before updating
 ** the checksum.
 **
 ** Callback shall implement: Set in non-volatile memory the Bootloader checksum validity
 **                           flag with invalid value
 **
 **/
void PROG_CustomInvalidateBootloaderChecksum(void)
{

}

/** \brief This API is called to store the computed Bootloader checksum in non-volatile memory
 **
 ** Callback is called: After Bootloader checksum computation at Bootloader start
 **
 ** Callback shall implement: store in non-volatile memory the Bootloader checksum
 **
 ** \param[in] pubComputedChecksum Pointer to Bootloader checksum to store.
 **
 **/
void PROG_CustomSetBootloaderChecksum(u8 * pubComputedChecksum)
{
    OSC_PARAM_UNUSED(pubComputedChecksum);
}

/** \brief This API is called to set the Bootloader checksum as valid
 **
 ** Callback is called: After Bootloader checksum computation, after updating
 ** the checksum.
 **
 ** Callback shall implement: Set in non-volatile memory the Bootloader checksum validity
 **                           flag with valid value
 **
 **/
void PROG_CustomValidateBootloaderChecksum(void)
{

}
[!ENDIF!]


[!IF "(node:exists(as:modconf('ProgVAG')) or (node:exists(as:modconf('ProgDAG'))))"!]

    [!VAR "UPDATE_TP_PARAM_USED" = "0"!]
        [!IF "node:exists(as:modconf('Uds'))"!]
            [!LOOP " as:modconf('Uds')/Service_DID/*"!]
                [!IF "(DID = num:hextoint('0x010B') and (node:exists(as:modconf('ProgDAG')))) or
                    (DID = num:hextoint('0x0410') and (node:exists(as:modconf('ProgVAG'))))"!]
                    [!VAR "UPDATE_TP_PARAM_USED" = "1"!]
                [!ENDIF!]
            [!ENDLOOP!]
        [!ENDIF!]
    [!IF "$UPDATE_TP_PARAM_USED = 1"!]

/** \brief Get the TP Blocksize value
 **
 ** Callback is called:  On bootloader startup or on demand of reprogramming, in order to get the TP Blocksize value used in application
 **
 ** Callback shall implement: The get of the TP Blocksize value used in application. If no valid value is available PROG_E_NOT_OK shall be returned.
 **
 ** \param[in,out] ubTpBsValue Blocksize value
 **
 ** \return return Get TP value status
 ** \retval PROG_E_OK
 ** \retval PROG_E_NOT_OK
 **/
tProgStatus PROG_CustomGetTpBsValue(u8* ubTpBsValue)
{
    OSC_PARAM_UNUSED(ubTpBsValue);

    return PROG_E_OK;
}
    [!ENDIF!]
[!ENDIF!]

[!IF "(node:exists(as:modconf('ProgDAG')))"!]
[!VAR "UPDATE_TP_PARAM_USED" = "0"!]
    [!IF "node:exists(as:modconf('Uds'))"!]
        [!LOOP " as:modconf('Uds')/Service_DID/*"!]
            [!IF "DID = num:hextoint('0x010B')"!]
                [!VAR "UPDATE_TP_PARAM_USED" = "1"!]
            [!ENDIF!]
        [!ENDLOOP!]
    [!ENDIF!]
    [!IF "$UPDATE_TP_PARAM_USED = 1"!]
/** \brief Get the STmin value
 **
 ** Callback is called:  On bootloader startup or on demand of reprogramming, in order to get the STmin value used in application
 **
 ** Callback shall implement: The get of the STmin value used in application. If no valid value is available PROG_E_NOT_OK shall be returned.
 **
 ** \param[in,out] ubTpStminValue STmin value
 **
 ** \return Get STmin value status
 ** \retval PROG_E_OK
 ** \retval PROG_E_NOT_OK
 **/
tProgStatus PROG_CustomGetTpStminValue(u8* ubTpStminValue)
{
    OSC_PARAM_UNUSED(ubTpStminValue);

    return PROG_E_OK;
}
    [!ENDIF!]
[!ENDIF!]


/** \brief Notification of a download event
 **
 ** Callback is called: On reception of RequestDownload routine
 **
 ** Callback shall implement: provide information that the Flash Memory was programmed and should be erased before a new writing and customer specific implementation on download event
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

[!IF "General/Erase_Check = 'Memory Block Erased Check'"!]
/** \brief Get the erase status of the memory block
 **
 ** Callback is called: On reception of Erase routine
 **
 ** Callback shall implement: provide information if logical block is already
 **                           erase and that erase shall be skipped
 **
 ** \param[in] ubBlockId ID of the Memory block to be erased
 **
 ** \return state
 ** \retval PROG_E_NOT_ERASED
 ** \retval PROG_E_ERASED
 **/
tProgEraseStatus PROG_CustomGetEraseStatus(u8 ubBlockId)
{
    OSC_PARAM_UNUSED(ubBlockId);

    return PROG_E_NOT_ERASED;
}
[!ENDIF!]

[!IF "General/Erase_Check = 'Memory Block Erased Check'"!]
/** \brief Set the erase status of the memory block
 **
 ** Callback is called: After successful logical block erasing and
 **                     RequestDownload request reception
 **
 ** Callback shall implement: storage of the logical block erase status
 **
 ** \param[in] ubBlockId ID of the Memory block to be erased
 ** \param[in] eEraseStatus New erase status
 **
 ** \return eProgStatus success of the erase status update
 ** \retval PROG_E_OK
 ** \retval PROG_E_NOT_OK
 **/
tProgStatus PROG_CustomSetEraseStatus(u8 ubBlockId,tProgEraseStatus eEraseStatus)
{
    OSC_PARAM_UNUSED(ubBlockId);
    OSC_PARAM_UNUSED(eEraseStatus);

    return PROG_E_OK;
}
[!ENDIF!]

[!IF "General/Erase_Check = 'First Programming Check'"!]
/** \brief Get the status of the Flash memory if it's full erased or not (i.e first download on this ECU)
 **
 ** Callback is called: On reception of Erase routine to skip erasing if memory has never been written
 **
 ** Callback shall implement: provide information if this is the first Flash programming
 **
 ** \return eIsFirstProgramming status return by the function (PROG_TRUE / PROG_FALSE)
 **/
tProgBoolean PROG_CustomIsFirstProgramming(void)
{
    return PROG_FALSE;
}
[!ENDIF!]

/** \brief Notification of memory access to allow customers to place their routines
 **
 ** Callback is called: After successful memory data access
 **
 ** Callback shall implement: Operation that need to be performed after a memory data access
 **
 ** \param[in] eMemType Memory type (RAM, Flash and Flash Ext)
 ** \param[in] eOperationType Operation type (Read, write and erase)
 ** \param[in] uMemAddress Start address
 ** \param[in] uLength Data length
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
    tDataLength uLength,
    tDataBufferType PROG_FAR_POINTER paubDataBuffer
)
{
    OSC_PARAM_UNUSED(eMemType);
    OSC_PARAM_UNUSED(eOperationType);
    OSC_PARAM_UNUSED(uMemAddress);
    OSC_PARAM_UNUSED(uLength);
    OSC_PARAM_UNUSED(paubDataBuffer);

    return PROG_E_OK;
}

[!VAR "CUSTOM_MEMORY_USE" = "0"!]
[!VAR "CUSTOM_MEMORY_ASYN" = "0"!]
[!LOOP "Segments/*"!]
    [!VAR "Memory_Type" = "node:ref(Memory)/Memory_Type"!]
    [!IF "$Memory_Type = 'CUSTOM'"!]
        [!VAR "CUSTOM_MEMORY_USE" = "1"!]
        [!VAR "MEMORY_MODE_CUSTOM_MEM" = "node:ref(Memory)/Memory_Mode"!]
        [!IF "$MEMORY_MODE_CUSTOM_MEM = 'asynchronous'"!]
            [!VAR "CUSTOM_MEMORY_ASYN" = "1"!]
        [!ENDIF!]
    [!ENDIF!]
[!ENDLOOP!]

[!IF "$CUSTOM_MEMORY_USE = 1"!]
/** \brief This API is called to perform an erase operation
 **
 ** Callback is called: After request erasing of the custom memory
 **
 ** Callback shall implement: Operation to erase the custom memory
 **
 ** \param[in] uMemAddress Start address
 ** \param[in] uLength Data length
 **
 ** \return eProgStatus success of the operation(s)
 ** \retval PROG_E_OK
 ** \retval PROG_E_NOT_OK
 ** \retval PROG_E_BUSY
 **/
tProgStatus PROG_CustomMemoryErase
(
    tProgAddressType uMemAddress,
    tDataLength uLength
)
{
    OSC_PARAM_UNUSED(uMemAddress);
    OSC_PARAM_UNUSED(uLength);

    return PROG_E_OK;
}

/** \brief This API is called to perform a writing operation
 **
 ** Callback is called: After request writing data on the custom memory
 **
 ** Callback shall implement: Operation to write data on custom memory
 **
 ** \param[in] uMemAddress Start address
 ** \param[in] uLength Data length
 ** \param[in] paubDataBuffer Data buffer
 **
 ** \return eProgStatus success of the operation(s)
 ** \retval PROG_E_OK
 ** \retval PROG_E_NOT_OK
 ** \retval PROG_E_BUSY
 **/
tProgStatus PROG_CustomMemoryWrite
(
    tProgAddressType uMemAddress,
    tDataLength uLength,
    tDataBufferType PROG_FAR_POINTER paubDataBuffer
)
{
    OSC_PARAM_UNUSED(uMemAddress);
    OSC_PARAM_UNUSED(uLength);
    OSC_PARAM_UNUSED(paubDataBuffer);

    return PROG_E_OK;
}

/** \brief This API is called to perform a reading operation
 **
 ** Callback is called: After request reading data on the custom memory
 **
 ** Callback shall implement: Operation to read data on custom memory
 **
 ** \param[in] uMemAddress Start address
 ** \param[in] uLength Data length
 ** \param[in] paubDataBuffer Data buffer
 **
 ** \return eProgStatus success of the operation(s)
 ** \retval PROG_E_OK
 ** \retval PROG_E_NOT_OK
 ** \retval PROG_E_BUSY
 **/
tProgStatus PROG_CustomMemoryRead
(
    tProgAddressType uMemAddress,
    tDataLength uLength,
    tDataBufferType PROG_FAR_POINTER paubDataBuffer
)
{
    OSC_PARAM_UNUSED(uMemAddress);
    OSC_PARAM_UNUSED(uLength);
    OSC_PARAM_UNUSED(paubDataBuffer);

    return PROG_E_OK;
}

[!IF "$CUSTOM_MEMORY_ASYN = 1"!]
/** \brief Get the status of memory job
 **
 ** Callback is called: After each memory access operation
 **
 ** Callback shall implement: After PROG_CustomMemoryErase/PROG_CustomMemoryWrite/PROG_CustomMemoryRead
 **                           returns PROG_E_BUSY, this callback is called periodically until getting
 **                           a status different from PROG_E_BUSY.
 **
 ** \return eProgStatus success of the operation(s)
 ** \retval PROG_E_OK
 ** \retval PROG_E_NOT_OK
 ** \retval PROG_E_BUSY
 **/
tProgStatus PROG_CustomMemGetJobStatus(void)
{
    return PROG_E_OK;
}

[!ELSE!]
/** \brief Get next sector start address
 **
 ** Callback is called: After an erase operation to set the beginning of the next sector address
 **
 ** Callback shall implement: Operation to get the next sector address
 **
 ** \param[in] uMemAddress Memory address of reference sector
 **
 ** \return Start address of the next sector.
 **
 **/
tProgAddressType PROG_CustomGetNextSectorAddr
(
    tProgAddressType uMemAddress
)
{
    return uMemAddress;
}

[!ENDIF!]
[!ENDIF!]
[!IF "General/ResumableReprog = 'true'"!]
/** \brief Retrieve segment list stored in memory
 **
 ** Callback is called: This function is called in case reprogramming shall be resume in order
 ** to get all data that have been previously written for the logical block
 **
 ** Callback shall implement: Copy from memory of data that have been previously stored
 ** with PROG_CustomStoreSegmentList
 **
 ** \param[in,out] pstSegList pointer on structure where to copy the data
 **
 **
 **/
void PROG_CustomGetSegmentList
(
    tSegmentListType * pstSegList
)
{
    OSC_PARAM_UNUSED(pstSegList);
}

/** \brief Store segment list in memory
 **
 ** Callback is called: This function is called on RequestTransferExit to
 ** store information about the downloaded segment
 **
 ** Callback shall implement: Copy to memory of the segment list
 **
 ** \param[in] pstSegList address of structure to copy
 **
 ** \return Resume address of the logical block.
 **
 **/
void PROG_CustomStoreSegmentList(tSegmentListType * pstSegList)
{
    OSC_PARAM_UNUSED(pstSegList);
}

/** \brief Store resume address
 **
 ** Callback is called: During reprogramming to store resume address
 **
 ** \param[in] ubBlockId Index of the logical block
 ** \param[in] ulAddress Address to store
 **
 **
 **/
void PROG_CustomStoreResumeAddress
(
    u8 ubBlockId,
    u32 ulAddress
)
{
    OSC_PARAM_UNUSED(ubBlockId);
    OSC_PARAM_UNUSED(ulAddress);
}

/** \brief Get resume address
 **
 ** Callback is called: On reception of ReadDataByIdenfifier for
 ** DID "Reprogramming Resume Information"
 **
 ** \param[in] ubBlockId Index of the logical block
 **
 **
 **/
u32 PROG_CustomGetResumeAddress
(
    u8 ubBlockId
)
{
    OSC_PARAM_UNUSED(ubBlockId);

    return 0U;
}


[!ENDIF!]


[!IF "node:exists(as:modconf('ProgFCA')) and as:modconf('ProgFCA')/General/PROG_FCA_VARIANT='Atlantis_High'"!]
/** \brief Callback used to check the TargetName
 **
 ** \param[in] pubTargetNameAddress TargetName address
 ** \param[in] ubLen TargetName length
 **
 ** \return return status
 ** \retval PROG_E_OK
 ** \retval PROG_E_NOT_OK
 **/
tProgStatus PROG_CustomCheckTargetName(u8* pubTargetNameAddress,u8 ubLen)
{
    OSC_PARAM_UNUSED(pubTargetNameAddress);
    OSC_PARAM_UNUSED(ubLen);

    return PROG_E_OK;
}

/** \brief Callback used to check the RollbackId
 **
 ** \param[in] pubRollbackIdAddress RollbackId address
 ** \param[in] ubLen RollbackId length
 **
 ** \return return status
 ** \retval PROG_E_OK
 ** \retval PROG_E_NOT_OK
 **/
tProgStatus PROG_CustomCheckRollbackId(u8* pubRollbackIdAddress,u8 ubLen)
{
    OSC_PARAM_UNUSED(pubRollbackIdAddress);
    OSC_PARAM_UNUSED(ubLen);
    return PROG_E_OK;
}

/** \brief Callback used to check the CompatibilityId
 **
 ** \param[in] pubCompatibilityIdAddress CompatibilityId address
 ** \param[in] ubLen CompatibilityId length
 **
 ** \return return status
 ** \retval PROG_E_OK
 ** \retval PROG_E_NOT_OK
 **/
tProgStatus PROG_CustomCheckCompatibilityId(u8* pubCompatibilityIdAddress,u8 ubLen)
{
    OSC_PARAM_UNUSED(pubCompatibilityIdAddress);
    OSC_PARAM_UNUSED(ubLen);
    return PROG_E_OK;
}

/** \brief Callback used to check the Uuid
 **
 ** \param[in] pubUuidAddress Uuid address
 ** \param[in] ubLen Uuid length
 **
 ** \return return status
 ** \retval PROG_E_OK
 ** \retval PROG_E_NOT_OK
 **/
tProgStatus PROG_CustomCheckUuid(u8* pubUuidAddress,u8 ubLen)
{
    OSC_PARAM_UNUSED(pubUuidAddress);
    OSC_PARAM_UNUSED(ubLen);
    return PROG_E_OK;
}

/** \brief Callback used to check the SigningInfo (SigningName and SigningKeyIdentifier)
 **
 ** \param[in] pubSigningInfoAddress SigningInfo address
 ** \param[in] ubLen SigningInfo length
 **
 ** \return return status
 ** \retval PROG_E_OK
 ** \retval PROG_E_NOT_OK
 **/
tProgStatus PROG_CustomCheckSigningInfo(u8* pubSigningInfoAddress,u8 ubLen)
{
    OSC_PARAM_UNUSED(pubSigningInfoAddress);
    OSC_PARAM_UNUSED(ubLen);
    return PROG_E_OK;
}
[!ENDIF!]
[!IF "node:exists(as:modconf('ProgVCC'))"!]
/** \brief Get ESS validity status
 **
 ** Callback is called: Before using information from ESS
 **
 ** Callback shall implement: ESS validity status
 **
 ** \return eProgStatus success of the operation
 ** \retval PROG_E_OK ESS is valid
 ** \retval PROG_E_NOT_OK is not valid
 **/
tProgStatus Prog_GetEssValidityStatus(void)
{
    return PROG_E_NOT_OK;
}
/** \brief Get ESS number of logical block
 **
 ** Callback is called: On RD or Erase routine to identify the downloaded block
 **
 ** Callback shall implement: return number of logical block in ESS
 **
 ** \param[out] pubBlockNbr number of logical block in ESS
 **
 ** \return eProgStatus success of the operation
 ** \retval PROG_E_OK Information is available
 ** \retval PROG_E_NOT_OK Information is not available
 **/
tProgStatus Prog_GetEssLogicalBlockNbr(u8* pubBlockNbr)
{
    OSC_PARAM_UNUSED(pubBlockNbr);
    return PROG_E_NOT_OK;
}
/** \brief Get ESS logical block Identifier
 **
 ** Callback is called: On RD or Erase routine to identify the downloaded block
 **
 ** Callback shall implement: return identifier of the request logical block in ESS
 **
 ** \param[in] ubBlockIndex Block identifier
 ** \param[out] pulBlockIdent identifier of the request logical block in ESS
 **
 ** \return eProgStatus success of the operation
 ** \retval PROG_E_OK Information is available
 ** \retval PROG_E_NOT_OK Information is not available
 **/
tProgStatus Prog_GetEssLogicalBlockId(u8 ubBlockIndex, u16* pulBlockIdent)
{
    OSC_PARAM_UNUSED(ubBlockIndex);
    OSC_PARAM_UNUSED(pulBlockIdent);
    return PROG_E_NOT_OK;
}
/** \brief Get ESS logical block address
 **
 ** Callback is called: On RD or Erase routine to identify the downloaded block
 **
 ** Callback shall implement: return address of the request logical block in ESS
 **
 ** \param[in] ubBlockIndex Block identifier
 ** \param[out] pulBlockAddr address of the request logical block in ESS
 **
 ** \return eProgStatus success of the operation
 ** \retval PROG_E_OK Information is available
 ** \retval PROG_E_NOT_OK Information is not available
 **/
tProgStatus Prog_GetEssLogicalBlockStartAddr(u8 ubBlockIndex, u32* pulBlockAddr)
{
    OSC_PARAM_UNUSED(ubBlockIndex);
    OSC_PARAM_UNUSED(pulBlockAddr);
    return PROG_E_NOT_OK;
}
/** \brief Get ESS logical block Length
 **
 ** Callback is called: On RD or Erase routine to identify the downloaded block
 **
 ** Callback shall implement: return length of the request logical block in ESS
 **
 ** \param[in] ubBlockIndex Block identifier
 ** \param[out] pulBlockLength length of the request logical block in ESS
 **
 ** \return eProgStatus success of the operation
 ** \retval PROG_E_OK Information is available
 ** \retval PROG_E_NOT_OK Information is not available
 **/
tProgStatus Prog_GetEssLogicalBlockLength(u8 ubBlockIndex, u32* pulBlockLength)
{
    OSC_PARAM_UNUSED(ubBlockIndex);
    OSC_PARAM_UNUSED(pulBlockLength);
    return PROG_E_NOT_OK;
}
/** \brief Get ESS logical block VBT address
 **
 ** Callback is called: On RD to get Verification Block Table location
 **
 ** Callback shall implement: return address of the verification block table of the request logical block in ESS
 **
 ** \param[in] ubBlockIndex Block identifier
 ** \param[out] pulVBTAddress address of the verification block table of the request logical block in ESS
 **
 ** \return eProgStatus success of the operation
 ** \retval PROG_E_OK Information is available
 ** \retval PROG_E_NOT_OK Information is not available
 **/
tProgStatus Prog_GetEssLogicalBlockVerifTable(u8 ubBlockIndex, u32* pulVBTAddress)
{
    OSC_PARAM_UNUSED(ubBlockIndex);
    OSC_PARAM_UNUSED(pulVBTAddress);
    return PROG_E_NOT_OK;
}
/** \brief Get ESS VBT address
 **
 ** Callback is called: On RD to get Verification Block Table location
 **
 ** Callback shall implement: return address of the verification block table of the request logical block in ESS
 **
 ** \param[out] pulVBTAddress address of the verification block table of the request logical block in ESS
 **
 ** \return eProgStatus success of the operation
 ** \retval PROG_E_OK Information is available
 ** \retval PROG_E_NOT_OK Information is not available
 **/
tProgStatus Prog_GetEssVerifTable(u32* pulVBTAddress)
{
    OSC_PARAM_UNUSED(pulVBTAddress);
    return PROG_E_OK;
}
/** \brief Get the address of the jump to the application
 **
 ** Callback is called: On switching to application mode
 **
 ** Callback shall implement: get the application start address from the ESS
 **
 ** \param[out] ulApplicationStartAddress Application start address
 **
 ** \return void
 **/
void Prog_GetEssApplicationStartAddress(u32* ulApplicationStartAddress)
{
    OSC_PARAM_UNUSED(ulApplicationStartAddress);
}
/** \brief API that invalidate the logical block
 **
 ** Callback is called: On Erase routine reception
 **
 ** Callback shall implement: 1- customer code that shall be executed before
 **                           performing an erasing of a logical block
 **
 **                           2- It shall invalidate the logical block that will be erased
 **                           to make sure no jump to the application will be done if an error occurred
 **                           and the application is not fully erased or reprogrammed
 **
 ** \param[in] ubBlockId The ID of the block that will be erased
 **
 ** \return Result application invalidation
 ** \retval PROG_E_OK Treatment finish successfully
 ** \retval PROG_E_NOT_OK Error happened during treatment
 **/
tProgStatus PROG_InvalidateBlock(u8 ubBlockId)
{
    OSC_PARAM_UNUSED(ubBlockId);
    return PROG_E_OK;
}
/** \brief Get the start address of the ESS
 **
 ** Callback is called: On calculating MAC
 **
 ** Callback shall implement: get the start address of the ESS
 **
 ** \param[out] ulEssStartAddress ESS start address
 **
 ** \return void
 **/
void Prog_GetEssStartAddr(u32* ulEssStartAddress)
{
    OSC_PARAM_UNUSED(ulEssStartAddress);
}

/** \brief Get the length of the ESS
 **
 ** Callback is called: On calculating MAC of ESS
 **
 ** \param[out] ulEssLength ESS length
 **
 ** Callback shall implement: get the length of the ESS
 **
 ** \return void
 **/
void Prog_GetEssLength(u32* ulEssLength)
{
    OSC_PARAM_UNUSED(ulEssLength);
}

/** \brief Check if the production key is written or not
 **
 ** Callback is called: before writing or reading the production key
 **
 **
 ** Callback shall implement: check if the key exists or not
 **
 ** \return boolean TRUE : Key exists, FALSE : Key does not exist
 **/
boolean Prog_CustomIsProdKeyPresent(void)
{
  return TRUE;
}

/** \brief Get the checksum of the key
 **
 ** Callback is called: On receiving RDBI of the production key
 **
 ** \param[out] aubKeyChecksum key checksum
 **
 ** Callback shall implement: get the key checksum from the non volatile memory
 **
 ** \return void
 **/
void Prog_CustomReadKeyChecksum(u8* aubKeyChecksum)
{
  OSC_PARAM_UNUSED(aubKeyChecksum);
}

/** \brief write the production key used in signature verification
 **
 ** Callback is called: On receving WDBI for the production key
 **
 ** \param[in] ulExponent key exponent
 ** \param[in] aubModulus key modulus
 ** \param[in] aubKeyChecksum key checksum
 **
 ** Callback shall implement: write the key and its checksum in non volatile memory
 **
 ** \return void
 **/
void Prog_CustomWriteKey(u32 ulExponent, u8* aubModulus, u8* aubKeyChecksum)
{
  OSC_PARAM_UNUSED(ulExponent);
  OSC_PARAM_UNUSED(aubModulus);
  OSC_PARAM_UNUSED(aubKeyChecksum);
}

/** \brief Get the result of the certificate verification
 **
 ** Callback is called: On checkMemory request
 **
 ** Callback shall implement: the certificate verification or its result
 **
 ** \return eProgStatus success of the certificate verififcation
 ** \retval PROG_E_OK Certificate verification passed
 ** \retval PROG_E_NOT_OK Certificate verification failed
 **/
tProgStatus  PROG_CustomCheckCertificateVerification(void)
{
  return PROG_E_OK;
}
[!ENDIF!]

[!IF "General/Dual_Memory_Bank_Used = 'true'"!]
/** \brief Calculate the write address on inactive memory bank
 ** 
 ** \param[in] ulAddr Write address on active memory bank
 ** 
 ** \return Calculated address on inactive memory bank
 **/
u32 PROG_CustomCalcInactiveBankWriteAddr(u32 ulAddr)
{
    OSC_PARAM_UNUSED(ulAddr);

    return 0U;
}

/** \brief Calculate the read address on inactive memory bank
 ** 
 ** \param[in] ulAddr Address on active memory bank
 ** 
 ** \return Calculated address on inactive bank
 **/
u32 PROG_CustomCalcInactiveBankReadAddr(u32 ulAddr)
{
    OSC_PARAM_UNUSED(ulAddr);

    return 0U;
}

[!ENDIF!]

