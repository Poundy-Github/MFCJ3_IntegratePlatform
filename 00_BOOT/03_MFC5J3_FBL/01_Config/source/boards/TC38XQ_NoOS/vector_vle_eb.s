/**
 * \file
 *
 * \blief Board startup files
 *
 * This file contains the implementation of the hardware
 * interrupt vector table
 *
 * \author Elektrobit Automotive GmbH, 91058 Erlangen, Germany
 *
 * Copyright 2005 - 2014 Elektrobit Automotive GmbH
 * All rights exclusively reserved for Elektrobit Automotive GmbH,
 * unless expressly agreed to otherwise.
 */

#ifndef I_KNOW_THAT_THIS_CODE_IS_NOT_FOR_PRODUCTION
#error "the program is not qualified for series production"
#endif

/* file is nammed vector_vle_eb.s
 * !LINKSTO OsekCore.Platforms.Board.012, 1
 */

/*define to exclude C Code in header files*/
#ifndef BOARD_ASM
#define BOARD_ASM 1
#endif

/* Must be first */
#include <Platforms_asm_TRICORE.h>
#include <board.h>


#define BOARD_GEN_VECTOR(name , id , func) \
  ISRVector name,   \
            id,   \
            func

#define   BOARD_GEN_EXCEPTIONS(name , id , func) \
  TrapVector name,    \
             id,    \
             func    

    PLATFORMS_ASM_SECTION_DECL_INTCTAB
    PLATFORMS_ASM_SECTION_INTCTAB

/*
 * define symbols as global to allow easier debugging
 */
    Platforms_global IntcVectorTableHw
    Platforms_global BoardExceptionTable

    Platforms_extern BoardInvalidException

    Platforms_gtype(IntcVectorTableHw,@function)
    Platforms_extern   boot          /* In cstartup.s */

  Platforms_align(8192,13)
 /* All ISRs are mapped to BoardInvalidException to catch all unwanted exceptions
 * !LINKSTO OsekCore.Platforms.Board.014, 1
 */

 /*!
 * Vector 0 is a jump to the startup code, so that the vector table can
 * be located at the reset address.
*/
Platforms_ttype(IntcVectorTableHw,FUNC)

/* Interrupt vector 0 can never be reached by an interrupt. A jump to the
 * boot address and the BOARD_TRICORE_BOOTWORD are placed here so that the
 * interrupt vector table can be placed at the ROM boot location, which
 * is often a very good place for alignment reasons.
*/
  j boot
  .word BOARD_TRICORE_BOOTWORD

/*Unless all other Interrupt Vector Table, AURIX got SRC (Service Request Control Register)
 *ordered by priority, this means the same interrupt can be mapped more than once.
 *there are 255 priorities in this configuration (32bytes spacing)
 * see §17.3.1.8 of datasheet
 */
#ifndef BOARD_ISR_FR0
  BOARD_GEN_VECTOR(Board_Prio1_ISR, 1, BoardInvalidInterrupt)
#else
  BOARD_GEN_VECTOR(Board_Prio1_ISR, 1, BoardFrInterrupt)
#endif

#ifndef BOARD_ISR_CAN0
  BOARD_GEN_VECTOR(Board_Prio2_ISR, 2, BoardInvalidInterrupt)

  BOARD_GEN_VECTOR(Board_Prio3_ISR, 3, BoardInvalidInterrupt)

  BOARD_GEN_VECTOR(Board_Prio4_ISR, 4, BoardInvalidInterrupt)

  BOARD_GEN_VECTOR(Board_Prio5_ISR, 5, BoardInvalidInterrupt)

  BOARD_GEN_VECTOR(Board_Prio6_ISR, 6, BoardInvalidInterrupt)

  BOARD_GEN_VECTOR(Board_Prio7_ISR, 7, BoardInvalidInterrupt)

  BOARD_GEN_VECTOR(Board_Prio8_ISR, 8, BoardInvalidInterrupt)

  BOARD_GEN_VECTOR(Board_Prio9_ISR, 9, BoardInvalidInterrupt)

  BOARD_GEN_VECTOR(Board_Prio10_ISR, 10, BoardInvalidInterrupt)

  BOARD_GEN_VECTOR(Board_Prio11_ISR, 11, BoardInvalidInterrupt)

  BOARD_GEN_VECTOR(Board_Prio12_ISR, 12, BoardInvalidInterrupt)

  BOARD_GEN_VECTOR(Board_Prio13_ISR, 13, BoardInvalidInterrupt)

  BOARD_GEN_VECTOR(Board_Prio14_ISR, 14, BoardInvalidInterrupt)

  BOARD_GEN_VECTOR(Board_Prio15_ISR, 15, BoardInvalidInterrupt)

  BOARD_GEN_VECTOR(Board_Prio16_ISR, 16, BoardInvalidInterrupt)

  BOARD_GEN_VECTOR(Board_Prio17_ISR, 17, BoardInvalidInterrupt)
