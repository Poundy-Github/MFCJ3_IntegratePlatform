# \file
#
# \brief AUTOSAR Pwm
#
# This file contains the implementation of the AUTOSAR
# module Pwm.
#
# \author Elektrobit Automotive GmbH, 91058 Erlangen, Germany
#
# Copyright 2005 - 2019 Elektrobit Automotive GmbH
# All rights exclusively reserved for Elektrobit Automotive GmbH,
# unless expressly agreed to otherwise.

#################################################################
# REGISTRY

LIBRARIES_TO_BUILD     += Pwm_src

Pwm_src_FILES += $(Pwm_CORE_PATH)\src\Pwm_17_GtmCcu6.c
Pwm_src_FILES += $(wildcard $(Pwm_OUTPUT_PATH)\src\Pwm_17_GtmCcu6_PBcfg.c)

ifeq ($(TS_BUILD_POST_BUILD_BINARY),TRUE)
# If the post build binary shall be built do 
# not compile any files other then the postbuild files.
Pwm_src_FILES :=
endif

.PHONY : complete_MCAL_origin Pwm_MCAL_origin 

complete_MCAL_origin: Pwm_MCAL_origin

Pwm_MCAL_origin: remove_Eclipse_cache
	@${ECHO} * Preparing MCAL module Pwm into vendor origin version
	@$(Pwm_CORE_PATH)\perform_MCAL_change.bat origin

.PHONY : complete_MCAL_EB_update Pwm_MCAL_EB_update

complete_MCAL_EB_update: Pwm_MCAL_EB_update

Pwm_MCAL_EB_update: remove_Eclipse_cache
	@${ECHO} * Preparing MCAL module Pwm into EB updated version
	@$(Pwm_CORE_PATH)\perform_MCAL_change.bat EB_update
