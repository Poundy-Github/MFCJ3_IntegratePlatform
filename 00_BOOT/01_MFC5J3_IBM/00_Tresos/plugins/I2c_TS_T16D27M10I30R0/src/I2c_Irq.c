/*******************************************************************************
**                                                                            **
** Copyright (C) Infineon Technologies (2018)                                 **
**                                                                            **
** All rights reserved.                                                       **
**                                                                            **
** This document contains proprietary information belonging to Infineon       **
** Technologies. Passing on and copying of this document, and communication   **
** of its contents is not permitted without prior written authorization.      **
**                                                                            **
********************************************************************************
**                                                                            **
**  FILENAME  : I2c_Irq.c                                                     **
**                                                                            **
**  VERSION   : 2.0.0                                                         **
**                                                                            **
**  DATE      : 2018-12-20                                                    **
**                                                                            **
**  VARIANT   : Post-Build                                                    **
**                                                                            **
**  PLATFORM  : Infineon AURIX2G                                              **
**                                                                            **
**  AUTHOR    : DL-AUTOSAR-Engineering                                        **
**                                                                            **
**  VENDOR    : Infineon Technologies                                         **
**                                                                            **
**  DESCRIPTION : This file contains the interrupt frames for the I2C Module. **
**                                                                            **
**  SPECIFICATION(S) : Specification of I2C Driver, AUTOSAR Release 4.2.2     **
**                                                                            **
**  MAY BE CHANGED BY USER : Yes                                              **
**                                                                            **
*******************************************************************************/

/*******************************************************************************
**                      Includes                                              **
*******************************************************************************/
#include "I2c.h"
#include "Irq.h"
#include "IFX_Os.h"
#include "I2c_Irq.h"

/*******************************************************************************
** Syntax          : void I2C0DTR_ISR(void)                                   **
**                                                                            **
** Service ID      : NA                                                       **
**                                                                            **
** Sync/Async      : Synchronous                                              **
**                                                                            **
** Reentrancy      : reentrant                                                **
**                                                                            **
** Parameters (in) : none                                                     **
**                                                                            **
** Parameters (out): none                                                     **
**                                                                            **
** Return value    : none                                                     **
**                                                                            **
** Description     : Service for DTR interrupt of I2Cx                        **
**                                                                            **
*******************************************************************************/
#if ((IRQ_I2C0DTR_EXIST == STD_ON))
#if ((IRQ_I2C_DTR_SR0_PRIO > 0) || (IRQ_I2C_DTR_SR0_CAT == IRQ_CAT2))
#if ((IRQ_I2C_DTR_SR0_PRIO > 0) && (IRQ_I2C_DTR_SR0_CAT == IRQ_CAT1))
IFX_INTERRUPT(I2C0DTR_ISR, 0, IRQ_I2C_DTR_SR0_PRIO)
#elif IRQ_I2C_DTR_SR0_CAT == IRQ_CAT2
ISR(I2C0DTR_ISR)
#endif
{
  /* Enable Global Interrupts */
  /*  ENABLE();*/
  /* Call data transfer interrupt funtion */
    I2c_IsrI2cDtr(I2C_ZERO);
}
#endif
#endif

#if ((IRQ_I2C1DTR_EXIST == STD_ON))
#if ((IRQ_I2C_DTR_SR1_PRIO > 0) || (IRQ_I2C_DTR_SR1_CAT == IRQ_CAT2))
#if ((IRQ_I2C_DTR_SR1_PRIO > 0) && (IRQ_I2C_DTR_SR1_CAT == IRQ_CAT1))
IFX_INTERRUPT(I2C1DTR_ISR, 0, IRQ_I2C_DTR_SR1_PRIO)
#elif IRQ_I2C_DTR_SR1_CAT == IRQ_CAT2
ISR(I2C1DTR_ISR)
#endif
{
  /* Enable Global Interrupts */
  /*  ENABLE();*/
  /* Call data transfer interrupt funtion */
  I2c_IsrI2cDtr(I2C_ONE);
}
#endif
#endif

