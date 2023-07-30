/* Platforms_asm_TRICORE.h
 *
 * This file includes the appropriate Platforms_asm_PA_xxx.h include file * depending on the chosen toolchain.
 *
 * Macros are defined that permit the same source files to be processed by the assemblers of
 * all toolchains. This is done by including the appropriate toolchain file.
 * The assembler memory-map file is also included if appropriate.
 *
 *
 * $Id: Platforms_asm_PA.h 18289 2014-06-12 15:16:16Z mist8519 $
 */
#ifndef __PLATFORMS_ASM_TRICORE_H
#define __PLATFORMS_ASM_TRICORE_H

#include <Platforms_defs.h>

/* Include the appropriate abstraction file for the toolchain
 */
#if (PLATFORMS_TOOLCHAIN==PLATFORMS_tasking)
#include "Platforms_asm_TRICORE_tasking.h"
#elif (PLATFORMS_TOOLCHAIN==PLATFORMS_dcc)
#include "../TRICORE/dcc/Platforms_asm_TRICORE_dcc.h"
#else
#error "Unknown or unsupported toolchain. Check your Makefiles!"
#endif

/* ***********************
 * Core  Register        *
 * **********************/
#if (TS_ARCH_DERIVATE == TS_TC1782)
#define PLATFORMS_CORE_ID  0xfe18  /* core id register */
#else
#define PLATFORMS_CORE_ID  0xfe1c  /* core id register */
#endif

/* ***********************
 * PSW Register          *
 * **********************/
#define PLATFORMS_N_CSA_EXTRA 6

#define PLATFORMS_PCXI   0xfe00  /* Previous context information register */
#define PLATFORMS_PSW    0xfe04  /* Program status word */
#define PLATFORMS_PC     0xfe08  /* Program counter */
#if (TS_ARCH_DERIVATE == TS_TC275 || (TS_ARCH_DERIVATE == TS_TC277))
#define PLATFORMS_DBITEN 0xfe0c  /* Register bank dual bit enable register */
#endif
#define PLATFORMS_SYSCON 0xfe14  /* System configuration register */
#define PLATFORMS_BIV    0xfe20  /* Base address of interrupt vector table */
#define PLATFORMS_BTV    0xfe24  /* Base address of trap vector table */
#define PLATFORMS_ISP    0xfe28  /* Interrupt stack pointer */
#define PLATFORMS_ICR    0xfe2c  /* Interrupt unit control register */
#define PLATFORMS_FCX    0xfe38  /* Free CSA list head pointer */
#define PLATFORMS_LCX    0xfe3c  /* Free CSA list limit pointer */

/* Bit definitions for PSW */
#define PLATFORMS_PSW_C        0x80000000    /* Carry */
#define PLATFORMS_PSW_V        0x40000000    /* Overflow */
#define PLATFORMS_PSW_SV       0x20000000    /* Sticky overflow */
#define PLATFORMS_PSW_AV       0x10000000    /* Advanced overflow */
#define PLATFORMS_PSW_SAV      0x08000000    /* Sticky advanced overflow */
#define PLATFORMS_PSW_PRS      0x00003000    /* Protection register set */
#define PLATFORMS_PSW_PRS_0    0x00000000    /*  --- Protection register set 1 */
#define PLATFORMS_PSW_PRS_1    0x00001000    /*  --- Protection register set 2 */
#define PLATFORMS_PSW_PRS_2    0x00002000    /*  --- Protection register set 3 */
#define PLATFORMS_PSW_PRS_3    0x00003000    /*  --- Protection register set 4 */
#define PLATFORMS_PSW_IO       0x00000C00    /* I/O privelege mode. */
#define PLATFORMS_PSW_IO_U0    0x00000000    /*  --- User 0 */
#define PLATFORMS_PSW_IO_U1    0x00000400    /*  --- User 1 */
#define PLATFORMS_PSW_IO_SU    0x00000800    /*  --- Supervisor */
#define PLATFORMS_PSW_IO_RES   0x00000C00    /*  --- Reserved */
#define PLATFORMS_PSW_IS       0x00000200    /* Interrupt stack in use */
#define PLATFORMS_PSW_GW       0x00000100    /* Global register write perm. */
#define PLATFORMS_PSW_CDE      0x00000080    /* Call depth count enable */
#define PLATFORMS_PSW_CDC      0x0000007F    /* Call depth counter */
#define PLATFORMS_PSW_CDC_DIS  0x0000007F    /*  --- Disable call depth ctr */
#define PLATFORMS_PSW_CDC_6    0x00000000    /*  --- 6-bit call depth counter */
#define PLATFORMS_PSW_CDC_5    0x00000040    /*  --- 5-bit call depth counter */
#define PLATFORMS_PSW_CDC_4    0x00000060    /*  --- 4-bit call depth counter */
#define PLATFORMS_PSW_CDC_3    0x00000070    /*  --- 3-bit call depth counter */
#define PLATFORMS_PSW_CDC_2    0x00000078    /*  --- 2-bit call depth counter */
#define PLATFORMS_PSW_CDC_1    0x0000007C    /*  --- 1-bit call depth counter */
#define PLATFORMS_PSW_CDC_TRA  0x0000007E    /*  --- Call trace */

/* ***********************
 * Interrupt Controller  *
 * **********************/
#if ( (TS_ARCH_DERIVATE == TS_TC275) || (TS_ARCH_DERIVATE == TS_TC21XL) \
		|| (TS_ARCH_DERIVATE == TS_TC277) || (TS_ARCH_DERIVATE == TS_TC297) || (TS_ARCH_DERIVATE == TS_TC39XX) || (TS_ARCH_DERIVATE == TS_TC38XQ) || (TS_ARCH_DERIVATE == TS_TC23XL) )
#define PLATFORMS_ICR_IE     0x00008000u  /* Interrupt enable. */
#define PLATFORMS_ICR_PIPN   0x00FF0000u  /* Pending interrupt priority */
#define PLATFORMS_ICR_CCPN   0x000000FFu  /* Current CPu priority number. */
#elif (TS_ARCH_DERIVATE == TS_TC1782)
#define PLATFORMS_ICR_IE			0x00000100		/* Interrupt enable. */
#define PLATFORMS_ICR_PIPN          0x00FF0000u  /* Pending interrupt priority */
#define PLATFORMS_ICR_CCPN          0x000000FFu  /* Current CPu priority number. */
#define	PLATFORMS_ICR_CONEC		    0x04000000		/* CPU cycles per arb. cycle */
#define PLATFORMS_ICR_CONEC_1		0x04000000		/*	--- 1 clock cycle */
#define PLATFORMS_ICR_CONEC_2		0x00000000		/*	--- 2 clock cycles */
#define PLATFORMS_ICR_CARBCYC		0x03000000		/* No. of arbitration cycles */
#define PLATFORMS_ICR_CARBCYC_4	    0x00000000		/*	--- 4 --> interrupts 1..255 */
#define PLATFORMS_ICR_CARBCYC_3	    0x01000000		/*	--- 3 --> interrupts 1..63 */
#define PLATFORMS_ICR_CARBCYC_2	    0x02000000		/*	--- 2 --> interrupts 1..15 */
#define PLATFORMS_ICR_CARBCYC_1	    0x03000000		/*	--- 1 --> interrupts 1..3 */

#else
#error "unsupported CPU for PLL settings"
#endif

/* ***********************
 * PLL Register          *
 * **********************/
#if ( (TS_ARCH_DERIVATE == TS_TC275) || (TS_ARCH_DERIVATE == TS_TC21XL) \
		|| (TS_ARCH_DERIVATE == TS_TC277) || (TS_ARCH_DERIVATE == TS_TC297) || (TS_ARCH_DERIVATE == TS_TC39XX) || (TS_ARCH_DERIVATE == TS_TC38XQ) || (TS_ARCH_DERIVATE == TS_TC23XL))
