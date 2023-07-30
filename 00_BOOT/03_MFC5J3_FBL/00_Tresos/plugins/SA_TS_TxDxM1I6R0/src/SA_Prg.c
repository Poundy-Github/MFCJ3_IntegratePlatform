/*===============================================================================*/
/*                                                                               */
/*                                 Sa LAYER                                      */
/*                                                                               */
/* ----------------------------------------------------------------------------- */
/*                                                                               */
/*                               Security Access                                 */
/*                                                                               */
/*===============================================================================*/
/*%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%                                        */
/*%%   _____________________________   %%  \file SA_Prg.c                        */
/*%%  |                             |  %%                                        */
/*%%  |   &&&&&   &&&&&             |  %%  Module version: 1.6.3 BL-3.X */
/*%%  |   &       &    &            |  %%                                        */
/*%%  |   &&&&    &&&&&             |  %%                                        */
/*%%  |   &       &    &            |  %%                                        */
/*%%  |   &&&&&   &&&&&             |  %%                                        */
/*%%  |_____________________________|  %%                                        */
/*%%                                   %%                                        */
/*%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%                                        */
/*===============================================================================*/
/* Copyright 2010 by Elektrobit Automotive GmbH                                  */
/* All rights exclusively reserved for Elektrobit Automotive GmbH,               */
/* unless expressly agreed to otherwise.                                         */
/*===============================================================================*/

/*=============================== FILE INCLUSION ================================*/
/*                                                                               */

#include "EB_Prj.h"
#include "board.h"
#include "SA_Priv.h"
#include "SA_Cbk.h"
#include <SA_Trace.h>                        /* Dbg related macros for EB */
/*                                                                               */
/*===============================================================================*/

/* CHECK: RULE 503 OFF */


/*============================= PUBLIC DEFINITIONS ==============================*/
/*                                                                               */
/*-------------------------------------------------------------------------------*/
/* - Public Variables                                                            */

tSaStatus m_eSaStatus;
#if (SA_USE_CRYPTO == STD_ON)
tSaCsmState m_eSaCsmState;
u8* m_pubDataRandomNumber;
u8 m_aubLastRandomNumber[SA_RANDOM_NUMBER_LENGTH];
u8 m_aubCurrentRandomNumber[SA_RANDOM_NUMBER_LENGTH];
tSaBoolean m_ubGenRandReqReceived;
#if (SA_COMPARE_KEY_TYPE == SA_COMPARE_KEY_VERIFY_SIGNATURE)
Csm_AsymPublicKeyType m_stAsymPublicKey;
const u8* m_pubCryptoSignature;
u8 m_ubVerifSigUpdateReqReceived;
Csm_VerifyResultType m_ubVerifyResult;
#endif /*(SA_COMPARE_KEY_TYPE == SA_COMPARE_KEY_VERIFY_SIGNATURE)*/
#endif /*(SA_USE_CRYPTO == STD_ON)*/

#if (SA_CSM_WRAPPER_43_USED == STD_ON)
NCS_PRI_VAR uint32 m_aubCurrentRandomNumberlen;
#endif /*SA_CSM_WRAPPER_43_USED*/
#if (SA_STATIC_SEED_ENABLED == STD_ON)
u8 m_ubLastSeedWasUsed;
u8 m_aubLastSeed[SA_SEED_LEN];
#endif /*(SA_STATIC_SEED_ENABLED == STD_ON)*/

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
#if (SA_COMPARE_KEY_TYPE == SA_COMPARE_KEY_STANDARD)
NCS_PRI_VAR u8 m_aubCalculatedKey[SA_KEY_LEN];
#endif /*(SA_COMPARE_KEY_TYPE == SA_COMPARE_KEY_STANDARD)*/

#if (SA_ANTISCANNING_ENABLED == STD_ON)
NCS_PRI_VAR tAntiscanInfo m_stAntiscanInfo;
#endif /*(SA_ANTISCANNING_ENABLED == STD_ON)*/
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

