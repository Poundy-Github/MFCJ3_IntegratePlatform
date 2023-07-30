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
*******************************************************************************
**                                                                            **
**  FILENAME    : Eth_17_GEthMac_Cfg.h                                        **
**                                                                            **
**  VERSION     : 1.30.0_16.0.0                                               **
**                                                                            **
**  DATE        : 2019-09-10                                                  **
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
**  TRACEABILITY : [cover parentID]                                           **
**                                                                            **
**  DESCRIPTION : This file contains                                          **
**                Code template for Eth_17_EthMac_Cfg.h file                  **
**                                                                            **
**  [/cover]                                                                  **
**                                                                            **
**  SPECIFICATION(S) : Specification of Eth Driver, AUTOSAR Release 4.2.2     **
**                                                                            **
**  MAY BE CHANGED BY USER : no                                               **
**                                                                            **
*************************************************************************/!][!//
[!//
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
**  FILENAME  : Eth_17_GEthMac_Cfg.h                                          **
**                                                                            **
**  VERSION   : 1.30.0_16.0.0                                                 **
**                                                                            **
**  DATE, TIME: [!"$date"!], [!"$time"!]      !!!IGNORE-LINE!!!                   **
**                                                                            **
**  GENERATOR : Build [!"$buildnr"!]          !!!IGNORE-LINE!!!                 **
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
[!/*
[cover parentID={9175D751-BD32-4da8-B016-DEF1B24823F0}][/cover]
*/!][!//
#ifndef ETH_17_GETHMAC_CFG_H
#define ETH_17_GETHMAC_CFG_H
[!INDENT "0"!][!//
  [!NOCODE!]
    [!INCLUDE "Eth_17_GEthMac.m"!][!//
  [!ENDNOCODE!]
  /*******************************************************************************
  **                      Includes                                              **
  *******************************************************************************/

  /*******************************************************************************
  **                      Global Macro Definitions                              **
  *******************************************************************************/
  [!/*
  [cover parentID={D658C1EB-7EA9-4748-9169-E3A2B9A13039}][/cover]
  */!][!//
  [!/*
  [cover parentID={DCEA0655-94F2-4367-95CF-88822D502F89}][/cover]
  */!][!//
  [!/*
  [cover parentID={1754662B-0773-4b17-A136-818FE286F0B3}][/cover]
  */!][!//
  [!/*
  [cover parentID={6963F774-4814-4aa5-843D-5B27938206A4}][/cover]
  */!][!//
  [!/*
  [cover parentID={42C82309-510D-4e83-BC27-B3BD0E6A8908}][/cover]
  */!][!//
  [!/*
  [cover parentID={9F5D2728-21C1-401f-B3A0-0C3307D7FA60}][/cover]
  */!][!//
  [!/*
  [cover parentID={5A365733-2164-426e-BD2D-F74D9D726CCD}][/cover]
  */!][!//
  [!AUTOSPACING!]
  [!VAR "MajorVersion" = "text:split($moduleReleaseVer, '.')[position()-1 = 0]"!][!//
  [!VAR "MinorVersion" = "text:split($moduleReleaseVer, '.')[position()-1 = 1]"!][!//
  [!VAR "RevisionVersion" = "text:split($moduleReleaseVer, '.')[position()-1 = 2]"!][!//
  #define ETH_17_GETHMAC_AR_RELEASE_MAJOR_VERSION      ([!"$MajorVersion"!]U)
  #define ETH_17_GETHMAC_AR_RELEASE_MINOR_VERSION      ([!"$MinorVersion"!]U)
  #define ETH_17_GETHMAC_AR_RELEASE_REVISION_VERSION   ([!"$RevisionVersion"!]U)

  [!VAR "SwMajorVersion" = "text:split($moduleSoftwareVer, '.')[position()-1 = 0]"!][!//
  [!VAR "SwMinorVersion" = "text:split($moduleSoftwareVer, '.')[position()-1 = 1]"!][!//
  [!VAR "SwPatchVersion" = "text:split($moduleSoftwareVer, '.')[position()-1 = 2]"!][!//
  #define ETH_17_GETHMAC_SW_MAJOR_VERSION              ([!"$SwMajorVersion"!]U)
  #define ETH_17_GETHMAC_SW_MINOR_VERSION              ([!"$SwMinorVersion"!]U)
  #define ETH_17_GETHMAC_SW_PATCH_VERSION              ([!"$SwPatchVersion"!]U)
  [!/* Select MODULE-CONFIGURATION as context-node */!][!//
  [!SELECT "as:modconf('Eth')[1]"!][!//
    [!//

    [!/*
    [cover parentID={2E77BC35-0888-4563-A909-392E775E8BF5}][/cover]
    */!][!//
    /*
    Configuration: ETH_17_GETHMAC_DEV_ERROR_DETECT
    - if STD_ON, DET is Enabled
    - if STD_OFF,DET is Disabled
       This parameter shall activate or
    deactivate the detection of all development errors.
    */
    #define ETH_17_GETHMAC_DEV_ERROR_DETECT  ([!//
    [!IF "EthGeneral/EthDevErrorDetect = 'true'"!][!//
      STD_ON[!//
    [!ELSE!][!//
      STD_OFF[!//
    [!ENDIF!][!//
    )

    [!/*
    [cover parentID={8DE29969-456D-442c-AB9A-E3CE23A1B3CA}][/cover]
    */!][!//
    /*
    Configuration: ETH_17_GETHMAC_VERSION_INFO_API
    - if STD_ON, Function Eth_17_GetVersionInfo is available
    - if STD_OFF,Function Eth_17_GetVersionInfo is not available
    */
    #define ETH_17_GETHMAC_VERSION_INFO_API  ([!//
    [!IF "EthGeneral/EthVersionInfoApi = 'true'"!][!//
      STD_ON[!//
    [!ELSE!][!//
      STD_OFF[!//
    [!ENDIF!][!//
    )

    [!/*
    [cover parentID={A809ED84-1425-4b24-B856-583715490717}][/cover]
    */!][!//
    [!VAR "MaxControllers"= "ecu:get('Eth.EthAvaliableNodes')"!][!//
    [!FOR "ConfigId" = "num:i(0)" TO "num:i($MaxControllers) - num:i(1)"!][!//
      [!IF "node:exists(EthConfigSet/*[1]/EthCtrlConfig/*[EthCtrlIdx = num:i($ConfigId)]) = 'true'"!][!//
        [!SELECT "EthConfigSet/*[1]/EthCtrlConfig/*[EthCtrlIdx = num:i($ConfigId)]"!][!//
          /* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32 chars.
            in generated code due to Autosar Naming constraints.*/
          /* MISRA2012_RULE_5_2_JUSTIFICATION: External identifiers going beyond 32 chars.
            in generated code due to Autosar Naming constraints.*/
          /* MISRA2012_RULE_5_4_JUSTIFICATION: External identifiers going beyond 32 chars.
            in generated code due to Autosar Naming constraints.*/
          /* MISRA2012_RULE_5_5_JUSTIFICATION: External identifiers going beyond 32 chars.
            in generated code due to Autosar Naming constraints.*/
          #ifndef Eth_17_GEthMacConf_EthCtrlConfig_[!"node:name(.)"!]
          /* Macro to hold index of the configured controller */
          /* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32 chars.
            in generated code due to Autosar Naming constraints.*/
          /* MISRA2012_RULE_5_2_JUSTIFICATION: External identifiers going beyond 32 chars.
            in generated code due to Autosar Naming constraints.*/
          /* MISRA2012_RULE_5_4_JUSTIFICATION: External identifiers going beyond 32 chars.
            in generated code due to Autosar Naming constraints.*/
          /* MISRA2012_RULE_5_5_JUSTIFICATION: External identifiers going beyond 32 chars.
            in generated code due to Autosar Naming constraints.*/
          #define Eth_17_GEthMacConf_EthCtrlConfig_[!"node:name(.)"!] ([!//
          [!"num:i(node:value(./EthCtrlIdx))"!]U)
          #endif
        [!ENDSELECT!][!//
      [!ENDIF!][!//
    [!ENDFOR!][!//
    [!/*
    [cover parentID={D108369D-DA09-42f0-82F7-4A56F045E2CB}][/cover]
    */!][!//
    /*
    Configuration: ETH_17_GETHMAC_INDEX
    - Ethernet Driver Instance ID, used in DET_Report(.,.) Interface.
    */
    #define ETH_17_GETHMAC_INDEX ([!//
    [!"num:i(node:value(EthGeneral/EthIndex))"!]U)
    [!NOCODE!]
      [!VAR "TotalConfig" = "num:i(count(EthConfigSet/*))"!][!//
      [!VAR "EthCtrlEnableMiiApi" = "num:i(0)"!][!//
      [!VAR "EthDemEnabled" = "num:i(0)"!][!//
      [!FOR "ConfigId" = "num:i(1)" TO "num:i($TotalConfig)"!][!//
        [!SELECT "EthConfigSet/*[num:i($ConfigId)]"!][!//
          [!FOR "ControllerId" = "num:i(0)" TO "num:i($MaxControllers) - num:i(1)"!][!//
            [!IF "node:exists(EthCtrlConfig/*[EthCtrlIdx = num:i($ControllerId)]) = 'true'"!]
              [!SELECT "EthCtrlConfig/*[EthCtrlIdx = num:i($ControllerId)]"!][!//
                [!VAR "EthCtrlEnableMiiApiTemp1" = "./EthCtrlEnableMii"!][!//
                [!VAR "EthCtrlIndexTemp1" = "./EthCtrlIdx"!][!//
                [!IF "./EthCtrlEnableMii = 'true'"!][!//
                  [!VAR "EthCtrlEnableMiiApi" = "num:i(1)"!][!//
                [!ENDIF!][!//
                [!FOR "ControllerId1" = "num:i(0)" TO "num:i($MaxControllers)-num:i(1)"!][!//
                  [!IF "node:exists(../*[EthCtrlIdx = num:i($ControllerId1)]) = 'true'"!]
                    [!SELECT "../*[EthCtrlIdx = num:i($ControllerId1)]"!][!//
                      [!VAR "EthCtrlEnableMiiApiTemp2" = "./EthCtrlEnableMii"!][!//
                      [!VAR "EthCtrlIndexTemp2" = "./EthCtrlIdx"!][!//
                      [!IF "$EthCtrlIndexTemp2 != $EthCtrlIndexTemp1"!][!//
                        [!IF "$EthCtrlEnableMiiApiTemp2 != $EthCtrlEnableMiiApiTemp1"!][!//
                          [!ERROR!]
                            ERROR: Select or Unselect EthCtrlEnableMii parmeter for all the controllers [!"@name"!].
                          [!ENDERROR!]
                        [!ENDIF!][!//
                      [!ENDIF!][!//
                    [!ENDSELECT!][!//
                  [!ENDIF!][!//
                [!ENDFOR!][!//
                [!IF "(node:exists(./EthDemEventParameterRefs/*[1]/ETH_E_ACCESS/*[1]) = 'true') and (node:value(./EthDemEventParameterRefs/*[1]/ETH_E_ACCESS/*[1]) != '' )"!][!//
                  [!VAR "EthDemEnabled" = "num:i(1)"!][!//
                [!ENDIF!][!//
                [!IF "(node:exists(./EthDemEventParameterRefs/*[1]/ETH_E_RX_FRAMES_LOST/*[1]) = 'true') and (node:value(./EthDemEventParameterRefs/*[1]/ETH_E_RX_FRAMES_LOST/*[1]) != '' )"!][!//
                  [!VAR "EthDemEnabled" = "num:i(1)"!][!//
                [!ENDIF!][!//
                [!IF "(node:exists(./EthDemEventParameterRefs/*[1]/ETH_E_CRC/*[1]) = 'true') and (node:value(./EthDemEventParameterRefs/*[1]/ETH_E_CRC/*[1]) != '' )"!][!//
                  [!VAR "EthDemEnabled" = "num:i(1)"!][!//
                [!ENDIF!][!//
                [!IF "(node:exists(./EthDemEventParameterRefs/*[1]/ETH_E_UNDERSIZEFRAME/*[1]) = 'true') and (node:value(./EthDemEventParameterRefs/*[1]/ETH_E_UNDERSIZEFRAME/*[1]) != '' )"!][!//
                  [!VAR "EthDemEnabled" = "num:i(1)"!][!//
                [!ENDIF!][!//
                [!IF "(node:exists(./EthDemEventParameterRefs/*[1]/ETH_E_OVERSIZEFRAME/*[1]) = 'true') and (node:value(./EthDemEventParameterRefs/*[1]/ETH_E_OVERSIZEFRAME/*[1]) != '' )"!][!//
                  [!VAR "EthDemEnabled" = "num:i(1)"!][!//
                [!ENDIF!][!//
                [!IF "(node:exists(./EthDemEventParameterRefs/*[1]/ETH_E_ALIGNMENT/*[1]) = 'true') and (node:value(./EthDemEventParameterRefs/*[1]/ETH_E_ALIGNMENT/*[1]) != '' )"!][!//
                  [!VAR "EthDemEnabled" = "num:i(1)"!][!//
                [!ENDIF!][!//
                [!IF "(node:exists(./EthDemEventParameterRefs/*[1]/ETH_E_SINGLECOLLISION/*[1]) = 'true') and (node:value(./EthDemEventParameterRefs/*[1]/ETH_E_SINGLECOLLISION/*[1]) != '' )"!][!//
                  [!VAR "EthDemEnabled" = "num:i(1)"!][!//
                [!ENDIF!][!//
                [!IF "(node:exists(./EthDemEventParameterRefs/*[1]/ETH_E_MULTIPLECOLLISION/*[1]) = 'true') and (node:value(./EthDemEventParameterRefs/*[1]/ETH_E_MULTIPLECOLLISION/*[1]) != '' )"!][!//
                  [!VAR "EthDemEnabled" = "num:i(1)"!][!//
                [!ENDIF!][!//
                [!IF "(node:exists(./EthDemEventParameterRefs/*[1]/ETH_E_LATECOLLISION/*[1]) = 'true') and (node:value(./EthDemEventParameterRefs/*[1]/ETH_E_LATECOLLISION/*[1]) != '' )"!][!//
                  [!VAR "EthDemEnabled" = "num:i(1)"!][!//
                [!ENDIF!][!//
              [!ENDSELECT!][!//
            [!ENDIF!][!//
          [!ENDFOR!][!//
        [!ENDSELECT!][!//
      [!ENDFOR!][!//
    [!ENDNOCODE!]
    [!/*
    [cover parentID={99257CFF-30EC-41b0-AF4C-5D417D32184D}][/cover]
    */!][!//
    /*
    Configuration: ETH_17_GETHMAC_ENA_MII_API
    - if STD_ON, Functions Eth_17_WriteMii,Eth_17_ReadMii are available
    - if STD_OFF,Functions Eth_17_WriteMii,Eth_17_ReadMii are not available
    */
    #define ETH_17_GETHMAC_ENA_MII_API  ([!//
    [!IF "$EthCtrlEnableMiiApi = num:i(1)"!][!//
      STD_ON[!//
    [!ELSE!][!//
      STD_OFF[!//
    [!ENDIF!][!//
    )
    [!/*
    [cover parentID={114AAF4A-9A14-44af-8CE3-3CF85DFF3484}][/cover]
    */!][!//
    /*
    Configuration:  ETH_17_GETHMAC_DEM_ENABLED
    ETH_17_GETHMAC_ENABLE_DEM_REPORT - Dem reporting enabled.
    ETH_17_GETHMAC_DISABLE_DEM_REPORT - Dem reporting disabled
    */
    #define ETH_17_GETHMAC_DEM_ENABLED  ([!//
    [!IF "$EthDemEnabled = num:i(1)"!][!//
      ETH_17_GETHMAC_ENABLE_DEM_REPORT[!//
    [!ELSE!][!//
      ETH_17_GETHMAC_DISABLE_DEM_REPORT[!//
    [!ENDIF!][!//
    )
    [!/*
    [cover parentID={557C98B5-9231-45e3-BC7A-3A9E5E7E0578}][/cover]
    */!][!//
    /* Maximum time in nanoseconds to wait for hardware timeout errors*/
    #define ETH_17_GETHMAC_MAXTIMEOUT_COUNT  ([!//
    [!"num:i(node:value(EthGeneral/EthTimeoutCount))"!][!//
    U)

    [!VAR "TxBuffer"= "num:i(0)"!][!//
    [!VAR "RxBuffer"= "num:i(0)"!][!//
    [!SELECT "EthConfigSet/*[1]"!][!//
      [!FOR "ControllerId" = "num:i(0)" TO "num:i($MaxControllers) - num:i(1)"!][!//
        [!IF "node:exists(EthCtrlConfig/*[EthCtrlIdx = num:i($ControllerId)]) = 'true'"!]
          [!SELECT "EthCtrlConfig/*[EthCtrlIdx = num:i($ControllerId)]"!][!//
            [!NOCODE!][!//
              /* Rx buffer memory is allocated as 8 byte aligned for optimal performance.
                 Total Rx memory allocates = Size of one 8 byte aligned buffer * Number of Buffers. */
              [!VAR "EthCtrlRxBufLenBytevalue" = "./EthCtrlRxBufLenByte"!][!//
              [!VAR "RxBufQuotient" = "num:i($EthCtrlRxBufLenBytevalue) div 8"!][!//
              [!IF "num:i($EthCtrlRxBufLenBytevalue) mod 8 != 0"!][!//
                [!VAR "EthCtrlRxBufLenBytevalue" = "(num:i($RxBufQuotient) + 1) * 8"!][!//
              [!ENDIF!]!][!//
              [!VAR "EthRxBufTotalvalue" = "./EthRxBufTotal"!][!//
              [!VAR "RxBuffer" = "(string(num:i($EthCtrlRxBufLenBytevalue) * num:i($EthRxBufTotalvalue)))"!][!//

              /* Tx buffer memory is allocated as 8 byte aligned for optimal performance.
                 Total Tx memory allocates = Size of one 8 byte aligned buffer * Number of Buffers. */
              [!VAR "EthCtrlTxBufLenBytevalue" = "./EthCtrlTxBufLenByte"!][!//
              [!VAR "TxBufQuotient" = "num:i($EthCtrlTxBufLenBytevalue) div 8"!][!//
              [!IF "num:i($EthCtrlTxBufLenBytevalue) mod 8 != 0"!][!//
                [!VAR "EthCtrlTxBufLenBytevalue" = "(num:i($TxBufQuotient) + 1) * 8"!][!//
              [!ENDIF!]!][!//
              [!VAR "EthTxBufTotalvalue" = "./EthTxBufTotal"!][!//
              [!VAR "TxBuffer" = "(string(num:i($EthCtrlTxBufLenBytevalue) * num:i($EthTxBufTotalvalue)))"!][!//
            [!ENDNOCODE!][!//
            [!/*
            [cover parentID={70E506DF-289C-4f17-9939-8E693FBEF5F1}][/cover]
            */!][!//
            [!/*
            [cover parentID={336AD0EF-41DF-4a79-9567-C67009C30581}][/cover]
            */!][!//
            /* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32 chars.
              in generated code due to Autosar Naming constraints.*/
            /* MISRA2012_RULE_5_2_JUSTIFICATION: External identifiers going beyond 32 chars.
              in generated code due to Autosar Naming constraints.*/
            /* MISRA2012_RULE_5_4_JUSTIFICATION: External identifiers going beyond 32 chars.
              in generated code due to Autosar Naming constraints.*/
            /* MISRA2012_RULE_5_5_JUSTIFICATION: External identifiers going beyond 32 chars.
              in generated code due to Autosar Naming constraints.*/
            /* No of receive buffer for controller[!"./EthCtrlIdx"!] */
            [!IF "(./EthRxBufTotal = 0 ) or ($RxBuffer = 0 )"!][!//
              #define ETH_17_GETHMAC_CNTRL[!"./EthCtrlIdx"!]_RXBUFFER_COUNT      (1U)
            [!ELSE!][!//
              #define ETH_17_GETHMAC_CNTRL[!"./EthCtrlIdx"!]_RXBUFFER_COUNT      ([!"num:max(./EthRxBufTotal)"!]U)
            [!ENDIF!][!//
            /* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32 chars.
              in generated code due to Autosar Naming constraints.*/
            /* MISRA2012_RULE_5_2_JUSTIFICATION: External identifiers going beyond 32 chars.
              in generated code due to Autosar Naming constraints.*/
            /* MISRA2012_RULE_5_4_JUSTIFICATION: External identifiers going beyond 32 chars.
              in generated code due to Autosar Naming constraints.*/
            /* MISRA2012_RULE_5_5_JUSTIFICATION: External identifiers going beyond 32 chars.
              in generated code due to Autosar Naming constraints.*/
            /* Size of the receive buffer for controller[!"./EthCtrlIdx"!] */
            [!IF "($RxBuffer = 0 )"!][!//
              #define ETH_17_GETHMAC_CNTRL[!"./EthCtrlIdx"!]_RXBUFFER_SIZE       (1U)
            [!ELSE!][!//
              #define ETH_17_GETHMAC_CNTRL[!"./EthCtrlIdx"!]_RXBUFFER_SIZE       ([!"string($RxBuffer)"!]U)
            [!ENDIF!][!//

            [!/*
            [cover parentID={F295F2DC-DABB-45a2-9625-BAC48EDAFE4B}][/cover]
            */!][!//
            [!/*
            [cover parentID={6B738DCE-C03B-4fb7-A29C-73433787349B}][/cover]
            */!][!//
            /* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32 chars.
              in generated code due to Autosar Naming constraints.*/
            /* MISRA2012_RULE_5_2_JUSTIFICATION: External identifiers going beyond 32 chars.
              in generated code due to Autosar Naming constraints.*/
            /* MISRA2012_RULE_5_4_JUSTIFICATION: External identifiers going beyond 32 chars.
              in generated code due to Autosar Naming constraints.*/
            /* MISRA2012_RULE_5_5_JUSTIFICATION: External identifiers going beyond 32 chars.
              in generated code due to Autosar Naming constraints.*/
            /* No of transmit buffer for controller[!"./EthCtrlIdx"!] */
            [!IF "(./EthTxBufTotal = 0 ) or ($TxBuffer = 0 )"!][!//
              #define ETH_17_GETHMAC_CNTRL[!"./EthCtrlIdx"!]_TXBUFFER_COUNT      (1U)
            [!ELSE!][!//
              #define ETH_17_GETHMAC_CNTRL[!"./EthCtrlIdx"!]_TXBUFFER_COUNT      ([!"num:max(./EthTxBufTotal)"!]U)
            [!ENDIF!][!//
            /* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32 chars.
              in generated code due to Autosar Naming constraints.*/
            /* MISRA2012_RULE_5_2_JUSTIFICATION: External identifiers going beyond 32 chars.
              in generated code due to Autosar Naming constraints.*/
            /* MISRA2012_RULE_5_4_JUSTIFICATION: External identifiers going beyond 32 chars.
              in generated code due to Autosar Naming constraints.*/
            /* MISRA2012_RULE_5_5_JUSTIFICATION: External identifiers going beyond 32 chars.
              in generated code due to Autosar Naming constraints.*/
            /* Size of the transmit buffer for controller[!"./EthCtrlIdx"!] */
            [!IF "($TxBuffer = 0 )"!][!//
              #define ETH_17_GETHMAC_CNTRL[!"./EthCtrlIdx"!]_TXBUFFER_SIZE       (1U)
            [!ELSE!][!//
              #define ETH_17_GETHMAC_CNTRL[!"./EthCtrlIdx"!]_TXBUFFER_SIZE       ([!"string($TxBuffer)"!]U)
            [!ENDIF!][!//
            [!VAR "TxBuffer"= "num:i(0)"!][!//
            [!VAR "RxBuffer"= "num:i(0)"!][!//
            [!VAR "EthCtrlRxBufLenBytevalue"= "num:i(0)"!][!//
            [!VAR "EthCtrlTxBufLenBytevalue"= "num:i(0)"!][!//
            [!VAR "RxBufQuotient"= "num:i(0)"!][!//
            [!VAR "TxBufQuotient"= "num:i(0)"!][!//
          [!ENDSELECT!][!//
        [!ENDIF!][!//
      [!ENDFOR!][!//
    [!ENDSELECT!][!//
    [!/*
    [cover parentID={41A84D49-4152-4314-8CDA-6AE376AFA507}][/cover]
    */!][!//
    [!VAR "EthPeripheralBusFrequency" = "num:i(node:ref(./EthGeneral/EthPeripheralBusClock)/McuPllDistributionSettingConfig/McuSPBFrequency)"!][!//
    /* Clock configuration for MDIO - between 1.0 MHz to 2.5 MHz frequency. */
    #define ETH_17_GETHMAC_MDIO_ADDR_REG_CR_VAL  [!//
    [!IF "(($EthPeripheralBusFrequency >= 60000000) or ($EthPeripheralBusFrequency <= 100000000) )"!][!//
      (ETH_17_GETHMAC_CR60_100MHZ)[!//
    [!ELSEIF "(($EthPeripheralBusFrequency > 100000000) or ($EthPeripheralBusFrequency <=150000000) )"!][!//
      (ETH_17_GETHMAC_CR100_150MHZ)[!//
    [!ELSEIF "(($EthPeripheralBusFrequency > 150000000) or ($EthPeripheralBusFrequency <=250000000) )"!][!//
      (ETH_17_GETHMAC_CR150_250MHZ)[!//
    [!ELSEIF "(($EthPeripheralBusFrequency > 250000000) or ($EthPeripheralBusFrequency <=300000000) )"!][!//
      (ETH_17_GETHMAC_CR250_300MHZ)[!//
    [!ELSE!]
      #error Invalid Mcu PeripheralBusFrequency in McuModuleConfiguration
    [!ENDIF!][!//

    [!/*
    [cover parentID={7136EE64-9265-4ec5-9551-A171A210D76F}][/cover]
    */!][!//
    /* fSPB (SPB frequency) period in nanoseconds */
    [!VAR "EthSpbPeriodInNanoSeconds" = "num:i((1000000000) div num:i($EthPeripheralBusFrequency))"!][!//
    #define ETH_17_GETHMAC_FSPB_PERIOD_IN_NANOSEC   ([!"$EthSpbPeriodInNanoSeconds"!]U)

    [!/*
    [cover parentID={7F19052C-DAA2-46cc-9EBA-19E7EA709EFD}][/cover]
    */!][!//
    /* fGETH frequency in Hz - basic frequency for the Gigabit Ethernet Kernel */
    [!VAR "EthOperateFrequency" = "num:i(node:ref(./EthGeneral/EthOperationFrequency)/McuPllDistributionSettingConfig/McuGEthFrequency)"!][!//
    [!IF "($EthOperateFrequency < 60000000)"!][!//
      [!ERROR!][!//
        Error :Invalid Gigabit Ethernet kernel frequency in McuModuleConfiguration .Supported frequency: >= 60MHz
      [!ENDERROR!][!//
    [!ENDIF!][!//
    #define ETH_17_GETHMAC_FGETH_IN_HZ              ([!"$EthOperateFrequency"!]U)

    [!/*
    [cover parentID={16E3273C-D568-4b30-9AEE-4D32E82030E8}][/cover]
    */!][!//
    /* Wait time in nanoseconds after a kernel reset in RGMII mode */
    #define ETH_17_GETHMAC_KRNLRST_RGMII_WAITCNT    ([!"num:i(ceiling(num:i(35) * ($EthSpbPeriodInNanoSeconds)))"!]U)

    [!/*
    [cover parentID={2695D50E-FE4E-4316-8D6F-32C25FD5C65B}][/cover]
    */!][!//
    /* Wait time in nanoseconds after a kernel reset in MII/ RMII mode */
    #define ETH_17_GETHMAC_KRNLRST_MII_WAITCNT      ([!"num:i(ceiling(num:i(70) * ($EthSpbPeriodInNanoSeconds)))"!]U)

    [!/*
    [cover parentID={AD378ADD-05C0-4141-87FB-B48FFA585843}][/cover]
    */!][!//
    /*
    Configuration: ETH_17_GETHMAC_GETDROPCOUNT_API
    - if STD_ON, Function Eth_17_GEthMac_GetDropCount is available
    - if STD_OFF,Function Eth_17_GEthMac_GetDropCount is not available
    */
    [!IF "EthGeneral/EthGetDropCountApi = 'true'"!][!//
      #define  ETH_17_GETHMAC_GETDROPCOUNT_API    (STD_ON)
    [!ELSE!][!//
      #define  ETH_17_GETHMAC_GETDROPCOUNT_API    (STD_OFF)
    [!ENDIF!][!//
    [!/*
    [cover parentID={1C5AE504-9DA1-46ae-A5B9-0EEB0D5AA296}][/cover]
    */!][!//
    /*
    Configuration: ETH_17_GETHMAC_GETETHERSTATS_API
    - if STD_ON, Function Eth_17_GEthMac_GetEtherStats is available
    - if STD_OFF,Function Eth_17_GEthMac_GetEtherStats is not available
    */
    [!IF "EthGeneral/EthGetEtherStatsApi   = 'true'"!][!//
      #define  ETH_17_GETHMAC_GETETHERSTATS_API   (STD_ON)
    [!ELSE!][!//
      #define  ETH_17_GETHMAC_GETETHERSTATS_API   (STD_OFF)
    [!ENDIF!][!//

    [!/*
    [cover parentID={5082AA23-BE6B-427f-A90A-B2D64CBBB75E}][/cover]
    */!][!//
    /*
    Configuration: ETH_17_GETHMAC_GLOBALTIMESUPPORT
    - if STD_ON, TimeStamp feature is enabled.
    - if STD_OFF,TimeStamp feature is disabled.
    */
    [!IF "EthGeneral/EthGlobalTimeSupport   = 'true'"!][!//
      #define  ETH_17_GETHMAC_GLOBALTIMESUPPORT   (STD_ON)
      [!WARNING "Compiler library will be used by Ethernet driver for compilation of global time APIs"!]
    [!ELSE!][!//
      #define  ETH_17_GETHMAC_GLOBALTIMESUPPORT   (STD_OFF)
    [!ENDIF!][!//
    [!/*
    [cover parentID={2B923B9E-FC14-4679-AEFA-4120A21E59F0}][/cover]
    */!][!//
    /*
      Configuration: ETH_17_GETHMAC_MULTICORE_ERROR_DETECT :
      Adds/removes the Multi-core error detection and reporting
      from the code
      - if STD_ON, Multi-core error detection and reporting is enabled
      - if STD_OFF, Multi-core error detection and reporting is disabled
    */
    [!IF "EthGeneral/EthMultiCoreErrorDetect   = 'true'"!][!//
      #define ETH_17_GETHMAC_MULTICORE_ERROR_DETECT           (STD_ON)
    [!ELSE!][!//
      #define ETH_17_GETHMAC_MULTICORE_ERROR_DETECT           (STD_OFF)
    [!ENDIF!][!//

    [!/*
    [cover parentID={88FA5E7E-8A67-4a0f-B18F-1F124C95265D}][/cover]
    */!][!//
    /*
      Configuration: ETH_17_GETHMAC_ICMP_CHECKSUMOFFLOAD_ENABLE
      - if STD_ON, Hardware offloading for ICMP checksums is enabled.
      - if STD_OFF,Hardware offloading for ICMP checksums is disabled.
    */
    [!IF "EthGeneral/EthCtrlOffloading/EthCtrlEnableOffloadChecksumICMP   = 'true'"!][!//
      #define ETH_17_GETHMAC_ICMP_CHECKSUMOFFLOAD_ENABLE  (STD_ON)
    [!ELSE!][!//
      #define ETH_17_GETHMAC_ICMP_CHECKSUMOFFLOAD_ENABLE  (STD_OFF)
    [!ENDIF!][!//

    [!/*
    [cover parentID={72875128-8C0E-4c2b-BA03-8D808FD6DDE1}][/cover]
    */!][!//
    /*
      Configuration: ETH_17_GETHMAC_IPV4_CHECKSUMOFFLOAD_ENABLE
      - if STD_ON, Hardware offloading for IPV4 checksums is enabled.
      - if STD_OFF,Hardware offloading for IPV4 checksums is disabled.
    */
    [!IF "EthGeneral/EthCtrlOffloading/EthCtrlEnableOffloadChecksumIPv4     = 'true'"!][!//
      #define ETH_17_GETHMAC_IPV4_CHECKSUMOFFLOAD_ENABLE  (STD_ON)
    [!ELSE!][!//
      #define ETH_17_GETHMAC_IPV4_CHECKSUMOFFLOAD_ENABLE  (STD_OFF)
    [!ENDIF!][!//

    [!/*
    [cover parentID={16638355-B870-4cce-A537-2BC8DE41EA0A}][/cover]
    */!][!//
    /*
      Configuration: ETH_17_GETHMAC_TCP_CHECKSUMOFFLOAD_ENABLE
      - if STD_ON, Hardware offloading for TCP checksums is enabled.
      - if STD_OFF,Hardware offloading for TCP checksums is disabled.
    */
    [!IF "EthGeneral/EthCtrlOffloading/EthCtrlEnableOffloadChecksumTCP     = 'true'"!][!//
      #define ETH_17_GETHMAC_TCP_CHECKSUMOFFLOAD_ENABLE   (STD_ON)
    [!ELSE!][!//
      #define ETH_17_GETHMAC_TCP_CHECKSUMOFFLOAD_ENABLE   (STD_OFF)
    [!ENDIF!][!//

    [!/*
    [cover parentID={3B533470-3220-479e-92CA-085A6F6D764E}][/cover]
    */!][!//
    /*
      Configuration: ETH_17_GETHMAC_UDP_CHECKSUMOFFLOAD_ENABLE
      - if STD_ON, Hardware offloading for UDP checksums is enabled.
      - if STD_OFF,Hardware offloading for UDP checksums is disabled.
    */
    [!IF "EthGeneral/EthCtrlOffloading/EthCtrlEnableOffloadChecksumUDP   = 'true'"!][!//
      #define ETH_17_GETHMAC_UDP_CHECKSUMOFFLOAD_ENABLE   (STD_ON)
    [!ELSE!][!//
      #define ETH_17_GETHMAC_UDP_CHECKSUMOFFLOAD_ENABLE   (STD_OFF)
    [!ENDIF!][!//

    [!/*
    [cover parentID={12FB11B3-90C8-4084-9C30-06E58F0525C0}][/cover]
    */!][!//
    /*
      Configuration: ETH_17_GETHMAC_UPDATE_PHY_ADDR_FILTER_API
      - if STD_ON, Function Eth_17_GEthMac_UpdatePhysAddrFilter is available
      - if STD_OFF,Function Eth_17_GEthMac_UpdatePhysAddrFilter is not available
    */
    [!IF "EthGeneral/EthUpdatePhysAddrFilter   = 'true'"!][!//
      #define ETH_17_GETHMAC_UPDATE_PHY_ADDR_FILTER_API   (STD_ON)
    [!ELSE!][!//
      #define  ETH_17_GETHMAC_UPDATE_PHY_ADDR_FILTER_API  (STD_OFF)
    [!ENDIF!][!//

    [!/*
    [cover parentID={9B61671A-B967-452e-B85D-3239659FCAB7}] ETH_17_INIT_API_MODE
    [/cover]
    */!][!//
    /*
      Configuration: ETH_17_GETHMAC_INIT_API_MODE
      - if ETH_17_GETHMAC_MCAL_SUPERVISOR - Init API is executed in supervisor mode.
      - if ETH_17_GETHMAC_MCAL_USER1 - Init API is executed in user1 mode.
    */
    [!IF "EthGeneral/EthInitApiMode = 'ETH_MCAL_SUPERVISOR'"!][!//
      #define ETH_17_GETHMAC_INIT_API_MODE         (ETH_17_GETHMAC_MCAL_SUPERVISOR)
    [!ELSE!][!//
      #define ETH_17_GETHMAC_INIT_API_MODE         (ETH_17_GETHMAC_MCAL_USER1)
    [!ENDIF!][!//

    [!/*
    [cover parentID={5AD0169E-F8A8-4c61-963F-C451AD884179}] ETH_17_RUNTIME_API_MODE
    [/cover]
    */!][!//
    /*
    Configuration: ETH_17_GETHMAC_RUNTIME_API_MODE
    - if ETH_17_GETHMAC_MCAL_SUPERVISOR - Runtime APIs are executed in supervisor mode.
    - if ETH_17_GETHMAC_MCAL_USER1 - Runtime APIs are executed in user1 mode.
    */
    [!IF "EthGeneral/EthRuntimeApiMode = 'ETH_MCAL_SUPERVISOR'"!][!//
      #define ETH_17_GETHMAC_RUNTIME_API_MODE      (ETH_17_GETHMAC_MCAL_SUPERVISOR)
    [!ELSE!][!//
      #define ETH_17_GETHMAC_RUNTIME_API_MODE      (ETH_17_GETHMAC_MCAL_USER1)
    [!ENDIF!][!//

    [!CALL "ETH_GenerateModuleMap", "Module" = "'ETH'"!][!//
    [!FOR "CoreId" = "num:i(0)" TO "num:i(6) - num:i(1)"!][!//
      [!VAR "MaxControllersCore" = "num:i(255)"!][!//
      [!VAR "TempCoreId" = "concat('CORE',$CoreId)"!][!//
      [!CALL "ETH_GetMasterCoreID"!][!//
      [!IF "(text:contains( text:split($CGAllocatedCores,','), $TempCoreId)) or ($CGMasterCoreId = $TempCoreId) or ($CoreId < ecu:get('Mcu.NoOfCoreAvailable'))"!][!//
        [!VAR "MaxControllersCore" = "num:i(0)"!][!//
        [!FOR "ControllerID" = "num:i(0)" TO "num:i($MaxControllers) - num:i(1)"!][!//
          [!IF "node:exists(EthConfigSet/*[1]/EthCtrlConfig/*[EthCtrlIdx = num:i($ControllerID)]) = 'true'"!][!//
            [!SELECT "EthConfigSet/*[1]/EthCtrlConfig/*[EthCtrlIdx = num:i($ControllerID)]"!][!//
              [!VAR "NodeName" = "node:name(.)"!][!//
              [!VAR "EthCtrlIdx" = "./EthCtrlIdx"!][!//
              [!CALL "ETH_ValidateChAllocation", "CoreNumber" = "$CoreId", "Channel" = "$NodeName"!][!//
              [!IF "$CGAllocationResult = 'TRUE'"!][!//
                [!VAR "MaxControllersCore" = "$MaxControllersCore + num:i(1)"!][!//
                /* Controller[!"$EthCtrlIdx"!] is configured to [!"$TempCoreId"!] */
                [!/*
                [cover parentID={3E74C90A-4440-4fea-8636-8DCE90FD596E}][/cover]
                */!][!//
                #define ETH_17_GETHMAC_CNTRL[!"$EthCtrlIdx"!]_[!"$TempCoreId"!]  (STD_ON)

                /* Controller[!"$EthCtrlIdx"!] is configured in this project */
                [!/*
                [cover parentID={5E682C09-4265-49ab-921A-6A3F3D57B55C}][/cover]
                */!][!//
                #define ETH_17_GETHMAC_CNTRL[!"$EthCtrlIdx"!]_CONFIGURED         (STD_ON)

              [!ENDIF!][!//
            [!ENDSELECT!][!//
          [!ENDIF!][!//
        [!ENDFOR!][!//
      [!ENDIF!][!//
      /* Maximum Controllers allocated to [!"$TempCoreId"!]
      Value = 255- represents core is not available in current device */
      [!/*
      [cover parentID={6632DC78-3CB1-42aa-AD9F-C1FB59604B90}][/cover]
      */!][!//
      #define ETH_17_GETHMAC_MAX_CNTRL_[!"$TempCoreId"!]               ([!"num:i($MaxControllersCore)"!]U)

    [!ENDFOR!][!//
    /* Maximum available cores in this device */
    [!/*
    [cover parentID={610E0D01-4B2C-408f-91F1-D05EAF5D13CD}][/cover]
    */!][!//
    #define ETH_17_GETHMAC_MAX_CORES                     ([!"ecu:get('Mcu.NoOfCoreAvailable')"!]U)

    /* Maximum controllers available in this device */
    [!/*
    [cover parentID={01FC6736-B6B0-435e-A832-08FC386C9D19}][/cover]
    */!][!//
    #define ETH_17_GETHMAC_MAX_CONTROLLERS               ([!"ecu:get('Eth.EthAvaliableNodes')"!]U)
    /*******************************************************************************
    **                      Global Type Definitions                               **
    *******************************************************************************/
    /*******************************************************************************
    **                      Global Constant Declarations                          **
    *******************************************************************************/

    /*******************************************************************************
    **                      Global Variable Declarations                          **
    *******************************************************************************/

    /*******************************************************************************
    **                      Global Inline Function Definitions                    **
    *******************************************************************************/
    #endif  /* ETH_17_GETHMAC_CFG_H */

  [!ENDSELECT!][!//
[!ENDINDENT!][!//
