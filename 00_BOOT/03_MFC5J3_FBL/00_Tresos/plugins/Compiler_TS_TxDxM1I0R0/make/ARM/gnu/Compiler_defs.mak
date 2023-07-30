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

ASM_FILTER_LIST = %.asm %.S

ABS_FILE_SUFFIX=elf
#define ASM_FILE_SUFFIX as workaround for Os (ASCOS-5483)
ASM_FILE_SUFFIX=asm
HEX_FILE_SUFFIX=mot

PROJECT_BINARY  = $(BIN_OUTPUT_PATH)/$(PROJECT).$(ABS_FILE_SUFFIX)
MAPFILE         = $(BIN_OUTPUT_PATH)/$(PROJECT).map
HEXFILE         = $(BIN_OUTPUT_PATH)/$(PROJECT).$(HEX_FILE_SUFFIX)


# ------ general files (used in common rules)
COMPILER_DIR    = $(TOOLPATH_COMPILER)/bin
CC              = $(COMPILER_DIR)/arm-none-eabi-gcc.exe
CCLIB           = $(COMPILER_DIR)/arm-none-eabi-gcc-ar.exe
ASM             = $(CC)
LINK            = $(COMPILER_DIR)/arm-none-eabi-gcc.exe
GCC             = $(PLUGINS_BASE)/Make_$(Make_VARIANT)/tools/gcc/bin/cpp.exe


# ------ compiler specific files (and the corresponding checks)
CPP              = $(COMPILER_DIR)/arm-none-eabi-cpp.exe

