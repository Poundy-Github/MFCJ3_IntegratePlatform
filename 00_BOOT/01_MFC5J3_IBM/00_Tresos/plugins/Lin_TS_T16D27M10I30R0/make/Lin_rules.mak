# \file
#
# \brief AUTOSAR Lin
#
# This file contains the implementation of the AUTOSAR
# module Lin.
#
# \author Elektrobit Automotive GmbH, 91058 Erlangen, Germany
#
# Copyright 2005 - 2019 Elektrobit Automotive GmbH
# All rights exclusively reserved for Elektrobit Automotive GmbH,
# unless expressly agreed to otherwise.

#################################################################
# REGISTRY

LIBRARIES_TO_BUILD     += Lin_src

Lin_src_FILES += $(Lin_CORE_PATH)\src\Lin_17_AscLin.c
Lin_src_FILES += $(Lin_CORE_PATH)\src\Lin_17_AscLin_Irq.c
Lin_src_FILES += $(wildcard $(Lin_OUTPUT_PATH)\src\Lin_17_AscLin_PBCfg.c)

ifeq ($(TS_BUILD_POST_BUILD_BINARY),TRUE)
# If the post build binary shall be built do 
# not compile any files other then the postbuild files.
Lin_src_FILES :=
endif

.PHONY : complete_MCAL_origin Lin_MCAL_origin 

complete_MCAL_origin: Lin_MCAL_origin

Lin_MCAL_origin: remove_Eclipse_cache
	@${ECHO} * Preparing MCAL module Lin into vendor origin version
	@$(Lin_CORE_PATH)\perform_MCAL_change.bat origin

.PHONY : complete_MCAL_EB_update Lin_MCAL_EB_update

complete_MCAL_EB_update: Lin_MCAL_EB_update

Lin_MCAL_EB_update: remove_Eclipse_cache
	@${ECHO} * Preparing MCAL module Lin into EB updated version
	@$(Lin_CORE_PATH)\perform_MCAL_change.bat EB_update
