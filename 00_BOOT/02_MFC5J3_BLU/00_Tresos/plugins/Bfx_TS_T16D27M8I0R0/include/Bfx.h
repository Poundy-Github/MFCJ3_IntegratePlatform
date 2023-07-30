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
**  FILENAME     : Bfx.h                                                      **
**                                                                            **
**  VERSION      : 6.0.0                                                      **
**                                                                            **
**  DATE         : 2019-06-19                                                 **
**  VARIANT      : Variant PC                                                 **
**                                                                            **
**  PLATFORM     : Infineon AURIX2G                                           **
**                                                                            **
**  AUTHOR       : DL-AUTOSAR-Engineering                                     **
**                                                                            **
**  VENDOR       : Infineon Technologies                                      **
**                                                                            **
**  TRACEABILITY : [cover parentID={AD206E98-A5A4-4617-AB6E-A1AA45B02DBE}]    **
**                                                                            **
**  DESCRIPTION  : BFX library header definition file                         **
**                                                                            **
**  [/cover]                                                                  **
**                                                                            **
**  SPECIFICATION(S) : Specification of BFX library, AUTOSAR Release 4.2.2    **
**                                                                            **
**  MAY BE CHANGED BY USER : no                                               **
**                                                                            **
*******************************************************************************/

#ifndef BFX_H
#define BFX_H


/*******************************************************************************
**                      Includes                                              **
*******************************************************************************/

/*[cover parentID={DC0B4213-1D31-4256-BAD3-DC0CD7F025C4}] 
File Structure
[/cover]*/

/*[cover parentID={43E56F75-50B4-4b3f-8C6C-13912D06E525}]*/
/*AUTOSAR data types are used instead of native C data types*/
#include "Std_Types.h"
/*[/cover] */

/* [cover parentID={2315CEFB-5155-410c-AA89-F72E519F9FBE}]
No configuration options. Hence no configuration file is included.
[/cover] */

/*******************************************************************************
**                      Global Macro Definitions                              **
*******************************************************************************/

/* [cover parentID={66B14F6E-1B0E-44fa-8823-83C3F63A2CCC}]
Published information 
[/cover] */

/* [cover parentID={54218CEC-C551-425b-B6CA-866ECF627E37}] */
/* Vendor ID and Module ID */
/* BFX Vendor ID - Vendor ID of the dedicated implementation of BFX
module according to the AUTOSAR vendor list */
#define BFX_VENDOR_ID                   (17U)

/*BFX Module ID - Module ID of BFX module from Module List */
#define BFX_MODULE_ID                   (205U)
/* [/cover] */

/* [cover parentID={C4D0F741-16CE-494c-B9FB-95C39C94BA13}] */
/* AUTOSAR version */
/* BFX AR Major Version - Major version number of AUTOSAR specification on
which the appropriate implementation of BFX module is based on */
#define BFX_AR_RELEASE_MAJOR_VERSION    (4U)
/* BFX AR Minor Version - Minor version number of AUTOSAR specification on
which the appropriate implementation of BFX module is based on */
#define BFX_AR_RELEASE_MINOR_VERSION    (2U)
/* BFX AR Patch Version - Patch level version number of AUTOSAR specification 
on which the appropriate implementation of BFX module is based on */
#define BFX_AR_RELEASE_REVISION_VERSION (2U)
/* [/cover] */

/* BFX SW Major Version - Major version number of the vendor specific
implementation of BFX module */
#define BFX_SW_MAJOR_VERSION            (10U)
/* BFX SW Minor Version - Minor version number of the vendor specific
implementation of BFX module */
#define BFX_SW_MINOR_VERSION            (30U)
/* BFX SW Patch Version - Patch level version number of the vendor specific
implementation of BFX module */
#define BFX_SW_PATCH_VERSION            (0U)

/* Holds maximum length of 8-bit data */
#define BFX_MAX_LENGTH_8BIT             ((uint8)8)
/* Holds maximum length of 16-bit data */
#define BFX_MAX_LENGTH_16BIT            ((uint8)16)
/* Holds maximum length of 32-bit data */
#define BFX_MAX_LENGTH_32BIT            ((uint8)32)


/*******************************************************************************
**                      Global Type Definitions                               **
*******************************************************************************/

/*******************************************************************************
**                      Global Constant Declarations                          **
*******************************************************************************/
/*******************************************************************************
**                      Global Variable Declarations                          **
*******************************************************************************/

/*[cover parentID={CC8A1B89-5F19-4485-96B6-CE3DD698F100}]
The BFX library is implemented as ASIL B module.There is no ASIL decomposition 
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
/*[cover parentID={6D3BA711-CAAB-4a34-82CC-822B613FCB90}]
MemMap_h file to be developed by user 
[/cover]*/
#include "Bfx_MemMap.h"

