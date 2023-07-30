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
**  FILENAME  : Lin_17_AscLin_Cfg.h                                           **
**                                                                            **
**  VERSION   : 5.0.0                                                         **
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
**  TRACEABILITY : [cover parentID= {AA023016-0BDC-4e83-9B26-5DD5E23FB0D9}]   **
**                                                                            **
**  DESCRIPTION  : Code template header file for Lin Driver                   **
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
**  FILENAME  : Lin_17_AscLin_Cfg.h                                           **
**                                                                            **
**  VERSION   : 5.0.0                                                         **
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

  #ifndef LIN_17_ASCLIN_CFG_H
  #define LIN_17_ASCLIN_CFG_H
  [!//
  [!//
  [!/* Select MODULE-CONFIGURATION as context-node */!][!//
  [!SELECT "as:modconf('Lin')[1]"!][!//.
    [!//
    [!//

    [!NOCODE!][!//
      [!VAR "AsMajorVersion" = "text:split($moduleReleaseVer, '.')[position()-1 = 0]"!][!//
      [!VAR "AsMinorVersion" = "text:split($moduleReleaseVer, '.')[position()-1 = 1]"!][!//
      [!VAR "AsRevisionVersion" = "text:split($moduleReleaseVer, '.')[position()-1 = 2]"!][!//
    [!ENDNOCODE!]
    /* AUTOSAR specification version numbers */
    [!/* [cover parentID={F782FE65-6409-435d-B60F-BDB2BA28B942}][/cover] */!][!//
    #define LIN_17_ASCLIN_AR_RELEASE_MAJOR_VERSION  ([!"$AsMajorVersion"!]U)
    [!/* [cover parentID={EBCB5295-37F1-4245-B910-B9D631695A5B}][/cover] */!][!//
    #define LIN_17_ASCLIN_AR_RELEASE_MINOR_VERSION  ([!"$AsMinorVersion"!]U)
    [!/* [cover parentID={D7C54551-1B28-4e71-8146-255DFB1B48DF}][/cover] */!][!//
    #define LIN_17_ASCLIN_AR_RELEASE_PATCH_VERSION  ([!"$AsRevisionVersion"!]U)

    [!NOCODE!][!//
      [!VAR "SwMajorVersion" = "text:split($moduleSoftwareVer, '.')[position()-1 = 0]"!][!//
      [!VAR "SwMinorVersion" = "text:split($moduleSoftwareVer, '.')[position()-1 = 1]"!][!//
      [!VAR "SwRevisionVersion" = "text:split($moduleSoftwareVer, '.')[position()-1 = 2]"!][!//
    [!ENDNOCODE!]
    /* Vendor specific implementation version information */
    [!/* [cover parentID={47C02321-1644-409a-B1AD-BE5DF049D318}][/cover] */!][!//
    #define LIN_17_ASCLIN_SW_MAJOR_VERSION  ([!"$SwMajorVersion"!]U)
    [!/* [cover parentID={43BCA263-B51C-433e-96E9-1A4663D296C7}][/cover] */!][!//
    #define LIN_17_ASCLIN_SW_MINOR_VERSION  ([!"$SwMinorVersion"!]U)
    [!/* [cover parentID={3C5D1657-F187-418a-9837-D0C45B391F5C}][/cover] */!][!//
    #define LIN_17_ASCLIN_SW_PATCH_VERSION  ([!"$SwRevisionVersion"!]U)
/*******************************************************************************
**                      Includes                                              **
*******************************************************************************/


/*******************************************************************************
**                      Global Macro Definitions                              **
*******************************************************************************/
    /*
    [!INDENT "4"!][!//
      Container : GeneralConfiguration
    [!ENDINDENT!][!//
    */

    /*
    [!INDENT "4"!][!//
      Configuration: LIN_17_ASCLIN_DEV_ERROR_DETECT
      - if STD_ON, DET is Enabled
      - if STD_OFF, DET is Disabled
    [!ENDINDENT!][!//
    */
    [!/* [cover parentID={548B891E-6906-4e34-B840-54C8D8D18CC3}][/cover] */!][!//
    [!IF "LinGeneral/LinDevErrorDetect = 'true'"!][!//
      #define LIN_17_ASCLIN_DEV_ERROR_DETECT (STD_ON)[!//
    [!ELSE!][!//
      #define LIN_17_ASCLIN_DEV_ERROR_DETECT (STD_OFF)[!//
    [!ENDIF!]

    /*
    [!INDENT "4"!][!//
      Configuration: LIN_17_ASCLIN_VERSION_INFO_API
      - if STD_ON, Lin_17_AscLin_GetVersionInfo() Api is Enabled
      - if STD_OFF, Lin_17_AscLin_GetVersionInfo() Api is Disabled
    [!ENDINDENT!][!//
    */

    [!/* [cover parentID={473B6FAA-FF58-44ed-8FAD-437A279719D6}][/cover] */!][!//
    [!IF "LinGeneral/LinVersionInfoApi = 'true'"!][!//
      #define LIN_17_ASCLIN_VERSION_INFO_API (STD_ON)[!//
    [!ELSE!][!//
      #define LIN_17_ASCLIN_VERSION_INFO_API (STD_OFF)[!//
    [!ENDIF!]

    /* Instance Id of Lin module instance */
    [!/* [cover parentID={C0A14270-7B99-404f-A786-A4FA4A52218D}][/cover] */!][!//
    #define LIN_17_ASCLIN_INDEX ([!"LinGeneral/LinIndex"!])

    [!/* [cover parentID={62884199-D967-4980-9624-4EC02F196494}][/cover] */!][!//
    /* Maximum number of ASCLIN Hw modules available  */
    #define LIN_17_ASCLIN_MAX_HW_UNIT ([!"ecu:get('AscLin.MaxNoOfAscLinModules')"!])

    /* Maximum number of LIN Channels configured */
    [!/* [cover parentID={13C90025-0DDF-4c15-BC50-F7A00D42656A}][/cover] */!][!//
    #define LIN_17_ASCLIN_MAXIMUM_CHANNEL ([!"num:i(count(LinGlobalConfig/LinChannel/*))"!])

    /*
    [!INDENT "4"!][!//
      Configuration: LIN_17_ASCLIN_CLC
      - if 0x0, ASCLIN module sleep upon request is Enabled
      - if 0x8, ASCLIN module sleep upon request is Disabled
    [!ENDINDENT!][!//
    */
    [!/* <!-- [cover parentID={799BA375-47FC-4d8a-A9BE-9E018E48C919}][/cover] --> */!][!//
    [!IF "LinGeneral/LinHwMcuTrigSleepEnable = 'true'"!][!//
      #define LIN_17_ASCLIN_CLC (0x0)[!//
    [!ELSE!][!//
      #define LIN_17_ASCLIN_CLC (0x8)[!//
    [!ENDIF!]

    /* Identifies the the Rx alternate pin selection for a channel */
    #define LIN_17_ASCLIN_SELECT_A (0x0)
    #define LIN_17_ASCLIN_SELECT_B (0x1)
    #define LIN_17_ASCLIN_SELECT_C (0x2)
    #define LIN_17_ASCLIN_SELECT_D (0x3)
    #define LIN_17_ASCLIN_SELECT_E (0x4)
    #define LIN_17_ASCLIN_SELECT_F (0x5)
    #define LIN_17_ASCLIN_SELECT_G (0x6)
    #define LIN_17_ASCLIN_SELECT_H (0x7)

    /* Identifies the the ASCLINx for a channel */
    [!FOR "Hwnumber" = "0" TO "num:i(ecu:get('AscLin.MaxNoOfAscLinModules')) - 1"!][!//
      #define LIN_17_ASCLIN[!"$Hwnumber"!] ([!"$Hwnumber"!]U)
    [!ENDFOR!][!//

    [!/* <!-- [cover parentID={C6B210D8-70C4-4d41-9D85-C55F542013F2}][/cover] --> */!][!//
    /* Generating list of offset addresses defined in register file for all LIN
     kernels */
    #define LIN_17_ASCLIN_REGADDR [!//
    [!INDENT "4"!][!//
      [!FOR "Hwnumber" = "0" TO "num:i(ecu:get('AscLin.MaxNoOfAscLinModules')) - 1"!]  [!//
        &MODULE_ASCLIN[!"$Hwnumber"!][!//
        [!IF "$Hwnumber != num:i(ecu:get('AscLin.MaxNoOfAscLinModules')) - 1"!][!//
          ,  [!//
        [!ENDIF!][!//
        [!INDENT "4"!][!//
          [!IF "$Hwnumber mod num:i(3) = num:i(0)"!][!//
            \
          [!ENDIF!][!//
        [!ENDINDENT!][!//
      [!ENDFOR!][!//
    [!ENDINDENT!]
    [!CR!]
    
    /*
    [!INDENT "4"!][!//
      Configuration: LIN_17_ASCLIN_CSRREG_CLKSEL
      - if 0x2, ASCLIN peripheral frequency for fast mode is selected
      - if 0x4, ASCLIN peripheral frequency for slow mode is selected
    [!ENDINDENT!][!//
    */
    [!/* <!-- [cover parentID={334F8800-1273-431e-B757-56ECE09B006D}][/cover] --> */!][!//
    [!IF "LinGeneral/LinCsrClksel = 'ASCLINF'"!][!//
      #define LIN_17_ASCLIN_CSRREG_CLKSEL (0x2)[!//
    [!ELSE!][!//
      #define LIN_17_ASCLIN_CSRREG_CLKSEL (0x4)[!//
    [!ENDIF!]

    [!/* [cover parentID={9A645A5C-2204-4b30-9B01-842C8E69CB7D}]Precompile Time support for User Mode[/cover] */!][!//
    [!/* <!-- [cover parentID={06B224D3-894C-440b-8002-F5419ABBE295}][/cover] --> */!][!//
    #define LIN_17_ASCLIN_INIT_DEINIT_API_MODE (LIN_17_ASC[!"node:value(LinGeneral/LinInitDeInitApiMode)"!]_MODE)

    [!/* <!-- [cover parentID={0E12D31A-E019-4dc4-B132-C9C0F0323403}][/cover] --> */!][!//
    [!/* <!-- [cover parentID={9A645A5C-2204-4b30-9B01-842C8E69CB7D}]Precompile Time support for User Mode[/cover] --> */!][!//
    #define LIN_17_ASCLIN_MCAL_SUPERVISOR_MODE [!//
    [!IF "(node:value(LinGeneral/LinInitDeInitApiMode) = 'LIN_MCAL_SUPERVISOR')"!][!//
      (STD_ON)
    [!ELSE!][!//
      (STD_OFF)
    [!ENDIF!][!//

    [!/* <!-- [cover parentID={03A1A449-E392-4490-999C-5C3BB8ED4FD4}][/cover] --> */!][!//
    [!/* <!-- [cover parentID={9A645A5C-2204-4b30-9B01-842C8E69CB7D}]Precompile Time support for User Mode[/cover] --> */!][!//
    #define LIN_17_ASCLIN_MCAL_USER1_MODE [!//
    [!IF "(node:value(LinGeneral/LinInitDeInitApiMode) = 'LIN_MCAL_USER1')"!][!//
      (STD_ON)
    [!ELSE!][!//
      (STD_OFF)
    [!ENDIF!][!//

    [!/* <!-- [cover parentID={92074205-839F-4851-B003-B7F50C72C32A}][/cover] --> */!][!//
    #define LIN_17_ASCLIN_INTERRUPT_DISABLED [!//
    [!IF "LinGeneral/LinInterruptDisabled = 'true'"!][!//
      (STD_ON)
    [!ELSE!][!//
      (STD_OFF)
    [!ENDIF!][!//

    [!LOOP "node:order(LinGlobalConfig/LinChannel/*,'./LinChannelId')"!]
      /*
      [!INDENT "4"!][!//
        Lin Channel : ([!"node:name(.)"!])
      [!ENDINDENT!][!//
      */

      /* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32 chars.
       in generated code due to Autosar Naming constraints.*/
      /* MISRA2012_RULE_5_2_JUSTIFICATION: External identifiers going beyond 32 chars.
       in generated code due to Autosar Naming constraints.*/
      /* MISRA2012_RULE_5_4_JUSTIFICATION: External identifiers going beyond 32 chars.
       in generated code due to Autosar Naming constraints.*/
      /* MISRA2012_RULE_5_5_JUSTIFICATION: External identifiers going beyond 32 chars.
       in generated code due to Autosar Naming constraints.*/

      #ifndef Lin_17_AscLinConf_LinChannel_[!"node:name(.)"!]

      /* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32 chars.
       in generated code due to Autosar Naming constraints.*/
      /* MISRA2012_RULE_5_2_JUSTIFICATION: External identifiers going beyond 32 chars.
       in generated code due to Autosar Naming constraints.*/
      /* MISRA2012_RULE_5_4_JUSTIFICATION: External identifiers going beyond 32 chars.
       in generated code due to Autosar Naming constraints.*/
      /* MISRA2012_RULE_5_5_JUSTIFICATION: External identifiers going beyond 32 chars.
       in generated code due to Autosar Naming constraints.*/

      /* <!-- [cover parentID={F7E0ED21-7774-45fb-9AEC-47490C5AE1F9}]
        [/cover] --> */

      #define Lin_17_AscLinConf_LinChannel_[!"node:name(.)"!]          ([!"./LinChannelId"!]U)
      #endif
    [!ENDLOOP!]

    /*
    [!INDENT "4"!][!//
      Configuration: LIN_17_ASCLIN_GLOBAL_CHANNEL_WAKEUP_SUPPORT
      - if STD_ON, LinChannelWakeupSupport is enabled for atleast 1 channel
      - if STD_OFF, LinChannelWakeupSupport is not enabled for atleast 1 channel
    [!ENDINDENT!][!//
    */
    [!NOCODE!][!//
      /* <!-- [cover parentID={E1E9628F-9893-4985-A650-16A54D16D8E5}]
        [/cover] --> */
      [!VAR "GlobalWakeupSupport" = "num:i(0)"!][!//
      [!LOOP "node:order(LinGlobalConfig/LinChannel/*,'./LinChannelId')"!][!//
        [!IF "./LinChannelWakeupSupport = 'true'"!][!//
          [!VAR "GlobalWakeupSupport" = "num:i(1)"!][!//
        [!BREAK!][!//
        [!ENDIF!] [!//
      [!ENDLOOP!][!//
    [!ENDNOCODE!][!//
    [!IF "num:i($GlobalWakeupSupport) = num:i(1)"!][!//
      #define LIN_17_ASCLIN_GLOBAL_CHANNEL_WAKEUP_SUPPORT (STD_ON)
    [!ELSE!][!//
      #define LIN_17_ASCLIN_GLOBAL_CHANNEL_WAKEUP_SUPPORT (STD_OFF)
    [!ENDIF!]
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
**                      Global Function Declarations                          **
*******************************************************************************/

/*******************************************************************************
**                      Global Inline Function Definitions                    **
*******************************************************************************/
  #endif /* LIN_17_ASCLIN_CFG_H */
  [!ENDSELECT!]
[!ENDINDENT!]