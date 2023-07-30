#EB_Automotive_Makefile

#################################################################
# DEFINITIONS


#################################################################
# REGISTRY

CanTrcv_1_T03_src_FILES   +=                                                         \
                             $(CanTrcv_1_T03_CORE_PATH)\src\CanTrcv_1_T03.c          \
                             $(CanTrcv_1_T03_OUTPUT_PATH)\src\CanTrcv_1_T03_Lcfg.c   \

LIBRARIES_TO_BUILD      += CanTrcv_1_T03_src

# Fill the list with post build configuration files needed to build the post build binary.
CanTrcv_1_T03_pbconfig_FILES := $(wildcard $(CanTrcv_1_T03_OUTPUT_PATH)/src/CanTrcv_1_T03_PBcfg.c)

ifneq ($(strip $(CanTrcv_1_T03_pbconfig_FILES)),)
LIBRARIES_PBCFG_TO_BUILD += CanTrcv_1_T03_pbconfig
LIBRARIES_TO_BUILD += CanTrcv_1_T03_pbconfig
endif


CPP_FILES_TO_BUILD      +=
ASM_FILES_TO_BUILD      +=


MAKE_CLEAN_RULES        +=
MAKE_GENERATE_RULES     +=
MAKE_COMPILE_RULES      +=
#MAKE_DEBUG_RULES       +=
MAKE_CONFIG_RULES       +=
#MAKE_ADD_RULES         +=



#################################################################
# DEPENDENCIES (only for assembler files)
#

#################################################################
# RULES
