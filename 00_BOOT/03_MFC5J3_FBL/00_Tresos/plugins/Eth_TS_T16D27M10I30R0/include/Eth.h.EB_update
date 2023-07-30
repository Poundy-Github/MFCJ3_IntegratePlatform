/**
 * \file
 *
 * \brief AUTOSAR Eth
 *
 * This file contains the implementation of the AUTOSAR
 * module Eth.
 *
 * \author Elektrobit Automotive GmbH, 91058 Erlangen, Germany
 *
 * Copyright 2005 - 2019 Elektrobit Automotive GmbH
 * All rights exclusively reserved for Elektrobit Automotive GmbH,
 * unless expressly agreed to otherwise.
 */

#ifndef ETH_H
#define ETH_H

#include <Eth_17_GEthMac.h>


/* needed since the module test do not consider VendorId & VendorApiInfix in all published interfaces */

#define Eth_ControllerInit(tmp1,tmp2) E_OK 

#define ETH_AR_RELEASE_MAJOR_VERSION    ETH_17_GETHMAC_AR_RELEASE_MAJOR_VERSION
#define ETH_AR_RELEASE_MINOR_VERSION    ETH_17_GETHMAC_AR_RELEASE_MINOR_VERSION

/* Global Type Definitions */
typedef Eth_17_GEthMac_ConfigType        Eth_ConfigType;

/* Global Function Declarations */
#define Eth_UpdatePhysAddrFilter Eth_17_GEthMac_UpdatePhysAddrFilter
#define Eth_MainFunction        Eth_17_GEthMac_MainFunction
#define Eth_GetVersionInfo      Eth_17_GEthMac_GetVersionInfo
#define Eth_Init                Eth_17_GEthMac_Init
#define Eth_GetControllerMode   Eth_17_GEthMac_GetControllerMode
#define Eth_GetCounterState     Eth_17_GEthMac_GetCounterState
#define Eth_GetPhysAddr         Eth_17_GEthMac_GetPhysAddr
#define Eth_ProvideTxBuffer     Eth_17_GEthMac_ProvideTxBuffer
#define Eth_ReadMii             Eth_17_GEthMac_ReadMii
#define Eth_WriteMii            Eth_17_GEthMac_WriteMii
#define Eth_Receive             Eth_17_GEthMac_Receive
#define Eth_SetControllerMode   Eth_17_GEthMac_SetControllerMode
#define Eth_Transmit            Eth_17_GEthMac_Transmit
#define Eth_TxConfirmation      Eth_17_GEthMac_TxConfirmation

/* Workaround for Eth_17_GEthMac_StateType declaration */
#define Eth_17_GEthMac_StateType     Eth_StateType

extern Eth_17_GEthMac_StateType Eth_17_GEthMac_DriverState ;

#endif /* ETH_H */
