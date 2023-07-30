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
/*%%   _____________________________   %%  \file BlPduR_Prg.c                      */
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
#include "BlPduR_Priv.h"
#include <BlPduR_Trace.h>
#include <TSMem.h>          /* EB specific memory functions */
#include <Base_Modules.h>   /* Module enable defines and standard config pointer names */
#if (STD_ON==BLPDUR_NETWORK_FLEXRAY_SUPPORTED)
#include "Frif_Api.h"
#if (STD_ON==BLPDUR_FRSM_ENABLEALLSLOTS)
#include "FrSM.h"
#endif
#endif
#if (BLPDUR_UPDATE_TP_PARAM_ENABLE == STD_ON)
#include <PduR_BlPduR.h>
#endif /*(BLPDUR_UPDATE_TP_PARAM_ENABLE == STD_ON)*/
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
#define FRCYCL_UNUSED 0xFFu

/*-------------------------------------------------------------------------------*/
/* - Private Types                                                               */

/*-------------------------------------------------------------------------------*/
/* - Private Variables                                                           */
#define BLPDUR_BUFF_START_SEC_VAR
#include <MemMap.h>
/* Functional TP buffer */
NCS_PRI_VAR uint8 m_aubTPFuncBuffer[BLPDUR_RX_FUNC_BUFFERSIZE];
#define BLPDUR_BUFF_STOP_SEC_VAR
#include <MemMap.h>

/* Tx Buffer info structure */
tBufferInfoType m_stTxBufferInfo = { 0U, 0U, 0U, BLPDUR_BUFF_IDLE, 0U };
/* Pointer to the Tx buffer used */
u8* m_pubTxBuffer = NULL_PTR;

/* Rx Functional Buffer information structure */
NCS_PRI_VAR tBufferInfoType m_stRxFuncBufferInfo;
#if (BLPDUR_ASR_NETWORK_PRESENT == STD_ON)
/* Rx Functional Buffer configuration information */
NCS_PRI_VAR tBufferConfigType m_stRxFuncBufferConfig;
 #endif
/* Pointer to the current Rx Buffer configuration information */
tBufferConfigType* m_pstRxCurrentBufferConfig;
/* Tab to store the pointer Rx Buffer configuration information
   The pointer are stored in the order of treatment */
tBufferConfigType* m_apstReceptionBuffer[BLPDUR_RX_BUFFER];
/* Counter on the number of element queued in m_apstReceptionBuffer */
u8 m_ubReceiveBuffCount;

#if (BLPDUR_MULTIPLE_BUFFERS_ENABLE ==  STD_ON)
/* Tab to store the pointer Rx Buffer configuration information  use for multiple buffer
   The pointer are stored in the order of treatment */
NCS_PRI_VAR tBufferConfigType* m_apstMultipleReceptionBuffer[BLPDUR_RX_PHY_BUFFER_NUM];
/* Number of buffer remaining locked */
NCS_PRI_VAR u8 m_ubBuffLockCount;
#endif

#if (BLPDUR_QUEUED_MANAGEMENT_ENABLE == STD_ON)
/* Tab to store the pointer Rx Buffer configuration information  use for queued buffers
   The pointers are stored in the order of treatment */
NCS_PRI_VAR tBufferConfigType* m_apstQueuedReceptionBuffer[BLPDUR_RX_PHY_BUFFER_NUM];
/* Number of queued buffers */
NCS_PRI_VAR u8 m_ubQueuedBuffCount;
#endif
#if (BLPDUR_MULTIPLE_ID_ENABLE ==  STD_ON)
#if (BLPDUR_MULTIPLE_ID_TYPE == BLPDUR_MULTIPLE_ID_CAN_NOTIFICATION)
/* Timeout value before selected default multiple ID configuration */
NCS_PRI_VAR u32 m_ulMultipleIdSelectTimeout;
#endif
/* Group ID value allowed */
NCS_PRI_VAR u8 m_ubGroupIdVal;
#endif

/* Message processing status */
NCS_PRI_VAR tBlPduRStatus m_uTreatmentStatus;
/* Current active connection */
u8 m_ubCurrentConnection;
/* Store the connection number of the tester who successfully unlocks the ECU. */
u8 m_ubStoredConnection;
#if (BLPDUR_USE_STREAMING == STD_ON)
/* Store Streaming status- Allowed/ Prohibited */
NCS_PRI_VAR u8 m_ubStreamingSetting;
#endif
#if (BLPDUR_SOURCE_ADDRESS_CHECK_ENABLE == STD_ON)
/* Current used tester address */
NCS_PRI_VAR u8 m_ubTesterAddress;
#endif

#if (BLPDUR_NETWORK_LIN_SUPPORTED == STD_ON)
#if (BLPDUR_USE_LIN_MANAGE_CNT == STD_ON)
/* Counter to schedule the Lin module */
NCS_PRI_VAR u8 m_ubLinManageCnt;
#endif /*(BLPDUR_USE_LIN_MANAGE_CNT == STD_ON)*/
#if (BLPDUR_USE_LTP_MANAGE_CNT == STD_ON)
/* Counter to schedule the Ltp module */
NCS_PRI_VAR u8 m_ubLtpManageCnt;
#endif /*(BLPDUR_USE_LTP_MANAGE_CNT == STD_ON)*/
#endif /*(BLPDUR_NETWORK_LIN_SUPPORTED == STD_ON)*/

#if (BLPDUR_USE_UDS_MANAGE_CNT == STD_ON)
/* Counter to schedule the UDS module */
NCS_PRI_VAR u8 m_ubDiagManageCnt;
#endif /*(BLPDUR_USE_DIAG_MANAGE_CNT == STD_ON)*/

#if (BLPDUR_USE_PROG_MANAGE_CNT == STD_ON)
/* Counter to schedule the Prog module */
NCS_PRI_VAR u8 m_ubProgManageCnt;
#endif /*(BLPDUR_USE_PROG_MANAGE_CNT == STD_ON)*/

#if (BLPDUR_USE_SA_MANAGE_CNT == STD_ON)
/* Counter to schedule the SA module */
NCS_PRI_VAR u8 m_ubSAManageCnt;
#endif /*(BLPDUR_USE_SA_MANAGE_CNT == STD_ON)*/

#if (BLPDUR_UPDATE_TP_PARAM_ENABLE == STD_ON)
NCS_PRI_VAR u16 m_uwBlPduRTpBsVal;
NCS_PRI_VAR u16 m_uwBlPduRTpStminVal;
#endif /*(BLPDUR_USE_SA_MANAGE_CNT == STD_ON)*/
/*-------------------------------------------------------------------------------*/
/* - Private Macros                                                              */

/*-------------------------------------------------------------------------------*/
/* - Private Function Prototypes                                                 */
/*                                                                               */
#if (BLPDUR_SOURCE_ADDRESS_CHECK_ENABLE == STD_ON)
NCS_PRI_FCT StatusType BlPduR_VerifyTesterFilter(PduIdType RxPduId);
#endif
#if (BLPDUR_MULTIPLE_ID_ENABLE ==  STD_ON)
NCS_PRI_FCT void BlPduR_ConvertRxFuncPduId(PduIdType * pubRxPduId);
#endif
NCS_PRI_FCT void BlPduR_TpRxMsgManage (void);
NCS_PRI_FCT void BlPduR_ReleaseBuffers(tBufferInfoType* pBufferInfo);
#if (BLPDUR_MULTIPLE_ID_TYPE == BLPDUR_MULTIPLE_ID_CAN_NOTIFICATION)
/**
 ** \brief This service is used to select the identifier group used at runtime
 **
 ** \param[in] ubGroupID Group Id value
 **/
NCS_PRI_FCT void BlPduR_SelectGroupID(u8 ubGroupID);
#endif /* (BLPDUR_MULTIPLE_ID_TYPE == BLPDUR_MULTIPLE_ID_CAN_NOTIFICATION) */

#if (BLPDUR_USE_STREAMING == STD_ON)

/** \brief Streams the received data
 **
 ** This function notifies the PROG module on every Consecutive frame
 ** reception and pass the data buffer and the length of the actual
 ** data received for the current download block.
 **
 ** \param[in]  ulReceivedDataLength- Total Received message length
 ** \param[in]  aubData message data pointer
 **/
NCS_PRI_FCT void BlPduR_StreamingFrameReceived(u16 ulReceivedDataLength, u8* aubData);

/** \brief Set to allow/deny download data streaming
 **
 ** This function enables and disables the streaming of the received
 ** data during the runtime.
 **
 ** \param[in]  ubStreamingState - Expected Streaming state
 **/
NCS_PRI_FCT void BlPduR_SetStreamingStatus(u8 ubStreamingState);

#endif /* (BLPDUR_USE_STREAMING == STD_ON) */
/*===============================================================================*/


/*=============================== IMPLEMENTATION ================================*/
/*                                                                               */

/*-------------------------------------------------------------------------------*/
/* - Public Functions                                                            */

/*----------------------------------{BlPduR_Init}--------------------------------*/
void BlPduR_Init(void)
{
    DBG_BLPDUR_INIT_ENTRY();

    /* Initialization of the communication stack */
    BlPduR_Init1();

    /* Initialization of the rest of the bootloader stack */
    BlPduR_Init2();

    /* Initialize Functional buffer information */
    m_stRxFuncBufferInfo.filledLen = 0U;
    m_stRxFuncBufferInfo.dataMark = 0U;
    m_stRxFuncBufferInfo.confirmedDataMark = 0U;
    m_stRxFuncBufferInfo.state = BLPDUR_BUFF_IDLE;
    m_stRxFuncBufferInfo.originatingRxPduId = 0U;

#if (BLPDUR_ASR_NETWORK_PRESENT == STD_ON)
    /* Rx Functional Buffer configuration initialisation*/
    m_stRxFuncBufferConfig.ptrBuffer = &m_aubTPFuncBuffer[0];
    m_stRxFuncBufferConfig.bufferInfo = &m_stRxFuncBufferInfo;
    m_stRxFuncBufferConfig.size = BLPDUR_RX_FUNC_BUFFERSIZE;
#endif

#if ((BLPDUR_UPDATE_TP_PARAM_ENABLE == STD_ON) && (BLPDUR_NETWORK_CAN_SUPPORTED == STD_ON))
    m_uwBlPduRTpBsVal = BLPDUR_BS_DEFAULT;
    m_uwBlPduRTpStminVal = BLPDUR_STMIN_DEFAULT;
#endif

    DBG_BLPDUR_INIT_EXIT();
}
/*----------------------------------{end BlPduR_Init}----------------------------*/

