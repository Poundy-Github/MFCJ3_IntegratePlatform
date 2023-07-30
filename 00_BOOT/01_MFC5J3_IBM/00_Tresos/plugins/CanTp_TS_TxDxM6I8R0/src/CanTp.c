/**
 * \file
 *
 * \brief AUTOSAR CanTp
 *
 * This file contains the implementation of the AUTOSAR
 * module CanTp.
 *
 * \author Elektrobit Automotive GmbH, 91058 Erlangen, Germany
 *
 * Copyright 2005 - 2019 Elektrobit Automotive GmbH
 * All rights exclusively reserved for Elektrobit Automotive GmbH,
 * unless expressly agreed to otherwise.
 */

/*==================[inclusions]============================================*/

#include <TSAutosar.h>         /* EB specific standard typesb */
#include <CanTp_Version.h>     /* CanTp version declarations */

/*==================[macros]================================================*/

/* !LINKSTO CanTp.ASR40.CANTP024,1, CanTp.EB.PublishedInformation,1 */
/*------------------[AUTOSAR vendor identification check]-------------------*/

#if (!defined CANTP_VENDOR_ID) /* configuration check */
#error CANTP_VENDOR_ID must be defined
#endif

#if (CANTP_VENDOR_ID != 1U) /* vendor check */
#error CANTP_VENDOR_ID has wrong vendor id
#endif

/*------------------[AUTOSAR release version identification check]----------*/

#if (!defined CANTP_AR_RELEASE_MAJOR_VERSION) /* configuration check */
#error CANTP_AR_RELEASE_MAJOR_VERSION must be defined
#endif

/* major version check */
#if (CANTP_AR_RELEASE_MAJOR_VERSION != 4U)
#error CANTP_AR_RELEASE_MAJOR_VERSION wrong (!= 4U)
#endif

#if (!defined CANTP_AR_RELEASE_MINOR_VERSION) /* configuration check */
#error CANTP_AR_RELEASE_MINOR_VERSION must be defined
#endif

/* minor version check */
#if (CANTP_AR_RELEASE_MINOR_VERSION != 0U )
#error CANTP_AR_RELEASE_MINOR_VERSION wrong (!= 0U)
#endif

#if (!defined CANTP_AR_RELEASE_REVISION_VERSION) /* configuration check */
#error CANTP_AR_RELEASE_REVISION_VERSION must be defined
#endif

/* revision version check */
#if (CANTP_AR_RELEASE_REVISION_VERSION != 3U )
#error CANTP_AR_RELEASE_REVISION_VERSION wrong (!= 3U)
#endif

/*------------------[AUTOSAR module version identification check]-----------*/

#if (!defined CANTP_SW_MAJOR_VERSION) /* configuration check */
#error CANTP_SW_MAJOR_VERSION must be defined
#endif

/* major version check */
#if (CANTP_SW_MAJOR_VERSION != 6U)
#error CANTP_SW_MAJOR_VERSION wrong (!= 6U)
#endif

#if (!defined CANTP_SW_MINOR_VERSION) /* configuration check */
#error CANTP_SW_MINOR_VERSION must be defined
#endif

/* minor version check */
#if (CANTP_SW_MINOR_VERSION < 8U)
#error CANTP_SW_MINOR_VERSION wrong (< 8U)
#endif

#if (!defined CANTP_SW_PATCH_VERSION) /* configuration check */
#error CANTP_SW_PATCH_VERSION must be defined
#endif

/* patch version check */
#if (CANTP_SW_PATCH_VERSION < 27U)
#error CANTP_SW_PATCH_VERSION wrong (< 27U)
#endif

/*==================[type definitions]======================================*/

/*==================[external function declarations]========================*/

/*==================[internal function declarations]========================*/

/*==================[external constants]====================================*/

/*------------------[version constants definition]--------------------------*/

/*==================[internal constants]====================================*/

/*==================[external data]=========================================*/

/*==================[internal data]=========================================*/

/*==================[external function definitions]=========================*/

/*==================[internal function definitions]=========================*/

/*==================[end of file]===========================================*/
