/**
 * \file
 *
 * \brief AUTOSAR Det
 *
 * This file contains the implementation of the AUTOSAR
 * module Det.
 *
 * \author Elektrobit Automotive GmbH, 91058 Erlangen, Germany
 *
 * Copyright 2005 - 2019 Elektrobit Automotive GmbH
 * All rights exclusively reserved for Elektrobit Automotive GmbH,
 * unless expressly agreed to otherwise.
 */

/*==================[inclusions]=================================================================*/

#include <Det_Trace.h>
#include <Std_Types.h>                                                 /* AUTOSAR standard types */

#if (defined DET_INTERNAL_USAGE)
#error DET_INTERNAL_USAGE is already defined
#endif

#define DET_INTERNAL_USAGE
#include <Det_BSW.h>                                              /* Declaration of Det BSW APIs */

#if (DET_RTE_USAGE == STD_ON)
#if (DET_ENABLE_ASR40_SERVICE_API == STD_ON)
#include <Rte_DevelopmentErrorTracer.h>

/*==================[macros]=====================================================================*/

/*==================[type definitions]===========================================================*/

/*==================[external function declarations]=============================================*/

/*==================[internal function declarations]=============================================*/

/*==================[external constants]=========================================================*/

/*==================[internal constants]=========================================================*/

/*==================[external data]==============================================================*/

/*==================[internal data]==============================================================*/

/*==================[internal function definitions]==============================================*/

/*==================[external function definitions]==============================================*/

#define DevelopmentErrorTracer_START_SEC_CODE
/* !LINKSTO Det.EB.req.swc_include,1 */
#include <DevelopmentErrorTracer_MemMap.h>

FUNC(Std_ReturnType, DET_CODE) Det_ASR40_Rte_ReportError(
   uint16 pdav0, /* Port defined argument for ModuleId */
   uint8  InstanceId,
   uint8  ApiId,
   uint8  ErrorId)
{
  Std_ReturnType retVal;
  DBG_DET_ASR40_RTE_REPORTERROR_ENTRY(pdav0,InstanceId,ApiId,ErrorId);

  retVal = Det_ASR40_ReportError(pdav0, InstanceId, ApiId, ErrorId);

  DBG_DET_ASR40_RTE_REPORTERROR_EXIT(retVal,pdav0,InstanceId,ApiId,ErrorId);
  return retVal;
}

#define DevelopmentErrorTracer_STOP_SEC_CODE
/* !LINKSTO Det.EB.req.swc_include,1 */
#include <DevelopmentErrorTracer_MemMap.h>

#endif /* (DET_ENABLE_ASR40_SERVICE_API == STD_ON) */
#endif /* (DET_RTE_USAGE == STD_ON) */

#if ((DET_RTE_USAGE == STD_OFF) || \
     (DET_ENABLE_ASR40_SERVICE_API == STD_OFF))

#include <Det_Compiler.h>                   /* Avoid empty translation unit according to ISO C90 */

#endif /* ((DET_RTE_USAGE == STD_OFF) || (DET_ENABLE_ASR40_SERVICE_API == STD_OFF)) */

/*==================[end of file]================================================================*/
