
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

#ifndef PDUR_CFGTYPES_H
#define PDUR_CFGTYPES_H



/*==================[inclusions]=============================================*/

#include <Platform_Types.h>
#include <TSAutosar.h>
#define TS_RELOCATABLE_CFG_ENABLE STD_OFF
#define TS_PB_CFG_PTR_CLASS PDUR_APPL_CONST
#include <TSPBConfig_Types.h>


/*==================[macros]=================================================*/


/*==================[type definitions]=======================================*/

typedef VAR( uint16, TYPEDEF ) PduR_GateTpSessionIndexType;

typedef VAR( uint16, TYPEDEF ) PduR_RefToRAM;

typedef VAR( uint16, TYPEDEF ) PduR_BufTpIndexType;

typedef VAR( uint16, TYPEDEF ) PduR_PduIdType;

typedef VAR( uint16, TYPEDEF ) PduR_RefToModuleAPI;

typedef VAR( uint8, TYPEDEF ) PduR_GateTpQueueIndexType;

typedef VAR( uint16, TYPEDEF ) PduR_TpThresholdType;

typedef VAR( uint16, TYPEDEF ) PduR_PduLengthType;

typedef struct /* PduR_AbstractRoutingTableEntry */ {
    VAR( PduR_PduIdType, TYPEDEF ) TargetPduId;
} PduR_AbstractRoutingTableEntry;

typedef struct /* PduR_RTabUpIfTxType */ {
    VAR( PduR_PduIdType, TYPEDEF ) TargetPduId;
    VAR( PduR_RefToModuleAPI, TYPEDEF ) TargetModuleAPIRef;
} PduR_RTabUpIfTxType;

typedef struct /* PduR_RTabLoIfType */ {
    VAR( PduR_PduIdType, TYPEDEF ) TargetPduId;
    VAR( PduR_RefToModuleAPI, TYPEDEF ) TargetModuleAPIRef;
} PduR_RTabLoIfType;

typedef struct /* PduR_Nto1TabTpType */ {
    VAR( PduR_PduIdType, TYPEDEF ) GMPduId;
    VAR( PduR_RefToRAM, TYPEDEF ) GMPduIdMemRef;
} PduR_Nto1TabTpType;

typedef struct /* PduR_GTabTpRxType */ {
    VAR( PduR_PduIdType, TYPEDEF ) TargetPduId;
    VAR( PduR_RefToRAM, TYPEDEF ) SessionQueueMemRef;
    VAR( PduR_TpThresholdType, TYPEDEF ) TpThreshold;
    VAR( PduR_RefToModuleAPI, TYPEDEF ) TargetModuleAPIRef;
    VAR( uint8, TYPEDEF ) MoreEntries;
    VAR( PduR_GateTpQueueIndexType, TYPEDEF ) SessionQueueDepth;
} PduR_GTabTpRxType;

typedef struct /* PduR_GTabIfRxType */ {
    VAR( PduR_PduIdType, TYPEDEF ) TargetPduId;
    VAR( uint16, TYPEDEF ) BufferId;
    VAR( PduR_RefToModuleAPI, TYPEDEF ) TargetModuleAPIRef;
} PduR_GTabIfRxType;

typedef struct /* PduR_MTabUpTpTxType */ {
    VAR( PduR_PduIdType, TYPEDEF ) TargetPduId;
    VAR( PduR_PduIdType, TYPEDEF ) UprLyrTxPduId;
    VAR( PduR_RefToModuleAPI, TYPEDEF ) TargetModuleAPIRef;
    VAR( PduR_RefToModuleAPI, TYPEDEF ) SourceModuleAPIRef;
    VAR( uint8, TYPEDEF ) TotalNumDests;
} PduR_MTabUpTpTxType;

typedef struct /* PduR_MTabUpIfTxType */ {
    VAR( PduR_PduIdType, TYPEDEF ) TargetPduId;
    VAR( PduR_RefToModuleAPI, TYPEDEF ) TargetModuleAPIRef;
    VAR( PduR_RefToModuleAPI, TYPEDEF ) SourceModuleAPIRef;
    VAR( PduR_PduIdType, TYPEDEF ) UprLyrTxPduId;
    VAR( PduR_BufTpIndexType, TYPEDEF ) BufferId;
    VAR( uint8, TYPEDEF ) TotalNumDests;
    VAR( uint8, TYPEDEF ) TxConfEnabled;
} PduR_MTabUpIfTxType;

