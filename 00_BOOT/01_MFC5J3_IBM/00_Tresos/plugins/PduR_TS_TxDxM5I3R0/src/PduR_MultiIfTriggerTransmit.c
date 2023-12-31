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

/*==================[inclusions]============================================*/

#include <PduR_Trace.h>
#include <TSAutosar.h>            /* EB specific standard types */
#include <ComStack_Types.h>       /* AUTOSAR Communication Stack types */
#include <PduR_Internal_Static.h> /* Internal API (static part) */
#include <PduR_Api_Depend.h>      /* Public API (depend part) */

#if((PDUR_ZERO_COST_OPERATION_IF == STD_OFF) && \
    (PDUR_MULTICAST_TOIF_SUPPORT == STD_ON) && \
    (PDUR_LOIF_TRIGGERTX_ENABLED == STD_ON))

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

FUNC(Std_ReturnType, PDUR_CODE) PduR_MultiIfTriggerTransmit
(
   PduIdType    MPduId,
   P2VAR(PduInfoType, AUTOMATIC, PDUR_APPL_DATA) PduInfoPtr
)
{
   Std_ReturnType RetVal;

   DBG_PDUR_MULTIIFTRIGGERTRANSMIT_ENTRY(MPduId, PduInfoPtr);

   {
      /* pointer to routing table */
      CONSTP2CONST(PduR_MTabUpIfTxType, AUTOMATIC, PDUR_APPL_CONST) pMTabUpIfTx =
         PDUR_GET_CONFIG_ADDR(PduR_MTabUpIfTxType, PduR_GConfigPtr->PduR_MTabUpIfConfig.MTabTxRef);

      /* reference to set of upper layer API-functions */
      const PduR_RefToModuleAPI SourceAPIRef = pMTabUpIfTx[MPduId].SourceModuleAPIRef;

      /* get upper layer PDU-ID */
      const PduR_PduIdType UprLyrTxPduId = pMTabUpIfTx[MPduId].UprLyrTxPduId;

      /* pointer to TriggerTransmit function */
      const PduR_IfTrTxFpType TriggerTransmitFp = PduR_IfModuleAPI[SourceAPIRef].IfTriggerTransmit;

      /* call TriggerTransmit function */
      RetVal = TriggerTransmitFp(UprLyrTxPduId, PduInfoPtr);
   }

   DBG_PDUR_MULTIIFTRIGGERTRANSMIT_EXIT(RetVal, MPduId, PduInfoPtr);

   return RetVal;
}

/* AUTOSAR Memory Mapping - end section for code */
#if (TS_MERGED_COMPILE == STD_OFF)
#define PDUR_STOP_SEC_CODE
#include <PduR_MemMap.h>
#endif

#else /* if (PDUR_ZERO_COST_OPERATION_IF == STD_OFF) && .. */

#include <TSCompiler.h>           /* usage of macro in TSCompiler_Default.h */

/* Avoid empty translation unit according to ISO C90 */
TS_PREVENTEMPTYTRANSLATIONUNIT


/*==================[internal function definitions]=========================*/

#endif /* if (PDUR_ZERO_COST_OPERATION_IF == STD_OFF) && .. */
/*==================[end of file]===========================================*/
