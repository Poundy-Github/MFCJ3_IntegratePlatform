/**EB_Automotive_C_Source_File */

#if (!defined CANTRCV_1_T03_H)
#define CANTRCV_1_T03_H

/* !LINKSTO CanTrcv.ASR40.CanTrcv052,1 */

/*==================[inclusions]=============================================*/

/* Always include pre-compile-time information - needed by own and foreign modules */
/* don't mix PBcfg or Lcfg symbolic name values into Cfg since those headerfiles are
 * included anyway right afterwards */
#if (defined CANTRCV_1_T03_NO_PBCFG_REQUIRED)

#if (defined CANTRCV_1_T03_NO_CFGCLASSMIX_REQUIRED)      /* To prevent double declaration */
#error CANTRCV_1_T03_NO_CFGCLASSMIX_REQUIRED already defined!
#endif /* #if (defined CANTRCV_1_T03_NO_CFGCLASSMIX_REQUIRED) */

#define CANTRCV_1_T03_NO_CFGCLASSMIX_REQUIRED
#endif /* CANTRCV_1_T03_NO_PBCFG_REQUIRED */

#include <CanTrcv_1_T03_Cfg.h>        /* Pre-Compile time configuration */

/* Exclude link-time config include file if requested to do so */
#if (!defined CANTRCV_1_T03_NO_LCFG_REQUIRED) && (!defined CANTRCV_1_T03_NO_CFG_REQUIRED)
#include <CanTrcv_1_T03_Lcfg.h>       /* Link time configuration */
#endif /* CANTRCV_1_T03_NO_LCFG_REQUIRED */

/* Exclude post-build-time config include file if requested to do so */
#if (!defined CANTRCV_1_T03_NO_PBCFG_REQUIRED) && (!defined CANTRCV_1_T03_NO_CFG_REQUIRED)
#if (CANTRCV_1_T03_PBCFGM_SUPPORT_ENABLED == STD_OFF)
#include <CanTrcv_1_T03_PBcfg.h>      /* Post-Build time configuration */
#endif /* CANTRCV_1_T03_PBCFGM_SUPPORT_ENABLED == STD_OFF */
#endif /* CANTRCV_1_T03_NO_PBCFG_REQUIRED */

#undef CANTRCV_1_T03_NO_LCFG_REQUIRED
#undef CANTRCV_1_T03_NO_PBCFG_REQUIRED
#undef CANTRCV_1_T03_NO_CFG_REQUIRED

#include <ComStack_Types.h>           /* Com-Stack wide types */
#include <Can_GeneralTypes.h>         /* Can-Stack wide types */

#include <CanTrcv_1_T03_Version.h>    /* Module versions */
#include <CanTrcv_1_T03_Types.h>      /* CanTrcv_1_T03_ConfigType */

#if (CANTRCV_1_T03_PBCFGM_SUPPORT_ENABLED == STD_ON)
#include <PbcfgM_Api.h>         /* Post build configuration manager */
#endif /* CANTRCV_1_T03__PBCFGM_SUPPORT_ENABLED */

/*==================[macros]=================================================*/

/*------------------[API service IDs]----------------------------------------*/

#if (defined CANTRCV_1_T03_ISVALIDCONFIG_SERVICE_ID)      /* To prevent double declaration */
#error CANTRCV_1_T03_ISVALIDCONFIG_SERVICE_ID already defined!
#endif /* #if (defined CANTRCV_1_T03_ISVALIDCONFIG_SERVICE_ID) */

#if (defined CANTRCV_1_T03_INIT_ID)      /* To prevent double declaration */
#error CANTRCV_1_T03_INIT_ID already defined!
#endif /* #if (defined CANTRCV_1_T03_INIT_ID) */

#if (defined CANTRCV_1_T03_SETOPMODE_ID)      /* To prevent double declaration */
#error CANTRCV_1_T03_SETOPMODE_ID already defined!
#endif /* #if (defined CANTRCV_1_T03_SETOPMODE_ID) */

#if (defined CANTRCV_1_T03_GETOPMODE_ID)      /* To prevent double declaration */
#error CANTRCV_1_T03_GETOPMODE_ID already defined!
#endif /* #if (defined CANTRCV_1_T03_GETOPMODE_ID) */

