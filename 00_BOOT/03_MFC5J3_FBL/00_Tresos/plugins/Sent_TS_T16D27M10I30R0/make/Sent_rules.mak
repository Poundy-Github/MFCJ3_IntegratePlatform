# \file
#
# \brief AUTOSAR Sent
#
# This file contains the implementation of the AUTOSAR
# module Sent.
#
# \author Elektrobit Automotive GmbH, 91058 Erlangen, Germany
#
# Copyright 2005 - 2019 Elektrobit Automotive GmbH
# All rights exclusively reserved for Elektrobit Automotive GmbH,
# unless expressly agreed to otherwise.

#################################################################
# REGISTRY

LIBRARIES_TO_BUILD     += Sent_src

Sent_src_FILES += $(Sent_CORE_PATH)\src\Sent.c
Sent_src_FILES += $(wildcard $(Sent_OUTPUT_PATH)\src\Sent_PBcfg.c)

ifeq ($(TS_BUILD_POST_BUILD_BINARY),TRUE)
# If the post build binary shall be built do 
# not compile any files other then the postbuild files.
Sent_src_FILES :=
endif

.PHONY : complete_MCAL_origin Sent_MCAL_origin 

complete_MCAL_origin: Sent_MCAL_origin

Sent_MCAL_origin: remove_Eclipse_cache
	@${ECHO} * Preparing MCAL module Sent into vendor origin version
	@$(Sent_CORE_PATH)\perform_MCAL_change.bat origin

.PHONY : complete_MCAL_EB_update Sent_MCAL_EB_update

complete_MCAL_EB_update: Sent_MCAL_EB_update

Sent_MCAL_EB_update: remove_Eclipse_cache
	@${ECHO} * Preparing MCAL module Sent into EB updated version
	@$(Sent_CORE_PATH)\perform_MCAL_change.bat EB_update
