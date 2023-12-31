/* CHECK: RULE 502 OFF */
/* CHECK: RULE 203 OFF */
/* CHECK: RULE 506 OFF */
/* CHECK: RULE 205 OFF */
/* CHECK: RULE 306 OFF */
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
**  FILENAME     : FlsLoader_Local.h                                          **
**                                                                            **
**  VERSION      : 2.0.0                                                      **
**                                                                            **
**  DATE         : 2017-04-05                                                 **
**                                                                            **
**  VARIANT      : Variant PC                                                 **
**                                                                            **
**  PLATFORM     : Infineon AURIX2G                                           **
**                                                                            **
**  AUTHOR       : DL-AUTOSAR-Engineering                                     **
**                                                                            **
**  VENDOR       : Infineon Technologies                                      **
**                                                                            **
**  DESCRIPTION  : Flsloader Driver local header definition file              **
**                                                                            **
**  SPECIFICATION(S) : NA                                                     **
**                                                                            **
**  MAY BE CHANGED BY USER : no                                               **
**                                                                            **
*******************************************************************************/

#ifndef FLSLOADER_LOCAL_H
#define FLSLOADER_LOCAL_H

/*******************************************************************************
**                      Includes                                              **
*******************************************************************************/
#include "FlsLoader.h"

/* Inclusion of Flash header file */
#include "IfxCpu_reg.h"
#include "IfxDmu_reg.h"
#include "IfxPmu_reg.h"
#include "IfxScu_reg.h"

/* Conditional Inclusion of Developement Error Tracer File */
#if  ( FLSLOADER_DEV_ERROR_DETECT == STD_ON )
#include "Det.h"
#endif
/*******************************************************************************
**                      Global Macro Definitions                             **
*******************************************************************************/
/* Sector Nos */
#define FLSLOADER_S0      ((uint32)(0U))
#define FLSLOADER_S1      ((uint32)(1U))
#define FLSLOADER_S2      ((uint32)(2U))
#define FLSLOADER_S3      ((uint32)(3U))
#define FLSLOADER_S4      ((uint32)(4U))
#define FLSLOADER_S5      ((uint32)(5U))
#define FLSLOADER_S6      ((uint32)(6U))
#define FLSLOADER_S7      ((uint32)(7U))
#define FLSLOADER_S8      ((uint32)(8U))
#define FLSLOADER_S9      ((uint32)(9U))
#define FLSLOADER_S10     ((uint32)(10U))
#define FLSLOADER_S11     ((uint32)(11U))
#define FLSLOADER_S12     ((uint32)(12U))
#define FLSLOADER_S13     ((uint32)(13U))
#define FLSLOADER_S14     ((uint32)(14U))
#define FLSLOADER_S15     ((uint32)(15U))
#define FLSLOADER_S16     ((uint32)(16U))
#define FLSLOADER_S17     ((uint32)(17U))
#define FLSLOADER_S18     ((uint32)(18U))
#define FLSLOADER_S19     ((uint32)(19U))
#define FLSLOADER_S20     ((uint32)(20U))
#define FLSLOADER_S21     ((uint32)(21U))
#define FLSLOADER_S22     ((uint32)(22U))
#define FLSLOADER_S23     ((uint32)(23U))
#define FLSLOADER_S24     ((uint32)(24U))
#define FLSLOADER_S25     ((uint32)(25U))
#define FLSLOADER_S26     ((uint32)(26U))
#define FLSLOADER_INV     ((uint32)(0xFFFFU))
#define FLSLOADER_TRUE    ((uint32)(0x1U))
#define FLSLOADER_FALSE   ((uint32)(0x0U))

#define FLSBANK0             ((uint8)(0x00))
#define FLSBANK1             ((uint8)(0x01))
#define FLSBANK2             ((uint8)(0x02))
#define FLSBANK3             ((uint8)(0x03))
#define FLSBANK4             ((uint8)(0x04))
#define FLSBANK5             ((uint8)(0x05))

#define FLSLOADER_MOD_256               ((uint32)(0x000000FFU))
#define FLSLOADER_MOD_32                ((uint32)(0x0000001FU))
#define FLSLOADER_PFLASH_MASK           ((uint32)(0x0000000FU))
/* Confirmation code is 0x57B5327F */
#define FLSLOADER_CONFIRMATION_CODE     ((uint32)(0x57B5327FU))
#define FLSLOADER_CONFIRMATION_CODE_B0  (0x34U)
#define FLSLOADER_CONFIRMATION_CODE_B1  (0x12U)
#define FLSLOADER_CONFIRMATION_CODE_B2  (0x21U)
#define FLSLOADER_CONFIRMATION_CODE_B3  (0x43U)

