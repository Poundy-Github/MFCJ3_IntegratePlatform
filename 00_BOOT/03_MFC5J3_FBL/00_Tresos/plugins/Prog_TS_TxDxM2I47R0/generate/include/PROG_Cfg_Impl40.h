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
/*%%   _____________________________   %%  \file PROG_Cfg_Impl40.h               */
/*%%  |                             |  %%  \brief PROG layer include plugin file */
/*%%  |   &&&&&   &&&&&             |  %%  Module version: 2.47.0 BL3              */
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
#ifndef PROG_CFG_IMPL40_H
#define PROG_CFG_IMPL40_H

[!NOCODE!]
[!IF "not(node:exists(as:modconf('ProgVAG')))"!]
    [!SKIPFILE!]
[!ENDIF!]
[!ENDNOCODE!]

[!IF "node:exists(as:modconf('ProgVAG'))"!]
[!/********************* Feature configuration for VAG ************************/!]

#define PROG_SIGNATURE_CALCULATION_OVER_HASH               STD_OFF
#define PROG_COMPUTE_HASH_WITH_ADDR_LEN                    [!WS "20"!][!IF "DownloadVerification/SignatureVerificationWithAddrLen = 'true'"!]STD_ON[!ELSE!]STD_OFF[!ENDIF!][!CR!]
#define PROG_RESUM_REPROG                                  STD_OFF

#define PROG_ECU_RESET_RESPONSE_SIZE                       2U
#define PROG_DSC_RESPONSE_SIZE                             2U
#define PROG_TD_RESPONSE_SIZE                              2U
#define PROG_RTE_RESPONSE_SIZE                             1U
#define PROG_COMPARE_KEY_RESPONSE_SIZE                     2U
#define PROG_ERASE_POS_RESPONSE_SIZE                       5U
#define PROG_CHK_PROG_DEP_POS_RESPONSE_SIZE                5U
#define PROG_ERASE_REQUEST_DATA                            4U
#define PROG_RD_RESPONSE_SIZE                              4U
#define PROG_TD_MIN_SIZE                                   2U
#define PROG_TD_MIN_SIZE_RD                                3U
#define PROG_WF_RESPONSE_SIZE                              3U
#define PROG_NRC_SIZE                                      3U
#define PROG_CHK_PROG_PRECOND_SIZE                         5U
#define PROG_CHK_PROG_PRECOND_SALOCKED_STATUS              0x81U
#define PROG_CHK_PROG_PRECOND_SALOCKED_RESPONSE_SIZE       0x01U
#define PROG_CRC_COMP_RESPONSE_SIZE                        5U
#define PROG_COH_CHK_RESP_SIZE                             5U
#define PROG_RTE_SIZE                                      1U


#define PROG_BOOT_REPROG                                   1U
#define PROG_BOOT_NOREPROG                                 0U

#define PROG_ERASE_ADDR_LEN                                4U
#define PROG_ERASE_SIZE_LEN                                4U

#define PROG_ERASE_TYPE                                    PROG_ERASE_BY_BLOCK_ID

#define PROG_REPROG_TYPE                                   PROG_NO_REPROG_TYPE

[!IF "General/PreliminaryErasing = 'true'"!]
[!IF "General/MaxBlockID = 'FF'"!]
#define PROG_MAX_BLOCK_ID                                  0xFFU
[!ENDIF!]
[!IF "General/MaxBlockID = 'FFFF'"!]
#define PROG_MAX_BLOCK_ID                                  0xFFFFU
[!ENDIF!]
[!ENDIF!]

