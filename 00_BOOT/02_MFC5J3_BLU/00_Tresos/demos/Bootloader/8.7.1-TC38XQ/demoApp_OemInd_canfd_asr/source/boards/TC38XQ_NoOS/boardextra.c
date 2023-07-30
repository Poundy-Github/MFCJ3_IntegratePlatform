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
 *%%   _____________________________   %%  \file Boardextra.c                    *
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

/*Contains all extra code required for board startup but not "common" */

#ifndef I_KNOW_THAT_THIS_CODE_IS_NOT_FOR_PRODUCTION
#error "the program is not qualified for series production"
#endif

#include "TSAutosar.h"
#include "board.h"
#include <Platforms_asm_TRICORE.h>
#if (PLATFORMS_TOOLCHAIN == PLATFORMS_tasking)

extern void _c_init(void); /* tasking C initialization function */

#endif
/*==================[internal function declarations]========================*/
void BoardInitCsaList(void);
void BoardInitSp(void);
void BoardWriteEndinit(uint32 state); /* Unlock endinit-protected registers. */
void BoardWriteEndInitAurix(uint32 state, platforms_tc_wdt_t *pWdt);

/*==================[external function definitions]=========================*/
#if (PLATFORMS_TOOLCHAIN == PLATFORMS_tasking)
void BoardInitCData(void);
#endif

/* These are not real variables: they are marker symbols set up by the linker script
 */
extern uint32 BOARD_CSAMEMORY_BEGIN;
extern uint32 BOARD_CSAMEMORY_END;

extern char __STARTBSS, __ENDBSS, __STARTDATA, __ENDDATA, __INITDATA, __STACK_SIZE,__SP_INIT;
platforms_tc_wdt_t * const Board_safetyWdt = &Board_pwr.pwr_swdt;
platforms_tc_wdt_t * const Board_cpuWdt = &Board_pwr.pwr_wdt[0];

/** \brief Structure definition for the BMHD\n
 *
 */
typedef struct
{
    unsigned short bmi;             /**< \brief 0x000: Boot Mode Index (BMI)*/
    unsigned short bmhdid;          /**< \brief 0x002: Boot Mode Header ID (CODE) = B359H*/
    unsigned int   stad;            /**< \brief 0x004: User Code start address*/
    unsigned int   crc;             /**< \brief 0x008: Check Result for the BMI Header (offset 000H - 007H)*/
    unsigned int   crcInv;          /**< \brief 0x00C: Inverted Check Result for the BMI Header (offset 000H - 007H)*/
    unsigned int   reserved[120];   /**< \brief 0x010: Reserved area (120 bytes) till the offset 0x1F0*/
    unsigned int   confirmation;    /**< \brief 0x1F0: 32-bit CODE, (always same)*/
} Ifx_Ssw_Bmhd;

#pragma section farrom "bmhd_origin"
#pragma protect
/*const Ifx_Ssw_Bmhd bmhd_0_orig __at(0xaf400000) = {*/
const Ifx_Ssw_Bmhd bmhd_0_orig = {
    0x00FE,                                                                     /**< \brief 0x000: .bmi: Boot Mode Index (BMI)*/
    0xB359,                                                                     /**< \brief 0x002: .bmhdid: Boot Mode Header ID (CODE) = B359H*/
    0xA0000000,                                                                 /**< \brief 0x004: .stad: User Code start address*/
    0x31795570,                                                                 /**< \brief 0x008: .crc: Check Result for the BMI Header (offset 000H - 007H)*/
    0xCE86AA8F,                                                                 /**< \brief 0x00C: .crcInv: Inverted Check Result for the BMI Header (offset 000H - 007H)*/
    {                                                                           /*Col:1,      2,      3,      4,      5,      6,      7,      8,      9,     10,     11,     12 */
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, /*Row: 1*/
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, /*Row: 2*/
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, /*Row: 3*/
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, /*Row: 4*/
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, /*Row: 5*/
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, /*Row: 6*/
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, /*Row: 7*/
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, /*Row: 8*/
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, /*Row: 9*/
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, /*Row:10*/
    },                                                                          /**< \brief 0x010: Reserved area 120 x 4= 480 bytes filled with zeros */
    0x43211234                                                                  /**< \brief 0x1F0: .confirmation: 32-bit CODE, (always same)*/
};