typedef struct /* PduR_MTabLoIfRxType */ {
    VAR( PduR_PduIdType, TYPEDEF ) TargetPduId;
    VAR( PduR_RefToModuleAPI, TYPEDEF ) TargetModuleAPIRef;
    VAR( uint8, TYPEDEF ) MoreEntries;
} PduR_MTabLoIfRxType;

typedef struct /* PduR_BufTpConfigType */ {
    VAR( PduR_RefToRAM, TYPEDEF ) MemRef;
    VAR( PduR_PduLengthType, TYPEDEF ) Length;
} PduR_BufTpConfigType;

typedef struct /* PduR_BufTfDynPyldConfigType */ {
    TS_REF2CFG( uint8 )  DefaultRef;
    VAR( PduR_RefToRAM, TYPEDEF ) MemRef;
    VAR( PduR_RefToRAM, TYPEDEF ) UsedSduLengthPtr;
    VAR( uint8, TYPEDEF ) Length;
    VAR( uint8, TYPEDEF ) Depth;
} PduR_BufTfDynPyldConfigType;

typedef struct /* PduR_BufDfDynPyldConfigType */ {
    VAR( PduR_RefToRAM, TYPEDEF ) MemRef;
    VAR( PduR_RefToRAM, TYPEDEF ) UsedSduLengthPtr;
    VAR( uint8, TYPEDEF ) Length;
    VAR( uint8, TYPEDEF ) Depth;
} PduR_BufDfDynPyldConfigType;

typedef struct /* PduR_BufSbConfigType */ {
    TS_REF2CFG( uint8 )  DefaultRef;
    VAR( PduR_RefToRAM, TYPEDEF ) MemRef;
    VAR( uint8, TYPEDEF ) Length;
} PduR_BufSbConfigType;

typedef struct /* PduR_BufTfConfigType */ {
    TS_REF2CFG( uint8 )  DefaultRef;
    VAR( PduR_RefToRAM, TYPEDEF ) MemRef;
    VAR( uint8, TYPEDEF ) Length;
    VAR( uint8, TYPEDEF ) Depth;
} PduR_BufTfConfigType;

typedef struct /* PduR_BufDfConfigType */ {
    VAR( PduR_RefToRAM, TYPEDEF ) MemRef;
    VAR( uint8, TYPEDEF ) Length;
    VAR( uint8, TYPEDEF ) Depth;
} PduR_BufDfConfigType;

typedef struct /* PduR_RTabUpIfTxConfigType */ {
    TS_REF2CFG( PduR_RTabUpIfTxType )  RTabTxRef;
    VAR( PduR_PduIdType, TYPEDEF ) RTabTxCount;
} PduR_RTabUpIfTxConfigType;

typedef struct /* PduR_RTabLoIfConfigType */ {
    TS_REF2CFG( PduR_RTabLoIfType )  RTabRxRef;
    TS_REF2CFG( PduR_RTabLoIfType )  RTabTxRef;
    VAR( PduR_PduIdType, TYPEDEF ) RTabRxCount;
    VAR( PduR_PduIdType, TYPEDEF ) RTabTxCount;
} PduR_RTabLoIfConfigType;

typedef struct /* PduR_Nto1TabTpConfigType */ {
    TS_REF2CFG( PduR_Nto1TabTpType )  Nto1TabTpRef;
    VAR( PduR_PduIdType, TYPEDEF ) Nto1TabTpCount;
} PduR_Nto1TabTpConfigType;

typedef struct /* PduR_GTabTpConfigType */ {
    TS_REF2CFG( PduR_GTabTpRxType )  GTabRxRef;
    VAR( PduR_PduIdType, TYPEDEF ) GTabRxCount;
} PduR_GTabTpConfigType;

typedef struct /* PduR_GTabIfConfigType */ {
    TS_REF2CFG( PduR_GTabIfRxType )  GTabRxRef;
    VAR( PduR_PduIdType, TYPEDEF ) GTabRxCount;
} PduR_GTabIfConfigType;

typedef struct /* PduR_MTabUpTpConfigType */ {
    TS_REF2CFG( PduR_MTabUpTpTxType )  MTabTxRef;
    VAR( PduR_PduIdType, TYPEDEF ) MTabTxCount;
} PduR_MTabUpTpConfigType;

typedef struct /* PduR_MTabUpIfConfigType */ {
    TS_REF2CFG( PduR_MTabUpIfTxType )  MTabTxRef;
    VAR( PduR_PduIdType, TYPEDEF ) MTabTxCount;
} PduR_MTabUpIfConfigType;

typedef struct /* PduR_MTabLoIfConfigType */ {
    TS_REF2CFG( PduR_MTabLoIfRxType )  MTabRxRef;
    VAR( PduR_PduIdType, TYPEDEF ) MTabRxCount;
} PduR_MTabLoIfConfigType;

