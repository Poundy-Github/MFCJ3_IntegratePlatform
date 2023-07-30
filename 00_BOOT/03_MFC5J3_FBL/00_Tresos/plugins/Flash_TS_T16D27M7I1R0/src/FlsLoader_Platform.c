/* CHECK: RULE 203 OFF */
/* CHECK: RULE 404 OFF */
/* CHECK: RULE 205 OFF */
/* CHECK: RULE 506 OFF */
/* CHECK: RULE 306 OFF */
/* CHECK: NOPARSE (Infineon implementation code */
/*******************************************************************************
**                                                                            **
** Copyright (C) Infineon Technologies (2017)                                 **
**                                                                            **
** All rights reserved.                                                       **
**                                                                            **
** This document contains proprietary information belonging to Infineon       **
** Technologies. Passing on and copying of this document, and communication   **
** of its contents is not permitted without prior written authorization.      **
**                                                                            **
********************************************************************************
**                                                                            **
**  FILENAME     : FlsLoader_Platform.c                                       **
**                                                                            **
**  VERSION      : 2.0.0                                                      **
**                                                                            **
**  DATE         : 2017-04-05                                                 **
**                                                                            **
**  VARIANT      : Variant PC                                                 **
**                                                                            **
**  PLATFORM     : Infineon AURIX2G                                           **
**                                                                            **
**  AUTHOR       : DL-AUTOSAR-Engineering                                     **
**                                                                            **
**  VENDOR       : Infineon Technologies                                      **
**                                                                            **
**  DESCRIPTION  : Flsloader driver platform specific source file             **
**                                                                            **
**  SPECIFICATION(S) : NA                                                     **
**                                                                            **
**  MAY BE CHANGED BY USER : no                                               **
**                                                                            **
*******************************************************************************/
/* Global Misra Violation and Suppression */
/*  MISRA-C:2004 Deviation List
 *
 *  MISRA-1) Deviated Rule 11.3 (advisory)
 *   "A cast should not be performed between a pointer type and an integral type."
 *
 *   Reason:
 *   A cast is mandatory for memory access in FLASH_LLD_Read() API.
 *
 *  MISRA-2) Deviated Rule 10.1
 *   "Implicit conversion of the expression of underlying type 'unsigned char' to the
 *         type 'signed int' that is not a wider integer type of the same signedness."
 *
 *   Reason:
 *   extern golobal variables.
 *
 *  MISRA-3) Deviated Rule 11.3
 *   "A cast should not be performed between a pointer type and an integral type."
 *
 *   Reason:
 *   A cast is mandatory for memory access in FLASH_LLD_Read() API.
 *
 *  MISRA-4) Deviated Rule 11.4
 *   "A cast should not be performed between a pointer to object type and a different pointer to object type."
 *
 *   Reason:
 *   A cast is mandatory for memory access in FLASH_LLD_Read() API.
 *
 *  MISRA-5) Deviated Rule 11.5
 *   "A cast shall not be performed that removes any const or volatile qualification from the type addressed by a pointer."
 *
 *   Reason:
 *   A cast is mandatory for memory access in FLASH_LLD_Read() API.
 *   Reason:
 *   extern golobal variables.
 *
 *  MISRA-6) Deviated Rule 17.4 (required)
 *   "Array indexing shall be the only allowed form of pointer arithmetic."
 *
 *   Reason:
 *   Incrementing data pointer is needed to update the pointer of the datas to read.
 *   The rule indicates that we need to manipulate arrays instead of pointers for
 *   arithmetic operations but this implies temporary array copy mechanism, so much
 *   more code (useless) to do the same thing.
 *
 *  MISRA-7) Deviated Rule 8.1
 *   "Function 'XXX' has no complete visible prototype at call."
 *
 *   Reason:
 *   A cast is mandatory for memory access in FLASH_LLD_Read() API.
 *
 */

 /* Deviation MISRA-1 MISRA-2 MISRA-3 MISRA-4 MISRA-5 MISRA-6 MISRA-7 <START> */
/*******************************************************************************
**                      Includes                                              **
*******************************************************************************/

#include "FlsLoader_Local.h"
#include "FlsLoader.h"
/*******************************************************************************
**                      Private Macro Definitions                             **
*******************************************************************************/
#define FLSLOADER_EEPROM_OFFSETEND      (FLSLOADER_DFLASH0_BANK_SIZE - 1U)
#define FLSLOADER_DF_EEPROM_SEGMENT     (0xAF0U)
#define FLSLOADER_DF_UCB_SEGMENT        (0xAF4U)
#define FLSLOADER_EEPROM_SECTOR_SIZE    (0xFFFU)    /* 4K Sector size */
#define FLSLOADER_UCB_SECTOR_SIZE_1     (0x1FFU)    /* 512 Bytes */
#define FLSLOADER_MOD_8                 (0x7U)
#define FLSLOADER_NUM_8                 (0x8U)
#define FLSLOADER_UCB_SECTOR_SIZE       (FLSLOADER_UCB_SECTOR_SIZE_1+1U)
#define FLSLOADER_NUM_UCB_SECTORS       (1U)
/* UCB size is 512 bytes, one page is 8Bytes, Total page = 64. (512/8)*/
#define FLSLOADER_NUM_UCB_PAGES         (64U)
#define FLSLOADER_PAGE_SIZE             (8U)

#define FLSLOADER_DFLASH0_ADDRESS_MASK  ((FlsLoader_AddressType)(0x000FFFFFU))
#define FLSLOADER_UCB_ADDRESS_MASK      ((FlsLoader_AddressType)(0x00005FFFU))

#define FLSLOADER_DFLASH_SECTOR_SIZE    (FLSLOADER_EEPROM_SECTOR_SIZE+1U)
#define FLSLOADER_PROCON_CHECK          ((uint32)(0xFFFFFFFU))

#define FLASH_PROTECTION_TRUE        ((FLSLOADER_DF0_PROT != NO_PROTECTION)||\
                                      (FLSLOADER_PF0_PROT != NO_PROTECTION)||\
                                      (FLSLOADER_PF1_PROT != NO_PROTECTION)||\
                                      (FLSLOADER_PF2_PROT != NO_PROTECTION)||\
                                      (FLSLOADER_PF3_PROT != NO_PROTECTION)||\
                                      (FLSLOADER_PF4_PROT != NO_PROTECTION)||\
                                      (FLSLOADER_PF5_PROT != NO_PROTECTION))

#define FLASH_PROTECTION_FALSE       ((FLSLOADER_PF0_PROT == NO_PROTECTION)&&\
                                      (FLSLOADER_PF1_PROT == NO_PROTECTION)&&\
                                      (FLSLOADER_PF2_PROT == NO_PROTECTION)&&\
                                      (FLSLOADER_PF3_PROT == NO_PROTECTION)&&\
                                      (FLSLOADER_PF4_PROT == NO_PROTECTION)&&\
                                      (FLSLOADER_PF5_PROT == NO_PROTECTION)&&\
                                      (FLSLOADER_DF0_PROT == NO_PROTECTION))

#define FLASH_READ_WRITE_PTOTECTION_TRUE \
                                   ((FLSLOADER_PF0_PROT == WRITE_PROTECTION)||\
                                    (FLSLOADER_PF1_PROT == WRITE_PROTECTION)||\
                                    (FLSLOADER_PF2_PROT == WRITE_PROTECTION)||\
                                    (FLSLOADER_PF3_PROT == WRITE_PROTECTION)||\
                                    (FLSLOADER_PF4_PROT == WRITE_PROTECTION)||\
                                    (FLSLOADER_PF5_PROT == WRITE_PROTECTION)||\
                                    (FLSLOADER_PF0_PROT == READ_PROTECTION)||\
                                    (FLSLOADER_PF1_PROT == READ_PROTECTION)||\
                                    (FLSLOADER_PF2_PROT == READ_PROTECTION)||\
                                    (FLSLOADER_PF3_PROT == READ_PROTECTION)||\
                                    (FLSLOADER_PF4_PROT == READ_PROTECTION)||\
                                    (FLSLOADER_PF5_PROT == READ_PROTECTION))

#define FLASH_OTP_OWP_PROTECTION_TRUE \
                                    ((FLSLOADER_PF0_PROT == OTP_PROTECTION)||\
                                    (FLSLOADER_PF0_PROT == WOP_PROTECTION)||\
                                    (FLSLOADER_PF1_PROT == OTP_PROTECTION)||\
                                    (FLSLOADER_PF1_PROT == WOP_PROTECTION)||\
                                    (FLSLOADER_PF2_PROT == OTP_PROTECTION)||\
                                    (FLSLOADER_PF2_PROT == WOP_PROTECTION)||\
                                    (FLSLOADER_PF3_PROT == OTP_PROTECTION)||\
                                    (FLSLOADER_PF3_PROT == WOP_PROTECTION)||\
                                    (FLSLOADER_PF4_PROT == OTP_PROTECTION)||\
                                    (FLSLOADER_PF4_PROT == WOP_PROTECTION)||\
                                    (FLSLOADER_PF5_PROT == OTP_PROTECTION)||\
                                    (FLSLOADER_PF5_PROT == WOP_PROTECTION))

/*******************************************************************************
**                      Private Constant Definitions                          **
*******************************************************************************/
#define FLSLOADER_START_SEC_CONST_32BIT
/* MISRA2012_RULE_4_10_JUSTIFICATION: Flsloader_Memmap.h is repeatedly included
 * without include guard. This is as per AUTOSAR */
#include "MemMap.h"

/* Start address of all the PFlash banks */
#if (FLSLOADER_DEV_ERROR_DETECT == STD_ON)
static const uint32 FlsLoader_PFlashOffset[FLSLOADER_NUM_OF_PFLASH_BANK]=
{
    /* MISRA2012_RULE_13_1_JUSTIFICATION: global const, no persistent
     * side effect */
    FLSLOADER_PFLASH0_START_ADDRESS,
    /* MISRA2012_RULE_13_1_JUSTIFICATION: global const, no persistent
     * side effect */
    FLSLOADER_PFLASH1_START_ADDRESS,
    /* MISRA2012_RULE_13_1_JUSTIFICATION: global const, no persistent
     * side effect */
    FLSLOADER_PFLASH2_START_ADDRESS,
    /* MISRA2012_RULE_13_1_JUSTIFICATION: global const, no persistent
     * side effect */
    FLSLOADER_PFLASH3_START_ADDRESS,
    /* MISRA2012_RULE_13_1_JUSTIFICATION: global const, no persistent
     * side effect */
    FLSLOADER_PFLASH4_START_ADDRESS,
    /* MISRA2012_RULE_13_1_JUSTIFICATION: global const, no persistent
     * side effect */
    FLSLOADER_PFLASH5_START_ADDRESS
    /* MISRA2012_RULE_13_1_JUSTIFICATION: global const, no persistent
     * side effect */
};
#endif
static const uint8 FlsLoader_PFlashSectorCount[FLSLOADER_NUM_OF_PFLASH_BANK]=
{
    FLSLOADER_NUM_OF_PF0_SECTORS,
    FLSLOADER_NUM_OF_PF1_SECTORS,
    FLSLOADER_NUM_OF_PF2_SECTORS,
    FLSLOADER_NUM_OF_PF3_SECTORS,
    FLSLOADER_NUM_OF_PF4_SECTORS,
    FLSLOADER_NUM_OF_PF5_SECTORS
};

#if (FLSLOADER_LOCK_UNLOCK_API == STD_ON)
/* UCB_PFLASH Content */
#if ((FLSLOADER_PF0_PROT == WRITE_PROTECTION)||\
     (FLSLOADER_PF1_PROT == WRITE_PROTECTION)||\
     (FLSLOADER_PF2_PROT == WRITE_PROTECTION)||\
     (FLSLOADER_PF3_PROT == WRITE_PROTECTION)||\
     (FLSLOADER_PF4_PROT == WRITE_PROTECTION)||\
     (FLSLOADER_PF5_PROT == WRITE_PROTECTION)||\
     (FLSLOADER_PF0_PROT == READ_PROTECTION) ||\
     (FLSLOADER_PF1_PROT == READ_PROTECTION) ||\
     (FLSLOADER_PF2_PROT == READ_PROTECTION) ||\
     (FLSLOADER_PF3_PROT == READ_PROTECTION) ||\
     (FLSLOADER_PF4_PROT == READ_PROTECTION) ||\
     (FLSLOADER_PF5_PROT == READ_PROTECTION))
/* MISRA2012_RULE_8_9_JUSTIFICATION: FlsLoader_UcbPFlashPage0 is declared
 * static to the file */
static const uint32 FlsLoader_UcbPFlashPage0[FLSLOADER_UCB_PFLASH_ORGINAL_SIZE]=
{
    FLSLOADER_PROCONP00, FLSLOADER_PROCONP01,   /*0x000, 0x004 */
    FLSLOADER_PROCONP02, FLSLOADER_PROCONP03,   /*0x008, 0x00C */
    FLSLOADER_PROCONP04, FLSLOADER_PROCONP05,   /*0x010, 0x014 */
    0x00000000, 0x00000000,                     /*0x018, 0x01C */
    FLSLOADER_PROCONP10, FLSLOADER_PROCONP11,   /*0x020, 0x024 */
    FLSLOADER_PROCONP12, FLSLOADER_PROCONP13,   /*0x028, 0x02C */
    FLSLOADER_PROCONP14, FLSLOADER_PROCONP15,   /*0x030, 0x034 */
    0x00000000, 0x00000000,                     /*0x038, 0x03C */
    FLSLOADER_PROCONP20, FLSLOADER_PROCONP21,   /*0x040, 0x044 */
    FLSLOADER_PROCONP22, FLSLOADER_PROCONP23,   /*0x048, 0x04C */
    FLSLOADER_PROCONP24, FLSLOADER_PROCONP25,   /*0x050, 0x054 */
    0x00000000, 0x00000000,                     /*0x058, 0x05C */
    FLSLOADER_PROCONP30, FLSLOADER_PROCONP31,   /*0x060, 0x064 */
    FLSLOADER_PROCONP32, FLSLOADER_PROCONP33,   /*0x068, 0x06C */
    FLSLOADER_PROCONP34, FLSLOADER_PROCONP35,   /*0x070, 0x074 */
    0x00000000, 0x00000000,                     /*0x078, 0x07C */
    FLSLOADER_PROCONP40, FLSLOADER_PROCONP41,   /*0x080, 0x084 */
    FLSLOADER_PROCONP42, FLSLOADER_PROCONP43,   /*0x088, 0x08C */
    FLSLOADER_PROCONP44, FLSLOADER_PROCONP45,   /*0x090, 0x094 */
    0x00000000, 0x00000000,                     /*0x098, 0x09C */
    FLSLOADER_PROCONP50, FLSLOADER_PROCONP51,   /*0x0A0, 0x0A4 */
    0x00000000, 0x00000000,                     /*0x0A8, 0x0AC */
    0x00000000, 0x00000000,                     /*0x0B0, 0x0B4 */
    0x00000000, 0x00000000,                     /*0x0B8, 0x0BC */
    0x00000000, 0x00000000,                     /*0x0C0, 0x0C4 */
    0x00000000, 0x00000000,                     /*0x0C8, 0x0CC */
    0x00000000, 0x00000000,                     /*0x0D0, 0x0D4 */
    0x00000000, 0x00000000,                     /*0x0D8, 0x0DC */
    0x00000000, 0x00000000,                     /*0x0E0, 0x0E4 */
    0x00000000, 0x00000000,                     /*0x0E8, 0x0EC */
    0x00000000, 0x00000000,                     /*0x0F0, 0x0F4 */
    0x00000000, 0x00000000,                     /*0x0F8, 0x0FC */
    FLSLOADER_PF0_PW00, FLSLOADER_PF0_PW01,     /*0x100, 0x104 */
    FLSLOADER_PF0_PW10, FLSLOADER_PF0_PW11,     /*0x108, 0x10C */
    FLSLOADER_PF0_PW20, FLSLOADER_PF0_PW21,     /*0x110, 0x114 */
    FLSLOADER_PF0_PW30, FLSLOADER_PF0_PW31,     /*0x118, 0x11C */
    0x00000000, 0x00000000,                     /*0x120, 0x124 */
    0x00000000, 0x00000000,                     /*0x128, 0x12C */
    0x00000000, 0x00000000,                     /*0x130, 0x134 */
    0x00000000, 0x00000000,                     /*0x138, 0x13C */
    0x00000000, 0x00000000,                     /*0x140, 0x144 */
    0x00000000, 0x00000000,                     /*0x148, 0x14C */
    0x00000000, 0x00000000,                     /*0x150, 0x154 */
    0x00000000, 0x00000000,                     /*0x158, 0x15C */
    0x00000000, 0x00000000,                     /*0x160, 0x164 */
    0x00000000, 0x00000000,                     /*0x168, 0x16C */
    0x00000000, 0x00000000,                     /*0x170, 0x174 */
    0x00000000, 0x00000000,                     /*0x178, 0x17C */
    0x00000000, 0x00000000,                     /*0x180, 0x184 */
    0x00000000, 0x00000000,                     /*0x188, 0x18C */
    0x00000000, 0x00000000,                     /*0x190, 0x194 */
    0x00000000, 0x00000000,                     /*0x198, 0x19C */
    0x00000000, 0x00000000,                     /*0x1A0, 0x1A4 */
    0x00000000, 0x00000000,                     /*0x1A8, 0x1AC */
    0x00000000, 0x00000000,                     /*0x1B0, 0x1B4 */
    0x00000000, 0x00000000,                     /*0x1B8, 0x1BC */
    0x00000000, 0x00000000,                     /*0x1C0, 0x1C4 */
    0x00000000, 0x00000000,                     /*0x1C8, 0x1CC */
    0x00000000, 0x00000000,                     /*0x1D0, 0x1D4 */
    0x00000000, 0x00000000,                     /*0x1D8, 0x1DC */
    0x00000000, 0x00000000,                     /*0x1E0, 0x1E4 */
    0x00000000, 0x00000000,                     /*0x1E8, 0x1EC */
    FLSLOADER_CONFIRMATION_CODE, 0x00000000,     /*0x1F0, 0x1F4 */
    0x00000000, 0x00000000                     /*0x1F8, 0x1FC */
};
#endif
  /*#if ((FLSLOADER_PF0_PROT == WRITE_PROTECTION)||...*/


  /* UCB_DPFLASH Content */
