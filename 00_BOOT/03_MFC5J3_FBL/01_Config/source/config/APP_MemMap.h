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

#define MEMMAP_ERROR_APP

/*------------------[Start of a module]--------------------------------------*/

/* Memory section macros for App */

#if (defined APP_START_SEC_VAR_UNSPECIFIED)
    #undef APP_START_SEC_VAR_UNSPECIFIED
    #undef MEMMAP_ERROR_APP
#elif (defined APP_STOP_SEC_VAR_UNSPECIFIED)
    #undef APP_STOP_SEC_VAR_UNSPECIFIED
    #undef MEMMAP_ERROR_APP

#elif (defined APP_START_SEC_CODE)
    #undef APP_START_SEC_CODE
    #undef MEMMAP_ERROR_APP
#elif (defined APP_STOP_SEC_CODE)
    #undef APP_STOP_SEC_CODE
    #undef MEMMAP_ERROR_APP

#endif

#if ((!defined MEMMAP_ERROR_APP) && (defined MEMMAP_ERROR))
  #undef MEMMAP_ERROR
#elif ((defined MEMMAP_ERROR_APP) && (!defined MEMMAP_ERROR))
  #undef MEMMAP_ERROR_APP
  #error MEMMAP_ERROR_APP the included memory section was not defined within the BSW-IMPLEMENTATION of App.
#endif
