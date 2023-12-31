/**
 * \file
 *
 * \brief AUTOSAR Mirror
 *
 * This file contains the implementation of the AUTOSAR
 * module Mirror.
 *
 * \author Elektrobit Automotive GmbH, 91058 Erlangen, Germany
 *
 * Copyright 2005 - 2019 Elektrobit Automotive GmbH
 * All rights exclusively reserved for Elektrobit Automotive GmbH,
 * unless expressly agreed to otherwise.
 */


/*
 *  MISRA-C:2012 Deviations:
 *
 *  MISRAC2012-1) Deviated Rule: 2.7 (Advisory)
 *    There should be no unused parameters in functions.
 *
 *    Reason:
 *    - The Mirror module only supports precompile variation so there could
 *      be unused parameters passed to a function that wouldn't be of use.
 *
 *  MISRAC2012-2) Deviated Rule: 16.1 (Required)
 *    All switch statements shall be well-formed.
 *
 *    Reason:
 *    - It is required to run the functions sequentially with the function
 *      which needs to start first is determined at the runtime so there
 *      must be no breaks in the switch case.
 *
 *  MISRAC2012-3) Deviated Rule: 16.3 (Required)
 *    An unconditional break statement shall terminate every switch-clause.
 *
 *    Reason:
 *    - It is required to run the functions sequentially with the function
 *      which needs to start first is determined at the runtime so there
 *      must be no breaks in the switch case.
 *
 *  MISRAC2012-4) Deviated Rule: 18.4 (Advisory)
 *    The +, -, += and -= operators should not be applied to an expression of pointer type.
 *
 *    Reason:
 *    - To copy a variable with a size bigger than 8 bits avoiding the difference
 *      between big endian and little endian processors operations on pointers
 *      must be performed.
 */

/*==================[inclusions]============================================*/

#include <TSAutosar.h> /* Specific standard types */
#include <Mirror.h> /* Module public API */
#include <Mirror_Cbk.h> /* Module call back public API */
#include <Mirror_Types.h> /* Module specific types */
#include <Mirror_Trace.h> /* Debug and trace */
#include <Mirror_Version.h> /* Module version declarations */
#include <PduR_Mirror.h> /* PduR public Api for Mirror */
#include <SchM_Mirror.h> /* SchM interface header */
#include <TSMem.h> /* EB memcopy */

/*==================[version check]=========================================*/

/*------------------[AUTOSAR vendor identification check]-------------------*/

#if (!defined MIRROR_VENDOR_ID) /* configuration check */
#error MIRROR_VENDOR_ID must be defined
#endif

#if (MIRROR_VENDOR_ID != 1U) /* vendor check */
#error MIRROR_VENDOR_ID has wrong vendor id
#endif

/*------------------[AUTOSAR release version identification check]----------*/

#if (!defined MIRROR_AR_RELEASE_MAJOR_VERSION) /* configuration check */
#error MIRROR_AR_RELEASE_MAJOR_VERSION must be defined
#endif

/* major version check */
#if (MIRROR_AR_RELEASE_MAJOR_VERSION != 4U)
#error MIRROR_AR_RELEASE_MAJOR_VERSION wrong (!= 4U)
#endif

#if (!defined MIRROR_AR_RELEASE_MINOR_VERSION) /* configuration check */
#error MIRROR_AR_RELEASE_MINOR_VERSION must be defined
#endif

/* minor version check */
#if (MIRROR_AR_RELEASE_MINOR_VERSION != 3U )
#error MIRROR_AR_RELEASE_MINOR_VERSION wrong (!= 3U)
#endif

#if (!defined MIRROR_AR_RELEASE_REVISION_VERSION) /* configuration check */
#error MIRROR_AR_RELEASE_REVISION_VERSION must be defined
#endif

/* revision version check */
#if (MIRROR_AR_RELEASE_REVISION_VERSION != 1U )
#error MIRROR_AR_RELEASE_REVISION_VERSION wrong (!= 1U)
#endif

/*------------------[AUTOSAR module version identification check]-----------*/

#if (!defined MIRROR_SW_MAJOR_VERSION) /* configuration check */
#error MIRROR_SW_MAJOR_VERSION must be defined
#endif

/* major version check */
#if (MIRROR_SW_MAJOR_VERSION != 1U)
#error MIRROR_SW_MAJOR_VERSION wrong (!= 1U)
#endif

#if (!defined MIRROR_SW_MINOR_VERSION) /* configuration check */
#error MIRROR_SW_MINOR_VERSION must be defined
#endif

/* minor version check */
#if (MIRROR_SW_MINOR_VERSION < 0U)
#error MIRROR_SW_MINOR_VERSION wrong (< 0U)
#endif

#if (!defined MIRROR_SW_PATCH_VERSION) /* configuration check */
#error MIRROR_SW_PATCH_VERSION must be defined
#endif

/* patch version check */
#if (MIRROR_SW_PATCH_VERSION < 7U)
#error MIRROR_SW_PATCH_VERSION wrong (< 7U)
#endif

/*==================[macros]================================================*/

/*==================[internal function declarations]=======================*/
#define MIRROR_START_SEC_CODE
#include <Mirror_MemMap.h>

/** \brief Mirror_FindSrcNetwork()
 **
 ** This function finds the Mirror network index and direction corresponding
 ** to the ComM network entered
 **
 ** - Retruns FALSE if no network was found corresponding to the ComM channel entered.
 ** - Retruns TRUE if a network was found corresponding to the ComM channel entered.
 **
 ** \param[in] network  Identifier of the ComM network.
 ** \param[inout] NetworkIndexPtr - Pointer to return the index of the source mirror network.
 */
static FUNC(boolean, MIRROR_CODE) Mirror_FindSrcNetwork
(
  VAR(NetworkHandleType, TYPEDEF) network,
  P2VAR(uint8, AUTOMATIC, MIRROR_APPL_DATA) NetworkIndexPtr
);

/** \brief Mirror_FindDestNetwork()
 **
 ** This function finds the Mirror network index and direction corresponding
 ** to the ComM network entered
 **
 ** - Retruns FALSE if no network was found corresponding to the ComM channel entered.
 ** - Retruns TRUE if a network was found corresponding to the ComM channel entered.
 **
 ** \param[in] network  Identifier of the ComM network.
 ** \param[inout] NetworkIndexPtr - Pointer to return the index of the source mirror network.
 */
static FUNC(boolean, MIRROR_CODE) Mirror_FindDestNetwork
(
  VAR(NetworkHandleType, TYPEDEF) network,
  P2VAR(uint8, AUTOMATIC, MIRROR_APPL_DATA) NetworkIndexPtr
);

/** \brief Mirror_StartSourceNetowrkInternal()
 **
 ** This function starts the source network specified in the input parameter.
 **
 ** \param[in] SourceNetworkIdx  Identifier of the source network.
 ** \param[in] MirrorActive  Flag to start or stop the network.
 */
static FUNC(void, MIRROR_CODE) Mirror_SourceNetworkActivateInternal
(
  VAR(uint8, MIRROR_VAR) SourceNetworkIdx,
  VAR(boolean, MIRROR_VAR) MirrorActive
);

/** \brief Mirror_InitBuffStatus()
 **
 ** This function resets the status of all the data elements buffers to available.
 **
 */
static FUNC(void, MIRROR_CODE) Mirror_InitBuffStatus
(
  void
);

/** \brief Mirror_SendActivationFrame()
 **
 ** This function sends the initialization frame needed after initializing the Mirror.
 **
 */
static FUNC(void, MIRROR_CODE) Mirror_SendActivationFrame
(
  void
);

/** \brief Mirror_InitQueueStatus()
 **
 ** This function resets the status of queues to NOT_ACTIVE.
 **
 */
static FUNC (void, MIRROR_CODE) Mirror_InitQueueStatus
(
  void
);

/** \brief Mirror_InitSrcNtwrkStatus()
 **
 ** This function resets all the status of the Source networks.
 **
 */
static FUNC(void, MIRROR_CODE) Mirror_InitSrcNetworkStatus
(
  void
);

/** \brief Mirror_OfflineInternal()
 **
 ** This function performs the offline sequence.
 **
 */
static FUNC (void, MIRROR_CODE) Mirror_OfflineInternal
(
  void
);

/** \brief Mirror_CheckSourceNetworksActivation()
 **
 ** This function checks if any source network is required to be
 ** started or stopped.
 **
 */
static FUNC (void, MIRROR_CODE) Mirror_CheckSourceNetworksActivation
(
  void
);

/** \brief Mirror_CheckSourceBusesStatus()
 **
 ** This function checks the source bus status.
 **
 */
 static FUNC (void, MIRROR_CODE) Mirror_CheckSourceBusesStatus
(
  void
);

/** \brief Mirror_ActivateQueueBuffer()
 **
 ** This function performs the queue buffer activation to set the time stamp with the min value.
 **
 ** \param[in] CanFrameReady  Identifier if a Can frame is ready.
 ** \param[in] CanFDFrameReady  Identifier if a CanFD frame is ready.
 ** \param[in] LinFrameReady  Identifier if a Lin frame is ready.
 */
static FUNC (void, MIRROR_CODE) Mirror_ActivateQueueBuffer
(
  VAR(boolean, MIRROR_VAR) CanFrameReady,
  VAR(boolean, MIRROR_VAR) CanFDFrameReady,
  VAR(boolean, MIRROR_VAR) LinFrameReady
);

/** \brief Mirror_GetMinTimeStamp()
 **
 ** This function evaluates the min time stamp of the time stamps entered as inputs.
 **
 ** \param[in] CanTimeStamp  Can frame time stamp.
 ** \param[in] CanFDTimeStamp  CanFD frame time stamp.
 ** \param[in] LinTimeStamp  Lin frame time stamp.
 **
 ** retval The type of the frame which has the min time stamp.
 **
 ** \param[inout] OutputTimeStamp  The result frame time stamp.
 **
 */
static FUNC (uint8, MIRROR_CODE) Mirror_GetMinTimeStamp
(
  P2CONST(MIRROR_TIMESTAMP_TYPE, AUTOMATIC, MIRROR_APPL_DATA) CanTimeStamp,
  P2CONST(MIRROR_TIMESTAMP_TYPE, AUTOMATIC, MIRROR_APPL_DATA) CanFDTimeStamp,
  P2CONST(MIRROR_TIMESTAMP_TYPE, AUTOMATIC, MIRROR_APPL_DATA) LinTimeStamp,
  P2VAR(MIRROR_TIMESTAMP_TYPE, AUTOMATIC, MIRROR_APPL_DATA) OutputTimeStamp
);

/** \brief Mirror_TimeStampComparator()
 **
 ** This function compares between the time stamps entered.
 **
 ** \param[in] TimeStamp_1  first time stamp operand.
 ** \param[in] TimeStamp_2  second time stamp operand.
 **
 **\param[inout] MinTimeStamp  The minimum time stamp between the 2 operands.
 **                            If both operands entered are NULL_PTR then the return will be TRUE
 **                            and the MinTimeStamp will be the max value.
 **
 ** \retval TRUE  TimeStamp_1 is less than or equal TimeStamp_2.
 **         FALSE TimeStamp_1 is greater than TimeStamp_2.
 */
static FUNC (boolean, MIRROR_CODE) Mirror_TimeStampComparator
(
  P2CONST(MIRROR_TIMESTAMP_TYPE, AUTOMATIC, MIRROR_APPL_DATA) TimeStamp_1,
  P2CONST(MIRROR_TIMESTAMP_TYPE, AUTOMATIC, MIRROR_APPL_DATA) TimeStamp_2,
  P2VAR(MIRROR_TIMESTAMP_TYPE, AUTOMATIC, MIRROR_APPL_DATA) MinTimeStamp
);

/** \brief Mirror_WriteFrameHeader()
 **
 ** This function fills the header of the frame currently being activated.
 **
 */
static FUNC (void, MIRROR_CODE) Mirror_WriteFrameHeader
(
  void
);

/** \brief Mirror_MemCpy16()
 **
 ** This function copies the uint16 value to the destination buffer.
 **
 */
static FUNC (void, MIRROR_CODE) Mirror_MemCpy16
(
  VAR(uint16, MIRROR_VAR) value,
  P2VAR(uint8, AUTOMATIC, MIRROR_APPL_DATA) dest
);

/** \brief Mirror_MemCpy32()
 **
 ** This function copies the uint16 value to the destination buffer.
 **
 */
static FUNC (void, MIRROR_CODE) Mirror_MemCpy32
(
  VAR(uint32, MIRROR_VAR) value,
  P2VAR(uint8, AUTOMATIC, MIRROR_APPL_DATA) dest
);

/** \brief Mirror_CopyFrames()
 **
 ** This function copies the ready frames from the intermediate buffer to the queue buffer.
 **
 ** \retval E_OK  All frames were copied successfully.
 **         E_NOT_OK Not all frames were copied successfully.
 */
static FUNC (Std_ReturnType, MIRROR_CODE) Mirror_CopyFrames
(
  void
);

/** \brief CopyStatusBytes()
 **
 ** This function copies the status bytes changed from the latest main function and not copied in a data element.
 **
 ** \retval E_OK  The status bytes were copied sucessfully and no queue overrun.
 **         E_NOT_OK queue overrun.
 **
 */
static FUNC (Std_ReturnType, MIRROR_CODE) CopyStatusBytes
(
  void
);

/** \brief CopyStatusDataElement()
 **
 ** This function copies the status byte of the input source network to the currently active queue buffer .
 **
 **
 */
static FUNC (void, MIRROR_CODE) CopyStatusDataElement
(
  VAR(uint8, MIRROR_VAR) SourceNetworkIndex,
  P2CONST(MIRROR_TIMESTAMP_TYPE, AUTOMATIC, MIRROR_APPL_DATA) TimeStamp
);

/** \brief InsertSourceNetworkIndex()
 **
 ** This function inserts the source network index inside the currently active queue buffer status array .
 **
 */
static FUNC (void, MIRROR_CODE) InsertSourceNetworkIndex
(
  VAR(uint8, MIRROR_VAR) SourceNetworkIndex
);

/** \brief QueueTimingOperations()
 **
 ** This function performs the timing operations if the active queue buffers .
 **
 */
static FUNC (void, MIRROR_CODE) QueueTimingOperations
(
  void
);
/** \brief QueueTimingOperations()
 **
 ** This function trasnmits the data in the said queue buffer.
 **
 */
static FUNC (void, MIRROR_CODE) Mirror_TransmitQueueBuffer
(
#if(MIRROR_DEV_ERROR_DETECT == STD_ON)
  VAR(uint8, MIRROR_VAR) ApiId
#else
  void
#endif /* MIRROR_DEV_ERROR_DETECT */
);

#if(MIRROR_CAN_SOURCENETWORK == STD_ON)
/** \brief Mirror_CopyCurrentCanFrame()
 **
 ** This function copies the can frame of the Mirror_CanElementReadIndex to the queue buffer.
 **
 ** \retval TRUE  Frame was copied succussfully.
 **         FALSE Frame wasn't copied as there is no space in the queue buffer.
 */
static FUNC (Std_ReturnType, MIRROR_CODE) Mirror_CopyCurrentCanFrame
(
  P2VAR(boolean, AUTOMATIC, MIRROR_APPL_DATA) CopySuccessStatus
);
#endif /* MIRROR_CAN_SOURCENETWORK == STD_ON */

#if(MIRROR_CANFD_SOURCENETWORK == STD_ON)
/** \brief Mirror_CopyCurrentCanFDFrame()
 **
 ** This function copies the can frame of the Mirror_CanFDElementReadIndex to the queue buffer.
 **
 ** \retval TRUE  Frame was copied succussfully.
 **         FALSE Frame wasn't copied as there is no space in the queue buffer.
 */
static FUNC (Std_ReturnType, MIRROR_CODE) Mirror_CopyCurrentCanFDFrame
(
  P2VAR(boolean, AUTOMATIC, MIRROR_APPL_DATA) CopySuccessStatus
);
#endif /* MIRROR_CANFD_SOURCENETWORK == STD_ON */

#if(MIRROR_LIN_SOURCENETWORK == STD_ON)
/** \brief Mirror_CopyCurrentLinFrame()
 **
 ** This function copies the can frame of the Mirror_LinElementReadIndex to the queue buffer.
 **
 ** \retval TRUE  Frame was copied succussfully.
 **         FALSE Frame wasn't copied as there is no space in the queue buffer.
 */
static FUNC (Std_ReturnType, MIRROR_CODE) Mirror_CopyCurrentLinFrame
(
  P2VAR(boolean, AUTOMATIC, MIRROR_APPL_DATA) CopySuccessStatus
);
#endif /* MIRROR_LIN_SOURCENETWORK == STD_ON */

/** \brief Mirror_TimeStampDiff()
 **
 ** This function gets the time difference between the entered time stamp and the reference time stamp of the Mirror in the unit of 10us.
 **
 ** \param[in] TimeStamp  time stamp operand to get the difference between and the reference time stamp.
 ** \param[inout] BelowMax  TRUE: If the difference between the time stamp and the reference is less than 655.35 ms.
 **                         FALSE: If the difference between the time stamp and the reference is larger than 655.35 ms.
 */
static FUNC (uint16, MIRROR_CODE) Mirror_TimeStampDiff
(
  P2CONST(MIRROR_TIMESTAMP_TYPE, AUTOMATIC, MIRROR_APPL_DATA) TimeStamp,
  P2VAR(boolean, AUTOMATIC, MIRROR_APPL_DATA) BelowMax
);

#define MIRROR_STOP_SEC_CODE
#include <Mirror_MemMap.h>

#if(MIRROR_CAN_SOURCENETWORK == STD_ON)

#define MIRROR_START_SEC_CAN_CODE
#include <Mirror_MemMap.h>

/** \brief Mirror_FindCanSourceNetwork()
 **
 ** This function finds the Source network Index from the CAN controller Id
 **
 */
static FUNC(boolean, MIRROR_CODE) Mirror_FindCanSourceNetwork
(
  VAR(uint8, MIRROR_VAR) controllerId,
  P2VAR(uint8, AUTOMATIC, MIRROR_APPL_DATA) CanSrcNtwrkIdx
);

/** \brief Mirror_StoreCanFrame()
 **
 ** This function stores the Can frame received from the CanIf through the Mirror_ReportCanFrame()
 **
 ** \param[in] SrcNtwrkIdx  Index of the source network this frame was received from.
 ** \param[in] CanId  The CanId this frame.
 ** \param[in] length  Length of the data received.
 ** \param[in] payload  Pointer to the data of the frame.
 */
static FUNC (void, MIRROR_CODE) Mirror_StoreCanFrame
(
  VAR(uint8, TYPEDEF) SrcNtwrkIdx,
  VAR(Can_IdType, TYPEDEF) canId,
  VAR(uint8, TYPEDEF) length,
  P2CONST(uint8, AUTOMATIC, MIRROR_APPL_DATA) payload
);

#if(MIRROR_CANFD_SOURCENETWORK == STD_ON)
/** \brief Mirror_StoreCanFDFrame()
 **
 ** This function stores the CanFD frame received from the CanIf through the Mirror_ReportCanFrame()
 **
 ** \param[in] SrcNtwrkIdx  Index of the source network this frame was received from.
 ** \param[in] CanId  The CanId this frame.
 ** \param[in] length  Length of the data received.
 ** \param[in] payload  Pointer to the data of the frame.
 */
static FUNC (void, MIRROR_CODE) Mirror_StoreCanFDFrame
(
  VAR(uint8, TYPEDEF) SrcNtwrkIdx,
  VAR(Can_IdType, TYPEDEF) canId,
  VAR(uint8, TYPEDEF) length,
  P2CONST(uint8, AUTOMATIC, MIRROR_APPL_DATA) payload
);
#endif /* MIRROR_CANFD_SOURCENETWORK == STD_ON */

#define MIRROR_STOP_SEC_CAN_CODE
#include <Mirror_MemMap.h>

#endif /* MIRROR_CAN_SOURCENETWORK == STD_ON */

#if(MIRROR_LIN_SOURCENETWORK == STD_ON)

#define MIRROR_START_SEC_LIN_CODE
#include <Mirror_MemMap.h>

/** \brief Mirror_FindLinSourceNetwork()
 **
 ** This function finds the Source network Index from the ComM handle Id
 **
 */
static FUNC(boolean, MIRROR_CODE) Mirror_FindLinSourceNetwork
(
  VAR(NetworkHandleType, MIRROR_VAR) network,
  P2VAR(uint8, AUTOMATIC, MIRROR_APPL_DATA) LinSrcNtwrkIdx
);

/** \brief Mirror_StoreLinFrame()
 **
 ** This function stores the Lin frame in the intermediate buffer.
 **
 */
static FUNC (void, MIRROR_CODE) Mirror_StoreLinFrame
(
  VAR(Lin_FramePidType, TYPEDEF) pid,
  P2CONST(PduInfoType, AUTOMATIC, MIRROR_APPL_DATA) pdu,
  VAR(Lin_StatusType, TYPEDEF) status,
  VAR(uint8, TYPEDEF) SrcNtwrkIdx
);
#define MIRROR_STOP_SEC_LIN_CODE
#include <Mirror_MemMap.h>

#endif /* MIRROR_LIN_SOURCENETWORK == STD_ON */


/*==================[external constants]====================================*/

/*==================[internal constants]====================================*/

/*==================[external data]=========================================*/

/*==================[internal data]=========================================*/

#define MIRROR_START_SEC_VAR_INIT_GLOBAL_8
#include <Mirror_MemMap.h>

/** \brief Variable to indicate the module status. */
STATIC VAR(boolean, MIRROR_VAR) Mirror_InitState = MIRROR_NOT_INITIALIZED;

/** \brief Variable to indicate if the offline mode is requested is Mirror_Offline() but not processed. */
STATIC VAR(boolean, MIRROR_VAR) Mirror_OfflineRequest = FALSE;

#if(MIRROR_CAN_SOURCENETWORK == STD_ON)
/** \brief Variable to indicate if the function Mirror_ReportCanFrame() is currently processing. */
STATIC VAR(boolean, MIRROR_VAR) Mirror_ReportingCanFrame = FALSE;
#endif /* MIRROR_CAN_SOURCENETWORK == STD_ON */

#if(MIRROR_LIN_SOURCENETWORK == STD_ON)
/** \brief Variable to indicate if the function Mirror_ReportLinFrame() is currently processing. */
STATIC VAR(boolean, MIRROR_VAR) Mirror_ReportingLinFrame = FALSE;
#endif /* MIRROR_LIN_SOURCENETWORK == STD_ON */

#define MIRROR_STOP_SEC_VAR_INIT_GLOBAL_8
#include <Mirror_MemMap.h>

#define MIRROR_START_SEC_VAR_CLEARED_LOCAL_8
#include <Mirror_MemMap.h>

/** \brief Variable to indicate the current active destination network. */
STATIC VAR(uint8, MIRROR_VAR) Mirror_ActiveDestination;

/** \brief Variable to indicate the required destination index to be active. */
STATIC VAR(uint8, MIRROR_VAR) Mirror_DestNetworkIdxRequired;

/** \brief Variable to indicate the required destination index to be active. */
STATIC VAR(uint8, MIRROR_VAR) Mirror_SequenceNumber;

/** \brief Variable to indicate the buffer type which will write the first data element in the queue buffer. */
STATIC VAR(uint8, MIRROR_VAR) DefaultDataElementMinTime;

/** \brief Variable to indicate if the Mirror is transmitting on the currently active destination network and waiting Mirror_TxConfirmation or time out. */
STATIC VAR(boolean, MIRROR_VAR) Mirror_IsTransmitting;

/** \brief Variable to indicate the global mirroring state. */
STATIC VAR(boolean, MIRROR_VAR) Mirror_IsActive;

#define MIRROR_STOP_SEC_VAR_CLEARED_LOCAL_8
#include <Mirror_MemMap.h>

#define MIRROR_START_SEC_VAR_CLEARED_LOCAL_16
#include <Mirror_MemMap.h>

/** \brief Variable to indicate the current active buffer in the queue. */
STATIC VAR(uint16, MIRROR_VAR) Mirror_ActiveQueueBuffer;

/** \brief Variable to indicate the queue buffer index that will be transmitted next. */
STATIC VAR(uint16, MIRROR_VAR) Mirror_NextTxQueueBuffer;

/** \brief Variable to indicate the queue buffer index that is being transmitted. */
STATIC VAR(uint16, MIRROR_VAR) Mirror_TxQueueBuffer;

#define MIRROR_STOP_SEC_VAR_CLEARED_LOCAL_16
#include <Mirror_MemMap.h>

