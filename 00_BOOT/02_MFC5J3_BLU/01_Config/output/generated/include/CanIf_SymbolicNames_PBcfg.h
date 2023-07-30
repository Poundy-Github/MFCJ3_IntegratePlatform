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


  #if (!defined CANIF_SYMBOLICNAMES_PBCFG_H)
#define CANIF_SYMBOLICNAMES_PBCFG_H

/*==================[includes]===============================================*/
/*==================[macros]=================================================*/

/*------------------[symbolic name values]----------------------------------*/

/** \brief Export symbolic name values for CanIfTxPduIds */


#if (defined CanIfConf_CanIfTxPduCfg_Pdu_Tx_Uds)
#error CanIfConf_CanIfTxPduCfg_Pdu_Tx_Uds already defined!
#endif /* #if( defined CanIfConf_CanIfTxPduCfg_Pdu_Tx_Uds)*/
#define CanIfConf_CanIfTxPduCfg_Pdu_Tx_Uds 0U

#if (defined CANIF_PROVIDE_LEGACY_SYMBOLIC_NAMES)
/** \brief Export symbolic name value with module abbreviation as prefix only (AUTOSAR 4.0 rev2 <=
AUTOSAR version) */
#if (defined CanIf_Pdu_Tx_Uds)
#error CanIf_Pdu_Tx_Uds already defined!
#endif /* #if( defined CanIf_Pdu_Tx_Uds)*/
#define CanIf_Pdu_Tx_Uds 0U
#endif /* defined CANIF_PROVIDE_LEGACY_SYMBOLIC_NAMES */


/** \brief Export symbolic name values for CanIfRxPduIds */


#if (defined CanIfConf_CanIfRxPduCfg_Pdu_Rx_UdsPhys)
#error CanIfConf_CanIfRxPduCfg_Pdu_Rx_UdsPhys already defined!
#endif /* #if( defined CanIfConf_CanIfRxPduCfg_Pdu_Rx_UdsPhys)*/
#define CanIfConf_CanIfRxPduCfg_Pdu_Rx_UdsPhys 0U

#if (defined CANIF_PROVIDE_LEGACY_SYMBOLIC_NAMES)
/** \brief Export symbolic name value with module abbreviation as prefix only (AUTOSAR 4.0 rev2 <=
AUTOSAR version) */
#if (defined CanIf_Pdu_Rx_UdsPhys)
#error CanIf_Pdu_Rx_UdsPhys already defined!
#endif /* #if( defined CanIf_Pdu_Rx_UdsPhys)*/
#define CanIf_Pdu_Rx_UdsPhys 0U
#endif /* defined CANIF_PROVIDE_LEGACY_SYMBOLIC_NAMES */

#if (defined CanIfConf_CanIfRxPduCfg_Pdu_Rx_UdsFunc)
#error CanIfConf_CanIfRxPduCfg_Pdu_Rx_UdsFunc already defined!
#endif /* #if( defined CanIfConf_CanIfRxPduCfg_Pdu_Rx_UdsFunc)*/
#define CanIfConf_CanIfRxPduCfg_Pdu_Rx_UdsFunc 1U

#if (defined CANIF_PROVIDE_LEGACY_SYMBOLIC_NAMES)
/** \brief Export symbolic name value with module abbreviation as prefix only (AUTOSAR 4.0 rev2 <=
AUTOSAR version) */
#if (defined CanIf_Pdu_Rx_UdsFunc)
#error CanIf_Pdu_Rx_UdsFunc already defined!
#endif /* #if( defined CanIf_Pdu_Rx_UdsFunc)*/
#define CanIf_Pdu_Rx_UdsFunc 1U
#endif /* defined CANIF_PROVIDE_LEGACY_SYMBOLIC_NAMES */


/** \brief Export symbolic name values for CanIfCtrlIds */


#if (defined CanIfConf_CanIfCtrlDrvCfg_CAN0)
#error CanIfConf_CanIfCtrlDrvCfg_CAN0 already defined!
#endif /* #if( defined CanIfConf_CanIfCtrlDrvCfg_CAN0)*/
#define CanIfConf_CanIfCtrlDrvCfg_CAN0 0U

#if (defined CANIF_PROVIDE_LEGACY_SYMBOLIC_NAMES)
/** \brief Export symbolic name value with module abbreviation as prefix only (AUTOSAR 4.0 rev2 <=
AUTOSAR version) */
#if (defined CanIf_CanIfCtrlDrvCfg_CAN0)
#error CanIf_CanIfCtrlDrvCfg_CAN0 already defined!
#endif /* #if( defined CanIf_CanIfCtrlDrvCfg_CAN0)*/
#define CanIf_CanIfCtrlDrvCfg_CAN0 0U
#endif /* defined CANIF_PROVIDE_LEGACY_SYMBOLIC_NAMES */


/** \brief Export symbolic name values for CanIfTrcvIds */

/*==================[type definitions]=======================================*/

/*==================[external function declarations]=========================*/

/*==================[internal function declarations]=========================*/

/*==================[external constants]=====================================*/

/*==================[internal constants]=====================================*/

/*==================[external data]==========================================*/

/*==================[internal data]==========================================*/

/*==================[external function definitions]==========================*/

/*==================[internal function definitions]==========================*/

#endif /* if !defined( CANIF_SYMBOLICNAMES_PBCFG_H ) */
/*==================[end of file]============================================*/
