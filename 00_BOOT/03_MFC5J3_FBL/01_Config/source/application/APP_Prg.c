/*********************************************************************************/
/*                                                                               */
/*                                  CAN Stack                                    */
/*                                                                               */
/* ----------------------------------------------------------------------------- */
/*                                                                               */
/*                                APP                                            */
/*                                                                               */
/*********************************************************************************/
/*%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%                                        */
/*%%   _____________________________   %%  \file APP_Prg.c                       */
/*%%  |                             |  %%                                        */
/*%%  |   &&&&&   &&&&&             |  %%  Module version: 3.6.8 BL-3.X                */
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

/*  MISRA-C:2004 Deviation List
 *
 *  MISRA-1) Deviated Rule: 16.7 (advisory)
 *   A pointer parameter in a function prototype should be declared as pointer to const
 *   if the pointer is not used to modify the addressed object.
 *
 *   Reason:
 *   The MISRA rule is not violated. This pointer will be used once the function is completed by customer.
 */


/******************************** FILE INCLUSION *********************************/
/*                                                                               */
/*-------------------------------------------------------------------------------*/
/* - Header Files: EB                                                            */
#include "EB_Prj.h"
#include "board.h"
#include "BlPduR_Prj.h"
#include "PROG_Priv.h"
#include "MemIf.h"
#include "TSMem.h"
#include "log.h"
/*                                                                               */
/*********************************************************************************/

/****************************** PUBLIC DEFINITIONS *******************************/
/*                                                                               */
/*-------------------------------------------------------------------------------*/
/* - Public Variables                                                            */

/*-------------------------------------------------------------------------------*/
/* - Public Function Prototypes                                                  */
extern tUdsStatus PROG_CheckMemory(u16 *puwLen, u8 *aubUdsData);
extern tProgStatus PROG_CheckFlashStatus(u8 ubLogicalSegmentId);

/*-------------------------------------------------------------------------------*/
/* - Public Callback Prototypes                                                  */

/*                                                                               */
/*********************************************************************************/

/***************************** PRIVATE DEFINITIONS *******************************/
/*                                                                               */
/*-------------------------------------------------------------------------------*/


/*-------------------------------------------------------------------------------*/
/* - Private Macros                                                              */
/*
 * \brief 	The length of Network information data identifier,
 * */
#define VERINFO_NETWORKINFORMATION_LEN        ((uint8)4u)
/*
 * \brief 	The length of function dpecification data identifier,
 * */
#define VERINFO_FUNCTIONSPECIFICATION_LEN     ((uint8)4u)
/*
 * \brief 	The length of diagnostic definition data identifier,
 * */
#define VERINFO_DIAGNOSTICDEFINITION_LEN      ((uint8)4u)

/*
 * \brief 	The length of software version number,
 * */
#define VERINFO_SOFTWAREVERSIONNUMBER_LEN     ((uint8)8u)
/*
 * \brief 	The length of software number,
 * */
#define VERINFO_SOFTWARENUMBER_LEN            ((uint8)20u)
/*
 * \brief 	The length of ECU hardware version number,
 * */
#define VERINFO_ECUHARDWAREVERSIONNUMBER_LEN  ((uint8)9u)
/*
 * \brief 	The length of project id,
 * */
#define VERINFO_PROJECTID_LEN                 ((uint8)2u)
/*
 * \brief 	The length of ECU internal software number,
 * */
#define VERINFO_ECUINTERNALSWNUMBER_LEN       ((uint8)5u)
/*
 * \brief 	The length of Soc software number,
 * */
#define VERINFO_SOCSOFTWARENUMBER_LEN         ((uint8)20u)
/*-------------------------------------------------------------------------------*/
/* - Private Types                                                               */
typedef struct
{
    u16  uwAttemptDownloadingCounter;
    u16  uwFlashDriverActivatedSuccessfullyCounter;
    u16  uwAppDownloadedSuccessfullyCounter;
    u16  uwFblDownloadedSuccessfullyCounter;
}tSecureUpdatingLogInfo;

/*
 * \brief 	s_VerInfo_RelVars_t,
 *			The below struct include all important paramter store in ROM.
 *      MUST COMPLIANCE TO APPLICATION CONST TYPE!!!
 * */
typedef struct 
{
    uint8 a_NetworkInformationDataIdentifier[VERINFO_NETWORKINFORMATION_LEN];/*F120: Network information */ 
    uint8 a_FunctionSpecificationDataIdentifier[VERINFO_FUNCTIONSPECIFICATION_LEN]; /*F121: Function Specification version */
    uint8 a_DiagnosticDefinitionDataIdentifier[VERINFO_DIAGNOSTICDEFINITION_LEN]; /*F122: Diagnostic Definition version */
    uint8 a_ECUSoftwareVersionNumberDataIdentifier[VERINFO_SOFTWAREVERSIONNUMBER_LEN];/*F189: vehicle Manufacturer ECU Software Version Number Data Identifier */ 
    uint8 a_ECUHardwareVersionNumber[VERINFO_ECUHARDWAREVERSIONNUMBER_LEN];/*F191: vehicle Manufacturer ECU Hardware Number Data Identifier */
    uint8 a_ProjectID[VERINFO_PROJECTID_LEN];/*FD21: project ID */
    uint8 a_ECUInternalSoftwareVersionNumber[VERINFO_ECUINTERNALSWNUMBER_LEN];/*FD28: ECU Internal Software Version number */
	uint8 a_SocSoftwareNumberDataIdentifier[VERINFO_SOCSOFTWARENUMBER_LEN];/*FD29: Soc Software number */
}s_VerInfo_RelVars_t; 

 
/* - Private Constants                                                           */
 