#define MIRROR_START_SEC_VAR_CLEARED_LOCAL_32
#include <Mirror_MemMap.h>

#if(MIRROR_LIN_SOURCENETWORK == STD_ON)
/** \brief Variable to indicate the current active read index of the LIN elements. */
STATIC VAR(uint32, MIRROR_VAR) Mirror_LinElementReadIndex;
#endif /* MIRROR_LIN_SOURCENETWORK == STD_ON */

#if(MIRROR_CAN_SOURCENETWORK == STD_ON)
/** \brief Variable to indicate the current active read index of the CAN elements. */
STATIC VAR(uint32, MIRROR_VAR) Mirror_CanElementReadIndex;
#endif /* MIRROR_CAN_SOURCENETWORK == STD_ON */

#if(MIRROR_CANFD_SOURCENETWORK == STD_ON)
/** \brief Variable to indicate the current active read index of the CANFD elements. */
STATIC VAR(uint32, MIRROR_VAR) Mirror_CanFDElementReadIndex;
#endif /* MIRROR_CANFD_SOURCENETWORK == STD_ON */

#define MIRROR_STOP_SEC_VAR_CLEARED_LOCAL_32
#include <Mirror_MemMap.h>

#define MIRROR_START_SEC_VAR_CLEARED_LOCAL_UNSPECIFIED
#include <Mirror_MemMap.h>

/** \brief Variable to indicate the time stamp of the currently active queue buffer. */
STATIC VAR(MIRROR_TIMESTAMP_TYPE, MIRROR_VAR) RefTimeStamp;

STATIC VAR(PduInfoType, MIRROR_VAR) TxPduInfo;

#define MIRROR_STOP_SEC_VAR_CLEARED_LOCAL_UNSPECIFIED
#include <Mirror_MemMap.h>

/*==================[external function definitions]=========================*/
#define MIRROR_START_SEC_CODE
#include <Mirror_MemMap.h>

/* !LINKSTO Mirror.ASR44.SWS_Mirror_01005,1 */
#if(MIRROR_VERSION_INFO_API == STD_ON)
FUNC(void, MIRROR_CODE) Mirror_GetVersionInfo
(
  P2VAR(Std_VersionInfoType, AUTOMATIC, MIRROR_APPL_DATA) VersionInfo
)
{
  DBG_MIRROR_GETVERSIONINFO_ENTRY(VersionInfo);

#if(MIRROR_DEV_ERROR_DETECT == STD_ON)
  /* check if the VersionInfo pointer is a Null Pointer */
  /* !LINKSTO Mirror.ASR44.SWS_Mirror_00066,1 */
  if(NULL_PTR == VersionInfo)
  {
    MIRROR_DET_REPORT_ERROR(MIRROR_SID_GETVERSIONINFO, MIRROR_E_PARAM_POINTER);
  }
  else
#endif /* MIRROR_DEV_ERROR_DETECT == STD_ON */
  {
    /* Return version information */
    VersionInfo->vendorID = (uint16)MIRROR_VENDOR_ID;
    VersionInfo->moduleID = (uint16)MIRROR_MODULE_ID;
    VersionInfo->sw_major_version = (uint8)MIRROR_SW_MAJOR_VERSION;
    VersionInfo->sw_minor_version = (uint8)MIRROR_SW_MINOR_VERSION;
    VersionInfo->sw_patch_version = (uint8)MIRROR_SW_PATCH_VERSION;
  }

  DBG_MIRROR_GETVERSIONINFO_EXIT(VersionInfo);
}
#endif /* MIRROR_VERSION_INFO_API */

/* !LINKSTO Mirror.ASR44.SWS_Mirror_01003,1 */
/* Deviation MISRAC2012-1 <1> */
FUNC(void, MIRROR_CODE) Mirror_Init
(
  P2CONST(Mirror_ConfigType, AUTOMATIC, MIRROR_APPL_CONST) config
)
{
  DBG_MIRROR_INIT_ENTRY(config);
  TS_PARAM_UNUSED(config);
  if(MIRROR_NOT_INITIALIZED == Mirror_InitState)
  {
      /* !LINKSTO Mirror.ASR44.SWS_Mirror_00002,1 */
      /* !LINKSTO Mirror.ASR44.SWS_Mirror_00009,1 */
      Mirror_ActiveDestination = (uint8)MIRROR_INITIAL_DEST_NETWORK_IDX;
      /* !LINKSTO Mirror.ASR44.SWS_Mirror_00043.Init,1 */
      /* CHECK: NOPARSE */
      if((Mirror_NetworkType)MIRROR_NT_CAN != Mirror_DestNetworks[Mirror_ActiveDestination].NetworkType)
      {
          Mirror_SequenceNumber = (uint8)0x00;
      }
      else
      {
          /* No Can destination is supported and no sequence number for can. */
          /* This case can't happen as the Mirroring over CAN isn't supported. */
      }
      /* CHECK: PARSE */
      /* !LINKSTO Mirror.ASR44.SWS_Mirror_00013,1 */
      Mirror_IsActive = FALSE;
      Mirror_IsTransmitting = FALSE;
      Mirror_InitBuffStatus();
      Mirror_InitQueueStatus();
      Mirror_InitSrcNetworkStatus();
      Mirror_InitState = MIRROR_INITIALIZED;
  }
  else
  {
#if(MIRROR_DEV_ERROR_DETECT == STD_ON)
      /* !LINKSTO Mirror.ASR44.SWS_Mirror_00005,1 */
      /* The Mirror is already initiallized */
      MIRROR_DET_REPORT_ERROR(MIRROR_SID_INIT, MIRROR_E_REINIT);
#endif /* MIRROR_DEV_ERROR_DETECT */
  }
  DBG_MIRROR_INIT_EXIT(config);
}

/* !LINKSTO Mirror.ASR44.SWS_Mirror_01004,1 */
FUNC(void, MIRROR_CODE) Mirror_DeInit
(
  void
)
{
  uint8 NetworkIndex =0U;
  DBG_MIRROR_DEINIT_ENTRY();
  #if(MIRROR_DEV_ERROR_DETECT == STD_ON)
  if(MIRROR_NOT_INITIALIZED == Mirror_InitState)
  {
      /* !LINKSTO Mirror.ASR44.SWS_Mirror_00004,1 */
      /* The Mirror is not initiallized */
      MIRROR_DET_REPORT_ERROR(MIRROR_SID_DEINIT, MIRROR_E_UNINIT);
  }
  else
#endif /* MIRROR_DEV_ERROR_DETECT */
  {
      /* !LINKSTO Mirror.ASR44.SWS_Mirror_00003,1 */
  /* Disable all source networks (That are enabled)*/
      for(NetworkIndex = (uint8) 0U; NetworkIndex < (uint8)MIRROR_NO_OF_SOURCENETWORKS; NetworkIndex++)
      {
          if(TRUE == Mirror_SourceNetworkStatus[NetworkIndex].IsSourceNetworkStarted)
          {
              Mirror_SourceNetworkActivateInternal(NetworkIndex, FALSE);
          }
          else
          {
              /* Do nothing */
          }
          Atomics_Store(&Mirror_SourceNetworkStatus[NetworkIndex].SourceNetworkRequestedActivationStatus, (Atomic_value_t)MIRROR_SOURCENETWORK_NO_REQUEST);
      }
      Mirror_IsActive = FALSE;
      Mirror_InitState = MIRROR_NOT_INITIALIZED;
      DBG_MIRROR_DEINIT_EXIT();
  }
}

/* !LINKSTO Mirror.EB.StartAllSourceNetworks,1 */
FUNC(Std_ReturnType, MIRROR_CODE) Mirror_StartAllSourceNetworks
(
  void
)
{
  Std_ReturnType retVal = E_NOT_OK;
  DBG_MIRROR_STARTALLSOURCENETWORKS_ENTRY();
#if(MIRROR_DEV_ERROR_DETECT == STD_ON)
  if(MIRROR_NOT_INITIALIZED == Mirror_InitState)
  {
      /* !LINKSTO Mirror.ASR44.SWS_Mirror_00004,1 */
      /* The Mirror is not initiallized */
      MIRROR_DET_REPORT_ERROR(MIRROR_SID_STARTALLSOURCENETWORKS, MIRROR_E_UNINIT);
  }
  else
#endif /* MIRROR_DEV_ERROR_DETECT */
  {
      if (TRUE == Mirror_OfflineRequest)
      {
          /* do nothing and skip as the Mirror should be in offline mode */
      }
      else
      {
          uint8 NetworkIndex= (uint8) 0U;
          for(NetworkIndex = (uint8) 0U; NetworkIndex < (uint8)MIRROR_NO_OF_SOURCENETWORKS; NetworkIndex++)
          {
              Atomics_Store(&Mirror_SourceNetworkStatus[NetworkIndex].SourceNetworkRequestedActivationStatus, (Atomic_value_t)MIRROR_SOURCENETWORK_START_REQUESTED);
          }
          retVal = E_OK;
      }
  }
  DBG_MIRROR_STARTALLSOURCENETWORKS_EXIT();
  return retVal;
}

/* !LINKSTO Mirror.EB.StopAllSourceNetworks,1 */
FUNC(Std_ReturnType, MIRROR_CODE) Mirror_StopAllSourceNetworks
(
  void
)
{
  Std_ReturnType retVal = E_NOT_OK;
  DBG_MIRROR_STOPALLSOURCENETWORKS_ENTRY();
#if(MIRROR_DEV_ERROR_DETECT == STD_ON)
  if(MIRROR_NOT_INITIALIZED == Mirror_InitState)
  {
      /* !LINKSTO Mirror.ASR44.SWS_Mirror_00004,1 */
      /* The Mirror is not initiallized */
      MIRROR_DET_REPORT_ERROR(MIRROR_SID_STOPALLSOURCENETWORKS, MIRROR_E_UNINIT);
  }
  else
#endif /* MIRROR_DEV_ERROR_DETECT */
  {
      if (TRUE == Mirror_OfflineRequest)
      {
          /* do nothing and skip as the Mirror should be in offline mode */
      }
      else
      {
          uint8 NetworkIndex= (uint8) 0U;
          for(NetworkIndex = (uint8) 0U; NetworkIndex < (uint8)MIRROR_NO_OF_SOURCENETWORKS; NetworkIndex++)
          {
              Atomics_Store(&Mirror_SourceNetworkStatus[NetworkIndex].SourceNetworkRequestedActivationStatus, (Atomic_value_t)MIRROR_SOURCENETWORK_STOP_REQUESTED);
          }
          retVal = E_OK;
      }
  }
  DBG_MIRROR_STOPALLSOURCENETWORKS_EXIT();
  return retVal;
}

/* !LINKSTO Mirror.ASR44.SWS_Mirror_01019,1 */
FUNC(Std_ReturnType, MIRROR_CODE) Mirror_StartSourceNetwork
(
  VAR(NetworkHandleType, TYPEDEF) network
)
{
  Std_ReturnType retVal = E_NOT_OK;
  DBG_MIRROR_STARTSOURCENETWORK_ENTRY(network);
#if(MIRROR_DEV_ERROR_DETECT == STD_ON)
  if(MIRROR_NOT_INITIALIZED == Mirror_InitState)
  {
      /* !LINKSTO Mirror.ASR44.SWS_Mirror_00004,1 */
      /* The Mirror is not initiallized */
      MIRROR_DET_REPORT_ERROR(MIRROR_SID_STARTSOURCENETWORK, MIRROR_E_UNINIT);
  }
  else
#endif /* MIRROR_DEV_ERROR_DETECT */
  {
      uint8 NetworkIndex = (uint8) 0U;
      if(TRUE == Mirror_FindSrcNetwork(network, &NetworkIndex))
      {
          if (TRUE == Mirror_OfflineRequest)
          {
              /* do nothing and skip as the Mirror should be in offline mode */
          }
          else
          {
              /* !LINKSTO Mirror.ASR44.SWS_Mirror_00019.AsyncStartCanNetwork,1 */
              /* !LINKSTO Mirror.ASR44.SWS_Mirror_00027.AsyncStartLinNetwork,1 */
              Atomics_Store(&Mirror_SourceNetworkStatus[NetworkIndex].SourceNetworkRequestedActivationStatus, (Atomic_value_t)MIRROR_SOURCENETWORK_START_REQUESTED);
              retVal = E_OK;
          }
      }
      else
      {
#if(MIRROR_DEV_ERROR_DETECT == STD_ON)
          /* !LINKSTO Mirror.ASR44.SWS_Mirror_00138,1 */
          /* The ComM network handle ID entered isn't valid */
          MIRROR_DET_REPORT_ERROR(MIRROR_SID_STARTSOURCENETWORK, MIRROR_E_INVALID_NETWORK_ID);
#endif /* MIRROR_DEV_ERROR_DETECT */
      }
  }
  DBG_MIRROR_STARTSOURCENETWORK_EXIT(network);
  return retVal;
}

/* !LINKSTO Mirror.ASR44.SWS_Mirror_01020,1 */
FUNC(Std_ReturnType, MIRROR_CODE) Mirror_StopSourceNetwork
(
  VAR(NetworkHandleType, TYPEDEF) network
)
{
  Std_ReturnType retVal = E_NOT_OK;
  DBG_MIRROR_STOPSOURCENETWORK_ENTRY(network);
#if(MIRROR_DEV_ERROR_DETECT == STD_ON)
  if(MIRROR_NOT_INITIALIZED == Mirror_InitState)
  {
      /* !LINKSTO Mirror.ASR44.SWS_Mirror_00004,1 */
      /* The Mirror is not initiallized */
      MIRROR_DET_REPORT_ERROR(MIRROR_SID_STOPSOURCENETWORK, MIRROR_E_UNINIT);
  }
  else
#endif /* MIRROR_DEV_ERROR_DETECT */
  {
      uint8 NetworkIndex = (uint8) 0U;
      if(TRUE == Mirror_FindSrcNetwork(network, &NetworkIndex))
      {
          if (TRUE == Mirror_OfflineRequest)
          {
              /* do nothing and skip as the Mirror should be in offline mode */
          }
          else
          {
              /* !LINKSTO Mirror.ASR44.SWS_Mirror_00020.AsyncStopCanNetwork,1 */
              /* !LINKSTO Mirror.ASR44.SWS_Mirror_00028.AsyncStopLinNetwork,1 */
              Atomics_Store(&Mirror_SourceNetworkStatus[NetworkIndex].SourceNetworkRequestedActivationStatus, (Atomic_value_t)MIRROR_SOURCENETWORK_STOP_REQUESTED);
              retVal = E_OK;
          }
      }
      else
      {
#if(MIRROR_DEV_ERROR_DETECT == STD_ON)
          /* !LINKSTO Mirror.ASR44.SWS_Mirror_00138,1 */
          /* The ComM network handle ID entered isn't valid */
          MIRROR_DET_REPORT_ERROR(MIRROR_SID_STOPSOURCENETWORK, MIRROR_E_INVALID_NETWORK_ID);
#endif /* MIRROR_DEV_ERROR_DETECT */
      }
  }
  DBG_MIRROR_STOPSOURCENETWORK_EXIT(network);
  return retVal;
}

/* !LINKSTO Mirror.ASR44.SWS_Mirror_01014,1 */
FUNC(boolean, MIRROR_CODE) Mirror_IsMirrorActive
(
  void
)
{
  boolean retVal = FALSE;
  DBG_MIRROR_ISMIRRORACTIVE_ENTRY();
#if(MIRROR_DEV_ERROR_DETECT == STD_ON)
  if(MIRROR_NOT_INITIALIZED == Mirror_InitState)
  {
      /* !LINKSTO Mirror.ASR44.SWS_Mirror_00004,1 */
      /* The Mirror is not initiallized */
      MIRROR_DET_REPORT_ERROR(MIRROR_SID_ISMIRRORACTIVE, MIRROR_E_UNINIT);
  }
  else
#endif /* MIRROR_DEV_ERROR_DETECT */
  {
      retVal = Mirror_IsActive;
  }
  DBG_MIRROR_ISMIRRORACTIVE_EXIT();
  return retVal;
}

/* !LINKSTO Mirror.ASR44.SWS_Mirror_01016,1 */
FUNC(NetworkHandleType, MIRROR_CODE) Mirror_GetDestNetwork
(
  void
)
{
  uint8 DestNetworkIdx = (uint8)MIRROR_INITIAL_DEST_NETWORK_IDX;
  NetworkHandleType retVal = (NetworkHandleType)0xFF;
  DBG_MIRROR_GETDESTNETWORK_ENTRY();
#if(MIRROR_DEV_ERROR_DETECT == STD_ON)
  if(MIRROR_NOT_INITIALIZED == Mirror_InitState)
  {
      /* !LINKSTO Mirror.ASR44.SWS_Mirror_00004,1 */
      /* The Mirror is not initiallized */
      MIRROR_DET_REPORT_ERROR(MIRROR_SID_GETDESTINATIONNETWORK, MIRROR_E_UNINIT);
  }
  else
#endif /* MIRROR_DEV_ERROR_DETECT */
  {
      retVal = Mirror_DestNetworks[DestNetworkIdx].ComMChannelId;
  }
  DBG_MIRROR_GETDESTNETWORK_EXIT();
  return retVal;
}

/* !LINKSTO Mirror.ASR44.SWS_Mirror_01015,1 */
FUNC(void, MIRROR_CODE) Mirror_Offline
(
  void
)
{
  DBG_MIRROR_OFFLINE_ENTRY();
#if(MIRROR_DEV_ERROR_DETECT == STD_ON)
  if(MIRROR_NOT_INITIALIZED == Mirror_InitState)
  {
      /* !LINKSTO Mirror.ASR44.SWS_Mirror_00004,1 */
      /* The Mirror is not initiallized */
      MIRROR_DET_REPORT_ERROR(MIRROR_SID_OFFLINE, MIRROR_E_UNINIT);
  }
  else
#endif /* MIRROR_DEV_ERROR_DETECT */
  {
      /* !LINKSTO Mirror.ASR44.SWS_Mirror_00012.Offline.DestNetworkReset,1 */
      Mirror_DestNetworkIdxRequired = MIRROR_INITIAL_DEST_NETWORK_IDX;
      Mirror_OfflineRequest = TRUE;
  }
  DBG_MIRROR_OFFLINE_EXIT();
}

/* !LINKSTO Mirror.ASR44.SWS_Mirror_01018,1 */
FUNC(boolean, MIRROR_CODE) Mirror_IsSourceNetworkStarted
(
  VAR(NetworkHandleType, TYPEDEF) network
)
{
  boolean ISNetworkStarted = FALSE;
  uint8 NetworkIndex = (uint8) 0U;
  DBG_MIRROR_ISSOURCENETWORKSTARTED_ENTRY();
#if(MIRROR_DEV_ERROR_DETECT == STD_ON)
  if(MIRROR_NOT_INITIALIZED == Mirror_InitState)
  {
      /* !LINKSTO Mirror.ASR44.SWS_Mirror_00004,1 */
      /* The Mirror is not initiallized */
      MIRROR_DET_REPORT_ERROR(MIRROR_SID_ISSOURCENETWORKSTARTED, MIRROR_E_UNINIT);
  }
  else
#endif /* MIRROR_DEV_ERROR_DETECT */
  {
      if(TRUE == Mirror_FindSrcNetwork(network, &NetworkIndex))
      {
          ISNetworkStarted = Mirror_SourceNetworkStatus[NetworkIndex].IsSourceNetworkStarted;
      }
      else
      {
#if(MIRROR_DEV_ERROR_DETECT == STD_ON)
          /* The network ID entered isn't valid */
          /* !LINKSTO Mirror.ASR44.SWS_Mirror_00138,1 */
          MIRROR_DET_REPORT_ERROR(MIRROR_SID_ISSOURCENETWORKSTARTED, MIRROR_E_INVALID_NETWORK_ID);
#endif /* MIRROR_DEV_ERROR_DETECT */
      }
  }
  DBG_MIRROR_ISSOURCENETWORKSTARTED_EXIT();
  return ISNetworkStarted;
}

/* !LINKSTO Mirror.ASR44.SWS_Mirror_01021,1 */
FUNC(Mirror_NetworkType, MIRROR_CODE) Mirror_GetNetworkType
(
  VAR(NetworkHandleType, TYPEDEF) network
)
{
  Mirror_NetworkType NetworkType = (NetworkHandleType)MIRROR_NT_INVALID;
  uint8 NetworkIndex = (uint8)0U;
  DBG_MIRROR_GETNETWORKTYPE_ENTRY(network);
#if(MIRROR_DEV_ERROR_DETECT == STD_ON)
  if(MIRROR_NOT_INITIALIZED == Mirror_InitState)
  {
      /* !LINKSTO Mirror.ASR44.SWS_Mirror_00004,1 */
      /* The Mirror is not initiallized */
      MIRROR_DET_REPORT_ERROR(MIRROR_SID_GETNETWORKTYPE, MIRROR_E_UNINIT);
  }
  else
#endif /* MIRROR_DEV_ERROR_DETECT */
  {
      if(TRUE == Mirror_FindSrcNetwork(network, &NetworkIndex))
      {
          NetworkType = Mirror_SourceNetworks[NetworkIndex].NetworkType;
      }
      else if(TRUE == Mirror_FindDestNetwork(network, &NetworkIndex))
      {
          NetworkType = Mirror_DestNetworks[NetworkIndex].NetworkType;
      }
      else
      {
#if(MIRROR_DEV_ERROR_DETECT == STD_ON)
          /* The network ID entered isn't valid */
          /* !LINKSTO Mirror.ASR44.SWS_Mirror_00138,1 */
          MIRROR_DET_REPORT_ERROR(MIRROR_SID_GETNETWORKTYPE, MIRROR_E_INVALID_NETWORK_ID);
#endif /* MIRROR_DEV_ERROR_DETECT */
      }
  }
  DBG_MIRROR_GETNETWORKTYPE_EXIT(network);
  return NetworkType;
}

/* !LINKSTO Mirror.ASR44.SWS_Mirror_01022,1 */
FUNC(uint8, MIRROR_CODE) Mirror_GetNetworkId
(
  VAR(NetworkHandleType, TYPEDEF) network
)
{
  uint8 NetworkId = (uint8)MIRROR_INVALID_MIRROR_ID;
  uint8 NetworkIndex = (uint8)0U;
  DBG_MIRROR_GETNETWORKID_ENTRY(network);
#if(MIRROR_DEV_ERROR_DETECT == STD_ON)
  if(MIRROR_NOT_INITIALIZED == Mirror_InitState)
  {
      /* !LINKSTO Mirror.ASR44.SWS_Mirror_00004,1 */
      /* The Mirror is not initiallized */
      MIRROR_DET_REPORT_ERROR(MIRROR_SID_GETNETWORKID, MIRROR_E_UNINIT);
  }
  else
#endif /* MIRROR_DEV_ERROR_DETECT */
  {
      if(TRUE == Mirror_FindSrcNetwork(network, &NetworkIndex))
      {
          NetworkId = Mirror_SourceNetworks[NetworkIndex].MirrorNetworkId;
      }
      else if(TRUE == Mirror_FindDestNetwork(network, &NetworkIndex))
      {
          NetworkId = Mirror_DestNetworks[NetworkIndex].MirrorNetworkId;
      }
      else
      {
#if(MIRROR_DEV_ERROR_DETECT == STD_ON)
          /* The network ID entered isn't valid */
          /* !LINKSTO Mirror.ASR44.SWS_Mirror_00138,1 */
          MIRROR_DET_REPORT_ERROR(MIRROR_SID_GETNETWORKID, MIRROR_E_INVALID_NETWORK_ID);
#endif /* MIRROR_DEV_ERROR_DETECT */
      }
  }
  DBG_MIRROR_GETNETWORKID_EXIT(network);
  return NetworkId;
}

