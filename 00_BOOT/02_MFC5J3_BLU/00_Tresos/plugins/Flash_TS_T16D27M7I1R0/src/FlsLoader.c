/* CHECK: RULE 203 OFF */
/* CHECK: RULE 404 OFF */
/* CHECK: RULE 205 OFF */
/* CHECK: RULE 506 OFF */
/* CHECK: RULE 306 OFF */
/* CHECK: NOPARSE (Infineon implementation code */
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
**  FILENAME     : FlsLoader.c                                                **
**                                                                            **
**  VERSION      : 3.0.0                                                      **
**                                                                            **
**  DATE         : 2017-04-07                                                 **
**                                                                            **
**  VARIANT      : Variant PC                                                 **
**                                                                            **
**  PLATFORM     : Infineon AURIX2G                                           **
**                                                                            **
**  AUTHOR       : DL-AUTOSAR-Engineering                                     **
**                                                                            **
**  VENDOR       : Infineon Technologies                                      **
**                                                                            **
**  DESCRIPTION  : Flsloader Driver source file                               **
**                                                                            **
**  SPECIFICATION(S) : NA                                                     **
**                                                                            **
**  MAY BE CHANGED BY USER : no                                               **
**                                                                            **
*******************************************************************************/
/* Global Misra Violation and Suppression */
/*  MISRA-C:2004 Deviation List
 *
 *  MISRA-1) Deviated Rule 11.3 (advisory)
 *   A cast should not be performed between a pointer type and an integral type.
 *
 *   Reason:
 *   "A cast is mandatory for memory access in FLASH_LLD_Read() API."
 *
 *  MISRA-2) Deviated Rule 10.1
 *   "Implicit conversion of the expression of underlying type 'unsigned char' to the
 *         type 'signed int' that is not a wider integer type of the same signedness."
 *
 *   Reason:
 *   extern golobal variables.
 *
 *  MISRA-3) Deviated Rule 13.2
 *   "Tests of a value against zero should be made explicit, unless the operand is effectively Boolean."
 *
 *   Reason:
 *   A cast is mandatory for memory access in FLASH_LLD_Read() API.
 *
 *  MISRA-4) Deviated Rule 17.4
 *   "Array indexing shall be the only allowed form of pointer arithmetic."
 *
 *   Reason:
 *   extern golobal variables.
 *
 *  MISRA-5) Deviated Rule 8.1
 *   "Function 'XXX' has no complete visible prototype at call."
 *
 *   Reason:
 *   A cast is mandatory for memory access in FLASH_LLD_Read() API.
 *
 *  MISRA-6) Deviated Rule 16.10
 *   "If a function returns error information, then that error information should be tested."
 *
 *   Reason:
 *   extern golobal variables.
 *
 *  MISRA-7) Deviated Rule 10.3
 *   "Complex expression of underlying type 'unsigned int' may only be cast to narrower integer
 *        type of same signedness, however the destination type is 'unsigned long'."
 *
 *   Reason:
 *   extern golobal variables.
 *
 *  MISRA-8) Deviated Rule 10.5
 *   "Bitwise ~ is applied to the operand of underlying type 'unsigned char', the result
 *     shall be immediatly cast to the underlying type."
 *
 *   Reason:
 *   A cast is mandatory for memory access in FLASH_LLD_Read() API.
 *
 *  MISRA-9) Deviated Rule 11.5
 *   "A cast shall not be performed that removes any const or volatile qualification from the type addressed by a pointer."
 *
 *   Reason:
 *   A cast is mandatory for memory access in FLASH_LLD_Read() API.
 *
 *  MISRA-10) Deviated Rule 12.2
 *   "The value of volatile 'TargetAddress' depends on the order of evaluation because of multiple accesses."
 *
 *   Reason:
 *   A cast is mandatory for memory access in FLASH_LLD_Read() API.
 *
 *  MISRA-11) Deviated Rule 14.2
 *  "All non-null statements shall either have at least one side effect however executed, or cause control flow to change"
 *
 *  Reason: 
 *    Needed
 */

 /* Deviation MISRA-1 MISRA-2 MISRA-3 MISRA-4 MISRA-5 MISRA-6 MISRA-7 MISRA-8 MISRA-9 MISRA-10 MISRA-11 <START> */
/*******************************************************************************
**                      Includes                                              **
*******************************************************************************/
/* Inclusion of Global Header File */
#include "IFX_Os.h"

  /* Inclusion of Flash header file */
#include "FlsLoader.h"

  /* Inclusion of Flash header file */
#include "FlsLoader_Local.h"
#include "EB_Prj.h"
#include "FLASH_RAM.h"


/*******************************************************************************
**                      Imported Compiler Switch Check                        **
*******************************************************************************/
#ifndef FLSLOADER_SW_MAJOR_VERSION
  #error "FLSLOADER_SW_MAJOR_VERSION is not defined. "
#endif

#ifndef FLSLOADER_SW_MINOR_VERSION
  #error "FLSLOADER_SW_MINOR_VERSION is not defined. "
#endif

#ifndef FLSLOADER_SW_PATCH_VERSION
  #error "FLSLOADER_SW_PATCH_VERSION is not defined. "
#endif

#if ( FLSLOADER_SW_MAJOR_VERSION != 1U )
  #error "FLSLOADER_SW_MAJOR_VERSION does not match. "
#endif

#if ( FLSLOADER_SW_MINOR_VERSION != 0U )
  #error "FLSLOADER_SW_MINOR_VERSION does not match. "
#endif

/*******************************************************************************
**                      Private Macro Definitions                             **
*******************************************************************************/
/*The following to macros are used to determine the status of Flash. */
#define FLSLOADER_NORMAL                (0U)

#if (FLSLOADER_SUSPEND_API == STD_ON)
#define FLSLOADER_SUSPEND               (1U)
#endif

#define FLSLOADER_UNINTIALIZED          (0U)

  /* Flash NULL */
#define FLSLOADER_NULL                  ((void *) 0)
#define FLSLOADER_ZERO_DATA             (0x00000000U)
#define FLSLOADER_NUM_5                 (5U)
#define FLSLOADER_NUM_32                (32U)
#define FLSLOADER_NUM_256               (256U)
#define FLSLOADER_NUM_8                 (8U)
#define FLSLOADER_UCB0                  (0U)
#define FLSLOADER_UCB1                  (1U)
#define FLSLOADER_PWD                   (8U)
#define FLSLOADER_NUM_3                 (3U)
  /* (17*8)bytes UCB <P/D>FLASH content */
#define FLSLOADER_FLASH_TRAP_DIS        (0xC0000000U)
#define FLSLOADER_FLASH_TRAP_EN         (0x3FFFFFFFU)

  /* Program Verify Error */
#define FLSLOADER_PVER_ERROR                  (0x00000008U)
  /* Erase Verify Error */
#define FLSLOADER_EVER_ERROR                  (0x00000010U)

  /* Flash command should point this Address */
#define FLSLOADER_CMD_BASE  ((FlsLoader_AddressType)(0xAF000000U))

#define FLSLOADER_WDT_PASSWORD_LOWER_MASK  ( 0x000000FCu )

  /* mask for password Bits 8-15 */
#define FLSLOADER_WDT_PASSWORD_UPPER_MASK  ( 0x0000FF00u )

  /* mask for password bits */
#define FLSLOADER_WDT_PASSWORD_MASK   \
                                    (FLSLOADER_WDT_PASSWORD_LOWER_MASK | \
                                     FLSLOADER_WDT_PASSWORD_UPPER_MASK)

#define FLSLOADER_WDT_RELOAD_MASK          ( 0xFFFF0000u )


  /* mask for LCK and ENDINIT status bits */
#define FLSLOADER_WDT_STATUS_MASK          ( 0x00000003u )


/*******************************************************************************
**                      Private function like Macros                          **
*******************************************************************************/

  /*
  Function Like Macro:FlsLoader_lGetMode
  macro to get the kind of flash
  Input Parameters: FlashType
  */
/* MISRA2012_RULE_4_9_JUSTIFICATION: Function like macro used for code
 * simplification and readability*/
#define FlsLoader_lGetMode(FlashType) (((FlashType)!=(FLSLOADER_DFLASH_BANK0)) \
                             ? (FLSLOADER_PFLASH_VAL) : (FLSLOADER_DFLASH_VAL))

/******************************************************************************
**                      Global Type Definitions                              **
******************************************************************************/

/******************************************************************************
**                      Private Type Definitions                             **
******************************************************************************/

/*******************************************************************************
**                      Private Constant Definitions                          **
*******************************************************************************/

/******************************************************************************
**                      Private Variable Definitions                         **
******************************************************************************/
#define FLSLOADER_START_SEC_VAR_8BIT
/* MISRA2012_RULE_4_10_JUSTIFICATION: Flsloader_Memmap.h is repeatedly included
 * without include guard. This is as per AUTOSAR */
#include "MemMap.h"
  static uint8 FlsLoader_Status;
#if (FLSLOADER_DEV_ERROR_DETECT == STD_ON)
  uint8  FlsLoader_InitStatus;
#endif
#define FLSLOADER_STOP_SEC_VAR_8BIT
/* MISRA2012_RULE_4_10_JUSTIFICATION: Flsloader_Memmap.h is repeatedly included
 * without include guard. This is as per AUTOSAR */
/* MISRA2012_RULE_20_1_JUSTIFICATION: declaration of 'FlsLoader_Status' before
 * #include memap.h - Accepted deviation in AUTOSAR */
#include "MemMap.h"

#define FLSLOADER_START_SEC_WRITE_CODE
/* MISRA2012_RULE_4_10_JUSTIFICATION: Flsloader_Memmap.h is repeatedly included
 * without include guard. This is as per AUTOSAR */
/* MISRA2012_RULE_20_1_JUSTIFICATION: declaration of 'FlsLoader_Status' before
 * #include memap.h - Accepted deviation in AUTOSAR */
#include "MemMap.h"
/*******************************************************************************
**                    Prototypes Of Local Functions                           **
*******************************************************************************/
  /* funtion to check program verification error */
LOCAL_INLINE FlsLoader_ReturnType FlsLoader_lPverCheck(void);

  /* funtion to check Erase verification error */
LOCAL_INLINE FlsLoader_ReturnType FlsLoader_lEverCheck(void);

LOCAL_INLINE void FlsLoader_lResetSafetyENDINIT(void);

LOCAL_INLINE void FlsLoader_lSetSafetyENDINIT(void);


LOCAL_INLINE FlsLoader_ReturnType FlsLoader_lBurstWrite (
                            uint32 BurstLoadPageCount,
                            FlsLoader_AddressType BurstOffSet,
                            uint32 FlashType,
                            const uint8 *SourceAddressPtr,
                            FlsLoader_AddressType TargetAddress,
                            uint32 NumberOfBursts);

LOCAL_INLINE FlsLoader_ReturnType FlsLoader_lPageWrite (
                           uint32 LoadPageCount,
                           FlsLoader_AddressType OffSet,
                           uint32 FlashType,
                           const uint8 *SourceAddressPtr,
                           FlsLoader_AddressType TargetAddress,
                           uint32 NoOfPages);

#define FLSLOADER_STOP_SEC_WRITE_CODE
/* MISRA2012_RULE_4_10_JUSTIFICATION: Flsloader_Memmap.h is repeatedly included
* without include guard. This is as per AUTOSAR */
/* MISRA2012_RULE_20_1_JUSTIFICATION: declaration of 'FlsLoader_Status' before
 * #include memap.h - Accepted deviation in AUTOSAR */
#include "MemMap.h"
/*******************************************************************************
**                      Global Constant Definitions                           **
*******************************************************************************/

/*******************************************************************************
**                      Global Variable Definitions                           **
*******************************************************************************/

/*******************************************************************************
**                      Global Function Definitions                           **
*******************************************************************************/
  /* Mapping the code */
#define FLSLOADER_START_SEC_CODE
/* MISRA2012_RULE_4_10_JUSTIFICATION: Flsloader_Memmap.h is repeatedly included
 * without include guard. This is as per AUTOSAR */
/* MISRA2012_RULE_20_1_JUSTIFICATION: declaration of 'FlsLoader_Status' before
 * #include memap.h - Accepted deviation in AUTOSAR */
#include "MemMap.h"

