/*===============================================================================*/
/*                                                                               */
/*                               BOOT Layers                                     */
/*                                                                               */
/* ----------------------------------------------------------------------------- */
/*                                                                               */
/*                               SA layer                                        */
/*                                                                               */
/*===============================================================================*/
/*%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%                                        */
/*%%   _____________________________   %%  \file SA_Cbk.c                        */
/*%%  |                             |  %%  \brief SA layer source plugin file    */
/*%%  |   &&&&&   &&&&&             |  %%  Module version: 1.0.255 OSC_BOOT */
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

/*=============================== IMPLEMENTATION ================================*/
/*                                                                               */
/*--------------------------------{SA_CustomCalculateKey}------------------------*/
void SA_CustomCalculateKey(u8 * aubSeed, u8 * m_aubCalculatedKey)
{
  OSC_PARAM_UNUSED(aubSeed);
  m_aubCalculatedKey[0] = 0x01;
  m_aubCalculatedKey[1] = 0x02;
  m_aubCalculatedKey[2] = 0x03;
  m_aubCalculatedKey[3] = 0x04;
}
/*------------------------------{end SA_CustomCalculateKey}----------------------*/

/*--------------------------------{SA_CustomStoreAsRetryCnt}---------------------*/
#if (SA_ANTISCANNING_ENABLED == STD_ON) 
void SA_CustomStoreAsRetryCnt(u8 RetryCntValue)
{
    OSC_PARAM_UNUSED(RetryCntValue);
}
#endif /*(PROG_SA_ANTISCANNING_ENABLE == STD_ON)*/
/*------------------------------{end SA_CustomStoreAsRetryCnt}-------------------*/

/*--------------------------------{SA_CustomRestoreAsRetryCnt}-------------------*/
#if (SA_ANTISCANNING_ENABLED == STD_ON) 
u8 SA_CustomRestoreAsRetryCnt(void)
{
    u8 RetAsRetryCnt = 0;
    
    /*Fetch from NVM*/
    return RetAsRetryCnt;
}
#endif /*(PROG_SA_ANTISCANNING_ENABLE == STD_ON)*/
/*------------------------------{end SA_CustomRestoreAsRetryCnt}-----------------*/

