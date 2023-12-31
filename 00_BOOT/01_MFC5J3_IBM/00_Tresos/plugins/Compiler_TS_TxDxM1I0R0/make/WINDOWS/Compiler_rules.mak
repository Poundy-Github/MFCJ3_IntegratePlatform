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

#################################################################
# this file just references the compiler_rules.mak makfiles
# in the TOOLCHAIN directory
include $(Compiler_CORE_PATH)/make/$(TARGET)/$(TOOLCHAIN)/Compiler$(RULES_FILE_SUFFIX)

#################################################################
# PROJECT_BINARY: path to the executable
#
# This is currently identical to FIRST_BUILD_TARGET for all
# supported compilers, therefore it is set here
PROJECT_BINARY := $(FIRST_BUILD_TARGET)

# append one dependency to the target for the project binary (created by build-exe-file)
$(PROJECT_BINARY): $(PROJECT_BINARY).manifest

# copy the application manifest file to the project binary to disable Windows user access control (UAC)
$(PROJECT_BINARY).manifest: $(Compiler_CORE_PATH)/make/$(TARGET)/application.manifest
	@$(COPY) $(call fixCmdPaths,$< $@) >$(DEVNULL)

# opens the debugger with current test
debug start_debug:
	$(DEBUGGER) $(PROJECT_BINARY)

# runs test and outputs Ts5Atl test result (only for Windows)
.PHONY: run
run:
	@set TS5ATL_PRINTRESULT=1 && $(PROJECT_BINARY)