/*----------------------------------{BlPduR_Init1}--------------------------------*/

void BlPduR_Init1(void)
{
    DBG_BLPDUR_INIT1_ENTRY();

    BlPduR_Custom_Com_Init();

#if (BLPDUR_NETWORK_LIN_SUPPORTED == STD_ON)
    BlPduR_Lin_Init();
#endif

    DBG_BLPDUR_INIT1_EXIT();
}

/*----------------------------------{end BlPduR_Init1}----------------------------*/

/*----------------------------------{BlPduR_Init2}--------------------------------*/
void BlPduR_Init2(void)
{
    u8 ubFlagIdx;
    DBG_BLPDUR_INIT2_ENTRY();

    /* Initialize connection and treatment status */
    m_ubCurrentConnection = BLPDUR_NO_ACTIVE_CONNECTION;
    m_ubStoredConnection = BLPDUR_NO_ACTIVE_CONNECTION;
    m_uTreatmentStatus = BLPDUR_E_IDLE;
#if (BLPDUR_USE_STREAMING == STD_ON)
    m_ubStreamingSetting= BLPDUR_STREAMING_ALLOWED;
#endif

    for (ubFlagIdx = 0U; ubFlagIdx < BLPDUR_RX_BUFFER; ubFlagIdx++)
    {
        /* Initialize all BLPDUR_RX_BUFFER reception buffers */
        m_apstReceptionBuffer[ubFlagIdx] = NULL_PTR;
    }

#if (BLPDUR_SOURCE_ADDRESS_CHECK_ENABLE == STD_ON)
    /* Initialize tester address */
    m_ubTesterAddress = BLPDUR_ALL_TESTER_ADDRESS;
#endif

#if (BLPDUR_USE_UDS_MANAGE_CNT == STD_ON)
    m_ubDiagManageCnt = 0U;
#endif /*(BLPDUR_USE_DIAG_MANAGE_CNT == STD_ON)*/

#if (BLPDUR_MULTIPLE_BUFFERS_ENABLE ==  STD_ON)
    m_ubBuffLockCount = 0U;

    for (ubFlagIdx = 0U; ubFlagIdx < BLPDUR_RX_PHY_BUFFER_NUM; ubFlagIdx++)
    {
        m_apstMultipleReceptionBuffer[ubFlagIdx] = NULL_PTR;
    }
#endif

#if (BLPDUR_QUEUED_MANAGEMENT_ENABLE == STD_ON)
    m_ubQueuedBuffCount = 0U;
    for (ubFlagIdx = 0U; ubFlagIdx < BLPDUR_RX_PHY_BUFFER_NUM; ubFlagIdx++)
    {
        m_apstQueuedReceptionBuffer[ubFlagIdx] = NULL_PTR;
    }
#endif
#if (BLPDUR_MULTIPLE_ID_ENABLE ==  STD_ON)
#if (BLPDUR_MULTIPLE_ID_TYPE == BLPDUR_MULTIPLE_ID_CAN_NOTIFICATION)
    /* Initialize timeout */
    m_ulMultipleIdSelectTimeout = BLPDUR_MULTIPLE_ID_TIMEOUT;
    /* Set the group ID as not yet selected */
    m_ubGroupIdVal = BLPDUR_MULTIPLE_ID_NO_SEL;

#elif (BLPDUR_MULTIPLE_ID_TYPE == BLPDUR_MULTIPLE_ID_EXTERNAL_NOTIFICATION)
    /* Retrieve the Group Id number */
    m_ubGroupIdVal = BlPduR_GetGroupIdVal();

    /* Check if value is in range */
    if(m_ubGroupIdVal >= BLPDUR_MULTIPLE_ID_CONF_MAX)
    {
        /* if value is out of range set default group */
        m_ubGroupIdVal = BLPDUR_ID_GROUP_DEFAULT;
    }
#else
    /* Nothing to do */
#endif
#endif

    /* Initialization of manage counters */
#if (BLPDUR_USE_PROG_MANAGE_CNT == STD_ON)
    m_ubProgManageCnt = 0U;
#endif /*(BLPDUR_USE_PROG_MANAGE_CNT == STD_ON)*/

#if (BLPDUR_USE_SA_MANAGE_CNT == STD_ON)
    m_ubSAManageCnt = 0U;
#endif /*(BLPDUR_USE_SA_MANAGE_CNT == STD_ON)*/

    /* Init */
#if (BLPDUR_USE_UDS == STD_ON)
    UDS_Init ();
#endif /*(BLPDUR_USE_UDS == STD_ON)*/
#if (BLPDUR_USE_FLASH == STD_ON)
    FLASH_Init ();
#endif /*(BLPDUR_USE_FLASH == STD_ON)*/
#if (BLPDUR_USE_PROG == STD_ON)
    PROG_Init ();
#endif /*(BLPDUR_USE_PROG == STD_ON)*/
#if (BLPDUR_USE_SA == STD_ON)
    SA_Init ();
#endif /*(BLPDUR_USE_SA == STD_ON)*/

    DBG_BLPDUR_INIT2_EXIT();
}
/*----------------------------------{end BlPduR_Init2}----------------------------*/

#if (BLPDUR_UPDATE_TP_PARAM_ENABLE == STD_ON)
/*----------------------------------{BlPduR_GetTpParameter}-------------------------*/
u16 BlPduR_GetTpParameter(tTpParameterId ubParameterId)
{
    u16 uwParameterValue;

    if(ubParameterId == BLPDUR_TP_BS)
    {
        uwParameterValue = m_uwBlPduRTpBsVal;
    }
    else /* if(ubParameterId == BLPDUR_TP_STMIN) */
    {
         uwParameterValue = m_uwBlPduRTpStminVal;
    }

    return uwParameterValue;
}
/*----------------------------------{end BlPduR_GetTpParameter}----------------------*/

/*----------------------------------{BlPduR_TpChangeParameter}-------------------------*/
tBlPduRStatus BlPduR_TpChangeParameter(tTpParameterId ubParameterId, u16 uwParameterValue)
{
    Std_ReturnType ePdurStatus;
    tBlPduRStatus eBlPdurStatus;
    u8 ubRxPduId;
    u8 ubIdx;
    u8 ubRxPduIdFound;

    /*Get the current Physical RxPduId*/
    /* Parse the table in order to find the current connection */
    ubRxPduId = 0U;
    ubRxPduIdFound = FALSE;
    for (ubIdx = 0U; ((BLPDUR_MAX_RX_PDU_NUM > ubIdx) && (TRUE != ubRxPduIdFound)); ubIdx++)
    {
        /* Filter on Addressing type Physical */
        if(BLPDUR_PHYSICAL == stRxPdu[ubIdx].AddressingType)
        {
            if (m_ubCurrentConnection == stRxPdu[ubIdx].ConnectionNum)
            {
                ubRxPduId = stRxPdu[ubIdx].RxPduId;
                ubRxPduIdFound = TRUE;
            }
            else
            {
                /* nothing to do */
            }
        }
        else
        {
            /* Functional RxPdu, nothing to do */
        }

    }

    if(TRUE == ubRxPduIdFound)
    {
        /*Change the parameter for the found Physical RxPduId*/
        ePdurStatus = PduR_BlPduRTpChangeParameter(ubRxPduId, ubParameterId, uwParameterValue);

        if(E_OK == ePdurStatus)
        {
            if(ubParameterId == BLPDUR_TP_BS)
            {
                m_uwBlPduRTpBsVal = uwParameterValue;
            }
            else /* if(ubParameterId == BLPDUR_TP_STMIN) */
            {
                m_uwBlPduRTpStminVal = uwParameterValue;
            }
            eBlPdurStatus = BLPDUR_E_OK;
        }
        else
        {
            eBlPdurStatus = BLPDUR_E_NOT_OK;
        }
    }
    else /* ubRxPduIdFound = FALSE */
    {
        eBlPdurStatus = BLPDUR_E_NOT_OK;
    }

    return eBlPdurStatus;
}
/*----------------------------------{end BlPduR_TpChangeParameter}----------------------*/
#endif /*(BLPDUR_UPDATE_TP_PARAM_ENABLE == STD_ON)*/

/*----------------------------------{BlPduR_Manage}--------------------------------*/
void BlPduR_Manage(void)
{
    DBG_BLPDUR_MANAGE_ENTRY();

    /* Process the Tp Rx Message */
    BlPduR_TpRxMsgManage();

#if (BLPDUR_MULTIPLE_ID_ENABLE ==  STD_ON) && (BLPDUR_MULTIPLE_ID_TYPE == BLPDUR_MULTIPLE_ID_CAN_NOTIFICATION)
    /* Check if the counter is activated */
    if(m_ulMultipleIdSelectTimeout > 0U)
    {
        /* If the counter timeout select default group ID */
        if(m_ulMultipleIdSelectTimeout == 1U)
        {
            /* Select the default ID group */
            BlPduR_SelectGroupID(BLPDUR_ID_GROUP_DEFAULT);
            m_ulMultipleIdSelectTimeout = 0U;
        }
        else
        {
            /* decrement counter */
            m_ulMultipleIdSelectTimeout--;
        }
    }
#endif
#if (BLPDUR_NETWORK_CAN_SUPPORTED == STD_ON)
    /* CanTp Main Function */
    CanTp_MainFunction();
#endif /*(BLPDUR_AUTOSAR_CAN == STD_ON)*/

#if (BLPDUR_NETWORK_LIN_SUPPORTED == STD_ON)
#if (BLPDUR_USE_LIN_MANAGE_CNT == STD_ON)
    /* Scheduler for Lin */
    if (m_ubLinManageCnt == ((LIN_MANAGE_PERIOD / BLPDUR_MANAGE_PERIOD) - 1U))
    {
        m_ubLinManageCnt = 0U;

        LIN_Manage ();
    }
    else
    {
        m_ubLinManageCnt++;
    }
#else
    LIN_Manage();
#endif /* (BLPDUR_USE_LIN_MANAGE_CNT == STD_ON)*/

#if (BLPDUR_USE_LTP_MANAGE_CNT == STD_ON)
    /* Scheduler for Lin */
    if (m_ubLtpManageCnt == ((LTP_MANAGE_PERIOD / BLPDUR_MANAGE_PERIOD) - 1U))
    {
        m_ubLtpManageCnt = 0U;

        LTP_Manage ();
    }
    else
    {
        m_ubLtpManageCnt++;
    }
#else
    LTP_Manage();
#endif /* BLPDUR_USE_LTP_MANAGE_CNT == STD_ON)*/
#endif /* (BLPDUR_NETWORK_LIN_SUPPORTED == STD_ON)*/

#if (BLPDUR_USE_UDS == STD_ON)
    /* Scheduler for Diagnostic */
#if (BLPDUR_USE_UDS_MANAGE_CNT == STD_ON)
    if (m_ubDiagManageCnt >= ((UDS_MANAGE_PERIOD / BLPDUR_MANAGE_PERIOD) - 1U))
    {
        m_ubDiagManageCnt = 0U;

        /* Diagnostic management */
        UDS_Manage ();
    }
    else
    {
        m_ubDiagManageCnt ++;
    }
#else
    /* Diagnostic management */
    UDS_Manage ();
#endif /*(BLPDUR_USE_DIAG_MANAGE_CNT == STD_ON)*/
#endif /*(BLPDUR_USE_UDS == STD_ON)*/


#if(BLPDUR_USE_PROG == STD_ON)
#if (BLPDUR_USE_PROG_MANAGE_CNT == STD_ON)
    /* Scheduler for PROG */
    if (m_ubProgManageCnt >= ((PROG_MANAGE_PERIOD / BLPDUR_MANAGE_PERIOD) - 1U))
    {
        m_ubProgManageCnt = 0U;

        /* PROG */
        PROG_Manage();
    }
    else
    {
        m_ubProgManageCnt ++;
    }
#else
    /* PROG management */
    PROG_Manage();
#endif /*(BLPDUR_USE_PROG_MANAGE_CNT == STD_ON)*/
#endif /*(BLPDUR_USE_PROG == STD_ON)*/

#if(BLPDUR_USE_SA == STD_ON)
#if (BLPDUR_USE_SA_MANAGE_CNT == STD_ON)
    /* Scheduler for SA */
    if (m_ubSAManageCnt >= ((SA_MANAGE_PERIOD / BLPDUR_MANAGE_PERIOD) - 1U))
    {
        m_ubSAManageCnt = 0U;

        /* SA management */
        SA_Manage();
    }
    else
    {
        m_ubSAManageCnt ++;
    }
#else
    /* SA management */
    SA_Manage();
#endif /*(BLPDUR_USE_SA_MANAGE_CNT == STD_ON)*/
#endif /*(BLPDUR_SA_PROG == STD_ON)*/

    DBG_BLPDUR_MANAGE_EXIT();

}
/*----------------------------------{end BlPduR_Manage}----------------------------*/