#define PLATFORMS_PLL_SET_P(p)   ( ((p)-1u) << 24u )   /* PLLCON0 : 1 <= p <= 16 */
#define PLATFORMS_PLL_SET_N(n)   ( ((n)-1u) << 9u )    /* PLLCON0 : 1 <= n <= 128 */
#define PLATFORMS_PLL_SET_K1(k1) ( ((k1)-1u) << 16u)   /* PLLCON1 : 1 <= k1 <= 128 */
#define PLATFORMS_PLL_SET_K2(k2) ( (k2)-1u)             /* PLLCON1 : 1 <= k2 <= 128 */
#define PLATFORMS_PLL_SET_K3(k3) ( (k3-1) << 8)        /* PLLCON1 : 1 <= k3 <= 15 */

/* pwr_pll_con[0]: Bits for PLL configuration register 0 */
#define PLATFORMS_PLL_RESLD         (0x00040000U)    /* Reset lock detection */
#define PLATFORMS_PLL_PLLPWD        (0x00010000U)    /* Power saving mode (doc incorrect?) */
#define PLATFORMS_PLL_OSCDISCDIS    (0x00000040U)    /* Clear FINDIS on loss of lock */
#define PLATFORMS_PLL_CLRFINDIS     (0x00000020U)    /* Write 1 here to CLEAR FINDIS! */
#define PLATFORMS_PLL_SETFINDIS     (0x00000010U)    /* Disconnect OSC from VCO. */
#define PLATFORMS_PLL_VCOBYP        (0x00000001U)    /* VCO bypass */

/* pwr_pllstat: Bits for PLL status register */
#define PLATFORMS_VCO_LOCK          (0x00000004u)    /* PLL VCO Lock Status */

#define PLATFORMS_CCUCON_LCK_LOCKED                    (0x80000000u) /* Register is locked and can't be updated anymore. */
#define PLATFORMS_CCUCON_UP                            (0x40000000u) /* Update Request */
#define PLATFORMS_CCUCON0_CLKSEL_MASK                  (0x30000000u) /* Mask to select all bits in the CLKSEL field. */
#define PLATFORMS_CCUCON0_CLKSEL_BACKUP_CLK_AS_FSOURCE 0u            /* Use backup clock as f_source. */
#define PLATFORMS_CCUCON0_CLKSEL_PLL_CLK_AS_FSOURCE    (0x10000000u) /* Use PLL output as f_source. */
#define PLATFORMS_CCUCON1_INSEL_MASK                   (0x30000000u) /* Mask to select all bits in the INSEL field. */
#define PLATFORMS_CCUCON1_INSEL_BACKUP_AS_CLK_SOURCE   0     /* Use backup clock as clock source. */
#define PLATFORMS_CCUCON1_INSEL_FOSC_AS_CLK_SOURCE     (0x10000000u) /* Use f_osc as clock source. */

#elif (TS_ARCH_DERIVATE == TS_TC1782)

/* pwr_pll_con[0]: Bits for PLL configuration register 0 */
#define PLATFORMS_PLL_RESLD		0x00040000		/* Reset lock detection */
#define PLATFORMS_PLL_PLLPWD		0x00010000		/* Power saving mode (doc incorrect?) */
#define PLATFORMS_PLL_OSCDISCDIS	0x00000040		/* Clear FINDIS on loss of lock */
#define PLATFORMS_PLL_CLRFINDIS	0x00000020		/* Write 1 here to CLEAR FINDIS! */
#define PLATFORMS_PLL_SETFINDIS	0x00000010		/* Disconnect OSC from VCO. */
#define PLATFORMS_PLL_VCOBYP		0x00000001		/* VCO bypass */

/* pwr_pllstat: Bits for PLL status register */
#define PLATFORMS_VCO_LOCK			0x00000004		/* PLL VCO Lock Status */

#define PLATFORMS_PLL_SET_P(p)		( (p-1) << 24 )		/* PLLCON0 : 1 <= p <= 16 */
#define PLATFORMS_PLL_SET_N(n)		( (n-1) << 9 )		/* PLLCON0 : 1 <= n <= 128 */
#define PLATFORMS_PLL_SET_K1(k1)	( (k1-1) << 16)		/* PLLCON1 : 1 <= k1 <= 128 */
#define PLATFORMS_PLL_SET_K2(k2)	(k2-1)				/* PLLCON1 : 1 <= k2 <= 128 */

#else
#error "unsupported CPU for PLL settings"
#endif

#ifndef BOARD_ASM

#if (TS_ARCH_DERIVATE == TS_TC1782)
 /* System Timer 0 */
#define PLATFORMS_SRC_STM0SR0 (*(volatile uint32 *)(0xF00002FCu))
#define PLATFORMS_SRC_STM0SR1 (*(volatile uint32 *)(0xF00002F8u))

/*  SRC register bit */
#define PLATFORMS_SRC_SRE       0x00001000u
#define PLATFORMS_SRC_TOS_CPU   0x00000000u
#define PLATFORMS_SRC_TOS_PCP   0x00000400u

/* SRC set request bit */
#define PLATFORMS_SRC_SETR_MASK  0x00008000u
#define PLATFORMS_SRC_SPRN_PRIO(x) (u32)((u32)x & (u32)0x000000FF) /* SRPN is between 1 and 255*/
#endif  /* TS_TC1782 */
 
/* SRC registers as defined in AuRIX Target Specification V1.4.1 2014-02 ?17 */
#if (TS_ARCH_DERIVATE == TS_TC1782)	
#define PLATFORMS_SRCBASE  0xf0004000u
#else
#define PLATFORMS_SRCBASE  0xf0038000u
#endif /* TS_TC1782 */

/* LIN 0 */
#if ((TS_ARCH_DERIVATE == TS_TC39XX) || (TS_ARCH_DERIVATE == TS_TC38XQ))
#define PLATFORMS_SRC_ASCLIN0TX (*(volatile uint32 *)(PLATFORMS_SRCBASE+0x0050u))
#define PLATFORMS_SRC_ASCLIN0RX (*(volatile uint32 *)(PLATFORMS_SRCBASE+0x0054u))
#define PLATFORMS_SRC_ASCLIN0EX (*(volatile uint32 *)(PLATFORMS_SRCBASE+0x0058u))
#else
#define PLATFORMS_SRC_ASCLIN0TX (*(volatile uint32 *)(PLATFORMS_SRCBASE+0x0080u))
#define PLATFORMS_SRC_ASCLIN0RX (*(volatile uint32 *)(PLATFORMS_SRCBASE+0x0084u))
#define PLATFORMS_SRC_ASCLIN0EX (*(volatile uint32 *)(PLATFORMS_SRCBASE+0x0088u))
#endif

/* LIN 1 */

#if ((TS_ARCH_DERIVATE == TS_TC39XX) || (TS_ARCH_DERIVATE == TS_TC38XQ))
#define PLATFORMS_SRC_ASCLIN1TX (*(volatile uint32 *)(PLATFORMS_SRCBASE+0x005Cu))
#define PLATFORMS_SRC_ASCLIN1RX (*(volatile uint32 *)(PLATFORMS_SRCBASE+0x0060u))
#define PLATFORMS_SRC_ASCLIN1EX (*(volatile uint32 *)(PLATFORMS_SRCBASE+0x0064u))
#else
#define PLATFORMS_SRC_ASCLIN1TX (*(volatile uint32 *)(PLATFORMS_SRCBASE+0x008Cu))
#define PLATFORMS_SRC_ASCLIN1RX (*(volatile uint32 *)(PLATFORMS_SRCBASE+0x0090u))
#define PLATFORMS_SRC_ASCLIN1EX (*(volatile uint32 *)(PLATFORMS_SRCBASE+0x0094u))
#endif

#if ((TS_ARCH_DERIVATE == TS_TC275) || (TS_ARCH_DERIVATE == TS_TC277))
/* LIN 2 */
#define PLATFORMS_SRC_ASCLIN2TX (*(volatile uint32 *)(PLATFORMS_SRCBASE+0x0098u))
#define PLATFORMS_SRC_ASCLIN2RX (*(volatile uint32 *)(PLATFORMS_SRCBASE+0x009Cu))
#define PLATFORMS_SRC_ASCLIN2EX (*(volatile uint32 *)(PLATFORMS_SRCBASE+0x00A0u))