/*******************************************************************************
**                      Global Function Declarations                          **
*******************************************************************************/
/*******************************************************************************
** Traceability      : [cover parentID  ]                                     **
**                                                                            **
** Syntax            : void Bfx_SetBit_u8u8                                   **
**                     (                                                      **
**                       uint8 * const Data,                                  **
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
extern void Bfx_SetBit_u8u8(uint8 * const Data, const uint8 BitPn);

/*******************************************************************************
** Traceability      : [cover parentID  ]                                     **
**                                                                            **
** Syntax            : void Bfx_SetBit_u16u8                                  **
**                     (                                                      **
**                       uint16 * const Data,                                 **
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
extern void Bfx_SetBit_u16u8(uint16* const Data, const uint8 BitPn);

/*******************************************************************************
** Traceability      : [cover parentID  ]                                     **
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
extern void Bfx_SetBit_u32u8(uint32* const Data, const uint8 BitPn);

/*******************************************************************************
** Traceability      : [cover parentID ]                                      **
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
extern void Bfx_ClrBit_u8u8(uint8* const Data, const uint8 BitPn);

/*******************************************************************************
** Traceability      : [cover parentID ]                                      **
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
extern void Bfx_ClrBit_u16u8(uint16* const Data, const uint8 BitPn);

/*******************************************************************************
** Traceability      : [cover parentID ]                                      **
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
extern void Bfx_ClrBit_u32u8(uint32* const Data, const uint8 BitPn);

/*******************************************************************************
** Traceability      : [cover parentID ]                                      **
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
extern boolean Bfx_GetBit_u8u8_u8( const uint8 Data, const uint8 BitPn);

/*******************************************************************************
** Traceability      : [cover parentID ]                                      **
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
extern boolean Bfx_GetBit_u16u8_u8( const uint16 Data, const uint8 BitPn);

/*******************************************************************************
** Traceability      : [cover parentID ]                                      **
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
extern boolean Bfx_GetBit_u32u8_u8( const uint32 Data, const uint8 BitPn);

/*******************************************************************************
** Traceability      : [cover parentID  ]                                     **
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
extern void Bfx_SetBits_u8u8u8u8(uint8* const Data,
                                 const uint8 BitStartPn,
                                 const uint8 BitLn,
                                 const uint8 Status);

/*******************************************************************************
** Traceability      : [cover parentID  ]                                     **
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
extern void Bfx_SetBits_u16u8u8u8(uint16* const Data,
                                  const uint8 BitStartPn,
                                  const uint8 BitLn,
                                  const uint8 Status);

/*******************************************************************************
** Traceability      : [cover parentID  ]                                     **
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
extern void Bfx_SetBits_u32u8u8u8(uint32* const Data,
                                  const uint8 BitStartPn,
                                  const uint8 BitLn,
                                  const uint8 Status);

/*******************************************************************************
** Traceability      : [cover parentID ]                                      **
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
extern uint8 Bfx_GetBits_u8u8u8_u8(const uint8 Data,
                                   const uint8 BitStartPn,
                                   const uint8 BitLn);

/*******************************************************************************
** Traceability      : [cover parentID ]                                      **
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
extern uint16 Bfx_GetBits_u16u8u8_u16(const uint16 Data,
                                      const uint8 BitStartPn,
                                      const uint8 BitLn);

/*******************************************************************************
** Traceability      : [cover parentID ]                                      **
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
extern uint32 Bfx_GetBits_u32u8u8_u32(const uint32 Data,
                                      const uint8 BitStartPn,
                                      const uint8 BitLn);

/*******************************************************************************
** Traceability      : [cover parentID  ]                                     **
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
extern boolean Bfx_TstBitMask_u8u8_u8(const uint8 Data, const uint8 Mask);

/*******************************************************************************
** Traceability      : [cover parentID  ]                                     **
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
extern boolean Bfx_TstBitMask_u16u16_u8(const uint16 Data, const uint16 Mask);

/*******************************************************************************
** Traceability      : [cover parentID  ]                                     **
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
extern boolean Bfx_TstBitMask_u32u32_u8(const uint32 Data, const uint32 Mask);

/*******************************************************************************
** Traceability      : [cover parentID  ]                                     **
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
extern boolean Bfx_TstBitLnMask_u8u8_u8(const uint8 Data, const uint8 Mask);

/*******************************************************************************
** Traceability      : [cover parentID  ]                                     **
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
extern boolean Bfx_TstBitLnMask_u16u16_u8(const uint16 Data, const uint16 Mask);

/*******************************************************************************
** Traceability      : [cover parentID  ]                                     **
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
extern boolean Bfx_TstBitLnMask_u32u32_u8(const uint32 Data, const uint32 Mask);

/*******************************************************************************
** Traceability      : [cover parentID  ]                                     **
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
extern boolean Bfx_TstParityEven_u8_u8(const uint8 Data);

/*******************************************************************************
** Traceability      : [cover parentID  ]                                     **
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
extern boolean Bfx_TstParityEven_u16_u8(const uint16 Data);

/*******************************************************************************
** Traceability      : [cover parentID  ]                                     **
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
extern boolean Bfx_TstParityEven_u32_u8(const uint32 Data);

/*******************************************************************************
** Traceability      : [cover parentID  ]                                     **
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
extern void Bfx_CopyBit_u8u8u8u8(uint8* const DestinationData,
                                 const uint8 DestinationPosition,
                                 const uint8 SourceData,
                                 const uint8 SourcePosition);

/*******************************************************************************
** Traceability      : [cover parentID  ]                                     **
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
extern void Bfx_CopyBit_u16u8u16u8(uint16* const DestinationData,
                                   const uint8 DestinationPosition,
                                   const uint16 SourceData,
                                   const uint8 SourcePosition);

/*******************************************************************************
** Traceability      : [cover parentID  ]                                     **
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
extern void Bfx_CopyBit_u32u8u32u8(uint32* const DestinationData,
                                   const uint8 DestinationPosition,
                                   const uint32 SourceData,
                                   const uint8 SourcePosition);

/*******************************************************************************
** Traceability      : [cover parentID  ]                                     **
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
extern void Bfx_PutBits_u8u8u8u8(uint8* const Data,
                                 const uint8 BitStartPn,
                                 const uint8 BitLn,
                                 const uint8 Pattern);

/*******************************************************************************
** Traceability      : [cover parentID  ]                                     **
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
extern void Bfx_PutBits_u16u8u8u16(uint16* const Data,
                                   const uint8 BitStartPn,
                                   const uint8 BitLn,
                                   const uint16 Pattern);

/*******************************************************************************
** Traceability      : [cover parentID  ]                                     **
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
extern void Bfx_PutBits_u32u8u8u32(uint32* const Data,
                                   const uint8 BitStartPn,
                                   const uint8 BitLn,
                                   const uint32 Pattern);

/*******************************************************************************
** Traceability      : [cover parentID  ]                                     **
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
extern void Bfx_PutBit_u8u8u8(uint8* const Data,
                              const uint8 BitPn,
                              const boolean Status);

/*******************************************************************************
** Traceability      : [cover parentID  ]                                     **
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
extern void Bfx_PutBit_u16u8u8(uint16* const Data,
                               const uint8 BitPn,
                               const boolean Status);

/*******************************************************************************
** Traceability      : [cover parentID  ]                                     **
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
extern void Bfx_PutBit_u32u8u8(uint32* const Data,
                               const uint8 BitPn,
                               const boolean Status);

/*******************************************************************************
** Traceability      : [cover parentID  ]                                     **
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
extern void Bfx_GetVersionInfo(Std_VersionInfoType * const Versioninfo);

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
#include "Bfx_MemMap.h"

/*******************************************************************************
**                    Global INLINE Function Definitions                      **
*******************************************************************************/

/*
Global INLINE functions are not defined under any Memory section here.
They will lie in Code Memory section of User Application wherever called.
Code Memory section naming shall be as per AS.
*/

/*******************************************************************************
** Traceability      : [cover parentID={6F9AA5AC-460A-4e75-8BA7-3058D802AF96},**
**                                     {826C08F0-0107-42bf-9DCC-FABBFE7F9A19},**
**                                     {762A4383-158A-4763-B14B-1CA408E2D54E}]**
**                                                                            **
** Syntax            : void Bfx_SetBitMask_u8u8                               **
**                     (                                                      **
**                       uint8* const Data,                                   **
**                       const uint8 Mask                                     **
**                     )                                                      **
**                                                                            **
** Description       : The Bfx_SetBitMask_u32u32 function sets the logical    **
**                     status of the bits of the Data parameter to 1, for all **
**                     the bit positions for which the logical status of bit  **
**                     in the Mask parameter is set to 1. The remaining bits  **
**                     of the Data parameter will retain their original       **
**                     values.                                                **
**                                                                            **
** [/cover]                                                                   **
**                                                                            **
** Service ID        : 0x2a                                                   **
**                                                                            **
** Sync/Async        : Synchronous                                            **
**                                                                            **
** Reentrancy        : Reentrant for pointer to distinct memory location      **
**                     passed as parameter to the API                         **
**                                                                            **
** Parameters (in)   : Mask - Mask value                                      **
**                                                                            **
** Parameters(in-out): Data - Pointer to data which is to be modified         **
**                                                                            **
** Parameters (out)  : None                                                   **
**                                                                            **
** Return value      : void                                                   **
*******************************************************************************/
static INLINE void Bfx_SetBitMask_u8u8(uint8* const Data, const uint8 Mask)
{
  /*Data is equal to Bitwise OR of Data and Mask.*/
  *Data |= Mask;
}

/*******************************************************************************
** Traceability      : [cover parentID={0913DED7-D25F-45b8-BBF8-21C22DB8B56C},**
**                                     {826C08F0-0107-42bf-9DCC-FABBFE7F9A19},**
**                                     {762A4383-158A-4763-B14B-1CA408E2D54E}]**
**                                                                            **
** Syntax            : void Bfx_SetBitMask_u16u16                             **
**                     (                                                      **
**                       uint16* const Data,                                  **
**                       const uint16 Mask                                    **
**                     )                                                      **
**                                                                            **
** Description       : The Bfx_SetBitMask_u16u16 function sets the logical    **
**                     status of the bits of the Data parameter to 1, for all **
**                     the bit positions for which the logical status of bit  **
**                     in the Mask parameter is set to 1. The remaining bits  **
**                     of the Data parameter will retain their original       **
**                     values.                                                **
**                                                                            **
** [/cover]                                                                   **
**                                                                            **
** Service ID        : 0x2b                                                   **
**                                                                            **
** Sync/Async        : Synchronous                                            **
**                                                                            **
** Reentrancy        : Reentrant for pointer to distinct memory location      **
**                     passed as parameter to the API                         **
**                                                                            **
** Parameters (in)   : Mask - Mask value                                      **
**                                                                            **
** Parameters(in-out): Data - Pointer to data which is to be modified         **
**                                                                            **
** Parameters (out)  : None                                                   **
**                                                                            **
** Return value      : void                                                   **
*******************************************************************************/
static INLINE void Bfx_SetBitMask_u16u16(uint16* const Data, const uint16 Mask)
{
  /*Data is equal to Bitwise OR of Data and Mask.*/
  *Data |= Mask;
}

