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
 * Copyright 2005 - 2018 Elektrobit Automotive GmbH
 * All rights exclusively reserved for Elektrobit Automotive GmbH,
 * unless expressly agreed to otherwise.
 */

/*==================[inclusions]=============================================*/

#define MEMMAP_ERROR_SCHM

/*------------------[Start of a module]--------------------------------------*/

/* Memory section macros for SchM */

#if (defined SCHM_START_SEC_VAR_UNSPECIFIED)
    #undef SCHM_START_SEC_VAR_UNSPECIFIED
    #undef MEMMAP_ERROR_SCHM
#elif (defined SCHM_STOP_SEC_VAR_UNSPECIFIED)
    #undef SCHM_STOP_SEC_VAR_UNSPECIFIED
    #undef MEMMAP_ERROR_SCHM

#elif (defined SCHM_START_SEC_CODE)
    #undef SCHM_START_SEC_CODE
    #undef MEMMAP_ERROR_SCHM
#elif (defined SCHM_STOP_SEC_CODE)
    #undef SCHM_STOP_SEC_CODE
    #undef MEMMAP_ERROR_SCHM

#endif

#if ((!defined MEMMAP_ERROR_SCHM) && (defined MEMMAP_ERROR))
  #undef MEMMAP_ERROR
#elif ((defined MEMMAP_ERROR_SCHM) && (!defined MEMMAP_ERROR))
  #undef MEMMAP_ERROR_SCHM
  #error MEMMAP_ERROR_SCHM the included memory section was not defined within the BSW-IMPLEMENTATION of SchM.
#endif
