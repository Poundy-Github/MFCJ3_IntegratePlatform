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
/*%%   _____________________________   %%  \file SA_Types.h                   */
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

#ifndef SA_TYPES_H
#define SA_TYPES_H

#include "SA_Cfg.h"

[!IF "(as:modconf('SA')/General/Seed_Type = 'Cryptographic_Random') or (as:modconf('SA')/General/Compare_Key_Type = 'Verify_Signature')"!]
#include "Csm.h"
[!IF "(as:modconf('SA')/General/Compare_Key_Type = 'Verify_Signature')"!]
#include "Std_Types.h"
[!ENDIF!]
[!ENDIF!]

typedef u8 tSaStatus;
#define SA_E_OK         0x01U
#define SA_E_NOT_OK     0x02U
#define SA_E_BUSY       0x03U
/*Following are for Anti-scanning*/
#define SA_E_NOK_INVALID_KEY      0x04U
[!IF "(as:modconf('SA')/General/Enable_Antiscanning = 'true')"!]
#define SA_E_NOK_AS_LOCKED        0x05U
[!ENDIF!]

[!IF "(as:modconf('SA')/General/Seed_Type = 'Cryptographic_Random') or (as:modconf('SA')/General/Compare_Key_Type = 'Verify_Signature')"!]
typedef u8 tSaCsmState;
[!IF "(as:modconf('SA')/General/Seed_Type = 'Cryptographic_Random')"!]
#define SA_CSM_STATE_INIT               0x00U
#define SA_IDLE                         0x01U
#define SA_SEED_GEN_STATE_INIT          0x02U
#define SA_SEED_GEN_STATE_START         0x03U
#define SA_SEED_GEN_STATE_UPDATE        0x05U
#define SA_RANDOM_GEN_STATE_GENERATE    0x06U
#define SA_RANDOM_GEN_STATE_STANDBY     0x07U
[!ENDIF!]
[!IF "(as:modconf('SA')/General/Compare_Key_Type = 'Verify_Signature')"!]
#define SA_SIGNATURE_CHECK_START        0x08U
#define SA_SIGNATURE_CHECK_UPDATE       0x09U
#define SA_SIGNATURE_CHECK_STANDBY      0x0CU
#define SA_SIGNATURE_CHECK_FINISH       0x0AU
[!ENDIF!]
[!ENDIF!]

/* SA boolean type */
#define SA_FALSE               0U
#define SA_TRUE                1U
typedef u8 tSaBoolean;

[!IF "node:exists(as:modconf('Prog')) and (as:modconf('Prog')/General/Enable_Compression = 'true')"!]
/*
* Number of bits allocated to indices into the text window
*/
#define LZSS_INDEX_BIT_COUNT      (u8)10U
/*
* Number of bits allocated for the length of an encode phrase
*/
#define LZSS_LENGTH_BIT_COUNT     (u8)4U
/*
* Size of the sliding window
*/
#define LZSS_WINDOW_SIZE          (u16)((u16)(1U) << LZSS_INDEX_BIT_COUNT )
/*
* Number of bytes to encode a byte array.
* Used to calculate if compression should be done or not
*/
#define LZSS_BREAK_EVEN   (u8)( ( 1U + LZSS_INDEX_BIT_COUNT + LZSS_LENGTH_BIT_COUNT ) / 9U )
/*
* End of stream indicator
*/
#define LZSS_END_OF_STREAM        (u8)0U

#define LZSS_MOD_WINDOW( a )      (u16)( ( a ) & ( LZSS_WINDOW_SIZE - 1U ) )

#define SA_DECOMP_OUT_BUF_SIZE   [!"num:i(General/Decomp_Out_Buffer_size)"!]U

#define SA_DECOMP_INIT              0x01U
#define SA_DECOMP_UNCOMPRESSED      0x02U
#define SA_DECOMP_COMPRESSPOS       0x04U
#define SA_DECOMP_COMPRESSLEN       0x08U
#define SA_DECOMP_COMPLETE          0x10U
#define SA_DECOMP_IN_PROGRESS       0x20U
#define SA_DECOMP_FINISH            0x40U
#define SA_ERR_NULL_PTR             0x80U
typedef u8 tDecompressStateType;
[!ENDIF!]


[!IF "(as:modconf('SA')/General/Enable_Antiscanning = 'true')"!]
typedef struct
{
 u8 ubRetryCnt;              /*Anti-scanning retry counter*/
 u32 ulLockTimer;            /*Anti-scanning Lock Timer*/
 tSaBoolean ubAsLocked;      /*Anti-scanning Lock State */
}tAntiscanInfo;
[!ENDIF!]
 /* use of demo wrapper check below */
 [!IF "node:exists(as:modconf('Csm'))"!]
     [!IF "(as:modconf('Prog')/General/Use_CSM_ASR430_DemoWrapper='true')"!]
#include "demo_csmwrapper.h"
/* Use a wrapper in the demo in order to use ASR 4.3 crypto interfaces */
#define SA_CSM_WRAPPER_43_USED				STD_ON    
	[!ELSE!]
#define SA_CSM_WRAPPER_43_USED				STD_OFF            
    [!ENDIF!]
[!ELSE!]
#define SA_CSM_WRAPPER_43_USED				STD_OFF   
[!ENDIF!]
#endif      /* SA_TYPES_H */
