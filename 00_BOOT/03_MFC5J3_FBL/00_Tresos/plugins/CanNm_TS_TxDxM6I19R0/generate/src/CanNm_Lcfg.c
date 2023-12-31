/**
 * \file
 *
 * \brief AUTOSAR CanNm
 *
 * This file contains the implementation of the AUTOSAR
 * module CanNm.
 *
 * \author Elektrobit Automotive GmbH, 91058 Erlangen, Germany
 *
 * Copyright 2005 - 2019 Elektrobit Automotive GmbH
 * All rights exclusively reserved for Elektrobit Automotive GmbH,
 * unless expressly agreed to otherwise.
 */

/*==================[inclusions]============================================*/

#include <TSAutosar.h> /* EB specific standard types */
#include <CanNm_Lcfg.h> /* Generated configuration */
#include <CanNm_Lcfg_Static.h>

/*==================[macros]================================================*/

/*==================[type definitions]======================================*/

/*==================[external function declarations]========================*/

/*==================[internal function declarations]========================*/

/*==================[external constants]====================================*/

/* start data section declaration */
#define CANNM_START_SEC_CONST_32
#include <CanNm_MemMap.h>

/* value used to validate post build configuration against link time configuration */
CONST(uint32, CANNM_CONST) CanNm_LcfgSignature = [!"asc:getConfigSignature(as:modconf('CanNm')[1]//*[not(child::*) and (node:configclass() = 'Link')])"!]U;

/* stop data section declaration */
#define CANNM_STOP_SEC_CONST_32
#include <CanNm_MemMap.h>


/*==================[internal constants]====================================*/

/*==================[external data]=========================================*/

/*==================[internal data]=========================================*/

/* start data section declaration */
#define CANNM_START_SEC_VAR_NO_INIT_UNSPECIFIED
#include <CanNm_MemMap.h>

/** \brief Internal memory statically allocated upon link-time. Size depends on
 ** post build configuration. Memory requirements of post build configuration
 ** must be smaller than COM_RAM_SIZE_MAX in order to avoid buffer
 ** overflows. Memory is aligned to the most stringent alignment requirement
 ** of any simple data type available on the respective platform, e.g. uint32.
 */
STATIC TS_DefMaxAlignedByteArray(CANNM_RX_TX_BUFFER_Local, CANNM, VAR_NOINIT, CANNM_DATA_MEM_SIZE);

/* stop data section declaration */
#define CANNM_STOP_SEC_VAR_NO_INIT_UNSPECIFIED
#include <CanNm_MemMap.h>

/*==================[external data]=========================================*/
/* start data section declaration */
#define CANNM_START_SEC_CONST_UNSPECIFIED
#include <CanNm_MemMap.h>

/** \brief Pointer to statically allocated RAM.
 */
CONSTP2VAR(uint8, CANNM_CONST, COM_VAR_NOINIT) CanNm_Rx_Tx_Buffer =
  (P2VAR(uint8, CANNM_CONST, COM_VAR_NOINIT)) CANNM_RX_TX_BUFFER_Local;

/* stop data section declaration */
#define CANNM_STOP_SEC_CONST_UNSPECIFIED
#include <CanNm_MemMap.h>

/*==================[external constants]====================================*/

/*==================[external function definitions]=========================*/

/*==================[internal function definitions]=========================*/

/*==================[end of file]===========================================*/
