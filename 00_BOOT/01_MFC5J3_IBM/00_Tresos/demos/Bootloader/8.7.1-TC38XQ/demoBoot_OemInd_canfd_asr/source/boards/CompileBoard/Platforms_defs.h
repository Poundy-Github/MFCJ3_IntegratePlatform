/**
 * \file
 *
 * \brief AUTOSAR Demo
 *
 * This file contains the implementation of the AUTOSAR
 * module Demo.
 *
 * \author Elektrobit Automotive GmbH, 91058 Erlangen, Germany
 *
 * Copyright 2005 - 2019 Elektrobit Automotive GmbH
 * All rights exclusively reserved for Elektrobit Automotive GmbH,
 * unless expressly agreed to otherwise.
 */

#ifndef _PLATFORMS_DEFS_H_
#define _PLATFORMS_DEFS_H_


#ifndef PLATFORMS_TOOLCHAIN
#error "PLATFORMS_TOOLCHAIN is not defined. Check your Makefiles!"
#endif

/*Supported Toolchains */
#define PLATFORMS_gnu      1
#define PLATFORMS_dcc     2
#define PLATFORMS_multi      3
#define PLATFORMS_tasking  4

#define TS_TC275    1U
#define TS_TC21XL   2U
#define TS_TC1782   3U
#define TS_TC277    4U
#define TS_TC297    5U
#define TS_TC23XL   6U
#define TS_TC39XX   7U
#define TS_TC38XQ   8U

#ifndef BOARD_ASM

typedef uint8 Platforms_ResetType;

#if (TS_ARCH_DERIVATE == TS_TC21XL) ||  (TS_ARCH_DERIVATE == TS_TC23XL)
    #define PLATFORMS_ESR0_RESET            0x00 /* ESR0 reset */
    #define PLATFORMS_ESR1_RESET            0x01 /* ESR1 reset */
    #define PLATFORMS_SMU_RESET             0x02 /* SMU reset */
    #define PLATFORMS_SW_RESET              0x03 /* Software reset */
    #define PLATFORMS_STM0_RESET            0x04 /* STM0 reset */
    #define PLATFORMS_POWER_ON_RESET        0x05 /* Power On reset */
    #define PLATFORMS_CB0_RESET             0x06 /* CB0 reset */
    #define PLATFORMS_CB1_RESET             0x07 /* CB1 reset */
    #define PLATFORMS_CB3_RESET             0x08 /* CB3 reset */
    #define PLATFORMS_TP_RESET              0x09 /* Tuning Protection reset */
    #define PLATFORMS_EVR13_RESET           0x0A /* EVR13 Regulator Watchdog reset */
    #define PLATFORMS_SUPPLY_WDOG_RESET     0x0B /* Supply Watchdog reset */
    #define PLATFORMS_STBYR_RESET           0x0C /* Standby Regulator Watchdog reset */
    #define PLATFORMS_RESET_UNDEFINED       0xFFU /* Reset is undefined */
	
#elif (TS_ARCH_DERIVATE == TS_TC1782)

	/* Reset Status types of MCU needed for user*/
    #define PLATFORMS_ESR0_RESET            0x00 /* ESR0 reset */
    #define PLATFORMS_ESR1_RESET            0x01 /* ESR1 reset */
    #define PLATFORMS_WDT_RESET             0x03/* SMU reset */
    #define PLATFORMS_SW_RESET              0x04 /* Software reset */
    #define PLATFORMS_POWER_ON_RESET        0x10 /* Power On reset */
    #define PLATFORMS_CB0_RESET             0x12 /* CB0 reset */
    #define PLATFORMS_CB1_RESET             0x13 /* CB1 reset */
    #define PLATFORMS_CB3_RESET             0x14 /* CB3 reset */
    #define PLATFORMS_TP_RESET              0x15 /* Tuning Protection reset */
	#define PLATFORMS_RESET_UNDEFINED       0xFFU /* Reset is undefined */
	
#else
    #define PLATFORMS_ESR0_RESET            0x00 /* ESR0 reset */
    #define PLATFORMS_ESR1_RESET            0x01 /* ESR1 reset */
    #define PLATFORMS_SMU_RESET             0x02 /* SMU reset */
    #define PLATFORMS_SW_RESET              0x03 /* Software reset */
    #define PLATFORMS_STM0_RESET            0x04 /* STM0 reset */
    #define PLATFORMS_STM1_RESET            0x05 /* STM1 reset */
    #define PLATFORMS_STM2_RESET            0x06 /* STM2 reset */
    #define PLATFORMS_POWER_ON_RESET        0x07 /* Power On reset */
    #define PLATFORMS_CB0_RESET             0x08 /* CB0 reset */
    #define PLATFORMS_CB1_RESET             0x09 /* CB1 reset */
    #define PLATFORMS_CB3_RESET             0x0A /* CB3 reset */
    #define PLATFORMS_TP_RESET              0x0B /* Tuning Protection reset */
    #define PLATFORMS_EVR13_RESET           0x0C /* EVR13 Regulator Watchdog reset */
    #define PLATFORMS_EVR33_RESET           0x0D /* EVR33 Regulator Watchdog reset */
    #define PLATFORMS_SUPPLY_WDOG_RESET     0x0E /* Supply Watchdog reset */
    #define PLATFORMS_STBYR_RESET           0x0F /* Standby Regulator Watchdog reset */
    #define PLATFORMS_RESET_UNDEFINED       0xFFU /* Reset is undefined */
#endif

typedef uint8 Platforms_PowerType;
#define PLATFORMS_MCU_IDLE      0x00
#define PLATFORMS_MCU_SLEEP     0x01
#define PLATFORMS_MCU_STANDBY   0x02


#endif /* BOARD_ASM */
#endif /* _PLATFORMS_DEFS_H_ */
