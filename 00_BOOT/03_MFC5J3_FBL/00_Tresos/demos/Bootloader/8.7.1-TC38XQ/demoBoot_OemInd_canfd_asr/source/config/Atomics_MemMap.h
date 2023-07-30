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

#define MEMMAP_ERROR_ATOMICS

/*------------------[Start of a module]--------------------------------------*/

/* Memory section macros for Atomics */

#if (defined ATOMICS_START_SEC_CODE)
  #undef ATOMICS_START_SEC_CODE
  #undef MEMMAP_ERROR_ATOMICS
#elif (defined ATOMICS_STOP_SEC_CODE)
  #undef ATOMICS_STOP_SEC_CODE
  #undef MEMMAP_ERROR_ATOMICS

#endif

#if ((!defined MEMMAP_ERROR_ATOMICS) && (defined MEMMAP_ERROR))
  #undef MEMMAP_ERROR
#elif ((defined MEMMAP_ERROR_ATOMICS) && (!defined MEMMAP_ERROR))
  #undef MEMMAP_ERROR_ATOMICS
  #error MEMMAP_ERROR_ATOMICS the included memory section was not defined within the BSW-IMPLEMENTATION of Atomics.
#endif
