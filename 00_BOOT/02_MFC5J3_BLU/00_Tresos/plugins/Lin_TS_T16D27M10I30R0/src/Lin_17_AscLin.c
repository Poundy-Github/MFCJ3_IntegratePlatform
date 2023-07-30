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
**  FILENAME     : Lin_17_AscLin.c                                            **
**                                                                            **
**  VERSION      : 1.30.0_14.0.0                                              **
**                                                                            **
**  DATE         : 2019-10-17                                                 **
**                                                                            **
**  VARIANT      : Variant PB                                                 **
**                                                                            **
**  PLATFORM     : Infineon AURIX2G                                           **
**                                                                            **
**  AUTHOR       : DL-AUTOSAR-Engineering                                     **
**                                                                            **
**  VENDOR       : Infineon Technologies                                      **
**                                                                            **
**  DESCRIPTION  : Lin Driver source file                                     **
**                                                                            **
**  SPECIFICATION(S) : Specification of Lin Driver, AUTOSAR Release 4.2.2     **
**                                                                            **
**  MAY BE CHANGED BY USER : no                                               **
**                                                                            **
*******************************************************************************/
/*******************************************************************************
**                      Include Section                                       **
*******************************************************************************/
/*[cover parentID={A6441ED2-CF72-40f9-B26D-BD0C8B9BBA95}][/cover]*/

/*[cover parentID={8302A971-6646-47d4-A47F-7928F4305FE5}][/cover]*/
/* Inclusion of ASCLIN Register structure header file */

/*[cover parentID={F8C4D3E6-63EA-4c56-BA03-7DB3B44D5C20}] Lin_17_AscLin_Irq.c
File to be developed by user [/cover] */

#include "IfxAsclin_reg.h"

/* Inclusion of SRC Register structure header file */
#include "IfxSrc_reg.h"

/* Global functions like Set/Reset END INIT protection bit,
  Enable/Disable interrupts, Automic write function */
#include "McalLib.h"

/* Own header file, this includes own configuration file also */
#include "Lin_17_AscLin.h"

#include "LinIf_Cbk.h"

#include "IfxAscLin_bf.h"

#if(LIN_17_ASCLIN_INIT_DEINIT_API_MODE != LIN_17_ASCLIN_MCAL_SUPERVISOR_MODE)
#include "McalLib_OsStub.h"
#endif


/* Conditional Inclusion of Developement Error Tracer File */
#if (LIN_17_ASCLIN_DEV_ERROR_DETECT == STD_ON)
#include "Det.h"
#endif /* (LIN_17_ASCLIN_DEV_ERROR_DETECT == STD_ON) */


/*******************************************************************************
**                      Imported Compiler Switch Check                        **
*******************************************************************************/

/* Version checks */

#ifndef LIN_17_ASCLIN_SW_MAJOR_VERSION
  #error "LIN_17_ASCLIN_SW_MAJOR_VERSION is not defined. "
#endif

#ifndef LIN_17_ASCLIN_SW_MINOR_VERSION
  #error "LIN_17_ASCLIN_SW_MINOR_VERSION is not defined. "
#endif

#ifndef LIN_17_ASCLIN_SW_PATCH_VERSION
  #error "LIN_17_ASCLIN_SW_PATCH_VERSION is not defined."
#endif

/* Check for Correct inclusion of headers */
#if ( LIN_17_ASCLIN_SW_MAJOR_VERSION != 10U )
  #error "LIN_17_ASCLIN_SW_MAJOR_VERSION does not match. "
#endif
#if ( LIN_17_ASCLIN_SW_MINOR_VERSION != 30U )
  #error "LIN_17_ASCLIN_SW_MINOR_VERSION does not match. "
#endif

#if ( LIN_17_ASCLIN_SW_PATCH_VERSION != 1U )
  #error "LIN_17_ASCLIN_SW_PATCH_VERSION does not match."
#endif

#ifndef LIN_17_ASCLIN_AR_RELEASE_MAJOR_VERSION
  #error "LIN_17_ASCLIN_AR_RELEASE_MAJOR_VERSION is not defined."
#endif


/*[cover parentID={0769BB51-2DA6-4bd2-A73E-9FDBFAB30329}] Modules version
consistency check [/cover]*/
#if ( LIN_17_ASCLIN_AR_RELEASE_MAJOR_VERSION != 4U)
  #error "LIN_17_ASCLIN_AR_RELEASE_MAJOR_VERSION does not match."
#endif

#if (LIN_17_ASCLIN_DEV_ERROR_DETECT == STD_ON)

#ifndef DET_AR_RELEASE_MAJOR_VERSION
#error "DET_AR_RELEASE_MAJOR_VERSION is not defined."
#endif

/* [cover parentID={F090B58A-D80C-4b1a-8EA2-3880C205B571}]
    [/cover] */
#if (DET_AR_RELEASE_MAJOR_VERSION != 4U)
   #error "DET_AR_RELEASE_MAJOR_VERSION does not match."
#endif

#endif
/* End for LIN_17_ASCLIN_DEV_ERROR_DETECT */

/*******************************************************************************
**                      Private Object Like Macro Definitions                 **
*******************************************************************************/

#define LIN_17_ASCLIN_FRAMECON_INIT_MODE (0U)/* ASCLIN INIT mode */
#define LIN_17_ASCLIN_FRAMECONREG_LIN_MODE (3U) /* ASCLIN LIN mode */
#define LIN_17_ASCLIN_FRAMECONREG_PEN_VAL (0U) /* Disable Parity */
#define LIN_17_ASCLIN_FRAMECONREG_CEN_VAL (1U) /* Collision detection enable */
#define LIN_17_ASCLIN_FRAMECONREG_STOP_VAL (1U) /* 1 stop bit */
#define LIN_17_ASCLIN_FRAMECONREG_LEAD_VAL (2U) /* 1 bit Lead value */

#define LIN_17_ASCLIN_BITCONREG_OS_VAL (15U) /* Oversampling value = 15X */
#define LIN_17_ASCLIN_BITCONREG_SM_VAL (1U) /* Sample Mode = 3 bit */
#define LIN_17_ASCLIN_BITCON_SP_VAL (9U) /* Sample point = 9 */

#define LIN_17_ASCLIN_IOCRREG_DEPTH_VAL (0U) /*digital Glitch Filter Disabled*/

#define LIN_17_ASCLIN_LINCONREG_CSEN_VAL (1U) /* Hw Checksum Enable  */
#define LIN_17_ASCLIN_LINCON_MASTER_ENABLE (1U) /* Enable LIN as Master */
/* Checksum injection to Rxfifo disabled */
#define LIN_17_ASCLIN_LINCONREG_CSI_VAL (0U)  /* Checksum injection disable */

#define LIN_17_ASCLIN_LINBTIMER_BREAK_VAL (14U) /* Break = 13 bit/s */
#define LIN_17_ASCLIN_LINHTIMER_HEADER_VAL (48U) /* Header Timeout = 48 bits */

#define LIN_17_ASCLIN_TXFIFOCONREG_INW_VAL (1U) /* Inlet valve width = 1 byte */
#define LIN_17_ASCLIN_RXFIFOCON_OUTW_VAL (1U) /* Outlet valve width = 1 byte */
#define LIN_17_ASCLIN_CSRREG_CLKSEL_NOCLK (0U) /* No Clock  */


/* AscLin Error Flags */
/* Framing Error */
#define LIN_17_ASCLIN_FLAGSREG_FE ((uint32)0x1 << IFX_ASCLIN_FLAGS_FE_OFF)
/* Header Timeout */
#define LIN_17_ASCLIN_FLAGSREG_HT ((uint32)0x1 << IFX_ASCLIN_FLAGS_HT_OFF)
/* Response Timeout */
#define LIN_17_ASCLIN_FLAGSREG_RT ((uint32)0x1 << IFX_ASCLIN_FLAGS_RT_OFF)
/* ID Parity Error */
#define LIN_17_ASCLIN_FLAGSREG_LP ((uint32)0x1 << IFX_ASCLIN_FLAGS_LP_OFF)
/* Checksum Error */
#define LIN_17_ASCLIN_FLAGSREG_LC ((uint32)0x1 << IFX_ASCLIN_FLAGS_LC_OFF)
/* Collision detected */
#define LIN_17_ASCLIN_FLAGSREG_CE ((uint32)0x1 << IFX_ASCLIN_FLAGS_CE_OFF)
/* Rx Fifo overflow */
#define LIN_17_ASCLIN_FLAGSREG_RFO ((uint32)0x1 << IFX_ASCLIN_FLAGS_RFO_OFF)
/* Rx Fifo underflow */
#define LIN_17_ASCLIN_FLAGSREG_RFU ((uint32)0x1 << IFX_ASCLIN_FLAGS_RFU_OFF)
/* Tx Fifo overflow */
#define LIN_17_ASCLIN_FLAGSREG_TFO ((uint32)0x1 << IFX_ASCLIN_FLAGS_TFO_OFF)
/* Tx Fifo Underflow */
#define LIN_17_ASCLIN_FLAGSREG_TC ((uint32)0x1 << IFX_ASCLIN_FLAGS_TC_OFF)

#if (LIN_17_ASCLIN_INTERRUPT_DISABLED == STD_OFF)
/* Falling edge detect */
#define LIN_17_ASCLIN_FLAGSREG_FED ((uint32)0x1 << IFX_ASCLIN_FLAGS_FED_OFF)
#endif

/* AscLin Status Flags */
/* Transmit header Completed */
#define LIN_17_ASCLIN_FLAGSREG_TH ((uint32)0x1 << IFX_ASCLIN_FLAGS_TH_OFF)
/* Transmit Response Completed */
#define LIN_17_ASCLIN_FLAGSREG_TR ((uint32)0x1 << IFX_ASCLIN_FLAGS_TR_OFF)
/* Receive Response completed  */
#define LIN_17_ASCLIN_FLAGSREG_RR ((uint32)0x1 << IFX_ASCLIN_FLAGS_RR_OFF)

/* Mask for PID to remove Parity bits */
#define LIN_17_ASCLIN_PID_MASK_WO_PARITY (0x3FU)
/* Mask to Clear All register Flags */
#define LIN_17_ASCLIN_FLAGSCLEAR_VAL (0xDFFFE06FU)

/* RXFIFO fill value when only ID is recieved */
#define LIN_17_ASCLIN_RXFIFOVAL_IDONLY (1U)

#define LIN_17_ASCLIN_ENABLE_FLAG (1U)
#define LIN_17_ASCLIN_DISABLE_FLAG (0U)
#define LIN_17_ASCLIN_SLEEPCMD_DL (8U)
#define LIN_17_ASCLIN_SLEEPCMD_PID (60U)
#define LIN_17_ASCLIN_SLEEPCMD_DATA0 (0x00U)
#define LIN_17_ASCLIN_SLEEPCMD_DATA1TO7 (0xFFU)
#define LIN_17_ASCLIN_SLEEPCMD_DATLEN (8U)

#define LIN_17_ASCLIN_NUMBER_ONE  (1U)
#define LIN_17_ASCLIN_NUMBER_ZERO (0U)

/* Header Timeout Error */
#define LIN_17_ASCLIN_HEADER_TIMEOUT_ERR (LIN_17_ASCLIN_FLAGSREG_HT)
/* Response Timeout Error */
#define LIN_17_ASCLIN_RESP_TIMEOUT_ERR (LIN_17_ASCLIN_FLAGSREG_RT)

#define LIN_17_ASCLIN_TIMEOUT_DURATION             (1000U)

#define LIN_17_ASCLIN_WAKEUP_VALUE              (496U)
/* MISRA2012_RULE_2_5_JUSTIFICATION: Macro will be used with
 other configuration enabled*/
#define LIN_17_ASCLIN_WAKEUP_NUMERATOR_VAL             (10U)
/* MISRA2012_RULE_2_5_JUSTIFICATION: Macro will be used with
 other configuration enabled*/
#define LIN_17_ASCLIN_WAKEUP_DENOMINATOR_VAL           (10U)

#define LIN_17_ASCLIN_ENHANCED_CHECKSUM            (1U)
#define LIN_17_ASCLIN_CLASSIC_CHECKSUM             (0U)

/* LIN Buffer Size */
#define LIN_17_ASCLIN_RESP_BUF_SIZE            (9U)

#define LIN_17_ASCLIN_KRST_TIMEOUT (0x100U)

/* Sleep Request Macros */
#define LIN_17_ASCLIN_SLEEP_NOT_REQ               (0U)
#define LIN_17_ASCLIN_SLEEP_REQ                   (1U)

#define LIN_17_ASCLIN_FIRST_CHANNEL               (0U)


/*******************************************************************************
**                   Function like macro definitions                          **
*******************************************************************************/
/* Flags, Flagsenable, Flagsclear register/s mask for
   Master to Slave transmission */
#define LIN_17_ASCLIN_FLAGS_MS_TX (LIN_17_ASCLIN_FLAGSREG_TR |\
  LIN_17_ASCLIN_FLAGSREG_HT | LIN_17_ASCLIN_FLAGSREG_TFO |\
  LIN_17_ASCLIN_FLAGSREG_CE | LIN_17_ASCLIN_FLAGSREG_RT |\
  LIN_17_ASCLIN_FLAGSREG_FE | LIN_17_ASCLIN_FLAGSREG_LP )

/* Flags, Flagsenable, Flagsclear register/s mask for
   Slave to Master transmission */
#define LIN_17_ASCLIN_FLAGS_MS_RX (LIN_17_ASCLIN_FLAGSREG_RR |\
  LIN_17_ASCLIN_FLAGSREG_HT | LIN_17_ASCLIN_FLAGSREG_RFO |\
  LIN_17_ASCLIN_FLAGSREG_RFU | LIN_17_ASCLIN_FLAGSREG_CE |\
  LIN_17_ASCLIN_FLAGSREG_RT | LIN_17_ASCLIN_FLAGSREG_FE |\
  LIN_17_ASCLIN_FLAGSREG_LC | LIN_17_ASCLIN_FLAGSREG_LP|\
  LIN_17_ASCLIN_FLAGSREG_TFO )

/* Flags, Flagsenable, Flagsclear register/s mask for
   Slave to Slave transmission */
#define LIN_17_ASCLIN_FLAGS_MS_HO (LIN_17_ASCLIN_FLAGSREG_TH |\
  LIN_17_ASCLIN_FLAGSREG_HT | LIN_17_ASCLIN_FLAGSREG_TFO |\
  LIN_17_ASCLIN_FLAGSREG_CE | LIN_17_ASCLIN_FLAGSREG_FE |\
  LIN_17_ASCLIN_FLAGSREG_LP )

/* Flags, Flagsenable, Flagsclear register/s mask for
   Master to Slave transmission */
#define LIN_17_ASCLIN_FLAGSCLEAR_MS_TX (LIN_17_ASCLIN_FLAGSREG_TR |\
  LIN_17_ASCLIN_FLAGSREG_HT | LIN_17_ASCLIN_FLAGSREG_TFO |\
  LIN_17_ASCLIN_FLAGSREG_CE | LIN_17_ASCLIN_FLAGSREG_RT |\
  LIN_17_ASCLIN_FLAGSREG_TC  | LIN_17_ASCLIN_FLAGSREG_FE |\
  LIN_17_ASCLIN_FLAGSREG_LP )

/* Flags, Flagsenable, Flagsclear register/s mask for
   Slave to Master transmission */
#define LIN_17_ASCLIN_FLAGSCLEAR_MS_RX (LIN_17_ASCLIN_FLAGSREG_RR |\
  LIN_17_ASCLIN_FLAGSREG_HT | LIN_17_ASCLIN_FLAGSREG_RFO |\
  LIN_17_ASCLIN_FLAGSREG_RFU | LIN_17_ASCLIN_FLAGSREG_CE |\
  LIN_17_ASCLIN_FLAGSREG_RT | LIN_17_ASCLIN_FLAGSREG_FE |\
  LIN_17_ASCLIN_FLAGSREG_LC | LIN_17_ASCLIN_FLAGSREG_TC )

/* Flags, Flagsenable, Flagsclear register/s mask for
   Slave to Slave transmission */
#define LIN_17_ASCLIN_FLAGSCLEAR_MS_HO (LIN_17_ASCLIN_FLAGSREG_TH \
  | LIN_17_ASCLIN_FLAGSREG_HT\
| LIN_17_ASCLIN_FLAGSREG_TFO | LIN_17_ASCLIN_FLAGSREG_CE |  \
LIN_17_ASCLIN_FLAGSREG_FE | LIN_17_ASCLIN_FLAGSREG_LP )

/*******************************************************************************
**                         User Mode Macros                                   **
*******************************************************************************/
/* [cover parentID={1A65EADD-AFD0-4845-B2D2-8257E086DD67}]
    [/cover] */
/* [cover parentID={9A645A5C-2204-4b30-9B01-842C8E69CB7D}]
    [/cover] */
#if(LIN_17_ASCLIN_INIT_DEINIT_API_MODE == LIN_17_ASCLIN_MCAL_SUPERVISOR_MODE)
/* MISRA2012_RULE_4_9_JUSTIFICATION: Function like macro is defined for User
   mode support in code. No side effects foreseen by violating this MISRA
   rule. */
#define LIN_17_ASCLIN_INIT_DEINIT_WRITESAFETYENDINITPROTREG(RegAdd,Data)   \
    Mcal_WritePeripEndInitProtReg(RegAdd,Data)
#else
/* MISRA2012_RULE_4_9_JUSTIFICATION: Function like macro is defined for
   User mode support in code. No side effects foreseen by violating this MISRA
   rule. */
#define LIN_17_ASCLIN_INIT_DEINIT_WRITESAFETYENDINITPROTREG(RegAdd,Data)   \
    MCAL_LIB_WRITEPERIPENDINITPROTREG(RegAdd,Data)
#endif

/*******************************************************************************
**                      Private Type Definitions                              **
*******************************************************************************/

/*This Type is used to internal state of LIN driver.*/
/* [cover parentID={181C36B0-2030-4b33-9351-815EF2FB202A}]
    [/cover] */
