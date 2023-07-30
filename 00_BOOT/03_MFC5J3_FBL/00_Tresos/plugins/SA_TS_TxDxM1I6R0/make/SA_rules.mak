# \file
#
# \brief AUTOSAR SA
#
# This file contains the implementation of the AUTOSAR
# module SA.
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

SA_src_FILES      := \
     $(SA_CORE_PATH)\src\SA_Prg.c \
     $(SA_CORE_PATH)\src\SA_Decomp.c \
     $(SA_OUTPUT_PATH)\src\SA_Cfg.c
	 
LIBRARIES_TO_BUILD += SA_src

#################################################################
# DEPENDENCIES (only for assembler files)
#

#################################################################
# RULES