/* Data verification */
[!IF "DownloadVerification/Checksum_Algo = 'CRC32 Ethernet'"!]
#define PROG_VERIFICATION_METHOD                           PROG_VERIFICATION_CRC
#define PROG_CRC_CALCULATION                               PROG_TD_CRC32
#define PROG_CRC_ALGO                                      PROG_CRC32_ETHERNET
#define PROG_VERIFICATION_ON_THE_FLY                       STD_OFF
#define PROG_SIGNATURE_CALCULATION                         STD_OFF
#define PROG_SIGNATURE_VERIFICATION_ON_FLASHED_DATA        STD_OFF
[!ENDIF!]
[!IF "DownloadVerification/Checksum_Algo = 'Signature'"!]
#define PROG_VERIFICATION_ON_THE_FLY                       STD_ON
#define PROG_SIGNATURE_CALCULATION                         STD_ON
#define PROG_VERIFICATION_METHOD                           PROG_VERIFICATION_IN_DFI
#define PROG_CRC_CALCULATION                               PROG_TD_CRC32
#define PROG_CRC_LENGTH                                    4U
#define PROG_SIGNATURE_VERIFICATION_ON_FLASHED_DATA        STD_OFF
#define PROG_CRC_ALGO                                      PROG_CRC32_ETHERNET
[!ENDIF!]

[!IF "DownloadVerification/CVN_Verification = 'true'"!]
#define PROG_CVN_CHECK                                     STD_ON
#define PROG_CVN_LENGTH                                    0x10U
#define PROG_PARTIAL_SW_ROUTINE_CVN_LEN                    0x17U
[!ELSE!]
#define PROG_CVN_CHECK                                     STD_OFF
[!ENDIF!]

#define PROG_HASH_CALCULATION                              STD_OFF
#define PROG_RANGE_CKS                                     STD_OFF
#define PROG_SEG_LIST_CKS                                  STD_ON
#define PROG_SINGLE_STEP_SIGNATURE_CHECK                   STD_OFF


/*Download type*/
[!IF "VAG/Request_Download_Address_Mode = 'Download by logical block'"!]
#define PROG_DOWNLOAD_TYPE                                 PROG_DOWNLOAD_BY_LOGICAL_BLOCK
[!ELSEIF "VAG/Request_Download_Address_Mode = 'Download by logical block and segment'"!]
#define PROG_DOWNLOAD_TYPE                                 PROG_DOWNLOAD_BY_LOGICAL_BLOCK_SEGMENT
[!ENDIF!]
#define PROG_MAX_RD_ADDRESS_LENGTH                         3U
/* Maximum Number of byte on which Block is coded in the Erase request */
#define PROG_MAX_BYTE_ERASE_BLOCK_LENGTH                   2U

/* Routine type defines */
#define PROG_ROUTINE_TYPE_1                                0x10U
#define PROG_ROUTINE_TYPE_2                                0x20U
#define PROG_ROUTINE_TYPE_3                                0x30U

/* Routine status defines */
#define PROG_ROUTINE_FINISHED_OK                           0x00U
#define PROG_ROUTINE_FINISHED_NOK                          0x01U
#define PROG_ROUTINE_IN_PROGRESS                           0x02U

/* specific routine result value */
#define PROG_ROUTINE_ACTIVE                                0x01U
#define PROG_ROUTINE_RESAVAILABLE                          0x02U
#define PROG_ROUTINE_PREDIF                                0x08U
#define PROG_ROUTINE_STOP_SUBFUNC                          0x10U
#define PROG_ROUTINE_RES_SUBFUNC                           0x20U
#define PROG_ROUTINE_SELFTERM                              0x40U
#define PROG_ROUTINE_AUTONOMOUS                            0x80U
[!IF "VAG/Downgrade_Protection = 'true'"!]
#define PROG_ROUTINE_RFS_DRV_INVALID_OR_MISSING            0x80U
#define PROG_ROUTINE_RFS_VER_OR_BID_INVALID                0x81U
[!ENDIF!]

#define PROG_APPL_VALID                                    0x00000002U
#define PROG_APPL_INVALID                                  0x00000001U

