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

include $(MAKE_ROOT)/make/tresos2_defs.mak

# if no config files are given in legacy mode, the generator should not be invoked
ifneq (,$(TRESOS2_PROJECT_NAME))
# add dependency to clean_all target
clean_all: 01_revert_merged_xdm
endif

# actually only calls the generator, if TRESOS_EARLY_BATCH_GENERATE is empty (disabled) or 'false' (opt-out)
# note that early generation executes up to here, then blocks the Studio calls, and finally continues from here on
01_tresos2_call_generator: $(TRESOS2_BATCH_FILE)
ifeq (,$(filter-out false,$(TRESOS_EARLY_BATCH_GENERATE)))
  ifeq (,$(TRESOS2_PROJECT_NAME))
	$(info EXECUTE tresos batch (legacy))
	@$(TRESOS2_GENERATOR) $(TRESOS2_WORKSPACE_OPTION) batch $(TRESOS2_BATCH_FILE)
  else
	$(info EXECUTE tresos batch (project))
	@$(TRESOS2_GENERATOR) $(TRESOS2_WORKSPACE_OPTION) batch $(TRESOS2_BATCH_FILE) || \
	( $(ECHO) Generate failed, moving workspace $(TRESOS2_WORKSPACE_DIR) to $(TRESOS2_OUTPUT_PATH)\
	& $(RMTREE) $(TRESOS2_WORKSPACE_OUT) \
	& $(MOVE) -v $(TRESOS2_WORKSPACE_DIR) $(TRESOS2_OUTPUT_PATH) \
	& exit 1 )
  endif
endif

################################################################
# move tresos studio workspace into project output path
# when using project mode and temporary workspace
# early batch generation uses few global workspaces for batch generation,
# so must work without the move
99_zzz_move_workspace:
ifeq (,$(filter-out false,$(TRESOS_EARLY_BATCH_GENERATE)))
  ifneq (,$(TRESOS2_PROJECT_NAME))
    ifneq (,$(TRESOS2_USE_TMP_WORKSPACE))
	-@$(RMDIR) $(TRESOS2_WORKSPACE_OUT) >$(DEVNULL) 2>&1 \
	 & ( $(call ifexist,$(TRESOS2_WORKSPACE_OUT), $(RMDIR) $(TRESOS2_WORKSPACE_OUT) >$(DEVNULL) 2>&1 )) \
	 & $(MOVE) -v $(TRESOS2_WORKSPACE_DIR) $(TRESOS2_OUTPUT_PATH)
    endif
  endif
endif # ifeq (,$(filter-out false,$(TRESOS_EARLY_BATCH_GENERATE)))

################################################################
# this rule invokes the tresos template generator
# select legacy mode or project mode by the TRESOS2_PROJECT_NAME
#
# If TRESOS2_SUPPRESS_GENERATE_SWCD is set, then the "generate_swcd"
# step is skipped in legacy mode.  This should only be used in
# situations were the the generated SWCD files are definitely not used
# in the final generation step.
.PHONY: 01_revert_merged_xdm 01_tresos2_call_generator 99_zzz_move_workspace write_batch_project

ifeq ($(TRESOS2_GENERATOR_MODE),NO_ACTION)
  MAKE_GENERATE_RULES +=
else
  MAKE_GENERATE_RULES += 01_revert_merged_xdm 01_tresos2_call_generator 99_zzz_move_workspace
endif


