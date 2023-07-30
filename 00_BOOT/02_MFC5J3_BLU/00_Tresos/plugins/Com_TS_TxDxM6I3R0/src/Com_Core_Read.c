/**
 * \file
 *
 * \brief AUTOSAR Com
 *
 * This file contains the implementation of the AUTOSAR
 * module Com.
 *
 * \author Elektrobit Automotive GmbH, 91058 Erlangen, Germany
 *
 * Copyright 2005 - 2019 Elektrobit Automotive GmbH
 * All rights exclusively reserved for Elektrobit Automotive GmbH,
 * unless expressly agreed to otherwise.
 */

/* MISRA-C:2012 Deviation List
 *
 * MISRAC2012-1) Deviated Rule: 10.8 (required)
 * The value of a composite expression shall not be
 * cast to a different essential type category.
 *
 * Reason:
 * The msb extraction is implemented through an
 * explicit type cast to a lower essential type
 * category. The truncation of the value is intended.
 *
 * MISRAC2012-2) Deviated Rule: 11.5 (advisory)
 * A conversion should not be performed from pointer to
 * void into pointer to object.
 *
 * Reason:
 * The memory routines are optimized for dealing with aligned
 * memory sections.
 *
 */

/*==================[inclusions]============================================*/

#include <TSAutosar.h>
#include <Com_Core_Read.h>
#include <Com_Cfg.h>
#include <TSMem.h>
#include <Com_Core_Read_hlp.h>

/*==================[macros]================================================*/

/*==================[type definitions]======================================*/

/*==================[external function declarations]========================*/

/*==================[internal function declarations]========================*/

#define COM_START_SEC_CODE
#include <Com_MemMap.h>

#if (COM_RX_LITTLEENDIAN_ENABLE == STD_ON)
static FUNC(void, COM_CODE) Com_EB_Read_08_DL_1
(
   P2VAR(void, AUTOMATIC, COM_APPL_DATA) SignalDataPtr,
   P2CONST(uint8, AUTOMATIC, COM_VAR_NOINIT) dataPtr,
   P2CONST(ComSignalBaseType, AUTOMATIC, AUTOMATIC) Com_EB_ReadPropPtr,
   P2VAR(uint8, AUTOMATIC, COM_APPL_DATA) retvalPtr
);
#else
#define Com_EB_Read_08_DL_1 Com_EB_Read_DET
#endif

#if (COM_RX_LITTLEENDIAN_ENABLE == STD_ON)
static FUNC(void, COM_CODE) Com_EB_Read_16_DL_1
(
      P2VAR(void, AUTOMATIC, COM_APPL_DATA) SignalDataPtr,
      P2CONST(uint8, AUTOMATIC, COM_VAR_NOINIT) dataPtr,
      P2CONST(ComSignalBaseType, AUTOMATIC, AUTOMATIC) Com_EB_ReadPropPtr,
      P2VAR(uint8, AUTOMATIC, COM_APPL_DATA) retvalPtr
);
#else
#define Com_EB_Read_16_DL_1 Com_EB_Read_DET
#endif

#if (COM_RX_LITTLEENDIAN_ENABLE == STD_ON)
static FUNC(void, COM_CODE) Com_EB_Read_32_DL_1
(
      P2VAR(void, AUTOMATIC, COM_APPL_DATA) SignalDataPtr,
      P2CONST(uint8, AUTOMATIC, COM_VAR_NOINIT) dataPtr,
      P2CONST(ComSignalBaseType, AUTOMATIC, AUTOMATIC) Com_EB_ReadPropPtr,
      P2VAR(uint8, AUTOMATIC, COM_APPL_DATA) retvalPtr
);
#else
#define Com_EB_Read_32_DL_1 Com_EB_Read_DET
#endif

#if ( (COM_RX_LITTLEENDIAN_ENABLE == STD_ON) )
static FUNC(void, COM_CODE) Com_EB_Read_64_DL_1
(
      P2VAR(void, AUTOMATIC, COM_APPL_DATA) SignalDataPtr,
      P2CONST(uint8, AUTOMATIC, COM_VAR_NOINIT) dataPtr,
      P2CONST(ComSignalBaseType, AUTOMATIC, AUTOMATIC) Com_EB_ReadPropPtr,
      P2VAR(uint8, AUTOMATIC, COM_APPL_DATA) retvalPtr
);
#else
#define Com_EB_Read_64_DL_1 Com_EB_Read_DET
#endif

static FUNC(void, COM_CODE) Com_EB_Read_AY_DL_1
(
      P2VAR(void, AUTOMATIC, COM_APPL_DATA) SignalDataPtr,
      P2CONST(uint8, AUTOMATIC, COM_VAR_NOINIT) dataPtr,
      P2CONST(ComSignalBaseType, AUTOMATIC, AUTOMATIC) Com_EB_ReadPropPtr,
      P2VAR(uint8, AUTOMATIC, COM_APPL_DATA) retvalPtr
);

#if (COM_RX_BIGENDIAN_ENABLE == STD_ON)
static FUNC(void, COM_CODE) Com_EB_Read_08_DL_2
(
   P2VAR(void, AUTOMATIC, COM_APPL_DATA) SignalDataPtr,
   P2CONST(uint8, AUTOMATIC, COM_VAR_NOINIT) dataPtr,
   P2CONST(ComSignalBaseType, AUTOMATIC, AUTOMATIC) Com_EB_ReadPropPtr,
   P2VAR(uint8, AUTOMATIC, COM_APPL_DATA) retvalPtr
);
#else
#define Com_EB_Read_08_DL_2 Com_EB_Read_DET
#endif

#if (COM_RX_BIGENDIAN_ENABLE == STD_ON)
static FUNC(void, COM_CODE) Com_EB_Read_16_DL_2
(
      P2VAR(void, AUTOMATIC, COM_APPL_DATA) SignalDataPtr,
      P2CONST(uint8, AUTOMATIC, COM_VAR_NOINIT) dataPtr,
      P2CONST(ComSignalBaseType, AUTOMATIC, AUTOMATIC) Com_EB_ReadPropPtr,
      P2VAR(uint8, AUTOMATIC, COM_APPL_DATA) retvalPtr
);
#else
#define Com_EB_Read_16_DL_2 Com_EB_Read_DET
#endif

#if (COM_RX_BIGENDIAN_ENABLE == STD_ON)
static FUNC(void, COM_CODE) Com_EB_Read_32_DL_2
(
      P2VAR(void, AUTOMATIC, COM_APPL_DATA) SignalDataPtr,
      P2CONST(uint8, AUTOMATIC, COM_VAR_NOINIT) dataPtr,
      P2CONST(ComSignalBaseType, AUTOMATIC, AUTOMATIC) Com_EB_ReadPropPtr,
      P2VAR(uint8, AUTOMATIC, COM_APPL_DATA) retvalPtr
);
#else
#define Com_EB_Read_32_DL_2 Com_EB_Read_DET
#endif

#if ( (COM_RX_BIGENDIAN_ENABLE == STD_ON) )
static FUNC(void, COM_CODE) Com_EB_Read_64_DL_2
(
      P2VAR(void, AUTOMATIC, COM_APPL_DATA) SignalDataPtr,
      P2CONST(uint8, AUTOMATIC, COM_VAR_NOINIT) dataPtr,
      P2CONST(ComSignalBaseType, AUTOMATIC, AUTOMATIC) Com_EB_ReadPropPtr,
      P2VAR(uint8, AUTOMATIC, COM_APPL_DATA) retvalPtr
);
#else
#define Com_EB_Read_64_DL_2 Com_EB_Read_DET
#endif

static FUNC(void, COM_CODE) Com_EB_Read_AY_DL_2
(
      P2VAR(void, AUTOMATIC, COM_APPL_DATA) SignalDataPtr,
      P2CONST(uint8, AUTOMATIC, COM_VAR_NOINIT) dataPtr,
      P2CONST(ComSignalBaseType, AUTOMATIC, AUTOMATIC) Com_EB_ReadPropPtr,
      P2VAR(uint8, AUTOMATIC, COM_APPL_DATA) retvalPtr
);

#if (COM_RX_LITTLEENDIAN_ENABLE == STD_ON)
static FUNC(void, COM_CODE) Com_EB_Read_08_EL_1
(
   P2VAR(void, AUTOMATIC, COM_APPL_DATA) SignalDataPtr,
   P2CONST(uint8, AUTOMATIC, COM_VAR_NOINIT) dataPtr,
   P2CONST(ComSignalBaseType, AUTOMATIC, AUTOMATIC) Com_EB_ReadPropPtr,
   P2VAR(uint8, AUTOMATIC, COM_APPL_DATA) retvalPtr
);
#else
#define Com_EB_Read_08_EL_1 Com_EB_Read_DET
#endif

#if (COM_RX_LITTLEENDIAN_ENABLE == STD_ON)
static FUNC(void, COM_CODE) Com_EB_Read_16_EL_1
(
      P2VAR(void, AUTOMATIC, COM_APPL_DATA) SignalDataPtr,
      P2CONST(uint8, AUTOMATIC, COM_VAR_NOINIT) dataPtr,
      P2CONST(ComSignalBaseType, AUTOMATIC, AUTOMATIC) Com_EB_ReadPropPtr,
      P2VAR(uint8, AUTOMATIC, COM_APPL_DATA) retvalPtr
);
#else
#define Com_EB_Read_16_EL_1 Com_EB_Read_DET
#endif

#if (COM_RX_LITTLEENDIAN_ENABLE == STD_ON)
static FUNC(void, COM_CODE) Com_EB_Read_32_EL_1
(
      P2VAR(void, AUTOMATIC, COM_APPL_DATA) SignalDataPtr,
      P2CONST(uint8, AUTOMATIC, COM_VAR_NOINIT) dataPtr,
      P2CONST(ComSignalBaseType, AUTOMATIC, AUTOMATIC) Com_EB_ReadPropPtr,
      P2VAR(uint8, AUTOMATIC, COM_APPL_DATA) retvalPtr
);
#else
#define Com_EB_Read_32_EL_1 Com_EB_Read_DET
#endif

#if ( (COM_RX_LITTLEENDIAN_ENABLE == STD_ON) )
static FUNC(void, COM_CODE) Com_EB_Read_64_EL_1
(
      P2VAR(void, AUTOMATIC, COM_APPL_DATA) SignalDataPtr,
      P2CONST(uint8, AUTOMATIC, COM_VAR_NOINIT) dataPtr,
      P2CONST(ComSignalBaseType, AUTOMATIC, AUTOMATIC) Com_EB_ReadPropPtr,
      P2VAR(uint8, AUTOMATIC, COM_APPL_DATA) retvalPtr
);
#else
#define Com_EB_Read_64_EL_1 Com_EB_Read_DET
#endif

static FUNC(void, COM_CODE) Com_EB_Read_AY_EL_1
(
      P2VAR(void, AUTOMATIC, COM_APPL_DATA) SignalDataPtr,
      P2CONST(uint8, AUTOMATIC, COM_VAR_NOINIT) dataPtr,
      P2CONST(ComSignalBaseType, AUTOMATIC, AUTOMATIC) Com_EB_ReadPropPtr,
      P2VAR(uint8, AUTOMATIC, COM_APPL_DATA) retvalPtr
);

#if (COM_RX_BIGENDIAN_ENABLE == STD_ON)
static FUNC(void, COM_CODE) Com_EB_Read_08_EL_2
(
   P2VAR(void, AUTOMATIC, COM_APPL_DATA) SignalDataPtr,
   P2CONST(uint8, AUTOMATIC, COM_VAR_NOINIT) dataPtr,
   P2CONST(ComSignalBaseType, AUTOMATIC, AUTOMATIC) Com_EB_ReadPropPtr,
   P2VAR(uint8, AUTOMATIC, COM_APPL_DATA) retvalPtr
);
#else
#define Com_EB_Read_08_EL_2 Com_EB_Read_DET
#endif