typedef struct /* PduR_PBConfigType */ {
    VAR( uint32, TYPEDEF ) PduR_PlatformSignature;
    VAR( uint32, TYPEDEF ) PduR_PublicInfoSignature;
    VAR( uint32, TYPEDEF ) PduR_CfgSignature;
    VAR( uint32, TYPEDEF ) PduR_LcfgSignature;
    TS_REF2CFG( uint8 )  PduR_BufDefaultRef;
    TS_REF2CFG( PduR_BufSbConfigType )  PduR_BufSbConfigRef;
    TS_REF2CFG( PduR_BufDfConfigType )  PduR_BufDfConfigRef;
    TS_REF2CFG( PduR_BufTfConfigType )  PduR_BufTfConfigRef;
    TS_REF2CFG( PduR_BufSbConfigType )  PduR_BufSbDynPyldConfigRef;
    TS_REF2CFG( PduR_BufDfDynPyldConfigType )  PduR_BufDfDynPyldConfigRef;
    TS_REF2CFG( PduR_BufTfDynPyldConfigType )  PduR_BufTfDynPyldConfigRef;
    TS_REF2CFG( PduR_BufTpConfigType )  PduR_BufTpConfigRef;
    CONST( PduR_MTabLoIfConfigType, TYPEDEF ) PduR_MTabLoIfConfig;
    CONST( PduR_MTabUpIfConfigType, TYPEDEF ) PduR_MTabUpIfConfig;
    CONST( PduR_MTabUpTpConfigType, TYPEDEF ) PduR_MTabUpTpConfig;
    CONST( PduR_GTabIfConfigType, TYPEDEF ) PduR_GTabIfConfig;
    CONST( PduR_GTabTpConfigType, TYPEDEF ) PduR_GTabTpConfig;
    CONST( PduR_Nto1TabTpConfigType, TYPEDEF ) PduR_Nto1TabTpConfig;
    VAR( PduR_RTabLoIfConfigType, TYPEDEF ) PduR_RTabLoIfConfig[1];
    VAR( PduR_RTabUpIfTxConfigType, TYPEDEF ) PduR_RTabUpIfTxConfig[1];
    VAR( uint16, TYPEDEF ) PduR_ConfigurationId;
    VAR( uint16, TYPEDEF ) PduR_BufSbCount;
    VAR( uint16, TYPEDEF ) PduR_BufDfCount;
    VAR( uint16, TYPEDEF ) PduR_BufTfCount;
    VAR( uint16, TYPEDEF ) PduR_BufSbDynPyldCount;
    VAR( uint16, TYPEDEF ) PduR_BufDfDynPyldCount;
    VAR( uint16, TYPEDEF ) PduR_BufTfDynPyldCount;
    VAR( PduR_BufTpIndexType, TYPEDEF ) PduR_BufTpCount;
    VAR( PduR_RefToRAM, TYPEDEF ) PduR_MultiTpTxSessionInfoRef;
    VAR( PduR_RefToRAM, TYPEDEF ) PduR_MultiIfTxInfoRef;
    VAR( PduR_RefToRAM, TYPEDEF ) PduR_BufSbDynPyldInfoRef;
    VAR( PduR_RefToRAM, TYPEDEF ) PduR_BufDfInfoRef;
    VAR( PduR_RefToRAM, TYPEDEF ) PduR_BufDfDynPyldInfoRef;
    VAR( PduR_RefToRAM, TYPEDEF ) PduR_BufTfInfoRef;
    VAR( PduR_RefToRAM, TYPEDEF ) PduR_BufTfDynPyldInfoRef;
    VAR( PduR_RefToRAM, TYPEDEF ) PduR_GateTpSessionInfoRef;
    VAR( PduR_RefToRAM, TYPEDEF ) PduR_GateTpSessionQueueInfoRef;
    VAR( uint8, TYPEDEF ) PduR_MultiTpTxRPathsMax;
} PduR_PBConfigType;


/*==================[external function declarations]=========================*/


/*==================[internal function declarations]=========================*/


/*==================[external constants]=====================================*/


/*==================[internal constants]=====================================*/


/*==================[external data]==========================================*/


/*==================[internal data]==========================================*/


/*==================[external function definitions]==========================*/


/*==================[internal function definitions]==========================*/



#undef TS_RELOCATABLE_CFG_ENABLE

#undef TS_PB_CFG_PTR_CLASS

#endif /* PDUR_CFGTYPES_H */

/*==================[end of file]============================================*/