/*******************************************************************************
** Syntax           :  FlsLoader_ReturnType FlsLoader_Init(                   **
**                      const FlsLoader_ConfigType* Address)                  **
**                                                                            **
** Service ID       : 0x00                                                    **
**                                                                            **
** Sync/Async       : Synchronous                                             **
**                                                                            **
** Reentrancy       : non - reentrant                                         **
**                                                                            **
** Parameters(in)   : Address :NULL Expected                                  **
**                                                                            **
** Parameters (out) : none                                                    **
**                                                                            **
** Return value     : FlsLoader_ReturnType:(If DET is not enabled)            **
**                    1.FLSLOADER_E_OK                                        **
**                    2.FLSLOADER_E_ROMVERSION                                **
**                    (If DET is enabled and an error has occurred)           **
**                    1.FLSLOADER_E_NOT_OK                                    **
**                                                                            **
** Description      : This function initilizes the flash module and checks    **
**                    if all the flash sectors is configured as ROM           **
**                                                                            **
*******************************************************************************/
/*
CD_FlsLoader028: This is the initialization function for FlsLoader.
*/
FlsLoader_ReturnType FlsLoader_Init(const FlsLoader_ConfigType* Address)
{
  FlsLoader_ReturnType  RetError;
  #if (FLSLOADER_DEV_ERROR_DETECT == STD_OFF)
  UNUSED_PARAMETER(Address);
  #endif

  /* Init RetError to OK */
  #if (FLSLOADER_DEV_ERROR_DETECT == STD_ON)
  RetError = FLSLOADER_E_OK;

  if ( Address != FLSLOADER_NULL )
  {
    /* Report FLSLOADER_E_PARAM_IGNORED DET */
    Det_ReportError(
                    FLSLOADER_MODULE_ID,
                    FLSLOADER_INSTANCE_ID,
                    FLSLOADER_SID_INIT,
                    FLSLOADER_E_PARAM_IGNORED);

    RetError = FLSLOADER_E_NOT_OK;
  }

  if (RetError != FLSLOADER_E_NOT_OK)
  #endif /*FLSLOADER_DEV_ERROR_DETECT */
  {
    RetError = FlsLoader_lCheckOTPWOP();
    /*FLASH_FCON register will be initialized in the start up. */
    FlsLoader_Status = FLSLOADER_NORMAL;
    #if (FLSLOADER_DEV_ERROR_DETECT == STD_ON)
    FlsLoader_InitStatus = FLSLOADER_INITIALIZED;
    #endif /*FLSLOADER_DEV_ERROR_DETECT*/

    Mcal_ResetCpuEndInitProtection();
    /* Disable traps on Uncorrectable errors */
    /* MISRA2012_RULE_11_4_JUSTIFICATION: SFR access */
    DMU_HF_ECCC.U |= FLSLOADER_FLASH_TRAP_DIS;
    /* Set End Init Protection */
    Mcal_SetCpuEndInitProtection();
  }

  return RetError;
}  /*End of Fls_Loader_Init */

/*Preprocessor switch to enable/disable the API to deinitialze
FlsLoader. */
#if (FLSLOADER_DEINIT_API == STD_ON)
/*******************************************************************************
** Syntax           :  FlsLoader_ReturnType FlsLoader_DeInit(void)            **
**                                                                            **
** Service ID       : 0x01                                                    **
**                                                                            **
** Sync/Async       : Synchronous                                             **
**                                                                            **
** Reentrancy       : non - reentrant                                         **
**                                                                            **
** Parameters(in)   : void                                                    **
**                                                                            **
** Parameters (out) : none                                                    **
**                                                                            **
** Return value     : FlsLoader_ReturnType:(If DET is not enabled)            **
**                    1. FLSLOADER_E_OK                                       **
**                    2. FLSLOADER_E_BUSY                                     **
**                    (If DET is enabled and an error has occurred)           **
**                    1. FLSLOADER_E_NOT_OK                                   **
**                    2. FLSLOADER_E_BUSY                                     **
**                                                                            **
** Description      : This function deinitilizes the flash module.            **
**                    This Function sets the registers to their default       **
**                    state and executes the reset to read command.           **
**                                                                            **
*******************************************************************************/
  /*
  CD_FlsLoader030: Service for FlsLaderDeInitialization
  */
FlsLoader_ReturnType FlsLoader_DeInit(void)
{
  FlsLoader_ReturnType  RetError;
  uint32 Fls0FsrCheck;
  /* Init RetError to OK */
  RetError = FLSLOADER_E_OK;

  #if (FLSLOADER_DEV_ERROR_DETECT == STD_ON)
  if (FlsLoader_InitStatus != FLSLOADER_INITIALIZED)
  {
  /* FlsLoader not initialized,Report to DET*/
    Det_ReportError ( FLSLOADER_MODULE_ID,
                      FLSLOADER_INSTANCE_ID,
                      FLSLOADER_SID_DEINIT,
                      FLSLOADER_E_UNINIT);
    RetError = FLSLOADER_E_NOT_OK;
  }

  if (RetError != FLSLOADER_E_NOT_OK )
  #endif /* FLSLOADER_DEV_ERROR_DETECT */
  {
    /* Check for Flash Busy*/
    /* MISRA2012_RULE_11_4_JUSTIFICATION: SFR access */
    Fls0FsrCheck = (DMU_HF_STATUS.U & (uint32)(FLSLOADER_FLASH_BUSY_MASK));

    if (Fls0FsrCheck != FLSLOADER_FALSE)
    {
      /* Report FLSLOADER_E_BUSY DET */
      RetError = FLSLOADER_E_BUSY;
      #if (FLSLOADER_DEV_ERROR_DETECT == STD_ON)

      Det_ReportError( FLSLOADER_MODULE_ID,
                       FLSLOADER_INSTANCE_ID,
                       FLSLOADER_SID_DEINIT,
                       (uint8)FLSLOADER_E_BUSY);
      #endif /* FLSLOADER_DEV_ERROR_DETECT */
    }
    else
    {
      FlsLoader_Status = FLSLOADER_NORMAL;
      #if (FLSLOADER_DEV_ERROR_DETECT == STD_ON)
      FlsLoader_InitStatus = FLSLOADER_UNINTIALIZED;
      #endif /* FLSLOADER_DEV_ERROR_DETECT */
      /* Reset to Read PFLASH, DFLASH (both banks) */
      /*MISRA2012_RULE_11_6_JUSTIFICATION: FlsLoader_AddressType is defined of
      type volatile uint32 to avoid compiler optimization in command cycles*/
      /*MISRA2012_RULE_11_2_JUSTIFICATION: The Pointers are type-cast to uint32
      for address comparison/calculation purpose.*/
      /*MISRA2012_RULE_13_2_JUSTIFICATION: The Pointers are type-cast to uint32
       *for address comparison/calculation purpose*/
      /*MISRA2012_RULE_1_3_JUSTIFICATION: The Pointers are type-cast to uint32
       *for address comparison/calculation purpose*/
      /* MISRA2012_RULE_11_4_JUSTIFICATION: SFR access */
      *((FlsLoader_AddressType*)FlsLoader_lResetRead(\
          FLSLOADER_DFLASH0_START_ADDRESS)) = FLSLOADER_VALUE_F0;
    }
    /* Reset EndInit protection */
    Mcal_ResetCpuEndInitProtection();
    /* Enable traps on Uncorrectable errors */
    /* MISRA2012_RULE_11_4_JUSTIFICATION: SFR access */
    DMU_HF_ECCC.U &= FLSLOADER_FLASH_TRAP_EN;
    /* Set EndInit protection */
    Mcal_SetCpuEndInitProtection();
  }
  return RetError;
}  /*End of function FlsLoader_DeInit */
#endif  /*(FLSLOADER_DEINIT_API == STD_ON) */

#define FLSLOADER_STOP_SEC_CODE
/* MISRA2012_RULE_4_10_JUSTIFICATION: Flsloader_Memmap.h is repeatedly included
 * without include guard. This is as per AUTOSAR */
/* MISRA2012_RULE_20_1_JUSTIFICATION: declaration of 'FlsLoader_Status' before
 * #include memap.h - Accepted deviation in AUTOSAR */
#include "MemMap.h"

#define FLSLOADER_START_SEC_WRITE_CODE
/* MISRA2012_RULE_4_10_JUSTIFICATION: Flsloader_Memmap.h is repeatedly included
 * without include guard. This is as per AUTOSAR */
/* MISRA2012_RULE_20_1_JUSTIFICATION: declaration of 'FlsLoader_Status' before
 * #include memap.h - Accepted deviation in AUTOSAR */
#include "MemMap.h"
/*******************************************************************************
** Syntax           :  FlsLoader_ReturnType FlsLoader_Write(                  **
**                      FlsLoader_AddressType TargetAddress,                  **
**                      FlsLoader_LengthType Length,                          **
**                      const uint8 *SourceAddressPtr                         **
**                    )                                                       **
**                                                                            **
** Service ID       : 0x02                                                    **
**                                                                            **
** Sync/Async       : Synchronous                                             **
**                                                                            **
** Reentrancy       : non - reentrant                                         **
**                                                                            **
** Parameters(in)   : Address:Source data Address                             **
**                    Length :Length of the data in bytes                     **
**                    - multiple of 256 bytes(8 pages)for PFLASH              **
**                    - multiple of 32 bytes (4 pages)for DFLASH              **
**                    TargetAddress :Destination Address in Flash             **
**                                                                            **
** Parameters (out) : none                                                    **
**                                                                            **
** Return value     : FlsLoader_ReturnType                                    **
**                    1.FLSLOADER_E_OK                                        **
**                    2.FLSLOADER_E_BUSY                                      **
**                    3.FLSLOADER_E_NOT_OK                                    **
**                    4.FLSLOADER_E_LOCKED                                    **
**                                                                            **
**                    1.FLSLOADER_E_NOT_OK for all errors                     **
**                                                                            **
** Description      : This function is used to program a page of internal     **
**                    flash using Burst mode of programming                   **
**                    This function does not check whether the TargetAddress  **
**                    crosses the boundry from one sector to another          **
*******************************************************************************/
FlsLoader_ReturnType FlsLoader_Write(FlsLoader_AddressType TargetAddress,
                                     FlsLoader_LengthType Length,
                                     const uint8 *SourceAddressPtr)
{
  FlsLoader_ReturnType  RetError;
  FlsLoader_AddressType OffSet;
  FlsLoader_AddressType BurstOffSet;
  uint32                FlashType;
  uint32                NumberOfBursts;
  uint32                FlsFsrCheck;
  uint32                Icr;
  uint32                BytesToWrite;
  uint32                NoOfPages;
  uint32                LoadPageCount;
  uint32                BurstLoadPageCount;

  /*Block 1: DET Check */
  #if (FLSLOADER_DEV_ERROR_DETECT == STD_ON)
  RetError = FlsLoader_lWriteDetCheck(Length,TargetAddress);


  if (RetError != FLSLOADER_E_NOT_OK)
  #endif /*FLSLOADER_E_NOT_OK*/
  {
    /*Check for Busy state of FLASH
    Registers differ between Checking of Busy state of PFlash and DFlash */
    /* MISRA2012_RULE_11_4_JUSTIFICATION: SFR access */
    FlsFsrCheck = (DMU_HF_STATUS.U & ((uint32)FLSLOADER_FLASH_BUSY_MASK));

    if ( FlsFsrCheck != FLSLOADER_FALSE)
    {
      /* Report FLSLOADER_E_BUSY DET */
      #if (FLSLOADER_DEV_ERROR_DETECT == STD_ON)
      Det_ReportError(FLSLOADER_MODULE_ID,
                      FLSLOADER_INSTANCE_ID,
                      FLSLOADER_SID_WRITE,
                      (uint8)FLSLOADER_E_BUSY);
      #endif /*FLSLOADER_DEV_ERROR_DETECT*/
      RetError = FLSLOADER_E_BUSY;
    }
    else if ( SourceAddressPtr == FLSLOADER_NULL)
    {
      #if (FLSLOADER_DEV_ERROR_DETECT == STD_ON)
      Det_ReportError(FLSLOADER_MODULE_ID,
                      FLSLOADER_INSTANCE_ID,
                      FLSLOADER_SID_WRITE,
                      (uint8)FLSLOADER_E_NOT_OK);
      #endif /*FLSLOADER_DEV_ERROR_DETECT*/
      RetError = FLSLOADER_E_NOT_OK;
    }
    else
    {
      /*PFLASH0*/
      /* Block 2: check the Flash Type DFLASH/PFLASH .
      If the Flash type is PFLASH check PMU0. */
      FlashType = FlsLoader_lGetFlashType (TargetAddress);
      /* Protection Installation check  */
      /* Preprocessor switch to enable/disable the lockcheck functionality */
      /*#if (FLSLOADER_ENABLE_LOCKCHECK == STD_ON)*/
      #if (FLSLOADER_ENABLE_LOCKCHECK == STD_ON)
      RetError = FlsLoader_lFlashLockCheck(TargetAddress,FlashType,Length);
      if (FLSLOADER_E_OK == RetError) /*FLSLOADER_ENABLE_LOCKCHECK*/
      #endif
      {
        /* Count the number of loops */
        if (FlashType != FLSLOADER_DFLASH_BANK0)
        {
          /* PFlash */
          if((TargetAddress & FLSLOADER_MOD_256) == 0x00U)
          {
            NumberOfBursts  = Length >> FLSLOADER_SHIFT_BY_8; /*Divide by 256*/
          }
          else
          {
            NumberOfBursts = 0;
          }
          LoadPageCount  = FLSLOADER_NUM_4;
          BurstLoadPageCount = FLSLOADER_NUM_32;
          OffSet       = (FlsLoader_AddressType)FLSLOADER_NUM_32;
          BurstOffSet  = (FlsLoader_AddressType)FLSLOADER_NUM_256;
          BytesToWrite = (Length - (NumberOfBursts * FLSLOADER_NUM_256));
          NoOfPages    = (BytesToWrite >> FLSLOADER_SHIFT_BY_5);
        }
        else
        {
          /* DFlash and UCB */
          if((TargetAddress & FLSLOADER_MOD_32) == 0x00U)
          {
            NumberOfBursts  = Length >> FLSLOADER_NUM_5; /*Divide by 32*/
          }
          else
          {
            NumberOfBursts = 0;
          }
          LoadPageCount      = 1U;
          BurstLoadPageCount = FLSLOADER_NUM_4;
          OffSet       = (FlsLoader_AddressType)FLSLOADER_NUM_8;
          BurstOffSet  = (FlsLoader_AddressType)FLSLOADER_NUM_32;
          BytesToWrite = (Length - (NumberOfBursts * FLSLOADER_NUM_32));
          NoOfPages    = (BytesToWrite >> FLSLOADER_SHIFT_BY_3);
        }

        /* Block 5: Execute the command sequence . */
        /*Initiating the state to normal*/
        FlsLoader_Status = FLSLOADER_NORMAL;
        /* Disable and restore interrupts for critical
        command cycles. As there are 2 critical command cycles,
        the entire write operation is protected. */
        /* copy the Address to local variable*/
        Icr = FlsLoader_lDisableInts();

        /*Write in Burst Mode*/
        RetError = FlsLoader_lBurstWrite (BurstLoadPageCount,BurstOffSet,
                                          FlashType,SourceAddressPtr,
                                          TargetAddress,NumberOfBursts);

        if ((RetError == FLSLOADER_E_OK) && (NoOfPages != 0U))
        {
          /* Write Remaining Pages */
          TargetAddress +=(NumberOfBursts *
                          (BurstLoadPageCount << FLSLOADER_NUM_3));
          /*MISRA2012_RULE_18_4_JUSTIFICATION: Pointer arithmetic is used to
          access user buffer efficiently*/
          SourceAddressPtr += (NumberOfBursts *\
                              (BurstLoadPageCount << FLSLOADER_NUM_3));
          RetError = FlsLoader_lPageWrite (LoadPageCount,
                                         OffSet,FlashType,SourceAddressPtr,
                                         TargetAddress,NoOfPages);
        }
        FlsLoader_lEnableInts(Icr);
      }
    }
  }
  return RetError;
}  /*End of function OCFLS_Write */
#define FLSLOADER_STOP_SEC_WRITE_CODE
/* MISRA2012_RULE_4_10_JUSTIFICATION: Flsloader_Memmap.h is repeatedly included
 * without include guard. This is as per AUTOSAR */
