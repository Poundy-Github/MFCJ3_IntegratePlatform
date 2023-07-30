/**
 * \file
 *
 * \brief AUTOSAR Com
 *
 * This file contains the implementation of the AUTOSAR
 * module Com.
 *
 * \author Elektrobit Automotive GmbH, 91058 Erlangen, Germany
 *
 * Copyright 2005 - 2019 Elektrobit Automotive GmbH
 * All rights exclusively reserved for Elektrobit Automotive GmbH,
 * unless expressly agreed to otherwise.
 */


/* MISRA-C:2012 Deviation List
 *
 *
 * MISRAC2012-1) Deviated Rule: 11.5 (advisory)
 * A conversion should not be performed from pointer to
 * void into pointer to object.
 *
 * Reason:
 * The memory routines are optimized for dealing with aligned
 * memory sections.
 *
 */

/*==================[inclusions]=============================================*/

#include <Com_Trace.h>
#include <TSAutosar.h>          /* EB specific standard types */
#include <ComStack_Types.h>     /* AUTOSAR standard types */
#include <Com_Api_Static.h>     /* module public static API */
#include <Com_Priv.h>           /* module internal stuff */
#include <Com_Cbk_Static.h>     /* Callback declarations header */
#include <TSMem.h>              /* TS_MemCpy */

#include <Com_Core_RxIPdu.h>    /* Header TxIPdu functions */

#if (COM_DEV_ERROR_DETECT == STD_ON)
#include <Det.h>                /* Det API */
#endif

#if (COM_RX_TPAPI_ENABLE == STD_ON)
#include <EcuC.h>
#endif /* (COM_RX_TPAPI_ENABLE == STD_ON) */

/*==================[macros]=================================================*/

/*==================[type definitions]=======================================*/

/*==================[external function declarations]=========================*/

/*==================[internal function declarations]=========================*/

#if (TS_MERGED_COMPILE == STD_OFF)
#define COM_START_SEC_CODE
#include <Com_MemMap.h>
#endif

#if ((COM_RX_SIG_CONF_IMMEDIATE_ENABLE == STD_ON) || \
      (COM_RX_SIG_CONF_DEFERRED_ENABLE == STD_ON))
#if (COM_NOTIFY_RECEIVERS_ENABLE == STD_ON)

/** \brief Com_EB_HandleRxConfirm - handles to Rx confirmations of a Pdu
  ** Preconditions:
 ** - COM should be initialized
 ** \param[in] IPduFlagBytePtr - pointer to the flags of the Pdu
 ** \param[in] IPduPtr - pointer to the configuration of the Pdu
 */
_COM_STATIC_ FUNC(void, COM_CODE) Com_EB_HandleRxConfirm
(
#if (COM_RX_SIG_CONF_DEFERRED_ENABLE == STD_ON)
   P2VAR(uint8, AUTOMATIC, COM_VAR_NOINIT) IPduFlagBytePtr,
#endif /* (COM_RX_SIG_CONF_DEFERRED_ENABLE == STD_ON) */
   P2CONST(ComRxIPduType, AUTOMATIC, COM_APPL_CONST) IPduPtr
);
#endif /* (COM_NOTIFY_RECEIVERS_ENABLE == STD_ON) */
#endif /* ((COM_RX_SIG_CONF_IMMEDIATE_ENABLE == STD_ON) || \
      (COM_RX_SIG_CONF_DEFERRED_ENABLE == STD_ON))*/

#if (TS_MERGED_COMPILE == STD_OFF)
#define COM_STOP_SEC_CODE
#include <Com_MemMap.h>
#endif

/*==================[external constants]=====================================*/

/*==================[internal constants]=====================================*/

/*==================[external data]==========================================*/

/*==================[internal data]==========================================*/

/*==================[external function definitions]==========================*/


#if (TS_MERGED_COMPILE == STD_OFF)
#define COM_START_SEC_CODE
#include <Com_MemMap.h>
#endif

