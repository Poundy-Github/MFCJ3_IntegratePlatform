/*******************************************************************************
**                                                                            **
** Copyright (C) Infineon Technologies (2019)                                 **
**                                                                            **
** All rights reserved.                                                       **
**                                                                            **
** This document contains proprietary information belonging to Infineon       **
** Technologies. Passing on and copying of this document, and communication   **
** of its contents is not permitted without prior written authorization.      **
**                                                                            **
********************************************************************************
**                                                                            **
**  FILENAME     : Bfx.c                                                      **
**                                                                            **
**  VERSION      : 8.0.0                                                      **
**                                                                            **
**  DATE         : 2019-06-19                                                 **
**                                                                            **
**  VARIANT      : Variant PC                                                 **
**                                                                            **
**  PLATFORM     : Infineon AURIX2G                                           **
**                                                                            **
**  AUTHOR       : DL-AUTOSAR-Engineering                                     **
**                                                                            **
**  VENDOR       : Infineon Technologies                                      **
**                                                                            **
**  TRACEABILITY : [cover parentID={DDA63FB1-2F74-4880-973A-BF580860E9BA},    **
**                                 {4336288A-B9DC-42d7-9958-67EA832D0F72}]    **
**                                                                            **
**  DESCRIPTION  : BFX library source file                                    **
**                                                                            **
**  [/cover]                                                                  **
**                                                                            **
**  SPECIFICATION(S) : Specification of BFX library, AUTOSAR Release 4.2.2    **
**                                                                            **
**  MAY BE CHANGED BY USER : no                                               **
**                                                                            **
*******************************************************************************/

/*******************************************************************************
**                      Includes                                              **
*******************************************************************************/

/*[cover parentID={DC0B4213-1D31-4256-BAD3-DC0CD7F025C4}] File Structure*/
/* Own header file */
#include "Bfx.h"
/*[/cover]*/

/*[cover parentID={0AF316CA-64BD-421b-8F2F-F3966F42F073}]
Imported SW Interfaces
No BSW module function is called. Hence no BSW module header file is included.
[/cover] */

/*******************************************************************************
**                      Imported Compiler Switch Checks                       **
*******************************************************************************/

/*[cover parentID={52DEE5CF-FAD4-4034-B8EA-0129E6E23863}] Version checks*/

/* BFX Header File Version Check */
#ifndef BFX_SW_MAJOR_VERSION
#error "BFX_SW_MAJOR_VERSION is not defined. "
#endif

#ifndef BFX_SW_MINOR_VERSION
#error "BFX_SW_MINOR_VERSION is not defined. "
#endif

#ifndef BFX_SW_PATCH_VERSION
#error "BFX_SW_PATCH_VERSION is not defined."
#endif

#if (BFX_SW_MAJOR_VERSION != 10U)
#error "BFX_SW_MAJOR_VERSION does not match. "
#endif

#if (BFX_SW_MINOR_VERSION != 30U)
#error "BFX_SW_MINOR_VERSION does not match. "
#endif

#if (BFX_SW_PATCH_VERSION != 0U)
#error "BFX_SW_PATCH_VERSION does not match."
#endif

/* AUTOSAR Secification File Version Check */
#ifndef BFX_AR_RELEASE_MAJOR_VERSION
#error "BFX_AR_RELEASE_MAJOR_VERSION is not defined. "
#endif

#if (BFX_AR_RELEASE_MAJOR_VERSION != 4U)
#error "BFX_AR_RELEASE_MAJOR_VERSION does not match. "
#endif

/*[/cover]*/

/*******************************************************************************
**                      Private Macro Definitions                             **
*******************************************************************************/

/* Default width of the bit handling request - 1 bit */
#define BFX_DEFAULT_WIDTH                    ((uint8)1)

/* Holds the all '1' status */
#define BFX_DEFAULT_STATUS_1_EIGHT_BITS      ((uint8)0xFFU)
#define BFX_DEFAULT_STATUS_1_SIXTEEN_BITS    ((uint16)0xFFFFU)
#define BFX_DEFAULT_STATUS_1_THIRTYTWO_BITS  ((uint32)0xFFFFFFFFU)

/* Holds the all '0' status */
#define BFX_DEFAULT_STATUS_0_EIGHT_BITS      ((uint8)0x00)
#define BFX_DEFAULT_STATUS_0_SIXTEEN_BITS    ((uint16)0x0000)
#define BFX_DEFAULT_STATUS_0_THIRTYTWO_BITS  ((uint32)0x00000000)

/* Masks all bits except LSB to determine whether the value is even or odd */
#define BFX_MASK_ALL_EXCEPT_LSB              (0x00000001)

#ifdef _DIABDATA_C_TRICORE_
#if (_DIABDATA_C_TRICORE_ == 1U)
/* ASM Macro definition for inserting 8 bits */
/* This is implemented differently from other compilers as Windriver supports
   inline assembly as function like asm macro
*/
__asm volatile void BFX_INSERT8BITS_DCC(uint8 * const TargetPtr,
                                                  const uint8 SourceVal,
                                                  const uint8 Pos,
                                                  const uint8 Width)
{
%reg TargetPtr, SourceVal, Pos, Width;
!
  ld.bu %d11, [TargetPtr]0
  mov %d12, Pos
  mov %d13, Width
  insert %d11, %d11, SourceVal, %e12
  st.b [TargetPtr]0, %d11
}

/* ASM Macro definition for inserting 16 bits */
/* This is implemented differently from other compilers as Windriver supports
   inline assembly as function like asm macro
 */
__asm volatile void BFX_INSERT16BITS_DCC(uint16 * const TargetPtr,
                                                   const uint16 SourceVal,
                                                   const uint8 Pos,
                                                   const uint8 Width)
{
%reg TargetPtr, SourceVal, Pos, Width;
!
  ld.hu %d11, [TargetPtr]0
  mov %d12, Pos
  mov %d13, Width
  insert %d11, %d11, SourceVal, %e12
  st.h [TargetPtr]0, %d11
}

/* ASM Macro definition for inserting 32 bits */
/* This is implemented differently from other compilers as Windriver supports
   inline assembly as function like asm macro
 */
__asm volatile void BFX_INSERT32BITS_DCC(uint32 * const TargetPtr,
                                                   const uint32 SourceVal,
                                                   const uint8 Pos,
                                                   const uint8 Width)
{
%reg TargetPtr, SourceVal, Pos, Width;
!
  ld.w %d11, [TargetPtr]0
  mov %d12, Pos
  mov %d13, Width
  insert %d11, %d11, SourceVal, %e12
  st.w [TargetPtr]0, %d11
}

/* ASM Macro definition for extracting 32 bits */
/* This is implemented differently from other compilers as Windriver supports
   inline assembly as function like asm macro
 */
__asm volatile uint32 BFX_EXTRACTBITS_DCC(const uint32 Value,
                                                    const uint8 Pos,
                                                    const uint8 Width)
{
%reg Value, Pos, Width;
!"%d2"
  mov %d12, Pos
  mov %d13, Width
  extr.u %d2, Value ,%e12
}

/* ASM Macro definition for odd parity check */
/* This is implemented differently from other compilers as Windriver supports
 * inline assembly as function like asm macro
 */
__asm volatile uint32 BFX_PARITY_DCC(const uint32 Value)
{
%reg Value;
!"%d2"
  popcnt.w %d14, Value
  and %d2, %d14, BFX_MASK_ALL_EXCEPT_LSB
}

#endif /* #if (_DIABDATA_C_TRICORE_ == 1U) */
#endif

/*******************************************************************************
**                         User Mode Macros                                   **
*******************************************************************************/

/*[cover parentID={C9E9BEC9-F29C-4330-920D-618869AE79FD}]
User Mode macros not required
[/cover]*/

/******************************************************************************/

/*******************************************************************************
**                      Private Type Definitions                              **
*******************************************************************************/

/******************************************************************************/

/*[cover parentID={CC8A1B89-5F19-4485-96B6-CE3DD698F100}]
The BFX library is implemented as ASIL B module. There is no ASIL decomposition
done for the BFX library.
[/cover]*/
/*[cover parentID={826C08F0-0107-42bf-9DCC-FABBFE7F9A19}]
Code Memory section executable by all cores
[/cover]*/
/* [cover parentID={EA0715EE-3E3C-4aac-A42E-4B5CFC96CEED}]
Memory mapping support
[/cover] */
/*[cover parentID={4579FE20-92DA-4848-93DB-7AD4FD35DD50}]
Code Memory section naming as per AS
[/cover]*/
#define BFX_START_SEC_CODE_ASIL_B_GLOBAL
/*MISRA2012_RULE_4_10_JUSTIFICATION: Memmap header is repeatedly included
without safegaurd. It complies to Autosar guidelines. */
/*[cover parentID={6D3BA711-CAAB-4a34-82CC-822B613FCB90}]
MemMap_h file to be developed by user
[/cover]*/
#include "Bfx_MemMap.h"
/*******************************************************************************
**                      Private Function Declarations                         **
*******************************************************************************/


LOCAL_INLINE void Bfx_lInsert8Bits(uint8 * const TargetPtr,
                                   const uint8 SourceVal,
                                   const uint8 Pos,
                                   const uint8 Width);

LOCAL_INLINE void Bfx_lInsert16Bits(uint16 * const TargetPtr,
                                    const uint16 SourceVal,
                                    const uint8 Pos,
                                    const uint8 Width);

LOCAL_INLINE void Bfx_lInsert32Bits(uint32 * const TargetPtr,
                                    const uint32 SourceVal,
                                    const uint8 Pos,
                                    const uint8 Width);

LOCAL_INLINE uint32 Bfx_lExtractBits(const uint32 Value,
                                     const uint8 Pos,
                                     const uint8 Width);

LOCAL_INLINE uint32 Bfx_lParity(const uint32 Value);

/*[cover parentID={826C08F0-0107-42bf-9DCC-FABBFE7F9A19}]
Code Memory section executable by all cores
[/cover]*/
/* [cover parentID={EA0715EE-3E3C-4aac-A42E-4B5CFC96CEED}]
Memory mapping support
[/cover] */
/*[cover parentID={4579FE20-92DA-4848-93DB-7AD4FD35DD50}]
Code Memory section naming as per AS
[/cover]*/
#define BFX_STOP_SEC_CODE_ASIL_B_GLOBAL
/*MISRA2012_RULE_4_10_JUSTIFICATION: Memmap header is repeatedly included
without safegaurd. It complies to Autosar guidelines. */
/*MISRA2012_RULE_20_1_JUSTIFICATION: Memmap header usage as per Autosar
guideline. */
/*[cover parentID={6D3BA711-CAAB-4a34-82CC-822B613FCB90}]
MemMap_h file to be developed by user
[/cover]*/
#include "Bfx_MemMap.h"

/*******************************************************************************
**                      Global Constant Definitions                           **
*******************************************************************************/
/*******************************************************************************
**                      Global Variable Definitions                           **
*******************************************************************************/
/*******************************************************************************
**                      Private Constant Definitions                          **
*******************************************************************************/
/*******************************************************************************
**                      Private Variable Definitions                          **
*******************************************************************************/
/******************************************************************************/

/*[cover parentID={826C08F0-0107-42bf-9DCC-FABBFE7F9A19}]
Code Memory section executable by all cores
[/cover]*/
/* [cover parentID={EA0715EE-3E3C-4aac-A42E-4B5CFC96CEED}]
Memory mapping support
[/cover] */
/*[cover parentID={4579FE20-92DA-4848-93DB-7AD4FD35DD50}]
Code Memory section naming as per AS
[/cover]*/
#define BFX_START_SEC_CODE_ASIL_B_GLOBAL
/*MISRA2012_RULE_4_10_JUSTIFICATION: Memmap header is repeatedly included
without safegaurd. It complies to Autosar guidelines. */
/*MISRA2012_RULE_20_1_JUSTIFICATION: Memmap header usage as per Autosar
guideline. */
/*[cover parentID={6D3BA711-CAAB-4a34-82CC-822B613FCB90}]
MemMap_h file to be developed by user
[/cover]*/
#include "Bfx_MemMap.h"
/*******************************************************************************
**                      Private Function Definitions                          **
*******************************************************************************/

/*******************************************************************************
** Traceability      : [cover parentID={B07BF891-FFAF-4c8d-BFBE-CDE10E99D329},**
**                                     {44B965C9-ADC0-4ebd-BF53-2C409B6CC3F7}]**
**                                                                            **
**                                                                            **
** Syntax            : void Bfx_lInsert8Bits                                  **
**                     (                                                      **
**                       uint8 * const TargetPtr,                             **
**                       const uint8 SourceVal,                               **
**                       const uint8 Pos,                                     **
**                       const uint8 Width                                    **
**                     )                                                      **
**                                                                            **
** Description       : The Bfx_lInsert8Bits function copies the bits from the **
**                     SourceVal parameter starting from 0 bit position for   **
**                     Width number of bits into the memory location pointed  **
**                     to by TargetPtr parameter at the bit positions starting**
**                     from Pos bit position for Width number of bits.        **
** [/cover]                                                                   **
**                                                                            **
** Service ID        : None                                                   **
**                                                                            **
** Sync/Async        : Synchronous                                            **
**                                                                            **
** Reentrancy        : Reentrant for pointer to distinct memory location      **
**                     passed as parameter to the function                    **
**                                                                            **
** Parameters (in)   : SourceVal - Source Data                                **
**                     Pos       - Start bit position (Valid range: 0 to 7 )  **
**                     Width     - Bit field length                           **
**                                (Valid range: 1 to (8-Pos))                 **
**                                                                            **
** Parameters(in-out): TargetPtr - Pointer to data which is to be modified    **
**                                                                            **
** Parameters (out)  : None                                                   **
**                                                                            **
** Return value      : void                                                   **
*******************************************************************************/
LOCAL_INLINE void Bfx_lInsert8Bits(uint8 * const TargetPtr,
                                   const uint8 SourceVal,
                                   const uint8 Pos,
                                   const uint8 Width)
{
  #ifdef _TASKING_C_TRICORE_
  #if (_TASKING_C_TRICORE_ == 1U)
  __asm("ld.bu d11,[%0]""\n\t" \
        "mov d12,%2""\n\t" \
        "mov d13,%3""\n\t" \
        "insert d11,d11,%1,e12""\n\t" \
        "st.b [%0],d11" \
        : \
        : "a"(TargetPtr), "d" (SourceVal), "d" (Pos), "d" (Width) \
        : "d11", "d12", "d13");
  #endif /* #if (_TASKING_C_TRICORE_ == 1U) */
  #endif /* _TASKING_C_TRICORE_ */

  #ifdef _GNU_C_TRICORE_
  #if (_GNU_C_TRICORE_ == 1U)
  __asm__("ld.bu %%d11,[%0]""\n\t" \
          "mov %%d12,%2""\n\t" \
          "mov %%d13,%3""\n\t" \
          "insert %%d11,%%d11,%1,%%e12""\n\t" \
          "st.b [%0],%%d11" \
          : \
          : "a"(TargetPtr), "d" (SourceVal), "d" (Pos), "d" (Width) \
          : "d11", "d12", "d13");
  #endif /* #if (_GNU_C_TRICORE_ == 1U) */
  #endif /* _GNU_C_TRICORE_ */

  #ifdef _DIABDATA_C_TRICORE_
  #if (_DIABDATA_C_TRICORE_ == 1U)
  BFX_INSERT8BITS_DCC(TargetPtr, SourceVal, Pos, Width);
  #endif /* #if (_DIABDATA_C_TRICORE_ == 1U) */
  #endif
  
  #ifdef _GHS_C_TRICORE_
  #if (_GHS_C_TRICORE_ == 1U)
  __asm ("ld.bu %%d11,[%0]""\n\t" \
         "mov %%d12,%2""\n\t" \
         "mov %%d13,%3""\n\t" \
         "insert %%d11,%%d11,%1,%%e12""\n\t" \
         "st.b [%0],%%d11" \
         : \
         : "a"(TargetPtr), "d" (SourceVal), "d" (Pos), "d" (Width) \
         : "d11", "d12", "d13");
  #endif /* #if (_GHS_C_TRICORE_ == 1U) */
  #endif /* _GHS_C_TRICORE_ */

  #if ((!defined(_TASKING_C_TRICORE_)) && (!defined(_GNU_C_TRICORE_)) &&\
       (!defined(_DIABDATA_C_TRICORE_)) && (!defined(_GHS_C_TRICORE_)))
  #error Unsupported compiler configured!
  #endif

  /* MISRA2012_RULE_2_7_JUSTIFICATION:Parameter are updated via assembly
     instruction, hence they are not unused.*/
  /* MISRA2012_RULE_8_13_JUSTIFICATION: Parameter are updated via assembly
     instruction, hence cannot be passed as const.*/
}

