/*******************************************************************************
**                                                                            **
** Copyright (C) Infineon Technologies (2019)                                 **
**                                                                            **
** All rights reserved.                                                       **
**                                                                            **
** This document contains proprietary information belonging to Infineon       **
** Technologies. Passing on and copying of this document, and communication   **
** of its contents is not permitted without prior written authorization.      **
**                                                                            **
********************************************************************************
**                                                                            **
**  FILENAME     : Irq.h                                                      **
**                                                                            **
**  VERSION      : 5.0.0                                                      **
**                                                                            **
**  DATE         : 2019-03-13                                                 **
**                                                                            **
**  VARIANT      : Variant PC                                                 **
**                                                                            **
**  PLATFORM     : Infineon AURIX2G                                           **
**                                                                            **
**  AUTHOR       : DL-AUTOSAR-Engineering                                     **
**                                                                            **
**  VENDOR       : Infineon Technologies                                      **
**                                                                            **
**  DESCRIPTION  : Irq Driver header definition file                          **
**                                                                            **
**  SPECIFICATION(S) : na                                                     **
**                                                                            **
**  MAY BE CHANGED BY USER : yes                                              **
**                                                                            **
*******************************************************************************/

#ifndef  IRQ_H
#define  IRQ_H

/*******************************************************************************
**                      Include Section                                       **
*******************************************************************************/
/* Inclusion of Platform_Types.h and Compiler.h SPI070: */
#include "Std_Types.h"

#include "Mcal_Compiler.h"
#ifdef _GNU_C_TRICORE_
#if (_GNU_C_TRICORE_ == 1U)
#include "intrinsics.h"
#endif
#endif


/*******************************************************************************
**                          Published parameters                              **
*******************************************************************************/
/* Irq Vendor ID */
#define IRQ_VENDOR_ID              ((uint16)17)
/* Irq Module ID */
#define IRQ_MODULE_ID              ((uint16)255)
/* Irq Instance ID */
#define IRQ_INSTANCE_ID            ((uint16)0)
/*******************************************************************************
**                      Global Macro Definitions                              **
*******************************************************************************/
#define IRQ_DMA_AVAILABLE          (0U)
#define IRQ_DMA_USED_MCALADC       (1U)
#define IRQ_DMA_USED_MCALSPI_TX    (2U)
#define IRQ_DMA_USED_MCALSPI_RX    (3U)
#define IRQ_CLEAR_MASK                0xFFFFFFFFU
#define SRC_STM0SR0_CLRR_CLEARMASK    0x7D3F1CFFU
#define SRC_STM0SR0_CLRR_SETMASK      0x02000000U
#define SRC_STM0SR0_SRE_CLEARMASK     0x7F3F18FFU
#define SRC_STM0SR1_CLRR_CLEARMASK    0x7D3F1CFFU
#define SRC_STM0SR1_CLRR_SETMASK      0x02000000U
#define SRC_STM0SR1_SRE_CLEARMASK     0x7F3F18FFU
#define STM0_CMP_CLEARMASK            0x00000000U



/* MISRA2012_RULE_4_9_JUSTIFICATION: Function like macro declared to ensure
correct syntax of declaring const pointer to function as required by specific
compiler, No arithmetic operation is done in this macro.*/
#define IRQ_SFR_MODIFY32(reg, clearmask ,setmask) \
  { ((reg)) &= clearmask; ((reg)) = (setmask);}

/* MISRA2012_RULE_4_9_JUSTIFICATION: Function like macro declared to ensure
correct syntax of declaring const pointer to function as required by specific
compiler, No arithmetic operation is done in this macro.*/
#define Irq_InstallInterruptHandler(priority,irq_handler)


#ifndef ISR
/* MISRA2012_RULE_4_9_JUSTIFICATION: Function like macro declared to ensure
correct syntax of declaring const pointer to function as required by specific
compiler, No arithmetic operation is done in this macro.*/
#define ISR(x) void x(void)
#endif


#ifdef _TASKING_C_TRICORE_
#if (_TASKING_C_TRICORE_ == 1U)

#ifndef IFX_INTERRUPT
/* MISRA2012_RULE_4_9_JUSTIFICATION: Function like macro declared to ensure
correct syntax of declaring const pointer to function as required by specific
compiler, No arithmetic operation is done in this macro.*/
#define IFX_INTERRUPT(isr, vectabNum, prio) \
                    void __interrupt(prio) __vector_table(vectabNum) isr(void)
#endif

#endif
#endif /* (_TASKING_C_TRICORE_ == 1U) */

