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
 * MISRAC2012-1) Deviated Rule: 20.10
 * The # and ## preprocessor operators should not be used.
 *
 * Reason:
 * This makes the code easier to maintain, while
 * supporting all needed combinations.
 */


#if (!defined IPDUM_INT_H)
#define IPDUM_INT_H

/*==================[inclusions]============================================*/
#include <IpduM_Cfg.h>
#include <IpduM_Types.h>

#if (IPDUM_DEV_ERROR_DETECT == STD_ON)
#include <Det.h>
#endif

#define TS_RELOCATABLE_CFG_ENABLE IPDUM_RELOCATABLE_CFG_ENABLE

#include <TSPBConfig_Access.h>    /* PB Macros */
/*==================[macros]================================================*/

/*------------------[AUTOSAR module identification]-------------------------*/

#if (defined IPDUM_INSTANCE_ID)
#error IPDUM_INSTANCE_ID already defined
#endif
/** \brief Id of instance of IpduM */
#define IPDUM_INSTANCE_ID  0U

/*------------------[macros for error codes]--------------------------------*/

#if (defined IPDUM_E_PARAM) /* to prevent double declaration */
#error IPDUM_E_PARAM already defined
#endif
/** \brief Development Error Code
 **
 ** API service called with wrong parameter.
 */
#define IPDUM_E_PARAM  0x10


#if (defined IPDUM_E_PARAM_POINTER ) /* to prevent double declaration */
#error IPDUM_E_PARAM_POINTER  already defined
#endif
/** \brief Development Error Code
 **
 ** API service called with a NULL pointer.
 */
#define IPDUM_E_PARAM_POINTER   0x11


#if (defined IPDUM_E_UNINIT) /* to prevent double declaration */
#error IPDUM_E_UNINIT already defined
#endif
/** \brief Development Error Code
 **
 ** API service used without module initialization.
 */
#define IPDUM_E_UNINIT  0x20

#if (defined IPDUM_E_HEADER) /* to prevent double declaration */
#error IPDUM_E_HEADER already defined
#endif
/** \brief Development Error Code
 **
 ** Erroneous header detected.
 */
#define IPDUM_E_HEADER  0x30

#if (defined IPDUM_E_QUEUEOVFL) /* to prevent double declaration */
#error IPDUM_E_QUEUEOVFL already defined
#endif
/** \brief Development Error Code
 **
 ** Container Queue overflow.
 */
#define IPDUM_E_QUEUEOVFL  0x31

#if (defined IPDUM_E_CONTAINER) /* to prevent double declaration */
#error IPDUM_E_CONTAINER already defined
#endif
/** \brief Development Error Code
 **
 ** Partly or erroneous container received.
 */
#define IPDUM_E_CONTAINER  0x32

/*------------------[macros for service IDs]--------------------------------*/

#if (defined IPDUM_SID_INIT)
#error IPDUM_SID_INIT already defined
#endif
/** \brief AUTOSAR API service ID.
 **
 ** Definition of service ID for IpduM_Init.
 */
#define IPDUM_SID_INIT  0x00U


#if (defined IPDUM_SID_GET_VERSION_INFO)
#error IPDUM_SID_GET_VERSION_INFO already defined
#endif
/** \brief AUTOSAR API service ID.
 **
 ** Definition of service ID for IpduM_GetVersionInfo.
 */
#define IPDUM_SID_GET_VERSION_INFO  0x01U


#if (defined IPDUM_SID_RX_INDICATION)
#error IPDUM_SID_RX_INDICATION already defined
#endif
/** \brief AUTOSAR API service ID.
 **
 ** Definition of service ID for IpduM_RxIndication.
 */
#define IPDUM_SID_RX_INDICATION  0x42U


#if (defined IPDUM_SID_TRANSMIT)
#error IPDUM_SID_TRANSMIT already defined
#endif
/** \brief AUTOSAR API service ID.
 **
 ** Definition of service ID for IpduM_Transmit.
 */
#define IPDUM_SID_TRANSMIT  0x03U


#if (defined IPDUM_SID_TX_CONFIRMATION)
#error IPDUM_SID_TX_CONFIRMATION already defined
#endif
/** \brief AUTOSAR API service ID.
 **
 ** Definition of service ID for IpduM_TxConfirmation.
 */
#define IPDUM_SID_TX_CONFIRMATION  0x40U


#if (defined IPDUM_SID_TRIGGER_TRANSMIT)
#error IPDUM_SID_TRIGGER_TRANSMIT already defined
#endif
/** \brief AUTOSAR API service ID.
 **
 ** Definition of service ID for IpduM_TriggerTransmit.
 */
#define IPDUM_SID_TRIGGER_TRANSMIT  0x41U


#if (defined IPDUM_SID_MAIN_FUNCTION_RX)
#error IPDUM_SID_MAIN_FUNCTION_RX already defined
#endif
/** \brief AUTOSAR API service ID.
 **
 ** Definition of service ID for IpduM_MainFunctionRx.
 */
#define IPDUM_SID_MAIN_FUNCTION_RX  0x11U


#if (defined IPDUM_SID_MAIN_FUNCTION_TX)
#error IPDUM_SID_MAIN_FUNCTION_TX already defined
#endif
/** \brief AUTOSAR API service ID.
 **
 ** Definition of service ID for IpduM_MainFunctionTx.
 */
#define IPDUM_SID_MAIN_FUNCTION_TX  0x12U


/*------------------[macros for Trigger Mode]-------------------------------*/
/* Trigger modes */
#if (defined IPDUM_TRIGGER_NONE)
#error IPDUM_TRIGGER_NONE already defined!
#endif /* #if (defined IPDUM_TRIGGER_NONE)*/
#define IPDUM_TRIGGER_NONE                 0U

#if (defined IPDUM_TRIGGER_STATIC)
#error IPDUM_TRIGGER_STATIC already defined!
#endif /* #if (defined IPDUM_TRIGGER_STATIC)*/
#define IPDUM_TRIGGER_STATIC               1U

#if (defined IPDUM_TRIGGER_DYNAMIC)
#error IPDUM_TRIGGER_DYNAMIC already defined!
#endif /* #if (defined IPDUM_TRIGGER_DYNAMIC)*/
#define IPDUM_TRIGGER_DYNAMIC              2U

#if (defined IPDUM_TRIGGER_STATIC_OR_DYNAMIC)
#error IPDUM_TRIGGER_STATIC_OR_DYNAMIC already defined!
#endif /* #if (defined IPDUM_TRIGGER_STATIC_OR_DYNAMIC)*/
#define IPDUM_TRIGGER_STATIC_OR_DYNAMIC    (IPDUM_TRIGGER_STATIC | IPDUM_TRIGGER_DYNAMIC)

/* Maximum trigger mode value */
#if (defined IPDUM_TRIGGER_MODE_MAX_VAL)
#error IPDUM_TRIGGER_MODE_MAX_VAL already defined!
#endif /* #if (defined IPDUM_TRIGGER_MODE_MAX_VAL)*/
#define IPDUM_TRIGGER_MODE_MAX_VAL         (IPDUM_TRIGGER_STATIC_OR_DYNAMIC)

/* Reserved for TxConfirmationId */
#if (defined IPDUM_RESERVED_PDUID)
#error IPDUM_RESERVED_PDUID already defined!
#endif /* #if (defined IPDUM_RESERVED_PDUID)*/
#define IPDUM_RESERVED_PDUID               ((PduIdType)0xFFFFU)

/* Definition of bit positions for member Flags of IpduM_ContainerRxPduType */
/* Bit position for IpduMContainerHeaderSize. It is set for IPDUM_HEADERTYPE_LONG, otherwise IPDUM_HEADERTYPE_SHORT is considered */
#if (defined IPDUM_HEADER_TYPE_POS)
#error IPDUM_HEADER_TYPE_POS already defined!
#endif /* #if (defined IPDUM_HEADER_TYPE_POS)*/
#define IPDUM_HEADER_TYPE_POS 0U

/* Bit position for IpduMContainerPduProcessing. It is set for PROCESSING_DEFERRED, otherwise PROCESSING_IMMEDIATE is considered */
#if (defined IPDUM_PDU_PROCESSING_POS)
#error IPDUM_PDU_PROCESSING_POS already defined!
#endif /* #if (defined IPDUM_PDU_PROCESSING_POS)*/
#define IPDUM_PDU_PROCESSING_POS 1U

/** \brief macro alias */
#if (defined IPDUM_LITTLE_ENDIAN)
#error IPDUM_LITTLE_ENDIAN already defined!
#endif /* #if (defined IPDUM_LITTLE_ENDIAN)*/
#define IPDUM_LITTLE_ENDIAN   LOW_BYTE_FIRST

