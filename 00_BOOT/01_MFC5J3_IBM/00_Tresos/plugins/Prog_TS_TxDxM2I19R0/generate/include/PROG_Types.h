/*********************************************************************************/
/*                                                                               */
/*                                BOOT Layers                                    */
/*                                                                               */
/* ------------------------------------------------------------------------------*/
/*                                                                               */
/*                                 PROG configuration                            */
/*                                                                               */
/*********************************************************************************/
/*%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%                                        */
/*%%   _____________________________   %%  \file PROG_Types.h                    */
/*%%  |                             |  %%  \brief PROG layer include plugin file */
/*%%  |   &&&&&   &&&&&             |  %%  Module version: 2.19.0 BL-3.X              */
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


[!AUTOSPACING!]
#ifndef PROG_TYPES_H
#define PROG_TYPES_H

#include <Std_Types.h>          /* AUTOSAR standard types */
[!IF "as:modconf('ProgJLR')/General/PROG_JLR_VARIANT='SBL_WITH_EB_FRAMEWORK'"!]
#include "fblFrameworkPublicApi.h"
[!ENDIF!]

[!VAR "SEGMENT_MAX"="num:dectoint(count(Segments/*))"!]
[!VAR "NBR_PROT_CAL"="0"!]
[!FOR "SEGMENT_IDX" = "1" TO "$SEGMENT_MAX"!]
[!IF "'PROG_PROT_CALIBRATION_PARTITION' = as:modconf('Prog')/Segments/*[number($SEGMENT_IDX)]/Partition_Type"!]
    [!VAR "NBR_PROT_CAL" = "num:dectoint($NBR_PROT_CAL) + 1"!]
[!ENDIF!]
[!ENDFOR!]


[!VAR "MIN_VAL_TO_WRITE_FOR_FLASH" = "0"!]
[!VAR "MIN_VAL_TO_WRITE_FOR_FLASH_EXT" = "0"!]
[!VAR "MIN_VAL_TO_WRITE_FOR_RAM" = "0"!]
[!VAR "MIN_VAL_TO_WRITE_FOR_CUSTOM_MEM" = "0"!]
[!VAR "MIN_VAL_TO_WRITE_FOR_ALL_MEMORIES" = "num:dectoint("0")"!]
[!LOOP "Segments/*"!]
    [!VAR "Memory_Type" = "node:ref(Memory)/Memory_Type"!]
    [!IF "$Memory_Type = 'FLASH'"!]
        [!VAR "MEMORY_MODE_FLASH" = "node:ref(Memory)/Memory_Mode"!]
        [!VAR "MIN_VAL_TO_WRITE_FOR_FLASH"="node:ref(Memory)/Min_Value_To_Write"!]
        [!IF "$MIN_VAL_TO_WRITE_FOR_FLASH > $MIN_VAL_TO_WRITE_FOR_ALL_MEMORIES"!]
            [!VAR "MIN_VAL_TO_WRITE_FOR_ALL_MEMORIES" = "$MIN_VAL_TO_WRITE_FOR_FLASH"!]
        [!ENDIF!]
    [!ELSEIF "$Memory_Type = 'FLASH_EXT'"!]
        [!VAR "MEMORY_MODE_FLASH_EXT" = "node:ref(Memory)/Memory_Mode"!]
        [!VAR "MIN_VAL_TO_WRITE_FOR_FLASH_EXT"="node:ref(Memory)/Min_Value_To_Write"!]
        [!IF "$MIN_VAL_TO_WRITE_FOR_FLASH_EXT > $MIN_VAL_TO_WRITE_FOR_ALL_MEMORIES"!]
            [!VAR "MIN_VAL_TO_WRITE_FOR_ALL_MEMORIES" = "$MIN_VAL_TO_WRITE_FOR_FLASH_EXT"!]
        [!ENDIF!]
    [!ELSEIF "$Memory_Type = 'RAM'"!]
        [!VAR "MEMORY_MODE_RAM" = "node:ref(Memory)/Memory_Mode"!]
        [!VAR "MIN_VAL_TO_WRITE_FOR_RAM"="node:ref(Memory)/Min_Value_To_Write"!]
        [!IF "$MIN_VAL_TO_WRITE_FOR_RAM > $MIN_VAL_TO_WRITE_FOR_ALL_MEMORIES"!]
            [!VAR "MIN_VAL_TO_WRITE_FOR_ALL_MEMORIES" = "$MIN_VAL_TO_WRITE_FOR_RAM"!]
        [!ENDIF!]
    [!ELSEIF "$Memory_Type = 'CUSTOM'"!]
        [!VAR "MEMORY_MODE_CUSTOM_MEM" = "node:ref(Memory)/Memory_Mode"!]
        [!VAR "MIN_VAL_TO_WRITE_FOR_CUSTOM_MEM"="node:ref(Memory)/Min_Value_To_Write"!]
        [!IF "$MIN_VAL_TO_WRITE_FOR_CUSTOM_MEM > $MIN_VAL_TO_WRITE_FOR_ALL_MEMORIES"!]
            [!VAR "MIN_VAL_TO_WRITE_FOR_ALL_MEMORIES" = "$MIN_VAL_TO_WRITE_FOR_CUSTOM_MEM"!]
        [!ENDIF!]
    [!ENDIF!]
