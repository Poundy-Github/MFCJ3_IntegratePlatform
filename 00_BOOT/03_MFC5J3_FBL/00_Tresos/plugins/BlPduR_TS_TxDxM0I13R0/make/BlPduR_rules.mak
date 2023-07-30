# \file
#
# \brief AUTOSAR BlPduR
#
# This file contains the implementation of the AUTOSAR
# module BlPduR.
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

BlPduR_src_FILES      := \
     $(BlPduR_OUTPUT_PATH)\src\BlPduR_Cfg.c \
     $(BlPduR_CORE_PATH)\src\BlPduR_Prg.c \
     $(BlPduR_CORE_PATH)\src\BlPduR_Lin.c

LIBRARIES_TO_BUILD += BlPduR_src

#################################################################
# DEPENDENCIES (only for assembler files)
#

#################################################################
# RULES




