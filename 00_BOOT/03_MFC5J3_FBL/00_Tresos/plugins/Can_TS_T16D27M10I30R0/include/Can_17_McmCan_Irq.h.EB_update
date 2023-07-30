
#ifndef CAN_17_MCMCAN_IRQ_H
#define CAN_17_MCMCAN_IRQ_H

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

#ifdef CAN0SR0_ISR
#define IRQ_CAN0SR0_EXIST      STD_ON
#define IRQ_CAN0_SR0_PRIO    CAN0SR0_ISR_ISR_LEVEL
#define IRQ_CAN0_SR0_CAT     CAN0SR0_ISR_ISR_CATEGORY
#else
#define IRQ_CAN0SR0_EXIST      STD_OFF
#endif

/**********************************************************/          

#ifdef CAN0SR1_ISR
#define IRQ_CAN0SR1_EXIST      STD_ON
#define IRQ_CAN0_SR1_PRIO    CAN0SR1_ISR_ISR_LEVEL
#define IRQ_CAN0_SR1_CAT     CAN0SR1_ISR_ISR_CATEGORY
#else
#define IRQ_CAN0SR1_EXIST      STD_OFF
#endif

/**********************************************************/          

#ifdef CAN0SR2_ISR
#define IRQ_CAN0SR2_EXIST      STD_ON
#define IRQ_CAN0_SR2_PRIO    CAN0SR2_ISR_ISR_LEVEL
#define IRQ_CAN0_SR2_CAT     CAN0SR2_ISR_ISR_CATEGORY
#else
#define IRQ_CAN0SR2_EXIST      STD_OFF
#endif

/**********************************************************/          

#ifdef CAN0SR3_ISR
#define IRQ_CAN0SR3_EXIST      STD_ON
#define IRQ_CAN0_SR3_PRIO    CAN0SR3_ISR_ISR_LEVEL
#define IRQ_CAN0_SR3_CAT     CAN0SR3_ISR_ISR_CATEGORY
#else
#define IRQ_CAN0SR3_EXIST      STD_OFF
#endif

/**********************************************************/          

#ifdef CAN0SR4_ISR
#define IRQ_CAN0SR4_EXIST      STD_ON
#define IRQ_CAN0_SR4_PRIO    CAN0SR4_ISR_ISR_LEVEL
#define IRQ_CAN0_SR4_CAT     CAN0SR4_ISR_ISR_CATEGORY
#else
#define IRQ_CAN0SR4_EXIST      STD_OFF
#endif
/**********************************************************/          

#ifdef CAN0SR5_ISR
#define IRQ_CAN0SR5_EXIST      STD_ON
#define IRQ_CAN0_SR5_PRIO    CAN0SR5_ISR_ISR_LEVEL
#define IRQ_CAN0_SR5_CAT     CAN0SR5_ISR_ISR_CATEGORY
#else
#define IRQ_CAN0SR5_EXIST      STD_OFF
#endif
/**********************************************************/          

#ifdef CAN0SR6_ISR
#define IRQ_CAN0SR6_EXIST      STD_ON
#define IRQ_CAN0_SR6_PRIO    CAN0SR6_ISR_ISR_LEVEL
#define IRQ_CAN0_SR6_CAT     CAN0SR6_ISR_ISR_CATEGORY
#else
#define IRQ_CAN0SR6_EXIST      STD_OFF
#endif
/**********************************************************/          

#ifdef CAN0SR7_ISR
#define IRQ_CAN0SR7_EXIST      STD_ON
#define IRQ_CAN0_SR7_PRIO    CAN0SR7_ISR_ISR_LEVEL
#define IRQ_CAN0_SR7_CAT     CAN0SR7_ISR_ISR_CATEGORY
#else
#define IRQ_CAN0SR7_EXIST      STD_OFF
#endif
/**********************************************************/          

#ifdef CAN0SR8_ISR
#define IRQ_CAN0SR8_EXIST      STD_ON
#define IRQ_CAN0_SR8_PRIO    CAN0SR8_ISR_ISR_LEVEL
#define IRQ_CAN0_SR8_CAT     CAN0SR8_ISR_ISR_CATEGORY
#else
#define IRQ_CAN0SR8_EXIST      STD_OFF
#endif
/**********************************************************/          

