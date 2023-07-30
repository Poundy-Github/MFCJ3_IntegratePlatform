# \file
#
# \brief AUTOSAR Sent
#
# This file contains the implementation of the AUTOSAR
# module Sent.
#
# \author Elektrobit Automotive GmbH, 91058 Erlangen, Germany
#
# Copyright 2005 - 2019 Elektrobit Automotive GmbH
# All rights exclusively reserved for Elektrobit Automotive GmbH,
# unless expressly agreed to otherwise.

#################################################################
# DEFINITIONS

Sent_CORE_PATH      ?= $(PLUGINS_BASE)\Sent_$(Sent_VARIANT)
Sent_OUTPUT_PATH    ?= $(AUTOSAR_BASE_OUTPUT_PATH)

Sent_GEN_FILES      += $(wildcard $(Sent_OUTPUT_PATH)\include\Sent_Cfg.h)
Sent_GEN_FILES      += $(wildcard $(Sent_OUTPUT_PATH)\include\Sent_PBcfg.h)
Sent_GEN_FILES      += $(wildcard $(Sent_OUTPUT_PATH)\src\Sent_PBcfg.c)

TRESOS_GEN_FILES   += $(Sent_GEN_FILES)

CC_INCLUDE_PATH    += $(Sent_CORE_PATH)\include \
                      $(Sent_OUTPUT_PATH)\include

