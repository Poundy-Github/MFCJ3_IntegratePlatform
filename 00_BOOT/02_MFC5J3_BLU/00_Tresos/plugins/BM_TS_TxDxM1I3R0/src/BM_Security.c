/*===============================================================================*/
/*                                                                               */
/*                               BOOT Layers                                     */
/*                                                                               */
/* ----------------------------------------------------------------------------- */
/*                                                                               */
/*                               BM layer                                        */
/*                                                                               */
/*===============================================================================*/
/*%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%                                        */
/*%%   _____________________________   %%  \file BM_Security.c                   */
/*%%  |                             |  %%  \brief BM layer include plugin file   */
/*%%  |   &&&&&   &&&&&             |  %%  Module version: 1.3.0 BL-3.X                */
/*%%  |   &       &    &            |  %%  Variant: OsekCore                  */
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
/*-------------------------------------------------------------------------------*/
/* - Header Files: Variable Types                                                */


/*-------------------------------------------------------------------------------*/
/* - Header Files: BM                                                            */

#include "EB_Prj.h"
#include "BM_Priv.h"
#include <BM_Trace.h>

#if ((BM_AUTHENTICATED_BOOT_ENABLE == STD_ON) || (BM_SECURE_BOOT_ENABLE == STD_ON))
#if (BM_CSM_PRESENT == STD_ON)
#include "Csm.h"
#endif
#endif

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
/* - Private Variables                                                           */

#if ((BM_AUTHENTICATED_BOOT_ENABLE == STD_ON) || (BM_SECURE_BOOT_ENABLE == STD_ON))
#if (BM_CSM_HASH_USED == STD_ON)
NCS_PRI_VAR u32 m_ulDigestLength;
#elif (BM_CSM_MAC_USED == STD_ON)
/* Key used for the MAC algorithm */
NCS_PRI_VAR Csm_SymKeyType m_stBMMacKey;
#endif
NCS_PRI_VAR u8  m_ubCsmFinished;
NCS_PRI_VAR Csm_ReturnType m_ubCsmResult;
#endif

/*-------------------------------------------------------------------------------*/
/* - Private Macros                                                              */

/*-------------------------------------------------------------------------------*/
/* - Private Function Prototypes                                                 */
#if (BM_CSM_MAC_USED == STD_ON)
NCS_PRI_VAR void BM_GetMacKey(Csm_SymKeyType* pstMacKey);
#endif
/*                                                                               */
/*===============================================================================*/

/*=============================== IMPLEMENTATION ================================*/
/*                                                                               */
/*-------------------------------------------------------------------------------*/
/* - PrivateFunctions                                                            */
/*------------------------------{BM_GetMacKey}------------------------------*/
#if (BM_CSM_MAC_USED == STD_ON)
NCS_PRI_VAR void BM_GetMacKey(Csm_SymKeyType* pstMacKey)
{
    u8 ubIdx;
    const u8 * paubKeyData;
    u32 ulMacKeyLength;
    BM_CustomGetMacKey(&paubKeyData, &ulMacKeyLength);

    pstMacKey->length = ulMacKeyLength;

    for (ubIdx = 0U; ubIdx < (ulMacKeyLength/sizeof(u32)); ubIdx++)
    {
        pstMacKey->data[ubIdx]  = (u32)paubKeyData[((u16)((u16)ulMacKeyLength - 1U) - ((u16)ubIdx*4U))];
        pstMacKey->data[ubIdx] |= (u32)((u32)((u32)paubKeyData[((u16)((u16)ulMacKeyLength - 2U) - ((u16)ubIdx*4U))] << 8U)  & 0x0000FF00U);
        pstMacKey->data[ubIdx] |= (u32)((u32)((u32)paubKeyData[((u16)((u16)ulMacKeyLength - 3U) - ((u16)ubIdx*4U))] << 16U) & 0x00FF0000U);
        pstMacKey->data[ubIdx] |= (u32)((u32)((u32)paubKeyData[((u16)((u16)ulMacKeyLength - 4U) - ((u16)ubIdx*4U))] << 24U) & 0xFF000000U);
    }

}
/*----------------------{End BM_GetMacKey}---------------------------*/
#endif