#if (COM_RX_BIGENDIAN_ENABLE == STD_ON)
static FUNC(void, COM_CODE) Com_EB_Read_16_EL_2
(
      P2VAR(void, AUTOMATIC, COM_APPL_DATA) SignalDataPtr,
      P2CONST(uint8, AUTOMATIC, COM_VAR_NOINIT) dataPtr,
      P2CONST(ComSignalBaseType, AUTOMATIC, AUTOMATIC) Com_EB_ReadPropPtr,
      P2VAR(uint8, AUTOMATIC, COM_APPL_DATA) retvalPtr
);
#else
#define Com_EB_Read_16_EL_2 Com_EB_Read_DET
#endif

#if (COM_RX_BIGENDIAN_ENABLE == STD_ON)
static FUNC(void, COM_CODE) Com_EB_Read_32_EL_2
(
      P2VAR(void, AUTOMATIC, COM_APPL_DATA) SignalDataPtr,
      P2CONST(uint8, AUTOMATIC, COM_VAR_NOINIT) dataPtr,
      P2CONST(ComSignalBaseType, AUTOMATIC, AUTOMATIC) Com_EB_ReadPropPtr,
      P2VAR(uint8, AUTOMATIC, COM_APPL_DATA) retvalPtr
);
#else
#define Com_EB_Read_32_EL_2 Com_EB_Read_DET
#endif

#if ( (COM_RX_BIGENDIAN_ENABLE == STD_ON) )
static FUNC(void, COM_CODE) Com_EB_Read_64_EL_2
(
      P2VAR(void, AUTOMATIC, COM_APPL_DATA) SignalDataPtr,
      P2CONST(uint8, AUTOMATIC, COM_VAR_NOINIT) dataPtr,
      P2CONST(ComSignalBaseType, AUTOMATIC, AUTOMATIC) Com_EB_ReadPropPtr,
      P2VAR(uint8, AUTOMATIC, COM_APPL_DATA) retvalPtr
);
#else
#define Com_EB_Read_64_EL_2 Com_EB_Read_DET
#endif

static FUNC(void, COM_CODE) Com_EB_Read_AY_EL_2
(
      P2VAR(void, AUTOMATIC, COM_APPL_DATA) SignalDataPtr,
      P2CONST(uint8, AUTOMATIC, COM_VAR_NOINIT) dataPtr,
      P2CONST(ComSignalBaseType, AUTOMATIC, AUTOMATIC) Com_EB_ReadPropPtr,
      P2VAR(uint8, AUTOMATIC, COM_APPL_DATA) retvalPtr
);

static FUNC(void, COM_CODE) Com_EB_Read_AY_DL_3
(
   P2VAR(void, AUTOMATIC, COM_APPL_DATA) SignalDataPtr,
   P2CONST(uint8, AUTOMATIC, COM_VAR_NOINIT) dataPtr,
   P2CONST(ComSignalBaseType, AUTOMATIC, AUTOMATIC) Com_EB_ReadPropPtr,
   P2VAR(uint8, AUTOMATIC, COM_APPL_DATA) retvalPtr
);

static FUNC(void, COM_CODE) Com_EB_Read_AY_EL_3
(
   P2VAR(void, AUTOMATIC, COM_APPL_DATA) SignalDataPtr,
   P2CONST(uint8, AUTOMATIC, COM_VAR_NOINIT) dataPtr,
   P2CONST(ComSignalBaseType, AUTOMATIC, AUTOMATIC) Com_EB_ReadPropPtr,
   P2VAR(uint8, AUTOMATIC, COM_APPL_DATA) retvalPtr
);

static FUNC(void, COM_CODE) Com_EB_Read_08_DL_SignExt
(
   P2VAR(void, AUTOMATIC, COM_APPL_DATA) SignalDataPtr,
   P2CONST(uint8, AUTOMATIC, COM_VAR_NOINIT) dataPtr,
   P2CONST(ComSignalBaseType, AUTOMATIC, AUTOMATIC) Com_EB_ReadPropPtr,
   P2VAR(uint8, AUTOMATIC, COM_APPL_DATA) retvalPtr
);

static FUNC(void, COM_CODE) Com_EB_Read_08_EL_SignExt
(
   P2VAR(void, AUTOMATIC, COM_APPL_DATA) SignalDataPtr,
   P2CONST(uint8, AUTOMATIC, COM_VAR_NOINIT) dataPtr,
   P2CONST(ComSignalBaseType, AUTOMATIC, AUTOMATIC) Com_EB_ReadPropPtr,
   P2VAR(uint8, AUTOMATIC, COM_APPL_DATA) retvalPtr
);

static FUNC(void, COM_CODE) Com_EB_Read_16_DL_SignExt
(
   P2VAR(void, AUTOMATIC, COM_APPL_DATA) SignalDataPtr,
   P2CONST(uint8, AUTOMATIC, COM_VAR_NOINIT) dataPtr,
   P2CONST(ComSignalBaseType, AUTOMATIC, AUTOMATIC) Com_EB_ReadPropPtr,
   P2VAR(uint8, AUTOMATIC, COM_APPL_DATA) retvalPtr
);

static FUNC(void, COM_CODE) Com_EB_Read_16_EL_SignExt
(
   P2VAR(void, AUTOMATIC, COM_APPL_DATA) SignalDataPtr,
   P2CONST(uint8, AUTOMATIC, COM_VAR_NOINIT) dataPtr,
   P2CONST(ComSignalBaseType, AUTOMATIC, AUTOMATIC) Com_EB_ReadPropPtr,
   P2VAR(uint8, AUTOMATIC, COM_APPL_DATA) retvalPtr
);

static FUNC(void, COM_CODE) Com_EB_Read_32_DL_SignExt
(
   P2VAR(void, AUTOMATIC, COM_APPL_DATA) SignalDataPtr,
   P2CONST(uint8, AUTOMATIC, COM_VAR_NOINIT) dataPtr,
   P2CONST(ComSignalBaseType, AUTOMATIC, AUTOMATIC) Com_EB_ReadPropPtr,
   P2VAR(uint8, AUTOMATIC, COM_APPL_DATA) retvalPtr
);

static FUNC(void, COM_CODE) Com_EB_Read_32_EL_SignExt
(
   P2VAR(void, AUTOMATIC, COM_APPL_DATA) SignalDataPtr,
   P2CONST(uint8, AUTOMATIC, COM_VAR_NOINIT) dataPtr,
   P2CONST(ComSignalBaseType, AUTOMATIC, AUTOMATIC) Com_EB_ReadPropPtr,
   P2VAR(uint8, AUTOMATIC, COM_APPL_DATA) retvalPtr
);

static FUNC(void, COM_CODE) Com_EB_Read_BO_DL
(
   P2VAR(void, AUTOMATIC, COM_APPL_DATA) SignalDataPtr,
   P2CONST(uint8, AUTOMATIC, COM_VAR_NOINIT) dataPtr,
   P2CONST(ComSignalBaseType, AUTOMATIC, AUTOMATIC) Com_EB_ReadPropPtr,
   P2VAR(uint8, AUTOMATIC, COM_APPL_DATA) retvalPtr
);

static FUNC(void, COM_CODE) Com_EB_Read_A1_DL
(
   P2VAR(void, AUTOMATIC, COM_APPL_DATA) SignalDataPtr,
   P2CONST(uint8, AUTOMATIC, COM_VAR_NOINIT) dataPtr,
   P2CONST(ComSignalBaseType, AUTOMATIC, AUTOMATIC) Com_EB_ReadPropPtr,
   P2VAR(uint8, AUTOMATIC, COM_APPL_DATA) retvalPtr
);

static FUNC(void, COM_CODE) Com_EB_Read_BO_EL
(
   P2VAR(void, AUTOMATIC, COM_APPL_DATA) SignalDataPtr,
   P2CONST(uint8, AUTOMATIC, COM_VAR_NOINIT) dataPtr,
   P2CONST(ComSignalBaseType, AUTOMATIC, AUTOMATIC) Com_EB_ReadPropPtr,
   P2VAR(uint8, AUTOMATIC, COM_APPL_DATA) retvalPtr
);

static FUNC(void, COM_CODE) Com_EB_Read_A1_EL
(
   P2VAR(void, AUTOMATIC, COM_APPL_DATA) SignalDataPtr,
   P2CONST(uint8, AUTOMATIC, COM_VAR_NOINIT) dataPtr,
   P2CONST(ComSignalBaseType, AUTOMATIC, AUTOMATIC) Com_EB_ReadPropPtr,
   P2VAR(uint8, AUTOMATIC, COM_APPL_DATA) retvalPtr
);

static FUNC(void, COM_CODE) Com_EB_Read_DET
(
      P2VAR(void, AUTOMATIC, COM_APPL_DATA) SignalDataPtr,
      P2CONST(uint8, AUTOMATIC, COM_VAR_NOINIT) dataPtr,
      P2CONST(ComSignalBaseType, AUTOMATIC, AUTOMATIC) Com_EB_ReadPropPtr,
      P2VAR(uint8, AUTOMATIC, COM_APPL_DATA) retvalPtr
);

#define COM_STOP_SEC_CODE
#include <Com_MemMap.h>

/*==================[external constants]====================================*/

#define COM_START_SEC_CONST_UNSPECIFIED
#include <Com_MemMap.h>

