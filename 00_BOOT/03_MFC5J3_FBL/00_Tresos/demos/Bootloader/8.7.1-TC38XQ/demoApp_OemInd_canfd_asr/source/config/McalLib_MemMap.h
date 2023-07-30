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

#define MEMMAP_ERROR_MCALLIB

/*------------------[Start of a module]--------------------------------------*/

/* Memory section macros for McalLib */

#if (defined MCALLIB_START_SEC_CODE_ASIL_B_GLOBAL)
  #undef MCALLIB_START_SEC_CODE_ASIL_B_GLOBAL
  #undef MEMMAP_ERROR_MCALLIB
#elif (defined MCALLIB_STOP_SEC_CODE_ASIL_B_GLOBAL)
  #undef MCALLIB_STOP_SEC_CODE_ASIL_B_GLOBAL
  #undef MEMMAP_ERROR_MCALLIB

#elif (defined MCALLIB_START_SEC_CONST_ASIL_B_GLOBAL_32)
  #undef MCALLIB_START_SEC_CONST_ASIL_B_GLOBAL_32
  #undef MEMMAP_ERROR_MCALLIB
#elif (defined MCALLIB_STOP_SEC_CONST_ASIL_B_GLOBAL_32)
  #undef MCALLIB_STOP_SEC_CONST_ASIL_B_GLOBAL_32
  #undef MEMMAP_ERROR_MCALLIB

#elif (defined MCALLIB_START_SEC_CONST_ASIL_B_GLOBAL_8)
  #undef MCALLIB_START_SEC_CONST_ASIL_B_GLOBAL_8
  #undef MEMMAP_ERROR_MCALLIB
#elif (defined MCALLIB_STOP_SEC_CONST_ASIL_B_GLOBAL_8)
  #undef MCALLIB_STOP_SEC_CONST_ASIL_B_GLOBAL_8
  #undef MEMMAP_ERROR_MCALLIB

#elif (defined MCALLIB_START_SEC_VAR_CLEARED_ASIL_B_GLOBAL_32)
  #undef MCALLIB_START_SEC_VAR_CLEARED_ASIL_B_GLOBAL_32
  #undef MEMMAP_ERROR_MCALLIB
#elif (defined MCALLIB_STOP_SEC_VAR_CLEARED_ASIL_B_GLOBAL_32)
  #undef MCALLIB_STOP_SEC_VAR_CLEARED_ASIL_B_GLOBAL_32
  #undef MEMMAP_ERROR_MCALLIB

#endif

#if ((!defined MEMMAP_ERROR_MCALLIB) && (defined MEMMAP_ERROR))
  #undef MEMMAP_ERROR
#elif ((defined MEMMAP_ERROR_MCALLIB) && (!defined MEMMAP_ERROR))
  #undef MEMMAP_ERROR_MCALLIB
  #error MEMMAP_ERROR_MCALLIB the included memory section was not defined within the BSW-IMPLEMENTATION of McalLib.
#endif
