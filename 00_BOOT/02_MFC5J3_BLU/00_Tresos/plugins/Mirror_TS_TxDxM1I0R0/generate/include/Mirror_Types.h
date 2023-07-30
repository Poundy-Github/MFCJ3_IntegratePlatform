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

#if(!defined MIRROR_TYPES_H)
#define MIRROR_TYPES_H

/*==================[inclusions]============================================*/

#include <TSAutosar.h>            /* Specific standard types */
#include <ComStack_Types.h>       /* AUTOSAR Communication Stack types */
#include <Atomics.h>              /* Atomics public APIs */
/* !LINKSTO Mirror.ASR44.SWS_Mirror_00142,1 */
[!IF "node:exists(as:modconf('Mirror')[1]/MirrorGeneral/MirrorCanFramesPerSecond)"!][!//
#include <CanIf.h>                /* CanIf public Api for Mirror */
[!ENDIF!][!//
/* !LINKSTO Mirror.ASR44.SWS_Mirror_00143,1 */
[!IF "node:exists(as:modconf('Mirror')[1]/MirrorGeneral/MirrorLinFramesPerSecond)"!][!//
#include <LinIf.h>                /* LinIf public Api for Mirror */
[!ENDIF!][!//
/* !LINKSTO Mirror.EB.MirrorCustomTimeStampHeader,1 */
[!IF "node:exists(as:modconf('Mirror')[1]/MirrorGeneral/MirrorCustomTimeFileName)"!][!//
#include "[!"node:value(as:modconf('Mirror')[1]/MirrorGeneral/MirrorCustomTimeFileName)"!]"     /* Custom time stamp file provided by the user */
[!ELSE!][!//
/* !LINKSTO Mirror.ASR44.SWS_Mirror_00147,1 */
#include <StbM.h>                 /* StbM public Api for Mirror */
[!ENDIF!]
[!INCLUDE "../include/Mirror_PrecompileMacros.m"!][!//
#include <Rte_Mirror_Type.h>
/*==================[macros]================================================*/

/** \brief Mirror Invalid network value .*/
/* !LINKSTO Mirror.ASR44.SWS_Mirror_00165,1 */
#if(defined MIRROR_INVALID_NETWORK)
#error MIRROR_INVALID_NETWORK already defined!
#endif /* #if(defined MIRROR_INVALID_NETWORK)*/
#define MIRROR_INVALID_NETWORK        0xFFU

/** \brief No data elements were generated for a bus type. */
#if(defined MIRROR_ZERO_ELEMENTS)
#error MIRROR_ZERO_ELEMENTS already defined!
#endif /* #if(defined MIRROR_ZERO_ELEMENTS)*/
#define MIRROR_ZERO_ELEMENTS        0x00U

/** \brief Transmission deadline configuration parameter was disabled. */
#if(defined MIRROR_TRANSMISSIONDEADLINE_DISABLED)
#error MIRROR_TRANSMISSIONDEADLINE_DISABLED already defined!
#endif /* #if(defined MIRROR_TRANSMISSIONDEADLINE_DISABLED)*/
#define MIRROR_TRANSMISSIONDEADLINE_DISABLED        0xFFFF

/** \brief No transceiver support for the network. */
#if(defined MIRROR_NO_NETWORKTRCV)
#error MIRROR_NO_NETWORKTRCV already defined!
#endif /* #if(defined MIRROR_NO_NETWORKTRCV)*/
#define MIRROR_NO_NETWORKTRCV        0xFFU

/** \brief Number of configured destination networks. */
#if(defined MIRROR_NO_OF_DESTNETWORKS)
#error MIRROR_NO_OF_DESTNETWORKS already defined!
#endif /* #if(defined MIRROR_NO_OF_DESTNETWORKS)*/
#define MIRROR_NO_OF_DESTNETWORKS        [!"num:i($Mirror_DestNetworkSize)"!]U

/** \brief Number of configured source networks. */
#if(defined MIRROR_NO_OF_SOURCENETWORKS)
#error MIRROR_NO_OF_SOURCENETWORKS already defined!
#endif /* #if(defined MIRROR_NO_OF_SOURCENETWORKS)*/
#define MIRROR_NO_OF_SOURCENETWORKS        [!"num:i($Mirror_SourceNetworkSize)"!]U

/** \brief Max Lin type frame size. */
#if(defined MIRROR_LIN_FRAME_SIZE)
#error MIRROR_LIN_FRAME_SIZE already defined!
#endif /* #if(defined MIRROR_LIN_FRAME_SIZE)*/
#define MIRROR_LIN_FRAME_SIZE        [!IF "node:empty(as:modconf('Mirror')[1]/MirrorGeneral/MirrorLinMaxFrameSize)"!]0x08U[!ELSE!][!"num:i(as:modconf('Mirror')[1]/MirrorGeneral/MirrorLinMaxFrameSize)"!]U[!ENDIF!]

/** \brief Max Can type frame size. */
#if(defined MIRROR_CAN_FRAME_SIZE)
#error MIRROR_CAN_FRAME_SIZE already defined!
#endif /* #if(defined MIRROR_CAN_FRAME_SIZE)*/
#define MIRROR_CAN_FRAME_SIZE        [!IF "node:empty(as:modconf('Mirror')[1]/MirrorGeneral/MirrorCanMaxFrameSize)"!]0x08U[!ELSE!][!"num:i(as:modconf('Mirror')[1]/MirrorGeneral/MirrorCanMaxFrameSize)"!]U[!ENDIF!]

/** \brief Max CanFD type frame size. */
#if(defined MIRROR_CANFD_FRAME_SIZE)
#error MIRROR_CANFD_FRAME_SIZE already defined!
#endif /* #if(defined MIRROR_CANFD_FRAME_SIZE)*/
#define MIRROR_CANFD_FRAME_SIZE        [!IF "node:empty(as:modconf('Mirror')[1]/MirrorGeneral/MirrorCanFDMaxFrameSize)"!]0x40U[!ELSE!][!"num:i(as:modconf('Mirror')[1]/MirrorGeneral/MirrorCanFDMaxFrameSize)"!]U[!ENDIF!]

/** \brief TimeStamp_Type wheter using StbM or custom type. */
#if(defined MIRROR_TIMESTAMP_TYPE)
#error MIRROR_TIMESTAMP_TYPE already defined!
#endif /* #if(defined MIRROR_TIMESTAMP_TYPE)*/
#define MIRROR_TIMESTAMP_TYPE        [!IF "node:exists(as:modconf('Mirror')[1]/MirrorGeneral/MirrorCustomTimeFileName)"!]Mirror_TimeStampType[!ELSE!]StbM_TimeStampType[!ENDIF!]

/** \brief UserData_Type wheter using StbM or custom type. */
#if(defined MIRROR_USERDATA_TYPE)
#error MIRROR_USERDATA_TYPE already defined!
#endif /* #if(defined MIRROR_USERDATA_TYPE)*/
#define MIRROR_USERDATA_TYPE        [!IF "node:exists(as:modconf('Mirror')[1]/MirrorGeneral/MirrorCustomTimeFileName)"!]Mirror_UserDataType[!ELSE!]StbM_UserDataType[!ENDIF!]

/** \brief SynchronizedTimeBaseType wheter using StbM or custom type. */
#if(defined MIRROR_SYNCHRONIZEDTIMEBASE_TYPE)
#error MIRROR_SYNCHRONIZEDTIMEBASE_TYPE already defined!
#endif /* #if(defined MIRROR_SYNCHRONIZEDTIMEBASE_TYPE)*/
#define MIRROR_SYNCHRONIZEDTIMEBASE_TYPE        [!IF "node:exists(as:modconf('Mirror')[1]/MirrorGeneral/MirrorCustomTimeFileName)"!]Mirror_SynchronizedTimeBaseType[!ELSE!]StbM_SynchronizedTimeBaseType[!ENDIF!]

/*==================[type definitions]======================================*/

/* !LINKSTO Mirror.ASR44.SWS_Mirror_01032,1 */
typedef VAR(uint32, TYPEDEF) Mirror_CanIdType;

typedef struct
{
  CONST(PduIdType, TYPEDEF) DestNetworkSrcPduRId;
  CONST(PduIdType, TYPEDEF) DestNetworkPduId;
  CONST(uint16, TYPEDEF) DestNetworkPduLength;
  CONST(uint16, TYPEDEF) DestQueueSizeRange;
  CONST(boolean, TYPEDEF) DestTxDeadlineEnable;
  CONST(uint16, TYPEDEF) DestTxDeadline;
  CONST(uint16, TYPEDEF) DestTxConfirmationTimeout;
  CONST(NetworkHandleType, TYPEDEF) ComMChannelId;
  CONST(Mirror_NetworkType, TYPEDEF) NetworkType;
  CONST(uint8, TYPEDEF) MirrorNetworkId;
  CONST(boolean, TYPEDEF) TriggerTxEnable;
}Mirror_DestNetworkType;

typedef struct
{
  CONST(NetworkHandleType, TYPEDEF) ComMChannelId;
  CONST(Mirror_NetworkType, TYPEDEF) NetworkType;
  CONST(uint8, TYPEDEF) SourceNetworkControllerIndex;
  CONST(uint8, TYPEDEF) NumOfSourceNetworkControllers;
  CONST(uint8, TYPEDEF) MirrorNetworkId;
  CONST(uint8, TYPEDEF) TrcvId;
  CONST(boolean,TYPEDEF) TrcvConfigured;
}Mirror_SourceNetworkType;

typedef struct
{
  VAR(Atomic_t, TYPEDEF) SourceNetworkRequestedActivationStatus;
  VAR(boolean, TYPEDEF) IsSourceNetworkStarted;
  VAR(boolean, TYPEDEF) IsStatusReported;
  VAR(uint8, TYPEDEF) SourceNetworkCurrentStatusByte;
  VAR(uint8, TYPEDEF) SourceNetworkOldStatusByte;
}Mirror_SourceNetworkStatusType;

typedef struct
{
  VAR(Atomic_t, TYPEDEF) TxTimer;
  VAR(uint16, TYPEDEF) FrameLength;
  VAR(uint8, TYPEDEF) QueueBuffStatus;
  VAR(uint8, TYPEDEF) MirroredSourceNetworksCount;
  VAR(uint8, TYPEDEF) MirroredSourceNetworks[MIRROR_NO_OF_SOURCENETWORKS];
}Mirror_QueueBufferStatusType;

/* !LINKSTO Mirror.ASR44.SWS_Mirror_01002,1 */
typedef struct
{
  VAR(uint8, TYPEDEF) dummy;
}Mirror_ConfigType;
[!IF "node:exists(as:modconf('Mirror')[1]/MirrorGeneral/MirrorLinFramesPerSecond)"!]
typedef struct
{
  VAR(uint8,TYPEDEF) FrameID;
  VAR(uint8, TYPEDEF) ElementLength;
  VAR(uint8, TYPEDEF) ElementStatus;
  VAR(uint8, TYPEDEF) NetworkStatus;
  VAR(uint8, TYPEDEF) ElementSrcNtwrk;
  VAR(uint8, TYPEDEF) DataElement[MIRROR_LIN_FRAME_SIZE];
}Mirror_LinElementType;
[!ENDIF!][!//
[!IF "node:exists(as:modconf('Mirror')[1]/MirrorGeneral/MirrorCanFramesPerSecond)"!]
typedef struct
{
  VAR(uint32,TYPEDEF) FrameID;
  VAR(uint8, TYPEDEF) ElementLength;
  VAR(uint8, TYPEDEF) ElementStatus;
  VAR(uint8, TYPEDEF) ElementSrcNtwrk;
  VAR(uint8, TYPEDEF) DataElement[MIRROR_CAN_FRAME_SIZE];
}Mirror_CanElementType;

typedef struct
{
  VAR(uint32,TYPEDEF) FrameID;
  VAR(uint8, TYPEDEF) ElementLength;
  VAR(uint8, TYPEDEF) ElementStatus;
  VAR(uint8, TYPEDEF) ElementSrcNtwrk;
  VAR(uint8, TYPEDEF) DataElement[MIRROR_CANFD_FRAME_SIZE];
}Mirror_CanFDElementType;
[!ENDIF!]

/*==================[external function declarations]========================*/

/*==================[internal function declarations]========================*/

/*==================[external constants]====================================*/

/*==================[internal constants]====================================*/

/*==================[external data]=========================================*/

/*==================[internal data]=========================================*/

/*==================[external function definitions]=========================*/

/*==================[internal function definitions]=========================*/

#endif /* if !defined(MIRROR_TYPES_H) */
/*==================[end of file]===========================================*/
