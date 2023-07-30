/*********************************************************************************/
/*                                                                               */
/*                                BOOT Layers                                    */
/*                                                                               */
/* ------------------------------------------------------------------------------*/
/*                                                                               */
/*                                 BM configuration                              */
/*                                                                               */
/*********************************************************************************/
/*%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%                                        */
/*%%   _____________________________   %%  \file BM_Cfg.h                        */
/*%%  |                             |  %%  \brief BM layer include plugin file   */
/*%%  |   &&&&&   &&&&&             |  %%  Module version: 1.3.0 BL-3.X                */
/*%%  |   &       &    &            |  %%  Variant: OsekCore                  */
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
[!AUTOSPACING!]

#ifndef BM_CFG_H
#define BM_CFG_H

[!IF "node:exists(as:modconf('Csm'))"!]
    [!IF "(as:modconf('Prog')/General/Use_CSM_ASR430_DemoWrapper='true')"!]
#include "demo_csmwrapper.h"
/* Use a wrapper in the demo in order to use ASR 4.3 crypto interfaces */
#define BM_CSM_WRAPPER_43_USED              STD_ON
    [!ELSE!]
#define BM_CSM_WRAPPER_43_USED              STD_OFF
    [!ENDIF!]
[!ELSE!]
#define BM_CSM_WRAPPER_43_USED              STD_OFF
[!ENDIF!]

 [!IF "node:exists(as:modconf('EB'))"!]
 /*Network Selection before BL 3 via the EB module*/
#define BM_CAN_USED              0U
#define BM_FLEXRAY_USED          1U
#define BM_ETHERNET_USED         2U
#define BM_NETWORK_USED              [!WS "21"!][!IF "(as:modconf('EB')/General/Protocol_Type = 'CAN')"!]BM_CAN_USED[!ELSEIF "(as:modconf('EB')/General/Protocol_Type = 'FLEXRAY')"!]BM_FLEXRAY_USED[!ELSE!]BM_ETHERNET_USED[!ENDIF!]
[!IF "(as:modconf('EB')/General/Protocol_Type = 'FLEXRAY')"!]

#define BM_FR_CYCLE_LENGTH              [!"General/BM_FR_CYCLE_LENGTH"!]U
#define BM_NETWORK_FLEXRAY_SUPPORTED              STD_ON
[!ELSE!]
#define BM_NETWORK_FLEXRAY_SUPPORTED              STD_OFF
[!ENDIF!]
[!ENDIF!]

/* BM Network Management */
#define BM_NETWORK_MANAGEMENT_ENABLE              [!WS "8"!][!IF "(as:modconf('Prog')/General/Network_Management = 'true')"!]STD_ON[!ELSE!]STD_OFF[!ENDIF!]

 [!IF "node:exists(as:modconf('BlPduR'))"!]
 /*Network Selection for BL-3.x(when BLPDUR module used)*/
 	[!IF "as:modconf('BlPduR')/General/FlexRay_Protocol_Supported = 'true'"!]
#define BM_NETWORK_FLEXRAY_SUPPORTED              STD_ON
#define BM_FR_CYCLE_LENGTH                  [!"General/BM_FR_CYCLE_LENGTH"!]U
	[!ELSE!]
#define BM_NETWORK_FLEXRAY_SUPPORTED              STD_OFF
	[!ENDIF!]
[!ELSE!]
#ifndef BM_NETWORK_FLEXRAY_SUPPORTED
#define BM_NETWORK_FLEXRAY_SUPPORTED              STD_OFF
#endif
[!ENDIF!]
[!IF "node:exists(as:modconf('BlPduR'))"!]
 	[!IF "as:modconf('BlPduR')/General/Can_Protocol_Supported = 'true'"!]
#define BM_NETWORK_CAN_SUPPORTED              STD_ON
	[!ELSE!]
#define BM_NETWORK_CAN_SUPPORTED              STD_OFF
	[!ENDIF!]