typedef enum
{
  LIN_17_ASCLIN_CH_UNINIT_I,
  LIN_17_ASCLIN_CH_INIT_I,
  LIN_17_ASCLIN_SEND_HEADER_I,
  LIN_17_ASCLIN_MASTER_TX_COMPLETE_I,
  LIN_17_ASCLIN_RECEIVE_COMPLETE_I,
  LIN_17_ASCLIN_WAKEUP_WAIT_I,
  LIN_17_ASCLIN_SLEEP_PENDING_I,
  LIN_17_ASCLIN_TX_HEADER_ERROR_I,
  LIN_17_ASCLIN_TX_ERROR_I,
  LIN_17_ASCLIN_RX_ERROR_I,        /*a. Framing Error, CRC error, collision and Short response */
  LIN_17_ASCLIN_RX_NO_RESPONSE_I,  /*a. When No response is received after header transmisison
                                     b. On response timeout - Returns LIN_RX_NO_RESPONSE */ 
} Lin_17_AscLin_IntStatusType;

/*
Lin_17_AscLin_ChannelInfoType: This structure is used for storing internal LIN
                     channel status and other information.
*/
/* [cover parentID={BF2D633E-B1C1-40b7-8F4F-0A0247A0830F}]
    [/cover] */
typedef struct
{
  Lin_17_AscLin_IntStatusType   State; /* Current internal state
                                          of LIN driver */
  uint8   Cs;    /* Checksum type */
  Lin_FramePidType   Pid;      /* Pid of the Pdu being serviced */
  Lin_FrameResponseType   Drc;      /* Response type fo the Pdu */
  uint8   Sleep;    /* Sleep requested/not requested */
  uint8   Dl;       /* Data length of the sdu */
} Lin_17_AscLin_ChannelInfoType;

/*******************************************************************************
**                      Global Constant Definitions                           **
*******************************************************************************/


/*******************************************************************************
**                      Global Variable Definitions                           **
*******************************************************************************/

/*******************************************************************************
**                      Private Constant Definitions                          **
*******************************************************************************/
/* [cover parentID={5713A17A-3FA1-427f-A0B6-89125A17689A}]
    [/cover] */
/* [cover parentID={EA0715EE-3E3C-4aac-A42E-4B5CFC96CEED}] memmap
    [/cover] */
/* [cover parentID={B7F970AB-64ED-40b5-9BE7-A64D9494F4AB}] memmap
    [/cover] */

#define  LIN_17_ASCLIN_START_SEC_CONST_QM_LOCAL_32
/* MISRA2012_RULE_4_10_JUSTIFICATION: To be compliant with autosar guidelines
Lin_17_AscLin_Memmap.h header is included without safegaurd.*/
/* MISRA2012_RULE_20_1_JUSTIFICATION: Lin_17_AscLin_Memmap.h header included
as per Autosar guidelines. */
#include "Lin_17_AscLin_MemMap.h"

static Ifx_ASCLIN* const Lin_17_AscLin_AscLinRegAddr[LIN_17_ASCLIN_MAX_HW_UNIT]\
= {                                                                            \
    /* This macro expands into a list of pointers, pointing to the register
     address in respective order of position depending on the device variant */
    LIN_17_ASCLIN_REGADDR
  };

/* [cover parentID={5713A17A-3FA1-427f-A0B6-89125A17689A}]
    [/cover] */
#define LIN_17_ASCLIN_STOP_SEC_CONST_QM_LOCAL_32
/* MISRA2012_RULE_4_10_JUSTIFICATION: To be compliant with autosar guidelines
Lin_17_AscLin_Memmap.h header is included without safegaurd.*/
/* MISRA2012_RULE_20_1_JUSTIFICATION: Lin_17_AscLin_Memmap.h header included
as per Autosar guidelines. */
#include "Lin_17_AscLin_MemMap.h"

/*******************************************************************************
**                      Private Variable Definitions                          **
*******************************************************************************/
/* [cover parentID={72DABBEB-F27B-4677-B6B4-B53F634341BA}]
    [/cover] */
#define  LIN_17_ASCLIN_START_SEC_VAR_CLEARED_QM_LOCAL_8
/* MISRA2012_RULE_4_10_JUSTIFICATION: To be compliant with autosar guidelines
Lin_17_AscLin_Memmap.h header is included without safegaurd.*/
/* MISRA2012_RULE_20_1_JUSTIFICATION: Lin_17_AscLin_Memmap.h header included
as per Autosar guidelines. */
#include "Lin_17_AscLin_MemMap.h"

/* Received data is loaded into this buffer */
static uint8  Lin_17_AscLin_ResponseBuffer[LIN_17_ASCLIN_MAXIMUM_CHANNEL]      \
  [LIN_17_ASCLIN_RESP_BUF_SIZE];

/* [cover parentID={72DABBEB-F27B-4677-B6B4-B53F634341BA}]
    [/cover] */
#define  LIN_17_ASCLIN_STOP_SEC_VAR_CLEARED_QM_LOCAL_8
/* MISRA2012_RULE_4_10_JUSTIFICATION: To be compliant with autosar guidelines
Lin_17_AscLin_Memmap.h header is included without safegaurd.*/
/* MISRA2012_RULE_20_1_JUSTIFICATION: Lin_17_AscLin_Memmap.h header included
as per Autosar guidelines. */
#include "Lin_17_AscLin_MemMap.h"

/* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32 chars
  in source code due to Autosar Naming constraints. Since compiler support
   more than 32 characters, no side affects seen*/
/* MISRA2012_RULE_5_2_JUSTIFICATION: External identifiers going beyond 32 chars
  in source code due to Autosar Naming constraints. Since compiler support
   more than 32 characters, no side affects seen*/
/* MISRA2012_RULE_5_4_JUSTIFICATION: External identifiers going beyond 32 chars
  in source code due to Autosar Naming constraints. Since compiler support
   more than 32 characters, no side affects seen*/
/* MISRA2012_RULE_5_5_JUSTIFICATION: External identifiers going beyond 32 chars
  in source code due to Autosar Naming constraints. Since compiler support
   more than 32 characters, no side affects seen*/
/* [cover parentID={72DABBEB-F27B-4677-B6B4-B53F634341BA}]
    [/cover] */
#define LIN_17_ASCLIN_START_SEC_VAR_CLEARED_QM_LOCAL_32
/* MISRA2012_RULE_4_10_JUSTIFICATION: To be compliant with autosar guidelines
Lin_17_AscLin_Memmap.h header is included without safegaurd.*/
/* MISRA2012_RULE_20_1_JUSTIFICATION: Lin_17_AscLin_Memmap.h header included
as per Autosar guidelines. */
#include "Lin_17_AscLin_MemMap.h"

/*
Variable Holds the Configuration Pointer given in Lin_17_AscLin_Init and
Lin_ChannelInit
*/
static const Lin_17_AscLin_ConfigType* Lin_17_AscLin_kConfigPtr;

/* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32 chars
  in source code due to Autosar Naming constraints. Since compiler support
   more than 32 characters, no side affects seen*/
/* MISRA2012_RULE_5_2_JUSTIFICATION: External identifiers going beyond 32 chars
  in source code due to Autosar Naming constraints. Since compiler support
   more than 32 characters, no side affects seen*/
/* MISRA2012_RULE_5_4_JUSTIFICATION: External identifiers going beyond 32 chars
  in source code due to Autosar Naming constraints. Since compiler support
   more than 32 characters, no side affects seen*/
/* MISRA2012_RULE_5_5_JUSTIFICATION: External identifiers going beyond 32 chars
  in source code due to Autosar Naming constraints. Since compiler support
   more than 32 characters, no side affects seen*/
/* [cover parentID={72DABBEB-F27B-4677-B6B4-B53F634341BA}]
    [/cover] */
#define LIN_17_ASCLIN_STOP_SEC_VAR_CLEARED_QM_LOCAL_32
/* MISRA2012_RULE_4_10_JUSTIFICATION: To be compliant with autosar guidelines
Lin_17_AscLin_Memmap.h header is included without safegaurd.*/
/* MISRA2012_RULE_20_1_JUSTIFICATION: Lin_17_AscLin_Memmap.h header included
as per Autosar guidelines. */
#include "Lin_17_AscLin_MemMap.h"

/* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32 chars
  in source code due to Autosar Naming constraints. Since compiler support
   more than 32 characters, no side affects seen*/
/* MISRA2012_RULE_5_2_JUSTIFICATION: External identifiers going beyond 32 chars
  in source code due to Autosar Naming constraints. Since compiler support
   more than 32 characters, no side affects seen*/
/* MISRA2012_RULE_5_4_JUSTIFICATION: External identifiers going beyond 32 chars
  in source code due to Autosar Naming constraints. Since compiler support
   more than 32 characters, no side affects seen*/
/* MISRA2012_RULE_5_5_JUSTIFICATION: External identifiers going beyond 32 chars
  in source code due to Autosar Naming constraints. Since compiler support
   more than 32 characters, no side affects seen*/
/* [cover parentID={72DABBEB-F27B-4677-B6B4-B53F634341BA}]
    [/cover] */
#define LIN_17_ASCLIN_START_SEC_VAR_CLEARED_QM_LOCAL_UNSPECIFIED
/* MISRA2012_RULE_4_10_JUSTIFICATION: To be compliant with autosar guidelines
Lin_17_AscLin_Memmap.h header is included without safegaurd.*/
/* MISRA2012_RULE_20_1_JUSTIFICATION: Lin_17_AscLin_Memmap.h header included
as per Autosar guidelines. */
#include "Lin_17_AscLin_MemMap.h"

/*
  This variable holds the status of the driver and includes: checksum,
  sleep status, data length, Pid response type, previous byte transmitted.
*/

static Lin_17_AscLin_ChannelInfoType Lin_17_AscLin_ChannelInfo                 \
  [LIN_17_ASCLIN_MAXIMUM_CHANNEL];

/* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32 chars
  in source code due to Autosar Naming constraints. Since compiler support
   more than 32 characters, no side affects seen*/
/* MISRA2012_RULE_5_2_JUSTIFICATION: External identifiers going beyond 32 chars
  in source code due to Autosar Naming constraints. Since compiler support
   more than 32 characters, no side affects seen*/
/* MISRA2012_RULE_5_4_JUSTIFICATION: External identifiers going beyond 32 chars
  in source code due to Autosar Naming constraints. Since compiler support
   more than 32 characters, no side affects seen*/
/* MISRA2012_RULE_5_5_JUSTIFICATION: External identifiers going beyond 32 chars
  in source code due to Autosar Naming constraints. Since compiler support
   more than 32 characters, no side affects seen*/
/* [cover parentID={72DABBEB-F27B-4677-B6B4-B53F634341BA}]
    [/cover] */
#define LIN_17_ASCLIN_STOP_SEC_VAR_CLEARED_QM_LOCAL_UNSPECIFIED
/* MISRA2012_RULE_4_10_JUSTIFICATION: To be compliant with autosar guidelines
Lin_17_AscLin_Memmap.h header is included without safegaurd.*/
/* MISRA2012_RULE_20_1_JUSTIFICATION: Lin_17_AscLin_Memmap.h header included
as per Autosar guidelines. */
#include "Lin_17_AscLin_MemMap.h"

/*******************************************************************************
**                      Private Function Declarations                         **
*******************************************************************************/
/* [cover parentID={4579FE20-92DA-4848-93DB-7AD4FD35DD50}]
    [/cover] */
/*[cover parentID={566ED99C-0D96-46ac-97BF-E97B04E2C700}]
    Callout Memory section not used in LIN driver
[/cover]*/
#define LIN_17_ASCLIN_START_SEC_CODE_QM_LOCAL
/*mapping of code and data to specific memory sections via memory mapping file*/
/* MISRA2012_RULE_4_10_JUSTIFICATION: To be compliant with autosar guidelines
Lin_17_AscLin_Memmap.h header is included without safegaurd.*/
/* MISRA2012_RULE_20_1_JUSTIFICATION: Lin_17_AscLin_Memmap.h header included
as per Autosar guidelines. */
#include "Lin_17_AscLin_MemMap.h"

#if (LIN_17_ASCLIN_DEV_ERROR_DETECT == STD_ON)

/* function returns the DET check status for channel, uninit */
LOCAL_INLINE Std_ReturnType Lin_17_AscLin_lGetDetStatus
(
  const uint8 Channel,                                                      \
  const uint8 ApiId                                                         \
);

LOCAL_INLINE  Std_ReturnType Lin_17_AscLin_lInitDetCheck
(                                                                            \
  const Lin_17_AscLin_ConfigType* const Config                               \
);

#endif
/* (LIN_17_ASCLIN_DEV_ERROR_DETECT == STD_ON)*/

/**/
LOCAL_INLINE Lin_17_AscLin_IntStatusType Lin_17_AscLin_lGetIntErrorStatus
(                                                                            \
  const uint32 HwErrorFlags, const uint8 Channel                             \
);

/**/
LOCAL_INLINE void Lin_17_AscLin_lHwSendWakeupPulse(const uint8 HwUnit);

/**/
LOCAL_INLINE void Lin_17_AscLin_lHwInitKernelReg(const uint8 HwUnit);


/**/
static void Lin_17_AscLin_lHwInit                                           \
(                                                                           \
  const uint8 HwUnit,                                                       \
  const Lin_17_AscLin_ChannelTimingConfigType TimingConfig,                 \
  const uint8 RxAlternatePinSelect                                          \
);

/**/
static void Lin_17_AscLin_lHwStartTransmission                              \
(                                                                           \
    const uint8 HwUnit,                                                     \
    const uint8 Channel                                                     \
);

static void Lin_17_AscLin_lHandleRx(const uint8  HwUnit);

static void Lin_17_AscLin_lHandleTx(const uint8  HwUnit);

static void Lin_17_AscLin_lHandleErr(const uint8  HwUnit);

#if (LIN_17_ASCLIN_GLOBAL_CHANNEL_WAKEUP_SUPPORT == STD_ON)

/**/
static void Lin_17_AscLin_lHwConfigWakeup                                     \
(                                                                            \
  const uint8 HwUnit,                                                        \
  const uint8 IocrDepth,                                                     \
  const uint16 BitconPrescalar                                               \
);

/**/
static void Lin_17_AscLin_lHwConfigAfterWakeup(const uint8 HwUnit);

#endif


/*******************************************************************************
**                      Global Function Definitions                           **
*******************************************************************************/

/*******************************************************************************
** Traceability :[cover parentID={001A7921-AA81-443e-B348-8A15E16AACE6}] **
**                         [/cover]                                       **
** Syntax : void Lin_17_AscLin_Init                                           **
**                               ( const Lin_17_AscLin_ConfigType* Config )   **
**                                                                            **
** Service ID:  0x00                                                          **
**                                                                            **
** Sync/Async:  Synchronous                                                   **
**                                                                            **
** Reentrancy:  Non reentrant                                                 **
**                                                                            **
** Parameters (in) :  Config - Pointer to LIN driver configuration set        **
**                                                                            **
** Parameters (out):  None                                                    **
**                                                                            **
** Return value    :  None                                                    **
**                                                                            **
** Description : Driver Module Initialization function.                       **
** Service for LIN initialization. The Initialization function shall          **
** initialize all the Lin channels with the values                            **
** of the structure referenced by the parameter Config.                       **
*******************************************************************************/
void Lin_17_AscLin_Init(const Lin_17_AscLin_ConfigType* const Config)
{
  uint8 ModuleNo;
  uint8 Chan;
  uint8 MaxChannel;
  const Lin_17_AscLin_ChannelType   *ChannelConfigPtr;
  Ifx_ASCLIN* HwModuleAddr;

  /* [cover parentID={6F017557-502E-47dd-A718-9C006789C05D}]
    [/cover] */
  #if (LIN_17_ASCLIN_DEV_ERROR_DETECT == STD_ON)
  Std_ReturnType ReturnStatus;
  /* [cover parentID={257022D9-9A4A-4c7e-A778-D2D510359BC2}]
    [/cover] */
  ReturnStatus = Lin_17_AscLin_lInitDetCheck(Config);
  /* [cover parentID={EC9A3949-9156-489a-814B-2FBE505AC83C}]
  [/cover] */
  if (ReturnStatus == E_OK)
  #endif
  {
    MaxChannel = Config->NoOfChannels;
    /* [cover parentID={1BA6DB00-3DF6-4cb6-8780-474C8B7FDB6B}]
        [/cover] */
    /* Enable the ASCLIN hardware unit/s for all the Lin channels */
    /* [cover parentID={37FD59F2-577F-4120-87CD-2542CB410358}]
        [/cover] */
    for (Chan = LIN_17_ASCLIN_NUMBER_ZERO; Chan < MaxChannel; Chan++)
    {

      /* [cover parentID={9CEA4605-62BC-4270-B083-49BDB85C203D}]
          [/cover] */
      ChannelConfigPtr = &(Config->ChannelConfigPtr[Chan]);

      /* Extract the hwmodule */
      ModuleNo = ChannelConfigPtr->HwModule;
      HwModuleAddr = Lin_17_AscLin_AscLinRegAddr[ModuleNo];
      /* MISRA2012_RULE_11_3_JUSTIFICATION: cast performed between a pointer to
       * object type and a pointer to a different object type due to SFR access.
      */
      /* MISRA2012_RULE_11_8_JUSTIFICATION: SFR access. Since the input
       * argument for the API discards volatile keyword. No side effects
       * foreseen by violating this MISRA rule */
      /* [cover parentID={56B35F33-68F9-4338-A645-EAACA76FD0E0}]
          [/cover] */
      LIN_17_ASCLIN_INIT_DEINIT_WRITESAFETYENDINITPROTREG                    \
      (                                                                    \
          (uint32*)&HwModuleAddr->CLC.U, LIN_17_ASCLIN_CLC                   \
      );

      if(HwModuleAddr->CLC.B.DISS != LIN_17_ASCLIN_DISABLE_FLAG)
      {
        Lin_17_AscLin_ChannelInfo[LIN_17_ASCLIN_FIRST_CHANNEL].State =         \
                LIN_17_ASCLIN_CH_UNINIT_I;
        /* if clc register value is not updated then LIN initialization
          is failed and hence the loop is break */
        break;
      }

      /* Reset Kernel  */
      /* [cover parentID={30C0A911-7A5D-4f79-B871-58C7F8AF9813}]
        [/cover] */
      Lin_17_AscLin_lHwInitKernelReg(ModuleNo);

      /* Initialise the Lin Hardware. */
      /* [cover parentID={09504911-2C34-4d6e-80C4-47D58D7FA9C3}]
        [/cover] */
      Lin_17_AscLin_lHwInit(ModuleNo, ChannelConfigPtr->TimingConfig,
      ChannelConfigPtr->RxAlternatePinSelect);

      /* Init the channel State variable */
      /* [cover parentID={639B5194-5EFC-470e-8B95-7C6C0ECEDEB4}]
        [/cover] */
      /* [cover parentID={E9945956-F203-4ac0-9070-6BA687D26269}]
      [/cover] */
      /* [cover parentID={D1D5A830-D9E3-4e36-B49E-D845B5E1AC7E}]
      [/cover] */
      Lin_17_AscLin_ChannelInfo[Chan].State = LIN_17_ASCLIN_CH_INIT_I;

    }
    /* Store Config for use by APIs*/
    Lin_17_AscLin_kConfigPtr = Config;

  }
  return ;
}

