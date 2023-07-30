/**
 * \file
 *
 * \brief AUTOSAR Demo
 *
 * This file contains the implementation of the AUTOSAR
 * module Demo.
 *
 * \author Elektrobit Automotive GmbH, 91058 Erlangen, Germany
 *
 * Copyright 2005 - 2019 Elektrobit Automotive GmbH
 * All rights exclusively reserved for Elektrobit Automotive GmbH,
 * unless expressly agreed to otherwise.
 */

/*
 *  MISRA deviation report:
 *  - This file violates MISRA-C:2004, Rule 19.6:
 *       "#undef shall not be used"
 *    Reason:
 *       The specification document explicitely describes this mechanism.
 *  - This file violates MISRA-C:2004, Rule 19.15:
 *       "Precautions shall be taken in order to prevent the contents
 *        of a header file being included twice."
 *    Reason:
 *       This file needs to be included more than once in a compilation unit
 */

/*==================[inclusions]=============================================*/

/*==================[macros]=================================================*/

/*------------------[Autosar vendor identification]--------------------------*/

/*------------------[AUTOSAR release version identification]-----------------*/

/*------------------[Autosar software version]-------------------------------*/

/*------------------[MemMap error checking]----------------------------------*/

#if 0 /* to be able to use #elif for every module */

/*****************************************************************************
**                              MCAL LIB                     				**
******************************************************************************/

/*------------------[Start of a module]--------------------------------------*/
/* following macors are needed for BasicTemplate application code            */
#elif (defined IRQ_START_SEC_CODE_QM_GLOBAL)
  #undef IRQ_START_SEC_CODE_QM_GLOBAL
  #undef MEMMAP_ERROR

#elif (defined IRQ_STOP_SEC_CODE_QM_GLOBAL)
  #undef IRQ_STOP_SEC_CODE_QM_GLOBAL
  #undef MEMMAP_ERROR 

#elif (defined IRQ_START_SEC_CODE)
  #undef IRQ_START_SEC_CODE
  #undef MEMMAP_ERROR

#elif (defined IRQ_STOP_SEC_CODE)
  #undef IRQ_STOP_SEC_CODE
  #undef MEMMAP_ERROR    
#endif

/*------------------[MemMap error checking]----------------------------------*/

/*==================[end of file]============================================*/
