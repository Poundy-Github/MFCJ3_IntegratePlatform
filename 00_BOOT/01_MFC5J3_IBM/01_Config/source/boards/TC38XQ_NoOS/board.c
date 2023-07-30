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
 *%%   _____________________________   %%  \file Board.c                         *
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
 * Copyright 2015 by Elektrobit Automotive GmbH                                  *
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

#include "TSAutosar.h"
#include <board.h>
#include <Ifx_reg.h>
#include "IfxPfi_bf.h"
#include "log.h"
extern char __STARTBSS, __ENDBSS, __STARTDATA, __ENDDATA, __INITDATA, __STACK_SIZE,__SP_INIT;
/*==================[internal function declarations]========================*/


/*==================[external function definitions]=========================*/
extern void BoardWriteEndinit(uint32 state);
extern uint32 boardGetCoreId(void);

#if (PLATFORMS_TOOLCHAIN == PLATFORMS_tasking)
extern void BoardInitCData(void);
#endif


#ifdef BOARD_ISR_TEST
volatile u32 isrCounter; /* invocation counter for TestIsr  */
#endif

/* These are not real variables: they are marker symbols set up by the linker script
 */
extern uint32 BoardExceptionTable;
extern uint32 IntcVectorTableHw;

uint32 tInterruptSave;


/* 
 * !LINKSTO OsekCore.Platforms.Board.102, 1
 */
#ifndef PLATFORMS_STUBS_ENABLED 
u8 ubBoardIntLockNestingCounter = 0U;
#endif

/* **********************
 * Stack Configuration  *
 * **********************
 */

#ifndef BOARD_ASM
#define BOARD_START_STACK_CODE
#include "Board_MemMap.h"
/* Define usage of at least 2000 bytes of stack size linking the __SP_INIT
 * !LINKSTO OsekCore.Platforms.Startup.012, 1
 */
/* Stack Size definition */
uint32 stack[1024];
#define BOARD_STOP_STACK_CODE
#include "Board_MemMap.h"
#endif  /* BOARD_ASM */

/* Stack pointer Address/Size*/
void * const boardSp = (void *) (((uint32) stack) + sizeof(stack));

uint32 ulSTMTimerOldVal;

uint32 ulBoardInfiniteLoop;

/* Copy the data section out from flash to RAM
 * and clear the bss section.
*/
/* RAM noinit
* !LINKSTO OsekCore.Platforms.Startup.013, 1
*/

static void BoardCopyRomToRam(void)
{
    register char * p;
    register char *q;
    for ( p = &__STARTDATA, q = &__INITDATA; p < &__ENDDATA; p++, q++ )
    {
        *p = *q;
    }
    for ( p = &__STARTBSS; p < &__ENDBSS; p++ )
    {
        *p = 0;
    }
}


/*
 ** BoardInit()
 **
 ** BoardInit() is called by the startup code (cstartup.s) after data and bss
 ** sections have been initialized (global variables may now be used).
 ** The BoardInit() can be used to start up drivers etc.
 */
/*
 * !LINKSTO OsekCore.Platforms.Board.013, 1
 */
void BoardInit(void)
{
#if (BOARD_LED_USED == BOARD_TRUE)
    /*Init LED so that an Invalid Interrupt/Exception can be seen earlier*/
    BoardInitLed();
#endif 

    PLATFORMS_RFJL();
    /* Special "return" */
}
/* DisableInterrupt is linked to PLatforms plugin file
 * !LINKSTO OsekCore.Platforms.Board.002, 1
 */
#ifndef PLATFORMS_STUBS_ENABLED 
void BoardDisableInterrupts(void)
{
    if (ubBoardIntLockNestingCounter < 255U)
    {
        if (ubBoardIntLockNestingCounter == 0U)
        {
            PLATFORMS_DISABLE();
        }
        ubBoardIntLockNestingCounter++;
    }
}
#endif /* ifndef PLATFORMS_STUBS_ENABLED  */
/* DisableInterrupt is linked to PLatforms plugin file
 * !LINKSTO OsekCore.Platforms.Board.002, 1
 */
#ifndef PLATFORMS_STUBS_ENABLED 
void BoardEnableInterrupts(void)
{
    if (ubBoardIntLockNestingCounter > 0U)
    {
        ubBoardIntLockNestingCounter--;

        if (ubBoardIntLockNestingCounter == 0U)
        {
            PLATFORMS_ENABLE();
        }
    }
 }