/* LIN 3 */
#define PLATFORMS_SRC_ASCLIN3TX (*(volatile uint32 *)(PLATFORMS_SRCBASE+0x00A4u))
#define PLATFORMS_SRC_ASCLIN3RX (*(volatile uint32 *)(PLATFORMS_SRCBASE+0x00A8u))
#define PLATFORMS_SRC_ASCLIN3EX (*(volatile uint32 *)(PLATFORMS_SRCBASE+0x00ACu))
#endif /* #if ((TS_ARCH_DERIVATE == TS_TC275) || (TS_ARCH_DERIVATE == TS_TC277)) */

#if (TS_ARCH_DERIVATE != TS_TC1782)
/* System Timer 0 */
#define PLATFORMS_SRC_STM0SR0 (*(volatile uint32 *)(PLATFORMS_SRCBASE+0x0490u))
#define PLATFORMS_SRC_STM0SR1 (*(volatile uint32 *)(PLATFORMS_SRCBASE+0x0494u))
#endif

#if ((TS_ARCH_DERIVATE == TS_TC275) || (TS_ARCH_DERIVATE == TS_TC277))
/* System Timer 1 */
#define PLATFORMS_SRC_STM1SR0 (*(volatile uint32 *)(PLATFORMS_SRCBASE+0x0498u))
#define PLATFORMS_SRC_STM1SR1 (*(volatile uint32 *)(PLATFORMS_SRCBASE+0x049Cu))

/* System Timer 2 */
#define PLATFORMS_SRC_STM2SR0 (*(volatile uint32 *)(PLATFORMS_SRCBASE+0x04A0u))
#define PLATFORMS_SRC_STM2SR1 (*(volatile uint32 *)(PLATFORMS_SRCBASE+0x04A4u))
#endif  /* #if ((TS_ARCH_DERIVATE == TS_TC275) || (TS_ARCH_DERIVATE == TS_TC277)) */

/* CAN */
#if (TS_ARCH_DERIVATE == TS_TC1782)

#define PLATFORMS_SRC_CANINT0       (*(volatile uint32 *)(PLATFORMS_SRCBASE + 0x00FCu))
#define PLATFORMS_SRC_CANINT1       (*(volatile uint32 *)(PLATFORMS_SRCBASE + 0x00F8u))
#define PLATFORMS_SRC_CANINT2       (*(volatile uint32 *)(PLATFORMS_SRCBASE + 0x00F4u))
#define PLATFORMS_SRC_CANINT3       (*(volatile uint32 *)(PLATFORMS_SRCBASE + 0x00F0u))
#define PLATFORMS_SRC_CANINT4       (*(volatile uint32 *)(PLATFORMS_SRCBASE + 0x00ECu))
#define PLATFORMS_SRC_CANINT5       (*(volatile uint32 *)(PLATFORMS_SRCBASE + 0x00E8u))
#define PLATFORMS_SRC_CANINT6       (*(volatile uint32 *)(PLATFORMS_SRCBASE + 0x00E4u))
#define PLATFORMS_SRC_CANINT7       (*(volatile uint32 *)(PLATFORMS_SRCBASE + 0x00E0u))
#define PLATFORMS_SRC_CANINT8       (*(volatile uint32 *)(PLATFORMS_SRCBASE + 0x00DCu))
#define PLATFORMS_SRC_CANINT9       (*(volatile uint32 *)(PLATFORMS_SRCBASE + 0x00D8u))
#define PLATFORMS_SRC_CANINT10      (*(volatile uint32 *)(PLATFORMS_SRCBASE + 0x00D4u))
#define PLATFORMS_SRC_CANINT11      (*(volatile uint32 *)(PLATFORMS_SRCBASE + 0x00D0u))
#define PLATFORMS_SRC_CANINT12      (*(volatile uint32 *)(PLATFORMS_SRCBASE + 0x00CCu))
#define PLATFORMS_SRC_CANINT13      (*(volatile uint32 *)(PLATFORMS_SRCBASE + 0x00C8u))
#define PLATFORMS_SRC_CANINT14      (*(volatile uint32 *)(PLATFORMS_SRCBASE + 0x00C4u))
#define PLATFORMS_SRC_CANINT15      (*(volatile uint32 *)(PLATFORMS_SRCBASE + 0x00C0u))



#endif	/* #if (TS_ARCH_DERIVATE == TS_TC1782) */
#if (TS_ARCH_DERIVATE == TS_TC38XQ)
#define PLATFORMS_SRC_CANINT0 (*(volatile uint32 *)(PLATFORMS_SRCBASE+0x40u+0x05B0u))
#define PLATFORMS_SRC_CANINT1 (*(volatile uint32 *)(PLATFORMS_SRCBASE+0x40u+0x05B4u))
#define PLATFORMS_SRC_CANINT2 (*(volatile uint32 *)(PLATFORMS_SRCBASE+0x40u+0x05B8u))
#define PLATFORMS_SRC_CANINT3 (*(volatile uint32 *)(PLATFORMS_SRCBASE+0x40u+0x05BCu))
#define PLATFORMS_SRC_CANINT4 (*(volatile uint32 *)(PLATFORMS_SRCBASE+0x40u+0x05C0u))
#define PLATFORMS_SRC_CANINT5 (*(volatile uint32 *)(PLATFORMS_SRCBASE+0x40u+0x05C4u))
#define PLATFORMS_SRC_CANINT6 (*(volatile uint32 *)(PLATFORMS_SRCBASE+0x40u+0x05C8u))
#define PLATFORMS_SRC_CANINT7 (*(volatile uint32 *)(PLATFORMS_SRCBASE+0x40u+0x05CCu))
#define PLATFORMS_SRC_CANINT8 (*(volatile uint32 *)(PLATFORMS_SRCBASE+0x40u+0x05D0u))
#define PLATFORMS_SRC_CANINT9 (*(volatile uint32 *)(PLATFORMS_SRCBASE+0x40u+0x05D4u))
#define PLATFORMS_SRC_CANINT10 (*(volatile uint32 *)(PLATFORMS_SRCBASE+0x40u+0x05D8u))
#define PLATFORMS_SRC_CANINT11 (*(volatile uint32 *)(PLATFORMS_SRCBASE+0x40u+0x05DCu))
#define PLATFORMS_SRC_CANINT12 (*(volatile uint32 *)(PLATFORMS_SRCBASE+0x40u+0x05E0u))
#define PLATFORMS_SRC_CANINT13 (*(volatile uint32 *)(PLATFORMS_SRCBASE+0x40u+0x05E4u))
#define PLATFORMS_SRC_CANINT14 (*(volatile uint32 *)(PLATFORMS_SRCBASE+0x40u+0x05E8u))
#define PLATFORMS_SRC_CANINT15 (*(volatile uint32 *)(PLATFORMS_SRCBASE+0x40u+0x05ECu))
#endif   /* #if (TS_ARCH_DERIVATE == TS_TC38XQ) */

/* CAN 1 */
#if ((TS_ARCH_DERIVATE == TS_TC21XL) || (TS_ARCH_DERIVATE == TS_TC277))
#define PLATFORMS_SRC_CAN1INT0 (*(volatile uint32 *)(PLATFORMS_SRCBASE+0x0940u))
#define PLATFORMS_SRC_CAN1INT1 (*(volatile uint32 *)(PLATFORMS_SRCBASE+0x0944u))
#define PLATFORMS_SRC_CAN1INT2 (*(volatile uint32 *)(PLATFORMS_SRCBASE+0x0948u))
#define PLATFORMS_SRC_CAN1INT3 (*(volatile uint32 *)(PLATFORMS_SRCBASE+0x094Cu))
#define PLATFORMS_SRC_CAN1INT4 (*(volatile uint32 *)(PLATFORMS_SRCBASE+0x0950u))
#define PLATFORMS_SRC_CAN1INT5 (*(volatile uint32 *)(PLATFORMS_SRCBASE+0x0954u))
#define PLATFORMS_SRC_CAN1INT6 (*(volatile uint32 *)(PLATFORMS_SRCBASE+0x0958u))
#define PLATFORMS_SRC_CAN1INT7 (*(volatile uint32 *)(PLATFORMS_SRCBASE+0x095Cu))
#endif /* #if ((TS_ARCH_DERIVATE == TS_TC21XL) || (TS_ARCH_DERIVATE == TS_TC277)) */

