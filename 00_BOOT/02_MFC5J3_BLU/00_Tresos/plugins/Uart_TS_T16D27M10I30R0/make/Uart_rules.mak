# \file
#
# \brief AUTOSAR Uart
#
# This file contains the implementation of the AUTOSAR
# module Uart.
#
# \author Elektrobit Automotive GmbH, 91058 Erlangen, Germany
#
# Copyright 2005 - 2019 Elektrobit Automotive GmbH
# All rights exclusively reserved for Elektrobit Automotive GmbH,
# unless expressly agreed to otherwise.

#################################################################
# REGISTRY

LIBRARIES_TO_BUILD     += Uart_src

Uart_src_FILES += $(Uart_CORE_PATH)\src\Uart.c
Uart_src_FILES += $(wildcard $(Uart_OUTPUT_PATH)\src\Uart_PBcfg.c)

ifeq ($(TS_BUILD_POST_BUILD_BINARY),TRUE)
# If the post build binary shall be built do 
# not compile any files other then the postbuild files.
Uart_src_FILES :=
endif

.PHONY : complete_MCAL_origin Uart_MCAL_origin 

complete_MCAL_origin: Uart_MCAL_origin

Uart_MCAL_origin: remove_Eclipse_cache
	@${ECHO} * Preparing MCAL module Uart into vendor origin version
	@$(Uart_CORE_PATH)\perform_MCAL_change.bat origin

.PHONY : complete_MCAL_EB_update Uart_MCAL_EB_update

complete_MCAL_EB_update: Uart_MCAL_EB_update

Uart_MCAL_EB_update: remove_Eclipse_cache
	@${ECHO} * Preparing MCAL module Uart into EB updated version
	@$(Uart_CORE_PATH)\perform_MCAL_change.bat EB_update