#if (FLSLOADER_DF0_PROT != NO_PROTECTION)
/* MISRA2012_RULE_8_9_JUSTIFICATION: FlsLoader_UcbDFlashPage0 is declared
 * static to the file */
static const uint32 FlsLoader_UcbDFlashPage0[FLSLOADER_UCB_DFLASH_ORGINAL_SIZE]=
{
    FLSLOADER_DF0_USERMODE, FLSLOADER_PROCOND0, /* 0x000, 0x004 */
    0x00000000, 0x00000000,                     /* 0x008, 0x00C */
    0x00000000, 0x00000000,                     /* 0x010, 0x014 */
    0x00000000, 0x00000000,                     /* 0x018, 0x01C */
    0x00000000, 0x00000000,                     /* 0x020, 0x024 */
    0x00000000, 0x00000000,                     /* 0x028, 0x02C */
    0x00000000, 0x00000000,                     /* 0x030, 0x034 */
    0x00000000, 0x00000000,                     /* 0x038, 0x03C */
    0x00000000, 0x00000000,                     /* 0x040, 0x044 */
    0x00000000, 0x00000000,                     /* 0x048, 0x04C */
    0x00000000, 0x00000000,                     /* 0x050, 0x054 */
    0x00000000, 0x00000000,                     /* 0x058, 0x05C */
    0x00000000, 0x00000000,                     /* 0x060, 0x064 */
    0x00000000, 0x00000000,                     /* 0x068, 0x06C */
    0x00000000, 0x00000000,                     /* 0x070, 0x074 */
    0x00000000, 0x00000000,                     /* 0x078, 0x07C */
    0x00000000, 0x00000000,                     /* 0x080, 0x084 */
    0x00000000, 0x00000000,                     /* 0x088, 0x08C */
    0x00000000, 0x00000000,                     /* 0x090, 0x094 */
    0x00000000, 0x00000000,                     /* 0x098, 0x09C */
    0x00000000, 0x00000000,                     /* 0x0A0, 0x0A4 */
    0x00000000, 0x00000000,                     /* 0x0A8, 0x0AC */
    0x00000000, 0x00000000,                     /* 0x0B0, 0x0B4 */
    0x00000000, 0x00000000,                     /* 0x0B8, 0x0BC */
    0x00000000, 0x00000000,                     /* 0x0C0, 0x0C4 */
    0x00000000, 0x00000000,                     /* 0x0C8, 0x0CC */
    0x00000000, 0x00000000,                     /* 0x0D0, 0x0D4 */
    0x00000000, 0x00000000,                     /* 0x0D8, 0x0DC */
    0x00000000, 0x00000000,                     /* 0x0E0, 0x0E4 */
    0x00000000, 0x00000000,                     /* 0x0E8, 0x0EC */
    0x00000000, 0x00000000,                     /* 0x0F0, 0x0F4 */
    0x00000000, 0x00000000,                     /* 0x0F8, 0x0FC */
    FLSLOADER_DF0_PW00, FLSLOADER_DF0_PW01,     /* 0x100, 0x104 */
    FLSLOADER_DF0_PW10, FLSLOADER_DF0_PW11,     /* 0x108, 0x10C */
    FLSLOADER_DF0_PW20, FLSLOADER_DF0_PW21,     /* 0x110, 0x114 */
    FLSLOADER_DF0_PW30, FLSLOADER_DF0_PW31,     /* 0x118, 0x11C */
    0x00000000, 0x00000000,                     /* 0x120, 0x124 */
    0x00000000, 0x00000000,                     /* 0x128, 0x12C */
    0x00000000, 0x00000000,                     /* 0x130, 0x134 */
    0x00000000, 0x00000000,                     /* 0x138, 0x13C */
    0x00000000, 0x00000000,                     /* 0x140, 0x144 */
    0x00000000, 0x00000000,                     /* 0x148, 0x14C */
    0x00000000, 0x00000000,                     /* 0x150, 0x154 */
    0x00000000, 0x00000000,                     /* 0x158, 0x15C */
    0x00000000, 0x00000000,                     /* 0x160, 0x164 */
    0x00000000, 0x00000000,                     /* 0x168, 0x16C */
    0x00000000, 0x00000000,                     /* 0x170, 0x174 */
    0x00000000, 0x00000000,                     /* 0x178, 0x17C */
    0x00000000, 0x00000000,                     /* 0x180, 0x184 */
    0x00000000, 0x00000000,                     /* 0x188, 0x18C */
    0x00000000, 0x00000000,                     /* 0x190, 0x194 */
    0x00000000, 0x00000000,                     /* 0x198, 0x19C */
    0x00000000, 0x00000000,                     /* 0x1A0, 0x1A4 */
    0x00000000, 0x00000000,                     /* 0x1A8, 0x1AC */
    0x00000000, 0x00000000,                     /* 0x1B0, 0x1B4 */
    0x00000000, 0x00000000,                     /* 0x1B8, 0x1BC */
    0x00000000, 0x00000000,                     /* 0x1C0, 0x1C4 */
    0x00000000, 0x00000000,                     /* 0x1C8, 0x1CC */
    0x00000000, 0x00000000,                     /* 0x1D0, 0x1D4 */
    0x00000000, 0x00000000,                     /* 0x1D8, 0x1DC */
    0x00000000, 0x00000000,                     /* 0x1E0, 0x1E4 */
    0x00000000, 0x00000000,                     /* 0x1E8, 0x1EC */
    FLSLOADER_CONFIRMATION_CODE, 0x00000000,/* 0x1F0, 0x1F4 */
    0x00000000, 0x00000000,                     /* 0x1F8, 0x1FC */
};
#endif
  /*#if (FLSLOADER_PF0_PROT != NO_PROTECTION)*/

  /* UCB OTP FLASH content */
#if  ((FLSLOADER_PF0_PROT == OTP_PROTECTION)||\
      (FLSLOADER_PF0_PROT == WOP_PROTECTION)||\
      (FLSLOADER_PF1_PROT == OTP_PROTECTION)||\
      (FLSLOADER_PF1_PROT == WOP_PROTECTION)||\
      (FLSLOADER_PF2_PROT == OTP_PROTECTION)||\
      (FLSLOADER_PF2_PROT == WOP_PROTECTION)||\
      (FLSLOADER_PF3_PROT == OTP_PROTECTION)||\
      (FLSLOADER_PF3_PROT == WOP_PROTECTION)||\
      (FLSLOADER_PF4_PROT == OTP_PROTECTION)||\
      (FLSLOADER_PF4_PROT == WOP_PROTECTION)||\
      (FLSLOADER_PF5_PROT == OTP_PROTECTION)||\
      (FLSLOADER_PF5_PROT == WOP_PROTECTION))
/* MISRA2012_RULE_8_9_JUSTIFICATION: FlsLoader_UcbDFlashPage0 is declared
 * static to the file */
static const uint32 FlsLoader_UcbOTPFlashPage0[FLSLOADER_UCB_OTP0_SIZE] = {
    FLSLOADER_PROCONOTP00, FLSLOADER_PROCONOTP01,   /* 0x000, 0x004 */
    FLSLOADER_PROCONOTP02, FLSLOADER_PROCONOTP03,   /* 0x008, 0x00C */
    FLSLOADER_PROCONOTP04, FLSLOADER_PROCONOTP05,   /* 0x010, 0x014 */
    0x00000000, 0x00000000,                         /* 0x018, 0x01C */
    FLSLOADER_PROCONOTP10, FLSLOADER_PROCONOTP11,   /* 0x020, 0x024 */
    FLSLOADER_PROCONOTP12, FLSLOADER_PROCONOTP13,   /* 0x028, 0x02C */
    FLSLOADER_PROCONOTP14, FLSLOADER_PROCONOTP15,   /* 0x030, 0x034 */
    0x00000000, 0x00000000,                         /* 0x038, 0x03C */
    FLSLOADER_PROCONOTP20, FLSLOADER_PROCONOTP21,   /* 0x040, 0x044 */
    FLSLOADER_PROCONOTP22, FLSLOADER_PROCONOTP23,   /* 0x048, 0x04C */
    FLSLOADER_PROCONOTP24, FLSLOADER_PROCONOTP25,   /* 0x050, 0x054 */
    0x00000000, 0x00000000,                         /* 0x058, 0x05C */
    FLSLOADER_PROCONOTP30, FLSLOADER_PROCONOTP31,   /* 0x060, 0x064 */
    FLSLOADER_PROCONOTP32, FLSLOADER_PROCONOTP33,   /* 0x068, 0x06C */
    FLSLOADER_PROCONOTP34, FLSLOADER_PROCONOTP35,   /* 0x070, 0x074 */
    0x00000000, 0x00000000,                         /* 0x078, 0x07C */
    FLSLOADER_PROCONOTP40, FLSLOADER_PROCONOTP41,   /* 0x080, 0x084 */
    FLSLOADER_PROCONOTP42, FLSLOADER_PROCONOTP43,   /* 0x088, 0x08C */
    FLSLOADER_PROCONOTP44, FLSLOADER_PROCONOTP45,   /* 0x090, 0x094 */
    0x00000000, 0x00000000,                         /* 0x098, 0x09C */
    FLSLOADER_PROCONOTP50, FLSLOADER_PROCONOTP51,   /* 0x0A0, 0x0A4 */
    0x00000000, 0x00000000,                         /* 0x0A8, 0x0AC */
    0x00000000, 0x00000000,                         /* 0x0B0, 0x0B4 */
    0x00000000, 0x00000000,                         /* 0x0B8, 0x0BC */
    0x00000000, 0x00000000,                         /* 0x0C0, 0x0C4 */
    0x00000000, 0x00000000,                         /* 0x0C8, 0x0CC */
    0x00000000, 0x00000000,                         /* 0x0D0, 0x0D4 */
    0x00000000, 0x00000000,                         /* 0x0D8, 0x0DC */
    0x00000000, 0x00000000,                         /* 0x0E0, 0x0E4 */
    0x00000000, 0x00000000,                         /* 0x0E8, 0x0EC */
    0x00000000, 0x00000000,                         /* 0x0F0, 0x0F4 */
    0x00000000, 0x00000000,                         /* 0x0F8, 0x0FC */
    FLSLOADER_PROCONWOP00, FLSLOADER_PROCONWOP01,   /* 0x100, 0x104 */
    FLSLOADER_PROCONWOP02, FLSLOADER_PROCONWOP03,   /* 0x108, 0x10C */
    FLSLOADER_PROCONWOP04, FLSLOADER_PROCONWOP05,   /* 0x110, 0x114 */
    0x00000000, 0x00000000,                         /* 0x118, 0x11C */
    FLSLOADER_PROCONWOP10, FLSLOADER_PROCONWOP11,   /* 0x120, 0x124 */
    FLSLOADER_PROCONWOP12, FLSLOADER_PROCONWOP13,   /* 0x128, 0x12C */
    FLSLOADER_PROCONWOP14, FLSLOADER_PROCONWOP15,   /* 0x130, 0x134 */
    0x00000000, 0x00000000,                         /* 0x138, 0x13C */
    FLSLOADER_PROCONWOP20, FLSLOADER_PROCONWOP21,   /* 0x140, 0x144 */
    FLSLOADER_PROCONWOP22, FLSLOADER_PROCONWOP23,   /* 0x148, 0x14C */
    FLSLOADER_PROCONWOP24, FLSLOADER_PROCONWOP25,   /* 0x150, 0x154 */
    0x00000000, 0x00000000,                         /* 0x158, 0x15C */
    FLSLOADER_PROCONWOP30, FLSLOADER_PROCONWOP31,   /* 0x160, 0x164 */
    FLSLOADER_PROCONWOP32, FLSLOADER_PROCONWOP33,   /* 0x168, 0x16C */
    FLSLOADER_PROCONWOP34, FLSLOADER_PROCONWOP35,   /* 0x170, 0x174 */
    0x00000000, 0x00000000,                         /* 0x178, 0x17C */
    FLSLOADER_PROCONWOP40, FLSLOADER_PROCONWOP41,   /* 0x180, 0x184 */
    FLSLOADER_PROCONWOP42, FLSLOADER_PROCONWOP43,   /* 0x188, 0x18C */
    FLSLOADER_PROCONWOP44, FLSLOADER_PROCONWOP45,   /* 0x190, 0x194 */
    0x00000000, 0x00000000,                         /* 0x198, 0x19C */
    FLSLOADER_PROCONWOP50, FLSLOADER_PROCONWOP51,   /* 0x1A0, 0x1A4 */
    0x00000000, 0x00000000,                         /* 0x1A8, 0x1AC */
    0x00000000, 0x00000000,                         /* 0x1B0, 0x1B4 */
    0x00000000, 0x00000000,                         /* 0x1B8, 0x1BC */
    0x00000000, 0x00000000,                         /* 0x1C0, 0x1C4 */
    0x00000000, 0x00000000,                         /* 0x1C8, 0x1CC */
    0x00000000, 0x00000000,                         /* 0x1D0, 0x1D4 */
    0x00000000, 0x00000000,                         /* 0x1D8, 0x1DC */
    0x00000000, 0x00000000,                         /* 0x1E0, 0x1E4 */
    0x00000000, 0x00000000,                         /* 0x1E8, 0x1EC */
    FLSLOADER_CONFIRMATION_CODE, 0x00000000,        /* 0x1F0, 0x1F4 */
    0x00000000, 0x00000000,                         /* 0x1F8, 0x1FC */
};
#endif  /*  #if ((FLSLOADER_PF0_PROT == OTP_PROTECTION)...*/
#endif /* #if (FLSLOADER_LOCK_UNLOCK_API == STD_ON)*/

