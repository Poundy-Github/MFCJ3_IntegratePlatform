/*********************************************************************************/
/*                                                                               */
/*                                  CAN Stack                                    */
/*                                                                               */
/* ------------------------------------------------------------------------------*/
/*                                                                               */
/*                                 APP configuration                             */
/*                                                                               */
/*********************************************************************************/
/*%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%                                        */
/*%%   _____________________________   %%  \file APP_Types.h                     */
/*%%  |                             |  %%  \brief APP layer types  */
/*%%  |   &&&&&   &&&&&             |  %%  Module version: 3.6.8 BL-3.X                */
/*%%  |   &       &    &            |  %%                                        */
/*%%  |   &&&&    &&&&&             |  %%                                        */
/*%%  |   &       &    &            |  %%                                        */
/*%%  |   &&&&&   &&&&&             |  %%                                        */
/*%%  |_____________________________|  %%                                        */
/*%%                                   %%                                        */
/*%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%                                        */
/*********************************************************************************/
/* Copyright 2010 by Elektrobit Automotive GmbH                                  */
/* All rights exclusively reserved for Elektrobit Automotive GmbH,               */
/* unless expressly agreed to otherwise.                                         */
/*********************************************************************************/

#ifndef APP_TYPES_H
#define APP_TYPES_H

/** \brief Define APP_FALSE */
#define APP_FALSE               0U
/** \brief Define APP_TRUE */
#define APP_TRUE                1U
/** \brief definition of the tAppBoolean */
typedef u8 tAppBoolean;

/** \brief Define SOFT_RESET */
#define SOFT_RESET 0x00U
/** \brief Define POWER_ON */
#define POWER_ON   0x01U

#define APP_SIG  0x5AA5A55AU

#define APP_ECU_SOFTWARE_AREA_A       0x00U
#define APP_ECU_SOFTWARE_AREA_B       0x01U

//update log address
#define APP_SECURE_UPDATING_LOG_ADDRESS                     0xAF07C028U
#define APP_SECURE_UPDATING_LOG_SIZE                        8U
//Part number address
#define APP_PART_NUMBER_ADDRESS                             0xAF07D028U
#define APP_PART_NUMBER_SIZE                                7U
//HW VERSION address
#define APP_HW_VERSION_ADDRESS                              0xAF07D068U
#define APP_HW_VERSION_SIZE                                 8U
//start error flag address
#define APP_ECU_SECURE_BOOT_ERROR_ADDRESS                   0xAF07E028U
#define APP_ECU_SECURE_BOOT_ERROR_SIZE                      8U
//AB bank start flag address 
#define APP_ECU_SOFTWARE_AREA_ADDRESS                       0xAF07F028U
#define APP_ECU_SOFTWARE_AREA_SIZE                          8U

#define APP_BOOTLOADER_VERSION_SIZE                         5U
#define APP_FLASH_DRIVER_PART_NUMBER_SIZE                   10U
#define APP_ECU_PART_NUMBER_SIZE                            14U

#define ATTEMPT_DOWNLOADING_COUNTER                         0U
#define FLASH_DRIVER_ACTIVATED_SUCCESSFULLY_COUNTER         1U
#define APP_DOWNLOADED_SUCCESSFULLY_COUNTER                 2U
#define FBL_DOWNLOADED_SUCCESSFULLY_COUNTER                 3U

#define APP_SHARED_MEMORY_ADDR                              (0x80104080U)
#define FBL_SPEC_VERSION_SIZE                               (4U)

#define APP_ECU_SOFTWARE_PART_NUMBER_OFFSET                 0x40U
#define APP_ECU_SOFTWARE_PART_NUMBER_SIZE                   20U
#define APP_ECU_SOFTWARE_VERSION_OFFSET                     0x60U
#define APP_ECU_SOFTWARE_VERSION_SIZE                       8U


typedef void (*ptAPPL_START_ADDR)(void);

#endif      /* APP_TYPES_H */
