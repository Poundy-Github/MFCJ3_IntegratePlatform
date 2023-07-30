#ifndef FLASH_CFG_H
#define FLASH_CFG_H
/*********************************************************************************/
/*                                                                               */
/*                               BOOT layers                                     */
/*                                                                               */
/* ----------------------------------------------------------------------------- */
/*                                                                               */
/*                                 FLASH configuration                           */
/*                                                                               */
/*********************************************************************************/
/*%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%                                        */
/*%%   _____________________________   %%  \file FLASH_Cfg.h                     */
/*%%  |                             |  %%  \brief FLASH layer implementation     */
/*%%  |   &&&&&   &&&&&             |  %%  Module version: 7.1.6                 */
/*%%  |   &       &    &            |  %%  TARGET: TRICORE                     */
/*%%  |   &&&&    &&&&&             |  %%  DERIVATE: TC38XQ                 */
/*%%  |   &       &    &            |  %%                                        */
/*%%  |   &&&&&   &&&&&             |  %%                                        */
/*%%  |_____________________________|  %%                                        */
/*%%                                   %%                                        */
/*%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%                                        */
/*********************************************************************************/
/* Copyright 2017 by Elektrobit Automotive GmbH                                  */
/* All rights exclusively reserved for Elektrobit Automotive GmbH,               */
/* unless expressly agreed to otherwise.                                         */
/*********************************************************************************/
/*  MISRA-C:2004 Deviation List
 *
 *  MISRA-1) Deviated Rule: 19.4 (required)
 *   "Macro defines a type specifier keyword."
 *
 *   Reason:
 *   This macro is used for target and compiler adaptation.
 */


/******************************** FILE INCLUSION *********************************/
/*                                                                               */
/*-------------------------------------------------------------------------------*/
/* - Header Files: Variable Types                                                */



/*-------------------------------------------------------------------------------*/
/* - Header Files: <NomCouche>                                                   */

/*                                                                               */
/*********************************************************************************/




/****************************** PUBLIC DEFINITIONS *******************************/
/*                                                                               */
/*-------------------------------------------------------------------------------*/
/* - Configuration Constants                                                     */
#define PAGE_SIZE           256U   /* program FLASH page size */
/*-------------------------------------------------------------------------------*/
/** \brief Minimum size in bytes for writting operation in FLASH memory */
#define FLASH_PAGES_SIZE_BYTE    256U

/* This Macro only used in Slicer mode */
#define FLASH_NUMBER_OF_PAGE_PER_SLICER    4U

/** \brief Value read of FLASH memory after an erase operation */
#define FLASH_ERASED_BYTE_VALUE   0x00U

/** \brief Define the total size of the flash memory */
#define FLASH_TOTAL_SIZE       0x24000U


/** \brief Flash driver does not call APIs to deactivate/activate the Watchdog during memory operations */
#define FLASH_WATCHDOG_CARE     FLASH_FALSE

/*-------------------------------------------------------------------------------*/
/* - Public Constants                                                            */

/*-------------------------------------------------------------------------------*/
/* - Public Types                                                                */

typedef unsigned char rBool;

#define FLASH_FALSE   0U
#define FLASH_TRUE    1U

#define FLASHPBUSY       0x00000001U      /* Program Flash Busy */
#define FLASHD0BUSY      0x00000004U      /* Data Flash Bank 0 Busy */
#define FLASHD1BUSY      0x00000008U      /* Data Flash Bank 1 Busy */
#define FLASH_MASK_BUSY (FLASHPBUSY | FLASHD0BUSY | FLASHD1BUSY)
#define FLASH_NOT_BUSY   0x00000000U

/*-------------------------------------------------------------------------------*/
/* - Public Macros                                                               */

/* Set memory mapping */
#define EB_RAM_MAPPING FLASH_TRUE
#define PRAGMA_SECTION1 "RAMCODE"

/** \brief Structure of flash sector containing adress, length and programmability information */
typedef struct FLS_INFO_TYPE_TAG
{
    uint32                  Start_Address;
    uint32                  Length;
    uint16                  Number;        /* Number of consecutive sector with the same size */
    rBool                   Programmable;
}tFlsInfo;


extern const tFlsInfo Fls_Info[FLASH_MAX_SECTOR];


/*                                                                               */
/*********************************************************************************/


#endif      /* FLASH_CFG_H */
