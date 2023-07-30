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
# DEFINITIONS

I2c_CORE_PATH      ?= $(PLUGINS_BASE)\I2c_$(I2c_VARIANT)
I2c_OUTPUT_PATH    ?= $(AUTOSAR_BASE_OUTPUT_PATH)

I2c_GEN_FILES      += $(wildcard $(I2c_OUTPUT_PATH)\include\I2c_Cfg.h)
I2c_GEN_FILES      += $(wildcard $(I2c_OUTPUT_PATH)\include\I2c_PBcfg.h)
I2c_GEN_FILES      += $(wildcard $(I2c_OUTPUT_PATH)\src\I2c_PBcfg.c)

TRESOS_GEN_FILES   += $(I2c_GEN_FILES)

CC_INCLUDE_PATH    += $(I2c_CORE_PATH)\include \
                      $(I2c_OUTPUT_PATH)\include

