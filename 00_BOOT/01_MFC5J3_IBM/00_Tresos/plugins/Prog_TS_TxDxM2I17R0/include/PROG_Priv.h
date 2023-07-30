#ifndef PROG_PRIV_H
#define PROG_PRIV_H

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
/*%%   _____________________________   %%  \file PROG_Priv.h                     */
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
/* Copyright 2010 by Elektrobit Automotive GmbH                                  */
/* All rights exclusively reserved for Elektrobit Automotive GmbH,               */
/* unless expressly agreed to otherwise.                                         */
/*===============================================================================*/

#include "PROG_Cfg.h"
#if (PROG_CRY_PRESENT == STD_ON)
#include "PROG_Cry.h"
#endif
#if ((PROG_COMPRESSION_ENABLE == STD_ON) && (PROG_CAL_PRESENT == STD_ON))
#include "Cal.h"
#endif

/*============================ PRIVATE DEFINITIONS ==============================*/

/*-------------------------------------------------------------------------------*/
/* - Private Variables                                                           */
/*                                                                               */

/*===============================================================================*/

/*-------------------------------------------------------------------------------*/
/* - Private Macros                                                              */
#define PROG_NO_EVENT       0xFFU
#define PROG_NO_AUTHENT     0x00U
#define PROG_BOOT_AUTHENT   0x01U
#define PROG_APP_AUTHENT    0x02U
#define PROG_LOGICAL_BLOCK_VALUE_INIT  0xFEU
/*                                                                               */
/*===============================================================================*/

/*-------------------------------------------------------------------------------*/
/* - Private Function Prototypes                                                 */
/*                                                                               */

/*===============================================================================*/

/*============================= PUBLIC DEFINITIONS ==============================*/
/*                                                                               */
/*-------------------------------------------------------------------------------*/
/* - Public Variables                                                            */
/** \brief structure for Diagnostic request/response informations               **/
#if ( ((PROG_IMPL_VARIANT == PROG_IMPL_10) || (PROG_IMPL_VARIANT == PROG_IMPL_20) || (PROG_IMPL_VARIANT == PROG_IMPL_60) ) && (PROG_RESPOND_TO_PROG_SESSION == STD_ON))
extern tProgBoolean m_ubSendResponsetoOpenProgramming;
#endif
extern u8 m_ubEvenToPost; /* contains the vent to post at initialization after SBA vaticket validation*/
extern tDiagMessageInfo m_stDiagMessageInfo; /* Contains request information */
extern tSegmentType m_stCurrentSegment; /* Information concerning the current transfer data operation */
extern tProgVerificationInfo m_stDataProgVerification; /* Information for the programming verification */
extern tReprogInfo m_stReprogInfo;
/* Information concerning the current transfer data operation */
extern tWriteInfo m_stWriteInfo;

#if (PROG_SLEEP_MANAGEMENT_TYPE == PROG_SLEEP_MANAGEMENT_TIMEOUT)
extern tProgBoolean m_ubBootInDefaultSession; /* Flag to indicate if the bootloader is in default session  */
#endif

#if PROG_SIGNATURE_CALCULATION == STD_ON
extern u8 m_aubExpectedSignature[PROG_SIGNATURE_LENGTH];
#endif

#if (PROG_CRY_PRESENT == STD_ON)
#if PROG_HASH_CALCULATION == STD_ON
extern u8 m_aubComputedMessageDigest[PROG_DIGEST_LENGTH];
#endif
#endif /* #if (PROG_CRY_PRESENT == STD_ON) */

#if (PROG_VERIFICATION_ON_THE_FLY == STD_ON) || (PROG_SIGNATURE_CALCULATION == STD_ON)
#if (PROG_CRY_PRESENT == STD_ON)
extern Csm_AsymPublicKeyType m_stProgAsymPublicKey;
#endif
#endif

extern u8 m_ubProgIsInit; /* Flag to indicate if the bootloader is initialized  */
#if (((PROG_AUTOCONTROL_ENABLE == STD_ON) && ((PROG_IMPL_VARIANT == PROG_IMPL_1) || (PROG_IMPL_VARIANT == PROG_IMPL_2))) \
    || ((PROG_ERASE_MEMORY_ENABLE == STD_ON) && (PROG_IMPL_VARIANT == PROG_IMPL_2)) \
    || ((PROG_PRE_INIT_ENABLE == STD_ON) && ((PROG_IMPL_VARIANT == PROG_IMPL_1)||(PROG_IMPL_VARIANT == PROG_IMPL_2))))
extern u32* pulProgFramework_Api_Array_Ptr;
#endif
#if (PROG_CRY_PRESENT == STD_ON)
extern const uint8 m_aKeyModulus[PROG_MODULUS_SIZE];
extern const uint8 m_aKeyPublicExponent[PROG_EXPONENT_SIZE];
#endif
#if PROG_PEC_ENABLE == STD_ON
extern tProgPECError m_uwPEC;
#endif

