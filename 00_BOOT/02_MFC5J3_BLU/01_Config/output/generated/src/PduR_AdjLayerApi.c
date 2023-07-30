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


/*==================[includes]==============================================*/


#include <TSAutosar.h> /* EB specific standard types */
#include <ComStack_Types.h> /* AUTOSAR Communication Stack types */
#include <PduR_Internal_Static.h> /* Internal API (static part) */
#define PDUR_NO_PBCFG_REQUIRED /* This prevents the inclusion of the symbolic name value header */
#include <PduR_BLUpdater.h> /* Header provided to Generic Upper Layer */
#define PDUR_NO_PBCFG_REQUIRED /* This prevents the inclusion of the symbolic name value header */
#include <PduR_CanIf.h> /* Header provided to Generic Upper Layer */
#include <PduR_Lcfg.h> /* Link-time configurable data */
#include <PduR_Types.h> /* PduR specific types */

/*==================[macros]================================================*/
/*==================[type definitions]======================================*/

typedef P2VAR(PduInfoType, AUTOMATIC, TYPEDEF) PduR_PduInfoPtrType;
typedef P2VAR(RetryInfoType, AUTOMATIC, TYPEDEF) PduR_RetryInfoPtrType;

/*==================[external constants]====================================*/

/*==================[internal constants]====================================*/

/*==================[external data]=========================================*/

/*==================[internal data]=========================================*/


/*==================[external function definitions]=========================*/

/* AUTOSAR Memory Mapping - start section for code */
#define PDUR_START_SEC_CODE
#include <PduR_MemMap.h>

/*****************************************************************************
    IF APIs for generic layer BLUpdater
*****************************************************************************/

FUNC(Std_ReturnType, PDUR_CODE) PduR_BLUpdaterTransmit
(
    PduIdType TxPduId,
    P2CONST(PduInfoType, AUTOMATIC, PDUR_APPL_DATA) PduInfoPtr
)
{
    Std_ReturnType RetVal;

    /* Call generic Transmit function with index PduR_BLUpdaterRTabUpIfTxConfigIdx
     * to select the proper configuration */
    RetVal = PduR_GenericIfTransmit(TxPduId, PduInfoPtr, PduR_BLUpdaterRTabUpIfTxConfigIdx);

    return RetVal;
}

/*****************************************************************************
    IF APIs for generic layer CanIf
*****************************************************************************/

FUNC(void, PDUR_CODE) PduR_CanIfRxIndication
(
    PduIdType    RxPduId,
    P2VAR(PduInfoType, AUTOMATIC, PDUR_APPL_DATA) PduInfoPtr
)
{
    /* Call generic RxIndication function with index PduR_CanIfRTabLoIfConfigIdx for
     * selecting the proper configuration */
    PduR_GenericIfRxIndication(RxPduId, PduInfoPtr, PduR_CanIfRTabLoIfConfigIdx);
}

FUNC(void, PDUR_CODE) PduR_CanIfTxConfirmation
(
    PduIdType    TxPduId
)
{
    /* Call generic TxConfirmation function with index PduR_CanIfRTabLoIfConfigIdx
     * to select the proper configuration */
    PduR_GenericIfTxConfirmation(TxPduId, PduR_CanIfRTabLoIfConfigIdx);
}

/* AUTOSAR Memory Mapping - stop section for code */
#define PDUR_STOP_SEC_CODE
#include <PduR_MemMap.h>

/*==================[internal function definitions]=========================*/

/*==================[end of file]===========================================*/
