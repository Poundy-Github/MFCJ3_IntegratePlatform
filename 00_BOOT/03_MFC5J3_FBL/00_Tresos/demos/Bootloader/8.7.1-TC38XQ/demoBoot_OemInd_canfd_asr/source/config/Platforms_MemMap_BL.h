/**
 * \file
 *
 * \brief AUTOSAR Demo_GM
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

#include "Platforms_defs.h"


/* Deviation MISRA-1 <START> */
#if 0 /* to be able to use #elif for every module */
/*------------------[Start of a module]--------------------------------------*/


#elif (defined CAN_17_MCANP_START_SEC_VAR_INIT_8BIT)
  #undef CAN_17_MCANP_START_SEC_VAR_INIT_8BIT
  #undef MEMMAP_ERROR

#elif (defined CAN_17_MCANP_STOP_SEC_VAR_INIT_8BIT)
  #undef CAN_17_MCANP_STOP_SEC_VAR_INIT_8BIT
  #undef MEMMAP_ERROR


#elif (defined MCAL_WDGLIB_START_SEC_CONST_32BIT)
  #undef MCAL_WDGLIB_START_SEC_CONST_32BIT
  #undef MEMMAP_ERROR

#elif (defined MCAL_WDGLIB_STOP_SEC_CONST_32BIT)
  #undef MCAL_WDGLIB_STOP_SEC_CONST_32BIT
  #undef MEMMAP_ERROR


#elif (defined MCAL_WDGLIB_START_SEC_VAR_32BIT)
  #undef MCAL_WDGLIB_START_SEC_VAR_32BIT
  #undef MEMMAP_ERROR

#elif (defined MCAL_WDGLIB_STOP_SEC_VAR_32BIT)
  #undef MCAL_WDGLIB_STOP_SEC_VAR_32BIT
  #undef MEMMAP_ERROR


#elif (defined MCAL_TCLIB_START_SEC_CONST_32BIT)
  #undef MCAL_TCLIB_START_SEC_CONST_32BIT
  #undef MEMMAP_ERROR

#elif (defined MCAL_TCLIB_STOP_SEC_CONST_32BIT)
  #undef MCAL_TCLIB_STOP_SEC_CONST_32BIT
  #undef MEMMAP_ERROR

#elif (defined MCAL_WDGLIB_START_SEC_VAR_INIT_32BIT)
  #undef MCAL_WDGLIB_START_SEC_VAR_INIT_32BIT
  #undef MEMMAP_ERROR

#elif (defined MCAL_WDGLIB_STOP_SEC_VAR_INIT_32BIT)
  #undef MCAL_WDGLIB_STOP_SEC_VAR_INIT_32BIT
  #undef MEMMAP_ERROR

#elif (defined MCAL_TCLIB_START_SEC_VAR_INIT_32BIT)
  #undef MCAL_TCLIB_START_SEC_VAR_INIT_32BIT
  #undef MEMMAP_ERROR

#elif (defined MCAL_TCLIB_STOP_SEC_VAR_INIT_32BIT)
  #undef MCAL_TCLIB_STOP_SEC_VAR_INIT_32BIT
  #undef MEMMAP_ERROR


#elif (defined MCAL_DMALIB_START_SEC_CODE)
  #undef MCAL_DMALIB_START_SEC_CODE
  #undef MEMMAP_ERROR

#elif (defined MCAL_DMALIB_STOP_SEC_CODE)
  #undef MCAL_DMALIB_STOP_SEC_CODE
  #undef MEMMAP_ERROR


#elif (defined RTE_START_SEC_CODE)
  #undef RTE_START_SEC_CODE
  #undef MEMMAP_ERROR

#elif (defined RTE_STOP_SEC_CODE)
  #undef RTE_STOP_SEC_CODE
  #undef MEMMAP_ERROR
  

#elif (defined SCHM_START_SEC_CODE)
  #undef SCHM_START_SEC_CODE
  #undef MEMMAP_ERROR

#elif (defined SCHM_STOP_SEC_CODE)
  #undef SCHM_STOP_SEC_CODE
  #undef MEMMAP_ERROR

#elif (defined SCHM_START_SEC_VAR_UNSPECIFIED)
  #undef SCHM_START_SEC_VAR_UNSPECIFIED
  #undef MEMMAP_ERROR

#elif (defined SCHM_STOP_SEC_VAR_UNSPECIFIED)
  #undef SCHM_STOP_SEC_VAR_UNSPECIFIED
  #undef MEMMAP_ERROR


#elif defined (PROG_START_SEC_VAR_RAM_NO_INIT)
   #undef      PROG_START_SEC_VAR_RAM_NO_INIT
     #if (PLATFORMS_TOOLCHAIN == PLATFORMS_tasking)
     #if (TS_ARCH_DERIVATE == TS_XC2268)
        #pragma section ram_no_init
       #else
        #pragma section farbss ".ram_no_init"
       #endif
     #elif (PLATFORMS_TOOLCHAIN == PLATFORMS_gnu)
      __attribute__((section(".ram_no_init")))
     #elif (PLATFORMS_TOOLCHAIN == PLATFORMS_multi)
       #pragma ghs section bss=".ram_no_init"
     #elif (PLATFORMS_TOOLCHAIN == PLATFORMS_dcc)
      #pragma section DATA "" ".ram_no_init"
     #endif
   #undef MEMMAP_ERROR

   #elif defined (PROG_STOP_SEC_VAR_RAM_NO_INIT)
   #undef      PROG_STOP_SEC_VAR_RAM_NO_INIT
     #if (PLATFORMS_TOOLCHAIN == PLATFORMS_tasking)
     #if (TS_ARCH_DERIVATE == TS_XC2268)
        #pragma endsection
       #else
        #pragma section farbss restore
       #endif

     #elif (PLATFORMS_TOOLCHAIN == PLATFORMS_gnu)
     #elif (PLATFORMS_TOOLCHAIN == PLATFORMS_multi)
       #pragma ghs section
     #elif (PLATFORMS_TOOLCHAIN == PLATFORMS_dcc)
		#pragma section DATA "" ""
     #endif
   #undef MEMMAP_ERROR
   
   
#elif defined (MCAL_TCLIB_START_SEC_CODE)
   #undef      MCAL_TCLIB_START_SEC_CODE
   #undef MEMMAP_ERROR
#elif defined (MCAL_TCLIB_STOP_SEC_CODE)
   #undef      MCAL_TCLIB_STOP_SEC_CODE
   #undef MEMMAP_ERROR
   
#elif defined (MCAL_WDGLIB_START_SEC_CODE)
   #undef      MCAL_WDGLIB_START_SEC_CODE
   #undef MEMMAP_ERROR
#elif defined (MCAL_WDGLIB_STOP_SEC_CODE)
   #undef      MCAL_WDGLIB_STOP_SEC_CODE
   #undef MEMMAP_ERROR
  
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

#elif (defined APP_START_SEC_VAR_NO_INIT_BOOT_STATUS)
   #undef      APP_START_SEC_VAR_NO_INIT_BOOT_STATUS
     #if (PLATFORMS_TOOLCHAIN == PLATFORMS_tasking)
       #pragma section farbss ".section_bootstatus"
     #elif (PLATFORMS_TOOLCHAIN == PLATFORMS_gnu)
      __attribute__((section(".section_bootstatus")))
     #elif (PLATFORMS_TOOLCHAIN == PLATFORMS_multi)
       #pragma ghs section bss=".section_bootstatus"
   #elif (PLATFORMS_TOOLCHAIN == PLATFORMS_dcc)
    #pragma section BSS ".section_bootstatus"
     #endif
   #undef MEMMAP_ERROR
