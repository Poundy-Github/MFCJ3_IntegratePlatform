# \file
#
# \brief AUTOSAR McalLib
#
# This file contains the implementation of the AUTOSAR
# module McalLib.
#
# \author Elektrobit Automotive GmbH, 91058 Erlangen, Germany
#
# Copyright 2005 - 2019 Elektrobit Automotive GmbH
# All rights exclusively reserved for Elektrobit Automotive GmbH,
# unless expressly agreed to otherwise.

#################################################################
# DEFINITIONS

McalLib_CORE_PATH      ?= $(PLUGINS_BASE)\McalLib_$(McalLib_VARIANT)
McalLib_OUTPUT_PATH    ?= $(AUTOSAR_BASE_OUTPUT_PATH)

McalLib_GEN_FILES      += $(wildcard $(McalLib_OUTPUT_PATH)\include\McalLib_Cfg.h)

TRESOS_GEN_FILES   += $(McalLib_GEN_FILES)

CC_INCLUDE_PATH    += $(McalLib_CORE_PATH)\include \
                      $(McalLib_OUTPUT_PATH)\include

