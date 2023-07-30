/**
 * \file
 *
 * \brief AUTOSAR Det
 *
 * This file contains the implementation of the AUTOSAR
 * module Det.
 *
 * \version 2.12.2
 *
 * \author Elektrobit Automotive GmbH, 91058 Erlangen, Germany
 *
 * Copyright 2005 - 2021 Elektrobit Automotive GmbH
 * All rights exclusively reserved for Elektrobit Automotive GmbH,
 * unless expressly agreed to otherwise.
 */
#ifndef DET_CBK_H
#define DET_CBK_H

extern FUNC(Std_ReturnType, DET_CODE) Det_CustomReportError
(
  uint16 ModuleId,
  uint8 InstanceId,
  uint8 ApiId,
  uint8 ErrorId
);

extern FUNC(Std_ReturnType, DET_CODE) Det_CustomReportRuntimeError
(
  uint16 ModuleId,
  uint8 InstanceId,
  uint8 ApiId,
  uint8 ErrorId);

extern FUNC(Std_ReturnType, DET_CODE) Det_CustomReportTransientFault
(
  uint16 ModuleId,
  uint8 InstanceId,
  uint8 ApiId,
  uint8 ErrorId
);

#endif /* ifndef DET_CBK_H */
/*==================[end of file]============================================*/