/*******************************************************************************
** Traceability :[cover parentID={5CA76F2E-2A38-4214-B7B9-1B9D511C32ED}] **
**                        [/cover]                                        **
**                                                                            **
** Syntax : Std_ReturnType Lin_17_AscLin_CheckWakeup(uint8 Channel)           **
** [/cover]                                                                   **
**                                                                            **
** Service ID:  0x0A                                                          **
**                                                                            **
** Sync/Async:  Synchronous                                                   **
**                                                                            **
** Reentrancy:  Non reentrant                                                 **
**                                                                            **
** Parameters (in): Channel - LIN channel to be addressed .                   **
**                                                                            **
** Parameters (out): None                                                     **
**                                                                            **
** Return value    : E_OK - send command has been accepted.                   **
**                   E_NOT_OK - send command has not been accepted,           **
**                              development or production error occurred.     **
** Description : Service to identifiy the Lin channel after a wake up is      **
** caused by LIN bus transceiver                                              **
*******************************************************************************/
Std_ReturnType Lin_17_AscLin_CheckWakeup(const uint8 Channel)
{
  const Lin_17_AscLin_ChannelType   *ChannelConfigPtr;
  uint32 EcumStatus;
  uint8 HwUnit;
  Std_ReturnType ReturnStatus;
  const Ifx_ASCLIN* HwModuleAddr;

  /* [cover parentID={00E1CCD0-9284-4a0d-8A10-BD6A7C9760BC}]
    [/cover] */
  #if (LIN_17_ASCLIN_DEV_ERROR_DETECT == STD_ON)
  /* [cover parentID={57F66744-06F6-423a-A3F2-637545ECF6E8}]
    [/cover] */
  ReturnStatus = Lin_17_AscLin_lGetDetStatus                                   \
                   (                                                           \
                      Channel,LIN_17_ASCLIN_SID_CHECKWAKEUP                    \
                    );
  /* [cover parentID={4FF9DC02-8E00-488f-9DBF-B3D7A9CE6624}]
      [/cover] */
  if (ReturnStatus == E_OK)
  #else
  /* [cover parentID={BC7DDA2B-EF32-4680-849D-1EA8B2448524}]
    [/cover] */
  ReturnStatus = E_OK;
  #endif  /* (LIN_17_ASCLIN_DEV_ERROR_DETECT == STD_ON) */
  {
    ChannelConfigPtr = &(Lin_17_AscLin_kConfigPtr->ChannelConfigPtr[Channel]);

    /* Extract the hwmodule */
    HwUnit = ChannelConfigPtr->HwModule;
    HwModuleAddr = Lin_17_AscLin_AscLinRegAddr[HwUnit];

    /* If RxD line = 0, provide notification */
    /* [cover parentID={8BAAF15D-C747-4bc2-9F46-4C053233D8F5}]
        [/cover] */
    if (HwModuleAddr->IOCR.B.RXM == STD_LOW)
    {

      EcumStatus = ChannelConfigPtr->WakeupSourceId;

      /* Set the wakeup event in ECUM regardless of
      LinChannelWakeupSupport*/
      /* [cover parentID={397EEB66-6F86-4a46-B5E5-F5C596C6164C}]
          [/cover] */
      EcuM_SetWakeupEvent((uint32)LIN_17_ASCLIN_ENABLE_FLAG << EcumStatus);
	  
/* --------{ EB Automotive legal  }--------- 

Note: Elektrobit Automotive GmbH modified the original code provided
      by the third party supplier. The modification is provided for convenience.
      Please use the modification on your discretion and account, or
      use the unmodified files provided with this distribution. 
      Please see for the reasons in the file ImportantNotes.txt for tag
ASCINFINEON-761 function "LinIf_WakeupConfirmation" should be call only if configured.	  
*/	

#if (LIN_GLOBAL_CHANNEL_WAKEUP_SUPPORT == STD_ON)
      /* Successful wakeup detection reported */
      /* [cover parentID={46F61585-74B5-4bf5-A12A-361E30796477}]
          [/cover] */
      LinIf_WakeupConfirmation((uint32)LIN_17_ASCLIN_ENABLE_FLAG << EcumStatus);
#endif	

    }/*(Lin_lHwGetRxDStatus(HwUnit) == STD_LOW)*/
  }
  return ReturnStatus;
}

/*******************************************************************************
** Traceability :[cover parentID={D17A666A-6BBA-4c01-AFEA-2D32CEEB9E02}] **
**                        [/cover]                                        **
** Syntax : Std_ReturnType Lin_17_AscLin_SendFrame                            **
**           (                                                                **
**             uint8 Channel,                                                 **
**             Lin_PduType* PduInfoPtr                                        **
**           )                                                                **
** [/cover]                                                                   **
**                                                                            **
** Service ID:  0x04                                                          **
**                                                                            **
** Sync/Async:  Asynchonous                                                   **
**                                                                            **
** Reentrancy:  Non reentrant                                                 **
**                                                                            **
** Parameters (in): Channel - LIN channel to be addressed .                   **
**                  PduInfoPtr - Pointer to PDU containing the PID, Checksum  **
**                  model, Response type, Dl and SDU data pointer             **
**                                                                            **
** Parameters (out): None                                                     **
**                                                                            **
** Return value    : E_OK - send command has been accepted.                   **
**                   E_NOT_OK - send command has not been accepted,           **
**                              development or production error occurred.     **
**                                                                            **
** Description : Service to send a Lin Frame (header and Response).           **
**                                                                            **
*******************************************************************************/
Std_ReturnType Lin_17_AscLin_SendFrame
(
  const uint8 Channel,
  Lin_PduType* const PduInfoPtr
)
{
  const Lin_17_AscLin_ChannelType   *ChannelConfigPtr;
  Lin_17_AscLin_IntStatusType CurStatus;
  uint8 HwUnit;
  Std_ReturnType   RetVal;
  uint8 Index;
  const uint8 *DataPtr;
  Ifx_ASCLIN*  HwModulePtr;

  /* [cover parentID={6DF86AA6-F42C-4ec0-AFA7-7DCF26707F91}]
    [/cover] */
  #if (LIN_17_ASCLIN_DEV_ERROR_DETECT == STD_ON)
  /* if the channel, UnInit parameters is invalid */
  /* [cover parentID={1075DF33-2FE3-4a1f-AD90-49CC6FA32731}]
    [/cover] */
  RetVal = Lin_17_AscLin_lGetDetStatus(Channel, LIN_17_ASCLIN_SID_SENDFRAME);

  /* Check pointer validity */
  /* [cover parentID={AB597A35-D80C-48cb-9726-EE6B952C3C28}]
    [/cover] */
  if ((RetVal == E_OK) && (PduInfoPtr == NULL_PTR))
  {
    /* Report to  DET */
    /* [cover parentID={5C040CCD-F57E-4353-89DA-7A33908EFCAB}]
        [/cover] */
    Det_ReportError(
      LIN_17_ASCLIN_MODULE_ID,
      LIN_17_ASCLIN_INSTANCE_ID,
      LIN_17_ASCLIN_SID_SENDFRAME,
      LIN_17_ASCLIN_E_PARAM_POINTER
    );

    RetVal = E_NOT_OK;

  }
  /* Check for the channel state machine in Sleep state */
  /* [cover parentID={6520F4C2-5EFA-4577-944C-083C3618C1BA}]
      [/cover] */
  /* [cover parentID={42D04DDA-B329-4bc7-9BD7-E78AEF772CF4}]
      [/cover] */
  else if ((RetVal == E_OK) &&
  (Lin_17_AscLin_ChannelInfo[Channel].State == LIN_17_ASCLIN_WAKEUP_WAIT_I))
  {
    /* Report to  DET */
    /* [cover parentID={A75AB9EE-0350-4da6-923C-2C94DB522447}]
        [/cover] */
    Det_ReportError(
      LIN_17_ASCLIN_MODULE_ID,
      LIN_17_ASCLIN_INSTANCE_ID,
      LIN_17_ASCLIN_SID_SENDFRAME,
      LIN_17_ASCLIN_E_STATE_TRANSITION
    );

    RetVal = E_NOT_OK;

  }
  else
  {
    /* Dummy else */
  }
  if (RetVal == E_OK)
  #else

  RetVal = E_OK;

  #endif  /* (LIN_17_ASCLIN_DEV_ERROR_DETECT == STD_ON) */
  {
    ChannelConfigPtr = &(Lin_17_AscLin_kConfigPtr->ChannelConfigPtr[Channel]);

    /* Extract the Hw module */
    HwUnit = ChannelConfigPtr->HwModule;

    HwModulePtr = (Lin_17_AscLin_AscLinRegAddr[HwUnit]);

    CurStatus = Lin_17_AscLin_ChannelInfo[Channel].State;

    /* Receive Buffer Mode = RXFIFO */
    HwModulePtr->RXFIFOCON.B.BUF = LIN_17_ASCLIN_DISABLE_FLAG;
    /* Flush the Rx fifo */
    HwModulePtr->RXFIFOCON.B.FLUSH = LIN_17_ASCLIN_ENABLE_FLAG;

    /* Disable the RX inlet */
    HwModulePtr->RXFIFOCON.B.ENI = LIN_17_ASCLIN_DISABLE_FLAG;
    /* Flush the Tx fifo */
    HwModulePtr->TXFIFOCON.B.FLUSH = LIN_17_ASCLIN_ENABLE_FLAG;

    /* Disable the Tx outlet b'fore the data entry */
    HwModulePtr->TXFIFOCON.B.ENO = LIN_17_ASCLIN_DISABLE_FLAG;

    /* Clear all the Flags. */
    HwModulePtr->FLAGSCLEAR.U = LIN_17_ASCLIN_FLAGSCLEAR_VAL;

    /* Tx / Rx already in progress */
    /* [cover parentID={C7FF0566-F055-4e87-91AC-83DD2DDC4DF5}]
        [/cover] */
    if (CurStatus == LIN_17_ASCLIN_SEND_HEADER_I)
    {
      /* RE-initialise the Hw Module */
      /* [cover parentID={C170BD7C-7975-45ba-9490-D8CE732998E8}]
          [/cover] */
      Lin_17_AscLin_lHwInit(HwUnit, ChannelConfigPtr->TimingConfig,
      ChannelConfigPtr->RxAlternatePinSelect);
    }

    /* [cover parentID={DF65621C-531E-42a2-91A3-672B39BF235C}]
         [/cover] */
    /* Copy PDU parmaeters in Lin_Channel_Info */
    Lin_17_AscLin_ChannelInfo[Channel].Dl = PduInfoPtr->Dl;

    if(PduInfoPtr->Cs == LIN_ENHANCED_CS)
    {
      Lin_17_AscLin_ChannelInfo[Channel].Cs = LIN_17_ASCLIN_ENHANCED_CHECKSUM;
    }
    else
    {
      Lin_17_AscLin_ChannelInfo[Channel].Cs = LIN_17_ASCLIN_CLASSIC_CHECKSUM;
    }

    Lin_17_AscLin_ChannelInfo[Channel].Pid = PduInfoPtr->Pid;

    Lin_17_AscLin_ChannelInfo[Channel].Drc = PduInfoPtr->Drc;

    /* [cover parentID={3E7D9C9E-F2DC-44cf-8CB5-1D14D2CA2311}]
    [/cover] */
    /* Write Data bytes to local buffer in case of Master to Slave */
    if (Lin_17_AscLin_ChannelInfo[Channel].Drc == LIN_MASTER_RESPONSE)
    {
      Index = LIN_17_ASCLIN_NUMBER_ZERO;
      DataPtr = PduInfoPtr->SduPtr;
      do
      {
        /* [cover parentID={97E637A4-C513-4f50-82C8-C8D09577ECFE}]
            [/cover] */
        Lin_17_AscLin_ResponseBuffer[Channel][Index] = *DataPtr;
        DataPtr++;
        Index++;
      } while (Index < Lin_17_AscLin_ChannelInfo[Channel].Dl);
    }

    /* Start the Frame Transmission */
    /* [cover parentID={6901C63E-1258-4002-AFAF-612DE69E451E}]
        [/cover] */
    Lin_17_AscLin_lHwStartTransmission(HwUnit, Channel);

    Lin_17_AscLin_ChannelInfo[Channel].State = LIN_17_ASCLIN_SEND_HEADER_I;
  }
  return RetVal;
  /* MISRA2012_RULE_8_13_JUSTIFICATION: To be compliant with autosar guidelines
  Lin_17_AscLin_SendFrame syntax is not changed.*/
}

/*******************************************************************************
** Traceability :[cover parentID={3172570B-BEE6-4305-92F9-9C6DA91D70EA}] **
**                           [/cover]                                     **
** Syntax : Std_ReturnType Lin_17_AscLin_GoToSleep( uint8 Channel )           **
** [/cover]                                                                   **
**                                                                            **
** Service ID:  0x06                                                          **
**                                                                            **
** Sync/Async:  Asynchonous                                                   **
**                                                                            **
** Reentrancy:  Non Reentrant                                                 **
**                                                                            **
** Parameters (in) : Channel - LIN channel to be addressed                    **
**                                                                            **
** Parameters (out): None                                                     **
**                                                                            **
** Return value    : E_OK: Sleep command has been accepted                    **
**                   E_NOT_OK: Sleep command has not been accepted,           **
**                   development or production error occurred                 **
**                                                                            **
** Description :    The service instructs the driver to transmit a            **
**               go-to-sleep-command on the addressed LIN channel             **
**                                                                            **
*******************************************************************************/
Std_ReturnType Lin_17_AscLin_GoToSleep(const uint8 Channel)
{

  const Lin_17_AscLin_ChannelType   *ChannelConfigPtr;
  Lin_17_AscLin_IntStatusType CurStatus;
  uint8 HwUnit;
  Std_ReturnType  RetVal;
  uint8 Index;

  Ifx_ASCLIN*  HwModulePtr;
  /* [cover parentID={C94B8C44-E89D-45b9-AB98-7253C44EAFAC}]
       [/cover] */
  #if (LIN_17_ASCLIN_DEV_ERROR_DETECT == STD_ON)
  /* if the channel, UnInit parameters is invalid */
  /* [cover parentID={2D44F4D5-F7DA-4379-94A9-96744017041A}]
       [/cover] */
  RetVal = Lin_17_AscLin_lGetDetStatus(Channel, LIN_17_ASCLIN_SID_GOTOSLEEP);
  /* [cover parentID={D6BF6D41-B133-4be8-9106-7DA5660D61FC}]
     [/cover] */
  if (RetVal == E_OK)
  #else
  /* [cover parentID={51DBFC85-1889-416d-A10E-355519895390}]
       [/cover] */
  RetVal = E_OK;
  #endif  /* (LIN_17_ASCLIN_DEV_ERROR_DETECT == STD_ON) */
  {

    ChannelConfigPtr = &(Lin_17_AscLin_kConfigPtr->ChannelConfigPtr[Channel]);

    /* Extract HwUnit */
    HwUnit = ChannelConfigPtr->HwModule;

    HwModulePtr = (Lin_17_AscLin_AscLinRegAddr[HwUnit]);

    /* Receive Buffer Mode = RXFIFO */
    HwModulePtr->RXFIFOCON.B.BUF = LIN_17_ASCLIN_DISABLE_FLAG;
    /* Flush the Rx fifo */
    HwModulePtr->RXFIFOCON.B.FLUSH = LIN_17_ASCLIN_ENABLE_FLAG;

    /* Disable the RX inlet */
    HwModulePtr->RXFIFOCON.B.ENI = LIN_17_ASCLIN_DISABLE_FLAG;
    /* Flush the Tx fifo */
    HwModulePtr->TXFIFOCON.B.FLUSH = LIN_17_ASCLIN_ENABLE_FLAG;

    /* Disable the Tx outlet b'fore the data entry */
    HwModulePtr->TXFIFOCON.B.ENO = LIN_17_ASCLIN_DISABLE_FLAG;

    /* Clear all the Flags. */
    HwModulePtr->FLAGSCLEAR.U = LIN_17_ASCLIN_FLAGSCLEAR_VAL;

    CurStatus = Lin_17_AscLin_ChannelInfo[Channel].State;

    /* Tx / Rx in progress */
    /* [cover parentID={2EC5E335-996D-4ca4-9214-533F8DED3F44}]
       [/cover] */
    if (CurStatus == LIN_17_ASCLIN_SEND_HEADER_I)
    {
      /* RE-initialise the Hw Module */
      /* [cover parentID={5DEC00CA-40F5-42c3-8297-8789584ED68E}]
         [/cover] */
      Lin_17_AscLin_lHwInit(HwUnit, ChannelConfigPtr->TimingConfig,
      ChannelConfigPtr->RxAlternatePinSelect);
    }

    /* Update Lin_Channel_Info with Sleep command */
    Lin_17_AscLin_ChannelInfo[Channel].Dl = LIN_17_ASCLIN_SLEEPCMD_DL;
    Lin_17_AscLin_ChannelInfo[Channel].Cs = LIN_17_ASCLIN_CLASSIC_CHECKSUM;
    Lin_17_AscLin_ChannelInfo[Channel].Pid = LIN_17_ASCLIN_SLEEPCMD_PID;
    Lin_17_AscLin_ChannelInfo[Channel].Drc = LIN_MASTER_RESPONSE;

    /* Sleep data */
    /* [cover parentID={CF442622-0972-4730-8131-760BAC9021B8}]
        Change state to sleep pending[/cover] */
    /* [cover parentID={3E7D9C9E-F2DC-44cf-8CB5-1D14D2CA2311}]
        Change state to sleep pending[/cover] */
    Lin_17_AscLin_ResponseBuffer[Channel][LIN_17_ASCLIN_NUMBER_ZERO] =         \
        LIN_17_ASCLIN_SLEEPCMD_DATA0;

    for(Index = LIN_17_ASCLIN_NUMBER_ONE;                                      \
              Index < LIN_17_ASCLIN_SLEEPCMD_DATLEN; Index++)
    {
      Lin_17_AscLin_ResponseBuffer[Channel][Index] =
           LIN_17_ASCLIN_SLEEPCMD_DATA1TO7;
    }

    /* Update the state variables. */
    /* [cover parentID={0D306C59-2A49-4477-AEDF-49EAD5998DC6}]
        Change state to sleep pending[/cover] */
    /* [cover parentID={639B5194-5EFC-470e-8B95-7C6C0ECEDEB4}]
            [/cover] */
    /* [cover parentID={F9F6B700-5F20-485b-8347-B32EA89F19D9}]
            [/cover] */
    Lin_17_AscLin_ChannelInfo[Channel].State = LIN_17_ASCLIN_SLEEP_PENDING_I;
    Lin_17_AscLin_ChannelInfo[Channel].Sleep = (uint8)LIN_17_ASCLIN_SLEEP_REQ;

    /* Start the Sleep Frame Transmission.
    Since sleep frame transmission is internal to Driver,
    Configure to send both header and response at one shot.
    */
    Lin_17_AscLin_lHwStartTransmission(HwUnit, Channel);


  }
  return RetVal;
}

