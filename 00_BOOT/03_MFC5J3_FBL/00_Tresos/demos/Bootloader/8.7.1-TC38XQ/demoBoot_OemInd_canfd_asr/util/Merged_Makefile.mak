

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

ATOMICS_USE_GENERIC_IMPL = 1 

PREPROCESSOR_DEFINES += TS_ATOMICS_USER_MULTICORE_CASE
TS_ATOMICS_USER_MULTICORE_CASE_KEY = ATOMICS_USER_MULTICORE_CASE
TS_ATOMICS_USER_MULTICORE_CASE_VALUE = 0

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


PREPROCESSOR_DEFINES += Pdur_provide_adjacent_module_vendor_symbolic_names
Pdur_provide_adjacent_module_vendor_symbolic_names_KEY := PDUR_PROVIDE_ADJACENT_MODULE_VENDOR_SYMBOLIC_NAMES
Pdur_provide_adjacent_module_vendor_symbolic_names_VALUE := 1

#override the default BOARD definition
BOARD =TC38XQ_NoOS### from ProjectMode_CommonSettings
#BOARD =TriboardTC38XQ### from ProjectMode_CommonSettings
# provide variant of Testing plugin for project mode tests
Testing_VARIANT := TS_TxDxM1I0R0
