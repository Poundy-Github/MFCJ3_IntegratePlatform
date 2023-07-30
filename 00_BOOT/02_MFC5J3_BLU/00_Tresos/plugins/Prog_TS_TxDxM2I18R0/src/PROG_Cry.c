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
/*%%   _____________________________   %%  \file PROG_Cry.c                      */
/*%%  |                             |  %%  \brief PROG cryptography feature      */
/*%%  |   &&&&&   &&&&&             |  %%  Module version: 2.18.0 BL-3.X */
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
 * MISRAC2012-1) Deviated Rule: 11.3 (required)
 * A cast shall not be performed between a pointer to object type and a pointer to a different
 * object type.
 *
 *   Reason:
 * The memory routines are optimized for dealing with aligned memory
 * and the correct alignment has been checked before converting
 * to different object types
 */
/* NOCOV List
 *
 * NOCOV-EMPTYDEFAULT:
 *   defensive code.
 *
 * Reason:
 * Defensive case which shall never happen.
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
#if (PROG_CSM_WRAPPER_43_USED==STD_OFF)
#include "Cry_LN.h"
#endif/*(PROG_CSM_WRAPPER_43_USED==STD_OFF)*/
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
NCS_PRI_VAR tProgStatus m_eCryptoStatus;
#if ((PROG_SINGLE_STEP_SIGNATURE_CHECK == STD_ON) || (PROG_HASH_CALCULATION == STD_ON))
NCS_PRI_VAR u8 const * m_pubCryptoData;
NCS_PRI_VAR u32 m_ulCryptoDataSize;
#endif /* ((PROG_SINGLE_STEP_SIGNATURE_CHECK == STD_ON) || (PROG_HASH_CALCULATION == STD_ON)) */

#if (PROG_SIGNATURE_CALCULATION == STD_ON)
NCS_PRI_VAR const u8* m_pubProgCryptoSignature;
#endif /*(PROG_SIGNATURE_CALCULATION == STD_ON)*/

#if ((PROG_SECURE_BOOT_CHECKSUM_COMPUTATION == STD_ON) || (PROG_SECURE_APPLI_CHECKSUM_COMPUTATION == STD_ON))
#if (PROG_HASH_CALCULATION == STD_ON)
NCS_PRI_VAR u8* m_pubHashValue;
#endif
#if (PROG_CSM_MAC_USED == STD_ON)
NCS_PRI_VAR u8* m_pubMacValue;
NCS_PRI_VAR Csm_SymKeyType m_stProgMacKey;
#endif
#endif

#if (PROG_HASH_CALCULATION == STD_ON)
NCS_PRI_VAR u32 m_ulDigestLength;
#endif

#if ((PROG_HASH_CALCULATION == STD_ON) || (PROG_CSM_MAC_USED == STD_ON))
NCS_PRI_VAR u16 m_uwCsmConfigId;
#endif

#if (PROG_SIGNATURE_CALCULATION == STD_ON)
NCS_PRI_VAR Csm_VerifyResultType m_ubProgVerifyResult;
#endif /*(PROG_SIGNATURE_CALCULATION == STD_ON)*/

NCS_PRI_VAR tProgCryState m_eCryptoState;

/*===============================================================================*/

/*-------------------------------------------------------------------------------*/
/* - Private Macros                                                              */

/*                                                                               */
/*===============================================================================*/

/*-------------------------------------------------------------------------------*/
/* - Private Function Prototypes                                                 */
/*                                                                               */
/** \brief Treat the Csm signature check notification **/
#if (PROG_SIGNATURE_CALCULATION == STD_ON)
NCS_PRI_FCT void PROG_CsmSignatureCheckNotification(void);
#endif /* (PROG_SIGNATURE_CALCULATION == STD_ON)*/

/** \brief Treat the Csm Hash notification **/
#if (PROG_HASH_CALCULATION == STD_ON)
NCS_PRI_FCT void PROG_CsmHashNotification(void);
#endif

/** \brief Treat the Csm Mac notification **/
#if (PROG_CSM_MAC_USED == STD_ON)
NCS_PRI_FCT void PROG_CsmMacGenerateNotification(void);
#endif
/*===============================================================================*/

/*=============================== IMPLEMENTATION ================================*/
/*                                                                               */

/*-------------------------------------------------------------------------------*/
/* - Public Functions                                                            */


/*---------------------------{PROG_VerifySignature}------------------------------*/
#if (PROG_SINGLE_STEP_SIGNATURE_CHECK == STD_ON)
tProgStatus PROG_VerifySignature(const Csm_AsymPublicKeyType* pstAsymPublicKey, u8* pubData, u32 ulDataSize, const u8* pubSignature)
{
    tProgStatus eStatus;

    DBG_PROG_VERIFYSIGNATURE_ENTRY(pstAsymPublicKey, pubData, ulDataSize, pubSignature);

    m_pubCryptoData = pubData;
    m_ulCryptoDataSize = ulDataSize;

    eStatus = PROG_VerifySignatureStart(pstAsymPublicKey, pubSignature)

    DBG_PROG_VERIFYSIGNATURE_EXIT(eStatus);
    return eStatus;
}
#endif /* PROG_SINGLE_STEP_SIGNATURE_CHECK == STD_ON */
/*--------------------------{End PROG_VerifySignature}---------------------------*/