[!ENDLOOP!]
#define PROG_MIN_VAL_TO_WRITE            [!"$MIN_VAL_TO_WRITE_FOR_ALL_MEMORIES"!]U

/* PROG boolean type */
#define PROG_FALSE                       0U
#define PROG_TRUE                        1U
typedef u8 tProgBoolean;

typedef u8 tProgStatus;
#define PROG_E_OK                        0x00U
#define PROG_E_NOT_OK                    0x01U
#define PROG_E_BUSY                      0x02U
#define PROG_E_CHECK_FAILED              0x03U
#define PROG_E_BYPASS                    0x04U

[!IF "node:exists(as:modconf('ProgVAG'))"!]
#define PROG_E_RFS_DRIVER_FAIL           0x05U
#define PROG_E_RFS_VERSION_FAIL          0x06U
[!ENDIF!]

typedef u8 tProgResCause;
#define PROG_RESET_CAUSE_ER              0x00U
#define PROG_RESET_CAUSE_DSC01           0x01U
#define PROG_RESET_CAUSE_DSC02           0x02U
#define PROG_RESET_CAUSE_S3_TIMEOUT      0x03U
typedef u8  tProgMemType;
#define PROG_MEM_TYPE_INIT               0xFFU
#define PROG_MEM_TYPE_FLASH              0x00U
#define PROG_MEM_TYPE_EEPROM             0x01U
#define PROG_MEM_TYPE_RAM                0x02U
#define PROG_MEM_TYPE_SCRATCHPAD         0x03U
#define PROG_MEM_TYPE_FLASH_EXT          0x04U
#define PROG_MEM_TYPE_CUSTOM             0x05U
typedef u8  tProgMemIdx;
typedef u8  tProgMemMode;
#define PROG_MEMORY_SYNCHRONOUS          0x01U
#define PROG_MEMORY_ASYNCHRONOUS         0x02U
#define PROG_MEMORY_NOTUSED              0x03U

typedef u8 tProgAccessType;
#define PROG_MEM_ACCESS_TYPE_NONE        0x00U
#define PROG_MEM_ACCESS_TYPE_READ        0x01U
#define PROG_MEM_ACCESS_TYPE_WRITE       0x02U
#define PROG_MEM_ACCESS_TYPE_READ_WRITE  0x03U

typedef u32 tDataLength;
/* basic data is byte */

typedef u8 tDataBufferType;

typedef u32 tProgAddressType;

typedef u8 tOperationType;
#define PROG_MEM_OPERATION_TYPE_ERASE    0x01U
#define PROG_MEM_OPERATION_TYPE_WRITE    0x02U
#define PROG_MEM_OPERATION_TYPE_READ     0x03U

typedef u8 tProgCompTimeoutStatus;
#define PROG_COMPLETECOMPATIBLE_START    0x01U
#define PROG_COMPLETECOMPATIBLE_END      0x02U
#define PROG_COMPLETECOMPATIBLE_ERROR    0x03U

