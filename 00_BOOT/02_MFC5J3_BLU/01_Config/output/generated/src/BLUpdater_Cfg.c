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

#ifndef NCS_UNITARY_TEST
const tCfgSegmentType stConfigBootReprog =
#else
tCfgSegmentType stConfigBootReprog =
#endif
{
    0x80060100U,                        /* Current Bootloader Start Address */
    0x8009ffffU,                        /* Current Bootloader End Address */
};

/* Description of the BL image inside the BLU and the marker */
#ifndef NCS_UNITARY_TEST
const tCfgSegmentType stConfigNewBootImage =
#else
tCfgSegmentType stConfigNewBootImage =
#endif
{
    0x800c0100U,                        /* New Bootloader Start Address */
    0x800fffffU,                        /* New Bootloader End Address*/
};