/*******************************************************************************
** Traceability      : [cover parentID={D67AFC87-A469-4e5f-BC5E-6D01F9CF0443},**
**                                     {44B965C9-ADC0-4ebd-BF53-2C409B6CC3F7}]**
**                                                                            **
**                                                                            **
** Syntax            : void Bfx_lInsert16Bits                                 **
**                     (                                                      **
**                       uint16 * const TargetPtr,                            **
**                       const uint16 SourceVal,                              **
**                       const uint8 Pos,                                     **
**                       const uint8 Width                                    **
**                     )                                                      **
**                                                                            **
** Description       : The Bfx_lInsert16Bits function copies the bits from the**
**                     SourceVal parameter starting from 0 bit position for   **
**                     Width number of bits into the memory location pointed  **
**                     to by TargetPtr parameter at the bit positions starting**
**                     from Pos bit position for Width number of bits.        **
** [/cover]                                                                   **
**                                                                            **
** Service ID        : None                                                   **
**                                                                            **
** Sync/Async        : Synchronous                                            **
**                                                                            **
** Reentrancy        : Reentrant for pointer to distinct memory location      **
**                     passed as parameter to the function                    **
**                                                                            **
** Parameters (in)   : SourceVal - Source Data                                **
**                     Pos       - Start bit position (Valid range: 0 to 15)  **
**                     Width     - Bit field length                           **
**                                 (Valid range: 1 to (16-Pos))               **
**                                                                            **
** Parameters(in-out): TargetPtr - Pointer to data which is to be modified    **
**                                                                            **
** Parameters (out)  : None                                                   **
**                                                                            **
** Return value      : void                                                   **
*******************************************************************************/
LOCAL_INLINE void Bfx_lInsert16Bits(uint16 * const TargetPtr,
                                    const uint16 SourceVal,
                                    const uint8 Pos,
                                    const uint8 Width)
{
  #ifdef _TASKING_C_TRICORE_
  #if (_TASKING_C_TRICORE_ == 1U)
  __asm("ld.hu d11,[%0]""\n\t" \
        "mov d12,%2""\n\t" \
        "mov d13,%3""\n\t" \
        "insert d11,d11,%1,e12""\n\t" \
        "st.h [%0],d11" \
        : \
        : "a"(TargetPtr), "d" (SourceVal), "d" (Pos), "d" (Width) \
        : "d11", "d12", "d13");
  #endif /* #if (_TASKING_C_TRICORE_ == 1U) */
  #endif /* _TASKING_C_TRICORE_ */

  #ifdef _GNU_C_TRICORE_
  #if (_GNU_C_TRICORE_ == 1U)
  __asm__("ld.hu %%d11,[%0]""\n\t" \
          "mov %%d12,%2""\n\t" \
          "mov %%d13,%3""\n\t" \
          "insert %%d11,%%d11,%1,%%e12""\n\t" \
          "st.h [%0],%%d11" \
          : \
          : "a"(TargetPtr), "d" (SourceVal), "d" (Pos), "d" (Width) \
          : "d11", "d12", "d13");
  #endif /* #if (_GNU_C_TRICORE_ == 1U) */
  #endif /* _GNU_C_TRICORE_ */

  #ifdef _DIABDATA_C_TRICORE_
  #if (_DIABDATA_C_TRICORE_ == 1U)
  BFX_INSERT16BITS_DCC(TargetPtr, SourceVal, Pos, Width);
  #endif /* #if (_DIABDATA_C_TRICORE_ == 1U) */
  #endif
  
  #ifdef _GHS_C_TRICORE_
  #if (_GHS_C_TRICORE_ == 1U)
  __asm ("ld.hu %%d11,[%0]""\n\t" \
         "mov %%d12,%2""\n\t" \
         "mov %%d13,%3""\n\t" \
         "insert %%d11,%%d11,%1,%%e12""\n\t" \
         "st.h [%0],%%d11" \
         : \
         : "a"(TargetPtr), "d" (SourceVal), "d" (Pos), "d" (Width) \
         : "d11", "d12", "d13");
  #endif /* #if (_GHS_C_TRICORE_ == 1U) */
  #endif /* _GHS_C_TRICORE_ */

  #if ((!defined(_TASKING_C_TRICORE_)) && (!defined(_GNU_C_TRICORE_)) &&\
       (!defined(_DIABDATA_C_TRICORE_)) && (!defined(_GHS_C_TRICORE_)))
  #error Unsupported compiler configured!
  #endif

  /* MISRA2012_RULE_2_7_JUSTIFICATION:Parameter are updated via assembly
     instruction, hence they are not unused.*/
  /* MISRA2012_RULE_8_13_JUSTIFICATION: Parameter are updated via assembly
     instruction, hence cannot be passed as const.*/
}

/*******************************************************************************
** Traceability      : [cover parentID={C1D10318-09FD-4cb8-9950-AF15B6F13A37},**
**                                     {44B965C9-ADC0-4ebd-BF53-2C409B6CC3F7}]**
**                                                                            **
**                                                                            **
** Syntax            : void Bfx_lInsert32Bits                                 **
**                     (                                                      **
**                       uint32 * const TargetPtr,                            **
**                       const uint32 SourceVal,                              **
**                       const uint8 Pos,                                     **
**                       const uint8 Width                                    **
**                     )                                                      **
**                                                                            **
** Description       : The Bfx_lInsert32Bits function copies the bits from the**
**                     SourceVal parameter starting from 0 bit position for   **
**                     Width number of bits into the memory location pointed  **
**                     to by TargetPtr parameter at the bit positions starting**
**                     from Pos bit position for Width number of bits.        **
** [/cover]                                                                   **
**                                                                            **
** Service ID        : None                                                   **
**                                                                            **
** Sync/Async        : Synchronous                                            **
**                                                                            **
** Reentrancy        : Reentrant for pointer to distinct memory location      **
**                     passed as parameter to the function                    **
**                                                                            **
** Parameters (in)   : SourceVal - Source Data                                **
**                     Pos       - Start bit position (Valid range: 0 to 31)  **
**                     Width     - Bit field length                           **
**                                 (Valid range: 1 to (32-Pos))               **
**                                                                            **
** Parameters(in-out): TargetPtr - Pointer to data which is to be modified    **
**                                                                            **
** Parameters (out)  : None                                                   **
**                                                                            **
** Return value      : void                                                   **
*******************************************************************************/
LOCAL_INLINE void Bfx_lInsert32Bits(uint32* const TargetPtr,
                                    const uint32 SourceVal,
                                    const uint8 Pos,
                                    const uint8 Width)
{
  #ifdef _TASKING_C_TRICORE_
  #if (_TASKING_C_TRICORE_ == 1U)
  __asm("ld.w d11,[%0]""\n\t" \
        "mov d12,%2""\n\t" \
        "mov d13,%3""\n\t" \
        "insert d11,d11,%1,e12""\n\t" \
        "st.w [%0],d11" \
        : \
        : "a"(TargetPtr), "d" (SourceVal), "d" (Pos), "d" (Width) \
        : "d11", "d12", "d13");
  #endif /* #if (_TASKING_C_TRICORE_ == 1U) */
  #endif /* _TASKING_C_TRICORE_ */

  #ifdef _GNU_C_TRICORE_
  #if (_GNU_C_TRICORE_ == 1U)
  __asm__("ld.w %%d11,[%0]""\n\t" \
          "mov %%d12,%2""\n\t" \
          "mov %%d13,%3""\n\t" \
          "insert %%d11,%%d11,%1,%%e12""\n\t" \
          "st.w [%0],%%d11" \
          : \
          : "a"(TargetPtr), "d" (SourceVal), "d" (Pos), "d" (Width) \
          : "d11", "d12", "d13");
  #endif /* #if (_GNU_C_TRICORE_ == 1U) */
  #endif /* _GNU_C_TRICORE_ */

  #ifdef _DIABDATA_C_TRICORE_
  #if (_DIABDATA_C_TRICORE_ == 1U)
  BFX_INSERT32BITS_DCC(TargetPtr, SourceVal, Pos, Width);
  #endif /* #if (_DIABDATA_C_TRICORE_ == 1U) */
  #endif
  
  #ifdef _GHS_C_TRICORE_
  #if (_GHS_C_TRICORE_ == 1U)
  __asm ("ld.w %%d11,[%0]""\n\t" \
         "mov %%d12,%2""\n\t" \
         "mov %%d13,%3""\n\t" \
         "insert %%d11,%%d11,%1,%%e12""\n\t" \
         "st.w [%0],%%d11" \
         : \
         : "a"(TargetPtr), "d" (SourceVal), "d" (Pos), "d" (Width) \
         : "d11", "d12", "d13");
  #endif /* #if (_GHS_C_TRICORE_ == 1U) */
  #endif /* _GHS_C_TRICORE_ */

  #if ((!defined(_TASKING_C_TRICORE_)) && (!defined(_GNU_C_TRICORE_)) &&\
       (!defined(_DIABDATA_C_TRICORE_)) && (!defined(_GHS_C_TRICORE_)))
  #error Unsupported compiler configured!
  #endif

  /* MISRA2012_RULE_2_7_JUSTIFICATION:Parameter are updated via assembly
     instruction, hence they are not unused.*/
  /* MISRA2012_RULE_8_13_JUSTIFICATION: Parameter are updated via assembly
     instruction, hence cannot be passed as const.*/
}

/*******************************************************************************
** Traceability      : [cover parentID={24F7AF0E-13C0-4849-A903-7190520A26E8},**
**                                     {44B965C9-ADC0-4ebd-BF53-2C409B6CC3F7}]**
**                                                                            **
**                                                                            **
** Syntax            : uint32 Bfx_lExtractBits                                **
**                     (                                                      **
**                       const uint32 Value,                                  **
**                       const uint8 Pos,                                     **
**                       const uint8 Width                                    **
**                     )                                                      **
**                                                                            **
** Description       : The Bfx_lExtractBits function returns the bits from the**
**                     Value parameter starting from Pos bit position for     **
**                     Width number of bits.                                  **
** [/cover]                                                                   **
**                                                                            **
** Service ID        : None                                                   **
**                                                                            **
** Sync/Async        : Synchronous                                            **
**                                                                            **
** Reentrancy        : Reentrant                                              **
**                                                                            **
** Parameters (in)   : Value - Input data                                     **
**                     Pos   - Start bit position (Valid range: 0 to 31)      **
**                     Width - Bit field length                               **
**                             (Valid range: 1 to (32-Pos))                   **
**                                                                            **
** Parameters(in-out): None                                                   **
**                                                                            **
** Parameters (out)  : None                                                   **
**                                                                            **
** Return value      : uint32 - Extracted data                                **
*******************************************************************************/
LOCAL_INLINE uint32 Bfx_lExtractBits(const uint32 Value,
                                     const uint8 Pos,
                                     const uint8 Width)
{
  uint32 ResultVal = 0x0U;

  #ifdef _TASKING_C_TRICORE_
  #if (_TASKING_C_TRICORE_ == 1U)
  __asm("mov d12,%2""\n\t" \
        "mov d13,%3""\n\t" \
        "extr.u %0,%1,e12" \
        : "=d" (ResultVal) \
        : "d" (Value), "d" (Pos), "d" (Width) \
        : "d12", "d13" );
  #endif /* #if (_TASKING_C_TRICORE_ == 1U) */
  #endif /* _TASKING_C_TRICORE_ */

  #ifdef _GNU_C_TRICORE_
  #if (_GNU_C_TRICORE_ == 1U)
  __asm__ volatile ("mov %%d12,%2""\n\t" \
                    "mov %%d13,%3""\n\t" \
                    "extr.u %0,%1,%%e12" \
                    : "=d" (ResultVal) \
                    : "d" (Value), "d" (Pos), "d" (Width) \
                    : "d12", "d13");
  #endif /* #if (_GNU_C_TRICORE_ == 1U) */
  #endif /* _GNU_C_TRICORE_ */

  #ifdef _DIABDATA_C_TRICORE_
  #if (_DIABDATA_C_TRICORE_ == 1U)
  ResultVal = BFX_EXTRACTBITS_DCC(Value, Pos, Width);
  #endif /* #if (_DIABDATA_C_TRICORE_ == 1U) */
  #endif
  
  #ifdef _GHS_C_TRICORE_
  #if (_GHS_C_TRICORE_ == 1U)
  __asm volatile ("mov %%d12,%2""\n\t" \
                  "mov %%d13,%3""\n\t" \
                  "extr.u %0,%1,%%e12" \
                  : "=d" (ResultVal) \
                  : "d" (Value), "d" (Pos), "d" (Width) \
                  : "d12", "d13");
  #endif /* #if (_GHS_C_TRICORE_ == 1U) */
  #endif /* _GHS_C_TRICORE_ */

  #if ((!defined(_TASKING_C_TRICORE_)) && (!defined(_GNU_C_TRICORE_)) &&\
       (!defined(_DIABDATA_C_TRICORE_)) && (!defined(_GHS_C_TRICORE_)))
  #error Unsupported compiler configured!
  #endif

  return ResultVal;

  /* MISRA2012_RULE_2_7_JUSTIFICATION:Parameter are updated via assembly
     instruction, hence they are not unused.*/
}

