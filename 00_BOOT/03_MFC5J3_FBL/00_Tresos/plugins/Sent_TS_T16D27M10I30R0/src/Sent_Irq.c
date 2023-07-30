/******************************************************************************
**                                                                           **
** Copyright (C) Infineon Technologies (2013)                                **
**                                                                           **
** All rights reserved.                                                      **
**                                                                           **
** This document contains proprietary information belonging to Infineon      **
** Technologies. Passing on and copying of this document, and communication  **
** of its contents is not permitted without prior written authorization.     **
**                                                                           **
*******************************************************************************
**                                                                           **
**  $FILENAME   : Sent_Irq.c $                                               **
**                                                                           **
**  $CC VERSION : \main\11 $                                                 **
**                                                                           **
**  $DATE       : 2016-06-27 $                                               **
**                                                                           **
**  AUTHOR      : DL-AUTOSAR-Engineering                                     **
**                                                                           **
**  VENDOR      : Infineon Technologies                                      **
**                                                                           **
**  DESCRIPTION : This file contains the interrupt frames for the SENT. This **
**                file is given for evaluation purpose only.                 **
**                                                                           **
**  MAY BE CHANGED BY USER [yes/no]: Yes                                     **
**                                                                           **
******************************************************************************/
/*******************************************************************************
**                      Includes                                              **
*******************************************************************************/
/* Inclusion of Tasking sfr file */


/*Include Irq Module*/
#include "Irq.h"

/* Include Mcal.h to import the library functions */ 
#include "Mcal.h"

/* Include SENT header file  */
#include "Sent.h"

/* Include SENT IRQ header file  */
#include "Sent_Irq.h"
/*******************************************************************************
**                      Imported Compiler Switch Checks                       **
*******************************************************************************/

/*******************************************************************************
**                      Private Macro Definitions                             **
*******************************************************************************/

/*******************************************************************************
**                      Private Type Definitions                              **
*******************************************************************************/

/*******************************************************************************
**                      Private Function Declarations                         **
*******************************************************************************/

/*******************************************************************************
**                      Global Constant Definitions                           **
*******************************************************************************/

/*******************************************************************************
**                      Global Variable Definitions                           **
*******************************************************************************/

/*******************************************************************************
**                      Private Constant Definitions                          **
*******************************************************************************/

/*******************************************************************************
**                      Private Variable Definitions                          **
*******************************************************************************/

/*******************************************************************************
**                      Private Function Definitions                          **
*******************************************************************************/

/*******************************************************************************
**                      Global Function Definitions                           **
*******************************************************************************/
#define IRQ_START_SEC_CODE
#include "MemMap.h"

#if (IRQ_SENT_EXIST == STD_ON)

/******************************************************************************
** Syntax : void SENTSR0_ISR(void)                                          **
**                                                                           **
** Service ID:       NA                                                      **
**                                                                           **
** Sync/Async:       Synchronous                                             **
**                                                                           **
** Reentrancy:       reentrant                                               **
**                                                                           **
** Parameters (in):  none                                                    **
**                                                                           **
** Parameters (out): none                                                    **
**                                                                           **
** Return value:     none                                                    **
**                                                                           **
** Description : Service for SENT Interrupt Node 0                           **
**                                                                           **
*****************************************************************************/
#if(IRQ_SENTSR0_EXIST == STD_ON)
#if((IRQ_SENT_SR0_PRIO > 0) || (IRQ_SENT_SR0_CAT == IRQ_CAT23))
#if((IRQ_SENT_SR0_PRIO > 0) && (IRQ_SENT_SR0_CAT == IRQ_CAT1))
IFX_INTERRUPT(SENTSR0_ISR, 0, IRQ_SENT_SR0_PRIO)
#elif IRQ_SENT_SR0_CAT == IRQ_CAT23
ISR(SENTSR0_ISR)
#endif
{
  /* Enable Global Interrupts */
#if (IRQ_SENT_SR0_CAT == IRQ_CAT1)
  Mcal_EnableAllInterrupts();
#endif
  
  Sent_Isr(Sent_kConfigPtr->SrnToChanMapPtr[0]);
}
#endif
#endif