static const u8 m_aubBootloaderSpecVersion[APP_BOOTLOADER_VERSION_SIZE] = {'V', '1','.','2','\0'};
static const u8 m_aubBootloaderVersion[APP_BOOTLOADER_VERSION_SIZE] = {'V', '1','.','2','\0'};
static const u8 m_aubFlashDriverVersion[APP_BOOTLOADER_VERSION_SIZE] = {'V', '1','.','2','\0'};
static const u8 m_aubFlashDriverPartNumber[APP_FLASH_DRIVER_PART_NUMBER_SIZE] = {'F', '6', '0', '0', '0', '9', '8', '1', '6', '0'};
static const u8 m_aubEcuPartNumber[APP_ECU_PART_NUMBER_SIZE] = {'F', '6', '0', '0', '0', '7', '0', '1', '6', '0', 0x00, 0x00, 0x00, 0x00};


#if !defined(RELEASE_VERSION)
volatile const u8 m_auReleaseVersion[16] =  {'D','E','B','U','G','\0','','','','','','','','','',''};
#else
volatile const u8 m_auReleaseVersion[16] =    {'R','E','L','E','A','S','E','\0','','','','','','','',''};
#endif 
 

static const s_VerInfo_RelVars_t *pstSharedMemory = APP_SHARED_MEMORY_ADDR;

/*-------------------------------------------------------------------------------*/
/* - Private Variables                                                           */



/*-------------------------------------------------------------------------------*/
/* - Private Function Prototypes                                                 */
static tAppBoolean APP_GetECUSoftwareVersion(u8 ubLocalSegmentId, u8 *pubVersion);
static tAppBoolean APP_ChangeToApplicationA(void);
static tAppBoolean APP_ChangeToApplicationB(void);
/*                                                                               */
/*********************************************************************************/

/******************************** IMPLEMENTATION *********************************/
/*                                                                               */

/*-------------------------------------------------------------------------------*/
/* - Public Functions                                                            */
 
/*-------------------------------------------------------------------------------*/
/* - Public Functions                                                            */

/*--------------------------{APP_Init}--------------------------------------*/
void APP_Init (void)
{
    LOG(LOG_LEVEL_INFO, "BootloaderVersion is %s,ReleaseVersion is %s",m_aubBootloaderVersion,m_auReleaseVersion);
}
/*--------------------------{end APP_Init}----------------------------------*/

/*--------------------------{APP_Manage}--------------------------------------*/
void APP_Manage (void)
{
}
/*--------------------------{end APP_Manage}----------------------------------*/

/*--------------------------{UDS_P2AboutToExpireInd}--------------------------------------*/
void UDS_P2AboutToExpireInd(void)
{
    LOG(LOG_LEVEL_INFO, "P2 about to expire");
}
/*--------------------------{end UDS_P2AboutToExpireInd}----------------------------------*/

/*--------------------------{APP_Dsc01Cbk}--------------------------------------*/
/* Deviation MISRA-1 */
 tUdsStatus APP_Dsc01Cbk(u16 *puwLen, u8 *aubUdsData)
 {
     OSC_PARAM_UNUSED(puwLen);
     OSC_PARAM_UNUSED(aubUdsData);

    /* Reset not performed */
    PROG_SetSecurityLevel (PROG_SEC_LEVEL_LOCK);

     return UDS_ACK;
 }
/*--------------------------{end APP_Dsc01Cbk}----------------------------------*/

/*--------------------------{APP_ReadBootloaderVersion}--------------------------------------*/
/* Deviation MISRA-1 */
tUdsStatus APP_ReadBootloaderVersion(u16 *puwLen, u8 *aubUdsData)
{
    TS_MemCpy(&aubUdsData[3U], m_aubBootloaderVersion, APP_BOOTLOADER_VERSION_SIZE);
    *puwLen = 3U + APP_BOOTLOADER_VERSION_SIZE;

    return UDS_ACK;
}
/*--------------------------{end APP_ReadBootloaderVersion}----------------------------------*/

/*--------------------------{APP_ReadFlashDriverPartNumber}--------------------------------------*/
/* Deviation MISRA-1 */
tUdsStatus APP_ReadFlashDriverPartNumber(u16 *puwLen, u8 *aubUdsData)
{
    TS_MemCpy(&aubUdsData[3U], m_aubFlashDriverPartNumber, APP_FLASH_DRIVER_PART_NUMBER_SIZE);
    *puwLen = 3U + APP_FLASH_DRIVER_PART_NUMBER_SIZE;

    return UDS_ACK;
}
/*--------------------------{end APP_ReadFlashDriverPartNumber}----------------------------------*/

/*--------------------------{APP_ReadSoftwareCheckCode}--------------------------------------*/
/* Deviation MISRA-1 */
tUdsStatus APP_ReadSoftwareCheckCode(u16 *puwLen, u8 *aubUdsData)
{
    *puwLen = 7U;
    OSC_PARAM_UNUSED(aubUdsData);

    return UDS_ACK;
}
/*--------------------------{end APP_ReadSoftwareCheckCode}----------------------------------*/

/*--------------------------{APP_ReadECUPartNumber}--------------------------------------*/
/* Deviation MISRA-1 */
tUdsStatus APP_ReadECUPartNumber(u16 *puwLen, u8 *aubUdsData)
{
    TS_MemCpy(&aubUdsData[3U], m_aubEcuPartNumber, APP_ECU_PART_NUMBER_SIZE);
    *puwLen = 3U + APP_ECU_PART_NUMBER_SIZE;

    return UDS_ACK;
}
/*--------------------------{end APP_ReadECUPartNumber}----------------------------------*/

