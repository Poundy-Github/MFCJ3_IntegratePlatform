# \file
#
# \brief AUTOSAR Fr
#
# This file contains the implementation of the AUTOSAR
# module Fr.
#
# \author Elektrobit Automotive GmbH, 91058 Erlangen, Germany
#
# Copyright 2005 - 2019 Elektrobit Automotive GmbH
# All rights exclusively reserved for Elektrobit Automotive GmbH,
# unless expressly agreed to otherwise.

#################################################################
# REGISTRY

LIBRARIES_TO_BUILD     += Fr_src

Fr_src_FILES += $(Fr_CORE_PATH)\src\Fr_17_Eray.c
Fr_src_FILES += $(wildcard $(Fr_OUTPUT_PATH)\src\Fr_17_Eray_PBcfg.c)

ifeq ($(TS_BUILD_POST_BUILD_BINARY),TRUE)
# If the post build binary shall be built do 
# not compile any files other then the postbuild files.
Fr_src_FILES :=
endif

.PHONY : complete_MCAL_origin Fr_MCAL_origin 

complete_MCAL_origin: Fr_MCAL_origin

Fr_MCAL_origin: remove_Eclipse_cache
	@${ECHO} * Preparing MCAL module Fr into vendor origin version
	@$(Fr_CORE_PATH)\perform_MCAL_change.bat origin

.PHONY : complete_MCAL_EB_update Fr_MCAL_EB_update

complete_MCAL_EB_update: Fr_MCAL_EB_update

Fr_MCAL_EB_update: remove_Eclipse_cache
	@${ECHO} * Preparing MCAL module Fr into EB updated version
	@$(Fr_CORE_PATH)\perform_MCAL_change.bat EB_update
