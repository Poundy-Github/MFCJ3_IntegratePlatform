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
**  FILENAME  : Mcu_17_TimerIp_Cfg.h                                          **
**                                                                            **
**  VERSION   : 11.0.0                                                        **
**                                                                            **
**  DATE, TIME: 2022-02-07, 08:43:23       !!!IGNORE-LINE!!!                  **
**                                                                            **
**  GENERATOR : Build b191017-0938           !!!IGNORE-LINE!!!                **
**                                                                            **
**  BSW MODULE DECRIPTION : Mcu.bmd                                           **
**                                                                            **
**  VARIANT   : Variant PB                                                    **
**                                                                            **
**  PLATFORM  : Infineon AURIX2G                                              **
**                                                                            **
**  AUTHOR    : DL-AUTOSAR-Engineering                                        **
**                                                                            **
**  VENDOR    : Infineon Technologies                                         **
**                                                                            **
**  DESCRIPTION  : Timer IPs configuration file generated by Mcu module       **
**                                                                            **
**  SPECIFICATION(S) : NA                                                     **
**                                                                            **
**  MAY BE CHANGED BY USER : no                                               **
**                                                                            **
*******************************************************************************/


#ifndef MCU_17_TIMERIP_CFG_H
#define MCU_17_TIMERIP_CFG_H

/*******************************************************************************
**                      Includes                                              **
*******************************************************************************/
#include "Std_Types.h"
#include "Mcu_Cfg.h"

/*******************************************************************************
**                      Global Macro Definitions                              **
*******************************************************************************/

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
**                      Global Function Declarations                          **
*******************************************************************************/

#define MCU_17_GTM_NO_OF_TIM_MODULES              (0x7U)
#define MCU_17_GTM_NO_OF_TIM_CHANNELS             (0x8U)

#define MCU_17_GTM_NO_OF_TOM_MODULES              (0x5U)
#define MCU_17_GTM_NO_OF_TOM_CHANNELS             (0x10U)
#define MCU_17_GTM_NO_OF_TOM_TGC                  (0x2U)

#define MCU_17_GTM_NO_OF_ATOM_MODULES             (0x9U)
#define MCU_17_GTM_NO_OF_ATOM_CHANNELS            (0x8U)
#define MCU_17_GTM_NO_OF_ATOM_AGC                 (0x1U)
#define MCU_17_CCU6_NO_OF_KERNELS                 (0x2U)
#define MCU_17_CCU6_NO_OF_COMPARATORS             (0x4U)
#define MCU_17_GPT12_NO_OF_TIMERS                 (0x5U)
#define MCU_17_ERU_NO_OF_OGU                      (0x8U)
#define MCU_17_STM_NO_OF_TIMERS                   (0x4U)

#define MCU_17_TIMERIP_ADC_USER       (STD_OFF)
#define MCU_17_TIMERIP_WDG_USER       (STD_OFF)
#define MCU_17_TIMERIP_PWM_USER       (STD_OFF)
#define MCU_17_TIMERIP_GPT_USER       (STD_OFF)
#define MCU_17_TIMERIP_OCU_USER       (STD_OFF)
#define MCU_17_TIMERIP_ICU_USER       (STD_OFF)
#define MCU_17_TIMERIP_DSADC_USER     (STD_OFF)
#define MCU_17_TIMERIP_STM_USER       (STD_OFF)

#endif /* end of MCU_17_TIMERIP_CFG_H */
