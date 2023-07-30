# \file
#
# \brief Autosar Flash
#
# This file contains the implementation of the Autosar
# module Flash.
#
# \author Elektrobit Automotive GmbH, 91058 Erlangen, Germany
#
# Copyright 2005 - 2010 Elektrobit Automotive GmbH
# All rights exclusively reserved for Elektrobit Automotive GmbH,
# unless expressly agreed to otherwise.

#################################################################
# DEFINITIONS

Flash_CORE_PATH         := $(SSC_ROOT)\Flash_$(Flash_VARIANT)

Flash_OUTPUT_PATH       := $(AUTOSAR_BASE_OUTPUT_PATH)

#################################################################
# REGISTRY
SSC_PLUGINS           += Flash
Flash_DEPENDENT_PLUGINS := base_make tresos
Flash_VERSION           := 2.00.00
Flash_DESCRIPTION       := Flash Basic Software Makefile PlugIn for Autosar
CC_INCLUDE_PATH       +=    \
   $(Flash_CORE_PATH)\include \
   $(Flash_OUTPUT_PATH)\include

# TC1782 library
ifeq ($(DERIVATE), TC38XQ)
CC_INCLUDE_PATH += $(PROJECT_ROOT)\source\boards\TriboardTC38XQ
endif