#define FLSLOADER_STOP_SEC_CONST_32BIT
/* MISRA2012_RULE_4_10_JUSTIFICATION: Flsloader_Memmap.h is repeatedly included
 * without include guard. This is as per AUTOSAR */
/* MISRA2012_RULE_20_1_JUSTIFICATION: declaration of 'FlsLoader_PFlashOffset'
 * before #include memap.h - Accepted deviation in AUTOSAR */
#include "MemMap.h"

/*******************************************************************************
**                    Prototypes Of Local Functions                           **
*******************************************************************************/
#define FLSLOADER_START_SEC_WRITE_CODE
/* MISRA2012_RULE_4_10_JUSTIFICATION: Flsloader_Memmap.h is repeatedly included
 * without include guard. This is as per AUTOSAR */
/* MISRA2012_RULE_20_1_JUSTIFICATION: declaration of 'FlsLoader_PFlashOffset'
 * before #include memap.h - Accepted deviation in AUTOSAR */
#include "MemMap.h"
#if (FLSLOADER_DEV_ERROR_DETECT == STD_ON)

  /*
  Function FlsLoader_lAddressPageCheck
  Input Parameters: TargetAddress
  */
LOCAL_INLINE uint8 FlsLoader_lAddressPageCheck(
                                         FlsLoader_AddressType TargetAddress);
  /*
  Function FlsLoader_lDFlashCheck
  Input Parameters: TargetAddress
  */
LOCAL_INLINE boolean FlsLoader_lDFlashCheck(
                                     FlsLoader_AddressType TargetAddress);
  /*
  Function FlsLoader_lDFlashAddressCheck
  Input Parameters: TargetAddress
  */
LOCAL_INLINE uint8 FlsLoader_lDFlashAddressCheck(
                                           FlsLoader_AddressType TargetAddress);
  /*
  Function FlsLoader_lDFlashLengthCheck
  Input Parameters: TargetAddress,Length
  */
LOCAL_INLINE uint8 FlsLoader_lDFlashLengthCheck(
      FlsLoader_LengthType NumberOfSectors,FlsLoader_AddressType TargetAddress);
    /*
  Function FlsLoader_lPFlashCheck
  Input Parameters: TargetAddress
  */
LOCAL_INLINE boolean FlsLoader_lPFlashCheck(
                                     FlsLoader_AddressType TargetAddress);
  /*
  Function FlsLoader_lPFlashAddressCheck
  Input Parameters: TargetAddress
  */
LOCAL_INLINE uint8 FlsLoader_lPFlashAddressCheck(FlsLoader_LengthType Len,
                                           FlsLoader_AddressType TargetAddress);
  /*
  Function FlsLoader_lDFlashPageCheck
  Input Parameters: TargetAddress,Length
  */
LOCAL_INLINE boolean FlsLoader_lDFlashPageCheck(
                 FlsLoader_AddressType TargetAddress,
                 FlsLoader_LengthType Length);

LOCAL_INLINE uint32 FlsLoader_lCheckBitStatus(const uint32 *StartAddress,
                                              uint32 first, uint32 Last);

LOCAL_INLINE uint32 FlsLoader_lSectorNumber(uint32 Offset, uint32 FlashBank);
#endif

#if (FLSLOADER_ENABLE_LOCKCHECK == STD_ON)
LOCAL_INLINE FlsLoader_ReturnType FlsLoader_lPFlashSectorCheck (
                        FlsLoader_AddressType TargetAddress,
                        FlsLoader_LengthType Length,uint32 FlashType);

LOCAL_INLINE uint8 FlsLoader_lCheckProtStatus(const uint32 *StartAddress,
                                              uint32 Length, uint32 First);

LOCAL_INLINE FlsLoader_ReturnType FlsLoader_lSectorProtCheck(
                        uint32 FlashType,
                        uint32 SectorNumber,
                        FlsLoader_LengthType Length );
#endif
#define FLSLOADER_STOP_SEC_WRITE_CODE
/* MISRA2012_RULE_4_10_JUSTIFICATION: Flsloader_Memmap.h is repeatedly included
 * without include guard. This is as per AUTOSAR */
/* MISRA2012_RULE_20_1_JUSTIFICATION: declaration of 'FlsLoader_PFlashOffset'
 * before #include memap.h - Accepted deviation in AUTOSAR */
#include "MemMap.h"

#define FLSLOADER_START_SEC_CODE
/* MISRA2012_RULE_4_10_JUSTIFICATION: Flsloader_Memmap.h is repeatedly included
 * without include guard. This is as per AUTOSAR */
/* MISRA2012_RULE_20_1_JUSTIFICATION: declaration of 'FlsLoader_PFlashOffset'
 * before #include memap.h - Accepted deviation in AUTOSAR */
#include "MemMap.h"

#if (FLSLOADER_LOCK_UNLOCK_API == STD_ON)
LOCAL_INLINE FlsLoader_ReturnType  FlsLoader_lLockCmdCycles(
                        FlsLoader_AddressType StartAddress,
                        FlsLoader_AddressType UcbSectorAddress,
                        const FlsLoader_AddressType *PdataPtr);
                         
LOCAL_INLINE FlsLoader_ReturnType FlsLoader_lLockCmdCyclesWrite(
                        FlsLoader_AddressType StartAddress,
                        FlsLoader_AddressType UcbSectorAddress,
                        const FlsLoader_AddressType *PdataPtr);
#endif
#define FLSLOADER_STOP_SEC_CODE
/* MISRA2012_RULE_4_10_JUSTIFICATION: Flsloader_Memmap.h is repeatedly included
 * without include guard. This is as per AUTOSAR */
/* MISRA2012_RULE_20_1_JUSTIFICATION: declaration of 'FlsLoader_PFlashOffset'
 * before #include memap.h - Accepted deviation in AUTOSAR */
#include "MemMap.h"

#define FLSLOADER_START_SEC_WRITE_CODE
/* MISRA2012_RULE_4_10_JUSTIFICATION: Flsloader_Memmap.h is repeatedly included
 * without include guard. This is as per AUTOSAR */
/* MISRA2012_RULE_20_1_JUSTIFICATION: declaration of 'FlsLoader_PFlashOffset'
 * before #include memap.h - Accepted deviation in AUTOSAR */
#include "MemMap.h"
/*******************************************************************************
** Syntax           : FlsLoader_ReturnType FlsLoader_lProtSeqOperErrorCheck( **
**                      uint32 Module, uint32 FlashType                       **
**                    )                                                       **
**                                                                            **
** Service ID       : None                                                    **
**                                                                            **
** Sync/Async       : Synchronous                                             **
**                                                                            **
** Reentrancy       : non - reentrant                                         **
**                                                                            **
** Parameters(in)   :                                                         **
**                                                                            **
** Parameters (out) : None                                                    **
**                                                                            **
** Return value     : value: RetError                                         **
**                                                                            **
** Description      : This function checks for protection, sequence, program, **
**                    and operational error occurred or not                   **
*******************************************************************************/
FlsLoader_ReturnType FlsLoader_lProtSeqOperErrorCheck(void)
{
  FlsLoader_ReturnType  RetError;
  volatile uint32 FsrErrcheck;

  RetError = FLSLOADER_E_OK;
  /* MISRA2012_RULE_11_4_JUSTIFICATION: SFR access */
  FsrErrcheck = ((uint32)DMU_HF_ERRSR.U & \
                 ((uint32)FLSLOADER_PROER_SQER_OPER_ERROR));
  if ((FsrErrcheck & FLSLOADER_OPER_ERROR)== FLSLOADER_OPER_ERROR)
  {
    RetError = FLSLOADER_E_NOT_OK;
  }
  else if ((FsrErrcheck & FLSLOADER_SQER_ERROR)== FLSLOADER_SQER_ERROR)
  {
    RetError = FLSLOADER_E_NOT_OK;
  }
  else if ((FsrErrcheck & FLSLOADER_PROER_ERROR)== FLSLOADER_PROER_ERROR)
  {
    RetError = FLSLOADER_E_LOCKED;
  }
  else
  {
    /* do nothing */
  }
  return RetError;
}
#define FLSLOADER_STOP_SEC_WRITE_CODE
/* MISRA2012_RULE_4_10_JUSTIFICATION: Flsloader_Memmap.h is repeatedly included
 * without include guard. This is as per AUTOSAR */
/* MISRA2012_RULE_20_1_JUSTIFICATION: declaration of 'FlsLoader_PFlashOffset'
 * before #include memap.h - Accepted deviation in AUTOSAR */
#include "MemMap.h"

/******************************************************************************
**                      Private Variable Definitions                         **
******************************************************************************/

/*******************************************************************************
**                      Global Function Definitions                           **
*******************************************************************************/

  /*Memory Map of the FlsLoader Code*/
#define FLSLOADER_START_SEC_CODE
/* MISRA2012_RULE_4_10_JUSTIFICATION: Flsloader_Memmap.h is repeatedly included
 * without include guard. This is as per AUTOSAR */
/* MISRA2012_RULE_20_1_JUSTIFICATION: declaration of 'FlsLoader_PFlashOffset'
 * before #include memap.h - Accepted deviation in AUTOSAR */
#include "MemMap.h"

#if (FLSLOADER_LOCK_UNLOCK_API == STD_ON)
/*******************************************************************************
** Syntax           : FlsLoader_ReturnType FlsLoader_lLock(void)              **
**                                                                            **
** Service ID       :   NA                                                    **
**                                                                            **
** Sync/Async       : Synchronous                                             **
**                                                                            **
** Reentrancy       : non - reentrant                                         **
**                                                                            **
** Parameters (in)  : none                                                    **
**                                                                            **
** Parameters (out) :                                                         **
** Return value     : FlsLoader_ReturnType                                    **
**                                                                            **
** Description      : This function Locks the required profile and called     **
**                    from Lock API.                                          **
**                                                                            **
*******************************************************************************/
 FlsLoader_ReturnType FlsLoader_lLock(void)
{
  FlsLoader_ReturnType RetError;
  #if (FLSLOADER_DF0_PROT != NO_PROTECTION)
  FlsLoader_ReturnType RetErrorDF;
  #endif /*(FLSLOADER_DF0_PROT != NO_PROTECTION)*/

  #if FLASH_OTP_OWP_PROTECTION_TRUE
  uint8 LoopCount;
  #endif

  #if FLASH_PROTECTION_TRUE
  FlsLoader_AddressType StartAddress;
  FlsLoader_AddressType UcbSectorAddress;
  const FlsLoader_AddressType *PdataPtr ;
  StartAddress = FLSLOADER_DFLASH0_START_ADDRESS;
  #endif  /*FLASH_PROTECTION_TRUE*/

  #if FLASH_PROTECTION_FALSE
  RetError = FLSLOADER_E_OK;
  #else

  /* Call the LOCK function for each type of protection*/
  /* Check if write or Read protection is Enabled on PF0/PF1 configuration*/
  #if FLASH_READ_WRITE_PTOTECTION_TRUE
  /*PFLASH protection */
  UcbSectorAddress = FLSLOADER_UCB_PFLASH_ORGINAL_START;
  /*MISRA2012_RULE_11_8_JUSTIFICATION: "PdataPtr" attempt to cast away
  volatile in terms of pointer access*/
  /*MISRA2012_RULE_11_5_JUSTIFICATION: "PdataPtr" attempt to cast away
  volatile in terms of pointer access*/
  /*MISRA2012_RULE_11_3_JUSTIFICATION: "PdataPtr" attempt to cast away
  volatile in terms of pointer access*/
  PdataPtr = (FlsLoader_AddressType *)(void*)(&FlsLoader_UcbPFlashPage0[0]);
  RetError = FlsLoader_lLockCmdCycles(StartAddress,UcbSectorAddress,PdataPtr );

  /* update UCB_PFLASH_COPY */
  UcbSectorAddress = FLSLOADER_UCB_PFLASH_COPY_START;
  RetError |= FlsLoader_lLockCmdCycles(StartAddress,UcbSectorAddress,PdataPtr);
  #endif

  #if FLASH_OTP_OWP_PROTECTION_TRUE
    /* update OTP0 */
    UcbSectorAddress = FLSLOADER_UCB_OTP0_START;
    /*MISRA2012_RULE_11_8_JUSTIFICATION: "PdataPtr" attempt to cast away
    volatile in terms of pointer access*/
    /*MISRA2012_RULE_11_5_JUSTIFICATION: "PdataPtr" attempt to cast away
    volatile in terms of pointer access*/
    /*MISRA2012_RULE_11_3_JUSTIFICATION: "PdataPtr" attempt to cast away
    volatile in terms of pointer access*/
    PdataPtr = (FlsLoader_AddressType *)(void*)(&FlsLoader_UcbOTPFlashPage0[0]);
    /* There are 8*2 sets of OTP original and copy configuration */
    for(LoopCount = 0U;
        (LoopCount < (FLSLOADER_NUM_8*FLSLOADER_NUM_2));
        LoopCount++)
    {
      RetError |= FlsLoader_lLockCmdCycles(StartAddress,
                                              UcbSectorAddress,
                                              PdataPtr);
      /*MISRA2012_RULE_13_2_JUSTIFICATION: The Pointers are type-cast to uint32
       *for address comparison/calculation purpose*/
      UcbSectorAddress+=FLSLOADER_UCB_OTP0_SIZE;
      if (RetError != FLSLOADER_E_OK)
      {
        break;
      }
    }

  #endif /*FLASH_READ_WRITE_PTOTECTION_TRUE*/

  /* End of Check for WR or READ protection on PF0/PF1 '*/

  /* Check for DF0 write or Read protection  */
  #if (FLSLOADER_DF0_PROT != NO_PROTECTION)
  /* DFLASH original protection */
  UcbSectorAddress = FLSLOADER_UCB_DFLASH_ORIGINAL_START;
  /*MISRA2012_RULE_11_6_JUSTIFICATION: "FlsLoader_UcbDFlashPage0" attempt to
  cast away const in terms of pointer access.*/
  /* MISRA2012_RULE_11_4_JUSTIFICATION: "FlsLoader_UcbDFlashPage0" attempt to
  cast away const in terms of pointer access.*/
  /* MISRA2012_RULE_11_5_JUSTIFICATION: "FlsLoader_UcbDFlashPage0" attempt to
  cast away const in terms of pointer access.*/
  /* MISRA2012_RULE_11_3_JUSTIFICATION: "FlsLoader_UcbDFlashPage0" attempt to
  cast away const in terms of pointer access.*/
  PdataPtr = (FlsLoader_AddressType *)((void*)FlsLoader_UcbDFlashPage0[0]);
  RetErrorDF = FlsLoader_lLockCmdCycles(StartAddress,UcbSectorAddress,
               PdataPtr);

  /* DFLASH Copy protection */
  UcbSectorAddress = FLSLOADER_UCB_DFLASH_COPY_START;
  RetErrorDF |= FlsLoader_lLockCmdCycles(StartAddress,UcbSectorAddress,
               PdataPtr);

  #if FLASH_PROTECTION_TRUE
  if(RetError == FLSLOADER_E_OK)
  #endif /* FLASH_PROTECTION_TRUE*/
  {
    RetError = RetErrorDF;
  }
  #endif /*(FLSLOADER_DF0_PROT != NO_PROTECTION)*/
    
  #endif /*FLASH_PROTECTION_FALSE*/

  return RetError;
}

