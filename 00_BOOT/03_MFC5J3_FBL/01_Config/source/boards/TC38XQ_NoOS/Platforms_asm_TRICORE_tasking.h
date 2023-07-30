/* Platforms_asm_TRICORE_tasking.h
 *
 * This file is the toolchain-dependent include file for the ghs assembler for the Power Architecture.
 *
 * This file defines the macros used in assembler files in a way such that the assembler files
 * will compile with the tasking assembler.
 *
 *
 * Copyright 1998-2015 Elektrobit Automotive GmbH
 * All rights exclusively reserved for Elektrobit Automotive GmbH,
 * unless expressly agreed to otherwise.
 *
 */
#ifndef __PLATFORMS_ASM_TRICORE_TASKING_H
#define __PLATFORMS_ASM_TRICORE_TASKING_H

#ifdef BOARD_ASM
/* Filename for the assembler
 */
#define Platforms_file(name)

/* Various assembler directives
 */
#define Platforms_global     .global
#define Platforms_extern     .extern
#define Platforms_gtype(s,t)
#define Platforms_ttype(s,t)  s  .type t

#define Platforms_align(n,p) .align n

#define Platforms_word       .word
#define Platforms_hword      .half

#define Platforms_section    .sect
#define Platforms_sdecl      .sdecl

/*  The Tasking assembler uses @his(x) and @los(x) to extract the
 *  high and low words from a literal.
 */
#define Platforms_hi(x)  @his(x)
#define Platforms_lo(x)  @los(x)

/*  Tasking assembler has no standard .text and .data sections so we have
 *  to explicitly declare them as well as switch to them.
 */
Platforms_sdecl ".text",code
Platforms_sdecl ".data",data

/* Data section
 *
 * This could be already defined by the user's memmap, so we only define it if it isn't already defined.
 */
#ifndef PLATFORMS_ASM_SECTION_DATA
#define PLATFORMS_ASM_SECTION_DATA   .sect ".data"
#endif

/* Text section
 *
 * This could be already defined by the user's memmap, so we only define it if it isn't already defined.
 */
#ifndef PLATFORMS_ASM_SECTION_TEXT
#define PLATFORMS_ASM_SECTION_TEXT   .sect ".text"
#endif

/* Interrupt Table section
 *
 */
#ifndef PLATFORMS_ASM_SECTION_DECL_INTCTAB
#define PLATFORMS_ASM_SECTION_DECL_INTCTAB Platforms_sdecl    ".intctab",code
#endif
#ifndef PLATFORMS_ASM_SECTION_INTCTAB
#define PLATFORMS_ASM_SECTION_INTCTAB Platforms_section  ".intctab"
#endif
/* Exception Table section
 *
 */
#ifndef PLATFORMS_ASM_SECTION_DECL_EXCTAB
#define PLATFORMS_ASM_SECTION_DECL_EXCTAB Platforms_sdecl    ".exctab",code
#endif
#ifndef PLATFORMS_ASM_SECTION_EXCTAB
#define PLATFORMS_ASM_SECTION_EXCTAB Platforms_section  ".exctab"

#endif

/*  For Tasking we have to put a # operator before immediate values
 *  in the assembler. This results in a C preprocesor warning, which
 *  can be turned off for .s files.
 */
#define PLATFORMS_IMM(p,x) p x

_mtcr .macro creg,reg
  dsync
  mtcr creg,reg
  isync
.endm

_mfcr .macro reg,creg
  mfcr reg,creg
.endm

ISRVector .macro name,id,entry
  Platforms_align (32,1)
  Platforms_global name
  Platforms_extern entry
name:
  j entry
.endm

TrapVector .macro name,id,entry
  Platforms_global name
  Platforms_extern entry
name:
  j entry
.endm

#else
/* Macro to return from a JL instruction. We call it RFJL, but it is
 * really only a JI A11.
 */
#define PLATFORMS_RFJL()     __asm ("ji a11")
#define PLATFORMS_RFE()      __asm ("rfe")

#define PLATFORMS_ISYNC()      __asm(" isync")
#define PLATFORMS_DSYNC()      __asm(" dsync")

#define PLATFORMS_MFCR(sysreg)  __mfcr(sysreg)

#define PLATFORMS_MTSP(val) \
  do {                      \
    register void *mtspTmp = (val);       \
    __asm("mov.aa sp,%0" : : "a" (mtspTmp));  \
  } while (0)

#define PLATFORMS_MTCR(csfr, val) \
  do {                                \
    register int mtcrTmp = (val);              \
    __asm(" dsync \n mtcr #"PLATFORMS__XSTR(csfr)",%0" : : "d" (mtcrTmp)); \
    PLATFORMS_ISYNC();                           \
  } while (0)

#define PLATFORMS_DISABLE()  __disable()
#define PLATFORMS_ENABLE()   __enable()

#define INTERRUPT_FUNC __interrupt

#endif /*ifdef BOARD_ASM */

#endif