/*******************************************************************************
** Traceability      : [cover parentID={DF86A86A-A0FA-47f6-BF61-7755388E748E},**
**                                     {826C08F0-0107-42bf-9DCC-FABBFE7F9A19},**
**                                     {762A4383-158A-4763-B14B-1CA408E2D54E}]**
**                                                                            **
** Syntax            : void Bfx_SetBitMask_u32u32                             **
**                     (                                                      **
**                       uint32* const Data,                                  **
**                       const uint32 Mask                                    **
**                     )                                                      **
**                                                                            **
** Description       : The Bfx_SetBitMask_u32u32 function sets the logical    **
**                     status of the bits of the Data parameter to 1, for all **
**                     the bit positions for which the logical status of bit  **
**                     in the Mask parameter is set to 1. The remaining bits  **
**                     of the Data parameter will retain their original       **
**                     values.                                                **
**                                                                            **
** [/cover]                                                                   **
**                                                                            **
** Service ID        : 0x2c                                                   **
**                                                                            **
** Sync/Async        : Synchronous                                            **
**                                                                            **
** Reentrancy        : Reentrant for pointer to distinct memory location      **
**                     passed as parameter to the API                         **
**                                                                            **
** Parameters (in)   : Mask - Mask value                                      **
**                                                                            **
** Parameters(in-out): Data - Pointer to data which is to be modified         **
**                                                                            **
** Parameters (out)  : None                                                   **
**                                                                            **
** Return value      : void                                                   **
*******************************************************************************/
static INLINE void Bfx_SetBitMask_u32u32(uint32* const Data, const uint32 Mask)
{
  /*Data is equal to Bitwise OR of Data and Mask.*/
  *Data |= Mask;
}

/*******************************************************************************
** Traceability      : [cover parentID={AA757405-3C76-45fb-BED8-518D5C3940EE},**
**                                     {826C08F0-0107-42bf-9DCC-FABBFE7F9A19},**
**                                     {762A4383-158A-4763-B14B-1CA408E2D54E}]**
**                                                                            **
** Syntax            : void Bfx_ClrBitMask_u8u8                               **
**                     (                                                      **
**                       uint8* const Data,                                   **
**                       const uint8 Mask                                     **
**                      )                                                     **
**                                                                            **
** Description       : The Bfx_ClrBitMask_u8u8 function clears the logical    **
**                     status of the bits of the Data parameter to 0, for all **
**                     the bit positions for which the logical status of bit  **
**                     in the Mask parameter is set to 1. The remaining bits  **
**                     of Data parameter will retain their original values.   **
**                                                                            **
** [/cover]                                                                   **
**                                                                            **
**                                                                            **
** Service ID        : 0x30                                                   **
**                                                                            **
** Sync/Async        : Synchronous                                            **
**                                                                            **
** Reentrancy        : Reentrant for pointer to distinct memory location      **
**                     passed as parameter to the API                         **
**                                                                            **
** Parameters (in)   : Mask - Mask value                                      **
**                                                                            **
** Parameters(in-out): Data - Pointer to data which is to be modified         **
**                                                                            **
** Parameters (out)  : None                                                   **
**                                                                            **
** Return value      : void                                                   **
*******************************************************************************/
static INLINE void Bfx_ClrBitMask_u8u8(uint8* const Data, const uint8 Mask)
{
  /*Data is equal to Bitwise AND of Data and Bitwise complement of Mask.*/
  *Data &= (~Mask);
}

/*******************************************************************************
** Traceability      : [cover parentID={8987E8DE-825A-48cb-9C8E-CE06410A59DE},**
**                                     {826C08F0-0107-42bf-9DCC-FABBFE7F9A19},**
**                                     {762A4383-158A-4763-B14B-1CA408E2D54E}]**
**                                                                            **
** Syntax            : void Bfx_ClrBitMask_u16u16                             **
**                     (                                                      **
**                       uint16* const Data,                                  **
**                       const uint16 Mask                                    **
**                      )                                                     **
**                                                                            **
** Description       : The Bfx_ClrBitMask_u16u16 function clears the logical  **
**                     status of the bits of the Data parameter to 0, for all **
**                     the bit positions for which the logical status of bit  **
**                     in the Mask parameter is set to 1. The remaining bits  **
**                     of Data parameter will retain their original values.   **
**                                                                            **
** [/cover]                                                                   **
**                                                                            **
**                                                                            **
** Service ID        : 0x31                                                   **
**                                                                            **
** Sync/Async        : Synchronous                                            **
**                                                                            **
** Reentrancy        : Reentrant for pointer to distinct memory location      **
**                     passed as parameter to the API                         **
**                                                                            **
** Parameters (in)   : Mask - Mask value                                      **
**                                                                            **
** Parameters(in-out): Data - Pointer to data which is to be modified         **
**                                                                            **
** Parameters (out)  : None                                                   **
**                                                                            **
** Return value      : void                                                   **
*******************************************************************************/
static INLINE void Bfx_ClrBitMask_u16u16(uint16* const Data, const uint16 Mask)
{
  /*Data is equal to Bitwise AND of Data and Bitwise complement of Mask.*/
  *Data &= (~Mask);
}

/*******************************************************************************
** Traceability      : [cover parentID={F9881519-1A97-46b4-A7F4-5295AA870DBA},**
**                                     {826C08F0-0107-42bf-9DCC-FABBFE7F9A19},**
**                                     {762A4383-158A-4763-B14B-1CA408E2D54E}]**
**                                                                            **
** Syntax            : void Bfx_ClrBitMask_u32u32                             **
**                     (                                                      **
**                       uint32* const Data,                                  **
**                       const uint32 Mask                                    **
**                      )                                                     **
**                                                                            **
** Description       : The Bfx_ClrBitMask_u32u32 function clears the logical  **
**                     status of the bits of the Data parameter to 0, for all **
**                     the bit positions for which the logical status of bit  **
**                     in the Mask parameter is set to 1. The remaining bits  **
**                     of Data parameter will retain their original values.   **
**                                                                            **
** [/cover]                                                                   **
**                                                                            **
**                                                                            **
** Service ID        : 0x32                                                   **
**                                                                            **
** Sync/Async        : Synchronous                                            **
**                                                                            **
** Reentrancy        : Reentrant for pointer to distinct memory location      **
**                     passed as parameter to the API                         **
**                                                                            **
** Parameters (in)   : Mask - Mask value                                      **
**                                                                            **
** Parameters(in-out): Data - Pointer to data which is to be modified         **
**                                                                            **
** Parameters (out)  : None                                                   **
**                                                                            **
** Return value      : void                                                   **
*******************************************************************************/
static INLINE void Bfx_ClrBitMask_u32u32(uint32* const Data, const uint32 Mask)
{
  /*Data is equal to Bitwise AND of Data and Bitwise complement of Mask.*/
  *Data &= (~Mask);
}