#if (defined IPDUM_BIG_ENDIAN)
#error IPDUM_BIG_ENDIAN already defined!
#endif /* #if (defined IPDUM_BIG_ENDIAN)*/
#define IPDUM_BIG_ENDIAN      HIGH_BYTE_FIRST

/** \brief macro to enable overwriting of static declaration for testing  purpose */
#ifndef IPDUM_STATIC
#if (IPDUM_AUTOSAR_VERSION == 21)
#define IPDUM_STATIC _STATIC_
#else
#define IPDUM_STATIC STATIC
#endif /* if (IPDUM_AUTOSAR_VERSION == 21) */
#endif /* ifndef IPDUM_STATIC */

/** \brief calculate modulo 8 in byte array  */
#if (defined IPDUM_MODULO_8)
#error IPDUM_MODULO_8 already defined!
#endif /* #if (defined IPDUM_MODULO_8)*/
#define IPDUM_MODULO_8(i) ((i)&7U)

/** \brief pattern to select bits between startbit and endbit */
#if (defined IPDUM_SELECT_BITMASK)
#error IPDUM_SELECT_BITMASK already defined!
#endif /* #if (defined IPDUM_SELECT_BITMASK)*/
#define IPDUM_SELECT_BITMASK(startbit,stopbit) \
  ((uint8)((uint8)(1U<<((uint8)((stopbit)-(startbit))+1U))-1U))

/** \brief pattern to clear all bits between startbit and endbit */
#if (defined IPDUM_CLEAR_BITMASK)
#error IPDUM_CLEAR_BITMASK already defined!
#endif /* #if (defined IPDUM_CLEAR_BITMASK)*/
#define IPDUM_CLEAR_BITMASK(startbit,stopbit) \
  ((uint8)~((uint8)(IPDUM_SELECT_BITMASK(startbit,stopbit)<<IPDUM_MODULO_8(startbit))))

/** \brief macro to extract the selector field */
#if (defined IPDUM_GET_SELECTOR)
#error IPDUM_GET_SELECTOR already defined!
#endif /* #if (defined IPDUM_GET_SELECTOR)*/
#define IPDUM_GET_SELECTOR(src,startbit,stopbit) \
  ((uint8)((uint8)((src)[(startbit)>>3U]>>((IPDUM_MODULO_8(startbit))))&IPDUM_SELECT_BITMASK(startbit,stopbit)))

/** \brief macro to set the selector field */
#if (defined IPDUM_SET_SELECTOR)
#error IPDUM_SET_SELECTOR already defined!
#endif /* #if (defined IPDUM_SET_SELECTOR)*/
#define IPDUM_SET_SELECTOR(dst,value,startbit,stopbit) \
  ((dst)[(startbit)>>3U]=(uint8)((dst)[(startbit)>>3U]&IPDUM_CLEAR_BITMASK(startbit,stopbit))| \
  ((uint8)((value)<<(IPDUM_MODULO_8(startbit)))))

/** \brief macro to convert bit into byte offset */
#if (defined IPDUM_GET_BYTE_OFFSET)
#error IPDUM_GET_BYTE_OFFSET already defined!
#endif /* #if (defined IPDUM_GET_BYTE_OFFSET)*/
#define IPDUM_GET_BYTE_OFFSET(bitpos) \
  ((bitpos)>>3U)

/** \brief macro to convert size in bits to bytes */
#if (defined IPDUM_GET_BYTE_SIZE)
#error IPDUM_GET_BYTE_SIZE already defined!
#endif /* #if (defined IPDUM_GET_BYTE_SIZE)*/
#define IPDUM_GET_BYTE_SIZE(bitsize) \
  (((bitsize)+7U)>>3U)

/** \brief macro to convert size in bits to bytes */
#if (defined IPDUM_GET_MIN_SDU_LEN)
#error IPDUM_GET_MIN_SDU_LEN already defined!
#endif /* #if (defined IPDUM_GET_MIN_SDU_LEN)*/
#define IPDUM_GET_MIN_SDU_LEN(bitsize) \
  (((bitsize)>>3U)+1U)

/** \brief macro to copy bytewise */
#if (defined IPDUM_COPY)
#error IPDUM_COPY already defined!
#endif /* #if (defined IPDUM_COPY)*/
#define IPDUM_COPY(Dest, Src, Size) \
  do \
  { \
    uint8 ii; \
    for (ii=0U;ii<(Size);ii++) \
    { \
      (Dest)[ii] = (Src)[ii]; \
    } \
  } while(0U)

/** \brief maximum size of TX pathway array */
#if (defined IPDUM_TX_PATHWAY_LEN)
#error IPDUM_TX_PATHWAY_LEN already defined!
#endif /* #if (defined IPDUM_TX_PATHWAY_LEN)*/
#define IPDUM_TX_PATHWAY_LEN (IpduM_ConfigPtr->TxPathWayLen)

/** \brief maximum size of RX pathway array */
#if (defined IPDUM_RX_PATHWAY_LEN)
#error IPDUM_RX_PATHWAY_LEN already defined!
#endif /* #if (defined IPDUM_RX_PATHWAY_LEN)*/
#define IPDUM_RX_PATHWAY_LEN (IpduM_ConfigPtr->RxPathWayLen)

/** \brief maximum size of RX container array */
#if (defined IPDUM_RX_CONTAINER_LEN)
#error IPDUM_RX_CONTAINER_LEN already defined!
#endif /* #if (defined IPDUM_RX_CONTAINER_LEN)*/
#define IPDUM_RX_CONTAINER_LEN (IpduM_ConfigPtr->RxContainerPduNum)

/** \brief number of existing RX container PDUs with processing deferred */
#if (defined IPDUM_RX_CONTAINER_PROCESSING_DEFERRED_NO)
#error IPDUM_RX_CONTAINER_PROCESSING_DEFERRED_NO already defined!
#endif /* #if (defined IPDUM_RX_CONTAINER_PROCESSING_DEFERRED_NO)*/
#define IPDUM_RX_CONTAINER_PROCESSING_DEFERRED_NO (IpduM_ConfigPtr->RxContainerProcessingDeferredNum)

/** \brief mark dynamic PDU for sending */
#if (defined IPDUM_PRIO_NOT_READY_TO_SEND)
#error IPDUM_PRIO_NOT_READY_TO_SEND already defined!
#endif /* #if (defined IPDUM_PRIO_NOT_READY_TO_SEND)*/
#define IPDUM_PRIO_NOT_READY_TO_SEND ((uint16)0x100U)

/** \brief Lowest possible priority in the queue */
#if (defined IPDUM_PRIO_LOWEST_POSSIBLE)
#error IPDUM_PRIO_LOWEST_POSSIBLE already defined!
#endif /* #if (defined IPDUM_PRIO_LOWEST_POSSIBLE)*/
#define IPDUM_PRIO_LOWEST_POSSIBLE ((uint16)0xFFFFU)

/** \brief reserved value for IpduM_TxTimeoutType to indicate that a call to
 * PduR_IpduMTransmit() has not yet completed */
#if (defined IPDUM_TRANSMIT_ONGOING)
#error IPDUM_TRANSMIT_ONGOING already defined!
#endif /* #if (defined IPDUM_TRANSMIT_ONGOING)*/
#define IPDUM_TRANSMIT_ONGOING 0xFFFFU

/** \brief reserved value for IpduM_TxTimeoutType to indicate that a call to
 * PduR_IpduMTransmit() has not yet completed but the sending of the PDU is
 * already confirmed */
#if (defined IPDUM_TRANSMIT_ONGOING_CONFIRMED)
#error IPDUM_TRANSMIT_ONGOING_CONFIRMED already defined!
#endif /* #if (defined IPDUM_TRANSMIT_ONGOING_CONFIRMED)*/
#define IPDUM_TRANSMIT_ONGOING_CONFIRMED (IPDUM_TRANSMIT_ONGOING - 1U)

/** \brief macro to get Container PDU header type: short (0) or long (1)
 *  - bit 0 from Flags */
#if (defined IPDUM_GET_HEADER_TYPE)
#error IPDUM_GET_HEADER_TYPE already defined!
#endif /* #if (defined IPDUM_GET_HEADER_TYPE)*/
#define IPDUM_GET_HEADER_TYPE(Flags) ((uint8)((Flags) & 0x01U))

/** \brief macro to get Container PDU processing type: immediate (0) or deferred (2)
 *  - bit 1 from Flags */