ifeq (,$(TRESOS2_PROJECT_NAME))
  ################################################################
  # batch commands for legacy mode tests
  LEGACY_BATCH_MERGE_XDM         = \
    -DValidate=FALSE $(TRESOS2_OPTIONS) legacy convert $(TRESOS2_CONF_FILES) $(TRESOS2_MERGED_XDM_FILENAME)
  LEGACY_BATCH_GENERATE_SWCD     = \
    -DEcuResourceModuleIds=$(TRESOS2_CONF_ECU_RESOURCEMODULE_IDS) -DValidate=FALSE -Dosek.orti=TRUE\
    -Dosek.html=FALSE -Dtarget=$(CPU) -Dderivate=$(DERIVATE)\
    $(TRESOS2_SWCD_OPTIONS) $(TRESOS2_USER_OPTIONS)\
    legacy make $(TRESOS2_GENERATE_SWCD_MODE_OPTION) $(TRESOS2_SYSD_GENSWCD_FILES)\
    $(TRESOS2_CONF_INPUT_FILES) $(PLUGINS_TO_GENERATE:%=-g %) -o $(TRESOS2_OUTPUT_PATH) -u
  LEGACY_BATCH_CONVERT           =\
    -DValidate=FALSE $(TRESOS2_OPTIONS) legacy convert $(TRESOS2_SYSD_ALL_FILES) $(TRESOS2_SYSTEM_MODEL40_FILENAME)
  LEGACY_BATCH_GENERATE_CONTRACT =\
    -DEcuResourceModuleIds=$(TRESOS2_CONF_ECU_RESOURCEMODULE_IDS) -DValidate=TRUE -Dosek.orti=TRUE\
    -Dosek.html=FALSE -Dtarget=$(CPU) -Dderivate=$(DERIVATE)\
    $(TRESOS2_OPTIONS) $(TRESOS2_USER_OPTIONS) -Dcontract.merge=true\
    legacy make contract $(TRESOS2_SYSD_ALL_FILES) -g Rte_$(Rte_VARIANT)\
    $(PLUGINS_TO_GENERATE:%=-g %) -o $(TRESOS2_OUTPUT_PATH)/include -u
  LEGACY_BATCH_GENERATE          =\
    -DEcuResourceModuleIds=$(TRESOS2_CONF_ECU_RESOURCEMODULE_IDS) -DValidate=TRUE -Dosek.orti=TRUE\
    -Dosek.html=FALSE -Dtarget=$(CPU) -Dderivate=$(DERIVATE) $(Rte_OPTIONS)\
    $(TRESOS2_OPTIONS) $(TRESOS2_USER_OPTIONS)\
    legacy make generate $(TRESOS2_SYSTEM_MODEL_INPUT_FILES) $(TRESOS2_CONF_INPUT_FILES)\
    $(PLUGINS_TO_GENERATE:%=-g %) -o $(TRESOS2_OUTPUT_PATH) -u

  LEGACY_BATCH_MERGE_XDM_info         := MERGING all module configuration files into a temporary one (legacy)
  LEGACY_BATCH_GENERATE_SWCD_info     := GENERATING tresos SWCD files via generator mode $(TRESOS2_GENERATE_SWCD_MODE_OPTION) (legacy)
  LEGACY_BATCH_CONVERT_info           := Temporarily convert all System Description files to temporary AUTOSAR 4.0 TDB system model
  LEGACY_BATCH_GENERATE_CONTRACT_info := GENERATING tresos Contract phase
  LEGACY_BATCH_GENERATE_info          := GENERATING source files
else
  ################################################################
  # batch commands for project mode test commands
  ifeq ($(TESTING_CALCULATE_HANDLE_ID),true)
    TRESOS2_AUTOCONFIGURE_TARGETS := AutoHandleId $(filter-out AutoHandleId,$(TRESOS2_AUTOCONFIGURE_TARGETS))
  endif
  $(eval \
    $(foreach importer, $(TRESOS2_RUN_IMPORTERS),\
      PROJECT_BATCH_IMPORTER_$(importer)       =\
        $$(TRESOS2_OPTIONS) $$(TRESOS2_USER_OPTIONS) import $$(TRESOS2_PROJECT_NAME) $(importer)$(\n)\
      PROJECT_BATCH_IMPORTER_$(importer)_info :=\
        RUNNING importer $(importer)$(\n)\
    )\
    $(foreach autoconfigure, $(TRESOS2_AUTOCONFIGURE_TARGETS),\
      PROJECT_BATCH_AUTOCONFIGURE_$(autoconfigure)       =\
        $$(TRESOS2_OPTIONS) $$(TRESOS2_USER_OPTIONS) autoconfigure $$(TRESOS2_PROJECT_NAME) $(autoconfigure)\
        $$(TRESOS2_AUTOCONFIGURE_OPTIONS_$(autoconfigure))$(\n)\
      PROJECT_BATCH_AUTOCONFIGURE_$(autoconfigure)_info :=\
        RUNNING autoconfigure $(autoconfigure)$(\n)\
    )\
  )
  PROJECT_BATCH_IMPORT_PROJECT = $(TRESOS2_OPTIONS) $(TRESOS2_USER_OPTIONS) importProject $(PROJECT_ROOT)
  PROJECT_BATCH_GENERATE_SWCD  = $(TRESOS2_OPTIONS) $(TRESOS2_USER_OPTIONS) make generate_swcd $(TRESOS2_PROJECT_NAME)
  PROJECT_BATCH_MERGE_BSWMD    = -DValidate=FALSE $(TRESOS2_OPTIONS) legacy convert $(TRESOS2_MERGE_BSWMD_FILES) $(lastword $(TRESOS2_MERGE_BSWMD_FILES))
  PROJECT_BATCH_GENERATE       = $(TRESOS2_OPTIONS) $(TRESOS2_USER_OPTIONS) make generate $(TRESOS2_PROJECT_NAME) $(PLUGINS_TO_GENERATE:%=-g %)
  PROJECT_BATCH_VERIFY         = $(TRESOS2_OPTIONS) $(TRESOS2_USER_OPTIONS) make $(TRESOS2_VERIFY_TARGET) $(TRESOS2_PROJECT_NAME)

  PROJECT_BATCH_IMPORT_PROJECT_info := IMPORTING tresos project
  PROJECT_BATCH_GENERATE_SWCD_info  := GENERATING tresos SWCD files
  PROJECT_BATCH_MERGE_BSWMD_info    := MERGING tresos BSWMD files
  PROJECT_BATCH_GENERATE_info       := GENERATING source files
  PROJECT_BATCH_VERIFY_info         := VERIFYING tresos project