/*******************************************************************************
** Traceability      : [cover parentID={EEABD022-A7D0-4b1b-9AFE-AB93984F7D0D},**
**                                     {44B965C9-ADC0-4ebd-BF53-2C409B6CC3F7}]**
**                                                                            **
**                                                                            **
** Syntax            : uint32 Bfx_lParity                                     **
**                     (                                                      **
**                       const uint32 Value                                   **
**                     )                                                      **
** Description       : The Bfx_lParity function returns the odd parity of     **
**                     the Value parameter.                                   **
** [/cover]                                                                   **
**                                                                            **
** Service ID        : None                                                   **
**                                                                            **
** Sync/Async        : Synchronous                                            **
**                                                                            **
** Reentrancy        : Reentrant                                              **
**                                                                            **
** Parameters (in)   : Value - Input data for parity check                    **
**                                                                            **
** Parameters(in-out): None                                                   **
**                                                                            **
** Parameters (out)  : None                                                   **
**                                                                            **
** Return value      : uint32 - Odd parity                                    **
*******************************************************************************/
LOCAL_INLINE uint32 Bfx_lParity(const uint32 Value)
{
  uint32 ResultVal = 0x0U;

  #ifdef _TASKING_C_TRICORE_
  #if (_TASKING_C_TRICORE_ == 1U)
  __asm("popcnt.w d14, %1""\n\t" \
        "and %0, d14, %2" \
        : "=d"(ResultVal) \
        : "d"(Value), "i"(BFX_MASK_ALL_EXCEPT_LSB) \
        : "d14");
  #endif /* #if (_TASKING_C_TRICORE_ == 1U) */
  #endif /* _TASKING_C_TRICORE_ */

  #ifdef _GNU_C_TRICORE_
  #if (_GNU_C_TRICORE_ == 1U)
  __asm__("popcnt.w %%d14, %1""\n\t" \
          "and %0, %%d14, %2" \
          : "=d"(ResultVal) \
          : "d"(Value), "i"(BFX_MASK_ALL_EXCEPT_LSB) \
          : "d14");
  #endif /* #if (_GNU_C_TRICORE_ == 1U) */
  #endif /* _GNU_C_TRICORE_ */

  #ifdef _DIABDATA_C_TRICORE_
  #if (_DIABDATA_C_TRICORE_ == 1U)
  ResultVal = BFX_PARITY_DCC(Value);
  #endif /* #if (_DIABDATA_C_TRICORE_ == 1U) */
  #endif
  
  #ifdef _GHS_C_TRICORE_
  #if (_GHS_C_TRICORE_ == 1U)
  __asm ("popcnt.w %%d14, %1""\n\t" \
         "and %0, %%d14, %2" \
         : "=d"(ResultVal) \
         : "d"(Value), "i"(BFX_MASK_ALL_EXCEPT_LSB) \
         : "d14");
  #endif /* #if (_GHS_C_TRICORE_ == 1U) */
  #endif /* _GHS_C_TRICORE_ */

  #if ((!defined(_TASKING_C_TRICORE_)) && (!defined(_GNU_C_TRICORE_)) &&\
       (!defined(_DIABDATA_C_TRICORE_)) && (!defined(_GHS_C_TRICORE_)))
  #error Unsupported compiler configured!
  #endif

  return ResultVal;
  /* MISRA2012_RULE_2_7_JUSTIFICATION:Parameter are updated via assembly
     instruction, hence they are not unused.*/
}

/*******************************************************************************
**                      Global Function Definitions                           **
*******************************************************************************/
/* [cover parentID={DC57EAE9-9BF3-42f2-B172-BF68A3BF5B66}]
BFX library does not require initialization or shut down  phase
[/cover] */

/*******************************************************************************
** Traceability      : [cover parentID={370DF4C4-2D74-4d77-9359-3AB8F40DD41A},**
**                                     {826C08F0-0107-42bf-9DCC-FABBFE7F9A19},**
**                                     {762A4383-158A-4763-B14B-1CA408E2D54E}]**
**                                                                            **
** Syntax            : void Bfx_SetBit_u8u8                                   **
**                     (                                                      **
**                       uint8* const Data,                                   **
**                       const uint8 BitPn                                    **
**                     )                                                      **
**                                                                            **
** Description       : The Bfx_SetBit_u8u8 function sets the logical status   **
**                     of the bit at BitPn bit position of the Data parameter **
**                     to 1.                                                  **
**                                                                            **
** [/cover]                                                                   **
**                                                                            **
** Service ID        : 0x01                                                   **
**                                                                            **
** Sync/Async        : Synchronous                                            **
**                                                                            **
** Reentrancy        : Reentrant for pointer to distinct memory location      **
**                     passed as parameter to the API                         **
**                                                                            **
** Parameters (in)   : BitPn - Bit position (Valid range: 0 to 7)             **
**                                                                            **
** Parameters(in-out): Data  - Pointer to data which is to be modified        **
**                                                                            **
** Parameters (out)  : None                                                   **
**                                                                            **
** Return value      : void                                                   **
*******************************************************************************/
void Bfx_SetBit_u8u8(uint8* const Data, const uint8 BitPn)
{
  /* [cover parentID={18069F15-3A0A-480f-A3B8-EA7774F28322}]
  Set bit at specified position
  [/cover] */
  Bfx_lInsert8Bits(Data, BFX_DEFAULT_STATUS_1_EIGHT_BITS, BitPn, \
                   BFX_DEFAULT_WIDTH);
}

/*******************************************************************************
** Traceability      : [cover parentID={DB38E919-375E-4d9d-A7E4-F73B323DD421},**
**                                     {826C08F0-0107-42bf-9DCC-FABBFE7F9A19},**
**                                     {762A4383-158A-4763-B14B-1CA408E2D54E}]**
**                                                                            **
** Syntax            : void Bfx_SetBit_u16u8                                  **
**                     (                                                      **
**                       uint16* const Data,                                  **
**                       const uint8 BitPn                                    **
**                     )                                                      **
**                                                                            **
** Description       : The Bfx_SetBit_u16u8 function sets the logical status  **
**                     of the bit at BitPn bit position of the Data parameter **
**                     to 1.                                                  **
**                                                                            **
** [/cover]                                                                   **
**                                                                            **
** Service ID        : 0x02                                                   **
**                                                                            **
** Sync/Async        : Synchronous                                            **
**                                                                            **
** Reentrancy        : Reentrant for pointer to distinct memory location      **
**                     passed as parameter to the API                         **
**                                                                            **
** Parameters (in)   : BitPn - Bit position (Valid range: 0 to 15)            **
**                                                                            **
** Parameters(in-out): Data  - Pointer to data which is to be modified        **
**                                                                            **
** Parameters (out)  : None                                                   **
**                                                                            **
** Return value      : void                                                   **
*******************************************************************************/
void Bfx_SetBit_u16u8(uint16* const Data, const uint8 BitPn)
{
  /* [cover parentID={B54F8846-CE7D-4faf-B051-E6587D418872}]
  Set bit at specified position
  [/cover] */
  Bfx_lInsert16Bits(Data, BFX_DEFAULT_STATUS_1_SIXTEEN_BITS, BitPn, \
                    BFX_DEFAULT_WIDTH);
}

/*******************************************************************************
** Traceability      : [cover parentID={8D467B3D-18D9-4264-ACC4-CCF2BD1128B5},**
**                                     {826C08F0-0107-42bf-9DCC-FABBFE7F9A19},**
**                                     {762A4383-158A-4763-B14B-1CA408E2D54E}]**
**                                                                            **
** Syntax            : void Bfx_SetBit_u32u8                                  **
**                     (                                                      **
**                       uint32* const Data,                                  **
**                       const uint8 BitPn                                    **
**                     )                                                      **
**                                                                            **
** Description       : The Bfx_SetBit_u32u8 function sets the logical status  **
**                     of the bit at BitPn bit position of the Data parameter **
**                     to 1.                                                  **
**                                                                            **
** [/cover]                                                                   **
**                                                                            **
** Service ID        : 0x03                                                   **
**                                                                            **
** Sync/Async        : Synchronous                                            **
**                                                                            **
** Reentrancy        : Reentrant for pointer to distinct memory location      **
**                     passed as parameter to the API                         **
**                                                                            **
** Parameters (in)   : BitPn - Bit position (Valid range: 0 to 31)            **
**                                                                            **
** Parameters(in-out): Data  - Pointer to data which is to be modified        **
**                                                                            **
** Parameters (out)  : None                                                   **
**                                                                            **
** Return value      : void                                                   **
*******************************************************************************/
void Bfx_SetBit_u32u8(uint32* const Data, const uint8 BitPn)
{
  /* [cover parentID={626FF1A4-52E3-4751-94D2-26F442EBDECA}]
  Set bit at specified position
  [/cover] */
  Bfx_lInsert32Bits(Data, BFX_DEFAULT_STATUS_1_THIRTYTWO_BITS, BitPn, \
                    BFX_DEFAULT_WIDTH);
}

/*******************************************************************************
** Traceability      : [cover parentID={EBADC8C7-DC4F-4204-B934-5A5E40D6D6CC},**
**                                     {826C08F0-0107-42bf-9DCC-FABBFE7F9A19},**
**                                     {762A4383-158A-4763-B14B-1CA408E2D54E}]**
**                                                                            **
** Syntax            : void Bfx_ClrBit_u8u8                                   **
**                     (                                                      **
**                       uint8* const Data,                                   **
**                       const uint8 BitPn                                    **
**                     )                                                      **
**                                                                            **
** Description       : The Bfx_ClrBit_u8u8 function clears the logical status **
**                     of the bit at BitPn bit position of the Data parameter **
**                     to 0.                                                  **
**                                                                            **
** [/cover]                                                                   **
**                                                                            **
** Service ID        : 0x06                                                   **
**                                                                            **
** Sync/Async        : Synchronous                                            **
**                                                                            **
** Reentrancy        : Reentrant for pointer to distinct memory location      **
**                     passed as parameter to the API                         **
**                                                                            **
** Parameters (in)   : BitPn - Bit position (Valid range: 0 to 7)             **
**                                                                            **
** Parameters(in-out): Data  - Pointer to data which is to be modified        **
**                                                                            **
** Parameters (out)  : None                                                   **
**                                                                            **
** Return value      : void                                                   **
*******************************************************************************/
void Bfx_ClrBit_u8u8(uint8* const Data, const uint8 BitPn)
{
  /* [cover parentID={4CD7E2E2-8845-4626-9B96-3BF100BAB684}]
  Clear bit at specified position
  [/cover] */
  Bfx_lInsert8Bits(Data, BFX_DEFAULT_STATUS_0_EIGHT_BITS, BitPn, \
                   BFX_DEFAULT_WIDTH);
}

/*******************************************************************************
** Traceability      : [cover parentID={DBD5C4F1-86CF-4d79-AB4A-70C83D46EBFC},**
**                                     {826C08F0-0107-42bf-9DCC-FABBFE7F9A19},**
**                                     {762A4383-158A-4763-B14B-1CA408E2D54E}]**
**                                                                            **
** Syntax            : void Bfx_ClrBit_u16u8                                  **
**                     (                                                      **
**                       uint16* const Data,                                  **
**                       const uint8 BitPn                                    **
**                     )                                                      **
**                                                                            **
** Description       : The Bfx_ClrBit_u16u8 function clears the logical status**
**                     of the bit at BitPn bit position of the Data parameter **
**                     to 0.                                                  **
**                                                                            **
** [/cover]                                                                   **
**                                                                            **
** Service ID        : 0x07                                                   **
**                                                                            **
** Sync/Async        : Synchronous                                            **
**                                                                            **
** Reentrancy        : Reentrant for pointer to distinct memory location      **
**                     passed as parameter to the API                         **
**                                                                            **
** Parameters (in)   : BitPn - Bit position (Valid range: 0 to 15)            **
**                                                                            **
** Parameters(in-out): Data  - Pointer to data which is to be modified        **
**                                                                            **
** Parameters (out)  : None                                                   **
**                                                                            **
** Return value      : void                                                   **
*******************************************************************************/
void Bfx_ClrBit_u16u8(uint16* const Data, const uint8 BitPn)
{
  /* [cover parentID={6C16625C-31DD-4163-B0FB-4FD8C120C37E}]
  Clear bit at specified position
  [/cover] */
  Bfx_lInsert16Bits(Data, BFX_DEFAULT_STATUS_0_SIXTEEN_BITS, BitPn, \
                    BFX_DEFAULT_WIDTH);
}

/*******************************************************************************
** Traceability      : [cover parentID={62A763AC-9D14-4c80-ABF0-B704131AAB58},**
**                                     {826C08F0-0107-42bf-9DCC-FABBFE7F9A19},**
**                                     {762A4383-158A-4763-B14B-1CA408E2D54E}]**
**                                                                            **
** Syntax            : void Bfx_ClrBit_u32u8                                  **
**                     (                                                      **
**                       uint32* const Data,                                  **
**                       const uint8 BitPn                                    **
**                     )                                                      **
**                                                                            **
** Description       : The Bfx_ClrBit_u32u8 function clears the logical status**
**                     of the bit at BitPn bit position of the Data parameter **
**                     to 0.                                                  **
**                                                                            **
** [/cover]                                                                   **
**                                                                            **
** Service ID        : 0x08                                                   **
**                                                                            **
** Sync/Async        : Synchronous                                            **
**                                                                            **
** Reentrancy        : Reentrant for pointer to distinct memory location      **
**                     passed as parameter to the API                         **
**                                                                            **
** Parameters (in)   : BitPn - Bit position (Valid range: 0 to 31)            **
**                                                                            **
** Parameters(in-out): Data  - Pointer to data which is to be modified        **
**                                                                            **
** Parameters (out)  : None                                                   **
**                                                                            **
** Return value      : void                                                   **
*******************************************************************************/
void Bfx_ClrBit_u32u8(uint32* const Data, const uint8 BitPn)
{
  /* [cover parentID={5F83395B-D398-4f2b-9F44-5EC5FD6D42C4}]
  Clear bit at specified position
  [/cover] */
  Bfx_lInsert32Bits(Data, BFX_DEFAULT_STATUS_0_THIRTYTWO_BITS, BitPn, \
                    BFX_DEFAULT_WIDTH);
}

