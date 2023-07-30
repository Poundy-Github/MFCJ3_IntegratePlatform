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
/*%%   _____________________________   %%  \file PROG_Security.c                 */
/*%%  |                             |  %%  \brief PROG security feature          */
/*%%  |   &&&&&   &&&&&             |  %%  Module version: 2.47.0 BL3 */
/*%%  |   &       &    &            |  %%                                        */
/*%%  |   &&&&    &&&&&             |  %%                                        */
/*%%  |   &       &    &            |  %%                                        */
/*%%  |   &&&&&   &&&&&             |  %%                                        */
/*%%  |_____________________________|  %%                                        */
/*%%                                   %%                                        */
/*%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%                                        */
/*===============================================================================*/
/* Copyright 2015 by Elektrobit Automotive GmbH                                  */
/* All rights exclusively reserved for Elektrobit Automotive GmbH,               */
/* unless expressly agreed to otherwise.                                         */
/*===============================================================================*/
/*
 * MISRA-C:2012 Deviation List
 *
 * MISRAC2012-1) Deviated Rule: 11.4 (advisory)
 * A conversion should not be performed between a pointer to object
 * and an integer type.
 *
 *   Reason:
 * The memory routines are optimized for dealing with aligned memory
 * sections and need to check the correct alignment before the operation.
 *
 */
/*=============================== FILE INCLUSION ================================*/
/*                                                                               */

#include "EB_Prj.h"
#include "PROG_Priv.h"
#include "PROG_Hsm.h"
#include "PROG_HsmPROG.h"
#include "board.h"
#include <PROG_Trace.h>                        /* Dbg related macros for EB */

#if (PROG_CRY_PRESENT == STD_ON)
#include "PROG_Cry.h"
#endif

/*============================= PUBLIC DEFINITIONS ==============================*/
/*                                                                               */
/*-------------------------------------------------------------------------------*/
/* - Public Variables                                                            */
/*                                                                               */
/*-------------------------------------------------------------------------------*/
/* - Public Function Prototypes                                                  */

/*-------------------------------------------------------------------------------*/
/* - Public Callback Prototypes                                                  */

/*                                                                               */
/*===============================================================================*/

/*============================ PRIVATE DEFINITIONS ==============================*/

/*-------------------------------------------------------------------------------*/
/* - Private Macros                                                              */
/*                                                                               */
#define PROG_HSM_IDLE               0U
#define PROG_HSM_UPDATEINIT_BLOCK   1U
#define PROG_HSM_UPDATE_BLOCK       2U
#define PROG_HSM_UPDATE_FINISH      3U

#define PROG_HSM_CHECKSUM_SIZE      16U
/*-------------------------------------------------------------------------------*/
/* - Private Variables                                                           */
/*                                                                               */
#if (PROG_SECURE_BOOT_CHECKSUM_COMPUTATION == STD_ON)
NCS_PRI_VAR u8 m_ubBootAuthenticationStoredEvent;
#endif

#if ((PROG_CSM_MAC_USED == STD_ON) || (PROG_CSM_HASH_USED == STD_ON))
NCS_PRI_VAR u8 m_ubBootAuthenticationPending;
#if (PROG_CSM_HASH_USED == STD_ON)
/* Hash algorithm is used */
NCS_PRI_VAR u8 m_aubChecksum[PROG_DIGEST_LENGTH];
#elif (PROG_CSM_MAC_USED == STD_ON)
/* Mac algorithm is used */
NCS_PRI_VAR u8 m_aubChecksum[PROG_SECURE_CHECKSUM_SIZE_IN_BYTES];
#else
/* nothing */
#endif
#endif

#if (PROG_HSM_MAC_USED == STD_ON)
NCS_PRI_VAR u8 m_ubHsmCurrentStep;
#endif /* PROG_HSM_MAC_USED */

#if (PROG_IMPL_VARIANT == PROG_IMPL_11)
NCS_PRI_VAR u32 m_ulBlockAddr;
NCS_PRI_VAR u32 m_ulBlockLength;
#endif
/*===============================================================================*/

/*-------------------------------------------------------------------------------*/
/* - Private Function Prototypes                                                 */
/*                                                                               */
#if (PROG_HSM_MAC_USED == STD_ON)
void PROG_HsmMacGenerateStart(void);
#endif /* PROG_HSM_MAC_USED */

/*===============================================================================*/