/*-------------------------------------------------------------------------------*/
/* - Public Functions                                                            */
#if ((BM_AUTHENTICATED_BOOT_ENABLE == STD_ON) || (BM_SECURE_BOOT_ENABLE == STD_ON))
#if (BM_CSM_HASH_USED == STD_ON)
tBMBoolean BM_ComputeHash(u8 const * pubDataToSign, u32 uwDataLength, u8 * pubHashValue)
{
    tBMBoolean eComputeSuccess = BM_FALSE;

    m_ubCsmFinished = BM_FALSE;

    /* Start the hash calculation */
    m_ubCsmResult = Csm_HashStart(BM_CSM_CHECKSUM_ID);

    if (CSM_E_OK == m_ubCsmResult)
    {
        while (BM_FALSE == m_ubCsmFinished)
        {
#if (BM_CSM_WRAPPER_43_USED == STD_OFF)
            /* Trig the Csm main function */
            Csm_MainFunction();
#else
            /* added call to crypto main for ASR 4.3 crypto version*/
            Crypto_MainFunction();
#endif
            BM_CustomBckOperation();
        }

        m_ubCsmFinished = BM_FALSE;

        if (CSM_E_OK == m_ubCsmResult)
        {
            /* Update the Hash calculation */
            m_ubCsmResult = Csm_HashUpdate(BM_CSM_CHECKSUM_ID, pubDataToSign, uwDataLength);

            if (CSM_E_OK == m_ubCsmResult)
            {
                while (BM_FALSE == m_ubCsmFinished)
                {
#if (BM_CSM_WRAPPER_43_USED == STD_OFF)
                    /* Trig the Csm main function */
                    Csm_MainFunction();
#else
                    /* added call to crypto main for ASR 4.3 crypto version*/
                    Crypto_MainFunction();
#endif
                    BM_CustomBckOperation();
                }

                m_ubCsmFinished = BM_FALSE;
                m_ulDigestLength  = BM_CHECKSUM_SIZE_IN_BYTES;

                if (CSM_E_OK == m_ubCsmResult)
                {
                    /* Finish the hash calculation */
                    m_ubCsmResult = Csm_HashFinish(BM_CSM_CHECKSUM_ID, pubHashValue, &m_ulDigestLength, FALSE);

                    if (CSM_E_OK == m_ubCsmResult)
                    {
                        while (BM_FALSE == m_ubCsmFinished)
                        {
#if (BM_CSM_WRAPPER_43_USED == STD_OFF)
                            /* Trig the Csm main function */
                            Csm_MainFunction();
#else
                            /* added call to crypto main for the crypto ASR 4.3 version*/
                            Crypto_MainFunction();
#endif
                            BM_CustomBckOperation();
                        }

                        eComputeSuccess = BM_TRUE;
                    }
                }
            }
        }
    }

    return eComputeSuccess;
}
#endif

#if (BM_CSM_MAC_USED == STD_ON)
tBMBoolean BM_VerifyMac(u8 const * pubExpectedChecksum, u8 const * pubDataToSign, u32 uwDataLength)
{
    tBMBoolean eComputeSuccess = BM_FALSE;
    Csm_VerifyResultType eCsmResult = CSM_E_VER_NOT_OK;
    m_ubCsmFinished = BM_FALSE;

    BM_DisableECCCheck();
    /* Get the key used for MAC algorithm */
    BM_GetMacKey(&m_stBMMacKey);

    /* Start the hash calculation */
    m_ubCsmResult = Csm_MacVerifyStart(BM_CSM_CHECKSUM_ID, &m_stBMMacKey);

    if (CSM_E_OK == m_ubCsmResult)
    {
        while (BM_FALSE == m_ubCsmFinished)
        {
#if (BM_CSM_WRAPPER_43_USED == STD_OFF)
            /* Trig the Csm main function */
            Csm_MainFunction();
#else
            /* call to crypto main for the crypto ASR 4.3 version*/
            Crypto_MainFunction();
#endif
            BM_CustomBckOperation();
        }

        m_ubCsmFinished = BM_FALSE;

        if (CSM_E_OK == m_ubCsmResult)
        {
            /* Update the Hash calculation */
            m_ubCsmResult = Csm_MacVerifyUpdate(BM_CSM_CHECKSUM_ID, pubDataToSign, uwDataLength);

            if (CSM_E_OK == m_ubCsmResult)
            {
                while (BM_FALSE == m_ubCsmFinished)
                {
#if (BM_CSM_WRAPPER_43_USED == STD_OFF)
                    /* Trig the Csm main function */
                    Csm_MainFunction();
#else
                    /* call to crypto main for the crypto ASR 4.3 version*/
                    Crypto_MainFunction();
#endif
                    BM_CustomBckOperation();
                }

                m_ubCsmFinished = BM_FALSE;

                if (CSM_E_OK == m_ubCsmResult)
                {
                    /* Finish the hash calculation */
                    m_ubCsmResult = Csm_MacVerifyFinish(BM_CSM_CHECKSUM_ID, pubExpectedChecksum, BM_CHECKSUM_SIZE_IN_BITS, &eCsmResult);

                    if (CSM_E_OK == m_ubCsmResult)
                    {
                        while (BM_FALSE == m_ubCsmFinished)
                        {
#if (BM_CSM_WRAPPER_43_USED == STD_OFF)
                            /* Trig the Csm main function */
                            Csm_MainFunction();
#else
                            /* call to crypto main for the crypto ASR 4.3 version*/
                            Crypto_MainFunction();
#endif
                            BM_CustomBckOperation();
                        }

                        if (CSM_E_VER_OK == eCsmResult)
                        {
                            /* The comparison of MAC returned success status */
                            eComputeSuccess = BM_TRUE;
                        }
                    }
                }
            }
        }
    }

    BM_EnableECCCheck();
    return eComputeSuccess;
}
#endif

/*-------------------------------{BM_CsmNotification}--------------------------*/
Std_ReturnType BM_CsmNotification(Csm_ReturnType result)
{
    /* Update Csm status variables */
    m_ubCsmFinished = BM_TRUE;
    m_ubCsmResult = result;

    return E_OK;
}
/*------------------------------{end BM_CsmNotification}------------------------*/
#endif /* ((BM_AUTHENTICATED_BOOT_ENABLE == STD_ON) || (BM_SECURE_BOOT_ENABLE == STD_ON)) */

