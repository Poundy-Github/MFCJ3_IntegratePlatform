# \file
#
# \brief AUTOSAR BM
#
# This file contains the implementation of the AUTOSAR
# module BM.
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

BM_src_FILES      := \
     $(BM_CORE_PATH)\src\BM_Prg.c \
     $(BM_CORE_PATH)\src\BM_SecureBoot.c \
     $(BM_CORE_PATH)\src\BM_Security.c
     
     
ifneq ("$(wildcard $(BM_OUTPUT_PATH)/src/BM_Cfg.c)","")
    BM_src_FILES      += $(BM_OUTPUT_PATH)\src\BM_Cfg.c
endif
	 
LIBRARIES_TO_BUILD += BM_src

#################################################################
# DEPENDENCIES (only for assembler files)
#

#################################################################
# RULES