/*----------------------------------{SA_Init}------------------------------------*/
void SA_Init (void)
{
#if (SA_COMPARE_KEY_TYPE == SA_COMPARE_KEY_STANDARD)
    u8 localIdx;
#endif /*(SA_COMPARE_KEY_TYPE == SA_COMPARE_KEY_STANDARD)*/
    DBG_SA_INIT_ENTRY();
    /*Init SA calculated key*/
#if (SA_COMPARE_KEY_TYPE == SA_COMPARE_KEY_STANDARD)
    for (localIdx = 0U; localIdx < SA_KEY_LEN; localIdx++)
    {
        m_aubCalculatedKey[localIdx] = 0U;
    }
#endif /*(SA_COMPARE_KEY_TYPE == SA_COMPARE_KEY_STANDARD)*/
#if ((SA_COMPRESSION_STATE == SA_COMPRESSION_ENABLED) && (PROG_CAL_PRESENT == STD_OFF))
    SA_DecompressInit();
#endif
#if (SA_SEED_TYPE == SA_SEED_CSM_RANDOM)
    SA_InitCrypto();
#endif
#if (SA_ANTISCANNING_ENABLED == STD_ON)
    /*Restore SA Anti-scanning retry counter*/
    m_stAntiscanInfo.ubRetryCnt = SA_CustomRestoreAsRetryCnt();
    if((SA_AS_MAX_NB_RETRY - 1U) < m_stAntiscanInfo.ubRetryCnt)
    {
        /*Rearm Antiscanning Lock Timer*/
        m_stAntiscanInfo.ulLockTimer = SA_AS_LOCK_TIMER;
        m_stAntiscanInfo.ubAsLocked = SA_TRUE;
    }
    else
    {
        m_stAntiscanInfo.ulLockTimer = 0U;
        m_stAntiscanInfo.ubAsLocked = SA_FALSE;
    }
#endif /*(SA_ANTISCANNING_ENABLED == STD_ON)*/
#if (SA_STATIC_SEED_ENABLED == STD_ON)
    m_ubLastSeedWasUsed = SA_TRUE;
#endif /*(SA_STATIC_SEED_ENABLED == STD_ON)*/
#if (SA_CSM_WRAPPER_43_USED == STD_ON)
    m_aubCurrentRandomNumberlen = SA_RANDOM_NUMBER_LENGTH;
#endif /*SA_CSM_WRAPPER_43_USED*/
    DBG_SA_INIT_EXIT();
}
/*----------------------------------{end SA_Init}----------------------------*/

/*----------------------------------{SA_Manage}--------------------------------*/
void SA_Manage (void)
{
    DBG_SA_MANAGE_ENTRY();
#if (SA_ANTISCANNING_ENABLED == STD_ON)

    /*Is the Anti-scanning locked*/
    if(0U < m_stAntiscanInfo.ulLockTimer)
    {
        /*Decrement Anti-scanning Lock Timer*/
        m_stAntiscanInfo.ulLockTimer--;
    }
    else
    {
        if(SA_TRUE == m_stAntiscanInfo.ubAsLocked)
        {
            /*Reset anti-scanning retry counter*/
            m_stAntiscanInfo.ubRetryCnt = 0U;
            m_stAntiscanInfo.ubAsLocked = SA_FALSE;
            /*Store the value of retry counter*/
            SA_CustomStoreAsRetryCnt( m_stAntiscanInfo.ubRetryCnt);
        }
        else
        {
            /*Do nothing*/
        }
    }
#endif /*(SA_ANTISCANNING_ENABLED == STD_ON)*/
    DBG_SA_MANAGE_EXIT();
}
/*----------------------------------{end SA_Manage}----------------------------*/

