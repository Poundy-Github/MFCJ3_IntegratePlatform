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

#define MEMMAP_ERROR_RESOURCEM

/*------------------[Start of a module]--------------------------------------*/

/* Memory section macros for ResourceM */

#if (defined RESOURCEM_START_SEC_CODE)
  #undef RESOURCEM_START_SEC_CODE
  #undef MEMMAP_ERROR_RESOURCEM
#elif (defined RESOURCEM_STOP_SEC_CODE)
  #undef RESOURCEM_STOP_SEC_CODE
  #undef MEMMAP_ERROR_RESOURCEM

#endif

#if ((!defined MEMMAP_ERROR_RESOURCEM) && (defined MEMMAP_ERROR))
  #undef MEMMAP_ERROR
#elif ((defined MEMMAP_ERROR_RESOURCEM) && (!defined MEMMAP_ERROR))
  #undef MEMMAP_ERROR_RESOURCEM
  #error MEMMAP_ERROR_RESOURCEM the included memory section was not defined within the BSW-IMPLEMENTATION of ResourceM.
#endif