/*=============================== IMPLEMENTATION ================================*/
/*                                                                               */

/*-------------------------------------------------------------------------------*/
/* - Public Functions                                                            */

#if ((PROG_CSM_MAC_USED == STD_ON) || (PROG_CSM_HASH_USED == STD_ON))
/*-----------------------------{PROG_SecurityInit}-------------------------------*/
void PROG_SecurityInit(void)
{
    DBG_PROG_SECURITYINIT_ENTRY();

    m_ubBootAuthenticationPending = PROG_NO_AUTHENT;

#if (PROG_SECURE_BOOT_CHECKSUM_COMPUTATION == STD_ON)
    m_ubBootAuthenticationStoredEvent = PROG_NO_EVENT;
#endif

    DBG_PROG_SECURITYINIT_EXIT();
}
/*---------------------------{end PROG_SecurityInit}-----------------------------*/

/*-------------------------{PROG_SecurityPendingOperation}-----------------------*/
tProgBoolean PROG_SecurityPendingOperation(void)
{
    tProgBoolean PendingOperation;
    DBG_PROG_SECURITYPENDINGOPERATION_ENTRY();

    if (PROG_NO_AUTHENT != m_ubBootAuthenticationPending)
    {
        PendingOperation = PROG_TRUE;
    }
    else
    {
        PendingOperation = PROG_FALSE;
    }
    DBG_PROG_SECURITYPENDINGOPERATION_EXIT(PendingOperation);
    return PendingOperation;
}
/*----------------------{end PROG_SecurityPendingOperation}----------------------*/
#endif