/* The following macros are used in the command cycles. */
#define FLSLOADER_CYCLE_5554           ((FlsLoader_AddressType)(0x00005554U))
#define FLSLOADER_CYCLE_55F0           ((FlsLoader_AddressType)(0x000055F0U))
#define FLSLOADER_CYCLE_AA50           ((FlsLoader_AddressType)(0x0000AA50U))
#define FLSLOADER_CYCLE_AA58           ((FlsLoader_AddressType)(0x0000AA58U))
#define FLSLOADER_CYCLE_AAA8           ((FlsLoader_AddressType)(0x0000AAA8U))
#define FLSLOADER_CYCLE_553C           ((FlsLoader_AddressType)(0x0000553CU))
#define FLSLOADER_MASK_HIGHER4_NIBBLES ((FlsLoader_AddressType)(0xFFFF0000U))
#define FLSLOADER_POSITION_0           ((FlsLoader_AddressType)0U)

/* The following values are used in the command cycles */
#define FLSLOADER_VALUE_F0             ((FlsLoader_AddressType)(0x000000F0U))
#define FLSLOADER_VALUE_00             ((FlsLoader_AddressType)(0x00000000U))
#define FLSLOADER_VALUE_A0             ((FlsLoader_AddressType)(0x000000A0U))
#define FLSLOADER_VALUE_AA             ((FlsLoader_AddressType)(0x000000AAU))
#define FLSLOADER_VALUE_A6             ((FlsLoader_AddressType)(0x000000A6U))
#define FLSLOADER_VALUE_80             ((FlsLoader_AddressType)(0x00000080U))
#define FLSLOADER_VALUE_50             ((FlsLoader_AddressType)(0x00000050U))
#define FLSLOADER_VALUE_FA             ((FlsLoader_AddressType)(0x000000FAU))

/* Command Cycle information*/
/* MISRA2012_RULE_4_9_JUSTIFICATION: Function like macro used for code
 * simplification and readability*/
#define FLSLOADER_GET_CYCLE_5554(Address) \
           (((Address) & FLSLOADER_MASK_HIGHER4_NIBBLES) + FLSLOADER_CYCLE_5554)
/* MISRA2012_RULE_4_9_JUSTIFICATION: Function like macro used for code
 * simplification and readability*/
#define FLSLOADER_GET_CYCLE_AA50(Address) \
           (((Address) & FLSLOADER_MASK_HIGHER4_NIBBLES) + FLSLOADER_CYCLE_AA50)
/* MISRA2012_RULE_4_9_JUSTIFICATION: Function like macro used for code
 * simplification and readability*/
#define FLSLOADER_GET_CYCLE_AA58(Address) \
           (((Address) & FLSLOADER_MASK_HIGHER4_NIBBLES) + FLSLOADER_CYCLE_AA58)
/* MISRA2012_RULE_4_9_JUSTIFICATION: Function like macro used for code
 * simplification and readability*/
#define FLSLOADER_GET_CYCLE_AAA8(Address) \
           (((Address) & FLSLOADER_MASK_HIGHER4_NIBBLES) + FLSLOADER_CYCLE_AAA8)
/* MISRA2012_RULE_4_9_JUSTIFICATION: Function like macro used for code
 * simplification and readability*/
#define FLSLOADER_GET_CYCLE_55F0(Address) \
           (((Address) & FLSLOADER_MASK_HIGHER4_NIBBLES) + FLSLOADER_CYCLE_55F0)
/* MISRA2012_RULE_4_9_JUSTIFICATION: Function like macro used for code
 * simplification and readability*/
#define FLSLOADER_GET_CYCLE_553C(Address) \
           (((Address) & FLSLOADER_MASK_HIGHER4_NIBBLES) + FLSLOADER_CYCLE_553C)

#define FLSLOADER_NUM_2                 (2U)
#define FLSLOADER_PFLASH5_MASK          (0X0FU)
#define FLSLOADER_PFLASH4_MASK          (0X0CU)
#define FLSLOADER_PFLASH3_MASK          (0X09U)
#define FLSLOADER_PFLASH2_MASK          (0X06U)
#define FLSLOADER_PFLASH1_MASK          (0X03U)
#define FLSLOADER_UCB_DF0_MASK          (0X04U)
#define FLSLOADER_DFLASH0_BUSY          (1U)
#define FLSLOADER_CMDCYCLE_TIMEOUT      (0x000FFFFFU)
/*#define FLSLOADER_CMDCYCLE_TIMEOUT      (0x2U)*/
#define FLSLOADER_BUSY_TIMEOUT          (0x00FFFFFFU)
/*#define FLSLOADER_BUSY_TIMEOUT          (0x2U)*/
#define FLSLOADER_BIT_SET               (1U)
#define FLSLOADER_PFLASH_BANK0          ((uint32)(0x00000000U))
#define FLSLOADER_PFLASH_BANK1          ((uint32)(0x00000001U))
#define FLSLOADER_PFLASH_BANK2          ((uint32)(0x00000002U))
#define FLSLOADER_PFLASH_BANK3          ((uint32)(0x00000003U))
#define FLSLOADER_PFLASH_BANK4          ((uint32)(0x00000004U))
#define FLSLOADER_PFLASH_BANK5          ((uint32)(0x00000005U))

