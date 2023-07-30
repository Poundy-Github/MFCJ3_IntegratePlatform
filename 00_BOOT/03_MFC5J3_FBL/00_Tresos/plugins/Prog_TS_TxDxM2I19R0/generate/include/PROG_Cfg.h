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
/*%%   _____________________________   %%  \file PROG_Cfg.h                      */
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
#ifndef PROG_CFG_H
#define PROG_CFG_H

/* to support ASR 4.3 CSM-Demo wrapper for the BL */
[!IF "node:exists(as:modconf('Csm'))"!]
    [!IF "(as:modconf('Prog')/General/Use_CSM_ASR430_DemoWrapper='true')"!]
#include "demo_csmwrapper.h"
#define PROG_CSM_WRAPPER_43_USED              STD_ON
    [!ELSE!]
#define PROG_CSM_WRAPPER_43_USED              STD_OFF
    [!ENDIF!]
[!ELSE!]
#define PROG_CSM_WRAPPER_43_USED              STD_OFF
[!ENDIF!]

[!VAR "MEMORY_MAX"="num:dectoint(count(Memory/*))"!]
[!VAR "SEGMENT_MAX"="num:dectoint(count(Segments/*))"!]

#define PROG_IMPL_0                                     0U
#define PROG_IMPL_1                                     1U
#define PROG_IMPL_2                                     2U
#define PROG_IMPL_3                                     3U
#define PROG_IMPL_4                                     4U
#define PROG_IMPL_10                                    10U
#define PROG_IMPL_11                                    11U
#define PROG_IMPL_20                                    20U
#define PROG_IMPL_30                                    30U
#define PROG_IMPL_31                                    31U
#define PROG_IMPL_40                                    40U
#define PROG_IMPL_50                                    50U
#define PROG_IMPL_60                                    60U



#define PROG_MSG_BYTE_INDEX(x)                          (u8) (x - PROG_RESPONSE_PARAMETERS_OFFSET)


/* Feature default configuration */
#define PROG_ERASE_ALFI                                 STD_OFF

/* Default compression algo value */
#define PROG_DFI_COMPRESSED_VAL                         [!"(num:inttohex(General/Compression_Algorithm))"!]0U

/* Verification variant define */

#define PROG_VERIFICATION_CRC                           0U
#define PROG_VERIFICATION_SIGNATURE_WITH_HASH           1U
#define PROG_VERIFICATION_SIGNATURE                     2U
#define PROG_VERIFICATION_SIGNATURE_AND_CRC             3U
#define PROG_VERIFICATION_SIGNATURE_WITH_HASH_AND_CRC   4U
#define PROG_VERIFICATION_HASH                          5U


[!IF "node:exists(as:modconf('ProgJLR'))"!]
#include "PROG_Cfg_Impl0.h"
[!ELSEIF "node:exists(as:modconf('ProgVCC'))"!]
#include "PROG_Cfg_Impl10.h"
[!ELSEIF "node:exists(as:modconf('ProgGM'))"!]
#include "PROG_Cfg_Impl20.h"
[!ELSEIF "node:exists(as:modconf('ProgFCA'))"!]
#include "PROG_Cfg_Impl30.h"
[!ELSEIF "node:exists(as:modconf('ProgVAG'))"!]
#include "PROG_Cfg_Impl40.h"
[!ELSEIF "node:exists(as:modconf('ProgDAG'))"!]
#include "PROG_Cfg_Impl50.h"
[!ELSEIF "node:exists(as:modconf('ProgOEMInd'))"!]
#include "PROG_Responses.h"
#include "PROG_Cfg_Impl60.h"
[!ELSE!]
[!ERROR "no ProgOem module has been found in the project."!]
[!ENDIF!] [!/* IF "node:exists(as:modconf('ProgJLR')) */!]

[!IF "node:exists(as:modconf('ProgFCA'))"!]
    [!IF "(as:modconf('Prog')/General/NO_SECURITYLEVEL_RESET_ON_SESSIONCHANGE='true')"!]
#define PROG_NORESET_SECURITYLEVEL        STD_ON
    [!ELSE!]
#define PROG_NORESET_SECURITYLEVEL        STD_OFF
    [!ENDIF!]
[!ELSE!]
#define PROG_NORESET_SECURITYLEVEL        STD_OFF
[!ENDIF!]

[!VAR "MEMORY_MAX"="num:dectoint(count(Memory/*))"!]
[!IF "(node:exists(as:modconf('Cal')) and as:modconf('Prog')/General/Enable_Compression='true')"!]
#define PROG_CALDECOMPRESS_CFGID                        [!"name(as:ref(as:modconf('Prog')/General/ProgCalReferences/ProgCalDecompressConfigId))"!]
[!ENDIF!]


[!VAR "SEGMENT_MAX"="num:dectoint(count(Segments/*))"!]


#define PROG_SEC_LEVEL_LOCK                             0U

#define PROG_CRC16_INIT_VAL                             0xFFFFU
#define PROG_CRC32_INIT_VAL                             0xFFFFFFFFU

#define PROG_CRC_CALC_SIZE                              0x20U

/* max block length for TransferData */
#define PROG_MAX_BYTE_IN_TD                             [!"num:dectoint(General/Max_Bytes_in_TD)"!]U


#define PROG_HSM_UPDATE_ENABLE                         [!WS "25"!][!IF "Segments/*/Partition_Type = 'PROG_HSM_PARTITION'"!]STD_ON[!ELSE!]STD_OFF[!ENDIF!][!CR!]

[!IF "(as:modconf('Prog')/Segments/*/Partition_Type='PROG_HSM_PARTITION')"!]
/*HSM Partition ID if the HSM programming is enabled*/
#define PROG_HSM_PARTITION_ID                           [!"(num:dectoint(Segments/*/HSM_PartitionID))"!]U
#define PROG_HSM_BUFFER_LENGTH                          [!"(num:dectoint(Segments/*/HSM_RAM_Buffer))"!]U
#define PROG_HSM_TIMEOUT                                [!"(num:dectoint(Segments/*/PROG_HSM_Timeout))"!]U
[!ENDIF!]