#define PLATFORMS_SRC_ERAYINT0 (*(volatile uint32 *)(PLATFORMS_SRCBASE+0x0BE0u))
#define PLATFORMS_SRC_ERAYINT1 (*(volatile uint32 *)(PLATFORMS_SRCBASE+0x0BE4u))
#define PLATFORMS_SRC_ERAYTINT0 (*(volatile uint32 *)(PLATFORMS_SRCBASE+0x0BE8u))
#define PLATFORMS_SRC_ERAYTINT1 (*(volatile uint32 *)(PLATFORMS_SRCBASE+0x0BECu))
#define PLATFORMS_SRC_ERAYNDAT0 (*(volatile uint32 *)(PLATFORMS_SRCBASE+0x0BF0u))
#define PLATFORMS_SRC_ERAYNDAT1 (*(volatile uint32 *)(PLATFORMS_SRCBASE+0x0BF4u))
#define PLATFORMS_SRC_ERAYMBSC0 (*(volatile uint32 *)(PLATFORMS_SRCBASE+0x0BF8u))
#define PLATFORMS_SRC_ERAYMBSC1 (*(volatile uint32 *)(PLATFORMS_SRCBASE+0x0BFCu))
#define PLATFORMS_SRC_ERAYOBUSY (*(volatile uint32 *)(PLATFORMS_SRCBASE+0x0C00u))
#define PLATFORMS_SRC_ERAYIBUSY (*(volatile uint32 *)(PLATFORMS_SRCBASE+0x0C04u))

#if (TS_ARCH_DERIVATE != TS_TC1782)
#define PLATFORMS_SRC_SRE        0x00000400u
#define PLATFORMS_SRC_TOS_CPU0   0x00000000u
#define PLATFORMS_SRC_TOS_CPU1   0x00000800u
#endif

#if ((TS_ARCH_DERIVATE == TS_TC275) || (TS_ARCH_DERIVATE == TS_TC277))
#define PLATFORMS_SRC_TOS_CPU2   0x00001000u
#define PLATFORMS_SRC_TOS_DMA    0x00001800u
#endif  /* #if ((TS_ARCH_DERIVATE == TS_TC275) || (TS_ARCH_DERIVATE == TS_TC277)) */

#define PLATFORMS_SRC_SPRN_PRIO(x) (u32)((u32)x & (u32)0x000000FF) /* SRPN is between 1 and 255*/

#if (TS_ARCH_DERIVATE != TS_TC1782)
#define PLATFORMS_SRC_SETR_MASK  0x04000000u
#endif

#define PLATFORMS_SRN_SETR   0x04000000u  /* Request set bit */
#define PLATFORMS_SRN_CLRR   0x02000000u  /* Request clear bit */
#define PLATFORMS_SRN_SRR    0x01000000u  /* Service request bit */
/* The AuRIX TC277 has only one DMA engine and three CPus, thus at most four service providers. */
#define PLATFORMS_SRN_TOS    0x00001800u  /* Type of service */
#define PLATFORMS_SRN_SRE    0x00000400u  /* Service request enable */
#define PLATFORMS_SRN_SRPN   0x000000ffu  /* Priority */

/* TC21x & TC275 registers end */

typedef struct board_uppercx_s
{
    volatile uint32 pcxi; /* link word */
    volatile uint32 psw; /* processor status word */
    volatile uint32 a10; /* Stack pointer. */
    volatile uint32 a11; /* Return address register. */
    volatile uint32 d8;
    volatile uint32 d9;
    volatile uint32 d10;
    volatile uint32 d11;
    volatile uint32 a12;
    volatile uint32 a13;
    volatile uint32 a14;
    volatile uint32 a15;
    volatile uint32 d12;
    volatile uint32 d13;
    volatile uint32 d14;
    volatile uint32 d15;
} board_uppercx_t;

typedef struct platforms_tc_wdt_s
{
    volatile uint32 wdt_con[2]; /* WDTxxxCON0 and WDTxxxCON1 */
    volatile uint32 wdt_sr; /* WDTxxxSR Status */
} platforms_tc_wdt_t;

#if (TS_ARCH_DERIVATE == TS_TC1782)
/* Watchdog Timer Control Register 0 */
#define PLATFORMS_ENDINIT			0x00000001		/* End of initialisation control */
#define PLATFORMS_WDTLCK			0x00000002		/* Lock */
#define PLATFORMS_WDTHPW0_MSK		0x0000000C		/* Hardware password 0 */
#define PLATFORMS_WDTHPW1_MSK		0x000000F0		/* Hardware password 1 */
#define PLATFORMS_WDTPW_MSK			0x0000FF00		/* User definable password */
#define PLATFORMS_WDTREL_MSK		0xFFFF0000		/* Reload value for watchdog timer */

/* Watchdog Timer Control Register 1 */
#define PLATFORMS_WDTIR			0x00000004		/* Input frequency request control */
#define PLATFORMS_WDTDR			0x00000008		/* Disable request control */
#define PLATFORMS_SCKCLR_MSK		0x00000700		/* Self check clear request */

/* Watchdog Timer Status Register */
#define PLATFORMS_WDTAE			0x00000001		/* Access error */
#define PLATFORMS_WDTOE			0x00000002		/* Overflow error */
#define PLATFORMS_WDTIS			0x00000004		/* Input clock status */
#define PLATFORMS_WDTDS			0x00000008		/* Enable/disable */
#define PLATFORMS_WDTTO			0x00000010		/* Time out period */
#define PLATFORMS_WDTPR			0x00000020		/* Reset prewarning */
#define PLATFORMS_SCKERR_MSK	0x0000FF00		/* Self check error bits */
#else
/* Bit fields in the WDT registers (only those that are used in the OS).
 * For a full description please refer to the Infineon documentation.
 */
#define PLATFORMS_WDT_REL    0xffff0000u /* WDTxCON0.REL */
#define PLATFORMS_WDT_PW     0x0000fffcu /* WDTxCON0.PW */
#define PLATFORMS_WDT_PW_INV 0x000000fcu /* WDTxCON0.PW (inverted portion) */
#define PLATFORMS_WDT_PW_LSB 0x00000004u /* WDTxCON0.PW (lsb) */
#define PLATFORMS_WDT_LCK    0x00000002u /* WDTxCON0.LCK */
#define PLATFORMS_ENDINIT    0x00000001u /* WDTxCON0.ENDINIT */

#define PLATFORMS_WDT_PAS    0x00000080u /* WDTxSR.PAS */
#define PLATFORMS_WDT_TCS    0x00000100u /* WDTxSR.TCS */
#endif /* #if (TS_ARCH_DERIVATE == TS_TC1782) */
/* The time taken for the computation of the final password from the WDTxSR TIM field.
 * Let's take a guess: 1 tick should be enough.
 */
#define PLATFORMS_WDT_TIMEGUESS  0x00010000u /* Estimated time for password computation */

