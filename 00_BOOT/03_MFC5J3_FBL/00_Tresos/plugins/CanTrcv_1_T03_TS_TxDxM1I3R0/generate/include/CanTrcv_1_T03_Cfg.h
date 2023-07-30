/**EB_Automotive_C_Source_File */


#if (!defined CANTRCV_1_T03_CFG_H)
#define CANTRCV_1_T03_CFG_H

/* !LINKSTO CanTrcv.ASR40.CanTrcv083,1 */

/*==================[inclusions]=============================================*/

/* It is required by AUTOSAR include the headerfile that contains the
 * post-build/link-time symbolic IDs here */
/* This mixture of config classes can be omitted for module internal purposes */
#if !defined CANTRCV_1_T03_NO_CFGCLASSMIX_REQUIRED
#include <CanTrcv_1_T03_SymbolicNames_PBcfg.h>
#endif /* CANTRCV_1_T03_NO_CFGCLASSMIX_REQUIRED */

#undef CANTRCV_1_T03_NO_CFGCLASSMIX_REQUIRED

#include <Std_Types.h>            /* Standard types */

/*==================[macros]=================================================*/

[!SELECT "as:modconf('CanTrcv')[(CommonPublishedInformation/VendorId = 1) and (CommonPublishedInformation/VendorApiInfix = 'T03')]"!]

#if (defined CANTRCV_1_T03_WAKEUP_NOT_SUPPORTED)      /* To prevent double declaration */
#error CANTRCV_1_T03_WAKEUP_NOT_SUPPORTED already defined!
#endif /* #if (defined CANTRCV_1_T03_WAKEUP_NOT_SUPPORTED) */

#if (defined CANTRCV_1_T03_WAKEUP_BY_POLLING)      /* To prevent double declaration */
#error CANTRCV_1_T03_WAKEUP_BY_POLLING already defined!
#endif /* #if (defined CANTRCV_1_T03_WAKEUP_BY_POLLING) */

/* Possible values of CANTRCV_1_T03_GENERAL_WAKE_UP_SUPPORT */
#define CANTRCV_1_T03_WAKEUP_NOT_SUPPORTED    0U
#define CANTRCV_1_T03_WAKEUP_BY_POLLING       1U


/* standard SWS pre-compile time configuration parameters */

#if (defined CANTRCV_1_T03_DEV_ERROR_DETECT)      /* To prevent double declaration */
#error CANTRCV_1_T03_DEV_ERROR_DETECT already defined!
#endif /* #if (defined CANTRCV_1_T03_DEV_ERROR_DETECT) */

/** \brief Development error detection support
 **
 ** This configuration parameter defines if development error detection is enabled
 */
