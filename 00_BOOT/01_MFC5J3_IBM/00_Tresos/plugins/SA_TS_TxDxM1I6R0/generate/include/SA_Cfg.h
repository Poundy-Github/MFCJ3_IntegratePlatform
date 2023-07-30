/*********************************************************************************/
/*                                                                               */
/*                                 Sa LAYER                                      */
/*                                                                               */
/* ----------------------------------------------------------------------------- */
/*                                                                               */
/*                               Security Access                                 */
/*                                                                               */
/*********************************************************************************/
/*%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%                                        */
/*%%   _____________________________   %%  \file SA_Cfg.h                        */
/*%%  |                             |  %%                                        */
/*%%  |   &&&&&   &&&&&             |  %%  Module version: 1.6.3 BL-3.X */
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

#ifndef SA_CFG_H
#define SA_CFG_H

/* Timer period in milliseconds for the SA periodic task */
/* The minimum value accepted for SA_MANAGE_PERIOD is 1 */
/* Range : (1 .. 100) */
#define SA_MANAGE_PERIOD                [!"num:i(General/MANAGE_PERIOD)"!]U

#define SA_SEED_LEN   ([!"num:dectoint(General/Security_Access_Seed_Length)"!]U)
#define SA_KEY_LEN   ([!"num:dectoint(General/Security_Access_Key_Length)"!]U)
#define SA_STATIC_KEY_LEN 5U     /* size of the static key */

#define SA_COMPRESSION_ENABLED            0x01U
#define SA_COMPRESSION_DISABLED           0x02U
#define SA_COMPRESSION_STATE   [!WS "5"!][!IF "node:exists(as:modconf('Prog')) and (as:modconf('Prog')/General/Enable_Compression = 'true')"!]SA_COMPRESSION_ENABLED[!ELSE!]SA_COMPRESSION_DISABLED[!ENDIF!][!CR!]

#define SA_RANDOM_NUMBER_LENGTH SA_SEED_LEN

#define SA_CHALLENGE_BIT 64U /* Size of PROG_SA_CHALLENGE_BYTE in bit, 8*8 = 64 */

#define SA_SEED_STANDARD    0x00U
#define SA_SEED_CSM_RANDOM  0x01U

#define SA_SEED_TYPE                       [!IF "as:modconf('SA')/General/Seed_Type = 'Cryptographic_Random'"!]SA_SEED_CSM_RANDOM[!ELSE!]SA_SEED_STANDARD[!ENDIF!]

[!IF "as:modconf('SA')/General/Seed_Type = 'Standard'"!]
#define SA_SECURITY_ALOGORITHM_STANDARD    0X00U
#define SA_SECURITY_ALOGORITHM_CUSTOM      0X01U
 
#define SA_SECURITY_ALOGORITHM_TYPE       [!IF "as:modconf('SA')/General/Security_Algorithm_Type = 'Standard'"!]SA_SECURITY_ALOGORITHM_STANDARD[!ELSE!]SA_SECURITY_ALOGORITHM_CUSTOM[!ENDIF!]
[!ENDIF!]

#define SA_COMPARE_KEY_STANDARD         0x00U
#define SA_COMPARE_KEY_VERIFY_SIGNATURE 0x01U

#define SA_COMPARE_KEY_TYPE                [!IF "General/Compare_Key_Type = 'Verify_Signature'"!]SA_COMPARE_KEY_VERIFY_SIGNATURE[!ELSE!]SA_COMPARE_KEY_STANDARD[!ENDIF!]

[!IF "(as:modconf('SA')/General/Seed_Type = 'Cryptographic_Random') or (as:modconf('SA')/General/Compare_Key_Type = 'Verify_Signature')"!]
#define SA_USE_CRYPTO                  STD_ON

[!IF "(as:modconf('SA')/General/Seed_Type = 'Cryptographic_Random')"!]
#define SA_CSM_RANDOM_GENERATE_ID       [!"name(as:ref(as:modconf('SA')/General/CsmRandomGenerateConfigId))"!]
#define SA_CSM_RANDOM_SEED_ID           [!"name(as:ref(as:modconf('SA')/General/CsmRandomSeedConfigId))"!]
[!ENDIF!]

[!IF "as:modconf('SA')/General/Compare_Key_Type = 'Verify_Signature'"!]
#define SA_CSM_SIG_VERIFY_ID           [!"name(as:ref(as:modconf('SA')/General/CsmSignatureVerifyConfigId))"!]
#define SA_SIGNATURE_LENGTH             SA_KEY_LEN
[!IF "node:exists(as:modconf('ProgDAG'))"!]
#define SA_PUBLIC_KEY_LENGTH            32U
#define SA_CRY_EXPONENT_ENABLED       STD_OFF
[!ELSEIF "node:exists(as:modconf('ProgFCA'))"!]
#define SA_PUBLIC_KEY_LENGTH            256U
#define SA_CRY_EXPONENT_ENABLED       STD_ON
[!ENDIF!]
[!ENDIF!]

[!ELSE!]
#define SA_USE_CRYPTO                   STD_OFF
[!ENDIF!]

[!IF "(as:modconf('SA')/General/Enable_Antiscanning = 'true')"!]
#define SA_ANTISCANNING_ENABLED            STD_ON
/* Anti-scanning Timer Load value */
#define  SA_AS_LOCK_TIMER                  [!"num:i(General/Security_Access_As_Timer div General/MANAGE_PERIOD)"!]U
/* Anti-scanning Retry Counter value */
#define SA_AS_MAX_NB_RETRY                 [!"num:i(General/Security_Access_As_Retry_Counter)"!]U
[!ELSE!]
#define SA_ANTISCANNING_ENABLED            STD_OFF
[!ENDIF!]

[!IF "(as:modconf('SA')/General/Enable_Static_Seed = 'true')"!]
#define SA_STATIC_SEED_ENABLED            STD_ON
[!ELSE!]
#define SA_STATIC_SEED_ENABLED            STD_OFF
[!ENDIF!]

[!IF "node:exists(as:modconf('ProgJLR')) or node:exists(as:modconf('ProgVCC'))"!]
extern const u8 m_aubStaticKey[SA_STATIC_KEY_LEN];
[!ENDIF!]

#endif      /* SA_CFG_H */
