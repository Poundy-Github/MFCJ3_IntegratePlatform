/*===============================================================================*/
/*                                                                               */
/*                                 FLASH configuration                           */
/*                                                                               */
/*===============================================================================*/
/*%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%                                        */
/*%%   _____________________________   %%  \file FLASH_Cfg.c                     */
/*%%  |                             |  %%  \brief FLASH layer implementation     */
/*%%  |   &&&&&   &&&&&             |  %%  Module version: 7.1.6                 */
/*%%  |   &       &    &            |  %%  TARGET: TRICORE                     */
/*%%  |   &&&&    &&&&&             |  %%  DERIVATE: TC38XQ                 */
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
[!AUTOSPACING!]



/*=============================== FILE INCLUSION ================================*/
/*                                                                               */
/*-------------------------------------------------------------------------------*/
/* - Header Files: PROG                                                          */

#include "EB_Prj.h"
/*                                                                               */
/*********************************************************************************/

const tFlsInfo Fls_Info[FLASH_MAX_SECTOR] =
{
    /* Start_Address       Length           Number          Programmable */

[!IF "General/UseSectorTab = 'true'"!]
[!VAR "SECTOR_MAX"="num:dectoint(count(FlsSector/*))"!]
[!IF "$SECTOR_MAX = 0"!]
[!ERROR "At least one FlsSector must be configured!!!"!]
[!ENDIF!]
[!FOR "SECTOR_IDX" = "1" TO "$SECTOR_MAX"!]
[!WS "5"!]{[!"num:inttohex(FlsSector/*[number($SECTOR_IDX)]/Start_Address,8)"!]U,[!WS "10"!][!"num:inttohex(FlsSector/*[number($SECTOR_IDX)]/Length,5)"!]U,[!WS "10"!][!"num:inttohex(FlsSector/*[number($SECTOR_IDX)]/Consecutive,4)"!]U,[!WS "10"!][!IF "(FlsSector/*[number($SECTOR_IDX)]/Programmable='true')"!] TRUE[!ELSE!] FALSE[!ENDIF!]},
[!ENDFOR!]
};


[!ENDIF!]

[!IF "General/ActivateSecurityCheck = 'true'"!]
const tFlashActivateSecurityCheck astFlashMemoryAreas[FLASH_MAX_PROTECTED_AREA_NB] =
{
    /* Start_Address       Length */

[!VAR "PROTECTED_AREA_MAX"="num:dectoint(count(FlashMemoryAreasProtection/*))"!]
[!FOR "PROTECTED_AREA_IDX" = "1" TO "$PROTECTED_AREA_MAX"!]
[!WS "4"!]{[!"num:inttohex(FlashMemoryAreasProtection/*[number($PROTECTED_AREA_IDX)]/Start_Address,8)"!]U,[!WS "10"!][!"num:inttohex(FlashMemoryAreasProtection/*[number($PROTECTED_AREA_IDX)]/Length,5)"!]U,}, 
[!ENDFOR!]
};
[!ENDIF!]
