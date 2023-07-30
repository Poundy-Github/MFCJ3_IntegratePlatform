/* CHECK: RULE 502 OFF */
/* CHECK: RULE 501 OFF */
/* CHECK: RULE 506 OFF */
/* CHECK: RULE 902 OFF */
/* CHECK: RULE 205 OFF */
#ifndef FLASH_LLD_H
#define FLASH_LLD_H


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
/*%%   _____________________________   %%  \file FLASH_LLD_.h                    */
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

/*  MISRA-C:2004 Deviation List
 *
 *  MISRA-1) Deviated Rule: 8.9 (required)
 *   "An identifier with external linkage shall have exactly one external definition."
 *
 *   Reason:
 *    Linker label declarations for RAM copy, defined in Map.
 *
 *  MISRA-2) Deviated Rule: 8.12 (required)
 *   "When an array is declared with external linkage, its size shall be stated explicitly
 *    or defined implicitly by initialization."
 *
 *   Reason:
 *    Linker label declarations for RAM copy, defined in Map.
 *
 *
 */

/*============================= PUBLIC DEFINITIONS ==============================*/
/*                                                                               */
/*-------------------------------------------------------------------------------*/
/* - Public Types                                                                */
/** \brief Flash type */
typedef u8 tFlashType;

/*-------------------------------------------------------------------------------*/
/* - Public Variables                                                            */

/*-------------------------------------------------------------------------------*/
/* - Public Function Prototypes                                                  */
/** \brief Write buffer of data to flash memory
 **
 ** This function allows to write a buffer of data in flash memory at the address
 ** specified in input parameter
 **
 ** \param[in] uAddr Memory address where the data shall be written
 ** \param[in] ulLen Length of the data to be written
 ** \param[in] aubData Buffer of data to be written
 **
 ** \return Result of operation
 ** \retval FLASH_LLD_ACCESS_ERROR An error occurred during writing operations. The data have not been written correctly.
 ** \retval FLASH_LLD_NO_ERROR     No problem, the data have been written correctly
 ** \retval FLASH_PROT_ERROR       Data cannot be written because address is located in a protected memory area
 **
 **
 **/
extern tFlashStatus FLASH_LLD_WriteBuffer(tFlashAddress uAddr,u32 ulLen,const u8 FLASH_FAR_POINTER aubData);

/** \brief Erase sector of flash memory
 **
 ** This function allows to erase the sector of the flash memory, corresponding to the address
 ** specified in input parameter
 **
 ** \param[in] ulSectorNo Sector to be erased
 **
 ** \return Result of operation
 ** \retval FLASH_LLD_ACCESS_ERROR An error occurred during erasing operations. The data have not been written correctly.
 ** \retval FLASH_LLD_NO_ERROR     No problem, the sector have been correctly erased
 ** \retval FLASH_PROT_ERROR       Data cannot be erased because address is located in a protected memory area
 **
 **/
extern tFlashStatus FLASH_LLD_EraseSector(u16 ulSectorNo);

/** \brief Erase one or several sectors of flash memory
 **
 ** This function allows to erase one or several sectors of the flash memory, starting from the address
 ** specified in input parameter.
 **
 ** \param[in] uAddr Memory address of the first sector to be erased
 ** \param[in] ulStartBlockNo First block to be erased
 ** \param[in] ulEndBlockNo Last block to be erased
 **
 ** \return Result of operation
 ** \retval FLASH_LLD_ACCESS_ERROR An error occurred during erasing operations. The data have not been written correctly.
 ** \retval FLASH_LLD_NO_ERROR     No problem, the sector(s) have been correctly erased
 ** \retval FLASH_PROT_ERROR       Data cannot be erased because address is located in a protected memory area
 **
 **
 **/
extern tFlashStatus FLASH_LLD_Erase(tFlashAddress uAddr, u16 ulStartBlockNo, u16 ulEndBlockNo);


/** \brief Initialize layer
 **
 ** This function initializes the FLASH layer, shall be called only once at ECU startup
 **
 **/
extern void FLASH_LLD_Init(void);


/** \brief Get the Flash memory type
 **
 **  this function is used to get the Flash memory type (PFLASH or DFLASH)
 **
 ** \param[in] uAddr Memory address
 ** \param[in] ubFlashFactor Value used to calculate the page size according the Flash type
 **
 ** \return Status of the ongoing operation
 **
 **/
extern tFlashStatus FLASH_LLD_GetFlashType(const tFlashAddress* uAddr, u8* ubFlashFactor);

/** \brief Convert non cashed memory address to cash memory address
  **
  **  this function is used to convert the non cashed address provided in parameter to cashed address
  **
  ** \param[in] uAddr non cashed memory address to be converted
  **
  ** \return Status of the ongoing operation
  **
  **/
extern tFlashStatus FLASH_LLD_GetCashedAddress(tFlashAddress* uAddr);

/*-------------------------------------------------------------------------------*/

/* - Public Callback Prototypes                                                  */

/*                                                                               */
/*===============================================================================*/



#endif      /* FLASH_LLD_H */
/* CHECK: RULE 205 ON */
/* CHECK: RULE 902 ON */
/* CHECK: RULE 506 ON */
/* CHECK: RULE 501 ON */
/* CHECK: RULE 502 ON */
