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
**  FILENAME    : Uart_Cfg.h                                                  **
**                                                                            **
**  VERSION     : 8.0.0                                                       **
**                                                                            **
**  DATE        : 2019-05-28                                                  **
**                                                                            **
**  AUTHOR      : DL-AUTOSAR-Engineering                                      **
**                                                                            **
**  VENDOR      : Infineon Technologies                                       **
**                                                                            **
**  DESCRIPTION : This file contains                                          **
**                Code template for Uart_Cfg.h file                           **
**                                                                            **
**  MAY BE CHANGED BY USER [yes/no]: No                                       **
**                                                                            **
******************************************************************************/!]
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
**  FILENAME  : Uart_Cfg.h                                                    **
**                                                                            **
**  VERSION   : 8.0.0                                                         **
**                                                                            **
**  DATE, TIME: [!"$date"!], [!"$time"!]  !!!IGNORE-LINE!!!                       **
**                                                                            **
**  GENERATOR : Build [!"$buildnr"!]      !!!IGNORE-LINE!!!                     **
**                                                                            **
**  BSW MODULE DECRIPTION : Uart.bmd                                          **
**                                                                            **
**  VARIANT   : Variant PB                                                    **
**                                                                            **
**  PLATFORM  : Infineon AURIX2G                                              **
**                                                                            **
**  AUTHOR    : DL-AUTOSAR-Engineering                                        **
**                                                                            **
**  VENDOR    : Infineon Technologies                                         **
**                                                                            **
**  DESCRIPTION  : Uart configuration generated out of ECUC file              **
**                                                                            **
**  SPECIFICATION(S) : Specification of Uart Driver, AUTOSAR Release 4.2.2    **
**                                                                            **
**  MAY BE CHANGED BY USER : no                                               **
**                                                                            **
*******************************************************************************/
/* [cover parentID={417E6D71-626B-439d-A213-18197AE5E50D}]
[/cover] */
#ifndef UART_CFG_H
#define UART_CFG_H

/*******************************************************************************
**                      Includes                                              **
*******************************************************************************/

/*******************************************************************************
**                      Global Macro Definitions                              **
*******************************************************************************/