/*******************************************************************************
** Syntax   :  LOCAL_INLINE FlsLoader_ReturnType FlsLoader_lLockCmdCycles(**
**                      FlsLoader_AddressType TargetAddress ,                 **
**                        FlsLoader_AddressType UcbSectorAddress,             **
**                        FlashLoader_DataType* PdataPtr                      **
**                    )                                                       **
**                                                                            **
** Service ID       :   NA                                                    **
**                                                                            **
** Sync/Async       : Synchronous                                             **
**                                                                            **
** Reentrancy       : non - reentrant                                         **
**                                                                            **
** Parameters (in)  : none                                                    **
**                                                                            **
** Parameters (out) :                                                         **
** Return value     : FlsLoader_ReturnType                                    **
**                                                                            **
** Description      : This function Locks the required profile and called     **
**                    from Lock  API.                                         **
**                                                                            **
*******************************************************************************/
LOCAL_INLINE FlsLoader_ReturnType FlsLoader_lLockCmdCycles(
                        FlsLoader_AddressType StartAddress,
                        FlsLoader_AddressType UcbSectorAddress,
                        const FlsLoader_AddressType *PdataPtr)
{
  FlsLoader_ReturnType  RetError;
  volatile uint32       BusyCheck;
  uint32                InnerCount;
  uint32                Icr;
  volatile uint32       FlashFsr;
  
  /* Enter Critical Section */
  Icr = FlsLoader_lDisableInts();

  /* Erase the corresponding User Configuraiton Block */
  /* cycle 1 */
  /*MISRA2012_RULE_11_6_JUSTIFICATION: FlsLoader_AddressType is defined of
  type volatile uint32 to avoid compiler optimization in command cycles*/
  /*MISRA2012_RULE_11_2_JUSTIFICATION: The Pointers are type-cast to uint32
  for address comparison/calculation purpose.*/
  /*MISRA2012_RULE_13_2_JUSTIFICATION: The Pointers are type-cast to uint32
   *for address comparison/calculation purpose*/
  /*MISRA2012_RULE_1_3_JUSTIFICATION: The Pointers are type-cast to uint32
   *for address comparison/calculation purpose*/
  /*MISRA2012_RULE_10_8_JUSTIFICATION: The Pointers are type-cast to
   *uint32 for address comparison/calculation purpose*/
  /* MISRA2012_RULE_11_4_JUSTIFICATION: SFR access */
  *((FlsLoader_AddressType*)FLSLOADER_GET_CYCLE_AA50(StartAddress))  = 
                                                             UcbSectorAddress;
  /* cycle 2 */
  /*MISRA2012_RULE_11_6_JUSTIFICATION: FlsLoader_AddressType is defined of
  type volatile uint32 to avoid compiler optimization in command cycles*/
  /*MISRA2012_RULE_11_2_JUSTIFICATION: The Pointers are type-cast to uint32
  for address comparison/calculation purpose.*/
  /*MISRA2012_RULE_13_2_JUSTIFICATION: The Pointers are type-cast to uint32
   *for address comparison/calculation purpose*/
  /*MISRA2012_RULE_1_3_JUSTIFICATION: The Pointers are type-cast to uint32
   *for address comparison/calculation purpose*/
  /*MISRA2012_RULE_10_8_JUSTIFICATION: The Pointers are type-cast to
   *uint32 for address comparison/calculation purpose*/
  /* MISRA2012_RULE_11_4_JUSTIFICATION: SFR access */
  *((FlsLoader_AddressType*)FLSLOADER_GET_CYCLE_AA58(StartAddress))  = 
                                                    FLSLOADER_NUM_UCB_SECTORS;
  /* cycle 3 */
  /*MISRA2012_RULE_11_6_JUSTIFICATION: FlsLoader_AddressType is defined of
  type volatile uint32 to avoid compiler optimization in command cycles*/
  /*MISRA2012_RULE_11_2_JUSTIFICATION: The Pointers are type-cast to uint32
  for address comparison/calculation purpose.*/
  /*MISRA2012_RULE_13_2_JUSTIFICATION: The Pointers are type-cast to uint32
   *for address comparison/calculation purpose*/
  /*MISRA2012_RULE_1_3_JUSTIFICATION: The Pointers are type-cast to uint32
   *for address comparison/calculation purpose*/
  /*MISRA2012_RULE_10_8_JUSTIFICATION: The Pointers are type-cast to
   *uint32 for address comparison/calculation purpose*/
  /* MISRA2012_RULE_11_4_JUSTIFICATION: SFR access */
  *((FlsLoader_AddressType*)FLSLOADER_GET_CYCLE_AAA8(StartAddress))  = 
                                                           FLSLOADER_VALUE_80;
  /* cycle 4 */
  /*MISRA2012_RULE_11_6_JUSTIFICATION: FlsLoader_AddressType is defined of
  type volatile uint32 to avoid compiler optimization in command cycles*/
  /*MISRA2012_RULE_11_2_JUSTIFICATION: The Pointers are type-cast to uint32
  for address comparison/calculation purpose.*/
  /*MISRA2012_RULE_13_2_JUSTIFICATION: The Pointers are type-cast to uint32
   *for address comparison/calculation purpose*/
  /*MISRA2012_RULE_1_3_JUSTIFICATION: The Pointers are type-cast to uint32
   *for address comparison/calculation purpose*/
  /*MISRA2012_RULE_10_8_JUSTIFICATION: The Pointers are type-cast to
   *uint32 for address comparison/calculation purpose*/
  /* MISRA2012_RULE_11_4_JUSTIFICATION: SFR access */
  *((FlsLoader_AddressType*)FLSLOADER_GET_CYCLE_AAA8(StartAddress))  = 
                                                           FLSLOADER_VALUE_50;

  InnerCount = 0U;
  /* MISRA2012_RULE_11_4_JUSTIFICATION: SFR access */
  FlashFsr = DMU_HF_OPERATION.B.ERASE;

  while((FlashFsr != FLSLOADER_BIT_SET) &&
        (InnerCount < FLSLOADER_CMDCYCLE_TIMEOUT))
  {
    InnerCount++;
    /* MISRA2012_RULE_11_4_JUSTIFICATION: SFR access */
    FlashFsr = DMU_HF_OPERATION.B.ERASE;
    #if (FLSLOADER_CALLOUT_FUNC == STD_ON)
    FlsLoader_lCalloutFunction(InnerCount);
    #endif
  }
  if(InnerCount < FLSLOADER_CMDCYCLE_TIMEOUT)
  {
    /* Check for FLASH BUSY flag */
    /* PnBUSY and D0BUSY */
    InnerCount = 0U;
    /* MISRA2012_RULE_11_4_JUSTIFICATION: SFR access */
    BusyCheck = (DMU_HF_STATUS.U & (uint32)FLSLOADER_DFLASH0_BUSY);

    while(( BusyCheck != 0U) && 
          (InnerCount < FLSLOADER_BUSY_TIMEOUT))
    {
      InnerCount++;
      /* MISRA2012_RULE_11_4_JUSTIFICATION: SFR access */
      BusyCheck = (DMU_HF_STATUS.U & (uint32)FLSLOADER_DFLASH0_BUSY);
#if (FLSLOADER_CALLOUT_FUNC == STD_ON)
      FlsLoader_lCalloutFunction(InnerCount);
#endif
    }
    if (InnerCount < FLSLOADER_BUSY_TIMEOUT )
    {
      /* This check makes sure that  erase operation is requested,
      No protection error and no sequence error has occurred. */
      
      /* This check makes sure No protection error and no sequence error
      and No operation error has occurred.*/
      RetError = FlsLoader_lProtSeqOperErrorCheck();
    }
    else
    {
      RetError = FLSLOADER_E_NOT_OK;
    }
  }
  else
  {
    RetError = FLSLOADER_E_NOT_OK;
  }
  /*MISRA2012_RULE_11_6_JUSTIFICATION: FlsLoader_AddressType is defined of
  type volatile uint32 to avoid compiler optimization in command cycles*/
  /*MISRA2012_RULE_11_2_JUSTIFICATION: The Pointers are type-cast to uint32
  for address comparison/calculation purpose.*/
  /*MISRA2012_RULE_13_2_JUSTIFICATION: The Pointers are type-cast to uint32
   *for address comparison/calculation purpose*/
  /*MISRA2012_RULE_1_3_JUSTIFICATION: The Pointers are type-cast to uint32
   *for address comparison/calculation purpose*/
  /*MISRA2012_RULE_10_8_JUSTIFICATION: The Pointers are type-cast to
   *uint32 for address comparison/calculation purpose*/
  /* MISRA2012_RULE_11_4_JUSTIFICATION: SFR access */
  *((FlsLoader_AddressType*)FlsLoader_lClearStatus(StartAddress)) = 
                                                           FLSLOADER_VALUE_FA;
  /* Enter Critical Section */
  FlsLoader_lEnableInts(Icr);
  /* Erase is completed now program 16 pages of UCB in Page mode. */
  /* Enter Critical Section */
  Icr = FlsLoader_lDisableInts();
  if (RetError == FLSLOADER_E_OK)
  {
      RetError = FlsLoader_lLockCmdCyclesWrite(StartAddress,
                               UcbSectorAddress,PdataPtr);
  }
  /* Exit Crtical Section */
  FlsLoader_lEnableInts(Icr);
  return RetError;
}
/*******************************************************************************
** Syntax   :  LOCAL_INLINE FlsLoader_ReturnType                          **
**                                FlsLoader_lLockCmdCyclesWrite(              **
**                                FlsLoader_AddressType TargetAddress ,       **
**                                FlsLoader_AddressType UcbSectorAddress,     **
**                                const FlashLoader_DataType* PdataPtr        **
**                                )                                           **
**                                                                            **
** Service ID       :   NA                                                    **
**                                                                            **
** Sync/Async       : Synchronous                                             **
**                                                                            **
** Reentrancy       : non - reentrant                                         **
**                                                                            **
** Parameters (in)  : none                                                    **
**                                                                            **
** Parameters (out) :                                                         **
** Return value     : FlsLoader_ReturnType                                    **
**                                                                            **
** Description      : This function Locks the required profile and called     **
**                    from Lock  API.                                         **
**                                                                            **
*******************************************************************************/
LOCAL_INLINE FlsLoader_ReturnType FlsLoader_lLockCmdCyclesWrite(
                         FlsLoader_AddressType StartAddress,
                         FlsLoader_AddressType UcbSectorAddress,
                         const FlsLoader_AddressType *PdataPtr)
{
  FlsLoader_ReturnType    RetError;
  uint32                  Count;
  uint32                  InCount;
  volatile uint32         FlashBusyStat;
  volatile uint32         BusyCheck;
  FlsLoader_AddressType   *LoadPageAddress;
  RetError = FLSLOADER_E_OK;
  
  for (Count = 0U; 
      (Count < FLSLOADER_NUM_UCB_PAGES) && (RetError == FLSLOADER_E_OK);
       Count++)
  {
    /* Enter the Page Mode */
    /*MISRA2012_RULE_11_6_JUSTIFICATION: FlsLoader_AddressType is defined of
    type volatile uint32 to avoid compiler optimization in command cycles*/
    /*MISRA2012_RULE_11_2_JUSTIFICATION: The Pointers are type-cast to uint32
    for address comparison/calculation purpose.*/
    /*MISRA2012_RULE_13_2_JUSTIFICATION: The Pointers are type-cast to uint32
     *for address comparison/calculation purpose*/
    /*MISRA2012_RULE_1_3_JUSTIFICATION: The Pointers are type-cast to uint32
     *for address comparison/calculation purpose*/
    /*MISRA2012_RULE_10_8_JUSTIFICATION: The Pointers are type-cast to
     *uint32 for address comparison/calculation purpose*/
    /* MISRA2012_RULE_11_4_JUSTIFICATION: SFR access */
    *((FlsLoader_AddressType*)FlsLoader_lEnterPageMode(StartAddress)) =
                                             FLSLOADER_DFLASH_VAL;
  
    InCount = 0U;
    /* MISRA2012_RULE_11_4_JUSTIFICATION: SFR access */
    FlashBusyStat = DMU_HF_STATUS.B.DFPAGE;

    /* Check if Program Flash is in page mode */
    while((FlashBusyStat != FLSLOADER_BIT_SET) && 
         (InCount < FLSLOADER_CMDCYCLE_TIMEOUT))
    {
      InCount++;
      /* MISRA2012_RULE_11_4_JUSTIFICATION: SFR access */
      FlashBusyStat = DMU_HF_STATUS.B.DFPAGE;
#if (FLSLOADER_CALLOUT_FUNC == STD_ON)
      FlsLoader_lCalloutFunction(InCount);
#endif
    }

    /* Check PFPAGE/DFPAGE bit was SET */
    if(InCount < FLSLOADER_CMDCYCLE_TIMEOUT)
    {
      /* Load the data */
      /*MISRA2012_RULE_11_6_JUSTIFICATION: FlsLoader_AddressType is defined of
      type volatile uint32 to avoid compiler optimization in command cycles*/
      /*MISRA2012_RULE_11_2_JUSTIFICATION: The Pointers are type-cast to uint32
      for address comparison/calculation purpose.*/
      /*MISRA2012_RULE_13_2_JUSTIFICATION: The Pointers are type-cast to uint32
       *for address comparison/calculation purpose*/
      /*MISRA2012_RULE_1_3_JUSTIFICATION: The Pointers are type-cast to uint32
       *for address comparison/calculation purpose*/
      /*MISRA2012_RULE_10_8_JUSTIFICATION: The Pointers are type-cast to
       *uint32 for address comparison/calculation purpose*/
      /* MISRA2012_RULE_11_4_JUSTIFICATION: SFR access */
      LoadPageAddress = \
                 (FlsLoader_AddressType *)FlsLoader_lLoadPage(StartAddress);
      *LoadPageAddress = *PdataPtr;
      /*MISRA2012_RULE_18_4_JUSTIFICATION: Pointer arithmetic is used to
      access user buffer efficiently*/
      *(LoadPageAddress + 1U) = *(PdataPtr + 1U);
      /*MISRA2012_RULE_18_4_JUSTIFICATION: Pointer arithmetic is used to
      access user buffer efficiently*/
      PdataPtr += FLSLOADER_NUM_2;
      /* Load Page register gets incremented automatically. */
      /* cycle 1 */
      /*MISRA2012_RULE_11_6_JUSTIFICATION: FlsLoader_AddressType is defined of
      type volatile uint32 to avoid compiler optimization in command cycles*/
      /*MISRA2012_RULE_11_2_JUSTIFICATION: The Pointers are type-cast to uint32
      for address comparison/calculation purpose.*/
      /*MISRA2012_RULE_13_2_JUSTIFICATION: The Pointers are type-cast to uint32
       *for address comparison/calculation purpose*/
      /*MISRA2012_RULE_1_3_JUSTIFICATION: The Pointers are type-cast to uint32
       *for address comparison/calculation purpose*/
      /*MISRA2012_RULE_10_8_JUSTIFICATION: The Pointers are type-cast to
       *uint32 for address comparison/calculation purpose*/
      /* MISRA2012_RULE_11_4_JUSTIFICATION: SFR access */
      *((FlsLoader_AddressType*)FLSLOADER_GET_CYCLE_AA50(StartAddress))
                                    = UcbSectorAddress;
      /* cycle 2 */
      /*MISRA2012_RULE_11_6_JUSTIFICATION: FlsLoader_AddressType is defined of
      type volatile uint32 to avoid compiler optimization in command cycles*/
      /*MISRA2012_RULE_11_2_JUSTIFICATION: The Pointers are type-cast to uint32
      for address comparison/calculation purpose.*/
      /*MISRA2012_RULE_13_2_JUSTIFICATION: The Pointers are type-cast to uint32
       *for address comparison/calculation purpose*/
      /*MISRA2012_RULE_1_3_JUSTIFICATION: The Pointers are type-cast to uint32
       *for address comparison/calculation purpose*/
      /*MISRA2012_RULE_10_8_JUSTIFICATION: The Pointers are type-cast to
       *uint32 for address comparison/calculation purpose*/
      /* MISRA2012_RULE_11_4_JUSTIFICATION: SFR access */
       *((FlsLoader_AddressType*)FLSLOADER_GET_CYCLE_AA58(StartAddress))
                                    =  FLSLOADER_VALUE_00;
      /* cycle 3 */
       /*MISRA2012_RULE_11_6_JUSTIFICATION: FlsLoader_AddressType is defined of
       type volatile uint32 to avoid compiler optimization in command cycles*/
       /*MISRA2012_RULE_11_2_JUSTIFICATION: The Pointers are type-cast to uint32
       for address comparison/calculation purpose.*/
       /*MISRA2012_RULE_13_2_JUSTIFICATION: The Pointers are type-cast to uint32
        *for address comparison/calculation purpose*/
       /*MISRA2012_RULE_1_3_JUSTIFICATION: The Pointers are type-cast to uint32
        *for address comparison/calculation purpose*/
       /*MISRA2012_RULE_10_8_JUSTIFICATION: The Pointers are type-cast to
        *uint32 for address comparison/calculation purpose*/
       /* MISRA2012_RULE_11_4_JUSTIFICATION: SFR access */
        *((FlsLoader_AddressType*)FLSLOADER_GET_CYCLE_AAA8(StartAddress))
                                    =  FLSLOADER_VALUE_A0;
      /*cycle 4 */
        /*MISRA2012_RULE_11_6_JUSTIFICATION: FlsLoader_AddressType is defined of
        type volatile uint32 to avoid compiler optimization in command cycles*/
      /*MISRA2012_RULE_11_2_JUSTIFICATION: The Pointers are type-cast to uint32
      for address comparison/calculation purpose.*/
      /*MISRA2012_RULE_13_2_JUSTIFICATION: The Pointers are type-cast to uint32
         *for address comparison/calculation purpose*/
        /*MISRA2012_RULE_1_3_JUSTIFICATION: The Pointers are type-cast to uint32
         *for address comparison/calculation purpose*/
        /*MISRA2012_RULE_10_8_JUSTIFICATION: The Pointers are type-cast to
         *uint32 for address comparison/calculation purpose*/
        /* MISRA2012_RULE_11_4_JUSTIFICATION: SFR access */
      *((FlsLoader_AddressType*)FLSLOADER_GET_CYCLE_AAA8(StartAddress))
                                    = FLSLOADER_VALUE_AA;
      InCount = 0U;
      /* MISRA2012_RULE_11_4_JUSTIFICATION: SFR access */
      FlashBusyStat = DMU_HF_OPERATION.B.PROG;

      while((FlashBusyStat != FLSLOADER_BIT_SET) &&
            (InCount < FLSLOADER_CMDCYCLE_TIMEOUT))
      {
        InCount++;
        /* MISRA2012_RULE_11_4_JUSTIFICATION: SFR access */
        FlashBusyStat = DMU_HF_OPERATION.B.PROG;
#if (FLSLOADER_CALLOUT_FUNC == STD_ON)
        FlsLoader_lCalloutFunction(InCount);
#endif
      }
      if (InCount < FLSLOADER_CMDCYCLE_TIMEOUT)
      {
        /* Check for FLASH BUSY flag */
        InCount = 0U;
        /* MISRA2012_RULE_11_4_JUSTIFICATION: SFR access */
        BusyCheck = (DMU_HF_STATUS.B.D0BUSY);

        while((BusyCheck != 0U)&& 
             (InCount < FLSLOADER_BUSY_TIMEOUT))
        {
          InCount++;
          /* MISRA2012_RULE_11_4_JUSTIFICATION: SFR access */
          BusyCheck = (DMU_HF_STATUS.B.D0BUSY);
#if (FLSLOADER_CALLOUT_FUNC == STD_ON)
          FlsLoader_lCalloutFunction(InCount);
#endif
        }
        if (InCount < FLSLOADER_BUSY_TIMEOUT )
        {
          /* This check makes sure No protection error and no sequence error
          and No operation error has occurred.*/
          RetError = FlsLoader_lProtSeqOperErrorCheck();
        }
        else
        {
          RetError = FLSLOADER_E_NOT_OK;
        }
      }
      else
      {
        RetError = FLSLOADER_E_NOT_OK;
      }
      /* Clear the status if the operation is successful.*/
      /*MISRA2012_RULE_11_6_JUSTIFICATION: FlsLoader_AddressType is defined of
      type volatile uint32 to avoid compiler optimization in command cycles*/
      /*MISRA2012_RULE_11_2_JUSTIFICATION: The Pointers are type-cast to uint32
      for address comparison/calculation purpose.*/
      /*MISRA2012_RULE_13_2_JUSTIFICATION: The Pointers are type-cast to uint32
       *for address comparison/calculation purpose*/
      /*MISRA2012_RULE_1_3_JUSTIFICATION: The Pointers are type-cast to uint32
       *for address comparison/calculation purpose*/
      /*MISRA2012_RULE_10_8_JUSTIFICATION: The Pointers are type-cast to
       *uint32 for address comparison/calculation purpose*/
      /* MISRA2012_RULE_11_4_JUSTIFICATION: SFR access */
      *((FlsLoader_AddressType*)FlsLoader_lClearStatus(StartAddress))
                                    =  FLSLOADER_VALUE_FA;
      
      /* Iterate the TargetAddress to the next page Address */
      /*MISRA2012_RULE_17_8_JUSTIFICATION: Pointer arithmetic is used to
      access UCB buffer efficiently*/
      UcbSectorAddress = UcbSectorAddress + FLSLOADER_PAGE_SIZE;
      
    }  /* End of InCount < FLSLOADER_CMDCYCLE_TIMEOUT*/
    else
    {
      RetError = FLSLOADER_E_NOT_OK;
    }
  }  /* End of For Loop */
  return RetError;
}

