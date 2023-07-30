#ifndef PROG_CRY_H
#define PROG_CRY_H

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
/*%%   _____________________________   %%  \file PROG_Cry.h                      */
/*%%  |                             |  %%  \brief PROG layer source plugin file  */
/*%%  |   &&&&&   &&&&&             |  %%  Module version: 2.17.0 BL-3.X */
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
[!AUTOSPACING!]
#if (PROG_CRY_PRESENT == STD_ON)
#include "Csm.h"

/*============================= PUBLIC DEFINITIONS ==============================*/
/*                                                                               */
/*-------------------------------------------------------------------------------*/
/* - Public Variables                                                            */

/*-------------------------------------------------------------------------------*/
/* - Public Function Prototypes                                                  */

typedef u8 tProgCryState;
#define PROG_IDLE                          0x00U
#define PROG_SIGNATURE_CHECK_START         0x01U
#define PROG_SIGNATURE_CHECK_UPDATE        0x02U
#define PROG_SIGNATURE_CHECK_UPDATE_END    0x03U
#define PROG_SIGNATURE_CHECK_FINISH        0x04U
#define PROG_HASH_START                    0x05U
#define PROG_HASH_START_END                0x06U
#define PROG_HASH_UPDATE                   0x07U
#define PROG_HASH_END                      0x08U
#define PROG_HASH_FINISH                   0x09U
#define PROG_SIGNATURE_CHECK_START_END     0x0AU
#define PROG_MAC_GENERATE_START            0x0BU
#define PROG_MAC_GENERATE_START_END        0x0CU
#define PROG_MAC_GENERATE_UPDATE           0x0DU
#define PROG_MAC_GENERATE_UPDATE_END       0x0EU
#define PROG_MAC_GENERATE_FINISH           0x0FU


/* Define the structure of a public key used for signature verification */
typedef struct
{
    const u8* pubKeyModulus;
    uint32 ulKeyModulusSize;
    const u8* pubKeyExponent;
    uint32 ulKeyExponentSize;
}tKeyStructure;

[!IF "node:exists(as:modconf('Csm'))"!]

[!IF "node:exists(as:modconf('ProgGM'))"!]
/* define the ID of each configuration */
#define PROG_CSM_SIG_VERIFY_ID            [!"name(as:ref(as:modconf('Prog')/GM/ProgCsmReferences/ProgCsmSignatureVerifyConfigId))"!]
#define PROG_CSM_HASH_FOR_SIGNATURE_ID    [!"name(as:ref(as:modconf('Prog')/GM/ProgCsmReferences/ProgCsmHashConfigId))"!]
[!ELSEIF "node:exists(as:modconf('ProgVCC'))"!]
#define PROG_CSM_SIG_VERIFY_ID            [!"name(as:ref(as:modconf('Prog')/Security/ProgCsmReferences/ProgCsmSignatureVerifyConfigId))"!]
#define PROG_CSM_HASH_ID                  [!"name(as:ref(as:modconf('Prog')/Security/ProgCsmReferences/ProgCsmHashConfigId))"!]
[!ELSEIF "not(node:exists(as:modconf('ProgFCA')) and as:modconf('ProgFCA')/General/PROG_FCA_VARIANT='Atlantis_Mid')"!]
/* define the ID of each configuration */
#define PROG_CSM_SIG_VERIFY_ID            [!"name(as:ref(as:modconf('Prog')/Security/ProgCsmReferences/ProgCsmSignatureVerifyConfigId))"!]
[!ENDIF!]

[!IF "node:exists(as:modconf('ProgDAG')) or (node:exists(as:modconf('ProgFCA')) and as:modconf('ProgFCA')/General/PROG_FCA_VARIANT='Atlantis_High')"!]
#define PROG_CSM_HASH_FOR_SIGNATURE_ID    [!"name(as:ref(as:modconf('Prog')/Security/ProgCsmReferences/ProgCsmHashConfigId))"!]
[!ENDIF!]

[!ENDIF!]

/* Define the size of the modulus and exponent used for signature verification */
#define PROG_MODULUS_SIZE                 256U
#define PROG_EXPONENT_SIZE                3U
/*                                                                               */
/*-------------------------------------------------------------------------------*/

#endif /* (PROG_CRY_PRESENT == STD_ON) */
#endif      /* PROG_CRY_H */