#if (defined CANTRCV_1_T03_GETBUSWUREASON_ID)      /* To prevent double declaration */
#error CANTRCV_1_T03_GETBUSWUREASON_ID already defined!
#endif /* #if (defined CANTRCV_1_T03_GETBUSWUREASON_ID) */

#if (defined CANTRCV_1_T03_GETVERSIONINFO_ID)      /* To prevent double declaration */
#error CANTRCV_1_T03_GETVERSIONINFO_ID already defined!
#endif /* #if (defined CANTRCV_1_T03_GETVERSIONINFO_ID) */

#if (defined CANTRCV_1_T03_SETWAKEUPMODE_ID)      /* To prevent double declaration */
#error CANTRCV_1_T03_SETWAKEUPMODE_ID already defined!
#endif /* #if (defined CANTRCV_1_T03_SETWAKEUPMODE_ID) */

#if (defined CANTRCV_1_T03_MAINFUNCTION_ID)      /* To prevent double declaration */
#error CANTRCV_1_T03_MAINFUNCTION_ID already defined!
#endif /* #if (defined CANTRCV_1_T03_MAINFUNCTION_ID) */

#if (defined CANTRCV_1_T03_CHECKWAKEUP_ID)      /* To prevent double declaration */
#error CANTRCV_1_T03_CHECKWAKEUP_ID already defined!
#endif /* #if (defined CANTRCV_1_T03_CHECKWAKEUP_ID) */

#if (defined CANTRCV_1_T03_MAINFUNCTIONDIAGNOSTICS_ID)      /* To prevent double declaration */
#error CANTRCV_1_T03_MAINFUNCTIONDIAGNOSTICS_ID already defined!
#endif /* #if (defined CANTRCV_1_T03_MAINFUNCTIONDIAGNOSTICS_ID) */

#if (defined CANTRCV_1_T03_GETTRCVSYSTEMDATA_ID)      /* To prevent double declaration */
#error CANTRCV_1_T03_GETTRCVSYSTEMDATA_ID already defined!
#endif /* #if (defined CANTRCV_1_T03_GETTRCVSYSTEMDATA_ID) */

#if (defined CANTRCV_1_T03_CLEARTRCVWUFFLAG_ID)      /* To prevent double declaration */
#error CANTRCV_1_T03_CLEARTRCVWUFFLAG_ID already defined!
#endif /* #if (defined CANTRCV_1_T03_CLEARTRCVWUFFLAG_ID) */

#if (defined CANTRCV_1_T03_READTRCVTIMEOUTFLAG_ID)      /* To prevent double declaration */
#error CANTRCV_1_T03_READTRCVTIMEOUTFLAG_ID already defined!
#endif /* #if (defined CANTRCV_1_T03_READTRCVTIMEOUTFLAG_ID) */

#if (defined CANTRCV_1_T03_CLEARTRCVTIMEOUTFLAG_ID)      /* To prevent double declaration */
#error CANTRCV_1_T03_CLEARTRCVTIMEOUTFLAG_ID already defined!
#endif /* #if (defined CANTRCV_1_T03_CLEARTRCVTIMEOUTFLAG_ID) */

#if (defined CANTRCV_1_T03_READTRCVSILENCEFLAG_ID)      /* To prevent double declaration */
#error CANTRCV_1_T03_READTRCVSILENCEFLAG_ID already defined!
#endif /* #if (defined CANTRCV_1_T03_READTRCVSILENCEFLAG_ID) */

#if (defined CANTRCV_1_T03_CHECKWAKEFLAG_ID)      /* To prevent double declaration */
#error CANTRCV_1_T03_CHECKWAKEFLAG_ID already defined!
#endif /* #if (defined CANTRCV_1_T03_CHECKWAKEFLAG_ID) */

#if (defined CANTRCV_1_T03_SETPNACTIVATIONSTATE_ID)      /* To prevent double declaration */
#error CANTRCV_1_T03_SETPNACTIVATIONSTATE_ID already defined!
#endif /* #if (defined CANTRCV_1_T03_SETPNACTIVATIONSTATE_ID) */

