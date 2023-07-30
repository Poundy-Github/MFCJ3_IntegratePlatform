
#ifndef QSPI_IRQ_H
#define QSPI_IRQ_H

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


#ifdef QSPI0ERR_ISR
#define IRQ_QSPI0ERR_EXIST       STD_ON
#define IRQ_QSPI0_ERR_PRIO    QSPI0ERR_ISR_ISR_LEVEL
#define IRQ_QSPI0_ERR_CAT     QSPI0ERR_ISR_ISR_CATEGORY
#else
#define IRQ_QSPI0ERR_EXIST       STD_OFF
#endif

/**********************************************************/          

#ifdef QSPI1ERR_ISR
#define IRQ_QSPI1ERR_EXIST       STD_ON
#define IRQ_QSPI1_ERR_PRIO    QSPI1ERR_ISR_ISR_LEVEL
#define IRQ_QSPI1_ERR_CAT     QSPI1ERR_ISR_ISR_CATEGORY
#else
#define IRQ_QSPI1ERR_EXIST       STD_OFF
#endif

/**********************************************************/          

#ifdef QSPI2ERR_ISR
#define IRQ_QSPI2ERR_EXIST       STD_ON
#define IRQ_QSPI2_ERR_PRIO    QSPI2ERR_ISR_ISR_LEVEL
#define IRQ_QSPI2_ERR_CAT     QSPI2ERR_ISR_ISR_CATEGORY
#else
#define IRQ_QSPI2ERR_EXIST       STD_OFF
#endif

/**********************************************************/          

#ifdef QSPI3ERR_ISR
#define IRQ_QSPI3ERR_EXIST       STD_ON
#define IRQ_QSPI3_ERR_PRIO    QSPI3ERR_ISR_ISR_LEVEL
#define IRQ_QSPI3_ERR_CAT     QSPI3ERR_ISR_ISR_CATEGORY
#else
#define IRQ_QSPI3ERR_EXIST       STD_OFF
#endif

/**********************************************************/          

#ifdef QSPI4ERR_ISR
#define IRQ_QSPI4ERR_EXIST       STD_ON
#define IRQ_QSPI4_ERR_PRIO    QSPI4ERR_ISR_ISR_LEVEL
#define IRQ_QSPI4_ERR_CAT     QSPI4ERR_ISR_ISR_CATEGORY
#else
#define IRQ_QSPI4ERR_EXIST       STD_OFF
#endif

/**********************************************************/          

#ifdef QSPI5ERR_ISR
#define IRQ_QSPI5ERR_EXIST       STD_ON
#define IRQ_QSPI5_ERR_PRIO    QSPI5ERR_ISR_ISR_LEVEL
#define IRQ_QSPI5_ERR_CAT     QSPI5ERR_ISR_ISR_CATEGORY
#else
#define IRQ_QSPI5ERR_EXIST       STD_OFF
#endif

/**********************************************************/          

#ifdef QSPI0PT_ISR
#define IRQ_QSPI0PT_EXIST      STD_ON
#define IRQ_QSPI0_PT_PRIO    QSPI0PT_ISR_ISR_LEVEL
#define IRQ_QSPI0_PT_CAT     QSPI0PT_ISR_ISR_CATEGORY
#else
#define IRQ_QSPI0PT_EXIST      STD_OFF
#endif
/**********************************************************/          

#ifdef QSPI1PT_ISR
#define IRQ_QSPI1PT_EXIST      STD_ON
#define IRQ_QSPI1_PT_PRIO    QSPI1PT_ISR_ISR_LEVEL
#define IRQ_QSPI1_PT_CAT     QSPI1PT_ISR_ISR_CATEGORY
#else
#define IRQ_QSPI1PT_EXIST      STD_OFF
#endif
/**********************************************************/          

#ifdef QSPI2PT_ISR
#define IRQ_QSPI2PT_EXIST      STD_ON
#define IRQ_QSPI2_PT_PRIO    QSPI2PT_ISR_ISR_LEVEL
#define IRQ_QSPI2_PT_CAT     QSPI2PT_ISR_ISR_CATEGORY
#else
#define IRQ_QSPI2PT_EXIST      STD_OFF
#endif
/**********************************************************/          

#ifdef QSPI3PT_ISR
#define IRQ_QSPI3PT_EXIST      STD_ON
#define IRQ_QSPI3_PT_PRIO    QSPI3PT_ISR_ISR_LEVEL
#define IRQ_QSPI3_PT_CAT     QSPI3PT_ISR_ISR_CATEGORY
#else
#define IRQ_QSPI3PT_EXIST      STD_OFF
#endif
/**********************************************************/          

#ifdef QSPI4PT_ISR
#define IRQ_QSPI4PT_EXIST      STD_ON
#define IRQ_QSPI4_PT_PRIO    QSPI4PT_ISR_ISR_LEVEL
#define IRQ_QSPI4_PT_CAT     QSPI4PT_ISR_ISR_CATEGORY
#else
#define IRQ_QSPI4PT_EXIST      STD_OFF
#endif
/**********************************************************/          

#ifdef QSPI5PT_ISR
#define IRQ_QSPI5PT_EXIST      STD_ON
#define IRQ_QSPI5_PT_PRIO    QSPI5PT_ISR_ISR_LEVEL
#define IRQ_QSPI5_PT_CAT     QSPI5PT_ISR_ISR_CATEGORY
#else
#define IRQ_QSPI5PT_EXIST      STD_OFF
#endif

#endif /* #ifndef QSPI_IRQ_H */