typedef struct platforms_tc_kernel_s
{
#if (TS_ARCH_DERIVATE == TS_TC1782)
    volatile uint32 reserved[2]; /* 0x04   Some modules use this! */
    volatile uint32 id; /* 0x08   Module identification register */
	volatile uint32	reserved1[1];	/* 0x00c */
	volatile uint32	pwr_osccon;		/* 0x010  OSC Control Register */
	volatile uint32	pwr_pllstat;	/* 0x014  PLL Status Register */
	volatile uint32	pwr_pllcon[2];	/* 0x018+ PLL Configuration Register */
	volatile uint32	reserved2[1];		/* 0x020 */
	volatile uint32	pwr_plleraystat;	/* 0x024  PLL ERAY Status Register */
	volatile uint32	pwr_plleraycon[2];	/* 0x028+ PLL ERAY Configuration Register */
	volatile uint32	pwr_ccucon[2];	/* 0x030+ CCu Control Register */
	volatile uint32	pwr_fdr;		/* 0x038  Fractional Divider Register */
	volatile uint32	pwr_extcon;		/* 0x03c  External Clock Control Register */
	volatile uint32	pwr_syscon;		/* 0x040  System Control Register */
	volatile uint32	reserved3[3];	/* 0x044 */
	volatile uint32	pwr_rststat;	/* 0x050  Reset Status Register */
	volatile uint32	pwr_rstcntcon;	/* 0x054  Reset Counter Control Register */
	volatile uint32	pwr_rstcon;		/* 0x058  Reset CON Register */
	volatile uint32	pwr_arstdis;	/* 0x05c  Application Reset Disable Register*/
	volatile uint32	pwr_swrstcon;	/* 0x060  Software Reset Configuration Register*/
	volatile uint32	reserved4[3];	/* 0x064 */
	volatile uint32	pwr_esrcfg[3];	/* ESR Configuration Register */
	volatile uint32	reserved5[1];	/* 0x07C*/
	volatile uint32	pwr_eicr[2];	/* 0x080+ External Input Channel Register */
	volatile uint32	pwr_eifr;		/* 0x088  External Input Flag Regsiter */
	volatile uint32	pwr_fmr;		/* 0x08c  Flag Modification Register */
	volatile uint32	pwr_pdrr;		/* 0x090  Pattern Detection Result Register */
	volatile uint32	pwr_igcr[2];	/* 0x094+ Interrupt Gating Register */
	volatile uint32	reserved6[1];	/* 0x09c */
	volatile uint32	pwr_iocr;		/* 0x0a0  Input/Output Control Register */
	volatile uint32	pwr_out;		/* 0x0a4  Output Register */
	volatile uint32	pwr_omr;		/* 0x0a8  Output Modification Register*/
	volatile uint32	pwr_in;			/* 0x0ac  Input Register */
	volatile uint32	pwr_pmcsr;		/* 0x0b0  Power Management Control and Status Register */
	volatile uint32	reserved7[3];	/* 0x0b4+ */
	volatile uint32	pwr_ststat;		/* 0x0c0  Start-up Status Register */
	volatile uint32	pwr_stcon;		/* 0x0c4  Start-up Configuration */
	volatile uint32	reserved8[2];	/* 0x0c8+ */
	volatile uint32	pwr_ecccon;		/* 0x0d0  ECC Error Trap Control */
	volatile uint32	pwr_eccstat;	/* 0x0d4  ECC Error Trap Status */
	volatile uint32	pwr_eccclr;		/* 0x0d8  ECC Error Trap Clear */
	volatile uint32	reserved9[1];	/* 0x0dc */
	volatile uint32	pwr_dtsstat;	/* 0x0e0  Die Temperature Sensor Status Register */
	volatile uint32	pwr_dtscon;		/* 0x0e4  Die Temperature Sensor Control Register */
	volatile uint32	reserved10[2];	/* 0x0e8+ */
    platforms_tc_wdt_t pwr_wdt;     /* 0xof WDT registers */
	volatile uint32	reserved11[1];	/* 0x0fc+ */
	volatile uint32	pwr_emsr;		/* 0x100  Emergency Stop Register */
	volatile uint32	reserved12[3];	/* 0x104+ */
	volatile uint32	pwr_intstat;	/* 0x110  Interrupt Status Register */
	volatile uint32	pwr_intset;		/* 0x114  Interrupt Set Register */
	volatile uint32	pwr_intclr;		/* 0x118  Interrupt Clear Register */
	volatile uint32	pwr_intdis;		/* 0x11c  Interrupt Disable Register */
	volatile uint32	pwr_intnp;		/* 0x120  Interrupt Node Pointer Register */
	volatile uint32	pwr_trapstat;	/* 0x124  Trap Status Register */
	volatile uint32	pwr_trapset;	/* 0x128  Trap Set Register */
	volatile uint32	pwr_trapclr;	/* 0x12c  Trap Clear Register */
	volatile uint32	pwr_trapdis;	/* 0x130  Trap Disable Register */
	volatile uint32	reserved13[3];	/* 0x134+ */
	volatile uint32	pwr_chipid;		/* 0x140  Chip Identification */
	volatile uint32	pwr_manid;		/* 0x144  Manufacture Identification Register */
	volatile uint32	reserved14[42];	/* 0x148 */
#else
    volatile uint32 clc; /* 0x00   Clock control register */
    volatile uint32 reserved; /* 0x04   Some modules use this! */
    volatile uint32 id; /* 0x08   Module identification register */
    volatile uint32 reserved1[1]; /* 0x0C */

    volatile uint32 pwr_osccon; /* 0x10 OSC Control */
    volatile uint32 pwr_pllstat; /* 0x14 PLL Status */
    volatile uint32 pwr_pllcon[3]; /* 0x18 PLL Configuration 0-2 */
    volatile uint32 pwr_plleraystat; /* 0x24 PLL_ERAY Status */
    volatile uint32 pwr_plleraycon[2];/* 0x28 PLL_ERAY Configuration 0 and 1 */
    volatile uint32 pwr_ccucon[2]; /* 0x30 CCu Control 0 and 1 */
    volatile uint32 pwr_fdr; /* 0x38 Fractional Divider */
    volatile uint32 pwr_extcon; /* 0x3C External Clock Control */
    volatile uint32 pwr_ccucon_2[4]; /* 0x40 CCu Control 2, 3, 4 and 5 */
    volatile uint32 pwr_rststat; /* 0x50 Reset Status */
    volatile uint32 reserved3[1]; /* 0x54 */
    volatile uint32 pwr_rstcon; /* 0x58 Reset CON */
    volatile uint32 pwr_arstdis; /* 0x5C Application Reset Disable */
    volatile uint32 pwr_swrstcon; /* 0x60 Software Reset Configuration */
    volatile uint32 pwr_rstcon2; /* 0x64 Additional reset control */
    volatile uint32 reserved4[1]; /* 0x68 */
    volatile uint32 pwr_evrrstcon; /* 0x6C EVR Reset Control */
    volatile uint32 pwr_esrcfg[2]; /* 0x70 ESR0 and 1 Configuration */
    volatile uint32 pwr_esrocfg; /* 0x78 ESR Reset Output Configuration */
    volatile uint32 pwr_syscon; /* 0x7C System Control */
#if ((TS_ARCH_DERIVATE == TS_TC21XL) || (TS_ARCH_DERIVATE == TS_TC277))
    volatile uint32 pwr_ccucon6; /* 0x80 CCu Control 6 */
    volatile uint32 reserved5[2]; /* 0x84 */
    volatile uint32 pwr_ccucon9; /* 0x8C CCu Control 9 */
    volatile uint32 reserved5_1[3]; /* 0x90 */
#else
    volatile uint32 reserved5[7]; /* 0x80 */
#endif
    volatile uint32 pwr_pdr; /* 0x9C Pad Driver Mode */
    volatile uint32 pwr_iocr; /* 0xA0 Input/Output Control */
    volatile uint32 pwr_out; /* 0xA4 Output */
    volatile uint32 pwr_omr; /* 0xA8 Output Modification */
    volatile uint32 pwr_in; /* 0xAC Input */
    volatile uint32 pwr_evrstat; /* 0xB0 EVR Status */
    volatile uint32 reserved6[1]; /* 0xB4 */
    volatile uint32 pwr_evr13con; /* 0xB8 EVR13 Control */
#if ((TS_ARCH_DERIVATE == TS_TC21XL) || (TS_ARCH_DERIVATE == TS_TC277))
    volatile uint32 reserved18; /* 0xBC */
#else
    volatile uint32 pwr_evr33con; /* 0xBC EVR33 Control */
#endif
    volatile uint32 pwr_ststat; /* 0xC0 Start-up Status */
#if ((TS_ARCH_DERIVATE == TS_TC21XL) || (TS_ARCH_DERIVATE == TS_TC277))
    volatile uint32 reserved17;  /* 0xC4 */
#else
    volatile uint32 pwr_stcon; /* 0xC4 Start-up Configuration */
#endif
    volatile uint32 pwr_pmswcr0; /* 0xC8 Standby and Wakeup Control 0 */
    volatile uint32 pwr_pmswstat; /* 0xCC Standby and Wakeup Status */
    volatile uint32 pwr_pmswstatclr; /* 0xD0 Standby and Wakeup Status Clear */
#if ((TS_ARCH_DERIVATE == TS_TC21XL) || (TS_ARCH_DERIVATE == TS_TC277))
    volatile uint32 pwr_pmcsr[1];  /* 0xD4 CPu0 Power Management Control and Status */
    volatile uint32 reserved19[2]; /* 0xD8 */
#else
    volatile uint32 pwr_pmcsr[3]; /* 0xD4 CPu0, 1 and 2 Power Management Control and Status */
#endif
    volatile uint32 pwr_dtsstat; /* 0xE0 Die Temperature Sensor Status */
    volatile uint32 pwr_dtscon; /* 0xE4 Die Temperature Sensor Control */
    volatile uint32 pwr_pmswcr1; /* 0xE8 Standby and Wakeup Control 1 */
    volatile uint32 reserved7[1]; /* 0xEC */
    platforms_tc_wdt_t pwr_swdt; /* 0xF0 Safety WDT */
    volatile uint32 pwr_emsr; /* 0xFC Emergency Stop */
#if ((TS_ARCH_DERIVATE == TS_TC21XL) || (TS_ARCH_DERIVATE == TS_TC277))
    platforms_tc_wdt_t pwr_wdt[1]; /* 0x100 3 CPu WDT modules */
    volatile uint32 reserved20[6]; /* 0x10C */
#else
    platforms_tc_wdt_t pwr_wdt[3]; /* 0x100 3 CPu WDT modules */
#endif
    volatile uint32 pwr_trapstat; /* 0x124 Trap Status */
    volatile uint32 pwr_trapset; /* 0x128 Trap Set */
    volatile uint32 pwr_trapclr; /* 0x12C Trap Clear */
    volatile uint32 pwr_trapdis; /* 0x130 Trap Disable */
    volatile uint32 pwr_lclcon[2]; /* 0x134 CPu0 and 1 Lockstep Control */
    volatile uint32 pwr_lcltest; /* 0x13C Lockstep Test */
    volatile uint32 pwr_chipid; /* 0x140 Chip Identification */
    volatile uint32 pwr_manid; /* 0x144 Manufacture Identification */
    volatile uint32 reserved8[7]; /* 0x148 */
#if ((TS_ARCH_DERIVATE == TS_TC21XL) || (TS_ARCH_DERIVATE == TS_TC277))
    volatile uint32 pwr_lbistctrl[3]; /* 0x164 Logic BIST Control 0, 1 and 2 */
    volatile uint32 reserved9[9]; /* 0x170 */
#else
    volatile uint32 pwr_lbistctrl[2]; /* 0x164 Logic BIST Control 0 and 1 */
    volatile uint32 reserved9[10]; /* 0x16C */
#endif
#if ((TS_ARCH_DERIVATE == TS_TC21XL) || (TS_ARCH_DERIVATE == TS_TC277))
    volatile uint32 reserved16; /* 0x194 */
#else
	volatile uint32 pwr_ccuconsm; /* 0x194 CCu Control Security Monitor */
#endif
#if ((TS_ARCH_DERIVATE == TS_TC21XL) || (TS_ARCH_DERIVATE == TS_TC277))
    volatile uint32 reserved10[1]; /* 0x198 */
#else
	volatile uint32 reserved10[2]; /* 0x198 */
#endif
    volatile uint32 pwr_evruvmon; /* 0x1A0 EVR undervoltage Monitor */
    volatile uint32 pwr_evrovmon; /* 0x1A4 EVR Overvoltage Monitor */
    volatile uint32 pwr_evrmonctrl; /* 0x1A8 EVR Monitor Control */
    volatile uint32 reserved11[1]; /* 0x1AC */
    volatile uint32 pwr_evrsdctrl1; /* 0x1B0 EVR SD Control 1 */
#if ((TS_ARCH_DERIVATE == TS_TC21XL) || (TS_ARCH_DERIVATE == TS_TC277))
    volatile uint32 pwr_evrsdctrl2;     /* 0x1B4 EVR SD Control 2 */
    volatile uint32 pwr_evrsdctrl3;     /* 0x1B8 EVR SD Control 3 */
    volatile uint32 reserved12[2];      /* 0x1BC */
    volatile uint32 pwr_evrsdcoeff2;    /* 0x1C4 EVR SD Coefficient 2 */
    volatile uint32 reserved12_1[5];    /* 0x1C8 */
    volatile uint32 pwr_pmswutcnt;      /* 0x1DC Standby WuT Count */
#else
	volatile uint32 reserved12[11]; /* 0x1B4 */
#endif
    volatile uint32 pwr_ovcenable; /* 0x1E0 Overlay Enable */
    volatile uint32 pwr_ovccon; /* 0x1E4 Overlay Control */
    volatile uint32 reserved13[10]; /* 0x1E8 */
    volatile uint32 pwr_eicr[4]; /* 0x210 External Input Channel 0, 1, 2 and 3 */
    volatile uint32 pwr_eifr; /* 0x220 External Input Flag */
    volatile uint32 pwr_fmr; /* 0x224 Flag Modification */
    volatile uint32 pwr_pdrr; /* 0x228 Pattern Detection Result */
    volatile uint32 pwr_igcr[4]; /* 0x22C Interrupt Gating 0, 1, 2 and 3 */
    volatile uint32 reserved14[1]; /* 0x23C */
    volatile uint32 pwr_dtslim; /* 0x240 Die Temperature Sensor Limit */
#if ((TS_ARCH_DERIVATE == TS_TC21XL) || (TS_ARCH_DERIVATE == TS_TC277))
    volatile uint32 reserved15[47];     /* 0x244 */
    volatile uint32 pwr_pmswcr3;        /* 0x300 Standby and Wakeup Control 3 */
    volatile uint32 reserved15_1[61];   /* 0x304 */
#else
    volatile uint32 reserved15[109]; /* 0x244 */
#endif
    volatile uint32 pwr_accen1; /* 0x3F8 Access Enable 1 */
    volatile uint32 pwr_accen0; /* 0x3FC Access Enable 0 */
#endif
} platforms_tc_kernel_t;