#endif /* ifndef PLATFORMS_STUBS_ENABLED  */
/*
 * !LINKSTO OsekCore.Platforms.Board.003, 1
 */
 void BoardWatchdogDeactivation(void)
{
    BoardWriteEndinit(0);

    /* Disable the safety watchdog */
    Board_pwr.pwr_swdt.wdt_con[1] = 8U;
    switch (boardGetCoreId())
    {
        case 0: /* Fall through */
        case 1: /* Fall through */
        case 2:
        case 3:
            /* Disable the CPU watchdogs */
            Board_pwr.pwr_wdt[boardGetCoreId()].wdt_con[1] = 8U;
            break;
        default:
              /* You have discovered an undocumented core, then reset the ECU :) */
              BoardPerformReset(PLATFORMS_SW_RESET);
            break;
        }

    BoardWriteEndinit(1);
}

void BoardStartupClocks(void)
{
    /* Clocks setup is under preprocessing conditions
     * !LINKSTO OsekCore.Platforms.Board.004, 1
     */

#if (BOARD_PLL_USED == BOARD_TRUE) 
    /* Now this function assumes, that it is called with the system running on the backup
         * clock, so we can start reconfiguring the PLL without further ado.
        */

        /* configure PLL dividers for normal mode */
        /* fVCO must be within 400 to 800 MHz */
        /* fVCO = fOSC / P * N */

    Board_pwr.pwr_pllcon[0]  = BOARD_INITIAL_PLLCON0;
    Board_pwr.pwr_pllcon[1]  = BOARD_INITIAL_PLLCON1;

    /* It is recommended to reset the VCO Lock detection (PLLCON0.RESLD = 1) after
         * the new values of the dividers are configured to get a defined VCO lock check
         * time.
    */
    Board_pwr.pwr_pllcon[0] |= BOARD_PLL_RESLD;



    /* switch to external oscillator */
    Board_pwr.pwr_osccon = (Board_pwr.pwr_osccon & (~BOARD_OSCCON_MODE_MASK)) | BOARD_OSCCON_MODE_OSC;
    Board_pwr.pwr_osccon = (Board_pwr.pwr_osccon & (~BOARD_OSCCON_OSCVAL_MASK)) | BOARD_OSCCON_OSCVAL;
    Board_pwr.pwr_osccon |= BOARD_OSCCON_OSCRES;


    /* Wait for PLL lock */
    while ( ((Board_pwr.pwr_osccon & BOARD_OSCCON_PLLHV) == 0) ||
            ((Board_pwr.pwr_osccon & BOARD_OSCCON_PLLLV) == 0) ) { }
    while ((Board_pwr.pwr_pllstat & BOARD_VCO_LOCK) == 0) { }


    /* now increase the frequency by step-wise reducing the K2 divider to BOARD_K2 */
    {
        u32 kdiv;
        do {
                volatile u32 i;

                kdiv = Board_pwr.pwr_pllcon[1] & PLLCON1_K2DIV_MASK;
                kdiv--;
                Board_pwr.pwr_pllcon[1] = (Board_pwr.pwr_pllcon[1] & ~PLLCON1_K2DIV_MASK) | kdiv;

                /* Between the update of two K2-Divider values 6 cycles of fPLL should be waited. */
                for(i=0; i<10; i++) { }

                /* wait until K2 is ready (K2RDY==1) */
                while ((Board_pwr.pwr_pllstat & PLLCON1_K2RDY) == 0) { }
        } while(kdiv >= BOARD_K2); /* target is BOARD_K2 - 1 */
    }


    /* Step 4: Configure CCU: The defaults fit the bill. */
    boardWaitForCCUCONIsUnlocked(Board_pwr.pwr_ccucon[0]);
    Board_pwr.pwr_ccucon[0]    = BOARD_CCUCON0_CLKSEL_PLL_CLK_AS_FSOURCE | BOARD_INITIAL_CCUCON0_DIV;
    Board_pwr.pwr_ccucon[0]   |= BOARD_CCUCON_UP;				/* Commit changes to CCUCON0 and 1 to core. */


    /* PER PLL init */
    Board_pwr.pwr_perpllcon[0] |= BOARD_PERPLLCON0_PLLPWD;

    Board_pwr.pwr_perpllcon[0] |= ((BOARD_N_PER-1) << 9);
    Board_pwr.pwr_perpllcon[0] |= ((BOARD_P_PER-1) << 24);

    Board_pwr.pwr_perpllcon[1] |= (BOARD_K2_PER-1);

    Board_pwr.pwr_perpllcon[1] |= ((BOARD_K3_PER-1) << 8);

    Board_pwr.pwr_perpllcon[0] |= BOARD_PERPLLCON0_RESLD;

    /* Wait for PERPLL lock */
    while ((Board_pwr.pwr_perpllstat & BOARD_PERPLLCON0_LOCK) == 0)
    { }

#endif /*#if (BOARD_TRUE == BOARD_STARTUP_CLOCK_ENABLE)*/
}



