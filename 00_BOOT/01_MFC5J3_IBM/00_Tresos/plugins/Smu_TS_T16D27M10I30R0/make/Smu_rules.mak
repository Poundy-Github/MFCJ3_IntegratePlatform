# \file
#
# \brief AUTOSAR Smu
#
# This file contains the implementation of the AUTOSAR
# module Smu.
#
# \author Elektrobit Automotive GmbH, 91058 Erlangen, Germany
#
# Copyright 2005 - 2019 Elektrobit Automotive GmbH
# All rights exclusively reserved for Elektrobit Automotive GmbH,
# unless expressly agreed to otherwise.

#################################################################
# REGISTRY

LIBRARIES_TO_BUILD     += Smu_src

Smu_src_FILES += $(Smu_CORE_PATH)\src\Smu.c
Smu_src_FILES += $(wildcard $(Smu_OUTPUT_PATH)\src\Smu_PBcfg.c)

ifeq ($(TS_BUILD_POST_BUILD_BINARY),TRUE)
# If the post build binary shall be built do 
# not compile any files other then the postbuild files.
Smu_src_FILES :=
endif

.PHONY : complete_MCAL_origin Smu_MCAL_origin 

complete_MCAL_origin: Smu_MCAL_origin

Smu_MCAL_origin: remove_Eclipse_cache
	@${ECHO} * Preparing MCAL module Smu into vendor origin version
	@$(Smu_CORE_PATH)\perform_MCAL_change.bat origin

.PHONY : complete_MCAL_EB_update Smu_MCAL_EB_update

complete_MCAL_EB_update: Smu_MCAL_EB_update

Smu_MCAL_EB_update: remove_Eclipse_cache
	@${ECHO} * Preparing MCAL module Smu into EB updated version
	@$(Smu_CORE_PATH)\perform_MCAL_change.bat EB_update
