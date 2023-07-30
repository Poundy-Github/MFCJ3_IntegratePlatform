#################################################################
#
# NAME: $Id: TriboardTC3X7TH.mak 26142 2017-03-14 12:34:14Z nibo2437 $
#
# FUNCTION: This file is part of the Autosar SC build environment.
#
# Copyright Elektrobit Automotive GmbH
# All rights exclusively reserved for Elektrobit Automotive GmbH,
# unless expressly agreed to otherwise.
#
#################################################################



##################################################################
#
# DEFINITIONS


CC_INCLUDE_PATH      += $(BOARD_PROJECT_PATH)
CPP_INCLUDE_PATH     += $(BOARD_PROJECT_PATH)
ASM_INCLUDE_PATH     += $(BOARD_PROJECT_PATH)

CC_FILES_TO_BUILD += $(BOARD_PROJECT_PATH)\board.c \
                     $(BOARD_PROJECT_PATH)\boardextra.c

EXCLUDE_MAKE_DEPEND  += $(BOARD_PROJECT_PATH)\cstartup.s \
                        $(BOARD_PROJECT_PATH)\vector_vle_eb.s
ASM_FILES_TO_BUILD +=  $(BOARD_PROJECT_PATH)\cstartup.s \
                       $(BOARD_PROJECT_PATH)\vector_vle_eb.s

######################## Defines for Linker file ############

ifeq ($(TOOLCHAIN),tasking)
LOC_FILE_SUFFIX=ldscript
endif

ifeq ($(TOOLCHAIN),dcc)
LOC_FILE_SUFFIX=dld
endif

LOC_FILE?=$(BOARD_PROJECT_PATH)/TC38XQ_$(TOOLCHAIN).$(LOC_FILE_SUFFIX)



#################################################################
# TRACE32_PATH
# Path to the Trace32 Debugger
#
TRACE32_PATH ?= C:\T32
# old T32
#TRACE32_APP_PATH ?= $(TRACE32_PATH)
# new T32 runnning on windows and linx
TRACE32_APP_PATH ?= $(TRACE32_PATH)\bin\windows64