#if (PROG_SIGNATURE_CALCULATION == STD_ON)
/*---------------------------{PROG_VerifySignatureStart}-----------------------------*/
tProgStatus PROG_VerifySignatureStart(const Csm_AsymPublicKeyType* pstAsymPublicKey, const u8* pubSignature)
{
    Csm_ReturnType eCsmStatus;
    tProgStatus eStatus;

    DBG_PROG_VERIFYSIGNATURESTART_ENTRY(pstAsymPublicKey, pubSignature);

    m_eCryptoState = PROG_SIGNATURE_CHECK_START;
    m_eCryptoStatus = PROG_E_BUSY;
    m_pubProgCryptoSignature = pubSignature;

    eCsmStatus = Csm_SignatureVerifyStart(PROG_CSM_SIG_VERIFY_ID, pstAsymPublicKey);

    if(eCsmStatus != CSM_E_OK)
    {
        m_eCryptoStatus = PROG_E_NOT_OK;
#if ((PROG_IMPL_VARIANT == PROG_IMPL_10) || (PROG_IMPL_VARIANT == PROG_IMPL_11))
        m_ubCheckMemoryStatus = PROG_INVALID_PUBLIC_KEY;
        /* Emit event PROG_EVENT_FAILED */
        PROG_HsmEmit (&PROG_HsmScPROG, PROG_HSM_PROG_EV_PROG_EVENT_FAILED);
#endif
    }

    /* Return the Crypto status */
    eStatus = m_eCryptoStatus;

    DBG_PROG_VERIFYSIGNATURESTART_EXIT(eStatus);
    return eStatus;
}
/*--------------------------{End PROG_VerifySignatureStart}--------------------------*/
#endif /*(PROG_SIGNATURE_CALCULATION == STD_ON)*/

#if (PROG_SIGNATURE_CALCULATION == STD_ON)
/*---------------------------{PROG_VerifySignatureUpdate}----------------------------*/
void PROG_VerifySignatureUpdate(u8 const * pubData, u32 ulDataSize)
{
    Csm_ReturnType eCsmStatus;

    DBG_PROG_VERIFYSIGNATUREUPDATE_ENTRY(pubData, ulDataSize);

    if(m_eCryptoStatus != PROG_E_NOT_OK)
    {
        m_eCryptoState = PROG_SIGNATURE_CHECK_UPDATE;

        eCsmStatus = Csm_SignatureVerifyUpdate(PROG_CSM_SIG_VERIFY_ID, pubData, ulDataSize);

        if(eCsmStatus == CSM_E_OK)
        {
            m_eCryptoStatus = PROG_E_BUSY;

        }
        else if (eCsmStatus == CSM_E_BUSY)
        {
            /* Wait for the treatment to finish */
            /* Nothing to do */
        }
        else
        {
            m_eCryptoStatus = PROG_E_NOT_OK;
        }
    }
    DBG_PROG_VERIFYSIGNATUREUPDATE_EXIT();
}
/*--------------------------{End PROG_VerifySignatureUpdate}-------------------------*/

/*---------------------------{PROG_VerifySignatureFinish}----------------------------*/
void PROG_VerifySignatureFinish(const u8* pubSignature)
{
    Csm_ReturnType eCsmStatus;

    DBG_PROG_VERIFYSIGNATUREFINISH_ENTRY(pubSignature);

    if(m_eCryptoStatus != PROG_E_NOT_OK)
    {
        if (pubSignature != NULL_PTR)
        {
            /* Update expected signature with the provided one */
            m_pubProgCryptoSignature = pubSignature;
        }

        m_eCryptoState = PROG_SIGNATURE_CHECK_FINISH;

        eCsmStatus = Csm_SignatureVerifyFinish(PROG_CSM_SIG_VERIFY_ID, m_pubProgCryptoSignature, PROG_SIGNATURE_LENGTH, &m_ubProgVerifyResult);

        if (CSM_E_OK == eCsmStatus)
        {
            m_eCryptoStatus = PROG_E_BUSY;
        }
        else if (eCsmStatus == CSM_E_BUSY)
        {
            /* Wait for the treatment to finish */
            /* Nothing to do */
        }
        else
        {
            m_eCryptoStatus = PROG_E_NOT_OK;
        }
    }
    DBG_PROG_VERIFYSIGNATUREFINISH_EXIT();
}
/*--------------------------{End PROG_VerifySignatureFinish}-------------------------*/
#endif /*(PROG_SIGNATURE_CALCULATION == STD_ON)*/