/* MISRA2012_RULE_20_1_JUSTIFICATION: declaration of 'FlsLoader_Status' before
 * #include memap.h - Accepted deviation in AUTOSAR */
#include "MemMap.h"

#define FLSLOADER_START_SEC_WRITE_CODE
/* MISRA2012_RULE_4_10_JUSTIFICATION: Flsloader_Memmap.h is repeatedly included
 * without include guard. This is as per AUTOSAR */
/* MISRA2012_RULE_20_1_JUSTIFICATION: declaration of 'FlsLoader_Status' before
 * #include memap.h - Accepted deviation in AUTOSAR */
#include "MemMap.h"
/*******************************************************************************
** Syntax           :  FlsLoader_ReturnType FlsLoader_Erase(                  **
**                      FlsLoader_AddressType TargetAddress,                  **
**                      FlsLoader_LengthType Length                           **
**                    )                                                       **
**                                                                            **
** Service ID       : 0x03                                                    **
**                                                                            **
** Sync/Async       : Synchronous                                             **
**                                                                            **
** Reentrancy       : non - reentrant                                         **
**                                                                            **
** Parameters(in)   : Length - Number of sectors                              **
**                    TargetAddress - Starting Address of the sector          **
**                                                                            **
** Parameters (out) : none                                                    **
**                                                                            **
** Return value     :  FlsLoader_ReturnType(DET is not enabled)               **
**                     1.FLSLOADER_E_OK                                       **
**                     2.FLSLOADER_E_BUSY                                     **
**                     4.FLSLOADER_E_LOCKED                                   **
**                                                                            **
**                     1.FLSLOADER_E_NOT_OK for all errors but for busy.      **
**                       For busy state FLSLOADER_E_BUSY is returned          **
**                                                                            **
** Description      : This function erases the sector of the internal flash.  **
*******************************************************************************/
/* Service to Erase a sector of Flash */
FlsLoader_ReturnType FlsLoader_Erase(FlsLoader_AddressType TargetAddress,
                                     FlsLoader_LengthType Length )
{
  FlsLoader_ReturnType  RetError;
  FlsLoader_AddressType StartAddress;
  uint32                FlsFsrCheck;
  uint32                FlsFSRErase;
  volatile uint32       BusyCheck;
  uint32                InnerCount;
  uint32                Icr;
  uint32                FlashType;

  /*Init RetError to OK */
  /*RetError = (FlsLoader_ReturnType)FLSLOADER_E_OK;*/

  /*Block 1: check DET */
  #if (FLSLOADER_DEV_ERROR_DETECT == STD_ON)
  RetError = FlsLoader_lEraseDetCheck(Length,TargetAddress);
  if (RetError == FLSLOADER_E_OK)
  #endif
  {
    /* Check for Busy state of FLASH
    Registers differ between Checking of Busy state of PFlash and DFlash */
    /* MISRA2012_RULE_11_4_JUSTIFICATION: SFR access */
    FlsFsrCheck = (DMU_HF_STATUS.U & ((uint32)FLSLOADER_FLASH_BUSY_MASK));

    if ( FlsFsrCheck != FLSLOADER_FALSE)
    {
      /* Report FLSLOADER_E_BUSY DET */
      #if (FLSLOADER_DEV_ERROR_DETECT == STD_ON)
      Det_ReportError( FLSLOADER_MODULE_ID,
                       FLSLOADER_INSTANCE_ID,
                       FLSLOADER_SID_ERASE,
                       (uint8)FLSLOADER_E_BUSY);
      #endif
      RetError = FLSLOADER_E_BUSY;
    }
    else
    {
      /* Extract the flash type */
      FlashType = FlsLoader_lGetFlashType (TargetAddress);

      /* Given Address belongs to Data FLASH */
      /*Check if the Target Address passed is UCB protected */
      /* Check if global write protection is installed in DFLASH*/
      /*Check if the Target Address passed is UCB protected */
      #if (FLSLOADER_ENABLE_LOCKCHECK == STD_ON)
      /* Protection Check Algorithm */
      /* Preprocessor switch to enable/disable the lockcheck functionality */
      /* Check if global write protection is installed */
      RetError = FlsLoader_lEraseLockCheck (TargetAddress,FlashType,Length);

      if (RetError == FLSLOADER_E_OK)
      #endif
      {
        StartAddress = FLSLOADER_CMD_BASE;
        Icr = FlsLoader_lDisableInts();
        if (FlashType != FLSLOADER_DFLASH_BANK0)
        {
          FlsLoader_lResetSafetyENDINIT();
        }
        DSYNC();
        FlsLoader_Status = FLSLOADER_NORMAL; /* Initiating the state to normal*/

        /* Safety Reset Endinit is required for PFlash */
        /* Enter Critical Section */
        /* cycle 1 */
        /*MISRA2012_RULE_11_6_JUSTIFICATION: FlsLoader_AddressType is defined of
        type volatile uint32 to avoid compiler optimization in command cycles*/
        /*MISRA2012_RULE_11_2_JUSTIFICATION: The Pointers are type-cast to
        uint32 for address comparison/calculation purpose.*/
        /*MISRA2012_RULE_13_2_JUSTIFICATION: The Pointers are type-cast to
         uint32 for address comparison/calculation purpose*/
        /*MISRA2012_RULE_1_3_JUSTIFICATION: The Pointers are type-cast to uint32
         *for address comparison/calculation purpose*/
        /*MISRA2012_RULE_10_8_JUSTIFICATION: The Pointers are type-cast to
         *uint32 for address comparison/calculation purpose*/
        /* MISRA2012_RULE_11_4_JUSTIFICATION: SFR access */
        *((FlsLoader_AddressType*)FLSLOADER_GET_CYCLE_AA50(StartAddress))  = 
                                                                  TargetAddress;
        /* cycle 2 */
        /*MISRA2012_RULE_11_6_JUSTIFICATION: FlsLoader_AddressType is defined of
        type volatile uint32 to avoid compiler optimization in command cycles*/
        /*MISRA2012_RULE_11_2_JUSTIFICATION: The Pointers are type-cast to
        uint32 for address comparison/calculation purpose.*/
        /*MISRA2012_RULE_13_2_JUSTIFICATION: The Pointers are type-cast to
         uint32 for address comparison/calculation purpose*/
        /*MISRA2012_RULE_1_3_JUSTIFICATION: The Pointers are type-cast to uint32
         *for address comparison/calculation purpose*/
        /*MISRA2012_RULE_10_8_JUSTIFICATION: The Pointers are type-cast to
         *uint32 for address comparison/calculation purpose*/
        /* MISRA2012_RULE_11_4_JUSTIFICATION: SFR access */
        *((FlsLoader_AddressType*)FLSLOADER_GET_CYCLE_AA58(StartAddress))  = 
                                                                   Length;
        /* cycle 3 */
        /*MISRA2012_RULE_11_6_JUSTIFICATION: FlsLoader_AddressType is defined of
        type volatile uint32 to avoid compiler optimization in command cycles*/
        /*MISRA2012_RULE_11_2_JUSTIFICATION: The Pointers are type-cast to
        uint32 for address comparison/calculation purpose.*/
        /*MISRA2012_RULE_13_2_JUSTIFICATION: The Pointers are type-cast to
         uint32 for address comparison/calculation purpose*/
        /*MISRA2012_RULE_1_3_JUSTIFICATION: The Pointers are type-cast to uint32
         *for address comparison/calculation purpose*/
        /*MISRA2012_RULE_10_8_JUSTIFICATION: The Pointers are type-cast to
         *uint32 for address comparison/calculation purpose*/
        /* MISRA2012_RULE_11_4_JUSTIFICATION: SFR access */
        *((FlsLoader_AddressType*)FLSLOADER_GET_CYCLE_AAA8(StartAddress))  = 
                                                             FLSLOADER_VALUE_80;
        /* cycle 4 */
        /*MISRA2012_RULE_11_6_JUSTIFICATION: FlsLoader_AddressType is defined of
        type volatile uint32 to avoid compiler optimization in command cycles*/
        /*MISRA2012_RULE_11_2_JUSTIFICATION: The Pointers are type-cast to
        uint32 for address comparison/calculation purpose.*/
        /*MISRA2012_RULE_13_2_JUSTIFICATION: The Pointers are type-cast to
         uint32 for address comparison/calculation purpose*/
        /*MISRA2012_RULE_1_3_JUSTIFICATION: The Pointers are type-cast to uint32
         *for address comparison/calculation purpose*/
        /*MISRA2012_RULE_10_8_JUSTIFICATION: The Pointers are type-cast to
         *uint32 for address comparison/calculation purpose*/
        /* MISRA2012_RULE_11_4_JUSTIFICATION: SFR access */
        *((FlsLoader_AddressType*)FLSLOADER_GET_CYCLE_AAA8(StartAddress))  = 
                                                             FLSLOADER_VALUE_50;
        /* Exit Critical Section */
        if (FlashType != FLSLOADER_DFLASH_BANK0)
        {
          FlsLoader_lSetSafetyENDINIT();
        }
        DSYNC();

        InnerCount = 0U;
        /* MISRA2012_RULE_11_4_JUSTIFICATION: SFR access */
        FlsFSRErase = DMU_HF_OPERATION.B.ERASE;

        while((FlsFSRErase != FLSLOADER_BIT_SET) &&
              (InnerCount < FLSLOADER_CMDCYCLE_TIMEOUT))
        {
          InnerCount++;
          /* MISRA2012_RULE_11_4_JUSTIFICATION: SFR access */
          FlsFSRErase = DMU_HF_OPERATION.B.ERASE;
#ifdef FLASH_OPERATION_CBK_TRICORE
            pFLASH_OperationCbk();
#endif
        }
        
        if(InnerCount < FLSLOADER_CMDCYCLE_TIMEOUT)
        {
          /* Check for FLASH BUSY flag */
          /* PnBUSY and D0BUSY */
          InnerCount = 0U;
          /* MISRA2012_RULE_11_4_JUSTIFICATION: SFR access */
          BusyCheck = (DMU_HF_STATUS.U & (uint32)FLSLOADER_FLASH_BUSY_MASK);
          while (( BusyCheck != 0U) &&
                 ( InnerCount < FLSLOADER_BUSY_TIMEOUT))
          {
            InnerCount++;
            /* MISRA2012_RULE_11_4_JUSTIFICATION: SFR access */
            BusyCheck = (DMU_HF_STATUS.U & (uint32)FLSLOADER_FLASH_BUSY_MASK);
#ifdef FLASH_OPERATION_CBK_TRICORE
            pFLASH_OperationCbk();
#endif

          }
          if (InnerCount < FLSLOADER_BUSY_TIMEOUT )
          {
            /* This check makes sure No protection error and no sequence error
            and No operation error has occurred.*/
            RetError = FlsLoader_lProtSeqOperErrorCheck();
            if(RetError == FLSLOADER_E_OK)
            {
              /* This check makes sure No erase verification error */
              RetError = FlsLoader_lEverCheck();
            }
          }
          else
          {
            RetError = FLSLOADER_E_NOT_OK;
          }
        }
        else
        {
          RetError = FLSLOADER_E_NOT_OK;
        }
        /* Clear the status if the operation is successful.*/
        /*MISRA2012_RULE_11_6_JUSTIFICATION: FlsLoader_AddressType is defined of
        type volatile uint32 to avoid compiler optimization in command cycles*/
        /*MISRA2012_RULE_11_2_JUSTIFICATION: The Pointers are type-cast to
        uint32 for address comparison/calculation purpose.*/
        /*MISRA2012_RULE_13_2_JUSTIFICATION: The Pointers are type-cast to
         uint32 for address comparison/calculation purpose*/
        /*MISRA2012_RULE_1_3_JUSTIFICATION: The Pointers are type-cast to uint32
         *for address comparison/calculation purpose*/
        /*MISRA2012_RULE_10_8_JUSTIFICATION: The Pointers are type-cast to
         *uint32 for address comparison/calculation purpose*/
        /* MISRA2012_RULE_11_4_JUSTIFICATION: SFR access */
        *((FlsLoader_AddressType*)FlsLoader_lClearStatus(StartAddress))
                          = FLSLOADER_VALUE_FA;
      
        FlsLoader_lEnableInts(Icr);
      }
    }
  }
  return RetError;
}  /* End of Function */
#define FLSLOADER_STOP_SEC_WRITE_CODE
/* MISRA2012_RULE_4_10_JUSTIFICATION: Flsloader_Memmap.h is repeatedly included
 * without include guard. This is as per AUTOSAR */