/** \brief CanTrcv_1_T03_IsValidConfig() service ID */
#define       CANTRCV_1_T03_ISVALIDCONFIG_SERVICE_ID          0x60U
/** \brief CanTrcv_1_T03_Init() service ID */
#define       CANTRCV_1_T03_INIT_ID                           0x00U
/** \brief CanTrcv_1_T03_SetOpMode() service ID */
#define       CANTRCV_1_T03_SETOPMODE_ID                      0x01U
/** \brief CanTrcv_1_T03_GetOpMode() service ID */
#define       CANTRCV_1_T03_GETOPMODE_ID                      0x02U
/** \brief CanTrcv_1_T03_GetBusWuReason() service ID */
#define       CANTRCV_1_T03_GETBUSWUREASON_ID                 0x03U
/** \brief CanTrcv_1_T03_GetVersionInfo() service ID */
#define       CANTRCV_1_T03_GETVERSIONINFO_ID                 0x04U
/** \brief CanTrcv_1_T03_SetWakeupMode() service ID */
#define       CANTRCV_1_T03_SETWAKEUPMODE_ID                  0x05U
/** \brief CanTrcv_1_T03_MainFunction() service ID */
#define       CANTRCV_1_T03_MAINFUNCTION_ID                   0x06U
/** \brief CanTrcv_1_T03_CheckWakeup() service ID */
#define       CANTRCV_1_T03_CHECKWAKEUP_ID                    0x07U
/** \brief CanTrcv_1_T03_MainFunctionDiagnostics () service ID */
#define       CANTRCV_1_T03_MAINFUNCTIONDIAGNOSTICS_ID        0x08U
/** \brief CanTrcv_1_T03_GetTrcvSystemData() service ID */
#define       CANTRCV_1_T03_GETTRCVSYSTEMDATA_ID              0x09U
/** \brief CanTrcv_1_T03_CanTrcv_ClearTrcvWufFlag () service ID */
#define       CANTRCV_1_T03_CLEARTRCVWUFFLAG_ID               0x0AU
/** \brief CanTrcv_1_T03_CanTrcv_ReadTrcvTimeoutFlag () service ID */
#define       CANTRCV_1_T03_READTRCVTIMEOUTFLAG_ID            0x0BU
/** \brief CanTrcv_1_T03_CanTrcv_ClearTrcvTimeoutFlag () service ID */
#define       CANTRCV_1_T03_CLEARTRCVTIMEOUTFLAG_ID           0x0CU
/** \brief CanTrcv_1_T03_CanTrcv_ReadTrcvSilenceFlag () service ID */
#define       CANTRCV_1_T03_READTRCVSILENCEFLAG_ID            0x0DU
/** \brief CanTrcv_1_T03_CheckWakeFlag () service ID */
#define       CANTRCV_1_T03_CHECKWAKEFLAG_ID                  0x0EU
/** \brief CanTrcv_1_T03_SetPNActivationState () service ID */
#define       CANTRCV_1_T03_SETPNACTIVATIONSTATE_ID           0x0FU




/*------------------[Development error codes]--------------------------------*/

#if (defined CANTRCV_1_T03_E_INVALID_TRANSCEIVER)      /* To prevent double declaration */
#error CANTRCV_1_T03_E_INVALID_TRANSCEIVER already defined!
#endif /* #if (defined CANTRCV_1_T03_E_INVALID_TRANSCEIVER) */

#if (defined CANTRCV_1_T03_E_PARAM_POINTER)      /* To prevent double declaration */
#error CANTRCV_1_T03_E_PARAM_POINTER already defined!
#endif /* #if (defined CANTRCV_1_T03_E_PARAM_POINTER) */

#if (defined CANTRCV_1_T03_E_TRCV_NOT_STANDBY)      /* To prevent double declaration */
#error CANTRCV_1_T03_E_TRCV_NOT_STANDBY already defined!
#endif /* #if (defined CANTRCV_1_T03_E_TRCV_NOT_STANDBY) */

#if (defined CANTRCV_1_T03_E_UNINIT)      /* To prevent double declaration */
#error CANTRCV_1_T03_E_UNINIT already defined!
#endif /* #if (defined CANTRCV_1_T03_E_UNINIT) */