/*******************************************************************************
** Traceability      : [cover parentID={8937B7D6-5D53-4dc7-B065-BC8A41F234BF},**
**                                     {826C08F0-0107-42bf-9DCC-FABBFE7F9A19},**
**                                     {762A4383-158A-4763-B14B-1CA408E2D54E}]**
**                                                                            **
** Syntax            : void Bfx_ToggleBits_u8                                 **
**                     (                                                      **
**                       uint8* const Data                                    **
**                     )                                                      **
**                                                                            **
** Description       : The Bfx_ToggleBits_u8 function toggles all the bits of **
**                     the Data parameter (1's complement of the Data         **
**                     parameter).                                            **
**                                                                            **
** [/cover]                                                                   **
**                                                                            **
** Service ID        : 0x46                                                   **
**                                                                            **
** Sync/Async        : Synchronous                                            **
**                                                                            **
** Reentrancy        : Reentrant for pointer to distinct memory location      **
**                     passed as parameter to the API                         **
**                                                                            **
** Parameters (in)   : None                                                   **
**                                                                            **
** Parameters(in-out): Data - Pointer to data which is to be modified         **
**                                                                            **
** Parameters (out)  : None                                                   **
**                                                                            **
** Return value      : void                                                   **
*******************************************************************************/
static INLINE void Bfx_ToggleBits_u8(uint8* const Data)
{
  /*Data is equal to Bitwise NOT of Data.*/
  *Data = ~(*Data);
}

/*******************************************************************************
** Traceability      : [cover parentID={7D126D21-984E-480a-A672-B986D557452E},**
**                                     {826C08F0-0107-42bf-9DCC-FABBFE7F9A19},**
**                                     {762A4383-158A-4763-B14B-1CA408E2D54E}]**
**                                                                            **
** Syntax            : void Bfx_ToggleBits_u16                                **
**                     (                                                      **
**                       uint16* const Data                                   **
**                     )                                                      **
**                                                                            **
** Description       : The Bfx_ToggleBits_u16 function toggles all the bits of**
**                     the Data parameter (1's complement of the Data         **
**                     parameter).                                            **
**                                                                            **
** [/cover]                                                                   **
**                                                                            **
** Service ID        : 0x47                                                   **
**                                                                            **
** Sync/Async        : Synchronous                                            **
**                                                                            **
** Reentrancy        : Reentrant for pointer to distinct memory location      **
**                     passed as parameter to the API                         **
**                                                                            **
** Parameters (in)   : None                                                   **
**                                                                            **
** Parameters(in-out): Data - Pointer to data which is to be modified         **
**                                                                            **
** Parameters (out)  : None                                                   **
**                                                                            **
** Return value      : void                                                   **
*******************************************************************************/
static INLINE void Bfx_ToggleBits_u16(uint16* const Data)
{
  /*Data is equal to Bitwise NOT of Data.*/
  *Data = ~(*Data);
}

/*******************************************************************************
** Traceability      : [cover parentID={A5F82090-2212-477e-A93B-451BA183251D},**
**                                     {826C08F0-0107-42bf-9DCC-FABBFE7F9A19},**
**                                     {762A4383-158A-4763-B14B-1CA408E2D54E}]**
**                                                                            **
** Syntax            : void Bfx_ToggleBits_u32                                **
**                     (                                                      **
**                       uint32* const Data                                   **
**                     )                                                      **
**                                                                            **
** Description       : The Bfx_ToggleBits_u32 function toggles all the bits of**
**                     the Data parameter (1's complement of the Data         **
**                     parameter).                                            **
**                                                                            **
** [/cover]                                                                   **
**                                                                            **
** Service ID        : 0x48                                                   **
**                                                                            **
** Sync/Async        : Synchronous                                            **
**                                                                            **
** Reentrancy        : Reentrant for pointer to distinct memory location      **
**                     passed as parameter to the API                         **
**                                                                            **
** Parameters (in)   : None                                                   **
**                                                                            **
** Parameters(in-out): Data - Pointer to data which is to be modified         **
**                                                                            **
** Parameters (out)  : None                                                   **
**                                                                            **
** Return value      : void                                                   **
*******************************************************************************/
static INLINE void Bfx_ToggleBits_u32(uint32* const Data)
{
  /*Data is equal to Bitwise NOT of Data.*/
  *Data = ~(*Data);
}

/*******************************************************************************
** Traceability      : [cover parentID={208AD1FB-083F-4fb6-B94F-E80C966B9313},**
**                                     {826C08F0-0107-42bf-9DCC-FABBFE7F9A19},**
**                                     {762A4383-158A-4763-B14B-1CA408E2D54E}]**
**                                                                            **
** Syntax            : void Bfx_ToggleBitMask_u8u8                            **
**                     (                                                      **
**                       uint32* const Data,                                  **
**                       const uint32 Mask                                    **
**                     )                                                      **
**                                                                            **
** Description       : The Bfx_ToggleBitMask_u32u32 function toggles the      **
**                     logical status of the bits of the Data parameter, for  **
**                     all the bit positions for which the logical status of  **
**                     bit in the Mask parameter is set to 1. The remaining   **
**                     bits of the Data parameter will retain their original  **
**                     values.                                                **
**                                                                            **
** [/cover]                                                                   **
**                                                                            **
** Service ID        : 0x4a                                                   **
**                                                                            **
** Sync/Async        : Synchronous                                            **
**                                                                            **
** Reentrancy        : Reentrant for pointer to distinct memory location      **
**                     passed as parameter to the API                         **
**                                                                            **
** Parameters (in)   : Mask - Mask value                                      **
**                                                                            **
** Parameters(in-out): Data - Pointer to data which is to be modified         **
**                                                                            **
** Parameters (out)  : None                                                   **
**                                                                            **
** Return value      : void                                                   **
*******************************************************************************/
static INLINE void Bfx_ToggleBitMask_u8u8(uint8* const Data,
                                          const uint8 Mask)
{
  /*Data is equal to Bitwise XOR of Data and Mask.*/
  /*XOR with 0 gives unchanged value*/
  /*XOR with 1 gives complement of the value*/
  *Data = (*Data) ^ (Mask);
}

/*******************************************************************************
** Traceability      : [cover parentID={195DE81E-E6F7-43d3-9BED-8DBD0B872B63},**
**                                     {826C08F0-0107-42bf-9DCC-FABBFE7F9A19},**
**                                     {762A4383-158A-4763-B14B-1CA408E2D54E}]**
**                                                                            **
** Syntax            : void Bfx_ToggleBitMask_u16u16                          **
**                     (                                                      **
**                       uint16* const Data,                                  **
**                       const uint16 Mask                                    **
**                     )                                                      **
**                                                                            **
** Description       : The Bfx_ToggleBitMask_u16u16 function toggles the      **
**                     logical status of the bits of the Data parameter, for  **
**                     all the bit positions for which the logical status of  **
**                     bit in the Mask parameter is set to 1. The remaining   **
**                     bits of the Data parameter will retain their original  **
**                     values.                                                **
**                                                                            **
** [/cover]                                                                   **
**                                                                            **
** Service ID        : 0x4b                                                   **
**                                                                            **
** Sync/Async        : Synchronous                                            **
**                                                                            **
** Reentrancy        : Reentrant for pointer to distinct memory location      **
**                     passed as parameter to the API                         **
**                                                                            **
** Parameters (in)   : Mask - Mask value                                      **
**                                                                            **
** Parameters(in-out): Data - Pointer to data which is to be modified         **
**                                                                            **
** Parameters (out)  : None                                                   **
**                                                                            **
** Return value      : void                                                   **
*******************************************************************************/
static INLINE void Bfx_ToggleBitMask_u16u16(uint16* const Data,
                                            const uint16 Mask)
{
  /*Data is equal to Bitwise XOR of Data and Mask.*/
  /*XOR with 0 gives unchanged value*/
  /*XOR with 1 gives complement of the value*/
  *Data = (*Data) ^ (Mask);
}