/* MISRA2012_RULE_20_1_JUSTIFICATION: declaration of 'FlsLoader_Status' before
 * #include memap.h - Accepted deviation in AUTOSAR */
#include "MemMap.h"

#define FLSLOADER_START_SEC_CODE
/* MISRA2012_RULE_4_10_JUSTIFICATION: Flsloader_Memmap.h is repeatedly included
 * without include guard. This is as per AUTOSAR */
/* MISRA2012_RULE_20_1_JUSTIFICATION: declaration of 'FlsLoader_Status' before
 * #include memap.h - Accepted deviation in AUTOSAR */
#include "MemMap.h"

  /* Preprocessor switch to enable/disable the FlsLoader_Lock API */
#if (FLSLOADER_LOCK_UNLOCK_API == STD_ON)
/*******************************************************************************
** Syntax           :  FlsLoader_ReturnType FlsLoader_Lock(                   **
**                              void                                          **
**                                                                            **
**                           )                                                **
**                                                                            **
** Service ID       : 0x04                                                    **
**                                                                            **
** Sync/Async       : Synchronous                                             **
**                                                                            **
** Reentrancy       : non - reentrant                                         **
**                                                                            **
** Parameters(in)   : FlsLoader_AddressType TargetAddress,                    **
**                    FlsLoader_LengthType Length                             **
**                                                                            **
** Parameters (out) : none                                                    **
**                                                                            **
** Return value     :  FlsLoader_ReturnType:(DET is not enabled)              **
**                     1.FLSLOADER_E_OK                                       **
**                     2.FLSLOADER_E_BUSY                                     **
**                     3.FLSLOADER_E_LOCKED                                   **
**                     4.FLSLOADER_E_NOT_OK for all errors but for busy.      **
**                       For busy state FLSLOADER_E_BUSY is returned          **
**                                                                            **
** Description      : This function is used to  Apply the sector protection to**
**                    the internal  Flash of the microcontroller.             **
**                    If any sector is previously locked FLSLOADER_E_LOCKED   **
**                    is returned.                                            **
**                    No valid parameters are expected here.                  **
**                    This API cannot be suspended                            **
**                    Service to Lock the internal flash of the microcontroller.
**                    Locking is dependent on the parameters given and not the**
**                    passsed parameters.                                     **
*******************************************************************************/
FlsLoader_ReturnType FlsLoader_Lock(void)
{
  uint32                FlashBusy;
  FlsLoader_ReturnType  RetError ;
  uint32                FlsFprodisp;
  uint32                FlsFproinp;
  uint32                FlsFproind;
  uint32                FlsFproinotp;

  RetError = FLSLOADER_E_OK ;

  #if (FLSLOADER_DEV_ERROR_DETECT == STD_ON)
  if (FlsLoader_InitStatus != FLSLOADER_INITIALIZED)
  {
    /* Report missing initialization to DET */
    Det_ReportError(FLSLOADER_MODULE_ID,
                    FLSLOADER_INSTANCE_ID,
                    FLSLOADER_SID_LOCK,
                    FLSLOADER_E_UNINIT);
    RetError = FLSLOADER_E_NOT_OK;
  }
  #endif
  /* (FLSLOADER_DEV_ERROR_DETECT == STD_ON) */

  /* Check if PFLASH or DFLASH is busy */
  /* MISRA2012_RULE_11_4_JUSTIFICATION: SFR access */
  FlashBusy = (uint32)(DMU_HF_STATUS.U & FLSLOADER_FLASH_BUSY_MASK);

  if (FlashBusy != FLSLOADER_ZERO_DATA)
  {
    /* Report Flash Busy to DET */
    RetError = FLSLOADER_E_BUSY;
    #if (FLSLOADER_DEV_ERROR_DETECT == STD_ON)
    Det_ReportError(FLSLOADER_MODULE_ID,
                    FLSLOADER_INSTANCE_ID,
                    FLSLOADER_SID_LOCK,
                    (uint8)FLSLOADER_E_BUSY);
    #endif    /*(FLSLOADER_DEV_ERROR_DETECT == STD_ON)*/
  }
    /* Protection should not be installed for the corresponding user level.*/
  if (RetError == FLSLOADER_E_OK)
  {
    /* Check if read/write/OTP/WOP is installled in PFLASH or DFLASH */
    /* MISRA2012_RULE_11_4_JUSTIFICATION: SFR access */
    FlsFprodisp = DMU_HF_PROTECT.B.PRODISP;
    /* Confirmation state of Pflash and Dflash */
    /* MISRA2012_RULE_11_4_JUSTIFICATION: SFR access */
    FlsFproinp = DMU_HF_CONFIRM1.B.PROINPO;
    /* MISRA2012_RULE_11_4_JUSTIFICATION: SFR access */
    FlsFproind = DMU_HF_CONFIRM1.B.PROINDO;
    /* MISRA2012_RULE_11_4_JUSTIFICATION: SFR access */
    FlsFproinotp = DMU_HF_CONFIRM2.B.PROINOTP0O;

    if(FlsFprodisp != 1U)
    {
      if(FlsFproinp == FLSLOADER_UCB_FLASH_CONFIRMED)
      {
        RetError = FLSLOADER_E_LOCKED;
      }
      if(FlsFproind == FLSLOADER_UCB_FLASH_CONFIRMED)
      {
        RetError = FLSLOADER_E_LOCKED;
      }
    }

    if(FlsFproinp == FLSLOADER_UCB_FLASH_ERRORED)
    {
      RetError = FLSLOADER_E_LOCKED;
    }
    else if (FlsFproind == FLSLOADER_UCB_FLASH_ERRORED)
    {
      RetError = FLSLOADER_E_LOCKED;
    }
    else
    {
      /* Do nothing */
    }

    if(FlsFproinotp == FLSLOADER_UCB_FLASH_CONFIRMED)
    {
      RetError = FLSLOADER_E_LOCKED;
    }
  }

  if (RetError == FLSLOADER_E_OK)
  {
    RetError = FlsLoader_lLock();
  }

  return RetError;
}  /* End of function FlsLoader_Lock */
#endif  /*(FLSLOADER_LOCK_UNLOCK_API == STD_ON) */