typedef struct platforms_tricore_tc39x_pwr_s
{
	volatile uint32		clc;		/* Clock control register */
	volatile uint32		reserved;	/* Some modules use this! */
	volatile uint32		id;			/* Module identification register */

	volatile uint32		reserved1[1];		/* 0xC */
	volatile uint32		pwr_osccon;			/* 0x10 OSC Control */
	volatile uint32		pwr_pllstat;		/* 0x14	PLL Status */
	volatile uint32		pwr_pllcon[3];		/* 0x18	PLL Configuration 0-2 */
	volatile uint32		pwr_perpllstat;		/* 0x24	PLL Status */
	volatile uint32		pwr_perpllcon[2];	/* 0x28	PLL Configuration 0-2 */
	volatile uint32		pwr_ccucon[2];		/* 0x30	CCU Control 0 *//* 0x34	CCU Control 1 */
	volatile uint32		unused2[2] ;		/* 0x38 registers not used by OS */
	volatile uint32		pwr_ccucon_2[4];	    /* 0x40 CCU Control 2 */
	volatile uint32     pwr_rststat; /* 0x50 Reset Status */
	volatile uint32     reserved3[1]; /* 0x54 */
	volatile uint32     pwr_rstcon; /* 0x58 Reset CON */
	volatile uint32     pwr_arstdis; /* 0x5C Application Reset Disable */
	volatile uint32     pwr_swrstcon; /* 0x60 Software Reset Configuration */
	volatile uint32     pwr_rstcon2; /* 0x64 Additional reset control */
	volatile uint32     reserved4[1]; /* 0x68 */
	volatile uint32     pwr_evrrstcon; /* 0x6C EVR Reset Control */
	volatile uint32     pwr_esrcfg[2]; /* 0x70 ESR0 and 1 Configuration */
	volatile uint32     pwr_esrocfg; /* 0x78 ESR Reset Output Configuration */
	volatile uint32		pwr_syscon;			/* 0x7C System Control */
	volatile uint32		pwr_ccucon6;		/* 0x80 CCU Control 6 */
	volatile uint32		pwr_ccucon7;		/* 0x84 CCU Control 7 */
	volatile uint32		pwr_ccucon8;		/* 0x88 CCU Control 8 */
	volatile uint32		pwr_ccucon9;		/* 0x8C CCU Control 9 */
	volatile uint32		pwr_ccucon10;		/* 0x90 CCU Control 10 */
	volatile uint32		pwr_ccucon11;		/* 0x94 CCU Control 11 */
	volatile uint32		unused4[15];		/* 0x98 registers not used by OS */
	volatile uint32     pwr_pmcsr[3]; /* 0xD4 CPu0, 1 and 2 Power Management Control and Status */
	volatile uint32     unused5[17];		/* 0x98 registers not used by OS */
	volatile uint32		pwr_trapstat;		/* 0x124 Trap Status */
	volatile uint32		pwr_trapset;		/* 0x128 Trap Set */
	volatile uint32		pwr_trapclr;		/* 0x12C Trap Clear */
	volatile uint32		pwr_trapdis;		/* 0x130 Trap Disable */
	volatile uint32		unused6[70];		/* 0x134 registers not used by OS */
	platforms_tc_wdt_t  pwr_wdt[6];	/* 0x24c 6 CPU WDT modules */
	volatile uint32		unused7[5];			/* 0x294 registers not used by OS */
	platforms_tc_wdt_t  pwr_swdt;	/* 0x2A8 System WDT */

} platforms_tricore_tc39x_pwr_t;

