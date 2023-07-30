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
/* Deviation MISRA-1 <START> */
#if 0 /* to be able to use #elif for every module */
/*------------------[Start of a module]--------------------------------------*/

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
        #pragma section farbss "ram_no_init"
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
       #pragma noclear
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
       #pragma noclear
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
      #if (TS_ARCH_FAMILY != TS_S12X)
            #pragma push
            #pragma section data_type ".prog_sig"
        #else
            #pragma DATA_SEG .prog_sig
        #endif
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
      #if (TS_ARCH_FAMILY != TS_S12X)
        #pragma pop
      #else
        #pragma DATA_SEG DEFAULT
       #endif
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
   #if (TS_ARCH_FAMILY != TS_S12X)
         #pragma push
         #pragma section data_type ".prog_antiscanning"
     #else
         #pragma DATA_SEG .prog_antiscanning
     #endif
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
   #if (TS_ARCH_FAMILY != TS_S12X)
     #pragma pop
   #else
     #pragma DATA_SEG DEFAULT
    #endif
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

#endif