/* !LINKSTO Mirror.ASR44.SWS_Mirror_01023,1 */
FUNC(NetworkHandleType, MIRROR_CODE) Mirror_GetNetworkHandle
(
  VAR(Mirror_NetworkType, TYPEDEF) networkType,
  VAR(uint8, TYPEDEF) networkId
)
{
  NetworkHandleType NetworkHandle = (Mirror_NetworkType)MIRROR_INVALID_NETWORK;
  boolean IsNetworkFound = FALSE;
  uint8 Index = (uint8)0x00;
  DBG_MIRROR_GETNETWORKHANDLE_ENTRY(networkType, networkId);
#if(MIRROR_DEV_ERROR_DETECT == STD_ON)
  if(MIRROR_NOT_INITIALIZED == Mirror_InitState)
  {
      /* !LINKSTO Mirror.ASR44.SWS_Mirror_00004,1 */
      /* The Mirror is not initiallized */
      MIRROR_DET_REPORT_ERROR(MIRROR_SID_GETNETWORKHANDLE, MIRROR_E_UNINIT);
  }
  else
#endif /* MIRROR_DEV_ERROR_DETECT */
  {
      /* Check source networks */
      while ((Index < (uint8)MIRROR_NO_OF_SOURCENETWORKS) && (FALSE == IsNetworkFound))
      {
          if(((Mirror_SourceNetworks[Index].MirrorNetworkId) == networkId) && (Mirror_SourceNetworks[Index].NetworkType == networkType))
          {
              IsNetworkFound = TRUE;
              NetworkHandle = Mirror_SourceNetworks[Index].ComMChannelId;
          }
          else
          {
              /* Do nothing and try the next iteration*/
          }
          Index++;
      }
      /* Check destination networks */
      Index = (uint8)0x00;
      while ((Index < (uint8)MIRROR_NO_OF_DESTNETWORKS) && (FALSE == IsNetworkFound))
      {
          if(((Mirror_DestNetworks[Index].MirrorNetworkId) == networkId) && (Mirror_DestNetworks[Index].NetworkType == networkType))
          {
              IsNetworkFound = TRUE;
              NetworkHandle = Mirror_DestNetworks[Index].ComMChannelId;
          }
          else
          {
              /* Do nothing and try the next iteration*/
          }
          Index++;
      }
#if(MIRROR_DEV_ERROR_DETECT == STD_ON)
      if(FALSE == IsNetworkFound)
      {
          /* The network ID entered isn't valid */
          /* !LINKSTO Mirror.ASR44.SWS_Mirror_00138,1 */
          MIRROR_DET_REPORT_ERROR(MIRROR_SID_GETNETWORKHANDLE, MIRROR_E_INVALID_NETWORK_ID);
      }
      else
      {
          /* The network is found */
      }
#endif /* MIRROR_DEV_ERROR_DETECT */
  }
  DBG_MIRROR_GETNETWORKHANDLE_EXIT(networkType, networkId);
  return NetworkHandle;
}

/* !LINKSTO Mirror.ASR44.SWS_Mirror_01030,1 */
FUNC(void, MIRROR_CODE) Mirror_MainFunction
(
  void
)
{
  DBG_MIRROR_MAINFUNCTION_ENTRY();
  if(MIRROR_NOT_INITIALIZED == Mirror_InitState)
  {
      /* The Mirror is not initiallized so it will return*/
  }
  else if(TRUE == Mirror_OfflineRequest)
  {
      /* The offline mode has been requested via Mirror_Offline() or Mirror_SwitchDestNetwork() */
      Mirror_OfflineInternal();
  }
  else
  {
      Std_ReturnType BuffStatus = E_OK;
      boolean CanElementReady = FALSE;
      boolean CanFDElementReady = FALSE;
      boolean LinElementReady = FALSE;
      uint8 SrcNtwrkIdx = (uint8)0x00;
#if(MIRROR_CAN_SOURCENETWORK == STD_ON)
  CanElementReady = (boolean)((uint8)MIRROR_ELEMENT_WRITING_FINISHED == Mirror_CanElement[Mirror_CanElementReadIndex].ElementStatus);
  if(TRUE == CanElementReady)
  {
      /* Do nothing */
  }
  else
  {
      CanElementReady = (boolean)((uint8)MIRROR_ELEMENT_WRITING_FINISHED == Mirror_CanElement[Mirror_CanElementReadIndex].ElementStatus);
  }
#endif /* MIRROR_CAN_SOURCENETWORK == STD_ON */

#if(MIRROR_CANFD_SOURCENETWORK == STD_ON)
  CanFDElementReady = (boolean)((uint8)MIRROR_ELEMENT_WRITING_FINISHED == Mirror_CanFDElement[Mirror_CanFDElementReadIndex].ElementStatus);
  if(TRUE == CanFDElementReady)
  {
      /* Do nothing */
  }
  else
  {
      CanFDElementReady = (boolean)((uint8)MIRROR_ELEMENT_WRITING_FINISHED == Mirror_CanFDElement[Mirror_CanFDElementReadIndex].ElementStatus);
  }
#endif /* MIRROR_CANFD_SOURCENETWORK == STD_ON */

#if(MIRROR_LIN_SOURCENETWORK == STD_ON)
  LinElementReady = (boolean)((uint8)MIRROR_ELEMENT_WRITING_FINISHED == Mirror_LinElement[Mirror_LinElementReadIndex].ElementStatus);
  if(TRUE == LinElementReady)
  {
      /* Do nothing */
  }
  else
  {
      LinElementReady = (boolean)((uint8)MIRROR_ELEMENT_WRITING_FINISHED == Mirror_LinElement[Mirror_LinElementReadIndex].ElementStatus);
  }
#endif /* MIRROR_LIN_SOURCENETWORK == STD_ON */
      /* Check if there is a request to start or stop a source network */
      Mirror_CheckSourceNetworksActivation();
      /* Check the status of the source networks */
      Mirror_CheckSourceBusesStatus();
      /* Check if any element is written in the internal buffers that waits to be copied in the main function to the queue*/
      if((TRUE == CanElementReady)||((TRUE == CanFDElementReady))||((TRUE == LinElementReady)))
      {
          switch (Mirror_QueueBufferStatus[Mirror_ActiveQueueBuffer].QueueBuffStatus)
          {
              case (uint8)MIRROR_QUEUE_BUFFER_NOT_ACTIVE:
              case (uint8)MIRROR_QUEUE_BUFFER_ACTIVE:
              {
                  BuffStatus = Mirror_CopyFrames();
              }
              break;
              case (uint8)MIRROR_QUEUE_BUFFER_TRANSMIT_REQUESTED:
              case (uint8)MIRROR_QUEUE_BUFFER_TRANSMITTING:
              {
#if(MIRROR_DEV_ERROR_DETECT == STD_ON)
                  /* !LINKSTO Mirror.ASR44.SWS_Mirror_00004,1 */
                  /* The queue buffer has no space while there are frames in the internal buffer needs to be copied. */
                  MIRROR_DET_REPORT_ERROR(MIRROR_SID_MAINFUNCTION, MIRROR_E_QUEUE_OVERRUN);
#endif /* MIRROR_DEV_ERROR_DETECT */
                  BuffStatus = E_NOT_OK;
              }
              break;
              /* CHECK: NOPARSE */
              default:
              {
#if(MIRROR_DEV_ERROR_DETECT == STD_ON)
                  /* This case can't happen only put for MISRA warning. */
                  /* unreachable code. */
                  MIRROR_UNREACHABLE_CODE_ASSERT(MIRROR_SID_MAINFUNCTION);
#endif /* MIRROR_DEV_ERROR_DETECT */
                  BuffStatus = E_NOT_OK;
                  break;
              }
              /* CHECK: PARSE */
          }
      }
      else
      {
          /* Do nothing no elements are received to be copied. */
      }
      /* Check if a new element with only the status of the network needs to be transmitted. */
      if (E_OK == BuffStatus)
      {
          /* !LINKSTO Mirror.ASR44.SWS_Mirror_00047,1 */
          (void)CopyStatusBytes();
      }
      else
      {
          /* Don't copy the status byte as no buffer is avialable. */
      }
      /* Clear the lost frame bit from the networks that had them set and were reported above during the copying of the frames. */
      for(SrcNtwrkIdx = (uint8)0x00; SrcNtwrkIdx < (uint8)MIRROR_NO_OF_SOURCENETWORKS; SrcNtwrkIdx += (uint8)0x01)
      {
          if((TRUE == (MIRROR_IS_LOST_FRAME_BIT_SET(Mirror_SourceNetworkStatus[SrcNtwrkIdx].SourceNetworkOldStatusByte))) &&
             (TRUE == Mirror_SourceNetworkStatus[SrcNtwrkIdx].IsStatusReported))
          {
              (MIRROR_CLEAR_LOST_FRAME_BIT(Mirror_SourceNetworkStatus[SrcNtwrkIdx].SourceNetworkCurrentStatusByte));
          }
          else
          {
              /* Do nothing */
          }
          Mirror_SourceNetworkStatus[SrcNtwrkIdx].IsStatusReported = FALSE;
      }
      /* Check the timing of the queue buffers */
      /* !LINKSTO Mirror.ASR44.SWS_Mirror_00006,1 */
      QueueTimingOperations();
  }
  DBG_MIRROR_MAINFUNCTION_EXIT();
}

/* !LINKSTO Mirror.ASR44.SWS_Mirror_01028,1 */
FUNC(void, MIRROR_CODE) Mirror_TxConfirmation
(
  PduIdType TxPduId
)
{
    DBG_MIRROR_TXCONFIRMATION_ENTRY(TxPduId);
#if(MIRROR_DEV_ERROR_DETECT == STD_ON)
  if(MIRROR_NOT_INITIALIZED == Mirror_InitState)
  {
      /* !LINKSTO Mirror.ASR44.SWS_Mirror_00004,1 */
      /* The Mirror is not initiallized */
      MIRROR_DET_REPORT_ERROR(MIRROR_SID_TXCONFIRMATION, MIRROR_E_UNINIT);
  }
  else
#endif /* MIRROR_DEV_ERROR_DETECT */
  {
      uint8 DestNetworkIdx = (uint8)0x00;
      boolean IsNetworkFound = FALSE;
      /* Check if the PduId entered is mapped to a destination network. */
      while ((FALSE == IsNetworkFound) && (DestNetworkIdx < (uint8) MIRROR_NO_OF_DESTNETWORKS))
      {
          if(TxPduId == Mirror_DestNetworks[DestNetworkIdx].DestNetworkPduId)
          {
              IsNetworkFound = TRUE;
          }
          else
          {
              /* Do nothing and check the next destination network. */
          }
          DestNetworkIdx += (uint8)0x01;
      }
      DestNetworkIdx -= (uint8)0x01;
      if (FALSE == IsNetworkFound)
      {
          /* The PduId isn't maped to any destination network. */
          /* !LINKSTO Mirror.ASR44.SWS_Mirror_00137.TxConfirmation,1 */
#if(MIRROR_DEV_ERROR_DETECT == STD_ON)
          MIRROR_DET_REPORT_ERROR(MIRROR_SID_TXCONFIRMATION, MIRROR_E_INVALID_PDU_SDU_ID);
#endif /* MIRROR_DEV_ERROR_DETECT */
      }
      else
      {
          /* The PduId maps to a destination network. */
          if(DestNetworkIdx != Mirror_ActiveDestination)
          {
              /* The destination network was changed before the TxConfirmation so do nothing. */
          }
          else
          {
              if (TRUE == Mirror_OfflineRequest)
              {
                  /*The Mirror should be in offline mode. */
                  Mirror_IsTransmitting = FALSE;
              }
              else
              {
                  /* There is no offline request for the Mirror module .*/
                  if((uint8)MIRROR_QUEUE_BUFFER_TRANSMITTING == Mirror_QueueBufferStatus[Mirror_TxQueueBuffer].QueueBuffStatus)
                  {
                      /* !LINKSTO Mirror.ASR44.SWS_Mirror_00152.TxConfirmation,1 */
                      Mirror_QueueBufferStatus[Mirror_TxQueueBuffer].QueueBuffStatus = (uint8)MIRROR_QUEUE_BUFFER_NOT_ACTIVE;
                      Mirror_QueueBufferStatus[Mirror_TxQueueBuffer].MirroredSourceNetworksCount = (uint8)0x00;
                      if(((uint8)MIRROR_QUEUE_BUFFER_TRANSMIT_REQUESTED == Mirror_QueueBufferStatus[Mirror_NextTxQueueBuffer].QueueBuffStatus) && ((Atomic_t)0x00 != Mirror_QueueBufferStatus[Mirror_TxQueueBuffer].TxTimer))
                      {
                          /* If TxTimer is 0 then that means the Mirror_TxConfirmation() preempted the Mirror_MainFunction()
                             when the TxTimer was 0 meaning the error regarding TxConfirmation timeout should be fired. */
                          Mirror_QueueBufferStatus[Mirror_TxQueueBuffer].TxTimer = (Atomic_t)MIRROR_TRANSMISSIONDEADLINE_DISABLED;
                          /* There is a buffer that needs to be transmitted. */
                          /* !LINKSTO Mirror.ASR44.SWS_Mirror_00053,1 */
                          Mirror_TransmitQueueBuffer
                          (
#if(MIRROR_DEV_ERROR_DETECT == STD_ON)
                            (uint8)MIRROR_SID_TXCONFIRMATION
#endif /* MIRROR_DEV_ERROR_DETECT */
                          );
                      }
                      else
                      {
                          /* no frame to be transmitted */
                          /* CHECK: NOPARSE */
                          if((Atomic_t)0x00 != Mirror_QueueBufferStatus[Mirror_TxQueueBuffer].TxTimer)
                          {
                              Mirror_QueueBufferStatus[Mirror_TxQueueBuffer].TxTimer = (Atomic_t)MIRROR_TRANSMISSIONDEADLINE_DISABLED;
                          }
                          else
                          {
                              /* This case can't happen unless the TxConfirmation preempts the Mirror_MainFunction while the TxTimer = 0
                                 and the state of the queue buffer is MIRROR_QUEUE_BUFFER_TRANSMIT_REQUESTED*/
                              /* Do nothing */
                          }
                          /* CHECK: PARSE */
                          Mirror_IsTransmitting = FALSE;
                      }
                  }
                  else
                  {
                      /* Do nothing. */
                  }
              }
          }
      }
  }
}

FUNC(void, COM_CODE) Mirror_PduRIfRxIndication
(
   PduIdType MirrorRxPduId,
   P2VAR(PduInfoType, AUTOMATIC, COM_APPL_DATA) PduInfoPtr
)
{
  TS_PARAM_UNUSED(MirrorRxPduId);
  TS_PARAM_UNUSED(PduInfoPtr);

#if(MIRROR_DEV_ERROR_DETECT == STD_ON)
  MIRROR_DET_REPORT_ERROR(MIRROR_SID_PDURIFRXINDICATION,MIRROR_E_INVALID_CALL);
#endif /* MIRROR_DEV_ERROR_DETECT == STD_ON */
}
#define MIRROR_STOP_SEC_CODE
#include <Mirror_MemMap.h>

/* !LINKSTO Mirror.ASR44.SWS_Mirror_01024,1 */
#if(MIRROR_CAN_SOURCENETWORK == STD_ON)

#define MIRROR_START_SEC_CAN_CODE
#include <Mirror_MemMap.h>

FUNC(void, MIRROR_CODE) Mirror_ReportCanFrame
(
  VAR(uint8, TYPEDEF) controllerId,
  VAR(Can_IdType, TYPEDEF) canId,
  VAR(uint8, TYPEDEF) length,
  P2CONST(uint8, AUTOMATIC, MIRROR_APPL_DATA) payload
)
{
  DBG_MIRROR_REPORTCANFRAME_ENTRY(controllerId, canId, length, payload);
#if(MIRROR_DEV_ERROR_DETECT == STD_ON)
  if(MIRROR_NOT_INITIALIZED == Mirror_InitState)
  {
      /* !LINKSTO Mirror.ASR44.SWS_Mirror_00004,1 */
      /* The Mirror is not initiallized */
      MIRROR_DET_REPORT_ERROR(MIRROR_SID_REPORTCANFRAME, MIRROR_E_UNINIT);
  }
  else
#endif /* MIRROR_DEV_ERROR_DETECT */
  {
      if(NULL_PTR == payload)
      {
#if(MIRROR_DEV_ERROR_DETECT == STD_ON)
          /*The payload pointer is NULL*/
          /* !LINKSTO Mirror.ASR44.SWS_Mirror_00007,1 */
          MIRROR_DET_REPORT_ERROR(MIRROR_SID_REPORTCANFRAME, MIRROR_E_PARAM_POINTER);
#endif /* MIRROR_DEV_ERROR_DETECT */
      }
      else
      {
          uint8 SrcNtwrkIdx = (uint8)0U;
          /*Get the source network from the Controller ID*/
          if(TRUE != Mirror_FindCanSourceNetwork(controllerId, &SrcNtwrkIdx))
          {
#if(MIRROR_DEV_ERROR_DETECT == STD_ON)
              /* The source network isn't found */
              /* !LINKSTO Mirror.EB.InvalidNetworkId,1 */
              MIRROR_DET_REPORT_ERROR(MIRROR_SID_REPORTCANFRAME, MIRROR_E_INVALID_NETWORK_ID);
#endif /* MIRROR_DEV_ERROR_DETECT */
          }
          else if (FALSE != Mirror_ReportingCanFrame)
          {
              /* !LINKSTO Mirror.EB.NestedReportFrameReportDet,1 */
#if(MIRROR_DEV_ERROR_DETECT == STD_ON)
              MIRROR_DET_REPORT_ERROR(MIRROR_SID_REPORTCANFRAME, MIRROR_E_NESTED_REPORT_FRAMES);
#endif /* MIRROR_DEV_ERROR_DETECT */
              /* !LINKSTO Mirror.EB.NestedReportFrameLostFrame,1 */
              MIRROR_SET_LOST_FRAME_BIT(Mirror_SourceNetworkStatus[SrcNtwrkIdx].SourceNetworkCurrentStatusByte);
          }
          else
          {
              if(FALSE == Mirror_SourceNetworkStatus[SrcNtwrkIdx].IsSourceNetworkStarted)
              {
                  /*Ignore the frame the network should be stopped*/
              }
              else
              {
                  if(TRUE == Mirror_OfflineRequest)
                  {
                      /*Do nothing this frame should be dropped*/
                  }
                  else
                  {
#if(MIRROR_DEV_ERROR_DETECT == STD_ON)
                      Mirror_ReportingCanFrame = TRUE;
#endif /* MIRROR_DEV_ERROR_DETECT */
                      /*Check the frame type if CAN 2.0 or CANFD*/
                      /* !LINKSTO Mirror.ASR44.SWS_Mirror_00021.ReportCanFrame,1 */
                      if((Can_IdType)MIRROR_CAN_NETWORK == (Can_IdType)MIRROR_CHECK_CANID_TYPE(canId))
                      {
                          /*Can 2.0*/
                          if((uint8)MIRROR_CAN_FRAME_SIZE >= length)
                          {
                               Mirror_StoreCanFrame(SrcNtwrkIdx, canId, length, payload);
                          }
                          else
                          {
#if(MIRROR_DEV_ERROR_DETECT == STD_ON)
                              /* The reported frame length is larger than the maximum length configured. */
                              /* !LINKSTO Mirror.EB.InvalidPduLength,1 */
                              MIRROR_DET_REPORT_ERROR(MIRROR_SID_REPORTCANFRAME, MIRROR_E_INVALID_PARAM);
#endif /* MIRROR_DEV_ERROR_DETECT */
                          }
                      }
                      else
                      {
#if(MIRROR_CANFD_SOURCENETWORK == STD_ON)
                          /*Can FD*/
                          if((uint8)MIRROR_CANFD_FRAME_SIZE >= length)
                          {
                              Mirror_StoreCanFDFrame(SrcNtwrkIdx, canId, length, payload);
                          }
                          else
                          {
#if(MIRROR_DEV_ERROR_DETECT == STD_ON)
                              /* The reported frame length is larger than the maximum length configured. */
                              /* !LINKSTO Mirror.EB.InvalidPduLength,1 */
                              MIRROR_DET_REPORT_ERROR(MIRROR_SID_REPORTCANFRAME, MIRROR_E_INVALID_PARAM);
#endif /* MIRROR_DEV_ERROR_DETECT */
                          }
#endif /* MIRROR_CANFD_SOURCENETWORK == STD_ON */
                      }
#if(MIRROR_DEV_ERROR_DETECT == STD_ON)
                      Mirror_ReportingCanFrame = FALSE;
#endif /* MIRROR_DEV_ERROR_DETECT */
                  }
              }
          }
      }
  }
  DBG_MIRROR_REPORTCANFRAME_EXIT(controllerId, canId, length, payload);
}

#define MIRROR_STOP_SEC_CAN_CODE
#include <Mirror_MemMap.h>

#endif /* MIRROR_CAN_SOURCENETWORK == STD_ON */

/* !LINKSTO Mirror.ASR44.SWS_Mirror_01027,1 */
#if(MIRROR_LIN_SOURCENETWORK == STD_ON)

#define MIRROR_START_SEC_LIN_CODE
#include <Mirror_MemMap.h>

FUNC(void, MIRROR_CODE) Mirror_ReportLinFrame
(
  VAR(NetworkHandleType, TYPEDEF) network,
  VAR(Lin_FramePidType, TYPEDEF) pid,
  P2CONST(PduInfoType, AUTOMATIC, MIRROR_APPL_DATA) pdu,
  VAR(Lin_StatusType, TYPEDEF) status
)
{
  DBG_MIRROR_REPORTLINFRAME_ENTRY(network, pid, pdu, status);
#if(MIRROR_DEV_ERROR_DETECT == STD_ON)
  if(MIRROR_NOT_INITIALIZED == Mirror_InitState)
  {
      /* !LINKSTO Mirror.ASR44.SWS_Mirror_00004,1 */
      /* The Mirror is not initiallized */
      MIRROR_DET_REPORT_ERROR(MIRROR_SID_REPORTLINFRAME, MIRROR_E_UNINIT);
  }
  else
#endif /* MIRROR_DEV_ERROR_DETECT */
  {
      uint8 SrcNtwrkIdx = (uint8)0U;
      /*Get the source network from the ComM handle ID*/
      if(TRUE != Mirror_FindLinSourceNetwork(network, &SrcNtwrkIdx))
      {
#if(MIRROR_DEV_ERROR_DETECT == STD_ON)
          /*The source network isn't found*/
          /* !LINKSTO Mirror.EB.InvalidNetworkId,1 */
          MIRROR_DET_REPORT_ERROR(MIRROR_SID_REPORTLINFRAME, MIRROR_E_INVALID_NETWORK_ID);
#endif /* MIRROR_DEV_ERROR_DETECT */
      }
      else if (FALSE != Mirror_ReportingLinFrame)
      {
          /* !LINKSTO Mirror.EB.NestedReportFrameReportDet,1 */
#if(MIRROR_DEV_ERROR_DETECT == STD_ON)
          MIRROR_DET_REPORT_ERROR(MIRROR_SID_REPORTLINFRAME, MIRROR_E_NESTED_REPORT_FRAMES);
#endif /* MIRROR_DEV_ERROR_DETECT */
          /* !LINKSTO Mirror.EB.NestedReportFrameLostFrame,1 */
          MIRROR_SET_LOST_FRAME_BIT(Mirror_SourceNetworkStatus[SrcNtwrkIdx].SourceNetworkCurrentStatusByte);
      }
      else
      {
          if(TRUE == Mirror_OfflineRequest)
          {
              /*Do nothing this frame or status should be dropped*/
          }
          else
          {
              if(FALSE == Mirror_SourceNetworkStatus[SrcNtwrkIdx].IsSourceNetworkStarted)
              {
                  /*Ignore the frame the network should be stopped*/
              }
              else
              {
                  if((NULL_PTR != pdu) && ((uint8)MIRROR_LIN_FRAME_SIZE < (pdu->SduLength)))
                  {
#if(MIRROR_DEV_ERROR_DETECT == STD_ON)
                      /* The reported frame length is larger than the maximum length configured. */
                      /* !LINKSTO Mirror.EB.InvalidPduLength,1 */
                      MIRROR_DET_REPORT_ERROR(MIRROR_SID_REPORTLINFRAME, MIRROR_E_INVALID_PARAM);
#endif /* MIRROR_DEV_ERROR_DETECT */
                  }
                  else
                  {
#if(MIRROR_DEV_ERROR_DETECT == STD_ON)
                      Mirror_ReportingLinFrame = TRUE;
#endif /* MIRROR_DEV_ERROR_DETECT */
                      Mirror_StoreLinFrame(pid,pdu,status,SrcNtwrkIdx);
#if(MIRROR_DEV_ERROR_DETECT == STD_ON)
                      Mirror_ReportingLinFrame = FALSE;
#endif /* MIRROR_DEV_ERROR_DETECT */
                  }
              }
          }
      }
  }
  DBG_MIRROR_REPORTLINFRAME_EXIT(network, pid, pdu, status);
}

#define MIRROR_STOP_SEC_LIN_CODE
#include <Mirror_MemMap.h>

#endif /* MIRROR_LIN_SOURCENETWORK == STD_ON */

/*==================[internal function definitions]=========================*/
#define MIRROR_START_SEC_CODE
#include <Mirror_MemMap.h>