u8 APP_GetApplicationRunningArea(void)
{
    u8 ubApplicationRunningArea;
    MemIf_JobResultType eMemIfResult;
    u8 ubIdx;
    u32 aulECUSoftwareAreaValue[APP_ECU_SOFTWARE_AREA_SIZE / 4U];

    ubApplicationRunningArea = APP_ECU_SOFTWARE_AREA_A;

    /* Read application running area form data flash */
    eMemIfResult = MemIf_ReadSync(
                    APP_ECU_SOFTWARE_AREA_ADDRESS,
                    (u8*)aulECUSoftwareAreaValue,
                    APP_ECU_SOFTWARE_AREA_SIZE);

    if (eMemIfResult == MEMIF_JOB_OK)
    {
        for (ubIdx = 0U; ubIdx < APP_ECU_SOFTWARE_AREA_SIZE / 4U; ubIdx++)
        {
            if(aulECUSoftwareAreaValue[ubIdx] != APP_SIG)
            {
                break;
            }
        }

        if (ubIdx == APP_ECU_SOFTWARE_AREA_SIZE / 4U)
        {
            ubApplicationRunningArea = APP_ECU_SOFTWARE_AREA_B;
        }
    }

    return ubApplicationRunningArea;
}

/*--------------------------{APP_ReadApplicationDownloadArea}--------------------------------------*/
/* Deviation MISRA-1 */
tUdsStatus APP_ReadApplicationDownloadArea(u16 *puwLen, u8 *aubUdsData)
{
    u8 ubApplicationRunningArea;

    /* Get application running area */
    ubApplicationRunningArea = APP_GetApplicationRunningArea();
    if(ubApplicationRunningArea == APP_ECU_SOFTWARE_AREA_A)
    {
        /* Application running area is A, download area B */
        aubUdsData[3U] = 'B';
    }
    else
    {
        /* Application running area is B, download area A */
        aubUdsData[3U] = 'A';
    }

    *puwLen = 4U;

    return UDS_ACK;
}
/*--------------------------{end APP_ReadApplicationDownloadArea}----------------------------------*/

/*--------------------------{APP_ReadSecureUpdatingLog}--------------------------------------*/
/* Deviation MISRA-1 */
tUdsStatus APP_ReadSecureUpdatingLog(u16 *puwLen, u8 *aubUdsData)
{
    tUdsStatus   eUdsStatus;
    MemIf_JobResultType eMemIfResult;
    tSecureUpdatingLogInfo eSecureUpdatingLogInfo;

    /* Read secure updating log form data flash */
    eMemIfResult = MemIf_ReadSync(APP_SECURE_UPDATING_LOG_ADDRESS,
                                  (u8*)&eSecureUpdatingLogInfo,
                                  APP_SECURE_UPDATING_LOG_SIZE);

    if (eMemIfResult == MEMIF_JOB_OK)
    {
        aubUdsData[3U] = (u8)(eSecureUpdatingLogInfo.uwAttemptDownloadingCounter >> 8U);
        aubUdsData[4U] = (u8)(eSecureUpdatingLogInfo.uwAttemptDownloadingCounter);
        aubUdsData[5U] = (u8)(eSecureUpdatingLogInfo.uwFlashDriverActivatedSuccessfullyCounter >> 8U);
        aubUdsData[6U] = (u8)(eSecureUpdatingLogInfo.uwFlashDriverActivatedSuccessfullyCounter);
        aubUdsData[7U] = (u8)(eSecureUpdatingLogInfo.uwAppDownloadedSuccessfullyCounter >> 8U);
        aubUdsData[8U] = (u8)(eSecureUpdatingLogInfo.uwAppDownloadedSuccessfullyCounter);
        aubUdsData[9U] = (u8)(eSecureUpdatingLogInfo.uwFblDownloadedSuccessfullyCounter >> 8U);
        aubUdsData[10U] = (u8)(eSecureUpdatingLogInfo.uwFblDownloadedSuccessfullyCounter);

        TS_MemSet(&aubUdsData[11U], 0x00U, 8U); 

        *puwLen = 19U;
        eUdsStatus = UDS_ACK;
    }
    else
    {
        /* error during reading */
        eUdsStatus = UDS_NRC_72;
    }

    return eUdsStatus;
}
/*--------------------------{end APP_ReadSecureUpdatingLog}----------------------------------*/

/*--------------------------{APP_ReadMcuABankError}--------------------------------------*/
/* Deviation MISRA-1 */
tUdsStatus APP_ReadMcuABankError(u16 *puwLen, u8 *aubUdsData)
{
    tUdsStatus   eUdsStatus;
    MemIf_JobResultType eMemIfResult;
    u8 ubIdx;
    u32 aulECUSecureBootError[APP_ECU_SECURE_BOOT_ERROR_SIZE / 4U];

    /* Read mcu A bank error form data flash */
    eMemIfResult = MemIf_ReadSync(
                    APP_ECU_SECURE_BOOT_ERROR_ADDRESS,
                    (u8*)aulECUSecureBootError,
                    APP_ECU_SECURE_BOOT_ERROR_SIZE);

    if (eMemIfResult == MEMIF_JOB_OK)
    {
        for (ubIdx = 0U; ubIdx < APP_ECU_SECURE_BOOT_ERROR_SIZE / 4U; ubIdx++)
        {
            if(aulECUSecureBootError[ubIdx] != APP_SIG)
            {
                break;
            }
        }

        if(ubIdx == APP_ECU_SECURE_BOOT_ERROR_SIZE / 4U)
        {
            /* Error flag is valid */
            aubUdsData[3U] = 0x01;
        }
        else
        {
            /* Error flag is invalid */
            aubUdsData[3U] = 0x00;
        }
        
        *puwLen = 4U;
        eUdsStatus = UDS_ACK;
    }
    else
    {
        /* error during reading */
        eUdsStatus = UDS_NRC_72;
    }

    return eUdsStatus;
}
/*--------------------------{end APP_ReadMcuABankError}----------------------------------*/

