/**EB_Automotive_C_Source_File */


/*
 * MISRA-C:2012 Deviations:
 *
 * MISRAC2012-1) Deviated Rule: 8.9 (Advisory)
 * An object should be defined at block scope if its identifier only
 * appears in a single function.
 *
 * Reason:
 * If DET is DISABLED, the variable CanTrcv_1_T03_InitState is used
 * only in the CanTrcv_1_T03_Init() function.
 */

/* !LINKSTO CanTrcv.ASR40.CanTrcv069,1 */

/*==================[inclusions]=============================================*/

#define CANTRCV_1_T03_NO_PBCFG_REQUIRED
#include <CanTrcv_1_T03.h>      /* Module public API and configuration */

#include <CanTrcv_1_T03_Trace.h>
#include <CanTrcv_1_T03_Lcfg.h> /* CanTrcv LinkTime configuration */

/* no dependencies to CanIf configuration */
#define CANIF_NO_CFG_REQUIRED
#define CANIF_NO_PBCFG_REQUIRED
#include <CanIf.h>              /* CanIf API */

/* CanTrcv.ASR40.CanTrcv067 deviate from CanTrcv.ASR40.CANIF409 */
#include <CanIf_Cbk.h>

#include <Spi.h>                /* macros to write into the SPI registers   */

#include <TSAutosar.h>          /* TS_STATIC_ASSERT */

#if (CANTRCV_1_T03_GENERAL_WAKE_UP_SUPPORT != CANTRCV_1_T03_WAKEUP_NOT_SUPPORTED)
#include <EcuM.h>               /* EcuM API */
#include <EcuM_Cbk.h>
#endif /* CANTRCV_1_T03_GENERAL_WAKE_UP_SUPPORT != CANTRCV_1_T03_WAKEUP_NOT_SUPPORTED */

#if (CANTRCV_1_T03_DEV_ERROR_DETECT == STD_ON)
#include <Det.h>                    /* AUTOSAR development error tracer */
#else /* CANTRCV_1_T03_DEV_ERROR_DETECT == STD_ON */
#include <TSAutosar.h>              /* TS_PARAM_UNUSED */
#endif /* CANTRCV_1_T03_DEV_ERROR_DETECT == STD_ON */

#if (CANTRCV_1_T03_ICU_DRIVER_SUPPORT == STD_ON)
#include <Icu.h>
#endif /* CANTRCV_1_T03_ICU_DRIVER_SUPPORT == STD_ON */


/*==================[version check]=========================================*/

/*------------------[AUTOSAR vendor identification check]-------------------*/

#if (!defined CANTRCV_1_T03_VENDOR_ID) /* configuration check */
#error CANTRCV_1_T03_VENDOR_ID must be defined
#endif

#if (CANTRCV_1_T03_VENDOR_ID != 1U) /* vendor check */
#error CANTRCV_1_T03_VENDOR_ID has wrong vendor id
#endif

/*------------------[AUTOSAR release version identification check]----------*/

#if (!defined CANTRCV_1_T03_AR_RELEASE_MAJOR_VERSION) /* configuration check */
#error CANTRCV_1_T03_AR_RELEASE_MAJOR_VERSION must be defined
#endif

/* major version check */
#if (CANTRCV_1_T03_AR_RELEASE_MAJOR_VERSION != 4U)
#error CANTRCV_1_T03_AR_RELEASE_MAJOR_VERSION wrong (!= 4U)
#endif

#if (!defined CANTRCV_1_T03_AR_RELEASE_MINOR_VERSION) /* configuration check */
#error CANTRCV_1_T03_AR_RELEASE_MINOR_VERSION must be defined
#endif

/* minor version check */
#if (CANTRCV_1_T03_AR_RELEASE_MINOR_VERSION != 0U )
#error CANTRCV_1_T03_AR_RELEASE_MINOR_VERSION wrong (!= 0U)
#endif

#if (!defined CANTRCV_1_T03_AR_RELEASE_REVISION_VERSION) /* configuration check */
#error CANTRCV_1_T03_AR_RELEASE_REVISION_VERSION must be defined
#endif

/* revision version check */
#if (CANTRCV_1_T03_AR_RELEASE_REVISION_VERSION != 3U )
#error CANTRCV_1_T03_AR_RELEASE_REVISION_VERSION wrong (!= 3U)
#endif

/*------------------[AUTOSAR module version identification check]-----------*/

#if (!defined CANTRCV_1_T03_SW_MAJOR_VERSION) /* configuration check */
#error CANTRCV_1_T03_SW_MAJOR_VERSION must be defined
#endif

/* major version check */
#if (CANTRCV_1_T03_SW_MAJOR_VERSION != 1U)
#error CANTRCV_1_T03_SW_MAJOR_VERSION wrong (!= 1U)
#endif

#if (!defined CANTRCV_1_T03_SW_MINOR_VERSION) /* configuration check */
#error CANTRCV_1_T03_SW_MINOR_VERSION must be defined
#endif

/* minor version check */
#if (CANTRCV_1_T03_SW_MINOR_VERSION < 3U)
#error CANTRCV_1_T03_SW_MINOR_VERSION wrong (< 3U)
#endif

#if (!defined CANTRCV_1_T03_SW_PATCH_VERSION) /* configuration check */
#error CANTRCV_1_T03_SW_PATCH_VERSION must be defined
#endif

/* patch version check */
#if (CANTRCV_1_T03_SW_PATCH_VERSION < 9U)
#error CANTRCV_1_T03_SW_PATCH_VERSION wrong (< 9U)
#endif

/*==================[macros]=================================================*/

#if (defined CANTRCV_OPMODE_UNKNOWN)      /* To prevent double declaration */
#error CANTRCV_OPMODE_UNKNOWN already defined!
#endif /* #if (defined CANTRCV_OPMODE_UNKNOWN) */

/** \brief This macro check if the operation mode of the transceiver is unknown */
#define CANTRCV_OPMODE_UNKNOWN(mode)                    \
    ( (   (CANTRCV_TRCVMODE_NORMAL != (mode))           \
       && (CANTRCV_TRCVMODE_STANDBY != (mode)))         \
       && (CANTRCV_TRCVMODE_SLEEP != (mode))            \
    )

#if (defined CANTRCV_WUPMODE_UNKNOWN)      /* To prevent double declaration */
#error CANTRCV_WUPMODE_UNKNOWN already defined!
#endif /* #if (defined CANTRCV_WUPMODE_UNKNOWN) */

/** \brief This macro check if the wakeup mode of the transceiver is unknown */
#define CANTRCV_WUPMODE_UNKNOWN(mode)                   \
    ( (   (CANTRCV_WUMODE_ENABLE != (mode))             \
       && (CANTRCV_WUMODE_DISABLE != (mode)))           \
       && (CANTRCV_WUMODE_CLEAR != (mode))              \
    )

#if (defined CANTRCV_DET_ERROR)      /* To prevent double declaration */
#error CANTRCV_DET_ERROR already defined!
#endif /* #if (defined CANTRCV_DET_ERROR) */

/** \brief Macro to report DET error
 **
 ** \param[in] ApiId Service ID of API
 ** \param[in] ErrId DET error ID
 */
#define CANTRCV_DET_ERROR(ApiId,ErrId)                          \
    (void) Det_ReportError((uint16)CANTRCV_1_T03_MODULE_ID,     \
                           (uint8)CANTRCV_1_T03_INSTANCE_ID,    \
                           (uint8)(ApiId),                      \
                           (uint8)(ErrId))

#if (defined CANTRCV_1_T03_NOT_ACTIVE)      /* To prevent double declaration */
#error CANTRCV_1_T03_NOT_ACTIVE already defined!
#endif /* #if (defined CANTRCV_1_T03_NOT_ACTIVE) */

/** \brief Defines the value of the InitState variable if CanTrcv is not initialized */
#define CANTRCV_1_T03_NOT_ACTIVE  0U

#if (defined CANTRCV_1_T03_ACTIVE)      /* To prevent double declaration */
#error CANTRCV_1_T03_ACTIVE already defined!
#endif /* #if (defined CANTRCV_1_T03_ACTIVE) */

/** \brief Defines the value of the InitState variable if CanTrcv is initialized */
#define CANTRCV_1_T03_ACTIVE      1U

#if (defined CANTRCV_1_T03_INVALID_ICU_CHANNEL)      /* To prevent double declaration */
#error CANTRCV_1_T03_INVALID_ICU_CHANNEL already defined!
#endif /* #if (defined CANTRCV_1_T03_INVALID_ICU_CHANNEL) */

/** \brief Invalid reference to ICU channel */
#define CANTRCV_1_T03_INVALID_ICU_CHANNEL              0xFFFFU

#if (defined CANTRCV_1_T03_INVALID_WAKEUP_SOURCE)      /* To prevent double declaration */
#error CANTRCV_1_T03_INVALID_WAKEUP_SOURCE already defined!
#endif /* #if (defined CANTRCV_1_T03_INVALID_WAKEUP_SOURCE) */

/** \brief wakeup source ID */
#define CANTRCV_1_T03_INVALID_WAKEUP_SOURCE            0xFFU

/*==================[macro guards start]=================================================*/

#if (defined STD_6_LSB_MASK)      /* To prevent double declaration */
#error STD_6_LSB_MASK already defined!
#endif /* #if (defined STD_6_LSB_MASK) */

#if (defined STD_5_MSB_MASK)      /* To prevent double declaration */
#error STD_5_MSB_MASK already defined!
#endif /* #if (defined STD_5_MSB_MASK) */

#if (defined EXT_BYTE_0_MASK)      /* To prevent double declaration */
#error EXT_BYTE_0_MASK already defined!
#endif /* #if (defined EXT_BYTE_0_MASK) */

#if (defined MC_CMD_SLEEP_MODE)      /* To prevent double declaration */
#error MC_CMD_SLEEP_MODE already defined!
#endif /* #if (defined MC_CMD_SLEEP_MODE) */

#if (defined MC_CMD_STANDBY_MODE)      /* To prevent double declaration */
#error MC_CMD_STANDBY_MODE already defined!
#endif /* #if (defined MC_CMD_STANDBY_MODE) */

#if (defined MC_CMD_NORMAL_MODE)      /* To prevent double declaration */
#error MC_CMD_NORMAL_MODE already defined!
#endif /* #if (defined MC_CMD_NORMAL_MODE) */

#if (defined MC_CMD_MASK_MODE)      /* To prevent double declaration */
#error MC_CMD_MASK_MODE already defined!
#endif /* #if (defined MC_CMD_MASK_MODE) */

#if (defined MODE_CONTROL_REGISTER_ADDR)      /* To prevent double declaration */
#error MODE_CONTROL_REGISTER_ADDR already defined!
#endif /* #if (defined MODE_CONTROL_REGISTER_ADDR) */

#if (defined SYST_EVENT_ENABLE_REGISTER_ADDR)      /* To prevent double declaration */
#error SYST_EVENT_ENABLE_REGISTER_ADDR already defined!
#endif /* #if (defined SYST_EVENT_ENABLE_REGISTER_ADDR) */

#if (defined LOCK_CONTROL_REGISTER_ADDR)      /* To prevent double declaration */
#error LOCK_CONTROL_REGISTER_ADDR already defined!
#endif /* #if (defined LOCK_CONTROL_REGISTER_ADDR) */

#if (defined CAN_CTRL_REGISTER_ADDR)      /* To prevent double declaration */
#error CAN_CTRL_REGISTER_ADDR already defined!
#endif /* #if (defined CAN_CTRL_REGISTER_ADDR) */

#if (defined TRANSCEIVER_STATUS_REGISTER_ADDR)      /* To prevent double declaration */
#error TRANSCEIVER_STATUS_REGISTER_ADDR already defined!
#endif /* #if (defined TRANSCEIVER_STATUS_REGISTER_ADDR) */

#if (defined TRANSCEIVER_EVENT_EN_REGISTER_ADDR)      /* To prevent double declaration */
#error TRANSCEIVER_EVENT_EN_REGISTER_ADDR already defined!
#endif /* #if (defined TRANSCEIVER_EVENT_EN_REGISTER_ADDR) */

#if (defined DATA_RATE_REGISTER_ADDR)      /* To prevent double declaration */
#error DATA_RATE_REGISTER_ADDR already defined!
#endif /* #if (defined DATA_RATE_REGISTER_ADDR) */

#if (defined ID_REGISTER_0_ADDR)      /* To prevent double declaration */
#error ID_REGISTER_0_ADDR already defined!
#endif /* #if (defined ID_REGISTER_0_ADDR) */

#if (defined ID_REGISTER_1_ADDR)      /* To prevent double declaration */
#error ID_REGISTER_1_ADDR already defined!
#endif /* #if (defined ID_REGISTER_1_ADDR) */

#if (defined ID_REGISTER_2_ADDR)      /* To prevent double declaration */
#error ID_REGISTER_2_ADDR already defined!
#endif /* #if (defined ID_REGISTER_2_ADDR) */

#if (defined ID_REGISTER_3_ADDR)      /* To prevent double declaration */
#error ID_REGISTER_3_ADDR already defined!
#endif /* #if (defined ID_REGISTER_3_ADDR) */

#if (defined MASK_REGISTER_0_ADDR)      /* To prevent double declaration */
#error MASK_REGISTER_0_ADDR already defined!
#endif /* #if (defined MASK_REGISTER_0_ADDR) */

#if (defined MASK_REGISTER_1_ADDR)      /* To prevent double declaration */
#error MASK_REGISTER_1_ADDR already defined!
#endif /* #if (defined MASK_REGISTER_1_ADDR) */

#if (defined MASK_REGISTER_2_ADDR)      /* To prevent double declaration */
#error MASK_REGISTER_2_ADDR already defined!
#endif /* #if (defined MASK_REGISTER_2_ADDR) */

#if (defined MASK_REGISTER_3_ADDR)      /* To prevent double declaration */
#error MASK_REGISTER_3_ADDR already defined!
#endif /* #if (defined MASK_REGISTER_3_ADDR) */

#if (defined FRAME_CTRL_REGISTER_ADDR)      /* To prevent double declaration */
#error FRAME_CTRL_REGISTER_ADDR already defined!
#endif /* #if (defined FRAME_CTRL_REGISTER_ADDR) */

#if (defined WAKEPIN_ENABLE_REGISTER_ADDR)      /* To prevent double declaration */
#error WAKEPIN_ENABLE_REGISTER_ADDR already defined!
#endif /* #if (defined WAKEPIN_ENABLE_REGISTER_ADDR) */

#if (defined GLOBAL_EVENT_STATUS_REGISTER_ADDR)      /* To prevent double declaration */
#error GLOBAL_EVENT_STATUS_REGISTER_ADDR already defined!
#endif /* #if (defined GLOBAL_EVENT_STATUS_REGISTER_ADDR) */

#if (defined SYSTEM_EVENT_STATUS_REGISTER_ADDR)      /* To prevent double declaration */
#error SYSTEM_EVENT_STATUS_REGISTER_ADDR already defined!
#endif /* #if (defined SYSTEM_EVENT_STATUS_REGISTER_ADDR) */

#if (defined TRCV_EVENT_STATUS_REGISTER_ADDR)      /* To prevent double declaration */
#error TRCV_EVENT_STATUS_REGISTER_ADDR already defined!
#endif /* #if (defined TRCV_EVENT_STATUS_REGISTER_ADDR) */

#if (defined WAKE_EVENT_STATUS_REGISTER_ADDR)      /* To prevent double declaration */
#error WAKE_EVENT_STATUS_REGISTER_ADDR already defined!
#endif /* #if (defined WAKE_EVENT_STATUS_REGISTER_ADDR) */

#if (defined DATA_MASK_REGISTER_0_ADDR_WITH_NO_SHIFT)      /* To prevent double declaration */
#error DATA_MASK_REGISTER_0_ADDR_WITH_NO_SHIFT already defined!
#endif /* #if (defined DATA_MASK_REGISTER_0_ADDR_WITH_NO_SHIFT) */

#if (defined DATA_MASK_REGISTER_0_ADDR)      /* To prevent double declaration */
#error DATA_MASK_REGISTER_0_ADDR already defined!
#endif /* #if (defined DATA_MASK_REGISTER_0_ADDR) */

#if (defined DATA_MASK_REGISTER_1_ADDR)      /* To prevent double declaration */
#error DATA_MASK_REGISTER_1_ADDR already defined!
#endif /* #if (defined DATA_MASK_REGISTER_1_ADDR) */

#if (defined DATA_MASK_REGISTER_2_ADDR)      /* To prevent double declaration */
#error DATA_MASK_REGISTER_2_ADDR already defined!
#endif /* #if (defined DATA_MASK_REGISTER_2_ADDR) */

#if (defined DATA_MASK_REGISTER_3_ADDR)      /* To prevent double declaration */
#error DATA_MASK_REGISTER_3_ADDR already defined!
#endif /* #if (defined DATA_MASK_REGISTER_3_ADDR) */

#if (defined DATA_MASK_REGISTER_4_ADDR)      /* To prevent double declaration */
#error DATA_MASK_REGISTER_4_ADDR already defined!
#endif /* #if (defined DATA_MASK_REGISTER_4_ADDR) */

#if (defined DATA_MASK_REGISTER_5_ADDR)      /* To prevent double declaration */
#error DATA_MASK_REGISTER_5_ADDR already defined!
#endif /* #if (defined DATA_MASK_REGISTER_5_ADDR) */

#if (defined DATA_MASK_REGISTER_6_ADDR)      /* To prevent double declaration */
#error DATA_MASK_REGISTER_6_ADDR already defined!
#endif /* #if (defined DATA_MASK_REGISTER_6_ADDR) */

#if (defined DATA_MASK_REGISTER_7_ADDR)      /* To prevent double declaration */
#error DATA_MASK_REGISTER_7_ADDR already defined!
#endif /* #if (defined DATA_MASK_REGISTER_7_ADDR) */

#if (defined LOCK_CONTROL_ALL)      /* To prevent double declaration */
#error LOCK_CONTROL_ALL already defined!
#endif /* #if (defined LOCK_CONTROL_ALL) */

#if (defined LOCK_CONTROL_2)      /* To prevent double declaration */
#error LOCK_CONTROL_2 already defined!
#endif /* #if (defined LOCK_CONTROL_2) */

#if (defined UNLOCK_CONTROL_ALL)      /* To prevent double declaration */
#error UNLOCK_CONTROL_ALL already defined!
#endif /* #if (defined UNLOCK_CONTROL_ALL) */

