# \file
#
# \brief AUTOSAR Eth
#
# This file contains the implementation of the AUTOSAR
# module Eth.
#
# \author Elektrobit Automotive GmbH, 91058 Erlangen, Germany
#
# Copyright 2005 - 2019 Elektrobit Automotive GmbH
# All rights exclusively reserved for Elektrobit Automotive GmbH,
# unless expressly agreed to otherwise.

#################################################################
# DEFINITIONS

Eth_CORE_PATH      ?= $(PLUGINS_BASE)\Eth_$(Eth_VARIANT)
Eth_OUTPUT_PATH    ?= $(AUTOSAR_BASE_OUTPUT_PATH)

Eth_GEN_FILES      += $(wildcard $(Eth_OUTPUT_PATH)\include\Eth_17_GEthMac_Cfg.h)
Eth_GEN_FILES      += $(wildcard $(Eth_OUTPUT_PATH)\include\Eth_17_GEthMac_PBcfg.h)
Eth_GEN_FILES      += $(wildcard $(Eth_OUTPUT_PATH)\src\Eth_17_GEthMac_PBcfg.c)

TRESOS_GEN_FILES   += $(Eth_GEN_FILES)

CC_INCLUDE_PATH    += $(Eth_CORE_PATH)\include \
                      $(Eth_OUTPUT_PATH)\include