#if (BLPDUR_SOURCE_ADDRESS_CHECK_ENABLE == STD_ON)
/*----------------------------------{BlPduR_VerifyTesterFilter}--------------------------------*/
NCS_PRI_FCT StatusType BlPduR_VerifyTesterFilter(PduIdType RxPduId)
{
    u8 ubConnectionIndex;
    StatusType stdReturnValue;

    /* tester address is not set yet, accept connection */
    if(BLPDUR_ALL_TESTER_ADDRESS == m_ubTesterAddress)
    {
        stdReturnValue = E_OK;
    }
    else
    {
        if (RxPduId < BLPDUR_MAX_RX_PDU_NUM)
        {
#if (PROG_IMPL_VARIANT == PROG_IMPL_20)
            if (stRxPdu[RxPduId].RxPduType == BLPDUR_STANDARD_CAN_ID)
            {
                /* no test filtering on standard CAN */
                stdReturnValue = E_OK;
            }
            else
            {
#endif /* PROG_IMPL_VARIANT */
                /* get connection index */
                ubConnectionIndex = stRxPdu[RxPduId].ConnectionNum;
                /* get tester address associated to that connection */
                if (m_ubTesterAddress == stPduConnection[ubConnectionIndex].TestAddress)
                {
                    stdReturnValue = E_OK;
                }
                else
                {
                    stdReturnValue = E_NOT_OK;
                }
#if (PROG_IMPL_VARIANT == PROG_IMPL_20)
            }
#endif /* PROG_IMPL_VARIANT */
        }
        else
        {
            stdReturnValue = E_NOT_OK;
        }
    }
    return stdReturnValue;
}
/*----------------------------------{end BlPduR_VerifyTesterFilter}--------------------------------*/
#endif

/*----------------------------------{BlPduR_TpRxMsgManage}--------------------------------*/
NCS_PRI_FCT void BlPduR_TpRxMsgManage (void)
{
    /* Data and length of the Diagnostic messages */
    tBufferConfigType* pstRxCurrentBufferConfig;
    tBufferInfoType *curRxBufferInfo;
    PduIdType uTxPduId;
    u16 uwLen;
    u8* paubUdsData;
    tUdsBoolean eStatusRxReq;
#if((BLPDUR_ASR_NETWORK_PRESENT == STD_ON) || (BLPDUR_NETWORK_LIN_SUPPORTED == STD_ON))
    tBlPduRStatus eStatus= BLPDUR_E_OK;
#endif
#if((BLPDUR_RX_BUFFER)!=2U)
    u8 ubIdx=0U;
#endif

    DBG_BLPDUR_TPRXMSGMANAGE_ENTRY();

    /* Check if a complete TP frame has been received */
    if ((BLPDUR_E_IDLE == m_uTreatmentStatus) && (NULL_PTR != m_apstReceptionBuffer[0]))
    {
        /* Set the message processing status to busy*/
        m_uTreatmentStatus = BLPDUR_E_BUSY;

        /* Get the first pointer Rx Buffer configuration (order of treatment)*/
        pstRxCurrentBufferConfig = m_apstReceptionBuffer[0];

        /* Decrement buffer count before removing it from the reception list */
        m_ubReceiveBuffCount--;

        /* shift reception flag */
#if((BLPDUR_RX_BUFFER)!=2U)
        for(ubIdx = 0U; ubIdx < (BLPDUR_RX_BUFFER - 1U); ubIdx++)
        {
            m_apstReceptionBuffer[ubIdx] = m_apstReceptionBuffer[ubIdx + 1U];
        }
#else
        m_apstReceptionBuffer[0U] = m_apstReceptionBuffer[1U];
#endif

        /* reset last reception flag to ensure the invalid value */
        m_apstReceptionBuffer[BLPDUR_RX_BUFFER - 1U] = NULL_PTR;

#if (BLPDUR_QUEUED_MANAGEMENT_ENABLE == STD_ON)
        /* Check if requests are queued*/
        if (m_ubQueuedBuffCount != 0 )
        {
            /* Get the config information*/
            curRxBufferInfo = m_apstQueuedReceptionBuffer[0]->bufferInfo;
            /* Read the message length */
            uwLen = curRxBufferInfo->filledLen;
            /* Read the message data buffer address */
            paubUdsData = m_apstQueuedReceptionBuffer[0]->ptrBuffer;
        }
        else
#endif
        {
        /* Get the first pointer Rx Buffer configuration information (order of treatment)*/
        curRxBufferInfo = pstRxCurrentBufferConfig->bufferInfo;

        /* Read the message length */
        uwLen = curRxBufferInfo->filledLen;
        /* Read the message data buffer address */
        paubUdsData = pstRxCurrentBufferConfig->ptrBuffer;
        }

        /* Diagnostic request treatment */
        eStatusRxReq = UDS_RxRequestWithAddrMode (&uwLen, paubUdsData, stRxPdu[curRxBufferInfo->originatingRxPduId].AddressingType, UDS_TYPE_DIAG);

        if (eStatusRxReq == UDS_TRUE)
        {
            /* Get the transmission Pdu Id */
            uTxPduId = stPduConnection[m_ubCurrentConnection].TxPdu;

            /* Answer to the request only it is asked by DIAG layer */
            if (uwLen > 0U)
            {
#if (BLPDUR_NETWORK_LIN_SUPPORTED == STD_ON)
                if(BLPDUR_LIN_TX_PDU == uTxPduId)
                {
                    /* Write the answer message data */
                    eStatus = BlPduR_LinTpTxMessage(uwLen, paubUdsData);
                }
                else
#endif
                {
#if (BLPDUR_ASR_NETWORK_PRESENT == STD_ON)
                    /* Write the answer message data */
                    eStatus = BlPduR_SendMsgData (uTxPduId, uwLen, paubUdsData);
#endif
                }

#if((BLPDUR_ASR_NETWORK_PRESENT == STD_ON) || (BLPDUR_NETWORK_LIN_SUPPORTED == STD_ON))
                /* The message sending finished with error */
                if (eStatus != BLPDUR_E_OK)
                {
                    /* Call tx Conf with error status */
                    BlPduR_TxConf(uTxPduId, BLPDUR_E_NOT_OK);
                }
#endif
            }
            else
            {
                /* Simulate Tx confirmation to free the buffer */
                BlPduR_TxConf(uTxPduId, BLPDUR_E_OK);
            }

        }
        else if(eStatusRxReq == UDS_NRC_78)
        {
            /* Nothing to do */
        }
        else
        {
            /* Set back treatment status to IDLE */
            m_uTreatmentStatus = BLPDUR_E_IDLE;

            /* Get the transmission Pdu Id */
            uTxPduId = stPduConnection[m_ubCurrentConnection].TxPdu;
            /* Simulate Tx confirmation to free the buffer */
            BlPduR_TxConf(uTxPduId, BLPDUR_E_OK);
        }


    }/* End of Uds message */

    DBG_BLPDUR_TPRXMSGMANAGE_EXIT();

}
/*----------------------------------{end BlPduR_TpRxMsgManage}----------------------------*/

#if (BLPDUR_SOURCE_ADDRESS_CHECK_ENABLE == STD_ON)
/*----------------------------------{BlPduR_SaveTesterAddress}--------------------------------*/
FUNC(void, PDUR_CODE) BlPduR_SaveTesterAddress(void)
{
    DBG_BLPDUR_SAVETESTERADDRESS_ENTRY();

    m_ubTesterAddress = stPduConnection[m_ubCurrentConnection].TestAddress;
    /* also store the connection number related to the tester address */
    m_ubStoredConnection = m_ubCurrentConnection;

    DBG_BLPDUR_SAVETESTERADDRESS_EXIT();
}
/*----------------------------------{end BlPduR_SaveTesterAddress}--------------------------------*/
#endif