#if (((PROG_CRC_COMPUTE_COMPARE_ENABLE == STD_ON) || (PROG_SEG_LIST_CKS == STD_ON)) && (PROG_CHECK_MEMORY_ENABLE == STD_ON) && (PROG_IMPL_VARIANT != PROG_IMPL_10) && (PROG_IMPL_VARIANT != PROG_IMPL_11))
#if (PROG_CRC_CALCULATION == PROG_TD_CRC32)
extern u32 m_ulExpectedCks;
#elif (PROG_CRC_CALCULATION == PROG_TD_CRC16)
extern u16 m_uwExpectedCks;
#endif
#endif

#if(PROG_SEG_LIST_CKS == STD_ON)
extern tSegmentListType m_stSegList;
#endif

#if (PROG_IMPL_VARIANT == PROG_IMPL_20)
extern u8 m_ubNormComEnabled; /* Information if normal Communication is enabled
                        (no reception of CommunicationControl request) */
extern u8 m_ubIsLocked; /* Information if ECU is locked
                        (no reception of SecurityAccess request) */
extern tBootStatus m_stBootStatus;
/* Buffer use to copy the manage the SBA ticket and AppSwInfo from RAM */
extern u8 m_aubSwInfo[1024];
extern u16 m_uwKeyNBID;
#endif
#if ((PROG_IMPL_VARIANT == PROG_IMPL_10) || (PROG_IMPL_VARIANT == PROG_IMPL_11))
extern tProgBoolean m_ubVerificationTablePresent;
#if(PROG_IMPL_VARIANT == PROG_IMPL_10)
extern tProgStatus m_ubSblVerficationStatus;
#endif
#endif

#if (PROG_PARTIAL_VERIFY_CRC == STD_ON)
extern u8 m_ubActivePartialVerifyCrc;
#endif

#if (PROG_CVN_CHECK == STD_ON)
extern tProgBoolean m_eCvnCheckInProgress;
#endif /* PROG_CVN_CHECK == STD_ON */

#if ((PROG_COMPRESSION_ENABLE == STD_ON) && (PROG_CAL_PRESENT == STD_ON))
/* Decompression context structure for CAL/CPL libraries */
extern Cal_DecompressCtxBufType m_stProgCplContext;
#endif

#if(PROG_MULTIPLE_BUFFERS_ENABLE == STD_ON)
extern tMultipleBuffReprogInfo m_stMultipleBuffers;
extern tEventInfo m_stEventInfo;
#endif

extern u8 * m_pubLastBufTxData;

#if PROG_HSM_UPDATE_ENABLE == STD_ON
extern u8 m_aubHsmbuffer[PROG_HSM_BUFFER_LENGTH];
extern u16 m_uwHsmbufferlength;
extern u16 m_uwHSMTimeoutCnt;
#endif
/*-------------------------------------------------------------------------------*/
/* - Public Function Prototypes                                                  */

#if PROG_TRANSFER_DATA_ENABLE == STD_ON
/** \brief Increment block sequence counter for TransferData process **/
INLINE extern void PROG_IncrementBlockSequenceCounter(void);
#endif

/* PROG_Prg.c */

/** \brief Set the size and address for CRC process
 **
 ** This function allow to set the address and size for the CRC calculation
 **
 ** \param[in] ulAddress start address for CRC calculation
 ** \param[in] ulSize length of data to calculate CRC on
 ** \param[in] ubAlgo algorithm to be used: PROG_VERIF_CRC, PROG_VERIF_SIGNATURE,PROG_VERIF_HASH
 ** \param[in] ubContinue boolean to avoid initialization
 **
 **/
extern void PROG_CRCSetParam(u32 ulAddress, u32 ulSize, tProgVerifAlgo ubAlgo, u8 ubContinue);
/** \brief Return the current CRC value
 **
 ** This function allow to return the current CRC value
 **
 ** \param[out] puwCrcVal CRC value returned
 **
 **/
#if ((PROG_CRC_CALCULATION == PROG_TD_CRC16) || (PROG_CRC_CALCULATION == PROG_TD_CRC_CUST))
extern void PROG_GetCrcValue(u16* puwCrcVal);
#elif (PROG_CRC_CALCULATION == PROG_TD_CRC32)
extern void PROG_GetCrcValue(u32* pulCrcVal);
#endif

#if (((PROG_IMPL_VARIANT == PROG_IMPL_10) || (PROG_IMPL_VARIANT == PROG_IMPL_20) || (PROG_IMPL_VARIANT == PROG_IMPL_30) || (PROG_IMPL_VARIANT == PROG_IMPL_60)) && ((PROG_RESPOND_TO_PROG_SESSION == STD_ON)))
extern void PROG_SendDsc02Resp(void);
#endif

#if PROG_SECURITY_ENABLE == STD_ON
/** \brief Set the current security level
 **
 ** \param[in] ubSecurityLevel security level to set
 **
 **
 **/
