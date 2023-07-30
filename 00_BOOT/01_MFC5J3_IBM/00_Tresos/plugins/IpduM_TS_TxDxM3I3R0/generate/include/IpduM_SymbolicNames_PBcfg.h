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
#if (!defined IPDUM_SYMBOLIC_NAMES_PBCFG_H)
#define IPDUM_SYMBOLIC_NAMES_PBCFG_H

[!INCLUDE "IpduM_Macros.m"!]

/*==================[inclusions]============================================*/

/*==================[macros]================================================*/

/************************/
/* Symbolic name values */
/************************/
[!INDENT "0"!][!//
[!SELECT "IpduMConfig/*[1]"!][!//
  [!IF "node:exists(IpduMRxPathway/*)"!][!//
    [!LOOP "IpduMRxPathway/*"!]
      /*################################################################################################*/
      /* Rx pathway: [!"name(.)"!] */
      [!CALL "GetSymbolName",
        "ShortNameRef"="'./IpduMRxIndication'",
        "OldName"="name(.)"!][!//
      [!CALL "GenSymbols",
        "SymbolicPrefix"="'IpduMConf_IpduMRxIndication_'",
        "SymbolicName"="$SymbolName",
        "SymbolicIdName"="'IpduMRxHandleId'",
        "SymbolicValue"="node:path(./IpduMRxIndication/IpduMRxHandleId)",
        "PduName"="name(node:ref(./IpduMRxIndication/IpduMRxIndicationPduRef))"!]
    [!ENDLOOP!]
  [!ENDIF!]
  [!IF "node:exists(IpduMTxPathway/*)"!][!//
    [!LOOP "IpduMTxPathway/*"!][!//
      /*################################################################################################*/
      /* Tx pathway: [!"name(.)"!] */
      [!IF "node:exists(./IpduMTxRequest/IpduMTxStaticPart)"!][!//
        [!CALL "GetSymbolName",
          "ShortNameRef"="'./IpduMTxRequest/IpduMTxStaticPart'",
          "OldName"="name(.)"!][!//
        [!CALL "GenSymbols",
          "SymbolicPrefix"="'IpduMConf_IpduMTxStaticPart_'",
          "SymbolicName"="$SymbolName",
          "SymbolicIdName"="'IpduMTxStaticHandleId'",
          "SymbolicValue"="node:path(./IpduMTxRequest/IpduMTxStaticPart/IpduMTxStaticHandleId)",
          "PduName"="name(node:ref(./IpduMTxRequest/IpduMTxStaticPart/IpduMTxStaticPduRef))"!]
      [!ENDIF!][!//
      [!LOOP "IpduMTxRequest/IpduMTxDynamicPart/*"!][!//
        [!CALL "GenSymbols",
          "SymbolicPrefix"="'IpduMConf_IpduMTxDynamicPart_'",
          "SymbolicName"="name(.)",
          "SymbolicIdName"="'IpduMTxDynamicHandleId'",
          "SymbolicValue"="node:path(./IpduMTxDynamicHandleId)",
          "PduName"="name(node:ref(./IpduMTxDynamicPduRef))"!]
      [!ENDLOOP!][!//
      [!CALL "GetSymbolName",
        "ShortNameRef"="'./IpduMTxRequest'",
        "OldName"="name(.)"!][!//
      [!CALL "GenSymbol",
        "SymbolicPrefix"="'IpduMConf_IpduMTxRequest_'",
        "SymbolicName"="$SymbolName",
        "SymbolicIdName"="'IpduMTxConfirmationPduId'",
        "SymbolicValue"="node:path(./IpduMTxRequest/IpduMTxConfirmationPduId)",
        "PduName"="name(node:ref(./IpduMTxRequest/IpduMOutgoingPduRef))"!]
    [!ENDLOOP!][!//
  [!ENDIF!][!//
  [!IF "node:exists(IpduMContainerRxPdu/*)"!][!//
    /*################################################################################################*/
    [!LOOP "IpduMContainerRxPdu/*"!]
      /* IpduMContainerRxPdu: [!"name(.)"!] */
      [!CALL "GenSymbol",
        "SymbolicPrefix"="'IpduMConf_IpduMContainerRxPdu_'",
        "SymbolicName"="name(.)",
        "SymbolicIdName"="'IpduMContainerRxHandleId'",
        "SymbolicValue"="node:path(./IpduMContainerRxHandleId)",
        "PduName"="name(node:ref(./IpduMContainerRxPduRef))"!]
    [!ENDLOOP!]
  [!ENDIF!]
  [!IF "node:exists(IpduMContainedTxPdu/*)"!][!//
    /*################################################################################################*/
    [!LOOP "IpduMContainedTxPdu/*"!]
      /* IpduMContainedTxPdu: [!"name(.)"!] */
      [!CALL "GenSymbol",
        "SymbolicPrefix"="'IpduMConf_IpduMContainedTxPdu_'",
        "SymbolicName"="name(.)",
        "SymbolicIdName"="'IpduMContainedTxPduHandleId'",
        "SymbolicValue"="node:path(./IpduMContainedTxPduHandleId)",
        "PduName"="name(node:ref(./IpduMContainedTxPduRef))"!]
    [!ENDLOOP!]
  [!ENDIF!]
  [!IF "node:exists(IpduMContainerTxPdu/*)"!][!//
    /*################################################################################################*/
    [!LOOP "IpduMContainerTxPdu/*"!]
      [!IF "node:exists(./IpduMContainerTxHandleId)"!][!//
      /* IpduMContainerTxPdu: [!"name(.)"!] */
      [!CALL "GenSymbol",
        "SymbolicPrefix"="'IpduMConf_IpduMContainerTxPdu_'",
        "SymbolicName"="name(.)",
        "SymbolicIdName"="'IpduMContainerTxHandleId'",
        "SymbolicValue"="node:path(./IpduMContainerTxHandleId)",
        "PduName"="name(node:ref(./IpduMContainerTxPduRef))"!][!//
      [!ENDIF!][!//
    [!ENDLOOP!]
  [!ENDIF!]
[!ENDSELECT!][!//
[!ENDINDENT!][!//

/*****************************************************/
/* Vendor specific outgoing and confirmation PDU IDs */
/*****************************************************/
#if (defined IPDUM_PROVIDE_ADJACENT_MODULE_VENDOR_SYMBOLIC_NAMES)
[!INDENT "0"!][!//
[!SELECT "IpduMConfig/*[1]"!][!//
  [!IF "node:exists(IpduMRxPathway/*)"!][!//
    [!LOOP "IpduMRxPathway/*"!]
     /*################################################################################################*/
      /* Rx pathway: [!"name(.)"!] */
      [!IF "node:exists(./IpduMRxIndication/IpduMRxStaticPart)"!][!/*
        */!][!CALL "GetOutputPduId","IpduMOutgoingPduRef"="IpduMRxIndication/IpduMRxStaticPart/IpduMOutgoingStaticPduRef"!]
        /* [!"node:path(IpduMRxIndication/IpduMRxStaticPart/IpduMOutgoingStaticPduRef)"!] */
#if (defined IPDUM_RX_OUTGOING_ID_[!"name(.)"!])
#error IPDUM_RX_OUTGOING_ID_[!"name(.)"!] already defined!
#endif /* #if (defined IPDUM_RX_OUTGOING_ID_[!"name(.)"!])*/
        #define IPDUM_RX_OUTGOING_ID_[!"name(.)"!] [!"num:i($PduID)"!]U /* [!"name(node:ref(IpduMRxIndication/IpduMRxStaticPart/IpduMOutgoingStaticPduRef))"!] Static Rx */
      [!ENDIF!][!//
      [!LOOP "IpduMRxIndication/IpduMRxDynamicPart/*"!]
        [!CALL "GetOutputPduId","IpduMOutgoingPduRef"="IpduMOutgoingDynamicPduRef"!][!/*
        */!]/* [!"node:path(IpduMOutgoingDynamicPduRef)"!] */
#if (defined IPDUM_RX_OUTGOING_ID_[!"name(./../../..)"!]_[!"name(.)"!])
#error IPDUM_RX_OUTGOING_ID_[!"name(./../../..)"!]_[!"name(.)"!] already defined!
#endif /* #if (defined IPDUM_RX_OUTGOING_ID_[!"name(./../../..)"!]_[!"name(.)"!])*/
        #define IPDUM_RX_OUTGOING_ID_[!"name(./../../..)"!]_[!"name(.)"!] [!"num:i($PduID)"!]U /* [!"name(node:ref(IpduMOutgoingDynamicPduRef))"!] Dynamic Rx */
      [!ENDLOOP!][!//
    [!ENDLOOP!][!//
  [!ENDIF!][!//
  [!IF "node:exists(IpduMContainedRxPdu/*)"!][!//
    /*################################################################################################*/
    [!LOOP "IpduMContainedRxPdu/*"!]
      /* IpduMContainedRxPdu: [!"name(.)"!] */
      [!CALL "GetOutputPduId","IpduMOutgoingPduRef"="./IpduMContainedRxPduRef"!][!/*
      */!]
#if (defined IPDUM_RX_OUTGOING_ID_[!"name(.)"!])
#error IPDUM_RX_OUTGOING_ID_[!"name(.)"!] already defined!
#endif /* #if (defined IPDUM_RX_OUTGOING_ID_[!"name(.)"!])*/
        #define IPDUM_RX_OUTGOING_ID_[!"name(.)"!] [!"num:i($PduID)"!]U
    [!ENDLOOP!][!//
  [!ENDIF!][!//
  [!IF "node:exists(IpduMContainerTxPdu/*)"!]
    /*################################################################################################*/
    [!LOOP "IpduMContainerTxPdu/*"!]
      /* IpduMContainerTxPdu: [!"name(.)"!] */
      [!CALL "GetOutputPduId", "IpduMOutgoingPduRef"="./IpduMContainerTxPduRef"!][!//
#if (defined IPDUM_TX_OUTGOING_ID_[!"name(.)"!])
#error IPDUM_TX_OUTGOING_ID_[!"name(.)"!] already defined!
#endif /* #if (defined IPDUM_TX_OUTGOING_ID_[!"name(.)"!])*/
      #define IPDUM_TX_OUTGOING_ID_[!"name(.)"!] [!"num:i($PduID)"!]U  /* [!"name(node:ref(./IpduMContainerTxPduRef))"!] Tx */
    [!ENDLOOP!]
  [!ENDIF!]
  [!IF "node:exists(IpduMContainedTxPdu/*)"!]
    /*################################################################################################*/
    [!LOOP "IpduMContainedTxPdu/*"!]
      /* IpduMContainedTxPdu: [!"name(.)"!] */
      [!CALL "GetResponsePduId", "IpduMPduRef"="./IpduMContainedTxPduRef"!][!//
#if (defined IPDUM_TX_CONFIRM_ID_[!"name(.)"!])
#error IPDUM_TX_CONFIRM_ID_[!"name(.)"!] already defined!
#endif /* #if (defined IPDUM_TX_CONFIRM_ID_[!"name(.)"!])*/
      #define IPDUM_TX_CONFIRM_ID_[!"name(.)"!] [!"num:i($ResponsePduID)"!]U  /* [!"name(node:ref(./IpduMContainedTxPduRef))"!] Tx */
    [!ENDLOOP!]
  [!ENDIF!]
  [!IF "node:exists(IpduMContainerTxPdu/*)"!]
    /*################################################################################################*/
    [!LOOP "IpduMContainerTxPdu/*"!]
      /* IpduMContainerTxPdu: [!"name(.)"!] */
      [!CALL "GetResponsePduId", "IpduMPduRef"="./IpduMContainerTxPduRef"!][!//
#if (defined IPDUM_TX_CONFIRM_ID_[!"name(.)"!])
#error IPDUM_TX_CONFIRM_ID_[!"name(.)"!] already defined!
#endif /* #if (defined IPDUM_TX_CONFIRM_ID_[!"name(.)"!])*/
      #define IPDUM_TX_CONFIRM_ID_[!"name(.)"!] [!"num:i($ResponsePduID)"!]U  /* [!"name(node:ref(./IpduMContainerTxPduRef))"!] Tx */
    [!ENDLOOP!]
  [!ENDIF!]
  [!IF "node:exists(IpduMTxPathway/*)"!][!//
    [!LOOP "IpduMTxPathway/*"!]
     /*################################################################################################*/
      /* Tx pathway: [!"name(.)"!] */
      [!IF "node:exists(./IpduMTxRequest/IpduMTxStaticPart)"!][!/*
        */!][!IF "./IpduMTxRequest/IpduMTxStaticPart/IpduMTxStaticConfirmation = 'true'"!][!/*
          */!][!CALL "GetResponsePduId","IpduMPduRef"="IpduMTxRequest/IpduMTxStaticPart/IpduMTxStaticPduRef"!]
              /* [!"node:path(IpduMTxRequest/IpduMTxStaticPart/IpduMTxStaticPduRef)"!] */
#if (defined IPDUM_TX_CONFIRM_ID_[!"name(.)"!])
#error IPDUM_TX_CONFIRM_ID_[!"name(.)"!] already defined!
#endif /* #if (defined IPDUM_TX_CONFIRM_ID_[!"name(.)"!])*/
              #define IPDUM_TX_CONFIRM_ID_[!"name(.)"!] [!"num:i($ResponsePduID)"!]U /* [!"name(node:ref(IpduMTxRequest/IpduMTxStaticPart/IpduMTxStaticPduRef))"!] Static Tx */
            [!ELSE!][!//
              /* [!"name(node:ref(IpduMTxRequest/IpduMTxStaticPart/IpduMTxStaticPduRef))"!] Disabled static TxConfirmation */
            [!ENDIF!][!//
      [!ENDIF!][!//
      [!LOOP "IpduMTxRequest/IpduMTxDynamicPart/*"!][!/*
        */!][!IF "./IpduMTxDynamicConfirmation = 'true'"!][!/*
          */!][!CALL "GetResponsePduId","IpduMPduRef"="./IpduMTxDynamicPduRef"!]
              /* [!"node:path(IpduMTxDynamicPduRef)"!] */
#if (defined IPDUM_TX_CONFIRM_ID_[!"name(./../../..)"!]_[!"name(.)"!])
#error IPDUM_TX_CONFIRM_ID_[!"name(./../../..)"!]_[!"name(.)"!] already defined!
#endif /* #if (defined IPDUM_TX_CONFIRM_ID_[!"name(./../../..)"!]_[!"name(.)"!])*/
              #define IPDUM_TX_CONFIRM_ID_[!"name(./../../..)"!]_[!"name(.)"!] [!"num:i($ResponsePduID)"!]U /* [!"name(node:ref(IpduMTxDynamicPduRef))"!] Dynamic Tx */
            [!ELSE!][!//
                 /* [!"name(node:ref(IpduMTxDynamicPduRef))"!]  Disabled dynamic TxConfirmation */
            [!ENDIF!][!//
      [!ENDLOOP!][!/*
        */!][!CALL "GetOutputPduId","IpduMOutgoingPduRef"="./IpduMTxRequest/IpduMOutgoingPduRef"!]
        /* [!"node:path(./IpduMTxRequest/IpduMOutgoingPduRef)"!] */
#if (defined IPDUM_TX_OUTGOING_ID_[!"name(.)"!])
#error IPDUM_TX_OUTGOING_ID_[!"name(.)"!] already defined!
#endif /* #if (defined IPDUM_TX_OUTGOING_ID_[!"name(.)"!])*/
        #define IPDUM_TX_OUTGOING_ID_[!"name(.)"!] [!"num:i($PduID)"!]U  /* [!"name(node:ref(./IpduMTxRequest/IpduMOutgoingPduRef))"!] Tx */
    [!ENDLOOP!][!//
  [!ENDIF!][!//
[!ENDSELECT!][!//
[!ENDINDENT!][!//
#endif

/*==================[type definitions]======================================*/

/*==================[external function declarations]========================*/

/*==================[internal function declarations]========================*/

/*==================[external constants]====================================*/

/*==================[internal constants]====================================*/

/*==================[external data]=========================================*/

/*==================[internal data]=========================================*/

/*==================[external function definitions]=========================*/

/*==================[internal function definitions]=========================*/

#endif /* if !defined( IPDUM_SYMBOLIC_NAMES_PBCFG_H ) */
/*==================[end of file]===========================================*/
