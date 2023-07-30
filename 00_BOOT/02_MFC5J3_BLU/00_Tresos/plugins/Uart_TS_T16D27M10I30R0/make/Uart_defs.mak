# \file
#
# \brief AUTOSAR Uart
#
# This file contains the implementation of the AUTOSAR
# module Uart.
#
# \author Elektrobit Automotive GmbH, 91058 Erlangen, Germany
#
# Copyright 2005 - 2019 Elektrobit Automotive GmbH
# All rights exclusively reserved for Elektrobit Automotive GmbH,
# unless expressly agreed to otherwise.

#################################################################
# DEFINITIONS

Uart_CORE_PATH      ?= $(PLUGINS_BASE)\Uart_$(Uart_VARIANT)
Uart_OUTPUT_PATH    ?= $(AUTOSAR_BASE_OUTPUT_PATH)

Uart_GEN_FILES      += $(wildcard $(Uart_OUTPUT_PATH)\include\Uart_Cfg.h)
Uart_GEN_FILES      += $(wildcard $(Uart_OUTPUT_PATH)\include\Uart_PBcfg.h)
Uart_GEN_FILES      += $(wildcard $(Uart_OUTPUT_PATH)\src\Uart_PBcfg.c)

TRESOS_GEN_FILES   += $(Uart_GEN_FILES)

CC_INCLUDE_PATH    += $(Uart_CORE_PATH)\include \
                      $(Uart_OUTPUT_PATH)\include