static FUNC(void, MIRROR_CODE) Mirror_SourceNetworkActivateInternal
(
  VAR(uint8, MIRROR_VAR) SourceNetworkIdx,
  VAR(boolean, MIRROR_VAR) MirrorActive
)
{
  VAR(uint8, TYPEDEF) ControllerIndex = Mirror_SourceNetworks[SourceNetworkIdx].SourceNetworkControllerIndex;
  switch (Mirror_SourceNetworks[SourceNetworkIdx].NetworkType)
  {
#if(MIRROR_CAN_SOURCENETWORK == STD_ON)
    case (Mirror_NetworkType)MIRROR_NT_CAN:
    {
        for(ControllerIndex = Mirror_SourceNetworks[SourceNetworkIdx].SourceNetworkControllerIndex; ControllerIndex < (uint8)(Mirror_SourceNetworks[SourceNetworkIdx].SourceNetworkControllerIndex + Mirror_SourceNetworks[SourceNetworkIdx].NumOfSourceNetworkControllers); ControllerIndex++)
        {
            /* !LINKSTO Mirror.ASR44.SWS_Mirror_00019.AsyncStartCanNetwork,1 */
            /* !LINKSTO Mirror.ASR44.SWS_Mirror_00020.AsyncStopCanNetwork,1 */
#if(MIRROR_CANIPCSUPPORT == STD_ON)
            Std_ReturnType retVal = E_OK;
            (void)SchM_Call_Mirror_CanIf_EnableBusMirroring(&retVal, Mirror_SourceNetworkControllers[ControllerIndex],MirrorActive);
#else
            (void)CanIf_EnableBusMirroring(Mirror_SourceNetworkControllers[ControllerIndex],MirrorActive);
#endif /* MIRROR_CANIPCSUPPORT == STD_ON */
        }
        break;
    }
#endif /* MIRROR_CAN_SOURCENETWORK == STD_ON */

#if(MIRROR_LIN_SOURCENETWORK == STD_ON)
    case (Mirror_NetworkType)MIRROR_NT_LIN:
    {
        /* !LINKSTO Mirror.ASR44.SWS_Mirror_00027.AsyncStartLinNetwork,1 */
        /* !LINKSTO Mirror.ASR44.SWS_Mirror_00028.AsyncStopLinNetwork,1 */
#if(MIRROR_LINIPCSUPPORT == STD_ON)
        Std_ReturnType retVal = E_OK;
        (void)SchM_Call_Mirror_LinIf_EnableBusMirroring(&retVal, (NetworkHandleType)Mirror_SourceNetworkControllers[ControllerIndex], MirrorActive);
#else
        (void)LinIf_EnableBusMirroring((NetworkHandleType)Mirror_SourceNetworkControllers[ControllerIndex], MirrorActive);
#endif /* MIRROR_LINIPCSUPPORT == STD_ON */
        break;
    }
#endif /* MIRROR_LIN_SOURCENETWORK == STD_ON */

    /* CHECK: NOPARSE */
    default:
    {
        MIRROR_UNREACHABLE_CODE_ASSERT(MIRROR_SID_MAINFUNCTION);
        /* Put for MISRA. */
        break;
    }
    /* CHECK: PARSE */
  }
  Mirror_SourceNetworkStatus[SourceNetworkIdx].IsSourceNetworkStarted = MirrorActive;
}

static FUNC(boolean, MIRROR_CODE) Mirror_FindSrcNetwork
(
  VAR(NetworkHandleType, TYPEDEF) network,
  P2VAR(uint8, AUTOMATIC, MIRROR_APPL_DATA) NetworkIndexPtr
)
{
  boolean IsNetworkFound = FALSE;
  uint8 Index = (uint8)0U;
  while ((Index < (uint8)MIRROR_NO_OF_SOURCENETWORKS) && (FALSE == IsNetworkFound))
  {
      if((Mirror_SourceNetworks[Index].ComMChannelId) == network)
      {
          *NetworkIndexPtr = Index;
          IsNetworkFound = TRUE;
      }
      else
      {
          /* Do nothing and try the next iteration*/
      }
      Index++;
  }
  return IsNetworkFound;
}

static FUNC(boolean, MIRROR_CODE) Mirror_FindDestNetwork
(
  VAR(NetworkHandleType, TYPEDEF) network,
  P2VAR(uint8, AUTOMATIC, MIRROR_APPL_DATA) NetworkIndexPtr
)
{
  boolean IsNetworkFound = FALSE;
  uint8 Index = (uint8)0U;
  while ((Index < (uint8)MIRROR_NO_OF_DESTNETWORKS) && (FALSE == IsNetworkFound))
  {
      if((Mirror_DestNetworks[Index].ComMChannelId) == network)
      {
          *NetworkIndexPtr = Index;
          IsNetworkFound = TRUE;
      }
      else
      {
          /* Do nothing and try the next iteration*/
      }
      Index++;
  }
  return IsNetworkFound;
}

static FUNC(void, MIRROR_CODE) Mirror_InitBuffStatus
(
  void
)
{
  uint32 ElementCounter = 0U;
#if (MIRROR_LIN_SOURCENETWORK == STD_ON)
  for(ElementCounter = 0U; ElementCounter < MIRROR_LIN_ELEMENTCOUNTER; ElementCounter++)
  {
      Mirror_LinElement[ElementCounter].ElementStatus = MIRROR_ELEMENT_AVAILABLE;
  }
  Atomics_Store(&Mirror_LinElementWriteIndex, (Atomic_value_t)0);
  Mirror_LinElementReadIndex = (uint32)0U;
  Mirror_ReportingLinFrame = FALSE;
#endif /* MIRROR_LIN_SOURCENETWORK == STD_ON */

#if (MIRROR_CAN_SOURCENETWORK == STD_ON)
  for(ElementCounter = 0U; ElementCounter < MIRROR_CAN_ELEMENTCOUNTER; ElementCounter++)
  {
      Mirror_CanElement[ElementCounter].ElementStatus = MIRROR_ELEMENT_AVAILABLE;
  }
  Atomics_Store(&Mirror_CanElementWriteIndex, (Atomic_value_t)0);
  Mirror_CanElementReadIndex = (uint32)0U;
  Mirror_ReportingCanFrame = FALSE;
#endif /* MIRROR_CAN_SOURCENETWORK == STD_ON */

#if (MIRROR_CANFD_SOURCENETWORK == STD_ON)
  for(ElementCounter = 0U; ElementCounter < MIRROR_CANFD_ELEMENTCOUNTER; ElementCounter++)
  {
      Mirror_CanFDElement[ElementCounter].ElementStatus = MIRROR_ELEMENT_AVAILABLE;
  }
  Atomics_Store(&Mirror_CanFDElementWriteIndex, (Atomic_value_t)0);
  Mirror_CanFDElementReadIndex = (uint32)0U;
#endif /* MIRROR_CANFD_SOURCENETWORK == STD_ON */
}

static FUNC(void, MIRROR_CODE) Mirror_SendActivationFrame
(
  void
)
{
  uint32 BuffIndex = (uint32)((uint32)Mirror_DestNetworks[Mirror_ActiveDestination].DestNetworkPduLength * (uint32)Mirror_ActiveQueueBuffer);
  MIRROR_USERDATA_TYPE Mirror_UserData;
  /* Get the time of the initialization */
  MIRROR_GET_TIME_STAMP(&RefTimeStamp, &Mirror_UserData);
  /* Write the header of the init frame (The frame only consists of a header) */
  Mirror_WriteFrameHeader();
  TxPduInfo.SduDataPtr = &TxBuffer[BuffIndex];
  TxPduInfo.SduLength = (PduLengthType)Mirror_QueueBufferStatus[Mirror_ActiveQueueBuffer].FrameLength;
  Mirror_TxQueueBuffer = Mirror_NextTxQueueBuffer;
  if(E_NOT_OK ==  PduR_MirrorTransmit(Mirror_DestNetworks[Mirror_ActiveDestination].DestNetworkSrcPduRId, &TxPduInfo))
  {
      /* The transmission failed so leave the status of the Queue to be NOT_ACTIVE and raise a DET error*/
#if(MIRROR_DEV_ERROR_DETECT == STD_ON)
      /* !LINKSTO Mirror.ASR44.SWS_Mirror_00150,1 */
      /* The Mirror trasnmission failed */
      MIRROR_DET_REPORT_ERROR(MIRROR_SID_MAINFUNCTION, MIRROR_E_TRANSMIT_FAILED);
      /*Set the buffer status to Not active*/
      Mirror_QueueBufferStatus[Mirror_ActiveQueueBuffer].QueueBuffStatus = (uint8)MIRROR_QUEUE_BUFFER_NOT_ACTIVE;
#endif /* MIRROR_DEV_ERROR_DETECT */
  }
  else
  {
      /* The transmission succeeded */
      Mirror_IsTransmitting = TRUE;
      Mirror_NextTxQueueBuffer = (Mirror_NextTxQueueBuffer + (uint16)1U) % Mirror_DestNetworks[Mirror_ActiveDestination].DestQueueSizeRange;
      Mirror_QueueBufferStatus[Mirror_ActiveQueueBuffer].QueueBuffStatus = (uint8)MIRROR_QUEUE_BUFFER_TRANSMITTING;
      Mirror_QueueBufferStatus[Mirror_ActiveQueueBuffer].TxTimer = (Atomic_t)Mirror_DestNetworks[Mirror_ActiveDestination].DestTxConfirmationTimeout + (Atomic_t)1;
      Mirror_ActiveQueueBuffer = (Mirror_ActiveQueueBuffer + (uint16)1U) % Mirror_DestNetworks[Mirror_ActiveDestination].DestQueueSizeRange;
  }
}

static FUNC (void, MIRROR_CODE) Mirror_InitQueueStatus
(
  void
)
{
  uint16 Mirror_queueIndex = (uint16)0U;
  for(Mirror_queueIndex = 0U; Mirror_queueIndex < MIRROR_MAX_QUEUE_SIZE; Mirror_queueIndex++)
  {
      Mirror_QueueBufferStatus[Mirror_queueIndex].TxTimer = (Atomic_t)0U;
      Mirror_QueueBufferStatus[Mirror_queueIndex].FrameLength = (uint16)0U;
      Mirror_QueueBufferStatus[Mirror_queueIndex].QueueBuffStatus = (uint8)MIRROR_QUEUE_BUFFER_NOT_ACTIVE;
      Mirror_QueueBufferStatus[Mirror_queueIndex].MirroredSourceNetworksCount = (uint8)0x00;
  }
  Mirror_ActiveQueueBuffer = (uint16)0U;
  Mirror_NextTxQueueBuffer = (uint16)0x00;
  Mirror_TxQueueBuffer = (uint16)0x00;
  TxPduInfo.SduDataPtr = NULL_PTR;
  TxPduInfo.SduLength = (PduLengthType)0U;
}

static FUNC(void, MIRROR_CODE) Mirror_InitSrcNetworkStatus
(
  void
)
{
  uint8 NetworkIndex = 0U;
  for(NetworkIndex = 0U; NetworkIndex < MIRROR_NO_OF_SOURCENETWORKS; NetworkIndex++)
  {
      Mirror_SourceNetworkStatus[NetworkIndex].SourceNetworkRequestedActivationStatus = (Atomic_t)MIRROR_SOURCENETWORK_NO_REQUEST;
      Mirror_SourceNetworkStatus[NetworkIndex].IsSourceNetworkStarted = FALSE;
      Mirror_SourceNetworkStatus[NetworkIndex].IsStatusReported = FALSE;
      Mirror_SourceNetworkStatus[NetworkIndex].SourceNetworkCurrentStatusByte = (uint8)0U;
      Mirror_SourceNetworkStatus[NetworkIndex].SourceNetworkOldStatusByte = (uint8)0U;
  }
}

static FUNC (void, MIRROR_CODE) Mirror_OfflineInternal
(
  void
)
{
  uint8 NetworkIndex= (uint8) 0U;
  /* discared all the received frames waiting to be mirrored*/
  /* !LINKSTO Mirror.ASR44.SWS_Mirror_00012.Offline.DiscardFrames,1 */
  Mirror_InitBuffStatus();
  Mirror_InitQueueStatus();
  /* Disable all source networks (That are enabled)*/
  /* !LINKSTO Mirror.ASR44.SWS_Mirror_00012.Offline.SourceBusses,1 */
  for(NetworkIndex = (uint8) 0U; NetworkIndex < (uint8)MIRROR_NO_OF_SOURCENETWORKS; NetworkIndex++)
  {
      if(TRUE == Mirror_SourceNetworkStatus[NetworkIndex].IsSourceNetworkStarted)
      {
          Mirror_SourceNetworkActivateInternal(NetworkIndex, FALSE);
      }
      else
      {
          /* Do nothing */
      }
      Atomics_Store(&Mirror_SourceNetworkStatus[NetworkIndex].SourceNetworkRequestedActivationStatus, (Atomic_value_t)MIRROR_SOURCENETWORK_NO_REQUEST);
  }
  /* Set the destination network to be the chosen one from the Mirror_Offline() or Mirror_SwitchDestNetwork() */
  /* !LINKSTO Mirror.ASR44.SWS_Mirror_00012.Offline.DestNetworkReset,1 */
  Mirror_ActiveDestination = Mirror_DestNetworkIdxRequired;
  Mirror_IsActive = FALSE;
  Mirror_OfflineRequest = FALSE;
  Mirror_IsTransmitting = FALSE;
}

static FUNC (void, MIRROR_CODE) Mirror_CheckSourceNetworksActivation
(
  void
)
{
  uint8 NetworkIndex = (uint8)0U;
  for(NetworkIndex = (uint8)0U; NetworkIndex < (uint8)MIRROR_NO_OF_SOURCENETWORKS; NetworkIndex++)
  {
      Atomic_value_t ReqActivationStatus = Atomics_Load(&Mirror_SourceNetworkStatus[NetworkIndex].SourceNetworkRequestedActivationStatus);
      switch (ReqActivationStatus)
      {
          /* !LINKSTO Mirror.ASR44.SWS_Mirror_00014.AsyncStartSourceNetwork,1 */
          case (Atomic_value_t)MIRROR_SOURCENETWORK_START_REQUESTED:
          {
              Atomic_t ResActivationStatus = (Atomic_t)MIRROR_SOURCENETWORK_START_REQUESTED;
              Mirror_SourceNetworkActivateInternal(NetworkIndex, TRUE);
              (void)Atomics_CompareExchange(&Mirror_SourceNetworkStatus[NetworkIndex].SourceNetworkRequestedActivationStatus, &ResActivationStatus, (Atomic_value_t)MIRROR_SOURCENETWORK_NO_REQUEST);
              Mirror_SourceNetworkStatus[NetworkIndex].SourceNetworkCurrentStatusByte = (uint8)0x00;
              Mirror_SourceNetworkStatus[NetworkIndex].SourceNetworkOldStatusByte = (uint8)0xFF;
              if(FALSE == Mirror_IsActive)
              {
                  /* First activation of the Mirror module */
                  /* !LINKSTO Mirror.EB.ActivationFrame,1 */
                  Mirror_SendActivationFrame();
                  Mirror_IsActive = TRUE;
              }
              else
              {
                  /* do nothing */
              }
          }
          break;
          /* !LINKSTO Mirror.ASR44.SWS_Mirror_00015.AsyncStopSourceNetwork,1 */
          case (Atomic_value_t)MIRROR_SOURCENETWORK_STOP_REQUESTED:
          {
              Atomic_t ResActivationStatus = (Atomic_t)MIRROR_SOURCENETWORK_STOP_REQUESTED;
              Mirror_SourceNetworkActivateInternal(NetworkIndex, FALSE);
              (void)Atomics_CompareExchange(&Mirror_SourceNetworkStatus[NetworkIndex].SourceNetworkRequestedActivationStatus, &ResActivationStatus, (Atomic_value_t)MIRROR_SOURCENETWORK_NO_REQUEST);
          }
          break;
          case MIRROR_SOURCENETWORK_NO_REQUEST:
          default:
          {
              /* Do nothing */
              break;
          }
      }
  }
}

 static FUNC (void, MIRROR_CODE) Mirror_CheckSourceBusesStatus
(
  void
)
{
  uint8 NetworkIndex = (uint8)0U;
  for(NetworkIndex = (uint8)0U; NetworkIndex < (uint8)MIRROR_NO_OF_SOURCENETWORKS; NetworkIndex++)
  {
      if (TRUE == Mirror_SourceNetworkStatus[NetworkIndex].IsSourceNetworkStarted)
      {
          switch (Mirror_SourceNetworks[NetworkIndex].NetworkType)
          {
#if(MIRROR_CAN_SOURCENETWORK == STD_ON)
              case (Mirror_NetworkType)MIRROR_NT_CAN:
              {
                  /* The Mirror considers the CAN source network to have a single controller but in the CANSM it might have more.*/
                  /* Only the first controller is uset to get the status. */
                  Can_ControllerStateType ControllerStatus = CAN_CS_STARTED;
                  CanTrcv_TrcvModeType TrcvStatus = CANTRCV_TRCVMODE_NORMAL;
                  Can_ErrorStateType ErrorStatus = CAN_ERRORSTATE_ACTIVE;
                  boolean IsNetworkOnline = FALSE;
#if(MIRROR_CANIPCSUPPORT == STD_ON)
                  Std_ReturnType retVal = E_OK;
                  (void)SchM_Call_Mirror_CanIf_GetControllerMode(&retVal, Mirror_SourceNetworkControllers[Mirror_SourceNetworks[NetworkIndex].SourceNetworkControllerIndex], &ControllerStatus);
#else
                  (void)CanIf_GetControllerMode(Mirror_SourceNetworkControllers[Mirror_SourceNetworks[NetworkIndex].SourceNetworkControllerIndex], &ControllerStatus);
#endif /* MIRROR_CANIPCSUPPORT == STD_ON */
#if(MIRROR_CANTRCV == STD_ON)
                  /* !LINKSTO Mirror.EB.CanSrcNtwrkNoTrcv,1 */
                  /* !LINKSTO Mirror.ASR44.SWS_Mirror_00026,1 */
                  if((FALSE == Mirror_SourceNetworks[NetworkIndex].TrcvConfigured) || (CAN_CS_STARTED != ControllerStatus))
                  {
                      /* Do nothing */
                  }
                  else
                  {
#if(MIRROR_CANIPCSUPPORT == STD_ON)
                      (void)SchM_Call_Mirror_CanIf_GetTrcvMode(&retVal ,Mirror_SourceNetworks[NetworkIndex].TrcvId, &TrcvStatus);
#else
                      (void)CanIf_GetTrcvMode(Mirror_SourceNetworks[NetworkIndex].TrcvId, &TrcvStatus);
#endif /* MIRROR_CANIPCSUPPORT == STD_ON */
                  }
#endif /* MIRROR_CANTRCV == STD_ON */
                  if((CAN_CS_STARTED == ControllerStatus) && (CANTRCV_TRCVMODE_NORMAL == TrcvStatus))
                  {
                      IsNetworkOnline = TRUE;
                      /* !LINKSTO Mirror.ASR44.SWS_Mirror_00080,1 */
                      MIRROR_SET_BUS_ONLINE_BIT(Mirror_SourceNetworkStatus[NetworkIndex].SourceNetworkCurrentStatusByte);
                  }
                  else
                  {
                      IsNetworkOnline = FALSE;
                      /* The network status will be offline and the bit status will be set as offline */
                  }
                  if(TRUE == IsNetworkOnline)
                  {
                      uint8 TxErrorCounter = (uint8)0U;
#if(MIRROR_CANIPCSUPPORT == STD_ON)
                      (void)SchM_Call_Mirror_CanIf_GetControllerErrorState(&retVal, Mirror_SourceNetworkControllers[Mirror_SourceNetworks[NetworkIndex].SourceNetworkControllerIndex], &ErrorStatus);
#else
                      (void)CanIf_GetControllerErrorState(Mirror_SourceNetworkControllers[Mirror_SourceNetworks[NetworkIndex].SourceNetworkControllerIndex], &ErrorStatus);
#endif /* MIRROR_CANIPCSUPPORT == STD_ON */
                      switch (ErrorStatus)
                      {
                          case CAN_ERRORSTATE_PASSIVE:
                          {
                            /* !LINKSTO Mirror.ASR44.SWS_Mirror_00081,1 */
                            MIRROR_CAN_SET_ERROR_PASSIVE_BIT(Mirror_SourceNetworkStatus[NetworkIndex].SourceNetworkCurrentStatusByte);
                            MIRROR_CAN_CLEAR_BUS_OFF_BIT(Mirror_SourceNetworkStatus[NetworkIndex].SourceNetworkCurrentStatusByte);
                          }
                          break;
                          case CAN_ERRORSTATE_BUSOFF:
                          {
                            /* !LINKSTO Mirror.ASR44.SWS_Mirror_00082,1 */
                            MIRROR_CAN_SET_BUS_OFF_BIT(Mirror_SourceNetworkStatus[NetworkIndex].SourceNetworkCurrentStatusByte);
                            MIRROR_CAN_CLEAR_ERROR_PASSIVE_BIT(Mirror_SourceNetworkStatus[NetworkIndex].SourceNetworkCurrentStatusByte);
                          }
                          break;
                          case CAN_ERRORSTATE_ACTIVE:
                          {
                            MIRROR_CAN_SET_ERROR_ACTIVE(Mirror_SourceNetworkStatus[NetworkIndex].SourceNetworkCurrentStatusByte);
                          }
                          break;
                          /* CHECK: NOPARSE */
                          default:
                          {
                              MIRROR_UNREACHABLE_CODE_ASSERT(MIRROR_SID_MAINFUNCTION);
                              /* Put for MISRA */
                              break;
                          }
                          /* CHECK: PARSE */
                      }
#if(MIRROR_CANIPCSUPPORT == STD_ON)
                      (void)SchM_Call_Mirror_CanIf_GetControllerTxErrorCounter(&retVal, Mirror_SourceNetworkControllers[Mirror_SourceNetworks[NetworkIndex].SourceNetworkControllerIndex], &TxErrorCounter);
#else
                      (void)CanIf_GetControllerTxErrorCounter(Mirror_SourceNetworkControllers[Mirror_SourceNetworks[NetworkIndex].SourceNetworkControllerIndex], &TxErrorCounter);
#endif /* MIRROR_CANIPCSUPPORT == STD_ON */
                      MIRROR_CAN_TXERROR_COUNTER_CASTING(TxErrorCounter);
                      MIRROR_CAN_CLEAR_TXERROR_COUNTER(Mirror_SourceNetworkStatus[NetworkIndex].SourceNetworkCurrentStatusByte);
                      /* !LINKSTO Mirror.ASR44.SWS_Mirror_00083,1 */
                      MIRROR_CAN_SET_TXERROR_COUNTER(Mirror_SourceNetworkStatus[NetworkIndex].SourceNetworkCurrentStatusByte,TxErrorCounter);
                  }
                  else
                  {
                      /* The network is not online so the status bits will be cleared except the lost frame bit*/
                      MIRROR_CAN_SET_BUS_OFFLINE(Mirror_SourceNetworkStatus[NetworkIndex].SourceNetworkCurrentStatusByte);
                  }
              }
              break;
#endif /* MIRROR_CAN_SOURCENETWORK == STD_ON */
#if(MIRROR_LIN_SOURCENETWORK == STD_ON)
              case (Mirror_NetworkType)MIRROR_NT_LIN:
              {
                  /* !LINKSTO Mirror.ASR44.SWS_Mirror_00035,1 */
                  LinTrcv_TrcvModeType TrcvStatus = LINTRCV_TRCV_MODE_NORMAL;
#if(MIRROR_LINTRCV == STD_ON)
                  /* !LINKSTO Mirror.EB.LinSrcNtwrkNoTrcv,1 */
                  if(FALSE == Mirror_SourceNetworks[NetworkIndex].TrcvConfigured)
                  {
                      /* Do nothing */
                  }
                  else
                  {
#if(MIRROR_LINIPCSUPPORT == STD_ON)
                      Std_ReturnType retVal = E_OK;
                      (void)SchM_Call_Mirror_LinIf_GetTrcvMode(&retVal, (NetworkHandleType)Mirror_SourceNetworkControllers[Mirror_SourceNetworks[NetworkIndex].SourceNetworkControllerIndex], &TrcvStatus);
#else
                      (void)LinIf_GetTrcvMode((NetworkHandleType)Mirror_SourceNetworkControllers[Mirror_SourceNetworks[NetworkIndex].SourceNetworkControllerIndex], &TrcvStatus);
#endif /* MIRROR_LINIPCSUPPORT == STD_ON */
                  }
#endif /* MIRROR_LINTRCV == STD_ON */
                  if(LINTRCV_TRCV_MODE_NORMAL == TrcvStatus)
                  {
                      /* !LINKSTO Mirror.ASR44.SWS_Mirror_00080,1 */
                      /* !LINKSTO Mirror.ASR44.SWS_Mirror_00084,1 */
                      MIRROR_SET_BUS_ONLINE_BIT(Mirror_SourceNetworkStatus[NetworkIndex].SourceNetworkCurrentStatusByte);
                  }
                  else
                  {
                      MIRROR_CLEAR_BUS_ONLINE_BIT(Mirror_SourceNetworkStatus[NetworkIndex].SourceNetworkCurrentStatusByte);
                  }
              }
              break;
#endif /* MIRROR_LIN_SOURCENETWORK == STD_ON */
              /* CHECK: NOPARSE */
              default:
              {
                /* Unsupported source network type*/
                MIRROR_UNREACHABLE_CODE_ASSERT(MIRROR_SID_MAINFUNCTION);
                break;
              }
              /* CHECK: PARSE */
          }
      }
      else
      {
          /* check the next network as the current network isn't active */
      }
  }
}