/*--------------------------{APP_ReadMcuBBankError}--------------------------------------*/
/* Deviation MISRA-1 */
tUdsStatus APP_ReadMcuBBankError(u16 *puwLen, u8 *aubUdsData)
{
    tUdsStatus   eUdsStatus;
    MemIf_JobResultType eMemIfResult;
    u8 ubIdx;
    u32 aulECUSecureBootError[APP_ECU_SECURE_BOOT_ERROR_SIZE / 4U];

    /* Read mcu B bank error form data flash */
    eMemIfResult = MemIf_ReadSync(
                    APP_ECU_SECURE_BOOT_ERROR_ADDRESS + APP_ECU_SECURE_BOOT_ERROR_SIZE,
                    (u8*)aulECUSecureBootError,
                    APP_ECU_SECURE_BOOT_ERROR_SIZE);

    if (eMemIfResult == MEMIF_JOB_OK)
    {
        for (ubIdx = 0U; ubIdx < APP_ECU_SECURE_BOOT_ERROR_SIZE / 4U; ubIdx++)
        {
            if(aulECUSecureBootError[ubIdx] != APP_SIG)
            {
                break;
            }
        }

        if(ubIdx == APP_ECU_SECURE_BOOT_ERROR_SIZE / 4U)
        {
            /* Error flag is valid */
            aubUdsData[3U] = 0x01;
        }
        else
        {
            /* Error flag is invalid */
            aubUdsData[3U] = 0x00;
        }
        
        *puwLen = 4U;
        eUdsStatus = UDS_ACK;
    }
    else
    {
        /* error during reading */
        eUdsStatus = UDS_NRC_72;
    }

    return eUdsStatus;
}
/*--------------------------{end APP_ReadMcuBBankError}----------------------------------*/

/*--------------------------{APP_CheckMemory}--------------------------------------*/
/* Deviation MISRA-1 */
tUdsStatus APP_CheckMemory(u16 *puwLen, u8 *aubUdsData)
{
    tUdsStatus eUdsStatus;
    tProgStatus eProgStatus;
    u8 ubIdx;
    u8 ubLocalSegmentId;
    u8 ubMemoryAddressLength;
    u32 ulStartAddress;
    u16 uwCrcValue;

    ubMemoryAddressLength = 4U;
    ulStartAddress = 0U;
    ubLocalSegmentId = 0U;

    /* Check if enough data are received */
    if ((u16)((u16)ubMemoryAddressLength + 4U) <= *puwLen)
    {
        /* Retrieve Address*/
        for (ubIdx = 0U; ubIdx < ubMemoryAddressLength; ubIdx++)
        {
            ulStartAddress |= (u32)((u32)(aubUdsData[ubIdx + 4U])
                    << (u8)(((ubMemoryAddressLength - 1U - ubIdx) * 8U)));
        }

        /* Check address*/
        if ((ulStartAddress >= m_stCurrentSegment.ulStartAddress) && (ulStartAddress < (m_stCurrentSegment.ulStartAddress + m_stCurrentSegment.ulSize)))
        {
            eProgStatus = PROG_GetSegmentByAddress(ulStartAddress, 0U, PROG_MEM_OPERATION_TYPE_READ, &ubLocalSegmentId);

            if (PROG_E_OK == eProgStatus)
            {
                if(stConfigSegment[ubLocalSegmentId].ePartitionType == PROG_FLASH_ROUTINES_PARTITION)
                {
                    PROG_GetCrcValue(&uwCrcValue);
                    *puwLen = 6U;
                    aubUdsData[4U] = (u8)((uwCrcValue >> 8U) & 0xFFU);
                    aubUdsData[5U] = (u8)( uwCrcValue        & 0xFFU);
                    eUdsStatus = PROG_CheckMemory(puwLen, aubUdsData);
                }
                else
                {
                    /* Set negative status */
                    eUdsStatus = UDS_NRC_31;
                }
            }
            else
            {
                /* Set negative status */
                eUdsStatus = UDS_NRC_31;
            }
        }
        else
        {
            /* Set negative status */
            eUdsStatus = UDS_NRC_31;
        }
    }
    else
    {
        /* Set negative status */
        eUdsStatus = UDS_NRC_13;
    }

    return eUdsStatus;
}
/*--------------------------{end APP_CheckMemory}----------------------------------*/

/*------------------------{Start APP_GetECUSoftwareVersion}------------------------*/
tAppBoolean APP_GetECUSoftwareVersion(u8 ubLocalSegmentId, u8 *pubVersion)
{
    tAppBoolean eStatus;
    tProgStatus  eProgStatus;
    u8 aubVersion[APP_ECU_SOFTWARE_VERSION_SIZE];

    eStatus = APP_FALSE;
    /* Check application status */
    eProgStatus = PROG_CheckFlashStatus(ubLocalSegmentId);
    if (eProgStatus == PROG_E_OK)
    {
        /* Application is vaild, read software version form application area */
        eProgStatus = PROG_MemDataAccess(PROG_MEM_TYPE_FLASH,
                                        PROG_MEM_OPERATION_TYPE_READ,
                                        (u32) (stConfigSegment[ubLocalSegmentId].ulStartAddress + APP_ECU_SOFTWARE_VERSION_OFFSET),
                                        APP_ECU_SOFTWARE_VERSION_SIZE,
                                        aubVersion);

        if (eProgStatus == PROG_E_OK)
        {
            if ((aubVersion[5U] >= '0') && (aubVersion[5U] <= '9') && (aubVersion[7U] >= '0') && (aubVersion[7U] <= '9'))
            {
                *pubVersion = ((aubVersion[5U] - '0') << 4U) | (aubVersion[7U] - '0');
                eStatus = APP_TRUE;
            }
        }
    }

    return eStatus;
}
/*--------------------------{end APP_GetECUSoftwareVersion}----------------------------------*/

