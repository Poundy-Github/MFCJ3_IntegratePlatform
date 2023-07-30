#ifndef PROG_PUB_H
#define PROG_PUB_H

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
/*%%   _____________________________   %%  \file PROG_Pub.h                      */
/*%%  |                             |  %%  \brief PROG layer source plugin file  */
/*%%  |   &&&&&   &&&&&             |  %%  Module version: 2.19.0 BL-3.X */
/*%%  |   &       &    &            |  %%                                        */
/*%%  |   &&&&    &&&&&             |  %%                                        */
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

#include "PROG_Cfg.h"

#if (PROG_CRY_PRESENT == STD_ON)
#include "Csm.h"
#endif /* (PROG_CRY_PRESENT == STD_ON)*/

/*============================= PUBLIC DEFINITIONS ==============================*/
/*                                                                               */
/*-------------------------------------------------------------------------------*/
/* - Public Variables                                                            */

/* Flag indicating if Response to Prog session from appli shall be done */
extern u8 m_ubSimulateProgSessionWithResponse;

#if (PROG_IMPL_VARIANT == PROG_IMPL_10) || (PROG_IMPL_VARIANT == PROG_IMPL_11)
/* Number of check memory failed requests */
extern u8 m_ubFailedCheckMemoryCount;
/* check memory routine status */
extern u8 m_ubCheckMemoryStatus;
#endif
/*-------------------------------------------------------------------------------*/
/* - Public Function Prototypes                                                  */

#if (PROG_CSM_MAC_USED == STD_ON)
/** \brief Get the key used to compute MAC checksum
 **
 ** This function is called to get the key used for MAC computation
 **
 ** \param[out] pstMacKey Pointer to the Key
 **
 **/
extern void PROG_GetMacKey(Csm_SymKeyType* pstMacKey);
#endif

/** \brief Initialize PROG module **/
extern void PROG_Init(void);
/** \brief Manage function to be called periodically **/
extern void PROG_Manage(void);
/** \brief Manage function to be called as fast as possible to perform
 **               background actions **/
extern void PROG_BckdManage(void);
/** \brief Reception of a programming session request **/
extern void PROG_OpenProgrammingSession (void);
/** \brief request to close the programming session
 **
 ** This function is called to request the close of the programming session
 **
 ** \param[in] eUdsChangeReason reason why the close is requested
 **
 **/
extern void PROG_CloseProgrammingSession (tUdsChangeReason eUdsChangeReason);
/** \brief Reception of a streaming frame
 **
 ** This function is called on reception of a streaming frame
 **
 ** \param[in] ulReceivedDataLength Data Length in the received frame
 ** \param[in] aubData Pointer to buffer where received data are located
 **
 **/
extern void PROG_StreamingFrameReceived(u16 ulReceivedDataLength, u8* aubData);
/** \brief Inform of network status change
 **
 ** This function is called on change of the network status
 **
 ** \param[in] uwNetworkStatus new network status
 **
 **/
extern void PROG_SetNetworkStatus(u16 uwNetworkStatus);
/** \brief Request to simulation a programming session opening **/
extern void PROG_SimulateOpenProgSession(void);
/** \brief called on confirmation of frame transmission
 **
 ** This function is called on confirmation of a diagnostic response
 ** transmission
 **
 ** \param[in] uMsgIdx Identifier of the transmission frame
 ** \param[in] ebStatus status of the transmission
 **
 **/
extern void PROG_TpTxConf(tTpMsgIdx uMsgIdx, u8 ebStatus);

/** \brief called on frame reception
 **
 ** This function is called on a diagnostic frame reception
 **
 ** \param[in] uMsgIdx Identifier of the transmission frame
 ** \param[in] ebStatus status of the transmission
 **
 **/
extern void PROG_TpRxInd(tTpMsgIdx uMsgIdx, u8 ebStatus);

/** \brief called on frame reception
 **
 ** This function is called on a diagnostic frame reception
 **
 ** \param[in] ubStatus status of the transmission
 **
 **/
