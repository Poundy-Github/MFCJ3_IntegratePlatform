/**
 * \file
 *
 * \brief AUTOSAR PduR
 *
 * This file contains the implementation of the AUTOSAR
 * module PduR.
 *
 * \author Elektrobit Automotive GmbH, 91058 Erlangen, Germany
 *
 * Copyright 2005 - 2019 Elektrobit Automotive GmbH
 * All rights exclusively reserved for Elektrobit Automotive GmbH,
 * unless expressly agreed to otherwise.
 */

/*
 *  MISRA-C:2012 Deviation List
 *
 *  MISRAC2012-1) Deviated Rule: 11.5 (advisory)
 *  A conversion should not be performed from pointer to void into pointer to
 *  object.
 *
 *  Reason:
 *  The memory routines are optimized for dealing with aligned memory sections.
 *
 */
/*==================[inclusions]============================================*/

#include <PduR_Trace.h>
#include <TSAutosar.h>            /* EB specific standard types */
#include <TSAtomic_Assign.h>      /* Atomic assignments from Base PlugIn */
#include <ComStack_Types.h>       /* AUTOSAR Communication Stack types */
#include <PduR_Internal_Static.h> /* Internal API (static part) */
#include <PduR_Api_Depend.h>      /* Public API (depend part) */

#if ((PDUR_ZERO_COST_OPERATION_TP == STD_OFF) && (PDUR_TPGATEWAY_SUPPORT == STD_ON))
#include <PduR_Lcfg.h>            /* Link-time configurable data */
/*==================[macros]================================================*/

/*==================[type definitions]======================================*/

/*==================[external function declarations]========================*/

/*==================[internal function declarations]========================*/

/* AUTOSAR Memory Mapping - start section for code */
#if (TS_MERGED_COMPILE == STD_OFF)
#define PDUR_START_SEC_CODE
#include <PduR_MemMap.h>
#endif

/**
 ** \brief Auxiliary TP gateway handler function
 **
 ** Auxiliary function that allocates a free TP gateway session.
 **
 **
 ** \param[in]  GMPduId             Identification of the received gateway PDU.
 ** \param[in]  TpSduLength         Total length of the PDU to be received.
 ** \param[out] SessionIndexUsed    SessionIndex of the selected TP gateway session.
 **                                 PDUR_NO_GATETP_SESSION_ASSIGNED if no one is free or
 **                                 already one is pending for GMPduId.
 **
 ** \return Result of TP gateway session request
 ** \retval BUFREQ_E_OVFL: No Buffer of the required length can be provided.
 **                        Either it is not configured of that size or temporary not available.
 ** \retval BUFREQ_OK: Otherwise.
 **/
STATIC FUNC(BufReq_ReturnType, PDUR_CODE) PduR_AssignGateTpSession
(
   PduR_PduIdType GMPduId,
   PduR_PduLengthType TpSduLength,
   P2VAR(PduR_GateTpSessionIndexType, AUTOMATIC, PDUR_APPL_DATA) SessionIndexUsed
);

/**
 ** \brief Auxiliary TP gateway handler function
 **
 ** Auxiliary function that determines the index of the first free position in the array
 ** of queued TP gateway sessions.
 **
 ** \param[in]  GMPduId             Identification of the received gateway PDU.
 **
 ** \return Index of the first free position in the array to queue the TP gateway session.
 **         PDUR_NO_GATETP_QUEUEING_POSSIBLE if TP gateway session for GMPduId can not be queued.
 **
 **/
STATIC FUNC(PduR_GateTpQueueIndexType, PDUR_CODE) PduR_GetGateTpQueueIndexHead
(
   PduR_PduIdType GMPduId
);

/*==================[external constants]====================================*/

/*==================[internal constants]====================================*/

/*==================[external data]=========================================*/

/*==================[internal data]=========================================*/

/*==================[external function definitions]=========================*/

