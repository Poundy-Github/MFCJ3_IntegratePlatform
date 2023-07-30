/********************************************************************************
 *                                                                               *
 *                                 EB Layers                                     *
 *                                                                               *
 * ----------------------------------------------------------------------------- *
 *                                                                               *
 *                                   Board                                       *
 *                                                                               *
 *********************************************************************************
 *%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%                                        *
 *%%   _____________________________   %%  \file Board.h                         *
 *%%  |                             |  %%                                        *
 *%%  |   &&&&&   &&&&&             |  %%  Module version: 1.0.0                 *
 *%%  |   &       &    &            |  %%                                        *
 *%%  |   &&&&    &&&&&             |  %%                                        *
 *%%  |   &       &    &            |  %%                                        *
 *%%  |   &&&&&   &&&&&             |  %%                                        *
 *%%  |_____________________________|  %%                                        *
 *%%                                   %%                                        *
 *%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%                                        *
 *********************************************************************************
 * Copyright 2013 by Elektrobit Automotive GmbH                                  *
 * All rights exclusively reserved for Elektrobit Automotive GmbH,               *
 * unless expressly agreed to otherwise.                                         *
 ********************************************************************************/
/* Board.c file
 * !LINKSTO OsekCore.Platforms.Board.001, 1
 *          OsekCore.Platforms.Board.012, 1
 */

#ifndef I_KNOW_THAT_THIS_CODE_IS_NOT_FOR_PRODUCTION
#error "the program is not qualified for series production"
#endif

#ifndef __BOARD_H__
#define __BOARD_H__

#ifndef BOARD_ASM

#include <Platform_Types.h>
#include <Platforms_defs.h>
#include <Platforms_asm_TRICORE.h>
#include <ncs.h>
#include <board_Pub.h>

#ifdef PLATFORMS_STUBS_ENABLED 
#include <BoardStub.h>
#endif /* PLATFORMS_STUBS_ENABLED  */

/* CAN stubs */
#ifndef CAN_CONST
#define CAN_CONST
#endif

/* infinite loop variable*/
extern uint32 ulBoardInfiniteLoop;

extern u8 ubBoardIntLockNestingCounter;

#ifdef BOARD_ISR_TEST
extern volatile uint32 isrCounter;
#endif /* #ifdef BOARD_ISR_TEST */

extern void BoardDisableECCCheck(void);
extern void BoardEnableECCCheck(void);
extern void Mcal_ResetCpuEndInitProtection(void);
extern void Mcal_SetCpuEndInitProtection(void);

#endif

/* ********************************************
 * General configuration
 * ********************************************
 */



#define PLATFORMS_STM_ISRR_CMP0IRR       0x00000001u   /* Reset CMP0 irq */
#define PLATFORMS_STM_ISRR_CMP0IRS       0x00000002u   /* Set CMP0 irq */
#define PLATFORMS_STM_ISRR_CMP1IRR       0x00000004u   /* Reset CMP1 irq */
#define PLATFORMS_STM_ISRR_CMP1IRS       0x00000008u   /* Set CMP1 irq */


/* arbitrary infinite loop timeout to exit a while loop
 * in case PLL cannot be locked for example
 */
#define BOARD_INFINITE_LOOP_TIMEOUT     100000U
#define BOARD_CHECK_INFINITE_LOOP(timer) \
    do{ \
      if(timer > BOARD_INFINITE_LOOP_TIMEOUT){ \
        BoardPerformReset(PLATFORMS_SW_RESET); \
      } \
    }while(0)

#define BOARD_TRUE                      1U
#define BOARD_FALSE                     0U

#define BOARD_WDG_USED                  BOARD_TRUE

#define BOARD_OSC_FREQ_MHZ              20U

#define BOARD_PWR_BASE                  (0xF0036000U)
#define Board_pwr                       ((platforms_tricore_tc39x_pwr_t *)BOARD_PWR_BASE)[0]

#define BOARD_STM_0                     (0xF0001000U)
#define Board_stm0                      ((platforms_tricore_tc39x_stm_t *)BOARD_STM_0)

/* 200Mhz Configuration */
#define BOARD_SYSTEM_CLOCK_HZ           200000000U
#define BOARD_SYSTEM_CLOCK_MHZ          200U

/* By default the SCU clocks the STM modules with f_source/2, whereat f_sys is the PLL's output in
 * this configuration (see register CCUCON1 field STMDIV).
 * If the user changes this during startup, the following macro needs to be adapted.
 */
#define BOARD_STM_FREQ_HZ               ((BOARD_SYSTEM_CLOCK_HZ)/2U)

