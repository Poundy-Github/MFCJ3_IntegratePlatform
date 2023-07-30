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
/*                                                                               */
/*===============================================================================*/

/*============================= PUBLIC DEFINITIONS ==============================*/
/*                                                                               */
/*-------------------------------------------------------------------------------*/
/* - Public Variables                                                            */

tpfuWrite tWrite_fptr;
tpfuErase tErase_fptr;
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
#define FLASH_LLD_PROGRAM_FLASH                     0U
#define FLASH_LLD_DATA_FLASH                        1U
#define FLASH_LLD_UNDEFINED_FLASH_LLD_TYPE          2U
#define FLASH_DO_NOT_SKIP_PAGE                      0U
#define FLASH_SKIP_PAGE                             1U
/*-------------------------------------------------------------------------------*/
/* - Private Types                                                               */

/*-------------------------------------------------------------------------------*/
/* - Private Variables                                                           */

NCS_PRI_VAR pFLASHLLDERASEPROCESS  pFLASH_RAM_EraseRoutine;
NCS_PRI_VAR pFLASHLLDPROGRAMBUFFER pFLASH_RAM_WriteRoutine;


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
#define FLASH_LLD_PFLASH_PHYSICAL_SECTOR_NUMBERS 8U
#define FLASH_LLD_PFLASH_ADDRESS_MASK                ((FlsLoader_AddressType)(0x00FFFFFFU))


/* Program Verify Error */
#define FLS_PVER_ERROR                  (0x02000000U)
/* Erase Verify Error */
#define FLS_EVER_ERROR                  (0x04000000U)

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
    uint32 ulIdx = 0U;
    uint32 ulFlsLoaderRomSectionSize =0U;
    uint32 ulDrvRamSectionSize = 0U;
    tWrite_fptr = NULL_PTR;
    tErase_fptr =NULL_PTR;

    /* CHECK: NOPARSE */
    /* NOCOV-DEFENSIVE*/
    if(  (((uint32)_lc_ge_FLS_DRV_WRITE_CODE) >= ((uint32)_lc_gb_FLS_DRV_WRITE_CODE))
       &&(((uint32)_lc_ue_FLS_LOADER_RAM_AREA)  >= ((uint32)_lc_ub_FLS_LOADER_RAM_AREA)))
    /* CHECK: PARSE */
    {
        /* Get the size of the ROM Code section to be copied in RAM */
        ulFlsLoaderRomSectionSize = (uint32)_lc_ge_FLS_DRV_WRITE_CODE - (uint32)_lc_gb_FLS_DRV_WRITE_CODE;
        /* Get the size of the reserved RAM area defined in the linker script */
        ulDrvRamSectionSize = (uint32)_lc_ue_FLS_LOADER_RAM_AREA - (uint32)_lc_ub_FLS_LOADER_RAM_AREA;

        /* CHECK: NOPARSE */
        /* NOCOV-DEFENSIVE*/
        if(ulFlsLoaderRomSectionSize <= ulDrvRamSectionSize)
        /* CHECK: PARSE */
        {
            /* Copy flash api code from ram to rom. Use linkers'labels */
            for ( ulIdx=0U; ulIdx < (uint32)ulFlsLoaderRomSectionSize; ulIdx++)
            {
                *( (u8 *)((uint32)_lc_ub_FLS_LOADER_RAM_AREA + (uint32)ulIdx)) = *((u8 *)((uint32)(_lc_gb_FLS_DRV_WRITE_CODE) + ulIdx));
            }
            pFLASH_RAM_WriteRoutine = ( pFLASHLLDPROGRAMBUFFER )((uint32)_lc_ub_FLS_LOADER_RAM_AREA + ( (uint32)(&FLASH_RAM_WriteRoutine) - (uint32)(_lc_gb_FLS_DRV_WRITE_CODE) ));
            pFLASH_RAM_EraseRoutine = ( pFLASHLLDERASEPROCESS )((uint32)_lc_ub_FLS_LOADER_RAM_AREA + ( (uint32)(&FLASH_RAM_EraseRoutine) - (uint32)(_lc_gb_FLS_DRV_WRITE_CODE) ));
            tWrite_fptr =  (tpfuWrite) ((uint32)_lc_ub_FLS_LOADER_RAM_AREA + ( (uint32)(&FlsLoader_Write) - (uint32)(_lc_gb_FLS_DRV_WRITE_CODE) ));
            tErase_fptr  = (tpfuErase) ((uint32)_lc_ub_FLS_LOADER_RAM_AREA + ( (uint32)(&FlsLoader_Erase) - (uint32)(_lc_gb_FLS_DRV_WRITE_CODE) ));
#ifdef FLASH_OPERATION_CBK_TRICORE

            pFLASH_OperationCbk  = (PFLASH_OPERATIONCBK) ((uint32)_lc_ub_FLS_LOADER_RAM_AREA + ( (uint32)(&FLASH_OPERATION_CBK_TRICORE) - (uint32)(_lc_gb_FLS_DRV_WRITE_CODE) ));
#endif
        }
        /* CHECK: NOPARSE */
        /* NOCOV-DEFENSIVE*/
        else
        {
            /* ROM Section is bigger than the reserved RAM section, do not copy */
        }
        /* CHECK: PARSE */
    }
    /* CHECK: NOPARSE */
    /* NOCOV-DEFENSIVE*/
    else
    {
        /* Inconsistent section begin/end values */
    }
    /* CHECK: PARSE */

    (void) FlsLoader_Init(NULL_PTR);
}
/*--------------------------------{end FLASH_LLD_Init}---------------------------*/

