/*********************************************************************************/
/*                                                                               */
/*                                BOOT Layers                                    */
/*                                                                               */
/* ------------------------------------------------------------------------------*/
/*                                                                               */
/*                                 PROG configuration                            */
/*                                                                               */
/*********************************************************************************/
/*%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%                                        */
/*%%   _____________________________   %%  \file PROG_Cbk.h                      */
/*%%  |                             |  %%  \brief PROG layer include plugin file */
/*%%  |   &&&&&   &&&&&             |  %%  Module version: 2.17.0 BL-3.X              */
/*%%  |   &       &    &            |  %%                                        */
/*%%  |   &&&&    &&&&&             |  %%                                        */
/*%%  |   &       &    &            |  %%                                        */
/*%%  |   &&&&&   &&&&&             |  %%                                        */
/*%%  |_____________________________|  %%                                        */
/*%%                                   %%                                        */
/*%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%                                        */
/*********************************************************************************/
/* Copyright 2010 by Elektrobit Automotive GmbH                                  */
/* All rights exclusively reserved for Elektrobit Automotive GmbH,               */
/* unless expressly agreed to otherwise.                                         */
/*********************************************************************************/

[!AUTOSPACING!]


#ifndef PROG_CBK_H
#define PROG_CBK_H

#if (PROG_CRY_PRESENT == STD_ON)
#include "Csm.h"
#endif /* (PROG_CRY_PRESENT == STD_ON) */

/*------------------------------{PROG_SwitchApplicationModeInd}-----------------*/
extern void PROG_SwitchApplicationModeInd(void);

/*--------------------------{PROG_DisableECCCheck}------------------------------*/
extern void PROG_DisableECCCheck(void);

/*--------------------------{PROG_EnableECCCheck}-------------------------------*/
extern void PROG_EnableECCCheck(void);

[!IF "Decryption/Enable_Decryption = 'true'"!]
/*--------------------------------{PROG_CustomDecryptData}------------------------*/
extern tProgStatus PROG_CustomDecryptData(u8 ubEncryptionMethod, u8 * pubData, u16 DataLength);
[!ENDIF!]

