# \file
#
# \brief AUTOSAR Pwm
#
# This file contains the implementation of the AUTOSAR
# module Pwm.
#
# \author Elektrobit Automotive GmbH, 91058 Erlangen, Germany
#
# Copyright 2005 - 2019 Elektrobit Automotive GmbH
# All rights exclusively reserved for Elektrobit Automotive GmbH,
# unless expressly agreed to otherwise.

#################################################################
# DEFINITIONS

Pwm_CORE_PATH      ?= $(PLUGINS_BASE)\Pwm_$(Pwm_VARIANT)
Pwm_OUTPUT_PATH    ?= $(AUTOSAR_BASE_OUTPUT_PATH)

Pwm_GEN_FILES      += $(wildcard $(Pwm_OUTPUT_PATH)\include\Pwm_17_GtmCcu6_Cfg.h)
Pwm_GEN_FILES      += $(wildcard $(Pwm_OUTPUT_PATH)\include\Pwm_17_GtmCcu6_PBcfg.h)
Pwm_GEN_FILES      += $(wildcard $(Pwm_OUTPUT_PATH)\src\Pwm_17_GtmCcu6_PBcfg.c)

TRESOS_GEN_FILES   += $(Pwm_GEN_FILES)

CC_INCLUDE_PATH    += $(Pwm_CORE_PATH)\include \
                      $(Pwm_OUTPUT_PATH)\include

