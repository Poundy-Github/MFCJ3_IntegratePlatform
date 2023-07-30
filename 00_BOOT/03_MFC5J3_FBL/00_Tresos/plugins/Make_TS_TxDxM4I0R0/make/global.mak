# \file
#
# \brief AUTOSAR Make
#
# This file contains the implementation of the AUTOSAR
# module Make.
#
# \author Elektrobit Automotive GmbH, 91058 Erlangen, Germany
#
# Copyright 2005 - 2019 Elektrobit Automotive GmbH
# All rights exclusively reserved for Elektrobit Automotive GmbH,
# unless expressly agreed to otherwise.

# set shell for Make
ifeq ($(OS),Windows_NT)
  SHELL := %WINDIR%/system32/cmd.exe
endif
# flag if Make is running on Windows, check if shell is cmd.exe
# (the make variable OS is overwritten by included plugin makefiles)
IS_DOS_SHELL := $(findstring cmd.exe,$(SHELL))
ifneq (,$(IS_DOS_SHELL))
  .SHELLFLAGS= /x /c
endif
# verify Make version
ifneq (4.0,$(MAKE_VERSION))
  $(error $(MAKE_VERSION) detected! expected Make version 4.0)
endif
# check if realpath works
ifeq (,$(realpath $(wildcard ../*)))
  $(error realpath returned empty string! ensure make in version at least 3.82 is installed)
endif

# macros for special characters
# sanitize input paths (backslashes are evil -> quoting hell)
EMPTY	:=
BLANK	:= $(EMPTY) $(EMPTY)
COMMA	:= ,
DOLLAR	:= $$
# macro for newline, use as $(\n) within make functions to insert a line break
define \n


endef

# macro for tabulator, use as $(\t) within make functions to insert a tab
define \t
	$(EMPTY)
endef

# don't evaluate CC_FILES_TO_BUILD -> $(wildcard caching problem for generated files
# TRESOS_BASE and PROJECT_ROOT are already sanitized by common.mak
#------------ directory checks
ifeq (,$(wildcard $(PROJECT_ROOT)))
  $(error DIRECTORY DOES NOT EXIST PROJECT_ROOT $(PROJECT_ROOT))
endif
ifeq (,$(wildcard $(subst \,/,$(TRESOS_BASE))))
  $(error DIRECTORY DOES NOT EXIST TRESOS_BASE $(TRESOS_BASE))
endif

# include configuration makefile
-include $(TARGET)_$(DERIVATE)_$(TOOLCHAIN)_cfg.mak

#################################################################
# Define the suffix for all files which implement the interfaces:
# Compiler Makefile Interface
# Board Makefile Interface
# Basic Software Makefile Interface
# Utility Makefile Interface
MAK_FILE_SUFFIX		?= mak
DEFS_FILE_SUFFIX	?= _defs.$(MAK_FILE_SUFFIX)
RULES_FILE_SUFFIX	?= _rules.$(MAK_FILE_SUFFIX)
CHECK_FILE_SUFFIX	?= _check.$(MAK_FILE_SUFFIX)
CFG_FILE_SUFFIX		?= _cfg.$(MAK_FILE_SUFFIX)

# one of the few paths in backslash-notation, because it's solely used to execute the tresos_cmd.bat
TRESOS_BIN		:= $(subst /,\,$(abspath $(TRESOS_BASE)/bin))
# we need 'override' here or we couldn't sanitize backslashes passed on the make command line
override FORWARD_PLUGINS_BASE	:= $(abspath $(subst \,/,$(PLUGINS_BASE)))
MAKE_ROOT		:= $(FORWARD_PLUGINS_BASE)/Make_$(Make_VARIANT)
BOARD_PROJECT_PATH	?= $(PROJECT_ROOT)/source/boards/$(BOARD)

# ------------  tools  --------------------------------------------------------------
# include GNU Make standard library
include $(MAKE_ROOT)/tools/gmsl/gmsl
# define variables as shortcuts for tools
TRACE32_DIR		?= $(TOOLS_BASE)/T32
TRACE32_BIN		?= $(TRACE32_DIR)/bin/windows/t32mppc.exe
TRACE32_CONFIG		?= $(EOCM_PATH)/EOCM_Base/config.t32

# std unix tools & respective DOS/Windows ports form a GNU tools abstraction layer
ifeq (,$(IS_DOS_SHELL))
  STATUS		:= $$?
  MKDIR			:= mkdir -p
  RM			:= rm -f
  MV			:= mv
  COPY			:= cp
  CP			:= cp
  RMTREE		:= rm -Rf
  RMDIR			:= rm -Rf
  DOS2UNIX		:= dos2unix
  PERL_EXE		:= perl
  ECHO			:= echo
  WHICH			:= which
  CPP			:= cpp
else
  STATUS		:= %ERRORLEVEL%
  # gnu & unix tools compiled for DOS can take forward-slash paths and can take unexpanded wildcards, but cmd.exe needs a backslash path to find them
  _MAKE_TOOLS		 = $(subst /,\,$(MAKE_ROOT))\tools
  _SFK_EXE		 = $(_MAKE_TOOLS)\sfk\sfk.exe
  _MKDIR_EXE		 = $(_MAKE_TOOLS)\GNU_Utils\mkdir.exe
  MKDIR			:= $(_MKDIR_EXE) -p
  _RM_EXE		 = $(_MAKE_TOOLS)\GNU_Utils\rm.exe
  RM			:= $(_RM_EXE) -f
  _MOVE_EXE		 = $(_MAKE_TOOLS)\GNU_Utils\mv.exe
  MOVE			:= $(_MOVE_EXE) -f
  MV			:= $(MOVE)
  _CP_EXE		 = $(_MAKE_TOOLS)\GNU_Utils\cp.exe
  CP			:= $(_CP_EXE)
# DEPRECATED
  # we use Windows/DOS copy because if you pass a "path/*.ext" parameter
  # to regular tools an invalid "path*.ext" pattern would be forwarded.
  # ... to be fixed
  COPY			:= copy /y
  RMTREE		:= $(_RM_EXE) -Rf
  # deprecated - use RMTREE instead!
  RMDIR			:= rmdir /s /q
  _DOS2UNIX_EXE		 = $(_MAKE_TOOLS)\dos2unix\dos2unix.exe
  DOS2UNIX		:= $(_DOS2UNIX_EXE) -q
  PERL_EXE		 = $(_MAKE_TOOLS)\strawberryperl\perl.exe -I$(MAKE_ROOT)/tools/strawberryperl
  ECHO			:= @$(_SFK_EXE) echo -spat
  WHICH			:= $(_SFK_EXE) pathfind
  _CPP_EXE		 = $(_MAKE_TOOLS)\gcc\bin\cpp.exe
  CPP			:= $(_CPP_EXE)

  ifeq (,$(wildcard $(subst \,/,$(_RM_EXE))))
    $(error FILE DOES NOT EXIST RM_EXE $(_RM_EXE))
  endif

  ifeq (,$(wildcard $(subst \,/,$(_MOVE_EXE))))
    $(error FILE DOES NOT EXIST MOVE_EXE $(_MOVE_EXE))
  endif

  ifeq (,$(wildcard $(subst \,/,$(_CP_EXE))))
    $(error FILE DOES NOT EXIST CP_EXE $(_CP_EXE))
  endif

  ifeq (,$(wildcard $(subst \,/,$(_MKDIR_EXE))))
    $(error FILE DOES NOT EXIST MKDIR_EXE $(_MKDIR_EXE))
  endif

  ifeq (,$(wildcard $(subst \,/,$(_SFK_EXE))))
    $(error FILE DOES NOT EXIST SFK_EXE $(_SFK_EXE))
  endif

  ifeq (,$(wildcard $(subst \,/,$(_CPP_EXE))))
    $(error FILE DOES NOT EXIST CPP_EXE $(_CPP_EXE))
  endif

  ifeq (,$(wildcard $(subst \,/,$(_DOS2UNIX_EXE))))
    $(error FILE DOES NOT EXIST DOS2UNIX_EXE $(_DOS2UNIX_EXE))
  endif

  ifneq (,$(IS_DOS_SHELL))
    ifeq (,$(wildcard $(subst \,/,$(firstword $(PERL_EXE)))))
      $(error FILE DOES NOT EXIST PERL_EXE $(firstword $(PERL_EXE)))
    endif
  endif
endif

# deprecated
SEPARATOR		:= $(ECHO) . 
CHECK_DUPS		:= $(MAKE_ROOT)/tools/scripts/check_dups.pl
CPP_DEPS		:= $(MAKE_ROOT)/tools/scripts/cppDeps.pl


# IF-conversion: do the correct path separator fixup for DOS/cmd.exe & linux/bash
# handles lists of paths and even full command lines, but doesn't handle commas in the input
ifeq (,$(IS_DOS_SHELL))
  fixCmdPaths=	$(subst \,/,$(1))
  ifexist=	[ -e '$1' ] && $2
  ifnotexist=	[ -e '$1' ] || $2
  DEVNULL:=	/dev/null
else
  fixCmdPaths=	$(subst /,\,$(1))
  ifexist=	if exist "$(subst /,\,$1)" $2
  ifnotexist=	if not exist "$(subst /,\,$1)" $2
  DEVNULL:=	nul:
endif

# commandline compression:
# cd to that directory and strip that directory prefix from all paths
# allows use of relative and absolute paths
# cd is an internal command in all shells, so doesn't add to execution time
# && is recognized by bash & cmd.exe
# used with fixCmdPaths, this is shell-agnostic
# Note: for the replacement to work, the directory has to include the suitable trailing slash
# This is not required, if only relative paths are used in the actual command
# as always, commas that need to be passed WITHIN an argument must be passed as $(COMMA)
runIn=cd $(call fixCmdPaths,$(1)) && $(subst $(1),,$(2))

################################################################
# helper to execute a command in a foreach loop or recursively
# note: the 3rd line (empty) is really needed to serve as a cmd-separator.
#
# args: 1 - cmd(s) to perform
define SC_CMD_AR_HELPER
	$(1)

endef
define SC_CMD_AR2_HELPER
	$(1)
	$(2)

endef

################################################################
# recursive helper to perform a task on chunks of a list
# note: do not place a space in front of argument 5 of the recursive call,
#       ( $(4),<here>$(wordlist... )). This would result in infinite recursion.
#
# args: 1 - variable-name that contains commands to perform
#       2 - additional arguments to $(1)
#       3 - max. number of elements in a chunk
#       4 - obsolete - was "$3+1 (sorry, cannot perform arith in make)"
#       5 - list
SC_CMD_LISTPERFORM = $(if $(5),\
  $(call $(1),$(2) $(wordlist 1,$(3),$(5)))\
  $(call SC_CMD_LISTPERFORM,$(1),$(2),$(3),_,$(filter-out $(wordlist 1,$(3),$(5)),$(5))))

# ------------  Project Directories  ---------------------------------------------------
# define paths relative to PROJECT_ROOT
# they help with DOS/Win/CygWin/linux agnostic code and small DOS commandline
REL_OUT_DIR			:= output
REL_BIN_DIR			:= $(REL_OUT_DIR)/bin
REL_DEP_DIR			:= $(REL_OUT_DIR)/depend
REL_LIB_DIR			:= $(REL_OUT_DIR)/lib
REL_MAKE_DIR			:= $(REL_OUT_DIR)/make
REL_OBJ_DIR			:= $(REL_OUT_DIR)/obj
REL_LIST_DIR			:= $(REL_OUT_DIR)/list
REL_LOG_DIR			:= $(REL_OUT_DIR)/temp

# now define absolute paths
OUTPUT_DIR			:= $(PROJECT_ROOT)/$(REL_OUT_DIR)
BIN_OUTPUT_PATH			:= $(PROJECT_ROOT)/$(REL_BIN_DIR)
DEPEND_DIR			:= $(PROJECT_ROOT)/$(REL_DEP_DIR)
LIB_DIR				:= $(PROJECT_ROOT)/$(REL_LIB_DIR)
MK_TMP_DIR			:= $(PROJECT_ROOT)/$(REL_MAKE_DIR)
OBJ_DIR				:= $(PROJECT_ROOT)/$(REL_OBJ_DIR)
LIST_DIR			:= $(PROJECT_ROOT)/$(REL_LIST_DIR)
LOG_DIR				:= $(PROJECT_ROOT)/$(REL_LOG_DIR)

OBJ_OUTPUT_PATH			:= $(OBJ_DIR)
GENERATED_DIR			 = $(subst \,/,$(GEN_OUTPUT_PATH))
GEN_OUTPUT_PATHS		?= $(GENERATED_DIR)
override GEN_OUTPUT_PATHS	:= $(subst \,/,$(GEN_OUTPUT_PATHS))
AUTOSAR_BASE_OUTPUT_PATH	?= $(OUTPUT_DIR)/generated
override AUTOSAR_BASE_OUTPUT_PATH	:= $(subst \,/,$(AUTOSAR_BASE_OUTPUT_PATH))

# add generated library directory to list of library include paths
LIB_INCLUDE_PATH		+= $(LIB_DIR)

# ------------  compiler  --------------------------------------------------------------
MAKE_INC_DEFAULT		 = $(MK_TMP_DIR)/compiler.inc
MAKE_INC			 = $(if $($(basename $(notdir $@))_OPTMAP),$($(basename $(notdir $@))_OPTMAP),$(MAKE_INC_DEFAULT))
MAKE_INCPP			 = $(MK_TMP_DIR)/compiler.incpp
ASM_INC				 = $(MK_TMP_DIR)/assembler.inc
DEPEND_INC			 = $(MK_TMP_DIR)/depend.inc
LNK_INC				 = $(MK_TMP_DIR)/lnk.inc
LIB_TO_OBJ			 = $(MK_TMP_DIR)/lib_to_obj.mak
OBJ_TO_CC			 = $(MK_TMP_DIR)/obj_to_cc.mak
PREP_TO_CC			 = $(MK_TMP_DIR)/prep_to_cc.mak
MAKE_INFO_FILE			 = $(MK_TMP_DIR)/make.info
PLUGIN_INC			 = $(MK_TMP_DIR)/plugins.mak
OPT_MAP				 = $(MK_TMP_DIR)/opt.map
SRC_LIST			 = $(MK_TMP_DIR)/src_list.txt
HDR_LIST			 = $(MK_TMP_DIR)/hdr_list.txt
GLOBAL_LIB_DIR_NAME		:= global_lib_dir.$(TOOLCHAIN)
GLOBAL_LIB_DIR			?= $(PLUGINS_BASE)\$(GLOBAL_LIB_DIR_NAME)
GLOBAL_LIB_DIR_F		 = $(subst \,/,$(GLOBAL_LIB_DIR))


# ------------  first rules  ------------------------------------------------------------
# declare 'all' as the default rule, if no make target was specified on the command line
.DEFAULT: all
.PHONY: all run mak postbuild clean clean_all clean_global preprocess depend show_rules single_file single_lib single_lib_clean

#all:
# just a little top-level magic to simplify things downstream
# simulation-of-simplicity (SOS): fold identical cases 'make' & 'make all'
# also do the right thing for TS_BUILD_POST_BUILD_BINARY
ifeq (,$(MAKECMDGOALS))
  override MAKECMDGOALS:=$(if $(filter TRUE,$(TS_BUILD_POST_BUILD_BINARY)),postbuild,all)
endif
ifeq (all run,$(filter all run,$(MAKECMDGOALS)))
run: all

endif

# don't create directories for cleaning & depend, but consider multiple make targets like "make depend all"
ifneq (,$(filter-out depend clean% $(MAKE_CLEAN_RULES),$(MAKECMDGOALS)))
  # check which directories need creation
  # we use gnu make -p (even on DOS), so concatenate them to one path that's efficiently creating the whole tree
  dirlist := $(addprefix $(OUTPUT_DIR)/,$(subst $(BLANK),/../,$(filter-out $(notdir $(wildcard $(OUTPUT_DIR)/*)),bin depend generated lib list make obj temp)))
  ifneq (,$(GLOBAL_LIB_ENABLE))
    ifeq (,$(wildcard $(GLOBAL_LIB_DIR_F)))
        dirlist += $(GLOBAL_LIB_DIR_F)
    endif
  endif
  ifneq (,$(dirlist))
    # at most 2 full paths in the list
    SHELLCOMMAND:=$(shell $(MKDIR) $(dirlist))
  endif
endif # all targets, except clean* & depend


# define postbuild output file 
POSTBUILD_BINARY = $(basename $(PROJECT_BINARY)).bin

# ------------  plugins  ----------------------------------------------------------------
# include all generated makefiles if they exist
GEN_MAKE_FILES = $(wildcard $(addsuffix /make/*.mak*,$(GEN_OUTPUT_PATHS)))

# only do the heavy lifting, if there are make targets left after ignoring all clean& help targets
ifneq (,$(filter-out show_rules clean% $(MAKE_CLEAN_RULES),$(MAKECMDGOALS)))
  ifneq (,$(filter-out generate% %generate depend,$(MAKECMDGOALS)))
    ifeq (,$(strip $(GEN_OUTPUT_PATH)))
      $(error No GEN_OUTPUT_PATH defined! Run make generate first)
    endif
    ifeq (,$(findstring Make_cfg.mak,$(GEN_MAKE_FILES)))
      ifeq (,$(findstring tresos2_call_generator,$(MAKECMDGOALS)))
        # if 'false' or empty
        ifeq (,$(filter-out false,$(USE_LEGACY_MAKECFG)))
          $(error $(MAKECMDGOALS) : Make_cfg.mak not found! Run make generate first)
        endif
      endif
    endif
  endif # not depend or *generate*

  ifneq (,$(GEN_MAKE_FILES))
    include $(GEN_MAKE_FILES)
  endif
  # filter out "Make" we do not need it
  PROJECT_MODULES_FILTERED := $(sort $(filter-out Make Testing tresos2, $(SOFTWARE_MODULES)))
  ifneq (,$(PROJECT_MODULES_FILTERED))

    # concatenate Module names (e.g. CRC) and TS-Strings (e.g. TS_TxDxM5I1R0) to a single string (e.g. CRC_TS_TxDxM5I1R0)
    FULL_TS_STRINGS = $(foreach PLUGIN, $(PROJECT_MODULES_FILTERED), $(PLUGIN)_$($(PLUGIN)_VARIANT))
    # concatenate FULL_TS_STRINGS (e.g. CRC_TS_TxDxM5I1R0) and PLUGINS_BASE (e.g. S:/PROJECTSPACE/eclipse/plugins) to S:/PROJECTSPACE/eclipse/plugins/CRC_TS_TxDxM5I1R0
    PLUGIN_DIRS = $(subst \,/,$(foreach DIR, $(PROJECT_MODULES_FILTERED), $(if $($(DIR)_CORE_PATH), $($(DIR)_CORE_PATH), $(addprefix $(FORWARD_PLUGINS_BASE)/,$(DIR)_$($(DIR)_VARIANT)))))
    # generate list of make dirs (e.g. S:/PROJECTSPACE/eclipse/plugins/Resource_TS_T2D17M0I9R0/make)
    PLUGIN_MAKE_DIRS = $(addsuffix /make/*$(DEFS_FILE_SUFFIX), $(PLUGIN_DIRS)) \
                       $(addsuffix /make/*$(RULES_FILE_SUFFIX), $(PLUGIN_DIRS)) \
                       $(addsuffix /make/*$(CHECK_FILE_SUFFIX), $(PLUGIN_DIRS))
    # use wildcard function to generate a list of all plugin make files
    PLUGIN_MAKES = $(wildcard $(PLUGIN_MAKE_DIRS))
    $(info including plugin makefiles: $(subst $(FORWARD_PLUGINS_BASE),$${PLUGIN_BASE},$(PLUGIN_MAKES)))
    $(eval $(addprefix $(\n)include ,$(PLUGIN_MAKES)))
  endif # ifneq (,$(PROJECT_MODULES_FILTERED))
endif # ifeq (,(filter show_rules single_lib_clean clean_all clean_global clean,(MAKECMDGOALS))

# define suffixes if not overridden by Compiler_defs.mak
ASM_FILE_SUFFIX		?= asm
CPP_FILE_SUFFIX		?= cpp
CC_FILE_SUFFIX		?= c
OBJ_FILE_SUFFIX		?= o
LIB_FILE_SUFFIX		?= a
PREP_FILE_SUFFIX	?= p

CC_FILTER_LIST		?= %.$(CC_FILE_SUFFIX)
ASM_FILTER_LIST		?= %.$(ASM_FILE_SUFFIX)
CPP_FILTER_LIST		?= %.$(CPP_FILE_SUFFIX)

# ------------  helper  ------------------------------------------------------
override CC_INCLUDE_PATH	:=$(call uniq,$(subst \,/,$(CC_INCLUDE_PATH)))
override USER_INCLUDE_PATH	:=$(call uniq,$(subst \,/,$(USER_INCLUDE_PATH)))
override LOCAL_INC_DIR		:=$(call uniq,$(subst \,/,$(LOCAL_INC_DIR)))

BASENAMES		 = $(call uniq,$(basename $(notdir $(realpath $(subst \,/,$(CC_FILES_TO_BUILD) $(ASM_FILES_TO_BUILD))))))
OBJECTS			 = $(addprefix $(OBJ_DIR)/,   $(addsuffix .$(OBJ_FILE_SUFFIX),$(BASENAMES)))
PREREQUISITES		 = $(addprefix $(DEPEND_DIR)/,$(addsuffix .d,$(BASENAMES)))
PREP_FILES		 = $(addprefix $(LIST_DIR)/,  $(addsuffix .$(PREP_FILE_SUFFIX),$(BASENAMES)))
GEN_INC_DIR		 = $(addsuffix /include,$(GEN_OUTPUT_PATHS))
ALL_INC_DIR		 = $(call uniq,$(addprefix -I,$(USER_INCLUDE_PATH) $(GEN_INC_DIR) $(filter-out $(GEN_INC_DIR), $(LOCAL_INC_DIR) $(CC_INCLUDE_PATH))))
HDR_PATH		 = $(USER_INCLUDE_PATH) $(filter-out $(USER_INCLUDE_PATH),$(CC_INCLUDE_PATH))

# generate preprocessor defines from key-value-pairs
cppGetPreProcessorDefines = $(foreach DEF,$(PREPROCESSOR_DEFINES),-D$($(DEF)_KEY)=$($(DEF)_VALUE))
# filter out libs where files are empty
LIBRARIES_TO_BUILD	:= $(sort $(foreach LIB_ITEM, $(LIBRARIES_TO_BUILD),$(if $($(LIB_ITEM)_FILES),$(LIB_ITEM))))

# ------------  list of lib only objects  ----------------------------------------------------------------
# list all objects in lib files
LIB_OBJECTS		 = $(addsuffix .$(OBJ_FILE_SUFFIX), $(sort $(basename $(notdir $(subst \,/,$(foreach LIB_ITEM,$(LIBRARIES_TO_BUILD),$($(LIB_ITEM)_FILES)))))))
# add output dir to all lib files
LIB_OBJECTS_OUT		 = $(addprefix $(OBJ_DIR)/, $(LIB_OBJECTS))
# get objects which are not in libraries
LINK_ONLY_OBJ		 = $(filter-out $(LIB_OBJECTS_OUT), $(OBJECTS))
# create list of all libs with output path
OUTPUT_PATH_LIBS	 = $(addprefix $(LIB_DIR)/, $(addsuffix .$(LIB_FILE_SUFFIX), $(LIBRARIES_TO_BUILD)))

# list all objects in postbuild libraries
POSTBUILD_OBJECTS	 = $(addsuffix .$(OBJ_FILE_SUFFIX), $(basename $(notdir $(foreach LIB_ITEM, $(LIBRARIES_PBCFG_TO_BUILD),$($(LIB_ITEM)_FILES)))))
# add output dir to all lib files
POSTBUILD_OBJECTS_OUT	 = $(addprefix $(OBJ_DIR)/, $(POSTBUILD_OBJECTS))

# ------------  main rules  ------------------------------------------------------------

# this is for handling the TS_BUILD_POST_BUILD_BINARY=TRUE commandline trigger
# normally you can just type "make postbuild" but this does not (yet) work for the legacy testcases
ifeq ($(TS_BUILD_POST_BUILD_BINARY),TRUE)
all: postbuild

else
all: $(PROJECT_BINARY) $(MAKE_INFO_FILE)

endif

# include the optional board make file here!
-include $(BOARD_PROJECT_PATH)/$(BOARD).mak
ifeq ($(MAKECMDGOALS),flat_src)
  ifneq (,$(IS_DOS_SHELL))
    include $(MAKE_ROOT)/make/flat_src.mak
  else
    $(error flat_src only supported for Windows)
  endif
endif

# check if post build files exist 
ifneq (,$(POSTBUILD_OBJECTS_OUT))
postbuild: $(POSTBUILD_BINARY)

else
postbuild:
	$(info WARNING: no postbuild files defined!)

endif

# ------------  rules for final binaries  ----------------------------------------------

# rule for invocation of the linker to build the executable
$(PROJECT_BINARY): $(OUTPUT_PATH_LIBS) $(LNK_INC) $(LINK_ONLY_OBJ) $(LIB_TO_OBJ) $(MAKE_CFG) $(LING_PREP) $(OBJ_TO_CC) $(LOC_FILE)
	$(build-exe-file)

# rule for generating the postbuild binary
$(POSTBUILD_BINARY): $(POSTBUILD_OBJECTS_OUT)
	$(build-postbuild-file)

# ------------  list of lib only sources  ----------------------------------------------------------------

# list of all source and postbuild config libs which are project specific
SRC_LIBS_TO_BUILD		 = $(filter %_src,$(LIBRARIES_TO_BUILD))
PBCONFIG_LIBS_TO_BUILD		 = $(filter %_pbconfig,$(LIBRARIES_TO_BUILD))

# list of all static lib which can be shared between projects
STATIC_LIBS			 = $(filter-out $(SRC_LIBS_TO_BUILD) $(PBCONFIG_LIBS_TO_BUILD),$(LIBRARIES_TO_BUILD))

# list of static libs which do not exist yet in the shared directory
ifneq (,$(GLOBAL_LIB_ENABLE))
  STATIC_LIBS_TO_BUILD = $(foreach LIB_ITEM,\
                                  $(STATIC_LIBS),\
                                  $(if $(wildcard $(GLOBAL_LIB_DIR_F)/$(LIB_ITEM).$(LIB_FILE_SUFFIX)),\
                                    ,\
                                    $(LIB_ITEM)\
                          ))
else
  STATIC_LIBS_TO_BUILD = $(STATIC_LIBS)
endif
# list of all libs which needs to be build
TOTAL_LIBS_TO_BUILD		 = $(SRC_LIBS_TO_BUILD) $(PBCONFIG_LIBS_TO_BUILD) $(STATIC_LIBS_TO_BUILD)

# list of all source files which needs to be build
LIB_SOURCES			 = $(subst \,/,$(foreach LIB_ITEM,$(TOTAL_LIBS_TO_BUILD),$($(LIB_ITEM)_FILES)))
CC_FILES_TO_BUILD		+= $(LIB_SOURCES)
OS_LIBS		 		 = $(OS_KERNEL_LIB_NAME) $(OS_USER_LIB_NAME) $(OS_ERROR_LIB_NAME) Os_src
NON_OS_LIBS			 = $(filter-out $(OS_LIBS), $(LIBRARIES_TO_BUILD))

# create a list of unique pathes and filter all duplicates from it (see ASCMAKE-552)
UNIQUE_SOURCES			 = $(call uniq,$(realpath $(subst \,/,$(CC_FILES_TO_BUILD) $(ASM_FILES_TO_BUILD))))

$(OUTPUT_PATH_LIBS):
ifeq (,$(GLOBAL_LIB_ENABLE))
	$(build-lib-file)
else
	$(if $(findstring $(basename $(@F)), $(SRC_LIBS_TO_BUILD) $(PBCONFIG_LIBS_TO_BUILD)),\
          $(build-lib-file),\
          $(if $(wildcard $(GLOBAL_LIB_DIR_F)/$(@F)),\
            $(COPY) $(call fixCmdPaths,$(GLOBAL_LIB_DIR_F)/$(@F) $@) >$(DEVNULL),\
            $(build-lib-file)))
	$(if $(findstring $(basename $(@F)), $(STATIC_LIBS)),\
          $(if $(wildcard $(GLOBAL_LIB_DIR_F)/$(@F)),\
            ,\
            $(COPY) $(call fixCmdPaths,$@ $(GLOBAL_LIB_DIR_F)/$(@F)) >$(DEVNULL) ))
endif

# ------------  rules  ------------------------------------------------------

#create all the files created by the make environment, same as the dependencies for the target PROJECT_BINARY
mak: $(LNK_INC) $(LIB_TO_OBJ) $(MAKE_CFG) $(LING_PREP) $(OBJ_TO_CC) $(LOC_FILE)

# list of directories for clean (all except generated)
clean_dirs := depend lib list make obj temp flat_src
ifeq (,$(CLEAN_KEEP_LOGS))
  clean_dirs += test
endif
ifeq (,$(CLEAN_KEEP_BIN))
  clean_dirs += bin
endif

clean:
ifneq (,$(IS_DOS_SHELL))
	@cd $(subst /,\,$(OUTPUT_DIR))\
	$(foreach DIR, $(clean_dirs), & $(RMTREE) $(DIR))
else
	@rm -r -f $(addprefix $(OUTPUT_DIR)/,$(clean_dirs)
endif

# clean_all just deletes the generated and output folder
clean_all:
ifneq (,$(IS_DOS_SHELL))
	@$(RMDIR) $(subst /,\,$(GENERATED_DIR)) & $(RMTREE) $(subst /,\,$(OUTPUT_DIR))
else
	@rm -r -f $(GENERATED_DIR) $(OUTPUT_DIR)
endif

# delete the output folder for the global libs
clean_global:
ifneq (,$(IS_DOS_SHELL))
	@if exist $(subst /,\,$(GLOBAL_LIB_DIR_F)) $(RMDIR) $(subst /,\,$(GLOBAL_LIB_DIR_F))
else
	@rm -r -f $(GLOBAL_LIB_DIR_F)
endif

MAKE_INFO += \
	PROJECT=$(PROJECT) \
	TARGET=$(TARGET) \
	DERIVATE=$(DERIVATE)

$(MAKE_INFO_FILE):
	$(info Building $(@F))
	$(file >$@,$(addprefix $(\n),$(MAKE_INFO)))

# At least for make files, we can keep paths relative to $(PROJECT_ROOT)  - lazy evaluation!
UNIQUE_SOURCES_REL= $(subst $(PROJECT_ROOT),$$(PROJECT_ROOT),$(subst $(GEN_OUTPUT_PATH),$$(GEN_OUTPUT_PATH),$(subst $(FORWARD_PLUGINS_BASE),$$(FORWARD_PLUGINS_BASE),$(UNIQUE_SOURCES))))

$(OBJ_TO_CC): $(LIB_TO_OBJ) $(MAKE_INC_DEFAULT) $(MAKE_INCPP) $(DEPEND_INC) $(ASM_INC) $(OPT_MAP)
	$(info Building $(@F) $(OS_GENERATED_APPL_FILES))
	$(file > $(OBJ_TO_CC),\
	  $(foreach SRC, $(filter $(CC_FILTER_LIST), $(UNIQUE_SOURCES_REL)),\
	    $(\n)$$(OBJ_DIR)/$(notdir $(basename $(SRC)).$(OBJ_FILE_SUFFIX)) $$(DEPEND_DIR)/$(notdir $(basename $(SRC)).d): $(SRC); $$(build-c-file))\
	  $(foreach SRC, $(filter $(ASM_FILTER_LIST), $(UNIQUE_SOURCES_REL) ),\
	    $(\n)$$(OBJ_DIR)/$(notdir $(basename $(SRC)).$(OBJ_FILE_SUFFIX)) $$(DEPEND_DIR)/$(notdir $(basename $(SRC)).d): $(SRC); $$(build-s-file))\
	  $(foreach SRC, $(filter $(CPP_FILTER_LIST), $(UNIQUE_SOURCES_REL) ),\
	    $(\n)$$(OBJ_DIR)/$(notdir $(basename $(SRC)).$(OBJ_FILE_SUFFIX)) $$(DEPEND_DIR)/$(notdir $(basename $(SRC)).d): $(SRC); $$(build-cpp-file))\
	)

$(OPT_MAP):
	$(info Building $(@F))
	$(file > $(OPT_MAP),\
	  $(foreach LIB, $(LIBRARIES_TO_BUILD),\
	    $(foreach OBJ, $(notdir $(basename $(subst \,/,$($(LIB)_FILES)))),\
	     $(if $($(LIB)_OPTMAP),$(\n)$(OBJ)_OPTMAP=$($(LIB)_OPTMAP)))))

$(PREP_TO_CC): $(DEPEND_INC)
	$(info Building $(@F))
	$(file > $(PREP_TO_CC),\
	  $(foreach SRC, $(filter $(CC_FILTER_LIST), $(UNIQUE_SOURCES_REL)),\
	    $(\n)$$(LIST_DIR)/$(notdir $(basename $(SRC)).$(PREP_FILE_SUFFIX)): $(SRC); $$(build-prep-file))\
	  $(foreach SRC, $(filter %.s $(ASM_FILTER_LIST), $(UNIQUE_SOURCES_REL)),\
	    $(\n)$$(LIST_DIR)/$(notdir $(basename $(SRC)).$(PREP_FILE_SUFFIX)): $(SRC); $$(build-prep-file))\
	  $(foreach SRC, $(filter $(CPP_FILTER_LIST), $(UNIQUE_SOURCES_REL)),\
	    $(\n)$$(LIST_DIR)/$(notdir $(basename $(SRC)).$(PREP_FILE_SUFFIX)): $(SRC); $$(build-prep-file))\
	)

$(SRC_LIST): $(MAKEFILE_LIST)
	$(info Building $(@F))
	$(file > $(SRC_LIST),$(addprefix $(\n),$(UNIQUE_SOURCES)))

$(HDR_LIST): $(MAKEFILE_LIST)
	$(info Building $(@F))
	$(file > $(HDR_LIST),$(addprefix $(\n),$(HDR_PATH)))

check_dups: $(SRC_LIST) $(HDR_LIST)
	@$(PERL_EXE) $(CHECK_DUPS) --hdr=$(HDR_LIST) --src=$(SRC_LIST)
	$(info Check finished)

ifeq (,$(build-prep-file-PROVIDED))
define build-prep-file
	$(info Preprocessing: $(notdir $<))
	@$(CPP) -E @$(DEPEND_INC) $< > $(LIST_DIR)/$(notdir $(basename $@).$(PREP_FILE_SUFFIX))
endef
endif

ifneq (,$(findstring generate,$(MAKECMDGOALS)))
  # handle all 'generate' and TresosStudio targets, consuming MAKE_GENERATE_RULES
  # includes Testing to allow MAKE_GENERATE_RULES updates
  include $(MAKE_ROOT)/make/tresos2_rules.mak
else 
  # includes Testing if present
  -include $(FORWARD_PLUGINS_BASE)/Testing_$(Testing_VARIANT)/make/Testing.mak
endif # 'generate' in the MAKECMDGOALS

preprocess: $(PREP_TO_CC) $(PREP_FILES)

# ------------  make temp and options files  -------------------------------------------

# Note: as the options specified in CC_OPT and CPP_OPT might contain blanks,
# the make function foreach cannot be used as it would split an option with blank in between
# resulting in an invalid options file.
# As writing all options into a single line might create a line too large for processing,
# line breaks are inserted before the options -D, -W, -X, -K, and -- using make function subst
_MAKE_INC_DEFAULT ?=\
  $(subst \,/,$(subst $(BLANK)-D,$(\n)-D,$(subst $(BLANK)-W,$(\n)-W,$(subst $(BLANK)-X,$(\n)-X,$(subst $(BLANK)-K,$(\n)-K,$(subst $(BLANK)--,$(\n)--,$(CC_OPT))))))\
  $(addprefix $(\n),$(ALL_INC_DIR)))\
  $(addprefix $(\n),$(call cppGetPreProcessorDefines))

$(MAKE_INC_DEFAULT):
	$(info Building $(@F))
	$(file >$@,$(_MAKE_INC_DEFAULT))

_MAKE_INCPP ?=\
  $(subst \,/,$(subst $(BLANK)-D,$(\n)-D,$(subst $(BLANK)-W,$(\n)-W,$(subst $(BLANK)-X,$(\n)-X,$(subst $(BLANK)-K,$(\n)-K,$(subst $(BLANK)--,$(\n)--,$(CPP_OPT))))))\
  $(addprefix $(\n),$(ALL_INC_DIR)))\
  $(addprefix $(\n),$(call cppGetPreProcessorDefines))

$(MAKE_INCPP):
	$(info Building $(@F))
	$(file >$@,$(_MAKE_INCPP))

_ASM_INC ?=\
  $(subst \,/,\
    $(ASM_OPT) $(PFLAGS)\
    $(addprefix $(\n),$(ALL_INC_DIR)))\
  $(addprefix $(\n),$(call cppGetPreProcessorDefines))

$(ASM_INC):
	$(info Building $(@F))
	$(file >$@,$(_ASM_INC))

_DEPEND_INC ?=\
  -DEMPTY\
  $(addprefix $(\n),$(subst \,/,$(ALL_INC_DIR)))\
  $(subst $(BLANK)-D,$(\n)-D,$(filter -D%, $(CC_OPT)) $(cppGetPreProcessorDefines))

$(DEPEND_INC):
	$(info Building $(@F))
	$(file >$@,$(_DEPEND_INC))

override LIB_INCLUDE_PATH	:= $(subst \,/,$(LIB_INCLUDE_PATH))
_LNK_INC ?=\
  $(subst \,/,\
    $(subst $(BLANK)-L,$(\n)-L,$(LINK_OPT))\
    $(addprefix $(\n)-L,$(LIB_INCLUDE_PATH))\
    $(addprefix $(\n),$(LINK_ONLY_OBJ) $(LIBRARIES_LINK_ONLY) $(OBJECTS_LINK_ONLY) $(OUTPUT_PATH_LIBS)))

$(LNK_INC):
ifeq (,$(build-link-inc-file-PROVIDED))
	$(info Linking)
	$(file >$@,$(_LNK_INC))
else
	$(build-link-inc-file)
endif

_LIB_TO_OBJ ?=\
  $(foreach LIB, $(TOTAL_LIBS_TO_BUILD),\
    $(\n)$$(LIB_DIR)/$(LIB).$(LIB_FILE_SUFFIX):\
    $(addprefix \$(\n)  $$(OBJ_DIR)/,\
      $(addsuffix .$(OBJ_FILE_SUFFIX),\
        $(basename $(notdir $(subst \,/,$($(LIB)_FILES))))\
      )\
    )\
  $(\n)\
  )\

$(LIB_TO_OBJ):
	$(info Building $(@F))
	$(file >$@,DEMPTY=0 $(_LIB_TO_OBJ))

# ------------  include the automatically generated prerequisites  ---------------------
# ------------  if target is not clean, tarball or zip             ---------------------

# here we decide whether it is necessary to build the .d files (PREREQUISITES)
# the all target is also allowed to work here
ifneq (,$(filter all%,$(MAKECMDGOALS)))
  # the postbuild target does not need the .d files
  ifneq ($(TS_BUILD_POST_BUILD_BINARY),TRUE)
    -include $(PREREQUISITES)
  endif
endif
ifneq (,$(filter all% postbuild,$(MAKECMDGOALS)))
  -include $(OBJ_TO_CC) $(LIB_TO_OBJ) $(OPT_MAP)
endif
# the preprocess target does not need the .d or .o files
ifeq ($(MAKECMDGOALS),preprocess)
  -include $(PREP_TO_CC)
endif

depend:
	$(info obsolete target: depend)

show_rules:
	@echo .
# to avoid 'nothing to be done for show_rules'
ifeq (,$(SILENT_HELP))
	$(info . -----------------------------------------------------------------)
	$(info .  Environment variables overview)
	$(info . -----------------------------------------------------------------)
  ifneq (,$(MISRA_MODULE))
	$(info .  MODULE            = $(MISRA_MODULE))
  endif
	$(info .  TARGET            = $(TARGET))
	$(info .  DERIVATE          = $(DERIVATE))
  ifneq (,$(SUBDERIVATE))
	$(info .  SUBDERIVATE       = $(SUBDERIVATE))
  endif
	$(info .  TOOLCHAIN         = $(TOOLCHAIN))
  ifeq (,$(TOOLPATH_COMPILER))
    ifneq ($(TARGET),WINDOWS)
	$(info .  TOOLPATH_COMPILER needs to be set to the used compiler directory)
    endif
  else
	$(info .  TOOLPATH_COMPILER = $(TOOLPATH_COMPILER))
  endif
	$(info .  TRESOS_BASE       = $(TRESOS_BASE))
	$(info .)
	$(info .  output directory   $(OUTPUT_DIR))
	$(info .  binaries           $(BIN_OUTPUT_PATH))
	$(info .  libraries          $(LIB_DIR))
	$(info .  generated files    $(GENERATED_DIR))
	$(info .  dependency files   $(DEPEND_DIR))
	$(info .  object files       $(OBJ_DIR))
	$(info .  preprocessed files $(LIST_DIR))
	$(info .)
	$(info . -----------------------------------------------------------------)
	$(info .  EB build rules overview)
	$(info . -----------------------------------------------------------------)
	$(info .  Full Scale Targets:)
	$(info .        make clean         ( remove all except generate folder        ))
	$(info .        make clean_all     ( remove output folder                     ))
	$(info .        make clean_global  ( remove output folder for the global libs ))
	$(info .        make generate      ( run tresos generator                     ))
	$(info .        make -j            ( generate depend files and executable     ))
	$(info .        make preprocess    ( generate preprocessed files              ))
	$(info .        make check_dups    ( check for duplicated file names          ))
	$(info .        make flat_src      ( copy all src files in flattened dir      ))
	$(info .        make mak           ( create all temporary files               ))
	$(info .)
	$(info .  Partial Build Options:)
	$(info .        make single_file SF=Filename      ( rebuild single file       ))
	$(info .        make single_lib  SL=libname       ( rebuild single library    ))
	$(info .        make single_lib_clean SL=libname  ( clean lib .d and .o files ))
	$(info .)
  ifneq (,$(MAKE_CLEAN_RULES)$(MAKE_GLOBAL_RULES))
	$(info .  Additional Targets:)
	$(foreach rule, $(MAKE_CLEAN_RULES),$(info .        make $(rule)		( $($(rule)_DESCRIPTION) )))
	$(foreach rule, $(MAKE_GLOBAL_RULES),$(info .        make $(rule)		( $($(rule)_DESCRIPTION) )))
  endif
endif # SILENT_HELP

ifeq ($(MAKECMDGOALS),single_file)
  SF_BASENAME = $(basename $(notdir $(SF)))
  ifeq (,$(findstring $(SF_BASENAME),$(BASENAMES)))
    $(error unkown filename in SF: "$(SF)")
  endif
  SF_OBJECT = $(addprefix $(OBJ_DIR)/, $(addsuffix .$(OBJ_FILE_SUFFIX),$(SF_BASENAME)))
  SF_PREREQUISITES = $(addprefix $(DEPEND_DIR)/, $(addsuffix .d,$(SF_BASENAME)))
  -include $(SF_PREREQUISITES)
  -include $(OBJ_TO_CC)
# rule for building the file
single_file: $(SF_OBJECT)

endif

# ------------  if single lib is build include only lib prerequisites  ---------------------

#common definitions
ifneq (,$(filter single_lib%,$(MAKECMDGOALS)))

  SINGLE_LIB_FILE_NAME		 = $(LIB_DIR)/$(SL).$(LIB_FILE_SUFFIX)
  SINGLE_LIB_BASENAMES		 = $(basename $(subst \,/,$($(SL)_FILES)))
  SINGLE_LIB_OBJECTS		 = $(addprefix $(OBJ_DIR)/,   $(notdir $(addsuffix .$(OBJ_FILE_SUFFIX),$(SINGLE_LIB_BASENAMES) ) ) )
  SINGLE_LIB_PREREQUISITES	 = $(addprefix $(DEPEND_DIR)/,$(notdir $(addsuffix .d,$(SINGLE_LIB_BASENAMES) ) ) )

  ifeq ($(MAKECMDGOALS),single_lib)

   ifeq (,$(findstring $(SL),$(LIBRARIES_TO_BUILD)))
      $(error Library SL "$(SL)" not defined in LIBRARIES_TO_BUILD: $(LIBRARIES_TO_BUILD))
    endif

  -include $(SINGLE_LIB_PREREQUISITES)
  -include $(OBJ_TO_CC)
  -include $(LIB_TO_OBJ)

single_lib : $(SINGLE_LIB_FILE_NAME)

  endif

  ifeq ($(MAKECMDGOALS),single_lib_clean)
    ifeq (,$(findstring $(SL),$(LIBRARIES_TO_BUILD)))
      $(error Library SL "$(SL)" not defined in LIBRARIES_TO_BUILD: $(LIBRARIES_TO_BUILD))
    endif
single_lib_clean : $(SINGLE_LIB_FILE_NAME)
	$(call SC_CMD_LISTPERFORM,SC_CMD_AR_HELPER,@cd $(PROJECT_ROOT) && $(RM) ,\
		10,11,$(subst \,/,$(subst $(PROJECT_ROOT)\,,$(SINGLE_LIB_OBJECTS) $(SINGLE_LIB_FILE_NAME) $(SINGLE_LIB_PREREQUISITES))))
	$(info ========================================)
	$(info . $(notdir $(SINGLE_LIB_FILE_NAME)) clean SUCCESSFUL)
	$(info ========================================)

  endif
endif
