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
/*%%   _____________________________   %%  \file FLASH_Prg.c                     */
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
#include "FLASH_LLD.h"
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

/** \brief Get the sector associated to the passed address
 **
 ** This function allows to retrieve the sector(s) associated to the passed address.
 ** It also provides the next sector address.
 **
 ** \param[in] uAddr Memory address of the first sector to be retrieved
 ** \param[in] uwLen Length of the memory area associated to the sectors
 ** \param[out] pulStartBlockNo Pointer to the first sector associated to the provided address
 ** \param[out] pulEndBlockNo Pointer to the last sector associated to the provided address
 ** \param[out] puNextSectorAddr Pointer to the address of the next sector
 **
 ** \return Result of operation
 ** \retval FLASH_ACCESS_ERROR An error occurred during erasing operations. The data have not been written correctly.
 ** \retval FLASH_NO_ERROR     No problem, the sector(s) have been correctly erased
 **
 **/
NCS_PRI_FCT tFlashStatus FLASH_GetAssociatedSectors(const tFlashAddress uAddr, u32 uwLen,
u16 *pulStartBlockNo, u16 *pulEndBlockNo, tFlashAddress *puNextSectorAddr);


/** \brief Check the addr to deal with is protected or not
 **
 ** \param[in] uAddr start address to be checked
 ** \param[in] uwLen lengh to be checked
 **
 ** \return the status of the address
 **
 **/
NCS_PRI_FCT tFlashStatus FLASH_CheckProtectAddr(tFlashAddress uAddr, u32 uwLen);

u8  ubProcessFlag        = 0U;
u16 uwremainProcessTimes = 0U;
u16 uwWriteIncrement     = 0U;
u16 uwNotAlignedDataLen  = 0U;
u16 uwStartBlockNo = 0U;
u16 uwEndBlockNo = 0U;
tFlashStatus uwGlobalStatus = FLASH_NO_ERROR;
tFlashAddress uAddrSlicerSync;
const u8 FLASH_FAR_POINTER aubDataSlicerSync = NULL_PTR;

/*                                                                               */
/*===============================================================================*/

/*=============================== IMPLEMENTATION ================================*/
/*                                                                               */
/*-------------------------------------------------------------------------------*/
/* - Public Functions                                                            */

/*----------------------------------{FLASH_Init}---------------------------------*/
void FLASH_Init(void)
{
    /* Manually initialize global variables */
    ubProcessFlag        = 0U;
    uwremainProcessTimes = 0U;
    uwWriteIncrement     = 0U;
    uwNotAlignedDataLen  = 0U;
    uwStartBlockNo = 0U;
    uwEndBlockNo = 0U;
    uwGlobalStatus = FLASH_NO_ERROR;
    uAddrSlicerSync = 0U;
    aubDataSlicerSync = NULL_PTR;

    FLASH_LLD_Init();
}
/*----------------------------------{end FLASH_Init}-----------------------------*/