#if (defined IPDUM_GET_PROCESSING_TYPE)
#error IPDUM_GET_PROCESSING_TYPE already defined!
#endif /* #if (defined IPDUM_GET_PROCESSING_TYPE)*/
#define IPDUM_GET_PROCESSING_TYPE(Flags) ((uint8)((Flags) & 0x02U))

/** \brief Container PDU none header size in bytes */
#if (defined IPDUM_HEADERTYPE_NONE)
#error IPDUM_HEADERTYPE_NONE already defined!
#endif /* #if (defined IPDUM_HEADERTYPE_NONE)*/
#define IPDUM_HEADERTYPE_NONE  (PduLengthType)0U

/** \brief Container PDU short header size in bytes */
#if (defined IPDUM_HEADERTYPE_SHORT)
#error IPDUM_HEADERTYPE_SHORT already defined!
#endif /* #if (defined IPDUM_HEADERTYPE_SHORT)*/
#define IPDUM_HEADERTYPE_SHORT  (PduLengthType)4U

/** \brief Container PDU long header size in bytes */
#if (defined IPDUM_HEADERTYPE_LONG)
#error IPDUM_HEADERTYPE_LONG already defined!
#endif /* #if (defined IPDUM_HEADERTYPE_LONG)*/
#define IPDUM_HEADERTYPE_LONG  (PduLengthType)8U

/** \brief macro to get the data length code from short header */
#if (defined IPDUM_GET_DLC_OF_SHORT_HEADER)
#error IPDUM_GET_DLC_OF_SHORT_HEADER already defined!
#endif /* #if (defined IPDUM_GET_DLC_OF_SHORT_HEADER)*/
#define IPDUM_GET_DLC_OF_SHORT_HEADER(Src, Idx) ((Src)[(Idx) + 3U])

/** \brief macro to check if ContainerTxPdu is TriggerFirst */
#if (defined IPDUM_IS_TRGGR_FIRST)
#error IPDUM_IS_TRGGR_FIRST already defined!
#endif /* #if (defined IPDUM_IS_TRGGR_FIRST)*/
#define IPDUM_IS_TRGGR_FIRST(cfgFlag) (boolean)((((cfgFlag) & 0x02U) != 0U)?TRUE:FALSE)

/** \brief macro to check if TriggerMode is DIRECT */
#if (defined IPDUM_IS_TXMODE_DIRECT)
#error IPDUM_IS_TXMODE_DIRECT already defined!
#endif /* #if (defined IPDUM_IS_TXMODE_DIRECT)*/
#define IPDUM_IS_TXMODE_DIRECT(cfgFlag) (boolean)((((cfgFlag) & 0x04U) != 0U)?TRUE:FALSE)

/** \brief macro to check if Container Pdu is QUEUING */
#if (defined IPDUM_IS_QUEUED)
#error IPDUM_IS_QUEUED already defined!
#endif /* #if (defined IPDUM_IS_QUEUED)*/
#define IPDUM_IS_QUEUED(cfgFlag) (boolean)((((cfgFlag) & 0x08U) != 0U)?TRUE:FALSE)

/** \brief macro to check if the ContainedTxPdu has TxConfirmation enabled */
#if (defined IPDUM_IS_CNTND_TXCONF)
#error IPDUM_IS_CNTND_TXCONF already defined!
#endif /* #if (defined IPDUM_IS_CNTND_TXCONF)*/
#define IPDUM_IS_CNTND_TXCONF(cfgFlag) (boolean)((((cfgFlag) & 0x01U) != 0U)?TRUE:FALSE)

/** \brief macro to check if the ContainerTxPdu has LAST_IS_BEST Coll. Semantics */
#if (defined IPDUM_IS_CNTR_LAST_IS_BEST)
#error IPDUM_IS_CNTR_LAST_IS_BEST already defined!
#endif /* #if (defined IPDUM_IS_CNTR_LAST_IS_BEST)*/
#define IPDUM_IS_CNTR_LAST_IS_BEST(cfgFlag) (boolean)((((cfgFlag) & 0x10U) != 0U)?TRUE:FALSE)

/** \brief macro to check if the ContainedTxPdu has Always as Trigger */
#if (defined IPDUM_IS_CNTND_TRGGR_ALWAYS)
#error IPDUM_IS_CNTND_TRGGR_ALWAYS already defined!
#endif /* #if (defined IPDUM_IS_CNTND_TRGGR_ALWAYS)*/
#define IPDUM_IS_CNTND_TRGGR_ALWAYS(cfgFlag) (boolean)((((cfgFlag) & 0x02U) != 0U)?TRUE:FALSE)

#define IPDUM_SWAP_U32(val) (((uint32)(val)                >> 24U) | \
                            (((uint32)(val) & 0x00FF0000U) >>  8U) | \
                            (((uint32)(val) & 0x0000FF00U) <<  8U) | \
                             ((uint32)(val)                << 24U))

#if (defined IPDUM_SWAPU32_IF_MUST)
#error IPDUM_SWAPU32_IF_MUST already defined!
#endif /* #if (defined IPDUM_SWAPU32_IF_MUST)*/
#if(IPDUM_HEADER_BYTE_ORDER == CPU_BYTE_ORDER)
  #define IPDUM_SWAPU32_IF_MUST(val)  (val)
#else
  #define IPDUM_SWAPU32_IF_MUST(val)  (IPDUM_SWAP_U32(val))
#endif

#if (defined IPDUM_CNTRTX_HAS_UPDATE_BITS)
#error IPDUM_CNTRTX_HAS_UPDATE_BITS already defined!
#endif /* #if (defined IPDUM_CNTRTX_HAS_UPDATE_BITS)*/
#define IPDUM_CNTRTX_HAS_UPDATE_BITS(cfgFlag)  (boolean)((((cfgFlag) & 0x20U) != 0U)?TRUE:FALSE)

#if (defined IPDUM_CNTRTX_HAS_PRIORITY)
#error IPDUM_CNTRTX_HAS_PRIORITY already defined!
#endif /* #if (defined IPDUM_CNTRTX_HAS_PRIORITY)*/
#define IPDUM_CNTRTX_HAS_PRIORITY(cfgFlag)  (boolean)((((cfgFlag) & 0x40U) != 0U)?TRUE:FALSE)

#if (defined IPDUM_SHORT_HDR_DLC_OFFST)
#error IPDUM_SHORT_HDR_DLC_OFFST already defined!
#endif /* #if (defined IPDUM_SHORT_HDR_DLC_OFFST)*/
#define IPDUM_SHORT_HDR_DLC_OFFST   3U

/** \brief Offset in bytes for first TxData element in IpduM_DataMem */
#if (defined IPDUM_TX_DATA_OFFSET)
#error IPDUM_TX_DATA_OFFSET already defined!
#endif /* #if (defined IPDUM_TX_DATA_OFFSET)*/
#define IPDUM_TX_DATA_OFFSET  ((uint16)0x0000U)

/* Config data access macros */

#if (defined IPDUM_PBCFG_ACCESS_PTR)
#error IPDUM_PBCFG_ACCESS_PTR already defined!
#endif /* #if (defined IPDUM_PBCFG_ACCESS_PTR)*/
#define IPDUM_PBCFG_ACCESS_PTR(ptr, type, element) \
    (TS_UNCHECKEDGETCFG(ptr, type, IPDUM, ptr->element))

#if (defined IPDUM_PBCFG_ACCESS)
#error IPDUM_PBCFG_ACCESS already defined!
#endif /* #if (defined IPDUM_PBCFG_ACCESS)*/
#define IPDUM_PBCFG_ACCESS(type, element) \
    (TS_UNCHECKEDGETCFG(IpduM_ConfigPtr, type, IPDUM, element))

#if (defined IPDUM_CFG_GET_MFTXLOOKUP) /* to prevent double declaration */
#error IPDUM_CFG_GET_MFTXLOOKUP already defined
#endif /* if (defined IPDUM_CFG_GET_MFTXLOOKUP) */
#define IPDUM_CFG_GET_MFTXLOOKUP(Index)   \
    (&IPDUM_PBCFG_ACCESS(PduIdType, IpduM_ConfigPtr->MFTxLookup)[(Index)])

#if (defined IPDUM_CFG_GET_MFRXLOOKUP) /* to prevent double declaration */
#error IPDUM_CFG_GET_MFRXLOOKUP already defined
#endif /* if (defined IPDUM_CFG_GET_MFRXLOOKUP) */
#define IPDUM_CFG_GET_MFRXLOOKUP(Index)   \
    (&IPDUM_PBCFG_ACCESS(PduIdType, IpduM_ConfigPtr->MFRxLookup)[(Index)])