#if ((PROG_SECURE_BOOT_CHECKSUM_COMPUTATION == STD_ON) || (PROG_SECURE_APPLI_CHECKSUM_COMPUTATION == STD_ON))
/*------------------------{PROG_SecurityChecksumNotification}------------------------*/
void PROG_SecurityChecksumNotification(void)
{
    DBG_PROG_SECURITYCHECKSUMNOTIFICATION_ENTRY();

#if (PROG_SECURE_BOOT_CHECKSUM_COMPUTATION == STD_ON)
    if (PROG_BOOT_AUTHENT == m_ubBootAuthenticationPending)
    {
        /* Invalid checksum */
        PROG_CustomInvalidateBootloaderChecksum();

        /* Write checksum */
        PROG_CustomSetBootloaderChecksum(&m_aubChecksum[0U]);

        /* Valid checksum */
        PROG_CustomValidateBootloaderChecksum();

        /* Authentication is finished */
        m_ubBootAuthenticationPending = PROG_NO_AUTHENT;

        /* Check if there is a pending event */
        if (PROG_NO_EVENT != m_ubBootAuthenticationStoredEvent)
        {
            /* Post Event in state machine */
            PROG_HsmEmit(&PROG_HsmScPROG, m_ubBootAuthenticationStoredEvent);
        }
    }
    else if (PROG_APP_AUTHENT == m_ubBootAuthenticationPending)
#endif
    {
#if (PROG_SECURE_APPLI_CHECKSUM_COMPUTATION == STD_ON)
#if (PROG_BLU_ACTIVE == STD_ON)
        if (PROG_TRUE == m_ubBLUPattern)
        {
            PROG_HsmEmit(&PROG_HsmScPROG, PROG_HSM_PROG_EV_PROG_EVENT_BLU_PROGRESS);
        }
        else
#endif /*(PROG_BLU_ACTIVE == STD_ON)*/
        {
#if ((PROG_IMPL_VARIANT == PROG_IMPL_11) || (PROG_IMPL_VARIANT == PROG_IMPL_60) || (PROG_IMPL_VARIANT == PROG_IMPL_91))
            /* emit event to go to check memory finished state */
            PROG_HsmEmit (&PROG_HsmScPROG, PROG_HSM_PROG_EV_PROG_EVENT_FINISHED);
#elif (PROG_IMPL_VARIANT == PROG_IMPL_30)
#if (PROG_HSM_MAC_USED == STD_ON)
            PROG_HsmEmit(&PROG_HsmScPROG, PROG_HSM_PROG_EV_PROG_EVENT_FINISHED);
#endif
#elif ((PROG_IMPL_VARIANT == PROG_IMPL_4)|| (PROG_IMPL_VARIANT == PROG_IMPL_5))
            /* Response shall be sent from Validation Finish state*/
            PROG_HsmEmit(&PROG_HsmScPROG, PROG_HSM_PROG_EV_PROG_EVENT_CRYPTO_FINISH);
#endif /*(PROG_IMPL_VARIANT == PROG_IMPL_4) || (PROG_IMPL_VARIANT == PROG_IMPL_5)*/

#if ((PROG_CSM_MAC_USED == STD_ON) || (PROG_CSM_HASH_USED == STD_ON))
            m_ubBootAuthenticationPending = PROG_NO_AUTHENT;
#if (PROG_CHECKMEMORY_TYPE == PROG_CHECKMEMORY_BY_BLOCK)
            /* Write checksum of the corresponding Block identifier */
            PROG_CustomSetApplicationChecksum(&m_aubChecksum[0U], m_stCurrentSegment.ubLogicalBlockId);
#else
            /* Write checksum of the corresponding Segment identifier */
            PROG_CustomSetApplicationChecksum(&m_aubChecksum[0U], m_stCurrentSegment.ubSegmentId);
#endif /*(PROG_CHECKMEMORY_TYPE == PROG_CHECKMEMORY_BY_BLOCK)*/
#endif /*((PROG_CSM_MAC_USED == STD_ON) || (PROG_CSM_HASH_USED == STD_ON))*/

#if (PROG_IMPL_VARIANT == PROG_IMPL_11)
            PROG_EnableECCCheck();
#endif

#if ((PROG_IMPL_VARIANT == PROG_IMPL_31) || (PROG_IMPL_VARIANT == PROG_IMPL_50) || (PROG_IMPL_VARIANT == PROG_IMPL_60))
            /* Send pending response to CheckMemory request or checkprog dep. request */
            UDS_LongRequestEnd(PROG_CRC_COMP_RESPONSE_SIZE, m_stDiagMessageInfo.pubTxData, UDS_ACK);

#elif (PROG_IMPL_VARIANT == PROG_IMPL_30)
            /* send positive response only when SecureBoot operations need not be performed*/
            UDS_LongRequestEnd(PROG_CHK_PROG_DEP_POS_RESPONSE_SIZE, m_stDiagMessageInfo.pubTxData, UDS_ACK);
#if (PROG_REQ_PROGRAMMING_STATUS_ENABLE == STD_ON)
            /* Good Checksum/Signature, update ProgrammingStatus */
            PROG_SetProgrammingStatus(PROG_RC_CHECKSUM_VERIFY, PROG_TRUE);
#endif /*(PROG_REQ_PROGRAMMING_STATUS_ENABLE == STD_ON)*/

            /* Set validity flag */
            PROG_CustomSetAppValidity(PROG_RetrieveRequestData32(&m_stDiagMessageInfo.pubData[PROG_CPD_STARTADDR_OFFSET]), PROG_RetrieveRequestData32(&m_stDiagMessageInfo.pubData[PROG_CPD_ENDADDR_OFFSET]));
#endif /*(PROG_IMPL_VARIANT == PROG_IMPL_30)*/
        }
#endif /*PROG_SECURE_APPLI_CHECKSUM_COMPUTATION*/
    }
#if (PROG_SECURE_BOOT_CHECKSUM_COMPUTATION == STD_ON)
    else
    {
        /* error case */
    }
#endif

    DBG_PROG_SECURITYCHECKSUMNOTIFICATION_EXIT();
}
/*---------------------{end PROG_SecurityChecksumNotification}-----------------------*/
#endif

#if (PROG_SECURE_BOOT_CHECKSUM_COMPUTATION == STD_ON)
/*------------------------{PROG_SecurityStorePendingEvent}-----------------------*/
void PROG_SecurityStorePendingEvent(u8 EventToStore)
{
    DBG_PROG_SECURITYSTOREPENDINGEVENT_ENTRY(EventToStore);

    /* Store event to be emitted after security computation is finished */
    m_ubBootAuthenticationStoredEvent =  EventToStore;

    DBG_PROG_SECURITYSTOREPENDINGEVENT_EXIT();
}
/*--------------------{end PROG_SecurityStorePendingEvent}-----------------------*/

