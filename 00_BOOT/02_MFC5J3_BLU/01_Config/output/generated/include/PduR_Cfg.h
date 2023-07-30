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
#if (!defined PDUR_CFG_H)
#define PDUR_CFG_H

/*==================[includes]==============================================*/

#include <TSAutosar.h>              /* EB specific standard types */

/*==================[macros]================================================*/


#if (defined PDUR_MEM_SIZE_MAX) /* to prevent double declaration */
#error PDUR_MEM_SIZE_MAX already defined
#endif /* if (defined PDUR_MEM_SIZE_MAX) */

/** \brief This macro specifies the maximum RAM size of the PduR module. */
#define PDUR_MEM_SIZE_MAX 0xFFFFU


#if (defined PDUR_ISVALIDCONFIG_MMAP_ENABLED) /* to prevent double declaration */
#error PDUR_ISVALIDCONFIG_MMAP_ENABLED already defined
#endif /* if (defined PDUR_ISVALIDCONFIG_MMAP_ENABLED) */

/** \brief This macro specifies if memmap for PduR_IsValidFunction is provided to special mem 
  *        sections. */
#define PDUR_ISVALIDCONFIG_MMAP_ENABLED STD_OFF


#if (defined PDUR_MAKENULLREF2VAR) /* to prevent double declaration */
#error PDUR_MAKENULLREF2VAR already defined
#endif /* if (defined PDUR_MAKENULLREF2VAR) */

/** \brief This macro specifies an invalid variable value referenced. */
#define PDUR_MAKENULLREF2VAR 65535U


#if (defined PDUR_DEV_ERROR_DETECT) /* to prevent double declaration */
#error PDUR_DEV_ERROR_DETECT already defined
#endif /* if (defined PDUR_DEV_ERROR_DETECT) */

/** \brief This macro specifies if development error detection is provided. */
#define PDUR_DEV_ERROR_DETECT STD_ON


#if (defined PDUR_INVALID_PDUID) /* to prevent double declaration */
#error PDUR_INVALID_PDUID already defined
#endif /* if (defined PDUR_INVALID_PDUID) */

/** \brief This macro specifies an invalid value of a PDU-ID. */
#define PDUR_INVALID_PDUID 65535U
  
#if (defined PDUR_INVALID_APIREF) /* to prevent double declaration */
#error PDUR_INVALID_APIREF already defined
#endif /* if (defined PDUR_INVALID_APIREF) */

/** \brief This macro specifies an invalid value of an API set referenced. */
#define PDUR_INVALID_APIREF 65535U


#if (defined PDUR_ZERO_COST_OPERATION) /* to prevent double declaration */
#error PDUR_ZERO_COST_OPERATION already defined
#endif /* if (defined PDUR_ZERO_COST_OPERATION) */

/** \brief This macro specifies if zero cost operation is enabled by PduRZeroCostOperation. */
#define PDUR_ZERO_COST_OPERATION STD_OFF


#if (defined PDUR_ZERO_COST_OPERATION_IF) /* to prevent double declaration */
#error PDUR_ZERO_COST_OPERATION_IF already defined
#endif /* if (defined PDUR_ZERO_COST_OPERATION_IF) */

/** \brief This macro specifies if zero cost operation is provided to communication interface 
  *        modules. Otherwise it is set to STD_OFF. */
#define PDUR_ZERO_COST_OPERATION_IF STD_OFF


#if (defined PDUR_ZERO_COST_OPERATION_TP) /* to prevent double declaration */
#error PDUR_ZERO_COST_OPERATION_TP already defined
#endif /* if (defined PDUR_ZERO_COST_OPERATION_TP) */

/** \brief This macro specifies if zero cost operation is provided to transport protocol modules. 
  *        Otherwise it is set to STD_OFF. */
#define PDUR_ZERO_COST_OPERATION_TP STD_OFF


#if (defined PDUR_ZERO_COST_OPERATION_FULL) /* to prevent double declaration */
#error PDUR_ZERO_COST_OPERATION_FULL already defined
#endif /* if (defined PDUR_ZERO_COST_OPERATION_FULL) */

/** \brief This macro specifies if zero cost operation is provided to communication interface and 
  *        transport protocol modules. Otherwise it is set to STD_OFF. */