/*******************************************************************************
** Syntax          : void I2C0P_ISR(void)                                     **
**                                                                            **
** Service ID      : NA                                                       **
**                                                                            **
** Sync/Async      : Synchronous                                              **
**                                                                            **
** Reentrancy      : reentrant                                                **
**                                                                            **
** Parameters (in) : none                                                     **
**                                                                            **
** Parameters (out): none                                                     **
**                                                                            **
** Return value    : none                                                     **
**                                                                            **
** Description     : Service for P interrupt of I2Cx                          **
**                                                                            **
*******************************************************************************/
#if ((IRQ_I2C0P_EXIST == STD_ON))
#if ((IRQ_I2C_P_SR0_PRIO > 0) || (IRQ_I2C_P_SR0_CAT == IRQ_CAT2))
#if ((IRQ_I2C_P_SR0_PRIO > 0) && (IRQ_I2C_P_SR0_CAT == IRQ_CAT1))
IFX_INTERRUPT(I2C0P_ISR, 0, IRQ_I2C_P_SR0_PRIO)
#elif IRQ_I2C_P_SR0_CAT == IRQ_CAT2
ISR(I2C0P_ISR)
#endif
{
  /* Enable Global Interrupts */
  /*  ENABLE();*/
  /* Call Protocol interrupt funtion */
  I2c_IsrI2cProtocol(I2C_ZERO);
}
#endif
#endif

#if ((IRQ_I2C1P_EXIST == STD_ON))
#if ((IRQ_I2C_P_SR1_PRIO > 0) || (IRQ_I2C_P_SR1_CAT == IRQ_CAT2))
#if ((IRQ_I2C_P_SR1_PRIO > 0) && (IRQ_I2C_P_SR1_CAT == IRQ_CAT1))
IFX_INTERRUPT(I2C1P_ISR, 0, IRQ_I2C_P_SR1_PRIO)
#elif IRQ_I2C_P_SR1_CAT == IRQ_CAT2
ISR(I2C1P_ISR)
#endif
{
  /* Enable Global Interrupts */
  /*  ENABLE();*/
  /* Call Protocol interrupt funtion */
  I2c_IsrI2cProtocol(I2C_ONE);
}
#endif
#endif


/*******************************************************************************
** Syntax          : void I2C0E_ISR(void)                                     **
**                                                                            **
** Service ID      : NA                                                       **
**                                                                            **
** Sync/Async      : Synchronous                                              **
**                                                                            **
** Reentrancy      : reentrant                                                **
**                                                                            **
** Parameters (in) : none                                                     **
**                                                                            **
** Parameters (out): none                                                     **
**                                                                            **
** Return value    : none                                                     **
**                                                                            **
** Description     : Service for Error interrupt of I2Cx                      **
**                                                                            **
*******************************************************************************/
#if ((IRQ_I2C0E_EXIST == STD_ON))
#if ((IRQ_I2C_ERR_SR0_PRIO > 0) || (IRQ_I2C_ERR_SR0_CAT == IRQ_CAT2))
#if ((IRQ_I2C_ERR_SR0_PRIO > 0) && (IRQ_I2C_ERR_SR0_CAT == IRQ_CAT1))
IFX_INTERRUPT(I2C0E_ISR, 0, IRQ_I2C_ERR_SR0_PRIO)
#elif IRQ_I2C_ERR_SR0_CAT == IRQ_CAT2
ISR(I2C0E_ISR)
#endif
{
  /* Enable Global Interrupts */
  /*  ENABLE();*/
  /* Call error interrupt funtion */
  I2c_IsrI2cError(I2C_ZERO);
}
#endif
#endif

#if ((IRQ_I2C1E_EXIST == STD_ON))
#if ((IRQ_I2C_ERR_SR1_PRIO > 0) || (IRQ_I2C_ERR_SR1_CAT == IRQ_CAT2))
#if ((IRQ_I2C_ERR_SR1_PRIO > 0) && (IRQ_I2C_ERR_SR1_CAT == IRQ_CAT1))
IFX_INTERRUPT(I2C1E_ISR, 0, IRQ_I2C_ERR_SR1_PRIO)
#elif IRQ_I2C_ERR_SR1_CAT == IRQ_CAT2
ISR(I2C1E_ISR)
#endif
{
  /* Enable Global Interrupts */
  /*  ENABLE();*/
  /* Call error interrupt funtion */
  I2c_IsrI2cError(I2C_ONE);
}
#endif
#endif
