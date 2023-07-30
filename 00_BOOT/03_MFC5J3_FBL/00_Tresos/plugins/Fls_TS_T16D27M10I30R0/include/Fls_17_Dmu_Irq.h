
#ifndef FLS_17_DMU_IRQ_H
#define FLS_17_DMU_IRQ_H

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

#ifdef DMUHOST_ISR
#define IRQ_DMUHOST_EXIST  STD_ON
#define IRQ_DMU_HOST_PRIO    DMUHOST_ISR_ISR_LEVEL
#define IRQ_DMU_HOST_CAT     DMUHOST_ISR_ISR_CATEGORY
#else
#define IRQ_DMUHOST_EXIST  STD_OFF
#endif

/**********************************************************/          

#ifdef DMUFSI_ISR
#define IRQ_DMUFSI_EXIST  STD_ON
#define IRQ_DMU_FSI_PRIO    DMUFSI_ISR_ISR_LEVEL
#define IRQ_DMU_FSI_CAT     DMUFSI_ISR_ISR_CATEGORY
#else
#define IRQ_DMUFSI_EXIST  STD_OFF
#endif
#endif