endif

ifeq (,$(TRESOS2_PROJECT_NAME))
  ################################################################
  # default batch actions to be executed for legacy mode tests
  ifndef LEGACY_BATCH_ACTIONS
    LEGACY_BATCH_ACTIONS := \
      $(if $(filter TRUE,$(TRESOS2_MERGE_XDM)),LEGACY_BATCH_MERGE_XDM) \
      $(if $(TRESOS2_SUPPRESS_GENERATE_SWCD),,LEGACY_BATCH_GENERATE_SWCD) \
      $(if $(filter TRUE,$(TRESOS2_CONVERT_TO_SYSTEM_MODEL40)),LEGACY_BATCH_CONVERT) \
      $(if $(filter TRUE,$(TRESOS2_GENERATE_CONTRACT)),LEGACY_BATCH_GENERATE_CONTRACT) \
      LEGACY_BATCH_GENERATE
  endif
else
  ################################################################
  # default batch actions to be executed for legacy mode tests
  ifndef PROJECT_BATCH_ACTIONS
    PROJECT_BATCH_ACTIONS := \
      $(if $(TRESOS2_USE_TMP_WORKSPACE),PROJECT_BATCH_IMPORT_PROJECT) \
      $(addprefix PROJECT_BATCH_IMPORTER_,$(call uniq,$(TRESOS2_RUN_IMPORTERS))) \
      $(addprefix PROJECT_BATCH_AUTOCONFIGURE_,$(call uniq,$(TRESOS2_AUTOCONFIGURE_TARGETS))) \
      $(if $(TRESOS2_GENERATE_SWCD),PROJECT_BATCH_GENERATE_SWCD) \
      $(if $(TRESOS2_MERGE_BSWMD_FILES),PROJECT_BATCH_MERGE_BSWMD) \
      PROJECT_BATCH_GENERATE \
      $(if $(TRESOS2_VERIFY_TARGET),PROJECT_BATCH_VERIFY)
  endif
endif

################################################################
# targets for writing tresos studio batch files
ifeq (,$(TRESOS2_PROJECT_NAME))
  TRESOS_MERGE_ACTIONS:=
  TRESOS_BATCH_ACTIONS:= $(LEGACY_BATCH_ACTIONS)
  TRESOS_BATCH_COPIES:=
else
define backup_emitter
	@$(call ifnotexist,$(1).orig, $(COPY) $(call fixCmdPaths,$(1) $(1).orig) > $(DEVNULL))

endef
  TRESOS_BATCH_COPIES= \
    $(info MERGING module configuration files) $(\n)\
    $(if $(TRESOS2_USE_TMP_WORKSPACE), $(\n)$(\t)@$(call ifexist,$(TRESOS2_WORKSPACE_DIR), $(RMTREE) $(TRESOS2_WORKSPACE_DIR) > $(DEVNULL) $(\n))) \
    $(foreach plugin,$(TRESOS2_ALL_PLUGINS),$(if $(word 2,$(TRESOS2_$(plugin)_CONF_FILES)),$(call backup_emitter,$(firstword $(TRESOS2_$(plugin)_CONF_FILES)))))
  # we don't want to generate two more variables per plugin to fit them into the BATCH_ACTIONS/_info concept
  TRESOS_MERGE_ACTIONS= \
    $(foreach plugin,$(TRESOS2_ALL_PLUGINS),$(if $(word 2,$(TRESOS2_$(plugin)_CONF_FILES)),$(if $(wildcard $(firstword $(TRESOS2_$(plugin)_CONF_FILES)).orig),,\
      $(\n)-DMapOptionalAsList=false $(TRESOS2_OPTIONS) legacy convert $(TRESOS2_$(plugin)_CONF_FILES) $(firstword $(TRESOS2_$(plugin)_CONF_FILES)))))
  TRESOS_BATCH_ACTIONS:= $(PROJECT_BATCH_ACTIONS)
