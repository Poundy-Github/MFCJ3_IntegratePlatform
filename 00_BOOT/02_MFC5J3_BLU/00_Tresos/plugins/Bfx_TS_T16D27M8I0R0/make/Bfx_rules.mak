# \file
#
# \brief AUTOSAR Bfx
#
# This file contains the implementation of the AUTOSAR
# module Bfx.
#
# \author Elektrobit Automotive GmbH, 91058 Erlangen, Germany
#
# Copyright 2005 - 2019 Elektrobit Automotive GmbH
# All rights exclusively reserved for Elektrobit Automotive GmbH,
# unless expressly agreed to otherwise.

#################################################################
# REGISTRY

LIBRARIES_TO_BUILD     += Bfx_src

Bfx_src_FILES += $(Bfx_CORE_PATH)\src\Bfx.c

ifeq ($(TS_BUILD_POST_BUILD_BINARY),TRUE)
# If the post build binary shall be built do 
# not compile any files other then the postbuild files.
Bfx_src_FILES :=
endif

.PHONY : complete_MCAL_origin Bfx_MCAL_origin 

complete_MCAL_origin: Bfx_MCAL_origin

Bfx_MCAL_origin: remove_Eclipse_cache
	@${ECHO} * Preparing MCAL module Bfx into vendor origin version
	@$(Bfx_CORE_PATH)\perform_MCAL_change.bat origin

.PHONY : complete_MCAL_EB_update Bfx_MCAL_EB_update

complete_MCAL_EB_update: Bfx_MCAL_EB_update

Bfx_MCAL_EB_update: remove_Eclipse_cache
	@${ECHO} * Preparing MCAL module Bfx into EB updated version
	@$(Bfx_CORE_PATH)\perform_MCAL_change.bat EB_update
