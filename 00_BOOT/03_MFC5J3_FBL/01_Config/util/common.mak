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

#################################################################
# ATTENTION:
# Blanks are not allowed in directories and file names!
#
# For more information on the makefiles and the build environment,
# see chapter 'Build environment' in the Base user's guide!

# helper definitions
EMPTY	:=
BLANK	:= $(EMPTY) $(EMPTY)
COMMA	:= ,
DOLLAR	:= $$
# macro for newline, use as $(\n) within make functions to insert a line break
define \n


endef

define \t
	$(EMPTY)
endef

# dynamic definition that adapts to SHELL changes - replaced by static version later
fixCmdPaths	=$(if $(findstring cmd.exe,$(SHELL)),$(subst /,\,$1),$(subst \,/,$1))
ifexist		=$(if $(findstring cmd.exe,$(SHELL)),if exist "$(subst /,\,$1)" $2,[ -e '$1' ] && $2)
DEVNULL		=$(if $(findstring cmd.exe,$(SHELL)),nul:,/dev/null)
#################################################################
# setup and sanitize input paths
#################################################################
override PROJECT_ROOT	:= $(subst \,/,$(PROJECT_ROOT))
override TRESOS_BASE	:= $(subst \,/,$(TRESOS_BASE))
PLUGINS_BASE		?= $(TRESOS_BASE)/plugins
override PLUGINS_BASE	:= $(subst \,/,$(PLUGINS_BASE))
# legacy settings
TRESOS2_BASE		:= $(TRESOS_BASE)
SSC_ROOT		:= $(PLUGINS_BASE)

#################################################################
# UTIL_DIR:
# The user can define own makefiles in the util directory
# of the application (included by name pattern by global.mak)
UTIL_DIR := $(PROJECT_ROOT)/util

#################################################################
# Make_OUTPUT_PATH:
# default output location for files generated by Make,
# if not set from environment
#
Make_OUTPUT_PATH ?= $(PROJECT_ROOT)/output/generated

#################################################################
# MAKE_CFG:
# File generated by Make which provides the project specific
# settings for the build environment, e.g. GEN_OUTPUT_PATH
# or PROJECT_MODULES;
# file must be generated before building is started
#
MAKE_CFG := $(Make_OUTPUT_PATH)/make/Make_cfg.mak

# USE_LEGACY_MAKECFG: If 'true' generate $(MAKE_CFG) in legacy mode,
# otherwise in project mode.
ifndef USE_LEGACY_MAKECFG
  ifeq ($(TESTING_USE_PROJECTIMPORT),true)
    USE_LEGACY_MAKECFG := false
  else
    USE_LEGACY_MAKECFG := $(if $(TRESOS2_PROJECT_NAME),false,true)
  endif
endif

# if file to include does not exist, Make will call rule to create it
-include $(MAKE_CFG)

# include the project settings (legacy mode only)
ifeq ($(USE_LEGACY_MAKECFG),true)
$(info include project_settings.mak)
-include $(UTIL_DIR)/project_settings.mak
endif

# setup and sanitize input paths
override GEN_OUTPUT_PATH     := $(subst \,/,$(GEN_OUTPUT_PATH))
override TRESOS2_OUTPUT_PATH := $(GEN_OUTPUT_PATH)

#################################################################
# include platform specific makefiles
#
-include $(strip $(TARGET))_Makefile.mak
-include $(strip $(TARGET))_$(strip $(DERIVATE))_Makefile.mak

#################################################################
# PROJECT_NAME:
# This variable defines the project name or merely the architecture
# independent part of the project name used for creating
# the fully expanded name of the project (Make variable PROJECT).
# If it is not set explicitly, the directory name is taken
#
PROJECT_NAME ?= $(notdir $(subst /util,,$(CURDIR)))

#################################################################
# PROJECT:
# This variable defines the project name and thus the final name
# of the application.
#
PROJECT := $(TARGET)_$(DERIVATE)_$(PROJECT_NAME)
# CPU: overridable equivalent to TARGET
CPU     ?= $(TARGET)

#################################################################
# set TOOLPATH_COMPILER from user environment if possible
#
ifneq ($(TOOLPATH_COMPILER_$(TARGET)),)
  TOOLPATH_COMPILER ?= $(TOOLPATH_COMPILER_$(TARGET))
endif