#ifdef _GNU_C_TRICORE_
#if (_GNU_C_TRICORE_ == 1U)
#ifndef IFX_INTERRUPT
/* MISRA2012_RULE_4_9_JUSTIFICATION: Function like macro declared to ensure
correct syntax of declaring const pointer to function as required by specific
compiler, No arithmetic operation is done in this macro.*/
#define IFX_INTERRUPT(isr, vectabNum, prio) \
                                   IFX_INTERRUPT_INTERNAL(isr, vectabNum, prio)
#endif


#ifndef IFX_INTERRUPT_INTERNAL
/* MISRA2012_RULE_4_9_JUSTIFICATION: Function like macro declared to ensure
correct syntax of declaring const pointer to function as required by specific
compiler, No arithmetic operation is done in this macro.*/
#define IFX_INTERRUPT_INTERNAL(isr, vectabNum, prio) \
__asm__ (".ifndef .intr.entry.include                        \n"\
    ".altmacro                                           \n"\
    ".macro .int_entry.2 intEntryLabel, name \
                                # define the section and inttab entry code \n"\
        " .pushsection .\\intEntryLabel,\"ax\",@progbits   \n"\
        " __\\intEntryLabel :                              \n"\
        "   svlcx                                        \n"\
        "   movh.a  %a14, hi:\\name                      \n"\
        "   lea     %a14, [%a14]lo:\\name                \n"\
        "   ji      %a14                                 \n"\
        " .popsection                                      \n"\
    ".endm                                               \n"\
    ".macro .int_entry.1 prio,vectabNum,u,name           \n"\
      ".int_entry.2 intvec_tc\\vectabNum\\u\\prio,(name) \
                                                  # build the unique name \n"\
    ".endm                                               \n"\
        "                                                    \n"\
    ".macro .intr.entry name,vectabNum,prio              \n"\
      ".int_entry.1 %(prio),%(vectabNum),_,name \
                               # evaluate the priority and the cpu number \n"\
    ".endm                                               \n"\
    ".intr.entry.include:                                \n"\
    ".endif                                              \n"\
        ".intr.entry "#isr","#vectabNum","#prio               );\
extern void __attribute__ ((interrupt_handler)) isr(); \
void isr (void)
#endif /* IFX_INTERRUPT */

#endif /* (_GNU_C_TRICORE_ == 1U) */
#endif /* End of #ifdef _GNU_C_TRICORE_ */



#ifdef _DIABDATA_C_TRICORE_

#if (_DIABDATA_C_TRICORE_ == 1U)

#ifndef IFX_INTERRUPT
/* MISRA2012_RULE_4_9_JUSTIFICATION: Function like macro declared to ensure
correct syntax of declaring const pointer to function as required by specific
compiler, No arithmetic operation is done in this macro.*/
#define IFX_INTERRUPT(isr, vectabNum, prio) \
                                  IFX_INTERRUPT_INTERNAL(isr, vectabNum, prio)
#endif

#ifndef IFX_INTERRUPT_INTERNAL
/* MISRA2012_RULE_4_9_JUSTIFICATION: Function like macro declared to ensure
correct syntax of declaring const pointer to function as required by specific
compiler, No arithmetic operation is done in this macro.*/
#define IFX_INTERRUPT_INTERNAL(isr, vectabNum, prio)                \
void __interrupt(prio) __vector_table(vectabNum) isr(void)
#endif /* IFX_INTERRUPT_INTERNAL */
#endif
#endif

#ifdef _GHS_C_TRICORE_
#if (_GHS_C_TRICORE_ == 1U)

#ifndef IFX_INTERRUPT
#define IFX_INTERRUPT(isr, vectabNum, prio) IFX_INTERRUPT_INTERNAL(isr, vectabNum, prio)
#endif

#define IFX_INTERRUPT_INTERNAL(isr, vectabNum, prio) \
__attribute__((section(".intvec_tc"#vectabNum"_"#prio))) void iVecEntry##vectabNum##_##prio(void) \
{ \
  __asm__("movh.a  a14, %hi("#isr") \n" \
      "lea     a14, [a14]%lo("#isr")\n" \
      "ji      a14"); \
} \
__interrupt void isr(void)
#endif /* (_GHS_C_TRICORE_ == 1U) */
#endif /* End of #ifdef _GHS_C_TRICORE_ */
/*******************************************************************************
**                      Global Type Definitions                               **
*******************************************************************************/

/*******************************************************************************
**                      Global Constant Declarations                          **
*******************************************************************************/

/*******************************************************************************
**                      Global Variable Declarations                          **
*******************************************************************************/

/*******************************************************************************
**                      Global Inline Function Definitions                    **
*******************************************************************************/

#endif /* IRQ_H */