extern void PROG_SetSecurityLevel(u8 ubSecurityLevel);
#endif
#if (((PROG_ERASE_MEMORY_ENABLE == STD_ON)&&(PROG_ERASE_TYPE == PROG_ERASE_BY_ADDR))||(PROG_REQUEST_DOWNLOAD_ENABLE == STD_ON))
/** \brief Check and Get segment configuration by providing a memory address
 **
 ** \param[in] ulMemoryAddress memory address
 ** \param[in] ulMemoryLength memory length
 ** \param[in] eAccessType access type requested on this memory
 ** \param[out] pubSegmentId index of the matching segment in configuration
 **
 ** \return Result of treatment
 ** \retval PROG_E_OK  Segment found
 ** \retval PROG_E_NOT_OK Segment not found
 **
 **/
extern tProgStatus PROG_GetSegmentByAddress(u32 ulMemoryAddress,
        u32 ulMemoryLength, tOperationType eOperationType, u8 * pubSegmentId);
#endif
#if (((PROG_DOWNLOAD_TYPE == PROG_DOWNLOAD_BY_LOGICAL_BLOCK) || (PROG_DOWNLOAD_TYPE == PROG_DOWNLOAD_BY_LOGICAL_BLOCK_SEGMENT)) && (PROG_REQUEST_DOWNLOAD_ENABLE == STD_ON))
/** \brief Check and Get segment configuration by providing the segment ID
 **
 ** \param[in] ubBlockId block table id
 ** \param[in] ubSegmentId segment id
 ** \param[in] ulMemoryLength memory length
 ** \param[out] pulMemoryAddress memory address
 ** \param[out] pubSegmentId segment id
 **
 ** \return Result of treatment
 ** \retval PROG_E_OK  Segment found
 ** \retval PROG_E_NOT_OK Segment not found
 **
 **/
extern tProgStatus PROG_GetSegmentBySegmentId(u8 ubBlockId, u8 ubSegmentId, u32 ulMemoryLength, u32* pulMemoryAddress, u8 * pubSegmentId);
#endif /*(((PROG_DOWNLOAD_TYPE == PROG_DOWNLOAD_BY_LOGICAL_BLOCK) || (PROG_DOWNLOAD_TYPE == PROG_DOWNLOAD_BY_LOGICAL_BLOCK_SEGMENT)) && (PROG_REQUEST_DOWNLOAD_ENABLE == STD_ON))*/

/* PROG_Customer.c  */

#if ((PROG_APPLI_CHECK_ENABLE == STD_ON) && (PROG_IMPL_VARIANT == PROG_IMPL_60))
/** \brief This API called after comparing the expected CRC and the calculated one.
 **
 ** \param[in] ubLogicalBlockId The id of the logical bloc for witch the compare was done
 ** \param[in] ubLogicalSegmentId The id of the logical segment  for witch the compare was done
 ** \param[in] ubCompareSuccess TRUE if the 2 elements of the compare are identical
 **
 ** \return Result of treatment
 ** \retval PROG_E_OK write marker successful
 ** \retval PROG_E_NOT_OK write marker finish with error
 **
 **/
extern tProgStatus PROG_CustomSetDownloadVerificationSuccess(u8 ubLogicalBlockId, u8 ubLogicalSegmentId, tProgBoolean ubCompareSuccess);
#endif
#if PROG_ERASE_MEMORY_ENABLE == STD_ON
#if PROG_ERASE_TYPE == PROG_ERASE_BY_ADDR
/** \brief Notification of erasing start
 **
 ** This function is called just before starting erasing
 ** It allows performing action or check erasing authorisation
 ** the function automatically sends
 **
 **
 ** \param[in] ulStartAddress start address of the section to erase
 ** \param[in] ulEraseLength length of data to erase
 ** \param[out] ErrorCode in case of NOK status, it contains the error code to send on the network
 **
 ** \return Result of treatment
 ** \retval PROG_E_OK  erasing can be done
 ** \retval PROG_E_NOT_OK  erasing cannot be done
 **
 **/
extern tProgStatus PROG_MemStartErasing(tProgAddressType ulStartAddress, u32 ulEraseLength, tUdsStatus * ErrorCode);
#elif ((PROG_ERASE_TYPE == PROG_ERASE_BY_BLOCK_ID) || (PROG_ERASE_TYPE == PROG_ERASE_BY_DYNAMIC_PARTITION_ID))
/** \brief Notification of erasing start
 **
 ** This function is called just before starting erasing
 ** It allows performing action or check erasing authorisation
 ** the function automatically sends
 **
 **
 ** \param[in] ubBlockId block id
 ** \param[out] ErrorCode in case of NOK status, it contains the error code to send on the network
 **
 ** \return Result of treatment
 ** \retval PROG_E_OK  erasing can be done
 ** \retval PROG_E_NOT_OK  erasing cannot be done
 **
 **/
extern tProgStatus PROG_MemStartErasing(u8 ubBlockId, tUdsStatus * ErrorCode);
#endif
#endif

/* PROG_Mem.c  */

