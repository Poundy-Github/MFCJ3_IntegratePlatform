# \file
#
# \brief AUTOSAR Spi
#
# This file contains the implementation of the AUTOSAR
# module Spi.
#
# \author Elektrobit Automotive GmbH, 91058 Erlangen, Germany
#
# Copyright 2005 - 2019 Elektrobit Automotive GmbH
# All rights exclusively reserved for Elektrobit Automotive GmbH,
# unless expressly agreed to otherwise.

#################################################################
# REGISTRY

LIBRARIES_TO_BUILD     += Spi_src

Spi_src_FILES += $(Spi_CORE_PATH)\src\Spi.c
Spi_src_FILES += $(wildcard $(Spi_OUTPUT_PATH)\src\Spi_PBcfg.c)

ifeq ($(TS_BUILD_POST_BUILD_BINARY),TRUE)
# If the post build binary shall be built do 
# not compile any files other then the postbuild files.
Spi_src_FILES :=
endif

.PHONY : complete_MCAL_origin Spi_MCAL_origin 

complete_MCAL_origin: Spi_MCAL_origin

Spi_MCAL_origin: remove_Eclipse_cache
	@${ECHO} * Preparing MCAL module Spi into vendor origin version
	@$(Spi_CORE_PATH)\perform_MCAL_change.bat origin

.PHONY : complete_MCAL_EB_update Spi_MCAL_EB_update

complete_MCAL_EB_update: Spi_MCAL_EB_update

Spi_MCAL_EB_update: remove_Eclipse_cache
	@${ECHO} * Preparing MCAL module Spi into EB updated version
	@$(Spi_CORE_PATH)\perform_MCAL_change.bat EB_update
