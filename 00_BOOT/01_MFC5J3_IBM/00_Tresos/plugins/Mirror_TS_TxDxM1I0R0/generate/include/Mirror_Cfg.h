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

[!CODE!]
#if (!defined MIRROR_CFG_H)
#define MIRROR_CFG_H

/*==================[includes]==============================================*/
 
#include <Mirror_Types.h>
[!INCLUDE "../include/Mirror_PrecompileMacros.m"!][!//
[!LOOP "as:modconf('Mirror')[1]/MirrorGeneral/MirrorHeaderFileInclusion/*"!][!//
#include "[!"node:value(.)"!]"      /* Call back header file */
[!ENDLOOP!][!//
/*==================[macros]================================================*/

/** \brief Support for Development error reporting
 ** This macro defines whether the Det_ReportError() is provided or not.
 ** STD_ON    Function is provided
 ** STD_OFF   Function is not provided
*/
/* !LINKSTO Mirror.ASR44.ECUC_Mirror_00003,1 */
#if(defined MIRROR_DEV_ERROR_DETECT)
#error MIRROR_DEV_ERROR_DETECT already defined!
#endif /* #if(defined MIRROR_DEV_ERROR_DETECT)*/
#define MIRROR_DEV_ERROR_DETECT        STD_[!IF "MirrorGeneral/MirrorDevErrorDetect = 'true'"!]ON[!ELSE!]OFF[!ENDIF!]

/** \brief Support of Mirror_GetVersionInfo()
 ** This macro defines whether the Mirror_GetVersionInfo is provided or not.
 ** STD_ON    Function is provided
 ** STD_OFF   Function is not provided
*/
#if(defined MIRROR_VERSION_INFO_API)
#error MIRROR_VERSION_INFO_API already defined!
#endif /* #if(defined MIRROR_VERSION_INFO_API)*/
#define MIRROR_VERSION_INFO_API        STD_[!IF "MirrorGeneral/MirrorVersionInfoApi = 'true'"!]ON[!ELSE!]OFF[!ENDIF!]

/** \brief The TimeBaseId the Mirror module will use. */
#if(defined MIRROR_TIMEBASEID)
#error MIRROR_TIMEBASEID already defined!
#endif /* #if(defined MIRROR_TIMEBASEID)*/
#define MIRROR_TIMEBASEID        [!IF "node:exists(as:modconf('Mirror')[1]/MirrorGeneral/MirrorCustomGetTimeFuncName)"!]0U[!ELSE!][!"node:value(as:ref(as:modconf('Mirror')[1]/MirrorGeneral/MirrorStbRef)/StbMSynchronizedTimeBaseIdentifier)"!]U[!ENDIF!]
[!CALL "InitialDestNetworkIndex"!][!//

/** \brief The initial destination network network the Mirror module will use. */
#if(defined MIRROR_INITIAL_DEST_NETWORK_IDX)
#error MIRROR_INITIAL_DEST_NETWORK_IDX already defined!
#endif /* #if(defined MIRROR_INITIAL_DEST_NETWORK_IDX)*/
#define MIRROR_INITIAL_DEST_NETWORK_IDX        [!"num:i($InitDestIndex)"!]U
[!CALL "NumOfSrcControllers"!][!//

/** \brief Number of source controllers or channels configured for all source networks. */
#if(defined MIRROR_NO_OF_SOURCECONTROLLERS)
#error MIRROR_NO_OF_SOURCECONTROLLERS already defined!
#endif /* #if(defined MIRROR_NO_OF_SOURCECONTROLLERS)*/
#define MIRROR_NO_OF_SOURCECONTROLLERS        [!"num:i($SrcControllerCount)"!]U

/* !LINKSTO Mirror.EB.MirrorGetCurrentTime,1 */
/** \brief The function used to get the current time wheter from StbM or a custom function. */
#if(defined MIRROR_GET_TIME_STAMP)
#error MIRROR_GET_TIME_STAMP already defined!
#endif /* #if(defined MIRROR_GET_TIME_STAMP)*/
#define MIRROR_GET_TIME_STAMP(TimeStamp,UserData)    [!IF "node:exists(as:modconf('Mirror')[1]/MirrorGeneral/MirrorCustomGetTimeFuncName)"!][!"node:value(as:modconf('Mirror')[1]/MirrorGeneral/MirrorCustomGetTimeFuncName)"!](MIRROR_TIMEBASEID, TimeStamp, UserData)[!ELSE!]StbM_GetCurrentTime(MIRROR_TIMEBASEID, TimeStamp, UserData)[!ENDIF!]
[!IF "(node:exists(as:modconf('Mirror')[1]/MirrorGeneral/MirrorLinLostFrameCallBack)) and not(node:empty(as:modconf('Mirror')[1]/MirrorGeneral/MirrorLinFramesPerSecond))"!][!//

/** \brief The call back function called in case of a lost LIN frame. */
#if(defined MIRROR_LIN_LOST_FRAME_CBK)
#error MIRROR_LIN_LOST_FRAME_CBK already defined!
#endif /* #if(defined MIRROR_LIN_LOST_FRAME_CBK)*/
#define MIRROR_LIN_LOST_FRAME_CBK() [!"node:value(as:modconf('Mirror')[1]/MirrorGeneral/MirrorLinLostFrameCallBack)"!]()
[!ENDIF!][!//
[!IF "(node:exists(as:modconf('Mirror')[1]/MirrorGeneral/MirrorCanLostFrameCallBack)) and not(node:empty(as:modconf('Mirror')[1]/MirrorGeneral/MirrorCanFramesPerSecond))"!][!//

/** \brief The call back function called in case of a lost CAN frame. */
#if(defined MIRROR_CAN_LOST_FRAME_CBK)
#error MIRROR_CAN_LOST_FRAME_CBK already defined!
#endif /* #if(defined MIRROR_CAN_LOST_FRAME_CBK)*/
#define MIRROR_CAN_LOST_FRAME_CBK() [!"node:value(as:modconf('Mirror')[1]/MirrorGeneral/MirrorCanLostFrameCallBack)"!]()
[!ENDIF!][!//
[!IF "(node:exists(as:modconf('Mirror')[1]/MirrorGeneral/MirrorCanFDLostFrameCallBack)) and not(node:empty(as:modconf('Mirror')[1]/MirrorGeneral/MirrorCanFDFramesPerSecond))"!][!//

/** \brief The call back function called in case of a lost CANFD frame. */
#if(defined MIRROR_CANFD_LOST_FRAME_CBK)
#error MIRROR_CANFD_LOST_FRAME_CBK already defined!
#endif /* #if(defined MIRROR_CANFD_LOST_FRAME_CBK)*/
#define MIRROR_CANFD_LOST_FRAME_CBK() [!"node:value(as:modconf('Mirror')[1]/MirrorGeneral/MirrorCanFDLostFrameCallBack)"!]()
[!ENDIF!][!//
[!CALL "MaxQueueAndBuffSize"!][!//

/** \brief The maximum number of queue buffer size configured for all destination networks. */
#if(defined MIRROR_MAX_QUEUE_SIZE)
#error MIRROR_MAX_QUEUE_SIZE already defined!
#endif /* #if(defined MIRROR_MAX_QUEUE_SIZE)*/
#define MIRROR_MAX_QUEUE_SIZE        [!"num:i($MaxQueueSize)"!]U

/** \brief The maximum buffer size that any destination network would use. */
#if(defined MIRROR_MAX_BUFFER_SIZE)
#error MIRROR_MAX_BUFFER_SIZE already defined!
#endif /* #if(defined MIRROR_MAX_BUFFER_SIZE)*/
#define MIRROR_MAX_BUFFER_SIZE        [!"num:i($MaxBuffSize)"!]U

/** \brief The number of Lin frames that could be stored before the main function starts coping from them. */
#if(defined MIRROR_LIN_ELEMENTCOUNTER)
#error MIRROR_LIN_ELEMENTCOUNTER already defined!
#endif /* #if(defined MIRROR_LIN_ELEMENTCOUNTER)*/
#define MIRROR_LIN_ELEMENTCOUNTER          [!IF "node:empty(as:modconf('Mirror')[1]/MirrorGeneral/MirrorLinFramesPerSecond)"!]MIRROR_ZERO_ELEMENTS[!ELSE!][!"num:i((((as:modconf('Mirror')[1]/MirrorGeneral/MirrorLinFramesPerSecond)) * $MainFuncPeriod) +1)"!]U[!ENDIF!]

/** \brief The number of Can frames that could be stored before the main function starts coping from them. */
#if(defined MIRROR_CAN_ELEMENTCOUNTER)
#error MIRROR_CAN_ELEMENTCOUNTER already defined!
#endif /* #if(defined MIRROR_CAN_ELEMENTCOUNTER)*/
#define MIRROR_CAN_ELEMENTCOUNTER          [!IF "node:empty(as:modconf('Mirror')[1]/MirrorGeneral/MirrorCanFramesPerSecond)"!]MIRROR_ZERO_ELEMENTS[!ELSE!][!"num:i((((as:modconf('Mirror')[1]/MirrorGeneral/MirrorCanFramesPerSecond)) * $MainFuncPeriod) +1)"!]U[!ENDIF!]

/** \brief The number of CanFD frames that could be stored before the main function starts coping from them. */
#if(defined MIRROR_CANFD_ELEMENTCOUNTER)
#error MIRROR_CANFD_ELEMENTCOUNTER already defined!
#endif /* #if(defined MIRROR_CANFD_ELEMENTCOUNTER)*/
#define MIRROR_CANFD_ELEMENTCOUNTER          [!IF "node:empty(as:modconf('Mirror')[1]/MirrorGeneral/MirrorCanFDFramesPerSecond)"!]MIRROR_ZERO_ELEMENTS[!ELSE!][!"num:i((((as:modconf('Mirror')[1]/MirrorGeneral/MirrorCanFDFramesPerSecond)) * $MainFuncPeriod) +1)"!]U[!ENDIF!]

/** \brief Indicating if a LIN source network is configured. */
#if(defined MIRROR_LIN_SOURCENETWORK)
#error MIRROR_LIN_SOURCENETWORK already defined!
#endif /* #if(defined MIRROR_LIN_SOURCENETWORK)*/
#define MIRROR_LIN_SOURCENETWORK          STD_[!IF "node:empty(as:modconf('Mirror')[1]/MirrorGeneral/MirrorLinFramesPerSecond)"!]OFF[!ELSE!]ON[!ENDIF!]

/** \brief Indicating if a CAN source network is configured. */
#if(defined MIRROR_CAN_SOURCENETWORK)
#error MIRROR_CAN_SOURCENETWORK already defined!
#endif /* #if(defined MIRROR_CAN_SOURCENETWORK)*/
#define MIRROR_CAN_SOURCENETWORK          STD_[!IF "node:empty(as:modconf('Mirror')[1]/MirrorGeneral/MirrorCanFramesPerSecond)"!]OFF[!ELSE!]ON[!ENDIF!]

/** \brief Indicating if a CANFD source network is configured. */
#if(defined MIRROR_CANFD_SOURCENETWORK)
#error MIRROR_CANFD_SOURCENETWORK already defined!
#endif /* #if(defined MIRROR_CANFD_SOURCENETWORK)*/
#define MIRROR_CANFD_SOURCENETWORK          STD_[!IF "node:empty(as:modconf('Mirror')[1]/MirrorGeneral/MirrorCanFDFramesPerSecond)"!]OFF[!ELSE!]ON[!ENDIF!]
[!CALL "SrcNetworkCtrlTrcvCheck"!][!//

/** \brief Indicating if any configured can source network has transceiver support. */
#if(defined MIRROR_CANTRCV)
#error MIRROR_CANTRCV already defined!
#endif /* #if(defined MIRROR_CANTRCV)*/
#define MIRROR_CANTRCV          STD_[!IF "$CanTrcvCfg = 1"!]ON[!ELSE!]OFF[!ENDIF!]

/** \brief Indicating if any configured lin source network has transceiver support. */
#if(defined MIRROR_LINTRCV)
#error MIRROR_LINTRCV already defined!
#endif /* #if(defined MIRROR_LINTRCV)*/
#define MIRROR_LINTRCV          STD_[!IF "$LinTrcvCfg = 1"!]ON[!ELSE!]OFF[!ENDIF!]

/** \brief Indicating if any configured can source network has transceiver support. */
#if(defined MIRROR_CANIPCSUPPORT)
#error MIRROR_CANIPCSUPPORT already defined!
#endif /* #if(defined MIRROR_CANIPCSUPPORT)*/
#define MIRROR_CANIPCSUPPORT          STD_[!IF "as:modconf('Mirror')[1]/MirrorGeneral/MirrorUseCanIfIPC = 'true'"!]ON[!ELSE!]OFF[!ENDIF!]

/** \brief Indicating if any configured lin source network has transceiver support. */
#if(defined MIRROR_LINIPCSUPPORT)
#error MIRROR_LINIPCSUPPORT already defined!
#endif /* #if(defined MIRROR_LINIPCSUPPORT)*/
#define MIRROR_LINIPCSUPPORT          STD_[!IF "as:modconf('Mirror')[1]/MirrorGeneral/MirrorUseLinIfIPC = 'true'"!]ON[!ELSE!]OFF[!ENDIF!]

/** \brief Indicating The number of Can source networks. */
#if(defined MIRROR_CANCTRLCNT)
#error MIRROR_CANCTRLCNT already defined!
#endif /* #if(defined MIRROR_CANCTRLCNT)*/
#define MIRROR_CANCTRLCNT          [!"num:i($CanCtrlCount)"!]U

/** \brief Indicating The number of Lin source networks. */
#if(defined MIRROR_LINCTRLCNT)
#error MIRROR_LINCTRLCNT already defined!
#endif /* #if(defined MIRROR_LINCTRLCNT)*/
#define MIRROR_LINCTRLCNT          [!"num:i($LinCtrlCount)"!]U

/*==================[type definitions]======================================*/

/*==================[external function declarations]========================*/

/*==================[internal function declarations]========================*/

/*==================[external constants]====================================*/
#define MIRROR_START_SEC_CONFIG_DATA_UNSPECIFIED
#include <Mirror_MemMap.h>

extern CONST(Mirror_DestNetworkType, MIRROR_APPL_CONST) Mirror_DestNetworks[MIRROR_NO_OF_DESTNETWORKS];

extern CONST(Mirror_SourceNetworkType, MIRROR_APPL_CONST) Mirror_SourceNetworks[MIRROR_NO_OF_SOURCENETWORKS];

#define MIRROR_STOP_SEC_CONFIG_DATA_UNSPECIFIED
#include <Mirror_MemMap.h>

#define MIRROR_START_SEC_CONFIG_DATA_8
#include <Mirror_MemMap.h>

extern CONST(uint8, MIRROR_APPL_CONST) Mirror_SourceNetworkControllers[MIRROR_NO_OF_SOURCECONTROLLERS];

#define MIRROR_STOP_SEC_CONFIG_DATA_8
#include <Mirror_MemMap.h>

/*==================[internal constants]====================================*/

/*==================[external data]=========================================*/
#define MIRROR_START_SEC_VAR_CLEARED_LOCAL_8
#include <Mirror_MemMap.h>

/** \brief The buffer provided to the lower layer to transmit the PDUs. */
extern VAR(uint8, MIRROR_VAR) TxBuffer[MIRROR_MAX_BUFFER_SIZE];

#define MIRROR_STOP_SEC_VAR_CLEARED_LOCAL_8
#include <Mirror_MemMap.h>

#define MIRROR_START_SEC_VAR_CLEARED_LOCAL_UNSPECIFIED
#include <Mirror_MemMap.h>

/** \brief Variable to indicate the if the source network is started. */
extern VAR(Mirror_SourceNetworkStatusType, MIRROR_VAR) Mirror_SourceNetworkStatus[MIRROR_NO_OF_SOURCENETWORKS];

extern VAR(Mirror_QueueBufferStatusType, MIRROR_VAR) Mirror_QueueBufferStatus[MIRROR_MAX_QUEUE_SIZE];

#define MIRROR_STOP_SEC_VAR_CLEARED_LOCAL_UNSPECIFIED
#include <Mirror_MemMap.h>

[!IF "node:exists(as:modconf('Mirror')[1]/MirrorGeneral/MirrorLinFramesPerSecond)"!][!//
#define MIRROR_START_SEC_LIN_VAR_NO_INIT_GLOBAL_UNSPECIFIED
#include <Mirror_MemMap.h>

extern VAR(Mirror_LinElementType, MIRROR_VAR) Mirror_LinElement[MIRROR_LIN_ELEMENTCOUNTER];

extern VAR(MIRROR_TIMESTAMP_TYPE, MIRROR_VAR) Mirror_LinTimeStamp[MIRROR_LIN_ELEMENTCOUNTER];

#define MIRROR_STOP_SEC_LIN_VAR_NO_INIT_GLOBAL_UNSPECIFIED
#include <Mirror_MemMap.h>
[!ENDIF!][!//

[!IF "node:exists(as:modconf('Mirror')[1]/MirrorGeneral/MirrorCanFramesPerSecond)"!][!//
#define MIRROR_START_SEC_CAN_VAR_NO_INIT_GLOBAL_UNSPECIFIED
#include <Mirror_MemMap.h>

extern VAR(Mirror_CanElementType, MIRROR_VAR) Mirror_CanElement[MIRROR_CAN_ELEMENTCOUNTER];

extern VAR(MIRROR_TIMESTAMP_TYPE, MIRROR_VAR) Mirror_CanTimeStamp[MIRROR_CAN_ELEMENTCOUNTER];

[!IF "node:exists(as:modconf('Mirror')[1]/MirrorGeneral/MirrorCanFDFramesPerSecond)"!][!//
extern VAR(Mirror_CanFDElementType, MIRROR_VAR) Mirror_CanFDElement[MIRROR_CANFD_ELEMENTCOUNTER];

extern VAR(MIRROR_TIMESTAMP_TYPE, MIRROR_VAR) Mirror_CanFDTimeStamp[MIRROR_CANFD_ELEMENTCOUNTER];
[!ENDIF!][!//

#define MIRROR_STOP_SEC_CAN_VAR_NO_INIT_GLOBAL_UNSPECIFIED
#include <Mirror_MemMap.h>
[!ENDIF!][!//

#define MIRROR_START_SEC_VAR_NO_INIT_GLOBAL_[!"num:i(ecu:get('Cpu.Type'))"!]
#include <Mirror_MemMap.h>

[!IF "node:exists(as:modconf('Mirror')[1]/MirrorGeneral/MirrorLinFramesPerSecond)"!][!//
extern VAR(Atomic_t, MIRROR_VAR) Mirror_LinElementWriteIndex;
[!ENDIF!][!//

[!IF "node:exists(as:modconf('Mirror')[1]/MirrorGeneral/MirrorCanFramesPerSecond)"!][!//
extern VAR(Atomic_t, MIRROR_VAR) Mirror_CanElementWriteIndex;
[!ENDIF!][!//

[!IF "node:exists(as:modconf('Mirror')[1]/MirrorGeneral/MirrorCanFramesPerSecond)"!][!//
extern VAR(Atomic_t, MIRROR_VAR) Mirror_CanFDElementWriteIndex;
[!ENDIF!][!//

#define MIRROR_STOP_SEC_VAR_NO_INIT_GLOBAL_[!"num:i(ecu:get('Cpu.Type'))"!]
#include <Mirror_MemMap.h>


/*==================[internal data]=========================================*/

/*==================[external function definitions]=========================*/

/*==================[internal function definitions]=========================*/

#endif /* if !defined( MIRROR_CFG_H ) */
/*==================[end of file]===========================================*/
[!ENDCODE!]