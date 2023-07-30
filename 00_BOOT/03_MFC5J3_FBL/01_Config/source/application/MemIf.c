/*===============================================================================*/
/*                                                                               */
/*                               MEMIF layers                                    */
/*                                                                               */
/* ------------------------------------------------------------------------------*/
/*                                                                               */
/*                              MEMIF  configuration                             */
/*                                                                               */
/*===============================================================================*/
/*%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%                                        */
/*%%   _____________________________   %%  \file MemIf.c                         */
/*%%  |                             |  %%  \brief MemIf layer implementation     */
/*%%  |   &&&&&   &&&&&             |  %%  Module version: 7.1.6                 */
/*%%  |   &       &    &            |  %%                                        */
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
 *  MISRA-1) Deviated Rule: 11.3 (advisory)
 *   "A cast should not be performed between a pointer type and an integral type."
 *
 *   Reason:
 *   A cast is mandatory for memory access in Flash_Read() API.
 *
 *  MISRA-2) Deviated Rule: 17.4 (required)
 *   "Array indexing shall be the only allowed form of pointer arithmetic."
 *
 *   Reason:
 *   Incrementing data pointer is needed to update the pointer of the datas to read.
 *   The rule indicates that we need to manipulate arrays instead of pointers for
 *   arithmetic operations but this implies temporary array copy mechanism, so much
 *   more code (useless) to do the same thing.
 *
 *  MISRA-3) Deviated Rule: 10.1 (required)
 *   "Implicit conversion of the expression of underlying type 'unsigned long' to
 *     the type 'signed int' that is not a wider integer type of the same signedness."
 *
 *   Reason:
 *   Data pointer needs to be incremented to get the value to be written.
 *
 *  MISRA-4) Deviated Rule: 8.1
 *   Function 'xxx' has no complete visible prototype at call
 *
 *   Reason:
 *   False positive.
 *
 *  MISRA-5)  Deviated Rule: 14.7
 *   A function shall have a single point of exit at the end of the function.
 *
 *   Reason:
 *   Add do-while loop to avoid compile error in coverage test.
 *
 *
 */

/* Deviation MISRA-5 <START> */

/* CHECK: RULE 404 OFF (Indentation rule deactivated as part of code are not     */
/* checked by CheckC                                                             */
/*=============================== FILE INCLUSION ================================*/
/*                                                                               */
/*-------------------------------------------------------------------------------*/
/* - Header Files:                                                               */
#include "EB_Prj.h"
#include "MemIf.h"
#include "Fls.h"
#include "board.h"
#include "log.h"
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
/* - Private Constants                                                           */
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
/*-------------------------------------------------------------------------------*/
/* - Public Functions                                                            */
void MemIf_Init(void)
{
    Fls_Init(&Fls_17_Dmu_Config);
}

MemIf_JobResultType MemIf_EraseSync(const u32 ulAddr,
                                    const u32 ulLen)
{
    MemIf_JobResultType  eFlsResult;
    MemIf_StatusType     eFlsStatus;
    Std_ReturnType       ReturnValueFls;

    eFlsResult = MEMIF_JOB_FAILED;

    /* Start erase */
    ReturnValueFls = Fls_Erase((u32)(ulAddr & 0x00FFF000U), 0x1000);
    if (ReturnValueFls == E_OK)
    {
        /* Flash operation unitl complete */
        do
        {
            Fls_MainFunction();
            eFlsStatus = Fls_GetStatus();
        }while (eFlsStatus == MEMIF_BUSY);

        if (eFlsStatus == MEMIF_IDLE)
        {
            /* Operation complete, get result */
            eFlsResult = Fls_GetJobResult();
        }
    }

    if (MEMIF_JOB_OK == eFlsResult)
    {
       LOG(LOG_LEVEL_INFO, "erase address 0x%08X length 0x%X success", ulAddr, ulLen);
    }
    else
    {
       LOG(LOG_LEVEL_ERROR, "erase address 0x%08X length 0x%X failure", ulAddr, ulLen);
    }

    return eFlsResult;
}

