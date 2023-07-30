/**
 * \file
 *
 * \brief AUTOSAR Demo
 *
 * This file contains the implementation of the AUTOSAR
 * module Demo.
 *
 * \author Elektrobit Automotive GmbH, 91058 Erlangen, Germany
 *
 * Copyright 2005 - 2019 Elektrobit Automotive GmbH
 * All rights exclusively reserved for Elektrobit Automotive GmbH,
 * unless expressly agreed to otherwise.
 */

#if (!defined DCM_TYPES_H)
#define DCM_TYPES_H

/*==[Includes]================================================================*/

#include <Dcm_StubCfg.h>
#include <ComStack_Types.h>

/*==[Macros]==================================================================*/

/* Dcm_StatusType */
#define DCM_E_OK 0x00U
#define DCM_E_COMPARE_KEY_FAILED 0x01U
#define DCM_E_TI_PREPARE_LIMITS 0x02U
#define DCM_E_TI_PREPARE_INCONSTENT 0x03U
#define DCM_E_SESSION_NOT_ALLOWED 0x04U
#define DCM_E_PROTOCOL_NOT_ALLOWED 0x05U
#define DCM_E_ROE_NOT_ACCEPTED 0x06U
#define DCM_E_PERIODICID_NOT_ACCEPTED 0x07U
#define DCM_E_REQUEST_NOT_ACCEPTED 0x08U
#define DCM_E_REQUEST_ENV_NOK 0x09U

/* Dcm_SecLevelType */
#define DCM_SEC_LEV_LOCKED 0x00U
#define DCM_SEC_LEV_L1 0x01U
#define DCM_SEC_LEV_ALL 0xFFU

/* Dcm_SesCtrlType */
#define DCM_DEFAULT_SESSION 0x01U
#define DCM_PROGRAMMING_SESSION 0x02U
#define DCM_EXTENDED_DIAGNOSTIC_SESSION 0x03U
#define DCM_SAFETY_SYSTEM_DIAGNOSTIC_SESSION 0x04U
#define DCM_ALL_SESSION_LEVEL 0xFFU

/* Dcm_ProtocolType */
#define DCM_OBD_ON_CAN 0x00U
#define DCM_OBD_ON_FLEXRAY 0x01U
#define DCM_OBD_ON_IP 0x02U
#define DCM_UDS_ON_CAN 0x03U
#define DCM_UDS_ON_FLEXRAY 0x04U
#define DCM_UDS_ON_IP 0x05U
#define DCM_ROE_ON_CAN 0x06U
#define DCM_ROE_ON_FLEXRAY 0x07U
#define DCM_ROE_ON_IP 0x08U
#define DCM_PERIODICTRANS_ON_CAN 0x09U
#define DCM_PERIODICTRANS_ON_FLEXRAY 0x0AU
#define DCM_PERIODICTRANS_ON_IP 0x0BU
#define DCM_SUPPLIER_1 0xF0U
#define DCM_SUPPLIER_2 0xF1U
#define DCM_SUPPLIER_3 0xF2U
#define DCM_SUPPLIER_4 0xF3U
#define DCM_SUPPLIER_5 0xF4U
#define DCM_SUPPLIER_6 0xF5U
#define DCM_SUPPLIER_7 0xF6U
#define DCM_SUPPLIER_8 0xF7U
#define DCM_SUPPLIER_9 0xF8U
#define DCM_SUPPLIER_10 0xF9U
#define DCM_SUPPLIER_11 0xFAU
#define DCM_SUPPLIER_12 0xFBU
#define DCM_SUPPLIER_13 0xFCU
#define DCM_SUPPLIER_14 0xFDU
#define DCM_SUPPLIER_15 0xFEU

