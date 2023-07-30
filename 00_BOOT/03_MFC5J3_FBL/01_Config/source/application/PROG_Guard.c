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
/*%%   _____________________________   %%  \file PROG_Guard.c                      */
/*%%  |                             |  %%  \brief PROG layer source plugin file  */
/*%%  |   &&&&&   &&&&&             |  %%  Module version: 1.12.0 BL3 */
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
#include "PROG_Guard.h"

/*=============================== IMPLEMENTATION ================================*/
/*                                                                               */
tProgStatus PROG_Custom_Guard_CheckMemory_CheckProgDep(void)
{
  /*Transition is accepted*/
  return PROG_E_OK;
}

tProgStatus PROG_Custom_Guard_CheckProgDep_CompareKey(void)
{
  PROG_Send_NRC(UDS_NRC_24);
  return PROG_E_NOT_OK;
}

tProgStatus PROG_Custom_Guard_CheckProgDep_EraseMemory(void)
{
  PROG_Send_NRC(UDS_NRC_24);
  return PROG_E_NOT_OK;
}

tProgStatus PROG_Custom_Guard_CheckProgDep_FingerPrint(void)
{
  PROG_Send_NRC(UDS_NRC_24);
  return PROG_E_NOT_OK;
}

tProgStatus PROG_Custom_Guard_CheckProgDep_CheckMemory(void)
{
  PROG_Send_NRC(UDS_NRC_24);
  return PROG_E_NOT_OK;
}

tProgStatus PROG_Custom_Guard_CheckProgDep_CheckProgDep(void)
{
  PROG_Send_NRC(UDS_NRC_24);
  return PROG_E_NOT_OK;
}

tProgStatus PROG_Custom_Guard_CompareKey_CheckProgDep(void)
{
  PROG_Send_NRC(UDS_NRC_24);
  return PROG_E_NOT_OK;
}

tProgStatus PROG_Custom_Guard_CompareKey_EraseMemory(void)
{
  PROG_Send_NRC(UDS_NRC_24);
  return PROG_E_NOT_OK;
}

tProgStatus PROG_Custom_Guard_CompareKey_RD(void)
{
  PROG_Send_NRC(UDS_NRC_24);
  return PROG_E_NOT_OK;
}

tProgStatus PROG_Custom_Guard_CompareKey_FingerPrint(void)
{
  /*Transition is accepted*/
  return PROG_E_OK;
}

tProgStatus PROG_Custom_Guard_EraseMemory_CheckProgDep(void)
{
  PROG_Send_NRC(UDS_NRC_24);
  return PROG_E_NOT_OK;
}

tProgStatus PROG_Custom_Guard_EraseMemory_RD(void)
{
  /*Transition is accepted*/
  return PROG_E_OK;
}

tProgStatus PROG_Custom_Guard_EraseMemory_FingerPrint(void)
{
  PROG_Send_NRC(UDS_NRC_24);
  return PROG_E_NOT_OK;
}

tProgStatus PROG_Custom_Guard_EraseMemory_EraseMemory(void)
{
  PROG_Send_NRC(UDS_NRC_24);
  return PROG_E_NOT_OK;
}

tProgStatus PROG_Custom_Guard_RD_CheckProgDep(void)
{
  PROG_Send_NRC(UDS_NRC_24);
  return PROG_E_NOT_OK;
}

tProgStatus PROG_Custom_Guard_RD_EraseMemory(void)
{
  PROG_Send_NRC(UDS_NRC_24);
  return PROG_E_NOT_OK;
}

tProgStatus PROG_Custom_Guard_RD_RD(void)
{
  PROG_Send_NRC(UDS_NRC_24);
  return PROG_E_NOT_OK;
}

tProgStatus PROG_Custom_Guard_RD_FingerPrint(void)
{
  PROG_Send_NRC(UDS_NRC_24);
  return PROG_E_NOT_OK;
}

tProgStatus PROG_Custom_Guard_RTE_FingerPrint(void)
{
  PROG_Send_NRC(UDS_NRC_24);
  return PROG_E_NOT_OK;
}

tProgStatus PROG_Custom_Guard_RTE_CheckMemory(void)
{
  /*Transition is accepted*/
  return PROG_E_OK;
}

tProgStatus PROG_Custom_Guard_RTE_CheckProgDep(void)
{
  // PROG_Send_NRC(UDS_NRC_24);
  // return PROG_E_NOT_OK;
  /*Transition is accepted*/
  return PROG_E_OK;
}

tProgStatus PROG_Custom_Guard_TD_EraseMemory(void)
{
  PROG_Send_NRC(UDS_NRC_24);
  return PROG_E_NOT_OK;
}

tProgStatus PROG_Custom_Guard_TD_FingerPrint(void)
{
  PROG_Send_NRC(UDS_NRC_24);
  return PROG_E_NOT_OK;
}

tProgStatus PROG_Custom_Guard_TD_RD(void)
{
  PROG_Send_NRC(UDS_NRC_24);
  return PROG_E_NOT_OK;
}

tProgStatus PROG_Custom_Guard_FingerPrint_RD(void)
{
  tProgStatus eStatus;
  if (PROG_CustomGetWriteFingerprintStatus() == PROG_E_OK)
  {
    eStatus = PROG_E_OK;
  }
  else
  {
    PROG_Send_NRC(UDS_NRC_24);
    eStatus = PROG_E_NOT_OK;
  }

  return eStatus;
}

tProgStatus PROG_Custom_Guard_FingerPrint_EraseMemory(void)
{
  PROG_Send_NRC(UDS_NRC_24);
  return PROG_E_NOT_OK;
}

tProgStatus PROG_Custom_Guard_FingerPrint_FingerPrint(void)
{
  /*Transition is accepted*/
  return PROG_E_OK;
}

tProgStatus PROG_Custom_Guard_TD_CheckProgDep(void)
{
  PROG_Send_NRC(UDS_NRC_24);
  return PROG_E_NOT_OK;
}

tProgStatus PROG_Custom_Guard_CheckMemory_RD(void)
{
  PROG_Send_NRC(UDS_NRC_24);
  return PROG_E_NOT_OK;
}

tProgStatus PROG_Custom_Guard_CheckProgDep_RD(void)
{
  PROG_Send_NRC(UDS_NRC_24);
  return PROG_E_NOT_OK;
}

tProgStatus PROG_Custom_Guard_ProgSession_EraseMemory(void)
{
  PROG_Send_NRC(UDS_NRC_24);
  return PROG_E_NOT_OK;
}

tProgStatus PROG_Custom_Guard_ProgSession_FingerPrint(void)
{
  /*Transition is accepted*/
  return PROG_E_OK;
}

tProgStatus PROG_Custom_Guard_FingerPrint_CheckProgDep(void)
{
  PROG_Send_NRC(UDS_NRC_24);
  return PROG_E_NOT_OK;
}
