# \file
#
# \brief AUTOSAR I2c
#
# This file contains the implementation of the AUTOSAR
# module I2c.
#
# \author Elektrobit Automotive GmbH, 91058 Erlangen, Germany
#
# Copyright 2005 - 2019 Elektrobit Automotive GmbH
# All rights exclusively reserved for Elektrobit Automotive GmbH,
# unless expressly agreed to otherwise.

#################################################################
# REGISTRY

LIBRARIES_TO_BUILD     += I2c_src

I2c_src_FILES += $(I2c_CORE_PATH)\src\I2c.c
I2c_src_FILES += $(wildcard $(I2c_OUTPUT_PATH)\src\I2c_PBcfg.c)

ifeq ($(TS_BUILD_POST_BUILD_BINARY),TRUE)
# If the post build binary shall be built do 
# not compile any files other then the postbuild files.
I2c_src_FILES :=
endif

.PHONY : complete_MCAL_origin I2c_MCAL_origin 

complete_MCAL_origin: I2c_MCAL_origin

I2c_MCAL_origin: remove_Eclipse_cache
	@${ECHO} * Preparing MCAL module I2c into vendor origin version
	@$(I2c_CORE_PATH)\perform_MCAL_change.bat origin

.PHONY : complete_MCAL_EB_update I2c_MCAL_EB_update

complete_MCAL_EB_update: I2c_MCAL_EB_update

I2c_MCAL_EB_update: remove_Eclipse_cache
	@${ECHO} * Preparing MCAL module I2c into EB updated version
	@$(I2c_CORE_PATH)\perform_MCAL_change.bat EB_update
