/*********************************************************************************/
/*                                                                               */
/*                               BOOT layers                                     */
/*                                                                               */
/* ----------------------------------------------------------------------------- */
/*                                                                               */
/*                              FLASH Hardware                                   */
/*                                                                               */
/*********************************************************************************/
/*%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%                                        */
/*%%   _____________________________   %%  \file FLASH_Hw.h                      */
/*%%  |                             |  %%  \brief FLASH layer implementation     */
/*%%  |   &&&&&   &&&&&             |  %%  Module version: 7.1.6                 */
/*%%  |   &       &    &            |  %%  TARGET: TRICORE                     */
/*%%  |   &&&&    &&&&&             |  %%  DERIVATE: TC38XQ                 */
/*%%  |   &       &    &            |  %%                                        */
/*%%  |   &&&&&   &&&&&             |  %%                                        */
/*%%  |_____________________________|  %%                                        */
/*%%                                   %%                                        */
/*%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%                                        */
/*********************************************************************************/
/* Copyright 2017 by Elektrobit Automotive GmbH                                  */
/* All rights exclusively reserved for Elektrobit Automotive GmbH,               */
/* unless expressly agreed to otherwise.                                         */
/*********************************************************************************/



#ifndef FLASH_HW_H
#define FLASH_HW_H

#define FLASH_REPROG_ENBABLE *(volatile u8*)(0xFF438000U)
#define FLASH_PROTCMD *(volatile u8*)(0xFF438004U)

#define FLASH_PROT_REPROG_Register(value) \
    do{ \
        FLASH_PROTCMD=0xa5U; \
        FLASH_REPROG_ENBABLE = (value); \
        FLASH_REPROG_ENBABLE = ~(value); \
        FLASH_REPROG_ENBABLE = (value); \
    }while(0U);

#define FLASH_TRAP_DIS    (0x00008000U)
#define FLASH_TRAP_EN     (0xFFFF7FFFU)

#endif      /* FLASH_HW_H */