/*--------------------------{APP_ExchangeApplicationRunningArea}-----------------------------*/
/* Deviation MISRA-1 */
tUdsStatus APP_ExchangeApplicationRunningArea(u16 *puwLen, u8 *aubUdsData)
{
    tUdsStatus eUdsStatus;
    tProgStatus eProgStatus;
    tAppBoolean eAppBoolean;
    u8 ubApplicationRunningArea;

    /* Get application running area */
    ubApplicationRunningArea = APP_GetApplicationRunningArea();
    if(ubApplicationRunningArea == APP_ECU_SOFTWARE_AREA_A)
    {
        /* Application running area is A, check application B status */
        eProgStatus = PROG_CheckFlashStatus(APP_ECU_SOFTWARE_AREA_B);
        if (eProgStatus == PROG_E_OK)
        {
            /* Application B is valid, change to application B */
            eAppBoolean = APP_ChangeToApplicationRunningArea(APP_ECU_SOFTWARE_AREA_B);
            if (eAppBoolean == APP_TRUE)
            {
                eUdsStatus = UDS_ACK;
            }
            else
            {
                /* Change failed, set negative status */
                eUdsStatus = UDS_NRC_72;
            }
        }
        else
        {
            /* Application B is not valid, set negative status */
            eUdsStatus = (tUdsStatus)0x02U;
        }
    }
    else
    {
        /* Application running area is B, check application A status */
        eProgStatus = PROG_CheckFlashStatus(APP_ECU_SOFTWARE_AREA_A);
        if (eProgStatus == PROG_E_OK)
        {
            /* Application A is valid, change to application A */
            eAppBoolean = APP_ChangeToApplicationRunningArea(APP_ECU_SOFTWARE_AREA_A);
            if (eAppBoolean == APP_TRUE)
            {
                eUdsStatus = UDS_ACK;
            }
            else
            {
                /* Change failed, set negative status */
                eUdsStatus = UDS_NRC_72;
            }
        }
        else
        {
            /* Application B is not valid, set negative status */
            eUdsStatus = (tUdsStatus)0x02U;
        }    
    }

    return eUdsStatus;
}
/*--------------------------{end APP_ExchangeApplicationRunningArea}----------------------------------*/

/*--------------------------{App_RollBackApplicationRunningArea}--------------------------------------*/
/* Deviation MISRA-1 */
tUdsStatus App_RollBackApplicationRunningArea(u16 *puwLen, u8 *aubUdsData)
{
    tUdsStatus eUdsStatus;
    tAppBoolean eResultA;
    tAppBoolean eResultB;
    u8 ubApplicationRunningArea;
    u8 ubVersionA;
    u8 ubVersionB;

    ubApplicationRunningArea = APP_GetApplicationRunningArea();
    eResultA = APP_GetECUSoftwareVersion(APP_ECU_SOFTWARE_AREA_A, &ubVersionA);
    eResultB = APP_GetECUSoftwareVersion(APP_ECU_SOFTWARE_AREA_B, &ubVersionB);

    if ((eResultA == APP_TRUE) && (eResultB == APP_TRUE))
    {
        if ((ubApplicationRunningArea == APP_ECU_SOFTWARE_AREA_A) && (ubVersionA > ubVersionB))
        {
            eResultB = APP_ChangeToApplicationRunningArea(APP_ECU_SOFTWARE_AREA_B);
            if (eResultB == APP_TRUE)
            {
                eUdsStatus = UDS_ACK;
            }
            else
            {
                eUdsStatus = UDS_NRC_72;
            }
        }
        else if((ubApplicationRunningArea == APP_ECU_SOFTWARE_AREA_B) && (ubVersionA < ubVersionB))
        {
            eResultA = APP_ChangeToApplicationRunningArea(APP_ECU_SOFTWARE_AREA_A);
            if (eResultA == APP_TRUE)
            {
                eUdsStatus = UDS_ACK;
            }
            else
            {
                eUdsStatus = UDS_NRC_72;
            }
        }
        else
        {
            eUdsStatus = (tUdsStatus)0x02U;
        }
    }
    else if ((eResultA == APP_TRUE) && (eResultB == APP_FALSE) && (ubApplicationRunningArea == APP_ECU_SOFTWARE_AREA_B))
    {
        eResultA = APP_ChangeToApplicationRunningArea(APP_ECU_SOFTWARE_AREA_A);
        if (eResultA == APP_TRUE)
        {
            eUdsStatus = UDS_ACK;
        }
        else
        {
            eUdsStatus = UDS_NRC_72;
        }
    }
    else if ((eResultA == APP_FALSE) && (eResultB == APP_TRUE) && (ubApplicationRunningArea == APP_ECU_SOFTWARE_AREA_A))
    {
        eResultB = APP_ChangeToApplicationRunningArea(APP_ECU_SOFTWARE_AREA_B);
        if (eResultB == APP_TRUE)
        {
            eUdsStatus = UDS_ACK;
        }
        else
        {
            eUdsStatus = UDS_NRC_72;
        }
    }
    else
    {
        eUdsStatus = (tUdsStatus)0x02U;
    }

    return eUdsStatus;
}
/*--------------------------{end App_RollBackApplicationRunningArea}----------------------------------*/