/** \brief Perform memory access
 **
 ** This function is called to perform an access (write, read, erase)
 ** in the memory
 **
 ** \param[in] eMemType type of memory to check: FLASH, FLASH_EXT, RAM
 ** \param[in] eOperationType type of the memory access (write, read, erase)
 ** \param[in] uMemAddress address to access
 ** \param[in] uLength Data length
 ** \param[in,out] paubDataBuffer pointer to buffer where data shall be set/get
 **
 ** \return Result of treatment
 ** \retval PROG_E_OK  memory access is successfull
 ** \retval PROG_E_NOT_OK  memory access failed
 ** \retval PROG_E_BUSY  memory access is in progress
 **
 **/
extern tProgStatus PROG_MemDataAccess
(
    tProgMemType                        eMemType,
    tOperationType                      eOperationType,
    tProgAddressType                    uMemAddress,
    tDataLength                         uLength,
    tDataBufferType PROG_FAR_POINTER    paubDataBuffer
);

#if ((PROG_FLASH_MODE == PROG_MEMORY_ASYNCHRONOUS) || (PROG_FLASH_EXT_MODE == PROG_MEMORY_ASYNCHRONOUS) || (PROG_CUSTOM_MEMORY_MODE == PROG_MEMORY_ASYNCHRONOUS))
/** \brief Check status of memory access
 **
 ** This function is called to identify the status of the previously
 ** memory access request
 **
 ** \param[in] eMemType type of memory to check: FLASH, FLASH_EXT, RAM
 **
 ** \return Result of treatment
 ** \retval PROG_E_OK  memory access is successful
 ** \retval PROG_E_NOT_OK  memory access failed
 ** \retval PROG_E_BUSY  memory access is in progress
 **
 **/
extern tProgStatus PROG_MemJobResult(tProgMemType eMemType);
#endif
#if (PROG_SLICED_ERASING_FOR_NRC78_SENDING == STD_ON)
tProgAddressType PROG_MemGetNextSectorAddr(tProgMemType eMemType, tProgAddressType uCurrentSectorAddr);
#endif /* PROG_SLICED_ERASING_FOR_NRC78_SENDING == STD_ON */

/** \brief Set the timeout value
 **
 ** This function is called to start and stop the sleep timeout
 **
 ** \param[in] TimeoutValue Value to set for timeout, 0 means stop
 **
 **/
#if (PROG_SLEEP_MANAGEMENT_TYPE == PROG_SLEEP_MANAGEMENT_TIMEOUT)
extern void PROG_SetSleepTimeout(u32 ulTimeoutValue);
#endif

#if ((PROG_IMPL_VARIANT == PROG_IMPL_20) ||  (PROG_IMPL_VARIANT == PROG_IMPL_60) || (PROG_IMPL_VARIANT == PROG_IMPL_11))
/** \brief Check if the memory type in the function parameter is well erased or not
 **
 ** \param[in] eMemType Memory Type
 ** \param[in] uMemAddress Address of the memory defined by eMemType
 **
 ** \return Result of treatment
 **/
extern tProgStatus PROG_MemCheckPageErasing
(
        tProgMemType                        eMemType,
        tProgAddressType                    uMemAddress
);
#endif

#if (PROG_IMPL_VARIANT == PROG_IMPL_20)
/** \brief Check ECU name compare to store one
 **
 ** \param[in] ubPartitionId partition ID to check
 ** \param[in] pubValToCheck PSI value to compare to
 **
 ** \return Result of treatment
 ** \retval PROG_E_OK PSI value correct
 ** \retval PROG_E_CHECK_FAILED PSI value different to the asked one
 ** \retval PROG_E_NOT_OK Partition ID out of range
 **/
extern tProgStatus PROG_CheckPSIValue(u8 ubPartitionId, tProgPsiValue ePsiValue);

/** \brief Start of validation of SBA ticket and sending the event as return value*/
extern u8 PROG_ValidateSBATicket(void);


/** \brief Allow to get the module partionID and the module index
 **
 ** \param[in] uwModuleId module ID to check
 ** \param[out] pubPartitionId partition ID found
 ** \param[out] pubModuleIndex Module index found
 **
 ** \return Result of treatment
 ** \retval PROG_E_OK Partition ID was found
 ** \retval PROG_E_NOT_OK Partition ID was found
 **/
extern tProgStatus PROG_GetModulePartition(u16 uwModuleId, u8 * pubPartitionId, u8 * pubModuleIndex);

extern tProgStatus PROG_GetPSIAddress(u8 ubPartitionId, u32* pulPSIAddress);

extern tProgStatus PROG_MemDataAccessByRegion
(
        tProgMemType eMemType,
        tOperationType eOperationType,
        tProgAddressType uMemAddress,
        u32* pulLength,
        tDataBufferType* paubDataBuffer
);

#endif

