[!AUTOSPACING!]
[!INDENT "0"!][!//
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
**  FILENAME  : Lin_17_AscLin_PBcfg.c                                         **
**                                                                            **
**  VERSION   : 6.0.0                                                         **
**                                                                            **
**  DATE      : 2019-05-31                                                    **
**                                                                            **
**  BSW MODULE DECRIPTION : Lin.bmd                                           **
**                                                                            **
**  VARIANT   : Variant PB                                                    **
**                                                                            **
**  PLATFORM  : Infineon AURIX2G                                              **
**                                                                            **
**  AUTHOR    : DL-AUTOSAR-Engineering                                        **
**                                                                            **
**  VENDOR    : Infineon Technologies                                         **
**                                                                            **
**  TRACEABILITY : [cover parentID= {38EF7570-7354-41e0-9327-62AE62DEA904}]   **
**                                                                            **
**  DESCRIPTION  : Code template source file for Lin Driver                   **
**                                                                            **
**  [/cover]                                                                  **
**                                                                            **
**  SPECIFICATION(S) : Specification of Lin Driver, AUTOSAR Release 4.2.2     **
**                                                                            **
**  MAY BE CHANGED BY USER : no                                               **
**                                                                            **
*****************************************************************************/!][!//
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
**  FILENAME  : Lin_17_AscLin_PBcfg.c                                         **
**                                                                            **
**  VERSION   : 6.0.0                                                         **
**                                                                            **
**  DATE, TIME: [!"$date"!], [!"$time"!]      !!!IGNORE-LINE!!!               **
**                                                                            **
**  GENERATOR : Build [!"$buildnr"!]          !!!IGNORE-LINE!!!               **
**                                                                            **
**  BSW MODULE DECRIPTION : Lin.bmd                                           **
**                                                                            **
**  VARIANT   : Variant PB                                                    **
**                                                                            **
**  PLATFORM  : Infineon AURIX2G                                              **
**                                                                            **
**  AUTHOR    : DL-AUTOSAR-Engineering                                        **
**                                                                            **
**  VENDOR    : Infineon Technologies                                         **
**                                                                            **
**  DESCRIPTION  : Lin configuration generated out of ECUC file               **
**                                                                            **
**  SPECIFICATION(S) : Specification of Lin Driver, AUTOSAR Release 4.2.2     **
**                                                                            **
**  MAY BE CHANGED BY USER : no                                               **
**                                                                            **
*******************************************************************************/
  [!/* [cover parentID={A6441ED2-CF72-40f9-B26D-BD0C8B9BBA95}][/cover] */!][!//
  [!NOCODE!]
    [!INCLUDE "Lin_17_AscLin.m"!][!//
  [!ENDNOCODE!]
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
/*******************************************************************************
**                      Includes                                              **
*******************************************************************************/
  /* Inclusion of Lin Header file */
  #include "Lin_17_AscLin.h"
/*******************************************************************************
**                      Private Macro Definitions                             **
*******************************************************************************/
/*******************************************************************************
**                      Global Constant Definitions                           **
*******************************************************************************/
  /* <!-- [cover parentID={E4047F9A-8865-4b2c-9D3C-385479854EAD}]
  [/cover] --> */
  #define LIN_17_ASCLIN_START_SEC_CONFIG_DATA_QM_LOCAL_UNSPECIFIED
  /* MISRA2012_RULE_4_10_JUSTIFICATION: To be compliant with autosar guidelines
  Lin_17_AscLin_Memmap.h header is included without safegaurd.*/
  /* MISRA2012_RULE_20_1_JUSTIFICATION: Lin_17_AscLin_Memmap.h header included
  as per Autosar guidelines. */
  #include "Lin_17_AscLin_MemMap.h"
/*******************************************************************************
**                      Configuration Options                                 **
*******************************************************************************/
/******************************************************************************/
  /*
  [!INDENT "4"!][!//
    Container: LinChannelConfiguration
  [!ENDINDENT!][!//
  */
  /*
  [!INDENT "4"!][!//
    To be used for global or static constants (unspecified size)
  [!ENDINDENT!][!//
  */
  [!/*[cover parentID={70F6B128-B564-4e2b-B6E7-A516D1FDB059}]Dependent Module Checks[/cover] */!][!//
  [!IF "not(node:exists(as:modconf('ResourceM')[1]))"!]
    [!ERROR!][!//
      LIN Code Generator: ResourceM module is not added to the project.
    [!ENDERROR!][!//
  [!ENDIF!]
  [!IF "not(node:exists(as:modconf('Mcu')[1]))"!]
    [!ERROR!][!//
      LIN Code Generator: Mcu module is not added to the project.
    [!ENDERROR!][!//
  [!ENDIF!]
  [!/*[cover parentID={3660BA10-FF74-4045-9607-57DB8AFDEBA6}][/cover]*/!][!//
  [!//
  [!/* Select MODULE-CONFIGURATION as context-node */!][!//
  [!SELECT "as:modconf('Lin')[1]"!][!//
    [!//
    [!/*[cover parentID={6188522A-98C1-4a67-B79D-8AE22F58B9E9}][/cover]*/!][!//
    [!VAR "TotalChannel" = "num:i(count(LinGlobalConfig/LinChannel/*))"!][!//
    [!VAR "LinMaxChannel" = "num:i(ecu:get('AscLin.MaxNoOfAscLinModules'))"!][!//
    [!IF "$VariantsConfigured = num:i(1)"!][!//
      static const uint8 Lin_17_AscLin_ChannelIdLookup_[!"$PredefinedVarName"!][LIN_17_ASCLIN_MAX_HW_UNIT] =
    [!ELSE!][!//
      static const uint8 Lin_17_AscLin_ChannelIdLookup[LIN_17_ASCLIN_MAX_HW_UNIT] =
    [!ENDIF!][!//
    {
    [!INDENT "4"!][!//
      [!FOR "LinCounter" = "0" TO "num:i($LinMaxChannel - 1)"!][!//
        [!IF "num:i(count(LinGlobalConfig/LinChannel/*[LinChanAssignedHw = concat('ASCLIN',$LinCounter)])) = num:i(0)"!][!//
          0xFFU[!//
        [!ELSE!][!//
          [!LOOP "LinGlobalConfig/LinChannel/*[LinChanAssignedHw = concat('ASCLIN',$LinCounter)]"!][!//
            [!"node:value(./LinChannelId)"!]U[!//
          [!ENDLOOP!][!//
        [!ENDIF!]
        [!IF "num:i($LinCounter) != num:i($LinMaxChannel - 1)"!][!//
          ,
        [!ELSE!]

        [!ENDIF!][!//
      [!ENDFOR!][!//
    [!ENDINDENT!][!//
    };
    [!IF "LinGeneral/LinCsrClksel = 'ASCLINF'"!][!//
      [!VAR "input_freq" = "num:i(node:ref(LinGeneral/LinSysClockRef)/McuPllDistributionSettingConfig/McuAscLinFastFrequency)"!][!//
    [!ELSE!][!//
      [!VAR "input_freq" = "num:i(node:ref(LinGeneral/LinSysClockRef)/McuPllDistributionSettingConfig/McuAscLinSlowFrequency)"!][!//
    [!ENDIF!][!//
    [!// Determine if the configuration done for the Lin module is valid
    [!CALL "Lin_17_AscLin_ConfigurationCheck",  "input_freq3" = "$input_freq"!][!//
    [!VAR "TotalChannel" = "num:i(count(LinGlobalConfig/LinChannel/*))"!][!//
    [!IF "$VariantsConfigured = num:i(1)"!][!//
      static const Lin_17_AscLin_ChannelType  Lin_17_AscLin_kChannelConfig_[!"$PredefinedVarName"!][[!"string(num:i($TotalChannel))"!]] =
    [!ELSE!][!//
      static const Lin_17_AscLin_ChannelType  Lin_17_AscLin_kChannelConfig[[!"string(num:i($TotalChannel))"!]] =
    [!ENDIF!][!//
    {
    [!VAR "Count" = "num:i(0)"!][!//
    [!LOOP "node:order(LinGlobalConfig/LinChannel/*, './LinChannelId')"!][!//
      [!NOCODE!][!//
        [!IF "LinAutoCalcBaudParams = 'true'"!][!//
          [!CALL "Lin_17_AscLin_CalcBaudParams", "BaudRate" = "LinChannelBaudRate", "input_freq1" = "$input_freq"!][!//
          [!VAR "BaudRate" = "num:i(LinChannelBaudRate)"!][!//
        [!ELSE!][!//
          [!VAR "Numerator" = "num:i(LinChannelBaudNumerator)"!][!//
          [!VAR "Denominator" = "num:i(LinChannelBaudDenominator)"!][!//
          [!VAR "Prescalar" = "num:i(LinChannelBaudPreScalar)"!][!//
          [!VAR "fPD" = "num:i($input_freq) div (num:i($Prescalar) + 1)"!][!//
          [!VAR "fOVS" = "num:i($fPD) * num:i($Numerator) div num:i($Denominator)"!][!//
          [!VAR "BaudRate" = "num:i($fOVS) div (num:i(15) + 1)"!][!//
        [!ENDIF!][!//
        [!CALL "Lin_17_AscLin_CalcWakeupParams",  "input_freq2" = "$input_freq"!][!//
      [!ENDNOCODE!][!//
      [!INDENT "2"!][!//
        /* LIN Channel ID: [!"LinChannelId"!] Configuration */
        {
        [!INDENT "4"!][!//
          /* BaudRate : [!"$BaudRate"!] Hz  */
          {
          [!INDENT "8"!]
            [!"$Numerator"!]U,  /* BRG.NUMERATOR value */
            [!"$Denominator"!]U,    /* BRG.DENOMINATOR value */
            [!"$Prescalar"!]U,  /* BITCON.PRESCALAR value */
            [!"num:i($WakeupPrescalar)"!]U,  /* Prescalar value for wakeup detection */
            [!"LinInterByteSpace"!]U, /* Inter byte or response space value */
            [!"num:i($WakeupIocrDepth)"!]U /* IOCR DEPTH value for wakeup detection */
          [!ENDINDENT!][!//
          },
        [!ENDINDENT!]
        [!AUTOSPACING!]
        [!INDENT "4"!]
          [!IF "node:refexists(./LinChannelEcuMWakeupSource/*[1]) = 'true'"!][!//
            [!VAR "WakeupSupport" = "node:ref(./LinChannelEcuMWakeupSource/*[1])/EcuMWakeupSourceId"!][!//
            [!"$WakeupSupport"!]U,          /* EcuM Wakeup Source ID */
          [!ELSE!][!//
            0xFFU,                            /* EcuM Wakeup Source ID */
          [!ENDIF!][!//
          LIN_17_[!"LinChanAssignedHw"!],   /* Hw Module used */
          [!IF "LinChannelWakeupSupport = 'true'"!][!//
            LIN_17_ASCLIN_CHANNEL_WAKEUP_ENABLED,     /* Wakeup Support */
          [!ELSE!][!//
            LIN_17_ASCLIN_CHANNEL_WAKEUP_DISABLED,    /* Wakeup Support */
          [!ENDIF!][!//
          [!/*[cover parentID={7C4697F7-2FA3-4c89-A4D7-CD9D017480AE}][/cover]*/!][!//
          [!VAR "Dataline" = "./LinRxAlternateInputSignal"!][!//
          [!IF "contains($Dataline, 'GN') or contains($Dataline, 'GP')"!][!//
            LIN_17_ASCLIN_SELECT_G
          [!ELSE!]
            LIN_17_ASCLIN_[!"substring-before($Dataline, '_P')"!]   /*Rx alternate pin select */
          [!ENDIF!]
        [!ENDINDENT!][!//
        [!VAR "Count" = "$Count + 1"!][!//
        [!IF "$Count < $TotalChannel"!][!//
          },
        [!ELSE!][!//
          }
        [!ENDIF!][!//
      [!ENDINDENT!][!//
    [!ENDLOOP!][!//
    };
    /*
    [!INDENT "4"!]
      The over all initialization data for the LIN driver.
      The user configured Lin driver initialization structure.
    [!ENDINDENT!]
    */
    /* MISRA2012_RULE_8_7_JUSTIFICATION: Module configuration data structure
    declaration as per Autosar guidelines. This data structure may be needed
    by SW units using Port Driver APIs */
    /* MISRA2012_RULE_8_4_JUSTIFICATION: Definition is as per Autosar guidelines */
    [!/*[cover parentID={172ADD26-8522-4416-A496-1C9D4CDF511C}][/cover]*/!][!//
    [!IF "$VariantsConfigured = num:i(1)"!][!//
      const Lin_17_AscLin_ConfigType  Lin_17_AscLin_Config_[!"$PredefinedVarName"!] =
    [!ELSE!][!//
      const Lin_17_AscLin_ConfigType  Lin_17_AscLin_Config =
    [!ENDIF!][!//
    {
    [!INDENT "2"!]
      [!IF "$VariantsConfigured = num:i(1)"!][!//
        &Lin_17_AscLin_kChannelConfig_[!"$PredefinedVarName"!][0],
      [!ELSE!][!//
        &Lin_17_AscLin_kChannelConfig[0],
      [!ENDIF!][!//
      [!IF "$VariantsConfigured = num:i(1)"!][!//
        &Lin_17_AscLin_ChannelIdLookup_[!"$PredefinedVarName"!][0],
      [!ELSE!][!//
        &Lin_17_AscLin_ChannelIdLookup[0],
      [!ENDIF!][!//
      [!"$TotalChannel"!]U
    [!ENDINDENT!]
    };
  [!ENDSELECT!][!//
  [!/*[cover parentID={E4047F9A-8865-4b2c-9D3C-385479854EAD}][/cover]*/!][!//
  #define LIN_17_ASCLIN_STOP_SEC_CONFIG_DATA_QM_LOCAL_UNSPECIFIED
  /* MISRA2012_RULE_4_10_JUSTIFICATION: To be compliant with autosar guidelines
  Lin_17_AscLin_Memmap.h header is included without safegaurd.*/
  /* MISRA2012_RULE_20_1_JUSTIFICATION: Lin_17_AscLin_Memmap.h header included
  as per Autosar guidelines. */
  #include "Lin_17_AscLin_MemMap.h"
[!ENDINDENT!]
/*******************************************************************************
**                      Global Variable Definitions                           **
*******************************************************************************/
/*******************************************************************************
**                      Private Constant Definitions                          **
*******************************************************************************/
/*******************************************************************************
**                      Private Variable Definitions                          **
*******************************************************************************/
/*******************************************************************************
**                      Global Function Definitions                           **
*******************************************************************************/
/*******************************************************************************
**                      Private Function Definitions                          **
*******************************************************************************/
