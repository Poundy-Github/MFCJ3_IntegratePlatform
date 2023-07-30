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
/*%%   _____________________________   %%  \file BM_Cbk.c                        */
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
/* - Header Files                                                                */

#include "EB_Prj.h"

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

void BM_DisableECCCheck(void)
{

}

void BM_EnableECCCheck(void)
{

}


/*----------------------------{BM_HardwareInit}----------------------------------*/
void BM_HardwareInit (void)
{

}
/*----------------------------{end BM_HardwareInit}------------------------------*/

/*----------------------------{BM_SoftwareInit}----------------------------------*/
void BM_SoftwareInit(void)
{

}
/*----------------------------{end BM_SoftwareInit}-----------------------------*/

[!IF "as:modconf('BM')/General/BM_SOURCE_ADDRESS_CHECK = 'true'"!]
/*-----------------------------{BM_GetTesterAddress}----------------------------*/
void BM_GetTesterAddress (u8 *ubTesterAddress)
{
    OSC_PARAM_UNUSED(ubTesterAddress);
}
/*-------------------------{end BM_GetTesterAddress}----------------------------*/
[!ENDIF!]

[!IF "(as:modconf('BM')/Security/SecureBoot/SECURE_AUTHENTICATED_BOOT = 'Authenticated')"!]
/*------------------{BM_CustomGetComputedApplicationChecksum}-------------------*/
void BM_CustomGetComputedApplicationChecksum (u8 * pubChecksum,  u16 uwBlockIdentifier)
{
    OSC_PARAM_UNUSED(pubChecksum);
    OSC_PARAM_UNUSED(uwBlockIdentifier);
}
/*----------------{end BM_CustomGetComputedApplicationChecksum}-----------------*/
[!ENDIF!]

[!IF "(as:modconf('BM')/Security/SecureBoot/SECURE_AUTHENTICATED_BOOT = 'Authenticated')
    or (as:modconf('BM')/Security/SecureBoot/SECURE_AUTHENTICATED_BOOT = 'Secure')"!]
/*----------------------{BM_CustomGetExpectedApplicationChecksum}-----------------------*/
void BM_CustomGetExpectedApplicationChecksum (u8 * pubChecksum, u16 uwBlockIdentifier)
{
    OSC_PARAM_UNUSED(pubChecksum);
    OSC_PARAM_UNUSED(uwBlockIdentifier);
}
/*-------------------{end BM_CustomGetExpectedApplicationChecksum}----------------------*/

/*--------------------------{BM_CustomSetInvalidAppli}--------------------------*/
void BM_CustomSetInvalidAppli (u16 uwBlockIdentifier)
{
    OSC_PARAM_UNUSED(uwBlockIdentifier);
}
/*-----------------------{end BM_CustomSetInvalidAppli}-------------------------*/

/*---------------------------{BM_CustomBckOperation}----------------------------*/
void BM_CustomBckOperation (void)
{

}
/*------------------------{end BM_CustomBckOperation}---------------------------*/
[!ENDIF!]

[!IF "((as:modconf('BM')/Security/SecureBoot/SECURE_AUTHENTICATED_BOOT = 'Authenticated')
    or (as:modconf('BM')/Security/SecureBoot/SECURE_AUTHENTICATED_BOOT = 'Secure'))
    and (as:modconf('BM')/Security/SecureBoot/BOOT_VERIFICATION = 'ON')"!]
/*--------------------------{BM_CustomSetInvalidBoot}---------------------------*/
void BM_CustomSetInvalidBoot (void)
{

}
/*-----------------------{end BM_CustomSetInvalidBoot}--------------------------*/
[!ENDIF!]


[!IF "as:modconf('Prog')/General/Dual_Memory_Bank_Used = 'true'"!]
/*--------------------------{BM_CustomDualBankInit}---------------------------*/
void BM_CustomDualBankInit (void)
{

}
/*-----------------------{end BM_CustomDualBankInit}--------------------------*/
[!ENDIF!]


[!IF "General/BM_TIMEOUT_CHECK = 'true'"!]
/*---------------------------{BM_CustomIsNormalStartup}----------------------------*/
tBMBoolean BM_CustomIsNormalStartup (void)
{
    return(BM_TRUE);
}
/*-----------------------{end BM_CustomIsNormalStartup}-------------------------*/
[!ENDIF!]

 [!VAR "ASR_430_MACPATH" = "0"!]
                 
 [!IF "node:exists(as:modconf('BM')/Security/BMCsmReferences/BMCsmChecksumConfigId)"!]
 [!IF "node:exists(node:ref(as:modconf('BM')/Security/BMCsmReferences/BMCsmChecksumConfigId)/CsmJobPrimitiveRef)"!]
 [!IF "node:exists(node:ref(node:ref(as:modconf('BM')/Security/BMCsmReferences/BMCsmChecksumConfigId)/CsmJobPrimitiveRef)/CsmMacVerify)"!]
 [!VAR "ASR_430_MACPATH" = "1"!]
 [!ENDIF!]
 [!ENDIF!]
 [!ENDIF!]

 [!IF "((as:modconf('Prog')/General/Use_CSM_ASR430_DemoWrapper = 'false') and (contains(as:modconf('BM')/Security/BMCsmChecksumConfigId, '/Csm/Csm/CsmMacVerify/') =  'true'))
     or ((as:modconf('Prog')/General/Use_CSM_ASR430_DemoWrapper = 'true') and  "$ASR_430_MACPATH = 1")"!]

 
const u32 m_ulMacKeyKength = 0x00000010UL;
const u8 m_aubKeyData[16U] =
{
    0xEBU, 0xEBU, 0xEBU, 0xEBU,
    0xEBU, 0xEBU, 0xEBU, 0xEBU,
    0xEBU, 0xEBU, 0xEBU, 0xEBU,
    0xEBU, 0xEBU, 0xEBU, 0xEBU
};
/*---------------------------{BM_CustomGetMacKey}----------------------------*/
void BM_CustomGetMacKey(const u8** paubKeyData, u32* pulKeyLength)
{
    *paubKeyData   = m_aubKeyData;
    *pulKeyLength  = m_ulMacKeyKength;
}
/*-----------------------{end BM_CustomGetMacKey}-------------------------*/
[!ENDIF!]