#if (PROG_CRY_PRESENT == STD_ON)
#if (PROG_CSM_MAC_USED == STD_ON)
/** \brief Starting the Mac generation
 **
 ** \param[in] uwCsmConfigId Id of the Csm configuration used
 ** \param[in] pubData pointer to the data to compute (NULL_PTR if no data provided)
 ** \param[in] ulDataSize Length of data to compute
 ** \param[in,out] pubMacResult pointer where to store the Mac value
 **
 ** \return Result of start
 ** \retval PROG_E_OK start ok
 ** \retval PROG_E_NOT_OK Start failed
 **/
extern tProgStatus PROG_MacGenerateStart(u16 uwCsmConfigId, u8 const * pubData, u32 ulDataSize, u8 * pubMacResult);
#endif

#if PROG_HASH_CALCULATION == STD_ON
/** \brief Starting the Hash calculation
 **
 ** \param[in] uwCsmConfigId Id of the Csm configuration used
 ** \param[in] pubData pointer to the data to compute (NULL_PTR if no data provided)
 ** \param[in] ulDataSize Length of data to compute
 ** \param[in] pubHashResult pointer where to store the hash value
 **
 ** \return Result of start
 ** \retval PROG_E_OK start ok
 ** \retval PROG_E_NOT_OK Start failed
 **/
extern tProgStatus PROG_ComputeHashStart(u16 uwCsmConfigId, u8 const * pubData,u32 ulDataSize, u8 * pubHashResult);

/** \brief Update of the Hash calculation
 **
 ** \param[in] pubData pointer to the data to compute
 ** \param[in] ulDataSize Length of data to compute
 **
 **/
extern void PROG_ComputeHashUpdate(u8 const * pubData, u32 ulDataSize);

/** \brief Finishing the Hash calculation
 **
 ** \param[out] pubHashValue pointer to the buffer to store hash result
 **
 **/
extern void PROG_ComputeHashFinish(u8* pubHashValue);
#endif /* PROG_HASH_CALCULATION == STD_ON */

#if PROG_SINGLE_STEP_SIGNATURE_CHECK == STD_ON
/** \brief Perform signature verification
 **
 ** \param[in] pstPublicKey pointer to the public key
 ** \param[in] pubData Pointer to the data to sign
 ** \param[in] uwDataSize Length of the data to sign
 ** \param[in] pubSignature Signature to verify
 **
 **/
extern tProgStatus PROG_VerifySignature(const Csm_AsymPublicKeyType* pstAsymPublicKey, u8* pubData, u32 ulDataSize, const u8* pubSignature);
#endif

#if (PROG_SIGNATURE_CALCULATION == STD_ON)
/** \brief Start signature verification
 **
 ** \param[in] pstPublicKey pointer to the public key
 ** \param[in] pubSignature pointer to the expected signature if available, NULL_PTR if not available
 **
 **/
extern tProgStatus PROG_VerifySignatureStart(const Csm_AsymPublicKeyType* pstAsymPublicKey, const u8* pubSignature);

/** \brief Update of the Signature verification
 **
 ** \param[in] pubData pointer to the data to compute
 ** \param[in] ulDataSize Length of data to compute
 **
 **/
extern void PROG_VerifySignatureUpdate(u8 const * pubData, u32 ulDataSize);

/** \brief Finish the Signature verification
 **
 ** \param[in] pubSignature pointer to the expected signature if available, NULL_PTR if not available
 **
 **/
extern void PROG_VerifySignatureFinish(const u8* pubSignature);
#endif /*(PROG_SIGNATURE_CALCULATION == STD_ON)*/

/** \brief Get the cryptography status
 **
 ** \return Result of treatment
 ** \retval PROG_E_OK Cryptography finished successfully
 ** \retval PROG_E_BUSY Cryptography calculation in progress
 ** \retval PROG_E_NOT_OK Cryptography finished on error
 **
 **/
extern tProgStatus PROG_GetCryptoStatus(void);

/** \brief Get the cryptography state
 **
 ** \return state
 ** \retval PROG_IDLE
 ** \retval PROG_SIGNATURE_CHECK_START
 ** \retval PROG_SIGNATURE_CHECK_UPDATE
 ** \retval PROG_SIGNATURE_CHECK_FINISH
 ** \retval PROG_HASH_START
 ** \retval PROG_HASH_START_END
 ** \retval PROG_HASH_UPDATE
 ** \retval PROG_HASH_END
 ** \retval PROG_HASH_FINISH
 **
 **/
extern tProgCryState PROG_GetCryptoState(void);
#endif

#if (PROG_SIGNATURE_CALCULATION == STD_ON)
#if (PROG_CRY_PRESENT == STD_ON)
extern void PROG_GetPublicKey(Csm_AsymPublicKeyType* pstPublicKey);
#endif
#endif

#if (PROG_UPDATE_PSI_ENABLE == STD_ON)
extern void PROG_WritePSIValue(u8 ubPartitionId, tProgPsiValue ePsiValue, tUdsStatus* peUdsStatus);
#endif

