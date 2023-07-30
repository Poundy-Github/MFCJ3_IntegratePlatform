/**
 * \file
 *
 * \brief AUTOSAR Atomics
 *
 * This file contains the implementation of the AUTOSAR
 * module Atomics.
 *
 * \author Elektrobit Automotive GmbH, 91058 Erlangen, Germany
 *
 * Copyright 2017 - 2019 Elektrobit Automotive GmbH
 * All rights exclusively reserved for Elektrobit Automotive GmbH,
 * unless expressly agreed to otherwise.
 */
#if !defined(ATOMICS_OS_VERSION_COMPARE_H)
#define ATOMICS_OS_VERSION_COMPARE_H

#include <Os_Version.h>

#define ATOMICS_OS_IS_OLDER_THAN(major, minor, patch) \
	( (OS_SW_MAJOR_VERSION < (major)) || \
	  (OS_SW_MAJOR_VERSION == (major)) && (OS_SW_MINOR_VERSION < (minor)) || \
	  (OS_SW_MAJOR_VERSION == (major)) && (OS_SW_MINOR_VERSION == (minor)) && (OS_SW_PATCH_VERSION < (patch)) )

#define ATOMICS_OS_IS_YOUNGER_THAN(major, minor, patch) \
	( (OS_SW_MAJOR_VERSION > (major)) || \
	  (OS_SW_MAJOR_VERSION == (major)) && (OS_SW_MINOR_VERSION > (minor)) || \
	  (OS_SW_MAJOR_VERSION == (major)) && (OS_SW_MINOR_VERSION == (minor)) && (OS_SW_PATCH_VERSION > (patch)) )

#endif /* ATOMICS_OS_VERSION_COMPARE_H */
