/* CHECK: RULE 502 OFF */
/* CHECK: RULE 203 OFF */
/* CHECK: RULE 505 OFF */
/* CHECK: RULE 205 OFF */
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
**  FILENAME     : FlsLoader.h                                                **
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
**  DESCRIPTION  : Flsloader Driver header definition file                    **
**                                                                            **
**  SPECIFICATION(S) : NA                                                     **
**                                                                            **
**  MAY BE CHANGED BY USER : no                                               **
**                                                                            **
*******************************************************************************/

#ifndef FLSLOADER_H
#define FLSLOADER_H

/*******************************************************************************
**                      Includes                                              **
*******************************************************************************/
/* Inclusion of Platform_Types.h and Compiler.h */
#include "Std_Types.h"
#include "Mcal_Compiler.h"
#include "McalLib.h"
#include "board.h"

/* Pre-compile/static configuration parameters for FLASHLOADER */
#include "FlsLoader_Cfg.h"

/* Conditional Inclusion of Developement Error Tracer File */
#if  ( FLSLOADER_DEV_ERROR_DETECT == STD_ON )
#include "Det.h"
#endif
/*******************************************************************************
**                      Global Macro Definitions                              **
*******************************************************************************/

/*
   Published parameters
*/

/* FLSLOADER Vendor ID */
#define FLSLOADER_VENDOR_ID              ((uint16)17U)

/* FLSLOADER module id 255 -> 0xFF */
#define FLSLOADER_MODULE_ID              ((uint16)255U)

/*If there is no error  */
#define FLSLOADER_E_OK              ((FlsLoader_ReturnType)0x0)
/*If there is error */
#define FLSLOADER_E_NOT_OK          ((FlsLoader_ReturnType)0x1)
/* If locked segment */
#define FLSLOADER_E_LOCKED          ((FlsLoader_ReturnType)0x2)

/*If the memory is installed with OTP */
#define FLSLOADER_E_ROMVERSION      ((FlsLoader_ReturnType)0x3)

/*If the device is busy */
#define FLSLOADER_E_BUSY            ((FlsLoader_ReturnType)0x5)

/*
   FLASH LOADER Development error codes
*/
#if (FLSLOADER_DEV_ERROR_DETECT == STD_ON)

/*If Invalid Parameter   */
#define FLSLOADER_E_PARAM_IGNORED   ((uint8)0x0)
/*If the Value is incorrect */
#define FLSLOADER_E_UNLOCKED        ((uint8)0x1)
/*If the Size is incorrect */
#define FLSLOADER_E_PARAM_LENGTH    ((uint8)0x2)
/*If the Position is incorrect */
#define FLSLOADER_E_PARAM_ADDRESS   ((uint8)0x3)
/*If the Channel is not initialised */
#define FLSLOADER_E_UNINIT          ((uint8)0x4)
/*If the Channel is not initialised */
#define FLSLOADER_E_PARAM_POINTER   ((uint8)0x6)

/*
   API Service ID's
*/
/* API Service ID for FlsLoader_Init() */
#define FLSLOADER_SID_INIT           ((uint8)0x0)
/* API Service ID for FlsLoader_DeInit() */
#define FLSLOADER_SID_DEINIT         ((uint8)0x1)
/* API Service ID for FlsLoader_WriteSync() */
#define FLSLOADER_SID_WRITE         ((uint8)0x2)
/* API Service ID for FlsLoader_EraseSync() */
#define FLSLOADER_SID_ERASE         ((uint8)0x3)
/* API Service ID for FlsLoader_Lock() */
#define FLSLOADER_SID_LOCK          ((uint8)0x4)
/* API Service ID for FlsLoader_Unlock() */
#define FLSLOADER_SID_UNLOCK        ((uint8)0x5)
/* API Service ID for FlsLoader_SuspendSync() */
#define FLSLOADER_SID_SUSPEND       ((uint8)0x6)
/* API Service ID for FlsLoader_GetVersionInfo() */
#define FLSLOADER_SID_GETVERSIONINFO ((uint8)0x7)

#endif  /*(FLSLOADER_DEV_ERROR_DETECT == STD_ON) */

