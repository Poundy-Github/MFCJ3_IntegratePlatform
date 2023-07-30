/**EB_Automotive_C_Source_File */

/*
 * MISRA-C:2012 Deviation List
 *
 * MISRAC2012-1) Deviated Rule: 8.11 (advisory)
 * When an array with external linkage is declared, its size should be
 * explicitly specified.
 *
 * Reason:
 * Since this is a link-time configuration parameter, the size of the array
 * depends on the configuration.
 *
 * MISRA-2) Deviated Rule: 19.6 (required)
 * #undef shall not be used.
 *
 * Reason:
 * In order to modify the behavior of the included file, enclosing the file
 * inclusion by a special macro definition is required.
 *
 * MISRA-3) Deviated Rule: 19.10 (required)
 * Parameter instance shall be enclosed in parentheses.
 *
 * Reason:
 * Enclosing the parameter in parentheses is not possible, because it results
 * in compiler syntax error.
 *
 */

#if (!defined CANTRCV_1_T03_INT_H)
#define CANTRCV_1_T03_INT_H

/*==================[inclusions]=============================================*/

#include <CanTrcv_1_T03_Cfg.h>    /* CANTRCV_1_T03_RELOCATABLE_CFG_ENABLE */
#include <CanTrcv_1_T03_Types.h>

#include <Can_GeneralTypes.h>     /* CanTrcv_TrcvWakeupReasonType */

#if (defined TS_RELOCATABLE_CFG_ENABLE)      /* To prevent double declaration */
#error TS_RELOCATABLE_CFG_ENABLE already defined!
#endif /* #if (defined TS_RELOCATABLE_CFG_ENABLE) */

#define TS_RELOCATABLE_CFG_ENABLE CANTRCV_1_T03_RELOCATABLE_CFG_ENABLE

#include <TSPBConfig_Access.h>
#include <TSPBConfig_Signature.h>           /* relocatable post-build macros */

/*==================[macros]=================================================*/

/* relocatable post build elements access macros. */

#if (defined CANTRCV_1_T03_PBCFG_ACCESS)      /* To prevent double declaration */
#error CANTRCV_1_T03_PBCFG_ACCESS already defined!
#endif /* #if (defined CANTRCV_1_T03_PBCFG_ACCESS) */

#if (defined CANTRCV_1_T03_CFG_GET_CHANNEL_CFG)      /* To prevent double declaration */
#error CANTRCV_1_T03_CFG_GET_CHANNEL_CFG already defined!
#endif /* #if (defined CANTRCV_1_T03_CFG_GET_CHANNEL_CFG) */

/* Deviation MISRA-3 <START> */
#define CANTRCV_1_T03_PBCFG_ACCESS(type, element) \
 (TS_UNCHECKEDGETCFG(CanTrcv_1_T03_ConfigPtr,type,CANTRCV_1_T03,CanTrcv_1_T03_ConfigPtr->element))
/* Deviation MISRA-3 <STOP> */

#define CANTRCV_1_T03_CFG_GET_CHANNEL_CFG(Index)   \
    (CANTRCV_1_T03_PBCFG_ACCESS(CanTrcv_1_T03_ChannelConfigType, channelConfigPtr)[(Index)])

/*==================[type definitions]=======================================*/

/** \brief
 **
 ** This structure contains the runtime information required per transceiver.
 */
typedef struct
{

#if (CANTRCV_1_T03_GENERAL_WAKE_UP_SUPPORT != CANTRCV_1_T03_WAKEUP_NOT_SUPPORTED)

    VAR(uint32, TYPEDEF)                        WakeupSource;
    /**< member stores current wakeup source if wakeup report is disabled */

    VAR(CanTrcv_TrcvWakeupReasonType, TYPEDEF)  WakeupReason;
    /**< member stores current transceiver wakeup reason information */

    VAR(boolean, TYPEDEF)                       WakeupModeEnabled;
    /**< member stores if reporting of wakeup is currently enabled or disabled */

#endif /* CANTRCV_1_T03_GENERAL_WAKE_UP_SUPPORT != CANTRCV_1_T03_WAKEUP_NOT_SUPPORTED */

    VAR(uint8,TYPEDEF)                          CurrentMode;
    /**< member stores current transceiver Mode */

}CanTrcv_1_T03_TrcvStateType;

/*==================[external function declarations]=========================*/

/*==================[internal function declarations]=========================*/

/*==================[external constants]=====================================*/
#define CANTRCV_1_T03_START_SEC_VAR_INIT_UNSPECIFIED
#include <CanTrcv_1_T03_MemMap.h>

extern P2CONST(CanTrcv_1_T03_ConfigType, CANTRCV_1_T03_VAR, CANTRCV_1_T03_APPL_CONST) CanTrcv_1_T03_ConfigPtr;

#define CANTRCV_1_T03_STOP_SEC_VAR_INIT_UNSPECIFIED
#include <CanTrcv_1_T03_MemMap.h>
/*==================[internal constants]=====================================*/

/*==================[external data]==========================================*/

/*==================[internal data]==========================================*/

/*==================[external function definitions]==========================*/

/*==================[internal function definitions]==========================*/

/* Deviation MISRA-2 */
#undef TS_RELOCATABLE_CFG_ENABLE

#endif /* #if (!defined CANTRCV_1_T03_INT_H) */

/*==================[end of file]============================================*/