#elif (defined APP_STOP_SEC_VAR_NO_INIT_BOOT_STATUS)
   #undef      APP_STOP_SEC_VAR_NO_INIT_BOOT_STATUS
     #if (PLATFORMS_TOOLCHAIN == PLATFORMS_tasking)
       #pragma section farbss restore
     #elif (PLATFORMS_TOOLCHAIN == PLATFORMS_gnu)
     #elif (PLATFORMS_TOOLCHAIN == PLATFORMS_multi)
       #pragma ghs section
     #elif (PLATFORMS_TOOLCHAIN == PLATFORMS_dcc)
        #pragma section BSS
     #endif
   #undef MEMMAP_ERROR

/*  Used for flash driver start */
#elif (defined FLASH_FLS_START_SEC_CODE)
   #undef      FLASH_FLS_START_SEC_CODE
    #if (PLATFORMS_TOOLCHAIN == PLATFORMS_dcc)
     #pragma section CODE ".fls_driver"
    #elif (PLATFORMS_TOOLCHAIN == PLATFORMS_multi)
     #pragma ghs section text = ".fls_driver" 
    #elif (PLATFORMS_TOOLCHAIN == PLATFORMS_gnu)
      __attribute__((section(".fls_driver")))
    #elif (PLATFORMS_TOOLCHAIN == PLATFORMS_softune)
      #pragma segment FAR_CODE=RAMCODE
      #pragma segment CODE=RAMCODE
    #elif (PLATFORMS_TOOLCHAIN == PLATFORMS_mwerks)
      #if (TS_ARCH_FAMILY == TS_S12X)
		#pragma CODE_SEG fls_driver
	  #elif (TS_ARCH_FAMILY == TS_S12Z)
	    #pragma CODE_SEG fls_driver
      #else
        #pragma push
        #pragma section code_type ".fls_driver"
      #endif
	#elif (PLATFORMS_TOOLCHAIN == PLATFORMS_cosmic)
	  #pragma section (fls_driver)
    #elif (PLATFORMS_TOOLCHAIN == PLATFORMS_ccs)
      #ifdef FLASH_FLS_RAM_FUNC
        #pragma CODE_SECTION(FLASH_FLS_RAM_FUNC,"ramfuncs")
      #endif
      #ifdef FLASH_OPERATION_CBK
        #pragma CODE_SECTION(FLASH_OPERATION_CBK,"ramfuncs")
      #endif
    #elif (PLATFORMS_TOOLCHAIN == PLATFORMS_ticgt)
     #ifdef FLASH_FLS_RAM_TMS320F28035_FUNC
       #pragma CODE_SECTION(FLASH_FLS_RAM_TMS320F28035_FUNC,"ramfuncs")
     #endif
     #ifdef FLASH_OPERATION_CBK
       #pragma CODE_SECTION(FLASH_OPERATION_CBK,"ramfuncs");
     #endif
    #elif (PLATFORMS_TOOLCHAIN == PLATFORMS_tasking)
       #if (TS_ARCH_DERIVATE == TS_XC2268)
           #pragma section code=DRV_FLS_WRITE_SEC
        #else

        #endif
    #endif
   #undef MEMMAP_ERROR
#elif (defined FLASH_FLS_STOP_SEC_CODE)
   #undef      FLASH_FLS_STOP_SEC_CODE
    #if (PLATFORMS_TOOLCHAIN == PLATFORMS_dcc)
     #pragma section CODE
    #elif (PLATFORMS_TOOLCHAIN == PLATFORMS_multi)
     #pragma ghs section text = default
    #elif (PLATFORMS_TOOLCHAIN == PLATFORMS_gnu)
    #elif (PLATFORMS_TOOLCHAIN == PLATFORMS_softune)
      #pragma segment FAR_CODE
      #pragma segment CODE
    #elif (PLATFORMS_TOOLCHAIN == PLATFORMS_mwerks)
      #if (TS_ARCH_FAMILY == TS_S12X)
		#pragma CODE_SEG DEFAULT
	  #elif (TS_ARCH_FAMILY == TS_S12Z)
		#pragma CODE_SEG DEFAULT
      #else
        #pragma pop
      #endif
	#elif (PLATFORMS_TOOLCHAIN == PLATFORMS_cosmic)
	  #pragma section ()
    #elif (PLATFORMS_TOOLCHAIN == PLATFORMS_tasking)
       #if (TS_ARCH_DERIVATE == TS_XC2268)
          #pragma endsection
        #else

        #endif
    #endif
   #undef MEMMAP_ERROR

#elif (defined FLASH_FLS_START_SEC_CONST)
   #undef      FLASH_FLS_START_SEC_CONST
    #if (PLATFORMS_TOOLCHAIN == PLATFORMS_dcc)
     #pragma section CONST ".fls_driver"
    #elif (PLATFORMS_TOOLCHAIN == PLATFORMS_gnu)
      __attribute__((section(".fls_driver")))
    #elif (PLATFORMS_TOOLCHAIN == PLATFORMS_multi)
     #pragma ghs section rodata = ".fls_driver"
    #elif (PLATFORMS_TOOLCHAIN == PLATFORMS_mwerks)
    #pragma push
    #pragma section const_type ".fls_driver"
    #endif
   #undef MEMMAP_ERROR
#elif (defined FLASH_FLS_STOP_SEC_CONST)
   #undef      FLASH_FLS_STOP_SEC_CONST
    #if (PLATFORMS_TOOLCHAIN == PLATFORMS_dcc)
     #pragma section CODE
    #elif (PLATFORMS_TOOLCHAIN == PLATFORMS_gnu)
    #elif (PLATFORMS_TOOLCHAIN == PLATFORMS_multi)
     #pragma ghs section rodata = default
    #elif (PLATFORMS_TOOLCHAIN == PLATFORMS_mwerks)
     #pragma pop
    #endif
   #undef MEMMAP_ERROR

/*  Used for flash driver end */

/*  Used for RH850 code needed to copy to RAM */
#elif (defined FLASH_START_R_FCL_CODE_USR)
   #undef      FLASH_START_R_FCL_CODE_USR
    #if (PLATFORMS_TOOLCHAIN == PLATFORMS_multi)
    #pragma ghs section text = ".R_FCL_CODE_USR"
    #elif (PLATFORMS_TOOLCHAIN == PLATFORMS_csp)
     #pragma section text "R_FCL_CODE_USR"
    #endif
   #undef MEMMAP_ERROR
#elif (defined FLASH_STOP_R_FCL_CODE_USR)
   #undef      FLASH_STOP_R_FCL_CODE_USR
    #if (PLATFORMS_TOOLCHAIN == PLATFORMS_multi)
    #pragma ghs section text = default
    #elif (PLATFORMS_TOOLCHAIN == PLATFORMS_csp)
     #pragma section default
    #endif
   #undef MEMMAP_ERROR

/* Start of History Record */
#elif (defined FLASH_START_RAM_CODE_USR )
   #undef      FLASH_START_RAM_CODE_USR 
    #if (PLATFORMS_TOOLCHAIN == PLATFORMS_dcc)
     #pragma section DATA ".data"
    #elif (PLATFORMS_TOOLCHAIN == PLATFORMS_multi)
     #pragma ghs section data = ".data"
    #elif (PLATFORMS_TOOLCHAIN == PLATFORMS_mwerks)
     #pragma section ".myCodeInRAM"
     __declspec(section ".myCodeInRAM")
    #endif
   #undef MEMMAP_ERROR
#elif (defined FLASH_STOP_RAM_CODE_USR )
   #undef      FLASH_STOP_RAM_CODE_USR 
    #if (PLATFORMS_TOOLCHAIN == PLATFORMS_dcc)
     #pragma section DATA
    #elif (PLATFORMS_TOOLCHAIN == PLATFORMS_multi)
     #pragma ghs section data = default
    #elif (PLATFORMS_TOOLCHAIN == PLATFORMS_mwerks)
     /* nothing to do */
    #endif
   #undef MEMMAP_ERROR
/* End of History Record */

