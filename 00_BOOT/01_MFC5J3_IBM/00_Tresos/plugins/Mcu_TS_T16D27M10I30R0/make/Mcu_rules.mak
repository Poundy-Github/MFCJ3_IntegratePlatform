# \file
#
# \brief AUTOSAR Mcu
#
# This file contains the implementation of the AUTOSAR
# module Mcu.
#
# \author Elektrobit Automotive GmbH, 91058 Erlangen, Germany
#
# Copyright 2005 - 2019 Elektrobit Automotive GmbH
# All rights exclusively reserved for Elektrobit Automotive GmbH,
# unless expressly agreed to otherwise.

#################################################################
# REGISTRY

LIBRARIES_TO_BUILD     += Mcu_src

Mcu_src_FILES += $(Mcu_CORE_PATH)\src\Mcu.c
Mcu_src_FILES += $(Mcu_CORE_PATH)\src\Mcu_17_TimerIp.c
Mcu_src_FILES += $(Mcu_CORE_PATH)\src\Gtm_Irq.c
Mcu_src_FILES += $(wildcard $(Mcu_OUTPUT_PATH)\src\Mcu_17_TimerIp_Cfg.c)
Mcu_src_FILES += $(wildcard $(Mcu_OUTPUT_PATH)\src\Mcu_PBcfg.c)

ifeq ($(TS_BUILD_POST_BUILD_BINARY),TRUE)
# If the post build binary shall be built do 
# not compile any files other then the postbuild files.
Mcu_src_FILES :=
endif

.PHONY : complete_MCAL_origin Mcu_MCAL_origin 

complete_MCAL_origin: Mcu_MCAL_origin

Mcu_MCAL_origin: remove_Eclipse_cache
	@${ECHO} * Preparing MCAL module Mcu into vendor origin version
	@$(Mcu_CORE_PATH)\perform_MCAL_change.bat origin

.PHONY : complete_MCAL_EB_update Mcu_MCAL_EB_update

complete_MCAL_EB_update: Mcu_MCAL_EB_update

Mcu_MCAL_EB_update: remove_Eclipse_cache
	@${ECHO} * Preparing MCAL module Mcu into EB updated version
	@$(Mcu_CORE_PATH)\perform_MCAL_change.bat EB_update
