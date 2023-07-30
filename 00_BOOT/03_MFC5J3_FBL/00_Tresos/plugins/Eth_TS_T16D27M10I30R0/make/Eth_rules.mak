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
# REGISTRY

LIBRARIES_TO_BUILD     += Eth_src

Eth_src_FILES += $(Eth_CORE_PATH)\src\Eth_17_GEthMac.c
Eth_src_FILES += $(Eth_CORE_PATH)\src\Eth_17_GEthMac_Irq.c
Eth_src_FILES += $(wildcard $(Eth_OUTPUT_PATH)\src\Eth_17_GEthMac_PBcfg.c)

ifeq ($(TS_BUILD_POST_BUILD_BINARY),TRUE)
# If the post build binary shall be built do 
# not compile any files other then the postbuild files.
Eth_src_FILES :=
endif

.PHONY : complete_MCAL_origin Eth_MCAL_origin 

complete_MCAL_origin: Eth_MCAL_origin

Eth_MCAL_origin: remove_Eclipse_cache
	@${ECHO} * Preparing MCAL module Eth into vendor origin version
	@$(Eth_CORE_PATH)\perform_MCAL_change.bat origin

.PHONY : complete_MCAL_EB_update Eth_MCAL_EB_update

complete_MCAL_EB_update: Eth_MCAL_EB_update

Eth_MCAL_EB_update: remove_Eclipse_cache
	@${ECHO} * Preparing MCAL module Eth into EB updated version
	@$(Eth_CORE_PATH)\perform_MCAL_change.bat EB_update
