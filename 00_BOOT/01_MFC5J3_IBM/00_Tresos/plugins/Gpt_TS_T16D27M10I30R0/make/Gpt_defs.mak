# \file
#
# \brief AUTOSAR Gpt
#
# This file contains the implementation of the AUTOSAR
# module Gpt.
#
# \author Elektrobit Automotive GmbH, 91058 Erlangen, Germany
#
# Copyright 2005 - 2019 Elektrobit Automotive GmbH
# All rights exclusively reserved for Elektrobit Automotive GmbH,
# unless expressly agreed to otherwise.

#################################################################
# DEFINITIONS

Gpt_CORE_PATH      ?= $(PLUGINS_BASE)\Gpt_$(Gpt_VARIANT)
Gpt_OUTPUT_PATH    ?= $(AUTOSAR_BASE_OUTPUT_PATH)

Gpt_GEN_FILES      += $(wildcard $(Gpt_OUTPUT_PATH)\include\Gpt_Cfg.h)
Gpt_GEN_FILES      += $(wildcard $(Gpt_OUTPUT_PATH)\include\Gpt_PBcfg.h)
Gpt_GEN_FILES      += $(wildcard $(Gpt_OUTPUT_PATH)\src\Gpt_PBcfg.c)

TRESOS_GEN_FILES   += $(Gpt_GEN_FILES)

CC_INCLUDE_PATH    += $(Gpt_CORE_PATH)\include \
                      $(Gpt_OUTPUT_PATH)\include