/* Start of History Record */
#elif (defined PROG_START_HISTORY_RECORD_SEC_CONST_8 )
   #undef      PROG_START_HISTORY_RECORD_SEC_CONST_8 
    #if (PLATFORMS_TOOLCHAIN == PLATFORMS_dcc)
     #pragma section CONST ".history_record"
    #elif (PLATFORMS_TOOLCHAIN == PLATFORMS_multi)
     #pragma ghs section rodata = ".history_record"
    #endif
   #undef MEMMAP_ERROR
#elif (defined PROG_STOP_HISTORY_RECORD_SEC_CONST_8 )
   #undef      PROG_STOP_HISTORY_RECORD_SEC_CONST_8 
    #if (PLATFORMS_TOOLCHAIN == PLATFORMS_dcc)
     #pragma section CONST
    #elif (PLATFORMS_TOOLCHAIN == PLATFORMS_multi)
     #pragma ghs section rodata = default
    #endif
   #undef MEMMAP_ERROR
/* End of History Record */

/*------------------[Start of a module]--------------------------------------*/
#elif (defined APP_COMPSTART_START_SEC_CONST_8)
  #undef APP_COMPSTART_START_SEC_CONST_8
    #if (PLATFORMS_TOOLCHAIN == PLATFORMS_tasking)
      #pragma section farrom "CompStart"
      #pragma protect
    #elif (PLATFORMS_TOOLCHAIN == PLATFORMS_gnu)
      __attribute__((section(".CompStart")))
    #elif (PLATFORMS_TOOLCHAIN == PLATFORMS_multi)
      #pragma ghs section rodata=".CompStart"
     #elif (PLATFORMS_TOOLCHAIN == PLATFORMS_dcc)
        #pragma section RODATA ".CompStart"
    #endif
  #undef MEMMAP_ERROR

#elif (defined APP_COMPSTART_STOP_SEC_CONST_8)
  #undef APP_COMPSTART_STOP_SEC_CONST_8
    #if (PLATFORMS_TOOLCHAIN == PLATFORMS_tasking)
      #pragma section farrom restore
      #pragma endprotect
    #elif (PLATFORMS_TOOLCHAIN == PLATFORMS_gnu)
    #elif (PLATFORMS_TOOLCHAIN == PLATFORMS_multi)
      #pragma ghs section rodata=default
     #elif (PLATFORMS_TOOLCHAIN == PLATFORMS_dcc)
      #pragma section RODATA
    #endif
  #undef MEMMAP_ERROR

#elif (defined APP_COMPADDRSTART_START_SEC_CONST_8)
  #undef APP_COMPADDRSTART_START_SEC_CONST_8
    #if (PLATFORMS_TOOLCHAIN == PLATFORMS_tasking)
      #pragma section farrom "CompAddrStart"
      #pragma protect
    #elif (PLATFORMS_TOOLCHAIN == PLATFORMS_gnu)  
      __attribute__((section(".CompAddrStart")))
    #elif (PLATFORMS_TOOLCHAIN == PLATFORMS_multi)
      #pragma ghs section rodata=".CompAddrStart"
     #elif (PLATFORMS_TOOLCHAIN == PLATFORMS_dcc)
        #pragma  section RODATA ".CompAddrStart"
    #endif
  #undef MEMMAP_ERROR

#elif (defined APP_COMPADDRSTART_STOP_SEC_CONST_8)
  #undef APP_COMPADDRSTART_STOP_SEC_CONST_8
    #if (PLATFORMS_TOOLCHAIN == PLATFORMS_tasking)
      #pragma section farrom restore
      #pragma endprotect
    #elif (PLATFORMS_TOOLCHAIN == PLATFORMS_gnu)
    #elif (PLATFORMS_TOOLCHAIN == PLATFORMS_multi)
      #pragma ghs section rodata=default
     #elif (PLATFORMS_TOOLCHAIN == PLATFORMS_dcc)
        #pragma  section RODATA
    #endif
  #undef MEMMAP_ERROR

#elif (defined APP_COMPADDRCOMPSTART_START_SEC_CONST_8)
  #undef APP_COMPADDRCOMPSTART_START_SEC_CONST_8
    #if (PLATFORMS_TOOLCHAIN == PLATFORMS_tasking)
      #pragma section farrom "CompAddCompStart"
      #pragma protect
    #elif (PLATFORMS_TOOLCHAIN == PLATFORMS_gnu)
      __attribute__((section(".CompAddCompStart")))
    #elif (PLATFORMS_TOOLCHAIN == PLATFORMS_multi)
      #pragma ghs section rodata=".CompAddCompStart"
     #elif (PLATFORMS_TOOLCHAIN == PLATFORMS_dcc)
        #pragma section rodata ".CompAddCompStart"
    #endif
  #undef MEMMAP_ERROR

#elif (defined APP_COMPADDRCOMPSTART_STOP_SEC_CONST_8)
  #undef APP_COMPADDRCOMPSTART_STOP_SEC_CONST_8
    #if (PLATFORMS_TOOLCHAIN == PLATFORMS_tasking)
      #pragma section farrom restore
      #pragma endprotect
    #elif (PLATFORMS_TOOLCHAIN == PLATFORMS_gnu)
    #elif (PLATFORMS_TOOLCHAIN == PLATFORMS_multi)
      #pragma ghs section rodata=default
     #elif (PLATFORMS_TOOLCHAIN == PLATFORMS_dcc)
        #pragma RODATA
    #endif
  #undef MEMMAP_ERROR

#elif (defined APP_COMPADDREND_START_SEC_CONST_8)
  #undef APP_COMPADDREND_START_SEC_CONST_8
    #if (PLATFORMS_TOOLCHAIN == PLATFORMS_tasking)
      #pragma section farrom "CompAddrEnd"
      #pragma protect
    #elif (PLATFORMS_TOOLCHAIN == PLATFORMS_gnu)
      __attribute__((section(".CompAddrEnd")))
    #elif (PLATFORMS_TOOLCHAIN == PLATFORMS_multi)
      #pragma ghs section rodata=".CompAddrEnd"

    #elif (PLATFORMS_TOOLCHAIN == PLATFORMS_dcc)
      #pragma section RODATA ".ComAddrEnd"
    #endif
     #undef MEMMAP_ERROR

#elif (defined APP_COMPADDREND_STOP_SEC_CONST_8)
  #undef APP_COMPADDREND_STOP_SEC_CONST_8
    #if (PLATFORMS_TOOLCHAIN == PLATFORMS_tasking)
      #pragma section farrom restore
      #pragma endprotect
    #elif (PLATFORMS_TOOLCHAIN == PLATFORMS_gnu)
    #elif (PLATFORMS_TOOLCHAIN == PLATFORMS_multi)
      #pragma ghs section rodata=default
    #elif (PLATFORMS_TOOLCHAIN == PLATFORMS_dcc)
      #pragma section RODATA
    #endif
  #undef MEMMAP_ERROR

#elif (defined APP_COMPEND_START_SEC_CONST_8)
  #undef APP_COMPEND_START_SEC_CONST_8
    #if (PLATFORMS_TOOLCHAIN == PLATFORMS_tasking)
      #pragma section farrom "CompEnd"
      #pragma protect
    #elif (PLATFORMS_TOOLCHAIN == PLATFORMS_gnu)
      __attribute__((section(".CompEnd")))
    #elif (PLATFORMS_TOOLCHAIN == PLATFORMS_multi)
      #pragma ghs section rodata=".CompEnd"
    #elif (PLATFORMS_TOOLCHAIN == PLATFORMS_dcc)
      #pragma section rodata ".CompEnd"
    #endif
  #undef MEMMAP_ERROR

#elif (defined APP_COMPEND_STOP_SEC_CONST_8)
  #undef APP_COMPEND_STOP_SEC_CONST_8
    #if (PLATFORMS_TOOLCHAIN == PLATFORMS_tasking)
      #pragma section farrom restore
      #pragma endprotect
    #elif (PLATFORMS_TOOLCHAIN == PLATFORMS_gnu)
    #elif (PLATFORMS_TOOLCHAIN == PLATFORMS_multi)
      #pragma ghs section rodata=default
    #elif (PLATFORMS_TOOLCHAIN == PLATFORMS_dcc)
      #pragma section rodata
    #endif

  #undef MEMMAP_ERROR