/*----------------------------------{SA_GetSeed}--------------------------------*/
tSaStatus SA_GetSeed(u8* aubSeed)
{
    tSaStatus eSaStatus;
#if (SA_SEED_TYPE != SA_SEED_CSM_RANDOM)
    u32 ulTempSeedData;
    /* Index of first copied byte of the random seed */
    u8 ubIdxRandom = 3U;
#endif /* if (SA_SEED_TYPE != SA_SEED_CSM_RANDOM) */

#if ((SA_SEED_TYPE != SA_SEED_CSM_RANDOM) || (SA_STATIC_SEED_ENABLED == STD_ON))
    /* Index of byte of the seed */
    u8 ubIdx;
#endif /*((SA_SEED_TYPE != SA_SEED_CSM_RANDOM) || (SA_STATIC_SEED_ENABLED == STD_ON))*/

    DBG_SA_GETSEED_ENTRY(aubSeed);

#if (SA_ANTISCANNING_ENABLED == STD_ON)
    if(0 == m_stAntiscanInfo.ulLockTimer)
    {
        /*Anti-scanning not locked*/
#endif /*(SA_ANTISCANNING_ENABLED == STD_ON)*/

#if (SA_STATIC_SEED_ENABLED == STD_ON)
        if(SA_TRUE == m_ubLastSeedWasUsed)
        {
            /* Generate new seed */
#endif /*(SA_STATIC_SEED_ENABLED == STD_ON)*/

#if (SA_SEED_TYPE != SA_SEED_CSM_RANDOM)
            ulTempSeedData = BoardGetRandom();

            /* For each byte of the seed */
            for (ubIdx = 0U; ubIdx < SA_SEED_LEN; ubIdx++)
            {
                /* Copy each byte of the random seed */
                aubSeed[ubIdx] = (u8)((u32)(ulTempSeedData >> (8U*ubIdxRandom)) & 0x000000FFU);
#if (SA_STATIC_SEED_ENABLED == STD_ON)
                /*store the generated seed*/
                m_aubLastSeed[ubIdx] = aubSeed[ubIdx];
#endif /*(SA_STATIC_SEED_ENABLED == STD_ON)*/

                /* If all of the four bytes of the random seed have been copied */
                if (0U == ubIdxRandom)
                {
                    /* Set the index to the first copied byte of the random seed */
                    ubIdxRandom = 3U;

                    /* Generate an other random seed */
                    ulTempSeedData = BoardGetRandom();
                }
                else
                {
                    /* Decrease the index of the copied byte of the random seed */
                    ubIdxRandom--;
                }
            }
#if (SA_STATIC_SEED_ENABLED == STD_ON)
            /*reset the seed usage flag*/
            m_ubLastSeedWasUsed = SA_FALSE;
#endif /*(SA_STATIC_SEED_ENABLED == STD_ON)*/

#if (SA_SECURITY_ALOGORITHM_TYPE == SA_SECURITY_ALOGORITHM_STANDARD)
            PROG_CalculateKey(&aubSeed[0], &m_aubCalculatedKey[0]);
#else
            /*Use custom algorithm to calculate key*/
            SA_CustomCalculateKey(&aubSeed[0], &m_aubCalculatedKey[0]);
#endif
            eSaStatus = SA_E_OK;
#endif /* if (SA_SEED_TYPE != SA_SEED_CSM_RANDOM) */

#if (SA_SEED_TYPE == SA_SEED_CSM_RANDOM)
            eSaStatus = SA_GenerateRandomNumber (aubSeed);
#endif /* if (SA_SEED_TYPE == SA_SEED_CSM_RANDOM) */
#if (SA_STATIC_SEED_ENABLED == STD_ON)
        }
        else
        {
            /*The last generated seed was not used, send it again*/
            for (ubIdx = 0U; ubIdx < SA_SEED_LEN; ubIdx++)
            {
                /* Copy each byte of the last seed */
                aubSeed[ubIdx] = m_aubLastSeed[ubIdx];
            }
            eSaStatus = SA_E_OK;
        }
#endif /*(SA_STATIC_SEED_ENABLED == STD_ON)*/

#if (SA_ANTISCANNING_ENABLED == STD_ON)
    }
    else
    {
        /*Anti-scanning locked*/
        eSaStatus = SA_E_NOK_AS_LOCKED;
    }
#endif /*(SA_ANTISCANNING_ENABLED == STD_ON)*/

    DBG_SA_GETSEED_EXIT(eSaStatus);
    return eSaStatus;
}
/*----------------------------------{end SA_GetSeed}----------------------------*/

/*----------------------------------{SA_CompareKey}-----------------------------*/
tSaStatus SA_CompareKey (const u8* aubReceivedKey)
{
    tSaStatus eSaStatus;
#if (SA_COMPARE_KEY_TYPE == SA_COMPARE_KEY_STANDARD)
    u8 ubIdx;
    tSaBoolean ubKeyMatch;
#endif /* if (SA_COMPARE_KEY_TYPE == SA_COMPARE_KEY_STANDARD) */
    DBG_SA_COMPAREKEY_ENTRY(aubReceivedKey);

#if (SA_STATIC_SEED_ENABLED == STD_ON)
    /*The generated seed was used*/
    m_ubLastSeedWasUsed = SA_TRUE;
#endif /*(SA_STATIC_SEED_ENABLED == STD_ON)*/

#if (SA_COMPARE_KEY_TYPE == SA_COMPARE_KEY_STANDARD)
    ubKeyMatch = SA_TRUE;
    eSaStatus = SA_E_NOT_OK;
    /*Check received key*/
    for (ubIdx = 0U; ubIdx < SA_KEY_LEN; ubIdx++)
    {
        if(m_aubCalculatedKey[ubIdx] != aubReceivedKey[ubIdx])
        {
            ubKeyMatch = SA_FALSE;
        }
    }
    eSaStatus = SA_Antiscanning(ubKeyMatch);
#endif /* if (SA_COMPARE_KEY_TYPE == SA_COMPARE_KEY_STANDARD) */

#if (SA_COMPARE_KEY_TYPE == SA_COMPARE_KEY_VERIFY_SIGNATURE)
    /* The received key is a signature, verify it */
    SA_VerifySignatureUpdate(aubReceivedKey);
    /*Update status global*/
    m_eSaStatus = SA_E_BUSY;
    /*Return status BUSY*/
    eSaStatus = SA_E_BUSY;
#endif /* if (SA_COMPARE_KEY_TYPE == SA_COMPARE_KEY_VERIFY_SIGNATURE) */

    DBG_SA_COMPAREKEY_EXIT(eSaStatus);
    return eSaStatus;
}
/*----------------------------------{end SA_CompareKey}-------------------------*/