#else
  BOARD_GEN_VECTOR(Board_Prio2_ISR, 2, BoardCan0Interrupt0)

  BOARD_GEN_VECTOR(Board_Prio3_ISR, 3, BoardCan0Interrupt1)

  BOARD_GEN_VECTOR(Board_Prio4_ISR, 4, BoardCan0Interrupt2)

  BOARD_GEN_VECTOR(Board_Prio5_ISR, 5, BoardCan0Interrupt3)

  BOARD_GEN_VECTOR(Board_Prio6_ISR, 6, BoardCan0Interrupt4)

  BOARD_GEN_VECTOR(Board_Prio7_ISR, 7, BoardCan0Interrupt5)

  BOARD_GEN_VECTOR(Board_Prio8_ISR, 8, BoardCan0Interrupt6)

  BOARD_GEN_VECTOR(Board_Prio9_ISR, 9, BoardCan0Interrupt7)

  BOARD_GEN_VECTOR(Board_Prio10_ISR, 10, BoardCan0Interrupt8)

  BOARD_GEN_VECTOR(Board_Prio11_ISR, 11, BoardCan0Interrupt9)

  BOARD_GEN_VECTOR(Board_Prio12_ISR, 12, BoardCan0Interrupt10)

  BOARD_GEN_VECTOR(Board_Prio13_ISR, 13, BoardCan0Interrupt11)

  BOARD_GEN_VECTOR(Board_Prio14_ISR, 14, BoardCan0Interrupt12)

  BOARD_GEN_VECTOR(Board_Prio15_ISR, 15, BoardCan0Interrupt13)

  BOARD_GEN_VECTOR(Board_Prio16_ISR, 16, BoardCan0Interrupt14)

  BOARD_GEN_VECTOR(Board_Prio17_ISR, 17, BoardCan0Interrupt15)
#endif
#ifndef BOARD_ISR_TEST
  BOARD_GEN_VECTOR(Board_Prio18_ISR, 18, BoardInvalidInterrupt)
#else
  BOARD_GEN_VECTOR(Board_Prio18_ISR, 18, TestIsr)
#endif
#ifndef BOARD_ISR_LIN0
  BOARD_GEN_VECTOR(Board_Prio19_ISR, 19, BoardInvalidInterrupt)

  BOARD_GEN_VECTOR(Board_Prio20_ISR, 20, BoardInvalidInterrupt)

  BOARD_GEN_VECTOR(Board_Prio21_ISR, 21, BoardInvalidInterrupt)
#else
  BOARD_GEN_VECTOR(Board_Prio19_ISR, 19, BoardLinTXInterrupt)

  BOARD_GEN_VECTOR(Board_Prio20_ISR, 20, BoardLinRXInterrupt)

  BOARD_GEN_VECTOR(Board_Prio21_ISR, 21, BoardLinERRInterrupt)