[!IF "General/Dsc_Prog_Response = 'true'"!]
[!VAR "SESSION_IDX" = "0"!]
[!FOR "SESSION_IDX" = "1" TO "num:dectoint(count(as:modconf('Uds')/Session/*))"!]
    [!IF "as:modconf('Uds')/Session/*[number($SESSION_IDX)]/@name = 'PROGRAMMING'"!]
        [!VAR "P2VAL" = "as:modconf('Uds')/Session/*[number($SESSION_IDX)]/UDS_P2"!]
        [!VAR "P2STARVAL" = "as:modconf('Uds')/Session/*[number($SESSION_IDX)]/UDS_P2STAR"!]
    [!ENDIF!]
[!ENDFOR!]
#define PROG_P2_PROG_SESSION_VAL                           (u16)[!"$P2VAL"!]U
#define PROG_P2STAR_PROG_SESSION_VAL                       (u16)[!"$P2STARVAL"!]U
[!ENDIF!]

[!VAR "SESSION_IDX" = "0"!]
[!FOR "SESSION_IDX" = "1" TO "num:dectoint(count(as:modconf('Uds')/Session/*))"!]
    [!IF "as:modconf('Uds')/Session/*[number($SESSION_IDX)]/@name = 'DEFAULT'"!]
        [!VAR "P2VAL" = "as:modconf('Uds')/Session/*[number($SESSION_IDX)]/UDS_P2"!]
        [!VAR "P2STARVAL" = "as:modconf('Uds')/Session/*[number($SESSION_IDX)]/UDS_P2STAR"!]
    [!ENDIF!]
[!ENDFOR!]
#define PROG_P2_DEFAULT_SESSION_VAL                        (u16)[!"$P2VAL"!]U
#define PROG_P2STAR_DEFAULT_SESSION_VAL                    (u16)[!"$P2STARVAL"!]U

#define PROG_AUTOCONTROL_POS_RESPONSE_SIZE                 6U

#define PROG_IMPL_VARIANT                                  PROG_IMPL_40

#define PROG_WATCHDOG_ENABLE                               STD_ON
#define PROG_REQUEST_DOWNLOAD_ENABLE                       STD_ON
#define PROG_SECURITY_ENABLE                               STD_ON
#define PROG_SA_SEED_ENABLE                                STD_ON
#define PROG_SA_KEY_ENABLE                                 STD_ON
#define PROG_ERASE_MEMORY_ENABLE                           STD_ON
#define PROG_TRANSFER_DATA_ENABLE                          STD_ON
#define PROG_REQUEST_TRANSFER_EXIT_ENABLE                  STD_ON
#define PROG_ECU_RESET_ENABLE                              STD_ON
#define PROG_ACTIVE_SBL_ENABLE                             STD_OFF
#define PROG_UPDATE_PSI_ENABLE                             STD_OFF
#define PROG_CONTROL_DTC_SETTING_ENABLE                    STD_ON
#define PROG_COMMUNICATION_CONTROL_ENABLE                  STD_ON
#define PROG_CHECK_MEMORY_ENABLE                           STD_ON
#define PROG_GET_EXPECTED_CRC_ENABLED                      [!WS "20"!][!IF "General/Expected_Crc_Location = 'Application'"!]STD_ON[!ELSE!]STD_OFF[!ENDIF!][!CR!]
#define PROG_CRC_COMPUTE_COMPARE_ENABLE                    STD_ON
#define PROG_SET_CRC_COMPARE_RESULT_ENABLE                 STD_ON
#define PROG_CONTROL_FAIL_SAFE_REACTION_START_ENABLE       STD_OFF
#define PROG_CONTROL_FAIL_SAFE_REACTION_STOP_ENABLE        STD_OFF
#define PROG_CHECK_PROGRAMMING_DEPENDENCIES_ENABLE         STD_OFF
#define PROG_NETWORK_MANAGEMENT_ENABLE                     STD_OFF
#define PROG_APPLI_CHECK_ON_S3TIMEOUT_ENABLE               STD_OFF
#define PROG_APPLI_CHECK_ENABLE                            STD_ON
#define PROG_RESPOND_TO_PROG_SESSION                       [!WS "20"!][!IF "General/Dsc_Prog_Response = 'true'"!]STD_ON[!ELSE!]STD_OFF[!ENDIF!][!CR!]
#define PROG_RESET_CAUSE_ENABLE                            STD_ON
#define PROG_BYPASS_SA_COMPARE_KEY                         [!WS "25"!][!IF "General/BypassSACompareKey = 'true'"!]STD_ON[!ELSE!]STD_OFF[!ENDIF!][!CR!]
#define PROG_PRECOND_CHECK_ENABLE                          [!WS "20"!][!IF "General/Check_Programming_PreConditions = 'true'"!]STD_ON[!ELSE!]STD_OFF[!ENDIF!][!CR!]
#define PROG_PEC_ENABLE                                    STD_OFF
#define PROG_MULTIPLE_BUFFERS_ENABLE                       [!WS "20"!][!IF "as:modconf('BlPduR')/General/MultipleRxBuffer = 'true'"!]STD_ON[!ELSE!]STD_OFF[!ENDIF!][!CR!]