/*---------------------------{PROG_GetCryptoStatus}------------------------------*/
tProgStatus PROG_GetCryptoStatus(void)
{
    tProgStatus eStatus;

    DBG_PROG_GETCRYPTOSTATUS_ENTRY();
    eStatus = m_eCryptoStatus;
    DBG_PROG_GETCRYPTOSTATUS_EXIT(eStatus);
    return eStatus;
}
/*--------------------------{End PROG_GetCryptoStatus}---------------------------*/

/*---------------------------{PROG_GetCryptoState}------------------------------*/
tProgCryState PROG_GetCryptoState(void)
{
    tProgCryState eState;

    DBG_PROG_GETCRYPTOSTATE_ENTRY();
    eState = m_eCryptoState;
    DBG_PROG_GETCRYPTOSTATE_EXIT(eState);
    return eState;
}
/*--------------------------{End PROG_GetCryptoState}---------------------------*/

#if (PROG_HASH_CALCULATION == STD_ON)
/*---------------------------{PROG_ComputeHashStart}-----------------------------*/
tProgStatus PROG_ComputeHashStart(u16 uwCsmConfigId, u8 const * pubData,u32 ulDataSize, u8 * pubHashResult)
{
    Csm_ReturnType eCsmStatus;
    tProgStatus    eProgStatus;

#if ((PROG_SECURE_BOOT_CHECKSUM_COMPUTATION == STD_OFF) && (PROG_SECURE_APPLI_CHECKSUM_COMPUTATION == STD_OFF))
    OSC_PARAM_UNUSED(pubHashResult);
#endif

    DBG_PROG_COMPUTEHASHSTART_ENTRY(uwCsmConfigId,pubData,ulDataSize,pubHashResult);


    m_uwCsmConfigId = uwCsmConfigId;
    m_eCryptoState = PROG_HASH_START;
    m_eCryptoStatus = PROG_E_BUSY;

    if (NULL_PTR != pubData)
    {
        m_pubCryptoData = pubData;
        m_ulCryptoDataSize = ulDataSize;
#if ((PROG_SECURE_BOOT_CHECKSUM_COMPUTATION == STD_ON) || (PROG_SECURE_APPLI_CHECKSUM_COMPUTATION == STD_ON))
        m_pubHashValue = pubHashResult;
#endif
    }

    eCsmStatus = Csm_HashStart(m_uwCsmConfigId);

    if (CSM_E_OK != eCsmStatus)
    {
        m_eCryptoStatus = PROG_E_NOT_OK;
        eProgStatus     = PROG_E_NOT_OK;
    }
    else
    {
        eProgStatus     = PROG_E_OK;
    }

    DBG_PROG_COMPUTEHASHSTART_EXIT(eProgStatus);

    return eProgStatus;
}
/*--------------------------{End Prog_ComputeHashStart}--------------------------*/

/*---------------------------{PROG_ComputeHashUpdate}----------------------------*/
void PROG_ComputeHashUpdate(u8 const * pubData, u32 ulDataSize)
{
    Csm_ReturnType eCsmStatus;

    DBG_PROG_COMPUTEHASHUPDATE_ENTRY(pubData, ulDataSize);

    if(m_eCryptoStatus != PROG_E_NOT_OK)
    {
        m_eCryptoState = PROG_HASH_UPDATE;

        eCsmStatus = Csm_HashUpdate(m_uwCsmConfigId, pubData, ulDataSize);

        if(eCsmStatus == CSM_E_OK)
        {
            m_eCryptoStatus = PROG_E_BUSY;

        }
        else if (eCsmStatus == CSM_E_BUSY)
        {
            /* Wait for the treatment to finish */
            /* Nothing to do */
        }
        else
        {
            m_eCryptoStatus = PROG_E_NOT_OK;
        }
    }
    DBG_PROG_COMPUTEHASHUPDATE_EXIT();
}
/*--------------------------{End PROG_ComputeHashUpdate}-------------------------*/

/*---------------------------{PROG_ComputeHashFinish}----------------------------*/
void PROG_ComputeHashFinish(u8* pubHashValue)
{
    Csm_ReturnType eCsmStatus;

    DBG_PROG_COMPUTEHASHFINISH_ENTRY(pubHashValue);

    if((m_eCryptoStatus != PROG_E_NOT_OK) && (m_eCryptoState == PROG_HASH_END))
    {
        m_ulDigestLength = PROG_DIGEST_LENGTH;

        m_eCryptoState = PROG_HASH_FINISH;

        eCsmStatus = Csm_HashFinish(m_uwCsmConfigId, pubHashValue, &m_ulDigestLength, FALSE);

        if(eCsmStatus == CSM_E_OK)
        {
            m_eCryptoStatus = PROG_E_BUSY;

        }
        else if (eCsmStatus == CSM_E_BUSY)
        {
            /* Wait for the treatment to finish */
            /* Nothing to do */
        }
        else
        {
            m_eCryptoStatus = PROG_E_NOT_OK;
        }
    }
    DBG_PROG_COMPUTEHASHFINISH_EXIT();
}
/*--------------------------{End PROG_ComputeHashFinish}-------------------------*/
#endif /* PROG_HASH_CALCULATION == STD_ON */