[!/* Select MODULE-CONFIGURATION as context-node */!][!//
[!AUTOSPACING!]
[!INDENT "0"!]
  [!SELECT "as:modconf('Uart')[1]"!][!//
    [!//
    [!//
    /*SW Version Information*/
    [!VAR "SwMajorVersion" = "text:split($moduleSoftwareVer, '.')[position()-1 = 0]"!][!//
    [!VAR "SwMinorVersion" = "text:split($moduleSoftwareVer, '.')[position()-1 = 1]"!][!//
    [!VAR "SwRevisionVersion" = "text:split($moduleSoftwareVer, '.')[position()-1 = 2]"!][!//
    /* [cover parentID={4CDB1F5E-2C2B-4d68-9010-0D6412FF9A56}]
    [/cover] */
    #define UART_SW_MAJOR_VERSION   ([!"$SwMajorVersion"!]U)
    /* [cover parentID={61892AA6-8599-46f6-BBB4-871FE72AAD0B}]
    [/cover] */
    #define UART_SW_MINOR_VERSION   ([!"$SwMinorVersion"!]U)
    /* [cover parentID={A1E33B51-84CE-4af3-83D2-6F00D9D7DE1D}]
    [/cover] */
    #define UART_SW_PATCH_VERSION   ([!"$SwRevisionVersion"!]U)

    [!VAR "Uart_MajorVersion" = "text:split($moduleReleaseVer, '.')[position()-1 = 0]"!][!//
    [!VAR "Uart_MinorVersion" = "text:split($moduleReleaseVer, '.')[position()-1 = 1]"!][!//
    [!VAR "Uart_RevisionVersion" = "text:split($moduleReleaseVer, '.')[position()-1 = 2]"!][!//
    [!VAR "Uart_NewString" = "text:replaceAll($moduleReleaseVer,"\.",'')"!]
    /* [cover parentID={CD73F08D-C743-4d6e-B2DA-A92CB28F0A95}]
    [/cover] */
    /* Section to Generate Autosar Specific Version Information */
    #define UART_AR_RELEASE_MAJOR_VERSION          ([!"$Uart_MajorVersion"!]U)
    /* [cover parentID={94FF191D-0837-4dd2-8F8A-0BF79B9E5475}]
    [/cover] */
    #define UART_AR_RELEASE_MINOR_VERSION          ([!"$Uart_MinorVersion"!]U)
    /* [cover parentID={F68A26DB-F5C8-4c06-9A6A-E6CC8FB9BAD5}]
    [/cover] */
    #define UART_AR_RELEASE_PATCH_VERSION       ([!"$Uart_RevisionVersion"!]U)
    [!//

    /*
      Configuration Options for the setting the privilege mode in Uart driver
    */
    #define UART_SUPERVISOR_MODE  (0U)
    #define UART_USER1_MODE       (1U)
    /*
             Container : UartGeneral Configuration
    */

    /*
    Derived Configuration for UartDevErrorDetect
    - if STD_ON, DET is Enabled
    - if STD_OFF,DET is Disabled
    The detection of all development errors is configurable (On / Off)
    at precompile time. The switch UART_DEV_ERROR_DETECT  shall
    activate or deactivate the detection of all development errors.

    If the switch UART_DEV_ERROR_DETECT is enabled API parameter checking
    is also enabled.
    */
    #define UART_DEV_ERROR_DETECT  ([!//
    [!IF "UartGeneral/UartDevErrorDetect = 'true'"!][!//
      STD_ON[!//
    [!ELSE!][!//
      STD_OFF[!//
    [!ENDIF!][!//
    )
    /* [cover parentID={A63E3C3E-8967-4d8e-9C89-F576C5551815}]
    [/cover] */
    /*
    Derived Configuration for UartVersionInfoApi
    - if STD_ON, Function Uart_GetVersionInfo is available
    - if STD_OFF,Function Uart_GetVersionInfo is not available
    */
    #define UART_VERSION_INFO_API  ([!//
    [!IF "UartGeneral/UartVersionInfoApi = 'true'"!][!//
      STD_ON[!//
    [!ELSE!][!//
      STD_OFF[!//
    [!ENDIF!][!//
    )
    /* [cover parentID={4429B9A4-4A10-4cd7-BAE2-7DDAC6E3237D}]
    [/cover] */
    /* [cover parentID={D1A79D4F-2569-410c-B3E8-AC33182F76B5}]
    [/cover] */
    /*
    Derived Configuration for Uart_InitCheck
    - if STD_ON, Function Uart_InitCheck is available
    - if STD_OFF,Function Uart_InitCheck is not available
    */
    #define UART_INIT_CHECK_API  ([!//
    [!IF "UartGeneral/UartInitCheckApi = 'true'"!][!//
      STD_ON[!//
    [!ELSE!][!//
      STD_OFF[!//
    [!ENDIF!][!//
    )
    /* [cover parentID={F9326D24-DFB7-4f82-88CA-E516B1811703}]
    [/cover] */
    /*
    Derived Configuration for UartDeinitApi
    - if STD_ON, Function UartDeinitApi is available
    - if STD_OFF,Function UartDeinitApi is not available
    */
    #define UART_DEINIT_API  ([!//
    [!IF "UartGeneral/UartDeInitApi = 'true'"!][!//
      STD_ON[!//
    [!ELSE!][!//
      STD_OFF[!//
    [!ENDIF!][!//
    )
    /* [cover parentID={96EF52DD-2606-4824-B769-A88314479A6F}]
    [/cover] */
    /*
    Derived Configuration for UartAbortReadApi
    - if STD_ON, Function UartAbortReadApi is available
    - if STD_OFF,Function UartAbortReadApi is not available
    */
    #define UART_ABORT_READ_API  ([!//
    [!IF "UartGeneral/UartAbortReadApi = 'true'"!][!//
      STD_ON[!//
    [!ELSE!][!//
      STD_OFF[!//
    [!ENDIF!][!//
    )
    /* [cover parentID={FFF59F58-EC6D-4755-BB4B-8FC53B4634BA}]
    [/cover] */
    /*
    Derived Configuration for UartAbortWriteApi
    - if STD_ON, Function UartAbortWriteApi is available
    - if STD_OFF,Function UartAbortWriteApi is not available
    */
    #define UART_ABORT_WRITE_API  ([!//
    [!IF "UartGeneral/UartAbortWriteApi = 'true'"!][!//
      STD_ON[!//
    [!ELSE!][!//
      STD_OFF[!//
    [!ENDIF!][!//
    )
    /* [cover parentID={4C9A5139-5A7F-4be2-AD8C-5E1D27DD2828}]
    [/cover] */
    /* Configuration: UART_INIT_DEINIT_API_MODE
    Determines the privilege mode in which the Initialization and
    De-initialization APIs would operate
    */
    [!VAR "UartMode"="'UART_SUPERVISOR_MODE'"!][!//
    [!IF "UartGeneral/UartInitDeInitApiMode = 'MCAL_USER1'"!][!//
      [!VAR "UartMode"="'UART_USER1_MODE'"!][!//
    [!ENDIF!][!//
    #define UART_INIT_DEINIT_API_MODE  ([!"$UartMode"!])

    [!VAR "UartOpMode" = "'false'"!][!//
    [!LOOP "UartConfigSet/UartChannel/*"!][!//
      [!IF "contains(UartRxChannelMode,'POLLING') = 'true'"!][!//
        [!VAR "UartOpMode" = "'true'"!][!//
      [!ENDIF!][!//
    [!ENDLOOP!][!//
    /* [cover parentID={59A52310-7D5F-428b-B542-578A53CC08D2}]
    [/cover] */
    /*
    Derived Configuration for UartRxPollingEnable
    - if STD_ON, Function Uart_MainFunction_Read is available
    - if STD_OFF,Function Uart_MainFunction_Read is not available
    */
    #define UART_RX_POLLING_ENABLE  ([!//
    [!IF "$UartOpMode = 'true'"!][!//
      STD_ON[!//
    [!ELSE!][!//
      STD_OFF[!//
    [!ENDIF!][!//
    )
    /* [cover parentID={DF7CB90D-64C9-451c-A273-AE7415D2745A}]
    [/cover] */
    [!VAR "UartOpMode" = "'false'"!][!//
    [!LOOP "UartConfigSet/UartChannel/*"!][!//
      [!IF "contains(UartTxChannelMode,'POLLING') = 'true'"!][!//
        [!VAR "UartOpMode" = "'true'"!][!//
      [!ENDIF!][!//
    [!ENDLOOP!][!//
    /*
    Derived Configuration for UartTxPollingEnable
    - if STD_ON, Function Uart_MainFunction_Write is available.
    - if STD_OFF,Function Uart_MainFunction_Write is not available.
    */
    #define UART_TX_POLLING_ENABLE  ([!//
    [!IF "$UartOpMode= 'true'"!][!//
      STD_ON[!//
    [!ELSE!][!//
      STD_OFF[!//
    [!ENDIF!][!//
    )
    /* [cover parentID={2596A0C0-0059-4db8-99CD-BE08911A6173}]
    [/cover] */
    /*
    Derived Configuration for UartSafetyEnable
    - if STD_ON, Safety feature is enable.
    - if STD_OFF,Safety feature is disable.
    */
    #define UART_SAFETY_ENABLE  ([!//
    [!IF "UartGeneral/UartSafetyEnable = 'true'"!][!//
      STD_ON[!//
    [!ELSE!][!//
      STD_OFF[!//
    [!ENDIF!][!//
    )
    /* Derived configuration for UartIndex */
    #define UART_INDEX  ([!"UartGeneral/UartIndex"!]U)

    /* [cover parentID={B76F4DF7-5C1E-43af-A615-C8E14D9B2B05}]
    [/cover] */
    /* Specifies the maximum time in nanoseconds to wait for hardware timeout errors */
    #define UART_MAXTIMEOUT_COUNT  ([!"UartGeneral/UartTimeoutCount"!]U)

    /* [cover parentID={288809DE-6463-4723-A725-1817AA5E94FA}]
    [/cover] */
    /* Total number of ASCLIN hardware module available */
    [!VAR "MaxAscLinMod"= "ecu:get('AscLin.MaxNoOfAscLinModules')"!][!//
    #define UART_MAX_HW_UNIT ([!"$MaxAscLinMod"!]U)

    /* Identifies the the ASCLIN for a channel */
    [!FOR "Hwnumber" = "0" TO "num:i(ecu:get('AscLin.MaxNoOfAscLinModules')) - 1"!][!//
      #define UART_ASCLIN[!"$Hwnumber"!] ([!"$Hwnumber"!]U)
    [!ENDFOR!][!//

    #define UART_ASCLIN_REG_ADDR \
    [!//
    [!FOR "Hwnumber" = "0" TO "num:i(ecu:get('AscLin.MaxNoOfAscLinModules')) - 1"!][!//
                            &MODULE_ASCLIN[!"$Hwnumber"!][!//
      [!IF "$Hwnumber != num:i(ecu:get('AscLin.MaxNoOfAscLinModules')) - 1"!],\
      [!ENDIF!][!//
    [!ENDFOR!][!//

    /* Maximum of number of channels configured. */
    [!VAR "TotalConfig" = "num:i(count(UartConfigSet/*))"!][!//
    [!VAR "MaxChannels"= "num:i(0)"!][!//
    [!VAR "Count"= "num:i(count(UartConfigSet/UartChannel/*))"!][!//
    [!VAR "MaxChannels" = "$Count"!][!//
    /* [cover parentID={344C50A8-3C3B-451c-BDC1-91765B6418CA}]
    [/cover] */
    #define UART_NUM_OF_CHANNEL_CONFIGURED ([!"$MaxChannels"!]U)
    /* Sleep mode is enable or disable */
    [!IF "UartGeneral/UartSleepEnable = 'true'"!][!//
      #define UART_SLEEP_MODE_SUPPORT (0U)
    [!ELSE!][!//
      #define UART_SLEEP_MODE_SUPPORT (0x08U)
    [!ENDIF!][!//

    /* [cover parentID={1C813F83-60F1-4df7-8D9F-3E1FEF4B2E54}]
    [/cover] */
    /* Enable/Disable RunTime error detection */
    #define UART_RUNTIME_ERROR_DETECT         ([!//
    [!IF "UartGeneral/UartRunTimeErrorDetect = 'true'"!][!//
      STD_ON[!//
    [!ELSE!][!//
      STD_OFF[!//
    [!ENDIF!][!//
    )

    /******************************************************************************
    **                      Global Type Definitions                              **
    ******************************************************************************/

    /******************************************************************************
    **                      Global Constant Declarations                         **
    ******************************************************************************/

    /*****************************************************************************
    **                      Global Variable Declarations                        **
    ******************************************************************************/

    /******************************************************************************
    **                      Global Inline Function Definitions                   **
    ******************************************************************************/
    #endif  /* UART_CFG_H */

  [!ENDSELECT!][!//
[!ENDINDENT!]