/* ISO 14 229 : */
/* This parameter is used by the requestDownload positive response message to */
/* inform the client how many data bytes (maxNumberOfBlockLength) shall be */
/* included in each TransferData request message from the client. This length */
/* reflects the complete message length, including the service identifier and */
/* the data parameters present in the TransferData request message. This */
/* parameter allows the client to adapt to the receive buffer size of the server */
/* before it starts transferring data to the server. */
#define PROG_SIZE_OF_NB_BLOCK_LEN                       0x20U


#define PROG_MAX_WRITE_SIZE                             0x20U

/* Polynomial for the CRC calculation */
#define PROG_CRC_TAB_SIZE                               256U

#define PROG_FLASH_CONTEXT_OK                           0x01U
#define PROG_FLASH_CONTEXT_NOT_OK                       0x00U

#define PROG_UDS_SESSION_DEFAULT                        UDS_SESSION_DEFAULT
#define PROG_UDS_SESSION_PROGRAMMING                    UDS_SESSION_PROGRAMMING

/* UDS Session parameter record */
#define PROG_UDS_SPREC                                  UDS_SPREC

/* ISO 14229 : The blockSequenceCounter parameter value starts at 01 hex with    */
/* the first TransferData request that follows the RequestDownload (34 hex) or   */
/* RequestUpload (35 hex) service. Its value is incremented by 1 for each        */
/* subsequent TransferData request. At the value of FF hex the                   */
/* blockSequenceCounter rolls over and starts at 00 hex with the next            */
/* TransferData request message.*/
#define PROG_BLOCK_SEQU_REINIT                          0x00U
#define PROG_BLOCK_SEQU_INIT                            0x01U
#define PROG_BLOCK_SEQU_MAX                             0xFFU

#define PROG_ERASE_BY_ADDR                              0x01U
#define PROG_ERASE_BY_BLOCK_ID                          0x02U
#define PROG_ERASE_BY_DYNAMIC_PARTITION_ID              0x03U

/* Define if the sleep management type */
#define PROG_SLEEP_MANAGEMENT_OFF                       0U
#define PROG_SLEEP_MANAGEMENT_TIMEOUT                   1U
#define PROG_SLEEP_MANAGEMENT_IO                        2U

/* PROG_CRC_CALCULATION values */
#define PROG_NO_CRC                                     0x00U
#define PROG_TD_CRC16                                   0x01U
#define PROG_TD_CRC32                                   0x02U
#define PROG_TD_CRC_CUST                                0x03U
#define PROG_CRC32_LENGTH                               0x04U
#define PROG_PARTIAL_SW_ROUTINE_CRC_LEN                 0x0BU

/* PROG_CRC_ALGO values */
#define PROG_CRC32_ETHERNET                             0x00U
#define PROG_CRC32_INT_STD                              0x01U
#define PROG_CRC16                                      0x02U

#define PROG_MANAGE_PERIOD                              [!"num:dectoint(General/MANAGE_PERIOD)"!]U

#define PROG_TUNABLE_PARAMETERS_DEACTIVATED             0x00U
#define PROG_TUNABLE_PARAMETERS_ACTIVATED               0x01U
#define PROG_TUNABLE_PARAMETERS                         [!WS "25"!][!IF "General/Tunable_Parameters = 'true'"!]PROG_TUNABLE_PARAMETERS_ACTIVATED[!ELSE!]PROG_TUNABLE_PARAMETERS_DEACTIVATED[!ENDIF!][!CR!]



[!IF "node:exists(as:modconf('SA'))"!]
#define PROG_SA_SEED_LEN                                ([!"num:dectoint(as:modconf('SA')/General/Security_Access_Seed_Length)"!]U)
#define PROG_SA_KEY_LEN                                 ([!"num:dectoint(as:modconf('SA')/General/Security_Access_Key_Length)"!]U)
#define PROG_USE_SA_WITH_CRYPTO                         [!WS "25"!][!IF "(as:modconf('SA')/General/Seed_Type = 'Cryptographic_Random') or (as:modconf('SA')/General/Seed_Type = 'Cryptographic_PUN') or (as:modconf('SA')/General/Compare_Key_Type = 'Verify_Signature')"!]STD_ON[!ELSE!]STD_OFF[!ENDIF!]
[!ELSE!]
#define PROG_SA_SEED_LEN                                ([!"GM/Security_Access_Seed_Length"!]U)
#define PROG_USE_SA_WITH_CRYPTO                         STD_OFF
[!ENDIF!]

[!VAR "SERVICE_IDX" = "0"!]
[!VAR "DSC_02_DENIED_IN_DEF_SESSION" = "0"!]
[!VAR "DSC_02_PROTECTED_BY_SA" = "0"!]
[!FOR "SERVICE_IDX" = "1" TO "num:dectoint(count(as:modconf('Uds')/Service/*))"!]
    [!IF "as:modconf('Uds')/Service/*[number($SERVICE_IDX)]/Service = 'DSC' and as:modconf('Uds')/Service/*[number($SERVICE_IDX)]/SubService = '2' and as:modconf('Uds')/Service/*[number($SERVICE_IDX)]/Default = 'false'"!]
        [!VAR "DSC_02_DENIED_IN_DEF_SESSION" = "1"!]
    [!ENDIF!]
    [!IF "as:modconf('Uds')/Service/*[number($SERVICE_IDX)]/Service = 'DSC' and as:modconf('Uds')/Service/*[number($SERVICE_IDX)]/SubService = '2' and as:modconf('Uds')/Service/*[number($SERVICE_IDX)]/SecurityLevel != '0'"!]
        [!VAR "DSC_02_PROTECTED_BY_SA" = "1"!]
#define PROG_SEC_LEVEL_PROGRAMMINGSESSION               [!"num:dectoint(as:modconf('Uds')/Service/*[number($SERVICE_IDX)]/SecurityLevel)"!]U
    [!ENDIF!]
