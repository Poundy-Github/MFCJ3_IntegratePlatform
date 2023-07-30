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
#================================================================
# Contains rules for building a flat directory structure
#================================================================

FLAT_OUT_DIR = $(subst \,/,$(OUTPUT_DIR))

# ------------  Project Directories  ---------------------------------------------------
FLAT_DIR         = $(FLAT_OUT_DIR)/flat_src
FLAT_DIR_DOS     = $(call fixCmdPaths,$(FLAT_DIR))
FLAT_SRC_DIR     = $(FLAT_DIR)/src
FLAT_OBJ_DIR     = $(FLAT_DIR)/obj
FLAT_BIN_DIR     = $(FLAT_DIR)/bin
FLAT_MAK_DIR     = $(FLAT_DIR)/mak
FLAT_DEP_DIR     = $(FLAT_DIR)/dep
FLAT_LIB_DIR     = $(FLAT_DIR)/lib
FLAT_DEP_INC     = $(FLAT_MAK_DIR)/dep.inc
FLAT_C_INC       = $(FLAT_MAK_DIR)/c.inc
FLAT_CPP_INC     = $(FLAT_MAK_DIR)/cpp.inc
FLAT_ASM_INC     = $(FLAT_MAK_DIR)/asm.inc
FLAT_LNK_INC     = $(FLAT_MAK_DIR)/lnk.inc
FLAT_SRC_INC     = $(FLAT_MAK_DIR)/src.inc
COPY_LIB_RULES   = $(FLAT_OUT_DIR)/make/copy_lib_rules.mak
FLAT_OUT_LIB     = $(FLAT_OBJ_DIR)/$(basename $(PROJECT_BINARY)).$(LIB_FILE_SUFFIX)
FLAT_LIB         = $(FLAT_MAK_DIR)/lib.inc
FLAT_MAK         = $(FLAT_MAK_DIR)/make.inc


FLAT_LIBS        = $(foreach LIB, $(LIBRARIES_LINK_ONLY) $(OBJECTS_LINK_ONLY),$(FLAT_LIB_DIR)/$(notdir $(LIB)))