CONSTP2VAR(Com_ReadFuncType, AUTOMATIC, COM_CODE)
        COM_READFUNCS[COM_CORE_READ_ARRAY_SIZE]=
{
      /*  00 */   Com_EB_Read_08_DL_1,
      /*  01 */   Com_EB_Read_16_DL_1,
      /*  02 */   Com_EB_Read_32_DL_1,
      /*  03 */   Com_EB_Read_AY_DL_1,
      /*  04 */   Com_EB_Read_08_DL_2,
      /*  05 */   Com_EB_Read_16_DL_2,
      /*  06 */   Com_EB_Read_32_DL_2,
      /*  07 */   Com_EB_Read_AY_DL_2,
      /*  08 */   Com_EB_Read_08_EL_1,
      /*  09 */   Com_EB_Read_16_EL_1,
      /*  10 */   Com_EB_Read_32_EL_1,
      /*  11 */   Com_EB_Read_AY_EL_1,
      /*  12 */   Com_EB_Read_08_EL_2,
      /*  13 */   Com_EB_Read_16_EL_2,
      /*  14 */   Com_EB_Read_32_EL_2,
      /*  15 */   Com_EB_Read_AY_EL_2,
      /*  16 */   Com_EB_Read_08_DL_SignExt,
      /*  17 */   Com_EB_Read_16_DL_SignExt,
      /*  18 */   Com_EB_Read_32_DL_SignExt,
      /*  19 */   Com_EB_Read_AY_DL_3,
      /*  20 */   Com_EB_Read_08_DL_SignExt,
      /*  21 */   Com_EB_Read_16_DL_SignExt,
      /*  22 */   Com_EB_Read_32_DL_SignExt,
      /*  23 */   Com_EB_Read_DET,
      /*  24 */   Com_EB_Read_08_EL_SignExt,
      /*  25 */   Com_EB_Read_16_EL_SignExt,
      /*  26 */   Com_EB_Read_32_EL_SignExt,
      /*  27 */   Com_EB_Read_AY_EL_3,
      /*  28 */   Com_EB_Read_08_EL_SignExt,
      /*  29 */   Com_EB_Read_16_EL_SignExt,
      /*  30 */   Com_EB_Read_32_EL_SignExt,
      /*  31 */   Com_EB_Read_DET,

      /*  32 */   Com_EB_Read_BO_DL,
      /*  33 */   Com_EB_Read_A1_DL,
      /*  34 */   Com_EB_Read_DET,
      /*  35 */   Com_EB_Read_64_DL_1,
      /*  36 */   Com_EB_Read_DET,
      /*  37 */   Com_EB_Read_DET,
      /*  38 */   Com_EB_Read_DET,
      /*  39 */   Com_EB_Read_64_DL_2,
      /*  40 */   Com_EB_Read_BO_EL,
      /*  41 */   Com_EB_Read_A1_EL,
      /*  42 */   Com_EB_Read_DET,
      /*  43 */   Com_EB_Read_64_EL_1,
      /*  44 */   Com_EB_Read_DET,
      /*  45 */   Com_EB_Read_DET,
      /*  46 */   Com_EB_Read_DET,
      /*  47 */   Com_EB_Read_64_EL_2,
      /*  48 */   Com_EB_Read_DET,
      /*  49 */   Com_EB_Read_DET,
      /*  50 */   Com_EB_Read_DET,
      /*  51 */   Com_EB_Read_DET,
      /*  52 */   Com_EB_Read_DET,
      /*  53 */   Com_EB_Read_DET,
      /*  54 */   Com_EB_Read_DET,
      /*  55 */   Com_EB_Read_DET,
      /*  56 */   Com_EB_Read_DET,
      /*  57 */   Com_EB_Read_DET,
      /*  58 */   Com_EB_Read_DET,
      /*  59 */   Com_EB_Read_DET,
      /*  60 */   Com_EB_Read_DET,
      /*  61 */   Com_EB_Read_DET,
      /*  62 */   Com_EB_Read_DET,
      /*  63 */   Com_EB_Read_DET,

      /*  64 */   Com_EB_Read_SignalExt,   /*  00 */
      /*  65 */   Com_EB_Read_SignalExt,   /*  01 */
      /*  66 */   Com_EB_Read_SignalExt,   /*  02 */
      /*  67 */   Com_EB_Read_SignalExt,   /*  03 */
      /*  68 */   Com_EB_Read_SignalExt,   /*  04 */
      /*  69 */   Com_EB_Read_SignalExt,   /*  05 */
      /*  70 */   Com_EB_Read_SignalExt,   /*  06 */
      /*  71 */   Com_EB_Read_SignalExt,   /*  07 */
      /*  72 */   Com_EB_Read_SignalExt,   /*  08 */
      /*  73 */   Com_EB_Read_SignalExt,   /*  09 */
      /*  74 */   Com_EB_Read_SignalExt,   /*  10 */
      /*  75 */   Com_EB_Read_SignalExt,   /*  11 */
      /*  76 */   Com_EB_Read_SignalExt,   /*  12 */
      /*  77 */   Com_EB_Read_SignalExt,   /*  13 */
      /*  78 */   Com_EB_Read_SignalExt,   /*  14 */
      /*  79 */   Com_EB_Read_SignalExt,   /*  15 */
      /*  80 */   Com_EB_Read_SignalExt,   /*  16 */
      /*  81 */   Com_EB_Read_SignalExt,   /*  17 */
      /*  82 */   Com_EB_Read_SignalExt,   /*  18 */
      /*  83 */   Com_EB_Read_SignalExt,   /*  19 */
      /*  84 */   Com_EB_Read_SignalExt,   /*  20 */
      /*  85 */   Com_EB_Read_SignalExt,   /*  21 */
      /*  86 */   Com_EB_Read_SignalExt,   /*  22 */
      /*  87 */   Com_EB_Read_DET,         /*  23 */
      /*  88 */   Com_EB_Read_SignalExt,   /*  24 */
      /*  89 */   Com_EB_Read_SignalExt,   /*  25 */
      /*  90 */   Com_EB_Read_SignalExt,   /*  26 */
      /*  91 */   Com_EB_Read_SignalExt,   /*  27 */
      /*  92 */   Com_EB_Read_SignalExt,   /*  28 */
      /*  93 */   Com_EB_Read_SignalExt,   /*  29 */
      /*  94 */   Com_EB_Read_SignalExt,   /*  30 */
      /*  95 */   Com_EB_Read_DET,         /*  31 */

      /*  96 */   Com_EB_Read_SignalExt,   /*  32 */
      /*  97 */   Com_EB_Read_SignalExt,   /*  33 */
      /*  98 */   Com_EB_Read_SignalExt,   /*  34 */
      /*  99 */   Com_EB_Read_SignalExt,   /*  35 */
      /* 100 */   Com_EB_Read_SignalExt,   /*  36 */
      /* 101 */   Com_EB_Read_SignalExt,   /*  37 */
      /* 102 */   Com_EB_Read_DET,         /*  38 */
      /* 103 */   Com_EB_Read_SignalExt,   /*  39 */

      /* 104 */   Com_EB_Read_SignalExt,   /*  40 */
      /* 105 */   Com_EB_Read_SignalExt,   /*  41 */
      /* 106 */   Com_EB_Read_SignalExt,   /*  42 */
      /* 107 */   Com_EB_Read_SignalExt,   /*  43 */
      /* 108 */   Com_EB_Read_SignalExt,   /*  44 */
      /* 109 */   Com_EB_Read_SignalExt,   /*  45 */
      /* 110 */   Com_EB_Read_DET,         /*  46 */
      /* 111 */   Com_EB_Read_SignalExt,   /*  47 */
      /* 112 */   Com_EB_Read_DET,         /*  48 */
      /* 113 */   Com_EB_Read_DET,         /*  49 */
      /* 114 */   Com_EB_Read_DET,         /*  50 */
      /* 115 */   Com_EB_Read_SignalExt,   /*  51 */
      /* 116 */   Com_EB_Read_DET,         /*  52 */
      /* 117 */   Com_EB_Read_DET,         /*  53 */
      /* 118 */   Com_EB_Read_DET,         /*  54 */
      /* 119 */   Com_EB_Read_SignalExt,   /*  55 */
      /* 120 */   Com_EB_Read_DET,         /*  56 */
      /* 121 */   Com_EB_Read_DET,         /*  57 */
      /* 122 */   Com_EB_Read_DET,         /*  58 */
      /* 123 */   Com_EB_Read_SignalExt,   /*  59 */
      /* 124 */   Com_EB_Read_DET,         /*  60 */
      /* 125 */   Com_EB_Read_DET,         /*  61 */
      /* 126 */   Com_EB_Read_DET,         /*  62 */
      /* 127 */   Com_EB_Read_SignalExt    /*  63 */
};
#define COM_STOP_SEC_CONST_UNSPECIFIED
#include <Com_MemMap.h>


/*==================[internal constants]====================================*/

/*==================[external data]=========================================*/

/*==================[internal data]=========================================*/

/*==================[external function definitions]=========================*/

/*==================[internal function definitions]==========================*/

#define COM_START_SEC_CODE
#include <Com_MemMap.h>

#if (COM_RX_LITTLEENDIAN_ENABLE == STD_ON)
static FUNC(void, COM_CODE) Com_EB_Read_08_DL_1
(
      P2VAR(void, AUTOMATIC, COM_APPL_DATA) SignalDataPtr,
      P2CONST(uint8, AUTOMATIC, COM_VAR_NOINIT) dataPtr,
      P2CONST(ComSignalBaseType, AUTOMATIC, AUTOMATIC) Com_EB_ReadPropPtr,
      P2VAR(uint8, AUTOMATIC, COM_APPL_DATA) retvalPtr
)
{
   /* Deviation MISRAC2012-2 */
   P2VAR (uint8, AUTOMATIC, COM_APPL_DATA) retPtr =
         (P2VAR (uint8, AUTOMATIC, COM_APPL_DATA))SignalDataPtr;

   uint8 value;

   ComSignalDescBitType row = (Com_EB_ReadPropPtr->ComSignalPositionInBit / 8U); /* Starting position of the signals in bits divided by 8 => starting position in byte */
   uint8 col = (uint8)Com_EB_ReadPropPtr->ComSignalPositionInBit % 8U;

   /* Signal position in bit has a maximum value of 2031. */
   sint16 pos = (sint16) row;

   uint16 tmpval;
   const uint8 space = col + 1U;
   uint8 bitsread = 0U;


   if (col == 7U)
   {
       tmpval = dataPtr[pos];
       /* read to much, shift back */
       value = (uint8)(tmpval >> (8U - Com_EB_ReadPropPtr->ComBitSize));
   }
   else
   {
       tmpval = dataPtr[pos];
       /* check number of bytes which shall be read */
       if (space < Com_EB_ReadPropPtr->ComBitSize)
       {
          /* another byte has to be read */
          bitsread = bitsread + 8U;
          tmpval = tmpval << 8U;
          pos = pos - 1;
          tmpval = (uint16)(tmpval | (uint8)(dataPtr[pos]));
       }

       /* read to much, shift back */
       value = (uint8)(tmpval >> ((col + 1U + bitsread) - (uint8)Com_EB_ReadPropPtr->ComBitSize));
   }

   /* mask the unused bits */
   {
      uint8 const mask = (uint8)(0xFFU >> (8U - Com_EB_ReadPropPtr->ComBitSize));
      value = (uint8)(value & mask);
   }

   *retPtr = value;

   TS_PARAM_UNUSED(retvalPtr);
   return;
} /* Com_EB_Read_08_FUNC(COM_EB_LOCK,COM_EB_ENDIAN) */
#endif

#if (COM_RX_LITTLEENDIAN_ENABLE == STD_ON)
static FUNC(void, COM_CODE) Com_EB_Read_16_DL_1
(
      P2VAR(void, AUTOMATIC, COM_APPL_DATA) SignalDataPtr,
      P2CONST(uint8, AUTOMATIC, COM_VAR_NOINIT) dataPtr,
      P2CONST(ComSignalBaseType, AUTOMATIC, AUTOMATIC) Com_EB_ReadPropPtr,
      P2VAR(uint8, AUTOMATIC, COM_APPL_DATA) retvalPtr

)
{
   /* Deviation MISRAC2012-2 */
   P2VAR (uint16, AUTOMATIC, COM_APPL_DATA) retPtr =
         (P2VAR (uint16, AUTOMATIC, COM_APPL_DATA))SignalDataPtr;

   uint16 value;

   uint8 bitsread = 0U;

   sint8 ssize = (sint8)Com_EB_ReadPropPtr->ComBitSize;

   uint32 tmpval;

   ComSignalDescBitType row = (Com_EB_ReadPropPtr->ComSignalPositionInBit / 8U); /* Starting position of the signals in bits divided by 8 => starting position in byte */
   uint8 col = (uint8)Com_EB_ReadPropPtr->ComSignalPositionInBit % 8U;

   /* Signal position in bit has a maximum value of 2031. */
   sint16 pos = (sint16) row;


   if (col == 7U)
   {
       bitsread = 8U;
       /* read the byte with the MSB */
       tmpval = (uint8)(dataPtr[pos]);

       /* range of col if 0-7, cast to signed char is still in range */
       ssize = ssize - 8;

       while (ssize > 0)
       {
          bitsread = bitsread + 8U;
          ssize = ssize - 8;
          tmpval = (uint32)tmpval << 8U;
          pos = pos - 1;
          tmpval = (uint32)(tmpval | (uint8)(dataPtr[pos]));
       }

       /* read to much, shift back */
       value = (uint16)(tmpval >> (bitsread - Com_EB_ReadPropPtr->ComBitSize));
   }
   else
   {
       /* read the byte with the MSB */
       tmpval = (uint8)(dataPtr[pos]);

       /* range of col if 0-7, cast to signed char is still in range */
       ssize = ssize - 1 - (sint8) col;

       while (ssize > 0)
       {
          bitsread = bitsread + 8U;
          ssize = ssize - 8;
          tmpval = (uint32)tmpval << 8U;
          pos = pos - 1;
          tmpval = (uint32)(tmpval | (uint8)(dataPtr[pos]));
       }

       /* read to much, shift back */
       value = (uint16)(tmpval >> ((col + 1U + bitsread) - (uint8)Com_EB_ReadPropPtr->ComBitSize));
   }

   /* mask the unused bits */
   {
      uint16 const mask = (uint16)(0xFFFFU >> (16U - Com_EB_ReadPropPtr->ComBitSize));
      value = (uint16)(value & mask);
   }

   *retPtr = value;

   TS_PARAM_UNUSED(retvalPtr);
   return;
} /* Com_EB_Read_16_FUNC(COM_EB_LOCK,COM_EB_ENDIAN) */
#endif