#if ((PROG_TRANSFER_DATA_ENABLE == STD_ON) && (PROG_IMPL_VARIANT == PROG_IMPL_20))
extern u8* PROG_GetPartitionAddrInAppSWInfo(u8* pubHeaderAddr, u8 ubPartitionId, u16 uwRamAccess);
#endif

#if ((PROG_ERASE_MEMORY_ENABLE == STD_ON) && (PROG_IMPL_VARIANT == PROG_IMPL_20))
extern tProgStatus PROG_InvalidateSection(u8 ubPartitionId);
#endif

/** \brief Request to simulation a programming session opening **/
extern void PROG_SimulateOpenProgSessionNoResponse(void);

#if (PROG_DSC02_DENIED_IN_DEF_SESSION == STD_ON)
/** \brief Request to simulation an Extended session **/
extern void PROG_SimulateExtendedSessionNoResponse(void);
#endif

#if (PROG_RESET_CAUSE_ENABLE == STD_ON)
/** \brief Request to simulation a programming session closing **/
extern void PROG_SimulateCloseProgSession(void);
#endif
/** \brief Request to simulation an ECU Reset **/
extern void PROG_SimulateER(void);
/** \brief Initialize PROG_Mem file variable **/
extern void PROG_MemInit(void);

#if (PROG_RESET_CAUSE_ENABLE == STD_ON)
/** \brief Send a response after reset if needed
 **
 ** \param[in] ubResetCause The cause of the reset
 ** \param[in] ubSendResp The need of sending a response after the reset
 **
 **/
extern void PROG_SendRespAfterReset(tProgResCause ubResetCause, tProgBoolean ubSendResp);
#endif

/** \brief Retrieve 32 bits requested data from buffer
 **
 ** \return Result of treatment
 ** \param[in] ubStartIndex Start index of the buffer
 **
 **/
extern u32 PROG_RetrieveRequestData32(u16 uwStartIndex);

/** \brief Retrieve 16 bits requested data from buffer
 **
 ** \return Result of treatment
 ** \param[in] ubStartIndex Start index of the buffer
 **
 **/
extern u16 PROG_RetrieveRequestData16(u16 uwStartIndex);

/** \brief Post event in state machine on reception of Diagnostic request
 **
 ** This function is called to on reception of a diagnostic request in order
 ** to post an event in state machine indicating the request reception
 **
 ** \param[in] puwLen Request data length
 ** \param[in] aubUdsData Request data
 ** \param[in] EventToPost identifier of the event to post in state machine
 **
 ** \return Result of treatment
 ** \retval UDS_NRC_78  Request management is pending
 **
 **/
extern tUdsStatus PROG_GenericRequest(u16 *puwLen, u8 *aubUdsData,
        u8 EventToPost);

#if ((PROG_CHECK_PROGRAMMING_DEPENDENCIES_REQUEST_ENABLE == STD_ON) && (PROG_IMPL_VARIANT == PROG_IMPL_20))
/** \brief Impl20 specific implementation of routine CheckProgrammingDependencies **/
extern tUdsStatus PROG_CheckProgrammingDependencies_Impl20(u16 *puwLen, u8 *aubUdsData);
#endif

#if ((PROG_SECURE_BOOT_CHECKSUM_COMPUTATION == STD_ON) || (PROG_SECURE_APPLI_CHECKSUM_COMPUTATION == STD_ON))
/** \brief Initialize security features
 **
 ** This function is called at Bootloader initialization
 **
 **/
extern void PROG_SecurityInit(void);

/** \brief Notify the end of Hash computation
 **
 ** This function is called when cryptography library
 ** notify the end of the hash computation
 **/
extern void PROG_SecurityChecksumNotification(void);

/** \brief Indicate if there is a security operation in progress
 **
 ** This function is called before processing a request
 ** requiring security functions
 **/
extern tProgBoolean PROG_SecurityPendingOperation(void);
#endif

#if (PROG_SECURE_APPLI_CHECKSUM_COMPUTATION == STD_ON)
/** \brief Start Application checksum computation
 **
 ** This function is called before sending response
 ** to CheckMemory request for authenticated block
 ** to perform Application checksum computation
 **
 **/
extern void PROG_SecurityComputeAppChecksum(void);
#endif

#if (PROG_SECURE_BOOT_CHECKSUM_COMPUTATION == STD_ON)
/** \brief Start Bootloader checksum computation
 **
 ** This function is called at Bootloader initialization
 ** to perform Bootloader checksum computation
 **
 **/
extern void PROG_SecurityComputeBootChecksum(void);

/** \brief Store a pending event during security computation
 **
 ** This function is called when an event cannot be processed
 ** due to security computation in progress. The event will be stored
 ** and managed after security computation is finished
 **
 ** \param[in] EventToPost event to store
 **/
extern void PROG_SecurityStorePendingEvent(u8 EventToStore);
#endif