/* Deviation MISRAC2012-1 <1> */
static FUNC (void, MIRROR_CODE) Mirror_ActivateQueueBuffer
(
  VAR(boolean, MIRROR_VAR) CanFrameReady,
  VAR(boolean, MIRROR_VAR) CanFDFrameReady,
  VAR(boolean, MIRROR_VAR) LinFrameReady
)
{
  MIRROR_TIMESTAMP_TYPE* CanTimeStamp = NULL_PTR;
  MIRROR_TIMESTAMP_TYPE* CanFDTimeStamp = NULL_PTR;
  MIRROR_TIMESTAMP_TYPE* LinTimeStamp = NULL_PTR;
#if(MIRROR_CAN_SOURCENETWORK == STD_ON)
  if(TRUE == CanFrameReady)
  {
      CanTimeStamp = &Mirror_CanTimeStamp[Mirror_CanElementReadIndex];
  }
  else
  {
      /* Do nothing */
  }
#else
  TS_PARAM_UNUSED(CanFrameReady);
#endif /* MIRROR_CAN_SOURCENETWORK == STD_ON */

#if(MIRROR_CANFD_SOURCENETWORK == STD_ON)
  if(TRUE == CanFDFrameReady)
  {
      CanFDTimeStamp = &Mirror_CanFDTimeStamp[Mirror_CanFDElementReadIndex];
  }
  else
  {
      /* Do nothing */
  }
#else
  TS_PARAM_UNUSED(CanFDFrameReady);
#endif /* MIRROR_CANFD_SOURCENETWORK == STD_ON */

#if(MIRROR_LIN_SOURCENETWORK == STD_ON)
  if(TRUE == LinFrameReady)
  {
      LinTimeStamp = &Mirror_LinTimeStamp[Mirror_LinElementReadIndex];
  }
  else
  {
      /* Do nothing */
  }
#else
  TS_PARAM_UNUSED(LinFrameReady);
#endif /* MIRROR_LIN_SOURCENETWORK == STD_ON */

  /* Get the minimum time stamp from all the buffers that has the status MIRROR_ELEMENT_WRITING_FINISHED*/
  DefaultDataElementMinTime = Mirror_GetMinTimeStamp(CanTimeStamp, CanFDTimeStamp, LinTimeStamp, &RefTimeStamp);
  /* Fill the header of the buffer. */
  Mirror_WriteFrameHeader();
  /* Set the Queue buffer status with Active */
  Mirror_QueueBufferStatus[Mirror_ActiveQueueBuffer].QueueBuffStatus = MIRROR_QUEUE_BUFFER_ACTIVE;
  /* Set the TxTimer with the DestTxDeadline*/
  Mirror_QueueBufferStatus[Mirror_ActiveQueueBuffer].TxTimer = (Atomic_t)Mirror_DestNetworks[Mirror_ActiveDestination].DestTxDeadline;
}

static FUNC (uint8, MIRROR_CODE) Mirror_GetMinTimeStamp
(
  P2CONST(MIRROR_TIMESTAMP_TYPE, AUTOMATIC, MIRROR_APPL_DATA) CanTimeStamp,
  P2CONST(MIRROR_TIMESTAMP_TYPE, AUTOMATIC, MIRROR_APPL_DATA) CanFDTimeStamp,
  P2CONST(MIRROR_TIMESTAMP_TYPE, AUTOMATIC, MIRROR_APPL_DATA) LinTimeStamp,
  P2VAR(MIRROR_TIMESTAMP_TYPE, AUTOMATIC, MIRROR_APPL_DATA) OutputTimeStamp
)
{
  uint8 MinDataElementTime = (uint8)MIRROR_CAN_DATA_ELEMENT;
  if(TRUE == Mirror_TimeStampComparator(CanTimeStamp, CanFDTimeStamp, OutputTimeStamp))
  {
      /* The data element with the min time stamp is a Can data element */
      MinDataElementTime = (uint8)MIRROR_CAN_DATA_ELEMENT;
  }
  else
  {
      /* The data element with the min time stamp is a CanFD data element */
      MinDataElementTime = (uint8)MIRROR_CANFD_DATA_ELEMENT;
  }
  if(TRUE == Mirror_TimeStampComparator(OutputTimeStamp, LinTimeStamp, OutputTimeStamp))
  {
      /* Do nothing as the data element with the min time stamp is the same as above */
  }
  else
  {
      /* The data element with the min time stamp is a Lin data element */
      MinDataElementTime = (uint8)MIRROR_LIN_DATA_ELEMENT;
  }
  return MinDataElementTime;
}

static FUNC (boolean, MIRROR_CODE) Mirror_TimeStampComparator
(
  P2CONST(MIRROR_TIMESTAMP_TYPE, AUTOMATIC, MIRROR_APPL_DATA) TimeStamp_1,
  P2CONST(MIRROR_TIMESTAMP_TYPE, AUTOMATIC, MIRROR_APPL_DATA) TimeStamp_2,
  P2VAR(MIRROR_TIMESTAMP_TYPE, AUTOMATIC, MIRROR_APPL_DATA) MinTimeStamp
)
{
  boolean retVal = TRUE;
  if(NULL_PTR == TimeStamp_2)
  {
      if(NULL_PTR == TimeStamp_1)
      {
          MinTimeStamp->secondsHi = 0xFFFFU;
          MinTimeStamp->seconds = 0xFFFFFFFFU;
          MinTimeStamp->nanoseconds = 0xFFFFFFFFU;
      }
      else
      {
          MinTimeStamp->secondsHi = TimeStamp_1->secondsHi;
          MinTimeStamp->seconds = TimeStamp_1->seconds;
          MinTimeStamp->nanoseconds = TimeStamp_1->nanoseconds;
      }
  }
  else if(NULL_PTR == TimeStamp_1)
  {
      retVal = FALSE;
      MinTimeStamp->secondsHi = TimeStamp_2->secondsHi;
      MinTimeStamp->seconds = TimeStamp_2->seconds;
      MinTimeStamp->nanoseconds = TimeStamp_2->nanoseconds;
  }
  else
  {
      if(TimeStamp_1->secondsHi < TimeStamp_2->secondsHi)
      {
          MinTimeStamp->secondsHi = TimeStamp_1->secondsHi;
          MinTimeStamp->seconds = TimeStamp_1->seconds;
          MinTimeStamp->nanoseconds = TimeStamp_1->nanoseconds;
      }
      else if (TimeStamp_1->secondsHi > TimeStamp_2->secondsHi)
      {
          retVal = FALSE;
          MinTimeStamp->secondsHi = TimeStamp_2->secondsHi;
          MinTimeStamp->seconds = TimeStamp_2->seconds;
          MinTimeStamp->nanoseconds = TimeStamp_2->nanoseconds;
      }
      else
      {
          /*The secondsHi are equal in both time stamps so check the seconds*/
          if(TimeStamp_1->seconds < TimeStamp_2->seconds)
          {
              MinTimeStamp->secondsHi = TimeStamp_1->secondsHi;
              MinTimeStamp->seconds = TimeStamp_1->seconds;
              MinTimeStamp->nanoseconds = TimeStamp_1->nanoseconds;
          }
          else if (TimeStamp_1->seconds > TimeStamp_2->seconds)
          {
              retVal = FALSE;
              MinTimeStamp->secondsHi = TimeStamp_2->secondsHi;
              MinTimeStamp->seconds = TimeStamp_2->seconds;
              MinTimeStamp->nanoseconds = TimeStamp_2->nanoseconds;
          }
          else
          {
              /*The secondsHi and seconds are equal in both time stamps so check the nanoseconds*/
              if(TimeStamp_1->nanoseconds <= TimeStamp_2->nanoseconds)
              {
                  MinTimeStamp->secondsHi = TimeStamp_1->secondsHi;
                  MinTimeStamp->seconds = TimeStamp_1->seconds;
                  MinTimeStamp->nanoseconds = TimeStamp_1->nanoseconds;
              }
              else
              {
                  retVal = FALSE;
                  MinTimeStamp->secondsHi = TimeStamp_2->secondsHi;
                  MinTimeStamp->seconds = TimeStamp_2->seconds;
                  MinTimeStamp->nanoseconds = TimeStamp_2->nanoseconds;
              }
          }
      }
  }
  return retVal;
}

static FUNC (void, MIRROR_CODE) Mirror_WriteFrameHeader
(
  void
)
{
  uint32 BuffIndex = (uint32)((uint32)Mirror_DestNetworks[Mirror_ActiveDestination].DestNetworkPduLength * (uint32)Mirror_ActiveQueueBuffer);
  /* !LINKSTO Mirror.ASR44.SWS_Mirror_00055,1 */
  /* !LINKSTO Mirror.ASR44.SWS_Mirror_00056,1 */
  /* !LINKSTO Mirror.ASR44.SWS_Mirror_00057,1 */
  /*Protocol version*/
  TxBuffer[BuffIndex] = (uint8)1U;
  BuffIndex += (uint32)1U;
  /* Sequence Number */
  TxBuffer[BuffIndex] = Mirror_SequenceNumber;
  BuffIndex += (uint32)1U;
  /* !LINKSTO Mirror.ASR44.SWS_Mirror_00060,1 */
  /* !LINKSTO Mirror.ASR44.SWS_Mirror_00061,1 */
  /* Time stamp secondsHi */
  Mirror_MemCpy16(RefTimeStamp.secondsHi, &TxBuffer[BuffIndex]);
  BuffIndex += (uint32)2U;
  /* Time stamp seconds */
  Mirror_MemCpy32(RefTimeStamp.seconds, &TxBuffer[BuffIndex]);
  BuffIndex += (uint32)4U;
  /* Time stamp nano seconds */
  Mirror_MemCpy32(RefTimeStamp.nanoseconds, &TxBuffer[BuffIndex]);
  BuffIndex += (uint32)4U;
  /* Frame length */
  /* !LINKSTO Mirror.ASR44.SWS_Mirror_00062,1 */
  /* !LINKSTO Mirror.ASR44.SWS_Mirror_00063,1 */
  Mirror_MemCpy16((uint16)0U, &TxBuffer[BuffIndex]);
  Mirror_QueueBufferStatus[Mirror_ActiveQueueBuffer].FrameLength = (uint16)MIRROR_FRAME_HEADER_SIZE;
  /* Increment the sequence number */
  /* !LINKSTO Mirror.ASR44.SWS_Mirror_00058,1 */
  /* !LINKSTO Mirror.ASR44.SWS_Mirror_00059,1 */
  Mirror_SequenceNumber += (uint8)0x01;
}

static FUNC (void, MIRROR_CODE) Mirror_MemCpy16
(
  VAR(uint16, MIRROR_VAR) value,
  P2VAR(uint8, AUTOMATIC, MIRROR_APPL_DATA) dest
)
{
  /* copy the first byte of the 4 bytes */
  *dest = (uint8)((value & (uint16)0xFF00U) >> 8U);
  /* copy the second byte of the 4 bytes */
  /* Deviation MISRAC2012-4 <1> */
  *(dest+1) = (uint8)(value & (uint16)0x00FFU);
}

static FUNC (void, MIRROR_CODE) Mirror_MemCpy32
(
  VAR(uint32, MIRROR_VAR) value,
  P2VAR(uint8, AUTOMATIC, MIRROR_APPL_DATA) dest
)
{
  /* copy the first byte of the 4 bytes */
  *dest = (uint8)((value & (uint32)0xFF000000U) >> 24U);
  /* copy the second byte of the 4 bytes */
  /* Deviation MISRAC2012-4 <1> */
  *(dest+1) = (uint8)((value & (uint32)0x00FF0000U) >> 16U);
  /* copy the third byte of the 4 bytes */
  /* Deviation MISRAC2012-4 <1> */
  *(dest+2) = (uint8)((value & (uint32)0x0000FF00U) >> 8U);
  /* copy the fourth byte of the 4 bytes */
  /* Deviation MISRAC2012-4 <1> */
  *(dest+3) = (uint8)(value & (uint32)0x000000FFU);
}

static FUNC (Std_ReturnType, MIRROR_CODE) Mirror_CopyFrames
(
  void
)
{
  boolean CopySuccess = TRUE;
  boolean FramesRemaining = TRUE;
  Std_ReturnType QueueBuffAvailable = E_OK;
  boolean CanElementReady = FALSE;
  boolean CanFDElementReady = FALSE;
  boolean LinElementReady = FALSE;
#if(MIRROR_CAN_SOURCENETWORK == STD_ON)
  uint32 CanElementCounter = (uint32)MIRROR_CAN_ELEMENTCOUNTER;
#endif /* MIRROR_CAN_SOURCENETWORK == STD_ON */
#if(MIRROR_CANFD_SOURCENETWORK == STD_ON)
  uint32 CanFDElementCounter = (uint32)MIRROR_CANFD_ELEMENTCOUNTER;
#endif /* MIRROR_CANFD_SOURCENETWORK == STD_ON */
#if(MIRROR_LIN_SOURCENETWORK == STD_ON)
  uint32 LinElementCounter = (uint32)MIRROR_LIN_ELEMENTCOUNTER;
#endif /* MIRROR_LIN_SOURCENETWORK == STD_ON */
  while ((E_OK == QueueBuffAvailable) && (TRUE == FramesRemaining))
  {
      CopySuccess = TRUE;
      if((uint8)MIRROR_QUEUE_BUFFER_NOT_ACTIVE == Mirror_QueueBufferStatus[Mirror_ActiveQueueBuffer].QueueBuffStatus)
      {
#if(MIRROR_CAN_SOURCENETWORK == STD_ON)
        CanElementReady = (boolean)((uint8)MIRROR_ELEMENT_WRITING_FINISHED == Mirror_CanElement[Mirror_CanElementReadIndex].ElementStatus);
#endif /* MIRROR_CAN_SOURCENETWORK == STD_ON */
#if(MIRROR_CANFD_SOURCENETWORK == STD_ON)
        CanFDElementReady = (boolean)((uint8)MIRROR_ELEMENT_WRITING_FINISHED == Mirror_CanFDElement[Mirror_CanFDElementReadIndex].ElementStatus);
#endif /* MIRROR_CANFD_SOURCENETWORK == STD_ON */
#if(MIRROR_LIN_SOURCENETWORK == STD_ON)
        LinElementReady = (boolean)((uint8)MIRROR_ELEMENT_WRITING_FINISHED == Mirror_LinElement[Mirror_LinElementReadIndex].ElementStatus);
#endif /* MIRROR_LIN_SOURCENETWORK == STD_ON */
        /* Activate the current queue buffer, copy the frame header and put the data element with the least time stamp in the queue buffer. */
        /* !LINKSTO Mirror.ASR44.SWS_Mirror_00044,1 */
        Mirror_ActivateQueueBuffer(CanElementReady, CanFDElementReady, LinElementReady);
      }
      else
      {
          /* Do nothing, The current buffer is activated. */
      }
      while ((TRUE == CopySuccess) && (TRUE == FramesRemaining))
      {
          FramesRemaining = FALSE;
          /* To copy the data element with the least time first in the queue buffer. */
          /* Deviation MISRAC2012-2 <1> */
          switch (DefaultDataElementMinTime)
          {
              /* !LINKSTO Mirror.ASR44.SWS_Mirror_00045,1 */
              /* Deviation MISRAC2012-3 <1> */
              case (uint8)MIRROR_CAN_DATA_ELEMENT:
              {
#if(MIRROR_CAN_SOURCENETWORK == STD_ON)
                  CanElementReady = (boolean)(((uint8)MIRROR_ELEMENT_WRITING_FINISHED == Mirror_CanElement[Mirror_CanElementReadIndex].ElementStatus) && (CanElementCounter > (uint32)0x00));
                  if((TRUE == CanElementReady) && (TRUE == CopySuccess))
                  {
                      QueueBuffAvailable = Mirror_CopyCurrentCanFrame(&CopySuccess);
                      if(TRUE == CopySuccess)
                      {
                          CanElementCounter -= (uint32)0x01;
                      }
                      else
                      {
                          /* Do nothing as the frame isn't copied to the counter shouldn't be decremented */
                      }
                      FramesRemaining = (FramesRemaining || (((uint8)MIRROR_ELEMENT_WRITING_FINISHED == Mirror_CanElement[Mirror_CanElementReadIndex].ElementStatus) && (CanElementCounter > (uint32)0x00)));
                  }
                  else
                  {
                      /* Do nothing. */
                  }
#endif /* MIRROR_CAN_SOURCENETWORK == STD_ON */
              }
              /* Deviation MISRAC2012-3 <1> */
              case (uint8)MIRROR_CANFD_DATA_ELEMENT:
              {
#if(MIRROR_CANFD_SOURCENETWORK == STD_ON)
                  CanFDElementReady = (boolean)(((uint8)MIRROR_ELEMENT_WRITING_FINISHED == Mirror_CanFDElement[Mirror_CanFDElementReadIndex].ElementStatus) && (CanFDElementCounter > (uint32)0x00));
                  if((TRUE == CanFDElementReady) && (TRUE == CopySuccess))
                  {
                      QueueBuffAvailable = Mirror_CopyCurrentCanFDFrame(&CopySuccess);
                      if(TRUE == CopySuccess)
                      {
                          CanFDElementCounter -= (uint32)0x01;
                      }
                      else
                      {
                          /* Do nothing as the frame isn't copied to the counter shouldn't be decremented */
                      }
                      FramesRemaining = (FramesRemaining || (((uint8)MIRROR_ELEMENT_WRITING_FINISHED == Mirror_CanFDElement[Mirror_CanFDElementReadIndex].ElementStatus) && (CanFDElementCounter > (uint32)0x00)));
                  }
                  else
                  {
                      /* Do nothing. */
                  }
#endif /* MIRROR_CANFD_SOURCENETWORK == STD_ON */
              }
              /* Deviation MISRAC2012-3 <1> */
              case (uint8)MIRROR_LIN_DATA_ELEMENT:
              {
#if(MIRROR_LIN_SOURCENETWORK == STD_ON)
                  LinElementReady = (boolean)(((uint8)MIRROR_ELEMENT_WRITING_FINISHED == Mirror_LinElement[Mirror_LinElementReadIndex].ElementStatus) && (LinElementCounter > (uint32)0x00));
                  if((TRUE == LinElementReady) && (TRUE == CopySuccess))
                  {
                      QueueBuffAvailable = Mirror_CopyCurrentLinFrame(&CopySuccess);
                      if(TRUE == CopySuccess)
                      {
                          LinElementCounter -= (uint32)0x01;
                      }
                      else
                      {
                          /* Do nothing as the frame isn't copied to the counter shouldn't be decremented */
                      }
                      FramesRemaining = (FramesRemaining || (((uint8)MIRROR_ELEMENT_WRITING_FINISHED == Mirror_LinElement[Mirror_LinElementReadIndex].ElementStatus) && (LinElementCounter > (uint32)0x00)));
                  }
                  else
                  {
                      /* Do nothing. */
                  }
#endif /* MIRROR_LIN_SOURCENETWORK == STD_ON */
                  DefaultDataElementMinTime = (uint8)MIRROR_CAN_DATA_ELEMENT;
                  break;
              }
              /* CHECK: NOPARSE */
              default:
              {
#if(MIRROR_DEV_ERROR_DETECT == STD_ON)
                  /* Unreachable code put for MISRA. */
                  MIRROR_UNREACHABLE_CODE_ASSERT(MIRROR_SID_MAINFUNCTION);
#endif /* MIRROR_DEV_ERROR_DETECT */
                  break;
              }
              /* CHECK: PARSE */
          }
      }
  }
  return QueueBuffAvailable;
}

static FUNC (Std_ReturnType, MIRROR_CODE) CopyStatusBytes
(
  void
)
{
  Std_ReturnType retVal = E_OK;
  uint8 Index = (uint8)0x00;
  boolean TimeStampBelowMax = FALSE;
  MIRROR_TIMESTAMP_TYPE StatusTimeStamp;
  MIRROR_USERDATA_TYPE Mirror_UserData;
  MIRROR_GET_TIME_STAMP(&StatusTimeStamp, &Mirror_UserData);
  while ((Index < MIRROR_NO_OF_SOURCENETWORKS) && (E_OK == retVal))
  {
      /* Check if a status byte was not reported in a previous data element that needs to be reported. */
      if((FALSE == Mirror_SourceNetworkStatus[Index].IsStatusReported) && (Mirror_SourceNetworkStatus[Index].SourceNetworkCurrentStatusByte != Mirror_SourceNetworkStatus[Index].SourceNetworkOldStatusByte))
      {
          /* Check if the current queue buffer is active to check the time stamp difference. */
          if((uint8)MIRROR_QUEUE_BUFFER_ACTIVE == Mirror_QueueBufferStatus[Mirror_ActiveQueueBuffer].QueueBuffStatus)
          {
              /* Check the time stamp difference of the current buffer */
              (void)Mirror_TimeStampDiff(&StatusTimeStamp, &TimeStampBelowMax);
              /* !LINKSTO Mirror.ASR44.SWS_Mirror_00049,1 */
              if(FALSE == TimeStampBelowMax)
              {
                  /* The time stamp exceeded the limit so move to the next buffer */
                  Mirror_QueueBufferStatus[Mirror_ActiveQueueBuffer].QueueBuffStatus = (uint8)MIRROR_QUEUE_BUFFER_TRANSMIT_REQUESTED;
                  Mirror_ActiveQueueBuffer = (Mirror_ActiveQueueBuffer + (uint16)1U) % (Mirror_DestNetworks[Mirror_ActiveDestination].DestQueueSizeRange);
              }
              else
              {
                  /* The time stamp is within limits */
              }
          }
          else
          {
              /* Do nothing as the current buffer isn't active. */
          }
          /* if the current buffer can store the current element then check if the next queue can store the element and is active. */
          if(((Mirror_QueueBufferStatus[Mirror_ActiveQueueBuffer].FrameLength + MIRROR_STATUS_ELEMENT_LENGTH) <=
            Mirror_DestNetworks[Mirror_ActiveDestination].DestNetworkPduLength) &&
            ((uint8)MIRROR_QUEUE_BUFFER_ACTIVE == Mirror_QueueBufferStatus[Mirror_ActiveQueueBuffer].QueueBuffStatus))
          {
              /* the buffer has a place to copy the status frame. */
              CopyStatusDataElement(Index, &StatusTimeStamp);
          }
          else
          {
              /* The current can't store the element so check the reason. */
              switch (Mirror_QueueBufferStatus[Mirror_ActiveQueueBuffer].QueueBuffStatus)
              {
                  /* !LINKSTO Mirror.ASR44.SWS_Mirror_00044,1 */
                  case (uint8)MIRROR_QUEUE_BUFFER_NOT_ACTIVE:
                  {
                      /* !LINKSTO Mirror.ASR44.SWS_Mirror_00111,1 */
                      /* Activate the buffer and copy the status data element. */
                      RefTimeStamp.secondsHi = StatusTimeStamp.secondsHi;
                      RefTimeStamp.seconds = StatusTimeStamp.seconds;
                      RefTimeStamp.nanoseconds = StatusTimeStamp.nanoseconds;
                      /* Fill the header of the buffer. */
                      Mirror_WriteFrameHeader();
                      /* Set the Queue buffer status with Active */
                      Mirror_QueueBufferStatus[Mirror_ActiveQueueBuffer].QueueBuffStatus = MIRROR_QUEUE_BUFFER_ACTIVE;
                      /* Set the TxTimer with the DestTxDeadline*/
                      Mirror_QueueBufferStatus[Mirror_ActiveQueueBuffer].TxTimer = (Atomic_t)Mirror_DestNetworks[Mirror_ActiveDestination].DestTxDeadline;
                      /* the buffer has a place to copy the status frame. */
                      CopyStatusDataElement(Index, &StatusTimeStamp);
                  }
                  break;
                  case (uint8)MIRROR_QUEUE_BUFFER_ACTIVE:
                  {
                      /* !LINKSTO Mirror.ASR44.SWS_Mirror_00111,1 */
                      /* The buffer is full so move to the next buffer in the queue*/
                      Mirror_QueueBufferStatus[Mirror_ActiveQueueBuffer].QueueBuffStatus = (uint8)MIRROR_QUEUE_BUFFER_TRANSMIT_REQUESTED;
                      Mirror_ActiveQueueBuffer = (Mirror_ActiveQueueBuffer + (uint16)1U) % (Mirror_DestNetworks[Mirror_ActiveDestination].DestQueueSizeRange);
                      /* Check the next buffer if available then fill the element in the buffer. */
                      if((uint8)MIRROR_QUEUE_BUFFER_NOT_ACTIVE == Mirror_QueueBufferStatus[Mirror_ActiveQueueBuffer].QueueBuffStatus)
                      {
                          /* The buffer is available. */
                          /* Activate the buffer and copy the status data element. */
                          RefTimeStamp.secondsHi = StatusTimeStamp.secondsHi;
                          RefTimeStamp.seconds = StatusTimeStamp.seconds;
                          RefTimeStamp.nanoseconds = StatusTimeStamp.nanoseconds;
                          /* Fill the header of the buffer. */
                          Mirror_WriteFrameHeader();
                          /* Set the Queue buffer status with Active */
                          Mirror_QueueBufferStatus[Mirror_ActiveQueueBuffer].QueueBuffStatus = MIRROR_QUEUE_BUFFER_ACTIVE;
                          /* Set the TxTimer with the DestTxDeadline*/
                          Mirror_QueueBufferStatus[Mirror_ActiveQueueBuffer].TxTimer = (Atomic_t)Mirror_DestNetworks[Mirror_ActiveDestination].DestTxDeadline;
                          /* the buffer has a place to copy the status frame. */
                          CopyStatusDataElement(Index, &StatusTimeStamp);
                      }
                      else
                      {
#if(MIRROR_DEV_ERROR_DETECT == STD_ON)
                          /* !LINKSTO Mirror.ASR44.SWS_Mirror_00004,1 */
                          /* All the Mirror queue buffers are full. */
                          MIRROR_DET_REPORT_ERROR(MIRROR_SID_MAINFUNCTION, MIRROR_E_QUEUE_OVERRUN);
#endif /* MIRROR_DEV_ERROR_DETECT */
                          retVal = E_NOT_OK;
                      }
                  }
                  break;
                  case (uint8)MIRROR_QUEUE_BUFFER_TRANSMIT_REQUESTED:
                  case (uint8)MIRROR_QUEUE_BUFFER_TRANSMITTING:
                  {
#if(MIRROR_DEV_ERROR_DETECT == STD_ON)
                      /* !LINKSTO Mirror.ASR44.SWS_Mirror_00004,1 */
                      /* All the Mirror queue buffers are full. */
                      MIRROR_DET_REPORT_ERROR(MIRROR_SID_MAINFUNCTION, MIRROR_E_QUEUE_OVERRUN);
#endif /* MIRROR_DEV_ERROR_DETECT */
                      retVal = E_NOT_OK;
                  }
                  break;
                  /* CHECK: NOPARSE */
                  default:
                  {
#if(MIRROR_DEV_ERROR_DETECT == STD_ON)
                      /* Unreachable code put for MISRA. */
                      MIRROR_UNREACHABLE_CODE_ASSERT(MIRROR_SID_MAINFUNCTION);
#endif /* MIRROR_DEV_ERROR_DETECT */
                      retVal = E_NOT_OK;
                      break;
                  }
                  /* CHECK: PARSE */
              }
          }
      }
      else
      {
          /* This network has no need to report a status byte. */
      }
      Index += (uint8)1U;
  }
  return retVal;
}