/*---------------------------{FLASH_LLD_WriteBuffer}-----------------------------*/
tFlashStatus FLASH_LLD_WriteBuffer(tFlashAddress uAddr, u16 uwLen,
        const u8 FLASH_FAR_POINTER aubData)
{
    u8 ebStatus = 0U;
    tFlashStatus eFlashStatus = FLASH_NO_ERROR;
    u16 uwWriteLength = 0U;
    u16  i = 0U;

    ebStatus = APP_InterruptDisable();
#if (FLASH_WATCHDOG_CARE == FLASH_TRUE)
    /* Deactivate the watchdog before Flash operation */
    Watchdog_WdgDeactivate();
#endif


    while((uwLen > uwWriteLength) && (eFlashStatus == FLASH_NO_ERROR))
    {
        for(i = 0U; i < FLASH_PAGES_SIZE_BYTE; i++)
        {
		    /* Deviation MISRA-4 */
            m_aubBuffer[i] = aubData[uwWriteLength + i];
        }

        eFlashStatus = pFLASH_RAM_WriteRoutine(uAddr,FLASH_PAGES_SIZE_BYTE,m_aubBuffer);
        /* CHECK: NOPARSE */
        /* NOCOV-DEFENSIVE*/
        if(eFlashStatus != FLASH_NO_ERROR)
        {
        /* CHECK: PARSE */
            eFlashStatus =  FLASH_ACCESS_ERROR;
        }
        uwWriteLength += FLASH_PAGES_SIZE_BYTE;
        uAddr += FLASH_PAGES_SIZE_BYTE;
    }
#if (FLASH_WATCHDOG_CARE == FLASH_TRUE)
    /* Reactivate the watchdog after Flash operation */
    Watchdog_WdgActivate();
#endif
    APP_InterruptEnable (ebStatus);
    return eFlashStatus;
}
/*-----------------------------{end FLASH_LLD_WriteBuffer}-----------------------*/

/*----------------------------{FLASH_LLD_EraseSector}----------------------------*/
tFlashStatus FLASH_LLD_EraseSector(u16 ulSectorNo)
{
    u8 ebStatus = 0U;
    tFlashStatus eFlashStatus = FLASH_NO_ERROR;

    ebStatus = APP_InterruptDisable();
#if (FLASH_WATCHDOG_CARE == FLASH_TRUE)
    /* Deactivate the watchdog before Flash operation */
    Watchdog_WdgDeactivate();
#endif

    eFlashStatus = pFLASH_RAM_EraseRoutine(ulSectorNo);

#if (FLASH_WATCHDOG_CARE == FLASH_TRUE)
    /* Reactivate the watchdog after Flash operation */
    Watchdog_WdgActivate();
#endif
    APP_InterruptEnable (ebStatus);
    return eFlashStatus;
}
/*-----------------------------{end FLASH_LLD_EraseSector}-----------------------*/
/* Deviation MISRA-1 MISRA-2 MISRA-3 <STOP> */
/* CHECK: RULE 901 ON */
/* CHECK: RULE 205 ON */
