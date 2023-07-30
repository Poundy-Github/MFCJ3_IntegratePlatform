# \file
#
# \brief AUTOSAR McalLib
#
# This file contains the implementation of the AUTOSAR
# module McalLib.
#
# \author Elektrobit Automotive GmbH, 91058 Erlangen, Germany
#
# Copyright 2005 - 2019 Elektrobit Automotive GmbH
# All rights exclusively reserved for Elektrobit Automotive GmbH,
# unless expressly agreed to otherwise.

#################################################################
# REGISTRY

LIBRARIES_TO_BUILD     += McalLib_src

McalLib_src_FILES += $(McalLib_CORE_PATH)\src\McalLib.c

ifeq ($(TS_BUILD_POST_BUILD_BINARY),TRUE)
# If the post build binary shall be built do 
# not compile any files other then the postbuild files.
McalLib_src_FILES :=
endif

.PHONY : complete_MCAL_origin McalLib_MCAL_origin 

complete_MCAL_origin: McalLib_MCAL_origin

McalLib_MCAL_origin: remove_Eclipse_cache
	@${ECHO} * Preparing MCAL module McalLib into vendor origin version
	@$(McalLib_CORE_PATH)\perform_MCAL_change.bat origin

.PHONY : complete_MCAL_EB_update McalLib_MCAL_EB_update

complete_MCAL_EB_update: McalLib_MCAL_EB_update

McalLib_MCAL_EB_update: remove_Eclipse_cache
	@${ECHO} * Preparing MCAL module McalLib into EB updated version
	@$(McalLib_CORE_PATH)\perform_MCAL_change.bat EB_update
