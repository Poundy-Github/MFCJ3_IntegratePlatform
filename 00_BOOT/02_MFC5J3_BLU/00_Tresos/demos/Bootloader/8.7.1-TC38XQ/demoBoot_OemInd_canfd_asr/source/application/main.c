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

#include <Base_Modules.h>   /* Module enable defines and standard config pointer names */
#include <Port.h>   /* Module enable defines and standard config pointer names */
#include <Mcu.h>

/******************************** DEFINES & VARIABLES ****************************/
/*                                                                               */
/*-------------------------------------------------------------------------------*/

/*-------------------------------------------------------------------------------*/
/* Following define are necessary to set CAN_MOIPR to wanted Interrupt vectors   */
/* MODULE_CAN  => Base Address of the CAN for TRICORE 277                        */
/* RXINP_02    => Bit to set to select Interrupt Output 2 in Rx                  */
/* TXINP_01    => Bit to set to select Interrupt Output 1 in Tx                  */
/* SET_RXTXINP => Mask to apply to select only bit of Rx and Tx interruption     */
/*-------------------------------------------------------------------------------*/
#define MODULE_CAN_BASE             (u32)0xF0018000u
#define RXINP_02                    (u32)0x00000002u
#define TXINP_01                    (u32)0x00000010u
#define SET_RXTXINP                 (u32)0xFFFFFF00u
#define CAN_MOIPR_PTR_REG32(n)      *(volatile u32 *) ((MODULE_CAN_BASE)+(0x1008ul + (((u32)(n)) * 0x20u)))

void main(void)
{
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
    /* Initialization of Port */
    Port_Init(&Port_Config);

    /* Initialization of EB Stack */
    BM_StartUp();


    /*------------------------------------------------------------*/
    /* As the MCAL doesn't allow to do this, it is necessary      */
    /* to map the following Message Object as following:          */
    /* Message Object 0 => Tx to O1                               */
    /*                     Rx to O2                               */
    /* Message Object 1 => Tx to O1                               */
    /*                     Rx to O2                               */
    /* Message Object 2 => Tx to O1                               */
    /*                     Rx to O2                               */
    /*------------------------------------------------------------*/
    /* In the UM of the TC27x, see:                               */
    /*  - Figure 22-33 Interrupt Compressor                       */
    /*  - §22.6.3 - CAN_MOIPRn register                           */
    /*------------------------------------------------------------*/
    /* Vector O1 and O2 are chosen according to:                  */
    /* - interrupt table defined in TriboardTC277/vector_vle_eb.s */
    /* - API defined to CAN Rx and Tx interruption in board_irq.c */
    /* - Mapping between Priority and Interrupt Output defined    */
    /*   in board.c                                               */
    /*   (PLATFORMS_SRC_CANINT0 to PLATFORMS_SRC_CANINT15)        */
    /*------------------------------------------------------------*/
    /* In board.c:                                                */
    /* - API BoardCan0Interrupt1 is defined for CAN Tx            */
    /* - API BoardCan0Interrupt2 is defined for CAN Rx            */
    /*------------------------------------------------------------*/
    /* In board_irq.c:                                            */
    /* - BOARD_GEN_VECTOR(Board_Prio3_ISR, 3, BoardCan0Interrupt1)*/
    /* - BOARD_GEN_VECTOR(Board_Prio4_ISR, 4, BoardCan0Interrupt2)*/
    /*------------------------------------------------------------*/
    // CAN_MOIPR_PTR_REG32(0U) = (CAN_MOIPR_PTR_REG32(0U) & SET_RXTXINP) | RXINP_02 | TXINP_01;
    // CAN_MOIPR_PTR_REG32(1U) = (CAN_MOIPR_PTR_REG32(1U) & SET_RXTXINP) | RXINP_02 | TXINP_01;
    // CAN_MOIPR_PTR_REG32(2U) = (CAN_MOIPR_PTR_REG32(2U) & SET_RXTXINP) | RXINP_02 | TXINP_01;
    // CAN_MOIPR_PTR_REG32(3U) = (CAN_MOIPR_PTR_REG32(3U) & SET_RXTXINP) | RXINP_02 | TXINP_01;
    // CAN_MOIPR_PTR_REG32(4U) = (CAN_MOIPR_PTR_REG32(4U) & SET_RXTXINP) | RXINP_02 | TXINP_01;
    // CAN_MOIPR_PTR_REG32(5U) = (CAN_MOIPR_PTR_REG32(5U) & SET_RXTXINP) | RXINP_02 | TXINP_01;
    // CAN_MOIPR_PTR_REG32(6U) = (CAN_MOIPR_PTR_REG32(6U) & SET_RXTXINP) | RXINP_02 | TXINP_01;
    // CAN_MOIPR_PTR_REG32(7U) = (CAN_MOIPR_PTR_REG32(7U) & SET_RXTXINP) | RXINP_02 | TXINP_01;
    // CAN_MOIPR_PTR_REG32(8U) = (CAN_MOIPR_PTR_REG32(8U) & SET_RXTXINP) | RXINP_02 | TXINP_01;
    // CAN_MOIPR_PTR_REG32(9U) = (CAN_MOIPR_PTR_REG32(9U) & SET_RXTXINP) | RXINP_02 | TXINP_01;


    /* Starting from there we known that the Application is NOT valid OR a Downloading is requested */

    /* Endless loop */
    for(;;)
    {

        /* Scheduler timer */
        if (BoardSchedulingTimer() == 0x01U)
        {
            /* CAN Application cyclic task */
            APP_Manage();
            BlPduR_Manage();
        }
        /* Call the prog_hsm main function */
        PROG_BckdManage();
    }
}