/* Dcm_NegativeResponseCodeType */
#define DCM_E_POSITIVERESPONSE 0x00U
#define DCM_E_GENERALREJECT 0x10U
#define DCM_E_SERVICENOTSUPPORTED 0x11U
#define DCM_E_SUBFUNCTIONNOTSUPPORTED 0x12U
#define DCM_E_INCORRECTMESSAGELENGTHORINVALIDFORMAT 0x13U
#define DCM_E_RESPONSETOOLONG 0x14U
#define DCM_E_BUSYREPEATREQUEST 0x21U
#define DCM_E_CONDITIONSNOTCORRECT 0x22U
#define DCM_E_REQUESTSEQUENCEERROR 0x24U
#define DCM_E_NORESPONSEFROMSUBNETCOMPONENT 0x25U
#define DCM_E_FAILUREPREVENTSEXECUTIONOFREQUESTEDACTION 0x26U
#define DCM_E_REQUESTOUTOFRANGE 0x31U
#define DCM_E_SECURITYACCESSDENIED 0x33U
#define DCM_E_INVALIDKEY 0x35U
#define DCM_E_EXCEEDNUMBEROFATTEMPTS 0x36U
#define DCM_E_REQUIREDTIMEDELAYNOTEXPIRED 0x37U
#define DCM_E_UPLOADDOWNLOADNOTACCEPTED 0x70U
#define DCM_E_TRANSFERDATASUSPENDED 0x71U
#define DCM_E_GENERALPROGRAMMINGFAILURE 0x72U
#define DCM_E_WRONGBLOCKSEQUENCECOUNTER 0x73U
#define DCM_E_REQUESTCORRECTLYRECEIVEDRESPONSEPENDING 0x78U
#define DCM_E_SUBFUNCTIONNOTSUPPORTEDINACTIVESESSION 0x7EU
#define DCM_E_SERVICENOTSUPPORTEDINACTIVESESSION 0x7FU
#define DCM_E_RPMTOOHIGH 0x81U
#define DCM_E_RPMTOOLOW 0x82U
#define DCM_E_ENGINEISRUNNING 0x83U
#define DCM_E_ENGINEISNOTRUNNING 0x84U
#define DCM_E_ENGINERUNTIMETOOLOW 0x85U
#define DCM_E_TEMPERATURETOOHIGH 0x86U
#define DCM_E_TEMPERATURETOOLOW 0x87U
#define DCM_E_VEHICLESPEEDTOOHIGH 0x88U
#define DCM_E_VEHICLESPEEDTOOLOW 0x89U
#define DCM_E_THROTTLE_PEDALTOOHIGH 0x8AU
#define DCM_E_THROTTLE_PEDALTOOLOW 0x8BU
#define DCM_E_TRANSMISSIONRANGENOTINNEUTRAL 0x8CU
#define DCM_E_TRANSMISSIONRANGENOTINGEAR 0x8DU
#define DCM_E_BRAKESWITCH_NOTCLOSED 0x8FU
#define DCM_E_SHIFTERLEVERNOTINPARK 0x90U
#define DCM_E_TORQUECONVERTERCLUTCHLOCKED 0x91U
#define DCM_E_VOLTAGETOOHIGH 0x92U
#define DCM_E_VOLTAGETOOLOW 0x93U

/* Dcm_CommunicationModeType */
#define DCM_ENABLE_RX_TX_NORM 0x00U
#define DCM_ENABLE_RX_DISABLE_TX_NORM 0x01U
#define DCM_DISABLE_RX_ENABLE_TX_NORM 0x02U
#define DCM_DISABLE_RX_TX_NORMAL 0x03U
#define DCM_ENABLE_RX_TX_NM 0x04U
#define DCM_ENABLE_RX_DISABLE_TX_NM 0x05U
#define DCM_DISABLE_RX_ENABLE_TX_NM 0x06U
#define DCM_DISABLE_RX_TX_NM 0x07U
#define DCM_ENABLE_RX_TX_NORM_NM 0x08U
#define DCM_ENABLE_RX_DISABLE_TX_NORM_NM 0x09U
#define DCM_DISABLE_RX_ENABLE_TX_NORM_NM 0x0AU
#define DCM_DISABLE_RX_TX_NORM_NM 0x0BU

/* Dcm_ConfirmationStatusType */
#define DCM_RES_POS_OK 0x00U
#define DCM_RES_POS_NOT_OK 0x01U
#define DCM_RES_NEG_OK 0x02U
#define DCM_RES_NEG_NOT_OK 0x03U

