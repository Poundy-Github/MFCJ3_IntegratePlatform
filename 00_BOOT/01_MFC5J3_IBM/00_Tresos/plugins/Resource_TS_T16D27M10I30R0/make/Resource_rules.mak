# \file
#
# \brief AUTOSAR Resource
#
# This file contains the implementation of the AUTOSAR
# module Resource.
#
# \author Elektrobit Automotive GmbH, 91058 Erlangen, Germany
#
# Copyright 2005 - 2019 Elektrobit Automotive GmbH
# All rights exclusively reserved for Elektrobit Automotive GmbH,
# unless expressly agreed to otherwise.

#################################################################
# REGISTRY

LIBRARIES_TO_BUILD     += Resource_src

Resource_src_FILES += $(Resource_CORE_PATH)\src\Mcal_SafetyError.c


ifeq ($(TS_BUILD_POST_BUILD_BINARY),TRUE)
# If the post build binary shall be built do 
# not compile any files other then the postbuild files.
Resource_src_FILES :=
endif

.PHONY : complete_MCAL_origin Resource_MCAL_origin 

complete_MCAL_origin: Resource_MCAL_origin

Resource_MCAL_origin: remove_Eclipse_cache
	@${ECHO} * Preparing MCAL module Resource into vendor origin version
	@$(Resource_CORE_PATH)\perform_MCAL_change.bat origin

.PHONY : complete_MCAL_EB_update Resource_MCAL_EB_update

complete_MCAL_EB_update: Resource_MCAL_EB_update

Resource_MCAL_EB_update: remove_Eclipse_cache
	@${ECHO} * Preparing MCAL module Resource into EB updated version
	@$(Resource_CORE_PATH)\perform_MCAL_change.bat EB_update