#if (SA_USE_CRYPTO == STD_ON)
/*---------------------------{SA_InitCrypto}-----------------------------*/
void SA_InitCrypto(void)
{
#if (SA_SEED_TYPE == SA_SEED_CSM_RANDOM)
    Csm_ReturnType eCsmStatus;
#endif /*(SA_SEED_TYPE == SA_SEED_CSM_RANDOM)*/

    DBG_SA_INITCRYPTO_ENTRY();

#if (SA_SEED_TYPE == SA_SEED_CSM_RANDOM)
    /* Start random number generation*/
    eCsmStatus = Csm_RandomSeedStart(SA_CSM_RANDOM_SEED_ID);
    if(eCsmStatus == CSM_E_OK)
    {
        m_eSaCsmState = SA_SEED_GEN_STATE_START;
    }
    else
    {
        m_eSaCsmState = SA_SEED_GEN_STATE_INIT;
    }
#endif /*(SA_SEED_TYPE == SA_SEED_CSM_RANDOM)*/
#if (SA_COMPARE_KEY_TYPE == SA_COMPARE_KEY_VERIFY_SIGNATURE)
    SA_GetPublicKey(&m_stAsymPublicKey);
#endif /* if (SA_COMPARE_KEY_TYPE == SA_COMPARE_KEY_VERIFY_SIGNATURE) */

    DBG_SA_INITCRYPTO_EXIT();
}
/*------------------------{end SA_InitCrypto}--------------------------*/

/*---------------------------{SA_GenerateRandomNumber}-----------------------------*/
tSaStatus SA_GenerateRandomNumber(u8* aubRandomNumber)
{
    Csm_ReturnType eCsmStatus;

    DBG_SA_GENERATERANDOMNUMBER_ENTRY(aubRandomNumber);
    /* Memorize Random Number buffer address for usage in next step */
    m_pubDataRandomNumber = aubRandomNumber;
    if((m_eSaCsmState == SA_RANDOM_GEN_STATE_STANDBY)
#if (SA_COMPARE_KEY_TYPE == SA_COMPARE_KEY_VERIFY_SIGNATURE)
        || (m_eSaCsmState == SA_SIGNATURE_CHECK_START)
        || (m_eSaCsmState == SA_SIGNATURE_CHECK_UPDATE)
        || (m_eSaCsmState == SA_SIGNATURE_CHECK_STANDBY)
#endif /* if (SA_COMPARE_KEY_TYPE == SA_COMPARE_KEY_VERIFY_SIGNATURE) */
        )
    {
#if (SA_CSM_WRAPPER_43_USED == STD_ON)
        Demo_Csm_CancelJob();
        eCsmStatus = Csm_RandomGenerate(SA_CSM_RANDOM_GENERATE_ID, m_aubCurrentRandomNumber,(uint32 *) &m_aubCurrentRandomNumberlen);
#else
        eCsmStatus = Csm_RandomGenerate(SA_CSM_RANDOM_GENERATE_ID, m_aubCurrentRandomNumber, SA_RANDOM_NUMBER_LENGTH);
#endif /*SA_CSM_WRAPPER_43_USED*/
        if(eCsmStatus == CSM_E_OK)
        {
            m_eSaCsmState = SA_RANDOM_GEN_STATE_GENERATE;
            m_eSaStatus = SA_E_BUSY;
        }
        else
        {
            m_eSaCsmState = SA_CSM_STATE_INIT;
            m_eSaStatus = SA_E_NOT_OK;
        }
    }
    else
    {
        if(m_eSaCsmState == SA_CSM_STATE_INIT)
        {
            m_eSaCsmState = SA_SEED_GEN_STATE_INIT;
            m_eSaStatus = SA_E_NOT_OK;
        }
        else
        {
            m_ubGenRandReqReceived = SA_TRUE;
            m_eSaStatus = SA_E_BUSY;
        }
    }

    DBG_SA_GENERATERANDOMNUMBER_EXIT(m_eSaStatus);
    return m_eSaStatus;
}
/*------------------------{end SA_GenerateRandomNumber}--------------------------*/

