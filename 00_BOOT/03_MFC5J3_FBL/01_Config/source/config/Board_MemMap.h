/**
 * \file
 *
 * \brief AUTOSAR Board_MemMap
 *
 * This file contains the implementation of the AUTOSAR
 * module Demo_GM.
 *
 * \author Elektrobit Automotive GmbH, 91058 Erlangen, Germany
 *
 * Copyright 2005 - 2017 Elektrobit Automotive GmbH
 * All rights exclusively reserved for Elektrobit Automotive GmbH,
 * unless expressly agreed to otherwise.
 */

/*
 *  MISRA deviation report:
 *  - This file violates MISRA-C:2004, Rule 19.6:
 *       "#undef shall not be used"
 *    Reason:
 *       The specification document explicitely describes this mechanism.
 *  - This file violates MISRA-C:2004, Rule 19.15:
 *       "Precautions shall be taken in order to prevent the contents
 *        of a header file being included twice."
 *    Reason:
 *       This file needs to be included more than once in a compilation unit
 */
/* CHECK: NOPARSE */

/*  MISRA-C:2004 Deviation List
 *
 *  MISRA-1) Deviated Rule: 3.4 (required)
 *   "All uses of the #pragma directive shall be documented and explained."
 *
 *   Reason:
 *   lib.
 *
 */

/* Deviation MISRA-1 <START> */
#if 0 /* to be able to use #elif for every module */
/*------------------[Start of a module]--------------------------------------*/

#elif (defined BOARD_START_STACK_CODE)
  #undef BOARD_START_STACK_CODE
    #if (PLATFORMS_TOOLCHAIN == PLATFORMS_tasking)
      #pragma section farbss "stack"
    #elif (PLATFORMS_TOOLCHAIN == PLATFORMS_gnu)
      __attribute__((section(".stack")))
    #elif (PLATFORMS_TOOLCHAIN == PLATFORMS_multi)
      #pragma ghs section bss=".stack"
    #elif (PLATFORMS_TOOLCHAIN == PLATFORMS_dcc)
      #pragma section DATA "" ".int_ram_stack"
    #endif
  #undef MEMMAP_ERROR

#elif (defined BOARD_STOP_STACK_CODE)
  #undef BOARD_STOP_STACK_CODE
    #if (PLATFORMS_TOOLCHAIN == PLATFORMS_tasking)
      #pragma section farbss restore
    #elif (PLATFORMS_TOOLCHAIN == PLATFORMS_gnu)
    #elif (PLATFORMS_TOOLCHAIN == PLATFORMS_multi)
      #pragma ghs section bss=default
    #elif (PLATFORMS_TOOLCHAIN == PLATFORMS_dcc)
      #pragma section DATA
    #endif
  #undef MEMMAP_ERROR

#elif (defined BOARD_START_SEC_VAR_NO_INIT)
   #undef      BOARD_START_SEC_VAR_NO_INIT
    #if (PLATFORMS_TOOLCHAIN == PLATFORMS_tasking)
     #if (TS_ARCH_DERIVATE == TS_XC2268)
        #pragma section section_noinit
      #else
        #pragma section farbss "section_noinit"
      #endif
    #elif (PLATFORMS_TOOLCHAIN == PLATFORMS_ccs)
     #pragma DATA_SECTION(ubRamNoInit,"section_noinit")
    #elif (PLATFORMS_TOOLCHAIN == PLATFORMS_softune)
      #pragma segment DATA=section_noinit
    #elif (PLATFORMS_TOOLCHAIN == PLATFORMS_ticgt)
     #pragma DATA_SECTION(ubRamNoInit,"section_noinit")
    #elif (PLATFORMS_TOOLCHAIN == PLATFORMS_gnu)
      __attribute__((section(".section_noinit")))
    #elif (PLATFORMS_TOOLCHAIN == PLATFORMS_multi)
      #if (defined BOARD_V850ESFX3)
        #pragma ghs section sbss=".section_noinit"
      #else
        #pragma ghs startdata
        #pragma ghs section bss=".section_noinit"
      #endif
    #elif (PLATFORMS_TOOLCHAIN == PLATFORMS_csp)
      #if (defined BOARD_RL78F1X_GFEGSM)
        #pragma section bss .section_noinit
      #else
        #pragma section .section_noinit
      #endif
    #elif (PLATFORMS_TOOLCHAIN == PLATFORMS_dcc)
      #pragma section DATA ".noinit" ".noinit" RW
      #pragma use_section DATA
    #elif (PLATFORMS_TOOLCHAIN == PLATFORMS_iar)
      #pragma object_attribute=__no_init
    #elif (PLATFORMS_TOOLCHAIN == PLATFORMS_mwerks)
      #if (TS_ARCH_FAMILY == TS_S12X)
        #pragma DATA_SEG __DPAGE_SEG .noinit
      #elif (TS_ARCH_FAMILY == TS_S12Z)
        #pragma DATA_SEG noinit
      #else
        #pragma push
        #pragma section ".noinit" ".noinitbss"
        __declspec (section ".noinit")        
      #endif
	#elif (PLATFORMS_TOOLCHAIN == PLATFORMS_cosmic)
	  #pragma section [noinit]	
    #endif
   #undef MEMMAP_ERROR
#elif (defined BOARD_STOP_SEC_VAR_NO_INIT)
   #undef      BOARD_STOP_SEC_VAR_NO_INIT
    #if (PLATFORMS_TOOLCHAIN == PLATFORMS_tasking)
      #if (TS_ARCH_FAMILY != TS_XC2000)
        #pragma section farbss restore
      #else
        #pragma endsection
      #endif
    #elif (PLATFORMS_TOOLCHAIN == PLATFORMS_ccs)

    #elif (PLATFORMS_TOOLCHAIN == PLATFORMS_gnu)
    #elif (PLATFORMS_TOOLCHAIN == PLATFORMS_multi)
		#if (defined BOARD_V850ESFX3)
		  #pragma ghs section sbss=default
		#else
          #pragma ghs section bss=default
          #pragma ghs enddata
		#endif
    #elif (PLATFORMS_TOOLCHAIN == PLATFORMS_csp)
		#if (defined BOARD_RL78F1X_GFEGSM)
		  #pragma section
		#else
		  #pragma section default
		#endif
    #elif (PLATFORMS_TOOLCHAIN == PLATFORMS_dcc)
      #pragma section DATA ".data"
    #elif (PLATFORMS_TOOLCHAIN == PLATFORMS_softune)
      #pragma segment DATA=DATA
    #elif (PLATFORMS_TOOLCHAIN == PLATFORMS_iar)
    #elif (PLATFORMS_TOOLCHAIN == PLATFORMS_mwerks)
      #if (TS_ARCH_FAMILY == TS_S12X)
		#pragma DATA_SEG DEFAULT
      #elif (TS_ARCH_FAMILY == TS_S12Z)
		#pragma DATA_SEG DEFAULT
      #else
        #pragma pop
      #endif
	#elif (PLATFORMS_TOOLCHAIN == PLATFORMS_cosmic)
	  #pragma section []
    #endif
   #undef MEMMAP_ERROR

#endif

/* Deviation MISRA-1 <STOP> */