#if (FLSLOADER_LOCK_UNLOCK_API == STD_ON)
/*******************************************************************************
** Syntax           :  FlsLoader_ReturnType FlsLoader_UnLock(                 **
**                       FlsLoader_AddressType TargetAddress,                 **
**                       FlsLoader_ValueType* Password                        **
**                                                                            **
**                    )                                                       **
**                                                                            **
** Service ID       : 0x05                                                    **
**                                                                            **
** Sync/Async       : Synchronous                                             **
**                                                                            **
** Reentrancy       : non - reentrant                                         **
**                                                                            **
** Parameters(in)   :                                                         **
**                    Password: pointer to the 4 double word(256 bit)         **
**                               Password for UCB protection                  **
**                    TargetAddress: Target address of user config block.     **
**                    Possible values are 0xAF100000, 0xAF100400.             **
**                                                                            **
** Parameters (out) : none                                                    **
**                                                                            **
** Return value     : FlsLoader_ReturnType:(DET is not enabled)               **
**                    1.FLSLOADER_E_OK                                        **
**                    2.FLSLOADER_E_BUSY                                      **
**                    3.FLSLOADER_E_NOT_OK                                    **
**                                                                            **
** Description      : This function is used to  unlock(protect) the protection
                      in                                PFLASH and DFLASH     **
                      protection.                                             **
**                    A wrong password will result in Protection Error        **
**                    This API needs to be called twice if the user needs to  **
**                    unlock both PFLASH and DFLASH protection                **
**                    This API cannot be suspended                            **
*******************************************************************************/
FlsLoader_ReturnType FlsLoader_UnLock(
                                    FlsLoader_AddressType TargetAddress,
                                    FlsLoader_ValueType* Password
                                    )
{
  FlsLoader_ReturnType   RetError ;
  FlsLoader_AddressType  StartAddress;
  uint32                 FlsErrCheck;
  volatile uint32        FlsBusyStat;
  volatile uint32        FlsFpro;
  volatile uint32        FlsFprodisd;
  volatile uint8         UserConfig;
  volatile uint8         Index;
  volatile FlsLoader_ValueType* Passwordptr;

  /* Init RetError to OK */
  RetError = FLSLOADER_E_OK ;
  Passwordptr = Password;

  #if (FLSLOADER_DEV_ERROR_DETECT == STD_ON)
  if (FlsLoader_InitStatus != FLSLOADER_INITIALIZED)
  {
    /*  Report missing initialization to DET */
    Det_ReportError(FLSLOADER_MODULE_ID,
                    FLSLOADER_INSTANCE_ID,
                    FLSLOADER_SID_UNLOCK,
                    FLSLOADER_E_UNINIT);
    RetError = FLSLOADER_E_NOT_OK;
  }
  else
  {
    /*MISRA2012_RULE_13_2_JUSTIFICATION: TargetAddress is defined of type
    volatile uint32 to avoid compiler optimization in command cycles*/
    /*MISRA2012_RULE_1_3_JUSTIFICATION: TargetAddress is defined of type
    volatile uint32 to avoid compiler optimization in command cycles*/
    if (TargetAddress != FLSLOADER_UCB_PFLASH_ORGINAL_START)
    {
      /*MISRA2012_RULE_13_2_JUSTIFICATION: TargetAddress is defined of type
      volatile uint32 to avoid compiler optimization in command cycles*/
      /*MISRA2012_RULE_1_3_JUSTIFICATION: TargetAddress is defined of type
      volatile uint32 to avoid compiler optimization in command cycles*/
      if (TargetAddress != FLSLOADER_UCB_DFLASH_ORIGINAL_START)
      {
        Det_ReportError(FLSLOADER_MODULE_ID,
                        FLSLOADER_INSTANCE_ID,
                        FLSLOADER_SID_UNLOCK,
                        FLSLOADER_E_PARAM_ADDRESS);
        RetError = FLSLOADER_E_NOT_OK;
      }
    }
  }
  #endif
  /* #if (FLSLOADER_DEV_ERROR_DETECT == STD_ON) */

  /* PROTECTION in PFLASH  */
  /*MISRA2012_RULE_13_2_JUSTIFICATION: TargetAddress is defined of type
  volatile uint32 to avoid compiler optimization in command cycles*/
  /*MISRA2012_RULE_1_3_JUSTIFICATION: TargetAddress is defined of type
  volatile uint32 to avoid compiler optimization in command cycles*/
  if ( TargetAddress == FLSLOADER_UCB_PFLASH_ORGINAL_START )
  {
    /* PROTECTION in PFLASH  */
    UserConfig = FLSLOADER_UCB0;
  }
  else
  {
    /* PROTECTION in DFLASH  */
    UserConfig = FLSLOADER_UCB1;
  }
  /* Start address for the command cycle */
  StartAddress = FLSLOADER_DFLASH0_START_ADDRESS;
  /* MISRA2012_RULE_11_4_JUSTIFICATION: SFR access */
  FlsBusyStat = (uint32)(DMU_HF_STATUS.U & (uint32)FLSLOADER_FLASH_BUSY_MASK);

  if (FlsBusyStat != 0U)
  {
    /* Report Pflash busy to DET */
    #if (FLSLOADER_DEV_ERROR_DETECT == STD_ON)
    Det_ReportError(
                    FLSLOADER_MODULE_ID,
                    FLSLOADER_INSTANCE_ID,
                    FLSLOADER_SID_UNLOCK,
             (uint8)FLSLOADER_E_BUSY);
    #endif
    RetError = FLSLOADER_E_BUSY;
  }
  if (RetError == FLSLOADER_E_OK)
  {
    /* cycle 1 */
    /*MISRA2012_RULE_11_6_JUSTIFICATION: FlsLoader_AddressType is defined of
    type volatile uint32 to avoid compiler optimization in command cycles*/
    /*MISRA2012_RULE_11_2_JUSTIFICATION: The Pointers are type-cast to uint32
    for address comparison/calculation purpose.*/
    /*MISRA2012_RULE_13_2_JUSTIFICATION: The Pointers are type-cast to uint32
     *for address comparison/calculation purpose*/
    /*MISRA2012_RULE_1_3_JUSTIFICATION: The Pointers are type-cast to uint32
     *for address comparison/calculation purpose*/
    /*MISRA2012_RULE_10_8_JUSTIFICATION: The Pointers are type-cast to
     *uint32 for address comparison/calculation purpose*/
    /* MISRA2012_RULE_11_4_JUSTIFICATION: SFR access */
    *((FlsLoader_AddressType*)FLSLOADER_GET_CYCLE_553C(StartAddress))  = 
                                                              UserConfig;
    /* Cycle 2 to Cycle 9 : Passwords for disabling protection */
    for(Index =(uint8)0U; Index < FLSLOADER_PWD; Index++)
    {
      /* provide 8 passwords */
      /*MISRA2012_RULE_11_6_JUSTIFICATION: FlsLoader_AddressType is defined of
      type volatile uint32 to avoid compiler optimization in command cycles*/
      /*MISRA2012_RULE_11_2_JUSTIFICATION: The Pointers are type-cast to uint32
      for address comparison/calculation purpose.*/
      /*MISRA2012_RULE_13_2_JUSTIFICATION: The Pointers are type-cast to uint32
       *for address comparison/calculation purpose*/
      /*MISRA2012_RULE_1_3_JUSTIFICATION: The Pointers are type-cast to uint32
       *for address comparison/calculation purpose*/
      /*MISRA2012_RULE_10_8_JUSTIFICATION: The Pointers are type-cast to
       *uint32 for address comparison/calculation purpose*/
      /* MISRA2012_RULE_11_4_JUSTIFICATION: SFR access */
      *((FlsLoader_AddressType*)FLSLOADER_GET_CYCLE_553C(StartAddress))  = 
                                                         Passwordptr[Index];
    }
    if (UserConfig == FLSLOADER_UCB0)
    {
      /*Check if there are no protection and sequence errors*/
      FlsErrCheck = FlsLoader_lProtSeqOperErrorCheck();
      /* Check if PFlash Protection is Disabled*/
      /* MISRA2012_RULE_11_4_JUSTIFICATION: SFR access */
      FlsFpro     = DMU_HF_PROTECT.B.PRODISP;
      /* return if protection is not disabled or if there are errors */
      if ((FlsFpro == 0U) || (FlsErrCheck == FLSLOADER_E_NOT_OK))
      {
      /* return if protection is not disabled or if there are errors */
        RetError = FLSLOADER_E_NOT_OK;
      }
    }
    else
    {
      /*Check if there are no protection and sequence errors*/
      FlsErrCheck = FlsLoader_lProtSeqOperErrorCheck();
      /* Check if DFlash Protection is Disabled*/
      /* MISRA2012_RULE_11_4_JUSTIFICATION: SFR access */
      FlsFprodisd = DMU_HF_PROTECT.B.PRODISD;
      /* return if protection is not disabled or if there are errors */
      if ((FlsFprodisd == 0U) || (FlsErrCheck == FLSLOADER_E_NOT_OK))
      {
        /* return if protection is not disabled or if there are errors */
        RetError = FLSLOADER_E_NOT_OK;
      }
    }

    if (RetError == (FlsLoader_ReturnType)FLSLOADER_E_OK)
    {
      /*MISRA2012_RULE_11_6_JUSTIFICATION: FlsLoader_AddressType is defined of
      type volatile uint32 to avoid compiler optimization in command cycles*/
      /*MISRA2012_RULE_11_2_JUSTIFICATION: The Pointers are type-cast to uint32
      for address comparison/calculation purpose.*/
      /*MISRA2012_RULE_13_2_JUSTIFICATION: The Pointers are type-cast to uint32
       *for address comparison/calculation purpose*/
      /*MISRA2012_RULE_1_3_JUSTIFICATION: The Pointers are type-cast to uint32
       *for address comparison/calculation purpose*/
      /*MISRA2012_RULE_10_8_JUSTIFICATION: The Pointers are type-cast to
       *uint32 for address comparison/calculation purpose*/
      /* MISRA2012_RULE_11_4_JUSTIFICATION: SFR access */
      *((FlsLoader_AddressType*)FlsLoader_lClearStatus(StartAddress)) = 
                                                      FLSLOADER_VALUE_FA;
    }
  }
  return RetError;
  /*MISRA2012_RULE_8_13_JUSTIFICATION: Accepted deviation in AUTOSAR*/
}
#endif  /* if (FLSLOADER_LOCK_UNLOCK_API == STD_ON)    */

#if (FLSLOADER_SUSPEND_API == STD_ON)
/*******************************************************************************
** Syntax           :  FlsLoader_ReturnType FlsLoader_Suspend(                **
**                      void                                                  **
**                    )                                                       **
**                                                                            **
** Service ID       : 0x06                                                    **
**                                                                            **
** Sync/Async       : Synchronous                                             **
**                                                                            **
** Reentrancy       : non - reentrant                                         **
**                                                                            **
** Parameters(in)   : void                                                    **
**                                                                            **
** Parameters (out) : none                                                    **
**                                                                            **
** Return value     : FLSLOADER_E_OK - API excecuted succesffully             **
**                    FLSLOADER_E_NOT_OK - DET errors occured                 **
**                                                                            **
**                                                                            **
** Description      : This function is used to  suspend flash write or        **
                      erase operation.                                        **
*******************************************************************************/
FlsLoader_ReturnType FlsLoader_Suspend (void)
{
  FlsLoader_ReturnType RetError ;
  RetError = FLSLOADER_E_OK;

  #if (FLSLOADER_DEV_ERROR_DETECT == STD_ON)
  if (FlsLoader_InitStatus != FLSLOADER_INITIALIZED)
  {
    /* Report missing initialization to DET */
    Det_ReportError(
                    FLSLOADER_MODULE_ID,
                    FLSLOADER_INSTANCE_ID,
                    FLSLOADER_SID_SUSPEND,
                    FLSLOADER_E_UNINIT);
    
    RetError = FLSLOADER_E_NOT_OK;
  }
  #endif

  FlsLoader_Status = FLSLOADER_SUSPEND;
  return RetError;
}  /*End of suspend function */
#endif /* (FLSLOADER_SUSPEND_API == STD_ON) */

#define FLSLOADER_STOP_SEC_CODE
/* MISRA2012_RULE_4_10_JUSTIFICATION: Flsloader_Memmap.h is repeatedly included
 * without include guard. This is as per AUTOSAR */
/* MISRA2012_RULE_20_1_JUSTIFICATION: declaration of 'FlsLoader_Status' before
 * #include memap.h - Accepted deviation in AUTOSAR */
#include "MemMap.h"
  /* Inline Functions */

#define FLSLOADER_START_SEC_WRITE_CODE
/* MISRA2012_RULE_4_10_JUSTIFICATION: Flsloader_Memmap.h is repeatedly included
 * without include guard. This is as per AUTOSAR */
/* MISRA2012_RULE_20_1_JUSTIFICATION: declaration of 'FlsLoader_Status' before
 * #include memap.h - Accepted deviation in AUTOSAR */
#include "MemMap.h"

/*******************************************************************************
** Syntax       :LOCAL_INLINE FlsLoader_ReturnType FlsLoader_lPverCheck  (**
**                                                                            **
**                                                                            **
** Service ID       : None                                                    **
**                                                                            **
** Sync/Async       : Synchronous                                             **
**                                                                            **
** Reentrancy       : non - reentrant                                         **
**                                                                            **
** Parameters(in)   :                                                         **
**                                                                            **
** Parameters (out) : None                                                    **
**                                                                            **
** Return value     : value: RetError                                         **
**                                                                            **
** Description      : This function checks for Program Verify Error           **
*******************************************************************************/
LOCAL_INLINE FlsLoader_ReturnType FlsLoader_lPverCheck(void)
{
  volatile uint32 FlsPeverErr ;
  FlsLoader_ReturnType  RetError;

  RetError = FLSLOADER_E_OK;
  /* MISRA2012_RULE_11_4_JUSTIFICATION: SFR access */
  FlsPeverErr = (uint32)(DMU_HF_STATUS.U & FLSLOADER_PVER_ERROR);
  
  if (FlsPeverErr != FLSLOADER_FALSE)
  {
    RetError = FLSLOADER_E_NOT_OK;
  }
  return RetError;
}
/*******************************************************************************
** Syntax          :LOCAL_INLINE FlsLoader_ReturnType                     **
**                                  FlsLoader_lEverCheck(void)                **
**                                                                            **
**                                                                            **
** Service ID       : None                                                    **
**                                                                            **
** Sync/Async       : Synchronous                                             **
**                                                                            **
** Reentrancy       : non - reentrant                                         **
**                                                                            **
** Parameters(in)   :                                                         **
**                                                                            **
** Parameters (out) : None                                                    **
**                                                                            **
** Return value     : value: RetError                                         **
**                                                                            **
** Description      : This function checks for Erase Verify Error             **
*******************************************************************************/
LOCAL_INLINE FlsLoader_ReturnType FlsLoader_lEverCheck(void)
{
  volatile uint32 FlsEverError;
  FlsLoader_ReturnType  RetError;

  RetError = FLSLOADER_E_OK;
  /* MISRA2012_RULE_11_4_JUSTIFICATION: SFR access */
  FlsEverError = (uint32)(DMU_HF_ERRSR.U & FLSLOADER_EVER_ERROR);
  
  if (FlsEverError != FLSLOADER_FALSE)
  {
    RetError = FLSLOADER_E_NOT_OK;
  }
  return RetError;
}
/*******************************************************************************
** Syntax           : uint32 FlsLoader_lDisableInts                           **
**                    (                                                       **
**                      void                                                  **
**                    )                                                       **
**                                                                            **
** Service ID       :   NA                                                    **
**                                                                            **
** Sync/Async       : Synchronous                                             **
**                                                                            **
** Reentrancy       : reentrant                                               **
**                                                                            **
** Parameters (in)  : none                                                    **
**                                                                            **
** Parameters (out) :                                                         **
** Return value     : uint32                                                  **
**                                                                            **
** Description      : This function disables the global interrupt flag.       **
**                                                                            **
*******************************************************************************/
uint32 FlsLoader_lDisableInts(void)
{
  uint32 Icr;
  /* read interrupt control register */
  ISYNC(); /* execute isync */
  Icr = (uint32)MFCR(CPU_ICR);
  DISABLE();
  return Icr;

}
/*******************************************************************************
** Syntax           : void FlsLoader_lEnableInts                              **
**                    (                                                       **
**                      uint32 Icr                                            **
**                    )                                                       **
**                                                                            **
** Service ID       :   NA                                                    **
**                                                                            **
** Sync/Async       : Synchronous                                             **
**                                                                            **
** Reentrancy       : reentrant                                               **
**                                                                            **
** Parameters (in)  : none                                                    **
**                                                                            **
** Parameters (out) :                                                         **
** Return value     : uint32                                                  **
**                                                                            **
** Description      : This function restores the global interrupt flag.       **
**                                                                            **
*******************************************************************************/
void FlsLoader_lEnableInts(uint32 Icr)
{
  uint32 IcrStatus=(uint32)Icr & ((uint32)1U << (uint32)FLSLOADER_SHIFT_BY_15);
  if (IcrStatus != FLSLOADER_FALSE)
  {
  /* interrupts were enabled, enable again */
    ENABLE();
  }

}
/*******************************************************************************
** Syntax           : void FlsLoader_lResetSafetyENDINIT                      **
**                    (                                                       **
**                      void                                                  **
**                    )                                                       **
**                                                                            **
** Service ID       :   NA                                                    **
**                                                                            **
** Sync/Async       : Synchronous                                             **
**                                                                            **
** Reentrancy       : reentrant                                               **
**                                                                            **
** Parameters (in)  : none                                                    **
**                                                                            **
** Parameters (out) :                                                         **
** Return value     : void                                                    **
**                                                                            **
** Description      : This function resets the safety end init flag.          **
** When FLsLoader driver is executing write or erase, it is assumed that      **
** there are no other tasks running in parallel or from another core that     **
** requires the service of safety WDG endinit function.                       **
** Password sequencing will not be enabled and not checked within this        **
** function, also Time based check is not enabled                             **
**                                                                            **
*******************************************************************************/
LOCAL_INLINE void FlsLoader_lResetSafetyENDINIT(void)
{
  uint32 NewValCon0;
  uint32 NewPw;                   /* next password to be used */
  uint32 NewRel;                  /* next reload value to be used */
 
  uint32 Result;
  
  /* Safety Wdg register is acquired */
  /*MISRA2012_RULE_19_2_JUSTIFICATION: Union used for register type
       definition */
  /* MISRA2012_RULE_11_4_JUSTIFICATION: SFR access */
  volatile Ifx_SCU_WDTS_CON0* ScuWdtcon0Ptr = &SCU_WDTS_CON0;
  /* save old value */
  /* MISRA2012_RULE_11_4_JUSTIFICATION: SFR access */
  NewValCon0  = SCU_WDTS_CON0.U;
  /* get valid next password */

  Result = NewValCon0 & FLSLOADER_WDT_PASSWORD_MASK;
  Result = ( Result & FLSLOADER_WDT_PASSWORD_UPPER_MASK) |
             ((~(Result & FLSLOADER_WDT_PASSWORD_LOWER_MASK)) 
             & FLSLOADER_WDT_PASSWORD_LOWER_MASK );

  /* password sequencing will not be enabled at this time,
  no need for the run time calculation of password */
  NewPw = Result;
  /* get valid next timer reload */
  Result = NewValCon0 & FLSLOADER_WDT_RELOAD_MASK;
  /* Time control enable shall not be enabled by the system */
  NewRel= Result;
  /* build required password WDTCON0 value */
  NewValCon0 =  ( (NewRel) |              /* new reload value  */
                  (NewPw)  |              /* new Password */
                  (1u) );                 /* Clear LCK, keep ENDINIT set */

  ScuWdtcon0Ptr->U  = NewValCon0;        /* password access to unlock */

  NewValCon0 &= ~ FLSLOADER_WDT_STATUS_MASK;/*clear ENDINIT and LCK Bit */
  NewValCon0 |= FLSLOADER_NUM_2;                    /* set LCK Bit */

  ScuWdtcon0Ptr->U = NewValCon0;  /* write access and lock for Timeout mode */
}

