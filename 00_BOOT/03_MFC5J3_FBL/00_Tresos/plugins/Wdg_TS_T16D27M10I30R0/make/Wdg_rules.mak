# \file
#
# \brief AUTOSAR Wdg
#
# This file contains the implementation of the AUTOSAR
# module Wdg.
#
# \author Elektrobit Automotive GmbH, 91058 Erlangen, Germany
#
# Copyright 2005 - 2019 Elektrobit Automotive GmbH
# All rights exclusively reserved for Elektrobit Automotive GmbH,
# unless expressly agreed to otherwise.

#################################################################
# REGISTRY

LIBRARIES_TO_BUILD     += Wdg_src

Wdg_src_FILES += $(Wdg_CORE_PATH)\src\Wdg_17_Scu.c
Wdg_src_FILES += $(wildcard $(Wdg_OUTPUT_PATH)\src\Wdg_17_Scu_PBcfg.c)

ifeq ($(TS_BUILD_POST_BUILD_BINARY),TRUE)
# If the post build binary shall be built do 
# not compile any files other then the postbuild files.
Wdg_src_FILES :=
endif

.PHONY : complete_MCAL_origin Wdg_MCAL_origin 

complete_MCAL_origin: Wdg_MCAL_origin

Wdg_MCAL_origin: remove_Eclipse_cache
	@${ECHO} * Preparing MCAL module Wdg into vendor origin version
	@$(Wdg_CORE_PATH)\perform_MCAL_change.bat origin

.PHONY : complete_MCAL_EB_update Wdg_MCAL_EB_update

complete_MCAL_EB_update: Wdg_MCAL_EB_update

Wdg_MCAL_EB_update: remove_Eclipse_cache
	@${ECHO} * Preparing MCAL module Wdg into EB updated version
	@$(Wdg_CORE_PATH)\perform_MCAL_change.bat EB_update
