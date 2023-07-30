/**EB_Automotive_C_Source_File */

#if (!defined CANTRCV_1_T03_TRACE_H)
#define CANTRCV_1_T03_TRACE_H
/*==================[inclusions]============================================*/

#include <Std_Types.h>

/* Check if BASE_DBG_ENABLE is defined and set to STD_ON.
 * If so, include Base_Dbg.h which includes a custom header file */
#if (defined BASE_DBG_ENABLE)
#if (BASE_DBG_ENABLE == STD_ON)

#include <Base_Dbg.h>

#endif
#endif
#include <CanTrcv_1_T03_Trace_Internal.h>

/*==================[macros]================================================*/

/** @cond
 ** \brief Exclude section from doxygen */
#ifndef DBG_CANTRCV_1_T03_ISVALIDCONFIG_ENTRY
/** \brief Entry point of function CanTrcv_1_T03_IsValidConfig()
 **
 ** The macro takes the function arguments as parameters.
 */
#define DBG_CANTRCV_1_T03_ISVALIDCONFIG_ENTRY(voidConfigPtr)
#endif
/** \brief Exclude section from doxygen
 ** @endcond */

/** @cond
 ** \brief Exclude section from doxygen */
#ifndef DBG_CANTRCV_1_T03_ISVALIDCONFIG_EXIT
/** \brief Exit point of function CanTrcv_1_T03_IsValidConfig()
 **
 ** The first parameter of the macro is the return
 ** value of the function, followed by the arguments
 ** of the function.
 */
#define DBG_CANTRCV_1_T03_ISVALIDCONFIG_EXIT(Retval,voidConfigPtr)
#endif
/** \brief Exclude section from doxygen
 ** @endcond */


/** @cond
 ** \brief Exclude section from doxygen */
#ifndef DBG_CANTRCV_1_T03_INIT_ENTRY
/** \brief Entry point of function CanTrcv_1_T03_Init()
 **
 ** The macro takes the function arguments as parameters.
 */
#define DBG_CANTRCV_1_T03_INIT_ENTRY(ConfigPtr)
#endif
/** \brief Exclude section from doxygen
 ** @endcond */

/** @cond
 ** \brief Exclude section from doxygen */
#ifndef DBG_CANTRCV_1_T03_INIT_EXIT
/** \brief Exit point of function CanTrcv_1_T03_Init()
 **
 ** The macro takes the function arguments as parameters.
 */
#define DBG_CANTRCV_1_T03_INIT_EXIT(ConfigPtr)
#endif
/** \brief Exclude section from doxygen
 ** @endcond */


/** @cond
 ** \brief Exclude section from doxygen */
#ifndef DBG_CANTRCV_1_T03_SETOPMODE_ENTRY
/** \brief Entry point of function CanTrcv_1_T03_SetOpMode()
 **
 ** The macro takes the function arguments as parameters.
 */
#define DBG_CANTRCV_1_T03_SETOPMODE_ENTRY(Transceiver,OpMode)
#endif
/** \brief Exclude section from doxygen
 ** @endcond */

/** @cond
 ** \brief Exclude section from doxygen */
#ifndef DBG_CANTRCV_1_T03_SETOPMODE_EXIT
/** \brief Exit point of function CanTrcv_1_T03_SetOpMode()
 **
 ** The first parameter of the macro is the return
 ** value of the function, followed by the arguments
 ** of the function.
 */
#define DBG_CANTRCV_1_T03_SETOPMODE_EXIT(Retval,Transceiver,OpMode)
#endif
/** \brief Exclude section from doxygen
 ** @endcond */


/** @cond
 ** \brief Exclude section from doxygen */
#ifndef DBG_CANTRCV_1_T03_GETOPMODE_ENTRY
/** \brief Entry point of function CanTrcv_1_T03_GetOpMode()
 **
 ** The macro takes the function arguments as parameters.
 */
#define DBG_CANTRCV_1_T03_GETOPMODE_ENTRY(Transceiver,OpMode)
#endif
/** \brief Exclude section from doxygen
 ** @endcond */

/** @cond
 ** \brief Exclude section from doxygen */
