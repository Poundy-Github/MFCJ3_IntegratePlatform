/**
 * \file
 *
 * \brief AUTOSAR MemMap
 *
 * This file contains the implementation of the AUTOSAR
 * module MemMap.
 *
 * \author Elektrobit Automotive GmbH, 91058 Erlangen, Germany
 *
 * Copyright 2005 - 2019 Elektrobit Automotive GmbH
 * All rights exclusively reserved for Elektrobit Automotive GmbH,
 * unless expressly agreed to otherwise.
 */

/*==================[inclusions]=============================================*/

/*==================[macros]=================================================*/

/*------------------[Autosar vendor identification]--------------------------*/

#if (!defined MEM_VENDOR_ID)
/** \brief Autosar module vendor identification
 **
 ** Vendor ID of the dedicated implementation of this module according
 ** to the AUTOSAR vendor list. */
#define MEMMAP_VENDOR_ID 1U /* Elektrobit Automotive GmbH */
#endif

/*------------------[AUTOSAR module identification]-------------------------*/

#if (defined MODULE_MODULE_ID)
#error MEMMAP_MODULE_ID already defined
#endif
/** \brief AUTOSAR module identification */
#define MEMMAP_MODULE_ID 195U

/*------------------[AUTOSAR release version identification]----------------*/

#if (!defined MEM_AR_MAJOR_VERSION)
/** \brief definition of the major version of the specification */
#define MEMMAP_AR_MAJOR_VERSION 4U
#endif

#if (!defined MEM_AR_MINOR_VERSION)
/** \brief definition of a minor version of the specification */
#define MEMMAP_AR_MINOR_VERSION 0U
#endif

#if (!defined MEM_AR_PATCH_VERSION)
/** \brief definition of a patch version of the specification */
#define MEMMAP_AR_PATCH_VERSION 3U
#endif

/*------------------[AUTOSAR module version identification]------------------*/

#if (!defined MEM_SW_MAJOR_VERSION)
/** \brief definition of the major version of this implementation */
#define MEMMAP_SW_MAJOR_VERSION 1U
#endif

#if (!defined MEM_SW_MINOR_VERSION)
/** \brief definition of a minor version of this implementation */
#define MEMMAP_SW_MINOR_VERSION 3U
#endif

#if (!defined MEM_SW_PATCH_VERSION)
/** \brief definition of a patch version of this implementation */
#define MEMMAP_SW_PATCH_VERSION 4U
#endif

/*------------------[MemMap error checking]----------------------------------*/

#if (defined MEMMAP_ERROR) /* to prevent double definition */
#error MEMMAP_ERROR defined, wrong MemMap.h usage
#endif /* if (!defined MEMMAP_ERROR) */

/** \brief Checks if this file has been correctly used
 **
 ** This definition checks if this file has been correctly included
 ** the last time.
 ** We do it here, before the big if-elif. */
#define MEMMAP_ERROR

/*------------------[MemMap extensions]--------------------------------------*/


#ifdef MEMMAP_ERROR
 #include <BLUpdater_MemMap.h>
#endif

#ifdef MEMMAP_ERROR
 #include <FlsLoader_MemMap.h>
#endif

#ifdef MEMMAP_ERROR
 #include <I2c_MemMap.h>
#endif

#ifdef MEMMAP_ERROR
 #include <IRQ_MemMap.h>
#endif

/*==================[inclusions]=============================================*/


#ifdef MEMMAP_ERROR
  #include <Atomics_MemMap.h>
#endif


#ifdef MEMMAP_ERROR
  #include <Base_MemMap.h>
#endif


#ifdef MEMMAP_ERROR
  #include <CanIf_MemMap.h>
#endif


#ifdef MEMMAP_ERROR
  #include <CanSM_MemMap.h>
#endif


#ifdef MEMMAP_ERROR
  #include <CanTp_MemMap.h>
#endif


#ifdef MEMMAP_ERROR
  #include <Can_17_McmCan_MemMap.h>
#endif


#ifdef MEMMAP_ERROR
  #include <Det_MemMap.h>
#endif


#ifdef MEMMAP_ERROR
  #include <EcuC_MemMap.h>
#endif


#ifdef MEMMAP_ERROR
  #include <McalLib_MemMap.h>
#endif


#ifdef MEMMAP_ERROR
  #include <Mcu_MemMap.h>
#endif


#ifdef MEMMAP_ERROR
  #include <PduR_MemMap.h>
#endif


#ifdef MEMMAP_ERROR
  #include <Port_MemMap.h>
#endif


#ifdef MEMMAP_ERROR
  #include <ResourceM_MemMap.h>
#endif


#ifdef MEMMAP_ERROR
  #undef MEMMAP_ERROR
  #error MEMMAP_ERROR defined, one or more memory sections or pragmas were not defined for any BSW descriptions.
#endif
