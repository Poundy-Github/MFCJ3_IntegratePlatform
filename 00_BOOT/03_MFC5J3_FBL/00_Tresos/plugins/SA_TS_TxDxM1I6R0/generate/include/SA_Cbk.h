/*********************************************************************************/
/*                                                                               */
/*                                 Sa LAYER                                      */
/*                                                                               */
/* ----------------------------------------------------------------------------- */
/*                                                                               */
/*                                  SA layer                                     */
/*                                                                               */
/*********************************************************************************/
/*%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%                                        */
/*%%   _____________________________   %%  \file SA_Cbk.h                        */
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

#ifndef SA_CBK_H
#define SA_CBK_H

[!IF "(as:modconf('SA')/General/Seed_Type = 'Cryptographic_Random') or (as:modconf('SA')/General/Compare_Key_Type = 'Verify_Signature')"!]
#include "Csm.h"
[!ENDIF!]
 
[!IF "as:modconf('SA')/General/Security_Algorithm_Type = 'Standard'"!]
/* Include header file that contains the standard algorithm function*/
#include "PROG_SecurityAlgorithm.h"
[!ENDIF!]

/*--------------------------------{SA_CustomCalculateKey}------------------------*/
extern void SA_CustomCalculateKey(u8 * aubSeed, u8 * aubCalculatedKey);

/*--------------------------------{SA_CustomStoreAsRetryCnt}---------------------*/
extern void SA_CustomStoreAsRetryCnt(u8 RetryCntValue);

/*--------------------------------{SA_CustomRestoreAsRetryCnt}-------------------*/
extern u8 SA_CustomRestoreAsRetryCnt(void);

[!IF "(as:modconf('SA')/General/Seed_Type = 'Cryptographic_Random') or (as:modconf('SA')/General/Compare_Key_Type = 'Verify_Signature')"!]
/*--------------------------------{SA_CustomGetLastRandomNumber}-------------------*/
extern void SA_CustomGetLastRandomNumber(u8* aubDataRandomNumber);

/*--------------------------------{SA_CustomStoreRandomNumber}-------------------*/
extern void SA_CustomStoreRandomNumber(u8* pubDataRandomNumber);

extern void SA_CustomGetAsymPublicKey(const u8** paubPublicModulus, u32* pulPublicExponent);

[!ENDIF!]


#endif      /* SA_CBK_H */