/*******************************************************************************
** Syntax           : void FlsLoader_lSetSafetyENDINIT                        **
**                    (                                                       **
**                      void                                                  **
**                    )                                                       **
**                                                                            **
** Service ID       :   NA                                                    **
**                                                                            **
** Sync/Async       : Synchronous                                             **
**                                                                            **
** Reentrancy       : reentrant                                               **
**                                                                            **
** Parameters (in)  : none                                                    **
**                                                                            **
** Parameters (out) :                                                         **
** Return value     : void                                                    **
**                                                                            **
** Description      : This function sets  the safety end init flag.           **
** When FLsLoader driver is executing write or erase, it is assumed that      **
** there are no other tasks running in parallel or from another core that     **
** requires the service of safety WDG endinit function.                       **
**                                                                            **
*******************************************************************************/
LOCAL_INLINE void FlsLoader_lSetSafetyENDINIT(void)
{
  uint32 NewValCon0;
  uint32 NewPw;                   /* next password to be used */
  uint32 NewRel;                  /* next timer reload to be used */
  uint32 Result;
  /*MISRA2012_RULE_19_2_JUSTIFICATION: Union used for register type
       definition */
  /* MISRA2012_RULE_11_4_JUSTIFICATION: SFR access */
  volatile Ifx_SCU_WDTS_CON0* ScuWdtcon0Ptr = &SCU_WDTS_CON0;
  /* save old value */
  /* MISRA2012_RULE_11_4_JUSTIFICATION: SFR access */
  NewValCon0  =SCU_WDTS_CON0.U;

  Result = NewValCon0 & FLSLOADER_WDT_PASSWORD_MASK;
  Result = ( Result & FLSLOADER_WDT_PASSWORD_UPPER_MASK) |
             ((~(Result & FLSLOADER_WDT_PASSWORD_LOWER_MASK)) 
             & FLSLOADER_WDT_PASSWORD_LOWER_MASK );
  NewPw = Result;

  Result = NewValCon0 & FLSLOADER_WDT_RELOAD_MASK;
  NewRel= Result;
  /* build required password WDTCON0 value */
  NewValCon0  =  ( (NewRel) |             /* new reload value  */
                  (NewPw)   |             /* new Password */
                  (1u) );                 /* Clear LCK, keep ENDINIT set */
  /* MISRA2012_RULE_11_4_JUSTIFICATION: SFR access */
  SCU_WDTS_CON0.U   = NewValCon0;         /*  unlock with password access */
  /* clear timer reload and restore saved and corrected reload value */
  NewValCon0 &= ~FLSLOADER_WDT_STATUS_MASK;/* clear ENDINIT and LCK Bit*/
  NewValCon0 |= FLSLOADER_NUM_3;         /* set LCK and ENDINIT Bit */
  ScuWdtcon0Ptr->U = NewValCon0;         /* write modify access and lock */

}

/*CYCLOMATIC_FlsLoader_lBurstWrite_JUSTIFICATION: This API perform the command
 * cycle execution where is is necessary to have all these checks
*/
/*******************************************************************************
** Syntax           :  void FlsLoader_lBurstWrite (uint32 BurstLoadPageCount, **
**                          FlsLoader_AddressType BurstOffSet,                **
**                          uint32 FlashType,                                 **
**                          const uint8 *SourceAddressPtr,                    **
**                          FlsLoader_AddressType TargetAddress,              **
**                          uint32 NumberOfBursts);                           **
**                                                                            **
** Service ID       :   NA                                                    **
**                                                                            **
** Sync/Async       : Synchronous                                             **
**                                                                            **
** Reentrancy       : reentrant                                               **
**                                                                            **
** Parameters (in)  : BurstLoadPageCount,                                     **
**                    BurstOffSet,                                            **
**                    FlashType,                                              **
**                    PdataPtr,                                               **
**                    TargetAddress                                           **
**                                                                            **
** Parameters (out) :                                                         **
**                                                                            **
** Return value     : FLSLOADER_E_OK                                          **
**                    FLSLOADER_E_NOT_OK                                      **
**                                                                            **
** Description      :                                                         **
**                                                                            **
**                                                                            **
*******************************************************************************/
LOCAL_INLINE FlsLoader_ReturnType FlsLoader_lBurstWrite (
                            uint32 BurstLoadPageCount,
                            FlsLoader_AddressType BurstOffSet,
                            uint32 FlashType,
                            const uint8 *SourceAddressPtr,
                            FlsLoader_AddressType TargetAddress,
                            uint32 NumberOfBursts)
{
  volatile uint32                FlashBusyStat;
  volatile uint32                BusyCheck;
  FlsLoader_AddressType         *PdataPtr;
  FlsLoader_AddressType         *LoadPageAddress;
  FlsLoader_ReturnType           RetError;
  FlsLoader_AddressType          StartAddress;
  uint32                         InCount;
  uint32                         Count;
  

  StartAddress = FLSLOADER_CMD_BASE;
  RetError = FLSLOADER_E_OK;
  /*MISRA2012_RULE_11_8_JUSTIFICATION: "PdataPtr" attempt to cast away
  volatile in terms of pointer access*/
  /*MISRA2012_RULE_11_5_JUSTIFICATION: "PdataPtr" attempt to cast away
  volatile in terms of pointer access*/
  /*MISRA2012_RULE_11_3_JUSTIFICATION: "PdataPtr" attempt to cast away
  volatile in terms of pointer access*/
  PdataPtr = (FlsLoader_AddressType *)(void *)(SourceAddressPtr);
 
  for (Count = 0U; 
      (Count < NumberOfBursts) && (RetError == FLSLOADER_E_OK); 
       Count++)
  {
    if (FlashType != FLSLOADER_DFLASH_BANK0)
    {
      FlsLoader_lResetSafetyENDINIT();
    }
    /* Enter the Page Mode */
    /*MISRA2012_RULE_11_6_JUSTIFICATION: FlsLoader_AddressType is defined of
    type volatile uint32 to avoid compiler optimization in command cycles*/
    /*MISRA2012_RULE_11_2_JUSTIFICATION: The Pointers are type-cast to uint32
    for address comparison/calculation purpose.*/
    /*MISRA2012_RULE_13_2_JUSTIFICATION: The Pointers are type-cast to uint32
     *for address comparison/calculation purpose*/
    /*MISRA2012_RULE_1_3_JUSTIFICATION: The Pointers are type-cast to uint32
     *for address comparison/calculation purpose*/
    /*MISRA2012_RULE_10_8_JUSTIFICATION: The Pointers are type-cast to
     *uint32 for address comparison/calculation purpose*/
    /* MISRA2012_RULE_11_4_JUSTIFICATION: SFR access */
    *((FlsLoader_AddressType*)FlsLoader_lEnterPageMode(StartAddress)) = \
                              FlsLoader_lGetMode(FlashType);

    DSYNC();
    InCount = 0U;
    /* Check if Program Flash is in page mode */
    if (FlashType != FLSLOADER_DFLASH_BANK0)
    {
      /* MISRA2012_RULE_11_4_JUSTIFICATION: SFR access */
      FlashBusyStat = DMU_HF_STATUS.B.PFPAGE;

      while((FlashBusyStat != FLSLOADER_BIT_SET) &&
           (InCount < FLSLOADER_CMDCYCLE_TIMEOUT))
      {
        InCount++;
        /* MISRA2012_RULE_11_4_JUSTIFICATION: SFR access */
        FlashBusyStat = DMU_HF_STATUS.B.PFPAGE;
#ifdef FLASH_OPERATION_CBK_TRICORE
            pFLASH_OperationCbk();
#endif
      }
    }
    else
    {
      /* MISRA2012_RULE_11_4_JUSTIFICATION: SFR access */
      FlashBusyStat = DMU_HF_STATUS.B.DFPAGE;

      while ((FlashBusyStat != FLSLOADER_BIT_SET) &&
             (InCount < FLSLOADER_CMDCYCLE_TIMEOUT))
      {
        InCount++;
        /* MISRA2012_RULE_11_4_JUSTIFICATION: SFR access */
        FlashBusyStat = DMU_HF_STATUS.B.DFPAGE;
#ifdef FLASH_OPERATION_CBK_TRICORE
            pFLASH_OperationCbk();
#endif
      }
    }

    /* Check PFPAGE/DFPAGE bit was SET */
    if(InCount < FLSLOADER_CMDCYCLE_TIMEOUT)
    {
      for (InCount=0U; InCount < BurstLoadPageCount; InCount++)
      {
        /* Load the data */
      /*MISRA2012_RULE_11_6_JUSTIFICATION: FlsLoader_AddressType is defined of
      type volatile uint32 to avoid compiler optimization in command cycles*/
      /*MISRA2012_RULE_11_2_JUSTIFICATION: The Pointers are type-cast to uint32
      for address comparison/calculation purpose.*/
      /*MISRA2012_RULE_13_2_JUSTIFICATION: The Pointers are type-cast to uint32
       *for address comparison/calculation purpose*/
      /*MISRA2012_RULE_1_3_JUSTIFICATION: The Pointers are type-cast to uint32
       *for address comparison/calculation purpose*/
      /*MISRA2012_RULE_10_8_JUSTIFICATION: The Pointers are type-cast to
       *uint32 for address comparison/calculation purpose*/
        /* MISRA2012_RULE_11_4_JUSTIFICATION: SFR access */
        LoadPageAddress = \
              (FlsLoader_AddressType *)FlsLoader_lLoadPage(StartAddress);
        *LoadPageAddress = *PdataPtr;
        /*MISRA2012_RULE_18_4_JUSTIFICATION: Pointer arithmetic is used to
        access user buffer efficiently*/
        *(LoadPageAddress + 1U) = *(PdataPtr + 1U);
        /*MISRA2012_RULE_18_4_JUSTIFICATION: Pointer arithmetic used to load
        data into address and is within allowed range*/
        PdataPtr += FLSLOADER_NUM_2;
        DSYNC();
        /* Load Page register gets incremented automatically. */
      }
      /* cycle 1 */
      /*MISRA2012_RULE_11_6_JUSTIFICATION: FlsLoader_AddressType is defined of
      type volatile uint32 to avoid compiler optimization in command cycles*/
      /*MISRA2012_RULE_11_2_JUSTIFICATION: The Pointers are type-cast to uint32
      for address comparison/calculation purpose.*/
      /*MISRA2012_RULE_13_2_JUSTIFICATION: The Pointers are type-cast to uint32
       *for address comparison/calculation purpose*/
      /*MISRA2012_RULE_1_3_JUSTIFICATION: The Pointers are type-cast to uint32
       *for address comparison/calculation purpose*/
      /*MISRA2012_RULE_10_8_JUSTIFICATION: The Pointers are type-cast to
       *uint32 for address comparison/calculation purpose*/
      /* MISRA2012_RULE_11_4_JUSTIFICATION: SFR access */
      *((FlsLoader_AddressType*)FLSLOADER_GET_CYCLE_AA50(StartAddress)) = \
                                                                  TargetAddress;
      /* cycle 2 */
      /*MISRA2012_RULE_11_6_JUSTIFICATION: FlsLoader_AddressType is defined of
      type volatile uint32 to avoid compiler optimization in command cycles*/
      /*MISRA2012_RULE_11_2_JUSTIFICATION: The Pointers are type-cast to uint32
      for address comparison/calculation purpose.*/
      /*MISRA2012_RULE_13_2_JUSTIFICATION: The Pointers are type-cast to uint32
       *for address comparison/calculation purpose*/
      /*MISRA2012_RULE_1_3_JUSTIFICATION: The Pointers are type-cast to uint32
       *for address comparison/calculation purpose*/
      /*MISRA2012_RULE_10_8_JUSTIFICATION: The Pointers are type-cast to
       *uint32 for address comparison/calculation purpose*/
      /* MISRA2012_RULE_11_4_JUSTIFICATION: SFR access */
      *((FlsLoader_AddressType*)FLSLOADER_GET_CYCLE_AA58(StartAddress))= \
                                                             FLSLOADER_VALUE_00;
      /* cycle 3 */
      /*MISRA2012_RULE_11_6_JUSTIFICATION: FlsLoader_AddressType is defined of
      type volatile uint32 to avoid compiler optimization in command cycles*/
      /*MISRA2012_RULE_11_2_JUSTIFICATION: The Pointers are type-cast to uint32
      for address comparison/calculation purpose.*/
      /*MISRA2012_RULE_13_2_JUSTIFICATION: The Pointers are type-cast to uint32
       *for address comparison/calculation purpose*/
      /*MISRA2012_RULE_1_3_JUSTIFICATION: The Pointers are type-cast to uint32
       *for address comparison/calculation purpose*/
      /*MISRA2012_RULE_10_8_JUSTIFICATION: The Pointers are type-cast to
       *uint32 for address comparison/calculation purpose*/
      /* MISRA2012_RULE_11_4_JUSTIFICATION: SFR access */
      *((FlsLoader_AddressType*)FLSLOADER_GET_CYCLE_AAA8(StartAddress)) = \
                                                             FLSLOADER_VALUE_A0;
      /*cycle 4 */
      /*MISRA2012_RULE_11_6_JUSTIFICATION: FlsLoader_AddressType is defined of
      type volatile uint32 to avoid compiler optimization in command cycles*/
      /*MISRA2012_RULE_11_2_JUSTIFICATION: The Pointers are type-cast to uint32
      for address comparison/calculation purpose.*/
      /*MISRA2012_RULE_13_2_JUSTIFICATION: The Pointers are type-cast to uint32
       *for address comparison/calculation purpose*/
      /*MISRA2012_RULE_1_3_JUSTIFICATION: The Pointers are type-cast to uint32
       *for address comparison/calculation purpose*/
      /*MISRA2012_RULE_10_8_JUSTIFICATION: The Pointers are type-cast to
       *uint32 for address comparison/calculation purpose*/
      /* MISRA2012_RULE_11_4_JUSTIFICATION: SFR access */
      *((FlsLoader_AddressType*)FLSLOADER_GET_CYCLE_AAA8(StartAddress)) = \
                                                             FLSLOADER_VALUE_A6;
      DSYNC();
      /* Wait till the PROG bit is set */
      InCount = 0U;
      /* MISRA2012_RULE_11_4_JUSTIFICATION: SFR access */
      FlashBusyStat = DMU_HF_OPERATION.B.PROG;

      while ((FlashBusyStat != FLSLOADER_BIT_SET) &&
             (InCount < FLSLOADER_CMDCYCLE_TIMEOUT))
      {
        InCount++;
        /* MISRA2012_RULE_11_4_JUSTIFICATION: SFR access */
        FlashBusyStat = DMU_HF_OPERATION.B.PROG;
#ifdef FLASH_OPERATION_CBK_TRICORE
            pFLASH_OperationCbk();
#endif
      }
      
      if (InCount < FLSLOADER_CMDCYCLE_TIMEOUT)
      {
        /* Check for FLASH BUSY flag */
        /* PnBUSY and D0BUSY */
        InCount = 0U;
        /* MISRA2012_RULE_11_4_JUSTIFICATION: SFR access */
        BusyCheck = (DMU_HF_STATUS.U & (uint32)FLSLOADER_FLASH_BUSY_MASK);

        while ((BusyCheck != 0U) &&
              (InCount < FLSLOADER_BUSY_TIMEOUT ))
        {
          InCount++;
          /* MISRA2012_RULE_11_4_JUSTIFICATION: SFR access */
          BusyCheck = (DMU_HF_STATUS.U & (uint32)FLSLOADER_FLASH_BUSY_MASK);
#ifdef FLASH_OPERATION_CBK_TRICORE
            pFLASH_OperationCbk();
#endif

        }
        /* This check makes sure No protection error and no sequence 
        error and No operation error has occurred.*/
        if (InCount < FLSLOADER_BUSY_TIMEOUT )
        {
          RetError = FlsLoader_lProtSeqOperErrorCheck();
          if(RetError == FLSLOADER_E_OK)
          {
            /* This check makes sure No program verification error */
            RetError = (FlsLoader_ReturnType)FlsLoader_lPverCheck();
          }
        }
        else
        {
          RetError = FLSLOADER_E_NOT_OK;
        }
      }
      else
      {
        RetError = FLSLOADER_E_NOT_OK;
      }
      /* Clear the status if the operation is successful.*/
      /*MISRA2012_RULE_11_6_JUSTIFICATION: FlsLoader_AddressType is defined of
      type volatile uint32 to avoid compiler optimization in command cycles*/
      /*MISRA2012_RULE_11_2_JUSTIFICATION: The Pointers are type-cast to uint32
      for address comparison/calculation purpose.*/
      /*MISRA2012_RULE_13_2_JUSTIFICATION: The Pointers are type-cast to uint32
       *for address comparison/calculation purpose*/
      /*MISRA2012_RULE_1_3_JUSTIFICATION: The Pointers are type-cast to uint32
       *for address comparison/calculation purpose*/
      /*MISRA2012_RULE_10_8_JUSTIFICATION: The Pointers are type-cast to
       *uint32 for address comparison/calculation purpose*/
      /* MISRA2012_RULE_11_4_JUSTIFICATION: SFR access */
      *((FlsLoader_AddressType*)FlsLoader_lClearStatus(StartAddress))
                                  = FLSLOADER_VALUE_FA;

      /* Iterate the TargetAddress to the next page Address */
      /*MISRA2012_RULE_13_2_JUSTIFICATION: TargetAddress is defined of type
      volatile uint32 to avoid compiler optimization in command cycles*/
      /*MISRA2012_RULE_1_3_JUSTIFICATION: TargetAddress is defined of type
      volatile uint32 to avoid compiler optimization in command cycles*/
      /*MISRA2012_RULE_17_8_JUSTIFICATION: The Pointers are type-cast to
       *uint32 for address comparison/calculation purpose*/
      /* MISRA2012_RULE_11_4_JUSTIFICATION: SFR access */
      TargetAddress = TargetAddress + BurstOffSet;
    }
    else
    {
      RetError = FLSLOADER_E_NOT_OK;
    }
    if ((FlashType != FLSLOADER_DFLASH_BANK0))
    {
      FlsLoader_lSetSafetyENDINIT();
    }
  }
  return RetError;
  /*MISRA2012_RULE_8_13_JUSTIFICATION: Accepted deviation in AUTOSAR*/
}

