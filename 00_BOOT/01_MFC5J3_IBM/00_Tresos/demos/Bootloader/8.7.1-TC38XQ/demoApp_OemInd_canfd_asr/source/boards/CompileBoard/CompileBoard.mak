# \file
#
# \brief AUTOSAR Demo
#
# This file contains the implementation of the AUTOSAR
# module Demo.
#
# \author Elektrobit Automotive GmbH, 91058 Erlangen, Germany
#
# Copyright 2005 - 2019 Elektrobit Automotive GmbH
# All rights exclusively reserved for Elektrobit Automotive GmbH,
# unless expressly agreed to otherwise.

############ TOOLCHAIN mapping ##############
OS_TOOLCHAIN=$(TOOLCHAIN)

ifeq ($(TOOLCHAIN),gcc)
OS_TOOLCHAIN=gnu
endif
ifeq ($(TOOLCHAIN),gnu)
OS_TOOLCHAIN=gnu
endif
ifeq ($(TOOLCHAIN),tasking)
OS_TOOLCHAIN=tasking
endif
ifeq ($(TOOLCHAIN),dcc)
OS_TOOLCHAIN=diab
endif

##################################################################
#
# DEFINITIONS
#
ifeq ($(OS_BOARD_DIR), )
OS_BOARD_DIR=$(BOARD_PROJECT_PATH)
endif

CC_INCLUDE_PATH      += $(OS_BOARD_DIR)
CPP_INCLUDE_PATH     += $(OS_BOARD_DIR)
ASM_INCLUDE_PATH     += $(OS_BOARD_DIR)

CC_FILES_TO_BUILD += $(OS_BOARD_DIR)\board.c 
ifeq ($(OS_TOOLCHAIN),tasking)
ASM_FILES_TO_BUILD +=  $(OS_BOARD_DIR)\boardAsmTasking.s
endif
ifeq ($(OS_TOOLCHAIN),gnu)
ASM_FILES_TO_BUILD +=  $(OS_BOARD_DIR)\boardAsmGnu.s
endif

######################## Defines for Linker file generation for Memory protected systems ############

ifeq ($(OS_TOOLCHAIN),gnu)
  LOC_FILE_SUFFIX ?= ldscript
  LINK_OPT += -e main
else
ifeq ($(OS_TOOLCHAIN),tasking)
  LOC_FILE_SUFFIX ?= ldscript
  LINK_OPT += -e main
else
  LOC_FILE_SUFFIX ?= ldscript
  LINK_OPT += -e main
endif
endif


CC_OPT += -DBOARD_DERIVATE=$(DERIVATE)


#LOC_FILE= $(PROJECT_ROOT)\source\boards\$(BOARD)\$(CPU)-$(OS_TOOLCHAIN).ldscript
LOC_FILE?=$(OS_BOARD_DIR)/board-$(OS_TOOLCHAIN).$(LOC_FILE_SUFFIX)

OS_APP_SPECS = \
$(foreach app,$(APPLICATIONS),-app $(app) $(app)_gen.$(OBJ_FILE_SUFFIX) $(OBJS_$(app)) \
  $(foreach task,$(TASKS_$(app)),-task $(task) $(OBJS_$(task))) \
  $(foreach isr,$(ISRS_$(app)),-isr $(isr) $(OBJS_$(isr))) \
)