[!ELSE!]
#define BM_NETWORK_CAN_SUPPORTED              STD_OFF
[!ENDIF!]

[!IF "node:exists(as:modconf('BlPduR'))"!]
  	[!IF "as:modconf('BlPduR')/General/Eth_Protocol_Supported = 'true'"!]
#define BM_NETWORK_ETH_SUPPORTED              STD_ON
 	[!ELSE!]
#define BM_NETWORK_ETH_SUPPORTED              STD_OFF
 	[!ENDIF!]
[!ELSE!]
#define BM_NETWORK_ETH_SUPPORTED 		STD_OFF
[!ENDIF!]

[!IF "node:exists(as:modconf('BlPduR'))"!]
   [!IF "as:modconf('BlPduR')/General/Lin_Protocol_Supported = 'true'"!]
#define BM_NETWORK_LIN_SUPPORTED              STD_ON
  [!ELSE!]
#define BM_NETWORK_LIN_SUPPORTED              STD_OFF
  [!ENDIF!]
[!ELSE!]
#define BM_NETWORK_LIN_SUPPORTED              STD_OFF
[!ENDIF!]
/* BM Timeout Check */
#define BM_TIMEOUT_CHECK_OFF                0U
#define BM_TIMEOUT_CHECK_ON                 1U
#define BM_TIMEOUT_CHECK                    [!WS "20"!][!IF "General/BM_TIMEOUT_CHECK = 'true'"!]BM_TIMEOUT_CHECK_ON[!ELSE!]BM_TIMEOUT_CHECK_OFF[!ENDIF!]

[!IF "General/BM_TIMEOUT_CHECK = 'true'"!]
/* Specific to timeout management */
#define BM_CALL_CYCLE                       [!"General/BM_CALL_CYCLE"!]U
#define BM_TIMEOUT_VALUE                    [!"General/BM_TIMEOUT_VALUE"!]U
[!ENDIF!]

[!IF "as:modconf('BM')/General/BM_SOURCE_ADDRESS_CHECK = 'true'"!]
/* Accept All Tester Address Value */
#define EB_ALL_TESTER_ADDRESS               0xFFU
[!ENDIF!]

/* BM Csm Presence */
[!IF "node:exists(as:modconf('Csm'))"!]
#define BM_CSM_PRESENT                      STD_ON
[!ELSE!]
#define BM_CSM_PRESENT                      STD_OFF
[!ENDIF!]

/* Source Address Check status */
#define BM_SOURCE_ADDRESS_CHECK             [!WS "13"!][!IF "(as:modconf('BM')/General/BM_SOURCE_ADDRESS_CHECK = 'true')"!]STD_ON[!ELSE!]STD_OFF[!ENDIF!][!CR!]

/* BM Authenticated Boot/Secure Boot information */
#define BM_AUTHENTICATED_BOOT_ENABLE        [!WS "8"!][!IF "(as:modconf('BM')/Security/SecureBoot/SECURE_AUTHENTICATED_BOOT = 'Authenticated')"!]STD_ON[!ELSE!]STD_OFF[!ENDIF!][!CR!]
#define BM_SECURE_BOOT_ENABLE               [!WS "15"!][!IF "(as:modconf('BM')/Security/SecureBoot/SECURE_AUTHENTICATED_BOOT = 'Secure')"!]STD_ON[!ELSE!]STD_OFF[!ENDIF!][!CR!]
#define BM_BOOT_CHECKSUM_VERIFICATION       [!WS "7"!][!IF "(as:modconf('BM')/Security/SecureBoot/BOOT_VERIFICATION = 'ON')"!]STD_ON[!ELSE!]STD_OFF[!ENDIF!][!CR!]