#if (defined CANTRCV_1_T03_TRCV_STATUS_CBSS)      /* To prevent double declaration */
#error CANTRCV_1_T03_TRCV_STATUS_CBSS already defined!
#endif /* #if (defined CANTRCV_1_T03_TRCV_STATUS_CBSS) */

#if (defined CANTRCV_1_T03_GLOBAL_EVENT_STATUS_MASK_NO_EVENT)      /* To prevent double declaration */
#error CANTRCV_1_T03_GLOBAL_EVENT_STATUS_MASK_NO_EVENT already defined!
#endif /* #if (defined CANTRCV_1_T03_GLOBAL_EVENT_STATUS_MASK_NO_EVENT) */

#if (defined CANTRCV_1_T03_GLOBAL_EVENT_STATUS_SYSE)      /* To prevent double declaration */
#error CANTRCV_1_T03_GLOBAL_EVENT_STATUS_SYSE already defined!
#endif /* #if (defined CANTRCV_1_T03_GLOBAL_EVENT_STATUS_SYSE) */

#if (defined CANTRCV_1_T03_GLOBAL_EVENT_STATUS_TRXE)      /* To prevent double declaration */
#error CANTRCV_1_T03_GLOBAL_EVENT_STATUS_TRXE already defined!
#endif /* #if (defined CANTRCV_1_T03_GLOBAL_EVENT_STATUS_TRXE) */

#if (defined CANTRCV_1_T03_GLOBAL_EVENT_STATUS_WPE)      /* To prevent double declaration */
#error CANTRCV_1_T03_GLOBAL_EVENT_STATUS_WPE already defined!
#endif /* #if (defined CANTRCV_1_T03_GLOBAL_EVENT_STATUS_WPE) */

#if (defined CANTRCV_1_T03_GLOBAL_EVENT_STATUS_MASK)      /* To prevent double declaration */
#error CANTRCV_1_T03_GLOBAL_EVENT_STATUS_MASK already defined!
#endif /* #if (defined CANTRCV_1_T03_GLOBAL_EVENT_STATUS_MASK) */

#if (defined CANTRCV_1_T03_SYSTEM_EVENT_STATUS_SPIF)      /* To prevent double declaration */
#error CANTRCV_1_T03_SYSTEM_EVENT_STATUS_SPIF already defined!
#endif /* #if (defined CANTRCV_1_T03_SYSTEM_EVENT_STATUS_SPIF) */

#if (defined CANTRCV_1_T03_SYSTEM_EVENT_STATUS_OTW)      /* To prevent double declaration */
#error CANTRCV_1_T03_SYSTEM_EVENT_STATUS_OTW already defined!
#endif /* #if (defined CANTRCV_1_T03_SYSTEM_EVENT_STATUS_OTW) */

#if (defined CANTRCV_1_T03_SYSTEM_EVENT_STATUS_PO)      /* To prevent double declaration */
#error CANTRCV_1_T03_SYSTEM_EVENT_STATUS_PO already defined!
#endif /* #if (defined CANTRCV_1_T03_SYSTEM_EVENT_STATUS_PO) */

#if (defined CANTRCV_1_T03_SYSTEM_EVENT_STATUS_MASK)      /* To prevent double declaration */
#error CANTRCV_1_T03_SYSTEM_EVENT_STATUS_MASK already defined!
#endif /* #if (defined CANTRCV_1_T03_SYSTEM_EVENT_STATUS_MASK) */

#if (defined CANTRCV_1_T03_TRANSCEIVER_EVENT_STATUS_CW)      /* To prevent double declaration */
#error CANTRCV_1_T03_TRANSCEIVER_EVENT_STATUS_CW already defined!
#endif /* #if (defined CANTRCV_1_T03_TRANSCEIVER_EVENT_STATUS_CW) */

#if (defined CANTRCV_1_T03_TRANSCEIVER_EVENT_STATUS_CF)      /* To prevent double declaration */
#error CANTRCV_1_T03_TRANSCEIVER_EVENT_STATUS_CF already defined!
#endif /* #if (defined CANTRCV_1_T03_TRANSCEIVER_EVENT_STATUS_CF) */

#if (defined CANTRCV_1_T03_TRANSCEIVER_EVENT_STATUS_CBS)      /* To prevent double declaration */
#error CANTRCV_1_T03_TRANSCEIVER_EVENT_STATUS_CBS already defined!
#endif /* #if (defined CANTRCV_1_T03_TRANSCEIVER_EVENT_STATUS_CBS) */

#if (defined CANTRCV_1_T03_TRANSCEIVER_EVENT_STATUS_PNFDE)      /* To prevent double declaration */
#error CANTRCV_1_T03_TRANSCEIVER_EVENT_STATUS_PNFDE already defined!
#endif /* #if (defined CANTRCV_1_T03_TRANSCEIVER_EVENT_STATUS_PNFDE) */

#if (defined CANTRCV_1_T03_TRANSCEIVER_EVENT_STATUS_MASK)      /* To prevent double declaration */
#error CANTRCV_1_T03_TRANSCEIVER_EVENT_STATUS_MASK already defined!
#endif /* #if (defined CANTRCV_1_T03_TRANSCEIVER_EVENT_STATUS_MASK) */

#if (defined CANTRCV_1_T03_WAKE_PIN_EVENT_STATUS_WPF)      /* To prevent double declaration */
#error CANTRCV_1_T03_WAKE_PIN_EVENT_STATUS_WPF already defined!
#endif /* #if (defined CANTRCV_1_T03_WAKE_PIN_EVENT_STATUS_WPF) */

#if (defined CANTRCV_1_T03_WAKE_PIN_EVENT_STATUS_WPR)      /* To prevent double declaration */
#error CANTRCV_1_T03_WAKE_PIN_EVENT_STATUS_WPR already defined!
#endif /* #if (defined CANTRCV_1_T03_WAKE_PIN_EVENT_STATUS_WPR) */

#if (defined CANTRCV_1_T03_WAKE_PIN_EVENT_STATUS_MASK)      /* To prevent double declaration */
#error CANTRCV_1_T03_WAKE_PIN_EVENT_STATUS_MASK already defined!
#endif /* #if (defined CANTRCV_1_T03_WAKE_PIN_EVENT_STATUS_MASK) */

#if (defined CANTRCV_1_T03_SYSTEM_ENABLE_SPIFE)      /* To prevent double declaration */
#error CANTRCV_1_T03_SYSTEM_ENABLE_SPIFE already defined!
#endif /* #if (defined CANTRCV_1_T03_SYSTEM_ENABLE_SPIFE) */

#if (defined CANTRCV_1_T03_SYSTEM_ENABLE_OTWE)      /* To prevent double declaration */
#error CANTRCV_1_T03_SYSTEM_ENABLE_OTWE already defined!
#endif /* #if (defined CANTRCV_1_T03_SYSTEM_ENABLE_OTWE) */

#if (defined CANTRCV_1_T03_TRANSCEIVER_ENABLE_CWE)      /* To prevent double declaration */
#error CANTRCV_1_T03_TRANSCEIVER_ENABLE_CWE already defined!
#endif /* #if (defined CANTRCV_1_T03_TRANSCEIVER_ENABLE_CWE) */

#if (defined CANTRCV_1_T03_TRANSCEIVER_ENABLE_CFE)      /* To prevent double declaration */
#error CANTRCV_1_T03_TRANSCEIVER_ENABLE_CFE already defined!
#endif /* #if (defined CANTRCV_1_T03_TRANSCEIVER_ENABLE_CFE) */

#if (defined CANTRCV_1_T03_TRANSCEIVER_ENABLE_CBSE)      /* To prevent double declaration */
#error CANTRCV_1_T03_TRANSCEIVER_ENABLE_CBSE already defined!
#endif /* #if (defined CANTRCV_1_T03_TRANSCEIVER_ENABLE_CBSE) */

#if (defined CANTRCV_1_T03_WAKE_ENABLE_WPFE)      /* To prevent double declaration */
#error CANTRCV_1_T03_WAKE_ENABLE_WPFE already defined!
#endif /* #if (defined CANTRCV_1_T03_WAKE_ENABLE_WPFE) */

#if (defined CANTRCV_1_T03_WAKE_ENABLE_WPRE)      /* To prevent double declaration */
#error CANTRCV_1_T03_WAKE_ENABLE_WPRE already defined!
#endif /* #if (defined CANTRCV_1_T03_WAKE_ENABLE_WPRE) */

#if (defined CANTRCV_1_T03_CAN_CTRL_CMC_ACTIVE_0)      /* To prevent double declaration */
#error CANTRCV_1_T03_CAN_CTRL_CMC_ACTIVE_0 already defined!
#endif /* #if (defined CANTRCV_1_T03_CAN_CTRL_CMC_ACTIVE_0) */

#if (defined CANTRCV_1_T03_CAN_CTRL_CMC)      /* To prevent double declaration */
#error CANTRCV_1_T03_CAN_CTRL_CMC already defined!
#endif /* #if (defined CANTRCV_1_T03_CAN_CTRL_CMC) */

#if (defined CANTRCV_1_T03_CAN_CTRL_CPNC)      /* To prevent double declaration */
#error CANTRCV_1_T03_CAN_CTRL_CPNC already defined!
#endif /* #if (defined CANTRCV_1_T03_CAN_CTRL_CPNC) */

#if (defined CANTRCV_1_T03_CAN_CTRL_PNCOK)      /* To prevent double declaration */
#error CANTRCV_1_T03_CAN_CTRL_PNCOK already defined!
#endif /* #if (defined CANTRCV_1_T03_CAN_CTRL_PNCOK) */

#if (defined CANTRCV_1_T03_CAN_CTRL_CFDC)      /* To prevent double declaration */
#error CANTRCV_1_T03_CAN_CTRL_CFDC already defined!
#endif /* #if (defined CANTRCV_1_T03_CAN_CTRL_CFDC) */

#if (defined CANTRCV_CONFIGURATION_NOK)      /* To prevent double declaration */
#error CANTRCV_CONFIGURATION_NOK already defined!
#endif /* #if (defined CANTRCV_CONFIGURATION_NOK) */

#if (defined CANTRCV_CONFIGURATION_OK)      /* To prevent double declaration */
#error CANTRCV_CONFIGURATION_OK already defined!
#endif /* #if (defined CANTRCV_CONFIGURATION_OK) */

#if (defined CANTRCV_SPI_WRITE)      /* To prevent double declaration */
#error CANTRCV_SPI_WRITE already defined!
#endif /* #if (defined CANTRCV_SPI_WRITE) */

#if (defined CANTRCV_SPI_READ)      /* To prevent double declaration */
#error CANTRCV_SPI_READ already defined!
#endif /* #if (defined CANTRCV_SPI_READ) */
/*==================[macro guards stop]==================================================*/
#define STD_6_LSB_MASK       0x0000003FU
#define STD_5_MSB_MASK       0x000007C0U

#define EXT_BYTE_0_MASK      0x000000ffU

#define MC_CMD_SLEEP_MODE    0x01U
#define MC_CMD_STANDBY_MODE  0x04U
#define MC_CMD_NORMAL_MODE   0x07U
#define MC_CMD_MASK_MODE     0x07U

/* Addresses of the transceiver registers */
/* Value adapt for SPI requests */
#define MODE_CONTROL_REGISTER_ADDR          ((uint8)(0x01U << 1))
#define SYST_EVENT_ENABLE_REGISTER_ADDR     ((uint8)(0x04U << 1))
#define LOCK_CONTROL_REGISTER_ADDR          ((uint8)(0x0AU << 1))
#define CAN_CTRL_REGISTER_ADDR              ((uint8)(0x20U << 1))
#define TRANSCEIVER_STATUS_REGISTER_ADDR    ((uint8)(0x22U << 1))
#define TRANSCEIVER_EVENT_EN_REGISTER_ADDR  ((uint8)(0x23U << 1))
#define DATA_RATE_REGISTER_ADDR             ((uint8)(0x26U << 1))
#define ID_REGISTER_0_ADDR                  ((uint8)(0x27U << 1))
#define ID_REGISTER_1_ADDR                  ((uint8)(0x28U << 1))
#define ID_REGISTER_2_ADDR                  ((uint8)(0x29U << 1))
#define ID_REGISTER_3_ADDR                  ((uint8)(0x2AU << 1))
#define MASK_REGISTER_0_ADDR                ((uint8)(0x2BU << 1))
#define MASK_REGISTER_1_ADDR                ((uint8)(0x2CU << 1))
#define MASK_REGISTER_2_ADDR                ((uint8)(0x2DU << 1))
#define MASK_REGISTER_3_ADDR                ((uint8)(0x2EU << 1))
#define FRAME_CTRL_REGISTER_ADDR            ((uint8)(0x2FU << 1))
#define WAKEPIN_ENABLE_REGISTER_ADDR        ((uint8)(0x4CU << 1))
#define GLOBAL_EVENT_STATUS_REGISTER_ADDR   ((uint8)(0x60U << 1))
#define SYSTEM_EVENT_STATUS_REGISTER_ADDR   ((uint8)(0x61U << 1))
#define TRCV_EVENT_STATUS_REGISTER_ADDR     ((uint8)(0x63U << 1))
#define WAKE_EVENT_STATUS_REGISTER_ADDR     ((uint8)(0x64U << 1))
#define DATA_MASK_REGISTER_0_ADDR_WITH_NO_SHIFT      0x68U
#define DATA_MASK_REGISTER_0_ADDR           ((uint8)(0x68U << 1))
#define DATA_MASK_REGISTER_1_ADDR           ((uint8)(0x69U << 1))
#define DATA_MASK_REGISTER_2_ADDR           ((uint8)(0x6AU << 1))
#define DATA_MASK_REGISTER_3_ADDR           ((uint8)(0x6BU << 1))
#define DATA_MASK_REGISTER_4_ADDR           ((uint8)(0x6CU << 1))
#define DATA_MASK_REGISTER_5_ADDR           ((uint8)(0x6DU << 1))
#define DATA_MASK_REGISTER_6_ADDR           ((uint8)(0x6EU << 1))
#define DATA_MASK_REGISTER_7_ADDR           ((uint8)(0x6FU << 1))


/* lock control management */
#define LOCK_CONTROL_ALL                    0x7FU
#define LOCK_CONTROL_2                      0x04U
#define UNLOCK_CONTROL_ALL                  0x00U

/* Transceiver status register */
#define CANTRCV_1_T03_TRCV_STATUS_CBSS      0x08U

/* Global event status register symbol */
#define CANTRCV_1_T03_GLOBAL_EVENT_STATUS_MASK_NO_EVENT  0x00U
#define CANTRCV_1_T03_GLOBAL_EVENT_STATUS_SYSE           0x01U
#define CANTRCV_1_T03_GLOBAL_EVENT_STATUS_TRXE           0x04U
#define CANTRCV_1_T03_GLOBAL_EVENT_STATUS_WPE            0x08U
#define CANTRCV_1_T03_GLOBAL_EVENT_STATUS_MASK          (CANTRCV_1_T03_GLOBAL_EVENT_STATUS_SYSE |  \
                                                         CANTRCV_1_T03_GLOBAL_EVENT_STATUS_TRXE |  \
                                                         CANTRCV_1_T03_GLOBAL_EVENT_STATUS_WPE)

/* System event status register symbol */
#define CANTRCV_1_T03_SYSTEM_EVENT_STATUS_SPIF           0x02U
#define CANTRCV_1_T03_SYSTEM_EVENT_STATUS_OTW            0x04U
#define CANTRCV_1_T03_SYSTEM_EVENT_STATUS_PO             0x10U
#define CANTRCV_1_T03_SYSTEM_EVENT_STATUS_MASK          (CANTRCV_1_T03_SYSTEM_EVENT_STATUS_SPIF |  \
                                                         CANTRCV_1_T03_SYSTEM_EVENT_STATUS_OTW  |  \
                                                         CANTRCV_1_T03_SYSTEM_EVENT_STATUS_PO)

/* Transceiver event status register */
#define CANTRCV_1_T03_TRANSCEIVER_EVENT_STATUS_CW        0x01U
#define CANTRCV_1_T03_TRANSCEIVER_EVENT_STATUS_CF        0x02U
#define CANTRCV_1_T03_TRANSCEIVER_EVENT_STATUS_CBS       0x10U
#define CANTRCV_1_T03_TRANSCEIVER_EVENT_STATUS_PNFDE     0x20U
#define CANTRCV_1_T03_TRANSCEIVER_EVENT_STATUS_MASK     (CANTRCV_1_T03_TRANSCEIVER_EVENT_STATUS_CW  |  \
                                                         CANTRCV_1_T03_TRANSCEIVER_EVENT_STATUS_CF  |  \
                                                         CANTRCV_1_T03_TRANSCEIVER_EVENT_STATUS_CBS |  \
                                                         CANTRCV_1_T03_TRANSCEIVER_EVENT_STATUS_PNFDE)

/* Wake pin event status register */
#define CANTRCV_1_T03_WAKE_PIN_EVENT_STATUS_WPF          0x01U
#define CANTRCV_1_T03_WAKE_PIN_EVENT_STATUS_WPR          0x02U
#define CANTRCV_1_T03_WAKE_PIN_EVENT_STATUS_MASK        (CANTRCV_1_T03_WAKE_PIN_EVENT_STATUS_WPF |  \
                                                                  CANTRCV_1_T03_WAKE_PIN_EVENT_STATUS_WPR)

/* System event capture enable register */
#define CANTRCV_1_T03_SYSTEM_ENABLE_SPIFE           0x02U
#define CANTRCV_1_T03_SYSTEM_ENABLE_OTWE            0x04U

/* Transceiver event capture enable register */
#define CANTRCV_1_T03_TRANSCEIVER_ENABLE_CWE        0x01U
#define CANTRCV_1_T03_TRANSCEIVER_ENABLE_CFE        0x02U
#define CANTRCV_1_T03_TRANSCEIVER_ENABLE_CBSE       0x10U

/* Wake pin event capture enable register */
#define CANTRCV_1_T03_WAKE_ENABLE_WPFE              0x01U
#define CANTRCV_1_T03_WAKE_ENABLE_WPRE              0x02U

/* CAN control register */
#define CANTRCV_1_T03_CAN_CTRL_CMC_ACTIVE_0         0x01U
#define CANTRCV_1_T03_CAN_CTRL_CMC                  0x03U
#define CANTRCV_1_T03_CAN_CTRL_CPNC                 0x10U
#define CANTRCV_1_T03_CAN_CTRL_PNCOK                0x20U
#define CANTRCV_1_T03_CAN_CTRL_CFDC                 0x40U

