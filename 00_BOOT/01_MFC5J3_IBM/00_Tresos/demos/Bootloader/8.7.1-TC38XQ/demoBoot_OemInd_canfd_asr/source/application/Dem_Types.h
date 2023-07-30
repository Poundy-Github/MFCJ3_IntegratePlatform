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

#if (!defined DEM_TYPES_H)
#define DEM_TYPES_H

/*==[Includes]================================================================*/

#include <Dem_StubCfg.h>
#include <Std_Types.h>

/*==[Macros]==================================================================*/

/* Dem_EventStatusType */
#define DEM_EVENT_STATUS_PASSED 0x00U
#define DEM_EVENT_STATUS_FAILED 0x01U
#define DEM_EVENT_STATUS_PREPASSED 0x02U
#define DEM_EVENT_STATUS_PREFAILED 0x03U

/* Dem_EventStatusExtendedType */
#define DEM_UDS_STATUS_TF 0x01U
#define DEM_UDS_STATUS_TFTOC 0x02U
#define DEM_UDS_STATUS_PDTC 0x04U
#define DEM_UDS_STATUS_CDTC 0x08U
#define DEM_UDS_STATUS_TNCSLC 0x10U
#define DEM_UDS_STATUS_TFSLC 0x20U
#define DEM_UDS_STATUS_TNCTOC 0x40U
#define DEM_UDS_STATUS_WIR 0x80U

/* Dem_OperationCycleStateType */
#define DEM_CYCLE_STATE_START 0x00U
#define DEM_CYCLE_STATE_END 0x01U

/* Dem_IndicatorStatusType */
#define DEM_INDICATOR_OFF 0x00U
#define DEM_INDICATOR_CONTINUOUS 0x01U
#define DEM_INDICATOR_BLINKING 0x02U
#define DEM_INDICATOR_BLINK_CONT 0x03U

/* Dem_DTCGroupType */
#define DEM_DTC_GROUP_EMISSION_REL_DTCS 0x00000000U
#define DEM_DTC_GROUP_BODY_DTCS 0x0000000EU
#define DEM_DTC_GROUP_CHASSIS_DTCS 0x0000000CU
#define DEM_DTC_GROUP_NETWORK_COM_DTCS 0x0000000BU
#define DEM_DTC_GROUP_POWERTRAIN_DTCS 0x0000000AU
#define DEM_DTC_GROUP_ALL_DTCS 0xffffffU

/* Dem_DTCKindType */
#define DEM_DTC_KIND_ALL_DTCS 0x01U
#define DEM_DTC_KIND_EMISSION_REL_DTCS 0x02U

/* Dem_DTCFormatType */
#define DEM_DTC_FORMAT_OBD 0x00U
#define DEM_DTC_FORMAT_UDS 0x01U

/* Dem_DTCOriginType */
#define DEM_DTC_ORIGIN_PRIMARY_MEMORY 0x01U
#define DEM_DTC_ORIGIN_MIRROR_MEMORY 0x02U
#define DEM_DTC_ORIGIN_PERMANENT_MEMORY 0x03U
#define DEM_DTC_ORIGIN_SECONDARY_MEMORY 0x04U

/* Dem_DTCRequestType */
#define DEM_FIRST_FAILED_DTC 0x01U
#define DEM_MOST_RECENT_FAILED_DTC 0x02U
#define DEM_FIRST_DET_CONFIRMED_DTC 0x03U
#define DEM_MOST_REC_DET_CONFIRMED_DTC 0x04U

/* Dem_DTCTranslationFormatType */
#define DEM_DTC_TRANSLATION_ISO15031_6 0x00U
#define DEM_DTC_TRANSLATION_ISO14229_1 0x01U
#define DEM_DTC_TRANSLATION_SAEJ1939_73 0x02U
#define DEM_DTC_TRANSLATION_ISO11992_4 0x03U

/* Dem_DTCSeverityType */
#define DEM_SEVERITY_NO_SEVERITY 0x00U
#define DEM_SEVERITY_MAINTENANCE_ONLY 0x20U
#define DEM_SEVERITY_CHECK_AT_NEXT_HALT 0x40U
#define DEM_SEVERITY_CHECK_IMMEDIATELY 0x80U

/* Dem_FilterForFDCType */
#define DEM_FILTER_FOR_FDC_YES 0x00U
#define DEM_FILTER_FOR_FDC_NO 0x01U

