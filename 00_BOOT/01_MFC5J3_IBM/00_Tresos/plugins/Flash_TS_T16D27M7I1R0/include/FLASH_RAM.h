/* CHECK: RULE 502 OFF */
/* CHECK: RULE 506 OFF */
#ifndef FLASH_RAM_H
#define FLASH_RAM_H

/*===============================================================================*/
/*                                                                               */
/*                               FLASH layers                                    */
/*                                                                               */
/* ------------------------------------------------------------------------------*/
/*                                                                               */
/*                              FLASH  configuration                             */
/*                                                                               */
/*===============================================================================*/
/*%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%                                        */
/*%%   _____________________________   %%  \file FLASH_RAM.h                    */
/*%%  |                             |  %%  \brief FLASH layer implementation     */
/*%%  |   &&&&&   &&&&&             |  %%  Module version: 7.1.6                 */
/*%%  |   &       &    &            |  %%  Variant: OsekCore                  */
/*%%  |   &&&&    &&&&&             |  %%                                        */
/*%%  |   &       &    &            |  %%                                        */
/*%%  |   &&&&&   &&&&&             |  %%                                        */
/*%%  |_____________________________|  %%                                        */
/*%%                                   %%                                        */
/*%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%                                        */
/*===============================================================================*/
/* Copyright 2017 by Elektrobit Automotive GmbH                                  */
/* All rights exclusively reserved for Elektrobit Automotive GmbH,               */
/* unless expressly agreed to otherwise.                                         */
/*===============================================================================*/

/*============================= PUBLIC DEFINITIONS ==============================*/
/*                                                                               */
/*-------------------------------------------------------------------------------*/
typedef void (*PFLASH_OPERATIONCBK) (void);
typedef tFlashStatus (*pFLASHLLDERASEPROCESS) (u16 ulSectorNo);
typedef tFlashStatus (*pFLASHLLDPROGRAMBUFFER) (tFlashAddress uAddr,u16 uwLen,const u8 FLASH_FAR_POINTER aubData);
typedef FlsLoader_ReturnType (*tpfuWrite)(FlsLoader_AddressType TargetAddress,FlsLoader_LengthType Length,const uint8 *SourceAddressPtr);
typedef FlsLoader_ReturnType (*tpfuErase)(FlsLoader_AddressType TargetAddress,FlsLoader_LengthType Length );

extern tpfuWrite tWrite_fptr;
extern tpfuErase tErase_fptr;
extern PFLASH_OPERATIONCBK pFLASH_OperationCbk;

#define FLSLOADER_START_SEC_WRITE_CODE
#include "MemMap.h"

/** \brief Erase one of flash memory
 **
 ** This function allows to erase one or several sectors of the flash memory, starting from the address
 ** specified in input parameter.
 **
 ** \param[in] ulSectorNo Block number to be erased
 **
 ** \return Result of operation
 ** \retval FLASH_ACCESS_ERROR An error occurred during erasing operations.
 ** \retval FLASH_NO_ERROR     No problem, the sector have been correctly erased
 **
 **
 **/
extern tFlashStatus FLASH_RAM_EraseRoutine(u16 ulSectorNo);

/** \brief Write buffer of data to flash memory
 **
 ** This function allows to write a buffer of data in flash memory at the address
 ** specified in input parameter
 **
 ** \param[in] uAddr Memory address where the data shall be written
 ** \param[in] uwLen Length of the data to be written
 ** \param[in] aubData Buffer of data to be written
 **
 ** \return Result of operation
 ** \retval FLASH_ACCESS_ERROR An error occurred during writing operations. The data have not been written correctly.
 ** \retval FLASH_NO_ERROR     No problem, the data have been written correctly
 **
 **
 **/
extern tFlashStatus FLASH_RAM_WriteRoutine(tFlashAddress uAddr,u16 uwLen,const u8 FLASH_FAR_POINTER aubData);

#define FLSLOADER_STOP_SEC_WRITE_CODE
#include "MemMap.h"




/*-------------------------------------------------------------------------------*/

/* - Public Callback Prototypes                                                  */

/*                                                                               */
/*===============================================================================*/

#endif      /* FLASH_RAM_H */
/* CHECK: RULE 502 ON */
/* CHECK: RULE 506 ON */