[!ENDFOR!]
[!IF "$DSC_02_DENIED_IN_DEF_SESSION = 1"!]
#define PROG_DSC02_DENIED_IN_DEF_SESSION                STD_ON
[!ELSE!]
#define PROG_DSC02_DENIED_IN_DEF_SESSION                STD_OFF
[!ENDIF!]
[!IF "$DSC_02_PROTECTED_BY_SA = 1"!]
#define PROG_DSC_02_PROTECTED_BY_SA                     STD_ON
[!ELSE!]
#define PROG_DSC_02_PROTECTED_BY_SA                     STD_OFF
[!ENDIF!]

#define PROG_DECRYPTION_ENABLE                          [!WS "26"!][!IF "Decryption/Enable_Decryption = 'true'"!]STD_ON[!ELSE!]STD_OFF[!ENDIF!][!CR!]

#define PROG_COMPRESSION_ENABLE                         [!WS "25"!][!IF "General/Enable_Compression = 'true'"!]STD_ON[!ELSE!]STD_OFF[!ENDIF!][!CR!]
#define PROG_DECOMP_SLICING_ENABLE                      [!WS "22"!][!IF "General/Enable_Compression = 'true' and General/Enable_Decompression_Slicing = 'true'"!]STD_ON[!ELSE!]STD_OFF[!ENDIF!][!CR!]
[!IF "General/Enable_Compression = 'true' and General/Enable_Decompression_Slicing = 'true'"!]
#define PROG_DECOMP_SLICE_SIZE                          [!"num:dectoint(General/Decomp_Slice_size)"!]U
[!ENDIF!]
[!IF "General/Enable_Compression = 'true'"!]
#define PROG_COMPRESSED_DATA_SIZE                       0x01U
#define PROG_DECOMPRESSED_DATA_SIZE                     0x02U
#define PROG_RD_DATA_SIZE_TYPE                          [!WS "26"!][!IF "General/Data_Size_In_RD = 'compressed'"!]PROG_COMPRESSED_DATA_SIZE[!ELSE!]PROG_DECOMPRESSED_DATA_SIZE[!ENDIF!][!CR!]
[!ENDIF!]

#define PROG_BLPDUR_SUPPORT_ENABLE                      [!WS "22"!][!IF "node:exists(as:modconf('BlPduR'))"!]STD_ON[!ELSE!]STD_OFF[!ENDIF!][!CR!]

#define PROG_MEMORY_NB                                  [!"$MEMORY_MAX"!]U
#define PROG_SEGMENT_NB                                 [!"$SEGMENT_MAX"!]U

/* Define if the auto-control is used or not */
#define PROG_AUTOCONTROL_ENABLE                         [!WS "25"!][!IF "General/Auto_Control = 'true'"!]STD_ON[!ELSE!]STD_OFF[!ENDIF!][!CR!]

/* Define if NRC78 shall be sent before starting erasing */
#define PROG_NRC78_ON_ERASE_ENABLE                      [!WS "22"!][!IF "General/Transmit_Nrc78_On_Erase = 'true'"!]STD_ON[!ELSE!]STD_OFF[!ENDIF!][!CR!]

/* Define if an NRC78 response shall be systematically sent receiving the Erase request */
#define PROG_NRC78_BEFORE_ERASECHECK                    [!WS "20"!][!IF "General/Transmit_Nrc78_Before_EraseCheck = 'true'"!]STD_ON[!ELSE!]STD_OFF[!ENDIF!][!CR!]

/* Define if Preliminary Erasing is activated or not */
#define PROG_PRELIM_ERASING_ENABLE                      [!WS "22"!][!IF "General/PreliminaryErasing = 'true'"!]STD_ON[!ELSE!]STD_OFF[!ENDIF!][!CR!]

/* Define if software shall check if memory is already erased before doing an erase */
[!IF "General/Erase_Check = 'First Programming Check'"!]
#define PROG_ERASE_CHECK_TYPE                           [!WS "27"!]PROG_1ST_PROGRAMMING_ERASE_CHECK[!CR!]
[!ELSE!]
    [!IF "General/Erase_Check = 'Memory Block Erased Check'"!]
#define PROG_ERASE_CHECK_TYPE                           [!WS "27"!]PROG_BLOCK_ERASE_CHECK[!CR!]
    [!ELSE!]
#define PROG_ERASE_CHECK_TYPE                           [!WS "27"!]PROG_DISABLED_ERASE_CHECK[!CR!]
    [!ENDIF!]
[!ENDIF!]

/* Define number of sector to erase before sending NRC78 */
#define PROG_NB_OF_SECTOR_TO_ERASE_BEFORE_SENDING_NRC78 [!"num:dectoint(as:modconf('Prog')/General/Number_Of_Sector_To_Erase_Before_Sending_NRC78)"!]U

/* Enable and disable erasing by sector */
[!VAR "SLICED_ERASING_FOR_NRC78_SENDING" = "1"!]
[!IF "as:modconf('Prog')/General/Number_Of_Sector_To_Erase_Before_Sending_NRC78 = '0'"!]
    [!VAR "SLICED_ERASING_FOR_NRC78_SENDING" = "0"!]
[!ENDIF!]

[!IF "$SLICED_ERASING_FOR_NRC78_SENDING = 0"!]
#define PROG_SLICED_ERASING_FOR_NRC78_SENDING STD_OFF
[!ELSE!]
#define PROG_SLICED_ERASING_FOR_NRC78_SENDING STD_ON
[!ENDIF!]

/* Define if response shall be sent before resetting software */
#define PROG_RESPOND_BEFORE_RESET                       [!WS "23"!][!IF "General/Transmit_Response_Before_Reset = 'true'"!]STD_ON[!ELSE!]STD_OFF[!ENDIF!][!CR!]

