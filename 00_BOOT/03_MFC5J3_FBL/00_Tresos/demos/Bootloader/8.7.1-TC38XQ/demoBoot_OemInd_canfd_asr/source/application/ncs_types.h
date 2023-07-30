/*********************************************************************************/
/*                                                                               */
/*                                 N  C  S                                       */
/*                                                                               */
/* ----------------------------------------------------------------------------- */
/*                                                                               */
/*            Standard NCS C data type definition file (target independent)      */
/*                                                                               */
/*********************************************************************************/
/*%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%                                        */
/*%%   _____________________________   %%  \file ncs_sdf.h                       */
/*%%  |                             |  %%  \brief  SDF configuration             */
/*%%  |   &&&&&   &&&&&             |  %%  Module version: 1.04                  */
/*%%  |   &       &    &            |  %%                                        */
/*%%  |   &&&&    &&&&&             |  %%                                        */
/*%%  |   &       &    &            |  %%                                        */
/*%%  |   &&&&&   &&&&&             |  %%                                        */
/*%%  |_____________________________|  %%                                        */
/*%%                                   %%                                        */
/*%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%                                        */
/*********************************************************************************/
/* Copyright 2011 by Elektrobit Automotive GmbH                                  */
/* All rights exclusively reserved for Elektrobit Automotive GmbH,               */
/* unless expressly agreed to otherwise.                                         */
/*********************************************************************************/
/*********************************************************************************/
/* Version history:                                                              */
/* 1.01: add some missing DEFINE                                                 */
/* 1.02: remove unused unions responsible for MISRA warnings                     */
/* 1.03: remove u8 type from TRUE and FALSE define                               */
/* 1.04: Deviate MISRA rule 6.3 and 20.1                                         */
/*********************************************************************************/

/*  MISRA-C:2004 Deviation List
 *
 *  MISRA-1) Deviated Rule: 6.3 (advisory)
 *   "'typedefs' that indicate size and signedness should be used in place of the basic types."
 *
 *   Reason:
 *   Global type definition for all the stack layers.
 *   Basic type use is necessary.
 *
 *  MISRA-2) Deviated Rule: 20.1 (required)
 *   "Reserved identifiers, macros and functions in the standard library, shall not be defined, redefined or undefined."
 *
 *   Reason:
 *   NULL definition is required.
 *   This is only used if not already defined.
 */


#ifndef __NCS_TYPES_H__
#define __NCS_TYPES_H__

/* Include AUTOSAR Basic Types */
#include <Std_Types.h>


/****************************** PUBLIC DEFINITIONS *******************************/
/*                                                                               */
/*-------------------------------------------------------------------------------*/
/* - Public Constants                                                            */

/*-------------------------------------------------------------------------------*/
/* - Public Types                                                                */

/* EXACT type definition */
/* Deviation MISRA-1 */
typedef uint8                   u8;         /* Range : 0..255 */
/* Deviation MISRA-1 */
typedef uint16                  u16;        /* Range : 0..65535 */
/* Deviation MISRA-1 */
typedef uint32                  u32;        /* Range : 0..4294967295 */
/* Deviation MISRA-1 */
typedef signed char             s8;         /* Range : -128..127 */
/* Deviation MISRA-1 */
typedef signed short int        s16;        /* Range : -32768..32767 */
/* Deviation MISRA-1 */
typedef signed long int         s32;        /* Range : -2147483648..2147483647 */


/* AT LEAST type definition */
/* Deviation MISRA-1 */
typedef unsigned int            u8m;         /* Range : at least 0..255 */
/* Deviation MISRA-1 */
typedef unsigned int            u16m;        /* Range : at least 0..65535 */
/* Deviation MISRA-1 */
typedef unsigned long int       u32m;        /* Range : at least 0..4294967295 */
/* Deviation MISRA-1 */
typedef signed int              s8m;         /* Range : at least -128..127 */
/* Deviation MISRA-1 */
typedef signed int              s16m;        /* Range : at least -32768..32767 */
/* Deviation MISRA-1 */
typedef signed long int         s32m;        /* Range : at least -2147483648..2147483647 */


#ifdef NCS_UNITARY_TEST 
/* Const definition into CODE segment */
#define NCS_CONST_SEG
/* data definition into DATA segment */
#define NCS_DATA_SEG
#else
#define NCS_CONST_SEG   /* erasing of 'code' definition */
#define NCS_DATA_SEG    /* Erasing of 'data' definition */
#endif

#ifndef TRUE
    #define TRUE    (1U)
#endif

#ifndef FALSE
    #define FALSE   (0U)
#endif


/* NULL pointer definition if not already defined */
#ifndef NULL
    /* Deviation MISRA-2 */
    #define NULL   (0)
#endif

#endif      /* __NCS_TYPES_H__ */
/* End of file */