#ifndef DBG_CANTRCV_1_T03_GETOPMODE_EXIT
/** \brief Exit point of function CanTrcv_1_T03_GetOpMode()
 **
 ** The first parameter of the macro is the return
 ** value of the function, followed by the arguments
 ** of the function.
 */
#define DBG_CANTRCV_1_T03_GETOPMODE_EXIT(Retval,Transceiver,OpMode)
#endif
/** \brief Exclude section from doxygen
 ** @endcond */


/** @cond
 ** \brief Exclude section from doxygen */
#ifndef DBG_CANTRCV_1_T03_GETBUSWUREASON_ENTRY
/** \brief Entry point of function CanTrcv_1_T03_GetBusWuReason()
 **
 ** The macro takes the function arguments as parameters.
 */
#define DBG_CANTRCV_1_T03_GETBUSWUREASON_ENTRY(Transceiver,reason)
#endif
/** \brief Exclude section from doxygen
 ** @endcond */

/** @cond
 ** \brief Exclude section from doxygen */
#ifndef DBG_CANTRCV_1_T03_GETBUSWUREASON_EXIT
/** \brief Exit point of function CanTrcv_1_T03_GetBusWuReason()
 **
 ** The first parameter of the macro is the return
 ** value of the function, followed by the arguments
 ** of the function.
 */
#define DBG_CANTRCV_1_T03_GETBUSWUREASON_EXIT(Retval,Transceiver,reason)
#endif
/** \brief Exclude section from doxygen
 ** @endcond */


/** @cond
 ** \brief Exclude section from doxygen */
#ifndef DBG_CANTRCV_1_T03_SETWAKEUPMODE_ENTRY
/** \brief Entry point of function CanTrcv_1_T03_SetWakeupMode()
 **
 ** The macro takes the function arguments as parameters.
 */
#define DBG_CANTRCV_1_T03_SETWAKEUPMODE_ENTRY(Transceiver,TrcvWakeupMode)
#endif
/** \brief Exclude section from doxygen
 ** @endcond */

/** @cond
 ** \brief Exclude section from doxygen */
#ifndef DBG_CANTRCV_1_T03_SETWAKEUPMODE_EXIT
/** \brief Exit point of function CanTrcv_1_T03_SetWakeupMode()
 **
 ** The first parameter of the macro is the return
 ** value of the function, followed by the arguments
 ** of the function.
 */
#define DBG_CANTRCV_1_T03_SETWAKEUPMODE_EXIT(Retval,Transceiver,TrcvWakeupMode)
#endif
/** \brief Exclude section from doxygen
 ** @endcond */


/** @cond
 ** \brief Exclude section from doxygen */
#ifndef DBG_CANTRCV_1_T03_CHECKWAKEUP_ENTRY
/** \brief Entry point of function CanTrcv_1_T03_CheckWakeup()
 **
 ** The macro takes the function arguments as parameters.
 */
#define DBG_CANTRCV_1_T03_CHECKWAKEUP_ENTRY(Transceiver)
#endif
/** \brief Exclude section from doxygen
 ** @endcond */

/** @cond
 ** \brief Exclude section from doxygen */
#ifndef DBG_CANTRCV_1_T03_CHECKWAKEUP_EXIT
/** \brief Exit point of function CanTrcv_1_T03_CheckWakeup()
 **
 ** The first parameter of the macro is the return
 ** value of the function, followed by the arguments
 ** of the function.
 */
#define DBG_CANTRCV_1_T03_CHECKWAKEUP_EXIT(Retval,Transceiver)
#endif
/** \brief Exclude section from doxygen
 ** @endcond */


/** @cond
 ** \brief Exclude section from doxygen */
#ifndef DBG_CANTRCV_1_T03_GETVERSIONINFO_ENTRY
/** \brief Entry point of function CanTrcv_1_T03_GetVersionInfo()
 **
 ** The macro takes the function arguments as parameters.
 */
#define DBG_CANTRCV_1_T03_GETVERSIONINFO_ENTRY(versioninfo)
#endif
/** \brief Exclude section from doxygen
 ** @endcond */

/** @cond
 ** \brief Exclude section from doxygen */
#ifndef DBG_CANTRCV_1_T03_GETVERSIONINFO_EXIT
/** \brief Exit point of function CanTrcv_1_T03_GetVersionInfo()
 **
 ** The macro takes the function arguments as parameters.
 */