#ifndef BOARD_ASM
/* Deviation MISRA-1 */
#define BOARD_UU(x) x ## U
#else
#define BOARD_UU(x) x
#endif

/** \brief Appends the character 'U' to \a x to mark it as \e unsigned.
 *
 * This macro allows to use the same definition of a constant number in C
 * and assembler code.
 * Some assemblers don't like the 'U' suffix and cease to work.
 * The 'U', though, is important to suppress MISRA warnings.
 * This macro removes the 'U', when the code is prepared (preprocessed) for an assembler
 * and preserves it for a C compiler. This decision is based on the macro BOARD_ASM.
 *
 * \param x  A constant number.
 *
 * \see BOARD_UU
 */
#define BOARD_U(x) BOARD_UU(x)

#define BOARD_PLLCON0_INSEL_MASK                    (3u << 30u) /* Mask to select all bits in the INSEL field. */
#define BOARD_PLLCON0_INSEL_BACKUP_AS_CLK_SOURCE    0           /* Use backup clock as PLL input. */
#define BOARD_PLLCON0_INSEL_FOSC_AS_CLK_SOURCE      (1u << 30u) /* Use f_osc as PLL input. */


#define BOARD_OSCCON_OSCVAL         (5u << 16)

#define BOARD_FSI2_DIV 1u /* 0 (stopped), 1, 2, 3; input fSRI */
#define BOARD_BBB_DIV  2u /* 0 (stopped), 1, 2, 3, 4, 5, 6, 8, 10, 12, 15; input fPLL */
#define BOARD_SRI_DIV  1u /* 1, 2, 3, 4, 5, 6, 8, 10, 12, 15; input fPLL*/
#define BOARD_LP_DIV   0u /* 0 (do not use LP_DIV), 1, 2, 3, 4 (see manual for meaning) */

#if BOARD_SYSTEM_CLOCK_HZ <= 200000000U
#define BOARD_FSI_DIV  2u /* 0 (stopped), 1, 2, 3; input fSRI*/
#define BOARD_SPB_DIV  3u /* 2, 3, 4, 5, 6, 8, 10, 12, 15; input fPLL */
#define BOARD_STM_DIV  2u /* 0 (stopped), 1, 2, 3, 4, 5, 6, 8, 10, 12, 15; input fPLL */
#define BOARD_GTM_DIV  2u /* 0 (stopped), 1, 2, 3, 4, 5, 6, 8, 10, 12, 15; input fPLL */

#else /* BOARD_SYS_FREQ <= 300 MHz */
#error "Please define clock divider macros for your chosen BOARD_SYS_FREQ"

#endif

#if (BOARD_STM_FREQ_HZ == 90000000U)
#define BOARD_NS2TICKS(nS)              ((uint32)((((nS)/10U)*9U)/10U))
#elif (BOARD_STM_FREQ_HZ == 75000000U)
#define BOARD_NS2TICKS(nS)              ((uint32)((((nS)/10U)*3U)/4U))
#elif (BOARD_STM_FREQ_HZ == 50000000U)
#define BOARD_NS2TICKS(nS)              ((uint32)((((nS)/10U)*1U)/2U))
#elif (BOARD_STM_FREQ_HZ == 100000000U)
#define BOARD_NS2TICKS(nS)              ((uint32)((((nS)/10U)*1U)/1U))
#else
#error "You must configure the above macros for the BOARD_STM_FREQ_HZ frequency"
#endif

#define BOARD_PLL_RESLD         BOARD_U(0x00040000)    /* Reset lock detection */
#define BOARD_PLL_PLLPWD        BOARD_U(0x00010000)    /* Power saving mode (doc incorrect?) */
#define BOARD_PLL_OSCDISCDIS    BOARD_U(0x00000040)    /* Clear FINDIS on loss of lock */
#define BOARD_PLL_CLRFINDIS     BOARD_U(0x00000020)    /* Write 1 here to CLEAR FINDIS! */
#define BOARD_PLL_SETFINDIS     BOARD_U(0x00000010)    /* Disconnect OSC from VCO. */
#define BOARD_PLL_VCOBYP        BOARD_U(0x00000001)    /* VCO bypass */

/* OSCCON defines */
#define BOARD_OSCCON_OSCVAL_MASK    0x001f0000u
#define BOARD_OSCCON_MODE_OSC       0x0
#define BOARD_OSCCON_MODE_MASK      0x00000060u
#define BOARD_OSCCON_MODE_OSC       0x0
#define BOARD_OSCCON_PLLHV          0x00000100u
#define BOARD_OSCCON_OSCRES         0x00000004u
#define BOARD_OSCCON_PLLLV          0x00000002u
#define BOARD_OSCCON_OSCSTABLE     (BOARD_OSCCON_PLLLV | BOARD_OSCCON_PLLHV)


