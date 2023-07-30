/**
 * \file
 *
 * \brief Bootloader Updater
 *
 * This file contains the implementation of the Bootloader
 * Updater module.
 *
 * \author Elektrobit Automotive GmbH, 91058 Erlangen, Germany
 *
 * Copyright 2005 - 2016 Elektrobit Automotive GmbH
 * All rights exclusively reserved for Elektrobit Automotive GmbH,
 * unless expressly agreed to otherwise.
 */

/*==================[inclusions]============================================*/


#include "EB_prj.h"
#include "board.h"
#include "Base_Modules.h"   /* Module enable defines and standard config pointer names */
#include "Port.h"
#include "Mcu.h"
#include "I2c.h"
#include "sbc_fs8x.h"
#include "log.h"

/******************************** DEFINES & VARIABLES ****************************/
/*                                                                               */
/*-------------------------------------------------------------------------------*/
#define LOG_MANAGE_PERIOD            1000U

NCS_PRI_VAR u16 m_uwLogManageCnt;

void main(void)
{
    LOG_OPEN();

    u8 Error_CountValue = 0;
    fs8x_drv_data_t drvConfig = {0};

    LOG(LOG_LEVEL_INFO, "Mcu_Init");
    Mcu_Init(&Mcu_Config);
    /* ignore return value (always E_NOT_OK). ERAY Pll is not supported for TC22
    * but the function tries to configure it anyway with 0 values. */
    (void)Mcu_InitClock(McuConf_McuClockSettingConfig_McuClockSettingConfig_0);

     /* Wait until the PLL is locked */
    while (MCU_PLL_LOCKED != Mcu_GetPllStatus())
    {
    ;
    }

     /* Activate the PLL Clock */
    Mcu_DistributePllClock();

    LOG(LOG_LEVEL_INFO, "Port_Init");
    /* Initialization of Port */
    Port_Init(&Port_Config);

    LOG(LOG_LEVEL_INFO, "Close watchdog");

    I2c_Init(&I2c_Config);

    /*FS8435 watchdog init*/
    loadDefaultDriverConfig(&drvConfig);
    sbcInitStart(&drvConfig);
    sbcInitClose(&drvConfig);

    FS8x_GetFaultErrorCounterValue(&drvConfig, &Error_CountValue);
    LOG(LOG_LEVEL_INFO, "Error_CountValue %d", Error_CountValue);
    for(u8 i = 0U; i <= (6U * Error_CountValue); i++)
    {
        FS8x_WD_Refresh(&drvConfig);
    }

    /* Try to release the FS0b pin. */
    FS8x_FS0B_Release(&drvConfig);

    FS8x_WD_Refresh(&drvConfig);            //Refresh wd make sure the WD refresh time in 256ms.
    GOTO_INITFS(&drvConfig);                //FS8435 goto INITFS function
    Disable_WD(&drvConfig);                 //FS8435 disable WD ,allow bootloader to download.
    sbcInitClose(&drvConfig);               //FS8435 first WD refesh and exit INITFS

    BoardDisableECCCheck();

    /* Initialization of EB Stack */
    LOG(LOG_LEVEL_INFO, "BLU_Init");
    BLU_Init();

    LOG(LOG_LEVEL_INFO, "Endless loop");

    /* Endless loop */
    for(;;)
    {
        /* Scheduler timer */
        if (BoardSchedulingTimer() == 0x01U)
        {
            BLU_Manage(); 

            m_uwLogManageCnt ++;
            if (m_uwLogManageCnt >= LOG_MANAGE_PERIOD)
            {
                m_uwLogManageCnt = 0U;

                LOG(LOG_LEVEL_INFO, "loop");
            } 
        }

        BLU_Start();
    }
}