#ifdef CAN0SR9_ISR
#define IRQ_CAN0SR9_EXIST      STD_ON
#define IRQ_CAN0_SR9_PRIO    CAN0SR9_ISR_ISR_LEVEL
#define IRQ_CAN0_SR9_CAT     CAN0SR9_ISR_ISR_CATEGORY
#else
#define IRQ_CAN0SR9_EXIST      STD_OFF
#endif
/**********************************************************/          

#ifdef CAN0SR10_ISR
#define IRQ_CAN0SR10_EXIST      STD_ON
#define IRQ_CAN0_SR10_PRIO    CAN0SR10_ISR_ISR_LEVEL
#define IRQ_CAN0_SR10_CAT     CAN0SR10_ISR_ISR_CATEGORY
#else
#define IRQ_CAN0SR10_EXIST      STD_OFF
#endif
/**********************************************************/          

#ifdef CAN0SR11_ISR
#define IRQ_CAN0SR11_EXIST      STD_ON
#define IRQ_CAN0_SR11_PRIO    CAN0SR11_ISR_ISR_LEVEL
#define IRQ_CAN0_SR11_CAT     CAN0SR11_ISR_ISR_CATEGORY
#else
#define IRQ_CAN0SR11_EXIST      STD_OFF
#endif
/**********************************************************/          

#ifdef CAN0SR12_ISR
#define IRQ_CAN0SR12_EXIST      STD_ON
#define IRQ_CAN0_SR12_PRIO    CAN0SR12_ISR_ISR_LEVEL
#define IRQ_CAN0_SR12_CAT     CAN0SR12_ISR_ISR_CATEGORY
#else
#define IRQ_CAN0SR12_EXIST      STD_OFF
#endif
/**********************************************************/          

#ifdef CAN0SR13_ISR
#define IRQ_CAN0SR13_EXIST      STD_ON
#define IRQ_CAN0_SR13_PRIO    CAN0SR13_ISR_ISR_LEVEL
#define IRQ_CAN0_SR13_CAT     CAN0SR13_ISR_ISR_CATEGORY
#else
#define IRQ_CAN0SR13_EXIST      STD_OFF
#endif/**********************************************************/          

#ifdef CAN0SR14_ISR
#define IRQ_CAN0SR14_EXIST      STD_ON
#define IRQ_CAN0_SR14_PRIO    CAN0SR14_ISR_ISR_LEVEL
#define IRQ_CAN0_SR14_CAT     CAN0SR14_ISR_ISR_CATEGORY
#else
#define IRQ_CAN0SR14_EXIST      STD_OFF
#endif
/**********************************************************/          

#ifdef CAN0SR15_ISR
#define IRQ_CAN0SR15_EXIST      STD_ON
#define IRQ_CAN0_SR15_PRIO    CAN0SR15_ISR_ISR_LEVEL
#define IRQ_CAN0_SR15_CAT     CAN0SR15_ISR_ISR_CATEGORY
#else
#define IRQ_CAN0SR15_EXIST      STD_OFF
#endif

/**********************************************************/          

#ifdef CAN1SR0_ISR
#define IRQ_CAN1SR0_EXIST      STD_ON
#define IRQ_CAN1_SR0_PRIO    CAN1SR0_ISR_ISR_LEVEL
#define IRQ_CAN1_SR0_CAT     CAN1SR0_ISR_ISR_CATEGORY
#else
#define IRQ_CAN1SR0_EXIST      STD_OFF
#endif

/**********************************************************/          

#ifdef CAN1SR1_ISR
#define IRQ_CAN1SR1_EXIST      STD_ON
#define IRQ_CAN1_SR1_PRIO    CAN1SR1_ISR_ISR_LEVEL
#define IRQ_CAN1_SR1_CAT     CAN1SR1_ISR_ISR_CATEGORY
#else
#define IRQ_CAN1SR1_EXIST      STD_OFF
#endif

/**********************************************************/          

#ifdef CAN1SR2_ISR
#define IRQ_CAN1SR2_EXIST      STD_ON
#define IRQ_CAN1_SR2_PRIO    CAN1SR2_ISR_ISR_LEVEL
#define IRQ_CAN1_SR2_CAT     CAN1SR2_ISR_ISR_CATEGORY
#else
#define IRQ_CAN1SR2_EXIST      STD_OFF
#endif

