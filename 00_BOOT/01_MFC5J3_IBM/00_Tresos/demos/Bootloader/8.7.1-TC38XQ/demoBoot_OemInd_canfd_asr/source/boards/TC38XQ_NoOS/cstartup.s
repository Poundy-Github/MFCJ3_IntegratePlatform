
#ifndef I_KNOW_THAT_THIS_CODE_IS_NOT_FOR_PRODUCTION
#error "the program is not qualified for series production"
#endif



#ifndef BOARD_ASM
#define BOARD_ASM
#endif

#include <Platforms_asm_TRICORE.h>
#include <board.h>

  PLATFORMS_ASM_SECTION_TEXT

#if (PLATFORMS_TOOLCHAIN == PLATFORMS_tasking)
  Platforms_sdecl   ".reset",code
  Platforms_section ".reset"
#elif (PLATFORMS_TOOLCHAIN == PLATFORMS_dcc)
  Platforms_section   ".reset",c
#else
#error "This compiler is not supported"
#endif

start:
    j       boot
  Platforms_word    BOARD_TRICORE_BOOTWORD
  Platforms_hword   BOARD_TRICORE_BMI
  Platforms_hword   0xB359
  Platforms_word    0 /* Range start */
  Platforms_word    0 /* Range end */
  Platforms_word    0 /* CRC Range */
  Platforms_word    0 /* ~CRC Range */

  /* Note: this is the CRC32 of the first 6 32-bit words in *big* endian byte order! */
  Platforms_word    0x5db996ac /* CRC */
  Platforms_word    0xa2466953 /* ~CRC */

  Platforms_extern  BoardStart
  Platforms_extern  BoardInit
  Platforms_extern  BoardInitSp
  Platforms_extern  main

  Platforms_global  boot
  Platforms_global  boardGetCoreId

  Platforms_extern  BoardInitCsaList

  Platforms_align   (32,5)

boot:
  disable


  movh  d0,PLATFORMS_IMM(#,Platforms_hi(BOARD_INITIAL_PSW))
  addi  d0,d0,PLATFORMS_IMM(#,Platforms_lo(BOARD_INITIAL_PSW))
  _mtcr  PLATFORMS_IMM(#,PLATFORMS_PSW),d0


#if (PLATFORMS_TOOLCHAIN==PLATFORMS_dcc)
    movh.a    sp,PLATFORMS_IMM(#,Platforms_hi(__SP_INIT))
    lea       sp,[sp]PLATFORMS_IMM(#,Platforms_lo(__SP_INIT))
#endif

#if (PLATFORMS_TOOLCHAIN==PLATFORMS_tasking)
  jl   BoardInitSp
  jl   BoardInitCsaList
#endif

#if (BOARD_INIT_CPU_REG == BOARD_TRUE)
  /* Init CSA list*/
  jl   BoardInitCsaList
#endif

  jl   BoardInit

  jl   BoardStart

  j    main

  j    boot

boardGetCoreId:
   _mfcr d2, PLATFORMS_IMM(#,PLATFORMS_CORE_ID)
   ret
