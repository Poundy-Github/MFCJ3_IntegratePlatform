/*===============================================================================*/
/*                                                                               */
/*                               BOOT Layers                                     */
/*                                                                               */
/* ----------------------------------------------------------------------------- */
/*                                                                               */
/*                               BM layer                                        */
/*                                                                               */
/*===============================================================================*/
/*%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%                                        */
/*%%   _____________________________   %%  \file BM_Cbk.c                        */
/*%%  |                             |  %%  \brief BM layer include plugin file   */
/*%%  |   &&&&&   &&&&&             |  %%  Module version: 1.15.0 BL3                */
/*%%  |   &       &    &            |  %%  Variant: OsekCore                  */
/*%%  |   &&&&    &&&&&             |  %%                                        */
/*%%  |   &       &    &            |  %%                                        */
/*%%  |   &&&&&   &&&&&             |  %%                                        */
/*%%  |_____________________________|  %%                                        */
/*%%                                   %%                                        */
/*%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%                                        */
/*===============================================================================*/
/* Copyright 2010 by Elektrobit Automotive GmbH                                  */
/* All rights exclusively reserved for Elektrobit Automotive GmbH,               */
/* unless expressly agreed to otherwise.                                         */
/*===============================================================================*/

/*=============================== FILE INCLUSION ================================*/
/*                                                                               */
/*-------------------------------------------------------------------------------*/
/* - Header Files                                                                */

#include "EB_Prj.h"
#include "MemIf.h"
#include "TSMem.h"
#include "board.h"
#include "md5.h"
#include "verify.h"
#include "log.h"
/*                                                                               */
/*===============================================================================*/

#if !defined(RELEASE_VERSION)
volatile const u8 m_auReleaseVersion[16] =  {'D','E','B','U','G','','','','','','','','','','',''};
#else
volatile const u8 m_auReleaseVersion[16] =    {'R','E','L','E','A','S','E','','','','','','','','',''};
#endif 
 

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
/* - Private Macros                                                              */
#define BM_SIG                          0x5AA5A55AU

#define BM_FLASH_STATUS_ADDR_BLU        0x800A0000U
#define BM_FLASH_STATUS_ADDR_BL         0x80060000U
#define BM_FLASH_STATUS_SIZE            32U

#define BM_BOOT_SIGNATURE_ADDR_BLU      0x800A4020U
#define BM_BOOT_SIGNATURE_ADDR_BL       0x80064020U
#define BM_BOOT_SIGNATURE_CHECK_COUNT   0x03U

#define BM_START_ADDR_BLU               0x800A4100U
#define BM_START_ADDR_BL                0x80064100U

#define BM_SIGNATURE_LENGTH             16U
#define BM_HASH_LENGTH                  16U

#define BM_SECURE_BOOT_ERROR_ADDR_BLU   0xAF07E040U
#define BM_SECURE_BOOT_ERROR_ADDR_BL    0xAF07E038U
#define BM_SECURE_BOOT_ERROR_SIZE       8U

/*-------------------------------------------------------------------------------*/
/* - Private Constants                                                           */
typedef struct
{
    u32  ulStatus;
    u32  ulDummy;
    u32  ulStartAddress;
    u32  ulSize;
    u8   ubSignature[BM_SIGNATURE_LENGTH];
}tSignatureInfo;

/*-------------------------------------------------------------------------------*/
/* - Private Variables                                                           */
#define BM_REPROG_FLAG_START_SEC_VAR_NO_INIT_8
#include "BM_MemMap.h"
NCS_PRI_VAR u32 m_ulBmSig;
#define BM_REPROG_FLAG_STOP_SEC_VAR_NO_INIT_8
#include "BM_MemMap.h"

/*-------------------------------------------------------------------------------*/
/* - Private Function Prototypes                                                 */

static tBMBoolean BM_CheckFlashStatus(u32 ulAddress);
static tBMBoolean BM_CheckBootSignature(u32 ulAddress);
static tBMBoolean BM_WriteSecureBootError(u32 ulAddress);

/*                                                                               */
/*===============================================================================*/


/*=============================== IMPLEMENTATION ================================*/
/*                                                                               */