extern void PROG_TpStartOfReceptionInd(u8 ubStatus);

/** \brief Called on entry to Sleep state **/
extern void PROG_Entry_Sleep(void);

#if ((PROG_WRITE_FINGERPRINT_ENABLE == STD_ON) || (PROG_IMPL_VARIANT == PROG_IMPL_60))
/** \brief Called on entry to WriteFingerprint state **/
extern void PROG_Entry_WriteFingerprint(void);
#endif
#if ((PROG_WRITE_FINGERPRINT_ENABLE == STD_ON) || (PROG_IMPL_VARIANT == PROG_IMPL_60))
/** \brief Called on loop in WriteFingerprint state **/
extern void PROG_WriteFingerprintCheck(void);
#endif
#if (PROG_ECU_RESET_ENABLE == STD_ON)
/** \brief Called on entry to EcuReset state **/
extern void PROG_Entry_EcuReset(void);
#endif
/** \brief Called on entry to Reset state **/
extern void PROG_Entry_Reset(void);
/** \brief Called on entry to DefaultSession state **/
extern void PROG_Entry_DefaultSession(void);
/** \brief Called on entry to ProgrammingSession state **/
extern void PROG_Entry_ProgrammingSession(void);
/** \brief Called on entry to ExtendedSession state **/
extern void PROG_Entry_ExtendedSession(void);

#if ((PROG_SA_SEED_ENABLE == STD_ON) && (PROG_SECURITY_ENABLE == STD_ON))
/** \brief Called on entry to GetSeed state **/
extern void PROG_Entry_GetSeedCheck(void);
/** \brief Called on entry to GetSeed state **/
extern void PROG_Entry_GetSeed(void);
/** \brief API called to get seed **/
extern void PROG_Do_GetSeed(void);
#endif /* ((PROG_SA_SEED_ENABLE == STD_ON) && (PROG_SECURITY_ENABLE == STD_ON)) */

#if (PROG_SA_SEED_ENABLE == STD_ON)
/** \brief Called in GetSeed_Unlocked state **/
extern void PROG_GetSeed_Unlocked(void);
#endif

/** \brief Called in CHECK_MEMORY_FINISH state **/
extern void PROG_AnswerSuccesiveCheckMemoryRequests(void);

#if (PROG_SA_KEY_ENABLE == STD_ON)
/** \brief Called on entry to CompareKey state **/
extern void PROG_Entry_CompareKeyCheck(void);
/** \brief Called on entry to CompareKey state **/
extern void PROG_Entry_CompareKey(void);
/** \brief API called to get seed result **/
extern void PROG_Do_CompareKey(void);
#endif /* (PROG_SA_KEY_ENABLE == STD_ON) */

/** \brief Called on entry to EraseCheck state **/
extern void PROG_Entry_EraseCheck(void);
/** \brief Called on entry to Erase state **/
extern void PROG_Entry_Erase(void);
/** \brief Called in Erase state **/
extern void PROG_Erase(void);
/** \brief Called on entry to EraseNRC78 state  **/
extern void PROG_Entry_EraseNRC78(void);
/** \brief Called on entry to EraseTransmitNRC78 state  **/
extern void PROG_Entry_EraseTransmitNRC78(void);

/** \brief Send the NRC_78 instantaneously to gain time **/
extern void PROG_SendNRC78(void);

#if PROG_REQUEST_DOWNLOAD_ENABLE == STD_ON
/** \brief Called receiving a RD request
 **
 ** \return Result of check
 ** \retval PROG_E_OK RD request accepted
 ** \retval PROG_E_NOT_OK RD request not accepted
 **
 **/
extern tProgStatus PROG_RD_Check(void);
#if (PROG_IMPL_VARIANT == PROG_IMPL_40)
/** \brief Called receiving a RD request after a RTE
 **
 ** \return Result of check
 ** \retval PROG_E_OK RD request accepted
 ** \retval PROG_E_NOT_OK RD request not accepted
 **
 **/
