# \file
#
# \brief AUTOSAR FlsLoader
#
# This file contains the implementation of the AUTOSAR
# module FlsLoader.
#
# \author Elektrobit Automotive GmbH, 91058 Erlangen, Germany
#
# Copyright 2005 - 2019 Elektrobit Automotive GmbH
# All rights exclusively reserved for Elektrobit Automotive GmbH,
# unless expressly agreed to otherwise.

#################################################################
# DEFINITIONS

FlsLoader_CORE_PATH      ?= $(PLUGINS_BASE)\FlsLoader_$(FlsLoader_VARIANT)
FlsLoader_OUTPUT_PATH    ?= $(AUTOSAR_BASE_OUTPUT_PATH)

FlsLoader_GEN_FILES      += $(wildcard $(FlsLoader_OUTPUT_PATH)\include\FlsLoader_Cfg.h)
FlsLoader_GEN_FILES      += $(wildcard $(FlsLoader_OUTPUT_PATH)\src\FlsLoader_Cfg.c)

TRESOS_GEN_FILES   += $(FlsLoader_GEN_FILES)

CC_INCLUDE_PATH    += $(FlsLoader_CORE_PATH)\include \
                      $(FlsLoader_OUTPUT_PATH)\include

