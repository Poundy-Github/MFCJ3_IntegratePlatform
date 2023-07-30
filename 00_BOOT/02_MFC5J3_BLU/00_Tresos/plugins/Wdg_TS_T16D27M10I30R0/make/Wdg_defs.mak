# \file
#
# \brief AUTOSAR Wdg
#
# This file contains the implementation of the AUTOSAR
# module Wdg.
#
# \author Elektrobit Automotive GmbH, 91058 Erlangen, Germany
#
# Copyright 2005 - 2019 Elektrobit Automotive GmbH
# All rights exclusively reserved for Elektrobit Automotive GmbH,
# unless expressly agreed to otherwise.

#################################################################
# DEFINITIONS

Wdg_CORE_PATH      ?= $(PLUGINS_BASE)\Wdg_$(Wdg_VARIANT)
Wdg_OUTPUT_PATH    ?= $(AUTOSAR_BASE_OUTPUT_PATH)

Wdg_GEN_FILES      += $(wildcard $(Wdg_OUTPUT_PATH)\include\Wdg_17_Scu_Cfg.h)
Wdg_GEN_FILES      += $(wildcard $(Wdg_OUTPUT_PATH)\include\Wdg_17_Scu_PBcfg.h)
Wdg_GEN_FILES      += $(wildcard $(Wdg_OUTPUT_PATH)\src\Wdg_17_Scu_PBcfg.c)

TRESOS_GEN_FILES   += $(Wdg_GEN_FILES)

CC_INCLUDE_PATH    += $(Wdg_CORE_PATH)\include \
                      $(Wdg_OUTPUT_PATH)\include