tAppBoolean APP_CheckFlashDriverCoherency(void)
{
    tAppBoolean eAppBoolean;
    u8 ubIdx;

    eAppBoolean = APP_TRUE;

    for (ubIdx = 0U; ubIdx < APP_BOOTLOADER_VERSION_SIZE; ubIdx++)
    {
        if(m_aubBootloaderVersion[ubIdx] != m_aubFlashDriverVersion[ubIdx])
        {
            eAppBoolean = APP_FALSE;
            break;
        }
    }

    return eAppBoolean;
}

/*--------------------------{APP_ReadBootloaderSpecVersion}--------------------------------------*/
/* Deviation MISRA-1 */
tUdsStatus APP_ReadBootloaderSpecVersion(u16 *puwLen, u8 *aubUdsData)//f171 fbl spec version
{
    /* Define pointer to length in callback */
    /* If nothing is implemented in callback, length returned is 0 and no response is sent */
    /* By default the callback length shall be 3 (service 1 and DID 2 ) */
    *puwLen = FBL_SPEC_VERSION_SIZE + 3;
    TS_MemCpy( &aubUdsData[3U],m_aubBootloaderSpecVersion,FBL_SPEC_VERSION_SIZE);
    return UDS_ACK;
}

/*--------------------------{APP_ReadSystemSupplier}--------------------------------------*/
/* Deviation MISRA-1 */
tUdsStatus APP_ReadSystemSupplier(u16 *puwLen, u8 *aubUdsData)//f18a static dflash
{
    /* Define pointer to length in callback */
    /* If nothing is implemented in callback, length returned is 0 and no response is sent */
    /* By default the callback length shall be 3 (service 1 and DID 2 ) */
    tUdsStatus eUdsStatus;
    MemIf_JobResultType eMemIfResult;

    /* Read secure updating log form data flash */
    eMemIfResult = MemIf_ReadSync(APP_PART_NUMBER_ADDRESS,//todo
                                  &aubUdsData[3U],
                                  APP_PART_NUMBER_SIZE);

    if (eMemIfResult == MEMIF_JOB_OK)
    {
        *puwLen = APP_PART_NUMBER_SIZE + 3;
        eUdsStatus = UDS_ACK;
    }
    else
    {
        /* error during reading */
        eUdsStatus = UDS_NRC_72;
    }
    return eUdsStatus;
}
/*--------------------------{end APP_ReadSystemSupplier}----------------------------------*/

/*--------------------------{APP_ReadECUHardwareVersion}--------------------------------------*/
/* Deviation MISRA-1 */
tUdsStatus APP_ReadECUHardwareVersion(u16 *puwLen, u8 *aubUdsData)//f089 static dflash
{
    /* Define pointer to length in callback */
    /* If nothing is implemented in callback, length returned is 0 and no response is sent */
    /* By default the callback length shall be 3 (service 1 and DID 2 ) */
    tUdsStatus eUdsStatus;
    MemIf_JobResultType eMemIfResult;

    /* Read secure updating log form data flash */
    eMemIfResult = MemIf_ReadSync(APP_HW_VERSION_ADDRESS,//todo
                                  &aubUdsData[3U],
                                  APP_HW_VERSION_SIZE);

    if (eMemIfResult == MEMIF_JOB_OK)
    {
        *puwLen = APP_HW_VERSION_SIZE + 3;
        eUdsStatus = UDS_ACK;
    }
    else
    {
        /* error during reading */
        eUdsStatus = UDS_NRC_72;
    }
    return eUdsStatus;
}
/*--------------------------{end APP_ReadECUHardwareVersion}----------------------------------*/

/*--------------------------{APP_ReadECUSoftwareVersion}--------------------------------------*/
/* Deviation MISRA-1 */
tUdsStatus APP_ReadECUSoftwareVersion(u16 *puwLen, u8 *aubUdsData)//f189 ROM
{
    /* Define pointer to length in callback */
    /* If nothing is implemented in callback, length returned is 0 and no response is sent */
    /* By default the callback length shall be 3 (service 1 and DID 2 ) */
    tUdsStatus   eUdsStatus;
    tProgStatus  eProgStatus;
    u8 ubApplicationRunningArea;
    u8 ubLocalSegmentId;

    /* Get application running area */
    ubApplicationRunningArea = APP_GetApplicationRunningArea();
    ubLocalSegmentId = ubApplicationRunningArea;

    /* Check application status */
    eProgStatus = PROG_CheckFlashStatus(ubLocalSegmentId);
    if (eProgStatus == PROG_E_OK)
    {
        /* Application is vaild, read ECU software version form application area */
        eProgStatus = PROG_MemDataAccess(PROG_MEM_TYPE_FLASH,
                                        PROG_MEM_OPERATION_TYPE_READ,
                                        (u32) (stConfigSegment[ubLocalSegmentId].ulStartAddress + APP_ECU_SOFTWARE_VERSION_OFFSET),
                                        APP_ECU_SOFTWARE_VERSION_SIZE,
                                        &aubUdsData[3U]);

        if (PROG_E_OK == eProgStatus)
        {
            *puwLen = 3U + APP_ECU_SOFTWARE_VERSION_SIZE;
            eUdsStatus = UDS_ACK;
        }
        else
        {
            /* error during reading */
            eUdsStatus = UDS_NRC_72;
        }
    }
    else
    {
        /* Application is not vaild, response default value */
        TS_MemSet(&aubUdsData[3U], 0xFFU, APP_ECU_SOFTWARE_VERSION_SIZE); 
        *puwLen = 3U + APP_ECU_SOFTWARE_VERSION_SIZE;    
        eUdsStatus = UDS_ACK;
    }

    return eUdsStatus;
}
/*--------------------------{end APP_ReadECUSoftwareVersion}----------------------------------*/

