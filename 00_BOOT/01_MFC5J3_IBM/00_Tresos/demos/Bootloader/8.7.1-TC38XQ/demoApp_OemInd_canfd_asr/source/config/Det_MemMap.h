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

#define MEMMAP_ERROR_DET

/*------------------[Start of a module]--------------------------------------*/

/* Memory section macros for Det */

#if (defined DET_START_SEC_CODE)
  #undef DET_START_SEC_CODE
  #undef MEMMAP_ERROR_DET
#elif (defined DET_STOP_SEC_CODE)
  #undef DET_STOP_SEC_CODE
  #undef MEMMAP_ERROR_DET

#elif (defined DET_START_SEC_VAR_INIT_8)
  #undef DET_START_SEC_VAR_INIT_8
  #undef MEMMAP_ERROR_DET
#elif (defined DET_STOP_SEC_VAR_INIT_8)
  #undef DET_STOP_SEC_VAR_INIT_8
  #undef MEMMAP_ERROR_DET

#elif (defined DET_START_SEC_VAR_NO_INIT_16)
  #undef DET_START_SEC_VAR_NO_INIT_16
  #undef MEMMAP_ERROR_DET
#elif (defined DET_STOP_SEC_VAR_NO_INIT_16)
  #undef DET_STOP_SEC_VAR_NO_INIT_16
  #undef MEMMAP_ERROR_DET

#elif (defined DET_START_SEC_VAR_NO_INIT_8)
  #undef DET_START_SEC_VAR_NO_INIT_8
  #undef MEMMAP_ERROR_DET
#elif (defined DET_STOP_SEC_VAR_NO_INIT_8)
  #undef DET_STOP_SEC_VAR_NO_INIT_8
  #undef MEMMAP_ERROR_DET

#elif (defined DET_START_SEC_VAR_NO_INIT_UNSPECIFIED)
  #undef DET_START_SEC_VAR_NO_INIT_UNSPECIFIED
  #undef MEMMAP_ERROR_DET
#elif (defined DET_STOP_SEC_VAR_NO_INIT_UNSPECIFIED)
  #undef DET_STOP_SEC_VAR_NO_INIT_UNSPECIFIED
  #undef MEMMAP_ERROR_DET

#endif

#if ((!defined MEMMAP_ERROR_DET) && (defined MEMMAP_ERROR))
  #undef MEMMAP_ERROR
#elif ((defined MEMMAP_ERROR_DET) && (!defined MEMMAP_ERROR))
  #undef MEMMAP_ERROR_DET
  #error MEMMAP_ERROR_DET the included memory section was not defined within the BSW-IMPLEMENTATION of Det.
#endif