#define PLLCON1_K2RDY       0x20u
#define PLLCON1_K2DIV_MASK  0x7u

#define BOARD_PERPLLCON0_PLLPWD    BOARD_U(0x00010000)
#define BOARD_PERPLLCON0_RESLD     BOARD_U(0x00040000)
#define BOARD_PERPLLCON0_K2RDY        0x20u
#define BOARD_PERPLLCON0_K3RDY        0x10u
#define BOARD_PERPLLCON0_LOCK         0x04u
#define BOARD_PERPLLCON0_K2DIV_MASK   0x7u


/* pwr_ccucon: Bits and masks for clock control register. */
#define BOARD_CCUCON_LCK_LOCKED                      (1u << 31u) /* Register is locked and can't be updated anymore. */
#define BOARD_CCUCON_UP                              (1u << 30u) /* Update Request */
#define BOARD_CCUCON0_CLKSEL_MASK                    (3u << 28u) /* Mask to select all bits in the CLKSEL field. */
#define BOARD_CCUCON0_CLKSEL_BACKUP_CLK_AS_FSOURCE   0           /* Use backup clock as f_source. */
#define BOARD_CCUCON0_CLKSEL_PLL_CLK_AS_FSOURCE      (1u << 28u) /* Use PLL output as f_source. */

#if (BOARD_SYSTEM_CLOCK_HZ <= 200000000U)
#define BOARD_INITIAL_CCUCON0_DIV ( \
    (BOARD_FSI2_DIV << 26u) | \
    (BOARD_FSI_DIV  << 24u) | \
    (BOARD_BBB_DIV  << 20u) | \
    (BOARD_SPB_DIV  << 16u) | \
    (BOARD_LP_DIV   << 12u) | \
    (BOARD_SRI_DIV  <<  8u) | \
    (BOARD_GTM_DIV  <<  4u) | \
    BOARD_STM_DIV \
    )
#else
#error "Please define clock divider macros for your chosen BOARD_SYS_FREQ"
#endif /*(BOARD_SYS_FREQ <= 200000000U)*/

/* pwr_ccucon_2: Bits and masks for clock control register. */
#define BOARD_CCUCON2_CLKSELASCLINS_MASK               (3u << 12u) /* Mask to select all bits in the CLKSEL field. */
#define BOARD_CCUCON2_CLKSEL_BACKUP_CLK_AS_FSOURCE     0           /* ASCLINS clock is stopped. */
#define BOARD_CCUCON2_CLKSEL_ASCLINSI_CLK_AS_FSOURCE   (1u << 12u) /* Use PLL output as f_source. */
#define BOARD_CCUCON2_ASCLINF_DIV                      (2u)        /* Use f_source/2. */

#define BOARD_CCUCON1_PLL_DIV_DIS                      0           /* fPLL1 / 2 = fsource1. */



#define BOARD_PLL_SET_P(p)        ( ((p)-1u) << 24u )        /* PLLCON0 : 1 <= p <= 16 */
#define BOARD_PLL_SET_N(n)        ( ((n)-1u) << 9u )         /* PLLCON0 : 1 <= n <= 128 */
#define BOARD_PLL_SET_K1(k1)      ( ((k1)-1u) << 16u)        /* PLLCON1 : 1 <= k1 <= 128 */
#define BOARD_PLL_SET_K2(k2)	((k2)-1u)				/* PLLCON1 : 1 <= k2 <= 128 */
#define BOARD_PLL_SET_K3(k3)	(((k3)-1u) << 8u)		/* PLLCON1 : 1 <= k3 <= 128 */

/* pwr_pllstat: Bits for PLL status register */
#define BOARD_VCO_LOCK			BOARD_U(0x00000004)		/* PLL VCO Lock Status */


/* This is the initial PSW value:
 *   - call depth count disabled
 *   - supervisor mode
 *   - protection register set 0
 *   - interrupt stack (so we don't have to initialise the IS register yet)
 */
#define BOARD_INITIAL_PSW               (PLATFORMS_PSW_CDC_DIS+PLATFORMS_PSW_IO_SU+PLATFORMS_PSW_PRS_0+PLATFORMS_PSW_IS)

/* ******************
 * Startup features *
 * ******************
 */
#define BOARD_TRICORE_BMI               0x0070      /* internal start from flash */
#define BOARD_TRICORE_BOOTWORD          0xa0300020


