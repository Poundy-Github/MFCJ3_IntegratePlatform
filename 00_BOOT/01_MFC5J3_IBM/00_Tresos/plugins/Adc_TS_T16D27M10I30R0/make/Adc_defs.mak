# \file
#
# \brief AUTOSAR Adc
#
# This file contains the implementation of the AUTOSAR
# module Adc.
#
# \author Elektrobit Automotive GmbH, 91058 Erlangen, Germany
#
# Copyright 2005 - 2019 Elektrobit Automotive GmbH
# All rights exclusively reserved for Elektrobit Automotive GmbH,
# unless expressly agreed to otherwise.

#################################################################
# DEFINITIONS

Adc_CORE_PATH      ?= $(PLUGINS_BASE)\Adc_$(Adc_VARIANT)
Adc_OUTPUT_PATH    ?= $(AUTOSAR_BASE_OUTPUT_PATH)

Adc_GEN_FILES      += $(wildcard $(Adc_OUTPUT_PATH)\include\Adc_Cfg.h)
Adc_GEN_FILES      += $(wildcard $(Adc_OUTPUT_PATH)\include\Adc_PBcfg.h)
Adc_GEN_FILES      += $(wildcard $(Adc_OUTPUT_PATH)\src\Adc_PBcfg.c)

TRESOS_GEN_FILES   += $(Adc_GEN_FILES)

CC_INCLUDE_PATH    += $(Adc_CORE_PATH)\include \
                      $(Adc_OUTPUT_PATH)\include

