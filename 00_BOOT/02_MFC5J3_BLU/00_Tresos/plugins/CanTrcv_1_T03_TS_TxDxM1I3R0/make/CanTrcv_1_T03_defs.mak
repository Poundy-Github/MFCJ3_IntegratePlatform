#EB_Automotive_Makefile

#################################################################
# DEFINITIONS


CanTrcv_1_T03_CORE_PATH      ?= $(PLUGINS_BASE)\CanTrcv_1_T03_$(CanTrcv_1_T03_VARIANT)
CanTrcv_1_T03_OUTPUT_PATH    ?= $(AUTOSAR_BASE_OUTPUT_PATH)



CanTrcv_1_T03_GEN_FILES      = \
                    $(CanTrcv_1_T03_OUTPUT_PATH)\src\CanTrcv_1_T03_Lcfg.c                    \
                    $(CanTrcv_1_T03_OUTPUT_PATH)\src\CanTrcv_1_T03_PBcfg.c                   \
                    $(CanTrcv_1_T03_OUTPUT_PATH)\include\CanTrcv_1_T03_Cfg.h                 \
                    $(CanTrcv_1_T03_OUTPUT_PATH)\include\CanTrcv_1_T03_Lcfg.h                \
                    $(CanTrcv_1_T03_OUTPUT_PATH)\include\CanTrcv_1_T03_PBcfg.h               \
                    $(CanTrcv_1_T03_OUTPUT_PATH)\include\CanTrcv_1_T03_SymbolicNames_PBcfg.h \
                    $(CanTrcv_1_T03_OUTPUT_PATH)\include\CanTrcv_1_T03_Trace.h               \

TRESOS_GEN_FILES  += $(CanTrcv_1_T03_GEN_FILES)



#################################################################
# REGISTRY

CanTrcv_1_T03_DEPENDENT_PLUGINS = base_make tresos
CanTrcv_1_T03_VERSION           = 1.00.00
CanTrcv_1_T03_DESCRIPTION       = CanTrcv Basic Software Makefile PlugIn for Autosar


CC_INCLUDE_PATH      += \
    $(CanTrcv_1_T03_CORE_PATH)\include                          \
    $(CanTrcv_1_T03_CORE_PATH)\src                              \



ASM_INCLUDE_PATH     +=