/*******************************************************************************
** Traceability      : [cover parentID={9A70B949-4D89-4d91-819E-CD517EEBC2B2},**
**                                     {826C08F0-0107-42bf-9DCC-FABBFE7F9A19},**
**                                     {762A4383-158A-4763-B14B-1CA408E2D54E}]**
**                                                                            **
** Syntax            : void Bfx_ToggleBitMask_u32u32                          **
**                     (                                                      **
**                       uint32* const Data,                                  **
**                       uint32 Mask                                          **
**                     )                                                      **
**                                                                            **
** Description       : The Bfx_ToggleBitMask_u32u32 function toggles the      **
**                     logical status of the bits of the Data parameter, for  **
**                     all the bit positions for which the logical status of  **
**                     bit in the Mask parameter is set to 1. The remaining   **
**                     bits of the Data parameter will retain their original  **
**                     values.                                                **
**                                                                            **
** [/cover]                                                                   **
**                                                                            **
** Service ID        : 0x4c                                                   **
**                                                                            **
** Sync/Async        : Synchronous                                            **
**                                                                            **
** Reentrancy        : Reentrant for pointer to distinct memory location      **
**                     passed as parameter to the API                         **
**                                                                            **
** Parameters (in)   : Mask - Mask value                                      **
**                                                                            **
** Parameters(in-out): Data - Pointer to data which is to be modified         **
**                                                                            **
** Parameters (out)  : None                                                   **
**                                                                            **
** Return value      : void                                                   **
*******************************************************************************/
static INLINE void Bfx_ToggleBitMask_u32u32(uint32* const Data,
                                            const uint32 Mask)
{
  /*Data is equal to Bitwise XOR of Data and Mask.*/
  /*XOR with 0 gives unchanged value*/
  /*XOR with 1 gives complement of the value*/
  *Data = (*Data) ^ (Mask);
}

/*******************************************************************************
** Traceability      : [cover parentID={308A7584-7C58-44eb-9A81-C79B18C02DF0},**
**                                     {826C08F0-0107-42bf-9DCC-FABBFE7F9A19},**
**                                     {762A4383-158A-4763-B14B-1CA408E2D54E}]**
**                                                                            **
** Syntax            : void Bfx_ShiftBitRt_u8u8                               **
**                     (                                                      **
**                       uint8* const Data,                                   **
**                       const uint8 ShiftCnt                                 **
**                     )                                                      **
**                                                                            **
** Description       : The Bfx_ShiftBitRt_u8u8 function shifts the bits of   **
**                     the Data parameter to the right by ShiftCnt count. The **
**                     most significant bit (left-most bit) is replaced by a 0**
**                     bit and the least significant bit (right-most bit) is  **
**                     discarded for every single bit shift cycle.            **
**                                                                            **
** [/cover]                                                                   **
**                                                                            **
** Service ID        : 0x50                                                   **
**                                                                            **
** Sync/Async        : Synchronous                                            **
**                                                                            **
** Reentrancy        : Reentrant for pointer to distinct memory location      **
**                     passed as parameter to the API                         **
**                                                                            **
** Parameters (in)   : ShiftCnt - Shift right count (Valid range: 0 to 7)     **
**                                                                            **
** Parameters(in-out): Data     - Pointer to data which is to be modified     **
**                                                                            **
** Parameters (out)  : None                                                   **
**                                                                            **
** Return value      : void                                                   **
*******************************************************************************/
static INLINE void Bfx_ShiftBitRt_u8u8(uint8* const Data,
                                       const uint8 ShiftCnt)
{
  /*Data Right Shifted by ShiftCnt number of times*/
  *Data = (uint8)(*Data >> ShiftCnt);
}

/*******************************************************************************
** Traceability      : [cover parentID={901BD331-E511-4f38-B1C6-AA9BC22F1DC2},**
**                                     {826C08F0-0107-42bf-9DCC-FABBFE7F9A19},**
**                                     {762A4383-158A-4763-B14B-1CA408E2D54E}]**
**                                                                            **
** Syntax            : void Bfx_ShiftBitRt_u16u8                              **
**                     (                                                      **
**                       uint16* const Data,                                  **
**                       const uint8 ShiftCnt                                 **
**                     )                                                      **
**                                                                            **
** Description       : The Bfx_ShiftBitRt_u16u8 function shifts the bits of   **
**                     the Data parameter to the right by ShiftCnt count. The **
**                     most significant bit (left-most bit) is replaced by a 0**
**                     bit and the least significant bit (right-most bit) is  **
**                     discarded for every single bit shift cycle.            **
**                                                                            **
** [/cover]                                                                   **
**                                                                            **
** Service ID        : 0x51                                                   **
**                                                                            **
** Sync/Async        : Synchronous                                            **
**                                                                            **
** Reentrancy        : Reentrant for pointer to distinct memory location      **
**                     passed as parameter to the API                         **
**                                                                            **
** Parameters (in)   : ShiftCnt - Shift right count (Valid range: 0 to 15)    **
**                                                                            **
** Parameters(in-out): Data     - Pointer to data which is to be modified     **
**                                                                            **
** Parameters (out)  : None                                                   **
**                                                                            **
** Return value      : void                                                   **
*******************************************************************************/
static INLINE void Bfx_ShiftBitRt_u16u8(uint16* const Data,
                                        const uint8 ShiftCnt)
{
  /*Data Right Shifted by ShiftCnt number of times*/
  *Data = (uint16)(*Data >> ShiftCnt);
}

/*******************************************************************************
** Traceability      : [cover parentID={368FDF87-541F-4604-BD29-2539D2D19F6B},**
**                                     {826C08F0-0107-42bf-9DCC-FABBFE7F9A19},**
**                                     {762A4383-158A-4763-B14B-1CA408E2D54E}]**
**                                                                            **
** Syntax            : void Bfx_ShiftBitRt_u32u8                              **
**                     (                                                      **
**                       uint32* const Data,                                  **
**                       const uint8 ShiftCnt                                 **
**                     )                                                      **
**                                                                            **
** Description       : The Bfx_ShiftBitRt_u32u8 function shifts the bits of   **
**                     the Data parameter to the right by ShiftCnt count. The **
**                     most significant bit (left-most bit) is replaced by a 0**
**                     bit and the least significant bit (right-most bit) is  **
**                     discarded for every single bit shift cycle.            **
**                                                                            **
** [/cover]                                                                   **
**                                                                            **
** Service ID        : 0x52                                                   **
**                                                                            **
** Sync/Async        : Synchronous                                            **
**                                                                            **
** Reentrancy        : Reentrant for pointer to distinct memory location      **
**                     passed as parameter to the API                         **
**                                                                            **
** Parameters (in)   : ShiftCnt - Shift right count (Valid range: 0 to 31)    **
**                                                                            **
** Parameters(in-out): Data     - Pointer to data which is to be modified     **
**                                                                            **
** Parameters (out)  : None                                                   **
**                                                                            **
** Return value      : void                                                   **
*******************************************************************************/
static INLINE void Bfx_ShiftBitRt_u32u8(uint32* const Data,
                                        const uint8 ShiftCnt)
{
  /*Data Right Shifted by ShiftCnt number of times*/
  *Data = (uint32)(*Data >> ShiftCnt);
}