/* Define if reset is required while switching from default to default session */
#define PROG_RESET_AFTER_DSC01_IN_DEFAULT_SESSION       [!WS "7"!][!IF "General/ResetAfterDsc01InDefaultSession = 'true'"!]STD_ON[!ELSE!]STD_OFF[!ENDIF!][!CR!]

[!IF "node:exists(as:modconf('EB')) and (as:modconf('EB')/Communication/EnableMultipleTpConnection='true')"!]
#define PROG_MULTIPLE_TP_CONNECTIONS_ENABLE             STD_ON
[!ELSE!]
#define PROG_MULTIPLE_TP_CONNECTIONS_ENABLE             STD_OFF
[!ENDIF!]

[!VAR "ERASE_MEMORY_USE" = "0"!]
[!VAR "ACTIVE_SBL_USE" = "0"!]
[!VAR "CHECK_PROG_DEP_USE" = "0"!]
[!VAR "AUTO_CONTROL_USE" = "0"!]
[!VAR "COHERENCY_PRE_CHECK_USE" = "0"!]
[!VAR "ACTIVE_CURRENT_SESSION_USE" = "0"!]
[!VAR "CURRENT_DIAG_APP_USE" = "0"!]
[!VAR "GET_PSI_USE" = "0"!]
[!VAR "GET_BOOT_STATUS_USE" = "0"!]
[!VAR "GET_PEC_USE" = "0"!]
[!VAR "GET_ECU_ID_USE" = "0"!]
[!VAR "GET_ECU_ADDR_USE" = "0"!]
[!VAR "GET_ECU_NAME_USE" = "0"!]
[!VAR "GET_SBA_TICKET_USE" = "0"!]
[!VAR "GET_BOOT_INFO_USE" = "0"!]
[!VAR "FINGERPRINT_USE" = "0"!]
[!IF "node:exists(as:modconf('Uds'))"!]
    [!/* Check if service are configured */!]
    [!LOOP " as:modconf('Uds')/Service/*"!]
    [!ENDLOOP!]
    [!/* Check if service DID are configured */!]
    [!LOOP " as:modconf('Uds')/Service_DID/*"!]
        [!IF "Callback = 'PROG_GetActiveCurrentSession'"!]
            [!VAR "ACTIVE_CURRENT_SESSION_USE" = "1"!]
        [!ENDIF!]
        [!IF "Callback = 'PROG_GetCurrentDiagApp'"!]
            [!VAR "CURRENT_DIAG_APP_USE" = "1"!]
        [!ENDIF!]
        [!IF "Callback = 'PROG_GetPSIValues'"!]
            [!VAR "GET_PSI_USE" = "1"!]
        [!ENDIF!]
        [!IF "Callback = 'PROG_GetBootStatus'"!]
            [!VAR "GET_BOOT_STATUS_USE" = "1"!]
        [!ENDIF!]
        [!IF "Callback = 'PROG_GetPEC'"!]
            [!VAR "GET_PEC_USE" = "1"!]
        [!ENDIF!]
        [!IF "Callback = 'PROG_GetEcuID'"!]
            [!VAR "GET_ECU_ID_USE" = "1"!]
        [!ENDIF!]
        [!IF "Callback = 'PROG_GetEcuAddr'"!]
            [!VAR "GET_ECU_ADDR_USE" = "1"!]
        [!ENDIF!]
        [!IF "Callback = 'PROG_GetEcuName'"!]
            [!VAR "GET_ECU_NAME_USE" = "1"!]
        [!ENDIF!]
        [!IF "Callback = 'PROG_GetSbaTicket'"!]
            [!VAR "GET_SBA_TICKET_USE" = "1"!]
        [!ENDIF!]
        [!IF "Callback = 'PROG_WriteFingerprint'"!]
            [!VAR "FINGERPRINT_USE" = "1"!]
        [!ENDIF!]
        [!IF "Callback = 'PROG_GetBootInfo'"!]
            [!VAR "GET_BOOT_INFO_USE" = "1"!]
        [!ENDIF!]
    [!ENDLOOP!]
    [!/* Check if Routine controle are configured */!]
    [!LOOP " as:modconf('Uds')/Routine_Control/*"!]
        [!IF "Callback = 'PROG_EraseMemory'"!]
            [!VAR "ERASE_MEMORY_USE" = "1"!]
        [!ENDIF!]
        [!IF "Callback = 'PROG_ActiveSBL'"!]
            [!VAR "ACTIVE_SBL_USE" = "1"!]
        [!ENDIF!]
        [!IF "Callback = 'PROG_CheckProgrammingDependencies'"!]
            [!VAR "CHECK_PROG_DEP_USE" = "1"!]
        [!ENDIF!]
        [!IF "Callback = 'PROG_AutoControl'"!]
            [!VAR "AUTO_CONTROL_USE" = "1"!]
        [!ENDIF!]
        [!IF "Callback = 'PROG_CoherencyPreCheck'"!]
            [!VAR "COHERENCY_PRE_CHECK_USE" = "1"!]
        [!ENDIF!]
    [!ENDLOOP!]
[!/* SERVICE DID */!]
    [!IF "$ACTIVE_CURRENT_SESSION_USE = 1"!]
#define PROG_ACTIVE_CURRENT_SESSION_REQUEST_ENABLE              STD_ON
    [!ELSE!]
#define PROG_ACTIVE_CURRENT_SESSION_REQUEST_ENABLE              STD_OFF
    [!ENDIF!]
    [!IF "$CURRENT_DIAG_APP_USE = 1"!]
#define PROG_CURRENT_DIAG_APPLICATION_REQUEST_ENABLE            STD_ON
    [!ELSE!]
#define PROG_CURRENT_DIAG_APPLICATION_REQUEST_ENABLE            STD_OFF
    [!ENDIF!]
    [!IF "$GET_PSI_USE = 1"!]
#define PROG_GET_PSI_REQUEST_ENABLE                             STD_ON
    [!ELSE!]