/*******************************************************************************
** Traceability      : [cover parentID={71315A63-0AF7-4eda-805A-490B11311EC1},**
**                                     {826C08F0-0107-42bf-9DCC-FABBFE7F9A19},**
**                                     {762A4383-158A-4763-B14B-1CA408E2D54E}]**
**                                                                            **
** Syntax            : boolean Bfx_GetBit_u8u8_u8                             **
**                     (                                                      **
**                       const uint8 Data,                                    **
**                       const uint8 BitPn                                    **
**                     )                                                      **
**                                                                            **
** Description       : The Bfx_GetBit_u8u8_u8 function returns TRUE when the  **
**                     logical status of the bit at BitPn bit position of the **
**                     Data input parameter is 1, otherwise the function      **
**                     returns FALSE.                                         **
**                                                                            **
** [/cover]                                                                   **
**                                                                            **
** Service ID        : 0x0a                                                   **
**                                                                            **
** Sync/Async        : Synchronous                                            **
**                                                                            **
** Reentrancy        : Reentrant                                              **
**                                                                            **
** Parameters (in)   : Data  - Input data                                     **
**                     BitPn - Bit position (Valid range: 0 to 7)             **
**                                                                            **
** Parameters (out)  : None                                                   **
**                                                                            **
** Return value      : boolean - Bit status                                   **
**                               TRUE  :Extracted bit is 1                    **
**                               FALSE :Extracted bit is 0                    **
*******************************************************************************/
boolean Bfx_GetBit_u8u8_u8(const uint8 Data, const uint8 BitPn)
{
  boolean ResultValue;

  /* [cover parentID={5CA198FA-AFA9-4a19-B430-1AAE37B749ED}]
  Extract bit from specified position
  [/cover] */
  /* [cover parentID={6195BF51-0FE4-44a7-ACC2-DFF532F3D80A}]
  Is the extracted bit non zero?
  [/cover] */
  if (Bfx_lExtractBits((uint32)Data, BitPn, BFX_DEFAULT_WIDTH) != (uint32)0U)
  {
    /* [cover parentID={A27EAB3F-4A72-47f7-8BDC-ABBE454F6602}]
    Return result as TRUE
    [/cover] */
    ResultValue = (boolean)TRUE;
  }
  else
  {
    /* [cover parentID={A9B5261F-8CFB-4dd8-B86A-812C467C4FEF}]
    Return result as FALSE
    [/cover] */
    ResultValue = (boolean)FALSE;
  }

  return ResultValue;
}
/*******************************************************************************
** Traceability      : [cover parentID={4956B919-A293-408c-ADF9-616E751F9445},**
**                                     {826C08F0-0107-42bf-9DCC-FABBFE7F9A19},**
**                                     {762A4383-158A-4763-B14B-1CA408E2D54E}]**
**                                                                            **
** Syntax            : boolean Bfx_GetBit_u16u8_u8                            **
**                     (                                                      **
**                       const uint16 Data,                                   **
**                       const uint8 BitPn                                    **
**                     )                                                      **
**                                                                            **
** Description       : The Bfx_GetBit_u16u8_u8 function returns TRUE when the **
**                     logical status of the bit at BitPn bit position of the **
**                     Data input parameter is 1, otherwise the function      **
**                     returns FALSE.                                         **
**                                                                            **
** [/cover]                                                                   **
**                                                                            **
** Service ID        : 0x0b                                                   **
**                                                                            **
** Sync/Async        : Synchronous                                            **
**                                                                            **
** Reentrancy        : Reentrant                                              **
**                                                                            **
** Parameters (in)   : Data  - Input data                                     **
**                     BitPn - Bit position (Valid range: 0 to 15)            **
**                                                                            **
** Parameters (out)  : None                                                   **
**                                                                            **
** Return value      : boolean - Bit status                                   **
**                               TRUE  :Extracted bit is 1                    **
**                               FALSE :Extracted bit is 0                    **
*******************************************************************************/
boolean Bfx_GetBit_u16u8_u8(const uint16 Data, const uint8 BitPn)
{
  boolean ResultValue;

  /* [cover parentID={1ACB5F5E-8286-447b-98B6-D6D054B0D74E}]
  Extract bit from specified position
  [/cover] */
  /* [cover parentID={4C4332B7-767A-4a55-9C75-EABD6613E4B0}]
  Is the extracted bit non zero?
  [/cover] */
  if (Bfx_lExtractBits((uint32)Data, BitPn, BFX_DEFAULT_WIDTH) != (uint32)0U)
  {
    /* [cover parentID={729341D0-2C6A-4193-A56B-1C8FAE055B24}]
    Return result as TRUE
    [/cover] */
    ResultValue = (boolean)TRUE;
  }
  else
  {
    /* [cover parentID={645088C6-C793-4dfb-A482-401D54035194}]
    Return result as FALSE
    [/cover] */
    ResultValue = (boolean)FALSE;
  }

  return ResultValue;
}
/*******************************************************************************
** Traceability      : [cover parentID={50CFB84B-B110-4ea3-BABB-A562C79F2466},**
**                                     {826C08F0-0107-42bf-9DCC-FABBFE7F9A19},**
**                                     {762A4383-158A-4763-B14B-1CA408E2D54E}]**
**                                                                            **
** Syntax            : boolean Bfx_GetBit_u32u8_u8                            **
**                     (                                                      **
**                       const uint32 Data,                                   **
**                       const uint8 BitPn                                    **
**                     )                                                      **
**                                                                            **
** Description       : The Bfx_GetBit_u32u8_u8 function returns TRUE when the **
**                     logical status of the bit at BitPn bit position of the **
**                     Data input parameter is 1, otherwise the function      **
**                     returns FALSE.                                         **
**                                                                            **
** [/cover]                                                                   **
**                                                                            **
** Service ID        : 0x0c                                                   **
**                                                                            **
** Sync/Async        : Synchronous                                            **
**                                                                            **
** Reentrancy        : Reentrant                                              **
**                                                                            **
** Parameters (in)   : Data  - Input data                                     **
**                     BitPn - Bit position (Valid range: 0 to 31)            **
**                                                                            **
** Parameters (out)  : None                                                   **
**                                                                            **
** Return value      : boolean - Bit status                                   **
**                               TRUE  :Extracted bit is 1                    **
**                               FALSE :Extracted bit is 0                    **
*******************************************************************************/
boolean Bfx_GetBit_u32u8_u8(const uint32 Data, const uint8 BitPn)
{
  boolean ResultValue;

  /* [cover parentID={E401CCF3-055A-497e-9AE8-B574C2AF62CA}]
  Extract bit from specified position
  [/cover] */
  /* [cover parentID={884D5F95-47A1-4a95-9AFE-55F500634635}]
  Is the extracted bit non zero?
  [/cover] */
  if (Bfx_lExtractBits(Data, BitPn, BFX_DEFAULT_WIDTH) != (uint32)0U)
  {
    /* [cover parentID={F5FA5213-AA56-45c1-8924-9095E696310C}]
    Return result as TRUE
    [/cover] */
    ResultValue = (boolean)TRUE;
  }
  else
  {
    /* [cover parentID={C1D686ED-35B1-437c-AA0C-B57B2DCBA0AC}]
    Return result as FALSE
    [/cover] */
    ResultValue = (boolean)FALSE;
  }

  return ResultValue;
}

/*******************************************************************************
** Traceability      : [cover parentID={1B4F8CED-2663-4d2b-A5E7-1BE433FB06C7},**
**                                     {826C08F0-0107-42bf-9DCC-FABBFE7F9A19},**
**                                     {762A4383-158A-4763-B14B-1CA408E2D54E}]**
**                                                                            **
** Syntax            : void Bfx_SetBits_u8u8u8u8                              **
**                     (                                                      **
**                       uint8* const Data,                                   **
**                       const uint8 BitStartPn,                              **
**                       const uint8 BitLn,                                   **
**                       const uint8 Status                                   **
**                     )                                                      **
**                                                                            **
** Description       : The Bfx_SetBits_u8u8u8u8 function clears the logical   **
**                     status of the bits of the Data parameter starting from **
**                     BitStartPn bit position for BitLn number of bits to 0  **
**                     when the value of Status parameter is zero.            **
**                     Otherwise for non zero value of Status parameter, the  **
**                     function sets the logical status of the bits of the    **
**                     Data parameter starting from BitStartPn bit position   **
**                     for BitLn number of bits to 1.                         **
**                                                                            **
** [/cover]                                                                   **
**                                                                            **
** Service ID        : 0x20                                                   **
**                                                                            **
** Sync/Async        : Synchronous                                            **
**                                                                            **
** Reentrancy        : Reentrant for pointer to distinct memory location      **
**                     passed as parameter to the API                         **
**                                                                            **
** Parameters (in)   : BitStartPn - Start bit position (Valid range: 0 to 7)  **
**                     BitLn      - Bit field length                          **
**                                  (Valid range: 1 to (8 - BitStartPn))      **
**                     Status     - Status value to be set                    **
**                                                                            **
** Parameters(in-out): Data       - Pointer to data which is to be modified   **
**                                                                            **
** Parameters (out)  : None                                                   **
**                                                                            **
** Return value      : void                                                   **
*******************************************************************************/
void Bfx_SetBits_u8u8u8u8(uint8* const Data,
                          const uint8 BitStartPn,
                          const uint8 BitLn,
                          const uint8 Status)
{
  /* [cover parentID={E1D65739-F41E-47e0-8DCB-47F0C65BA653}]
  Initialize all the bits of the value to be inserted to 0
  [/cover] */

  uint8 SourceData = BFX_DEFAULT_STATUS_0_EIGHT_BITS;

  /* [cover parentID={C2C64356-4343-450a-A8F7-78FB07AEC3FD}]
  Is the status parameter passed to the API non zero?
  [/cover] */
  if (Status != 0U)
  {
    /* [cover parentID={E02F0FA7-6B27-4b68-9527-0C860B821095}]
    Update all the bits of the value to be inserted to 1
    [/cover] */
    SourceData = BFX_DEFAULT_STATUS_1_EIGHT_BITS;
  }

  /* [cover parentID={F4292F90-E346-432d-AAA1-D5DE7968EBC6}]
  Insert the specified number of bits of the value to be inserted into Data
  parameter starting from the specified position
  [/cover] */
  Bfx_lInsert8Bits(Data, SourceData, BitStartPn, BitLn);
}

/*******************************************************************************
** Traceability      : [cover parentID={EA541C21-B2D4-4c22-9033-5C6AB54CBF0A},**
**                                     {826C08F0-0107-42bf-9DCC-FABBFE7F9A19},**
**                                     {762A4383-158A-4763-B14B-1CA408E2D54E}]**
**                                                                            **
** Syntax            : void Bfx_SetBits_u16u8u8u8                             **
**                     (                                                      **
**                       uint16* const Data,                                  **
**                       const uint8 BitStartPn,                              **
**                       const uint8 BitLn,                                   **
**                       const uint8 Status                                   **
**                     )                                                      **
**                                                                            **
** Description       : The Bfx_SetBits_u16u8u8u8 function clears the logical  **
**                     status of the bits of the Data parameter starting from **
**                     BitStartPn bit position for BitLn number of bits to 0  **
**                     when the value of Status parameter is zero.            **
**                     Otherwise for non zero value of Status parameter, the  **
**                     function sets the logical status of the bits of the    **
**                     Data parameter starting from BitStartPn bit position   **
**                     for BitLn number of bits to 1.                         **
**                                                                            **
** [/cover]                                                                   **
**                                                                            **
** Service ID        : 0x21                                                   **
**                                                                            **
** Sync/Async        : Synchronous                                            **
**                                                                            **
** Reentrancy        : Reentrant for pointer to distinct memory location      **
**                     passed as parameter to the API                         **
**                                                                            **
** Parameters (in)   : BitStartPn - Start bit position (Valid range: 0 to 15) **
**                     BitLn      - Bit field length                          **
**                                  (Valid range: 1 to (16 - BitStartPn))     **
**                     Status     - Status value to be set                    **
**                                                                            **
** Parameters(in-out): Data       - Pointer to data which is to be modified   **
**                                                                            **
** Parameters (out)  : None                                                   **
**                                                                            **
** Return value      : void                                                   **
*******************************************************************************/
void Bfx_SetBits_u16u8u8u8(uint16* const Data,
                           const uint8 BitStartPn,
                           const uint8 BitLn,
                           const uint8 Status)
{
  /* [cover parentID={DBE57D26-E43D-475f-8A35-D63E9DBBBB30}]
  Initialize all the bits of the value to be inserted to 0
  [/cover] */
  uint16 SourceData = BFX_DEFAULT_STATUS_0_SIXTEEN_BITS;

  /* [cover parentID={BC973D4F-F38E-43ad-8EC3-5CA0F5EDED55}]
  Is the status parameter passed to the API non zero?
  [/cover] */
  if (Status != 0U)
  {
    /* [cover parentID={BA01C5E7-C80B-4c8d-8B73-979D789828F9}]
    Update all the bits of the value to be inserted to 1
    [/cover] */
    SourceData = BFX_DEFAULT_STATUS_1_SIXTEEN_BITS;
  }

  /* [cover parentID={EDBBE0F8-ADF6-40e8-9902-02777E7F2D05}]
  Insert the specified number of bits of the value to be inserted into Data
  parameter starting from the specified position
  [/cover] */
  Bfx_lInsert16Bits(Data, SourceData, BitStartPn, BitLn);
}

