# \file
#
# \brief AUTOSAR Compiler
#
# This file contains the implementation of the AUTOSAR
# module Compiler.
#
# \author Elektrobit Automotive GmbH, 91058 Erlangen, Germany
#
# Copyright 2017 - 2019 Elektrobit Automotive GmbH
# All rights exclusively reserved for Elektrobit Automotive GmbH,
# unless expressly agreed to otherwise.

ASM_FILTER_LIST := %.asm %.s
ABS_FILE_SUFFIX   =elf
MAP_FILE_SUFFIX   =map
HEX_FILE_SUFFIX   =mot
LIB_FILE_SUFFIX =lib

PROJECT_BINARY  = $(BIN_OUTPUT_PATH)\$(PROJECT).$(ABS_FILE_SUFFIX)
MAPFILE         = $(BIN_OUTPUT_PATH)\$(PROJECT).$(MAP_FILE_SUFFIX)
HEXFILE         = $(BIN_OUTPUT_PATH)\$(PROJECT).$(HEX_FILE_SUFFIX)

# override globale make default suffixes
ASM_FILE_SUFFIX   =asm

# ------ general files (used in common rules)
COMPILER_DIR    = $(TOOLPATH_COMPILER)
CC              = $(COMPILER_DIR)/armclang.exe
CCLIB           = $(COMPILER_DIR)/armar.exe
ASM             = $(COMPILER_DIR)/armclang.exe
ASM_2            = $(COMPILER_DIR)/armasm.exe
LINK            = $(COMPILER_DIR)/armlink.exe
GCC             = $(PLUGINS_BASE)/Make_$(Make_VARIANT)/tools/gcc/bin/cpp.exe