/*-------------------------------------------------------------------------------*/
/* - Public Functions                                                            */



/*----------------------------{BM_CheckProgRequest}----------------------------------*/
extern tBMBoolean BM_CheckProgRequest(void)
{
    tBMBoolean eBMBoolean;

    eBMBoolean = BoardIsSwReset();

    if (BM_TRUE == eBMBoolean)
    {
        LOG(LOG_LEVEL_INFO, "ProgSig 0x%08X", m_ulBmSig);

        /* Check if the signature is set */
        if (m_ulBmSig != BM_SIG)
        {
            eBMBoolean = BM_FALSE;
        }
    }

    return eBMBoolean;
}
/*----------------------------{end BM_CheckProgRequest}------------------------------*/

/*----------------------------{BM_CustomCheckValidAppl}----------------------------------*/
extern tBMBoolean BM_CustomCheckValidAppl(void)
{
    return BM_TRUE;
}
/*----------------------------{end BM_CustomCheckValidAppl}------------------------------*/

/*----------------------------{BM_CustomCheckValidBLU}----------------------------------*/
extern tBMBoolean BM_CustomCheckValidBLU(void)
{
    tBMBoolean eBMBoolean;

    BM_DisableECCCheck();

    /* check bootloader updater flash status */
    eBMBoolean = BM_CheckFlashStatus(BM_FLASH_STATUS_ADDR_BLU);

    if (BM_TRUE == eBMBoolean)
    {
        /* check bootloader updater Signature */
        eBMBoolean = BM_CheckBootSignature(BM_BOOT_SIGNATURE_ADDR_BLU);

        if (BM_TRUE != eBMBoolean)
        {
            LOG(LOG_LEVEL_ERROR, "bootloader updater signature error");

            /* write bootloader updater Signature error flag */
            BM_WriteSecureBootError(BM_SECURE_BOOT_ERROR_ADDR_BLU);
        }
    }
    else
    {
        LOG(LOG_LEVEL_INFO, "no bootloader updater");        
    }

    BM_EnableECCCheck();

    return eBMBoolean;
}
/*----------------------------{end BM_CustomCheckValidBLU}------------------------------*/

/*----------------------------{BM_CustomCheckValidBL}----------------------------------*/
extern tBMBoolean BM_CustomCheckValidBL(void)
{
    tBMBoolean eBMBoolean;

    BM_DisableECCCheck();

    /* check bootloader flash status */
    eBMBoolean = BM_CheckFlashStatus(BM_FLASH_STATUS_ADDR_BL);

    if (BM_TRUE == eBMBoolean)
    {
        /* check bootloader Signature */
        eBMBoolean = BM_CheckBootSignature(BM_BOOT_SIGNATURE_ADDR_BL);

        if (BM_TRUE != eBMBoolean)
        {
            LOG(LOG_LEVEL_ERROR, "bootloader signature error");

            /* write bootloader Signature error flag */
            BM_WriteSecureBootError(BM_SECURE_BOOT_ERROR_ADDR_BL);
        }
    }
    else
    {
        LOG(LOG_LEVEL_ERROR, "bootloader status error");        
    }

    BM_EnableECCCheck();

    return eBMBoolean;
}
/*----------------------------{end BM_CustomCheckValidBL}------------------------------*/

/*----------------------------{BM_JumpToApplication}----------------------------------*/
extern void BM_JumpToApplication(void)
{

}
/*----------------------------{end BM_JumpToApplication}------------------------------*/

/*----------------------------{BM_JumpToBLU}----------------------------------*/
extern void BM_JumpToBLU(void)
{
    ptBLU_START_ADDR pBLU_START_ADDR;
 
    pBLU_START_ADDR = BM_START_ADDR_BLU;

    LOG(LOG_LEVEL_INFO, "jump to bootloader updater start address 0x%X", pBLU_START_ADDR);
    /* jump to bootloader updater */
    pBLU_START_ADDR();
    LOG(LOG_LEVEL_ERROR, "bootloader updater start address error");
}
/*----------------------------{end BM_JumpToBLU}------------------------------*/

