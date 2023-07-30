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

ABS_FILE_SUFFIX=elf
ASM_FILE_SUFFIX=s
HEX_FILE_SUFFIX=mot

PROJECT_BINARY  = $(BIN_OUTPUT_PATH)\$(PROJECT).$(ABS_FILE_SUFFIX)
MAPFILE         = $(BIN_OUTPUT_PATH)\$(PROJECT).map
HEXFILE         = $(BIN_OUTPUT_PATH)\$(PROJECT).$(HEX_FILE_SUFFIX)


# ------ general files (used in common rules)
COMPILER_DIR    = $(TOOLPATH_COMPILER)/bin
CC              = $(COMPILER_DIR)/cctc.exe
CCLIB           = $(COMPILER_DIR)/artc.exe
ASM             = $(COMPILER_DIR)/astc.exe
LINK            = $(COMPILER_DIR)/ltc.exe
ifeq (,$(findstring $(subst \,/,$(CPP_DEPS)),$(wildcard $(subst \,/,$(CPP_DEPS)) )))
GCC             = $(PLUGINS_BASE)/Make_$(Make_VARIANT)/tools/gcc/bin/cpp.exe
else
GCC             = $(PERL_EXE) $(CPP_DEPS)
endif

# ------ compiler specific files (and the corresponding checks)
CPP             = $(COMPILER_DIR)/cptc.exe
CTC             = $(COMPILER_DIR)/ctc.exe
ifeq ($(strip $(Compiler_CORE_PATH)),)
DEP_CONVERTER   = $(PLUGINS_BASE)/Compiler_$(Compiler_VARIANT)/make/$(TARGET)/$(TOOLCHAIN)/convert_tasking_dep_3.5.pl
else
DEP_CONVERTER   = $(Compiler_CORE_PATH)/make/$(TARGET)/$(TOOLCHAIN)/convert_tasking_dep_3.5.pl
endif

ifeq ($(strip $(Compiler_CORE_PATH)),)
GET_LICENSE_SCRIPT   = $(PLUGINS_BASE)/Compiler_$(Compiler_VARIANT)/make/$(TARGET)/$(TOOLCHAIN)/get_license.pl
else
GET_LICENSE_SCRIPT   = $(Compiler_CORE_PATH)/make/$(TARGET)/$(TOOLCHAIN)/get_license.pl
endif

ifeq (,$(findstring $(subst \,/,$(CPP)),$(wildcard $(subst \,/,$(CPP)))))
  $(error FILE DOES NOT EXIST CPP $(CPP) $(wildcard $(subst \,/,$(CPP))))
endif

ifeq (,$(findstring $(subst \,/,$(CTC)),$(wildcard $(subst \,/,$(CTC)))))
  $(error FILE DOES NOT EXIST CTC $(CTC))
endif

ifeq (,$(findstring $(subst \,/,$(DEP_CONVERTER)),$(wildcard $(subst \,/,$(DEP_CONVERTER)) )))
  $(error FILE DOES NOT EXIST DEP_CONVERTER $(DEP_CONVERTER))
endif

ifeq (,$(findstring $(subst \,/,$(GET_LICENSE_SCRIPT)),$(wildcard $(subst \,/,$(GET_LICENSE_SCRIPT)) )))
  $(error FILE DOES NOT EXIST GET_LICENSE_SCRIPT $(GET_LICENSE_SCRIPT))
endif

ifeq (,$(findstring $(subst \,/,$(firstword $(PERL_EXE))),$(wildcard $(subst \,/,$(firstword $(PERL_EXE))) )))
  $(error FILE DOES NOT EXIST PERL $(firstword $(PERL_EXE)))
endif

# call the converter script every time make resolves it's variables
# in this way the tasking depend files are always converted before being
# included by make
CONVERTER_OUTPUT := $(shell $(PERL_EXE) $(DEP_CONVERTER) $(DEPEND_DIR) $(OBJ_DIR))

WAIT_FOR_LICENSE := $(shell $(PERL_EXE) $(GET_LICENSE_SCRIPT) $(COMPILER_DIR)/ctc.exe $(MAKECMDGOALS))