#pragma section farrom "bmhd_copy"
#pragma protect
/*const Ifx_Ssw_Bmhd bmhd_0_copy __at(0xaf401000) = {*/
const Ifx_Ssw_Bmhd bmhd_0_copy = {
    0x00FE,                                                                     /**< \brief 0x000: .bmi: Boot Mode Index (BMI)*/
    0xB359,                                                                     /**< \brief 0x002: .bmhdid: Boot Mode Header ID (CODE) = B359H*/
    0xA0000000,                                                                 /**< \brief 0x004: .stad: User Code start address*/
    0x31795570,                                                                 /**< \brief 0x008: .crc: Check Result for the BMI Header (offset 000H - 007H)*/
    0xCE86AA8F,                                                                 /**< \brief 0x00C: .crcInv: Inverted Check Result for the BMI Header (offset 000H - 007H)*/
    {                                                                           /*Col:1,      2,      3,      4,      5,      6,      7,      8,      9,     10,     11,     12 */
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, /*Row: 1*/
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, /*Row: 2*/
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, /*Row: 3*/
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, /*Row: 4*/
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, /*Row: 5*/
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, /*Row: 6*/
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, /*Row: 7*/
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, /*Row: 8*/
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, /*Row: 9*/
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, /*Row:10*/
    },                                                                          /**< \brief 0x010: Reserved area 120 x 4= 480 bytes filled with zeros */
    0x43211234                                                                  /**< \brief 0x1F0: .confirmation: 32-bit CODE, (always same)*/
};

#pragma section farrom restore
/* Internal function called only from Assembly code for startup feature
 * - initialise the free CSA list. DO NOT CALL FROM C!
 * */
void BoardInitCsaList(void)
{
    register uint32 align;
    register uint32 cx;
    register board_uppercx_t *pcx;
    register uint32 nCx;
    register uint32 i;

    /* Force the CSA start address to the correct alignment (64 bytes)
     * Lower 6 bits must be zero, and we always round upwards.
     */
    align = (((uint32) &BOARD_CSAMEMORY_BEGIN) + 0x3fu) & 0xffffffc0u;
    pcx = (board_uppercx_t *) align;
    cx = Platforms_CxFromAddr(align);

    /* Force the CSA end address to the correct alignment (64 bytes)
     * Lower 6 bits must be zero, and we always round downwards.
     */
    align = ((uint32) &BOARD_CSAMEMORY_END) & 0xffffffc0u;
    nCx = (align - (uint32) pcx) >> 6;

    /* Check that we have enough CSAs available:
     * - PLATFORMS_CSAMEMORY_BEGIN must be smaller then PLATFORMS_CSAMEMORY_END
     * - Number of CSAs must be greater than N_CSA_EXTRA so that we have at least
     *   1 CSA in the main list to work with before we go to exception handling
     */
    if (((uint32) &BOARD_CSAMEMORY_BEGIN >= (uint32) &BOARD_CSAMEMORY_END)
            || (nCx <= PLATFORMS_N_CSA_EXTRA))
    {
        /* can't continue: not enough CSAs */
        BoardPerformReset(PLATFORMS_SW_RESET);
    }

    /* Head of the list.
     */
    PLATFORMS_MTCR(PLATFORMS_FCX, cx);

    /* Set limit register (exception occurs when FCX gets here).
     * This assumes that nCx is greater than N_CSA_EXTRA which is checked above.
     */
    PLATFORMS_MTCR(PLATFORMS_LCX, cx + (nCx - PLATFORMS_N_CSA_EXTRA));

    /* CSA list, including "normal" CSAs and extra CSAs for handling exceptions.
     * We initialise 1 CSA fewer than we have in this loop because the final CSA's
     * link must be zero.
     */
    for (i = 0; i < (nCx - 1u); i++)
    {
        cx++;
        pcx[i].pcxi = cx;
    }

    /* Tail of list. Another exception occurs when FCX is 0,
     * but we can't handle it because there are no CSAs!
     */
    pcx[i].pcxi = 0;

    PLATFORMS_RFJL();
    /* Special "return" */
}