#elif (defined APP_COMPCONSTTEST_START_SEC_CONST_8)
  #undef APP_COMPCONSTTEST_START_SEC_CONST_8
    #if (PLATFORMS_TOOLCHAIN == PLATFORMS_tasking)
      #pragma section farrom "CompConstTest"
      #pragma protect
    #elif (PLATFORMS_TOOLCHAIN == PLATFORMS_gnu)
      __attribute__((section(".CompConstTest")))
    #elif (PLATFORMS_TOOLCHAIN == PLATFORMS_multi)
      #pragma ghs section rodata=".CompConstTest"
    #elif (PLATFORMS_TOOLCHAIN == PLATFORMS_dcc)
        #pragma section rodata ".CompConstTest"
    #endif

  #undef MEMMAP_ERROR

#elif (defined APP_COMPCONSTTEST_STOP_SEC_CONST_8)
  #undef APP_COMPCONSTTEST_STOP_SEC_CONST_8
    #if (PLATFORMS_TOOLCHAIN == PLATFORMS_tasking)
      #pragma section farrom restore
      #pragma endprotect
    #elif (PLATFORMS_TOOLCHAIN == PLATFORMS_gnu)
    #elif (PLATFORMS_TOOLCHAIN == PLATFORMS_multi)
      #pragma ghs section rodata=default
    #elif (PLATFORMS_TOOLCHAIN == PLATFORMS_dcc)
      #pragma section rodata
    #endif
  #undef MEMMAP_ERROR

#elif (defined APP_COMPCALLOUT_START_SEC_CODE_8)
  #undef APP_COMPCALLOUT_START_SEC_CODE_8
    #if (PLATFORMS_TOOLCHAIN == PLATFORMS_tasking)
      #pragma section code "CompleteCompatibleCallout"
      #pragma protect
    #elif (PLATFORMS_TOOLCHAIN == PLATFORMS_gnu)
      __attribute__((section(".CompleteCompatibleCallout")))
    #elif (PLATFORMS_TOOLCHAIN == PLATFORMS_multi)
      #pragma ghs section text=".CompleteCompatibleCallout"
    #elif (PLATFORMS_TOOLCHAIN == PLATFORMS_dcc)
      #pragma section text ".CompleteCompatibleCallout"
    #endif
  #undef MEMMAP_ERROR

#elif (defined APP_COMPCALLOUT_STOP_SEC_CODE_8)
  #undef APP_COMPCALLOUT_STOP_SEC_CODE_8
    #if (PLATFORMS_TOOLCHAIN == PLATFORMS_tasking)
      #pragma section code restore
      #pragma endprotect
    #elif (PLATFORMS_TOOLCHAIN == PLATFORMS_gnu)
    #elif (PLATFORMS_TOOLCHAIN == PLATFORMS_multi)
      #pragma ghs section text=default
    #elif (PLATFORMS_TOOLCHAIN == PLATFORMS_dcc)
          #pragma section text
    #endif
  #undef MEMMAP_ERROR

/*------------------[Start of a module]--------------------------------------*/
#elif defined (BM_BOOT_CKS_START_SEC_VAR)
    #undef      BM_BOOT_CKS_START_SEC_VAR
    #if (PLATFORMS_TOOLCHAIN == PLATFORMS_tasking)
		#if (TS_ARCH_DERIVATE == TS_XC2268)
          #pragma  section far="Bootchecksum"
	      #pragma  romdata
	      #pragma  protect
        #else
          #pragma  section farrom "Bootchecksum"
          #pragma protect
        #endif
    #elif (PLATFORMS_TOOLCHAIN == PLATFORMS_gnu)
      __attribute__((section(".bootchecksum")))
    #elif (PLATFORMS_TOOLCHAIN == PLATFORMS_multi)
        #pragma ghs section rodata = ".bootchecksum"
    #elif (PLATFORMS_TOOLCHAIN == PLATFORMS_dcc)
    #endif
    #undef MEMMAP_ERROR
#elif defined (BM_BOOT_CKS_STOP_SEC_VAR)
    #undef      BM_BOOT_CKS_STOP_SEC_VAR
    #if (PLATFORMS_TOOLCHAIN == PLATFORMS_tasking)
		#if (TS_ARCH_DERIVATE == TS_XC2268)
		  #pragma endprotect
	      #pragma noromdata
          #pragma endsection
        #else
          #pragma section farrom restore
          #pragma endprotect
        #endif
    #elif (PLATFORMS_TOOLCHAIN == PLATFORMS_gnu)
    #elif (PLATFORMS_TOOLCHAIN == PLATFORMS_multi)
        #pragma ghs section rodata=default
    #elif (PLATFORMS_TOOLCHAIN == PLATFORMS_dcc)
    #endif
    #undef MEMMAP_ERROR
  

/*------------------[Start of a module]--------------------------------------*/
#elif defined (PROG_START_SEC_CODE)
   #undef      PROG_START_SEC_CODE
   #undef MEMMAP_ERROR
#elif defined (PROG_STOP_SEC_CODE)
   #undef      PROG_STOP_SEC_CODE
   #undef MEMMAP_ERROR

#elif defined (PROG_GET_DID_F0F3_START_SEC_CODE)
   #undef      PROG_GET_DID_F0F3_START_SEC_CODE
   #undef MEMMAP_ERROR
#elif defined (PROG_GET_DID_F0F3_STOP_SEC_CODE)
   #undef      PROG_GET_DID_F0F3_STOP_SEC_CODE
   #undef MEMMAP_ERROR

#elif defined (PROG_GET_DID_F0F6_START_SEC_CODE)
   #undef      PROG_GET_DID_F0F6_START_SEC_CODE
   #undef MEMMAP_ERROR
#elif defined (PROG_GET_DID_F0F6_STOP_SEC_CODE)
   #undef      PROG_GET_DID_F0F6_STOP_SEC_CODE
   #undef MEMMAP_ERROR

#elif defined (PROG_START_SEC_VAR_INIT_8)
   #undef      PROG_START_SEC_VAR_INIT_8
   #undef MEMMAP_ERROR
#elif defined (PROG_STOP_SEC_VAR_INIT_8)
   #undef      PROG_STOP_SEC_VAR_INIT_8
   #undef MEMMAP_ERROR

#elif defined (PROG_START_SEC_VAR_NO_INIT_8)
   #undef      PROG_START_SEC_VAR_NO_INIT_8

   #undef MEMMAP_ERROR
#elif defined (PROG_STOP_SEC_VAR_NO_INIT_8)
   #undef      PROG_STOP_SEC_VAR_NO_INIT_8
   #undef MEMMAP_ERROR

#elif defined (PROG_START_SEC_VAR_NO_INIT_UNSPECIFIED)
   #undef      PROG_START_SEC_VAR_NO_INIT_UNSPECIFIED
   #undef MEMMAP_ERROR
#elif defined (PROG_STOP_SEC_VAR_NO_INIT_UNSPECIFIED)
   #undef      PROG_STOP_SEC_VAR_NO_INIT_UNSPECIFIED
   #undef MEMMAP_ERROR

#elif defined (PROG_START_SEC_VAR_RAM_NO_INIT)
   #undef      PROG_START_SEC_VAR_RAM_NO_INIT
     #if (PLATFORMS_TOOLCHAIN == PLATFORMS_tasking)
     #if (TS_ARCH_DERIVATE == TS_XC2268)
        #pragma section ram_no_init
       #else
        #pragma section farbss ".ram_no_init"
       #endif
     #elif (PLATFORMS_TOOLCHAIN == PLATFORMS_gnu)
      __attribute__((section(".ram_no_init")))
     #elif (PLATFORMS_TOOLCHAIN == PLATFORMS_multi)
       #pragma ghs section bss=".ram_no_init"
     #elif (PLATFORMS_TOOLCHAIN == PLATFORMS_dcc)
      #pragma section DATA "" ".ram_no_init"
     #endif
   #undef MEMMAP_ERROR
