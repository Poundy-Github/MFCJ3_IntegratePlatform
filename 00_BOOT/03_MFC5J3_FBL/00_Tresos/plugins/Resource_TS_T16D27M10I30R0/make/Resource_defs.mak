# \file
#
# \brief AUTOSAR Resource
#
# This file contains the implementation of the AUTOSAR
# module Resource.
#
# \author Elektrobit Automotive GmbH, 91058 Erlangen, Germany
#
# Copyright 2005 - 2019 Elektrobit Automotive GmbH
# All rights exclusively reserved for Elektrobit Automotive GmbH,
# unless expressly agreed to otherwise.

#################################################################
# DEFINITIONS

Resource_CORE_PATH      := $(PLUGINS_BASE)\Resource_$(Resource_VARIANT)
Resource_OUTPUT_PATH    := $(AUTOSAR_BASE_OUTPUT_PATH)


TRESOS_GEN_FILES   += $(Resource_GEN_FILES)

ifeq ($(DERIVATE),TC35XT)
CC_INCLUDE_PATH    += $(Resource_CORE_PATH)\include \
                      $(Resource_CORE_PATH)\include\TC35xA \
                      $(Resource_OUTPUT_PATH)\include
endif
ifeq ($(DERIVATE),$(filter $(DERIVATE), TC38XQ TC38XT))
CC_INCLUDE_PATH    += $(Resource_CORE_PATH)\include \
                      $(Resource_CORE_PATH)\include\TC38xA \
                      $(Resource_OUTPUT_PATH)\include
endif
ifeq ($(DERIVATE),TC39XX)
CC_INCLUDE_PATH    += $(Resource_CORE_PATH)\include \
                      $(Resource_CORE_PATH)\include\TC39xB \
                      $(Resource_OUTPUT_PATH)\include
endif				  
					  
