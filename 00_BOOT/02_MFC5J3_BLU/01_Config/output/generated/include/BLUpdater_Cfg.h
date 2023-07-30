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

/* Define Pdu for transmition */
#define  BLU_Pdu_Tx_Uds

#define BLU_MANAGE_PERIOD                              1U

#define BLU_NRC78_SENDING_PERIOD                       (2000U/BLU_MANAGE_PERIOD)
 

#define BLU_SECURE_BOOT                STD_OFF

#define BLU_COMMUNICATION_SUPPORT STD_ON
#endif /* BLUpdater_CFG_H */
