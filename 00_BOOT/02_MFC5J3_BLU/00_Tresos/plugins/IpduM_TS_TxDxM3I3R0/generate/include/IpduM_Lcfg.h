/**
 * \file
 *
 * \brief AUTOSAR IpduM
 *
 * This file contains the implementation of the AUTOSAR
 * module IpduM.
 *
 * \author Elektrobit Automotive GmbH, 91058 Erlangen, Germany
 *
 * Copyright 2005 - 2019 Elektrobit Automotive GmbH
 * All rights exclusively reserved for Elektrobit Automotive GmbH,
 * unless expressly agreed to otherwise.
 */
#if (!defined IPDUM_LCFG_H)
#define IPDUM_LCFG_H

[!AUTOSPACING!]
/*==================[includes]==============================================*/

#include <TSAutosar.h>              /* global configuration */
#include <IpduM_Types.h>            /* Module types */

[!INCLUDE "IpduM_Macros.m"!]
/*==================[macros]================================================*/
[!SELECT "IpduMConfig/*[1]"!]

/**
 * Size of internal IpduM data in units of bytes (static memory
 * allocation) - Memory required by post-build configuration must be smaller
 * than this constant
 */[!//
[!IF "node:exists(../../IpduMGeneral/IpduMDataMemSize)"!]
#if (defined IPDUM_DATA_MEM_SIZE)
#error IPDUM_DATA_MEM_SIZE already defined!
#endif /* #if (defined IPDUM_DATA_MEM_SIZE)*/
#define IPDUM_DATA_MEM_SIZE [!"../../IpduMGeneral/IpduMDataMemSize"!]U
 [!ELSE!]
#if (defined IPDUM_DATA_MEM_SIZE)
#error IPDUM_DATA_MEM_SIZE already defined!
#endif /* #if (defined IPDUM_DATA_MEM_SIZE)*/
#define IPDUM_DATA_MEM_SIZE \
    [!IF "node:exists(IpduMTxPathway/*) or node:exists(IpduMContainerRxPdu/*[IpduMContainerPduProcessing='IPDUM_PROCESSING_DEFERRED']) or node:exists(IpduMContainerTxPdu/*)"!][!//
    [!CALL "GetDataMemSlices"!]
    ([!"$IpduMDataMemPathwaySize"!] + [!"$IpduMDataMemRxContainerSize"!] + [!"$IpduMDataMemTxContainerSize"!])
    [!ELSE!]
    1U
    [!ENDIF!]
[!ENDIF!]

[!ENDSELECT!]

/*==================[type definitions]======================================*/

/*==================[external function declarations]========================*/

/*==================[internal function declarations]========================*/

/*==================[external constants]====================================*/

/* start data section declaration */
#define IPDUM_START_SEC_CONST_32
#include <IpduM_MemMap.h>

/* value used to validate post build configuration against link time configuration */
extern CONST(uint32, IPDUM_CONST) IpduM_LcfgSignature;

/* stop data section declaration */
#define IPDUM_STOP_SEC_CONST_32
#include <IpduM_MemMap.h>

/*==================[internal constants]====================================*/

/*==================[external data]=========================================*/

/*==================[internal data]=========================================*/

/*==================[external function definitions]=========================*/

/*==================[internal function definitions]=========================*/

#endif /* if !defined( IPDUM_LCFG_H ) */
/*==================[end of file]===========================================*/
