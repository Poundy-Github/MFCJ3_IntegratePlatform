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
#if (!defined PDUR_SYMBOLIC_NAMES_PBCFG_H)
#define PDUR_SYMBOLIC_NAMES_PBCFG_H

/*==================[includes]==============================================*/

/*==================[macros]================================================*/
/* -------------------- Routing path: 0 Pdu_Rx_UdsPhys */
#if (defined PduRConf_PduRSrcPdu_Sdu_Rx_Phys_Group_0)
#error PduRConf_PduRSrcPdu_Sdu_Rx_Phys_Group_0 is already defined
#endif
/** \brief Export symbolic name value */
#define PduRConf_PduRSrcPdu_Sdu_Rx_Phys_Group_0 0U /* SRC CanIf-LO-IF */

#if (defined PDUR_PROVIDE_LEGACY_SYMBOLIC_NAMES)
#if (defined PduR_Sdu_Rx_Phys_Group_0)
#error PduR_Sdu_Rx_Phys_Group_0 is already defined
#endif
/** \brief Export symbolic name value with module abbreviation as prefix only (AUTOSAR 4.0 rev2 <= AUTOSAR version) */
#define PduR_Sdu_Rx_Phys_Group_0 0U
#endif /* defined PDUR_PROVIDE_LEGACY_SYMBOLIC_NAMES */

#if (defined PduRConf_PduRDestPdu_Sdu_Rx_Phys_Group_0_d)
#error PduRConf_PduRDestPdu_Sdu_Rx_Phys_Group_0_d is already defined
#endif
/** \brief Export symbolic name value */
#define PduRConf_PduRDestPdu_Sdu_Rx_Phys_Group_0_d 0U /* DEST BLUpdater-UP-IF */


/* -------------------- Routing path: 1 Pdu_Rx_UdsFunc */
#if (defined PduRConf_PduRSrcPdu_Sdu_Rx_Func_Group_0)
#error PduRConf_PduRSrcPdu_Sdu_Rx_Func_Group_0 is already defined
#endif
/** \brief Export symbolic name value */
#define PduRConf_PduRSrcPdu_Sdu_Rx_Func_Group_0 1U /* SRC CanIf-LO-IF */

#if (defined PDUR_PROVIDE_LEGACY_SYMBOLIC_NAMES)
#if (defined PduR_Sdu_Rx_Func_Group_0)
#error PduR_Sdu_Rx_Func_Group_0 is already defined
#endif
/** \brief Export symbolic name value with module abbreviation as prefix only (AUTOSAR 4.0 rev2 <= AUTOSAR version) */
#define PduR_Sdu_Rx_Func_Group_0 1U
#endif /* defined PDUR_PROVIDE_LEGACY_SYMBOLIC_NAMES */

#if (defined PduRConf_PduRDestPdu_Sdu_Rx_Func_Group_0_d)
#error PduRConf_PduRDestPdu_Sdu_Rx_Func_Group_0_d is already defined
#endif
/** \brief Export symbolic name value */
#define PduRConf_PduRDestPdu_Sdu_Rx_Func_Group_0_d 1U /* DEST BLUpdater-UP-IF */


/* -------------------- Routing path: 2 Pdu_Tx_Uds */
#if (defined PduRConf_PduRSrcPdu_Sdu_Tx_Group_0)
#error PduRConf_PduRSrcPdu_Sdu_Tx_Group_0 is already defined
#endif
/** \brief Export symbolic name value */
#define PduRConf_PduRSrcPdu_Sdu_Tx_Group_0 0U /* SRC BLUpdater-UP-IF */

#if (defined PDUR_PROVIDE_LEGACY_SYMBOLIC_NAMES)
#if (defined PduR_Sdu_Tx_Group_0)
#error PduR_Sdu_Tx_Group_0 is already defined
#endif
/** \brief Export symbolic name value with module abbreviation as prefix only (AUTOSAR 4.0 rev2 <= AUTOSAR version) */
#define PduR_Sdu_Tx_Group_0 0U
#endif /* defined PDUR_PROVIDE_LEGACY_SYMBOLIC_NAMES */

#if (defined PduRConf_PduRDestPdu_Sdu_Tx_Group_0_d)
#error PduRConf_PduRDestPdu_Sdu_Tx_Group_0_d is already defined
#endif
/** \brief Export symbolic name value */
#define PduRConf_PduRDestPdu_Sdu_Tx_Group_0_d 0U /* DEST CanIf-LO-IF */



/* Define vendor specific destination PDU IDs of adjacent modules */
#if (defined PDUR_PROVIDE_ADJACENT_MODULE_VENDOR_SYMBOLIC_NAMES)

/* -------------------- Routing path: 0 Pdu_Rx_UdsPhys */
/* PDURSA_Pdu_Rx_UdsPhys   SRC CanIf-LO-IF  Not defined since the configuration does not supply this ID */
#define PDURDA_Pdu_Rx_UdsPhys 0U /* DEST BLUpdater-UP-IF */

/* -------------------- Routing path: 1 Pdu_Rx_UdsFunc */
/* PDURSA_Pdu_Rx_UdsFunc   SRC CanIf-LO-IF  Not defined since the configuration does not supply this ID */
#define PDURDA_Pdu_Rx_UdsFunc 1U /* DEST BLUpdater-UP-IF */

/* -------------------- Routing path: 2 Pdu_Tx_Uds */
#define PDURSA_Pdu_Tx_Uds 0U /* SRC BLUpdater-UP-IF */
#define PDURDA_Pdu_Tx_Uds 0U /* DEST CanIf-LO-IF DIRECT */

#endif /* defined PDUR_PROVIDE_ADJACENT_MODULE_VENDOR_SYMBOLIC_NAMES */

/*==================[type definitions]======================================*/

/*==================[external function declarations]========================*/

/*==================[internal function declarations]========================*/

/*==================[external constants]====================================*/

/*==================[internal constants]====================================*/

/*==================[external data]=========================================*/

/*==================[internal data]=========================================*/

/*==================[external function definitions]=========================*/

/*==================[internal function definitions]=========================*/

#endif /* if !defined( PDUR_SYMBOLIC_NAMES_PBCFG_H ) */
/*==================[end of file]===========================================*/
