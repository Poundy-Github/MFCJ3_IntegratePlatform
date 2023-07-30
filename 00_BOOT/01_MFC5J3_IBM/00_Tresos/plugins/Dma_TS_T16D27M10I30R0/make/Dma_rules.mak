# \file
#
# \brief AUTOSAR Dma
#
# This file contains the implementation of the AUTOSAR
# module Dma.
#
# \author Elektrobit Automotive GmbH, 91058 Erlangen, Germany
#
# Copyright 2005 - 2019 Elektrobit Automotive GmbH
# All rights exclusively reserved for Elektrobit Automotive GmbH,
# unless expressly agreed to otherwise.

#################################################################
# REGISTRY

LIBRARIES_TO_BUILD     += Dma_src

Dma_src_FILES += $(Dma_CORE_PATH)\src\Dma.c
Dma_src_FILES += $(Dma_CORE_PATH)\src\Dma_Irq.c
Dma_src_FILES += $(wildcard $(Dma_OUTPUT_PATH)\src\Dma_PBcfg.c)

ifeq ($(TS_BUILD_POST_BUILD_BINARY),TRUE)
# If the post build binary shall be built do 
# not compile any files other then the postbuild files.
Dma_src_FILES :=
endif

.PHONY : complete_MCAL_origin Dma_MCAL_origin 

complete_MCAL_origin: Dma_MCAL_origin

Dma_MCAL_origin: remove_Eclipse_cache
	@${ECHO} * Preparing MCAL module Dma into vendor origin version
	@$(Dma_CORE_PATH)\perform_MCAL_change.bat origin

.PHONY : complete_MCAL_EB_update Dma_MCAL_EB_update

complete_MCAL_EB_update: Dma_MCAL_EB_update

Dma_MCAL_EB_update: remove_Eclipse_cache
	@${ECHO} * Preparing MCAL module Dma into EB updated version
	@$(Dma_CORE_PATH)\perform_MCAL_change.bat EB_update
