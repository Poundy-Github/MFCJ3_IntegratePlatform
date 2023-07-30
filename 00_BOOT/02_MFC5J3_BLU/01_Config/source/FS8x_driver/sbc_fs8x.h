/*
 * Copyright (c) 2016 - 2018, NXP Semiconductors, Inc.
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
 *
 * o Redistributions of source code must retain the above copyright notice, this list
 *   of conditions and the following disclaimer.
 *
 * o Redistributions in binary form must reproduce the above copyright notice, this
 *   list of conditions and the following disclaimer in the documentation and/or
 *   other materials provided with the distribution.
 *
 * o Neither the name of the copyright holder nor the names of its
 *   contributors may be used to endorse or promote products derived from this
 *   software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR
 * ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON
 * ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

/** @file sbc_fs8x.h
 * @brief FS8x driver interface.
 *
 * @author nxf44615
 * @version 1.1
 * @date 9-Oct-2018
 * @copyright Copyright (c) 2016 - 2018, NXP Semiconductors, Inc.
 */

#ifndef SBC_FS8X_H_
#define SBC_FS8X_H_

/*******************************************************************************
 * Includes
 ******************************************************************************/

#include <stdbool.h>
#include "sbc_fs8x_map.h"
#include "sbc_fs8x_common.h"

/*******************************************************************************
 * Definitions
 ******************************************************************************/
/** @brief Watchdog seed default value. */
#define FS8x_WD_SEED_DEFAULT 0x5AB2U

/** @addtogroup EnumsDefs
 * @{ */
/** @brief Voltage outputs. Can be used with function @ref FS8x_SetRegulatorState(). */
typedef enum
{
    fs8xBuck1 = 4,  /**< BUCK1 */
    fs8xBuck2 = 3,  /**< BUCK2 */
    fs8xBuck3 = 2,  /**< BUCK3 */
    fs8xLdo1 = 1,   /**< LDO1 */
    fs8xLdo2 = 0,   /**< LDO2 */
    fs8xVBoost = 5, /**< VBOOST */
    fs8xVPre = 6    /**< VPRE */
} fs8x_reg_output_t;

