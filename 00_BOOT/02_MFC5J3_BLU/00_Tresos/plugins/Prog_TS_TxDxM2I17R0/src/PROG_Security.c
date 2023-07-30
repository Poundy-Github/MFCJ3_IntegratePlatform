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
/*%%  |   &&&&&   &&&&&             |  %%  Module version: 2.17.0 BL-3.X */
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
/* - Private Variables                                                           */
/*                                                                               */
#if (PROG_SECURE_BOOT_CHECKSUM_COMPUTATION == STD_ON)
NCS_PRI_VAR u8 m_ubBootAuthenticationStoredEvent;
#endif

#if ((PROG_SECURE_BOOT_CHECKSUM_COMPUTATION == STD_ON) || (PROG_SECURE_APPLI_CHECKSUM_COMPUTATION == STD_ON))
NCS_PRI_VAR u8 m_ubBootAuthenticationPending;
#if (PROG_CSM_HASH_USED == STD_ON)
/* Hash algorithm is used */
NCS_PRI_VAR u8 m_aubChecksum[PROG_DIGEST_LENGTH];
#else
/* Mac algorithm is used */
NCS_PRI_VAR u8 m_aubChecksum[PROG_SECURE_CHECKSUM_SIZE_IN_BYTES];
#endif
#endif

/*===============================================================================*/

/*-------------------------------------------------------------------------------*/
/* - Private Macros                                                              */

/*                                                                               */
/*===============================================================================*/

/*-------------------------------------------------------------------------------*/
/* - Private Function Prototypes                                                 */
/*                                                                               */

/*===============================================================================*/

/*=============================== IMPLEMENTATION ================================*/
/*                                                                               */

/*-------------------------------------------------------------------------------*/
/* - Public Functions                                                            */

#if ((PROG_SECURE_BOOT_CHECKSUM_COMPUTATION == STD_ON) || (PROG_SECURE_APPLI_CHECKSUM_COMPUTATION == STD_ON))
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
#if (PROG_IMPL_VARIANT == PROG_IMPL_11)
      PROG_CustomSetApplicationChecksum(&m_aubChecksum[0U], m_stCurrentSegment.ubLogicalBlockId);
      /* Write checksum of the corresponding Block identifier */
      m_ubBootAuthenticationPending = PROG_NO_AUTHENT;
      /* emit event to go to check memory finished state */
      PROG_HsmEmit (&PROG_HsmScPROG, PROG_HSM_PROG_EV_PROG_EVENT_FINISHED);
      PROG_EnableECCCheck();
#else
        /* Write checksum of the corresponding Block identifier */
        PROG_CustomSetApplicationChecksum(&m_aubChecksum[0U], m_stCurrentSegment.ubLogicalBlockId);
        m_ubBootAuthenticationPending = PROG_NO_AUTHENT;

        /* Send pending response to CheckMemory request */
        UDS_LongRequestEnd(PROG_CRC_COMP_RESPONSE_SIZE, m_stDiagMessageInfo.pubTxData, UDS_ACK);
#endif
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


#if (PROG_SECURE_APPLI_CHECKSUM_COMPUTATION == STD_ON)
/*------------------------{PROG_SecurityComputeAppChecksum}-----------------------*/
void PROG_SecurityComputeAppChecksum(void)
{
#if (PROG_IMPL_VARIANT == PROG_IMPL_11)
    u32 ulBlockAddr;
    u32 ulBlockLength;
#endif
    DBG_PROG_SECURITYCOMPUTEAPPCHECKSUM_ENTRY();

    /* Start Hash computation on configured Application range */
    m_ubBootAuthenticationPending = PROG_APP_AUTHENT;

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
      Prog_GetEssStartAddr(&ulBlockAddr);
      Prog_GetEssLength(&ulBlockLength);
    }
    else
    {
      /* get start address and length from ESS, subtract 1 because the ESS starts from zero and 1 was added to handle the ESS itself */
      (void)Prog_GetEssLogicalBlockStartAddr(m_stCurrentSegment.ubLogicalBlockId - 1, &ulBlockAddr);
      (void)Prog_GetEssLogicalBlockLength(m_stCurrentSegment.ubLogicalBlockId - 1, &ulBlockLength);
    }

    /* ECC is disabled here because VCC requires the verification of the erased area as well  */
    PROG_DisableECCCheck();

    (void)PROG_MacGenerateStart(PROG_CSM_SECURE_MAC_ID,
        (u8*)ulBlockAddr,
        ulBlockLength,
        &m_aubChecksum[0U]);
#else
    /* Deviation MISRAC2012-1 */
    (void)PROG_MacGenerateStart(PROG_CSM_SECURE_MAC_ID,
                                (u8*)stCfgBlockSecureBootInfo[m_stCurrentSegment.ubLogicalBlockId].ulStartAddressForSecureBoot,
                                stCfgBlockSecureBootInfo[m_stCurrentSegment.ubLogicalBlockId].ulLengthForSecureBoot,
                                &m_aubChecksum[0U]);
#endif
#endif

    DBG_PROG_SECURITYCOMPUTEAPPCHECKSUM_EXIT();
}
/*--------------------{end PROG_SecurityComputeAppChecksum}-----------------------*/
#endif
