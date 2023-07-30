/*******************************************************************************
**                                                                            **
** Copyright (C) Infineon Technologies (2017)                                 **
**                                                                            **
** All rights reserved.                                                       **
**                                                                            **
** This document contains proprietary information belonging to Infineon       **
** Technologies. Passing on and copying of this document, and communication   **
** of its contents is not permitted without prior written authorization.      **
**                                                                            **
********************************************************************************
**                                                                            **
**  FILENAME     : SchM_McalLib.h                                             **
**                                                                            **
**  VERSION      : 1.0.0                                                      **
**                                                                            **
**  DATE         : 2017-11-08                                                 **
**                                                                            **
**  VARIANT      : Variant PC                                                 **
**                                                                            **
**  PLATFORM     : Infineon AURIX2G                                           **
**                                                                            **
**  AUTHOR       : DL-AUTOSAR-Engineering                                     **
**                                                                            **
**  VENDOR       : Infineon Technologies                                      **
**                                                                            **
**  DESCRIPTION  : SchM file for McalLib                                      **
**                                                                            **
**  SPECIFICATION(S) : NA                                                     **
**                                                                            **
**  MAY BE CHANGED BY USER : yes                                              **
**                                                                            **
*******************************************************************************/

#ifndef MCAL_LIB_SCHM_H
#define MCAL_LIB_SCHM_H
/*******************************************************************************
**                      Includes                                              **
*******************************************************************************/
#include "Std_Types.h"

/*******************************************************************************
** Traceability     :                                                         **
**                                                                            **
** Syntax           : void SchM_Enter_McalLib_PeripheralEndInit(void)         **
**                                                                            **
** Description      : Enters Module exclusive area                            **
**                                                                            **
** Service ID       : NA                                                      **
**                                                                            **
** Sync/Async       : Synchronous                                             **
**                                                                            **
** Reentrancy       : Not Reentrant                                           **
**                                                                            **
** Parameters(in)   : None                                                    **
** Parameters (out) : None                                                    **
**                                                                            **
** Return value     : None                                                    **
**                                                                            **
*******************************************************************************/
extern void SchM_Enter_McalLib_PeripheralEndInit(void);
/*******************************************************************************
** Traceability     :                                                         **
**                                                                            **
** Syntax           : void SchM_Exit_McalLib_PeripheralEndInit(void)          **
**                                                                            **
** Description      : Exit Module exclusive area                              **
**                                                                            **
** Service ID       : NA                                                      **
**                                                                            **
** Sync/Async       : Synchronous                                             **
**                                                                            **
** Reentrancy       : Not Reentrant                                           **
**                                                                            **
** Parameters(in)   : None                                                    **
** Parameters (out) : None                                                    **
**                                                                            **
** Return value     : None                                                    **
**                                                                            **
*******************************************************************************/
extern void SchM_Exit_McalLib_PeripheralEndInit(void);
/*******************************************************************************
** Traceability     :                                                         **
**                                                                            **
** Syntax           : void SchM_Enter_McalLib_SafetyEndInit(void)             **
**                                                                            **
** Description      : Enters Module exclusive area                            **
**                                                                            **
** Service ID       : NA                                                      **
**                                                                            **
** Sync/Async       : Synchronous                                             **
**                                                                            **
** Reentrancy       : Not Reentrant                                           **
**                                                                            **
** Parameters(in)   : None                                                    **
** Parameters (out) : None                                                    **
**                                                                            **
** Return value     : None                                                    **
**                                                                            **
*******************************************************************************/
extern void SchM_Enter_McalLib_SafetyEndInit(void);
/*******************************************************************************
** Traceability     :                                                         **
**                                                                            **
** Syntax           : void SchM_Exit_McalLib_SafetyEndInit(void)              **
**                                                                            **
** Description      : Exit Module exclusive area                              **
**                                                                            **
** Service ID       : NA                                                      **
**                                                                            **
** Sync/Async       : Synchronous                                             **
**                                                                            **
** Reentrancy       : Not Reentrant                                           **
**                                                                            **
** Parameters(in)   : None                                                    **
** Parameters (out) : None                                                    **
**                                                                            **
** Return value     : None                                                    **
**                                                                            **
*******************************************************************************/
extern void SchM_Exit_McalLib_SafetyEndInit(void);
/*******************************************************************************
** Traceability     :                                                         **
**                                                                            **
** Syntax           : void SchM_Enter_McalLib_CpuEndInit(void)                **
**                                                                            **
** Description      : Enters Module exclusive area                            **
**                                                                            **
** Service ID       : NA                                                      **
**                                                                            **
** Sync/Async       : Synchronous                                             **
**                                                                            **
** Reentrancy       : Not Reentrant on same CPU, Reentrant on other CPUs      **
**                                                                            **
** Parameters(in)   : None                                                    **
** Parameters (out) : None                                                    **
** Return value     : None                                                    **
**                                                                            **
*******************************************************************************/
extern void SchM_Enter_McalLib_CpuEndInit(void);
/*******************************************************************************
** Traceability     :                                                         **
**                                                                            **
** Syntax           : void SchM_Exit_McalLib_CpuEndInit(void)                 **
**                                                                            **
** Description      : Exit Module exclusive area                              **
**                                                                            **
** Service ID       : NA                                                      **
**                                                                            **
** Sync/Async       : Synchronous                                             **
**                                                                            **
** Reentrancy       : Not Reentrant on same CPU, Reentrant on other CPUs      **
**                                                                            **
** Parameters(in)   : None                                                    **
** Parameters (out) : None                                                    **
**                                                                            **
** Return value     : None                                                    **
**                                                                            **
*******************************************************************************/
extern void SchM_Exit_McalLib_CpuEndInit(void);
/*******************************************************************************
** Traceability     :                                                         **
**                                                                            **
** Syntax           : void SchM_Enter_McalLib_StmTimerResolution(void)        **
**                                                                            **
** Description      : Enters Module exclusive area                            **
**                                                                            **
** Service ID       : NA                                                      **
**                                                                            **
** Sync/Async       : Synchronous                                             **
**                                                                            **
** Reentrancy       : Not Reentrant                                           **
**                                                                            **
** Parameters(in)   : None                                                    **
** Parameters (out) : None                                                    **
**                                                                            **
** Return value     : None                                                    **
**                                                                            **
*******************************************************************************/
extern void SchM_Enter_McalLib_StmTimerResolution(void);
/*******************************************************************************
** Traceability     :                                                         **
**                                                                            **
** Syntax           : void SchM_Exit_McalLib_StmTimerResolution(void)         **
**                                                                            **
** Description      : Exit Module exclusive area                              **
**                                                                            **
** Service ID       : NA                                                      **
**                                                                            **
** Sync/Async       : Synchronous                                             **
**                                                                            **
** Reentrancy       : Not Reentrant                                           **
**                                                                            **
** Parameters(in)   : None                                                    **
** Parameters (out) : None                                                    **
**                                                                            **
** Return value     : None                                                    **
**                                                                            **
*******************************************************************************/
extern void SchM_Exit_McalLib_StmTimerResolution(void);

#endif
