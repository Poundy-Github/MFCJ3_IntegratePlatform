/**
 * \file
 *
 * \brief AUTOSAR Base
 *
 * This file contains the implementation of the AUTOSAR
 * module Base.
 *
 * \author Elektrobit Automotive GmbH, 91058 Erlangen, Germany
 *
 * Copyright 2005 - 2019 Elektrobit Automotive GmbH
 * All rights exclusively reserved for Elektrobit Automotive GmbH,
 * unless expressly agreed to otherwise.
 */

/* !LINKSTO Base.ModuleInfo.HeaderFile,1 */
#if (!defined BASE_MODULES_H)
#define BASE_MODULES_H

/*==================[macros]=================================================*/

#ifndef BASE_BM_ENABLED
/** \brief Enable status of the module BM (/BM/BM) (VariantPreCompile) */
#define BASE_BM_ENABLED STD_ON
#endif

#ifndef BASE_BM_HEADER
/** \brief Name of the BM (/BM/BM) module's main header file */
#define BASE_BM_HEADER <BM.h>
#endif

#ifndef BASE_BASE_ENABLED
/** \brief Enable status of the module Base (/Base/Base) (VariantPreCompile) */
#define BASE_BASE_ENABLED STD_ON
#endif

#ifndef BASE_BASE_HEADER
/** \brief Name of the Base (/Base/Base) module's main header file */
#define BASE_BASE_HEADER <Base.h>
#endif

#ifndef BASE_DET_ENABLED
/** \brief Enable status of the module Det (/Det/Det) (VariantPreCompile) */
#define BASE_DET_ENABLED STD_ON
#endif

#ifndef BASE_DET_HEADER
/** \brief Name of the Det (/Det/Det) module's main header file */
#define BASE_DET_HEADER <Det.h>
#endif

#ifndef BASE_FLS_ENABLED
/** \brief Enable status of the module Fls (/Fls/Fls) (VariantPostBuild) */
#define BASE_FLS_ENABLED STD_ON
#endif

#ifndef BASE_FLS_17_DMU_ENABLED
/** \brief Enable status of the module Fls (/Fls/Fls) (VariantPostBuild) */
#define BASE_FLS_17_DMU_ENABLED STD_ON
#endif

#ifndef BASE_FLS_HEADER
/** \brief Name of the Fls (/Fls/Fls) module's main header file */
#define BASE_FLS_HEADER <Fls_17_Dmu.h>
#endif

#ifndef BASE_FLS_17_DMU_HEADER
/** \brief Name of the Fls (/Fls/Fls) module's main header file */
#define BASE_FLS_17_DMU_HEADER <Fls_17_Dmu.h>
#endif

#ifndef BASE_MCALLIB_ENABLED
/** \brief Enable status of the module McalLib (/McalLib/McalLib) (VariantPreCompile) */
#define BASE_MCALLIB_ENABLED STD_ON
#endif

#ifndef BASE_MCALLIB_HEADER
/** \brief Name of the McalLib (/McalLib/McalLib) module's main header file */
#define BASE_MCALLIB_HEADER <McalLib.h>
#endif

#ifndef BASE_MCU_ENABLED
/** \brief Enable status of the module Mcu (/Mcu/Mcu) (VariantPostBuild) */
#define BASE_MCU_ENABLED STD_ON
#endif

#ifndef BASE_MCU_HEADER
/** \brief Name of the Mcu (/Mcu/Mcu) module's main header file */
#define BASE_MCU_HEADER <Mcu.h>
#endif

#ifndef BASE_MEMMAP_ENABLED
/** \brief Enable status of the module MemMap (/MemMap/MemMap) (VariantPreCompile) */
#define BASE_MEMMAP_ENABLED STD_ON
#endif

#ifndef BASE_MEMMAP_HEADER
/** \brief Name of the MemMap (/MemMap/MemMap) module's main header file */
#define BASE_MEMMAP_HEADER <MemMap.h>
#endif

#ifndef BASE_RESOURCEM_ENABLED
/** \brief Enable status of the module ResourceM (/Resource/ResourceM) (VariantPreCompile) */
#define BASE_RESOURCEM_ENABLED STD_OFF
#endif

#ifndef BASE_RESOURCEM_HEADER
/** \brief Name of the ResourceM (/Resource/ResourceM) module's main header file */
#define BASE_RESOURCEM_HEADER <ResourceM.h>
#endif

#endif /* if !defined( BASE_MODULES_H ) */
/*==================[end of file]============================================*/