/******************************************************************************
** Syntax : void SENTSR1_ISR(void)                                          **
**                                                                           **
** Service ID:       NA                                                      **
**                                                                           **
** Sync/Async:       Synchronous                                             **
**                                                                           **
** Reentrancy:       reentrant                                               **
**                                                                           **
** Parameters (in):  none                                                    **
**                                                                           **
** Parameters (out): none                                                    **
**                                                                           **
** Return value:     none                                                    **
**                                                                           **
** Description : Service for SENT Interrupt Node 1                           **
**                                                                           **
*****************************************************************************/
#if(IRQ_SENTSR1_EXIST == STD_ON)
#if((IRQ_SENT_SR1_PRIO > 0) || (IRQ_SENT_SR1_CAT == IRQ_CAT23))
#if((IRQ_SENT_SR1_PRIO > 0) && (IRQ_SENT_SR1_CAT == IRQ_CAT1))
IFX_INTERRUPT(SENTSR1_ISR, 0, IRQ_SENT_SR1_PRIO)
#elif IRQ_SENT_SR1_CAT == IRQ_CAT23
ISR(SENTSR1_ISR)
#endif
{
  /* Enable Global Interrupts */
#if (IRQ_SENT_SR1_CAT == IRQ_CAT1)
  Mcal_EnableAllInterrupts();
#endif
  
  Sent_Isr(Sent_kConfigPtr->SrnToChanMapPtr[1]);
}
#endif
#endif

/******************************************************************************
** Syntax : void SENTSR2_ISR(void)                                          **
**                                                                           **
** Service ID:       NA                                                      **
**                                                                           **
** Sync/Async:       Synchronous                                             **
**                                                                           **
** Reentrancy:       reentrant                                               **
**                                                                           **
** Parameters (in):  none                                                    **
**                                                                           **
** Parameters (out): none                                                    **
**                                                                           **
** Return value:     none                                                    **
**                                                                           **
** Description : Service for SENT Interrupt Node 2                           **
**                                                                           **
*****************************************************************************/
#if(IRQ_SENTSR2_EXIST == STD_ON)
#if((IRQ_SENT_SR2_PRIO > 0) || (IRQ_SENT_SR2_CAT == IRQ_CAT23))
#if((IRQ_SENT_SR2_PRIO > 0) && (IRQ_SENT_SR2_CAT == IRQ_CAT1))
IFX_INTERRUPT(SENTSR2_ISR, 0, IRQ_SENT_SR2_PRIO)
#elif IRQ_SENT_SR2_CAT == IRQ_CAT23
ISR(SENTSR2_ISR)
#endif
{
  /* Enable Global Interrupts */
#if (IRQ_SENT_SR2_CAT == IRQ_CAT1)
  Mcal_EnableAllInterrupts();
#endif
  
  Sent_Isr(Sent_kConfigPtr->SrnToChanMapPtr[2]);
}
#endif
#endif

/******************************************************************************
** Syntax : void SENTSR3_ISR(void)                                          **
**                                                                           **
** Service ID:       NA                                                      **
**                                                                           **
** Sync/Async:       Synchronous                                             **
**                                                                           **
** Reentrancy:       reentrant                                               **
**                                                                           **
** Parameters (in):  none                                                    **
**                                                                           **
** Parameters (out): none                                                    **
**                                                                           **
** Return value:     none                                                    **
**                                                                           **
** Description : Service for SENT Interrupt Node 3                           **
**                                                                           **
*****************************************************************************/
#if(IRQ_SENTSR3_EXIST == STD_ON)
#if((IRQ_SENT_SR3_PRIO > 0) || (IRQ_SENT_SR3_CAT == IRQ_CAT23))
#if((IRQ_SENT_SR3_PRIO > 0) && (IRQ_SENT_SR3_CAT == IRQ_CAT1))
IFX_INTERRUPT(SENTSR3_ISR, 0, IRQ_SENT_SR3_PRIO)
#elif IRQ_SENT_SR3_CAT == IRQ_CAT23
ISR(SENTSR3_ISR)
#endif
{
  /* Enable Global Interrupts */
#if (IRQ_SENT_SR3_CAT == IRQ_CAT1)
  Mcal_EnableAllInterrupts();
#endif
  
  Sent_Isr(Sent_kConfigPtr->SrnToChanMapPtr[3]);
}
#endif
#endif

