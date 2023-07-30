
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

#ifndef PDUR_PBCFG_H
#define PDUR_PBCFG_H



/*==================[inclusions]=============================================*/

#include <PduR_SymbolicNames_PBcfg.h>
#include <TSAutosar.h>
#include <PduR_CfgTypes.h>
#include <Compiler.h>
#define TS_RELOCATABLE_CFG_ENABLE STD_OFF
#define TS_PB_CFG_PTR_CLASS PDUR_APPL_CONST
#include <TSPBConfig_Types.h>


/*==================[macros]=================================================*/

#if (defined PduRRoutingTables) /* To prevent double definition */
#error PduRRoutingTables already defined
#endif /* (defined PduRRoutingTables) */

#define PduRRoutingTables (PduR_ConfigLayout.PduR_RootConfig)



/*==================[type definitions]=======================================*/

typedef struct /* PduR_ConfigLayoutType */ {
    CONST( PduR_PBConfigType, TYPEDEF ) PduR_RootConfig;
    VAR( PduR_RTabLoIfType, TYPEDEF ) PduR_RTabLoIfRx[2];
    VAR( PduR_RTabLoIfType, TYPEDEF ) PduR_RTabLoIfTx[1];
    VAR( PduR_RTabUpIfTxType, TYPEDEF ) PduR_RTabUpIfTx[1];
} PduR_ConfigLayoutType;

typedef CONST( PduR_ConfigLayoutType, TYPEDEF ) PduR_ConstConfigLayoutType;


/*==================[external function declarations]=========================*/


/*==================[internal function declarations]=========================*/


/*==================[external constants]=====================================*/

#define PDUR_START_SEC_CONFIG_DATA_UNSPECIFIED
#include <PduR_MemMap.h>

extern PduR_ConstConfigLayoutType PduR_ConfigLayout;

#define PDUR_STOP_SEC_CONFIG_DATA_UNSPECIFIED
#include <PduR_MemMap.h>


/*==================[internal constants]=====================================*/


/*==================[external data]==========================================*/


/*==================[internal data]==========================================*/


/*==================[external function definitions]==========================*/


/*==================[internal function definitions]==========================*/



#undef TS_RELOCATABLE_CFG_ENABLE

#undef TS_PB_CFG_PTR_CLASS

#endif /* PDUR_PBCFG_H */

/*==================[end of file]============================================*/