/*******************************************************************************
** Traceability      : [cover parentID={E8BF75C7-F05D-4f53-81B8-0C3AE2F33B46},**
**                                     {826C08F0-0107-42bf-9DCC-FABBFE7F9A19},**
**                                     {762A4383-158A-4763-B14B-1CA408E2D54E}]**
**                                                                            **
** Syntax            : void Bfx_SetBits_u32u8u8u8                             **
**                     (                                                      **
**                       uint32* const Data,                                  **
**                       const uint8 BitStartPn,                              **
**                       const uint8 BitLn,                                   **
**                       const uint8 Status                                   **
**                     )                                                      **
**                                                                            **
** Description       : The Bfx_SetBits_u32u8u8u8 function clears the logical  **
**                     status of the bits of the Data parameter starting from **
**                     BitStartPn bit position for BitLn number of bits to 0  **
**                     when the value of Status parameter is zero.            **
**                     Otherwise for non zero value of Status parameter, the  **
**                     function sets the logical status of the bits of the    **
**                     Data parameter starting from BitStartPn bit position   **
**                     for BitLn number of bits to 1.                         **
**                                                                            **
** [/cover]                                                                   **
**                                                                            **
** Service ID        : 0x22                                                   **
**                                                                            **
** Sync/Async        : Synchronous                                            **
**                                                                            **
** Reentrancy        : Reentrant for pointer to distinct memory location      **
**                     passed as parameter to the API                         **
**                                                                            **
** Parameters (in)   : BitStartPn - Start bit position (Valid range: 0 to 31) **
**                     BitLn      - Bit field length                          **
**                                  (Valid range: 1 to (32 - BitStartPn))     **
**                     Status     - Status value to be set                    **
**                                                                            **
** Parameters(in-out): Data       - Pointer to data which is to be modified   **
**                                                                            **
** Parameters (out)  : None                                                   **
**                                                                            **
** Return value      : void                                                   **
*******************************************************************************/
void Bfx_SetBits_u32u8u8u8(uint32* const Data,
                           const uint8 BitStartPn,
                           const uint8 BitLn,
                           const uint8 Status)
{
  /* [cover parentID={6D2D9D7E-432C-408e-9DC6-A33C60F7C74B}]
  Initialize all the bits of the value to be inserted to 0
  [/cover] */
  uint32 SourceData = BFX_DEFAULT_STATUS_0_THIRTYTWO_BITS;

  /* [cover parentID={1912FD23-C603-4d7b-8E73-0D6DFC3AC4D1}]
  Is the status parameter passed to the API non zero?
  [/cover] */
  if (Status != 0U)
  {
    /* [cover parentID={11E85383-518C-4bf5-A0ED-0C0C34369884}]
    Update all the bits of the value to be inserted to 1
    [/cover] */
    SourceData = BFX_DEFAULT_STATUS_1_THIRTYTWO_BITS;
  }

  /* [cover parentID={A555CF28-4802-4499-915B-5AD9F9EB098F}]
  Is number of bits to be modified 32?
  [/cover] */
  if (BitLn == BFX_MAX_LENGTH_32BIT)
  {
    /* [cover parentID={A4017B60-0DC7-4c03-BDE0-C612E38A9BD3}]
    Insert all the bits of the value to be inserted into Data parameter
    [/cover] */
    *Data = SourceData;
  }
  else
  {
    /* [cover parentID={EFD3F402-CD97-4191-A214-8A5523E74AE6}]
    Insert the specified number of bits of the value to be inserted into Data
    parameter starting from the specified position
    [/cover] */
    Bfx_lInsert32Bits(Data, SourceData, BitStartPn, BitLn);
  }
}

/*******************************************************************************
** Traceability      : [cover parentID={8B100A1A-4510-47a0-A747-A13F236D2938},**
**                                     {826C08F0-0107-42bf-9DCC-FABBFE7F9A19},**
**                                     {762A4383-158A-4763-B14B-1CA408E2D54E}]**
**                                                                            **
** Syntax            : uint8 Bfx_GetBits_u8u8u8_u8                            **
**                     (                                                      **
**                       const uint8 Data,                                    **
**                       const uint8 BitStartPn,                              **
**                       const uint8 BitLn                                    **
**                     )                                                      **
**                                                                            **
** Description       : The Bfx_GetBits_u8u8u8_u8 function returns the bits    **
**                     of the Data input parameter starting from BitStartPn   **
**                     bit position for BitLn number of bits.                 **
**                                                                            **
** [/cover]                                                                   **
**                                                                            **
** Service ID        : 0x26                                                   **
**                                                                            **
** Sync/Async        : Synchronous                                            **
**                                                                            **
** Reentrancy        : Reentrant                                              **
**                                                                            **
** Parameters (in)   : Data        - Input data                               **
**                     BitStartPn  - Start bit position (Valid range: 0 to 7) **
**                     BitLn       - Bit field length                         **
**                                   (Valid range: 1 to (8 - BitStartPn))     **
**                                                                            **
** Parameters(in-out): None                                                   **
**                                                                            **
** Parameters (out)  : None                                                   **
**                                                                            **
** Return value      : uint8      - Bits extracted from the input parameter   **
**                                                                            **
*******************************************************************************/
uint8 Bfx_GetBits_u8u8u8_u8(const uint8 Data,
                            const uint8 BitStartPn,
                            const uint8 BitLn)
{
  uint8 ResultValue;
  /* [cover parentID={D3C31030-989A-4761-ACFA-592CB5E424F6}]
  Extract specified number of bits starting from specified position
  [/cover] */
  ResultValue = (uint8)Bfx_lExtractBits((uint32)Data, BitStartPn, BitLn);

  /* [cover parentID={B23D85FE-7645-467d-A708-58F7195A8050}]
  Return the extracted bits
  [/cover] */
  return ResultValue;
}

/*******************************************************************************
** Traceability      : [cover parentID={EFDF924E-BB78-4322-8E9B-9F00854ECAF6},**
**                                     {826C08F0-0107-42bf-9DCC-FABBFE7F9A19},**
**                                     {762A4383-158A-4763-B14B-1CA408E2D54E}]**
**                                                                            **
** Syntax            : uint16 Bfx_GetBits_u16u8u8_u16                         **
**                     (                                                      **
**                       const uint16 Data,                                   **
**                       const uint8 BitStartPn,                              **
**                       const uint8 BitLn                                    **
**                     )                                                      **
**                                                                            **
** Description       : The Bfx_GetBits_u32u8u8_u32 function returns the bits  **
**                     of the Data input parameter starting from BitStartPn   **
**                     bit position for BitLn number of bits.                 **
**                                                                            **
** [/cover]                                                                   **
**                                                                            **
** Service ID        : 0x27                                                   **
**                                                                            **
** Sync/Async        : Synchronous                                            **
**                                                                            **
** Reentrancy        : Reentrant                                              **
**                                                                            **
** Parameters (in)   : Data        - Input data                               **
**                     BitStartPn  - Start bit position (Valid range: 0 to 15)**
**                     BitLn       - Bit field length                         **
**                                   (Valid range: 1 to (16 - BitStartPn))    **
**                                                                            **
** Parameters(in-out): None                                                   **
**                                                                            **
** Parameters (out)  : None                                                   **
**                                                                            **
** Return value      : uint16      - Bits extracted from the input parameter  **
**                                                                            **
*******************************************************************************/
uint16 Bfx_GetBits_u16u8u8_u16(const uint16 Data,
                               const uint8 BitStartPn,
                               const uint8 BitLn)
{
  uint16 ResultValue;

  /* [cover parentID={89014975-82DB-4ff9-9937-EDFF514863D1}]
  Extract specified number of bits starting from specified position
  [/cover] */
  ResultValue = (uint16)Bfx_lExtractBits((uint32)Data, BitStartPn, BitLn);

  /* [cover parentID={6783C927-AEFF-40db-A1A8-34A4CB491485}]
  Return the extracted bits
  [/cover] */
  return ResultValue;
}

/*******************************************************************************
** Traceability      : [cover parentID={7EE2F159-557F-4f9a-B5E5-380D9CB97CB0},**
**                                     {826C08F0-0107-42bf-9DCC-FABBFE7F9A19},**
**                                     {762A4383-158A-4763-B14B-1CA408E2D54E}]**
**                                                                            **
** Syntax            : uint32 Bfx_GetBits_u32u8u8_u32                         **
**                     (                                                      **
**                       const uint32 Data,                                   **
**                       const uint8 BitStartPn,                              **
**                       const uint8 BitLn                                    **
**                     )                                                      **
**                                                                            **
** Description       : The Bfx_GetBits_u32u8u8_u32 function returns the bits  **
**                     of the Data input parameter starting from BitStartPn   **
**                     bit position for BitLn number of bits.                 **
**                                                                            **
** [/cover]                                                                   **
**                                                                            **
** Service ID        : 0x28                                                   **
**                                                                            **
** Sync/Async        : Synchronous                                            **
**                                                                            **
** Reentrancy        : Reentrant                                              **
**                                                                            **
** Parameters (in)   : Data        - Input data                               **
**                     BitStartPn  - Start bit position (Valid range: 0 to 31)**
**                     BitLn       - Bit field length                         **
**                                   (Valid range: 1 to (32 - BitStartPn))    **
**                                                                            **
** Parameters(in-out): None                                                   **
**                                                                            **
** Parameters (out)  : None                                                   **
**                                                                            **
** Return value      : uint32      - Bits extracted from the input parameter  **
**                                                                            **
*******************************************************************************/
uint32 Bfx_GetBits_u32u8u8_u32(const uint32 Data,
                               const uint8 BitStartPn,
                               const uint8 BitLn)
{
  uint32 ResultValue;

  /* [cover parentID={5F0ACB68-1DAF-45fd-B8A3-3F948AE67CBA}]
  Is number of bits to be extracted 32?
  [/cover] */
  if (BitLn == BFX_MAX_LENGTH_32BIT)
  {
    /* [cover parentID={8E472D22-DD73-4fb6-A47A-A6392C22A120}]
    Extract all the bits
    [/cover] */
    ResultValue = Data;
  }
  else
  {
    /* [cover parentID={03144818-3D82-43c9-A651-539022A3C908}]
    Extract specified number of bits starting from specified position
    [/cover] */
    ResultValue = Bfx_lExtractBits(Data, BitStartPn, BitLn);
  }

  /* [cover parentID={29852CDD-50FD-45ab-86BF-EA018FC69225}]
  Return the extracted bits
  [/cover] */
  return ResultValue;
}

/*******************************************************************************
** Traceability      : [cover parentID={C231B55F-2892-4eab-85FD-0011AA3422A2},**
**                                     {826C08F0-0107-42bf-9DCC-FABBFE7F9A19},**
**                                     {762A4383-158A-4763-B14B-1CA408E2D54E}]**
**                                                                            **
** Syntax            : boolean Bfx_TstBitMask_u8u8_u8                         **
**                     (                                                      **
**                       const uint8 Data,                                    **
**                       const uint8 Mask                                     **
**                     )                                                      **
**                                                                            **
** Description       : The Bfx_TstBitMask_u8u8_u8 function returns TRUE when  **
**                     the logical status of all the bits defined in the Mask **
**                     parameter are also set at the same bit position in the **
**                     Data input parameter, otherwise the function returns   **
**                     FALSE.                                                 **
**                                                                            **
** [/cover]                                                                   **
**                                                                            **
** Service ID        : 0x36                                                   **
**                                                                            **
** Sync/Async        : Synchronous                                            **
**                                                                            **
** Reentrancy        : Reentrant                                              **
**                                                                            **
** Parameters (in)   : Data    - Input data                                   **
**                     Mask    - Mask value                                   **
**                                                                            **
** Parameters(in-out): None                                                   **
**                                                                            **
** Parameters (out)  : None                                                   **
**                                                                            **
** Return value      : boolean - Test result                                  **
**                               TRUE  :All bits defined in mask are set in   **
**                                      input parameter                       **
**                               FALSE :At least one bit defined in mask is   **
**                                      not set in input parameter            **
*******************************************************************************/
boolean Bfx_TstBitMask_u8u8_u8(const uint8 Data, const uint8 Mask)
{
  boolean ResultValue;

  /* [cover parentID={BA2B06BB-50AB-4b57-9D74-97F1AEECE684}]
  Is the value obtained by masking of data with specified mask same as the
  specified mask?
  [/cover] */
  if ((Data & Mask) == Mask)
  {
    /* [cover parentID={75FE7451-21C0-463c-8612-258143621E73}]
    Return result as TRUE
    [/cover] */
    ResultValue = (boolean)TRUE;
  }
  else
  {
    /* [cover parentID={2AB21B45-FB0C-4335-ADF9-02623FDA91C9}]
    Return result as FALSE
    [/cover] */
    ResultValue = (boolean)FALSE;
  }

  return ResultValue;
}

/*******************************************************************************
** Traceability      : [cover parentID={18881389-A2E8-41ad-A8F9-E2E1FD34F57E},**
**                                     {826C08F0-0107-42bf-9DCC-FABBFE7F9A19},**
**                                     {762A4383-158A-4763-B14B-1CA408E2D54E}]**
**                                                                            **
** Syntax            : boolean Bfx_TstBitMask_u16u16_u8                       **
**                     (                                                      **
**                       const uint16 Data,                                   **
**                       const uint16 Mask                                    **
**                     )                                                      **
**                                                                            **
** Description       : The Bfx_TstBitMask_u16u16_u8 function returns TRUE when**
**                     the logical status of all the bits defined in the Mask **
**                     parameter are also set at the same bit position in the **
**                     Data input parameter, otherwise the function returns   **
**                     FALSE.                                                 **
**                                                                            **
** [/cover]                                                                   **
**                                                                            **
** Service ID        : 0x37                                                   **
**                                                                            **
** Sync/Async        : Synchronous                                            **
**                                                                            **
** Reentrancy        : Reentrant                                              **
**                                                                            **
** Parameters (in)   : Data    - Input data                                   **
**                     Mask    - Mask value                                   **
**                                                                            **
** Parameters(in-out): None                                                   **
**                                                                            **
** Parameters (out)  : None                                                   **
**                                                                            **
** Return value      : boolean - Test result                                  **
**                               TRUE  :All bits defined in mask are set in   **
**                                      input parameter                       **
**                               FALSE :At least one bit defined in mask is   **
**                                      not set in input parameter            **
*******************************************************************************/
boolean Bfx_TstBitMask_u16u16_u8(const uint16 Data, const uint16 Mask)
{

  boolean ResultValue;

  /* [cover parentID={E6912A5A-377D-4601-B6D9-34BCF6C3E3E3}]
  Is the value obtained by masking of data with specified mask same as the
  specified mask?
  [/cover] */
  if ((Data & Mask) == Mask)
  {
    /* [cover parentID={6EBDBAEB-8288-4282-AAC1-7C02B88D15D9}]
    Return result as TRUE
    [/cover] */
    ResultValue = (boolean)TRUE;
  }
  else
  {
    /* [cover parentID={C6848A4D-6A92-4c26-8348-E059018A066E}]
    Return result as FALSE
    [/cover] */
    ResultValue = (boolean)FALSE;
  }

  return ResultValue;
}