/**
 * \brief Com_RxIndication - Signal the COM a PDU has arrived
 *
 * This functions signals the COM that a PDU has arrived
 * Preconditions:
 * - COM should be initialized
 *
 * \param[in] ComRxPduId - ID of the received I-PDU.
 * \param[in] PduInfoPtr - Contains the length (SduLength) of the received I-PDU and a pointer to
 * a buffer (SduDataPtr) containing the I-PDU.
 *
 * \ServiceID{0x42}
 * \Reentrancy{Re-entrant for different values of ComRxPduId only.}
 * \Synchronicity{Synchronous}
 */
FUNC(void, COM_CODE) Com_RxIndication
(
   PduIdType ComRxPduId,
   P2VAR(PduInfoType, AUTOMATIC, COM_APPL_DATA) PduInfoPtr
)
{

  DBG_COM_RXINDICATION_ENTRY(ComRxPduId,PduInfoPtr);

  /* Debug output */
#if (COM_DEV_ERROR_DETECT == STD_ON)
  /* check whether Com is initialized */
  if (Com_InitStatus == COM_EB_UNINIT)
  {
    COM_DET_REPORTERROR(COM_E_UNINIT, COMServiceId_RxIndication);
  }
  /* check SignalDataPtr */
  else if (PduInfoPtr == NULL_PTR)
  {
    COM_DET_REPORTERROR(COM_E_PARAM_POINTER, COMServiceId_RxIndication);
  }
  /* check if PduInfoPtr->SduDataPtr is NULL_PTR */
  else if (PduInfoPtr->SduDataPtr == NULL_PTR)
  {
    COM_DET_REPORTERROR(COM_E_PARAM_POINTER, COMServiceId_RxIndication);
  }
  /* check if ComRxPduId is valid */
  else if (Com_gConfigPtr->ComRxIPduArraySize <= ComRxPduId)
  {
    COM_DET_REPORTERROR(COM_E_PARAM, COMServiceId_RxIndication);
  }
  else

#endif /* (COM_DEV_ERROR_DETECT == STD_ON) */

  {

    /* pointer to the configuration of the IPdu to which the signal belongs */
    P2CONST(ComRxIPduType, AUTOMATIC, COM_APPL_CONST) IPduPtr;
    P2VAR(uint8, AUTOMATIC, COM_VAR_NOINIT) pdudataptr; /* pointer to the data of the PDU */

    /* get IPdu to which ComRxPduId identifies and check if the IPdu is valid */
    IPduPtr = COM_GET_CONFIG_ELEMENT(ComRxIPduType, Com_gConfigPtr->ComRxIPduRef, ComRxPduId);


#if ( (COM_PBCFG_VARIANT_SUPPORT_ENABLED == STD_ON) && (COM_DEV_ERROR_DETECT == STD_ON) )
    if( TRUE == COM_GET_COM_RX_IPDU_DUMMY(IPduPtr) )
    {
      COM_DET_REPORTERROR(COM_E_PARAM, COMServiceId_RxIndication);
    }
    else
#endif /* ( (COM_PBCFG_VARIANT_SUPPORT_ENABLED == STD_ON) && (COM_DEV_ERROR_DETECT == STD_ON) ) */
    {

      /* pointer to byte with status flags of the Pdu */
      CONSTP2VAR(uint8, AUTOMATIC, COM_VAR_NOINIT) IPduFlagBytePtr =
          &Com_gDataMemPtr[(Com_gConfigPtr->ComRxIPduStatusBase + ComRxPduId)];

      /* get data pointer of I-PDU */
      pdudataptr = &Com_gDataMemPtr[(IPduPtr->ComIPduValueRef)];

      /* If the PDU can be received (is started) */
      if ( Com_IsBitSet_8(IPduFlagBytePtr, COM_RXPDU_STARTED) )
      {
        /* If there is a callout, let it decide whether to receive the
         * IPDU or not */

#if (COM_CALL_OUT_FUNC_PTR_ARRAY_SIZE_MAX != COM_INDEX_NONE)
        boolean coretval = TRUE;  /* call-out function return value */

        /* Get the function pointer of the callout function */
        if (IPduPtr->ComIPduCallOutFuncPtrRef != COM_CALL_OUT_FUNC_PTR_NULL)
        {
          CONSTP2VAR(Com_RxCalloutType, AUTOMATIC, COM_APPL_CODE) fptr =
              Com_RxCallouts[(IPduPtr->ComIPduCallOutFuncPtrRef)];
          coretval = fptr(ComRxPduId, PduInfoPtr);
        }

        /* If the callout-function was not called (because there is none),
         * the coretval is TRUE by default */

        /* Stop processing if the callout returned FALSE */
        if (coretval == TRUE)
#endif /* (COM_CALL_OUT_FUNC_PTR_ARRAY_SIZE_MAX != COM_INDEX_NONE) */
        {

          /* get length of I-PDU */
          uint32 pdulength = (uint32) IPduPtr->ComIPduSizeMax;

          if (PduInfoPtr->SduLength < pdulength)
          {
            pdulength = PduInfoPtr->SduLength;
          }

          /* Copy the content of the received PDU to the PDU buffer */
          /* Enter critical section to guarantee a consistent PDU is copied */
          Com_EB_SchM_Enter_SCHM_COM_EXCLUSIVE_AREA_1();

          /* copy the Pdu */
          TS_MemCpy(pdudataptr, PduInfoPtr->SduDataPtr, pdulength);

#if (COM_RX_DYN_LENGTH_IPDU_ENABLE == STD_ON)
          /* set the size of the I-PDU */
          /* Deviation MISRAC2012-1 */
          COM_SET_RX_IPDU_SIZE(ComRxPduId, (ComIPduSizeType) pdulength);
#endif /* (COM_RX_DYN_LENGTH_IPDU_ENABLE == STD_ON) */

          /* Leave critical section */
          Com_EB_SchM_Exit_SCHM_COM_EXCLUSIVE_AREA_1();

#if (COM_SIGNAL_GW_ENABLE == STD_ON)
          /* check if the I-Pdu has a flag for SigGW configured and therefore
           * at least one signal (with or without update bit) which has to be
           * gated */
          if (IPduPtr->ComIPduSigGWFlagBit != COM_IPDU_INVALID)
          {
            /* set the I-Pdu SigGWFlag */
            COM_AtomicSetBit_8(COM_RX_IPDU_SIG_GW_FLAG_ADDRESS(IPduPtr),
                COM_RX_IPDU_SIG_GW_FLAG_BIT(IPduPtr));
          }
#endif /* (COM_SIGNAL_GW_ENABLE == STD_ON) */

#if ((COM_RX_SIG_CONF_IMMEDIATE_ENABLE == STD_ON) || \
    (COM_RX_SIG_CONF_DEFERRED_ENABLE == STD_ON))
#if (COM_NOTIFY_RECEIVERS_ENABLE == STD_ON)

          Com_EB_HandleRxConfirm(
#if (COM_RX_SIG_CONF_DEFERRED_ENABLE == STD_ON)
              IPduFlagBytePtr,
#endif /* (COM_RX_SIG_CONF_DEFERRED_ENABLE == STD_ON) */
              IPduPtr
          );
#endif /* (COM_NOTIFY_RECEIVERS_ENABLE == STD_ON) */
#endif /* ((COM_RX_SIG_CONF_IMMEDIATE_ENABLE == STD_ON) || \
      (COM_RX_SIG_CONF_DEFERRED_ENABLE == STD_ON))*/

        }                         /* coretval == TRUE */
      }                            /* COM_RXPDU_STARTED */

    }

  }

  DBG_COM_RXINDICATION_EXIT(ComRxPduId,PduInfoPtr);
}                               /* Com_RxIndication */


