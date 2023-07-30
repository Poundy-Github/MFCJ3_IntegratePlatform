[!/*****************************************************************************
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
**  FILENAME    : Eth_17_GEthMac_PBCfg.c                                      **
**                                                                            **
**  VERSION     : 1.30.0_17.0.0                                               **
**                                                                            **
**  DATE        : 2019-08-19                                                  **
**                                                                            **
**  BSW MODULE DECRIPTION : NA                                                **
**                                                                            **
**  VARIANT   : Variant PB                                                    **
**                                                                            **
**  PLATFORM  : Infineon AURIX2G                                              **
**                                                                            **
**  AUTHOR      : DL-AUTOSAR-Engineering                                      **
**                                                                            **
**  VENDOR      : Infineon Technologies                                       **
**                                                                            **
**                                                                            **
**  TRACEABILITY : [cover parentID]                                           **
**                                                                            **
**  DESCRIPTION  : Code template source file for Eth Driver                   **
**                                                                            **
**  [/cover]                                                                  **
**                                                                            **
**  SPECIFICATION(S) : Specification of Eth Driver, AUTOSAR Release 4.2.2     **
**                                                                            **
**  MAY BE CHANGED BY USER : no                                               **
**                                                                            **
******************************************************************************/!]
/******************************************************************************
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
**  FILENAME  : Eth_17_GEthMac_PBCfg.c                                        **
**                                                                            **
**  VERSION   : 1.30.0_17.0.0                                                 **
**                                                                            **
**  DATE, TIME: [!"$date"!], [!"$time"!]     !!!IGNORE-LINE!!!                     **
**                                                                            **
**  GENERATOR : Build [!"$buildnr"!]       !!!IGNORE-LINE!!!                      **
**                                                                            **
**  BSW MODULE DECRIPTION : NA                                                **
**                                                                            **
**  VARIANT   : Variant PB                                                    **
**                                                                            **
**  PLATFORM  : Infineon AURIX2G                                              **
**                                                                            **
**  AUTHOR    : DL-AUTOSAR-Engineering                                        **
**                                                                            **
**  VENDOR    : Infineon Technologies                                         **
**                                                                            **
**  DESCRIPTION  : Eth configuration generated out of ECUC file               **
**                                                                            **
**  SPECIFICATION(S) : Specification of Eth Driver, AUTOSAR Release 4.2.2     **
**                                                                            **
**  MAY BE CHANGED BY USER : no                                               **
**                                                                            **
*******************************************************************************/
[!/*[cover parentID={D8FB187A-2C4B-458d-A778-7659DDA17C34}][/cover]*/!][!//
[!/*[cover parentID={E4047F9A-8865-4b2c-9D3C-385479854EAD}][/cover]*/!][!//
/*******************************************************************************
**                      Includes                                              **
*******************************************************************************/
[!INDENT "0"!][!//
/* Include ETH Module File */
#include "Eth_17_GEthMac.h"
[!NOCODE!]
[!INCLUDE "Eth_17_GEthMac.m"!][!//
[!ENDNOCODE!]
/*******************************************************************************
**                      Private Macro Definitions                             **
*******************************************************************************/
/*******************************************************************************
**                      Imported Compiler Switch Check                        **
*******************************************************************************/
/*******************************************************************************
**                      Private Type Definitions                              **
*******************************************************************************/
/*******************************************************************************
**                      Private Function Declarations                         **
*******************************************************************************/
/*******************************************************************************
**                      Global Constant Definitions                           **
*******************************************************************************/
[!/*[cover parentID={E980AA54-E65B-4195-9529-297D70DC1946}][/cover]*/!][!//
[!/*[cover parentID={E1C2C17A-28DB-4b56-B41E-7E982611415E}][/cover]*/!][!//
[!/* [cover parentID={781260A6-01AA-46e5-82B8-ADEA8BA4A533}][/cover] */!][!//
[!/*[cover parentID={4579FE20-92DA-4848-93DB-7AD4FD35DD50}][/cover]*/!][!//

[!NOCODE!][!//
[!IF "not(node:exists(as:modconf('Mcu')[1]))"!]
  [!ERROR!][!//
    Ethernet needs Mcu module
  [!ENDERROR!][!//
[!ENDIF!]
[!IF "not(node:exists(as:modconf('ResourceM')[1]))"!]
  [!ERROR!][!//
    Ethernet needs ResourceM module
  [!ENDERROR!][!//
[!ENDIF!][!//
[!//
[!ENDNOCODE!][!//
[!//
[!VAR "VariantsConfigured" = "num:i(0)"!]
[!SELECT "as:modconf('EcuC')[1]"!][!//
  [!IF "node:exists(EcucPostBuildVariants/*[1]/EcucSelectedPostBuildVariantRef)"!][!//
    [!VAR "PredefinedVarName1" = "(EcucPostBuildVariants/*[1]/EcucSelectedPostBuildVariantRef)"!]
    [!VAR "PredefinedVarName2" = "substring-after($PredefinedVarName1, "/")"!][!//
    [!VAR "PredefinedVarName3" = "substring-after($PredefinedVarName2, "/")"!][!//
    [!VAR "PredefinedVarName" = "substring-after($PredefinedVarName3, "/")"!][!//
    [!VAR "VariantsConfigured" = "num:i(1)"!]
  [!ENDIF!][!//
[!ENDSELECT!]
[!AUTOSPACING!]
[!SELECT "as:modconf('Eth')[1]"!][!//
  [!CALL "ETH_GenerateModuleMap", "Module" = "'ETH'"!][!//
  [!CALL "ETH_GetMasterCoreID"!][!//
  [!VAR "MaxControllers"= "ecu:get('Eth.EthAvaliableNodes')"!][!//
  [!VAR "MaxControllersConfigured"= "num:i(count(EthConfigSet/*[1]/EthCtrlConfig/*))"!][!//
  [!IF "$MaxControllersConfigured > num:i(1)"!]
    [!FOR "ControllerId" = "num:i(0)" TO "num:i($MaxControllers)-num:i(1)"!]
      [!SELECT "EthConfigSet/*[1]/EthCtrlConfig/*[EthCtrlIdx = num:i($ControllerId)]"!]
        [!IF "num:i($ControllerId) = num:i(0)"!]
          [!VAR "MacAddress0" = "node:value(./EthCtrlPhyAddress)"!]
        [!ENDIF!]
        [!IF "num:i($ControllerId) = num:i(1)"!]
          [!VAR "MacAddress1" = "node:value(./EthCtrlPhyAddress)"!]
        [!ENDIF!]
      [!ENDSELECT!]
    [!ENDFOR!]
    [!IF "$MacAddress0 = $MacAddress1"!]
      [!ERROR!]
        Error : MACAddress configured in parameter EthCtrlPhyAddress must be unique for each ETH controller.
      [!ENDERROR!]
    [!ENDIF!]
  [!ENDIF!]
  /* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32 chars.
    in generated code due to Autosar Naming constraints.*/
  /* MISRA2012_RULE_5_2_JUSTIFICATION: External identifiers going beyond 32 chars.
    in generated code due to Autosar Naming constraints.*/
  /* MISRA2012_RULE_5_4_JUSTIFICATION: External identifiers going beyond 32 chars.
    in generated code due to Autosar Naming constraints.*/
  /* MISRA2012_RULE_5_5_JUSTIFICATION: External identifiers going beyond 32 chars.
    in generated code due to Autosar Naming constraints.*/
  #define ETH_17_GETHMAC_START_SEC_CONFIG_DATA_QM_GLOBAL_UNSPECIFIED
  /* MISRA2012_RULE_4_10_JUSTIFICATION: Memmap header is repeatedly included
     without safeguard. It complies to Autosar guidelines. */
  /* MISRA2012_RULE_20_1_JUSTIFICATION: Declaration of notification function
    before MemMap inclusion It complies to Autosar guidelines. */
  #include "Eth_17_GEthMac_MemMap.h"
  /*Array to store index of the controller in the allocated core.*/
  [!VAR "CurrentIdx" = "num:i(255)"!][!//
  [!VAR "EthCore0Idx" = "num:i(0)"!][!//
  [!VAR "EthCore1Idx" = "num:i(0)"!][!//
  [!VAR "EthCore2Idx" = "num:i(0)"!][!//
  [!VAR "EthCore3Idx" = "num:i(0)"!][!//
  [!VAR "EthCore4Idx" = "num:i(0)"!][!//
  [!VAR "EthCore5Idx" = "num:i(0)"!][!//
  [!IF "$VariantsConfigured = num:i(1)"!][!//
    [!/*[cover parentID={0E3E8C79-9359-47c5-9119-D7CD442DE334}][/cover]*/!][!//
      static const uint8 Eth_17_GEthMac_ControllerIndexMap_[!"$PredefinedVarName"!] [[!"num:i($MaxControllersConfigured)"!]] =
  [!ELSE!][!//
      static const uint8 Eth_17_GEthMac_ControllerIndexMap [[!"num:i($MaxControllersConfigured)"!]] =
  [!ENDIF!][!//
  {
  [!INDENT "2"!][!//
  [!FOR "ControllerID" = "num:i(0)" TO "num:i($MaxControllers) - num:i(1)"!][!//
    [!IF "node:exists(EthConfigSet/*[1]/EthCtrlConfig/*[EthCtrlIdx = num:i($ControllerID)]) = 'true'"!][!//
      [!SELECT "EthConfigSet/*[1]/EthCtrlConfig/*[EthCtrlIdx = num:i($ControllerID)]"!][!//
        [!VAR "NodeName" = "node:name(.)"!][!//
        [!FOR "CoreId" = "num:i(0)" TO "num:i(ecu:get('Mcu.NoOfCoreAvailable')) - num:i(1)"!][!//
          [!CALL "ETH_ValidateChAllocation", "CoreNumber" = "$CoreId", "Channel" = "$NodeName"!][!//
          [!IF "$CGAllocationResult = 'TRUE'"!][!//
            [!IF "$CoreId = num:i(0)"!][!//
              [!VAR "CurrentIdx" = "$EthCore0Idx"!][!//
              [!VAR "EthCore0Idx" = "$EthCore0Idx+num:i(1)"!][!//
            [!ELSEIF "$CoreId = num:i(1)"!][!//
              [!VAR "CurrentIdx" = "$EthCore1Idx"!][!//
              [!VAR "EthCore1Idx" = "$EthCore1Idx+num:i(1)"!][!//
            [!ELSEIF "$CoreId = num:i(2)"!][!//
              [!VAR "CurrentIdx" = "$EthCore2Idx"!][!//
              [!VAR "EthCore2Idx" = "$EthCore2Idx+num:i(1)"!][!//
            [!ELSEIF "$CoreId = num:i(3)"!][!//
              [!VAR "CurrentIdx" = "$EthCore3Idx"!][!//
              [!VAR "EthCore3Idx" = "$EthCore3Idx+num:i(1)"!][!//
            [!ELSEIF "$CoreId = num:i(4)"!][!//
              [!VAR "CurrentIdx" = "$EthCore4Idx"!][!//
              [!VAR "EthCore4Idx" = "$EthCore4Idx+num:i(1)"!][!//
            [!ELSEIF "$CoreId = num:i(5)"!][!//
              [!VAR "CurrentIdx" = "$EthCore5Idx"!][!//
              [!VAR "EthCore5Idx" = "$EthCore5Idx+num:i(1)"!][!//
            [!ENDIF!][!//
          [!ENDIF!][!//
        [!ENDFOR!][!//
      [!ENDSELECT!][!//
      [!"num:inttohex(number($CurrentIdx))"!]U,
    [!ENDIF!][!//
    [!VAR "CurrentIdx" = "num:i(255)"!][!//
  [!ENDFOR!][!//
  [!ENDINDENT!][!//
  };

  /* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32 chars.
    in generated code due to Autosar Naming constraints.*/
  /* MISRA2012_RULE_5_2_JUSTIFICATION: External identifiers going beyond 32 chars.
    in generated code due to Autosar Naming constraints.*/
  /* MISRA2012_RULE_5_4_JUSTIFICATION: External identifiers going beyond 32 chars.
    in generated code due to Autosar Naming constraints.*/
  /* MISRA2012_RULE_5_5_JUSTIFICATION: External identifiers going beyond 32 chars.
    in generated code due to Autosar Naming constraints.*/
  #define ETH_17_GETHMAC_STOP_SEC_CONFIG_DATA_QM_GLOBAL_UNSPECIFIED
  /* MISRA2012_RULE_4_10_JUSTIFICATION: Memmap header is repeatedly included
     without safeguard. It complies to Autosar guidelines. */
  /* MISRA2012_RULE_20_1_JUSTIFICATION: Declaration of notification function
    before MemMap inclusion It complies to Autosar guidelines. */
  #include "Eth_17_GEthMac_MemMap.h"

  [!FOR "CoreId" = "num:i(0)" TO "num:i(ecu:get('Mcu.NoOfCoreAvailable')) - num:i(1)"!][!//
    [!VAR "MaxControllersCore" = "num:i(0)"!][!//
    [!VAR "TempCoreId" = "concat('CORE',$CoreId)"!][!//
    [!CALL "ETH_GetMasterCoreID"!][!//
    [!FOR "ControllerID" = "num:i(0)" TO "num:i($MaxControllers) - num:i(1)"!][!//
      [!IF "node:exists(EthConfigSet/*[1]/EthCtrlConfig/*[EthCtrlIdx = num:i($ControllerID)]) = 'true'"!][!//
        [!SELECT "EthConfigSet/*[1]/EthCtrlConfig/*[EthCtrlIdx = num:i($ControllerID)]"!][!//
          [!VAR "NodeName" = "node:name(.)"!][!//
          [!VAR "EthCtrlIdx" = "./EthCtrlIdx"!][!//
          [!CALL "ETH_ValidateChAllocation", "CoreNumber" = "$CoreId", "Channel" = "$NodeName"!][!//
          [!IF "$CGAllocationResult = 'TRUE'"!][!//
            [!NOCODE!][!//
              [!VAR "MaxControllersCore" = "$MaxControllersCore + num:i(1)"!][!//
            [!ENDNOCODE!][!//
          [!ENDIF!][!//
        [!ENDSELECT!][!//
      [!ENDIF!][!//
    [!ENDFOR!][!//
    [!IF "$MaxControllersCore != num:i(0)"!][!//
      /* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32 chars.
        in generated code due to Autosar Naming constraints.*/
      /* MISRA2012_RULE_5_2_JUSTIFICATION: External identifiers going beyond 32 chars.
        in generated code due to Autosar Naming constraints.*/
      /* MISRA2012_RULE_5_4_JUSTIFICATION: External identifiers going beyond 32 chars.
        in generated code due to Autosar Naming constraints.*/
      /* MISRA2012_RULE_5_5_JUSTIFICATION: External identifiers going beyond 32 chars.
        in generated code due to Autosar Naming constraints.*/
      #define ETH_17_GETHMAC_START_SEC_CONFIG_DATA_QM_CORE[!"$CoreId"!]_UNSPECIFIED
      /* MISRA2012_RULE_4_10_JUSTIFICATION: Memmap header is repeatedly included
         without safeguard. It complies to Autosar guidelines. */
      /* MISRA2012_RULE_20_1_JUSTIFICATION: Declaration of notification function
        before MemMap inclusion It complies to Autosar guidelines. */
      #include "Eth_17_GEthMac_MemMap.h"
      /* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32 chars.
        in generated code due to Autosar Naming constraints.*/
      /* MISRA2012_RULE_5_2_JUSTIFICATION: External identifiers going beyond 32 chars.
        in generated code due to Autosar Naming constraints.*/
      /* MISRA2012_RULE_5_4_JUSTIFICATION: External identifiers going beyond 32 chars.
        in generated code due to Autosar Naming constraints.*/
      /* MISRA2012_RULE_5_5_JUSTIFICATION: External identifiers going beyond 32 chars.
        in generated code due to Autosar Naming constraints.*/
      [!/*[cover parentID={E1C2C17A-28DB-4b56-B41E-7E982611415E}][/cover]*/!][!//
      /*  Structure to store controller configuration data for Core[!"$CoreId"!] */
      [!IF "$VariantsConfigured = num:i(1)"!]
        static const Eth_17_GEthMac_CoreCntrlConfigType Eth_17_GEthMac_CoreCntrlConfigCore[!"$CoreId"!]_[!"$PredefinedVarName"!][[!"num:i($MaxControllersCore)"!]]=
      [!ELSE!]
        static const Eth_17_GEthMac_CoreCntrlConfigType Eth_17_GEthMac_CoreCntrlConfigCore[!"$CoreId"!][[!"num:i($MaxControllersCore)"!]]=
      [!ENDIF!]
      {
      [!FOR "ControllerId" = "num:i(0)" TO "num:i($MaxControllers) - num:i(1)"!][!//
        [!IF "node:exists(EthConfigSet/*[1]/EthCtrlConfig/*[EthCtrlIdx = num:i($ControllerId)]) = 'true'"!][!//
          [!SELECT "EthConfigSet/*[1]/EthCtrlConfig/*[EthCtrlIdx = num:i($ControllerId)]"!][!//
            [!VAR "NodeName" = "node:name(.)"!][!//
            [!VAR "EthCtrlIdxTemp" = "./EthCtrlIdx"!][!//
            [!CALL "ETH_ValidateChAllocation", "CoreNumber" = "$CoreId", "Channel" = "$NodeName"!][!//
            [!IF "$CGAllocationResult = 'TRUE'"!][!//
              [!NOCODE!][!//
                [!VAR "EthCtrlRxBufLenBytevalue" = "./EthCtrlRxBufLenByte"!][!//
                [!VAR "EthCtrlTxBufLenBytevalue" = "./EthCtrlTxBufLenByte"!][!//
                [!VAR "EthCtrlRxBufLenBytevalueActual" = "./EthCtrlRxBufLenByte"!][!//
                [!VAR "EthCtrlTxBufLenBytevalueActual" = "./EthCtrlTxBufLenByte"!][!//
                [!VAR "RxBufQuotient" = "num:i($EthCtrlRxBufLenBytevalue) div 8"!][!//
                /*Checking if configured RxLengthByte is a muliple of 8 0r not*/
                [!IF "num:i($EthCtrlRxBufLenBytevalue) mod 8 != 0"!][!//
                  /*if configured value for RxLengthByte is not a multiple of 8 assign the next
                  multiple of 8 to variable EthCtrlRxBufLenBytevalue*/
                  [!VAR "EthCtrlRxBufLenBytevalue" = "num:i((num:i($RxBufQuotient) + 1) * 8)"!][!//
                [!ENDIF!]!][!//
                [!VAR "TxBufQuotient" = "num:i($EthCtrlTxBufLenBytevalue) div 8"!][!//
                /*Checking if configured TxLengthByte is a muliple of 8 0r not*/
                [!IF "num:i($EthCtrlTxBufLenBytevalue) mod 8 != 0"!][!//
                  /*if configured value for TxLengthByte is not a multiple of 8 assign the next
                  multiple of 8 to variable EthCtrlTxBufLenBytevalue*/
                  [!VAR "EthCtrlTxBufLenBytevalue" = "num:i((num:i($TxBufQuotient) + 1) * 8)"!][!//
                [!ENDIF!]!][!//
                [!VAR "EthRxBufTotalvalue" = "./EthRxBufTotal"!][!//
                [!VAR "EthTxBufTotalvalue" = "./EthTxBufTotal"!][!//
                [!VAR "EthMACAddress" = "text:replaceAll(node:value(./EthCtrlPhyAddress),'-',':')"!][!//
                [!IF "./EthSpeed = 'ETH_10MBPS'"!][!//
                  [!VAR "EthCntrlPortSpeedSelect" = "num:i(1)"!][!//
                [!ELSEIF "./EthSpeed = 'ETH_100MBPS'"!][!//
                  [!VAR "EthCntrlPortSpeedSelect" = "num:i(3)"!][!//
                [!ELSE!][!//
                  [!VAR "EthCntrlPortSpeedSelect" = "num:i(0)"!][!//
                [!ENDIF!][!//

                [!IF "./EthPhyInterface = 'MII'"!][!//
                  [!VAR "EthCntrlMode" = "num:i(0)"!][!// /* MII MODE */[!//
                [!ELSEIF "./EthPhyInterface = 'RMII'"!][!//
                  [!VAR "EthCntrlMode" = "num:i(4)"!][!// /* RMII MODE */[!//
                [!ELSE!][!//
                  [!VAR "EthCntrlMode" = "num:i(1)"!][!// /* RGMII MODE */ [!//
                [!ENDIF!][!//
                [!VAR "EthCntrlMode" = "bit:shl($EthCntrlMode,2)"!][!//
                [!VAR "EthCtrlProperty" = "bit:or($EthCntrlPortSpeedSelect,$EthCntrlMode)"!][!//

                [!IF "./EthOpMode = 'FULLDUPLEX'"!][!//
                  [!VAR "EthCntrlOpMode" = "num:i(1)"!][!// /* FULLDUPLEX */[!//
                [!ELSE!][!//
                  [!VAR "EthCntrlOpMode" = "num:i(0)"!][!// /* HALFDUPLEX */[!//
                [!ENDIF!][!//
                [!VAR "EthCntrlOpMode" = "bit:shl($EthCntrlOpMode,5)"!][!//
                [!VAR "EthCtrlProperty" = "bit:or($EthCtrlProperty,$EthCntrlOpMode)"!][!//

                /* Enabled/Disable Tx Interrupt*/
                [!VAR "EthInterruptEnable" = "num:i(0)"!][!//
                [!IF "./EthCtrlEnableTxInterrupt = 'true'"!][!//
                  [!VAR "EthInterruptEnable" = "bit:shl(num:i(1),6)"!][!//
                [!ENDIF!][!//
                /* Enabled/Disable Rx Interrupt*/
                [!IF "./EthCtrlEnableRxInterrupt = 'true'"!][!//
                  [!VAR "EthInterruptEnable" = "bit:or($EthInterruptEnable,bit:shl(num:i(1),7))"!][!//
                [!ENDIF!][!//
                [!VAR "EthCtrlProperty" = "bit:or($EthCtrlProperty,$EthInterruptEnable)"!][!//

                [!VAR "EthCrcStrip" = "num:i(0)"!][!//
                [!IF "./EthCtrlEnableCrcStripping = 'true'"!][!//
                  [!VAR "EthCrcStrip" = "bit:shl(num:i(1),8)"!][!//
                [!ENDIF!][!//
                [!VAR "EthCtrlProperty" = "bit:or($EthCtrlProperty,$EthCrcStrip)"!][!//

                /*Specifies the Tx/Rx clock delay in RGMII mode for skew timing*/
                [!VAR "EthTxRxSkewDelay" = "num:i(0)"!][!//
                [!IF "./EthPhyInterface = 'RGMII'"!][!//
                  [!VAR "EthTxRxSkewDelay" = "./EthSkewTxClockDelay"!][!//
                  [!VAR "EthTxRxSkewDelay" = "bit:or($EthTxRxSkewDelay,bit:shl(num:i(./EthSkewRxClockDelay),4))"!][!//
                [!ENDIF!][!//

                /*Selects alternate input for MDIO Input Signal */
                [!VAR "EthAltInSelx" = "substring(./EthMdioAlternateInput,1,4)"!][!//
                [!IF "$EthAltInSelx = 'ALT0'"!][!//
                  [!VAR "EthMdioAltInputVal" = "num:i(0)"!][!//
                [!ELSEIF "$EthAltInSelx = 'ALT1'"!][!//
                  [!VAR "EthMdioAltInputVal" = "num:i(1)"!][!//
                [!ELSEIF "$EthAltInSelx = 'ALT2'"!][!//
                  [!VAR "EthMdioAltInputVal" = "num:i(2)"!][!//
                [!ELSEIF "$EthAltInSelx = 'ALT3'"!][!//
                  [!VAR "EthMdioAltInputVal" = "num:i(3)"!][!//
                [!ELSE!]
                  [!VAR "EthMdioAltInputVal" = "num:i(0)"!][!//
                [!ENDIF!][!//

                /*Selects alternate input for Receive Clock for MII/RGMII-only ALT0 for RGMII*/
                [!IF "./EthPhyInterface != 'RMII'"!][!//
                  [!VAR "EthRxClkInx" = "substring(./EthRxclkInput,1,4)"!][!//
                  [!IF "$EthRxClkInx = 'ALT0'"!][!//
                    [!VAR "EthRxClkInVal" = "num:i(0)"!][!//
                  [!ELSEIF "$EthRxClkInx = 'ALT1'"!][!//
                    [!VAR "EthRxClkInVal" = "num:i(4)"!][!//
                  [!ELSEIF "$EthRxClkInx = 'ALT2'"!][!//
                    [!VAR "EthRxClkInVal" = "num:i(8)"!][!//
                  [!ELSEIF "$EthRxClkInx = 'ALT3'"!][!//
                    [!VAR "EthRxClkInVal" = "num:i(12)"!][!//
                  [!ELSE!]
                    [!VAR "EthRxErrMIIInVal" = "num:i(0)"!][!//
                  [!ENDIF!][!//
                [!ELSE!]
                  [!VAR "EthRxClkInVal" = "num:i(0)"!][!//
                [!ENDIF!][!//
                [!VAR "EthGpctlRegVal" = "bit:or($EthMdioAltInputVal,$EthRxClkInVal)"!][!//

                /*Selects alternate input for Receive Error for MII. */
                [!IF "./EthPhyInterface = 'MII'"!][!//
                  [!VAR "EthRxErrMIIInx" = "substring(./EthRxErrMIIInput,1,4)"!][!//
                  [!IF "$EthRxErrMIIInx = 'ALT0'"!][!//
                    [!VAR "EthRxErrMIIInVal" = "num:i(0)"!][!//
                  [!ELSEIF "$EthRxErrMIIInx = 'ALT1'"!][!//
                    [!VAR "EthRxErrMIIInVal" = "num:i(1024)"!][!//
                  [!ELSEIF "$EthRxErrMIIInx = 'ALT2'"!][!//
                    [!VAR "EthRxErrMIIInVal" = "num:i(2048)"!][!//
                  [!ELSEIF "$EthRxErrMIIInx = 'ALT3'"!][!//
                    [!VAR "EthRxErrMIIInVal" = "num:i(3072)"!][!//
                  [!ELSE!]
                    [!VAR "EthRxErrMIIInVal" = "num:i(0)"!][!//
                  [!ENDIF!][!//
                [!ELSE!]
                  [!VAR "EthRxErrMIIInVal" = "num:i(0)"!][!//
                [!ENDIF!][!//
                [!VAR "EthGpctlRegVal" = "bit:or($EthGpctlRegVal,$EthRxErrMIIInVal)"!][!//

                /*Selects alternate input for Carrier Sense for MII. */
                [!IF "./EthPhyInterface = 'MII'"!][!//
                  [!VAR "EthCarrierSenseMIIInx" = "substring(./EthCarrierSenseMIIInput,1,4)"!][!//
                  [!IF "$EthCarrierSenseMIIInx = 'ALT0'"!][!//
                    [!VAR "EthCarrierSenseMIIInVal" = "num:i(0)"!][!//
                  [!ELSEIF "$EthCarrierSenseMIIInx = 'ALT1'"!][!//
                    [!VAR "EthCarrierSenseMIIInVal" = "num:i(16)"!][!//
                  [!ELSEIF "$EthCarrierSenseMIIInx = 'ALT2'"!][!//
                    [!VAR "EthCarrierSenseMIIInVal" = "num:i(32)"!][!//
                  [!ELSEIF "$EthCarrierSenseMIIInx = 'ALT3'"!][!//
                    [!VAR "EthCarrierSenseMIIInVal" = "num:i(48)"!][!//
                  [!ELSE!]
                    [!VAR "EthCarrierSenseMIIInVal" = "num:i(0)"!][!//
                  [!ENDIF!][!//
                [!ELSE!][!//
                  [!VAR "EthCarrierSenseMIIInVal" = "num:i(0)"!][!//
                [!ENDIF!][!//
                [!VAR "EthGpctlRegVal" = "bit:or($EthGpctlRegVal,$EthCarrierSenseMIIInVal)"!][!//

                /*Selects alternate input for Carrier Sense for MII. */
                [!IF "./EthPhyInterface = 'MII'"!][!//
                  [!VAR "EthRecDataValidMIIInx" = "substring(./EthRecDataValidMIIInput,1,4)"!][!//
                  [!IF "$EthRecDataValidMIIInx = 'ALT0'"!][!//
                    [!VAR "EthRecDataValidMIIInVal" = "num:i(0)"!][!//
                  [!ELSEIF "$EthRecDataValidMIIInx = 'ALT1'"!][!//
                    [!VAR "EthRecDataValidMIIInVal" = "num:i(256)"!][!//
                  [!ELSEIF "$EthRecDataValidMIIInx = 'ALT2'"!][!//
                    [!VAR "EthRecDataValidMIIInVal" = "num:i(512)"!][!//
                  [!ELSEIF "$EthRecDataValidMIIInx = 'ALT3'"!][!//
                    [!VAR "EthRecDataValidMIIInVal" = "num:i(768)"!][!//
                  [!ELSE!]
                    [!VAR "EthRecDataValidMIIInVal" = "num:i(0)"!][!//
                  [!ENDIF!][!//
                [!ELSE!][!//
                  [!VAR "EthRecDataValidMIIInVal" = "num:i(0)"!][!//
                [!ENDIF!][!//
                [!VAR "EthGpctlRegVal" = "bit:or($EthGpctlRegVal,$EthRecDataValidMIIInVal)"!][!//

                /*Selects alternate input for Transmit clock input for MII. */
                [!IF "./EthPhyInterface = 'MII'"!][!//
                  [!VAR "EthTxClockMIIInputCntrlx" = "substring(./EthTxClockMIIInput,1,4)"!][!//
                  [!IF "$EthTxClockMIIInputCntrlx = 'ALT0'"!][!//
                    [!VAR "EthTxClockMIIInputCntrlVal" = "num:i(0)"!][!//
                  [!ELSEIF "$EthTxClockMIIInputCntrlx = 'ALT1'"!][!//
                    [!VAR "EthTxClockMIIInputCntrlVal" = "num:i(1048576)"!][!//
                  [!ELSEIF "$EthTxClockMIIInputCntrlx = 'ALT2'"!][!//
                    [!VAR "EthTxClockMIIInputCntrlVal" = "num:i(2097152)"!][!//
                  [!ELSEIF "$EthTxClockMIIInputCntrlx = 'ALT3'"!][!//
                    [!VAR "EthTxClockMIIInputCntrlVal" = "num:i(3145728)"!][!//
                  [!ELSE!]
                    [!VAR "EthTxClockMIIInputCntrlVal" = "num:i(0)"!][!//
                  [!ENDIF!][!//
                [!ELSE!][!//
                  [!VAR "EthTxClockMIIInputCntrlVal" = "num:i(0)"!][!//
                [!ENDIF!][!//
                [!VAR "EthGpctlRegVal" = "bit:or($EthGpctlRegVal,$EthTxClockMIIInputCntrlVal)"!][!//

                /*Selects alternate input for Collision input for MII. */
                [!IF "./EthPhyInterface = 'MII'"!][!//
                  [!VAR "EthCollisionMIICntrlx" = "substring(./EthCollisionMII,1,4)"!][!//
                  [!IF "$EthCollisionMIICntrlx = 'ALT0'"!][!//
                    [!VAR "EthCollisionMIICntrlVal" = "num:i(0)"!][!//
                  [!ELSEIF "$EthCollisionMIICntrlx = 'ALT1'"!][!//
                    [!VAR "EthCollisionMIICntrlVal" = "num:i(64)"!][!//
                  [!ELSEIF "$EthCollisionMIICntrlx = 'ALT2'"!][!//
                    [!VAR "EthCollisionMIICntrlVal" = "num:i(128)"!][!//
                  [!ELSEIF "$EthCollisionMIICntrlx = 'ALT3'"!][!//
                    [!VAR "EthCollisionMIICntrlVal" = "num:i(192)"!][!//
                  [!ELSE!]
                    [!VAR "EthCollisionMIICntrlVal" = "num:i(0)"!][!//
                  [!ENDIF!][!//
                [!ELSE!][!//
                  [!VAR "EthCollisionMIICntrlVal" = "num:i(0)"!][!//
                [!ENDIF!][!//
                [!VAR "EthGpctlRegVal" = "bit:or($EthGpctlRegVal,$EthCollisionMIICntrlVal)"!][!//

                /*Selects alternate input for Reference clock input for RMII(50MHz). */
                [!IF "./EthPhyInterface = 'RMII'"!][!//
                  [!VAR "EthRefClkRMIIInx" = "substring(./EthRefClkRMIIInput,1,4)"!][!//
                  [!IF "$EthRefClkRMIIInx = 'ALT0'"!][!//
                    [!VAR "EthRefClkRMIIInVal" = "num:i(0)"!][!//
                  [!ELSEIF "$EthRefClkRMIIInx = 'ALT1'"!][!//
                    [!VAR "EthRefClkRMIIInVal" = "num:i(4)"!][!//
                  [!ELSEIF "$EthRefClkRMIIInx = 'ALT2'"!][!//
                    [!VAR "EthRefClkRMIIInVal" = "num:i(8)"!][!//
                  [!ELSEIF "$EthRefClkRMIIInx = 'ALT3'"!][!//
                    [!VAR "EthRefClkRMIIInVal" = "num:i(12)"!][!//
                  [!ELSE!]
                    [!VAR "EthRefClkRMIIInVal" = "num:i(0)"!][!//
                  [!ENDIF!][!//
                [!ELSE!][!//
                  [!VAR "EthRefClkRMIIInVal" = "num:i(0)"!][!//
                [!ENDIF!][!//
                [!VAR "EthGpctlRegVal" = "bit:or($EthGpctlRegVal,$EthRefClkRMIIInVal)"!][!//

                /*Selects alternate input for Carrier Sense/Data Valid combi-signal for RMII */
                [!IF "./EthPhyInterface = 'RMII'"!][!//
                  [!VAR "EthCRSDVRMIIInx" = "substring(./EthCRSDVRMIIInput,1,4)"!][!//
                  [!IF "$EthCRSDVRMIIInx = 'ALT0'"!][!//
                    [!VAR "EthCRSDVRMIIInVal" = "num:i(0)"!][!//
                  [!ELSEIF "$EthCRSDVRMIIInx = 'ALT1'"!][!//
                    [!VAR "EthCRSDVRMIIInVal" = "num:i(256)"!][!//
                  [!ELSEIF "$EthCRSDVRMIIInx = 'ALT2'"!][!//
                  [!VAR "EthCRSDVRMIIInVal" = "num:i(512)"!][!//
                  [!ELSEIF "EthCRSDVRMIIInx = 'ALT3'"!][!//
                  [!VAR "EthCRSDVRMIIInVal" = "num:i(768)"!][!//
                  [!ELSE!]
                  [!VAR "EthCRSDVRMIIInVal" = "num:i(0)"!][!//
                  [!ENDIF!][!//
                [!ELSE!][!//
                  [!VAR "EthCRSDVRMIIInVal" = "num:i(0)"!][!//
                [!ENDIF!][!//
                [!VAR "EthGpctlRegVal" = "bit:or($EthGpctlRegVal,$EthCRSDVRMIIInVal)"!][!//

                /*Selects alternate input for RX-Data 0 for MII and RMII-only ALT0 for RGMII*/
                [!VAR "EthReceiveData0Inx" = "substring(./EthReceiveData0Input,1,4)"!][!//
                [!IF "$EthReceiveData0Inx = 'ALT0'"!][!//
                  [!VAR "EthReceiveData0InVal" = "num:i(0)"!][!//
                [!ELSEIF "$EthReceiveData0Inx = 'ALT1'"!][!//
                  [!VAR "EthReceiveData0InVal" = "num:i(4096)"!][!//
                [!ELSEIF "$EthReceiveData0Inx = 'ALT2'"!][!//
                  [!VAR "EthReceiveData0InVal" = "num:i(8192)"!][!//
                [!ELSEIF "EthReceiveData0Inx = 'ALT3'"!][!//
                  [!VAR "EthReceiveData0InVal" = "num:i(12288)"!][!//
                [!ELSE!]
                  [!VAR "EthReceiveData0InVal" = "num:i(0)"!][!//
                [!ENDIF!][!//
                [!VAR "EthGpctlRegVal" = "bit:or($EthGpctlRegVal,$EthReceiveData0InVal)"!][!//

                /*Selects alternate input for RX-Data 1 for MII and RMII-only ALT0 for RGMII*/
                [!VAR "EthReceiveData1Inx" = "substring(./EthReceiveData1Input,1,4)"!][!//
                [!IF "$EthReceiveData1Inx = 'ALT0'"!][!//
                  [!VAR "EthReceiveData1InVal" = "num:i(0)"!][!//
                [!ELSEIF "$EthReceiveData1Inx = 'ALT1'"!][!//
                  [!VAR "EthReceiveData1InVal" = "num:i(16384)"!][!//
                [!ELSEIF "$EthReceiveData1Inx = 'ALT2'"!][!//
                  [!VAR "EthReceiveData1InVal" = "num:i(32768)"!][!//
                [!ELSEIF "EthReceiveData1Inx = 'ALT3'"!][!//
                  [!VAR "EthReceiveData1InVal" = "num:i(49152)"!][!//
                [!ELSE!]
                  [!VAR "EthReceiveData1InVal" = "num:i(0)"!][!//
                [!ENDIF!][!//
                [!VAR "EthGpctlRegVal" = "bit:or($EthGpctlRegVal,$EthReceiveData1InVal)"!][!//

                /*Selects alternate input for RX-Data 2 for MII and RMII-only ALT0 for RGMII*/
                [!VAR "EthReceiveData2Inx" = "substring(./EthReceiveData2Input,1,4)"!][!//
                [!IF "$EthReceiveData2Inx = 'ALT0'"!][!//
                  [!VAR "EthReceiveData2InVal" = "num:i(0)"!][!//
                [!ELSEIF "$EthReceiveData2Inx = 'ALT1'"!][!//
                  [!VAR "EthReceiveData2InVal" = "num:i(65536)"!][!//
                [!ELSEIF "$EthReceiveData2Inx = 'ALT2'"!][!//
                  [!VAR "EthReceiveData2InVal" = "num:i(131072)"!][!//
                [!ELSEIF "EthReceiveData2Inx = 'ALT3'"!][!//
                  [!VAR "EthReceiveData2InVal" = "num:i(196608)"!][!//
                [!ELSE!]
                  [!VAR "EthReceiveData2InVal" = "num:i(0)"!][!//
                [!ENDIF!][!//
                [!VAR "EthGpctlRegVal" = "bit:or($EthGpctlRegVal,$EthReceiveData2InVal)"!][!//

                /*Selects alternate input for RX-Data 3 for MII and RMII-only ALT0 for RGMII*/
                [!VAR "EthReceiveData3Inx" = "substring(./EthReceiveData3Input,1,4)"!][!//
                [!IF "$EthReceiveData3Inx = 'ALT0'"!][!//
                  [!VAR "EthReceiveData3InVal" = "num:i(0)"!][!//
                [!ELSEIF "$EthReceiveData3Inx = 'ALT1'"!][!//
                  [!VAR "EthReceiveData3InVal" = "num:i(262144)"!][!//
                [!ELSEIF "$EthReceiveData3Inx = 'ALT2'"!][!//
                  [!VAR "EthReceiveData3InVal" = "num:i(524288)"!][!//
                [!ELSEIF "EthReceiveData3Inx = 'ALT3'"!][!//
                  [!VAR "EthReceiveData3InVal" = "num:i(786432)"!][!//
                [!ELSE!]
                  [!VAR "EthReceiveData3InVal" = "num:i(0)"!][!//
                [!ENDIF!][!//
                [!VAR "EthGpctlRegVal" = "bit:or($EthGpctlRegVal,$EthReceiveData3InVal)"!][!//
              [!ENDNOCODE!][!//
              [!INDENT "2"!][!//
              {
                [!INDENT "4"!][!//
                 /*Specifies the Tx[0:3]/Rx[4:7] clock delay in RGMII mode for transmit
                skew timing*/
                (uint32)[!"$EthTxRxSkewDelay"!],
                /* Element to store GETH_GPCTL register value for current controller */
                (uint32)[!"$EthGpctlRegVal"!],
                [!IF "$EthRxBufTotalvalue = 0"!][!//
                  (uint16)0U,[!//  /*Configured Receive Buffer Length*/
                [!ELSE!][!//
                  (uint16)[!"$EthCtrlRxBufLenBytevalueActual"!]U,  /*Configured Receive Buffer Length*/
                [!ENDIF!][!//
                [!IF "$EthRxBufTotalvalue = 0"!][!//
                  (uint16)0U,[!//  /*Receive Buffer Length 8 byte aligned*/
                [!ELSE!][!//
                  (uint16)[!"$EthCtrlRxBufLenBytevalue"!]U,  /*Receive Buffer Length 8 byte aligned*/
                [!ENDIF!][!//
                [!IF "$EthTxBufTotalvalue = 0"!][!//
                  (uint16)0U,  /*Configured Transmit Buffer Length*/
                [!ELSE!][!//
                  (uint16)[!"$EthCtrlTxBufLenBytevalueActual"!]U,  /*Configured Transmit Buffer Length*/
                [!ENDIF!][!//
                [!IF "$EthTxBufTotalvalue = 0"!][!//
                  (uint16)0U,  /*Transmit Buffer Length 8 byte aligned*/
                [!ELSE!][!//
                  (uint16)[!"$EthCtrlTxBufLenBytevalue"!]U,  /*Transmit Buffer Length 8 byte aligned*/
                [!ENDIF!][!//
                 /* Properties of Ethernet Controller
                 Bit[0] - Port Select(PS)
                   0 for 1000Mbps
                   1 for 10 or 100 Mbps
                 Bit[1] - Speed(FES)
                   0 for 10 Mbps when PS bit is 1 and 1 Gbps when PS bit is 0
                   1 for 100 Mbps when PS bit is 1
                 Bit[2:4] - PhyInterface (000-MII, 100-RMII,001-RGMII)
                 Bit[5] - Mode of the Controller [0 - HALFDUPLEX, 1- FULLDUPLEX]
                 Bit[6] - Tx Interrupt Enable/Disable [0 - Disabled, 1- Enabled]
                 Bit[7] - Rx Interrupt Enable/Disable [0 - Disabled, 1- Enabled]
                 Bit[8] - CRC Stripping Enable/Disable [0 - Disabled, 1- Enabled]
                */
                (uint16)[!"$EthCtrlProperty"!],
                [!IF "$EthCtrlRxBufLenBytevalue = 0"!][!//
                  (uint16)0U,                               /*Total Receive Buffer*/
                [!ELSE!][!//
                  (uint8)[!"$EthRxBufTotalvalue"!]U,         /*Total Receive Buffer*/
                [!ENDIF!][!//
                [!IF "$EthCtrlTxBufLenBytevalue = 0"!][!//
                  (uint8)0U,                                /*Total Transmit Buffer*/
                [!ELSE!][!//
                  (uint8)[!"$EthTxBufTotalvalue"!]U,         /*Total Transmit Buffer*/
                [!ENDIF!][!//
                /* MAC address of the controller in network byte order */
                {
                  (uint8)0x[!"text:split($EthMACAddress, ':')[position() = 1]"!]U,
                  (uint8)0x[!"text:split($EthMACAddress, ':')[position() = 2]"!]U,
                  (uint8)0x[!"text:split($EthMACAddress, ':')[position() = 3]"!]U,
                  (uint8)0x[!"text:split($EthMACAddress, ':')[position() = 4]"!]U,
                  (uint8)0x[!"text:split($EthMACAddress, ':')[position() = 5]"!]U,
                  (uint8)0x[!"text:split($EthMACAddress, ':')[position() = 6]"!]U
                },
                    /* Eth Controller Index */
                (uint8)[!"$EthCtrlIdxTemp"!],
                /*DEM Id for Ethernet controller hardware test failure*/
                [!IF "(node:exists(./EthDemEventParameterRefs/*[1]/ETH_E_ACCESS/*[1]) = 'true') and (node:value(./EthDemEventParameterRefs/*[1]/ETH_E_ACCESS/*[1]) != ' ' )"!][!//
                  DemConf_DemEventParameter_[!"node:name(node:ref(node:value(./EthDemEventParameterRefs/*[1]/ETH_E_ACCESS/*[1])))"!],
                [!ELSE!][!//
                  ETH_17_GETHMAC_DISABLE_DEM_REPORT,
                [!ENDIF!][!//
                /*DEM Id for Ethernet controller Frames Lost Error*/
                [!IF "(node:exists(./EthDemEventParameterRefs/*[1]/ETH_E_RX_FRAMES_LOST/*[1]) = 'true') and (node:value(./EthDemEventParameterRefs/*[1]/ETH_E_RX_FRAMES_LOST/*[1]) != ' ' )"!][!//
                  DemConf_DemEventParameter_[!"node:name(node:ref(node:value(./EthDemEventParameterRefs/*[1]/ETH_E_RX_FRAMES_LOST/*[1])))"!],
                [!ELSE!][!//
                  ETH_17_GETHMAC_DISABLE_DEM_REPORT,
                [!ENDIF!][!//
                /*DEM Id for Ethernet controller Frames Alignment Error*/
                [!IF "(node:exists(./EthDemEventParameterRefs/*[1]/ETH_E_ALIGNMENT/*[1]) = 'true') and (node:value(./EthDemEventParameterRefs/*[1]/ETH_E_ALIGNMENT/*[1]) != ' ' )"!][!//
                  DemConf_DemEventParameter_[!"node:name(node:ref(node:value(./EthDemEventParameterRefs/*[1]/ETH_E_ALIGNMENT/*[1])))"!],
                [!ELSE!][!//
                  ETH_17_GETHMAC_DISABLE_DEM_REPORT,
                [!ENDIF!][!//
                /*DEM Id for Ethernet controller Frames CRC Error*/
                [!IF "(node:exists(./EthDemEventParameterRefs/*[1]/ETH_E_CRC/*[1]) = 'true') and (node:value(./EthDemEventParameterRefs/*[1]/ETH_E_CRC/*[1]) != ' ' )"!][!//
                  DemConf_DemEventParameter_[!"node:name(node:ref(node:value(./EthDemEventParameterRefs/*[1]/ETH_E_CRC/*[1])))"!],
                [!ELSE!][!//
                  ETH_17_GETHMAC_DISABLE_DEM_REPORT,
                [!ENDIF!][!//
                /*DEM Id for Ethernet controller  Undersize frame Error*/
                [!IF "(node:exists(./EthDemEventParameterRefs/*[1]/ETH_E_UNDERSIZEFRAME/*[1]) = 'true') and (node:value(./EthDemEventParameterRefs/*[1]/ETH_E_UNDERSIZEFRAME/*[1]) != ' ' )"!][!//
                  DemConf_DemEventParameter_[!"node:name(node:ref(node:value(./EthDemEventParameterRefs/*[1]/ETH_E_UNDERSIZEFRAME/*[1])))"!],
                [!ELSE!][!//
                  ETH_17_GETHMAC_DISABLE_DEM_REPORT,
                [!ENDIF!][!//
                /*DEM Id for Ethernet controller  Oversize frame Error*/
                [!IF "(node:exists(./EthDemEventParameterRefs/*[1]/ETH_E_OVERSIZEFRAME/*[1]) = 'true') and (node:value(./EthDemEventParameterRefs/*[1]/ETH_E_OVERSIZEFRAME/*[1]) != ' ' )"!][!//
                  DemConf_DemEventParameter_[!"node:name(node:ref(node:value(./EthDemEventParameterRefs/*[1]/ETH_E_OVERSIZEFRAME/*[1])))"!],
                [!ELSE!][!//
                  ETH_17_GETHMAC_DISABLE_DEM_REPORT,
                [!ENDIF!][!//
                /*DEM Id for Ethernet controller Single collision Error*/
                [!IF "(node:exists(./EthDemEventParameterRefs/*[1]/ETH_E_SINGLECOLLISION/*[1]) = 'true') and (node:value(./EthDemEventParameterRefs/*[1]/ETH_E_SINGLECOLLISION/*[1]) != ' ' )"!][!//
                  DemConf_DemEventParameter_[!"node:name(node:ref(node:value(./EthDemEventParameterRefs/*[1]/ETH_E_SINGLECOLLISION/*[1])))"!],
                [!ELSE!][!//
                  ETH_17_GETHMAC_DISABLE_DEM_REPORT,
                [!ENDIF!][!//
                /*DEM Id for Ethernet controller Multiple collision Error*/
                [!IF "(node:exists(./EthDemEventParameterRefs/*[1]/ETH_E_MULTIPLECOLLISION/*[1]) = 'true') and (node:value(./EthDemEventParameterRefs/*[1]/ETH_E_MULTIPLECOLLISION/*[1]) != ' ' )"!][!//
                  DemConf_DemEventParameter_[!"node:name(node:ref(node:value(./EthDemEventParameterRefs/*[1]/ETH_E_MULTIPLECOLLISION/*[1])))"!],
                [!ELSE!][!//
                  ETH_17_GETHMAC_DISABLE_DEM_REPORT,
                [!ENDIF!][!//
                /*DEM Id for Ethernet controller Late collision Error*/
                [!IF "(node:exists(./EthDemEventParameterRefs/*[1]/ETH_E_LATECOLLISION/*[1]) = 'true') and (node:value(./EthDemEventParameterRefs/*[1]/ETH_E_LATECOLLISION/*[1]) != ' ' )"!][!//
                  DemConf_DemEventParameter_[!"node:name(node:ref(node:value(./EthDemEventParameterRefs/*[1]/ETH_E_LATECOLLISION/*[1])))"!],
                [!ELSE!][!//
                  ETH_17_GETHMAC_DISABLE_DEM_REPORT,
                [!ENDIF!][!//
                [!ENDINDENT!][!//
                },
                [!ENDINDENT!][!//
            [!ENDIF!][!//
          [!ENDSELECT!][!//
        [!ENDIF!][!//
      [!ENDFOR!][!//
      };
      /* Structure to store core[!"$CoreId"!] configuration data */
      [!/*[cover parentID={CD05F9DB-4692-41dd-A4A4-8FDF9EB121F8}][/cover]*/!][!//
      [!IF "$VariantsConfigured = num:i(1)"!][!//
        static const Eth_17_GEthMac_CoreConfigType Eth_17_GEthMac_ConfigCore[!"$CoreId"!]_[!"$PredefinedVarName"!] =
      [!ELSE!][!//
        static const Eth_17_GEthMac_CoreConfigType Eth_17_GEthMac_ConfigCore[!"$CoreId"!] =
      [!ENDIF!][!//
      {
      [!INDENT "2"!][!//
      /* Starting address of the controller configuration for core[!"$CoreId"!] */
      /* MISRA2012_RULE_11_8_JUSTIFICATION: No side effects foreseen
      * by violating this MISRA rule */
      /* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32 chars.
        in generated code due to Autosar Naming constraints.*/
      /* MISRA2012_RULE_5_2_JUSTIFICATION: External identifiers going beyond 32 chars.
        in generated code due to Autosar Naming constraints.*/
      /* MISRA2012_RULE_5_4_JUSTIFICATION: External identifiers going beyond 32 chars.
        in generated code due to Autosar Naming constraints.*/
      /* MISRA2012_RULE_5_5_JUSTIFICATION: External identifiers going beyond 32 chars.
        in generated code due to Autosar Naming constraints.*/
      [!IF "$VariantsConfigured = num:i(1)"!][!//
        (Eth_17_GEthMac_CoreCntrlConfigType*)Eth_17_GEthMac_CoreCntrlConfigCore[!"$CoreId"!]_[!"$PredefinedVarName"!],
      [!ELSE!][!//
        (Eth_17_GEthMac_CoreCntrlConfigType*)Eth_17_GEthMac_CoreCntrlConfigCore[!"$CoreId"!],
      [!ENDIF!][!//
      [!"num:i($MaxControllersCore)"!]U /* Maximum controllers allocated to core[!"$CoreId"!] */
      [!ENDINDENT!][!//
      };
      /* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32 chars.
        in generated code due to Autosar Naming constraints.*/
      /* MISRA2012_RULE_5_2_JUSTIFICATION: External identifiers going beyond 32 chars.
        in generated code due to Autosar Naming constraints.*/
      /* MISRA2012_RULE_5_4_JUSTIFICATION: External identifiers going beyond 32 chars.
        in generated code due to Autosar Naming constraints.*/
      /* MISRA2012_RULE_5_5_JUSTIFICATION: External identifiers going beyond 32 chars.
        in generated code due to Autosar Naming constraints.*/
      #define ETH_17_GETHMAC_STOP_SEC_CONFIG_DATA_QM_CORE[!"$CoreId"!]_UNSPECIFIED
      /* MISRA2012_RULE_4_10_JUSTIFICATION: Memmap header is repeatedly included
         without safeguard. It complies to Autosar guidelines. */
      /* MISRA2012_RULE_20_1_JUSTIFICATION: Declaration of notification function
        before MemMap inclusion It complies to Autosar guidelines. */
      #include "Eth_17_GEthMac_MemMap.h"

    [!ENDIF!][!//
  [!ENDFOR!][!//
  /*
            Ethernet driver configuration root structure
  */
  /* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32 chars.
    in generated code due to Autosar Naming constraints.*/
  /* MISRA2012_RULE_5_2_JUSTIFICATION: External identifiers going beyond 32 chars.
    in generated code due to Autosar Naming constraints.*/
  /* MISRA2012_RULE_5_4_JUSTIFICATION: External identifiers going beyond 32 chars.
    in generated code due to Autosar Naming constraints.*/
  /* MISRA2012_RULE_5_5_JUSTIFICATION: External identifiers going beyond 32 chars.
    in generated code due to Autosar Naming constraints.*/
  #define ETH_17_GETHMAC_START_SEC_CONFIG_DATA_QM_GLOBAL_UNSPECIFIED
  /* MISRA2012_RULE_4_10_JUSTIFICATION: Memmap header is repeatedly included
     without safeguard. It complies to Autosar guidelines. */
     /* MISRA2012_RULE_20_1_JUSTIFICATION: Memmap header usage as per Autosar
    guideline. */
  #include "Eth_17_GEthMac_MemMap.h"
  [!/*[cover parentID={8EFA36FA-6DD0-481e-A6DF-720A634D9D89}][/cover]*/!][!//
  [!VAR "Module" = "'ETH'"!][!//
  [!CALL "ETH_GenerateModuleMap", "Module" = "'ETH'"!][!//
  [!CALL "ETH_GetMasterCoreID"!][!//
  [!IF "$VariantsConfigured = num:i(1)"!]
    const Eth_17_GEthMac_ConfigType Eth_17_GEthMac_Config_[!"$PredefinedVarName"!] =
  [!ELSE!]
    const Eth_17_GEthMac_ConfigType Eth_17_GEthMac_Config =
  [!ENDIF!]
  {
  [!INDENT "2"!][!//
  /* starting address of Core<x> Configuration data */
  {
  [!INDENT "4"!][!//
  [!FOR "CoreId" = "num:i(0)" TO "num:i(ecu:get('Mcu.NoOfCoreAvailable')) - num:i(1)"!][!//
    [!VAR "TempCoreId" = "concat('CORE',$CoreId)"!][!//
    [!VAR "MaxControllersCore" = "num:i(0)"!][!//
    [!FOR "ControllerID" = "num:i(0)" TO "num:i($MaxControllers) - num:i(1)"!][!//
      [!IF "node:exists(EthConfigSet/*[1]/EthCtrlConfig/*[EthCtrlIdx = num:i($ControllerID)]) = 'true'"!][!//
        [!SELECT "EthConfigSet/*[1]/EthCtrlConfig/*[EthCtrlIdx = num:i($ControllerID)]"!][!//
          [!VAR "NodeName" = "node:name(.)"!][!//
          [!VAR "EthCtrlIdx" = "./EthCtrlIdx"!][!//
          [!CALL "ETH_ValidateChAllocation", "CoreNumber" = "$CoreId", "Channel" = "$NodeName"!][!//
          [!IF "$CGAllocationResult = 'TRUE'"!][!//
            [!NOCODE!][!//
              [!VAR "MaxControllersCore" = "$MaxControllersCore + num:i(1)"!][!//
            [!ENDNOCODE!][!//
          [!ENDIF!][!//
        [!ENDSELECT!][!//
      [!ENDIF!][!//
    [!ENDFOR!][!//
    [!IF "$MaxControllersCore != num:i(0)"!][!//
      /* MISRA2012_RULE_11_8_JUSTIFICATION: No side effects foreseen
       * by violating this MISRA rule */
      [!IF "$VariantsConfigured = num:i(1)"!][!//
        (Eth_17_GEthMac_CoreConfigType*)&Eth_17_GEthMac_ConfigCore[!"$CoreId"!]_[!"$PredefinedVarName"!][!IF "$CoreId < num:i(ecu:get('Mcu.NoOfCoreAvailable')) - num:i(1)"!],[!ENDIF!][!CR!]
      [!ELSE!][!//
        (Eth_17_GEthMac_CoreConfigType*)&Eth_17_GEthMac_ConfigCore[!"$CoreId"!][!IF "$CoreId < num:i(ecu:get('Mcu.NoOfCoreAvailable')) - num:i(1)"!],[!ENDIF!][!CR!]
      [!ENDIF!]
       /* MISRA2012_RULE_11_8_JUSTIFICATION: No side effects foreseen
       * by violating this MISRA rule */
      [!ELSE!]
        NULL_PTR[!IF "$CoreId < num:i(ecu:get('Mcu.NoOfCoreAvailable')) - num:i(1)"!],[!ENDIF!][!CR!]
    [!ENDIF!]
  [!ENDFOR!]
  [!ENDINDENT!][!//
  },
  /* Address of index mapping array */
  [!IF "$VariantsConfigured = num:i(1)"!][!//
    (uint8*)Eth_17_GEthMac_ControllerIndexMap_[!"$PredefinedVarName"!]
  [!ELSE!][!//
    (uint8*)Eth_17_GEthMac_ControllerIndexMap
  [!ENDIF!][!//
    /* MISRA2012_RULE_11_8_JUSTIFICATION: No side effects foreseen
   * by violating this MISRA rule */
   [!ENDINDENT!][!//
  };
  /* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32 chars.
    in generated code due to Autosar Naming constraints.*/
  /* MISRA2012_RULE_5_2_JUSTIFICATION: External identifiers going beyond 32 chars.
    in generated code due to Autosar Naming constraints.*/
  /* MISRA2012_RULE_5_4_JUSTIFICATION: External identifiers going beyond 32 chars.
    in generated code due to Autosar Naming constraints.*/
  /* MISRA2012_RULE_5_5_JUSTIFICATION: External identifiers going beyond 32 chars.
    in generated code due to Autosar Naming constraints.*/
  #define ETH_17_GETHMAC_STOP_SEC_CONFIG_DATA_QM_GLOBAL_UNSPECIFIED
  /* MISRA2012_RULE_4_10_JUSTIFICATION: Memmap header is repeatedly included
     without safeguard. It complies to Autosar guidelines. */
  /* MISRA2012_RULE_20_1_JUSTIFICATION: Memmap header usage as per Autosar
    guideline. */
  #include "Eth_17_GEthMac_MemMap.h"
[!ENDSELECT!][!//
[!ENDINDENT!][!//