FUNC(BufReq_ReturnType, PDUR_CODE) PduR_GateTpStartOfReception
(
   PduIdType GMPduId,
   PduLengthType TpSduLength,
   P2VAR(PduLengthType, AUTOMATIC, PDUR_APPL_DATA) BufferSizePtr
)
{
   BufReq_ReturnType RetVal;

   DBG_PDUR_GATETPSTARTOFRECEPTION_ENTRY(GMPduId, TpSduLength, BufferSizePtr);

#if (PDUR_ROUTINGPATHGROUPS_SUPPORT == STD_ON)
   if(PduR_RPathGroupNumTpGwDestEnabled(GMPduId) > PDUR_RPATHGROUP_NUM_NO_DEST_ENABLED)
#endif
   {
      PduR_GateTpSessionIndexType SessionIndex;

      /* assign TP gateway session,
         no protection since this is the first call of the sequence of calls */
      RetVal = PduR_AssignGateTpSession(GMPduId, TpSduLength, &SessionIndex);

      /* free TP gateway session (TP buffer) assigned */
      if(SessionIndex != PDUR_NO_GATETP_SESSION_ASSIGNED)
      {
         /* pointer to TP buffer configurations */
         CONSTP2CONST(PduR_BufTpConfigType, AUTOMATIC, PDUR_APPL_CONST) pBufTpConfig =
            PDUR_GET_CONFIG_ADDR(PduR_BufTpConfigType, PduR_GConfigPtr->PduR_BufTpConfigRef);

         *BufferSizePtr = pBufTpConfig[SessionIndex].Length;
      }
      /* else: no TP buffer of that size configured, temporary not available or
         already ongoing TP gateway session.
      RetVal = BUFREQ_E_OVFL, BufferSize shall remain unchanged */
   }
#if (PDUR_ROUTINGPATHGROUPS_SUPPORT == STD_ON)
   else
   {
      /* no single destination PDU is active (reachable) */
      RetVal = BUFREQ_E_NOT_OK;
   }
#endif

   DBG_PDUR_GATETPSTARTOFRECEPTION_EXIT(RetVal, GMPduId, TpSduLength, BufferSizePtr);

   return RetVal;
}


/*==================[internal function definitions]=========================*/