#endif
  BOARD_GEN_VECTOR(Board_Prio22_ISR, 22, BoardInvalidInterrupt)

  BOARD_GEN_VECTOR(Board_Prio23_ISR, 23, BoardInvalidInterrupt)

  BOARD_GEN_VECTOR(Board_Prio24_ISR, 24, BoardInvalidInterrupt)

  BOARD_GEN_VECTOR(Board_Prio25_ISR, 25, BoardInvalidInterrupt)

  BOARD_GEN_VECTOR(Board_Prio26_ISR, 26, BoardInvalidInterrupt)

  BOARD_GEN_VECTOR(Board_Prio27_ISR, 27, BoardInvalidInterrupt)

  BOARD_GEN_VECTOR(Board_Prio28_ISR, 28, BoardInvalidInterrupt)

  BOARD_GEN_VECTOR(Board_Prio29_ISR, 29, BoardInvalidInterrupt)

  BOARD_GEN_VECTOR(Board_Prio30_ISR, 30, BoardInvalidInterrupt)

  BOARD_GEN_VECTOR(Board_Prio31_ISR, 31, BoardInvalidInterrupt)

  BOARD_GEN_VECTOR(Board_Prio32_ISR, 32, BoardInvalidInterrupt)

  BOARD_GEN_VECTOR(Board_Prio33_ISR, 33, BoardInvalidInterrupt)

  BOARD_GEN_VECTOR(Board_Prio34_ISR, 34, BoardInvalidInterrupt)

  BOARD_GEN_VECTOR(Board_Prio35_ISR, 35, BoardInvalidInterrupt)

  BOARD_GEN_VECTOR(Board_Prio36_ISR, 36, BoardInvalidInterrupt)

  BOARD_GEN_VECTOR(Board_Prio37_ISR, 37, BoardInvalidInterrupt)

  BOARD_GEN_VECTOR(Board_Prio38_ISR, 38, BoardInvalidInterrupt)

  BOARD_GEN_VECTOR(Board_Prio39_ISR, 39, BoardInvalidInterrupt)

  BOARD_GEN_VECTOR(Board_Prio40_ISR, 40, BoardInvalidInterrupt)

  BOARD_GEN_VECTOR(Board_Prio41_ISR, 41, BoardInvalidInterrupt)

  BOARD_GEN_VECTOR(Board_Prio42_ISR, 42, BoardInvalidInterrupt)

  BOARD_GEN_VECTOR(Board_Prio43_ISR, 43, BoardInvalidInterrupt)

  BOARD_GEN_VECTOR(Board_Prio44_ISR, 44, BoardInvalidInterrupt)

  BOARD_GEN_VECTOR(Board_Prio45_ISR, 45, BoardInvalidInterrupt)

  BOARD_GEN_VECTOR(Board_Prio46_ISR, 46, BoardInvalidInterrupt)

  BOARD_GEN_VECTOR(Board_Prio47_ISR, 47, BoardInvalidInterrupt)

  BOARD_GEN_VECTOR(Board_Prio48_ISR, 48, BoardInvalidInterrupt)

  BOARD_GEN_VECTOR(Board_Prio49_ISR, 49, BoardInvalidInterrupt)

  BOARD_GEN_VECTOR(Board_Prio50_ISR, 50, BoardInvalidInterrupt)

  BOARD_GEN_VECTOR(Board_Prio51_ISR, 51, BoardInvalidInterrupt)

  BOARD_GEN_VECTOR(Board_Prio52_ISR, 52, BoardInvalidInterrupt)

  BOARD_GEN_VECTOR(Board_Prio53_ISR, 53, BoardInvalidInterrupt)

  BOARD_GEN_VECTOR(Board_Prio54_ISR, 54, BoardInvalidInterrupt)

  BOARD_GEN_VECTOR(Board_Prio55_ISR, 55, BoardInvalidInterrupt)

  BOARD_GEN_VECTOR(Board_Prio56_ISR, 56, BoardInvalidInterrupt)

  BOARD_GEN_VECTOR(Board_Prio57_ISR, 57, BoardInvalidInterrupt)

  BOARD_GEN_VECTOR(Board_Prio58_ISR, 58, BoardInvalidInterrupt)

  BOARD_GEN_VECTOR(Board_Prio59_ISR, 59, BoardInvalidInterrupt)

  BOARD_GEN_VECTOR(Board_Prio60_ISR, 60, BoardInvalidInterrupt)

  BOARD_GEN_VECTOR(Board_Prio61_ISR, 61, BoardInvalidInterrupt)

  BOARD_GEN_VECTOR(Board_Prio62_ISR, 62, BoardInvalidInterrupt)

  BOARD_GEN_VECTOR(Board_Prio63_ISR, 63, BoardInvalidInterrupt)

  BOARD_GEN_VECTOR(Board_Prio64_ISR, 64, BoardInvalidInterrupt)

  BOARD_GEN_VECTOR(Board_Prio65_ISR, 65, BoardInvalidInterrupt)

  BOARD_GEN_VECTOR(Board_Prio66_ISR, 66, BoardInvalidInterrupt)

  BOARD_GEN_VECTOR(Board_Prio67_ISR, 67, BoardInvalidInterrupt)

  BOARD_GEN_VECTOR(Board_Prio68_ISR, 68, BoardInvalidInterrupt)

  BOARD_GEN_VECTOR(Board_Prio69_ISR, 69, BoardInvalidInterrupt)

  BOARD_GEN_VECTOR(Board_Prio70_ISR, 70, BoardInvalidInterrupt)

  BOARD_GEN_VECTOR(Board_Prio71_ISR, 71, BoardInvalidInterrupt)

  BOARD_GEN_VECTOR(Board_Prio72_ISR, 72, BoardInvalidInterrupt)

  BOARD_GEN_VECTOR(Board_Prio73_ISR, 73, BoardInvalidInterrupt)

  BOARD_GEN_VECTOR(Board_Prio74_ISR, 74, BoardInvalidInterrupt)

  BOARD_GEN_VECTOR(Board_Prio75_ISR, 75, BoardInvalidInterrupt)

  BOARD_GEN_VECTOR(Board_Prio76_ISR, 76, BoardInvalidInterrupt)

  BOARD_GEN_VECTOR(Board_Prio77_ISR, 77, BoardInvalidInterrupt)

  BOARD_GEN_VECTOR(Board_Prio78_ISR, 78, BoardInvalidInterrupt)

  BOARD_GEN_VECTOR(Board_Prio79_ISR, 79, BoardInvalidInterrupt)

  BOARD_GEN_VECTOR(Board_Prio80_ISR, 80, BoardInvalidInterrupt)

  BOARD_GEN_VECTOR(Board_Prio81_ISR, 81, BoardInvalidInterrupt)

  BOARD_GEN_VECTOR(Board_Prio82_ISR, 82, BoardInvalidInterrupt)

  BOARD_GEN_VECTOR(Board_Prio83_ISR, 83, BoardInvalidInterrupt)

  BOARD_GEN_VECTOR(Board_Prio84_ISR, 84, BoardInvalidInterrupt)

  BOARD_GEN_VECTOR(Board_Prio85_ISR, 85, BoardInvalidInterrupt)

  BOARD_GEN_VECTOR(Board_Prio86_ISR, 86, BoardInvalidInterrupt)

  BOARD_GEN_VECTOR(Board_Prio87_ISR, 87, BoardInvalidInterrupt)

  BOARD_GEN_VECTOR(Board_Prio88_ISR, 88, BoardInvalidInterrupt)

  BOARD_GEN_VECTOR(Board_Prio89_ISR, 89, BoardInvalidInterrupt)

  BOARD_GEN_VECTOR(Board_Prio90_ISR, 90, BoardInvalidInterrupt)

  BOARD_GEN_VECTOR(Board_Prio91_ISR, 91, BoardInvalidInterrupt)

  BOARD_GEN_VECTOR(Board_Prio92_ISR, 92, BoardInvalidInterrupt)

  BOARD_GEN_VECTOR(Board_Prio93_ISR, 93, BoardInvalidInterrupt)

  BOARD_GEN_VECTOR(Board_Prio94_ISR, 94, BoardInvalidInterrupt)

  BOARD_GEN_VECTOR(Board_Prio95_ISR, 95, BoardInvalidInterrupt)

  BOARD_GEN_VECTOR(Board_Prio96_ISR, 96, BoardInvalidInterrupt)

  BOARD_GEN_VECTOR(Board_Prio97_ISR, 97, BoardInvalidInterrupt)

  BOARD_GEN_VECTOR(Board_Prio98_ISR, 98, BoardInvalidInterrupt)

  BOARD_GEN_VECTOR(Board_Prio99_ISR, 99, BoardInvalidInterrupt)

  BOARD_GEN_VECTOR(Board_Prio100_ISR, 100, BoardInvalidInterrupt)

  BOARD_GEN_VECTOR(Board_Prio101_ISR, 101, BoardInvalidInterrupt)

  BOARD_GEN_VECTOR(Board_Prio102_ISR, 102, BoardInvalidInterrupt)

  BOARD_GEN_VECTOR(Board_Prio103_ISR, 103, BoardInvalidInterrupt)

  BOARD_GEN_VECTOR(Board_Prio104_ISR, 104, BoardInvalidInterrupt)

  BOARD_GEN_VECTOR(Board_Prio105_ISR, 105, BoardInvalidInterrupt)

  BOARD_GEN_VECTOR(Board_Prio106_ISR, 106, BoardInvalidInterrupt)

  BOARD_GEN_VECTOR(Board_Prio107_ISR, 107, BoardInvalidInterrupt)

  BOARD_GEN_VECTOR(Board_Prio108_ISR, 108, BoardInvalidInterrupt)

  BOARD_GEN_VECTOR(Board_Prio109_ISR, 109, BoardInvalidInterrupt)

  BOARD_GEN_VECTOR(Board_Prio110_ISR, 110, BoardInvalidInterrupt)

  BOARD_GEN_VECTOR(Board_Prio111_ISR, 111, BoardInvalidInterrupt)

  BOARD_GEN_VECTOR(Board_Prio112_ISR, 112, BoardInvalidInterrupt)

  BOARD_GEN_VECTOR(Board_Prio113_ISR, 113, BoardInvalidInterrupt)

  BOARD_GEN_VECTOR(Board_Prio114_ISR, 114, BoardInvalidInterrupt)

  BOARD_GEN_VECTOR(Board_Prio115_ISR, 115, BoardInvalidInterrupt)

  BOARD_GEN_VECTOR(Board_Prio116_ISR, 116, BoardInvalidInterrupt)

  BOARD_GEN_VECTOR(Board_Prio117_ISR, 117, BoardInvalidInterrupt)

  BOARD_GEN_VECTOR(Board_Prio118_ISR, 118, BoardInvalidInterrupt)

  BOARD_GEN_VECTOR(Board_Prio119_ISR, 119, BoardInvalidInterrupt)

  BOARD_GEN_VECTOR(Board_Prio120_ISR, 120, BoardInvalidInterrupt)

  BOARD_GEN_VECTOR(Board_Prio121_ISR, 121, BoardInvalidInterrupt)

  BOARD_GEN_VECTOR(Board_Prio122_ISR, 122, BoardInvalidInterrupt)

  BOARD_GEN_VECTOR(Board_Prio123_ISR, 123, BoardInvalidInterrupt)

  BOARD_GEN_VECTOR(Board_Prio124_ISR, 124, BoardInvalidInterrupt)

  BOARD_GEN_VECTOR(Board_Prio125_ISR, 125, BoardInvalidInterrupt)

  BOARD_GEN_VECTOR(Board_Prio126_ISR, 126, BoardInvalidInterrupt)

  BOARD_GEN_VECTOR(Board_Prio127_ISR, 127, BoardInvalidInterrupt)

  BOARD_GEN_VECTOR(Board_Prio128_ISR, 128, BoardInvalidInterrupt)

  BOARD_GEN_VECTOR(Board_Prio129_ISR, 129, BoardInvalidInterrupt)

  BOARD_GEN_VECTOR(Board_Prio130_ISR, 130, BoardInvalidInterrupt)

  BOARD_GEN_VECTOR(Board_Prio131_ISR, 131, BoardInvalidInterrupt)

  BOARD_GEN_VECTOR(Board_Prio132_ISR, 132, BoardInvalidInterrupt)

  BOARD_GEN_VECTOR(Board_Prio133_ISR, 133, BoardInvalidInterrupt)

  BOARD_GEN_VECTOR(Board_Prio134_ISR, 134, BoardInvalidInterrupt)

  BOARD_GEN_VECTOR(Board_Prio135_ISR, 135, BoardInvalidInterrupt)

  BOARD_GEN_VECTOR(Board_Prio136_ISR, 136, BoardInvalidInterrupt)

  BOARD_GEN_VECTOR(Board_Prio137_ISR, 137, BoardInvalidInterrupt)

  BOARD_GEN_VECTOR(Board_Prio138_ISR, 138, BoardInvalidInterrupt)

  BOARD_GEN_VECTOR(Board_Prio139_ISR, 139, BoardInvalidInterrupt)

  BOARD_GEN_VECTOR(Board_Prio140_ISR, 140, BoardInvalidInterrupt)

  BOARD_GEN_VECTOR(Board_Prio141_ISR, 141, BoardInvalidInterrupt)

  BOARD_GEN_VECTOR(Board_Prio142_ISR, 142, BoardInvalidInterrupt)

  BOARD_GEN_VECTOR(Board_Prio143_ISR, 143, BoardInvalidInterrupt)

  BOARD_GEN_VECTOR(Board_Prio144_ISR, 144, BoardInvalidInterrupt)

  BOARD_GEN_VECTOR(Board_Prio145_ISR, 145, BoardInvalidInterrupt)

  BOARD_GEN_VECTOR(Board_Prio146_ISR, 146, BoardInvalidInterrupt)

  BOARD_GEN_VECTOR(Board_Prio147_ISR, 147, BoardInvalidInterrupt)

  BOARD_GEN_VECTOR(Board_Prio148_ISR, 148, BoardInvalidInterrupt)

  BOARD_GEN_VECTOR(Board_Prio149_ISR, 149, BoardInvalidInterrupt)

  BOARD_GEN_VECTOR(Board_Prio150_ISR, 150, BoardInvalidInterrupt)

  BOARD_GEN_VECTOR(Board_Prio151_ISR, 151, BoardInvalidInterrupt)

  BOARD_GEN_VECTOR(Board_Prio152_ISR, 152, BoardInvalidInterrupt)

  BOARD_GEN_VECTOR(Board_Prio153_ISR, 153, BoardInvalidInterrupt)

  BOARD_GEN_VECTOR(Board_Prio154_ISR, 154, BoardInvalidInterrupt)

  BOARD_GEN_VECTOR(Board_Prio155_ISR, 155, BoardInvalidInterrupt)

  BOARD_GEN_VECTOR(Board_Prio156_ISR, 156, BoardInvalidInterrupt)

  BOARD_GEN_VECTOR(Board_Prio157_ISR, 157, BoardInvalidInterrupt)

  BOARD_GEN_VECTOR(Board_Prio158_ISR, 158, BoardInvalidInterrupt)

  BOARD_GEN_VECTOR(Board_Prio159_ISR, 159, BoardInvalidInterrupt)

  BOARD_GEN_VECTOR(Board_Prio160_ISR, 160, BoardInvalidInterrupt)

  BOARD_GEN_VECTOR(Board_Prio161_ISR, 161, BoardInvalidInterrupt)

  BOARD_GEN_VECTOR(Board_Prio162_ISR, 162, BoardInvalidInterrupt)

  BOARD_GEN_VECTOR(Board_Prio163_ISR, 163, BoardInvalidInterrupt)

  BOARD_GEN_VECTOR(Board_Prio164_ISR, 164, BoardInvalidInterrupt)

  BOARD_GEN_VECTOR(Board_Prio165_ISR, 165, BoardInvalidInterrupt)

  BOARD_GEN_VECTOR(Board_Prio166_ISR, 166, BoardInvalidInterrupt)

  BOARD_GEN_VECTOR(Board_Prio167_ISR, 167, BoardInvalidInterrupt)

  BOARD_GEN_VECTOR(Board_Prio168_ISR, 168, BoardInvalidInterrupt)

  BOARD_GEN_VECTOR(Board_Prio169_ISR, 169, BoardInvalidInterrupt)

  BOARD_GEN_VECTOR(Board_Prio170_ISR, 170, BoardInvalidInterrupt)

  BOARD_GEN_VECTOR(Board_Prio171_ISR, 171, BoardInvalidInterrupt)

  BOARD_GEN_VECTOR(Board_Prio172_ISR, 172, BoardInvalidInterrupt)

  BOARD_GEN_VECTOR(Board_Prio173_ISR, 173, BoardInvalidInterrupt)

  BOARD_GEN_VECTOR(Board_Prio174_ISR, 174, BoardInvalidInterrupt)

  BOARD_GEN_VECTOR(Board_Prio175_ISR, 175, BoardInvalidInterrupt)

  BOARD_GEN_VECTOR(Board_Prio176_ISR, 176, BoardInvalidInterrupt)

  BOARD_GEN_VECTOR(Board_Prio177_ISR, 177, BoardInvalidInterrupt)

  BOARD_GEN_VECTOR(Board_Prio178_ISR, 178, BoardInvalidInterrupt)

  BOARD_GEN_VECTOR(Board_Prio179_ISR, 179, BoardInvalidInterrupt)

  BOARD_GEN_VECTOR(Board_Prio180_ISR, 180, BoardInvalidInterrupt)

  BOARD_GEN_VECTOR(Board_Prio181_ISR, 181, BoardInvalidInterrupt)

  BOARD_GEN_VECTOR(Board_Prio182_ISR, 182, BoardInvalidInterrupt)

  BOARD_GEN_VECTOR(Board_Prio183_ISR, 183, BoardInvalidInterrupt)

  BOARD_GEN_VECTOR(Board_Prio184_ISR, 184, BoardInvalidInterrupt)

  BOARD_GEN_VECTOR(Board_Prio185_ISR, 185, BoardInvalidInterrupt)

  BOARD_GEN_VECTOR(Board_Prio186_ISR, 186, BoardInvalidInterrupt)

  BOARD_GEN_VECTOR(Board_Prio187_ISR, 187, BoardInvalidInterrupt)

  BOARD_GEN_VECTOR(Board_Prio188_ISR, 188, BoardInvalidInterrupt)

  BOARD_GEN_VECTOR(Board_Prio189_ISR, 189, BoardInvalidInterrupt)

  BOARD_GEN_VECTOR(Board_Prio190_ISR, 190, BoardInvalidInterrupt)

  BOARD_GEN_VECTOR(Board_Prio191_ISR, 191, BoardInvalidInterrupt)

  BOARD_GEN_VECTOR(Board_Prio192_ISR, 192, BoardInvalidInterrupt)

  BOARD_GEN_VECTOR(Board_Prio193_ISR, 193, BoardInvalidInterrupt)

  BOARD_GEN_VECTOR(Board_Prio194_ISR, 194, BoardInvalidInterrupt)

  BOARD_GEN_VECTOR(Board_Prio195_ISR, 195, BoardInvalidInterrupt)

  BOARD_GEN_VECTOR(Board_Prio196_ISR, 196, BoardInvalidInterrupt)

  BOARD_GEN_VECTOR(Board_Prio197_ISR, 197, BoardInvalidInterrupt)

  BOARD_GEN_VECTOR(Board_Prio198_ISR, 198, BoardInvalidInterrupt)

  BOARD_GEN_VECTOR(Board_Prio199_ISR, 199, BoardInvalidInterrupt)

  BOARD_GEN_VECTOR(Board_Prio200_ISR, 200, BoardInvalidInterrupt)

  BOARD_GEN_VECTOR(Board_Prio201_ISR, 201, BoardInvalidInterrupt)

  BOARD_GEN_VECTOR(Board_Prio202_ISR, 202, BoardInvalidInterrupt)

  BOARD_GEN_VECTOR(Board_Prio203_ISR, 203, BoardInvalidInterrupt)

  BOARD_GEN_VECTOR(Board_Prio204_ISR, 204, BoardInvalidInterrupt)

  BOARD_GEN_VECTOR(Board_Prio205_ISR, 205, BoardInvalidInterrupt)

  BOARD_GEN_VECTOR(Board_Prio206_ISR, 206, BoardInvalidInterrupt)

  BOARD_GEN_VECTOR(Board_Prio207_ISR, 207, BoardInvalidInterrupt)

  BOARD_GEN_VECTOR(Board_Prio208_ISR, 208, BoardInvalidInterrupt)

  BOARD_GEN_VECTOR(Board_Prio209_ISR, 209, BoardInvalidInterrupt)

  BOARD_GEN_VECTOR(Board_Prio210_ISR, 210, BoardInvalidInterrupt)

  BOARD_GEN_VECTOR(Board_Prio211_ISR, 211, BoardInvalidInterrupt)

  BOARD_GEN_VECTOR(Board_Prio212_ISR, 212, BoardInvalidInterrupt)

  BOARD_GEN_VECTOR(Board_Prio213_ISR, 213, BoardInvalidInterrupt)

  BOARD_GEN_VECTOR(Board_Prio214_ISR, 214, BoardInvalidInterrupt)

  BOARD_GEN_VECTOR(Board_Prio215_ISR, 215, BoardInvalidInterrupt)

  BOARD_GEN_VECTOR(Board_Prio216_ISR, 216, BoardInvalidInterrupt)

  BOARD_GEN_VECTOR(Board_Prio217_ISR, 217, BoardInvalidInterrupt)

  BOARD_GEN_VECTOR(Board_Prio218_ISR, 218, BoardInvalidInterrupt)

  BOARD_GEN_VECTOR(Board_Prio219_ISR, 219, BoardInvalidInterrupt)

  BOARD_GEN_VECTOR(Board_Prio220_ISR, 220, BoardInvalidInterrupt)

  BOARD_GEN_VECTOR(Board_Prio221_ISR, 221, BoardInvalidInterrupt)

  BOARD_GEN_VECTOR(Board_Prio222_ISR, 222, BoardInvalidInterrupt)

  BOARD_GEN_VECTOR(Board_Prio223_ISR, 223, BoardInvalidInterrupt)

  BOARD_GEN_VECTOR(Board_Prio224_ISR, 224, BoardInvalidInterrupt)

  BOARD_GEN_VECTOR(Board_Prio225_ISR, 225, BoardInvalidInterrupt)

  BOARD_GEN_VECTOR(Board_Prio226_ISR, 226, BoardInvalidInterrupt)

  BOARD_GEN_VECTOR(Board_Prio227_ISR, 227, BoardInvalidInterrupt)

  BOARD_GEN_VECTOR(Board_Prio228_ISR, 228, BoardInvalidInterrupt)

  BOARD_GEN_VECTOR(Board_Prio229_ISR, 229, BoardInvalidInterrupt)

  BOARD_GEN_VECTOR(Board_Prio230_ISR, 230, BoardInvalidInterrupt)

  BOARD_GEN_VECTOR(Board_Prio231_ISR, 231, BoardInvalidInterrupt)

  BOARD_GEN_VECTOR(Board_Prio232_ISR, 232, BoardInvalidInterrupt)

  BOARD_GEN_VECTOR(Board_Prio233_ISR, 233, BoardInvalidInterrupt)

  BOARD_GEN_VECTOR(Board_Prio234_ISR, 234, BoardInvalidInterrupt)

  BOARD_GEN_VECTOR(Board_Prio235_ISR, 235, BoardInvalidInterrupt)

  BOARD_GEN_VECTOR(Board_Prio236_ISR, 236, BoardInvalidInterrupt)

  BOARD_GEN_VECTOR(Board_Prio237_ISR, 237, BoardInvalidInterrupt)

  BOARD_GEN_VECTOR(Board_Prio238_ISR, 238, BoardInvalidInterrupt)

  BOARD_GEN_VECTOR(Board_Prio239_ISR, 239, BoardInvalidInterrupt)

  BOARD_GEN_VECTOR(Board_Prio240_ISR, 240, BoardInvalidInterrupt)

  BOARD_GEN_VECTOR(Board_Prio241_ISR, 241, BoardInvalidInterrupt)

  BOARD_GEN_VECTOR(Board_Prio242_ISR, 242, BoardInvalidInterrupt)

  BOARD_GEN_VECTOR(Board_Prio243_ISR, 243, BoardInvalidInterrupt)

  BOARD_GEN_VECTOR(Board_Prio244_ISR, 244, BoardInvalidInterrupt)

  BOARD_GEN_VECTOR(Board_Prio245_ISR, 245, BoardInvalidInterrupt)

  BOARD_GEN_VECTOR(Board_Prio246_ISR, 246, BoardInvalidInterrupt)

  BOARD_GEN_VECTOR(Board_Prio247_ISR, 247, BoardInvalidInterrupt)

  BOARD_GEN_VECTOR(Board_Prio248_ISR, 248, BoardInvalidInterrupt)

  BOARD_GEN_VECTOR(Board_Prio249_ISR, 249, BoardInvalidInterrupt)

  BOARD_GEN_VECTOR(Board_Prio250_ISR, 250, BoardInvalidInterrupt)

  BOARD_GEN_VECTOR(Board_Prio251_ISR, 251, BoardInvalidInterrupt)

  BOARD_GEN_VECTOR(Board_Prio252_ISR, 252, BoardInvalidInterrupt)

  BOARD_GEN_VECTOR(Board_Prio253_ISR, 253, BoardInvalidInterrupt)

  BOARD_GEN_VECTOR(Board_Prio254_ISR, 254, BoardInvalidInterrupt)

  BOARD_GEN_VECTOR(Board_Prio255_ISR, 255, BoardInvalidInterrupt)