/*CYCLOMATIC_FlsLoader_lPageWrite_JUSTIFICATION: This API perform the command
 * cycle execution where is is necessary to have all these checks
*/
/*******************************************************************************
**FlsLoader_ReturnType FlsLoader_lPageWrite (uint32 LoadPageCount,            **
**                           FlsLoader_AddressType OffSet,                    **
**                           uint32 FlashType,                                **
**                           const uint8 *SourceAddressPtr,                   **
**                           FlsLoader_AddressType TargetAddress,             **
**                           uint32 NoOfPages);                               **
**                                                                            **
** Service ID       :   NA                                                    **
**                                                                            **
** Sync/Async       : Synchronous                                             **
**                                                                            **
** Reentrancy       : reentrant                                               **
**                                                                            **
** Parameters (in)  :  LoadPageCount,                                         **
**                     OffSet,                                                **
**                     FlashType,                                             **
**                     SourceAddressPtr,                                      **
**                     TargetAddress                                          **
**                                                                            **
** Parameters (out) :                                                         **
**                                                                            **
** Return value     : FLSLOADER_E_OK                                          **
**                    FLSLOADER_E_NOT_OK                                      **
**                                                                            **
** Description      :                                                         **
**                                                                            **
**                                                                            **
*******************************************************************************/
LOCAL_INLINE FlsLoader_ReturnType FlsLoader_lPageWrite (
                           uint32 LoadPageCount,
                           FlsLoader_AddressType OffSet,
                           uint32 FlashType,
                           const uint8 *SourceAddressPtr,
                           FlsLoader_AddressType TargetAddress,
                           uint32 NoOfPages)
{
  volatile uint32                FlashBusyStat;
  volatile uint32                BusyCheck;
  uint32                         InCount;
  uint32                         Count;
  FlsLoader_ReturnType           RetError;
  FlsLoader_AddressType          StartAddress;
  FlsLoader_AddressType         *PdataPtr;
  FlsLoader_AddressType         *LoadPageAddress;
  
  
  StartAddress = FLSLOADER_CMD_BASE;
  RetError = FLSLOADER_E_OK;
  /*MISRA2012_RULE_11_8_JUSTIFICATION: "PdataPtr" attempt to cast away
  volatile in terms of pointer access*/
  /*MISRA2012_RULE_11_5_JUSTIFICATION: "PdataPtr" attempt to cast away
  volatile in terms of pointer access*/
  /*MISRA2012_RULE_11_3_JUSTIFICATION: "PdataPtr" attempt to cast away
  volatile in terms of pointer access*/
  PdataPtr = (FlsLoader_AddressType *)(void *)(SourceAddressPtr);

  for (Count = 0U; (Count < NoOfPages) && (RetError == FLSLOADER_E_OK); Count++)
  {
    if (FlashType != FLSLOADER_DFLASH_BANK0)
    {
      FlsLoader_lResetSafetyENDINIT();
    }
    /* Enter the Page Mode */
    /*MISRA2012_RULE_11_6_JUSTIFICATION: FlsLoader_AddressType is defined of
    type volatile uint32 to avoid compiler optimization in command cycles*/
    /*MISRA2012_RULE_11_2_JUSTIFICATION: The Pointers are type-cast to uint32
    for address comparison/calculation purpose.*/
    /*MISRA2012_RULE_13_2_JUSTIFICATION: The Pointers are type-cast to uint32
     *for address comparison/calculation purpose*/
    /*MISRA2012_RULE_1_3_JUSTIFICATION: The Pointers are type-cast to uint32
     *for address comparison/calculation purpose*/
    /*MISRA2012_RULE_10_8_JUSTIFICATION: The Pointers are type-cast to
     *uint32 for address comparison/calculation purpose*/
    /* MISRA2012_RULE_11_4_JUSTIFICATION: SFR access */
    *((FlsLoader_AddressType*)FlsLoader_lEnterPageMode(StartAddress)) = \
                                       FlsLoader_lGetMode(FlashType);
    DSYNC();
    InCount = 0U;
    /*Check if Program Flash is in page mode */
    if (FlashType != FLSLOADER_DFLASH_BANK0)
    {
      /* MISRA2012_RULE_11_4_JUSTIFICATION: SFR access */
      FlashBusyStat = DMU_HF_STATUS.B.PFPAGE;

      while((FlashBusyStat != FLSLOADER_BIT_SET) &&
            (InCount < FLSLOADER_CMDCYCLE_TIMEOUT))
      {
        InCount++;
        /* MISRA2012_RULE_11_4_JUSTIFICATION: SFR access */
        FlashBusyStat = DMU_HF_STATUS.B.PFPAGE;
#ifdef FLASH_OPERATION_CBK_TRICORE
            pFLASH_OperationCbk();
#endif
      }
    }
    else
    {
      /* MISRA2012_RULE_11_4_JUSTIFICATION: SFR access */
      FlashBusyStat = DMU_HF_STATUS.B.DFPAGE;

      while((FlashBusyStat != FLSLOADER_BIT_SET) &&
           (InCount < FLSLOADER_CMDCYCLE_TIMEOUT))
      {
        InCount++;
        /* MISRA2012_RULE_11_4_JUSTIFICATION: SFR access */
        FlashBusyStat = DMU_HF_STATUS.B.DFPAGE;
#ifdef FLASH_OPERATION_CBK_TRICORE
            pFLASH_OperationCbk();
#endif
      }
    }

    /* Check PFPAGE/DFPAGE bit was SET */
    if(InCount < FLSLOADER_CMDCYCLE_TIMEOUT)
    {
      for (InCount=0U; InCount < LoadPageCount; InCount++)
      {
        /* Load the data */
      /*MISRA2012_RULE_11_6_JUSTIFICATION: FlsLoader_AddressType is defined of
      type volatile uint32 to avoid compiler optimization in command cycles*/
      /*MISRA2012_RULE_11_2_JUSTIFICATION: The Pointers are type-cast to uint32
      for address comparison/calculation purpose.*/
      /*MISRA2012_RULE_13_2_JUSTIFICATION: The Pointers are type-cast to uint32
       *for address comparison/calculation purpose*/
      /*MISRA2012_RULE_1_3_JUSTIFICATION: The Pointers are type-cast to uint32
       *for address comparison/calculation purpose*/
      /*MISRA2012_RULE_10_8_JUSTIFICATION: The Pointers are type-cast to
       *uint32 for address comparison/calculation purpose*/
        /* MISRA2012_RULE_11_4_JUSTIFICATION: SFR access */
        LoadPageAddress = \
                (FlsLoader_AddressType *)FlsLoader_lLoadPage(StartAddress);

        *LoadPageAddress = *PdataPtr;
        /*MISRA2012_RULE_18_4_JUSTIFICATION: Pointer arithmetic used to load
        data into address and is within allowed range*/
        *(LoadPageAddress + 1U) = *(PdataPtr + 1U);
        /*MISRA2012_RULE_18_4_JUSTIFICATION: Pointer arithmetic used to load
        data into address and is within allowed range*/
        PdataPtr += FLSLOADER_NUM_2;
        /* Load Page register gets incremented automatically. */
      }
      /* cycle 1 */
      /*MISRA2012_RULE_11_6_JUSTIFICATION: FlsLoader_AddressType is defined of
      type volatile uint32 to avoid compiler optimization in command cycles*/
      /*MISRA2012_RULE_11_2_JUSTIFICATION: The Pointers are type-cast to uint32
      for address comparison/calculation purpose.*/
      /*MISRA2012_RULE_13_2_JUSTIFICATION: The Pointers are type-cast to uint32
       *for address comparison/calculation purpose*/
      /*MISRA2012_RULE_1_3_JUSTIFICATION: The Pointers are type-cast to uint32
       *for address comparison/calculation purpose*/
      /*MISRA2012_RULE_10_8_JUSTIFICATION: The Pointers are type-cast to
       *uint32 for address comparison/calculation purpose*/
      /* MISRA2012_RULE_11_4_JUSTIFICATION: SFR access */
      *((FlsLoader_AddressType*)FLSLOADER_GET_CYCLE_AA50(StartAddress)) = \
                                                                  TargetAddress;
      /* cycle 2 */
      /*MISRA2012_RULE_11_6_JUSTIFICATION: FlsLoader_AddressType is defined of
      type volatile uint32 to avoid compiler optimization in command cycles*/
      /*MISRA2012_RULE_11_2_JUSTIFICATION: The Pointers are type-cast to uint32
      for address comparison/calculation purpose.*/
      /*MISRA2012_RULE_13_2_JUSTIFICATION: The Pointers are type-cast to uint32
       *for address comparison/calculation purpose*/
      /*MISRA2012_RULE_1_3_JUSTIFICATION: The Pointers are type-cast to uint32
       *for address comparison/calculation purpose*/
      /*MISRA2012_RULE_10_8_JUSTIFICATION: The Pointers are type-cast to
       *uint32 for address comparison/calculation purpose*/
      /* MISRA2012_RULE_11_4_JUSTIFICATION: SFR access */
      *((FlsLoader_AddressType*)FLSLOADER_GET_CYCLE_AA58(StartAddress))= \
                                                             FLSLOADER_VALUE_00;
      /* cycle 3 */
      /*MISRA2012_RULE_11_6_JUSTIFICATION: FlsLoader_AddressType is defined of
      type volatile uint32 to avoid compiler optimization in command cycles*/
      /*MISRA2012_RULE_11_2_JUSTIFICATION: The Pointers are type-cast to uint32
      for address comparison/calculation purpose.*/
      /*MISRA2012_RULE_13_2_JUSTIFICATION: The Pointers are type-cast to uint32
       *for address comparison/calculation purpose*/
      /*MISRA2012_RULE_1_3_JUSTIFICATION: The Pointers are type-cast to uint32
       *for address comparison/calculation purpose*/
      /*MISRA2012_RULE_10_8_JUSTIFICATION: The Pointers are type-cast to
       *uint32 for address comparison/calculation purpose*/
      /* MISRA2012_RULE_11_4_JUSTIFICATION: SFR access */
      *((FlsLoader_AddressType*)FLSLOADER_GET_CYCLE_AAA8(StartAddress))= \
                                                             FLSLOADER_VALUE_A0;
      /*cycle 4 */
      /*MISRA2012_RULE_11_6_JUSTIFICATION: FlsLoader_AddressType is defined of
      type volatile uint32 to avoid compiler optimization in command cycles*/
      /*MISRA2012_RULE_11_2_JUSTIFICATION: The Pointers are type-cast to uint32
      for address comparison/calculation purpose.*/
      /*MISRA2012_RULE_13_2_JUSTIFICATION: The Pointers are type-cast to uint32
       *for address comparison/calculation purpose*/
      /*MISRA2012_RULE_1_3_JUSTIFICATION: The Pointers are type-cast to uint32
       *for address comparison/calculation purpose*/
      /*MISRA2012_RULE_10_8_JUSTIFICATION: The Pointers are type-cast to
       *uint32 for address comparison/calculation purpose*/
      /* MISRA2012_RULE_11_4_JUSTIFICATION: SFR access */
      *((FlsLoader_AddressType*)FLSLOADER_GET_CYCLE_AAA8(StartAddress))= \
                                                             FLSLOADER_VALUE_AA;
      DSYNC();
      /* Wait till the PROG bit is set */
      InCount = 0U;
      /* MISRA2012_RULE_11_4_JUSTIFICATION: SFR access */
      FlashBusyStat = DMU_HF_OPERATION.B.PROG;

      while((FlashBusyStat != FLSLOADER_BIT_SET) &&
            (InCount < FLSLOADER_CMDCYCLE_TIMEOUT))
      {
        InCount++;
        /* MISRA2012_RULE_11_4_JUSTIFICATION: SFR access */
        FlashBusyStat = DMU_HF_OPERATION.B.PROG;
#ifdef FLASH_OPERATION_CBK_TRICORE
            pFLASH_OperationCbk();
#endif
      }
      if (InCount < FLSLOADER_CMDCYCLE_TIMEOUT)
      {
        /* Check for FLASH BUSY flag */
        /* PnBUSY and D0BUSY */
        InCount = 0U;
        /* MISRA2012_RULE_11_4_JUSTIFICATION: SFR access */
        BusyCheck = (DMU_HF_STATUS.U & (uint32)FLSLOADER_FLASH_BUSY_MASK);

        while((BusyCheck != 0U) && 
              (InCount < FLSLOADER_BUSY_TIMEOUT))
        {
          InCount++;
          /* MISRA2012_RULE_11_4_JUSTIFICATION: SFR access */
          BusyCheck = (DMU_HF_STATUS.U & (uint32)FLSLOADER_FLASH_BUSY_MASK);
#ifdef FLASH_OPERATION_CBK_TRICORE
            pFLASH_OperationCbk();
#endif

        }

        if (InCount < FLSLOADER_BUSY_TIMEOUT )
        {
          /* This check makes sure No protection error and no 
          sequence error and No operation error has occurred.*/
          RetError = FlsLoader_lProtSeqOperErrorCheck();
          if(RetError == (FlsLoader_ReturnType)FLSLOADER_E_OK)
          {
            /* This check makes sure No program verification error */
            RetError = (FlsLoader_ReturnType)FlsLoader_lPverCheck();
          }
        }
        else
        {
          RetError = FLSLOADER_E_NOT_OK;
        }
      }
      else
      {
        RetError = FLSLOADER_E_NOT_OK;
      }
      /* Clear the status if the operation is successful.*/
      /*MISRA2012_RULE_11_6_JUSTIFICATION: FlsLoader_AddressType is defined of
      type volatile uint32 to avoid compiler optimization in command cycles*/
      /*MISRA2012_RULE_11_2_JUSTIFICATION: The Pointers are type-cast to uint32
      for address comparison/calculation purpose.*/
      /*MISRA2012_RULE_13_2_JUSTIFICATION: The Pointers are type-cast to uint32
       *for address comparison/calculation purpose*/
      /*MISRA2012_RULE_1_3_JUSTIFICATION: The Pointers are type-cast to uint32
       *for address comparison/calculation purpose*/
      /*MISRA2012_RULE_10_8_JUSTIFICATION: The Pointers are type-cast to
       *uint32 for address comparison/calculation purpose*/
      /* MISRA2012_RULE_11_4_JUSTIFICATION: SFR access */
      *((FlsLoader_AddressType*)FlsLoader_lClearStatus(StartAddress))= \
                                                             FLSLOADER_VALUE_FA;

      /*Iterate the TargetAddress to the next page Address */
      /*MISRA2012_RULE_13_2_JUSTIFICATION: TargetAddress is defined of type
      volatile uint32 to avoid compiler optimization in command cycles*/
      /*MISRA2012_RULE_1_3_JUSTIFICATION: TargetAddress is defined of type
      volatile uint32 to avoid compiler optimization in command cycles*/
      /*MISRA2012_RULE_17_8_JUSTIFICATION: TargetAddress is defined of type
      volatile uint32 to avoid compiler optimization in command cycles*/
      TargetAddress = TargetAddress + OffSet;
    }
    else
    {
      RetError = FLSLOADER_E_NOT_OK;
    }
    if ((FlashType != FLSLOADER_DFLASH_BANK0))
    {
      FlsLoader_lSetSafetyENDINIT();
    }
  }
  return RetError;
  /*MISRA2012_RULE_8_13_JUSTIFICATION: Accepted deviation in AUTOSAR*/
}
#define FLSLOADER_STOP_SEC_WRITE_CODE
/* MISRA2012_RULE_4_10_JUSTIFICATION: Flsloader_Memmap.h is repeatedly included
 * without include guard. This is as per AUTOSAR */