extern tProgStatus PROG_Guard_RD_Check_RTEFinish(void);
#endif
/** \brief Called on entry to RD state **/
extern void PROG_Entry_RD(void);
#endif

#if (PROG_IMPL_VARIANT == PROG_IMPL_40)
/** \brief Called on entry to RD SIGNATURE state **/
extern void PROG_Entry_RD_Signature(void);

/** \brief Called on entry to RD Finish state **/
extern void PROG_Entry_RD_Finish(void);
#endif

#if PROG_TRANSFER_DATA_ENABLE == STD_ON
/** \brief Called on entry to TD state **/
extern void PROG_Entry_TD(void);
/** \brief Called on entry to Streaming state **/
extern void PROG_Entry_Streaming(void);
/** \brief Called in Streaming state **/
extern void PROG_Streaming(void);
/** \brief Called on entry to TD_Failed state **/
extern void PROG_Entry_TD_Failed(void);
/** \brief Called on entry to Write state **/
extern void PROG_Entry_Write(void);
/** \brief Called in Write state **/
extern void PROG_Write(void);
/** \brief Called in WriteCheck state **/
extern void PROG_WriteCheck(void);
/** \brief Called on exit from TD_Write state **/
extern void PROG_Exit_TD_Write(void);
/** \brief Called in TD state **/
extern tProgStatus PROG_TD(void);

#if ((PROG_CRC_CALCULATION != PROG_NO_CRC) || (PROG_SIGNATURE_CALCULATION == STD_ON) || (PROG_HASH_CALCULATION == STD_ON))
/** \brief Called in CRC state **/
extern tProgStatus PROG_VerificationOnTheFly(void);
extern tProgStatus PROG_CRC(void);
extern void PROG_Do_CheckHash(void);
extern void PROG_Entry_CheckHash(void);
#endif
extern void PROG_Do_CheckSignature(void);
#if (PROG_IMPL_VARIANT == PROG_IMPL_20)
extern void PROG_Entry_TD_Header(void);
extern void PROG_SignerInfoCheck(void);
extern void PROG_Entry_ValidateSignerInfo(void);
extern void PROG_SignatureCheck(void);
extern void PROG_Entry_ValidateSignature(void);
#endif /* PROG_IMPL_VARIANT == PROG_IMPL_20 */
#endif /* PROG_TRANSFER_DATA_ENABLE == STD_ON */

extern void PROG_HSMUpdate_TD(void);
extern void PROG_Entry_HSMUpdate_TDFinish(void);
extern void PROG_HSMStatusManage(void);

#if PROG_REQUEST_TRANSFER_EXIT_ENABLE == STD_ON
/** \brief Called on entry to RTEFailed state **/
extern void PROG_Entry_RTEFailed(void);
/** \brief Called on entry to RTE state **/
extern void PROG_Entry_RTE(void);
#if ((PROG_IMPL_VARIANT == PROG_IMPL_1)  || (PROG_IMPL_VARIANT == PROG_IMPL_2) || \
     (PROG_IMPL_VARIANT == PROG_IMPL_3)  || (PROG_IMPL_VARIANT == PROG_IMPL_4) || \
     (PROG_IMPL_VARIANT == PROG_IMPL_10) || (PROG_IMPL_VARIANT == PROG_IMPL_11)|| \
     (PROG_IMPL_VARIANT == PROG_IMPL_60) )
/** \brief Called on cyclically in RTE state **/
extern void PROG_RTE(void);
#endif /* (PROG_IMPL_VARIANT != PROG_IMPL_20) && (PROG_IMPL_VARIANT != PROG_IMPL_30)*/
/** \brief Called on entry to RTEFinish state **/
extern void PROG_Entry_RTEFinish(void);

#if (PROG_IMPL_VARIANT == PROG_IMPL_20)
extern void PROG_ComputeMessageDigest(void);
extern void PROG_MessageDigestCheck(void);
#endif /* #if (PROG_IMPL_VARIANT == PROG_IMPL_20) */
#endif /* #if (PROG_REQUEST_TRANSFER_EXIT_ENABLE == STD_ON) */
/** \brief Called to send negative response
 **
 ** \param[in] eUdsStatus Error code to use in negative response
 **/