/* Check if a re-initialization is necessary */
#define CANTRCV_CONFIGURATION_NOK       0U
#define CANTRCV_CONFIGURATION_OK        1U

/* Set SPI sequence bit mode as read or write access to transceiver */
/** \brief Set 0 in SPI sequence for writing a register of the transceiver */
#define       CANTRCV_SPI_WRITE                               0x0U
/** \brief Set 1 in SPI sequence for reading a register of the transceiver */
#define       CANTRCV_SPI_READ                                0x1U

/*==================[type definitions]=======================================*/

/*==================[external function declarations]=========================*/

/*==================[internal function declarations]=========================*/

#define CANTRCV_1_T03_START_SEC_CODE
#include <CanTrcv_1_T03_MemMap.h>

/** \brief Internal transceiver Init funcion
 **
 ** This function initializes all necessry CanTrcv
 ** register dependent on the configuration
 **
 ** \param[in] Transceiver Index of the transceiver
 ** \param[in] InitialMode operating state the CanTrcv shall reach
 ** \param[in] ServiceId Service ID of caller
 **
 ** \return Result of operation
 ** \retval E_OK      initialization done
 ** \retval E_NOT_OK  initialization failed
  */
STATIC FUNC( Std_ReturnType, CANTRCV_1_T03_CODE) CanTrcv_1_T03_InternalTrcvInit
(
    uint8 Transceiver,
    uint8 InitialMode,
    uint8 ServiceID
);

#if ( CANTRCV_1_T03_PN_SUPPORT == STD_ON )
/** \brief Internal set Pn Init funcion
 **
 ** This function sets the partial network related
 ** register during initialization
 **
 ** \param[in] Transceiver Index of the transceiver
 ** \param[in] ServiceId Service ID of caller
 **
 ** \return Result of operation
 ** \retval E_OK      initialization done
 ** \retval E_NOT_OK  initialization failed
  */
STATIC FUNC( Std_ReturnType, CANTRCV_1_T03_CODE) CanTrcv_1_T03_InternalPnInit
(
    uint8 Transceiver,
    uint8 ServiceID
);
#endif /* CANTRCV_1_T03_PN_SUPPORT == STD_ON */

#if ( CANTRCV_1_T03_PN_SUPPORT == STD_ON )
/** \brief Internal Init funcion for standard Ids
 **
 ** This function sets the partial network related
 ** standard CAN Id register during initialization
 **
 ** \param[in] Transceiver Index of the transceiver
 ** \param[in] ServiceId Service ID of caller
 **
 ** \return Result of operation
 ** \retval E_OK      initialization done
 ** \retval E_NOT_OK  initialization failed
  */
STATIC FUNC( Std_ReturnType, CANTRCV_1_T03_CODE) CanTrcv_1_T03_StdIdRegInit
(
    uint8 Transceiver,
    uint8 ServiceID
);
#endif /* CANTRCV_1_T03_PN_SUPPORT == STD_ON */

#if ( CANTRCV_1_T03_PN_SUPPORT == STD_ON )
/** \brief Internal Init funcion for extended Ids
 **
 ** This function sets the partial network related
 ** extended CAN Id register during initialization
 **
 ** \param[in] Transceiver Index of the transceiver
 ** \param[in] ServiceId Service ID of caller
 **
 ** \return Result of operation
 ** \retval E_OK      initialization done
 ** \retval E_NOT_OK  initialization failed
  */
STATIC FUNC( Std_ReturnType, CANTRCV_1_T03_CODE) CanTrcv_1_T03_ExtIdRegInit
(
    uint8 Transceiver,
    uint8 ServiceID
);
#endif /* CANTRCV_1_T03_PN_SUPPORT == STD_ON */

#if ( CANTRCV_1_T03_PN_SUPPORT == STD_ON )
/** \brief Internal Init funcion for extended Ids
 **
 ** This function sets the partial network related
 ** extended CAN Id register during initialization
 **
 ** \param[in] Transceiver Index of the transceiver
 ** \param[in] ServiceId Service ID of caller
 **
 ** \return Result of operation
 ** \retval E_OK      initialization done
 ** \retval E_NOT_OK  initialization failed
  */
STATIC FUNC( Std_ReturnType, CANTRCV_1_T03_CODE) CanTrcv_1_T03_ExtIdMaskRegInit
(
    uint8 Transceiver,
    uint8 ServiceID
);
#endif /* CANTRCV_1_T03_PN_SUPPORT == STD_ON */

/** \brief Internal Init funcion for event capture register
 **
 ** This function sets the event capture register
 ** during initialization
 **
 ** \param[in] Transceiver Index of the transceiver
 ** \param[in] ServiceId Service ID of caller
 **
 ** \return Result of operation
 ** \retval E_OK      initialization done
 ** \retval E_NOT_OK  initialization failed
  */
#if (CANTRCV_1_T03_GENERAL_WAKE_UP_SUPPORT != CANTRCV_1_T03_WAKEUP_NOT_SUPPORTED)
STATIC FUNC( Std_ReturnType, CANTRCV_1_T03_CODE) CanTrcv_1_T03_EventRegInit
(
    uint8 Transceiver,
    uint8 ServiceID
);
#endif /* CANTRCV_1_T03_GENERAL_WAKE_UP_SUPPORT != CANTRCV_1_T03_WAKEUP_NOT_SUPPORTED */

#if (CANTRCV_1_T03_OPERATION_MODE_API == STD_ON)
/** \brief Internal set operating mode function
 **
 ** This function sets the mode of the transceiver
 **
 ** \param[in] Transceiver Index of the transceiver
 ** \param[in] OpMode Desired operating mode
 **
 ** \return Result of operation
 ** \retval E_OK      state transition performed
 ** \retval E_NOT_OK  No state transition performed
  */
STATIC FUNC( Std_ReturnType, CANTRCV_1_T03_CODE ) CanTrcv_1_T03_InternalSetOpMode
(
    uint8 Transceiver,
    uint8 OpMode,
    uint8 ServiceID
);
#endif /* CANTRCV_1_T03_OPERATION_MODE_API == STD_ON */

#if (CANTRCV_1_T03_ICU_DRIVER_SUPPORT == STD_ON)
/** \brief Internal ICU driver notifcation function
 **
 ** This function notifies the ICU driver.
 **
 ** \param[in] Transceiver Index of the transceiver
 ** \param[in] NewMode new operating mode
 */
STATIC FUNC( void, CANTRCV_1_T03_CODE ) CanTrcv_1_T03_IcuDriverNotification
(
    uint8 Transceiver,
    uint8 NewMode
);
#endif /* CANTRCV_1_T03_ICU_DRIVER_SUPPORT == STD_ON */

/** \brief Synchrnous SPI transmit
 **
 ** This function triggers a synchrnous SPI transmit.
 **
 ** \param[in] Sequence Id of the SPI sequence
 **
 ** \return Result of operation
 ** \retval E_OK      transmission successful
 ** \retval E_NOT_OK  transmission failed
 */
STATIC FUNC( Std_ReturnType, CANTRCV_1_T03_CODE ) CanTrcv_1_T03_SpiCommSyncTransmit
(
    Spi_SequenceType Sequence,
    uint8 SpiAccessSync
);

/** \brief Reads SPI buffer
 **
 ** This function reads the value of a SPI buffer.
 ** The buffer is updated after a read transmission.
 **
 ** \param[in] Channel Id of the SPI buffer
 ** \param[in] DataBufferPtr Points to the memory to store the data
 **
 ** \return Result of operation
 ** \retval E_OK      read operation successful
 ** \retval E_NOT_OK  read operation failed
 */
STATIC FUNC( Std_ReturnType, CANTRCV_1_T03_CODE ) CanTrcv_1_T03_SpiCommReadIB
(
    Spi_ChannelType Channel,
    P2VAR(uint16, AUTOMATIC, AUTOMATIC) DataBufferPtr
);

/** \brief Writes SPI buffer
 **
 ** This function writes the value to a SPI buffer.
 ** The content of the buffer is used during a transmission.
 **
 ** \param[in] Channel Id of the SPI buffer
 ** \param[in] DataBufferPtr Points to data which shall be written to the buffer
 **
 ** \return Result of operation
 ** \retval E_OK      write operation successful
 ** \retval E_NOT_OK  write operation failed
 */
STATIC FUNC( Std_ReturnType, CANTRCV_1_T03_CODE ) CanTrcv_1_T03_SpiCommWriteIB
(
    Spi_ChannelType Channel,
    P2CONST(uint16, AUTOMATIC, AUTOMATIC) DataBufferPtr
);

/** \brief Performing complete SPI access
 **
 ** This function performs the following sequence:
 ** 1a. write the SPI address ubRegAccess to the SPI buffer.
 ** 1b. (in case of a write operation): writes the data (ubData) to the buffer.
 ** 2.  triggers a synchronous SPI transmit
 ** 3.  (in case of a write operation): returns the data (ubData)
 **
 ** \param[in] Transceiver Index of the transceiver
 ** \param[in] ubRegAccess contains the SPI register address and the read/write bit
 ** \param[in] ubData points to the memory where data shall be read from or written to.
 ** \param[in] ServiceID Service ID of the calling function (in case DET is needed)
 **
 ** \return Result of operation
 ** \retval E_OK      SPI operation successful
 ** \retval E_NOT_OK  SPI operation failed
 */
STATIC FUNC( Std_ReturnType, CANTRCV_1_T03_CODE ) CanTrcv_1_T03_AccessSpi
(
    uint8 Transceiver,
    uint8 ubRegAccess,
    P2VAR(uint8, AUTOMATIC, CANTRCV_1_T03_APPL_DATA) ubData,
    uint8 ServiceID
);

#if ( CANTRCV_1_T03_GENERAL_WAKE_UP_SUPPORT != CANTRCV_1_T03_WAKEUP_NOT_SUPPORTED )
/** \brief Clears event status register
 **
 ** This function clears all events (system, transceiver and wakeup-pin)
 ** from the relating status register
 **
 ** \param[in] Transceiver Index of the transceiver
 ** \param[in] ServiceID Service ID of the calling function (in case DET is needed)
 **
 ** \return Result of operation
 ** \retval E_OK      operation successful
 ** \retval E_NOT_OK  operation failed
 */
STATIC FUNC( Std_ReturnType, CANTRCV_1_T03_CODE ) CanTrcv_1_T03_ClearEvStatusReg
(
    uint8 Transceiver,
    uint8 ServiceID
);
#endif /* CANTRCV_1_T03_GENERAL_WAKE_UP_SUPPORT != CANTRCV_1_T03_WAKEUP_NOT_SUPPORTED */

#if (CANTRCV_1_T03_GENERAL_WAKE_UP_SUPPORT != CANTRCV_1_T03_WAKEUP_NOT_SUPPORTED)
/** \brief Internal check wakeup event function
 **
 ** This function checks if a wakeup event (POR, SysErr, ByBus, Pin) occurred.
 ** If so, the appropriate wakeup source mask is reported to EcuM by calling
 ** EcuM_SetWakeupSource and the reporting is locked afterwards (until
 ** rearmed when switching to state 'STANDBY'.
 **
 ** \param[in] Transceiver Index of the transceiver
 ** \param[in] ServiceID Service ID of the calling function (in case DET is needed)
 **
 ** \return Result of operation
 ** \retval E_OK      wakeup event reported to EcuM
 ** \retval E_NOT_OK  no wakeup event reported to EcuM
  */
STATIC FUNC( Std_ReturnType, CANTRCV_1_T03_CODE ) CanTrcv_1_T03_CheckAndReportWakeup
(
    uint8 Transceiver,
    uint8 ServiceID
);
#endif /* CANTRCV_1_T03_GENERAL_WAKE_UP_SUPPORT != CANTRCV_1_T03_WAKEUP_NOT_SUPPORTED */

#define CANTRCV_1_T03_STOP_SEC_CODE
#include <CanTrcv_1_T03_MemMap.h>

/*==================[external constants]=====================================*/

/*==================[internal constants]=====================================*/

/*==================[external data]==========================================*/

/*==================[internal data]==========================================*/

#define CANTRCV_1_T03_START_SEC_VAR_INIT_8
#include <CanTrcv_1_T03_MemMap.h>
/* Deviation MISRAC2012-1 */
STATIC VAR(uint8, CANTRCV_1_T03_VAR) CanTrcv_1_T03_InitState = CANTRCV_1_T03_NOT_ACTIVE;

#define CANTRCV_1_T03_STOP_SEC_VAR_INIT_8
#include <CanTrcv_1_T03_MemMap.h>

#define CANTRCV_1_T03_START_SEC_VAR_INIT_UNSPECIFIED
#include <CanTrcv_1_T03_MemMap.h>

/* Global Configuration Pointer */
P2CONST(CanTrcv_1_T03_ConfigType, CANTRCV_1_T03_VAR, CANTRCV_1_T03_APPL_CONST) CanTrcv_1_T03_ConfigPtr = NULL_PTR;

#define CANTRCV_1_T03_STOP_SEC_VAR_INIT_UNSPECIFIED
#include <CanTrcv_1_T03_MemMap.h>

/*==================[external function definitions]==========================*/

#define CANTRCV_1_T03_START_SEC_CODE
#include <CanTrcv_1_T03_MemMap.h>

FUNC( Std_ReturnType, CANTRCV_1_T03_CODE) CanTrcv_1_T03_IsValidConfig
(
        P2CONST(void,AUTOMATIC,CANTRCV_1_T03_APPL_CONST) voidConfigPtr
)
{
    /* Assume an invalid configuration */
    Std_ReturnType RetVal = E_NOT_OK;
    P2CONST(CanTrcv_1_T03_ConfigType,AUTOMATIC,CANTRCV_1_T03_APPL_CONST) ConfigPtr = voidConfigPtr;

    DBG_CANTRCV_1_T03_ISVALIDCONFIG_ENTRY(voidConfigPtr);

    if (ConfigPtr != NULL_PTR)
    {
        /* Check if the configuration fits to the platform */
        if (TS_PlatformSigIsValid(ConfigPtr->PlatformSignature))
        {
            /* Validate the post build configuration against the compile time configuration */
            if (CANTRCV_1_T03_CFG_SIGNATURE == ConfigPtr->CfgSignature)
            {
                /* Validate the post build configuration against the link time configuration */
                if (CanTrcv_1_T03_LcfgSignature == ConfigPtr->LcfgSignature)
                {
                    /* Validate the Published information in post build configuration against the
                       Published information in compile time configuration*/
                    if(CANTRCV_1_T03_PUBLIC_INFO_SIGNATURE == ConfigPtr->PublicInfoSignature)
                    {
                        /* Indicate that the configuration is valid */
                        RetVal = E_OK;
                    }
                }
            }
        }
    }

    DBG_CANTRCV_1_T03_ISVALIDCONFIG_EXIT(RetVal,voidConfigPtr);
    return RetVal;
}

FUNC( void, CANTRCV_1_T03_CODE) CanTrcv_1_T03_Init
(
    P2CONST(CanTrcv_1_T03_ConfigType, AUTOMATIC, CANTRCV_1_T03_APPL_CONST) ConfigPtr
)
{

    P2CONST(CanTrcv_1_T03_ConfigType,AUTOMATIC,CANTRCV_1_T03_APPL_CONST) LocalConfigPtr = ConfigPtr;

    /** \brief This compile time assertions checks the restriction of Spi_DataType
     ** (see Limitation documentation for more details) */
    TS_STATIC_ASSERT( ((sizeof(Spi_DataType) == 1U) || (sizeof(Spi_DataType) == 2U)),
                  CanTrcv_restricts_Spi_DataType_to_8_or_16bit);

    DBG_CANTRCV_1_T03_INIT_ENTRY(ConfigPtr);

    /* reset initialization state */
    CanTrcv_1_T03_InitState = CANTRCV_1_T03_NOT_ACTIVE;

    /* Save the configuration pointer */
#if (CANTRCV_1_T03_PBCFGM_SUPPORT_ENABLED == STD_ON)
    /* If the initialization function is called with a null pointer get the configuration from the
     * post build configuration manager */
    if (LocalConfigPtr == NULL_PTR)
    {
        PbcfgM_ModuleConfigPtrType ModuleConfig = NULL_PTR;
        if (E_OK == PbcfgM_GetConfig(
              CANTRCV_1_T03_MODULE_ID,
              CANTRCV_1_T03_INSTANCE_ID,
              &ModuleConfig))
        {
            LocalConfigPtr =
              (P2CONST(CanTrcv_1_T03_ConfigType, AUTOMATIC, CANTRCV_1_T03_APPL_CONST)) ModuleConfig;
        }
    }
#endif /* CANTRCV_1_T03_PBCFGM_SUPPORT_ENABLED == STD_OFF */

/* check if development error detection is enabled */
#if (CANTRCV_1_T03_DEV_ERROR_DETECT == STD_ON)

    /* check whether parameter CanTrcv_RootPtr is a NULL_PTR */
    if(LocalConfigPtr == NULL_PTR)
    {
        /* found a NULL_PTR, report to DET */
        (void)Det_ReportError(CANTRCV_1_T03_MODULE_ID,
                              CANTRCV_1_T03_INSTANCE_ID,
                              CANTRCV_1_T03_INIT_ID,
                              CANTRCV_1_T03_E_PARAM_POINTER
                             );
    }
    /* check that configuration pointer is valid */
    else if ( E_OK != CanTrcv_1_T03_IsValidConfig(LocalConfigPtr))
    {
        (void)Det_ReportError(CANTRCV_1_T03_MODULE_ID,
                              CANTRCV_1_T03_INSTANCE_ID,
                              CANTRCV_1_T03_INIT_ID,
                              CANTRCV_1_T03_E_PARAM_POINTER
                             );
    }
    else
#endif /* CANTRCV_1_T03_DEV_ERROR_DETECT */

    /* perform functionality */
    {
        uint8 Transceiver;
        Std_ReturnType ret = E_OK;

        CanTrcv_1_T03_ConfigPtr = LocalConfigPtr;

        /* Initialize each configured CanTrcv Channels */
        /* DET have also to be checked for each transceivers */
        for (Transceiver = 0U; (Transceiver < CanTrcv_1_T03_ConfigPtr->nrOfChannels) && (ret == E_OK); Transceiver++)
        {
            /* ---- initialize run-time data structure CanTrcv_1_T03_TrcvState ---- */
#if (CANTRCV_1_T03_GENERAL_WAKE_UP_SUPPORT != CANTRCV_1_T03_WAKEUP_NOT_SUPPORTED)
            CanTrcv_1_T03_TrcvState[Transceiver].WakeupModeEnabled = TRUE;
            CanTrcv_1_T03_TrcvState[Transceiver].WakeupSource = 0U;
            CanTrcv_1_T03_TrcvState[Transceiver].WakeupReason = CANTRCV_WU_POWER_ON;
               /* check if a wakeup has been detected */
            (void)CanTrcv_1_T03_CheckAndReportWakeup( Transceiver, CANTRCV_1_T03_INIT_ID);
#endif /* (CANTRCV_1_T03_GENERAL_WAKE_UP_SUPPORT != CANTRCV_1_T03_WAKEUP_NOT_SUPPORTED) */

            /* Internal function to initialize trcv as this action has also
             * to be done in CanTrcv_1_T03_SetOpMode.
             */
            ret = CanTrcv_1_T03_InternalTrcvInit( Transceiver,
                                                  CANTRCV_1_T03_CFG_GET_CHANNEL_CFG(Transceiver).CanTrcvInitState,
                                                  CANTRCV_1_T03_INIT_ID
                                                );
        }

        if(E_OK == ret)
        {
            /* CanTrcv initialization successful */
            CanTrcv_1_T03_InitState = CANTRCV_1_T03_ACTIVE;
        }
    }

    /* In case all APIs (Operating mode, Wakeup mode, Partial networking) are turned off
     * this prevents the compiler warning "CanTrcv_1_T03_InitState" was set but never used. */
    TS_PARAM_UNUSED(CanTrcv_1_T03_InitState);

    DBG_CANTRCV_1_T03_INIT_EXIT(ConfigPtr);
}