/**
 * \brief Com_TpRxIndication - indicating the correct, or incorrect,
 *                             end of the reception process.
 *
 * This functions signals the COM the correct, or incorrect,
 * end of the reception process.
 * Preconditions:
 * - COM should be initialized
 * - the Pdu must be started before
 * \param[in] PduId - ID of the AUTOSAR COM module's I-PDU that has been received.
 *                    Identifies the data that has been received.
 * \param[in] Result - NTFRSLT_OK: the complete I-PDU has been received and is
 *                                 stored in the receive buffer.
 *                     ANY OTHER VALUE: the I-PDU has not been received;
 *                     the receive buffer can be unlocked by the AUTOSAR COM
 *
 * \ServiceID{0x1E}
 * \Reentrancy{Re-entrant for different values of ComRxPduId only.}
 * \Synchronicity{Synchronous}
 */
FUNC(void, COM_CODE) Com_TpRxIndication
(
    PduIdType PduId,
    NotifResultType Result
)
{

  DBG_COM_TPRXINDICATION_ENTRY(PduId,Result);

#if (COM_RX_TPAPI_ENABLE == STD_ON)

  /* Debug output */
#if (COM_DEV_ERROR_DETECT == STD_ON)
  /* check whether Com is initialized */
  if (Com_InitStatus == COM_EB_UNINIT)
  {
     COM_DET_REPORTERROR(COM_E_UNINIT, COMServiceId_TpRxIndication);
  }
  /* check if ComRxPduId is valid */
  else if (Com_gConfigPtr->ComRxIPduArraySize <= PduId)
  {
     COM_DET_REPORTERROR(COM_E_PARAM, COMServiceId_TpRxIndication);
  }
  else

#endif /* (COM_DEV_ERROR_DETECT == STD_ON) */

  {

    Std_ReturnType RetVal = E_NOT_OK;
    PduLengthType copiedDataSize;
    CONSTP2CONST(ComRxIPduType, AUTOMATIC, COM_APPL_CONST) IPduPtr =
        COM_GET_CONFIG_ELEMENT(ComRxIPduType, Com_gConfigPtr->ComRxIPduRef, PduId);

#if (COM_DEV_ERROR_DETECT == STD_ON)
      if (IPduPtr->ComRxIpduTPControlInfoRef == COM_IPDU_ARRAY_SIZE_MAX)
      {
        /* enters also for dummy pdu, isvalidconfig check ensure array size max value */
        COM_DET_REPORTERROR(COM_E_PARAM, COMServiceId_TpRxIndication);
      }
      else
#endif /* (COM_DEV_ERROR_DETECT == STD_ON) */

      {

        PduInfoType pduinfo;

        /* get TP Control array of struct base */
        CONSTP2VAR(EcuC_RxControlInfoType, AUTOMATIC, COM_VAR_NOINIT) TpRxContPtrBase =
            COM_GET_MEMPTR(EcuC_RxControlInfoType, Com_gConfigPtr->ComRxIpduTPControlInfoBase);

        /* get TP Control struct value pointer */
        CONSTP2VAR(EcuC_RxControlInfoType, AUTOMATIC, COM_VAR_NOINIT) TpRxContPtrValPtr =
            &TpRxContPtrBase[IPduPtr->ComRxIpduTPControlInfoRef];

        /* pointer to byte with status flags of the Pdu */
        CONSTP2VAR(uint8, AUTOMATIC, COM_VAR_NOINIT) IPduFlagBytePtr =
            &Com_gDataMemPtr[(Com_gConfigPtr->ComRxIPduStatusBase + PduId)];

        CONSTP2VAR(uint8, AUTOMATIC, COM_VAR_NOINIT) pduShadowDataPtr =
            (P2VAR(uint8, AUTOMATIC, COM_VAR_NOINIT))
            & Com_gDataMemPtr[((IPduPtr->ComIPduValueRef) + (IPduPtr->ComIPduSizeMax))];

        /* ref to TP Control struct exists for this IPdu &&
         * IPdu is started */
        if( Com_IsBitSet_8(IPduFlagBytePtr, COM_RXPDU_STARTED) )
        {

          RetVal = EcuC_TpRxIndication
              (
                  TpRxContPtrValPtr,
                  Result,
                  &copiedDataSize
              );

          if(RetVal == E_OK)
          {
            pduinfo.SduDataPtr = pduShadowDataPtr;
            pduinfo.SduLength = copiedDataSize;

            Com_RxIndication(PduId, &pduinfo);
          }
          /* else: no notifications () or I-PDU callouts (SWS_Com_00720) */

        }

      }

  }
#else
  TS_PARAM_UNUSED(PduId);
  TS_PARAM_UNUSED(Result);
#endif /* (COM_RX_TPAPI_ENABLE == STD_ON) */

  DBG_COM_TPRXINDICATION_EXIT(PduId,Result);
}

