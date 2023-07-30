/*===============================================================================*/
/*                                                                               */
/*                               BOOT Layers                                     */
/*                                                                               */
/* ----------------------------------------------------------------------------- */
/*                                                                               */
/*                               UDS layer                                      */
/*                                                                               */
/*===============================================================================*/
/*%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%                                        */
/*%%   _____________________________   %%  \file UDS_Cbk.c                      */
/*%%  |                             |  %%  \brief UDS layer source plugin file  */
/*%%  |   &&&&&   &&&&&             |  %%  Module version: 3.8.2 BL-3.X */
/*%%  |   &       &    &            |  %%                                        */
/*%%  |   &&&&    &&&&&             |  %%                                        */
/*%%  |   &       &    &            |  %%                                        */
/*%%  |   &&&&&   &&&&&             |  %%                                        */
/*%%  |_____________________________|  %%                                        */
/*%%                                   %%                                        */
/*%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%                                        */
/*===============================================================================*/
/* Copyright 2015 by Elektrobit Automotive GmbH                                  */
/* All rights exclusively reserved for Elektrobit Automotive GmbH,               */
/* unless expressly agreed to otherwise.                                         */
/*===============================================================================*/

/*=============================== FILE INCLUSION ================================*/
/*                                                                               */
#include "EB_Prj.h"
#include "board.h"
#include "log.h"
/*=============================== IMPLEMENTATION ================================*/
/*                                                                               */

void UDS_CustomPositiveAnswerInd (const u16 *puwLen, const u8 *aubUdsData)
{
    // if (aubUdsData[0] == 0x71)
    // {
    //     LOG(LOG_LEVEL_INFO, "UDS_CustomPositiveAnswerInd data = 0x%02x 0x%02x 0x%02x 0x%02x ",aubUdsData[0], aubUdsData[1],aubUdsData[2],aubUdsData[3]);
    // }
}