/* So far no Port are used in the Board
 * !LINKSTO OsekCore.Platforms.Board.007, 1
 */
void BoardPortsSettings(void)
{
}
/*
 * !LINKSTO OsekCore.Platforms.Board.005, 1
 * Value passed in �S
 */
uint8 BoardInitializationTimers(uint16 uwTimer)
{
    uint8 RetVal = 0u;
    

    /*Disable Interrupt generation on Timer Compare*/
    Board_stm0->stm_icr = (Board_stm0->stm_icr & ~(PLATFORMS_STM_ICR_CMP0))
            | PLATFORMS_STM_ICR_DISABLE;

    /*Clear interrupt flag (reset value shall be 0 but ... we don't know */
    Board_stm0->stm_isrr = PLATFORMS_STM_ISRR_CMP0IRR;

    /* Setup Compare register CMP0[31:0] used for comparison, STM[0] is the lowest bit*/
    Board_stm0->stm_cmcon = (Board_stm0->stm_cmcon & ~(PLATFORMS_STM_CMCON0))
            | PLATFORMS_STM_MSIZE0;

    /* Store actual time for STM0*/
    ulSTMTimerOldVal = Board_stm0->stm_tim0;

    /* check Timer validity and Board frequency available */
    if ((uwTimer >= BOARD_TIMER_MINIMAL) && (BOARD_SYSTEM_CLOCK_MHZ > 0u))
    {
        /* Timer configured OK*/
        RetVal = 1u;
    }
    else
    {
        RetVal = 0u;
    }
    return RetVal;
}
/*
 * !LINKSTO OsekCore.Platforms.Board.010, 1
 */
uint8 BoardSchedulingTimer(void)
{
    uint8 ubFlag;
    ubFlag = 0x0u;

    /* if STM0 is > to the next Configured value, time expired and needs to be reloaded*/
    if (Board_stm0->stm_tim0 > ulSTMTimerOldVal)
    {
        if((Board_stm0->stm_tim0 - ulSTMTimerOldVal) >= BOARD_NS2TICKS(BOARD_SCHEDULER*1000))
        {
            /* Store actual time for STM0*/
            ulSTMTimerOldVal = Board_stm0->stm_tim0;

            /* Set return flag to TRUE */
            ubFlag = 0x1U;
        }
    }
    else if ((Board_stm0->stm_tim0 + (U32_MAX - ulSTMTimerOldVal)) >= BOARD_NS2TICKS(BOARD_SCHEDULER*1000))
    {
        /* Store actual time for STM0*/
        ulSTMTimerOldVal = Board_stm0->stm_tim0;

        /* Set return flag to TRUE */
        ubFlag = 0x1U;
    }
    else
    {
        /* nothing to do */
    }

    return ubFlag;
}
/*
 * !LINKSTO OsekCore.Platforms.Board.011, 1
 */
void BoardStart(void)
{
    /* Desactivation of watchdog */
    BoardWatchdogDeactivation();

    /* Clear BSS sections, copy Data/init sections: the API _c_init function provided by tasking does not work for this target
     */
    BoardCopyRomToRam();

    BoardDisableInterrupts();

    /* Setup clocks*/
    //BoardStartupClocks();

    if (1u != BoardInitializationTimers(BOARD_SCHEDULER))
    {
        /*in case timer cannot be initialized, while loop for debugging
         * !LINKSTO OsekCore.Platforms.Board.011, 1
         */
        for (;;)
        {
        }
    }

    /* Port Initialisation */
    BoardPortsSettings();

    /* Initialization ISRs */
    BoardInitInterrupts();

    BoardEnableInterrupts();

    PLATFORMS_RFJL();
    /* Special "return" */
}
/*
 * !LINKSTO OsekCore.Platforms.Board.008, 1
 */
