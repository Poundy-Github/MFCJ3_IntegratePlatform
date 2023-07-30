# \file
#
# \brief AUTOSAR Lin
#
# This file contains the implementation of the AUTOSAR
# module Lin.
#
# \author Elektrobit Automotive GmbH, 91058 Erlangen, Germany
#
# Copyright 2005 - 2019 Elektrobit Automotive GmbH
# All rights exclusively reserved for Elektrobit Automotive GmbH,
# unless expressly agreed to otherwise.

#################################################################
# DEFINITIONS

Lin_CORE_PATH      ?= $(PLUGINS_BASE)\Lin_$(Lin_VARIANT)
Lin_OUTPUT_PATH    ?= $(AUTOSAR_BASE_OUTPUT_PATH)

Lin_GEN_FILES      += $(wildcard $(Lin_OUTPUT_PATH)\include\Lin_17_AscLin_Cfg.h)
Lin_GEN_FILES      += $(wildcard $(Lin_OUTPUT_PATH)\include\Lin_17_AscLin_PBcfg.h)
Lin_GEN_FILES      += $(wildcard $(Lin_OUTPUT_PATH)\src\Lin_17_AscLin_PBcfg.c)

TRESOS_GEN_FILES   += $(Lin_GEN_FILES)

CC_INCLUDE_PATH    += $(Lin_CORE_PATH)\include \
                      $(Lin_OUTPUT_PATH)\include

