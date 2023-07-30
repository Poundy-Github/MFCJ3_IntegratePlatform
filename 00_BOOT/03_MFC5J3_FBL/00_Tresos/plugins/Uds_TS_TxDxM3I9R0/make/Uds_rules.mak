# \file
#
# \brief AUTOSAR Uds
#
# This file contains the implementation of the AUTOSAR
# module Uds.
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

Uds_src_FILES      := \
     $(Uds_CORE_PATH)\src\UDS_Prg.c \
     $(Uds_OUTPUT_PATH)\src\UDS_Cfg.c

LIBRARIES_TO_BUILD += Uds_src

#################################################################
# DEPENDENCIES (only for assembler files)
#

#################################################################
# RULES