/* ----------------------------------------------------------------------------------------- */

#if (CANTRCV_1_T03_OPERATION_MODE_API == STD_ON)
FUNC( Std_ReturnType, CANTRCV_1_T03_CODE ) CanTrcv_1_T03_SetOpMode
(
    uint8 Transceiver,
    CanTrcv_TrcvModeType OpMode
)
{
    /* Shall be initialized to E_OK for check mechanism */
    Std_ReturnType RetVal = E_NOT_OK;

    DBG_CANTRCV_1_T03_SETOPMODE_ENTRY(Transceiver,OpMode);

#if (CANTRCV_1_T03_DEV_ERROR_DETECT == STD_ON)

    /* CanTrcv.ASR40.CanTrcv122 */
    if (CANTRCV_1_T03_NOT_ACTIVE == CanTrcv_1_T03_InitState)
    {
        CANTRCV_DET_ERROR(CANTRCV_1_T03_SETOPMODE_ID,CANTRCV_1_T03_E_UNINIT);
    }
    /* CanTrcv.ASR40.CanTrcv123 */
    else if (Transceiver >= CanTrcv_1_T03_ConfigPtr->nrOfChannels)
    {
        CANTRCV_DET_ERROR(CANTRCV_1_T03_SETOPMODE_ID,CANTRCV_1_T03_E_INVALID_TRANSCEIVER);
    }
    /* CanTrcv.ASR40.CanTrcv087 */
    else if (CANTRCV_OPMODE_UNKNOWN(OpMode))
    {
        CANTRCV_DET_ERROR(CANTRCV_1_T03_SETOPMODE_ID,CANTRCV_1_T03_E_PARAM_TRCV_OPMODE);
    }
    else
#endif /* CANTRCV_1_T03_DEV_ERROR_DETECT == STD_ON */
    {
        /* get current state; Do this after ensure that Transceiver is within range! */
        uint8 CurMode = CanTrcv_1_T03_TrcvState[Transceiver].CurrentMode;

        /* CanTrcv.ASR40.CanTrcv120 */
        /* CanTrcv.EB.SetOpMode.InvalidMode */
        if (((uint8)CANTRCV_TRCVMODE_SLEEP == CurMode) && (CANTRCV_TRCVMODE_STANDBY == OpMode))
        {
#if (CANTRCV_1_T03_DEV_ERROR_DETECT == STD_ON)
            CANTRCV_DET_ERROR(CANTRCV_1_T03_SETOPMODE_ID,CANTRCV_1_T03_E_TRCV_NOT_NORMAL);
#endif /* CANTRCV_1_T03_DEV_ERROR_DETECT == STD_ON */
        }
        /* CanTrcv.ASR40.CanTrcv121 */
        else if (((uint8)CANTRCV_TRCVMODE_NORMAL == CurMode) && (CANTRCV_TRCVMODE_SLEEP == OpMode))
        {
#if (CANTRCV_1_T03_DEV_ERROR_DETECT == STD_ON)
            CANTRCV_DET_ERROR(CANTRCV_1_T03_SETOPMODE_ID,CANTRCV_1_T03_E_TRCV_NOT_STANDBY);
#endif /* CANTRCV_1_T03_DEV_ERROR_DETECT == STD_ON */
        }
        else
        {
            /* mode transition allowed, perform it now */
            RetVal = CanTrcv_1_T03_InternalSetOpMode( Transceiver,
                                                      (uint8)OpMode,
                                                      CANTRCV_1_T03_SETOPMODE_ID
                                                    );

            if (E_OK == RetVal)
            {
                /* Abstracted Transceiver Id expected from CanIf for callbacks */
                uint8 CanIfTrcvId = CANTRCV_1_T03_CFG_GET_CHANNEL_CFG(Transceiver).CanIfTrcvId;

#if ( CANTRCV_1_T03_PN_SUPPORT == STD_ON )
#if ( CANTRCV_1_T03_CANIF_PN_CALLBACK_SUPPORT == STD_ON)
                if((CANTRCV_1_T03_CFG_GET_CHANNEL_CFG(Transceiver).CanTrcvPnEnabled != 0U) &&
                   (CANTRCV_TRCVMODE_NORMAL == OpMode))
                {
                    /* CanTrcv.ASR40.CanTrcv188 */
                    CanIf_ConfirmPnAvailability( CanIfTrcvId );
                }
#endif /* #if ( CANTRCV_1_T03_CANIF_PN_CALLBACK_SUPPORT == STD_ON) */
#endif /* ( CANTRCV_1_T03_PN_SUPPORT == STD_ON ) */
                /* CanTrcv.ASR40.CanTrcv158 */
                /* call indication to inform of the successful transition */
                CanIf_TrcvModeIndication(CanIfTrcvId, OpMode);
            }
        }
    }

    DBG_CANTRCV_1_T03_SETOPMODE_EXIT(RetVal,Transceiver,OpMode);
    return RetVal;
}
#endif /* CANTRCV_1_T03_OPERATION_MODE_API == STD_ON */

/* ----------------------------------------------------------------------------------------- */

#if (CANTRCV_1_T03_OPERATION_MODE_API == STD_ON)
FUNC( Std_ReturnType, CANTRCV_1_T03_CODE ) CanTrcv_1_T03_GetOpMode
(
    uint8 Transceiver,
    P2VAR( CanTrcv_TrcvModeType, AUTOMATIC, CANTRCV_1_T03_APPL_DATA ) OpMode
)
{
    /* Shall be initialized to E_OK for check mechanism */
    Std_ReturnType RetVal = E_NOT_OK;

    /* Buffer managing data of transceiver registers */
    uint8 ubDataRegBuffer;

    DBG_CANTRCV_1_T03_GETOPMODE_ENTRY(Transceiver,OpMode);

#if (CANTRCV_1_T03_DEV_ERROR_DETECT == STD_ON)

    /* CanTrcv.ASR40.CanTrcv124 */
    if (CANTRCV_1_T03_NOT_ACTIVE == CanTrcv_1_T03_InitState)
    {
        CANTRCV_DET_ERROR(CANTRCV_1_T03_GETOPMODE_ID,CANTRCV_1_T03_E_UNINIT);
    }
    /* CanTrcv.ASR40.CanTrcv129 */
    else if (Transceiver >= CanTrcv_1_T03_ConfigPtr->nrOfChannels)
    {
        CANTRCV_DET_ERROR(CANTRCV_1_T03_GETOPMODE_ID,CANTRCV_1_T03_E_INVALID_TRANSCEIVER);
    }
    /* CanTrcv.ASR40.CanTrcv132 */
    else if (NULL_PTR == OpMode)
    {
        CANTRCV_DET_ERROR(CANTRCV_1_T03_GETOPMODE_ID,CANTRCV_1_T03_E_PARAM_POINTER);
    }
    else

#endif /* CANTRCV_1_T03_DEV_ERROR_DETECT == STD_ON */

    {
        /* Check the mode control register for getting MC mode */
        RetVal = CanTrcv_1_T03_AccessSpi( Transceiver,
                                          (CANTRCV_SPI_READ|MODE_CONTROL_REGISTER_ADDR),
                                          &ubDataRegBuffer,
                                          CANTRCV_1_T03_GETOPMODE_ID
                                        );

        if(E_OK == RetVal)
        {
            /* CanTrcv.ASR40.CanTrcv106 */
            switch(ubDataRegBuffer & MC_CMD_MASK_MODE)
            {
                case MC_CMD_SLEEP_MODE:
                {
                    *OpMode = CANTRCV_TRCVMODE_SLEEP;

                    /* Already set to RetVal = E_OK; */
                    break;
                }

                case MC_CMD_STANDBY_MODE:
                {
                    *OpMode = CANTRCV_TRCVMODE_STANDBY;

                    /* Already set to RetVal = E_OK; */
                    break;
                }

                case MC_CMD_NORMAL_MODE:
                {
                    *OpMode = CANTRCV_TRCVMODE_NORMAL;

                    /* Already set to RetVal = E_OK; */
                    break;
                }

                /* CHECK: NOPARSE */
                default:
                {
                    /* We let the previous mode as unexpected behavior happened */

                    RetVal = E_NOT_OK;
                    break;
                }
                /* CHECK: PARSE */
            }
        }
    }


    DBG_CANTRCV_1_T03_GETOPMODE_EXIT(RetVal,Transceiver,OpMode);
    return RetVal;
}
#endif /* CANTRCV_1_T03_OPERATION_MODE_API == STD_ON */

/* ----------------------------------------------------------------------------------------- */

#if (CANTRCV_1_T03_WAKEUP_MODE_API == STD_ON)
FUNC( Std_ReturnType, CANTRCV_1_T03_CODE ) CanTrcv_1_T03_GetBusWuReason
(
    uint8 Transceiver,
    P2VAR( CanTrcv_TrcvWakeupReasonType, AUTOMATIC, CANTRCV_1_T03_APPL_DATA ) reason
)
{
    /* Shall be initialized to E_OK for check mechanism */
    Std_ReturnType RetVal = E_NOT_OK;

    DBG_CANTRCV_1_T03_GETBUSWUREASON_ENTRY(Transceiver,reason);


#if (CANTRCV_1_T03_DEV_ERROR_DETECT == STD_ON)

    /* CanTrcv.ASR40.CanTrcv125 */
    if (CANTRCV_1_T03_NOT_ACTIVE == CanTrcv_1_T03_InitState)
    {
        CANTRCV_DET_ERROR(CANTRCV_1_T03_GETBUSWUREASON_ID,CANTRCV_1_T03_E_UNINIT);
    }
    /* CanTrcv.ASR40.CanTrcv130 */
    else if (Transceiver >= CanTrcv_1_T03_ConfigPtr->nrOfChannels)
    {
        CANTRCV_DET_ERROR(CANTRCV_1_T03_GETBUSWUREASON_ID,CANTRCV_1_T03_E_INVALID_TRANSCEIVER);
    }
    /* CanTrcv.ASR40.CanTrcv133 */
    else if (NULL_PTR == reason)
    {
        CANTRCV_DET_ERROR(CANTRCV_1_T03_GETBUSWUREASON_ID,CANTRCV_1_T03_E_PARAM_POINTER);
    }
    else

#endif /* CANTRCV_1_T03_DEV_ERROR_DETECT == STD_ON */

    {

        RetVal = E_OK;
#if (CANTRCV_1_T03_GENERAL_WAKE_UP_SUPPORT != CANTRCV_1_T03_WAKEUP_NOT_SUPPORTED)
       *reason = CanTrcv_1_T03_TrcvState[Transceiver].WakeupReason;
#else /* CANTRCV_1_T03_GENERAL_WAKE_UP_SUPPORT != CANTRCV_1_T03_WAKEUP_NOT_SUPPORTED */
        *reason = CANTRCV_WU_NOT_SUPPORTED;
#endif /* CANTRCV_1_T03_GENERAL_WAKE_UP_SUPPORT != CANTRCV_1_T03_WAKEUP_NOT_SUPPORTED */
        }

    DBG_CANTRCV_1_T03_GETBUSWUREASON_EXIT(RetVal,Transceiver,reason);
    return RetVal;
}
#endif /* CANTRCV_1_T03_WAKEUP_MODE_API == STD_ON */

/* ----------------------------------------------------------------------------------------- */

/* CanTrcv.ASR40.CanTrcv109 */
#if (CANTRCV_1_T03_GET_VERSION_INFO == STD_ON)
FUNC( void, CANTRCV_1_T03_CODE ) CanTrcv_1_T03_GetVersionInfo
(
    P2VAR( Std_VersionInfoType, AUTOMATIC, CANTRCV_1_T03_APPL_DATA ) versioninfo
)
{
#if (CANTRCV_1_T03_DEV_ERROR_DETECT == STD_ON)

    /* CanTrcv.ASR40.CanTrcv134 */

    DBG_CANTRCV_1_T03_GETVERSIONINFO_ENTRY(versioninfo);
    if (NULL_PTR == versioninfo)
    {
        CANTRCV_DET_ERROR(CANTRCV_1_T03_GETVERSIONINFO_ID,CANTRCV_1_T03_E_PARAM_POINTER);
    }
    else

#endif /* CANTRCV_1_T03_DEV_ERROR_DETECT == STD_ON */

    {
        /* write version information */
        versioninfo->vendorID = CANTRCV_1_T03_VENDOR_ID;
        versioninfo->moduleID = CANTRCV_1_T03_MODULE_ID;
        versioninfo->sw_major_version = CANTRCV_1_T03_SW_MAJOR_VERSION;
        versioninfo->sw_minor_version = CANTRCV_1_T03_SW_MINOR_VERSION;
        versioninfo->sw_patch_version = CANTRCV_1_T03_SW_PATCH_VERSION;
    }

    DBG_CANTRCV_1_T03_GETVERSIONINFO_EXIT(versioninfo);
}
#endif /* CANTRCV_1_T03_GET_VERSION_INFO == STD_ON */

/* ----------------------------------------------------------------------------------------- */

#if (CANTRCV_1_T03_WAKEUP_MODE_API == STD_ON)
FUNC( Std_ReturnType, CANTRCV_1_T03_CODE ) CanTrcv_1_T03_SetWakeupMode
(
    uint8 Transceiver,
    CanTrcv_TrcvWakeupModeType TrcvWakeupMode
)
{
    /* Shall be initialized to E_OK for check mechanism */
    Std_ReturnType RetVal = E_NOT_OK;

    DBG_CANTRCV_1_T03_SETWAKEUPMODE_ENTRY(Transceiver,TrcvWakeupMode);

#if (CANTRCV_1_T03_DEV_ERROR_DETECT == STD_ON)

    /* CanTrcv.ASR40.CanTrcv127 */
    if (CANTRCV_1_T03_NOT_ACTIVE == CanTrcv_1_T03_InitState)
    {
        CANTRCV_DET_ERROR(CANTRCV_1_T03_SETWAKEUPMODE_ID,CANTRCV_1_T03_E_UNINIT);
    }
    /* CanTrcv.ASR40.CanTrcv131 */
    else if (Transceiver >= CanTrcv_1_T03_ConfigPtr->nrOfChannels)
    {
        CANTRCV_DET_ERROR(CANTRCV_1_T03_SETWAKEUPMODE_ID,CANTRCV_1_T03_E_INVALID_TRANSCEIVER);
    }
    /* CanTrcv.ASR40.CanTrcv089 */
    else if (CANTRCV_WUPMODE_UNKNOWN(TrcvWakeupMode))
    {
        CANTRCV_DET_ERROR(CANTRCV_1_T03_SETWAKEUPMODE_ID,CANTRCV_1_T03_E_PARAM_TRCV_WAKEUP_MODE);
    }
    else

#endif /* CANTRCV_1_T03_DEV_ERROR_DETECT == STD_ON */

    {

#if (CANTRCV_1_T03_GENERAL_WAKE_UP_SUPPORT != CANTRCV_1_T03_WAKEUP_NOT_SUPPORTED)

        /* CanTrcv.ASR40.CanTrcv095 */
        switch(TrcvWakeupMode)
        {
            /* CanTrcv.ASR40.CanTrcv111 */
            case CANTRCV_WUMODE_CLEAR:
            {
                /* CanTrcv.ASR40.CanTrcv150 */
                /* Clear all event: status flags must be cleared to avoid  deadlock */
                RetVal = CanTrcv_1_T03_ClearEvStatusReg( Transceiver,
                                                         CANTRCV_1_T03_SETWAKEUPMODE_ID
                                                        );

                break;
            }
            case CANTRCV_WUMODE_ENABLE:
            {
                /* set wakeup enable flag */
                CanTrcv_1_T03_TrcvState[Transceiver].WakeupModeEnabled = TRUE;

                /* CanTrcv.ASR40.CanTrcv111*/
                if (CanTrcv_1_T03_TrcvState[Transceiver].WakeupSource != 0U)
                {
                    EcuM_SetWakeupEvent(CanTrcv_1_T03_TrcvState[Transceiver].WakeupSource);
                }

                RetVal = E_OK;
                break;
            }
            case CANTRCV_WUMODE_DISABLE:
            {
                /* CanTrcv.ASR40.CanTrcv093*/

                /* clear wakeup enable flag */
                CanTrcv_1_T03_TrcvState[Transceiver].WakeupModeEnabled = FALSE;

                RetVal = E_OK;
                break;
            }

            /* CHECK: NOPARSE */
            default: /* unreachable code */
                break;
            /* CHECK: PARSE */
        }

#endif /* CANTRCV_1_T03_GENERAL_WAKE_UP_SUPPORT != CANTRCV_1_T03_WAKEUP_NOT_SUPPORTED */
    }


    DBG_CANTRCV_1_T03_SETWAKEUPMODE_EXIT(RetVal,Transceiver,TrcvWakeupMode);
    return RetVal;
}
#endif /* CANTRCV_1_T03_WAKEUP_MODE_API == STD_ON */

