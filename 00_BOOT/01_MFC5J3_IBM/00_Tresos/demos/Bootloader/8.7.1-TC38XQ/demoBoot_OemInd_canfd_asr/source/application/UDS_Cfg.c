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
/*%%   _____________________________   %%  \file UDS_Cfg.c                       */
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




/******************************** FILE INCLUSION *********************************/
/*                                                                               */
/*-------------------------------------------------------------------------------*/
/* - Header Files: UDS                                                           */
#include "EB_Prj.h"
/*                                                                               */
/*********************************************************************************/




/****************************** PUBLIC DEFINITIONS *******************************/
/*                                                                               */
/*-------------------------------------------------------------------------------*/
/* - Public Variables                                                            */

/*-------------------------------------------------------------------------------*/
/* - Public Function Prototypes                                                  */

/*-------------------------------------------------------------------------------*/
/* - Public Callback Prototypes                                                  */

/*                                                                               */
/*********************************************************************************/


/***************************** PRIVATE DEFINITIONS *******************************/
/*                                                                               */
/*-------------------------------------------------------------------------------*/
/* - Private Constants                                                           */

/*-------------------------------------------------------------------------------*/
/* - Private Types                                                               */

/*-------------------------------------------------------------------------------*/
/* - Private Variables                                                           */



/* Diagnostic services configuration 1, stored in Read-Only memory */
const tUdsSrvCfg1 m_astDiagSrvCfg1[UDS_SRV_CFG1_MAX] =
{
    {UDS_SRV_DSC, 0x01U, 0x3U, 2U, 0U, UDS_ADDR_PHYSICAL_FUNCTIONAL, &PROG_Dsc01Cbk},    /* UDS_SESSION_DEFAULT_MASK | UDS_SESSION_PROGRAMMING_MASK */
    {UDS_SRV_DSC, 0x02U, 0x7U, 2U, 0U, UDS_ADDR_PHYSICAL_FUNCTIONAL, NULL},    /* UDS_SESSION_DEFAULT_MASK | UDS_SESSION_PROGRAMMING_MASK | UDS_SESSION_EXTENDED_DIAG_MASK */
    {UDS_SRV_DSC, 0x03U, 0x7U, 2U, 0U, UDS_ADDR_PHYSICAL_FUNCTIONAL, NULL},    /* UDS_SESSION_DEFAULT_MASK | UDS_SESSION_PROGRAMMING_MASK | UDS_SESSION_EXTENDED_DIAG_MASK */
    {UDS_SRV_ER, 0x01U, 0x3U, 2U, 0U, UDS_ADDR_PHYSICAL_FUNCTIONAL, &PROG_EcuReset},    /* UDS_SESSION_DEFAULT_MASK | UDS_SESSION_PROGRAMMING_MASK */
    {UDS_SRV_SA, 0x01U, 0x2U, 2U, 0U, UDS_ADDR_PHYSICAL_FUNCTIONAL, &PROG_RequestSeed},    /*  UDS_SESSION_PROGRAMMING_MASK */
    {UDS_SRV_SA, 0x02U, 0x2U, 4U, 0U, UDS_ADDR_PHYSICAL_FUNCTIONAL, &PROG_SendKey},    /*  UDS_SESSION_PROGRAMMING_MASK */
    {UDS_SRV_TP, 0x00U, 0x3U, 2U, 0U, UDS_ADDR_PHYSICAL_FUNCTIONAL, NULL},    /* UDS_SESSION_DEFAULT_MASK | UDS_SESSION_PROGRAMMING_MASK */
    {UDS_SRV_CDTCS, 0x02U, 0x6U, 2U, 0U, UDS_ADDR_PHYSICAL_FUNCTIONAL, &PROG_ControlDTCSetting},    /*  UDS_SESSION_PROGRAMMING_MASK | UDS_SESSION_EXTENDED_DIAG_MASK */
    {UDS_SRV_RD, 0x00U, 0x2U, 0U, 1U, UDS_ADDR_PHYSICAL_FUNCTIONAL, &PROG_RequestDownload},    /*  UDS_SESSION_PROGRAMMING_MASK */
    {UDS_SRV_TD, 0x00U, 0x2U, 0U, 0U, UDS_ADDR_PHYSICAL_FUNCTIONAL, &PROG_TransferData},    /*  UDS_SESSION_PROGRAMMING_MASK */
    {UDS_SRV_RTE, 0x00U, 0x2U, 0U, 0U, UDS_ADDR_PHYSICAL_FUNCTIONAL, &PROG_RequestTransferExit},    /*  UDS_SESSION_PROGRAMMING_MASK */
    {UDS_SRV_CC, 0x03U, 0x6U, 3U, 0U, UDS_ADDR_PHYSICAL_FUNCTIONAL, &PROG_CommunicationControl},    /*  UDS_SESSION_PROGRAMMING_MASK | UDS_SESSION_EXTENDED_DIAG_MASK */
};