#if (COM_RX_LITTLEENDIAN_ENABLE == STD_ON)
static FUNC(void, COM_CODE) Com_EB_Read_32_DL_1
(
      P2VAR(void, AUTOMATIC, COM_APPL_DATA) SignalDataPtr,
      P2CONST(uint8, AUTOMATIC, COM_VAR_NOINIT) dataPtr,
      P2CONST(ComSignalBaseType, AUTOMATIC, AUTOMATIC) Com_EB_ReadPropPtr,
      P2VAR(uint8, AUTOMATIC, COM_APPL_DATA) retvalPtr
)
{
  /* Deviation MISRAC2012-2 */
   P2VAR (uint32, AUTOMATIC, COM_APPL_DATA) retPtr =
         (P2VAR (uint32, AUTOMATIC, COM_APPL_DATA))SignalDataPtr;

   uint32 value = 0;

   ComSignalDescBitType row = (Com_EB_ReadPropPtr->ComSignalPositionInBit / 8U); /* Starting position of the signals in bits divided by 8 => starting position in byte */
   uint8 col = (uint8)Com_EB_ReadPropPtr->ComSignalPositionInBit % 8U;

   /* Signal position in bit has a maximum value of 2031. */
   sint16 pos = (sint16) row;

   ComSignalBitSizeType size = Com_EB_ReadPropPtr->ComBitSize;

      if (col != 7U)
      {
         /* data does not start on byte boundary (MSB) */
         uint8 const space = col + 1;
         uint8 const mask = ((uint8) 0xFFU) >> (7U - col);
         uint8 const tmp_val = dataPtr[pos] & mask;
         value = (uint32) tmp_val;

         if (space >= size)
         {
            /* If we've already read as many or more bits than intended */
            value >>= (space - size);
            size = 0U;
         }
         else
         {
            /* prepare to continue reading */
            pos = pos - 1;
            size -= space;
         }
      }


      while (size > 7U)
      {
         /* read whole bytes */
         value <<= 8U;
         value += dataPtr[pos];
         size -= 8U;
         pos = pos - 1;
      }


      if (size > 0U)
      {
         /* read last bits */
         value <<= size;
         value += (uint32) dataPtr[pos] >> (8U - size);
      }

   *retPtr = value;

   TS_PARAM_UNUSED(retvalPtr);
   return;
} /* Com_EB_Read_32_FUNC(COM_EB_LOCK,COM_EB_ENDIAN) */
#endif

#if ( (COM_RX_LITTLEENDIAN_ENABLE == STD_ON) )
static FUNC(void, COM_CODE) Com_EB_Read_64_DL_1
(
      P2VAR(void, AUTOMATIC, COM_APPL_DATA) SignalDataPtr,
      P2CONST(uint8, AUTOMATIC, COM_VAR_NOINIT) dataPtr,
      P2CONST(ComSignalBaseType, AUTOMATIC, AUTOMATIC) Com_EB_ReadPropPtr,
      P2VAR(uint8, AUTOMATIC, COM_APPL_DATA) retvalPtr

)
{
  P2VAR(ComEmu64Type, AUTOMATIC, AUTOMATIC) SignalDataPtr_loc =
      (P2VAR(ComEmu64Type, AUTOMATIC, COM_APPL_DATA)) SignalDataPtr;

  if(Com_EB_ReadPropPtr->ComBitSize > 32U)
  {
    ComSignalBaseType Com_EB_ReadProp_loc = *Com_EB_ReadPropPtr;

    /* set ComBitSize for higher bytes */
    Com_EB_ReadProp_loc.ComBitSize = Com_EB_ReadPropPtr->ComBitSize - 32U;

    Com_EB_Read_32_DL_1(
          &SignalDataPtr_loc->HiWord,
          dataPtr,
          &Com_EB_ReadProp_loc,
          retvalPtr);

    /* adapt Com_EB_ReadPropPtr_loc for low 32 bits */
    Com_EB_ReadProp_loc.ComSignalPositionInBit =
        Com_EB_ReadPropPtr->ComSignalPositionInBit - (Com_EB_ReadPropPtr->ComBitSize - 32U);
    Com_EB_ReadProp_loc.ComBitSize = 32U;

    Com_EB_Read_32_DL_1(
          &SignalDataPtr_loc->LoWord,
          dataPtr,
          &Com_EB_ReadProp_loc,
          retvalPtr);
  }
  else
  {

    Com_EB_Read_32_DL_1(
          &SignalDataPtr_loc->LoWord,
          dataPtr,
          Com_EB_ReadPropPtr,
          retvalPtr);
  }

  TS_PARAM_UNUSED(retvalPtr);
  return;
} /* Com_EB_Read_64_FUNC(COM_EB_LOCK,COM_EB_ENDIAN) */
#endif

static FUNC(void, COM_CODE) Com_EB_Read_AY_DL_1
(
      P2VAR(void, AUTOMATIC, COM_APPL_DATA) SignalDataPtr,
      P2CONST(uint8, AUTOMATIC, COM_VAR_NOINIT) dataPtr,
      P2CONST(ComSignalBaseType, AUTOMATIC, AUTOMATIC) Com_EB_ReadPropPtr,
      P2VAR(uint8, AUTOMATIC, COM_APPL_DATA) retvalPtr
)
{
   uint16 ii = 0U;
   /* Deviation MISRAC2012-2 */
   P2VAR(uint8, AUTOMATIC, COM_APPL_DATA) U8Ptr =
         (P2VAR(uint8, AUTOMATIC, COM_APPL_DATA)) SignalDataPtr;

   do
   {
      uint16 pos = COM_EB_CONVERT_ENDIAN_RX_POS_NET_E1(Com_EB_ReadPropPtr->ComSignalPositionInBit, Com_EB_ReadPropPtr->ComBitSize, ii);
      U8Ptr[ii] = dataPtr[pos];
      ii++;
   }while (ii < (Com_EB_ReadPropPtr->ComBitSize));

   TS_PARAM_UNUSED(retvalPtr);
   return;
} /* Com_EB_Read_AY_FUNC(COM_EB_LOCK,COM_EB_ENDIAN) */

#if (COM_RX_BIGENDIAN_ENABLE == STD_ON)
static FUNC(void, COM_CODE) Com_EB_Read_08_DL_2
(
      P2VAR(void, AUTOMATIC, COM_APPL_DATA) SignalDataPtr,
      P2CONST(uint8, AUTOMATIC, COM_VAR_NOINIT) dataPtr,
      P2CONST(ComSignalBaseType, AUTOMATIC, AUTOMATIC) Com_EB_ReadPropPtr,
      P2VAR(uint8, AUTOMATIC, COM_APPL_DATA) retvalPtr
)
{
   /* Deviation MISRAC2012-2 */
   P2VAR (uint8, AUTOMATIC, COM_APPL_DATA) retPtr =
         (P2VAR (uint8, AUTOMATIC, COM_APPL_DATA))SignalDataPtr;

   uint8 value;

   ComSignalDescBitType row = (Com_EB_ReadPropPtr->ComSignalPositionInBit / 8U); /* Starting position of the signals in bits divided by 8 => starting position in byte */
   uint8 col = (uint8)Com_EB_ReadPropPtr->ComSignalPositionInBit % 8U;

   /* Signal position in bit has a maximum value of 2031. */
   sint16 pos = (sint16) row;

   uint16 tmpval;
   const uint8 space = col + 1U;
   uint8 bitsread = 0U;

   if (col == 7U)
   {
       tmpval = dataPtr[pos];
       /* read to much, shift back */
       value = (uint8)(tmpval >> (8U - Com_EB_ReadPropPtr->ComBitSize));
   }
   else
   {
       tmpval = dataPtr[pos];
       /* check number of bytes which shall be read */
       if (space < Com_EB_ReadPropPtr->ComBitSize)
       {
          /* another byte has to be read */
          bitsread = bitsread + 8U;
          tmpval = tmpval << 8U;
          pos = pos + 1;
          tmpval = (uint16)(tmpval | (uint8)(dataPtr[pos]));
       }

       /* read to much, shift back */
       value = (uint8)(tmpval >> ((col + 1U + bitsread) - (uint8)Com_EB_ReadPropPtr->ComBitSize));
   }

   /* mask the unused bits */
   {
      uint8 const mask = (uint8)(0xFFU >> (8U - Com_EB_ReadPropPtr->ComBitSize));
      value = (uint8)(value & mask);
   }

   *retPtr = value;

   TS_PARAM_UNUSED(retvalPtr);
   return;
} /* Com_EB_Read_08_FUNC(COM_EB_LOCK,COM_EB_ENDIAN) */
#endif

#if (COM_RX_BIGENDIAN_ENABLE == STD_ON)
static FUNC(void, COM_CODE) Com_EB_Read_16_DL_2
(
      P2VAR(void, AUTOMATIC, COM_APPL_DATA) SignalDataPtr,
      P2CONST(uint8, AUTOMATIC, COM_VAR_NOINIT) dataPtr,
      P2CONST(ComSignalBaseType, AUTOMATIC, AUTOMATIC) Com_EB_ReadPropPtr,
      P2VAR(uint8, AUTOMATIC, COM_APPL_DATA) retvalPtr

)
{
   /* Deviation MISRAC2012-2 */
   P2VAR (uint16, AUTOMATIC, COM_APPL_DATA) retPtr =
         (P2VAR (uint16, AUTOMATIC, COM_APPL_DATA))SignalDataPtr;

   uint16 value;

   uint8 bitsread = 0U;

   sint8 ssize = (sint8)Com_EB_ReadPropPtr->ComBitSize;

   uint32 tmpval;

   ComSignalDescBitType row = (Com_EB_ReadPropPtr->ComSignalPositionInBit / 8U); /* Starting position of the signals in bits divided by 8 => starting position in byte */
   uint8 col = (uint8)Com_EB_ReadPropPtr->ComSignalPositionInBit % 8U;

   /* Signal position in bit has a maximum value of 2031. */
   sint16 pos = (sint16) row;

   if (col == 7U)
   {
       bitsread = 8U;
       /* read the byte with the MSB */
       tmpval = (uint8)(dataPtr[pos]);

       /* range of col if 0-7, cast to signed char is still in range */
       ssize = ssize - 8;

       while (ssize > 0)
       {
          bitsread = bitsread + 8U;
          ssize = ssize - 8;
          tmpval = (uint32)tmpval << 8U;
          pos = pos + 1;
          tmpval = (uint32)(tmpval | (uint8)(dataPtr[pos]));
       }

       /* read to much, shift back */
       value = (uint16)(tmpval >> (bitsread - Com_EB_ReadPropPtr->ComBitSize));
   }
   else
   {
       /* read the byte with the MSB */
       tmpval = (uint8)(dataPtr[pos]);

       /* range of col if 0-7, cast to signed char is still in range */
       ssize = ssize - 1 - (sint8) col;

       while (ssize > 0)
       {
          bitsread = bitsread + 8U;
          ssize = ssize - 8;
          tmpval = (uint32)tmpval << 8U;
          pos = pos + 1;
          tmpval = (uint32)(tmpval | (uint8)(dataPtr[pos]));
       }

       /* read to much, shift back */
       value = (uint16)(tmpval >> ((col + 1U + bitsread) - (uint8)Com_EB_ReadPropPtr->ComBitSize));
   }

   /* mask the unused bits */
   {
      uint16 const mask = (uint16)(0xFFFFU >> (16U - Com_EB_ReadPropPtr->ComBitSize));
      value = (uint16)(value & mask);
   }

   *retPtr = value;

   TS_PARAM_UNUSED(retvalPtr);
   return;
} /* Com_EB_Read_16_FUNC(COM_EB_LOCK,COM_EB_ENDIAN) */
#endif