#if (defined IPDUM_CFG_GET_RXMFLOOKUP) /* to prevent double declaration */
#error IPDUM_CFG_GET_RXMFLOOKUP already defined
#endif /* if (defined IPDUM_CFG_GET_RXMFLOOKUP) */
#define IPDUM_CFG_GET_RXMFLOOKUP(Index)   \
    (&IPDUM_PBCFG_ACCESS(PduIdType, IpduM_ConfigPtr->RxMFLookup)[(Index)])

#if (defined IPDUM_CFG_GET_RX_IDXS) /* to prevent double declaration */
#error IPDUM_CFG_GET_RX_IDXS already defined
#endif /* if (defined IPDUM_CFG_GET_RX_IDXS) */
#define IPDUM_CFG_GET_RX_IDXS(Index)   \
    (IPDUM_PBCFG_ACCESS(uint8, IpduM_ConfigPtr->RxHandlerIndices)[(Index)])

#if (defined IPDUM_CFG_GET_RX_PATHWAY) /* to prevent double declaration */
#error IPDUM_CFG_GET_RX_PATHWAY already defined
#endif /* if (defined IPDUM_CFG_GET_RX_PATHWAY) */
#define IPDUM_CFG_GET_RX_PATHWAY(Index)   \
    (&IPDUM_PBCFG_ACCESS(IpduM_RxPathWayType, IpduM_ConfigPtr->RxPathWay)[(Index)])

#if (defined IPDUM_CFG_GET_TX_PATHWAY) /* to prevent double declaration */
#error IPDUM_CFG_GET_TX_PATHWAY already defined
#endif /* if (defined IPDUM_CFG_GET_TX_PATHWAY) */
#define IPDUM_CFG_GET_TX_PATHWAY(Index)   \
    (&IPDUM_PBCFG_ACCESS(IpduM_TxPathWayType, IpduM_ConfigPtr->TxPathWay)[(Index)])

#if (defined IPDUM_CFG_GET_TX_PART) /* to prevent double declaration */
#error IPDUM_CFG_GET_TX_PART already defined
#endif /* if (defined IPDUM_CFG_GET_TX_PART) */
#define IPDUM_CFG_GET_TX_PART(Index)   \
    (&IPDUM_PBCFG_ACCESS(IpduM_TxPartType, IpduM_ConfigPtr->TxPart)[(Index)])

#if (defined IPDUM_CFG_GET_CNTR_RX) /* to prevent double declaration */
#error IPDUM_CFG_GET_CNTR_RX already defined
#endif /* if (defined IPDUM_CFG_GET_CNTR_RX) */
#define IPDUM_CFG_GET_CNTR_RX(Index)   \
    (&IPDUM_PBCFG_ACCESS(IpduM_ContainerRxPduType, IpduM_ConfigPtr->ContainerRxPdu)[(Index)])

#if (defined IPDUM_CFG_GET_CNTD_RX) /* to prevent double declaration */
#error IPDUM_CFG_GET_CNTD_RX already defined
#endif /* if (defined IPDUM_CFG_GET_CNTD_RX) */
#define IPDUM_CFG_GET_CNTD_RX(Index)   \
    (&IPDUM_PBCFG_ACCESS(IpduM_ContainedRxPduType, IpduM_ConfigPtr->ContainedRxPdu)[(Index)])

#if (defined IPDUM_CFG_GET_CNTD_RX_ACCEPTALL) /* to prevent double declaration */
#error IPDUM_CFG_GET_CNTD_RX_ACCEPTALL already defined
#endif /* if (defined IPDUM_CFG_GET_CNTD_RX_ACCEPTALL) */
#define IPDUM_CFG_GET_CNTD_RX_ACCEPTALL(Index)   \
    (&IPDUM_PBCFG_ACCESS(IpduM_ContainedRxPduType, IpduM_ConfigPtr->ContainedRxPduAcceptAll)[(Index)])

#if (defined IPDUM_CFG_GET_STATIC_CNTD_RX) /* to prevent double declaration */
#error IPDUM_CFG_GET_STATIC_CNTD_RX already defined
#endif /* if (defined IPDUM_CFG_GET_STATIC_CNTD_RX) */
#define IPDUM_CFG_GET_STATIC_CNTD_RX(Index)   \
    (&IPDUM_PBCFG_ACCESS(IpduM_StaticContainedRxPduType, IpduM_ConfigPtr->StaticContainedRxPdu)[(Index)])
    
#if (defined IPDUM_CFG_GET_CNTR_TX) /* to prevent double declaration */
#error IPDUM_CFG_GET_CNTR_TX already defined
#endif /* if (defined IPDUM_CFG_GET_CNTR_TX) */
#define IPDUM_CFG_GET_CNTR_TX(Index)   \
    (&IPDUM_PBCFG_ACCESS(IpduM_ContainerTxPduType, IpduM_ConfigPtr->ContainerTxPdu)[(Index)])

#if (defined IPDUM_CFG_GET_CNTD_TX) /* to prevent double declaration */
#error IPDUM_CFG_GET_CNTD_TX already defined
#endif /* if (defined IPDUM_CFG_GET_CNTD_TX) */
#define IPDUM_CFG_GET_CNTD_TX(Index)   \
    (&IPDUM_PBCFG_ACCESS(IpduM_ContainedTxPduType, IpduM_ConfigPtr->ContainedTxPdu)[(Index)])

/** \brief used for the retrieval and execution of internal RxInd function */
#if (defined IPDUM_GET_RXIND_HANDLER)
#error IPDUM_GET_RXIND_HANDLER already defined!
#endif /* #if (defined IPDUM_GET_RXIND_HANDLER)*/
#define IPDUM_RXIND_HANDLER(id, ptr) IpduM_RxHandlers[IPDUM_CFG_GET_RX_IDXS(id)]((((id) < IPDUM_RX_PATHWAY_LEN) ? (id) : ((id) - IPDUM_RX_PATHWAY_LEN)) ,(ptr))

#if (defined IPDUM_CFG_GET_RX_DYNAMIC_PART) /* to prevent double declaration */
#error IPDUM_CFG_GET_RX_DYNAMIC_PART already defined
#endif /* if (defined IPDUM_CFG_GET_RX_DYNAMIC_PART) */
#define IPDUM_CFG_GET_RX_DYNAMIC_PART(ptr, Index)   \
    (&IPDUM_PBCFG_ACCESS(IpduM_RxPartType, ptr->DynamicPart)[(Index)])

#if (defined IPDUM_CFG_GET_RX_STATIC_PART) /* to prevent double declaration */
#error IPDUM_CFG_GET_RX_STATIC_PART already defined
#endif /* if (defined IPDUM_CFG_GET_RX_STATIC_PART) */
#define IPDUM_CFG_GET_RX_STATIC_PART(ptr)   \
    (IPDUM_PBCFG_ACCESS(IpduM_RxPartType, ptr->StaticPart))

#if (defined IPDUM_CFG_GET_TX_COPY_BITFIELD) /* to prevent double declaration */
#error IPDUM_CFG_GET_TX_COPY_BITFIELD already defined
#endif /* if (defined IPDUM_CFG_GET_TX_COPY_BITFIELD) */
#define IPDUM_CFG_GET_TX_COPY_BITFIELD(ptr)   \
    (IPDUM_PBCFG_ACCESS(IpduM_CopyBitFieldType, ptr->CopyBitField))

#if (defined IPDUM_CFG_GET_RX_COPY_BITFIELD) /* to prevent double declaration */
#error IPDUM_CFG_GET_RX_COPY_BITFIELD already defined
#endif /* if (defined IPDUM_CFG_GET_RX_COPY_BITFIELD) */
#define IPDUM_CFG_GET_RX_COPY_BITFIELD(ptr)   \
    (IPDUM_PBCFG_ACCESS(IpduM_CopyBitFieldType, ptr->CopyBitField))

/** \brief Offset in bytes for ContainerRxPdu related data in IpduM_DataMem */
#if (defined IPDUM_RX_DATA_CNTR_OFFSET)
#error IPDUM_RX_DATA_CNTR_OFFSET already defined!
#endif /* #if (defined IPDUM_RX_DATA_CNTR_OFFSET)*/
#define IPDUM_RX_DATA_CNTR_OFFSET  (IpduM_ConfigPtr->RxCntrOffset)

