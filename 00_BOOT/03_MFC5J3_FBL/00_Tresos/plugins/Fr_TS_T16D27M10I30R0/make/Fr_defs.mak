# \file
#
# \brief AUTOSAR Fr
#
# This file contains the implementation of the AUTOSAR
# module Fr.
#
# \author Elektrobit Automotive GmbH, 91058 Erlangen, Germany
#
# Copyright 2005 - 2019 Elektrobit Automotive GmbH
# All rights exclusively reserved for Elektrobit Automotive GmbH,
# unless expressly agreed to otherwise.

#################################################################
# DEFINITIONS

Fr_CORE_PATH      ?= $(PLUGINS_BASE)\Fr_$(Fr_VARIANT)
Fr_OUTPUT_PATH    ?= $(AUTOSAR_BASE_OUTPUT_PATH)

Fr_GEN_FILES      += $(wildcard $(Fr_OUTPUT_PATH)\include\Fr_17_Eray_Cfg.h)
Fr_GEN_FILES      += $(wildcard $(Fr_OUTPUT_PATH)\include\Fr_17_Eray_PBcfg.h)
Fr_GEN_FILES      += $(wildcard $(Fr_OUTPUT_PATH)\src\Fr_17_Eray_PBcfg.c)

TRESOS_GEN_FILES   += $(Fr_GEN_FILES)

CC_INCLUDE_PATH    += $(Fr_CORE_PATH)\include \
                      $(Fr_OUTPUT_PATH)\include