/*******************************************************************************
** Traceability :[cover parentID={7B6A6C05-68D3-45d0-A527-ADEB39AC2E85}] **
**                        [/cover]                                        **
**                                                                            **
** Syntax : Std_ReturnType Lin_17_AscLin_GoToSleepInternal( uint8 Channel )   **
** [/cover]                                                                   **
**                                                                            **
** Service ID:  0x09                                                          **
**                                                                            **
** Sync/Async:  Synchronous                                                   **
**                                                                            **
** Reentrancy:  Non Reentrant                                                 **
**                                                                            **
** Parameters (in) : Channel - LIN channel to be addressed .                  **
**                                                                            **
** Parameters (out): None                                                     **
**                                                                            **
** Return value    : E_OK: Command has been accepted.                         **
**                   E_NOT_OK: Command has not been accepted, development     **
**                   or production error occurred                             **
**                                                                            **
** Description : Sets the channel state to LIN_CH_SLEEP                       **
**                                                                            **
*******************************************************************************/
Std_ReturnType Lin_17_AscLin_GoToSleepInternal(const uint8 Channel)
{
  const Lin_17_AscLin_ChannelType   *ChannelConfigPtr;
  uint8 HwUnit;
  Ifx_ASCLIN*  HwModulePtr;
  Std_ReturnType  RetVal;

  /* [cover parentID={5154DAA8-3580-4d5a-A639-EA8585BFE9D8}]
    [/cover] */
  #if (LIN_17_ASCLIN_DEV_ERROR_DETECT == STD_ON)

  /* if the channel, UnInit parameters is invalid */
  /* [cover parentID={2B7B6F9E-F2D6-4546-B4BE-9E9CE20901AC}]
    [/cover] */
  RetVal = Lin_17_AscLin_lGetDetStatus                                         \
             (                                                                 \
               Channel, LIN_17_ASCLIN_SID_GOTOSLEEPINTERNAL                    \
             );
  /* [cover parentID={D3D7BA5B-B25B-43f7-BC79-BDFB627F44EB}]
    [/cover] */
  if (RetVal == E_OK)
  #else
  /* [cover parentID={F608C27F-DD0E-44c2-8209-18DDE9559097}]
    [/cover] */
  RetVal = E_OK;

  #endif  /* (LIN_17_ASCLIN_DEV_ERROR_DETECT == STD_ON) */
  {
    ChannelConfigPtr = &(Lin_17_AscLin_kConfigPtr->ChannelConfigPtr[Channel]);
    HwUnit = ChannelConfigPtr->HwModule;
    HwModulePtr = Lin_17_AscLin_AscLinRegAddr[HwUnit];
    #if (LIN_17_ASCLIN_INTERRUPT_DISABLED == STD_OFF)
    /* Disable FLAGSEN */
    HwModulePtr->FLAGSCLEAR.U =
    LIN_17_ASCLIN_FLAGSCLEAR_MS_TX | LIN_17_ASCLIN_FLAGSCLEAR_MS_RX |
    LIN_17_ASCLIN_FLAGSCLEAR_MS_HO ;

    HwModulePtr->FLAGSENABLE.U = (uint32)LIN_17_ASCLIN_DISABLE_FLAG;
    #endif

    /* Change LIN Rx state to LIN_WAKEUP_WAIT */
    /* [cover parentID={50849575-C2FE-4e97-9999-FFEB44EB95BB}]
        [/cover] */
    /* [cover parentID={639B5194-5EFC-470e-8B95-7C6C0ECEDEB4}]
            [/cover] */
    Lin_17_AscLin_ChannelInfo[Channel].State = LIN_17_ASCLIN_WAKEUP_WAIT_I;


    /* Disable Tx Fifo outlet */
    HwModulePtr->TXFIFOCON.B.ENO = LIN_17_ASCLIN_DISABLE_FLAG;

    /* [cover parentID={0665FFA1-4EC2-4146-8F75-57EBED42760A}]
      [/cover] */
    #if (LIN_17_ASCLIN_GLOBAL_CHANNEL_WAKEUP_SUPPORT == STD_ON)
    if (LIN_17_ASCLIN_CHANNEL_WAKEUP_ENABLED == (ChannelConfigPtr->Wakeup))
    {
      /* Configure the timings for wakeup detection */
      /* [cover parentID={9BCA3BE4-3C89-4d16-835E-73B035730202}]
          [/cover] */
      Lin_17_AscLin_lHwConfigWakeup(HwUnit,
          ChannelConfigPtr->TimingConfig.HwWakeupIocrDepth,
          ChannelConfigPtr->TimingConfig.HwWakeupBitconPrescalar);
    }
    #endif

    Lin_17_AscLin_ChannelInfo[Channel].Sleep = (uint8)LIN_17_ASCLIN_SLEEP_REQ;
  }
  return RetVal;
}

/*******************************************************************************
** Traceability :[cover parentID={E8ABDF1F-19B8-4250-A694-D5E8BB4643C0}]      **
**                        [/cover]                                            **
** Syntax : Std_ReturnType Lin_17_AscLin_Wakeup( uint8 Channel )              **
** [/cover]                                                                   **
**                                                                            **
** Service ID:      7                                                         **
**                                                                            **
** Sync/Async:      Asynchronous                                              **
**                                                                            **
** Reentrancy:      non reentrant                                             **
**                                                                            **
** Parameters (in): Channel    : LIN channel to be addressed                  **
**                                                                            **
** Parameters (out):none                                                      **
**                                                                            **
** Return value:    E_OK     :Wake-up request has been accepted               **
**                  E_NOT_OK :Wake-up request has not been accepted,          **
**                            development or production error occurred        **
**                                                                            **
** Description :    The service function Lin_WakeUp generates a wakeup pulse  **
**                  on the addressed LIN channel                              **
**                                                                            **
**     Note :       The LIN channel shall be in the LIN_CH_SLEEP state when   **
**                  this service will be called.                              **
*******************************************************************************/
Std_ReturnType Lin_17_AscLin_Wakeup(const uint8 Channel)
{
  const Lin_17_AscLin_ChannelType   *ChannelConfigPtr;
  uint8 HwUnit;
  Std_ReturnType  RetVal;

  /* [cover parentID={6CC40F51-407D-4a62-BA35-CEE06AB02B2B}]
      [/cover] */
  #if (LIN_17_ASCLIN_DEV_ERROR_DETECT == STD_ON)
  /* if the channel, UnInit parameters is invalid */
  /* [cover parentID={98092161-60EF-447d-AF61-9490AEC86B93}]
      [/cover] */
  RetVal = Lin_17_AscLin_lGetDetStatus(Channel, LIN_17_ASCLIN_SID_WAKEUP);

  /* Check for the channel state machine in Sleep state */
  /* [cover parentID={6BF1BF46-F85D-4235-AE2F-8DB1893AD5C8}]
      [/cover] */
  if ((RetVal == E_OK)&&
  (!(Lin_17_AscLin_ChannelInfo[Channel].State == LIN_17_ASCLIN_WAKEUP_WAIT_I)))
  {
    /* Report to  DET */
    /* [cover parentID={9F17B5BC-6BBF-46c1-B59B-4FFEC37BB7D8}]
        [/cover] */
    Det_ReportError(
      LIN_17_ASCLIN_MODULE_ID,
      LIN_17_ASCLIN_INSTANCE_ID,
      LIN_17_ASCLIN_SID_WAKEUP,
      LIN_17_ASCLIN_E_STATE_TRANSITION
    );

    RetVal = E_NOT_OK;
  }
  /* [cover parentID={5E7F6761-480F-4c05-8A0E-AA726068F311}]
     [/cover] */
  if (RetVal == E_OK)
  #else
  /* [cover parentID={4A92E47A-30C3-4798-A1E1-9655DBCDC641}]
        [/cover] */
  RetVal = E_OK;
  if (Lin_17_AscLin_ChannelInfo[Channel].State == LIN_17_ASCLIN_WAKEUP_WAIT_I)
  #endif
  {
    /* Change LIN state to LIN_17_ASCLIN_CH_INIT_I */
    /* [cover parentID={639B5194-5EFC-470e-8B95-7C6C0ECEDEB4}]
            [/cover] */
    /* [cover parentID={D1D5A830-D9E3-4e36-B49E-D845B5E1AC7E}]
      [/cover] */
    Lin_17_AscLin_ChannelInfo[Channel].State = LIN_17_ASCLIN_CH_INIT_I;
    Lin_17_AscLin_ChannelInfo[Channel].Sleep =                                 \
      (uint8)LIN_17_ASCLIN_SLEEP_NOT_REQ;

    ChannelConfigPtr = &(Lin_17_AscLin_kConfigPtr->ChannelConfigPtr[Channel]);

    /* Extract Hw Module */
    HwUnit = ChannelConfigPtr->HwModule;
    /* [cover parentID={639B5194-5EFC-470e-8B95-7C6C0ECEDEB4}]
            [/cover] */
    #if (LIN_17_ASCLIN_GLOBAL_CHANNEL_WAKEUP_SUPPORT == STD_ON)
    if (LIN_17_ASCLIN_CHANNEL_WAKEUP_ENABLED == (ChannelConfigPtr->Wakeup))
    {
      /* Configure the timings after the wakeup detection/generation */
      /* [cover parentID={639B5194-5EFC-470e-8B95-7C6C0ECEDEB4}]
          [/cover] */
      Lin_17_AscLin_lHwConfigAfterWakeup(HwUnit);
    }
    #endif

    /* [cover parentID={21E59C47-7D7B-4b70-9664-536266661B70}]
        [/cover] */
    Lin_17_AscLin_lHwSendWakeupPulse(HwUnit);
  }
  return RetVal;
}

/*******************************************************************************
** Traceability :[cover parentID={508EA393-BC0C-4a41-B45B-F1DA3E2CE186}] **
**                           [/cover]                                     **
**                                                                            **
** Syntax : Std_ReturnType Lin_17_AscLin_WakeupInternal( uint8 Channel )      **
** [/cover]                                                                   **
**                                                                            **
** Service ID:      0xB                                                       **
**                                                                            **
** Sync/Async:      Asynchronous                                              **
**                                                                            **
** Reentrancy:      non reentrant                                             **
**                                                                            **
** Parameters (in): Channel    : LIN channel to be addressed                  **
**                                                                            **
** Parameters (out):none                                                      **
**                                                                            **
** Return value:    E_OK     :Wake-up request has been accepted               **
**                  E_NOT_OK :Wake-up request has not been accepted,          **
**                            development or production error occurred        **
**                                                                            **
** Description      : This service Sets the channel state to                  **
**                    LIN_CH_OPERATIONAL without generating a wake up pulse.  **
**                                                                            **
**     Note :       The LIN channel shall be in the LIN_CH_SLEEP state when   **
**                  this service will be called.                              **
*******************************************************************************/
Std_ReturnType Lin_17_AscLin_WakeupInternal(const uint8 Channel)
{
  #if (LIN_17_ASCLIN_GLOBAL_CHANNEL_WAKEUP_SUPPORT == STD_ON)
  const Lin_17_AscLin_ChannelType   *ChannelConfigPtr;
  uint8 HwUnit;
  #endif
  Std_ReturnType  RetVal;

  /* [cover parentID={F8E7A629-0FB8-4720-BB68-2F826450A548}]
      [/cover] */
  #if (LIN_17_ASCLIN_DEV_ERROR_DETECT == STD_ON)
  /* if the channel, UnInit parameters is invalid */
  /* [cover parentID={A29B579E-3A6B-40f0-BAC7-4E565FF05443}]
      [/cover] */
  RetVal = Lin_17_AscLin_lGetDetStatus                                         \
   (                                                                           \
    Channel,LIN_17_ASCLIN_SID_WAKEUPINTERNAL                                   \
   );

  /* Check for the channel state machine in Sleep state */
  /* [cover parentID={772504A5-6089-408d-8C12-1A741C937021}]
     [/cover] */
  if ((RetVal == E_OK)&& (!(Lin_17_AscLin_ChannelInfo[Channel].State ==        \
     LIN_17_ASCLIN_WAKEUP_WAIT_I)))
  {
    /* Report to  DET */
    /* [cover parentID={E4BC9FC5-C30A-4771-9D5F-17F89591E6C8}]
       [/cover] */
    Det_ReportError(
      LIN_17_ASCLIN_MODULE_ID,
      LIN_17_ASCLIN_INSTANCE_ID,
      LIN_17_ASCLIN_SID_WAKEUPINTERNAL,
      LIN_17_ASCLIN_E_STATE_TRANSITION
    );

    RetVal = E_NOT_OK;

  }
  /* [cover parentID={994823DF-74CC-4699-9DAF-F72C3B6B33B5}]
      [/cover] */
  if (RetVal == E_OK)
  #else
  /* [cover parentID={CC364EC5-4298-49a9-874C-205DE44F2DD8}]
      [/cover] */
  RetVal = E_OK;
  if (Lin_17_AscLin_ChannelInfo[Channel].State == LIN_17_ASCLIN_WAKEUP_WAIT_I)
  #endif  /* (LIN_17_ASCLIN_DEV_ERROR_DETECT == STD_ON) */
  {
    /* Change LIN state to LIN_17_ASCLIN_CH_INIT_I */
    /* [cover parentID={0C877D48-6AD3-4707-AD2C-E5B0E10D4A57}]
        Change LIN state to operational [/cover] */
    /* [cover parentID={639B5194-5EFC-470e-8B95-7C6C0ECEDEB4}]
            [/cover] */
    /* [cover parentID={D1D5A830-D9E3-4e36-B49E-D845B5E1AC7E}]
      [/cover] */
    Lin_17_AscLin_ChannelInfo[Channel].State = LIN_17_ASCLIN_CH_INIT_I;
    Lin_17_AscLin_ChannelInfo[Channel].Sleep =                                 \
      (uint8)LIN_17_ASCLIN_SLEEP_NOT_REQ;

    /* [cover parentID={639B5194-5EFC-470e-8B95-7C6C0ECEDEB4}]
            [/cover] */
    #if (LIN_17_ASCLIN_GLOBAL_CHANNEL_WAKEUP_SUPPORT == STD_ON)
    ChannelConfigPtr = &(Lin_17_AscLin_kConfigPtr->ChannelConfigPtr[Channel]);
    /* Extract Hw Module */
    HwUnit = ChannelConfigPtr->HwModule;
    if (LIN_17_ASCLIN_CHANNEL_WAKEUP_ENABLED == (ChannelConfigPtr->Wakeup))
    {
      /* Configure the timings after the wakeup detection/generation */
      /* [cover parentID={639B5194-5EFC-470e-8B95-7C6C0ECEDEB4}]
              [/cover] */
      Lin_17_AscLin_lHwConfigAfterWakeup(HwUnit);
    }
    #endif
  }
  return RetVal;
}

/*******************************************************************************
** Traceability :[cover parentID={022145B5-9509-49ed-B308-8A082B02D270}]      **
**                           [/cover]                                         **
** Syntax : Lin_StatusType Lin_17_AscLin_GetStatus                            **
                                           ( uint8 Channel, uint8 **LinSduPtr)**
** [/cover]                                                                   **
**                                                                            **
** Service ID:      0x08                                                      **
**                                                                            **
** Sync/Async:      Synchronous                                               **
**                                                                            **
** Reentrancy:      non reentrant                                             **
**                                                                            **
** Parameters (in): Channel    : LIN channel to be addressed                  **
**                                                                            **
** Parameters (out):LinSduPtr : Reference to a shadow buffer or memory mapped **
**                               LIN Hardware receive buffer where the current**
**                               SDU is stored                                **
**                                                                            **
** Return value:    LIN_NOT_OK  : Development or Production error occurred    **
**                  LIN_TX_OK   : Successful transmission                     **
**                  LIN_TX_BUSY : Ongoing Transmission (Header or Response)   **
**                  LIN_TX_HEADER_ERROR :                                     **
**                      Erroneous header transmission such as:                **
**                         - Mismatch between sent and read back data         **
**                         - Identifier parity error or                       **
**                         - Physical bus error                               **
**                  LIN_TX_ERROR: Erroneous transmission                      **
**                         - Mismatch between sent and read back data         **
**                         - Physical bus error                               **
**                  LIN_RX_OK   : Reception of correct response               **
**                  LIN_RX_BUSY : Ongoing reception: at least one response    **
**                                byte has been received, but the checksum    **
**                                byte has not been received                  **
**                  LIN_RX_ERROR: Erroneous reception                         **
**                                - Framing error                             **
**                                - Data error                                **
**                                - Checksum error or Short response          **
**                  LIN_RX_NO_RESPONSE : No reception                         **
**                  LIN_CH_OPERATIONAL : Normal operation; the related LIN    **
**                                    channel is ready to transmit next header**
**                                    No data from previous frame available   **
**                                   (e.g. after initialization)              **
**                  LIN_SLEEP : Sleep mode operation; in this mode wake-up    **
**                                 detection from slave nodes is enabled      **
**                  LIN_TX_HEADER_TIMEOUT_ERROR : Header timeout occured      **
**                  LIN_RX_RESPONSE_TIMEOUT_ERROR : Response timeout occured  **
**                                                                            **
** Description :    Indicates the current transmission, reception or          **
**                  operation status of the LIN driver                        **
**                                                                            **
**                  If a SDU has been successfully received, the SDU          **
**                  will be stored in a shadow buffer or memory mapped LIN    **
**                  Hardware receive buffer referenced by Lin_SduPtr.         **
**                  The buffer will only be valid and must be read until the  **
**                  next Lin_17_AscLin_SendFrame function call.               **
**                  The LIN driver shall provide a function to                **
**                  interrogate the status of the current frame transmission  **
**                  request ((Lin_17_AscLin_GetStatus)                        **
**                  The LIN driver shall provide a service for                **
**                  checking the current state of each LIN channel under its  **
**                  control (( Lin_17_AscLin_GetStatus)                       **
**                  LIN operation states for a LIN channel or frame,          **
**                  as returned by the API service Lin_17_AscLin_GetStatus()  **
**                                                                            **
*******************************************************************************/
/*CYCLOMATIC_Lin_17_AscLin_GetStatus_JUSTIFICATION: The complexity is
   due to the different switch cases for the channel state. Adding in the same
   API is done for readability.*/