/*
 * !LINKSTO OsekCore.Platforms.Startup.007, 1
 * !LINKSTO OsekCore.Platforms.Startup.009, 1
 */
#if (PLATFORMS_TOOLCHAIN == PLATFORMS_tasking)
void BoardInitCData(void)
{
	 register char * p;
	    register char * q;
	    for ( p = &__STARTDATA, q = &__INITDATA; p < &__ENDDATA; p++, q++ )
	    {
	        *p = *q;
	    }

	    for ( p = &__STARTBSS; p < &__ENDBSS; p++ )
	    {
	        *p = 0;
	    }
}
#endif /*#if (PLATFORMS_TOOLCHAIN == PLATFORMS_tasking)*/

void BoardWriteEndinit(uint32 state)
{
    BoardWriteEndInitAurix(state, Board_safetyWdt);
    BoardWriteEndInitAurix(state, Board_cpuWdt);
}

void BoardWriteEndInitAurix(uint32 state, platforms_tc_wdt_t *pWdt)
{
    uint32 modify, password, ei, wmode, lsfr, lsb;
    PLATFORMS_DSYNC();

    /* This is the target value of the ENDINIT bit
     */
    ei = (state == 0) ? 0u : PLATFORMS_ENDINIT;

    /* This is a local copy of the WDTxSR, from which we use the PAS and TCS bits.
     */
    wmode = pWdt->wdt_sr;

    /* Read the current password and re-invert the bits that are supplied inverted.
     * Also clear the LCK bit.
     */
    password = ((pWdt->wdt_con[0] ^ PLATFORMS_WDT_PW_INV)
            & ((uint32) ~(uint32) PLATFORMS_WDT_LCK)) | PLATFORMS_ENDINIT;

    /* Calculate the value to use in the modify access.
     * This value sets the LCK bit again and has ENDINIT as requested.
     */
    modify = (password & ((uint32) ~(uint32) PLATFORMS_ENDINIT))
            | PLATFORMS_WDT_LCK | ei;

    if ((wmode & PLATFORMS_WDT_PAS) != 0)
    {
        /* Calculate the next password from the current password. This first step isolates
         * the existing password.
         */
        lsfr = password & PLATFORMS_WDT_PW;

        /* Calculate XOR of bits 15, 14, 13 and 3 into bit 2. The other bits contain junk after all the
         * shifting and XORing, so discard them.
         */
        lsb = ((lsfr >> 13) ^ (lsfr >> 12) ^ (lsfr >> 11) ^ (lsfr >> 1))
                & PLATFORMS_WDT_PW_LSB;

        /* Calculate the lsfr shifted left. Discard the upper bit of the field.
         * This shifts a zero into the LSB.
         */
        lsfr = (lsfr << 1) & PLATFORMS_WDT_PW;

        /* Put the shifted password and the calculated lsb back into the password field.
         */
        password = (password & ((uint32) ~(uint32) PLATFORMS_WDT_PW)) | lsfr
                | lsb;
    }

    if ((wmode & PLATFORMS_WDT_TCS) != 0)
    {
        /* Calculate the time estimate for the password. This uses the fact that the TIM field of
         * WDTxSR is in the same place (upper 16 bits) as the REL field of WDTxCON0.
         * The TIMEGUESS must be shifted up there too.
         */
        password = (password & ~PLATFORMS_WDT_REL)
                | ((~(pWdt->wdt_sr + PLATFORMS_WDT_TIMEGUESS))
                        & PLATFORMS_WDT_REL);
    }

    /* Perform "Password Access" to WDTxCON0 to clear the LCK bit and enable modification of ENDINIT.
     */
    pWdt->wdt_con[0] = password;

    /* Perform "Modify Access" to WDTxCON0 to change ENDINIT and set the LCK bit again.
     */
    pWdt->wdt_con[0] = modify;

    /* Wait until ENDINIT really is the expected value.
     */
    ulBoardInfiniteLoop = 0;
    while ((pWdt->wdt_con[0] & PLATFORMS_ENDINIT) != ei)
    {
        /* If the processor hangs here, the password was probably wrong. */
      ulBoardInfiniteLoop++;
    }
    BOARD_CHECK_INFINITE_LOOP(ulBoardInfiniteLoop);


}
