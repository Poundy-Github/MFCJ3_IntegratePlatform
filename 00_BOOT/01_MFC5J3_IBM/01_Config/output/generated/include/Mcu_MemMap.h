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

#define MEMMAP_ERROR_MCU

/*------------------[Start of a module]--------------------------------------*/

/* Memory section macros for Mcu */

#if (defined MCU_START_SEC_CODE_ASIL_B_GLOBAL)
  #undef MCU_START_SEC_CODE_ASIL_B_GLOBAL
  #undef MEMMAP_ERROR_MCU
#elif (defined MCU_STOP_SEC_CODE_ASIL_B_GLOBAL)
  #undef MCU_STOP_SEC_CODE_ASIL_B_GLOBAL
  #undef MEMMAP_ERROR_MCU

#elif (defined MCU_START_SEC_CONFIG_DATA_ASIL_B_GLOBAL_UNSPECIFIED)
  #undef MCU_START_SEC_CONFIG_DATA_ASIL_B_GLOBAL_UNSPECIFIED
  #undef MEMMAP_ERROR_MCU
#elif (defined MCU_STOP_SEC_CONFIG_DATA_ASIL_B_GLOBAL_UNSPECIFIED)
  #undef MCU_STOP_SEC_CONFIG_DATA_ASIL_B_GLOBAL_UNSPECIFIED
  #undef MEMMAP_ERROR_MCU

#elif (defined MCU_START_SEC_VAR_CLEARED_ASIL_B_GLOBAL_32)
  #undef MCU_START_SEC_VAR_CLEARED_ASIL_B_GLOBAL_32
  #undef MEMMAP_ERROR_MCU
#elif (defined MCU_STOP_SEC_VAR_CLEARED_ASIL_B_GLOBAL_32)
  #undef MCU_STOP_SEC_VAR_CLEARED_ASIL_B_GLOBAL_32
  #undef MEMMAP_ERROR_MCU

#elif (defined MCU_17_TIMERIP_START_SEC_CODE_ASIL_B_GLOBAL)
  #undef MCU_17_TIMERIP_START_SEC_CODE_ASIL_B_GLOBAL
  #undef MEMMAP_ERROR_MCU
#elif (defined MCU_17_TIMERIP_STOP_SEC_CODE_ASIL_B_GLOBAL)
  #undef MCU_17_TIMERIP_STOP_SEC_CODE_ASIL_B_GLOBAL
  #undef MEMMAP_ERROR_MCU

#elif (defined MCU_17_TIMERIP_START_SEC_CODE_FAST_ASIL_B_GLOBAL)
  #undef MCU_17_TIMERIP_START_SEC_CODE_FAST_ASIL_B_GLOBAL
  #undef MEMMAP_ERROR_MCU
#elif (defined MCU_17_TIMERIP_STOP_SEC_CODE_FAST_ASIL_B_GLOBAL)
  #undef MCU_17_TIMERIP_STOP_SEC_CODE_FAST_ASIL_B_GLOBAL
  #undef MEMMAP_ERROR_MCU

#elif (defined MCU_17_TIMERIP_START_SEC_CONFIG_DATA_ASIL_B_GLOBAL_16)
  #undef MCU_17_TIMERIP_START_SEC_CONFIG_DATA_ASIL_B_GLOBAL_16
  #undef MEMMAP_ERROR_MCU
#elif (defined MCU_17_TIMERIP_STOP_SEC_CONFIG_DATA_ASIL_B_GLOBAL_16)
  #undef MCU_17_TIMERIP_STOP_SEC_CONFIG_DATA_ASIL_B_GLOBAL_16
  #undef MEMMAP_ERROR_MCU

#elif (defined MCU_17_TIMERIP_START_SEC_CONFIG_DATA_ASIL_B_GLOBAL_32)
  #undef MCU_17_TIMERIP_START_SEC_CONFIG_DATA_ASIL_B_GLOBAL_32
  #undef MEMMAP_ERROR_MCU
#elif (defined MCU_17_TIMERIP_STOP_SEC_CONFIG_DATA_ASIL_B_GLOBAL_32)
  #undef MCU_17_TIMERIP_STOP_SEC_CONFIG_DATA_ASIL_B_GLOBAL_32
  #undef MEMMAP_ERROR_MCU

#elif (defined MCU_17_TIMERIP_START_SEC_CONST_ASIL_B_GLOBAL_UNSPECIFIED)
  #undef MCU_17_TIMERIP_START_SEC_CONST_ASIL_B_GLOBAL_UNSPECIFIED
  #undef MEMMAP_ERROR_MCU
#elif (defined MCU_17_TIMERIP_STOP_SEC_CONST_ASIL_B_GLOBAL_UNSPECIFIED)
  #undef MCU_17_TIMERIP_STOP_SEC_CONST_ASIL_B_GLOBAL_UNSPECIFIED
  #undef MEMMAP_ERROR_MCU

#elif (defined MCU_17_TIMERIP_START_SEC_VAR_INIT_ASIL_B_GLOBAL_32)
  #undef MCU_17_TIMERIP_START_SEC_VAR_INIT_ASIL_B_GLOBAL_32
  #undef MEMMAP_ERROR_MCU
#elif (defined MCU_17_TIMERIP_STOP_SEC_VAR_INIT_ASIL_B_GLOBAL_32)
  #undef MCU_17_TIMERIP_STOP_SEC_VAR_INIT_ASIL_B_GLOBAL_32
  #undef MEMMAP_ERROR_MCU

#elif (defined MCU_17_TIMERIP_START_SEC_VAR_INIT_ASIL_B_GLOBAL_UNSPECIFIED)
  #undef MCU_17_TIMERIP_START_SEC_VAR_INIT_ASIL_B_GLOBAL_UNSPECIFIED
  #undef MEMMAP_ERROR_MCU
#elif (defined MCU_17_TIMERIP_STOP_SEC_VAR_INIT_ASIL_B_GLOBAL_UNSPECIFIED)
  #undef MCU_17_TIMERIP_STOP_SEC_VAR_INIT_ASIL_B_GLOBAL_UNSPECIFIED
  #undef MEMMAP_ERROR_MCU

#endif

#if ((!defined MEMMAP_ERROR_MCU) && (defined MEMMAP_ERROR))
  #undef MEMMAP_ERROR
#elif ((defined MEMMAP_ERROR_MCU) && (!defined MEMMAP_ERROR))
  #undef MEMMAP_ERROR_MCU
  #error MEMMAP_ERROR_MCU the included memory section was not defined within the BSW-IMPLEMENTATION of Mcu.
#endif