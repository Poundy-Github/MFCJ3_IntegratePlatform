/*===============================================================================*/
/*                                                                               */
/*                               FLASH layers                                    */
/*                                                                               */
/* ------------------------------------------------------------------------------*/
/*                                                                               */
/*                       Tricore Flash Low Layer Driver                          */
/*                                                                               */
/*===============================================================================*/
/*%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%                                        */
/*%%   _____________________________   %%  \file FLASH_RAM.c                     */
/*%%  |                             |  %%  \brief FLASH layer implementation     */
/*%%  |   &&&&&   &&&&&             |  %%  Module version: 7.1.6               */
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


/*=============================== FILE INCLUSION ================================*/
/*                                                                               */
/*-------------------------------------------------------------------------------*/
/* - Header Files:                                                               */
#include "EB_Prj.h"
#include "FlsLoader_Local.h"
#include "FlsLoader_Cfg.h"
#include "FLASH_RAM.h"

/*                                                                               */
/*===============================================================================*/

/*============================= PUBLIC DEFINITIONS ==============================*/
/*                                                                               */
/*-------------------------------------------------------------------------------*/
/* - Public Variables                                                            */

/*-------------------------------------------------------------------------------*/
/* - Public Function Prototypes                                                  */

/*-------------------------------------------------------------------------------*/
/* - Public Callback Prototypes                                                  */

/*                                                                               */
/*===============================================================================*/

/*============================ PRIVATE DEFINITIONS ==============================*/
/*                                                                               */
/*-------------------------------------------------------------------------------*/
/*-------------------------------------------------------------------------------*/
/* - Private Types                                                               */

/*-------------------------------------------------------------------------------*/
/* - Private Variables                                                           */


/*-------------------------------------------------------------------------------*/
/* - Private Macros                                                              */

/*-------------------------------------------------------------------------------*/
/* - Private Function Prototypes                                                 */


/*                                                                               */
/*===============================================================================*/

/*=============================== IMPLEMENTATION ================================*/
/*                                                                               */

#define FLSLOADER_START_SEC_WRITE_CODE
#include "MemMap.h"
/*---------------------------{FLASH_RAM_WriteRoutine}-----------------------------*/
tFlashStatus FLASH_RAM_WriteRoutine(tFlashAddress uAddr,u32 ulLen,const u8 FLASH_FAR_POINTER aubData)
{
    FlsLoader_ReturnType ulFlsStatus = FLSLOADER_E_OK;
    tFlashStatus eFlashStatus = FLASH_NO_ERROR;

    /* Write Operation */
    ulFlsStatus = FlsLoader_Write((FlsLoader_AddressType) uAddr,
            (FlsLoader_LengthType) ulLen, (const u8*) aubData);

    /* CHECK: NOPARSE (Error cannot happen with correct parameter (already filtered) unless an hardware error occurs) */
    if (FLSLOADER_E_OK == ulFlsStatus)
    {
        eFlashStatus = FLASH_NO_ERROR;
    }
    else /* Either Flash is busy, locked, suspend or another error occurred*/
    {
        eFlashStatus = FLASH_ACCESS_ERROR;
    }
    /* CHECK: PARSE */

    return eFlashStatus;
}
/*---------------------------{end FLASH_RAM_WriteRoutine}-----------------------------*/

/*---------------------------{FLASH_RAM_WriteRoutine}-----------------------------*/
/* Deviation MISRA-5 */
tFlashStatus FLASH_RAM_EraseRoutine(u16 ulSectorNo)
{

    FlsLoader_ReturnType ulFlsStatus = FLSLOADER_E_OK;
    tFlashStatus eFlashStatus = FLASH_NO_ERROR;
    u8 ubLoop = 0U;
    u16 ulSectorNoTmp = 0U;
    tFlashAddress uAddr = 0U;
    u8 ubFlasgEndLoop = FLASH_FALSE;

    /* Find associated start address of the sector to be erased */
    for (ubLoop = 0U;
            ((ubLoop < FLASH_INFO_SIZE) && (ubFlasgEndLoop == FLASH_FALSE));
            ubLoop++)
    {
        ulSectorNoTmp += Fls_Info[ubLoop].Number;

        if ((ulSectorNoTmp) >= (ulSectorNo))
        {
            uAddr = (u32) (Fls_Info[ubLoop].Start_Address
                    + (u32) (Fls_Info[ubLoop].Length
                            * (u32) (Fls_Info[ubLoop].Number
                                    - (u32) ((u32) ulSectorNoTmp
                                            - (u32) ulSectorNo))));
            ubFlasgEndLoop = FLASH_TRUE;
        }
    }


    ulFlsStatus = FlsLoader_Erase((FlsLoader_AddressType) uAddr,
            (FlsLoader_LengthType) 1U);

    /* CHECK: PARSE */

    /* CHECK: NOPARSE (Error cannot happen with correct parameter (already filtered) unless an hardware error occurs) */
    /* If no error */
    if (FLSLOADER_E_OK == ulFlsStatus)
    {
        eFlashStatus = FLASH_NO_ERROR;
    }
    /* If erasing error */
    else /* Either Flash is busy, locked, suspend or another error occurred*/
    {
        eFlashStatus = FLASH_ACCESS_ERROR;
    }
    /* CHECK: PARSE */

    return eFlashStatus;
}

#define FLSLOADER_STOP_SEC_WRITE_CODE
#include "MemMap.h"
/*-----------------------------{end FLASH_RAM_EraseRoutine}-----------------------*/