/******************************************************************************
** Syntax : void SENTSR4_ISR(void)                                          **
**                                                                           **
** Service ID:       NA                                                      **
**                                                                           **
** Sync/Async:       Synchronous                                             **
**                                                                           **
** Reentrancy:       reentrant                                               **
**                                                                           **
** Parameters (in):  none                                                    **
**                                                                           **
** Parameters (out): none                                                    **
**                                                                           **
** Return value:     none                                                    **
**                                                                           **
** Description : Service for SENT Interrupt Node 4                           **
**                                                                           **
*****************************************************************************/
#if(IRQ_SENTSR4_EXIST == STD_ON)
#if((IRQ_SENT_SR4_PRIO > 0) || (IRQ_SENT_SR4_CAT == IRQ_CAT23))
#if((IRQ_SENT_SR4_PRIO > 0) && (IRQ_SENT_SR4_CAT == IRQ_CAT1))
IFX_INTERRUPT(SENTSR4_ISR, 0, IRQ_SENT_SR4_PRIO)
#elif IRQ_SENT_SR4_CAT == IRQ_CAT23
ISR(SENTSR4_ISR)
#endif
{
  /* Enable Global Interrupts */
#if (IRQ_SENT_SR4_CAT == IRQ_CAT1)
  Mcal_EnableAllInterrupts();
#endif
  
  Sent_Isr(Sent_kConfigPtr->SrnToChanMapPtr[4]);
}
#endif
#endif
/******************************************************************************
** Syntax : void SENTSR5_ISR(void)                                          **
**                                                                           **
** Service ID:       NA                                                      **
**                                                                           **
** Sync/Async:       Synchronous                                             **
**                                                                           **
** Reentrancy:       reentrant                                               **
**                                                                           **
** Parameters (in):  none                                                    **
**                                                                           **
** Parameters (out): none                                                    **
**                                                                           **
** Return value:     none                                                    **
**                                                                           **
** Description : Service for SENT Interrupt Node 5                           **
**                                                                           **
*****************************************************************************/
#if(IRQ_SENTSR5_EXIST == STD_ON)
#if((IRQ_SENT_SR5_PRIO > 0) || (IRQ_SENT_SR5_CAT == IRQ_CAT23))
#if((IRQ_SENT_SR5_PRIO > 0) && (IRQ_SENT_SR5_CAT == IRQ_CAT1))
IFX_INTERRUPT(SENTSR5_ISR, 0, IRQ_SENT_SR5_PRIO)
#elif IRQ_SENT_SR5_CAT == IRQ_CAT23
ISR(SENTSR5_ISR)
#endif
{
  /* Enable Global Interrupts */
#if (IRQ_SENT_SR5_CAT == IRQ_CAT1)
  Mcal_EnableAllInterrupts();
#endif
  
  Sent_Isr(Sent_kConfigPtr->SrnToChanMapPtr[5]);
}
#endif
#endif

/******************************************************************************
** Syntax : void SENTSR6_ISR(void)                                          **
**                                                                           **
** Service ID:       NA                                                      **
**                                                                           **
** Sync/Async:       Synchronous                                             **
**                                                                           **
** Reentrancy:       reentrant                                               **
**                                                                           **
** Parameters (in):  none                                                    **
**                                                                           **
** Parameters (out): none                                                    **
**                                                                           **
** Return value:     none                                                    **
**                                                                           **
** Description : Service for SENT Interrupt Node 6                           **
**                                                                           **
*****************************************************************************/
#if(IRQ_SENTSR6_EXIST == STD_ON)
#if((IRQ_SENT_SR6_PRIO > 0) || (IRQ_SENT_SR6_CAT == IRQ_CAT23))
#if((IRQ_SENT_SR6_PRIO > 0) && (IRQ_SENT_SR6_CAT == IRQ_CAT1))
IFX_INTERRUPT(SENTSR6_ISR, 0, IRQ_SENT_SR6_PRIO)
#elif IRQ_SENT_SR6_CAT == IRQ_CAT23
ISR(SENTSR6_ISR)
#endif
{
  /* Enable Global Interrupts */
#if (IRQ_SENT_SR6_CAT == IRQ_CAT1)
  Mcal_EnableAllInterrupts();
#endif
  
  Sent_Isr(Sent_kConfigPtr->SrnToChanMapPtr[6]);
}
#endif
#endif