#endif  /* #if (FLSLOADER_LOCK_UNLOCK_API == STD_ON)*/

/*******************************************************************************
** Syntax :           FlsLoader_ReturnType FlsLoader_lCheckOTPWOP(void)       **
**                                                                            **
** Service ID       : None                                                    **
**                                                                            **
** Sync/Async       : Synchronous                                             **
**                                                                            **
** Reentrancy       : non - reentrant                                         **
**                                                                            **
** Parameters(in)   : none                                                    **
**                                                                            **
** Parameters (out) : none                                                    **
**                                                                            **
** Return value     : FLSLOADER_E_OK                                          **
**                    FLSLOADER_E_ROMVERSION                                  **
**                                                                            **
** Description      : This function checks whether all the sectors have been  **
**                    protected under OTP and WOP                             **
*******************************************************************************/
FlsLoader_ReturnType FlsLoader_lCheckOTPWOP(void)
{
  FlsLoader_ReturnType  RetError;
  uint32 FlsOTPCheck;
  uint32 FlsWOPCheck;
  uint32 * OtpAddress;
  uint32 * WopAddress;

  uint8 FlsIndex = 0;
  RetError = FLSLOADER_E_OK;

  for(FlsIndex =0; FlsIndex < (uint8)FLSLOADER_NUM_OF_PFLASH_BANK; FlsIndex++)
  {
      /* Check OTP register of all the sectors */
      uint32 FlsSector = (uint8)FlsLoader_PFlashSectorCount[FlsIndex];

      FlsOTPCheck = FLSLOADER_PROCON_CHECK;
      FlsWOPCheck = FLSLOADER_PROCON_CHECK;
      /*MISRA2012_RULE_11_8_JUSTIFICATION: "OtpAddress" attempt to cast away
      volatile in terms of pointer access*/
      /*MISRA2012_RULE_11_5_JUSTIFICATION: "OtpAddress" attempt to cast away
      volatile in terms of pointer access*/
      /*MISRA2012_RULE_11_3_JUSTIFICATION: "OtpAddress" attempt to cast away
      volatile in terms of pointer access*/
      /* MISRA2012_RULE_11_4_JUSTIFICATION: SFR access */
      OtpAddress = (uint32 *)&(MODULE_DMU.HP[FlsIndex].PROCON_OTP0.U);
      /*MISRA2012_RULE_11_8_JUSTIFICATION: "WopAddress" attempt to cast away
      volatile in terms of pointer access*/
      /*MISRA2012_RULE_11_5_JUSTIFICATION: "WopAddress" attempt to cast away
      volatile in terms of pointer access*/
      /*MISRA2012_RULE_11_3_JUSTIFICATION: "WopAddress" attempt to cast away
      volatile in terms of pointer access*/
      /* MISRA2012_RULE_11_4_JUSTIFICATION: SFR access */
      WopAddress = (uint32 *)&(MODULE_DMU.HP[FlsIndex].PROCON_WOP0.U);

      while(FlsSector != 0U)
      {
        /* Check OTP status of the all the register */
        FlsOTPCheck &= *OtpAddress;
        OtpAddress++;
        /* Check WOP status of the all the register */
        FlsWOPCheck &= *WopAddress;
        WopAddress++;
        FlsSector -=FLSLOADER_DECREMENT_BY_32;
      }

      if((FlsOTPCheck != FLSLOADER_PROCON_CHECK) &&
         (FlsWOPCheck != FLSLOADER_PROCON_CHECK))
      {
          break;
      }
  }

  if (FlsIndex == FLSLOADER_NUM_OF_PFLASH_BANK)
  {
      /* All sectors of all the banks are either WOP or OTP protected */
      RetError = FLSLOADER_E_ROMVERSION;
  }

  return RetError;
  /*MISRA2012_RULE_8_13_JUSTIFICATION: OtpAddress is a SFR access,
   * Accepted deviation in AUTOSAR*/
  /*MISRA2012_RULE_8_13_JUSTIFICATION: WopAddress is a SFR access,
   * Accepted deviation in AUTOSAR*/
}

#define FLSLOADER_STOP_SEC_CODE
/* MISRA2012_RULE_4_10_JUSTIFICATION: Flsloader_Memmap.h is repeatedly included
 * without include guard. This is as per AUTOSAR */
/* MISRA2012_RULE_20_1_JUSTIFICATION: declaration of 'FlsLoader_PFlashOffset'
 * before #include memap.h - Accepted deviation in AUTOSAR */
#include "MemMap.h"

#define FLSLOADER_START_SEC_WRITE_CODE
/* MISRA2012_RULE_4_10_JUSTIFICATION: Flsloader_Memmap.h is repeatedly included
 * without include guard. This is as per AUTOSAR */
/* MISRA2012_RULE_20_1_JUSTIFICATION: declaration of 'FlsLoader_PFlashOffset'
 * before #include memap.h - Accepted deviation in AUTOSAR */
#include "MemMap.h"
/*******************************************************************************
** Syntax :           LOCAL_INLINE uint32 FlsLoader_lSectorNumber(        **
**                      uint32 Offset                                         **
**                    )                                                       **
**                                                                            **
** Service ID       : None                                                    **
**                                                                            **
** Sync/Async       : Synchronous                                             **
**                                                                            **
** Reentrancy       : non - reentrant                                         **
**                                                                            **
** Parameters(in)   : offset: PFLASH0/1 Offset address                        **
**                                                                            **
** Parameters (out) : none                                                    **
**                                                                            **
** Return value     : SectorNumber                                            **
**                                                                            **
** Description      : This function will return the sector number             **
*******************************************************************************/
LOCAL_INLINE uint32 FlsLoader_lSectorNumber(uint32 Offset, uint32 FlashBank)
{
  uint32 SectorNumber;
  uint32 TotalSectros = (uint32)FlsLoader_PFlashSectorCount[FlashBank];

  for(SectorNumber = 0U;
      SectorNumber < TotalSectros;
      SectorNumber++)
  {
    if((SectorNumber * FLSLOADER_PF_SECTOR_SIZE) == Offset)
    {
      break;
    }
  }

  if(SectorNumber == (uint32)TotalSectros)
  {
    SectorNumber = FLSLOADER_INV;
  }

  return SectorNumber;
}