#define PROG_GET_PSI_REQUEST_ENABLE                             STD_OFF
    [!ENDIF!]
    [!IF "$GET_BOOT_STATUS_USE = 1"!]
#define PROG_GET_BOOT_STATUS_REQUEST_ENABLE                     STD_ON
    [!ELSE!]
#define PROG_GET_BOOT_STATUS_REQUEST_ENABLE                     STD_OFF
    [!ENDIF!]
    [!IF "$GET_PEC_USE = 1"!]
#define PROG_GET_PEC_REQUEST_ENABLE                             STD_ON
    [!ELSE!]
#define PROG_GET_PEC_REQUEST_ENABLE                             STD_OFF
    [!ENDIF!]
    [!IF "$GET_ECU_ID_USE = 1"!]
#define PROG_GET_ECU_ID_REQUEST_ENABLE                          STD_ON
    [!ELSE!]
#define PROG_GET_ECU_ID_REQUEST_ENABLE                          STD_OFF
    [!ENDIF!]
    [!IF "$GET_ECU_ADDR_USE = 1"!]
#define PROG_GET_ECU_ADDR_REQUEST_ENABLE                        STD_ON
    [!ELSE!]
#define PROG_GET_ECU_ADDR_REQUEST_ENABLE                        STD_OFF
    [!ENDIF!]
    [!IF "$GET_ECU_NAME_USE = 1"!]
#define PROG_GET_ECU_NAME_REQUEST_ENABLE                        STD_ON
    [!ELSE!]
#define PROG_GET_ECU_NAME_REQUEST_ENABLE                        STD_OFF
    [!ENDIF!]
    [!IF "$GET_SBA_TICKET_USE = 1"!]
#define PROG_GET_SBA_TICKET_REQUEST_ENABLE                      STD_ON
    [!ELSE!]
#define PROG_GET_SBA_TICKET_REQUEST_ENABLE                      STD_OFF
    [!ENDIF!]
    [!IF "$FINGERPRINT_USE = 1"!]
#define PROG_WRITE_FINGERPRINT_ENABLE                           STD_ON
    [!ELSE!]
#define PROG_WRITE_FINGERPRINT_ENABLE                           STD_OFF
    [!ENDIF!]
    [!IF "$GET_BOOT_INFO_USE = 1"!]
#define PROG_GET_BOOT_INFO_REQUEST_ENABLE                       STD_ON
    [!ELSE!]
#define PROG_GET_BOOT_INFO_REQUEST_ENABLE                       STD_OFF
    [!ENDIF!]
[!/* END SERVICE DID */!]

[!/* ROUTINE CONTROLE */!]
    [!IF "$ERASE_MEMORY_USE = 1"!]
#define PROG_ERASE_MEMORY_REQUEST_ENABLE                        STD_ON
    [!ELSE!]
#define PROG_ERASE_MEMORY_REQUEST_ENABLE                        STD_OFF
    [!ENDIF!]
    [!IF "$ACTIVE_SBL_USE = 1"!]
#define PROG_ACTIVE_SBL_REQUEST_ENABLE                          STD_ON
    [!ELSE!]
#define PROG_ACTIVE_SBL_REQUEST_ENABLE                          STD_OFF
    [!ENDIF!]
    [!IF "$CHECK_PROG_DEP_USE = 1"!]
#define PROG_CHECK_PROGRAMMING_DEPENDENCIES_REQUEST_ENABLE      STD_ON
    [!ELSE!]
#define PROG_CHECK_PROGRAMMING_DEPENDENCIES_REQUEST_ENABLE      STD_OFF
    [!ENDIF!]
    [!IF "$AUTO_CONTROL_USE = 1"!]
#define PROG_AUTO_CONTROL_REQUEST_ENABLE                        STD_ON
    [!ELSE!]
#define PROG_AUTO_CONTROL_REQUEST_ENABLE                        STD_OFF
    [!ENDIF!]
    [!IF "$COHERENCY_PRE_CHECK_USE = 1"!]
#define PROG_COHERENCY_PRE_CHECK_ENABLE                         STD_ON
    [!ELSE!]
#define PROG_COHERENCY_PRE_CHECK_ENABLE                         STD_OFF
    [!ENDIF!]
[!/*END ROUTINE CONTROLE */!]
[!ENDIF!]