/*--------------------------------{FLASH_WriteBuffer}----------------------------*/
tFlashStatus FLASH_WriteBuffer(tFlashAddress uAddr, u16 uwLen,
        const u8 FLASH_FAR_POINTER aubData)
{
    tFlashStatus eFlashStatus = FLASH_ACCESS_ERROR;
    u8 ubFlashWriteFactor = 1U;
    u16 uwPageSizeByte = 0U;
    u32 ulAddressMax = 0U;
    u16 uwResultModulo = 0U;
    u16 uwTmpLen = uwLen;

    tFlashAddress ulAddrMasked = (u32)(uAddr & 0xDFFFFFFFU);


#if (FLASH_MODE==FLASH_MODE_BLOCKER_SYNC)
    u16 uwSize = 0U;
    u8 aubTmpData[FLASH_WRITE_BUFFER]={0U};
    u32 uLoopWritingLastByte = 0U;
    u8 ubWriteStatus = FLASH_TRUE;
    /* Initialize temporary data buffer with erased byte value for padding */
    for (uwSize = 0U; uwSize < FLASH_WRITE_BUFFER; uwSize++)
    {
        aubTmpData[uwSize] = FLASH_ERASED_BYTE_VALUE;
    }

#endif


#if (FLASH_MODE==FLASH_MODE_SLICER_SYNC)
    ubProcessFlag = FLASH_PROCESS_WRITE;
#endif

    /* Max address calculation */
    ulAddressMax = (u32) ((u32) Fls_Info[FLASH_INFO_SIZE - 1U].Start_Address
                                + (u32) (Fls_Info[FLASH_INFO_SIZE - 1U].Length * Fls_Info[FLASH_INFO_SIZE - 1U].Number));


    uwPageSizeByte = FLASH_PAGES_SIZE_BYTE;



#if (FLASH_MODE==FLASH_MODE_SLICER_SYNC)
    ubFlashWriteFactor = FLASH_NUMBER_OF_PAGE_PER_SLICER;
    uwWriteIncrement = (u16)(ubFlashWriteFactor * uwPageSizeByte);
#endif


                /* Check writing operation will not exceed FLASH max address */
                if ( ((u32) ((u32) ulAddrMasked + (u32) uwLen) > (u32) (ulAddressMax)) || ((u32)(ulAddrMasked) > (u32)(ulAddressMax)) )
                {
                    eFlashStatus = FLASH_ACCESS_ERROR;
                }
                /* Check writing operation will not write before FLASH min address */
                /* CHECK: NOPARSE */
                /* NOCOV-DEFENSIVE*/
                else if ((u32)(ulAddrMasked) < (u32)(Fls_Info[0U].Start_Address))
                {
                    eFlashStatus = FLASH_ACCESS_ERROR;
                }
                /* CHECK: PARSE */
                else if(FLASH_CheckProtectAddr(ulAddrMasked, uwLen) == FLASH_PROT_ERROR)
                {
                    eFlashStatus = FLASH_PROT_ERROR;
                }
                else
                {

                    /* Check if the address is aligned on FLASH_PAGES_SIZE_BYTE */
                    if ((0U == (ulAddrMasked % uwPageSizeByte)))
                    {
                        /* Set the length into long word instead of byte */
                        uwLen = (u16) (uwLen
                                / (u16) ((u16) ubFlashWriteFactor * uwPageSizeByte));

#if (FLASH_MODE==FLASH_MODE_SLICER_SYNC)
                        uwremainProcessTimes = (uwLen);
                        /* Remember current address */
                        uAddrSlicerSync = (u32)uAddr;
                        aubDataSlicerSync = aubData;
                        uwResultModulo = (u16) (uwTmpLen
                            % (u16) ((u16) ubFlashWriteFactor
                                    * uwPageSizeByte));
                        /* There are some data not alinged to uwWriteIncrement should be handled  individually*/
                        if(uwResultModulo > 0U)
                        {
                            uwremainProcessTimes = uwremainProcessTimes + 1;
                            uwNotAlignedDataLen = uwResultModulo;
                        }
                        else
                        {
                            /* do nothing */
                        }
                        uwGlobalStatus = FLASH_BUSY;
                        FLASH_MainFunction();
                        eFlashStatus = uwGlobalStatus;
#endif

#if (FLASH_MODE==FLASH_MODE_BLOCKER_SYNC)
                        /* Data length to be written is less than page flash size*/
                        if (uwTmpLen
                                < (u16) ((u16) ubFlashWriteFactor * uwPageSizeByte))
                        {
                            /* Calcul of how many bytes (under ubFlashWriteFactor * FLASH_PAGES_SIZE_BYTE bytes) there is to fill-in */
                            uwResultModulo = (u16) (uwTmpLen % (u16)((u16) ubFlashWriteFactor * uwPageSizeByte));

                            /* Filling aubTmpData with last value to write in flash */
                            for (uLoopWritingLastByte = 0U;
                                    uLoopWritingLastByte < uwResultModulo;
                                    uLoopWritingLastByte++)
                            {
                                aubTmpData[uLoopWritingLastByte] =
                                aubData[uLoopWritingLastByte];
                            }

                            eFlashStatus =
                            FLASH_LLD_WriteBuffer(ulAddrMasked,
                                    (u16) ((u16) ubFlashWriteFactor
                                            * uwPageSizeByte), aubTmpData);
                        }
                        /* Data length to be written take more than page flash size*/
                        else
                        {

                            /* Write each page */
                            for (uwSize = 0U;
                                    (uwSize < (uwLen + 1U)) && (FLASH_TRUE == ubWriteStatus);
                                    uwSize++)
                            {
                                /* Writing of 8 bytes with received values else bytes are completed with erased value */
                                /* (0xFF or 0x00) to conserve old value */
                                if (uwSize < uwLen)
                                {
                                    eFlashStatus = FLASH_LLD_WriteBuffer(ulAddrMasked,
                                            (u16) ((u16) ubFlashWriteFactor
                                                    * uwPageSizeByte), aubData);
                                }

                                else
                                {
                                    /* Calcul of how many bytes (under 8 bytes) there is to fill-in */
                                    uwResultModulo = (u16) (uwTmpLen
                                            % (u16) ((u16) ubFlashWriteFactor
                                                    * uwPageSizeByte));

                                    if (uwResultModulo > 0U)
                                    {
                                        /* Filling aubTmpData with last value to write in flash */
                                        for (uLoopWritingLastByte = 0U;
                                                uLoopWritingLastByte < uwResultModulo;
                                                uLoopWritingLastByte++)
                                        {
                                            aubTmpData[uLoopWritingLastByte] =
                                            aubData[uLoopWritingLastByte];
                                        }

                                        eFlashStatus = FLASH_LLD_WriteBuffer(ulAddrMasked,
                                                (u16) ((u16) ubFlashWriteFactor
                                                        * uwPageSizeByte),
                                                aubTmpData);
                                    }
                                }
                                /* CHECK: NOPARSE (Error cannot happen with correct parameter (already filtered) unless an hardware error occurs) */
                                if (FLASH_NO_ERROR == eFlashStatus)
                                {
                                    /* Go to next address and next data to write */
                                    ulAddrMasked += (u32) ((u32) ubFlashWriteFactor
                                            * uwPageSizeByte);
                                    /* Deviation MISRA-2, MISRA-3 */
                                    aubData += ((u32) ubFlashWriteFactor
                                            * uwPageSizeByte);
                                }
                                else /* Either Flash is busy, locked, suspend or another error occurred*/
                                {
                                    /* Leave the loop */
                                    ubWriteStatus = FLASH_FALSE;
                                }
                                /* CHECK: PARSE */
                            }
                        }
#endif
                    }
                    else
                    {
                        eFlashStatus = FLASH_ACCESS_ERROR;
                        uwGlobalStatus = eFlashStatus;
                    }
                }


    return eFlashStatus;
}
/*----------------------------{end FLASH_WriteBuffer}----------------------------*/