#################################################################
# CC_FILES_TO_BUILD:
# The variable CC_FILES_TO_BUILD contains the list of C source
# files which are compiled to object files.
# The default file suffix is 'c' and can be changed by setting
# the variable CC_FILE_SUFFIX
#
# For example:
# CC_FILES_TO_BUILD = $(PROJECT_ROOT)\source\application\test\file1.c \
#                     $(PROJECT_ROOT)\source\application\test\file2.c \
#                     $(PROJECT_ROOT)\source\application\test\file3.c
#
CC_FILES_TO_BUILD += $(wildcard $(addprefix $(PROJECT_ROOT)/source/,\
  AesLib/*.c application/*.c application/$(TARGET)/*.c application/$(TARGET)/$(DERIVATE)/*.c\
  stubs/*.c stubs/$(TARGET)/*.c stubs/$(TARGET)/$(DERIVATE)/*.c))

#################################################################
# CPP_FILES_TO_BUILD:
# The variable CPP_FILES_TO_BUILD contains the list of C++ source
# files which are compiled to object files.
# The default file suffix is 'cpp' and can be changed by setting
# the variable CPP_FILE_SUFFIX
#
# For example:
# CPP_FILES_TO_BUILD = $(PROJECT_ROOT)\source\application\test\file4.cpp \
#                      $(PROJECT_ROOT)\source\application\test\file5.cpp \
#                      $(PROJECT_ROOT)\source\application\test\file6.cpp
#
#
CPP_FILES_TO_BUILD +=

#################################################################
# ASM_FILES_TO_BUILD:
# The variable ASM_FILES_TO_BUILD contains the list of assembler
# files. These files are compiled to object files.
# The default file suffix is 'asm' and can be changed by setting
# the variable ASM_FILE_SUFFIX
#
# For example:
# ASM_FILES_TO_BUILD = $(PROJECT_ROOT)\source\asm\myasmfile.asm vectortable.asm
# or
# ASM_FILES_TO_BUILD = $(PROJECT_ROOT)\source\asm\myasmfile.asm \
#                      $(PROJECT_ROOT)\source\application\vectortable.asm
#
ASM_FILES_TO_BUILD +=

#################################################################
# LIBRARIES_TO_BUILD:
# The variable LIBRARIES_TO_BUILD is a list that contains the
# names of all application libraries. These libraries are used to
# manage all source files of the application. In the makefile one
# additional setting named <library name>_FILES is necessary for
# each application library to specify the file paths of all source
# files that are used to build the library.
#
# For example:
# LIBRARIES_TO_BUILD = blinker_lib light_lib
#
# blinker_lib_FILES = $(PROJECT_ROOT)\src\blinker_main.c \
#                     $(PROJECT_ROOT)\src\blinker_init.c \
#                     $(PROJECT_ROOT)\src\blinker_cyclic.c
#
# light_lib_FILES = $(PROJECT_ROOT)\src\light_main.c \
#                   $(PROJECT_ROOT)\src\light_on.c \
#                   $(PROJECT_ROOT)\src\light_off.c
#
# ATTENTION:
# If make reports an error like -The input line is too long- by calling
# the linker or the library builder, the count of configured libraries
# (or source files per library) is too long.
# Due to the limitation in the length of the Windows command line,
# the count of configurable libraries is limited. The limitation
# depends on the version of the Windows console (cmd.exe) which
# depends on the version of Windows. GNU Make calls the linker and
# passes options and arguments on the command line.
# The maximal length of the command line in Windows 7 is:
# 8196 characters
#
LIBRARIES_TO_BUILD += FS8x_src

FS8x_src_FILES      := \
     $(PROJECT_ROOT)\source\FS8x_driver\sbc_fs8x.c \
     $(PROJECT_ROOT)\source\FS8x_driver\sbc_fs8x_communication.c \
     $(PROJECT_ROOT)\source\FS8x_driver\Gp_PwrCtrl.c

ifeq ($(USE_LOG),true)
LIBRARIES_TO_BUILD += Log_src

Log_src_FILES      := \
     $(PROJECT_ROOT)\source\log\log.c \
     $(PROJECT_ROOT)\source\log\lsglog.c \
     $(PROJECT_ROOT)\source\log\printf.c
endif

#################################################################
# LIBRARIES_LINK_ONLY:
# This variable defines additional libraries. These libraries are
# not building during the build process. They must exist therefore.
#
# For example:
# LIBRARIES_LINK_ONLY = C:\Programme\matlab\libs\matlab.a
#
LIBRARIES_LINK_ONLY += $(PROJECT_ROOT)\source\mbedtls\mbedtls.a

#################################################################
# OBJECTS_LINK_ONLY :
# This variable defines additional objects. These objects are
# not building during the build process. They must exist therefore.
#
# For example:
# OBJECTS_LINK_ONLY = C:\Programme\matlab\libs\matlabobj.obj
#
OBJECTS_LINK_ONLY +=

#################################################################
# CC_INCLUDE_PATH, CPP_INCLUDE_PATH and ASM_INCLUDE_PATH:
# The paths to own user include files. The paths must be preceded
# by no option . If more than one path is used, you will have
# to separate them by spaces.
#
# For example:
# CC_INCLUDE_PATH = C:\ssc_st10\my_include_folder \
#                   C:\more_includes
#
CC_INCLUDE_PATH  += \
  $(PROJECT_ROOT)/source/FS8x_driver\
  $(PROJECT_ROOT)/source/mbedtls\
  $(PROJECT_ROOT)/source/log\
  $(PROJECT_ROOT)/source/stubs\
  $(PROJECT_ROOT)/source/stubs/$(TARGET)\
  $(PROJECT_ROOT)/source/stubs/$(TARGET)/$(DERIVATE)\
  $(PROJECT_ROOT)/source/application\
  $(PROJECT_ROOT)/source/application/$(TARGET)\
  $(PROJECT_ROOT)/source/application/$(TARGET)/$(DERIVATE)\
  $(PROJECT_ROOT)/source/boards/$(BOARD)\
  $(PROJECT_ROOT)/source/config\
  $(PROJECT_ROOT)/source/AesLib\
  $(PROJECT_ROOT)/source/config/$(TOOLCHAIN)

CPP_INCLUDE_PATH +=

ASM_INCLUDE_PATH += $(PROJECT_ROOT)/source/boards/$(BOARD)

#################################################################
# global preprocessor options:
# (setting of controller family/derivate)
#
PREPROCESSOR_DEFINES   += ts_arch_family ts_arch_derivate
ts_arch_family_KEY     := TS_ARCH_FAMILY
ts_arch_derivate_KEY   := TS_ARCH_DERIVATE
ts_arch_family_VALUE   := TS_$(TARGET)
ts_arch_derivate_VALUE := TS_$(DERIVATE)

ifeq ($(USE_LEGACY_MAKECFG),true)
#################################################################
# include the project settings  (legacy mode only)
#################################################################
-include $(PROJECT_ROOT)\util\project_settings.mak
endif

#################################################################
# setup TRESOS_BASE and PLUGINS_BASE
#################################################################
PLUGINS_BASE ?= $(TRESOS_BASE)\plugins
# legacy settings
TRESOS2_BASE := $(TRESOS_BASE)
SSC_ROOT     := $(PLUGINS_BASE)

#################################################################
# Define the default target with a default dependency to generate
# the project configuration makefile;
#################################################################
all: $(MAKE_CFG)
mak: $(MAKE_CFG)

#################################################################
# Check mandatory variables are not empty and
# paths do not contain blanks

ifeq ($(TARGET),)
  $(error The variable TARGET is not set)
endif
ifeq ($(DERIVATE),)
  $(error The variable DERIVATE is not set)
endif
ifeq ($(TOOLCHAIN),)
  $(error The variable TOOLCHAIN is not set)
endif
ifeq ($(PROJECT_ROOT),)
  $(error The variable PROJECT_ROOT is not set)
endif
ifneq (1,$(words $(PROJECT_ROOT)))
  $(error The path given by variable PROJECT_ROOT=$(PROJECT_ROOT) \
is not valid, blanks are not allowed. Please change the path and \
set PROJECT_ROOT in file 'launch_cfg.bat' accordingly)
endif
ifeq ($(TRESOS_BASE),)
  $(error The variable TRESOS_BASE is not set)
endif
ifneq (1,$(words $(TRESOS_BASE)))
  $(error The path given by variable TRESOS_BASE=$(TRESOS_BASE) \
is not valid, blanks are not allowed. Please change the path and \
set TRESOS_BASE in file 'launch_cfg.bat' accordingly)
endif
ifeq ($(PLUGINS_BASE),)
  $(error The variable TRESOS_BASE is not set)
endif
ifneq (1,$(words $(PLUGINS_BASE)))
  $(error The path given by variable PLUGINS_BASE=$(PLUGINS_BASE) \
is not valid, blanks are not allowed. Please change the path and \
set PLUGINS_BASE in file 'launch_cfg.bat' accordingly)
endif

#################################################################
# Include the global makefile to start the build process

# Check for project specific global.mak
ifneq (,$(wildcard $(subst \,/,$(PROJECT_ROOT)/util/global.mak)))
  # use global.mak from util folder of application
  include $(PROJECT_ROOT)/util/global.mak
else
  # check that variable Make_VARIANT is set;
  # when a project is generated for the first time, Make_VARIANT
  # is not yet set, thus global.mak cannot be included
  ifneq (,$(Make_VARIANT))
    # use default global.mak
    include $(PLUGINS_BASE)/Make_$(Make_VARIANT)/make/global.mak
  endif
endif

#################################################################
# generate linker file when all object files are known
-include $(BOARD_PROJECT_PATH)/$(BOARD)_link.mak

#################################################################
# For debugging purposes: target that prints environment into
# log file "make.set.log".
generate_env:
	set > make.set.log

#################################################################
# Target to generate the build environment config file
# legacy mode
ifeq ($(USE_LEGACY_MAKECFG),true)
$(MAKE_CFG): 
	$(info ==============================================)
	$(info . GENERATING build environment config (legacy))
	$(if $(wildcard $(@D)),,$(info $(shell $(MKDIR) $(@D) 2>$(DEVNULL))))
	$(file >$(subst \,/,$@),\
	override PROJECT_ROOT    := $$(subst \,/,$$(PROJECT_ROOT))$(\n)\
	TRESOS2_ECU_ID           := ECU$(\n)\
	PROJECT_OUTPUT_PATH      := $$(PROJECT_ROOT)/output$(\n)\
	GEN_OUTPUT_PATH          := $$(PROJECT_OUTPUT_PATH)/generated$(\n)\
	AUTOSAR_BASE_OUTPUT_PATH := $$(GEN_OUTPUT_PATH))
	$(info ==============================================)

# for tests in project mode but with legacy Make_cfg.mak,
# remove the file generated by tresos Studio after the "make generate" call,
# and recreate it
ifneq ($(TRESOS2_PROJECT_NAME),)
generate:
	@$(if $(wildcard $(MAKE_CFG)),del $(call fixCmdPaths,$(MAKE_CFG)) && )$(MAKE) -f $(firstword $(MAKEFILE_LIST)) $(MAKE_CFG) GEN_OUTPUT_PATH=$(GEN_OUTPUT_PATH)
endif

else

# project mode

# Do not replace "$(TRESOS_BASE)\bin\tresos_cmd.bat" with variable
# $(TRESOS2_GENERATOR) or use other variables as the makefile where
# it is defined cannot be included before $(MAKE_CFG) is created and included
# As a rule: only use functions & variables, defined within this file.
$(MAKE_CFG):
	$(info ========================================)
	$(info . GENERATING build environment config)
ifneq (,$(TRESOS2_USE_TMP_WORKSPACE))
ifneq (,$(TRESOS2_WORKSPACE_DIR))
	$(file  >$(UTIL_DIR)/tresos_makecfg.batch,importProject $(PROJECT_ROOT))
	$(file >>$(UTIL_DIR)/tresos_makecfg.batch,$(TRESOS2_USER_OPTIONS) make generate_project_data $(TRESOS2_PROJECT_NAME))
	@if exist $(subst /,\,$(TRESOS2_WORKSPACE_DIR)) del /f /s /q $(subst /,\,$(TRESOS2_WORKSPACE_DIR)) > nul
	@call $(subst /,\,$(TRESOS_BASE)\bin\tresos_cmd.bat) -data $(TRESOS2_WORKSPACE_DIR) batch $(UTIL_DIR)/tresos_makecfg.batch
else
	@call $(subst /,\,$(TRESOS_BASE)\bin\tresos_cmd.bat) $(TRESOS2_USER_OPTIONS) make generate_project_data $(TRESOS2_PROJECT_NAME)
endif
else
	call $(TRESOS_BASE)\bin\tresos_cmd.bat $(TRESOS2_USER_OPTIONS) make generate_project_data $(TRESOS2_PROJECT_NAME)
endif
	@echo ****************************************

endif