[!VAR "FLASH_USE" = "0"!]
[!VAR "FLASH_ACCESS" = "0"!]
[!VAR "FLASH_EXT_USE" = "0"!]
[!VAR "FLASH_EXT_ACCESS" = "0"!]
[!VAR "RAM_USE" = "0"!]
[!VAR "RAM_ACCESS" = "0"!]
[!VAR "CUSTOM_MEMORY_USE" = "0"!]
[!VAR "CUSTOM_MEMORY_ACCESS" = "0"!]
[!VAR "FLASH_ROUTINES_INRAM_USED" = "0"!]
[!LOOP "Segments/*"!]
    [!VAR "Memory_Type" = "node:ref(Memory)/Memory_Type"!]
    [!IF "as:modconf('Prog')/DownloadFlashRoutines/Download_Flash_Routines='true'"!]
        [!VAR "Partition_Type" = "./Partition_Type"!]
    [!ENDIF!]
    [!IF "$Memory_Type = 'FLASH'"!]
        [!VAR "FLASH_USE" = "1"!]
        [!VAR "MEMORY_MODE_FLASH" = "node:ref(Memory)/Memory_Mode"!]
        [!VAR "MEMORY_ADDRESS_OFFSET_FLASH"="node:ref(Memory)/Addr_Offset"!]
        [!VAR "ERASE_VALUE_FLASH"="node:ref(Memory)/Erase_Value"!]
        [!VAR "MIN_VAL_TO_WRITE_FOR_FLASH"="node:ref(Memory)/Min_Value_To_Write"!]
        [!IF "Access_Type = 'READ'"!]
            [!IF "$FLASH_ACCESS = 0"!]
                [!VAR "FLASH_ACCESS" = "'READ'"!]
            [!ELSEIF "$FLASH_ACCESS = 'WRITE'"!]
                [!VAR "FLASH_ACCESS" = "'READ_WRITE'"!]
            [!ENDIF!]
        [!ELSEIF "Access_Type = 'WRITE'"!]
            [!IF "$FLASH_ACCESS = 0"!]
                [!VAR "FLASH_ACCESS" = "'WRITE'"!]
            [!ELSEIF "$FLASH_ACCESS = 'READ'"!]
                [!VAR "FLASH_ACCESS" = "'READ_WRITE'"!]
            [!ENDIF!]
        [!ELSE!]
            [!VAR "FLASH_ACCESS" = "'READ_WRITE'"!]
        [!ENDIF!]
    [!ELSEIF "$Memory_Type = 'FLASH_EXT'"!]
        [!VAR "FLASH_EXT_USE" = "1"!]
        [!VAR "MEMORY_MODE_FLASH_EXT" = "node:ref(Memory)/Memory_Mode"!]
        [!VAR "MEMORY_ADDRESS_OFFSET_FLASH_EXT"="node:ref(Memory)/Addr_Offset"!]
        [!VAR "ERASE_VALUE_FLASH_EXT"="node:ref(Memory)/Erase_Value"!]
        [!VAR "MIN_VAL_TO_WRITE_FOR_FLASH_EXT"="node:ref(Memory)/Min_Value_To_Write"!]
        [!IF "Access_Type = 'READ'"!]
            [!IF "$FLASH_EXT_ACCESS = 0"!]
                [!VAR "FLASH_EXT_ACCESS" = "'READ'"!]
            [!ELSEIF "$FLASH_EXT_ACCESS = 'WRITE'"!]
                [!VAR "FLASH_EXT_ACCESS" = "'READ_WRITE'"!]
            [!ENDIF!]
        [!ELSEIF "Access_Type = 'WRITE'"!]
            [!IF "$FLASH_EXT_ACCESS = 0"!]
                [!VAR "FLASH_EXT_ACCESS" = "'WRITE'"!]
            [!ELSEIF "$FLASH_EXT_ACCESS = 'READ'"!]
                [!VAR "FLASH_EXT_ACCESS" = "'READ_WRITE'"!]
            [!ENDIF!]
        [!ELSE!]
            [!VAR "FLASH_EXT_ACCESS" = "'READ_WRITE'"!]
        [!ENDIF!]
    [!ELSEIF "$Memory_Type = 'RAM'"!]
        [!VAR "RAM_USE" = "1"!]
        [!VAR "MEMORY_MODE_RAM" = "node:ref(Memory)/Memory_Mode"!]
        [!VAR "MEMORY_ADDRESS_OFFSET_RAM"="node:ref(Memory)/Addr_Offset"!]
        [!VAR "ERASE_VALUE_RAM"="node:ref(Memory)/Erase_Value"!]
        [!IF "Access_Type = 'READ'"!]
            [!IF "$RAM_ACCESS = 0"!]
                [!VAR "RAM_ACCESS" = "'READ'"!]
            [!ELSEIF "$RAM_ACCESS = 'WRITE'"!]
                [!VAR "RAM_ACCESS" = "'READ_WRITE'"!]
            [!ENDIF!]
        [!ELSEIF "Access_Type = 'WRITE'"!]
            [!IF "$RAM_ACCESS = 0"!]
                [!VAR "RAM_ACCESS" = "'WRITE'"!]
            [!ELSEIF "$RAM_ACCESS = 'READ'"!]
                [!VAR "RAM_ACCESS" = "'READ_WRITE'"!]
            [!ENDIF!]
        [!ELSE!]
            [!VAR "RAM_ACCESS" = "'READ_WRITE'"!]
        [!ENDIF!]
    [!ELSEIF "$Memory_Type = 'CUSTOM'"!]
        [!VAR "CUSTOM_MEMORY_USE" = "1"!]
        [!VAR "MEMORY_MODE_CUSTOM_MEM" = "node:ref(Memory)/Memory_Mode"!]
        [!VAR "MEMORY_ADDRESS_OFFSET_CUSTOM_MEM"="node:ref(Memory)/Addr_Offset"!]
        [!VAR "ERASE_VALUE_CUSTOM_MEM"="node:ref(Memory)/Erase_Value"!]
        [!IF "Access_Type = 'READ'"!]
            [!IF "$CUSTOM_MEMORY_ACCESS = 0"!]
                [!VAR "CUSTOM_MEMORY_ACCESS" = "'READ'"!]
            [!ELSEIF "$CUSTOM_MEMORY_ACCESS = 'WRITE'"!]
                [!VAR "CUSTOM_MEMORY_ACCESS" = "'READ_WRITE'"!]
            [!ENDIF!]
        [!ELSEIF "Access_Type = 'WRITE'"!]
            [!IF "$CUSTOM_MEMORY_ACCESS = 0"!]
                [!VAR "CUSTOM_MEMORY_ACCESS" = "'WRITE'"!]
            [!ELSEIF "$CUSTOM_MEMORY_ACCESS = 'READ'"!]
                [!VAR "CUSTOM_MEMORY_ACCESS" = "'READ_WRITE'"!]
            [!ENDIF!]
        [!ELSE!]
            [!VAR "CUSTOM_MEMORY_ACCESS" = "'READ_WRITE'"!]
        [!ENDIF!]
    [!ENDIF!]
    [!IF "as:modconf('Prog')/DownloadFlashRoutines/Download_Flash_Routines='true'"!]
        [!IF "$Partition_Type = 'PROG_FLASH_ROUTINES_PARTITION'"!]
            [!VAR "Flash_Routines_StartAdd" = "./Erase_Start_Address"!]
            [!VAR "Flash_Routines_EndAdd" = "./Erase_End_Address"!]
            [!VAR "Flash_Routines_EraseVal" = "node:ref(Memory)/Erase_Value"!]
        [!ENDIF!]
    [!ENDIF!]
[!ENDLOOP!]