typedef u8 tProgPartitionType;
#define PROG_APPLICATION_PARTITION       0x01U
#define PROG_CALIBRATION_PARTITION       0x02U
#define PROG_PROT_CALIBRATION_PARTITION  0x03U
#define PROG_SBA_PARTITION               0x04U
#define PROG_BOOTLOADER_PARTITION        0x05U
#define PROG_FLASH_ROUTINES_PARTITION    0x06U
#define PROG_ESS_PARTITION               0x07U
#define PROG_HSM_PARTITION               0x08U

typedef u8 tProgDownloadType;
#define PROG_DOWNLOAD_BY_ADDR            0x01U
#define PROG_DOWNLOAD_BY_LOGICAL_BLOCK   0x02U
#define PROG_DOWNLOAD_BY_LOGICAL_BLOCK_SEGMENT   0x03U

/* Size of the maximum length of the answer to Check Memory request */
/* between the Implementation 40,50 and 60 */
#define PROG_MAX_LENGTH_CHECKMEMORY_ANSWER 6U


[!IF "node:exists(as:modconf('ProgGM'))"!]
[!IF "GM/PEC_Enable = 'true'"!]
typedef u16 tProgPECError;
#define PROG_PEC_NO_ERROR                 0x0000U
#define PROG_ERR_PARTITION_ID             0x0001U
#define PROG_ERR_SW_NOT_PRESENT           0x0002U
#define PROG_ERR_REVOKE_SW                0x0003U
#define PROG_ERR_ERASE_SW                 0x0004U
#define PROG_ERR_GET_APP_INFO             0x0005U
#define PROG_ERR_REVOKE_CAL               0x0006U
#define PROG_ERR_ERASE_CAL                0x0007U
#define PROG_ERR_GET_CAL_INFO             0x0008U
#define PROG_ERR_UPDATE_PSI               0x0009U
#define PROG_ERR_DATA_TYPE                0x000AU
#define PROG_ERR_COMPRESSION              0x000BU
#define PROG_ERR_LENGTH_EXCEEDED          0x000CU
#define PROG_ERR_MORE_DATA_EXPECTED       0x000DU
#define PROG_ERR_FLASH_WRITE              0x000EU
#define PROG_ERR_MODULE_ID                0x000FU
#define PROG_ERR_BCID                     0x0010U
#define PROG_ERR_CCID                     0x0011U
#define PROG_ERR_ECU_NAME                 0x0012U
#define PROG_ERR_ECU_ID                   0x0013U
#define PROG_ERR_SW_REGION                0x0014U
#define PROG_ERR_SIGNATURE                0x0015U
#define PROG_ERR_APP_NBID                 0x0016U
#define PROG_ERR_SUBJECT_NAME             0x0017U
#define PROG_ERR_KEY_NBID                 0x0018U
#define PROG_ERR_CERT                     0x0019U
#define PROG_ERR_CAL_REGION               0x001AU
#define PROG_ERR_MD                       0x001BU
#define PROG_ERR_ROOT_SIGNATURE           0x001CU
#define PROG_ERR_MSG_OUT_OF_SEQUENCE      0x001DU
#define PROG_ERR_UNDEFINED                0x0020U
#define PROG_ERR_PROTECTEDCAL_NOT_DEFINED 0x0035U
#define PROG_ERR_PER_DATA_TX_NOT_ALLOW    0x0037U

[!ENDIF!]

typedef u8 tProgSigBypass;
#define PROG_ERR_SBA_ECU_NAME            0x01U
#define PROG_ERR_SBA_ECU_ID              0x02U
#define PROG_ERR_SBA_SIGNATURE           0x04U
#define PROG_ERR_SBA_CERT                0x08U
#define PROG_SBA_OK                      0x80U

typedef u8 tProgPsiValue;
#define PROG_PSI_PROGRAMMED              0x00U
#define PROG_PSI_REVOKED                 0x01U
#define PROG_PSI_INVALID                 0x02U