[!IF "((Security/SecureBoot/SECURE_AUTHENTICATED_BOOT = 'Authenticated') or (Security/SecureBoot/SECURE_AUTHENTICATED_BOOT = 'Secure'))"!]
/* Specific to Authenticated and Secure Boot */
/* Csm Configuration used */
#define BM_CSM_CHECKSUM_ID                  [!"as:name(as:ref(as:modconf('BM')/Security/BMCsmReferences/BMCsmChecksumConfigId))"!]
/* Size of the checksum */
#define BM_CHECKSUM_SIZE_IN_BITS            [!"num:dectoint((Security/SecureBoot/CHECKSUM_LENGTH)*8)"!]U
#define BM_CHECKSUM_SIZE_IN_BYTES           [!"num:dectoint(Security/SecureBoot/CHECKSUM_LENGTH)"!]U
/* Type of algorithm used to check integrity of Bootloader/Application */
[!IF "as:modconf('Prog')/General/Use_CSM_ASR430_DemoWrapper = 'false'"!]
/* For version of Csm to 4.0.3 */
#define BM_CSM_MAC_USED                     [!WS "21"!][!IF "contains(as:modconf('BM')/Security/BMCsmReferences/BMCsmChecksumConfigId, '/Csm/Csm/CsmMacVerify/') =  'true'"!]STD_ON[!ELSE!]STD_OFF[!ENDIF!][!CR!]
#define BM_CSM_HASH_USED                    [!WS "20"!][!IF "contains(as:modconf('BM')/Security/BMCsmReferences/BMCsmChecksumConfigId, '/Csm/Csm/CsmHash/') =  'true'"!]STD_ON[!ELSE!]STD_OFF[!ENDIF!][!CR!]
[!ELSE!]
/* For version of Csm from 4.3.0 */
#define BM_CSM_HASH_USED                    [!WS "20"!][!IF "node:exists(node:ref(node:ref(as:modconf('BM')/Security/BMCsmReferences/BMCsmChecksumConfigId)/CsmJobPrimitiveRef)/CsmHash)"!]STD_ON[!ELSE!]STD_OFF[!ENDIF!][!CR!]
#define BM_CSM_MAC_USED                     [!WS "21"!][!IF "node:exists(node:ref(node:ref(as:modconf('BM')/Security/BMCsmReferences/BMCsmChecksumConfigId)/CsmJobPrimitiveRef)/CsmMacVerify)"!]STD_ON[!ELSE!]STD_OFF[!ENDIF!][!CR!]
[!ENDIF!]
[!IF "Security/SecureBoot/BOOT_VERIFICATION = 'ON'"!]
/* Specific to Authenticated and Secure Boot with Bootloader verification */
#define BM_BOOT_START_ADDR                  ([!"num:inttohex(Security/SecureBoot/BootCksStartAddress)"!]U)
#define BM_BOOT_LENGTH                      ([!"num:inttohex(Security/SecureBoot/BootCksRangeLength)"!]U)
[!ENDIF!]
[!ELSE!]
#define BM_CSM_MAC_USED                     STD_OFF
#define BM_CSM_HASH_USED                    STD_OFF
[!ENDIF!]

[!IF "as:modconf('Prog')/General/Dual_Memory_Bank_Used = 'true'"!]
#define BM_OTA_DUALBANK_USED                          STD_ON
[!ELSE!]
#define BM_OTA_DUALBANK_USED                          STD_OFF
[!ENDIF!]

[!IF "((as:modconf('BM')/Security/SecureBoot/SECURE_AUTHENTICATED_BOOT='Authenticated') or
     (as:modconf('BM')/Security/SecureBoot/SECURE_AUTHENTICATED_BOOT='Secure')) and (not(node:exists(as:modconf('ProgVCC'))))"!]
/* Table of information for each Block needed for Authenticated/Secure Boot */
extern const tProg_BlockSecureBootInfo stCfgBMBlockSecureBootInfo[PROG_BLOCK_NB];
[!ENDIF!]

#endif /* BM_CFG_H */
