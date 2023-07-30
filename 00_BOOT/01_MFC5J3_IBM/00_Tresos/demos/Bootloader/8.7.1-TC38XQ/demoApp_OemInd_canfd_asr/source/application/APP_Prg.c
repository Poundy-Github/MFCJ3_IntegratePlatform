/*********************************************************************************/
/*                                                                               */
/*                                  CAN Stack                                    */
/*                                                                               */
/* ----------------------------------------------------------------------------- */
/*                                                                               */
/*                                APP                                            */
/*                                                                               */
/*********************************************************************************/
/*%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%                                        */
/*%%   _____________________________   %%  \file APP_Prg.c                       */
/*%%  |                             |  %%                                        */
/*%%  |   &&&&&   &&&&&             |  %%  Module version: 3.6.255 OSC_BOOT                */
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

/*  MISRA-C:2004 Deviation List
 *
 *  MISRA-1) Deviated Rule: 16.7 (advisory)
 *   A pointer parameter in a function prototype should be declared as pointer to const
 *   if the pointer is not used to modify the addressed object.
 *
 *   Reason:
 *   The MISRA rule is not violated. This pointer will be used once the function is completed by customer.
 */


/******************************** FILE INCLUSION *********************************/
/*                                                                               */
/*-------------------------------------------------------------------------------*/
/* - Header Files: EB                                                            */
#include "EB_Prj.h"
#include "board.h"
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

#define DEMO_CAL_START_SEC_CONST_8
#include <MemMap.h>
NCS_PRI_VAR const u8 m_aubDidF18c[128] = {0xEBU, 0xEBU, 0xEBU, 0xEBU, 0xEBU, 0xEBU, 0xEBU, 0xEBU, 0xEBU, 0xEBU, 0xEBU, 0xEBU, 0xEBU, 0xEBU, 0xEBU, 0xEBU, 0xEBU, 0xEBU, 0xEBU, 0xEBU, 0xEBU, 0xEBU, 0xEBU, 0xEBU, 0xEBU, 0xEBU, 0xEBU, 0xEBU};
#define DEMO_CAL_STOP_SEC_CONST_8
#include <MemMap.h>

/*-------------------------------------------------------------------------------*/
/* - Private Types                                                               */

/*-------------------------------------------------------------------------------*/
/* - Private Variables                                                           */
#define PROG_REPROG_FLAG_START_SEC_VAR_NO_INIT_8
#include <MemMap.h>
tNoIntShareVar stNoIntShareVar;
#define PROG_REPROG_FLAG_STOP_SEC_VAR_NO_INIT_8
#include <MemMap.h>

/* Integration to test the response after the reset */
NCS_PRI_VAR u8 m_ubProgFirstCall;
NCS_PRI_VAR u8 m_aubUdsData[7];

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
/* - Public Functions                                                            */

/*--------------------------{APP_AppliRunning}--------------------------------------*/
/* Deviation MISRA-1 */
tUdsStatus APP_AppliRunning(u16 *puwLen, u8 *aubUdsData)
{
  aubUdsData[3] = 0xEBU;

  *puwLen = 4U;
  return UDS_ACK;
}
/*--------------------------{end APP_AppliRunning}----------------------------------*/

/*--------------------------{APP_InterruptEnable}--------------------------------------*/
void APP_InterruptEnable (u8 ebStatus)
{
    /* Implement here a treatment for a critical section exit. */
    /* Interrupts must be resumed. */
    OSC_PARAM_UNUSED(ebStatus);
    BoardEnableInterrupts();
}
/*--------------------------{end APP_InterruptEnable}----------------------------------*/

/*--------------------------{APP_InterruptDisable}--------------------------------------*/
u8 APP_InterruptDisable (void)
{
    /* Implement here a treatment for a critical section entry. */
    /* Interrupts must be suspended. */
    BoardDisableInterrupts();
    return (0);
}
/*--------------------------{end APP_InterruptDisable}----------------------------------*/

/*--------------------------{APP_Init}--------------------------------------*/
void APP_Init (void)
{
    m_ubProgFirstCall = TRUE;
}
/*--------------------------{end APP_Init}----------------------------------*/

/*--------------------------{APP_Manage}--------------------------------------*/
void APP_Manage (void)
{

}
/*--------------------------{end APP_Manage}----------------------------------*/


/*--------------------------{CAN_BusOffInd}--------------------------------------*/
void CAN_BusOffInd (void)
{
}
/*--------------------------{end CAN_BusOffInd}----------------------------------*/


/*--------------------------{UDS_P2AboutToExpireInd}--------------------------------------*/
void UDS_P2AboutToExpireInd(void)
{

}
/*--------------------------{end UDS_P2AboutToExpireInd}----------------------------------*/

