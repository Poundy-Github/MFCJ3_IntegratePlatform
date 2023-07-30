
#ifndef ETH_17_ETHMAC_IRQ_H
#define ETH_17_ETHMAC_IRQ_H

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

#ifdef IRQ_CAT23
#if (IRQ_CAT23 != 2)
#error IRQ_CAT23 already defined with a wrong value
#endif
#else
#define IRQ_CAT23                    (2)
#endif



/* The name of the ISRs shall be the same name than the ISR       *
 * functions provided by Infineon                                 */

/**********************************************************/          

#ifdef ETHSR0_ISR
#define IRQ_ETHSR0_EXIST    STD_ON
#define IRQ_GETH_SR0_PRIO    GETHSR0_ISR_ISR_LEVEL
#define IRQ_GETH_SR0_CAT     GETHSR0_ISR_ISR_CATEGORY
#else
#define IRQ_ETHSR0_EXIST  	 STD_OFF
#endif

/**********************************************************/          

#ifdef ETHSR2_ISR
#define IRQ_ETHSR2_EXIST    STD_ON
#define IRQ_GETH_SR2_PRIO    GETHSR2_ISR_ISR_LEVEL
#define IRQ_GETH_SR2_CAT     GETHSR2_ISR_ISR_CATEGORY
#else
#define IRQ_ETHSR2_EXIST  	 STD_OFF
#endif

/**********************************************************/          

#ifdef ETHSR6_ISR
#define IRQ_ETHSR6_EXIST    STD_ON
#define IRQ_GETH_SR6_PRIO    GETHSR6_ISR_ISR_LEVEL
#define IRQ_GETH_SR6_CAT     GETHSR6_ISR_ISR_CATEGORY
#else
#define IRQ_ETHSR6_EXIST  	 STD_OFF
#endif

/**********************************************************/          

#ifdef ETHSR10_ISR
#define IRQ_ETHSR10_EXIST    STD_ON
#define IRQ_GETH1_SR0_PRIO    GETHSR10_ISR_ISR_LEVEL
#define IRQ_GETH1_SR0_CAT     GETHSR10_ISR_ISR_CATEGORY
#else
#define IRQ_ETHSR10_EXIST    STD_OFF
#endif

/**********************************************************/          

#ifdef ETHSR12_ISR
#define IRQ_ETHSR12_EXIST    STD_ON
#define IRQ_GETH1_SR2_PRIO    GETHSR12_ISR_ISR_LEVEL
#define IRQ_GETH1_SR2_CAT     GETHSR12_ISR_ISR_CATEGORY
#else
#define IRQ_ETHSR12_EXIST    STD_OFF
#endif

/**********************************************************/          

#ifdef ETHSR16_ISR
#define IRQ_ETHSR16_EXIST    STD_ON
#define IRQ_GETH1_SR6_PRIO    GETHSR16_ISR_ISR_LEVEL
#define IRQ_GETH1_SR6_CAT     GETHSR16_ISR_ISR_CATEGORY
#else
#define IRQ_ETHSR16_EXIST    STD_OFF
#endif

/**********************************************************/  
#endif