/* Dcm_OpStatusType */
#define DCM_INITIAL 0x00U
#define DCM_PENDING 0x01U
#define DCM_CANCEL 0x02U
#define DCM_FORCE_RCRRP_OK 0x03U

/* Dcm_ReturnReadMemoryType */
#define DCM_READ_OK 0x00U
#define DCM_READ_PENDING 0x01U
#define DCM_READ_FAILED 0x02U

/* Dcm_ReturnWriteMemoryType */
#define DCM_WRITE_OK 0x00U
#define DCM_WRITE_PENDING 0x01U
#define DCM_WRITE_FAILED 0x02U

/* Dcm_RoeStateType */
#define DCM_ROE_ACTIVE 0x00U
#define DCM_ROE_UNACTIVE 0x01U

/* Dcm_EcuStartModeType */
#define DCM_COLD_START 0x00U
#define DCM_WARM_START 0x01U

/* Dcm_ResetModeType */
#define DCM_NO_RESET 0x00U
#define DCM_HARD_RESET 0x01U
#define DCM_KEY_ON_OFF_RESET 0x02U
#define DCM_SOFT_RESET 0x03U
#define DCM_ENABLE_RAPID_POWER_SHUTDOWN_RESET 0x04U
#define DCM_DISABLE_RAPID_POWER_SHUTDOWN_RESET 0x05U
#define DCM_BOOTLOADER_RESET 0x06U
#define DCM_SS_BOOTLOADER_RESET 0x07U
#define DCM_RESET_EXECUTION 0x08U

/*==[Types]===================================================================*/

typedef uint8 Dcm_StatusType;

typedef uint8 Dcm_SecLevelType;

typedef uint8 Dcm_SesCtrlType;

typedef uint8 Dcm_ProtocolType;

typedef uint8 Dcm_NegativeResponseCodeType;

typedef uint8 Dcm_CommunicationModeType;

typedef struct
{
   uint8 Dummy;
} Dcm_ConfigType;

typedef uint8 Dcm_ConfirmationStatusType;

typedef uint8 Dcm_OpStatusType;

typedef uint8 Dcm_ReturnReadMemoryType;

typedef uint8 Dcm_ReturnWriteMemoryType;

typedef uint8 Dcm_RoeStateType;

typedef uint8 Dcm_EcuStartModeType;

typedef struct
{
   uint8 ProtocolId;
   uint8 TesterSourceAddr;
   uint8 Sid;
   uint8 SubFncId;
} Dcm_ProgConditionsType;

typedef uint8 Dcm_MsgItemType;

typedef Dcm_MsgItemType* Dcm_MsgType;

typedef uint32 Dcm_MsgLenType;

typedef struct
{
   unsigned int reqType:1;
   unsigned int suppressPosResponse:1;
   unsigned int cancelOperation:1;
} Dcm_MsgAddInfoType;

typedef uint8 Dcm_IdContextType;

typedef struct
{
   Dcm_MsgType reqData;
   Dcm_MsgLenType reqDataLen;
   Dcm_MsgType resData;
   Dcm_MsgLenType resDataLen;
   Dcm_MsgAddInfoType msgAddInfo;
   Dcm_MsgLenType resMaxDataLen;
   Dcm_IdContextType idContext;
   PduIdType dcmRxPduId;
} Dcm_MsgContextType;

typedef uint8 Dcm_ResetModeType;

/*==[Declaration of functions with external linkage]==========================*/

#define EBSTUBS_START_SEC_CODE
#include <EBStubs_MemMap.h>

#define EBSTUBS_STOP_SEC_CODE
#include <EBStubs_MemMap.h>

/*==[Constants with external linkage]=========================================*/

/*==[Variables with external linkage]=========================================*/

#define EBSTUBS_START_SEC_VAR_NO_INIT_UNSPECIFIED
#include <EBStubs_MemMap.h>


#define EBSTUBS_STOP_SEC_VAR_NO_INIT_UNSPECIFIED
#include <EBStubs_MemMap.h>

/* stub extension header file */
#include <Dcm_StubExt.h>

#endif /* !defined DCM_TYPES_H */