#elif defined (PROG_STOP_SEC_VAR_RAM_NO_INIT)
   #undef      PROG_STOP_SEC_VAR_RAM_NO_INIT
     #if (PLATFORMS_TOOLCHAIN == PLATFORMS_tasking)
     #if (TS_ARCH_DERIVATE == TS_XC2268)
        #pragma endsection
       #else
        #pragma section farbss restore
       #endif

     #elif (PLATFORMS_TOOLCHAIN == PLATFORMS_gnu)
     #elif (PLATFORMS_TOOLCHAIN == PLATFORMS_multi)
       #pragma ghs section
     #elif (PLATFORMS_TOOLCHAIN == PLATFORMS_dcc)
       #pragma section BSS "" ""
     #endif
   #undef MEMMAP_ERROR

#elif defined (PROG_START_SEC_CONST_UNSPECIFIED)
   #undef      PROG_START_SEC_CONST_UNSPECIFIED
   #undef MEMMAP_ERROR
#elif defined (PROG_STOP_SEC_CONST_UNSPECIFIED)
   #undef      PROG_STOP_SEC_CONST_UNSPECIFIED
   #undef MEMMAP_ERROR

#elif defined (PROG_START_SEC_CONST_8)
   #undef      PROG_START_SEC_CONST_8
   #undef MEMMAP_ERROR
#elif defined (PROG_STOP_SEC_CONST_8)
   #undef      PROG_STOP_SEC_CONST_8
   #undef MEMMAP_ERROR

#elif defined (PROG_SBL_HEADER_START_SEC_CONST_8)
   #undef      PROG_SBL_HEADER_START_SEC_CONST_8
   #undef MEMMAP_ERROR
   #if (PLATFORMS_TOOLCHAIN == PLATFORMS_tasking)
       #pragma section farrom "SBLHeader"
       #pragma protect
     #elif (PLATFORMS_TOOLCHAIN == PLATFORMS_gnu)
      __attribute__((section(".SBLHeader")))
     #elif (PLATFORMS_TOOLCHAIN == PLATFORMS_multi)
       #pragma ghs section rodata=".SBLHeader"
     #elif (PLATFORMS_TOOLCHAIN == PLATFORMS_dcc)
    #pragma section CONST ".SBLHeader"
     #endif
#elif defined (PROG_SBL_HEADER_STOP_SEC_CONST_8)
   #undef      PROG_SBL_HEADER_STOP_SEC_CONST_8
   #undef MEMMAP_ERROR
   #if (PLATFORMS_TOOLCHAIN == PLATFORMS_tasking)
     #pragma  section farrom restore
     #pragma endprotect
     #pragma clear
   #elif (PLATFORMS_TOOLCHAIN == PLATFORMS_gnu)
   #elif (PLATFORMS_TOOLCHAIN == PLATFORMS_multi)
     #pragma ghs section
   #elif (PLATFORMS_TOOLCHAIN == PLATFORMS_dcc)
      #pragma section CONST
   #endif

#elif defined (PROG_SBL_VALIDITY_START_SEC_CONST_8)
   #undef      PROG_SBL_VALIDITY_START_SEC_CONST_8
   #undef MEMMAP_ERROR
   #if (PLATFORMS_TOOLCHAIN == PLATFORMS_tasking)
       #pragma section farrom "SBLValidity"
       #pragma protect
     #elif (PLATFORMS_TOOLCHAIN == PLATFORMS_gnu)
      __attribute__((section(".SBLValidity")))
     #elif (PLATFORMS_TOOLCHAIN == PLATFORMS_multi)
       #pragma ghs section rodata=".SBLValidity"
     #elif (PLATFORMS_TOOLCHAIN == PLATFORMS_dcc)
      #pragma section CONST ".SBLValidity"
     #endif
#elif defined (PROG_SBL_VALIDITY_STOP_SEC_CONST_8)
   #undef      PROG_SBL_VALIDITY_STOP_SEC_CONST_8
   #undef MEMMAP_ERROR
   #if (PLATFORMS_TOOLCHAIN == PLATFORMS_tasking)
     #pragma section farrom restore
     #pragma endprotect
     #pragma clear
   #elif (PLATFORMS_TOOLCHAIN == PLATFORMS_gnu)
   #elif (PLATFORMS_TOOLCHAIN == PLATFORMS_multi)
     #pragma ghs section
   #elif (PLATFORMS_TOOLCHAIN == PLATFORMS_dcc)
    #pragma section CONST
   #endif

#elif defined (PROG_REPROG_FLAG_START_SEC_VAR_NO_INIT_8)
   #undef      PROG_REPROG_FLAG_START_SEC_VAR_NO_INIT_8
     #if (PLATFORMS_TOOLCHAIN == PLATFORMS_tasking)
       #if (TS_ARCH_DERIVATE == TS_XC2268)
           #pragma section far=prog_sig
           #pragma protect
        #else
           #pragma section farbss "prog_sig"
           #pragma protect
        #endif
     #elif (PLATFORMS_TOOLCHAIN == PLATFORMS_gnu)
      __attribute__((section(".prog_sig")))
     #elif (PLATFORMS_TOOLCHAIN == PLATFORMS_multi)
		#if (defined BOARD_V850ESFX3)
		  #pragma ghs section sbss=".prog_sig"
		#else
		  #pragma ghs section bss=".prog_sig"
		#endif
     #elif (PLATFORMS_TOOLCHAIN == PLATFORMS_dcc)
       #pragma section DATA "" ".prog_sig"
     #elif (PLATFORMS_TOOLCHAIN == PLATFORMS_softune)
       #pragma segment DATA=prog_sig

     #elif (PLATFORMS_TOOLCHAIN == PLATFORMS_ccs)
       #pragma DATA_SECTION(m_ulProgSig,".prog_sig")
     #elif (PLATFORMS_TOOLCHAIN == PLATFORMS_ticgt)
       #pragma DATA_SECTION(m_ulProgSig,".prog_sig")
     #elif (PLATFORMS_TOOLCHAIN == PLATFORMS_ticgt)
      #pragma DATA_SECTION(m_ulProgSig,".prog_sig")
     #elif (PLATFORMS_TOOLCHAIN == PLATFORMS_csp)
		#if (defined BOARD_RL78F1X_GFEGSM)
		  #pragma section bss .prog_sig
		#else
		  #pragma section .prog_sig
		#endif
     #elif (PLATFORMS_TOOLCHAIN == PLATFORMS_mwerks)
       #if (TS_ARCH_FAMILY == TS_S12X)
		 #pragma DATA_SEG .prog_sig
       #elif (TS_ARCH_FAMILY == TS_S12Z)
		 #pragma DATA_SEG prog_sig
       #else
         #pragma push
         #pragma section data_type ".prog_sig"
	   #endif
	 #elif (PLATFORMS_TOOLCHAIN == PLATFORMS_cosmic)
	   #pragma section [prog_sig]
     #endif
   #undef MEMMAP_ERROR
#elif defined (PROG_REPROG_FLAG_STOP_SEC_VAR_NO_INIT_8)
   #undef      PROG_REPROG_FLAG_STOP_SEC_VAR_NO_INIT_8
   #undef MEMMAP_ERROR
   #if (PLATFORMS_TOOLCHAIN == PLATFORMS_tasking)
     #if (TS_ARCH_DERIVATE == TS_XC2268)
         #pragma endprotect
         #pragma endsection
      #else
         #pragma section farbss restore
         #pragma endprotect
      #endif
   #elif (PLATFORMS_TOOLCHAIN == PLATFORMS_gnu)
   #elif (PLATFORMS_TOOLCHAIN == PLATFORMS_multi)
     #pragma ghs section
   #elif (PLATFORMS_TOOLCHAIN == PLATFORMS_dcc)
     #pragma section DATA
   #elif (PLATFORMS_TOOLCHAIN == PLATFORMS_softune)
      #pragma segment DATA=DATA
    #elif (PLATFORMS_TOOLCHAIN == PLATFORMS_csp)
		#if (defined BOARD_RL78F1X_GFEGSM)
		  #pragma section
		#else
          #pragma section default
		#endif
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
 #elif defined (PROG_ANTISCANNING_START_SEC_VAR_NO_INIT_8)
