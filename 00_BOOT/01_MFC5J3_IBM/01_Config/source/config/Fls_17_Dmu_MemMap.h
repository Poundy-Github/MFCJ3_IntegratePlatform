/**
 * \file
 *
 * \brief AUTOSAR MemMap
 *
 * This file contains the implementation of the AUTOSAR
 * module MemMap.
 *
 * \author Elektrobit Automotive GmbH, 91058 Erlangen, Germany
 *
 * Copyright 2005 - 2019 Elektrobit Automotive GmbH
 * All rights exclusively reserved for Elektrobit Automotive GmbH,
 * unless expressly agreed to otherwise.
 */

/*==================[inclusions]=============================================*/

#define MEMMAP_ERROR_FLS_17_DMU

/*------------------[Start of a module]--------------------------------------*/

/* Memory section macros for Fls_17_Dmu */

#if (defined FLS_17_DMU_START_SEC_CODE_ASIL_B_LOCAL)
  #undef FLS_17_DMU_START_SEC_CODE_ASIL_B_LOCAL
  #undef MEMMAP_ERROR_FLS_17_DMU
#elif (defined FLS_17_DMU_STOP_SEC_CODE_ASIL_B_LOCAL)
  #undef FLS_17_DMU_STOP_SEC_CODE_ASIL_B_LOCAL
  #undef MEMMAP_ERROR_FLS_17_DMU

#elif (defined FLS_17_DMU_START_SEC_CONFIG_DATA_ASIL_B_LOCAL_UNSPECIFIED)
  #undef FLS_17_DMU_START_SEC_CONFIG_DATA_ASIL_B_LOCAL_UNSPECIFIED
  #undef MEMMAP_ERROR_FLS_17_DMU
#elif (defined FLS_17_DMU_STOP_SEC_CONFIG_DATA_ASIL_B_LOCAL_UNSPECIFIED)
  #undef FLS_17_DMU_STOP_SEC_CONFIG_DATA_ASIL_B_LOCAL_UNSPECIFIED
  #undef MEMMAP_ERROR_FLS_17_DMU

#elif (defined FLS_17_DMU_START_SEC_VAR_CLEARED_ASIL_B_LOCAL_UNSPECIFIED)
  #undef FLS_17_DMU_START_SEC_VAR_CLEARED_ASIL_B_LOCAL_UNSPECIFIED
  #undef MEMMAP_ERROR_FLS_17_DMU
#elif (defined FLS_17_DMU_STOP_SEC_VAR_CLEARED_ASIL_B_LOCAL_UNSPECIFIED)
  #undef FLS_17_DMU_STOP_SEC_VAR_CLEARED_ASIL_B_LOCAL_UNSPECIFIED
  #undef MEMMAP_ERROR_FLS_17_DMU

#elif (defined FLS_17_DMU_START_SEC_VAR_CLEARED_ASIL_B_LOCAL_32)
  #undef FLS_17_DMU_START_SEC_VAR_CLEARED_ASIL_B_LOCAL_32
  #undef MEMMAP_ERROR_FLS_17_DMU
#elif (defined FLS_17_DMU_STOP_SEC_VAR_CLEARED_ASIL_B_LOCAL_32)
  #undef FLS_17_DMU_STOP_SEC_VAR_CLEARED_ASIL_B_LOCAL_32
  #undef MEMMAP_ERROR_FLS_17_DMU
#endif

#if ((!defined MEMMAP_ERROR_FLS_17_DMU) && (defined MEMMAP_ERROR))
  #undef MEMMAP_ERROR
#elif ((defined MEMMAP_ERROR_FLS_17_DMU) && (!defined MEMMAP_ERROR))
  #undef MEMMAP_ERROR_FLS_17_DMU
  #error MEMMAP_ERROR_FLS_17_DMU the included memory section was not defined within the BSW-IMPLEMENTATION of Fls_17_Dmu.
#endif
