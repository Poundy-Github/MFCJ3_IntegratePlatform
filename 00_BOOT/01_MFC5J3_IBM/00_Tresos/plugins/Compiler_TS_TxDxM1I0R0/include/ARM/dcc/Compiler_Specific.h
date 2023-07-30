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

/*
 * MISRA-C:2012 Deviation List
 *
 * MISRAC2012-1) Deviated Rule: 21.1 (required)
 * #define and #undef shall not be used on a reserved identifier or reserved
 * macro name.
 *
 * Reason:
 * Generally, all identifiers that begin with the underscore character are reserved.
 * The macro _DIABDATA_C_ARM_ is only used for Autosar 2.1 backward compatibility.
 */
/* COMPILER010 */
/* !LINKSTO CompilerAbstraction.ASR403.COMPILER010, 1 */
#if (defined _DIABDATA_C_ARM_) /* to prevent double definition */
#error _DIABDATA_C_ARM_ already defined
#endif /* if (defined _DIABDATA_C_ARM_) */

/** \brief compiler symbol for DiabData compiler for ARM */
/* Deviation MISRAC2012-1 */
#define _DIABDATA_C_ARM_ 1U

#endif /* if (!defined COMPILER_SPECIFIC_H) */