/*!
 * Exception vectors
 *
 * Tricore has 8 exception vectors. They can be located anywhere in memory,
 * as long as they are aligned on a 64-word (256-byte) boundary.
 *
 * The first 6 exceptions, numbered 0 to 5, are fairly standard processor
 * exceptions. In each case, the register D15 contains the trap
 * identification number, which gives more detail about the
 * trap that occurred.
 *
 * The 7th exception is the syscall exception. This exception is used
 * to provide the interface between user-side code and kernel code.
 * The register D15 contains the system-call number specified in the
 * instruction, which ranges from 0 to 255.
 *
 * The final exception is NMI. NMI is normally triggered as a result
 * of an external non-maskable interrupt. On some Tricore boards, NMI
 * is used instead of a normal maskable interrupt. It is a simple matter
 * to redirect the interrupt to a maskable interrupt by writing an NMI
 * handler that triggers a software-triggered interrupt (through CPUSRC1
 * for example), and then by handling the interrupt on CPUSRC1 in the
 * normal way. Note that the NMI trap can also be caused by other events,
 * such as the  watchdog timer or a PLL problem. The NMISR register can
 * be examined to determine the cause.
 * WARNING: some Tricore derivatives do not always set the NMIEXT bit in
 * this register, so if no source is indicated, an external NMI should be
 * assumed.
 *
 *
 * In this version of the exception table, all exceptions  end up in
 * an endless loop. The loop
 */


