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

#if (defined _LINARO_C_CORTEXM_) /* to prevent double definition */
#error _LINARO_C_CORTEXM_ already defined
#endif /* if (defined _LINARO_C_CORTEXM_) */

/** \brief compiler symbol for Gnu_Linaro compiler */
#define _LINARO_C_CORTEXM_ 1U

#endif /* if (!defined COMPILER_SPECIFIC_H) */
