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
 *  MISRAC2012-1) Deviated Rule: 13.5 (required)
 *  The right hand operand of a logical && or || operator shall not contain persistent side effects.
 *
 *  Reason:
 *  This violation is a false positive.
 *  The right hand operation does not contain persistent side effects. The usage of a macro is not
 *  interpreted correctly by the tool.
 *
 */
/*==================[inclusions]============================================*/

#include <PduR_Trace.h>
#include <TSAutosar.h>            /* EB specific standard types */
#include <ComStack_Types.h>       /* AUTOSAR Communication Stack types */
#include <PduR_Internal_Static.h> /* Internal API (static part) */
#include <PduR_Api_Depend.h>      /* Public API (depend part) */

#if ((PDUR_LOIF_ENABLED == STD_ON) && (PDUR_ZERO_COST_OPERATION_IF == STD_OFF))
#include <PduR_Lcfg.h>            /* Link-time configurable data */
/*==================[macros]================================================*/

/*==================[type definitions]======================================*/

/*==================[external function declarations]========================*/

/*==================[internal function declarations]========================*/

/*==================[external constants]====================================*/

/*==================[internal constants]====================================*/

/*==================[external data]=========================================*/

/*==================[internal data]=========================================*/

/*==================[external function definitions]=========================*/

/* AUTOSAR Memory Mapping - start section for code */
#if (TS_MERGED_COMPILE == STD_OFF)
#define PDUR_START_SEC_CODE
#include <PduR_MemMap.h>
#endif

FUNC(void, PDUR_CODE) PduR_GenericIfRxIndication
(
   PduIdType   RxPduId,
   P2VAR(PduInfoType, AUTOMATIC, PDUR_APPL_DATA) PduInfoPtr,
   uint8 RTabLoIfConfigIdx
)
{
   /* pointer to configuration */
   CONSTP2CONST(PduR_RTabLoIfConfigType, AUTOMATIC, PDUR_APPL_CONST) pRTabLoIfConfig =
      &PduR_GConfigPtr->PduR_RTabLoIfConfig[RTabLoIfConfigIdx];

   DBG_PDUR_GENERICIFRXINDICATION_ENTRY(RxPduId, PduInfoPtr, RTabLoIfConfigIdx);

   /* check if PDU Router is initialized */
   if(PduR_State == PDUR_UNINIT)
   {
      /* according to PDUR330, no routing shall be performed in the uninitialized state */

#if (PDUR_DEV_ERROR_DETECT == STD_ON)
      /* reported to Det in development mode */
      PDUR_DET_REPORT_ERROR(PDUR_SID_LO_RXIND, PDUR_E_INVALID_REQUEST);
   }
   /* range check of PDU ID */
   else if (RxPduId >= pRTabLoIfConfig->RTabRxCount)
   {
       PDUR_DET_REPORT_ERROR(PDUR_SID_LO_RXIND, PDUR_E_PDU_ID_INVALID);
   }
   /* check if input parameter is not NULL */
   else if (PduInfoPtr == NULL_PTR)
   {
       PDUR_DET_REPORT_ERROR(PDUR_SID_LO_RXIND, PDUR_E_NULL_POINTER);
#endif /* #if (PDUR_DEV_ERROR_DETECT == STD_ON) */
   }
   else
   {
      /* pointer to routing table */
      CONSTP2CONST(PduR_RTabLoIfType, AUTOMATIC, PDUR_APPL_CONST) pIfRTabRx =
         PDUR_GET_CONFIG_ADDR(PduR_RTabLoIfType, pRTabLoIfConfig->RTabRxRef);

#if (PDUR_ROUTINGPATHGROUPS_SUPPORT == STD_ON)
      /* get destination PDU routing path group ID from routing table */
      const PduR_RoutingPathGroupIdType GroupId = pIfRTabRx[RxPduId].RPathGroupId;

      /* destination is either enabled or not referenced by a routing path group,
         Note: Order of OR condition on purpose for faster evaluation and preventing call
         of PduR_IsRoutingPathGroupEnabled with PDUR_ROUTINGPATHGROUP_GO_THROUGH_ID */
      /* Deviation MISRAC2012-1 */
      if((GroupId == PDUR_ROUTINGPATHGROUP_GO_THROUGH_ID) ||
         (PduR_IsRoutingPathGroupEnabled(GroupId) != FALSE))
#endif /* (PDUR_ROUTINGPATHGROUPS_SUPPORT == STD_ON) */
      {
        /* reference to set of target If-module API-functions */
        const PduR_RefToModuleAPI TargetAPIRef = pIfRTabRx[RxPduId].TargetModuleAPIRef;

        /* get pointer to RxIndication function from routing table */
        const PduR_IfRxIndFpType RxIndFp = PduR_IfModuleAPI[TargetAPIRef].IfRxIndication;

#if (PDUR_DEV_ERROR_DETECT == STD_ON)
        /* check if target function pointer is equal to null pointer */
        /* CHECK: NOPARSE */
        if(NULL_PTR == RxIndFp)
        {
           /* in the sense of defensive programming, call assertion if
            * target function pointer is equal to null pointer */
           PDUR_UNREACHABLE_CODE_ASSERT(PDUR_SID_LO_RXIND);
        }
        else
        /* CHECK: PARSE */
#endif /* #if (PDUR_DEV_ERROR_DETECT == STD_ON) */
        {
           /* get target PDU ID to RxIndication function from routing table */
           const PduR_PduIdType TargetPduId = pIfRTabRx[RxPduId].TargetPduId;

           /* call RxIndication function */
           RxIndFp(TargetPduId, PduInfoPtr);
        }
      }
   }

   DBG_PDUR_GENERICIFRXINDICATION_EXIT(RxPduId, PduInfoPtr, RTabLoIfConfigIdx);
}

/* AUTOSAR Memory Mapping - end section for code */
#if (TS_MERGED_COMPILE == STD_OFF)
#define PDUR_STOP_SEC_CODE
#include <PduR_MemMap.h>
#endif

#else /* if (PDUR_LOIF_ENABLED == STD_ON) && .. */
#include <TSCompiler.h>           /* usage of macro in TSCompiler_Default.h */
/* Avoid empty translation unit according to ISO C90 */
TS_PREVENTEMPTYTRANSLATIONUNIT


/*==================[internal function definitions]=========================*/

#endif /* if (PDUR_LOIF_ENABLED == STD_ON) && .. */
/*==================[end of file]===========================================*/
