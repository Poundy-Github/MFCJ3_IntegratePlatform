/*********************************************************************************/
/*                                                                               */
/*                               BOOT layers                                     */
/*                                                                               */
/* ----------------------------------------------------------------------------- */
/*                                                                               */
/*                                 FLASH configuration                           */
/*                                                                               */
/*********************************************************************************/
/*%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%                                        */
/*%%   _____________________________   %%  \file FLASH_Cfg.h                     */
/*%%  |                             |  %%  \brief FLASH layer implementation     */
/*%%  |   &&&&&   &&&&&             |  %%  Module version: 7.1.6                 */
/*%%  |   &       &    &            |  %%                                        */
/*%%  |   &&&&    &&&&&             |  %%                                        */
/*%%  |   &       &    &            |  %%                                        */
/*%%  |   &&&&&   &&&&&             |  %%                                        */
/*%%  |_____________________________|  %%                                        */
/*%%                                   %%                                        */
/*%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%                                        */
/*********************************************************************************/
/* Copyright 2017 by Elektrobit Automotive GmbH                                  */
/* All rights exclusively reserved for Elektrobit Automotive GmbH,               */
/* unless expressly agreed to otherwise.                                         */
/*********************************************************************************/




#ifndef FLASH_CBK_H
#define FLASH_CBK_H

/* Operation Callback prototype */
[!IF "General/Operation_Callback != 'NULL_CALLBACK'"!]
#define FLSLOADER_START_SEC_WRITE_CODE
#include <MemMap.h>
extern void [!"General/Operation_Callback"!](void);
#define FLSLOADER_STOP_SEC_WRITE_CODE
#include <MemMap.h>
[!ELSE!]
[!ENDIF!]

#endif      /* FLASH_CBK_H */
