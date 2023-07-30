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

#define MEMMAP_ERROR_I2C

/*------------------[Start of a module]--------------------------------------*/

/* Memory section macros for I2c */

#if (defined I2C_START_SEC_CODE_QM_LOCAL)
  #undef I2C_START_SEC_CODE_QM_LOCAL
  #undef MEMMAP_ERROR_I2C
#elif (defined I2C_STOP_SEC_CODE_QM_LOCAL)
  #undef I2C_STOP_SEC_CODE_QM_LOCAL
  #undef MEMMAP_ERROR_I2C

#elif (defined I2C_START_SEC_CONFIG_DATA_QM_LOCAL_UNSPECIFIED)
  #undef I2C_START_SEC_CONFIG_DATA_QM_LOCAL_UNSPECIFIED
  #undef MEMMAP_ERROR_I2C
#elif (defined I2C_STOP_SEC_CONFIG_DATA_QM_LOCAL_UNSPECIFIED)
  #undef I2C_STOP_SEC_CONFIG_DATA_QM_LOCAL_UNSPECIFIED
  #undef MEMMAP_ERROR_I2C

#elif (defined I2C_START_SEC_CONST_QM_LOCAL_32)
  #undef I2C_START_SEC_CONST_QM_LOCAL_32
  #undef MEMMAP_ERROR_I2C
#elif (defined I2C_STOP_SEC_CONST_QM_LOCAL_32)
  #undef I2C_STOP_SEC_CONST_QM_LOCAL_32
  #undef MEMMAP_ERROR_I2C

#elif (defined I2C_START_SEC_VAR_CLEARED_QM_LOCAL_UNSPECIFIED)
  #undef I2C_START_SEC_VAR_CLEARED_QM_LOCAL_UNSPECIFIED
  #undef MEMMAP_ERROR_I2C
#elif (defined I2C_STOP_SEC_VAR_CLEARED_QM_LOCAL_UNSPECIFIED)
  #undef I2C_STOP_SEC_VAR_CLEARED_QM_LOCAL_UNSPECIFIED
  #undef MEMMAP_ERROR_I2C

#elif (defined I2C_START_SEC_VAR_CLEARED_QM_LOCAL_8)
  #undef I2C_START_SEC_VAR_CLEARED_QM_LOCAL_8
  #undef MEMMAP_ERROR_I2C
#elif (defined I2C_STOP_SEC_VAR_CLEARED_QM_LOCAL_8)
  #undef I2C_STOP_SEC_VAR_CLEARED_QM_LOCAL_8
  #undef MEMMAP_ERROR_I2C

#elif (defined I2C_START_SEC_VAR_CLEARED_QM_LOCAL_32)
  #undef I2C_START_SEC_VAR_CLEARED_QM_LOCAL_32
  #undef MEMMAP_ERROR_I2C
#elif (defined I2C_STOP_SEC_VAR_CLEARED_QM_LOCAL_32)
  #undef I2C_STOP_SEC_VAR_CLEARED_QM_LOCAL_32
  #undef MEMMAP_ERROR_I2C
#endif

#if ((!defined MEMMAP_ERROR_I2C) && (defined MEMMAP_ERROR))
  #undef MEMMAP_ERROR
#elif ((defined MEMMAP_ERROR_I2C) && (!defined MEMMAP_ERROR))
  #undef MEMMAP_ERROR_I2C
  #error MEMMAP_ERROR_I2C the included memory section was not defined within the BSW-IMPLEMENTATION of I2c.
#endif
