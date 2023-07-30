/*===============================================================================*/
/*                                                                               */
/*                               BOOT Layers                                     */
/*                                                                               */
/* ----------------------------------------------------------------------------- */
/*                                                                               */
/*                               PROG layer                                      */
/*                                                                               */
/*===============================================================================*/
/*%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%                                        */
/*%%   _____________________________   %%  \file PROG_Responses.c                */
/*%%  |                             |  %%  \brief PROG layer source plugin file  */
/*%%  |   &&&&&   &&&&&             |  %%  Module version: 2.3.255 BL-3.X */
/*%%  |   &       &    &            |  %%                                        */
/*%%  |   &&&&    &&&&&             |  %%                                        */
/*%%  |   &       &    &            |  %%                                        */
/*%%  |   &&&&&   &&&&&             |  %%                                        */
/*%%  |_____________________________|  %%                                        */
/*%%                                   %%                                        */
/*%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%                                        */
/*===============================================================================*/
/* Copyright 2017 by Elektrobit Automotive GmbH                                  */
/* All rights exclusively reserved for Elektrobit Automotive GmbH,               */
/* unless expressly agreed to otherwise.                                         */
/*===============================================================================*/
/*=============================== FILE INCLUSION ================================*/
/*                                                                               */
#include "EB_Prj.h"
#include "PROG_Hsm.h"
#include "PROG_HsmPROG.h"
#include "board.h"
/*=============================== IMPLEMENTATION ================================*/
/*                                                                               */

void PROG_Custom_EraseRoutine_Succeed(u8 * Data, u16 * DataLength)
{
  /*No Change*/
  
}

void PROG_Custom_EraseRoutine_Failed(u8 * Data, u16 * DataLength, tUdsStatus * eUdsStatus)
{
  /*No Change*/
  
}

void PROG_Custom_CheckMemoryRoutine_Succeed(u8 * Data, u16 * DataLength)
{
  /*No Change*/
 
}

void PROG_Custom_CheckMemoryRoutine_Failed(u8 * Data, u16 * DataLength, tUdsStatus * eUdsStatus)
{
  /*No Change*/
  
}


void PROG_Custom_PreCondCheckRoutine_Succeed(u8 * Data, u16 * DataLength)
{
  /*No Change*/
   
}

void PROG_Custom_PreCondCheckRoutine_Failed(u8 * Data, u16 * DataLength, tUdsStatus * eUdsStatus)
{
  /*No Change*/
  
}

void PROG_Custom_CheckProgDepRoutine_Succeed(u8 * Data, u16 * DataLength)
{
  /* Remove status */
  *DataLength = *DataLength -1;
   
}

void PROG_Custom_CheckProgDepRoutine_Failed(u8 * Data, u16 * DataLength, tUdsStatus * eUdsStatus)
{
  /*No Change*/
  
}
