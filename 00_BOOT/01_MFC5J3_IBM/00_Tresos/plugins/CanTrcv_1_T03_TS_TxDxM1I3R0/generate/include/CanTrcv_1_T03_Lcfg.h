/**EB_Automotive_C_Source_File */
[!CODE!]
[!AUTOSPACING!]

#if (!defined CANTRCV_1_T03_LCFG_H)
#define CANTRCV_1_T03_LCFG_H

/*==================[includes]==============================================*/

#include <ComStack_Types.h>         /* typedefs for AUTOSAR com stack */
#include <CanTrcv_1_T03_Int.h>      /* CanTrcv_1_T03_TrcvStateType */

/*==================[macros]================================================*/

/*==================[type definitions]======================================*/

/*==================[external function declarations]========================*/

/*==================[internal function declarations]========================*/

/*==================[external constants]====================================*/

/*==================[internal constants]====================================*/

/*==================[external data]=========================================*/

/*==================[internal data]=========================================*/

/* start data section declaration */
#define CANTRCV_1_T03_START_SEC_CONST_32
#include <CanTrcv_1_T03_MemMap.h>

/* value used to validate post build configuration against link time configuration */
extern CONST(uint32, CANTRCV_1_T03_CONST) CanTrcv_1_T03_LcfgSignature;

/* stop data section declaration */
#define CANTRCV_1_T03_STOP_SEC_CONST_32
#include <CanTrcv_1_T03_MemMap.h>


#define CANTRCV_1_T03_START_SEC_VAR_CLEARED_UNSPECIFIED
#include <CanTrcv_1_T03_MemMap.h>

/** \brief Postbuild capable Channel configuration in RAM */
extern VAR(CanTrcv_1_T03_TrcvStateType, CANTRCV_1_T03_VAR)
    CanTrcv_1_T03_TrcvState[CANTRCV_1_T03_MAX_NUMBER_OF_CHANNELS];

#define CANTRCV_1_T03_STOP_SEC_VAR_CLEARED_UNSPECIFIED
#include <CanTrcv_1_T03_MemMap.h>


/*==================[external function definitions]=========================*/

/*==================[internal function definitions]=========================*/

#endif /* if !defined( CANTRCV_1_T03_LCFG_H ) */
/*==================[end of file]===========================================*/
[!ENDCODE!][!//
