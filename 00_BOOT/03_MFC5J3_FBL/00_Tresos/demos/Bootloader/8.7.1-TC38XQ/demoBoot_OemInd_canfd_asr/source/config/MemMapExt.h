#if 0 /* to be able to use #elif for every module */

#elif (defined MCU_START_SEC_RRAM_VAR_8)
    #undef MCU_START_SEC_RRAM_VAR_8
    #undef MEMMAP_ERROR
#elif (defined MCU_STOP_SEC_RRAM_VAR_8)
    #undef MCU_STOP_SEC_RRAM_VAR_8
    #undef MEMMAP_ERROR
#elif (defined MCU_START_SEC_RRAM_VAR_8)
    #undef MCU_START_SEC_RRAM_VAR_8
    #undef MEMMAP_ERROR
#elif (defined MCU_STOP_SEC_RRAM_VAR_8)
    #undef MCU_STOP_SEC_RRAM_VAR_8
    #undef MEMMAP_ERROR
#elif (defined PORT_START_SEC_CONFIG_CONST_UNSPECIFIED)
    #undef PORT_START_SEC_CONFIG_CONST_UNSPECIFIED
    #undef MEMMAP_ERROR
#elif (defined PORT_STOP_SEC_CONFIG_CONST_UNSPECIFIED)
    #undef PORT_STOP_SEC_CONFIG_CONST_UNSPECIFIED
    #undef MEMMAP_ERROR
#elif defined (DEMO_CAL_START_SEC_CONST_8)
   #undef      DEMO_CAL_START_SEC_CONST_8
    #if(PLATFORMS_TOOLCHAIN == PLATFORMS_multi)
       #pragma ghs section rodata=".Demo_Comp"
     #endif
   #undef MEMMAP_ERROR

#elif (defined DEMO_CAL_STOP_SEC_CONST_8)
   #undef      DEMO_CAL_STOP_SEC_CONST_8
     #if(PLATFORMS_TOOLCHAIN == PLATFORMS_multi)
       #pragma ghs section
     #endif
   #undef MEMMAP_ERROR

#endif
