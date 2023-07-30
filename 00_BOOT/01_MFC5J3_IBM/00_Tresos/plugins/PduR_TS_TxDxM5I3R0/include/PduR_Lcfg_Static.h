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
#if (!defined PDUR_LCFG_STATIC_H)
#define PDUR_LCFG_STATIC_H

/*==================[inclusions]============================================*/

#include <TSAutosar.h>              /* EB specific standard types */

/*==================[macros]================================================*/

/*==================[type definitions]======================================*/

/*==================[external function declarations]========================*/

/*==================[internal function declarations]========================*/

/*==================[external constants]====================================*/

/*==================[internal constants]====================================*/

/*==================[internal data]=========================================*/

/* start data section declaration */
#define PDUR_START_SEC_CONST_UNSPECIFIED
#include <PduR_MemMap.h>

/**
 * \brief Pointer to internal memory.
 */
extern CONSTP2VAR(uint8, PDUR_CONST, PDUR_VAR_NOINIT) PduR_GMemPtr;

/* stop data section declaration */
#define PDUR_STOP_SEC_CONST_UNSPECIFIED
#include <PduR_MemMap.h>

/*==================[external function definitions]=========================*/

/*==================[internal function definitions]=========================*/

#endif /* if !defined( PDUR_LCFG_STATIC_H ) */
/*==================[end of file]===========================================*/