#define PROG_ECU_ID_SIZE                 16U
#define PROG_ECU_NAME_SIZE               8U
#define PROG_SUBJECT_NAME_SIZE           16U
#define PROG_BOOT_NB_MODULE_SIZE         1U
#define PROG_BOOT_MODULE_ID_SIZE         1U
#define PROG_BOOT_PART_NUMBER_SIZE       4U
#define PROG_BOOT_DLS_SIZE               2U
#define PROG_BOOT_PROT_CALIB_NUMBER_SIZE        1U
#define PROG_BOOT_PROT_CALIB_PARTITION_ID_SIZE  1U
#define PROG_BOOT_MAX_PROT_PARTITIONS           [!"num:dectoint($NBR_PROT_CAL)"!]U
#define PROG_BOOT_PRIMARY_MICRO_ID       0x47U
#define PROG_BOOT_NUMBER_OF_MODULES      0x01U
#define PROG_MAX_PARTITION               [!"num:dectoint(GM/MAX_PARTITION)"!]U
#define PROG_MAX_REGION_ALLOWED          [!"num:dectoint(GM/MAX_REGION_ALLOWED)"!]U
[!ENDIF!]

[!IF "as:modconf('ProgVCC')/General/PROG_VCC_VARIANT='PBL' or as:modconf('ProgVCC')/General/PROG_VCC_VARIANT='SBL'
    or as:modconf('ProgJLR')/General/PROG_JLR_VARIANT='PBL' or as:modconf('ProgJLR')/General/PROG_JLR_VARIANT='SBL'"!]
typedef struct s_secondary_bootloader_interface
{
    u32 software_version;          /* meta data */
    u8  referenceString[16];       /* reference string of the SBL */
    void *ptr_function[25];        /* function pointer list */
    u32 ulSBLValidityFlagAddr;     /* SBL validity flag address */
}t_secondary_bootloader_interface;
#define PROG_DIGEST_LENGTH     32U    /* digest length for VCC */
 typedef struct
 {
    u32 ulStartAddress;          /* start address of the hashed data */
    u32 ulLength;       /* length of the hashed data */
    u8  aubDigest[PROG_DIGEST_LENGTH];        /* function pointer list */
 }tDataBlockType;
[!ENDIF!]

typedef u32 tProgCompleteStatus;
[!IF "as:modconf('ProgVCC')/General/PROG_VCC_VARIANT='PBL'
    or as:modconf('ProgJLR')/General/PROG_JLR_VARIANT='PBL_WITH_EB_FRAMEWORK'
    or as:modconf('ProgJLR')/General/PROG_JLR_VARIANT='PBL'"!]
    [!IF "node:exists(as:modconf('EB')) and (as:modconf('EB')/Communication/EnableMultipleTpConnection='true')"!]
typedef void (*ptSBL_StartUp_Code)(u32 ulInfoSBL, u8 ubRxPduId);
    [!ELSE!]
typedef void (*ptSBL_StartUp_Code)(u32 ulInfoSBL);
    [!ENDIF!]
typedef void (*ptAPPL_START_ADDR)(void);
[!ENDIF!]
typedef tProgCompleteStatus (*ptCompleteCompatibleCallOut)(void);

[!IF "as:modconf('ProgJLR')/General/PROG_JLR_VARIANT='PBL_WITH_EB_FRAMEWORK' or as:modconf('ProgJLR')/General/PROG_JLR_VARIANT='SBL_WITH_EB_FRAMEWORK'"!]
/* Function pointer type definition for ZF framework */
typedef u8 (*tpulVerifySectionCrc)(void);
typedef u8 (*tpulinvalidateSection)(u32);
typedef u8 (*tpulisValidApplication)(void);
typedef void* (*tpulGetAddress)(u8,u32);
[!IF "as:modconf('ProgJLR')/General/PROG_JLR_VARIANT='SBL_WITH_EB_FRAMEWORK'"!]
/* Function pointer for skipPage Api */
typedef u8 (*tpulskipPage)(u32*);
[!ENDIF!]
[!ENDIF!]

/* Type of algorithm used for programming verification */
typedef u8 tProgVerifAlgo;
#define PROG_VERIFY_CRC         0x00U
#define PROG_VERIFY_SIGNATURE   0x01U
#define PROG_VERIFY_HASH        0x02U

typedef struct
{
    u32 ulAdd; /*Address to read data*/
    u32 ulCnt; /*Number of data get to compute CRC */
[!IF "node:exists(as:modconf('ProgVAG')) or node:exists(as:modconf('ProgDAG')) or OemInd/Checksum_Algo='CRC32 Ethernet' or OemInd/Checksum_Algo='CRC32 InternationalStandard'"!]
    u32 ulVal; /* CRC32 value */
[!ELSE!]
    u16 uwVal; /* CRC16 value */
[!ENDIF!]
    tProgVerifAlgo ubAlgo;
[!IF "(node:exists(as:modconf('ProgFCA')) and as:modconf('ProgFCA')/General/PROG_FCA_VARIANT='Atlantis_High') or node:exists(as:modconf('ProgVAG')) or node:exists(as:modconf('ProgDAG'))  or node:exists(as:modconf('ProgVCC')) or (node:exists(as:modconf('ProgOEMInd')) and OemInd/Erase_Mode = 'LogicalBlock') or (node:exists(as:modconf('ProgOEMInd')) and OemInd/Erase_Mode = 'All')"!]
    u8  ubLogicalBlockId;
[!ENDIF!]
}tProgVerificationInfo;

[!IF "node:exists(as:modconf('ProgGM'))"!]
typedef struct
{
    u32 ulAddress;
    u32 ulSize;
}tRegiontype;
[!ENDIF!]

typedef struct
{
    u32  ulStartAddress;   /*Start address of the segment*/
    u32  ulSize;           /*Size of the segment */
[!IF "node:exists(as:modconf('ProgGM'))"!]
    tRegiontype astRegion[PROG_MAX_REGION_ALLOWED];
    u8   *pubRegionPtr;    /*Pointer to the current region*/
    u16  uwModuleId;       /* Current downloaded module ID */
    u8   ubRegionNbr;
[!ENDIF!]
[!IF "(node:exists(as:modconf('ProgFCA')) and as:modconf('ProgFCA')/General/PROG_FCA_VARIANT='Atlantis_High')
 or node:exists(as:modconf('ProgVAG')) or node:exists(as:modconf('ProgDAG')) or node:exists(as:modconf('ProgVCC'))
    or (node:exists(as:modconf('ProgOEMInd')) and OemInd/Erase_Mode = 'All')
    or (node:exists(as:modconf('ProgOEMInd')) and OemInd/Erase_Mode = 'LogicalBlock')"!]
    u8  ubLogicalSegmentId;    /*Identifier for the logical segment*/
    u8  ubLogicalBlockId;      /*Identifier for the logical block*/
[!ENDIF!]
    u8   ubSegmentId;      /*Identifier of the segment in segment configuration array */
    u8   ubSegmentNbr;     /*Remaining number of segment in the current block*/
}tSegmentType;

[!VAR "MEMORY_MAX"="num:dectoint(count(Memory/*))"!]
#define PROG_MEMORY_NB [!"$MEMORY_MAX"!]U
[!IF "node:exists(as:modconf('ProgVAG')) or node:exists(as:modconf('ProgVCC')) or node:exists(as:modconf('ProgDAG')) or node:exists(as:modconf('ProgOEMInd'))"!]


#define PROG_SEGMENT_NB [!"$SEGMENT_MAX"!]U
#define PROG_MAX_RD_PER_BLOCK   [!"num:dectoint(DownloadVerification/MaxNumberOfRDPerBlock)"!]U
typedef struct
{
    u8 ubSegNbr;
    tSegmentType astSeg[PROG_MAX_RD_PER_BLOCK];
    u8 ubSegListCrcIndex;
}tSegmentListType;
[!ENDIF!]

typedef struct
{
    tProgAddressType         ulStartAddress;
    tProgAddressType         ulEndAddress;
    tProgAddressType         ulEraseStartAddress;
    tProgAddressType         ulEraseEndAddress;
    tProgMemIdx              ubMemoryIdx;
    tProgAccessType          eSegAccessType;
[!IF "node:exists(as:modconf('ProgGM')) or node:exists(as:modconf('ProgFCA')) or node:exists(as:modconf('ProgVAG')) or node:exists(as:modconf('ProgDAG')) or node:exists(as:modconf('ProgOEMInd')) or node:exists(as:modconf('ProgVCC'))"!]
    tProgPartitionType       ePartitionType;
[!ENDIF!]
[!IF "node:exists(as:modconf('ProgOEMInd'))"!]
    tProgBoolean            eValidityCheck;
[!ENDIF!]
[!IF "node:exists(as:modconf('ProgVAG')) or node:exists(as:modconf('ProgDAG')) or node:exists(as:modconf('ProgVCC')) or (node:exists(as:modconf('ProgFCA')) and as:modconf('ProgFCA')/General/PROG_FCA_VARIANT='Atlantis_High') or (node:exists(as:modconf('ProgOEMInd')) and as:modconf('Prog')/OemInd/Erase_Mode != 'Address')"!]
    u8                       ubBlockIndex;
[!ENDIF!]
}tCfgSegmentType;

typedef struct
{
    tProgMemType             eMemoryType;
    tProgMemMode             eMemoryMode;
    u32                      ulMinValueToWrite;
    tProgAddressType         ulAddressOffset;
    u8                       ubEraseValue;
}tCfgMemorytType;

typedef struct
{
    u16 uwBlockIdentifier;
    u8 ubFirstSegmentId;
    u8 ubSegmentNbr;
    u16 uwProgCntrMax;
}tProg_Block;

[!IF "(not((as:modconf('BM')/Security/SecureBoot/SECURE_AUTHENTICATED_BOOT = 'OFF') and (as:modconf('Prog')/Security/Secure_Checksum_computation = 'false'))) and
    (node:exists(as:modconf('ProgDAG')) or (node:exists(as:modconf('ProgFCA')) and as:modconf('ProgFCA')/General/PROG_FCA_VARIANT='Atlantis_High'))"!]
typedef struct
{
    u32 ulStartAddressForSecureBoot;
    u32 ulLengthForSecureBoot;
    u16 uwBlockIdentifier;
    u8  ubBlockVerifiedInSecure;
    u8  ubBlockBlockerExecution;
}tProg_BlockSecureBootInfo;
[!ENDIF!]

typedef struct
{
    u8 * pubData;    /* Pointer to Tp buffer use for reception*/
    u8 * pubTxData;  /* Pointer to Tp buffer use for transmission*/
    u16 uwLength;    /* Length of request/response */
    u8 ubDiagStatus; /* Status of the request management */
}tDiagMessageInfo;

typedef struct
{
    u8 aubData[PROG_MAX_LENGTH_CHECKMEMORY_ANSWER];    /* Contains data of the answer */
    u16 uwLength;    /* Length of request/response */
    u8 ubDiagStatus; /* Status of the request management */
}tFirstCheckMemoryAnswerInfo;

typedef struct
{
    u32 ulMemorySizeExpected;
    u32 ulReceivedSizeOfData; /* Number of data received and written */
[!IF "General/Enable_Compression = 'true'"!]
    u32 ulTotalDecompDataWrite;
[!ENDIF!]
[!IF "node:exists(as:modconf('ProgGM'))"!]
    u16 uwExpectedModuleId[PROG_MAX_PARTITION];
[!ENDIF!]
    u8 ubBlockSequenceCounter;
    u8 ubRDReceived;
[!IF "General/Enable_Compression = 'true'"!]
    u8 ubCompRequired;
[!ENDIF!]
}tReprogInfo;

[!IF "as:modconf('BlPduR')/General/MultipleRxBuffer = 'true'"!]
typedef struct
{
    u32 ulBufferedSizeOfData;
    u8 eResponsePending;
    u8 eBufferProcessing;
}tMultipleBuffReprogInfo;
[!ENDIF!]

typedef struct
{
[!IF "General/Enable_Compression = 'true'"!]
    u8 * pubDecompData; /*Pointer to buffer in COMP containing data to write*/
[!ENDIF!]
    u32 ulAddressToWrite;
    u32 ulDataToBeWritten; /* Total number of data received */
    u32 ulWrittenData; /* Total number of data written */
    u32 ulWriteLength; /* Number of data written at last write */
[!IF "General/Enable_Compression = 'true'"!]
    u32 ulInDecompDataLength;
[!ENDIF!]
    u8 ubTDReceived;
}tWriteInfo;


typedef struct
{
    u32 ulStartAddress;
    u32 ulMemorySize;
    u16 uwBlockIdentifier;
    u8  ubSegmentId;
    u8  ubDataFormatId;
}tRDParam;

typedef P2FUNC (void*, EBSTUBS_APPL_CODE, t_PROG_fctptr)(void) ;

typedef struct
{
    u8 aubData[PROG_MIN_VAL_TO_WRITE];
    u16 uwOldDataLength;
    u16 uwNewDataLength;
}tPageBuffer;

[!VAR "SEGMENT_MAX"="num:dectoint(count(Segments/*))"!]
[!VAR "SEGMENT_IDX"="1"!]
[!VAR "PROT_CALIB_IDX"="1"!]
[!IF "node:exists(as:modconf('ProgGM'))"!]
typedef struct
{
    u16 uwBCID;
[!IF "GM/EcuId_Source = 'Tresos_Configuration'"!]
    u8  aubEcuId[PROG_ECU_ID_SIZE];
[!ENDIF!]
    u8  aubEcuName[PROG_ECU_NAME_SIZE];
    u8  aubSubjectName[PROG_SUBJECT_NAME_SIZE];
    u8  aubBootPartNumber[PROG_BOOT_PART_NUMBER_SIZE];
    u8  aubBootDLS[PROG_BOOT_DLS_SIZE];
    u8  aubProtectedCalibNumber;
[!IF "$NBR_PROT_CAL > 0"!]
    u8  aubProtectedCalibPartitionID[PROG_BOOT_MAX_PROT_PARTITIONS];
[!ENDIF!]
}tBootInfoBlock;

typedef struct
{
    u8 ubBootIntegrity;
    tProgSigBypass ubSignatureBypass;
}tBootStatus;
[!ENDIF!]

typedef u8 tProgEraseCheckType;
#define PROG_DISABLED_ERASE_CHECK        0x00U
#define PROG_1ST_PROGRAMMING_ERASE_CHECK 0x01U
#define PROG_BLOCK_ERASE_CHECK           0x02U


typedef u8 tProgEraseStatus;
#define PROG_E_NOT_ERASED        0x00U
#define PROG_E_ERASED            0x01U



typedef struct
{
    u8 ubAppFingerprintWriten; /*Application Fingerprint writing success flag*/
    u8 ubCalFingerprintWriten; /*Calibration Fingerprint writing success flag*/
}tWfSuccess;

typedef u8 tProgCohChkResult;
#define PROG_E_COHCHK_CORRECT             0x00U
#define PROG_E_COHCHK_INCORRECT           0x01U
#define PROG_E_COHCHK_INCORRECT_SW_HW     0x02U
#define PROG_E_COHCHK_INCORRECT_SW_SW     0x03U
#define PROG_E_COHCHK_INCORRECT_OTHER     0x04U

[!IF "node:exists(as:modconf('Uds'))"!]
[!VAR "COHERENCY_PRE_CHECK_USE" = "0"!]
    [!LOOP " as:modconf('Uds')/Routine_Control/*"!]
        [!IF "Callback = 'PROG_CoherencyPreCheck'"!]
            [!VAR "COHERENCY_PRE_CHECK_USE" = "1"!]
        [!ENDIF!]
    [!ENDLOOP!]
    [!IF "$COHERENCY_PRE_CHECK_USE = 1"!]
typedef u8 tProgCohPreChkResult;
#define PROG_E_COHPRECHK_CORRECT          0x00U
#define PROG_E_COHPRECHK_INTERNAL_ERROR   0x01U
#define PROG_E_COHPRECHK_INCORRECT_HW_SW  0x02U
#define PROG_E_COHPRECHK_INCORRECT_SW_SW  0x03U
    [!ENDIF!]
[!ENDIF!]

[!IF "as:modconf('BlPduR')/General/MultipleRxBuffer = 'true'"!]
typedef struct
{
    u16 Length;    /* Length of request */
    u8 * Data;    /* Pointer to Tp buffer use for reception*/
    u8 Event;  /* Stored event */
}tEventInfo;
[!ENDIF!]

#endif /* PROG_TYPES_H */