Lin_StatusType Lin_17_AscLin_GetStatus
(
  const uint8 Channel,
  uint8 ** const LinSduPtr
)
{
  Lin_StatusType  Status;
  Lin_17_AscLin_IntStatusType    CurrentState;
  const Lin_17_AscLin_ChannelType   *ChannelConfigPtr;
  uint8 HwUnit;
  uint8 FifoValue;
  const Ifx_ASCLIN* HwModulePtr;
  #if (LIN_17_ASCLIN_INTERRUPT_DISABLED == STD_ON)
  Lin_17_AscLin_IntStatusType CheckErr;
  uint32 HwErrorFlags;
  #endif

  #if (LIN_17_ASCLIN_DEV_ERROR_DETECT == STD_ON)
  Std_ReturnType   DetStatus;
  #endif

  /* [cover parentID={BAB7E1C2-FF99-40f3-A409-88DA62FCA1A9}]
      [/cover] */
  #if (LIN_17_ASCLIN_DEV_ERROR_DETECT == STD_ON)
  /* if the channel, UnInit parameters is invalid */
  /* [cover parentID={4D966324-7633-401c-8063-AB278B7EE84F}]
      [/cover] */
  DetStatus = Lin_17_AscLin_lGetDetStatus(Channel, LIN_17_ASCLIN_SID_GETSTATUS);

  /* Check for the channel state machine in Sleep state */
  /* [cover parentID={872EE24C-1E2B-4be9-AEB1-686180DA4B42}]
      [/cover] */
  if ((DetStatus == E_OK) &&(LinSduPtr == NULL_PTR) &&
  (Lin_17_AscLin_ChannelInfo[Channel].State ==                                 \
      LIN_17_ASCLIN_RECEIVE_COMPLETE_I))
  {
    /* Report to  DET */
    /* [cover parentID={630FF490-78A7-40b4-BD20-9D354A13A1BF}]
        [/cover] */
    Det_ReportError(
      LIN_17_ASCLIN_MODULE_ID,
      LIN_17_ASCLIN_INSTANCE_ID,
      LIN_17_ASCLIN_SID_GETSTATUS,
      LIN_17_ASCLIN_E_PARAM_POINTER
    );

    Status = LIN_NOT_OK;
  }
  /* [cover parentID={BDAED758-B766-494f-92CB-3B54A62F8FBB}]
    [/cover] */
  else if (DetStatus != E_OK)
  {
    Status = LIN_NOT_OK;
  }
  else
  {
    Status = LIN_OPERATIONAL;
  }
  /* [cover parentID={B737ADF0-531D-405a-B478-0FC43C4B8D1F}]
    [/cover] */
  if (Status != LIN_NOT_OK)
  #endif  /* (LIN_17_ASCLIN_DEV_ERROR_DETECT == STD_ON) */
  {
    ChannelConfigPtr = &(Lin_17_AscLin_kConfigPtr->ChannelConfigPtr[Channel]);

    /* Extract HwUnit */
    HwUnit = ChannelConfigPtr->HwModule;

    HwModulePtr = Lin_17_AscLin_AscLinRegAddr[HwUnit];

    /* If global interrupts are disabled */
    /* [cover parentID={D75E246D-0169-491e-8F2C-13D748B17109}]
       [/cover] */
    /* [cover parentID={B773D1E5-8B30-49ea-AFFD-AF9C1B138B8F}]
       [/cover] */
    #if (LIN_17_ASCLIN_INTERRUPT_DISABLED == STD_ON)
    HwErrorFlags = HwModulePtr->FLAGS.U;

    CheckErr = Lin_17_AscLin_lGetIntErrorStatus(HwErrorFlags, Channel);

    /* [cover parentID={CF2DBE7D-9BA7-44cc-8BDF-812030ECDAAD}]
         [/cover] */
    if (CheckErr !=  LIN_17_ASCLIN_CH_INIT_I)
    {
      Lin_17_AscLin_lHandleErr(HwUnit);
      Lin_17_AscLin_ChannelInfo[Channel].State = CheckErr;
    }
    else if (Lin_17_AscLin_ChannelInfo[Channel].Drc == LIN_MASTER_RESPONSE)
    {
      if (((HwErrorFlags & ((uint32)LIN_17_ASCLIN_FLAGSREG_TR)) !=             \
          LIN_17_ASCLIN_DISABLE_FLAG))
      {
        Lin_17_AscLin_lHandleTx(HwUnit);
      }
    }
    else if (Lin_17_AscLin_ChannelInfo[Channel].Drc == LIN_SLAVE_RESPONSE)
    {
      if(((HwErrorFlags & ((uint32)LIN_17_ASCLIN_FLAGSREG_RR)) !=              \
          LIN_17_ASCLIN_DISABLE_FLAG))
      {
        Lin_17_AscLin_lHandleRx(HwUnit);
      }
    }
    else
    {
      if(((HwErrorFlags & ((uint32)LIN_17_ASCLIN_FLAGSREG_TH)) !=
          LIN_17_ASCLIN_DISABLE_FLAG))
      {
        Lin_17_AscLin_lHandleTx(HwUnit);
      }
    }
    #endif

    CurrentState = Lin_17_AscLin_ChannelInfo[Channel].State;

    /* [cover parentID={E5F47BAE-30C8-4960-90A0-2258B37D3ED2}]
          [/cover] */
    switch(CurrentState)
    {
      /* [cover parentID={C4AE0BCE-259D-427d-B6DE-DF2229E30419}]
            [/cover] */
      case LIN_17_ASCLIN_MASTER_TX_COMPLETE_I:
      {
        /* Successful transmission */
        /* [cover parentID={1E1C39C0-D3F0-4845-A722-8B5AA75DBC3C}]
            [/cover] */
        Status = LIN_TX_OK;
        break;
      }
      /* [cover parentID={B6DE8101-ACED-44db-B120-5CC5A66174AD}]
          [/cover] */
      case LIN_17_ASCLIN_WAKEUP_WAIT_I:
      {
        /* Lin is in Sleep */
        /* [cover parentID={47FD79A9-8C1B-48c3-85FD-A15789A5A5D8}]
            [/cover] */
        /* [cover parentID={C6E1B316-290D-43d5-8DBE-6D3E1639F9F0}]
            [/cover] */
        Status = LIN_CH_SLEEP;
        break;
      }
      /* [cover parentID={639B5194-5EFC-470e-8B95-7C6C0ECEDEB4}]
            [/cover] */
      case LIN_17_ASCLIN_SLEEP_PENDING_I:
      {
        /* Lin is in Sleep */
        /* [cover parentID={639B5194-5EFC-470e-8B95-7C6C0ECEDEB4}]
            [/cover] */
        /* [cover parentID={C6E1B316-290D-43d5-8DBE-6D3E1639F9F0}]
            [/cover] */
        Status = LIN_CH_SLEEP;
        Lin_17_AscLin_ChannelInfo[Channel].State =                             \
           LIN_17_ASCLIN_WAKEUP_WAIT_I;
        break;
      }
      /* [cover parentID={B4A4A4AF-C3A1-4188-9397-8094B83B6C6D}]
          [/cover] */
      case LIN_17_ASCLIN_RECEIVE_COMPLETE_I:
      {
        /* [cover parentID={EA9AC102-1367-4b45-B0AC-A5C6D6DE8950}]
            [/cover] */
        /* Successful reception */
        Status = LIN_RX_OK;
        /* Assign the receive buffer pointer */
        *LinSduPtr = Lin_17_AscLin_ResponseBuffer[Channel];
        break;
      }
      /* [cover parentID={EF58A14B-DF2F-4c4e-922A-F1C1FA4B1140}]
          [/cover] */
      case LIN_17_ASCLIN_TX_HEADER_ERROR_I:
      {
        /* erroneous header transmission */
        /* [cover parentID={8416B444-B0DB-4081-B7ED-9F93221448B5}]
            [/cover] */
        Status = LIN_TX_HEADER_ERROR;
        break;
      }
      /* [cover parentID={3C6F26DD-AFE9-4a42-A8BE-8BEA30A89467}]
          [/cover] */
      case LIN_17_ASCLIN_TX_ERROR_I:
      {
        /* Erroneous transmission */
        /* [cover parentID={B9F9310E-A6CA-459d-985B-426B557CE771}]
             [/cover] */
        Status = LIN_TX_ERROR;
        break;
      }
      /* [cover parentID={9E80B047-235E-4de2-8A05-BA9EBA2B98F0}]
          [/cover] */
      case LIN_17_ASCLIN_RX_ERROR_I:
      {
        /* Erroneous reception */
        /* [cover parentID={F2FA01D6-0FDD-4219-997A-AFF04EC74708}]
             [/cover] */
        Status = LIN_RX_ERROR;
        break;
      }
      /* [cover parentID={D54ECE89-BBD0-4fcf-BA61-8DB79AE34D5C}]
          [/cover] */
      case LIN_17_ASCLIN_RX_NO_RESPONSE_I:
      {
        /* No response received */
        /* [cover parentID={F91014F3-C578-422e-936A-5CAD4DBFB1A8}]
             [/cover] */
        Status = LIN_RX_NO_RESPONSE;
        break;
      }
      /* [cover parentID={25375049-A985-4f1a-81A3-C02CF37EB4D3}]
            [/cover] */
      case LIN_17_ASCLIN_SEND_HEADER_I:
      {
        /* [cover parentID={6FD24265-EB40-4806-B3E0-F64C47AFC3DB}]
          [/cover] */
        Status = LIN_TX_BUSY;
        /* Read the RXFIFO FILL value from hw */
        FifoValue = HwModulePtr->RXFIFOCON.B.FILL;

        /* [cover parentID={5136AEF0-3FD9-425f-BAC4-DB5C0971A06C}]
               [/cover] */
        if (LIN_17_ASCLIN_RXFIFOVAL_IDONLY < FifoValue)
        {
          /* ID + atleast 1 response data byte received */
          /* [cover parentID={17FBC9E3-F5BB-4f71-B104-34BAE9DADE9A}]
               [/cover] */
          Status = LIN_RX_BUSY;
        }
        /* [cover parentID={DAE48E36-55E7-4292-AB4F-05CCFC21776D}]
             [/cover] */
        else if (LIN_17_ASCLIN_RXFIFOVAL_IDONLY == FifoValue )
        {
          /* Only ID received. No response data byte received */
          /* [cover parentID={1BAD64EC-0D74-4cb4-948F-841DAA41CCDE}]
               [/cover] */
          Status = LIN_RX_NO_RESPONSE;
        }
        else
        { /* Empty Else */
        }

        break;
      }
      /* [cover parentID={FE734954-354F-4251-A028-880701925535}]
           [/cover] */
      default:
      {
        /* Default case is Normal operation */
        /* [cover parentID={ACE4274C-7B68-43da-85D2-E140CB84712A}]
            [/cover] */
        Status = LIN_OPERATIONAL;
        break;
      }

    }
  }
  /* [cover parentID={4144ED6C-404A-48df-A98E-02544BB71B93}]
    [/cover] */
  return Status;
}
#if (LIN_17_ASCLIN_INTERRUPT_DISABLED == STD_OFF)
/*******************************************************************************
** Traceability :[cover parentID={2CB4EE2F-66E6-4169-9A87-C3E729D3BBB7}]      **
**                        [/cover]                                            **
** Syntax :          void Lin_17_AscLin_IsrReceive( uint8  HwUnit)            **
** [/cover]                                                                   **
**                                                                            **
** Service ID:       none                                                     **
**                                                                            **
** Sync/Async:       Synchronous                                              **
**                                                                            **
** Reentrancy:       reentrant                                                **
**                                                                            **
** Parameters (in):  HwUnit : Represents Hw Module number                     **
**                                                                            **
**                                                                            **
** Parameters (out): none                                                     **
**                                                                            **
** Return value:     none                                                     **
**                                                                            **
** Description :     This ISR will be called whenever the Slave response data **
**                   is completely received by the ASCLIN w/o any errors      **
**                                                                            **
*******************************************************************************/
void Lin_17_AscLin_IsrReceive(const uint8  HwUnit)
{

  uint32 HwErrorFlags;

  const Ifx_ASCLIN*  HwModulePtr;
  HwModulePtr = Lin_17_AscLin_AscLinRegAddr[HwUnit];

  HwErrorFlags = HwModulePtr->FLAGS.U;

  /*[cover parentID={06FCE003-905F-4af7-9273-1926F4E52C3E}][/cover]*/
  /*[cover parentID={AB1D241E-CCCC-4bc5-B21C-0E21BCCA91BF}][/cover]*/
  if((HwErrorFlags & ((uint32)LIN_17_ASCLIN_FLAGSREG_RR)) !=                   \
        LIN_17_ASCLIN_DISABLE_FLAG)
  {
    Lin_17_AscLin_lHandleRx(HwUnit);
  }
}
#endif
/*******************************************************************************
** Traceability :[cover parentID={A2D519FC-40B7-4ce7-9F54-1060A2530D5B}]      **
**                        [/cover]                                            **
** Syntax :          static void Lin_17_AscLin_lHandleRx( uint8  HwUnit)      **
** [/cover]                                                                   **
**                                                                            **
** Service ID:       none                                                     **
**                                                                            **
** Sync/Async:       Synchronous                                              **
**                                                                            **
** Reentrancy:       reentrant                                                **
**                                                                            **
** Parameters (in):  HwUnit : Represents Hw Module number                     **
**                                                                            **
**                                                                            **
** Parameters (out): none                                                     **
**                                                                            **
** Return value:     none                                                     **
**                                                                            **
** Description :     This local function will be called whenever the Slave    **
                     response data is completely received by the ASCLIN w/o   **
                     any errors                                               **
**                                                                            **
*******************************************************************************/
static void Lin_17_AscLin_lHandleRx(const uint8  HwUnit)
{
  uint8  *RespPtr;
  uint8 Channel;
  uint8 Count;

  Ifx_ASCLIN*  HwModulePtr;
  HwModulePtr = Lin_17_AscLin_AscLinRegAddr[HwUnit];

  /* Extract the Channel */
  Channel =                                                                  \
      Lin_17_AscLin_kConfigPtr->Lin_17_AscLin_ChannelIdLookupPtr[HwUnit];
  /*[cover parentID={19BCC778-CF72-4f97-851B-AB6BB3021220}]
    [/cover]*/
  /* copy the Response buffer pointer to local variable */
  RespPtr = Lin_17_AscLin_ResponseBuffer[Channel];

  Count = Lin_17_AscLin_ChannelInfo[Channel].Dl;

  /*[cover parentID={94C8F60E-9EA5-4652-B9FE-3F58B3D5991D}]
    [/cover]*/
  /*[cover parentID={C972A71B-3B64-4dff-A4C7-07F63C93E7A6}][/cover]*/
  *RespPtr = (uint8)HwModulePtr->RXDATA.U;

  /* Copy the RX FIFO data to the given buffer */
  while(Count != LIN_17_ASCLIN_NUMBER_ZERO)
  {
    *RespPtr = (uint8)HwModulePtr->RXDATA.U;
    RespPtr++;
    Count--;
  }
  /* [cover parentID={5518F4F6-AF46-4b75-AC21-0215A43BA123}]
      [/cover] */
  /* [cover parentID={D2FF3221-EAF7-4308-A633-31E5897ABE77}]
      [/cover] */
  /* Flush the RX, TX FIFOs */
  HwModulePtr->TXFIFOCON.B.FLUSH = LIN_17_ASCLIN_ENABLE_FLAG;
  HwModulePtr->RXFIFOCON.B.FLUSH = LIN_17_ASCLIN_ENABLE_FLAG;

  /* Clear and disable all intr in FlagsEnable register */
  HwModulePtr->FLAGSCLEAR.U =
  LIN_17_ASCLIN_FLAGSCLEAR_MS_TX | LIN_17_ASCLIN_FLAGSCLEAR_MS_RX |
  LIN_17_ASCLIN_FLAGSCLEAR_MS_HO ;

  HwModulePtr->FLAGSENABLE.U = (uint32)LIN_17_ASCLIN_DISABLE_FLAG;

  /* Update the state */
  Lin_17_AscLin_ChannelInfo[Channel].State = LIN_17_ASCLIN_RECEIVE_COMPLETE_I;
}
#if (LIN_17_ASCLIN_INTERRUPT_DISABLED == STD_OFF)
/*******************************************************************************
** Traceability :[cover parentID={2842502A-E2A6-4d6d-8F06-82AAE3D96731}]      **
**                           [/cover]                                         **
** Syntax :          void Lin_17_AscLin_IsrTransmit( uint8  HwUnit)           **
** [/cover]                                                                   **
**                                                                            **
** Service ID:       none                                                     **
**                                                                            **
** Sync/Async:       Synchronous                                              **
**                                                                            **
** Reentrancy:       reentrant                                                **
**                                                                            **
** Parameters (in):  HwUnit : Represents Hw Module number                     **
**                                                                            **
**                                                                            **
** Parameters (out): none                                                     **
**                                                                            **
** Return value:     none                                                     **
**                                                                            **
** Description :     This ISR will be called whenever the response data       **
**                   is successfully transmitted by the ASCLIN w/o any errors **
**                                                                            **
*******************************************************************************/
void Lin_17_AscLin_IsrTransmit(const uint8  HwUnit)
{
  uint32 HwErrorFlags;
  const Ifx_ASCLIN*  HwModulePtr;

  HwModulePtr = Lin_17_AscLin_AscLinRegAddr[HwUnit];

  HwErrorFlags = HwModulePtr->FLAGS.U;

  /* [cover parentID={193A941A-FA09-4c36-AA09-826BC8CE1C8F}]
      [/cover] */
  /* [cover parentID={0242755F-CCBB-4fe5-AD24-54D9FC57A86F}]
      [/cover] */
  if(((HwErrorFlags & ((uint32)LIN_17_ASCLIN_FLAGSREG_TH)) !=                  \
    LIN_17_ASCLIN_DISABLE_FLAG) || ((HwErrorFlags &                            \
    ((uint32)LIN_17_ASCLIN_FLAGSREG_TR)) != LIN_17_ASCLIN_DISABLE_FLAG))
  {
    Lin_17_AscLin_lHandleTx(HwUnit);
  }
}
#endif
/*******************************************************************************
** Traceability :[cover parentID={3E5700B0-6D15-46ea-8D42-3C2177F78CE5}]      **
**                           [/cover]                                         **
** Syntax :          static void Lin_17_AscLin_lHandleTx( uint8  HwUnit)      **
** [/cover]                                                                   **
**                                                                            **
** Service ID:       none                                                     **
**                                                                            **
** Sync/Async:       Synchronous                                              **
**                                                                            **
** Reentrancy:       reentrant                                                **
**                                                                            **
** Parameters (in):  HwUnit : Represents Hw Module number                     **
**                                                                            **
**                                                                            **
** Parameters (out): none                                                     **
**                                                                            **
** Return value:     none                                                     **
**                                                                            **
** Description :     This ISR will be called whenever the response data       **
**                   is successfully transmitted by the ASCLIN w/o any errors **
**                                                                            **
*******************************************************************************/
static void Lin_17_AscLin_lHandleTx(const uint8  HwUnit)
{
    #if (LIN_17_ASCLIN_GLOBAL_CHANNEL_WAKEUP_SUPPORT == STD_ON)
    const Lin_17_AscLin_ChannelType   *ChannelConfigPtr;
    #endif
    uint8 Channel;
    Ifx_ASCLIN*  HwModulePtr;

  HwModulePtr = Lin_17_AscLin_AscLinRegAddr[HwUnit];
     /* Extract the Channel */
    /* [cover parentID={25E1E2B9-93E8-43ee-BB4D-4D735275EAD8}]
        [/cover] */
    Channel =                                                                  \
         Lin_17_AscLin_kConfigPtr->Lin_17_AscLin_ChannelIdLookupPtr[HwUnit];
    /* [cover parentID={5518F4F6-AF46-4b75-AC21-0215A43BA123}]
      [/cover] */
    /* Flush the RX, TX FIFOs */
    HwModulePtr->TXFIFOCON.B.FLUSH = LIN_17_ASCLIN_ENABLE_FLAG;
    HwModulePtr->RXFIFOCON.B.FLUSH = LIN_17_ASCLIN_ENABLE_FLAG;

    /* Clear and disable all intr in FlagsEnable register */
    HwModulePtr->FLAGSCLEAR.U =
    LIN_17_ASCLIN_FLAGSCLEAR_MS_TX | LIN_17_ASCLIN_FLAGSCLEAR_MS_RX |
    LIN_17_ASCLIN_FLAGSCLEAR_MS_HO ;

    HwModulePtr->FLAGSENABLE.U = (uint32)LIN_17_ASCLIN_DISABLE_FLAG;

    /* [cover parentID={7AC758FD-75DF-4cfb-B952-2685ED8B8CCC}]
          [/cover] */
    if (Lin_17_AscLin_ChannelInfo[Channel].Sleep !=                            \
      (uint8)LIN_17_ASCLIN_SLEEP_REQ)
    {
      /* If the Sleep is Not requested,
      then update the state to Transmit completed */
      /* [cover parentID={CC2BAFE1-A7C2-4535-9E63-B9D9B52BBB9C}]
          [/cover] */
      /* [cover parentID={1E9CC33A-2372-4192-A962-F37B5E0AD56D}]
          [/cover] */
      Lin_17_AscLin_ChannelInfo[Channel].State =                               \
          LIN_17_ASCLIN_MASTER_TX_COMPLETE_I;
    }
    else
    {
      /* Disable the Tx Outlet */
      HwModulePtr->TXFIFOCON.B.ENO = LIN_17_ASCLIN_DISABLE_FLAG;

      /* [cover parentID={01BA7042-867F-4811-B6A2-0729C4583CED}]
          [/cover] */
      #if (LIN_17_ASCLIN_GLOBAL_CHANNEL_WAKEUP_SUPPORT == STD_ON)
      ChannelConfigPtr = &(Lin_17_AscLin_kConfigPtr->ChannelConfigPtr[Channel]);
      if (LIN_17_ASCLIN_CHANNEL_WAKEUP_ENABLED == (ChannelConfigPtr->Wakeup))
      {
        /* Configure the timings for wakeup detection */
        /* [cover parentID={2694425A-8374-4cb4-ADA3-076C20EEAFAE}]
            [/cover] */
        Lin_17_AscLin_lHwConfigWakeup(HwUnit,
        ChannelConfigPtr->TimingConfig.HwWakeupIocrDepth,
        ChannelConfigPtr->TimingConfig.HwWakeupBitconPrescalar);
      }
      #endif
    }
}
#if (LIN_17_ASCLIN_INTERRUPT_DISABLED == STD_OFF)
/*******************************************************************************
** Traceability :[cover parentID={75CFD809-326C-4952-A2FF-5526AB7CA43B}] **
**                  [/cover]                                              **
** Syntax :          void Lin_17_AscLin_IsrError( uint8  HwUnit)              **
** [/cover]                                                                   **
**                                                                            **
** Service ID:       none                                                     **
**                                                                            **
** Sync/Async:       Synchronous                                              **
**                                                                            **
** Reentrancy:       reentrant                                                **
**                                                                            **
** Parameters (in):  HwUnit : Represents Hw Module number                     **
**                                                                            **
**                                                                            **
** Parameters (out): none                                                     **
**                                                                            **
** Return value:     none                                                     **
**                                                                            **
** Description :     This ISR will be called whenever there is an data        **
**                   transmission or reception error
**                   or a wakeup interrupt in ASCLIN                          **
*******************************************************************************/
void Lin_17_AscLin_IsrError(const uint8 HwUnit)
{
  #if (LIN_17_ASCLIN_GLOBAL_CHANNEL_WAKEUP_SUPPORT == STD_ON)
  const Lin_17_AscLin_ChannelType   *ChannelConfigPtr;
  #endif

  #if (LIN_17_ASCLIN_INTERRUPT_DISABLED == STD_OFF)

  uint32 HwErrorFlags;
  uint8 Channel;
  Ifx_ASCLIN*  HwModulePtr;
  HwModulePtr = Lin_17_AscLin_AscLinRegAddr[HwUnit];

  /* Extract the Channel */
  Channel =                                                                    \
      Lin_17_AscLin_kConfigPtr->Lin_17_AscLin_ChannelIdLookupPtr[HwUnit];
  HwErrorFlags = HwModulePtr->FLAGS.U;

  /* if Channel has NOT requested Sleep */
  /* [cover parentID={797B6752-1D88-47b5-B5D0-8729D14A6EA0}]
      [/cover] */
  /* [cover parentID={43DD1352-7E95-47ce-B2A9-0C7F04132716}]
      [/cover] */
  if (Lin_17_AscLin_ChannelInfo[Channel].Sleep !=                              \
    (uint8)LIN_17_ASCLIN_SLEEP_REQ)
  {
    /* Get the Error Status and update internal state */
    /* [cover parentID={9591230D-A273-4891-BC4D-414DD0427872}]
        [/cover] */
    Lin_17_AscLin_ChannelInfo[Channel].State =                                 \
    Lin_17_AscLin_lGetIntErrorStatus(HwErrorFlags, Channel);
  }
  else
  {
    /* Wakeup intr (no error) */
    /* [cover parentID={CF5A7105-24E3-44f6-B57D-1927A3DA9E2C}]
         [/cover] */
    if ( ((HwErrorFlags & LIN_17_ASCLIN_FLAGSREG_FED ) !=                      \
        LIN_17_ASCLIN_DISABLE_FLAG))
    {
      /* [cover parentID={F8AB2E2D-0D1C-481a-9A18-BD807C830DCC}]
          [/cover] */
      #if (LIN_17_ASCLIN_GLOBAL_CHANNEL_WAKEUP_SUPPORT == STD_ON)
      ChannelConfigPtr = &(Lin_17_AscLin_kConfigPtr->ChannelConfigPtr[Channel]);
      /* Configure the timings after the wakeup detection */
      /* [cover parentID={639B5194-5EFC-470e-8B95-7C6C0ECEDEB4}]
            [/cover] */
      Lin_17_AscLin_lHwConfigAfterWakeup(HwUnit);
      /* [cover parentID={4E13C3D9-D6A6-4e42-9466-FE3A9A09F874}]
          [/cover] */
      EcuM_CheckWakeup(                                                        \
       (uint32)LIN_17_ASCLIN_ENABLE_FLAG << (ChannelConfigPtr->WakeupSourceId));
      #endif
    }
    else
    {
      /* Disable the Tx Outlet */
      HwModulePtr->TXFIFOCON.B.ENO = LIN_17_ASCLIN_DISABLE_FLAG;
      /* [cover parentID={F8AB2E2D-0D1C-481a-9A18-BD807C830DCC}]
          [/cover] */
      #if (LIN_17_ASCLIN_GLOBAL_CHANNEL_WAKEUP_SUPPORT == STD_ON)
      ChannelConfigPtr = &(Lin_17_AscLin_kConfigPtr->ChannelConfigPtr[Channel]);
      /* Configure the timings for wakeup detection */
      /* [cover parentID={CBC4BCE2-7865-45c2-A7A3-6D5417A30618}]
          [/cover] */
      Lin_17_AscLin_lHwConfigWakeup(HwUnit,                                    \
      ChannelConfigPtr->TimingConfig.HwWakeupIocrDepth,                        \
      ChannelConfigPtr->TimingConfig.HwWakeupBitconPrescalar);
      #endif
    }
  }
  #endif
      /* [cover parentID={5518F4F6-AF46-4b75-AC21-0215A43BA123}]
          [/cover] */
   Lin_17_AscLin_lHandleErr(HwUnit);
}
#endif
/*******************************************************************************
** Traceability :[cover parentID={1F2EE594-92D5-41f6-8D58-C7F3A3A69817}]      **
**                        [/cover]                                            **
** Syntax :          static void Lin_17_AscLin_lHandleErr( uint8  HwUnit)     **
** [/cover]                                                                   **
**                                                                            **
** Service ID:       none                                                     **
**                                                                            **
** Sync/Async:       Synchronous                                              **
**                                                                            **
** Reentrancy:       reentrant                                                **
**                                                                            **
** Parameters (in):  HwUnit : Represents Hw Module number                     **
**                                                                            **
**                                                                            **
** Parameters (out): none                                                     **
**                                                                            **
** Return value:     none                                                     **
**                                                                            **
** Description :     This ISR will be called whenever there is an data        **
**                   transmission or reception error
**                   or a wakeup interrupt in ASCLIN                          **
*******************************************************************************/
static void Lin_17_AscLin_lHandleErr( uint8  HwUnit)
{
    Ifx_ASCLIN*  HwModulePtr;
  HwModulePtr = Lin_17_AscLin_AscLinRegAddr[HwUnit];

  /* Flush the RX, TX FIFOs */
  /* [cover parentID={5518F4F6-AF46-4b75-AC21-0215A43BA123}]
      [/cover] */
  /* [cover parentID={FFCC72F3-D47F-41a3-8D63-A9854F84C426}]
      [/cover] */
  HwModulePtr->TXFIFOCON.B.FLUSH = LIN_17_ASCLIN_ENABLE_FLAG;
  HwModulePtr->RXFIFOCON.B.FLUSH = LIN_17_ASCLIN_ENABLE_FLAG;

  /* Clear and disable all intr in FlagsEnable register */
  HwModulePtr->FLAGSCLEAR.U =
  LIN_17_ASCLIN_FLAGSCLEAR_MS_TX | LIN_17_ASCLIN_FLAGSCLEAR_MS_RX |
  LIN_17_ASCLIN_FLAGSCLEAR_MS_HO ;

  HwModulePtr->FLAGSENABLE.U = (uint32)LIN_17_ASCLIN_DISABLE_FLAG;

}
/*******************************************************************************
** Traceability :[cover parentID={11D8FCC9-EA25-4cc7-A512-F27C802D74F9}]      **
**                        [/cover]                                            **
** Syntax : LOCAL_INLINE Std_ReturnType Lin_17_AscLin_lGetDetStatus           **
**         (                                                                  **
**           uint8 Channel,                                                   **
**           uint8 ApiId                                                      **
**         )                                                                  **
**                                                                            **
** Service ID:  None                                                          **
**                                                                            **
** Sync/Async:  Synchronous                                                   **
**                                                                            **
** Reentrancy:  Re-entrant (for different channel Ids)                        **
**                                                                            **
** Parameters (in) :   Channel - ChannelId                                    **
**                     ApiId - API ID                                         **
**                                                                            **
** Parameters (out): None                                                     **
**                                                                            **
** Return value    : Returns DET status, E_OK or E_NOT_OK                     **
**                                                                            **
** Description : This Function returns the status of DET check                **
**                                                                            **
*******************************************************************************/
#if (LIN_17_ASCLIN_DEV_ERROR_DETECT == STD_ON)
LOCAL_INLINE Std_ReturnType Lin_17_AscLin_lGetDetStatus
(
  const uint8 Channel,
  const uint8 ApiId
)
{
  Std_ReturnType ReturnStatus;
  uint8 MaxChannel;

  /* [cover parentID={4E31C23B-01D3-46b8-8AB3-6E4F4DB3DE98}]
    [/cover] */
  ReturnStatus = E_OK;

  /* Check for LIN module initialization */
  /* [cover parentID={16D15282-4E18-4f1c-85A4-497CB13CEC1C}]
    [/cover] */
  /* [cover parentID={EAC6896A-D756-46f1-9BC8-00919A2518E0}]
    [/cover] */
  if (Lin_17_AscLin_ChannelInfo[LIN_17_ASCLIN_FIRST_CHANNEL].State == LIN_17_ASCLIN_CH_UNINIT_I)
  {
    /* Report to  DET */
    /* [cover parentID={4EDF95B0-21BE-4693-8886-D401DA59D2E4}]
        [/cover] */
    Det_ReportError(
      LIN_17_ASCLIN_MODULE_ID,
      LIN_17_ASCLIN_INSTANCE_ID,
      ApiId,
      LIN_17_ASCLIN_E_UNINIT
    );

    ReturnStatus = E_NOT_OK;
  }

  if (ReturnStatus == E_OK)
  {

    MaxChannel = Lin_17_AscLin_kConfigPtr->NoOfChannels;

    /* Check channel out of range*/
    /* [cover parentID={7F22A0B8-40DA-4fb1-9B71-E262A9B52F9E}]
        [/cover] */
    /* [cover parentID={EDB9A363-3AA1-43a1-9D0D-68F573ADFE64}]
        [/cover] */
    if ( Channel >= MaxChannel )
    {
      /* Report to  DET */
      /* [cover parentID={E1D7398F-8AEA-4e2c-AD82-BCDE054F120A}]
          [/cover] */
      Det_ReportError(
        LIN_17_ASCLIN_MODULE_ID,
        LIN_17_ASCLIN_INSTANCE_ID,
        ApiId,
        LIN_17_ASCLIN_E_INVALID_CHANNEL
      );

      ReturnStatus = E_NOT_OK;
    }
  }

  return ReturnStatus;
}
#endif /*(LIN_17_ASCLIN_DEV_ERROR_DETECT == STD_ON)*/