#if (PROG_CSM_MAC_USED == STD_ON)
/*-----------------------{PROG_CsmMacGenerateNotification}------------------------------*/
NCS_PRI_FCT void PROG_CsmMacGenerateNotification(void)
{
#if ((PROG_SECURE_BOOT_CHECKSUM_COMPUTATION == STD_ON) || (PROG_SECURE_APPLI_CHECKSUM_COMPUTATION == STD_ON))
    tProgBoolean eProgBoolean;
    Csm_ReturnType eCsmStatus;
#endif
    switch (m_eCryptoState)
    {
        case PROG_MAC_GENERATE_START:
            m_eCryptoStatus = PROG_E_OK;
            m_eCryptoState = PROG_MAC_GENERATE_START_END;

#if ((PROG_SECURE_BOOT_CHECKSUM_COMPUTATION == STD_ON) || (PROG_SECURE_APPLI_CHECKSUM_COMPUTATION == STD_ON))
            /* Check if Mac computation is for Authentication. In positive case all crypto calculation triggering is performed */
            eProgBoolean = PROG_SecurityPendingOperation();

            if (PROG_TRUE == eProgBoolean)
            {
                m_eCryptoState = PROG_MAC_GENERATE_UPDATE;
                eCsmStatus = Csm_MacGenerateUpdate(m_uwCsmConfigId, m_pubCryptoData, m_ulCryptoDataSize);

                if (CSM_E_OK != eCsmStatus)
                {
                    m_eCryptoStatus = PROG_E_NOT_OK;
                    m_eCryptoState = PROG_IDLE;
                    /*push failed event*/
                    PROG_HsmEmit (&PROG_HsmScPROG, PROG_HSM_PROG_EV_PROG_EVENT_FAILED);
                }
            }
            else
            {
                /* Nothing to do */
            }
#endif
            break;


        case PROG_MAC_GENERATE_UPDATE:
            m_eCryptoStatus = PROG_E_OK;
            m_eCryptoState = PROG_MAC_GENERATE_UPDATE_END;

#if ((PROG_SECURE_BOOT_CHECKSUM_COMPUTATION == STD_ON) || (PROG_SECURE_APPLI_CHECKSUM_COMPUTATION == STD_ON))
            /* Check if Mac computation is for Authentication. In positive case all crypto calculation triggering is performed */
            eProgBoolean = PROG_SecurityPendingOperation();

            if (PROG_TRUE == eProgBoolean)
            {
                m_ulDigestLength = PROG_SECURE_CHECKSUM_SIZE_IN_BITS;
                m_eCryptoState = PROG_MAC_GENERATE_FINISH;
                eCsmStatus = Csm_MacGenerateFinish(m_uwCsmConfigId, m_pubMacValue, &m_ulDigestLength, FALSE);

                if (CSM_E_OK != eCsmStatus)
                {
                    m_eCryptoStatus = PROG_E_NOT_OK;
                    m_eCryptoState = PROG_IDLE;
                    /*push failed event*/
                    PROG_HsmEmit (&PROG_HsmScPROG, PROG_HSM_PROG_EV_PROG_EVENT_FAILED);
                }
            }
            else
#endif
            {
                /* Nothing to do */
            }
            break;



        case PROG_MAC_GENERATE_FINISH:
            m_eCryptoStatus = PROG_E_OK;
            m_eCryptoState = PROG_IDLE;

#if ((PROG_SECURE_BOOT_CHECKSUM_COMPUTATION == STD_ON) || (PROG_SECURE_APPLI_CHECKSUM_COMPUTATION == STD_ON))
            /* Check if hash computation is for Authentication. In positive case all crypto calculation triggering is performed */
            /* directly in not */
            eProgBoolean = PROG_SecurityPendingOperation();

            if (PROG_TRUE == eProgBoolean)
            {
                /* Notify security feature with hash value */
                PROG_SecurityChecksumNotification();
            }
            else
#endif
            {
                /* Emit event PROG_EVENT_CRYPTO_FINISH */
                PROG_HsmEmit (&PROG_HsmScPROG, PROG_HSM_PROG_EV_PROG_EVENT_CRYPTO_FINISH);
            }
            break;
/* CHECK: NOPARSE */
/* NOCOV-EMPTYDEFAULT */
        default:
            m_eCryptoStatus = PROG_E_NOT_OK;
            m_eCryptoState = PROG_IDLE;
            /*push failed event*/
            PROG_HsmEmit (&PROG_HsmScPROG, PROG_HSM_PROG_EV_PROG_EVENT_FAILED);
            break;
/* CHECK: PARSE */
    }
}
/*----------------------{End PROG_CsmMacGenerateNotification}---------------------------*/