#undef      PROG_ANTISCANNING_START_SEC_VAR_NO_INIT_8
  #if (PLATFORMS_TOOLCHAIN == PLATFORMS_tasking)
    #if (TS_ARCH_DERIVATE == TS_XC2268)
        #pragma section far=prog_sig
        #pragma protect
     #else
        #pragma section farbss "prog_antiscanning"
        #pragma protect
     #endif
  #elif (PLATFORMS_TOOLCHAIN == PLATFORMS_gnu)
      __attribute__((section(".prog_antiscanning")))
  #elif (PLATFORMS_TOOLCHAIN == PLATFORMS_multi)
 #if (defined BOARD_V850ESFX3)
   #pragma ghs section sbss=".prog_antiscanning"
 #else
   #pragma ghs section bss=".prog_antiscanning"
 #endif
  #elif (PLATFORMS_TOOLCHAIN == PLATFORMS_dcc)
    #pragma section DATA "" ".prog_antiscanning"
  #elif (PLATFORMS_TOOLCHAIN == PLATFORMS_softune)
    #pragma segment DATA=prog_antiscanning

  #elif (PLATFORMS_TOOLCHAIN == PLATFORMS_ccs)
    #pragma DATA_SECTION(m_ulProgSig,".prog_antiscanning")
  #elif (PLATFORMS_TOOLCHAIN == PLATFORMS_ticgt)
    #pragma DATA_SECTION(m_ulProgSig,".prog_antiscanning")
  #elif (PLATFORMS_TOOLCHAIN == PLATFORMS_ticgt)
    #pragma DATA_SECTION(m_ulProgSig,".prog_antiscanning")
  #elif (PLATFORMS_TOOLCHAIN == PLATFORMS_csp)
  #if (defined BOARD_RL78F1X_GFEGSM)
    #pragma section bss .prog_antiscanning
  #else
    #pragma section .prog_antiscanning
  #endif
  #elif (PLATFORMS_TOOLCHAIN == PLATFORMS_mwerks)
    #if (TS_ARCH_FAMILY == TS_S12X)
	  #pragma DATA_SEG .prog_antiscanning
    #elif (TS_ARCH_FAMILY == TS_S12Z)
	  #pragma DATA_SEG prog_antiscanning
    #else
      #pragma push
      #pragma section data_type ".prog_antiscanning"
    #endif
  #elif (PLATFORMS_TOOLCHAIN == PLATFORMS_cosmic)
    #pragma section [prog_antiscanning]
  #endif
#undef MEMMAP_ERROR
#elif defined (PROG_ANTISCANNING_FLAG_STOP_SEC_VAR_NO_INIT_8)
#undef      PROG_ANTISCANNING_FLAG_STOP_SEC_VAR_NO_INIT_8
#undef MEMMAP_ERROR
#if (PLATFORMS_TOOLCHAIN == PLATFORMS_tasking)
  #if (TS_ARCH_DERIVATE == TS_XC2268)
      #pragma endprotect
      #pragma endsection
   #else
      #pragma section farbss restore
      #pragma endprotect
   #endif
#elif (PLATFORMS_TOOLCHAIN == PLATFORMS_gnu)
#elif (PLATFORMS_TOOLCHAIN == PLATFORMS_multi)
  #pragma ghs section
#elif (PLATFORMS_TOOLCHAIN == PLATFORMS_dcc)
     #pragma section DATA
#elif (PLATFORMS_TOOLCHAIN == PLATFORMS_softune)
   #pragma segment DATA=DATA
#elif (PLATFORMS_TOOLCHAIN == PLATFORMS_csp)
  #if (defined BOARD_RL78F1X_GFEGSM)
    #pragma section
  #else
    #pragma section default
  #endif
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

#elif defined (PROG_TESTER_ADDRESS_FLAG_START_SEC_VAR_NO_INIT_8)
   #undef      PROG_TESTER_ADDRESS_FLAG_START_SEC_VAR_NO_INIT_8
     #if (PLATFORMS_TOOLCHAIN == PLATFORMS_tasking)
       #pragma section farbss "tester_address"
       #pragma protect
     #elif (PLATFORMS_TOOLCHAIN == PLATFORMS_gnu)
      __attribute__((section(".tester_address")))
     #elif (PLATFORMS_TOOLCHAIN == PLATFORMS_multi)
       #pragma ghs section bss=".tester_address"
     #elif (PLATFORMS_TOOLCHAIN == PLATFORMS_dcc)
       #pragma section DATA "" ".tester_address"
     #endif
   #undef MEMMAP_ERROR
#elif defined (PROG_TESTER_ADDRESS_FLAG_STOP_SEC_VAR_NO_INIT_8)
   #undef      PROG_TESTER_ADDRESS_FLAG_STOP_SEC_VAR_NO_INIT_8
   #undef MEMMAP_ERROR
   #if (PLATFORMS_TOOLCHAIN == PLATFORMS_tasking)
     #pragma section farbss restore
     #pragma endprotect
   #elif (PLATFORMS_TOOLCHAIN == PLATFORMS_gnu)
   #elif (PLATFORMS_TOOLCHAIN == PLATFORMS_multi)
     #pragma ghs section
   #elif (PLATFORMS_TOOLCHAIN == PLATFORMS_dcc)
     #pragma section DATA "" ""
   #endif

#elif defined (PROG_ECU_ADDRESS_START_SEC_VAR_NO_INIT_8)
   #undef      PROG_ECU_ADDRESS_START_SEC_VAR_NO_INIT_8
     #if (PLATFORMS_TOOLCHAIN == PLATFORMS_tasking)
       #pragma section farbss "ecu_address"
       #pragma protect
     #elif (PLATFORMS_TOOLCHAIN == PLATFORMS_gnu)
      __attribute__((section(".ecu_address")))
     #elif (PLATFORMS_TOOLCHAIN == PLATFORMS_multi)
       #pragma ghs section bss=".ecu_address"
     #elif (PLATFORMS_TOOLCHAIN == PLATFORMS_dcc)
       #pragma section DATA "" ".ecu_address"
     #endif
   #undef MEMMAP_ERROR
#elif defined (PROG_ECU_ADDRESS_STOP_SEC_VAR_NO_INIT_8)
   #undef      PROG_ECU_ADDRESS_STOP_SEC_VAR_NO_INIT_8
   #undef MEMMAP_ERROR
   #if (PLATFORMS_TOOLCHAIN == PLATFORMS_tasking)
     #pragma section farbss restore
     #pragma endprotect
   #elif (PLATFORMS_TOOLCHAIN == PLATFORMS_gnu)
   #elif (PLATFORMS_TOOLCHAIN == PLATFORMS_multi)
     #pragma ghs section
   #elif (PLATFORMS_TOOLCHAIN == PLATFORMS_dcc)
     #pragma section DATA "" ""
   #endif

#elif defined (PROG_SUPPPOSITIVERESPONSE_FLAG_START_SEC_VAR_NO_INIT_8)
   #undef      PROG_SUPPPOSITIVERESPONSE_FLAG_START_SEC_VAR_NO_INIT_8
     #if (PLATFORMS_TOOLCHAIN == PLATFORMS_tasking)
       #pragma section farbss "applitoboot_response"
       #pragma protect
     #elif (PLATFORMS_TOOLCHAIN == PLATFORMS_gnu)
      __attribute__((section(".applitoboot_response")))
     #elif (PLATFORMS_TOOLCHAIN == PLATFORMS_multi)
       #pragma ghs section bss=".applitoboot_response"
     #elif (PLATFORMS_TOOLCHAIN == PLATFORMS_dcc)
       #pragma section DATA "" ".applitoboot_response"
     #endif
   #undef MEMMAP_ERROR