#if (COM_RX_BIGENDIAN_ENABLE == STD_ON)
static FUNC(void, COM_CODE) Com_EB_Read_32_DL_2
(
      P2VAR(void, AUTOMATIC, COM_APPL_DATA) SignalDataPtr,
      P2CONST(uint8, AUTOMATIC, COM_VAR_NOINIT) dataPtr,
      P2CONST(ComSignalBaseType, AUTOMATIC, AUTOMATIC) Com_EB_ReadPropPtr,
      P2VAR(uint8, AUTOMATIC, COM_APPL_DATA) retvalPtr

)
{
   /* Deviation MISRAC2012-2 */
   P2VAR (uint32, AUTOMATIC, COM_APPL_DATA) retPtr =
         (P2VAR (uint32, AUTOMATIC, COM_APPL_DATA))SignalDataPtr;

   uint32 value = 0;

   ComSignalDescBitType row = (Com_EB_ReadPropPtr->ComSignalPositionInBit / 8U); /* Starting position of the signals in bits divided by 8 => starting position in byte */
   uint8 col = (uint8)Com_EB_ReadPropPtr->ComSignalPositionInBit % 8U;

   /* Signal position in bit has a maximum value of 2031. */
   sint16 pos = (sint16) row;

   ComSignalBitSizeType size = Com_EB_ReadPropPtr->ComBitSize;

      if (col != 7U)
      {
         /* data does not start on byte boundary (MSB) */
         uint8 const space = col + 1;
         uint8 const mask = ((uint8) 0xFFU) >> (7U - col);
         uint8 const tmp_val = dataPtr[pos] & mask;
         value = (uint32) tmp_val;

         if (space >= size)
         {
            /* If we've already read as many or more bits than intended */
            value >>= (space - size);
            size = 0U;
         }
         else
         {
            /* prepare to continue reading */
            pos = pos + 1;
            size -= space;
         }
      }

      while (size > 7U)
      {
         /* read whole bytes */
         value <<= 8U;
         value += dataPtr[pos];
         size -= 8U;
         pos = pos + 1;
      }

      if (size > 0U)
      {
         /* read last bits */
         value <<= size;
         value += (uint32) dataPtr[pos] >> (8U - size);
      }

   *retPtr = value;

   TS_PARAM_UNUSED(retvalPtr);
   return;
} /* Com_EB_Read_32_FUNC(COM_EB_LOCK,COM_EB_ENDIAN) */
#endif

#if ( (COM_RX_BIGENDIAN_ENABLE == STD_ON) )
static FUNC(void, COM_CODE) Com_EB_Read_64_DL_2
(
      P2VAR(void, AUTOMATIC, COM_APPL_DATA) SignalDataPtr,
      P2CONST(uint8, AUTOMATIC, COM_VAR_NOINIT) dataPtr,
      P2CONST(ComSignalBaseType, AUTOMATIC, AUTOMATIC) Com_EB_ReadPropPtr,
      P2VAR(uint8, AUTOMATIC, COM_APPL_DATA) retvalPtr

)
{
  P2VAR(ComEmu64Type, AUTOMATIC, AUTOMATIC) SignalDataPtr_loc =
      (P2VAR(ComEmu64Type, AUTOMATIC, COM_APPL_DATA)) SignalDataPtr;

  if(Com_EB_ReadPropPtr->ComBitSize > 32U)
  {
    ComSignalBaseType Com_EB_ReadProp_loc = *Com_EB_ReadPropPtr;

    /* set ComBitSize for higher bytes */
    Com_EB_ReadProp_loc.ComBitSize = Com_EB_ReadPropPtr->ComBitSize - 32U;

    Com_EB_Read_32_DL_2(
          &SignalDataPtr_loc->HiWord,
          dataPtr,
          &Com_EB_ReadProp_loc,
          retvalPtr);

    /* adapt Com_EB_ReadPropPtr_loc for low 32 bits */
    Com_EB_ReadProp_loc.ComSignalPositionInBit =
        Com_EB_ReadPropPtr->ComSignalPositionInBit + (Com_EB_ReadPropPtr->ComBitSize - 32U);
    Com_EB_ReadProp_loc.ComBitSize = 32U;

    Com_EB_Read_32_DL_2(
          &SignalDataPtr_loc->LoWord,
          dataPtr,
          &Com_EB_ReadProp_loc,
          retvalPtr);
  }
  else
  {
    Com_EB_Read_32_DL_2(
          &SignalDataPtr_loc->LoWord,
          dataPtr,
          Com_EB_ReadPropPtr,
          retvalPtr);
  }

  TS_PARAM_UNUSED(retvalPtr);
  return;
} /* Com_EB_Read_64_FUNC(COM_EB_LOCK,COM_EB_ENDIAN) */
#endif

static FUNC(void, COM_CODE) Com_EB_Read_AY_DL_2
(
      P2VAR(void, AUTOMATIC, COM_APPL_DATA) SignalDataPtr,
      P2CONST(uint8, AUTOMATIC, COM_VAR_NOINIT) dataPtr,
      P2CONST(ComSignalBaseType, AUTOMATIC, AUTOMATIC) Com_EB_ReadPropPtr,
      P2VAR(uint8, AUTOMATIC, COM_APPL_DATA) retvalPtr
)
{
   uint16 ii = 0U;
   /* Deviation MISRAC2012-2 */
   P2VAR(uint8, AUTOMATIC, COM_APPL_DATA) U8Ptr =
         (P2VAR(uint8, AUTOMATIC, COM_APPL_DATA)) SignalDataPtr;

   do
   {
      uint16 pos = COM_EB_CONVERT_ENDIAN_RX_POS_NET_E2(Com_EB_ReadPropPtr->ComSignalPositionInBit, Com_EB_ReadPropPtr->ComBitSize, ii);
      U8Ptr[ii] = dataPtr[pos];
      ii++;
   }while (ii < (Com_EB_ReadPropPtr->ComBitSize));

   TS_PARAM_UNUSED(retvalPtr);
   return;
} /* Com_EB_Read_AY_FUNC(COM_EB_LOCK,COM_EB_ENDIAN) */

#if (COM_RX_LITTLEENDIAN_ENABLE == STD_ON)
static FUNC(void, COM_CODE) Com_EB_Read_08_EL_1
(
      P2VAR(void, AUTOMATIC, COM_APPL_DATA) SignalDataPtr,
      P2CONST(uint8, AUTOMATIC, COM_VAR_NOINIT) dataPtr,
      P2CONST(ComSignalBaseType, AUTOMATIC, AUTOMATIC) Com_EB_ReadPropPtr,
      P2VAR(uint8, AUTOMATIC, COM_APPL_DATA) retvalPtr
)
{
   /* Deviation MISRAC2012-2 */
   P2VAR (uint8, AUTOMATIC, COM_APPL_DATA) retPtr =
         (P2VAR (uint8, AUTOMATIC, COM_APPL_DATA))SignalDataPtr;

   uint8 value;

   ComSignalDescBitType row = (Com_EB_ReadPropPtr->ComSignalPositionInBit / 8U); /* Starting position of the signals in bits divided by 8 => starting position in byte */
   uint8 col = (uint8)Com_EB_ReadPropPtr->ComSignalPositionInBit % 8U;

   /* Signal position in bit has a maximum value of 2031. */
   sint16 pos = (sint16) row;

   uint16 tmpval;
   const uint8 space = col + 1U;
   uint8 bitsread = 0U;

   if (col == 7U)
   {
       TS_AtomicAssign8(tmpval, dataPtr[pos]);
       /* read to much, shift back */
       value = (uint8)(tmpval >> (8U - Com_EB_ReadPropPtr->ComBitSize));
   }
   else
   {
       /* check number of bytes which shall be read */
       if (space < Com_EB_ReadPropPtr->ComBitSize)
       {
          Com_EB_SchM_Enter_SCHM_COM_EXCLUSIVE_AREA_0();

          tmpval = dataPtr[pos];
          /* another byte has to be read */
          bitsread = bitsread + 8U;
          tmpval = tmpval << 8U;
          pos = pos - 1;
          tmpval = (uint16)(tmpval | (uint8)(dataPtr[pos]));

          Com_EB_SchM_Exit_SCHM_COM_EXCLUSIVE_AREA_0();
       }
       else
       {
          TS_AtomicAssign8(tmpval, dataPtr[pos]);
       }

       /* read to much, shift back */
       value = (uint8)(tmpval >> ((col + 1U + bitsread) - (uint8)Com_EB_ReadPropPtr->ComBitSize));
   }


   /* mask the unused bits */
   {
      uint8 const mask = (uint8)(0xFFU >> (8U - Com_EB_ReadPropPtr->ComBitSize));
      value = (uint8)(value & mask);
   }

   *retPtr = value;

   TS_PARAM_UNUSED(retvalPtr);
   return;
} /* Com_EB_Read_08_FUNC(COM_EB_LOCK,COM_EB_ENDIAN) */
#endif

#if (COM_RX_LITTLEENDIAN_ENABLE == STD_ON)
static FUNC(void, COM_CODE) Com_EB_Read_16_EL_1
(
      P2VAR(void, AUTOMATIC, COM_APPL_DATA) SignalDataPtr,
      P2CONST(uint8, AUTOMATIC, COM_VAR_NOINIT) dataPtr,
      P2CONST(ComSignalBaseType, AUTOMATIC, AUTOMATIC) Com_EB_ReadPropPtr,
      P2VAR(uint8, AUTOMATIC, COM_APPL_DATA) retvalPtr
)
{
   /* Deviation MISRAC2012-2 */
   P2VAR (uint16, AUTOMATIC, COM_APPL_DATA) retPtr =
         (P2VAR (uint16, AUTOMATIC, COM_APPL_DATA))SignalDataPtr;

   uint16 value;

   uint8 bitsread = 0U;

   sint8 ssize = (sint8)Com_EB_ReadPropPtr->ComBitSize;

   uint32 tmpval;

   ComSignalDescBitType row = (Com_EB_ReadPropPtr->ComSignalPositionInBit / 8U); /* Starting position of the signals in bits divided by 8 => starting position in byte */
   uint8 col = (uint8)Com_EB_ReadPropPtr->ComSignalPositionInBit % 8U;

   /* Signal position in bit has a maximum value of 2031. */
   sint16 pos = (sint16) row;

   Com_EB_SchM_Enter_SCHM_COM_EXCLUSIVE_AREA_0();
   if (col == 7U)
   {
       bitsread = 8U;
       /* read the byte with the MSB */
       tmpval = (uint8)(dataPtr[pos]);

       /* range of col if 0-7, cast to signed char is still in range */
       ssize = ssize - 8;

       while (ssize > 0)
       {
          bitsread = bitsread + 8U;
          ssize = ssize - 8;
          tmpval = (uint32)tmpval << 8U;
          pos = pos - 1;
          tmpval = (uint32)(tmpval | (uint8)(dataPtr[pos]));
       }

       /* read to much, shift back */
       value = (uint16)(tmpval >> (bitsread - Com_EB_ReadPropPtr->ComBitSize));
   }
   else
   {
       /* read the byte with the MSB */
       tmpval = (uint8)(dataPtr[pos]);

       /* range of col if 0-7, cast to signed char is still in range */
       ssize = ssize - 1 - (sint8) col;

       while (ssize > 0)
       {
          bitsread = bitsread + 8U;
          ssize = ssize - 8;
          tmpval = (uint32)tmpval << 8U;
          pos = pos - 1;
          tmpval = (uint32)(tmpval | (uint8)(dataPtr[pos]));
       }

       /* read to much, shift back */
       value = (uint16)(tmpval >> ((col + 1U + bitsread) - (uint8)Com_EB_ReadPropPtr->ComBitSize));
   }

   Com_EB_SchM_Exit_SCHM_COM_EXCLUSIVE_AREA_0();

   /* mask the unused bits */
   {
      uint16 const mask = (uint16)(0xFFFFU >> (16U - Com_EB_ReadPropPtr->ComBitSize));
      value = (uint16)(value & mask);
   }

   *retPtr = value;

   TS_PARAM_UNUSED(retvalPtr);
   return;
} /* Com_EB_Read_16_FUNC(COM_EB_LOCK,COM_EB_ENDIAN) */
#endif

