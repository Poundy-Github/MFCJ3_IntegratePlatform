# \file
#
# \brief AUTOSAR Atomics
#
# This file contains the implementation of the AUTOSAR
# module Atomics.
#
# \author Elektrobit Automotive GmbH, 91058 Erlangen, Germany
#
# Copyright 2017 - 2019 Elektrobit Automotive GmbH
# All rights exclusively reserved for Elektrobit Automotive GmbH,
# unless expressly agreed to otherwise.

Atomics_CORE_PATH ?= $(PLUGINS_BASE)\Atomics_$(Atomics_VARIANT)

CC_INCLUDE_PATH += $(Atomics_CORE_PATH)\include

Atomics_FILES := \
	$(Atomics_CORE_PATH)\src\Atomics.c \
	$(Atomics_CORE_PATH)\src\Atomics_TSPlatforms.c

# The variable ATOMICS_USE_GENERIC_IMPL is defined via the Make command-line.
# It selects either the generic or specialized implementation of the Atomics
# module. For further information please refer to the AutoCore Generic Base
# documentation.
#
# Please select one of the following configuration options.
# 1. set ATOMICS_USE_GENERIC_IMPL to 0 to select the specialized implementation,
#    which depends on EB tresos AutoCore OS, or
# 2. set ATOMICS_USE_GENERIC_IMPL to 1 to select the generic implementation,
#    which depends on AUTOSAR features only.
ifndef ATOMICS_USE_GENERIC_IMPL
$(error "Please choose between generic or specialized implementation by defining ATOMICS_USE_GENERIC_IMPL appropriately.")
endif

ifneq ($(ATOMICS_USE_GENERIC_IMPL),0)
# The generic implementation shall be used and not the specialized one provided
# by EB tresos AutoCore OS. This implementation is contained in the files in the
# list Atomics_FILES.
CC_FILES_TO_BUILD += $(Atomics_FILES)

ifeq ($(MISRA_MODULE),Atomics)
# The Makefiles in asc_Testing for Polysapce expect the list of files to check
# in the Make variable Atomics_CC_FILES_TO_BUILD.
Atomics_CC_FILES_TO_BUILD += $(Atomics_FILES)
endif # $(MISRA_MODULE) == "Atomics"
endif # $(ATOMICS_USE_GENERIC_IMPL) != 0

PREPROCESSOR_DEFINES += TS_Atomics_use_generic_impl
TS_Atomics_use_generic_impl_KEY = ATOMICS_USE_GENERIC_IMPL
TS_Atomics_use_generic_impl_VALUE = $(ATOMICS_USE_GENERIC_IMPL)