/**********************************************************/          

#ifdef CAN1SR3_ISR
#define IRQ_CAN1SR3_EXIST      STD_ON
#define IRQ_CAN1_SR3_PRIO    CAN1SR3_ISR_ISR_LEVEL
#define IRQ_CAN1_SR3_CAT     CAN1SR3_ISR_ISR_CATEGORY
#else
#define IRQ_CAN1SR3_EXIST      STD_OFF
#endif

/**********************************************************/          

#ifdef CAN1SR4_ISR
#define IRQ_CAN1SR4_EXIST      STD_ON
#define IRQ_CAN1_SR4_PRIO    CAN1SR4_ISR_ISR_LEVEL
#define IRQ_CAN1_SR4_CAT     CAN1SR4_ISR_ISR_CATEGORY
#else
#define IRQ_CAN1SR4_EXIST      STD_OFF
#endif

/**********************************************************/          

#ifdef CAN1SR5_ISR
#define IRQ_CAN1SR5_EXIST      STD_ON
#define IRQ_CAN1_SR5_PRIO    CAN1SR5_ISR_ISR_LEVEL
#define IRQ_CAN1_SR5_CAT     CAN1SR5_ISR_ISR_CATEGORY
#else
#define IRQ_CAN1SR5_EXIST      STD_OFF
#endif

/**********************************************************/          

#ifdef CAN1SR6_ISR
#define IRQ_CAN1SR6_EXIST      STD_ON
#define IRQ_CAN1_SR6_PRIO    CAN1SR6_ISR_ISR_LEVEL
#define IRQ_CAN1_SR6_CAT     CAN1SR6_ISR_ISR_CATEGORY
#else
#define IRQ_CAN1SR6_EXIST      STD_OFF
#endif

/**********************************************************/          

#ifdef CAN1SR7_ISR
#define IRQ_CAN1SR7_EXIST      STD_ON
#define IRQ_CAN1_SR7_PRIO    CAN1SR7_ISR_ISR_LEVEL
#define IRQ_CAN1_SR7_CAT     CAN1SR7_ISR_ISR_CATEGORY
#else
#define IRQ_CAN1SR7_EXIST      STD_OFF
#endif

/**********************************************************/          

#ifdef CAN1SR8_ISR
#define IRQ_CAN1SR8_EXIST      STD_ON
#define IRQ_CAN1_SR8_PRIO    CAN1SR8_ISR_ISR_LEVEL
#define IRQ_CAN1_SR8_CAT     CAN1SR8_ISR_ISR_CATEGORY
#else
#define IRQ_CAN1SR8_EXIST      STD_OFF
#endif

/**********************************************************/          

#ifdef CAN1SR9_ISR
#define IRQ_CAN1SR9_EXIST      STD_ON
#define IRQ_CAN1_SR9_PRIO    CAN1SR9_ISR_ISR_LEVEL
#define IRQ_CAN1_SR9_CAT     CAN1SR9_ISR_ISR_CATEGORY
#else
#define IRQ_CAN1SR9_EXIST      STD_OFF
#endif

/**********************************************************/          

#ifdef CAN1SR10_ISR
#define IRQ_CAN1SR10_EXIST      STD_ON
#define IRQ_CAN1_SR10_PRIO    CAN1SR10_ISR_ISR_LEVEL
#define IRQ_CAN1_SR10_CAT     CAN1SR10_ISR_ISR_CATEGORY
#else
#define IRQ_CAN1SR10_EXIST      STD_OFF
#endif

/**********************************************************/          

#ifdef CAN1SR11_ISR
#define IRQ_CAN1SR11_EXIST      STD_ON
#define IRQ_CAN1_SR11_PRIO    CAN1SR11_ISR_ISR_LEVEL
#define IRQ_CAN1_SR11_CAT     CAN1SR11_ISR_ISR_CATEGORY
#else
#define IRQ_CAN1SR11_EXIST      STD_OFF
#endif

/**********************************************************/          

#ifdef CAN1SR12_ISR
#define IRQ_CAN1SR12_EXIST      STD_ON
#define IRQ_CAN1_SR12_PRIO    CAN1SR12_ISR_ISR_LEVEL
#define IRQ_CAN1_SR12_CAT     CAN1SR12_ISR_ISR_CATEGORY
#else
#define IRQ_CAN1SR12_EXIST      STD_OFF
#endif