/*---------------------------{SA_GenerateRandomCallback}-----------------------------*/
void SA_GenerateRandomCallback(Csm_ReturnType eCsmResult)
{
    Csm_ReturnType eCsmStatus;
    u32 ulLocalIdx;

    DBG_SA_GENERATERANDOMCALLBACK_ENTRY(eCsmResult);
    if(eCsmResult == CSM_E_OK)
    {
        switch(m_eSaCsmState)
        {
            case SA_SEED_GEN_STATE_START:
                /* Get the last seed of a random value for seed generation */
                SA_CustomGetLastRandomNumber(m_aubLastRandomNumber);
                eCsmStatus = Csm_RandomSeedUpdate(SA_CSM_RANDOM_SEED_ID, (const u8*) m_aubLastRandomNumber, (u32)SA_RANDOM_NUMBER_LENGTH);
                if(eCsmStatus == CSM_E_OK)
                {
                    m_eSaCsmState = SA_SEED_GEN_STATE_UPDATE;
                }
                else
                {
                    m_eSaCsmState = SA_CSM_STATE_INIT;
                    m_eSaStatus = SA_E_NOT_OK;
                }
                break;
            case SA_SEED_GEN_STATE_UPDATE:
                eCsmStatus = Csm_RandomSeedFinish(SA_CSM_RANDOM_SEED_ID);
                if(eCsmStatus == CSM_E_OK)
                {
                    m_eSaCsmState = SA_RANDOM_GEN_STATE_STANDBY;
                }
                else
                {
                    m_eSaCsmState = SA_CSM_STATE_INIT;
                    m_eSaStatus = SA_E_NOT_OK;
                }
                break;
            case SA_RANDOM_GEN_STATE_STANDBY:
                if(SA_TRUE == m_ubGenRandReqReceived)
                {
#if (SA_CSM_WRAPPER_43_USED == STD_ON)
                    Demo_Csm_CancelJob();
                    eCsmStatus = Csm_RandomGenerate(SA_CSM_RANDOM_GENERATE_ID, m_aubCurrentRandomNumber,(uint32 *) &m_aubCurrentRandomNumberlen);
#else
                    eCsmStatus = Csm_RandomGenerate(SA_CSM_RANDOM_GENERATE_ID, m_aubCurrentRandomNumber, SA_RANDOM_NUMBER_LENGTH);
#endif /*SA_CSM_WRAPPER_43_USED*/
                    if(eCsmStatus == CSM_E_OK)
                    {
                        m_eSaCsmState = SA_RANDOM_GEN_STATE_GENERATE;
                    }
                    else
                    {
                        m_eSaCsmState = SA_CSM_STATE_INIT;
                        m_eSaStatus = SA_E_NOT_OK;
                    }
                }
                break;
            case SA_RANDOM_GEN_STATE_GENERATE:
                /* The random number has been generated and can now be used */
                m_eSaCsmState = SA_RANDOM_GEN_STATE_STANDBY;
                /* Store the random value for further use */
                for(ulLocalIdx=0; ulLocalIdx<SA_RANDOM_NUMBER_LENGTH; ulLocalIdx++)
                {
                    m_pubDataRandomNumber[ulLocalIdx] = m_aubCurrentRandomNumber[ulLocalIdx];
#if (SA_STATIC_SEED_ENABLED == STD_ON)
                    /* Store the last generated Seed */
                    m_aubLastSeed[ulLocalIdx] = m_aubCurrentRandomNumber[ulLocalIdx];
#endif /*(SA_STATIC_SEED_ENABLED == STD_ON)*/
                }
#if (SA_STATIC_SEED_ENABLED == STD_ON)
                    /* Reset the Seed usage flag */
                    m_ubLastSeedWasUsed = SA_FALSE;
#endif /*(SA_STATIC_SEED_ENABLED == STD_ON)*/
                SA_CustomStoreRandomNumber(m_aubCurrentRandomNumber);

#if (SA_SEED_TYPE == SA_SEED_CSM_RANDOM)
                m_eSaStatus = SA_E_OK;
#endif /* if (SA_SEED_TYPE == SA_SEED_CSM_RANDOM) */
#if (SA_COMPARE_KEY_TYPE == SA_COMPARE_KEY_VERIFY_SIGNATURE)
                /* Start the signature verification algorithm */
                SA_VerifySignature(&m_stAsymPublicKey);
#endif /* if (SA_COMPARE_KEY_TYPE == SA_COMPARE_KEY_VERIFY_SIGNATURE) */
                break;
            default:
                /* Nothing to do */
                break;
        }
    }
    else
    {
        m_eSaCsmState = SA_SEED_GEN_STATE_INIT;
        m_eSaStatus = SA_E_NOT_OK;
    }

    DBG_SA_GENERATERANDOMCALLBACK_EXIT();
}
/*------------------------{end SA_GenerateRandomCallback}--------------------------*/