#define PROG_SBL_HEADER_DEFINE                             STD_OFF

#define PROG_SWITCH_APPLICATION_MODE_ENABLE                STD_ON
#define PROG_CHECK_PROGRAMMING_REQUEST_ENABLE              STD_ON
#define PROG_CAL_CRC_ENABLE                                STD_ON
#define PROG_ACTIVE_SBL_RESPONSE_ENABLE                    STD_OFF
#define PROG_PRE_INIT_ENABLE                               STD_ON
#define PROG_EXTENDED_SESSION_MANAGED                      STD_ON

#define PROG_ERASE_ALL                                     STD_OFF
#define PROG_AUTHENTICATED_BOOT_ENABLE                     STD_OFF
#define PROG_BOOT_VERIFICATION                             STD_OFF
#define PROG_SECURE_BOOT_CHECKSUM_COMPUTATION              STD_OFF
#define PROG_SECURE_APPLI_CHECKSUM_COMPUTATION             STD_OFF

#define PROG_SLEEP_MANAGEMENT_TYPE                         [!WS "25"!][!IF "General/Sleep_Management_Type = 'Timeout'"!]PROG_SLEEP_MANAGEMENT_TIMEOUT[!ELSEIF "General/Sleep_Management_Type = 'I/O'"!]PROG_SLEEP_MANAGEMENT_IO[!ELSE!]PROG_SLEEP_MANAGEMENT_OFF[!ENDIF!][!CR!]
[!IF "General/Sleep_Management_Type = 'Timeout'"!]
#define PROG_SLEEP_TIMEOUT                                 [!WS "33"!]([!"num:dectoint(General/Sleep_Timeout)"!]U/PROG_MANAGE_PERIOD)
[!ENDIF!]

[!IF "node:exists(as:modconf('ProgVAG'))"!]
[!IF "(as:modconf('SA')/General/Enable_Antiscanning = 'true')"!]
#define PROG_ANTISCANNING_ENABLED                          STD_ON
[!ELSE!]
#define PROG_ANTISCANNING_ENABLED                          STD_OFF
[!ENDIF!]
[!ENDIF!]

/* Security access limit request seed */
[!IF "(as:modconf('SA')/General/Enable_Request_Seed_Limit = 'true')"!]
#define PROG_LIMIT_NB_REQUEST_SEED_ENABLED              STD_ON
[!ELSE!]
#define PROG_LIMIT_NB_REQUEST_SEED_ENABLED              STD_OFF
[!ENDIF!]