/******************************************************************************
** Syntax : void SENTSR7_ISR(void)                                          **
**                                                                           **
** Service ID:       NA                                                      **
**                                                                           **
** Sync/Async:       Synchronous                                             **
**                                                                           **
** Reentrancy:       reentrant                                               **
**                                                                           **
** Parameters (in):  none                                                    **
**                                                                           **
** Parameters (out): none                                                    **
**                                                                           **
** Return value:     none                                                    **
**                                                                           **
** Description : Service for SENT Interrupt Node 7                           **
**                                                                           **
*****************************************************************************/
#if(IRQ_SENTSR7_EXIST == STD_ON)
#if((IRQ_SENT_SR7_PRIO > 0) || (IRQ_SENT_SR7_CAT == IRQ_CAT23))
#if((IRQ_SENT_SR7_PRIO > 0) && (IRQ_SENT_SR7_CAT == IRQ_CAT1))
IFX_INTERRUPT(SENTSR7_ISR, 0, IRQ_SENT_SR7_PRIO)
#elif IRQ_SENT_SR7_CAT == IRQ_CAT23
ISR(SENTSR7_ISR)
#endif
{
  /* Enable Global Interrupts */
#if (IRQ_SENT_SR7_CAT == IRQ_CAT1)
  Mcal_EnableAllInterrupts();
#endif
  
  Sent_Isr(Sent_kConfigPtr->SrnToChanMapPtr[7]);
}
#endif
#endif

/******************************************************************************
** Syntax : void SENTSR8_ISR(void)                                          **
**                                                                           **
** Service ID:       NA                                                      **
**                                                                           **
** Sync/Async:       Synchronous                                             **
**                                                                           **
** Reentrancy:       reentrant                                               **
**                                                                           **
** Parameters (in):  none                                                    **
**                                                                           **
** Parameters (out): none                                                    **
**                                                                           **
** Return value:     none                                                    **
**                                                                           **
** Description : Service for SENT Interrupt Node 8                           **
**                                                                           **
*****************************************************************************/
#if(IRQ_SENTSR8_EXIST == STD_ON)
#if((IRQ_SENT_SR8_PRIO > 0) || (IRQ_SENT_SR8_CAT == IRQ_CAT23))
#if((IRQ_SENT_SR8_PRIO > 0) && (IRQ_SENT_SR8_CAT == IRQ_CAT1))
IFX_INTERRUPT(SENTSR8_ISR, 0, IRQ_SENT_SR8_PRIO)
#elif IRQ_SENT_SR8_CAT == IRQ_CAT23
ISR(SENTSR8_ISR)
#endif
{
  /* Enable Global Interrupts */
#if (IRQ_SENT_SR8_CAT == IRQ_CAT1)
  Mcal_EnableAllInterrupts();
#endif
  
  Sent_Isr(Sent_kConfigPtr->SrnToChanMapPtr[8]);
}
#endif
#endif

