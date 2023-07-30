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

#define MEMMAP_ERROR_PDUR

/*------------------[Start of a module]--------------------------------------*/

/* Memory section macros for PduR */

#if (defined PDUR_START_SEC_CODE)
  #undef PDUR_START_SEC_CODE
  #undef MEMMAP_ERROR_PDUR
#elif (defined PDUR_STOP_SEC_CODE)
  #undef PDUR_STOP_SEC_CODE
  #undef MEMMAP_ERROR_PDUR

#elif (defined PDUR_START_SEC_CONFIG_DATA_UNSPECIFIED)
  #undef PDUR_START_SEC_CONFIG_DATA_UNSPECIFIED
  #undef MEMMAP_ERROR_PDUR
#elif (defined PDUR_STOP_SEC_CONFIG_DATA_UNSPECIFIED)
  #undef PDUR_STOP_SEC_CONFIG_DATA_UNSPECIFIED
  #undef MEMMAP_ERROR_PDUR

#elif (defined PDUR_START_SEC_CONST_16)
  #undef PDUR_START_SEC_CONST_16
  #undef MEMMAP_ERROR_PDUR
#elif (defined PDUR_STOP_SEC_CONST_16)
  #undef PDUR_STOP_SEC_CONST_16
  #undef MEMMAP_ERROR_PDUR

#elif (defined PDUR_START_SEC_CONST_32)
  #undef PDUR_START_SEC_CONST_32
  #undef MEMMAP_ERROR_PDUR
#elif (defined PDUR_STOP_SEC_CONST_32)
  #undef PDUR_STOP_SEC_CONST_32
  #undef MEMMAP_ERROR_PDUR

#elif (defined PDUR_START_SEC_CONST_8)
  #undef PDUR_START_SEC_CONST_8
  #undef MEMMAP_ERROR_PDUR
#elif (defined PDUR_STOP_SEC_CONST_8)
  #undef PDUR_STOP_SEC_CONST_8
  #undef MEMMAP_ERROR_PDUR

#elif (defined PDUR_START_SEC_CONST_UNSPECIFIED)
  #undef PDUR_START_SEC_CONST_UNSPECIFIED
  #undef MEMMAP_ERROR_PDUR
#elif (defined PDUR_STOP_SEC_CONST_UNSPECIFIED)
  #undef PDUR_STOP_SEC_CONST_UNSPECIFIED
  #undef MEMMAP_ERROR_PDUR

#elif (defined PDUR_START_SEC_VAR_INIT_UNSPECIFIED)
  #undef PDUR_START_SEC_VAR_INIT_UNSPECIFIED
  #undef MEMMAP_ERROR_PDUR
#elif (defined PDUR_STOP_SEC_VAR_INIT_UNSPECIFIED)
  #undef PDUR_STOP_SEC_VAR_INIT_UNSPECIFIED
  #undef MEMMAP_ERROR_PDUR

#elif (defined PDUR_START_SEC_VAR_NOINIT_UNSPECIFIED)
  #undef PDUR_START_SEC_VAR_NOINIT_UNSPECIFIED
  #undef MEMMAP_ERROR_PDUR
#elif (defined PDUR_STOP_SEC_VAR_NOINIT_UNSPECIFIED)
  #undef PDUR_STOP_SEC_VAR_NOINIT_UNSPECIFIED
  #undef MEMMAP_ERROR_PDUR

#endif

#if ((!defined MEMMAP_ERROR_PDUR) && (defined MEMMAP_ERROR))
  #undef MEMMAP_ERROR
#elif ((defined MEMMAP_ERROR_PDUR) && (!defined MEMMAP_ERROR))
  #undef MEMMAP_ERROR_PDUR
  #error MEMMAP_ERROR_PDUR the included memory section was not defined within the BSW-IMPLEMENTATION of PduR.
#endif