/*--------------------------{APP_ProgSession}--------------------------------------*/
/* Deviation MISRA-1 */
tUdsStatus APP_ProgSession(u16 *puwLen, u8 *aubUdsData)
{
    OSC_PARAM_UNUSED(aubUdsData);

    BlPduR_StoreConnectionInfo();

    stNoIntShareVar.ulProgSig = 0x55AA55AAU;
    stNoIntShareVar.ubResetCause = PROG_RESET_CAUSE_DSC02;
    /* Check SuppressPositiveResponseBit */
    if (0x80U == (aubUdsData[1] & 0x80U))
    {
        /* do not send the response */
        stNoIntShareVar.ubSendResp = PROG_FALSE;
    }
    else
    {
        /* send the response */
        stNoIntShareVar.ubSendResp = PROG_TRUE;
    }

    BoardPerformSwReset();

    /* Dummy check to avoid warning */
    if (stNoIntShareVar.ulProgSig == 0x55AA55AAU)
    {
        *puwLen = 2U;
    }

    /* No return since reset is triggered */
    return UDS_ACK;
}

/*--------------------------{end APP_ProgSession}----------------------------------*/
/* Deviation MISRA-1 */
tUdsStatus APP_EcuReset(u16 *puwLen, u8 *aubUdsData)
{
    OSC_PARAM_UNUSED(puwLen);

    BlPduR_StoreConnectionInfo();

    stNoIntShareVar.ubResetCause = PROG_RESET_CAUSE_ER;
    /* Check SuppressPositiveResponseBit */
    if (0x80U == (aubUdsData[1] & 0x80U))
    {
        stNoIntShareVar.ubSendResp = PROG_FALSE;
    }
    else
    {
        stNoIntShareVar.ubSendResp = PROG_TRUE;
    }

    /* Reset the board */
    BoardPerformSwReset();

    return UDS_ACK;
}

/*--------------------------{APP_CommunicationControl}--------------------------------------*/
/* Deviation MISRA-1 */
 tUdsStatus APP_CommunicationControl(u16 *puwLen, u8 *aubUdsData)
 {
    *puwLen = 2U;
     OSC_PARAM_UNUSED(aubUdsData);

     return UDS_ACK;
 }
/*--------------------------{end APP_CommunicationControl}----------------------------------*/

/*--------------------------{APP_ControlDTCSetting}--------------------------------------*/
/* Deviation MISRA-1 */
tUdsStatus APP_ControlDTCSetting(u16 *puwLen, u8 *aubUdsData)
{
    OSC_PARAM_UNUSED(puwLen);
    OSC_PARAM_UNUSED(aubUdsData);

    return UDS_ACK;
}
/*--------------------------{end APP_ControlDTCSetting}----------------------------------*/

/*--------------------------{UDS_ReadDataByIdentifier_F18C}--------------------------------------*/
/* Deviation MISRA-1 */
tUdsStatus UDS_ReadDataByIdentifier_F18C(u16 *puwLen, u8 *aubUdsData)
{
    u8 ubIdx;
    *puwLen = 7U;

    for(ubIdx = 0U; ubIdx < (*puwLen - 3U); ubIdx++)
    {
        aubUdsData[3U + ubIdx] = m_aubDidF18c[ubIdx];
    }
    return UDS_ACK;
}
/*--------------------------{end UDS_ReadDataByIdentifier_F18C}----------------------------------*/

/*--------------------------{APP_UdsSessionStatusInd}--------------------------------------*/
void APP_UdsSessionStatusInd (tUdsSessionType eUdsNewSessType,tUdsSessionType eUdsOldSessType,tUdsChangeReason eUdsChangingCause)
{
    OSC_PARAM_UNUSED(eUdsOldSessType);
    OSC_PARAM_UNUSED(eUdsChangingCause);
    OSC_PARAM_UNUSED(eUdsNewSessType);
}
/*--------------------------{end APP_UdsSessionStatusInd}----------------------------------*/

/*--------------------------{NCS_SdfVariableCoherencyError}--------------------------------------*/
void NCS_SdfVariableCoherencyError(u16 uwParam)
{
    OSC_PARAM_UNUSED(uwParam);
}
/*--------------------------{end NCS_SdfVariableCoherencyError}----------------------------------*/

/*--------------------------{NCS_SdfVariableRangeError}--------------------------------------*/
void NCS_SdfVariableRangeError(u16 uwParam)
{
    OSC_PARAM_UNUSED(uwParam);
}
/*--------------------------{end NCS_SdfVariableRangeError}----------------------------------*/