/*******************************************************************************
** Traceability      : [cover parentID={0B7C8575-F856-420f-AFF6-B12B16FDDE87},**
**                                     {826C08F0-0107-42bf-9DCC-FABBFE7F9A19},**
**                                     {762A4383-158A-4763-B14B-1CA408E2D54E}]**
**                                                                            **
** Syntax            : void Bfx_ShiftBitLt_u8u8                               **
**                     (                                                      **
**                       uint8* const Data,                                   **
**                       const uint8 ShiftCnt                                 **
**                     )                                                      **
**                                                                            **
** Description       : The Bfx_ShiftBitLt_u8u8 function shifts the bits of    **
**                     the Data parameter to the left by ShiftCnt count. The  **
**                     least significant bit (right-most bit) is replaced by a**
**                     0 bit and the most significant bit (left-most bit) is  **
**                     discarded for every single bit shift cycle.            **
**                                                                            **
** [/cover]                                                                   **
**                                                                            **
** Service ID        : 0x56                                                   **
**                                                                            **
** Sync/Async        : Synchronous                                            **
**                                                                            **
** Reentrancy        : Reentrant for pointer to distinct memory location      **
**                     passed as parameter to the API                         **
**                                                                            **
** Parameters (in)   : ShiftCnt - Shift left count (Valid range: 0 to 7)      **
**                                                                            **
** Parameters(in-out): Data     - Pointer to data which is to be modified     **
**                                                                            **
** Parameters (out)  : None                                                   **
**                                                                            **
** Return value      : void                                                   **
*******************************************************************************/
static INLINE void Bfx_ShiftBitLt_u8u8(uint8* const Data,
                                       const uint8 ShiftCnt)
{
  /*Data Left Shifted by ShiftCnt number of times*/
  *Data = (uint8)(((uint32)(*Data)) << ShiftCnt);
}

/*******************************************************************************
** Traceability      : [cover parentID={736588AF-9605-4f3f-ABF0-B42841715F34},**
**                                     {826C08F0-0107-42bf-9DCC-FABBFE7F9A19},**
**                                     {762A4383-158A-4763-B14B-1CA408E2D54E}]**
**                                                                            **
** Syntax            : void Bfx_ShiftBitLt_u16u8                              **
**                     (                                                      **
**                       uint16* const Data,                                  **
**                       const uint8 ShiftCnt                                 **
**                     )                                                      **
**                                                                            **
** Description       : The Bfx_ShiftBitLt_u16u8 function shifts the bits of   **
**                     the Data parameter to the left by ShiftCnt count. The  **
**                     least significant bit (right-most bit) is replaced by a**
**                     0 bit and the most significant bit (left-most bit) is  **
**                     discarded for every single bit shift cycle.            **
**                                                                            **
** [/cover]                                                                   **
**                                                                            **
** Service ID        : 0x57                                                   **
**                                                                            **
** Sync/Async        : Synchronous                                            **
**                                                                            **
** Reentrancy        : Reentrant for pointer to distinct memory location      **
**                     passed as parameter to the API                         **
**                                                                            **
** Parameters (in)   : ShiftCnt - Shift left count (Valid range: 0 to 15)     **
**                                                                            **
** Parameters(in-out): Data     - Pointer to data which is to be modified     **
**                                                                            **
** Parameters (out)  : None                                                   **
**                                                                            **
** Return value      : void                                                   **
*******************************************************************************/
static INLINE void Bfx_ShiftBitLt_u16u8(uint16* const Data,
                                        const uint8 ShiftCnt)
{
  /*Data Left Shifted by ShiftCnt number of times*/
  *Data = (uint16)(((uint32) * Data) << ShiftCnt);
}


/*******************************************************************************
** Traceability      : [cover parentID={B6EAE094-DFFC-4671-8C5D-8B984A16D19A},**
**                                     {826C08F0-0107-42bf-9DCC-FABBFE7F9A19},**
**                                     {762A4383-158A-4763-B14B-1CA408E2D54E}]**
**                                                                            **
** Syntax            : void Bfx_ShiftBitLt_u32u8                              **
**                     (                                                      **
**                       uint32* const Data,                                  **
**                       const uint8 ShiftCnt                                 **
**                     )                                                      **
**                                                                            **
** Description       : The Bfx_ShiftBitLt_u32u8 function shifts the bits of   **
**                     the Data parameter to the left by ShiftCnt count. The  **
**                     least significant bit (right-most bit) is replaced by a**
**                     0 bit and the most significant bit (left-most bit) is  **
**                     discarded for every single bit shift cycle.            **
**                                                                            **
** [/cover]                                                                   **
**                                                                            **
** Service ID        : 0x58                                                   **
**                                                                            **
** Sync/Async        : Synchronous                                            **
**                                                                            **
** Reentrancy        : Reentrant for pointer to distinct memory location      **
**                     passed as parameter to the API                         **
**                                                                            **
** Parameters (in)   : ShiftCnt - Shift left count (Valid range: 0 to 31)     **
**                                                                            **
** Parameters(in-out): Data     - Pointer to data which is to be modified     **
**                                                                            **
** Parameters (out)  : None                                                   **
**                                                                            **
** Return value      : void                                                   **
*******************************************************************************/
static INLINE void Bfx_ShiftBitLt_u32u8(uint32* const Data,
                                        const uint8 ShiftCnt)
{
  /*Data Left Shifted by ShiftCnt number of times*/
  *Data = *Data << ShiftCnt;
}

/*******************************************************************************
** Traceability      : [cover parentID={387FE8EC-FBAE-49cc-B50F-7546ADFB4453},**
**                                     {826C08F0-0107-42bf-9DCC-FABBFE7F9A19},**
**                                     {762A4383-158A-4763-B14B-1CA408E2D54E}]**
**                                                                            **
** Syntax            : void Bfx_RotBitRt_u8u8                                 **
**                     (                                                      **
**                       uint8* const Data,                                   **
**                       const uint8 ShiftCnt                                 **
**                     )                                                      **
**                                                                            **
** Description       : The Bfx_RotBitRt_u8u8 function rotates the bits of the **
**                     Data parameter to the right by ShiftCnt count. The     **
**                     least significant bit (right-most bit) is rotated to   **
**                     the most significant bit (left-most bit) location for  **
**                     every single bit shift cycle.                          **
**                                                                            **
** [/cover]                                                                   **
**                                                                            **
** Service ID        : 0x5a                                                   **
**                                                                            **
** Sync/Async        : Synchronous                                            **
**                                                                            **
** Reentrancy        : Reentrant for pointer to distinct memory location      **
**                     passed as parameter to the API                         **
**                                                                            **
** Parameters (in)   : ShiftCnt - Shift count (Valid range: 0 to 7)           **
**                                                                            **
** Parameters(in-out): Data     - Pointer to data which is to be modified     **
**                                                                            **
** Parameters (out)  : None                                                   **
**                                                                            **
** Return value      : void                                                   **
*******************************************************************************/
static INLINE void Bfx_RotBitRt_u8u8(uint8* const Data, const uint8 ShiftCnt)
{
  /*  Data is equal to addition of
      1)  Data Right Shifted by ShiftCnt number of times and
      2)  Data Left Shifted by ((Max Length or (Max Position +1))-ShiftCnt)
        number of times.
  */
  *Data = (uint8)(*Data >> ShiftCnt) +
          (uint8)((((uint32)(*Data)) <<
          ((uint8)(BFX_MAX_LENGTH_8BIT - ShiftCnt))));
}

/*******************************************************************************
** Traceability      : [cover parentID={C4C0C241-9623-4783-8A76-29186EF9430A},**
**                                     {826C08F0-0107-42bf-9DCC-FABBFE7F9A19},**
**                                     {762A4383-158A-4763-B14B-1CA408E2D54E}]**
**                                                                            **
** Syntax            : void Bfx_RotBitRt_u16u8                                **
**                     (                                                      **
**                       uint16* const Data,                                  **
**                       const uint8 ShiftCnt                                 **
**                     )                                                      **
**                                                                            **
** Description       : The Bfx_RotBitRt_u16u8 function rotates the bits of the**
**                     Data parameter to the right by ShiftCnt count. The     **
**                     least significant bit (right-most bit) is rotated to   **
**                     the most significant bit (left-most bit) location for  **
**                     every single bit shift cycle.                          **
**                                                                            **
** [/cover]                                                                   **
**                                                                            **
** Service ID        : 0x5b                                                   **
**                                                                            **
** Sync/Async        : Synchronous                                            **
**                                                                            **
** Reentrancy        : Reentrant for pointer to distinct memory location      **
**                     passed as parameter to the API                         **
**                                                                            **
** Parameters (in)   : ShiftCnt - Shift count (Valid range: 0 to 15)          **
**                                                                            **
** Parameters(in-out): Data     - Pointer to data which is to be modified     **
**                                                                            **
** Parameters (out)  : None                                                   **
**                                                                            **
** Return value      : void                                                   **
*******************************************************************************/
static INLINE void Bfx_RotBitRt_u16u8(uint16* const Data, const uint8 ShiftCnt)
{
  /*  Data is equal to addition of
      1)  Data Right Shifted by ShiftCnt number of times and
      2)  Data Left Shifted by ((Max Length or (Max Position +1))-ShiftCnt)
        number of times.
  */
  *Data = (uint16)(*Data >> ShiftCnt) +
          (uint16)(((uint32) * Data) << (uint8)(BFX_MAX_LENGTH_16BIT - ShiftCnt));
}