MemIf_JobResultType MemIf_WriteSync(const u32 ulAddr,
                                    const u8 *aubData,
                                    const u32 ulLen)
{
    MemIf_JobResultType  eFlsResult;
    MemIf_StatusType     eFlsStatus;
    Std_ReturnType       ReturnValueFls;

    eFlsResult = MEMIF_JOB_FAILED;

    /* Start write */
    ReturnValueFls = Fls_Write((u32)(ulAddr & 0x00FFFFFFU), aubData, ulLen);
    if (ReturnValueFls == E_OK)
    {
        /* Flash operation unitl complete */
        do
        {
            Fls_MainFunction();
            eFlsStatus = Fls_GetStatus();
        } while (eFlsStatus == MEMIF_BUSY);

        if (eFlsStatus == MEMIF_IDLE)
        {
            /* Operation complete, get result */
            eFlsResult = Fls_GetJobResult();
        }
    }

    if (MEMIF_JOB_OK == eFlsResult)
    {
       LOG(LOG_LEVEL_INFO, "write address 0x%08X length 0x%X success", ulAddr, ulLen);
    }
    else
    {
       LOG(LOG_LEVEL_ERROR, "write address 0x%08X length 0x%X failure", ulAddr, ulLen);
    }

    return eFlsResult;
}

MemIf_JobResultType MemIf_ReadSync(const u32 ulAddr,
                                   u8 *aubData,
                                   const u32 ulLen)
{
    MemIf_JobResultType  eFlsResult;
    MemIf_StatusType     eFlsStatus;
    Std_ReturnType       ReturnValueFls;

    eFlsResult = MEMIF_JOB_FAILED;

    /* Disable ECC check */
    BoardDisableECCCheck();

    /* Start read */
    ReturnValueFls = Fls_Read((u32)(ulAddr & 0x00FFFFFFU), aubData, ulLen);
    if (ReturnValueFls == E_OK)
    {
        /* Flash operation unitl complete */
        do
        {
            Fls_MainFunction();
            eFlsStatus = Fls_GetStatus();
        } while (eFlsStatus == MEMIF_BUSY);

        if (eFlsStatus == MEMIF_IDLE)
        {
            /* Operation complete, get result */
            eFlsResult = Fls_GetJobResult();
        }
    }

    /* Enable ECC check */
    BoardEnableECCCheck();

    if (MEMIF_JOB_OK == eFlsResult)
    {
       LOG(LOG_LEVEL_INFO, "read address 0x%08X length 0x%X success", ulAddr, ulLen);
    }
    else
    {
       LOG(LOG_LEVEL_ERROR, "read address 0x%08X length 0x%X failure", ulAddr, ulLen);
    }

    return eFlsResult;
}

MemIf_JobResultType MemIf_CompareSync(const u32 ulAddr,
                                      const u8 *aubData,
                                      const u32 ulLen)
{
    MemIf_JobResultType  eFlsResult;
    MemIf_StatusType     eFlsStatus;
    Std_ReturnType       ReturnValueFls;

    eFlsResult = MEMIF_JOB_FAILED;

    /* Disable ECC check */
    BoardDisableECCCheck();

    /* Start compare */
    ReturnValueFls = Fls_Compare((u32)(ulAddr & 0x00FFFFFFU), aubData, ulLen);
    if (ReturnValueFls == E_OK)
    {
        /* Flash operation unitl complete */ 
        do
        {
            Fls_MainFunction();
            eFlsStatus = Fls_GetStatus();
        } while (eFlsStatus == MEMIF_BUSY);

        if (eFlsStatus == MEMIF_IDLE)
        {
            /* Operation complete, get result */
            eFlsResult = Fls_GetJobResult();
        }
    }

    /* Enable ECC check */
    BoardEnableECCCheck();

    LOG(LOG_LEVEL_INFO, "compare address 0x%08X length 0x%X result %d", ulAddr, ulLen, eFlsResult);

    return eFlsResult;
}

MemIf_JobResultType MemIf_BlankCheckSync(const u32 ulAddr,
                                         const u32 ulLen)
{
    MemIf_JobResultType  eFlsResult;
    MemIf_StatusType     eFlsStatus;
    Std_ReturnType       ReturnValueFls;

    eFlsResult = MEMIF_JOB_FAILED;

    /* Disable ECC check */
    BoardDisableECCCheck();

    /* Start blank check */
    ReturnValueFls = Fls_17_Dmu_BlankCheck((u32)(ulAddr & 0x00FFFFFFU), ulLen);
    if (ReturnValueFls == E_OK)
    {
         /* Flash operation unitl complete */
        do
        {
            Fls_MainFunction();
            eFlsStatus = Fls_GetStatus();
        } while (eFlsStatus == MEMIF_BUSY);

        if (eFlsStatus == MEMIF_IDLE)
        {
            /* Operation complete, get result */
            eFlsResult = Fls_GetJobResult();
        }
    }

    /* Enable ECC check */
    BoardEnableECCCheck();

    LOG(LOG_LEVEL_INFO, "blank check address 0x%08X length 0x%X result %d", ulAddr, ulLen, eFlsResult);

    return eFlsResult;
}

/* CHECK: RULE 404 ON                                                            */
/*-------------------------------------------------------------------------------*/

/* Deviation MISRA-5 <STOP> */
