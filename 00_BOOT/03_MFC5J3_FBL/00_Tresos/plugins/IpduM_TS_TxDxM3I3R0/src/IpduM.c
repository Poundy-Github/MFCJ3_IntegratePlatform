/**
 * \file
 *
 * \brief AUTOSAR IpduM
 *
 * This file contains the implementation of the AUTOSAR
 * module IpduM.
 *
 * \author Elektrobit Automotive GmbH, 91058 Erlangen, Germany
 *
 * Copyright 2005 - 2019 Elektrobit Automotive GmbH
 * All rights exclusively reserved for Elektrobit Automotive GmbH,
 * unless expressly agreed to otherwise.
 */

/*
 * MISRA-C:2012 Deviations:
 *
 * MISRAC2012-1) Deviated Rule: 11.3
 * A cast shall not be performed between a pointer to object type and
 * a pointer to a different object type.
 *
 * Reason:
 * For post build configuration this type cast is needed.
 *
 * MISRAC2012-2) Deviated Rule: 20.7
 * Expressions resulting from the expansion of macro parameters shall be
 * enclosed in parentheses.
 *
 * Reason:
 * The AUTOSAR compiler abstraction requires these definitions in this way
 * and the arguments cannot be enclosed in parentheses due to C syntax.
 *
 * MISRAC2012-3) Deviated Rule: 8.9 (Advisory)
 * An object should be defined at block scope if its identifier only
 * appears in a single function.
 *
 * Reason:
 * The AUTOSAR memory mapping requires that functions are mapped in
 * SEC_CODE memory sections. Objects at block scope require a different
 * memory mapping, e.g. to a SEC_VAR section, which leads to nested memory
 * sections, which is not supported by some compilers.
 *
 * MISRAC2012-4) Deviated Rule: 18.4
 * The +, -, += and -= operators should not be applied to an expression
 * of pointer type.
 *
 * Reason:
 * When assembling the Container PDU it's more efficient using pointer
 * arithmetic than the adress-of operator, indexing and helper variables.
 * (No negative index could be used)
 *
 * MISRAC2012-5) Deviated Rule: 13.2 (required)
 * The value of an expression and its persistent side effects shall be the same under
 * all permitted evaluation orders.
 *
 * Reason:
 * Macro COMSTACK_BF_ITERATE is an optimized pattern to iterate over bit fields.
 * The side effect was checked and has no negative impact.
 *
 * MISRAC2012-6) Deviated Rule: 13.4 (required)
 * The result of an assignment operator should not be used.
 *
 * Reason:
 * The result of the assignment has to be used, the counter value has to be updated
 * externally. Expression is safe.
 *
 * MISRAC2012-7) Deviated Rule: 14.2
 * 2nd expression should contain a comparison with loop counter (ContainerRxIndex).
 * A for loop shall be well-formed.
 *
 * Reason:
 * 1)The comparison is done with the incremented loop counter to protect the last for loop entry.
 * 2)Macro COMSTACK_BF_ITERATE is an optimized pattern to iterate over bit fields.
 *   It allows the compiler to optimize the code footprint reducing number of instruction
 *   cache miss.
 *
 */


/*==================[inclusions]============================================*/
#include <IpduM_Trace.h>

#include <ComStack_Types.h>
#include <IpduM_Lcfg_Static.h>
/* !LINKSTO IPDUM.ASR40.IPDUM148_3,1 */
#include <PduR_IpduM.h>
/* !LINKSTO IPDUM.ASR40.IPDUM148_2,1 */
#include <IpduM_Cbk.h>
/* !LINKSTO IPDUM.EB.IPDUM148,1 */
#include <IpduM_Api.h>
#include <TSAtomic_Assign.h>
#include <TSMem.h>
#include <IpduM_Int.h>
#include <ComStack_Helpers.h>

#if (IPDUM_DEV_ERROR_DETECT == STD_ON)
/* !LINKSTO IPDUM.ASR40.IPDUM148_5,1 */
#include <Det.h>
#endif

/*==================[macros]================================================*/

/* Deviation MISRAC2012-5 */
/* Deviation MISRAC2012-6 */
/* Deviation MISRAC2012-7 */
#define IPDUM_COMSTACK_BF_ITERATE(Next, BitFieldPtr, Start, End) \
  (Next) = (Start); (End) > ((Next) = ComStack_FindNextOne((BitFieldPtr), (Next)));
/*------------------[AUTOSAR vendor identification check]-------------------*/

#if (!defined IPDUM_VENDOR_ID) /* configuration check */
#error IPDUM_VENDOR_ID must be defined
#endif

#if (IPDUM_VENDOR_ID != 1U) /* vendor check */
#error IPDUM_VENDOR_ID has wrong vendor id
#endif

/*------------------[AUTOSAR release version identification check]----------*/

#if (!defined IPDUM_AR_RELEASE_MAJOR_VERSION) /* configuration check */
#error IPDUM_AR_RELEASE_MAJOR_VERSION must be defined
#endif

/* major version check */
#if (IPDUM_AR_RELEASE_MAJOR_VERSION != 4U)
#error IPDUM_AR_RELEASE_MAJOR_VERSION wrong (!= 4U)
#endif

#if (!defined IPDUM_AR_RELEASE_MINOR_VERSION) /* configuration check */
#error IPDUM_AR_RELEASE_MINOR_VERSION must be defined
#endif

/* minor version check */
#if (IPDUM_AR_RELEASE_MINOR_VERSION != 0U )
#error IPDUM_AR_RELEASE_MINOR_VERSION wrong (!= 0U)
#endif

#if (!defined IPDUM_AR_RELEASE_REVISION_VERSION) /* configuration check */
#error IPDUM_AR_RELEASE_REVISION_VERSION must be defined
#endif

/* revision version check */
#if (IPDUM_AR_RELEASE_REVISION_VERSION != 3U )
#error IPDUM_AR_RELEASE_REVISION_VERSION wrong (!= 3U)
#endif

/*------------------[AUTOSAR module version identification check]-----------*/

#if (!defined IPDUM_SW_MAJOR_VERSION) /* configuration check */
#error IPDUM_SW_MAJOR_VERSION must be defined
#endif

/* major version check */
#if (IPDUM_SW_MAJOR_VERSION != 3U)
#error IPDUM_SW_MAJOR_VERSION wrong (!= 3U)
#endif

#if (!defined IPDUM_SW_MINOR_VERSION) /* configuration check */
#error IPDUM_SW_MINOR_VERSION must be defined
#endif

/* minor version check */
#if (IPDUM_SW_MINOR_VERSION < 3U)
#error IPDUM_SW_MINOR_VERSION wrong (< 3U)
#endif

#if (!defined IPDUM_SW_PATCH_VERSION) /* configuration check */
#error IPDUM_SW_PATCH_VERSION must be defined
#endif

/* patch version check */
#if (IPDUM_SW_PATCH_VERSION < 24U)
#error IPDUM_SW_PATCH_VERSION wrong (< 24U)
#endif

/*==================[type definitions]======================================*/

/* typedef to resolve MISRA Rule 16.7 violation */
#if (IPDUM_ZERO_COPY == STD_ON)
typedef P2CONST(PduInfoType, AUTOMATIC, IPDUM_APPL_DATA) PduTxInfoType;
#else
typedef P2VAR(PduInfoType, AUTOMATIC, IPDUM_APPL_DATA) PduTxInfoType;
#endif /* (IPDUM_ZERO_COPY == STD_ON) */

/*==================[external function declarations]========================*/

/*==================[internal function declarations]========================*/
#define IPDUM_START_SEC_CODE
#include <IpduM_MemMap.h>

#if (IPDUM_ZERO_COPY == STD_OFF)
IPDUM_STATIC FUNC(PduLengthType, IPDUM_CODE) IpduM_BitCopy
(
  P2VAR(uint8, AUTOMATIC, IPDUM_APPL_DATA) Dest,
  P2CONST(uint8, AUTOMATIC, IPDUM_APPL_DATA) Src,
  P2CONST(IpduM_CopyBitFieldType, AUTOMATIC, IPDUM_APPL_CONST) CopyBitField,
  IpduM_BitfieldArraySizeType Size
);

IPDUM_STATIC FUNC(void, IPDUM_CODE) IpduM_PreparePdu
(
  P2CONST(IpduM_TxPathWayType, AUTOMATIC, IPDUM_APPL_CONST) TxPathWay
);
#endif

#if (IPDUM_DYNAMIC_PART_QUEUE == STD_ON)
IPDUM_STATIC FUNC(Std_ReturnType, IPDUM_CODE) IpduM_InsertQueue
(
  PduIdType TxPduId,
  PduIdType PduRTxConfirmationPduId,
  P2CONST(PduInfoType, AUTOMATIC, IPDUM_APPL_DATA) PduInfoPtr,
  uint16 DynamicPriority
);

/* Deviation MISRAC2012-2 */
IPDUM_STATIC FUNC(FUNC_P2VAR(IpduM_QueueEntryType, AUTOMATIC, IPDUM_VAR_NOINIT), IPDUM_CODE) IpduM_RemoveQueue
(
    PduIdType TxConfirmationPduId
);

IPDUM_STATIC FUNC(Std_ReturnType, IPDUM_CODE) IpduM_HandleQueueFilling
(
  PduIdType TxPduId,
  P2CONST(PduInfoType, AUTOMATIC, IPDUM_APPL_DATA) PduInfoPtr,
  P2CONST(IpduM_TxPathWayType, AUTOMATIC, IPDUM_APPL_CONST) TxPathWayT,
  P2CONST(IpduM_TxPartType, AUTOMATIC, IPDUM_APPL_CONST) TxPartT,
  PduTxInfoType PduTxInfoPtr,
  P2VAR(PduIdType, AUTOMATIC, IPDUM_APPL_DATA) PdumDynamicTxPduIdPtr,
  P2VAR(PduIdType, AUTOMATIC, IPDUM_APPL_DATA) PduRTxConfirmationPduIdPtr,
  P2VAR(boolean, AUTOMATIC, IPDUM_APPL_DATA) ImmediatelySendPtr
);

#if (IPDUM_ZERO_COPY == STD_OFF)
IPDUM_STATIC FUNC(void,IPDUM_CODE) IpduM_SetDynamicPduReadyToSend(PduIdType TxPduId);
#endif

IPDUM_STATIC FUNC(uint16, IPDUM_CODE) IpduM_GetMaxPriorityQueue(PduIdType TxPduId);
#endif /* IPDUM_DYNAMIC_PART_QUEUE == STD_ON */

#if (IPDUM_ENABLE_JIT_UPDATE == STD_ON) || \
    (IPDUM_INITIALIZATION_BY_SIGNAL_VALUE == STD_ON)
IPDUM_STATIC FUNC(Std_ReturnType, IPDUM_CODE) IpduM_UpdatePdu
(
  PduIdType PduRTriggerTxPduId,
  PduIdType TxPartIndex,
  P2CONST(IpduM_TxPathWayType, AUTOMATIC, IPDUM_APPL_CONST) TxPathWay,
  boolean IsInit
);
#endif /* (IPDUM_ENABLE_JIT_UPDATE == STD_ON) || .. */

#if (IPDUM_ENABLE_JIT_UPDATE == STD_ON)
IPDUM_STATIC FUNC(void, IPDUM_CODE) IpduM_GetJitDataTransmit
(
  PduIdType TxPduId,
  P2CONST(IpduM_TxPartType, AUTOMATIC, IPDUM_APPL_CONST) TxPart,
  P2CONST(IpduM_TxDataType, AUTOMATIC, IPDUM_APPL_DATA) TxData,
  P2CONST(IpduM_TxPathWayType, AUTOMATIC, IPDUM_APPL_CONST) TxPathWay,
  P2VAR(IpduM_JitDataType, AUTOMATIC, IPDUM_APPL_DATA) JitData
);

#if (IPDUM_STATIC_PART_EXISTS == STD_ON)
IPDUM_STATIC FUNC(void, IPDUM_CODE) IpduM_GetStaticJitData
(
  P2CONST(IpduM_TxPathWayType, AUTOMATIC, IPDUM_APPL_CONST) TxPathWay,
  P2VAR(IpduM_JitDataType, AUTOMATIC, IPDUM_APPL_DATA) JitData
);
#endif

IPDUM_STATIC FUNC(void, IPDUM_CODE) IpduM_GetDynamicJitData
(
  PduIdType TxConfPduId,
  P2CONST(IpduM_TxDataType, AUTOMATIC, IPDUM_APPL_DATA) TxData,
  P2CONST(IpduM_TxPathWayType, AUTOMATIC, IPDUM_APPL_CONST) TxPathWay,
  P2VAR(IpduM_JitDataType, AUTOMATIC, IPDUM_APPL_DATA) JitData
);
#endif /* (IPDUM_ENABLE_JIT_UPDATE == STD_ON) */

IPDUM_STATIC FUNC(void, IPDUM_CODE) IpduM_HandleRxPathWay
(
  PduIdType RxPduId,
  P2VAR(PduInfoType, AUTOMATIC, IPDUM_APPL_DATA) PduInfoPtr
);

IPDUM_STATIC FUNC(Std_ReturnType, IPDUM_CODE) IpduM_HandleTxPathWay
(
  PduIdType TxPduId,
  P2CONST(PduInfoType, AUTOMATIC, AUTOMATIC) PduInfoPtr
);

#if (IPDUM_CONTAINER_PDU_HANDLING_ENABLE == STD_ON)

#if (IPDUM_ZERO_COPY == STD_OFF)
IPDUM_STATIC FUNC(Std_ReturnType, IPDUM_CODE) IpduM_CntrTriggerTransmit
(
  PduIdType TxPduId,
  P2VAR(PduInfoType, AUTOMATIC, AUTOMATIC) PduInfoPtr
);

/*
 * \brief Assembles TriggerTransmit-LastIsBest containers
 *
 * Does not consume the list (second parameter)
 * If used with the queued confirmation list, it does not
 * touch the queue elements, it has to be dropped manually
 * afterwards
 *
 * \param[in]       cntrPtr             Pointer to Container
 *                                      config structure
 * \param[in]       containedPduList    Pointer to list of
 *                                      Contained PDUs
 * \param[inout]    pduInfoPtr          PduInfo used for the
 *                                      assembly of the container
 */
IPDUM_STATIC FUNC(void, IPDUM_CODE) IpduM_PackDataTTLBtoBuff
(
  P2CONST(IpduM_ContainerTxPduType, AUTOMATIC, IPDUM_APPL_CONST) cntrPtr,
  P2VAR(uint16, AUTOMATIC, AUTOMATIC) containedPduList,
  P2VAR(PduInfoType, AUTOMATIC, AUTOMATIC) pduInfoPtr
);
#endif

IPDUM_STATIC FUNC(Std_ReturnType, IPDUM_CODE) IpduM_HandleTxContainerPdu
(
  PduIdType TxPduId
#if(IPDUM_CNTND_COLLECT_QUEUED_TX == STD_ON)
  , P2CONST(PduInfoType, AUTOMATIC, IPDUM_APPL_DATA) PduInfoPtr
#endif
);

IPDUM_STATIC FUNC(sint32, IPDUM_CODE) IpduM_RxCntd_BinSearch
(
  P2CONST(IpduM_ContainedRxPduType, AUTOMATIC, IPDUM_APPL_CONST) ContainedPduHeaderIds,
  sint32 left,
  sint32 right,
  uint32 PduHeaderId
);

#if (IPDUM_STATIC_CONTAINER_PDU_HANDLING_ENABLE == STD_ON)
IPDUM_STATIC INLINE FUNC(boolean, IPDUM_CODE) IpduM_IsBitSet
(
  P2CONST(uint8, AUTOMATIC, IPDUM_APPL_CONST) DataPtr,
  uint32 BytePosition,
  uint8 BitMask
);

IPDUM_STATIC FUNC(void, IPDUM_CODE) IpduM_HandleStaticRxPdu
(
  P2CONST(IpduM_ContainerRxPduType, AUTOMATIC, IPDUM_APPL_CONST) ContainerPdu,
  P2VAR(PduInfoType, AUTOMATIC, IPDUM_APPL_DATA) PduInfoPtr
);
#endif /* IPDUM_STATIC_CONTAINER_PDU_HANDLING_ENABLE == STD_ON */

IPDUM_STATIC FUNC(void, IPDUM_CODE) IpduM_HandleDynamicRxPdu
(
  P2CONST(IpduM_ContainerRxPduType, AUTOMATIC, IPDUM_APPL_CONST) ContainerPdu,
  P2VAR(PduInfoType, AUTOMATIC, IPDUM_APPL_DATA) PduInfoPtr
);

IPDUM_STATIC FUNC(void, IPDUM_CODE) IpduM_HandleRxContainerPdu
(
  PduIdType ContainerRxIndex,
  P2VAR(PduInfoType, AUTOMATIC, IPDUM_APPL_DATA) PduInfoPtr
);

IPDUM_STATIC FUNC(void, IPDUM_CODE) IpduM_AddtoDeferredList
(
  PduIdType ContainerRxIndex,
  P2VAR(PduInfoType, AUTOMATIC, IPDUM_APPL_DATA) PduInfoPtr
);

IPDUM_STATIC FUNC(void, IPDUM_CODE) IpduM_DynamicPackDataOne
(
  uint16 ContainedPduIndex,
  uint16 ParentContainerIndex,
  uint32 buffOffset,
  PduLengthType length,
  P2VAR(uint8, AUTOMATIC, IPDUM_APPL_DATA) DstBuffer,
  P2VAR(uint8, AUTOMATIC, IPDUM_APPL_DATA) SrcBuffer
);

IPDUM_STATIC FUNC(uint32, IPDUM_CODE) IpduM_DynamicPackDataAll
(
  P2VAR(uint8, AUTOMATIC, IPDUM_APPL_DATA) DstBuffer,
  uint16 ParentContainerIndex
);

#if (IPDUM_STATIC_CONTAINER_PDU_HANDLING_ENABLE == STD_ON)
IPDUM_STATIC INLINE FUNC(void, IPDUM_CODE) IpduM_AtomicSetBit
(
  P2VAR(uint8, AUTOMATIC, IPDUM_APPL_CONST) DataPtr,
  uint32 BytePosition,
  uint8 BitMask
);

IPDUM_STATIC FUNC(uint32, IPDUM_CODE) IpduM_StaticPackDataAll
(
  P2VAR(uint8, AUTOMATIC, IPDUM_APPL_DATA) DstBuffer,
  uint16 ParentContainerIndex
);
#endif

IPDUM_STATIC FUNC(boolean, IPDUM_CODE) IpduM_ContainsElem
(
  uint16 ParentContainerIndex,
  uint16 ContainedIndex
);

IPDUM_STATIC FUNC(void, IPDUM_CODE) IpduM_AddtoList
(
  uint16 ContainedIndex,
  uint16 ParentContainerIndex,
  PduLengthType length
);

IPDUM_STATIC FUNC(PduLengthType, IPDUM_CODE) IpduM_PackDataAllGeneric
(
  P2VAR(uint8, AUTOMATIC, AUTOMATIC) currentDataBuffer,
  uint16 ParentContainerIndex
);

IPDUM_STATIC FUNC(void, IPDUM_CODE) IpduM_AddtoListGeneric
(
#if ( (IPDUM_STATIC_CONTAINER_PDU_HANDLING_ENABLE == STD_ON) || (IPDUM_CONTAINEDTXPDU_PRIORITY_HANDLING_ENABLE == STD_ON) )
    P2CONST(IpduM_ContainerTxPduType, AUTOMATIC, IPDUM_APPL_CONST) cntrPtr,
#endif
    uint16 ContainedPduIndex,
    uint16 ParentContainerIndex,
    PduLengthType ContainedPduLength
);

#if (IPDUM_CONTAINEDTXPDU_PRIORITY_HANDLING_ENABLE == STD_ON)

/* !LINKSTO IpduM.ASR44.SWS_IpduM_00248,1 */

IPDUM_STATIC FUNC(void, IPDUM_CODE) IpduM_AddtoSortedPrioList
(
  uint16 ContainedIndex,
  uint16 ParentContainerIndex,
  PduLengthType length
);
#endif

#if (IPDUM_STATIC_CONTAINER_PDU_HANDLING_ENABLE == STD_ON)
IPDUM_STATIC FUNC(void, IPDUM_CODE) IpduM_AddtoSortedList
(
  uint16 ContainedIndex,
  uint16 ParentContainerIndex
);
#endif

IPDUM_STATIC FUNC(boolean, IPDUM_CODE) IpduM_CheckSizeTrigger
(
  uint16 ParentContainerIndex,
  PduLengthType length,
  P2CONST(IpduM_ContainerTxPduType, AUTOMATIC, IPDUM_APPL_CONST) cntrPtr
);

IPDUM_STATIC FUNC(void, IPDUM_CODE) IpduM_CntrConfPrepare
(
  PduIdType id
#if (IPDUM_CONTAINER_QUEUING_TX == STD_ON)
  ,P2CONST(IpduM_ContainerTxPduType, AUTOMATIC, IPDUM_APPL_CONST) cntrPtr,
  P2VAR(IpduM_ContainerQueueType, AUTOMATIC, IPDUM_APPL_DATA) qPtr
#endif
);

IPDUM_STATIC FUNC(void, IPDUM_CODE) IpduM_CurrCntrPrepare
(
#if(IPDUM_CNTND_COLLECT_QUEUED_TX == STD_ON)
  boolean isLastIsBest,
  CONSTP2CONST(uint8, AUTOMATIC, IPDUM_APPL_DATA) currentDataBuffer,
#endif
  PduIdType id,
  P2VAR(PduInfoType, AUTOMATIC, AUTOMATIC) pduInfo
);

IPDUM_STATIC FUNC(void, IPDUM_CODE) IpduM_SendCurrCntr
(
  PduIdType id
);

#if (IPDUM_CONTAINER_QUEUING_TX == STD_ON)
IPDUM_STATIC FUNC(void, IPDUM_CODE) IpduM_DequeueCntr
(
  PduIdType id
);
#endif

IPDUM_STATIC FUNC(void, IPDUM_CODE) IpduM_CntrSizeAnnounce
(
  PduIdType id
);

IPDUM_STATIC FUNC(void, IPDUM_CODE) IpduM_LastIsBest_CntrAdd
(
    uint16 ParentContainerIndex,
    uint16 ContainedPduIndex,
    P2VAR(boolean, AUTOMATIC, AUTOMATIC) sendTrigger,
    P2VAR(boolean, AUTOMATIC, AUTOMATIC) sizeTrigger
);

#if (IPDUM_CNTND_COLLECT_QUEUED_TX == STD_ON)
IPDUM_STATIC FUNC(void, IPDUM_CODE) IpduM_Queued_CntrAdd
(
    uint16 ParentContainerIndex,
    uint16 ContainedPduIndex,
    P2VAR(boolean, AUTOMATIC, AUTOMATIC) sendTrigger,
    P2VAR(boolean, AUTOMATIC, AUTOMATIC) sizeTrigger,
    P2CONST(PduInfoType, AUTOMATIC, AUTOMATIC) PduInfoPtr
);
#endif

IPDUM_STATIC FUNC(void, IPDUM_CODE) IpduM_UpdateCntrSendTimeout
(
  IpduM_TxSendTimeoutType configuredContainedSendTimeout,
  P2CONST(uint16, AUTOMATIC, IPDUM_APPL_DATA) ContainerTxList,
  P2VAR(IpduM_TxSendTimeoutType, AUTOMATIC, IPDUM_APPL_DATA) sendTimeoutCounter
);

#if (IPDUM_STATIC_CONTAINER_PDU_HANDLING_ENABLE == STD_ON)
IPDUM_STATIC INLINE FUNC(void, IPDUM_CODE) IpduM_StaticCntrCheckTrigger
(
  uint16 ParentContainerIndex,
  P2VAR(boolean, AUTOMATIC, IPDUM_APPL_DATA) sendTrigger
);
#endif

IPDUM_STATIC INLINE FUNC(void, IPDUM_CODE) IpduM_CntrCheckSendTrigger
(
  uint16 ParentContainerIndex,
  P2VAR(boolean, AUTOMATIC, IPDUM_APPL_DATA) sendTrigger
);

IPDUM_STATIC INLINE FUNC(void, IPDUM_CODE) IpduM_LastIsBest_CntrCheckTriggers
(
  uint16 ParentContainerIndex,
  uint16 ContainedPduIndex,
  P2CONST(uint16, AUTOMATIC, IPDUM_APPL_DATA) ContainerTxList,
  P2VAR(boolean, AUTOMATIC, IPDUM_APPL_DATA) trigger
);

#if (IPDUM_CNTND_COLLECT_QUEUED_TX == STD_ON)
IPDUM_STATIC INLINE FUNC(void, IPDUM_CODE) IpduM_Queued_CntrCheckTriggers
(
  uint16 ParentContainerIndex,
  uint16 ContainedPduIndex,
  P2VAR(boolean, AUTOMATIC, IPDUM_APPL_DATA) trigger
);
#endif

IPDUM_STATIC FUNC(void, IPDUM_CODE) IpduM_CallCntrSendFunction
(
  PduIdType index
);
#if(IPDUM_DEDICATED_IPDU_PROCESSING_SUPPORT == STD_OFF)
IPDUM_STATIC FUNC(void, IPDUM_CODE) IpduM_CntrHandleTimers
(
  void
);
#else
IPDUM_STATIC FUNC(void, IPDUM_CODE) IpduM_CntrHandleTimers
(
  IpduM_MainFuncIdxType idx
);
#endif
IPDUM_STATIC FUNC(void, IPDUM_CODE) IpduM_CntrTxConfirmation
(
  PduIdType TxPduId
);

IPDUM_STATIC FUNC(void, IPDUM_CODE) IpduM_SetFlags_DT_LastIsBest_NoCntrQueuing
(
  P2VAR(IpduM_CntrTxDataType, AUTOMATIC, AUTOMATIC) cntrRamPtr,
  P2VAR(Std_ReturnType, AUTOMATIC, AUTOMATIC) RetValue,
  P2VAR(boolean, AUTOMATIC, AUTOMATIC) prepareCurrentInstance,
  boolean sendTrigger
);

IPDUM_STATIC FUNC(Std_ReturnType, IPDUM_CODE) IpduM_DT_LastIsBest_NoCntrQueuing
(
    PduIdType TxPduId
);

#if (IPDUM_CONTAINER_QUEUING_TX == STD_ON)
IPDUM_STATIC FUNC(void, IPDUM_CODE) IpduM_SetFlags_DT_LastIsBest_WithCntrQueuing
(
  P2VAR(IpduM_CntrTxDataType, AUTOMATIC, AUTOMATIC) cntrRamPtr,
  P2VAR(boolean, AUTOMATIC, AUTOMATIC) addToQCurrentInstance,
  P2VAR(boolean, AUTOMATIC, AUTOMATIC) prepareCurrentInstance,
  boolean sendTrigger
);

IPDUM_STATIC FUNC(Std_ReturnType, IPDUM_CODE) IpduM_DT_LastIsBest_WithCntrQueuing
(
    PduIdType TxPduId
);
#endif

#if (IPDUM_CNTND_COLLECT_QUEUED_TX == STD_ON)
IPDUM_STATIC FUNC(Std_ReturnType, IPDUM_CODE) IpduM_DT_Queued_NoCntrQueuing
(
    PduIdType TxPduId,
    P2CONST(PduInfoType, AUTOMATIC, IPDUM_APPL_DATA) PduInfoPtr
);
#endif

#if (IPDUM_CONTAINER_QUEUING_TX == STD_ON)
#if (IPDUM_CNTND_COLLECT_QUEUED_TX == STD_ON)
IPDUM_STATIC FUNC(Std_ReturnType, IPDUM_CODE) IpduM_DT_Queued_WithCntrQueuing
(
    PduIdType TxPduId,
    P2CONST(PduInfoType, AUTOMATIC, IPDUM_APPL_DATA) PduInfoPtr
);
#endif
#endif

IPDUM_STATIC FUNC(void, IPDUM_CODE) IpduM_SetFlags_TT_LastIsBest_NoCntrQueuing
(
  P2VAR(IpduM_CntrTxDataType, AUTOMATIC, AUTOMATIC) cntrRamPtr,
  P2VAR(Std_ReturnType, AUTOMATIC, AUTOMATIC) RetValue,
  P2VAR(boolean, AUTOMATIC, AUTOMATIC) ttSizeAnnounce,
  boolean sizeAnnounceTrg,
  boolean sendTrigger
);

IPDUM_STATIC FUNC(Std_ReturnType, IPDUM_CODE) IpduM_TT_LastIsBest_NoCntrQueuing
(
    PduIdType TxPduId
);

#if (IPDUM_CONTAINER_QUEUING_TX == STD_ON)
IPDUM_STATIC FUNC(void, IPDUM_CODE) IpduM_SetFlags_TT_LastIsBest_WithCntrQueuing
(
  P2VAR(IpduM_CntrTxDataType, AUTOMATIC, AUTOMATIC) cntrRamPtr,
  P2VAR(boolean, AUTOMATIC, AUTOMATIC) addToQCurrentInstance,
  P2VAR(boolean, AUTOMATIC, AUTOMATIC) ttSizeAnnounce,
  uint16 ParentContainerIndex,
  boolean sizeAnnounceTrg,
  boolean sendTrigger
);

IPDUM_STATIC FUNC(Std_ReturnType, IPDUM_CODE) IpduM_TT_LastIsBest_WithCntrQueuing
(
    PduIdType TxPduId
);
#endif

#if (IPDUM_CNTND_COLLECT_QUEUED_TX == STD_ON)
IPDUM_STATIC FUNC(Std_ReturnType, IPDUM_CODE) IpduM_TT_Queued_NoCntrQueuing
(
    PduIdType TxPduId,
    P2CONST(PduInfoType, AUTOMATIC, IPDUM_APPL_DATA) PduInfoPtr
);
#endif

#if (IPDUM_CONTAINER_QUEUING_TX == STD_ON)
#if (IPDUM_CNTND_COLLECT_QUEUED_TX == STD_ON)
IPDUM_STATIC FUNC(Std_ReturnType, IPDUM_CODE) IpduM_TT_Queued_WithCntrQueuing
(
    PduIdType TxPduId,
    P2CONST(PduInfoType, AUTOMATIC, IPDUM_APPL_DATA) PduInfoPtr
);
#endif
#endif

#if ((IPDUM_CONTAINER_QUEUING_RX == STD_ON) || (IPDUM_CONTAINER_QUEUING_TX == STD_ON))
/*
 * \brief Store data in queue
 *
 * Stores data in the queue. Circular buffers are used, data is
 * overwritten in case of an overflow.
 * \em{length is stored at the beginning of \p dataOut}
 *
 * \param[in]  qPtr        Pointer to queue struct
 * \param[in]  dataIn      Input data
 * \param[out] dataOut     Output buffer, direction is inferred
 *                         from the address (TX buff verified)
 * \param[in] cntrPduLen   Configured length of PDU
 * \param[in] length       Length of input data
 * \param[in] qSize        Depth of the queue associated with
 *                         the Container
 *
 * \return BUFREQ_E_OVFL if DET is enabled and overflow occurs
 *         BUFREQ_OK No overflow or DET is disabled
 */
IPDUM_STATIC FUNC(BufReq_ReturnType, IPDUM_CODE) IpduM_CntrQPush
(
  P2VAR(IpduM_ContainerQueueType, AUTOMATIC, AUTOMATIC) qPtr,
  P2CONST(uint8, AUTOMATIC, AUTOMATIC) dataIn,
  P2VAR(uint8, AUTOMATIC, AUTOMATIC) dataOut,
  PduLengthType cntrPduLen,
  PduLengthType length,
  uint8 qSize
);

#if (IPDUM_CONTAINER_QUEUING_TX == STD_ON)
/*
 * \brief Add to queue, set confirmation indexes and clear list
 *
 * The function has to be called from a protected context
 *
 * \param[in] ParentContainerIndex        index used to refer container
 * \param[in] currentDataBuffer           buffer to be copied from
 * \param[in] length                      length to be copied
 * \return                 void
 */
IPDUM_STATIC FUNC(void, IPDUM_CODE) IpduM_CntrQAdd
(
  uint16 ParentContainerIndex,
  P2CONST(uint8, AUTOMATIC, IPDUM_APPL_DATA) currentDataBuffer,
  PduLengthType length
);

/*
 * \brief Queues the list of Contained PDUs, saves confirmation list,
 *  clears the list of currently contained PDUs
 *
 *  The function has to be called from a protected context
 *
 * \param[in] ParentContainerIndex index used to refer container
 * \return    BUFREQ_OK            list added to the queue (or DET disabled)
 *            BUFREQ_E_OVFL        queue overflowed, list added by eliminating
 *                                 the oldest entry
 */
IPDUM_STATIC FUNC(BufReq_ReturnType, IPDUM_CODE) IpduM_CntrQCntdListOnly
(
  uint16 ParentContainerIndex
);

/*
 * \brief Check if container queue is empty
 *
 * \param[in] index        index used to refer container
 * \return                 TRUE if queue is empty
 *                         FALSE otherwise
 */
IPDUM_STATIC FUNC(boolean, IPDUM_CODE) IpduM_IsCntrQEmpty
(
  uint16 index
);
#endif

/*
 * \brief Retrieves data from queue (destructive)
 *
 * Data retrieved from the queue is \em removed
 * afterwards.
 *
 * \param[in]  qPtr        Pointer to queue structure
 * \param[out] length      Length of stored data
 * \param[in]  dataIn      Pointer to start of buffer
 * \param[out] dataOut     Pointer to out buffer
 * \param[in]  cntrPduLen  Configured PDU length
 * \param[in]  qSize       Depth of the queue associated
 *                         with the Container
 *
 * \return                 BUFREQ_E_NOT_OK if queue is empty
 *                         BUFREQ_OK otherwise
 */