/* Define if NRC78 shall be sent before SecurityAccess */
#define PROG_NRC78_ON_SA_ENABLE                            [!WS "28"!][!IF "NRC78_Transmission/Transmit_Nrc78_On_SecurityAccess = 'true'"!]STD_ON[!ELSE!]STD_OFF[!ENDIF!][!CR!]

/* Define for the fingerprint writing */
#define PROG_WF_DID_1ST_BYTE                               0xF1U
#define PROG_WF_DID_2ND_BYTE_APP                           0x5AU
#define PROG_WF_DID_2ND_BYTE_CALIB                         0x5AU

/*Use of StartAddress - EndAddress instead of StartAddress-Length*/
#define PROG_USE_START_ADDR_END_ADDR                       STD_OFF

/*Programming Status usage*/
#define PROG_REQ_PROGRAMMING_STATUS_ENABLE                 STD_OFF

#define PROG_USE_ECUID_CALLBACK                            STD_OFF

/*Use Coherency check*/
#define PROG_COHERENCY_CHECK_ENABLE                        STD_ON

/* Use Programming counter */
#define PROG_PROGRAMMING_CNTR_ENABLE                       STD_ON

/* Use partial checksum verification */
[!IF "node:exists(as:modconf('Uds'))"!]
    [!VAR "PARTIAL_VERIFY_CRC_USE" = "0"!]
    [!LOOP " as:modconf('Uds')/Routine_Control/*"!]
        [!IF "Callback = 'PROG_PartialVerificationCrc'"!]
            [!VAR "PARTIAL_VERIFY_CRC_USE" = "1"!]
        [!ENDIF!]
    [!ENDLOOP!]
    [!IF "$PARTIAL_VERIFY_CRC_USE = 1"!]
#define PROG_PARTIAL_VERIFY_CRC                            STD_ON
#define PROG_PART_VERIF_BLOCKID_LEN_1BYTE                  1U
#define PROG_PART_VERIF_BLOCKID_LEN_2BYTES                 2U
    [!ELSE!]
#define PROG_PARTIAL_VERIFY_CRC                            STD_OFF
    [!ENDIF!]
[!ENDIF!]


[!IF "(node:exists(as:modconf('ReProgMemM')))"!]
[!VAR "MEMORY_MAX"="num:dectoint(count(as:modconf('ReProgMemM')/MemoryConfig/Memory/*))"!]
[!ELSEIF "(node:exists(as:modconf('Flash')))"!]
[!VAR "MEMORY_MAX"="num:dectoint(count(Memory/*))"!]
[!ENDIF!]

[!VAR "UPDATE_TP_PARAM_USED" = "0"!]
[!IF "node:exists(as:modconf('Uds'))"!]
    [!LOOP " as:modconf('Uds')/Service_DID/*"!]
        [!IF "DID = num:hextoint('0x0410')"!]
            [!VAR "UPDATE_TP_PARAM_USED" = "1"!]
        [!ENDIF!]
    [!ENDLOOP!]
[!ENDIF!]
/* Dynamic reconfiguration of TP parameters: BS and STmin */
#define PROG_UPDATE_TP_PARAM_ENABLE                        [!WS "24"!][!IF "$UPDATE_TP_PARAM_USED = 1"!]STD_ON[!ELSE!]STD_OFF[!ENDIF!][!CR!]

#define PROG_GET_PROG_CNTR_ENABLE                          1U
#define PROG_GET_PROG_CNTR_DISABLE                         0U

[!VAR "GET_PROG_CNTR_ALL" = "0"!]
[!IF "node:exists(as:modconf('Uds'))"!]
    [!LOOP " as:modconf('Uds')/Service_DID/*"!]
        [!IF "Callback = 'PROG_GetAllProgCntrLockVals'"!]
            [!VAR "GET_PROG_CNTR_ALL" = "1"!]
        [!ENDIF!]
    [!ENDLOOP!]
[!ENDIF!]