[!IF "General/Dsc_Prog_Response = 'true'"!]
[!VAR "SESSION_IDX" = "0"!]
[!FOR "SESSION_IDX" = "1" TO "num:dectoint(count(as:modconf('Uds')/Session/*))"!]
    [!IF "as:modconf('Uds')/Session/*[number($SESSION_IDX)]/@name = 'PROGRAMMING'"!]
        [!VAR "P2VAL" = "as:modconf('Uds')/Session/*[number($SESSION_IDX)]/UDS_P2"!]
        [!VAR "P2STARVAL" = "as:modconf('Uds')/Session/*[number($SESSION_IDX)]/UDS_P2STAR"!]
    [!ENDIF!]
[!ENDFOR!]
#define PROG_P2_PROG_SESSION_VAL                        [!WS "24"!](u16)[!"$P2VAL"!]U
#define PROG_P2STAR_PROG_SESSION_VAL                    [!WS "20"!](u16)[!"$P2STARVAL"!]U
[!ENDIF!]

[!VAR "FAR_POINTER"="General/FAR_POINTER_Definition"!]
#define PROG_FAR_POINTER                                *[!"$FAR_POINTER"!]

extern const tCfgMemorytType m_astCfgMemory[PROG_MEMORY_NB];
[!IF "General/Tunable_Parameters = 'false'"!]
extern const tCfgSegmentType stConfigSegment[PROG_SEGMENT_NB];
[!ELSE!]
extern const tCfgSegmentType stConstConfigSegment[PROG_SEGMENT_NB];
extern tCfgSegmentType stConfigSegment[PROG_SEGMENT_NB];
[!ENDIF!]

/* Algorithm to be used for OemInd implementation: EB/Custom */
#define PROG_APPLI_CHECK_ALGO_EB                        [!WS "24"!][!IF "OemInd/Application_Validity_Algo = 'EB'"!]STD_ON[!ELSE!]STD_OFF[!ENDIF!][!CR!]

[!IF "$FLASH_USE = 1"!]
#define PROG_FLASH_MEMORY_USE                           PROG_TRUE
#define PROG_FLASH_ERASE_VALUE                          [!"$ERASE_VALUE_FLASH"!]U
#define PROG_FLASH_ADDR_OFFSET                          [!"$MEMORY_ADDRESS_OFFSET_FLASH"!]U
#define PROG_FLASH_ACCESS_TYPE                          [!WS "26"!][!IF "$FLASH_ACCESS = 'READ'"!]PROG_MEM_ACCESS_TYPE_READ[!ELSEIF "$FLASH_ACCESS = 'WRITE'"!]PROG_MEM_ACCESS_TYPE_WRITE[!ELSEIF "$FLASH_ACCESS = 'READ_WRITE'"!]PROG_MEM_ACCESS_TYPE_READ_WRITE[!ELSE!]PROG_MEM_ACCESS_TYPE_NONE[!ENDIF!][!CR!]
    [!IF "$MEMORY_MODE_FLASH = 'asynchronous'"!]
#define PROG_FLASH_MODE                                 PROG_MEMORY_ASYNCHRONOUS
    [!ELSE!]
#define PROG_FLASH_MODE                                 PROG_MEMORY_SYNCHRONOUS
    [!ENDIF!]
[!ELSE!]
#define PROG_FLASH_MEMORY_USE                           PROG_FALSE
#define PROG_FLASH_MODE                                 PROG_MEMORY_NOTUSED
#define PROG_FLASH_ACCESS_TYPE                          PROG_MEMORY_NOTUSED
[!ENDIF!]

[!IF "$FLASH_EXT_USE = 1"!]
#define PROG_FLASH_EXT_MEMORY_USE                       PROG_TRUE
#define PROG_FLASH_EXT_ERASE_VALUE                      [!"$ERASE_VALUE_FLASH_EXT"!]U
#define PROG_FLASH_EXT_ADDR_OFFSET                      [!"$MEMORY_ADDRESS_OFFSET_FLASH_EXT"!]U
#define PROG_FLASH_EXT_ACCESS_TYPE                      [!WS "2"!][!IF "$FLASH_EXT_ACCESS = 'READ'"!]PROG_MEM_ACCESS_TYPE_READ[!ELSEIF "$FLASH_EXT_ACCESS = 'WRITE'"!]PROG_MEM_ACCESS_TYPE_WRITE[!ELSEIF "$FLASH_EXT_ACCESS ='READ_WRITE'"!]PROG_MEM_ACCESS_TYPE_READ_WRITE[!ELSE!]PROG_MEM_ACCESS_TYPE_NONE[!ENDIF!][!CR!]
    [!IF "$MEMORY_MODE_FLASH_EXT = 'asynchronous'"!]
#define PROG_FLASH_EXT_MODE                             PROG_MEMORY_ASYNCHRONOUS
    [!ELSE!]
#define PROG_FLASH_EXT_MODE                             PROG_MEMORY_SYNCHRONOUS
    [!ENDIF!]
[!ELSE!]
#define PROG_FLASH_EXT_MEMORY_USE                       PROG_FALSE
#define PROG_FLASH_EXT_MODE                             PROG_MEMORY_NOTUSED
#define PROG_FLASH_EXT_ACCESS_TYPE                      PROG_MEMORY_NOTUSED
[!ENDIF!]

[!IF "$RAM_USE = 1"!]
#define PROG_RAM_MEMORY_USE                             PROG_TRUE
#define PROG_RAM_ERASE_VALUE                            [!"$ERASE_VALUE_RAM"!]U
#define PROG_RAM_MODE                                   PROG_MEMORY_SYNCHRONOUS
#define PROG_RAM_ACCESS_TYPE                            [!WS "28"!][!IF "$RAM_ACCESS = 'READ'"!]PROG_MEM_ACCESS_TYPE_READ[!ELSEIF "$RAM_ACCESS = 'WRITE'"!]PROG_MEM_ACCESS_TYPE_WRITE[!ELSEIF "$RAM_ACCESS = 'READ_WRITE'"!]PROG_MEM_ACCESS_TYPE_READ_WRITE[!ELSE!]PROG_MEM_ACCESS_TYPE_NONE[!ENDIF!][!CR!]


