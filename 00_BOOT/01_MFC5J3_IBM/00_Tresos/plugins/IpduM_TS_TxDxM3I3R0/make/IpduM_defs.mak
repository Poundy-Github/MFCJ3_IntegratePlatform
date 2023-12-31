# \file
#
# \brief AUTOSAR IpduM
#
# This file contains the implementation of the AUTOSAR
# module IpduM.
#
# \author Elektrobit Automotive GmbH, 91058 Erlangen, Germany
#
# Copyright 2005 - 2019 Elektrobit Automotive GmbH
# All rights exclusively reserved for Elektrobit Automotive GmbH,
# unless expressly agreed to otherwise.

#################################################################
# DEFINITIONS

IpduM_CORE_PATH    ?= $(PLUGINS_BASE)\IpduM_$(IpduM_VARIANT)

IpduM_OUTPUT_PATH  ?= $(AUTOSAR_BASE_OUTPUT_PATH)

#################################################################
# REGISTRY


IpduM_DEPENDENT_PLUGINS := base_make tresos
IpduM_VERSION           := 2.00.00
IpduM_DESCRIPTION       = IpduM Basic Software Makefile PlugIn for Autosar

CC_INCLUDE_PATH        += \
   $(IpduM_CORE_PATH)\include \
   $(IpduM_OUTPUT_PATH)\include