#if (defined CANTRCV_1_T03_E_TRCV_NOT_NORMAL)      /* To prevent double declaration */
#error CANTRCV_1_T03_E_TRCV_NOT_NORMAL already defined!
#endif /* #if (defined CANTRCV_1_T03_E_TRCV_NOT_NORMAL) */

#if (defined CANTRCV_1_T03_E_PARAM_TRCV_WAKEUP_MODE)      /* To prevent double declaration */
#error CANTRCV_1_T03_E_PARAM_TRCV_WAKEUP_MODE already defined!
#endif /* #if (defined CANTRCV_1_T03_E_PARAM_TRCV_WAKEUP_MODE) */

#if (defined CANTRCV_1_T03_E_PARAM_TRCV_OPMODE)      /* To prevent double declaration */
#error CANTRCV_1_T03_E_PARAM_TRCV_OPMODE already defined!
#endif /* #if (defined CANTRCV_1_T03_E_PARAM_TRCV_OPMODE) */

#if (defined CANTRCV_1_T03_E_BAUDRATE_NOT_SUPPORTED)      /* To prevent double declaration */
#error CANTRCV_1_T03_E_BAUDRATE_NOT_SUPPORTED already defined!
#endif /* #if (defined CANTRCV_1_T03_E_BAUDRATE_NOT_SUPPORTED) */

#if (defined CANTRCV_1_T03_E_NO_TRCV_CONTROL)      /* To prevent double declaration */
#error CANTRCV_1_T03_E_NO_TRCV_CONTROL already defined!
#endif /* #if (defined CANTRCV_1_T03_E_NO_TRCV_CONTROL) */

/** \brief API called with wrong parameter for transceiver DET error code */
#define       CANTRCV_1_T03_E_INVALID_TRANSCEIVER             0x01U
/** \brief API called with with null pointer parameter DET error code */
#define       CANTRCV_1_T03_E_PARAM_POINTER                   0x02U
/** \brief API service used without initialization DET error code */
#define       CANTRCV_1_T03_E_UNINIT                          0x11U
/** \brief API service called in wrong transceiver operation mode (1) DET error code */
#define       CANTRCV_1_T03_E_TRCV_NOT_STANDBY                0x21U
/** \brief API service called in wrong transceiver operation mode (2) DET error code */
#define       CANTRCV_1_T03_E_TRCV_NOT_NORMAL                 0x22U
/** \brief API service called with invalid parameter for TrcvWakeupMode DET error code */
#define       CANTRCV_1_T03_E_PARAM_TRCV_WAKEUP_MODE          0x23U
/** \brief API service called with invalid parameter for TrcvOperationMode DET error code */
#define       CANTRCV_1_T03_E_PARAM_TRCV_OPMODE               0x24U
/** \brief API service called with invalid parameter for Baudrate DET error code */
#define       CANTRCV_1_T03_E_BAUDRATE_NOT_SUPPORTED          0x25U
/** \brief API service called with invalid parameter for no/incorrect communication to Transceiver DET error code */
#define       CANTRCV_1_T03_E_NO_TRCV_CONTROL                 0x26U

/*------------------[function like marcros]--------------------------------*/

/*==================[type definitions]=======================================*/

/*==================[external function declarations]=========================*/

#define CANTRCV_1_T03_START_SEC_CODE
#include <CanTrcv_1_T03_MemMap.h>

/** \brief Validate configuration
 **
 ** Checks if the post build configuration fits to the link time configuration part.
 **
 ** \return E_OK if the given module configurations is valid otherwise E_NOT_OK.
 **
 ** \ServiceID{0x60}
 ** \Reentrancy{Reentrant}
 ** \Synchronicity{Synchronous}
 **/
extern FUNC(Std_ReturnType, CANTRCV_1_T03_CODE) CanTrcv_1_T03_IsValidConfig(
    P2CONST(void, AUTOMATIC, CANTRCV_1_T03_APPL_CONST) voidConfigPtr);

/** \brief CAN transceiver initialization function
 **
 ** This function initializes the CAN transceiver module.
 **
 ** \ServiceID{0x00}
 ** \Reentrancy{Non-Reentrant}
 ** \Synchronicity{Synchronous}
 */
