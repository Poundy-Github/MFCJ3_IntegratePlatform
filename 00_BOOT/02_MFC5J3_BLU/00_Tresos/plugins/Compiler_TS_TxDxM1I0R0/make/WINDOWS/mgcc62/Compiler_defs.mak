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

PROJECT_BINARY  = $(BIN_OUTPUT_PATH)/$(PROJECT).exe
FIRST_BUILD_TARGET := $(PROJECT_BINARY)
MAPFILE         = $(BIN_OUTPUT_PATH)/$(PROJECT).map

#######
# needs to removed if compiler is not in Platforms anymore
# from here ...
TOOLPATH_COMPILER_INTERN := $(PLUGINS_BASE)/Platforms_$(Platforms_VARIANT)/tools/mingw-gcc-6.2.0/bin
COMPILER_SFXARCHIVE      := $(PLUGINS_BASE)/Platforms_$(Platforms_VARIANT)/tools/mingw-gcc-6.2.0/MinGw.exe

# check is necessary, TOOLPATH_COMPILER is always set on CC, for WINDOWS it is set empty
ifeq ($(strip $(TOOLPATH_COMPILER)),)
# TOOLPATH_COMPILER is set on CC ?= does not work, workaround :=
TOOLPATH_COMPILER        := $(TOOLPATH_COMPILER_INTERN)
endif
# till here
#######

CC              = $(TOOLPATH_COMPILER)/gcc.exe
GPP             = $(TOOLPATH_COMPILER)/g++.exe
CCLIB           = $(TOOLPATH_COMPILER)/ar.exe
LINK            = $(TOOLPATH_COMPILER)/gcc.exe
ASM             = $(TOOLPATH_COMPILER)/gcc.exe
OBJCOPY         = $(TOOLPATH_COMPILER)/objcopy.exe
GCC             = $(MAKE_ROOT)/tools/gcc/bin/cpp.exe

LIB_FILE_SUFFIX = lib

COMPILER_DIR    = $(TOOLPATH_COMPILER)
DEBUGGER        = $(TOOLPATH_COMPILER)/gdb.exe

#######
# needs to removed if compiler is not in Platforms anymore
# from here ...
# check if internal compiler is used
ifeq ($(TOOLPATH_COMPILER),$(TOOLPATH_COMPILER_INTERN))
  EXTRACT_COMPILER := $(TOOLPATH_COMPILER)/gcc.exe
  ifeq (,$(findstring $(subst \,/,$(EXTRACT_COMPILER)),$(wildcard $(subst \,/,$(EXTRACT_COMPILER)) )))
    # compiler not found: unzip it
    OUTPUT_SHELL:= $(shell $(COMPILER_SFXARCHIVE) -y)
  endif
endif
# till here
#######

ifeq (,$(findstring $(subst \,/,$(GCC)),$(wildcard $(subst \,/,$(GCC)) )))
  $(error FILE DOES NOT EXIST GCC $(GCC))
endif
ifeq (,$(findstring $(subst \,/,$(CPP)),$(wildcard $(subst \,/,$(CPP)) )))
  $(error FILE DOES NOT EXIST CPP $(CPP))
endif

#######
# needs to removed if compiler is not in Platforms anymore
# from here ...

# ensure the compiler directory is in the path!
OUTPUT_SHELL_GCC:= $(shell $(WHICH) libgomp-1.dll)

ifeq ($(findstring not found,$(OUTPUT_SHELL_GCC)),not found)
  NEW_PATH:=$(TOOLPATH_COMPILER);$(PATH)
  export PATH=$(NEW_PATH)
endif