#if (FLASH_MODE==FLASH_MODE_SLICER_SYNC)
/*----------------------------------{FLASH_Erase}--------------------------------*/
tFlashStatus FLASH_Erase(tFlashAddress uAddr, u32 uwLen)
{
    tFlashStatus eFlashStatus = FLASH_NO_ERROR;
    u16 ulStartBlockNo = 0U;
    u16 ulEndBlockNo = 0U;


    ubProcessFlag = FLASH_PROCESS_ERASE;


            /* Look for the sectors associated to the addresses */
            /* Deviation MISRA-4 */
            eFlashStatus = FLASH_GetAssociatedSectors(uAddr, uwLen, &ulStartBlockNo, &ulEndBlockNo, NULL_PTR);

            /* If sector to erase have been found */
            if (FLASH_NO_ERROR == eFlashStatus)
            {
                if(FLASH_CheckProtectAddr(uAddr, uwLen) != FLASH_PROT_ERROR)
                {
                    uwStartBlockNo = ulStartBlockNo;
                    uwEndBlockNo = ulEndBlockNo;
                    uwremainProcessTimes = (uwEndBlockNo -uwStartBlockNo) +1U;
                    eFlashStatus =  FLASH_BUSY;
                    uwGlobalStatus =  eFlashStatus;
                }
                else
                {
                    eFlashStatus = FLASH_PROT_ERROR;
                    uwGlobalStatus = eFlashStatus;
                }
            }
            else
            {
                /* return FLASH_ACCESS_ERROR */
            }

    return eFlashStatus;
}
/*-----------------------------{end FLASH_Erase}---------------------------------*/