#if (FLSLOADER_DEV_ERROR_DETECT == STD_ON)
/*******************************************************************************
** Syntax           :  FlsLoader_ReturnType FlsLoader_lWriteDetCheck(         **
**                      FlsLoader_LengthType Length,                          **
**                      FlsLoader_AddressType TargetAddress                   **
**                    )                                                       **
**                                                                            **
** Service ID       : None                                                    **
**                                                                            **
** Sync/Async       : Synchronous                                             **
**                                                                            **
** Reentrancy       : non - reentrant                                         **
**                                                                            **
** Parameters(in)   : Length :Length of the data                              **
**                    TargetAddress :Destination Address in Flash             **
**                                                                            **
** Parameters (out) : none                                                    **
**                                                                            **
** Return value     : RetError                                                **
**                                                                            **
** Description      : This function is DET Check function for                 **
**                    FlsLoader_lWrite                                        **
*******************************************************************************/
FlsLoader_ReturnType FlsLoader_lWriteDetCheck( FlsLoader_LengthType Length,
                                           FlsLoader_AddressType TargetAddress)
{
  uint8                     ErrorHook;
  FlsLoader_ReturnType      RetError;
  FlsLoader_LengthType      TargetEnd;

  /* Init RetError to OK */
  RetError = FLSLOADER_E_OK;

  /* check for Init DET */
  if (FlsLoader_InitStatus != FLSLOADER_INITIALIZED)
  {
    /* Report missing initialization DET */
    Det_ReportError(FLSLOADER_MODULE_ID,
                    FLSLOADER_INSTANCE_ID,
                    FLSLOADER_SID_WRITE,
                    FLSLOADER_E_UNINIT);
    RetError = FLSLOADER_E_NOT_OK;
  }

  /* Check of TargetAddress
  TargetAddress can be multiple of 256 bytes in case of PFLASH or 32 bytes.
  in case of DFLASH. */
  /* Report Invalid TargetAddress to DET */
  if ( RetError != FLSLOADER_E_NOT_OK)
  {
    ErrorHook = FlsLoader_lAddressPageCheck(TargetAddress);
    if  (0U == ErrorHook)
    {
        Det_ReportError(FLSLOADER_MODULE_ID,
                        FLSLOADER_INSTANCE_ID,
                        FLSLOADER_SID_WRITE,
                        FLSLOADER_E_PARAM_ADDRESS);

        RetError = FLSLOADER_E_NOT_OK;
    }
  }

  if ( RetError != FLSLOADER_E_NOT_OK)
  {
  /* Returns true if, position is DFLASH address */
  if (FlsLoader_lCheckFlashType(TargetAddress) == TRUE)
  {
    /* Given TargetAddress and Length should not exceed the flash
     * boundary.*/
    /* Its Data Flash assign,Report invalid Length to DET */
    if (FlsLoader_lDFlashPageCheck(TargetAddress,Length) == FLSLOADER_TRUE)
    {
        Det_ReportError(FLSLOADER_MODULE_ID,
                        FLSLOADER_INSTANCE_ID,
                        FLSLOADER_SID_WRITE,
                        FLSLOADER_E_PARAM_LENGTH);

        RetError = FLSLOADER_E_NOT_OK;
    }
  }
  else  /*PFlash*/
  {
      TargetEnd = (Length + TargetAddress) - 1U;

      if ((Length == (FlsLoader_LengthType)0U) ||
         ((Length & ((FlsLoader_LengthType)FLSLOADER_MOD_32)) != 0U))
      {
          Det_ReportError(FLSLOADER_MODULE_ID,
                          FLSLOADER_INSTANCE_ID,
                          FLSLOADER_SID_WRITE,
                          FLSLOADER_E_PARAM_LENGTH);

          RetError = FLSLOADER_E_NOT_OK;
      }
      else if(TargetEnd > (FlsLoader_LengthType)FLSLOADER_PFLASH5_END)
      {
          Det_ReportError(FLSLOADER_MODULE_ID,
                          FLSLOADER_INSTANCE_ID,
                          FLSLOADER_SID_WRITE,
                          FLSLOADER_E_PARAM_LENGTH);

          RetError = FLSLOADER_E_NOT_OK;
      }
      else
      {
      /* dummy else */
      }
  }
  }
  return RetError;
}
/*******************************************************************************
** Syntax           :  FlsLoader_ReturnType FlsLoader_lEraseDetCheck(         **
**                      FlsLoader_LengthType NumberOfSectors,                 **
**                      FlsLoader_AddressType TargetAddress                   **
**                    )                                                       **
**                                                                            **
** Service ID       : None                                                    **
**                                                                            **
** Sync/Async       : Synchronous                                             **
**                                                                            **
** Reentrancy       : non - reentrant                                         **
**                                                                            **
** Parameters(in)   : NumberOfSectors :Number of sectors to be erased         **
**                    TargetAddress :Destination Address in Flash             **
**                                                                            **
** Parameters (out) : none                                                    **
**                                                                            **
** Return value     : RetError                                                **
**                                                                            **
** Description      : This function is DET Check  for FlsLoader_Erase         **
*******************************************************************************/
FlsLoader_ReturnType FlsLoader_lEraseDetCheck(
                                      FlsLoader_LengthType NumberOfSectors,
                                      FlsLoader_AddressType TargetAddress)
{
  FlsLoader_ReturnType  RetError;
  uint8                 ErrorHook;

  RetError = FLSLOADER_E_OK;
  if (FlsLoader_InitStatus != FLSLOADER_INITIALIZED)
  {
    /* CD_FlsLoader039: Report missing initilization to DET */
    Det_ReportError(FLSLOADER_MODULE_ID,
                    FLSLOADER_INSTANCE_ID,
                    FLSLOADER_SID_ERASE,
                    FLSLOADER_E_UNINIT);
    RetError = FLSLOADER_E_NOT_OK;
  }
  else
  {
    /* CD_FlsLoader041: Report invalid TargetAddress to DET */
    if (FlsLoader_lCheckFlashType(TargetAddress) == TRUE)
    {  /* Check for DFLASH Address*/
      if (FlsLoader_lDFlashCheck(TargetAddress) == FLSLOADER_TRUE)
      {
        ErrorHook = FlsLoader_lDFlashAddressCheck(TargetAddress);
        if  (0U == ErrorHook)
        {
          Det_ReportError(FLSLOADER_MODULE_ID,
                          FLSLOADER_INSTANCE_ID,
                          FLSLOADER_SID_ERASE,
                          FLSLOADER_E_PARAM_ADDRESS);
          RetError = FLSLOADER_E_NOT_OK;
        }
      }
      if (RetError != FLSLOADER_E_NOT_OK)
      {
        ErrorHook = FlsLoader_lDFlashLengthCheck(NumberOfSectors,TargetAddress);
        if(0U == ErrorHook)
        {
          Det_ReportError(FLSLOADER_MODULE_ID,
                          FLSLOADER_INSTANCE_ID,
                          FLSLOADER_SID_ERASE,
                          FLSLOADER_E_PARAM_LENGTH);
          RetError = FLSLOADER_E_NOT_OK;
        }
      }
    }
    else
    {
      /* Check for PFLASH Address.*/
      /*MISRA2012_RULE_13_2_JUSTIFICATION: The Pointers are type-cast to
       uint32 for address comparison/calculation purpose*/
      if(TargetAddress < FLSLOADER_PFLASH0_START_ADDRESS)
      {
        Det_ReportError(FLSLOADER_MODULE_ID,
                        FLSLOADER_INSTANCE_ID,
                        FLSLOADER_SID_ERASE,
                        FLSLOADER_E_PARAM_ADDRESS);
        RetError = FLSLOADER_E_NOT_OK;
      }
      /*MISRA2012_RULE_13_2_JUSTIFICATION: The Pointers are type-cast to
       uint32 for address comparison/calculation purpose*/
      else if(TargetAddress > FLSLOADER_PFLASH5_END)
      {
        Det_ReportError(FLSLOADER_MODULE_ID,
                      FLSLOADER_INSTANCE_ID,
                      FLSLOADER_SID_ERASE,
                      FLSLOADER_E_PARAM_ADDRESS);
        RetError = FLSLOADER_E_NOT_OK;
      }
      else
      {
        ErrorHook = FlsLoader_lPFlashAddressCheck(NumberOfSectors,\
                                                  TargetAddress);

        if  (0U == ErrorHook)
        {
          Det_ReportError(FLSLOADER_MODULE_ID,
                          FLSLOADER_INSTANCE_ID,
                          FLSLOADER_SID_ERASE,
                          FLSLOADER_E_PARAM_ADDRESS);

          RetError = FLSLOADER_E_NOT_OK;
        }
      }
    }/* end of if check FlashType */
  }
  return RetError;
} 
/*******************************************************************************
** Syntax   :   LOCAL_INLINE uint8 FlsLoader_lAddressPageCheck(           **
**                      FlsLoader_AddressType TargetAddress                   **
**                    )                                                       **
**                                                                            **
** Service ID       : None                                                    **
**                                                                            **
** Sync/Async       : Synchronous                                             **
**                                                                            **
** Reentrancy       : non - reentrant                                         **
**                                                                            **
** Parameters(in)   : TargetAddress : Address passed                          **
**                                                                            **
** Parameters (out) : None                                                    **
**                                                                            **
** Return value     : RetVal                                                  **
**                                                                            **
** Description      : This function returns the give TargetAddress last two   **
**                    nibbles are zero value                                  **
*******************************************************************************/
LOCAL_INLINE uint8 FlsLoader_lAddressPageCheck(
                                           FlsLoader_AddressType TargetAddress)
{
  uint8     RetVal;
  /* Init ErrorHook to false */
  RetVal = 0U;
  /* Check of TargetAddress
  TargetAddress can be multiple of 256 bytes or 32 bytes. */
  /* CD_FlsLoader036 :Report Invalid TargetAddress to DET */
  if (FlsLoader_lPFlashCheck(TargetAddress) == FLSLOADER_TRUE)
  {
    /* First byte is already checked, last two nibbles must be zero for 256
       byte address*/
    /*MISRA2012_RULE_11_6_JUSTIFICATION: FlsLoader_AddressType is defined of
    type volatile uint32 to avoid compiler optimization in command cycles*/
    /*MISRA2012_RULE_11_2_JUSTIFICATION: The Pointers are type-cast to
    uint32 for address comparison/calculation purpose.*/
    /*MISRA2012_RULE_13_2_JUSTIFICATION: The Pointers are type-cast to
     uint32 for address comparison/calculation purpose*/
    /*MISRA2012_RULE_1_3_JUSTIFICATION: The Pointers are type-cast to uint32
     *for address comparison/calculation purpose*/
    /*MISRA2012_RULE_10_8_JUSTIFICATION: The Pointers are type-cast to
     *uint32 for address comparison/calculation purpose*/
    /* MISRA2012_RULE_11_4_JUSTIFICATION: SFR access */
    if ((TargetAddress & (FlsLoader_AddressType)FLSLOADER_MOD_32) == \
                                                          FLSLOADER_POSITION_0 )
    {
      RetVal = 1U; /* valid sector Address */
    }
  }
  else
  {
    if (FlsLoader_lDFlashCheck(TargetAddress) == FLSLOADER_TRUE)
    {
      /*MISRA2012_RULE_11_6_JUSTIFICATION: FlsLoader_AddressType is defined of
      type volatile uint32 to avoid compiler optimization in command cycles*/
      /*MISRA2012_RULE_11_2_JUSTIFICATION: The Pointers are type-cast to
      uint32 for address comparison/calculation purpose.*/
      /*MISRA2012_RULE_13_2_JUSTIFICATION: The Pointers are type-cast to
       uint32 for address comparison/calculation purpose*/
      /*MISRA2012_RULE_1_3_JUSTIFICATION: The Pointers are type-cast to uint32
       *for address comparison/calculation purpose*/
      /*MISRA2012_RULE_10_8_JUSTIFICATION: The Pointers are type-cast to
       *uint32 for address comparison/calculation purpose*/
      /* MISRA2012_RULE_11_4_JUSTIFICATION: SFR access */
      if ( (TargetAddress & (FlsLoader_AddressType)FLSLOADER_MOD_8) == \
                                                          FLSLOADER_POSITION_0 )
      {
        RetVal = 1U;
      }
    }
  } /* end of if TargetAddress check */
  return RetVal;
}
/*******************************************************************************
** Syntax           :  LOCAL_INLINE boolean FlsLoader_lDFlashCheck(       **
**                                       FlsLoader_AddressType TargetAddress) **
**                                                                            **
** Service ID       : None                                                    **
**                                                                            **
** Sync/Async       : Synchronous                                             **
**                                                                            **
** Reentrancy       : non - reentrant                                         **
**                                                                            **
** Parameters(in)   : TargetAddress : Address passed                          **
**                                                                            **
** Parameters (out) : None                                                    **
**                                                                            **
** Return value     : RetVal                                                  **
**                                                                            **
** Description      : Checks that TargetAddress is within DFLASH Address Range**
*******************************************************************************/
LOCAL_INLINE boolean FlsLoader_lDFlashCheck(
                                            FlsLoader_AddressType TargetAddress)
{
  boolean RetVal;
  RetVal  = FALSE;

  /*MISRA2012_RULE_13_2_JUSTIFICATION: The Pointers are type-cast to
   uint32 for address comparison/calculation purpose*/
  if(TargetAddress >= FLSLOADER_DFLASH0_START_ADDRESS)
  {
    /*MISRA2012_RULE_13_2_JUSTIFICATION: The Pointers are type-cast to
     uint32 for address comparison/calculation purpose*/
    if(TargetAddress <= FLSLOADER_DFLASH0_END)
    {
      RetVal = TRUE;
    }
  }
  /*MISRA2012_RULE_13_2_JUSTIFICATION: The Pointers are type-cast to
   uint32 for address comparison/calculation purpose*/
  if(TargetAddress >= FLSLOADER_UCB_START)
  {
    /*MISRA2012_RULE_13_2_JUSTIFICATION: The Pointers are type-cast to
     uint32 for address comparison/calculation purpose*/
    if(TargetAddress <= FLSLOADER_UCB_END)
    {
        RetVal = TRUE;
    }
  }
  return RetVal;
}

/*******************************************************************************
** Syntax   :   LOCAL_INLINE uint8 FlsLoader_lDFlashAddressCheck(         **
**                      FlsLoader_AddressType TargetAddress                   **
**                    )                                                       **
**                                                                            **
** Service ID       : None                                                    **
**                                                                            **
** Sync/Async       : Synchronous                                             **
**                                                                            **
** Reentrancy       : non - reentrant                                         **
**                                                                            **
** Parameters(in)   : TargetAddress : Address passed                          **
**                                                                            **
** Parameters (out) : None                                                    **
**                                                                            **
** Return value     : RetVal                                                  **
**                                                                            **
** Description      : This function returns if the given TargetAddress        **
**                    matches the start of DF_EEPROM or DF_UCB sector address **
*******************************************************************************/
LOCAL_INLINE uint8 FlsLoader_lDFlashAddressCheck(
                                           FlsLoader_AddressType TargetAddress)
{
  uint16               DfSegment;
  uint8                RetVal;
  RetVal = 0U;
  DfSegment = (uint16)(TargetAddress >> FLSLOADER_SHIFT_BY_20);
  if (DfSegment == FLSLOADER_DF_EEPROM_SEGMENT)
  {
    /*MISRA2012_RULE_13_2_JUSTIFICATION: The Pointers are type-cast to
     uint32 for address comparison/calculation purpose*/
    if ((TargetAddress & (FlsLoader_AddressType)FLSLOADER_EEPROM_SECTOR_SIZE) \
        == FLSLOADER_POSITION_0)
    {
      RetVal = 1U; /*Valid DF_EEPROM Start Sector Address */
    }
  }
  else if (DfSegment == FLSLOADER_DF_UCB_SEGMENT)
  {
    /*MISRA2012_RULE_13_2_JUSTIFICATION: The Pointers are type-cast to
     uint32 for address comparison/calculation purpose*/
    if ((TargetAddress & (FlsLoader_AddressType)FLSLOADER_UCB_SECTOR_SIZE_1) \
        == FLSLOADER_POSITION_0)
    {
      RetVal = 1U; /*Valid DF_UCB Start Sector Address */
    }
  }
  else
  {
    RetVal = 0U;
  }
  return RetVal;
}
/*******************************************************************************
** Syntax   :   LOCAL_INLINE uint8 FlsLoader_lDFlashLengthCheck(              **
**                      FlsLoader_LengthType NumberOfSectors,                 **
**                      FlsLoader_AddressType TargetAddress                   **
**                    )                                                       **
**                                                                            **
** Service ID       : None                                                    **
**                                                                            **
** Sync/Async       : Synchronous                                             **
**                                                                            **
** Reentrancy       : non - reentrant                                         **
**                                                                            **
** Parameters(in)   : TargetAddress  : Address passed                         **
**                    NumberOfSectors: Length of the data                     **
** Parameters (out) : None                                                    **
**                                                                            **
** Return value     : RetVal                                                  **
**                                                                            **
** Description      : This function returns if the given Length               **
**                    is within DF_EEPROM or DF_UCB range                     **
*******************************************************************************/
LOCAL_INLINE uint8 FlsLoader_lDFlashLengthCheck(
       FlsLoader_LengthType NumberOfSectors,FlsLoader_AddressType TargetAddress)
{
  uint32               DFLengthCheck;
  uint16               DfSegment;
  uint8                RetVal;
  
  RetVal = 1U;
  DfSegment = (uint16)(TargetAddress >> FLSLOADER_SHIFT_BY_20);
  if (NumberOfSectors == 0U)
  {
    RetVal = 0U;
  }
  if (DfSegment == FLSLOADER_DF_EEPROM_SEGMENT)
  {
    /*MISRA2012_RULE_13_2_JUSTIFICATION: The Pointers are type-cast to
     uint32 for address comparison/calculation purpose*/

    DFLengthCheck = ((uint32)(TargetAddress + (FlsLoader_AddressType)\
                             (NumberOfSectors * FLSLOADER_DFLASH_SECTOR_SIZE)))\
                             -1U;

    if ( DFLengthCheck > FLSLOADER_DFLASH0_END )
    {
      RetVal = 0U; /*InValid DF_EEPROM Sector Length */
    }
  }
  if (DfSegment == FLSLOADER_DF_UCB_SEGMENT)
  {
    /*MISRA2012_RULE_13_2_JUSTIFICATION: The Pointers are type-cast to
     uint32 for address comparison/calculation purpose*/
    DFLengthCheck = ((uint32)(TargetAddress + (FlsLoader_AddressType) \
                             (NumberOfSectors * FLSLOADER_UCB_SECTOR_SIZE)))-1U;
    if ( DFLengthCheck > FLSLOADER_UCB_END )
    {
      RetVal = 0U; /*InValid DF_EEPROM Sector Length */
    }
  }
  return RetVal;
}
/*******************************************************************************
** Syntax           :  LOCAL_INLINE boolean FlsLoader_lPFlashCheck(       **
**                                       FlsLoader_AddressType TargetAddress) **
**                                                                            **
** Service ID       : None                                                    **
**                                                                            **
** Sync/Async       : Synchronous                                             **
**                                                                            **
** Reentrancy       : non - reentrant                                         **
**                                                                            **
** Parameters(in)   : TargetAddress                                           **
**                                                                            **
** Parameters (out) : None                                                    **
**                                                                            **
** Return value     :  RetVal                                                 **
**                                                                            **
** Description      :Checks that TargetAddress is within PFLASH Address Range **
*******************************************************************************/
LOCAL_INLINE boolean FlsLoader_lPFlashCheck(
                         FlsLoader_AddressType TargetAddress)
{
  boolean RetVal;
  RetVal = FALSE;
  /*MISRA2012_RULE_13_2_JUSTIFICATION: The Pointers are type-cast to
   uint32 for address comparison/calculation purpose*/
  if(TargetAddress >= FLSLOADER_PFLASH0_START_ADDRESS)
  {
    /*MISRA2012_RULE_13_2_JUSTIFICATION: The Pointers are type-cast to
     uint32 for address comparison/calculation purpose*/
    if(TargetAddress <= FLSLOADER_PFLASH5_END)
    {
      RetVal = TRUE;
    }
  }
   return RetVal;
}