extern void PROG_Send_NRC(tUdsStatus eUdsStatus);
/** \brief Check if SBL is valid and compatible
 **
 ** \return Result of check
 ** \retval PROG_E_OK SBL is valid and compatible with PBL
 ** \retval PROG_E_NOT_OK SBL is not valid and/or incompatible with PBL
 **
 **/
extern tProgStatus PROG_ActiveSBL_Check(void);
/** \brief Called on entry to ActiveSBL state **/
extern void PROG_Entry_ActiveSBL(void);
/** \brief Called on entry to SblSynch state **/
extern void PROG_Entry_SblSynch(void);
/** \brief Called to perform the jump to SBL **/
extern void PROG_JumpToSBL(void);
/** \brief Called on entry to AutoControl state **/
extern void PROG_Entry_AutoControl(void);
#if PROG_AUTOCONTROL_ENABLE == STD_ON
#if ((PROG_IMPL_VARIANT == PROG_IMPL_1)||(PROG_IMPL_VARIANT == PROG_IMPL_2) ||\
    (PROG_IMPL_VARIANT == PROG_IMPL_3)||(PROG_IMPL_VARIANT == PROG_IMPL_4))
/** \brief manage asynchronous autocontrol **/
extern void PROG_AutoControl_Process(void);
#endif /*((PROG_IMPL_VARIANT == PROG_IMPL_1)||(PROG_IMPL_VARIANT == PROG_IMPL_2) ||\
            (PROG_IMPL_VARIANT == PROG_IMPL_3)||(PROG_IMPL_VARIANT == PROG_IMPL_4))*/
#endif /* PROG_AUTOCONTROL_ENABLE == STD_ON */

#if ((PROG_APPLI_CHECK_ENABLE == STD_ON) && ((PROG_IMPL_VARIANT == PROG_IMPL_20) || (PROG_IMPL_VARIANT == PROG_IMPL_60)))
/* Exclude doxygen extract as Api already exist in PROG_Cbk.c */
#ifndef DOXYGEN_SHOULD_SKIP_THIS
/** \brief Check if application is valid
 **
 ** \return Result of check
 ** \retval TRUE Application is valid
 ** \retval FALSE Application is not valid
 **
 **/

extern tProgBoolean PROG_IsValidApplication(void);

#endif /* DOXYGEN_SHOULD_SKIP_THIS */
#endif

#if ((PROG_APPLI_CHECK_ENABLE == STD_ON) && (PROG_IMPL_VARIANT == PROG_IMPL_60))
/* Exclude doxygen extract as Api already exist in PROG_Cbk.c */
#ifndef DOXYGEN_SHOULD_SKIP_THIS
/** \brief API that invalidate the application marker
 **
 ** This API is before starting the erasing routine.
 ** It shall invalidate the application or the current erased section to make sure no jump to the application will be done
 ** if an error occurred and the application is not fully erased or reprogrammed
 **
 ** \param[in] Erased Start address of the segment that will be erased
 ** \param[in] ulEraseLength requested erase length
 ** \param[in] ErrorCode UDS error code that shall be return in case of error during API treatment
 **
 ** \return Result application invalidation
 ** \retval PROG_E_OK Treatment finish successfully
 ** \retval PROG_E_NOT_OK Error happened during treatment (ErrorCode shall be filled in this case)
 **/
extern tProgStatus PROG_InvalidateSection(tProgAddressType ulStartAddress, u32 ulEraseLength, tUdsStatus * ErrorCode);
#endif /* DOXYGEN_SHOULD_SKIP_THIS */
#endif

#if (PROG_UPDATE_PSI_ENABLE == STD_ON)
/** \brief Called on entry to UpdatePSI state **/
extern void PROG_Entry_UpdatePSI(void);
#endif

