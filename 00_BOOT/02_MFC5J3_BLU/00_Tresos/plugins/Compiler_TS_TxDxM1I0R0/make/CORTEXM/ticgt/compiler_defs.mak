# \file
#
# \brief AUTOSAR Platforms
#
# This file contains the implementation of the AUTOSAR
# module Platforms.
#
# \author Elektrobit Automotive GmbH, 91058 Erlangen, Germany
#
# Copyright 2005 - 2017 Elektrobit Automotive GmbH
# All rights exclusively reserved for Elektrobit Automotive GmbH,
# unless expressly agreed to otherwise.

# override globale make default suffixes
OBJ_FILE_SUFFIX   =obj
OBJ_FILE_SUFFIX_2 =
LIB_FILE_SUFFIX   =lib
ASM_FILE_SUFFIX   =s
ASM_FILE_SUFFIX_2 =arm_asm
CC_FILE_SUFFIX    =c
CC_FILE_SUFFIX_2  =
CPP_FILE_SUFFIX   =cpp
CPP_FILE_SUFFIX_2 =
H_FILE_SUFFIX     =h
H_FILE_SUFFIX_2   =
PRE_FILE_SUFFIX   =pp
ABS_FILE_SUFFIX   =elf
MAP_FILE_SUFFIX   =map
INC_FILE_SUFFIX   =inc
INA_FILE_SUFFIX   =ina
INL_FILE_SUFFIX   =inl
HEX_FILE_SUFFIX   =hex
PROJECT_BINARY  = $(BIN_OUTPUT_PATH)\$(PROJECT).elf
MAPFILE         = $(BIN_OUTPUT_PATH)\$(PROJECT).map

# ------ general files (used in common rules)
COMPILER_DIR    = $(TOOLPATH_COMPILER)\bin
CC              = $(COMPILER_DIR)\armcl.exe
CCLIB           = $(COMPILER_DIR)\armar.exe
ASM             = $(COMPILER_DIR)\armcl.exe
LINK            = $(COMPILER_DIR)\armcl.exe
GCC             = $(SSC_ROOT)/Make_$(Make_VARIANT)/tools/gcc/bin/cpp.exe

# ------ compiler specific files (and the corresponding checks)

# ------ define compiler specific include paths
CC_INCLUDE_PATH      +=  $(TOOLPATH_COMPILER)\include

CPP_INCLUDE_PATH     +=  $(TOOLPATH_COMPILER)\include

ASM_INCLUDE_PATH     +=  $(TOOLPATH_COMPILER)\include