/*******************************************************************************
** Traceability      : [cover parentID={59403A4F-D8BE-4be8-A2B2-FDAE1EF0067E},**
**                                     {826C08F0-0107-42bf-9DCC-FABBFE7F9A19},**
**                                     {762A4383-158A-4763-B14B-1CA408E2D54E}]**
**                                                                            **
** Syntax            : void Bfx_RotBitRt_u32u8                                **
**                     (                                                      **
**                       uint32* const Data,                                  **
**                       const uint8 ShiftCnt                                 **
**                     )                                                      **
**                                                                            **
** Description       : The Bfx_RotBitRt_u32u8 function rotates the bits of the**
**                     Data parameter to the right by ShiftCnt count. The     **
**                     least significant bit (right-most bit) is rotated to   **
**                     the most significant bit (left-most bit) location for  **
**                     every single bit shift cycle.                          **
**                                                                            **
** [/cover]                                                                   **
**                                                                            **
** Service ID        : 0x5c                                                   **
**                                                                            **
** Sync/Async        : Synchronous                                            **
**                                                                            **
** Reentrancy        : Reentrant for pointer to distinct memory location      **
**                     passed as parameter to the API                         **
**                                                                            **
** Parameters (in)   : ShiftCnt - Shift count (Valid range: 0 to 31)          **
**                                                                            **
** Parameters(in-out): Data     - Pointer to data which is to be modified     **
**                                                                            **
** Parameters (out)  : None                                                   **
**                                                                            **
** Return value      : void                                                   **
*******************************************************************************/
static INLINE void Bfx_RotBitRt_u32u8(uint32* const Data, const uint8 ShiftCnt)
{
  /*  Data is equal to addition of
      1)  Data Right Shifted by ShiftCnt number of times and
      2)  Data Left Shifted by ((Max Length or (Max Position +1))-ShiftCnt)
        number of times.
  */
  *Data = (*Data >> ShiftCnt) +
          (*Data << (uint8)(BFX_MAX_LENGTH_32BIT - ShiftCnt));
}

/*******************************************************************************
** Traceability      : [cover parentID={7453858F-E5CD-4335-B315-EDB428DBDF6E},**
**                                     {826C08F0-0107-42bf-9DCC-FABBFE7F9A19},**
**                                     {762A4383-158A-4763-B14B-1CA408E2D54E}]**
**                                                                            **
** Syntax            : void Bfx_RotBitLt_u8u8                                 **
**                     (                                                      **
**                       uint8* const Data,                                   **
**                       const uint8 ShiftCnt                                 **
**                     )                                                      **
**                                                                            **
** Description       : The Bfx_RotBitLt_u8u8 function rotates the bits of the **
**                     Data parameter to the left by ShiftCnt count. The      **
**                     most significant bit (left-most bit) is rotated to     **
**                     the least significant bit (right-most bit) location for**
**                     every single bit shift cycle.                          **
**                                                                            **
** [/cover]                                                                   **
**                                                                            **
** Service ID        : 0x60                                                   **
**                                                                            **
** Sync/Async        : Synchronous                                            **
**                                                                            **
** Reentrancy        : Reentrant for pointer to distinct memory location      **
**                     passed as parameter to the API                         **
**                                                                            **
** Parameters (in)   : ShiftCnt - Shift count (Valid range: 0 to 7)           **
**                                                                            **
** Parameters(in-out): Data     - Pointer to data which is to be modified     **
**                                                                            **
** Parameters (out)  : None                                                   **
**                                                                            **
** Return value      : void                                                   **
*******************************************************************************/
static INLINE void Bfx_RotBitLt_u8u8(uint8* const Data, const uint8 ShiftCnt)
{
  /*  Data is equal to addition of
      1)Data Left Shifted by ShiftCnt number of times and
      2)Data Right Shifted by (Max Length or (MaxPos+1))-ShiftCnt number of times.
  */
  *Data = (uint8)(((uint32) * Data) << ShiftCnt) +
          (uint8)(*Data >> (uint8)(BFX_MAX_LENGTH_8BIT - ShiftCnt));
}

/*******************************************************************************
** Traceability      : [cover parentID={E41BE5C3-5963-4b98-8C6D-6922239B0480},**
**                                     {826C08F0-0107-42bf-9DCC-FABBFE7F9A19},**
**                                     {762A4383-158A-4763-B14B-1CA408E2D54E}]**
**                                                                            **
** Syntax            : void Bfx_RotBitLt_u16u8                                **
**                     (                                                      **
**                       uint16* const Data,                                  **
**                       const uint8 ShiftCnt                                 **
**                     )                                                      **
**                                                                            **
** Description       : The Bfx_RotBitLt_u16u8 function rotates the bits of the**
**                     Data parameter to the left by ShiftCnt count. The      **
**                     most significant bit (left-most bit) is rotated to     **
**                     the least significant bit (right-most bit) location for**
**                     every single bit shift cycle.                          **
**                                                                            **
** [/cover]                                                                   **
**                                                                            **
** Service ID        : 0x61                                                   **
**                                                                            **
** Sync/Async        : Synchronous                                            **
**                                                                            **
** Reentrancy        : Reentrant for pointer to distinct memory location      **
**                     passed as parameter to the API                         **
**                                                                            **
** Parameters (in)   : ShiftCnt - Shift count (Valid range: 0 to 15)          **
**                                                                            **
** Parameters(in-out): Data     - Pointer to data which is to be modified     **
**                                                                            **
** Parameters (out)  : None                                                   **
**                                                                            **
** Return value      : void                                                   **
*******************************************************************************/
static INLINE void Bfx_RotBitLt_u16u8(uint16* const Data, const uint8 ShiftCnt)
{
  /*  Data is equal to addition of
      1)  Data Left Shifted by ShiftCnt number of times and
      2)  Data Right Shifted by (Max Length or (MaxPos+1))-ShiftCnt number of
          times.
  */
  *Data = (uint16)(((uint32) * Data) << ShiftCnt) +
          (uint16)(*Data >> (uint8)(BFX_MAX_LENGTH_16BIT - ShiftCnt));
}