void BoardInitLed(void)
{
    LEDS_INIT();
    LEDS_SET(0); /* check the LEDS */
    LEDS_SET(1);
    LEDS_SET(0);
}

/*
 * !LINKSTO OsekCore.Platforms.Board.009, 1
 */
void BoardToggleLed(uint8 ubLed)
{
    LEDS_SET(ubLed);
}

void BoardInitInterrupts(void)
{
    BoardWriteEndinit(0);

    /*
     * !LINKSTO OsekCore.Platforms.Startup.006, 1
     */
    PLATFORMS_MTCR(PLATFORMS_BTV, (uint32 )&BoardExceptionTable);
    PLATFORMS_MTCR(PLATFORMS_BIV, (uint32 )&IntcVectorTableHw);
    PLATFORMS_MTCR(PLATFORMS_ISP, ((unsigned )stack) + sizeof(stack));

    /* Set initial PSW value.
     */
    PLATFORMS_MTCR(PLATFORMS_PSW, BOARD_INITIAL_PSW);

    BoardWriteEndinit(1);

    /* Configure each interrupt, still, all ISR are disables in ICR*/
#ifdef BOARD_ISR_FR0
    PLATFORMS_SRC_ERAYINT0 = PLATFORMS_SRC_TOS_CPU0 | PLATFORMS_SRC_SRE | PLATFORMS_SRC_SPRN_PRIO(1);
#endif

#ifdef BOARD_ISR_CAN0
    PLATFORMS_SRC_CANINT0 = PLATFORMS_SRC_TOS_CPU0 | PLATFORMS_SRC_SRE | PLATFORMS_SRC_SPRN_PRIO(2);
    PLATFORMS_SRC_CANINT1 = PLATFORMS_SRC_TOS_CPU0 | PLATFORMS_SRC_SRE | PLATFORMS_SRC_SPRN_PRIO(3);
    PLATFORMS_SRC_CANINT2 = PLATFORMS_SRC_TOS_CPU0 | PLATFORMS_SRC_SRE | PLATFORMS_SRC_SPRN_PRIO(4);
    PLATFORMS_SRC_CANINT3 = PLATFORMS_SRC_TOS_CPU0 | PLATFORMS_SRC_SRE | PLATFORMS_SRC_SPRN_PRIO(5);
    PLATFORMS_SRC_CANINT4 = PLATFORMS_SRC_TOS_CPU0 | PLATFORMS_SRC_SRE | PLATFORMS_SRC_SPRN_PRIO(6);
    PLATFORMS_SRC_CANINT5 = PLATFORMS_SRC_TOS_CPU0 | PLATFORMS_SRC_SRE | PLATFORMS_SRC_SPRN_PRIO(7);
    PLATFORMS_SRC_CANINT6 = PLATFORMS_SRC_TOS_CPU0 | PLATFORMS_SRC_SRE | PLATFORMS_SRC_SPRN_PRIO(8);
    PLATFORMS_SRC_CANINT7 = PLATFORMS_SRC_TOS_CPU0 | PLATFORMS_SRC_SRE | PLATFORMS_SRC_SPRN_PRIO(9);
    PLATFORMS_SRC_CANINT8 = PLATFORMS_SRC_TOS_CPU0 | PLATFORMS_SRC_SRE | PLATFORMS_SRC_SPRN_PRIO(10);
    PLATFORMS_SRC_CANINT9 = PLATFORMS_SRC_TOS_CPU0 | PLATFORMS_SRC_SRE | PLATFORMS_SRC_SPRN_PRIO(11);
    PLATFORMS_SRC_CANINT10 = PLATFORMS_SRC_TOS_CPU0 | PLATFORMS_SRC_SRE | PLATFORMS_SRC_SPRN_PRIO(12);
    PLATFORMS_SRC_CANINT11 = PLATFORMS_SRC_TOS_CPU0 | PLATFORMS_SRC_SRE | PLATFORMS_SRC_SPRN_PRIO(13);
    PLATFORMS_SRC_CANINT12 = PLATFORMS_SRC_TOS_CPU0 | PLATFORMS_SRC_SRE | PLATFORMS_SRC_SPRN_PRIO(14);
    PLATFORMS_SRC_CANINT13 = PLATFORMS_SRC_TOS_CPU0 | PLATFORMS_SRC_SRE | PLATFORMS_SRC_SPRN_PRIO(15);
    PLATFORMS_SRC_CANINT14 = PLATFORMS_SRC_TOS_CPU0 | PLATFORMS_SRC_SRE | PLATFORMS_SRC_SPRN_PRIO(16);
    PLATFORMS_SRC_CANINT15 = PLATFORMS_SRC_TOS_CPU0 | PLATFORMS_SRC_SRE | PLATFORMS_SRC_SPRN_PRIO(17);
#endif

#ifdef BOARD_ISR_TEST
    PLATFORMS_SRC_STM0SR0 = PLATFORMS_SRC_TOS_CPU0 | PLATFORMS_SRC_SRE | PLATFORMS_SRC_SPRN_PRIO(18);
#endif

#ifdef BOARD_ISR_LIN0
    PLATFORMS_SRC_ASCLIN1TX = PLATFORMS_SRC_SPRN_PRIO(19);
    PLATFORMS_SRC_ASCLIN1RX = PLATFORMS_SRC_SPRN_PRIO(20);
    PLATFORMS_SRC_ASCLIN1EX = PLATFORMS_SRC_SPRN_PRIO(21);
#endif

}

