# \file
#
# \brief AUTOSAR Platforms
#
# This file contains the implementation of the AUTOSAR
# module Platforms.
#
# \author Elektrobit Automotive GmbH, 91058 Erlangen, Germany
#
# Copyright 2005 - 2016 Elektrobit Automotive GmbH
# All rights exclusively reserved for Elektrobit Automotive GmbH,
# unless expressly agreed to otherwise.

GET_LOC_FILE = $(if $(EXT_LOCATOR_FILE),$(EXT_LOCATOR_FILE),$(LOC_FILE))

EB_VERBOSE?=
    
####################################################################################################
# build-exe-file
#---------------------------------------------------------------------------------------------------
# Target................: $(PROJECT_BINARY)
#---------------------------------------------------------------------------------------------------
# $@....................: e.g. project.elf
# $(LNK_INC)............: generated linker option file (e.g. <PROJECT_ROOT>/output/make/link.inc)
# $(GET_LOC_FILE).......: linker locator file 
#---------------------------------------------------------------------------------------------------
# Desciption............: defines the call to the linker
####################################################################################################
define build-exe-file
    $(EB_VERBOSE)$(LINK) --via=$(LNK_INC) --scatter=$(GET_LOC_FILE) -o $@
	$(EB_VERBOSE)$(LINK) --via=$(LNK_INC) --scatter=$(GET_LOC_FILE) -o $(HEXFILE)
	@echo ******************************
	@echo ** BUILD DONE
	@echo ******************************
endef

####################################################################################################
# build-c-file
#---------------------------------------------------------------------------------------------------
# Target................: see obj_to_cc.mak
#---------------------------------------------------------------------------------------------------
# $@....................: full path to object file e.g. <OBJ_DIR>/Appl_Main.o
# $<....................: full path to source file e.g. <SRC_DIR>/Appl_Main.c
# $(DEPEND_DIR).........: depend directory e.g. <PROJECT_ROOT>/output/depend
# $(MAKE_INC)...........: compiler option file e.g. <PROJECT_ROOT>/output/make/compiler.inc
# $(OBJ_DIR)............: object directory e.g. <PROJECT_ROOT>/output/obj
# $(CC).................: executable for building objects defined in compiler_defs.mak
# $(MOVE)...............: executable to move files (e.g. plugins/Make_TS_VARIANT/tools/mv.exe)
#---------------------------------------------------------------------------------------------------
# Desciption............: defines the call to the compiler
####################################################################################################
define build-c-file
	$(info compiling: $(notdir $<) $(if $(filter $(MAKE_INC),$(MAKE_INC_DEFAULT)),,(using $(notdir $(MAKE_INC)))))
	$(file > $(DEPEND_DIR)/$(notdir $(basename $@)).d, TEST=compile error in c file $(notdir $<))
	$(EB_VERBOSE)$(CC) -MD @$(MAKE_INC) -c -o $(OBJ_DIR)/$(notdir $(basename $@)).o $<
	@if exist $(OBJ_DIR)/$(notdir $(basename $@)).d $(EB_VERBOSE)$(MOVE) $(OBJ_DIR)/$(notdir $(basename $@)).d $(DEPEND_DIR)/$(notdir $(basename $@)).d
	@if exist $(notdir $(basename $@)).s $(MOVE) $(notdir $(basename $@)).s $(OBJ_DIR)/$(notdir $(basename $@)).s
endef

####################################################################################################
# build-s-file
#---------------------------------------------------------------------------------------------------
# Target................: see obj_to_cc.mak
#---------------------------------------------------------------------------------------------------
# $@....................: full path to object file e.g. <OBJ_DIR>/cstartup.o
# $<....................: full path to source file e.g. <SRC_DIR>/cstartup.s
# $(DEPEND_DIR).........: depend directory e.g. <PROJECT_ROOT>/output/depend
# $(DEPEND_INC).........: option file for the gcc (contains only -D and -I options)
# $(ASM_OPT)............: assembler options
# $(GCC)................: executable for building dependencies defined in compiler_defs.mak
# $(OBJ_DIR)............: object directory e.g. <PROJECT_ROOT>/output/obj
# $(ASM).................: executable for building objects from assembler source (see compiler_defs.mak)
#---------------------------------------------------------------------------------------------------
# Desciption............: defines the call to the compiler
####################################################################################################
define build-s-file
	$(info assembling: $(notdir $<))
	$(EB_VERBOSE)$(GCC) -MM @$(DEPEND_INC) $<  > $(DEPEND_DIR)/$(notdir $(basename $@)).d
	$(EB_VERBOSE)$(ASM) @$(ASM_INC) -c -x assembler-with-cpp  $< -o $(OBJ_DIR)/$(notdir $(basename $@)).o
endef

####################################################################################################
# build-lib-file
#---------------------------------------------------------------------------------------------------
# Target................: see lib_to_obj.mak
#---------------------------------------------------------------------------------------------------
# $@....................: full path to library file e.g. <LIB_DIR>/Base_src.a
# $+....................: list of object files e.g. <OBJ_DIR>/cstartup.o <OBJ_DIR>/Appl_Main.o
# $(CCLIB)..............: executable for building objects defined in compiler_defs.mak
#---------------------------------------------------------------------------------------------------
# Desciption............: defines the call to the archiver to build a lib from a list of objects
#                       : this is a recursive call
####################################################################################################
define build-lib-file
	$(call SC_CMD_LISTPERFORM,SC_CMD_AR_HELPER,\
		$(info building lib: $(notdir $@)) \
		$(EB_VERBOSE)$(CCLIB) -r $@,20,21, $+)
endef



build-link-inc-file-PROVIDED=TRUE
define build-link-inc-file
	$(info Linking)
	$(file >$@, $(subst \,/,$(LINK_OPT)))
    $(foreach i,$(addprefix --libpath=,$(LIB_INCLUDE_PATH)), $(file >>$@,$(subst \,/,$i)))
	$(foreach i,$(LINK_ONLY_OBJ), $(file >>$@,$(subst \,/,$i)))
	$(foreach i,$(LIBRARIES_LINK_ONLY), $(file >>$@,$(subst \,/,$i)))
	$(foreach i,$(OBJECTS_LINK_ONLY), $(file >>$@,$(subst \,/,$i)))
	$(foreach i,$(OUTPUT_PATH_LIBS), $(file >>$@,$(subst \,/,$i)))
endef
