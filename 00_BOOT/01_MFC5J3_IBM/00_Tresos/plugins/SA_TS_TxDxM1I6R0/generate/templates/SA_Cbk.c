/*===============================================================================*/
/*                                                                               */
/*                               BOOT Layers                                     */
/*                                                                               */
/* ----------------------------------------------------------------------------- */
/*                                                                               */
/*                               SA layer                                        */
/*                                                                               */
/*===============================================================================*/
/*%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%                                        */
/*%%   _____________________________   %%  \file SA_Cbk.c                        */
/*%%  |                             |  %%  \brief SA layer source plugin file    */
/*%%  |   &&&&&   &&&&&             |  %%  Module version: 1.6.3 BL-3.X */
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

/*=============================== FILE INCLUSION ================================*/
/*                                                                               */
#include "EB_Prj.h"
#include "board.h"

/*=============================== IMPLEMENTATION ================================*/
/*                                                                               */

#if (SA_SEED_TYPE != SA_SEED_CSM_RANDOM)
/** \brief API that calculates the security access key
 **
 ** This callback is called on reception of SecurityAccess service to perfom
 ** computation of the security key based on a random seed.
 **
 ** \param[in] aubSeed Address of the seed array
 ** \param[out] aubCalculatedKey Address where the calculated key will be copied
 **/
void SA_CustomCalculateKey(u8 * aubSeed, u8 * aubCalculatedKey)
{
    OSC_PARAM_UNUSED(aubSeed);
    OSC_PARAM_UNUSED(aubCalculatedKey);
}
#endif /*(SA_SEED_TYPE != SA_SEED_CSM_RANDOM)*/


#if (SA_ANTISCANNING_ENABLED == STD_ON)
/** \brief API that stores the security access anti-scanning retry counter
 **
 ** This callback is called on reception of SecurityAccess service in case
 ** anti-scanning feature is activated. The counter value provided as parameter
 ** shall be stored in non-volatile memory.
 **
 ** \param[in] RetryCntValue Value of security access anti-scanning retry counter
 **/
void SA_CustomStoreAsRetryCnt(u8 RetryCntValue)
{
    OSC_PARAM_UNUSED(RetryCntValue);
}
#endif /*(PROG_SA_ANTISCANNING_ENABLE == STD_ON)*/


#if (SA_ANTISCANNING_ENABLED == STD_ON)
/** \brief API that restores the security access anti-scanning retry counter
 **
 ** This callback is called at Bootloader startup (if anti-scanning feature is
 ** activated) to get the retry counter value from non-volatile memory.
 **
 ** \return Value of security access anti-scanning retry counter
 **/
u8 SA_CustomRestoreAsRetryCnt(void)
{
    u8 RetAsRetryCnt = 0;
    /*Fetch from NVM*/
    return RetAsRetryCnt;
}
#endif /*(PROG_SA_ANTISCANNING_ENABLE == STD_ON)*/

[!IF "(as:modconf('SA')/General/Seed_Type = 'Cryptographic_Random') or (as:modconf('SA')/General/Compare_Key_Type = 'Verify_Signature')"!]
/** \brief Get the last random number stored
 **
 ** Called in SA_GenerateRandomCallback when Csm is in SA_SEED_GEN_STATE_START state
 **
 ** \param[out] aubDataRandomNumber Generated random number array
 **/
void SA_CustomGetLastRandomNumber(u8* aubDataRandomNumber)
{
    OSC_PARAM_UNUSED(aubDataRandomNumber);
}

/** \brief Store the generated random number
 **
 ** Called in SA_GenerateRandomCallback when Csm is in SA_RANDOM_GEN_STATE_GENERATE state
 **
 ** \param[in] aubDataRandomNumber Generated random number array
 **/
void SA_CustomStoreRandomNumber(u8* pubDataRandomNumber)
{
    OSC_PARAM_UNUSED(pubDataRandomNumber);
}


/*Public Key:EC172B93AD5E563BF4932C70E1245034C35467EF2EFD4D64EBF819683467E2BF*/

const u32 m_ulSAPublicExponent = 0UL;

const u8 m_aubSAPublicModulus[32] =
    {
        0xEC, 0x17, 0x2B, 0x93, 0xAD, 0x5E, 0x56, 0x3B,
        0xF4, 0x93, 0x2C, 0x70, 0xE1, 0x24, 0x50, 0x34,
        0xC3, 0x54, 0x67, 0xEF, 0x2E, 0xFD, 0x4D, 0x64,
        0xEB, 0xF8, 0x19, 0x68, 0x34, 0x67, 0xE2, 0xBF,
    };

/** \brief Get the public key when using asymmetric cryptography. Used in SA_InitCrypto
 **
 ** \param[out] paubPublicModulus Pointer to public key modulus array
 ** \param[out] pulPublicExponent Pointer to public key exponent
 **
 **/
/*---------------------------{PROG_CustomGetAsymPublicKey}-----------------------------*/
void SA_CustomGetAsymPublicKey(const u8** paubPublicModulus, u32* pulPublicExponent)
{
    *paubPublicModulus = m_aubSAPublicModulus;
    *pulPublicExponent = m_ulSAPublicExponent;
}
/*------------------------{end PROG_CustomGetAsymPublicKey}--------------------------*/
[!ENDIF!]