#define PDUR_ZERO_COST_OPERATION_FULL STD_OFF


#if (defined PDUR_VERSION_INFO_API) /* to prevent double declaration */
#error PDUR_VERSION_INFO_API already defined
#endif /* if (defined PDUR_VERSION_INFO_API) */

/** \brief This macro specifies if the PduR_GetVersionInfo API is enabled by PduRVersionInfoApi. 
  *        */
#define PDUR_VERSION_INFO_API STD_OFF


#if (defined PDUR_PBCFGM_SUPPORT_ENABLED) /* to prevent double declaration */
#error PDUR_PBCFGM_SUPPORT_ENABLED already defined
#endif /* if (defined PDUR_PBCFGM_SUPPORT_ENABLED) */

/** \brief This macro specifies if the PduR is referenced by the PbcfgM module. */
#define PDUR_PBCFGM_SUPPORT_ENABLED STD_OFF


#if (defined PDUR_AUTOSAR32_SUPPORT) /* to prevent double declaration */
#error PDUR_AUTOSAR32_SUPPORT already defined
#endif /* if (defined PDUR_AUTOSAR32_SUPPORT) */

/** \brief This macro specifies if the wrapping to an AUTOSAR 3.2 upper layer module with TP 
  *        interface is supported. */
#define PDUR_AUTOSAR32_SUPPORT STD_OFF


#if (defined PDUR_AUTOSAR32_REVISION_COMPATIBILITY) /* to prevent double declaration */
#error PDUR_AUTOSAR32_REVISION_COMPATIBILITY already defined
#endif /* if (defined PDUR_AUTOSAR32_REVISION_COMPATIBILITY) */

/** \brief This macro enables/disables the passing of return values of AUTOSAR 3.2 upper layer 
  *        modules for dedicated AUTOSAR 3.2 revisions on Rx side. */
#define PDUR_AUTOSAR32_REVISION_COMPATIBILITY STD_OFF


#if (defined PDUR_CONST_CFG_ADDRESS_ENABLE) /* to prevent double declaration */
#error PDUR_CONST_CFG_ADDRESS_ENABLE already defined
#endif /* if (defined PDUR_CONST_CFG_ADDRESS_ENABLE) */

/** \brief This macro specifies if the constant configuration address optimization is enabled by 
  *        PduRConstCfgAddressEnable. */
#define PDUR_CONST_CFG_ADDRESS_ENABLE STD_OFF



#if (defined PDUR_RELOCATABLE_CFG_ENABLE) /* to prevent double declaration */
#error PDUR_RELOCATABLE_CFG_ENABLE already defined
#endif /* if (defined PDUR_RELOCATABLE_CFG_ENABLE) */

/** \brief This macro specifies if the relocatable configuration support is enabled by 
  *        PduRRelocatableCfgEnable. */
#define PDUR_RELOCATABLE_CFG_ENABLE STD_OFF


#if (defined PDUR_CFG_SIGNATURE) /* to prevent double declaration */
#error PDUR_CFG_SIGNATURE already defined
#endif /* if (defined PDUR_CFG_SIGNATURE) */

/** \brief This macro specifies the compile time signature. */
#define PDUR_CFG_SIGNATURE 3972577955U


#if (defined PDUR_PUBLIC_INFO_SIGNATURE) /* to prevent double declaration */
#error PDUR_PUBLIC_INFO_SIGNATURE already defined
#endif /* if (defined PDUR_PUBLIC_INFO_SIGNATURE) */

/** \brief This macro specifies the published information signature. */
#define PDUR_PUBLIC_INFO_SIGNATURE 3287682526U

        
#if (defined PDUR_ROUTINGPATHGROUPS_SUPPORT) /* to prevent double declaration */
#error PDUR_ROUTINGPATHGROUPS_SUPPORT already defined
#endif /* if (defined PDUR_ROUTINGPATHGROUPS_SUPPORT) */

/** \brief This macro specifies if the configuration PduRRoutingPathGroupSupport is enabled */
#define PDUR_ROUTINGPATHGROUPS_SUPPORT STD_OFF


