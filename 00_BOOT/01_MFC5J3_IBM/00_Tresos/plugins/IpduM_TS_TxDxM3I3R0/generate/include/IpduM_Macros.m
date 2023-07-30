[!/**
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
 */!][!//

[!INCLUDE "IpduM_GenParams.m"!]

[!NOCODE!]
[!IF "not(var:defined('IPDUM_MACROS_M'))"!]
[!VAR "IPDUM_MACROS_M"="'true'"!]

[!/* ComStack_FindNextOne() needs a terminator bit set */!]
[!VAR "IpduM_ExtraBitsForSearchAlgo" = "num:i(1)"!]

[!/*
****************************************************************************************************
* Helper macro calculates the necessary bitfield size in uint32s
* Suitable to be used for ComStack_FindNextOne() searchable bitfields.
* The result is in "BFSizeU32"
****************************************************************************************************
*/!]
[!MACRO "GetBFSizeInUINT32", "numElems"!][!NOCODE!]
[!VAR "BFSizeU32" = "num:i(($numElems + $IpduM_ExtraBitsForSearchAlgo + 31) div 32)"!]
[!ENDNOCODE!][!ENDMACRO!]

[!/*
****************************************************************************************************
* Helper macro that facilitates the alignment of RAM data.
* The result resides in "valPadded".
****************************************************************************************************
*/!]
[!MACRO "IpduMHelpAlign","valToExtend","Alignment"="4"!][!NOCODE!]
[!VAR "valPadded" = "num:i($valToExtend)"!]
[!IF "$valToExtend > 0"!]
  [!VAR "padVal" = "num:i($Alignment - ($valToExtend mod $Alignment))"!]
  [!VAR "valPadded" = "num:i($valToExtend + $padVal)"!]
[!ENDIF!]
[!ENDNOCODE!][!ENDMACRO!]

[!/*
****************************************************************************************************
* MACRO establishes the IpduM_DataMem slice allocated to TxPathways
* Within this file it's not grouped with the others because it's used by IpduMCalculateRxQueueSlices
****************************************************************************************************
*/!]
[!MACRO "GetTxPathwaySize"!][!NOCODE!]
[!VAR "IpduMDataMemPathwayOffset" = "'0U'"!][!/*This is always zero*/!]
[!VAR "IpduMDataMemPathwaySize" = "'0U'"!]
[!SELECT "as:modconf('IpduM')/IpduMConfig/*[1]"!]
[!IF "node:exists(IpduMTxPathway/*)"!]
  [!VAR "TxPathWayTotalCount" = "num:i(count(IpduMTxPathway/*))"!]
  [!IF "$IpduMDynamicPartQueue = 'true'"!]
    [!VAR "TxQueueTotalEntries" = "num:i(sum(IpduMTxPathway/*/IpduMTxRequest/IpduMQueueSize))"!]
  [!ELSE!]
    [!VAR "TxQueueTotalEntries" = "num:i(0)"!]
  [!ENDIF!]
  [!IF "$IpduMZeroCopy = 'true'"!]
    [!VAR "TxTotalBufferSize" = "num:i(0)"!]
  [!ELSE!]
    [!CALL "IpduMHelpAlign","valToExtend"="num:i(sum(node:refs(./IpduMTxPathway/*/IpduMTxRequest/IpduMOutgoingPduRef)/PduLength))"!]
    [!VAR "TxTotalBufferSize" = "$valPadded"!]
  [!ENDIF!]
[!VAR "IpduMDataMemPathwaySize"!](sizeof(IpduM_TxDataType)*[!"$TxPathWayTotalCount"!]U) + (sizeof(IpduM_QueueEntryType)*[!"$TxQueueTotalEntries"!]U) + [!"$TxTotalBufferSize"!]U[!ENDVAR!]
[!ENDIF!][!//IpduMTxPathway
[!ENDSELECT!]
[!ENDNOCODE!][!ENDMACRO!]

[!/*
****************************************************************************************************
* This calculates the queue slices allocated for the TX containers and stores them in a string.
* Entries consist of colon-joined container index, buffer index, queue index tuples
* separated by semicolons.
****************************************************************************************************
*/!]
[!VAR "sizPduLen" = "as:modconf('EcuC')/EcucPduCollection/PduLengthTypeEnum"!]
[!IF "$sizPduLen = 'UINT32'"!]
  [!VAR "sizPduLen" = "num:i(4)"!]
[!ELSEIF "$sizPduLen = 'UINT16'"!]
  [!VAR "sizPduLen" = "num:i(2)"!]
[!ELSE!]
  [!VAR "sizPduLen" = "num:i(1)"!]
[!ENDIF!]

[!MACRO "IpduMCalculateQueueTxSlices"!][!NOCODE!]
[!VAR "IpduMQTxSlicesLst" = "''"!]
[!VAR "BuffQIdxTxCumulator" = "num:i(0)"!]
[!VAR "QTxSizeCumulator" = "num:i(0)"!]
[!LOOP "as:modconf('IpduM')/IpduMConfig/*[1]/IpduMContainerTxPdu/*"!]
  [!IF "node:exists(IpduMContainerQueueSize)"!]
    [!VAR "IpduMQTxSlicesLst"!][!"$IpduMQTxSlicesLst"!];[!"node:pos(.)"!]:[!"$QTxSizeCumulator"!]:[!"$BuffQIdxTxCumulator"!][!ENDVAR!]
    [!VAR "BuffQIdxTxCumulator" = "$BuffQIdxTxCumulator + num:i(1)"!]
    [!VAR "QTxSizeCumulator" = "num:i($QTxSizeCumulator + node:value(IpduMContainerQueueSize)*($sizPduLen + node:ref(IpduMContainerTxPduRef)/PduLength))"!]
  [!ENDIF!]
[!ENDLOOP!]
[!VAR "IpduMQTxSlicesLst"!][!"$IpduMQTxSlicesLst"!];[!ENDVAR!]
[!CALL "IpduMHelpAlign","valToExtend"="$QTxSizeCumulator"!]
[!VAR "QTxSizeCumulator" = "$valPadded"!]
[!ENDNOCODE!][!ENDMACRO!]

[!/*
****************************************************************************************************
* Macro used to established whether byte swapping the header id is necessary
****************************************************************************************************
*/!]
[!MACRO "IpduMIsHeaderSwapNeeded"!][!NOCODE!]
[!VAR "IpduMHeaderSwapNeeded" = "false()"!]
[!VAR "IHBO" = "'LE'"!]
[!IF "node:exists(as:modconf('IpduM')[1]/IpduMGeneral/IpduMHeaderByteOrder) and node:value(as:modconf('IpduM')[1]/IpduMGeneral/IpduMHeaderByteOrder) = 'IPDUM_BIG_ENDIAN'"!]
  [!VAR "IHBO" = "'BE'"!]
[!ENDIF!]
[!IF "asc:getEndianness() != $IHBO"!]
  [!VAR "IpduMHeaderSwapNeeded" = "true()"!]
[!ENDIF!]
[!ENDNOCODE!][!ENDMACRO!]

[!/*
****************************************************************************************************
* Macro swaps an uint32 (byte reversal)
* The output is stored in the variable IpduMHeaderID
****************************************************************************************************
*/!]
[!MACRO "IpduMGetHeaderID", "headerIDVal"!][!NOCODE!]
[!IF "not(var:defined('IpduMHeaderSwapNeeded'))"!]
  [!CALL "IpduMIsHeaderSwapNeeded"!]
[!ENDIF!]
[!IF "$IpduMHeaderSwapNeeded = 'false'"!]
  [!VAR "IpduMHeaderID" = "num:i($headerIDVal)"!]
[!ELSE!]
  [!VAR "IpduMHeaderID" = "num:i(bit:or(bit:or(bit:or(bit:shr(bit:and($headerIDVal,4278190080),24), bit:shr(bit:and($headerIDVal, 16711680),8)), bit:shl(bit:and($headerIDVal, 65280),8)), bit:shl(bit:and($headerIDVal, 255), 24)))"!]
[!ENDIF!]
[!ENDNOCODE!][!ENDMACRO!]

[!/*
****************************************************************************************************
* This calculates the queue indices allocated for the RX containers and stores them in a string.
* Entries consist of colon-joined container index, buffer index, queue index tuples
* separated by semicolons. The dummy value 0 is used because of the shared macro GetBuffSliceIdx.
****************************************************************************************************
*/!]
[!MACRO "IpduMCalculateRxQueueSlices"!][!NOCODE!]
[!VAR "IpduMRxQSlicesLst" = "''"!]
[!VAR "RxBuffQIdxCumulator" = "num:i(-1)"!]
[!VAR "buffIdx" = "num:i(0)"!]
[!IF "not(var:defined(IpduMDataMemPathwaySize))"!][!CALL "GetTxPathwaySize"!][!ENDIF!]
[!CALL "GetBFSizeInUINT32", "numElems"="$NoOfDeferredContainers"!]
[!VAR "IpduMDeferredListSize" = "$BFSizeU32"!]
  [!IF "$IpduMMultiMF = 'true'"!]
    [!/* Suboptimal allocation, can be reduced once the generator is migrated */!]
    [!VAR "IpduMDeferredListSize" = "num:i($IpduMDeferredListSize * (1 + count(as:modconf('IpduM')[1]/IpduMGeneral/IpduMRxProcessing/*)) * 4 )"!]
[!ENDIF!]
[!VAR "buffIdxBaseRx" = "concat('(IpduM_DataOffsetType)(',$IpduMDataMemPathwaySize,' + (sizeof(uint32)*',$IpduMDeferredListSize,'U)')"!]
[!LOOP "node:order(as:modconf('IpduM')/IpduMConfig/*[1]/IpduMContainerRxPdu/*[node:value(IpduMContainerPduProcessing) = 'IPDUM_PROCESSING_DEFERRED'], 'node:IpduMContainerRxHandleId')"!]
  [!VAR "RxCntQueueSize" = "num:i(1)"!]
  [!IF "node:exists(IpduMContainerQueueSize)"!]
    [!VAR "RxBuffQIdxCumulator" = "$RxBuffQIdxCumulator + num:i(1)"!]
    [!VAR "RxCntQueueSize" = "node:value(IpduMContainerQueueSize)"!]
  [!ENDIF!]
    [!VAR "IpduMRxQSlicesLst"!][!"$IpduMRxQSlicesLst"!];[!"node:pos(.)"!]:[!"concat($buffIdxBaseRx,' + ',$buffIdx,'U)')"!]:[!"$RxBuffQIdxCumulator"!][!ENDVAR!]
  [!VAR "buffIdx" = "num:i($buffIdx + (node:value(as:ref(./IpduMContainerRxPduRef)/PduLength) + $sizPduLen) * $RxCntQueueSize)"!]
[!ENDLOOP!]
[!VAR "IpduMRxQSlicesLst"!][!"$IpduMRxQSlicesLst"!];[!ENDVAR!]
[!CALL "IpduMHelpAlign","valToExtend"="$buffIdx"!]
[!VAR "DeferredDataLength"="num:i($valPadded)"!]
[!ENDNOCODE!][!ENDMACRO!]

[!/*
****************************************************************************************************
*/!]
[!NOCODE!]
[!IF "$IpduMContainerPduHandlingEnable = 'true'"!]
  [!CALL "IpduMCalculateQueueTxSlices"!]
  [!CALL "IpduMCalculateRxQueueSlices"!]
[!ENDIF!]
[!ENDNOCODE!]

[!/*
****************************************************************************************************
* Sorts the Tx Containers because node:order() and node:when() can't
****************************************************************************************************
*/!]
[!MACRO "GetIpduMTxContainersLst"!][!NOCODE!]
[!VAR "IpduMTxContainersLst" = "''"!]
[!VAR "IpduMCntrIdx" = "num:i(0)"!]
[!LOOP "node:order(as:modconf('IpduM')/IpduMConfig/*[1]/IpduMContainerTxPdu/*[node:exists(IpduMContainerTxHandleId)], 'node:IpduMContainerTxHandleId')"!]
  [!VAR "IpduMTxContainersLst"!][!"$IpduMTxContainersLst"!];[!"as:path(.)"!]:[!"$IpduMCntrIdx"!][!ENDVAR!]
  [!VAR "IpduMCntrIdx" = "num:i($IpduMCntrIdx + 1)"!]
[!ENDLOOP!]
[!LOOP "node:order(as:modconf('IpduM')/IpduMConfig/*[1]/IpduMContainerTxPdu/*[not(node:exists(IpduMContainerTxHandleId))], 'node:name(.)')"!]
  [!VAR "IpduMTxContainersLst"!][!"$IpduMTxContainersLst"!];[!"as:path(.)"!]:[!"$IpduMCntrIdx"!][!ENDVAR!]
  [!VAR "IpduMCntrIdx" = "num:i($IpduMCntrIdx + 1)"!]
[!ENDLOOP!]
[!VAR "IpduMTxContainersLst" = "concat($IpduMTxContainersLst, ';')"!]
[!ENDNOCODE!][!ENDMACRO!]

[!/*
****************************************************************************************************
* Gets the Contained collections semantics based on Container referenced
* (Gets backward reference from Container to Contained)
****************************************************************************************************
*/!]
[!MACRO "GetIpduMCntrCollectSemantics", "Container"!][!NOCODE!]
[!VAR "parentNode" = "node:path($Container)"!]
[!LOOP "../../IpduMContainedTxPdu/*"!]
  [!IF "node:path(node:value(./IpduMContainedTxInContainerPduRef))=$parentNode"!]
    [!VAR "CollectionSemantics" = "node:value(./IpduMContainedTxPduCollectionSemantics)"!]
    [!BREAK!]
  [!ENDIF!]
[!ENDLOOP!]
[!ENDNOCODE!][!ENDMACRO!]


[!/*
****************************************************************************************************
* Gets the number of containeds that have different priorities.
* (If we have containeds with different priorities then it makes sense to sort them)
****************************************************************************************************
*/!]
[!MACRO "GetIpduMCntdTxPrioFlag", "Container"!][!NOCODE!]
[!VAR "prios" = "text:join((../../IpduMContainedTxPdu/*[node:exists(IpduMContainedTxPduPriority) and node:path(node:value(./IpduMContainedTxInContainerPduRef)) = $Container]/IpduMContainedTxPduPriority), ':')"!]
[!VAR "prioFlag" = "node:when(num:min(text:split($prios, ':')) != num:max(text:split($prios, ':')), num:i(1), num:i(0))"!]
[!ENDNOCODE!][!ENDMACRO!]


[!/*
****************************************************************************************************
* Sets the variable IpduMCntdInCntrIdx to the index of the container obtained by the sorting
* of the containers using the MACRO GetIpduMTxContainersLst.
* The supplied parameter is expected to be the path of a node
****************************************************************************************************
*/!]
[!MACRO "GetIpduMCntdInCntrIdx", "ContainerPath"!][!NOCODE!]
[!VAR "IpduMCntdInCntrIdx" = "num:i(-1)"!]
[!IF "not(var:defined('IpduMTxContainersLst'))"!]
  [!CALL "GetIpduMTxContainersLst"!]
[!ENDIF!]
[!VAR "entry" = "substring-before(substring-after($IpduMTxContainersLst , concat(';',$ContainerPath,':')) , ';')"!]
[!IF "$entry != ''"!]
  [!VAR "IpduMCntdInCntrIdx" = "num:i($entry)"!]
[!ENDIF!]
[!ENDNOCODE!][!ENDMACRO!]

[!/*
****************************************************************************************************
* MACRO established the IpduM_DateMem slice allocated to ContainerRxPdus
* IpduM_DataMem is made up of 3 chunks, Pathway, ContainerRxPdu and ContainerTxPdu related data.
* The offsets and length are set in the 4 associated variables.
* The values are strings.
****************************************************************************************************
*/!]

[!MACRO "GetDataMemSlices"!][!NOCODE!]
[!IF "not(var:defined(IpduMDataMemPathwaySize))"!][!CALL "GetTxPathwaySize"!][!ENDIF!]
[!IF "not(var:defined(IpduMDataMemRxContainerSize))"!][!CALL "GetRxCntrSize"!][!ENDIF!]
[!IF "not(var:defined(IpduMDataMemTxContainerSize))"!][!CALL "GetTxCntrSize"!][!ENDIF!]
[!ENDNOCODE!][!ENDMACRO!]

[!/*
****************************************************************************************************
* MACRO used to establish the memory requirements for reception.
****************************************************************************************************
*/!]
[!MACRO "GetRxCntrSize"!][!NOCODE!]
[!VAR "IpduMDataMemRxContainerOffset" = "'0U'"!]
[!VAR "IpduMDataMemRxContainerSize" = "'0U'"!]
[!SELECT "as:modconf('IpduM')/IpduMConfig/*[1]"!]
[!IF "$IpduMContainerPduHandlingEnable = 'true'"!]
  [!IF "node:exists(IpduMContainerRxPdu/*)"!]
    [!IF "$NoOfDeferredContainers > num:i(0)"!][!// Processing deferred
      [!CALL "GetBFSizeInUINT32", "numElems"="$NoOfDeferredContainers"!]
      [!VAR "IpduMDeferredListSize" = "$BFSizeU32"!]
      [!IF "$IpduMMultiMF = 'true'"!]
        [!/* Suboptimal allocation, can be reduced once the generator is migrated */!]
        [!VAR "IpduMDeferredListSize" = "num:i($IpduMDeferredListSize * (1 + count(../../IpduMGeneral/IpduMRxProcessing/*)) * 4)"!]
      [!ENDIF!]
      [!VAR "IpduMDataMemRxContainerSize"!](sizeof(uint32)*[!"$IpduMDeferredListSize"!]U)[!ENDVAR!]
      [!IF "not(var:defined('DeferredDataLength'))"!][!CALL "IpduMCalculateRxQueueSlices"!][!ENDIF!]
      [!VAR "IpduMDataMemRxContainerSize"!][!"$IpduMDataMemRxContainerSize"!] + [!"num:i($DeferredDataLength)"!]U[!ENDVAR!]
      [!IF "$IpduMContainerQueuingRxEnable = 'true'"!]
        [!VAR "IpduMDataMemRxContainerSize"!][!"$IpduMDataMemRxContainerSize"!] + (sizeof(IpduM_ContainerQueueType)*[!"$NumIpduMRxQContainers"!]U)[!ENDVAR!]
      [!ENDIF!][!//IpduMContainerQueuingRxEnable
    [!ENDIF!][!// Processing deferred
  [!ENDIF!][!//IpduMContainerRxPdu
[!IF "not(var:defined('IpduMDataMemPathwaySize'))"!][!CALL "GetTxPathwaySize"!][!ENDIF!]
[!VAR "IpduMDataMemRxContainerOffset" = "$IpduMDataMemPathwaySize"!]
[!ENDIF!][!//IpduMContainerPduHandlingEnable
[!ENDSELECT!]
[!ENDNOCODE!][!ENDMACRO!]

[!/*
****************************************************************************************************
* MACRO used to establish the memory requirements for transmission.
****************************************************************************************************
*/!]
[!MACRO "GetTxCntrSize"!][!NOCODE!]
[!SELECT "as:modconf('IpduM')/IpduMConfig/*[1]"!]
[!VAR "IpduMDataMemTxContainerOffset" = "'0U'"!]
[!VAR "IpduMDataMemTxContainerSize" = "'0U'"!]
[!IF "$IpduMContainerPduHandlingEnable = 'true'"!]
  [!VAR "numTxContainers" = "num:i(count(IpduMContainerTxPdu/*))"!]
  [!VAR "LBMaxLen" = "node:refs(node:refs(IpduMContainedTxPdu/*[IpduMContainedTxPduCollectionSemantics='IPDUM_COLLECT_LAST_IS_BEST']/IpduMContainedTxInContainerPduRef)[IpduMContainerTxTriggerMode = 'IPDUM_DIRECT']/IpduMContainerTxPduRef)/PduLength"!]
    [!IF "$LBMaxLen = ''"!]
      [!VAR "LBMaxLen" = "num:i(0)"!]
    [!ELSE!]
      [!CALL "IpduMHelpAlign","valToExtend"="num:max($LBMaxLen)"!]
      [!VAR "LBMaxLen" = "num:i($valPadded)"!]
    [!ENDIF!]
  [!IF "node:exists(./IpduMContainedTxPdu/*)"!]
    [!CALL "IpduMHelpAlign","valToExtend"="sum(node:refs(IpduMContainedTxPdu/*[IpduMContainedTxPduCollectionSemantics = 'IPDUM_COLLECT_LAST_IS_BEST' and node:ref(IpduMContainedTxInContainerPduRef)/IpduMContainerTxTriggerMode = 'IPDUM_DIRECT']/IpduMContainedTxPduRef)/PduLength)"!]
    [!VAR "containedLBLen" = "num:i($valPadded)"!]
  [!ELSE!]
    [!VAR "containedLBLen" = "'0'"!]
  [!ENDIF!]
  [!IF "not(var:defined('QTxSizeCumulator'))"!][!CALL "IpduMCalculateQueueTxSlices"!][!ENDIF!]
  [!VAR "CQCurrDataCumulator" = "num:i(0)"!]
  [!VAR "lstLenCumulator" = "num:i(0)"!]
  [!LOOP "IpduMContainerTxPdu/*"!]
    [!VAR "pduLen" = "num:i(node:value(as:ref(./IpduMContainerTxPduRef)/PduLength))"!]
    [!VAR "cntrQSize" = "num:i(1)"!]
    [!IF "node:exists(IpduMContainerQueueSize) and not(node:empty(./IpduMContainerQueueSize))"!]
      [!VAR "cntrQSize" = "node:value(IpduMContainerQueueSize)"!]
    [!ENDIF!]
    [!CALL "GetIpduMCntrCollectSemantics", "Container" = "node:path(.)"!]
      [!IF "$CollectionSemantics = 'IPDUM_COLLECT_QUEUED'"!]
        [!VAR "CQCurrDataCumulator" = "num:i($CQCurrDataCumulator + $pduLen)"!]
        [!IF "node:value(IpduMContainerHeaderSize) = 'IPDUM_HEADERTYPE_SHORT'"!]
          [!VAR "minSize" = "num:i(5)"!]
        [!ELSE!]
          [!VAR "minSize" = "num:i(9)"!]
        [!ENDIF!]
        [!VAR "lstLenCumulator" = "$lstLenCumulator + num:i((ceiling($pduLen div $minSize) + 1) * ($cntrQSize + 1))"!]
      [!ELSE!]
        [!/* cntrQSize + 1 is used because of normal PDU list length is added to txConfList size*queue size */!]
        [!VAR "lstLenCumulator" = "$lstLenCumulator + num:i((count(node:refs(../../../*/IpduMContainedTxPdu/*[node:path(node:ref(IpduMContainedTxInContainerPduRef)) = node:path(node:current())]/IpduMContainedTxPduRef)) + 1) * ($cntrQSize + 1))"!]
      [!ENDIF!][!//CollectionSemantics
  [!ENDLOOP!]
  [!CALL "IpduMHelpAlign","valToExtend"="$CQCurrDataCumulator"!]
  [!VAR "CQCurrDataCumulator"="$valPadded"!]
  [!VAR "IpduMDataMemTxContainerSize" = "concat('(sizeof(IpduM_CntrTxDataType)*',$numTxContainers,'U) + ',$containedLBLen, 'U + ',$LBMaxLen,'U + (sizeof(uint16)*',num:i($lstLenCumulator),'U) + ',$CQCurrDataCumulator,'U + ',$QTxSizeCumulator,'U + (sizeof(IpduM_ContainerQueueType)*',$NumIpduMQTxContainers,'U)')"!]
[!ENDIF!][!//IpduMContainerPduHandlingEnable
[!ENDSELECT!]

[!IF "not(var:defined('IpduMDataMemRxContainerOffset'))"!][!CALL "GetRxCntrSize"!][!ENDIF!]
[!VAR "IpduMDataMemTxContainerOffset" = "concat($IpduMDataMemRxContainerOffset, ' + ', $IpduMDataMemRxContainerSize)"!]

[!ENDNOCODE!][!ENDMACRO!]

[!/*
****************************************************************************************************
* Create three lists of PDU names and the corresponding handle IDs.
* - SrcPduRefToHandleIdList will hold all source PDU IDs of all PduR routing paths.
* - DestPduRefToHandleIdList will hold all destination PDU IDs of all PduR routing paths.
* - ComPduRefToHandleIdList will hold the ComHandleIds of the ComIpdus(configured to sent normal Ipdus)
*   which references the same global PDU that is referenced by request messages.
* Each list is realized as continuous string. The string contains tuples separated by ";". Each
* tuple contains two elements separated by ":". First element of tuple is the PDU reference. The
* Second element of the tuple is the corresponding handle ID.
* A list, for example, looks like this: Pdu_0:321;Pdu_1:322;Pdu_3:323;
* The location of the PDU AUTOSAR/TOP-LEVEL-PACKAGES/EcuC/ELEMENTS/EcuC/EcucPduCollection/Pdu/ is
* not shown in the example.
****************************************************************************************************
*/!]
[!VAR "SrcPduRefToHandleIdList"="''"!]
[!VAR "DestPduRefToHandleIdList"="''"!]
[!VAR "ComPduRefToHandleIdList"="''"!]
[!// Iterate over all routing paths to collect the source and destination PDU-IDs
[!LOOP "as:modconf('PduR')[1]/PduRRoutingTables/*[1]/PduRRoutingTable/*[1]/PduRRoutingPath/*"!]
    [!// Get the source PDU-ID of a routing path
    [!VAR "SrcHandleId" = "./PduRSrcPdu/PduRSourcePduHandleId"!]
    [!IF "num:isnumber($SrcHandleId) and node:refexists(./PduRSrcPdu/PduRSrcPduRef)"!]
        [!VAR "SrcPduRef" = "node:path(node:ref(./PduRSrcPdu/PduRSrcPduRef))"!]
        [!VAR "SrcPduRefToHandleIdList"!][!"$SrcPduRefToHandleIdList"!];[!"$SrcPduRef"!]:[!"$SrcHandleId"!][!ENDVAR!]
    [!ENDIF!]
    [!// Get the destination PDU-IDs of a routing path
    [!LOOP "./PduRDestPdu/*"!]
        [!IF "node:exists(./PduRDestPduHandleId)"!]
            [!VAR "DestHandleId" = "./PduRDestPduHandleId"!]
            [!IF "num:isnumber($DestHandleId) and node:refexists(./PduRDestPduRef)"!]
                [!VAR "DestPduRef" = "node:path(node:ref(./PduRDestPduRef))"!]
                [!VAR "DestPduRefToHandleIdList"!][!"$DestPduRefToHandleIdList"!];[!"$DestPduRef"!]:[!"$DestHandleId"!][!ENDVAR!]
            [!ENDIF!]
        [!ENDIF!]
    [!ENDLOOP!]
[!ENDLOOP!]

[!LOOP "as:modconf('Com')[1]/ComConfig/*[1]/ComIPdu/*[ComIPduDirection = 'SEND' and ComIPduType = 'NORMAL']"!]
    [!IF "node:exists(./ComIPduHandleId)"!]
            [!VAR "ComHandleId" = "./ComIPduHandleId"!]
            [!IF "num:isnumber($ComHandleId) and node:refexists(./ComPduIdRef)"!]
                [!VAR "ComPduRef" = "node:path(node:ref(./ComPduIdRef))"!]
                [!VAR "ComPduRefToHandleIdList"!][!"$ComPduRefToHandleIdList"!];[!"$ComPduRef"!]:[!"$ComHandleId"!][!ENDVAR!]
            [!ENDIF!]
    [!ENDIF!]
[!ENDLOOP!]

[!/*
****************************************************************************************************
* MACRO to get the ComIPduHandleId with which Com_TriggerIPDUSend() has to be called. The macro parameter
* "IpduMRequestMessagePduRef" must reference this PDU. The PDU-ID is stored in the global variable "PduID".
*
* GetOutputPduId is called to check whether the Pdu referenced by IpduMRequestMessage is
* also referenced by any of the PduRSrcPdu.
****************************************************************************************************
*/!]
[!MACRO "GetComHandleId","IpduMRequestMessagePduRef"!][!NOCODE!]
    [!VAR "IpduMRequestMsgPduRefPath" = "node:path(node:ref($IpduMRequestMessagePduRef))"!]
    [!CALL "GetOutputPduId","IpduMOutgoingPduRef"="$IpduMRequestMessagePduRef"!]
    [!IF "$FoundIds ='true'"!]
      [!VAR "FoundIds" = "false()"!]
      [!LOOP "text:split($ComPduRefToHandleIdList,';')"!]
          [!IF "string(text:split(.,':')[1]) = $IpduMRequestMsgPduRefPath"!]
              [!VAR "PduID" = "text:split(.,':')[2]"!]
              [!VAR "FoundIds" = "true()"!]
          [!ENDIF!]
      [!ENDLOOP!]
      [!IF "$FoundIds = 'false'"!]
          [!ERROR!] The Com module does not reference the PDU '[!"$IpduMRequestMsgPduRefPath"!]' [!ENDERROR!]
      [!ENDIF!]
    [!ENDIF!]
[!ENDNOCODE!][!ENDMACRO!]

[!/*
****************************************************************************************************
* MACRO to get the PduR source PDU ID the PduR has to be called with. The macro parameter
* "IpduMOutgoingPduRef" must reference this PDU. The PDU-ID is stored in the global variable "PduID".
****************************************************************************************************
*/!]
[!MACRO "GetOutputPduId","IpduMOutgoingPduRef"!][!NOCODE!]
    [!VAR "IpduMOutgoingPduRefPath" = "node:path(node:ref($IpduMOutgoingPduRef))"!]
    [!VAR "FoundIds" = "false()"!]
    [!LOOP "text:split($SrcPduRefToHandleIdList,';')"!]
        [!IF "string(text:split(.,':')[1]) = $IpduMOutgoingPduRefPath"!]
            [!VAR "PduID" = "text:split(.,':')[2]"!]
            [!VAR "FoundIds" = "true()"!]
            [!BREAK!]
        [!ENDIF!]
    [!ENDLOOP!]
    [!IF "$FoundIds = 'false'"!]
        [!ERROR!] The PduR does not reference the PDU '[!"node:path(node:ref($IpduMOutgoingPduRef))"!]' [!ENDERROR!]
    [!ENDIF!]
[!ENDNOCODE!][!ENDMACRO!]

[!/*
****************************************************************************************************
* MACRO to get the PduR's destination PDU-ID referenced by global PDU "IpduMPduRef". The PDU-ID is
* stored in the global variable "ResponsePduID". The variable "FoundReponseId" inherently indicate if
* the TxConfirmation is enabled or disabled by the PduR. The macro shall only be applied if the
* considered TxConfirmation of the IpduM is enabled.
****************************************************************************************************
*/!]
[!MACRO "GetResponsePduId","IpduMPduRef"!][!NOCODE!]
    [!VAR "IpduMPduRefPath" = "node:path(node:ref($IpduMPduRef))"!]
    [!VAR "FoundReponseId" = "false()"!]
    [!LOOP "text:split($DestPduRefToHandleIdList,';')"!]
        [!IF "string(text:split(.,':')[1]) = $IpduMPduRefPath"!]
            [!VAR "ResponsePduID" = "text:split(.,':')[2]"!]
            [!VAR "FoundReponseId" = "true()"!]
            [!BREAK!]
        [!ENDIF!]
    [!ENDLOOP!]
    [!IF "$FoundReponseId = 'false'"!]
      /* refs not shared, needed for Symbolic names */
      /* no direct call in order to preserve err msg */
      [!LOOP "text:split($SrcPduRefToHandleIdList,';')"!]
        [!IF "string(text:split(.,':')[1]) = $IpduMPduRefPath"!]
          [!VAR "ResponsePduID" = "text:split(.,':')[2]"!]
          [!VAR "FoundReponseId" = "true()"!]
          [!BREAK!]
        [!ENDIF!]
      [!ENDLOOP!]
        [!IF "$FoundReponseId = 'false'"!]
          [!ERROR!] Either PDU '[!"node:path(node:ref($IpduMPduRef))"!]' is not referenced by the PduR module or associated parameter 'PduRDestPduHandleId' is disabled.[!ENDERROR!]
        [!ENDIF!]
    [!ENDIF!]
[!ENDNOCODE!][!ENDMACRO!]

[!/*
****************************************************************************************************
* MACRO to get the string for the symbolic name value. Sets variable "SymbolName" holding either the
* short name of the referenced container or (if not available) the provided "Oldname".
* "ShortNameRef" must reference the container holding the short name. (AUTOSAR short name)
* "OldName" must hold a unique string for the case that the specification
* conform short name does not exist. This is supplied to be backward compatible.
****************************************************************************************************
*/!]
[!MACRO "GetSymbolName","ShortNameRef","OldName"!][!NOCODE!]
  [!VAR "SymbolName" = "asc:getShortName($ShortNameRef)"!]
    [!IF "$SymbolName = ''"!]
      [!VAR "SymbolName" = "$OldName"!]
    [!ENDIF!]
[!ENDNOCODE!][!ENDMACRO!]

[!/*
****************************************************************************************************
* MACRO to generate all symbolic name values for an ID
****************************************************************************************************
*/!]
[!MACRO "GenSymbols","SymbolicPrefix","SymbolicName","SymbolicIdName","SymbolicValue","PduName"!][!/*
*/!]/*------------------------------------------------------------------------------------------------*/
/* [!"node:path($SymbolicValue)"!] */
#if (defined [!"$SymbolicPrefix"!][!"$SymbolicName"!])
#error [!"$SymbolicPrefix"!][!"$SymbolicName"!] is already defined
#endif
/** \brief Export symbolic name value for [!"$SymbolicIdName"!] */
#define [!"$SymbolicPrefix"!][!"$SymbolicName"!] [!"node:value($SymbolicValue)"!]U /* [!"$PduName"!] */

#if (defined IPDUM_PROVIDE_LEGACY_SYMBOLIC_NAMES)
#if (defined IpduM_[!"$SymbolicName"!])
#error IpduM_[!"$SymbolicName"!] is already defined
#endif
/** \brief Export symbolic name value with module abbreviation as prefix only (AUTOSAR version <= AUTOSAR 4.0 rev2) */
#define IpduM_[!"$SymbolicName"!] [!"node:value($SymbolicValue)"!]U
#endif /* defined IPDUM_PROVIDE_LEGACY_SYMBOLIC_NAMES */[!//
[!ENDMACRO!]

[!/*
****************************************************************************************************
* MACRO to generate a single symbolic name value for an ID
****************************************************************************************************
*/!]
[!MACRO "GenSymbol","SymbolicPrefix","SymbolicName","SymbolicIdName","SymbolicValue","PduName"!][!/*
*/!]/*------------------------------------------------------------------------------------------------*/
/* [!"node:path($SymbolicValue)"!] */
#if (defined [!"$SymbolicPrefix"!][!"$SymbolicName"!])
#error [!"$SymbolicPrefix"!][!"$SymbolicName"!] is already defined
#endif
/** \brief Export symbolic name value for [!"$SymbolicIdName"!] */
#define [!"$SymbolicPrefix"!][!"$SymbolicName"!] [!"node:value($SymbolicValue)"!]U /* [!"$PduName"!] */
[!ENDMACRO!]

[!/*
****************************************************************************************************
* MACRO to convert Timeouts values to MainFunctionTx cycles. Value is rounded down
* Instead of string matching workaround two parameters are used,
* nodePath is the path to the container, while
* valPathNode is the path to the value.
* NOTE: valPathNode isn't relative to nodePath because of the SendTimeouts
* NOTE2: nodePath is expected to be a SHORT-NAME-path
****************************************************************************************************
*/!]
[!MACRO "TxTimeoutToMFC","nodePath","valPathNode","asPathChildrenWorkaround"="1"!][!NOCODE!]
[!IF "$IpduMMultiMF = 'true'"!]
  [!IF "not(var:defined('mfTXalloc'))"!][!CALL "createTXMFAlloc"!][!ENDIF!]
  [!LOOP "text:split($mfTXalloc, ';')"!]
    [!IF "contains(text:split(.,'#')[4], $nodePath)"!]
      [!VAR "txTBase" = "text:split(.,'#')[5]"!]
      [!BREAK!]
    [!ENDIF!]
  [!ENDLOOP!]
[!ELSE!]
  [!VAR "txTBase" = "as:modconf('IpduM')[1]/IpduMGeneral/IpduMTxTimeBase"!]
[!ENDIF!]
[!/* as:ref() workaround, it doesn't resolve IpduMTxRequest for ex */!]
[!VAR "Children" = "''"!]
[!FOR "k" = "0" TO "$asPathChildrenWorkaround - 1"!]
  [!IF "$k = 0"!]
    [!VAR "pathSep"="''"!]
  [!ELSE!]
    [!VAR "pathSep"="'/'"!]
  [!ENDIF!]
  [!VAR "Children" = "concat(text:split($valPathNode,'/')[last() - $k],$pathSep,$Children)"!]
[!ENDFOR!]
[!/* There would be no need for this if as:value would exist */!]
[!VAR "Parents" = "substring-before($valPathNode, $Children)"!]
[!/* When obtaining  */!]
[!VAR "shortNameToXPath" = "concat(node:path(as:ref($Parents)),'/',$Children)"!]
[!VAR "mVal" = "node:value($shortNameToXPath) div $txTBase"!]
[!IF "text:match(string($mVal),'\d+\.9{15}')"!]
  [!VAR "mVal" = "num:i(ceiling($mVal))"!]
[!ENDIF!]
[!VAR "exponent" = "0"!]
[!IF "num:i($mVal) != $mVal"!]
  [!VAR "exponent" = "string-length(substring-after(string($mVal), '.'))"!]
[!ENDIF!]
[!FOR "i" = "1" TO "$exponent"!]
  [!VAR "mVal" = "$mVal * 10"!]
[!ENDFOR!]
[!VAR "mVal" = "num:i($mVal)"!]
[!ENDNOCODE!][!ENDMACRO!]

[!/*
****************************************************************************************************
* MACRO to get the TxSendTimeout, this being that of the Container or the Contained, depending
* which is lesser.
* The parameter is expected to be that of type "IpduMContainedTxPdu"
****************************************************************************************************
*/!]
[!MACRO "GetMinTxSendTimeout", "ValPath1"!][!NOCODE!]
[!VAR "TxSContainedTimeout" = "num:i(0)"!]
[!VAR "TxSTimeoutContainer" = "num:i(0)"!]
[!VAR "assocCntrPath" = "as:path(as:ref(as:ref($ValPath1)/IpduMContainedTxInContainerPduRef))"!]
[!IF "node:exists(as:ref($ValPath1)/IpduMContainedTxPduSendTimeout)"!]
  [!CALL "TxTimeoutToMFC", "nodePath"="$assocCntrPath", "valPathNode"="concat($ValPath1, '/IpduMContainedTxPduSendTimeout')"!]
  [!VAR "TxSContainedTimeout" = "$mVal"!]
[!ENDIF!]
[!IF "node:exists(as:ref($assocCntrPath)/IpduMContainerTxSendTimeout)"!]
  [!CALL "TxTimeoutToMFC", "nodePath"="$assocCntrPath", "valPathNode"="concat($assocCntrPath, '/IpduMContainerTxSendTimeout')"!]
  [!VAR "TxSTimeoutContainer" = "$mVal"!]
[!ENDIF!]
[!IF "$TxSContainedTimeout = 0"!]
  [!VAR "MinTxSendTimeout" = "$TxSTimeoutContainer"!]
[!ELSEIF "$TxSTimeoutContainer = 0"!]
  [!VAR "MinTxSendTimeout" = "$TxSContainedTimeout"!]
[!ELSE!]
  [!IF "$TxSTimeoutContainer < $TxSContainedTimeout"!]
    [!VAR "MinTxSendTimeout" = "$TxSTimeoutContainer"!]
  [!ELSE!]
    [!VAR "MinTxSendTimeout" = "$TxSContainedTimeout"!]
  [!ENDIF!]
[!ENDIF!]
[!ENDNOCODE!][!ENDMACRO!]

[!/*
****************************************************************************************************
* Macro creates a string-map of container-MainFunctionRx allocation.
* Attributes are separeted by pound sign(#), attribute list elements by pipe (|) and entries by semicolon (;).
* Unallocated containers are at the end.
****************************************************************************************************
*/!]
[!MACRO "createRXMFAlloc"!][!NOCODE!]
[!IF "not(var:defined('mfRXalloc'))"!]
[!VAR "mfRXalloc" = "''"!]
[!VAR "mfRXalloc"!][!"$mfRXalloc"!];[!"num:i(0)"!]# #IpduM_MainFunctionRx#[!"text:join(text:difference(as:paths(as:modconf('IpduM')[1]/IpduMConfig/*[1]/IpduMContainerRxPdu/*[IpduMContainerPduProcessing='IPDUM_PROCESSING_DEFERRED']), as:paths(node:refs(as:modconf('IpduM')[1]/IpduMGeneral/IpduMRxProcessing/*/IpduMRxPduRef/*))),'|')"!][!ENDVAR!]
[!LOOP "as:modconf('IpduM')[1]/IpduMGeneral/IpduMRxProcessing/*"!]
  [!VAR "pos" = "num:i(node:pos(.) + 1)"!]
  [!VAR "mfRXalloc"!][!"$mfRXalloc"!];[!"$pos"!]#[!"node:name(.)"!]#IpduM_MainFunctionRx_[!"node:name(.)"!]#[!"text:join(./IpduMRxPduRef/*,'|')"!][!ENDVAR!]
[!ENDLOOP!]
[!ENDIF!][!//var:defined()
[!ENDNOCODE!][!ENDMACRO!]
[!/*
****************************************************************************************************
* Macro creates a string-map of pathway-container-MainFunctionTX allocation.
* Attributes are separeted by pound sign(#), attribute list elements by pipe (|) and entries by semicolon (;).
* Unallocated containers are at the end.
****************************************************************************************************
*/!]
[!MACRO "createTXMFAlloc"!][!NOCODE!]
[!IF "not(var:defined('mfTXalloc'))"!]
[!VAR "mfTXalloc" = "''"!]
[!VAR "mfTXalloc"!][!"$mfTXalloc"!];[!"num:i(0)"!]# #IpduM_MainFunctionTx#[!"concat(text:join(text:difference(as:paths(as:modconf('IpduM')[1]/IpduMConfig/*[1]/IpduMTxPathway/*), as:paths(node:refs(as:modconf('IpduM')[1]/IpduMGeneral/IpduMTxProcessing/*/IpduMTxPduRef/*))),'|'),'|',text:join(text:difference(as:paths(as:modconf('IpduM')[1]/IpduMConfig/*[1]/IpduMContainerTxPdu/*), as:paths(node:refs(as:modconf('IpduM')[1]/IpduMGeneral/IpduMTxProcessing/*/IpduMTxPduRef/*))),'|'))"!]#[!"as:modconf('IpduM')[1]/IpduMGeneral/IpduMTxTimeBase"!][!ENDVAR!]
[!LOOP "as:modconf('IpduM')[1]/IpduMGeneral/IpduMTxProcessing/*"!]
  [!VAR "pos" = "num:i(node:pos(.) + 1)"!]
  [!VAR "mfTXalloc"!][!"$mfTXalloc"!];[!"$pos"!]#[!"node:name(.)"!]#IpduM_MainFunctionTx_[!"node:name(.)"!]#[!"text:replaceAll(text:join(./IpduMTxPduRef/*,'|'),'ASPath\:','')"!]#[!"./IpduMTimeBase"!][!ENDVAR!]
[!ENDLOOP!]
[!ENDIF!][!//var:defined()
[!ENDNOCODE!][!ENDMACRO!]
[!/*
****************************************************************************************************
* MACRO provides the ID/idx suitable to be used for the split MainFunctions
* The idx is stored in "MFProcRefID"
****************************************************************************************************
*/!]
[!MACRO "GetProcessingRefID","refPath","Direction"!][!NOCODE!]
[!IF "not(var:defined('numPathways'))"!]
  [!VAR "numPathways" = "num:i(count(as:modconf('IpduM')/IpduMConfig/*[1]/IpduMTxPathway/*))"!]
[!ENDIF!]
[!IF "$Direction = 'TX'"!]
[!// Check if it's a Pathway, don't split the string unnecessarily
  [!IF "node:exists(as:ref($refPath)/IpduMTxRequest/IpduMTxConfirmationPduId)"!]
    [!VAR "MFProcRefID" = "num:i(node:value(as:ref($refPath)/IpduMTxRequest/IpduMTxConfirmationPduId))"!]
  [!ELSE!][!//It's a Container
    [!IF "not(var:defined('IpduMTxContainersLst'))"!][!CALL "GetIpduMTxContainersLst"!][!ENDIF!]
    [!LOOP "text:split($IpduMTxContainersLst,';')"!]
      [!IF "text:split(.,':')[1] = $refPath"!]
        [!VAR "MFProcRefID" = "num:i(text:split(.,':')[2] + $numPathways)"!]
        [!BREAK!]
      [!ENDIF!]
    [!ENDLOOP!]
  [!ENDIF!]
[!ELSE!][!//RX
  [!VAR "MFProcRefID" = "num:i(node:value(as:ref($refPath)/IpduMContainerRxHandleId))"!]
[!ENDIF!]
[!ENDNOCODE!][!ENDMACRO!]
[!/*
****************************************************************************************************
* Macro creates section / segment strings for memory mapping
* Results are in "secSTART", "secSTOP", "segCODE".
****************************************************************************************************
*/!]
[!MACRO "createSegmentStr","shortName"!][!NOCODE!]
[!IF "not(var:defined('mipStr'))"!]
  [!//maybe at some point join would work with varargs as well
  [!VAR "mipStr" = "'IPDUM'"!]
  [!VAR "startStr" = "'START'"!]
  [!VAR "stopStr" = "'STOP'"!]
  [!VAR "sectionStr" = "'SEC'"!]
  [!VAR "segmentStr" = "'CODE'"!]
  [!VAR "scope" = "'LOCAL'"!]
  [!VAR "delimiter" = "'_'"!]
[!ENDIF!]
[!/*
[!IF "$shortName = ' '"!][!//single empty space because of tokenization
*/!]
  [!VAR "secSTART" = "concat($mipStr, $delimiter, $startStr, $delimiter, $sectionStr, $delimiter, $segmentStr)"!]
  [!VAR "secSTOP" = "concat($mipStr, $delimiter, $stopStr, $delimiter, $sectionStr, $delimiter, $segmentStr)"!]
  [!VAR "segCODE" = "concat($mipStr, $delimiter, $segmentStr)"!]
[!/*
[!ELSE!]
  [!VAR "secSTART" = "concat($mipStr, $delimiter, text:toupper($shortName), $delimiter, $startStr, $delimiter, $sectionStr, $delimiter, $segmentStr, $delimiter, $scope)"!]
  [!VAR "secSTOP" = "concat($mipStr, $delimiter, text:toupper($shortName), $delimiter, $stopStr, $delimiter, $sectionStr, $delimiter, $segmentStr, $delimiter, $scope)"!]
  [!VAR "segCODE" = "concat($mipStr, $delimiter, text:toupper($shortName), $delimiter, $segmentStr)"!]
[!ENDIF!]
*/!]
[!ENDNOCODE!][!ENDMACRO!]
[!/*
****************************************************************************************************
* MACRO used to get internal RxIndication handles function index.
* Note: Needs to be in sync with IpduM.c.m4.
****************************************************************************************************
*/!]
[!MACRO "IpduMGetRxIndHandlerFuncIdx","cfgItemPath"!][!NOCODE!]
  [!IF "contains($cfgItemPath, 'IpduMRxPathway')"!]
    [!VAR "IpduMRxIndHandlerFuncIdx" = "num:i(0)"!]
  [!ELSE!]
    [!SELECT "node:ref($cfgItemPath)"!]
      [!IF "./IpduMContainerPduProcessing = 'IPDUM_PROCESSING_IMMEDIATE'"!]
        [!VAR "IpduMRxIndHandlerFuncIdx" = "num:i(1)"!]
      [!ELSE!]
        [!VAR "IpduMRxIndHandlerFuncIdx" = "num:i(2)"!]
      [!ENDIF!]
    [!ENDSELECT!]
  [!ENDIF!]
[!ENDNOCODE!][!ENDMACRO!]
[!/*
****************************************************************************************************
* Calculates the offsets into IpduM_GDataMemPtr (byte offsets, not uint32)
****************************************************************************************************
*/!]
[!MACRO "GetBuffSliceIdx", "Direction", "ContainerIdx"!][!NOCODE!]
[!VAR "BuffSliceIdx" = "num:i(-1)"!]
[!VAR "BuffQIdx" = "num:i(-1)"!]
[!IF "$Direction = 'TX'"!]
  [!IF "not(var:defined('IpduMDataMemTxContainerOffset'))"!][!CALL "GetTxCntrSize"!][!ENDIF!]
  [!VAR "lst" = "string($IpduMQTxSlicesLst)"!]
  [!VAR "baseOfs" = "concat('(IpduM_DataOffsetType)(',$IpduMDataMemTxContainerOffset,' + (sizeof(IpduM_CntrTxDataType)*',$numTxContainers,'U) + ',$containedLBLen,'U + ',$LBMaxLen,'U + (sizeof(uint16)*',num:i($lstLenCumulator),'U) + ',$CQCurrDataCumulator,'U')"!]
  [!VAR "varData" = "$QTxSizeCumulator"!]
  [!VAR "bsi_prefix" = "concat($baseOfs,' + ')"!]
  [!VAR "bsi_postfix" = "'U)'"!]
[!ELSE!]
  [!IF "not(var:defined('IpduMDataMemRxContainerSize'))"!][!CALL "GetRxCntrSize"!][!ENDIF!]
  [!VAR "lst" = "string($IpduMRxQSlicesLst)"!]
  [!VAR "baseOfs" = "$buffIdxBaseRx"!]
  [!VAR "varData" = "$DeferredDataLength"!]
  [!VAR "bsi_prefix" = "''"!]
  [!VAR "bsi_postfix" = "''"!]
[!ENDIF!]
[!VAR "QSPos" = "substring-before(substring-after($lst , concat(';',$ContainerIdx,':')) , ';')"!]
[!IF "$QSPos != ''"!]
  [!VAR "BuffSliceIdx" = "concat($bsi_prefix,text:split($QSPos,':')[1],$bsi_postfix)"!]
  [!VAR "qbuffVal" = "num:i(text:split($QSPos,':')[2])"!]
  [!VAR "BuffQIdx" = "concat($baseOfs,' + ',$varData,'U + (sizeof(IpduM_ContainerQueueType)*',$qbuffVal,'U))')"!]
[!ENDIF!]
[!ENDNOCODE!][!ENDMACRO!]
[!/*
****************************************************************************************************
* Calculates the offsets into IpduM_GDataMemPtr used for storing assembled Container PDUs
* Note: The order in which the macro is called matters as an offset cumulator variable is used.
* The return value is stored in "CntrTmpDSOfs".
****************************************************************************************************
*/!]
[!MACRO "GetTempDataStoreOffset", "ContainerPath"!][!NOCODE!]
[!IF "not(var:defined('LBMaxLen'))"!][!CALL "GetTxCntrSize"!][!ENDIF!]
[!IF "not(var:defined('tdsOfsCQ'))"!]
[!/* It's either 0 or length of buffer allocated for LB, needs to be initialized only once */!]
  [!VAR "tdsOfsCQ" = "$LBMaxLen"!]
  [!VAR "CQofs" = "num:i(0)"!]
[!ENDIF!]
[!IF "not(var:defined('tdsOfs'))"!]
  [!IF "not(var:defined('IpduMDataMemTxContainerOffset'))"!][!CALL "GetTxCntrSize"!][!ENDIF!]
  [!VAR "tdsOfs" = "concat('(IpduM_DataOffsetType)(',$IpduMDataMemTxContainerOffset,' + (sizeof(IpduM_CntrTxDataType)*',$numTxContainers,'U) + ',$containedLBLen,'U')"!]
[!ENDIF!]
[!CALL "GetIpduMCntrCollectSemantics", "Container" = "node:path(.)"!]
[!IF "$CollectionSemantics = 'IPDUM_COLLECT_LAST_IS_BEST'"!]
  [!VAR "CntrTmpDSOfs" = "concat($tdsOfs,')')"!]
[!ELSE!]
  [!VAR "CntrTmpDSOfs" = "concat($tdsOfs,' + ', $tdsOfsCQ, 'U + (sizeof(uint16)*',num:i($lstLenCumulator),'U) + ',$CQofs,'U)')"!]
  [!VAR "CQofs" = "num:i($CQofs + node:value(node:ref(node:ref($ContainerPath)/IpduMContainerTxPduRef)/PduLength))"!]
[!ENDIF!]
[!ENDNOCODE!][!ENDMACRO!]

[!/*
****************************************************************************************************
* Calculates the offsets into IpduM_GDataMemPtr used for storing Contained PDUs awaiting assembly.
* Only the ones with collection semantics IPDUM_COLLECT_LAST_IS_BEST and associated to a Container
* with IpduMContainerTxTriggerMode configured as IPDUM_DIRECT are considered.
* Note: The order in which the macro is called matters as an offset cumulator variable is used.
* The return value is stored in "cntdBuffOffset".
****************************************************************************************************
*/!]
[!MACRO "GetContainedBuffOffset", "CntdPath"!][!NOCODE!]
[!IF "not(var:defined('cntdBO'))"!]
  [!IF "not(var:defined('IpduMDataMemTxContainerOffset'))"!][!CALL "GetTxCntrSize"!][!ENDIF!]
  [!VAR "cntdBO" = "concat('(IpduM_DataOffsetType)(',$IpduMDataMemTxContainerOffset,' + (sizeof(IpduM_CntrTxDataType)*',$numTxContainers,'U) + ')"!]
  [!VAR "cntdOCumulator" = "num:i(0)"!]
[!ENDIF!]
[!IF "node:ref($CntdPath)/IpduMContainedTxPduCollectionSemantics = 'IPDUM_COLLECT_LAST_IS_BEST' and node:ref(node:ref($CntdPath)/IpduMContainedTxInContainerPduRef)/IpduMContainerTxTriggerMode = 'IPDUM_DIRECT'"!]
  [!VAR "cntdBuffOffset" = "concat($cntdBO,$cntdOCumulator,'U)')"!]
  [!VAR "cntdOCumulator" = "num:i($cntdOCumulator + node:ref(node:ref($CntdPath)/IpduMContainedTxPduRef)/PduLength)"!]
[!ELSE!]
  [!VAR "cntdBuffOffset" = "'0U'"!]
[!ENDIF!]
[!ENDNOCODE!][!ENDMACRO!]
[!/*
****************************************************************************************************
* Calculates the offsets into IpduM_GDataMemPtr used for storing the list of IDs of Contained PDUs
* Two offsets are returned, one for the list of IDs and a second one for the list storing the IDs
* awaiting confirmation.
* Note: As helper variables are used, the order in which the macro gets called is significant (retains state)
* Results are "returned" in "cplOfs" and "ccplOfs".
****************************************************************************************************
*/!]
[!MACRO "GetPduListOffset", "ContainerPath"!][!NOCODE!]
[!IF "not(var:defined('LBMaxLen'))"!][!CALL "GetTxCntrSize"!][!ENDIF!]
[!IF "not(var:defined('lOfs'))"!]
  [!VAR "lOfs" = "concat('(IpduM_DataOffsetType)(',$IpduMDataMemTxContainerOffset,' + (sizeof(IpduM_CntrTxDataType)*',$numTxContainers,'U) + ',$containedLBLen, 'U + ', $LBMaxLen, 'U + (sizeof(uint16)*')"!]
  [!VAR "cplOfs" = "num:i(0)"!][!// Offset for the pdu list
  [!VAR "ccplOfs" = "num:i(0)"!][!// Offset for the confirmation list
  [!VAR "sCounter" = "num:i(0)"!]
[!ENDIF!]
[!VAR "qS" = "num:i(1)"!]
[!IF "node:exists(node:ref($ContainerPath)/IpduMContainerQueueSize)"!]
  [!VAR "qS" = "num:i(node:value(node:ref($ContainerPath)/IpduMContainerQueueSize))"!]
[!ENDIF!]
[!CALL "GetIpduMCntrCollectSemantics", "Container" = "$ContainerPath"!]
[!IF "$CollectionSemantics = 'IPDUM_COLLECT_QUEUED'"!]
  [!VAR "pl" = "num:i(node:value(node:ref(node:ref($ContainerPath)/IpduMContainerTxPduRef)/PduLength))"!]
  [!IF "node:value(node:ref($ContainerPath)/IpduMContainerHeaderSize) = 'IPDUM_HEADERTYPE_SHORT'"!]
    [!VAR "minSize" = "num:i(5)"!]
  [!ELSE!]
    [!VAR "minSize" = "num:i(9)"!]
  [!ENDIF!]
  [!VAR "sz" = "num:i(ceiling($pl div $minSize) + 1)"!]
[!ELSE!]
  [!VAR "sz" = "num:i(count(node:refs(as:modconf('IpduM')[1]/IpduMConfig/*[1]/IpduMContainedTxPdu/*[node:path(node:ref(IpduMContainedTxInContainerPduRef)) = $ContainerPath]/IpduMContainedTxPduRef))+1)"!]
[!ENDIF!][!//CollectionSemantics
[!VAR "cplOfs" = "concat($lOfs, $sCounter,'U))')"!]
[!VAR "ccplOfs" = "concat($lOfs, num:i($sCounter + $sz),'U))')"!]
[!VAR "sCounter" = "num:i($sCounter + ($sz * ($qS + 1)))"!]
[!ENDNOCODE!][!ENDMACRO!]


[!ENDIF!][!// multiple inclusion protection
[!ENDNOCODE!][!//