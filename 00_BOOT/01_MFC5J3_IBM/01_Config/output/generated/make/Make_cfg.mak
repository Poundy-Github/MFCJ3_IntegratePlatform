# \file
#
# \brief AUTOSAR Make
#
# This file contains the implementation of the AUTOSAR
# module Make.
#
# \author Elektrobit Automotive GmbH, 91058 Erlangen, Germany
#
# Copyright 2005 - 2019 Elektrobit Automotive GmbH
# All rights exclusively reserved for Elektrobit Automotive GmbH,
# unless expressly agreed to otherwise.
#################################################################
# This makefile exports parameters derived from the
# project configuration into variables for make

# Only include these variables once
ifndef PROJECT_MODULES

# project name in workspace
TRESOS2_PROJECT_NAME := Boot
TRESOS2_ECU_ID       := demoBoot_OemInd_can_asr

# target and derivate
TARGET   := TRICORE
DERIVATE := TC38XQ

ifeq (,$(ENABLED_PLUGINS))
# In case enabled modules are NOT specified explicitly
# use all enabled modules (including modules, that are NOT generated)
PROJECT_MODULES := Atomics BM Base Compiler Det Fls Make McalLib Mcu MemMap Platforms Resource
else
# otherwise only use generated modules
PROJECT_MODULES := Atomics BM Base Compiler Det Fls Make McalLib Mcu MemMap Platforms Resource
endif

# add tresos2 make plugin if not yet contained in SOFTWARE_MODULES
SOFTWARE_MODULES := $(strip $(filter-out tresos2,$(SOFTWARE_MODULES)) tresos2)

# There might already modules added to SOFTWARE_MODULES. So add only what's
# not yet contained SOFTWARE_MODULES.
# Duplicated entries are removed by the sort function.
SOFTWARE_MODULES += $(sort $(filter-out $(SOFTWARE_MODULES),$(PROJECT_MODULES)))

# variables defining module versions and locations of the plugins
Atomics_VARIANT   := TS_TxDxM1I0R0
Atomics_CORE_PATH := $(TRESOS_BASE)/plugins/Atomics_TS_TxDxM1I0R0
BM_VARIANT   := TS_TxDxM1I15R0
BM_CORE_PATH := $(TRESOS_BASE)/plugins/BM_TS_TxDxM1I15R0
Base_VARIANT   := TS_TxDxM5I0R0
Base_CORE_PATH := $(TRESOS_BASE)/plugins/Base_TS_TxDxM5I0R0
Compiler_VARIANT   := TS_TxDxM1I0R0
Compiler_CORE_PATH := $(TRESOS_BASE)/plugins/Compiler_TS_TxDxM1I0R0
Det_VARIANT   := TS_TxDxM6I5R0
Det_CORE_PATH := $(TRESOS_BASE)/plugins/Det_TS_TxDxM6I5R0
Fls_VARIANT   := TS_T16D27M10I30R0
Fls_CORE_PATH := $(TRESOS_BASE)/plugins/Fls_TS_T16D27M10I30R0
Make_VARIANT   := TS_TxDxM4I0R0
Make_CORE_PATH := $(TRESOS_BASE)/plugins/Make_TS_TxDxM4I0R0
McalLib_VARIANT   := TS_T16D27M10I30R0
McalLib_CORE_PATH := $(TRESOS_BASE)/plugins/McalLib_TS_T16D27M10I30R0
Mcu_VARIANT   := TS_T16D27M10I30R0
Mcu_CORE_PATH := $(TRESOS_BASE)/plugins/Mcu_TS_T16D27M10I30R0
MemMap_VARIANT   := TS_TxDxM1I3R0
MemMap_CORE_PATH := $(TRESOS_BASE)/plugins/MemMap_TS_TxDxM1I3R0
Platforms_VARIANT   := TS_T16D27M3I0R0
Platforms_CORE_PATH := $(TRESOS_BASE)/plugins/Platforms_TS_T16D27M3I0R0
Resource_VARIANT   := TS_T16D27M10I30R0
Resource_CORE_PATH := $(TRESOS_BASE)/plugins/Resource_TS_T16D27M10I30R0

# variables defining module generation output paths

# default output path for generated files
GEN_OUTPUT_PATH  ?= $(PROJECT_ROOT)/output/generated
# list of all output paths of generated files
GEN_OUTPUT_PATHS ?= \
 $(GEN_OUTPUT_PATH)
override GEN_OUTPUT_PATH  := $(subst \,/,$(GEN_OUTPUT_PATH))
override GEN_OUTPUT_PATHS := $(subst \,/,$(GEN_OUTPUT_PATHS))

# output path for files created by the build environment
PROJECT_OUTPUT_PATH ?= $(abspath $(GEN_OUTPUT_PATH)/..)

# for compatibility reasons we need the AUTOSAR_BASE_OUTPUT_PATH
AUTOSAR_BASE_OUTPUT_PATH ?= $(GEN_OUTPUT_PATH)
override AUTOSAR_BASE_OUTPUT_PATH := $(subst \,/,$(AUTOSAR_BASE_OUTPUT_PATH))

endif


# No Os configuration found, declare Os Vendor empty
OS_VENDOR :=