#define DBG_CANTRCV_1_T03_GETVERSIONINFO_EXIT(versioninfo)
#endif
/** \brief Exclude section from doxygen
 ** @endcond */


/** @cond
 ** \brief Exclude section from doxygen */
#ifndef DBG_CANTRCV_1_T03_GETTRCVSYSTEMDATA_ENTRY
/** \brief Entry point of function CanTrcv_1_T03_GetTrcvSystemData()
 **
 ** The macro takes the function arguments as parameters.
 */
#define DBG_CANTRCV_1_T03_GETTRCVSYSTEMDATA_ENTRY(Transceiver,TrcvSysData)
#endif
/** \brief Exclude section from doxygen
 ** @endcond */

/** @cond
 ** \brief Exclude section from doxygen */
#ifndef DBG_CANTRCV_1_T03_GETTRCVSYSTEMDATA_EXIT
/** \brief Exit point of function CanTrcv_1_T03_GetTrcvSystemData()
 **
 ** The first parameter of the macro is the return
 ** value of the function, followed by the arguments
 ** of the function.
 */
#define DBG_CANTRCV_1_T03_GETTRCVSYSTEMDATA_EXIT(Retval,Transceiver,TrcvSysData)
#endif
/** \brief Exclude section from doxygen
 ** @endcond */


/** @cond
 ** \brief Exclude section from doxygen */
#ifndef DBG_CANTRCV_1_T03_CLEARTRCVWUFFLAG_ENTRY
/** \brief Entry point of function CanTrcv_1_T03_ClearTrcvWufFlag()
 **
 ** The macro takes the function arguments as parameters.
 */
#define DBG_CANTRCV_1_T03_CLEARTRCVWUFFLAG_ENTRY(Transceiver)
#endif
/** \brief Exclude section from doxygen
 ** @endcond */

/** @cond
 ** \brief Exclude section from doxygen */
#ifndef DBG_CANTRCV_1_T03_CLEARTRCVWUFFLAG_EXIT
/** \brief Exit point of function CanTrcv_1_T03_ClearTrcvWufFlag()
 **
 ** The first parameter of the macro is the return
 ** value of the function, followed by the arguments
 ** of the function.
 */
#define DBG_CANTRCV_1_T03_CLEARTRCVWUFFLAG_EXIT(Retval,Transceiver)
#endif
/** \brief Exclude section from doxygen
 ** @endcond */


/** @cond
 ** \brief Exclude section from doxygen */
#ifndef DBG_CANTRCV_1_T03_READTRCVTIMEOUTFLAG_ENTRY
/** \brief Entry point of function CanTrcv_1_T03_ReadTrcvTimeoutFlag()
 **
 ** The macro takes the function arguments as parameters.
 */
#define DBG_CANTRCV_1_T03_READTRCVTIMEOUTFLAG_ENTRY(Transceiver,FlagState)
#endif
/** \brief Exclude section from doxygen
 ** @endcond */

/** @cond
 ** \brief Exclude section from doxygen */
#ifndef DBG_CANTRCV_1_T03_READTRCVTIMEOUTFLAG_EXIT
/** \brief Exit point of function CanTrcv_1_T03_ReadTrcvTimeoutFlag()
 **
 ** The first parameter of the macro is the return
 ** value of the function, followed by the arguments
 ** of the function.
 */
#define DBG_CANTRCV_1_T03_READTRCVTIMEOUTFLAG_EXIT(Retval,Transceiver,FlagState)
#endif
/** \brief Exclude section from doxygen
 ** @endcond */


/** @cond
 ** \brief Exclude section from doxygen */
#ifndef DBG_CANTRCV_1_T03_CLEARTRCVTIMEOUTFLAG_ENTRY
/** \brief Entry point of function CanTrcv_1_T03_ClearTrcvTimeoutFlag()
 **
 ** The macro takes the function arguments as parameters.
 */
#define DBG_CANTRCV_1_T03_CLEARTRCVTIMEOUTFLAG_ENTRY(Transceiver)
#endif
/** \brief Exclude section from doxygen
 ** @endcond */

/** @cond
 ** \brief Exclude section from doxygen */