/*
 * Board_InvalidInterrupt(uint32 id)
 *
 * The Board_InvalidInterrupt() routine is used for uninitialized
 * vectors of the vector table if errorhandling is set to minimal.
 * Parameter 'id' is containing the interrupt identification number.
 */
/*
 * !LINKSTO OsekCore.Platforms.Board.014, 1
 */
void BoardInvalidInterrupt(uint32 id)
{

    LOG(LOG_LEVEL_ERROR, "BoardInvalidInterrupt id[%X]",id);

#if (BOARD_LED_USED == BOARD_TRUE)
    LEDS_INIT()
    ;
    LEDS_SET(0x0F);
#endif

    /* infinite loop is intended for debugging purposes*/
    for (;;)
    {
    }
}

/*
 * BoardInvalidException(uint32 id, uint32 sp)
 *
 * The boardInvalidException() routine is used for uninitialized
 * vectors of the exception table if Exception handling is off.
 * Parameter 'id' contains the exception id
 * and 'sp' is the current stack pointer.
 *
 */
/*
 * !LINKSTO OsekCore.Platforms.Board.015,1
 */
void BoardInvalidException0(uint32 id, uint32 sp)
{

  LOG(LOG_LEVEL_ERROR, "BoardInvalidException 0 id[%X] sp[%X]",id, sp);

#if (BOARD_LED_USED == BOARD_TRUE)
    LEDS_INIT();

    /* infinite loop is intended for debugging purposes*/
    LEDS_SET(0xF0);
#endif

    for (;;)
    {
    }
}
void BoardInvalidException1(uint32 id, uint32 sp)
{

  LOG(LOG_LEVEL_ERROR, "BoardInvalidException 1 id[%X] sp[%X]",id, sp);

#if (BOARD_LED_USED == BOARD_TRUE)
    LEDS_INIT();

    /* infinite loop is intended for debugging purposes*/
    LEDS_SET(0xF0);
#endif

    for (;;)
    {
    }
}
void BoardInvalidException2(uint32 id, uint32 sp)
{

  LOG(LOG_LEVEL_ERROR, "BoardInvalidException 2 id[%X] sp[%X]",id, sp);

#if (BOARD_LED_USED == BOARD_TRUE)
    LEDS_INIT();

    /* infinite loop is intended for debugging purposes*/
    LEDS_SET(0xF0);
#endif

    for (;;)
    {
    }
}
void BoardInvalidException3(uint32 id, uint32 sp)
{

  LOG(LOG_LEVEL_ERROR, "BoardInvalidException 3 id[%X] sp[%X]",id, sp);

#if (BOARD_LED_USED == BOARD_TRUE)
    LEDS_INIT();

    /* infinite loop is intended for debugging purposes*/
    LEDS_SET(0xF0);
#endif

    for (;;)
    {
    }
}
void BoardInvalidException4(uint32 id, uint32 sp)
{

  LOG(LOG_LEVEL_ERROR, "BoardInvalidException  4 id[%X] sp[%X]",id, sp);

#if (BOARD_LED_USED == BOARD_TRUE)
    LEDS_INIT();

    /* infinite loop is intended for debugging purposes*/
    LEDS_SET(0xF0);
#endif

    for (;;)
    {
    }
}
void BoardInvalidException5(uint32 id, uint32 sp)
{

  LOG(LOG_LEVEL_ERROR, "BoardInvalidException 5 id[%X] sp[%X]",id, sp);

#if (BOARD_LED_USED == BOARD_TRUE)
    LEDS_INIT();

    /* infinite loop is intended for debugging purposes*/
    LEDS_SET(0xF0);
#endif

    for (;;)
    {
    }
}
void BoardInvalidException6(uint32 id, uint32 sp)
{

  LOG(LOG_LEVEL_ERROR, "BoardInvalidException 6 id[%X] sp[%X]",id, sp);

#if (BOARD_LED_USED == BOARD_TRUE)
    LEDS_INIT();

    /* infinite loop is intended for debugging purposes*/
    LEDS_SET(0xF0);
#endif

    for (;;)
    {
    }
}
void BoardInvalidException7(uint32 id, uint32 sp)
{

  LOG(LOG_LEVEL_ERROR, "BoardInvalidException 7 id[%X] sp[%X]",id, sp);

#if (BOARD_LED_USED == BOARD_TRUE)
    LEDS_INIT();

    /* infinite loop is intended for debugging purposes*/
    LEDS_SET(0xF0);
#endif

    for (;;)
    {
    }
}
/*
 * !LINKSTO OsekCore.Platforms.Board.016,1
 */