/*******************************************************************************
** Traceability      : [cover parentID={047E0F26-5FC6-4da6-AA57-675C5AD55363},**
**                                     {826C08F0-0107-42bf-9DCC-FABBFE7F9A19},**
**                                     {762A4383-158A-4763-B14B-1CA408E2D54E}]**
**                                                                            **
** Syntax            : boolean Bfx_TstBitMask_u32u32_u8                       **
**                     (                                                      **
**                       const uint32 Data,                                   **
**                       const uint32 Mask                                    **
**                     )                                                      **
**                                                                            **
** Description       : The Bfx_TstBitMask_u32u32_u8 function returns TRUE when**
**                     the logical status of all the bits defined in the Mask **
**                     parameter are also set at the same bit position in the **
**                     Data input parameter, otherwise the function returns   **
**                     FALSE.                                                 **
**                                                                            **
** [/cover]                                                                   **
**                                                                            **
** Service ID        : 0x38                                                   **
**                                                                            **
** Sync/Async        : Synchronous                                            **
**                                                                            **
** Reentrancy        : Reentrant                                              **
**                                                                            **
** Parameters (in)   : Data    - Input data                                   **
**                     Mask    - Mask value                                   **
**                                                                            **
** Parameters(in-out): None                                                   **
**                                                                            **
** Parameters (out)  : None                                                   **
**                                                                            **
** Return value      : boolean - Test result                                  **
**                               TRUE  :All bits defined in mask are set in   **
**                                      input parameter                       **
**                               FALSE :At least one bit defined in mask is   **
**                                      not set in input parameter            **
*******************************************************************************/
boolean Bfx_TstBitMask_u32u32_u8(const uint32 Data, const uint32 Mask)
{
  boolean ResultValue;

  /* [cover parentID={7928FD72-5B90-4a68-863F-8338723A9976}]
  Is the value obtained by masking of data with specified mask same as the
  specified mask?
  [/cover] */
  if ((Data & Mask) == Mask)
  {
    /* [cover parentID={B73C97F5-BBD4-453c-BBA9-BFBE9B6001CD}]
    Return result as TRUE
    [/cover] */
    ResultValue = (boolean)TRUE;
  }
  else
  {
    /* [cover parentID={4333A9BA-4285-4dae-8621-68A32052CF99}]
    Return result as FALSE
    [/cover] */
    ResultValue = (boolean)FALSE;
  }

  return ResultValue;
}

/*******************************************************************************
** Traceability      : [cover parentID={E099C4F2-5F42-4571-832F-4EAF2F665EBB},**
**                                     {826C08F0-0107-42bf-9DCC-FABBFE7F9A19},**
**                                     {762A4383-158A-4763-B14B-1CA408E2D54E}]**
**                                                                            **
** Syntax            : boolean Bfx_TstBitLnMask_u8u8_u8                       **
**                     (                                                      **
**                       const uint8 Data,                                    **
**                       const uint8 Mask                                     **
**                     )                                                      **
**                                                                            **
** Description       : The Bfx_TstBitLnMask_u8u8_u8 function returns TRUE when**
**                     the logical status of at least one bit defined in the  **
**                     Mask parameter is also set at the same bit position in **
**                     the Data input parameter, otherwise the function       **
**                     returns FALSE.                                         **
**                                                                            **
** [/cover]                                                                   **
**                                                                            **
** Service ID        : 0x3a                                                   **
**                                                                            **
** Sync/Async        : Synchronous                                            **
**                                                                            **
** Reentrancy        : Reentrant                                              **
**                                                                            **
** Parameters (in)   : Mask    - Mask value                                   **
**                     Data    - Input data                                   **
**                                                                            **
** Parameters(in-out): None                                                   **
**                                                                            **
** Parameters (out)  : None                                                   **
**                                                                            **
** Return value      : boolean - Test result                                  **
**                               TRUE  :At least one bit defined in mask is   **
**                                      set in input parameter                **
**                               FALSE :No bit defined in mask is set in input**
**                                      parameter                             **
*******************************************************************************/
boolean Bfx_TstBitLnMask_u8u8_u8(const uint8 Data, const uint8 Mask)
{
  boolean ResultValue;

  /* [cover parentID={C8FC3BA4-C391-42f4-B05F-2A0237A316FA}]
  Is the value obtained by masking of data with specified mask non zero?
  [/cover] */
  if ((uint8)(Data & Mask) != 0U)
  {
    /* [cover parentID={DFB5E091-1BBD-42d4-884E-C7A3E4A1FCB2}]
    Return result as TRUE
    [/cover] */
    ResultValue = (boolean)TRUE;
  }
  else
  {
    /* [cover parentID={0722B7F1-7B9E-490f-82AE-E9107C9D9BEB}]
    Return result as FALSE
    [/cover] */
    ResultValue = (boolean)FALSE;
  }

  return ResultValue;
}

/*******************************************************************************
** Traceability      : [cover parentID={1D0D1F15-2C3B-409a-B155-B6587E7AE23A},**
**                                     {826C08F0-0107-42bf-9DCC-FABBFE7F9A19},**
**                                     {762A4383-158A-4763-B14B-1CA408E2D54E}]**
**                                                                            **
** Syntax            : boolean Bfx_TstBitLnMask_u16u16_u8                     **
**                     (                                                      **
**                       const uint16 Data,                                   **
**                       const uint16 Mask                                    **
**                     )                                                      **
**                                                                            **
** Description       : The Bfx_TstBitLnMask_u16u16_u8 function returns TRUE   **
**                     when the logical status of at least one bit defined in **
**                     the Mask parameter is also set at the same bit position**
**                     in the Data input parameter, otherwise the function    **
**                     returns FALSE.                                         **
**                                                                            **
** [/cover]                                                                   **
**                                                                            **
** Service ID        : 0x3b                                                   **
**                                                                            **
** Sync/Async        : Synchronous                                            **
**                                                                            **
** Reentrancy        : Reentrant                                              **
**                                                                            **
** Parameters (in)   : Mask    - Mask value                                   **
**                     Data    - Input data                                   **
**                                                                            **
** Parameters(in-out): None                                                   **
**                                                                            **
** Parameters (out)  : None                                                   **
**                                                                            **
** Return value      : boolean - Test result                                  **
**                               TRUE  :At least one bit defined in mask is   **
**                                      set in input parameter                **
**                               FALSE :No bit defined in mask is set in input**
**                                      parameter                             **
*******************************************************************************/
boolean Bfx_TstBitLnMask_u16u16_u8(const uint16 Data, const uint16 Mask)
{
  boolean ResultValue;

  /* [cover parentID={8793782E-37DD-4dc8-BA4C-360909EC25EB}]
  Is the value obtained by masking of data with specified mask non zero?
  [/cover] */
  if (((uint16)(Data & Mask)) != 0U)
  {
    /* [cover parentID={9B95AE81-62AD-4f9c-9662-7AA7C3CCCDC9}]
    Return result as TRUE
    [/cover] */
    ResultValue = (boolean)TRUE;
  }
  else
  {
    /* [cover parentID={9FEA854F-6765-4590-AA15-1F9AA64EBFE2}]
    Return result as FALSE
    [/cover] */
    ResultValue = (boolean)FALSE;
  }

  return ResultValue;
}

/*******************************************************************************
** Traceability      : [cover parentID={455E950E-6409-47f0-ACA1-517EFFA6ECD9},**
**                                     {826C08F0-0107-42bf-9DCC-FABBFE7F9A19},**
**                                     {762A4383-158A-4763-B14B-1CA408E2D54E}]**
**                                                                            **
** Syntax            : boolean Bfx_TstBitLnMask_u32u32_u8                     **
**                     (                                                      **
**                       const uint32 Data,                                   **
**                       const uint32 Mask                                    **
**                     )                                                      **
**                                                                            **
** Description       : The Bfx_TstBitLnMask_u32u32_u8 function returns TRUE   **
**                     when the logical status of at least one bit defined in **
**                     the Mask parameter is also set at the same bit position**
**                     in the Data input parameter, otherwise the function    **
**                     returns FALSE.                                         **
**                                                                            **
** [/cover]                                                                   **
**                                                                            **
** Service ID        : 0x3c                                                   **
**                                                                            **
** Sync/Async        : Synchronous                                            **
**                                                                            **
** Reentrancy        : Reentrant                                              **
**                                                                            **
** Parameters (in)   : Mask    - Mask value                                   **
**                     Data    - Input data                                   **
**                                                                            **
** Parameters(in-out): None                                                   **
**                                                                            **
** Parameters (out)  : None                                                   **
**                                                                            **
** Return value      : boolean - Test result                                  **
**                               TRUE  :At least one bit defined in mask is   **
**                                      set in input parameter                **
**                               FALSE :No bit defined in mask is set in input**
**                                      parameter                             **
*******************************************************************************/
boolean Bfx_TstBitLnMask_u32u32_u8(const uint32 Data, const uint32 Mask)
{
  boolean ResultValue;

  /* [cover parentID={B87AF996-9C39-426d-A502-536A2E507443}]
  Is the value obtained by masking of data with specified mask non zero?
  [/cover] */
  if((Data & Mask) != 0U)
  {
    /* [cover parentID={3742E0D6-AEDC-4238-A757-A73294C5C4BF}]
    Return result as TRUE
    [/cover] */
    ResultValue = (boolean)TRUE;
  }
  else
  {
    /* [cover parentID={709DD6A3-EFF3-4ac9-B7EA-3993E565C8C9}]
    Return result as FALSE
    [/cover] */
    ResultValue = (boolean)FALSE;
  }

  return ResultValue;
}

/*******************************************************************************
** Traceability      : [cover parentID={7CAFBB18-DCD8-4979-847B-C77AF5C6D779},**
**                                     {826C08F0-0107-42bf-9DCC-FABBFE7F9A19},**
**                                     {762A4383-158A-4763-B14B-1CA408E2D54E}]**
**                                                                            **
** Syntax            : boolean Bfx_TstParityEven_u8_u8                        **
**                     (                                                      **
**                       const uint8 Data                                     **
**                     )                                                      **
**                                                                            **
** Description       : The Bfx_TstParityEven_u8_u8 function returns TRUE when **
**                     the logical status of even number of bits in the Data  **
**                     input parameter is set to 1, otherwise the function    **
**                     returns FALSE.                                         **
**                                                                            **
** [/cover]                                                                   **
**                                                                            **
** Service ID        : 0x40                                                   **
**                                                                            **
** Sync/Async        : Synchronous                                            **
**                                                                            **
** Reentrancy        : Reentrant                                              **
**                                                                            **
** Parameters (in)   : Data    - Input data                                   **
**                                                                            **
** Parameters(in-out): None                                                   **
**                                                                            **
** Parameters (out)  : None                                                   **
**                                                                            **
** Return value      : boolean - Test result                                  **
**                               TRUE  :Parity of input parameter is even     **
**                               FALSE :Parity of input parameter is odd      **
*******************************************************************************/
boolean Bfx_TstParityEven_u8_u8(const uint8 Data)
{
  boolean ResultValue;

  /* [cover parentID={FFA292AE-B84D-4877-93A5-073C38DCF3B6}]
  Compute the odd parity for Data
  [/cover] */
  /* [cover parentID={9940BDBE-D9B4-4c08-96F2-07F4AD30EDD3}]
  Is the computed odd parity zero?
  [/cover] */
  if (Bfx_lParity((uint32)Data) == 0U)
  {
    /* [cover parentID={DD015841-4DCE-41af-9540-F13BDE99DD33}]
    Return result as TRUE
    [/cover] */
    ResultValue = (boolean)TRUE;
  }
  else
  {
    /* [cover parentID={C977E1FD-C53F-4581-A263-1D9CCD422BB1}]
    Return result as FALSE
    [/cover] */
    ResultValue = (boolean)FALSE;
  }

  return ResultValue;
}

/*******************************************************************************
** Traceability      : [cover parentID={ACCFECED-0AB4-4f6e-87AA-75CF0CFDD289},**
**                                     {826C08F0-0107-42bf-9DCC-FABBFE7F9A19},**
**                                     {762A4383-158A-4763-B14B-1CA408E2D54E}]**
**                                                                            **
** Syntax            : boolean Bfx_TstParityEven_u16_u8                       **
**                     (                                                      **
**                       const uint16 Data                                    **
**                     )                                                      **
**                                                                            **
** Description       : The Bfx_TstParityEven_u16_u8 function returns TRUE when**
**                     the logical status of even number of bits in the Data  **
**                     input parameter is set to 1, otherwise the function    **
**                     returns FALSE.                                         **
**                                                                            **
** [/cover]                                                                   **
**                                                                            **
** Service ID        : 0x41                                                   **
**                                                                            **
** Sync/Async        : Synchronous                                            **
**                                                                            **
** Reentrancy        : Reentrant                                              **
**                                                                            **
** Parameters (in)   : Data    - Input data                                   **
**                                                                            **
** Parameters(in-out): None                                                   **
**                                                                            **
** Parameters (out)  : None                                                   **
**                                                                            **
** Return value      : boolean - Test result                                  **
**                               TRUE  :Parity of input parameter is even     **
**                               FALSE :Parity of input parameter is odd      **
*******************************************************************************/
boolean Bfx_TstParityEven_u16_u8(const uint16 Data)
{
  boolean ResultValue;

  /* [cover parentID={0198EA53-C7FA-4907-947E-7AA7D3099A95}]
  Compute the odd parity for Data
  [/cover] */
  /* [cover parentID={66F9708F-AD3C-4a5f-AFDB-8573DD506908}]
  Is the computed odd parity zero?
  [/cover] */
  if (Bfx_lParity((uint32)Data) == 0U)
  {
    /* [cover parentID={DE997520-7AC1-4445-92CE-F467556E63B5}]
    Return result as TRUE
    [/cover] */
    ResultValue = (boolean)TRUE;
  }
  else
  {
    /* [cover parentID={DBE8E9C7-27D0-4a4c-AA94-523236B94016}]
    Return result as FALSE
    [/cover] */
    ResultValue = (boolean)FALSE;
  }

  return ResultValue;
}

