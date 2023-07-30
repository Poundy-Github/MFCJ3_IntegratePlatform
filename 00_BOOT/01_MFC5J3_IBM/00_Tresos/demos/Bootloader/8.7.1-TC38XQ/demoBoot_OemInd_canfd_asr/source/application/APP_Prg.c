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
/*%%  |   &&&&&   &&&&&             |  %%  Module version: 3.6.0 BL-2.X                */
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

/*-------------------------------------------------------------------------------*/
/* - Private Types                                                               */

/*-------------------------------------------------------------------------------*/
/* - Private Variables                                                           */

/* Interrupt context */
NCS_PRI_VAR u8 m_ubItContext;


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
    return (m_ubItContext);
}
/*--------------------------{end APP_InterruptDisable}----------------------------------*/


/*--------------------------{APP_Init}--------------------------------------*/
void APP_Init (void)
{

}
/*--------------------------{end APP_Init}----------------------------------*/

/*--------------------------{APP_Manage}--------------------------------------*/
void APP_Manage (void)
{

}
/*--------------------------{end APP_Manage}----------------------------------*/

#ifdef BOARD_ISR_STMTIMER
/*--------------------------{APP_PlatformSTMTimSch}----------------------------------*/
void APP_PlatformSTMTimSch (void)
{
    /* Manage response for long request */
    UDS_ResponsePending_Manage();
}
/*--------------------------{end APP_PlatformSTMTimSch}----------------------------------*/
#endif

/*--------------------------{UDS_P2AboutToExpireInd}--------------------------------------*/
void UDS_P2AboutToExpireInd(void)
{

}
/*--------------------------{end UDS_P2AboutToExpireInd}----------------------------------*/

/*--------------------------{APP_UdsSessionStatusInd}--------------------------------------*/
void APP_UdsSessionStatusInd (tUdsSessionType eUdsNewSessType,tUdsSessionType eUdsOldSessType,tUdsChangeReason eUdsChangingCause)
{
    OSC_PARAM_UNUSED(eUdsOldSessType);
    OSC_PARAM_UNUSED(eUdsChangingCause);
    OSC_PARAM_UNUSED(eUdsNewSessType);
}
/*--------------------------{end APP_UdsSessionStatusInd}----------------------------------*/

/*--------------------------{APP_TpDataBufferEmptyInd}--------------------------------------*/
void APP_TpDataBufferEmptyInd (tTpMsgIdx uMsgIdx)
{
    OSC_PARAM_UNUSED(uMsgIdx);
}
/*--------------------------{end APP_TpDataBufferEmptyInd}----------------------------------*/

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

/*-------------------------------------------------------------------------------*/

/*--------------------------{APP_GetUdsDataBufferInd}--------------------------------------*/
/* Deviation MISRA-1 */
void APP_GetUdsDataBufferInd(u16 *uwLen, u8 *paubUdsData, tTpMsgIdx uMsgIdx, tUdsStatus eStatusRxReq)
{
    OSC_PARAM_UNUSED(uwLen);
    OSC_PARAM_UNUSED(uMsgIdx);
    OSC_PARAM_UNUSED(eStatusRxReq);
    OSC_PARAM_UNUSED(paubUdsData);
}

/*--------------------------{end APP_GetUdsDataBufferInd}----------------------------------*/

#if (CAN_WAKE_UP_DETECTION  == CAN_WAKE_UP_ACTIVATE)
/*--------------------------{APP_CanWakeUpInd}--------------------------------------*/
void APP_CanWakeUpInd (void)
{

}
/*--------------------------{end APP_CanWakeUpInd}----------------------------------*/
#endif

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

/*--------------------------{APP_DisableFailSafeReaction}--------------------------------------*/
/* Deviation MISRA-1 */
tUdsStatus APP_DisableFailSafeReaction(u16 *puwLen, u8 *aubUdsData)
{
    OSC_PARAM_UNUSED(puwLen);
    OSC_PARAM_UNUSED(aubUdsData);

    return UDS_ACK;
}
/*--------------------------{end APP_DisableFailSafeReaction}----------------------------------*/

/*--------------------------{APP_ReadFingerPrint}--------------------------------------*/
/* Deviation MISRA-1 */
tUdsStatus APP_ReadFingerPrint(u16 *puwLen, u8 *aubUdsData)
{
    OSC_PARAM_UNUSED(aubUdsData);
    
    *puwLen = 7;

    return UDS_ACK;
}
/*--------------------------{end APP_ReadFingerPrint}----------------------------------*/