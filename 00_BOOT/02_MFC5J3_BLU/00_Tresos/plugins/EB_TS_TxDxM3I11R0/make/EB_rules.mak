# \file
#
# \brief AUTOSAR EB
#
# This file contains the implementation of the AUTOSAR
# module EB.
#
# \author Elektrobit Automotive GmbH, 91058 Erlangen, Germany
#
# Copyright 2005 - 2019 Elektrobit Automotive GmbH
# All rights exclusively reserved for Elektrobit Automotive GmbH,
# unless expressly agreed to otherwise.

#################################################################
# DEFINITIONS

#################################################################
# REGISTRY

EB_src_FILES      := \
     $(EB_OUTPUT_PATH)\src\EB_Cfg.c \
     $(EB_OUTPUT_PATH)\src\EB_Prg.c
    
ifneq ("$(wildcard $(EB_OUTPUT_PATH)/src/EB_Boot_PduR.c)","")
    EB_src_FILES      += $(EB_OUTPUT_PATH)\src\EB_Boot_PduR.c
endif

ifneq ("$(wildcard $(EB_OUTPUT_PATH)/src/EB_FullDuplex.c)","")
    EB_src_FILES      += $(EB_OUTPUT_PATH)\src\EB_FullDuplex.c
endif
     
LIBRARIES_TO_BUILD += EB_src

#################################################################
# DEPENDENCIES (only for assembler files)
#

#################################################################
# RULES




