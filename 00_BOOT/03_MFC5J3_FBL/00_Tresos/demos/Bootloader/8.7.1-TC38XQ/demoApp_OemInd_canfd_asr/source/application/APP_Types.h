/*********************************************************************************/
/*                                                                               */
/*                                  CAN Stack                                    */
/*                                                                               */
/* ------------------------------------------------------------------------------*/
/*                                                                               */
/*                                 APP configuration                             */
/*                                                                               */
/*********************************************************************************/
/*%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%                                        */
/*%%   _____________________________   %%  \file APP_Types.h                     */
/*%%  |                             |  %%  \brief APP layer types  */
/*%%  |   &&&&&   &&&&&             |  %%  Module version: 3.6.255 OSC_BOOT                */
/*%%  |   &       &    &            |  %%                                        */
/*%%  |   &&&&    &&&&&             |  %%                                        */
/*%%  |   &       &    &            |  %%                                        */
/*%%  |   &&&&&   &&&&&             |  %%                                        */
/*%%  |_____________________________|  %%                                        */
/*%%                                   %%                                        */
/*%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%                                        */
/*********************************************************************************/
/* Copyright 2010 by Elektrobit Automotive GmbH                                  */
/* All rights exclusively reserved for Elektrobit Automotive GmbH,               */
/* unless expressly agreed to otherwise.                                         */
/*********************************************************************************/

#ifndef APP_TYPES_H
#define APP_TYPES_H

#include "EB_prj.h"


/** \brief Define APP_FALSE */
#define APP_FALSE               0U
/** \brief Define APP_TRUE */
#define APP_TRUE                1U
/** \brief definition of the tAppBoolean */
typedef u8 tAppBoolean;

/** \brief Define SOFT_RESET */
#define SOFT_RESET 0x00U
/** \brief Define POWER_ON */
#define POWER_ON   0x01U

#define PROG_INFO_PROGR_AND_VALID           0x01U
#define PROG_INFO_SW_SW_MISMATCH            0x02U
#define PROG_INFO_SW_HW_MISMATCH            0x04U
#define PROG_INFO_MEMORY_STATUS             0x08U
#define PROG_INFO_REPROG_STATE_VALID        0x00U
#define PROG_INFO_REPROG_STATE_ERASED_START 0x10U
#define PROG_INFO_REPROG_STATE_ERASED_END   0x20U
#define PROG_INFO_REPROG_STATE_REPROG_START 0x30U
#define PROG_INFO_REPROG_STATE_CHECK_OK     0x40U
#define PROG_INFO_REPROG_STATE_CHECK_NOK    0x50U
#define PROG_INFO_REPROG_STATE_CHECK_SW_NOK 0x60U
typedef void (*ptAPPL_START_ADDR)(void);

typedef struct
{
    u32 ulProgSig;
    u8 ubSendResp;
    u8 ubResetCause;
    u8 ubTesterAddress;
    u8 ubRxPduId;
} tNoIntShareVar;

#endif      /* APP_TYPES_H */