#if (PROG_IMPL_VARIANT == PROG_IMPL_2)
/** \brief Called to write one or more flash pages
 **
 ** This API can be called by the Framework to write one or more
 ** specific flash pages.
 **
 ** \param[in] ulAddress Address of the first page to write
 ** \param[in] ubPages number of pages to write
 ** \param[in] pulDataBuffer pointer to the buffer of data to write
 ** \param[in] uwDataBufferLenght Exact length of data to write
 **
 ** \return Result of the write operation
 ** \retval PROG_FLASH_PAGE_E_OK write is successfull
 ** \retval PROG_FLASH_PAGE_E_NOT_OK write is not successfull
 **/
extern u8 PROG_FlashPage(u32 ulAddress, u8 ubPages, u32* pulDataBuffer, u16 uwDataBufferLenght);
/** \brief Called by the Flash driver to know if the page can be written
 **
 ** This API is called by the Flash driver to know if it is authorized to write a Flash pages.
 ** The API will forward the request to the framework
 **
 ** \param[in] uAddr pointer on Address of the page to write
 **
 ** \return Result of the check
 ** \retval PROG_NO_SKIP_PAGE page can be written
 ** \retval others write is not allowed
 **/
extern u8 PROG_SkipPage(u32* uAddr);
#endif /* (PROG_IMPL_VARIANT == PROG_IMPL_2) */
#if PROG_CHECK_PROGRAMMING_DEPENDENCIES_ENABLE == STD_ON
/** \brief Called to verify if CheckProgDependencies routine can be executed
 **
 ** \return Result of check
 ** \retval PROG_E_OK check is allowed
 ** \retval PROG_E_NOT_OK check is not allowed
 **
 **/
extern tProgStatus PROG_Check_Prg_Dep_Check(void);
/** \brief Called to send CheckProgDependencies routine response  **/
extern void PROG_Entry_CheckDependenciesFinish(void);
/** \brief Called to calculate the CRC for CheckProgDependencies routine **/
extern void PROG_Do_CheckPrgDependencies(void);
#endif /* PROG_CHECK_PROGRAMMING_DEPENDENCIES_ENABLE == STD_ON */



#if (PROG_CRC_CALCULATION == PROG_TD_CRC16)
/** \brief Called to calculate CRC
 **
 ** \param[in] aubCrcData Data to add in the CRC calculation
 ** \param[in] ulReadLength Data length to add in the CRC calculation
 ** \param[out] uwCrcValue Pointer to variable where to set the CRC result
 **/
extern void PROG_CalcCrc16(const u8 * aubCrcData, u32 ulReadLength, u16 * uwCrcValue);
#endif /*(PROG_CRC_CALCULATION == PROG_TD_CRC16)*/
#if (PROG_CRC_CALCULATION == PROG_TD_CRC32)
/** \brief Called to calculate CRC
 **
 ** \param[in] aubCrcData Data to add in the CRC calculation
 ** \param[in] ulReadLength Data length to add in the CRC calculation
 ** \param[out] ulCrcValue Pointer to variable where to set the CRC result
 **/
extern void PROG_CalcCrc32(const u8 * aubCrcData, u32 ulReadLength, u32 * ulCrcValue);
#endif
/** \brief Called on entry to INIT state **/
extern  void PROG_Entry_INIT(void);
/** \brief Called on entry to INIT state **/
extern  void PROG_Exit_INIT(void);

/** \brief Called on entry to PreInit state **/
extern  void PROG_Entry_PreInit(void);
/** \brief Called in PreInit state **/
extern  void PROG_PreInit(void);

/* HsmStub.c  */
/** \brief Called on entry to Alive state **/
extern  void PROG_Entry_Alive(void);
/** \brief Called on entry to EraseFinish state **/
extern void PROG_Entry_EraseFinish(void);

/** \brief Called before going to PROG_Erase state
 **
 ** \return Result of check
 ** \retval PROG_E_OK Erase request accepted
 ** \retval PROG_E_NOT_OK Erase request not accepted
 **
 **/
