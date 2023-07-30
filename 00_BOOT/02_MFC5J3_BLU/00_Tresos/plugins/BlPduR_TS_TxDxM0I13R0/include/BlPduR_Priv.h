/*===============================================================================*/
/*                                                                               */
/*                               BOOT Layers                                     */
/*                                                                               */
/* ----------------------------------------------------------------------------- */
/*                                                                               */
/*                               BlPduR layer                                    */
/*                                                                               */
/*===============================================================================*/
/*%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%                                        */
/*%%   _____________________________   %%  \file BlPduR_Priv.h                   */
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
#ifndef BLPDUR_PRIV_H
#define BLPDUR_PRIV_H

extern tBufferInfoType m_stTxBufferInfo;
extern u8* m_pubTxBuffer;
extern tBufferConfigType* m_pstRxCurrentBufferConfig;
extern tBufferConfigType* m_apstReceptionBuffer[BLPDUR_RX_BUFFER];
extern u8 m_ubReceiveBuffCount;
extern u8 m_ubCurrentConnection;

#if (BLPDUR_NETWORK_LIN_SUPPORTED == STD_ON)
extern tBlPduRStatus BlPduR_LinTpTxMessage(u16 uwlen, u8* pubData);
extern void BlPduR_Lin_Init(void);
#endif

extern void BlPduR_TxConf(PduIdType uTxPduId, tBlPduRStatus eBlPduRStatus);
extern void BlPduR_RxInd(PduIdType uRxPduId, tBlPduRStatus eBlPduRStatus);


#endif      /* BLPDUR_PUB_H */