IPDUM_STATIC FUNC(BufReq_ReturnType, IPDUM_CODE) IpduM_CntrQPop
(
  P2VAR(IpduM_ContainerQueueType, AUTOMATIC, AUTOMATIC) qPtr,
  P2VAR(PduLengthType, AUTOMATIC, AUTOMATIC) length,
  P2VAR(uint8, AUTOMATIC, AUTOMATIC) dataIn,
  P2VAR(uint8, AUTOMATIC, AUTOMATIC) dataOut,
  PduLengthType cntrPduLen,
  uint8 qSize
);

#endif /* (IPDUM_CONTAINER_QUEUING_RX == STD_ON) || ... */
#if (IPDUM_CONTAINER_QUEUING_TX == STD_ON)
/*
 * \brief Non-destructive retrieval of data from queue
 *
 * \param[in]  qPtr        Pointer to associated queue structure
 * \param[out] length      Length of stored data
 * \param[in] dataIn       Pointer to start of buffer
 *                         Used only for type inference
 * \param[out] dataPtr     Copies data to dataPtr
 * \param[in] cntrPduLen   Configured length of PDU
 * \return    void         No return value since
 *                         it's used only from IpduM_DequeueCntr,
 *                         which in turn from IpduM_CallCntrSendFunction,
 *                         where it's verified whether there are queued entities.
 */
LOCAL_INLINE FUNC(void, IPDUM_CODE) IpduM_CntrQPeek
(
  P2VAR(IpduM_ContainerQueueType, AUTOMATIC, AUTOMATIC) qPtr,
  P2VAR(PduLengthType, AUTOMATIC, AUTOMATIC) length,
  P2VAR(uint8, AUTOMATIC, AUTOMATIC) dataIn,
  P2VAR(uint8, AUTOMATIC, AUTOMATIC) dataPtr,
  /* Deviation MISRAC2012-2 */
  PduLengthType cntrPduLen
);
#endif /* IPDUM_CONTAINER_QUEUING_TX == STD_ON */
#endif /* IPDUM_CONTAINER_PDU_HANDLING_ENABLE == STD_ON */

#define IPDUM_STOP_SEC_CODE
#include <IpduM_MemMap.h>

/*==================[external constants]====================================*/

/*==================[internal constants]====================================*/

#define IPDUM_START_SEC_CONST_UNSPECIFIED
#include <IpduM_MemMap.h>

#if(IPDUM_CONTAINER_PDU_HANDLING_ENABLE == STD_ON)
/* Deviation MISRAC2012-3 */
IPDUM_STATIC CONST(IpduM_RxIndHandlerType, IPDUM_APPL_CONST) IpduM_RxHandlers[3U] =
{
  IpduM_HandleRxPathWay,
  IpduM_HandleRxContainerPdu,
  IpduM_AddtoDeferredList
};
#else
/* Deviation MISRAC2012-3 */
IPDUM_STATIC CONST(IpduM_RxIndHandlerType, IPDUM_APPL_CONST) IpduM_RxHandlers[1U] =
{
  IpduM_HandleRxPathWay
};
#endif


#define IPDUM_STOP_SEC_CONST_UNSPECIFIED
#include <IpduM_MemMap.h>

/*==================[external data]=========================================*/

/*==================[internal data]=========================================*/
#define IPDUM_START_SEC_VAR_FAST_INIT_8
#include <IpduM_MemMap.h>

/** \brief IpduM_InitStatus
 * global variable for the actual initialization status of the IpduM */
/* !LINKSTO IPDUM.ASR40.IPDUM075,1 */
IPDUM_STATIC VAR(IpduM_StatusType, IPDUM_VAR_FAST) IpduM_InitStatus = IPDUM_UNINIT;

#define IPDUM_STOP_SEC_VAR_FAST_INIT_8
#include <IpduM_MemMap.h>


#define IPDUM_START_SEC_VAR_FAST_INIT_UNSPECIFIED
#include <IpduM_MemMap.h>

/** \brief IpduM_ConfigPtr
 * global variable for the config ptr of the IpduM */
/* !LINKSTO IPDUM.ASR40.IPDUM075,1 */
IPDUM_STATIC P2CONST(IpduM_ConfigType, IPDUM_VAR, IPDUM_APPL_CONST) IpduM_ConfigPtr = NULL_PTR;

#define IPDUM_STOP_SEC_VAR_FAST_INIT_UNSPECIFIED
#include <IpduM_MemMap.h>

/*==================[external function definitions]=========================*/

#define IPDUM_START_SEC_CODE
#include <IpduM_MemMap.h>

/*--------------------------------------------------------------------------*/
FUNC(void, IPDUM_CODE) IpduM_Init
(
  P2CONST(IpduM_ConfigType, AUTOMATIC, IPDUM_APPL_CONST) Config
)
{
  P2VAR(IpduM_TxDataType, AUTOMATIC, IPDUM_VAR_NOINIT) TxData;
  P2CONST(IpduM_TxPathWayType, AUTOMATIC, IPDUM_APPL_CONST) TxPathWayI;
  P2CONST(IpduM_ConfigType, AUTOMATIC, IPDUM_APPL_CONST) InternalConfig = Config;
  uint16 i;
#if (IPDUM_DEV_ERROR_DETECT == STD_ON)
  boolean InitFlag = TRUE;
#endif

  DBG_IPDUM_INIT_ENTRY(Config);

#if (IPDUM_PBCFGM_SUPPORT_ENABLED == STD_ON)
  /* If the initialization function is called with an null pointer get the configuration from the
   * post build configuration manager */

  if (InternalConfig == NULL_PTR)
  {
    PbcfgM_ModuleConfigPtrType ModuleConfig = NULL_PTR;
    (void) PbcfgM_GetConfig(
            IPDUM_MODULE_ID,
            0U, /* dummy instance ID */
            &ModuleConfig);

    InternalConfig = (P2CONST(IpduM_ConfigType, AUTOMATIC, IPDUM_APPL_CONST)) ModuleConfig;
  }
#endif

#if (IPDUM_DEV_ERROR_DETECT == STD_ON)
  if (NULL_PTR == InternalConfig)
  {
    IPDUM_DET_REPORT_ERROR(IPDUM_SID_INIT, IPDUM_E_PARAM_POINTER);
    InitFlag = FALSE;
  }
  else
  {
    /* check that configuration pointer is valid */
    if (E_OK != IpduM_IsValidConfig(InternalConfig))
    {
      IPDUM_DET_REPORT_ERROR(IPDUM_SID_INIT, IPDUM_E_CONFIG_PTR_INVALID);
      InitFlag = FALSE;
    }
    else
    {
      /* Check if IpduMDataMemSize is big enough for the current configuration */
      if (FALSE == IPDUM_NULL_PTR_CHECK(InternalConfig->TxPathWay))
      {
#if (IPDUM_ZERO_COPY == STD_OFF)
        P2CONST(IpduM_TxPathWayType, AUTOMATIC, IPDUM_APPL_CONST) TxPathWay = &IPDUM_PBCFG_ACCESS_PTR(InternalConfig, IpduM_TxPathWayType, TxPathWay)[InternalConfig->TxPathWayLen-1U];
        uint16 ByteSize = IPDUM_GET_BYTE_SIZE(TxPathWay->Size);
        if (((uint32)(TxPathWay->BufferOffset)+ ByteSize) >
        IpduM_GDataMemSize
        )
#elif (IPDUM_DYNAMIC_PART_QUEUE == STD_ON)
          P2CONST(IpduM_TxPathWayType, AUTOMATIC, IPDUM_APPL_CONST) TxPathWay = &IPDUM_PBCFG_ACCESS_PTR(InternalConfig, IpduM_TxPathWayType, TxPathWay)[InternalConfig->TxPathWayLen-1U];
        if (((uint32)(TxPathWay->QueueOffset + (TxPathWay->QueueSize * sizeof(IpduM_QueueEntryType)))) > IpduM_GDataMemSize)
#else
          if ((uint32)(InternalConfig->TxPathWayLen*sizeof(IpduM_TxDataType)) > IpduM_GDataMemSize )
#endif
          {
            IPDUM_DET_REPORT_ERROR(IPDUM_SID_INIT, IPDUM_E_PARAM);
            InitFlag = FALSE;
          }
      }
#if(IPDUM_CONTAINER_PDU_HANDLING_ENABLE == STD_ON)
      if((uint32)InternalConfig->DataMemMinLen > IpduM_GDataMemSize)
      {
        IPDUM_DET_REPORT_ERROR(IPDUM_SID_INIT, IPDUM_E_PARAM);
        InitFlag = FALSE;
      }
#endif /* IPDUM_CONTAINER_PDU_HANDLING_ENABLE == STD_OFF */
    }
  }

  if (InitFlag == TRUE)
#endif /* IPDUM_DEV_ERROR_DETECT == STD_ON */
  {
    IpduM_ConfigPtr = InternalConfig;

    if (FALSE == IPDUM_NULL_PTR_CHECK(IpduM_ConfigPtr->TxPathWay))
    {
      /* Deviation MISRAC2012-1 */
      TxData = (P2VAR(IpduM_TxDataType, AUTOMATIC, IPDUM_VAR_NOINIT))(&IpduM_GDataMemPtr[IPDUM_TX_DATA_OFFSET]);

      for (i=0; i<IPDUM_TX_PATHWAY_LEN; i++)
      {
        TxPathWayI = IPDUM_CFG_GET_TX_PATHWAY(i);

        if (TxPathWayI->Size > 0)
        {
#if (IPDUM_ZERO_COPY == STD_OFF)

          /* Initialize selector and initial values */
          IpduM_PreparePdu(TxPathWayI);

#if (IPDUM_INITIALIZATION_BY_SIGNAL_VALUE == STD_ON)
          /* Since the return value of the Com_TriggerTransmit is E_NOT_OK due to stopped
             signals at initialization, but initial data copied, the return value is not
             considered here */
          (void)IpduM_UpdatePdu(
                                TxPathWayI->InitialDynamicPartTrigTxHandleId,
                                TxPathWayI->InitialDynamicPartIndex,
                                TxPathWayI,
                                TRUE
                               );


#if (IPDUM_STATIC_PART_EXISTS == STD_ON)
          /* Since the return value of the Com_TriggerTransmit is E_NOT_OK due to stopped
             signals at initialization, but initial data copied, the return value is not
             considered here */
          (void)IpduM_UpdatePdu(
                                TxPathWayI->StaticPartTrigTxHandleId,
                                TxPathWayI->StaticPartIndex,
                                TxPathWayI,
                                TRUE
                               );
#endif /* (IPDUM_STATIC_PART_EXISTS == STD_ON) */
#endif /* (IPDUM_INITIALIZATION_BY_SIGNAL_VALUE == STD_ON) */
#endif /* (IPDUM_ZERO_COPY == STD_OFF) */

          /* Initialize timeout monitor */
          TxData[i].ConfirmationTimeoutCounter = 0U;

          /* Set TxConfirmation PDU-ID to invalid value */
          TxData[i].PduRTxConfirmationPduId = IPDUM_RESERVED_PDUID;

#if (IPDUM_ENABLE_JIT_UPDATE == STD_ON)
          /* Set associated dynamic Tx part of confirmation ID to invalid value */
          TxData[i].DynamicPartIndex = IPDUM_RESERVED_PDUID;

          /* Set TriggerTx PDU-ID to invalid value */
          TxData[i].PduRTriggerTxPduId = IPDUM_RESERVED_PDUID;
#endif /* (IPDUM_ENABLE_JIT_UPDATE == STD_ON) */

#if (IPDUM_DYNAMIC_PART_QUEUE == STD_ON)
          /* Initialize queue position */
          TxData[i].QueuePos = 0U;
#endif
        }
      }
    }

#if (IPDUM_CONTAINER_PDU_HANDLING_ENABLE == STD_ON)
    TS_MemBZero(&IpduM_GDataMemPtr[IPDUM_RX_DATA_CNTR_OFFSET], (IpduM_GDataMemSize - IPDUM_RX_DATA_CNTR_OFFSET));
    /* Set terminator bit for the bitfield */
    for(i = 0U; i < IPDUM_RX_CONTAINER_PROCESSING_DEFERRED_NO; i++)
    {
      P2VAR(uint32, AUTOMATIC, IPDUM_VAR_NOINIT) deferredListPtr = IPDUM_GET_DEFERRED_LIST(IPDUM_GET_RX_MF_IDX(i));

      deferredListPtr[IPDUM_RX_CONTAINER_PROCESSING_DEFERRED_NO / 32U] |= ((uint32)1U << ((IPDUM_RX_CONTAINER_PROCESSING_DEFERRED_NO) % 32U));
    }
#endif

    /* tag module as initialized */
    IpduM_InitStatus = IPDUM_INIT;
  }

  DBG_IPDUM_INIT_EXIT(Config);
}
/*--------------------------------------------------------------------------*/
FUNC(void, IPDUM_CODE) IpduM_RxIndication
(
  PduIdType RxPduId,
  P2VAR(PduInfoType, AUTOMATIC, IPDUM_APPL_DATA) PduInfoPtr
)
{
  DBG_IPDUM_RXINDICATION_ENTRY(RxPduId,PduInfoPtr);

#if (IPDUM_DEV_ERROR_DETECT == STD_ON)
  if (IPDUM_INIT != IpduM_InitStatus)
  {
    IPDUM_DET_REPORT_ERROR(IPDUM_SID_RX_INDICATION, IPDUM_E_UNINIT);
  }
#if (IPDUM_CONTAINER_PDU_HANDLING_ENABLE == STD_ON)
  else if (RxPduId >= (IPDUM_RX_PATHWAY_LEN + IPDUM_RX_CONTAINER_LEN))
#else
  else if (RxPduId >= IPDUM_RX_PATHWAY_LEN)
#endif
  {
    IPDUM_DET_REPORT_ERROR(IPDUM_SID_RX_INDICATION, IPDUM_E_PARAM);
  }
  else if (NULL_PTR == PduInfoPtr)
  {
    IPDUM_DET_REPORT_ERROR(IPDUM_SID_RX_INDICATION, IPDUM_E_PARAM_POINTER);
  }
  else if (NULL_PTR == PduInfoPtr->SduDataPtr)
  {
    IPDUM_DET_REPORT_ERROR(IPDUM_SID_RX_INDICATION, IPDUM_E_PARAM_POINTER);
  }
  else
#endif
  {
    IPDUM_RXIND_HANDLER(RxPduId, PduInfoPtr);
  }

  DBG_IPDUM_RXINDICATION_EXIT(RxPduId,PduInfoPtr);
}
/*--------------------------------------------------------------------------*/
FUNC(Std_ReturnType, IPDUM_CODE) IpduM_Transmit
(
  PduIdType TxPduId,
  P2CONST(PduInfoType, AUTOMATIC, IPDUM_APPL_DATA) PduInfoPtr
)
{
  Std_ReturnType RetValue = E_NOT_OK;

  boolean canProceed = (boolean) FALSE;

  DBG_IPDUM_TRANSMIT_ENTRY(TxPduId,PduInfoPtr);

#if (IPDUM_DEV_ERROR_DETECT == STD_ON)
  if (IPDUM_INIT != IpduM_InitStatus)
  {
    IPDUM_DET_REPORT_ERROR(IPDUM_SID_TRANSMIT, IPDUM_E_UNINIT);
  }
#if (IPDUM_CONTAINER_PDU_HANDLING_ENABLE == STD_ON)
  else if (TxPduId >= (IpduM_ConfigPtr->TxPartLen + IpduM_ConfigPtr->TxContainedPduNum))
#else
  else if (TxPduId >= IpduM_ConfigPtr->TxPartLen)
#endif
  {
    IPDUM_DET_REPORT_ERROR(IPDUM_SID_TRANSMIT, IPDUM_E_PARAM);
  }
  else if (NULL_PTR == PduInfoPtr)
  {
    IPDUM_DET_REPORT_ERROR(IPDUM_SID_TRANSMIT, IPDUM_E_PARAM_POINTER);
  }
  else if (NULL_PTR == PduInfoPtr->SduDataPtr)
  {
    if(TxPduId < IpduM_ConfigPtr->TxPartLen)
    {
      IPDUM_DET_REPORT_ERROR(IPDUM_SID_TRANSMIT, IPDUM_E_PARAM_POINTER);
    }
    else
    {
#if(IPDUM_CNTND_COLLECT_QUEUED_TX == STD_ON)
      const uint16 ContainedPduIndex = (uint16)TxPduId - (uint16)IpduM_ConfigPtr->TxPartLen;
      const uint16 ParentContainerIndex = IPDUM_CFG_GET_CNTD_TX(ContainedPduIndex)->IpduMContainerTxIndex;
      const boolean isLastIsBest = IPDUM_IS_CNTR_LAST_IS_BEST(IPDUM_CFG_GET_CNTR_TX(ParentContainerIndex)->CfgFlags);
#endif

#if(IPDUM_CNTND_COLLECT_QUEUED_TX == STD_ON)
      if(isLastIsBest)
#endif
      {
        canProceed = (boolean) TRUE;
      }
#if(IPDUM_CNTND_COLLECT_QUEUED_TX == STD_ON)
      else
      {
        IPDUM_DET_REPORT_ERROR(IPDUM_SID_TRANSMIT, IPDUM_E_PARAM_POINTER);
      }
#endif
    }
  }
#if (IPDUM_DYNAMIC_PART_QUEUE == STD_ON)
  else if (PduInfoPtr->SduLength > IPDUM_TX_SDU_SIZE)
  {
    /* if queuing is enabled, check that data fits into the queue */
    IPDUM_DET_REPORT_ERROR(IPDUM_SID_TRANSMIT, IPDUM_E_PARAM);
  }
#endif
  else
#endif
  {
    canProceed = (boolean) TRUE;
  }

  if(canProceed)
  {
#if (IPDUM_CONTAINER_PDU_HANDLING_ENABLE == STD_ON)
    if(TxPduId < IpduM_ConfigPtr->TxPartLen)
    {
#endif
      RetValue = IpduM_HandleTxPathWay(TxPduId, PduInfoPtr);
#if (IPDUM_CONTAINER_PDU_HANDLING_ENABLE == STD_ON)
    }
    else if (0U != PduInfoPtr->SduLength)
    {
      RetValue = IpduM_HandleTxContainerPdu
      (
        TxPduId
#if (IPDUM_CNTND_COLLECT_QUEUED_TX == STD_ON)
        , PduInfoPtr
#endif
      );
    }
    else
    {
      RetValue = E_OK;
    }
#endif
  }

  DBG_IPDUM_TRANSMIT_EXIT(RetValue,TxPduId,PduInfoPtr);
  return RetValue;
}

/*--------------------------------------------------------------------------*/
#if (IPDUM_ZERO_COPY == STD_OFF)
FUNC(Std_ReturnType , IPDUM_CODE) IpduM_TriggerTransmit
(
  PduIdType TxPduId,
  P2VAR(PduInfoType, AUTOMATIC, IPDUM_APPL_DATA) PduInfoPtr
)
{
  P2CONST(IpduM_TxPathWayType, AUTOMATIC, IPDUM_APPL_CONST) TxPathWay;
  P2VAR(uint8, AUTOMATIC, IPDUM_VAR_NOINIT) Buffer;
  Std_ReturnType RetValue = E_NOT_OK;

  DBG_IPDUM_TRIGGERTRANSMIT_ENTRY(TxPduId,PduInfoPtr);

#if (IPDUM_DEV_ERROR_DETECT == STD_ON)
  if (IPDUM_INIT != IpduM_InitStatus)
  {
    IPDUM_DET_REPORT_ERROR(IPDUM_SID_TRIGGER_TRANSMIT, IPDUM_E_UNINIT);
  }
  else if (NULL_PTR==PduInfoPtr)
  {
    IPDUM_DET_REPORT_ERROR(IPDUM_SID_TRIGGER_TRANSMIT, IPDUM_E_PARAM_POINTER);
  }
  else if (NULL_PTR==PduInfoPtr->SduDataPtr)
  {
    IPDUM_DET_REPORT_ERROR(IPDUM_SID_TRIGGER_TRANSMIT, IPDUM_E_PARAM_POINTER);
  }
#if (IPDUM_CONTAINER_PDU_HANDLING_ENABLE == STD_ON)
  else if (TxPduId >= (IpduM_ConfigPtr->TxPathWayLen + IpduM_ConfigPtr->TxContainerPduNum))
#else
  else if (TxPduId >= IpduM_ConfigPtr->TxPathWayLen)
#endif
  {
    IPDUM_DET_REPORT_ERROR(IPDUM_SID_TRIGGER_TRANSMIT, IPDUM_E_PARAM);
  }
  else
#endif

  {
#if (IPDUM_CONTAINER_PDU_HANDLING_ENABLE == STD_ON)
    if(TxPduId < IpduM_ConfigPtr->TxPathWayLen)
    {
#endif
      /* Ignore if the Size of the Path way is zero */
      if (IPDUM_CFG_GET_TX_PATHWAY(TxPduId)->Size > 0U)
      {
        TxPathWay = IPDUM_CFG_GET_TX_PATHWAY(TxPduId);
        RetValue = E_OK;

#if (IPDUM_ENABLE_JIT_UPDATE == STD_ON)
        {
          P2VAR(IpduM_TxDataType, AUTOMATIC, IPDUM_VAR_NOINIT) TxData;
          IpduM_JitDataType JitDataDyn = {IPDUM_RESERVED_PDUID, IPDUM_RESERVED_PDUID};
          Std_ReturnType RetValUpdDyn;
#if (IPDUM_STATIC_PART_EXISTS == STD_ON)
          /* static JIT update */
          IpduM_JitDataType JitDataStat = {IPDUM_RESERVED_PDUID, IPDUM_RESERVED_PDUID};

          /* get static JIT data */
          IpduM_GetStaticJitData(TxPathWay, &JitDataStat);

          /* JIT update of static part of multiplexed I-PDU, overrules initialized return value */
          RetValue =
              IpduM_UpdatePdu(JitDataStat.TxPduId, JitDataStat.TxPartIndex, TxPathWay, FALSE);
#endif /* (IPDUM_STATIC_PART_EXISTS == STD_ON) */

          /* dynamic JIT update */
          /* Deviation MISRAC2012-1 */
          TxData = (P2VAR(IpduM_TxDataType, AUTOMATIC, IPDUM_VAR_NOINIT))(&IpduM_GDataMemPtr[IPDUM_TX_DATA_OFFSET]);

          /* get dynamic JIT data */
          IpduM_GetDynamicJitData(TxPduId, TxData, TxPathWay, &JitDataDyn);

          /* JIT update of dynamic part of multiplexed I-PDU */
          RetValUpdDyn =
              IpduM_UpdatePdu(JitDataDyn.TxPduId, JitDataDyn.TxPartIndex, TxPathWay, FALSE);

          /* Error is returned if Up_TriggerTransmit is called erroneous either by static or dynamic
           part */
          if (RetValUpdDyn != E_OK)
          {
            RetValue = E_NOT_OK;
          }
        }
#endif /* (IPDUM_ENABLE_JIT_UPDATE == STD_ON) */

#if (IPDUM_ENABLE_JIT_UPDATE == STD_ON)
        if(RetValue == E_OK)
#endif
        {
          /* Get pointer to internal buffer */
          Buffer = &IpduM_GDataMemPtr[TxPathWay->BufferOffset];

          SchM_Enter_IpduM_SCHM_IPDUM_EXCLUSIVE_AREA_0();

          /* Copy data to output buffer */
          PduInfoPtr->SduLength = IPDUM_GET_BYTE_SIZE(TxPathWay->Size);
          IPDUM_COPY(PduInfoPtr->SduDataPtr, Buffer, PduInfoPtr->SduLength);

          SchM_Exit_IpduM_SCHM_IPDUM_EXCLUSIVE_AREA_0();
        }
      }
#if (IPDUM_CONTAINER_PDU_HANDLING_ENABLE == STD_ON)
    }
    else
    {
      RetValue = IpduM_CntrTriggerTransmit(TxPduId, PduInfoPtr);
    }
#endif /* IPDUM_CONTAINER_PDU_HANDLING_ENABLE == STD_ON */
  }

  DBG_IPDUM_TRIGGERTRANSMIT_EXIT(RetValue,TxPduId,PduInfoPtr);

  return RetValue;
}
#endif /* IPDUM_ZERO_COPY == STD_OFF */
/*--------------------------------------------------------------------------*/
FUNC(void, IPDUM_CODE) IpduM_TxConfirmation (PduIdType TxPduId)
{
  P2CONST(IpduM_TxPathWayType, AUTOMATIC, IPDUM_APPL_CONST) TxPathWayC;
  P2VAR(IpduM_TxDataType, AUTOMATIC, IPDUM_VAR_NOINIT) TxData;
  PduIdType TxDynConfirmHandleId = IPDUM_RESERVED_PDUID;

  DBG_IPDUM_TXCONFIRMATION_ENTRY(TxPduId);

#if (IPDUM_DEV_ERROR_DETECT == STD_ON)
  if (IPDUM_INIT != IpduM_InitStatus)
  {
    IPDUM_DET_REPORT_ERROR(IPDUM_SID_TX_CONFIRMATION, IPDUM_E_UNINIT);
  }
#if (IPDUM_CONTAINER_PDU_HANDLING_ENABLE == STD_ON)
  else if (TxPduId >= (IpduM_ConfigPtr->TxPathWayLen + IpduM_ConfigPtr->TxContainerPduNum))
#else
  else if (TxPduId >= IpduM_ConfigPtr->TxPathWayLen)
#endif
  {
    IPDUM_DET_REPORT_ERROR(IPDUM_SID_TX_CONFIRMATION, IPDUM_E_PARAM);
  }
  else
#endif

  {
#if(IPDUM_CONTAINER_PDU_HANDLING_ENABLE == STD_ON)
    if(TxPduId < IpduM_ConfigPtr->TxPathWayLen)
    {
#endif
      /* Ignore if the Size of the Path way is zero */
      if (IPDUM_CFG_GET_TX_PATHWAY(TxPduId)->Size > 0U)
      {
        boolean TxConfirmFlag = FALSE;

        /* Deviation MISRAC2012-1 */
        TxData = (P2VAR(IpduM_TxDataType, AUTOMATIC, IPDUM_VAR_NOINIT))(&IpduM_GDataMemPtr[IPDUM_TX_DATA_OFFSET]);

        TxPathWayC = IPDUM_CFG_GET_TX_PATHWAY(TxPduId);

        SchM_Enter_IpduM_SCHM_IPDUM_EXCLUSIVE_AREA_0();

        /* Check if we are waiting for a confirmation */
        if ((TxData[TxPduId].ConfirmationTimeoutCounter > 0U) || (TxPathWayC->ConfirmationTimeout == 0U))
        {
          if(TxData[TxPduId].ConfirmationTimeoutCounter == IPDUM_TRANSMIT_ONGOING)
          {
            /* Signal not to start the time out counter, because the PDU is confirmed before the function
             * IpduM_Transmit() has finished */
            TxData[TxPduId].ConfirmationTimeoutCounter = IPDUM_TRANSMIT_ONGOING_CONFIRMED;
          }
          else
          {
            /* Stop timeout counter */
            TxData[TxPduId].ConfirmationTimeoutCounter = 0U;
          }

          /* In the case there is a dynamic part get the dynamic confirmation ID to call the PduR with */
          if((IPDUM_RESERVED_PDUID != TxData[TxPduId].PduRTxConfirmationPduId) &&
              (TxPathWayC->DynamicConfirmArraySize != 0U))
          {
            /* Store handle ID for TxConfirmation of dynamic part for later use */
            TxDynConfirmHandleId = TxData[TxPduId].PduRTxConfirmationPduId;

            /* Reset stored ID for confirmation of dynamic part */
            TxData[TxPduId].PduRTxConfirmationPduId = IPDUM_RESERVED_PDUID;

            /* TxData[TxPduId].PduRTriggerTxPduId and TxData[TxPduId].DynamicPartIndex are not reset,
             they refer always to the last part transmitted relevant for JIT update */
          }

          /* Call the confirmation outside the exclusive area */
          TxConfirmFlag = TRUE;
        }
        SchM_Exit_IpduM_SCHM_IPDUM_EXCLUSIVE_AREA_0();

        if (TxConfirmFlag == TRUE)
        {

#if (IPDUM_STATIC_PART_EXISTS == STD_ON)
          /* Call PduR_IpduM_TxConfirmation for the static part */
          if (IPDUM_RESERVED_PDUID != TxPathWayC->StaticPartTxConfHandleId)
          {
            PduR_IpduMTxConfirmation(TxPathWayC->StaticPartTxConfHandleId);
          }
#endif

          /* do PduR_IpduMTxConfirmation() if we have found a matching dynamic part */
          if (IPDUM_RESERVED_PDUID != TxDynConfirmHandleId)
          {
            /* Call PduR_IpduM_TxConfirmation for the dynamic part */
            PduR_IpduMTxConfirmation(TxDynConfirmHandleId);
          }
        }
      }
#if (IPDUM_CONTAINER_PDU_HANDLING_ENABLE == STD_ON)
    }
    else
    {
      IpduM_CntrTxConfirmation(TxPduId);
    }
#endif /* IPDUM_CONTAINER_PDU_HANDLING_ENABLE == STD_ON */
  }

  DBG_IPDUM_TXCONFIRMATION_EXIT(TxPduId);
}