extern tProgStatus PROG_Erase_Guard(void);

#if PROG_IMPL_VARIANT == PROG_IMPL_20
extern void PROG_Entry_ValidateSBASignerInfo(void);
extern void PROG_SBASignerInfoCheck(void);
extern void PROG_Entry_ValidateSBASignature(void);
extern void PROG_SBASignatureCheck(void);
extern void PROG_Entry_DecompHeader(void);
extern void PROG_CheckDecompHeaderStatus(void);
#endif /* #if PROG_INI_IMPL == PROG_IMPL_20 */
#if (PROG_NETWORK_MANAGEMENT_ENABLE == STD_ON)
/** \brief Function providing the network status
 ** \return Network Status
 **
 **/
extern u16 PROG_GetNetworkStatus(void);
#endif

#define PROG_GET_DID_F0F3_START_SEC_CODE
#include <MemMap.h>
/** \brief Called by external module to get data of DID F0F3
 **
 ** This API is called by an external value to get the data of the DID F0F3
 ** (EcuId)
 **
 ** \param[out] aubData DID data
 **
 **/
extern void PROG_GetDidF0F3(u8 *aubData);
#define PROG_GET_DID_F0F3_STOP_SEC_CODE
#include <MemMap.h>

#define PROG_GET_DID_F0F6_START_SEC_CODE
#include <MemMap.h>
/** \brief Called by external module to get data of DID F0F6
 **
 ** This API is called by an external value to get the data of the DID F0F6
 ** (EcuId)
 **
 ** \param[out] aubData DID data
 **
 **/
extern void PROG_GetDidF0F6(u8 *aubData);
#define PROG_GET_DID_F0F6_STOP_SEC_CODE
#include <MemMap.h>


/** \brief Finishing the checksum  calculation
 **
 ** \return state
 ** \retval PROG_E_OK Calculation finished successfully
 ** \retval PROG_E_BUSY Calculation in progress
 ** \retval PROG_E_NOT_OK Calculation finished on error
 **
 **/
extern tProgStatus PROG_RangeChecksumFinish(void);

/** \brief Init of the Checksum Calculation */
extern void PROG_Entry_ChecksumByRange(void);

/** \brief Update the programming status
 **
 ** \param[in] ulProgrammingStatusMask the mask for a specific failure
 ** \param[in] ubStatus failure status (0 - present, 1 - not present)
 **
 **/
extern void PROG_SetProgrammingStatus(u32 ulProgrammingStatusMask, tProgBoolean ubStatus);

/** \brief Function providing the programming pre-conditions check status
 **
 ** \return Programming Pre-conditions check Status
 **
 **/
extern tProgStatus PROG_CheckProgrammingPreCondition(void);

/** \brief Check memory programming  **/
extern void PROG_Entry_CheckMemory(void);
#if (PROG_CHECK_MEMORY_ENABLE == STD_ON)
/** \brief Called on entry to CHECK_MEMORY_FINISH state  **/
extern void PROG_Entry_CheckMemoryFinish(void);
#endif
#if (((PROG_IMPL_VARIANT == PROG_IMPL_40) || (PROG_IMPL_VARIANT == PROG_IMPL_50) || (PROG_IMPL_VARIANT == PROG_IMPL_60) || (PROG_IMPL_VARIANT == PROG_IMPL_10) || (PROG_IMPL_VARIANT == PROG_IMPL_11)) && (PROG_CHECK_MEMORY_ENABLE == STD_ON))
/** \brief Check memory programming  **/
extern void PROG_Exit_CheckMemory(void);
/** \brief Called on exit to CHECK_MEMORY_FINISH state  **/
extern void PROG_Exit_CheckMemoryFinish(void);
#endif
/** \brief Check memory programming  **/
#if (((PROG_IMPL_VARIANT == PROG_IMPL_40) || (PROG_IMPL_VARIANT == PROG_IMPL_50) || (PROG_IMPL_VARIANT == PROG_IMPL_60))  && (PROG_CHECK_MEMORY_ENABLE == STD_ON))
extern void PROG_Entry_CheckMemoryCompute(void);
extern void PROG_Entry_SignatureCheck(void);
#endif