#if (defined PDUR_MULTICORE_SUPPORT) /* to prevent double declaration */
#error PDUR_MULTICORE_SUPPORT already defined
#endif /* if (defined PDUR_MULTICORE_SUPPORT) */

/** \brief This macro specifies if multicore support is enabled by PduRMultiCoreSupport. */
#define PDUR_MULTICORE_SUPPORT STD_OFF


#if (defined PDUR_PBCFG_VARIANT_SUPPORT_ENABLED) /* to prevent double declaration */
#error PDUR_PBCFG_VARIANT_SUPPORT_ENABLED already defined
#endif /* if (defined PDUR_PBCFG_VARIANT_SUPPORT_ENABLED) */

/** \brief Evaluated with help of the vairant:all() XPath function. Possible values are STD_ON if 
  *        variant handling in PduR module is configured, else STD_OFF. */
#define PDUR_PBCFG_VARIANT_SUPPORT_ENABLED STD_OFF


/*------------------[module support]----------------------------------------*/
 
#if (defined PDUR_LOIF_ENABLED) /* to prevent double declaration */
#error PDUR_LOIF_ENABLED already defined
#endif /* if (defined PDUR_LOIF_ENABLED) */

/** \brief This macro specifies if at least one lower layer communication interface module is 
  *        provided. Otherwise it is set to STD_OFF. */
#define PDUR_LOIF_ENABLED STD_ON


#if (defined PDUR_LOIF_TXCONF_ENABLED) /* to prevent double declaration */
#error PDUR_LOIF_TXCONF_ENABLED already defined
#endif /* if (defined PDUR_LOIF_TXCONF_ENABLED) */

/** \brief This macro specifies if at least one lower layer communication interface module with 
  *        enabled PduRTxConfirmation is provided. Otherwise it is set to STD_OFF. */
#define PDUR_LOIF_TXCONF_ENABLED STD_ON


#if (defined PDUR_LOIF_TRIGGERTX_ENABLED) /* to prevent double declaration */
#error PDUR_LOIF_TRIGGERTX_ENABLED already defined
#endif /* if (defined PDUR_LOIF_TRIGGERTX_ENABLED) */

/** \brief This macro specifies if at least one lower layer communication interface module with 
  *        enabled PduRTriggertransmit is provided. Otherwise it is set to STD_OFF. */
#define PDUR_LOIF_TRIGGERTX_ENABLED STD_OFF


#if (defined PDUR_LOTP_ENABLED) /* to prevent double declaration */
#error PDUR_LOTP_ENABLED already defined
#endif /* if (defined PDUR_LOTP_ENABLED) */

/** \brief This macro specifies if at least one lower layer transport protocol module is provided. 
  *        Otherwise it is set to STD_OFF. */
#define PDUR_LOTP_ENABLED STD_OFF


#if (defined PDUR_UPIF_ENABLED) /* to prevent double declaration */
#error PDUR_UPIF_ENABLED already defined
#endif /* if (defined PDUR_UPIF_ENABLED) */

/** \brief This macro specifies if at least one upper layer communication interface module is 
  *        provided. Otherwise it is set to STD_OFF. */
#define PDUR_UPIF_ENABLED STD_ON


#if (defined PDUR_UPTP_ENABLED) /* to prevent double declaration */
#error PDUR_UPTP_ENABLED already defined
#endif /* if (defined PDUR_UPTP_ENABLED) */

/** \brief This macro specifies if at least one upper layer transport protocol module is provided. 
  *        Otherwise it is set to STD_OFF. */
#define PDUR_UPTP_ENABLED STD_OFF


#if (defined PDUR_LOIF_STATPAYLOAD_ENABLED) /* to prevent double declaration */
#error PDUR_LOIF_STATPAYLOAD_ENABLED already defined
#endif /* if (defined PDUR_LOIF_STATPAYLOAD_ENABLED) */

/** \brief This macro specifies if at least one lower layer communication interface module with 
  *        enabled PduRStaticPduLengthSupport is provided. Otherwise it is set to STD_OFF. */
#define PDUR_LOIF_STATPAYLOAD_ENABLED STD_OFF


/*------------------[gateway operation]-------------------------------------*/

