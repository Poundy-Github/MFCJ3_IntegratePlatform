

#include Merged_Makefile.mak from TARGET and TARGET\DERIVATE
-include $(PROJECT_ROOT)\util\$(TARGET)\Merged_Makefile.mak
-include $(PROJECT_ROOT)\util\$(TARGET)\$(DERIVATE)\Merged_Makefile.mak

PREPROCESSOR_DEFINES += production_disclaimer
production_disclaimer_KEY := I_KNOW_THAT_THIS_CODE_IS_NOT_FOR_PRODUCTION
production_disclaimer_VALUE := 1

PREPROCESSOR_DEFINES+=compilercfg_extension_file
compilercfg_extension_file_KEY=COMPILERCFG_EXTENSION_FILE
compilercfg_extension_file_VALUE=1 
 
PREPROCESSOR_DEFINES+=platform_toolchain
platform_toolchain_KEY=PLATFORMS_TOOLCHAIN
platform_toolchain_VALUE=PLATFORMS_$(TOOLCHAIN)

TRESOS2_NOGEN_PLUGINS +=  MemMap_BL

#override the default BOARD definition
BOARD =TC38XQ_NoOS### from ProjectMode_CommonSettings
# provide variant of Testing plugin for project mode tests
Testing_VARIANT := TS_TxDxM1I0R0

# from \common\Include\Platforms_CommonSettings\util\TC38XQ\Merged_Makefile.mak
# enable Resource plugin in make environment
ENABLED_PLUGINS += Resource


PREPROCESSOR_DEFINES += production_disclaimer
production_disclaimer_KEY := I_KNOW_THAT_THIS_CODE_IS_NOT_FOR_PRODUCTION
production_disclaimer_VALUE := 1

PREPROCESSOR_DEFINES+=platform_toolchain
platform_toolchain_KEY=PLATFORMS_TOOLCHAIN
platform_toolchain_VALUE=PLATFORMS_$(TOOLCHAIN)

TRESOS2_NOGEN_PLUGINS +=  MemMap_BL

PREPROCESSOR_DEFINES+=compilercfg_extension_file
compilercfg_extension_file_KEY=COMPILERCFG_EXTENSION_FILE
compilercfg_extension_file_VALUE=1 

#override the default BOARD definition 
BOARD = TC38XQ_NoOS
 ### from ProjectMode_CommonSettings
# provide variant of Testing plugin for project mode tests
Testing_VARIANT := TS_TxDxM1I0R0
#################################################################
#
# ATOMICS_USE_GENERIC_IMPL
# Since, no OS is available when this dirMerge module ('Base_NoOs_Common') is
# included, the Atomics module must use its generic implementation to depend
# only on the API as defined by AUTOSAR. This means, the dirMerge module
# 'Os_Stub' must be included as well, but that's already the case in the
# dirMerge module 'Base_NoOs'.
ATOMICS_USE_GENERIC_IMPL = 1

# ATOMICS_USER_MULTICORE_CASE
# Assume the single-core case, because the dirMerge module 'Os_stub'
# doesn't offer multi-core functionality.
PREPROCESSOR_DEFINES += TS_ATOMICS_USER_MULTICORE_CASE
TS_ATOMICS_USER_MULTICORE_CASE_KEY = ATOMICS_USER_MULTICORE_CASE
TS_ATOMICS_USER_MULTICORE_CASE_VALUE = 0

#################################################################
# CC_INCLUDE_PATH, CPP_INCLUDE_PATH and ASM_INCLUDE_PATH:
# The paths to own user include files. The paths must be preceded
# by no option . If more than one path is used, you will have
# to separate them by spaces.
#
USER_INCLUDE_PATH  += $(PROJECT_ROOT)\source\config \
                      $(PROJECT_ROOT)\source\config\$(TARGET) \
                      $(PROJECT_ROOT)\source\config\$(TARGET)\$(DERIVATE)

#################################################################
# handling of Compiler and Atomics plugin
# enable as plugins are mandatory
ENABLED_PLUGINS += Compiler Atomics
# but do not generate code
TRESOS2_NOGEN_PLUGINS += Compiler Atomics

TRESOS2_AUTOCONFIGURE_TARGETS :=

PREPROCESSOR_DEFINES += board_isr_can0
board_isr_can0_KEY := BOARD_ISR_CAN0
board_isr_can0_VALUE := 1

PREPROCESSOR_DEFINES += board_isr_stmtimer
board_isr_stmtimer_KEY := BOARD_ISR_STMTIMER
board_isr_stmtimer_VALUE := 0

PREPROCESSOR_DEFINES += autosar_os_not_used
autosar_os_not_used_KEY := AUTOSAR_OS_NOT_USED
autosar_os_not_used_VALUE := 1

PREPROCESSOR_DEFINES += use_sw_vector_mode
use_sw_vector_mode_KEY := USE_SW_VECTOR_MODE
use_sw_vector_mode_VALUE := 1

PREPROCESSOR_DEFINES += autosar_can_interrupt
autosar_can_interrupt_KEY := AUTOSAR_CAN_INTERRUPT
autosar_can_interrupt_VALUE := 1

PREPROCESSOR_DEFINES += Pdur_provide_adjacent_module_vendor_symbolic_names
Pdur_provide_adjacent_module_vendor_symbolic_names_KEY := PDUR_PROVIDE_ADJACENT_MODULE_VENDOR_SYMBOLIC_NAMES
Pdur_provide_adjacent_module_vendor_symbolic_names_VALUE := 1