/*******************************************************************************
** Syntax   :   LOCAL_INLINE uint8 FlsLoader_lPFlashAddressCheck(         **
**                      FlsLoader_AddressType TargetAddress                   **
**                    )                                                       **
**                                                                            **
** Service ID       : None                                                    **
**                                                                            **
** Sync/Async       : Synchronous                                             **
**                                                                            **
** Reentrancy       : non - reentrant                                         **
**                                                                            **
** Parameters(in)   : TargetAddress : Address passed                          **
**                                                                            **
** Parameters (out) : None                                                    **
**                                                                            **
** Return value     :  RetVal                                                 **
**                                                                            **
** Description      : This function returns if the given TargetAddress        **
**                    matches the start PFlash sector start address           **
*******************************************************************************/
LOCAL_INLINE uint8 FlsLoader_lPFlashAddressCheck(
                                           FlsLoader_LengthType Len,
                                           FlsLoader_AddressType TargetAddress)
{
  uint8     RetVal = 0x01;
  uint32    Offset;
  uint32    SectorNumber;
  uint8     NoOfSectors;
  uint32    FlashBank;


  FlashBank = FlsLoader_lGetFlashType(TargetAddress);
  NoOfSectors = FlsLoader_PFlashSectorCount[FlashBank];

  Offset = TargetAddress - FlsLoader_PFlashOffset[FlashBank];

  SectorNumber = FlsLoader_lSectorNumber(Offset, FlashBank);

  if(SectorNumber == FLSLOADER_INV)
  {
    /* Target address is not the start address of a sector */
    RetVal = 0x00; /*Error*/
  }
  else
  {
    /* Check if affected number of sectors are more than the available one */
    if ((Len == 0U)||
       ((SectorNumber + Len) > NoOfSectors))
    {
      RetVal = 0x00;
    }
  }

  return RetVal;
}

/*******************************************************************************
** Syntax           :  LOCAL_INLINE boolean FlsLoader_lDFlashPageCheck(   **
**                                       FlsLoader_AddressType TargetAddress, **
                                         FlsLoader_LengthType Length )        **
**                                                                            **
** Service ID       : None                                                    **
**                                                                            **
** Sync/Async       : Synchronous                                             **
**                                                                            **
** Reentrancy       : non - reentrant                                         **
**                                                                            **
** Parameters(in)   : TargetAddress, Length                                   **
**                                                                            **
** Parameters (out) : None                                                    **
**                                                                            **
** Return value     : boolean                                                 **
**                    TRUE = Not OK -length and address are not in DF range   **
**                    FALSE = OK- Lenght and address are in range             **
**                                                                            **
** Description      : Checks the length for DFlash operation                  **
*******************************************************************************/
LOCAL_INLINE boolean FlsLoader_lDFlashPageCheck(
                FlsLoader_AddressType TargetAddress,FlsLoader_LengthType Length)
{
  boolean                   RetVal;
  uint16                    DfSegment;
  FlsLoader_LengthType      TargetEnd;
  RetVal   = FALSE;
  
  if ((Length) == (FlsLoader_LengthType)0U)
  {
    RetVal = TRUE;
  }
  else if (((Length) & ((FlsLoader_LengthType)FLSLOADER_MOD_8)) != 0U)
  {
    RetVal = TRUE;
  }
  else
  {
    /* Check address is in EEPROM Segment or in UCB segment */
    DfSegment = (uint16)(TargetAddress >> FLSLOADER_SHIFT_BY_20);
    /*MISRA2012_RULE_13_2_JUSTIFICATION: The Pointers are type-cast to
     uint32 for address comparison/calculation purpose*/
    if (DfSegment == FLSLOADER_DF_EEPROM_SEGMENT)
    {
      /*MISRA2012_RULE_13_2_JUSTIFICATION: The Pointers are type-cast to
       uint32 for address comparison/calculation purpose*/
      TargetEnd = (Length+(TargetAddress & FLSLOADER_DFLASH0_ADDRESS_MASK))-1U;
      if (TargetEnd > (FlsLoader_LengthType)FLSLOADER_EEPROM_OFFSETEND)
      {
          RetVal = TRUE;
      }
    }
    /*MISRA2012_RULE_13_2_JUSTIFICATION: The Pointers are type-cast to
     uint32 for address comparison/calculation purpose*/
    else if (DfSegment == FLSLOADER_DF_UCB_SEGMENT)
    {
      /*MISRA2012_RULE_13_2_JUSTIFICATION: The Pointers are type-cast to
       uint32 for address comparison/calculation purpose*/
      TargetEnd = (Length+(TargetAddress & FLSLOADER_UCB_ADDRESS_MASK))-1U;
      if (TargetEnd > (FlsLoader_LengthType)FLSLOADER_UCB_ADDRESS_MASK)
      {
          RetVal = TRUE;
      }
    }
    else
    {
      RetVal = TRUE;
    }
  }
  return RetVal;
}
#endif /* #if (FLSLOADER_DEV_ERROR_DETECT == STD_ON) */

/*******************************************************************************
** Syntax           :  uint32 FlsLoader_lGetFlashType(                        **
**                                       FlsLoader_AddressType TargetAddress) **
                                                                              **
**                                                                            **
** Service ID       : None                                                    **
**                                                                            **
** Sync/Async       : Synchronous                                             **
**                                                                            **
** Reentrancy       : non - reentrant                                         **
**                                                                            **
** Parameters(in)   : TargetAddress                                           **
**                                                                            **
** Parameters (out) : None                                                    **
**                                                                            **
** Return value     : uint32 FlashType                                        **
**                                                                            **
** Description      : Checks the whether Flash is DFlash or Pflash            **
*******************************************************************************/
uint32 FlsLoader_lGetFlashType(FlsLoader_AddressType TargetAddress)
{
  uint32      Flash_Type;
  uint8       PfSegment;
  if (FlsLoader_lCheckFlashType(TargetAddress) == TRUE)
  {
      Flash_Type = FLSLOADER_DFLASH_BANK0;
  }
  else
  {
    /* Given Address belongs to PFLASH  */
    /* Address 7th Nibble | PFlash Bank */
    /* ---------------------------------*/
    /*  (0-2)             | PF0         */
    /*  (3-5)             | PF1         */
    /*  (6-8)             | PF2         */
    /*  (9-B)             | PF3         */
    /*  (C-E)             | PF4         */
    /*  (F)               | PF5         */


    PfSegment = (uint8)((TargetAddress >> FLSLOADER_SHIFT_BY_20)
                       & FLSLOADER_PFLASH_MASK);

    if (PfSegment == FLSLOADER_PFLASH5_MASK)
    {
      Flash_Type = FLSLOADER_PFLASH_BANK5;
    }
    else if (PfSegment >= FLSLOADER_PFLASH4_MASK)
    {
      Flash_Type = FLSLOADER_PFLASH_BANK4;
    }
    else if (PfSegment >= FLSLOADER_PFLASH3_MASK)
    {
      Flash_Type = FLSLOADER_PFLASH_BANK3;
    }
    else if (PfSegment >= FLSLOADER_PFLASH2_MASK)
    {
      Flash_Type = FLSLOADER_PFLASH_BANK2;
    }
    else if (PfSegment >= FLSLOADER_PFLASH1_MASK)
    {
      Flash_Type = FLSLOADER_PFLASH_BANK1;
    }
    else
    {
      Flash_Type = FLSLOADER_PFLASH_BANK0;
    }
  }
  return Flash_Type;
}
/*******************************************************************************
** Syntax           :  FlsLoader_ReturnType                                   **
**                     FlsLoader_lFlashLockCheck (                            **
**                                    FlsLoader_AddressType TargetAddress,    **
**                                    uint32 FlashType,                       **
**                                    FlsLoader_LengthType Length)            **
**                                                                            **
** Service ID       : NA                                                      **
**                                                                            **
** Sync/Async       : Synchronous                                             **
**                                                                            **
** Reentrancy       : non - reentrant                                         **
**                                                                            **
** Parameters (in)  : TargetAddress, FlashType, Length                        **
**                                                                            **
** Parameters (out) : None                                                    **
**                                                                            **
** Return value     : FlsLoader_ReturnType                                    **
**                                                                            **
** Description      : This function will return if the sector is protected    **
**                                                                            **
*******************************************************************************/
#if (FLSLOADER_ENABLE_LOCKCHECK == STD_ON)
FlsLoader_ReturnType FlsLoader_lFlashLockCheck (
                        FlsLoader_AddressType TargetAddress,uint32 FlashType,
                        FlsLoader_LengthType Length)
{
  volatile uint32                FlsFpro;
  volatile uint32                FlsFprod;
  volatile uint32                FlsProconp1;
  volatile uint32                FlsProcondrpro1;
  FlsLoader_ReturnType           RetError;
  
  RetError = FLSLOADER_E_OK;
  
  if (FlashType != FLSLOADER_DFLASH_BANK0)
  {
    /* PFlash */
    /* MISRA2012_RULE_11_4_JUSTIFICATION: SFR access */
    FlsFpro = DMU_HF_PROTECT.B.PRODISP;

    if (FlsFpro != 1U)
    {
      /* MISRA2012_RULE_11_4_JUSTIFICATION: SFR access */
      FlsProconp1 = DMU_HF_PROCONPF.B.RPRO;

      if (FlsProconp1 == 1U)
      {
        RetError = FLSLOADER_E_LOCKED;
      }
      else
      {
        RetError = FlsLoader_lPFlashSectorCheck(TargetAddress,Length,FlashType);
      }
    }
  }
  else
  {
    /*Check if global write protection is installed in DFLASH*/
    /* MISRA2012_RULE_11_4_JUSTIFICATION: SFR access */
    FlsFprod = DMU_HF_PROTECT.B.PRODISD;
    /* MISRA2012_RULE_11_4_JUSTIFICATION: SFR access */
    FlsProcondrpro1 = DMU_HF_PROCONDF.B.RPRO;

    if(FlsFprod != 1U)
    {
      if(FlsProcondrpro1 == 1U)
      {
        RetError = FLSLOADER_E_LOCKED;
      }
    }
  }
  return RetError;
}
/*******************************************************************************
** Syntax           :  FlsLoader_ReturnType                                   **
**                     FlsLoader_lPFlashSectorCheck (                         **
**                                       FlsLoader_AddressType TargetAddress, **
**                                       FlsLoader_LengthType Length,         **
**                                       uint32 FlashType)                    **
**                                                                            **
** Service ID       : NA                                                      **
**                                                                            **
** Sync/Async       : Synchronous                                             **
**                                                                            **
** Reentrancy       : non - reentrant                                         **
**                                                                            **
** Parameters (in)  : TargetAddress, Length                                   **
**                                                                            **
** Parameters (out) : None                                                    **
**                                                                            **
** Return value     : FlsLoader_ReturnType                                    **
**                                                                            **
** Description      : This function will return if the sector is protected    **
**                                                                            **
*******************************************************************************/
LOCAL_INLINE FlsLoader_ReturnType FlsLoader_lPFlashSectorCheck (
                          FlsLoader_AddressType TargetAddress,
                          FlsLoader_LengthType Length,uint32 FlashType)
{
  uint32            SectorNumber;
  uint32            SectorNumber1;
  uint32            SectorLength;
  uint8             SectorMask = 0;
  uint32            Offset;
  uint32            Offset1;
  FlsLoader_ReturnType  RetError = FLSLOADER_E_OK;
  /* MISRA2012_RULE_11_4_JUSTIFICATION: SFR access */
  /*MISRA2012_RULE_11_8_JUSTIFICATION: "OtpAddress" attempt to cast away
  volatile in terms of pointer access*/
  /*MISRA2012_RULE_11_3_JUSTIFICATION: "OtpAddress" attempt to cast away
  volatile in terms of pointer access*/
  const uint32   *FlsRegProconp0 = \
                              (uint32*)&(MODULE_DMU.HP_PROCON[FlashType].P0.U);

  uint8 NumberOfSector = FlsLoader_PFlashSectorCount[FlashType];
  /* Address offset within the sector */
  Offset = TargetAddress - FlsLoader_PFlashOffset[(uint8)FlashType];

  /* Let's find the start sector */
  for(SectorNumber = 0U; SectorNumber < NumberOfSector; SectorNumber++)
  {
      if(Offset < (FLSLOADER_PF_SECTOR_SIZE*SectorNumber))
      {
        break;
      }
  }

  SectorNumber--;
  /* Let's find the end sector+1 */
  /* MISRA2012_RULE_17_8_JUSTIFICATION: Used in pointer arithmetic operation
   *  Accepted deviation*/
  TargetAddress = TargetAddress + Length;
  Offset1 = TargetAddress - FlsLoader_PFlashOffset[(uint8)FlashType];

  for(SectorNumber1 = 0U; SectorNumber1 < NumberOfSector; SectorNumber1++)
  {
      if(Offset1 < (FLSLOADER_PF_SECTOR_SIZE*SectorNumber1))
      {
          break;
      }
  }

  SectorLength = SectorNumber1-SectorNumber;

  SectorMask = FlsLoader_lCheckProtStatus(FlsRegProconp0,\
                                          SectorLength,\
                                          SectorNumber);

  if(SectorMask != 0U)
  {
      RetError = FLSLOADER_E_LOCKED;
  }

  return RetError;
}
/*******************************************************************************
** Syntax           :  FlsLoader_ReturnType                                   **
**                     FlsLoader_lEraseLockCheck (                            **
**                                    FlsLoader_AddressType TargetAddress,    **
**                                    uint32 FlashType,                       **
**                                    FlsLoader_LengthType Length)            **
**                                                                            **
** Service ID       : NA                                                      **
**                                                                            **
** Sync/Async       : Synchronous                                             **
**                                                                            **
** Reentrancy       : non - reentrant                                         **
**                                                                            **
** Parameters (in)  : TargetAddress, FlashType, Length                        **
**                                                                            **
** Parameters (out) : None                                                    **
**                                                                            **
** Return value     : FlsLoader_ReturnType                                    **
**                                                                            **
** Description      : This function will return if the sector is protected    **
**                                                                            **
*******************************************************************************/
FlsLoader_ReturnType FlsLoader_lEraseLockCheck (
                          FlsLoader_AddressType TargetAddress,uint32 FlashType,
                          FlsLoader_LengthType Length)
{
  volatile uint32                FlsFproD;
  volatile uint32                FlsProcond2;
  volatile uint32                FlsProcondrpro2;
  volatile uint32                FlsFpro;
  volatile uint32                FlsProconp2;
  FlsLoader_ReturnType           RetError;
  uint32                         SectorNumber;
  uint32                         Offset;
   
  RetError = FLSLOADER_E_OK;
  /* Given Address belongs to Data FLASH */
  /*Check if the Target Address passed is UCB protected */
  /* Check if global write protection is installed in DFLASH*/
  if (FlashType == FLSLOADER_DFLASH_BANK0)
  {
    /* MISRA2012_RULE_11_4_JUSTIFICATION: SFR access */
    FlsFproD = DMU_HF_PROTECT.B.PRODISD;
    /* MISRA2012_RULE_11_4_JUSTIFICATION: SFR access */
    FlsProcond2 = DMU_HF_PROCONDF.B.L;
    /* MISRA2012_RULE_11_4_JUSTIFICATION: SFR access */
    FlsProcondrpro2 = DMU_HF_PROCONPF.B.RPRO;

    if (FlsFproD != 1U)
    {
      if(FlsProcond2 == 1U)
      {
        RetError = FLSLOADER_E_LOCKED;
      }
      if(FlsProcondrpro2 == 1U)
      {
        RetError = FLSLOADER_E_LOCKED;
      }
    }
  }
  else
  {
    /*Check if the Target Address passed is UCB protected */
    /* Protection Check Algorithm */
    /* Preprocessor switch to enable/disable the lockcheck functionality */
    /* Check if global write protection is installed */
    /* MISRA2012_RULE_11_4_JUSTIFICATION: SFR access */
    FlsFpro = DMU_HF_PROTECT.B.PRODISP;

    if(FlsFpro != 1U)
    {
      /* MISRA2012_RULE_11_4_JUSTIFICATION: SFR access */
      FlsProconp2 = DMU_HF_PROCONPF.B.RPRO;

      if (FlsProconp2 == 1U)
      {
        RetError = FLSLOADER_E_LOCKED;
      }
      else
      {
        Offset = TargetAddress - FlsLoader_PFlashOffset[FlashType];
        SectorNumber = FlsLoader_lSectorNumber(Offset, FlashType);
        RetError = FlsLoader_lSectorProtCheck(FlashType, SectorNumber, Length);
      }
    }
  }
  return RetError;
}