#if (defined PDUR_TPGATEWAY_SUPPORT) /* to prevent double declaration */
#error PDUR_TPGATEWAY_SUPPORT already defined
#endif /* if (defined PDUR_TPGATEWAY_SUPPORT) */

/** \brief This macro specifies if routing of I-PDUs from a transport protocol module to one or 
  *        more transport protocol module(s) is enabled by PduRTpGatewaySupport. */
#define PDUR_TPGATEWAY_SUPPORT STD_OFF


#if (defined PDUR_IFGATEWAY_SUPPORT) /* to prevent double declaration */
#error PDUR_IFGATEWAY_SUPPORT already defined
#endif /* if (defined PDUR_IFGATEWAY_SUPPORT) */

/** \brief This macro specifies if routing of I-PDUs from a communication interface module to one 
  *        or more communication interface module(s) is enabled by PduRIfGatewaySupport. */
#define PDUR_IFGATEWAY_SUPPORT STD_OFF


#if (defined PDUR_SB_TX_BUFFER_SUPPORT) /* to prevent double declaration */
#error PDUR_SB_TX_BUFFER_SUPPORT already defined
#endif /* if (defined PDUR_SB_TX_BUFFER_SUPPORT) */

/** \brief This macro specifies if usage of single buffers is enabled by PduRSbTxBufferSupport. 
  *        */
#define PDUR_SB_TX_BUFFER_SUPPORT STD_OFF


#if (defined PDUR_FIFO_TX_BUFFER_SUPPORT) /* to prevent double declaration */
#error PDUR_FIFO_TX_BUFFER_SUPPORT already defined
#endif /* if (defined PDUR_FIFO_TX_BUFFER_SUPPORT) */

/** \brief This macro specifies if usage of single buffers is enabled by PduRFifoTxBufferSupport. 
  *        */
#define PDUR_FIFO_TX_BUFFER_SUPPORT STD_OFF


#if (defined PDUR_TPGWQUEUE_ENABLE) /* to prevent double declaration */
#error PDUR_TPGWQUEUE_ENABLE already defined
#endif /* if (defined PDUR_TPGWQUEUE_ENABLE) */

/** \brief This macro specifies if the queuing of incoming TP gateway requests is enabled by 
  *        PduRTpGwQueueEnable for already ongoing transmissions. */
#define PDUR_TPGWQUEUE_ENABLE STD_OFF


#if (defined PDUR_TPGWQUEUE_AND_NTO1ROUTING_ENABLED) /* to prevent double declaration */
#error PDUR_TPGWQUEUE_AND_NTO1ROUTING_ENABLED already defined
#endif /* if (defined PDUR_TPGWQUEUE_AND_NTO1ROUTING_ENABLED) */

/** \brief This macro specifies if TP gateway queuing and N:1 routing features are enabled by 
  *        PduRTpGwQueueEnable and PduRNto1RoutingSupport. */
#define PDUR_TPGWQUEUE_AND_NTO1ROUTING_ENABLED STD_OFF


/*------------------[Multicast operations]-------------------------------------*/

#if (defined PDUR_MULTICAST_TOIF_SUPPORT) /* to prevent double declaration */
#error PDUR_MULTICAST_TOIF_SUPPORT already defined
#endif /* if (defined PDUR_MULTICAST_TOIF_SUPPORT) */

/** \brief This macro specifies if multicast from a local module to multiple communication 
  *        interface modules is enabled by PduRMulticastToIfSupport. */
#define PDUR_MULTICAST_TOIF_SUPPORT STD_OFF


#if (defined PDUR_MULTICAST_TX_CONFIRMATION) /* to prevent double declaration */
#error PDUR_MULTICAST_TX_CONFIRMATION already defined
#endif /* if (defined PDUR_MULTICAST_TX_CONFIRMATION) */

/** \brief This macro specifies if call of Up_TxConfirmation is enabled by 
  *        PduRMulticastTxConfirmation for routing paths to multiple communication interface 
  *        modules. */
#define PDUR_MULTICAST_TX_CONFIRMATION STD_OFF


#if (defined PDUR_MULTICAST_FROMIF_SUPPORT) /* to prevent double declaration */
#error PDUR_MULTICAST_FROMIF_SUPPORT already defined
#endif /* if (defined PDUR_MULTICAST_FROMIF_SUPPORT) */