[!IF "$GET_PROG_CNTR_ALL = 1"!]
#define PROG_CNTR_GET_TYPE                                 PROG_GET_PROG_CNTR_ENABLE
[!ELSE!]
#define PROG_CNTR_GET_TYPE                                 PROG_GET_PROG_CNTR_DISABLE
[!ENDIF!]

[!IF "node:exists(as:modconf('Csm'))"!]
#define PROG_CRY_PRESENT                                   STD_ON

#define PROG_DIGEST_LENGTH                                 64U
#define PROG_SIGNATURE_LENGTH                              384U
#define PROG_KEY_LENGTH                                    384U /* In bytes */

#define PROG_CRY_EXPONENT_ENABLED                          STD_ON
[!ELSE!]
#define PROG_CRY_PRESENT                                   STD_OFF
[!ENDIF!]
[!IF "node:exists(as:modconf('Cal'))"!]
#define PROG_CAL_PRESENT                                   STD_ON
[!ELSE!]
#define PROG_CAL_PRESENT                                   STD_OFF
[!ENDIF!]

[!IF "node:exists(as:modconf('CryShe'))"!]
#define PROG_CRYSHE_PRESENT                                STD_ON
[!ELSE!]
#define PROG_CRYSHE_PRESENT                                STD_OFF
[!ENDIF!]

[!VAR "BLOCK_MAX"="num:dectoint(count(Blocks/*))"!]
[!IF "General/PreliminaryErasing = 'true'"!]
/* Include a virtual block with all the segments */
#define PROG_BLOCK_NB                                      [!"num:dectoint($BLOCK_MAX + 1)"!]U
[!ELSE!]
#define PROG_BLOCK_NB                                      [!"$BLOCK_MAX"!]U
[!ENDIF!]
extern const tProg_Block stCfgBlock[PROG_BLOCK_NB];
[!ENDIF!]

/* Downloading Flash driver feature activation */
#define PROG_DOWNLOAD_FLASH_ROUTINES_ENABLE                [!WS "16"!][!IF "DownloadFlashRoutines/Download_Flash_Routines = 'true'"!]STD_ON[!ELSE!]STD_OFF[!ENDIF!]

#define PROG_DOWNLOAD_FLASH_ROUTINES_REJECT_AFTER_FAILURE  STD_ON

#define PROG_CSM_HASH_USED                                 STD_OFF
#define PROG_CSM_MAC_USED                                  STD_OFF

/****************************************************/
/*                  UDS                             */
/****************************************************/
#define PROG_RESPONSE_PARAMETERS_OFFSET                    (u8) (1U)/* This define is used because the tables in C starts from 0 and not 1
                                                                    and the indexes in the specifications starts sometimes from 1 */

/* Services */

/* Routines */
#define PROG_RC_ROUTINE_STATUS_BASE_INDEX                  PROG_MSG_BYTE_INDEX(5U)
#define PROG_RC_ROUTINE_INFO_BASE_INDEX                    PROG_MSG_BYTE_INDEX(5U)
#define PROG_RC_ROUTINE_INFO_SIZE                          (u8) 1U

/* Routine 0x0202 */
[!IF "DownloadVerification/Checksum_Algo = 'CRC32 Ethernet'"!]
#define PROG_RC_OPTION_RECORD_CRC_VAL_BASE_INDEX           PROG_MSG_BYTE_INDEX(5U)
[!ENDIF!]
[!IF "DownloadVerification/Checksum_Algo = 'Signature'"!]
#define PROG_RC_OPTION_RECORD_SIGVAL_BASE_INDEX            PROG_MSG_BYTE_INDEX(5U)
#define PROG_RC_OPTION_RECORD_SIGVAL_SIZE                  (u16) PROG_SIGNATURE_LENGTH
#define PROG_RC_OPTION_RECORD_CRC_VAL_BASE_INDEX           (u16)(PROG_RC_OPTION_RECORD_SIGVAL_BASE_INDEX + PROG_RC_OPTION_RECORD_SIGVAL_SIZE)

