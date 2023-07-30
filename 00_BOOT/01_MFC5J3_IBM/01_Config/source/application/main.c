/**
 * \file
 *
 * \brief Bootloader Demo
 *
 * This file contains the implementation of the Bootloader
 * module Demo.
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
#include "Mcu.h"
#include "log.h" 

/******************************** DEFINES & VARIABLES ****************************/
/*                                                                               */
/*-------------------------------------------------------------------------------*/
extern const u8 m_auReleaseVersion[16];
#define LOG_MANAGE_PERIOD            1000U

NCS_PRI_VAR u16 m_uwLogManageCnt;

void main(void)
{
    LOG_OPEN();

    LOG(LOG_LEVEL_INFO, "Mcu_Init");
    LOG(LOG_LEVEL_INFO, "BLU ReleaseVersion is %s",m_auReleaseVersion);

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

    MemIf_Init();

    /* Boot start up */
    LOG(LOG_LEVEL_INFO, "BM_InitialBootStartUp");
    BM_InitialBootStartUp();

    LOG(LOG_LEVEL_INFO, "Endless loop");

    /* Endless loop */
    for(;;)
    {
        /* Scheduler timer */
        if (BoardSchedulingTimer() == 0x01U)
        {
            m_uwLogManageCnt ++;
            if (m_uwLogManageCnt >= LOG_MANAGE_PERIOD)
            {
                m_uwLogManageCnt = 0U;

                LOG(LOG_LEVEL_INFO, "loop");
            }
        }
    }
}
