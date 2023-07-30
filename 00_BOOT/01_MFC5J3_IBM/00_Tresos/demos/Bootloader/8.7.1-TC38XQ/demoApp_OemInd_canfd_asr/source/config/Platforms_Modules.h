/**
 * \file
 *
 * \brief Autosar ApplTemplates
 *
 * This file contains the implementation of the Autosar
 * module ApplTemplates.
 *
 * \author Elektrobit Automotive GmbH, 91058 Erlangen, Germany
 *
 * Copyright 2005 - 2012 Elektrobit Automotive GmbH
 * All rights exclusively reserved for Elektrobit Automotive GmbH,
 * unless expressly agreed to otherwise.
 */

#ifndef PLATFORMS_MODULES_H
#define PLATFORMS_MODULES_H

/*==================[includes]==============================================*/

/*==================[macros]================================================*/

/*
 * Here you can define platform-specific names for init functions
 * and configuration pointer names when modules require other init function
 * names or configuration pointer names than defined in BswM_Modules.h
 * or Base_Modules.h.
 */

#define SPI_INIT_FUNC         Spi_Init
#define BASE_SPI_CONFIG_PTR   &Spi_GstConfiguration[0]

#define FLS_INIT_FUNC         Fls_Init
#define BASE_FLS_CONFIG_PTR   &Fls_GstConfiguration[0]

#define FEE_INIT_FUNC         Fee_Init
#define BASE_FEE_CONFIG_PTR

#define CAN_INIT_FUNC         Can_Init
#define BASE_CAN_CONFIG_PTR   (&Can_17_MCanP_ConfigRoot[0U])

#define LIN_INIT_FUNC
#define BASE_LIN_CONFIG_PTR

#define FR_INIT_FUNC          Fr_Init
/* For Renesas FlexRay driver comment next line in */
/*#define BASE_FR_CONFIG_PTR    &Fr_GstConfiguration[0]*/
/* For EB FlexRay driver comment next line in */
#define BASE_FR_CONFIG_PTR    &FrMultipleConfiguration

#define ETH_INIT_FUNC
#define BASE_ETH_CONFIG_PTR

/* EcuM basicTempalte cfg is using following defines to keep them common */
#define BASE_MCU_CONFIG_PTR   &Mcu_GstConfiguration[0]

#ifndef MCU_CLOCK_CFG_PARAM
#define MCU_CLOCK_CFG_PARAM 1U
#endif


/*==================[type definitions]======================================*/

/*==================[external function declarations]========================*/

/*==================[internal function declarations]========================*/

/*==================[external constants]====================================*/

/*==================[internal constants]====================================*/

/*==================[external data]=========================================*/

/*==================[internal data]=========================================*/

/*==================[external function definitions]=========================*/

/*==================[internal function definitions]=========================*/

#endif /* ifndef PLATFORMS_MODULES_H */

/*==================[end of file]===========================================*/