/*******************************************************************************
** Traceability :[cover parentID={BA1097B5-C2AC-4744-97AC-68CDAF23E632}]      **
**                           [/cover]                                         **
** Traceability :                                                             **
** Syntax           : static void Lin_17_AscLin_lHwInit                       **
**                      (                                                     **
**                         uint8 HwUnit,                                      **
**                         Lin_17_AscLin_ChannelTimingConfigType TimingConfig,**
**                         uint8 RxAlternatePinSelect                         **
**                      )                                                     **
**                                                                            **
** Service ID       : NA                                                      **
**                                                                            **
** Sync/Async       : Synchronous                                             **
**                                                                            **
** Reentrancy       : Non reentrant                                           **
**                                                                            **
** Parameters (in)  : HwUnit   : ASCLIN Hardware module no                    **
**                TimingConfig : Channel timing configuration parameter       **
**                RxAlternatePinSelect: Rx alternate pin selection            **
**                                                                            **
** Parameters (out) : None                                                    **
**                                                                            **
** Return value     : None                                                    **
**                                                                            **
** Description      : This function initialises the ASCLIN Hw module          **
*******************************************************************************/
static void Lin_17_AscLin_lHwInit
(
  const uint8 HwUnit,
  const Lin_17_AscLin_ChannelTimingConfigType TimingConfig,
  const uint8 RxAlternatePinSelect
)
{
  Ifx_ASCLIN*  HwModulePtr;
  uint32 TimeOutCount ;
  uint8 HeaderTimeOutVal;

  HwModulePtr = Lin_17_AscLin_AscLinRegAddr[HwUnit];

  /* Disable the Clock source. */
  HwModulePtr->CSR.B.CLKSEL = LIN_17_ASCLIN_CSRREG_CLKSEL_NOCLK;

  TimeOutCount = LIN_17_ASCLIN_TIMEOUT_DURATION;
  /*Wait TW or poll for CSR.CON = 0*/
  /* [cover parentID={3831B2B5-BC7E-461f-9B3A-85054ED31C32}]
      [/cover] */
  while ((HwModulePtr->CSR.B.CON != LIN_17_ASCLIN_DISABLE_FLAG) &&             \
         (TimeOutCount > LIN_17_ASCLIN_NUMBER_ZERO))
  {
    TimeOutCount-- ;
  }

  /* Change to INIT mode */
  HwModulePtr->FRAMECON.B.MODE = LIN_17_ASCLIN_FRAMECON_INIT_MODE;

  /* Connect the Clock source */
  HwModulePtr->CSR.B.CLKSEL = LIN_17_ASCLIN_CSRREG_CLKSEL;

  TimeOutCount = LIN_17_ASCLIN_TIMEOUT_DURATION;
  /* provide delay of TW >= 4 * (1/fA) + 2 * (1/fCLC) clock cycles */
  /*Wait TW or poll for CSR.CON = 1*/
  while ((HwModulePtr->CSR.B.CON != LIN_17_ASCLIN_ENABLE_FLAG) &&              \
         (TimeOutCount > LIN_17_ASCLIN_NUMBER_ZERO))
  {
    TimeOutCount-- ;
  }

  /* Disable the Clock source. */
  HwModulePtr->CSR.B.CLKSEL = LIN_17_ASCLIN_CSRREG_CLKSEL_NOCLK;

  TimeOutCount = LIN_17_ASCLIN_TIMEOUT_DURATION;
  /* provide delay of  TW >= 4 * (1/fA) + 2 * (1/fCLC) clock cycles */
  /* [cover parentID={528C5F6D-B261-436f-8D34-34BB2840A1DC}]
      [/cover] */
  while ((HwModulePtr->CSR.B.CON != LIN_17_ASCLIN_DISABLE_FLAG) &&             \
         (TimeOutCount > LIN_17_ASCLIN_NUMBER_ZERO))
  {
    TimeOutCount-- ;
  }
  /* Change to LIN mode */
  HwModulePtr->FRAMECON.B.MODE = LIN_17_ASCLIN_FRAMECONREG_LIN_MODE;

  /* Lin mode is Master Mode */
  HwModulePtr->LIN.CON.B.MS = LIN_17_ASCLIN_LINCON_MASTER_ENABLE;

  /* [cover parentID={F1058C0B-9867-4981-9F09-9C59A6A3827C}]
      [/cover] */
  /* Configure the Baudrate parameters */
  HwModulePtr->BRG.B.NUMERATOR = TimingConfig.HwBrgNumerator;
  HwModulePtr->BRG.B.DENOMINATOR = TimingConfig.HwBrgDenominator;
  HwModulePtr->BITCON.B.PRESCALER = TimingConfig.HwBitconPrescalar;
  HwModulePtr->BITCON.B.OVERSAMPLING = LIN_17_ASCLIN_BITCONREG_OS_VAL;

  /* Digital Glitch Filter = OFF */
  HwModulePtr->IOCR.B.DEPTH = LIN_17_ASCLIN_IOCRREG_DEPTH_VAL;

  /* Configure the Sample mode, Sample point, Parity, Collision detection */
  HwModulePtr->BITCON.B.SM = LIN_17_ASCLIN_BITCONREG_SM_VAL;
  HwModulePtr->BITCON.B.SAMPLEPOINT = LIN_17_ASCLIN_BITCON_SP_VAL;
  HwModulePtr->FRAMECON.B.PEN = LIN_17_ASCLIN_FRAMECONREG_PEN_VAL;
  HwModulePtr->FRAMECON.B.CEN = LIN_17_ASCLIN_FRAMECONREG_CEN_VAL;

  /* STOP bit = 1 */
  HwModulePtr->FRAMECON.B.STOP = LIN_17_ASCLIN_FRAMECONREG_STOP_VAL;

  /* LIN Break Timer */
  HwModulePtr->LIN.BTIMER.B.BREAK = LIN_17_ASCLIN_LINBTIMER_BREAK_VAL;

  /* LEAD val i.e delay b/w end of break and start of Sync character */
  HwModulePtr->FRAMECON.B.LEAD = LIN_17_ASCLIN_FRAMECONREG_LEAD_VAL;

  /* IDLE value i.e Interbyte space or response space */
  HwModulePtr->FRAMECON.B.IDLE = TimingConfig.InterByteResponseSpace;

  /* Hw checksum enable, Checksum  injection to Rx FIFO disable */
  HwModulePtr->LIN.CON.B.CSEN = LIN_17_ASCLIN_LINCONREG_CSEN_VAL;
  HwModulePtr->LIN.CON.B.CSI = LIN_17_ASCLIN_LINCONREG_CSI_VAL;

  /* Header Timeout = 48 bit times + Interbyte Space + Lead value */
  HeaderTimeOutVal =                                                           \
    ((uint8)LIN_17_ASCLIN_LINHTIMER_HEADER_VAL +                               \
    TimingConfig.InterByteResponseSpace +                                      \
    (uint8)LIN_17_ASCLIN_FRAMECONREG_LEAD_VAL);

  HwModulePtr->LIN.HTIMER.B.HEADER = HeaderTimeOutVal;

  /* Configure the RX inlet, TX outlet width/s to 1 byte */
  /* [cover parentID={CF4574A7-B1B9-4dd2-9E14-B165D1120EF6}]
      [/cover] */
  HwModulePtr->TXFIFOCON.B.INW = LIN_17_ASCLIN_TXFIFOCONREG_INW_VAL;
  HwModulePtr->RXFIFOCON.B.OUTW = LIN_17_ASCLIN_RXFIFOCON_OUTW_VAL;

  HwModulePtr->IOCR.B.ALTI =  RxAlternatePinSelect;

  HwModulePtr->FRAMECON.B.MSB = LIN_17_ASCLIN_DISABLE_FLAG;
  HwModulePtr->LIN.CON.B.ABD = LIN_17_ASCLIN_DISABLE_FLAG;
  HwModulePtr->IOCR.B.LB =  LIN_17_ASCLIN_DISABLE_FLAG;

  /* Connect the Clock source */
  HwModulePtr->CSR.B.CLKSEL = LIN_17_ASCLIN_CSRREG_CLKSEL;

  TimeOutCount = LIN_17_ASCLIN_TIMEOUT_DURATION;
  /* provide delay of TW >= 4 * (1/fA) + 2 * (1/fCLC) clock cycles */
  /*Wait TW or poll for CSR.CON = 1*/
  while ((HwModulePtr->CSR.B.CON != LIN_17_ASCLIN_ENABLE_FLAG) &&              \
         (TimeOutCount > LIN_17_ASCLIN_NUMBER_ZERO))
  {
    TimeOutCount-- ;
  }
}