#endif

/*------------------------------{FLASH_EraseSector}------------------------------*/
tFlashStatus FLASH_EraseSector(tFlashAddress uAddr)
{
    tFlashStatus eFlashStatus = FLASH_NO_ERROR;
    u16 ulSectorNo = 0U;


            /* Check if sector associated to the addresse exist. */
            /* Deviation MISRA-4 */
            eFlashStatus = FLASH_GetAssociatedSectors(uAddr, 0, &ulSectorNo,
            NULL_PTR, NULL_PTR);

            /* If sector to erase have been found */
            if (FLASH_NO_ERROR == eFlashStatus)
            {
                if(FLASH_CheckProtectAddr(uAddr, 1U) != FLASH_PROT_ERROR)
                {
                    eFlashStatus = FLASH_LLD_EraseSector(ulSectorNo);


#if (FLASH_MODE==FLASH_MODE_SLICER_SYNC)
                    uwGlobalStatus =  eFlashStatus;
#endif
                }
                else
                {
                    eFlashStatus = FLASH_PROT_ERROR;
                    uwGlobalStatus = eFlashStatus;
                }
            }
            else
            {
                /* return FLASH_ACCESS_ERROR */
            }



    return eFlashStatus;
}
/*--------------------------{end FLASH_EraseSector}------------------------------*/


/*--------------------------------{FLASH_Read}-----------------------------------*/
tFlashStatus FLASH_Read(tFlashAddress uAddr, u16 uwLen, u8 *aubData)
{
    tFlashStatus eFlashStatus = FLASH_NO_ERROR;
    u32 uwIdxWord = 0U;
#ifdef FLASH_GPAGE_SIZE
    tFlashAddress uAddrTemp = 0U;
#endif
    if (NULL_PTR != aubData)
    {
        for (uwIdxWord = 0U; uwIdxWord < uwLen; uwIdxWord++)
        {
#ifdef FLASH_GPAGE_SIZE
            uAddrTemp = FLASH_GLOBAL_TO_PGADEADDR(uAddr);
            /* Deviation MISRA-1, MISRA-2 */
            aubData[uwIdxWord] = ((u8)(* (volatile u8 *far)uAddrTemp));
#else
            /* Deviation MISRA-1, MISRA-2 */

            aubData[uwIdxWord] = ((u8)(* (volatile u8 *)uAddr));


#endif
            uAddr ++;
        }
    }
    else
    {
        eFlashStatus = FLASH_ACCESS_ERROR;
    }
    return eFlashStatus;
}
/*-------------------------------{end FLASH_Read}--------------------------------*/

/*-------------------------{FLASH_GetNextSectorAddr}-----------------------------*/
tFlashAddress FLASH_GetNextSectorAddr(tFlashAddress uAddr)
{
    tFlashAddress uNextSectorAddr = 0U;

    tFlashAddress ulAddrMask;

    ulAddrMask = (u32)(uAddr & 0x20000000U);

    /* Look for the sectors associated to the addresses */
    /* No need to evaluate the return code, puNextSectorAddr will take
     *  a special value if no associated sector is found */
    /* Deviation MISRA-4 */
    (void) FLASH_GetAssociatedSectors(uAddr, 0, NULL_PTR, NULL_PTR,
            &uNextSectorAddr);

    uNextSectorAddr |=  (u32)ulAddrMask;

    return uNextSectorAddr;
}
/*------------------------{End FLASH_GetNextSectorAddr}--------------------------*/


