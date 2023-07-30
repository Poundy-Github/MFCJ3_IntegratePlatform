/*********************************************************************************/
/*                                                                               */
/*                                  CAN Stack                                    */
/*                                                                               */
/* ----------------------------------------------------------------------------- */
/*                                                                               */
/*                                APP                                            */
/*                                                                               */
/*********************************************************************************/
/*%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%                                        */
/*%%   _____________________________   %%  \file APP_Pub.h                       */
/*%%  |                             |  %%                                        */
/*%%  |   &&&&&   &&&&&             |  %%  Module version: 3.5.255 OSC_BOOT                */
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

#ifndef APP_PUB_H
#define APP_PUB_H

/* PROG boolean type */
#define PROG_FALSE               0U
#define PROG_TRUE                1U
typedef u8 tProgBoolean;

typedef u8 tProgResCause;
#define PROG_RESET_CAUSE_ER             0x00U
#define PROG_RESET_CAUSE_DSC01          0x01U
#define PROG_RESET_CAUSE_DSC02          0x02U
#define PROG_RESET_CAUSE_S3_TIMEOUT     0x03U

#define PROG_ECU_RESET_RESPONSE_SIZE    2U

/* Specific to Authenticate Boot */
#define BM_CHECKSUM_SIZE_IN_BYTES       64U

#define PROG_P2STAR_DEFAULT_SESSION_VAL m_stSessionInfo[UDS_DEFAULT_SESSION_INDEX].uwP2StarVal
#define PROG_P2_DEFAULT_SESSION_VAL     m_stSessionInfo[UDS_DEFAULT_SESSION_INDEX].uwP2Val
#define PROG_P2STAR_PROG_SESSION_VAL    m_stSessionInfo[UDS_PROGRAMMING_SESSION_INDEX].uwP2StarVal
#define PROG_P2_PROG_SESSION_VAL        m_stSessionInfo[UDS_PROGRAMMING_SESSION_INDEX].uwP2Val

#define PROG_BLOCK_NB 2U

#define PROG_REPROG_FLAG_START_SEC_VAR_NO_INIT_8
#include <MemMap.h>
extern tNoIntShareVar stNoIntShareVar;
#define PROG_REPROG_FLAG_STOP_SEC_VAR_NO_INIT_8
#include <MemMap.h>

/** \brief Initialize layer
 **
 ** This function initializes all layers of the complete STACK.
 ** EB_Init is called in this API.
 ** It shall be called only once at ECU startup.
 **
 **/
extern void APP_Init (void);

/** \brief Regular tick of the layer
 **
 ** Ensure cyclic tasks of the layer.
 **
 **/
extern void APP_Manage (void);

extern void APP_Reset_Cause(void);

extern void PROG_SimulateOpenProgSession(void);

extern void PROG_SimulateCloseProgSession(void);

extern void PROG_SimulateER(void);

#endif      /* APP_PUB_H */