ifneq ($(MAKECMDGOALS),depend)
  ifneq ($(MAKECMDGOALS),clean_all)
    ifneq ($(MAKECMDGOALS),clean)
      # create directories
      ifneq (bin depend generated lib flat_src list make obj temp,$(notdir $(sort $(wildcard $(OUTPUT_DIR)/*))))
        SHELLCOMMAND:=$(shell $(call ifnotexist,$(FLAT_DIR_DOS), mkdir $(FLAT_DIR_DOS) ))
        SHELLCOMMAND:=$(shell $(call ifnotexist,$(FLAT_SRC_DIR), mkdir $(call fixCmdPaths,$(FLAT_SRC_DIR)) ))
        SHELLCOMMAND:=$(shell $(call ifnotexist,$(FLAT_OBJ_DIR), mkdir $(call fixCmdPaths,$(FLAT_OBJ_DIR)) ))
        SHELLCOMMAND:=$(shell $(call ifnotexist,$(FLAT_BIN_DIR), mkdir $(call fixCmdPaths,$(FLAT_BIN_DIR)) ))
        SHELLCOMMAND:=$(shell $(call ifnotexist,$(FLAT_DEP_DIR), mkdir $(call fixCmdPaths,$(FLAT_DEP_DIR)) ))
        SHELLCOMMAND:=$(shell $(call ifnotexist,$(FLAT_MAK_DIR), mkdir $(call fixCmdPaths,$(FLAT_MAK_DIR)) ))
        SHELLCOMMAND:=$(shell $(call ifnotexist,$(FLAT_LIB_DIR), mkdir $(call fixCmdPaths,$(FLAT_LIB_DIR)) ))
      endif
    endif
  endif
endif
# ------------  tools  --------------------------------------------------------------
FLAT_SRC_SCRIPT     := $(MAKE_ROOT)/tools/scripts/createFlatSrc.pl

# ------------  rules  --------------------------------------------------------------

# $(copy-platform-files) --> see optional definition in compiler_rules.mak of Compiler plugin

flat_src: $(SRC_LIST) $(HDR_LIST) $(FLAT_DEP_INC) $(FLAT_C_INC) $(FLAT_CPP_INC) $(FLAT_LNK_INC) $(FLAT_LIB) $(FLAT_MAK) $(FLAT_ASM_INC) $(FLAT_SRC_INC) $(DLL_RULES) $(FLAT_LIBS) $(LOC_FILE)
	@$(PERL_EXE) $(FLAT_SRC_SCRIPT) --src=$(SRC_LIST) --hdr=$(HDR_LIST) --depDir=$(DEPEND_DIR) --destDir=$(FLAT_DIR)
	@$(COPY) $(call fixCmdPaths,$(PLUGINS_BASE)\Compiler_$(Compiler_VARIANT)\make\$(CPU)\$(TOOLCHAIN)\Compiler$(RULES_FILE_SUFFIX)) $(FLAT_DIR_DOS)\Compiler$(RULES_FILE_SUFFIX) >nul
	@$(call ifexist,$(PLUGINS_BASE)\Compiler_$(Compiler_VARIANT)\make\$(CPU)\$(TOOLCHAIN)\linux_Makefile, $(COPY) $(call fixCmdPaths,$(PLUGINS_BASE)\Compiler_$(Compiler_VARIANT)\make\$(CPU)\$(TOOLCHAIN)\linux_Makefile) $(FLAT_DIR_DOS)\Makefile >nul)
	@$(call ifnotexist,$(PLUGINS_BASE)\Compiler_$(Compiler_VARIANT)\make\$(CPU)\$(TOOLCHAIN)\linux_Makefile, echo WARNING: linux_Makefile not found for toolchain $(TOOLCHAIN) in Compiler_$(Compiler_VARIANT))
	@$(COPY) $(call fixCmdPaths,$(LOC_FILE)) $(FLAT_DIR_DOS)\$(notdir $(LOC_FILE)) >nul
	$(copy-platform-files)
	@$(ECHO) Created flat source in $(FLAT_DIR)

define	copy-lib-file
	$(info copying $(notdir $<))
	@$(COPY) $(call fixCmdPaths,$< $@) > nul
endef

$(COPY_LIB_RULES):
	$(info Building $(notdir $(COPY_LIB_RULES)))
	$(file > $@, Dempty_dummy=0)
	$(foreach LIB, $(LIBRARIES_LINK_ONLY) $(OBJECTS_LINK_ONLY),\
          $(file >> $(COPY_LIB_RULES),\
            $(FLAT_LIB_DIR)/$(notdir $(LIB)) : $(subst \,/,$(LIB)) ; $(DOLLAR)(copy-lib-file) \
          )\
        )

$(FLAT_SRC_INC): $(MAKEFILE_LIST)
	$(info Building $(notdir $(FLAT_SRC_INC)))
	$(file > $(FLAT_SRC_INC), Dempty_dummy=0)
	$(foreach SRC, $(sort $(CC_FILES_TO_BUILD) $(ASM_FILES_TO_BUILD)),\
          $(file >> $(FLAT_SRC_INC),\
             SRC_FILE_TO_BUILD+=./src/$(notdir $(subst -,_,$(SRC)))\
          )\
        )
	$(foreach OBJ, $(sort $(LINK_ONLY_OBJ) $(OBJECTS_LINK_ONLY)),\
          $(file >> $(FLAT_SRC_INC),\
             LINK_ONLY_OBJ+=./obj/$(notdir $(subst -,_,$(OBJ)))\
          )\
        )
	$(file >> $(FLAT_SRC_INC),\
        LOC_FILE=$(notdir $(LOC_FILE))\
     )\


$(FLAT_DEP_INC):
	$(info Building $(notdir $(FLAT_DEP_INC)))
	$(file > $@,-Dempty_dummy)
	$(file >>$@,-I./src)
	$(file >>$@,$(filter -D%, $(CC_OPT)) $(cppGetPreProcessorDefines))
	$(shell $(DOS2UNIX) $@)

$(FLAT_C_INC):
	$(info Building $(notdir $(FLAT_C_INC)))
	$(file > $@,-Dempty_dummy)
	$(file >>$@,-I./src)
	$(file >>$@, $(CC_OPT) $(cppGetPreProcessorDefines))
	$(shell $(DOS2UNIX) $@)

$(FLAT_ASM_INC):
	$(info Building $(notdir $(FLAT_ASM_INC)))
	$(file > $@,-Dempty_dummy)
	$(file >>$@,-I./src)
	$(file >>$@, $(ASM_OPT) $(filter -D%, $(CC_OPT)) $(cppGetPreProcessorDefines))
	$(shell $(DOS2UNIX) $@)

$(FLAT_CPP_INC):
	$(info Building $(notdir $(FLAT_CPP_INC)))
	$(file > $@,-Dempty_dummy)
	$(file >>$@,-I./src)
	$(file >>$@, $(CPP_OPT) $(cppGetPreProcessorDefines))
	$(shell $(DOS2UNIX) $@)

ifeq ($(build-link-inc-file-PROVIDED),)
$(FLAT_LNK_INC):
	$(file >$@, $(subst \,/,$(LINK_OPT)))
	$(foreach i,$(subst -,_,$(LINK_ONLY_OBJ)), $(file >>$@,./obj/$(notdir $i)))
	$(foreach i,$(subst -,_,$(LIBRARIES_LINK_ONLY)), $(file >>$@,./lib/$(notdir $i)))
	$(foreach i,$(subst -,_,$(OBJECTS_LINK_ONLY)), $(file >>$@,./lib/$(notdir $i)))
	$(file >>$@,$(addprefix ./lib/,$(notdir $(FLAT_OUT_LIB))))
else
$(FLAT_LNK_INC):
	$(build-link-inc-file-flat)
endif

$(FLAT_MAK):
	$(file > $@,#generated file $(notdir $@))
	$(file >>$@,PROJECT_BINARY=$(notdir $(PROJECT_BINARY)))
	$(file >>$@,CC_OPT=$(CC_OPT))
	$(file >>$@,ASM_OPT=$(ASM_OPT))
	$(file >>$@,CPP_OPT=$(CPP_OPT))
	$(file >>$@,LINK_OPT=$(subst \,/,$(LINK_OPT)))
	$(file >>$@,BOARD=$(BOARD))
	$(file >>$@,TARGET=$(TARGET))
	$(file >>$@,DERIVATE=$(DERIVATE))
	$(file >>$@,TOOLCHAIN=$(TOOLCHAIN))


$(FLAT_LIB):
	$(info Building $(notdir $(FLAT_LIB)))
	$(file > $(FLAT_LIB),# generated file $(notdir $(FLAT_LIB)))
	$(foreach OBJ, \
	  $(addprefix ./obj/,\
	    $(addsuffix .$(OBJ_FILE_SUFFIX), \
	      $(notdir \
	        $(basename $(LIB_OBJECTS_OUT)) \
	      ) \
	    )\
	  ),\
	  $(file >>$(FLAT_LIB), \
	    $(addprefix ./lib/,$(notdir $(FLAT_OUT_LIB))): $(subst -,_,$(OBJ)) \
	  ) \
	)


ifneq ($(MAKECMDGOALS),clean)
-include $(COPY_LIB_RULES)
endif