# \file
#
# \brief AUTOSAR Spi
#
# This file contains the implementation of the AUTOSAR
# module Spi.
#
# \author Elektrobit Automotive GmbH, 91058 Erlangen, Germany
#
# Copyright 2005 - 2019 Elektrobit Automotive GmbH
# All rights exclusively reserved for Elektrobit Automotive GmbH,
# unless expressly agreed to otherwise.

#################################################################
# DEFINITIONS

Spi_CORE_PATH      ?= $(PLUGINS_BASE)\Spi_$(Spi_VARIANT)
Spi_OUTPUT_PATH    ?= $(AUTOSAR_BASE_OUTPUT_PATH)

Spi_GEN_FILES      += $(wildcard $(Spi_OUTPUT_PATH)\include\Spi_Cfg.h)
Spi_GEN_FILES      += $(wildcard $(Spi_OUTPUT_PATH)\include\Spi_PBcfg.h)
Spi_GEN_FILES      += $(wildcard $(Spi_OUTPUT_PATH)\src\Spi_PBcfg.c)

TRESOS_GEN_FILES   += $(Spi_GEN_FILES)

CC_INCLUDE_PATH    += $(Spi_CORE_PATH)\include \
                      $(Spi_OUTPUT_PATH)\include

