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
/*%%   _____________________________   %%  \file BLUpdater_Cfg.h                 */
/*%%  |                             |  %%  \brief BLUpdater layer include plugin file */
/*%%  |   &&&&&   &&&&&             |  %%  Module version: 1.3.0 BL3                */
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

#ifndef BLUPDATER_CFG_H
#define BLUPDATER_CFG_H

#ifndef NCS_UNITARY_TEST
extern const tCfgSegmentType stConfigBootReprog;
extern const tCfgSegmentType stConfigNewBootImage;
#else
extern tCfgSegmentType stConfigBootReprog;
extern tCfgSegmentType stConfigNewBootImage;
#endif

[!AUTOSPACING!]
/* Define Pdu for transmition */
[!LOOP "PduConnection/*[LinConnection = 'false']"!]
#define  BLU_[!"name(node:ref(TxPduRef))"!]
[!ENDLOOP!]

#define BLU_MANAGE_PERIOD        [!WS "30"!][!"num:dectoint(General/BLU_MANAGE_PERIOD)"!]U

[!IF "(General/BLU_Communication_Support = 'true')"!]
#define BLU_NRC78_SENDING_PERIOD [!WS "23"!]([!"num:dectoint(General/NRC78_Sending_Period)"!]U/BLU_MANAGE_PERIOD)
[!ENDIF!]
 
[!IF "(Security/SecureBoot/SECURE_BOOT = 'true')"!]
#define BLU_SECURE_BOOT [!WS "16"!]STD_ON
#define BLU_BOOT_START_ADDR                  ([!"num:inttohex(Security/SecureBoot/BootCksStartAddress)"!]U)
#define BLU_BOOT_LENGTH                      ([!"num:inttohex(Security/SecureBoot/BootCksRangeLength)"!]U)
[!ELSE!]
#define BLU_SECURE_BOOT [!WS "16"!]STD_OFF
[!ENDIF!]

[!IF "(General/BLU_Communication_Support = 'true')"!]
#define BLU_COMMUNICATION_SUPPORT STD_ON
[!ELSE!]
#define BLU_COMMUNICATION_SUPPORT STD_OFF
[!ENDIF!]
#endif /* BLUpdater_CFG_H */