/** \brief Offset in bytes for ContainerTxPdu related data in IpduM_DataMem */
#if (defined IPDUM_TX_DATA_CNTR_OFFSET)
#error IPDUM_TX_DATA_CNTR_OFFSET already defined!
#endif /* #if (defined IPDUM_TX_DATA_CNTR_OFFSET)*/
#define IPDUM_TX_DATA_CNTR_OFFSET  (IpduM_ConfigPtr->TxCntrOffset)

#if (defined IPDUM_NULL_PTR_CHECK)
#error IPDUM_NULL_PTR_CHECK already defined!
#endif /* #if (defined IPDUM_NULL_PTR_CHECK) */

#if (IPDUM_RELOCATABLE_CFG_ENABLE == STD_ON)
#define IPDUM_NULL_PTR_CHECK(x) ((x) == 0U? TRUE: FALSE)
#else
#define IPDUM_NULL_PTR_CHECK(x) ((x) == NULL_PTR? TRUE: FALSE) 
#endif

#if (defined IPDUM_GET_DEFERRED_LIST)
#error IPDUM_GET_DEFERRED_LIST already defined!
#endif /* #if (defined IPDUM_GET_DEFERRED_LIST) */
#if(IPDUM_DEDICATED_IPDU_PROCESSING_SUPPORT == STD_OFF)
#define IPDUM_GET_DEFERRED_LIST(mfIdx)  (P2VAR(uint32, AUTOMATIC, IPDUM_VAR_NOINIT))&IpduM_GDataMemPtr[IPDUM_RX_DATA_CNTR_OFFSET]
#else
#define IPDUM_GET_DEFERRED_LIST(mfIdx)  (P2VAR(uint32, AUTOMATIC, IPDUM_VAR_NOINIT))&IpduM_GDataMemPtr[(IPDUM_RX_DATA_CNTR_OFFSET + (sizeof(uint32)* (*IPDUM_CFG_GET_MFRXLOOKUP(mfIdx))))]
#endif

#if (defined IPDUM_GET_DEFERRED_DATA)
#error IPDUM_GET_DEFERRED_DATA already defined!
#endif /* #if (defined IPDUM_GET_DEFERRED_DATA) */
#define IPDUM_GET_DEFERRED_DATA(idx)  (P2VAR(uint8, AUTOMATIC, IPDUM_VAR_NOINIT))&IpduM_GDataMemPtr[IPDUM_PBCFG_ACCESS(IpduM_ContainerRxPduType,IpduM_ConfigPtr->ContainerRxPdu)[(idx)].BuffOffset]

#if (defined IPDUM_GET_RX_QUEUE)
#error IPDUM_GET_RX_QUEUE already defined!
#endif /* #if (defined IPDUM_GET_RX_QUEUE) */
#define IPDUM_GET_RX_QUEUE(idx)  (P2VAR(IpduM_ContainerQueueType, AUTOMATIC, IPDUM_VAR_NOINIT))&IpduM_GDataMemPtr[IPDUM_PBCFG_ACCESS(IpduM_ContainerRxPduType,IpduM_ConfigPtr->ContainerRxPdu)[(idx)].QueueBuffOffset]

#if (defined IPDUM_GET_CNTR_TXDATA)
#error IPDUM_GET_CNTR_TXDATA already defined!
#endif /* #if (defined IPDUM_GET_CNTR_TXDATA) */
#define IPDUM_GET_CNTR_TXDATA(idx)  ((P2VAR(IpduM_CntrTxDataType, AUTOMATIC, IPDUM_VAR_NOINIT))&IpduM_GDataMemPtr[(IPDUM_TX_DATA_CNTR_OFFSET + ((idx) * sizeof(IpduM_CntrTxDataType)))])

#if (defined IPDUM_GET_TX_PDULIST)
#error IPDUM_GET_TX_PDULIST already defined!
#endif /* #if (defined IPDUM_GET_TX_PDULIST) */
#define IPDUM_GET_TX_PDULIST(idx)  (P2VAR(uint16, AUTOMATIC, IPDUM_VAR_NOINIT))&IpduM_GDataMemPtr[IPDUM_PBCFG_ACCESS(IpduM_ContainerTxPduType,IpduM_ConfigPtr->ContainerTxPdu)[(idx)].PdusListOffset]

#if (defined IPDUM_GET_TX_CONFLIST)
#error IPDUM_GET_TX_CONFLIST already defined!
#endif /* #if (defined IPDUM_GET_TX_CONFLIST) */
#define IPDUM_GET_TX_CONFLIST(idx)  (P2VAR(uint16, AUTOMATIC, IPDUM_VAR_NOINIT))&IpduM_GDataMemPtr[IPDUM_PBCFG_ACCESS(IpduM_ContainerTxPduType,IpduM_ConfigPtr->ContainerTxPdu)[(idx)].ConfirmListOffset]

#if (defined IPDUM_GET_TX_CURRDATABUFF)
#error IPDUM_GET_TX_CURRDATABUFF already defined!
#endif /* #if (defined IPDUM_GET_TX_CURRDATABUFF) */
#define IPDUM_GET_TX_CURRDATABUFF(idx)  (P2VAR(uint8, AUTOMATIC, IPDUM_VAR_NOINIT))&IpduM_GDataMemPtr[IPDUM_PBCFG_ACCESS(IpduM_ContainerTxPduType,IpduM_ConfigPtr->ContainerTxPdu)[(idx)].CurrentDataOffset]

#if (defined IPDUM_GET_TX_QUEUE)
#error IPDUM_GET_TX_QUEUE already defined!
#endif /* #if (defined IPDUM_GET_TX_QUEUE) */
#define IPDUM_GET_TX_QUEUE(idx)  (P2VAR(IpduM_ContainerQueueType, AUTOMATIC, IPDUM_VAR_NOINIT))&IpduM_GDataMemPtr[IPDUM_PBCFG_ACCESS(IpduM_ContainerTxPduType,IpduM_ConfigPtr->ContainerTxPdu)[(idx)].QueueBuffOffset]

#if (defined IPDUM_GET_TX_QDATABUFF)
#error IPDUM_GET_TX_QDATABUFF already defined!
#endif /* #if (defined IPDUM_GET_TX_QDATABUFF) */
#define IPDUM_GET_TX_QDATABUFF(idx)  (P2VAR(uint8, AUTOMATIC, IPDUM_VAR_NOINIT))&IpduM_GDataMemPtr[IPDUM_PBCFG_ACCESS(IpduM_ContainerTxPduType,IpduM_ConfigPtr->ContainerTxPdu)[(idx)].BuffOffset]

#if (defined IPDUM_GET_TX_CNTD_DATABUFF)
#error IPDUM_GET_TX_CNTD_DATABUFF already defined!
#endif /* #if (defined IPDUM_GET_TX_CNTD_DATABUFF) */
#define IPDUM_GET_TX_CNTD_DATABUFF(idx)  (P2VAR(uint8, AUTOMATIC, IPDUM_VAR_NOINIT))&IpduM_GDataMemPtr[IPDUM_PBCFG_ACCESS(IpduM_ContainedTxPduType,IpduM_ConfigPtr->ContainedTxPdu)[(idx)].BuffOffset]

/** \brief This is the macro meant to be used throughout the code */
#if (defined IPDUM_CNTRQ)
#error IPDUM_CNTRQ already defined!
#endif /* #if (defined IPDUM_CNTRQ) */
/* Deviation MISRAC2012-1 */
#define IPDUM_CNTRQ(OPERATION, DIRECTION, ContainerIdx, inPtr, outPtr, length) IPDUM_CNTRQ##OPERATION(DIRECTION, (ContainerIdx), (length), (inPtr), (outPtr))

#if (defined IPDUM_CNTRQPUSH)
#error IPDUM_CNTRQPUSH already defined!
#endif /* #if (defined IPDUM_CNTRQPUSH) */
/* Deviation MISRAC2012-1 */
#define IPDUM_CNTRQPUSH(DIRECTION, ContainerIdx, length, inPtr, outPtr) IPDUM_CNTRQPUSH_##DIRECTION((ContainerIdx), (length), (inPtr))

#if (defined IPDUM_CNTRQPUSH_RX)
#error IPDUM_CNTRQPUSH_RX already defined!
#endif /* #if (defined IPDUM_CNTRQPUSH_RX) */
#define IPDUM_CNTRQPUSH_RX(ContainerIdx, length, inPtr) IpduM_CntrQPush(IPDUM_GET_RX_QUEUE((ContainerIdx)), (inPtr), (IPDUM_GET_DEFERRED_DATA((ContainerRxIndex))), (IPDUM_PBCFG_ACCESS(IpduM_ContainerRxPduType,IpduM_ConfigPtr->ContainerRxPdu)[(ContainerIdx)].PduLength), (length), (IPDUM_PBCFG_ACCESS(IpduM_ContainerRxPduType,IpduM_ConfigPtr->ContainerRxPdu)[(ContainerIdx)].ContainerQueueSize))

