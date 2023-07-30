# \file
#
# \brief AUTOSAR Icu
#
# This file contains the implementation of the AUTOSAR
# module Icu.
#
# \author Elektrobit Automotive GmbH, 91058 Erlangen, Germany
#
# Copyright 2005 - 2019 Elektrobit Automotive GmbH
# All rights exclusively reserved for Elektrobit Automotive GmbH,
# unless expressly agreed to otherwise.

#################################################################
# REGISTRY

LIBRARIES_TO_BUILD     += Icu_src

Icu_src_FILES += $(Icu_CORE_PATH)\src\Icu_17_TimerIp.c
Icu_src_FILES += $(Icu_CORE_PATH)\src\Eru_Irq.c
Icu_src_FILES += $(Icu_CORE_PATH)\src\Icu_17_TimerIp_Irq.c
Icu_src_FILES += $(wildcard $(Icu_OUTPUT_PATH)\src\Icu_17_TimerIp_PBcfg.c)

ifeq ($(TS_BUILD_POST_BUILD_BINARY),TRUE)
# If the post build binary shall be built do 
# not compile any files other then the postbuild files.
Icu_src_FILES :=
endif

.PHONY : complete_MCAL_origin Icu_MCAL_origin 

complete_MCAL_origin: Icu_MCAL_origin

Icu_MCAL_origin: remove_Eclipse_cache
	@${ECHO} * Preparing MCAL module Icu into vendor origin version
	@$(Icu_CORE_PATH)\perform_MCAL_change.bat origin

.PHONY : complete_MCAL_EB_update Icu_MCAL_EB_update

complete_MCAL_EB_update: Icu_MCAL_EB_update

Icu_MCAL_EB_update: remove_Eclipse_cache
	@${ECHO} * Preparing MCAL module Icu into EB updated version
	@$(Icu_CORE_PATH)\perform_MCAL_change.bat EB_update
