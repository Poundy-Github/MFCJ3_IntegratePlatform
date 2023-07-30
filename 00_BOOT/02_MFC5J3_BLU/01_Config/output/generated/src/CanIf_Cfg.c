/**
 * \file
 *
 * \brief AUTOSAR CanIf
 *
 * This file contains the implementation of the AUTOSAR
 * module CanIf.
 *
 * \author Elektrobit Automotive GmbH, 91058 Erlangen, Germany
 *
 * Copyright 2005 - 2019 Elektrobit Automotive GmbH
 * All rights exclusively reserved for Elektrobit Automotive GmbH,
 * unless expressly agreed to otherwise.
 */

/*
 *  MISRA-C:2012 Deviations:
 *
 *  MISRAC2012-1) Deviated Rule: 9.5 (Required)
 *    Where designated initializers are used to initialize an array object the
 *    size of the array shall be specified explicitly.
 *
 *    Reason:
 *    Array size and initialization are depending on configuration whereas the
 *    array declaration is used by configuration-independent library code.
 */

/*==================[inclusions]=============================================*/

#define CANIF_NO_CFGCLASSMIX_REQUIRED
#define CANIF_NO_PBCFG_REQUIRED
#include <CanIf.h>                /* CanIf Types */
#include <CanIf_Int.h>





/* do not indirectly include PduR_SymbolicNames_PBcfg.h via PduR_CanIf.h */
#define PDUR_NO_PBCFG_REQUIRED

#include <PduR_CanIf.h>            /* PduR callback function declarations */


/*==================[macros]=================================================*/

/*==================[type definitions]=======================================*/

/*==================[external function declarations]=========================*/

/*==================[internal function declarations]=========================*/

/*==================[internal constants]=====================================*/

/*==================[external constants]=====================================*/

#define CANIF_START_SEC_CONFIG_DATA_UNSPECIFIED
#include <CanIf_MemMap.h>



/** \brief Configuration of upper layer callback function pointers */
/* Deviation MISRAC2012-1 <START> */
CONST( CanIf_CbkFctPtrTblType, CANIF_APPL_CONST ) CanIf_CbkFctPtrTbl[] =
{
  {
     /* PDUR */
    &PduR_CanIfRxIndication,
    &PduR_CanIfTxConfirmation,
  },
};
/* Deviation MISRAC2012-1 <STOP> */





#define CANIF_STOP_SEC_CONFIG_DATA_UNSPECIFIED
#include <CanIf_MemMap.h>

/*==================[external data]==========================================*/


#define CANIF_START_SEC_VAR_NO_INIT_8
#include <CanIf_MemMap.h>

#if( ( CANIF_WAKEUP_VALIDATION_API == STD_ON ) || \
     ( CANIF_PUBLIC_TXCONFIRM_POLLING_SUPPORT == STD_ON )  || \
     ( CANIF_PUBLIC_PN_SUPPORT == STD_ON) || \
     ( CANIF_BUS_MIRRORING_SUPPORT == STD_ON ) )

/** \brief Controller flags
 **
 ** This array contains the wakeup flags of all configured
 ** controllers. If a bit/flag has the value 1 it is set.
 ** Bit masks are:
 ** CANIF_WAKEUP_MASK             Wakeup flag
 ** CANIF_WAKEUP_VALIDATION_MASK  Wakeup validation flag
 ** CANIF_TX_CONFIRMATION_MASK    Tx confirmation flag
 ** CANIF_PN_FILTER_ACTIVE_MASK   Partial networking filter flag
 ** CANIF_BUS_MIRRORING_MASK      Mirroring flag
 */
VAR( uint8, CANIF_VAR )
  CanIf_CanControllerFlags[4U];

#endif /* ( CANIF_WAKEUP_VALIDATION_API == STD_ON ) || \
          ( CANIF_PUBLIC_TXCONFIRM_POLLING_SUPPORT == STD_ON )  || \
          ( CANIF_PUBLIC_PN_SUPPORT == STD_ON) || \
          ( CANIF_BUS_MIRRORING_SUPPORT == STD_ON ) ) */







#define CANIF_STOP_SEC_VAR_NO_INIT_8
#include <CanIf_MemMap.h>

#define CANIF_START_SEC_VAR_NO_INIT_16
#include <CanIf_MemMap.h>





#define CANIF_STOP_SEC_VAR_NO_INIT_16
#include <CanIf_MemMap.h>

#define CANIF_START_SEC_VAR_NO_INIT_UNSPECIFIED
#include <CanIf_MemMap.h>

VAR( CanIf_ControllerModeType, CANIF_VAR )
  CanIf_CanControllerMode[4U];

VAR( CanIf_PduModeType, CANIF_VAR )
  CanIf_PduMode[4U];

/** \brief Array for dynamic CAN IDs
 **
 ** This array contains the current set CAN ID for dynamic Tx L-PDUs.
 */
 VAR( Can_IdType, CANIF_VAR )
  CanIf_DynamicTxLPduCanIds[1U];




  
#define CANIF_STOP_SEC_VAR_NO_INIT_UNSPECIFIED
#include <CanIf_MemMap.h>


/*==================[internal data]==========================================*/

/*==================[external function definitions]==========================*/

/*==================[internal function definitions]==========================*/

/*==================[end of file]============================================*/
