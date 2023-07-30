# \file
#
# \brief AUTOSAR Adc
#
# This file contains the implementation of the AUTOSAR
# module Adc.
#
# \author Elektrobit Automotive GmbH, 91058 Erlangen, Germany
#
# Copyright 2005 - 2019 Elektrobit Automotive GmbH
# All rights exclusively reserved for Elektrobit Automotive GmbH,
# unless expressly agreed to otherwise.

#################################################################
# REGISTRY

LIBRARIES_TO_BUILD     += Adc_src

Adc_src_FILES += $(Adc_CORE_PATH)\src\Adc.c
Adc_src_FILES += $(Adc_CORE_PATH)\src\Adc_Irq.c
Adc_src_FILES += $(wildcard $(Adc_OUTPUT_PATH)\src\Adc_PBcfg.c)

ifeq ($(TS_BUILD_POST_BUILD_BINARY),TRUE)
# If the post build binary shall be built do 
# not compile any files other then the postbuild files.
Adc_src_FILES :=
endif

.PHONY : complete_MCAL_origin Adc_MCAL_origin 

complete_MCAL_origin: Adc_MCAL_origin

Adc_MCAL_origin: remove_Eclipse_cache
	@${ECHO} * Preparing MCAL module Adc into vendor origin version
	@$(Adc_CORE_PATH)\perform_MCAL_change.bat origin

.PHONY : complete_MCAL_EB_update Adc_MCAL_EB_update

complete_MCAL_EB_update: Adc_MCAL_EB_update

Adc_MCAL_EB_update: remove_Eclipse_cache
	@${ECHO} * Preparing MCAL module Adc into EB updated version
	@$(Adc_CORE_PATH)\perform_MCAL_change.bat EB_update