STATIC FUNC(BufReq_ReturnType, PDUR_CODE) PduR_AssignGateTpSession
(
   PduR_PduIdType GMPduId,
   PduR_PduLengthType TpSduLength,
   P2VAR(PduR_GateTpSessionIndexType, AUTOMATIC, PDUR_APPL_DATA) SessionIndexUsed
)
{
   PduR_BufTpIndexType  BufTpIndex = 0U;
   BufReq_ReturnType RetVal;

   /* pointer to TP buffer configurations */
   CONSTP2CONST(PduR_BufTpConfigType, AUTOMATIC, PDUR_APPL_CONST) pBufTpConfig =
      PDUR_GET_CONFIG_ADDR(PduR_BufTpConfigType, PduR_GConfigPtr->PduR_BufTpConfigRef);

   /* pointer to routing table */
   CONSTP2CONST(PduR_GTabTpRxType, AUTOMATIC, PDUR_APPL_CONST) pGTabTpRx =
      PDUR_GET_CONFIG_ADDR(PduR_GTabTpRxType, PduR_GConfigPtr->PduR_GTabTpConfig.GTabRxRef);

   /* initial session index, empty element in queue */
   PduR_GateTpSessionIndexType SessionIndex = PDUR_NO_GATETP_SESSION_ASSIGNED;

   /* pointer to TP gateway sessions */
   /* Deviation MISRAC2012-1 */
   CONSTP2VAR(PduR_GateTpSessionInfoType, AUTOMATIC, PDUR_VAR_NOINIT) pSessionInfos =
      PDUR_GET_RAM_ADDR(PduR_GateTpSessionInfoType, PduR_GConfigPtr->PduR_GateTpSessionInfoRef);

   PduR_PduLengthType BufTpThreshold;

   /* provide next queue index to be used for reception */
   PduR_GateTpQueueIndexType QueueIndex = PduR_GetGateTpQueueIndexHead(GMPduId);

   DBG_PDUR_ASSIGNGATETPSESSION_ENTRY(GMPduId, TpSduLength, SessionIndexUsed);

   /* reception request for GMPduId can be handled */
   if(QueueIndex != PDUR_NO_GATETP_QUEUEING_POSSIBLE)
   {
      /* TP buffer threshold for direct routing (no TpThreshold configured) */
      if(pGTabTpRx[GMPduId].TpThreshold == PDUR_GATETPTHRESHOLD_DIRECT)
      {
         BufTpThreshold = TpSduLength;
      }
      /* TP buffer threshold for routing on the fly (TpThreshold configured) */
      else
      {
#if (PDUR_TPGWQUEUE_ENABLE == STD_ON)
         /* for to be queued PDUs, the complete PDU needs to be stored, since only the first
            TP buffer can be considered as ring buffer */
         if (PduR_GateTpNoSessionQueued(GMPduId) == FALSE)
         {
            BufTpThreshold = TpSduLength;
         }
         else
#endif /* (PDUR_TPGWQUEUE_ENABLE == STD_ON)  */
         {
            BufTpThreshold = pGTabTpRx[GMPduId].TpThreshold;
         }
      }

      /* search for free TP buffer */
      /* determine TP buffer of maximum size */
      if(TpSduLength == PDUR_SDU_LENGTH_ZERO)
      {
         /* initially set to allow first while loop */
         uint8 ResultGetBitOccupiedSession;

         /* search for TP buffer in descending order */
         SessionIndex = (PduR_GateTpSessionIndexType)PduR_GConfigPtr->PduR_BufTpCount;

         /* search for free TP gateway session */
         do{
            /* loop is left if free TP gateway session is detected. */
            SessionIndex--;

            /* check if TP gateway session is occupied */
            TS_GetBit(&pSessionInfos[SessionIndex].Status, PDUR_GATETP_OCCUPIED_SES_POS,
                      uint8, ResultGetBitOccupiedSession);

         }while((SessionIndex > 0U) &&
                (ResultGetBitOccupiedSession > 0U) &&
                (BufTpThreshold <= pBufTpConfig[SessionIndex - 1U].Length));

         /* no free TP gateway session detected or not applicable */
         if((ResultGetBitOccupiedSession > 0U) ||
            (BufTpThreshold > pBufTpConfig[SessionIndex].Length))
         {
            SessionIndex = PDUR_NO_GATETP_SESSION_ASSIGNED;
         }
      }
      /*  No TP buffer of the required length can be provided */
      else if(BufTpThreshold > pBufTpConfig[PduR_GConfigPtr->PduR_BufTpCount - 1U].Length)
      {
        /* RetVal BUFREQ_E_OVFL is returned since no session is assigned */
      }
      /* determine free TP buffer next to TpSduLength - direct routing (no TpThreshold configured)
         or TP buffer next to TpThreshold - routing on the fly (TpThreshold configured) */
      else
      {
         uint8 ResultGetBitOccupiedSession;

         /* search for first suitable TP buffer in ascending order */
         while((BufTpIndex < PduR_GConfigPtr->PduR_BufTpCount) &&
               (BufTpThreshold > pBufTpConfig[BufTpIndex].Length))
         {
            /* loop is left if first valid TP buffer size is detected. */
            BufTpIndex++;
         }

         SessionIndex = BufTpIndex;

         /* search for free TP gateway session */
         do{
            /* check if session is occupied */
            TS_GetBit(&pSessionInfos[SessionIndex].Status, PDUR_GATETP_OCCUPIED_SES_POS,
                      uint8, ResultGetBitOccupiedSession);

            /* loop is left if free TP gateway session is detected.
               If its not detected, the final SessionIndex
               holds the value of PduR_GConfigPtr->PduR_BufTpCount. */
            SessionIndex++;

         }while((SessionIndex < PduR_GConfigPtr->PduR_BufTpCount) &&
                (ResultGetBitOccupiedSession > 0U));

         /* no proper TP gateway session detected */
         if(ResultGetBitOccupiedSession > 0U)
         {
            SessionIndex = PDUR_NO_GATETP_SESSION_ASSIGNED;
         }
         else
         {
            /* correction from do-while loop */
            SessionIndex--;
         }
      }
   }

   /* assign TP gateway session and queue at proper position */
   if(SessionIndex != PDUR_NO_GATETP_SESSION_ASSIGNED)
   {
      /* pointer to queue of TP gateway sessions */
      /* Deviation MISRAC2012-1 */
      CONSTP2VAR(PduR_GateTpSessionIndexType, AUTOMATIC, PDUR_VAR_NOINIT) pGateTpSessionIndex =
         PDUR_GET_RAM_ADDR(PduR_GateTpSessionIndexType, pGTabTpRx[GMPduId].SessionQueueMemRef);

      /* both are identical if valid TP gateway session detected */
      BufTpIndex = (PduR_BufTpIndexType)SessionIndex;

      /* provide entry to queue of TP gateway sessions */
      pGateTpSessionIndex[QueueIndex] = SessionIndex;

      /* occupy TP gateway session and initialize */
      TS_AtomicAssign8(pSessionInfos[SessionIndex].Status, (uint8)PDUR_GATETP_RST_STATUS_MSK);
      TS_AtomicSetBit_8(&pSessionInfos[SessionIndex].Status, PDUR_GATETP_OCCUPIED_SES_POS);
      TS_AtomicAssign8(pSessionInfos[SessionIndex].PendTxConfCount,
                       (uint8)PDUR_GATETP_NO_PEND_TXCONF_MSK);
      pSessionInfos[SessionIndex].TpSduLength = TpSduLength;
      pSessionInfos[SessionIndex].RxWriteIndex = 0U;
      pSessionInfos[SessionIndex].AvailableBufferSize = pBufTpConfig[BufTpIndex].Length;

      /* if a TP gateway session is assigned also a TP buffer is assigned and vice versa */
      RetVal = BUFREQ_OK;
   }
   else
   {
     /* no TP buffer of that size configured, temporary not available or
        already ongoing TP gateway session.
        AvailableBufferSize shall remain unchanged */
     RetVal = BUFREQ_E_OVFL;
   }

   *SessionIndexUsed = SessionIndex;

   DBG_PDUR_ASSIGNGATETPSESSION_EXIT(RetVal, GMPduId, TpSduLength, SessionIndexUsed);

   return RetVal;
}


