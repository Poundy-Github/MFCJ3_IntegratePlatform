/*********************************************************************************/
/*                                                                               */
/*                               BOOT Layers                                     */
/*                                                                               */
/* ----------------------------------------------------------------------------- */
/*                                                                               */
/*                               BM layer                                        */
/*                                                                               */
/*********************************************************************************/
/*%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%                                        */
/*%%   _____________________________   %%  \file BM_Types.h                      */
/*%%  |                             |  %%  \brief BM layer include plugin file   */
/*%%  |   &&&&&   &&&&&             |  %%  Module version: 1.15.0 BL3                */
/*%%  |   &       &    &            |  %%  Variant: OsekCore                  */
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




#ifndef BM_TYPES_H
#define BM_TYPES_H


  

typedef u8 tBMTimeout;

typedef u8 tBMBoolean;
#define BM_FALSE                    0U
#define BM_TRUE                     1U

#define BM_BOOT_MANAGER             0U
#define BM_INITIAL_BOOT_MANAGER     1U

typedef u8 tBMHsmJobResult;
#define BM_HSM_JOB_OK               0U
#define BM_HSM_JOB_FAILED           1U
#define BM_HSM_JOB_PENDING          2U




  
typedef void (*ptBLU_START_ADDR)(void);
typedef void (*ptBL_START_ADDR)(void);


#endif      /* BM_TYPES_H */