/*------------------------{PROG_SecurityComputeBootChecksum}-----------------------*/
void PROG_SecurityComputeBootChecksum(void)
{
    DBG_PROG_SECURITYCOMPUTEBOOTCHECKSUM_ENTRY();

    /* Start Hash computation on configured Bootloader range*/
    m_ubBootAuthenticationPending = PROG_BOOT_AUTHENT;

#if (PROG_CSM_HASH_USED == STD_ON)
    /* Deviation MISRAC2012-1 */
    (void)PROG_ComputeHashStart(PROG_CSM_SECURE_HASH_ID,
                                (u8*)PROG_AUTHENTICATED_BOOT_START_ADDR,
                                PROG_AUTHENTICATED_BOOT_START_LENGTH,
                                &m_aubChecksum[0U]);
#else
    /* Deviation MISRAC2012-1 */
    (void)PROG_MacGenerateStart(PROG_CSM_SECURE_MAC_ID,
                                (u8*)PROG_AUTHENTICATED_BOOT_START_ADDR,
                                PROG_AUTHENTICATED_BOOT_START_LENGTH,
                                &m_aubChecksum[0U]);
#endif

    DBG_PROG_SECURITYCOMPUTEBOOTCHECKSUM_EXIT();
}
/*--------------------{end PROG_SecurityComputeBootChecksum}-----------------------*/
#endif

#if ((PROG_AUTHENTICATED_BOOT_ENABLE == STD_ON) && (PROG_BOOT_VERIFICATION == STD_ON))
/*-----------------------{PROG_GetComputedBootloaderChecksum}----------------------*/
tProgStatus PROG_GetComputedBootloaderChecksum(u8 * pubComputedChecksum)
{
    tProgStatus eProgStatus;
    tProgBoolean eValidBootloaderChecksum;

    DBG_PROG_GETCOMPUTEDBOOTLOADERCHECKSUM_ENTRY(pubComputedChecksum);

    eValidBootloaderChecksum = PROG_CustomIsValidBootloaderChecksum();

    /* Verify checksum validity */
    if (PROG_TRUE == eValidBootloaderChecksum)
    {
        /* Get checksum */
        PROG_CustomGetComputedBootloaderChecksum(pubComputedChecksum);
        eProgStatus = PROG_E_OK;
    }
    else
    {
        /* Checksum is invalid and shall be computed again */
        eProgStatus = PROG_E_NOT_OK;
    }
    DBG_PROG_GETCOMPUTEDBOOTLOADERCHECKSUM_EXIT(eProgStatus);
    return eProgStatus;
}
/*-----------------------{end PROG_GetComputedBootloaderChecksum}-------------------*/
#endif