#define PROG_RC_STATUS_RECORD_VERIF_RESULTS_BASE_INDEX     PROG_RC_ROUTINE_STATUS_BASE_INDEX
#define PROG_RC_STATUS_RECORD_VERIF_RESULTS_SIZE           (u8) 1U
#define PROG_RC_STATUS_RECORD_VERIF_RESULTS_OK             (u8) 0U
#define PROG_RC_STATUS_RECORD_VERIF_RESULTS_GEN_FAILURE    (u8) 1U
#define PROG_RC_STATUS_RECORD_VERIF_RESULTS_CRC_FAILED     (u8) 2U
#define PROG_RC_STATUS_RECORD_VERIF_RESULTS_SIG_FAILED     (u8) 4U
#define PROG_RC_STATUS_RECORD_VERIF_RESULTS_DELTA_FAILED   (u8) 8U
#define PROG_RC_STATUS_RECORD_VERIF_RESULTS_RW_FAILED      (u8) 64U
#define PROG_RC_STATUS_RECORD_VERIF_RESULTS_NOK            (u8) 3U
[!ENDIF!]
/* Routine 0xFF00 */
#define PROG_RC_STATUS_RECORD_ERASEVERIF_BASE_INDEX        PROG_RC_ROUTINE_STATUS_BASE_INDEX
#define PROG_RC_STATUS_RECORD_ERASEVERIF_OK                (u8) 0U
#define PROG_RC_STATUS_RECORD_ERASEVERIF_NOT_OK            (u8) 1U

/* Routine 0xFF01 */

/* Data Identifiers */
#define PROG_DID_DATA_RECORD_BASE_INDEX                    PROG_MSG_BYTE_INDEX(4U)

/* DID 0x0410-Bootloader TP Blocksize */
#define PROG_DID_BS_VALUE_BASE_INDEX                       PROG_DID_DATA_RECORD_BASE_INDEX
#define PROG_UPDATE_TP_PARAM_RESPONSE_SIZE                 (u8) 4U

#define PROG_RC_PART_VERIF_BLOCKID_BASE_INDEX              PROG_MSG_BYTE_INDEX(7U)

/* Block Id in Fingerprint */
#define PROG_BLOCKID_IN_FINGERPRINT                        STD_OFF

#define PROG_DECOMP_FLASH_ROUTINES                         STD_OFF

/*Securiy access request seed delay timer*/
[!IF "as:modconf('SA')/General/Security_Access_Rs_Delay_Timer != '0'"!]
#define PROG_REQUEST_SEED_DELAY_TIMER_ENABLED            STD_ON
[!ELSE!]
#define PROG_REQUEST_SEED_DELAY_TIMER_ENABLED            STD_OFF
[!ENDIF!]

/*Introduced below the compiler switch to support Fingerprint for the Segments in RAM*/
#ifndef PROG_RAMSEG_FINGERPRINT_SUPPORT
#define PROG_RAMSEG_FINGERPRINT_SUPPORT                    STD_OFF
#endif

/* Downgrade protection activation */
#define PROG_ENABLE_DOWNGRADE_PROTECTION                   [!WS "20"!][!IF "VAG/Downgrade_Protection = 'true'"!]STD_ON[!ELSE!]STD_OFF[!ENDIF!][!CR!]
[!IF "VAG/Downgrade_Protection = 'true'"!]
[!LOOP "as:modconf('Prog')/Blocks/*"!]
    [!IF "node:name(.) = node:name(node:ref(as:modconf('Prog')/VAG/PFT_Block_Id))"!]
/* The index of the pseudo flash driver in the table stCfgBlock */
#define PROG_PFT_BLOCK                                     [!WS "38"!][!"num:i(@index)"!]U
    [!ENDIF!]
[!ENDLOOP!]

[!ENDIF!]

#endif /* PROG_CFG_IMPL_40_H */