#if(IPDUM_DEDICATED_IPDU_PROCESSING_SUPPORT == STD_OFF)
FUNC(void, IPDUM_CODE) IpduM_MainFunctionRx(void)
#else
FUNC(void, IPDUM_CODE) IpduM_MainFunctionRx_Generic
(
  IpduM_MainFuncIdxType MFIdx
)
#endif
{

  DBG_IPDUM_MAINFUNCTIONRX_ENTRY();

#if (IPDUM_CONTAINER_PDU_HANDLING_ENABLE == STD_ON)
  if (IPDUM_INIT == IpduM_InitStatus)
  {
    if(0U != IPDUM_RX_CONTAINER_PROCESSING_DEFERRED_NO)
    {
      /* Deviation MISRAC2012-1 */
      P2VAR(uint32, AUTOMATIC, IPDUM_VAR_NOINIT) deferredListPtr = IPDUM_GET_DEFERRED_LIST(MFIdx);
      uint8 localDataBuffer[IPDUM_MAX_CONTAINER_RX_LENGTH];
      PduInfoType stPduInfo;
      uint32 ContainerRxIndex;

      /* Deviation MISRAC2012-6 */
      /* Deviation MISRAC2012-7 */
      for(IPDUM_COMSTACK_BF_ITERATE(ContainerRxIndex, deferredListPtr, COMSTACK_BF_START, IPDUM_RX_CONTAINER_PROCESSING_DEFERRED_NO))
      {
        /* Deviation MISRAC2012-1 */
        P2VAR(uint8, AUTOMATIC, AUTOMATIC) deferredDataPtr = IPDUM_GET_DEFERRED_DATA(ContainerRxIndex);
#if (IPDUM_CONTAINER_QUEUING_RX == STD_ON)
        P2CONST(IpduM_ContainerRxPduType, AUTOMATIC, IPDUM_APPL_CONST) cntrPtr = IPDUM_CFG_GET_CNTR_RX(ContainerRxIndex);
        BufReq_ReturnType ret = BUFREQ_E_BUSY;
#endif
        const uint16 cntrByteIdx = (uint16)(ContainerRxIndex / 32U);
        const uint8 cntrBitIdx = ContainerRxIndex % 32U;

        TS_AtomicClearBit_32(&deferredListPtr[cntrByteIdx], cntrBitIdx);

        stPduInfo.SduDataPtr = localDataBuffer;

#if (IPDUM_CONTAINER_QUEUING_RX == STD_ON)
        while(BUFREQ_E_NOT_OK != ret)
        {
          stPduInfo.SduLength = 0U;

          if(cntrPtr->ContainerQueueSize > 0U)
          {
          SchM_Enter_IpduM_SCHM_IPDUM_EXCLUSIVE_AREA_0();
          /* Deviation MISRAC2012-1 */
          ret = IPDUM_CNTRQ(POP, RX, ContainerRxIndex, deferredDataPtr, stPduInfo.SduDataPtr, &stPduInfo.SduLength);
          SchM_Exit_IpduM_SCHM_IPDUM_EXCLUSIVE_AREA_0();
          }
          else
#endif /* IPDUM_CONTAINER_QUEUING_RX == STD_ON */
          {
            stPduInfo.SduLength = 0U;

            SchM_Enter_IpduM_SCHM_IPDUM_EXCLUSIVE_AREA_0();
            TS_MemCpy(&stPduInfo.SduLength, &deferredDataPtr[0U], sizeof(PduLengthType));
            TS_MemCpy(&stPduInfo.SduDataPtr[0U], &deferredDataPtr[sizeof(PduLengthType)], stPduInfo.SduLength);
            SchM_Exit_IpduM_SCHM_IPDUM_EXCLUSIVE_AREA_0();

#if (IPDUM_CONTAINER_QUEUING_RX == STD_ON)
            /* Terminate the inner loop after processing */
            ret = BUFREQ_E_NOT_OK;
#endif
          }

          if(0U < stPduInfo.SduLength)
          {
            IpduM_HandleRxContainerPdu(ContainerRxIndex, &stPduInfo);
          }
#if (IPDUM_CONTAINER_QUEUING_RX == STD_ON)
        } /* end while */
#endif
      } /* end for */
    } /* deferred */
  }
#endif

  DBG_IPDUM_MAINFUNCTIONRX_EXIT();
}
#if(IPDUM_DEDICATED_IPDU_PROCESSING_SUPPORT == STD_OFF)
FUNC(void, IPDUM_CODE) IpduM_MainFunctionTx(void)
#else
FUNC(void, IPDUM_CODE) IpduM_MainFunctionTx_Generic
(
  IpduM_MainFuncIdxType MFIdx
)
#endif
{
  uint16 index;
#if(IPDUM_DEDICATED_IPDU_PROCESSING_SUPPORT == STD_ON)
  IpduM_MainFuncIdxType i;
#endif
  P2VAR(IpduM_TxDataType, AUTOMATIC, IPDUM_VAR_NOINIT) TxData;

#if (IPDUM_DYNAMIC_PART_QUEUE == STD_ON)
  P2CONST(IpduM_TxPathWayType, AUTOMATIC, IPDUM_APPL_CONST) TxPathWayMain;
  P2CONST(IpduM_TxPartType, AUTOMATIC, IPDUM_APPL_CONST) TxPartMain;
#if (IPDUM_ZERO_COPY == STD_OFF)
  P2VAR(uint8, AUTOMATIC, IPDUM_VAR_NOINIT) TxBuffer;
#endif
#endif

  DBG_IPDUM_MAINFUNCTIONTX_ENTRY();

  if (IPDUM_INIT == IpduM_InitStatus)
  {
#if(IPDUM_DEDICATED_IPDU_PROCESSING_SUPPORT == STD_OFF)
    for(index=0U; index<IPDUM_TX_PATHWAY_LEN; index++)
    {
#else
    for(i=1U; i<=IPDUM_GET_TX_MF_IDX(MFIdx); i++)
    {
      index = IPDUM_GET_TX_MF_IDX(MFIdx + i);
      if(index >= IPDUM_TX_PATHWAY_LEN)
      {
        /* Jump over Container indices */
        continue;
      }
#endif
      /* Check for valid PduIds */
      if (IPDUM_CFG_GET_TX_PATHWAY(index)->Size > 0U)
      {
#if (IPDUM_DYNAMIC_PART_QUEUE == STD_ON)
        PduInfoType PduInfo;
        boolean TxFlag = FALSE;
        PduIdType TxPduId = 0U;
#endif

        /* Deviation MISRAC2012-1 */
        TxData = (P2VAR(IpduM_TxDataType, AUTOMATIC, IPDUM_VAR_NOINIT))(&IpduM_GDataMemPtr[IPDUM_TX_DATA_OFFSET]);

        SchM_Enter_IpduM_SCHM_IPDUM_EXCLUSIVE_AREA_0();

        /* Check for pending requests */
        if (TxData[index].ConfirmationTimeoutCounter>=IPDUM_TRANSMIT_ONGOING_CONFIRMED)
        {
          /* the main function just preempted a call to PduR_IpduMTransmit() =>
           * do nothing */
        }
        else if (TxData[index].ConfirmationTimeoutCounter>0U)
        {
          /* a call to PduR_IpduMTransmit() has completed and we're waiting
           * for the corresponding confirmation */

          /* decrease timer */
          TxData[index].ConfirmationTimeoutCounter--;
        }
#if (IPDUM_DYNAMIC_PART_QUEUE != STD_ON)
        else
        {
        }
#else /* (IPDUM_DYNAMIC_PART_QUEUE != STD_ON) */
        else
        {
          P2VAR(IpduM_QueueEntryType, AUTOMATIC, IPDUM_VAR_NOINIT) QueueEntry;

          /* Get entry with highest priority */
          QueueEntry = IpduM_RemoveQueue(index);

          if (NULL_PTR != QueueEntry)
          {
#if (IPDUM_ZERO_COPY == STD_ON)
            uint8 SduDataBuffer[IPDUM_TX_SDU_SIZE];
#endif
            TxPduId = QueueEntry->TxPduId;

            /* Get pointer of TxPathWay */
            TxPathWayMain = IPDUM_CFG_GET_TX_PATHWAY(index);

            /* set timeout counter to special value for ongoing calls to
             * PduR_IpduMTransmit() - will be set to correct timeout value after
             * PduR_IpduMTransmit() has returned */
            TxData[index].ConfirmationTimeoutCounter = IPDUM_TRANSMIT_ONGOING;

            /* Set PDU Info */
            PduInfo.SduLength = IPDUM_GET_BYTE_SIZE(TxPathWayMain->Size);

            /* TxPathWay is the same, but TxPartMain may have been changed */
            TxPartMain = IPDUM_CFG_GET_TX_PART(TxPduId);

#if (IPDUM_ZERO_COPY == STD_OFF)
            /* Get pointer to static buffer */
            TxBuffer = &IpduM_GDataMemPtr[TxPathWayMain->BufferOffset];

            /* Assemble PDU */
            (void)IpduM_BitCopy(TxBuffer,
                QueueEntry->SduData,
                IPDUM_CFG_GET_TX_COPY_BITFIELD(TxPartMain),
                TxPartMain->CopyBitFieldArraySize);

            /* Set PDU Info */
            PduInfo.SduDataPtr = &TxBuffer[0];

            /* Automatically set selector value */
#if (IPDUM_AUTOMATIC_SELECTOR == STD_ON)
            IPDUM_SET_SELECTOR(PduInfo.SduDataPtr,
                TxPartMain->SelectorValue,
                TxPathWayMain->StartBit,
                TxPathWayMain->EndBit);
#endif
#else /* (IPDUM_ZERO_COPY == STD_OFF) */

            /* copy data from queue element to local buffer, since after we've
             * left the critical section another IpduM_Transmit() or the
             * IpduM_MainFunctionTx() might preempt us and modify the queue
             * adjust the source data pointer according to the start bit
             * (in the zero copy case only a single CopyBitField is allowed) */
            IPDUM_COPY(SduDataBuffer, &QueueEntry->SduData[IPDUM_GET_BYTE_OFFSET(IPDUM_CFG_GET_TX_COPY_BITFIELD(TxPartMain)->StartBit)], PduInfo.SduLength);

            /* Set PDU Info */
            PduInfo.SduDataPtr = SduDataBuffer;
#endif /* (IPDUM_ZERO_COPY == STD_OFF) */

            TxData[TxPartMain->TxConfirmationPduId].PduRTxConfirmationPduId =
                QueueEntry->PduRTxConfirmationPduId;

            TxFlag = TRUE;
          }
        }
#endif /* (IPDUM_DYNAMIC_PART_QUEUE != STD_ON) */

        SchM_Exit_IpduM_SCHM_IPDUM_EXCLUSIVE_AREA_0();

#if (IPDUM_DYNAMIC_PART_QUEUE == STD_ON)
        if (TxFlag == TRUE)
        {
          Std_ReturnType RetValue;

          /* Get pointer of TxPathWay */
          TxPathWayMain = IPDUM_CFG_GET_TX_PATHWAY(index);

          /* Get TxPartMain */
          TxPartMain = IPDUM_CFG_GET_TX_PART(TxPduId);

          /* Transmit frame */
          RetValue = PduR_IpduMTransmit(
              TxPartMain->TxOutgoingPduId,
              &PduInfo
          );

          if (E_NOT_OK == RetValue)
          {
            /* The transmit failed, reset confirmation timer so that other frames
             * can be transmitted */
            TS_AtomicAssign16(TxData[index].ConfirmationTimeoutCounter, 0);
          }
          else
          {
            /* Start timer for timeout surveillance */
            TS_AtomicAssign16(TxData[index].ConfirmationTimeoutCounter, TxPathWayMain->ConfirmationTimeout);
          }
        }
#endif /* (IPDUM_DYNAMIC_PART_QUEUE == STD_ON) */
      }
    }

#if (IPDUM_CONTAINER_PDU_HANDLING_ENABLE == STD_ON)
#if(IPDUM_DEDICATED_IPDU_PROCESSING_SUPPORT == STD_OFF)
    IpduM_CntrHandleTimers();
#else
    IpduM_CntrHandleTimers(MFIdx);
#endif /* IPDUM_DEDICATED_IPDU_PROCESSING_SUPPORT == STD_OFF */
#endif /* IPDUM_CONTAINER_PDU_HANDLING_ENABLE == STD_ON */
  }

  DBG_IPDUM_MAINFUNCTIONTX_EXIT();
}



/*--------------------------------------------------------------------------*/
#if (IPDUM_VERSION_INFO_API == STD_ON)
FUNC(void, IPDUM_CODE) IpduM_GetVersionInfo
(
  CONSTP2VAR(Std_VersionInfoType, AUTOMATIC, IPDUM_APPL_DATA) versioninfo
)
{
  DBG_IPDUM_GETVERSIONINFO_ENTRY(versioninfo);
#if (IPDUM_DEV_ERROR_DETECT == STD_ON)

  if (NULL_PTR==versioninfo)
  {
    IPDUM_DET_REPORT_ERROR(IPDUM_SID_GET_VERSION_INFO, IPDUM_E_PARAM_POINTER);
  }
  else
#endif

  {
    versioninfo->vendorID         = IPDUM_VENDOR_ID;
    versioninfo->moduleID         = IPDUM_MODULE_ID;
    versioninfo->sw_major_version = IPDUM_SW_MAJOR_VERSION;
    versioninfo->sw_minor_version = IPDUM_SW_MINOR_VERSION;
    versioninfo->sw_patch_version = IPDUM_SW_PATCH_VERSION;
  }

  DBG_IPDUM_GETVERSIONINFO_EXIT(versioninfo);
}
#endif

/*--------------------------------------------------------------------------*/

#define IPDUM_STOP_SEC_CODE
#include <IpduM_MemMap.h>

/*==================[internal function definitions]=========================*/

#define IPDUM_START_SEC_CODE
#include <IpduM_MemMap.h>

#if (IPDUM_ZERO_COPY == STD_OFF)
IPDUM_STATIC FUNC(PduLengthType, IPDUM_CODE) IpduM_BitCopy
(
  P2VAR(uint8, AUTOMATIC, IPDUM_APPL_DATA) Dest,
  P2CONST(uint8, AUTOMATIC, IPDUM_APPL_DATA) Src,
  P2CONST(IpduM_CopyBitFieldType, AUTOMATIC, IPDUM_APPL_CONST) CopyBitField,
  IpduM_BitfieldArraySizeType Size
)
{
  IpduM_BitfieldArraySizeType i;
  uint8 SrcOffset;
  uint8 DstOffset = 0U;
  PduLengthType LastByte = 0U;

  for (i=0U; i<Size; i++)
  {
#if (IPDUM_BYTE_COPY == STD_ON)
    uint8 Length = (uint8) IPDUM_GET_BYTE_SIZE(CopyBitField[i].EndBit-CopyBitField[i].StartBit);
    SrcOffset = (uint8) IPDUM_GET_BYTE_OFFSET(CopyBitField[i].StartBit);
    DstOffset = (uint8) IPDUM_GET_BYTE_OFFSET(CopyBitField[i].DestinationBit);

    /* Copy data bytewise */
    IPDUM_COPY(&Dest[DstOffset], &Src[SrcOffset], Length);

    if (((PduLengthType) DstOffset + (PduLengthType) Length) > LastByte)
    {
        LastByte = ((PduLengthType) DstOffset + (PduLengthType) Length);
    }
#else
    uint16 j;
    uint16 Length = CopyBitField[i].EndBit-CopyBitField[i].StartBit;

    /* Copy data bitwise */
    for (j=0U; j<=Length; j++)
    {
      /* Src and Dst offset in bytes */
      SrcOffset = (uint8)((uint16)(CopyBitField[i].StartBit+j)>>3U);
      DstOffset = (uint8)((uint16)(CopyBitField[i].DestinationBit+j)>>3U);

      /* First clear bit, because destination can be initialized with any value */
      Dest[DstOffset] &= (uint8)(~(uint8)(1U<<
                          (IPDUM_MODULO_8((uint16)(CopyBitField[i].DestinationBit+j)))));

      /* Set bit */
      Dest[DstOffset] |= (uint8)(((uint8)(Src[SrcOffset]>>
                          (IPDUM_MODULO_8((uint16)(CopyBitField[i].StartBit+j))))&1U) <<
                          (IPDUM_MODULO_8((uint16)(CopyBitField[i].DestinationBit+j))));

    }
    if ( DstOffset > LastByte)
    {
        LastByte = DstOffset;
    }
#endif
  }

  return LastByte + 1U;
}
#endif

/*--------------------------------------------------------------------------*/
#if (IPDUM_ZERO_COPY == STD_OFF)
IPDUM_STATIC FUNC(void, IPDUM_CODE) IpduM_PreparePdu
(
  P2CONST(IpduM_TxPathWayType, AUTOMATIC, IPDUM_APPL_CONST) TxPathWay
)
{
  uint8 i;
  uint8 Size;
  P2VAR(uint8, AUTOMATIC, IPDUM_VAR_NOINIT) Buffer;

  Buffer = &IpduM_GDataMemPtr[TxPathWay->BufferOffset];

  /* Convert from bits to bytes */
  Size = (uint8) IPDUM_GET_BYTE_SIZE(TxPathWay->Size);

  /* set default values */
  for (i=0U; i<Size; i++)
  {
    Buffer[i] = TxPathWay->UnusedAreasDefault;
  }
}
#endif

#if (IPDUM_DYNAMIC_PART_QUEUE == STD_ON)
/*--------------------------------------------------------------------------*/
IPDUM_STATIC FUNC(Std_ReturnType, IPDUM_CODE) IpduM_InsertQueue
(
  PduIdType TxPduId,
  PduIdType PduRTxConfirmationPduId,
  P2CONST(PduInfoType, AUTOMATIC, IPDUM_APPL_DATA) PduInfoPtr,
  uint16 DynamicPriority
)
{
  uint8 i;
  IpduM_QueueEntryType key;
  P2VAR(IpduM_QueueEntryType, AUTOMATIC, IPDUM_VAR_NOINIT) Queue;
  P2VAR(uint8, AUTOMATIC, IPDUM_VAR_NOINIT) QueuePosition;
  P2CONST(IpduM_TxPathWayType, AUTOMATIC, IPDUM_APPL_CONST) TxPathWayIQ;
  P2VAR(IpduM_TxDataType, AUTOMATIC, IPDUM_VAR_NOINIT) TxData;
  Std_ReturnType RetValue = E_NOT_OK;

  /* Get TxPathWay */
  PduIdType TxConfPduId = IPDUM_CFG_GET_TX_PART(TxPduId)->TxConfirmationPduId;
  TxPathWayIQ = IPDUM_CFG_GET_TX_PATHWAY(TxConfPduId);

  /* Insert entry if there is a queue, otherwise return E_NOT_OK to indicate that the PDU can not
   * be transmitted while a transmission is ongoing */
  if(TxPathWayIQ->QueueSize > 0U)
  {
    RetValue = E_OK;

    /* Get TxData */
    /* Deviation MISRAC2012-1 */
    TxData = (P2VAR(IpduM_TxDataType, AUTOMATIC, IPDUM_VAR_NOINIT))(&IpduM_GDataMemPtr[IPDUM_TX_DATA_OFFSET]);

    /* Get start address of queue for this PDU */
    /* Deviation MISRAC2012-1 */
    Queue = (P2VAR(IpduM_QueueEntryType, AUTOMATIC, IPDUM_VAR_NOINIT))(&IpduM_GDataMemPtr[TxPathWayIQ->QueueOffset]);

    /* Get Queue position */
    QueuePosition = &TxData[TxConfPduId].QueuePos;

    /* First check if PDU is already queued */
    for (i=0U; i<(*QueuePosition); i++)
    {
      if (Queue[i].TxPduId == TxPduId)
      {
        RetValue = E_NOT_OK;
      }
    }

    if (E_OK == RetValue)
    {
      if ((*QueuePosition) >= TxPathWayIQ->QueueSize)
      {
        /* Queue full, check if priority is higher than job with lowest priority */
        if ( DynamicPriority < Queue[0].DynamicPriority )
        {
          /* Priority is higher, overwrite lowest priority job */
          Queue[0].TxPduId = TxPduId;
          Queue[0].PduRTxConfirmationPduId = PduRTxConfirmationPduId;
          IPDUM_COPY(Queue[0].SduData, PduInfoPtr->SduDataPtr, PduInfoPtr->SduLength);
          Queue[0].DynamicPriority = DynamicPriority;

          /* Sort queue */
          i=0U;
          while(((i+1U)<TxPathWayIQ->QueueSize) && (Queue[i].DynamicPriority<Queue[i+1U].DynamicPriority))
          {
            /* Swap entries */
            key = Queue[i];
            Queue[i] = Queue[i+1U];
            Queue[i+1U] = key;
            i++;
          }
        }
        else
        {
          /* Priority is lower, job cannot be queued */
          RetValue = E_NOT_OK;
        }
      }
      else
      {
        /* Queue not full, insert entry */
        Queue[(*QueuePosition)].TxPduId = TxPduId;
        Queue[(*QueuePosition)].PduRTxConfirmationPduId = PduRTxConfirmationPduId;
        IPDUM_COPY(Queue[(*QueuePosition)].SduData, PduInfoPtr->SduDataPtr, PduInfoPtr->SduLength);
        Queue[(*QueuePosition)].DynamicPriority = DynamicPriority;

        /* Sort queue according to priority */
        i=(*QueuePosition);
        while((i>0U) && (Queue[i].DynamicPriority>=Queue[i-1U].DynamicPriority))
        {
          /* Swap entries */
          key = Queue[i];
          Queue[i] = Queue[i-1U];
          Queue[i-1U] = key;
          i--;
        }
        /* Set position to next free element */
        (*QueuePosition)++;
      }
    }
  }

  return RetValue;
}

/*--------------------------------------------------------------------------*/
/* Deviation MISRAC2012-2 */
IPDUM_STATIC FUNC(FUNC_P2VAR(IpduM_QueueEntryType, AUTOMATIC, IPDUM_VAR_NOINIT), IPDUM_CODE) IpduM_RemoveQueue
(
    PduIdType TxConfirmationPduId
)
{
  P2VAR(IpduM_QueueEntryType, AUTOMATIC, IPDUM_VAR_NOINIT) Queue;
  P2VAR(IpduM_QueueEntryType, AUTOMATIC, IPDUM_VAR_NOINIT) NextEntry;
  P2VAR(uint8, AUTOMATIC, IPDUM_VAR_NOINIT) QueuePosition;
  P2CONST(IpduM_TxPathWayType, AUTOMATIC, IPDUM_APPL_CONST) TxPathWayRQ;
  P2VAR(IpduM_TxDataType, AUTOMATIC, IPDUM_VAR_NOINIT) TxData;

  /* Get TxPathWay */
  TxPathWayRQ = IPDUM_CFG_GET_TX_PATHWAY(TxConfirmationPduId);

  /* Get TxData */
  /* Deviation MISRAC2012-1 */
  TxData = (P2VAR(IpduM_TxDataType, AUTOMATIC, IPDUM_VAR_NOINIT))(&IpduM_GDataMemPtr[IPDUM_TX_DATA_OFFSET]);

  /* Get start address of queue for this PDU */
  /* Deviation MISRAC2012-1 */
  Queue = (P2VAR(IpduM_QueueEntryType, AUTOMATIC, IPDUM_VAR_NOINIT))(&IpduM_GDataMemPtr[TxPathWayRQ->QueueOffset]);

  /* Get start address of queue for this PDU */
  QueuePosition = &TxData[TxConfirmationPduId].QueuePos;

  if ( (*(QueuePosition) > 0U) &&
       ((Queue[(*QueuePosition)-1U].DynamicPriority&IPDUM_PRIO_NOT_READY_TO_SEND)!=IPDUM_PRIO_NOT_READY_TO_SEND)
     )
  {
    /* Return job with highest priority */
    NextEntry = &Queue[(*QueuePosition)-1U];

    /* Remove element */
    (*QueuePosition)--;
  }
  else
  {
    NextEntry = NULL_PTR;
  }

  return NextEntry;
}

/*--------------------------------------------------------------------------*/
IPDUM_STATIC FUNC(Std_ReturnType, IPDUM_CODE) IpduM_HandleQueueFilling
(
    PduIdType TxPduId,
    P2CONST(PduInfoType, AUTOMATIC, IPDUM_APPL_DATA) PduInfoPtr,
    P2CONST(IpduM_TxPathWayType, AUTOMATIC, IPDUM_APPL_CONST) TxPathWayT,
    P2CONST(IpduM_TxPartType, AUTOMATIC, IPDUM_APPL_CONST) TxPartT,
    PduTxInfoType PduTxInfoPtr,
    P2VAR(PduIdType, AUTOMATIC, IPDUM_APPL_DATA) PdumDynamicTxPduIdPtr,
    P2VAR(PduIdType, AUTOMATIC, IPDUM_APPL_DATA) PduRTxConfirmationPduIdPtr,
    P2VAR(boolean, AUTOMATIC, IPDUM_APPL_DATA) ImmediatelySendPtr
)
{
  Std_ReturnType RetValue;
  uint16 DynPriority;

#if (IPDUM_ZERO_COPY == STD_ON)
  TS_PARAM_UNUSED(PduTxInfoPtr);
#else /* (IPDUM_ZERO_COPY == STD_ON) */
  /* Static or dynamic part */
  if (TxPduId < IpduM_ConfigPtr->TxDynamicPartOffset)
  {
    RetValue = E_OK;

    /* Static */
    if ((TxPathWayT->TriggerMode & IPDUM_TRIGGER_STATIC) == IPDUM_TRIGGER_STATIC)
    {
      P2VAR(IpduM_QueueEntryType, AUTOMATIC, IPDUM_VAR_NOINIT) QueueEntry;

      /* Trigger condition fulfilled, increase priority for pending dynamic PDUs */
      IpduM_SetDynamicPduReadyToSend(TxPduId);

      /* Remove entry with highest priority */
      QueueEntry = IpduM_RemoveQueue(TxPartT->TxConfirmationPduId);

      /* Copy only if a dynamic part exists */
      if (NULL_PTR != QueueEntry)
      {
        /* Get pointer to static buffer */
        PduTxInfoPtr->SduDataPtr = &IpduM_GDataMemPtr[TxPathWayT->BufferOffset];

        /* Assemble dynamic PDU */
        PduTxInfoPtr->SduLength = IpduM_BitCopy(PduTxInfoPtr->SduDataPtr,
        QueueEntry->SduData,
        IPDUM_CFG_GET_TX_COPY_BITFIELD(IPDUM_CFG_GET_TX_PART(QueueEntry->TxPduId)),
        IPDUM_CFG_GET_TX_PART(QueueEntry->TxPduId)->CopyBitFieldArraySize);

        /* Store PDU IDs for dynamic part (currently retrieved from queue) */
        *PdumDynamicTxPduIdPtr = QueueEntry->TxPduId;
        *PduRTxConfirmationPduIdPtr = QueueEntry->PduRTxConfirmationPduId;
      }

      /* And mark for immediately sending */
      *ImmediatelySendPtr = TRUE;
    }
  }
  else
#endif /* (IPDUM_ZERO_COPY == STD_ON) */
  {
    RetValue = E_OK;

    /* dynamic part (when IPDUM_ZERO_COPY == STD_ON the must not be a static part) */

    /* Set priority */
    DynPriority = TxPartT->DynamicPriority;

    /* Dynamic triggering condition fulfilled? */
    if ((TxPathWayT->TriggerMode & IPDUM_TRIGGER_DYNAMIC) != IPDUM_TRIGGER_DYNAMIC)
    {
      /* Trigger condition not fulfilled, mark as not to send */
      DynPriority |= IPDUM_PRIO_NOT_READY_TO_SEND;
    }

    /* Check if priority is higher than highest in queue and triggered */
    if ((DynPriority < IpduM_GetMaxPriorityQueue(TxPduId)) &&
        (DynPriority < IPDUM_PRIO_NOT_READY_TO_SEND))
    {
      /* Priority is higher than in queue, send immediately */
      *ImmediatelySendPtr = TRUE;

      /* Store PDU IDs for dynamic part (currently passed via API) */
      *PdumDynamicTxPduIdPtr = TxPduId;
      *PduRTxConfirmationPduIdPtr = TxPartT->PduRTxConfirmationPduId;
    }
    else
    {
      /* Priority is lesser than in queue, put into queue */
      RetValue = IpduM_InsertQueue(TxPduId,
              TxPartT->PduRTxConfirmationPduId,
              PduInfoPtr,
              DynPriority);
    }
  }

  return RetValue;
}

/*--------------------------------------------------------------------------*/
#if (IPDUM_ZERO_COPY == STD_OFF)
IPDUM_STATIC FUNC(void, IPDUM_CODE) IpduM_SetDynamicPduReadyToSend(PduIdType TxPduId)
{
  uint8 i;
  P2VAR(IpduM_QueueEntryType, AUTOMATIC, IPDUM_VAR_NOINIT) Queue;
  P2VAR(uint8, AUTOMATIC, IPDUM_VAR_NOINIT) QueuePos;
  P2CONST(IpduM_TxPathWayType, AUTOMATIC, IPDUM_APPL_CONST) TxPathWay;
  P2VAR(IpduM_TxDataType, AUTOMATIC, IPDUM_VAR_NOINIT) TxData;

  /* Get TxPathWay */
  PduIdType TxConfPduId = IPDUM_CFG_GET_TX_PART(TxPduId)->TxConfirmationPduId;
  TxPathWay = IPDUM_CFG_GET_TX_PATHWAY(TxConfPduId);

  /* Get TxData */
  /* Deviation MISRAC2012-1 */
  TxData = (P2VAR(IpduM_TxDataType, AUTOMATIC, IPDUM_VAR_NOINIT))(&IpduM_GDataMemPtr[IPDUM_TX_DATA_OFFSET]);

  /* Get start address of queue for this PDU */
  /* Deviation MISRAC2012-1 */
  Queue = (P2VAR(IpduM_QueueEntryType, AUTOMATIC, IPDUM_VAR_NOINIT))(&IpduM_GDataMemPtr[TxPathWay->QueueOffset]);

  /* Get Queue position */
  QueuePos = &TxData[IPDUM_CFG_GET_TX_PART(TxPduId)->TxConfirmationPduId].QueuePos;

  /* Set PDU to ready for send */
  for(i=0; i<(*QueuePos);i++)
  {
    Queue[i].DynamicPriority &= (uint16)(~IPDUM_PRIO_NOT_READY_TO_SEND);
  }

}
#endif

/*--------------------------------------------------------------------------*/
IPDUM_STATIC FUNC(uint16, IPDUM_CODE) IpduM_GetMaxPriorityQueue(PduIdType TxPduId)
{
  uint8 QueuePosition;
  P2VAR(IpduM_QueueEntryType, AUTOMATIC, IPDUM_VAR_NOINIT) Queue;
  P2CONST(IpduM_TxPathWayType, AUTOMATIC, IPDUM_APPL_CONST) TxPathWayGM;
  P2VAR(IpduM_TxDataType, AUTOMATIC, IPDUM_VAR_NOINIT) TxData;
  uint16 Priority=IPDUM_PRIO_LOWEST_POSSIBLE;

  /* Get TxPathWay */
  PduIdType TxConfPduId = IPDUM_CFG_GET_TX_PART(TxPduId)->TxConfirmationPduId;
  TxPathWayGM = IPDUM_CFG_GET_TX_PATHWAY(TxConfPduId);

  /* Get TxData */
  /* Deviation MISRAC2012-1 */
  TxData = (P2VAR(IpduM_TxDataType, AUTOMATIC, IPDUM_VAR_NOINIT))(&IpduM_GDataMemPtr[IPDUM_TX_DATA_OFFSET]);

  /* Get start address of queue for this PDU */
  /* Deviation MISRAC2012-1 */
  Queue = (P2VAR(IpduM_QueueEntryType, AUTOMATIC, IPDUM_VAR_NOINIT))(&IpduM_GDataMemPtr[TxPathWayGM->QueueOffset]);

  /* Get Queue position */
  QueuePosition = TxData[TxConfPduId].QueuePos;

  if (QueuePosition > 0U)
  {
      Priority = Queue[QueuePosition - 1U].DynamicPriority;
  }

  return Priority;
}
#endif


/*--------------------------------------------------------------------------*/
#if (IPDUM_ENABLE_JIT_UPDATE == STD_ON) || \
    (IPDUM_INITIALIZATION_BY_SIGNAL_VALUE == STD_ON)
IPDUM_STATIC FUNC(Std_ReturnType, IPDUM_CODE) IpduM_UpdatePdu
(
  PduIdType PduRTriggerTxPduId,
  PduIdType TxPartIndex,
  P2CONST(IpduM_TxPathWayType, AUTOMATIC, IPDUM_APPL_CONST) TxPathWay,
  boolean IsInit
)
{
  Std_ReturnType RetVal;

  /* JIT update of multiplexed I-PDU */
  if (PduRTriggerTxPduId != IPDUM_RESERVED_PDUID)
  {
    CONSTP2CONST(IpduM_TxPartType, AUTOMATIC, IPDUM_APPL_CONST) TxPartU =
      IPDUM_CFG_GET_TX_PART(TxPartIndex);
    uint8 TrigTxBuffer[IPDUM_TX_SDU_SIZE];
    PduInfoType PduInfoTrigTx;

    /* prepare PDU for TriggerTransmit */
    PduInfoTrigTx.SduDataPtr = &TrigTxBuffer[0];
    PduInfoTrigTx.SduLength = IPDUM_TX_SDU_SIZE;

    /* get update of PDU */
    RetVal = PduR_IpduMTriggerTransmit(PduRTriggerTxPduId, &PduInfoTrigTx);

    /* segment copied also in case of an erroneous call of the PduR within IpduM_Init,
       necessary for initialization where the Com_TriggerTransmit returns E_NOT_OK  */
    if((IsInit == TRUE) ||
       ((IsInit == FALSE) && (RetVal == E_OK )))
    {
      SchM_Enter_IpduM_SCHM_IPDUM_EXCLUSIVE_AREA_0();

      /* unhandled return value of PduLengthType */
      (void)IpduM_BitCopy(&IpduM_GDataMemPtr[TxPathWay->BufferOffset],
                          PduInfoTrigTx.SduDataPtr,
                          IPDUM_CFG_GET_TX_COPY_BITFIELD(TxPartU),
                          TxPartU->CopyBitFieldArraySize);

      SchM_Exit_IpduM_SCHM_IPDUM_EXCLUSIVE_AREA_0();
    }
  }
  else
  {
    RetVal = E_OK;
  }

  return RetVal;
}
#endif /* (IPDUM_ENABLE_JIT_UPDATE == STD_ON) || .. */


#if (IPDUM_ENABLE_JIT_UPDATE == STD_ON)
IPDUM_STATIC FUNC(void, IPDUM_CODE) IpduM_GetJitDataTransmit
(
  PduIdType TxPduId,
  P2CONST(IpduM_TxPartType, AUTOMATIC, IPDUM_APPL_CONST) TxPart,
  P2CONST(IpduM_TxDataType, AUTOMATIC, IPDUM_APPL_DATA) TxData,
  P2CONST(IpduM_TxPathWayType, AUTOMATIC, IPDUM_APPL_CONST) TxPathWay,
  P2VAR(IpduM_JitDataType, AUTOMATIC, IPDUM_APPL_DATA) JitData
)
{

  if(TxPduId < IpduM_ConfigPtr->TxDynamicPartOffset)
  /* static trigger condition fulfilled */
  {
    IpduM_GetDynamicJitData(TxPart->TxConfirmationPduId, TxData, TxPathWay, JitData);
  }
#if (IPDUM_STATIC_PART_EXISTS == STD_ON)
  else
  /* dynamic trigger condition fulfilled */
  {
    IpduM_GetStaticJitData(TxPathWay, JitData);
  }
#endif /* (IPDUM_STATIC_PART_EXISTS == STD_ON) */

}


#if (IPDUM_STATIC_PART_EXISTS == STD_ON)
IPDUM_STATIC FUNC(void, IPDUM_CODE) IpduM_GetStaticJitData
(
  P2CONST(IpduM_TxPathWayType, AUTOMATIC, IPDUM_APPL_CONST) TxPathWay,
  P2VAR(IpduM_JitDataType, AUTOMATIC, IPDUM_APPL_DATA) JitData
)
{
  /* initial data for JIT update */
  JitData->TxPduId = IPDUM_RESERVED_PDUID;
  JitData->TxPartIndex = IPDUM_RESERVED_PDUID;

  if(TxPathWay->StaticPartIndex != IPDUM_RESERVED_PDUID)
  {
    const boolean isJitUpdate = (boolean)IPDUM_CFG_GET_TX_PART(TxPathWay->StaticPartIndex)->JitUpdate;

    /* get PDU-ID of static part for enabled JIT */
    if(isJitUpdate != (boolean)FALSE)
    {
      JitData->TxPduId = TxPathWay->StaticPartTrigTxHandleId;
      JitData->TxPartIndex = TxPathWay->StaticPartIndex;
    }
  }
}
#endif /* (IPDUM_STATIC_PART_EXISTS == STD_ON) */


IPDUM_STATIC FUNC(void, IPDUM_CODE) IpduM_GetDynamicJitData
(
  PduIdType TxConfPduId,
  P2CONST(IpduM_TxDataType, AUTOMATIC, IPDUM_APPL_DATA) TxData,
  P2CONST(IpduM_TxPathWayType, AUTOMATIC, IPDUM_APPL_CONST) TxPathWay,
  P2VAR(IpduM_JitDataType, AUTOMATIC, IPDUM_APPL_DATA) JitData
)
{
  PduIdType DynamicPartIndexLocal;
  TS_AtomicAssign16(DynamicPartIndexLocal, TxData[TxConfPduId].DynamicPartIndex);

  /* initial data for JIT update */
  JitData->TxPduId = IPDUM_RESERVED_PDUID;
  JitData->TxPartIndex = IPDUM_RESERVED_PDUID;

  /* did we get a dynamic PDU already? */
  if (DynamicPartIndexLocal != IPDUM_RESERVED_PDUID)
  {
    CONSTP2CONST(IpduM_TxPartType, AUTOMATIC, IPDUM_APPL_CONST) TxPartJitDyn =
        IPDUM_CFG_GET_TX_PART(DynamicPartIndexLocal);

    /* get PDU-ID of already received dynamic part for enabled JIT */
    if(TxPartJitDyn->JitUpdate)
    {
      TS_AtomicAssign16(JitData->TxPduId, TxData[TxConfPduId].PduRTriggerTxPduId);
      JitData->TxPartIndex = DynamicPartIndexLocal;
    }
  }
  else
  {
    CONSTP2CONST(IpduM_TxPartType, AUTOMATIC, IPDUM_APPL_CONST) TxPartJitDyn =
        IPDUM_CFG_GET_TX_PART(TxPathWay->InitialDynamicPartIndex);

    /* get PDU-ID of initial dynamic part for enabled JIT */
    if(TxPartJitDyn->JitUpdate)
    {
      JitData->TxPduId = TxPathWay->InitialDynamicPartTrigTxHandleId;
      JitData->TxPartIndex = TxPathWay->InitialDynamicPartIndex;
    }
  }
}
#endif /* (IPDUM_ENABLE_JIT_UPDATE == STD_ON) */


IPDUM_STATIC FUNC(void, IPDUM_CODE) IpduM_HandleRxPathWay
(
  PduIdType RxPduId,
  P2VAR(PduInfoType, AUTOMATIC, IPDUM_APPL_DATA) PduInfoPtr
)
{
  uint16 i;
  IpduM_SelectorType Selector;
#if (IPDUM_ZERO_COPY == STD_OFF)
  uint8 Buffer[IPDUM_RECEIVE_STACK_SIZE];
  PduInfoType PduBufferInfo = {NULL_PTR, 0U};
#else
  PduInfoType LocalPduInfo;
  IpduM_BitfieldType Offset;
  IpduM_BitfieldType EndByte;
#endif
  P2CONST(IpduM_RxPathWayType, AUTOMATIC, IPDUM_APPL_CONST) RxPathWayRI;
  P2CONST(IpduM_RxPartType, AUTOMATIC, IPDUM_APPL_CONST) RxDynamicPart = NULL_PTR;

  /* Get RxPathWay container */
  RxPathWayRI = IPDUM_CFG_GET_RX_PATHWAY(RxPduId);

  /* Cast to uint8 is safe, max value is 253 + 2 */
  if(PduInfoPtr->SduLength >= (uint8)IPDUM_GET_MIN_SDU_LEN(RxPathWayRI->EndBit))
  {
    /* Extract selector */
    Selector = IPDUM_GET_SELECTOR(PduInfoPtr->SduDataPtr, RxPathWayRI->StartBit, RxPathWayRI->EndBit);

    /* Search for dynamic part */
    i = 0U;
    while(i < RxPathWayRI->DynamicPduArraySize)
    {
      IpduM_SelectorType SelectorValue = IPDUM_CFG_GET_RX_DYNAMIC_PART(RxPathWayRI, i)->SelectorValue;
      if (SelectorValue == Selector)
      {
        /* Found, set RxDynamicPart */
        RxDynamicPart = IPDUM_CFG_GET_RX_DYNAMIC_PART(RxPathWayRI, i);
        break;
      }
      i++;
    }

#if (IPDUM_ZERO_COPY == STD_ON)

    /* Static part exists? */
#if (IPDUM_STATIC_PART_EXISTS == STD_ON)
    {
      if (FALSE == IPDUM_NULL_PTR_CHECK(RxPathWayRI->StaticPart))
      {
        P2CONST(IpduM_RxPartType, AUTOMATIC, IPDUM_APPL_CONST) RxStaticPart = IPDUM_CFG_GET_RX_STATIC_PART(RxPathWayRI);
        /* Calculate offset */
        Offset = IPDUM_GET_BYTE_OFFSET(IPDUM_CFG_GET_RX_COPY_BITFIELD(RxStaticPart)->StartBit);
        EndByte = IPDUM_GET_BYTE_OFFSET(IPDUM_CFG_GET_RX_COPY_BITFIELD(RxStaticPart)->EndBit);

        /* Call rx indication for static part */
        LocalPduInfo.SduLength = (EndByte - Offset) + 1U;
        LocalPduInfo.SduDataPtr = &PduInfoPtr->SduDataPtr[Offset];
        PduR_IpduMRxIndication(RxStaticPart->OutgoingHandleId, &LocalPduInfo);
      }
    }
#endif

    /* Always ensure that the selector is valid */
    if ( NULL_PTR != RxDynamicPart )
    {
      /* Calculate offset */
      Offset = IPDUM_GET_BYTE_OFFSET(IPDUM_CFG_GET_RX_COPY_BITFIELD(RxDynamicPart)->StartBit);
      EndByte = IPDUM_GET_BYTE_OFFSET(IPDUM_CFG_GET_RX_COPY_BITFIELD(RxDynamicPart)->EndBit);

      /* Call rx indication for dynamic part */
      LocalPduInfo.SduLength = (EndByte - Offset) + 1U;
      LocalPduInfo.SduDataPtr = &PduInfoPtr->SduDataPtr[Offset];
      PduR_IpduMRxIndication(RxDynamicPart->OutgoingHandleId, &LocalPduInfo);
    }
#else /* IPDUM_ZERO_COPY == STD_ON) */
#if (IPDUM_STATIC_PART_EXISTS == STD_ON)
    {
      if (FALSE == IPDUM_NULL_PTR_CHECK(RxPathWayRI->StaticPart))
      {
        P2CONST(IpduM_RxPartType, AUTOMATIC, IPDUM_APPL_CONST) RxStaticPart = IPDUM_CFG_GET_RX_STATIC_PART(RxPathWayRI);
        P2CONST(IpduM_CopyBitFieldType, AUTOMATIC, IPDUM_APPL_CONST) CopyBitField = IPDUM_CFG_GET_RX_COPY_BITFIELD(RxStaticPart);

        PduBufferInfo.SduDataPtr = &Buffer[0];

        /* Assemble fragmented static part into temporary buffer */
        PduBufferInfo.SduLength = IpduM_BitCopy(&Buffer[0],
            PduInfoPtr->SduDataPtr,
            CopyBitField,
            RxStaticPart->CopyBitFieldArraySize);

        /* Call rx indication for static part */
        PduR_IpduMRxIndication(RxStaticPart->OutgoingHandleId, &PduBufferInfo);
      }
    }
#endif

    /* Always ensure that the selector is valid */
    if ( NULL_PTR != RxDynamicPart )
    {
      P2CONST(IpduM_CopyBitFieldType, AUTOMATIC, IPDUM_APPL_CONST) CopyBitField = IPDUM_CFG_GET_RX_COPY_BITFIELD(RxDynamicPart);

      PduBufferInfo.SduDataPtr = &Buffer[0];

      /* Assemble fragmented dynamic part into temporary buffer */
      PduBufferInfo.SduLength = IpduM_BitCopy(&Buffer[0],
          PduInfoPtr->SduDataPtr,
          CopyBitField,
          RxDynamicPart->CopyBitFieldArraySize);

      /* Call rx indication for dynamic part */
      PduR_IpduMRxIndication(RxDynamicPart->OutgoingHandleId, &PduBufferInfo);
    }
#endif
  }
#if (IPDUM_DEV_ERROR_DETECT == STD_ON)
  else
  {
    IPDUM_DET_REPORT_ERROR(IPDUM_SID_RX_INDICATION, IPDUM_E_PARAM);
  }
#endif
}

IPDUM_STATIC FUNC(Std_ReturnType, IPDUM_CODE) IpduM_HandleTxPathWay
(
  PduIdType TxPduId,
  P2CONST(PduInfoType, AUTOMATIC, AUTOMATIC) PduInfoPtr
)
{
  P2CONST(IpduM_TxPartType, AUTOMATIC, IPDUM_APPL_CONST) TxPartT;
  P2CONST(IpduM_TxPathWayType, AUTOMATIC, IPDUM_APPL_CONST) TxPathWayT;
  P2VAR(IpduM_TxDataType, AUTOMATIC, IPDUM_VAR_NOINIT) TxData;
  PduIdType PdumDynamicTxPduId = IPDUM_RESERVED_PDUID; /* local PDU-ID of dynamic part */
  PduIdType PduRTxConfirmationPduId = IPDUM_RESERVED_PDUID; /* TxConf PDU-ID of dynamic part */
#if (IPDUM_DYNAMIC_PART_QUEUE == STD_ON)
  uint16 DynPriority;
  boolean ImmediatelySend = FALSE;
#endif /* (IPDUM_DYNAMIC_PART_QUEUE == STD_ON) */
#if (IPDUM_ENABLE_JIT_UPDATE == STD_ON)
  PduIdType PduRTriggerTxPduId = IPDUM_RESERVED_PDUID; /* TriggerTx PDU-ID of dynamic part */
  IpduM_JitDataType JitData = {IPDUM_RESERVED_PDUID, IPDUM_RESERVED_PDUID}; /* JIT update data */
#endif

  PduInfoType PduTxInfo = { NULL_PTR, 0U };

  Std_ReturnType RetValue = E_NOT_OK;

  RetValue = E_OK;

  /* Get TxPartT */
  TxPartT = IPDUM_CFG_GET_TX_PART(TxPduId);

  /* Deviation MISRAC2012-1 */
  TxData = (P2VAR(IpduM_TxDataType, IPDUM_VAR, IPDUM_VAR))(&IpduM_GDataMemPtr[IPDUM_TX_DATA_OFFSET]);

  TxPathWayT = IPDUM_CFG_GET_TX_PATHWAY(TxPartT->TxConfirmationPduId);

  /* Ignore if the Size of the Path way is zero */
  if (TxPathWayT->Size == 0U)
  {
    RetValue = E_OK;
  }
  else
  {
#if (IPDUM_DEFENSIVE_PROGRAMMING_ENABLED == STD_ON)
    /* CHECK: NOPARSE */
    if (TxPathWayT->TriggerMode > (uint8)IPDUM_TRIGGER_MODE_MAX_VAL)
    {
      /* unexpected error condition - should never be reached */
      IPDUM_UNREACHABLE_CODE_ASSERT(IPDUM_SID_TRANSMIT);
    }
    else
      /* CHECK: PARSE */
#endif /* (IPDUM_DEFENSIVE_PROGRAMMING_ENABLED == STD_ON) */
    {
      boolean TxFlag = FALSE;

      SchM_Enter_IpduM_SCHM_IPDUM_EXCLUSIVE_AREA_0();

      /* Check if a transmission is ongoing */
      if (0 == TxData[TxPartT->TxConfirmationPduId].ConfirmationTimeoutCounter)
      {
        /* No request pending */

#if (IPDUM_DYNAMIC_PART_QUEUE == STD_ON)
        RetValue = IpduM_HandleQueueFilling(TxPduId,
            PduInfoPtr,
            TxPathWayT,
            TxPartT,
            &PduTxInfo,
            &PdumDynamicTxPduId,
            &PduRTxConfirmationPduId,
            &ImmediatelySend
        );
#else /* (IPDUM_DYNAMIC_PART_QUEUE == STD_ON) */
#if (IPDUM_ZERO_COPY == STD_OFF)
        /* dynamic part ? */
        if (TxPduId >= IpduM_ConfigPtr->TxDynamicPartOffset)
#endif /* (IPDUM_ZERO_COPY == STD_OFF) */
          /* dynamic part (when IPDUM_ZERO_COPY == STD_ON the must not be a static part) */
        {
          /* Store PDU IDs for dynamic part */
          PdumDynamicTxPduId = TxPduId;
          PduRTxConfirmationPduId = TxPartT->PduRTxConfirmationPduId;
#if (IPDUM_ENABLE_JIT_UPDATE == STD_ON)
          PduRTriggerTxPduId = TxPartT->PduRTriggerTxPduId;
#endif /* (IPDUM_ENABLE_JIT_UPDATE == STD_ON) */
        }
#endif /* (IPDUM_DYNAMIC_PART_QUEUE == STD_ON) */

#if (IPDUM_ZERO_COPY == STD_OFF)
        /* Get pointer to static buffer */
        PduTxInfo.SduDataPtr = &IpduM_GDataMemPtr[TxPathWayT->BufferOffset];

        /* Assemble PDU */
        PduTxInfo.SduLength = IpduM_BitCopy(PduTxInfo.SduDataPtr,
            PduInfoPtr->SduDataPtr,
            IPDUM_CFG_GET_TX_COPY_BITFIELD(TxPartT),
            TxPartT->CopyBitFieldArraySize);
#endif /* (IPDUM_ZERO_COPY == STD_OFF) */

        /* In case we have updated the dynamic part, store the PDU-IDs for the dynamic part */
        if (PdumDynamicTxPduId != IPDUM_RESERVED_PDUID)
        {
          TxData[TxPartT->TxConfirmationPduId].PduRTxConfirmationPduId = PduRTxConfirmationPduId;
#if (IPDUM_ENABLE_JIT_UPDATE == STD_ON)
          TxData[TxPartT->TxConfirmationPduId].PduRTriggerTxPduId = PduRTriggerTxPduId;
          TxData[TxPartT->TxConfirmationPduId].DynamicPartIndex = TxPduId;
#endif /* (IPDUM_ENABLE_JIT_UPDATE == STD_ON) */
        }

#if (IPDUM_DYNAMIC_PART_QUEUE == STD_ON)
        if (TRUE == ImmediatelySend)
#else /* (IPDUM_DYNAMIC_PART_QUEUE == STD_ON) */
          /* Trigger condition fulfilled? */
          if ( ((TxPduId < IpduM_ConfigPtr->TxDynamicPartOffset) &&
              ((TxPathWayT->TriggerMode & IPDUM_TRIGGER_STATIC) == IPDUM_TRIGGER_STATIC) ) ||
              ((TxPduId >= IpduM_ConfigPtr->TxDynamicPartOffset) &&
                  ((TxPathWayT->TriggerMode & IPDUM_TRIGGER_DYNAMIC) == IPDUM_TRIGGER_DYNAMIC) )
          )
#endif /* (IPDUM_DYNAMIC_PART_QUEUE == STD_ON) */
          {
#if (IPDUM_ZERO_COPY == STD_ON)
            /* In case of zero copy the buffer passed as parameter (PduInfoPtr)
             * is used for further transmission. This is done by setting the SduDataPtr
             * of the outgoing PDU to the byte position containing the start bit
             * of the TX segment within the buffer provided by PduInfoPtr function parameter.
             * This requires to adapt the SduLength to the byte size of the TX segment
             * to avoid a bound violation further on when PduR_IpduMTransmit is called.
             * The generator ensures that there is only one single dynamic TX segment
             * configured. */

            /* Calculate byte offsets of the dynamic TX segment */
            const IpduM_BitfieldType StartByteOffset = IPDUM_GET_BYTE_OFFSET(IPDUM_CFG_GET_TX_COPY_BITFIELD(TxPartT)->StartBit);
            const IpduM_BitfieldType EndByteOffset = IPDUM_GET_BYTE_OFFSET(IPDUM_CFG_GET_TX_COPY_BITFIELD(TxPartT)->EndBit);

            /* Calculate required SduLength in byte */
            PduTxInfo.SduLength = (EndByteOffset - StartByteOffset) + 1U;
#else /* (IPDUM_ZERO_COPY == STD_ON) */

            /* If zero copy is deactivated get the SduLength form the configured Tx pathway */
            PduTxInfo.SduLength = IPDUM_GET_BYTE_SIZE(TxPathWayT->Size);

#endif /* (IPDUM_ZERO_COPY == STD_ON) */

            /* set timeout counter to special value for ongoing calls to
             * PduR_IpduMTransmit() - will be set to correct timeout value after
             * PduR_IpduMTransmit() has returned */
            TxData[TxPartT->TxConfirmationPduId].ConfirmationTimeoutCounter = IPDUM_TRANSMIT_ONGOING;

            /* Set PDU Info */
#if (IPDUM_ZERO_COPY == STD_OFF)

            /* Automatically set selector value */
#if (IPDUM_AUTOMATIC_SELECTOR == STD_ON)
            /* do we have an updated dynamic part? */
            if (PdumDynamicTxPduId != IPDUM_RESERVED_PDUID)
            {
              CONSTP2CONST(IpduM_TxPartType, AUTOMATIC, IPDUM_APPL_CONST) TxDynamicPart = IPDUM_CFG_GET_TX_PART(PdumDynamicTxPduId);

              /* set the selector value based on the TxPart configuration (which is derived based on the TxPduId */
              IPDUM_SET_SELECTOR(PduTxInfo.SduDataPtr,
                  TxDynamicPart->SelectorValue,
                  TxPathWayT->StartBit,
                  TxPathWayT->EndBit);
            }
#endif /* (IPDUM_AUTOMATIC_SELECTOR == STD_ON) */
#else /* (IPDUM_ZERO_COPY == STD_OFF) */

            /* zero copy - just adjust the data pointer according to the start bit
             * (in the zero copy case only a single CopyBitField is allowed) */
            PduTxInfo.SduDataPtr = &PduInfoPtr->SduDataPtr[StartByteOffset];
#endif /* (IPDUM_ZERO_COPY == STD_OFF) */

#if (IPDUM_ENABLE_JIT_UPDATE == STD_ON)
            /* get data for JIT update */
            IpduM_GetJitDataTransmit(TxPduId, TxPartT, TxData, TxPathWayT, &JitData);
#endif /* (IPDUM_ENABLE_JIT_UPDATE == STD_ON) */

            TxFlag = TRUE;
          }
          else
          {
            /* return E_OK */
          }
      }

      else /* Transmission ongoing */
      {
#if (IPDUM_DYNAMIC_PART_QUEUE == STD_ON)
        if (TxPduId < IpduM_ConfigPtr->TxDynamicPartOffset)
        {
          /* Static part, reject */
          RetValue = E_NOT_OK;
        }
        else
        {
          /* Set priority */
          DynPriority = TxPartT->DynamicPriority;

          /* Queue dynamic part */
          if ((TxPathWayT->TriggerMode & IPDUM_TRIGGER_DYNAMIC) != IPDUM_TRIGGER_DYNAMIC)
          {
            /* Trigger condition not fulfilled, mark as not to send */
            DynPriority |= IPDUM_PRIO_NOT_READY_TO_SEND;
          }

          RetValue = IpduM_InsertQueue(TxPduId,
              TxPartT->PduRTxConfirmationPduId,
              PduInfoPtr,
              DynPriority);
        }
#else /* (IPDUM_DYNAMIC_PART_QUEUE == STD_ON) */
        RetValue = E_NOT_OK;
#endif /* (IPDUM_DYNAMIC_PART_QUEUE == STD_ON) */
      }

      SchM_Exit_IpduM_SCHM_IPDUM_EXCLUSIVE_AREA_0();

#if (IPDUM_ENABLE_JIT_UPDATE == STD_ON)
      /* JIT update of multiplexed I-PDU if trigger condition fulfilled */
      if (TxFlag == TRUE)
      {
        Std_ReturnType RetValUpdatePdu;

        RetValUpdatePdu =
            IpduM_UpdatePdu(JitData.TxPduId, JitData.TxPartIndex, TxPathWayT, FALSE);

        /* No Transmit to be called if Up_TriggerTransmit is called erroneous */
        if (RetValUpdatePdu != E_OK)
        {
          TxFlag = FALSE;
        }
      }
#endif /* (IPDUM_ENABLE_JIT_UPDATE == STD_ON) */

      /* Check whether the frame is to be transmitted */
      if (TxFlag == TRUE)
      {
        Std_ReturnType TransmitRetVal = E_NOT_OK;

        /* Transmit frame */
        TransmitRetVal = PduR_IpduMTransmit(TxPartT->TxOutgoingPduId, &PduTxInfo);

        SchM_Enter_IpduM_SCHM_IPDUM_EXCLUSIVE_AREA_0();

        if (E_NOT_OK == TransmitRetVal)
        {
          /* Reset confirmation timer so that a new frame can be transmitted */
          TxData[TxPartT->TxConfirmationPduId].ConfirmationTimeoutCounter = 0U;

          /* Transmit failed, return with error */
          RetValue = E_NOT_OK;
        }
        else
        {
          switch (TxData[TxPartT->TxConfirmationPduId].ConfirmationTimeoutCounter)
          {
          case IPDUM_TRANSMIT_ONGOING:
            /* Start timer for timeout monitoring */
            TxData[TxPartT->TxConfirmationPduId].ConfirmationTimeoutCounter = TxPathWayT->ConfirmationTimeout;
            break;

          case IPDUM_TRANSMIT_ONGOING_CONFIRMED:
            /* Do not start the time out counting when the transmit of the PDU
             * was confirmed before PduR_IpduMTransmit() has completely finished */
            TxData[TxPartT->TxConfirmationPduId].ConfirmationTimeoutCounter = 0U;
            break;

            /* all possible cases have been explicitly covered in 'case's above, the 'default'
             * cannot be reached */

            /* CHECK: NOPARSE */
          default:
            IPDUM_UNREACHABLE_CODE_ASSERT(IPDUM_SID_TRANSMIT);
            break;
            /* CHECK: PARSE */
          }
        }
        SchM_Exit_IpduM_SCHM_IPDUM_EXCLUSIVE_AREA_0() ;
      }
    }
    /* TxPathWayT->TriggerMode > IPDUM_TRIGGER_MODE_MAX_VAL */
  }

  return RetValue;
}

#if (IPDUM_CONTAINER_PDU_HANDLING_ENABLE == STD_ON)

IPDUM_STATIC FUNC(void, IPDUM_CODE) IpduM_CallCntrSendFunction
(
  PduIdType index
)
{
  P2CONST(IpduM_ContainerTxPduType, AUTOMATIC, IPDUM_APPL_CONST) cntrPtr = IPDUM_CFG_GET_CNTR_TX(index);
  /* Deviation MISRAC2012-1 */
  P2VAR(IpduM_CntrTxDataType, AUTOMATIC, AUTOMATIC) cntrRamPtr = IPDUM_GET_CNTR_TXDATA(index);
  uint8 lTxMtx = 0U;

#if (IPDUM_CONTAINER_QUEUING_TX == STD_ON)
  boolean isCntrQEmpty;
#endif

  SchM_Enter_IpduM_SCHM_IPDUM_EXCLUSIVE_AREA_0();

#if (IPDUM_CONTAINER_QUEUING_TX == STD_ON)
  isCntrQEmpty = IpduM_IsCntrQEmpty(index);
#endif

  lTxMtx = cntrRamPtr->TxMtx;
  cntrRamPtr->TxMtx = 1U;

  SchM_Exit_IpduM_SCHM_IPDUM_EXCLUSIVE_AREA_0();

  if(lTxMtx == 0U)
  {
    if((boolean) TRUE == IPDUM_IS_TXMODE_DIRECT(cntrPtr->CfgFlags))
    {
      if((boolean) TRUE == IPDUM_IS_QUEUED(cntrPtr->CfgFlags))
      {
#if (IPDUM_CONTAINER_QUEUING_TX == STD_ON)
        if(isCntrQEmpty)
#endif
        {
          IpduM_SendCurrCntr(index);
        }
#if (IPDUM_CONTAINER_QUEUING_TX == STD_ON)
        else
        {
          IpduM_DequeueCntr(index);
        }
#endif
      }
      else
      {
        IpduM_SendCurrCntr(index);
      }
    }
    else
    {
      IpduM_CntrSizeAnnounce(index);
    }

    TS_AtomicAssign8(cntrRamPtr->TxMtx, 0U);
  }
}

#if(IPDUM_DEDICATED_IPDU_PROCESSING_SUPPORT == STD_OFF)
IPDUM_STATIC FUNC(void, IPDUM_CODE) IpduM_CntrHandleTimers(void)
#else
IPDUM_STATIC FUNC(void, IPDUM_CODE) IpduM_CntrHandleTimers(IpduM_MainFuncIdxType idx)
#endif
{
  if(FALSE == IPDUM_NULL_PTR_CHECK(IpduM_ConfigPtr->ContainerTxPdu))
  {
    /* TxSendTimeout handling */
    uint16 index;
#if(IPDUM_DEDICATED_IPDU_PROCESSING_SUPPORT == STD_ON)
    IpduM_MainFuncIdxType i;
#endif
    /* Deviation MISRAC2012-1 */
    P2VAR(IpduM_CntrTxDataType, AUTOMATIC, AUTOMATIC) cntrTxDataPtr = IPDUM_GET_CNTR_TXDATA(0U);
#if(IPDUM_CONTAINER_QUEUING_TX == STD_ON)
    CONSTP2CONST(IpduM_ContainerTxPduType, AUTOMATIC, IPDUM_APPL_CONST) cntrs = IPDUM_CFG_GET_CNTR_TX(0);
#endif

#if(IPDUM_DEDICATED_IPDU_PROCESSING_SUPPORT == STD_OFF)
    for(index = (IpduM_ContainerNumType)0U; index < IpduM_ConfigPtr->TxContainerPduNum; index++)
    {
      boolean internalTransmitFlag = (boolean)FALSE;
#if(IPDUM_CONTAINER_QUEUING_TX == STD_ON)
      boolean hasElemQueued = (boolean) FALSE;
#endif

#else
    for(i=1U; i<=IPDUM_GET_TX_MF_IDX(idx); i++)
    {
      boolean internalTransmitFlag = (boolean)FALSE;

#if((IPDUM_CONTAINER_QUEUING_TX == STD_ON))
      boolean hasElemQueued = (boolean) FALSE;
#endif

      index = IPDUM_GET_TX_MF_IDX(idx + i);
      if(index < IPDUM_TX_PATHWAY_LEN)
      {
        /* Jump over pathways */
        continue;
      }
      /* This is needed at the moment in order to differentiate between pathways and containers in MF TX */
      index -= IPDUM_TX_PATHWAY_LEN;
#endif


      SchM_Enter_IpduM_SCHM_IPDUM_EXCLUSIVE_AREA_0();

#if(IPDUM_CONTAINER_QUEUING_TX == STD_ON)
      if((boolean)TRUE == IPDUM_IS_QUEUED(cntrs[index].CfgFlags))
      {
        if((boolean)FALSE == IpduM_IsCntrQEmpty(index))
        {
          hasElemQueued = (boolean) TRUE;
        }
      }
#endif

      if(0U < cntrTxDataPtr[index].ConfirmTimeout)
      {
        cntrTxDataPtr[index].ConfirmTimeout--;
      }

      if(0U < cntrTxDataPtr[index].SendTimeout)
      {
        cntrTxDataPtr[index].SendTimeout--;

        if(0U == cntrTxDataPtr[index].SendTimeout)
        {
#if(IPDUM_CONTAINER_QUEUING_TX == STD_ON)
          if((0U != cntrTxDataPtr[index].ConfirmTimeout) || ((boolean)TRUE == hasElemQueued))
#else
          if((0U != cntrTxDataPtr[index].ConfirmTimeout))
#endif
          {
            cntrTxDataPtr[index].SendTimeout = 1U;
          }
          else
          {
            internalTransmitFlag = (boolean)TRUE;
          }
        }

      }

      if(0U == cntrTxDataPtr[index].ConfirmTimeout)
      {
        if(
            ((boolean)TRUE == cntrTxDataPtr[index].ConfAwait)
        )
        {
          cntrTxDataPtr[index].ConfAwait = (boolean) FALSE;
          internalTransmitFlag = (boolean)TRUE;
        }

#if (IPDUM_CONTAINER_QUEUING_TX == STD_ON)
          if((boolean)TRUE == hasElemQueued)
          {
            if((boolean)TRUE == IPDUM_IS_TXMODE_DIRECT(cntrs[index].CfgFlags))
            {
              internalTransmitFlag = (boolean)TRUE;
            }
            else
            {
              if(cntrTxDataPtr[index].QMFSizeAnnounceFlag)
              {
                internalTransmitFlag = (boolean)TRUE;
              }
            }
          }
#endif
      }

      SchM_Exit_IpduM_SCHM_IPDUM_EXCLUSIVE_AREA_0();

      if((boolean)TRUE == internalTransmitFlag)
      {
        IpduM_CallCntrSendFunction(index);
      }
    }

  }
}

#if (IPDUM_ZERO_COPY == STD_OFF)
IPDUM_STATIC FUNC(Std_ReturnType, IPDUM_CODE) IpduM_CntrTriggerTransmit
(
  PduIdType TxPduId,
  P2VAR(PduInfoType, AUTOMATIC, AUTOMATIC) PduInfoPtr
)
{
  uint16 ParentContainerIndex = (uint16)TxPduId - (uint16)IpduM_ConfigPtr->TxPathWayLen;
  P2CONST(IpduM_ContainerTxPduType, AUTOMATIC, IPDUM_APPL_CONST) cntrPtr = IPDUM_CFG_GET_CNTR_TX(ParentContainerIndex);
  Std_ReturnType RetValue = (Std_ReturnType)E_NOT_OK;


  if(IPDUM_IS_TXMODE_DIRECT(cntrPtr->CfgFlags) == (boolean)FALSE)
  {
    /* Deviation MISRAC2012-1 */
    P2VAR(IpduM_CntrTxDataType, AUTOMATIC, AUTOMATIC) cntrRamPtr = IPDUM_GET_CNTR_TXDATA(ParentContainerIndex);
    /* Deviation MISRAC2012-1 */
    P2VAR(uint16, AUTOMATIC, AUTOMATIC) containerTxList = IPDUM_GET_TX_PDULIST(ParentContainerIndex);

#if (IPDUM_CONTAINER_QUEUING_TX == STD_ON)
    boolean isContainerQueued = (boolean) IPDUM_IS_QUEUED(cntrPtr->CfgFlags);
#if(IPDUM_CNTND_COLLECT_QUEUED_TX == STD_ON)
    P2VAR(IpduM_ContainerQueueType, AUTOMATIC, IPDUM_APPL_DATA) qPtr = IPDUM_GET_TX_QUEUE(ParentContainerIndex);
#endif
#endif

#if(IPDUM_CNTND_COLLECT_QUEUED_TX == STD_ON)
    boolean isLastIsBest = (boolean) IPDUM_IS_CNTR_LAST_IS_BEST(cntrPtr->CfgFlags);
#endif

#if (IPDUM_CONTAINER_QUEUING_TX == STD_ON)
    BufReq_ReturnType ret = BUFREQ_E_BUSY;

    if(isContainerQueued)
    {
#if(IPDUM_CNTND_COLLECT_QUEUED_TX == STD_ON)
      if(TRUE != isLastIsBest)
      {
        SchM_Enter_IpduM_SCHM_IPDUM_EXCLUSIVE_AREA_0();

        /* Deviation MISRAC2012-1 */
        ret = IPDUM_CNTRQ(POP, TX, ParentContainerIndex, NULL_PTR, PduInfoPtr->SduDataPtr, &PduInfoPtr->SduLength);

        SchM_Exit_IpduM_SCHM_IPDUM_EXCLUSIVE_AREA_0();
      }
      else
#endif /* IPDUM_CNTND_COLLECT_QUEUED_TX == STD_ON */
      {
        boolean isQEmpty;
        SchM_Enter_IpduM_SCHM_IPDUM_EXCLUSIVE_AREA_0();
        isQEmpty = IpduM_IsCntrQEmpty(ParentContainerIndex);
        SchM_Exit_IpduM_SCHM_IPDUM_EXCLUSIVE_AREA_0();

        if(!isQEmpty)
        {
          CONSTP2VAR(uint16, AUTOMATIC, AUTOMATIC) confList = IPDUM_GET_TX_CONFLIST(ParentContainerIndex);
          IpduM_PackDataTTLBtoBuff(cntrPtr,
                                   &confList[qPtr->QPopIdx * cntrPtr->chunkSize],
                                   PduInfoPtr
                                   );

          SchM_Enter_IpduM_SCHM_IPDUM_EXCLUSIVE_AREA_0();

          qPtr->QLBTxConf = qPtr->QPopIdx;
          qPtr->QPopIdx = (qPtr->QPopIdx + 1U) % cntrPtr->IpduMContainerQueueSize;
          qPtr->QFull = 0U;

          SchM_Exit_IpduM_SCHM_IPDUM_EXCLUSIVE_AREA_0();

          if(0U < PduInfoPtr->SduLength)
          {
            ret = BUFREQ_OK;
          }
        }
      } /* end !last is best */
    } /* end is cntr queued */
    else
#endif /* IPDUM_CONTAINER_QUEUING_TX == STD_ON */
    {
#if (IPDUM_CONTAINER_QUEUING_TX == STD_ON)
      /* reusing the variable, because it can't be initialised where declared */
      ret = BUFREQ_E_NOT_OK;
#endif /* IPDUM_CONTAINER_QUEUING_TX == STD_ON */
    }


#if (IPDUM_CONTAINER_QUEUING_TX == STD_ON)
    if(BUFREQ_OK == ret)
    {
      RetValue = (Std_ReturnType)E_OK;

      SchM_Enter_IpduM_SCHM_IPDUM_EXCLUSIVE_AREA_0();

      cntrRamPtr->ConfirmTimeout = cntrPtr->IpduMContainerTxConfirmationTimeout;

      if(FALSE == IpduM_IsCntrQEmpty(ParentContainerIndex))
      {
        cntrRamPtr->ConfAwait = TRUE;
      }

      SchM_Exit_IpduM_SCHM_IPDUM_EXCLUSIVE_AREA_0();
    }
    else
#endif /* IPDUM_CONTAINER_QUEUING_TX == STD_ON */
    {
#if (IPDUM_CNTND_COLLECT_QUEUED_TX == STD_ON)
      if(TRUE != isLastIsBest)
      {
        SchM_Enter_IpduM_SCHM_IPDUM_EXCLUSIVE_AREA_0();

        TS_AtomicAssignGeneric(PduInfoPtr->SduLength, (PduLengthType)cntrRamPtr->ListSize);
        TS_MemCpy(PduInfoPtr->SduDataPtr, IPDUM_GET_TX_CURRDATABUFF(ParentContainerIndex), PduInfoPtr->SduLength);

        SchM_Exit_IpduM_SCHM_IPDUM_EXCLUSIVE_AREA_0();
      }
      else
#endif /* IPDUM_CNTND_COLLECT_QUEUED_TX == STD_ON */
      {
        IpduM_PackDataTTLBtoBuff(cntrPtr,
                                 containerTxList,
                                 PduInfoPtr
                                );
      }

      SchM_Enter_IpduM_SCHM_IPDUM_EXCLUSIVE_AREA_0();

      /* update via PduR Trigger Transmit before queuing */
      cntrRamPtr->AnnounceSize = (boolean) FALSE;

      if(0U != PduInfoPtr->SduLength)
      {
        /* Deviation MISRAC2012-1 */
        P2VAR(uint16, AUTOMATIC, AUTOMATIC) confList = IPDUM_GET_TX_CONFLIST(ParentContainerIndex);
#if (IPDUM_CONTAINER_QUEUING_TX == STD_OFF)
        const uint16 txconf_offset = 0U;
#else
        /* Deviation MISRAC2012-1 */
        const uint16 txconf_offset = ((TRUE == IPDUM_IS_QUEUED(cntrPtr->CfgFlags)) ? (uint16) qPtr->QPushIdx : 0U) * (uint16) cntrPtr->chunkSize;
        qPtr->QLBTxConf = qPtr->QPushIdx;
#endif

        /* store Contained indexes for later confirmation */
        TS_MemCpy(&confList[txconf_offset],
                  &containerTxList[0U],
                  sizeof(containerTxList[0U]) * ((uint32)containerTxList[0U] + 1U)
        );

        cntrRamPtr->ConfirmTimeout = cntrPtr->IpduMContainerTxConfirmationTimeout;

        RetValue = (Std_ReturnType)E_OK;
      }
      else
      {
        RetValue = (Std_ReturnType)E_NOT_OK;
      }

      containerTxList[0U] = 0U;
      cntrRamPtr->ListSize = 0U;

      cntrRamPtr->SendTimeout = 0U;

      SchM_Exit_IpduM_SCHM_IPDUM_EXCLUSIVE_AREA_0();
    }
  }

  return RetValue;
}

IPDUM_STATIC FUNC(void, IPDUM_CODE) IpduM_PackDataTTLBtoBuff
(
  P2CONST(IpduM_ContainerTxPduType, AUTOMATIC, IPDUM_APPL_CONST) cntrPtr,
  P2VAR(uint16, AUTOMATIC, AUTOMATIC) containedPduList,
  P2VAR(PduInfoType, AUTOMATIC, AUTOMATIC) pduInfoPtr
)
{
  P2CONST(IpduM_ContainedTxPduType, AUTOMATIC, AUTOMATIC) containedPtr;
  CONSTP2VAR(uint8, AUTOMATIC, AUTOMATIC) origDataPTr = pduInfoPtr->SduDataPtr;
  PduLengthType finalLength;
  uint16 cntdIdx;
  Std_ReturnType ttRet;

#if (IPDUM_STATIC_CONTAINER_PDU_HANDLING_ENABLE == STD_ON)
  if(IPDUM_HEADERTYPE_NONE ==  cntrPtr->HeaderSize)
  {
    TS_MemSet(pduInfoPtr->SduDataPtr, cntrPtr->IpduMUnusedAreasDefault, cntrPtr->PduLength);
    finalLength = cntrPtr->StaticSduLength;
    for(cntdIdx = 1U; cntdIdx <= containedPduList[0U]; cntdIdx++)
    {
      containedPtr = IPDUM_CFG_GET_CNTD_TX(containedPduList[cntdIdx]);

      /* Deviation MISRAC2012-4 */
      pduInfoPtr->SduDataPtr = origDataPTr + containedPtr->IpduMContainedPduOffset;
      pduInfoPtr->SduLength = containedPtr->PduLength;

      ttRet = PduR_IpduMTriggerTransmit(containedPtr->IpduMContainedTxPduHandleId, pduInfoPtr);

      if(E_OK == ttRet)
      {
        if(cntrPtr->NumCntdStatic == cntdIdx)
        {
          finalLength = containedPtr->IpduMContainedPduOffset + pduInfoPtr->SduLength;
        }

        if(IPDUM_CNTRTX_HAS_UPDATE_BITS(cntrPtr->CfgFlags))
        {
          IpduM_AtomicSetBit(origDataPTr, containedPtr->IpduMUpdateBitBytePosition, containedPtr->IpduMUpdateBitMask);
        }
      }
    } /* end for */
  }
  else
#endif /* IPDUM_STATIC_CONTAINER_PDU_HANDLING_ENABLE == STD_ON */
  {
    /* Value set for the very first iteration */
    pduInfoPtr->SduLength = 0U;
    for(cntdIdx = 1U; cntdIdx <= containedPduList[0U]; cntdIdx++)
    {
      const uint8 headerSize = cntrPtr->HeaderSize;
      containedPtr = IPDUM_CFG_GET_CNTD_TX(containedPduList[cntdIdx]);

      /* Deviation MISRAC2012-4 */
      pduInfoPtr->SduDataPtr += headerSize;
      pduInfoPtr->SduLength = containedPtr->PduLength;
      ttRet = PduR_IpduMTriggerTransmit(containedPtr->IpduMContainedTxPduHandleId, pduInfoPtr);

      /* Deviation MISRAC2012-4 */
      pduInfoPtr->SduDataPtr -= headerSize;

      if(E_OK == ttRet)
      {
        const uint32 headerId = containedPtr->IpduMContainedPduHeaderId;
        if(IPDUM_HEADERTYPE_SHORT == headerSize)
        {
          TS_MemCpy(pduInfoPtr->SduDataPtr, ((const uint8*)&headerId + IPDUM_HDR_ID_OFFST), IPDUM_SHORT_HDR_DLC_OFFST);
          pduInfoPtr->SduDataPtr[IPDUM_SHORT_HDR_DLC_OFFST] = (uint8)pduInfoPtr->SduLength;
        }
        else
        {
          const uint32 len = IPDUM_SWAPU32_IF_MUST(pduInfoPtr->SduLength);

          TS_MemCpy(pduInfoPtr->SduDataPtr, &headerId, 4U);
          /* Deviation MISRAC2012-4 */
          TS_MemCpy(pduInfoPtr->SduDataPtr + 4U, &len, 4U);
        }
        /* Deviation MISRAC2012-4 */
        pduInfoPtr->SduDataPtr += headerSize + pduInfoPtr->SduLength;
      } /* ttRet == E_OK */
    } /* end for */
    finalLength = pduInfoPtr->SduDataPtr - origDataPTr;
  } /* end dynamic header */
  pduInfoPtr->SduDataPtr = origDataPTr;
  pduInfoPtr->SduLength = finalLength;
}
#endif

IPDUM_STATIC FUNC(Std_ReturnType, IPDUM_CODE) IpduM_HandleTxContainerPdu
(
  PduIdType TxPduId
#if(IPDUM_CNTND_COLLECT_QUEUED_TX == STD_ON)
  , P2CONST(PduInfoType, AUTOMATIC, IPDUM_APPL_DATA) PduInfoPtr
#endif
)
{
  const uint16 ContainedPduIndex = (uint16)TxPduId - (uint16)IpduM_ConfigPtr->TxPartLen;
  const uint16 ParentContainerIndex = IPDUM_CFG_GET_CNTD_TX(ContainedPduIndex)->IpduMContainerTxIndex;
  P2CONST(IpduM_ContainerTxPduType, AUTOMATIC, IPDUM_APPL_CONST) cntrPtr = IPDUM_CFG_GET_CNTR_TX(ParentContainerIndex);
#if(IPDUM_CONTAINER_QUEUING_TX == STD_ON)
  const boolean isContainerQueued = IPDUM_IS_QUEUED(cntrPtr->CfgFlags);
#endif
  Std_ReturnType RetValue = E_NOT_OK;
  /* Deviation MISRAC2012-1 */
  P2VAR(IpduM_CntrTxDataType, AUTOMATIC, AUTOMATIC) cntrRamPtr = IPDUM_GET_CNTR_TXDATA(ParentContainerIndex);
  uint8 lTxMtx = 0U;

#if(IPDUM_CNTND_COLLECT_QUEUED_TX == STD_ON)
  const boolean isLastIsBest = IPDUM_IS_CNTR_LAST_IS_BEST(cntrPtr->CfgFlags);
#endif

  SchM_Enter_IpduM_SCHM_IPDUM_EXCLUSIVE_AREA_0();

  lTxMtx = cntrRamPtr->TxMtx;
  cntrRamPtr->TxMtx = 1U;

  SchM_Exit_IpduM_SCHM_IPDUM_EXCLUSIVE_AREA_0();

  if(lTxMtx == 0U)
  {
    if((boolean) TRUE == IPDUM_IS_TXMODE_DIRECT(cntrPtr->CfgFlags))
    {
#if(IPDUM_CNTND_COLLECT_QUEUED_TX == STD_ON)
      if(isLastIsBest)
#endif
      {
#if(IPDUM_CONTAINER_QUEUING_TX == STD_ON)
        if(isContainerQueued)
        {
          RetValue = IpduM_DT_LastIsBest_WithCntrQueuing(TxPduId);
        }
        else
#endif
        {
          RetValue = IpduM_DT_LastIsBest_NoCntrQueuing(TxPduId);
        }
      }
#if(IPDUM_CNTND_COLLECT_QUEUED_TX == STD_ON)
      else
      {
#if(IPDUM_CONTAINER_QUEUING_TX == STD_ON)
        if(isContainerQueued)
        {
          RetValue = IpduM_DT_Queued_WithCntrQueuing(TxPduId, PduInfoPtr);
        }
        else
#endif
        {
          RetValue = IpduM_DT_Queued_NoCntrQueuing(TxPduId, PduInfoPtr);
        }
      }
#endif
    }
    else
    {
#if(IPDUM_CNTND_COLLECT_QUEUED_TX == STD_ON)
      if(isLastIsBest)
#endif
      {
#if(IPDUM_CONTAINER_QUEUING_TX == STD_ON)
        if(isContainerQueued)
        {
          RetValue = IpduM_TT_LastIsBest_WithCntrQueuing(TxPduId);
        }
        else
#endif
        {
          RetValue = IpduM_TT_LastIsBest_NoCntrQueuing(TxPduId);
        }
      }
#if(IPDUM_CNTND_COLLECT_QUEUED_TX == STD_ON)
      else
      {
#if(IPDUM_CONTAINER_QUEUING_TX == STD_ON)
        if(isContainerQueued)
        {
          RetValue = IpduM_TT_Queued_WithCntrQueuing(TxPduId, PduInfoPtr);
        }
        else
#endif
        {
          RetValue = IpduM_TT_Queued_NoCntrQueuing(TxPduId, PduInfoPtr);
        }
      }
#endif
    }

    TS_AtomicAssign8(cntrRamPtr->TxMtx, 0U);
  }

  return RetValue;
}

IPDUM_STATIC FUNC(sint32, IPDUM_CODE) IpduM_RxCntd_BinSearch
(
  P2CONST(IpduM_ContainedRxPduType, AUTOMATIC, IPDUM_APPL_CONST) ContainedPduHeaderIds,
  sint32 left,
  sint32 right,
  uint32 PduHeaderId
)
{
  sint32 position = IPDUM_IDX_NOT_FOUND;
  while (left <= right)
  {
    sint32 middle = left + ((right - left)/2);

    /* Check if PduHeaderId is present in the middle */
    if (ContainedPduHeaderIds[middle].ContainedPduHeaderId == IPDUM_SWAPU32_IF_MUST(PduHeaderId))
    {
      position = middle;
      break;
    }

    if (ContainedPduHeaderIds[middle].ContainedPduHeaderId < IPDUM_SWAPU32_IF_MUST(PduHeaderId))
    {
      /* If PduHeaderId greater, ignore left half */
      left = middle + 1;
    }
    else
    {
      /* If PduHeaderId is smaller, ignore right half */
      right = middle - 1;
    }
  }

  /* Return position */
  return position;
}

IPDUM_STATIC FUNC(void, IPDUM_CODE) IpduM_HandleDynamicRxPdu
(
  P2CONST(IpduM_ContainerRxPduType, AUTOMATIC, IPDUM_APPL_CONST) ContainerPdu,
  P2VAR(PduInfoType, AUTOMATIC, IPDUM_APPL_DATA) PduInfoPtr
)
{
  uint32 ContainedDLCLength = 0U;
  PduLengthType Idx;
  PduLengthType IdxOld = 0;
  boolean Stop = FALSE;
  const PduLengthType HeaderSize = ContainerPdu->HeaderSize;
  for (Idx = 0U; ((Idx < PduInfoPtr->SduLength) && (Idx >= IdxOld)); Idx += HeaderSize + (PduLengthType)ContainedDLCLength)
  {
    const PduLengthType RemainLen = PduInfoPtr->SduLength - Idx;

    /* only continue if there are enough bytes left to provide a complete header */
    if(RemainLen >= HeaderSize)
    {
      /* initialize PduHeaderId with 0U to handle the 4th byte for short header and the next 4 bytes for long header*/
      uint32 PduHeaderId = 0U;
      /* extract PDU Header Id: first 3 bytes for short header, first 4 bytes for long header */
      /* extract DLC: 4th byte for short header, 5th-7th bytes for long header */
      /* get header type: short(0), long(1) */
      if(HeaderSize == IPDUM_HEADERTYPE_SHORT)
      {
        /* Deviation MISRAC2012-4 */
        TS_MemCpy(((uint8*)&PduHeaderId + IPDUM_HDR_ID_OFFST), &PduInfoPtr->SduDataPtr[Idx], IPDUM_SHORT_HDR_DLC_OFFST);
        ContainedDLCLength = PduInfoPtr->SduDataPtr[Idx + IPDUM_SHORT_HDR_DLC_OFFST];
      }
      else
      {
        uint32 swapValue;
        TS_MemCpy(&PduHeaderId, &PduInfoPtr->SduDataPtr[Idx], 4U);
        TS_MemCpy(&ContainedDLCLength, &PduInfoPtr->SduDataPtr[Idx + 4U], 4U);
        swapValue = IPDUM_SWAPU32_IF_MUST(ContainedDLCLength);
        ContainedDLCLength = swapValue;
      }

      /* stop when a HeaderId = 0 is encountered */
      if(PduHeaderId != 0U)
      {
        if ((ContainedDLCLength + HeaderSize) > ContainedDLCLength)
        {
          /* only continue if there are enough bytes left to cover the PDU size read from DLC */
          if(RemainLen >= (ContainedDLCLength + HeaderSize))
          {
            sint32 CntdIdx = IPDUM_IDX_NOT_FOUND;
            P2CONST(IpduM_ContainedRxPduType, TYPEDEF, IPDUM_APPL_CONST) cntdRxPtr;
            uint32 startIdx = ContainerPdu->ContainedRxPduFirst;
            uint32 stopIdx;

            /* when ContainedRxPduFirst is less than RxCntdPduAcceptAllNum then
             * we have a IPDUM_ACCEPT_ALL container PDU
             */
            if(ContainerPdu->ContainedRxPduFirst < IpduM_ConfigPtr->RxCntdPduAcceptAllNum)
            {
              cntdRxPtr = IPDUM_CFG_GET_CNTD_RX_ACCEPTALL(0);
            }
            else
            {
              /* subtract number of contained PDUs which do not reference
               * any container PDU
               */
              startIdx -= IpduM_ConfigPtr->RxCntdPduAcceptAllNum;
              cntdRxPtr = IPDUM_CFG_GET_CNTD_RX(0);
            }

            stopIdx = startIdx + ContainerPdu->ContainedRxPduNum;

            CntdIdx = IpduM_RxCntd_BinSearch(cntdRxPtr, (sint32)startIdx, (sint32)stopIdx, PduHeaderId);

            if(IPDUM_IDX_NOT_FOUND != CntdIdx)
            {
              PduInfoType LocalPdu;

              LocalPdu.SduLength = (PduLengthType)ContainedDLCLength;
              LocalPdu.SduDataPtr =
                  &PduInfoPtr->SduDataPtr[Idx + HeaderSize];

              /* forward matching received PDUs to PduR */
              PduR_IpduMRxIndication(
                  cntdRxPtr[CntdIdx].OutgoingPduId,
                  &LocalPdu
              );
              /* Misra allows one break statement per each for/while loop */
            }
          }
          else
          {
#if (IPDUM_DEV_ERROR_DETECT == STD_ON)
            IPDUM_DET_REPORT_ERROR(IPDUM_SID_RX_INDICATION, IPDUM_E_HEADER);
#endif
            Stop = TRUE;
          }
        }
        else
        {
#if (IPDUM_DEV_ERROR_DETECT == STD_ON)
          IPDUM_DET_REPORT_ERROR(IPDUM_SID_RX_INDICATION, IPDUM_E_HEADER);
#endif
          Stop = TRUE;
        }
      }
      else
      {
        /* stop processing if a PDU header ID equal to 0 is encountered */
        Stop = TRUE;
      }
    }

    if(Stop == TRUE)
    {
      /* Misra allows one break statement per each for/while loop */
      break;
    }
  }
}

#if (IPDUM_STATIC_CONTAINER_PDU_HANDLING_ENABLE == STD_ON)
IPDUM_STATIC INLINE FUNC(boolean, IPDUM_CODE) IpduM_IsBitSet
(
  P2CONST(uint8, AUTOMATIC, IPDUM_APPL_CONST) DataPtr,
  uint32 BytePosition,
  uint8 BitMask
)
{
  boolean RetVal = FALSE;
  uint8 BitValue = (uint8)(DataPtr[BytePosition] & BitMask);

  if(BitValue > 0U)
  {
    RetVal = TRUE;
  }

  return RetVal;
}

IPDUM_STATIC FUNC(void, IPDUM_CODE) IpduM_HandleStaticRxPdu
(
  P2CONST(IpduM_ContainerRxPduType, AUTOMATIC, IPDUM_APPL_CONST) ContainerPdu,
  P2VAR(PduInfoType, AUTOMATIC, IPDUM_APPL_DATA) PduInfoPtr
)
{
  uint32 idx;
  uint32 startIdx = ContainerPdu->ContainedRxPduFirst;
  uint32 stopIdx = startIdx + ContainerPdu->ContainedRxPduNum;

  for(idx = startIdx; idx < stopIdx; idx++)
  {
    P2CONST(IpduM_StaticContainedRxPduType, AUTOMATIC, IPDUM_APPL_CONST) ContainedPdu = IPDUM_CFG_GET_STATIC_CNTD_RX(idx);
    boolean processPdu = FALSE;

    if(ContainedPdu->IpduMContainedPduOffset >= PduInfoPtr->SduLength)
    {
#if (IPDUM_DEV_ERROR_DETECT == STD_ON)
      IPDUM_DET_REPORT_ERROR(IPDUM_SID_RX_INDICATION, IPDUM_E_CONTAINER);
#endif
      break;
    }

    if(ContainedPdu->HasIpduMUpdateBitPositionSet)
    {
      if(IpduM_IsBitSet(PduInfoPtr->SduDataPtr, ContainedPdu->IpduMUpdateBitBytePosition, ContainedPdu->IpduMUpdateBitMask))
      {
        processPdu = TRUE;
      }
    }
    else
    {
      processPdu = TRUE;
    }

    if(processPdu)
    {
      PduInfoType LocalPdu;

      /* only that last contained PDU
       * can have variable size
       */
      if(idx ==  (stopIdx - 1U))
      {
        PduLengthType RemainingLength = PduInfoPtr->SduLength - (PduLengthType)ContainedPdu->IpduMContainedPduOffset;

        if(RemainingLength < ContainedPdu->PduLength)
        {
          LocalPdu.SduLength = RemainingLength;
        }
        else
        {
          LocalPdu.SduLength = ContainedPdu->PduLength;
        }
      }
      else
      {
        LocalPdu.SduLength = ContainedPdu->PduLength;
      }

      LocalPdu.SduDataPtr = &PduInfoPtr->SduDataPtr[ContainedPdu->IpduMContainedPduOffset];

      PduR_IpduMRxIndication(ContainedPdu->OutgoingPduId, &LocalPdu);
    }
  }
}
#endif /* IPDUM_STATIC_CONTAINER_PDU_HANDLING_ENABLE == STD_ON */

IPDUM_STATIC FUNC(void, IPDUM_CODE) IpduM_HandleRxContainerPdu
(
  PduIdType ContainerRxIndex,
  P2VAR(PduInfoType, AUTOMATIC, IPDUM_APPL_DATA) PduInfoPtr
)
{
  P2CONST(IpduM_ContainerRxPduType, AUTOMATIC, IPDUM_APPL_CONST) ContainerPdu =
      IPDUM_CFG_GET_CNTR_RX(ContainerRxIndex);

#if (IPDUM_STATIC_CONTAINER_PDU_HANDLING_ENABLE == STD_ON)
  if(ContainerPdu->HeaderSize == IPDUM_HEADERTYPE_NONE)
  {
    IpduM_HandleStaticRxPdu(ContainerPdu, PduInfoPtr);
  }
  else
#endif
  {
    IpduM_HandleDynamicRxPdu(ContainerPdu, PduInfoPtr);
  }
}

IPDUM_STATIC FUNC(void, IPDUM_CODE) IpduM_AddtoDeferredList
(
  PduIdType ContainerRxIndex,
  P2VAR(PduInfoType, AUTOMATIC, IPDUM_APPL_DATA) PduInfoPtr
)
{
  if(PduInfoPtr->SduLength <= IPDUM_CFG_GET_CNTR_RX(ContainerRxIndex)->PduLength)
  {
    /* Deviation MISRAC2012-1 */
    P2VAR(uint32, AUTOMATIC, IPDUM_VAR_NOINIT) deferredListPtr = IPDUM_GET_DEFERRED_LIST(IPDUM_GET_RX_MF_IDX(ContainerRxIndex));
#if((IPDUM_DEV_ERROR_DETECT == STD_ON) && (IPDUM_CONTAINER_QUEUING_RX == STD_ON))
    BufReq_ReturnType ret = BUFREQ_E_NOT_OK;
#endif /* IPDUM_DEV_ERROR_DETECT == STD_ON */
    const uint16 cntrByteIdx = ContainerRxIndex / (uint16)32U;
    const uint8 cntrBitIdx = ContainerRxIndex % 32U;

    /* Mark container */
    TS_AtomicSetBit_32(&deferredListPtr[cntrByteIdx], cntrBitIdx);

    SchM_Enter_IpduM_SCHM_IPDUM_EXCLUSIVE_AREA_0();

#if (IPDUM_CONTAINER_QUEUING_RX == STD_ON)
    if(IPDUM_CFG_GET_CNTR_RX(ContainerRxIndex)->ContainerQueueSize > 0U)
    {
#if (IPDUM_DEV_ERROR_DETECT == STD_ON)
      /* Deviation MISRAC2012-1 */
      ret = IPDUM_CNTRQ(PUSH, RX, ContainerRxIndex, &PduInfoPtr->SduDataPtr[0], &deferredDataPtr[0U], PduInfoPtr->SduLength);
#else
      /* Deviation MISRAC2012-1 */
      (void)IPDUM_CNTRQ(PUSH, RX, ContainerRxIndex, &PduInfoPtr->SduDataPtr[0], &deferredDataPtr[0U], PduInfoPtr->SduLength);
#endif
    }
    else
#endif /* IPDUM_CONTAINER_QUEUING_RX == STD_ON */
    {
      /* Deviation MISRAC2012-1 */
      P2VAR(uint8, AUTOMATIC, IPDUM_VAR_NOINIT) deferredDataPtr = IPDUM_GET_DEFERRED_DATA(ContainerRxIndex);

      TS_MemCpy(
          &deferredDataPtr[0U],
          &PduInfoPtr->SduLength,
          sizeof(PduLengthType)
      );
      TS_MemCpy(
          &deferredDataPtr[sizeof(PduLengthType)],
          &PduInfoPtr->SduDataPtr[0U],
          PduInfoPtr->SduLength
      );
    }

    SchM_Exit_IpduM_SCHM_IPDUM_EXCLUSIVE_AREA_0();

#if (IPDUM_CONTAINER_QUEUING_RX == STD_ON)
#if (IPDUM_DEV_ERROR_DETECT == STD_ON)
    if (BUFREQ_E_OVFL == ret)
    {
      IPDUM_DET_REPORT_ERROR(IPDUM_SID_RX_INDICATION, IPDUM_E_QUEUEOVFL);
    }
#endif /* IPDUM_DEV_ERROR_DETECT == STD_ON */
#endif /* IPDUM_CONTAINER_QUEUING_RX == STD_ON */
  }
#if (IPDUM_DEV_ERROR_DETECT == STD_ON)
  else
  {
    IPDUM_DET_REPORT_ERROR(IPDUM_SID_RX_INDICATION, IPDUM_E_CONTAINER);
  }
#endif /* IPDUM_DEV_ERROR_DETECT == STD_ON */
}

IPDUM_STATIC FUNC(void, IPDUM_CODE) IpduM_DynamicPackDataOne
(
  uint16 ContainedPduIndex,
  uint16 ParentContainerIndex,
  uint32 buffOffset,
  PduLengthType length,
  P2VAR(uint8, AUTOMATIC, IPDUM_APPL_DATA) DstBuffer,
  P2VAR(uint8, AUTOMATIC, IPDUM_APPL_DATA) SrcBuffer
)
{
  const uint8 headerSize = IPDUM_CFG_GET_CNTR_TX(ParentContainerIndex)->HeaderSize;
  uint32 headerId = IPDUM_CFG_GET_CNTD_TX(ContainedPduIndex)->IpduMContainedPduHeaderId;

  uint32 idxData = buffOffset;

  if(headerSize == IPDUM_HEADERTYPE_SHORT)
  {
    /* Deviation MISRAC2012-4 */
    TS_MemCpy(&DstBuffer[idxData], ((uint8*)&headerId + IPDUM_HDR_ID_OFFST), IPDUM_SHORT_HDR_DLC_OFFST);
    DstBuffer[idxData + IPDUM_SHORT_HDR_DLC_OFFST] = (uint8)length;
  }
  else
  {
    const uint32 len = IPDUM_SWAPU32_IF_MUST(length);

    TS_MemCpy(&DstBuffer[idxData], &headerId, 4U);
    TS_MemCpy(&DstBuffer[idxData + 4U], &len, 4U);
  }

  idxData += headerSize;

  TS_MemCpy(&DstBuffer[idxData], &SrcBuffer[0U], length);
}

IPDUM_STATIC FUNC(uint32, IPDUM_CODE) IpduM_DynamicPackDataAll
(
  P2VAR(uint8, AUTOMATIC, IPDUM_APPL_DATA) DstBuffer,
  uint16 ParentContainerIndex
)
{
  /* Deviation MISRAC2012-1 */
  P2VAR(uint32, AUTOMATIC, IPDUM_APPL_DATA) containerTxListSize = &IPDUM_GET_CNTR_TXDATA(ParentContainerIndex)->ListSize;
  /* Deviation MISRAC2012-1 */
  P2VAR(uint16, AUTOMATIC, AUTOMATIC) containerTxList = IPDUM_GET_TX_PDULIST(ParentContainerIndex);

  uint16 idx;

  uint32 buffOffset = 0U;
  uint16 numContained;
  const uint8 headerSize = IPDUM_CFG_GET_CNTR_TX(ParentContainerIndex)->HeaderSize;

  TS_AtomicAssign16(numContained, containerTxList[0U]);
  TS_AtomicAssign32((*containerTxListSize), 0U);

  for(idx = 1U; idx <= numContained; idx++)
  {
    uint16 containedIndex;

    PduInfoType pduInfo;
    Std_ReturnType retVal;
    P2CONST(IpduM_ContainedTxPduType, AUTOMATIC, AUTOMATIC) containedPtr;

    TS_AtomicAssign16(containedIndex, containerTxList[idx]);
    containedPtr = IPDUM_CFG_GET_CNTD_TX(containedIndex);

    pduInfo.SduDataPtr = IPDUM_GET_TX_CNTD_DATABUFF(containedIndex);
    pduInfo.SduLength = containedPtr->PduLength;

    retVal = PduR_IpduMTriggerTransmit(containedPtr->IpduMContainedTxPduHandleId, &pduInfo);

    SchM_Enter_IpduM_SCHM_IPDUM_EXCLUSIVE_AREA_0();

    if((Std_ReturnType)E_OK == retVal)
    {
      IpduM_DynamicPackDataOne(containedIndex, ParentContainerIndex, buffOffset, pduInfo.SduLength, DstBuffer, pduInfo.SduDataPtr);

      buffOffset += (uint32)headerSize + (uint32)pduInfo.SduLength;

      *containerTxListSize += (uint32)headerSize + (uint32)containedPtr->PduLength;
    }
    else
    {
      containerTxList[idx] = (uint16)(IpduM_ConfigPtr->TxContainedPduNum + 1U);
    }

    SchM_Exit_IpduM_SCHM_IPDUM_EXCLUSIVE_AREA_0();
  }

  SchM_Enter_IpduM_SCHM_IPDUM_EXCLUSIVE_AREA_0();

  /* Removing dropped ones from the list */
  /* The last element is inspected separately to avoid overallocation or out of bounds access */
  for(idx = 1U; idx < numContained; idx++)
  {
    if(containerTxList[idx] > IpduM_ConfigPtr->TxContainedPduNum)
    {
      containerTxList[idx] = containerTxList[idx + 1U];
      containerTxList[idx + 1U] = (uint16)(IpduM_ConfigPtr->TxContainedPduNum + 1U);
      containerTxList[0U]--;
    }
  }

  if(containerTxList[numContained] > IpduM_ConfigPtr->TxContainedPduNum)
  {
    containerTxList[0U]--;
  }

  SchM_Exit_IpduM_SCHM_IPDUM_EXCLUSIVE_AREA_0();

  return buffOffset;
}

#if (IPDUM_STATIC_CONTAINER_PDU_HANDLING_ENABLE == STD_ON)
IPDUM_STATIC INLINE FUNC(void, IPDUM_CODE) IpduM_AtomicSetBit
(
  P2VAR(uint8, AUTOMATIC, IPDUM_APPL_CONST) DataPtr,
  uint32 BytePosition,
  uint8 BitMask
)
{
  TS_AtomicAssign8(DataPtr[BytePosition], (uint8)(DataPtr[BytePosition] | BitMask));
}

IPDUM_STATIC FUNC(uint32, IPDUM_CODE) IpduM_StaticPackDataAll
(
  P2VAR(uint8, AUTOMATIC, IPDUM_APPL_DATA) DstBuffer,
  uint16 ParentContainerIndex
)
{
  /* Deviation MISRAC2012-1 */
  P2VAR(uint16, AUTOMATIC, AUTOMATIC) containerTxList = IPDUM_GET_TX_PDULIST(ParentContainerIndex);
  P2CONST(IpduM_ContainerTxPduType, AUTOMATIC, AUTOMATIC) cntrPtr = IPDUM_CFG_GET_CNTR_TX(ParentContainerIndex);

  uint16 idx;

  uint32 buffOffset = cntrPtr->StaticSduLength;
  uint16 numContained;

  SchM_Enter_IpduM_SCHM_IPDUM_EXCLUSIVE_AREA_0();

  numContained = containerTxList[0U];
  TS_MemSet(DstBuffer, cntrPtr->IpduMUnusedAreasDefault, cntrPtr->PduLength);

  SchM_Exit_IpduM_SCHM_IPDUM_EXCLUSIVE_AREA_0();

  for(idx = 1U; idx <= numContained; idx++)
  {
    uint16 containedIndex;
    P2CONST(IpduM_ContainedTxPduType, AUTOMATIC, AUTOMATIC) containedPtr;

    PduInfoType pduInfo;
    Std_ReturnType retVal;

    TS_AtomicAssign16(containedIndex, containerTxList[idx]);
    containedPtr = IPDUM_CFG_GET_CNTD_TX(containedIndex);

    pduInfo.SduDataPtr = IPDUM_GET_TX_CNTD_DATABUFF(containedIndex);
    pduInfo.SduLength = containedPtr->PduLength;

    retVal = PduR_IpduMTriggerTransmit(containedPtr->IpduMContainedTxPduHandleId, &pduInfo);

    if((Std_ReturnType)E_OK == retVal)
    {

      SchM_Enter_IpduM_SCHM_IPDUM_EXCLUSIVE_AREA_0();

      TS_MemCpy(&DstBuffer[containedPtr->IpduMContainedPduOffset], pduInfo.SduDataPtr, pduInfo.SduLength);

      SchM_Exit_IpduM_SCHM_IPDUM_EXCLUSIVE_AREA_0();

      if(idx == cntrPtr->NumCntdStatic)
      {
        buffOffset = (uint32)containedPtr->IpduMContainedPduOffset + (uint32)pduInfo.SduLength;
      }

      if(IPDUM_CNTRTX_HAS_UPDATE_BITS(cntrPtr->CfgFlags))
      {
        IpduM_AtomicSetBit(DstBuffer, containedPtr->IpduMUpdateBitBytePosition, containedPtr->IpduMUpdateBitMask);
      }
    }
    else
    {
      TS_AtomicAssign16(containerTxList[idx], (uint16)(IpduM_ConfigPtr->TxContainedPduNum + 1U));
    }
  }

  SchM_Enter_IpduM_SCHM_IPDUM_EXCLUSIVE_AREA_0();

  /* Removing dropped ones from the list */
  /* The last element is inspected separately to avoid overallocation or out of bounds access */
  for(idx = 1U; idx < numContained; idx++)
  {
    if(containerTxList[idx] > IpduM_ConfigPtr->TxContainedPduNum)
    {
      containerTxList[idx] = containerTxList[idx + 1U];
      containerTxList[idx + 1U] = (uint16)(IpduM_ConfigPtr->TxContainedPduNum + 1U);
      containerTxList[0U]--;
    }
  }

  if(containerTxList[numContained] > IpduM_ConfigPtr->TxContainedPduNum)
  {
    containerTxList[0U]--;
  }

  SchM_Exit_IpduM_SCHM_IPDUM_EXCLUSIVE_AREA_0();

  return buffOffset;
}
#endif /* IPDUM_STATIC_CONTAINER_PDU_HANDLING_ENABLE == STD_ON */

IPDUM_STATIC FUNC(boolean, IPDUM_CODE) IpduM_ContainsElem
(
  uint16 ParentContainerIndex,
  uint16 ContainedIndex
)
{
  /* Deviation MISRAC2012-1 */
  P2VAR(uint16, AUTOMATIC, IPDUM_APPL_DATA) containerTxList = IPDUM_GET_TX_PDULIST(ParentContainerIndex);
  uint16 idx;
  boolean ret = (boolean)FALSE;

  for(idx = (uint16)1; idx <= containerTxList[0U]; idx++)
  {
    if(ContainedIndex == containerTxList[idx])
    {
      ret = (boolean)TRUE;
      break;
    }
  }

  return ret;
}

IPDUM_STATIC FUNC(void, IPDUM_CODE) IpduM_AddtoList
(
  uint16 ContainedIndex,
  uint16 ParentContainerIndex,
  PduLengthType length
)
{
  /* Deviation MISRAC2012-1 */
  P2VAR(uint32, AUTOMATIC, IPDUM_APPL_DATA) containerTxListSize = &IPDUM_GET_CNTR_TXDATA(ParentContainerIndex)->ListSize;
  /* Deviation MISRAC2012-1 */
  P2VAR(uint16, AUTOMATIC, AUTOMATIC) containerTxList = IPDUM_GET_TX_PDULIST(ParentContainerIndex);
  const uint16 currentIndex = containerTxList[0U] + 1U;

  containerTxList[currentIndex] = ContainedIndex;
  containerTxList[0U] = currentIndex;

  *containerTxListSize += (PduLengthType)(length + IPDUM_CFG_GET_CNTR_TX(ParentContainerIndex)->HeaderSize);
}

IPDUM_STATIC FUNC(PduLengthType, IPDUM_CODE) IpduM_PackDataAllGeneric
(
  P2VAR(uint8, AUTOMATIC, AUTOMATIC) currentDataBuffer,
  uint16 ParentContainerIndex
)
{
  PduLengthType length;

#if (IPDUM_STATIC_CONTAINER_PDU_HANDLING_ENABLE == STD_ON)
  P2CONST(IpduM_ContainerTxPduType, AUTOMATIC, IPDUM_APPL_CONST) cntrPtr = IPDUM_CFG_GET_CNTR_TX(ParentContainerIndex);

  if (cntrPtr->HeaderSize == IPDUM_HEADERTYPE_NONE)
  {
    length = (PduLengthType)IpduM_StaticPackDataAll(currentDataBuffer, ParentContainerIndex);
  }
  else
#endif
  {
    length = (PduLengthType)IpduM_DynamicPackDataAll(currentDataBuffer, ParentContainerIndex);
  }

  return length;
}

IPDUM_STATIC FUNC(void, IPDUM_CODE) IpduM_AddtoListGeneric
(
#if ( (IPDUM_STATIC_CONTAINER_PDU_HANDLING_ENABLE == STD_ON) || (IPDUM_CONTAINEDTXPDU_PRIORITY_HANDLING_ENABLE == STD_ON) )
    P2CONST(IpduM_ContainerTxPduType, AUTOMATIC, IPDUM_APPL_CONST) cntrPtr,
#endif
    uint16 ContainedPduIndex,
    uint16 ParentContainerIndex,
    PduLengthType ContainedPduLength
)
{
#if (IPDUM_STATIC_CONTAINER_PDU_HANDLING_ENABLE == STD_ON)
  if (cntrPtr->HeaderSize == IPDUM_HEADERTYPE_NONE)
  {
    TS_PARAM_UNUSED(ContainedPduLength);
    IpduM_AddtoSortedList(ContainedPduIndex, ParentContainerIndex);
  }
  else
#endif
  {
#if (IPDUM_CONTAINEDTXPDU_PRIORITY_HANDLING_ENABLE == STD_ON)
    if(IPDUM_CNTRTX_HAS_PRIORITY(cntrPtr->CfgFlags))
    {
      IpduM_AddtoSortedPrioList(ContainedPduIndex, ParentContainerIndex, ContainedPduLength);
    }
    else
#endif
    {
      IpduM_AddtoList(ContainedPduIndex, ParentContainerIndex, ContainedPduLength);
    }
  }
}


#if (IPDUM_CONTAINEDTXPDU_PRIORITY_HANDLING_ENABLE == STD_ON)

IPDUM_STATIC FUNC(void, IPDUM_CODE) IpduM_AddtoSortedPrioList
(
  uint16 ContainedIndex,
  uint16 ParentContainerIndex,
  PduLengthType length
)
{
  /* Deviation MISRAC2012-1 */
  P2VAR(uint32, AUTOMATIC, IPDUM_APPL_DATA) containerTxListSize = &IPDUM_GET_CNTR_TXDATA(ParentContainerIndex)->ListSize;
  /* Deviation MISRAC2012-1 */
  P2VAR(uint16, AUTOMATIC, AUTOMATIC) containerTxList = IPDUM_GET_TX_PDULIST(ParentContainerIndex);
  const uint16 currentIndex = containerTxList[0U] + 1U;




    uint16 idx;
    uint16 NewCntdTxPos;
    P2CONST(IpduM_ContainedTxPduType, AUTOMATIC, AUTOMATIC) NewCntdTxCfg = IPDUM_CFG_GET_CNTD_TX(ContainedIndex);

    /* !LINKSTO IpduM.ASR44.SWS_IpduM_00249,1 */

    for(idx = 1U; idx < currentIndex; idx++)
    {
      P2CONST(IpduM_ContainedTxPduType, AUTOMATIC, AUTOMATIC) CurrCntdTxCfg = IPDUM_CFG_GET_CNTD_TX(containerTxList[idx]);
      if(CurrCntdTxCfg->IpduMContainedTxPduPriority > NewCntdTxCfg->IpduMContainedTxPduPriority)
      {
        break;
      }
    }

    NewCntdTxPos = idx;

    for(idx = currentIndex; idx > NewCntdTxPos; idx--)
    {
      containerTxList[idx] = containerTxList[idx - 1U];
    }

    containerTxList[NewCntdTxPos] = ContainedIndex;
    containerTxList[0U] = currentIndex;


  *containerTxListSize += (PduLengthType)(length + IPDUM_CFG_GET_CNTR_TX(ParentContainerIndex)->HeaderSize);
}

#endif


#if (IPDUM_STATIC_CONTAINER_PDU_HANDLING_ENABLE == STD_ON)
IPDUM_STATIC FUNC(void, IPDUM_CODE) IpduM_AddtoSortedList
(
  uint16 ContainedIndex,
  uint16 ParentContainerIndex
)
{
  /* Deviation MISRAC2012-1 */
  P2VAR(uint16, AUTOMATIC, AUTOMATIC) containerTxList = IPDUM_GET_TX_PDULIST(ParentContainerIndex);
  const uint16 currentIndex = containerTxList[0U] + 1U;

  if(currentIndex == 1U)
  {
    containerTxList[currentIndex] = ContainedIndex;
    containerTxList[0U] = currentIndex;
  }
  else
  {
    uint16 idx;
    uint16 NewCntdTxPos;
    P2CONST(IpduM_ContainedTxPduType, AUTOMATIC, AUTOMATIC) NewCntdTxConf = IPDUM_CFG_GET_CNTD_TX(ContainedIndex);

    for(idx = 1U; idx < currentIndex; idx++)
    {
      P2CONST(IpduM_ContainedTxPduType, AUTOMATIC, AUTOMATIC) CurrCntdTxConf = IPDUM_CFG_GET_CNTD_TX(containerTxList[idx]);
      if(CurrCntdTxConf->IpduMContainedPduOffset > NewCntdTxConf->IpduMContainedPduOffset)
      {
        break;
      }
    }

    NewCntdTxPos = idx;

    for(idx = currentIndex; idx > NewCntdTxPos; idx--)
    {
      containerTxList[idx] = containerTxList[idx - 1U];
    }

    containerTxList[NewCntdTxPos] = ContainedIndex;
    containerTxList[0U] = currentIndex;
  }
}
#endif /* IPDUM_STATIC_CONTAINER_PDU_HANDLING_ENABLE == STD_ON */

IPDUM_STATIC FUNC(boolean, IPDUM_CODE) IpduM_CheckSizeTrigger
(
  uint16 ParentContainerIndex,
  PduLengthType length,
  P2CONST(IpduM_ContainerTxPduType, AUTOMATIC, IPDUM_APPL_CONST) cntrPtr
)
{
  /* Deviation MISRAC2012-1 */
  P2VAR(uint32, AUTOMATIC, AUTOMATIC) containerTxListSize = &IPDUM_GET_CNTR_TXDATA(ParentContainerIndex)->ListSize;
  boolean ret;
  const PduLengthType headerSize = cntrPtr->HeaderSize;
  if((*containerTxListSize + (uint32)length + (uint32)headerSize) <= (uint32)cntrPtr->PduLength)
  {
    ret = (boolean)FALSE;
  }
  else
  {
    ret = (boolean)TRUE;
  }

  return ret;
}

IPDUM_STATIC FUNC(void, IPDUM_CODE) IpduM_CntrConfPrepare
(
  PduIdType id
#if (IPDUM_CONTAINER_QUEUING_TX == STD_ON)
  ,P2CONST(IpduM_ContainerTxPduType, AUTOMATIC, IPDUM_APPL_CONST) cntrPtr,
  P2VAR(IpduM_ContainerQueueType, AUTOMATIC, IPDUM_APPL_DATA) qPtr
#endif
)
{
#if (IPDUM_CONTAINER_QUEUING_TX == STD_ON)
    const uint16 txconf_offset = ((TRUE == IPDUM_IS_QUEUED(cntrPtr->CfgFlags)) ? (uint16) qPtr->QPushIdx : 0U) * (uint16) cntrPtr->chunkSize;
#else
    const uint16 txconf_offset = 0U;
#endif
    /* Deviation MISRAC2012-1 */
    P2VAR(uint16, AUTOMATIC, AUTOMATIC) pduList = IPDUM_GET_TX_PDULIST(id);
    /* Deviation MISRAC2012-1 */
    P2VAR(uint16, AUTOMATIC, AUTOMATIC) confList = IPDUM_GET_TX_CONFLIST(id);

    /* store Contained indexes for later confirmation */
    TS_MemCpy(&confList[txconf_offset],
              &pduList[0U],
              sizeof(pduList[0U]) * ((uint32)pduList[0U] + 1U)
    );
}

IPDUM_STATIC FUNC(void, IPDUM_CODE) IpduM_CurrCntrPrepare
(
#if(IPDUM_CNTND_COLLECT_QUEUED_TX == STD_ON)
  boolean isLastIsBest,
  CONSTP2CONST(uint8, AUTOMATIC, IPDUM_APPL_DATA) currentDataBuffer,
#endif
  PduIdType id,
  P2VAR(PduInfoType, AUTOMATIC, AUTOMATIC) pduInfo
)
{
#if(IPDUM_CNTND_COLLECT_QUEUED_TX == STD_ON)
  if(isLastIsBest)
#endif
  {
    pduInfo->SduLength = IpduM_PackDataAllGeneric(
        pduInfo->SduDataPtr,
        id
    );
  }
#if(IPDUM_CNTND_COLLECT_QUEUED_TX == STD_ON)
  else
  {
    SchM_Enter_IpduM_SCHM_IPDUM_EXCLUSIVE_AREA_0();

    /* Deviation MISRAC2012-1 */
    pduInfo->SduLength = (PduLengthType)IPDUM_GET_CNTR_TXDATA(id)->ListSize;
    TS_MemCpy(pduInfo->SduDataPtr, currentDataBuffer, pduInfo->SduLength);

    SchM_Exit_IpduM_SCHM_IPDUM_EXCLUSIVE_AREA_0();
  }
#endif
}

IPDUM_STATIC FUNC(void, IPDUM_CODE) IpduM_SendCurrCntr
(
  PduIdType id
)
{
  P2CONST(IpduM_ContainerTxPduType, AUTOMATIC, IPDUM_APPL_CONST) cntrPtr = IPDUM_CFG_GET_CNTR_TX(id);
  /* Deviation MISRAC2012-1 */
  P2VAR(IpduM_CntrTxDataType, AUTOMATIC, AUTOMATIC) cntrRamPtr = IPDUM_GET_CNTR_TXDATA(id);
  /* Deviation MISRAC2012-1 */
  P2VAR(uint16, AUTOMATIC, AUTOMATIC) containerTxList = IPDUM_GET_TX_PDULIST(id);
#if (IPDUM_CONTAINER_QUEUING_TX == STD_ON)
  /* Deviation MISRAC2012-1 */
  P2VAR(IpduM_ContainerQueueType, AUTOMATIC, IPDUM_APPL_DATA) qPtr = IPDUM_GET_TX_QUEUE(id);
  const boolean isContainerQueued = IPDUM_IS_QUEUED(cntrPtr->CfgFlags);
#endif

#if(IPDUM_CNTND_COLLECT_QUEUED_TX == STD_ON)
  const boolean isLastIsBest = IPDUM_IS_CNTR_LAST_IS_BEST(cntrPtr->CfgFlags);
  P2VAR(uint8, AUTOMATIC, AUTOMATIC) currentDataBuffer = IPDUM_GET_TX_CURRDATABUFF(id);
#endif

  uint8 localDataBuffer[IPDUM_MAX_CONTAINER_TX_LENGTH];
  PduInfoType pduInfo;

  Std_ReturnType retVal = (Std_ReturnType) E_NOT_OK;

  pduInfo.SduDataPtr = localDataBuffer;

#if(IPDUM_CNTND_COLLECT_QUEUED_TX == STD_ON)
  IpduM_CurrCntrPrepare(isLastIsBest, currentDataBuffer, id, &pduInfo);
#else
  IpduM_CurrCntrPrepare(id, &pduInfo);
#endif

  SchM_Enter_IpduM_SCHM_IPDUM_EXCLUSIVE_AREA_0();

#if (IPDUM_CONTAINER_QUEUING_TX == STD_ON)
  IpduM_CntrConfPrepare(id, cntrPtr, qPtr);
#else
  IpduM_CntrConfPrepare(id);
#endif

  if(pduInfo.SduLength > 0U)
  {
    cntrRamPtr->ConfirmTimeout = cntrPtr->IpduMContainerTxConfirmationTimeout;
  }

  SchM_Exit_IpduM_SCHM_IPDUM_EXCLUSIVE_AREA_0();

  if(pduInfo.SduLength > 0U)
  {
    retVal = PduR_IpduMTransmit(IPDUM_CFG_GET_CNTR_TX(id)->IpduMContainerTxHandleId, &pduInfo);
  }

  SchM_Enter_IpduM_SCHM_IPDUM_EXCLUSIVE_AREA_0();

  if(pduInfo.SduLength > 0U)
  {
    if(retVal == E_OK)
    {
      containerTxList[0U] = 0U;
      cntrRamPtr->ListSize = 0U;
    }
    else
    {
      cntrRamPtr->ConfirmTimeout = 0U;

#if (IPDUM_CONTAINER_QUEUING_TX == STD_ON)
      if(isContainerQueued)
      {
        IpduM_CntrQAdd(id, localDataBuffer, pduInfo.SduLength);
      }
      else
#endif
      {
        containerTxList[0U] = 0U;
        cntrRamPtr->ListSize = 0U;
      }
    }
  }

  SchM_Exit_IpduM_SCHM_IPDUM_EXCLUSIVE_AREA_0();
}

#if (IPDUM_CONTAINER_QUEUING_TX == STD_ON)
IPDUM_STATIC FUNC(void, IPDUM_CODE) IpduM_DequeueCntr
(
  PduIdType id
)
{
  P2CONST(IpduM_ContainerTxPduType, AUTOMATIC, IPDUM_APPL_CONST) cntrPtr = IPDUM_CFG_GET_CNTR_TX(id);
  /* Deviation MISRAC2012-1 */
  P2VAR(IpduM_ContainerQueueType, AUTOMATIC, IPDUM_APPL_DATA) qPtr = IPDUM_GET_TX_QUEUE(id);
  /* Deviation MISRAC2012-1 */
  P2VAR(IpduM_CntrTxDataType, AUTOMATIC, AUTOMATIC) cntrRamPtr = IPDUM_GET_CNTR_TXDATA(id);

  uint8 localDataBuffer[IPDUM_MAX_CONTAINER_TX_LENGTH];
  PduInfoType pduInfo;

  Std_ReturnType retVal = (Std_ReturnType) E_NOT_OK;

  SchM_Enter_IpduM_SCHM_IPDUM_EXCLUSIVE_AREA_0();


  pduInfo.SduDataPtr = localDataBuffer;

  /* Deviation MISRAC2012-1 */
  IPDUM_CNTRQ(PEEK, TX, id, NULL_PTR, pduInfo.SduDataPtr, &pduInfo.SduLength);

  cntrRamPtr->ConfirmTimeout = cntrPtr->IpduMContainerTxConfirmationTimeout;

  SchM_Exit_IpduM_SCHM_IPDUM_EXCLUSIVE_AREA_0();


  retVal = PduR_IpduMTransmit(IPDUM_CFG_GET_CNTR_TX(id)->IpduMContainerTxHandleId, &pduInfo);


  SchM_Enter_IpduM_SCHM_IPDUM_EXCLUSIVE_AREA_0();

  if(retVal == E_OK)
  {
    qPtr->QPopIdx = ((qPtr->QPopIdx + 1U) % cntrPtr->IpduMContainerQueueSize); qPtr->QFull = 0U;
  }
  else
  {
    cntrRamPtr->ConfirmTimeout = 0U;
  }

  SchM_Exit_IpduM_SCHM_IPDUM_EXCLUSIVE_AREA_0();
}
#endif

IPDUM_STATIC FUNC(void, IPDUM_CODE) IpduM_CntrSizeAnnounce
(
  PduIdType id
)
{
  P2CONST(IpduM_ContainerTxPduType, AUTOMATIC, IPDUM_APPL_CONST) cntrPtr = IPDUM_CFG_GET_CNTR_TX(id);
  /* Deviation MISRAC2012-1 */
  P2VAR(IpduM_CntrTxDataType, AUTOMATIC, AUTOMATIC) cntrRamPtr = IPDUM_GET_CNTR_TXDATA(id);
  /* Deviation MISRAC2012-1 */
  P2VAR(uint16, AUTOMATIC, AUTOMATIC) cntrTxList = IPDUM_GET_TX_PDULIST(id);

#if (IPDUM_CONTAINER_QUEUING_TX == STD_ON)
  const boolean isContainerQueued = IPDUM_IS_QUEUED(cntrPtr->CfgFlags);
  boolean callInstancePrep = FALSE;
#if (IPDUM_CNTND_COLLECT_QUEUED_TX == STD_ON)
  const boolean isLastIsBest = IPDUM_IS_CNTR_LAST_IS_BEST(cntrPtr->CfgFlags);
  CONSTP2VAR(uint8, AUTOMATIC, AUTOMATIC) currentDataBuffer = IPDUM_GET_TX_CURRDATABUFF(id);
#endif /* IPDUM_CNTND_COLLECT_QUEUED_TX == STD_ON */
#endif /* IPDUM_CONTAINER_QUEUING_TX == STD_ON */

  Std_ReturnType retVal = (Std_ReturnType) E_NOT_OK;

  {
    PduInfoType pduInfo;
    pduInfo.SduDataPtr = NULL_PTR;
    pduInfo.SduLength = cntrPtr->PduLength;


    retVal = PduR_IpduMTransmit(IPDUM_CFG_GET_CNTR_TX(id)->IpduMContainerTxHandleId, &pduInfo);
  }

  if(retVal == E_NOT_OK)
  {
#if (IPDUM_CONTAINER_QUEUING_TX == STD_ON)
    if(isContainerQueued)
    {
      /* Remove these once the module switches to the Atomics module */
      boolean lclQMFSizeAnnounceFlag;
      TS_AtomicAssign8(lclQMFSizeAnnounceFlag, cntrRamPtr->QMFSizeAnnounceFlag);

      if(FALSE == lclQMFSizeAnnounceFlag)
      {
        uint32 len;
        TS_AtomicAssign32(len, cntrRamPtr->ListSize);
        if(len > 0U)
        {
          callInstancePrep = TRUE;
        }
      }

      TS_AtomicAssign8(cntrRamPtr->QMFSizeAnnounceFlag, (uint8)TRUE);
    }
    else
#endif
    {
      TS_AtomicAssign32(cntrRamPtr->ListSize, (uint32)0U);
      TS_AtomicAssign16(cntrTxList[0U], (uint16)0U);
    }
  }
  else
  {
#if (IPDUM_CONTAINER_QUEUING_TX == STD_ON)
    if(isContainerQueued)
    {
      TS_AtomicAssign8(cntrRamPtr->QMFSizeAnnounceFlag, (uint8)FALSE);
    }
#endif
  }

#if (IPDUM_CONTAINER_QUEUING_TX == STD_ON)
  if(callInstancePrep)
  {
    SchM_Enter_IpduM_SCHM_IPDUM_EXCLUSIVE_AREA_0();

#if(IPDUM_CNTND_COLLECT_QUEUED_TX == STD_ON)
    if(FALSE != isLastIsBest)
    {
      (void)IpduM_CntrQCntdListOnly(id);
    }
    else
#endif
    {
      IpduM_CntrQAdd(id, currentDataBuffer, cntrRamPtr->ListSize);
    }

    SchM_Exit_IpduM_SCHM_IPDUM_EXCLUSIVE_AREA_0();
  }
#endif
}

IPDUM_STATIC FUNC(void, IPDUM_CODE) IpduM_LastIsBest_CntrAdd
(
    uint16 ParentContainerIndex,
    uint16 ContainedPduIndex,
    P2VAR(boolean, AUTOMATIC, AUTOMATIC) sendTrigger,
    P2VAR(boolean, AUTOMATIC, AUTOMATIC) sizeTrigger
)
{
  /* check if Contained PDU is already present in Container PDU */
  if ((boolean) FALSE == IpduM_ContainsElem(ParentContainerIndex, ContainedPduIndex))
  {
    /* no, it is not, try to add it */

    const PduLengthType ContainedPduLength = IPDUM_CFG_GET_CNTD_TX(ContainedPduIndex)->PduLength;
    P2CONST(IpduM_ContainerTxPduType, AUTOMATIC, IPDUM_APPL_CONST) cntrPtr = IPDUM_CFG_GET_CNTR_TX(ParentContainerIndex);
    const IpduM_TxSendTimeoutType configuredContainedSendTimeout = IPDUM_CFG_GET_CNTD_TX(ContainedPduIndex)->IpduMContainedTxPduSendTimeout;
    /* Deviation MISRAC2012-1 */
    P2VAR(IpduM_CntrTxDataType, AUTOMATIC, AUTOMATIC) cntrRamPtr = IPDUM_GET_CNTR_TXDATA(ParentContainerIndex);
    /* Deviation MISRAC2012-1 */
    P2VAR(uint16, AUTOMATIC, AUTOMATIC) containerTxList = IPDUM_GET_TX_PDULIST(ParentContainerIndex);

    /* check if the Contained fits into Container */
    if(IpduM_CheckSizeTrigger(ParentContainerIndex, ContainedPduLength, cntrPtr))
    {
      /* it does not, trigger sending */
      *sendTrigger = TRUE;
      *sizeTrigger = TRUE;
    }
    else
    {
      /* load configured send timeout when container is empty */
      if(containerTxList[0U] == 0U)
      {
        cntrRamPtr->SendTimeout = configuredContainedSendTimeout;
      }

      /* add it to the Container List */
      IpduM_AddtoListGeneric(
      #if ( (IPDUM_STATIC_CONTAINER_PDU_HANDLING_ENABLE == STD_ON) || (IPDUM_CONTAINEDTXPDU_PRIORITY_HANDLING_ENABLE == STD_ON) )
              cntrPtr,
      #endif
              ContainedPduIndex,
              ParentContainerIndex,
              ContainedPduLength
          );
    }
  }
}

#if (IPDUM_CNTND_COLLECT_QUEUED_TX == STD_ON)
IPDUM_STATIC FUNC(void, IPDUM_CODE) IpduM_Queued_CntrAdd
(
    uint16 ParentContainerIndex,
    uint16 ContainedPduIndex,
    P2VAR(boolean, AUTOMATIC, AUTOMATIC) sendTrigger,
    P2VAR(boolean, AUTOMATIC, AUTOMATIC) sizeTrigger,
    P2CONST(PduInfoType, AUTOMATIC, AUTOMATIC) PduInfoPtr
)
{
  P2CONST(IpduM_ContainerTxPduType, AUTOMATIC, IPDUM_APPL_CONST) cntrPtr = IPDUM_CFG_GET_CNTR_TX(ParentContainerIndex);
  CONSTP2VAR(uint8, AUTOMATIC, IPDUM_APPL_DATA) currentDataBuffer = IPDUM_GET_TX_CURRDATABUFF(ParentContainerIndex);
  const IpduM_TxSendTimeoutType configuredContainedSendTimeout = IPDUM_CFG_GET_CNTD_TX(ContainedPduIndex)->IpduMContainedTxPduSendTimeout;
  /* Deviation MISRAC2012-1 */
  P2VAR(IpduM_CntrTxDataType, AUTOMATIC, AUTOMATIC) cntrRamPtr = IPDUM_GET_CNTR_TXDATA(ParentContainerIndex);
  /* Deviation MISRAC2012-1 */
  P2VAR(uint16, AUTOMATIC, AUTOMATIC) containerTxList = IPDUM_GET_TX_PDULIST(ParentContainerIndex);

  if(IpduM_CheckSizeTrigger(ParentContainerIndex, PduInfoPtr->SduLength, cntrPtr))
  {
    *sendTrigger = TRUE;
    *sizeTrigger = TRUE;
  }
  else
  {
    /* load configured send timeout when container is empty */
    if(containerTxList[0U] == 0U)
    {
      cntrRamPtr->SendTimeout = configuredContainedSendTimeout;
    }

    /* add it to the Container List */
    /* Deviation MISRAC2012-1 */
    IpduM_DynamicPackDataOne(ContainedPduIndex, ParentContainerIndex, IPDUM_GET_CNTR_TXDATA(ParentContainerIndex)->ListSize, PduInfoPtr->SduLength, currentDataBuffer, PduInfoPtr->SduDataPtr);
    IpduM_AddtoList(ContainedPduIndex, ParentContainerIndex, PduInfoPtr->SduLength);
  }
}
#endif

IPDUM_STATIC FUNC(void, IPDUM_CODE) IpduM_UpdateCntrSendTimeout
(
  IpduM_TxSendTimeoutType configuredContainedSendTimeout,
  P2CONST(uint16, AUTOMATIC, IPDUM_APPL_DATA) ContainerTxList,
  P2VAR(IpduM_TxSendTimeoutType, AUTOMATIC, IPDUM_APPL_DATA) sendTimeoutCounter
)
{
  /* check if the container is not empty
   * and update send timeout */
  if((uint16)1 < ContainerTxList[0U])
  {
    /* check if the configured Contained Tx send timeout is
     * less than current sendTimeoutCounter
     */
    if (*sendTimeoutCounter > configuredContainedSendTimeout)
    {
      /* update sendTimeoutCounter if it is */
      *sendTimeoutCounter = configuredContainedSendTimeout;
    }
  }
}

#if (IPDUM_STATIC_CONTAINER_PDU_HANDLING_ENABLE == STD_ON)
IPDUM_STATIC INLINE FUNC(void, IPDUM_CODE) IpduM_StaticCntrCheckTrigger
(
  uint16 ParentContainerIndex,
  P2VAR(boolean, AUTOMATIC, IPDUM_APPL_DATA) sendTrigger
)
{
  /* Deviation MISRAC2012-1 */
  P2VAR(uint16, AUTOMATIC, AUTOMATIC) containerTxList = IPDUM_GET_TX_PDULIST(ParentContainerIndex);
  P2CONST(IpduM_ContainerTxPduType, AUTOMATIC, AUTOMATIC) cntrPtr = IPDUM_CFG_GET_CNTR_TX(ParentContainerIndex);

  /* if all contained PDUs get updated
   * then container must be triggered for sending
   */
  if(containerTxList[0U] == cntrPtr->NumCntdStatic)
  {
    *sendTrigger = TRUE;
  }
}
#endif /* IPDUM_STATIC_CONTAINER_PDU_HANDLING_ENABLE == STD_ON */

IPDUM_STATIC INLINE FUNC(void, IPDUM_CODE) IpduM_CntrCheckSendTrigger
(
  uint16 ParentContainerIndex,
  P2VAR(boolean, AUTOMATIC, IPDUM_APPL_DATA) sendTrigger
)
{
  P2CONST(IpduM_ContainerTxPduType, AUTOMATIC, IPDUM_APPL_CONST) cntrPtr = IPDUM_CFG_GET_CNTR_TX(ParentContainerIndex);
  /* Deviation MISRAC2012-1 */
  P2VAR(IpduM_CntrTxDataType, AUTOMATIC, AUTOMATIC) cntrRamPtr = IPDUM_GET_CNTR_TXDATA(ParentContainerIndex);

  /* check condition trigger
   * - Size triggering.
   * */
  if(cntrRamPtr->ListSize == (uint32)cntrPtr->PduLength)
  {
    *sendTrigger = (boolean)TRUE;
  }
}

IPDUM_STATIC INLINE FUNC(void, IPDUM_CODE) IpduM_LastIsBest_CntrCheckTriggers
(
  uint16 ParentContainerIndex,
  uint16 ContainedPduIndex,
  P2CONST(uint16, AUTOMATIC, IPDUM_APPL_DATA) ContainerTxList,
  P2VAR(boolean, AUTOMATIC, IPDUM_APPL_DATA) trigger
)
{
  uint16 idx;
  PduLengthType length = 0U;
  P2CONST(IpduM_ContainerTxPduType, AUTOMATIC, IPDUM_APPL_CONST) cntrPtr = IPDUM_CFG_GET_CNTR_TX(ParentContainerIndex);
  /* Deviation MISRAC2012-1 */
  P2VAR(uint16, AUTOMATIC, AUTOMATIC) cntrTxList = IPDUM_GET_TX_PDULIST(ParentContainerIndex);
  /* Deviation MISRAC2012-1 */
  P2VAR(IpduM_CntrTxDataType, AUTOMATIC, AUTOMATIC) cntrRamPtr = IPDUM_GET_CNTR_TXDATA(ParentContainerIndex);

  const uint16 currentIndex = ContainerTxList[0U];

  for(idx = 1U; idx <= currentIndex; idx++)
  {
    uint16 containedIndex = ContainerTxList[idx];

    length += IPDUM_CFG_GET_CNTD_TX(containedIndex)->PduLength;
  }

  length += ((PduLengthType)currentIndex * (PduLengthType)cntrPtr->HeaderSize);

  if((uint32)length >= cntrPtr->IpduMContainerTxSizeThreshold)
  {
    *trigger = (boolean) TRUE;
  }

  /* check condition triggers
   * - Threshold triggering
   * - IpduMContainerTxFirstContainedPduTrigger triggering
   * - IPDUM_TRIGGER_ALWAYS triggering
   * */
  if(
      (cntrRamPtr->ListSize >= cntrPtr->IpduMContainerTxSizeThreshold)
      ||((IPDUM_IS_TRGGR_FIRST(cntrPtr->CfgFlags) == TRUE) && (cntrTxList[0U] == 1U))
      || (IPDUM_IS_CNTND_TRGGR_ALWAYS(IPDUM_CFG_GET_CNTD_TX(ContainedPduIndex)->CfgFlags) == TRUE)
    )
  {
    *trigger = (boolean)TRUE;
  }
}

#if (IPDUM_CNTND_COLLECT_QUEUED_TX == STD_ON)
IPDUM_STATIC INLINE FUNC(void, IPDUM_CODE) IpduM_Queued_CntrCheckTriggers
(
  uint16 ParentContainerIndex,
  uint16 ContainedPduIndex,
  P2VAR(boolean, AUTOMATIC, IPDUM_APPL_DATA) trigger
)
{
  P2CONST(IpduM_ContainerTxPduType, AUTOMATIC, IPDUM_APPL_CONST) cntrPtr = IPDUM_CFG_GET_CNTR_TX(ParentContainerIndex);
  /* Deviation MISRAC2012-1 */
  P2VAR(uint16, AUTOMATIC, AUTOMATIC) cntrTxList = IPDUM_GET_TX_PDULIST(ParentContainerIndex);
  /* Deviation MISRAC2012-1 */
  P2VAR(IpduM_CntrTxDataType, AUTOMATIC, AUTOMATIC) cntrRamPtr = IPDUM_GET_CNTR_TXDATA(ParentContainerIndex);

  /* check condition triggers
   * - Threshold triggering
   * - IpduMContainerTxFirstContainedPduTrigger triggering
   * - IPDUM_TRIGGER_ALWAYS triggering
   * */
  if(
      (cntrRamPtr->ListSize >= cntrPtr->IpduMContainerTxSizeThreshold)
      ||((IPDUM_IS_TRGGR_FIRST(cntrPtr->CfgFlags) == TRUE) && (cntrTxList[0U] == 1U))
      || (IPDUM_IS_CNTND_TRGGR_ALWAYS(IPDUM_CFG_GET_CNTD_TX(ContainedPduIndex)->CfgFlags) == TRUE)
    )
  {
    *trigger = (boolean)TRUE;
  }
}
#endif


IPDUM_STATIC FUNC(void, IPDUM_CODE) IpduM_CntrTxConfirmation
(
  PduIdType TxPduId
)
{
  const uint16 ParentContainerIndex = (uint16)TxPduId - (uint16)IpduM_ConfigPtr->TxPathWayLen;
  /* Deviation MISRAC2012-1 */
  P2VAR(uint16, AUTOMATIC, AUTOMATIC) ConfirmationList = IPDUM_GET_TX_CONFLIST(ParentContainerIndex);
  /* Deviation MISRAC2012-1 */
  P2VAR(IpduM_CntrTxDataType, AUTOMATIC, AUTOMATIC) cntrRamPtr = IPDUM_GET_CNTR_TXDATA(ParentContainerIndex);
  uint16 idxTbl;
  boolean internalTransmitFlag = (boolean)FALSE;
#if (IPDUM_CONTAINER_QUEUING_TX == STD_ON)
  P2CONST(IpduM_ContainerTxPduType, AUTOMATIC, IPDUM_APPL_CONST)  cntrPtr = IPDUM_CFG_GET_CNTR_TX(ParentContainerIndex);
  const boolean isQueued = IPDUM_IS_QUEUED(cntrPtr->CfgFlags);
#endif

  IpduM_TxConfirmTimeoutType confTimeout;

  TS_AtomicAssign16(confTimeout, cntrRamPtr->ConfirmTimeout);

  if(0U < confTimeout)
  {
    uint16 numContained;

#if (IPDUM_CONTAINER_QUEUING_TX == STD_OFF)
    uint16 txConf_offset = 0U;
#else
    uint16 txConf_offset;
    uint8 qOfsVal;

    /* Deviation MISRAC2012-1 */
    P2VAR(IpduM_ContainerQueueType, AUTOMATIC, IPDUM_APPL_DATA) qPtr = IPDUM_GET_TX_QUEUE(ParentContainerIndex);

    if(isQueued)
    {
      if((!IPDUM_IS_TXMODE_DIRECT(cntrPtr->CfgFlags)) && (IPDUM_IS_CNTR_LAST_IS_BEST(cntrPtr->CfgFlags)))
      {
        TS_AtomicAssign8(qOfsVal, qPtr->QLBTxConf);
      }
      else
      {
        TS_AtomicAssign8(qOfsVal, qPtr->QPopIdx);
      }
      txConf_offset = (uint16)qOfsVal * (uint16) cntrPtr->chunkSize;
    }
    else
    {
      txConf_offset = 0U;
    }
#endif

    TS_AtomicAssign16(numContained, ConfirmationList[txConf_offset]);

    for(idxTbl = 1U; idxTbl <= numContained; idxTbl++)
    {
      uint16 ContainedTxPduIndex;
      P2CONST(IpduM_ContainedTxPduType, AUTOMATIC, AUTOMATIC) ContainedTxPdu;

      TS_AtomicAssign16(ContainedTxPduIndex, ConfirmationList[idxTbl + txConf_offset]);

      ContainedTxPdu = IPDUM_CFG_GET_CNTD_TX(ContainedTxPduIndex);

      if(IPDUM_IS_CNTND_TXCONF(ContainedTxPdu->CfgFlags) == (boolean)TRUE)
      {
        PduR_IpduMTxConfirmation(ContainedTxPdu->IpduMContainedTxPduHandleId);
      }
    }

    SchM_Enter_IpduM_SCHM_IPDUM_EXCLUSIVE_AREA_0();

    TS_AtomicAssign16(ConfirmationList[txConf_offset], 0U);
    TS_AtomicAssign16(cntrRamPtr->ConfirmTimeout, 0U);

    SchM_Exit_IpduM_SCHM_IPDUM_EXCLUSIVE_AREA_0();
  }

  SchM_Enter_IpduM_SCHM_IPDUM_EXCLUSIVE_AREA_0();

  if((boolean)TRUE == cntrRamPtr->ConfAwait)
  {
    cntrRamPtr->ConfAwait = (boolean) FALSE;

#if (IPDUM_CONTAINER_QUEUING_TX == STD_ON)
    if((boolean)TRUE == isQueued)
    {
      internalTransmitFlag = (boolean)TRUE;
    }
    else
#endif
    {
      if(cntrRamPtr->ListSize > 0U)
      {
        internalTransmitFlag = (boolean)TRUE;
      }
    }
  }

#if ((IPDUM_CONTAINER_QUEUING_TX == STD_ON) && (IPDUM_DEQUEUE_IN_TX_CONF == STD_ON))
  if((boolean) TRUE == IPDUM_IS_TXMODE_DIRECT(IPDUM_CFG_GET_CNTR_TX(ParentContainerIndex)->CfgFlags))
  {
    if((boolean) TRUE == isQueued)
    {
      if((boolean) FALSE == IpduM_IsCntrQEmpty(ParentContainerIndex))
      {
        internalTransmitFlag = (boolean)TRUE;
      }
    }
  }
#endif

  SchM_Exit_IpduM_SCHM_IPDUM_EXCLUSIVE_AREA_0();

  if((boolean)TRUE == internalTransmitFlag)
  {
    /* If internalTransmitFlag is set, we've just reset ConfAwait
     * Check if this confirmation is interrupting, postpone it
     * until the next MainFunction if yes
     */
    uint8 MtxVal;
    TS_AtomicAssign8(MtxVal, cntrRamPtr->TxMtx);
    if(0U != MtxVal)
    {
      TS_AtomicAssign8(cntrRamPtr->ConfAwait, (boolean)TRUE);
    }
    else
    {
      IpduM_CallCntrSendFunction(ParentContainerIndex);
    }
  }
}

IPDUM_STATIC FUNC(void, IPDUM_CODE) IpduM_SetFlags_DT_LastIsBest_NoCntrQueuing
(
  P2VAR(IpduM_CntrTxDataType, AUTOMATIC, AUTOMATIC) cntrRamPtr,
  P2VAR(Std_ReturnType, AUTOMATIC, AUTOMATIC) RetValue,
  P2VAR(boolean, AUTOMATIC, AUTOMATIC) prepareCurrentInstance,
  boolean sendTrigger
)
{
  if((boolean)TRUE == sendTrigger)
  {
    if(0U < cntrRamPtr->ConfirmTimeout)
    {
      cntrRamPtr->ConfAwait = (boolean) TRUE;
      *RetValue = (Std_ReturnType) E_NOT_OK;
    }
    else
    {
      *prepareCurrentInstance = TRUE;
    }
  }
}

IPDUM_STATIC FUNC(Std_ReturnType, IPDUM_CODE) IpduM_DT_LastIsBest_NoCntrQueuing
(
    PduIdType TxPduId
)
{
  Std_ReturnType RetValue;

  const uint16 ContainedPduIndex = (uint16)TxPduId - (uint16)IpduM_ConfigPtr->TxPartLen;
  const uint16 ParentContainerIndex = IPDUM_CFG_GET_CNTD_TX(ContainedPduIndex)->IpduMContainerTxIndex;
  P2CONST(IpduM_ContainerTxPduType, AUTOMATIC, IPDUM_APPL_CONST) cntrPtr = IPDUM_CFG_GET_CNTR_TX(ParentContainerIndex);
  /* Deviation MISRAC2012-1 */
  P2VAR(IpduM_CntrTxDataType, AUTOMATIC, AUTOMATIC) cntrRamPtr = IPDUM_GET_CNTR_TXDATA(ParentContainerIndex);
  const PduLengthType ContainedPduLength = IPDUM_CFG_GET_CNTD_TX(ContainedPduIndex)->PduLength;
  const IpduM_TxSendTimeoutType configuredContainedSendTimeout = IPDUM_CFG_GET_CNTD_TX(ContainedPduIndex)->IpduMContainedTxPduSendTimeout;
  /* Deviation MISRAC2012-1 */
  P2VAR(uint16, AUTOMATIC, AUTOMATIC) containerTxList = IPDUM_GET_TX_PDULIST(ParentContainerIndex);
  /* Deviation MISRAC2012-1 */
  P2VAR(uint16, AUTOMATIC, AUTOMATIC) containerConfTxList = IPDUM_GET_TX_CONFLIST(ParentContainerIndex);

  uint16 currentIndex;
  PduLengthType length;
  PduInfoType pduInfo;
  uint8 localDataBuffer[IPDUM_MAX_CONTAINER_TX_LENGTH];

  boolean sendTrigger = (boolean) FALSE;
  boolean sizeTrigger = (boolean) FALSE;
  boolean internalTransmitFlag = (boolean) FALSE;
  boolean prepareCurrentInstance = FALSE;

  SchM_Enter_IpduM_SCHM_IPDUM_EXCLUSIVE_AREA_0();

  RetValue = (Std_ReturnType) E_OK;

  IpduM_LastIsBest_CntrAdd(ParentContainerIndex, ContainedPduIndex, &sendTrigger, &sizeTrigger);
  IpduM_UpdateCntrSendTimeout(configuredContainedSendTimeout, (P2CONST(uint16, AUTOMATIC, AUTOMATIC))containerTxList, &cntrRamPtr->SendTimeout);
  IpduM_CntrCheckSendTrigger(ParentContainerIndex, &sendTrigger);
  IpduM_LastIsBest_CntrCheckTriggers(ParentContainerIndex, ContainedPduIndex, (P2CONST(uint16, AUTOMATIC, AUTOMATIC))containerTxList, &sendTrigger);

#if (IPDUM_STATIC_CONTAINER_PDU_HANDLING_ENABLE == STD_ON)
  IpduM_StaticCntrCheckTrigger(ParentContainerIndex, &sendTrigger);
#endif

  IpduM_SetFlags_DT_LastIsBest_NoCntrQueuing(
    cntrRamPtr,
    &RetValue,
    &prepareCurrentInstance,
    sendTrigger
  );

  SchM_Exit_IpduM_SCHM_IPDUM_EXCLUSIVE_AREA_0();

  if(prepareCurrentInstance)
  {
    length = IpduM_PackDataAllGeneric(
        localDataBuffer,
        ParentContainerIndex
    );

    pduInfo.SduLength = length;
    pduInfo.SduDataPtr = localDataBuffer;

    if(length > 0U)
    {
      internalTransmitFlag = (boolean) TRUE;

      TS_AtomicAssign16(cntrRamPtr->ConfirmTimeout, cntrPtr->IpduMContainerTxConfirmationTimeout);
    }
  }

  if(internalTransmitFlag)
  {
    RetValue = PduR_IpduMTransmit(IPDUM_CFG_GET_CNTR_TX(ParentContainerIndex)->IpduMContainerTxHandleId, &pduInfo);
  }

  SchM_Enter_IpduM_SCHM_IPDUM_EXCLUSIVE_AREA_0();

  if(internalTransmitFlag)
  {
    if(RetValue == E_OK)
    {
      currentIndex = containerTxList[0U];
      currentIndex++;

      TS_MemCpy(&containerConfTxList[0U], &containerTxList[0U], currentIndex * sizeof(containerTxList[0U]));

      cntrRamPtr->SendTimeout = 0U;
    }
    else
    {
      cntrRamPtr->ConfirmTimeout = 0U;
    }

    containerTxList[0U] = 0U;
    cntrRamPtr->ListSize = 0U;
  }

/*   if it was a size trigger, add the Contained which
     did not fit to a new instance only if it fits */

  if(((boolean)TRUE == sizeTrigger) && ((boolean)FALSE == cntrRamPtr->ConfAwait))
  {
    cntrRamPtr->SendTimeout = configuredContainedSendTimeout;

    IpduM_AddtoListGeneric(
    #if ( (IPDUM_STATIC_CONTAINER_PDU_HANDLING_ENABLE == STD_ON) || (IPDUM_CONTAINEDTXPDU_PRIORITY_HANDLING_ENABLE == STD_ON) )
            cntrPtr,
    #endif
            ContainedPduIndex,
            ParentContainerIndex,
            ContainedPduLength
        );
  }

  SchM_Exit_IpduM_SCHM_IPDUM_EXCLUSIVE_AREA_0();

  return RetValue;
}

#if (IPDUM_CONTAINER_QUEUING_TX == STD_ON)

IPDUM_STATIC FUNC(void, IPDUM_CODE) IpduM_SetFlags_DT_LastIsBest_WithCntrQueuing
(
  P2VAR(IpduM_CntrTxDataType, AUTOMATIC, AUTOMATIC) cntrRamPtr,
  P2VAR(boolean, AUTOMATIC, AUTOMATIC) addToQCurrentInstance,
  P2VAR(boolean, AUTOMATIC, AUTOMATIC) prepareCurrentInstance,
  boolean sendTrigger
)
{
  if((boolean)TRUE == sendTrigger)
   {
     if(0U < cntrRamPtr->ConfirmTimeout)
     {
       *addToQCurrentInstance = TRUE;
     }
     else
     {
       *prepareCurrentInstance = TRUE;
     }
   }
}

IPDUM_STATIC FUNC(Std_ReturnType, IPDUM_CODE) IpduM_DT_LastIsBest_WithCntrQueuing
(
    PduIdType TxPduId
)
{
  Std_ReturnType RetValue;

  const uint16 ContainedPduIndex = (uint16)TxPduId - (uint16)IpduM_ConfigPtr->TxPartLen;
  const uint16 ParentContainerIndex = IPDUM_CFG_GET_CNTD_TX(ContainedPduIndex)->IpduMContainerTxIndex;
  P2CONST(IpduM_ContainerTxPduType, AUTOMATIC, IPDUM_APPL_CONST) cntrPtr = IPDUM_CFG_GET_CNTR_TX(ParentContainerIndex);
  /* Deviation MISRAC2012-1 */
  P2VAR(IpduM_CntrTxDataType, AUTOMATIC, AUTOMATIC) cntrRamPtr = IPDUM_GET_CNTR_TXDATA(ParentContainerIndex);
  const PduLengthType ContainedPduLength = IPDUM_CFG_GET_CNTD_TX(ContainedPduIndex)->PduLength;
  /* Deviation MISRAC2012-1 */
  P2VAR(uint16, AUTOMATIC, AUTOMATIC) containerTxList = IPDUM_GET_TX_PDULIST(ParentContainerIndex);
  /* Deviation MISRAC2012-1 */
  P2VAR(uint16, AUTOMATIC, AUTOMATIC) containerConfTxList = IPDUM_GET_TX_CONFLIST(ParentContainerIndex);
  const IpduM_TxSendTimeoutType configuredContainedSendTimeout = IPDUM_CFG_GET_CNTD_TX(ContainedPduIndex)->IpduMContainedTxPduSendTimeout;
  P2VAR(uint8, AUTOMATIC, IPDUM_APPL_DATA) currentDataBuffer = IPDUM_GET_TX_CURRDATABUFF(ParentContainerIndex);
  /* Deviation MISRAC2012-1 */
  P2VAR(IpduM_ContainerQueueType, AUTOMATIC, IPDUM_APPL_DATA) qPtr = IPDUM_GET_TX_QUEUE(ParentContainerIndex);
  uint16 currentIndex;
  PduLengthType length = 0U;
  PduInfoType pduInfo;

  boolean sendTrigger = (boolean) FALSE;
  boolean sizeTrigger = (boolean) FALSE;
  boolean internalTransmitFlag = (boolean) FALSE;
  boolean prepareCurrentInstance = FALSE;
  boolean addToQCurrentInstance = FALSE;

  SchM_Enter_IpduM_SCHM_IPDUM_EXCLUSIVE_AREA_0();

  RetValue = (Std_ReturnType) E_OK;

  IpduM_LastIsBest_CntrAdd(ParentContainerIndex, ContainedPduIndex, &sendTrigger, &sizeTrigger);
  IpduM_UpdateCntrSendTimeout(configuredContainedSendTimeout, (P2CONST(uint16, AUTOMATIC, AUTOMATIC))containerTxList, &cntrRamPtr->SendTimeout);
  IpduM_CntrCheckSendTrigger(ParentContainerIndex, &sendTrigger);
  IpduM_LastIsBest_CntrCheckTriggers(ParentContainerIndex, ContainedPduIndex, (P2CONST(uint16, AUTOMATIC, AUTOMATIC))containerTxList, &sendTrigger);

#if (IPDUM_STATIC_CONTAINER_PDU_HANDLING_ENABLE == STD_ON)
  IpduM_StaticCntrCheckTrigger(ParentContainerIndex, &sendTrigger);
#endif

  IpduM_SetFlags_DT_LastIsBest_WithCntrQueuing(
    cntrRamPtr,
    &addToQCurrentInstance,
    &prepareCurrentInstance,
    sendTrigger
  );

  SchM_Exit_IpduM_SCHM_IPDUM_EXCLUSIVE_AREA_0();

  if(addToQCurrentInstance)
  {
    length = IpduM_PackDataAllGeneric(
        currentDataBuffer,
        ParentContainerIndex
    );

    if(length > 0U)
    {
      SchM_Enter_IpduM_SCHM_IPDUM_EXCLUSIVE_AREA_0();
      IpduM_CntrQAdd(ParentContainerIndex, currentDataBuffer, length);
      SchM_Exit_IpduM_SCHM_IPDUM_EXCLUSIVE_AREA_0();
    }

    addToQCurrentInstance = FALSE;
  }

  if(prepareCurrentInstance)
  {
    length = IpduM_PackDataAllGeneric(
        currentDataBuffer,
        ParentContainerIndex
    );

    pduInfo.SduLength = length;
    pduInfo.SduDataPtr = currentDataBuffer;

    if(length > 0U)
    {
      internalTransmitFlag = (boolean) TRUE;

      TS_AtomicAssign16(cntrRamPtr->ConfirmTimeout, cntrPtr->IpduMContainerTxConfirmationTimeout);
    }
  }

  if(internalTransmitFlag)
  {
    RetValue = PduR_IpduMTransmit(IPDUM_CFG_GET_CNTR_TX(ParentContainerIndex)->IpduMContainerTxHandleId, &pduInfo);
  }

  SchM_Enter_IpduM_SCHM_IPDUM_EXCLUSIVE_AREA_0();

  if(internalTransmitFlag)
  {
    if(RetValue == E_OK)
    {
      uint16 txConf_offset = (uint16) qPtr->QPushIdx * (uint16) cntrPtr->chunkSize;

      currentIndex = containerTxList[0U];
      currentIndex++;

      TS_MemCpy(&containerConfTxList[txConf_offset], &containerTxList[0U], currentIndex * sizeof(containerTxList[0U]));

      cntrRamPtr->SendTimeout = 0U;
      containerTxList[0U] = 0U;
      cntrRamPtr->ListSize = 0U;
    }
    else
    {
      cntrRamPtr->ConfirmTimeout = 0U;

      addToQCurrentInstance = TRUE;
    }
  }

  if(addToQCurrentInstance)
  {
    IpduM_CntrQAdd(ParentContainerIndex, currentDataBuffer, length);
  }
  SchM_Exit_IpduM_SCHM_IPDUM_EXCLUSIVE_AREA_0();
/*   if it was a size trigger, add the Contained which
     did not fit to a new instance */

  if((boolean)TRUE == sizeTrigger)
  {

    SchM_Enter_IpduM_SCHM_IPDUM_EXCLUSIVE_AREA_0();

    cntrRamPtr->SendTimeout = configuredContainedSendTimeout;

    IpduM_AddtoListGeneric(
    #if ( (IPDUM_STATIC_CONTAINER_PDU_HANDLING_ENABLE == STD_ON) || (IPDUM_CONTAINEDTXPDU_PRIORITY_HANDLING_ENABLE == STD_ON) )
            cntrPtr,
    #endif
            ContainedPduIndex,
            ParentContainerIndex,
            ContainedPduLength
        );

    SchM_Exit_IpduM_SCHM_IPDUM_EXCLUSIVE_AREA_0();
  }

  return E_OK;
}
#endif

#if (IPDUM_CNTND_COLLECT_QUEUED_TX == STD_ON)
IPDUM_STATIC FUNC(Std_ReturnType, IPDUM_CODE) IpduM_DT_Queued_NoCntrQueuing
(
    PduIdType TxPduId,
    P2CONST(PduInfoType, AUTOMATIC, IPDUM_APPL_DATA) PduInfoPtr
)
{
  Std_ReturnType RetValue;

  const uint16 ContainedPduIndex = (uint16)TxPduId - (uint16)IpduM_ConfigPtr->TxPartLen;
  const uint16 ParentContainerIndex = IPDUM_CFG_GET_CNTD_TX(ContainedPduIndex)->IpduMContainerTxIndex;
  P2CONST(IpduM_ContainerTxPduType, AUTOMATIC, IPDUM_APPL_CONST) cntrPtr = IPDUM_CFG_GET_CNTR_TX(ParentContainerIndex);
  /* Deviation MISRAC2012-1 */
  P2VAR(IpduM_CntrTxDataType, AUTOMATIC, AUTOMATIC) cntrRamPtr = IPDUM_GET_CNTR_TXDATA(ParentContainerIndex);
  /* Deviation MISRAC2012-1 */
  P2VAR(uint16, AUTOMATIC, AUTOMATIC) containerTxList = IPDUM_GET_TX_PDULIST(ParentContainerIndex);
  P2VAR(uint8, AUTOMATIC, AUTOMATIC) currentDataBuffer = IPDUM_GET_TX_CURRDATABUFF(ParentContainerIndex);
  const IpduM_TxSendTimeoutType configuredContainedSendTimeout = IPDUM_CFG_GET_CNTD_TX(ContainedPduIndex)->IpduMContainedTxPduSendTimeout;
  uint16 currentIndex;
  PduLengthType length;
  PduInfoType pduInfo;
  uint8 localDataBuffer[IPDUM_MAX_CONTAINER_TX_LENGTH];

  boolean sendTrigger = (boolean) FALSE;
  boolean sizeTrigger = (boolean) FALSE;
  boolean internalTransmitFlag = (boolean) FALSE;

  SchM_Enter_IpduM_SCHM_IPDUM_EXCLUSIVE_AREA_0();

  RetValue = (Std_ReturnType) E_OK;

  IpduM_Queued_CntrAdd(ParentContainerIndex, ContainedPduIndex, &sendTrigger, &sizeTrigger, PduInfoPtr);
  IpduM_UpdateCntrSendTimeout(configuredContainedSendTimeout, (P2CONST(uint16, AUTOMATIC, AUTOMATIC))containerTxList, &cntrRamPtr->SendTimeout);
  IpduM_CntrCheckSendTrigger(ParentContainerIndex, &sendTrigger);
  IpduM_Queued_CntrCheckTriggers(ParentContainerIndex, ContainedPduIndex, &sendTrigger);

  if((boolean)TRUE == sendTrigger)
  {
    if(0U < cntrRamPtr->ConfirmTimeout)
    {
      cntrRamPtr->ConfAwait = (boolean) TRUE;
      RetValue = (Std_ReturnType) E_NOT_OK;
    }
    else
    {
      internalTransmitFlag = (boolean) TRUE;

      length = (PduLengthType) cntrRamPtr->ListSize;
      TS_MemCpy(localDataBuffer, currentDataBuffer, length);

      pduInfo.SduLength = length;
      pduInfo.SduDataPtr = localDataBuffer;

      cntrRamPtr->ConfirmTimeout = cntrPtr->IpduMContainerTxConfirmationTimeout;
    }
  }

  SchM_Exit_IpduM_SCHM_IPDUM_EXCLUSIVE_AREA_0();

  if(internalTransmitFlag)
  {
    RetValue = PduR_IpduMTransmit(IPDUM_CFG_GET_CNTR_TX(ParentContainerIndex)->IpduMContainerTxHandleId, &pduInfo);
  }

  SchM_Enter_IpduM_SCHM_IPDUM_EXCLUSIVE_AREA_0();

  if(internalTransmitFlag)
   {
     if(RetValue == E_OK)
     {
       currentIndex = containerTxList[0U];
       currentIndex++;

       /* Deviation MISRAC2012-1 */
       TS_MemCpy(IPDUM_GET_TX_CONFLIST(ParentContainerIndex), &containerTxList[0U], currentIndex * sizeof(containerTxList[0U]));

       cntrRamPtr->SendTimeout = 0U;
     }
     else
     {
       cntrRamPtr->ConfirmTimeout = 0U;
     }

     containerTxList[0U] = 0U;
     cntrRamPtr->ListSize = 0U;
   }

 /*   if it was a size trigger, add the Contained which
      did not fit to a new instance */

   if(((boolean)TRUE == sizeTrigger) && ((boolean)FALSE == cntrRamPtr->ConfAwait))
   {
     cntrRamPtr->SendTimeout = configuredContainedSendTimeout;

     IpduM_DynamicPackDataOne(ContainedPduIndex, ParentContainerIndex, cntrRamPtr->ListSize, PduInfoPtr->SduLength, currentDataBuffer, PduInfoPtr->SduDataPtr);
     IpduM_AddtoList(ContainedPduIndex, ParentContainerIndex, PduInfoPtr->SduLength);
   }

   SchM_Exit_IpduM_SCHM_IPDUM_EXCLUSIVE_AREA_0();

   return RetValue;
}
#endif

#if (IPDUM_CNTND_COLLECT_QUEUED_TX == STD_ON)
#if (IPDUM_CONTAINER_QUEUING_TX == STD_ON)
IPDUM_STATIC FUNC(Std_ReturnType, IPDUM_CODE) IpduM_DT_Queued_WithCntrQueuing
(
    PduIdType TxPduId,
    P2CONST(PduInfoType, AUTOMATIC, IPDUM_APPL_DATA) PduInfoPtr
)
{
  Std_ReturnType RetValue;

  const uint16 ContainedPduIndex = (uint16)TxPduId - (uint16)IpduM_ConfigPtr->TxPartLen;
  const uint16 ParentContainerIndex = IPDUM_CFG_GET_CNTD_TX(ContainedPduIndex)->IpduMContainerTxIndex;
  P2CONST(IpduM_ContainerTxPduType, AUTOMATIC, IPDUM_APPL_CONST) cntrPtr = IPDUM_CFG_GET_CNTR_TX(ParentContainerIndex);
  /* Deviation MISRAC2012-1 */
  P2VAR(IpduM_CntrTxDataType, AUTOMATIC, AUTOMATIC) cntrRamPtr = IPDUM_GET_CNTR_TXDATA(ParentContainerIndex);
  /* Deviation MISRAC2012-1 */
  P2VAR(uint16, AUTOMATIC, AUTOMATIC) containerTxList = IPDUM_GET_TX_PDULIST(ParentContainerIndex);
  /* Deviation MISRAC2012-1 */
  P2VAR(uint16, AUTOMATIC, AUTOMATIC) containerConfTxList = IPDUM_GET_TX_CONFLIST(ParentContainerIndex);
  const IpduM_TxSendTimeoutType configuredContainedSendTimeout = IPDUM_CFG_GET_CNTD_TX(ContainedPduIndex)->IpduMContainedTxPduSendTimeout;
  P2VAR(uint8, AUTOMATIC, AUTOMATIC) currentDataBuffer = IPDUM_GET_TX_CURRDATABUFF(ParentContainerIndex);
  /* Deviation MISRAC2012-1 */
  P2VAR(IpduM_ContainerQueueType, AUTOMATIC, IPDUM_APPL_DATA) qPtr = IPDUM_GET_TX_QUEUE(ParentContainerIndex);
  uint16 currentIndex;
  PduLengthType length = 0U;
  PduInfoType pduInfo;
  uint8 localDataBuffer[IPDUM_MAX_CONTAINER_TX_LENGTH];

  boolean sendTrigger = (boolean) FALSE;
  boolean sizeTrigger = (boolean) FALSE;
  boolean internalTransmitFlag = (boolean) FALSE;
  boolean addToQCurrentInstance = FALSE;

  SchM_Enter_IpduM_SCHM_IPDUM_EXCLUSIVE_AREA_0();

  RetValue = (Std_ReturnType) E_OK;

  IpduM_Queued_CntrAdd(ParentContainerIndex, ContainedPduIndex, &sendTrigger, &sizeTrigger, PduInfoPtr);
  IpduM_UpdateCntrSendTimeout(configuredContainedSendTimeout, (P2CONST(uint16, AUTOMATIC, AUTOMATIC))containerTxList, &cntrRamPtr->SendTimeout);
  IpduM_CntrCheckSendTrigger(ParentContainerIndex, &sendTrigger);
  IpduM_Queued_CntrCheckTriggers(ParentContainerIndex, ContainedPduIndex, &sendTrigger);

  if((boolean)TRUE == sendTrigger)
  {
    if(0U < cntrRamPtr->ConfirmTimeout)
    {
      length = (PduLengthType)cntrRamPtr->ListSize;
      addToQCurrentInstance = TRUE;
    }
    else
    {
      internalTransmitFlag = (boolean) TRUE;

      length = (PduLengthType)cntrRamPtr->ListSize;
      TS_MemCpy(localDataBuffer, currentDataBuffer, length);

      pduInfo.SduLength = length;
      pduInfo.SduDataPtr = localDataBuffer;

      cntrRamPtr->ConfirmTimeout = cntrPtr->IpduMContainerTxConfirmationTimeout;
    }
  }

  if(addToQCurrentInstance)
  {
    IpduM_CntrQAdd(ParentContainerIndex, currentDataBuffer, length);
    addToQCurrentInstance = FALSE;
  }

  SchM_Exit_IpduM_SCHM_IPDUM_EXCLUSIVE_AREA_0();

  if(internalTransmitFlag)
  {
    RetValue = PduR_IpduMTransmit(IPDUM_CFG_GET_CNTR_TX(ParentContainerIndex)->IpduMContainerTxHandleId, &pduInfo);
  }

  SchM_Enter_IpduM_SCHM_IPDUM_EXCLUSIVE_AREA_0();

  if(internalTransmitFlag)
   {
     if(RetValue == E_OK)
     {
       uint16 txConf_offset = (uint16) qPtr->QPushIdx * (uint16) cntrPtr->chunkSize;

       currentIndex = containerTxList[0U];
       currentIndex++;

       TS_MemCpy(&containerConfTxList[txConf_offset], &containerTxList[0U], currentIndex * sizeof(containerTxList[0U]));

       cntrRamPtr->SendTimeout = 0U;
       containerTxList[0U] = 0U;
       cntrRamPtr->ListSize = 0U;
     }
     else
     {
       cntrRamPtr->ConfirmTimeout = 0U;

       addToQCurrentInstance = TRUE;
     }


   }

  if(addToQCurrentInstance)
  {
    IpduM_CntrQAdd(ParentContainerIndex, localDataBuffer, length);
  }

  SchM_Exit_IpduM_SCHM_IPDUM_EXCLUSIVE_AREA_0();

 /*   if it was a size trigger, add the Contained which
      did not fit to a new instance*/

   if((boolean)TRUE == sizeTrigger)
   {
     SchM_Enter_IpduM_SCHM_IPDUM_EXCLUSIVE_AREA_0();

     cntrRamPtr->SendTimeout = configuredContainedSendTimeout;

     IpduM_DynamicPackDataOne(ContainedPduIndex, ParentContainerIndex, cntrRamPtr->ListSize, PduInfoPtr->SduLength, currentDataBuffer, PduInfoPtr->SduDataPtr);
     IpduM_AddtoList(ContainedPduIndex, ParentContainerIndex, PduInfoPtr->SduLength);

     SchM_Exit_IpduM_SCHM_IPDUM_EXCLUSIVE_AREA_0();
   }

   return E_OK;
}
#endif
#endif

IPDUM_STATIC FUNC(void, IPDUM_CODE) IpduM_SetFlags_TT_LastIsBest_NoCntrQueuing
(
  P2VAR(IpduM_CntrTxDataType, AUTOMATIC, AUTOMATIC) cntrRamPtr,
  P2VAR(Std_ReturnType, AUTOMATIC, AUTOMATIC) RetValue,
  P2VAR(boolean, AUTOMATIC, AUTOMATIC) ttSizeAnnounce,
  boolean sizeAnnounceTrg,
  boolean sendTrigger
)
{
  if(sizeAnnounceTrg)
  {
    if(0U < cntrRamPtr->ConfirmTimeout)
    {
      if((boolean) FALSE == cntrRamPtr->AnnounceSize)
      {
        cntrRamPtr->ConfAwait = (boolean) TRUE;
        cntrRamPtr->AnnounceSize = (boolean) TRUE;
      }
    }
    else
    {
      if((boolean) FALSE == cntrRamPtr->AnnounceSize)
      {
        *ttSizeAnnounce = (boolean) TRUE;
      }
    }
  }

  if((boolean)TRUE == sendTrigger)
  {
    if(0U < cntrRamPtr->ConfirmTimeout)
    {
      *RetValue = (Std_ReturnType) E_NOT_OK;

      if((boolean) FALSE == cntrRamPtr->AnnounceSize)
      {
        cntrRamPtr->ConfAwait = (boolean) TRUE;
      }
    }
    else
    {
      if((boolean) FALSE == cntrRamPtr->AnnounceSize)
      {
        *ttSizeAnnounce = (boolean) TRUE;
      }
    }
  }
}

IPDUM_STATIC FUNC(Std_ReturnType, IPDUM_CODE) IpduM_TT_LastIsBest_NoCntrQueuing
(
    PduIdType TxPduId
)
{
  Std_ReturnType RetValue;

  const uint16 ContainedPduIndex = (uint16)TxPduId - (uint16)IpduM_ConfigPtr->TxPartLen;
  const uint16 ParentContainerIndex = IPDUM_CFG_GET_CNTD_TX(ContainedPduIndex)->IpduMContainerTxIndex;
  P2CONST(IpduM_ContainerTxPduType, AUTOMATIC, IPDUM_APPL_CONST) cntrPtr = IPDUM_CFG_GET_CNTR_TX(ParentContainerIndex);
  /* Deviation MISRAC2012-1 */
  P2VAR(IpduM_CntrTxDataType, AUTOMATIC, AUTOMATIC) cntrRamPtr = IPDUM_GET_CNTR_TXDATA(ParentContainerIndex);
  /* Deviation MISRAC2012-1 */
  P2VAR(uint16, AUTOMATIC, AUTOMATIC) containerTxList = IPDUM_GET_TX_PDULIST(ParentContainerIndex);
  const IpduM_TxSendTimeoutType configuredContainedSendTimeout = IPDUM_CFG_GET_CNTD_TX(ContainedPduIndex)->IpduMContainedTxPduSendTimeout;

  boolean sendTrigger = (boolean) FALSE;
  boolean sizeTrigger = (boolean) FALSE;
  boolean ttSizeAnnounce = (boolean) FALSE;
  boolean sizeAnnounceTrg = (boolean) FALSE;

  SchM_Enter_IpduM_SCHM_IPDUM_EXCLUSIVE_AREA_0();

  RetValue = (Std_ReturnType) E_OK;

  IpduM_LastIsBest_CntrAdd(ParentContainerIndex, ContainedPduIndex, &sendTrigger, &sizeTrigger);
  IpduM_UpdateCntrSendTimeout(configuredContainedSendTimeout, (P2CONST(uint16, AUTOMATIC, AUTOMATIC))containerTxList, &cntrRamPtr->SendTimeout);
  IpduM_CntrCheckSendTrigger(ParentContainerIndex, &sendTrigger);
  IpduM_LastIsBest_CntrCheckTriggers(ParentContainerIndex, ContainedPduIndex, (P2CONST(uint16, AUTOMATIC, AUTOMATIC))containerTxList, &sizeAnnounceTrg);

  IpduM_SetFlags_TT_LastIsBest_NoCntrQueuing(
    cntrRamPtr,
    &RetValue,
    &ttSizeAnnounce,
    sizeAnnounceTrg,
    sendTrigger
  );

  SchM_Exit_IpduM_SCHM_IPDUM_EXCLUSIVE_AREA_0();

  if(ttSizeAnnounce)
  {
    PduInfoType pduInfo;
    pduInfo.SduDataPtr = NULL_PTR;
    pduInfo.SduLength = cntrPtr->PduLength;

    RetValue = PduR_IpduMTransmit(cntrPtr->IpduMContainerTxHandleId, &pduInfo);

    if(sendTrigger)
    {
      if(E_NOT_OK == RetValue)
      {
        SchM_Enter_IpduM_SCHM_IPDUM_EXCLUSIVE_AREA_0();

        cntrRamPtr->ListSize = 0U;
        containerTxList[0U] = 0U;
        cntrRamPtr->AnnounceSize = (boolean) FALSE;

        SchM_Exit_IpduM_SCHM_IPDUM_EXCLUSIVE_AREA_0();
      }
    }
    else
    {
      if(E_OK == RetValue)
      {
        SchM_Enter_IpduM_SCHM_IPDUM_EXCLUSIVE_AREA_0();

        cntrRamPtr->AnnounceSize = (boolean) TRUE;
        cntrRamPtr->SendTimeout = 0U;

        SchM_Exit_IpduM_SCHM_IPDUM_EXCLUSIVE_AREA_0();
      }
    }
  }

  if(sizeTrigger)
  {
    RetValue = E_NOT_OK;
  }

  return RetValue;
}

#if (IPDUM_CONTAINER_QUEUING_TX == STD_ON)

IPDUM_STATIC FUNC(void, IPDUM_CODE) IpduM_SetFlags_TT_LastIsBest_WithCntrQueuing
(
  P2VAR(IpduM_CntrTxDataType, AUTOMATIC, AUTOMATIC) cntrRamPtr,
  P2VAR(boolean, AUTOMATIC, AUTOMATIC) addToQCurrentInstance,
  P2VAR(boolean, AUTOMATIC, AUTOMATIC) ttSizeAnnounce,
  uint16 ParentContainerIndex,
  boolean sizeAnnounceTrg,
  boolean sendTrigger
)
{
  if(sizeAnnounceTrg)
   {
     if(0U == cntrRamPtr->ConfirmTimeout)
     {
       if((boolean) FALSE == cntrRamPtr->AnnounceSize)
       {
         if(IpduM_IsCntrQEmpty(ParentContainerIndex))
         {
           *ttSizeAnnounce = (boolean) TRUE;
         }
       }
     }
     else
     {
       cntrRamPtr->AnnounceSize = (boolean) TRUE;
       cntrRamPtr->ConfAwait = TRUE;
     }
   }

   if((boolean)TRUE == sendTrigger)
   {
     if(0U == cntrRamPtr->ConfirmTimeout)
     {
      if(IpduM_IsCntrQEmpty(ParentContainerIndex))
       {
         if((boolean) FALSE == cntrRamPtr->AnnounceSize)
         {
           *ttSizeAnnounce = (boolean) TRUE;
         }
       }
     }

     *addToQCurrentInstance = TRUE;
   }
}

IPDUM_STATIC FUNC(Std_ReturnType, IPDUM_CODE) IpduM_TT_LastIsBest_WithCntrQueuing
(
    PduIdType TxPduId
)
{
  const uint16 ContainedPduIndex = (uint16)TxPduId - (uint16)IpduM_ConfigPtr->TxPartLen;
  const uint16 ParentContainerIndex = IPDUM_CFG_GET_CNTD_TX(ContainedPduIndex)->IpduMContainerTxIndex;
  P2CONST(IpduM_ContainerTxPduType, AUTOMATIC, IPDUM_APPL_CONST) cntrPtr = IPDUM_CFG_GET_CNTR_TX(ParentContainerIndex);
  /* Deviation MISRAC2012-1 */
  P2VAR(IpduM_CntrTxDataType, AUTOMATIC, AUTOMATIC) cntrRamPtr = IPDUM_GET_CNTR_TXDATA(ParentContainerIndex);
  const PduLengthType ContainedPduLength = IPDUM_CFG_GET_CNTD_TX(ContainedPduIndex)->PduLength;
  /* Deviation MISRAC2012-1 */
  P2VAR(uint16, AUTOMATIC, AUTOMATIC) containerTxList = IPDUM_GET_TX_PDULIST(ParentContainerIndex);
  const IpduM_TxSendTimeoutType configuredContainedSendTimeout = IPDUM_CFG_GET_CNTD_TX(ContainedPduIndex)->IpduMContainedTxPduSendTimeout;

#if(IPDUM_DEV_ERROR_DETECT == STD_ON)
  /* Initialised with non-used value */
  BufReq_ReturnType bufRet = BUFREQ_E_BUSY;
#endif

  boolean sendTrigger = (boolean) FALSE;
  boolean sizeTrigger = (boolean) FALSE;
  boolean ttSizeAnnounce = (boolean) FALSE;
  boolean sizeAnnounceTrg = (boolean) FALSE;
  boolean addToQCurrentInstance = FALSE;

  Std_ReturnType RetVal;

  SchM_Enter_IpduM_SCHM_IPDUM_EXCLUSIVE_AREA_0();

  IpduM_LastIsBest_CntrAdd(ParentContainerIndex, ContainedPduIndex, &sendTrigger, &sizeTrigger);
  IpduM_UpdateCntrSendTimeout(configuredContainedSendTimeout, (P2CONST(uint16, AUTOMATIC, AUTOMATIC))containerTxList, &cntrRamPtr->SendTimeout);
  IpduM_CntrCheckSendTrigger(ParentContainerIndex, &sendTrigger);
  IpduM_LastIsBest_CntrCheckTriggers(ParentContainerIndex, ContainedPduIndex, (P2CONST(uint16, AUTOMATIC, AUTOMATIC))containerTxList, &sizeAnnounceTrg);

  IpduM_SetFlags_TT_LastIsBest_WithCntrQueuing(
    cntrRamPtr,
    &addToQCurrentInstance,
    &ttSizeAnnounce,
    ParentContainerIndex,
    sizeAnnounceTrg,
    sendTrigger
  );

  if(addToQCurrentInstance)
  {
#if(IPDUM_DEV_ERROR_DETECT == STD_ON)
    bufRet = IpduM_CntrQCntdListOnly(ParentContainerIndex);
#else
    (void)IpduM_CntrQCntdListOnly(ParentContainerIndex);
#endif
  }

  SchM_Exit_IpduM_SCHM_IPDUM_EXCLUSIVE_AREA_0();

#if(IPDUM_DEV_ERROR_DETECT == STD_ON)
  if(BUFREQ_E_OVFL == bufRet)
  {
    IPDUM_DET_REPORT_ERROR(IPDUM_SID_TRANSMIT, IPDUM_E_QUEUEOVFL);
  }
#endif

  if(ttSizeAnnounce)
  {
    PduInfoType pduInfo;
    pduInfo.SduDataPtr = NULL_PTR;
    pduInfo.SduLength = cntrPtr->PduLength;

    RetVal = PduR_IpduMTransmit(cntrPtr->IpduMContainerTxHandleId, &pduInfo);
  }

  SchM_Enter_IpduM_SCHM_IPDUM_EXCLUSIVE_AREA_0();

  if(ttSizeAnnounce)
  {
    if(sendTrigger)
    {
      if(E_NOT_OK == RetVal)
      {
        cntrRamPtr->QMFSizeAnnounceFlag = TRUE;
      }
    }
    else
    {
      if(E_OK == RetVal)
      {
        cntrRamPtr->AnnounceSize = (boolean) TRUE;
        cntrRamPtr->SendTimeout = 0U;
      }
    }
  }

  /*   if it was a size trigger, add the Contained which
       did not fit to a new instance */

  if((boolean)TRUE == sizeTrigger)
  {
    cntrRamPtr->SendTimeout = configuredContainedSendTimeout;

    IpduM_AddtoListGeneric(
#if ( (IPDUM_STATIC_CONTAINER_PDU_HANDLING_ENABLE == STD_ON) || (IPDUM_CONTAINEDTXPDU_PRIORITY_HANDLING_ENABLE == STD_ON) )
        cntrPtr,
#endif
        ContainedPduIndex,
        ParentContainerIndex,
        ContainedPduLength
    );

    sizeAnnounceTrg = FALSE;
    IpduM_LastIsBest_CntrCheckTriggers(ParentContainerIndex, ContainedPduIndex, (P2CONST(uint16, AUTOMATIC, AUTOMATIC))containerTxList, &sizeAnnounceTrg);
    if(sizeAnnounceTrg)
    {
      cntrRamPtr->ConfAwait = TRUE;
    }
  }

  SchM_Exit_IpduM_SCHM_IPDUM_EXCLUSIVE_AREA_0();

  return E_OK;
}
#endif

#if (IPDUM_CNTND_COLLECT_QUEUED_TX == STD_ON)
IPDUM_STATIC FUNC(Std_ReturnType, IPDUM_CODE) IpduM_TT_Queued_NoCntrQueuing
(
    PduIdType TxPduId,
    P2CONST(PduInfoType, AUTOMATIC, IPDUM_APPL_DATA) PduInfoPtr
)
{
  Std_ReturnType RetValue;

  const uint16 ContainedPduIndex = (uint16)TxPduId - (uint16)IpduM_ConfigPtr->TxPartLen;
  const uint16 ParentContainerIndex = IPDUM_CFG_GET_CNTD_TX(ContainedPduIndex)->IpduMContainerTxIndex;
  P2CONST(IpduM_ContainerTxPduType, AUTOMATIC, IPDUM_APPL_CONST) cntrPtr = IPDUM_CFG_GET_CNTR_TX(ParentContainerIndex);
  /* Deviation MISRAC2012-1 */
  P2VAR(IpduM_CntrTxDataType, AUTOMATIC, AUTOMATIC) cntrRamPtr = IPDUM_GET_CNTR_TXDATA(ParentContainerIndex);
  /* Deviation MISRAC2012-1 */
  P2VAR(uint16, AUTOMATIC, AUTOMATIC) containerTxList = IPDUM_GET_TX_PDULIST(ParentContainerIndex);
  const IpduM_TxSendTimeoutType configuredContainedSendTimeout = IPDUM_CFG_GET_CNTD_TX(ContainedPduIndex)->IpduMContainedTxPduSendTimeout;

  boolean sendTrigger = (boolean) FALSE;
  boolean sizeTrigger = (boolean) FALSE;
  boolean ttSizeAnnounce = (boolean) FALSE;
  boolean sizeAnnounceTrg = (boolean) FALSE;

  SchM_Enter_IpduM_SCHM_IPDUM_EXCLUSIVE_AREA_0();

  RetValue = (Std_ReturnType) E_OK;

  IpduM_Queued_CntrAdd(ParentContainerIndex, ContainedPduIndex, &sendTrigger, &sizeTrigger, PduInfoPtr);
  IpduM_UpdateCntrSendTimeout(configuredContainedSendTimeout, (P2CONST(uint16, AUTOMATIC, AUTOMATIC))containerTxList, &cntrRamPtr->SendTimeout);
  IpduM_CntrCheckSendTrigger(ParentContainerIndex, &sendTrigger);
  IpduM_Queued_CntrCheckTriggers(ParentContainerIndex, ContainedPduIndex, &sizeAnnounceTrg);

  if(sizeAnnounceTrg)
  {
    if(0U < cntrRamPtr->ConfirmTimeout)
    {
      if((boolean) FALSE == cntrRamPtr->AnnounceSize)
      {
        cntrRamPtr->ConfAwait = (boolean) TRUE;
        cntrRamPtr->AnnounceSize = (boolean) TRUE;
      }
    }
    else
    {
      if((boolean) FALSE == cntrRamPtr->AnnounceSize)
      {
        ttSizeAnnounce = (boolean) TRUE;
      }
    }
  }

  if((boolean)TRUE == sendTrigger)
  {
    if(0U < cntrRamPtr->ConfirmTimeout)
    {
      RetValue = (Std_ReturnType) E_NOT_OK;

      if((boolean) FALSE == cntrRamPtr->AnnounceSize)
      {
        cntrRamPtr->ConfAwait = (boolean) TRUE;
      }
    }
    else
    {
      if((boolean) FALSE == cntrRamPtr->AnnounceSize)
      {
        ttSizeAnnounce = (boolean) TRUE;
      }
    }
  }

  SchM_Exit_IpduM_SCHM_IPDUM_EXCLUSIVE_AREA_0();

  if(ttSizeAnnounce)
  {
    PduInfoType pduInfo;
    pduInfo.SduDataPtr = NULL_PTR;
    pduInfo.SduLength = cntrPtr->PduLength;

    RetValue = PduR_IpduMTransmit(cntrPtr->IpduMContainerTxHandleId, &pduInfo);

    if(sendTrigger)
    {
      if(E_NOT_OK == RetValue)
      {
        SchM_Enter_IpduM_SCHM_IPDUM_EXCLUSIVE_AREA_0();

        cntrRamPtr->ListSize = 0U;
        containerTxList[0U] = 0U;
        cntrRamPtr->AnnounceSize = (boolean) FALSE;

        SchM_Exit_IpduM_SCHM_IPDUM_EXCLUSIVE_AREA_0();
      }
    }
    else
    {
      if(E_OK == RetValue)
      {
        SchM_Enter_IpduM_SCHM_IPDUM_EXCLUSIVE_AREA_0();

        cntrRamPtr->AnnounceSize = (boolean) TRUE;
        cntrRamPtr->SendTimeout = 0U;

        SchM_Exit_IpduM_SCHM_IPDUM_EXCLUSIVE_AREA_0();
      }
    }
  }

  if(sizeTrigger)
  {
    RetValue = E_NOT_OK;
  }

   return RetValue;
}
#endif

#if (IPDUM_CNTND_COLLECT_QUEUED_TX == STD_ON)
#if (IPDUM_CONTAINER_QUEUING_TX == STD_ON)
IPDUM_STATIC FUNC(Std_ReturnType, IPDUM_CODE) IpduM_TT_Queued_WithCntrQueuing
(
  PduIdType TxPduId,
  P2CONST(PduInfoType, AUTOMATIC, IPDUM_APPL_DATA) PduInfoPtr
)
{
  const uint16 ContainedPduIndex = (uint16)TxPduId - (uint16)IpduM_ConfigPtr->TxPartLen;
  const uint16 ParentContainerIndex = IPDUM_CFG_GET_CNTD_TX(ContainedPduIndex)->IpduMContainerTxIndex;
  P2CONST(IpduM_ContainerTxPduType, AUTOMATIC, IPDUM_APPL_CONST) cntrPtr = IPDUM_CFG_GET_CNTR_TX(ParentContainerIndex);
  /* Deviation MISRAC2012-1 */
  P2VAR(IpduM_CntrTxDataType, AUTOMATIC, AUTOMATIC) cntrRamPtr = IPDUM_GET_CNTR_TXDATA(ParentContainerIndex);
  /* Deviation MISRAC2012-1 */
  P2VAR(uint16, AUTOMATIC, AUTOMATIC) containerTxList = IPDUM_GET_TX_PDULIST(ParentContainerIndex);
  const IpduM_TxSendTimeoutType configuredContainedSendTimeout = IPDUM_CFG_GET_CNTD_TX(ContainedPduIndex)->IpduMContainedTxPduSendTimeout;
  P2VAR(uint8, AUTOMATIC, AUTOMATIC) currentDataBuffer = IPDUM_GET_TX_CURRDATABUFF(ParentContainerIndex);

  PduLengthType length;

  boolean sendTrigger = (boolean) FALSE;
  boolean sizeTrigger = (boolean) FALSE;
  boolean ttSizeAnnounce = (boolean) FALSE;
  boolean sizeAnnounceTrg = (boolean) FALSE;
  boolean addToQCurrentInstance = FALSE;

  Std_ReturnType RetVal;

  SchM_Enter_IpduM_SCHM_IPDUM_EXCLUSIVE_AREA_0();

  IpduM_Queued_CntrAdd(ParentContainerIndex, ContainedPduIndex, &sendTrigger, &sizeTrigger, PduInfoPtr);
  IpduM_UpdateCntrSendTimeout(configuredContainedSendTimeout, (P2CONST(uint16, AUTOMATIC, AUTOMATIC))containerTxList, &cntrRamPtr->SendTimeout);
  IpduM_CntrCheckSendTrigger(ParentContainerIndex, &sendTrigger);
  IpduM_Queued_CntrCheckTriggers(ParentContainerIndex, ContainedPduIndex, &sizeAnnounceTrg);

  if(sizeAnnounceTrg)
  {
    if(0U == cntrRamPtr->ConfirmTimeout)
    {
      if((boolean) FALSE == cntrRamPtr->AnnounceSize)
      {
        if(IpduM_IsCntrQEmpty(ParentContainerIndex))
        {
          ttSizeAnnounce = (boolean) TRUE;
        }
      }
    }
    else
    {
      cntrRamPtr->AnnounceSize = (boolean) TRUE;
      cntrRamPtr->ConfAwait = TRUE;
    }
  }

  if((boolean)TRUE == sendTrigger)
  {
    if(0U == cntrRamPtr->ConfirmTimeout)
    {
      if(IpduM_IsCntrQEmpty(ParentContainerIndex))
      {
        if((boolean) FALSE == cntrRamPtr->AnnounceSize)
        {
          ttSizeAnnounce = (boolean) TRUE;
        }
      }
    }

    length = (PduLengthType)cntrRamPtr->ListSize;

    addToQCurrentInstance = TRUE;
    cntrRamPtr->SendTimeout = 0U;
  }

  if(addToQCurrentInstance)
  {
    IpduM_CntrQAdd(ParentContainerIndex, currentDataBuffer, length);
  }

  SchM_Exit_IpduM_SCHM_IPDUM_EXCLUSIVE_AREA_0();

  if(ttSizeAnnounce)
  {
    PduInfoType pduInfo;
    pduInfo.SduDataPtr = NULL_PTR;
    pduInfo.SduLength = cntrPtr->PduLength;

    RetVal = PduR_IpduMTransmit(cntrPtr->IpduMContainerTxHandleId, &pduInfo);
  }

  SchM_Enter_IpduM_SCHM_IPDUM_EXCLUSIVE_AREA_0();

  if(ttSizeAnnounce)
  {
    if(sendTrigger)
    {
      if(E_NOT_OK == RetVal)
      {
        cntrRamPtr->QMFSizeAnnounceFlag = TRUE;
      }
    }
    else
    {
      if(E_OK == RetVal)
      {
        cntrRamPtr->AnnounceSize = (boolean) TRUE;
        cntrRamPtr->SendTimeout = 0U;
      }
    }
  }

  /*   if it was a size trigger, add the Contained which
       did not fit to a new instance */

  if((boolean)TRUE == sizeTrigger)
  {
    cntrRamPtr->SendTimeout = configuredContainedSendTimeout;

    IpduM_DynamicPackDataOne(ContainedPduIndex, ParentContainerIndex, cntrRamPtr->ListSize, PduInfoPtr->SduLength, currentDataBuffer, PduInfoPtr->SduDataPtr);
    IpduM_AddtoList(ContainedPduIndex, ParentContainerIndex, PduInfoPtr->SduLength);

    sizeAnnounceTrg = FALSE;
    IpduM_Queued_CntrCheckTriggers(ParentContainerIndex, ContainedPduIndex, &sizeAnnounceTrg);
    if(sizeAnnounceTrg)
    {
      cntrRamPtr->ConfAwait = TRUE;
    }
  }

  SchM_Exit_IpduM_SCHM_IPDUM_EXCLUSIVE_AREA_0();

  return E_OK;
}
#endif
#endif

#endif /* IPDUM_CONTAINER_PDU_HANDLING == STD_ON */

#if ((IPDUM_CONTAINER_QUEUING_TX == STD_ON) || (IPDUM_CONTAINER_QUEUING_RX == STD_ON))
IPDUM_STATIC FUNC(BufReq_ReturnType, IPDUM_CODE) IpduM_CntrQPush
(
  P2VAR(IpduM_ContainerQueueType, AUTOMATIC, AUTOMATIC) qPtr,
  P2CONST(uint8, AUTOMATIC, AUTOMATIC) dataIn,
  P2VAR(uint8, AUTOMATIC, AUTOMATIC) dataOut,
  PduLengthType cntrPduLen,
  PduLengthType length,
  uint8 qSize
)
{
  const IpduM_DataOffsetType qBuffIdx = (IpduM_DataOffsetType)(qPtr->QPushIdx * (cntrPduLen + sizeof(PduLengthType)));
  BufReq_ReturnType ret;
  uint8 next_p;

  next_p = (((qPtr->QPushIdx) + 1U) % qSize);

  if(0U < qPtr->QFull)
  {
    ret = BUFREQ_E_OVFL;
    qPtr->QPopIdx = ((qPtr->QPopIdx + 1U) % qSize);
  }
  else if(next_p == qPtr->QPopIdx)
  {
    ret = BUFREQ_OK;
    qPtr->QFull = 1U;
  }
  else
  {
    ret = BUFREQ_OK;
  }

  TS_MemCpy(&dataOut[qBuffIdx], &length, sizeof(PduLengthType));
  TS_MemCpy(&dataOut[qBuffIdx + sizeof(PduLengthType)], dataIn, length);

  TS_AtomicAssign8(qPtr->QPushIdx, next_p);

  return ret;
}

#if (IPDUM_CONTAINER_QUEUING_TX == STD_ON)
IPDUM_STATIC FUNC(void, IPDUM_CODE) IpduM_CntrQAdd
(
  uint16 ParentContainerIndex,
  P2CONST(uint8, AUTOMATIC, IPDUM_APPL_DATA) currentDataBuffer,
  PduLengthType length
)
{
    P2CONST(IpduM_ContainerTxPduType, AUTOMATIC, IPDUM_APPL_CONST)  cntrPtr = IPDUM_CFG_GET_CNTR_TX(ParentContainerIndex);
    /* Deviation MISRAC2012-1 */
    P2VAR(uint32, AUTOMATIC, IPDUM_APPL_DATA) containerTxListSize = &IPDUM_GET_CNTR_TXDATA(ParentContainerIndex)->ListSize;
    /* Deviation MISRAC2012-1 */
    P2VAR(uint16, AUTOMATIC, AUTOMATIC) containerTxList = IPDUM_GET_TX_PDULIST(ParentContainerIndex);
    /* Deviation MISRAC2012-1 */
    P2VAR(uint16, AUTOMATIC, AUTOMATIC) containerConfTxList = IPDUM_GET_TX_CONFLIST(ParentContainerIndex);
#if (IPDUM_DEV_ERROR_DETECT == STD_ON)
    BufReq_ReturnType ret;

    /* queue the current instance */
    /* Deviation MISRAC2012-1 */
    ret = IPDUM_CNTRQ(PUSH, TX, ParentContainerIndex, currentDataBuffer, NULL_PTR, length);
#else
     /* Deviation MISRAC2012-1 */
    (void)IPDUM_CNTRQ(PUSH, TX, ParentContainerIndex, currentDataBuffer, NULL_PTR, length);
#endif
    {
      /* store Contained indexes for later confirmation */
      /* Deviation MISRAC2012-1 */
      P2VAR(IpduM_ContainerQueueType, AUTOMATIC, IPDUM_APPL_DATA) qPtr = IPDUM_GET_TX_QUEUE(ParentContainerIndex);
      const uint16 txConf_offset = (((boolean)TRUE == IPDUM_IS_QUEUED(cntrPtr->CfgFlags)) ? (uint16) qPtr->QPushIdx : 0U) * (uint16) cntrPtr->chunkSize;

      TS_MemCpy(&containerConfTxList[txConf_offset],
          &containerTxList[0U],
          sizeof(containerTxList[0U]) * ((uint32)containerTxList[0U] + 1U)
      );
    }

    /* clear list */
    *containerTxListSize = 0U;
    containerTxList[0U] = 0U;

#if (IPDUM_DEV_ERROR_DETECT == STD_ON)
    /*  */
    if(BUFREQ_E_OVFL == ret)
    {
      /* The function is called from a protected section.
       * Have to leave that for the DET. Handling it from the outside
       * would be more cumbersome.
       */
      SchM_Exit_IpduM_SCHM_IPDUM_EXCLUSIVE_AREA_0();
      IPDUM_DET_REPORT_ERROR(IPDUM_SID_TRANSMIT, IPDUM_E_QUEUEOVFL);
      SchM_Enter_IpduM_SCHM_IPDUM_EXCLUSIVE_AREA_0();
    }
#endif
}

IPDUM_STATIC FUNC(boolean, IPDUM_CODE) IpduM_IsCntrQEmpty
(
  uint16 index
)
{
  /* Deviation MISRAC2012-1 */
  P2VAR(IpduM_ContainerQueueType, AUTOMATIC, AUTOMATIC) qPtr = IPDUM_GET_TX_QUEUE(index);
  boolean retVal = (boolean) FALSE;

  if(0U == qPtr->QFull)
  {
    if(qPtr->QPushIdx == qPtr->QPopIdx)
    {
      retVal = (boolean) TRUE;
    }
  }

  return retVal;
}
#endif

IPDUM_STATIC FUNC(BufReq_ReturnType, IPDUM_CODE) IpduM_CntrQPop
(
  P2VAR(IpduM_ContainerQueueType, AUTOMATIC, AUTOMATIC) qPtr,
  P2VAR(PduLengthType, AUTOMATIC, AUTOMATIC) length,
  P2VAR(uint8, AUTOMATIC, AUTOMATIC) dataIn,
  P2VAR(uint8, AUTOMATIC, AUTOMATIC) dataOut,
  PduLengthType cntrPduLen,
  uint8 qSize
)
{
  const IpduM_DataOffsetType qBuffIdx = (IpduM_DataOffsetType)(qPtr->QPopIdx * (cntrPduLen + sizeof(PduLengthType)));
  BufReq_ReturnType ret;

  if ((qPtr->QPushIdx == qPtr->QPopIdx) && (0U == qPtr->QFull))
  {
    ret = BUFREQ_E_NOT_OK;
  }
  else
  {
    ret = BUFREQ_OK;
    qPtr->QFull = 0U;

    TS_MemCpy(length, &dataIn[qBuffIdx], sizeof(PduLengthType));
    TS_MemCpy(dataOut, &dataIn[qBuffIdx + sizeof(PduLengthType)], *length);

    qPtr->QPopIdx = ((qPtr->QPopIdx + 1U) % qSize);
  }

  return ret;
}

#endif /* (IPDUM_CONTAINER_QUEUING_TX == STD_ON) || (IPDUM_CONTAINER_QUEUING_RX == STD_ON) */

#if (IPDUM_CONTAINER_QUEUING_TX == STD_ON)

LOCAL_INLINE FUNC(void, IPDUM_CODE) IpduM_CntrQPeek
(
  P2VAR(IpduM_ContainerQueueType, AUTOMATIC, AUTOMATIC) qPtr,
  P2VAR(PduLengthType, AUTOMATIC, AUTOMATIC) length,
  P2VAR(uint8, AUTOMATIC, AUTOMATIC) dataIn,
  P2VAR(uint8, AUTOMATIC, AUTOMATIC) dataPtr,
  PduLengthType cntrPduLen
)
{
  IpduM_DataOffsetType qBuffIdx = (IpduM_DataOffsetType)(qPtr->QPopIdx * (cntrPduLen + sizeof(PduLengthType)));

  TS_MemCpy(length, &dataIn[qBuffIdx], sizeof(PduLengthType));
  TS_MemCpy(dataPtr, &dataIn[qBuffIdx + sizeof(PduLengthType)], *length);

}

IPDUM_STATIC FUNC(BufReq_ReturnType, IPDUM_CODE) IpduM_CntrQCntdListOnly
(
  uint16 ParentContainerIndex
)
{
  P2CONST(IpduM_ContainerTxPduType, AUTOMATIC, IPDUM_APPL_CONST) cntrPtr = IPDUM_CFG_GET_CNTR_TX(ParentContainerIndex);
  P2VAR(IpduM_ContainerQueueType, AUTOMATIC, IPDUM_APPL_DATA) qPtr = IPDUM_GET_TX_QUEUE(ParentContainerIndex);

  const uint8 next_p = (((qPtr->QPushIdx) + 1U) % cntrPtr->IpduMContainerQueueSize);
  const uint16 txConf_offset = (((boolean)TRUE == IPDUM_IS_QUEUED(cntrPtr->CfgFlags)) ? (uint16) qPtr->QPushIdx : 0U) * (uint16) cntrPtr->chunkSize;
#if(IPDUM_DEV_ERROR_DETECT == STD_ON)
  BufReq_ReturnType bufRet;
#endif
  qPtr->QPushIdx = next_p;

  if(0U < qPtr->QFull)
  {
#if(IPDUM_DEV_ERROR_DETECT == STD_ON)
    bufRet = BUFREQ_E_OVFL;
#endif
    qPtr->QPopIdx = ((qPtr->QPopIdx + 1U) % cntrPtr->IpduMContainerQueueSize);
  }
  else if(next_p == qPtr->QPopIdx)
  {
#if(IPDUM_DEV_ERROR_DETECT == STD_ON)
    bufRet = BUFREQ_OK;
#endif
    qPtr->QFull = 1U;
  }
  else
  {
#if(IPDUM_DEV_ERROR_DETECT == STD_ON)
    bufRet = BUFREQ_OK;
#endif
  }

  {
    P2VAR(uint16, AUTOMATIC, AUTOMATIC) containerTxList = IPDUM_GET_TX_PDULIST(ParentContainerIndex);
    P2VAR(uint16, AUTOMATIC, IPDUM_APPL_DATA) containerConfTxList = IPDUM_GET_TX_CONFLIST(ParentContainerIndex);
    P2VAR(IpduM_CntrTxDataType, AUTOMATIC, AUTOMATIC) cntrRamPtr = IPDUM_GET_CNTR_TXDATA(ParentContainerIndex);

    /* Store the Contained PDUs */
    TS_MemCpy(&containerConfTxList[txConf_offset],
              &containerTxList[0U],
              sizeof(containerTxList[0U]) * ((uint32)containerTxList[0U] + 1U)
             );

    containerTxList[0U] = 0U;
    cntrRamPtr->SendTimeout = 0U;
    cntrRamPtr->ListSize = 0U;
  }
#if(IPDUM_DEV_ERROR_DETECT == STD_ON)
  return bufRet;
#else
  return BUFREQ_OK;
#endif
}
#endif /* IPDUM_CONTAINER_QUEUING_TX == STD_ON */

#define IPDUM_STOP_SEC_CODE
#include <IpduM_MemMap.h>

/*==================[end of file]===========================================*/