/*==================[internal function definitions]==========================*/

#if ((COM_RX_SIG_CONF_IMMEDIATE_ENABLE == STD_ON) || \
      (COM_RX_SIG_CONF_DEFERRED_ENABLE == STD_ON))
#if (COM_NOTIFY_RECEIVERS_ENABLE == STD_ON)

/** \brief Com_EB_HandleRxConfirm - handles to Rx confirmations of a Pdu
  ** Preconditions:
 ** - COM should be initialized
 ** \param[in] IPduFlagBytePtr - pointer to the flags of the Pdu
 ** \param[in] IPduPtr - pointer to the configuration of the Pdu
 */
_COM_STATIC_ FUNC(void, COM_CODE) Com_EB_HandleRxConfirm
(
#if (COM_RX_SIG_CONF_DEFERRED_ENABLE == STD_ON)
   P2VAR(uint8, AUTOMATIC, COM_VAR_NOINIT) IPduFlagBytePtr,
#endif /* (COM_RX_SIG_CONF_DEFERRED_ENABLE == STD_ON) */
   P2CONST(ComRxIPduType, AUTOMATIC, COM_APPL_CONST) IPduPtr
)
{

#if ((COM_RX_SIG_CONF_IMMEDIATE_ENABLE == STD_ON) && (COM_RX_SIG_CONF_DEFERRED_ENABLE == STD_ON))

         if (COM_GET_COM_RX_IPDU_SIGNAL_PROCESSING(IPduPtr) == COM_DEFERED)
#endif /* ((COM_RX_SIG_CONF_IMMEDIATE_ENABLE == STD_ON) && (COM_RX_SIG_CONF_DEFERRED_ENABLE == STD_ON)) */

#if (COM_RX_SIG_CONF_DEFERRED_ENABLE == STD_ON)
         {
            /* Set Notify Flag */
            COM_AtomicSetBit_8(IPduFlagBytePtr, COM_RXPDU_RXDEFNOTIFY);
         }
#endif /* (COM_RX_SIG_CONF_DEFERRED_ENABLE == STD_ON) */

#if ((COM_RX_SIG_CONF_IMMEDIATE_ENABLE == STD_ON) && (COM_RX_SIG_CONF_DEFERRED_ENABLE == STD_ON))
         else
#endif /* ((COM_RX_SIG_CONF_IMMEDIATE_ENABLE == STD_ON) && (COM_RX_SIG_CONF_DEFERRED_ENABLE == STD_ON)) */

#if (COM_RX_SIG_CONF_IMMEDIATE_ENABLE == STD_ON)
         {
            /* Notify Receivers */
            Com_EB_NotifyReceivers(IPduPtr);
         }
#endif /* (COM_RX_SIG_CONF_IMMEDIATE_ENABLE == STD_ON) */


   return;
}
#endif /* (COM_NOTIFY_RECEIVERS_ENABLE == STD_ON) */
#endif /* ((COM_RX_SIG_CONF_IMMEDIATE_ENABLE == STD_ON) || \
      (COM_RX_SIG_CONF_DEFERRED_ENABLE == STD_ON))*/


#if (TS_MERGED_COMPILE == STD_OFF)
#define COM_STOP_SEC_CODE
#include <Com_MemMap.h>
#endif
/*==================[end of file]============================================*/