/** AMUX channel selection. Can be used with function @ref FS8x_SwitchAMUXchannel(). */
typedef enum
{
    fs8xAmuxGnd = FS8X_M_AMUX_GND,                                  /**< GND */
    fs8xAmuxVddio = FS8X_M_AMUX_VDDIO,                              /**< VDDIO */
    fs8xAmuxTempSensor = FS8X_M_AMUX_TEMPERATURE_SENSOR,            /**< Temperature sensor */
    fs8xAmuxBandgapMain = FS8X_M_AMUX_BAND_GAP_MAIN,                /**< Main Bandgap */
    fs8xAmuxBandgapFailSafe = FS8X_M_AMUX_BAND_GAP_FAIL_SAFE,       /**< Fail-safe bandgap */
    fs8xAmuxVbuck1Volt = FS8X_M_AMUX_VBUCK1_VOLTAGE,                /**< BUCK1 */
    fs8xAmuxVbuck2Volt = FS8X_M_AMUX_VBUCK2_VOLTAGE,                /**< BUCK2 */
    fs8xAmuxVbuck3VoltDiv2_5 = FS8X_M_AMUX_VBUCK3_VOLTAGE_DIVIDED,  /**< BUCK3 divided by 2.5 */
    fs8xAmuxVpreVoltDiv2_5 = FS8X_M_AMUX_VPRE_VOLTAGE_DIVIDED,      /**< VPRE divided by 2.5 */
    fs8xAmuxVboostVoltDiv2_5 = FS8X_M_AMUX_VBOOST_VOLTAGE_DIVIDED,  /**< VBOOST divided by 2.5 */
    fs8xAmuxVldo1VoltDiv2_5 = FS8X_M_AMUX_VLDO1_VOLTAGE_DIVIDED,    /**< VLDO1 divided by 2.5 */
    fs8xAmuxVldo2VoltDiv2_5 = FS8X_M_AMUX_VLDO2_VOLTAGE_DIVIDED,    /**< VLDO2 divided by 2.5 */
    fs8xAmuxVbosVoltDiv2_5 = FS8X_M_AMUX_VBOS_VOLTAGE_DIVIDED,      /**< VBOS divided by 2.5 */
    fs8xAmuxVsup1VoltDiv7_5 = FS8X_M_AMUX_VSUP1_VOLTAGE_DIVIDED,    /**< VSUP1 divided by 7.5 */
    fs8xAmuxWake1VoltDiv7_5 = FS8X_M_AMUX_WAKE1_VOLTAGE_DIVIDED,    /**< WAKE1 divided by 7.5 */
    fs8xAmuxWake2VoltDiv7_5 = FS8X_M_AMUX_WAKE2_VOLTAGE_DIVIDED,    /**< WAKE2 divided by 7.5 */
    fs8xAmuxVana = FS8X_M_AMUX_VANA,                                /**< Vana */
    fs8xAmuxVdig = FS8X_M_AMUX_VDIG,                                /**< Vdig */
    fs8xAmuxVdigFs = FS8X_M_AMUX_VDIG_FS,                           /**< Vdig_fs */
    fs8xAmuxPsync = FS8X_M_AMUX_PSYNC_VOLTAGE,                      /**< PSYNC */
    fs8xAmuxVsup1VoltDiv14 = FS8X_M_RATIO_RATIO_14 | FS8X_M_AMUX_VSUP1_VOLTAGE_DIVIDED, /**< VSUP1 divided by 14 */
    fs8xAmuxWake1VoltDiv14 = FS8X_M_RATIO_RATIO_14 | FS8X_M_AMUX_WAKE1_VOLTAGE_DIVIDED, /**< WAKE1 divided by 14 */
    fs8xAmuxWake2VoltDiv14 = FS8X_M_RATIO_RATIO_14 | FS8X_M_AMUX_WAKE2_VOLTAGE_DIVIDED  /**< WAKE2 divided by 14 */
} fs8x_amux_selection_t;
/** @} */