/* Derivate supports instruction & data cache so it should be setup at startup.*/
#ifndef BOARD_DISABLE_CACHE
#define BOARD_DISABLE_CACHE             BOARD_TRUE
#endif

/* Derivate always runs in lock step mode. An initialisation
** for all register is needed to avoid unexpected system behavior.*/
#ifndef BOARD_INIT_CPU_REG
#define BOARD_INIT_CPU_REG              BOARD_TRUE
#endif

/* Initialize SRAM. If enabled, cstartup.s will initialize the SRAM according
 * to the following settings. This is needed for ECC enabled systems where
 * initializing the C bss and data sections is not enough.
 * set to 1 to enable initialization, to 0 to disable. */
#ifndef BOARD_INIT_SRAM
#define BOARD_INIT_SRAM                 BOARD_TRUE
#endif

#ifndef BOARD_STARTUP_CLOCK_ENABLE
#define BOARD_STARTUP_CLOCK_ENABLE      BOARD_TRUE
#endif

#ifndef BOARD_WDG_USED
#define BOARD_WDG_USED                  BOARD_TRUE
#endif

#ifndef BOARD_INIT_IT
#define BOARD_INIT_IT                   BOARD_TRUE
#endif

#ifndef BOARD_INTERRUPT_ENABLE
#define BOARD_INTERRUPT_ENABLE          BOARD_TRUE
#endif

/* This feature is developped for demo boards, but in some project specific 
 * cases the board is a real ECU.
 * In this case it can be risky to pilote external port that might be link 
 * to a specific hardware component.
 */
#ifndef BOARD_LED_USED 
#define BOARD_LED_USED                  BOARD_FALSE
#endif

/* **********************
 * Output configuration *
 * **********************
 */

/*1µS is the minimal timer available*/
#define BOARD_TIMER_MINIMAL             1L

/* Timer Initialisation - schedule to 1000µs */
#define BOARD_SCHEDULER                 1000U

/* **********************
 * PLL Settings         *
 * **********************
 */
/* Define if the main PLL shall be initialized */
#define BOARD_PLL_USED                  BOARD_FALSE

#define boardWaitForCCUCONIsUnlocked(x) \
  do { \
    while (((x) & PLATFORMS_CCUCON_LCK_LOCKED) != 0) {} \
  } while (0)



#define BOARD_INITIAL_CCUCON_DIV_MASK   0x0FFFFFFFU
/* A-step values
 #define BOARD_INITIAL_CCUCON1_DIV      0x00002211U
 #define BOARD_INITIAL_CCUCON2_DIV      0x000002B2U
 */
/* B-step values */
#define BOARD_INITIAL_CCUCON1_DIV       0x12202212U
#define BOARD_INITIAL_CCUCON2_DIV       0x00000002U


#if (BOARD_OSC_FREQ_MHZ== 20U) && (BOARD_SYSTEM_CLOCK_HZ==200000000U)
/*
 * P = 1;  N = 40;  k2 = 4;
 *
 * Input to VCO is 20MHz/1 = 20 MHz.
 * PLL runs at 20MHz*40 = 800 MHz, which is within the 400 - 800MHz operating range.
 * Output is 800MHz/4 = 200 MHz.
 *
 * The macros BOARD_P, BOARD_N, BOARD_K1 and BOARD_K2 are the "true" values of P, N, K1 and K2
 */
#define BOARD_P                         1U
#define BOARD_N                         40U
#define BOARD_K3                        8U
#define BOARD_K2                        4U
#define BOARD_K1                        1U
#define BOARD_K2_INITIAL                8U /* start with 100 MHz */


#define BOARD_P_PER                         1U
#define BOARD_N_PER                         32U
#define BOARD_K3_PER                        1U
#define BOARD_K2_PER                        2U


#elif (BOARD_OSC_FREQ_MHZ== 20U) && (BOARD_SYSTEM_CLOCK_HZ==150000000U)
/*
 * P = 2;  N = 60;  K2 = 4;
 *
 * Input to VCO is 20MHz/2 = 10 MHz.
 * PLL runs at 10MHz*60 = 600 MHz, which is within the 400 - 720MHz operating range.
 * Output is 600MHz/4 = 150 MHz.
 *
 *  The macros BOARD_P, BOARD_N, BOARD_K1 and BOARD_K2 are the "true" values of P, N, K1 and K2
 */
#define BOARD_P                         2U
#define BOARD_N                         60U
#define BOARD_K3                        6U
#define BOARD_K2                        4U
#define BOARD_K1                        1U
#define BOARD_K2_INITIAL                30U /* 600 VCO/30 = 20 MHz == BOARD_XTAL_FREQ */