#ifndef PLATFORMS_STUBS_ENABLED 
void BoardPerformReset(Platforms_ResetType ubResetType)
{

    if(PLATFORMS_SW_RESET == ubResetType)
    {

        /* Disable Write protected register*/
        BoardWriteEndinit(0);
        /* Disable Interrupts before Reset*/
        BoardDisableInterrupts();
        /* Trigger SW Reset by writting ResetRequest  SWRSTCON*/
        Board_pwr.pwr_swrstcon |= PLATFORMS_SWRSTCON_SWRSTREQ;

        /* Wait for Reset*/
        for(;;)
        {

        }

        /* Infinite loop is intended since ECU shall reset,
         * in worst case, if WDG is on, it shall reset the ECU
         */
    }
    /* Other reset types are not implemented*/
}
#endif /* ifdef PLATFORMS_STUBS_ENABLED  */

#ifndef PLATFORMS_STUBS_ENABLED 
void BoardPerformSwReset()
{
    /* Disable Write protected register*/
    BoardWriteEndinit(0);
    /* Disable Interrupts before Reset*/
    BoardDisableInterrupts();

    Mcu_PerformReset();
}
#endif /* ifndef PLATFORMS_STUBS_ENABLED  */
/*
 * !LINKSTO OsekCore.Platforms.Board.017,1
 */
#ifndef PLATFORMS_STUBS_ENABLED 
Platforms_ResetType BoardGetResetType(void)
{
    volatile Platforms_ResetType BoardResetReturn;
    volatile uint32 BoardResetRegister;

    BoardResetReturn = PLATFORMS_RESET_UNDEFINED;
    BoardResetRegister = PLATFORMS_RAW_RESET_UNDEFINED;

    /* Get RAW Reset Reason */
    BoardResetRegister = (uint32)(Board_pwr.pwr_rststat & PLATFORMS_RESET_REASON_MASK);

    if(PLATFORMS_RAW_SW_RESET == (BoardResetRegister & PLATFORMS_RAW_SW_RESET))
    {
        BoardResetReturn = PLATFORMS_SW_RESET;
    }
    else if ( (PLATFORMS_RAW_POWER_ON_RESET_1 == (BoardResetRegister & PLATFORMS_RAW_POWER_ON_RESET_1)) ||
              (PLATFORMS_RAW_POWER_ON_RESET_2 == (BoardResetRegister & PLATFORMS_RAW_POWER_ON_RESET_2))
    )
    {
        BoardResetReturn = PLATFORMS_POWER_ON_RESET;
    }
    else
    {
        BoardResetReturn = PLATFORMS_RESET_UNDEFINED;
    }

    LOG(LOG_LEVEL_INFO, "reset reason 0x%X", BoardResetReturn);

    return BoardResetReturn;
}
#endif /* ifndef PLATFORMS_STUBS_ENABLED  */