#if (defined IPDUM_CNTRQPUSH_TX)
#error IPDUM_CNTRQPUSH_TX already defined!
#endif /* #if (defined IPDUM_CNTRQPUSH_TX) */
#define IPDUM_CNTRQPUSH_TX(ContainerIdx, length, inPtr) IpduM_CntrQPush(IPDUM_GET_TX_QUEUE((ContainerIdx)), (inPtr), IPDUM_GET_TX_QDATABUFF((ContainerIdx)), (IPDUM_CFG_GET_CNTR_TX(ContainerIdx)->PduLength), (length), (IPDUM_CFG_GET_CNTR_TX(ContainerIdx)->IpduMContainerQueueSize))

#if (defined IPDUM_CNTRQPEEK)
#error IPDUM_CNTRQPEEK already defined!
#endif /* #if (defined IPDUM_CNTRQPEEK) */
/* Deviation MISRAC2012-1 */
#define IPDUM_CNTRQPEEK(DIRECTION, ContainerIdx, length, inPtr, outPtr) IPDUM_CNTRQPEEK_##DIRECTION((ContainerIdx), (length), (outPtr))

#if (defined IPDUM_CNTRQPEEK_RX)
#error IPDUM_CNTRQPEEK_RX already defined!
#endif /* #if (defined IPDUM_CNTRQPEEK_RX) */
#define IPDUM_CNTRQPEEK_RX(ContainerIdx, length, outPtr) IpduM_CntrQPeek(IPDUM_GET_RX_QUEUE((ContainerIdx)), (length), (IPDUM_GET_DEFERRED_DATA((ContainerRxIndex))), (outPtr), (IPDUM_PBCFG_ACCESS(IpduM_ContainerRxPduType,IpduM_ConfigPtr->ContainerRxPdu)[(ContainerIdx)].PduLength))

#if (defined IPDUM_CNTRQPEEK_TX)
#error IPDUM_CNTRQPEEK_TX already defined!
#endif /* #if (defined IPDUM_CNTRQPEEK_TX) */
#define IPDUM_CNTRQPEEK_TX(ContainerIdx, length, outPtr) IpduM_CntrQPeek(IPDUM_GET_TX_QUEUE((ContainerIdx)), (length), IPDUM_GET_TX_QDATABUFF((ContainerIdx)), (outPtr), (IPDUM_CFG_GET_CNTR_TX(ContainerIdx)->PduLength))

#if (defined IPDUM_CNTRQPOP)
#error IPDUM_CNTRQPOP already defined!
#endif /* #if (defined IPDUM_CNTRQPOP) */
/* Deviation MISRAC2012-1 */
#define IPDUM_CNTRQPOP(DIRECTION, ContainerIdx, length, inPtr, outPtr) IPDUM_CNTRQPOP_##DIRECTION((ContainerIdx), (length), (outPtr))

#if (defined IPDUM_CNTRQPOP_RX)
#error IPDUM_CNTRQPOP_RX already defined!
#endif /* #if (defined IPDUM_CNTRQPOP_RX) */
#define IPDUM_CNTRQPOP_RX(ContainerIdx, length, outPtr) IpduM_CntrQPop(IPDUM_GET_RX_QUEUE((ContainerIdx)), (length), IPDUM_GET_DEFERRED_DATA((ContainerIdx)), (outPtr), IPDUM_PBCFG_ACCESS(IpduM_ContainerRxPduType,IpduM_ConfigPtr->ContainerRxPdu)[(ContainerIdx)].PduLength, IPDUM_PBCFG_ACCESS(IpduM_ContainerRxPduType,IpduM_ConfigPtr->ContainerRxPdu)[(ContainerIdx)].ContainerQueueSize)

#if (defined IPDUM_CNTRQPOP_TX)
#error IPDUM_CNTRQPOP_TX already defined!
#endif /* #if (defined IPDUM_CNTRQPOP_TX) */
#define IPDUM_CNTRQPOP_TX(ContainerIdx, length, outPtr) IpduM_CntrQPop(IPDUM_GET_TX_QUEUE((ContainerIdx)), (length), IPDUM_GET_TX_QDATABUFF((ContainerIdx)), (outPtr), IPDUM_CFG_GET_CNTR_TX(ContainerIdx)->PduLength, IPDUM_CFG_GET_CNTR_TX(ContainerIdx)->IpduMContainerQueueSize)

#if (defined IPDUM_GET_TX_MF_IDX)
#error IPDUM_GET_TX_MF_IDX already defined!
#endif /* #if (defined IPDUM_GET_TX_MF_IDX) */
#define IPDUM_GET_TX_MF_IDX(idx) (*IPDUM_CFG_GET_MFTXLOOKUP(idx))

#if (defined IPDUM_GET_RX_MF_IDX)
#error IPDUM_GET_RX_MF_IDX already defined!
#endif /* #if (defined IPDUM_GET_RX_MF_IDX) */
#if(IPDUM_DEDICATED_IPDU_PROCESSING_SUPPORT == STD_ON)
#define IPDUM_GET_RX_MF_IDX(idx) (*IPDUM_CFG_GET_RXMFLOOKUP(idx))
#else
#define IPDUM_GET_RX_MF_IDX(idx) (idx)
#endif

#if (defined IPDUM_IDX_NOT_FOUND)
#error IPDUM_IDX_NOT_FOUND already defined!
#endif /* #if (defined IPDUM_IDX_NOT_FOUND) */
#define IPDUM_IDX_NOT_FOUND ((sint32) -1)

#if (defined IPDUM_E_CONFIG_PTR_INVALID)
#error IPDUM_E_CONFIG_PTR_INVALID already defined
#endif /* if (defined IPDUM_E_CONFIG_PTR_INVALID) */

/** \brief Error code for invalid configuration pointer.
 **/
#define IPDUM_E_CONFIG_PTR_INVALID 0x00U

[!AUTOSPACING!]
[!INCLUDE "IpduM_Macros.m"!]

[!SELECT "IpduMConfig/*[1]"!]
[!VAR "BufferOffset"= "num:i(0)"!]
[!VAR "QueueOffset"= "num:i(0)"!]

/* Data offsets for Pbcfg */