/* ----------------------------------------------------------------------------------------- */

#if (CANTRCV_1_T03_WAKEUP_MODE_API == STD_ON)
FUNC( Std_ReturnType, CANTRCV_1_T03_CODE ) CanTrcv_1_T03_CheckWakeup
(
    uint8 Transceiver
)
{
    Std_ReturnType RetVal = E_NOT_OK;

    DBG_CANTRCV_1_T03_CHECKWAKEUP_ENTRY(Transceiver);


#if (CANTRCV_1_T03_DEV_ERROR_DETECT == STD_ON)

    /* CanTrcv.ASR40.CanTrcv144 */
    if (CANTRCV_1_T03_NOT_ACTIVE == CanTrcv_1_T03_InitState)
    {
        CANTRCV_DET_ERROR(CANTRCV_1_T03_CHECKWAKEUP_ID,CANTRCV_1_T03_E_UNINIT);
    }
    /* CanTrcv.ASR40.CanTrcv145 */
    else if (Transceiver >= CanTrcv_1_T03_ConfigPtr->nrOfChannels)
    {
        CANTRCV_DET_ERROR(CANTRCV_1_T03_CHECKWAKEUP_ID,CANTRCV_1_T03_E_INVALID_TRANSCEIVER);
    }
    else

#endif /* CANTRCV_1_T03_DEV_ERROR_DETECT == STD_ON */
    {

#if (CANTRCV_1_T03_GENERAL_WAKE_UP_SUPPORT != CANTRCV_1_T03_WAKEUP_NOT_SUPPORTED)
        RetVal = CanTrcv_1_T03_CheckAndReportWakeup( Transceiver,
                                                     CANTRCV_1_T03_CHECKWAKEUP_ID
                                                   );
#endif /* CANTRCV_1_T03_GENERAL_WAKE_UP_SUPPORT != CANTRCV_1_T03_WAKEUP_NOT_SUPPORTED */

    }


    DBG_CANTRCV_1_T03_CHECKWAKEUP_EXIT(RetVal,Transceiver);
    return RetVal;
}
#endif /* CANTRCV_1_T03_WAKEUP_MODE_API == STD_ON */



#if (CANTRCV_1_T03_PN_SUPPORT == STD_ON)

FUNC( Std_ReturnType, CANTRCV_1_T03_CODE ) CanTrcv_1_T03_GetTrcvSystemData
(
    uint8 Transceiver,
    P2CONST (uint32, AUTOMATIC, CANTRCV_1_T03_APPL_CONST) TrcvSysData
)
{
    /* Shall be initialized to E_NOT_OK for check mechanism */
    Std_ReturnType RetVal = E_NOT_OK;

    DBG_CANTRCV_1_T03_GETTRCVSYSTEMDATA_ENTRY(Transceiver,TrcvSysData);

#if (CANTRCV_1_T03_DEV_ERROR_DETECT == STD_ON)
    /* CanTrcv.ASR40.CanTrcv191 */
    if (CANTRCV_1_T03_NOT_ACTIVE == CanTrcv_1_T03_InitState)
    {
        CANTRCV_DET_ERROR(CANTRCV_1_T03_GETTRCVSYSTEMDATA_ID,CANTRCV_1_T03_E_UNINIT);
    }
    /* CanTrcv.ASR40.CanTrcv192 */
    else if (Transceiver >= CanTrcv_1_T03_ConfigPtr->nrOfChannels)
    {
       CANTRCV_DET_ERROR(CANTRCV_1_T03_GETTRCVSYSTEMDATA_ID,CANTRCV_1_T03_E_INVALID_TRANSCEIVER);
    }
    /* CanTrcv.ASR40.CanTrcv193 */
    else if (NULL_PTR == TrcvSysData)
    {
        CANTRCV_DET_ERROR(CANTRCV_1_T03_GETTRCVSYSTEMDATA_ID,CANTRCV_1_T03_E_PARAM_POINTER);
    }
    else
#else
    TS_PARAM_UNUSED(Transceiver);
    TS_PARAM_UNUSED(TrcvSysData);
#endif /* CANTRCV_1_T03_DEV_ERROR_DETECT == STD_ON */

    {
        RetVal = E_NOT_OK;
    }


    DBG_CANTRCV_1_T03_GETTRCVSYSTEMDATA_EXIT(RetVal,Transceiver,TrcvSysData);
    return RetVal;
}
#endif /* CANTRCV_1_T03_PN_SUPPORT == STD_ON */



#if (CANTRCV_1_T03_PN_SUPPORT == STD_ON)

FUNC( Std_ReturnType, CANTRCV_1_T03_CODE ) CanTrcv_1_T03_ClearTrcvWufFlag
(
    uint8 Transceiver
)
{
    /* Shall be initialized to E_OK for check mechanism */
    Std_ReturnType RetVal = E_NOT_OK;

    DBG_CANTRCV_1_T03_CLEARTRCVWUFFLAG_ENTRY(Transceiver);

#if (CANTRCV_1_T03_DEV_ERROR_DETECT == STD_ON)

    /* CanTrcv.ASR40.CanTrcv197 */
    if (CANTRCV_1_T03_NOT_ACTIVE == CanTrcv_1_T03_InitState)
    {
        CANTRCV_DET_ERROR(CANTRCV_1_T03_CLEARTRCVWUFFLAG_ID,CANTRCV_1_T03_E_UNINIT);
    }
    /* CanTrcv.ASR40.CanTrcv198 */
    else if (Transceiver >= CanTrcv_1_T03_ConfigPtr->nrOfChannels)
    {
        CANTRCV_DET_ERROR(CANTRCV_1_T03_CLEARTRCVWUFFLAG_ID,CANTRCV_1_T03_E_INVALID_TRANSCEIVER);
    }
    else
#endif
    {

        if(TRUE == CANTRCV_1_T03_CFG_GET_CHANNEL_CFG(Transceiver).CanTrcvHwPnSupport)
        {
            /* CanTrcv.ASR40.CanTrcv194 */
            /* Clear all event: status flag must be cleared to avoid deadlock */
            RetVal = CanTrcv_1_T03_ClearEvStatusReg( Transceiver,
                                                     CANTRCV_1_T03_CLEARTRCVWUFFLAG_ID
                                                    );

            /* Deviation from Implementation hints which are part of CanTrcv194:
             * The CanTrcv is not set to mode STANDBY.
             * Rationale: This implementation hint is for module CanSM
             * which invokes this API during the DeInit transition for PN. */
#if ( CANTRCV_1_T03_CANIF_PN_CALLBACK_SUPPORT == STD_ON)
            if(E_OK == RetVal)
            {
                /* CanTrcv.ASR40.CanTrcv195 */
                CanIf_ClearTrcvWufFlagIndication
                    (
                        CANTRCV_1_T03_CFG_GET_CHANNEL_CFG(Transceiver).CanIfTrcvId
                    );
            }
#endif /* #if ( CANTRCV_1_T03_CANIF_PN_CALLBACK_SUPPORT == STD_ON) */
        }
    }


    DBG_CANTRCV_1_T03_CLEARTRCVWUFFLAG_EXIT(RetVal,Transceiver);
    return RetVal;
}
#endif /* CANTRCV_1_T03_PN_SUPPORT == STD_ON */

#if (CANTRCV_1_T03_PN_SUPPORT == STD_ON)

FUNC( Std_ReturnType, CANTRCV_1_T03_CODE ) CanTrcv_1_T03_ReadTrcvTimeoutFlag
(
    uint8 Transceiver,
    P2VAR(CanTrcv_TrcvFlagStateType, AUTOMATIC, CANTRCV_1_T03_APPL_DATA) FlagState
)
{
    /* Shall be initialized to E_NOT_OK for check mechanism */
    Std_ReturnType RetVal = E_NOT_OK;

    DBG_CANTRCV_1_T03_READTRCVTIMEOUTFLAG_ENTRY(Transceiver,FlagState);

#if (CANTRCV_1_T03_DEV_ERROR_DETECT == STD_ON)

    if (CANTRCV_1_T03_NOT_ACTIVE == CanTrcv_1_T03_InitState)
    {
        CANTRCV_DET_ERROR(CANTRCV_1_T03_READTRCVTIMEOUTFLAG_ID,CANTRCV_1_T03_E_UNINIT);
    }
    /* CanTrcv.ASR40.CanTrcv199 */
    else if (Transceiver >= CanTrcv_1_T03_ConfigPtr->nrOfChannels)
    {
        CANTRCV_DET_ERROR(CANTRCV_1_T03_READTRCVTIMEOUTFLAG_ID,CANTRCV_1_T03_E_INVALID_TRANSCEIVER);
    }
    /* CanTrcv.ASR40.CanTrcv200 */
    else if (NULL_PTR == FlagState)
    {
        CANTRCV_DET_ERROR(CANTRCV_1_T03_READTRCVTIMEOUTFLAG_ID,CANTRCV_1_T03_E_PARAM_POINTER);
    }
    else
#endif
    {

        if(TRUE == CANTRCV_1_T03_CFG_GET_CHANNEL_CFG(Transceiver).CanTrcvHwPnSupport)
        {
            /* Buffer managing data of transceiver registers */
            uint8 ubDataRegBuffer;
            /* store status of SPI access */
            Std_ReturnType SpiAccess;

            /* Check the Transceiver event capture enable register */
            SpiAccess = CanTrcv_1_T03_AccessSpi( Transceiver,
                                                (CANTRCV_SPI_READ|TRANSCEIVER_EVENT_EN_REGISTER_ADDR),
                                                 &ubDataRegBuffer,
                                                 CANTRCV_1_T03_READTRCVTIMEOUTFLAG_ID
                                               );

            if( (E_OK == SpiAccess) &&
                ((ubDataRegBuffer & CANTRCV_1_T03_TRANSCEIVER_ENABLE_CFE) == CANTRCV_1_T03_TRANSCEIVER_ENABLE_CFE) )
            {
                /* CAN failure detection enabled */

                /* Check the Transceiver event status register */
                SpiAccess = CanTrcv_1_T03_AccessSpi( Transceiver,
                                                    (CANTRCV_SPI_READ|TRCV_EVENT_STATUS_REGISTER_ADDR),
                                                     &ubDataRegBuffer,
                                                     CANTRCV_1_T03_READTRCVTIMEOUTFLAG_ID
                                                   );

                if(E_OK == SpiAccess)
                {
                    /* status successful obtained  */
                    RetVal = E_OK;

                    *FlagState = ((ubDataRegBuffer & CANTRCV_1_T03_TRANSCEIVER_EVENT_STATUS_CF)
                                  == CANTRCV_1_T03_TRANSCEIVER_EVENT_STATUS_CF)
                        ? (CanTrcv_TrcvFlagStateType)CANTRCV_FLAG_SET
                        : (CanTrcv_TrcvFlagStateType)CANTRCV_FLAG_CLEARED;
                }
            }
        }
    }

    DBG_CANTRCV_1_T03_READTRCVTIMEOUTFLAG_EXIT(RetVal,Transceiver,FlagState);
    return RetVal;
}

#endif /* CANTRCV_1_T03_PN_SUPPORT == STD_ON */


#if (CANTRCV_1_T03_PN_SUPPORT == STD_ON)

FUNC( Std_ReturnType, CANTRCV_1_T03_CODE ) CanTrcv_1_T03_ClearTrcvTimeoutFlag
(
    uint8 Transceiver
)
{
    /* Shall be initialized to E_OK for check mechanism */
    Std_ReturnType RetVal = E_NOT_OK;

    DBG_CANTRCV_1_T03_CLEARTRCVTIMEOUTFLAG_ENTRY(Transceiver);

#if (CANTRCV_1_T03_DEV_ERROR_DETECT == STD_ON)

    if (CANTRCV_1_T03_NOT_ACTIVE == CanTrcv_1_T03_InitState)
    {
        CANTRCV_DET_ERROR(CANTRCV_1_T03_CLEARTRCVTIMEOUTFLAG_ID,CANTRCV_1_T03_E_UNINIT);
    }
    /* CanTrcv.ASR40.CanTrcv201 */
    else if (Transceiver >= CanTrcv_1_T03_ConfigPtr->nrOfChannels)
    {
        CANTRCV_DET_ERROR(CANTRCV_1_T03_CLEARTRCVTIMEOUTFLAG_ID,CANTRCV_1_T03_E_INVALID_TRANSCEIVER);
    }
    else
#endif
    {

        if(TRUE == CANTRCV_1_T03_CFG_GET_CHANNEL_CFG(Transceiver).CanTrcvHwPnSupport)
        {
            /* Buffer managing data of transceiver registers */
            uint8 ubDataRegBuffer;

            /* Write a 1 to the CF flag to clear it (writing 0 has no effect ) */
            ubDataRegBuffer = (uint8)(CANTRCV_1_T03_TRANSCEIVER_EVENT_STATUS_CF);

            RetVal = CanTrcv_1_T03_AccessSpi( Transceiver,
                                              (CANTRCV_SPI_WRITE|TRCV_EVENT_STATUS_REGISTER_ADDR),
                                              &ubDataRegBuffer,
                                              CANTRCV_1_T03_CLEARTRCVTIMEOUTFLAG_ID
                                            );
        }
    }


    DBG_CANTRCV_1_T03_CLEARTRCVTIMEOUTFLAG_EXIT(RetVal,Transceiver);
    return RetVal;
}
#endif /* CANTRCV_1_T03_PN_SUPPORT == STD_ON */


#if (CANTRCV_1_T03_PN_SUPPORT == STD_ON)

FUNC( Std_ReturnType, CANTRCV_1_T03_CODE ) CanTrcv_1_T03_ReadTrcvSilenceFlag
(
    uint8 Transceiver,
    P2VAR(CanTrcv_TrcvFlagStateType, AUTOMATIC, CANTRCV_1_T03_APPL_DATA) FlagState
)
{
    /* Shall be initialized to E_NOT_OK for check mechanism */
    Std_ReturnType RetVal = E_NOT_OK;

    DBG_CANTRCV_1_T03_READTRCVSILENCEFLAG_ENTRY(Transceiver,FlagState);

#if (CANTRCV_1_T03_DEV_ERROR_DETECT == STD_ON)

    if (CANTRCV_1_T03_NOT_ACTIVE == CanTrcv_1_T03_InitState)
    {
        CANTRCV_DET_ERROR(CANTRCV_1_T03_READTRCVSILENCEFLAG_ID,CANTRCV_1_T03_E_UNINIT);
    }
    /* CanTrcv.ASR40.CanTrcv202 */
    else if (Transceiver >= CanTrcv_1_T03_ConfigPtr->nrOfChannels)
    {
        CANTRCV_DET_ERROR(CANTRCV_1_T03_READTRCVSILENCEFLAG_ID,CANTRCV_1_T03_E_INVALID_TRANSCEIVER);
    }
    /* CanTrcv.ASR40.CanTrcv203 */
    else if (NULL_PTR == FlagState)
    {
        CANTRCV_DET_ERROR(CANTRCV_1_T03_READTRCVSILENCEFLAG_ID,CANTRCV_1_T03_E_PARAM_POINTER);
    }
    else
#endif
    {

        if(TRUE == CANTRCV_1_T03_CFG_GET_CHANNEL_CFG(Transceiver).CanTrcvHwPnSupport)
        {
            /* Buffer managing data of transceiver registers */
            uint8 ubDataRegBuffer;
            /* store status of SPI access */
            Std_ReturnType SpiAccess;

            /* Check the Transceiver event capture enable register */
            SpiAccess = CanTrcv_1_T03_AccessSpi( Transceiver,
                                                (CANTRCV_SPI_READ|TRANSCEIVER_EVENT_EN_REGISTER_ADDR),
                                                 &ubDataRegBuffer,
                                                 CANTRCV_1_T03_READTRCVSILENCEFLAG_ID
                                               );

            if( (E_OK == SpiAccess) &&
                ((ubDataRegBuffer & CANTRCV_1_T03_TRANSCEIVER_ENABLE_CBSE) == CANTRCV_1_T03_TRANSCEIVER_ENABLE_CBSE) )
            {
                /* CAN silence detection enabled */

                /* Check the Transceiver status register */
                SpiAccess = CanTrcv_1_T03_AccessSpi( Transceiver,
                                                    (CANTRCV_SPI_READ|TRANSCEIVER_STATUS_REGISTER_ADDR),
                                                     &ubDataRegBuffer,
                                                     CANTRCV_1_T03_READTRCVSILENCEFLAG_ID
                                                   );

                if(E_OK == SpiAccess)
                {
                    /* status successful obtained  */
                    RetVal = E_OK;

                    *FlagState = ((ubDataRegBuffer & CANTRCV_1_T03_TRCV_STATUS_CBSS)
                                  == CANTRCV_1_T03_TRCV_STATUS_CBSS)
                        ? (CanTrcv_TrcvFlagStateType)CANTRCV_FLAG_SET
                        : (CanTrcv_TrcvFlagStateType)CANTRCV_FLAG_CLEARED;
                }
            }
        }
    }


    DBG_CANTRCV_1_T03_READTRCVSILENCEFLAG_EXIT(RetVal,Transceiver,FlagState);
    return RetVal;
}

#endif /* CANTRCV_1_T03_PN_SUPPORT == STD_ON */


#if (CANTRCV_1_T03_PN_SUPPORT == STD_ON)

