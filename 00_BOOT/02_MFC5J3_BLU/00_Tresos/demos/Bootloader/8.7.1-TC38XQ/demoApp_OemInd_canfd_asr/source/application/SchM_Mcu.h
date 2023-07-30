#if (!defined SCHM_MCU_H)
#define SCHM_MCU_H

/** \file
 ** \brief AUTOSAR SchM Schedule Manager
 **
 ** This file includes function prototype stubs for SchM_Enter/Exit
 ** and SchM_Act/CancelMainFunction for the module Mcu .
 **
 ** \project AUTOSAR Standard Core
 ** \author Horst Laschinsky
 ** \author Elektrobit Automotive GmbH, 91058 Erlangen, Germany
 **
 ** $Id: SchM_Mcu.h 7374 2019-07-09 15:10:59Z vira270768 $
 ** Release: BLP-3.X_ACG-8_TRICORE_TC38XQ
 **
 ** \controller independent
 ** \compiler independent
 ** \hardware independent
 **
 ** Copyright 2008 by Elektrobit Automotive GmbH
 ** All rights exclusively reserved for Elektrobit Automotive GmbH
 ** unless expressly agreed to otherwise */

/** \addtogroup SchM Schedule Manager
 ** @{ */

/*==================[includes]==============================================*/

#include <SchM.h>      /* SchM API */

/*==================[macros]================================================*/

/* exclusive area/instance IDs/literals */
#define SCHM_MCU_EXCLUSIVE_AREA_0 0U
 
/* wrapper macros */
#define SchM_Enter_Mcu_SCHM_MCU_EXCLUSIVE_AREA_0() \
  SchM_EB_Enter_Mcu(SCHM_MCU_EXCLUSIVE_AREA_0)
 
#define SchM_Exit_Mcu_SCHM_MCU_EXCLUSIVE_AREA_0() \
  SchM_EB_Exit_Mcu(SCHM_MCU_EXCLUSIVE_AREA_0)

/*==================[type definitions]======================================*/

/*==================[external function declarations]========================*/

/*==================[internal function declarations]========================*/

/*==================[external constants]====================================*/

/*==================[internal constants]====================================*/

/*==================[external data]=========================================*/

/*==================[internal data]=========================================*/

/*==================[external function definitions]=========================*/

/*==================[internal function definitions]=========================*/
#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */
/* ==================[Includes]=============================================== */
#include <SchM_McuType.h>

/* ==================[Declaration of functions with external linkage]========= */
#define RTE_START_SEC_CODE
#include <MemMap.h>
extern FUNC(void, RTE_CODE) SchM_Enter_Mcu_TomTgcReg (void);
extern FUNC(void, RTE_CODE) SchM_Exit_Mcu_TomTgcReg (void);
extern FUNC(void, RTE_CODE) SchM_Enter_Mcu_AtomAgcReg (void);
extern FUNC(void, RTE_CODE) SchM_Exit_Mcu_AtomAgcReg (void);
#define RTE_STOP_SEC_CODE
#include <MemMap.h>

#ifdef __cplusplus
} /* extern "C" */
#endif /* __cplusplus */

/** @} doxygen end group definition */
#endif /* if !defined( SCHM_MCU_H ) */
/*==================[end of file]===========================================*/