/* The flash sizes */
#define FLSLOADER_SIZE_16K          ((0x00004000U))
#define FLSLOADER_SIZE_64K          ((0x00010000U))
#define FLSLOADER_SIZE_128K         ((0x00020000U))

/* To differentiate between PFLASH and DFLASH the following value is written
in the command cycle. */
#define FLSLOADER_PFLASH_VAL            ((FlsLoader_AddressType)(0x00000050U))
#define FLSLOADER_DFLASH_VAL            ((FlsLoader_AddressType)(0x0000005DU))
/* Suspend Feature is not supported by the hardware */
#define FLSLOADER_SUSPEND_API           (STD_OFF)

/*******************************************************************************
**                      Private Macro like functions                          **
*******************************************************************************/

/*******************************************************************************
**                      Global Type Definitions                               **
*******************************************************************************/
/*
Type: FlsLoader_ValueType
Specifies the values for Mode and Password
*/
typedef uint32 FlsLoader_ValueType;

/*
Type: FlsLoader_AddressType
This specifies the starting address of a sector of Flash
or starting address of a page
*/
typedef uint32 volatile FlsLoader_AddressType;

/*
Type: FlsLoader_LengthType
This specifies the Length/size to programme /erase
*/
typedef uint32 FlsLoader_LengthType;

/*
Type: FlsLoader_ReturnType
This specifies the various Return types that can be specified by the APIs
*/
typedef uint32 FlsLoader_ReturnType;

/*
Type: FlsLoader_Configtype
*/
typedef void FlsLoader_ConfigType;
#if (FLSLOADER_CALLOUT_FUNC == STD_ON)
extern void FlsLoader_LoopCallOut(void);
#endif

/*******************************************************************************
**                      Global Constant Declarations                          **
*******************************************************************************/

/*******************************************************************************
**                      Global Variable Declarations                          **
*******************************************************************************/
#define FLSLOADER_START_SEC_CODE
/* MISRA2012_RULE_4_10_JUSTIFICATION: Flsloader_Memmap.h is repeatedly included
 * without include guard. This is as per AUTOSAR */
#include "MemMap.h"
/*******************************************************************************
**                      Global Function Declarations                          **
*******************************************************************************/
/*******************************************************************************
** Syntax : void FlsLoader_GetVersionInfo(                                    **
**                                      Std_VersionInfoType *VersioninfoPtr ) **
**                                                                            **
** Service ID:      7                                                         **
**                                                                            **
** Sync/Async:      Synchronous                                               **
**                                                                            **
** Reentrancy:      non reentrant                                             **
**                                                                            **
** Parameters (in): none
**                                                                            **
** Parameters (out):VersioninfoPtr : Pointer to where to store the version    **
**                                   information of this module.              **
**                                                                            **
** Return value:    none                                                      **
**                                                                            **
** Description :    This service returns the version information of           **
**                  this module.                                              **
**                  The version information includes:                         **
**                  Module Id,Vendor Id , Vendor specific version numbers     **
**                                                                            **
*******************************************************************************/
extern void  FlsLoader_GetVersionInfo(Std_VersionInfoType * VersionInfoPtr);

/*******************************************************************************
** Syntax           :  FlsLoader_ReturnType FlsLoader_Init                    **
**                    (                                                       **
**                      const FlsLoader_ConfigType* Address                   **
**                    )                                                       **
**                                                                            **
** Service ID       : 0x00                                                    **
**                                                                            **
** Sync/Async       : Synchronous                                             **
**                                                                            **
** Reentrancy       : non - reentrant                                         **
**                                                                            **
** Parameters(in)   : address :NULL Expected                                  **
**                                                                            **
** Parameters (out) : none                                                    **
**                                                                            **
** Return value     : FlsLoader_ReturnType:(If DET is not enabled)            **
**                    1.FLSLOADER_E_OK                                        **
**                    2.FLSLOADER_E_ROMVERSION                                **
**                    (If DET is enabled and an error has occured)            **
**                    1.FLSLOADER_E_NOT_OK                                    **
**                                                                            **
** Description      : This function initilizes the flash module and checks    **
**                    if all the flash sectors is configured as ROM           **
**                    (protected under user2)                                 **
**                                                                            **
*******************************************************************************/
extern FlsLoader_ReturnType FlsLoader_Init(const FlsLoader_ConfigType* Address);