//add for FS85
typedef enum
{
    /* Generic error codes */
    STATUS_SUCCESS                         = 0x000U,    /*!< Generic operation success status */
    STATUS_ERROR                           = 0x001U,    /*!< Generic operation failure status */
    STATUS_BUSY                            = 0x002U,    /*!< Generic operation busy status */
    STATUS_TIMEOUT                         = 0x003U,    /*!< Generic operation timeout status */
    STATUS_UNSUPPORTED                     = 0x004U,    /*!< Generic operation unsupported status */
    /* MCU specific error codes */
    STATUS_MCU_GATED_OFF                   = 0x100U,  /*!< Module is gated off */
    STATUS_MCU_TRANSITION_FAILED           = 0x101U,  /*!< Error occurs during transition. */
    STATUS_MCU_INVALID_STATE               = 0x102U,  /*!< Unsupported in current state. */
    STATUS_MCU_NOTIFY_BEFORE_ERROR         = 0x103U,  /*!< Error occurs during send "BEFORE" notification. */
    STATUS_MCU_NOTIFY_AFTER_ERROR          = 0x104U,  /*!< Error occurs during send "AFTER" notification. */
    /* I2C specific error codes */
    STATUS_I2C_RECEIVED_NACK               = 0x200U,  /*!< NACK signal received  */
    STATUS_I2C_TX_UNDERRUN                 = 0x201U,  /*!< TX underrun error */
    STATUS_I2C_RX_OVERRUN                  = 0x202U,  /*!< RX overrun error */
    STATUS_I2C_ARBITRATION_LOST            = 0x203U,  /*!< Arbitration lost */
    STATUS_I2C_ABORTED                     = 0x204U,  /*!< A transfer was aborted */
    STATUS_I2C_BUS_BUSY                    = 0x205U,  /*!< I2C bus is busy, cannot start transfer */
    /* CAN specific error codes */
    STATUS_CAN_BUFF_OUT_OF_RANGE           = 0x300U,  /*!< The specified MB index is out of the configurable range */
    STATUS_CAN_NO_TRANSFER_IN_PROGRESS     = 0x301U,  /*!< There is no transmission or reception in progress */
    /* Security specific error codes */
    STATUS_SEC_SEQUENCE_ERROR              = 0x402U,  /*!< The sequence of commands or subcommands is out of
                                                            sequence */
    STATUS_SEC_KEY_NOT_AVAILABLE           = 0x403U,  /*!< A key is locked due to failed boot measurement or
                                                            an active debugger */
    STATUS_SEC_KEY_INVALID                 = 0x404U,  /*!< A function is called to perform an operation with
                                                            a key that is not allowed for the given operation */
    STATUS_SEC_KEY_EMPTY                   = 0x405U,  /*!< Attempt to use a key that has not been initialized yet */
    STATUS_SEC_NO_SECURE_BOOT              = 0x406U,  /*!< The conditions for a secure boot process are not met */
    STATUS_SEC_KEY_WRITE_PROTECTED         = 0x407U,  /*!< Request for updating a write protected key slot,
                                                            or activating debugger with write protected key(s) */
    STATUS_SEC_KEY_UPDATE_ERROR            = 0x408U,  /*!< Key update did not succeed due to errors in
                                                            verification of the messages */
    STATUS_SEC_RNG_SEED                    = 0x409U,  /*!< Returned by CMD_RND and CMD_DEBUG if the seed has not
                                                            been initialized before */
    STATUS_SEC_NO_DEBUGGING                = 0x40AU,  /*!< DEBUG command authentication failed */
    STATUS_SEC_MEMORY_FAILURE              = 0x40CU,  /*!< General memory technology failure
                                                            (multibit ECC error, common fault detected) */
    STATUS_SEC_HSM_INTERNAL_MEMORY_ERROR   = 0x410U,  /*!< An internal memory error encountered while
                                                           executing the command */
    STATUS_SEC_INVALID_COMMAND             = 0x411U,  /*!< Command value out of range */
    STATUS_SEC_TRNG_ERROR                  = 0x412U,  /*!< One or more statistical tests run on the TRNG output failed */
    STATUS_SEC_HSM_FLASH_BLOCK_ERROR       = 0x413U,  /*!< Error reading, programming or erasing one of the HSM flash blocks */
    STATUS_SEC_INTERNAL_CMD_ERROR          = 0x414U,  /*!< An internal command processor error while executing a command */
    STATUS_SEC_MAC_LENGTH_ERROR            = 0x415U,  /*!< MAC/Message length out of range */
    STATUS_SEC_INVALID_ARG                 = 0x421U,  /*!< Invalid command argument */
    STATUS_SEC_TRNG_CLOCK_ERROR            = 0x423U,  /*!< TRNG not provided with a stable clock */
    /* SPI specific error codes */
    STATUS_SPI_TX_UNDERRUN                 = 0x500U,  /*!< TX underrun error */
    STATUS_SPI_RX_OVERRUN                  = 0x501U,  /*!< RX overrun error */
    STATUS_SPI_ABORTED                     = 0x502U,  /*!< A transfer was aborted */
    /* UART specific error codes */
    STATUS_UART_TX_UNDERRUN                = 0x600U,  /*!< TX underrun error */
    STATUS_UART_RX_OVERRUN                 = 0x601U,  /*!< RX overrun error */
    STATUS_UART_ABORTED                    = 0x602U,  /*!< A transfer was aborted */
    /* I2S specific error codes */
    STATUS_I2S_TX_UNDERRUN                 = 0x700U,  /*!< TX underrun error */
    STATUS_I2S_RX_OVERRUN                  = 0x701U,  /*!< RX overrun error */
    STATUS_I2S_ABORTED                     = 0x702U,  /*!< A transfer was aborted */
    /* SBC specific error codes */
    SBC_NVN_ERROR                          = 0x800U, /*!< Unsuccessful attempt writing to non volatile memory
                                                          (0x73 and 0x74). Set device to factory settings. */
    SBC_COMM_ERROR                         = 0x801U, /*!< Data transfer was aborted */
    SBC_CMD_ERROR                          = 0x802U, /*!< Wrong command. */
    SBC_ERR_NA                             = 0x803U, /*!< Feature/device not available */
    SBC_MTPNV_LOCKED                       = 0x804U, /*!< Unable to write MTPNV cells, NVMPS = 0 */

    /* FLASH specific error codes */
    STATUS_FLASH_ERROR_ENABLE              = 0x901U, /*!< It's impossible to enable an operation */
    STATUS_FLASH_ERROR_NO_BLOCK            = 0x902U, /*!< No blocks have been enabled for Array Integrity check */
    STATUS_FLASH_INPROGRESS                = 0x903U, /*!< InProgress status */

    /* SAI specific error codes */
    STATUS_SAI_ABORTED                     = 0xA00U, /*!< SAI aborted status */

    /* ENET specific error codes */
    STATUS_ENET_RX_QUEUE_EMPTY             = 0xA01U, /*!< There is no available frame in the receive queue */
    STATUS_ENET_TX_QUEUE_FULL              = 0xA02U, /*!< There is no available space for the frame in the transmit queue */
    STATUS_ENET_BUFF_NOT_FOUND             = 0xA03U, /*!< The specified buffer was not found in the queue */

    /* FCCU specific error codes */
    STATUS_FCCU_ERROR_CONFIG_TIMEOUT       = 0xB01U, /*!< FCCU triggers TimeOut when try to enter in Config State */
    STATUS_FCCU_ERROR_INIT_FCCU            = 0xB02U, /*!< FCCU Initializing FCCU Module */
    STATUS_FCCU_ERROR_SET_CONFIG           = 0xB03U, /*!< FCCU Fail to Enter in Config Mode  */
    STATUS_FCCU_ERROR_SET_NORMAL           = 0xB04U, /*!< FCCU Fail to Enter in Normal Mode  */
    STATUS_FCCU_ERROR_APPLY_NCF_CONFIG     = 0xB05U, /*!< FCCU Fail to set NoCritical Faults  */
    STATUS_FCCU_ERROR_UPDATE_FREEZE        = 0xB06U, /*!< FCCU Fail to update Freez Status registers */
    STATUS_FCCU_ERROR_CLEAR_FREEZE         = 0xB07U, /*!< FCCU Fail to Clear Freez Status registers */
    STATUS_FCCU_ERROR_SET_EOUT             = 0xB08U, /*!< FCCU Fail to Set Eout Configuration */
    STATUS_FCCU_ERROR_FAULT_DETECTED       = 0xB09U, /*!< FCCU Faults Detected */
    STATUS_FCCU_ERROR_OTHER                = 0xB0AU, /*!< FCCU other Error */

    /* EMIOS specific error codes */
    STATUS_EMIOS_WRONG_MODE                = 0xC00U,   /*!< EMIOS unsuccessful attempt selecting wrong mode. */
    STATUS_EMIOS_CNT_BUS_OVERFLOW          = 0xC01U,   /*!< EMIOS counter bus overflow. */
    STATUS_EMIOS_WRONG_CNT_BUS             = 0xC02U,   /*!< EMIOS unsuccessful attempt selecting wrong counter bus. */
    STATUS_EMIOS_ENABLE_GLOBAL_FRZ         = 0xC03U,   /*!< EMIOS must set global allow enter debug mode first. */

    /* EEE specific error codes */
    STATUS_EEE_ERROR_NO_ENOUGH_SPACE       = 0xD00U, /*!< The data is too big to fit in any of the block */
    STATUS_EEE_ERROR_NO_ENOUGH_BLOCK       = 0xD01U, /*!< The block numbers is not enough for round robin */
    STATUS_EEE_ERROR_DATA_NOT_FOUND        = 0xD02U, /*!< The required data is not found in the EEPROM emulation */
    STATUS_EEE_ERROR_NOT_IN_CACHE          = 0xD03U, /*!< The required data is not in the cache table */
    STATUS_EEE_ERROR_PROGRAM_INDICATOR     = 0xD04U, /*!< Failed to make block indicator to non-blank for several times */
    STATUS_EEE_HVOP_INPROGRESS             = 0xD05U, /*!< The high voltage operation is in progress */

    /* uSDHC specific error codes */
    STATUS_USDHC_OUT_OF_RANGE              = 0xE00U,    /*!< The size of data to be sent is larger than maximum size of ADMA table */
    STATUS_USDHC_PREPARE_ADMA_FAILED       = 0xE01U,    /*!< Failed to prepare the ADMA table */

    /* TDM specific error codes */
    STATUS_TDM_DIARY_FULL                  = 0xF01U, /*!< No empty flash left in diary region */

    /* PHY specific error codes */
    STATUS_PHY_ACCESS_FAILED               = 0x1001U, /*!< Could not access PHY registers */
    STATUS_PHY_INCOMPATIBLE_DEVICE         = 0x1002U  /*!< The selected PHY driver is not compatible with the device */
} status_t;
//add for FS85
/*******************************************************************************
 * Global Variables
 ******************************************************************************/