#if (PROG_IMPL_VARIANT == PROG_IMPL_10) || (PROG_IMPL_VARIANT == PROG_IMPL_11)
/** \brief Called on entry to CHECK_MEMORY_FAILED state  **/
extern void PROG_Impl10_Entry_CheckMemoryFailed(void);
/** \brief Called on entry to RTE_COMPARE_HASH state  **/
extern void PROG_Impl10_CompareDataBlockHash(void);
/** \brief Called on entry to HASH_CHECK**/
extern void PROG_Impl10_CheckDataBlocksResult(void);
/** \brief Called on entry to SIGNATURE_CHECK **/
extern void PROG_Impl10_Entry_SignatureCheck(void);
/** \brief Called on entry to RTE_COMPARE_HASH **/
extern void PROG_Impl10_FinalizeHash(void);
/** \brief Called while RTE_COMPARE_HASH is active, it updates the hash calculation according to the length mentioned in VBT **/
extern void PROG_Impl10_Do_HashMoreUnwrittenData(void);
/** \brief Called on entry to MAC_GENERATATION, it generates the mac for each software part **/
extern void PROG_Impl10_GenerateMac(void);
/** \brief Called on guard of check memory to check whether it is allowed or not  **/
extern tProgStatus PROG_Impl10_CheckMemoryAllowed(void);
/** \brief Called during the write production key state to check if hash is finished **/
extern void PROG_Impl10_Do_CheckHashOfKey(void);
/** \brief Called on when the hash calculation is finished  **/
extern void PROG_Impl10_Entry_WriteKeyFinished(void);
/** \brief Called upon the reception of write key request  **/
extern void PROG_Impl10_Entry_CheckReceivedKey(void);
#endif


/** \brief Compare the expected and the calculated CRCs
 **
 ** \return Result of treatment
 ** \retval PROG_E_OK Compare OK
 ** \retval PROG_E_BUSY Compare in progress
 ** \retval PROG_E_NOT_OK Compare finished on error
 **
 **/
extern tProgStatus PROG_CRC_Compare(void);

#if((PROG_SEG_LIST_CKS == STD_ON) && (PROG_IMPL_VARIANT != PROG_IMPL_10) && (PROG_IMPL_VARIANT != PROG_IMPL_11))
/** \brief API for CRC calculation on all downloaded segments
 **
 **/
extern void PROG_CheckSegmentListCrc(void);
#endif /*#if((PROG_SEG_LIST_CKS == STD_ON) && (PROG_IMPL_VARIANT != PROG_IMPL_10) && (PROG_IMPL_VARIANT != PROG_IMPL_11))*/



/** \brief Called to do the Coherency Check treatment
 **
 **/
extern void PROG_Do_CoherencyCheck(void);


#if PROG_IMPL_VARIANT == PROG_IMPL_50
/** \brief Called to do the Coherency Pre Check treatment
 **
 **/
extern void PROG_Entry_CoherencyPreCheck(void);
#endif /* #if PROG_IMPL_VARIANT == PROG_IMPL_50 */

#if (PROG_CHECK_PROGRAMMING_REQUEST_ENABLE == STD_ON)
/** \brief Check programming request
 **
 ** \return Programming Request Check Status
 **
 **/
extern tProgBoolean PROG_CheckProgrammingRequest(void);
#endif /*#if (PROG_CHECK_PROGRAMMING_REQUEST_ENABLE == STD_ON)*/

#if (PROG_SWITCH_APPLICATION_MODE_ENABLE == STD_ON)
extern void PROG_SwitchApplicationMode(void);
#endif /*#if (PROG_SWITCH_APPLICATION_MODE_ENABLE == STD_ON)*/

extern tProgBoolean PROG_CheckValidAppl (void);