static FUNC (void, MIRROR_CODE) CopyStatusDataElement
(
  VAR(uint8, MIRROR_VAR) SourceNetworkIndex,
  P2CONST(MIRROR_TIMESTAMP_TYPE, AUTOMATIC, MIRROR_APPL_DATA) TimeStamp
)
{
  /* The byte indicating the network type and the availability of the status byte */
  uint8 DataElementAvStatus = (uint8)0U;
  /* The start writing index in the destination frame buffer */
  uint32 BuffIndex = (uint32)(Mirror_QueueBufferStatus[Mirror_ActiveQueueBuffer].FrameLength) + (uint32)((uint32)Mirror_ActiveQueueBuffer * (uint32)(Mirror_DestNetworks[Mirror_ActiveDestination].DestNetworkPduLength));
  boolean TimeStampBelowMax = FALSE;
  /* The time stamp difference */
  uint16 TimeDiff = Mirror_TimeStampDiff(TimeStamp, &TimeStampBelowMax);
  MIRROR_SET_NETWORK_STATE_AVAILABLE(DataElementAvStatus);
  switch (Mirror_SourceNetworks[SourceNetworkIndex].NetworkType)
  {
#if(MIRROR_CAN_SOURCENETWORK == STD_ON)
      /* !LINKSTO Mirror.ASR44.SWS_Mirror_00073,1 */
      /* !LINKSTO Mirror.ASR44.SWS_Mirror_00074,1 */
      case MIRROR_NT_CAN:
      {
          MIRROR_SET_NETWORK_TYPE(DataElementAvStatus,MIRROR_NT_CAN);
      }
      break;
#endif /* MIRROR_CAN_SOURCENETWORK == STD_ON */
#if(MIRROR_LIN_SOURCENETWORK == STD_ON)
      case MIRROR_NT_LIN:
      {
          MIRROR_SET_NETWORK_TYPE(DataElementAvStatus,MIRROR_NT_LIN);
      }
      break;
#endif /* MIRROR_LIN_SOURCENETWORK == STD_ON */
      /* CHECK: NOPARSE */
      default:
      {
          /* impossible to reach here (un supported network type) */
          MIRROR_UNREACHABLE_CODE_ASSERT(MIRROR_SID_MAINFUNCTION);
          break;
      }
      /* CHECK: PARSE */
  }
  /* Time stamp copying */
  Mirror_MemCpy16(TimeDiff, &TxBuffer[BuffIndex]);
  BuffIndex += (uint32)2U;
  /* availability byte copying */
  TxBuffer[BuffIndex] = DataElementAvStatus;
  BuffIndex += (uint32)1;
  /* Network ID copying*/
  /* !LINKSTO Mirror.ASR44.SWS_Mirror_00076,1 */
  TxBuffer[BuffIndex] = Mirror_SourceNetworks[SourceNetworkIndex].MirrorNetworkId;
  BuffIndex += (uint32)1;
  /* Report the status and put the old status as the new status to check again in the next main function */
  Mirror_SourceNetworkStatus[SourceNetworkIndex].SourceNetworkOldStatusByte = Mirror_SourceNetworkStatus[SourceNetworkIndex].SourceNetworkCurrentStatusByte;
  /* !LINKSTO Mirror.ASR44.SWS_Mirror_00077,1 */
  /* !LINKSTO Mirror.ASR44.SWS_Mirror_00078,1 */
  TxBuffer[BuffIndex] = Mirror_SourceNetworkStatus[SourceNetworkIndex].SourceNetworkOldStatusByte;
  /* Increase the frame length by the length of the status data element */
  Mirror_QueueBufferStatus[Mirror_ActiveQueueBuffer].FrameLength += (uint16)MIRROR_STATUS_ELEMENT_LENGTH;
  /* Overwrite the Frame length in the dest frame with the new length after adding the frame*/
  Mirror_MemCpy16((uint16)(Mirror_QueueBufferStatus[Mirror_ActiveQueueBuffer].FrameLength - (uint16)MIRROR_FRAME_HEADER_SIZE), &TxBuffer[MIRROR_DEST_FRAME_DATALENGTH_POSITION]);
  Mirror_SourceNetworkStatus[SourceNetworkIndex].IsStatusReported = TRUE;
  InsertSourceNetworkIndex(SourceNetworkIndex);
}

static FUNC (void, MIRROR_CODE) Mirror_TransmitQueueBuffer
(
#if(MIRROR_DEV_ERROR_DETECT == STD_ON)
  VAR(uint8, MIRROR_VAR) ApiId
#else
  void
#endif /* MIRROR_DEV_ERROR_DETECT */
)
{
  uint32 BuffIndex = (uint32)((uint32)Mirror_NextTxQueueBuffer * (uint32)Mirror_DestNetworks[Mirror_ActiveDestination].DestNetworkPduLength);
  Mirror_TxQueueBuffer = Mirror_NextTxQueueBuffer;
  TxPduInfo.SduDataPtr = &TxBuffer[BuffIndex];
  TxPduInfo.SduLength = (PduLengthType)Mirror_QueueBufferStatus[Mirror_TxQueueBuffer].FrameLength;
  Mirror_NextTxQueueBuffer = (Mirror_NextTxQueueBuffer + (uint16)1U) % Mirror_DestNetworks[Mirror_ActiveDestination].DestQueueSizeRange;
  /* !LINKSTO Mirror.ASR44.SWS_Mirror_00051,1 */
  if(E_NOT_OK == PduR_MirrorTransmit(Mirror_DestNetworks[Mirror_ActiveDestination].DestNetworkSrcPduRId, &TxPduInfo))
  {
      uint8 BuffSrcNtwrkIdx = (uint8)0x00;
      /* The transmission failed so leave the status of the Queue to be NOT_ACTIVE and raise a DET error*/
#if(MIRROR_DEV_ERROR_DETECT == STD_ON)
      /* !LINKSTO Mirror.ASR44.SWS_Mirror_00150,1 */
      /* The Mirror trasnmission failed */
      MIRROR_DET_REPORT_ERROR(ApiId, MIRROR_E_TRANSMIT_FAILED);
#endif /* MIRROR_DEV_ERROR_DETECT */
      /* Set the buffer status to not active */
      Mirror_QueueBufferStatus[Mirror_TxQueueBuffer].QueueBuffStatus = (uint8)MIRROR_QUEUE_BUFFER_NOT_ACTIVE;
      Mirror_IsTransmitting = FALSE;
      /* set lost frame bit in all the source networks. */
      for(BuffSrcNtwrkIdx = (uint8)0x00; BuffSrcNtwrkIdx < Mirror_QueueBufferStatus[Mirror_TxQueueBuffer].MirroredSourceNetworksCount; BuffSrcNtwrkIdx += (uint8)0x01)
      {
          /* !LINKSTO Mirror.ASR44.SWS_Mirror_00079,1 */
          (MIRROR_SET_LOST_FRAME_BIT(Mirror_SourceNetworkStatus[Mirror_QueueBufferStatus[Mirror_TxQueueBuffer].MirroredSourceNetworks[BuffSrcNtwrkIdx]].SourceNetworkCurrentStatusByte));
      }
      Mirror_QueueBufferStatus[Mirror_TxQueueBuffer].MirroredSourceNetworksCount = (uint8)0x00;
  }
  else
  {
      /* The transmission succeeded */
      Mirror_IsTransmitting = TRUE;
      Mirror_QueueBufferStatus[Mirror_TxQueueBuffer].QueueBuffStatus = (uint8)MIRROR_QUEUE_BUFFER_TRANSMITTING;
      Mirror_QueueBufferStatus[Mirror_TxQueueBuffer].TxTimer = Mirror_DestNetworks[Mirror_ActiveDestination].DestTxConfirmationTimeout;
  }
}

#if(MIRROR_CAN_SOURCENETWORK == STD_ON)
static FUNC (Std_ReturnType, MIRROR_CODE) Mirror_CopyCurrentCanFrame
(
  P2VAR(boolean, AUTOMATIC, MIRROR_APPL_DATA) CopySuccessStatus
)
{
  Std_ReturnType retVal = E_OK;
  /* Check The Data Element length */
  uint16 DataElementLength = (uint16)MIRROR_CAN_ELEMENT_MINIMUM_LENGTH;
  uint16 DataElementTimeStamp = (uint16)0U;
  uint8 DataElementAvStatus = (uint8)0U;
  boolean NetworkStatusAvailable = FALSE;
  boolean TimeStampBelowMax = FALSE;
  /* Check if network status is started to check the status byte for the current data element */
  if (TRUE == (Mirror_SourceNetworkStatus[Mirror_CanElement[Mirror_CanElementReadIndex].ElementSrcNtwrk].IsSourceNetworkStarted))
  {
      /* The source network that reported this frame is active so a check to the status byte is needed */
      if((Mirror_SourceNetworkStatus[Mirror_CanElement[Mirror_CanElementReadIndex].ElementSrcNtwrk].SourceNetworkCurrentStatusByte) ==
      (Mirror_SourceNetworkStatus[Mirror_CanElement[Mirror_CanElementReadIndex].ElementSrcNtwrk].SourceNetworkOldStatusByte))
      {
          /* no change is done to the status between 2 different main functions so no data element will be reported */
      }
      else
      {
          /* !LINKSTO Mirror.ASR44.SWS_Mirror_00068,1 */
          /* a change has occurred so the Network status byte is available */
          NetworkStatusAvailable = TRUE;
          DataElementLength = DataElementLength + (uint16)1;
          MIRROR_SET_NETWORK_STATE_AVAILABLE(DataElementAvStatus);
      }
  }
  else
  {
      /* The source network isn't started so no status will be reported, only the data element*/
  }
  DataElementLength = DataElementLength + (uint16)Mirror_CanElement[Mirror_CanElementReadIndex].ElementLength;
  /* if the current buffer can't store the current element then check if the next queue can store the element. */
  if((Mirror_QueueBufferStatus[Mirror_ActiveQueueBuffer].FrameLength + DataElementLength) >
    Mirror_DestNetworks[Mirror_ActiveDestination].DestNetworkPduLength)
  {
      /* The buffer is full so move to the next buffer in the queue*/
      Mirror_QueueBufferStatus[Mirror_ActiveQueueBuffer].QueueBuffStatus = (uint8)MIRROR_QUEUE_BUFFER_TRANSMIT_REQUESTED;
      Mirror_ActiveQueueBuffer = (Mirror_ActiveQueueBuffer + (uint16)1U) % (Mirror_DestNetworks[Mirror_ActiveDestination].DestQueueSizeRange);
      /* Check the current status of the queue buffer */
      *CopySuccessStatus = FALSE;
      /* !LINKSTO Mirror.ASR44.SWS_Mirror_00048,1 */
      if((uint8)MIRROR_QUEUE_BUFFER_NOT_ACTIVE == Mirror_QueueBufferStatus[Mirror_ActiveQueueBuffer].QueueBuffStatus)
      {
          /* Do nothing the next buffer is available */
      }
      else
      {
          /* The next buffer in the queue isn't available and the all the queue buffers are full */
#if(MIRROR_DEV_ERROR_DETECT == STD_ON)
          /* !LINKSTO Mirror.ASR44.SWS_Mirror_00004,1 */
          /* All the Mirror queue buffers are full. */
          MIRROR_DET_REPORT_ERROR(MIRROR_SID_MAINFUNCTION, MIRROR_E_QUEUE_OVERRUN);
#endif /* MIRROR_DEV_ERROR_DETECT */
          retVal = E_NOT_OK;
      }
  }
  else
  {
      /* The queue has space to copy the current frame */
      *CopySuccessStatus = TRUE;
  }
  DataElementTimeStamp = Mirror_TimeStampDiff(&(Mirror_CanTimeStamp[Mirror_CanElementReadIndex]), &TimeStampBelowMax);
  if((TRUE == *CopySuccessStatus) && (TRUE == TimeStampBelowMax))
  {
      /* !LINKSTO Mirror.ASR44.SWS_Mirror_00064,1 */
      /* The Frame can be copied so Set the availability status byte and start the copying The data to the queue buffer*/
      uint32 BuffIndex = (uint32)(Mirror_QueueBufferStatus[Mirror_ActiveQueueBuffer].FrameLength) + (uint32)((uint32)Mirror_ActiveQueueBuffer * (uint32)(Mirror_DestNetworks[Mirror_ActiveDestination].DestNetworkPduLength));
      /* !LINKSTO Mirror.ASR44.SWS_Mirror_00069,1 */
      MIRROR_SET_NETWORK_FRAMEID_AVAILABLE(DataElementAvStatus);
      /* !LINKSTO Mirror.ASR44.SWS_Mirror_00070,1 */
      /* !LINKSTO Mirror.ASR44.SWS_Mirror_00071,1 */
      /* !LINKSTO Mirror.ASR44.SWS_Mirror_00072,1 */
      MIRROR_SET_NETWORK_PAYLOAD_AVAILABLE(DataElementAvStatus);
      /* !LINKSTO Mirror.ASR44.SWS_Mirror_00073,1 */
      /* !LINKSTO Mirror.ASR44.SWS_Mirror_00074,1 */
      MIRROR_SET_NETWORK_TYPE(DataElementAvStatus,MIRROR_NT_CAN);
      /* !LINKSTO Mirror.ASR44.SWS_Mirror_00065,1 */
      /* !LINKSTO Mirror.ASR44.SWS_Mirror_00066,1 */
      /* Time stamp copying */
      Mirror_MemCpy16(DataElementTimeStamp, &TxBuffer[BuffIndex]);
      BuffIndex += (uint32)2U;
      /* availability byte copying */
      TxBuffer[BuffIndex] = DataElementAvStatus;
      BuffIndex += (uint32)1;
      /* Network ID copying*/
      /* !LINKSTO Mirror.ASR44.SWS_Mirror_00076,1 */
      TxBuffer[BuffIndex] = Mirror_SourceNetworks[Mirror_CanElement[Mirror_CanElementReadIndex].ElementSrcNtwrk].MirrorNetworkId;
      BuffIndex += (uint32)1;
      /* !LINKSTO Mirror.ASR44.SWS_Mirror_00067,1 */
      if(TRUE == NetworkStatusAvailable)
      {
          /* Network has a new state */
          /* !LINKSTO Mirror.ASR44.SWS_Mirror_00077,1 */
          /* !LINKSTO Mirror.ASR44.SWS_Mirror_00078,1 */
          Mirror_SourceNetworkStatus[Mirror_CanElement[Mirror_CanElementReadIndex].ElementSrcNtwrk].SourceNetworkOldStatusByte = Mirror_SourceNetworkStatus[Mirror_CanElement[Mirror_CanElementReadIndex].ElementSrcNtwrk].SourceNetworkCurrentStatusByte;
          TxBuffer[BuffIndex] = Mirror_SourceNetworkStatus[Mirror_CanElement[Mirror_CanElementReadIndex].ElementSrcNtwrk].SourceNetworkOldStatusByte;
          BuffIndex += (uint32)1;
      }
      else
      {
          /* Network has the same old state */
      }
      /* To stop reporting the status if a new status arrived within this main function via report frame */
      Mirror_SourceNetworkStatus[Mirror_CanElement[Mirror_CanElementReadIndex].ElementSrcNtwrk].IsStatusReported = TRUE;
      /* FrameID copying */
      /* !LINKSTO Mirror.ASR44.SWS_Mirror_00095,1 */
      /* !LINKSTO Mirror.ASR44.SWS_Mirror_00097,1 */
      Mirror_MemCpy32(Mirror_CanElement[Mirror_CanElementReadIndex].FrameID, &TxBuffer[BuffIndex]);
      BuffIndex += (uint32)4;
      /* Payload length copying */
      /* !LINKSTO Mirror.ASR44.SWS_Mirror_00109,1 */
      /* !LINKSTO Mirror.ASR44.SWS_Mirror_00110,1 */
      TxBuffer[BuffIndex] = Mirror_CanElement[Mirror_CanElementReadIndex].ElementLength;
      BuffIndex += (uint32)1;
      /* Payload copying */
      /* !LINKSTO Mirror.ASR44.SWS_Mirror_00111,1 */
      TS_MemCpy(&TxBuffer[BuffIndex], &(Mirror_CanElement[Mirror_CanElementReadIndex].DataElement[0]), Mirror_CanElement[Mirror_CanElementReadIndex].ElementLength);
      /* Change the status of the Can data element to available */
      Mirror_CanElement[Mirror_CanElementReadIndex].ElementStatus = (uint8)MIRROR_ELEMENT_AVAILABLE;
      Mirror_CanElementReadIndex = (Mirror_CanElementReadIndex + (uint32)1) % (uint32)MIRROR_CAN_ELEMENTCOUNTER;
      Mirror_QueueBufferStatus[Mirror_ActiveQueueBuffer].FrameLength += DataElementLength;
      /* Overwrite the Frame length in the dest frame with the new length after adding the frame*/
      /* !LINKSTO Mirror.ASR44.SWS_Mirror_00062,1 */
      Mirror_MemCpy16((uint16)(Mirror_QueueBufferStatus[Mirror_ActiveQueueBuffer].FrameLength - (uint16)MIRROR_FRAME_HEADER_SIZE), &TxBuffer[MIRROR_DEST_FRAME_DATALENGTH_POSITION]);
      /* Enter te network Index in the queue status as a network that has an element in the current buffer. */
      InsertSourceNetworkIndex(Mirror_CanElement[Mirror_CanElementReadIndex].ElementSrcNtwrk);
  }
  else
  {
      /* !LINKSTO Mirror.ASR44.SWS_Mirror_00049,1 */
      if((FALSE == TimeStampBelowMax) && (TRUE == *CopySuccessStatus))
      {
          /* The time stamp of this data element exceeded the limit of 655.35ms */
          /* Move to the next buffer in the next iteration */
          Mirror_QueueBufferStatus[Mirror_ActiveQueueBuffer].QueueBuffStatus = (uint8)MIRROR_QUEUE_BUFFER_TRANSMIT_REQUESTED;
          Mirror_ActiveQueueBuffer = (Mirror_ActiveQueueBuffer + (uint16)1U) % (Mirror_DestNetworks[Mirror_ActiveDestination].DestQueueSizeRange);
          /* !LINKSTO Mirror.ASR44.SWS_Mirror_00048,1 */
          if((uint8)MIRROR_QUEUE_BUFFER_NOT_ACTIVE == Mirror_QueueBufferStatus[Mirror_ActiveQueueBuffer].QueueBuffStatus)
          {
              /* The buffer is inactive but available. */
          }
          else
          {
              /* The buffer status isn't available and the all the queue buffers are full */
#if(MIRROR_DEV_ERROR_DETECT == STD_ON)
              /* !LINKSTO Mirror.ASR44.SWS_Mirror_00004,1 */
              /* The Mirror queue buffer is full with remaining data elements to be copied */
              MIRROR_DET_REPORT_ERROR(MIRROR_SID_MAINFUNCTION, MIRROR_E_QUEUE_OVERRUN);
#endif /* MIRROR_DEV_ERROR_DETECT */
              retVal = E_NOT_OK;
          }
      }
      else
      {
          /* The case is handled above as the frame couldn't be copied not due to time stamp difference */
      }
      /* The Frame couldn't be copied. */
      *CopySuccessStatus = FALSE;
  }
  return retVal;
}
#endif /* MIRROR_CAN_SOURCENETWORK == STD_ON */

