/**
 * \file
 *
 * \brief AUTOSAR EcuC
 *
 * This file contains the implementation of the AUTOSAR
 * module EcuC.
 *
 * \author Elektrobit Automotive GmbH, 91058 Erlangen, Germany
 *
 * Copyright 2005 - 2019 Elektrobit Automotive GmbH
 * All rights exclusively reserved for Elektrobit Automotive GmbH,
 * unless expressly agreed to otherwise.
 */






#ifndef ECUC_CFG_H
#define ECUC_CFG_H

/*==================[inclusions]============================================*/

#include <EcuC_CfgTypes.h>

/*==================[macros]================================================*/

#ifdef ECUC_DEV_ERROR_DETECT
  #error already defined: ECUC_DEV_ERROR_DETECT
#endif
/** \brief Development error detection support */
#define ECUC_DEV_ERROR_DETECT STD_ON
#ifdef ECUC_META_DATA_HANDLING_ENABLED
  #error already defined: ECUC_META_DATA_HANDLING_ENABLED
#endif
/** \brief EcuC Meta Data Handling is enabled */
#define ECUC_META_DATA_HANDLING_ENABLED STD_OFF

#endif   /* ECUC_CFG_H */