extern FUNC( void, CANTRCV_1_T03_CODE ) CanTrcv_1_T03_Init
(
  P2CONST(CanTrcv_1_T03_ConfigType, AUTOMATIC, CANTRCV_1_T03_APPL_CONST) ConfigPtr
);

#if (CANTRCV_1_T03_OPERATION_MODE_API == STD_ON)
/** \brief CAN transceiver set operation mode function
 **
 ** This function sets the mode of the transceiver
 **
 ** \param[in] Transceiver Index of the transceiver
 ** \param[in] OpMode Desired operating mode
 **
 ** \return Result of operation
 ** \retval E_OK      transceiver state has been changed to the requested mode
 ** \retval E_NOT_OK  transceiver state change has failed or the parameter is out of allowed range
 **
 ** \ServiceID{0x01}
 ** \Reentrancy{Non-Reentrant}
 ** \Synchronicity{Synchronous}
 */
extern FUNC( Std_ReturnType, CANTRCV_1_T03_CODE ) CanTrcv_1_T03_SetOpMode
(
  uint8 Transceiver,
  CanTrcv_TrcvModeType OpMode
);

/** \brief CAN transceiver get operation mode function
 **
 ** This function gets the mode of the transceiver
 **
 ** \param[in] Transceiver Index of the transceiver
 ** \param[out] OpMode Pointer to operation mode of the bus
 **
 ** \return Result of operation
 ** \retval E_OK      operation mode was detected
 ** \retval E_NOT_OK  operation mode was not detected
 **
 ** \ServiceID{0x02}
 ** \Reentrancy{Reentrant}
 ** \Synchronicity{Synchronous}
 */
extern FUNC( Std_ReturnType, CANTRCV_1_T03_CODE ) CanTrcv_1_T03_GetOpMode
(
  uint8 Transceiver,
  P2VAR( CanTrcv_TrcvModeType, AUTOMATIC, CANTRCV_1_T03_APPL_DATA ) OpMode
);
#endif /* CANTRCV_1_T03_OPERATION_MODE_API == STD_ON */

#if (CANTRCV_1_T03_WAKEUP_MODE_API == STD_ON)
/** \brief CAN transceiver get wakeup reason function
 **
 ** This function gets the wakeup reason for the channel CanNetwork
 **
 ** \param[in] Transceiver Index of the transceiver
 ** \param[out] reason Pointer to wake up reason of the bus
 **
 ** \return Result of operation
 ** \retval E_OK      wake up reason was detected
 ** \retval E_NOT_OK  wake up reason was not detected
 **
 ** \ServiceID{0x03}
 ** \Reentrancy{Reentrant}
 ** \Synchronicity{Synchronous}
 */
extern FUNC( Std_ReturnType, CANTRCV_1_T03_CODE ) CanTrcv_1_T03_GetBusWuReason
(
  uint8 Transceiver,
  P2VAR( CanTrcv_TrcvWakeupReasonType, AUTOMATIC, CANTRCV_1_T03_APPL_DATA ) reason
);

/** \brief CAN transceiver set wakeup mode function
 **
 ** This function enables, disables or clears wake-up events
 **
 ** \param[in] Transceiver Index of the transceiver
 ** \param[in] TrcvWakeupMode Requested transceiver wakeup reason
 **
 ** \return Result of operation
 ** \retval E_OK      wakeup state has been changed to the requested mode
 ** \retval E_NOT_OK  wakeup state change has failed or the parameter is out of the allowed range
 **
 ** \ServiceID{0x05}
 ** \Reentrancy{Non-Reentrant}
 ** \Synchronicity{Synchronous}
 */
extern FUNC( Std_ReturnType, CANTRCV_1_T03_CODE ) CanTrcv_1_T03_SetWakeupMode
(
  uint8 Transceiver,
  CanTrcv_TrcvWakeupModeType TrcvWakeupMode
);

/** \brief CAN transceiver check for wakeup function
 **
 ** This function checks for wake-up events
 **
 ** \param[in] Transceiver Index of the transceiver
 **
 ** \return Result of operation
 ** \retval E_OK      valid interrupt detected
 ** \retval E_NOT_OK  no interrupt detected
 **
 ** \ServiceID{0x07}
 ** \Reentrancy{Non-Reentrant}
 ** \Synchronicity{Synchronous}
 */