#if(MIRROR_CANFD_SOURCENETWORK == STD_ON)
static FUNC (Std_ReturnType, MIRROR_CODE) Mirror_CopyCurrentCanFDFrame
(
  P2VAR(boolean, AUTOMATIC, MIRROR_APPL_DATA) CopySuccessStatus
)
{
  Std_ReturnType retVal = E_OK;
  /* Check The Data Element length */
  uint16 DataElementLength = (uint16)MIRROR_CAN_ELEMENT_MINIMUM_LENGTH;
  uint16 DataElementTimeStamp = (uint16)0U;
  uint8 DataElementAvStatus = (uint8)0U;
  boolean NetworkStatusAvailable = FALSE;
  boolean TimeStampBelowMax = FALSE;
  /* Check if network status is started to check the status byte for the current data element */
  if (TRUE == (Mirror_SourceNetworkStatus[Mirror_CanFDElement[Mirror_CanFDElementReadIndex].ElementSrcNtwrk].IsSourceNetworkStarted))
  {
      /* The source network that reported this frame is active so a check to the status byte is needed */
      if((Mirror_SourceNetworkStatus[Mirror_CanFDElement[Mirror_CanFDElementReadIndex].ElementSrcNtwrk].SourceNetworkCurrentStatusByte) ==
      (Mirror_SourceNetworkStatus[Mirror_CanFDElement[Mirror_CanFDElementReadIndex].ElementSrcNtwrk].SourceNetworkOldStatusByte))
      {
          /* no change is done to the status between 2 different main functions so no data element will be reported */
      }
      else
      {
          /* !LINKSTO Mirror.ASR44.SWS_Mirror_00068,1 */
          /* a change has occured so the Network status byte is available */
          NetworkStatusAvailable = TRUE;
          DataElementLength = DataElementLength + (uint16)1;
          MIRROR_SET_NETWORK_STATE_AVAILABLE(DataElementAvStatus);
      }
  }
  else
  {
      /* The source network isn't started so no status will be reported only the data element*/
  }
  DataElementLength = DataElementLength + (uint16)Mirror_CanFDElement[Mirror_CanFDElementReadIndex].ElementLength;
  /* if the current buffer can't store the current element then check if the next queue can store the element. */
  if((Mirror_QueueBufferStatus[Mirror_ActiveQueueBuffer].FrameLength + DataElementLength) >
    Mirror_DestNetworks[Mirror_ActiveDestination].DestNetworkPduLength)
  {
      /* The buffer is full so move to the next buffer in the queue*/
      Mirror_QueueBufferStatus[Mirror_ActiveQueueBuffer].QueueBuffStatus = (uint8)MIRROR_QUEUE_BUFFER_TRANSMIT_REQUESTED;
      Mirror_ActiveQueueBuffer = (Mirror_ActiveQueueBuffer + (uint16)1U) % (Mirror_DestNetworks[Mirror_ActiveDestination].DestQueueSizeRange);
      *CopySuccessStatus = FALSE;
      /* Check the current status of the queue buffer */
      /* !LINKSTO Mirror.ASR44.SWS_Mirror_00048,1 */
      if((uint8)MIRROR_QUEUE_BUFFER_NOT_ACTIVE == Mirror_QueueBufferStatus[Mirror_ActiveQueueBuffer].QueueBuffStatus)
      {
          /* The buffer is inactive but available. */
      }
      else
      {
          /* The buffer status isn't available and the all the queue buffers are full */
#if(MIRROR_DEV_ERROR_DETECT == STD_ON)
          /* !LINKSTO Mirror.ASR44.SWS_Mirror_00113,1 */
          /* The Mirror queue buffer is full with remaining data elements to be copied */
          MIRROR_DET_REPORT_ERROR(MIRROR_SID_MAINFUNCTION, MIRROR_E_QUEUE_OVERRUN);
#endif /* MIRROR_DEV_ERROR_DETECT */
          retVal = E_NOT_OK;
      }
  }
  else
  {
      /* The queue has space to copy the current frame */
      *CopySuccessStatus = TRUE;
  }
  DataElementTimeStamp = Mirror_TimeStampDiff(&(Mirror_CanFDTimeStamp[Mirror_CanFDElementReadIndex]), & TimeStampBelowMax);
  if((TRUE == *CopySuccessStatus) && (TRUE == TimeStampBelowMax))
  {
      /* !LINKSTO Mirror.ASR44.SWS_Mirror_00064,1 */
      /* The Frame can be copied so Set the availability status byte and start the copying The data to the queue buffer*/
      uint32 BuffIndex = (uint32)(Mirror_QueueBufferStatus[Mirror_ActiveQueueBuffer].FrameLength) + (uint32)((uint32)Mirror_ActiveQueueBuffer * (uint32)(Mirror_DestNetworks[Mirror_ActiveDestination].DestNetworkPduLength));
      /* !LINKSTO Mirror.ASR44.SWS_Mirror_00069,1 */
      MIRROR_SET_NETWORK_FRAMEID_AVAILABLE(DataElementAvStatus);
      /* !LINKSTO Mirror.ASR44.SWS_Mirror_00070,1 */
      /* !LINKSTO Mirror.ASR44.SWS_Mirror_00071,1 */
      /* !LINKSTO Mirror.ASR44.SWS_Mirror_00072,1 */
      MIRROR_SET_NETWORK_PAYLOAD_AVAILABLE(DataElementAvStatus);
      /* !LINKSTO Mirror.ASR44.SWS_Mirror_00073,1 */
      /* !LINKSTO Mirror.ASR44.SWS_Mirror_00074,1 */
      MIRROR_SET_NETWORK_TYPE(DataElementAvStatus,MIRROR_NT_CAN);
      /* !LINKSTO Mirror.ASR44.SWS_Mirror_00065,1 */
      /* !LINKSTO Mirror.ASR44.SWS_Mirror_00066,1 */
      /* Time stamp copying */
      Mirror_MemCpy16(DataElementTimeStamp, &TxBuffer[BuffIndex]);
      BuffIndex += (uint32)2U;
      /* availability byte copying */
      TxBuffer[BuffIndex] = DataElementAvStatus;
      BuffIndex += (uint32)1;
      /* Network ID copying*/
      /* !LINKSTO Mirror.ASR44.SWS_Mirror_00076,1 */
      TxBuffer[BuffIndex] = Mirror_SourceNetworks[Mirror_CanFDElement[Mirror_CanFDElementReadIndex].ElementSrcNtwrk].MirrorNetworkId;
      BuffIndex += (uint32)1;
      /* !LINKSTO Mirror.ASR44.SWS_Mirror_00067,1 */
      if(TRUE == NetworkStatusAvailable)
      {
          /* Network has a new state */
          /* !LINKSTO Mirror.ASR44.SWS_Mirror_00077,1 */
          /* !LINKSTO Mirror.ASR44.SWS_Mirror_00078,1 */
          Mirror_SourceNetworkStatus[Mirror_CanFDElement[Mirror_CanFDElementReadIndex].ElementSrcNtwrk].SourceNetworkOldStatusByte = Mirror_SourceNetworkStatus[Mirror_CanFDElement[Mirror_CanFDElementReadIndex].ElementSrcNtwrk].SourceNetworkCurrentStatusByte;
          TxBuffer[BuffIndex] = Mirror_SourceNetworkStatus[Mirror_CanFDElement[Mirror_CanFDElementReadIndex].ElementSrcNtwrk].SourceNetworkOldStatusByte;
          BuffIndex += (uint32)1;
      }
      else
      {
          /* Network has the same old state */
      }
      /* To stop reporting the status if a new status arrived within this main function via report frame */
      Mirror_SourceNetworkStatus[Mirror_CanFDElement[Mirror_CanFDElementReadIndex].ElementSrcNtwrk].IsStatusReported = TRUE;
      /* FrameID copying */
      /* !LINKSTO Mirror.ASR44.SWS_Mirror_00095,1 */
      /* !LINKSTO Mirror.ASR44.SWS_Mirror_00097,1 */
      Mirror_MemCpy32(Mirror_CanFDElement[Mirror_CanFDElementReadIndex].FrameID, &TxBuffer[BuffIndex]);
      BuffIndex += (uint32)4;
      /* Payload length copying */
      /* !LINKSTO Mirror.ASR44.SWS_Mirror_00109,1 */
      /* !LINKSTO Mirror.ASR44.SWS_Mirror_00110,1 */
      TxBuffer[BuffIndex] = Mirror_CanFDElement[Mirror_CanFDElementReadIndex].ElementLength;
      BuffIndex += (uint32)1;
      /* Payload copying */
      /* !LINKSTO Mirror.ASR44.SWS_Mirror_00111,1 */
      TS_MemCpy(&TxBuffer[BuffIndex], &(Mirror_CanFDElement[Mirror_CanFDElementReadIndex].DataElement[0]), Mirror_CanFDElement[Mirror_CanFDElementReadIndex].ElementLength);
      /* Change the status of the CanFD data element to available */
      Mirror_CanFDElement[Mirror_CanFDElementReadIndex].ElementStatus = (uint8)MIRROR_ELEMENT_AVAILABLE;
      Mirror_CanFDElementReadIndex = (Mirror_CanFDElementReadIndex + (uint32)1) % (uint32)MIRROR_CANFD_ELEMENTCOUNTER;
      Mirror_QueueBufferStatus[Mirror_ActiveQueueBuffer].FrameLength += DataElementLength;
      /* Overwrite the Frame length in the dest frame with the new length after adding the frame*/
      /* !LINKSTO Mirror.ASR44.SWS_Mirror_00062,1 */
      Mirror_MemCpy16((uint16)(Mirror_QueueBufferStatus[Mirror_ActiveQueueBuffer].FrameLength - (uint16)MIRROR_FRAME_HEADER_SIZE), &TxBuffer[MIRROR_DEST_FRAME_DATALENGTH_POSITION]);
      /* Enter te network Index in the queue status as a network that has an element in the current buffer. */
      InsertSourceNetworkIndex(Mirror_CanFDElement[Mirror_CanFDElementReadIndex].ElementSrcNtwrk);
  }
  else
  {
      /* !LINKSTO Mirror.ASR44.SWS_Mirror_00049,1 */
      if((FALSE == TimeStampBelowMax) && (TRUE == *CopySuccessStatus))
      {
          /* The time stamp of this data element exceeded the limit of 655.35ms */
          /* Move to the next buffer in the next iteration and activate it. */
          Mirror_QueueBufferStatus[Mirror_ActiveQueueBuffer].QueueBuffStatus = (uint8)MIRROR_QUEUE_BUFFER_TRANSMIT_REQUESTED;
          Mirror_ActiveQueueBuffer = (Mirror_ActiveQueueBuffer + (uint16)1U) % (Mirror_DestNetworks[Mirror_ActiveDestination].DestQueueSizeRange);
          /* !LINKSTO Mirror.ASR44.SWS_Mirror_00048,1 */
          if((uint8)MIRROR_QUEUE_BUFFER_NOT_ACTIVE == Mirror_QueueBufferStatus[Mirror_ActiveQueueBuffer].QueueBuffStatus)
          {
              /* The buffer is inactive but available. */
          }
          else
          {
              /* The buffer status isn't available and the all the queue buffers are full */
#if(MIRROR_DEV_ERROR_DETECT == STD_ON)
              /* !LINKSTO Mirror.ASR44.SWS_Mirror_00113,1 */
              /* The Mirror queue buffer is full with remaining data elements to be copied */
              MIRROR_DET_REPORT_ERROR(MIRROR_SID_MAINFUNCTION, MIRROR_E_QUEUE_OVERRUN);
#endif /* MIRROR_DEV_ERROR_DETECT */
              retVal = E_NOT_OK;
          }
      }
      else
      {
          /* The case is handled above as the frame couldn't be copied not due to time stamp difference */
      }
      /* The Frame couldn't be copied. */
      *CopySuccessStatus = FALSE;
  }
  return retVal;
}
#endif /* MIRROR_CANFD_SOURCENETWORK == STD_ON */

#if(MIRROR_LIN_SOURCENETWORK == STD_ON)
static FUNC (Std_ReturnType, MIRROR_CODE) Mirror_CopyCurrentLinFrame
(
  P2VAR(boolean, AUTOMATIC, MIRROR_APPL_DATA) CopySuccessStatus
)
{
  Std_ReturnType retVal = E_OK;
  /* Check The Data Element length */
  uint16 DataElementLength = (uint16)MIRROR_LIN_ELEMENT_MINIMUM_LENGTH;
  uint16 DataElementTimeStamp = (uint16)0U;
  uint8 DataElementAvStatus = (uint8)0U;
  boolean NetworkStatusAvailable = FALSE;
  boolean TimeStampBelowMax = FALSE;
  /* Check if network status is started to check the status byte for the current data element */
  if (TRUE == (Mirror_SourceNetworkStatus[Mirror_LinElement[Mirror_LinElementReadIndex].ElementSrcNtwrk].IsSourceNetworkStarted))
  {
      /* The source network that reported this frame is active so a check to the status byte is needed */
      if((Mirror_SourceNetworkStatus[Mirror_LinElement[Mirror_LinElementReadIndex].ElementSrcNtwrk].SourceNetworkCurrentStatusByte) ==
      (Mirror_SourceNetworkStatus[Mirror_LinElement[Mirror_LinElementReadIndex].ElementSrcNtwrk].SourceNetworkOldStatusByte))
      {
          /* no change is done to the status between 2 different main functions so no data element will be reported */
          NetworkStatusAvailable = FALSE;
      }
      else
      {
          /* !LINKSTO Mirror.ASR44.SWS_Mirror_00068,1 */
          /* a change has occured so the Network status byte is available */
          NetworkStatusAvailable = TRUE;
          DataElementLength = DataElementLength + (uint16)1U;
          MIRROR_SET_NETWORK_STATE_AVAILABLE(DataElementAvStatus);
      }
  }
  else
  {
      /* The source network isn't started so no status will be reported only the data element*/
      NetworkStatusAvailable = FALSE;
  }
  if((Mirror_LinElement[Mirror_LinElementReadIndex].NetworkStatus != (uint8)0U) && (FALSE == NetworkStatusAvailable))
  {
      NetworkStatusAvailable = TRUE;
      DataElementLength = DataElementLength + (uint16)1U;
      MIRROR_SET_NETWORK_STATE_AVAILABLE(DataElementAvStatus);
  }
  else
  {
      /* Data element available. */
      DataElementLength = DataElementLength + (uint16)1U;
  }
  DataElementLength = DataElementLength + (uint16)Mirror_LinElement[Mirror_LinElementReadIndex].ElementLength;
  /* if the current buffer can't store the current element then check if the next queue can store the element. */
  if((Mirror_QueueBufferStatus[Mirror_ActiveQueueBuffer].FrameLength + DataElementLength) >
    Mirror_DestNetworks[Mirror_ActiveDestination].DestNetworkPduLength)
  {
      /* The buffer is full so move to the next buffer in the queue*/
      Mirror_QueueBufferStatus[Mirror_ActiveQueueBuffer].QueueBuffStatus = (uint8)MIRROR_QUEUE_BUFFER_TRANSMIT_REQUESTED;
      Mirror_ActiveQueueBuffer = (Mirror_ActiveQueueBuffer + (uint16)1U) % (Mirror_DestNetworks[Mirror_ActiveDestination].DestQueueSizeRange);
      *CopySuccessStatus = FALSE;
      /* Check the current status of the queue buffer */
      /* !LINKSTO Mirror.ASR44.SWS_Mirror_00048,1 */
      if((uint8)MIRROR_QUEUE_BUFFER_NOT_ACTIVE == Mirror_QueueBufferStatus[Mirror_ActiveQueueBuffer].QueueBuffStatus)
      {
          /* The buffer is inactive but available. */
      }
      else
      {
          /* The buffer status isn't available and the all the queue buffers are full */
#if(MIRROR_DEV_ERROR_DETECT == STD_ON)
          /* !LINKSTO Mirror.ASR44.SWS_Mirror_00004,1 */
          /* The Mirror queue buffer is full with remaining data elements to be copied */
          MIRROR_DET_REPORT_ERROR(MIRROR_SID_MAINFUNCTION, MIRROR_E_QUEUE_OVERRUN);
#endif /* MIRROR_DEV_ERROR_DETECT */
          retVal = E_NOT_OK;
      }
  }
  else
  {
      /* The queue has space to copy the current frame */
      *CopySuccessStatus = TRUE;
  }
  DataElementTimeStamp = Mirror_TimeStampDiff(&(Mirror_LinTimeStamp[Mirror_LinElementReadIndex]), &TimeStampBelowMax);
  if((TRUE == *CopySuccessStatus) && (TRUE == TimeStampBelowMax))
  {
      /* !LINKSTO Mirror.ASR44.SWS_Mirror_00064,1 */
      /* The Frame can be copied so Set the availability status byte and start the copying The data to the queue buffer*/
      uint32 BuffIndex = (uint32)(Mirror_QueueBufferStatus[Mirror_ActiveQueueBuffer].FrameLength) + (uint32)((uint32)Mirror_ActiveQueueBuffer * (uint32)(Mirror_DestNetworks[Mirror_ActiveDestination].DestNetworkPduLength));
      /* !LINKSTO Mirror.ASR44.SWS_Mirror_00069,1 */
      /* !LINKSTO Mirror.ASR44.SWS_Mirror_00070,1 */
      MIRROR_SET_NETWORK_FRAMEID_AVAILABLE(DataElementAvStatus);
      if((uint8)0 == Mirror_LinElement[Mirror_LinElementReadIndex].ElementLength)
      {
          /* Do nothing (don't set the PAYLOAD available bit) */
      }
      else
      {
           /* !LINKSTO Mirror.ASR44.SWS_Mirror_00071,1 */
           /* !LINKSTO Mirror.ASR44.SWS_Mirror_00072,1 */
           MIRROR_SET_NETWORK_PAYLOAD_AVAILABLE(DataElementAvStatus);
      }
      /* !LINKSTO Mirror.ASR44.SWS_Mirror_00073,1 */
      /* !LINKSTO Mirror.ASR44.SWS_Mirror_00074,1 */
      MIRROR_SET_NETWORK_TYPE(DataElementAvStatus,MIRROR_NT_LIN);
      /* !LINKSTO Mirror.ASR44.SWS_Mirror_00065,1 */
      /* !LINKSTO Mirror.ASR44.SWS_Mirror_00066,1 */
      /* Time stamp copying */
      Mirror_MemCpy16(DataElementTimeStamp, &TxBuffer[BuffIndex]);
      BuffIndex += (uint32)2U;
      /* availability byte copying */
      TxBuffer[BuffIndex] = DataElementAvStatus;
      BuffIndex += (uint32)1;
      /* Network ID copying*/
      /* !LINKSTO Mirror.ASR44.SWS_Mirror_00076,1 */
      TxBuffer[BuffIndex] = Mirror_SourceNetworks[Mirror_LinElement[Mirror_LinElementReadIndex].ElementSrcNtwrk].MirrorNetworkId;
      BuffIndex += (uint32)1;
      /* !LINKSTO Mirror.ASR44.SWS_Mirror_00067,1 */
      if(TRUE == NetworkStatusAvailable)
      {
          /* Network has a new state */
          /* !LINKSTO Mirror.ASR44.SWS_Mirror_00077,1 */
          /* !LINKSTO Mirror.ASR44.SWS_Mirror_00078,1 */
          uint8 LinStatus = (uint8)0U;
          Mirror_SourceNetworkStatus[Mirror_LinElement[Mirror_LinElementReadIndex].ElementSrcNtwrk].SourceNetworkOldStatusByte = Mirror_SourceNetworkStatus[Mirror_LinElement[Mirror_LinElementReadIndex].ElementSrcNtwrk].SourceNetworkCurrentStatusByte;
          LinStatus = Mirror_SourceNetworkStatus[Mirror_LinElement[Mirror_LinElementReadIndex].ElementSrcNtwrk].SourceNetworkOldStatusByte | Mirror_LinElement[Mirror_LinElementReadIndex].NetworkStatus;
          TxBuffer[BuffIndex] = LinStatus;
          BuffIndex += (uint32)1;
      }
      else
      {
          /* Network has the same old state */
      }
      /* To stop reporting the status if a new status arrived within this main function via report frame */
      Mirror_SourceNetworkStatus[Mirror_LinElement[Mirror_LinElementReadIndex].ElementSrcNtwrk].IsStatusReported = TRUE;
      /* FrameID copying */
      /* !LINKSTO Mirror.ASR44.SWS_Mirror_00095,1 */
      /* !LINKSTO Mirror.ASR44.SWS_Mirror_00102,1 */
      TxBuffer[BuffIndex] = Mirror_LinElement[Mirror_LinElementReadIndex].FrameID;
      BuffIndex += (uint32)1;
      /* Payload length copying */
      /* !LINKSTO Mirror.ASR44.SWS_Mirror_00109,1 */
      /* !LINKSTO Mirror.ASR44.SWS_Mirror_00110,1 */
      /* Payload and element length copying */
      /* !LINKSTO Mirror.ASR44.SWS_Mirror_00111,1 */
      if((uint8)0U == Mirror_LinElement[Mirror_LinElementReadIndex].ElementLength)
      {
          /* Do nothing (No payload to copy) */
      }
      else
      {
          TxBuffer[BuffIndex] = Mirror_LinElement[Mirror_LinElementReadIndex].ElementLength;
          BuffIndex += (uint32)1;
          TS_MemCpy(&TxBuffer[BuffIndex], &(Mirror_LinElement[Mirror_LinElementReadIndex].DataElement[0]), Mirror_LinElement[Mirror_LinElementReadIndex].ElementLength);
      }
      /* Change the status of the Can data element to available */
      Mirror_LinElement[Mirror_LinElementReadIndex].ElementStatus = (uint8)MIRROR_ELEMENT_AVAILABLE;
      Mirror_LinElementReadIndex = (Mirror_LinElementReadIndex + (uint32)1) % (uint32)MIRROR_LIN_ELEMENTCOUNTER;
      Mirror_QueueBufferStatus[Mirror_ActiveQueueBuffer].FrameLength += DataElementLength;
      /* !LINKSTO Mirror.ASR44.SWS_Mirror_00062,1 */
      /* Overwrite the Frame length in the dest frame with the new length after adding the frame*/
      Mirror_MemCpy16((uint16)(Mirror_QueueBufferStatus[Mirror_ActiveQueueBuffer].FrameLength - (uint16)MIRROR_FRAME_HEADER_SIZE), &TxBuffer[MIRROR_DEST_FRAME_DATALENGTH_POSITION]);
      /* Enter te network Index in the queue status as a network that has an element in the current buffer. */
      InsertSourceNetworkIndex(Mirror_LinElement[Mirror_LinElementReadIndex].ElementSrcNtwrk);
  }
  else
  {
      /* !LINKSTO Mirror.ASR44.SWS_Mirror_00049,1 */
      if((FALSE == TimeStampBelowMax) && (TRUE == *CopySuccessStatus))
      {
          /* The time stamp of this data element exceeded the limit of 655.35ms */
          /* Move to the next buffer in the next iteration and activate it. */
          Mirror_QueueBufferStatus[Mirror_ActiveQueueBuffer].QueueBuffStatus = (uint8)MIRROR_QUEUE_BUFFER_TRANSMIT_REQUESTED;
          Mirror_ActiveQueueBuffer = (Mirror_ActiveQueueBuffer + (uint16)1U) % (Mirror_DestNetworks[Mirror_ActiveDestination].DestQueueSizeRange);
          /* !LINKSTO Mirror.ASR44.SWS_Mirror_00048,1 */
          if((uint8)MIRROR_QUEUE_BUFFER_NOT_ACTIVE == Mirror_QueueBufferStatus[Mirror_ActiveQueueBuffer].QueueBuffStatus)
          {
              /* The buffer is inactive but available. */
          }
          else
          {
              /* The buffer status isn't available and the all the queue buffers are full */
#if(MIRROR_DEV_ERROR_DETECT == STD_ON)
              /* !LINKSTO Mirror.ASR44.SWS_Mirror_00113,1 */
              /* The Mirror queue buffer is full with remaining data elements to be copied */
              MIRROR_DET_REPORT_ERROR(MIRROR_SID_MAINFUNCTION, MIRROR_E_QUEUE_OVERRUN);
#endif /* MIRROR_DEV_ERROR_DETECT */
              retVal = E_NOT_OK;
          }
      }
      else
      {
          /* The case is handled above as the frame couldn't be copied not due to time stamp difference */
      }
      /* The Frame couldn't be copied. */
            *CopySuccessStatus = FALSE;
  }
  return retVal;
}
#endif /* MIRROR_LIN_SOURCENETWORK == STD_ON */

static FUNC (uint16, MIRROR_CODE) Mirror_TimeStampDiff
(
  P2CONST(MIRROR_TIMESTAMP_TYPE, AUTOMATIC, MIRROR_APPL_DATA) TimeStamp,
  P2VAR(boolean, AUTOMATIC, MIRROR_APPL_DATA) BelowMax
)
{
  uint16 Diff = (uint16)0U;
  MIRROR_TIMESTAMP_TYPE TempTimeStamp;
  if(FALSE == Mirror_TimeStampComparator(&RefTimeStamp, TimeStamp, &TempTimeStamp))
  {
      /* The difference is 0 */
      *BelowMax = TRUE;
  }
  else
  {
      uint16 DiffSecondsHi = (uint16)0U;
      uint32 DiffNanoSeconds = (uint32)0U;
      uint32 DiffSeconds = (uint32)0U;
      /* Calculate the diffeence in seconds. */
      DiffSecondsHi = TimeStamp->secondsHi - RefTimeStamp.secondsHi;
      DiffSeconds = TimeStamp->seconds - RefTimeStamp.seconds;
      if(TimeStamp->seconds >= RefTimeStamp.seconds)
      {
        /* Do nothing */
      }
      else
      {
          DiffSecondsHi -= (uint16)0x01;
      }
      /* Calculate the diffeence in nanoseconds. */
      if(TimeStamp->nanoseconds >= RefTimeStamp.nanoseconds)
      {
          DiffNanoSeconds = TimeStamp->nanoseconds - RefTimeStamp.nanoseconds;
      }
      else
      {
          uint32 TempNanoSeconds = TimeStamp->nanoseconds + (uint32)MIRROR_SECOND_TO_NANOSECONDS;
          DiffNanoSeconds = TempNanoSeconds - RefTimeStamp.nanoseconds;
          DiffSeconds -= (uint32)0x01;
      }
      Diff = (uint16)(DiffNanoSeconds / (uint32)(MIRROR_10_MICROSECONDS_TO_NANOSECONDS));
      if((DiffSecondsHi > (uint16)0x00) || (DiffSeconds > (uint32)0x00) || (DiffNanoSeconds >= (uint32)MIRROR_MAX_TIMESTAMP_DIFFERENCE))
      {
          *BelowMax = FALSE;
      }
      else
      {
          *BelowMax = TRUE;
      }
  }
  return Diff;
}