/* MISRA2012_RULE_20_1_JUSTIFICATION: declaration of 'FlsLoader_Status' before
 * #include memap.h - Accepted deviation in AUTOSAR */
#include "MemMap.h"
#define FLSLOADER_START_SEC_CODE
/* MISRA2012_RULE_4_10_JUSTIFICATION: Flsloader_Memmap.h is repeatedly included
 * without include guard. This is as per AUTOSAR */
/* MISRA2012_RULE_20_1_JUSTIFICATION: declaration of 'FlsLoader_Status' before
 * #include memap.h - Accepted deviation in AUTOSAR */
#include "MemMap.h"
/*******************************************************************************
**                                                                            **
** Syntax : void FlsLoader_GetVersionInfo ( Std_VersionInfoType               **
**                                        * VersionInfoPtr)                   **
**                                                                            **
** Description : Service to get DMA driver version                            **
** [/cover]                                                                   **
**                                                                            **
** Service ID:  0x07                                                          **
**                                                                            **
** Sync/Async:  Synchronous                                                   **
**                                                                            **
** Reentrancy:  Reentrant                                                     **
**                                                                            **
** Parameters (in) :  None                                                    **
**                                                                            **
** Parameters (out):  VersionInfoPtr -  Pointer to store version ID by driver **
**                                                                            **
** Return value    :  None                                                    **
**                                                                            **
*******************************************************************************/
void FlsLoader_GetVersionInfo( Std_VersionInfoType * VersionInfoPtr)
{
    if(VersionInfoPtr == NULL_PTR)
    {
    #if ( FLSLOADER_DEV_ERROR_DETECT == STD_ON )
        /*Report DET on DriverState error*/
        Det_ReportError(FLSLOADER_MODULE_ID,
                        FLSLOADER_INSTANCE_ID,
                        FLSLOADER_SID_GETVERSIONINFO,
                        FLSLOADER_E_PARAM_POINTER);
    #endif
    }
    else
    {
        VersionInfoPtr->moduleID         = FLSLOADER_MODULE_ID;
        VersionInfoPtr->sw_major_version = FLSLOADER_SW_MAJOR_VERSION;
        VersionInfoPtr->sw_minor_version = FLSLOADER_SW_MINOR_VERSION;
        VersionInfoPtr->sw_patch_version = FLSLOADER_SW_PATCH_VERSION;
        VersionInfoPtr->vendorID         = FLSLOADER_VENDOR_ID;
    }
}
#define FLSLOADER_STOP_SEC_CODE
/* MISRA2012_RULE_4_10_JUSTIFICATION: Flsloader_Memmap.h is repeatedly included
 * without include guard. This is as per AUTOSAR */
/* MISRA2012_RULE_20_1_JUSTIFICATION: declaration of 'FlsLoader_Status' before
 * #include memap.h - Accepted deviation in AUTOSAR */
#include "MemMap.h"
/* Deviation MISRA-1 MISRA-2 MISRA-3 MISRA-4 MISRA-5 MISRA-6 MISRA-7 MISRA-8 MISRA-9 MISRA-10 MISRA-11 <STOP> */
/* CHECK: RULE 203 ON */
/* CHECK: RULE 404 ON */
/* CHECK: RULE 205 ON */
/* CHECK: RULE 506 ON */
/* CHECK: RULE 306 ON */
/* CHECK: PARSE */
