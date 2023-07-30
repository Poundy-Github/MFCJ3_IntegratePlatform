/*===============================================================================*/
/*                                                                               */
/*                               BOOT Layers                                     */
/*                                                                               */
/* ----------------------------------------------------------------------------- */
/*                                                                               */
/*                               BlPduR layer                                      */
/*                                                                               */
/*===============================================================================*/
/*%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%                                        */
/*%%   _____________________________   %%  \file BlPduR_Lin.c                    */
/*%%  |                             |  %%                                        */
/*%%  |   &&&&&   &&&&&             |  %%  Module version: 0.13.0 BL-3.X                */
/*%%  |   &       &    &            |  %%                                        */
/*%%  |   &&&&    &&&&&             |  %%                                        */
/*%%  |   &       &    &            |  %%                                        */
/*%%  |   &&&&&   &&&&&             |  %%                                        */
/*%%  |_____________________________|  %%                                        */
/*%%                                   %%                                        */
/*%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%                                        */
/*===============================================================================*/
/* Copyright 2016 by Elektrobit Automotive GmbH                                  */
/* All rights exclusively reserved for Elektrobit Automotive GmbH,               */
/* unless expressly agreed to otherwise.                                         */
/*===============================================================================*/

/*=============================== FILE INCLUSION ================================*/
/*                                                                               */
/*-------------------------------------------------------------------------------*/
/* - Header Files: BlPduR                                                           */
#include "BlPduR_Prj.h"

#if (BLPDUR_NETWORK_LIN_SUPPORTED == STD_ON)
#include "BlPduR_Priv.h"
#include <BlPduR_Trace.h>
#include <TSMem.h>          /* EB specific memory functions */
#include <Base_Modules.h>   /* Module enable defines and standard config pointer names */
/*                                                                               */
/*===============================================================================*/

/*============================= PUBLIC DEFINITIONS ==============================*/
/*                                                                               */
/*-------------------------------------------------------------------------------*/
/* - Public Variables                                                            */

/*-------------------------------------------------------------------------------*/
/* - Public Function Prototypes                                                  */

/*-------------------------------------------------------------------------------*/
/* - Public Callback Prototypes                                                  */
/*                                                                               */
/*===============================================================================*/

/*============================ PRIVATE DEFINITIONS ==============================*/
/*                                                                               */
/*-------------------------------------------------------------------------------*/
/* - Private Constants                                                           */

/*-------------------------------------------------------------------------------*/
/* - Private Types                                                               */

/*-------------------------------------------------------------------------------*/
/* - Private Variables                                                           */
/* Rx Functional Buffer information structure */
NCS_PRI_VAR tBufferInfoType m_stRxLinBufferInfo;

NCS_PRI_VAR tBufferConfigType m_stRxLinBufferConfig;
/*-------------------------------------------------------------------------------*/
/* - Private Macros                                                              */

/*-------------------------------------------------------------------------------*/
/* - Private Function Prototypes                                                 */
/*                                                                               */

/*===============================================================================*/


/*=============================== IMPLEMENTATION ================================*/
/*                                                                               */

/*-------------------------------------------------------------------------------*/
/* - Public Functions                                                            */
/*--------------------------------{BLPDUR_LIN_Init}--------------------------------*/
void BlPduR_Lin_Init(void)
{
    /* Initialize LIN reception buffer information */
    m_stRxLinBufferInfo.filledLen = 0U;
    m_stRxLinBufferInfo.dataMark = 0U;
    m_stRxLinBufferInfo.confirmedDataMark = 0U;
    m_stRxLinBufferInfo.state = BLPDUR_BUFF_IDLE;
    m_stRxLinBufferInfo.originatingRxPduId = 0U;

    /* Initialize LIN reception buffer configuration */
    m_stRxLinBufferConfig.ptrBuffer = NULL_PTR;
    m_stRxLinBufferConfig.bufferInfo = &m_stRxLinBufferInfo;
    m_stRxLinBufferConfig.size = BLPDUR_RX_PHYS_BUFFERSIZE;
}
/*--------------------------------{end BLPDUR_LIN_Init}----------------------------*/
/*--------------------------------{LIN_StatusInd}--------------------------------*/
#if (LIN_CTRL_MAX > 1)
    void LIN_StatusInd (u8 ubCtrlIdx, tLinFrameIdx uFrameIdx, tLinFrameStatus eStatus)
#else
    void LIN_StatusInd (tLinFrameIdx uFrameIdx, tLinFrameStatus eStatus)
#endif
{
    /* Successfull transmission */
    if (eStatus == LIN_STATUS_TX_OK)
    {
#if BLPDUR_LIN_BIT_RESPONSE_ENABLE == STD_ON
        /* The error_response bit is clear */
        if (uFrameIdx == BLPDUR_LIN_FRAME_IDX_BIT_RESP_ERROR)
        {
            LIN_WR_BIT_RESPONSE_ERROR(LIN_FALSE);
        }
#endif

        /* For the Transport Protocol, N_As indication
           Associate the COM frame to the TP message */
        if (uFrameIdx == BLPDUR_LIN_FRAME_IDX_TX)
        {
            /* Call LTP Tx Confirmation */
            LTP_LinTxConf();
        }
    }
}
/*---------------------------------{end LIN_StatusInd}----------------------------*/

