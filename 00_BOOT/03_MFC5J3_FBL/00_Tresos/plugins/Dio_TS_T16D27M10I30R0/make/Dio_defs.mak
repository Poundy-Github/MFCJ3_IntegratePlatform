# \file
#
# \brief AUTOSAR Dio
#
# This file contains the implementation of the AUTOSAR
# module Dio.
#
# \author Elektrobit Automotive GmbH, 91058 Erlangen, Germany
#
# Copyright 2005 - 2019 Elektrobit Automotive GmbH
# All rights exclusively reserved for Elektrobit Automotive GmbH,
# unless expressly agreed to otherwise.

#################################################################
# DEFINITIONS

Dio_CORE_PATH      ?= $(PLUGINS_BASE)\Dio_$(Dio_VARIANT)
Dio_OUTPUT_PATH    ?= $(AUTOSAR_BASE_OUTPUT_PATH)

Dio_GEN_FILES      += $(wildcard $(Dio_OUTPUT_PATH)\include\Dio_Cfg.h)
Dio_GEN_FILES      += $(wildcard $(Dio_OUTPUT_PATH)\src\Dio_Lcfg.c)

TRESOS_GEN_FILES   += $(Dio_GEN_FILES)

CC_INCLUDE_PATH    += $(Dio_CORE_PATH)\include \
                      $(Dio_OUTPUT_PATH)\include

