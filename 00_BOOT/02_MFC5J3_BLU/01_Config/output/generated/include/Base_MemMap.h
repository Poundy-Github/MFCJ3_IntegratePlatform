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

#define MEMMAP_ERROR_BASE

/*------------------[Start of a module]--------------------------------------*/

/* Memory section macros for Base */

#if (defined BASE_START_SEC_CODE)
  #undef BASE_START_SEC_CODE
  #undef MEMMAP_ERROR_BASE
#elif (defined BASE_STOP_SEC_CODE)
  #undef BASE_STOP_SEC_CODE
  #undef MEMMAP_ERROR_BASE

#endif

#if ((!defined MEMMAP_ERROR_BASE) && (defined MEMMAP_ERROR))
  #undef MEMMAP_ERROR
#elif ((defined MEMMAP_ERROR_BASE) && (!defined MEMMAP_ERROR))
  #undef MEMMAP_ERROR_BASE
  #error MEMMAP_ERROR_BASE the included memory section was not defined within the BSW-IMPLEMENTATION of Base.
#endif
