# \file
#
# \brief AUTOSAR Fls
#
# This file contains the implementation of the AUTOSAR
# module Fls.
#
# \author Elektrobit Automotive GmbH, 91058 Erlangen, Germany
#
# Copyright 2005 - 2019 Elektrobit Automotive GmbH
# All rights exclusively reserved for Elektrobit Automotive GmbH,
# unless expressly agreed to otherwise.

#################################################################
# REGISTRY

LIBRARIES_TO_BUILD     += Fls_src

Fls_src_FILES += $(Fls_CORE_PATH)\src\Fls_17_Dmu.c
Fls_src_FILES += $(Fls_CORE_PATH)\src\Fls_17_Dmu_ac.c
Fls_src_FILES += $(Fls_CORE_PATH)\src\Fls_17_Dmu_Irq.c
Fls_src_FILES += $(wildcard $(Fls_OUTPUT_PATH)\src\Fls_17_Dmu_PBcfg.c)

ifeq ($(TS_BUILD_POST_BUILD_BINARY),TRUE)
# If the post build binary shall be built do 
# not compile any files other then the postbuild files.
Fls_src_FILES :=
endif

.PHONY : complete_MCAL_origin Fls_MCAL_origin 

complete_MCAL_origin: Fls_MCAL_origin

Fls_MCAL_origin: remove_Eclipse_cache
	@${ECHO} * Preparing MCAL module Fls into vendor origin version
	@$(Fls_CORE_PATH)\perform_MCAL_change.bat origin

.PHONY : complete_MCAL_EB_update Fls_MCAL_EB_update

complete_MCAL_EB_update: Fls_MCAL_EB_update

Fls_MCAL_EB_update: remove_Eclipse_cache
	@${ECHO} * Preparing MCAL module Fls into EB updated version
	@$(Fls_CORE_PATH)\perform_MCAL_change.bat EB_update