#else
#error "You must define appropriate P, N, K1 and K2 values for this combination of crystal and CPU speed."
#endif

#if defined(BOARD_P) && defined(BOARD_N) && defined(BOARD_K1) && defined(BOARD_K2) && defined(BOARD_K3)
/*
 * These definitions should work for all valid combinations of P, N, K1 and K2.
 * The macros represent the base values of PLLCON0 and PLLCON1; extra bits that need
 * to be set and then cleared in order to kick-start the PLL are added by software in board.c
 *
 * The bit OSCDISCDIS is set.
 *
 * Besides PLL settings, the clock dividers inside the clock control unit (CCU) are set up.
 */

#define BOARD_INITIAL_PLLCON0		(BOARD_PLL_SET_P(BOARD_P)|BOARD_PLL_SET_N(BOARD_N)|BOARD_PLL_PLLPWD|BOARD_PLLCON0_INSEL_FOSC_AS_CLK_SOURCE)
#define BOARD_INITIAL_PLLCON1		(BOARD_PLL_SET_K2(BOARD_K2_INITIAL))

#else
#error "The crystal versus CPU speed selection above does not set the divider macros correctly!"

#endif

/* *****************************
 * I/O configuration  *
 * *****************************/
/* The next few lines contain the initialization of the user LEDs on the board. */
/* 8 toogle LEDs connected to P33.6 ... P33.13 */
#define BOARD_P33_BASE                  0xF003C100U
#define BOARD_P33_OUT                   (*(uint32 *)(BOARD_P33_BASE+0x0U))
#define BOARD_P33_IOCR0                 (*(uint32 *)(BOARD_P33_BASE+0x10U))
#define BOARD_P33_IOCR4                 (*(uint32 *)(BOARD_P33_BASE+0x14U))
#define BOARD_P33_IOCR8                 (*(uint32 *)(BOARD_P33_BASE+0x18U))
#define BOARD_P33_IOCR12                (*(uint32 *)(BOARD_P33_BASE+0x1cU))

#define LEDS_SET(x)\
    do {\
      BOARD_P33_OUT = (BOARD_P33_OUT & ~0x3fc0U) | (((~(x))&0xffU) << 6U);\
    } while (0)

#define LEDS_GET()  ((BOARD_P33_OUT>>6U) & 0xffU)

#define LEDS_INIT()\
    do {\
      BOARD_P33_IOCR4  = 0x80801010u;\
      BOARD_P33_IOCR8  = 0x80808080u;\
      BOARD_P33_IOCR12 = 0x10108080u;\
    } while (0)

/* *****************************
 * Interrupt Vector configuration  *
 * *****************************/
 
#define BOARD_FR_INT_VECT               1U
#define BOARD_TEST_INT_VECT             18U

#define TRIGGER_INT() do { \
  volatile int i; \
    (PLATFORMS_SRC_STM0SR0) |= PLATFORMS_SRC_SETR_MASK; \
  PLATFORMS_ISYNC(); \
  for(i=40; i > 0; i--) { } \
  } while(0)



#define TRIGGER_INT_STM0() do { \
  volatile int i; \
    (PLATFORMS_SRC_STM0SR0) |= PLATFORMS_SRC_SETR_MASK; \
  PLATFORMS_ISYNC(); \
  for(i=40; i > 0; i--) { } \
  } while(0)


#define BOARD_FR_INT_VECT               1U
#define BOARD_CAN_INT_VECT0             2U
#define BOARD_CAN_INT_VECT1             3U
#define BOARD_CAN_INT_VECT2             4U
#define BOARD_CAN_INT_VECT3             5U
#define BOARD_CAN_INT_VECT4             6U
#define BOARD_CAN_INT_VECT5             7U
#define BOARD_CAN_INT_VECT6             8U
#define BOARD_CAN_INT_VECT7             9U
#define BOARD_CAN_INT_VECT8             10U
#define BOARD_CAN_INT_VECT9             11U
#define BOARD_CAN_INT_VECT10            12U
#define BOARD_CAN_INT_VECT11            13U
#define BOARD_CAN_INT_VECT12            14U
#define BOARD_CAN_INT_VECT13            15U
#define BOARD_CAN_INT_VECT14            16U
#define BOARD_CAN_INT_VECT15            17U
#define BOARD_TEST_INT_VECT             18U
#define BOARD_LIN_INT_VECT_TX           19U
#define BOARD_LIN_INT_VECT_RX           20U
#define BOARD_LIN_INT_VECT_ERR          21U

#endif
