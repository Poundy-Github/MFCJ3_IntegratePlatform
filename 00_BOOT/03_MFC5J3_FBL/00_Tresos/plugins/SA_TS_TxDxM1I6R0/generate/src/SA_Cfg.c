/*********************************************************************************/
/*                                                                               */
/*                                 Sa LAYER                                      */
/*                                                                               */
/* ----------------------------------------------------------------------------- */
/*                                                                               */
/*                               Security Access                                 */
/*                                                                               */
/*********************************************************************************/
/*%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%                                        */
/*%%   _____________________________   %%  \file SA_Cfg.c                        */
/*%%  |                             |  %%                                        */
/*%%  |   &&&&&   &&&&&             |  %%  Module version: 1.6.3 BL-3.X */
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



/******************************** FILE INCLUSION *********************************/
/*                                                                               */
#include "EB_Prj.h"
[!AUTOSPACING!]

[!IF "node:exists(as:modconf('ProgJLR')) or node:exists(as:modconf('ProgVCC'))"!]
const u8 m_aubStaticKey[SA_STATIC_KEY_LEN] = {[!"num:inttohex(General/Static_Key_0)"!]U, [!"num:inttohex(General/Static_Key_1)"!]U, [!"num:inttohex(General/Static_Key_2)"!]U, [!"num:inttohex(General/Static_Key_3)"!]U, [!"num:inttohex(General/Static_Key_4)"!]U};
[!ENDIF!]

