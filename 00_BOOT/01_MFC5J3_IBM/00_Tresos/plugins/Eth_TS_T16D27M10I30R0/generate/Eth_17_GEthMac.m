[!/*
/*******************************************************************************
**                                                                            **
** Copyright (C) Infineon Technologies (2019)                                 **
**                                                                            **
** All rights reserved.                                                       **
**                                                                            **
** This document contains proprietary information belonging to Infineon       **
** Technologies. Passing on and copying of this document, and communication   **
** of its contents is not permitted without prior written authorization.      **
**                                                                            **
********************************************************************************
**                                                                            **
**  FILENAME  : Eth_17_GEthMac.m                                              **
**                                                                            **
**  VERSION   : 2.0.0                                                         **
**                                                                            **
**  DATE      : 2019-06-05                                                    **
**                                                                            **
**  BSW MODULE DESCRIPTION : Eth.bmd                                          **
**                                                                            **
**  VARIANT   : Variant PB                                                    **
**                                                                            **
**  PLATFORM  : Infineon AURIX2G                                              **
**                                                                            **
**  AUTHOR    : DL-AUTOSAR-Engineering                                        **
**                                                                            **
**  VENDOR    : Infineon Technologies                                         **
**                                                                            **
**  TRACEABILITY :                                                            **
**                                                                            **
**  DESCRIPTION  : Code template macro file for Eth Driver                    **
**                                                                            **
**                                                                            **
**                                                                            **
**  SPECIFICATION(S) : Specification of Eth Driver, AUTOSAR Release 4.2.2     **
**                                                                            **
**  MAY BE CHANGED BY USER : no                                               **
**                                                                            **
*******************************************************************************/
*/!]

[!/* *** multiple inclusion protection*** */!][!//
[!IF "not(var:defined('ETH_17_GETHMAC_M'))"!][!//
  [!VAR "ETH_17_GETHMAC_M"="'true'"!][!//
/*******************************************************************************
** Name             : ETH_GenerateModuleMap                                   **
**                                                                            **
** Description      : Macro to generate core-channel mappings for a module    **
**                                                                            **
*******************************************************************************/
  [!MACRO "ETH_GenerateModuleMap", "Module" = ""!][!//
    [!NOCODE!][!//
      [!SELECT "as:modconf('ResourceM')[1]"!][!//
        [!VAR "CGMasterCoreId_Extract" = "substring(node:value(ResourceMMcalConfig/*[1]/ResourceMMasterCore),5,1)"!][!//
        [!VAR "CGCoreID" = "num:i(0)"!][!//
        [!VAR "CGAllocatedChannelMap" = "''"!][!//
        [!VAR "CGCoreMap" = "''"!][!//
        [!VAR "CGAllocatedCores" = "''"!][!//
        [!LOOP "ResourceMMcalConfig/*[1]/ResourceMMcalCore/*"!][!//
          [!VAR "CGCoreID" = "./ResourceMCoreID"!][!//
          [!LOOP "ResourceMAllocation/*"!][!//
            [!IF "$Module = ./ResourceMModuleName"!][!//
              [!IF "node:refvalid(./ResourceMResourceRef) = 'true'"!][!//
              [!ELSE!][!//
                [!ERROR!]
                  ERROR: Invalid resource allocation done in [!"$CGCoreID"!] for [!"$Module"!] module:[!"node:path(.)"!] [!//
                [!ENDERROR!]
              [!ENDIF!][!//
              [!VAR "index" = "num:i(count(text:split(./ResourceMResourceRef, '/')))"!][!//
              [!VAR "ResourceName" = "text:split(./ResourceMResourceRef, '/')[num:i($index)]"!][!//
              [!VAR "CGCoreMap" = "text:toupper(concat($CGCoreMap, $CGCoreID, '_', $ResourceName, ','))"!][!//
              [!VAR "CGAllocatedCores" = "concat($CGAllocatedCores,$CGCoreID,',')"!][!//
              [!VAR "CGAllocatedChannelMap" = "text:toupper(concat($CGAllocatedChannelMap, $ResourceName, ','))"!][!//
            [!ENDIF!][!//
          [!ENDLOOP!][!//
        [!ENDLOOP!][!//
      [!ENDSELECT!][!//
    [!ENDNOCODE!][!//
  [!ENDMACRO!][!//

/*******************************************************************************
** Name             : ETH_ValidateChAllocation                                **
**                                                                            **
** Description      : Macro to validate if a channel is allocated to the core **
**                                                                            **
** Pre-requisite    : ETH_GenerateModuleMap macro should be called before     **
**                    calling this macro                                      **
*******************************************************************************/
  [!MACRO "ETH_ValidateChAllocation", "CoreNumber" = "", "Channel" = ""!][!//
    [!NOCODE!][!//
    [!VAR "CGAllocationResult" = "'FALSE'"!][!//
    [!VAR "CGChannelPattern" = "text:toupper(concat('CORE', num:i($CoreNumber), '_', $Channel))"!][!//
    [!IF "text:contains( text:split($CGCoreMap,','), $CGChannelPattern )"!][!//
      [!VAR "CGAllocationResult" = "'TRUE'"!][!//
    [!ELSEIF "not(text:contains( text:split($CGAllocatedChannelMap,','), text:toupper($Channel)))"!][!//
      [!IF "num:i($CGMasterCoreId_Extract) = (num:i($CoreNumber))"!][!//
        [!VAR "CGAllocationResult" = "'TRUE'"!][!//
      [!ENDIF!][!//
    [!ENDIF!][!//
    [!ENDNOCODE!][!//
  [!ENDMACRO!][!//
/*******************************************************************************
** Name             : ETH_GetMasterCoreID                                     **
**                                                                            **
** Description      : Macro to get master core ID                             **
**                                                                            **
** Pre-requisite    : NA                                                      **
*******************************************************************************/
  [!MACRO "ETH_GetMasterCoreID"!][!//
    [!SELECT "as:modconf('ResourceM')[1]"!][!//
      [!VAR "CGMasterCoreId" = "node:value(ResourceMMcalConfig/*[1]/ResourceMMasterCore)"!][!//
    [!ENDSELECT!][!//
  [!ENDMACRO!]


[!ENDIF!][!// IF "not(var:defined('ETH_17_GETHMAC_M'))