#if (FLASH_MODE==FLASH_MODE_SLICER_SYNC)
/*----------------------------{FLASH_MainFunction}-------------------------------*/
void FLASH_MainFunction(void)
{
    u16 uwSize = 0U;
    u16 uwSizeTemp = 0U;
    u16 uLoopWritingLastByte = 0U;
    tFlashStatus RetVal = FLASH_NO_ERROR;

    u8 aubTmpData[FLASH_NUMBER_OF_PAGE_PER_SLICER * FLASH_PAGES_SIZE_BYTE] = {0U};
    uwSizeTemp = FLASH_NUMBER_OF_PAGE_PER_SLICER * FLASH_PAGES_SIZE_BYTE;

    /* Initialize temporary data buffer with erased byte value for padding */
    /* Deviation MISRA-3 */
    for (uwSize = 0U; uwSize < uwSizeTemp; uwSize++)
    {
        aubTmpData[uwSize] = FLASH_ERASED_BYTE_VALUE;
    }
    /* CHECK: NOPARSE (Error cannot happen unless an hardware error occurs) */
    if ((uwGlobalStatus != FLASH_ACCESS_ERROR)&& (uwremainProcessTimes > 0))
    /* CHECK: PARSE */
    {
       if (ubProcessFlag == FLASH_PROCESS_WRITE)
       {
            if ((uwremainProcessTimes == 1U) && (uwNotAlignedDataLen > 0U))
            {
                /* Filling aubTmpData with last value to write in flash */
                for (uLoopWritingLastByte = 0U;
                        uLoopWritingLastByte < uwNotAlignedDataLen;
                        uLoopWritingLastByte++)
                {
				    /* Deviation MISRA-2 */
                    aubTmpData[uLoopWritingLastByte] =
                        aubDataSlicerSync[uLoopWritingLastByte];
                }
				/* CHECK: NOPARSE */
				/* NOCOV-DEFENSIVE*/
                if ((uwNotAlignedDataLen % FLASH_PAGES_SIZE_BYTE) == 0 )
                {
                    uwNotAlignedDataLen = ((uwNotAlignedDataLen / FLASH_PAGES_SIZE_BYTE) * FLASH_PAGES_SIZE_BYTE);
                }
				/* CHECK: PARSE */
                else
                {
                    uwNotAlignedDataLen = ((uwNotAlignedDataLen / FLASH_PAGES_SIZE_BYTE) * FLASH_PAGES_SIZE_BYTE) + FLASH_PAGES_SIZE_BYTE;
                }
                RetVal = FLASH_LLD_WriteBuffer(uAddrSlicerSync, uwNotAlignedDataLen, &aubTmpData[0]);
            }
            else

            {
                RetVal = FLASH_LLD_WriteBuffer(uAddrSlicerSync, uwWriteIncrement, aubDataSlicerSync);
                /* Go to next address and next data to write */
                /* Deviation MISRA-3 */
                uAddrSlicerSync += (u32)uwWriteIncrement;
                 /* Deviation MISRA-1 */
                aubDataSlicerSync =(u8 FLASH_FAR_POINTER)((u32)aubDataSlicerSync + (u32)uwWriteIncrement);
            }
       }
       else
       {
            /* CHECK: NOPARSE (Start number should not small than End number) */
           if (uwStartBlockNo <= uwEndBlockNo)
            /* CHECK: PARSE */
           {
                RetVal = FLASH_LLD_EraseSector(uwStartBlockNo);
           }
           uwStartBlockNo += 1U;
       }

       uwremainProcessTimes -= 1U;
       if(uwremainProcessTimes == 0U)
       {
           uwGlobalStatus = RetVal;
       }
       else
       {
           /* CHECK: NOPARSE (Error cannot happen unless an hardware error occurs) */
           if(RetVal == FLASH_ACCESS_ERROR)
           /* CHECK: PARSE */
           {
                uwGlobalStatus = RetVal;
           }
       }

    }
    else
    {
        ubProcessFlag        = 0U;
        uwWriteIncrement     = 0U;
        uwNotAlignedDataLen  = 0U;
        uwStartBlockNo = 0U;
        uwEndBlockNo = 0U;
        uAddrSlicerSync = 0U;
        aubDataSlicerSync = NULL_PTR;
    }
}
/*---------------------------{End FLASH_MainFunction}----------------------------*/
#endif

