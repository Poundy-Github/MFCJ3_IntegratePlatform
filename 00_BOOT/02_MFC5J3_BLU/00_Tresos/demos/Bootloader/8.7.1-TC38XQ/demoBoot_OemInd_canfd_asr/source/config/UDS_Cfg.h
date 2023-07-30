/*********************************************************************************/
/*                                                                               */
/*                                  CAN Stack                                    */
/*                                                                               */
/* ----------------------------------------------------------------------------- */
/*                                                                               */
/*                               UDS configuration                               */
/*                                                                               */
/*********************************************************************************/
/*%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%                                        */
/*%%   _____________________________   %%  \file UDS_Cfg.h                       */
/*%%  |                             |  %%                                        */
/*%%  |   &&&&&   &&&&&             |  %%  Module version: 3.9.2 BL-3.X */
/*%%  |   &       &    &            |  %%  Variant: ISO                  */
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



#ifndef UDS_CFG_H
#define UDS_CFG_H





/****************************** PUBLIC DEFINITIONS *******************************/
/*                                                                               */
/*-------------------------------------------------------------------------------*/
/* - Configuration Constants                                                     */

/* Define if NRC 7E is implemented for RC request */
#define RC_NRC_IMPLEMENTATION            0x31U

/* DID implemented in other session and session supported by the service */
#define UDS_NRC_INVALID_DID            0x31U

/* Define NRC78 first timing */
#define UDS_P2_ADJUST             45U

/* Define NRC78 period */
#define UDS_P2STAR_ADJUST            0U

/* for compatibility for older modules version, keep all these defines */
#define UDS_SESSION_DEFAULT            m_stSessionInfo[UDS_DEFAULT_SESSION_INDEX].ubSessionValue
#define UDS_SESSION_PROGRAMMING            m_stSessionInfo[UDS_PROGRAMMING_SESSION_INDEX].ubSessionValue
#define UDS_SESSION_EXTENDED_DIAG            m_stSessionInfo[UDS_EXTENDED_SESSION_INDEX].ubSessionValue
#define UDS_SESSION_SUPPLIER            m_stSessionInfo[UDS_SUPPLIER_SESSION_INDEX].ubSessionValue
#define UDS_SESSION_OTHER_01            m_stSessionInfo[UDS_OTHER_01_SESSION_INDEX].ubSessionValue
#define UDS_SESSION_OTHER_02            m_stSessionInfo[UDS_OTHER_02_SESSION_INDEX].ubSessionValue
#define UDS_SESSION_OTHER_03            m_stSessionInfo[UDS_OTHER_03_SESSION_INDEX].ubSessionValue
#define UDS_SESSION_OTHER_04            m_stSessionInfo[UDS_OTHER_04_SESSION_INDEX].ubSessionValue

#define UDS_SUPPLIERSERVICE_BA            STD_OFF
#define UDS_SUPPLIERSERVICE_BB            STD_OFF
#define UDS_SUPPLIERSERVICE_BC            STD_OFF
#define UDS_SUPPLIERSERVICE_BD            STD_OFF
#define UDS_SUPPLIERSERVICE_BE            STD_OFF

/*-------------------------------------------------------------------------------*/
/* - Configuration Variable or Register Aliases                                  */



/*-------------------------------------------------------------------------------*/
/* - Public Constants                                                            */

extern const tUdsSessionInfo m_stSessionInfo[UDS_CONFIGURABLE_SESSION_MAX];

/*-------------------------------------------------------------------------------*/
/* - Public Types                                                                */


/*-------------------------------------------------------------------------------*/
/* - Public Macros                                                               */
#define UDS_SECURITY_LEVEL_CHECK_CBK            PROG_GetSecurityLevel

#define UDS_FULL_RESPONSEPENDING                    STD_ON


#define UDS_EXT_RESPONSEPENDING_MANAGE_CALL         STD_OFF
/*                                                                               */
/*********************************************************************************/

#endif      /* UDS_CFG_H */
