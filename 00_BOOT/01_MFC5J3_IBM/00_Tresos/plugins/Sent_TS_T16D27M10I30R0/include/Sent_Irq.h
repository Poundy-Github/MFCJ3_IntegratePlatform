
#ifndef SENT_IRQ_H
#define SENT_IRQ_H

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

/*************************SENTSR0_ISR*********************************/          

#ifdef SENTSR0_ISR
#define IRQ_SENTSR0_EXIST      STD_ON
#define IRQ_SENT_SR0_PRIO    SENTSR0_ISR_ISR_LEVEL
#define IRQ_SENT_SR0_CAT     SENTSR0_ISR_ISR_CATEGORY
#else
#define IRQ_SENTSR0_EXIST      STD_OFF
#endif

/*************************SENTSR1_ISR*********************************/          

#ifdef SENTSR1_ISR
#define IRQ_SENTSR1_EXIST      STD_ON
#define IRQ_SENT_SR1_PRIO    SENTSR1_ISR_ISR_LEVEL
#define IRQ_SENT_SR1_CAT     SENTSR1_ISR_ISR_CATEGORY
#else
#define IRQ_SENTSR1_EXIST      STD_OFF
#endif

/*************************SENTSR2_ISR*********************************/          

#ifdef SENTSR2_ISR
#define IRQ_SENTSR2_EXIST      STD_ON
#define IRQ_SENT_SR2_PRIO    SENTSR2_ISR_ISR_LEVEL
#define IRQ_SENT_SR2_CAT     SENTSR2_ISR_ISR_CATEGORY
#else
#define IRQ_SENTSR2_EXIST      STD_OFF
#endif

/*************************SENTSR3_ISR*********************************/          

#ifdef SENTSR3_ISR
#define IRQ_SENTSR3_EXIST      STD_ON
#define IRQ_SENT_SR3_PRIO    SENTSR3_ISR_ISR_LEVEL
#define IRQ_SENT_SR3_CAT     SENTSR3_ISR_ISR_CATEGORY
#else
#define IRQ_SENTSR3_EXIST      STD_OFF
#endif

/*************************SENTSR4_ISR*********************************/          

#ifdef SENTSR4_ISR
#define IRQ_SENTSR4_EXIST      STD_ON
#define IRQ_SENT_SR4_PRIO    SENTSR4_ISR_ISR_LEVEL
#define IRQ_SENT_SR4_CAT     SENTSR4_ISR_ISR_CATEGORY
#else
#define IRQ_SENTSR4_EXIST      STD_OFF
#endif

/*************************SENTSR5_ISR*********************************/          

#ifdef SENTSR5_ISR
#define IRQ_SENTSR5_EXIST      STD_ON
#define IRQ_SENT_SR5_PRIO    SENTSR5_ISR_ISR_LEVEL
#define IRQ_SENT_SR5_CAT     SENTSR5_ISR_ISR_CATEGORY
#else
#define IRQ_SENTSR5_EXIST      STD_OFF
#endif

/*************************SENTSR6_ISR*********************************/          

#ifdef SENTSR6_ISR
#define IRQ_SENTSR6_EXIST      STD_ON
#define IRQ_SENT_SR6_PRIO    SENTSR6_ISR_ISR_LEVEL
#define IRQ_SENT_SR6_CAT     SENTSR6_ISR_ISR_CATEGORY
#else
#define IRQ_SENTSR6_EXIST      STD_OFF
#endif

/*************************SENTSR7_ISR*********************************/          

#ifdef SENTSR7_ISR
#define IRQ_SENTSR7_EXIST      STD_ON
#define IRQ_SENT_SR7_PRIO    SENTSR7_ISR_ISR_LEVEL
#define IRQ_SENT_SR7_CAT     SENTSR7_ISR_ISR_CATEGORY
#else
#define IRQ_SENTSR7_EXIST      STD_OFF
#endif

/*************************SENTSR8_ISR*********************************/          

#ifdef SENTSR8_ISR
#define IRQ_SENTSR8_EXIST      STD_ON
#define IRQ_SENT_SR8_PRIO    SENTSR8_ISR_ISR_LEVEL
#define IRQ_SENT_SR8_CAT     SENTSR8_ISR_ISR_CATEGORY
#else
#define IRQ_SENTSR8_EXIST      STD_OFF
#endif

/*************************SENTSR9_ISR*********************************/          

#ifdef SENTSR9_ISR
#define IRQ_SENTSR9_EXIST      STD_ON
#define IRQ_SENT_SR9_PRIO    SENTSR9_ISR_ISR_LEVEL
#define IRQ_SENT_SR9_CAT     SENTSR9_ISR_ISR_CATEGORY
#else
#define IRQ_SENTSR9_EXIST      STD_OFF
#endif

/*************************SENTSR10_ISR*********************************/          

#ifdef SENTSR10_ISR
#define IRQ_SENTSR10_EXIST      STD_ON
#define IRQ_SENT_SR10_PRIO    SENTSR10_ISR_ISR_LEVEL
#define IRQ_SENT_SR10_CAT     SENTSR10_ISR_ISR_CATEGORY
#else
#define IRQ_SENTSR10_EXIST      STD_OFF
#endif

/*************************SENTSR11_ISR*********************************/          

#ifdef SENTSR11_ISR
#define IRQ_SENTSR11_EXIST      STD_ON
#define IRQ_SENT_SR11_PRIO    SENTSR11_ISR_ISR_LEVEL
#define IRQ_SENT_SR11_CAT     SENTSR11_ISR_ISR_CATEGORY
#else
#define IRQ_SENTSR11_EXIST      STD_OFF
#endif

/*************************SENTSR12_ISR*********************************/          

#ifdef SENTSR12_ISR
#define IRQ_SENTSR12_EXIST      STD_ON
#define IRQ_SENT_SR12_PRIO    SENTSR12_ISR_ISR_LEVEL
#define IRQ_SENT_SR12_CAT     SENTSR12_ISR_ISR_CATEGORY
#else
#define IRQ_SENTSR12_EXIST      STD_OFF
#endif

/*************************SENTSR13_ISR*********************************/          

#ifdef SENTSR13_ISR
#define IRQ_SENTSR13_EXIST      STD_ON
#define IRQ_SENT_SR13_PRIO    SENTSR13_ISR_ISR_LEVEL
#define IRQ_SENT_SR13_CAT     SENTSR13_ISR_ISR_CATEGORY
#else
#define IRQ_SENTSR13_EXIST      STD_OFF
#endif

/*************************SENTSR14_ISR*********************************/          

#ifdef SENTSR14_ISR
#define IRQ_SENTSR14_EXIST      STD_ON
#define IRQ_SENT_SR14_PRIO    SENTSR14_ISR_ISR_LEVEL
#define IRQ_SENT_SR14_CAT     SENTSR14_ISR_ISR_CATEGORY
#else
#define IRQ_SENTSR14_EXIST      STD_OFF
#endif

#endif