/*----------------------------------{BlPduR_StartOfReception}--------------------------------*/
/* request buffer for TP message reception */
#if (BLPDUR_ASR_NETWORK_PRESENT == STD_ON)
FUNC(BufReq_ReturnType, PDUR_CODE) BlPduR_StartOfReception
(
    PduIdType RxPduId,
    PduLengthType TpSduLength,
    P2VAR(PduLengthType, AUTOMATIC, PDUR_APPL_DATA) BufferSizePtr
)
{
    BufReq_ReturnType retVal = BUFREQ_E_NOT_OK;
#if (BLPDUR_SOURCE_ADDRESS_CHECK_ENABLE == STD_ON)
    StatusType stdTesterFilterStatus;
#endif
    tBufferInfoType *curRxBufferInfo;
#if (BLPDUR_MULTIPLE_BUFFERS_ENABLE ==  STD_ON)
    u8 ubBufferFound = BLPDUR_FALSE;
    u8 ubIdx;
#endif
#if (BLPDUR_QUEUED_MANAGEMENT_ENABLE ==  STD_ON)
    u8 ubBufferFound = BLPDUR_FALSE;
    u8 ubFullQueue = BLPDUR_TRUE;
    u8 ubIdx;
    u8 ubFlagIdx;
#endif
    PduIdType ubRxPduId = RxPduId;

    DBG_BLPDUR_STARTOFRECEPTION_ENTRY(RxPduId,TpSduLength,BufferSizePtr);

    if((BufferSizePtr != NULL_PTR))
    {
        /*Check Pdu in PduConfig*/
        if (ubRxPduId < BLPDUR_MAX_RX_PDU_NUM)
        {
#if (BLPDUR_SOURCE_ADDRESS_CHECK_ENABLE == STD_ON)
            /* Check if tester is allowed */
            stdTesterFilterStatus = BlPduR_VerifyTesterFilter(RxPduId);

            if(E_OK == stdTesterFilterStatus)

#endif
            {
#if (BLPDUR_MULTIPLE_ID_ENABLE ==  STD_ON)
                /* Convert PduId if necessary */
                BlPduR_ConvertRxFuncPduId(&ubRxPduId);
#endif
                /* Check connection status */
                if((m_ubCurrentConnection == BLPDUR_NO_ACTIVE_CONNECTION) || ( m_ubCurrentConnection == stRxPdu[ubRxPduId].ConnectionNum))
                {
                    /* Get current buffer */
                    if((BLPDUR_FUNCTIONAL == stRxPdu[ubRxPduId].AddressingType)
                            && ((m_pstRxCurrentBufferConfig == NULL_PTR)
                                || (m_pstRxCurrentBufferConfig->bufferInfo->state == BLPDUR_BUFF_IDLE)))
                    {
                        m_pstRxCurrentBufferConfig = &m_stRxFuncBufferConfig;
#if (BLPDUR_MULTIPLE_BUFFERS_ENABLE == STD_ON) || (BLPDUR_QUEUED_MANAGEMENT_ENABLE == STD_ON)
                        ubBufferFound = BLPDUR_TRUE;
#endif
                    }
#if (BLPDUR_QUEUED_MANAGEMENT_ENABLE == STD_ON)
/* CHECK: NOPARSE */
/* NOCOV-NCS_UNITARY_TEST*/
/* It's not possible to test else condition here */
                    else if(BLPDUR_PHYSICAL == stRxPdu[ubRxPduId].AddressingType)
                    {
/* CHECK: PARSE */
#else
                    else if((BLPDUR_PHYSICAL == stRxPdu[ubRxPduId].AddressingType) &&
                            ((m_pstRxCurrentBufferConfig == NULL_PTR) || (m_pstRxCurrentBufferConfig->bufferInfo->state != BLPDUR_BUFF_PROCESSING)))
                    {
#endif
#if (BLPDUR_MULTIPLE_BUFFERS_ENABLE ==  STD_ON)
                        for(ubIdx = 0U; (ubIdx < BLPDUR_RX_PHY_BUFFER_NUM) && (ubBufferFound == BLPDUR_FALSE); ubIdx++)
                        {
                            /* Get buffer Info */
                            curRxBufferInfo = stRxPhysBufferConfig[ubIdx].bufferInfo;
                            /* If RX in progress buffer shall be selected */
                            if((BLPDUR_BUFF_IDLE == curRxBufferInfo->state) || (BLPDUR_BUF_RX_IN_PROGRESS == curRxBufferInfo->state))
                            {
                                m_pstRxCurrentBufferConfig = &stRxPhysBufferConfig[ubIdx];
                                ubBufferFound = BLPDUR_TRUE;
                            }
                        }
#elif (BLPDUR_QUEUED_MANAGEMENT_ENABLE == STD_ON)
                        /* Check if the Queued is full */
                        for (ubFlagIdx = 0U; ubFlagIdx < BLPDUR_RX_PHY_BUFFER_NUM; ubFlagIdx++)
                        {
                            if (m_apstQueuedReceptionBuffer[ubFlagIdx] == NULL_PTR)
                            {
                                ubFullQueue = BLPDUR_FALSE;
                            }
                        }
                        if (ubFullQueue == BLPDUR_FALSE)
                        {
                            for(ubIdx = 0U; (ubIdx < BLPDUR_RX_PHY_BUFFER_NUM) && (ubBufferFound == BLPDUR_FALSE); ubIdx++)
                            {
                                /* Get buffer Info */
                                curRxBufferInfo = stRxPhysBufferConfig[ubIdx].bufferInfo;
                                /* If RX in progress buffer shall be selected */
                                if(BLPDUR_BUFF_IDLE == curRxBufferInfo->state)
                                {
                                    m_pstRxCurrentBufferConfig = &stRxPhysBufferConfig[ubIdx];
                                    ubBufferFound = BLPDUR_TRUE;
                                }
                            }
                        }
                        else
                        {
                           retVal = BUFREQ_E_NOT_OK;
                        }
#else
                        m_pstRxCurrentBufferConfig = &stRxPhysBufferConfig[0];
#endif
                    }
                    else
                    {
                        /* Frame rejected nothing to do */
                    }
#if (BLPDUR_MULTIPLE_BUFFERS_ENABLE ==  STD_ON) || (BLPDUR_QUEUED_MANAGEMENT_ENABLE == STD_ON)
                    if(ubBufferFound == BLPDUR_TRUE)
                    {
#else
                        if(((BLPDUR_FUNCTIONAL == stRxPdu[ubRxPduId].AddressingType)
                                && ((m_pstRxCurrentBufferConfig == NULL_PTR)
                                    || (m_pstRxCurrentBufferConfig->bufferInfo->state == BLPDUR_BUFF_IDLE)))
                                || ((m_pstRxCurrentBufferConfig->bufferInfo->state != BLPDUR_BUFF_PROCESSING)
                                    && (BLPDUR_PHYSICAL == stRxPdu[ubRxPduId].AddressingType)))
                        {
#endif

                            curRxBufferInfo = m_pstRxCurrentBufferConfig->bufferInfo;

                            if(BLPDUR_BUF_RX_IN_PROGRESS == curRxBufferInfo->state)
                            {
                                curRxBufferInfo->state = BLPDUR_BUFF_IDLE;
                                BlPduR_RxInd(ubRxPduId, BLPDUR_E_NOT_OK );
                            }

                            if(TpSduLength == 0U)
                            {
                                /*  When the API is invoked with TpSduLength equal to 0,
                                *  the value BUFREQ_OK shall be returned and BufferSizePtr shall be set to the
                                *  free size of the Rx buffer.
                                */
                                *BufferSizePtr = m_pstRxCurrentBufferConfig->size;
                                retVal = BUFREQ_OK;
                            }
                            else if(TpSduLength <= (m_pstRxCurrentBufferConfig->size))
                            {
                                /* allocate Rx buffer */
                                curRxBufferInfo->state              = BLPDUR_BUF_RX_IN_PROGRESS;
                                /* store the received DataLength */
                                curRxBufferInfo->filledLen          = TpSduLength;
                                /* remember ubRxPduId */
                                curRxBufferInfo->originatingRxPduId = ubRxPduId;
                                /* set current dataMark to 0 to signal where to copy new data. */
                                curRxBufferInfo->dataMark = 0U;
                                /* Update size of the allocated buffer to caller */
                                *BufferSizePtr = m_pstRxCurrentBufferConfig->size;

                                retVal = BUFREQ_OK;

#if (PROG_IMPL_VARIANT == PROG_IMPL_20)
                                /* All types other than STANDARD_CAN_ID changes the connection number. */
                                /* If m_ubStoredConnection is not set, m_ubCurrentConnection can be changed. */
                                if (  (stRxPdu[ubRxPduId].RxPduType != BLPDUR_STANDARD_CAN_ID)
                                   || (m_ubStoredConnection == BLPDUR_NO_ACTIVE_CONNECTION))
                                {
#endif /* PROG_IMPL_VARIANT */
                                    m_ubCurrentConnection = stRxPdu[ubRxPduId].ConnectionNum;
#if (PROG_IMPL_VARIANT == PROG_IMPL_20)
                                }
                                /* STANDARD_CAN_ID uses the stored connection number. */
                                else
                                {
                                    m_ubCurrentConnection = m_ubStoredConnection;
                                }
#endif /* PROG_IMPL_VARIANT */

#if (BLPDUR_USE_PROG == STD_ON)
                                PROG_TpStartOfReceptionInd(BLPDUR_E_OK);
#endif

                                /* Stop S3 timer on start of frame reception */
                                UDS_StopSessionTimer();
                            }
                            else
                            {
                                retVal = BUFREQ_E_OVFL;

#if (BLPDUR_USE_PROG == STD_ON)
                                PROG_TpStartOfReceptionInd(BLPDUR_E_NOT_OK);
#endif
                            }

                    }
                }
                else
                {
                    /*Unknow PduId*/
                    retVal = BUFREQ_E_NOT_OK;

#if (BLPDUR_USE_PROG == STD_ON)
                    PROG_TpStartOfReceptionInd(BLPDUR_E_NOT_OK);
#endif
                }
            }
#if (BLPDUR_SOURCE_ADDRESS_CHECK_ENABLE == STD_ON)

            else
            {
                /* Tester is not allowed */
                retVal = BUFREQ_E_NOT_OK;

#if (BLPDUR_USE_PROG == STD_ON)
                PROG_TpStartOfReceptionInd(BLPDUR_E_NOT_OK);
#endif
            }
#endif
        }
        else
        {
            /*Unknow PduId*/
            retVal = BUFREQ_E_NOT_OK;

#if (BLPDUR_USE_PROG == STD_ON)
            PROG_TpStartOfReceptionInd(BLPDUR_E_NOT_OK);
#endif
        }

    }
    else
    {
        retVal = BUFREQ_E_NOT_OK;

#if (BLPDUR_USE_PROG == STD_ON)
        PROG_TpStartOfReceptionInd(BLPDUR_E_NOT_OK);
#endif
    }

    DBG_BLPDUR_STARTOFRECEPTION_EXIT(retVal);

    return retVal;
}
#endif
/*----------------------------------{end BlPduR_StartOfReception}----------------------------*/

/*----------------------------------{BlPduR_CopyRxData}-------------------------------*/
/* Copy receive TP buffer to the wrapper receive buffer for every received segment */
#if (BLPDUR_ASR_NETWORK_PRESENT == STD_ON)
FUNC(BufReq_ReturnType, PDUR_CODE) BlPduR_CopyRxData
(
    PduIdType RxPduId,
    P2CONST(PduInfoType, AUTOMATIC, PDUR_APPL_CONST) PduInfoPtr,
    P2VAR(PduLengthType, AUTOMATIC, PDUR_APPL_DATA) BufferSizePtr
)
{
    /* Initialization */
    BufReq_ReturnType retVal = BUFREQ_E_NOT_OK;
    tBufferInfoType *curRxBufferInfo = NULL_PTR;
    PduIdType ubRxPduId = RxPduId;

    DBG_BLPDUR_COPYRXDATA_ENTRY(RxPduId,PduInfoPtr,BufferSizePtr);

    if((PduInfoPtr != NULL_PTR) && (BufferSizePtr != NULL_PTR))
    {
        /* get the current buffer info */
        curRxBufferInfo = m_pstRxCurrentBufferConfig->bufferInfo;

        if ((curRxBufferInfo->state) == BLPDUR_BUF_RX_IN_PROGRESS)
        {
            if ((PduInfoPtr->SduLength == 0U) || (PduInfoPtr->SduDataPtr == NULL_PTR))
            {
                /* return available buffer size */
                *BufferSizePtr = (m_pstRxCurrentBufferConfig->size) - (curRxBufferInfo->dataMark);
                retVal = BUFREQ_OK;
            }
            else
            {
                if(((curRxBufferInfo->dataMark)+(PduInfoPtr->SduLength)) <= (curRxBufferInfo->filledLen))
                {
                    /* copy payload into receive buffer */
                    TS_MemCpy(&(m_pstRxCurrentBufferConfig->ptrBuffer[curRxBufferInfo->dataMark]),
                            PduInfoPtr->SduDataPtr, (uint16)PduInfoPtr->SduLength
                           );

                    curRxBufferInfo->dataMark = (curRxBufferInfo->dataMark) + (PduInfoPtr->SduLength);

                    /* Return remaining free space in receive buffer after completion of this call */
                    *BufferSizePtr = (m_pstRxCurrentBufferConfig->size) - (curRxBufferInfo->dataMark);

#if (BLPDUR_USE_STREAMING == STD_ON)
                    /* Call TP streaming except for the last segment Streaming */
                    if(((curRxBufferInfo->dataMark)+(PduInfoPtr->SduLength)) < (curRxBufferInfo->filledLen))
                    {
                      BlPduR_StreamingFrameReceived((curRxBufferInfo->dataMark - 2U),m_pstRxCurrentBufferConfig->ptrBuffer);
                    }
#endif
                    retVal = BUFREQ_OK;
                }
                else
                {
                    retVal = BUFREQ_E_NOT_OK;
#if (BLPDUR_MULTIPLE_ID_ENABLE ==  STD_ON)
                    /* Convert PduId if necessary */
                    BlPduR_ConvertRxFuncPduId(&ubRxPduId);
#endif
                    BlPduR_RxInd(ubRxPduId, BLPDUR_E_NOT_OK );
                }
            }
        }
        else
        {
            /* No reception initiated on this RxPduId */
            *BufferSizePtr = 0U;
        }
    }
    else
    {
        retVal = BUFREQ_E_NOT_OK;
#if (BLPDUR_MULTIPLE_ID_ENABLE ==  STD_ON)
        /* Convert PduId if necessary */
        BlPduR_ConvertRxFuncPduId(&ubRxPduId);
#endif
        BlPduR_RxInd(ubRxPduId, BLPDUR_E_NOT_OK );
    }

    DBG_BLPDUR_COPYRXDATA_EXIT(retVal);

    return retVal;
}
#endif
/*----------------------------------{end BlPduR_CopyRxData}----------------------------*/

/*----------------------------------{BlPduR_TpRxIndication}-----------------------------*/
/* forward RxIndication */
#if (BLPDUR_ASR_NETWORK_PRESENT == STD_ON)
FUNC(void, PDUR_CODE) BlPduR_TpRxIndication
(
    PduIdType    RxPduId,
    NotifResultType  Result
)
{
    PduIdType ubRxPduId = RxPduId;

    DBG_BLPDUR_TPRXINDICATION_ENTRY(RxPduId,Result);
#if (BLPDUR_MULTIPLE_ID_ENABLE ==  STD_ON)
    /* Convert PduId if necessary */
    BlPduR_ConvertRxFuncPduId(&ubRxPduId);
#endif
    if(Result == NTFRSLT_OK)
    {
        BlPduR_RxInd(ubRxPduId, BLPDUR_E_OK );
    }
    else
    {
        BlPduR_RxInd(ubRxPduId, BLPDUR_E_NOT_OK );
    }

    DBG_BLPDUR_TPRXINDICATION_EXIT();
}
#endif
/*----------------------------------{end BlPduR_TpRxIndication}----------------------------*/

/*----------------------------------{BlPduR_RxInd}-------------------------------*/
void BlPduR_RxInd(PduIdType uRxPduId, tBlPduRStatus eBlPduRStatus)
{
    tBufferInfoType *curRxBufferInfo;

    if (BLPDUR_E_OK == eBlPduRStatus)
    {
      /* If the Tester Present is received with suppress positive Response bit set */
      /* and with correct length                                                   */
      if ((m_pstRxCurrentBufferConfig->ptrBuffer[0] == 0x3EU) &&
          (m_pstRxCurrentBufferConfig->ptrBuffer[1] == 0x80U) &&
          (m_pstRxCurrentBufferConfig->bufferInfo->filledLen == 2))
      {
        /* Reload S3 timer */
        UDS_ReloadTStopDiag();

        /* Re-initialize the connection */
        m_ubCurrentConnection = BLPDUR_NO_ACTIVE_CONNECTION;

       /* Set the buffer state to Idle */
        m_pstRxCurrentBufferConfig->bufferInfo->state = BLPDUR_BUFF_IDLE;

      }
      else
      {
          /* Set current buffer to processing state */
          curRxBufferInfo = m_pstRxCurrentBufferConfig->bufferInfo;

          curRxBufferInfo->state = BLPDUR_BUFF_PROCESSING;
          /* The buffer reception order shall stored */
          m_apstReceptionBuffer[m_ubReceiveBuffCount] = m_pstRxCurrentBufferConfig;
          m_ubReceiveBuffCount++;

#if (BLPDUR_QUEUED_MANAGEMENT_ENABLE == STD_ON)
#if (BLPDUR_PROG_2_SUCCESSIVE_CHECKMEMORY_ALLOWED == STD_ON)
        if ((m_pstRxCurrentBufferConfig->ptrBuffer[0] == BLPDUR_UDS_SRV_RCONTROL) &&
            (m_pstRxCurrentBufferConfig->ptrBuffer[2] == BLPDUR_UDS_CHECK_MEMORY_RID_0) &&
            (m_pstRxCurrentBufferConfig->ptrBuffer[3] == BLPDUR_UDS_CHECK_MEMORY_RID_1) &&
            (m_ubQueuedBuffCount !=0))
        {
            /* The previous request and the current one are CheckMemory requests ? */
            if ((m_apstQueuedReceptionBuffer[m_ubQueuedBuffCount - 1]->ptrBuffer [0] == m_pstRxCurrentBufferConfig->ptrBuffer [0]) &&
                (m_apstQueuedReceptionBuffer[m_ubQueuedBuffCount - 1]->ptrBuffer [2] == m_pstRxCurrentBufferConfig->ptrBuffer [2]) &&
                (m_apstQueuedReceptionBuffer[m_ubQueuedBuffCount - 1]->ptrBuffer [3] == m_pstRxCurrentBufferConfig->ptrBuffer [3]))
            {
                /* Do not queue a consecutive CheckMemory */
            }
            else
            {
                /* The buffer reception order shall stored for the queued treatment */
                m_apstQueuedReceptionBuffer[m_ubQueuedBuffCount] = m_pstRxCurrentBufferConfig;
                /* Increment the number of Queued requests */
                m_ubQueuedBuffCount++;
            }
        }
        else
#endif
        {
            /* The buffer reception order shall stored for the queued treatment */
            m_apstQueuedReceptionBuffer[m_ubQueuedBuffCount] = m_pstRxCurrentBufferConfig;
            /* Increment the number of Queued requests */
            m_ubQueuedBuffCount++;
        }
#endif
          /* Stop S3 timer */
          UDS_StopSessionTimer();

#if (BLPDUR_USE_STREAMING == STD_ON)
          /* Set the Streaming status to Forbidden until the request/s processing is completed */
          BlPduR_SetStreamingStatus(BLPDUR_STREAMING_FORBIDDEN);
#endif
      }
    }
    else
    {
      /* Reload S3 timer */
      UDS_ReloadTStopDiag();

#if (BLPDUR_QUEUED_MANAGEMENT_ENABLE == STD_ON)
      if (m_ubQueuedBuffCount <= 1)
#endif
      {
#if (BLPDUR_USE_STREAMING == STD_ON)
      /* Set the Streaming status to Allowed as there was error while receiving the request */
      BlPduR_SetStreamingStatus(BLPDUR_STREAMING_ALLOWED);
#endif
      }
    }

    /* PduId cast to be compatible with old prototype format */
    APP_TpRxInd((u8)(uRxPduId & 0x00FFU), eBlPduRStatus);
#if (BLPDUR_USE_PROG == STD_ON)
    /* PduValue cast to be compatible with old prototype format */
    PROG_TpRxInd((u8)(uRxPduId & 0x00FFU), eBlPduRStatus);
#endif

}
/*----------------------------------{end BlPduR_RxInd}----------------------------*/


/*---------------------------[BlPduR_SendMsgData]----------------------------------*/
#if (BLPDUR_ASR_NETWORK_PRESENT == STD_ON)
/* Function used to trigger transmission */
tBlPduRStatus BlPduR_SendMsgData (PduIdType PduId, u16 uwLen, u8 *paubData)
{
    tBlPduRStatus retVal = BLPDUR_E_OK;
    PduInfoType TxInformation;
    Std_ReturnType RetCode;

    DBG_BLPDUR_SENDMSGDATA_ENTRY(PduId,uwLen,paubData);

    if((paubData != NULL_PTR) && (uwLen != 0U))
    {
        /* Update transmission buffer */
        m_pubTxBuffer = paubData;
        m_stTxBufferInfo.filledLen = uwLen;

        /* Update transmission information given to PduR module*/
        TxInformation.SduDataPtr = NULL_PTR;
        TxInformation.SduLength = (PduLengthType)uwLen;
        RetCode = PduR_BlPduRTransmit(PduId, &TxInformation);

        if (RetCode != E_OK)
        {
            retVal = BLPDUR_E_NOT_OK;
        }
    }
    else
    {
        retVal = BLPDUR_E_NOT_OK;
    }

    DBG_BLPDUR_SENDMSGDATA_EXIT(retVal);

    return retVal;
}
#endif
/*----------------------------------{end BlPduR_SendMsgData}----------------------------*/

/*----------------------------------{BlPduR_CopyTxData}-------------------------------*/
/* Copy transmission TP buffer */
#if (BLPDUR_ASR_NETWORK_PRESENT == STD_ON)
FUNC(BufReq_ReturnType, PDUR_CODE) BlPduR_CopyTxData
(
    PduIdType TxPduId,
    P2VAR(PduInfoType, AUTOMATIC, PDUR_APPL_DATA) PduInfoPtr,
    P2VAR(RetryInfoType, AUTOMATIC, PDUR_APPL_DATA) RetryInfoPtr,
    P2VAR(PduLengthType, AUTOMATIC, PDUR_APPL_DATA) AvailableDataPtr
)
{
    BufReq_ReturnType retVal = BUFREQ_E_NOT_OK;

    DBG_BLPDUR_COPYTXDATA_ENTRY(TxPduId,PduInfoPtr,RetryInfoPtr,AvailableDataPtr);

    OSC_PARAM_UNUSED(TxPduId);

    if((PduInfoPtr != NULL_PTR) && (AvailableDataPtr != NULL_PTR))
    {
        if(PduInfoPtr->SduLength == 0U)
        {
            /* TP layer polls length of transmission, supply length of data */
            *AvailableDataPtr = m_stTxBufferInfo.filledLen;
            retVal = BUFREQ_OK;
        }
        else if (RetryInfoPtr == NULL_PTR)
        {
            /* copy data */
            TS_MemCpy(PduInfoPtr->SduDataPtr, &m_pubTxBuffer[m_stTxBufferInfo.dataMark],
                    (uint16)PduInfoPtr->SduLength);

            /* Supply length of remaining data */
            m_stTxBufferInfo.dataMark += PduInfoPtr->SduLength;
            *AvailableDataPtr = m_stTxBufferInfo.filledLen - m_stTxBufferInfo.dataMark;

            retVal = BUFREQ_OK;
        }
        else
        {
            retVal = BUFREQ_E_NOT_OK;
        }
    }
    else
    {
        retVal = BUFREQ_E_NOT_OK;
    }

    DBG_BLPDUR_COPYTXDATA_EXIT(retVal);

    return retVal;
}
#endif
/*----------------------------------{end BlPduR_CopyTxData}----------------------------*/

/*----------------------------------{BlPduR_TpTxConfirmation}---------------------------*/
/* forward TxConfirmation */
#if (BLPDUR_ASR_NETWORK_PRESENT == STD_ON)
FUNC(void, PDUR_CODE) BlPduR_TpTxConfirmation
(
    PduIdType    TxPduId,
    NotifResultType  Result
)
{
    DBG_BLPDUR_TPTXCONFIRMATION_ENTRY(TxPduId,Result);

    if(Result == NTFRSLT_OK)
    {
        BlPduR_TxConf(TxPduId, BLPDUR_E_OK);
    }
    else
    {
        BlPduR_TxConf(TxPduId, BLPDUR_E_NOT_OK);
    }

    DBG_BLPDUR_TPTXCONFIRMATION_EXIT();
}
#endif
/*----------------------------------{end BlPduR_TpTxConfirmation}----------------------------*/

/*----------------------------------{BlPduR_TxConf}-------------------------------*/
void BlPduR_TxConf(PduIdType uTxPduId, tBlPduRStatus eBlPduRStatus)
{
#if (BLPDUR_QUEUED_MANAGEMENT_ENABLE != STD_ON)
    tBufferInfoType *curRxBufferInfo;
#endif
#if (BLPDUR_QUEUED_MANAGEMENT_ENABLE == STD_ON)
    u8 ubIdx;
#endif
    if (m_uTreatmentStatus == BLPDUR_E_BUSY)
    {
        if (NULL_PTR == m_pubTxBuffer)
        {
            m_uTreatmentStatus = BLPDUR_E_IDLE;
        }
        else if((m_pubTxBuffer[0] == UDS_NRC) && (m_pubTxBuffer[2] == UDS_NRC_78))
        {
            UDS_LongRequestRespTxConf();
        }
        else
        {
            m_uTreatmentStatus = BLPDUR_E_IDLE;
        }
    }

    if((m_uTreatmentStatus == BLPDUR_E_IDLE) && (m_pstRxCurrentBufferConfig != NULL_PTR))
    {
#if (BLPDUR_QUEUED_MANAGEMENT_ENABLE != STD_ON)
        curRxBufferInfo = m_pstRxCurrentBufferConfig->bufferInfo;
#endif
#if (BLPDUR_QUEUED_MANAGEMENT_ENABLE == STD_ON)
        /* Release the buffer for the request just responded */
        BlPduR_ReleaseBuffers(m_apstQueuedReceptionBuffer[0U]->bufferInfo);
        /* shift reception flag */
        for(ubIdx = 0U; ubIdx < (BLPDUR_RX_PHY_BUFFER_NUM - 1U); ubIdx++)
        {
            m_apstQueuedReceptionBuffer[ubIdx] = m_apstQueuedReceptionBuffer[ubIdx + 1U];
        }
        /* reset last reception flag to ensure the invalid value */
        m_apstQueuedReceptionBuffer[BLPDUR_RX_PHY_BUFFER_NUM - 1U] = NULL_PTR;
        /* Decrement count of queued buffers*/
        m_ubQueuedBuffCount--;
#endif
        /* Release Rx buffer */
#if (BLPDUR_MULTIPLE_BUFFERS_ENABLE == STD_ON)
        if (curRxBufferInfo->state != BLPDUR_BUFF_LOCK)
#endif /*(BLPDUR_MULTIPLE_BUFFERS_ENABLE == STD_ON)*/
#if (BLPDUR_QUEUED_MANAGEMENT_ENABLE != STD_ON)
        {
            /*if not lock buffer can be released */
            BlPduR_ReleaseBuffers(curRxBufferInfo);
        }
#endif /* (BLPDUR_QUEUED_MANAGEMENT_ENABLE != STD_ON) */

        /* Reload S3 timer */
        UDS_ReloadTStopDiag();
    }

    if(m_uTreatmentStatus == BLPDUR_E_IDLE)
    {
        /* Re-Initialize current Connection */
        m_ubCurrentConnection = BLPDUR_NO_ACTIVE_CONNECTION;
    }

    /* Release Tx buffer */
    BlPduR_ReleaseBuffers(&m_stTxBufferInfo);

/* PduId cast to be compatible with old prototype format */
    APP_TpTxConf((u8)(uTxPduId & 0x00FFU), eBlPduRStatus);
#if (BLPDUR_USE_PROG == STD_ON)
/* PduId cast to be compatible with old prototype format */
    PROG_TpTxConf((u8)(uTxPduId & 0x00FFU), eBlPduRStatus);
#endif
}
/*----------------------------------{end BlPduR_TxConf}----------------------------*/

/*----------------------------------{BlPduR_ReleaseBuffers}------------------------*/
NCS_PRI_FCT void BlPduR_ReleaseBuffers(tBufferInfoType* pBufferInfo)
{
    /* set buffer state to idle */
    pBufferInfo->state = BLPDUR_BUFF_IDLE;
    /* reset filled buffer length */
    pBufferInfo->filledLen = 0;
    /* reset buffer data marking variables */
    pBufferInfo->confirmedDataMark = 0U;
    pBufferInfo->dataMark = 0U;
#if (BLPDUR_QUEUED_MANAGEMENT_ENABLE == STD_ON)
    if (m_ubQueuedBuffCount < 1)
#endif
    {
#if (BLPDUR_USE_STREAMING == STD_ON)
    /* When no messages in Queue for the further processing, allow streaming */
    BlPduR_SetStreamingStatus(BLPDUR_STREAMING_ALLOWED);
#endif
    }
}
/*----------------------------------{end BlPduR_RxInd}----------------------------*/

/*----------------------------------{UDS_SessionStatusInd}--------------------------------*/
void UDS_SessionStatusInd (tUdsSessionType eUdsNewSessType,tUdsSessionType eUdsOldSessType,tUdsChangeReason eUdsChangingCause)
{

    DBG_UDS_SESSIONSTATUSIND_ENTRY(eUdsNewSessType,eUdsOldSessType,eUdsChangingCause);
#if (BLPDUR_USE_PROG == STD_ON)
    if(eUdsNewSessType == UDS_SESSION_PROGRAMMING)
    {
        /* action to perform on programming session opening */
        PROG_OpenProgrammingSession();
    }
    else
    {
        /* if leaving programming session */
        if(eUdsOldSessType == UDS_SESSION_PROGRAMMING)
        {

            PROG_CloseProgrammingSession(eUdsChangingCause);
        }
        else
        {
            /* Nothing to do */
        }
    }
#endif /*(BLPDUR_USE_PROG == STD_ON)*/
    /* Notify for diagnostic session transition */
    APP_UdsSessionStatusInd (eUdsNewSessType, eUdsOldSessType, eUdsChangingCause);

    DBG_UDS_SESSIONSTATUSIND_EXIT();
}
/*----------------------------------{end UDS_SessionStatusInd}----------------------------*/



/*----------------------------{BlPduR_SetTesterAddress}------------------------------*/
#if (BLPDUR_SOURCE_ADDRESS_CHECK_ENABLE == STD_ON)
void BlPduR_SetTesterAddress(u8 ubTesterAddress)
{
    u8 ubIdx;
    u8 ubFound;
    ubFound = BLPDUR_FALSE;

    DBG_BLPDUR_SETTESTERADDRESS_ENTRY(ubTesterAddress);

    /* Check if tester address given is configured
     * If it exist store current connection */
    for(ubIdx = 0U; (ubIdx < BLPDUR_MAX_PDU_CONNECTION) && (ubFound != BLPDUR_TRUE); ubIdx++)
    {
        if (ubTesterAddress == stPduConnection[ubIdx].TestAddress)
        {
            /* Store tester address and connection */
            m_ubTesterAddress = ubTesterAddress;
            m_ubCurrentConnection = ubIdx;
            m_ubStoredConnection = ubIdx;
            ubFound = BLPDUR_TRUE;
        }
    }

    /* If the tester address given is not correct
     * set default connection and all tester allowed */
    if(ubFound == BLPDUR_FALSE)
    {
        m_ubTesterAddress = BLPDUR_ALL_TESTER_ADDRESS;
        m_ubCurrentConnection = BLPDUR_NO_ACTIVE_CONNECTION;
    }

    DBG_BLPDUR_SETTESTERADDRESS_EXIT();
}
#endif
/*-------------------------{end BlPduR_SetTesterAddress}-----------------------------*/

/*----------------------------{BlPduR_StoreConnectionInfo}------------------------------*/
void BlPduR_StoreConnectionInfo(void)
{
    u8 ubRxPduId;
    u8 ubIdx;
    u8 ubRxPduIdFound;

    DBG_BLPDUR_STORECONNECTIONINFO_ENTRY();

    /*Get the current Physical RxPduId*/
    /* Parse the table in order to find the current connection */
    ubRxPduId = 0U;
    ubRxPduIdFound = FALSE;
    for (ubIdx = 0U; ((BLPDUR_MAX_RX_PDU_NUM > ubIdx) && (TRUE != ubRxPduIdFound)); ubIdx++)
    {
        /* Filter on Addressing type Physical */
        if(BLPDUR_PHYSICAL == stRxPdu[ubIdx].AddressingType)
        {
            if (m_ubCurrentConnection == stRxPdu[ubIdx].ConnectionNum)
            {
                ubRxPduId = stRxPdu[ubIdx].RxPduId;
                ubRxPduIdFound = TRUE;
            }
            else
            {
                /* nothing to do */
            }
        }
        else
        {
            /* Functional RxPdu, nothing to do */
        }

    }

    /* Callback to store the RxPduId */
    BlPduR_StoreRxPduId(ubRxPduId);

    DBG_BLPDUR_STORECONNECTIONINFO_EXIT();
}
/*-------------------------{end BlPduR_StoreConnectionInfo}-----------------------------*/

/*----------------------------{BlPduR_RetrieveConnectionInfo}------------------------------*/
void BlPduR_RetrieveConnectionInfo(void)
{
    u8 ubRxPduId;

    DBG_BLPDUR_RETRIEVECONNECTIONINFO_ENTRY();

    BlPduR_GetRxPduId(&ubRxPduId);

    /* If index is in the range of the table */
    if (BLPDUR_MAX_RX_PDU_NUM > ubRxPduId)
    {
        /* Store tester address and connection */
#if (BLPDUR_SOURCE_ADDRESS_CHECK_ENABLE == STD_ON)
        m_ubTesterAddress = stPduConnection[stRxPdu[ubRxPduId].ConnectionNum].TestAddress;
#endif
        m_ubCurrentConnection = stRxPdu[ubRxPduId].ConnectionNum;
#if (BLPDUR_MULTIPLE_ID_ENABLE ==  STD_ON)
        m_ubGroupIdVal = stRxPdu[ubRxPduId].GroupId;
#endif
    }
    else
    {
        /* Set default connection and all tester allowed */
#if (BLPDUR_SOURCE_ADDRESS_CHECK_ENABLE == STD_ON)
        m_ubTesterAddress = BLPDUR_ALL_TESTER_ADDRESS;
#endif

        m_ubCurrentConnection = BLPDUR_NO_ACTIVE_CONNECTION;
#if (BLPDUR_MULTIPLE_ID_ENABLE ==  STD_ON)
        m_ubGroupIdVal = BLPDUR_MULTIPLE_ID_NO_SEL;
#endif
    }

    DBG_BLPDUR_RETRIEVECONNECTIONINFO_EXIT();
}
/*-------------------------{end BlPduR_RetrieveConnectionInfo}-----------------------------*/

/*----------------------------{BlPduR_Send_TPFrame}------------------------------*/
void BlPduR_Send_TPFrame(u16 uwLen, u8 *paubData)
{
    PduIdType uTxPduId;

    DBG_BLPDUR_SEND_TPFRAME_ENTRY(uwLen,paubData);

    /* Get the Tx Pdu Id of the current connection */
    uTxPduId = stPduConnection[m_ubCurrentConnection].TxPdu;

#if (BLPDUR_NETWORK_LIN_SUPPORTED == STD_ON)
    if(BLPDUR_LIN_TX_PDU == uTxPduId)
    {
        (void)BlPduR_LinTpTxMessage(uwLen, paubData);
    }
    else
#endif
    {
#if (BLPDUR_ASR_NETWORK_PRESENT == STD_ON)
        if (0U != uwLen)
        {
            /* Send the frame */
            (void)BlPduR_SendMsgData(uTxPduId, uwLen, paubData);
        }
        else
        {
            /* Simulate Tx confirmation to free the buffer */
            BlPduR_TxConf(uTxPduId, BLPDUR_E_OK);
        }
#endif
    }

    DBG_BLPDUR_SEND_TPFRAME_EXIT();

}
/*-------------------------{end BlPduR_Send_TPFrame}-----------------------------*/

/*----------------------------{BlPduR_SimulateRxRequest}------------------------------*/
/* Deviation MISRA-2 */
void BlPduR_SimulateRxRequest(u16 uwLen, u8 * paubUdsData, u8 ubWithResp)
{
    DBG_BLPDUR_SIMULATERXREQUEST_ENTRY(uwLen,paubUdsData, ubWithResp);
    if (ubWithResp == TRUE)
    {
        m_uTreatmentStatus = BLPDUR_E_BUSY;
    }
    (void)UDS_RxRequest(&uwLen, paubUdsData);

    DBG_BLPDUR_SIMULATERXREQUEST_EXIT();
}
/*-------------------------{end BlPduR_SimulateRxRequest}-----------------------------*/

/*-------------------------------{BlPduR_LockBuffer}------------------------------*/
#if (BLPDUR_MULTIPLE_BUFFERS_ENABLE ==  STD_ON)
void BlPduR_LockBuffer(u8* pubIsLastBuffer)
{
    tBufferInfoType *curRxBufferInfo;

    DBG_BLPDUR_LOCKBUFFER_ENTRY(pubIsLastBuffer);

    /* The buffer reception order shall stored for the multiplebuffer treatment */
    m_apstMultipleReceptionBuffer[m_ubBuffLockCount] = m_pstRxCurrentBufferConfig;

    /* Set the buffer in lock state */
    curRxBufferInfo = m_pstRxCurrentBufferConfig->bufferInfo;
    curRxBufferInfo->state = BLPDUR_BUFF_LOCK;

    /* Increment the number of lock buffer */
    m_ubBuffLockCount++;

    /* Check if all the buffer are locked */
    if (BLPDUR_RX_PHY_BUFFER_NUM == m_ubBuffLockCount)
    {
        *pubIsLastBuffer = BLPDUR_TRUE;
    }
    else
    {
        *pubIsLastBuffer = BLPDUR_FALSE;
    }

    DBG_BLPDUR_LOCKBUFFER_EXIT();
}
#endif
/*----------------------------{end BlPduR_LockBuffer}-----------------------------*/

/*-----------------------------{BlPduR_UnlockBuffer}------------------------------*/
#if (BLPDUR_MULTIPLE_BUFFERS_ENABLE ==  STD_ON)
void BlPduR_UnlockBuffer(u8 ubBufferType)
{
    u8 ubIdx;

    DBG_BLPDUR_UNLOCKBUFFER_ENTRY(ubBufferType);

    /* If buffer is the first buffer locked */
    if (BLPDUR_OLD_BUFFER == ubBufferType)
    {
        BlPduR_ReleaseBuffers(m_apstMultipleReceptionBuffer[0]->bufferInfo);

        /* shift reception flag */
        for(ubIdx = 0U; ubIdx < (BLPDUR_RX_PHY_BUFFER_NUM - 1U); ubIdx++)
        {
            m_apstMultipleReceptionBuffer[ubIdx] = m_apstMultipleReceptionBuffer[ubIdx + 1U];
        }

        /* reset last reception flag to ensure the invalid value */
        m_apstMultipleReceptionBuffer[BLPDUR_RX_PHY_BUFFER_NUM - 1U] = NULL_PTR;

        /* Decrement count of buffer locked */
        m_ubBuffLockCount--;
    }
    /* otherwise reset all buffers */
    else
    {
        for(ubIdx = 0U;ubIdx <BLPDUR_RX_PHY_BUFFER_NUM; ubIdx++)
        {
            /* Release all buffer */
            BlPduR_ReleaseBuffers(stRxPhysBufferConfig[ubIdx].bufferInfo);
            /* release all queued element */
            m_apstMultipleReceptionBuffer[ubIdx] = NULL_PTR;
        }

        /* Reinit the counter */
        m_ubBuffLockCount = 0U;
    }

    DBG_BLPDUR_UNLOCKBUFFER_EXIT();
}
#endif
/*--------------------------{end BlPduR_UnlockBuffer}-----------------------------*/

/*----------------------------{BlPduR_GetNextBuffer}------------------------------*/
#if (BLPDUR_MULTIPLE_BUFFERS_ENABLE ==  STD_ON)
void BlPduR_GetNextBuffer(u16* puwLen, u8 ** paubData)
{
    DBG_BLPDUR_GETNEXTBUFFER_ENTRY(puwLen,paubData);

    if(m_apstMultipleReceptionBuffer[0] == NULL_PTR)
    {
        /* First buffer is not locked. No buffer is taken*/
        *paubData = NULL_PTR;
        *puwLen = 0U;
    }
    else
    {
        /* First buffer is taken*/
        *paubData = m_apstMultipleReceptionBuffer[0U]->ptrBuffer;
        *puwLen = m_apstMultipleReceptionBuffer[0U]->bufferInfo->filledLen;
    }

    DBG_BLPDUR_GETNEXTBUFFER_EXIT();
}
#endif
/*-------------------------{end BlPduR_GetNextBuffer}-----------------------------*/

/*----------------------------{BlPduR_RxIndication}------------------------------*/
#if (BLPDUR_MULTIPLE_ID_ENABLE ==  STD_ON) && (BLPDUR_MULTIPLE_ID_TYPE == BLPDUR_MULTIPLE_ID_CAN_NOTIFICATION)
FUNC(void, PDUR_CODE) BlPduR_RxIndication
(
   PduIdType RxPduId,
   P2VAR(PduInfoType, AUTOMATIC, PDUR_APPL_DATA) PduInfoPtr
)
{
    u8 ubArchitectureId;
    u8 ubGroupID;
    u8 ubGroupIdx;

    DBG_BLPDUR_RXINDICATION_ENTRY(RxPduId,PduInfoPtr);

    /* Initialize Id Group */
    ubGroupID = BLPDUR_MULTIPLE_ID_NO_SEL;

    /* Retrieve the architecture ID from the PDU */
    ubArchitectureId = PduInfoPtr->SduDataPtr[BLPDUR_MULTIPLE_ID_BYTE_IDX_IN_DATA];

    OSC_PARAM_UNUSED(RxPduId);

    /* For all group ID configured */
    for(ubGroupIdx = 0U; ubGroupIdx < BLPDUR_ID_GROUP_NUM; ubGroupIdx++)
    {
        /* Check if the architecture ID is present in the group ID */
        if(stMultipleIdConfig[ubGroupIdx].ArchitectureId == ubArchitectureId)
        {
            /* Select the correct group ID */
            ubGroupID = ubGroupIdx;
        }
    }

    /* Check if Group ID is in the configured range */
    /* If not wait for a known ID */
    if(ubGroupID < BLPDUR_MULTIPLE_ID_CONF_MAX)
    {
        /* Call API to select received group ID */
        BlPduR_SelectGroupID(ubGroupID);
    }

    DBG_BLPDUR_RXINDICATION_EXIT();
}
#endif
/*-------------------------{end BlPduR_RxIndication}-----------------------------*/

/*----------------------------{BlPduR_SelectGroupID}------------------------------*/
#if (BLPDUR_MULTIPLE_ID_ENABLE ==  STD_ON) && (BLPDUR_MULTIPLE_ID_TYPE == BLPDUR_MULTIPLE_ID_CAN_NOTIFICATION)
NCS_PRI_FCT void BlPduR_SelectGroupID(u8 ubGroupID)
{
    DBG_BLPDUR_SELECTGROUPID_ENTRY(ubGroupID);

    /* Check if the group ID is already known */
    if(m_ubGroupIdVal == BLPDUR_MULTIPLE_ID_NO_SEL)
    {
        /* Stop the counter for default selection */
        m_ulMultipleIdSelectTimeout = 0U;
        /* Set the group ID */
        m_ubGroupIdVal = ubGroupID;
    }

    DBG_BLPDUR_SELECTGROUPID_EXIT();
}
#endif
/*-------------------------{end BlPduR_SelectGroupID}-----------------------------*/

/*----------------------------{CanLPduReceiveCalloutFunction}------------------------------*/
#if (BLPDUR_MULTIPLE_ID_ENABLE ==  STD_ON)
FUNC(boolean, COM_APPL_CODE) BlPduR_GroupIdFrameFilter(Can_HwHandleType Hrh,Can_IdType CanId,uint8 CanDlc,const uint8 *CanSduPtr)
{
    boolean RetVal;
    uint8 Idx;
    Can_IdType LocalCanID;

    DBG_BLPDUR_GROUPIDFRAMEFILTER_ENTRY(Hrh, CanId, CanDlc, CanSduPtr);

    OSC_PARAM_UNUSED(Hrh);
    OSC_PARAM_UNUSED(CanDlc);
    OSC_PARAM_UNUSED(CanSduPtr);

    RetVal = BLPDUR_FALSE;

    LocalCanID = (uint32)(CanId & 0x1FFFFFFFU);

    /* If the group ID is already selected */
    if(m_ubGroupIdVal != BLPDUR_MULTIPLE_ID_NO_SEL)
    {
        /* For all the ID in the active group */
        for(Idx = 0U; (Idx < stMultipleIdConfig[m_ubGroupIdVal].NumOfIdInGroup) && (RetVal == BLPDUR_FALSE); Idx++)
        {
            /* return TRUE If the ID is found */
            if(LocalCanID == stMultipleIdConfig[m_ubGroupIdVal].GroupCanIdPtr[Idx])
            {
                RetVal = BLPDUR_TRUE;
            }
        }
    }

#if (BLPDUR_MULTIPLE_ID_TYPE == BLPDUR_MULTIPLE_ID_CAN_NOTIFICATION)
    /* If ID wasn't found in Diag list */
    if( RetVal == BLPDUR_FALSE)
    {
        /* Check if the ID is the one used to select the group ID */
        if(LocalCanID == BLPDUR_MULTIPLE_ID_CAN_SELECT_IDENT)
        {
            RetVal = BLPDUR_TRUE;
        }
    }
#endif

    DBG_BLPDUR_GROUPIDFRAMEFILTER_EXIT(RetVal);

    return RetVal;
}
#endif
/*-------------------------{end CanLPduReceiveCalloutFunction}-----------------------------*/

/*----------------------------{BlPduR_ConvertRxFuncPduId}------------------------------*/
#if (BLPDUR_MULTIPLE_ID_ENABLE ==  STD_ON)
void BlPduR_ConvertRxFuncPduId(PduIdType * pubRxPduId)
{
    u8 LoopIndex;
    u8 IdFound = FALSE;

    if (BLPDUR_FUNCTIONAL == stRxPdu[*pubRxPduId].AddressingType)
    {
        for (LoopIndex=0; ((LoopIndex < (BLPDUR_MAX_RX_PDU_NUM + BLPDUR_SHARED_RX_PDU_NUM)) && (IdFound == FALSE)); LoopIndex++)
        {
           if ( *pubRxPduId == stRxPdu[LoopIndex].RxPduId)
           {
                /* Check if Pdu belong to active group */
                if (stRxPdu[LoopIndex].GroupId == m_ubGroupIdVal)
                {
                    /* Id found, Convert id */
                    *pubRxPduId = LoopIndex;
                    /* exit loop */
                    IdFound = TRUE;
                }
           }
        }
    }
    else
    {
        /* no translation for physical pdu */
    }

}
#endif
/*-------------------------{end BlPduR_ConvertRxFuncPduId}-----------------------------*/
/*-------------------------{BlPduR_IsTcpConnectionReestablished}-------------------------------*/
#if (BLPDUR_NETWORK_ETH_SUPPORTED == STD_ON)
tBlPduRBoolean BlPduR_IsTcpConnectionReestablished(void)
{
    tBlPduRBoolean RetVal;
    PduIdType uwBlPduRTxPduId;
    PduIdType uwPduRTargetPduId;
    SoAd_SoConIdType SoConIdPtr;
    SoAd_SoConModeType ModePtr;

    DBG_BLPDUR_ISTCPCONNECTIONREESTABLISHED_ENTRY();

    RetVal = BLPDUR_FALSE;

#if (PROG_BLPDUR_SUPPORT_ENABLE == STD_ON)
    /* Retrieve connection information needed to send the response */
    BlPduR_RetrieveConnectionInfo();
#endif /*(PROG_BLPDUR_SUPPORT_ENABLE == STD_ON)*/

    /* Get the transmission Pdu Id of BlPduR */
    uwBlPduRTxPduId = stPduConnection[m_ubCurrentConnection].TxPdu;

    /* Get the corresponding TargetPduId of PduR (corresponding to PduId of SoAd) */
    uwPduRTargetPduId = PduR_ConfigLayout.PduR_RTabUpTpTx[uwBlPduRTxPduId].TargetPduId;

    /* Get the socket connection Id */
    if (SoAd_GetSoConId(uwPduRTargetPduId, &SoConIdPtr) == E_OK)
    {
        /* Check if the connection mode is retrieved successfully */
        if (SoAd_GetSoConMode(SoConIdPtr, &ModePtr) == E_OK)
        {
            if (ModePtr == SOAD_SOCON_ONLINE)
            {
                RetVal = BLPDUR_TRUE;
            }
        }
    }

   DBG_BLPDUR_ISTCPCONNECTIONREESTABLISHED_EXIT(RetVal);
   return RetVal;
}
#endif
/*-------------------------{end BlPduR_IsTcpConnectionReestablished}-------------------------------*/
/*----------------------------{BlPduR_IsNetworkSynchronized}---------------------------*/
u8 BlPduR_IsNetworkSynchronized (u8 * frCycle)
{
    u8 returnval;
#if (STD_ON==BLPDUR_NETWORK_FLEXRAY_SUPPORTED)
    u16 frMacroTick = 0U;
    if (FrIf_GetGlobalTime(FR_CCINDEX, frCycle, &frMacroTick) == E_OK)
    {
        /*Fr is Synchronized*/
        returnval=BLPDUR_E_OK;
    }
    else
    {
        /*Fr is not yet Synchronized*/
        returnval = BLPDUR_E_NOT_OK;
    }
#else
    *frCycle = FRCYCL_UNUSED;
    returnval = BLPDUR_E_OK;
#endif
    return returnval;
}
/*----------------------------{ end BlPduR_IsNetworkSynchronized}----------------------*/
/*----------------------------{BlPduR_AllSlots}----------------------------------------*/
void BlPduR_AllSlots(void)
{
#if (STD_ON==BLPDUR_NETWORK_FLEXRAY_SUPPORTED)
#if (STD_ON==BLPDUR_FRSM_ENABLEALLSLOTS)
    /* Request AllSlots mode */
    (void)FrSM_AllSlots(0U);
#endif
#endif
}
/*----------------------------{ end BlPduR_AllSlots}-----------------------------------*/
#if (BLPDUR_USE_STREAMING == STD_ON)
/*--------------------------{BlPduR_StreamingFrameReceived}----------------------------*/
void BlPduR_StreamingFrameReceived(u16 ulReceivedDataLength, u8* aubData)
{
    /* If the streaming is allowed forward the information to PROG */
    if(m_ubStreamingSetting == BLPDUR_STREAMING_ALLOWED)
    {
        PROG_StreamingFrameReceived(ulReceivedDataLength,aubData);
    }
}
/*----------------------------------{end BlPduR_StreamingFrameReceived}----------------*/

/*----------------------------------{BlPduR_SetStreamingStatus}------------------------*/
void BlPduR_SetStreamingStatus(u8 ubStreamingState)
{
    /* Allowed state values- BLPDUR_STREAMING_FORBIDDEN and BLPDUR_STREAMING_ALLOWED */
    m_ubStreamingSetting = ubStreamingState;
}
/*----------------------------------{end BlPduR_SetStreamingStatus}--------------------*/
#endif
