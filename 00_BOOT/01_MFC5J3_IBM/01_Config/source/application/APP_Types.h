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
/*%%  |   &&&&&   &&&&&             |  %%  Module version: 3.6.8 BL-3.X                */
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

/** \brief Define APP_FALSE */
#define APP_FALSE               0U
/** \brief Define APP_TRUE */
#define APP_TRUE                1U
/** \brief definition of the tAppBoolean */
typedef u8 tAppBoolean;

#define APP_SIG  0x5AA5A55AU

typedef void (*ptAPPL_START_ADDR)(void);

#endif      /* APP_TYPES_H */
