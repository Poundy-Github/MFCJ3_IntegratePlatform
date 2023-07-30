# \file
#
# \brief AUTOSAR Dio
#
# This file contains the implementation of the AUTOSAR
# module Dio.
#
# \author Elektrobit Automotive GmbH, 91058 Erlangen, Germany
#
# Copyright 2005 - 2019 Elektrobit Automotive GmbH
# All rights exclusively reserved for Elektrobit Automotive GmbH,
# unless expressly agreed to otherwise.

#################################################################
# REGISTRY

LIBRARIES_TO_BUILD     += Dio_src

Dio_src_FILES += $(Dio_CORE_PATH)\src\Dio.c
Dio_src_FILES += $(wildcard $(Dio_OUTPUT_PATH)\src\Dio_Lcfg.c)

ifeq ($(TS_BUILD_POST_BUILD_BINARY),TRUE)
# If the post build binary shall be built do 
# not compile any files other then the postbuild files.
Dio_src_FILES :=
endif

.PHONY : complete_MCAL_origin Dio_MCAL_origin 

complete_MCAL_origin: Dio_MCAL_origin

Dio_MCAL_origin: remove_Eclipse_cache
	@${ECHO} * Preparing MCAL module Dio into vendor origin version
	@$(Dio_CORE_PATH)\perform_MCAL_change.bat origin

.PHONY : complete_MCAL_EB_update Dio_MCAL_EB_update

complete_MCAL_EB_update: Dio_MCAL_EB_update

Dio_MCAL_EB_update: remove_Eclipse_cache
	@${ECHO} * Preparing MCAL module Dio into EB updated version
	@$(Dio_CORE_PATH)\perform_MCAL_change.bat EB_update