/******************************************************************************
** Syntax : void SENTSR9_ISR(void)                                          **
**                                                                           **
** Service ID:       NA                                                      **
**                                                                           **
** Sync/Async:       Synchronous                                             **
**                                                                           **
** Reentrancy:       reentrant                                               **
**                                                                           **
** Parameters (in):  none                                                    **
**                                                                           **
** Parameters (out): none                                                    **
**                                                                           **
** Return value:     none                                                    **
**                                                                           **
** Description : Service for SENT Interrupt Node 9                           **
**                                                                           **
*****************************************************************************/
#if(IRQ_SENTSR9_EXIST == STD_ON)
#if((IRQ_SENT_SR9_PRIO > 0) || (IRQ_SENT_SR9_CAT == IRQ_CAT23))
#if((IRQ_SENT_SR9_PRIO > 0) && (IRQ_SENT_SR9_CAT == IRQ_CAT1))
IFX_INTERRUPT(SENTSR9_ISR, 0, IRQ_SENT_SR9_PRIO)
#elif IRQ_SENT_SR9_CAT == IRQ_CAT23
ISR(SENTSR9_ISR)
#endif
{
  /* Enable Global Interrupts */
#if (IRQ_SENT_SR9_CAT == IRQ_CAT1)
  Mcal_EnableAllInterrupts();
#endif
  
  Sent_Isr(Sent_kConfigPtr->SrnToChanMapPtr[9]);
}
#endif
#endif

/******************************************************************************
** Syntax : void SENTSR10_ISR(void)                                          **
**                                                                           **
** Service ID:       NA                                                      **
**                                                                           **
** Sync/Async:       Synchronous                                             **
**                                                                           **
** Reentrancy:       reentrant                                               **
**                                                                           **
** Parameters (in):  none                                                    **
**                                                                           **
** Parameters (out): none                                                    **
**                                                                           **
** Return value:     none                                                    **
**                                                                           **
** Description : Service for SENT Interrupt Node 10                          **
**                                                                           **
*****************************************************************************/
#if(IRQ_SENTSR10_EXIST == STD_ON)
#if((IRQ_SENT_SR10_PRIO > 0) || (IRQ_SENT_SR10_CAT == IRQ_CAT23))
#if((IRQ_SENT_SR10_PRIO > 0) && (IRQ_SENT_SR10_CAT == IRQ_CAT1))
IFX_INTERRUPT(SENTSR10_ISR, 0, IRQ_SENT_SR10_PRIO)
#elif IRQ_SENT_SR10_CAT == IRQ_CAT23
ISR(SENTSR10_ISR)
#endif
{
  /* Enable Global Interrupts */
#if (IRQ_SENT_SR10_CAT == IRQ_CAT1)
  Mcal_EnableAllInterrupts();
#endif
  
  Sent_Isr(Sent_kConfigPtr->SrnToChanMapPtr[10]);
}
#endif
#endif

/******************************************************************************
** Syntax : void SENTSR11_ISR(void)                                          **
**                                                                           **
** Service ID:       NA                                                      **
**                                                                           **
** Sync/Async:       Synchronous                                             **
**                                                                           **
** Reentrancy:       reentrant                                               **
**                                                                           **
** Parameters (in):  none                                                    **
**                                                                           **
** Parameters (out): none                                                    **
**                                                                           **
** Return value:     none                                                    **
**                                                                           **
** Description : Service for SENT Interrupt Node 11                          **
**                                                                           **
*****************************************************************************/
#if(IRQ_SENTSR11_EXIST == STD_ON)
#if((IRQ_SENT_SR11_PRIO > 0) || (IRQ_SENT_SR11_CAT == IRQ_CAT23))
#if((IRQ_SENT_SR11_PRIO > 0) && (IRQ_SENT_SR11_CAT == IRQ_CAT1))
IFX_INTERRUPT(SENTSR11_ISR, 0, IRQ_SENT_SR11_PRIO)
#elif IRQ_SENT_SR11_CAT == IRQ_CAT23
ISR(SENTSR11_ISR)
#endif
{
  /* Enable Global Interrupts */
#if (IRQ_SENT_SR11_CAT == IRQ_CAT1)
  Mcal_EnableAllInterrupts();
#endif
  
  Sent_Isr(Sent_kConfigPtr->SrnToChanMapPtr[11]);
}
#endif
#endif