/* Diagnostic services configuration 2, stored in Read-Only memory */
const tUdsSrvCfg2 m_astDiagSrvCfg2[UDS_SRV_CFG2_MAX] =
{
    {UDS_SRV_RDBI, 0xf181U, 0x3U, 3U, 0U, UDS_ADDR_PHYSICAL_FUNCTIONAL, &PROG_ReadFingerPrint},    /* UDS_SESSION_DEFAULT_MASK | UDS_SESSION_PROGRAMMING_MASK */
    {UDS_SRV_WDBI, 0xf181U, 0x2U, 19U, 0U, UDS_ADDR_PHYSICAL_FUNCTIONAL, &PROG_WriteFingerprint},    /*  UDS_SESSION_PROGRAMMING_MASK */
    {UDS_SRV_WDBI, 0xfd03U, 0x7U, 4U, 0U, UDS_ADDR_PHYSICAL, &UDS_EbTestingWriteDataByIdentifier},    /* UDS_SESSION_DEFAULT_MASK | UDS_SESSION_PROGRAMMING_MASK | UDS_SESSION_EXTENDED_DIAG_MASK */

};


/* Diagnostic services configuration 3, stored in Read-Only memory */
const tUdsSrvCfg3 m_astDiagSrvCfg3[UDS_SRV_CFG3_MAX] =
{
    {UDS_SRV_RC, 0x01U, 0xff00U, 0x2U, 12U, 1U, UDS_ADDR_PHYSICAL_FUNCTIONAL, &PROG_EraseMemory},    /*  UDS_SESSION_PROGRAMMING_MASK */
    {UDS_SRV_RC, 0x01U, 0x0202U, 0x2U, 8U, 1U, UDS_ADDR_PHYSICAL_FUNCTIONAL, &PROG_CheckMemory},    /*  UDS_SESSION_PROGRAMMING_MASK */
    {UDS_SRV_RC, 0x01U, 0x0203U, 0x4U, 4U, 0U, UDS_ADDR_PHYSICAL, &PROG_ReqCheckProgPreCondition},    /*  UDS_SESSION_EXTENDED_DIAG_MASK */
    {UDS_SRV_RC, 0x01U, 0xff01U, 0x2U, 4U, 0U, UDS_ADDR_PHYSICAL, &PROG_CoherencyCheck},    /*  UDS_SESSION_PROGRAMMING_MASK */
};



/* Structure storing sessions and associated NRC_78 timings (P2 and P2Star) */
const tUdsSessionInfo m_stSessionInfo[UDS_CONFIGURABLE_SESSION_MAX] = 
{
  
  {1, 50, 5000, UDS_SESSION_PROT_DEFAULT, UDS_SESSION_PROT_DEFAULT_MASK},
  {2, 50, 5000, UDS_SESSION_PROT_PROGRAMMING, UDS_SESSION_PROT_PROGRAMMING_MASK},
  {3, 50, 5000, UDS_SESSION_PROT_EXTENDED_DIAG, UDS_SESSION_PROT_EXTENDED_DIAG_MASK},
  {96, 50, 5000, UDS_SESSION_PROT_SUPPLIER, UDS_SESSION_PROT_SUPPLIER_MASK},
  {64, 50, 5000, UDS_SESSION_PROT_OTHER_01, UDS_SESSION_PROT_OTHER_01_MASK},
  {65, 50, 5000, UDS_SESSION_PROT_OTHER_02, UDS_SESSION_PROT_OTHER_02_MASK},
  {66, 50, 5000, UDS_SESSION_PROT_OTHER_03, UDS_SESSION_PROT_OTHER_03_MASK},
  {67, 50, 5000, UDS_SESSION_PROT_OTHER_04, UDS_SESSION_PROT_OTHER_04_MASK}
};

/*-------------------------------------------------------------------------------*/
/* - Private Macros                                                              */

/*-------------------------------------------------------------------------------*/
/* - Private Function Prototypes                                                 */

/*                                                                               */
/*********************************************************************************/




/******************************** IMPLEMENTATION *********************************/
/*                                                                               */

/*-------------------------------------------------------------------------------*/
/* - Public Functions                                                            */

/*-------------------------------------------------------------------------------*/
/* - Private Functions                                                           */

/*-------------------------------------------------------------------------------*/
/* - Public Callbacks                                                            */

/*                                                                               */
/*********************************************************************************/