/*******************************************************************************
** Traceability      : [cover parentID={5D85A155-22CA-446f-81D8-9A10FDAE0E7F},**
**                                     {826C08F0-0107-42bf-9DCC-FABBFE7F9A19},**
**                                     {762A4383-158A-4763-B14B-1CA408E2D54E}]**
**                                                                            **
** Syntax            : boolean Bfx_TstParityEven_u32_u8                       **
**                     (                                                      **
**                       const uint32 Data                                    **
**                     )                                                      **
**                                                                            **
** Description       : The Bfx_TstParityEven_u32_u8 function returns TRUE when**
**                     the logical status of even number of bits in the Data  **
**                     input parameter is set to 1, otherwise the function    **
**                     returns FALSE.                                         **
**                                                                            **
** [/cover]                                                                   **
**                                                                            **
** Service ID        : 0x42                                                   **
**                                                                            **
** Sync/Async        : Synchronous                                            **
**                                                                            **
** Reentrancy        : Reentrant                                              **
**                                                                            **
** Parameters (in)   : Data    - Input data                                   **
**                                                                            **
** Parameters(in-out): None                                                   **
**                                                                            **
** Parameters (out)  : None                                                   **
**                                                                            **
** Return value      : boolean - Test result                                  **
**                               TRUE  :Parity of input parameter is even     **
**                               FALSE :Parity of input parameter is odd      **
*******************************************************************************/
boolean Bfx_TstParityEven_u32_u8(const uint32 Data)
{
  boolean ResultValue;

  /* [cover parentID={459736C3-3E5A-4a2f-B277-B017CE380BBF}]
  Compute the odd parity for Data
  [/cover] */
  /* [cover parentID={DAADB693-D551-4eb3-A0E8-1B0182932A11}]
  Is the computed odd parity zero?
  [/cover] */
  if (Bfx_lParity(Data) == 0U)
  {
    /* [cover parentID={F7DC956A-8A22-4b58-ACC4-45E191AEEA5C}]
    Return result as TRUE
    [/cover] */
    ResultValue = (boolean)TRUE;
  }
  else
  {
    /* [cover parentID={CFA10C19-EED6-4869-B564-7D361CE332AC}]
    Return result as FALSE
    [/cover] */
    ResultValue = (boolean)FALSE;
  }

  return ResultValue;
}

/*******************************************************************************
** Traceability      : [cover parentID={794A96C2-AF39-4566-83B3-B82884C5648C},**
**                                     {826C08F0-0107-42bf-9DCC-FABBFE7F9A19},**
**                                     {762A4383-158A-4763-B14B-1CA408E2D54E}]**
**                                                                            **
** Syntax            : void Bfx_CopyBit_u8u8u8u8                              **
**                     (                                                      **
**                       uint8* const DestinationData,                        **
**                       const uint8 DestinationPosition,                     **
**                       const uint8 SourceData,                              **
**                       const uint8 SourcePosition                           **
**                     )                                                      **
**                                                                            **
** Description       : The Bfx_CopyBit_u8u8u8u8 function copies a bit at      **
**                     SourcePosition bit position of the SourceData parameter**
**                     to DestinationPosition bit position of the             **
**                     DestinationData parameter.                             **
**                                                                            **
** [/cover]                                                                   **
**                                                                            **
** Service ID        : 0x66                                                   **
**                                                                            **
** Sync/Async        : Synchronous                                            **
**                                                                            **
** Reentrancy        : Reentrant for pointer to distinct memory location      **
**                     passed as parameter to the API                         **
**                                                                            **
** Parameters (in)   : DestinationPosition  - Destination bit position        **
**                                            (Valid range: 0 to 7)           **
**                     SourceData           - Source data                     **
**                     SourcePosition       - Source bit position             **
**                                            (Valid range: 0 to 7)           **
**                                                                            **
** Parameters(in-out): DestinationData      - Pointer to destination data     **
**                                            which is to be modified         **
**                                                                            **
** Parameters (out)  : None                                                   **
**                                                                            **
** Return value      : void                                                   **
*******************************************************************************/
void Bfx_CopyBit_u8u8u8u8(uint8* const DestinationData,
                          const uint8 DestinationPosition,
                          const uint8 SourceData,
                          const uint8 SourcePosition)
{
  /* [cover parentID={9E96AC6C-182A-4d6b-9C5B-48F7FC68B27F}]
  Extract the bit at the specified position of SourceData
  [/cover] */
  uint32 Status = Bfx_lExtractBits((uint32)SourceData, SourcePosition, \
                                   BFX_DEFAULT_WIDTH);
  /* [cover parentID={4B8502B7-E3B5-4942-871A-A97CC5CE6775}]
  Insert the extracted bit at specified position of DestinationData
  [/cover] */
  Bfx_lInsert8Bits(DestinationData, (uint8)Status, \
                   DestinationPosition, BFX_DEFAULT_WIDTH);
}

/*******************************************************************************
** Traceability      : [cover parentID={9BD3929F-8DE0-4dbc-9F86-DC1195384BC5},**
**                                     {826C08F0-0107-42bf-9DCC-FABBFE7F9A19},**
**                                     {762A4383-158A-4763-B14B-1CA408E2D54E}]**
**                                                                            **
** Syntax            : void Bfx_CopyBit_u16u8u16u8                            **
**                     (                                                      **
**                       uint16* const DestinationData,                       **
**                       const uint8 DestinationPosition,                     **
**                       const uint16 SourceData,                             **
**                       const uint8 SourcePosition                           **
**                     )                                                      **
**                                                                            **
** Description       : The Bfx_CopyBit_u16u8u16u8 function copies a bit at    **
**                     SourcePosition bit position of the SourceData parameter**
**                     to DestinationPosition bit position of the             **
**                     DestinationData parameter.                             **
**                                                                            **
** [/cover]                                                                   **
**                                                                            **
** Service ID        : 0x67                                                   **
**                                                                            **
** Sync/Async        : Synchronous                                            **
**                                                                            **
** Reentrancy        : Reentrant for pointer to distinct memory location      **
**                     passed as parameter to the API                         **
**                                                                            **
** Parameters (in)   : DestinationPosition  - Destination bit position        **
**                                            (Valid range: 0 to 15)          **
**                     SourceData           - Source data                     **
**                     SourcePosition       - Source bit position             **
**                                            (Valid range: 0 to 15)          **
**                                                                            **
** Parameters(in-out): DestinationData      - Pointer to destination data     **
**                                            which is to be modified         **
**                                                                            **
** Parameters (out)  : None                                                   **
**                                                                            **
** Return value      : void                                                   **
*******************************************************************************/
void Bfx_CopyBit_u16u8u16u8(uint16* const DestinationData,
                            const uint8 DestinationPosition,
                            const uint16 SourceData,
                            const uint8 SourcePosition)
{
  /* [cover parentID={982AE1DD-E1E7-4ff2-ABE9-77CBCE08F140}]
  Extract the bit at the specified position of SourceData
  [/cover] */
  uint32 Status = Bfx_lExtractBits((uint32)SourceData, SourcePosition, \
                                   BFX_DEFAULT_WIDTH);
  /* [cover parentID={9CADCBC1-2F61-445f-9E3F-5C5ED4E7F254}]
  Insert the extracted bit at specified position of DestinationData
  [/cover] */
  Bfx_lInsert16Bits(DestinationData, (uint16)Status, \
                    DestinationPosition, BFX_DEFAULT_WIDTH);
}

/*******************************************************************************
** Traceability      : [cover parentID={10421E8B-E1D7-484b-91BD-79D678CEC458},**
**                                     {826C08F0-0107-42bf-9DCC-FABBFE7F9A19},**
**                                     {762A4383-158A-4763-B14B-1CA408E2D54E}]**
**                                                                            **
** Syntax            : void Bfx_CopyBit_u32u8u32u8                            **
**                     (                                                      **
**                       uint32* const DestinationData,                       **
**                       const uint8 DestinationPosition,                     **
**                       const uint32 SourceData,                             **
**                       const uint8 SourcePosition                           **
**                     )                                                      **
**                                                                            **
** Description       : The Bfx_CopyBit_u32u8u32u8 function copies a bit at    **
**                     SourcePosition bit position of the SourceData parameter**
**                     to DestinationPosition bit position of the             **
**                     DestinationData parameter.                             **
**                                                                            **
** [/cover]                                                                   **
**                                                                            **
** Service ID        : 0x68                                                   **
**                                                                            **
** Sync/Async        : Synchronous                                            **
**                                                                            **
** Reentrancy        : Reentrant for pointer to distinct memory location      **
**                     passed as parameter to the API                         **
**                                                                            **
** Parameters (in)   : DestinationPosition  - Destination bit position        **
**                                            (Valid range: 0 to 31)          **
**                     SourceData           - Source data                     **
**                     SourcePosition       - Source bit position             **
**                                            (Valid range: 0 to 31)          **
**                                                                            **
** Parameters(in-out): DestinationData      - Pointer to destination data     **
**                                            which is to be modified         **
**                                                                            **
** Parameters (out)  : None                                                   **
**                                                                            **
** Return value      : void                                                   **
*******************************************************************************/
void Bfx_CopyBit_u32u8u32u8(uint32* const DestinationData,
                            const uint8 DestinationPosition,
                            const uint32 SourceData,
                            const uint8 SourcePosition)
{
  /* [cover parentID={45CBD19C-C1C1-428e-9F65-5AEE0CBC7D39}]
  Extract the bit at the specified position of SourceData
  [/cover] */
  uint32 Status = Bfx_lExtractBits(SourceData, SourcePosition, \
                                   BFX_DEFAULT_WIDTH);
  /* [cover parentID={7DBAC541-F1C7-4ebd-BAFD-8E5845F85A04}]
  Insert the extracted bit at specified position of DestinationData
  [/cover] */
  Bfx_lInsert32Bits(DestinationData, Status, \
                    DestinationPosition, BFX_DEFAULT_WIDTH);
}

/*******************************************************************************
** Traceability      : [cover parentID={FEF4C275-13FB-4180-AF6F-B7A556C304CC},**
**                                     {826C08F0-0107-42bf-9DCC-FABBFE7F9A19},**
**                                     {762A4383-158A-4763-B14B-1CA408E2D54E}]**
**                                                                            **
** Syntax            : void Bfx_PutBits_u8u8u8u8                              **
**                     (                                                      **
**                       uint8* const Data,                                   **
**                       const uint8 BitStartPn,                              **
**                       const uint8 BitLn,                                   **
**                       const uint8 Pattern                                  **
**                     )                                                      **
**                                                                            **
** Description       : The Bfx_PutBits_u8u8u8u8 function copies the bit       **
**                     pattern from the Pattern parameter starting from 0 bit **
**                     position for BitLn number of bits into the Data        **
**                     parameter at the bit positions starting from BitStartPn**
**                     bit position for BitLn number of bits.                 **
**                                                                            **
** [/cover]                                                                   **
**                                                                            **
** Service ID        : 0x70                                                   **
**                                                                            **
** Sync/Async        : Synchronous                                            **
**                                                                            **
** Reentrancy        : Reentrant for pointer to distinct memory location      **
**                     passed as parameter to the API                         **
**                                                                            **
** Parameters (in)   : BitStartPn - Start bit position (Valid range: 0 to 7)  **
**                     BitLn      - Bit field length                          **
**                                  (Valid range: 1 to (8 - BitStartPn))      **
**                     Pattern    - Bit pattern to be set                     **
**                                                                            **
** Parameters(in-out): Data       - Pointer to destination data which is to be**
**                                  modified                                  **
**                                                                            **
** Parameters (out)  : None                                                   **
**                                                                            **
** Return value      : void                                                   **
*******************************************************************************/
void Bfx_PutBits_u8u8u8u8(uint8* const Data,
                          const uint8 BitStartPn,
                          const uint8 BitLn,
                          const uint8 Pattern)
{
  /* [cover parentID={4D312315-EC08-4f98-9DE9-FB0A29DE063E}]
  Insert the the specified number of bits from the Pattern into the Data
  starting from specified position
  [/cover] */
  Bfx_lInsert8Bits(Data, Pattern, BitStartPn, BitLn);
}

/*******************************************************************************
** Traceability      : [cover parentID={F323A140-7F49-4026-97D2-7E13215CF3DE},**
**                                     {826C08F0-0107-42bf-9DCC-FABBFE7F9A19},**
**                                     {762A4383-158A-4763-B14B-1CA408E2D54E}]**
**                                                                            **
** Syntax            : void Bfx_PutBits_u16u8u8u16                            **
**                     (                                                      **
**                       uint16* const Data,                                  **
**                       const uint8 BitStartPn,                              **
**                       const uint8 BitLn,                                   **
**                       const uint16 Pattern                                 **
**                     )                                                      **
**                                                                            **
** Description       : The Bfx_PutBits_u16u8u8u16 function copies the bit     **
**                     pattern from the Pattern parameter starting from 0 bit **
**                     position for BitLn number of bits into the Data        **
**                     parameter at the bit positions starting from BitStartPn**
**                     bit position for BitLn number of bits.                 **
**                                                                            **
** [/cover]                                                                   **
**                                                                            **
** Service ID        : 0x71                                                   **
**                                                                            **
** Sync/Async        : Synchronous                                            **
**                                                                            **
** Reentrancy        : Reentrant for pointer to distinct memory location      **
**                     passed as parameter to the API                         **
**                                                                            **
** Parameters (in)   : BitStartPn - Start bit position (Valid range: 0 to 15) **
**                     BitLn      - Bit field length                          **
**                                  (Valid range: 1 to (16 - BitStartPn))     **
**                     Pattern    - Bit pattern to be set                     **
**                                                                            **
** Parameters(in-out): Data       - Pointer to destination data which is to be**
**                                  modified                                  **
**                                                                            **
** Parameters (out)  : None                                                   **
**                                                                            **
** Return value      : void                                                   **
*******************************************************************************/
void Bfx_PutBits_u16u8u8u16(uint16* const Data,
                            const uint8 BitStartPn,
                            const uint8 BitLn,
                            const uint16 Pattern)
{
  /* [cover parentID={68993B6E-C74F-4704-A8F3-7C61DB45464A}]
  Insert the the specified number of bits from the Pattern into the Data
  starting from specified position
  [/cover] */
  Bfx_lInsert16Bits(Data, Pattern, BitStartPn, BitLn);
}