/*------------------------------{PROG_GetMacKey}------------------------------*/
void PROG_GetMacKey(Csm_SymKeyType* pstMacKey)
{
    u8 ubIdx;
    const u8 * paubKeyData;
    u32 ulMacKeyLength;

    DBG_PROG_GETMACKEY_ENTRY(pstMacKey);

    PROG_CustomGetMacKey(&paubKeyData, &ulMacKeyLength);

    pstMacKey->length = ulMacKeyLength;

    for (ubIdx = 0U; ubIdx < (ulMacKeyLength/sizeof(u32)); ubIdx++)
    {
        pstMacKey->data[ubIdx]  = (u32)            paubKeyData[((u16)((u16)ulMacKeyLength - 1U) - ((u16)ubIdx*4U))];
        pstMacKey->data[ubIdx] |= (u32)((u32)((u32)paubKeyData[((u16)((u16)ulMacKeyLength - 2U) - ((u16)ubIdx*4U))] << 8U)  & 0x0000FF00U);
        pstMacKey->data[ubIdx] |= (u32)((u32)((u32)paubKeyData[((u16)((u16)ulMacKeyLength - 3U) - ((u16)ubIdx*4U))] << 16U) & 0x00FF0000U);
        pstMacKey->data[ubIdx] |= (u32)((u32)((u32)paubKeyData[((u16)((u16)ulMacKeyLength - 4U) - ((u16)ubIdx*4U))] << 24U) & 0xFF000000U);
    }

    DBG_PROG_GETMACKEY_EXIT();
}
/*----------------------{End PROG_GetMacKey}---------------------------*/

/*---------------------------{PROG_MacGenerateStart}-----------------------------*/
tProgStatus PROG_MacGenerateStart(u16 uwCsmConfigId, u8 const * pubData, u32 ulDataSize, u8 * pubMacResult)
{
    Csm_ReturnType eCsmStatus;
    tProgStatus    eProgStatus;

    DBG_PROG_MACGENERATESTART_ENTRY(uwCsmConfigId,pubData,ulDataSize,pubMacResult);

    m_uwCsmConfigId = uwCsmConfigId;
    m_eCryptoState = PROG_MAC_GENERATE_START;
    m_eCryptoStatus = PROG_E_BUSY;

    if (NULL_PTR != pubData)
    {
        m_pubCryptoData = pubData;
        m_ulCryptoDataSize = ulDataSize;
#if ((PROG_SECURE_BOOT_CHECKSUM_COMPUTATION == STD_ON) || (PROG_SECURE_APPLI_CHECKSUM_COMPUTATION == STD_ON))
        m_pubMacValue = pubMacResult;
#endif
    }

    PROG_GetMacKey(&m_stProgMacKey);

    eCsmStatus = Csm_MacGenerateStart(m_uwCsmConfigId, &m_stProgMacKey);

    if (CSM_E_OK != eCsmStatus)
    {
        m_eCryptoStatus = PROG_E_NOT_OK;
        eProgStatus     = PROG_E_NOT_OK;
    }
    else
    {
        eProgStatus     = PROG_E_OK;
    }

    DBG_PROG_MACGENERATESTART_EXIT(eProgStatus);

    return eProgStatus;
}
/*--------------------------{End PROG_MacGenerateStart}--------------------------*/
#endif

