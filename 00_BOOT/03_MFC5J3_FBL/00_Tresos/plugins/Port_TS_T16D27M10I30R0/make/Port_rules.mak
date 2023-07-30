# \file
#
# \brief AUTOSAR Port
#
# This file contains the implementation of the AUTOSAR
# module Port.
#
# \author Elektrobit Automotive GmbH, 91058 Erlangen, Germany
#
# Copyright 2005 - 2019 Elektrobit Automotive GmbH
# All rights exclusively reserved for Elektrobit Automotive GmbH,
# unless expressly agreed to otherwise.

#################################################################
# REGISTRY

LIBRARIES_TO_BUILD     += Port_src

Port_src_FILES += $(Port_CORE_PATH)\src\Port.c
Port_src_FILES += $(wildcard $(Port_OUTPUT_PATH)\src\Port_PBcfg.c)

ifeq ($(TS_BUILD_POST_BUILD_BINARY),TRUE)
# If the post build binary shall be built do 
# not compile any files other then the postbuild files.
Port_src_FILES :=
endif

.PHONY : complete_MCAL_origin Port_MCAL_origin 

complete_MCAL_origin: Port_MCAL_origin

Port_MCAL_origin: remove_Eclipse_cache
	@${ECHO} * Preparing MCAL module Port into vendor origin version
	@$(Port_CORE_PATH)\perform_MCAL_change.bat origin

.PHONY : complete_MCAL_EB_update Port_MCAL_EB_update

complete_MCAL_EB_update: Port_MCAL_EB_update

Port_MCAL_EB_update: remove_Eclipse_cache
	@${ECHO} * Preparing MCAL module Port into EB updated version
	@$(Port_CORE_PATH)\perform_MCAL_change.bat EB_update