extern FUNC( Std_ReturnType, CANTRCV_1_T03_CODE ) CanTrcv_1_T03_CheckWakeup
(
  uint8 Transceiver
);
#endif /* CANTRCV_1_T03_WAKEUP_MODE_API == STD_ON */

#if (CANTRCV_1_T03_GET_VERSION_INFO == STD_ON)
/** \brief CAN transceiver get version info function
 **
 ** This function gets the version of the module
 **
 ** \param[out] versioninfo Pointer to version information of this module
 **
 ** \ServiceID{0x04}
 ** \Reentrancy{Non-Reentrant}
 ** \Synchronicity{Synchronous}
 */
extern FUNC( void, CANTRCV_1_T03_CODE ) CanTrcv_1_T03_GetVersionInfo
(
  P2VAR( Std_VersionInfoType, AUTOMATIC, CANTRCV_1_T03_APPL_DATA ) versioninfo
);
#endif /* CANTRCV_1_T03_GET_VERSION_INFO == STD_ON */

#if (CANTRCV_1_T03_PN_SUPPORT == STD_ON)
/** \brief CAN transceiver coniguration/status data function
 **
 ** This function checks the transceive configuration/status of registers:
 ** Mode control register (address 01h)
 ** CAN control register (address 20h)
 ** Transceiver status register (address 22h)
 ** Transceiver event capture enable register (address 23h)
 **
 ** \param[in] Transceiver Index of the transceiver
 **            TrcvSysData Configuration/status of the transceiver
 **
 ** \return Result of operation
 ** \retval E_OK      Trcv reading status
 ** \retval E_NOT_OK  Wrong reading, data not available
 **
 ** \ServiceID{0x09}
 ** \Reentrancy{Non-Reentrant}
 ** \Synchronicity{Synchronous}
 */

extern FUNC( Std_ReturnType, CANTRCV_1_T03_CODE ) CanTrcv_1_T03_GetTrcvSystemData
(
    uint8 Transceiver,
    P2CONST (uint32, AUTOMATIC, CANTRCV_1_T03_APPL_CONST) TrcvSysData

);

/** \brief CAN transceiver clear WUF flag
 **
 ** This function clear all WU flags and also global register
 **
 ** \param[in] Transceiver Index of the transceiver
 **
 ** \return Result of operation
 ** \retval E_OK      flag event clear ok
 ** \retval E_NOT_OK  flag even clear not done
 **
 ** \ServiceID{0x0A}
 ** \Reentrancy{Reentrant}
 ** \Synchronicity{Synchronous}
 */
extern FUNC( Std_ReturnType, CANTRCV_1_T03_CODE ) CanTrcv_1_T03_ClearTrcvWufFlag
(
    uint8 Transceiver
);

/** \brief CAN transceiver read timeout flag
 **
 ** This function read the flag CFS to know if it
 ** has been set and fill in FlagState
 **
 ** \param[in] Transceiver Index of the transceiver
 **            FlagState Set the CFS status
 **
 ** \return Result of operation
 ** \retval E_OK      flag CFS as been read
 ** \retval E_NOT_OK  error during acces to CFS flag
 **
 ** \ServiceID{0x0B}
 ** \Reentrancy{Non-Reentrant}
 ** \Synchronicity{Synchronous}
 */

extern FUNC( Std_ReturnType, CANTRCV_1_T03_CODE ) CanTrcv_1_T03_ReadTrcvTimeoutFlag
(
    uint8 Transceiver,
    P2VAR(CanTrcv_TrcvFlagStateType, AUTOMATIC, CANTRCV_1_T03_APPL_DATA) FlagState
);

/** \brief Clear timeout flag of transceiver
 **
 ** This function will clear the flag CF
 ** in charge of managing CAN failure anor dominant clamped Tx
 **
 ** \param[in] Transceiver Index of the transceiver
 **
 ** \return Result of operation
 ** \retval E_OK      flag CF clear
 ** \retval E_NOT_OK  error during clearing CFS flag
 **
 ** \ServiceID{0x0C}
 ** \Reentrancy{Non-Reentrant}
 ** \Synchronicity{Synchronous}
 */

extern FUNC( Std_ReturnType, CANTRCV_1_T03_CODE ) CanTrcv_1_T03_ClearTrcvTimeoutFlag
(
    uint8 Transceiver
);