/** \brief This macro specifies if multicast from a communication interface module to one or more 
  *        communication interface module(s) and local module(s) is enabled by 
  *        PduRMulticastFromIfSupport. */
#define PDUR_MULTICAST_FROMIF_SUPPORT STD_OFF


#if (defined PDUR_MULTICAST_UPTOLOTP_SUPPORT) /* to prevent double declaration */
#error PDUR_MULTICAST_UPTOLOTP_SUPPORT already defined
#endif /* if (defined PDUR_MULTICAST_UPTOLOTP_SUPPORT) */

/** \brief This macro specifies if multicast from a local module to multiple transport protocol 
  *        modules is enabled by PduRMulticastUpToLoTpSupport. */
#define PDUR_MULTICAST_UPTOLOTP_SUPPORT STD_OFF


#if (defined PDUR_MULTICAST_LOTPTOUP_SUPPORT) /* to prevent double declaration */
#error PDUR_MULTICAST_LOTPTOUP_SUPPORT already defined
#endif /* if (defined PDUR_MULTICAST_LOTPTOUP_SUPPORT) */

/** \brief This macro specifies if multicast from a transport protocol module to one or more 
  *        transport protocol(s) and a local module is enabled by PduRMulticastLoTpToUpSupport. 
  *        */
#define PDUR_MULTICAST_LOTPTOUP_SUPPORT STD_OFF


#if (defined PDUR_MULTICAST_TP_HIGHEST_WINS_STRATEGY) /* to prevent double declaration */
#error PDUR_MULTICAST_TP_HIGHEST_WINS_STRATEGY already defined
#endif /* if (defined PDUR_MULTICAST_TP_HIGHEST_WINS_STRATEGY) */

/** \brief This macro specifies if the highest wins strategy is applied to multicast gateway 
  *        transmissions and pure multicast transmissions for transport protocol modules by 
  *        configuration parameter PduRMulticastTpHighestWinsStrategy. */
#define PDUR_MULTICAST_TP_HIGHEST_WINS_STRATEGY STD_OFF




/*-----------[Change Parameter and Cancel Receive/Transmit Functionality]--------------*/

#if (defined PDUR_UPTP_CHANGEPARAM_ENABLED) /* to prevent double declaration */
#error PDUR_UPTP_CHANGEPARAM_ENABLED already defined
#endif /* if (defined PDUR_UPTP_CHANGEPARAM_ENABLED) */

/** \brief This macro specifies if at least one upper layer transport protocol module with enabled 
  *        PduRChangeParameterRequestApi is provided. Otherwise it is set to STD_OFF. */
#define PDUR_UPTP_CHANGEPARAM_ENABLED STD_OFF


#if (defined PDUR_UPTP_CANCELTX_ENABLED) /* to prevent double declaration */
#error PDUR_UPTP_CANCELTX_ENABLED already defined
#endif /* if (defined PDUR_UPTP_CANCELTX_ENABLED) */

/** \brief This macro specifies if at least one upper layer transport protocol module with enabled 
  *        PduRCancelTransmit is provided. Otherwise it is set to STD_OFF. */
#define PDUR_UPTP_CANCELTX_ENABLED STD_OFF


#if (defined PDUR_UPTP_CANCELRX_ENABLED) /* to prevent double declaration */
#error PDUR_UPTP_CANCELRX_ENABLED already defined
#endif /* if (defined PDUR_UPTP_CANCELRX_ENABLED) */

/** \brief This macro specifies if at least one upper layer transport protocol module with enabled 
  *        PduRCancelReceive is provided. Otherwise it is set to STD_OFF. */
#define PDUR_UPTP_CANCELRX_ENABLED STD_OFF


/*==================[type definitions]======================================*/

/*==================[external function declarations]========================*/

/*==================[internal function declarations]========================*/

/*==================[external constants]====================================*/

/*==================[internal constants]====================================*/
/*==================[external data]=========================================*/

/*==================[internal data]=========================================*/

/*==================[external function definitions]=========================*/

/*==================[internal function definitions]=========================*/

#endif /* if !defined( PDUR_CFG_H ) */
/*==================[end of file]===========================================*/
