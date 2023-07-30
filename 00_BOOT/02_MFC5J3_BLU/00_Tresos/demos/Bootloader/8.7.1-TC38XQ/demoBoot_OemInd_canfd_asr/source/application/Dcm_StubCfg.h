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

#if (!defined DCM_STUBCFG_H)
#define DCM_STUBCFG_H

/*
   Configuration file for the Dcm code stub
   The following symbols have the potential to change the behavior of the stub:
   ============================================================================

   - EBSTUBS_FUNCTION_TRACE_DCM
        Values: STD_ON (default)/STD_OFF
        En-/Disables function tracing feature module-wide if the more specific
        symbols for the single API functions are not defined.
        Also defines the default values for the following symbols if they are not set.
        If function tracing is disabled on global level this symbol has no effect.

   - EBSTUBS_FUNCTION_TRACE_DCM_[fctname]
        Values: STD_ON/STD_OFF Default: EBSTUBS_FUNCTION_TRACE_DCM
        En-/Disables function tracing feature for a single API function.
        If function tracing is disabled on global level this symbol has no effect.
        Defining a value overrules the behavior set by the module-wide symbol.
        In detail the symbols are:
      * EBSTUBS_FUNCTION_TRACE_DCM_INIT
      * EBSTUBS_FUNCTION_TRACE_DCM_GETVERSIONINFO
      * EBSTUBS_FUNCTION_TRACE_DCM_DEMTRIGGERONDTCSTATUS
      * EBSTUBS_FUNCTION_TRACE_DCM_GETSECURITYLEVEL
      * EBSTUBS_FUNCTION_TRACE_DCM_GETSESCTRLTYPE
      * EBSTUBS_FUNCTION_TRACE_DCM_GETACTIVEPROTOCOL
      * EBSTUBS_FUNCTION_TRACE_DCM_RESETTODEFAULTSESSION
      * EBSTUBS_FUNCTION_TRACE_DCM_TRIGGERONEVENT
      * EBSTUBS_FUNCTION_TRACE_DCM_SETACTIVEDIAGNOSTIC
      * EBSTUBS_FUNCTION_TRACE_DCM_MAINFUNCTION
      * EBSTUBS_FUNCTION_TRACE_DCM_COMM_NOCOMMODEENTERED
      * EBSTUBS_FUNCTION_TRACE_DCM_COMM_SILENTCOMMODEENTERED
      * EBSTUBS_FUNCTION_TRACE_DCM_COMM_FULLCOMMODEENTERED
      * EBSTUBS_FUNCTION_TRACE_DCM_STARTOFRECEPTION
      * EBSTUBS_FUNCTION_TRACE_DCM_COPYRXDATA
      * EBSTUBS_FUNCTION_TRACE_DCM_TPRXINDICATION
      * EBSTUBS_FUNCTION_TRACE_DCM_COPYTXDATA
      * EBSTUBS_FUNCTION_TRACE_DCM_TPTXCONFIRMATION

   Note: A function is only written to the function tracing buffer if:
         The global symbol EBSTUBS_FUNCTION_TRACE is enabled AND
         the symbol of the relevant function EBSTUBS_FUNCTION_TRACE_[fctname] is enabled.

     - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

   - EBSTUBS_FUNCENABLED_DCM
        Values: STD_ON (default)/STD_OFF
        En-/Disables all API functions of a single code stub at pre-compile time.
        Also defines the default values for the following symbols if they are not set.

   - EBSTUBS_FUNCENABLED_DCM_[fctname]
        Values: STD_ON/STD_OFF Default: EBSTUBS_FUNCENABLED_DCM
        En-/Disables a single API function at pre-compile time.
        Defining a value overrules the behavior set by the module-wide symbol.
        In detail the symbols are:
      * EBSTUBS_FUNCENABLED_DCM_INIT
      * EBSTUBS_FUNCENABLED_DCM_GETVERSIONINFO
      * EBSTUBS_FUNCENABLED_DCM_DEMTRIGGERONDTCSTATUS
      * EBSTUBS_FUNCENABLED_DCM_GETSECURITYLEVEL
      * EBSTUBS_FUNCENABLED_DCM_GETSESCTRLTYPE
      * EBSTUBS_FUNCENABLED_DCM_GETACTIVEPROTOCOL
      * EBSTUBS_FUNCENABLED_DCM_RESETTODEFAULTSESSION
      * EBSTUBS_FUNCENABLED_DCM_TRIGGERONEVENT
      * EBSTUBS_FUNCENABLED_DCM_SETACTIVEDIAGNOSTIC
      * EBSTUBS_FUNCENABLED_DCM_MAINFUNCTION
      * EBSTUBS_FUNCENABLED_DCM_COMM_NOCOMMODEENTERED
      * EBSTUBS_FUNCENABLED_DCM_COMM_SILENTCOMMODEENTERED
      * EBSTUBS_FUNCENABLED_DCM_COMM_FULLCOMMODEENTERED
      * EBSTUBS_FUNCENABLED_DCM_STARTOFRECEPTION
      * EBSTUBS_FUNCENABLED_DCM_COPYRXDATA
      * EBSTUBS_FUNCENABLED_DCM_TPRXINDICATION
      * EBSTUBS_FUNCENABLED_DCM_COPYTXDATA
      * EBSTUBS_FUNCENABLED_DCM_TPTXCONFIRMATION

     - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

   - EBSTUBS_MAX_CALLS_DCM
        Values: [numeric value] Default: 1
        Defines the number of API calls for which the code stubs can store the function arguments.
        Also defines the default values for the following symbols if they are not set.

   - EBSTUBS_MAX_CALLS_DCM_[fctname]
        Values: [numeric value] Default: EBSTUBS_MAX_CALLS_DCM
        Defines the number of API calls for which a specific function can.
        store the function arguments.
        Defining a value overrules the behavior set by the module-wide symbol.
        In detail the symbols are:
      * EBSTUBS_MAX_CALLS_DCM_INIT
      * EBSTUBS_MAX_CALLS_DCM_GETVERSIONINFO
      * EBSTUBS_MAX_CALLS_DCM_DEMTRIGGERONDTCSTATUS
      * EBSTUBS_MAX_CALLS_DCM_GETSECURITYLEVEL
      * EBSTUBS_MAX_CALLS_DCM_GETSESCTRLTYPE
      * EBSTUBS_MAX_CALLS_DCM_GETACTIVEPROTOCOL
      * EBSTUBS_MAX_CALLS_DCM_RESETTODEFAULTSESSION
      * EBSTUBS_MAX_CALLS_DCM_TRIGGERONEVENT
      * EBSTUBS_MAX_CALLS_DCM_SETACTIVEDIAGNOSTIC
      * EBSTUBS_MAX_CALLS_DCM_MAINFUNCTION
      * EBSTUBS_MAX_CALLS_DCM_COMM_NOCOMMODEENTERED
      * EBSTUBS_MAX_CALLS_DCM_COMM_SILENTCOMMODEENTERED
      * EBSTUBS_MAX_CALLS_DCM_COMM_FULLCOMMODEENTERED
      * EBSTUBS_MAX_CALLS_DCM_STARTOFRECEPTION
      * EBSTUBS_MAX_CALLS_DCM_COPYRXDATA
      * EBSTUBS_MAX_CALLS_DCM_TPRXINDICATION
      * EBSTUBS_MAX_CALLS_DCM_COPYTXDATA
      * EBSTUBS_MAX_CALLS_DCM_TPTXCONFIRMATION
*/

#endif /* !defined DCM_STUBCFG_H */