#if (SA_COMPARE_KEY_TYPE == SA_COMPARE_KEY_VERIFY_SIGNATURE)
/*---------------------------{SA_SignatureVerifAndHashCallback}-----------------------------*/
void SA_SignatureVerifAndHashCallback(Csm_ReturnType eCsmResult)
{
    Csm_ReturnType eCsmStatus;
    tSaBoolean ubKeyMatch;

    DBG_SA_SIGNATUREVERIFANDHASHCALLBACK_ENTRY(eCsmResult);
    if(eCsmResult == CSM_E_OK)
    {
        switch(m_eSaCsmState)
        {
            case SA_SIGNATURE_CHECK_START:
                eCsmStatus = Csm_SignatureVerifyUpdate(SA_CSM_SIG_VERIFY_ID, (const u8*) m_aubCurrentRandomNumber,SA_SEED_LEN);
                m_eSaCsmState = SA_SIGNATURE_CHECK_UPDATE;
                if(eCsmStatus != CSM_E_OK)
                {
                    /*return SA_E_NOK_INVALID_KEY or SA_E_NOK_AS_LOCKED depending on the previous SecurityAccess atempts.
                    The return value is calculated by calling the Anti-scanning API with a wrong result (SA_FALSE).*/
                    m_eSaStatus = SA_Antiscanning(SA_FALSE);
                    m_eSaCsmState = SA_CSM_STATE_INIT;
                }
                break;
            case SA_SIGNATURE_CHECK_UPDATE:
                if(SA_TRUE == m_ubVerifSigUpdateReqReceived)
                {
                    eCsmStatus = Csm_SignatureVerifyFinish(SA_CSM_SIG_VERIFY_ID, m_pubCryptoSignature, SA_SIGNATURE_LENGTH, &m_ubVerifyResult);
                    /* continue with the signature verification */
                    m_eSaCsmState = SA_SIGNATURE_CHECK_FINISH;
                    m_ubVerifSigUpdateReqReceived = FALSE;
                    if(eCsmStatus != CSM_E_OK)
                    {
                        /*return SA_E_NOK_INVALID_KEY or SA_E_NOK_AS_LOCKED depending on the previous SecurityAccess atempts.
                        The return value is calculated by calling the Anti-scanning API with a wrong result (SA_FALSE).*/
                        m_eSaStatus = SA_Antiscanning(SA_FALSE);
                        m_eSaCsmState = SA_CSM_STATE_INIT;
                    }
                }
                else
                {
                    m_eSaCsmState = SA_SIGNATURE_CHECK_STANDBY;
                }
                break;
            case SA_SIGNATURE_CHECK_FINISH:
                m_eSaCsmState = SA_RANDOM_GEN_STATE_STANDBY;
                if(m_ubVerifyResult == CSM_E_OK)
                {
                    ubKeyMatch = SA_TRUE;
                }
                else
                {
                    ubKeyMatch = SA_FALSE;
                }
                /* Check for SA_ANTISCANNING_ENABLED is done inside SA_Antiscanning()*/
                m_eSaStatus = SA_Antiscanning(ubKeyMatch);
                break;
            case SA_SIGNATURE_CHECK_STANDBY:
                break;
            default:
                /*return SA_E_NOK_INVALID_KEY or SA_E_NOK_AS_LOCKED depending on the previous SecurityAccess atempts.
                The return value is calculated by calling the Anti-scanning API with a wrong result (SA_FALSE).*/
                m_eSaStatus = SA_Antiscanning(SA_FALSE);
                m_eSaCsmState = SA_CSM_STATE_INIT;
                break;
        }
    }
    else
    {
        /*return SA_E_NOK_INVALID_KEY or SA_E_NOK_AS_LOCKED depending on the previous SecurityAccess atempts.
        The return value is calculated by calling the Anti-scanning API with a wrong result (SA_FALSE).*/
        m_eSaStatus = SA_Antiscanning(SA_FALSE);
        m_eSaCsmState = SA_RANDOM_GEN_STATE_STANDBY;
    }

    DBG_SA_SIGNATUREVERIFANDHASHCALLBACK_EXIT();
}
/*------------------------{end SA_SignatureVerifAndHashCallback}--------------------------*/

/*---------------------------{SA_VerifySignature}-----------------------------*/
void SA_VerifySignature(const Csm_AsymPublicKeyType* pstAsymPublicKey)
{
    Csm_ReturnType eCsmStatus;

    DBG_SA_VERIFYSIGNATURE_ENTRY(pstAsymPublicKey);
    eCsmStatus = Csm_SignatureVerifyStart(SA_CSM_SIG_VERIFY_ID, pstAsymPublicKey);
    if(eCsmStatus == CSM_E_OK)
    {
        m_eSaCsmState = SA_SIGNATURE_CHECK_START;
    }
    else
    {
        /*return SA_E_NOK_INVALID_KEY or SA_E_NOK_AS_LOCKED depending on the previous SecurityAccess atempts.
        The return value is calculated by calling the Anti-scanning API with a wrong result (SA_FALSE).*/
        m_eSaStatus = SA_Antiscanning(SA_FALSE);
        m_eSaCsmState = SA_RANDOM_GEN_STATE_STANDBY;
    }

    DBG_SA_VERIFYSIGNATURE_EXIT();
    }
/*------------------------{end SA_VerifySignature}--------------------------*/

