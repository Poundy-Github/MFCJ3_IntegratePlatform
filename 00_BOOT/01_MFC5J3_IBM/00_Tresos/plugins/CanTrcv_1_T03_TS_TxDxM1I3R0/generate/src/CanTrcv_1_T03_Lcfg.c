/**EB_Automotive_C_Source_File */
[!CODE!]
[!AUTOSPACING!]

/*==================[inclusions]=============================================*/
[!INCLUDE "../include/CanTrcv_1_T03_Vars.m"!]
[!SELECT "as:modconf('CanTrcv')[(CommonPublishedInformation/VendorId = 1) and (CommonPublishedInformation/VendorApiInfix = 'T03')]"!]
#define CANTRCV_1_T03_NO_CFGCLASSMIX_REQUIRED
#define CANTRCV_1_T03_NO_PBCFG_REQUIRED
#include <CanTrcv_1_T03_Lcfg.h> /* Generated configuration */

/*==================[macros]=================================================*/

/*==================[type definitions]=======================================*/

/*==================[external function declarations]=========================*/

/*==================[internal function declarations]=========================*/

/*==================[external constants]=====================================*/

/* start data section declaration */
#define CANTRCV_1_T03_START_SEC_CONST_32
#include <CanTrcv_1_T03_MemMap.h>

/* value used to validate post build configuration against link time configuration */
CONST(uint32, CANTRCV_1_T03_CONST) CanTrcv_1_T03_LcfgSignature = [!"asc:getConfigSignature(.//*[not(child::*) and (node:configclass() = 'Link')])"!]U;

/* stop data section declaration */
#define CANTRCV_1_T03_STOP_SEC_CONST_32
#include <CanTrcv_1_T03_MemMap.h>


#define CANTRCV_1_T03_START_SEC_VAR_CLEARED_UNSPECIFIED
#include <CanTrcv_1_T03_MemMap.h>

VAR(CanTrcv_1_T03_TrcvStateType, CANTRCV_1_T03_VAR)
CanTrcv_1_T03_TrcvState[CANTRCV_1_T03_MAX_NUMBER_OF_CHANNELS];

#define CANTRCV_1_T03_STOP_SEC_VAR_CLEARED_UNSPECIFIED
#include <CanTrcv_1_T03_MemMap.h>
[!ENDSELECT!]
/*==================[internal constants]=====================================*/

/*==================[external data]==========================================*/

/*==================[internal function definitions]==========================*/

/*==================[end of file]============================================*/
[!ENDCODE!][!//