#ifndef DBG_CANTRCV_1_T03_CLEARTRCVTIMEOUTFLAG_EXIT
/** \brief Exit point of function CanTrcv_1_T03_ClearTrcvTimeoutFlag()
 **
 ** The first parameter of the macro is the return
 ** value of the function, followed by the arguments
 ** of the function.
 */
#define DBG_CANTRCV_1_T03_CLEARTRCVTIMEOUTFLAG_EXIT(Retval,Transceiver)
#endif
/** \brief Exclude section from doxygen
 ** @endcond */


/** @cond
 ** \brief Exclude section from doxygen */
#ifndef DBG_CANTRCV_1_T03_READTRCVSILENCEFLAG_ENTRY
/** \brief Entry point of function CanTrcv_1_T03_ReadTrcvSilenceFlag()
 **
 ** The macro takes the function arguments as parameters.
 */
#define DBG_CANTRCV_1_T03_READTRCVSILENCEFLAG_ENTRY(Transceiver,FlagState)
#endif
/** \brief Exclude section from doxygen
 ** @endcond */

/** @cond
 ** \brief Exclude section from doxygen */
#ifndef DBG_CANTRCV_1_T03_READTRCVSILENCEFLAG_EXIT
/** \brief Exit point of function CanTrcv_1_T03_ReadTrcvSilenceFlag()
 **
 ** The first parameter of the macro is the return
 ** value of the function, followed by the arguments
 ** of the function.
 */
#define DBG_CANTRCV_1_T03_READTRCVSILENCEFLAG_EXIT(Retval,Transceiver,FlagState)
#endif
/** \brief Exclude section from doxygen
 ** @endcond */


/** @cond
 ** \brief Exclude section from doxygen */
#ifndef DBG_CANTRCV_1_T03_SETPNACTIVATIONSTATE_ENTRY
/** \brief Entry point of function CanTrcv_1_T03_SetPNActivationState()
 **
 ** The macro takes the function arguments as parameters.
 */
#define DBG_CANTRCV_1_T03_SETPNACTIVATIONSTATE_ENTRY(ActivationState)
#endif
/** \brief Exclude section from doxygen
 ** @endcond */

/** @cond
 ** \brief Exclude section from doxygen */
#ifndef DBG_CANTRCV_1_T03_SETPNACTIVATIONSTATE_EXIT
/** \brief Exit point of function CanTrcv_1_T03_SetPNActivationState()
 **
 ** The first parameter of the macro is the return
 ** value of the function, followed by the arguments
 ** of the function.
 */
#define DBG_CANTRCV_1_T03_SETPNACTIVATIONSTATE_EXIT(Retval,ActivationState)
#endif
/** \brief Exclude section from doxygen
 ** @endcond */


/** @cond
 ** \brief Exclude section from doxygen */
#ifndef DBG_CANTRCV_1_T03_CHECKWAKEFLAG_ENTRY
/** \brief Entry point of function CanTrcv_1_T03_CheckWakeFlag()
 **
 ** The macro takes the function arguments as parameters.
 */
#define DBG_CANTRCV_1_T03_CHECKWAKEFLAG_ENTRY(Transceiver)
#endif
/** \brief Exclude section from doxygen
 ** @endcond */

/** @cond
 ** \brief Exclude section from doxygen */
#ifndef DBG_CANTRCV_1_T03_CHECKWAKEFLAG_EXIT
/** \brief Exit point of function CanTrcv_1_T03_CheckWakeFlag()
 **
 ** The first parameter of the macro is the return
 ** value of the function, followed by the arguments
 ** of the function.
 */
#define DBG_CANTRCV_1_T03_CHECKWAKEFLAG_EXIT(Retval,Transceiver)
#endif
/** \brief Exclude section from doxygen
 ** @endcond */


/*==================[type definitions]======================================*/

/*==================[external function declarations]========================*/

/*==================[internal function declarations]========================*/

/*==================[external constants]====================================*/

/*==================[internal constants]====================================*/

/*==================[external data]=========================================*/

/*==================[internal data]=========================================*/

/*==================[external function definitions]=========================*/

/*==================[internal function definitions]=========================*/

#endif /* (!defined CANTRCV_1_T03_TRACE_H) */
/*==================[end of file]===========================================*/