[!IF "not(var:defined('IpduMDataMemTxContainerOffset'))"!][!CALL "GetDataMemSlices"!][!ENDIF!][!//
#if (defined IPDUM_TXCNTROFFSET)
#error IPDUM_TXCNTROFFSET already defined!
#endif /* #if (defined IPDUM_TXCNTROFFSET) */
#define IPDUM_TXCNTROFFSET ((IpduM_DataOffsetType)([!"$IpduMDataMemTxContainerOffset"!]))

#if (defined IPDUM_RXCNTROFFSET)
#error IPDUM_RXCNTROFFSET already defined!
#endif /* #if (defined IPDUM_RXCNTROFFSET) */
#define IPDUM_RXCNTROFFSET ((IpduM_DataOffsetType)([!"$IpduMDataMemRxContainerOffset"!]))

[!CALL "GetDataMemSlices"!]
#if (defined IPDUM_DATAMEMMINLEN)
#error IPDUM_DATAMEMMINLEN already defined!
#endif /* #if (defined IPDUM_DATAMEMMINLEN) */
#define IPDUM_DATAMEMMINLEN ((IpduM_DataOffsetType)([!"$IpduMDataMemPathwaySize"!] + [!"$IpduMDataMemRxContainerSize"!] + [!"$IpduMDataMemTxContainerSize"!]))

[!LOOP "node:order(IpduMTxPathway/*, 'node:value(./IpduMTxRequest/IpduMTxConfirmationPduId)')"!]
[!// BufferOffset
[!VAR "OutgoingPduLength" = "node:value(as:ref(./IpduMTxRequest/IpduMOutgoingPduRef)/PduLength)"!]
[!IF "$IpduMZeroCopy = 'false'"!]
  [!VAR "BufferOffsetStr" = "concat('((IpduM_DataOffsetType)(sizeof(IpduM_TxDataType) * ',string(num:i(count(as:modconf('IpduM')[1]/IpduMConfig/*[1]/IpduMTxPathway/*))),'U)) + ((IpduM_DataOffsetType)(sizeof(IpduM_QueueEntryType) * ',string($TxQueueTotalEntries),'U) + ',string($BufferOffset),'U)')"!]
  [!VAR "BufferOffset"= "num:i($BufferOffset + $OutgoingPduLength)"!]
#if (defined IPDUM_TXPATHWAY_BUFFER_OFFSET_[!"node:pos(.)"!])
#error IPDUM_TXPATHWAY_BUFFER_OFFSET_[!"node:pos(.)"!] already defined!
#endif /* #if (defined IPDUM_TXPATHWAY_BUFFER_OFFSET_[!"node:pos(.)"!]) */
#define IPDUM_TXPATHWAY_BUFFER_OFFSET_[!"node:pos(.)"!] ([!"$BufferOffsetStr"!])
[!ENDIF!]
[!IF "$IpduMDynamicPartQueue = 'true'"!]
  [!VAR "QueueOffsetStr" = "concat('((IpduM_DataOffsetType)sizeof(IpduM_TxDataType) * ',string(num:i(count(as:modconf('IpduM')[1]/IpduMConfig/*[1]/IpduMTxPathway/*))),'U) + ((IpduM_DataOffsetType)sizeof(IpduM_QueueEntryType) * ',string($QueueOffset),'U)')"!]
  [!VAR "QueueOffset"= "num:i($QueueOffset + ./IpduMTxRequest/IpduMQueueSize)"!]
#if (defined IPDUM_TXPATHWAY_QUEUE_OFFSET_[!"node:pos(.)"!])
#error IPDUM_TXPATHWAY_QUEUE_OFFSET_[!"node:pos(.)"!] already defined!
#endif /* #if (defined IPDUM_TXPATHWAY_QUEUE_OFFSET_[!"node:pos(.)"!]) */
#define IPDUM_TXPATHWAY_QUEUE_OFFSET_[!"node:pos(.)"!] ([!"$QueueOffsetStr"!])
[!ENDIF!]
[!ENDLOOP!]

[!IF "$IpduMContainerPduHandlingEnable = 'true'"!]
[!VAR "NrOfRxContainers" = "num:i(count(IpduMContainerRxPdu/*))"!]
  [!IF "$NrOfRxContainers > 0"!]
    [!LOOP "node:order(IpduMContainerRxPdu/*, 'node:IpduMContainerRxHandleId')"!]
      [!CALL "GetBuffSliceIdx", "Direction"="'RX'", "ContainerIdx"="node:pos(.)"!]
      [!IF "$BuffSliceIdx < 0"!]
#if (defined IPDUM_RXCNTR_BUFFER_OFFSET_[!"node:pos(.)"!])
#error IPDUM_RXCNTR_BUFFER_OFFSET_[!"node:pos(.)"!] already defined!
#endif /* #if (defined IPDUM_RXCNTR_BUFFER_OFFSET_[!"node:pos(.)"!]) */
#define IPDUM_RXCNTR_BUFFER_OFFSET_[!"node:pos(.)"!] (0U)

      [!ELSE!]
#if (defined IPDUM_RXCNTR_BUFFER_OFFSET_[!"node:pos(.)"!])
#error IPDUM_RXCNTR_BUFFER_OFFSET_[!"node:pos(.)"!] already defined!
#endif /* #if (defined IPDUM_RXCNTR_BUFFER_OFFSET_[!"node:pos(.)"!]) */
#define IPDUM_RXCNTR_BUFFER_OFFSET_[!"node:pos(.)"!] ([!"$BuffSliceIdx"!])
      [!ENDIF!]

      [!IF "node:exists(./IpduMContainerQueueSize) and not(node:empty(./IpduMContainerQueueSize))"!]
#if (defined IPDUM_RXCNTR_QUEUE_BUFFER_OFFSET_[!"node:pos(.)"!])
#error IPDUM_RXCNTR_QUEUE_BUFFER_OFFSET_[!"node:pos(.)"!] already defined!
#endif /* #if (defined IPDUM_RXCNTR_QUEUE_BUFFER_OFFSET_[!"node:pos(.)"!]) */
#define IPDUM_RXCNTR_QUEUE_BUFFER_OFFSET_[!"node:pos(.)"!] ([!"$BuffQIdx"!])

      [!ELSE!]
#if (defined IPDUM_RXCNTR_QUEUE_BUFFER_OFFSET_[!"node:pos(.)"!])
#error IPDUM_RXCNTR_QUEUE_BUFFER_OFFSET_[!"node:pos(.)"!] already defined!
#endif /* #if (defined IPDUM_RXCNTR_QUEUE_BUFFER_OFFSET_[!"node:pos(.)"!]) */
#define IPDUM_RXCNTR_QUEUE_BUFFER_OFFSET_[!"node:pos(.)"!] (0U)
      [!ENDIF!]

    [!ENDLOOP!]
  [!ENDIF!]
  
  [!VAR "numTxContainer" = "num:i(count(IpduMContainerTxPdu/*))"!]
  [!IF "$numTxContainer > 0"!]
    [!CALL "GetIpduMTxContainersLst"!]
    [!FOR "i" = "0" TO "$numTxContainer - 1"!]
      [!VAR "nd" = "text:split(string(text:split($IpduMTxContainersLst,';')[position()-1 = $i]),':')[1]"!]
      [!SELECT "as:ref($nd)"!]
        [!CALL "GetTempDataStoreOffset", "ContainerPath"="node:path(.)"!]
#if (defined IPDUM_TXCNTR_CURRENT_DATA_OFFSET_[!"$i"!])
#error IPDUM_TXCNTR_CURRENT_DATA_OFFSET_[!"$i"!] already defined!
#endif /* #if (defined IPDUM_TXCNTR_CURRENT_DATA_OFFSET_[!"$i"!]) */
#define IPDUM_TXCNTR_CURRENT_DATA_OFFSET_[!"$i"!] ([!"$CntrTmpDSOfs"!])
        
        [!CALL "GetPduListOffset", "ContainerPath"="node:path(.)"!]
#if (defined IPDUM_TXCNTR_PDUS_LIST_OFFSET_[!"$i"!])
#error IPDUM_TXCNTR_PDUS_LIST_OFFSET_[!"$i"!] already defined!
#endif /* #if (defined IPDUM_TXCNTR_PDUS_LIST_OFFSET_[!"$i"!]) */
#define IPDUM_TXCNTR_PDUS_LIST_OFFSET_[!"$i"!] ([!"$cplOfs"!])

#if (defined IPDUM_TXCNTR_CONFIRM_LIST_OFFSET_[!"$i"!])
#error IPDUM_TXCNTR_CONFIRM_LIST_OFFSET_[!"$i"!] already defined!
#endif /* #if (defined IPDUM_TXCNTR_CONFIRM_LIST_OFFSET_[!"$i"!]) */
#define IPDUM_TXCNTR_CONFIRM_LIST_OFFSET_[!"$i"!] ([!"$ccplOfs"!])
           
        [!IF "$IpduMContainerQueuingTxEnable = 'true'"!]
          [!CALL "GetBuffSliceIdx", "Direction"="'TX'", "ContainerIdx"="node:pos(.)"!]
          [!IF "$BuffSliceIdx != num:i(-1)"!]
#if (defined IPDUM_TXCNTR_BUFFER_OFFSET_[!"$i"!])
#error IPDUM_TXCNTR_BUFFER_OFFSET_[!"$i"!] already defined!
#endif /* #if (defined IPDUM_TXCNTR_BUFFER_OFFSET_[!"$i"!]) */
#define IPDUM_TXCNTR_BUFFER_OFFSET_[!"$i"!] ([!"$BuffSliceIdx"!])
    
#if (defined IPDUM_TXCNTR_QUEUE_BUFFER_OFFSET_[!"$i"!])
#error IPDUM_TXCNTR_QUEUE_BUFFER_OFFSET_[!"$i"!] already defined!
#endif /* #if (defined IPDUM_TXCNTR_QUEUE_BUFFER_OFFSET_[!"$i"!]) */
#define IPDUM_TXCNTR_QUEUE_BUFFER_OFFSET_[!"$i"!] ([!"$BuffQIdx"!])
         
          [!ENDIF!]
        [!ENDIF!]
      [!ENDSELECT!]
    [!ENDFOR!]
  [!ENDIF!]
  
  [!VAR "numContainedTx" = "num:i(count(IpduMContainedTxPdu/*))"!]
  [!IF "$numContainedTx > 0"!]
    [!LOOP "node:order(IpduMContainedTxPdu/*, 'node:value(.)')"!]
      [!CALL "GetContainedBuffOffset","CntdPath"="node:path(.)"!]
#if (defined IPDUM_TXCNTD_BUFFER_OFFSET_[!"node:pos(.)"!])
#error IPDUM_TXCNTD_BUFFER_OFFSET_[!"node:pos(.)"!] already defined!
#endif /* #if (defined IPDUM_TXCNTR_QUEUE_BUFFER_OFFSET_[!"node:pos(.)"!]) */
#define IPDUM_TXCNTD_BUFFER_OFFSET_[!"node:pos(.)"!] ([!"$cntdBuffOffset"!])
      
    [!ENDLOOP!]
  [!ENDIF!]
[!ENDIF!]

[!ENDSELECT!]






/*------------------------[Defensive programming]----------------------------*/

#if (defined IPDUM_PRECONDITION_ASSERT)
#error IPDUM_PRECONDITION_ASSERT is already defined
#endif

#if (defined IPDUM_PRECONDITION_ASSERT_NO_EVAL)
#error IPDUM_PRECONDITION_ASSERT_NO_EVAL is already defined
#endif

#if (IPDUM_PRECONDITION_ASSERT_ENABLED == STD_ON)
/** \brief Report an assertion violation to Det
 **

 ** \param[in] Condition The condition which is verified
 ** \param[in] ApiId The service ID of the API function */
#define IPDUM_PRECONDITION_ASSERT(Condition, ApiId) \
  DET_PRECONDITION_ASSERT((Condition), IPDUM_MODULE_ID, IPDUM_INSTANCE_ID, (ApiId))

/** \brief Report an assertion violation to Det
 **

 ** \param[in] Condition The condition which is verified
 ** \param[in] ApiId The service ID of the API function */
#define IPDUM_PRECONDITION_ASSERT_NO_EVAL(Condition, ApiId) \
  DET_PRECONDITION_ASSERT_NO_EVAL((Condition), IPDUM_MODULE_ID, IPDUM_INSTANCE_ID, (ApiId))
#else
#define IPDUM_PRECONDITION_ASSERT(Condition, ApiId)
#define IPDUM_PRECONDITION_ASSERT_NO_EVAL(Condition, ApiId)
#endif

#if (defined IPDUM_POSTCONDITION_ASSERT)
#error IPDUM_POSTCONDITION_ASSERT is already defined
#endif

#if (defined IPDUM_POSTCONDITION_ASSERT_NO_EVAL)
#error IPDUM_POSTCONDITION_ASSERT_NO_EVAL is already defined
#endif

#if (IPDUM_POSTCONDITION_ASSERT_ENABLED == STD_ON)
/** \brief Report an assertion violation to Det
 **

 ** \param[in] Condition The condition which is verified
 ** \param[in] ApiId The service ID of the API function */
#define IPDUM_POSTCONDITION_ASSERT(Condition, ApiId) \
  DET_POSTCONDITION_ASSERT((Condition), IPDUM_MODULE_ID, IPDUM_INSTANCE_ID, (ApiId))

/** \brief Report an assertion violation to Det
 **

 ** \param[in] Condition The condition which is verified
 ** \param[in] ApiId The service ID of the API function */
#define IPDUM_POSTCONDITION_ASSERT_NO_EVAL(Condition, ApiId) \
  DET_POSTCONDITION_ASSERT_NO_EVAL((Condition), IPDUM_MODULE_ID, IPDUM_INSTANCE_ID, (ApiId))
#else
#define IPDUM_POSTCONDITION_ASSERT(Condition, ApiId)
#define IPDUM_POSTCONDITION_ASSERT_NO_EVAL(Condition, ApiId)
#endif

#if (defined IPDUM_INVARIANT_ASSERT)
#error IPDUM_INVARIANT_ASSERT is already defined
#endif

#if (defined IPDUM_INVARIANT_ASSERT_NO_EVAL)
#error IPDUM_INVARIANT_ASSERT_NO_EVAL is already defined
#endif

#if (IPDUM_INVARIANT_ASSERT_ENABLED == STD_ON)
/** \brief Report an assertion violation to Det
 **

 ** \param[in] Condition The condition which is verified
 ** \param[in] ApiId The service ID of the API function */
#define IPDUM_INVARIANT_ASSERT(Condition, ApiId) \
  DET_INVARIANT_ASSERT((Condition), IPDUM_MODULE_ID, IPDUM_INSTANCE_ID, (ApiId))

/** \brief Report an assertion violation to Det
 **

 ** \param[in] Condition The condition which is verified
 ** \param[in] ApiId The service ID of the API function */
#define IPDUM_INVARIANT_ASSERT_NO_EVAL(Condition, ApiId) \
  DET_INVARIANT_ASSERT_NO_EVAL((Condition), IPDUM_MODULE_ID, IPDUM_INSTANCE_ID, (ApiId))
#else
#define IPDUM_INVARIANT_ASSERT(Condition, ApiId)
#define IPDUM_INVARIANT_ASSERT_NO_EVAL(Condition, ApiId)
#endif

#if (defined IPDUM_STATIC_ASSERT)
# error IPDUM_STATIC_ASSERT is already defined
#endif
#if (IPDUM_STATIC_ASSERT_ENABLED == STD_ON)
/** \brief Report an static assertion violation to Det
 **
 ** \param[in] Condition Condition which is violated */
# define IPDUM_STATIC_ASSERT(expr) DET_STATIC_ASSERT(expr)
#else
# define IPDUM_STATIC_ASSERT(expr)
#endif

#if (defined IPDUM_UNREACHABLE_CODE_ASSERT)
#error IPDUM_UNREACHABLE_CODE_ASSERT is already defined
#endif
#if (IPDUM_UNREACHABLE_CODE_ASSERT_ENABLED == STD_ON)
/** \brief Report an unreachable code assertion violation to Det
 **

 ** \param[in] ApiId Service ID of the API function */
#define IPDUM_UNREACHABLE_CODE_ASSERT(ApiId) \
  DET_UNREACHABLE_CODE_ASSERT(IPDUM_MODULE_ID, IPDUM_INSTANCE_ID, (ApiId))
#else
#define IPDUM_UNREACHABLE_CODE_ASSERT(ApiId)
#endif

#if (defined IPDUM_INTERNAL_API_ID)
#error IPDUM_INTERNAL_API_ID is already defined
#endif
/** \brief API ID of module internal functions to be used in assertions */
#define IPDUM_INTERNAL_API_ID DET_INTERNAL_API_ID



/*==================[type definitions]======================================*/
/** \brief definition of the IpduM_StatusType */
typedef uint8 IpduM_StatusType;

typedef P2FUNC(void, IPDUM_CODE, IpduM_RxIndHandlerType)
(
  VAR(PduIdType, TYPEDEF) RxPduId,
  P2VAR(PduInfoType, AUTOMATIC, IPDUM_APPL_DATA) PduInfoPtr
);

/** \brief Definition of constant IPDUM_UNINIT */
#if (defined IPDUM_UNINIT)        /* To prevent double declaration */
#error IPDUM_UNINIT already defined
#endif /* if (defined IPDUM_UNINIT) */

/** \brief Define IPDUM_UNINIT */
#define IPDUM_UNINIT ((IpduM_StatusType) 0x0)

/** \brief Definition of constant IPDUM_INIT */
#if (defined IPDUM_INIT)          /* To prevent double declaration */
#error IPDUM_INIT already defined
#endif /* if (defined IPDUM_INIT) */

/** \brief Define IPDUM_INIT */
#define IPDUM_INIT ((IpduM_StatusType) 0x01U)

/* define function like macro for development error reporting,
 * if development error detection is enabled */
#if (IPDUM_DEV_ERROR_DETECT==STD_ON)

#if (defined IPDUM_DET_REPORT_ERROR)
#error IPDUM_DET_REPORT_ERROR already defined!
#endif /* #if (defined IPDUM_DET_REPORT_ERROR)*/

#define IPDUM_DET_REPORT_ERROR(ApiId,ErrorId)    \
  (void)Det_ReportError(IPDUM_MODULE_ID, IPDUM_INSTANCE_ID, (ApiId), (uint8)(ErrorId))
#endif /* if (IPDUM_DEV_ERROR_DETECT == STD_ON) */

/*==================[external function declarations]========================*/

/*==================[internal function declarations]========================*/

/*==================[external constants]====================================*/

/*==================[internal constants]====================================*/

/*==================[external data]=========================================*/

/*==================[internal data]=========================================*/

/*==================[external function definitions]=========================*/

/*==================[internal function definitions]=========================*/


#undef TS_RELOCATABLE_CFG_ENABLE

#endif /* if !defined( IPDUM_INT_H ) */
/*==================[end of file]===========================================*/