[!IF "node:exists(as:modconf('ProgJLR')) and as:modconf('ProgJLR')/General/PROG_JLR_VARIANT='PBL'
        or node:exists(as:modconf('ProgGM')) or node:exists(as:modconf('ProgFCA')) or node:exists(as:modconf('ProgVCC'))
    or node:exists(as:modconf('ProgVAG')) or node:exists(as:modconf('ProgDAG'))
    or node:exists(as:modconf('ProgOEMInd'))"!]

/*--------------------------------{PROG_CheckProgRequest}------------------------*/
extern u8 PROG_CheckProgRequest(void);
[!ENDIF!]
[!IF "node:exists(as:modconf('ProgJLR')) and as:modconf('ProgJLR')/General/PROG_JLR_VARIANT='PBL'
    or node:exists(as:modconf('ProgGM')) or node:exists(as:modconf('ProgFCA'))
    or node:exists(as:modconf('ProgVAG')) or node:exists(as:modconf('ProgDAG'))
    or node:exists(as:modconf('ProgOEMInd'))"!]

/*--------------------------{PROG_JumpToApplication}-----------------------------*/
extern void PROG_JumpToApplication(void);
[!ENDIF!]
[!IF "(node:exists(as:modconf('ProgJLR'))
    and (as:modconf('ProgJLR')/General/PROG_JLR_VARIANT='PBL' or as:modconf('ProgJLR')/General/PROG_JLR_VARIANT='SBL'))
    or node:exists(as:modconf('ProgFCA'))
    or node:exists(as:modconf('ProgVAG'))
    or (node:exists(as:modconf('ProgOEMInd')) and (./OemInd/Application_Validity_Algo='Custom'))
    or node:exists(as:modconf('ProgDAG'))"!]

/*------------------------------{PROG_IsValidApplication}-----------------------*/
extern tProgBoolean PROG_IsValidApplication(void);
[!ENDIF!]
[!IF "(node:exists(as:modconf('ProgJLR'))
    and (as:modconf('ProgJLR')/General/PROG_JLR_VARIANT='PBL' or as:modconf('ProgJLR')/General/PROG_JLR_VARIANT='SBL'))
    or (node:exists(as:modconf('ProgFCA')) and as:modconf('ProgFCA')/General/PROG_FCA_VARIANT='Atlantis_Mid')
    or node:exists(as:modconf('ProgVAG'))
    or node:exists(as:modconf('ProgDAG'))"!]

/*------------------------------{PROG_VerifySectionCrc}--------------------------*/
extern tProgCompleteStatus PROG_VerifySectionCrc(void);
[!ENDIF!]
[!IF "node:exists(as:modconf('ProgJLR')) and as:modconf('ProgJLR')/General/PROG_JLR_VARIANT='SBL'
    or (node:exists(as:modconf('ProgOEMInd')) and (./OemInd/Application_Validity_Algo='Custom') and (./OemInd/Erase_Mode != 'All'))
    or (node:exists(as:modconf('ProgFCA')) and as:modconf('ProgFCA')/General/PROG_FCA_VARIANT='Atlantis_Mid')"!]

/*------------------------------{PROG_InvalidateSection}------------------------*/
extern tProgStatus PROG_InvalidateSection(tProgAddressType ulStartAddress, u32 ulEraseLength, tUdsStatus * ErrorCode);
[!ENDIF!]
[!IF "node:exists(as:modconf('ProgVAG')) or node:exists(as:modconf('ProgDAG')) or
    (node:exists(as:modconf('ProgOEMInd')) and (./OemInd/Erase_Mode = 'All')) or
    (node:exists(as:modconf('ProgFCA')) and as:modconf('ProgFCA')/General/PROG_FCA_VARIANT='Atlantis_High')"!]

/*------------------------------{PROG_InvalidateSection_BlockID}----------------*/
extern tProgStatus PROG_InvalidateSection_BlockID(u8 ubBlockId);
[!ENDIF!]
[!IF "node:exists(as:modconf('ProgGM'))"!]

/*------------------------------{PROG_GetKeyNBIDValue}--------------------------*/
extern u16 PROG_GetKeyNBIDValue(void);


/*------------------------------{PROG_GetNBIDValue}-----------------------------*/
extern u16 PROG_GetNBIDValue(void);


/*------------------------------{PROG_SetKeyNBIDValue}--------------------------*/
extern void PROG_SetKeyNBIDValue(u16 uwKeyNBID);

/*------------------------------{PROG_SetNBIDValue}-----------------------------*/
extern void PROG_SetNBIDValue(u16 uwNBID);
/*------------------------------{PROG_GetSBIFlagValue}-----------------------------*/
extern u8 PROG_GetSBIFlagValue(void);
/*------------------------------{PROG_SetSBIFlagValue}-----------------------------*/
extern void PROG_SetSBIFlagValue(u8 ubSBI);
[!ENDIF!]
[!IF "not(node:exists(as:modconf('ProgVCC'))) and General/Dsc_Prog_Response = 'true'"!]
/*--------------------------{PROG_GetSuppressBitFromAppli}--------------------*/
extern u8 PROG_GetSuppressBitFromAppli(void);
[!ENDIF!]
[!IF "General/Erase_Check = 'true'"!]
/*------------------------------{PROG_GetEraseStateStatus}----------------------*/
extern void PROG_GetEraseStateStatus(tProgEraseStatus * eEraseStatus);

[!ENDIF!]
[!IF "node:exists(as:modconf('ProgGM'))"!]
/*---------------------------{PROG_CopySBATicket}-----------------------------*/
extern tProgStatus PROG_CopySBATicket(u8 * pubRamBuffer);
extern void Prog_CustomGetAdditionalProgrammingConditionalFlags(u8 * pubFlag);
extern void Prog_CustomGetECUInternalProgrammingFlag(u8 * pubFlag);
extern void Prog_CustomGetProgrammingTolerantConditionsFlag(u8 * pubFlag);
extern void Prog_CustomGetProgrammingConditionsFlag(u8 * pubFlag);
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

/*------------------------{PROG_CustomWriteFingerprint}-----------------------------*/
extern tProgStatus PROG_CustomWriteFingerprint(u8 * pubRamBuffer);

/*------------------------{PROG_CustomGetWriteFingerprintStatus}--------------------*/
extern tProgStatus PROG_CustomGetWriteFingerprintStatus(void);
    [!ENDIF!]
[!ENDIF!]
[!IF "(node:exists(as:modconf('ProgFCA')) and as:modconf('ProgFCA')/General/PROG_FCA_VARIANT='Atlantis_Mid')"!]

/*---------------------------{PROG_CustomStartChecksumCalc}-------------------------*/
extern void PROG_CustomStartChecksumCalc(void);
[!ENDIF!]
[!IF "(node:exists(as:modconf('ProgFCA')) and as:modconf('ProgFCA')/General/PROG_FCA_VARIANT='Atlantis_Mid')"!]

/*---------------------------{PROG_CustomChecksumCalc}------------------------------*/
extern tProgStatus PROG_CustomChecksumCalc(u16* puwCalculatedCks);
[!ENDIF!]
[!IF "(node:exists(as:modconf('ProgFCA')) and as:modconf('ProgFCA')/General/PROG_FCA_VARIANT='Atlantis_Mid')"!]

/*---------------------------{PROG_CustomUpdateChecksumCalc}------------------------*/
extern void PROG_CustomUpdateChecksumCalc(u8* pubData, u32 ulDataSize);
[!ENDIF!]
[!IF "(node:exists(as:modconf('ProgFCA')) and as:modconf('ProgFCA')/General/PROG_FCA_VARIANT='Atlantis_Mid')"!]
/*---------------------------{PROG_CustomSetAppValidity}----------------------------*/
extern void PROG_CustomSetAppValidity(u32 ulAddress, u32 ulEndAddress);
[!ENDIF!]
[!IF "node:exists(as:modconf('ProgVAG'))
    or node:exists(as:modconf('ProgDAG'))
        or node:exists(as:modconf('ProgVCC'))
    or (node:exists(as:modconf('ProgFCA')) and as:modconf('ProgFCA')/General/PROG_FCA_VARIANT='Atlantis_High')
    or (node:exists(as:modconf('ProgOEMInd')) and (./OemInd/Application_Validity_Algo='Custom'))"!]
/*---------------------------{PROG_CustomSetDownloadVerificationSuccess}----------------------*/
extern tProgStatus PROG_CustomSetDownloadVerificationSuccess(u8 ubLogicalBlockId, u8 ubLogicalSegmentId, tProgBoolean ubCompareSuccess);
[!ENDIF!]
[!IF "(node:exists(as:modconf('ProgVAG')) and General/Expected_Crc_Location = 'Application')
    or (node:exists(as:modconf('ProgOEMInd')) and (./OemInd/Application_Validity_Algo='Custom'))
    or (node:exists(as:modconf('ProgDAG')) and General/Expected_Crc_Location = 'Application')"!]

/*---------------------------{PROG_CustomGetExpectedCrc}----------------------------*/
extern void PROG_CustomGetExpectedCrc(u8 ubLogicalBlockId, u32* pulExpectedCrc);
[!ENDIF!]
[!IF "(node:exists(as:modconf('ProgFCA')) and as:modconf('ProgFCA')/General/PROG_FCA_VARIANT='Atlantis_Mid')"!]

/*---------------------------{PROG_CustomWriteProgStatus}---------------------------*/
extern void PROG_CustomWriteProgStatus(u32 ulProgrammingStatus);
[!ENDIF!] /* PROG_REQ_PROGRAMMING_STATUS_ENABLE == STD_ON */
[!IF "(node:exists(as:modconf('ProgVAG'))) or (node:exists(as:modconf('ProgDAG'))) or (as:modconf('Prog')/General/Transmit_Response_Before_Reset = 'false')"!]

/*---------------------------{PROG_CustomGetResetCause}-----------------------------*/
extern void PROG_CustomGetResetCause(tProgResCause* pubResetCause, tProgBoolean* pubSendResp);

/*---------------------------{PROG_CustomStoreResetCause}---------------------------*/
extern void PROG_CustomStoreResetCause(tProgResCause ubResetCause, tProgBoolean ubSendResp);
[!ENDIF!]

[!IF "node:exists(as:modconf('ProgVAG')) or node:exists(as:modconf('ProgDAG'))
    or node:exists(as:modconf('ProgOEMInd'))"!]
[!IF "General/Check_Programming_PreConditions = 'true'"!]
/*---------------------------{PROG_CustCheckProgPrecond}----------------------------*/
extern tProgStatus PROG_CustCheckProgPrecond(void);
[!ENDIF!]
[!ENDIF!]

[!IF "(node:exists(as:modconf('ProgFCA')) and as:modconf('ProgFCA')/General/PROG_FCA_VARIANT='Atlantis_High')"!]
[!IF "General/Check_Programming_PreConditions = 'true'"!]
/*---------------------------{PROG_CustCheckProgPrecond}----------------------------*/
extern void PROG_CustCheckProgPrecondList(u8 * pubProgrammingConditionNumber, u8 * paubConditionList);
[!ENDIF!]
[!ENDIF!]


#ifdef NCS_UNITARY_TEST
extern void PROG_RamRead(tProgAddressType uMemAddress, tDataLength uLength, tDataBufferType PROG_FAR_POINTER paubDataBuffer);
extern void PROG_RamWrite(tProgAddressType uMemAddress, tDataLength uLength, tDataBufferType PROG_FAR_POINTER paubDataBuffer);
#endif     /* NCS_UNITARY_TEST */
[!IF "(node:exists(as:modconf('ProgVAG')) )
    or (node:exists(as:modconf('ProgDAG')))
    or (node:exists(as:modconf('ProgOEMInd')))"!]
/*---------------------------{PROG_CustomWriteCRC}-----------------------------*/
extern void PROG_CustomWriteCRC(u32 ulCrcVal);
[!ENDIF!]

[!IF "DownloadVerification/CVN_Verification = 'true'"!]
extern tProgStatus PROG_CustomCvnVerification(u8 ubLogicalBlockId, const u8* paubExpectedCvn);
extern tProgStatus PROG_CustomCvnVerificationStatus(void);
[!ENDIF!]

[!IF "(node:exists(as:modconf('ProgVAG'))
    or (node:exists(as:modconf('ProgDAG')))
    or (node:exists(as:modconf('ProgFCA')) and as:modconf('ProgFCA')/General/PROG_FCA_VARIANT='Atlantis_High')
    or (node:exists(as:modconf('ProgOEMInd'))))"!]
/*---------------------------{PROG_CustomCoherencyCheck}-----------------------------*/
extern tProgStatus PROG_CustomCoherencyCheck(tProgCohChkResult* eCohChkResult);
[!ENDIF!]

[!IF "node:exists(as:modconf('Uds'))"!]
    [!VAR "COHERENCY_PRE_CHECK_USE" = "0"!]
    [!LOOP " as:modconf('Uds')/Routine_Control/*"!]
        [!IF "Callback = 'PROG_CoherencyPreCheck'"!]
            [!VAR "COHERENCY_PRE_CHECK_USE" = "1"!]
        [!ENDIF!]
    [!ENDLOOP!]
    [!IF "$COHERENCY_PRE_CHECK_USE = 1"!]
/*---------------------------{PROG_CustomComputeCoherencyPreCheck}-----------------------------*/
extern tProgCohChkResult PROG_CustomComputeCoherencyPreCheck(u8* paubUdsData, u16 puwlen, tUdsStatus* eUdsStatus);
    [!ENDIF!]
[!ENDIF!]

[!IF "node:exists(as:modconf('ProgGM'))"!]
[!IF "GM/EcuId_Source = 'User_Callback'"!]
extern void PROG_CustomGetEcuId(u8* paubEcuId);
[!ENDIF!]
[!ENDIF!]

[!IF "(node:exists(as:modconf('ProgVAG'))
    or (node:exists(as:modconf('ProgDAG')))
    or ( (node:exists(as:modconf('ProgFCA'))) and (as:modconf('ProgFCA')/General/PROG_FCA_VARIANT='Atlantis_High')) )"!]
extern u16 PROG_CustomGetProgCounter(u8 ubBlockId);

extern tProgStatus PROG_CustomIncrementProgCounter(u8 ubBlockId);
[!ENDIF!]

[!IF "node:exists(as:modconf('Uds'))"!]
    [!VAR "PARTIAL_VERIFY_CRC_USE" = "0"!]
    [!LOOP " as:modconf('Uds')/Routine_Control/*"!]
        [!IF "Callback = 'PROG_PartialVerificationCrc'"!]
            [!VAR "PARTIAL_VERIFY_CRC_USE" = "1"!]
        [!ENDIF!]
    [!ENDLOOP!]
    [!IF "$PARTIAL_VERIFY_CRC_USE = 1"!]
extern void PROG_CustomGetPartProgSegList(u8 ubBlockId,u32* aulSegProgSize,u8* ubSegNbr);
extern void PROG_CustomSetPartProgSegList(u8 ubBlockId,u32* aulSegProgSize,u8* ubSegNbr);
extern void PROG_CustomClearPartProgSegList(u8 ubBlockId);
    [!ENDIF!]
[!ENDIF!]

[!IF "node:exists(as:modconf('Csm'))"!]
[!IF "(node:exists(as:modconf('ProgGM'))
    or (node:exists(as:modconf('ProgDAG')))
      or (node:exists(as:modconf('ProgVCC')))
    or (node:exists(as:modconf('ProgFCA')) and as:modconf('ProgFCA')/General/PROG_FCA_VARIANT='Atlantis_High')
    or (node:exists(as:modconf('ProgVAG')))
    or (node:exists(as:modconf('ProgOEMInd'))))"!]
extern void PROG_CustomGetAsymPublicKey(const u8** paubPublicModulus, u32* pulPublicExponent);
[!ENDIF!]
[!ENDIF!]

[!IF "(as:modconf('BM')/Security/SecureBoot/SECURE_AUTHENTICATED_BOOT='Authenticated')"!]
/*---------------------------{PROG_CustomInvalidateBootloaderChecksum}-----------------------------*/
extern void PROG_CustomInvalidateBootloaderChecksum(void);

/*---------------------------{PROG_CustomValidateBootloaderChecksum}-----------------------------*/
extern void PROG_CustomValidateBootloaderChecksum(void);

/*---------------------------{PROG_CustomSetBootloaderChecksum}-----------------------------*/
extern void PROG_CustomSetBootloaderChecksum(u8 * pubComputedChecksum);
[!ENDIF!]

[!IF "(as:modconf('BM')/Security/SecureBoot/SECURE_AUTHENTICATED_BOOT ='Authenticated') and
    (as:modconf('BM')/Security/SecureBoot/BOOT_VERIFICATION ='ON')"!]
/*---------------------------{PROG_CustomGetComputedBootloaderChecksum}-----------------------------*/
extern void PROG_CustomGetComputedBootloaderChecksum(u8 * pubComputedChecksum);

/*---------------------------{PROG_CustomIsValidBootloaderChecksum}-----------------------------*/
extern tProgStatus PROG_CustomIsValidBootloaderChecksum(void);
[!ENDIF!]


 [!IF "((not((as:modconf('BM')/Security/SecureBoot/SECURE_AUTHENTICATED_BOOT = 'OFF') and (as:modconf('Prog')/Security/Secure_Checksum_computation = 'false'))) and
     (node:exists(as:modconf('ProgDAG')) or (node:exists(as:modconf('ProgFCA')) and as:modconf('ProgFCA')/General/PROG_FCA_VARIANT='Atlantis_High')))
     or ((as:modconf('Prog')/Security/Secure_Checksum_computation = 'true') and (node:exists(as:modconf('ProgVCC'))) and (as:modconf('ProgVCC')/General/PROG_VCC_VARIANT='SBL'))"!]

[!IF "((as:modconf('Prog')/General/Use_CSM_ASR430_DemoWrapper = 'false') and (contains(as:modconf('Prog')/Security/ProgCsmSecureConfigId, '/Csm/Csm/CsmMacGenerate/') =  'true')) or
    ((as:modconf('Prog')/General/Use_CSM_ASR430_DemoWrapper = 'true') and (node:exists(node:ref(node:ref(as:modconf('Prog')/Security/ProgCsmSecureConfigId)/CsmJobPrimitiveRef)/CsmMacGenerate)) )"!]
/*---------------------------{PROG_CustomGetMacKey}-----------------------------*/
extern void PROG_CustomGetMacKey(const u8** paubKeyData, u32* pulKeyLength);
[!ENDIF!]

/*---------------------------{PROG_CustomSetApplicationChecksum}-----------------------------*/
extern void PROG_CustomSetApplicationChecksum(u8 * pubComputedChecksum, u16 uwBlockIdentifier);
[!ENDIF!]





[!IF "(node:exists(as:modconf('ProgVAG'))
    or (node:exists(as:modconf('ProgDAG'))))"!]

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

extern tProgStatus PROG_CustomGetTpBsValue(u8* ubTpBsValue);
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
extern tProgStatus PROG_CustomGetTpStminValue(u8* ubTpStminValue);
    [!ENDIF!]
[!ENDIF!]

[!IF "General/Erase_Check = 'First Programming Check'"!]
/*---------------------------{PROG_CustomIsFirstProgramming}-----------------------------*/
extern tProgBoolean PROG_CustomIsFirstProgramming(void);
[!ENDIF!]

/*---------------------------{PROG_CustomDownloadNotification}-----------------------------*/
extern tProgStatus PROG_CustomDownloadNotification(u32 ulStartAddress, u32 ulMemorySize);

[!IF "General/Erase_Check = 'Memory Block Erased Check'"!]
/*---------------------------{PROG_CustomGetEraseStatus}-----------------------------*/
extern tProgEraseStatus PROG_CustomGetEraseStatus(u8 ubBlockId);
[!ENDIF!]

[!IF "General/Erase_Check = 'Memory Block Erased Check'"!]
/*---------------------------{PROG_CustomSetEraseStatus}-----------------------------*/
extern tProgStatus PROG_CustomSetEraseStatus(u8 ubBlockId,tProgEraseStatus eEraseStatus);
[!ENDIF!]

/*---------------------------{PROG_CustomMemoryAccessNotification}-------------------*/
extern tProgStatus PROG_CustomMemoryAccessNotification
(
    tProgMemType eMemType,
    tOperationType eOperationType,
    tProgAddressType uMemAddress,
    tDataLength uLength,
    tDataBufferType PROG_FAR_POINTER paubDataBuffer
);

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
/*---------------------------{PROG_CustomMemoryErase}-------------------*/
extern tProgStatus PROG_CustomMemoryErase
(
    tProgAddressType uMemAddress,
    tDataLength uLength
);

/*---------------------------{PROG_CustomMemoryWrite}-------------------*/
extern tProgStatus PROG_CustomMemoryWrite
(
    tProgAddressType uMemAddress,
    tDataLength uLength,
    tDataBufferType PROG_FAR_POINTER paubDataBuffer
);

/*---------------------------{PROG_CustomMemoryRead}-------------------*/
extern tProgStatus PROG_CustomMemoryRead
(
    tProgAddressType uMemAddress,
    tDataLength uLength,
    tDataBufferType PROG_FAR_POINTER paubDataBuffer
);

[!IF "$CUSTOM_MEMORY_ASYN = 1"!]
/*---------------------------{PROG_CustomMemGetJobStatus}-------------------*/
extern tProgStatus PROG_CustomMemGetJobStatus(void);
[!ELSE!]
/*---------------------------{PROG_CustomGetNextSextorAddr}-------------------*/
extern tProgAddressType PROG_CustomGetNextSectorAddr(tProgAddressType uMemAddress);
[!ENDIF!]
[!ENDIF!]

[!IF "General/ResumableReprog = 'true'"!]
/*---------------------------{PROG_CustomGetSegmentList}-------------------*/
extern void PROG_CustomGetSegmentList(tSegmentListType * pstSegList);

extern void PROG_CustomStoreSegmentList(tSegmentListType * pstSegList);

extern void PROG_CustomStoreResumeAddress(u8 ubBlockId, u32 ulAddress);

extern u32 PROG_CustomGetResumeAddress(u8 ubBlockId);
[!ENDIF!]

[!IF "node:exists(as:modconf('ProgFCA')) and as:modconf('ProgFCA')/General/PROG_FCA_VARIANT='Atlantis_High'"!]
/*---------------------------{PROG_CustomCheckTargetName}-----------------------------*/
extern tProgStatus PROG_CustomCheckTargetName(u8* pubTargetNameAddress,u8 ubLen);
/*------------------------{end PROG_CustomCheckTargetName}--------------------------*/

/*---------------------------{PROG_CustomCheckRollbackId}-----------------------------*/
extern tProgStatus PROG_CustomCheckRollbackId(u8* pubRollbackIdAddress,u8 ubLen);
/*------------------------{end PROG_CustomCheckRollbackId}--------------------------*/

/*---------------------------{PROG_CustomCheckCompatibilityId}-----------------------------*/
extern tProgStatus PROG_CustomCheckCompatibilityId(u8* pubCompatibilityIdAddress,u8 ubLen);
/*------------------------{end PROG_CustomCheckCompatibilityId}--------------------------*/

/*---------------------------{PROG_CustomCheckUuid}-----------------------------*/
extern tProgStatus PROG_CustomCheckUuid(u8* pubUuidAddress,u8 ubLen);
/*------------------------{end PROG_CustomCheckUuid}--------------------------*/

/*---------------------------{PROG_CustomCheckSigningInfo}-----------------------------*/
extern tProgStatus PROG_CustomCheckSigningInfo(u8* pubSigningInfoAddress,u8 ubLen);
/*------------------------{end PROG_CustomCheckSigningInfo}--------------------------*/
[!ENDIF!]

[!IF "node:exists(as:modconf('ProgVCC'))"!]
extern tProgStatus Prog_GetEssValidityStatus(void);
extern tProgStatus Prog_GetEssLogicalBlockNbr(u8* pubBlockNbr);
extern tProgStatus Prog_GetEssLogicalBlockId(u8 ubBlockIndex, u16* pulBlockIdent);
extern tProgStatus Prog_GetEssLogicalBlockStartAddr(u8 ubBlockIndex, u32* pulBlockAddr);
extern tProgStatus Prog_GetEssLogicalBlockLength(u8 ubBlockIndex, u32* pulBlockLength);
extern tProgStatus Prog_GetEssLogicalBlockVerifTable(u8 ubBlockIndex, u32* pulVBTAddress);
extern tProgStatus Prog_GetEssVerifTable(u32* pulVBTAddress);
extern tProgStatus PROG_InvalidateBlock(u8 ubBlockId);
extern void Prog_GetEssApplicationStartAddress(u32* ulApplicationStartAddress);
extern void Prog_GetEssStartAddr(u32* ulEssStartAddress);
extern void Prog_GetEssLength(u32* ulEssLength);
extern boolean Prog_CustomIsProdKeyPresent(void);
extern void Prog_CustomReadKeyChecksum(u8* aubKeyChecksum);
extern void Prog_CustomWriteKey(u32 ulExponent, u8* aubModulus, u8* aubKeyChecksum);
extern tProgStatus PROG_CustomCheckCertificateVerification(void);
[!ENDIF!]

[!IF "(node:exists(as:modconf('ProgGM')) and (as:modconf('Prog')/Segments/*/Partition_Type='PROG_HSM_PARTITION'))"!]
extern tProgStatus PROG_HSMRequestUpdate(void);
extern tProgStatus Prog_HSMTransferData(u8* paubHsmBuffer,u16 uwHsmBufferLength, u16* uwHsmPEC);
extern tProgPECError PROG_HSMLastDataReceived(void);

[!ENDIF!]

[!IF "General/Dual_Memory_Bank_Used = 'true'"!]
/*---------------------------{PROG_CustomCalcInactiveBankWriteAddr}-----------------------------*/
extern u32 PROG_CustomCalcInactiveBankWriteAddr(u32 ulAddr);
/*------------------------{end PROG_CustomCalcInactiveBankWriteAddr}--------------------------*/

/*---------------------------{PROG_CustomCalcInactiveBankReadAddr}-----------------------------*/
extern u32 PROG_CustomCalcInactiveBankReadAddr(u32 ulAddr);
/*------------------------{end PROG_CustomCalcInactiveBankReadAddr}--------------------------*/
[!ENDIF!]


#endif     /* PROG_CBK_H */