/*******************************************************************************
 * API
 ******************************************************************************/
/** @defgroup API Driver API
 * @{ */
/** @brief Changes seed of LFSR used for watchdog.
 *
 * The watchdog seed can be changed just during the INIT_FS phase (for challenger WD)
 * or during the OPEN watchdog window (for simple WD). Timing is up to the application!
 * @param [in] drvData  Driver run-time data.
 * @param [in] wdSeed   Watchdog LFSR seed.
 * @return @ref fs8x_status_t "Status return code." */
fs8x_status_t FS8x_WD_ChangeSeed(fs8x_drv_data_t* drvData, uint16_t wdSeed);

/** @brief Performs the watchdog refresh.
 * @param [in]  drvData     Driver run-time data.
 * @return @ref fs8x_status_t "Status return code." */
fs8x_status_t FS8x_WD_Refresh(fs8x_drv_data_t* drvData);

/** @brief FS0B release routine.
 *
 * This function also checks all preconditions before
 * it sends the register write command (LBIST_OK = ABIST1_OK = ABIST2_OK = 1,
 * Fault Error Counter = 0). If any precondition is not met, the function returns
 * @ref fs8xStatusError.
 * @param [in] drvData      Driver run-time data.
 * @return @ref fs8x_status_t "Status return code." */