tAppBoolean APP_ChangeToApplicationRunningArea(u8 ubApplicationRunningArea)
{
    tAppBoolean eAppBoolean;

    if (ubApplicationRunningArea == APP_ECU_SOFTWARE_AREA_A)
    {
        /* Change to application A */
        eAppBoolean = APP_ChangeToApplicationA();
    }
    else
    {
        /* Change to application B */
        eAppBoolean = APP_ChangeToApplicationB();
    }

    return eAppBoolean;
}

tAppBoolean APP_ChangeToApplicationA(void)
{
    tAppBoolean eAppBoolean;
    MemIf_JobResultType eMemIfResult;

    eAppBoolean = APP_FALSE;

    /* Erase application running area flag form data flash */
    eMemIfResult = MemIf_EraseSync(
                    APP_ECU_SOFTWARE_AREA_ADDRESS,
                    APP_ECU_SOFTWARE_AREA_SIZE);

    if (eMemIfResult == MEMIF_JOB_OK)
    {
        eMemIfResult = MemIf_BlankCheckSync(
                APP_ECU_SOFTWARE_AREA_ADDRESS,
                APP_ECU_SOFTWARE_AREA_SIZE);

        if (eMemIfResult == MEMIF_JOB_OK)
        {
            eAppBoolean = APP_TRUE;
        }
    }

    return eAppBoolean;
}

tAppBoolean APP_ChangeToApplicationB(void)
{
    tAppBoolean eAppBoolean;
    MemIf_JobResultType eMemIfResult;
    u8 ubIdx;
    u32 aulECUSoftwareAreaValue[APP_ECU_SOFTWARE_AREA_SIZE / 4U];

    eAppBoolean = APP_FALSE;

    for (ubIdx = 0U; ubIdx < APP_ECU_SOFTWARE_AREA_SIZE / 4U; ubIdx++)
    {
        aulECUSoftwareAreaValue[ubIdx] = APP_SIG;
    }

    /* Check if application running area flag is blank */
    eMemIfResult = MemIf_BlankCheckSync(
            APP_ECU_SOFTWARE_AREA_ADDRESS,
            APP_ECU_SOFTWARE_AREA_SIZE);

    if (eMemIfResult != MEMIF_JOB_OK)
    {
        /* Application running area flag is not blank, erase the flag */
        eMemIfResult = MemIf_EraseSync(
                        APP_ECU_SOFTWARE_AREA_ADDRESS,
                        APP_ECU_SOFTWARE_AREA_SIZE);
        if (eMemIfResult == MEMIF_JOB_OK)
        {
            /* check if application running area flag is blank */
            eMemIfResult = MemIf_BlankCheckSync(
                    APP_ECU_SOFTWARE_AREA_ADDRESS,
                    APP_ECU_SOFTWARE_AREA_SIZE);
        }
    }

    if (eMemIfResult == MEMIF_JOB_OK)
    {
        /* Write application running area flag to data flash */
        eMemIfResult = MemIf_WriteSync(
                        APP_ECU_SOFTWARE_AREA_ADDRESS,
                        (u8*)aulECUSoftwareAreaValue,
                        APP_ECU_SOFTWARE_AREA_SIZE);
    }

    if (eMemIfResult == MEMIF_JOB_OK)
    {
        /* Verify application running area flag */
        eMemIfResult = MemIf_CompareSync(
                APP_ECU_SOFTWARE_AREA_ADDRESS,
                (u8*)aulECUSoftwareAreaValue,
                APP_ECU_SOFTWARE_AREA_SIZE);

        if (eMemIfResult == MEMIF_JOB_OK)
        {
            eAppBoolean = APP_TRUE;
        }
    }

    return eAppBoolean;
}

tAppBoolean APP_WriteSecureBootError(u8 ubApplicationRunningArea)
{
    tAppBoolean eAppBoolean;
    MemIf_JobResultType eMemIfResult;
    u8 ubIdx;
    u32 aulECUSecureBootError[APP_ECU_SECURE_BOOT_ERROR_SIZE / 4U];

    eAppBoolean = APP_FALSE;

    for (ubIdx = 0U; ubIdx < APP_ECU_SECURE_BOOT_ERROR_SIZE / 4U; ubIdx++)
    {
        aulECUSecureBootError[ubIdx] = APP_SIG;
    }

    /* Check secure boot error flag is writen */
    eMemIfResult = MemIf_CompareSync(
            APP_ECU_SECURE_BOOT_ERROR_ADDRESS + ubApplicationRunningArea * APP_ECU_SECURE_BOOT_ERROR_SIZE,
            (u8*)aulECUSecureBootError,
            APP_ECU_SECURE_BOOT_ERROR_SIZE);

    if (eMemIfResult == MEMIF_JOB_OK)
    {
        eAppBoolean = APP_TRUE;
    }
    else
    {
        /* Write secure boot error flag to data flash */
        eMemIfResult = MemIf_WriteSync(
                        APP_ECU_SECURE_BOOT_ERROR_ADDRESS + ubApplicationRunningArea * APP_ECU_SECURE_BOOT_ERROR_SIZE,
                        (u8*)aulECUSecureBootError,
                        APP_ECU_SECURE_BOOT_ERROR_SIZE);

        if (eMemIfResult == MEMIF_JOB_OK)
        {
            eAppBoolean = APP_TRUE;
        }
    }

    return eAppBoolean;
}

