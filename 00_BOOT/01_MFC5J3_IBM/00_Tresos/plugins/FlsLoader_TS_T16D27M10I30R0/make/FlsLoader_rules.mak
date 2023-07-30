# \file
#
# \brief AUTOSAR FlsLoader
#
# This file contains the implementation of the AUTOSAR
# module FlsLoader.
#
# \author Elektrobit Automotive GmbH, 91058 Erlangen, Germany
#
# Copyright 2005 - 2019 Elektrobit Automotive GmbH
# All rights exclusively reserved for Elektrobit Automotive GmbH,
# unless expressly agreed to otherwise.

#################################################################
# REGISTRY

LIBRARIES_TO_BUILD     += FlsLoader_src

FlsLoader_src_FILES += $(FlsLoader_CORE_PATH)\src\FlsLoader.c
FlsLoader_src_FILES += $(FlsLoader_CORE_PATH)\src\FlsLoader_Platform.c
FlsLoader_src_FILES += $(wildcard $(FlsLoader_OUTPUT_PATH)\src\FlsLoader_Cfg.c)

ifeq ($(TS_BUILD_POST_BUILD_BINARY),TRUE)
# If the post build binary shall be built do 
# not compile any files other then the postbuild files.
FlsLoader_src_FILES :=
endif

.PHONY : complete_MCAL_origin FlsLoader_MCAL_origin 

complete_MCAL_origin: FlsLoader_MCAL_origin

FlsLoader_MCAL_origin: remove_Eclipse_cache
	@${ECHO} * Preparing MCAL module FlsLoader into vendor origin version
	@$(FlsLoader_CORE_PATH)\perform_MCAL_change.bat origin

.PHONY : complete_MCAL_EB_update FlsLoader_MCAL_EB_update

complete_MCAL_EB_update: FlsLoader_MCAL_EB_update

FlsLoader_MCAL_EB_update: remove_Eclipse_cache
	@${ECHO} * Preparing MCAL module FlsLoader into EB updated version
	@$(FlsLoader_CORE_PATH)\perform_MCAL_change.bat EB_update