#define FLSLOADER_DFLASH_BANK0          ((uint32)(0x00000010U))
#define FLSLOADER_UCB_DFLASH_BANK0      ((uint32)(0x00000020U))

#define FLSLOADER_SHIFT_BY_20           ((uint32)(20U))
#define FLSLOADER_SHIFT_BY_15           (15U)
#define FLSLOADER_SHIFT_BY_8            (8U)
#define FLSLOADER_SHIFT_BY_5            ((uint32)(5U))
#define FLSLOADER_SHIFT_BY_3            (3U)

#define FLSLOADER_DECREMENT_BY_32       ((uint32)(32U))
#define FLSLOADER_REG_FIRST_BIT         ((uint32)(0U))
#define FLSLOADER_REG_32_BIT            ((uint32)(32U))

#define FLSLOADER_UCB_FLASH_CONFIRMED  ((uint32)2U)
#define FLSLOADER_UCB_FLASH_ERRORED    ((uint32)3U)

/* Protection,sequence and operation errors */
#define FLSLOADER_PROER_SQER_OPER_ERROR (0x00000007U)
#define FLSLOADER_OPER_ERROR            (0x00000001U)
#define FLSLOADER_SQER_ERROR            (0x00000002U)
#define FLSLOADER_PROER_ERROR           (0x00000004U)
#define FLSLOADER_INITIALIZED           (1U)
#define FLSLOADER_NUM_4                 (4U)
#define FLSLOADER_NUM_6                 (6U)

/*******************************************************************************
**                      Global function like Macros                          **
*******************************************************************************/
/*
Function Like Macro:FlsLoader_lCheckFlashType
macro to get wheter its PFLASH or DFLASH
Input Parameters:
Address: Address of the flash
*/
/* MISRA2012_RULE_4_9_JUSTIFICATION: Function like macro used for code
 * simplification and readability*/
#define FlsLoader_lCheckFlashType(Address) \
          ((0xAFU ==(((Address) >> 24U) & 0xFFU)) ? 1U : 0U )

/*
Function Like Macro:FlsLoader_lEnterPageMode
Enters the Page Mode
Input Parameters: Address
*/
/* MISRA2012_RULE_4_9_JUSTIFICATION: Function like macro used for code
 * simplification and readability*/
#define FlsLoader_lEnterPageMode(Address)    \
          (((Address) & FLSLOADER_MASK_HIGHER4_NIBBLES) + FLSLOADER_CYCLE_5554)
/*
Function Like Macro:FlsLoader_lClearStatus
Clears the status register
Input Parameters: Address
*/
/* MISRA2012_RULE_4_9_JUSTIFICATION: Function like macro used for code
 * simplification and readability*/
#define FlsLoader_lClearStatus(Address)    \
          (((Address) & FLSLOADER_MASK_HIGHER4_NIBBLES) + FLSLOADER_CYCLE_5554)
/*
Function Like Macro:FlsLoader_lLoadPage
Loads the page in Write API
Input Parameters: Address
*/
/* MISRA2012_RULE_4_9_JUSTIFICATION: Function like macro used for code
 * simplification and readability*/
#define FlsLoader_lLoadPage(Address)   \
          (((Address) & FLSLOADER_MASK_HIGHER4_NIBBLES) + FLSLOADER_CYCLE_55F0)
/*
Function Like Macro:FlsLoader_lResetRead
Resets to Read
Input Parameters: Address
*/
/* MISRA2012_RULE_4_9_JUSTIFICATION: Function like macro used for code
 * simplification and readability*/
#define FlsLoader_lResetRead(Address)   \
          (((Address) & FLSLOADER_MASK_HIGHER4_NIBBLES) + FLSLOADER_CYCLE_5554)

/*******************************************************************************
**                      Global Variable Definitions                          **
*******************************************************************************/
#if (FLSLOADER_DEV_ERROR_DETECT == STD_ON)
#define FLSLOADER_START_SEC_VAR_8BIT
/* MISRA2012_RULE_4_10_JUSTIFICATION: Flsloader_Memmap.h is repeatedly included
 * without include guard. This is as per AUTOSAR */
