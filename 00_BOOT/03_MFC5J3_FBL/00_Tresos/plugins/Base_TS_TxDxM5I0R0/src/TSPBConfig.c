/**
 * \file
 *
 * \brief AUTOSAR Base
 *
 * This file contains the implementation of the AUTOSAR
 * module Base.
 *
 * \author Elektrobit Automotive GmbH, 91058 Erlangen, Germany
 *
 * Copyright 2005 - 2019 Elektrobit Automotive GmbH
 * All rights exclusively reserved for Elektrobit Automotive GmbH,
 * unless expressly agreed to otherwise.
 */

/*
 * MISRA-C:2012 Deviation List
 *
 * MISRAC2012-1) Deviated Rule: 11.4 (advisory)
 * A conversion should not be performed between a pointer to object
 * and an integer type.
 *
 * Reason:
 * Depending on the standard library the offsetof() macro is expanded
 * to a construct which may violate this rule.
 *
 * MISRAC2012-2) Deviated Rule: 1.3 (required)
 * There shall be no occurrence of undefined or critical unspecified behaviour.
 *
 * Reason:
 * MISRA-C:2012 Rule 1.3 gives the following rationale for
 * forbidding the use of this macro: "Use of this macro can lead
 * to undefined behavior when the types of the operands are
 * incompatible or when bitfields are used."
 * This rationale is an ambiguous and incomplete deduction of a
 * statement in section G.2 "Undefined behavior" of the ISO 9899:1990
 * standard: "The behavior is undefined in the following
 * circumstances: The member designator parameter of an offsetof
 * macro is an invalid right operand of the .operator for the type
 * parameter, or designates a bit-field."
 * Since the only uses of offsetof in the context of this header
 * file is in line with the restrictions imposed by ISO 9899:1990, the
 * behavior is not undefined here.
 * The offsetof macro is needed to compute a structure member's
 * offset from the beginning of a structure in order to create
 * references within a relocatable post build configuration.
 *
 * MISRAC2012-3) Deviated Rule: 20.7 (required)
 * Expressions resulting from the expansion of macro parameters shall be
 * enclosed in parentheses.
 *
 * Reason:
 * Macros are used for type independent casts. Such a parameter cannot be
 * enclosed in parentheses as this would lead to a syntax error.
 *
 * MISRAC2012-4) Deviated Rule: 11.9 (required)
 * The macro NULL shall be the only permitted form of integer null pointer constant
 *
 * Reason:
 * Macros are used in order to check the alignment for different data types.
 */

/*==================[inclusions]=============================================*/

#include <Std_Types.h>
#include <TSPBConfig_Signature.h>

/*==================[macros]=================================================*/

/*==================[type definitions]=======================================*/

/*==================[external function declarations]=========================*/

/*==================[internal function declarations]=========================*/

/*==================[external constants]=====================================*/

/*==================[internal constants]=====================================*/

/*==================[external data]==========================================*/

/*==================[internal data]==========================================*/

/*==================[external function definitions]==========================*/

#define BASE_START_SEC_CODE
#include <Base_MemMap.h>

/** \brief Checks whether the platform signature \p signature is valid
 *
 * \param[in] signature Platform signature
 *
 * \return Validity status
 * \retval TRUE the platform signature \p signature is valid
 * \retval FALSE the platform signature \p signature is invalid
 */
/* Deviation MISRAC2012-1 <+16>, MISRAC2012-2 <+16>, MISRAC2012-3 <+16>, MISRAC2012-4 <+16> */
FUNC(boolean, BASE_CODE) TS_PlatformSigIsValid
(
  uint32 signature
)
{
  boolean RetVal = FALSE;

  if (TS_SIG_CHECK_ENDIANESS(signature) &&
      TS_SIG_CHECK_ALIGNMENT_ARRAY (signature) &&
      TS_SIG_CHECK_ALIGNMENT_STRUCT(signature) &&
      TS_SIG_CHECK_ALIGNMENT_SINT32(signature) &&
      TS_SIG_CHECK_ALIGNMENT_SINT16(signature) &&
      TS_SIG_CHECK_ALIGNMENT_SINT8(signature) &&
      TS_SIG_CHECK_ALIGNMENT_UINT32(signature) &&
      TS_SIG_CHECK_ALIGNMENT_UINT16(signature) &&
      TS_SIG_CHECK_ALIGNMENT_UINT8(signature))
  {
    RetVal = TRUE;
  }

  return RetVal;
}

#define BASE_STOP_SEC_CODE
#include <Base_MemMap.h>

/*==================[internal function definitions]==========================*/

/*==================[end of file]============================================*/