FUNC( Std_ReturnType, CANTRCV_1_T03_CODE ) CanTrcv_1_T03_SetPNActivationState
(
    CanTrcv_PNActivationType ActivationState
)
{
    /* Shall be initialized to E_OK for check mechanism */
    Std_ReturnType RetVal = E_NOT_OK;

    DBG_CANTRCV_1_T03_SETPNACTIVATIONSTATE_ENTRY(ActivationState);

#if (CANTRCV_1_T03_DEV_ERROR_DETECT == STD_ON)

    /* CanTrcv.ASR40.CanTrcv220 */
    if (CANTRCV_1_T03_NOT_ACTIVE == CanTrcv_1_T03_InitState)
    {
        CANTRCV_DET_ERROR(CANTRCV_1_T03_SETPNACTIVATIONSTATE_ID,CANTRCV_1_T03_E_UNINIT);
    }
    else
#endif
    {

        /* Used for loop on all transceiver */
        uint8 Transceiver;

        for (Transceiver = 0; Transceiver < CanTrcv_1_T03_ConfigPtr->nrOfChannels; Transceiver++)
        {
            if(TRUE == CANTRCV_1_T03_CFG_GET_CHANNEL_CFG(Transceiver).CanTrcvHwPnSupport)
            {
                /* Buffer managing data of transceiver registers */
                uint8 ubDataRegBuffer;

                /* Unlock all control register*/
                ubDataRegBuffer = (uint8)(~LOCK_CONTROL_2);
                RetVal = CanTrcv_1_T03_AccessSpi( Transceiver,
                                                  (CANTRCV_SPI_WRITE|LOCK_CONTROL_REGISTER_ADDR),
                                                  &ubDataRegBuffer,
                                                  CANTRCV_1_T03_SETPNACTIVATIONSTATE_ID
                                                );

                if(E_OK == RetVal)
                {
                    /* Check the CAN control register before switching operating mode*/
                    RetVal = CanTrcv_1_T03_AccessSpi( Transceiver,
                                                      (CANTRCV_SPI_READ|CAN_CTRL_REGISTER_ADDR),
                                                      &ubDataRegBuffer,
                                                      CANTRCV_1_T03_SETPNACTIVATIONSTATE_ID
                                                    );
                }

                if(E_OK == RetVal)
                {
                    /* CanTrcv.ASR40.CanTrcv221 */
                    if(PN_ENABLED == ActivationState)
                    {
                        /* Set CPNC = = PNCOK = 1 */
                        ubDataRegBuffer = ubDataRegBuffer | CANTRCV_1_T03_CAN_CTRL_CPNC | CANTRCV_1_T03_CAN_CTRL_PNCOK;
                        RetVal = CanTrcv_1_T03_AccessSpi( Transceiver,
                                                          (CANTRCV_SPI_WRITE|CAN_CTRL_REGISTER_ADDR),
                                                          &ubDataRegBuffer,
                                                          CANTRCV_1_T03_SETPNACTIVATIONSTATE_ID
                                                        );
                    }
                    /* CanTrcv.ASR40.CanTrcv222 */
                    /* CHECK: NOPARSE */
                    else if(PN_DISABLED == ActivationState)
                    {
                        /* Erasing of CPNC */
                        ubDataRegBuffer = ubDataRegBuffer & (uint8)(~CANTRCV_1_T03_CAN_CTRL_CPNC);
                        RetVal = CanTrcv_1_T03_AccessSpi( Transceiver,
                                                          (CANTRCV_SPI_WRITE|CAN_CTRL_REGISTER_ADDR),
                                                          &ubDataRegBuffer,
                                                          CANTRCV_1_T03_SETPNACTIVATIONSTATE_ID
                                                        );
                    }
                    else
                    {
                        RetVal = E_NOT_OK;
                    }
                    /* CHECK: PARSE */
                }

                if(E_OK == RetVal)
                {
                  /* Lock all control register*/
                  ubDataRegBuffer = LOCK_CONTROL_ALL;
                  RetVal = CanTrcv_1_T03_AccessSpi( Transceiver,
                                                    (CANTRCV_SPI_WRITE|LOCK_CONTROL_REGISTER_ADDR),
                                                    &ubDataRegBuffer,
                                                    CANTRCV_1_T03_SETPNACTIVATIONSTATE_ID
                                                  );
                }
            }
        }
    }


    DBG_CANTRCV_1_T03_SETPNACTIVATIONSTATE_EXIT(RetVal,ActivationState);
    return RetVal;
}

#endif /* CANTRCV_1_T03_PN_SUPPORT == STD_ON */


#if (CANTRCV_1_T03_PN_SUPPORT == STD_ON)

FUNC( Std_ReturnType, CANTRCV_1_T03_CODE )  CanTrcv_1_T03_CheckWakeFlag
(
    uint8 Transceiver
)
{
    /* Shall be initialized to E_OK for check mechanism */
    Std_ReturnType RetVal = E_NOT_OK;

    DBG_CANTRCV_1_T03_CHECKWAKEFLAG_ENTRY(Transceiver);

#if (CANTRCV_1_T03_DEV_ERROR_DETECT == STD_ON)

    if (CANTRCV_1_T03_NOT_ACTIVE == CanTrcv_1_T03_InitState)
    {
        CANTRCV_DET_ERROR(CANTRCV_1_T03_CHECKWAKEFLAG_ID,CANTRCV_1_T03_E_UNINIT);
    }
    /* CanTrcv.ASR40.CanTrcv225 */
    else if (Transceiver >= CanTrcv_1_T03_ConfigPtr->nrOfChannels)
    {
        CANTRCV_DET_ERROR(CANTRCV_1_T03_CHECKWAKEFLAG_ID,CANTRCV_1_T03_E_INVALID_TRANSCEIVER);
    }
    else
#endif
    {

        if(TRUE == CANTRCV_1_T03_CFG_GET_CHANNEL_CFG(Transceiver).CanTrcvHwPnSupport)
        {
            /* CanTrcv.ASR40.CanTrcv224.2 */
            (void) CanTrcv_1_T03_CheckAndReportWakeup( Transceiver,
                                                       CANTRCV_1_T03_CHECKWAKEFLAG_ID
                                                     );
#if ( CANTRCV_1_T03_CANIF_PN_CALLBACK_SUPPORT == STD_ON)
            /* CanTrcv.ASR40.CanTrcv224.1 */
            CanIf_CheckTrcvWakeFlagIndication
                (
                    CANTRCV_1_T03_CFG_GET_CHANNEL_CFG(Transceiver).CanIfTrcvId
                );
#endif /* #if ( CANTRCV_1_T03_CANIF_PN_CALLBACK_SUPPORT == STD_ON) */
            RetVal = E_OK;
        }
    }


    DBG_CANTRCV_1_T03_CHECKWAKEFLAG_EXIT(RetVal,Transceiver);
    return RetVal;
}

#endif /* CANTRCV_1_T03_PN_SUPPORT == STD_ON */

/* ----------------------------------------------------------------------------------------- */

/*==================[internal function definitions]==========================*/

STATIC FUNC( Std_ReturnType, CANTRCV_1_T03_CODE) CanTrcv_1_T03_InternalTrcvInit
(
    uint8 Transceiver,
    uint8 InitialMode,
    uint8 ServiceID
)
{
    /* Shall be initialized to E_OK for check mechanism */
    Std_ReturnType RetVal;
    /* Enable/disable Pn */
    uint8 selwup_bits = 0U;  /* default setting = no selective wakeup */

    /* Unlock all control register*/
    uint8 ubDataRegBuffer = UNLOCK_CONTROL_ALL;


    RetVal = CanTrcv_1_T03_AccessSpi( Transceiver,
                                      (CANTRCV_SPI_WRITE|LOCK_CONTROL_REGISTER_ADDR),
                                      &ubDataRegBuffer,
                                      ServiceID
                                    );

#if ( CANTRCV_1_T03_PN_SUPPORT == STD_ON )

    if (RetVal == E_OK)
    {
        if (TRUE == CANTRCV_1_T03_CFG_GET_CHANNEL_CFG(Transceiver).CanTrcvHwPnSupport)
        {
            /* Activate selective wakeup */
            selwup_bits = (uint8)(CANTRCV_1_T03_CAN_CTRL_CPNC | CANTRCV_1_T03_CAN_CTRL_PNCOK);
#if ( CANTRCV_1_T03_FD_TOLERANCE == STD_ON )
            /* Activate CAN-FD passive support */
            selwup_bits |= (uint8)CANTRCV_1_T03_CAN_CTRL_CFDC;
#endif /* CANTRCV_1_T03_FD_TOLERANCE == STD_ON */
            RetVal = CanTrcv_1_T03_InternalPnInit( Transceiver, ServiceID );
        }
    }
#endif /* CANTRCV_1_T03_PN_SUPPORT == STD_ON */

#if (CANTRCV_1_T03_GENERAL_WAKE_UP_SUPPORT != CANTRCV_1_T03_WAKEUP_NOT_SUPPORTED)
    if (RetVal == E_OK)
    {
        if (CANTRCV_1_T03_CFG_GET_CHANNEL_CFG(Transceiver).CanTrcvWakeupUsed == TRUE)
        {
            /* System register init */
            /* Transceiver event register init */
            /* Wake pin register init */
            RetVal = CanTrcv_1_T03_EventRegInit(Transceiver, ServiceID);
        }
    }
#endif /* CANTRCV_1_T03_GENERAL_WAKE_UP_SUPPORT != CANTRCV_1_T03_WAKEUP_NOT_SUPPORTED */

    if (RetVal == E_OK)
    {
        /* Now you can select the CMC mode and also configure CPNC and PNCOK
         *
         * According to the datasheet:
         * If selective wake-up is disabled (CPNC = 0) or partial networking is not configured
         * correctly (PNCOK = 0), and the CAN transceiver is in Offline mode with wake-up enabled
         * (CWE = 1), then any valid wake-up pattern (according to ISO 11898-5/-6) will trigger a
         * wake-up event.
         */
        /* Now you can select the CMC mode and also configure CPNC and PNCOK */
        ubDataRegBuffer = (uint8)
            (selwup_bits | CANTRCV_1_T03_CFG_GET_CHANNEL_CFG(Transceiver).CanTrcvModeSlct );
        RetVal = CanTrcv_1_T03_AccessSpi( Transceiver,
                                          (CANTRCV_SPI_WRITE|CAN_CTRL_REGISTER_ADDR),
                                          &ubDataRegBuffer,
                                          ServiceID
                                        );
    }


    if (RetVal == E_OK)
    {
        /* CanTrcv.ASR40.CanTrcv148 */
#if (CANTRCV_1_T03_OPERATION_MODE_API == STD_ON)

        RetVal = CanTrcv_1_T03_InternalSetOpMode( Transceiver, InitialMode, ServiceID );

#else /* CANTRCV_1_T03_OPERATION_MODE_API == STD_ON */

        /* Set the mode of the transceiver: MC bits (sleep, standby, normal) */
        if((uint8)CANTRCV_TRCVMODE_NORMAL == InitialMode)
        {
            ubDataRegBuffer = 0x07U;
        }
        /* CHECK: NOPARSE */
        else if((uint8)CANTRCV_TRCVMODE_STANDBY == InitialMode)
        {
            ubDataRegBuffer = 0x04U;
        }
        else
        {
            /* Value CANTRCV_TRCVMODE_SLEEP invalid.
             * API CanTrcv_SetOpMode can only be disabled if CanTrcvWakeUpSupport is disabled.
             */
            ;
        }
        /* CHECK: PARSE */

        RetVal = CanTrcv_1_T03_AccessSpi( Transceiver,
                                          (CANTRCV_SPI_WRITE|MODE_CONTROL_REGISTER_ADDR),
                                          &ubDataRegBuffer,
                                          ServiceID
                                        );

        CanTrcv_1_T03_TrcvState[Transceiver].CurrentMode = InitialMode;

#endif /* CANTRCV_1_T03_OPERATION_MODE_API == STD_ON */
    }

    if (RetVal == E_OK)
    {
        /* Lock all control register*/
        ubDataRegBuffer = LOCK_CONTROL_ALL;
        RetVal = CanTrcv_1_T03_AccessSpi( Transceiver,
                                          (CANTRCV_SPI_WRITE|LOCK_CONTROL_REGISTER_ADDR),
                                          &ubDataRegBuffer,
                                          ServiceID
                                        );
    }

    return RetVal;
}


#if ( CANTRCV_1_T03_PN_SUPPORT == STD_ON )
STATIC FUNC( Std_ReturnType, CANTRCV_1_T03_CODE) CanTrcv_1_T03_InternalPnInit
(
    uint8 Transceiver,
    uint8 ServiceID
)
{
    Std_ReturnType RetVal;
    /* Buffer managing data of transceiver registers */
    uint8 ubDataRegBuffer;
    /* Loop counter to initialize data mask register */
    uint8 ubDataMaskCnt = 8U;


    /* Baudrate init */
    ubDataRegBuffer = CANTRCV_1_T03_CFG_GET_CHANNEL_CFG(Transceiver).CanTrcvBaudRate;
    RetVal = CanTrcv_1_T03_AccessSpi( Transceiver,
                                      (CANTRCV_SPI_WRITE|DATA_RATE_REGISTER_ADDR),
                                      &ubDataRegBuffer,
                                      ServiceID
                                    );

    if (RetVal == E_OK)
    {
        /* ID and mask registers init */
        if(CANTRCV_1_T03_STANDARD_ID == CANTRCV_1_T03_CFG_GET_CHANNEL_CFG(Transceiver).CanTrcvPnCanIdIsExtended)
        {
            /* use a standard Can ID for selective wakeup */
            RetVal = CanTrcv_1_T03_StdIdRegInit( Transceiver, ServiceID );
        }
        else
        {
            /* use a extended Can ID for selective wakeup */
            RetVal = CanTrcv_1_T03_ExtIdRegInit( Transceiver, ServiceID );
            if (RetVal == E_OK)
            {
                RetVal = CanTrcv_1_T03_ExtIdMaskRegInit( Transceiver, ServiceID );
            }
        }
    }

    if (RetVal == E_OK)
    {
        /* IDE and DLC init */
        ubDataRegBuffer = (uint8)((uint8)(CANTRCV_1_T03_CFG_GET_CHANNEL_CFG(Transceiver).CanTrcvPnCanIdIsExtended << 7) |
                                  (uint8)((uint8)(CANTRCV_1_T03_CFG_GET_CHANNEL_CFG(Transceiver).CanTrcvPnFramePNDM << 6) |
                                          CANTRCV_1_T03_CFG_GET_CHANNEL_CFG(Transceiver).CanTrcvPnFrameDlc));

        RetVal = CanTrcv_1_T03_AccessSpi( Transceiver,
                                          (CANTRCV_SPI_WRITE|FRAME_CTRL_REGISTER_ADDR),
                                          &ubDataRegBuffer,
                                          ServiceID
                                        );
    }

    if (RetVal == E_OK)
    {
        /* Mask data init */
        /* All data will be initialize even if only a part is used. No use of DLC */
        /* Data mask 0 to 7 */
        do
        {
            ubDataMaskCnt--;
            ubDataRegBuffer = CANTRCV_1_T03_CFG_GET_CHANNEL_CFG(Transceiver).CanTrcvPnFrameDataMaskSpec[ubDataMaskCnt];
            RetVal = CanTrcv_1_T03_AccessSpi( Transceiver,
                                              CANTRCV_SPI_WRITE|(uint8)((DATA_MASK_REGISTER_0_ADDR_WITH_NO_SHIFT+(7U-ubDataMaskCnt)) << 1),
                                              &ubDataRegBuffer,
                                              ServiceID
                                            );

        }
        while ((0U < ubDataMaskCnt) && (RetVal == E_OK));
    }


    return RetVal;
} /* CanTrcv_1_T03_InternalPnInit */
#endif /* CANTRCV_1_T03_PN_SUPPORT == STD_ON */


#if ( CANTRCV_1_T03_PN_SUPPORT == STD_ON )
STATIC FUNC( Std_ReturnType, CANTRCV_1_T03_CODE) CanTrcv_1_T03_StdIdRegInit
(
    uint8 Transceiver,
    uint8 ServiceID
)
{
    Std_ReturnType RetVal;
    /* Buffer managing data of transceiver registers */
    uint8 ubDataRegBuffer;


    /* ID */
    ubDataRegBuffer = (uint8)(((CANTRCV_1_T03_CFG_GET_CHANNEL_CFG(Transceiver).CanTrcvPnFrameCanId) & STD_6_LSB_MASK ) << 2);
    RetVal = CanTrcv_1_T03_AccessSpi( Transceiver,
                                      (CANTRCV_SPI_WRITE|ID_REGISTER_2_ADDR),
                                      &ubDataRegBuffer,
                                      ServiceID
                                    );

    if (RetVal == E_OK)
    {
        ubDataRegBuffer = (uint8)(((CANTRCV_1_T03_CFG_GET_CHANNEL_CFG(Transceiver).CanTrcvPnFrameCanId) & STD_5_MSB_MASK) >> 6);
        RetVal = CanTrcv_1_T03_AccessSpi( Transceiver,
                                          (CANTRCV_SPI_WRITE|ID_REGISTER_3_ADDR),
                                          &ubDataRegBuffer,
                                          ServiceID
                                        );
    }

    /* Mask */
    if (RetVal == E_OK)
    {
        ubDataRegBuffer = (uint8)(((CANTRCV_1_T03_CFG_GET_CHANNEL_CFG(Transceiver).CanTrcvPnFrameCanIdMask) & STD_6_LSB_MASK ) << 2);
        RetVal = CanTrcv_1_T03_AccessSpi( Transceiver,
                                          (CANTRCV_SPI_WRITE|MASK_REGISTER_2_ADDR),
                                          &ubDataRegBuffer,
                                          ServiceID
                                        );
    }

    if (RetVal == E_OK)
    {
        ubDataRegBuffer = (uint8)(((CANTRCV_1_T03_CFG_GET_CHANNEL_CFG(Transceiver).CanTrcvPnFrameCanIdMask) & STD_5_MSB_MASK) >> 6);
        RetVal = CanTrcv_1_T03_AccessSpi( Transceiver,
                                          (CANTRCV_SPI_WRITE|MASK_REGISTER_3_ADDR),
                                          &ubDataRegBuffer,
                                          ServiceID
                                        );
    }


    return RetVal;
} /* CanTrcv_1_T03_StdIdRegInit */
#endif /* CANTRCV_1_T03_PN_SUPPORT == STD_ON */