/******************************************************************************
** Syntax : void SENTSR12_ISR(void)                                          **
**                                                                           **
** Service ID:       NA                                                      **
**                                                                           **
** Sync/Async:       Synchronous                                             **
**                                                                           **
** Reentrancy:       reentrant                                               **
**                                                                           **
** Parameters (in):  none                                                    **
**                                                                           **
** Parameters (out): none                                                    **
**                                                                           **
** Return value:     none                                                    **
**                                                                           **
** Description : Service for SENT Interrupt Node 12                          **
**                                                                           **
*****************************************************************************/
#if(IRQ_SENTSR12_EXIST == STD_ON)
#if((IRQ_SENT_SR12_PRIO > 0) || (IRQ_SENT_SR12_CAT == IRQ_CAT23))
#if((IRQ_SENT_SR12_PRIO > 0) && (IRQ_SENT_SR12_CAT == IRQ_CAT1))
IFX_INTERRUPT(SENTSR12_ISR, 0, IRQ_SENT_SR12_PRIO)
#elif IRQ_SENT_SR12_CAT == IRQ_CAT23
ISR(SENTSR12_ISR)
#endif
{
  /* Enable Global Interrupts */
#if (IRQ_SENT_SR12_CAT == IRQ_CAT1)
  Mcal_EnableAllInterrupts();
#endif
  
  Sent_Isr(Sent_kConfigPtr->SrnToChanMapPtr[12]);
}
#endif
#endif

/******************************************************************************
** Syntax : void SENTSR13_ISR(void)                                          **
**                                                                           **
** Service ID:       NA                                                      **
**                                                                           **
** Sync/Async:       Synchronous                                             **
**                                                                           **
** Reentrancy:       reentrant                                               **
**                                                                           **
** Parameters (in):  none                                                    **
**                                                                           **
** Parameters (out): none                                                    **
**                                                                           **
** Return value:     none                                                    **
**                                                                           **
** Description : Service for SENT Interrupt Node 13                          **
**                                                                           **
*****************************************************************************/
#if(IRQ_SENTSR13_EXIST == STD_ON)
#if((IRQ_SENT_SR13_PRIO > 0) || (IRQ_SENT_SR13_CAT == IRQ_CAT23))
#if((IRQ_SENT_SR13_PRIO > 0) && (IRQ_SENT_SR13_CAT == IRQ_CAT1))
IFX_INTERRUPT(SENTSR13_ISR, 0, IRQ_SENT_SR13_PRIO)
#elif IRQ_SENT_SR13_CAT == IRQ_CAT23
ISR(SENTSR13_ISR)
#endif
{
  /* Enable Global Interrupts */
#if (IRQ_SENT_SR13_CAT == IRQ_CAT1)
  Mcal_EnableAllInterrupts();
#endif
  
  Sent_Isr(Sent_kConfigPtr->SrnToChanMapPtr[13]);
}
#endif
#endif

/******************************************************************************
** Syntax : void SENTSR14_ISR(void)                                          **
**                                                                           **
** Service ID:       NA                                                      **
**                                                                           **
** Sync/Async:       Synchronous                                             **
**                                                                           **
** Reentrancy:       reentrant                                               **
**                                                                           **
** Parameters (in):  none                                                    **
**                                                                           **
** Parameters (out): none                                                    **
**                                                                           **
** Return value:     none                                                    **
**                                                                           **
** Description : Service for SENT Interrupt Node 14                          **
**                                                                           **
*****************************************************************************/
#if(IRQ_SENTSR14_EXIST == STD_ON)
#if((IRQ_SENT_SR14_PRIO > 0) || (IRQ_SENT_SR14_CAT == IRQ_CAT23))
#if((IRQ_SENT_SR14_PRIO > 0) && (IRQ_SENT_SR14_CAT == IRQ_CAT1))
IFX_INTERRUPT(SENTSR14_ISR, 0, IRQ_SENT_SR14_PRIO)
#elif IRQ_SENT_SR14_CAT == IRQ_CAT23
ISR(SENTSR14_ISR)
#endif
{
  /* Enable Global Interrupts */
#if (IRQ_SENT_SR14_CAT == IRQ_CAT1)
  Mcal_EnableAllInterrupts();
#endif
  
  Sent_Isr(Sent_kConfigPtr->SrnToChanMapPtr[14]);
}
#endif
#endif

#endif

#define IRQ_STOP_SEC_CODE
#include "MemMap.h"