/*---------------------------{PROG_CsmNotification}----------------------------*/
Std_ReturnType PROG_CsmNotification(Csm_ReturnType eResult)
{
    Std_ReturnType RetVal = 0U;

    DBG_PROG_CSMNOTIFICATION_ENTRY(eResult);

#if ((PROG_SIGNATURE_CALCULATION == STD_ON) || (PROG_HASH_CALCULATION == STD_ON) || (PROG_CSM_MAC_USED == STD_ON))
    if (CSM_E_OK == eResult)
    {
        switch (m_eCryptoState)
        {
#if (PROG_SIGNATURE_CALCULATION == STD_ON)
            /* Management of the signature check */
            case PROG_SIGNATURE_CHECK_START:
            case PROG_SIGNATURE_CHECK_UPDATE:
            case PROG_SIGNATURE_CHECK_FINISH:
                PROG_CsmSignatureCheckNotification();
                break;
#endif /*#if (PROG_SIGNATURE_CALCULATION == STD_ON)*/
#if (PROG_HASH_CALCULATION == STD_ON)
            /* Management of the Hash */
            case PROG_HASH_START:
            case PROG_HASH_UPDATE:
            case PROG_HASH_FINISH :
                PROG_CsmHashNotification();
                break;
#endif /* PROG_HASH_CALCULATION == STD_ON  */
#if (PROG_CSM_MAC_USED == STD_ON)
            /* Management of the Hash */
            case PROG_MAC_GENERATE_START:
            case PROG_MAC_GENERATE_UPDATE:
            case PROG_MAC_GENERATE_FINISH :
                PROG_CsmMacGenerateNotification();
                break;
#endif /* PROG_CSM_MAC_USED == STD_ON  */
            /* Shall not happened go back in stable state happened */
            default:
                m_eCryptoStatus = PROG_E_NOT_OK;
                m_eCryptoState = PROG_IDLE;
#if (PROG_IMPL_VARIANT != PROG_IMPL_20)
                PROG_HsmEmit (&PROG_HsmScPROG, PROG_HSM_PROG_EV_PROG_EVENT_FAILED);
#endif
                break;
        }
    }
    else
#else
    OSC_PARAM_UNUSED(eResult);
#endif /*((PROG_SIGNATURE_CALCULATION == STD_ON) || (PROG_HASH_CALCULATION == STD_ON) || (PROG_CSM_MAC_USED == STD_ON))*/
    {
        m_eCryptoStatus = PROG_E_NOT_OK;
        m_eCryptoState = PROG_IDLE;
#if (PROG_IMPL_VARIANT != PROG_IMPL_20)
        PROG_HsmEmit (&PROG_HsmScPROG, PROG_HSM_PROG_EV_PROG_EVENT_FAILED);
#endif
    }

    DBG_PROG_CSMNOTIFICATION_EXIT(RetVal);

    return RetVal;
}
/*--------------------------{End PROG_CsmNotification}-------------------------*/

#if (PROG_SIGNATURE_CALCULATION == STD_ON)
/*-----------------------{PROG_CsmSignatureCheckNotification}--------------------*/
NCS_PRI_FCT void PROG_CsmSignatureCheckNotification(void)
{
#if PROG_SINGLE_STEP_SIGNATURE_CHECK == STD_ON
    Csm_ReturnType eCsmStatus;
#endif

    switch(m_eCryptoState)
    {
        case PROG_SIGNATURE_CHECK_START:
#if (PROG_SINGLE_STEP_SIGNATURE_CHECK == STD_OFF)
            m_eCryptoStatus = PROG_E_OK;
            m_eCryptoState = PROG_SIGNATURE_CHECK_START_END;
#if (PROG_IMPL_VARIANT == PROG_IMPL_40)
            /* Emit event PROG_EVENT_CRYPTO_FINISH */
            PROG_HsmEmit (&PROG_HsmScPROG, PROG_HSM_PROG_EV_PROG_EVENT_CRYPTO_NOTIFY);
#endif
#else
            m_eCryptoState = PROG_SIGNATURE_CHECK_UPDATE;

            eCsmStatus = Csm_SignatureVerifyUpdate(PROG_CSM_SIG_VERIFY_ID, m_pubCryptoData, m_ulCryptoDataSize);

            if (CSM_E_OK == eCsmStatus)
            {

            }
            else
            {
                m_eCryptoStatus = PROG_E_NOT_OK;
                m_eCryptoState = PROG_IDLE;
#if (PROG_IMPL_VARIANT != PROG_IMPL_20)
                PROG_HsmEmit (&PROG_HsmScPROG, PROG_HSM_PROG_EV_PROG_EVENT_FAILED);
#endif
            }
#endif
            break;

        case PROG_SIGNATURE_CHECK_UPDATE:
#if (PROG_SINGLE_STEP_SIGNATURE_CHECK == STD_OFF)
            m_eCryptoStatus = PROG_E_OK;
            m_eCryptoState = PROG_SIGNATURE_CHECK_UPDATE_END;

#if (PROG_IMPL_VARIANT == PROG_IMPL_40)
            /* Emit event PROG_EVENT_CRYPTO_FINISH */
            PROG_HsmEmit (&PROG_HsmScPROG, PROG_HSM_PROG_EV_PROG_EVENT_CRYPTO_NOTIFY);
#endif
#else
            m_eCryptoState = PROG_SIGNATURE_CHECK_FINISH;
            eCsmStatus = Csm_SignatureVerifyFinish(PROG_CSM_SIG_VERIFY_ID, m_pubProgCryptoSignature, PROG_SIGNATURE_LENGTH, &m_ubProgVerifyResult);

            if (CSM_E_OK != eCsmStatus)
            {
                m_eCryptoStatus = PROG_E_NOT_OK;
                m_eCryptoState = PROG_IDLE;
#if (PROG_IMPL_VARIANT != PROG_IMPL_20)
                PROG_HsmEmit (&PROG_HsmScPROG, PROG_HSM_PROG_EV_PROG_EVENT_FAILED);
#endif
            }
#endif
            break;

        case PROG_SIGNATURE_CHECK_FINISH:
            m_eCryptoStatus = PROG_E_OK;
            m_eCryptoState = PROG_IDLE;

            if (m_ubProgVerifyResult == CSM_E_VER_OK)
            {
                /* Emit event PROG_EVENT_CRYPTO_FINISH */
                PROG_HsmEmit (&PROG_HsmScPROG, PROG_HSM_PROG_EV_PROG_EVENT_CRYPTO_FINISH);
            }
            else
            {
                m_eCryptoStatus = PROG_E_NOT_OK;
#if (PROG_IMPL_VARIANT != PROG_IMPL_20)
                PROG_HsmEmit (&PROG_HsmScPROG, PROG_HSM_PROG_EV_PROG_EVENT_FAILED);
#endif
            }
            break;

/* CHECK: NOPARSE */
/* NOCOV-EMPTYDEFAULT */
        default:
            m_eCryptoStatus = PROG_E_NOT_OK;
            m_eCryptoState = PROG_IDLE;
#if (PROG_IMPL_VARIANT != PROG_IMPL_20)
                PROG_HsmEmit (&PROG_HsmScPROG, PROG_HSM_PROG_EV_PROG_EVENT_FAILED);
#endif
            break;
/* CHECK: PARSE */
    }
}
/*----------------------{End PROG_CsmSignatureCheckNotification}-----------------*/
#endif /*(PROG_SIGNATURE_CALCULATION == STD_ON)*/

