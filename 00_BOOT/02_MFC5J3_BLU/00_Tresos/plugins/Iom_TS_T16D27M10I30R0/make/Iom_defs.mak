# \file
#
# \brief AUTOSAR Iom
#
# This file contains the implementation of the AUTOSAR
# module Iom.
#
# \author Elektrobit Automotive GmbH, 91058 Erlangen, Germany
#
# Copyright 2005 - 2019 Elektrobit Automotive GmbH
# All rights exclusively reserved for Elektrobit Automotive GmbH,
# unless expressly agreed to otherwise.

#################################################################
# DEFINITIONS

Iom_CORE_PATH      ?= $(PLUGINS_BASE)\Iom_$(Iom_VARIANT)
Iom_OUTPUT_PATH    ?= $(AUTOSAR_BASE_OUTPUT_PATH)

Iom_GEN_FILES      += $(wildcard $(Iom_OUTPUT_PATH)\include\Iom_Cfg.h)
Iom_GEN_FILES      += $(wildcard $(Iom_OUTPUT_PATH)\include\Iom_PBcfg.h)
Iom_GEN_FILES      += $(wildcard $(Iom_OUTPUT_PATH)\src\Iom_PBCfg.c)

TRESOS_GEN_FILES   += $(Iom_GEN_FILES)

CC_INCLUDE_PATH    += $(Iom_CORE_PATH)\include \
                      $(Iom_OUTPUT_PATH)\include