/*----------------------------{BM_JumpToBL}----------------------------------*/
extern void BM_JumpToBL(void)
{
    ptBL_START_ADDR pBL_START_ADDR;
 
    pBL_START_ADDR = BM_START_ADDR_BL;

    LOG(LOG_LEVEL_INFO, "jump to bootloader start address 0x%X", pBL_START_ADDR);
    /* jump to bootloader */
    pBL_START_ADDR();
    LOG(LOG_LEVEL_ERROR, "bootloader start address error");
}
/*----------------------------{end BM_JumpToBL}------------------------------*/

void BM_DisableECCCheck(void)
{
    BoardDisableECCCheck();
}

void BM_EnableECCCheck(void)
{
    BoardEnableECCCheck();
}

tBMBoolean BM_CheckFlashStatus(u32 ulAddress)
{
    tBMBoolean eBMBoolean;
    u8 ubIdx;

    eBMBoolean = BM_TRUE;

    LOG(LOG_LEVEL_INFO, "BM_CheckFlashStatus ulAddress{0x%04x} is 0x%04x",ulAddress,*(u32 *)ulAddress);

    for (ubIdx = 0U; ubIdx < BM_FLASH_STATUS_SIZE / 4U; ubIdx++, ulAddress += 4U)
    {
        

        if(*(u32 *)ulAddress != BM_SIG)
        {
            eBMBoolean = BM_FALSE;
            break;
        }
    }
    
    return eBMBoolean;
}

tBMBoolean BM_CheckBootSignature(u32 ulAddress)
{
    tBMBoolean eBMBoolean;
    int ret;
    u8 ubIdx;
    tSignatureInfo* pstSignatureInfo;
    u8 aubHash[BM_HASH_LENGTH];

    eBMBoolean = BM_FALSE;

    for (ubIdx = 0U; ((ubIdx < BM_BOOT_SIGNATURE_CHECK_COUNT) && (BM_FALSE == eBMBoolean)); ubIdx++)
    {
        pstSignatureInfo = (tSignatureInfo*)ulAddress;

        /* check signature status and size */
        if ((pstSignatureInfo->ulStatus == BM_SIG) || (pstSignatureInfo->ulSize == 0))
        {
            eBMBoolean = BM_TRUE;
        }

        if (BM_TRUE == eBMBoolean)
        {
            /* calculate md5 */
            ret = mbedtls_md5_ret((u8*)(pstSignatureInfo->ulStartAddress), pstSignatureInfo->ulSize, aubHash);
            if (ret != E_OK)
            {
                eBMBoolean = BM_FALSE;
            }
        }
        
        if (BM_TRUE == eBMBoolean)
        {
            #if defined(RELEASE_VERSION)
            /* verify signature */
            ret = mbedtls_verify(aubHash, pstSignatureInfo->ubSignature);
            // ret = TS_MemCmp(aubHash, pstSignatureInfo->ubSignature,16);
            if (ret != E_OK)
            {
                eBMBoolean = BM_FALSE;
            }
            #else
            //none
            #endif
             
        } 
    }

    return eBMBoolean;
}

tBMBoolean BM_WriteSecureBootError(u32 ulAddress)
{
    tBMBoolean eBMBoolean;
    MemIf_JobResultType eMemIfResult;
    u8 ubIdx;
    u32 aulECUSecureBootError[BM_SECURE_BOOT_ERROR_SIZE / 4U];

    eBMBoolean = BM_FALSE;

    for (ubIdx = 0U; ubIdx < BM_SECURE_BOOT_ERROR_SIZE / 4U; ubIdx++)
    {
        aulECUSecureBootError[ubIdx] = BM_SIG;
    }

    eMemIfResult = MemIf_CompareSync(ulAddress, (u8*)aulECUSecureBootError, BM_SECURE_BOOT_ERROR_SIZE);
    if (eMemIfResult == MEMIF_JOB_OK)
    {
        eBMBoolean = BM_TRUE;
    }
    else
    {
        eMemIfResult = MemIf_WriteSync(ulAddress, (u8*)aulECUSecureBootError, BM_SECURE_BOOT_ERROR_SIZE);
        if (eMemIfResult == MEMIF_JOB_OK)
        {
            eBMBoolean = BM_TRUE;
        }
    }

    return eBMBoolean;
}