#if ( CANTRCV_1_T03_PN_SUPPORT == STD_ON )
STATIC FUNC( Std_ReturnType, CANTRCV_1_T03_CODE) CanTrcv_1_T03_ExtIdRegInit
(
    uint8 Transceiver,
    uint8 ServiceID
)
{
    Std_ReturnType RetVal;
    /* Buffer managing data of transceiver registers */
    uint8 ubDataRegBuffer;


    /* ID */
    ubDataRegBuffer = (uint8)((CANTRCV_1_T03_CFG_GET_CHANNEL_CFG(Transceiver).CanTrcvPnFrameCanId) & EXT_BYTE_0_MASK);
    RetVal = CanTrcv_1_T03_AccessSpi( Transceiver,
                                      (CANTRCV_SPI_WRITE|ID_REGISTER_0_ADDR),
                                      &ubDataRegBuffer,
                                      ServiceID
                                    );

    if (RetVal == E_OK)
    {
        ubDataRegBuffer = (uint8)(((CANTRCV_1_T03_CFG_GET_CHANNEL_CFG(Transceiver).CanTrcvPnFrameCanId) >> 8) & EXT_BYTE_0_MASK);
        RetVal = CanTrcv_1_T03_AccessSpi( Transceiver,
                                          (CANTRCV_SPI_WRITE|ID_REGISTER_1_ADDR),
                                          &ubDataRegBuffer,
                                          ServiceID
                                        );
    }

    if (RetVal == E_OK)
    {
        ubDataRegBuffer = (uint8)(((CANTRCV_1_T03_CFG_GET_CHANNEL_CFG(Transceiver).CanTrcvPnFrameCanId) >> 16) & EXT_BYTE_0_MASK);
        RetVal = CanTrcv_1_T03_AccessSpi( Transceiver,
                                          (CANTRCV_SPI_WRITE|ID_REGISTER_2_ADDR),
                                          &ubDataRegBuffer,
                                          ServiceID
                                        );
    }

    if (RetVal == E_OK)
    {
        ubDataRegBuffer = (uint8)(((CANTRCV_1_T03_CFG_GET_CHANNEL_CFG(Transceiver).CanTrcvPnFrameCanId) >> 24) & EXT_BYTE_0_MASK);
        RetVal = CanTrcv_1_T03_AccessSpi( Transceiver,
                                          (CANTRCV_SPI_WRITE|ID_REGISTER_3_ADDR),
                                          &ubDataRegBuffer,
                                          ServiceID
                                        );
    }


    return RetVal;
} /* CanTrcv_1_T03_ExtIdRegInit */
#endif /* CANTRCV_1_T03_PN_SUPPORT == STD_ON */


#if ( CANTRCV_1_T03_PN_SUPPORT == STD_ON )
STATIC FUNC( Std_ReturnType, CANTRCV_1_T03_CODE) CanTrcv_1_T03_ExtIdMaskRegInit
(
    uint8 Transceiver,
    uint8 ServiceID
)
{
    Std_ReturnType RetVal;
    /* Buffer managing data of transceiver registers */
    uint8 ubDataRegBuffer;


    /* Mask */
    ubDataRegBuffer = (uint8)(CANTRCV_1_T03_CFG_GET_CHANNEL_CFG(Transceiver).CanTrcvPnFrameCanIdMask & EXT_BYTE_0_MASK);
    RetVal = CanTrcv_1_T03_AccessSpi( Transceiver,
                                      (CANTRCV_SPI_WRITE|MASK_REGISTER_0_ADDR),
                                      &ubDataRegBuffer,
                                      ServiceID
                                    );

    if (RetVal == E_OK)
    {
        ubDataRegBuffer = (uint8)(((CANTRCV_1_T03_CFG_GET_CHANNEL_CFG(Transceiver).CanTrcvPnFrameCanIdMask) >> 8) & EXT_BYTE_0_MASK);
        RetVal = CanTrcv_1_T03_AccessSpi( Transceiver,
                                          (CANTRCV_SPI_WRITE|MASK_REGISTER_1_ADDR),
                                          &ubDataRegBuffer,
                                          ServiceID
                                        );
    }

    if (RetVal == E_OK)
    {
        ubDataRegBuffer = (uint8)(((CANTRCV_1_T03_CFG_GET_CHANNEL_CFG(Transceiver).CanTrcvPnFrameCanIdMask) >> 16) & EXT_BYTE_0_MASK);
        RetVal = CanTrcv_1_T03_AccessSpi( Transceiver,
                                          (CANTRCV_SPI_WRITE|MASK_REGISTER_2_ADDR),
                                          &ubDataRegBuffer,
                                          ServiceID
                                        );
    }

    if (RetVal == E_OK)
    {
        ubDataRegBuffer = (uint8)(((CANTRCV_1_T03_CFG_GET_CHANNEL_CFG(Transceiver).CanTrcvPnFrameCanIdMask) >> 24) & EXT_BYTE_0_MASK);
        RetVal = CanTrcv_1_T03_AccessSpi( Transceiver,
                                          (CANTRCV_SPI_WRITE|MASK_REGISTER_3_ADDR),
                                          &ubDataRegBuffer,
                                          ServiceID
                                        );
    }


    return RetVal;
} /* CanTrcv_1_T03_ExtIdMaskRegInit */
#endif /* CANTRCV_1_T03_PN_SUPPORT == STD_ON */


#if (CANTRCV_1_T03_GENERAL_WAKE_UP_SUPPORT != CANTRCV_1_T03_WAKEUP_NOT_SUPPORTED)
STATIC FUNC( Std_ReturnType, CANTRCV_1_T03_CODE) CanTrcv_1_T03_EventRegInit
(
    uint8 Transceiver,
    uint8 ServiceID
)
{
    Std_ReturnType RetVal;
    /* Buffer managing data of transceiver registers */
    uint8 ubDataRegBuffer;


    /* System register init */
    ubDataRegBuffer = 0U;
    RetVal = CanTrcv_1_T03_AccessSpi( Transceiver,
                                      (CANTRCV_SPI_WRITE|SYST_EVENT_ENABLE_REGISTER_ADDR),
                                      &ubDataRegBuffer,
                                      ServiceID
                                    );

    if (RetVal == E_OK)
    {
        /* Transceiver register init */
        ubDataRegBuffer = (CANTRCV_1_T03_CFG_GET_CHANNEL_CFG(Transceiver).CanTrcvTransceiverEventReg &
                           (uint8)(CANTRCV_1_T03_TRANSCEIVER_ENABLE_CBSE |
                                   CANTRCV_1_T03_TRANSCEIVER_ENABLE_CFE  |
                                   CANTRCV_1_T03_TRANSCEIVER_ENABLE_CWE));
        RetVal = CanTrcv_1_T03_AccessSpi( Transceiver,
                                          (CANTRCV_SPI_WRITE|TRANSCEIVER_EVENT_EN_REGISTER_ADDR),
                                          &ubDataRegBuffer,
                                          ServiceID
                                        );
    }

    if (RetVal == E_OK)
    {
        /* Wake pin register init */
        ubDataRegBuffer = (CANTRCV_1_T03_CFG_GET_CHANNEL_CFG(Transceiver).CanTrcvWakePinReg &
                           (uint8)(CANTRCV_1_T03_WAKE_ENABLE_WPRE | CANTRCV_1_T03_WAKE_ENABLE_WPFE));
        RetVal = CanTrcv_1_T03_AccessSpi( Transceiver,
                                          (CANTRCV_SPI_WRITE|WAKEPIN_ENABLE_REGISTER_ADDR),
                                          &ubDataRegBuffer,
                                          ServiceID
                                        );
    }


    return RetVal;
} /* CanTrcv_1_T03_EventRegInit */
#endif /* CANTRCV_1_T03_GENERAL_WAKE_UP_SUPPORT != CANTRCV_1_T03_WAKEUP_NOT_SUPPORTED */


#if (CANTRCV_1_T03_OPERATION_MODE_API == STD_ON)
STATIC FUNC( Std_ReturnType, CANTRCV_1_T03_CODE ) CanTrcv_1_T03_InternalSetOpMode
(
    uint8 Transceiver,
    uint8 OpMode,
    uint8 ServiceID
)
{
    Std_ReturnType RetVal = E_NOT_OK;

    /* Buffer managing data of transceiver registers */
    uint8 ubDataRegBuffer;

    /* Store the current transceiver mode in a local variable */
    uint8 CurMode = CanTrcv_1_T03_TrcvState[Transceiver].CurrentMode;
    /* New Mode after transceiver mode switch takes place - initial set to current mode */
    uint8 NewMode = CurMode;


    /*
     * The T03 transceiver hardware variants knows following operating modes:
     *
     *    Transceiver Mode  |  Transition condition                           |
     *  -----------------------------------------------------------------------
     *    Off               | Vbat undervoltage event                         |
     *  -----------------------------------------------------------------------
     *    Normal            | MC = 111                                        |
     *  -----------------------------------------------------------------------
     *    Standby           | Power On                                     OR |
     *                      | MC = 001 && (WU pending || disable)          OR |
     *                      | MC = 001 && no WU pending && WU enable       OR |
     *                      | MC = 100                                     OR |
     *                      | No overtemp event                               |
     *  -----------------------------------------------------------------------
     *    Sleep             | MC = 001 && no WU pending && WU enable       OR |
     *                      | Vccor Vio undervoltage event from Stb/Normal    |
     *  -----------------------------------------------------------------------
     *    Overtemp          | Overtemperature event from Stb / Normal / Sleep |
     *  -----------------------------------------------------------------------
     *    (not used)        |                                                 |
     */

    if(OpMode == CurMode)
    {
      /* As such BSWM_C_056 and SWS_CanTrcv_00161 are satisfied */
      RetVal = E_OK;
    }
    /* Send SPI request to set register in right values to switch in the requested state*/
    /* CanTrcv.ASR40.CanTrcv102 */
    switch (OpMode)
    {

        /* ------------------ old state --> NORMAL --------------- */
        case CANTRCV_TRCVMODE_NORMAL:
        {
            /* STANDBY/power-on --> NORMAL */
            /* SLEEP --> NORMAL */
#if (CANTRCV_1_T03_GENERAL_WAKE_UP_SUPPORT != CANTRCV_1_T03_WAKEUP_NOT_SUPPORTED)
            if ((((uint8)CANTRCV_TRCVMODE_STANDBY == CurMode) || (CANTRCV_1_T03_NOT_ACTIVE == CanTrcv_1_T03_InitState))
                 || ((uint8)CANTRCV_TRCVMODE_SLEEP == CurMode))
#else
            if (((uint8)CANTRCV_TRCVMODE_STANDBY == CurMode) || (CANTRCV_1_T03_NOT_ACTIVE == CanTrcv_1_T03_InitState))
#endif /* CANTRCV_1_T03_GENERAL_WAKE_UP_SUPPORT != CANTRCV_1_T03_WAKEUP_NOT_SUPPORTED */
            {
                /* Send MC with 111 */
                ubDataRegBuffer = MC_CMD_NORMAL_MODE;
                RetVal = CanTrcv_1_T03_AccessSpi( Transceiver,
                                                  (CANTRCV_SPI_WRITE|MODE_CONTROL_REGISTER_ADDR),
                                                  &ubDataRegBuffer,
                                                  ServiceID
                                                );

                if(E_OK == RetVal)
                {
                    /* Unlock control register 2 */
                    ubDataRegBuffer = (uint8)(~LOCK_CONTROL_2);
                    RetVal = CanTrcv_1_T03_AccessSpi( Transceiver,
                                                      (CANTRCV_SPI_WRITE|LOCK_CONTROL_REGISTER_ADDR),
                                                      &ubDataRegBuffer,
                                                      ServiceID
                                                    );
                }

                if(E_OK == RetVal)
                {
                    /* Send CMC with 01 for active mode */
                    RetVal = CanTrcv_1_T03_AccessSpi( Transceiver,
                                                      (CANTRCV_SPI_READ|CAN_CTRL_REGISTER_ADDR),
                                                      &ubDataRegBuffer,
                                                      ServiceID
                                                    );
                }

                if(E_OK == RetVal)
                {
                    ubDataRegBuffer = ( ubDataRegBuffer &
                                       (uint8)(~CANTRCV_1_T03_CAN_CTRL_CMC) ) |  /* Erasing of CMC bits*/
                                      CANTRCV_1_T03_CAN_CTRL_CMC_ACTIVE_0;  /* Set CMC as Active */
                    RetVal = CanTrcv_1_T03_AccessSpi( Transceiver,
                                                      (CANTRCV_SPI_WRITE|CAN_CTRL_REGISTER_ADDR),
                                                      &ubDataRegBuffer,
                                                      ServiceID
                                                    );
                }

                /* Lock all control register*/
                if(E_OK == RetVal)
                {
                    ubDataRegBuffer = LOCK_CONTROL_ALL;
                    RetVal = CanTrcv_1_T03_AccessSpi( Transceiver,
                                                      (CANTRCV_SPI_WRITE|LOCK_CONTROL_REGISTER_ADDR),
                                                      &ubDataRegBuffer,
                                                      ServiceID
                                                    );
                }

#if (CANTRCV_1_T03_GENERAL_WAKE_UP_SUPPORT != CANTRCV_1_T03_WAKEUP_NOT_SUPPORTED)

                if ( ((uint8)CANTRCV_TRCVMODE_SLEEP == CurMode) ||
                     ((uint8)CANTRCV_TRCVMODE_STANDBY == CurMode) )
                {
                    /* Wakeup by internal trigger (EcuM request to normal).
                     * Note that a all wakeup reasons except power on have a higher priority
                     * when checking the wakeup source via CanTrcv_GetBusWuReason.
                     */
                    if (CanTrcv_1_T03_TrcvState[Transceiver].WakeupReason == CANTRCV_WU_POWER_ON)
                    {
                        CanTrcv_1_T03_TrcvState[Transceiver].WakeupReason = CANTRCV_WU_INTERNALLY;
                    }
                }
#endif /* CANTRCV_1_T03_GENERAL_WAKE_UP_SUPPORT != CANTRCV_1_T03_WAKEUP_NOT_SUPPORTED */
            }
            NewMode = (uint8)CANTRCV_TRCVMODE_NORMAL;
            break;
        }

        /* ------------------ old state --> STANDBY --------------- */
        case CANTRCV_TRCVMODE_STANDBY:
        {
            /* NORMAL/power-on --> STANDBY */
            /* CanTrcv.ASR40.CanTrcv103 */
            if (((uint8)CANTRCV_TRCVMODE_NORMAL == CurMode) || (CANTRCV_1_T03_NOT_ACTIVE == CanTrcv_1_T03_InitState))
            {
#if (CANTRCV_1_T03_GENERAL_WAKE_UP_SUPPORT != CANTRCV_1_T03_WAKEUP_NOT_SUPPORTED)
                /* Clear all events to be ready for a new wakeup */
                RetVal = CanTrcv_1_T03_ClearEvStatusReg( Transceiver,
                                                         ServiceID
                                                       );
                if(E_OK == RetVal)
#endif /* CANTRCV_1_T03_GENERAL_WAKE_UP_SUPPORT != CANTRCV_1_T03_WAKEUP_NOT_SUPPORTED */
                {
                    /* Send MC with 100 */
                    ubDataRegBuffer = MC_CMD_STANDBY_MODE;
                    RetVal = CanTrcv_1_T03_AccessSpi( Transceiver,
                                                      (CANTRCV_SPI_WRITE|MODE_CONTROL_REGISTER_ADDR),
                                                      &ubDataRegBuffer,
                                                      ServiceID
                                                    );
                }
            }
#if (CANTRCV_1_T03_GENERAL_WAKE_UP_SUPPORT != CANTRCV_1_T03_WAKEUP_NOT_SUPPORTED)
            if(E_OK == RetVal)
#endif /* CANTRCV_1_T03_GENERAL_WAKE_UP_SUPPORT != CANTRCV_1_T03_WAKEUP_NOT_SUPPORTED */
            {
                NewMode = (uint8)CANTRCV_TRCVMODE_STANDBY;
            }
            break;
        }

#if (CANTRCV_1_T03_GENERAL_WAKE_UP_SUPPORT != CANTRCV_1_T03_WAKEUP_NOT_SUPPORTED)

        /* ------------------ old state --> SLEEP --------------- */
        case CANTRCV_TRCVMODE_SLEEP:
        {
            /* STANDBY/power-on --> SLEEP */
            /* CanTrcv.ASR40.CanTrcv104 */
            if (((uint8)CANTRCV_TRCVMODE_STANDBY == CurMode) || (CANTRCV_1_T03_NOT_ACTIVE == CanTrcv_1_T03_InitState))
            {
                /* Check if at least one regular wake-up event is enabled
                 * If no wakeup event is enabled, a transition to SLEEP is denied.
                 * See also "Chapter 6.6.2 Sleep mode protection" of the TJA1145
                 */
                if ( (CANTRCV_1_T03_CFG_GET_CHANNEL_CFG(Transceiver).CanTrcvTransceiverEventReg != 0U) ||
                     (CANTRCV_1_T03_CFG_GET_CHANNEL_CFG(Transceiver).CanTrcvWakePinReg != 0U)
                   )
                {
                    /* Clear all events to be not lock into an internal mode
                     * See also "Chapter 6.6.2 Sleep mode protection" of the TJA1145
                     */
                    RetVal = CanTrcv_1_T03_ClearEvStatusReg( Transceiver,
                                                             ServiceID
                                                           );

                    if(E_OK == RetVal)
                    {
                        /* Send MC with 001 */
                        ubDataRegBuffer = MC_CMD_SLEEP_MODE;
                        RetVal = CanTrcv_1_T03_AccessSpi( Transceiver,
                                                          (CANTRCV_SPI_WRITE|MODE_CONTROL_REGISTER_ADDR),
                                                          &ubDataRegBuffer,
                                                          ServiceID
                                                        );
                    }
                }
                else
                {
                    /* CanTrcv.EB.NoRegularWupEvent */
                    RetVal = E_NOT_OK;
                }
            }
            else
            {
                /* CanTrcv.ASR40.CanTrcv161 */
                ; /* else: stay in SLEEP */
            }
            NewMode = (uint8)CANTRCV_TRCVMODE_SLEEP;
            break;
        }

#endif /* CANTRCV_1_T03_GENERAL_WAKE_UP_SUPPORT != CANTRCV_1_T03_WAKEUP_NOT_SUPPORTED */

        /* CHECK: NOPARSE */
        default:
        {
            /* CanTrcv.ASR40.CanTrcv105 */
            RetVal = E_NOT_OK;
            break;
        }
        /* CHECK: PARSE */
    }


    if(E_OK == RetVal)
    {
        /* set new transceiver operating mode as current mode */
        CanTrcv_1_T03_TrcvState[Transceiver].CurrentMode = NewMode;

#if (CANTRCV_1_T03_ICU_DRIVER_SUPPORT == STD_ON)
        /* Don't notify Icu driver from inside CanTrcv_Init function.
         * Icu driver might not be initialized at this point of time. */
        if (CANTRCV_1_T03_ACTIVE == CanTrcv_1_T03_InitState)
        {
            CanTrcv_1_T03_IcuDriverNotification(Transceiver, NewMode);
        }
#endif /* CANTRCV_1_T03_ICU_DRIVER_SUPPORT == STD_ON */
    }


    return RetVal;
}
#endif /* CANTRCV_1_T03_OPERATION_MODE_API == STD_ON */

