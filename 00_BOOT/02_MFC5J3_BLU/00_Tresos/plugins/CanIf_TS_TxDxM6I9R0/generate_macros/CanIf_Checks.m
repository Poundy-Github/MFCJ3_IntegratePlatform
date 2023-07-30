[!/**
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
 */!][!//
[!/*
*** multiple inclusion protection ***
*/!][!IF "not(var:defined('CANIF_CHECKS_M'))"!][!/*
*/!][!VAR "CANIF_CHECKS_M"="'true'"!][!/*

*/[!INCLUDE "CanIf_PreCompileMacros.m"!][!/*
*/!][!INCLUDE "CanIf_Macros.m"!][!/*

=============================================================================
Configuration Checks as defined in the DOORS Design Document
=============================================================================


*** Check that all transceivers have different infixes ***
*/!][!LOOP "text:split($trcvInfixList,';')"!][!/*
   */!][!ASSERT "text:uniq(text:split($trcvInfixList,';'), .)"!]Two transceiver drivers used have identical VendorId ('[!"substring-before(., '_')"!]') and VendorApiInfix ('[!"substring-after(., '_')"!]')[!ENDASSERT!][!/*
*/!][!ENDLOOP!][!/*
*/!][!/*


*/!][!VAR "controllerRefs"="''"!][!/*
*/!][!LOOP "CanIfCtrlDrvCfg/*[1]/CanIfCtrlCfg/*"!][!/*
   */!][!ASSERT "as:ref(CanIfCtrlCanCtrlRef)/CanControllerActivation = 'true'"!]CAN Controller [!"name(as:ref(CanIfCtrlCanCtrlRef))"!] (referenced by [!"name(.)"!]) needs to be activated for use with the CAN Interface.[!ENDASSERT!][!/*

   */!][!ASSERT "count(text:grep(text:split($controllerRefs), CanIfCtrlCanCtrlRef)) = 0"!]CAN Controller [!"name(as:ref(CanIfCtrlCanCtrlRef))"!] is referenced multiple times. Needs to be unique.[!ENDASSERT!][!/*
   */!][!VAR "controllerRefs" = "concat($controllerRefs, ' ', CanIfCtrlCanCtrlRef)"!][!/*
*/!][!ENDLOOP!][!/*


<!-- !LINKSTO CanIf.ASR40.CANIF663,1 -->
*/!][!LOOP "CanIfInitCfg/*[1]/CanIfInitHohCfg/*[1]/CanIfHrhCfg/*"!][!/*
   */!][!IF "(CanIfHrhSoftwareFilter = 'false') and
             (count(../../../../CanIfRxPduCfg/*[num:i(count(CanIfRxPduHrhIdRef/*[as:path(as:ref(.)) = as:path(node:current())])) > 0]) > 1)"!][!/*
      */!][!WARNING!]HrH [!"name(.)"!] is used by multiple Rx-PDUs but software filtering is disabled.[!ENDWARNING!][!/*
   */!][!ENDIF!][!/*
*/!][!ENDLOOP!][!/*


*/!][!LOOP "CanIfInitCfg/*[1]/CanIfInitHohCfg/*[1]/CanIfHrhCfg/*"!][!/*
   */!][!ASSERT "as:path(as:ref(as:ref(CanIfHrhIdSymRef)/CanControllerRef)) = as:path(as:ref(as:ref(CanIfHrhCanCtrlIdRef)/CanIfCtrlCanCtrlRef))"!]HrH [!"name(.)"!] is assigned to a different CAN controller than its associated CAN Driver HrH.[!ENDASSERT!][!/*
   */!][!ASSERT "count(../*[CanIfHrhIdSymRef = node:current()/CanIfHrhIdSymRef]) = 1"!]HrH [!"name(.)"!] references a CAN Driver HrH that is referenced by another HrH.[!ENDASSERT!][!/*
*/!][!ENDLOOP!][!/*


*/!][!LOOP "CanIfInitCfg/*[1]/CanIfInitHohCfg/*[1]/CanIfHthCfg/*"!][!/*
   */!][!ASSERT "as:path(as:ref(as:ref(CanIfHthIdSymRef)/CanControllerRef)) = as:path(as:ref(as:ref(CanIfHthCanCtrlIdRef)/CanIfCtrlCanCtrlRef))"!]HtH [!"name(.)"!] is assigned to a different CAN controller than its associated CAN Driver HtH.[!ENDASSERT!][!/*
   */!][!ASSERT "count(..//*[CanIfHthIdSymRef = node:current()/CanIfHthIdSymRef]) = 1"!]HtH [!"name(.)"!] references a CAN Driver HtH that is referenced by another HtH.[!ENDASSERT!][!/*
*/!][!ENDLOOP!][!/*



*/!][!VAR "ecucRefList"="concat(text:join(CanIfInitCfg/*[1]/CanIfRxPduCfg/*/CanIfRxPduRef), ' ', text:join(CanIfInitCfg/*[1]/CanIfTxPduCfg/*/CanIfTxPduRef))"!][!/*
*/!][!LOOP "text:split($ecucRefList)"!][!/*
   */!][!ASSERT "text:uniq(text:split($ecucRefList), .)"!]Global PDU [!"."!] is referenced more than once[!ENDASSERT!][!/*
*/!][!ENDLOOP!][!/*


*/!][!LOOP "CanIfInitCfg/*[1]/CanIfTxPduCfg/*"!][!/*
   */!][!IF "CanIfTxPduCanIdType = 'STANDARD_CAN'"!][!/*
      */!][!ASSERT "node:value(as:ref(as:ref(as:ref(CanIfTxPduBufferRef)/CanIfBufferHthRef/*[1])/CanIfHthIdSymRef)/CanIdType) != 'EXTENDED'"!]
      Tx-PDU [!"name(.)"!] uses standard identifiers but is associated to an HtH that is configured for extended identifiers.[!ENDASSERT!][!/*
   */!][!ENDIF!][!/*
   */!][!IF "CanIfTxPduCanIdType = 'STANDARD_FD_CAN'"!][!/*
      */!][!ASSERT "node:value(as:ref(as:ref(as:ref(CanIfTxPduBufferRef)/CanIfBufferHthRef/*[1])/CanIfHthIdSymRef)/CanIdType) != 'EXTENDED'"!]
      Tx-PDU [!"name(.)"!] uses standard identifiers but is associated to an HtH that is configured for extended identifiers.[!ENDASSERT!][!/*
   */!][!ENDIF!][!/*
   */!][!IF "CanIfTxPduCanIdType = 'EXTENDED_CAN'"!][!/*
      */!][!ASSERT "node:value(as:ref(as:ref(as:ref(CanIfTxPduBufferRef)/CanIfBufferHthRef/*[1])/CanIfHthIdSymRef)/CanIdType) != 'STANDARD'"!]
      Tx-PDU [!"name(.)"!] uses extended identifiers but is associated to an HtH that is configured for standard identifiers.[!ENDASSERT!][!/*
   */!][!ENDIF!][!/*
   */!][!IF "CanIfTxPduCanIdType = 'EXTENDED_FD_CAN'"!][!/*
      */!][!ASSERT "node:value(as:ref(as:ref(as:ref(CanIfTxPduBufferRef)/CanIfBufferHthRef/*[1])/CanIfHthIdSymRef)/CanIdType) != 'STANDARD'"!]
      Tx-PDU [!"name(.)"!] uses extended identifiers but is associated to an HtH that is configured for standard identifiers.[!ENDASSERT!][!/*
   */!][!ENDIF!][!/*
*/!][!ENDLOOP!][!/*

*/!][!IF "$controllerNum > as:modconf('CanIf')[1]/CanIfPublicCfg/CanIfPublicMaxCtrl"!][!/*
  */!][!ERROR!]The number of configured Can controllers ([!"num:i($controllerNum)"!]) must not exceed CanIfPublicMaxCtrl ([!"as:modconf('CanIf')[1]/CanIfPublicCfg/CanIfPublicMaxCtrl"!]).[!ENDERROR!][!/*
*/!][!ENDIF!][!/*

*/!][!IF "count(as:modconf('CanIf')[1]/CanIfInitCfg/*[1]/CanIfTxPduCfg/*[CanIfTxPduReadNotifyStatus = 'true']) > as:modconf('CanIf')[1]/CanIfPublicCfg/CanIfPublicMaxTxNotifyPdus"!][!/*
  */!][!ERROR!]The number of enabled TxPdu read status notification ([!"num:i(count(as:modconf('CanIf')[1]/CanIfInitCfg/*[1]/CanIfTxPduCfg/*[CanIfTxPduReadNotifyStatus = 'true']))"!]) must not exceed CanIfPublicMaxTxNotifyPdus ([!"as:modconf('CanIf')[1]/CanIfPublicCfg/CanIfPublicMaxTxNotifyPdus"!]).[!ENDERROR!][!/*
*/!][!ENDIF!][!/*

*/!][!IF "count(as:modconf('CanIf')[1]/CanIfInitCfg/*[1]/CanIfRxPduCfg/*[CanIfRxPduReadNotifyStatus = 'true']) > as:modconf('CanIf')[1]/CanIfPublicCfg/CanIfPublicMaxRxNotifyPdus"!][!/*
  */!][!ERROR!]The number of enabled RxPdu read status notification ([!"num:i(count(as:modconf('CanIf')[1]/CanIfInitCfg/*[1]/CanIfRxPduCfg/*[CanIfRxPduReadNotifyStatus = 'true']))"!]) must not exceed CanIfPublicMaxRxNotifyPdus ([!"as:modconf('CanIf')[1]/CanIfPublicCfg/CanIfPublicMaxRxNotifyPdus"!]).[!ENDERROR!][!/*
*/!][!ENDIF!][!/*

*/!][!IF "node:exists(as:modconf('CanIf')[1]/CanIfPublicCfg/CanIfPublicMaxRxBuffer) and ($currRxBufferPos > as:modconf('CanIf')[1]/CanIfPublicCfg/CanIfPublicMaxRxBuffer)"!][!/*
  */!][!ERROR!]The actually required message buffer required for Pdus which support CanIf_ReadRxPduData() ([!"num:i($currRxBufferPos)"!]) must not exceed CanIfPublicMaxRxBuffer ([!"as:modconf('CanIf')[1]/CanIfPublicCfg/CanIfPublicMaxRxBuffer"!]).[!ENDERROR!][!/*
*/!][!ENDIF!][!/*

*/!][!IF "node:exists(as:modconf('CanIf')[1]/CanIfPublicCfg/CanIfPublicMaxHths) and ($hthNum > as:modconf('CanIf')[1]/CanIfPublicCfg/CanIfPublicMaxHths)"!][!/*
  */!][!ERROR!]The number of configured Hths ([!"num:i($hthNum)"!]) must not exceed CanIfPublicMaxHths ([!"as:modconf('CanIf')[1]/CanIfPublicCfg/CanIfPublicMaxHths"!]).[!ENDERROR!][!/*
*/!][!ENDIF!][!/*

*/!][!IF "node:exists(as:modconf('CanIf')[1]/CanIfPublicCfg/CanIfPublicMaxTxBufferSize) and ($currTxMemoryIndex > as:modconf('CanIf')[1]/CanIfPublicCfg/CanIfPublicMaxTxBufferSize)"!][!/*
  */!][!ERROR!]The required Tx-Buffer memory ([!"num:i($currTxMemoryIndex)"!]) exceeds the configured Tx-Buffer memory (CanIfPublicMaxTxBufferSize).[!ENDERROR!][!/*
*/!][!ENDIF!][!/*

*/!][!IF "node:exists(as:modconf('CanIf')[1]/CanIfPublicCfg/CanIfPublicMaxDynTxPdus) and ($dynamicTxPduNum > as:modconf('CanIf')[1]/CanIfPublicCfg/CanIfPublicMaxDynTxPdus)"!][!/*
  */!][!ERROR!]The number of dynamic Tx-Pdus ([!"num:i($dynamicTxPduNum)"!]) must not exceed CanIfPublicMaxDynTxPdus ([!"as:modconf('CanIf')[1]/CanIfPublicCfg/CanIfPublicMaxDynTxPdus"!]).[!ENDERROR!][!/*
*/!][!ENDIF!][!/*

*** End of file ***
*/!][!ENDIF!][!/*
*/!][!//
