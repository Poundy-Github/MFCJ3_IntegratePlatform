/*===============================================================================*/
/*                                                                               */
/*                               BOOT Layers                                     */
/*                                                                               */
/* ----------------------------------------------------------------------------- */
/*                                                                               */
/*                               BLUpdater layer                                 */
/*                                                                               */
/*===============================================================================*/
/*%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%                                        */
/*%%   _____________________________   %%  \file BLUpdater_Cbk.c                 */
/*%%  |                             |  %%  \brief BLUpdater plugin file          */
/*%%  |   &&&&&   &&&&&             |  %%  Module version: 1.3.0 BL3                */
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
#include "Base_Modules.h"   /* Module enable defines and standard config pointer names */
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
/* - Private Variables                                                           */

/*-------------------------------------------------------------------------------*/
/* - Private Macros                                                              */
#define BLU_SIG                          0x5AA5A55AU

#define BLU_FLASH_STATUS_ADDR_BLU        0x800A0000U
#define BLU_FLASH_STATUS_ADDR_BL         0x80060000U
#define BLU_FLASH_STATUS_SIZE            32U

/*-------------------------------------------------------------------------------*/
/* - Private Function Prototypes                                                 */

/*                                                                               */
/*===============================================================================*/


/*=============================== IMPLEMENTATION ================================*/
/*                                                                               */

/*-------------------------------------------------------------------------------*/
/* - Public Functions                                                            */
/** \brief Callback to set validity marker for New Bootloader
 **
 ** The validity of the New Bootloader shall be saved here
 **
 ** \param[in] eNewBootValidity status to write
 **
 ** \return Result application validation
 ** \retval BLU_TRUE finish successfully
 ** \retval BLU_FALSE Error happened during treatment (ErrorCode shall be filled in this case)
 **/
tBLUBoolean BLU_CustomSetValidityNewBootloader(tBLUBoolean eNewBootValidity)
{
    tBLUBoolean eBLUBoolean;
    tFlashStatus eFlashStatus;
    u8 ubIdx;
    u32 aulFlashStatusValue[BLU_FLASH_STATUS_SIZE / 4U];

    eBLUBoolean = BLU_TRUE;

    LOG(LOG_LEVEL_INFO, "set new bootloader valid");

    if (eNewBootValidity == BLU_TRUE)
    {
        for (ubIdx = 0U; ubIdx < BLU_FLASH_STATUS_SIZE / 4U; ubIdx ++)
        {
            aulFlashStatusValue[ubIdx] = BLU_SIG;
        }

        /* Trigger the Writing job */
        eFlashStatus = FLASH_WriteBuffer(BLU_FLASH_STATUS_ADDR_BL, BLU_FLASH_STATUS_SIZE, (u8*)aulFlashStatusValue);

        /* If an error occurred during the operation */
        while (eFlashStatus == FLASH_BUSY) 
        {
            FLASH_MainFunction();
            eFlashStatus = FLASH_GetJobStatus();
        }

        /* If an error occurred during the operation */
        if (eFlashStatus != FLASH_NO_ERROR)
        {
            /* Indicate that an error is occurred during the Erase */
            eBLUBoolean = BLU_FALSE;
        }
    }

    return eBLUBoolean;
}
/** \brief Callback to set validity marker pf the Bootloader Updater
 **
 ** The validity of the Bootloader Updater shall be saved here
 **
 ** \param[in] eBLUValidity status to write
 **
 ** \return Result application invalidation
 ** \retval BLU_TRUE Treatment finish successfully
 ** \retval BLU_FALSE Error happened during treatment 
 **/
tBLUBoolean BLU_CustomSetValidityBLUpdater(tBLUBoolean eBLUValidity)
{
    tBLUBoolean eBLUBoolean;
    tFlashStatus eFlashStatus;

    eBLUBoolean = BLU_TRUE;

    if (eBLUValidity == BLU_FALSE)
    {
        LOG(LOG_LEVEL_INFO, "set BLU invalidity");

        /* Trigger the Erasing job */
        eFlashStatus = FLASH_EraseSector(BLU_FLASH_STATUS_ADDR_BLU);

        /* If an error occurred during the operation */
        if (eFlashStatus != FLASH_NO_ERROR)
        {
            /* Indicate that an error is occurred during the Erase */
            eBLUBoolean = BLU_FALSE;
        }
    }
    else
    {
        LOG(LOG_LEVEL_ERROR, "Bootloader update failed");
    }

    return eBLUBoolean;
}

/** \brief Callback to get Pdu ID
 ** Get the Rx Pdu Identifier on which the response after reset shall be sent
 **
 ** \param[out] pubRxPduId Rx Pdu Identifier pointer
 **
 **/
void BLU_CustomGetPduID(u16* pubRxPduId)
{
    *pubRxPduId = 0U;
}
/** \brief Callback to trigger the Watchdog
 ** Watchdog can be triggered directly by using this callback.
 **
 **/
void BLU_CustomTriggerWatchdog(void)
{

}

/** \brief Initialization of modules of communication stack
 **
 **/
void BLU_Custom_Com_Init(void)
{
    /* If one of the ASR stack is configured initialize the PduR */
    PduR_Init(BASE_PDUR_CONFIG_PTR);

    /* Start Can Controller */
    Can_Init(&Can_17_McmCan_Config);

    CanIf_Init(BASE_CANIF_CONFIG_PTR);

    CanSM_Init(BASE_CANSM_CONFIG_PTR);

    /* Request for FULL communication */
    (void)CanSM_RequestComMode(0U, COMM_FULL_COMMUNICATION);
}