/*---------------------------{SA_VerifySignatureUpdate}-----------------------------*/
void SA_VerifySignatureUpdate(const u8* pubSignature)
{
    DBG_SA_VERIFYSIGNATUREUPDATE_ENTRY(pubSignature);

    /* Update the pointer to the received signature */
    m_pubCryptoSignature = pubSignature;

    if(m_eSaCsmState == SA_SIGNATURE_CHECK_STANDBY)
    {
        (void) Csm_SignatureVerifyFinish(SA_CSM_SIG_VERIFY_ID, m_pubCryptoSignature, SA_SIGNATURE_LENGTH, &m_ubVerifyResult);
        /* Continue with the signature verification */
        m_eSaCsmState = SA_SIGNATURE_CHECK_FINISH;
    }
    else
    {
        m_ubVerifSigUpdateReqReceived = SA_TRUE;
    }

    DBG_SA_VERIFYSIGNATUREUPDATE_EXIT();
}
/*------------------------{end SA_VerifySignatureUpdate}--------------------------*/
#endif /*(SA_COMPARE_KEY_TYPE == SA_COMPARE_KEY_VERIFY_SIGNATURE)*/
/*---------------------------{SA_CsmNotification}-----------------------------*/
Std_ReturnType SA_CsmNotification(Csm_ReturnType eCsmResult)
{
    DBG_SA_CSMNOTIFICATION_ENTRY(eCsmResult);
    switch(m_eSaCsmState)
    {
    case SA_SEED_GEN_STATE_INIT:
    case SA_SEED_GEN_STATE_START:
    case SA_SEED_GEN_STATE_UPDATE:
    case SA_RANDOM_GEN_STATE_STANDBY:
    case SA_RANDOM_GEN_STATE_GENERATE:
        SA_GenerateRandomCallback(eCsmResult);
        break;
#if (SA_COMPARE_KEY_TYPE == SA_COMPARE_KEY_VERIFY_SIGNATURE)
    case SA_SIGNATURE_CHECK_START:
    case SA_SIGNATURE_CHECK_UPDATE:
    case SA_SIGNATURE_CHECK_STANDBY:
    case SA_SIGNATURE_CHECK_FINISH:
        SA_SignatureVerifAndHashCallback(eCsmResult);
        break;
#endif /*(SA_COMPARE_KEY_TYPE == SA_COMPARE_KEY_VERIFY_SIGNATURE)*/
    default:
        /* Nothing to do */
        break;
    }

    DBG_SA_CSMNOTIFICATION_EXIT(E_OK);
    return E_OK;
}
/*------------------------{end SA_CsmNotification}--------------------------*/
#endif /*(SA_USE_CRYPTO == STD_ON)*/

/*---------------------------{SA_GetStatus}-----------------------------*/
tSaStatus SA_GetStatus(void)
{
    DBG_SA_GETSTATUS_ENTRY();
    DBG_SA_GETSTATUS_EXIT(m_eSaStatus);
    return m_eSaStatus;
}
/*------------------------{end SA_GetStatus}--------------------------*/

/*---------------------------{SA_Antiscanning}-----------------------------*/
tSaStatus SA_Antiscanning(u8 ubKeyMatch)
{
    tSaStatus eSaStatus;

    DBG_SA_ANTISCANNING_ENTRY(ubKeyMatch);
    if(ubKeyMatch == SA_TRUE)
    {
#if (SA_ANTISCANNING_ENABLED == STD_ON)
        if(m_stAntiscanInfo.ubRetryCnt != 0)
        {
            /*Reset anti-scanning retry counter*/
            m_stAntiscanInfo.ubRetryCnt = 0;
            m_stAntiscanInfo.ubAsLocked = SA_FALSE;
            /*Store the value of retry counter*/
            SA_CustomStoreAsRetryCnt(m_stAntiscanInfo.ubRetryCnt);
        }
#endif /*(SA_ANTISCANNING_ENABLED == STD_ON)*/
        /*Return status OK*/
        eSaStatus = SA_E_OK;
    }
    else
    {
#if (SA_ANTISCANNING_ENABLED == STD_ON)
        if((SA_AS_MAX_NB_RETRY-1U) > m_stAntiscanInfo.ubRetryCnt)
        {
            /*Increment antiscanning retry counter*/
            m_stAntiscanInfo.ubRetryCnt++;
            /*Store the value of retry counter*/
            SA_CustomStoreAsRetryCnt(m_stAntiscanInfo.ubRetryCnt);
            /*Return INVALID KEY status*/
            eSaStatus = SA_E_NOK_INVALID_KEY;
        }
        else
        {
            /*Increment antiscanning retry counter*/
            m_stAntiscanInfo.ubRetryCnt++;
            /*Store the value of retry counter*/
            SA_CustomStoreAsRetryCnt(m_stAntiscanInfo.ubRetryCnt);

            /*Load Anti-scanning Lock Timer */
            m_stAntiscanInfo.ulLockTimer = SA_AS_LOCK_TIMER;
            m_stAntiscanInfo.ubAsLocked = SA_TRUE;
            /*Return antiscanning Locked status*/
            eSaStatus = SA_E_NOK_AS_LOCKED;
        }
#else /* (SA_ANTISCANNING_ENABLED == STD_OFF) */
        /*Return INVALID KEY status*/
        eSaStatus = SA_E_NOK_INVALID_KEY;
#endif /* (SA_ANTISCANNING_ENABLED == STD_ON) */
    }

    DBG_SA_ANTISCANNING_EXIT(eSaStatus);
    return eSaStatus;
}
/*------------------------{end SA_Antiscanning}--------------------------*/