/*==============================================================================
 *  Exception Table // Trap handler
 *============================================================================== */
 PLATFORMS_ASM_SECTION_DECL_EXCTAB
 PLATFORMS_ASM_SECTION_EXCTAB

  Platforms_align(256,8)
/*==============================================================================
 *  Reset/MMU exception
 *============================================================================== */
BoardExceptionTable:

  BOARD_GEN_EXCEPTIONS(Board_Trap0, 0, BoardInvalidException)
/*==============================================================================
 *  Internal protection traps
 *==============================================================================*/
  Platforms_align(32,5)
  BOARD_GEN_EXCEPTIONS(Board_Trap1, 1, BoardInvalidException)
/*==============================================================================
 *  Instruction errors
 *==============================================================================*/
  Platforms_align(32,5)
  BOARD_GEN_EXCEPTIONS(Board_Trap2, 2, BoardInvalidException)
/*==============================================================================
 *  Context management errors
 *==============================================================================*/
  Platforms_align(32,5)
  BOARD_GEN_EXCEPTIONS(Board_Trap3, 3, BoardInvalidException)
/*==============================================================================
 *  System bus and peripheral errors
 *==============================================================================*/
  Platforms_align(32,5)
  BOARD_GEN_EXCEPTIONS(Board_Trap4, 4, BoardInvalidException)
/*==============================================================================
 *  Assertion traps
 *==============================================================================*/
  Platforms_align(32,5)
  BOARD_GEN_EXCEPTIONS(Board_Trap5, 5, BoardInvalidException)
/*==============================================================================
 *  System call exception
  *==============================================================================*/
  Platforms_align(32,5)
  BOARD_GEN_EXCEPTIONS(Board_Trap6, 6, BoardInvalidException)
/*==============================================================================
 *  NMI, watchdog and PLL traps
 *==============================================================================*/
  Platforms_align(32,5)
  BOARD_GEN_EXCEPTIONS(Board_Trap7, 7, BoardInvalidException)