typedef struct platforms_tc_stm_s
{
    volatile uint32 clc; /* 0x00   Clock control register */
    volatile uint32 reserved; /* 0x04   Some modules use this! */
    volatile uint32 id; /* 0x08   Module identification register */
    volatile uint32 reserved0[1]; /* 0x0C */
    volatile uint32 stm_tim0; /* 0x10 bits 31..0 */
    volatile uint32 stm_tim1; /* 0x14 bits 35..4 */
    volatile uint32 stm_tim2; /* 0x18 bits 39..8 */
    volatile uint32 stm_tim3; /* 0x1C bits 43..12 */
    volatile uint32 stm_tim4; /* 0c20 bits 47..16 */
    volatile uint32 stm_tim5; /* 0x24 bits 51..20 */
    volatile uint32 stm_tim6; /* 0x28 bits 55/63..32 (!!!) */
    volatile uint32 stm_cap; /* 0x2C capture register for bits 55/63..32 */
    volatile uint32 stm_cmp[2]; /* 0x30 - 0x34 compare registers (1796) */
    volatile uint32 stm_cmcon; /* 0x38 compare control (1796) */
    volatile uint32 stm_icr; /* 0x3C interrupt control (1796) */
#if (TS_ARCH_DERIVATE == TS_TC1782)
    volatile uint32 stm_isrr; /* 0x40 interrupt set/reset (1796) */
	volatile uint32		reserved1[45];
	volatile uint32		stm_src1;		/* service request (1796) */
	volatile uint32		stm_src0;		/* service request (1796) */
#else
    volatile uint32 stm_iscr; /* 0x40 interrupt set/reset (1796) */
    volatile uint32 reserved1[3]; /* 0x44 */
    volatile uint32 stm_tim0sv; /* 0x50 Timer 0 Register Second View */
    volatile uint32 stm_capsv; /* 0x54 Timer Capture Register Second View */
    volatile uint32 reserved2[36]; /* 0x58 */
    volatile uint32 stm_ocs; /* 0xE8 OCDS Control and Status */
    volatile uint32 stm_krstclr; /* 0xEC Reset Status Clear */
    volatile uint32 stm_krst1; /* 0xF0 Reset Control 1 */
    volatile uint32 stm_krst0; /* 0xF4 Reset Control 0 */
    volatile uint32 stm_accen1; /* 0xF8 Access Enable 1 */
    volatile uint32 stm_accen0; /* 0xFC Access Enable 0 */
#endif

} platforms_tc_stm_t;

typedef struct platforms_tricore_tc39x_stm_s
{
    volatile uint32 clc; /* 0x00   Clock control register */
    volatile uint32 reserved; /* 0x04   Some modules use this! */
    volatile uint32 id; /* 0x08   Module identification register */
	volatile uint32			reserved0[1];	/* 0x0C */
	volatile uint32			stm_tim0;		/* 0x10 bits 31..0 */
	volatile uint32			stm_tim1;		/* 0x14 bits 35..4 */
	volatile uint32			stm_tim2;		/* 0x18 bits 39..8 */
	volatile uint32			stm_tim3;		/* 0x1C bits 43..12 */
	volatile uint32			stm_tim4;		/* 0c20 bits 47..16 */
	volatile uint32     	stm_tim5;		/* 0x24 bits 51..20 */
	volatile uint32			stm_tim6;		/* 0x28 bits 55/63..32 (!!!) */
	volatile uint32			stm_cap;		/* 0x2C capture register for bits 55/63..32 */
	volatile uint32			stm_cmp[2];		/* 0x30 - 0x34 compare registers (1796) */
	volatile uint32			stm_cmcon;		/* 0x38 compare control (1796) */
	volatile uint32			stm_icr;		/* 0x3C interrupt control (1796) */
	volatile uint32			stm_isrr;		/* 0x40 interrupt set/reset (1796) */
	volatile uint32			reserved1[3];	/* 0x44 */
	volatile uint32			stm_tim0sv;		/* 0x50 Timer 0 Register Second View */
	volatile uint32			stm_capsv;		/* 0x54 Timer Capture Register Second View */
	volatile uint32			reserved2[36];	/* 0x58 */
	volatile uint32			stm_ocs;		/* 0xE8 OCDS Control and Status */
	volatile uint32			stm_krstclr;	/* 0xEC Reset Status Clear */
	volatile uint32			stm_krst1;		/* 0xF0 Reset Control 1 */
	volatile uint32			stm_krst0;		/* 0xF4 Reset Control 0 */
	volatile uint32			stm_accen1;		/* 0xF8 Access Enable 1 */
	volatile uint32			stm_accen0;		/* 0xFC Access Enable 0 */
} platforms_tricore_tc39x_stm_t;


/* Bits in stm_cmcon.*/
#define PLATFORMS_STM_MSIZE0        0x0000001fu
#define PLATFORMS_STM_MSTART0       0x00001f00u
#define PLATFORMS_STM_MSIZE1        0x001f0000u
#define PLATFORMS_STM_MSTART1       0x1f000000u
#define PLATFORMS_STM_CMCON0        0x0000ffffu
#define PLATFORMS_STM_CMCON1        0xffff0000u

/* Bits in stm_icr*/
#if (TS_ARCH_DERIVATE == TS_TC1782)
	
/* Bit definitions for CLC */
#define PLATFORMS_CLC_RMC	0x00000700		/* Clock divider (Rate mode control?) */
#define PLATFORMS_CLC_FSOE	0x00000020		/* Fast shut-off enable */
#define PLATFORMS_CLC_SBWE	0x00000010		/* Suspend bit write enable */
#define PLATFORMS_CLC_EDIS	0x00000008		/* External request disable */
#define PLATFORMS_CLC_SPEN	0x00000004		/* Suspend enable bit */
#define PLATFORMS_CLC_DISS	0x00000002		/* Disable status bit */
#define PLATFORMS_CLC_DISR	0x00000001		/* Disable request bit */