/* Enable / Disable the use of the function */
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
**                    (If DET is enabled and an error has occured)            **
**                    1. FLSLOADER_E_NOT_OK                                   **
**                    2. FLSLOADER_E_BUSY                                     **
**                                                                            **
** Description      : This function deinitilizes the flash module.            **
**                    This Function sets the registers to their default       **
**                    state and executes the reset to read command.           **
**                                                                            **
*******************************************************************************/

extern  FlsLoader_ReturnType FlsLoader_DeInit(void);

#else

#define FlsLoader_DeInit() \
ERROR_FlsLoader_DeInit_NOT_SELECTED

#endif /* (FLSLOADER_DEINIT_API == STD_ON) */

#define FLSLOADER_STOP_SEC_CODE
/* MISRA2012_RULE_4_10_JUSTIFICATION: Flsloader_Memmap.h is repeatedly included
 * without include guard. This is as per AUTOSAR */
#include "MemMap.h"

#define FLSLOADER_START_SEC_WRITE_CODE
/* MISRA2012_RULE_4_10_JUSTIFICATION: Flsloader_Memmap.h is repeatedly included
 * without include guard. This is as per AUTOSAR */
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
extern FlsLoader_ReturnType FlsLoader_Write(
                                     FlsLoader_AddressType TargetAddress,
                                     FlsLoader_LengthType Length,
                                     const uint8 *SourceAddressPtr);

/*******************************************************************************
** Syntax           :  FlsLoader_ReturnType FlsLoader_Erase                   **
**                    (                                                       **
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
** Parameters(in)   : Length -Number of Sectors                               **
**                    TargetAddress
                    - specifies the appropriate starting address of the sector**
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
** Description      : This function erases the sector of the internal flash   **
**                    in PFLASH and DFLASH                                    **
**                    The completion of this operation is denoted by clearing **
**                    of busy status flag or suspend operation or Error       **
**                    FLSLOADER_E_LOCKED is returned if a call is made to     **
**                    a protected sector                                      **
*******************************************************************************/
extern  FlsLoader_ReturnType FlsLoader_Erase(
                                     FlsLoader_AddressType TargetAddress,
                                     FlsLoader_LengthType Length
                                             );
extern void FlsLoader_lEraseComSeq(FlsLoader_AddressType TargetAddress,
                                     FlsLoader_LengthType Length );
#define FLSLOADER_STOP_SEC_WRITE_CODE
/* MISRA2012_RULE_4_10_JUSTIFICATION: Flsloader_Memmap.h is repeatedly included
 * without include guard. This is as per AUTOSAR */
#include "MemMap.h"

#define FLSLOADER_START_SEC_WRITE_CODE
/* MISRA2012_RULE_4_10_JUSTIFICATION: Flsloader_Memmap.h is repeatedly included
 * without include guard. This is as per AUTOSAR */
#include "MemMap.h"
/* Enable / Disable the use of the function */
#if (FLSLOADER_LOCK_UNLOCK_API == STD_ON)
/*******************************************************************************
** Syntax           :  FlsLoader_ReturnType FlsLoader_Lock                    **
**                    (                                                       **
                          FlsLoader_AddressType TargetAddress,
                          FlsLoader_LengthType Length
                        );
**                                                                            **
** Service ID       : 0x04                                                    **
**                                                                            **
** Sync/Async       : Synchronous                                             **
**                                                                            **
** Reentrancy       : non - reentrant                                         **
**                                                                            **
** Parameters(in)   : FlsLoader_AddressType TargetAddress                     **
**                    FlsLoader_LengthType Length                             **
**                                                                            **
** Parameters (out) : none                                                    **
**                                                                            **
** Return value     :  FlsLoader_ReturnType:(DET is not enabled)              **
**                     1.FLSLOADER_E_OK                                       **
**                     2.FLSLOADER_E_BUSY                                     **
**                     3.FLSLOADER_E_LOCKED                                   **
**                     (DET is enabled and an error has occured )             **
**                     1.FLSLOADER_E_NOT_OK for all errors but for busy.      **
**                       For busy state FLSLOADER_E_BUSY is returned          **
**                                                                            **
** Description      : This function is used to  lock(protect) the internal    **
**                    Flash of the microcontroller.The function LOCKSYNC is   **
**                    repeatedly called if more than one user level is        **
**                    configured.Possible user levels are User0,User1 and     **
**                    User2.User Level 2 is meant for One Time Programming    **
**                    If any sector is previously locked and the user         **
**                    desires to change the locking sectors,unlock command is **
**                    required.                                               **
**                    No valid parameters are expected here.                  **
**                    The User0 and User1 sectors can be programmed only four **
**                    times in its lifecycle.                                 **
**                    This API cannot be suspended                            **
*******************************************************************************/
extern FlsLoader_ReturnType FlsLoader_Lock(void);