/*------------------------{PROG_SecurityComputeAppChecksum}-----------------------*/
void PROG_SecurityComputeAppChecksum(void)
{
#if (PROG_SECURE_APPLI_CHECKSUM_COMPUTATION == STD_ON)
    DBG_PROG_SECURITYCOMPUTEAPPCHECKSUM_ENTRY();

#if ((PROG_CSM_MAC_USED == STD_ON) || (PROG_CSM_HASH_USED == STD_ON))
    /* Start Hash computation on configured Application range */
    m_ubBootAuthenticationPending = PROG_APP_AUTHENT;
#endif

#if (PROG_CSM_HASH_USED == STD_ON)
    /* Deviation MISRAC2012-1 */
    (void)PROG_ComputeHashStart(PROG_CSM_SECURE_HASH_ID,
                                (u8*)stCfgBlockSecureBootInfo[m_stCurrentSegment.ubLogicalBlockId].ulStartAddressForSecureBoot,
                                stCfgBlockSecureBootInfo[m_stCurrentSegment.ubLogicalBlockId].ulLengthForSecureBoot,
                                &m_aubChecksum[0U]);
#else
#if (PROG_IMPL_VARIANT == PROG_IMPL_11)
    /* In case of ESS, use start and length from the configuration of the first configured segment */
    if(0 == m_stCurrentSegment.ubLogicalBlockId)
    {
      Prog_GetEssStartAddr(&m_ulBlockAddr);
      Prog_GetEssLength(&m_ulBlockLength);
    }
    else
    {
      /* get start address and length from ESS, subtract 1 because the ESS starts from zero and 1 was added to handle the ESS itself */
      (void)Prog_GetEssLogicalBlockStartAddr(m_stCurrentSegment.ubLogicalBlockId - 1, &m_ulBlockAddr);
      (void)Prog_GetEssLogicalBlockLength(m_stCurrentSegment.ubLogicalBlockId - 1, &m_ulBlockLength);
    }

    /* ECC is disabled here because VCC requires the verification of the erased area as well  */
    PROG_DisableECCCheck();
    /* Deviation MISRAC2012-1 */
#if (PROG_HSM_MAC_USED == STD_ON)
    PROG_HsmMacGenerateStart();
#else
    (void)PROG_MacGenerateStart(PROG_CSM_SECURE_MAC_ID,
        (u8*)m_ulBlockAddr,
        m_ulBlockLength,
        &m_aubChecksum[0U]);
#endif /* PROG_HSM_MAC_USED */
#else
#if (PROG_CSM_MAC_USED == STD_ON)
    /* Deviation MISRAC2012-1 */
#if (PROG_CHECKMEMORY_TYPE == PROG_CHECKMEMORY_BY_BLOCK)
    (void)PROG_MacGenerateStart(PROG_CSM_SECURE_MAC_ID,
                                (u8*)stCfgBlockSecureBootInfo[m_stCurrentSegment.ubLogicalBlockId].ulStartAddressForSecureBoot,
                                stCfgBlockSecureBootInfo[m_stCurrentSegment.ubLogicalBlockId].ulLengthForSecureBoot,
                                &m_aubChecksum[0U]);
#else
    (void)PROG_MacGenerateStart(PROG_CSM_SECURE_MAC_ID,
                                (u8*)stCfgBlockSecureBootInfo[m_stCurrentSegment.ubSegmentId].ulStartAddressForSecureBoot,
                                stCfgBlockSecureBootInfo[m_stCurrentSegment.ubSegmentId].ulLengthForSecureBoot,
                                &m_aubChecksum[0U]);
#endif /*(PROG_CHECKMEMORY_TYPE == PROG_CHECKMEMORY_BY_BLOCK)*/
#endif /*(PROG_CSM_MAC_USED == STD_ON)*/
#if (PROG_HSM_MAC_USED == STD_ON)
    PROG_HsmMacGenerateStart();
#endif /* PROG_HSM_MAC_USED */
#endif
#endif

    DBG_PROG_SECURITYCOMPUTEAPPCHECKSUM_EXIT();
#else
#if ((PROG_IMPL_VARIANT == PROG_IMPL_4) || (PROG_IMPL_VARIANT == PROG_IMPL_5))
    /*Secure Application Checksum Computation feat. is disabled or not supported*/
    PROG_HsmEmit(&PROG_HsmScPROG, PROG_HSM_PROG_EV_PROG_EVENT_CRYPTO_FINISH);
#endif /*(PROG_IMPL_VARIANT != PROG_IMPL_4)|| (PROG_IMPL_VARIANT == PROG_IMPL_5)*/
#if ((PROG_IMPL_VARIANT == PROG_IMPL_90) || (PROG_IMPL_VARIANT == PROG_IMPL_91))
PROG_HsmEmit(&PROG_HsmScPROG, PROG_HSM_PROG_EV_PROG_EVENT_FINISHED);
#endif /*(PROG_IMPL_VARIANT != PROG_IMPL_90)|| (PROG_IMPL_VARIANT == PROG_IMPL_91)*/
#endif /*(PROG_SECURE_APPLI_CHECKSUM_COMPUTATION == STD_ON)*/
}
/*--------------------{end PROG_SecurityComputeAppChecksum}-----------------------*/


#if (PROG_HSM_MAC_USED == STD_ON)
void PROG_HsmMacGenerateStart(void)
{
    /* try to start HSM actions */
    m_ubHsmCurrentStep = PROG_HSM_UPDATEINIT_BLOCK;
}
#endif /* PROG_HSM_MAC_USED */