[!IF "as:modconf('Prog')/DownloadFlashRoutines/Download_Flash_Routines='true'"!]
/* These macros are used to define the address of the Flash routine in RAM memory */
#define PROG_FLASH_ROUTINES_RAM_ADDR_START              [!"$Flash_Routines_StartAdd"!]U
#define PROG_FLASH_ROUTINES_RAM_ADDR_END                [!"$Flash_Routines_EndAdd"!]U
#define PROG_FLASH_ROUTINES_RAM_ERASE_VALUE             [!"$Flash_Routines_EraseVal"!]U
[!ENDIF!]
[!ELSE!]
#define PROG_RAM_MEMORY_USE                             PROG_FALSE
#define PROG_RAM_MODE                                   PROG_MEMORY_NOTUSED
#define PROG_RAM_ERASE_VALUE                            0U
[!ENDIF!]

[!IF "$CUSTOM_MEMORY_USE = 1"!]
#define PROG_CUSTOM_MEMORY_USE                          PROG_TRUE
#define PROG_CUSTOM_MEMORY_ERASE_VALUE                  [!"$ERASE_VALUE_CUSTOM_MEM"!]U
#define PROG_CUSTOM_MEMORY_ADDR_OFFSET                  [!"$MEMORY_ADDRESS_OFFSET_CUSTOM_MEM"!]U
#define PROG_CUSTOM_MEMORY_ACCESS_TYPE                  [!WS "18"!][!IF "$CUSTOM_MEMORY_ACCESS = 'READ'"!]PROG_MEM_ACCESS_TYPE_READ[!ELSEIF "$CUSTOM_MEMORY_ACCESS = 'WRITE'"!]PROG_MEM_ACCESS_TYPE_WRITE[!ELSEIF "$CUSTOM_MEMORY_ACCESS ='READ_WRITE'"!]PROG_MEM_ACCESS_TYPE_READ_WRITE[!ELSE!]PROG_MEM_ACCESS_TYPE_NONE[!ENDIF!][!CR!]
    [!IF "$MEMORY_MODE_CUSTOM_MEM = 'asynchronous'"!]
#define PROG_CUSTOM_MEMORY_MODE                         PROG_MEMORY_ASYNCHRONOUS
    [!ELSE!]
#define PROG_CUSTOM_MEMORY_MODE                         PROG_MEMORY_SYNCHRONOUS
    [!ENDIF!]
[!ELSE!]
#define PROG_CUSTOM_MEMORY_USE                          PROG_FALSE
#define PROG_CUSTOM_MEMORY_MODE                         PROG_MEMORY_NOTUSED
#define PROG_CUSTOM_MEMORY_ACCESS_TYPE                  PROG_MEMORY_NOTUSED
[!ENDIF!]

[!IF "General/Tunable_Parameters = 'false'"!]
/* Segment Index */
[!FOR "SEGMENT_IDX" = "1" TO "$SEGMENT_MAX"!]
        [!VAR "SEGMENT_NAME"="text:toupper(name(Segments/*[number($SEGMENT_IDX)]))"!]
        [!VAR "SEGMENT_ID"="num:inttohex(($SEGMENT_IDX)-1)"!]
#define PROG_SEG_[!"$SEGMENT_NAME"!]                    [!"$SEGMENT_ID"!]
[!ENDFOR!]
[!ENDIF!]

[!FOR "MEMORY_IDX" = "1" TO "$MEMORY_MAX"!]
        [!VAR "MEMORY_NAME"="text:toupper(name(Memory/*[number($MEMORY_IDX)]))"!]
        [!VAR "MEMORY_ID"="num:inttohex(($MEMORY_IDX)-1)"!]
#define PROG_MEMORY_[!"$MEMORY_NAME"!]                  [!"$MEMORY_ID"!]
[!ENDFOR!]

[!IF "General/Dual_Memory_Bank_Used = 'true'"!]
#define PROG_OTA_DUALBANK_USED                          STD_ON
[!ELSE!]
#define PROG_OTA_DUALBANK_USED                          STD_OFF
[!ENDIF!]

/* Network use definition */
#define PROG_BLPDUR_NETWORK_CAN_SUPPORTED      [!WS "6"!][!IF "as:modconf('BlPduR')/General/Can_Protocol_Supported = 'true'"!]STD_ON[!ELSE!]STD_OFF[!ENDIF!][!CR!]
#define PROG_BLPDUR_NETWORK_FLEXRAY_SUPPORTED  [!WS "2"!][!IF "as:modconf('BlPduR')/General/FlexRay_Protocol_Supported = 'true'"!]STD_ON[!ELSE!]STD_OFF[!ENDIF!][!CR!]
#define PROG_BLPDUR_NETWORK_ETH_SUPPORTED      [!WS "6"!][!IF "as:modconf('BlPduR')/General/Eth_Protocol_Supported = 'true'"!]STD_ON[!ELSE!]STD_OFF[!ENDIF!][!CR!]
#define PROG_BLPDUR_NETWORK_LIN_SUPPORTED      [!WS "6"!][!IF "as:modconf('BlPduR')/General/Lin_Protocol_Supported = 'true'"!]STD_ON[!ELSE!]STD_OFF[!ENDIF!][!CR!]
#define PROG_BLPDUR_ASR_NETWORK_PRESENT        [!WS "8"!][!IF "as:modconf('BlPduR')/General/Can_Protocol_Supported = 'true'
                                                          or as:modconf('BlPduR')/General/FlexRay_Protocol_Supported = 'true'
                                                          or as:modconf('BlPduR')/General/Eth_Protocol_Supported = 'true'"!]STD_ON[!ELSE!]STD_OFF[!ENDIF!][!CR!]

#endif /* PROG_CFG_H */