#if (PROG_HASH_CALCULATION == STD_ON)
/*-----------------------{PROG_CsmHashNotification}------------------------------*/
NCS_PRI_FCT void PROG_CsmHashNotification(void)
{
#if ((PROG_SECURE_BOOT_CHECKSUM_COMPUTATION == STD_ON) || (PROG_SECURE_APPLI_CHECKSUM_COMPUTATION == STD_ON))
    Csm_ReturnType eCsmStatus;
#endif
    switch (m_eCryptoState)
    {
        case PROG_HASH_START:
            m_eCryptoStatus = PROG_E_OK;
            m_eCryptoState = PROG_HASH_START_END;

#if ((PROG_SECURE_BOOT_CHECKSUM_COMPUTATION == STD_ON) || (PROG_SECURE_APPLI_CHECKSUM_COMPUTATION == STD_ON))
            /* Check if hash computation is for Authentication. In positive case all crypto calculation triggering is performed */
            /* directly in not */
            if (PROG_TRUE == PROG_SecurityPendingOperation())
            {
                m_eCryptoState = PROG_HASH_UPDATE;
                eCsmStatus = Csm_HashUpdate(m_uwCsmConfigId, m_pubCryptoData, m_ulCryptoDataSize);

                if (CSM_E_OK != eCsmStatus)
                {
                    m_eCryptoStatus = PROG_E_NOT_OK;
                    m_eCryptoState = PROG_IDLE;
                    /*push failed event*/
                    PROG_HsmEmit (&PROG_HsmScPROG, PROG_HSM_PROG_EV_PROG_EVENT_FAILED);
                }
            }
            else
            {
                /* Nothing to do */
            }
#endif
            break;


        case PROG_HASH_UPDATE:
            m_eCryptoStatus = PROG_E_OK;
            m_eCryptoState = PROG_HASH_END;

#if ((PROG_SECURE_BOOT_CHECKSUM_COMPUTATION == STD_ON) || (PROG_SECURE_APPLI_CHECKSUM_COMPUTATION == STD_ON))
            /* Check if hash computation is for Authentication. In positive case all crypto calculation triggering is performed */
            /* directly in not*/
            if (PROG_TRUE == PROG_SecurityPendingOperation())
            {
                m_ulDigestLength = PROG_DIGEST_LENGTH;
                m_eCryptoState = PROG_HASH_FINISH;
                eCsmStatus = Csm_HashFinish(m_uwCsmConfigId, m_pubHashValue, &m_ulDigestLength, FALSE);

                if (CSM_E_OK != eCsmStatus)
                {
                    m_eCryptoStatus = PROG_E_NOT_OK;
                    m_eCryptoState = PROG_IDLE;
                    /*push failed event*/
                    PROG_HsmEmit (&PROG_HsmScPROG, PROG_HSM_PROG_EV_PROG_EVENT_FAILED);
                }
            }
            else
#endif
            {
#if (PROG_IMPL_VARIANT == PROG_IMPL_20)
                /* Emit event PROG_EVENT_CRYPTO_NOTIFY */
                PROG_HsmEmit (&PROG_HsmScPROG, PROG_HSM_PROG_EV_PROG_EVENT_CRYPTO_NOTIFY);
#endif
            }
            break;



        case PROG_HASH_FINISH:
            m_eCryptoStatus = PROG_E_OK;
            m_eCryptoState = PROG_IDLE;

#if ((PROG_SECURE_BOOT_CHECKSUM_COMPUTATION == STD_ON) || (PROG_SECURE_APPLI_CHECKSUM_COMPUTATION == STD_ON))
            /* Check if hash computation is for Authentication. In positive case all crypto calculation triggering is performed */
            /* directly in not */
            if (PROG_TRUE == PROG_SecurityPendingOperation())
            {
                /* Notify security feature with hash value */
                PROG_SecurityChecksumNotification();
            }
            else
#endif
            {
                /* Emit event PROG_EVENT_CRYPTO_FINISH */
                PROG_HsmEmit (&PROG_HsmScPROG, PROG_HSM_PROG_EV_PROG_EVENT_CRYPTO_FINISH);
            }
            break;
/* CHECK: NOPARSE */
/* NOCOV-EMPTYDEFAULT */
        default:
            m_eCryptoStatus = PROG_E_NOT_OK;
            m_eCryptoState = PROG_IDLE;
            /*push failed event*/
            PROG_HsmEmit (&PROG_HsmScPROG, PROG_HSM_PROG_EV_PROG_EVENT_FAILED);
            break;
/* CHECK: PARSE */
    }
}
/*----------------------{End PROG_CsmHashNotification}---------------------------*/
#endif /* PROG_HASH_CALCULATION == STD_ON */


