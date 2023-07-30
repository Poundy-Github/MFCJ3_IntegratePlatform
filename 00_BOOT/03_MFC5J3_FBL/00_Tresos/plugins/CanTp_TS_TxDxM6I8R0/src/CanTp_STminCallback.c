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
#include <CanTp_Internal.h>    /* internal macros and variables */

/*==================[macros]================================================*/

/*==================[type definitions]======================================*/

/*==================[external function declarations]========================*/

/*==================[internal function declarations]========================*/
#if(TS_MERGED_COMPILE == STD_OFF)
#define CANTP_START_SEC_CODE
#include <CanTp_MemMap.h>
#endif /* TS_MERGED_COMPILE == STD_OFF */

#if(CANTP_JUMPTABLE_MODE != CANTP_JUMPTABLE_CLIENT)

/** \brief Function to process STmin timeout
 **
 ** This function takes care of sending the next CF after STmin has elapsed
 **
 ** \param[in] ChannelPtr  pointer to channel data structure to ease lookups
 */
STATIC FUNC(void, CANTP_CODE) CanTp_STminTimeoutHandling
(
  P2VAR(CanTp_ChannelType, AUTOMATIC, CANTP_VAR) ChannelPtr
);

#endif /* CANTP_JUMPTABLE_MODE != CANTP_JUMPTABLE_CLIENT */

#if(TS_MERGED_COMPILE == STD_OFF)
#define CANTP_STOP_SEC_CODE
#include <CanTp_MemMap.h>
#endif /* TS_MERGED_COMPILE == STD_OFF */
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

FUNC(void, CANTP_CODE) CanTp_STminCallback
(
  CanTp_ChType Channel
)
{
  P2VAR(CanTp_ChannelType, AUTOMATIC, CANTP_VAR) ChannelPtr;
  boolean STminCallbackFlag = FALSE;

  ChannelPtr = &CanTp_Channel[Channel];

  CANTP_ENTER_CRITICAL_SECTION();

  /* lock channel if possible */
  if(CANTP_IS_CHANNEL_LOCKED(ChannelPtr))
  {
    ChannelPtr->PostSTminFlag = TRUE;
  }
  else
  {
    CANTP_LOCK_CHANNEL(ChannelPtr);
    /* Setting STminCallbackFlag to send next CF */
    STminCallbackFlag = TRUE;
  }
  CANTP_LEAVE_CRITICAL_SECTION();

  if(STminCallbackFlag == (boolean)TRUE)
  {
    CanTp_STminTimeoutHandling(ChannelPtr);
    CANTP_UNLOCK_CHANNEL(ChannelPtr);
  }
}

FUNC(void, CANTP_CODE) CanTp_PostSTminCallback
(
  P2VAR(CanTp_ChannelType, AUTOMATIC, CANTP_VAR) ChannelPtr
)
{
  boolean PendingSTminTimeout = FALSE;

  CANTP_ENTER_CRITICAL_SECTION();
  if(ChannelPtr->PostSTminFlag)
  {
    /* Postponed STmin timeout detected */
    ChannelPtr->PostSTminFlag = FALSE;
    PendingSTminTimeout = TRUE;
  }
  CANTP_LEAVE_CRITICAL_SECTION();

  if(PendingSTminTimeout)
  {
    CanTp_STminTimeoutHandling(ChannelPtr);
  }
}

#endif /* CANTP_JUMPTABLE_MODE != CANTP_JUMPTABLE_CLIENT */

/*==================[internal function definitions]=========================*/
#if(CANTP_JUMPTABLE_MODE != CANTP_JUMPTABLE_CLIENT)

STATIC FUNC(void, CANTP_CODE) CanTp_STminTimeoutHandling
(
  P2VAR(CanTp_ChannelType, AUTOMATIC, CANTP_VAR) ChannelPtr
)
{
  CanTp_ChStateType ChannelState;
  TS_AtomicAssign8(ChannelState, ChannelPtr->State);

  if(ChannelState == CANTP_CH_TX_WAITTMR_CF)
  {
    DBG_CANTP_CHANNEL_STATE_GRP(
                                DBG_CANTP_GET_CHANNEL_INDEX(ChannelPtr),
                                ChannelPtr->State,
                                CANTP_CH_TX_BUFREQ_CF
                               );

    /* Time between 2 frames has elapsed. Start sending next frame */
    TS_AtomicAssign8(ChannelPtr->State, CANTP_CH_TX_BUFREQ_CF);

    CanTp_TxStateHandling(ChannelPtr);
  }
}

#endif /* CANTP_JUMPTABLE_MODE != CANTP_JUMPTABLE_CLIENT */

#if(TS_MERGED_COMPILE == STD_OFF)
#define CANTP_STOP_SEC_CODE
#include <CanTp_MemMap.h>
#endif /* TS_MERGED_COMPILE == STD_OFF */
/*==================[end of file]===========================================*/
