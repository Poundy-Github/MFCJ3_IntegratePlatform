/*********************************************************************************/
/*                                                                               */
/*                                  BOOT Layers                                  */
/*                                                                               */
/* ------------------------------------------------------------------------------*/
/*                                                                               */
/*                                 PROG configuration                            */
/*                                                                               */
/*********************************************************************************/
/*%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%                                        */
/*%%   _____________________________   %%  \file PROG_Cfg.c                      */
/*%%  |                             |  %%  \brief PROG layer source plugin file  */
/*%%  |   &&&&&   &&&&&             |  %%  Module version: 2.19.0 BL-3.X              */
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
#include "EB_Prj.h"






                                                                                                
/*----------------------------------------------------------------------------------*/


const tCfgMemorytType m_astCfgMemory[PROG_MEMORY_NB] =
{
    {
        PROG_MEM_TYPE_FLASH,
        PROG_MEMORY_SYNCHRONOUS,
        0x100U,
        0x0U,
        0x0U,
    },
};

const tCfgSegmentType stConfigSegment[PROG_SEGMENT_NB] =
{
    {
        0xa0100000U,                        /* Start Address */
        0xa01fbfffU,                        /* End Address */
        0xa0100000U,                        /* Erase Start Address */
        0xa01fbfffU,                        /* Erase End Address */
        0U,               /* Selected Memory Index */
        PROG_MEM_ACCESS_TYPE_READ_WRITE,   /* Memory Access Type */
        PROG_APPLICATION_PARTITION,        /* Partition Type */
        PROG_TRUE,/* Validity Check */
    },
    {
        0xa01fc000U,                        /* Start Address */
        0xa024ffffU,                        /* End Address */
        0xa01fc000U,                        /* Erase Start Address */
        0xa024ffffU,                        /* Erase End Address */
        0U,               /* Selected Memory Index */
        PROG_MEM_ACCESS_TYPE_READ_WRITE,   /* Memory Access Type */
        PROG_CALIBRATION_PARTITION,        /* Partition Type */
        PROG_TRUE,/* Validity Check */
    },
};






/* Programmed magic number value */
const u8 m_aCfgMagicNumProgrammedValue[PROG_MAGIC_NUM_SIZE] =
{
    /* PROGRAMM in ASCII */
    0x50U,
    0x52U,
    0x4FU,
    0x47U,
    0x52U,
    0x41U,
    0x4dU,
    0x4dU,
};
/* Revoked PSI value */
const u8 m_aCfgMagicNumRevokedValue[PROG_MAGIC_NUM_SIZE] =
{
    /* REVOKED in ASCII */
    0x56U,
    0x52U,
    0x45U,
    0x56U,
    0x4FU,
    0x4BU,
    0x45U,
    0x44U
};