#if (PROG_SIGNATURE_CALCULATION == STD_ON)
/*------------------------------{PROG_GetPublicKey}------------------------------*/
void PROG_GetPublicKey(Csm_AsymPublicKeyType* pstPublicKey)
{
    u8 ubIdx;
    const u8 * paubPublicModulus;
    u32 ulPublicExponent;

    PROG_CustomGetAsymPublicKey(&paubPublicModulus, &ulPublicExponent);

    pstPublicKey->length = 0U;

#if (PROG_CRY_EXPONENT_ENABLED == STD_ON)
    pstPublicKey->data[0] = 1U; /* Exponent size */
    pstPublicKey->data[1] = ulPublicExponent; /* Exponent */

    pstPublicKey->data[(PROG_KEY_LENGTH/sizeof(u32)) + 1] = (PROG_KEY_LENGTH/sizeof(u32)); /* Modulus size */

    for(ubIdx = 0U; /* Modulus */
        ubIdx < pstPublicKey->data[(PROG_KEY_LENGTH/sizeof(u32)) + 1];
        ubIdx++)
    {
        u8 ubLocIdx = ubIdx + ((u8)(PROG_KEY_LENGTH/sizeof(u32))) + 2U;
        pstPublicKey->data[ubLocIdx] = (u32) paubPublicModulus[((u16)(PROG_KEY_LENGTH - 1U) - ((u16)ubIdx*4U))];
        pstPublicKey->data[ubLocIdx] |= (u32)((u32)((u32)paubPublicModulus[((u16)(PROG_KEY_LENGTH - 2U) - ((u16)ubIdx*4U))] << 8U) & 0x0000FF00U);
        pstPublicKey->data[ubLocIdx] |= (u32)((u32)((u32)paubPublicModulus[((u16)(PROG_KEY_LENGTH - 3U) - ((u16)ubIdx*4U))] << 16U) & 0x00FF0000U);
        pstPublicKey->data[ubLocIdx] |= (u32)((u32)((u32)paubPublicModulus[((u16)(PROG_KEY_LENGTH - 4U) - ((u16)ubIdx*4U))] << 24U) & 0xFF000000U);
    }
#else
    pstPublicKey->data[0] = (PROG_KEY_LENGTH/sizeof(u32)); /* Modulus size */

    for(ubIdx = 0U; /* Modulus */
        ubIdx < pstPublicKey->data[0];
        ubIdx++)
    {
        pstPublicKey->data[ubIdx + 1U] = (u32) paubPublicModulus[((PROG_KEY_LENGTH - 1U) - (ubIdx*4U))];
        pstPublicKey->data[ubIdx + 1U] |= (u32)((u32)((u32)paubPublicModulus[((PROG_KEY_LENGTH - 2U) - (ubIdx*4U))] << 8U) & 0x0000FF00U);
        pstPublicKey->data[ubIdx + 1U] |= (u32)((u32)((u32)paubPublicModulus[((PROG_KEY_LENGTH - 3U) - (ubIdx*4U))] << 16U) & 0x00FF0000U);
        pstPublicKey->data[ubIdx + 1U] |= (u32)((u32)((u32)paubPublicModulus[((PROG_KEY_LENGTH - 4U) - (ubIdx*4U))] << 24U) & 0xFF000000U);
    }
#endif
}
/*----------------------------{End PROG_GetPublicKey}----------------------------*/
#endif /* (PROG_CRY_PRESENT == STD_ON) */
#endif /* (PROG_SIGNATURE_CALCULATION == STD_ON) */
