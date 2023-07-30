/* CHECK: RULE 901 OFF */
/* CHECK: RULE 205 OFF */
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
/*%%   _____________________________   %%  \file FLASH_LLD.c                    */
/*%%  |                             |  %%  \brief FLASH layer implementation      */
/*%%  |   &&&&&   &&&&&             |  %%  Module version: 7.1.6               */
/*%%  |   &       &    &            |  %%  Variant: OsekCore                     */
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

/* Global Misra Violation and Suppression */
/*  MISRA-C:2004 Deviation List
 *
 *  MISRA-1) Deviated Rule 19.11
 *   "XXX is not defined."
 *
 *   Reason:
 *   Needed for if/else checking.
 *
 *  MISRA-2) Deviated Rule 11.3 (advisory)
 *   "A cast should not be performed between a pointer type and an integral type."
 *
 *   Reason:
 *   A cast is mandatory for memory access in FLASH_LLD_Read() API.
 *
 *  MISRA-3) Deviated Rule: 3.4 (required)
 *   "All uses of the #pragma directive shall be documented and explained."
 *
 *   Reason:
 *   Needed for align memory.
 *
 *  MISRA-4) Deviated Rule: 17.4 (required)
 *   "Array indexing shall be the only allowed form of pointer arithmetic."
 *
 *   Reason:
 *   Incrementing data pointer is needed to update the pointer of the datas to read.
 *   The rule indicates that we need to manipulate arrays instead of pointers for
 *   arithmetic operations but this implies temporary array copy mechanism, so much
 *   more code (useless) to do the same thing. 
 *
 */

 /* Deviation MISRA-1 MISRA-2 MISRA-3 <START> */

/*=============================== FILE INCLUSION ================================*/
/*                                                                               */
/*-------------------------------------------------------------------------------*/
/* - Header Files:                                                               */
#include "EB_Prj.h"
#include "FlsLoader_Local.h"
#include "FlsLoader_Cfg.h"
#ifdef FLASH_MANAGE_SKIP_PAGE
#include "Flash_Wrapper.h"
#endif
#include "Flash_LLD.h"
#if (FLASH_WATCHDOG_CARE == FLASH_TRUE)
#include "Watchdog.h"
#endif
#include "FLASH_RAM.h"
#include "board.h"

/*                                                                               */
/*===============================================================================*/

/*============================= PUBLIC DEFINITIONS ==============================*/
/*                                                                               */
/*-------------------------------------------------------------------------------*/
/* - Public Variables                                                            */

PFLASH_OPERATIONCBK pFLASH_OperationCbk;
/*-------------------------------------------------------------------------------*/
/* - Public Function Prototypes                                                  */

/*-------------------------------------------------------------------------------*/
/* - Public Callback Prototypes                                                  */

/*                                                                               */
/*===============================================================================*/

/*============================ PRIVATE DEFINITIONS ==============================*/
/*                                                                               */
/*-------------------------------------------------------------------------------*/
/* - Private Constants                                                           */

/*-------------------------------------------------------------------------------*/
/* - Private Types                                                               */

/*-------------------------------------------------------------------------------*/
/* - Private Variables                                                           */

#if (FLASH_COMPILER == WINDRIVER)
NCS_PRI_VAR __attribute__(( aligned(4) )) u8 m_aubBuffer[FLASH_PAGES_SIZE_BYTE];
#elif (FLASH_COMPILER == HIGHTEC)
NCS_PRI_VAR __attribute__(( aligned(4) )) u8 m_aubBuffer[FLASH_PAGES_SIZE_BYTE];
#elif (FLASH_COMPILER == GHS)
#pragma alignvar (4)
NCS_PRI_VAR u8 m_aubBuffer[FLASH_PAGES_SIZE_BYTE];
#else
#pragma align 8
NCS_PRI_VAR u8 m_aubBuffer[FLASH_PAGES_SIZE_BYTE];
#endif



/*-------------------------------------------------------------------------------*/
/* - Private Macros                                                              */

/*-------------------------------------------------------------------------------*/
/* - Private Function Prototypes                                                 */
/*                                                                               */
/*===============================================================================*/

/*=============================== IMPLEMENTATION ================================*/
/*                                                                               */

/*-------------------------------------------------------------------------------*/
/* - Public Functions                                                            */

/*-------------------------------{FLASH_LLD_Init}--------------------------------*/
void FLASH_LLD_Init(void)
{
    (void) FlsLoader_Init(NULL_PTR);
}
/*--------------------------------{end FLASH_LLD_Init}---------------------------*/

/*---------------------------{FLASH_LLD_WriteBuffer}-----------------------------*/
tFlashStatus FLASH_LLD_WriteBuffer(tFlashAddress uAddr, u32 ulLen,
        const u8 FLASH_FAR_POINTER aubData)
{
    tFlashStatus eFlashStatus = FLASH_NO_ERROR;
    u32 ulWriteLength = 0U;
    u32 i = 0U;

    BoardDisableInterrupts();
#if (FLASH_WATCHDOG_CARE == FLASH_TRUE)
    /* Deactivate the watchdog before Flash operation */
    Watchdog_WdgDeactivate();
#endif

    while((ulLen > ulWriteLength) && (eFlashStatus == FLASH_NO_ERROR))
    {
        for(i = 0U; i < FLASH_PAGES_SIZE_BYTE; i++)
        {
            /* Deviation MISRA-4 */
            m_aubBuffer[i] = aubData[ulWriteLength + i];
        }

        eFlashStatus = FLASH_RAM_WriteRoutine(uAddr,FLASH_PAGES_SIZE_BYTE,m_aubBuffer);
        /* CHECK: NOPARSE */
        /* NOCOV-DEFENSIVE*/
        if(eFlashStatus != FLASH_NO_ERROR)
        {
        /* CHECK: PARSE */
            eFlashStatus =  FLASH_ACCESS_ERROR;
        }
        ulWriteLength += FLASH_PAGES_SIZE_BYTE;
        uAddr += FLASH_PAGES_SIZE_BYTE;
    }
#if (FLASH_WATCHDOG_CARE == FLASH_TRUE)
    /* Reactivate the watchdog after Flash operation */
    Watchdog_WdgActivate();
#endif
    BoardEnableInterrupts();
    return eFlashStatus;
}
/*-----------------------------{end FLASH_LLD_WriteBuffer}-----------------------*/

/*----------------------------{FLASH_LLD_EraseSector}----------------------------*/
tFlashStatus FLASH_LLD_EraseSector(u16 ulSectorNo)
{
    tFlashStatus eFlashStatus = FLASH_NO_ERROR;

    BoardDisableInterrupts();
#if (FLASH_WATCHDOG_CARE == FLASH_TRUE)
    /* Deactivate the watchdog before Flash operation */
    Watchdog_WdgDeactivate();
#endif

    eFlashStatus = FLASH_RAM_EraseRoutine(ulSectorNo);

#if (FLASH_WATCHDOG_CARE == FLASH_TRUE)
    /* Reactivate the watchdog after Flash operation */
    Watchdog_WdgActivate();
#endif
    BoardEnableInterrupts();
    return eFlashStatus;
}
/*-----------------------------{end FLASH_LLD_EraseSector}-----------------------*/
/* Deviation MISRA-1 MISRA-2 MISRA-3 <STOP> */
/* CHECK: RULE 901 ON */
/* CHECK: RULE 205 ON */
