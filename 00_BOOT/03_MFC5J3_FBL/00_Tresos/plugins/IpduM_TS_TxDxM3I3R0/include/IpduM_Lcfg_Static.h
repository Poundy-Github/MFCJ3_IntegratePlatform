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
#if (!defined IPDUM_LCFG_STATIC_H)
#define IPDUM_LCFG_STATIC_H

/*==================[inclusions]============================================*/

/*==================[macros]================================================*/

/*==================[type definitions]======================================*/

/*==================[external function declarations]========================*/

/*==================[internal function declarations]========================*/

/*==================[external constants]====================================*/

/*==================[internal constants]====================================*/

/*==================[external data]=========================================*/
/* start data section declaration */
#define IPDUM_START_SEC_CONST_UNSPECIFIED
#include <IpduM_MemMap.h>

/** \brief
 * Exported pointer to post build memory which is statically allocated upon link-time
 *
 * Although the memory itself (i.e., the start address of the memory) is 32 bit aligned, a uint8
 * pointer is used for access to facilitate accesses as byte array with byte offsets as array indices
 */
extern CONSTP2VAR(uint8, IPDUM_CONST, IPDUM_VAR_NOINIT) IpduM_GDataMemPtr;

/* stop data section declaration */
#define IPDUM_STOP_SEC_CONST_UNSPECIFIED
#include <IpduM_MemMap.h>

/* start data section declaration */
#define IPDUM_START_SEC_CONST_32
#include <IpduM_MemMap.h>

/** \brief
 * Constant with size of post-build RAM in units of bytes
 */
extern CONST(uint32, IPDUM_CONST) IpduM_GDataMemSize;

/* stop data section declaration */
#define IPDUM_STOP_SEC_CONST_32
#include <IpduM_MemMap.h>

/*==================[internal data]=========================================*/

/*==================[external function definitions]=========================*/

/*==================[internal function definitions]=========================*/

#endif /* if !defined( IPDUM_LCFG_STATIC_H ) */
/*==================[end of file]===========================================*/
