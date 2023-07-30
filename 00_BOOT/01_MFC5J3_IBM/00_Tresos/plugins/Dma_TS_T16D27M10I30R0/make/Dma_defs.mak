# \file
#
# \brief AUTOSAR Dma
#
# This file contains the implementation of the AUTOSAR
# module Dma.
#
# \author Elektrobit Automotive GmbH, 91058 Erlangen, Germany
#
# Copyright 2005 - 2019 Elektrobit Automotive GmbH
# All rights exclusively reserved for Elektrobit Automotive GmbH,
# unless expressly agreed to otherwise.

#################################################################
# DEFINITIONS

Dma_CORE_PATH      ?= $(PLUGINS_BASE)\Dma_$(Dma_VARIANT)
Dma_OUTPUT_PATH    ?= $(AUTOSAR_BASE_OUTPUT_PATH)

Dma_GEN_FILES      += $(wildcard $(Dma_OUTPUT_PATH)\include\Dma_Cfg.h)
Dma_GEN_FILES      += $(wildcard $(Dma_OUTPUT_PATH)\include\Dma_PBcfg.h)
Dma_GEN_FILES      += $(wildcard $(Dma_OUTPUT_PATH)\src\Dma_PBcfg.c)

TRESOS_GEN_FILES   += $(Dma_GEN_FILES)

CC_INCLUDE_PATH    += $(Dma_CORE_PATH)\include \
                      $(Dma_OUTPUT_PATH)\include

