#if (!defined SCHM_CANIF_H)
#define SCHM_CANIF_H

/** \file
 ** \brief AUTOSAR SchM Schedule Manager
 **
 ** This file includes function prototype stubs for SchM_Enter/Exit
 ** and SchM_Act/CancelMainFunction for the module CanIf .
 **
 ** \project AUTOSAR Standard Core
 ** \author Horst Laschinsky
 ** \author Elektrobit Automotive GmbH, 91058 Erlangen, Germany
 **
 ** $Id: SchM_CanIf.h 1306 2012-02-23 09:35:17Z thga2649 $
 ** Release: BLP-3.X_ACG-8_TRICORE_TC38XQ
 **
 ** \controller independent
 ** \compiler independent
 ** \hardware independent
 **
 ** Copyright 2008 by Elektrobit Automotive GmbH
 ** All rights exclusively reserved for Elektrobit Automotive GmbH
 ** unless expressly agreed to otherwise */

/** \addtogroup SchM Schedule Manager
 ** @{ */

/*==================[includes]==============================================*/


/*==================[macros]================================================*/

/*==================[type definitions]======================================*/

/*==================[external function declarations]=========================*/

extern FUNC(void, SCHM_CODE) SchM_Enter_CanIf_SCHM_CANIF_EXCLUSIVE_AREA_0(void);

extern FUNC(void, SCHM_CODE) SchM_Exit_CanIf_SCHM_CANIF_EXCLUSIVE_AREA_0(void);


/*==================[internal function declarations]========================*/

/*==================[external constants]====================================*/

/*==================[internal constants]====================================*/

/*==================[external data]=========================================*/

/*==================[internal data]=========================================*/

/*==================[external function definitions]=========================*/

/*==================[internal function definitions]=========================*/

/** @} doxygen end group definition */
#endif /* if !defined( SCHM_CANIF_H ) */
/*==================[end of file]===========================================*/