/*----------------------------{FLASH_GetJobStatus}-------------------------------*/
tFlashStatus FLASH_GetJobStatus(void)
{
    tFlashStatus RetVal = FLASH_NO_ERROR;

    RetVal = uwGlobalStatus;

    return RetVal;
}
/*---------------------------{End FLASH_GetJobStatus}----------------------------*/

/*-------------------------------------------------------------------------------*/
/* - Private Functions                                                           */

/*----------------------------{FLASH_GetAssociatedSectors}-----------------------*/
/* Deviation MISRA-4 */

NCS_PRI_FCT tFlashStatus FLASH_GetAssociatedSectors(const tFlashAddress uAddr,
    u32 uwLen, u16 *pulStartBlockNo, u16 *pulEndBlockNo, tFlashAddress *puNextSectorAddr)
{
    tFlashStatus eFlashStatus = FLASH_ACCESS_ERROR;
    u16 uLoop = 0U;
    u16 uwSectorCount = 0U;
    u16 uwLoopConsecutive = 0U;
    u8 ubFlagEndLoop = FLASH_FALSE;
    u8 ubSectorFound = FLASH_FALSE;

    tFlashAddress ulAddrMasked = (u32)(uAddr & 0xDFFFFFFFU);

    /* Look for the sector(s) associated to the addresses */
    while ((uLoop < FLASH_INFO_SIZE) && (ubFlagEndLoop == FLASH_FALSE))
    {
        uwLoopConsecutive = 0;

        while ((uwLoopConsecutive < Fls_Info[uLoop].Number)
                && (ubFlagEndLoop == FLASH_FALSE))
        {
            if (((u32) ulAddrMasked
                    >= (u32) (Fls_Info[uLoop].Start_Address
                            + (Fls_Info[uLoop].Length * uwLoopConsecutive)))
                    && ((((u32) ulAddrMasked
                            < (u32) ((u32) (Fls_Info[uLoop].Start_Address
                                    + (u32) (Fls_Info[uLoop].Length
                                            * (u32) ((u32) uwLoopConsecutive
                                                    + 1U))))))
                    && (FLASH_FALSE == ubSectorFound)))
            {
                if (NULL_PTR != pulStartBlockNo)
                {

                    /* set the start block number to erase */
                    for (uwSectorCount = 0; uwSectorCount < uLoop;
                            uwSectorCount++)
                    {
                        *pulStartBlockNo += Fls_Info[uwSectorCount].Number;
                    }

                    *pulStartBlockNo += uwLoopConsecutive;
                }

                if (NULL_PTR != puNextSectorAddr)
                {
                    if (((FLASH_INFO_SIZE - 1U) == uLoop)
                            && (uwLoopConsecutive
                                    == (Fls_Info[FLASH_INFO_SIZE - 1U].Number
                                            - 1U))) /* last sector*/
                    {
                        /* Associated sector is the last configured, provide address outside the last sector range */
                        *puNextSectorAddr =
                                (Fls_Info[FLASH_INFO_SIZE - 1U].Start_Address
                                        + (Fls_Info[FLASH_INFO_SIZE - 1U].Length
                                                * Fls_Info[FLASH_INFO_SIZE - 1U].Number))
                                        + 1U;
                    }
                    else
                    {
                        /* CHECK: NOPARSE (Each target can only cover one case) */
                        /* NOCOV-DEFENSIVE*/
                        if(uwLoopConsecutive == (Fls_Info[uLoop].Number -1U))
                        {
                            *puNextSectorAddr = Fls_Info[uLoop +1U].Start_Address;
                        }
                        else
                        {
                            *puNextSectorAddr = Fls_Info[uLoop].Start_Address
                                + (u32) (Fls_Info[uLoop].Length
                                        * (u32) ((u32) uwLoopConsecutive + 1U));
                        }
                        /* CHECK: PARSE */
                    }
                }

                /* set a flag to indicate the address is found */
                ubSectorFound = FLASH_TRUE;
            }

            /* If the address is found count how many sectors must be erased*/
            if (ubSectorFound == FLASH_TRUE)
            {
                if ((u32) ((u32) (Fls_Info[uLoop].Start_Address
                        + (Fls_Info[uLoop].Length * uwLoopConsecutive))
                        + (u32) (Fls_Info[uLoop].Length))
                        >= (u32) (ulAddrMasked + uwLen))
                {
                    if (NULL_PTR != pulEndBlockNo)
                    {

                        /* Last block to erase is found */
                        for (uwSectorCount = 0; uwSectorCount < uLoop;
                                uwSectorCount++)
                        {
                            *pulEndBlockNo += Fls_Info[uwSectorCount].Number;
                        }

                        *pulEndBlockNo += uwLoopConsecutive;
                    }

                    /* Set end loop flag to true to exit loop */
                    ubFlagEndLoop = FLASH_TRUE;

                    /* return FLASH_NO_ERROR*/
                    eFlashStatus = FLASH_NO_ERROR;
                }
            }
            else if ((NULL_PTR != puNextSectorAddr)
                    && (((FLASH_INFO_SIZE - 1U) == uLoop)
                    && ((Fls_Info[FLASH_INFO_SIZE - 1U].Number - 1U)
                            == uwLoopConsecutive)))
            {
                /* No associated sector is found, provide last address of the last sector */
                *puNextSectorAddr =
                        (Fls_Info[FLASH_INFO_SIZE - 1U].Start_Address
                                + (Fls_Info[FLASH_INFO_SIZE - 1U].Length
                                        * Fls_Info[FLASH_INFO_SIZE - 1U].Number))
                                - 1U;

                /* Set end loop flag to true to exit loop */
                ubFlagEndLoop = FLASH_TRUE;
            }
            else
            {
                /* nothing to do */
            }

            uwLoopConsecutive++;
        }

        uLoop++;
    }

    return eFlashStatus;
}
/*----------------------------{End FLASH_GetAssociatedSectors}-----------------------*/

