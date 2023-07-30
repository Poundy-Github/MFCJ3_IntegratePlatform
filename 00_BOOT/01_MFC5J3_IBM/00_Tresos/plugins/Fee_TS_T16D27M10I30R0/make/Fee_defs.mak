# \file
#
# \brief AUTOSAR Fee
#
# This file contains the implementation of the AUTOSAR
# module Fee.
#
# \author Elektrobit Automotive GmbH, 91058 Erlangen, Germany
#
# Copyright 2005 - 2019 Elektrobit Automotive GmbH
# All rights exclusively reserved for Elektrobit Automotive GmbH,
# unless expressly agreed to otherwise.

#################################################################
# DEFINITIONS

Fee_CORE_PATH      ?= $(PLUGINS_BASE)\Fee_$(Fee_VARIANT)
Fee_OUTPUT_PATH    ?= $(AUTOSAR_BASE_OUTPUT_PATH)

Fee_GEN_FILES      += $(wildcard $(Fee_OUTPUT_PATH)\include\Fee_Cfg.h)
Fee_GEN_FILES      += $(wildcard $(Fee_OUTPUT_PATH)\include\Fee_PBcfg.h)
Fee_GEN_FILES      += $(wildcard $(Fee_OUTPUT_PATH)\src\Fee_PBcfg.c)

TRESOS_GEN_FILES   += $(Fee_GEN_FILES)

CC_INCLUDE_PATH    += $(Fee_CORE_PATH)\include \
                      $(Fee_OUTPUT_PATH)\include

