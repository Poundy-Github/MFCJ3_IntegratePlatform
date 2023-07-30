/*********************************************************************************/
/*                                                                               */
/*                                BOOT Layers                                    */
/*                                                                               */
/* ------------------------------------------------------------------------------*/
/*                                                                               */
/*                                 BM configuration                              */
/*                                                                               */
/*********************************************************************************/
/*%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%                                        */
/*%%   _____________________________   %%  \file BM_Cfg.h                        */
/*%%  |                             |  %%  \brief BM layer include plugin file   */
/*%%  |   &&&&&   &&&&&             |  %%  Module version: 1.15.0 BL3                */
/*%%  |   &       &    &            |  %%  Variant: OsekCore                  */
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

#ifndef BM_CFG_H
#define BM_CFG_H

#define BM_IMPL_10                          10U
#define BM_IMPL_NOT_DEFINED                 255U


#define BM_IMPL_VARIANT                     BM_IMPL_NOT_DEFINED


#define BM_EXECUTE_TESTAPPL                 STD_OFF

#define BM_BOOT_MANAGER_VARIANT             BM_INITIAL_BOOT_MANAGER
#define BM_INITIAL_BOOT_APPLICATION_VALIDITY_CHECK        STD_OFF


/* BM Authenticated Boot/Secure Boot information */
#define BM_AUTHENTICATED_BOOT_ENABLE        STD_OFF
#define BM_SECURE_BOOT_ENABLE               STD_OFF
#define BM_BOOT_CHECKSUM_VERIFICATION       STD_OFF


#define BM_CSM_MAC_USED                     STD_OFF
#define BM_CSM_HASH_USED                    STD_OFF


#define BM_HSM_MAC_USED                     STD_OFF


#endif /* BM_CFG_H */