/** \brief Read slicence flag
 **
 ** This function read the flag CBS and CBSS
 ** to check if activities occur on the network
 **
 ** \param[in] Transceiver Index of the transceiver
 **            FlagState Set the status of the network
 **
 ** \return Result of operation
 ** \retval E_OK      flags read ok
 ** \retval E_NOT_OK  issue for reading flags
 **
 ** \ServiceID{0x0D}
 ** \Reentrancy{Non-Reentrant}
 ** \Synchronicity{Synchronous}
 */

extern FUNC( Std_ReturnType, CANTRCV_1_T03_CODE ) CanTrcv_1_T03_ReadTrcvSilenceFlag
(
    uint8 Transceiver,
    P2VAR(CanTrcv_TrcvFlagStateType, AUTOMATIC, CANTRCV_1_T03_APPL_DATA) FlagState
);

/** \brief Manage PN (dis)activation
 **
 ** Calling this function allows to activate or not
 ** the PN of the transceiver modifying CPNC bit
 **
 ** \param[in] ActivationState (dis)active PN mode
 **
 ** \return Result of operation
 ** \retval E_OK      PN has been changed to the requested configuration
 ** \retval E_NOT_OK  PN configuration change has failed
 **
 ** \ServiceID{0x0F}
 ** \Reentrancy{Non-Reentrant}
 ** \Synchronicity{Synchronous}
 */

extern FUNC( Std_ReturnType, CANTRCV_1_T03_CODE ) CanTrcv_1_T03_SetPNActivationState
(
    CanTrcv_PNActivationType ActivationState
);

/** \brief Check wake flag
 **
 ** Check the status of the wakeup flag
 ** from the transceiver hardware
 **
 ** \param[in] Transceiver Index of the transceiver
 **
 ** \return Result of operation
 ** \retval E_OK      check of the WU flag OK
 ** \retval E_NOT_OK  check WU flag not accepted
 **
 ** \ServiceID{0x0E}
 ** \Reentrancy{Non-Reentrant}
 ** \Synchronicity{Synchronous}
 */

extern FUNC( Std_ReturnType, CANTRCV_1_T03_CODE )  CanTrcv_1_T03_CheckWakeFlag
(
    uint8 Transceiver
);
#endif /* CANTRCV_1_T03_PN_SUPPORT == STD_ON */

#if (defined CanTrcv_1_T03_MainFunction)      /* To prevent double declaration */
#error CanTrcv_1_T03_MainFunction already defined!
#endif /* #if (defined CanTrcv_1_T03_MainFunction) */

/** \brief CAN transceiver main function
 **
 ** Main function of Can Tranceiver.
 ** Note: In this implementation the MainFunction has no functionality
 ** (it is possible to satisfy the AUTOSAR 4.0 spec without MainFunction).
 ** Therefore and for optimization reason the function is defined as empty macro.
 **
 ** \ServiceID{0x06}
 ** \Synchronicity{FIXED_CYCLIC}
 */
#define CanTrcv_1_T03_MainFunction()


#if (defined CanTrcv_1_T03_MainFunctionDiagnostics)      /* To prevent double declaration */
#error CanTrcv_1_T03_MainFunctionDiagnostics already defined!
#endif /* #if (defined CanTrcv_1_T03_MainFunctionDiagnostics) */

/** \brief Main function Diagnostics
 **
 ** Service to read the transceiver diagnostic
 ** status periodically and sets products/development accordingly
 **
 ** \ServiceID{0x08}
 ** \Synchronicity{FIXED_CYCLIC}
 */
#define CanTrcv_1_T03_MainFunctionDiagnostics()


#define CANTRCV_1_T03_STOP_SEC_CODE
#include <CanTrcv_1_T03_MemMap.h>

/*==================[internal function declarations]=========================*/

/*==================[external constants]=====================================*/

/*==================[internal constants]=====================================*/

/*==================[external data]==========================================*/

/*==================[internal data]==========================================*/

/*==================[external function definitions]==========================*/

/*==================[internal function definitions]==========================*/

#endif /* #if (!defined CANTRCV_1_T03_H) */

/*==================[end of file]============================================*/
