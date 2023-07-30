/*********************************************************************************/
/*                                                                               */
/*                                BOOT Layers                                    */
/*                                                                               */
/* ------------------------------------------------------------------------------*/
/*                                                                               */
/*                                 BLUpdater configuration                       */
/*                                                                               */
/*********************************************************************************/
/*%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%                                        */
/*%%   _____________________________   %%  \file BLUpdater_Cfg.c                 */
/*%%  |                             |  %%  \brief BLUpdater layer source plugin file */
/*%%  |   &&&&&   &&&&&             |  %%  Module version: 1.3.0 BL3              */
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

#include "EB_Prj.h"
/*----------------------------------------------------------------------------------*/

/* Description of the bootloader area to erase/Reprogram */
[!AUTOSPACING!]

#ifndef NCS_UNITARY_TEST
const tCfgSegmentType stConfigBootReprog =
#else
tCfgSegmentType stConfigBootReprog =
#endif
{
    [!VAR "START_ADD"="num:inttohex(as:modconf('BLUpdater')/Bootloader_Configuration/Current_Bootloader/Current_Bootloader_Start_Address)"!]
    [!VAR "END_ADD"="num:inttohex(as:modconf('BLUpdater')/Bootloader_Configuration/Current_Bootloader/Current_Bootloader_End_Address)"!]
    [!"$START_ADD"!]U,[!WS "24"!]/* Current Bootloader Start Address */
    [!"$END_ADD"!]U,[!WS "24"!]  /* Current Bootloader End Address */
};

/* Description of the BL image inside the BLU and the marker */
#ifndef NCS_UNITARY_TEST
const tCfgSegmentType stConfigNewBootImage =
#else
tCfgSegmentType stConfigNewBootImage =
#endif
{
    [!VAR "NEW_BOOT_START_ADD"="num:inttohex(as:modconf('BLUpdater')/Bootloader_Configuration/New_Bootloader/New_Bootloader_Start_Address)"!]
    [!VAR "NEW_BOOT_END_ADD"="num:inttohex(as:modconf('BLUpdater')/Bootloader_Configuration/New_Bootloader/New_Bootloader_End_Address)"!]
    [!"$NEW_BOOT_START_ADD"!]U,[!WS "24"!]/* New Bootloader Start Address */
    [!"$NEW_BOOT_END_ADD"!]U,[!WS "24"!]  /* New Bootloader End Address*/
};