/*----------------------------------{LIN_ComLossInd}--------------------------------*/
void LIN_ComLossInd(void)
{
    /* Switch the LIN layer to Anormal mode */
    (void)l_ifc_disconnect ();
}
/*----------------------------------{end LIN_ComLossInd}----------------------------*/

/*----------------------------------{LIN_WakeUpInd}--------------------------------*/
void LIN_WakeUpInd(void)
{
    /* Switch the LIN layer to Normal mode */
    (void)l_ifc_connect ();
}
/*----------------------------------{end LIN_WakeUpInd}----------------------------*/

/*-----------------------------{LTP_RxInd}------------------------------------------*/
void LTP_RxInd (u8 ebStatus)
{
    /* Transport Protocol functions return status */
    tLtpStatus eStatus ;
    tBufferInfoType *curRxBufferInfo;

    if(ebStatus == LTP_MSG_STATUS_OK)
    {
        if((m_ubCurrentConnection == BLPDUR_NO_ACTIVE_CONNECTION) || (m_ubCurrentConnection == stRxPdu[BLPDUR_RX_LIN].ConnectionNum))
        {
            /* Get the current buffer config for order storage */
            m_pstRxCurrentBufferConfig = &m_stRxLinBufferConfig;

            /* Get the current buffer information */
            curRxBufferInfo = m_pstRxCurrentBufferConfig->bufferInfo;

            /* retrieve buffer pointer and length of data received */
            eStatus = LTP_GetMsgData (&curRxBufferInfo->filledLen, &m_pstRxCurrentBufferConfig->ptrBuffer);

            if(eStatus == LTP_MSG_STATUS_OK)
            {
                /* allocate Rx buffer */
                curRxBufferInfo->state = BLPDUR_BUFF_PROCESSING;
                /* remember RxPduId */
                curRxBufferInfo->originatingRxPduId = BLPDUR_RX_LIN;
                /* set current dataMark to the length of received data. */
                curRxBufferInfo->dataMark = curRxBufferInfo->filledLen;

                /* Update current connection */
                m_ubCurrentConnection = stRxPdu[BLPDUR_RX_LIN].ConnectionNum;

                /* The buffer reception order shall stored */
                m_apstReceptionBuffer[m_ubReceiveBuffCount] = m_pstRxCurrentBufferConfig;
                m_ubReceiveBuffCount++;

                /* Stop S3 timer on start of frame reception */
                UDS_StopSessionTimer();

                APP_TpRxInd(BLPDUR_RX_LIN, ebStatus);
            }
            else
            {
                BlPduR_RxInd(BLPDUR_RX_LIN, BLPDUR_E_NOT_OK );
            }
        }
    }
    else
    {
        BlPduR_RxInd(BLPDUR_RX_LIN, BLPDUR_E_NOT_OK );
    }

}
/*----------------------------------{end LTP_RxInd}--------------------------------*/

/*-----------------------------------{BlPduR_LinTpTxMessage}----------------------------------*/
tBlPduRStatus BlPduR_LinTpTxMessage (u16 uwlen, u8* pubData)
{
    tBlPduRStatus eBlPduRStatus = BLPDUR_E_OK;
    tLtpStatus eLtpStatus;

    /* Store transmit buffer to manage TxConf correctly */
    m_pubTxBuffer = pubData;

    /* Write the answer message datas */
    eLtpStatus = LTP_SetMsgData (uwlen, pubData);

    /* The message datas update is complete without any error */
    if (eLtpStatus == LTP_ERR_OK)
    {
        /* Send the Diagnostic answer message */
        eLtpStatus = LTP_SendMsg();

        if (eLtpStatus != LTP_ERR_OK)
        {
            eBlPduRStatus = BLPDUR_E_NOT_OK;
        }
    }
    else
    {
        eBlPduRStatus = BLPDUR_E_NOT_OK;
    }

    return eBlPduRStatus;
}
/*----------------------------------{end BlPduR_LinTpTxMessage}-------------------------------*/

/*-----------------------------------{LTP_TxConf}----------------------------------*/
void LTP_TxConf (u8 ebStatus)
{
    if(ebStatus == LTP_MSG_STATUS_OK)
    {
        /* Call BlPduR TxConfirmation */
        BlPduR_TxConf(BLPDUR_LIN_TX_PDU,BLPDUR_E_OK);
    }
    else
    {
        /* Call BlPduR TxConfirmation */
        BlPduR_TxConf(BLPDUR_LIN_TX_PDU,BLPDUR_E_NOT_OK);
    }
}
/*----------------------------------{end LTP_TxConf}-------------------------------*/
#endif /* #if (BLPDUR_LIN_USED == STD_ON)*/