#if (COM_RX_LITTLEENDIAN_ENABLE == STD_ON)
static FUNC(void, COM_CODE) Com_EB_Read_32_EL_1
(
      P2VAR(void, AUTOMATIC, COM_APPL_DATA) SignalDataPtr,
      P2CONST(uint8, AUTOMATIC, COM_VAR_NOINIT) dataPtr,
      P2CONST(ComSignalBaseType, AUTOMATIC, AUTOMATIC) Com_EB_ReadPropPtr,
      P2VAR(uint8, AUTOMATIC, COM_APPL_DATA) retvalPtr
)
{
   /* Deviation MISRAC2012-2 */
   P2VAR (uint32, AUTOMATIC, COM_APPL_DATA) retPtr =
         (P2VAR (uint32, AUTOMATIC, COM_APPL_DATA))SignalDataPtr;

   uint32 value = 0;

   ComSignalDescBitType row = (Com_EB_ReadPropPtr->ComSignalPositionInBit / 8U); /* Starting position of the signals in bits divided by 8 => starting position in byte */
   uint8 col = (uint8)Com_EB_ReadPropPtr->ComSignalPositionInBit % 8U;

   /* Signal position in bit has a maximum value of 2031. */
   sint16 pos = (sint16) row;

   ComSignalBitSizeType size = Com_EB_ReadPropPtr->ComBitSize;

   Com_EB_SchM_Enter_SCHM_COM_EXCLUSIVE_AREA_0();

      if (col != 7U)
      {
         /* data does not start on byte boundary (MSB) */
         uint8 const space = col + 1;
         uint8 const mask = ((uint8) 0xFFU) >> (7U - col);
         uint8 const tmp_val = dataPtr[pos] & mask;
         value = (uint32) tmp_val;

         if (space >= size)
         {
            /* If we've already read as many or more bits than intended */
            value >>= (space - size);
            size = 0U;
         }
         else
         {
            /* prepare to continue reading */
            pos = pos - 1;
            size -= space;
         }
      }

      while (size > 7U)
      {
         /* read whole bytes */
         value <<= 8U;
         value += dataPtr[pos];
         size -= 8U;
         pos = pos - 1;
      }

      if (size > 0U)
      {
         /* read last bits */
         value <<= size;
         value += (uint32) dataPtr[pos] >> (8U - size);
      }

   Com_EB_SchM_Exit_SCHM_COM_EXCLUSIVE_AREA_0();

   *retPtr = value;

   TS_PARAM_UNUSED(retvalPtr);
   return;
} /* Com_EB_Read_32_FUNC(COM_EB_LOCK,COM_EB_ENDIAN) */
#endif

#if ( (COM_RX_LITTLEENDIAN_ENABLE == STD_ON) )
static FUNC(void, COM_CODE) Com_EB_Read_64_EL_1
(
      P2VAR(void, AUTOMATIC, COM_APPL_DATA) SignalDataPtr,
      P2CONST(uint8, AUTOMATIC, COM_VAR_NOINIT) dataPtr,
      P2CONST(ComSignalBaseType, AUTOMATIC, AUTOMATIC) Com_EB_ReadPropPtr,
      P2VAR(uint8, AUTOMATIC, COM_APPL_DATA) retvalPtr
)
{
  P2VAR(ComEmu64Type, AUTOMATIC, AUTOMATIC) SignalDataPtr_loc =
      (P2VAR(ComEmu64Type, AUTOMATIC, COM_APPL_DATA)) SignalDataPtr;

  if(Com_EB_ReadPropPtr->ComBitSize > 32U)
  {
    ComSignalBaseType Com_EB_ReadProp_loc = *Com_EB_ReadPropPtr;

    /* set ComBitSize for higher bytes */
    Com_EB_ReadProp_loc.ComBitSize = Com_EB_ReadPropPtr->ComBitSize - 32U;

    Com_EB_SchM_Enter_SCHM_COM_EXCLUSIVE_AREA_0();

    Com_EB_Read_32_DL_1(
          &SignalDataPtr_loc->HiWord,
          dataPtr,
          &Com_EB_ReadProp_loc,
          retvalPtr);

    /* adapt Com_EB_ReadPropPtr_loc for low 32 bits */
    Com_EB_ReadProp_loc.ComSignalPositionInBit =
        Com_EB_ReadPropPtr->ComSignalPositionInBit - (Com_EB_ReadPropPtr->ComBitSize - 32U);
    Com_EB_ReadProp_loc.ComBitSize = 32U;

    Com_EB_Read_32_DL_1(
          &SignalDataPtr_loc->LoWord,
          dataPtr,
          &Com_EB_ReadProp_loc,
          retvalPtr);

    Com_EB_SchM_Exit_SCHM_COM_EXCLUSIVE_AREA_0();
  }
  else
  {
    Com_EB_Read_32_EL_1(
          &SignalDataPtr_loc->LoWord,
          dataPtr,
          Com_EB_ReadPropPtr,
          retvalPtr);
  }

  TS_PARAM_UNUSED(retvalPtr);
  return;
} /* Com_EB_Read_64_FUNC(COM_EB_LOCK,COM_EB_ENDIAN) */
#endif

static FUNC(void, COM_CODE) Com_EB_Read_AY_EL_1
(
      P2VAR(void, AUTOMATIC, COM_APPL_DATA) SignalDataPtr,
      P2CONST(uint8, AUTOMATIC, COM_VAR_NOINIT) dataPtr,
      P2CONST(ComSignalBaseType, AUTOMATIC, AUTOMATIC) Com_EB_ReadPropPtr,
      P2VAR(uint8, AUTOMATIC, COM_APPL_DATA) retvalPtr
)
{
   uint16 ii = 0U;
   /* Deviation MISRAC2012-2 */
   P2VAR(uint8, AUTOMATIC, COM_APPL_DATA) U8Ptr =
         (P2VAR(uint8, AUTOMATIC, COM_APPL_DATA)) SignalDataPtr;

   Com_EB_SchM_Enter_SCHM_COM_EXCLUSIVE_AREA_0();

   do
   {
      uint16 pos = COM_EB_CONVERT_ENDIAN_RX_POS_NET_E1(Com_EB_ReadPropPtr->ComSignalPositionInBit, Com_EB_ReadPropPtr->ComBitSize, ii);
      U8Ptr[ii] = dataPtr[pos];
      ii++;
   }while (ii < (Com_EB_ReadPropPtr->ComBitSize));

   Com_EB_SchM_Exit_SCHM_COM_EXCLUSIVE_AREA_0();

   TS_PARAM_UNUSED(retvalPtr);
   return;
} /* Com_EB_Read_AY_FUNC(COM_EB_LOCK,COM_EB_ENDIAN) */

#if (COM_RX_BIGENDIAN_ENABLE == STD_ON)
static FUNC(void, COM_CODE) Com_EB_Read_08_EL_2
(
      P2VAR(void, AUTOMATIC, COM_APPL_DATA) SignalDataPtr,
      P2CONST(uint8, AUTOMATIC, COM_VAR_NOINIT) dataPtr,
      P2CONST(ComSignalBaseType, AUTOMATIC, AUTOMATIC) Com_EB_ReadPropPtr,
      P2VAR(uint8, AUTOMATIC, COM_APPL_DATA) retvalPtr
)
{
   /* Deviation MISRAC2012-2 */
   P2VAR (uint8, AUTOMATIC, COM_APPL_DATA) retPtr =
         (P2VAR (uint8, AUTOMATIC, COM_APPL_DATA))SignalDataPtr;

   uint8 value;

   ComSignalDescBitType row = (Com_EB_ReadPropPtr->ComSignalPositionInBit / 8U); /* Starting position of the signals in bits divided by 8 => starting position in byte */
   uint8 col = (uint8)Com_EB_ReadPropPtr->ComSignalPositionInBit % 8U;

   /* Signal position in bit has a maximum value of 2031. */
   sint16 pos = (sint16) row;

   uint16 tmpval;
   const uint8 space = col + 1U;
   uint8 bitsread = 0U;

   if (col == 7U)
   {
       TS_AtomicAssign8(tmpval, dataPtr[pos]);
       /* read to much, shift back */
       value = (uint8)(tmpval >> (8U - Com_EB_ReadPropPtr->ComBitSize));
   }
   else
   {
       /* check number of bytes which shall be read */
       if (space < Com_EB_ReadPropPtr->ComBitSize)
       {
          Com_EB_SchM_Enter_SCHM_COM_EXCLUSIVE_AREA_0();

          tmpval = dataPtr[pos];
          /* another byte has to be read */
          bitsread = bitsread + 8U;
          tmpval = tmpval << 8U;
          pos = pos + 1;
          tmpval = (uint16)(tmpval | (uint8)(dataPtr[pos]));

          Com_EB_SchM_Exit_SCHM_COM_EXCLUSIVE_AREA_0();
       }
       else
       {
          TS_AtomicAssign8(tmpval, dataPtr[pos]);
       }

       /* read to much, shift back */
       value = (uint8)(tmpval >> ((col + 1U + bitsread) - (uint8)Com_EB_ReadPropPtr->ComBitSize));
   }


   /* mask the unused bits */
   {
      uint8 const mask = (uint8)(0xFFU >> (8U - Com_EB_ReadPropPtr->ComBitSize));
      value = (uint8)(value & mask);
   }

   *retPtr = value;

   TS_PARAM_UNUSED(retvalPtr);
   return;
} /* Com_EB_Read_08_FUNC(COM_EB_LOCK,COM_EB_ENDIAN) */
#endif

#if (COM_RX_BIGENDIAN_ENABLE == STD_ON)
static FUNC(void, COM_CODE) Com_EB_Read_16_EL_2
(
      P2VAR(void, AUTOMATIC, COM_APPL_DATA) SignalDataPtr,
      P2CONST(uint8, AUTOMATIC, COM_VAR_NOINIT) dataPtr,
      P2CONST(ComSignalBaseType, AUTOMATIC, AUTOMATIC) Com_EB_ReadPropPtr,
      P2VAR(uint8, AUTOMATIC, COM_APPL_DATA) retvalPtr
)
{
   /* Deviation MISRAC2012-2 */
   P2VAR (uint16, AUTOMATIC, COM_APPL_DATA) retPtr =
         (P2VAR (uint16, AUTOMATIC, COM_APPL_DATA))SignalDataPtr;

   uint16 value;

   uint8 bitsread = 0U;

   sint8 ssize = (sint8)Com_EB_ReadPropPtr->ComBitSize;

   uint32 tmpval;

   ComSignalDescBitType row = (Com_EB_ReadPropPtr->ComSignalPositionInBit / 8U); /* Starting position of the signals in bits divided by 8 => starting position in byte */
   uint8 col = (uint8)Com_EB_ReadPropPtr->ComSignalPositionInBit % 8U;

   /* Signal position in bit has a maximum value of 2031. */
   sint16 pos = (sint16) row;

   Com_EB_SchM_Enter_SCHM_COM_EXCLUSIVE_AREA_0();

   if (col == 7U)
   {
       bitsread = 8U;
       /* read the byte with the MSB */
       tmpval = (uint8)(dataPtr[pos]);

       /* range of col if 0-7, cast to signed char is still in range */
       ssize = ssize - 8;

       while (ssize > 0)
       {
          bitsread = bitsread + 8U;
          ssize = ssize - 8;
          tmpval = (uint32)tmpval << 8U;
          pos = pos + 1;
          tmpval = (uint32)(tmpval | (uint8)(dataPtr[pos]));
       }

       /* read to much, shift back */
       value = (uint16)(tmpval >> (bitsread - Com_EB_ReadPropPtr->ComBitSize));
   }
   else
   {
       /* read the byte with the MSB */
       tmpval = (uint8)(dataPtr[pos]);

       /* range of col if 0-7, cast to signed char is still in range */
       ssize = ssize - 1 - (sint8) col;

       while (ssize > 0)
       {
          bitsread = bitsread + 8U;
          ssize = ssize - 8;
          tmpval = (uint32)tmpval << 8U;
          pos = pos + 1;
          tmpval = (uint32)(tmpval | (uint8)(dataPtr[pos]));
       }

       /* read to much, shift back */
       value = (uint16)(tmpval >> ((col + 1U + bitsread) - (uint8)Com_EB_ReadPropPtr->ComBitSize));
   }

   Com_EB_SchM_Exit_SCHM_COM_EXCLUSIVE_AREA_0();

   /* mask the unused bits */
   {
      uint16 const mask = (uint16)(0xFFFFU >> (16U - Com_EB_ReadPropPtr->ComBitSize));
      value = (uint16)(value & mask);
   }

   *retPtr = value;

   TS_PARAM_UNUSED(retvalPtr);
   return;
} /* Com_EB_Read_16_FUNC(COM_EB_LOCK,COM_EB_ENDIAN) */
#endif

