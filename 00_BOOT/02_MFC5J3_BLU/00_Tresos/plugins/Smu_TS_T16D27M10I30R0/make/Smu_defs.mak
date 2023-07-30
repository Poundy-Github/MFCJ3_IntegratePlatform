# \file
#
# \brief AUTOSAR Smu
#
# This file contains the implementation of the AUTOSAR
# module Smu.
#
# \author Elektrobit Automotive GmbH, 91058 Erlangen, Germany
#
# Copyright 2005 - 2019 Elektrobit Automotive GmbH
# All rights exclusively reserved for Elektrobit Automotive GmbH,
# unless expressly agreed to otherwise.

#################################################################
# DEFINITIONS

Smu_CORE_PATH      ?= $(PLUGINS_BASE)\Smu_$(Smu_VARIANT)
Smu_OUTPUT_PATH    ?= $(AUTOSAR_BASE_OUTPUT_PATH)

Smu_GEN_FILES      += $(wildcard $(Smu_OUTPUT_PATH)\include\Smu_Cfg.h)
Smu_GEN_FILES      += $(wildcard $(Smu_OUTPUT_PATH)\include\Smu_PBcfg.h)
Smu_GEN_FILES      += $(wildcard $(Smu_OUTPUT_PATH)\src\Smu_PBcfg.c)

TRESOS_GEN_FILES   += $(Smu_GEN_FILES)

CC_INCLUDE_PATH    += $(Smu_CORE_PATH)\include \
                      $(Smu_OUTPUT_PATH)\include