/* Dem_FilterWithSeverityType */
#define DEM_FILTER_WITH_SEVERITY_YES 0x00U
#define DEM_FILTER_WITH_SEVERITY_NO 0x01U

/* Dem_InitMonitorReasonType */
#define DEM_INIT_MONITOR_CLEAR 0x01U
#define DEM_INIT_MONITOR_RESTART 0x02U

/* Dem_ReturnSetFilterType */
#define DEM_FILTER_ACCEPTED 0x00U
#define DEM_WRONG_FILTER 0x01U

/* Dem_ReturnGetStatusOfDTCType */
#define DEM_STATUS_OK 0x00U
#define DEM_STATUS_WRONG_DTC 0x01U
#define DEM_STATUS_WRONG_DTCORIGIN 0x02U
#define DEM_STATUS_FAILED 0x03U
#define DEM_STATUS_PENDING 0x04U

/* Dem_ReturnGetNextFilteredDTCType */
#define DEM_FILTERED_OK 0x00U
#define DEM_FILTERED_NO_MATCHING_DTC 0x01U
#define DEM_FILTERED_PENDING 0x02U

/* Dem_ReturnGetNumberOfFilteredDTCType */
#define DEM_NUMBER_OK 0x00U
#define DEM_NUMBER_FAILED 0x01U
#define DEM_NUMBER_PENDING 0x02U

/* Dem_ReturnClearDTCType */
#define DEM_CLEAR_OK 0x00U
#define DEM_CLEAR_WRONG_DTC 0x01U
#define DEM_CLEAR_WRONG_DTCORIGIN 0x02U
#define DEM_CLEAR_FAILED 0x03U
#define DEM_CLEAR_PENDING 0x04U

/* Dem_ReturnControlDTCSettingType */
#define DEM_CONTROL_DTC_SETTING_OK 0x00U
#define DEM_CONTROL_DTC_SETTING_N_OK 0x01U
#define DEM_CONTROL_DTC_WRONG_DTCGROUP 0x02U

/* Dem_ReturnDisableDTCRecordUpdateType */
#define DEM_DISABLE_DTCRECUP_OK 0x00U
#define DEM_DISABLE_DTCRECUP_WRONG_DTC 0x01U
#define DEM_DISABLE_DTCRECUP_WRONG_DTCORIGIN 0x02U
#define DEM_DISABLE_DTCRECUP_PENDING 0x03U

/* Dem_ReturnGetFreezeFrameDataByRecordType */
#define DEM_GET_FFBYRECORD_OK 0x00U
#define DEM_GET_FFBYRECORD_WRONG_RECORD 0x01U
#define DEM_GET_FFBYRECORD_NO_DTC_FOR_RECORD 0x02U

/* Dem_ReturnGetExtendedDataRecordByDTCType */
#define DEM_RECORD_OK 0x00U
#define DEM_RECORD_WRONG_DTC 0x01U
#define DEM_RECORD_WRONG_DTCORIGIN 0x02U
#define DEM_RECORD_WRONG_NUMBER 0x03U
#define DEM_RECORD_WRONG_BUFFERSIZE 0x04U
#define DEM_RECORD_PENDING 0x05U

/* Dem_ReturnGetDTCByOccurrenceTimeType */
#define DEM_OCCURR_OK 0x00U
#define DEM_OCCURR_NOT_AVAILABLE 0x01U

/* Dem_ReturnGetFreezeFrameDataByDTCType */
#define DEM_GET_FFDATABYDTC_OK 0x00U
#define DEM_GET_FFDATABYDTC_WRONG_DTC 0x01U
#define DEM_GET_FFDATABYDTC_WRONG_DTCORIGIN 0x02U
#define DEM_GET_FFDATABYDTC_WRONG_RECORDNUMBER 0x03U
#define DEM_GET_FFDATABYDTC_WRONG_BUFFERSIZE 0x04U
#define DEM_GET_FFDATABYDTC_PENDING 0x05U

/* Dem_ReturnGetSizeOfExtendedDataRecordByDTCType */
#define DEM_GET_SIZEOFEDRBYDTC_OK 0x00U
#define DEM_GET_SIZEOFEDRBYDTC_W_DTC 0x01U
#define DEM_GET_SIZEOFEDRBYDTC_W_DTCOR 0x02U
#define DEM_GET_SIZEOFEDRBYDTC_W_RNUM 0x03U
#define DEM_GET_SIZEOFEDRBYDTC_PENDING 0x04U

