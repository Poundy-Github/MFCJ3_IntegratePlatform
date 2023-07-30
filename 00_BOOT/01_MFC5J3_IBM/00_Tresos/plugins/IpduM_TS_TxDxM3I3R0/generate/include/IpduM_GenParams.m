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
[!NOCODE!]
[!IF "not(var:defined('IPDUM_GENPARAMS_M'))"!]
[!VAR "IPDUM_GENPARAMS_M"="'true'"!]

[!// Avoid executing the validator just because of these
****************************************************************************
* Get all the general parameters in variables.
****************************************************************************
*/!][!//
[!SELECT "as:modconf('IpduM')[1]/IpduMGeneral"!][!//
[!VAR "IpduMRxTimeBase" = "node:value(./IpduMRxTimeBase)"!][!//
[!VAR "IpduMTxTimeBase" = "node:value(./IpduMTxTimeBase)"!][!//
[!VAR "IpduMDevErrorDetect" = "node:value(./IpduMDevErrorDetect)"!][!//
[!VAR "IpduMStaticPartExists" = "node:value(./IpduMStaticPartExists)"!][!//
[!VAR "IpduMVersionInfoApi" = "node:value(./IpduMVersionInfoApi)"!][!//
[!VAR "IpduMZeroCopy" = "node:value(./IpduMZeroCopy)"!][!//
[!VAR "IpduMByteCopy" = "node:value(./IpduMByteCopy)"!][!//
[!VAR "IpduMDynamicPartQueue" = "node:value(./IpduMDynamicPartQueue)"!][!//
[!VAR "IpduMTxAutomaticSelector" = "node:value(./IpduMTxAutomaticSelector)"!][!//
[!VAR "IpduMInitializationBySignalValue" = "node:value(./IpduMInitializationBySignalValue)"!][!//
[!VAR "IpduMEnableJitUpdate" = "node:value(./IpduMEnableJitUpdate)"!][!//
[!VAR "IpduMContainerPduHandlingEnable" = "node:value(./IpduMContainerPduHandlingEnable)"!][!//
[!VAR "IpduMContainerQueuingRxEnable" = "./IpduMContainerQueuingRx = 'true'"!][!//
[!VAR "IpduMContainerQueuingTxEnable" = "./IpduMContainerQueuingTx = 'true'"!][!//
[!VAR "IpduMContainedCollectQueuedTxEnable" = "./IpduMContainedCollectQueuedTx = 'true'"!][!//
[!VAR "IpduMStaticContainerPduHandlingEnable" = "./IpduMStaticContainerPduHandling = 'true'"!][!//
[!VAR "MaxContainerTxPduLength" = "num:i(0)"!][!//
[!VAR "MaxContainerRxPduLength" = "num:i(0)"!][!//
[!VAR "IpduMMultiMF" = "./IpduMDedicatedIpduProcessingSupport = 'true'"!][!//
[!VAR "IpduMContainedTxPduPriorityHandlingEnable" = "./IpduMContainedTxPduPriorityHandling = 'true'"!][!//
[!IF "$IpduMContainerPduHandlingEnable = 'true'"!][!//
  [!VAR "MaxContainerRxPduLength" = "num:i(./IpduMMaxContainerRxLength)"!][!//
  [!VAR "MaxContainerTxPduLength" = "num:i(./IpduMMaxContainerTxLength)"!][!//
[!ENDIF!][!//
[!ENDSELECT!][!//
[!// Not a general parameter, still needed
[!VAR "NumIpduMQTxContainers" = "num:i(count(as:modconf('IpduM')/IpduMConfig/*[1]/IpduMContainerTxPdu/*[node:exists(IpduMContainerQueueSize)]))"!][!//
[!VAR "NumIpduMRxQContainers" = "num:i(count(as:modconf('IpduM')/IpduMConfig/*[1]/IpduMContainerRxPdu/*[node:exists(IpduMContainerQueueSize)]))"!][!//
[!VAR "NoOfDeferredContainers" ="num:i(count(as:modconf('IpduM')/IpduMConfig/*[1]/IpduMContainerRxPdu/*[IpduMContainerPduProcessing = 'IPDUM_PROCESSING_DEFERRED']))"!][!//

[!ENDIF!][!// multiple inclusion protection
[!ENDNOCODE!][!//