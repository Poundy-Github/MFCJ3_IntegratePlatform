/**
 * \file
 *
 * \brief AUTOSAR CanTp
 *
 * This file contains the implementation of the AUTOSAR
 * module CanTp.
 *
 * \author Elektrobit Automotive GmbH, 91058 Erlangen, Germany
 *
 * Copyright 2005 - 2019 Elektrobit Automotive GmbH
 * All rights exclusively reserved for Elektrobit Automotive GmbH,
 * unless expressly agreed to otherwise.
 */

/*==================[inclusions]============================================*/

#include <CanTp_Trace.h>
#include <TSAutosar.h>         /* EB specific standard types */
#include <ComStack_Types.h>    /* typedefs for AUTOSAR com stack */
#include <CanTp_InternalLib.h> /* internal macros and variables */
#include <CanTp_Internal.h>    /* internal macros and variables */
#include <CanIf.h>             /* CanIf module types and API */

/*==================[macros]================================================*/

/*==================[type definitions]======================================*/

/*==================[external function declarations]========================*/

/*==================[internal function declarations]========================*/

/*==================[external constants]====================================*/

/*==================[internal constants]====================================*/

/*==================[external data]=========================================*/

/*==================[internal data]=========================================*/

/*==================[external function definitions]=========================*/

#if(TS_MERGED_COMPILE == STD_OFF)
#define CANTP_START_SEC_CODE
#include <CanTp_MemMap.h>
#endif /* TS_MERGED_COMPILE == STD_OFF */

#if(CANTP_JUMPTABLE_MODE != CANTP_JUMPTABLE_CLIENT)

FUNC(void, CANTP_CODE) CanTp_TransmitFrame
(
  P2VAR(CanTp_ChannelType, AUTOMATIC, CANTP_VAR) ChannelPtr
)
{
  PduInfoType       PduInfo;  /* data to be transmitted */
  /* Id of affected N-SDU */
  const PduIdType NSduId = ChannelPtr->NSduId;
  PduIdType         LSduId;   /* LSduId to transmit via CanIf */
  Std_ReturnType    CanIfRet; /* return value of CanIf */
  CanTp_ChStateType ChannelState;

  /* init */
  PduInfo.SduLength  = ChannelPtr->CanIfDLC;
  PduInfo.SduDataPtr = (P2VAR(uint8, AUTOMATIC, CANTP_APPL_DATA)) ChannelPtr->CanIfData;

  /* CanIf might be in passive mode and respond within the CanIf_Transmit()
     call. Therefore the state will be set now.
   */
  TS_AtomicAssign8(ChannelState, ChannelPtr->State);

  /* get LSduId */
  if(CANTP_CH_GET_MODE(ChannelState) == CANTP_CH_MODE_RX)
  {
    LSduId = CANTP_CFG_GET_RXNSDU_CONFIG(NSduId).LSduIdFc;
  }
  else
  {
    /* isn't Rx -> must be Tx */
    LSduId = CANTP_CFG_GET_TXNSDU_CONFIG(NSduId).LSduIdxF;
  }

  /* switch to next state */
  CANTP_CH_SET_ACTION(ChannelPtr, CANTP_CH_ACTION_CONFIRM);

  /* now transmit data to CanIf */
  CanIfRet = CANTP_CANIF_TRANSMIT(LSduId, &PduInfo);

  if(CanIfRet == E_OK)
  {
    /* Reset send buffer */
    ChannelPtr->CanIfDLC = 0U;
  }
  else
  {
    /* !LINKSTO CanTp.EB.11310, 2 */
    /* !LINKSTO CanTp.EB.11310_2, 1 */
    CanTp_StopChannel(ChannelPtr, CANTP_ULIND_STATUS, NTFRSLT_E_NOT_OK);
  }
}

#endif /* CANTP_JUMPTABLE_MODE != CANTP_JUMPTABLE_CLIENT */

#if(TS_MERGED_COMPILE == STD_OFF)
#define CANTP_STOP_SEC_CODE
#include <CanTp_MemMap.h>
#endif /* TS_MERGED_COMPILE == STD_OFF */

/*==================[internal function definitions]=========================*/

/*==================[end of file]===========================================*/
