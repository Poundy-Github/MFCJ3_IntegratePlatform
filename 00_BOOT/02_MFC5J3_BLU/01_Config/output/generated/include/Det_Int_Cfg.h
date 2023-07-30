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
#ifndef DET_INT_CFG_H
#define DET_INT_CFG_H

/*==================[includes]==============================================*/

/* Include declaration of user defined callback function */
#include <Det_Cbk.h>

/*==================[macros]================================================*/


/* !LINKSTO EB_Ref.SWS_Det_00180.Signature,1 */
/* !LINKSTO EB_Ref.SWS_Det_00180.ID,1 */

#if (defined DET_NOTIFICATIONS_DEVELOPMENT_ERROR)
#error DET_NOTIFICATIONS_DEVELOPMENT_ERROR is already defined
#endif

/* !LINKSTO SWS_Det_00181,1 */
/** \brief Call user defined notification functions */
#define DET_NOTIFICATIONS_DEVELOPMENT_ERROR(a,b,c,d)              \
          do                                    \
          {                                     \
            Det_CustomReportError(a,b,c,d); \
          } while (0)

/* !LINKSTO SWS_Det_00184,1 */
#if (defined DET_NOTIFICATIONS_RUNTIME_ERROR)
#error DET_NOTIFICATIONS_RUNTIME_ERROR is already defined
#endif

/** \brief Call user defined notification functions */
#define DET_NOTIFICATIONS_RUNTIME_ERROR(a,b,c,d)              \
          do                                    \
          {                                     \
            Det_CustomReportRuntimeError(a,b,c,d); \
          } while (0)

/* !LINKSTO SWS_Det_00187,1 */
#if (defined DET_NOTIFICATIONS_TRANSIENT_FAULT)
#error DET_NOTIFICATIONS_TRANSIENT_FAULT is already defined
#endif

/** \brief Call user defined notification functions */
#define DET_NOTIFICATIONS_TRANSIENT_FAULT(a,b,c,d)              \
          do                                    \
          {                                     \
            transientFaultRetVal |= Det_CustomReportTransientFault(a,b,c,d); \
          } while (0)

/*==================[type definitions]======================================*/

/*==================[external function declarations]========================*/

/*==================[internal function declarations]========================*/

/*==================[external constants]====================================*/

/*==================[internal constants]====================================*/

/*==================[external data]=========================================*/

/*==================[internal data]=========================================*/

/*==================[external function definitions]=========================*/

/*==================[internal function definitions]=========================*/

#endif /* if !defined( DET_INT_CFG_H ) */
/*==================[end of file]===========================================*/