#if (PROG_PROGRAMMING_CNTR_ENABLE == STD_ON)
/** \brief API for checking the programming counter
 **
 ** \param[in] ubBlockId BlockID
 **
 **/
extern tProgStatus PROG_CheckProgrammingCounter(u8 ubBlockId);
#endif /*#if (PROG_PROGRAMMING_CNTR_ENABLE == STD_ON)*/


#if (PROG_PROGRAMMING_CNTR_ENABLE == STD_ON)
/** \brief API for getting the programming counter lock value (maximum programming counter) for a specific block
 **
 ** \param[in] ubBlockId BlockID
 **
 ** \param[out] puwProgCntMax Programming Counter lock value
 **
 ** \return Operation status
 ** \retval PROG_E_OK Block index has been found
 ** \retval PROG_E_NOT_OK Block index has not been found
 **
 **/
extern tProgStatus PROG_GetProgCntrLockVal(u8 ubBlockId, u16* puwProgCntMax);
#endif /*#if (PROG_PROGRAMMING_CNTR_ENABLE == STD_ON)*/


/** \brief Called on VerifyPartialSoftwareChecksum routine reception
 **
 **/
extern void PROG_Entry_PartialVerificationCrc(void);

/** \brief Called on VerifyPartialSoftwareChecksum routine reception
 **
 **/
extern void PROG_Exit_PartialVerificationCrc(void);


/** \brief This API allow to perform the partial software CRC computation over all programmed segment
 **
 **/
extern void PROG_CheckPartialSegmentListCrc(void);


/** \brief This API allow to perform the partial software CVN check
 **
 **/
#if (PROG_CVN_CHECK == STD_ON)
extern tProgStatus PROG_CheckPartialSwCvnStatus(tProgStatus eProgStatus);
#endif /* PROG_CVN_CHECK == STD_ON */

#if ((PROG_AUTHENTICATED_BOOT_ENABLE == STD_ON) && (PROG_BOOT_VERIFICATION == STD_ON))
/** \brief API for getting the previously computed Bootloader checksum
 **
 ** \param[out] pubComputedChecksum Computed Checksum (if return is PROG_E_OK)
 **
 ** \return Operation status
 ** \retval PROG_E_OK Checksum has been provide
 ** \retval PROG_E_NOT_OK Checksum is invalid and cannot be provided
 **
 **/
extern tProgStatus PROG_GetComputedBootloaderChecksum(u8 * pubComputedChecksum);
#endif


#if ((PROG_DOWNLOAD_FLASH_ROUTINES_ENABLE == STD_ON) || (PROG_DECOMP_FLASH_ROUTINES == STD_ON))
/** \brief Returns the value of m_ubFlashRoutinesPresent, that represents the presence
 **        of the flash routines in RAM
 **
 ** This function is called to verify the presence of the flash routines
 **
 ** \return Result of treatment
 ** \retval PROG_TRUE Flash routines are present in RAM
 ** \retval PROG_FALSE Flash routines are not present in RAM
 **/
extern tProgBoolean PROG_DrvDown_IsFlashRoutinesPresent(void);
#endif

#if (PROG_IMPL_VARIANT == PROG_IMPL_50)
/** \brief Entry function for Resume verification state  **/
extern void PROG_Entry_ResumeVerification(void);

/** \brief Entry function for Resume verification state  **/
extern void PROG_Entry_Resume_Finish(void);

/** \brief Provide next segment to verify
 **
 ** This function is called after verification of a segment to get
 ** information of the next segment
 **
 **/
extern void PROG_ResReprog_CheckSegmentListVerif(void);
#endif

/** \brief Send response in the case of a failure on secure checksum calculation
 **
 ** This function is called at the end of the Check Memory in the case of
 **  a failure on secure checksum calculation
 **
 **/
extern void PROG_Entry_SecureChecksumFailed(void);
/*                                                                               */
/*-------------------------------------------------------------------------------*/


#endif      /* PROG_PUB_H */