[!IF "CanTrcvGeneral/CanTrcvDevErrorDetect = 'true'"!][!//
#define CANTRCV_1_T03_DEV_ERROR_DETECT STD_ON
[!ELSE!][!//
#define CANTRCV_1_T03_DEV_ERROR_DETECT STD_OFF
[!ENDIF!][!//


#if (defined CANTRCV_1_T03_GET_VERSION_INFO)      /* To prevent double declaration */
#error CANTRCV_1_T03_GET_VERSION_INFO already defined!
#endif /* #if (defined CANTRCV_1_T03_GET_VERSION_INFO) */

/** \brief GetVersionAPI support
 **
 ** This configuration parameter defines if the GetVersionInfo API of the module exists
 */
[!IF "CanTrcvGeneral/CanTrcvGetVersionInfo = 'true'"!][!//
#define CANTRCV_1_T03_GET_VERSION_INFO STD_ON
[!ELSE!][!//
#define CANTRCV_1_T03_GET_VERSION_INFO STD_OFF
[!ENDIF!][!//


#if (defined CANTRCV_1_T03_GENERAL_WAKE_UP_SUPPORT)      /* To prevent double declaration */
#error CANTRCV_1_T03_GENERAL_WAKE_UP_SUPPORT already defined!
#endif /* #if (defined CANTRCV_1_T03_GENERAL_WAKE_UP_SUPPORT) */

/** \brief Wakeup support mode
 **
 ** This configuration parameter defines if and which wakeup support is selected
 ** Possible values are:
 **                      CANTRCV_1_T03_WAKEUP_NOT_SUPPORTED
 **                      CANTRCV_1_T03_WAKEUP_BY_POLLING
 ** 
 ** If nothing is selected the default value is CANTRCV_1_T03_WAKEUP_NOT_SUPPORTED
 */
[!IF "node:value(CanTrcvGeneral/CanTrcvWakeUpSupport) = 'CANTRCV_WAKEUP_BY_POLLING'"!]
#define CANTRCV_1_T03_GENERAL_WAKE_UP_SUPPORT  CANTRCV_1_T03_WAKEUP_BY_POLLING
[!ELSE!]
#define CANTRCV_1_T03_GENERAL_WAKE_UP_SUPPORT  CANTRCV_1_T03_WAKEUP_NOT_SUPPORTED
[!ENDIF!]


#if (defined CANTRCV_1_T03_INSTANCE_ID)      /* To prevent double declaration */
#error CANTRCV_1_T03_INSTANCE_ID already defined!
#endif /* #if (defined CANTRCV_1_T03_INSTANCE_ID) */

/** \brief Instance ID
 **
 ** This configuration parameter defines the instance ID of the module
 */
#define CANTRCV_1_T03_INSTANCE_ID 0U

#if (defined CANTRCV_1_T03_WAIT_COUNT)      /* To prevent double declaration */
#error CANTRCV_1_T03_WAIT_COUNT already defined!
#endif /* #if (defined CANTRCV_1_T03_WAIT_COUNT) */

/** \brief Wait count
 **
 ** This counter is used to realize wait states during operation mode changes
*/
#define CANTRCV_1_T03_WAIT_COUNT [!//
[!"num:i(node:value(CanTrcvGeneral/CanTrcvWaitCount))"!]U

#if (defined CANTRCV_1_T03_STANDARD_ID)      /* To prevent double declaration */
#error CANTRCV_1_T03_STANDARD_ID already defined!
#endif /* #if (defined CANTRCV_1_T03_STANDARD_ID) */

#if (defined CANTRCV_1_T03_EXTENDED_ID)      /* To prevent double declaration */
#error CANTRCV_1_T03_EXTENDED_ID already defined!
#endif /* #if (defined CANTRCV_1_T03_EXTENDED_ID) */

/** \brief ID type (Std / Ext)
 **
 ** Can identifier type of the Transceiver
 */
#define CANTRCV_1_T03_STANDARD_ID       0x0U
#define CANTRCV_1_T03_EXTENDED_ID       0x1U

#if (defined CANTRCV_1_T03_SPI_COMM_RETRIES)      /* To prevent double declaration */
#error CANTRCV_1_T03_SPI_COMM_RETRIES already defined!
#endif /* #if (defined CANTRCV_1_T03_SPI_COMM_RETRIES) */

/** \brief Wait count
 **
 ** This value indicates the maximal number of communication retries in case
 ** of failed SPI communications
 */
#define CANTRCV_1_T03_SPI_COMM_RETRIES [!//
[!"num:i(node:value(CanTrcvConfigSet/*[1]/CanTrcvSPICommRetries))"!]U

#if (defined CANTRCV_1_T03_SPI_TIMEOUT_COUNTER)      /* To prevent double declaration */
#error CANTRCV_1_T03_SPI_TIMEOUT_COUNTER already defined!
#endif /* #if (defined CANTRCV_1_T03_SPI_TIMEOUT_COUNTER) */

/** \brief Wait count
 **
 ** This value indicates the maximal number of communication retries 
 ** for polling SPI async result
 */

[!IF "node:exists(VendorSpecific/CanTrcvSpiAccessAsynchronousTimeout)"!][!//
#define CANTRCV_1_T03_SPI_TIMEOUT_COUNTER [!"num:i(node:value(VendorSpecific/CanTrcvSpiAccessAsynchronousTimeout))"!]U
[!ELSE!][!//
#define CANTRCV_1_T03_SPI_TIMEOUT_COUNTER 1U
[!ENDIF!][!//

#if (defined CANTRCV_1_T03_PN_SUPPORT)      /* To prevent double declaration */
#error CANTRCV_1_T03_PN_SUPPORT already defined!
#endif /* #if (defined CANTRCV_1_T03_PN_SUPPORT) */

/** \brief Selective wakeup support
 **
 ** This macro enables or disables selective wakeup support.
 */
[!IF "VendorSpecific/CanTrcvPnSupport = 'true'"!][!//
#define CANTRCV_1_T03_PN_SUPPORT          STD_ON
[!ELSE!][!//
#define CANTRCV_1_T03_PN_SUPPORT          STD_OFF
[!ENDIF!][!//

#if (defined CANTRCV_1_T03_FD_TOLERANCE)      /* To prevent double declaration */
#error CANTRCV_1_T03_FD_TOLERANCE already defined!
#endif /* #if (defined CANTRCV_1_T03_FD_TOLERANCE) */

/** \brief CAN-FD frame passive support with PN enabled
 **
 ** This macro enables or disables passive support
 */
#define CANTRCV_1_T03_FD_TOLERANCE        STD_O[!IF "VendorSpecific/CanTrcvCanFdTolerance = 'true'"!]N[!ELSE!]FF[!ENDIF!]


#if (defined CANTRCV_1_T03_OPERATION_MODE_API)      /* To prevent double declaration */
#error CANTRCV_1_T03_OPERATION_MODE_API already defined!
#endif /* #if (defined CANTRCV_1_T03_OPERATION_MODE_API) */


/** \brief Operation mode API support
 **
 ** This configuration parameter defines if the Operation mode API of the module
 ** (CanTrcv_SetOpMode and CanTrcv_GetOpMode) exists.
 */
[!IF "VendorSpecific/CanTrcvOperationModeApiEnable = 'true'"!][!//
#define CANTRCV_1_T03_OPERATION_MODE_API STD_ON
[!ELSE!][!//
#define CANTRCV_1_T03_OPERATION_MODE_API STD_OFF
[!ENDIF!][!//


#if (defined CANTRCV_1_T03_WAKEUP_MODE_API)      /* To prevent double declaration */
#error CANTRCV_1_T03_WAKEUP_MODE_API already defined!
#endif /* #if (defined CANTRCV_1_T03_WAKEUP_MODE_API) */

/** \brief Wakeup API support
 **
 ** This configuration parameter defines if the Wakeup API of the module
 ** (CanTrcv_GetBusWuReason and CanTrcv_SetWakeupMode) exists.
 */
[!IF "VendorSpecific/CanTrcvWakeupModeApiEnable = 'true'"!][!//
#define CANTRCV_1_T03_WAKEUP_MODE_API STD_ON
[!ELSE!][!//
#define CANTRCV_1_T03_WAKEUP_MODE_API STD_OFF
[!ENDIF!][!//

#if (defined CANTRCV_1_T03_ICU_DRIVER_SUPPORT)      /* To prevent double declaration */
#error CANTRCV_1_T03_ICU_DRIVER_SUPPORT already defined!
#endif /* #if (defined CANTRCV_1_T03_ICU_DRIVER_SUPPORT) */

/** \brief ICU driver API support
 **
 ** This configuration parameter defines if the CanTrcv uses the ICU driver API
 */
[!IF "VendorSpecific/CanTrcvIcuDriverSupportApiEnable = 'true'"!][!//
#define CANTRCV_1_T03_ICU_DRIVER_SUPPORT STD_ON
[!ELSE!][!//
#define CANTRCV_1_T03_ICU_DRIVER_SUPPORT STD_OFF
[!ENDIF!][!//

#if (defined CANTRCV_1_T03_CANIF_PN_CALLBACK_SUPPORT)      /* To prevent double declaration */
#error CANTRCV_1_T03_CANIF_PN_CALLBACK_SUPPORT already defined!
#endif /* #if (defined CANTRCV_1_T03_CANIF_PN_CALLBACK_SUPPORT) */

/** \brief CanIf callback API support
 **
 ** This configuration parameter defines if the CanTrcv uses CanIf PN callbacks
 */
[!IF "VendorSpecific/CanTrcvPnCanIfCallbackSupport = 'true'"!][!//
#define CANTRCV_1_T03_CANIF_PN_CALLBACK_SUPPORT STD_ON
[!ELSE!][!//
#define CANTRCV_1_T03_CANIF_PN_CALLBACK_SUPPORT STD_OFF
[!ENDIF!][!//

#if (defined CANTRCV_1_T03_MAX_NUMBER_OF_CHANNELS)      /* To prevent double declaration */
#error CANTRCV_1_T03_MAX_NUMBER_OF_CHANNELS already defined!
#endif /* #if (defined CANTRCV_1_T03_MAX_NUMBER_OF_CHANNELS) */

/** \brief Maximum possible number of CanTrcv channels
 **
 ** This configuration parameter defines the reserved memory in RAM for the CanTrcv
 ** channels. The number of configured channels must be smaller than this number.
 */
#define CANTRCV_1_T03_MAX_NUMBER_OF_CHANNELS  [!"VendorSpecific/CanTrcvMaxChannelNumber"!]U[!//

[!SELECT "VendorSpecific"!]

#if (defined CANTRCV_1_T03_PBCFGM_SUPPORT_ENABLED)
#error CANTRCV_1_T03_PBCFGM_SUPPORT_ENABLED already defined
#endif
/** \brief Indicates PbcfgM support for CanTrcv_1_T03 */
#define CANTRCV_1_T03_PBCFGM_SUPPORT_ENABLED [!IF "node:contains(node:refs(as:modconf('PbcfgM')/PbcfgMBswModules/*/PbcfgMBswModuleRef), as:modconf('CanTrcv')[(CommonPublishedInformation/VendorId = 1) and (CommonPublishedInformation/VendorApiInfix = 'T03')]) = 'true'"!]STD_ON[!ELSE!]STD_OFF[!ENDIF!]


/* ----- Pre-processor switch to enable/disable relocatable postbuild config ----- */
#if (CANTRCV_1_T03_PBCFGM_SUPPORT_ENABLED == STD_ON)

#if (defined CANTRCV_1_T03_RELOCATABLE_CFG_ENABLE)
#error CANTRCV_1_T03_RELOCATABLE_CFG_ENABLE already defined
#endif
#define CANTRCV_1_T03_RELOCATABLE_CFG_ENABLE [!IF "as:modconf('PbcfgM')/PbcfgMGeneral/PbcfgMRelocatableCfgEnable = 'true'"!]STD_ON[!ELSE!]STD_OFF[!ENDIF!]

#else

#if (defined CANTRCV_1_T03_RELOCATABLE_CFG_ENABLE)
#error CANTRCV_1_T03_RELOCATABLE_CFG_ENABLE already defined
#endif
#define CANTRCV_1_T03_RELOCATABLE_CFG_ENABLE [!IF "CanTrcvRelocatablePbcfgEnable = 'true'"!]STD_ON[!ELSE!]STD_OFF[!ENDIF!]

#endif
[!IF "not(node:exists(CanTrcvRelocatablePbcfgEnable))"!]
[!ERROR!]Parameter CanTrcvRelocatablePbcfgEnable can not be found in current path. Use SELECT to specify the path.[!ENDERROR!]
[!ENDIF!]
[!ENDSELECT!]

#if (defined CANTRCV_1_T03_CFG_SIGNATURE)      /* To prevent double declaration */
#error CANTRCV_1_T03_CFG_SIGNATURE already defined!
#endif /* #if (defined CANTRCV_1_T03_CFG_SIGNATURE) */

/** \brief Compile time verification value */
#define CANTRCV_1_T03_CFG_SIGNATURE [!"asc:getConfigSignature(.//*[not(child::*) and (node:configclass() = 'PreCompile') ])"!]U

#if (defined CANTRCV_1_T03_PUBLIC_INFO_SIGNATURE)      /* To prevent double declaration */
#error CANTRCV_1_T03_PUBLIC_INFO_SIGNATURE already defined!
#endif /* #if (defined CANTRCV_1_T03_PUBLIC_INFO_SIGNATURE) */

/** \brief Compile time Published information verfication value */
#define CANTRCV_1_T03_PUBLIC_INFO_SIGNATURE  [!"asc:getConfigSignature(node:difference(CommonPublishedInformation//*[not(child::*) and (node:configclass() = 'PublishedInformation') ], CommonPublishedInformation/Release))"!]U

[!ENDSELECT!]
/*==================[type definitions]=======================================*/

/*==================[external function declarations]=========================*/

/*==================[internal function declarations]=========================*/

/*==================[external constants]=====================================*/

/*==================[internal constants]=====================================*/

/*==================[external data]==========================================*/

/*==================[internal data]==========================================*/

/*==================[external function definitions]==========================*/

/*==================[internal function definitions]==========================*/

#endif /* #if (!defined CANTRCV_1_T03_CFG_H) */

/*==================[end of file]============================================*/