static FUNC (void, MIRROR_CODE) InsertSourceNetworkIndex
(
  VAR(uint8, MIRROR_VAR) SourceNetworkIndex
)
{
  uint8 Index = (uint8)0x00;
  boolean NetworkExists = FALSE;
  while((Index < Mirror_QueueBufferStatus[Mirror_ActiveQueueBuffer].MirroredSourceNetworksCount) && (FALSE == NetworkExists))
  {
      if(SourceNetworkIndex == Mirror_QueueBufferStatus[Mirror_ActiveQueueBuffer].MirroredSourceNetworks[Index])
      {
          NetworkExists = TRUE;
      }
      else
      {
          /* Do nothing and go to the next iteration. */
      }
      Index += (uint8)0x01;
  }
  if(FALSE == NetworkExists)
  {
      Mirror_QueueBufferStatus[Mirror_ActiveQueueBuffer].MirroredSourceNetworks[Index] = SourceNetworkIndex;
      Mirror_QueueBufferStatus[Mirror_ActiveQueueBuffer].MirroredSourceNetworksCount += (uint8)0x01;
  }
  else
  {
      /* Do nothing */
  }
}

static FUNC (void, MIRROR_CODE) QueueTimingOperations
(
  void
)
{
  /* Check the currently transmitted buffer */
  if((uint8)MIRROR_QUEUE_BUFFER_TRANSMITTING == Mirror_QueueBufferStatus[Mirror_TxQueueBuffer].QueueBuffStatus)
  {
      (void)Atomics_FetchSub(&Mirror_QueueBufferStatus[Mirror_TxQueueBuffer].TxTimer, (Atomic_value_t)0x01);
      /* Check if time reached 0 as a replacment for Mirror_TxConfirmation() with E_NOT_OK as a result */
      if((Atomic_t)0x00 == Mirror_QueueBufferStatus[Mirror_TxQueueBuffer].TxTimer)
      {
          uint8 BuffSrcNtwrkIdx = (uint8)0x00;
          /* The transmission failed so set the status of the Queue to be NOT_ACTIVE, raise the flag indicating Tx error and raise a DET error*/
          Mirror_IsTransmitting = FALSE;
#if(MIRROR_DEV_ERROR_DETECT == STD_ON)
          /* !LINKSTO Mirror.ASR44.SWS_Mirror_00153.TxConfirmationTimeOut,1 */
          /* The Mirror trasnmission failed */
          MIRROR_DET_REPORT_ERROR(MIRROR_SID_MAINFUNCTION, MIRROR_E_TRANSMIT_FAILED);
#endif /* MIRROR_DEV_ERROR_DETECT */
          /* Set the buffer status to not active */
          /* !LINKSTO Mirror.ASR44.SWS_Mirror_00152.TxConfirmationTimeOut,1 */
          Mirror_QueueBufferStatus[Mirror_TxQueueBuffer].QueueBuffStatus = (uint8)MIRROR_QUEUE_BUFFER_NOT_ACTIVE;
          /* set lost frame bit in all the source networks. */
          for(BuffSrcNtwrkIdx = (uint8)0x00; BuffSrcNtwrkIdx < Mirror_QueueBufferStatus[Mirror_TxQueueBuffer].MirroredSourceNetworksCount; BuffSrcNtwrkIdx += (uint8)0x01)
          {
              /* !LINKSTO Mirror.ASR44.SWS_Mirror_00079,1 */
              (MIRROR_SET_LOST_FRAME_BIT(Mirror_SourceNetworkStatus[Mirror_QueueBufferStatus[Mirror_TxQueueBuffer].MirroredSourceNetworks[BuffSrcNtwrkIdx]].SourceNetworkCurrentStatusByte));
          }
          Mirror_QueueBufferStatus[Mirror_TxQueueBuffer].MirroredSourceNetworksCount = (uint8)0x00;
      }
      else
      {
          /* The time didn't reach 0 so wait for the TxConfirmation */
      }
  }
  else
  {
      /* Do nothing as the buffer isn't trasnmitting */
  }
  /* Checking the buffer to be transmitted next if ready and if there is no transmission ongoing. */
  /* !LINKSTO Mirror.ASR44.SWS_Mirror_00048,1 */
  if(((uint8)MIRROR_QUEUE_BUFFER_TRANSMIT_REQUESTED == Mirror_QueueBufferStatus[Mirror_NextTxQueueBuffer].QueueBuffStatus) && (FALSE == Mirror_IsTransmitting))
  {
      /* !LINKSTO Mirror.ASR44.SWS_Mirror_00053,1 */
      Mirror_TransmitQueueBuffer
      (
#if(MIRROR_DEV_ERROR_DETECT == STD_ON)
      (uint8)MIRROR_SID_MAINFUNCTION
#endif /* MIRROR_DEV_ERROR_DETECT */
       );
  }
  else
  {
      /* !LINKSTO Mirror.ASR44.SWS_Mirror_00052,1 */
      /* a buffer is being transmitted so put the status to pending transmit. */
      /* The state should be the same so do nothing. */
  }
  /* Check the currently active buffer. */
  if(((uint8)MIRROR_QUEUE_BUFFER_ACTIVE == Mirror_QueueBufferStatus[Mirror_ActiveQueueBuffer].QueueBuffStatus) && (TRUE == Mirror_DestNetworks[Mirror_ActiveDestination].DestTxDeadlineEnable))
  {
      /* !LINKSTO Mirror.ASR44.SWS_Mirror_00050,1 */
      (void)Atomics_FetchSub(&Mirror_QueueBufferStatus[Mirror_ActiveQueueBuffer].TxTimer, (Atomic_value_t)0x01);
      if(((Atomic_t)0x00 == Mirror_QueueBufferStatus[Mirror_ActiveQueueBuffer].TxTimer) && (TRUE == Mirror_DestNetworks[Mirror_ActiveDestination].DestTxDeadlineEnable))
      {
          /* The buffer could be transmitted so check if another buffer is being trasnmitted. */
          if(TRUE == Mirror_IsTransmitting)
          {
              /* !LINKSTO Mirror.ASR44.SWS_Mirror_00052,1 */
              /* a buffer is being transmitted so put the status to pending transmit. */
              Mirror_QueueBufferStatus[Mirror_ActiveQueueBuffer].QueueBuffStatus = (uint8)MIRROR_QUEUE_BUFFER_TRANSMIT_REQUESTED;
          }
          else
          {
              /* !LINKSTO Mirror.ASR44.SWS_Mirror_00053,1 */
              Mirror_TransmitQueueBuffer
              (
#if(MIRROR_DEV_ERROR_DETECT == STD_ON)
              (uint8)MIRROR_SID_MAINFUNCTION
#endif /* MIRROR_DEV_ERROR_DETECT */
              );
          }
          /* Move to the next buffer as this will be transmitted or will be requested to be transmitted */
           Mirror_ActiveQueueBuffer = (Mirror_ActiveQueueBuffer + (uint16)1U) % (Mirror_DestNetworks[Mirror_ActiveDestination].DestQueueSizeRange);
      }
      else
      {
          /* Do nothing as the time didn't reach 0. */
      }
  }
  else
  {
      /* Do nothing as the buffer isn't active yet or to TxDeadline configured. */
  }
}

#define MIRROR_STOP_SEC_CODE
#include <Mirror_MemMap.h>

#if(MIRROR_CAN_SOURCENETWORK == STD_ON)

#define MIRROR_START_SEC_CAN_CODE
#include <Mirror_MemMap.h>

static FUNC(boolean, MIRROR_CODE) Mirror_FindCanSourceNetwork
(
  VAR(uint8, MIRROR_VAR) controllerId,
  P2VAR(uint8, AUTOMATIC, MIRROR_APPL_DATA) CanSrcNtwrkIdx
)
{
  uint8 SrcNtwrkIdx = (uint8)0U;
  boolean IsSrcNtwrkFound = (boolean)FALSE;
  while(((boolean)FALSE == IsSrcNtwrkFound) && (SrcNtwrkIdx < (uint8)MIRROR_NO_OF_SOURCENETWORKS))
  {
    if((uint8)MIRROR_NT_CAN == Mirror_SourceNetworks[SrcNtwrkIdx].NetworkType)
    {
        uint8 CtrlIdx = Mirror_SourceNetworks[SrcNtwrkIdx].SourceNetworkControllerIndex;
        for(CtrlIdx = Mirror_SourceNetworks[SrcNtwrkIdx].SourceNetworkControllerIndex; CtrlIdx < (Mirror_SourceNetworks[SrcNtwrkIdx].SourceNetworkControllerIndex + Mirror_SourceNetworks[SrcNtwrkIdx].NumOfSourceNetworkControllers); CtrlIdx++)
        {
            if(Mirror_SourceNetworkControllers[CtrlIdx] == controllerId)
            {
               IsSrcNtwrkFound = (boolean)TRUE;
            }
            else
            {
                /* Do nothing */
            }
        }
    }
    else
    {
        /*Do nothing and check the next network (not a CAN network source)*/
    }
    SrcNtwrkIdx++;
  }
  SrcNtwrkIdx--;
  *CanSrcNtwrkIdx = SrcNtwrkIdx;
  return IsSrcNtwrkFound;
}

static FUNC (void, MIRROR_CODE) Mirror_StoreCanFrame
(
  VAR(uint8, TYPEDEF) SrcNtwrkIdx,
  VAR(Can_IdType, TYPEDEF) canId,
  VAR(uint8, TYPEDEF) length,
  P2CONST(uint8, AUTOMATIC, MIRROR_APPL_DATA) payload
)
{
  MIRROR_USERDATA_TYPE Mirror_UserData;
  Atomic_value_t Lcl_WriteIdx = Atomics_FetchAdd(&Mirror_CanElementWriteIndex, (Atomic_value_t)1);
  if((Atomic_value_t)MIRROR_CAN_ELEMENTCOUNTER <= (Lcl_WriteIdx + (Atomic_value_t)1U))
  {
      Atomics_Store(&Mirror_CanElementWriteIndex ,(Atomic_value_t)0U);
  }
  else
  {
      /*Do nothing*/
  }
  Lcl_WriteIdx = Lcl_WriteIdx % (Atomic_value_t)MIRROR_CAN_ELEMENTCOUNTER;
  if((uint8)MIRROR_ELEMENT_AVAILABLE == Mirror_CanElement[Lcl_WriteIdx].ElementStatus)
  {
      Mirror_CanElement[Lcl_WriteIdx].ElementStatus = (uint8)MIRROR_ELEMENT_WRITING_IN_PROGRESS;
      MIRROR_GET_TIME_STAMP(&Mirror_CanTimeStamp[Lcl_WriteIdx], &Mirror_UserData);
      Mirror_CanElement[Lcl_WriteIdx].ElementSrcNtwrk = SrcNtwrkIdx;
      Mirror_CanElement[Lcl_WriteIdx].FrameID = (uint32)canId;
      Mirror_CanElement[Lcl_WriteIdx].ElementLength = length;
      TS_MemCpy(&(Mirror_CanElement[Lcl_WriteIdx].DataElement[0]), payload, length);
      Mirror_CanElement[Lcl_WriteIdx].ElementStatus = (uint8)MIRROR_ELEMENT_WRITING_FINISHED;
  }
  else
  {
      /* Runtime error of internal buffer over run */
      Atomics_Store(&Mirror_CanElementWriteIndex ,Lcl_WriteIdx);
#if(MIRROR_DEV_ERROR_DETECT == STD_ON)
      /* !LINKSTO Mirror.EB.IntermediateQueueOverRun,1 */
      MIRROR_DET_REPORT_ERROR(MIRROR_SID_REPORTCANFRAME, MIRROR_E_INTERMEDIATE_BUFFER_OVERRUN);
#endif /* MIRROR_DEV_ERROR_DETECT */
      /* !LINKSTO Mirror.ASR44.SWS_Mirror_00079,1 */
      MIRROR_SET_LOST_FRAME_BIT(Mirror_SourceNetworkStatus[SrcNtwrkIdx].SourceNetworkCurrentStatusByte);
      /* !LINKSTO Mirror.EB.CanLostFrameCallBack,1 */
#if(defined MIRROR_CAN_LOST_FRAME_CBK)
      MIRROR_CAN_LOST_FRAME_CBK();
#endif /* #if(defined MIRROR_CAN_LOST_FRAME_CBK)*/
  }
}

#if(MIRROR_CANFD_SOURCENETWORK == STD_ON)
static FUNC (void, MIRROR_CODE) Mirror_StoreCanFDFrame
(
  VAR(uint8, TYPEDEF) SrcNtwrkIdx,
  VAR(Can_IdType, TYPEDEF) canId,
  VAR(uint8, TYPEDEF) length,
  P2CONST(uint8, AUTOMATIC, MIRROR_APPL_DATA) payload
)
{
  MIRROR_USERDATA_TYPE Mirror_UserData;
  Atomic_value_t Lcl_WriteIdx = Atomics_FetchAdd(&Mirror_CanFDElementWriteIndex,(Atomic_value_t)1);
  if((Atomic_value_t)MIRROR_CANFD_ELEMENTCOUNTER <= (Lcl_WriteIdx + (Atomic_value_t)1U))
  {
      Atomics_Store(&Mirror_CanFDElementWriteIndex ,(Atomic_value_t)0U);
  }
  else
  {
      /*Do nothing*/
  }
  Lcl_WriteIdx = Lcl_WriteIdx % (Atomic_value_t)MIRROR_CANFD_ELEMENTCOUNTER;
  if((uint8)MIRROR_ELEMENT_AVAILABLE == Mirror_CanFDElement[Lcl_WriteIdx].ElementStatus)
  {
      Mirror_CanFDElement[Lcl_WriteIdx].ElementStatus = (uint8)MIRROR_ELEMENT_WRITING_IN_PROGRESS;
      MIRROR_GET_TIME_STAMP(&Mirror_CanFDTimeStamp[Lcl_WriteIdx], &Mirror_UserData);
      Mirror_CanFDElement[Lcl_WriteIdx].ElementSrcNtwrk = SrcNtwrkIdx;
      Mirror_CanFDElement[Lcl_WriteIdx].FrameID = (uint32)canId;
      Mirror_CanFDElement[Lcl_WriteIdx].ElementLength = length;
      TS_MemCpy(&(Mirror_CanFDElement[Lcl_WriteIdx].DataElement[0]), payload, length);
      Mirror_CanFDElement[Lcl_WriteIdx].ElementStatus = (uint8)MIRROR_ELEMENT_WRITING_FINISHED;
  }
  else
  {
      /* Runtime error of internal buffer over run */
      Atomics_Store(&Mirror_CanFDElementWriteIndex ,Lcl_WriteIdx);
#if(MIRROR_DEV_ERROR_DETECT == STD_ON)
      /* !LINKSTO Mirror.EB.IntermediateQueueOverRun,1 */
      MIRROR_DET_REPORT_ERROR(MIRROR_SID_REPORTCANFRAME, MIRROR_E_INTERMEDIATE_BUFFER_OVERRUN);
#endif /* MIRROR_DEV_ERROR_DETECT */
      /* !LINKSTO Mirror.ASR44.SWS_Mirror_00079,1 */
      MIRROR_SET_LOST_FRAME_BIT(Mirror_SourceNetworkStatus[SrcNtwrkIdx].SourceNetworkCurrentStatusByte);
      /* !LINKSTO Mirror.EB.CanFDLostFrameCallBack,1 */
#if(defined MIRROR_CANFD_LOST_FRAME_CBK)
      MIRROR_CANFD_LOST_FRAME_CBK();
#endif /* #if(defined MIRROR_CANFD_LOST_FRAME_CBK)*/
  }
}
#endif /* MIRROR_CANFD_SOURCENETWORK == STD_ON */

#define MIRROR_STOP_SEC_CAN_CODE
#include <Mirror_MemMap.h>

#endif /* MIRROR_CAN_SOURCENETWORK == STD_ON */

#if(MIRROR_LIN_SOURCENETWORK == STD_ON)

#define MIRROR_START_SEC_LIN_CODE
#include <Mirror_MemMap.h>

static FUNC(boolean, MIRROR_CODE) Mirror_FindLinSourceNetwork
(
  VAR(NetworkHandleType, MIRROR_VAR) network,
  P2VAR(uint8, AUTOMATIC, MIRROR_APPL_DATA) LinSrcNtwrkIdx
)
{
  uint8 SrcNtwrkIdx = (uint8)0U;
  boolean IsSrcNtwrkFound = (boolean)FALSE;
  while(((boolean)FALSE == IsSrcNtwrkFound) && (SrcNtwrkIdx < (uint8)MIRROR_NO_OF_SOURCENETWORKS))
  {
    if((uint8)MIRROR_NT_LIN == Mirror_SourceNetworks[SrcNtwrkIdx].NetworkType)
    {
        if(Mirror_SourceNetworks[SrcNtwrkIdx].ComMChannelId == network)
        {
           IsSrcNtwrkFound = (boolean)TRUE;
        }
        else
        {
            /* Do nothing */
        }
    }
    else
    {
        /*Do nothing and check the next network (not a LIN network source)*/
    }
    SrcNtwrkIdx++;
  }
  SrcNtwrkIdx--;
  *LinSrcNtwrkIdx = SrcNtwrkIdx;
  return IsSrcNtwrkFound;
}

static FUNC (void, MIRROR_CODE) Mirror_StoreLinFrame
(
  VAR(Lin_FramePidType, TYPEDEF) pid,
  P2CONST(PduInfoType, AUTOMATIC, MIRROR_APPL_DATA) pdu,
  VAR(Lin_StatusType, TYPEDEF) status,
  VAR(uint8, TYPEDEF) SrcNtwrkIdx
)
{
  boolean IsDataReported = FALSE;
  /* !LINKSTO Mirror.ASR44.SWS_Mirror_00034,1 */
  /* !LINKSTO Mirror.ASR44.SWS_Mirror_00084,1 */
  /* !LINKSTO Mirror.ASR44.SWS_Mirror_00029.ReportLinFrame,1 */
  MIRROR_USERDATA_TYPE Mirror_UserData;
  Atomic_value_t Lcl_WriteIdx = Atomics_FetchAdd(&Mirror_LinElementWriteIndex, (Atomic_value_t)1);
  if((Atomic_value_t)MIRROR_LIN_ELEMENTCOUNTER <= (Lcl_WriteIdx + (Atomic_value_t)1U))
  {
      Atomics_Store(&Mirror_LinElementWriteIndex, (Atomic_value_t)0U);
  }
  else
  {
      /*Do nothing*/
  }
  Lcl_WriteIdx = Lcl_WriteIdx % (Atomic_value_t)MIRROR_LIN_ELEMENTCOUNTER;
  if((uint8)MIRROR_ELEMENT_AVAILABLE == Mirror_LinElement[Lcl_WriteIdx].ElementStatus)
  {
      Mirror_LinElement[Lcl_WriteIdx].ElementStatus = (uint8)MIRROR_ELEMENT_WRITING_IN_PROGRESS;
      MIRROR_GET_TIME_STAMP(&Mirror_LinTimeStamp[Lcl_WriteIdx], &Mirror_UserData);
      Mirror_LinElement[Lcl_WriteIdx].ElementSrcNtwrk = SrcNtwrkIdx;
      Mirror_LinElement[Lcl_WriteIdx].FrameID = (uint8)pid;
      Mirror_LinElement[Lcl_WriteIdx].NetworkStatus = (uint8)0U;
      switch (status)
      {
          case LIN_TX_HEADER_ERROR:
          /* !LINKSTO Mirror.ASR44.SWS_Mirror_00085,1 */
          MIRROR_LIN_STATUS_SET_TX_HEADER_ERROR_BIT(Mirror_LinElement[Lcl_WriteIdx].NetworkStatus);
          break;

          case LIN_TX_ERROR:
          /* !LINKSTO Mirror.ASR44.SWS_Mirror_00086,1 */
          (MIRROR_LIN_STATUS_SET_TX_ERROR_BIT(Mirror_LinElement[Lcl_WriteIdx].NetworkStatus));
          break;

          case LIN_RX_ERROR:
          /* !LINKSTO Mirror.ASR44.SWS_Mirror_00087,1 */
          MIRROR_LIN_STATUS_SET_RX_ERROR_BIT(Mirror_LinElement[Lcl_WriteIdx].NetworkStatus);
          break;

          case LIN_RX_NO_RESPONSE:
          /* !LINKSTO Mirror.ASR44.SWS_Mirror_00088,1 */
          MIRROR_LIN_STATUS_SET_RX_NO_RESPONSE_BIT(Mirror_LinElement[Lcl_WriteIdx].NetworkStatus);
          break;

          case LIN_RX_OK:
          IsDataReported = TRUE;
          break;

          case LIN_TX_OK:
          IsDataReported = TRUE;
          break;

          default:
          {
#if(MIRROR_DEV_ERROR_DETECT == STD_ON)
              /* Invalid status was reported. */
              /* !LINKSTO Mirror.EB.InvalidStatus,1 */
              MIRROR_DET_REPORT_ERROR(MIRROR_SID_REPORTLINFRAME, MIRROR_E_INVALID_STATUS);
#endif /* MIRROR_DEV_ERROR_DETECT */
              break;
          }

      }
      if(FALSE == IsDataReported)
      {
          /* Do nothing as no data should have been reported but an empty frame will be saved */
      }
      else
      {
          if(NULL_PTR == pdu)
          {
#if(MIRROR_DEV_ERROR_DETECT == STD_ON)
              /* The pdu pointer is NULL */
              /* !LINKSTO Mirror.ASR44.SWS_Mirror_00007,1 */
              MIRROR_DET_REPORT_ERROR(MIRROR_SID_REPORTLINFRAME, MIRROR_E_PARAM_POINTER);
#endif /* MIRROR_DEV_ERROR_DETECT */
          }
          else
          {
              /* Do nothing */
          }
          }
          if((NULL_PTR == pdu) || (FALSE == IsDataReported))
          {
              Mirror_LinElement[Lcl_WriteIdx].ElementLength = 0;
          }
          else
          {
              Mirror_LinElement[Lcl_WriteIdx].ElementLength = (uint8)pdu->SduLength;
              TS_MemCpy(&(Mirror_LinElement[Lcl_WriteIdx].DataElement[0]), pdu->SduDataPtr, pdu->SduLength);
          }
          Mirror_LinElement[Lcl_WriteIdx].ElementStatus = (uint8)MIRROR_ELEMENT_WRITING_FINISHED;
  }
  else
  {
      Atomics_Store(&Mirror_LinElementWriteIndex, Lcl_WriteIdx);
#if(MIRROR_DEV_ERROR_DETECT == STD_ON)
      /* !LINKSTO Mirror.EB.IntermediateQueueOverRun,1 */
      /* Runtime error of internal buffer over run */
      MIRROR_DET_REPORT_ERROR(MIRROR_SID_REPORTLINFRAME, MIRROR_E_INTERMEDIATE_BUFFER_OVERRUN);
#endif /* MIRROR_DEV_ERROR_DETECT */
      /* !LINKSTO Mirror.ASR44.SWS_Mirror_00079,1 */
      MIRROR_SET_LOST_FRAME_BIT(Mirror_SourceNetworkStatus[SrcNtwrkIdx].SourceNetworkCurrentStatusByte);
      /* !LINKSTO Mirror.EB.LinLostFrameCallBack,1 */
#if(defined MIRROR_LIN_LOST_FRAME_CBK)
      MIRROR_LIN_LOST_FRAME_CBK();
#endif /* #if(defined MIRROR_LIN_LOST_FRAME_CBK)*/
  }
}

#define MIRROR_STOP_SEC_LIN_CODE
#include <Mirror_MemMap.h>

#endif /* MIRROR_LIN_SOURCENETWORK == STD_ON */