/*******************************************************************************
** Traceability      : [cover parentID={3FB7D5F3-2908-40f4-BB63-414010081D5B},**
**                                     {826C08F0-0107-42bf-9DCC-FABBFE7F9A19},**
**                                     {762A4383-158A-4763-B14B-1CA408E2D54E}]**
**                                                                            **
** Syntax            : void Bfx_RotBitLt_u32u8                                **
**                     (                                                      **
**                       uint32* const Data,                                  **
**                       const uint8 ShiftCnt                                 **
**                     )                                                      **
**                                                                            **
** Description       : The Bfx_RotBitLt_u32u8 function rotates the bits of the**
**                     Data parameter to the left by ShiftCnt count. The      **
**                     most significant bit (left-most bit) is rotated to     **
**                     the least significant bit (right-most bit) location for**
**                     every single bit shift cycle.                          **
**                                                                            **
** [/cover]                                                                   **
**                                                                            **
** Service ID        : 0x62                                                   **
**                                                                            **
** Sync/Async        : Synchronous                                            **
**                                                                            **
** Reentrancy        : Reentrant for pointer to distinct memory location      **
**                     passed as parameter to the API                         **
**                                                                            **
** Parameters (in)   : ShiftCnt - Shift count (Valid range: 0 to 31)          **
**                                                                            **
** Parameters(in-out): Data     - Pointer to data which is to be modified     **
**                                                                            **
** Parameters (out)  : None                                                   **
**                                                                            **
** Return value      : void                                                   **
*******************************************************************************/
static INLINE void Bfx_RotBitLt_u32u8(uint32* const Data, const uint8 ShiftCnt)
{
  /*  Data is equal to addition of
      1)  Data Left Shifted by ShiftCnt number of times and
      2)  Data Right Shifted by (Max Length or (MaxPos+1))-ShiftCnt number of
        times.
  */
  *Data = (*Data << ShiftCnt) +
          (*Data >> (BFX_MAX_LENGTH_32BIT - ShiftCnt));
}

/*******************************************************************************
** Traceability      : [cover parentID={C89A45E8-BE7B-446e-82E3-9E48109C33B8},**
**                                     {826C08F0-0107-42bf-9DCC-FABBFE7F9A19},**
**                                     {762A4383-158A-4763-B14B-1CA408E2D54E}]**
**                                                                            **
** Syntax            : void Bfx_PutBitsMask_u8u8u8                            **
**                     (                                                      **
**                       uint8* const Data,                                   **
**                       const uint8 Pattern,                                 **
**                       const uint8 Mask                                     **
**                      )                                                     **
**                                                                            **
** Description       : The Bfx_PutBitsMask_u8u8u8 function copies the bit     **
**                     pattern from the Pattern parameter into the Data       **
**                     parameter, for all the bit positions for which the     **
**                     logical status of bit in the Mask parameter is set to 1**
**                     The remaining bits of the Data parameter retain their  **
**                     original values.                                       **
**                                                                            **
** [/cover]                                                                   **
**                                                                            **
**                                                                            **
**                                                                            **
** Service ID        : 0x80                                                   **
**                                                                            **
** Sync/Async        : Synchronous                                            **
**                                                                            **
** Reentrancy        : Reentrant for pointer to distinct memory location      **
**                     passed as parameter to the API                         **
**                                                                            **
** Parameters (in)   : Pattern - Bit pattern to be set                        **
**                     Mask    - Mask value                                   **
**                                                                            **
** Parameters(in-out): Data    - Pointer to destination data which is to be   **
**                               modified                                     **
**                                                                            **
** Parameters (out)  : None                                                   **
**                                                                            **
** Return value      : void                                                   **
*******************************************************************************/
static INLINE void Bfx_PutBitsMask_u8u8u8(uint8* const Data,
                                          const uint8 Pattern,
                                          const uint8 Mask)
{
  /*  Data is equal to Bitwise OR of
      1)  Bitwise AND of Data and complement of Mask and
      2)  Bitwise AND of Pattern and Mask.
  */
  *Data = (*Data & (uint8)(~Mask)) | (uint8)(Pattern & Mask);
}

/*******************************************************************************
** Traceability      : [cover parentID={C64BA5A6-2D83-4e88-BC3B-C438AF44C598},**
**                                     {826C08F0-0107-42bf-9DCC-FABBFE7F9A19},**
**                                     {762A4383-158A-4763-B14B-1CA408E2D54E}]**
**                                                                            **
** Syntax            : void Bfx_PutBitsMask_u16u16u16                         **
**                     (                                                      **
**                       uint16* const Data,                                  **
**                       const uint16 Pattern,                                **
**                       const uint16 Mask                                    **
**                      )                                                     **
**                                                                            **
** Description       : The Bfx_PutBitsMask_u16u16u16 function copies the bit  **
**                     pattern from the Pattern parameter into the Data       **
**                     parameter, for all the bit positions for which the     **
**                     logical status of bit in the Mask parameter is set to 1**
**                     The remaining bits of the Data parameter retain their  **
**                     original values.                                       **
**                                                                            **
** [/cover]                                                                   **
**                                                                            **
**                                                                            **
**                                                                            **
** Service ID        : 0x81                                                   **
**                                                                            **
** Sync/Async        : Synchronous                                            **
**                                                                            **
** Reentrancy        : Reentrant for pointer to distinct memory location      **
**                     passed as parameter to the API                         **
**                                                                            **
** Parameters (in)   : Pattern - Bit pattern to be set                        **
**                     Mask    - Mask value                                   **
**                                                                            **
** Parameters(in-out): Data    - Pointer to destination data which is to be   **
**                               modified                                     **
**                                                                            **
** Parameters (out)  : None                                                   **
**                                                                            **
** Return value      : void                                                   **
*******************************************************************************/
static INLINE void Bfx_PutBitsMask_u16u16u16(uint16* const Data,
                                             const uint16 Pattern,
                                             const uint16 Mask)
{
  /*  Data is equal to Bitwise OR of
      1)  Bitwise AND of Data and complement of Mask and
      2)  Bitwise AND of Pattern and Mask.
  */
  *Data = (*Data & (uint16)(~Mask)) | (uint16)(Pattern & Mask);
}

/*******************************************************************************
** Traceability      : [cover parentID={FAE92A6F-8944-4af4-B092-1D45BDFC4ED9},**
**                                     {826C08F0-0107-42bf-9DCC-FABBFE7F9A19},**
**                                     {762A4383-158A-4763-B14B-1CA408E2D54E}]**
**                                                                            **
** Syntax            : void Bfx_PutBitsMask_u32u32u32                         **
**                     (                                                      **
**                       uint32* const Data,                                  **
**                       const uint32 Pattern,                                **
**                       const uint32 Mask                                    **
**                      )                                                     **
**                                                                            **
** Description       : The Bfx_PutBitsMask_u32u32u32 function copies the bit  **
**                     pattern from the Pattern parameter into the Data       **
**                     parameter, for all the bit positions for which the     **
**                     logical status of bit in the Mask parameter is set to 1**
**                     The remaining bits of the Data parameter retain their  **
**                     original values.                                       **
**                                                                            **
** [/cover]                                                                   **
**                                                                            **
**                                                                            **
**                                                                            **
** Service ID        : 0x82                                                   **
**                                                                            **
** Sync/Async        : Synchronous                                            **
**                                                                            **
** Reentrancy        : Reentrant for pointer to distinct memory location      **
**                     passed as parameter to the API                         **
**                                                                            **
** Parameters (in)   : Pattern - Bit pattern to be set                        **
**                     Mask    - Mask value                                   **
**                                                                            **
** Parameters(in-out): Data    - Pointer to destination data which is to be   **
**                               modified                                     **
**                                                                            **
** Parameters (out)  : None                                                   **
**                                                                            **
** Return value      : void                                                   **
*******************************************************************************/
static INLINE void Bfx_PutBitsMask_u32u32u32(uint32* const Data,
                                             const uint32 Pattern,
                                             const uint32 Mask)
{
  /* Data is equal to Bitwise OR of
     1)  Bitwise AND of Data and complement of Mask and
     2)  Bitwise AND of Pattern and Mask.
  */
  *Data = (*Data & (~Mask)) | (Pattern & Mask);
}

/*******************************************************************************
**                            LOW Level Driver Definitions                    **
*******************************************************************************/

/*******************************************************************************
**                            LOW Level Driver Definitions                    **
*******************************************************************************/

#endif /* BFX_H */

