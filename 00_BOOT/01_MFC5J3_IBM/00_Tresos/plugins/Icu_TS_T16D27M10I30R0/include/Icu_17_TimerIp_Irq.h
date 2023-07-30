
#ifndef ICU_17_GTMCCU6_IRQ_H
#define ICU_17_GTMCCU6_IRQ_H

/*******************************************************************************
**                      Includes                                              **
*******************************************************************************/

#include "Std_Types.h"                                                        

#ifdef OS_KERNEL_TYPE                                                           
#include <Os.h>        /* OS interrupt services */                              
#endif


/*******************************************************************************
**                      Public Macro Definitions                              **
*******************************************************************************/

/************************* interrupt CATEGORY *********************************/

#ifdef IRQ_CAT1
#if (IRQ_CAT1 != 1)
#error IRQ_CAT1 already defined with a wrong value
#endif
#else
#define IRQ_CAT1                    (1)
#endif

#ifdef IRQ_CAT2
#if (IRQ_CAT2 != 2)
#error IRQ_CAT2 already defined with a wrong value
#endif
#else
#define IRQ_CAT2                    (2)
#endif



/* The name of the ISRs shall be the same name than the ISR       *
 * functions provided by Infineon                                 */

/**********************************************************/          

#ifdef CCU60SR0_ISR
#define IRQ_CCU60SR0_EXIST  STD_ON
#define IRQ_CCU60_SR0_PRIO    CCU60SR0_ISR_ISR_LEVEL
#define IRQ_CCU60_SR0_CAT     CCU60SR0_ISR_ISR_CATEGORY
#else
#define IRQ_CCU60SR0_EXIST  STD_OFF
#endif

/**********************************************************/          

#ifdef CCU60SR1_ISR
#define IRQ_CCU60SR1_EXIST  STD_ON
#define IRQ_CCU60_SR1_PRIO    CCU60SR1_ISR_ISR_LEVEL
#define IRQ_CCU60_SR1_CAT     CCU60SR1_ISR_ISR_CATEGORY
#else
#define IRQ_CCU60SR1_EXIST  STD_OFF
#endif

/**********************************************************/          

#ifdef CCU60SR2_ISR
#define IRQ_CCU60SR2_EXIST  STD_ON
#define IRQ_CCU60_SR2_PRIO    CCU60SR2_ISR_ISR_LEVEL
#define IRQ_CCU60_SR2_CAT     CCU60SR2_ISR_ISR_CATEGORY
#else
#define IRQ_CCU60SR2_EXIST  STD_OFF
#endif

/**********************************************************/          

#ifdef CCU60SR3_ISR
#define IRQ_CCU60SR3_EXIST  STD_ON
#define IRQ_CCU60_SR3_PRIO    CCU60SR3_ISR_ISR_LEVEL
#define IRQ_CCU60_SR3_CAT     CCU60SR3_ISR_ISR_CATEGORY
#else
#define IRQ_CCU60SR3_EXIST  STD_OFF
#endif


/**********************************************************/          

#ifdef CCU61SR0_ISR
#define IRQ_CCU61SR0_EXIST  STD_ON
#define IRQ_CCU61_SR0_PRIO    CCU61SR0_ISR_ISR_LEVEL
#define IRQ_CCU61_SR0_CAT     CCU61SR0_ISR_ISR_CATEGORY
#else
#define IRQ_CCU61SR0_EXIST  STD_OFF
#endif

/**********************************************************/          

#ifdef CCU61SR1_ISR
#define IRQ_CCU61SR1_EXIST  STD_ON
#define IRQ_CCU61_SR1_PRIO    CCU61SR1_ISR_ISR_LEVEL
#define IRQ_CCU61_SR1_CAT     CCU61SR1_ISR_ISR_CATEGORY
#else
#define IRQ_CCU61SR1_EXIST  STD_OFF
#endif

/**********************************************************/          

#ifdef CCU61SR2_ISR
#define IRQ_CCU61SR2_EXIST  STD_ON
#define IRQ_CCU61_SR2_PRIO    CCU61SR2_ISR_ISR_LEVEL
#define IRQ_CCU61_SR2_CAT     CCU61SR2_ISR_ISR_CATEGORY
#else
#define IRQ_CCU61SR2_EXIST  STD_OFF
#endif

/**********************************************************/          

#ifdef CCU61SR3_ISR
#define IRQ_CCU61SR3_EXIST  STD_ON
#define IRQ_CCU61_SR3_PRIO    CCU61SR3_ISR_ISR_LEVEL
#define IRQ_CCU61_SR3_CAT     CCU61SR3_ISR_ISR_CATEGORY
#else
#define IRQ_CCU61SR3_EXIST  STD_OFF
#endif



#endif /* #ifndef ICU_17_GTMCCU6_IRQ_H */