#if (LIN_17_ASCLIN_DEV_ERROR_DETECT == STD_ON)
/*******************************************************************************
** Traceability :[cover parentID={7CD6E79A-EAF5-4e41-A5E7-5228D90D3C37}]      **
**                        [/cover]                                            **
** Syntax : LOCAL_INLINE  Std_ReturnType Lin_17_AscLin_lInitDetCheck          **
**         (                                                                  **
**              const Lin_17_AscLin_ConfigType *Config                        **
**         )                                                                  **
**                                                                            **
** Service ID:  None                                                          **
**                                                                            **
** Sync/Async:  Synchronous                                                   **
**                                                                            **
** Reentrancy:  Re-entrant                                                    **
**                                                                            **
** Parameters (in) :  Config - Pointer to the config root.                    **
**                                                                            **
** Parameters (out): None                                                     **
**                                                                            **
** Return value    : Returns DET status, E_OK or E_NOT_OK                     **
**                                                                            **
** Description : This Function checks all the DETs for Lin_17_AscLin_Init API.**
**                                                                            **
*******************************************************************************/
LOCAL_INLINE  Std_ReturnType Lin_17_AscLin_lInitDetCheck
(
  const Lin_17_AscLin_ConfigType* const Config
)
{
  Std_ReturnType ErrorStatus;

  ErrorStatus = E_OK;

  /* Configuration pointer is null */
  /* [cover parentID={A390CE15-A292-4f72-A5E8-BD878E77E24D}]
    [/cover] */
  /* [cover parentID={4353DFB6-5EFC-457c-8100-01F4D4430B98}]
      [/cover] */
  if (Config == NULL_PTR)
  {
    /* Report to  DET invalid input pointer */
    /* [cover parentID={69D78BF4-425F-4742-82C0-D2CF8D7EBA7B}]
      [/cover] */
    Det_ReportError(
      LIN_17_ASCLIN_MODULE_ID,
      LIN_17_ASCLIN_INSTANCE_ID,
      LIN_17_ASCLIN_SID_INIT,
      LIN_17_ASCLIN_E_INVALID_POINTER
    );

    ErrorStatus = E_NOT_OK;
  }

  if (ErrorStatus == E_OK)
  {

    /* Check for LIN module initialization */
    /* [cover parentID={C515FBC1-8135-4ef1-BDC6-E6896FB59CAC}]
      [/cover] */
    /* [cover parentID={EBFDA74D-9805-43ca-9BE9-8A50158DC544}]
      [/cover] */
    if (Lin_17_AscLin_ChannelInfo[LIN_17_ASCLIN_FIRST_CHANNEL].State != LIN_17_ASCLIN_CH_UNINIT_I)
    {
      /* Report to  DET module is already initialized*/
      /* [cover parentID={186A3BD5-58C3-4408-9A36-706468258B72}]
        [/cover] */
      Det_ReportError(
        LIN_17_ASCLIN_MODULE_ID,
        LIN_17_ASCLIN_INSTANCE_ID,
        LIN_17_ASCLIN_SID_INIT,
        LIN_17_ASCLIN_E_STATE_TRANSITION
      );

      ErrorStatus = E_NOT_OK;
    }
  }

  return ErrorStatus;
}
#endif /*(LIN_17_ASCLIN_DEV_ERROR_DETECT == STD_ON)*/

/*******************************************************************************
** Traceability :[cover parentID={BFDAB12B-DC50-4853-8648-B1F3E36F7642}]      **
**                        [/cover]                                            **
** Syntax           : LOCAL_INLINE void Lin_17_AscLin_lHwInitKernelReg        **
**                      (uint8 HwUnit)                                        **
**                                                                            **
** Service ID       : NA                                                      **
**                                                                            **
** Sync/Async       : Synchronous                                             **
**                                                                            **
** Reentrancy       : Reentrant                                               **
**                                                                            **
** Parameters (in)  : HwUnit   : ASCLIN Hardware module no                    **
**                                                                            **
** Parameters (out) : None                                                    **
**                                                                            **
** Return value     : None                                                    **
**                                                                            **
** Description      : This function resets the Kernel                         **
*******************************************************************************/
LOCAL_INLINE void Lin_17_AscLin_lHwInitKernelReg(const uint8 HwUnit)
{
  uint32 WaitCount, RstStatus;
  Ifx_ASCLIN* HwModuleAddr;
  WaitCount = LIN_17_ASCLIN_KRST_TIMEOUT;
  HwModuleAddr = Lin_17_AscLin_AscLinRegAddr[HwUnit];

  /* [cover parentID={A194A83B-B657-42cf-99E2-B93652ACAB9E}]
    [/cover] */
  /* MISRA2012_RULE_11_3_JUSTIFICATION: cast performed between a pointer to
   * object type and a pointer to a different object type due to SFR access. */
  /* MISRA2012_RULE_11_8_JUSTIFICATION: SFR access. Since the input
   * argument for the API discards volatile keyword. No side effects foreseen
   * by violating this MISRA rule*/
  LIN_17_ASCLIN_INIT_DEINIT_WRITESAFETYENDINITPROTREG(                         \
    (uint32*)&HwModuleAddr->KRST0.U, LIN_17_ASCLIN_ENABLE_FLAG);

  /* MISRA2012_RULE_11_3_JUSTIFICATION: cast performed between a pointer to
  * object type and a pointer to a different object type due to SFR access. */
  /* MISRA2012_RULE_11_8_JUSTIFICATION: SFR access. Since the input
   * argument for the API discards volatile keyword. No side effects foreseen
   * by violating this MISRA rule*/
  LIN_17_ASCLIN_INIT_DEINIT_WRITESAFETYENDINITPROTREG(                         \
    (uint32*)&HwModuleAddr->KRST1.U, LIN_17_ASCLIN_ENABLE_FLAG);
  do
  {
    WaitCount--;

    RstStatus = HwModuleAddr->KRST0.B.RSTSTAT;
  }
  while ((RstStatus == LIN_17_ASCLIN_DISABLE_FLAG) &&                          \
         (WaitCount > LIN_17_ASCLIN_NUMBER_ZERO));

  /* MISRA2012_RULE_11_3_JUSTIFICATION: cast performed between a pointer to
   * object type and a pointer to a different object type due to SFR access. */
  /* MISRA2012_RULE_11_8_JUSTIFICATION: SFR access. Since the input
   * argument for the API discards volatile keyword. No side effects foreseen
   * by violating this MISRA rule*/
  LIN_17_ASCLIN_INIT_DEINIT_WRITESAFETYENDINITPROTREG(                         \
      (uint32*)&HwModuleAddr->KRSTCLR.U, LIN_17_ASCLIN_ENABLE_FLAG);

}

/*******************************************************************************
** Traceability :[cover parentID={55D558BF-1DDC-46ae-A340-41F9A18B272C}]      **
**                        [/cover]                                            **
** Syntax           : static void Lin_17_AscLin_lHwStartTransmission          **
**                      (uint8 HwUnit,                                        **
**                       uint8 Channel)                                       **
** [/cover]                                                                   **
**                                                                            **
** Service ID       : NA                                                      **
**                                                                            **
** Sync/Async       : Synchronous                                             **
**                                                                            **
** Reentrancy       : Reentrant                                               **
**                                                                            **
** Parameters (in)  : HwUnit   : ASCLIN Hardware module no                    **
**                Channel : LIN Channel number                                **
**                                                                            **
** Parameters (out) : None                                                    **
**                                                                            **
** Return value     : None                                                    **
**                                                                            **
** Description      : This function configures the ASCLIN hardware for        **
**                    Frame transmission.                                     **
*******************************************************************************/
static void Lin_17_AscLin_lHwStartTransmission
(
  const uint8 HwUnit,
  const uint8 Channel
)
{
  Ifx_ASCLIN*  HwModulePtr;
  uint32 LocalPid;
  uint8 ResponseTimeOutVal;
  uint8 count;
  uint8 cntr;

  Lin_FrameResponseType LocalDrc;

  HwModulePtr = Lin_17_AscLin_AscLinRegAddr[HwUnit];

  /* Calculate the Response timeout value as per LIN2.1
     Response timeout = ((10 * (Datalength + 1) * 1.4))
                      = ((Datalength +1) * (14))
     */
  ResponseTimeOutVal = (uint8)((Lin_17_AscLin_ChannelInfo[Channel].Dl + 1UL)   \
                               * (14UL));

  /* Configure the data length, checksum , response timeout */
  HwModulePtr->DATCON.B.DATLEN = Lin_17_AscLin_ChannelInfo[Channel].Dl -       \
                                 LIN_17_ASCLIN_NUMBER_ONE ;
  /*[cover parentID={A72F1A67-E51D-4c28-972A-B5BC4B355289}]
      [/cover]*/
  HwModulePtr->DATCON.B.CSM = (uint8)Lin_17_AscLin_ChannelInfo[Channel].Cs;
  HwModulePtr->DATCON.B.RESPONSE = (uint8)ResponseTimeOutVal;
  /* Response mode = Reponsetype */
  HwModulePtr->DATCON.B.RM = LIN_17_ASCLIN_ENABLE_FLAG;

  /*[cover parentID={2F471638-7EA8-4008-87A4-D7613885567E}]
      [/cover]*/
  /* Enable the appropriate interrupt Flags  */
  LocalDrc = Lin_17_AscLin_ChannelInfo[Channel].Drc;

  if (LIN_MASTER_RESPONSE == LocalDrc)
  {
    /* [cover parentID={D291ED3D-C0F4-4eed-9BB1-848097D24AD2}]
        [/cover] */
    HwModulePtr->FLAGSENABLE.U = LIN_17_ASCLIN_FLAGS_MS_TX;
    HwModulePtr->DATCON.B.HO = LIN_17_ASCLIN_DISABLE_FLAG;
  }
  else if (LIN_SLAVE_RESPONSE == LocalDrc)
  {
    /* [cover parentID={FA3663B3-2A4B-4476-8BFC-63C29E0744BF}]
        [/cover] */
    HwModulePtr->FLAGSENABLE.U = LIN_17_ASCLIN_FLAGS_MS_RX;
    HwModulePtr->RXFIFOCON.B.ENI = LIN_17_ASCLIN_ENABLE_FLAG;
    HwModulePtr->DATCON.B.HO = LIN_17_ASCLIN_DISABLE_FLAG;
  }
  else
  {
    /* [cover parentID={E9B3584A-1AB6-4851-99AC-4CCC813862A9}]
        [/cover] */
    HwModulePtr->FLAGSENABLE.U = LIN_17_ASCLIN_FLAGS_MS_HO;
    HwModulePtr->DATCON.B.HO = LIN_17_ASCLIN_ENABLE_FLAG;
  }

  /* Write ID to Tx Fifo.
    the Parity is masked out since the Hw generates the parity automatically */
  LocalPid = Lin_17_AscLin_ChannelInfo[Channel].Pid ;
  LocalPid &= LIN_17_ASCLIN_PID_MASK_WO_PARITY;
  HwModulePtr->TXDATA.U =  LocalPid;


  /* Write Data bytes to Tx fifo in case of Master to Slave */
  if (Lin_17_AscLin_ChannelInfo[Channel].Drc == LIN_MASTER_RESPONSE)
  {
    count = Lin_17_AscLin_ChannelInfo[Channel].Dl;
    for (cntr = (uint8)LIN_17_ASCLIN_NUMBER_ZERO; cntr < count; cntr++)
    {
      /*[cover parentID={94C8F60E-9EA5-4652-B9FE-3F58B3D5991D}]
      [/cover]*/
      HwModulePtr->TXDATA.U = Lin_17_AscLin_ResponseBuffer[Channel][cntr];
    }
  }

  /* Enable the Header Transmission */
  /* [cover parentID={AC8BA49E-F628-487e-B04B-4F58F058F0E7}]
    [/cover] */
  HwModulePtr->FLAGSSET.B.THRQS = LIN_17_ASCLIN_ENABLE_FLAG ;


  /* Enable the Response transmission in case of Master to Slave  */
  if (Lin_17_AscLin_ChannelInfo[Channel].Drc == LIN_MASTER_RESPONSE)
  {
    HwModulePtr->FLAGSSET.B.TRRQS = LIN_17_ASCLIN_ENABLE_FLAG ;
  }

  /* Enable the Tx Outlet */
  /* [cover parentID={16F058DD-B1BA-47a2-8C4F-A810561E2BD2}]
    [/cover] */
  HwModulePtr->TXFIFOCON.B.ENO = LIN_17_ASCLIN_ENABLE_FLAG;

}