/**********************************************************/          

#ifdef CAN1SR13_ISR
#define IRQ_CAN1SR13_EXIST      STD_ON
#define IRQ_CAN1_SR13_PRIO    CAN1SR13_ISR_ISR_LEVEL
#define IRQ_CAN1_SR13_CAT     CAN1SR13_ISR_ISR_CATEGORY
#else
#define IRQ_CAN1SR13_EXIST      STD_OFF
#endif

/**********************************************************/          

#ifdef CAN1SR14_ISR
#define IRQ_CAN1SR14_EXIST      STD_ON
#define IRQ_CAN1_SR14_PRIO    CAN1SR14_ISR_ISR_LEVEL
#define IRQ_CAN1_SR14_CAT     CAN1SR14_ISR_ISR_CATEGORY
#else
#define IRQ_CAN1SR14_EXIST      STD_OFF
#endif

/**********************************************************/          

#ifdef CAN1SR15_ISR
#define IRQ_CAN1SR15_EXIST      STD_ON
#define IRQ_CAN1_SR15_PRIO    CAN1SR15_ISR_ISR_LEVEL
#define IRQ_CAN1_SR15_CAT     CAN1SR15_ISR_ISR_CATEGORY
#else
#define IRQ_CAN1SR15_EXIST      STD_OFF
#endif

/**********************************************************/          

#ifdef CAN2SR0_ISR
#define IRQ_CAN2SR0_EXIST      STD_ON
#define IRQ_CAN2_SR0_PRIO    CAN2SR0_ISR_ISR_LEVEL
#define IRQ_CAN2_SR0_CAT     CAN2SR0_ISR_ISR_CATEGORY
#else
#define IRQ_CAN2SR0_EXIST      STD_OFF
#endif

/**********************************************************/          

#ifdef CAN2SR1_ISR
#define IRQ_CAN2SR1_EXIST      STD_ON
#define IRQ_CAN2_SR1_PRIO    CAN2SR1_ISR_ISR_LEVEL
#define IRQ_CAN2_SR1_CAT     CAN2SR1_ISR_ISR_CATEGORY
#else
#define IRQ_CAN2SR1_EXIST      STD_OFF
#endif

/**********************************************************/          

#ifdef CAN2SR2_ISR
#define IRQ_CAN2SR2_EXIST      STD_ON
#define IRQ_CAN2_SR2_PRIO    CAN2SR2_ISR_ISR_LEVEL
#define IRQ_CAN2_SR2_CAT     CAN2SR2_ISR_ISR_CATEGORY
#else
#define IRQ_CAN2SR2_EXIST      STD_OFF
#endif

/**********************************************************/          

#ifdef CAN2SR3_ISR
#define IRQ_CAN2SR3_EXIST      STD_ON
#define IRQ_CAN2_SR3_PRIO    CAN2SR3_ISR_ISR_LEVEL
#define IRQ_CAN2_SR3_CAT     CAN2SR3_ISR_ISR_CATEGORY
#else
#define IRQ_CAN2SR3_EXIST      STD_OFF
#endif

/**********************************************************/          

#ifdef CAN2SR4_ISR
#define IRQ_CAN2SR4_EXIST      STD_ON
#define IRQ_CAN2_SR4_PRIO    CAN2SR4_ISR_ISR_LEVEL
#define IRQ_CAN2_SR4_CAT     CAN2SR4_ISR_ISR_CATEGORY
#else
#define IRQ_CAN2SR4_EXIST      STD_OFF
#endif
/**********************************************************/          

#ifdef CAN2SR5_ISR
#define IRQ_CAN2SR5_EXIST      STD_ON
#define IRQ_CAN2_SR5_PRIO    CAN2SR5_ISR_ISR_LEVEL
#define IRQ_CAN2_SR5_CAT     CAN2SR5_ISR_ISR_CATEGORY
#else
#define IRQ_CAN2SR5_EXIST      STD_OFF
#endif

/**********************************************************/          

