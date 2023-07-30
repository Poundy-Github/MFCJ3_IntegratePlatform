
/**
 * \file
 *
 * \brief SchM
 *
 * This file contains the implementation of the SchM
 * exclusive areas.
 *
 * \author Elektrobit Automotive GmbH, 91058 Erlangen, Germany
 *
 * Copyright 2005 - 2013 Elektrobit Automotive GmbH
 * All rights exclusively reserved for Elektrobit Automotive GmbH,
 * unless expressly agreed to otherwise.
 */

 /* Misra deviations:
  * 1) Deviation against MISRA-C:1998 Rule 11 (required)
  *      and               MISRA-C:2004 Rule 5.1 (required)
  *      Description:
  *      Identifiers (internal and external) shall not rely
  *      on the significance of more than 31 characters.
  *      Reason:
  *      The defined SchM naming convention may result in
  *      identifiers with more than 31 characters.
  *      The compliance to this rule is under user's control.
  *
  */


/*==================[inclusions]=============================================*/

#include <Std_Types.h>

#include <EB_Prj.h>

#include <board.h>

/*==================[macros]=================================================*/

/*------------------[interrupt locking]--------------------------------------*/

/*==================[internal data]==========================================*/

/*------------------[API function definitions]-------------------------------*/
FUNC(void, SCHM_CODE) SchM_Enter_Det_SCHM_DET_EXCLUSIVE_AREA_0(void)
{
  BoardDisableInterrupts();
} /* FUNC(void, SCHM_CODE) SchM_Enter_Det_SCHM_DET_EXCLUSIVE_AREA_0 (void) */


FUNC(void, SCHM_CODE) SchM_Exit_Det_SCHM_DET_EXCLUSIVE_AREA_0(void)
{
  BoardEnableInterrupts();
} /* FUNC(void, SCHM_CODE) SchM_Exit_Det_SCHM_DET_EXCLUSIVE_AREA_0 (void) */

FUNC(void, SCHM_CODE) SchM_Enter_McalLib_PeripheralEndInit (void)
{
  BoardDisableInterrupts();

} /* FUNC(void, SCHM_CODE) SchM_Enter_McalLib_PeripheralEndInit (void) */

FUNC(void, SCHM_CODE) SchM_Exit_McalLib_PeripheralEndInit (void)
{
  BoardEnableInterrupts();

} /* FUNC(void, SCHM_CODE) SchM_Exit_McalLib_PeripheralEndInit (void) */

FUNC(void, SCHM_CODE) SchM_Enter_McalLib_CpuEndInit (void)
{
  BoardDisableInterrupts();

} /* FUNC(void, SCHM_CODE) SchM_Enter_McalLib_CpuEndInit (void) */

FUNC(void, SCHM_CODE) SchM_Exit_McalLib_CpuEndInit (void)
{
  BoardEnableInterrupts();

} /* FUNC(void, SCHM_CODE) SchM_Exit_McalLib_CpuEndInit (void) */

FUNC(void, SCHM_CODE) SchM_Enter_McalLib_SafetyEndInit (void)
{
  BoardDisableInterrupts();

} /* FUNC(void, SCHM_CODE) SchM_Enter_McalLib_SafetyEndInit (void) */

FUNC(void, SCHM_CODE) SchM_Exit_McalLib_SafetyEndInit (void)
{
  BoardEnableInterrupts();

} /* FUNC(void, SCHM_CODE) SchM_Exit_McalLib_SafetyEndInit (void) */

FUNC(void, SCHM_CODE) SchM_Enter_McalLib_StmTimerResolution (void)
{
  BoardDisableInterrupts();

} /* FUNC(void, SCHM_CODE) SchM_Enter_McalLib_StmTimerResolution (void) */

FUNC(void, SCHM_CODE) SchM_Exit_McalLib_StmTimerResolution (void)
{
  BoardEnableInterrupts();

} /* FUNC(void, SCHM_CODE) SchM_Exit_McalLib_StmTimerResolution (void) */

void SuspendAllInterrupts(void)
{
  BoardDisableInterrupts();
  
}

void ResumeAllInterrupts(void)
{
  BoardEnableInterrupts();
  
}

/*==================[internal function definitions]==========================*/

/*==================[end of file]============================================*/