/*******************************************************************************
** Syntax           :  FlsLoader_ReturnType  FlsLoader_lSectorProtCheck(      **
**                      uint32 FlashType,uint32 SectorNumber,                 **
**                      FlsLoader_LengthType Length )                         **
**                    )                                                       **
**                                                                            **
** Service ID       : None                                                    **
**                                                                            **
** Sync/Async       : Synchronous                                             **
**                                                                            **
** Reentrancy       : non - reentrant                                         **
**                                                                            **
** Parameters(in)   :                                                         **
**                    SectorNumber : Sector Number                            **
**                    FlashType : PFLASH0 / PFLASH1/PFLASH2/PFLASH3           **
**                                                                            **
** Parameters (out) : None                                                    **
**                                                                            **
** Return value     : FlsLoader_ReturnType                                    **
**                                                                            **
** Description      : This function returns sector locked or not.             **
*******************************************************************************/
LOCAL_INLINE FlsLoader_ReturnType FlsLoader_lSectorProtCheck(
                               uint32 FlashType,
                               uint32 SectorNumber,FlsLoader_LengthType Length )
{
  uint8 RetProtError  = 0;
  uint8 RetOtpError   = 0;
  uint8 RetWopError   = 0;

  FlsLoader_ReturnType RetError = FLSLOADER_E_OK;
  /*MISRA2012_RULE_19_2_JUSTIFICATION: Union used for register type
       definition */
  volatile Ifx_DMU_HP_PROCON_P0           *FlsRegProconp;
  /*MISRA2012_RULE_19_2_JUSTIFICATION: Union used for register type
       definition */
  volatile Ifx_DMU_HP_PROCON_WOP0         *FlsRegProconWop;
  /*MISRA2012_RULE_19_2_JUSTIFICATION: Union used for register type
       definition */
  volatile Ifx_DMU_HP_PROCON_OTP0         *FlsRegProconOtp;

  if(SectorNumber != FLSLOADER_INV)
  {
    /* Find out the base address of protection registers */
    if (FlashType == FLSLOADER_PFLASH_BANK5)
    {
      /* MISRA2012_RULE_11_4_JUSTIFICATION: SFR access */
      FlsRegProconp =   &(DMU_HP_PROCON5_P0);
      /* MISRA2012_RULE_11_4_JUSTIFICATION: SFR access */
      FlsRegProconOtp = &(DMU_HP_PROCON5_OTP0);
      /* MISRA2012_RULE_11_4_JUSTIFICATION: SFR access */
      FlsRegProconWop = &(DMU_HP_PROCON5_WOP0);
    }
    else if (FlashType == FLSLOADER_PFLASH_BANK4)
    {
      /* MISRA2012_RULE_11_4_JUSTIFICATION: SFR access */
      FlsRegProconp = &(DMU_HP_PROCON4_P0);
      /* MISRA2012_RULE_11_4_JUSTIFICATION: SFR access */
      FlsRegProconOtp = &(DMU_HP_PROCON4_OTP0);
      /* MISRA2012_RULE_11_4_JUSTIFICATION: SFR access */
      FlsRegProconWop = &(DMU_HP_PROCON4_WOP0);
    }
    else if (FlashType == FLSLOADER_PFLASH_BANK3)
    {
      /* MISRA2012_RULE_11_4_JUSTIFICATION: SFR access */
      FlsRegProconp = &(DMU_HP_PROCON3_P0);
      /* MISRA2012_RULE_11_4_JUSTIFICATION: SFR access */
      FlsRegProconOtp = &(DMU_HP_PROCON3_OTP0);
      /* MISRA2012_RULE_11_4_JUSTIFICATION: SFR access */
      FlsRegProconWop = &(DMU_HP_PROCON3_WOP0);
      /* MISRA2012_RULE_11_4_JUSTIFICATION: SFR access */
    }
    else if (FlashType == FLSLOADER_PFLASH_BANK2)
    {
      /* MISRA2012_RULE_11_4_JUSTIFICATION: SFR access */
      FlsRegProconp = &(DMU_HP_PROCON2_P0);
      /* MISRA2012_RULE_11_4_JUSTIFICATION: SFR access */
      FlsRegProconOtp = &(DMU_HP_PROCON2_OTP0);
      /* MISRA2012_RULE_11_4_JUSTIFICATION: SFR access */
      FlsRegProconWop = &(DMU_HP_PROCON2_WOP0);
    }
    else if (FlashType == FLSLOADER_PFLASH_BANK1)
    {
      /* MISRA2012_RULE_11_4_JUSTIFICATION: SFR access */
      FlsRegProconp = &(DMU_HP_PROCON1_P0);
      /* MISRA2012_RULE_11_4_JUSTIFICATION: SFR access */
      FlsRegProconOtp = &(DMU_HP_PROCON1_OTP0);
      /* MISRA2012_RULE_11_4_JUSTIFICATION: SFR access */
      FlsRegProconWop = &(DMU_HP_PROCON1_WOP0);
    }
    else
    {
      /* MISRA2012_RULE_11_4_JUSTIFICATION: SFR access */
      FlsRegProconp = &(DMU_HP_PROCON0_P0);
      /* MISRA2012_RULE_11_4_JUSTIFICATION: SFR access */
      FlsRegProconOtp = &(DMU_HP_PROCON0_OTP0);
      /* MISRA2012_RULE_11_4_JUSTIFICATION: SFR access */
      FlsRegProconWop = &(DMU_HP_PROCON0_WOP0);
    }
    /* MISRA2012_RULE_11_3_JUSTIFICATION: SFR access */
    RetProtError =  FlsLoader_lCheckProtStatus( (uint32*)FlsRegProconp,\
                                                Length,SectorNumber);
    /* MISRA2012_RULE_11_3_JUSTIFICATION: SFR access */
    RetOtpError =  FlsLoader_lCheckProtStatus( (uint32*)FlsRegProconOtp,\
                                                Length,SectorNumber );
    /* MISRA2012_RULE_11_3_JUSTIFICATION: SFR access */
    RetWopError =  FlsLoader_lCheckProtStatus( (uint32*)FlsRegProconWop,\
                                                Length,SectorNumber );

    if((RetProtError == (uint8)0x01U) ||
       (RetOtpError  == (uint8)0x01U) ||
       (RetWopError  == (uint8)0x01U))
    {
      /* Sectors are locked */
      RetError = FLSLOADER_E_NOT_OK;
    }
    else
    {
      /* Sectors are not locked */
      RetError = FLSLOADER_E_OK;
    }

  }
  else
  {
    RetError = FLSLOADER_E_NOT_OK;
  }
  return RetError;
  /*MISRA2012_RULE_8_13_JUSTIFICATION: FlsRegProconOtp is a SFR access,
   * Accepted deviation in AUTOSAR*/
  /*MISRA2012_RULE_8_13_JUSTIFICATION: FlsRegProconp is a SFR access,
   * Accepted deviation in AUTOSAR*/
  /*MISRA2012_RULE_8_13_JUSTIFICATION: FlsRegProconWop is a SFR access,
   * Accepted deviation in AUTOSAR*/
}

#endif

/*******************************************************************************
** Syntax           :  uint32  FlsLoader_lCheckBitStatus(                     **
**                      const uint32 *StartAddress,uint32 first, uint32 last) **
**                                                                            **
** Service ID       : None                                                    **
**                                                                            **
** Sync/Async       : Synchronous                                             **
**                                                                            **
** Reentrancy       : non - reentrant                                         **
**                                                                            **
** Parameters(in)   : StartAddress : address to be checked                    **
**                    first : start bit to be checked                         **
**                    last : last bit to be checked                           **
**                                                                            **
** Parameters (out) : None                                                    **
**                                                                            **
** Return value     : uint32 : bit status mask                                **
**                                                                            **
** Description      : This function returns the status of the bits from start **
**                    to last position                                        **
*******************************************************************************/
LOCAL_INLINE uint32 FlsLoader_lCheckBitStatus(const uint32 *StartAddress,
                                 uint32 first, uint32 Last)
{
  uint32 MsbFlushCount;
  uint32 MaskStatus  = *StartAddress;

  Last--;
  MsbFlushCount = 31U - Last; /* Number of MSB bits to be flushed */

  /* Flush MSB bits, back to original */
  MaskStatus = ( MaskStatus << MsbFlushCount) >> MsbFlushCount;
  /* Flush LSB and back to original */
  MaskStatus = ( MaskStatus >> first) << first;   /* Flush LSB bits */

  return MaskStatus;
}

/*******************************************************************************
** Syntax           :  uint8  FlsLoader_lCheckProtStatus(                     **
**                     const uint32 *StartAddress,uint32 Length,uint32 Start) **
**                                                                            **
** Service ID       : None                                                    **
**                                                                            **
** Sync/Async       : Synchronous                                             **
**                                                                            **
** Reentrancy       : non - reentrant                                         **
**                                                                            **
** Parameters(in)   : StartAddress : Protection register address              **
**                    Length : Number of sectors to be checked                **
**                    First : Starting sector number                          **
**                                                                            **
** Parameters (out) : None                                                    **
**                                                                            **
** Return value     : 0 : Sectors are protected                               **
**                    1 : Sectors are not protected                           **
**                                                                            **
** Description      : This function returns the status of the bits from start **
**                    to last position                                        **
*******************************************************************************/
LOCAL_INLINE uint8 FlsLoader_lCheckProtStatus(const uint32 *StartAddress,
                                              uint32 Length, uint32 First)
{
  uint8 RetError = 0x00;
  uint32 MaskStatus   = 0;
  uint32 LastRegVal   = 0;
  uint32 FirstRegVal  = 0;
  uint32  Last         = (First + Length);

  while(Last != 0U)
  {
    /* Check if last bit is in current register or not */
    LastRegVal = Last >> FLSLOADER_SHIFT_BY_5;

    if(LastRegVal == 0U)
    {
      /* Last is in the current register */
      MaskStatus = FlsLoader_lCheckBitStatus(StartAddress,First,Last);
      StartAddress++;
      Last  = FLSLOADER_REG_FIRST_BIT;
      /*MISRA2012_RULE_17_8_JUSTIFICATION: Function parameter changed to
      access SFR efficiently*/
      First = FLSLOADER_REG_FIRST_BIT;
    }
    else
    {
      /* Last bit lies in the next register */
      /* check if the first bit lies in the current register */
      FirstRegVal = First >> FLSLOADER_SHIFT_BY_5;

      if(FirstRegVal == 0U)
      {
        /* First bit lies in the current register */
        /* Mask will be from the First bit to the 31st bit for this register*/
        MaskStatus = FlsLoader_lCheckBitStatus(StartAddress,First,
                                               FLSLOADER_REG_32_BIT);
        StartAddress++;
        /* For next register read bits from starting i.e. First = 0 */
        /*MISRA2012_RULE_17_8_JUSTIFICATION: Function parameter changed to
        access SFR efficiently*/
        First = 0U;
        Last = Last - FLSLOADER_DECREMENT_BY_32;
      }
      else
      {
        /*First bit lies is next register */
        /* Nothing to be read from this register as First bit is in next reg*/
        StartAddress++;
        Last  -= FLSLOADER_DECREMENT_BY_32;
        First -= FLSLOADER_DECREMENT_BY_32;
      }
    }

    if(MaskStatus != 0x00U)
    {
      /* Sectors are protected */
      RetError = 0x01;
      break;
    }
  }

  return RetError;
}


#define FLSLOADER_STOP_SEC_WRITE_CODE
/* MISRA2012_RULE_4_10_JUSTIFICATION: Flsloader_Memmap.h is repeatedly included
 * without include guard. This is as per AUTOSAR */
/* MISRA2012_RULE_20_1_JUSTIFICATION: declaration of 'FlsLoader_PFlashOffset'
 * before #include memap.h - Accepted deviation in AUTOSAR */
#include "MemMap.h"
/* Deviation MISRA-1 MISRA-2 MISRA-3 MISRA-4 MISRA-5 MISRA-6 MISRA-7 <STOP> */
/* CHECK: RULE 203 ON */
/* CHECK: RULE 404 ON */
/* CHECK: RULE 205 ON */
/* CHECK: RULE 506 ON */
/* CHECK: RULE 306 ON */
/* CHECK: PARSE */