void PROG_HsmManage(void)
{
#if ((PROG_HSM_MAC_USED == STD_ON) && (PROG_SECURE_APPLI_CHECKSUM_COMPUTATION == STD_ON))
    tProgStatus ubLocJobResult;
    u8         *pubLocMemoryAddress;
    u32         ulLocMemorySize;


    ubLocJobResult = PROG_E_BUSY;

    switch (m_ubHsmCurrentStep)
    {
        case PROG_HSM_UPDATEINIT_BLOCK:
#if (PROG_IMPL_VARIANT == PROG_IMPL_11)
            /* Deviation MISRAC2012-1 */
            pubLocMemoryAddress = (u8 *)m_ulBlockAddr;
            ulLocMemorySize = m_ulBlockLength;
            ubLocJobResult = PROG_CustomHsmUpdateInitBlock(m_stCurrentSegment.ubLogicalBlockId,
                                                       pubLocMemoryAddress,
                                                       ulLocMemorySize);
#elif (PROG_CHECKMEMORY_TYPE == PROG_CHECKMEMORY_BY_BLOCK)
            /* Deviation MISRAC2012-1 */
            pubLocMemoryAddress = (u8 *)(stCfgBlockSecureBootInfo[m_stCurrentSegment.ubLogicalBlockId].ulStartAddressForSecureBoot);
            ulLocMemorySize = stCfgBlockSecureBootInfo[m_stCurrentSegment.ubLogicalBlockId].ulLengthForSecureBoot;
            ubLocJobResult = PROG_CustomHsmUpdateInitBlock(m_stCurrentSegment.ubLogicalBlockId,
                                                       pubLocMemoryAddress,
                                                       ulLocMemorySize);
#else
            /* Deviation MISRAC2012-1 */
            pubLocMemoryAddress = (u8 *)(stCfgBlockSecureBootInfo[m_stCurrentSegment.ubSegmentId].ulStartAddressForSecureBoot);
            ulLocMemorySize = stCfgBlockSecureBootInfo[m_stCurrentSegment.ubSegmentId].ulLengthForSecureBoot;
            ubLocJobResult = PROG_CustomHsmUpdateInitBlock(m_stCurrentSegment.ubSegmentId,
                                                       pubLocMemoryAddress,
                                                       ulLocMemorySize);
#endif
            break;

        case PROG_HSM_UPDATE_BLOCK:
#if (PROG_IMPL_VARIANT == PROG_IMPL_11)
            /* Deviation MISRAC2012-1 */
            pubLocMemoryAddress = (u8 *)m_ulBlockAddr;
            ulLocMemorySize = m_ulBlockLength;
            ubLocJobResult = PROG_CustomHsmUpdateBlock(m_stCurrentSegment.ubLogicalBlockId,
                                                       pubLocMemoryAddress,
                                                       ulLocMemorySize);
#elif (PROG_CHECKMEMORY_TYPE == PROG_CHECKMEMORY_BY_BLOCK)
            /* Deviation MISRAC2012-1 */
            pubLocMemoryAddress = (u8 *)(stCfgBlockSecureBootInfo[m_stCurrentSegment.ubLogicalBlockId].ulStartAddressForSecureBoot);
            ulLocMemorySize = stCfgBlockSecureBootInfo[m_stCurrentSegment.ubLogicalBlockId].ulLengthForSecureBoot;
            ubLocJobResult = PROG_CustomHsmUpdateBlock(m_stCurrentSegment.ubLogicalBlockId,
                                                       pubLocMemoryAddress,
                                                       ulLocMemorySize);
#else
            /* Deviation MISRAC2012-1 */
            pubLocMemoryAddress = (u8 *)(stCfgBlockSecureBootInfo[m_stCurrentSegment.ubSegmentId].ulStartAddressForSecureBoot);
            ulLocMemorySize = stCfgBlockSecureBootInfo[m_stCurrentSegment.ubSegmentId].ulLengthForSecureBoot;
            ubLocJobResult = PROG_CustomHsmUpdateBlock(m_stCurrentSegment.ubSegmentId,
                                                       pubLocMemoryAddress,
                                                       ulLocMemorySize);
#endif
            break;

        case PROG_HSM_UPDATE_FINISH:
            /* update is OK */
            PROG_CustomHsmUpdateFinish(PROG_E_OK);
            PROG_SecurityChecksumNotification();
            m_ubHsmCurrentStep = PROG_HSM_IDLE;
            break;

        case PROG_HSM_IDLE:
        default:
            /* do nothing */
            break;
    }

    if (ubLocJobResult == PROG_E_OK)
    {
        /* go to the next step */
        m_ubHsmCurrentStep++;
    }
    else if (ubLocJobResult == PROG_E_NOT_OK)
    {
        m_ubHsmCurrentStep = PROG_HSM_IDLE;
        /* report failure */
        PROG_CustomHsmUpdateFinish(PROG_E_NOT_OK);
        PROG_HsmEmit(&PROG_HsmScPROG, PROG_HSM_PROG_EV_PROG_EVENT_FAILED);
    }
    else
    {
        /* do nothing */
    }
#endif /* ((PROG_HSM_MAC_USED == STD_ON) && (PROG_SECURE_APPLI_CHECKSUM_COMPUTATION == STD_ON)) */
}

/*-------------------------------------------------------------------------------*/
