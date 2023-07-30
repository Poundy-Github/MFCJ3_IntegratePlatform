/* CHECK: RULE 502 OFF */
/* CHECK: RULE 205 OFF */
#ifndef FLASH_PUB_H
#define FLASH_PUB_H

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
/*%%   _____________________________   %%  \file FLASH_Pub.h                     */
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
/* - Public Variables                                                            */

/*-------------------------------------------------------------------------------*/
/* - Public Function Prototypes                                                  */
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
 **/
extern tFlashStatus FLASH_WriteBuffer(tFlashAddress uAddr,u16 uwLen,const u8 FLASH_FAR_POINTER aubData);

/** \brief Erase sector of flash memory
 **
 ** This function allows to erase the sector of the flash memory, corresponding to the address
 ** specified in input parameter
 **
 ** \param[in] uAddr Memory address of the sector to be erased
 **
 ** \return Result of operation
 ** \retval FLASH_ACCESS_ERROR An error occurred during erasing operations. The data have not been written correctly.
 ** \retval FLASH_NO_ERROR     No problem, the sector have been correctly erased
 **
 **/

extern tFlashStatus FLASH_EraseSector(tFlashAddress uAddr);


#if (FLASH_MODE==FLASH_MODE_SLICER_SYNC)
/** \brief Erase one or several sectors of flash memory
 **
 ** This function allows to erase one or several sectors of the flash memory, starting from the address
 ** specified in input parameter.
 **
 ** \param[in] uAddr Memory address of the first sector to be erased
 ** \param[in] uwLen Length of the data to be erased
 **
 ** \return Result of operation
 ** \retval FLASH_ACCESS_ERROR An error occurred during erasing operations. The data have not been written correctly.
 ** \retval FLASH_NO_ERROR     No problem, the sector(s) have been correctly erased
 **
 **/

extern tFlashStatus FLASH_Erase(tFlashAddress uAddr, u32 uwLen);

#endif

/** \brief Read the flash memory
 **
 ** This function allows to read the data located to the address specified in input parameter.
 **
 ** \param[in] uAddr Memory address in flash to read
 ** \param[in] uwLen Length of the data to read
 ** \param[in] aubData Buffer where to store the read data
 **
 ** \return Result of operation
 ** \retval FLASH_ACCESS_ERROR An error occurred during check operations.
 ** \retval FLASH_NO_ERROR     No problem, the memory has been checked correctly
 **
 **/
extern tFlashStatus FLASH_Read(tFlashAddress uAddr,u16 uwLen, u8 *aubData);

/** \brief Initialize layer
 **
 ** This function initializes the FLASH layer, shall be called only once at ECU startup
 **
 **/
extern void FLASH_Init(void);

/** \brief Get next sector start address
 **
 ** This function is used to get start address of the sector after the one in which
 ** address specified in input parameter belongs to.
 **
 ** \param[in] uAddr Memory address of reference sector
 **
 ** \return Start address of the next sector.
 **         In case the sector address given in parameter is the last one the mapping,
 **         the function returns last address of the current sector.
 **
 **/
tFlashAddress FLASH_GetNextSectorAddr(tFlashAddress uAddr);

/** \brief Get the status of the current operation
 **
 **  this function is used to request the status of the ongoing asynchronous operation
 **  (Flash erase or write)
 **
 ** \return Status of the ongoing operation
 **
 **/
tFlashStatus FLASH_GetJobStatus(void);


#if (FLASH_MODE==FLASH_MODE_SLICER_SYNC)
/** \brief Process Asynchronous operation for flash mode
 **
 **  this function is used to process of the ongoing Asynchronous operation
 **  (Flash erase or write)
 **
 ** \no return value
 **
 **/
extern void FLASH_MainFunction(void);
#endif
/*-------------------------------------------------------------------------------*/

/* - Public Callback Prototypes                                                  */

/*                                                                               */
/*===============================================================================*/



#endif      /* FLASH_PUB_H */
/* CHECK: RULE 205 ON */
/* CHECK: RULE 502 ON */