endif #ifeq (,$(TRESOS2_PROJECT_NAME))

$(info $(foreach v,\
TRESOS2_GEN_PLUGINS\
TRESOS2_NOGEN_PLUGINS\
TRESOS_BATCH_COPIES\
TRESOS_BATCH_ACTIONS\
,$(\n)$(v)=$($(v)))$(\n))

# common batch file emitter rule for PROJECT & LEGACY mode
$(TRESOS2_BATCH_FILE): $(MAKEFILE_LIST) | $(TRESOS2_OUTPUT_PATH)
	$(info WRITING tresos studio batch file $(subst $(subst /,\,$(PROJECT_ROOT)),PROJECT_ROOT,$(@)))
	@$(call TRESOS_BATCH_COPIES)
	$(file > $(TRESOS2_BATCH_FILE),# generated file for batch processing$(\n)\
	  $(TRESOS_MERGE_ACTIONS) \
	  $(foreach action,$(TRESOS_BATCH_ACTIONS),\
	    $(if $(value $(action)_info),$(info $($(action)_info))\
		$(\n)# $(action): $($(action)_info))\
	    $(\n)$($(action))$(\n) ))

################################################################
# revert merged XDM file(s) from copied ones;
# not used MOVE as GNU mv.exe creates lowercase file names 
01_revert_merged_xdm:
	$(foreach xdmfile, $(wildcard $(PROJECT_ROOT)/config/*.xdm.orig), \
	  $(call SC_CMD_AR_HELPER, \
	    -@move /Y $(call fixCmdPaths,$(xdmfile) $(basename $(xdmfile))) > $(DEVNULL) \
	))

# include the Testing make file here! last chance to add to MAKE_GENERATE_RULES
-include $(FORWARD_PLUGINS_BASE)/Testing_$(Testing_VARIANT)/make/Testing.mak

# now consume MAKE_GENERATE_RULES ...
SORTED_MAKE_GENERATE_RULES := $(sort $(MAKE_GENERATE_RULES))

# for the early generate, we split the generate rule into early_generate & the rest
# thus we can call 'make early_generate' to execute everything up to the empty 01_tresos2_call_generator, 
# then run the blocked batch-of-batches Tresos Studio for amortized startup time & cache locality
# then continue with the rest of 'make generate'
# Note: tests can opt-out by setting TRESOS_EARLY_BATCH_GENERATE=false
ifneq (,$(filter-out false,$(TRESOS_EARLY_BATCH_GENERATE)))
  # 1: split-token  2: 1st word of list (empty=end-condition) 3: rest of list
  _split=$(if $(2),$(2) $(call _split,$1,$(filter-out $(1),$(firstword $(3))),$(wordlist 2,100,$(3))))
  # 1: split-token  3: rest of list
  # split-token is included in the returned sub-list
  split=$(call _split,$(1),$(filter-out $(1),$(firstword $(2))),$(wordlist 2,100,$(2)))$(1)
  SORTED_MAKE_EARLY_GENERATE_RULES:= $(call split,01_tresos2_call_generator,$(SORTED_MAKE_GENERATE_RULES))
  SORTED_MAKE_GENERATE_RULES:= $(filter-out $(SORTED_MAKE_EARLY_GENERATE_RULES),$(SORTED_MAKE_GENERATE_RULES))
  # The + in the output marks the things done before /after the early Tresos Studio call
  $(info MAKE_EARLY_GENERATE_RULES= $(SORTED_MAKE_EARLY_GENERATE_RULES)  +  $(SORTED_MAKE_GENERATE_RULES))
endif

ifneq (,$(findstring generate,$(MAKECMDGOALS)))
# handle all 'generate' & TresosStudio targets, consuming MAKE_GENERATE_RULES

# Due to goal-sorting, the 'generate' targets so far cannot be built in parallel
# To still allow a global MAKEFLAGS=-j, we selectively opt out of parallel make for all generate targets
.NOTPARALLEL:
.PHONY: early_generate generate generate_all 01_tresos2_call_generator

early_generate: $(SORTED_MAKE_EARLY_GENERATE_RULES)

generate: $(SORTED_MAKE_GENERATE_RULES)

generate_all: generate
	+$(MAKE) -f $(firstword $(MAKEFILE_LIST)) $(USR_MAKEFLAGS) all

generate_all_run: generate
	+$(MAKE) -f $(firstword $(MAKEFILE_LIST)) $(USR_MAKEFLAGS) all run

endif