#ifdef CAN2SR6_ISR
#define IRQ_CAN2SR6_EXIST      STD_ON
#define IRQ_CAN2_SR6_PRIO    CAN2SR6_ISR_ISR_LEVEL
#define IRQ_CAN2_SR6_CAT     CAN2SR6_ISR_ISR_CATEGORY
#else
#define IRQ_CAN2SR6_EXIST      STD_OFF
#endif

/**********************************************************/          

#ifdef CAN2SR7_ISR
#define IRQ_CAN2SR7_EXIST      STD_ON
#define IRQ_CAN2_SR7_PRIO    CAN2SR7_ISR_ISR_LEVEL
#define IRQ_CAN2_SR7_CAT     CAN2SR7_ISR_ISR_CATEGORY
#else
#define IRQ_CAN2SR7_EXIST      STD_OFF
#endif

/**********************************************************/          

#ifdef CAN2SR8_ISR
#define IRQ_CAN2SR8_EXIST      STD_ON
#define IRQ_CAN2_SR8_PRIO    CAN2SR8_ISR_ISR_LEVEL
#define IRQ_CAN2_SR8_CAT     CAN2SR8_ISR_ISR_CATEGORY
#else
#define IRQ_CAN2SR8_EXIST      STD_OFF
#endif

/**********************************************************/          

#ifdef CAN2SR9_ISR
#define IRQ_CAN2SR9_EXIST      STD_ON
#define IRQ_CAN2_SR9_PRIO    CAN2SR9_ISR_ISR_LEVEL
#define IRQ_CAN2_SR9_CAT     CAN2SR9_ISR_ISR_CATEGORY
#else
#define IRQ_CAN2SR9_EXIST      STD_OFF
#endif

/**********************************************************/          

#ifdef CAN2SR10_ISR
#define IRQ_CAN2SR10_EXIST      STD_ON
#define IRQ_CAN2_SR10_PRIO    CAN2SR10_ISR_ISR_LEVEL
#define IRQ_CAN2_SR10_CAT     CAN2SR10_ISR_ISR_CATEGORY
#else
#define IRQ_CAN2SR10_EXIST      STD_OFF
#endif

/**********************************************************/          

#ifdef CAN2SR11_ISR
#define IRQ_CAN2SR11_EXIST      STD_ON
#define IRQ_CAN2_SR11_PRIO    CAN2SR11_ISR_ISR_LEVEL
#define IRQ_CAN2_SR11_CAT     CAN2SR11_ISR_ISR_CATEGORY
#else
#define IRQ_CAN2SR11_EXIST      STD_OFF
#endif

/**********************************************************/          

#ifdef CAN2SR12_ISR
#define IRQ_CAN2SR12_EXIST      STD_ON
#define IRQ_CAN2_SR12_PRIO    CAN2SR12_ISR_ISR_LEVEL
#define IRQ_CAN2_SR12_CAT     CAN2SR12_ISR_ISR_CATEGORY
#else
#define IRQ_CAN2SR12_EXIST      STD_OFF
#endif

/**********************************************************/          

#ifdef CAN2SR13_ISR
#define IRQ_CAN2SR13_EXIST      STD_ON
#define IRQ_CAN2_SR13_PRIO    CAN2SR13_ISR_ISR_LEVEL
#define IRQ_CAN2_SR13_CAT     CAN2SR13_ISR_ISR_CATEGORY
#else
#define IRQ_CAN2SR13_EXIST      STD_OFF
#endif

/**********************************************************/          

#ifdef CAN2SR14_ISR
#define IRQ_CAN2SR14_EXIST      STD_ON
#define IRQ_CAN2_SR14_PRIO    CAN2SR14_ISR_ISR_LEVEL
#define IRQ_CAN2_SR14_CAT     CAN2SR14_ISR_ISR_CATEGORY
#else
#define IRQ_CAN2SR14_EXIST      STD_OFF
#endif

/**********************************************************/          

#ifdef CAN2SR15_ISR
#define IRQ_CAN2SR15_EXIST      STD_ON
#define IRQ_CAN2_SR15_PRIO    CAN2SR15_ISR_ISR_LEVEL
#define IRQ_CAN2_SR15_CAT     CAN2SR15_ISR_ISR_CATEGORY
#else
#define IRQ_CAN2SR15_EXIST      STD_OFF
#endif

#endif /* #ifndef CAN_17_MCANP_IRQ_H */