#elif defined (PROG_SUPPPOSITIVERESPONSE_FLAG_STOP_SEC_VAR_NO_INIT_8)
   #undef      PROG_SUPPPOSITIVERESPONSE_FLAG_STOP_SEC_VAR_NO_INIT_8
   #undef MEMMAP_ERROR
   #if (PLATFORMS_TOOLCHAIN == PLATFORMS_tasking)
     #pragma section farbss restore
     #pragma endprotect
   #elif (PLATFORMS_TOOLCHAIN == PLATFORMS_gnu)
   #elif (PLATFORMS_TOOLCHAIN == PLATFORMS_multi)
     #pragma ghs section
   #elif (PLATFORMS_TOOLCHAIN == PLATFORMS_dcc)
     #pragma section DATA "" ""
   #endif

#elif defined (PROG_BOOT_INFO_START_SEC_CONST_UNSPECIFIED)
   #undef      PROG_BOOT_INFO_START_SEC_CONST_UNSPECIFIED
   #undef MEMMAP_ERROR
#elif defined (PROG_BOOT_INFO_STOP_SEC_CONST_UNSPECIFIED)
   #undef      PROG_BOOT_INFO_STOP_SEC_CONST_UNSPECIFIED
   #undef MEMMAP_ERROR
   
#elif (defined PROG_START_SEC_CODE_FLASH_PAGE)
  #undef PROG_START_SEC_CODE_FLASH_PAGE
  #undef MEMMAP_ERROR
  #if (PLATFORMS_TOOLCHAIN == PLATFORMS_tasking)
    #pragma section code="FlashPage"
    #pragma protect
     #elif (PLATFORMS_TOOLCHAIN == PLATFORMS_dcc)
        #pragma section code "FlashPage"
  #endif

#elif (defined PROG_STOP_SEC_CODE_FLASH_PAGE)
  #undef PROG_STOP_SEC_CODE_FLASH_PAGE
  #undef MEMMAP_ERROR
  #if (PLATFORMS_TOOLCHAIN == PLATFORMS_tasking)
    #pragma section code
    #pragma endprotect

  #elif (PLATFORMS_TOOLCHAIN == PLATFORMS_dcc)
      #pragma section code
  #endif

/*****************************************************************************
**                                 EB                                       **
******************************************************************************/
#elif (defined EB_BUFF_TP_WRAP_START_SEC_VAR )
  #undef EB_BUFF_TP_WRAP_START_SEC_VAR
  #undef MEMMAP_ERROR
#elif (defined EB_BUFF_TP_WRAP_STOP_SEC_VAR )
  #undef EB_BUFF_TP_WRAP_STOP_SEC_VAR
  #undef MEMMAP_ERROR
  
#elif (defined EB_FUNCBUFF_TP_WRAP_START_SEC_VAR )
  #undef EB_FUNCBUFF_TP_WRAP_START_SEC_VAR
  #undef MEMMAP_ERROR
#elif (defined EB_FUNCBUFF_TP_WRAP_STOP_SEC_VAR )
  #undef EB_FUNCBUFF_TP_WRAP_STOP_SEC_VAR
  #undef MEMMAP_ERROR
  
#elif (defined EB_PHYSBUFF_TP_WRAP_START_SEC_VAR )
  #undef EB_PHYSBUFF_TP_WRAP_START_SEC_VAR
  #undef MEMMAP_ERROR
#elif (defined EB_PHYSBUFF_TP_WRAP_STOP_SEC_VAR )
  #undef EB_PHYSBUFF_TP_WRAP_STOP_SEC_VAR
  #undef MEMMAP_ERROR
  
/*****************************************************************************
**                               BLPDUR                                       **
******************************************************************************/
#elif (defined BLPDUR_BUFF_START_SEC_VAR )
  #undef BLPDUR_BUFF_START_SEC_VAR
  #undef MEMMAP_ERROR
#elif (defined BLPDUR_BUFF_STOP_SEC_VAR )
  #undef BLPDUR_BUFF_STOP_SEC_VAR
  #undef MEMMAP_ERROR

  /*****************************************************************************
**                                 FLSLOADER                                **
******************************************************************************/

/*
 * To be used for mapping code to application block, boot block,
 * external flash etc
 */
#elif defined (FLSLOADER_START_SEC_CODE)
   #undef      FLSLOADER_START_SEC_CODE
   #undef MEMMAP_ERROR
#elif defined (FLSLOADER_STOP_SEC_CODE)
   #undef      FLSLOADER_STOP_SEC_CODE
   #undef MEMMAP_ERROR
#elif defined (FLSLOADER_START_SEC_WRITE_CODE)
  #if (PLATFORMS_TOOLCHAIN == PLATFORMS_tasking)
       #pragma section code "DRV_FLS_WRITE_SEC"
       #pragma section_name_with_symbol
       #pragma section_name_with_module
  #elif (PLATFORMS_TOOLCHAIN == PLATFORMS_dcc)
    #pragma section CODE ".DRV_FLS_WRITE_SEC"
  #endif

   #undef      FLSLOADER_START_SEC_WRITE_CODE
   #undef MEMMAP_ERROR
   
#elif defined (FLSLOADER_STOP_SEC_WRITE_CODE)
   #if (PLATFORMS_TOOLCHAIN == PLATFORMS_tasking)
        #pragma section code restore
   
  #elif (PLATFORMS_TOOLCHAIN == PLATFORMS_dcc)
    #pragma section CODE
  #endif

   #undef      FLSLOADER_STOP_SEC_WRITE_CODE
   #undef MEMMAP_ERROR
#elif defined (FLSLOADER_START_SEC_ERASE_CODE)
   #undef      FLSLOADER_START_SEC_ERASE_CODE
   #undef MEMMAP_ERROR
#elif defined (FLSLOADER_STOP_SEC_ERASE_CODE)
   #undef      FLSLOADER_STOP_SEC_ERASE_CODE
   #undef MEMMAP_ERROR
#elif defined (FLSLOADER_START_SEC_VAR_NOINIT_8BIT)
   #undef      FLSLOADER_START_SEC_VAR_NOINIT_8BIT
   #undef MEMMAP_ERROR
#elif defined (FLSLOADER_STOP_SEC_VAR_NOINIT_8BIT)
   #undef      FLSLOADER_STOP_SEC_VAR_NOINIT_8BIT
   #undef MEMMAP_ERROR
#elif defined (FLSLOADER_START_SEC_VAR_NOINIT_16BIT)
   #undef      FLSLOADER_START_SEC_VAR_NOINIT_16BIT
   #undef MEMMAP_ERROR
#elif defined (FLSLOADER_STOP_SEC_VAR_NOINIT_16BIT)
   #undef      FLSLOADER_STOP_SEC_VAR_NOINIT_16BIT
   #undef MEMMAP_ERROR


#elif defined (FLSLOADER_START_SEC_VAR_NOINIT_32BIT)
   #undef      FLSLOADER_START_SEC_VAR_NOINIT_32BIT
   #undef MEMMAP_ERROR
#elif defined (FLSLOADER_STOP_SEC_VAR_NOINIT_32BIT)
   #undef      FLSLOADER_STOP_SEC_VAR_NOINIT_32BIT
   #undef MEMMAP_ERROR


#elif defined (FLSLOADER_START_SEC_VAR_NOINIT_UNSPECIFIED)
   #undef      FLSLOADER_START_SEC_VAR_NOINIT_UNSPECIFIED
   #undef MEMMAP_ERROR
