# \file
#
# \brief AUTOSAR ProgOEMInd
#
# This file contains the implementation of the AUTOSAR
# module ProgOEMInd.
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

ProgOEMInd_src_FILES      := \
    $(ProgOEMInd_CORE_PATH)\src\PROG_Hsm.c \
    $(ProgOEMInd_CORE_PATH)\src\PROG_HsmPROGData.c \
    $(ProgOEMInd_CORE_PATH)\src\PROG_HsmPROGFnct.c \
    $(ProgOEMInd_CORE_PATH)\src\PROG_DoubleGuard.c

LIBRARIES_TO_BUILD += ProgOEMInd_src

#################################################################
# DEPENDENCIES (only for assembler files)
#

#################################################################
# RULES