#if ((PROG_DOWNLOAD_FLASH_ROUTINES_ENABLE == STD_ON) || (PROG_DECOMP_FLASH_ROUTINES == STD_ON))
/** \brief Verify if we can execute the transition to RD or Erase state
 **
 ** This function is called by the guards of the RD and Erase transitions
 **
 ** \return Result of treatment
 ** \retval PROG_E_OK Transition is authorized
 ** \retval PROG_E_NOT_OK Transition is not authorized
 **/
extern tProgStatus PROG_DrvDown_VerifyTransition(void);
#endif


#if PROG_DOWNLOAD_FLASH_ROUTINES_ENABLE == STD_ON
/** \brief Erase the flash routines downloaded to RAM
 **
 ** This function is called before reset in order to erase the flash routines.
 **
 **/
extern void PROG_DrvDown_EraseFlashRoutines(void);
#endif


#if ((PROG_DOWNLOAD_FLASH_ROUTINES_ENABLE == STD_ON) || (PROG_DECOMP_FLASH_ROUTINES == STD_ON))
/** \brief Before going to RD state, verify that the Flash routines are present/uncorrupted or not in RAM
 **
 ** This function is called by the PROG_RD_Check function
 **
 ** \return Result of treatment
 ** \retval PROG_E_OK Current segment is RAM or the Flash routines are present and not corrupted
 ** \retval PROG_E_NOT_OK Flash routines are not present/or corrupted in RAM and current segment is Flash or FlashExt
 **/
extern tProgStatus PROG_DrvDown_RD_Check(u8 ubLocalSegmentId);
#endif

#if PROG_DOWNLOAD_FLASH_ROUTINES_ENABLE == STD_ON
/** \brief Returns the value of m_ubFlashRoutinesCorrupted, that represents the corruption
 **        of the flash routines in RAM
 **
 ** This function is called to verify if the downloaded flash routines are corrupted
 **
 ** \return Result of treatment
 ** \retval PROG_TRUE Flash routines are corrupted in RAM (check memory failed)
 ** \retval PROG_FALSE Flash routines are not corrupted in RAM (check memory succeeded)
 **/
extern tProgBoolean PROG_DrvDown_IsFlashRoutinesCorrupted(void);
#endif


#if ((PROG_DOWNLOAD_FLASH_ROUTINES_ENABLE == STD_ON) || (PROG_DECOMP_FLASH_ROUTINES == STD_ON))
/** \brief Sets the value of m_ubFlashRoutinesPresent, that represents the presence
 **        of the flash routines in RAM
 **
 ** This function is called to change the status of the presence of the flash routines
 **
 ** \param[in] eProgPresent the presence of the flash routines in RAM
 ** it's set to PROG_TRUE after successful check memory
 ** it's set to PROG_FALSE after erasing the flash routines
 **
 **/
extern void PROG_DrvDown_SetFlashRoutinesPresence(tProgBoolean eProgPresent);
#endif


#if PROG_DOWNLOAD_FLASH_ROUTINES_ENABLE == STD_ON
/** \brief Sets the value of m_ubFlashRoutinesCorrupted, that represents the corruption
 **        of the flash routines in RAM
 **
 ** This function is called to changed the status of corruption of the flash routines
 **
 ** \param[in] eProgCorruption the corruption of the flash routines in RAM
 **
 **/
extern void PROG_DrvDown_SetFlashRoutinesCorruption(tProgBoolean eProgCorruption);
#endif


#if (PROG_IMPL_VARIANT == PROG_IMPL_20)
/** \brief initialization function related to profile 20, only initialize variables related to profile 20
 **/
extern void PROG_Init_Impl20(void);
#endif

#if ((PROG_IMPL_VARIANT == PROG_IMPL_10) || (PROG_IMPL_VARIANT == PROG_IMPL_11))
/** \brief initialization function related to profile 20, only initialize variables related to profile 10
 **/
extern void PROG_Init_Impl10(void);
/** \brief checks whether the given address is for VBT or not
 ** \param[in] tProgAddressType current segment address
 **
 ** \return tProgBoolean
 ** \retval TRUE  Address corresponds to VBT
 ** \retval FALSE Address does not correspond to VBT
 **/
extern tProgBoolean PROG_Impl10_IsVerificationTableAddress(tProgAddressType ulAddress);
/** \brief checks if the VBT is downloaded or not
**
** \return tProgBoolean
** \retval TRUE VBT is already downloaded
** \retval FALSE VBT is not downloaded
**
**/
extern tProgBoolean PROG_Impl10_IsVerificationTablePresent(void);
/** \brief checks whether the given address is within the range mentioned in the VBT
 ** and if the order of download is respected
 ** \param[in] tProgAddressType current segment address
 **
 ** \return tProgBoolean
 ** \retval TRUE  Address is valid
 ** \retval FALSE Address is not valid
 **/
extern tProgStatus PROG_Impl10_ValidateDataBlockAddress(tProgAddressType ulAddress);
/** \brief this functions checks if the address is within the range mentioned in  VBT
 ** and if not it modifies it to match the VBT to correctly calculate the hash
 ** \param[out] u3*2 adjusted start address
 **
 ** \return void
 **/