#if (LIN_17_ASCLIN_GLOBAL_CHANNEL_WAKEUP_SUPPORT == STD_ON)
/*******************************************************************************
** Traceability :[cover parentID={D8757EEC-657D-4128-A4F7-6AFA5BB7D660}]      **
**                        [/cover]                                            **
** Syntax           : static void Lin_17_AscLin_lHwConfigWakeup               **
**                      (uint8 HwUnit,                                        **
**                       uint8 IocrDepth                                      **
**                       uint16 BitconPrescalar)                              **
**                                                                            **
** Service ID       : NA                                                      **
**                                                                            **
** Sync/Async       : Synchronous                                             **
**                                                                            **
** Reentrancy       : Reentrant                                               **
**                                                                            **
** Parameters (in)  : HwUnit   : ASCLIN Hardware module no                    **
**                    IocrDepth   : IOCR Depth for wakeup detection           **
**                    BitconPrescalar   :Prescalar value for wakeup detection **
**                                                                            **
** Parameters (out) : None                                                    **
**                                                                            **
** Return value     : None                                                    **
**                                                                            **
** Description      : This function configures the hardware for the wakeup    **
*******************************************************************************/
static void Lin_17_AscLin_lHwConfigWakeup
(
  const uint8 HwUnit,
  const uint8 IocrDepth,
  const uint16 BitconPrescalar
)
{
  Ifx_ASCLIN*  HwModulePtr;
  uint32 TimeOutCount;

  HwModulePtr = Lin_17_AscLin_AscLinRegAddr[HwUnit];

  /* Disable the Clock source. */
  HwModulePtr->CSR.B.CLKSEL = LIN_17_ASCLIN_CSRREG_CLKSEL_NOCLK;

  /* Configure the Digital filter depth and  prescalar value for
  wakeup detection */
  TimeOutCount = LIN_17_ASCLIN_TIMEOUT_DURATION;
  /*Wait TW or poll for CSR.CON = 0*/
  while ((HwModulePtr->CSR.B.CON != LIN_17_ASCLIN_DISABLE_FLAG) &&             \
         (TimeOutCount > LIN_17_ASCLIN_DISABLE_FLAG))
  {
    TimeOutCount-- ;
  }

  /* Re-Configure NUM and DEN to maintain 1 microtick = 1 tick so that
     there is no effect from the median filter and only the
     glitch filter is used for wakeup detection */
  /* [cover parentID={B9F5312B-6DA0-44bb-BC84-D686FFEB145C}]
      [/cover] */
  HwModulePtr->BRG.B.NUMERATOR = LIN_17_ASCLIN_WAKEUP_NUMERATOR_VAL;
  HwModulePtr->BRG.B.DENOMINATOR = LIN_17_ASCLIN_WAKEUP_DENOMINATOR_VAL;
  HwModulePtr->IOCR.B.DEPTH = IocrDepth;
  HwModulePtr->BITCON.B.PRESCALER = BitconPrescalar;

  /* Connect the Clock source */
  HwModulePtr->CSR.B.CLKSEL = LIN_17_ASCLIN_CSRREG_CLKSEL;

  /* [cover parentID={D92C21BA-843B-41d8-8587-8A9FC70C0843}]
     [/cover] */
  TimeOutCount = LIN_17_ASCLIN_TIMEOUT_DURATION;
  /* provide delay of TW >= 4 * (1/fA) + 2 * (1/fCLC) clock cycles */
  /*Wait TW or poll or CSR.CON = 1*/
  while ((HwModulePtr->CSR.B.CON != LIN_17_ASCLIN_ENABLE_FLAG) &&
         (TimeOutCount > LIN_17_ASCLIN_DISABLE_FLAG))
  {
    TimeOutCount-- ;
  }

  HwModulePtr->FLAGSCLEAR.B.FEDC = LIN_17_ASCLIN_ENABLE_FLAG;

  /* Enable the FED flag and intr */
  HwModulePtr->FLAGSENABLE.B.FEDE = LIN_17_ASCLIN_ENABLE_FLAG;

}
#endif
#if (LIN_17_ASCLIN_GLOBAL_CHANNEL_WAKEUP_SUPPORT == STD_ON)
/*******************************************************************************
** Traceability :[cover parentID={C589F536-155A-42c1-BDC2-3D8A89EB7C71}]      **
**                        [/cover]                                            **
** Syntax           : static void Lin_17_AscLin_lHwConfigAfterWakeup          **
**                      (uint8 HwUnit)                                        **
**                                                                            **
** Service ID       : NA                                                      **
**                                                                            **
** Sync/Async       : Synchronous                                             **
**                                                                            **
** Reentrancy       : Reentrant                                               **
**                                                                            **
** Parameters (in)  : HwUnit   : ASCLIN Hardware module no                    **
**                                                                            **
** Parameters (out) : None                                                    **
**                                                                            **
** Return value     : None                                                    **
**                                                                            **
** Description      : This function configures the hardware after the wakeup  **
 **                   pulse is sent/ received                                 **
*******************************************************************************/
static void Lin_17_AscLin_lHwConfigAfterWakeup(const uint8 HwUnit)
{
  Ifx_ASCLIN*  HwModulePtr;
  Lin_17_AscLin_ChannelTimingConfigType TimingData;
  uint32 TimeOutCount;
  uint8 Channel;

  /* Extract the Channel */
  Channel =                                                                    \
          Lin_17_AscLin_kConfigPtr->Lin_17_AscLin_ChannelIdLookupPtr[HwUnit];


  TimingData =                                                                 \
    (Lin_17_AscLin_kConfigPtr->ChannelConfigPtr[Channel].TimingConfig);

  HwModulePtr = Lin_17_AscLin_AscLinRegAddr[HwUnit];

  /* clear Falling edge intr */
  HwModulePtr->FLAGSCLEAR.B.FEDC = LIN_17_ASCLIN_ENABLE_FLAG;

  /* Disable Falling edge intr */
  HwModulePtr->FLAGSENABLE.B.FEDE = LIN_17_ASCLIN_DISABLE_FLAG;

  HwModulePtr->CSR.B.CLKSEL = LIN_17_ASCLIN_CSRREG_CLKSEL_NOCLK;
  TimeOutCount = LIN_17_ASCLIN_TIMEOUT_DURATION;
  /*Wait TW or poll for CSR.CON = 0*/
  while ((HwModulePtr->CSR.B.CON != LIN_17_ASCLIN_DISABLE_FLAG) &&             \
         (TimeOutCount > LIN_17_ASCLIN_NUMBER_ZERO))
  {
    TimeOutCount-- ;
  }

  /* Restore the Baudrate parameters */
  /* [cover parentID={B6C3930F-9535-4675-B966-F7B1E48D2CBE}]
    [/cover] */
  HwModulePtr->BRG.B.NUMERATOR = TimingData.HwBrgNumerator;
  HwModulePtr->BRG.B.DENOMINATOR = TimingData.HwBrgDenominator;
  HwModulePtr->IOCR.B.DEPTH = LIN_17_ASCLIN_IOCRREG_DEPTH_VAL;
  HwModulePtr->BITCON.B.PRESCALER = TimingData.HwBitconPrescalar;

  /* Connect the Clock source */
  HwModulePtr->CSR.B.CLKSEL = LIN_17_ASCLIN_CSRREG_CLKSEL;
  TimeOutCount = LIN_17_ASCLIN_TIMEOUT_DURATION;
  /* provide delay of TW >= 4 * (1/fA) + 2 * (1/fCLC) clock cycles */
  /*Wait TW or poll for CSR.CON = 1*/
  while ((HwModulePtr->CSR.B.CON != LIN_17_ASCLIN_ENABLE_FLAG) &&              \
         (TimeOutCount > LIN_17_ASCLIN_NUMBER_ZERO))
  {
    TimeOutCount-- ;
  }
}
#endif

/*******************************************************************************
** Traceability :[cover parentID={BC9028A6-D3CF-48b1-93A6-25359079C9A0}]      **
**                           [/cover]                                         **
** Syntax           : LOCAL_INLINE Lin_17_AscLin_IntStatusType                **
** Lin_17_AscLin_lGetIntErrorStatus(uint32 HwErrorFlags,const uint8 Channel)  **
**                                                                            **
** Service ID       : NA                                                      **
**                                                                            **
** Sync/Async       : Synchronous                                             **
**                                                                            **
** Reentrancy       : Reentrant                                               **
**                                                                            **
** Parameters (in)  : HwErrorFlags   : Hw error FLAGS as given by ASCLIN      **
**                  : Channel        : LIN channel to be addressed            **
**                                                                            **
** Parameters (out) : Lin_17_AscLin_IntStatusType: Internal Status information**
**                                                                            **
** Return value     : Status                                                  **
**                                                                            **
** Description      : This function returns the internal status information   **
**                   based on the asclin hw error flags register.             **
**                                                                            **
*******************************************************************************/
LOCAL_INLINE Lin_17_AscLin_IntStatusType Lin_17_AscLin_lGetIntErrorStatus
(
  const uint32 HwErrorFlags, const uint8 Channel
)
{
  Lin_17_AscLin_IntStatusType Status;
  uint8 HwUnit;
  uint8 FifoValue;
  const Ifx_ASCLIN* HwModulePtr;
  const Lin_17_AscLin_ChannelType   *ChannelConfigPtr;

  ChannelConfigPtr = &(Lin_17_AscLin_kConfigPtr->ChannelConfigPtr[Channel]);
  /* Extract HwUnit */
  HwUnit = ChannelConfigPtr->HwModule;
  HwModulePtr = Lin_17_AscLin_AscLinRegAddr[HwUnit];
  /* Read the RXFIFO FILL value from hw */
  FifoValue = HwModulePtr->RXFIFOCON.B.FILL;

  /* Check for the header error. */
  /* Header Error: (Transmit header not completed) AND
     (Collision detected OR Tx-FIFO overflow OR Parity Error) */
  /* [cover parentID={687CE175-1CAF-4828-8E00-E2F5DE0E3C0E}]
    [/cover] */
 if ((((HwErrorFlags & ((uint32)LIN_17_ASCLIN_FLAGSREG_TH)) ==                 \
     LIN_17_ASCLIN_DISABLE_FLAG) && ((HwErrorFlags & (LIN_17_ASCLIN_FLAGSREG_CE\
   | LIN_17_ASCLIN_FLAGSREG_TFO | LIN_17_ASCLIN_FLAGSREG_LP                    \
   | LIN_17_ASCLIN_HEADER_TIMEOUT_ERR)) != LIN_17_ASCLIN_DISABLE_FLAG)))
  {
    /* [cover parentID={D419CF2F-67E3-4461-B063-628539862733}]
        [/cover] */
    Status = LIN_17_ASCLIN_TX_HEADER_ERROR_I;
  }
  /* Check for the transmit error. */
  /* Transmit Error:(Transmit header completed) AND
     (Collision detected OR Tx FIFO overflow) */
  /* [cover parentID={5A62BDFA-560C-49f7-B00F-E08948C12D11}]
    [/cover] */
  else if (((HwErrorFlags & LIN_17_ASCLIN_FLAGSREG_TH) !=                      \
      LIN_17_ASCLIN_DISABLE_FLAG) && ((HwErrorFlags &                          \
      (LIN_17_ASCLIN_FLAGSREG_CE | LIN_17_ASCLIN_FLAGSREG_TFO)) !=             \
      LIN_17_ASCLIN_DISABLE_FLAG) )
  {
    /* [cover parentID={B73CBBD5-9BCC-4826-99D5-E849A90BEEDF}]
        [/cover] */
    Status = LIN_17_ASCLIN_TX_ERROR_I;
  }
  /* Check for the receive error. */
  /* Receive Error:(Transmit header completed) AND
     (Checksum Error OR Rx-FIFO overflow/Underflow OR Framing Error) */
  /* [cover parentID={8D8E82BD-D9B4-4f1d-9029-772AC759E59C}]
    [/cover] */
  else if (((HwErrorFlags & LIN_17_ASCLIN_FLAGSREG_TH) !=                      \
      LIN_17_ASCLIN_DISABLE_FLAG) && ((HwErrorFlags &                          \
      (LIN_17_ASCLIN_FLAGSREG_LC | LIN_17_ASCLIN_FLAGSREG_RFO |                \
      LIN_17_ASCLIN_FLAGSREG_RFU | LIN_17_ASCLIN_FLAGSREG_FE |                 \
      LIN_17_ASCLIN_RESP_TIMEOUT_ERR)) != LIN_17_ASCLIN_DISABLE_FLAG))
  {
    /* [cover parentID={337D8EC9-A5DE-4666-BE0A-6561C3C9C54E}]
    [/cover] */
    Status = LIN_17_ASCLIN_RX_ERROR_I;
    /* Check if the response timeout occured and only 1 ID byte is received */
    /* [cover parentID={3B14BFF7-45F7-4d63-B8D8-7B7A7BAC27E0}]
    [/cover] */
    if (((HwErrorFlags & LIN_17_ASCLIN_RESP_TIMEOUT_ERR) !=                     \
          LIN_17_ASCLIN_DISABLE_FLAG) && (LIN_17_ASCLIN_RXFIFOVAL_IDONLY ==     \
          FifoValue))
    {
    /* [cover parentID={7084C3E3-73C3-4401-8878-7C4FF4376746}]
    [/cover] */
      Status = LIN_17_ASCLIN_RX_NO_RESPONSE_I;
    }
  }
  else
  { /* No Error */
    /* [cover parentID={D1D5A830-D9E3-4e36-B49E-D845B5E1AC7E}]
      [/cover] */
    Status = LIN_17_ASCLIN_CH_INIT_I;
  }

  return Status;
}

/*******************************************************************************
** Traceability :[cover parentID={B0B79DAA-543F-46b0-B614-AD8FEB018804}]      **
**                        [/cover]                                            **
** Syntax           : LOCAL_INLINE void Lin_17_AscLin_lHwSendWakeupPulse      **
**                    (                                                       **
                         uint8 HwUnit                                         **
                      )                                                       **
**                                                                            **
** Service ID       : NA                                                      **
**                                                                            **
** Sync/Async       : Synchronous                                             **
**                                                                            **
** Reentrancy       : Reentrant                                               **
**                                                                            **
** Parameters (in)  : HwUnit   : ASCLIN Hardware module no                    **
**                                                                            **
** Parameters (out) : None                                                    **
**                                                                            **
** Return value     : None                                                    **
**                                                                            **
** Description      : This function sends the wakeup pulse with the           **
**                    time duration given by wakeup val                       **
*******************************************************************************/
LOCAL_INLINE void Lin_17_AscLin_lHwSendWakeupPulse(const uint8 HwUnit)
{
  Ifx_ASCLIN*  HwModulePtr;
  HwModulePtr = Lin_17_AscLin_AscLinRegAddr[HwUnit];

  /* update the Wakeup pulse time duration in TX data  */
  /* [cover parentID={BAADBD24-5761-45b2-A5EA-059850AD3D03}]
      [/cover] */
  HwModulePtr->TXDATA.U = LIN_17_ASCLIN_WAKEUP_VALUE;

  /* Enable Tx Fifo outlet */
  HwModulePtr->TXFIFOCON.B.ENO = LIN_17_ASCLIN_ENABLE_FLAG;

  /* Set the Transmit wakeup pulse request bit */
  /* [cover parentID={3A996364-9681-4f0d-9E12-3FC8E80EB69F}]
      [/cover] */
  HwModulePtr->FLAGSSET.B.TWRQS = LIN_17_ASCLIN_ENABLE_FLAG;
}

#if(LIN_17_ASCLIN_VERSION_INFO_API == STD_ON)
/*******************************************************************************
** Traceability :[cover parentID={A14F0239-0C17-4d5a-B301-BA104A995C98}] **
**                  [/cover]                                              **
** Syntax           : void  Lin_17_AscLin_GetVersionInfo                      **
**                    (                                                       **
**                      Std_VersionInfoType *VersionInfo                      **
**                    )                                                       **
** [/cover]                                                                   **
**                                                                            **
** Service ID       : 0x01                                                    **
**                                                                            **
** Sync/Async       : Synchronous                                             **
**                                                                            **
** Reentrancy       : Reentrant                                               **
**                                                                            **
** Parameters (in)  : none                                                    **
**                                                                            **
** Parameters (out) : versioninfo - Pointer to where to store the             **
**                    version information of this module.                     **
**                                                                            **
** Return value     : none                                                    **
**                                                                            **
** Description      : This function:                                          **
**   - This function returns the version information of the module            **
*******************************************************************************/
/* [cover parentID={0D572F1F-4815-4464-808C-FB9B006910CB}]
      [/cover] */
void  Lin_17_AscLin_GetVersionInfo(Std_VersionInfoType *const versioninfo)
{

  /* [cover parentID={27EC1E8E-92F2-472b-8C7D-A886EDFF43F1}]
      [/cover] */
  #if (LIN_17_ASCLIN_DEV_ERROR_DETECT == STD_ON)
  /* [cover parentID={DD0A7898-E567-41b5-BB0B-8E1B89658C39}]
      [/cover] */
  /* [cover parentID={EA08717D-94D1-48d2-B346-386F24C5E1DD}]
      [/cover] */
  if((versioninfo) == (NULL_PTR))
  {
    /* [cover parentID={FC42A679-4D41-4c70-9D91-9BBADDBC161C}]
        [/cover] */
    Det_ReportError(
      LIN_17_ASCLIN_MODULE_ID,
      LIN_17_ASCLIN_INSTANCE_ID,
      LIN_17_ASCLIN_SID_VERSIONINFO,
      LIN_17_ASCLIN_E_PARAM_POINTER
    );
  }
  else
  #endif
  {
    /* [cover parentID={CE29FE32-AB25-4b86-973E-B69964451527}]
         [/cover] */
    /* LIN vendor ID */
    ((Std_VersionInfoType*)(versioninfo))->moduleID = LIN_17_ASCLIN_MODULE_ID;
    /* LIN vendor ID */
    ((Std_VersionInfoType*)(versioninfo))->vendorID = LIN_17_ASCLIN_VENDOR_ID;
    /* Major version of LIN */
    ((Std_VersionInfoType*)(versioninfo))->sw_major_version =
                                       (uint8)LIN_17_ASCLIN_SW_MAJOR_VERSION;
    /* Minor version of LIN */
    ((Std_VersionInfoType*)(versioninfo))->sw_minor_version =
                                       (uint8)LIN_17_ASCLIN_SW_MINOR_VERSION;
    /* Patch version of LIN */
    ((Std_VersionInfoType*)(versioninfo))->sw_patch_version =
                                       (uint8)LIN_17_ASCLIN_SW_PATCH_VERSION;
  }
}
#endif

/* [cover parentID={4579FE20-92DA-4848-93DB-7AD4FD35DD50}]
    [/cover] */
#define LIN_17_ASCLIN_STOP_SEC_CODE_QM_LOCAL
/*mapping of code and data to specific memory sections via memory mapping file*/
/* MISRA2012_RULE_4_10_JUSTIFICATION: To be compliant with autosar guidelines
Lin_17_AscLin_Memmap.h header is included without safegaurd.*/
/* MISRA2012_RULE_20_1_JUSTIFICATION: Lin_17_AscLin_Memmap.h header included
as per Autosar guidelines. */
#include "Lin_17_AscLin_MemMap.h"