#if (COM_RX_BIGENDIAN_ENABLE == STD_ON)
static FUNC(void, COM_CODE) Com_EB_Read_32_EL_2
(
      P2VAR(void, AUTOMATIC, COM_APPL_DATA) SignalDataPtr,
      P2CONST(uint8, AUTOMATIC, COM_VAR_NOINIT) dataPtr,
      P2CONST(ComSignalBaseType, AUTOMATIC, AUTOMATIC) Com_EB_ReadPropPtr,
      P2VAR(uint8, AUTOMATIC, COM_APPL_DATA) retvalPtr
)
{
   /* Deviation MISRAC2012-2 */
   P2VAR (uint32, AUTOMATIC, COM_APPL_DATA) retPtr =
         (P2VAR (uint32, AUTOMATIC, COM_APPL_DATA))SignalDataPtr;

   uint32 value = 0;

   ComSignalDescBitType row = (Com_EB_ReadPropPtr->ComSignalPositionInBit / 8U); /* Starting position of the signals in bits divided by 8 => starting position in byte */
   uint8 col = (uint8)Com_EB_ReadPropPtr->ComSignalPositionInBit % 8U;

   /* Signal position in bit has a maximum value of 2031. */
   sint16 pos = (sint16) row;

   ComSignalBitSizeType size = Com_EB_ReadPropPtr->ComBitSize;

   Com_EB_SchM_Enter_SCHM_COM_EXCLUSIVE_AREA_0();

      if (col != 7U)
      {
         /* data does not start on byte boundary (MSB) */
         uint8 const space = col + 1;
         uint8 const mask = ((uint8) 0xFFU) >> (7U - col);
         uint8 const tmp_val = dataPtr[pos] & mask;
         value = (uint32) tmp_val;

         if (space >= size)
         {
            /* If we've already read as many or more bits than intended */
            value >>= (space - size);
            size = 0U;
         }
         else
         {
            /* prepare to continue reading */
            pos = pos + 1;
            size -= space;
         }
      }

      while (size > 7U)
      {
         /* read whole bytes */
         value <<= 8U;
         value += dataPtr[pos];
         size -= 8U;
         pos = pos + 1;
      }

      if (size > 0U)
      {
         /* read last bits */
         value <<= size;
         value += (uint32) dataPtr[pos] >> (8U - size);
      }

   Com_EB_SchM_Exit_SCHM_COM_EXCLUSIVE_AREA_0();

   *retPtr = value;

   TS_PARAM_UNUSED(retvalPtr);
   return;
} /* Com_EB_Read_32_FUNC(COM_EB_LOCK,COM_EB_ENDIAN) */
#endif

#if ( (COM_RX_BIGENDIAN_ENABLE == STD_ON) )
static FUNC(void, COM_CODE) Com_EB_Read_64_EL_2
(
      P2VAR(void, AUTOMATIC, COM_APPL_DATA) SignalDataPtr,
      P2CONST(uint8, AUTOMATIC, COM_VAR_NOINIT) dataPtr,
      P2CONST(ComSignalBaseType, AUTOMATIC, AUTOMATIC) Com_EB_ReadPropPtr,
      P2VAR(uint8, AUTOMATIC, COM_APPL_DATA) retvalPtr
)
{
  P2VAR(ComEmu64Type, AUTOMATIC, AUTOMATIC) SignalDataPtr_loc =
      (P2VAR(ComEmu64Type, AUTOMATIC, COM_APPL_DATA)) SignalDataPtr;

  if(Com_EB_ReadPropPtr->ComBitSize > 32U)
  {
    ComSignalBaseType Com_EB_ReadProp_loc = *Com_EB_ReadPropPtr;

    /* set ComBitSize for higher bytes */
    Com_EB_ReadProp_loc.ComBitSize = Com_EB_ReadPropPtr->ComBitSize - 32U;

    Com_EB_SchM_Enter_SCHM_COM_EXCLUSIVE_AREA_0();

    Com_EB_Read_32_DL_2(
          &SignalDataPtr_loc->HiWord,
          dataPtr,
          &Com_EB_ReadProp_loc,
          retvalPtr);

    /* adapt Com_EB_ReadPropPtr_loc for low 32 bits */
    Com_EB_ReadProp_loc.ComSignalPositionInBit =
        Com_EB_ReadPropPtr->ComSignalPositionInBit + (Com_EB_ReadPropPtr->ComBitSize - 32U);
    Com_EB_ReadProp_loc.ComBitSize = 32U;

    Com_EB_Read_32_DL_2(
          &SignalDataPtr_loc->LoWord,
          dataPtr,
          &Com_EB_ReadProp_loc,
          retvalPtr);

    Com_EB_SchM_Exit_SCHM_COM_EXCLUSIVE_AREA_0();
  }
  else
  {
    Com_EB_Read_32_EL_2(
          &SignalDataPtr_loc->LoWord,
          dataPtr,
          Com_EB_ReadPropPtr,
          retvalPtr);
  }

  TS_PARAM_UNUSED(retvalPtr);
  return;
} /* Com_EB_Read_64_FUNC(COM_EB_LOCK,COM_EB_ENDIAN) */
#endif

static FUNC(void, COM_CODE) Com_EB_Read_AY_EL_2
(
      P2VAR(void, AUTOMATIC, COM_APPL_DATA) SignalDataPtr,
      P2CONST(uint8, AUTOMATIC, COM_VAR_NOINIT) dataPtr,
      P2CONST(ComSignalBaseType, AUTOMATIC, AUTOMATIC) Com_EB_ReadPropPtr,
      P2VAR(uint8, AUTOMATIC, COM_APPL_DATA) retvalPtr
)
{
   uint16 ii = 0U;
   /* Deviation MISRAC2012-2 */
   P2VAR(uint8, AUTOMATIC, COM_APPL_DATA) U8Ptr =
         (P2VAR(uint8, AUTOMATIC, COM_APPL_DATA)) SignalDataPtr;

   Com_EB_SchM_Enter_SCHM_COM_EXCLUSIVE_AREA_0();

   do
   {
      uint16 pos = COM_EB_CONVERT_ENDIAN_RX_POS_NET_E2(Com_EB_ReadPropPtr->ComSignalPositionInBit, Com_EB_ReadPropPtr->ComBitSize, ii);
      U8Ptr[ii] = dataPtr[pos];
      ii++;
   }while (ii < (Com_EB_ReadPropPtr->ComBitSize));

   Com_EB_SchM_Exit_SCHM_COM_EXCLUSIVE_AREA_0();

   TS_PARAM_UNUSED(retvalPtr);
   return;
} /* Com_EB_Read_AY_FUNC(COM_EB_LOCK,COM_EB_ENDIAN) */

static FUNC(void, COM_CODE) Com_EB_Read_AY_DL_3
(
   P2VAR(void, AUTOMATIC, COM_APPL_DATA) SignalDataPtr,
   P2CONST(uint8, AUTOMATIC, COM_VAR_NOINIT) dataPtr,
   P2CONST(ComSignalBaseType, AUTOMATIC, AUTOMATIC) Com_EB_ReadPropPtr,
   P2VAR(uint8, AUTOMATIC, COM_APPL_DATA) retvalPtr
)
{

   ComSignalDescBitType startbyte =
         Com_EB_ReadPropPtr->ComSignalPositionInBit;

   CONSTP2CONST(uint8, AUTOMATIC, COM_VAR_NOINIT) valPtr =
         &dataPtr[startbyte];

   /* copy the data from the Pdu */
   TS_MemCpy(SignalDataPtr,
      valPtr,
      Com_EB_ReadPropPtr->ComBitSize);

   TS_PARAM_UNUSED(retvalPtr);
   return;
}

static FUNC(void, COM_CODE) Com_EB_Read_AY_EL_3
(
   P2VAR(void, AUTOMATIC, COM_APPL_DATA) SignalDataPtr,
   P2CONST(uint8, AUTOMATIC, COM_VAR_NOINIT) dataPtr,
   P2CONST(ComSignalBaseType, AUTOMATIC, AUTOMATIC) Com_EB_ReadPropPtr,
   P2VAR(uint8, AUTOMATIC, COM_APPL_DATA) retvalPtr
)
{
   ComSignalDescBitType startbyte =
         Com_EB_ReadPropPtr->ComSignalPositionInBit;

   CONSTP2CONST(uint8, AUTOMATIC, COM_VAR_NOINIT) valPtr =
         &dataPtr[startbyte];

   /* Enter critical section */
   Com_EB_SchM_Enter_SCHM_COM_EXCLUSIVE_AREA_0();

   /* copy the data from the Pdu */
   TS_MemCpy(SignalDataPtr,
      valPtr,
      Com_EB_ReadPropPtr->ComBitSize);

   /* Leave critical section */
   Com_EB_SchM_Exit_SCHM_COM_EXCLUSIVE_AREA_0();

   TS_PARAM_UNUSED(retvalPtr);
   return;
}

static FUNC(void, COM_CODE) Com_EB_Read_08_DL_SignExt
(
   P2VAR(void, AUTOMATIC, COM_APPL_DATA) SignalDataPtr,
   P2CONST(uint8, AUTOMATIC, COM_VAR_NOINIT) dataPtr,
   P2CONST(ComSignalBaseType, AUTOMATIC, AUTOMATIC) Com_EB_ReadPropPtr,
   P2VAR(uint8, AUTOMATIC, COM_APPL_DATA) retvalPtr
)
{
   /* Deviation MISRAC2012-2 */
   P2VAR(uint8, AUTOMATIC, COM_APPL_DATA) SignalDataPtrU8 =
         (P2VAR(uint8, AUTOMATIC, COM_APPL_DATA)) SignalDataPtr;

   Com_EB_Read_Core_NoLock_NoSign(SignalDataPtr, dataPtr, Com_EB_ReadPropPtr, retvalPtr);

   {
      /* Deviation MISRAC2012-1 */
      boolean const MSB = (boolean)((*SignalDataPtrU8) >> (Com_EB_ReadPropPtr->ComBitSize - 1U));
      if (MSB != 0U)
      {
         uint8 const sigExtMask  = (uint8)(0xFFU << (Com_EB_ReadPropPtr->ComBitSize - 1U));
         (*SignalDataPtrU8) = (uint8)((*SignalDataPtrU8) | sigExtMask );
      }
   }

   TS_PARAM_UNUSED(retvalPtr);
   return;
}

static FUNC(void, COM_CODE) Com_EB_Read_08_EL_SignExt
(
   P2VAR(void, AUTOMATIC, COM_APPL_DATA) SignalDataPtr,
   P2CONST(uint8, AUTOMATIC, COM_VAR_NOINIT) dataPtr,
   P2CONST(ComSignalBaseType, AUTOMATIC, AUTOMATIC) Com_EB_ReadPropPtr,
   P2VAR(uint8, AUTOMATIC, COM_APPL_DATA) retvalPtr
)
{
   /* Deviation MISRAC2012-2 */
   P2VAR(uint8, AUTOMATIC, COM_APPL_DATA) SignalDataPtrU8 =
         (P2VAR(uint8, AUTOMATIC, COM_APPL_DATA)) SignalDataPtr;

   Com_EB_Read_Core_NoSign(SignalDataPtr, dataPtr, Com_EB_ReadPropPtr, retvalPtr);

   {
      /* Deviation MISRAC2012-1 */
      boolean const MSB = (boolean)((*SignalDataPtrU8) >> (Com_EB_ReadPropPtr->ComBitSize - 1U));
      if (MSB != 0U)
      {
         uint8 const sigExtMask  = (uint8)(0xFFU << (Com_EB_ReadPropPtr->ComBitSize - 1U));
         (*SignalDataPtrU8) = (uint8)((*SignalDataPtrU8) | sigExtMask );
      }
   }

   TS_PARAM_UNUSED(retvalPtr);
   return;
}

