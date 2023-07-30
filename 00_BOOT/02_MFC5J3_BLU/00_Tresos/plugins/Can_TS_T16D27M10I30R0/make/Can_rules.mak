# \file
#
# \brief AUTOSAR Can
#
# This file contains the implementation of the AUTOSAR
# module Can.
#
# \author Elektrobit Automotive GmbH, 91058 Erlangen, Germany
#
# Copyright 2005 - 2019 Elektrobit Automotive GmbH
# All rights exclusively reserved for Elektrobit Automotive GmbH,
# unless expressly agreed to otherwise.

#################################################################
# REGISTRY

LIBRARIES_TO_BUILD     += Can_src

Can_src_FILES += $(Can_CORE_PATH)\src\Can_17_McmCan.c
Can_src_FILES += $(Can_CORE_PATH)\src\Can_17_McmCan_Irq.c
Can_src_FILES += $(wildcard $(Can_OUTPUT_PATH)\src\Can_17_McmCan_PBcfg.c)

ifeq ($(TS_BUILD_POST_BUILD_BINARY),TRUE)
# If the post build binary shall be built do 
# not compile any files other then the postbuild files.
Can_src_FILES :=
endif

.PHONY : complete_MCAL_origin Can_MCAL_origin 

complete_MCAL_origin: Can_MCAL_origin

Can_MCAL_origin: remove_Eclipse_cache
	@${ECHO} * Preparing MCAL module Can into vendor origin version
	@$(Can_CORE_PATH)\perform_MCAL_change.bat origin

.PHONY : complete_MCAL_EB_update Can_MCAL_EB_update

complete_MCAL_EB_update: Can_MCAL_EB_update

Can_MCAL_EB_update: remove_Eclipse_cache
	@${ECHO} * Preparing MCAL module Can into EB updated version
	@$(Can_CORE_PATH)\perform_MCAL_change.bat EB_update
