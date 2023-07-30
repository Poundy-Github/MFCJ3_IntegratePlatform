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

#define MEMMAP_ERROR_PORT

/*------------------[Start of a module]--------------------------------------*/

/* Memory section macros for Port */

#if (defined PORT_START_SEC_CODE_ASIL_B_GLOBAL)
  #undef PORT_START_SEC_CODE_ASIL_B_GLOBAL
  #undef MEMMAP_ERROR_PORT
#elif (defined PORT_STOP_SEC_CODE_ASIL_B_GLOBAL)
  #undef PORT_STOP_SEC_CODE_ASIL_B_GLOBAL
  #undef MEMMAP_ERROR_PORT

#elif (defined PORT_START_SEC_CONFIG_DATA_ASIL_B_GLOBAL_UNSPECIFIED)
  #undef PORT_START_SEC_CONFIG_DATA_ASIL_B_GLOBAL_UNSPECIFIED
  #undef MEMMAP_ERROR_PORT
#elif (defined PORT_STOP_SEC_CONFIG_DATA_ASIL_B_GLOBAL_UNSPECIFIED)
  #undef PORT_STOP_SEC_CONFIG_DATA_ASIL_B_GLOBAL_UNSPECIFIED
  #undef MEMMAP_ERROR_PORT

#elif (defined PORT_START_SEC_CONST_ASIL_B_GLOBAL_16)
  #undef PORT_START_SEC_CONST_ASIL_B_GLOBAL_16
  #undef MEMMAP_ERROR_PORT
#elif (defined PORT_STOP_SEC_CONST_ASIL_B_GLOBAL_16)
  #undef PORT_STOP_SEC_CONST_ASIL_B_GLOBAL_16
  #undef MEMMAP_ERROR_PORT

#elif (defined PORT_START_SEC_VAR_CLEARED_ASIL_B_GLOBAL_32)
  #undef PORT_START_SEC_VAR_CLEARED_ASIL_B_GLOBAL_32
  #undef MEMMAP_ERROR_PORT
#elif (defined PORT_STOP_SEC_VAR_CLEARED_ASIL_B_GLOBAL_32)
  #undef PORT_STOP_SEC_VAR_CLEARED_ASIL_B_GLOBAL_32
  #undef MEMMAP_ERROR_PORT

#elif (defined PORT_START_SEC_VAR_CLEARED_ASIL_B_GLOBAL_8)
  #undef PORT_START_SEC_VAR_CLEARED_ASIL_B_GLOBAL_8
  #undef MEMMAP_ERROR_PORT
#elif (defined PORT_STOP_SEC_VAR_CLEARED_ASIL_B_GLOBAL_8)
  #undef PORT_STOP_SEC_VAR_CLEARED_ASIL_B_GLOBAL_8
  #undef MEMMAP_ERROR_PORT

#endif

#if ((!defined MEMMAP_ERROR_PORT) && (defined MEMMAP_ERROR))
  #undef MEMMAP_ERROR
#elif ((defined MEMMAP_ERROR_PORT) && (!defined MEMMAP_ERROR))
  #undef MEMMAP_ERROR_PORT
  #error MEMMAP_ERROR_PORT the included memory section was not defined within the BSW-IMPLEMENTATION of Port.
#endif