#define PLATFORMS_STM_ICR_CMP0EN		0x00000001u	/* Enable CMP0 */
#define PLATFORMS_STM_ICR_CMP0IR		0x00000002u	/* CMP0 IRQ pending */
#define PLATFORMS_STM_ICR_CMP0OS		0x00000004u	/* CMP0 IRQ */
#define PLATFORMS_STM_ICR_CMP1EN		0x00000010u	/*	... same for CMP1 */
#define PLATFORMS_STM_ICR_CMP1IR		0x00000020u
#define PLATFORMS_STM_ICR_CMP1OS		0x00000040u
#define PLATFORMS_STM_ICR_CMP0		    0x00000007u
#define PLATFORMS_STM_ICR_CMP1		    0x00000070u
#define PLATFORMS_STM_ICR_DISABLE   0x00000000u /* disable ISR generation*/	
#define PLATFORMS_STM_ICR_ENABLE    0x00000001u /* Enable ISR generation*/

/* Bits in stm_isrr*/
#define PLATFORMS_STM_ISRR_CMP0IRR       0x00000001u   /* Reset CMP0 irq */
#define PLATFORMS_STM_ISRR_CMP0IRS       0x00000002u   /* Set CMP0 irq */
#define PLATFORMS_STM_ISRR_CMP1IRR       0x00000004u   /* Reset CMP1 irq */
#define PLATFORMS_STM_ISRR_CMP1IRS       0x00000008u   /* Set CMP1 irq */
#else /* TS_TC1782 */

/* Bits in stm_icr*/
#define PLATFORMS_STM_ICR_CMP0      0x00000007u
#define PLATFORMS_STM_ICR_CMP0IR    0x00000001u /* Compare Register CMP0 Interrupt Request Flag*/
#define PLATFORMS_STM_ICR_CMP0OS    0x00000000u /* Interrupt output STMIR0 selected */
#define PLATFORMS_STM_ICR_DISABLE   0x00000000u /* disable ISR generation*/	
	
/* Bits in stm_iscr*/
#define PLATFORMS_STM_ISCR_CMP0IRR       0x00000001u   /* Reset CMP0 irq */
#define PLATFORMS_STM_ISCR_CMP0IRS       0x00000002u   /* Set CMP0 irq */
#define PLATFORMS_STM_ISCR_CMP1IRR       0x00000004u   /* Reset CMP1 irq */
#define PLATFORMS_STM_ISCR_CMP1IRS       0x00000008u   /* Set CMP1 irq */
#endif  /* TS_TC1782 */

/* Constants for the OCS register.*/
#define PLATFORMS_STM_OCS_SUS_MASK        0x0F000000u
#define PLATFORMS_STM_OCS_SUS_WILL_STOP   0x02000000u
#define PLATFORMS_STM_OCS_SUS_WRITE_PROT  0x10000000u

#define PLATFORMS_SWRSTCON_SWRSTREQ       0x00000002u

#if (TS_ARCH_DERIVATE == TS_TC1782)
#define PLATFORMS_RESET_REASON_MASK       ((uint32)(0x003F001DU))
#define PLATFORMS_RAW_ESR0_RESET          ((uint32)(0x00000001U)) /* ESR0 reset */
#define PLATFORMS_RAW_ESR1_RESET          ((uint32)(0x00000002U)) /* ESR1 reset */
#define PLATFORMS_RAW_WDT_RESET           ((uint32)(0x00000008U)) /* WDT reset */
#define PLATFORMS_RAW_SW_RESET            ((uint32)(0x00000010U)) /* Software reset */
#define PLATFORMS_RAW_POWER_ON_RESET      ((uint32)(0x00010000U)) /* Power On reset, Pulling down PORST Line */
#define PLATFORMS_RAW_CB0_RESET           ((uint32)(0x00040000U)) /* Cerberus System Reset*/
#define PLATFORMS_RAW_CB1_RESET           ((uint32)(0x00080000U)) /* Cerberus Debug Reset*/
#define PLATFORMS_RAW_CB3_RESET           ((uint32)(0x00100000U)) /* Cerberus Application Reset*/
#define PLATFORMS_RAW_TP_RESET            ((uint32)(0x00200000U)) /* Tuning Protection Reset*/
#define PLATFORMS_RAW_RESET_UNDEFINED     ((uint32)(0xFFFFFFFFU)) /* Reset is undefined*/

#else /* #if (TS_ARCH_DERIVATE == TS_TC1782) */
#define PLATFORMS_RESET_REASON_MASK       0x13BD00FBU
#define PLATFORMS_RAW_ESR0_RESET          ((uint32)(0x00000001U)) /* ESR0 reset */
#define PLATFORMS_RAW_ESR1_RESET          ((uint32)(0x00000002U)) /* ESR1 reset */
#define PLATFORMS_RAW_SMU_RESET           ((uint32)(0x00000008U)) /* SMU reset */
#define PLATFORMS_RAW_SW_RESET            ((uint32)(0x00000010U)) /* Software reset */
#define PLATFORMS_RAW_STM0_RESET          ((uint32)(0x00000020U)) /* STM0 Reset*/
#define PLATFORMS_RAW_STM1_RESET          ((uint32)(0x00000040U)) /* STM1 Reset*/
#define PLATFORMS_RAW_STM2_RESET          ((uint32)(0x00000080U)) /* STM2 Reset*/
#define PLATFORMS_RAW_POWER_ON_RESET_1    ((uint32)(0x13810000U)) /* Power On reset on battery connect*/
#define PLATFORMS_RAW_POWER_ON_RESET_2    ((uint32)(0x00010000U)) /* Power On reset, Pulling down PORST Line */
#define PLATFORMS_RAW_CB0_RESET           ((uint32)(0x00040000U)) /* Cerberus System Reset*/
#define PLATFORMS_RAW_CB1_RESET           ((uint32)(0x00080000U)) /* Cerberus Debug Reset*/
#define PLATFORMS_RAW_CB3_RESET           ((uint32)(0x00100000U)) /* Cerberus Application Reset*/
#define PLATFORMS_RAW_TP_RESET            ((uint32)(0x00200000U)) /* Tuning Protection Reset*/
#define PLATFORMS_RAW_EVR13_RESET         ((uint32)(0x00810000U)) /* EVR13 Reset*/
#define PLATFORMS_RAW_EVR33_RESET         ((uint32)(0x01010000U)) /* EVR33 Reset*/
#define PLATFORMS_RAW_SUPPLY_WDOG_RESET   ((uint32)(0x02010000U)) /* Supply Watchdog Reset*/
#define PLATFORMS_RAW_STBYR_RESET         ((uint32)(0x10010000U)) /* Standby Regualtor Watchdog Reset*/
#define PLATFORMS_RAW_RESET_UNDEFINED     ((uint32)(0xFFFFFFFFU)) /* Reset is undefined*/
#endif  /* #if (TS_ARCH_DERIVATE == TS_TC1782) */

#endif /*#ifndef BOARD_ASM*/

/*  Bit definitions for all context pointer registers (PCXI,FCX,LCX)
 */
#define PLATFORMS_CX_SEG     (0x000F0000U)    /* Segment number of CSA. */
#define PLATFORMS_CX_OFF     (0x0000FFFFU)    /* Index of CSA. */
#define PLATFORMS_CX_CX      (PLATFORMS_CX_SEG|PLATFORMS_CX_OFF) /* Entire context */

#define PLATFORMS_AddrFromCx(cx) \
  ((void *)( (((cx) & PLATFORMS_CX_SEG) << 12) + (((cx) & PLATFORMS_CX_OFF) << 6) ))

/* Platforms_CxFromAddr() converts an address to a CSA link word.
 * No test is made for validity!
 */
#define Platforms_CxFromAddr(a) \
  ( (((a) >> 6) & PLATFORMS_CX_OFF) +  (((a) >> 12) & PLATFORMS_CX_SEG) )

#define PLATFORMS__XSTR(s) PLATFORMS__STR(s)
#define PLATFORMS__STR(s) #s

/* CHECK: PARSE */
#endif
/* Editor settings - DO NOT DELETE
 * vi:set ts=4:
 */
