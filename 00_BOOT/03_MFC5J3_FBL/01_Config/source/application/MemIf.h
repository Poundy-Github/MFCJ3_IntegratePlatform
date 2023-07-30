/**
 * \file
 *
 * \brief AUTOSAR Demo
 *
 * This file contains the implementation of the AUTOSAR
 * module Demo.
 *
 * \author Elektrobit Automotive GmbH, 91058 Erlangen, Germany
 *
 * Copyright 2005 - 2019 Elektrobit Automotive GmbH
 * All rights exclusively reserved for Elektrobit Automotive GmbH,
 * unless expressly agreed to otherwise.
 */

#if (!defined MEMIF_H)
#define MEMIF_H


#include <MemIf_Types.h>

/** \brief Initialize layer
 **
 ** This function initializes the MemIf layer, shall be called only once at ECU startup
 **
 **/
extern void MemIf_Init(void);

/** \brief Erase one or several sectors of flash memory synchronized
 **
 ** This function allows to erase one or several sectors of the flash memory, starting from the address
 ** specified in input parameter.
 **
 ** \param[in] ulAddr Memory address of the first sector to be erased
 ** \param[in] ulLen  Length of the data to be erased
 **
 ** \return Result of operation
 ** \retval MEMIF_JOB_FAILED An error occurred during erasing operations. The data have not been written correctly.
 ** \retval MEMIF_JOB_OK     No problem, the sector(s) have been correctly erased
 **
 **/
extern MemIf_JobResultType MemIf_EraseSync(const u32 ulAddr,
                                           const u32 ulLen);

/** \brief Write buffer of data to flash memory synchronized
 **
 ** This function allows to write a buffer of data in flash memory at the address
 ** specified in input parameter
 **
 ** \param[in] ulAddr  Memory address where the data shall be written
 ** \param[in] aubData Buffer of data to be written
 ** \param[in] ulLen   Length of the data to be written
 **
 ** \return Result of operation
 ** \retval MEMIF_JOB_FAILED An error occurred during writing operations. The data have not been written correctly.
 ** \retval MEMIF_JOB_OK     No problem, the data have been written correctly
 **
 **/
extern MemIf_JobResultType MemIf_WriteSync(const u32 ulAddr,
                                           const u8 *aubData,
                                           const u32 ulLen);

/** \brief Read the flash memory synchronized
 **
 ** This function allows to read the data located to the address specified in input parameter.
 **
 ** \param[in] ulAddr Memory address in flash to read
 ** \param[in] aubData Buffer where to store the read data
 ** \param[in] ulLen Length of the data to read
 **
 ** \return Result of operation
 ** \retval MEMIF_JOB_FAILED An error occurred during check operations.
 ** \retval MEMIF_JOB_OK     No problem, the memory has been checked correctly
 **
 **/
extern MemIf_JobResultType MemIf_ReadSync(const u32 ulAddr,
                                          u8 *aubData,
                                          const u32 ulLen);

/** \brief Compare the flash memory synchronized
 **
 ** This function allows to compare the data with the address specified in input parameter.
 **
 ** \param[in] ulAddr Memory address in flash to read
 ** \param[in] aubData Buffer which to compare the read data
 ** \param[in] ulLen Length of the data to compare
 **
 ** \return Result of operation
 ** \retval MEMIF_JOB_FAILED An error occurred during check operations.
 ** \retval MEMIF_JOB_OK     No problem, the memory has been checked correctly
 **
 **/
extern MemIf_JobResultType MemIf_CompareSync(const u32 ulAddr,
                                             const u8 *aubData,
                                             const u32 ulLen);

/** \brief Check the flash memory blank synchronized
 **
 ** This function allows to check whether a given memory area has been erased but not (yet) programmed.
 **
 ** \param[in] ulAddr Memory address in flash to check
 ** \param[in] ulLen Length of the data to check
 **
 ** \return Result of operation
 ** \retval MEMIF_JOB_FAILED An error occurred during check operations.
 ** \retval MEMIF_JOB_OK     No problem, the memory has been checked correctly
 **
 **/
extern MemIf_JobResultType MemIf_BlankCheckSync(const u32 ulAddr,
                                                const u32 ulLen);
#endif /* !defined MEMIF_H */