#if (CANTRCV_1_T03_ICU_DRIVER_SUPPORT == STD_ON)
STATIC FUNC( void, CANTRCV_1_T03_CODE ) CanTrcv_1_T03_IcuDriverNotification
(
    uint8 Transceiver,
    uint8 NewMode
)
{
    uint16 IcuChannel = CANTRCV_1_T03_CFG_GET_CHANNEL_CFG(Transceiver).CanTrcvIcuChannel;


    /* Check if actual transceiver has a Icu configuration */
    if (CANTRCV_1_T03_INVALID_ICU_CHANNEL != IcuChannel)
    {
        if (CANTRCV_TRCVMODE_NORMAL == NewMode)
        {
            /* CanTrcv.ASR40.CanTrcv173.1 */
            Icu_DisableEdgeDetection(IcuChannel);
            /* CanTrcv.ASR40.CanTrcv173 */
            Icu_DisableNotification(IcuChannel);
        }
        else if (CANTRCV_TRCVMODE_STANDBY == NewMode)
        {
            /* CanTrcv.ASR40.CanTrcv172 */
            Icu_EnableNotification(IcuChannel);
            /* CanTrcv.ASR40.CanTrcv172.1 */
            Icu_EnableEdgeDetection(IcuChannel);
        }
        else
        {
            ; /* else: no notification */
        }
    }

} /* CanTrcv_1_T03_IcuDriverNotification */
#endif /* CANTRCV_1_T03_ICU_DRIVER_SUPPORT == STD_ON */

/** \brief This function allows to manage the maximum communication retries
 ** for CanTrcv_1_T03_SpiCommSyncTransmit (CanTrcv179_Conf)
 */
STATIC FUNC( Std_ReturnType, CANTRCV_1_T03_CODE ) CanTrcv_1_T03_SpiCommSyncTransmit
(
    Spi_SequenceType Sequence,
     uint8 SpiAccessSync
)
{
    Std_ReturnType retStatus;
#if ( CANTRCV_1_T03_SPI_COMM_RETRIES > 0)
    uint8 countRetries = 0U;
#endif /* CANTRCV_1_T03_SPI_COMM_RETRIES > 0 */
    Spi_SeqResultType seqResult;
    uint32 u32Timeout;
    u32Timeout = CANTRCV_1_T03_SPI_TIMEOUT_COUNTER;
#if ( CANTRCV_1_T03_SPI_COMM_RETRIES > 0)
    do
    {
        countRetries++;
#endif /* CANTRCV_1_T03_SPI_COMM_RETRIES > 0 */
        if(0U != SpiAccessSync)
        {
          retStatus = Spi_SyncTransmit(Sequence);
        }
        else
        {
          retStatus = Spi_AsyncTransmit(Sequence);
          if(E_OK == retStatus)
          {
            do
            {
              u32Timeout--;
              seqResult = Spi_GetSequenceResult(Sequence);
            } while ((SPI_SEQ_PENDING == seqResult) && (u32Timeout > 0U));
          }
          else
          {
            /*retry*/
          }
        }
#if ( CANTRCV_1_T03_SPI_COMM_RETRIES > 0)
    }
    while( (E_OK != retStatus) && (CANTRCV_1_T03_SPI_COMM_RETRIES >= countRetries) );
#endif /* CANTRCV_1_T03_SPI_COMM_RETRIES > 0 */

    return retStatus;
}



/** \brief This function allows to manage the maximum communication retries
 ** for CanTrcv_1_T03_SpiCommSyncTransmit (CanTrcv179_Conf)
 */
STATIC FUNC( Std_ReturnType, CANTRCV_1_T03_CODE ) CanTrcv_1_T03_SpiCommWriteIB
(
    Spi_ChannelType Channel,
    P2CONST(uint16, AUTOMATIC, AUTOMATIC) DataBufferPtr
)
{
    Std_ReturnType retStatus;

    /* Deviation MISRAC2012-1 */
    P2CONST(Spi_DataType, AUTOMATIC, AUTOMATIC) SpiDataPtr =
      (P2CONST(Spi_DataType, AUTOMATIC, AUTOMATIC)) DataBufferPtr;

    /* The Spi API makes it necessary to cast our data buffer of 16bit width
     * to an pointer of unknown size. Spi defines 8/16 or 32bit as Spi_DataType.
     * To avoid alignment violations the CanTrcv restricts Spi_DataType to
     * 8 or 16bit!
     */
    retStatus = Spi_WriteIB(Channel, SpiDataPtr);

    return retStatus;
}



/** \brief This function allows to manage the maximum communication retries
 ** for CanTrcv_1_T03_SpiCommReadIB (CanTrcv179_Conf)
 */
STATIC FUNC( Std_ReturnType, CANTRCV_1_T03_CODE ) CanTrcv_1_T03_SpiCommReadIB
(
    Spi_ChannelType Channel,
    P2VAR(uint16, AUTOMATIC, AUTOMATIC) DataBufferPtr
)
{
    Std_ReturnType retStatus;

    /* Deviation MISRAC2012-1 */
    P2VAR(Spi_DataType, AUTOMATIC, AUTOMATIC) SpiDataPtr =
      (P2VAR(Spi_DataType, AUTOMATIC, AUTOMATIC)) DataBufferPtr;

    /* The Spi API makes it necessary to cast our data buffer of 16bit width
     * to an pointer of unknown size. Spi defines 8/16 or 32bit as Spi_DataType.
     * To avoid alignment violations the CanTrcv restricts Spi_DataType to
     * 8 or 16bit!
     */
    retStatus = Spi_ReadIB(Channel, SpiDataPtr);

    return retStatus;
}


/** \brief This function manage the formatting for sending or
 ** writing into the transceiver
 *
 * Transceiver: Index of the transceiver
 * ubRegAccess: contain address and operation type (W / R)
 * ubData: data to write on the register
 *
 */
STATIC FUNC( Std_ReturnType, CANTRCV_1_T03_CODE ) CanTrcv_1_T03_AccessSpi
(
    uint8 Transceiver,
    uint8 ubRegAccess,
    P2VAR(uint8, AUTOMATIC, CANTRCV_1_T03_APPL_DATA) ubData,
    uint8 ServiceID
)
{
    Std_ReturnType retStatus = E_NOT_OK;

    uint16 uwDataBufferSet;

    /* Deviation MISRA-2 */
    uwDataBufferSet = (uint16) (((uint16)ubRegAccess << 8U) | ((uint16)*ubData));

    /* Read access*/
    if( (ubRegAccess & CANTRCV_SPI_READ) == CANTRCV_SPI_READ)
    {
        retStatus = CanTrcv_1_T03_SpiCommWriteIB
            (
                CANTRCV_1_T03_CFG_GET_CHANNEL_CFG(Transceiver).CanTrcvSpiChannel,
                &uwDataBufferSet
            );

        if(E_OK == retStatus)
        {
            retStatus = CanTrcv_1_T03_SpiCommSyncTransmit
                (
                    CANTRCV_1_T03_CFG_GET_CHANNEL_CFG(Transceiver).CanTrcvSpiSequence,
                    CANTRCV_1_T03_CFG_GET_CHANNEL_CFG(Transceiver).CanTrcvSpiAccess
                );

            if( E_OK == retStatus)
            {
                retStatus = CanTrcv_1_T03_SpiCommReadIB
                    (
                        CANTRCV_1_T03_CFG_GET_CHANNEL_CFG(Transceiver).CanTrcvSpiChannel,
                        &uwDataBufferSet
                    );

                if(E_OK == retStatus)
                {
                    /* Cast to keep only 8bits data register*/
                    *ubData = (uint8)(uwDataBufferSet & 0x00FFU);
                }
            }
        }
    }
    else
    {
        retStatus = CanTrcv_1_T03_SpiCommWriteIB
            (
                CANTRCV_1_T03_CFG_GET_CHANNEL_CFG(Transceiver).CanTrcvSpiChannel,
                &uwDataBufferSet
            );

        if( E_OK == retStatus)
        {
            retStatus = CanTrcv_1_T03_SpiCommSyncTransmit
                (
                    CANTRCV_1_T03_CFG_GET_CHANNEL_CFG(Transceiver).CanTrcvSpiSequence,
                    CANTRCV_1_T03_CFG_GET_CHANNEL_CFG(Transceiver).CanTrcvSpiAccess
                );
        }
    }

#if (CANTRCV_1_T03_DEV_ERROR_DETECT == STD_ON)
    if(retStatus != E_OK)
    {
        /* CanTrcv.ASR40.CanTrcv113 */
        CANTRCV_DET_ERROR(ServiceID, CANTRCV_1_T03_E_NO_TRCV_CONTROL);
    }
#else /* CANTRCV_1_T03_DEV_ERROR_DETECT == STD_ON */
    TS_PARAM_UNUSED(ServiceID);
#endif /* CANTRCV_1_T03_DEV_ERROR_DETECT == STD_ON */

    return retStatus;
}


#if (CANTRCV_1_T03_GENERAL_WAKE_UP_SUPPORT != CANTRCV_1_T03_WAKEUP_NOT_SUPPORTED)
/** \brief This function manage the clearing of event
 ** status registers
 *
 * Transceiver: Index of the transceiver
 *
 */
STATIC FUNC( Std_ReturnType, CANTRCV_1_T03_CODE ) CanTrcv_1_T03_ClearEvStatusReg
(
    uint8 Transceiver,
    uint8 ServiceID
)
{    /* Shall be initialized to E_OK for check mechanism */
    Std_ReturnType RetVal = E_NOT_OK;

    /* Buffer managing data of transceiver registers */
    uint8 ubDataRegBuffer;



    /* Clear all events to be not lock into an internal mode
     * See also "Chapter 6.6.2 Sleep mode protection" of the TJA1145
     */
    /* Clear System event register by setting 1 in each events */

    /* Clear system event status register by setting one in bits */
    ubDataRegBuffer = CANTRCV_1_T03_SYSTEM_EVENT_STATUS_MASK;
    RetVal = CanTrcv_1_T03_AccessSpi( Transceiver,
                                      (CANTRCV_SPI_WRITE|SYSTEM_EVENT_STATUS_REGISTER_ADDR),
                                      &ubDataRegBuffer,
                                      ServiceID
                                    );

    if(E_OK == RetVal)
    {
        /* Clear transceiver event status register by setting one in bits */
        ubDataRegBuffer = CANTRCV_1_T03_TRANSCEIVER_EVENT_STATUS_MASK;
        RetVal = CanTrcv_1_T03_AccessSpi( Transceiver,
                                          (CANTRCV_SPI_WRITE|TRCV_EVENT_STATUS_REGISTER_ADDR),
                                          &ubDataRegBuffer,
                                          ServiceID
                                        );
    }

    if(E_OK == RetVal)
    {
        /* Clear wake pin event status register by setting one in bits */
        ubDataRegBuffer = CANTRCV_1_T03_WAKE_PIN_EVENT_STATUS_MASK;
        RetVal = CanTrcv_1_T03_AccessSpi( Transceiver,
                                          (CANTRCV_SPI_WRITE|WAKE_EVENT_STATUS_REGISTER_ADDR),
                                          &ubDataRegBuffer,
                                          ServiceID
                                        );
    }

    if(E_OK == RetVal)
    {
        /* Clear global event status register by setting one in bits */
        ubDataRegBuffer = CANTRCV_1_T03_GLOBAL_EVENT_STATUS_MASK;
        RetVal = CanTrcv_1_T03_AccessSpi( Transceiver,
                                          (CANTRCV_SPI_WRITE|GLOBAL_EVENT_STATUS_REGISTER_ADDR),
                                          &ubDataRegBuffer,
                                          ServiceID
                                         );
    }

    if(E_OK == RetVal)
    {
        /* CanTrcv.ASR40.CanTrcv094 */
        /* clear internally stored wakeup events */
        CanTrcv_1_T03_TrcvState[Transceiver].WakeupSource = 0U;
        /* set back wakeup reason */
        CanTrcv_1_T03_TrcvState[Transceiver].WakeupReason = CANTRCV_WU_POWER_ON;
    }

    return RetVal;
}
#endif /* CANTRCV_1_T03_GENERAL_WAKE_UP_SUPPORT != CANTRCV_1_T03_WAKEUP_NOT_SUPPORTED */

#if (CANTRCV_1_T03_GENERAL_WAKE_UP_SUPPORT != CANTRCV_1_T03_WAKEUP_NOT_SUPPORTED)
STATIC FUNC( Std_ReturnType, CANTRCV_1_T03_CODE ) CanTrcv_1_T03_CheckAndReportWakeup
(
    uint8 Transceiver,
    uint8 ServiceID
)
{
    Std_ReturnType WakeupReported = E_NOT_OK;

    /* Use invalid value as default for the wakeup source ID */
    uint8 CanIfTrcvWUSourceId = CANTRCV_1_T03_INVALID_WAKEUP_SOURCE;

    /* Wakeup mask */
    uint32 CanIfTrcvWUSourceMask;


    /* get wakeup status from status register of transceiver hardware */
    if (CANTRCV_1_T03_CFG_GET_CHANNEL_CFG(Transceiver).CanTrcvWakeupUsed == TRUE)
    {
        Std_ReturnType SpiStatus = E_OK;

        /* Buffer managing data of transceiver registers */
        uint8 ubDataRegBuffer_TrcvEvent = 0x0U;
        uint8 ubDataRegBuffer_WakeEvent = 0x0U;

        if(CanTrcv_1_T03_AccessSpi( Transceiver,
                                  (CANTRCV_SPI_READ|TRCV_EVENT_STATUS_REGISTER_ADDR),
                                   &ubDataRegBuffer_TrcvEvent,
                                   ServiceID) != E_OK)
        {
            SpiStatus = E_NOT_OK;
        }
        else if(CanTrcv_1_T03_AccessSpi( Transceiver,
                                        (CANTRCV_SPI_READ|WAKE_EVENT_STATUS_REGISTER_ADDR),
                                         &ubDataRegBuffer_WakeEvent,
                                         ServiceID) != E_OK)
        {
            SpiStatus = E_NOT_OK;
        }
        else
        {
          /* nothing to do here */
        }

        if(E_OK == SpiStatus)
        {
            if( CANTRCV_1_T03_TRANSCEIVER_EVENT_STATUS_CW == (ubDataRegBuffer_TrcvEvent & CANTRCV_1_T03_TRANSCEIVER_EVENT_STATUS_CW) )
            {
                CanTrcv_1_T03_TrcvState[Transceiver].WakeupReason = CANTRCV_WU_BY_BUS;
                CanIfTrcvWUSourceId = CANTRCV_1_T03_CFG_GET_CHANNEL_CFG(Transceiver).CanTrcvByBusWakeupSourceRef;
            }
            else if( (CANTRCV_1_T03_WAKE_PIN_EVENT_STATUS_WPF == (ubDataRegBuffer_WakeEvent & CANTRCV_1_T03_WAKE_PIN_EVENT_STATUS_WPF)) ||
                (CANTRCV_1_T03_WAKE_PIN_EVENT_STATUS_WPR == (ubDataRegBuffer_WakeEvent & CANTRCV_1_T03_WAKE_PIN_EVENT_STATUS_WPR)) )
            {
                CanTrcv_1_T03_TrcvState[Transceiver].WakeupReason = CANTRCV_WU_BY_PIN;
                CanIfTrcvWUSourceId = CANTRCV_1_T03_CFG_GET_CHANNEL_CFG(Transceiver).CanTrcvByPinWakeupSourceRef;
            }
            else if( (CANTRCV_1_T03_TRANSCEIVER_EVENT_STATUS_PNFDE == (ubDataRegBuffer_TrcvEvent & CANTRCV_1_T03_TRANSCEIVER_EVENT_STATUS_PNFDE)) ||
                (CANTRCV_1_T03_TRANSCEIVER_EVENT_STATUS_CF == (ubDataRegBuffer_TrcvEvent & CANTRCV_1_T03_TRANSCEIVER_EVENT_STATUS_CF)) )
            {
                CanTrcv_1_T03_TrcvState[Transceiver].WakeupReason = CANTRCV_WU_BY_SYSERR;
                CanIfTrcvWUSourceId = CANTRCV_1_T03_CFG_GET_CHANNEL_CFG(Transceiver).CanTrcvSyserrWakeupSourceRef;
            }
            else
            {
                if(CanTrcv_1_T03_TrcvState[Transceiver].WakeupReason != CANTRCV_WU_INTERNALLY)
                {
                    CanTrcv_1_T03_TrcvState[Transceiver].WakeupReason = CANTRCV_WU_POWER_ON;
                }
            }
        }
        else
        {
            CanTrcv_1_T03_TrcvState[Transceiver].WakeupReason = CANTRCV_WU_ERROR;
        }
    }
    else
    {
        CanTrcv_1_T03_TrcvState[Transceiver].WakeupReason = CANTRCV_WU_NOT_SUPPORTED;
    }

    /* check if there is a wakeup status */
    if (CanIfTrcvWUSourceId != CANTRCV_1_T03_INVALID_WAKEUP_SOURCE)
    {
        /* Wakeup detected by transceiver hardware, take the configured ID and build the mask */
        CanIfTrcvWUSourceMask = ((uint32)1U) << CanIfTrcvWUSourceId;
    }
    else
    {
        /* No wakeup detected, take the internally stored value (could be also 0)  */
        CanIfTrcvWUSourceMask = CanTrcv_1_T03_TrcvState[Transceiver].WakeupSource;
    }

    /* Only report wakeup if there was:
     * 1.) a wakeup event read from the status register of the hardware or
     * 2.) an internally stored wakeup event. */
    if (CanIfTrcvWUSourceMask != 0U)
    {
        /* Only report wakeup if wakeup mode is set to WUMODE_ENABLE! */
        if (CanTrcv_1_T03_TrcvState[Transceiver].WakeupModeEnabled)
        {
            /* CanTrcv.EB.CanTrcv_CheckWakeup: deviation to fulfill SWS EcuM specification
             * indicate wakeup reason to EcuM */
            EcuM_SetWakeupEvent(CanIfTrcvWUSourceMask);

            /* CanTrcv.ASR40.CanTrcv146 */
            WakeupReported = E_OK;
        }
        else
        {
            /* If mode is WUMOODE_DISABLE then store the wakeup event internally. */
            CanTrcv_1_T03_TrcvState[Transceiver].WakeupSource = CanIfTrcvWUSourceMask;
        }
    }


    return WakeupReported;
}
#endif /* CANTRCV_1_T03_GENERAL_WAKE_UP_SUPPORT != CANTRCV_1_T03_WAKEUP_NOT_SUPPORTED */


#define CANTRCV_1_T03_STOP_SEC_CODE
#include <CanTrcv_1_T03_MemMap.h>

/*==================[end of file]============================================*/