tAppBoolean APP_EraseSecureBootError(void)
{
    tAppBoolean eAppBoolean;
    MemIf_JobResultType eMemIfResult;

    eAppBoolean = APP_FALSE;

    /* Erase secure boot error flag form data flash */
    eMemIfResult = MemIf_EraseSync(
                    APP_ECU_SECURE_BOOT_ERROR_ADDRESS,
                    APP_ECU_SECURE_BOOT_ERROR_SIZE * 2U);

    if (eMemIfResult == MEMIF_JOB_OK)
    {
        /* Check secure boot error flag is erased */
        eMemIfResult = MemIf_BlankCheckSync(
                APP_ECU_SECURE_BOOT_ERROR_ADDRESS,
                APP_ECU_SECURE_BOOT_ERROR_SIZE * 2U);

        if (eMemIfResult == MEMIF_JOB_OK)
        {
            eAppBoolean = APP_TRUE;
        }
    }

    return eAppBoolean;
}

tAppBoolean APP_WriteSecureUpdatingLog(u8 ubLogType)
{
    tAppBoolean eAppBoolean;
    MemIf_JobResultType eMemIfResult;
    tSecureUpdatingLogInfo eSecureUpdatingLogInfo;
    eAppBoolean = APP_TRUE;

    /* Read secure updating log form data flash */
    eMemIfResult = MemIf_ReadSync(APP_SECURE_UPDATING_LOG_ADDRESS,
                                  (u8*)&eSecureUpdatingLogInfo,
                                  APP_SECURE_UPDATING_LOG_SIZE);

    if (eMemIfResult != MEMIF_JOB_OK)
    {
        eSecureUpdatingLogInfo.uwAttemptDownloadingCounter = 0U;
        eSecureUpdatingLogInfo.uwFlashDriverActivatedSuccessfullyCounter = 0U;
        eSecureUpdatingLogInfo.uwAppDownloadedSuccessfullyCounter = 0U;
        eSecureUpdatingLogInfo.uwFblDownloadedSuccessfullyCounter = 0U;
    }

    switch (ubLogType)
    {
        case ATTEMPT_DOWNLOADING_COUNTER:
            /* Update attempt downloading counter */
            eSecureUpdatingLogInfo.uwAttemptDownloadingCounter ++;
            break;

        case FLASH_DRIVER_ACTIVATED_SUCCESSFULLY_COUNTER:
            /* Update flash driver activated successfully counter */
            eSecureUpdatingLogInfo.uwFlashDriverActivatedSuccessfullyCounter ++;
            break;

        case APP_DOWNLOADED_SUCCESSFULLY_COUNTER:
            /* Update app downloaded successfully counter */
            eSecureUpdatingLogInfo.uwAppDownloadedSuccessfullyCounter ++;
            break;

        case FBL_DOWNLOADED_SUCCESSFULLY_COUNTER:
            /* Update fbl downloaded successfully counter */
            eSecureUpdatingLogInfo.uwFblDownloadedSuccessfullyCounter ++;
            break;

        default :
            /* Invalid case */
            eAppBoolean = APP_FALSE;
            break;
    }

    if (eAppBoolean == APP_TRUE)
    {
        /* Erase old secure updating log form data flash */
        eMemIfResult = MemIf_EraseSync(
                        APP_SECURE_UPDATING_LOG_ADDRESS,
                        APP_SECURE_UPDATING_LOG_SIZE);

        if (eMemIfResult != MEMIF_JOB_OK)
        {
            eAppBoolean = APP_FALSE;
        }
    }

    if (eAppBoolean == APP_TRUE)
    {
        /* Check old secure updating log is erased */
        eMemIfResult = MemIf_BlankCheckSync(
                APP_SECURE_UPDATING_LOG_ADDRESS,
                APP_SECURE_UPDATING_LOG_SIZE);

        if (eMemIfResult != MEMIF_JOB_OK)
        {
            eAppBoolean = APP_FALSE;
        }
    }

    if (eAppBoolean == APP_TRUE)
    {
        /* Write new secure updating log to data flash */
        eMemIfResult = MemIf_WriteSync(
                        APP_SECURE_UPDATING_LOG_ADDRESS,
                        (u8*)&eSecureUpdatingLogInfo,
                        APP_SECURE_UPDATING_LOG_SIZE);

        if (eMemIfResult != MEMIF_JOB_OK)
        {
            eAppBoolean = APP_FALSE;
        }
    }

    return eAppBoolean;
}

/*--------------------------{APP_UdsSessionStatusInd}--------------------------------------*/
void APP_UdsSessionStatusInd (tUdsSessionType eUdsNewSessType,tUdsSessionType eUdsOldSessType,tUdsChangeReason eUdsChangingCause)
{
    LOG(LOG_LEVEL_INFO, "change session from %d to %d as %d", eUdsOldSessType, eUdsNewSessType, eUdsChangingCause);

    if(eUdsOldSessType == UDS_SESSION_EXTENDED_DIAG)
    {
        PROG_CloseExtendedSession(eUdsChangingCause);
    }
}
/*--------------------------{end APP_UdsSessionStatusInd}----------------------------------*/

/*--------------------------{APP_TpTxConf}--------------------------------------*/
void APP_TpTxConf (tTpMsgIdx uMsgIdx, u8 ebStatus)
{
    OSC_PARAM_UNUSED(uMsgIdx);
    OSC_PARAM_UNUSED(ebStatus);
}
/*--------------------------{end APP_TpTxConf}----------------------------------*/

/*--------------------------{APP_TpRxInd}--------------------------------------*/
void APP_TpRxInd (tTpMsgIdx uMsgIdx, u8 ebStatus)
{
    OSC_PARAM_UNUSED(uMsgIdx);
    OSC_PARAM_UNUSED(ebStatus);
}
/*--------------------------{end APP_TpRxInd}----------------------------------*/