#elif defined (FLSLOADER_STOP_SEC_VAR_NOINIT_UNSPECIFIED)
   #undef      FLSLOADER_STOP_SEC_VAR_NOINIT_UNSPECIFIED
   #undef MEMMAP_ERROR


#elif defined (FLSLOADER_START_SEC_VAR_POWER_ON_INIT_8BIT)
   #undef      FLSLOADER_START_SEC_VAR_POWER_ON_INIT_8BIT
   #undef MEMMAP_ERROR
#elif defined (FLSLOADER_STOP_SEC_VAR_POWER_ON_INIT_8BIT)
   #undef      FLSLOADER_STOP_SEC_VAR_POWER_ON_INIT_8BIT
   #undef MEMMAP_ERROR


#elif defined (FLSLOADER_START_SEC_VAR_POWER_ON_INIT_16BIT)
   #undef      FLSLOADER_START_SEC_VAR_POWER_ON_INIT_16BIT
   #undef MEMMAP_ERROR
#elif defined (FLSLOADER_STOP_SEC_VAR_POWER_ON_INIT_16BIT)
   #undef      FLSLOADER_STOP_SEC_VAR_POWER_ON_INIT_16BIT
   #undef MEMMAP_ERROR


#elif defined (FLSLOADER_START_SEC_VAR_POWER_ON_INIT_32BIT)
   #undef      FLSLOADER_START_SEC_VAR_POWER_ON_INIT_32BIT
   #undef MEMMAP_ERROR
#elif defined (FLSLOADER_STOP_SEC_VAR_POWER_ON_INIT_32BIT)
   #undef      FLSLOADER_STOP_SEC_VAR_POWER_ON_INIT_32BIT
   #undef MEMMAP_ERROR


#elif defined (FLSLOADER_START_SEC_VAR_POWER_ON_INIT_UNSPECIFIED)
   #undef      FLSLOADER_START_SEC_VAR_POWER_ON_INIT_UNSPECIFIED
   #undef MEMMAP_ERROR
#elif defined (FLSLOADER_STOP_SEC_VAR_POWER_ON_INIT_UNSPECIFIED)
   #undef      FLSLOADER_STOP_SEC_VAR_POWER_ON_INIT_UNSPECIFIED
   #undef MEMMAP_ERROR


#elif defined (FLSLOADER_START_SEC_VAR_FAST_8BIT)
   #undef      FLSLOADER_START_SEC_VAR_FAST_8BIT
   #undef MEMMAP_ERROR
#elif defined (FLSLOADER_STOP_SEC_VAR_FAST_8BIT)
   #undef      FLSLOADER_STOP_SEC_VAR_FAST_8BIT
   #undef MEMMAP_ERROR


#elif defined (FLSLOADER_START_SEC_VAR_FAST_16BIT)
   #undef      FLSLOADER_START_SEC_VAR_FAST_16BIT
   #undef MEMMAP_ERROR
#elif defined (FLSLOADER_STOP_SEC_VAR_FAST_16BIT)
   #undef      FLSLOADER_STOP_SEC_VAR_FAST_16BIT
   #undef MEMMAP_ERROR


#elif defined (FLSLOADER_START_SEC_VAR_FAST_32BIT)
   #undef      FLSLOADER_START_SEC_VAR_FAST_32BIT
   #undef MEMMAP_ERROR
#elif defined (FLSLOADER_STOP_SEC_VAR_FAST_32BIT)
   #undef      FLSLOADER_STOP_SEC_VAR_FAST_32BIT
   #undef MEMMAP_ERROR


#elif defined (FLSLOADER_START_SEC_VAR_FAST_UNSPECIFIED)
   #undef      FLSLOADER_START_SEC_VAR_FAST_UNSPECIFIED
   #undef MEMMAP_ERROR
#elif defined (FLSLOADER_STOP_SEC_VAR_FAST_UNSPECIFIED)
   #undef      FLSLOADER_STOP_SEC_VAR_FAST_UNSPECIFIED
   #undef MEMMAP_ERROR


#elif defined (FLSLOADER_START_SEC_VAR_8BIT)
   #undef      FLSLOADER_START_SEC_VAR_8BIT
   #undef MEMMAP_ERROR
#elif defined (FLSLOADER_STOP_SEC_VAR_8BIT)
   #undef      FLSLOADER_STOP_SEC_VAR_8BIT
   #undef MEMMAP_ERROR


#elif defined (FLSLOADER_START_SEC_VAR_16BIT)
   #undef      FLSLOADER_START_SEC_VAR_16BIT
   #undef MEMMAP_ERROR
#elif defined (FLSLOADER_STOP_SEC_VAR_16BIT)
   #undef      FLSLOADER_STOP_SEC_VAR_16BIT
   #undef MEMMAP_ERROR


#elif defined (FLSLOADER_START_SEC_VAR_32BIT)
   #undef      FLSLOADER_START_SEC_VAR_32BIT
   #undef MEMMAP_ERROR
#elif defined (FLSLOADER_STOP_SEC_VAR_32BIT)
   #undef      FLSLOADER_STOP_SEC_VAR_32BIT
   #undef MEMMAP_ERROR


#elif defined (FLSLOADER_START_SEC_VAR_UNSPECIFIED)
   #undef      FLSLOADER_START_SEC_VAR_UNSPECIFIED
   #undef MEMMAP_ERROR
#elif defined (FLSLOADER_STOP_SEC_VAR_UNSPECIFIED)
   #undef      FLSLOADER_STOP_SEC_VAR_UNSPECIFIED
   #undef MEMMAP_ERROR


#elif defined (FLSLOADER_START_SEC_CONST_8BIT)
   #undef      FLSLOADER_START_SEC_CONST_8BIT
   #undef MEMMAP_ERROR
#elif defined (FLSLOADER_STOP_SEC_CONST_8BIT)
   #undef      FLSLOADER_STOP_SEC_CONST_8BIT
   #undef MEMMAP_ERROR


#elif defined (FLSLOADER_START_SEC_CONST_16BIT)
   #undef      FLSLOADER_START_SEC_CONST_16BIT
   #undef MEMMAP_ERROR
#elif defined (FLSLOADER_STOP_SEC_CONST_16BIT)
   #undef      FLSLOADER_STOP_SEC_CONST_16BIT
   #undef MEMMAP_ERROR


#elif defined (FLSLOADER_START_SEC_CONST_32BIT)
   #undef      FLSLOADER_START_SEC_CONST_32BIT
   #undef MEMMAP_ERROR
#elif defined (FLSLOADER_STOP_SEC_CONST_32BIT)
   #undef      FLSLOADER_STOP_SEC_CONST_32BIT
   #undef MEMMAP_ERROR


#elif defined (FLSLOADER_START_SEC_CONST_UNSPECIFIED)
   #undef      FLSLOADER_START_SEC_CONST_UNSPECIFIED
   #undef MEMMAP_ERROR
#elif defined (FLSLOADER_STOP_SEC_CONST_UNSPECIFIED)
   #undef      FLSLOADER_STOP_SEC_CONST_UNSPECIFIED
   #undef MEMMAP_ERROR

/*
Fls_Write API : Section
*/
#elif defined (FLSLOADER_START_SEC_WRITE_CODE)
   #undef      FLSLOADER_START_SEC_WRITE_CODE
   #undef MEMMAP_ERROR
#elif defined (FLSLOADER_STOP_SEC_WRITE_CODE)
   #undef      FLSLOADER_STOP_SEC_WRITE_CODE
   #undef MEMMAP_ERROR
/*
Fls Erase API : Section
*/
#elif defined (FLSLOADER_START_SEC_ERASE_CODE)
   #undef      FLSLOADER_START_SEC_ERASE_CODE
   #undef MEMMAP_ERROR
#elif defined (FLSLOADER_STOP_SEC_ERASE_CODE)
   #undef      FLSLOADER_STOP_SEC_ERASE_CODE
   #undef MEMMAP_ERROR

#endif

/* Deviation MISRA-1 <STOP> */