STATIC FUNC(PduR_GateTpQueueIndexType, PDUR_CODE) PduR_GetGateTpQueueIndexHead
(
   PduR_PduIdType GMPduId
)
{
   PduR_GateTpQueueIndexType QueueIndex;

   /* pointer to routing table */
   CONSTP2CONST(PduR_GTabTpRxType, AUTOMATIC, PDUR_APPL_CONST) pGTabTpRx =
      PDUR_GET_CONFIG_ADDR(PduR_GTabTpRxType, PduR_GConfigPtr->PduR_GTabTpConfig.GTabRxRef);

   DBG_PDUR_GETGATETPQUEUEINDEXHEAD_ENTRY(GMPduId);

#if (PDUR_TPGWQUEUE_ENABLE == STD_ON)
   if (pGTabTpRx[GMPduId].SessionQueueDepth > PDUR_GATETPQUEUE_DEPTH_ONE)
   {
      /* pointer to TP gateway session queue info */
      /* Deviation MISRAC2012-1 */
      CONSTP2VAR(PduR_GateTpSessionQueueInfoType, AUTOMATIC, PDUR_VAR_NOINIT) pGateTpSessionQueueInfo =
         PDUR_GET_RAM_ADDR(PduR_GateTpSessionQueueInfoType, PduR_GConfigPtr->PduR_GateTpSessionQueueInfoRef);

      QueueIndex = pGateTpSessionQueueInfo[GMPduId].HeadIdx;
   }
   else
#endif /* (PDUR_TPGWQUEUE_ENABLE == STD_ON)  */
   {
      /* pointer to queue of TP gateway sessions */
      /* Deviation MISRAC2012-1 */
      CONSTP2VAR(PduR_GateTpSessionIndexType, AUTOMATIC, PDUR_VAR_NOINIT) pGateTpSessionIndex =
         PDUR_GET_RAM_ADDR(PduR_GateTpSessionIndexType, pGTabTpRx[GMPduId].SessionQueueMemRef);

      QueueIndex = PDUR_GATETPQUEUE_FIRSTINDEX;

      /* free session can not be queued */
      if(pGateTpSessionIndex[QueueIndex] != PDUR_NO_GATETP_SESSION_ASSIGNED)
      {
         QueueIndex = PDUR_NO_GATETP_QUEUEING_POSSIBLE;
      }
   }

   DBG_PDUR_GETGATETPQUEUEINDEXHEAD_EXIT(QueueIndex, GMPduId);

   return QueueIndex;
}


/* AUTOSAR Memory Mapping - end section for code */
#if (TS_MERGED_COMPILE == STD_OFF)
#define PDUR_STOP_SEC_CODE
#include <PduR_MemMap.h>
#endif

#else /* if (PDUR_ZERO_COST_OPERATION_TP == STD_OFF) && .. */

#include <TSCompiler.h>           /* usage of macro in TSCompiler_Default.h */

/* Avoid empty translation unit according to ISO C90 */
TS_PREVENTEMPTYTRANSLATIONUNIT

#endif /* if (PDUR_ZERO_COST_OPERATION_TP == STD_OFF) && .. */
/*==================[end of file]===========================================*/