/*----------------------------{FLASH_CheckProtectAddr}-----------------------*/
NCS_PRI_FCT tFlashStatus FLASH_CheckProtectAddr(tFlashAddress uAddr, u32 uwLen)
{
    tFlashStatus eFlashStatus = FLASH_NO_ERROR;
    u16 uwLoop = 0U;
    u8 ubFlagProtect = 0U;
    tFlashAddress uSectorEndAddr = 0U;
    tFlashAddress uStartAddr = 0U;
    tFlashAddress uEndAddr = 0U;
    uStartAddr = (u32)uAddr;
    /*  To avoid misra warnings */
    uEndAddr = (u32)(uStartAddr + uwLen);
    uEndAddr -= 1U;
    while((uwLoop < FLASH_INFO_SIZE) && (FLASH_FALSE == ubFlagProtect))
    {
        /*  To avoid misra warnings */
        uSectorEndAddr =
                (u32)(Fls_Info[uwLoop].Start_Address
                    + (u32)(Fls_Info[uwLoop].Number * Fls_Info[uwLoop].Length));
        uSectorEndAddr -=  1U;
        if( ((u32)uSectorEndAddr >= (u32)uStartAddr)
          && ((u32)(Fls_Info[uwLoop].Start_Address) <= (u32)uEndAddr)
          && (Fls_Info[uwLoop].Programmable == FLASH_FALSE))
        {
            eFlashStatus = FLASH_PROT_ERROR;
            ubFlagProtect = FLASH_TRUE;
        }
        uwLoop++;
    }
    return eFlashStatus;
}
/*----------------------------{End FLASH_CheckProtectAddr}-----------------------*/

/* CHECK: RULE 404 ON                                                            */
/*-------------------------------------------------------------------------------*/

/* Deviation MISRA-5 <STOP> */
