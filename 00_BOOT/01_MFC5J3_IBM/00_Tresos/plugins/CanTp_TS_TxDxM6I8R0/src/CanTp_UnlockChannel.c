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

/*==================[inclusions]=============================================*/

#include <CanTp_Trace.h>
#include <TSAutosar.h>         /* EB specific standard types */
#include <ComStack_Types.h>    /* typedefs for AUTOSAR com stack */
#include <CanTp_Internal.h>    /* internal macros and variables */
#include <CanTp_Cbk.h>         /* CanTp callback declarations */

/*==================[macros]=================================================*/

/*==================[type definitions]=======================================*/

/*==================[external function declarations]=========================*/

/*==================[internal function declarations]=========================*/

/*==================[external constants]=====================================*/

/*==================[internal constants]=====================================*/

/*==================[external data]==========================================*/

/*==================[internal data]==========================================*/

/*==================[external function definitions]==========================*/

#if(TS_MERGED_COMPILE == STD_OFF)
#define CANTP_START_SEC_CODE
#include <CanTp_MemMap.h>
#endif /* TS_MERGED_COMPILE == STD_OFF */

#if(CANTP_JUMPTABLE_MODE != CANTP_JUMPTABLE_CLIENT)

FUNC(void, CANTP_CODE) CanTp_UnlockChannel
(
  P2VAR(CanTp_ChannelType, AUTOMATIC, CANTP_VAR) ChannelPtr
)
{
  CanTp_ChStateType ChannelState;
  boolean PostponedFlags = FALSE;

  do
  {
    boolean TimeoutDetected = FALSE;

    TS_AtomicAssign8(ChannelState, ChannelPtr->State);

    /* Check if timeout occurred during channel lock */
    if(ChannelState != CANTP_CH_IDLE)
    {
      CANTP_ENTER_CRITICAL_SECTION();
      /* if post ticks are available */
      if(ChannelPtr->PostTicks > 0U)
      {
        /* shutdown channel, if Postticks already exceeded Ticks */
        if(ChannelPtr->PostTicks >= ChannelPtr->Ticks)
        {
          ChannelPtr->Ticks = 0U;
          TimeoutDetected = TRUE;
        }
        else
        {
          /* count down the Postticks */
          ChannelPtr->Ticks -= ChannelPtr->PostTicks;
          ChannelPtr->PostTicks = 0U;
          TimeoutDetected = FALSE;
        }
      }
      CANTP_LEAVE_CRITICAL_SECTION();
    }

    /* Perform timeout task if required. */
    if(TimeoutDetected)
    {
      CanTp_TimeoutHandling(ChannelPtr);
    }

    CANTP_ENTER_CRITICAL_SECTION();

    if(
         ChannelPtr->PostRxIndFlag
         || ChannelPtr->PostTxConfFlag
         || ChannelPtr->PostSTminFlag
      )
    {
      PostponedFlags = TRUE;
    }
    else
    {
      /* No postponed tasks left */
      PostponedFlags = FALSE;
      /* now unlock channel */
      ChannelPtr->ChannelLockFlag = 0U;
    }

    CANTP_LEAVE_CRITICAL_SECTION();

    if(PostponedFlags)
    {
      /* Process Tx confirmation before Rx indication.
         This shall avoid that Frame is rejected because channel is not in the
         proper state (waiting for the pending Tx confirmation).
       */
      CanTp_PostTxConfirmation(ChannelPtr);

      CanTp_PostRxIndication(ChannelPtr);

      CanTp_PostSTminCallback(ChannelPtr);
    }
  } while(PostponedFlags); /* Loop until all postponed tasks are done */
}

#endif /* CANTP_JUMPTABLE_MODE != CANTP_JUMPTABLE_CLIENT */

#if(TS_MERGED_COMPILE == STD_OFF)
#define CANTP_STOP_SEC_CODE
#include <CanTp_MemMap.h>
#endif /* TS_MERGED_COMPILE == STD_OFF */

/*==================[internal function definitions]==========================*/

/*==================[end of file]============================================*/
