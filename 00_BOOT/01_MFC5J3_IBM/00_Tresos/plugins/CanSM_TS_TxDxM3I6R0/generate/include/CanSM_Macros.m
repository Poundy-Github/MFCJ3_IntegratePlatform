[!/**
 * \file
 *
 * \brief AUTOSAR CanSM
 *
 * This file contains the implementation of the AUTOSAR
 * module CanSM.
 *
 * \author Elektrobit Automotive GmbH, 91058 Erlangen, Germany
 *
 * Copyright 2005 - 2019 Elektrobit Automotive GmbH
 * All rights exclusively reserved for Elektrobit Automotive GmbH,
 * unless expressly agreed to otherwise.
 */!][!//
[!NOCODE!]
[!IF "not(var:defined('CANSM_MACROS_M'))"!]
[!VAR "CANSM_MACROS_M"="'true'"!]

[!VAR "numNetworks"="num:i(count(CanSMConfiguration/*[1]/CanSMManagerNetwork/*))"!]
[!VAR "numControllers"="num:i(count(CanSMConfiguration/*[1]/CanSMManagerNetwork/*/CanSMController/*))"!]
[!VAR "singleControllers"="$numNetworks = count(CanSMConfiguration/*[1]/CanSMManagerNetwork/*[count(CanSMController/*) = 1])"!]
[!VAR "numTransceivers"="num:i(count(CanSMConfiguration/*[1]/CanSMManagerNetwork/*/CanSMTransceiverId))"!]
[!VAR "useTransceiver"="$numTransceivers > 0"!]
[!VAR "useDEM"="as:modconf('CanSM')[1]/ReportToDem/CanSMBusOffReportToDem = 'DEM'"!]

[!/* some resources needs to be available in code if PnSupport or(!!) transceiver are enabled  */!]
[!VAR "globalPnSupport"="as:modconf('CanSM')[1]/CanSMGeneral/CanSMPNSupport"!]
[!VAR "multiCoreSupport"="as:modconf('CanSM')[1]/CanSMGeneral/CanSMMultiCoreSupport"!]

[!/* maximum controller id */!]
[!VAR "ctrlMax"="0"!]
[!LOOP "CanSMConfiguration/*[1]/CanSMManagerNetwork/*/CanSMController/*/CanSMControllerId"!]
  [!IF "as:ref(.)/CanIfCtrlId > $ctrlMax"!]
    [!VAR "ctrlMax"="as:ref(.)/CanIfCtrlId"!]
  [!ENDIF!]
[!ENDLOOP!]

[!/* maximum transceiver id */!]
[!VAR "trcvMax"="0"!]
[!LOOP "CanSMConfiguration/*[1]/CanSMManagerNetwork/*/CanSMTransceiverId"!]
  [!IF "node:refvalid(.) and (as:ref(.)/CanIfTrcvId > $trcvMax)"!]
    [!VAR "trcvMax"="as:ref(.)/CanIfTrcvId"!]
  [!ENDIF!]
[!ENDLOOP!]

[!IF "$numNetworks > 1"!]
  [!/* check if network handles are consecutive */!]
  [!VAR "networkHandles"="''"!]
  [!LOOP "node:order(CanSMConfiguration/*[1]/CanSMManagerNetwork/*,'as:ref(CanSMComMNetworkHandleRef)/ComMChannelId')"!]
    [!VAR "networkHandles"="concat($networkHandles,' ',num:i(as:ref(CanSMComMNetworkHandleRef)/ComMChannelId))"!]
  [!ENDLOOP!]
  [!/* snip leading space */!]
  [!VAR "networkHandles"="substring($networkHandles,2)"!]
  [!/* now check */!]
  [!VAR "nwHandlesConsecutive"="'true'"!]
  [!VAR "x"="text:split($networkHandles)[1]"!]
  [!VAR "nwHandleOffset"="$x"!]
  [!LOOP "text:split($networkHandles)[position()>1]"!]
    [!IF ". != ($x + 1)"!]
      [!VAR "nwHandlesConsecutive"="'false'"!]
    [!ENDIF!]
    [!VAR "x"="num:i(.)"!]
  [!ENDLOOP!]
[!ENDIF!]

[!/* network index lookup table; Format: (index:path to CanSMManagerNetwork;)+ */!]
[!VAR "nwIdxLut"="''"!]
[!VAR "idx"="0"!]
[!LOOP "node:order(CanSMConfiguration/*[1]/CanSMManagerNetwork/*,'as:ref(CanSMComMNetworkHandleRef)/ComMChannelId')"!]
  [!VAR "nwIdxLut"="concat($nwIdxLut,num:i($idx),':',as:path(.),';')"!]
  [!VAR "idx"="$idx + 1"!]
[!ENDLOOP!]

[!/*
*** macros generate line breaks when expanded, so use comment-indentation here ***
*/!][!MACRO "CalcToTicks", "time", "maxTicks"!][!/*
*** results are limited to <= maxTicks, which is only necessary in case of rounding errors, ***
*** because ranges of interacting parameters are appropriately limited ***
   */!][!VAR "macroTicks"="num:i(ceiling($time div as:modconf('CanSM')[1]/CanSMGeneral/CanSMMainFunctionTimePeriod))"!][!/*
   */!][!IF "$macroTicks > num:i($maxTicks)"!][!/*
   */!][!"$maxTicks"!][!/*
   */!][!ELSE!][!/*
   */!][!"$macroTicks"!][!/*
   */!][!ENDIF!][!/*
*/!][!ENDMACRO!][!/*
*/!][!MACRO "getNwIdxByNwRef", "nwRef"!][!/*
   */!][!"substring-before(text:grep(text:split($nwIdxLut,';'), concat('.*:', $nwRef, '$'))[1], ':')"!][!/*
   */!][!ENDMACRO!][!/*
*/!]


[!/* use macro for BOR timing/counter params if they are equal for all networks */!]
[!VAR "nwSpecificBorTimeL1"="string(count(CanSMConfiguration/*[1]/CanSMManagerNetwork/*[CanSMBorTimeL1 != ../*[1]/CanSMBorTimeL1]) != 0)"!]
[!VAR "nwSpecificBorTimeL2"="string(count(CanSMConfiguration/*[1]/CanSMManagerNetwork/*[CanSMBorTimeL2 != ../*[1]/CanSMBorTimeL2]) != 0)"!]
[!VAR "nwSpecificBorCounterL1ToL2"="string(count(CanSMConfiguration/*[1]/CanSMManagerNetwork/*[CanSMBorCounterL1ToL2 != ../*[1]/CanSMBorCounterL1ToL2]) != 0)"!]
[!/* only compare networks which do not use Tx confirmation polling */!]
[!VAR "nwSpecificBorTimeTxEnsured"="string(count(CanSMConfiguration/*[1]/CanSMManagerNetwork/*[(CanSMBorTxConfirmationPolling = 'false') and (CanSMBorTimeTxEnsured != num:max(../*[CanSMBorTxConfirmationPolling = 'false']/CanSMBorTimeTxEnsured))]) != 0)"!]

[!VAR "useBorTimeTxEnsured"="string(count(CanSMConfiguration/*[1]/CanSMManagerNetwork/*[CanSMBorTxConfirmationPolling = 'false']) > 0)"!]
[!VAR "nwSpecificBorTxConfirmationPolling"="string(count(CanSMConfiguration/*[1]/CanSMManagerNetwork/*[CanSMBorTxConfirmationPolling != ../*[1]/CanSMBorTxConfirmationPolling]) != 0)"!]

[!ENDIF!]
[!ENDNOCODE!][!//