#ifndef PLATFORMS_STUBS_ENABLED 
uint8 BoardIsSwReset()
{
	Platforms_ResetType ResetFlag,ResetType;
	ResetType =BoardGetResetType() ;

	if(ResetType == PLATFORMS_SW_RESET)
	{
		ResetFlag = TRUE;
	}
	else
	{
		ResetFlag = FALSE;
	}
   return 	ResetFlag;

}
#endif /* ifdef PLATFORMS_STUBS_ENABLED  */
/*
 * !LINKSTO OsekCore.Platforms.Board.018,1
 */
#ifndef PLATFORMS_STUBS_ENABLED 
void BoardSetState(Platforms_PowerType ubState)
{
    /* Check input States in acceptable range */
    if( (PLATFORMS_MCU_IDLE == ubState) ||
        (PLATFORMS_MCU_SLEEP == ubState) ||
        (PLATFORMS_MCU_STANDBY == ubState)
    )
    {
        /* Go to StandBy mode */
        BoardWriteEndinit(0); /* Unlock endinit-protected registers. */

        /*Set correct core to requested state*/
        Board_pwr.pwr_pmcsr[boardGetCoreId()] = ubState + 1;

        BoardWriteEndinit(1); /* lock endinit-protected registers. */

        if( (PLATFORMS_MCU_SLEEP == ubState) || (PLATFORMS_MCU_SLEEP == ubState))
        {
           /* infinite loop to wait Sleep / Standby*/
           for(;;)
           {

           }
        }
    }
}
#endif /* ifndef PLATFORMS_STUBS_ENABLED  */

/*
 * !LINKSTO OsekCore.Platforms.Board.019,1
 */
#ifndef PLATFORMS_STUBS_ENABLED 
uint32 BoardGetRandom(void)
{
    uint32 ulBoardRandom;

    /* Get 32bits STM0 */
    ulBoardRandom = Board_stm0->stm_tim0;

    /* Bit inverted */
    ulBoardRandom = ~(ulBoardRandom);

    /* Manipulate the Random value so it is not that easy to find !*/
    ulBoardRandom =(uint32) ((uint32) ulBoardRandom + (uint32) (ulBoardRandom << 16U)
                    + (uint32) (ulBoardRandom >> 24U));

    return ulBoardRandom;
}
#endif /* ifndef PLATFORMS_STUBS_ENABLED  */

/* Internal function called only from Assembly code for startup feature
 * - initialize the Stack Pointer, as STACK grows down, SP shall point to lower address of the stack. DO NOT CALL FROM C!
 * */
void BoardInitSp(void)
{
    PLATFORMS_MTSP(boardSp);
    PLATFORMS_RFJL();
}

void BoardDisableECCCheck(void)
{
  /*Invalid ECC trap error */
  Mcal_ResetCpuEndInitProtection();
  CPU0_FLASHCON2.B.ECCCORDIS = 1;
  CPU0_FLASHCON1.B.MASKUECC = 1;
  CPU1_FLASHCON2.B.ECCCORDIS = 1;
  CPU1_FLASHCON1.B.MASKUECC = 1;
  CPU2_FLASHCON2.B.ECCCORDIS = 1;
  CPU2_FLASHCON1.B.MASKUECC = 1;
  CPU3_FLASHCON2.B.ECCCORDIS = 1;
  CPU3_FLASHCON1.B.MASKUECC = 1;
  Mcal_SetCpuEndInitProtection();
}

void BoardEnableECCCheck(void)
{
  Mcal_ResetCpuEndInitProtection();
  CPU0_FLASHCON2.B.ECCCORDIS = 2;
  CPU0_FLASHCON1.B.MASKUECC = 2;
  CPU1_FLASHCON2.B.ECCCORDIS = 2;
  CPU1_FLASHCON1.B.MASKUECC = 2;
  CPU2_FLASHCON2.B.ECCCORDIS = 2;
  CPU2_FLASHCON1.B.MASKUECC = 2;
  CPU3_FLASHCON2.B.ECCCORDIS = 2;
  CPU3_FLASHCON1.B.MASKUECC = 2;
  Mcal_SetCpuEndInitProtection();
}

void Mcal_ResetCpuEndInitProtection(void)
{
    BoardWriteEndinit(0);
}

void Mcal_SetCpuEndInitProtection(void)
{
    BoardWriteEndinit(1);
}