static FUNC(void, COM_CODE) Com_EB_Read_16_DL_SignExt
(
   P2VAR(void, AUTOMATIC, COM_APPL_DATA) SignalDataPtr,
   P2CONST(uint8, AUTOMATIC, COM_VAR_NOINIT) dataPtr,
   P2CONST(ComSignalBaseType, AUTOMATIC, AUTOMATIC) Com_EB_ReadPropPtr,
   P2VAR(uint8, AUTOMATIC, COM_APPL_DATA) retvalPtr
)
{
   /* Deviation MISRAC2012-2 */
   P2VAR(uint16, AUTOMATIC, COM_APPL_DATA) SignalDataPtrU16 =
         (P2VAR(uint16, AUTOMATIC, COM_APPL_DATA)) SignalDataPtr;

   Com_EB_Read_Core_NoLock_NoSign(SignalDataPtr, dataPtr, Com_EB_ReadPropPtr, retvalPtr);

   {
      /* Deviation MISRAC2012-1 */
      boolean const MSB = (boolean)((*SignalDataPtrU16) >> (Com_EB_ReadPropPtr->ComBitSize - 1U));
      if (MSB != 0U)
      {
         uint16 const sigExtMask  = (uint16)(0xFFFFU << (Com_EB_ReadPropPtr->ComBitSize - 1U));
         (*SignalDataPtrU16) = (uint16)((*SignalDataPtrU16) | sigExtMask );
      }
   }

   TS_PARAM_UNUSED(retvalPtr);
   return;
}

static FUNC(void, COM_CODE) Com_EB_Read_16_EL_SignExt
(
   P2VAR(void, AUTOMATIC, COM_APPL_DATA) SignalDataPtr,
   P2CONST(uint8, AUTOMATIC, COM_VAR_NOINIT) dataPtr,
   P2CONST(ComSignalBaseType, AUTOMATIC, AUTOMATIC) Com_EB_ReadPropPtr,
   P2VAR(uint8, AUTOMATIC, COM_APPL_DATA) retvalPtr
)
{
   /* Deviation MISRAC2012-2 */
   P2VAR(uint16, AUTOMATIC, COM_APPL_DATA) SignalDataPtrU16 =
         (P2VAR(uint16, AUTOMATIC, COM_APPL_DATA)) SignalDataPtr;

   Com_EB_Read_Core_NoSign(SignalDataPtr, dataPtr, Com_EB_ReadPropPtr, retvalPtr);

   {
      /* Deviation MISRAC2012-1 */
      boolean const MSB = (boolean)((*SignalDataPtrU16) >> (Com_EB_ReadPropPtr->ComBitSize - 1U));
      if (MSB != 0U)
      {
         uint16 const sigExtMask  = (uint16)(0xFFFFU << (Com_EB_ReadPropPtr->ComBitSize - 1U));
         (*SignalDataPtrU16) = (uint16)((*SignalDataPtrU16) | sigExtMask );
      }
   }

   TS_PARAM_UNUSED(retvalPtr);
   return;
}

static FUNC(void, COM_CODE) Com_EB_Read_32_DL_SignExt
(
   P2VAR(void, AUTOMATIC, COM_APPL_DATA) SignalDataPtr,
   P2CONST(uint8, AUTOMATIC, COM_VAR_NOINIT) dataPtr,
   P2CONST(ComSignalBaseType, AUTOMATIC, AUTOMATIC) Com_EB_ReadPropPtr,
   P2VAR(uint8, AUTOMATIC, COM_APPL_DATA) retvalPtr
)
{
   /* Deviation MISRAC2012-2 */
   P2VAR(uint32, AUTOMATIC, COM_APPL_DATA) SignalDataPtrU32 =
         (P2VAR(uint32, AUTOMATIC, COM_APPL_DATA)) SignalDataPtr;

   Com_EB_Read_Core_NoLock_NoSign(SignalDataPtr, dataPtr, Com_EB_ReadPropPtr, retvalPtr);

   {
      /* Deviation MISRAC2012-1 */
      boolean const MSB = (boolean)((*SignalDataPtrU32) >> (Com_EB_ReadPropPtr->ComBitSize - 1U));
      if (MSB != 0U)
      {
         uint32 const sigExtMask  = (uint32)(0xFFFFFFFFUL << (Com_EB_ReadPropPtr->ComBitSize - 1U));
         (*SignalDataPtrU32) = (uint32)((*SignalDataPtrU32) | sigExtMask );
      }
   }

   TS_PARAM_UNUSED(retvalPtr);
   return;
}

static FUNC(void, COM_CODE) Com_EB_Read_32_EL_SignExt
(
   P2VAR(void, AUTOMATIC, COM_APPL_DATA) SignalDataPtr,
   P2CONST(uint8, AUTOMATIC, COM_VAR_NOINIT) dataPtr,
   P2CONST(ComSignalBaseType, AUTOMATIC, AUTOMATIC) Com_EB_ReadPropPtr,
   P2VAR(uint8, AUTOMATIC, COM_APPL_DATA) retvalPtr
)
{
   /* Deviation MISRAC2012-2 */
   P2VAR(uint32, AUTOMATIC, COM_APPL_DATA) SignalDataPtrU32 =
         (P2VAR(uint32, AUTOMATIC, COM_APPL_DATA)) SignalDataPtr;

   Com_EB_Read_Core_NoSign(SignalDataPtr, dataPtr, Com_EB_ReadPropPtr, retvalPtr);

   {
      /* Deviation MISRAC2012-1 */
      boolean const MSB = (boolean)((*SignalDataPtrU32) >> (Com_EB_ReadPropPtr->ComBitSize - 1U));
      if (MSB != 0U)
      {
         uint32 const sigExtMask  = (uint32)(0xFFFFFFFFUL << (Com_EB_ReadPropPtr->ComBitSize - 1U));
         (*SignalDataPtrU32) = (uint32)((*SignalDataPtrU32) | sigExtMask );
      }
   }

   TS_PARAM_UNUSED(retvalPtr);
   return;
}

static FUNC(void, COM_CODE) Com_EB_Read_BO_DL
(
   P2VAR(void, AUTOMATIC, COM_APPL_DATA) SignalDataPtr,
   P2CONST(uint8, AUTOMATIC, COM_VAR_NOINIT) dataPtr,
   P2CONST(ComSignalBaseType, AUTOMATIC, AUTOMATIC) Com_EB_ReadPropPtr,
   P2VAR(uint8, AUTOMATIC, COM_APPL_DATA) retvalPtr
)
{
   /* Deviation MISRAC2012-2 */
   P2VAR(boolean, AUTOMATIC, COM_APPL_DATA) SignalDataPtrBool =
         (P2VAR(boolean, AUTOMATIC, COM_APPL_DATA)) SignalDataPtr;

   uint16 const pos = Com_EB_ReadPropPtr->ComSignalPositionInBit / 8U;
   uint8 const bit = (uint8) Com_EB_ReadPropPtr->ComSignalPositionInBit % 8U;

   *SignalDataPtrBool = Com_IsBitSet_8(&dataPtr[pos], bit);

   TS_PARAM_UNUSED(retvalPtr);
   return;
}

static FUNC(void, COM_CODE) Com_EB_Read_A1_DL
(
   P2VAR(void, AUTOMATIC, COM_APPL_DATA) SignalDataPtr,
   P2CONST(uint8, AUTOMATIC, COM_VAR_NOINIT) dataPtr,
   P2CONST(ComSignalBaseType, AUTOMATIC, AUTOMATIC) Com_EB_ReadPropPtr,
   P2VAR(uint8, AUTOMATIC, COM_APPL_DATA) retvalPtr
)
{
   /* Deviation MISRAC2012-2 */
   P2VAR(uint8, AUTOMATIC, COM_APPL_DATA) SignalDataPtrU8 =
         (P2VAR(uint8, AUTOMATIC, COM_APPL_DATA)) SignalDataPtr;

   uint16 const pos = Com_EB_ReadPropPtr->ComSignalPositionInBit;

   ((*SignalDataPtrU8) = (dataPtr[pos]));

   TS_PARAM_UNUSED(retvalPtr);
   return;
}

static FUNC(void, COM_CODE) Com_EB_Read_BO_EL
(
   P2VAR(void, AUTOMATIC, COM_APPL_DATA) SignalDataPtr,
   P2CONST(uint8, AUTOMATIC, COM_VAR_NOINIT) dataPtr,
   P2CONST(ComSignalBaseType, AUTOMATIC, AUTOMATIC) Com_EB_ReadPropPtr,
   P2VAR(uint8, AUTOMATIC, COM_APPL_DATA) retvalPtr
)
{
   /* Deviation MISRAC2012-2 */
   P2VAR(boolean, AUTOMATIC, COM_APPL_DATA) SignalDataPtrBool =
         (P2VAR(boolean, AUTOMATIC, COM_APPL_DATA)) SignalDataPtr;

   uint16 const pos = Com_EB_ReadPropPtr->ComSignalPositionInBit / 8U;
   uint8 const bit = (uint8) Com_EB_ReadPropPtr->ComSignalPositionInBit % 8U;

   *SignalDataPtrBool = Com_IsBitSet_8(&dataPtr[pos],bit);

   TS_PARAM_UNUSED(retvalPtr);
   return;
}

static FUNC(void, COM_CODE) Com_EB_Read_A1_EL
(
   P2VAR(void, AUTOMATIC, COM_APPL_DATA) SignalDataPtr,
   P2CONST(uint8, AUTOMATIC, COM_VAR_NOINIT) dataPtr,
   P2CONST(ComSignalBaseType, AUTOMATIC, AUTOMATIC) Com_EB_ReadPropPtr,
   P2VAR(uint8, AUTOMATIC, COM_APPL_DATA) retvalPtr
)
{
   /* Deviation MISRAC2012-2 */
   P2VAR(uint8, AUTOMATIC, COM_APPL_DATA) SignalDataPtrU8 =
         (P2VAR(uint8, AUTOMATIC, COM_APPL_DATA)) SignalDataPtr;

   uint16 const pos = Com_EB_ReadPropPtr->ComSignalPositionInBit;

   TS_AtomicAssign8(*SignalDataPtrU8, dataPtr[pos]);

   TS_PARAM_UNUSED(retvalPtr);
   return;
}

static FUNC(void, COM_CODE) Com_EB_Read_DET
(
      P2VAR(void, AUTOMATIC, COM_APPL_DATA) SignalDataPtr,
      P2CONST(uint8, AUTOMATIC, COM_VAR_NOINIT) dataPtr,
      P2CONST(ComSignalBaseType, AUTOMATIC, AUTOMATIC) Com_EB_ReadPropPtr,
      P2VAR(uint8, AUTOMATIC, COM_APPL_DATA) retvalPtr
)
{
#if (COM_DEV_ERROR_DETECT == STD_ON)

     COM_DET_REPORTERROR(COM_E_PARAM_POINTER, COM_INTERNAL_API_ID);

#endif /* COM_DEV_ERROR_DETECT */

#if (COM_PRECONDITION_ASSERT_ENABLED == STD_ON)
   if(retvalPtr != NULL_PTR)
#endif /* (COM_PRECONDITION_ASSERT_ENABLED == STD_ON) */
   {
     *retvalPtr = COM_SERVICE_NOT_AVAILABLE;
   }

   TS_PARAM_UNUSED(SignalDataPtr);
   TS_PARAM_UNUSED(dataPtr);
   TS_PARAM_UNUSED(Com_EB_ReadPropPtr);

   return;
}

#define COM_STOP_SEC_CODE
#include <Com_MemMap.h>

/*==================[end of file]============================================*/

