# \file
#
# \brief AUTOSAR Icu
#
# This file contains the implementation of the AUTOSAR
# module Icu.
#
# \author Elektrobit Automotive GmbH, 91058 Erlangen, Germany
#
# Copyright 2005 - 2019 Elektrobit Automotive GmbH
# All rights exclusively reserved for Elektrobit Automotive GmbH,
# unless expressly agreed to otherwise.

#################################################################
# DEFINITIONS

Icu_CORE_PATH      ?= $(PLUGINS_BASE)\Icu_$(Icu_VARIANT)
Icu_OUTPUT_PATH    ?= $(AUTOSAR_BASE_OUTPUT_PATH)

Icu_GEN_FILES      += $(wildcard $(Icu_OUTPUT_PATH)\include\Icu_17_TimerIp_Cfg.h)
Icu_GEN_FILES      += $(wildcard $(Icu_OUTPUT_PATH)\include\Icu_17_TimerIp_PBcfg.h)
Icu_GEN_FILES      += $(wildcard $(Icu_OUTPUT_PATH)\src\Icu_17_TimerIp_PBcfg.c)

TRESOS_GEN_FILES   += $(Icu_GEN_FILES)

CC_INCLUDE_PATH    += $(Icu_CORE_PATH)\include \
                      $(Icu_OUTPUT_PATH)\include

