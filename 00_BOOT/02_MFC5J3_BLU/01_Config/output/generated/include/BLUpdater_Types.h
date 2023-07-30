/*********************************************************************************/
/*                                                                               */
/*                               BOOT Layers                                     */
/*                                                                               */
/* ----------------------------------------------------------------------------- */
/*                                                                               */
/*                               BLUpdater Configuration                         */
/*                                                                               */
/*********************************************************************************/
/*%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%                                        */
/*%%   _____________________________   %%  \file BLUpdater_Types.h               */
/*%%  |                             |  %%                                        */
/*%%  |   &&&&&   &&&&&             |  %%  Module version: 1.3.0 BL3                */
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


#ifndef BLUPDATER_TYPES_H
#define BLUPDATER_TYPES_H

/* BLU boolean type */
typedef u8 tBLUBoolean;
#define BLU_FALSE                     0U
#define BLU_TRUE                      1U

typedef u8 tBLUStatus;
#define BLU_E_OK                      0x00U
#define BLU_E_NOT_OK                  0x01U
#define BLU_E_BUSY                    0x02U

/* BLU Operation type */
typedef u8 tBLUOperation;
#define BLU_ERASE                     0x00U
#define BLU_WRITE                     0x01U
#define BLU_COMPARE                   0x02U

#define BLU_FINISH                    0x04U

typedef struct
{
    u32  ulStartAddress;   /* Start address of the segment */
    u32  ulEndAddress;     /* End address of the segment */
}tCfgSegmentType;

#endif /* BLUpdater_TYPES_H */