/*--------------------------{APP_TpTxConf}--------------------------------------*/
void APP_TpTxConf (tTpMsgIdx uMsgIdx, u8 ebStatus)
{
    OSC_PARAM_UNUSED(uMsgIdx);
    OSC_PARAM_UNUSED(ebStatus);
}
/*--------------------------{end APP_TpTxConf}----------------------------------*/

/*--------------------------{APP_TpRxInd}--------------------------------------*/
void APP_TpRxInd (tTpMsgIdx uMsgIdx, u8 ebStatus)
{
    OSC_PARAM_UNUSED(uMsgIdx);
    OSC_PARAM_UNUSED(ebStatus);

}
/*--------------------------{end APP_TpRxInd}----------------------------------*/

/*--------------------------{APP_ReqCheckProgPreCondition}--------------------------------------*/
tUdsStatus APP_ReqCheckProgPreCondition(u16 *puwLen, u8 *aubUdsData)
{
    tUdsStatus eStatus;
    *puwLen = 4U;
    eStatus = UDS_ACK;
    return (eStatus);
}
/*--------------------------{end APP_ReqCheckProgPreCondition}----------------------------------*/

/*--------------------------{APP_DisableFailSafeReaction}--------------------------------------*/
tUdsStatus APP_DisableFailSafeReaction(u16 *puwLen, u8 *aubUdsData)
{
    tUdsStatus eStatus;
    *puwLen = 4U;
    eStatus = UDS_ACK;
    return (eStatus);
}
/*--------------------------{end APP_DisableFailSafeReaction}----------------------------------*/

/*--------------------------{APP_Reset_Cause}--------------------------------------*/
void APP_Reset_Cause(void)
{
    tProgResCause ubResetCause;
    tProgBoolean  ubSendResp;


    /* Get the reset cause and send response status */
    ubResetCause = stNoIntShareVar.ubResetCause;
    ubSendResp = stNoIntShareVar.ubSendResp;

    if (PROG_TRUE == ubSendResp)
    {
        /* Response needed, check the reset cause */
        switch (ubResetCause)
        {
            case PROG_RESET_CAUSE_ER:
                /*Send Positive Response to ER*/
                PROG_SimulateER();
                break;

            case PROG_RESET_CAUSE_DSC01:
                /*Send Positive Response to DSC01*/
                PROG_SimulateCloseProgSession();
                break;

            case PROG_RESET_CAUSE_S3_TIMEOUT:
            default:
                /*do nothing*/
                break;
        }
    }
    else
    {
        /*Do nothing, no response needed*/
    }
}
/*--------------------------{end APP_Reset_Cause}----------------------------------*/

/*---------------------------{PROG_SimulateCloseProgSession}----------------------*/
void PROG_SimulateCloseProgSession(void)
{
    u16 uwLen;

    if (TRUE == m_ubProgFirstCall)
    {
        BlPduR_RetrieveConnectionInfo();

        /* Prepare the sending of response to DSC01 */
        uwLen = 6U;

        m_aubUdsData[0U]=(u8)(UDS_SRV_DSC + UDS_ACK);
        m_aubUdsData[1U]=(u8)(UDS_SESSION_DEFAULT);
        m_aubUdsData[2U]=(u8)((PROG_P2_DEFAULT_SESSION_VAL)>>8U);
        m_aubUdsData[3U]=(u8) (PROG_P2_DEFAULT_SESSION_VAL);
        m_aubUdsData[4U]=(u8)((PROG_P2STAR_DEFAULT_SESSION_VAL/10U)>>8U);
        m_aubUdsData[5U]=(u8)((PROG_P2STAR_DEFAULT_SESSION_VAL/10U));

        /* Send Message */
        EB_Send_TPFrame(uwLen, m_aubUdsData);
    }
}
/*--------------------------{end PROG_SimulateCloseProgSession}-------------------*/

/*----------------------------------{PROG_SimulateER}-----------------------------*/
void PROG_SimulateER(void)
{
    u16 uwLen;

    if (TRUE == m_ubProgFirstCall)
    {
        BlPduR_RetrieveConnectionInfo();

        /* Prepare the sending of response to ER */
        uwLen = PROG_ECU_RESET_RESPONSE_SIZE;

        /* Reset type: HW */
        m_aubUdsData[0U]=(u8)(UDS_SRV_ER + UDS_ACK);
        m_aubUdsData[1U]=(u8)(UDS_SESSION_DEFAULT);

        /* Send Message */
        EB_Send_TPFrame(uwLen, m_aubUdsData);
    }
}
/*--------------------------------{end PROG_SimulateER}---------------------------*/

/*-------------------------------------------------------------------------------*/