#if (SA_COMPARE_KEY_TYPE == SA_COMPARE_KEY_VERIFY_SIGNATURE)
/*------------------------------{SA_GetPublicKey}------------------------------*/
void SA_GetPublicKey(Csm_AsymPublicKeyType* pstPublicKey)
{
    u8 ubIdx;
    const u8 * paubPublicModulus;
    u32 ulPublicExponent;

    SA_CustomGetAsymPublicKey(&paubPublicModulus, &ulPublicExponent);

    pstPublicKey->length = 0U;

#if(SA_CRY_EXPONENT_ENABLED == STD_ON)
    pstPublicKey->data[0] = 1U; /* Exponent size */
    pstPublicKey->data[1] = ulPublicExponent; /* Exponent */

    pstPublicKey->data[(SA_PUBLIC_KEY_LENGTH/sizeof(u32)) + 1] = (SA_PUBLIC_KEY_LENGTH/sizeof(u32)); /* Modulus size */

    for(ubIdx = 0U; /* Modulus */
        ubIdx < pstPublicKey->data[(SA_PUBLIC_KEY_LENGTH/sizeof(u32)) + 1];
        ubIdx++)
    {
        u8 ubLocIdx = ubIdx + ((u8)(SA_PUBLIC_KEY_LENGTH/sizeof(u32))) + 2U;
        pstPublicKey->data[ubLocIdx] = (u32) paubPublicModulus[((u16)(SA_PUBLIC_KEY_LENGTH - 1U) - ((u16)ubIdx*4U))];
        pstPublicKey->data[ubLocIdx] |= (u32)((u32)((u32)paubPublicModulus[((u16)(SA_PUBLIC_KEY_LENGTH - 2U) - ((u16)ubIdx*4U))] << 8U) & 0x0000FF00U);
        pstPublicKey->data[ubLocIdx] |= (u32)((u32)((u32)paubPublicModulus[((u16)(SA_PUBLIC_KEY_LENGTH - 3U) - ((u16)ubIdx*4U))] << 16U) & 0x00FF0000U);
        pstPublicKey->data[ubLocIdx] |= (u32)((u32)((u32)paubPublicModulus[((u16)(SA_PUBLIC_KEY_LENGTH - 4U) - ((u16)ubIdx*4U))] << 24U) & 0xFF000000U);
    }
#else /*(SA_CRY_EXPONENT_ENABLED == STD_OFF)*/

    pstPublicKey->data[0] = (SA_PUBLIC_KEY_LENGTH/sizeof(u32)); /* Modulus size */

    for(ubIdx = 0U; /* Modulus */
        ubIdx < pstPublicKey->data[0];
        ubIdx++)
    {
        pstPublicKey->data[ubIdx + 1U] = (u32) paubPublicModulus[((SA_PUBLIC_KEY_LENGTH - 1U) - (ubIdx*4U))];
        pstPublicKey->data[ubIdx + 1U] |= (u32)((u32)((u32)paubPublicModulus[((SA_PUBLIC_KEY_LENGTH - 2U) - (ubIdx*4U))] << 8U) & 0x0000FF00U);
        pstPublicKey->data[ubIdx + 1U] |= (u32)((u32)((u32)paubPublicModulus[((SA_PUBLIC_KEY_LENGTH - 3U) - (ubIdx*4U))] << 16U) & 0x00FF0000U);
        pstPublicKey->data[ubIdx + 1U] |= (u32)((u32)((u32)paubPublicModulus[((SA_PUBLIC_KEY_LENGTH - 4U) - (ubIdx*4U))] << 24U) & 0xFF000000U);
    }
#endif /*(SA_CRY_EXPONENT_ENABLED == STD_ON)*/

}
/*----------------------------{End SA_GetPublicKey}----------------------------*/
#endif /* if (SA_COMPARE_KEY_TYPE == SA_COMPARE_KEY_VERIFY_SIGNATURE) */