/* Dem_ReturnGetSizeOfFreezeFrameByDTCType */
#define DEM_GET_SIZEOFFF_OK 0x00U
#define DEM_GET_SIZEOFFF_WRONG_DTC 0x01U
#define DEM_GET_SIZEOFFF_WRONG_DTCOR 0x02U
#define DEM_GET_SIZEOFFF_WRONG_RNUM 0x03U
#define DEM_GET_SIZEOFFF_PENDING 0x04U

/* Dem_ReturnGetSeverityOfDTCType */
#define DEM_GET_SEVERITYOFDTC_OK 0x00U
#define DEM_GET_SEVERITYOFDTC_WRONG_DTC 0x01U
#define DEM_GET_SEVERITYOFDTC_NOSEVERITY 0x02U
#define DEM_GET_SEVERITYOFDTC_PENDING 0x03U

/* Dem_ReturnGetFunctionalUnitOfDTCType */
#define DEM_GET_SEVERITYOFDTC_OK 0x00U
#define DEM_GET_SEVERITYOFDTC_WRONG_DTC 0x01U

/* Dem_DataKindType */
#define DEM_DATAKIND_FREEZEFRAME 0x00U
#define DEM_DATAKIND_EXTENDEDDATA 0x01U

/* Dem_UdsStatusByteType */
#define DEM_UDS_STATUS_TF 0x01U
#define DEM_UDS_STATUS_TFTOC 0x02U
#define DEM_UDS_STATUS_PDTC 0x04U
#define DEM_UDS_STATUS_CDTC 0x08U
#define DEM_UDS_STATUS_TNCSLC 0x10U
#define DEM_UDS_STATUS_TFSLC 0x20U
#define DEM_UDS_STATUS_TNCTOC 0x40U
#define DEM_UDS_STATUS_WIR 0x80U

/*==[Types]===================================================================*/

typedef struct
{
   uint8 Dummy;
} Dem_ConfigType;

typedef uint16 Dem_EventIdType;

typedef uint8 Dem_EventStatusType;

typedef uint8 Dem_EventStatusExtendedType;

typedef uint8 Dem_OperationCycleStateType;

typedef uint8 Dem_IndicatorStatusType;

typedef uint32 Dem_DTCGroupType;

typedef uint8 Dem_DTCKindType;

typedef uint8 Dem_DTCFormatType;

typedef uint8 Dem_DTCOriginType;

typedef uint8 Dem_DTCRequestType;

typedef uint8 Dem_DTCTranslationFormatType;

typedef uint8 Dem_DTCSeverityType;

typedef uint8 Dem_FilterForFDCType;

typedef uint8 Dem_FilterWithSeverityType;

typedef uint8 Dem_RatioIdType;

typedef uint8 Dem_InitMonitorReasonType;

typedef uint8 Dem_ReturnSetFilterType;

typedef uint8 Dem_ReturnGetStatusOfDTCType;

typedef uint8 Dem_ReturnGetNextFilteredDTCType;

typedef uint8 Dem_ReturnGetNumberOfFilteredDTCType;

typedef uint8 Dem_ReturnClearDTCType;

typedef uint8 Dem_ReturnControlDTCSettingType;

typedef uint8 Dem_ReturnDisableDTCRecordUpdateType;

typedef uint8 Dem_ReturnGetFreezeFrameDataByRecordType;

typedef uint8 Dem_ReturnGetExtendedDataRecordByDTCType;

typedef uint8 Dem_ReturnGetDTCByOccurrenceTimeType;

typedef uint8 Dem_ReturnGetFreezeFrameDataByDTCType;

typedef uint8 Dem_ReturnGetSizeOfExtendedDataRecordByDTCType;

typedef uint8 Dem_ReturnGetSizeOfFreezeFrameByDTCType;

typedef uint8 Dem_ReturnGetSeverityOfDTCType;

typedef uint8 Dem_ReturnGetFunctionalUnitOfDTCType;

typedef uint8 Dem_DataKindType;

typedef uint32 Dem_DTCType;

typedef uint8 Dem_UdsStatusByteType;

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
#include <Dem_StubExt.h>

#endif /* !defined DEM_TYPES_H */