#else
#define FlsLoader_Lock() ERROR_FlsLoader_Lock_NOT_SELECTED

#endif

/* Enable / Disable the use of the function */
#if (FLSLOADER_LOCK_UNLOCK_API == STD_ON)
/*******************************************************************************
** Syntax           :  FlsLoader_ReturnType FlsLoader_UnLock                  **
**                    (                                                       **
**                        FlsLoader_AddressType TargetAddress,                **
**                        FlsLoader_ValueType* Password                       **
**                    )                                                       **
**                                                                            **
** Service ID       : 0x05                                                    **
**                                                                            **
** Sync/Async       : Synchronous                                             **
**                                                                            **
** Reentrancy       : non - reentrant                                         **
**                                                                            **
** Parameters(in)   : Mode :Mode for which the flash should be unlocked       **
**                    Password :Password for User0 or User1                   **
**                    Size :Null expected                                     **
**                    Position:Null Expected                                  **
**                                                                            **
** Parameters (out) : none                                                    **
**                                                                            **
** Return value     : FlsLoader_ReturnType:(DET is not enabled)               **
                      1.FLSLOADER_E_OK                                        **
                      2.FLSLOADER_E_BUSY                                      **
                      4.FLSLOADER_E_NOT_OK for all errors but for busy.       **
                         For busy state FLSLOADER_E_BUSY is returned          **
**                                                                            **
** Description      : This function is used to  unlock(protect) the protection
                      in                                PFLASH and DFLASH     **
                      protection.                                             **
**                    A wrong password will result in Protection Error        **
**                    This API needs to be called twice if the user needs to  **
**                    unlock both PFLASH and DFLASH protection                **
**                    This API cannot be suspended                            **
******************************************************************************/
extern FlsLoader_ReturnType FlsLoader_UnLock(
                                          FlsLoader_AddressType TargetAddress,
                                          FlsLoader_ValueType* Password);

#else
#define FlsLoader_UnLock(TargetAddress,Password) \
                             ERROR_FlsLoader_UnLock_NOT_SELECTED

#endif

#if (FLSLOADER_SUSPEND_API == STD_ON)
/*******************************************************************************
** Syntax           :  FlsLoader_ReturnType FlsLoader_Suspend                 **
**                    (                                                       **
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
** Return value     : FlsLoader_ReturnType:(DET is not enabled)               **
**                    FLSLOADER_E_OK                                          **
**                    (DET is enabled and an error has occured)               **
**                    FLSLOADER_E_NOT_OK                                      **
**                                                                            **
** Description      : This function is used to  suspend flash write or        **
                      erase operation.                                        **
*******************************************************************************/
extern FlsLoader_ReturnType FlsLoader_Suspend(void);
#endif /*(FLSLOADER_SUSPEND_API == STD_ON)*/

#define FLSLOADER_STOP_SEC_WRITE_CODE
/* MISRA2012_RULE_4_10_JUSTIFICATION: Flsloader_Memmap.h is repeatedly included
 * without include guard. This is as per AUTOSAR */
#include "MemMap.h"

#endif
   /* #ifndef FLSLOADER_H */
/* CHECK: RULE 502 ON */
/* CHECK: RULE 203 ON */
/* CHECK: RULE 505 ON */
/* CHECK: RULE 205 ON */
