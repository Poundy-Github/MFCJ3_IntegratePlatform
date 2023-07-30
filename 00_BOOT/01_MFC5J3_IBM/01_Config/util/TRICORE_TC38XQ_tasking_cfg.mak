# \file
#
# \brief AUTOSAR Os
#
# This file contains the implementation of the AUTOSAR
# module Os.
#
# \author Elektrobit Automotive GmbH, 91058 Erlangen, Germany
#
# Copyright 1998 - 2018 Elektrobit Automotive GmbH
# All rights exclusively reserved for Elektrobit Automotive GmbH,
# unless expressly agreed to otherwise.

#################################################################
# Toolchain settings
#################################################################
# TOOLPATH_COMPILER:
# Path to the tasking compiler and linker.
# It is checked, if an environment variable
# $(SSC_TRICORE_277_TOOLPATH_COMPILER) exists.
# If so, this variable is taken for TOOLPATH_COMPILER
# If it doesn't exist, TOOLPATH_COMPILER must be set by user
# (modify command in line following the ifeq).
#
# For example:
TOOLPATH_COMPILER ?=


#################################################################
# TASKING_MODE:
#
# To compile a C source file the C compiler and the assembler must
# be called. This can be done by one call of the control program cctc
# or by a call of the compiler ctc and the assembler astc. The variable
# TASKING_MODE allows to select the kind of the tool chain call.
# Valid values are CONTROL_PROGRAM and COMPILER_ASSEMBLER.
TASKING_MODE = CONTROL_PROGRAM

#################################################################
# Define the options for the compiler.
#
CC_OPT += --core=tc1.6.2
CC_OPT += --iso=99
CC_OPT += -O2RG
CC_OPT += --align=4
CC_OPT += --misrac-version=2012
CC_OPT += --eabi=fHns
CC_OPT += --integer-enumeration
CC_OPT += --language=-comments,-gcc,+volatile,-strings
CC_OPT += --switch=auto

CC_OPT += -s
CC_OPT += --default-near-size=0
CC_OPT += --default-a0-size=0
CC_OPT += --default-a1-size=0
CC_OPT += --mitigation=tcvx-43260

CC_OPT += -g
CC_OPT += -DOS_TRICOREARCH=OS_TRICOREARCH_162
CC_OPT += -DCOMPILERCFG_EXTENSION_MCAL_FILE
CC_OPT += -DUSE_TASKING_INIT=0
CC_OPT += -DOS_TOOL=OS_tasking
CC_OPT += -DOS_ARCH=OS_TRICORE

ifeq ($(USE_LOG),true)
CC_OPT += -DLOG_EN
endif

ifeq ($(BOOT_RELEASE),true)
CC_OPT += -DRELEASE_VERSION
endif

#################################################################
# General path setup

# Path where the map file should get generated
MAP_FILE = $(BIN_OUTPUT_PATH)\$(PROJECT).map

# Path where the output file should get generated
OUT_FILE = $(BUILD_DIR)\$(PROJECT).out


#################################################################
# Define the default options for the assembler.
#
ASM_OPT += --core=tc1.6.2
ASM_OPT += -L1 
ASM_OPT += -gh 
ASM_OPT += --symbol-scope=l
ASM_OPT += -Ogs
ASM_OPT += --error-limit=42
ASM_OPT += --emit-locals=-equs,-symbols
ASM_OPT += --list-file


#################################################################
# Define the options for the linker
#

# Generate map file
LINK_OPT += -M$(MAP_FILE)
LINK_OPT += --hex-format=S
LINK_OPT += -vv
LINK_OPT += -OcLtxy
LINK_OPT += --user-provided-initialization-code
LINK_OPT += --first-library-first
LINK_OPT += --ignore-default-library-path


# Linker optimizations
# - C do not delete unreferenced sections
# - L do not use a ffd algorithm to locate unrestricted sections
# - t emit smart restrictions to decrease copy table size
# - x delete duplicate code sections
# - Y do not delete duplicate constant data sections (needed for Rte)
# LINK_OPT += -OtcxyL



# Linker archive options: insert-replace/create/update
AR_OPT += -rcu