/*******************************************************************************
** Traceability      : [cover parentID={062A0EF3-0804-43a8-944C-5437894297DA},**
**                                     {826C08F0-0107-42bf-9DCC-FABBFE7F9A19},**
**                                     {762A4383-158A-4763-B14B-1CA408E2D54E}]**
**                                                                            **
** Syntax            : void Bfx_PutBits_u32u8u8u32                            **
**                     (                                                      **
**                       uint32* const Data,                                  **
**                       const uint8 BitStartPn,                              **
**                       const uint8 BitLn,                                   **
**                       const uint32 Pattern                                 **
**                     )                                                      **
**                                                                            **
** Description       : The Bfx_PutBits_u32u8u8u32 function copies the bit     **
**                     pattern from the Pattern parameter starting from 0 bit **
**                     position for BitLn number of bits into the Data        **
**                     parameter at the bit positions starting from BitStartPn**
**                     bit position for BitLn number of bits.                 **
**                                                                            **
** [/cover]                                                                   **
**                                                                            **
** Service ID        : 0x72                                                   **
**                                                                            **
** Sync/Async        : Synchronous                                            **
**                                                                            **
** Reentrancy        : Reentrant for pointer to distinct memory location      **
**                     passed as parameter to the API                         **
**                                                                            **
** Parameters (in)   : BitStartPn - Start bit position (Valid range: 0 to 31) **
**                     BitLn      - Bit field length                          **
**                                  (Valid range: 1 to (32 - BitStartPn))     **
**                     Pattern    - Bit pattern to be set                     **
**                                                                            **
** Parameters(in-out): Data       - Pointer to destination data which is to be**
**                                  modified                                  **
**                                                                            **
** Parameters (out)  : None                                                   **
**                                                                            **
** Return value      : void                                                   **
*******************************************************************************/
void Bfx_PutBits_u32u8u8u32(uint32* const Data,
                            const uint8 BitStartPn,
                            const uint8 BitLn,
                            const uint32 Pattern)
{
  /* [cover parentID={E30DFEE8-1F52-4713-A3DF-1E3F2DF35976}]
  Is number of bits to be modified 32?
  [/cover] */
  if(BitLn == BFX_MAX_LENGTH_32BIT)
  {
    /* [cover parentID={34B5CC33-2CA2-4703-81B8-236A68DACE92}]
    Insert all the bits of Pattern into Data
    [/cover] */
    *Data = Pattern;
  }
  else
  {
    /* [cover parentID={BF805070-A2BF-40bf-8B46-BB7098EE64D8}]
    Insert the the specified number of bits from Pattern into Data starting from
    specified position
    [/cover] */
    Bfx_lInsert32Bits(Data, Pattern, BitStartPn, BitLn);
  }
}

/*******************************************************************************
** Traceability      : [cover parentID={AEACC909-ED92-4e45-97A7-13BB2DAD64BD},**
**                                     {826C08F0-0107-42bf-9DCC-FABBFE7F9A19},**
**                                     {762A4383-158A-4763-B14B-1CA408E2D54E}]**
**                                                                            **
** Syntax            : void Bfx_PutBit_u8u8u8                                 **
**                     (                                                      **
**                       uint8* const Data,                                   **
**                       const uint8 BitPn,                                   **
**                       const boolean Status                                 **
**                     )                                                      **
**                                                                            **
** Description       : The Bfx_PutBit_u8u8u8 function updates the logical     **
**                     status of the bit at BitPn bit position of the Data    **
**                     parameter to 1 when the value of Status parameter is   **
**                     TRUE, otherwise the function updates the logical status**
**                     of the bit at BitPn bit position of the Data parameter **
**                     to 0.                                                  **
**                                                                            **
** [/cover]                                                                   **
**                                                                            **
** Service ID        : 0x85                                                   **
**                                                                            **
** Sync/Async        : Synchronous                                            **
**                                                                            **
** Reentrancy        : Reentrant for pointer to distinct memory location      **
**                     passed as parameter to the API                         **
**                                                                            **
** Parameters (in)   : BitPn  - Bit position (Valid range: 0 to 7)            **
**                     Status - Status value (Valid values: TRUE or FALSE)    **
**                                                                            **
** Parameters(in-out): Data   - Pointer to data which is to be modified       **
**                                                                            **
** Parameters (out)  : None                                                   **
**                                                                            **
** Return value      : void                                                   **
*******************************************************************************/
void Bfx_PutBit_u8u8u8(uint8* const Data,
                       const uint8 BitPn,
                       const boolean Status)
{
  /* [cover parentID={37F27069-B388-46e6-A736-4CFE653624C2}]
  Is the status parameter passed to the API TRUE?
  [/cover] */
  if(Status == (boolean)TRUE)
  {
    /* [cover parentID={8A49161A-E95A-4756-AC49-BA373035C2E0}]
    Set the bit at the specified position
    [/cover] */
    Bfx_lInsert8Bits(Data, BFX_DEFAULT_STATUS_1_EIGHT_BITS, \
                     BitPn, BFX_DEFAULT_WIDTH);
  }
  else
  {
    /* [cover parentID={24D4E1B2-3033-4baf-9AAE-203F880FD945}]
    Clear the bit at the specified position
    [/cover] */
    Bfx_lInsert8Bits(Data, BFX_DEFAULT_STATUS_0_EIGHT_BITS, \
                     BitPn, BFX_DEFAULT_WIDTH);
  }
}

/*******************************************************************************
** Traceability      : [cover parentID={E7F683A0-091D-431e-8C5D-2B829E0890D1},**
**                                     {826C08F0-0107-42bf-9DCC-FABBFE7F9A19},**
**                                     {762A4383-158A-4763-B14B-1CA408E2D54E}]**
**                                                                            **
** Syntax            : void Bfx_PutBit_u16u8u8                                **
**                     (                                                      **
**                       uint16* const Data,                                  **
**                       const uint8 BitPn,                                   **
**                       const boolean Status                                 **
**                     )                                                      **
**                                                                            **
** Description       : The Bfx_PutBit_u16u8u8 function updates the logical    **
**                     status of the bit at BitPn bit position of the Data    **
**                     parameter to 1 when the value of Status parameter is   **
**                     TRUE, otherwise the function updates the logical status**
**                     of the bit at BitPn bit position of the Data parameter **
**                     to 0.                                                  **
**                                                                            **
** [/cover]                                                                   **
**                                                                            **
** Service ID        : 0x86                                                   **
**                                                                            **
** Sync/Async        : Synchronous                                            **
**                                                                            **
** Reentrancy        : Reentrant for pointer to distinct memory location      **
**                     passed as parameter to the API                         **
**                                                                            **
** Parameters (in)   : BitPn  - Bit position (Valid range: 0 to 15)           **
**                     Status - Status value (Valid values: TRUE or FALSE)    **
**                                                                            **
** Parameters(in-out): Data   - Pointer to data which is to be modified       **
**                                                                            **
** Parameters (out)  : None                                                   **
**                                                                            **
** Return value      : void                                                   **
*******************************************************************************/
void Bfx_PutBit_u16u8u8(uint16* const Data,
                        const uint8 BitPn,
                        const boolean Status)
{
  /* [cover parentID={2007F92E-4970-4a16-92F6-0E36D1B0CEAE}]
  Is the status parameter passed to the API TRUE?
  [/cover] */
  if(Status == (boolean)TRUE)
  {
    /* [cover parentID={12AA32D7-3F01-4489-8C9B-1E0BC9721A30}]
    Set the bit at the specified position
    [/cover] */
    Bfx_lInsert16Bits(Data, BFX_DEFAULT_STATUS_1_SIXTEEN_BITS, \
                      BitPn, BFX_DEFAULT_WIDTH);
  }
  else
  {
    /* [cover parentID={D7C87E0F-8844-447f-90DC-0C8F68715BBF}]
    Clear the bit at the specified position
    [/cover] */
    Bfx_lInsert16Bits(Data, BFX_DEFAULT_STATUS_0_SIXTEEN_BITS, \
                      BitPn, BFX_DEFAULT_WIDTH);
  }
}

/*******************************************************************************
** Traceability      : [cover parentID={2CF113E0-38FF-4489-BBE2-F01FABF4DD87},**
**                                     {826C08F0-0107-42bf-9DCC-FABBFE7F9A19},**
**                                     {762A4383-158A-4763-B14B-1CA408E2D54E}]**
**                                                                            **
** Syntax            : void Bfx_PutBit_u32u8u8                                **
**                     (                                                      **
**                       uint32* const Data,                                  **
**                       const uint8 BitPn,                                   **
**                       const boolean Status                                 **
**                     )                                                      **
**                                                                            **
** Description       : The Bfx_PutBit_u32u8u8 function updates the logical    **
**                     status of the bit at BitPn bit position of the Data    **
**                     parameter to 1 when the value of Status parameter is   **
**                     TRUE, otherwise the function updates the logical status**
**                     of the bit at BitPn bit position of the Data parameter **
**                     to 0.                                                  **
**                                                                            **
** [/cover]                                                                   **
**                                                                            **
** Service ID        : 0x87                                                   **
**                                                                            **
** Sync/Async        : Synchronous                                            **
**                                                                            **
** Reentrancy        : Reentrant for pointer to distinct memory location      **
**                     passed as parameter to the API                         **
**                                                                            **
** Parameters (in)   : BitPn  - Bit position (Valid range: 0 to 31)           **
**                     Status - Status value (Valid values: TRUE or FALSE)    **
**                                                                            **
** Parameters(in-out): Data   - Pointer to data which is to be modified       **
**                                                                            **
** Parameters (out)  : None                                                   **
**                                                                            **
** Return value      : void                                                   **
*******************************************************************************/
void Bfx_PutBit_u32u8u8(uint32* const Data,
                        const uint8 BitPn,
                        const boolean Status)
{
  /* [cover parentID={FEF813FC-1C87-45e7-BE46-6278CE1EB176}]
  Is the status parameter passed to the API TRUE?
  [/cover] */
  if(Status == (boolean)TRUE)
  {
    /* [cover parentID={2946F86B-7564-4e9f-9FEF-0A2664130E29}]
    Set the bit at the specified position
    [/cover] */
    Bfx_lInsert32Bits(Data, BFX_DEFAULT_STATUS_1_THIRTYTWO_BITS, \
                      BitPn, BFX_DEFAULT_WIDTH);
  }
  else
  {
    /* [cover parentID={EB0C38DF-8FBA-43a3-AAD6-F806DC6FEC91}]
    Clear the bit at the specified position
    [/cover] */
    Bfx_lInsert32Bits(Data, BFX_DEFAULT_STATUS_0_THIRTYTWO_BITS, \
                      BitPn, BFX_DEFAULT_WIDTH);
  }
}

/*******************************************************************************
** Traceability      : [cover parentID={07EEBE08-34BB-4df3-A5F3-B41147724599},**
**                                     {826C08F0-0107-42bf-9DCC-FABBFE7F9A19},**
**                                     {762A4383-158A-4763-B14B-1CA408E2D54E}]**
**                                                                            **
** Syntax            : void Bfx_GetVersionInfo                                **
**                     (                                                      **
**                       Std_VersionInfoType* const Versioninfo               **
**                     )                                                      **
**                                                                            **
** Description       : The Bfx_GetVersionInfo returns the version information **
**                     of BFX library.                                        **
**                                                                            **
** [/cover]                                                                   **
**                                                                            **
** Service ID        : 0xff                                                   **
**                                                                            **
** Sync/Async        : Synchronous                                            **
**                                                                            **
** Reentrancy        : Reentrant                                              **
**                                                                            **
** Parameters (in)   : None                                                   **
**                                                                            **
** Parameters(in-out): None                                                   **
**                                                                            **
** Parameters (out)  : Versioninfo - Pointer to where to store the version    **
**                     information of this module                             **
**                                                                            **
** Return value      : void                                                   **
*******************************************************************************/
/*[cover parentID={0AF316CA-64BD-421b-8F2F-F3966F42F073}]
Imported SW Interfaces
Std_VersionInfoType is imported
[/cover] */
void Bfx_GetVersionInfo(Std_VersionInfoType * const Versioninfo)
{
  ((Std_VersionInfoType*)(Versioninfo))->vendorID = BFX_VENDOR_ID;
  ((Std_VersionInfoType*)(Versioninfo))->moduleID = BFX_MODULE_ID;
  ((Std_VersionInfoType*)(Versioninfo))->sw_major_version =\
                                         (uint8)BFX_SW_MAJOR_VERSION;
  ((Std_VersionInfoType*)(Versioninfo))->sw_minor_version =\
                                         (uint8)BFX_SW_MINOR_VERSION;
  ((Std_VersionInfoType*)(Versioninfo))->sw_patch_version =\
                                         (uint8)BFX_SW_PATCH_VERSION;
}/* end of Bfx_GetVersionInfo() */

/*******************************************************************************
**                            General Notes                                   **
*******************************************************************************/

/*******************************************************************************
**                            LOW Level Driver Functions                      **
*******************************************************************************/

/*******************************************************************************
**                            LOW Level Driver Functions                      **
*******************************************************************************/

/*[cover parentID={35C78994-9DC3-4b1c-96AF-706E29827EC8}]
Interrupt Control Registers not written
[/cover] */

/*[cover parentID={826C08F0-0107-42bf-9DCC-FABBFE7F9A19}]
Code Memory section executable by all cores
[/cover]*/
/* [cover parentID={EA0715EE-3E3C-4aac-A42E-4B5CFC96CEED}]
Memory mapping support
[/cover] */
/*[cover parentID={4579FE20-92DA-4848-93DB-7AD4FD35DD50}]
Code Memory section naming as per AS
[/cover]*/
#define BFX_STOP_SEC_CODE_ASIL_B_GLOBAL
/*MISRA2012_RULE_4_10_JUSTIFICATION: Memmap header is repeatedly included
without safegaurd. It complies to Autosar guidelines. */
/*MISRA2012_RULE_20_1_JUSTIFICATION: Memmap header usage as per Autosar
guideline. */
/*[cover parentID={6D3BA711-CAAB-4a34-82CC-822B613FCB90}]
MemMap_h file to be developed by user
[/cover]*/
#include "Bfx_MemMap.h"

/*[cover parentID={566ED99C-0D96-46ac-97BF-E97B04E2C700}]
Callout Memory section not used in BFX library
[/cover]*/
/*[cover parentID={E4047F9A-8865-4b2c-9D3C-385479854EAD}]
Configuration data Memory section not used in BFX library
[/cover]*/
/*[cover parentID={5713A17A-3FA1-427f-A0B6-89125A17689A}]
Constant data Memory section not used in BFX library
[/cover]*/
/*[cover parentID={72DABBEB-F27B-4677-B6B4-B53F634341BA}]
Variable data Memory section not used in BFX library
[/cover]*/

