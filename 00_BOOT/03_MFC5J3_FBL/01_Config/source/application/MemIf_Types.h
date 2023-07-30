/**
 * \file
 *
 * \brief AUTOSAR Demo
 *
 * This file contains the implementation of the AUTOSAR
 * module Demo.
 *
 * \author Elektrobit Automotive GmbH, 91058 Erlangen, Germany
 *
 * Copyright 2005 - 2019 Elektrobit Automotive GmbH
 * All rights exclusively reserved for Elektrobit Automotive GmbH,
 * unless expressly agreed to otherwise.
 */

#if (!defined MEMIF_TYPES_H)
#define MEMIF_TYPES_H

/*==[Includes]================================================================*/


#include <Std_Types.h>

/*==[Macros]==================================================================*/

/* MemIf_StatusType */
#define MEMIF_UNINIT 0x00U
#define MEMIF_IDLE 0x01U
#define MEMIF_BUSY 0x02U
//#define MEMIF_BUSY_INTERNAL 0x03U

/* MemIf_JobResultType */
#define MEMIF_JOB_OK 0x00U
#define MEMIF_JOB_PENDING 0x01U
#define MEMIF_JOB_FAILED 0x02U
#define MEMIF_JOB_CANCELED 0x03U
#define MEMIF_BLOCK_INCONSISTENT 0x04U
//#define MEMIF_BLOCK_INVALID 0x05U

/* MemIf_ModeType */
#define MEMIF_MODE_SLOW 0x00U
#define MEMIF_MODE_FAST 0x01U

/*==[Types]===================================================================*/

typedef uint8 MemIf_StatusType;

typedef uint8 MemIf_JobResultType;

typedef uint8 MemIf_ModeType;

/*==[Declaration of functions with external linkage]==========================*/

/*==[Constants with external linkage]=========================================*/

/*==[Variables with external linkage]=========================================*/

#endif /* !defined MEMIF_TYPES_H */