extern void PROG_Impl10_AdjustAddressForHash(u32*ulAddress);
/** \brief this functions checks if the length is within the range mentioned in VBT
 ** and if not it modifies it to match the VBT to correctly calculate the hash
 ** \param[out] u32* adjusted length
 **
 ** \return void
 **/
extern void PROG_Impl10_AdjustLengthForHash(u32*ulReadLength);
#if (PROG_IMPL_VARIANT == PROG_IMPL_11)
extern  void PROG_Impl10_SoftwarePartFinished(void);
#endif
#endif
#if PROG_RESUM_REPROG == STD_ON
/** \brief Restore the resume information that have been previously stored
 **
 ** This function is called in case reprogramming shall be resume in order
 ** to get all data that have been previously written for the logical block
 **
 **
 **/
extern void PROG_RestoreResumeInfo(void);
#endif


#if PROG_RESUM_REPROG == STD_ON
/** \brief Perform action at the end of erase process
 **
 ** This function is called to perform action at the end of erase process
 **
 **/
extern void PROG_ResReprog_EraseStatusCheck(u8 ubBlockId);
#endif
#if PROG_RESUM_REPROG == STD_ON
/** \brief Perform action at the end of erase process
 **
 ** This function is called to perform action at the end of erase process
 **
 **/
extern tProgStatus PROG_ResReprog_CheckResume(u32 ulAddress, u8 ubBlockId, tProgBoolean *ubResumeNeed);
#endif

#if ((PROG_ERASE_MEMORY_ENABLE == STD_ON) && (PROG_ERASE_TYPE == PROG_ERASE_BY_BLOCK_ID))
/** \brief Check and Get segment configuration by providing a block identifier
 **
 ** \param[in] ubBlockId block identifier
 ** \param[out] pubSegmentId index of the first matching segment in configuration
 ** \param[out] pubSegmentNbr number of matching segment in configuration
 **
 ** \return Result of treatment
 ** \retval PROG_E_OK  Segment found
 ** \retval PROG_E_NOT_OK Segment not found
 **
 **/
extern tProgStatus PROG_GetSegmentByBlockId(u8 ubBlockId,
        u8 * pubSegmentId, u8 * pubSegmentNbr);
#endif


#if (PROG_PRELIM_ERASING_ENABLE == STD_ON)
/** \brief Verify the Programming Counter of each block and after construct the segment
 **        struct to erase all of them.
 **
 ** This function is called to fulfil the segment struct with all the information
 ** (e.g. start address, size etc) needed to erase the memory.
 **
 ** \return Result of treatment
 ** \retval PROG_E_OK The programming counter is ok and the struct is well filled.
 ** \retval PROG_E_NOT_OK At least one of the segments can't be erased.
 **
 **/
extern tProgStatus PROG_PrelimErasing(tSegmentType * pstSegment);
#endif

#if (PROG_DECOMP_FLASH_ROUTINES == STD_ON)
/** \brief Decompress the Flash driver routines from ROM to RAM
 **
 ** This function is called to decompress the Flash driver routines from ROM to RAM
 **
 ** \return Result of decompression
 ** \retval PROG_E_OK Flash driver routines are correctly decompressed in RAM
 ** \retval PROG_E_NOT_OK Flash driver routines are not correctly decompressed in RAM
 **/
extern tProgStatus PROG_Drv_DecompressFlashRoutines(void);

/** \brief Clear the RAM area where Flash driver routines were decompressed
 **
 ** This function is called to clear the RAM area where Flash driver routines were decompressed
 **
 ** \return Result of clear
 ** \retval PROG_E_OK Flash driver routines were correctly cleared in RAM
 ** \retval PROG_E_NOT_OK Flash driver routines are not correctly cleared in RAM
 **/
extern tProgStatus PROG_Drv_ClearFlashRoutines(void);
#endif

#if (PROG_IMPL_VARIANT == PROG_IMPL_11)
/** \brief Manage erase routine verification using ESS
 ** \param[in] tSegmentType current segment information
 **
 ** \return tProgStatus
 ** \retval PROG_E_OK  Request is ok
 ** \retval PROG_E_NOT_OK Request is no ok
 ** \retval PROG_E_BYPASS Erasing shall be bypassed (memory already erased)
 **/
extern tProgStatus PROG_ExtractEraseParameters_Impl11(tSegmentType * pstSegment);
/** \brief Manage RequestDownload verification using ESS
 ** \param[in] tSegmentType current segment information
 **
 ** \return tProgStatus
 ** \retval PROG_E_OK  Request is ok
 ** \retval PROG_E_NOT_OK Request is no ok
 **/
extern tProgStatus PROG_RD_Check_Impl11(u32 ulStartAddress, u32 ulMemorySize, u8 ubLocalSegmentId, u8 * pubBlockIndex);
#endif
/*                                                                               */
/*-------------------------------------------------------------------------------*/


#endif      /* PROG_PRIV_H */