fs8x_status_t FS8x_FS0B_Release(fs8x_drv_data_t* drvData);

/** @brief Switches a desired channel to the AMUX pin.
 * @param [in] drvData           Driver run-time data.
 * @param [in] channelSelection  Selected channel to be delivered to AMUX pin.
 * @return @ref fs8x_status_t "Status return code." */
fs8x_status_t FS8x_SwitchAMUXchannel(fs8x_drv_data_t* drvData, fs8x_amux_selection_t channelSelection);

/** @brief Sets state (enable/disable) of the selected voltage regulator.
 * @param [in] drvData  Driver run-time data.
 * @param [in] vreg     Voltage regulator enum (LDO1-2, BUCK1-3, BOOST, VPRE).
 * @param [in] enable   State (enable = true / disable = false).
 * @return @ref fs8x_status_t "Status return code." */
fs8x_status_t FS8x_SetRegulatorState(fs8x_drv_data_t* drvData, fs8x_reg_output_t vreg, bool enable);

/** @brief Reads actual Fault Error Counter value.
 * @param [in]  drvData                 Driver run-time data.
 * @param [out] faultErrorCounterValue  Fault Error counter value storage.
 * @return @ref fs8x_status_t "Status return code." */
fs8x_status_t FS8x_GetFaultErrorCounterValue(fs8x_drv_data_t* drvData, uint8_t* faultErrorCounterValue);

void Pmic_FS8435_Diagnostic(fs8x_drv_data_t* drvData);
fs8x_status_t GOTO_INITFS(fs8x_drv_data_t* drvData);
fs8x_status_t Disable_WD(fs8x_drv_data_t* drvData);
fs8x_status_t sbcInitStart(fs8x_drv_data_t* drvData);
status_t sbcInitClose(fs8x_drv_data_t* drvData);
void loadDefaultDriverConfig(fs8x_drv_data_t* drvData);
/** @} */
#endif /* SBC_FS8X_H_ */