#include "MemMap.h"

extern uint8 FlsLoader_InitStatus;

#define FLSLOADER_STOP_SEC_VAR_8BIT
/* MISRA2012_RULE_4_10_JUSTIFICATION: Flsloader_Memmap.h is repeatedly included
 * without include guard. This is as per AUTOSAR */
#include "MemMap.h"
#endif

/*******************************************************************************
**                      Private Function Declarations                         **
*******************************************************************************/
#define FLSLOADER_START_SEC_WRITE_CODE
/* MISRA2012_RULE_4_10_JUSTIFICATION: Flsloader_Memmap.h is repeatedly included
 * without include guard. This is as per AUTOSAR */
#include "MemMap.h"


/*******************************************************************************
**                      Global Inline Function Declarations                   **
*******************************************************************************/
#if (FLSLOADER_LOCK_UNLOCK_API == STD_ON)
extern FlsLoader_ReturnType FlsLoader_lLock(void);
#endif

extern FlsLoader_ReturnType FlsLoader_lCheckOTPWOP(void);

#define FLSLOADER_STOP_SEC_WRITE_CODE
/* MISRA2012_RULE_4_10_JUSTIFICATION: Flsloader_Memmap.h is repeatedly included
 * without include guard. This is as per AUTOSAR */
#include "MemMap.h"

#define FLSLOADER_START_SEC_WRITE_CODE
/* MISRA2012_RULE_4_10_JUSTIFICATION: Flsloader_Memmap.h is repeatedly included
 * without include guard. This is as per AUTOSAR */
#include "MemMap.h"

#if (FLSLOADER_DEV_ERROR_DETECT == STD_ON)
extern FlsLoader_ReturnType FlsLoader_lWriteDetCheck(
                                            FlsLoader_LengthType Length,\
                                        FlsLoader_AddressType TargetAddress);
                                        
extern FlsLoader_ReturnType FlsLoader_lEraseDetCheck(
                                     FlsLoader_LengthType NumberOfSectors,\
                                     FlsLoader_AddressType TargetAddress);

#endif

extern uint32 FlsLoader_lGetFlashType(
                      FlsLoader_AddressType TargetAddress);

extern uint32 FlsLoader_lDisableInts(void);

extern void FlsLoader_lEnableInts(uint32 Icr);

extern FlsLoader_ReturnType FlsLoader_lProtSeqOperErrorCheck(void);

#if (FLSLOADER_ENABLE_LOCKCHECK == STD_ON)
extern FlsLoader_ReturnType FlsLoader_lFlashLockCheck (
                        FlsLoader_AddressType TargetAddress,uint32 FlashType,
                        FlsLoader_LengthType Length);
extern FlsLoader_ReturnType FlsLoader_lEraseLockCheck (
                        FlsLoader_AddressType TargetAddress,uint32 FlashType,
                        FlsLoader_LengthType Length);
#endif

#if (FLSLOADER_CALLOUT_FUNC == STD_ON)
/*******************************************************************************
** Syntax           :  void  FlsLoader_lCalloutFunction(uint32 Timeout)       **
**                                                                            **
** Service ID       : None                                                    **
**                                                                            **
** Sync/Async       : Synchronous                                             **
**                                                                            **
** Reentrancy       : non - reentrant                                         **
**                                                                            **
** Parameters(in)   : Timeout : Timeout value                                 **
**                                                                            **
** Parameters (out) : None                                                    **
**                                                                            **
** Return value     : NA                                                      **
**                                                                            **
** Description      : This function calls the FlsLoader Call-Out function     **
**                    at every  0xFFFF loop count                             **
*******************************************************************************/
LOCAL_INLINE void FlsLoader_lCalloutFunction(uint32 Timeout)
{
  if((Timeout & 0xFFFFU) == 0x0000U)
  {
    FlsLoader_LoopCallOut();
  }
}
#endif /*(FLSLOADER_CALLOUT_FUNC == STD_ON)*/

#define FLSLOADER_STOP_SEC_WRITE_CODE
/* MISRA2012_RULE_4_10_JUSTIFICATION: Flsloader_Memmap.h is repeatedly included
 * without include guard. This is as per AUTOSAR */
#include "MemMap.h"
#endif /* End of FLSLOADER_LOCAL_H */
/* CHECK: RULE 502 ON */
/* CHECK: RULE 203 ON */
/* CHECK: RULE 506 ON */
/* CHECK: RULE 205 ON */
/* CHECK: RULE 306 ON */
