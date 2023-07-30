#if (!defined COMPILER_SPECIFIC_H)
#define COMPILER_SPECIFIC_H
/**
 * \file
 *
 * \brief AUTOSAR Compiler
 *
 * This file contains the implementation of the AUTOSAR
 * module Compiler.
 *
 * \author Elektrobit Automotive GmbH, 91058 Erlangen, Germany
 *
 * Copyright 2017 - 2019 Elektrobit Automotive GmbH
 * All rights exclusively reserved for Elektrobit Automotive GmbH,
 * unless expressly agreed to otherwise.
 */

/*==================[inclusions]=============================================*/

/*==================[macros]=================================================*/

/*------------------[compiler symbol]----------------------------------------*/

/* COMPILER010 */
#if (defined _IAR_C_CORTEXM_) /* to prevent double definition */
#error _IAR_C_CORTEXM_ already defined
#endif /* if (defined _IAR_C_CORTEXM_) */

/** \brief compiler symbol for IAR compiler */
#define _IAR_C_CORTEXM_ 1U



#endif /* if (!defined COMPILER_SPECIFIC_H) */
