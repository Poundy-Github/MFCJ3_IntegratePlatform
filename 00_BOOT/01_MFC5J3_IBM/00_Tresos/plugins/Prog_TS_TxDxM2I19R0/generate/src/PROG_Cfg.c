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
[!AUTOSPACING!]
[!VAR "MEMORY_MAX"="num:dectoint(count(Memory/*))"!]
[!VAR "SEGMENT_MAX"="num:dectoint(count(Segments/*))"!]
[!VAR "SEGMENT_IDX"="1"!]
[!VAR "SEGMENT_IDX_2"="1"!]
[!VAR "BLOCK_MAX"="num:dectoint(count(Blocks/*))"!]
[!VAR "BLOCK_IDX"="1"!]

[!VAR "SEGMENT_FOR_BOOTLOADER_PARTITION_IS_DEFINED" = "0"!]
[!/* Collect the information if a Bootloader Partition has been defined */!]
[!FOR "SEGMENT_IDX" = "1" TO "$SEGMENT_MAX"!]
    [!IF "(Segments/*[number($SEGMENT_IDX)]/Partition_Type) = 'PROG_BOOTLOADER_PARTITION'"!]
        [!VAR "SEGMENT_FOR_BOOTLOADER_PARTITION_IS_DEFINED" = "1"!]
        [!VAR "NAME_OF_SEGMENT_FOR_BOOTLOADER_PARTITION" = "text:toupper(name(as:modconf('Prog')/Segments/*[number($SEGMENT_IDX)]))"!]
    [!ENDIF!]
[!ENDFOR!]

[!/* In case that a segment has been defined for Bootloader partition, a block with index 0 shall refer to this segment */!]
[!IF "$SEGMENT_FOR_BOOTLOADER_PARTITION_IS_DEFINED = 1"!]
    [!VAR "GOOD_ASSOCIATION" = "0"!]
    [!VAR "BLOCK_INDEX_0_IS_DEFINED" = "0"!]
    [!VAR "BLOCK_REFERENCING_SEGMENT_BOOTLOADER_EXISTS" = "0"!]
    [!VAR "NUMBER_OF_BLOCKS_WHICH_REFER_TO_BOOT_PARTITION_SEGMENT" = "0"!]
    [!FOR "BLOCK_IDX" = "1" TO "$BLOCK_MAX"!]
        [!IF "(text:toupper(name(node:ref(as:modconf('Prog')/Blocks/*[number($BLOCK_IDX)]/First_Segment))) = $NAME_OF_SEGMENT_FOR_BOOTLOADER_PARTITION)"!]
            [!VAR "BLOCK_REFERENCING_SEGMENT_BOOTLOADER_EXISTS" = "1"!]
            [!VAR "NAME_OF_BLOCK_REFERENCING_BOOTLOADER_SEGMENT" = "name(as:modconf('Prog')/Blocks/*[number($BLOCK_IDX)])"!]
            [!VAR "NUMBER_OF_BLOCKS_WHICH_REFER_TO_BOOT_PARTITION_SEGMENT" = "$NUMBER_OF_BLOCKS_WHICH_REFER_TO_BOOT_PARTITION_SEGMENT + 1"!]
            [!IF "num:hextoint(as:modconf('Prog')/Blocks/*[number($BLOCK_IDX)]/Block_Identifier) = number('0')"!]
                [!VAR "BLOCK_INDEX_0_IS_DEFINED" = "1"!]
                [!VAR "NAME_OF_BLOCK_INDEX_0" = "name(as:modconf('Prog')/Blocks/*[number($BLOCK_IDX)])"!]
                [!VAR "GOOD_ASSOCIATION" = "1"!]
            [!ENDIF!]
        [!ELSE!]
            [!IF "num:hextoint(as:modconf('Prog')/Blocks/*[number($BLOCK_IDX)]/Block_Identifier) = number('0')"!]
                [!VAR "BLOCK_INDEX_0_IS_DEFINED" = "1"!]
                [!VAR "NAME_OF_BLOCK_INDEX_0" = "name(as:modconf('Prog')/Blocks/*[number($BLOCK_IDX)])"!]
            [!ENDIF!]
        [!ENDIF!]
    [!ENDFOR!]
    [!IF "$GOOD_ASSOCIATION = 0"!]
        [!IF "$BLOCK_INDEX_0_IS_DEFINED = 0"!]
            [!IF "$BLOCK_REFERENCING_SEGMENT_BOOTLOADER_EXISTS = 0"!]
                [!ERROR!]
                    No block with index 0 exists and no block refers to "[!"$NAME_OF_SEGMENT_FOR_BOOTLOADER_PARTITION"!]"
                [!ENDERROR!]
            [!ELSE!]
                [!IF "$NUMBER_OF_BLOCKS_WHICH_REFER_TO_BOOT_PARTITION_SEGMENT = 1"!]
                    [!ERROR!]
                        Block "[!"$NAME_OF_BLOCK_REFERENCING_BOOTLOADER_SEGMENT"!]" which refers to "[!"$NAME_OF_SEGMENT_FOR_BOOTLOADER_PARTITION"!]" must have index 0
                    [!ENDERROR!]
                [!ELSE!]
                    [!ERROR!]
                        More than one block refers to "[!"$NAME_OF_SEGMENT_FOR_BOOTLOADER_PARTITION"!]" but none of them has index 0
                    [!ENDERROR!]
                [!ENDIF!]
            [!ENDIF!]
        [!ELSE!]
            [!IF "$BLOCK_REFERENCING_SEGMENT_BOOTLOADER_EXISTS = 0"!]
                [!ERROR!]
                    No block refers to "[!"$NAME_OF_SEGMENT_FOR_BOOTLOADER_PARTITION"!]". Block with index 0 "[!"$NAME_OF_BLOCK_INDEX_0"!]" must refer to "[!"$NAME_OF_SEGMENT_FOR_BOOTLOADER_PARTITION"!]"
                [!ENDERROR!]
            [!ELSE!]
                [!IF "$NUMBER_OF_BLOCKS_WHICH_REFER_TO_BOOT_PARTITION_SEGMENT = 1"!]
                    [!ERROR!]
                        Either Block with index 0 "[!"$NAME_OF_BLOCK_INDEX_0"!]" must refer to "[!"$NAME_OF_SEGMENT_FOR_BOOTLOADER_PARTITION"!]" or block "[!"$NAME_OF_BLOCK_REFERENCING_BOOTLOADER_SEGMENT"!]" which refers to "[!"$NAME_OF_SEGMENT_FOR_BOOTLOADER_PARTITION"!]" must have index 0
                    [!ENDERROR!]
                [!ELSE!]
                    [!ERROR!]
                        More than one block refers to "[!"$NAME_OF_SEGMENT_FOR_BOOTLOADER_PARTITION"!]" but none of them has index 0. Block with index 0 "[!"$NAME_OF_BLOCK_INDEX_0"!]" doesn't refer to "[!"$NAME_OF_SEGMENT_FOR_BOOTLOADER_PARTITION"!]"
                    [!ENDERROR!]
                [!ENDIF!]
            [!ENDIF!]
        [!ENDIF!]
    [!ENDIF!]
[!ENDIF!]

[!/*Check if two segment are not overlapping each other */!]
[!FOR "SEGMENT_IDX" = "1" TO "$SEGMENT_MAX"!]
    [!FOR "SEGMENT_IDX_2" = "1" TO "$SEGMENT_MAX"!]
        [!IF "$SEGMENT_IDX_2 != $SEGMENT_IDX"!]
            [!IF "(num:dectoint(Segments/*[number($SEGMENT_IDX)]/Reprog_Start_Address) >= num:dectoint(Segments/*[number($SEGMENT_IDX_2)]/Reprog_Start_Address)
                    and num:dectoint(Segments/*[number($SEGMENT_IDX)]/Reprog_Start_Address) <= num:dectoint(Segments/*[number($SEGMENT_IDX_2)]/Reprog_End_Address))
                    and (num:dectoint(Segments/*[number($SEGMENT_IDX)]/Reprog_Start_Address) != 0 and num:dectoint(Segments/*[number($SEGMENT_IDX_2)]/Reprog_End_Address) != 0)"!]
                [!WARNING "The reprogramming start address of a segment shall not be inside an already configured one"!]
            [!ENDIF!]
            [!IF "(num:dectoint(Segments/*[number($SEGMENT_IDX)]/Reprog_End_Address) >= num:dectoint(Segments/*[number($SEGMENT_IDX_2)]/Reprog_Start_Address)
                    and num:dectoint(Segments/*[number($SEGMENT_IDX)]/Reprog_End_Address) <= num:dectoint(Segments/*[number($SEGMENT_IDX_2)]/Reprog_End_Address))
                    and (num:dectoint(Segments/*[number($SEGMENT_IDX)]/Reprog_Start_Address) != 0 and num:dectoint(Segments/*[number($SEGMENT_IDX_2)]/Reprog_End_Address) != 0)"!]
                [!WARNING "The reprogramming end address of a segment shall not be inside an already configured one"!]
            [!ENDIF!]
            [!IF "(num:dectoint(Segments/*[number($SEGMENT_IDX)]/Erase_Start_Address) >= num:dectoint(Segments/*[number($SEGMENT_IDX_2)]/Erase_Start_Address)
                    and num:dectoint(Segments/*[number($SEGMENT_IDX)]/Erase_Start_Address) <= num:dectoint(Segments/*[number($SEGMENT_IDX_2)]/Erase_End_Address))
                    and (num:dectoint(Segments/*[number($SEGMENT_IDX)]/Erase_Start_Address) != 0 and num:dectoint(Segments/*[number($SEGMENT_IDX_2)]/Erase_End_Address) != 0)"!]
                [!WARNING "The erasing start address of a segment shall not be inside an already configured one"!]
            [!ENDIF!]
            [!IF "(num:dectoint(Segments/*[number($SEGMENT_IDX)]/Erase_End_Address) >= num:dectoint(Segments/*[number($SEGMENT_IDX_2)]/Erase_Start_Address)
                    and num:dectoint(Segments/*[number($SEGMENT_IDX)]/Erase_End_Address) <= num:dectoint(Segments/*[number($SEGMENT_IDX_2)]/Erase_End_Address))
                    and (num:dectoint(Segments/*[number($SEGMENT_IDX)]/Erase_Start_Address) != 0 and num:dectoint(Segments/*[number($SEGMENT_IDX_2)]/Erase_End_Address) != 0)"!]
                [!WARNING "The erasing end address of a segment shall not be inside an already configured one"!]
            [!ENDIF!]
        [!ENDIF!]
    [!ENDFOR!]
[!ENDFOR!]

/*----------------------------------------------------------------------------------*/


const tCfgMemorytType m_astCfgMemory[PROG_MEMORY_NB] =
{
    [!FOR "MEMORY_IDX" = "1" TO "$MEMORY_MAX"!]
    [!VAR "MEMORY_TYPE"="text:toupper(Memory/*[number($MEMORY_IDX)]/Memory_Type)"!]
    [!VAR "MEMORY_MODE"="(Memory/*[number($MEMORY_IDX)]/Memory_Mode)"!]
    [!VAR "MEMORY_MIN_VALUE_TO_WRITE"="num:inttohex(Memory/*[number($MEMORY_IDX)]/Min_Value_To_Write)"!]
    [!VAR "MEMORY_ADDRESS_OFFSET"="num:inttohex(Memory/*[number($MEMORY_IDX)]/Addr_Offset)"!]
    [!VAR "MEMORY_ERASE_VALUE"="num:inttohex(Memory/*[number($MEMORY_IDX)]/Erase_Value)"!]
    {
        PROG_MEM_TYPE_[!"$MEMORY_TYPE"!],
        [!WS "8"!][!IF "$MEMORY_MODE = 'asynchronous'"!]PROG_MEMORY_ASYNCHRONOUS[!ELSE!]PROG_MEMORY_SYNCHRONOUS[!ENDIF!],
        [!"$MEMORY_MIN_VALUE_TO_WRITE"!]U,
        [!"$MEMORY_ADDRESS_OFFSET"!]U,
        [!"$MEMORY_ERASE_VALUE"!]U,
    },
    [!ENDFOR!]
};

[!IF "General/Tunable_Parameters = 'false'"!]
const tCfgSegmentType stConfigSegment[PROG_SEGMENT_NB] =
{
    [!FOR "SEGMENT_IDX" = "1" TO "$SEGMENT_MAX"!]
        [!VAR "START_ADD"="num:inttohex(Segments/*[number($SEGMENT_IDX)]/Reprog_Start_Address)"!]
        [!VAR "END_ADD"="num:inttohex(Segments/*[number($SEGMENT_IDX)]/Reprog_End_Address)"!]
        [!VAR "ERASE_START_ADD"="num:inttohex(Segments/*[number($SEGMENT_IDX)]/Erase_Start_Address)"!]
        [!VAR "ERASE_END_ADD"="num:inttohex(Segments/*[number($SEGMENT_IDX)]/Erase_End_Address)"!]
        [!VAR "MEM_NAME" = "text:toupper(name(node:ref(Segments/*[number($SEGMENT_IDX)]/Memory)))"!]
        [!VAR "ACCESS_TYPE"="num:Segments/*[number($SEGMENT_IDX)]/Access_Type"!]
        [!FOR "MEMORY_IDX" = "1" TO "$MEMORY_MAX"!]
            [!IF "$MEM_NAME = text:toupper(name(Memory/*[number($MEMORY_IDX)]))"!]
                [!VAR "SELECTED_MEM_IDX" = "num:dectoint($MEMORY_IDX - 1)"!]
            [!ENDIF!]
        [!ENDFOR!]
        [!VAR "LAST_LOWER_START_ADDRESS" = "0"!]
        [!IF "(((node:exists(as:modconf('ProgOEMInd')) and as:modconf('Prog')/OemInd/Erase_Mode = 'All') or node:exists(as:modconf('ProgVCC'))) and $BLOCK_MAX=0)"!]
            [!VAR "BLOCK_INDEX" = "num:i(0)"!]
        [!ENDIF!]
        [!FOR "BLOCK_IDX" = "1" TO "$BLOCK_MAX"!]
            [!VAR "SEGMENT_REFERENCE" = "text:toupper(name(node:ref(as:modconf('Prog')/Blocks/*[number($BLOCK_IDX)]/First_Segment)))"!]
            [!FOR "SEGMENT_IDX1" = "1" TO "$SEGMENT_MAX"!]
                [!IF "(text:toupper(name(as:modconf('Prog')/Segments/*[number($SEGMENT_IDX1)])) = $SEGMENT_REFERENCE)"!]
                    [!VAR "CURRENT_START_ADDRESS" = "num:dectoint(as:modconf('Prog')/Segments/*[number($SEGMENT_IDX1)]/Reprog_Start_Address)"!]
                    [!IF "$CURRENT_START_ADDRESS <= num:dectoint(as:modconf('Prog')/Segments/*[number($SEGMENT_IDX)]/Reprog_Start_Address)"!]
                        [!IF "$LAST_LOWER_START_ADDRESS <= $CURRENT_START_ADDRESS"!]
                            [!VAR "BLOCK_INDEX" = "num:i(($BLOCK_IDX)-1)"!]
                            [!VAR "LAST_LOWER_START_ADDRESS" = "$CURRENT_START_ADDRESS"!]
                        [!ENDIF!]
                    [!ENDIF!]
                [!ENDIF!]
            [!ENDFOR!]
        [!ENDFOR!]
    {
        [!"$START_ADD"!]U,[!WS "24"!]/* Start Address */
        [!"$END_ADD"!]U,[!WS "24"!]/* End Address */
        [!"$ERASE_START_ADD"!]U,[!WS "24"!]/* Erase Start Address */
        [!"$ERASE_END_ADD"!]U,[!WS "24"!]/* Erase End Address */
        [!"$SELECTED_MEM_IDX"!]U,[!WS "15"!]/* Selected Memory Index */
        PROG_MEM_ACCESS_TYPE_[!"$ACCESS_TYPE"!],[!WS "3"!]/* Memory Access Type */
[!IF "node:exists(as:modconf('ProgGM')) or node:exists(as:modconf('ProgFCA')) or node:exists(as:modconf('ProgVAG')) or node:exists(as:modconf('ProgDAG')) or node:exists(as:modconf('ProgVCC')) or node:exists(as:modconf('ProgOEMInd'))"!]
        [!"Segments/*[number($SEGMENT_IDX)]/Partition_Type"!][!IF "node:exists(as:modconf('ProgOEMInd')) or node:exists(as:modconf('ProgVAG')) or node:exists(as:modconf('ProgDAG')) or node:exists(as:modconf('ProgVCC')) or (node:exists(as:modconf('ProgFCA')) and as:modconf('ProgFCA')/General/PROG_FCA_VARIANT='Atlantis_High')"!],[!ENDIF!][!WS "8"!]/* Partition Type */
[!ENDIF!]
[!IF "node:exists(as:modconf('ProgOEMInd'))"!]
        [!WS "8"!][!IF "Segments/*[number($SEGMENT_IDX)]/ValidityCheck = 'false'"!]PROG_FALSE[!ELSE!]PROG_TRUE[!ENDIF!],/* Validity Check */
[!ENDIF!]
[!IF "node:exists(as:modconf('ProgVAG')) or node:exists(as:modconf('ProgDAG')) or node:exists(as:modconf('ProgVCC')) or (node:exists(as:modconf('ProgFCA')) and as:modconf('ProgFCA')/General/PROG_FCA_VARIANT='Atlantis_High') or (node:exists(as:modconf('ProgOEMInd')) and as:modconf('Prog')/OemInd/Erase_Mode != 'Address')"!]
        [!"$BLOCK_INDEX"!]U[!WS "33"!]/* Corresponding Block Index */
[!ENDIF!]
    },
    [!ENDFOR!]
};

[!IF "node:exists(as:modconf('ProgVAG')) or node:exists(as:modconf('ProgDAG'))
    or (node:exists(as:modconf('ProgFCA')) and as:modconf('ProgFCA')/General/PROG_FCA_VARIANT='Atlantis_High')
    or (node:exists(as:modconf('ProgOEMInd')) and OemInd/Erase_Mode = 'LogicalBlock')"!]
const tProg_Block    stCfgBlock[PROG_BLOCK_NB] =
{
    [!FOR "BLOCK_IDX" = "1" TO "$BLOCK_MAX"!]
        [!VAR "BLOCK_IDENT"="num:inttohex(Blocks/*[number($BLOCK_IDX)]/Block_Identifier)"!]
        [!VAR "SEGMENT_NAME"="text:toupper(name(node:ref(Blocks/*[number($BLOCK_IDX)]/First_Segment)))"!]
        [!VAR "SEGMENT_NBR"="num:inttohex(Blocks/*[number($BLOCK_IDX)]/Segment_Number)"!]
        [!VAR "SEGMENT_PRG_CNT_MAX"="num:inttohex(Blocks/*[number($BLOCK_IDX)]/Block_Programming_Counter_Max)"!]
        [!VAR "SEGMENT_ID"="(Blocks/*[number($BLOCK_IDX)]/First_Segment)"!]
    {
        [!"$BLOCK_IDENT"!]U,[!WS "23"!]/* Block Identifier */
        PROG_SEG_[!"$SEGMENT_NAME"!],[!WS "2"!]/* Name of the first segment*/
        [!"$SEGMENT_NBR"!]U,[!WS "23"!]/* Number of segments contained in the block */
        [!"$SEGMENT_PRG_CNT_MAX"!]U,[!WS "23"!]/* Maximum number of programming allowed */
    },
    [!ENDFOR!]
    [!IF "General/PreliminaryErasing = 'true'"!]
    /* A virtual block containing all the segments in order to support preliminary erasing */
        [!VAR "SEGMENT_NAME"="text:toupper(name(Segments/*[number(1)]))"!]
        [!VAR "SEGMENT_NBR"="num:dectoint(count(Segments/*))"!]
    {
        PROG_MAX_BLOCK_ID,[!WS "10"!]/* Block Identifier */
        PROG_SEG_[!"$SEGMENT_NAME"!],[!WS "2"!]/* Name of the first segment*/
        [!"$SEGMENT_NBR"!]U,[!WS "23"!]/* Number of segments contained in the block */
        0U,[!WS "26"!]/* Maximum number of programming allowed */
    }
    [!ENDIF!]
};
[!ENDIF!]

[!/*All segments shall be erased on reception of EraseMemory so we generate a single block containing all segments */!]
[!IF "((node:exists(as:modconf('ProgOEMInd')) and OemInd/Erase_Mode = 'All') or (node:exists(as:modconf('ProgVCC'))))"!]
const tProg_Block    stCfgBlock[PROG_BLOCK_NB] =
{
    [!VAR "SEGMENT_NAME"="text:toupper(name(Segments/*[number(1)]))"!]
    [!VAR "SEGMENT_NBR"="num:dectoint(count(Segments/*))"!]
    {
        0,/* Block Identifier */
        PROG_SEG_[!"$SEGMENT_NAME"!],/* Name of the first segment*/
        [!"$SEGMENT_NBR"!]U,/* Number of segments contained in the block */
        0,/* Maximum number of programming allowed */
    },
};
[!ENDIF!]

[!IF "(not((as:modconf('BM')/Security/SecureBoot/SECURE_AUTHENTICATED_BOOT = 'OFF') and (as:modconf('Prog')/Security/Secure_Checksum_computation = 'false'))) and
          (node:exists(as:modconf('ProgDAG')) or (node:exists(as:modconf('ProgFCA')) and as:modconf('ProgFCA')/General/PROG_FCA_VARIANT='Atlantis_High'))"!]
const tProg_BlockSecureBootInfo    stCfgBlockSecureBootInfo[PROG_BLOCK_NB] =
{
    [!FOR "BLOCK_IDX" = "1" TO "$BLOCK_MAX"!]
        [!VAR "BLOCK_IDENT"="num:inttohex(Blocks/*[number($BLOCK_IDX)]/Block_Identifier)"!]
        [!VAR "START_ADDRESS"="num:inttohex(Blocks/*[number($BLOCK_IDX)]/SecureBoot/Start_Address_Secure_Boot_Verification)"!]
        [!VAR "LENGTH"="num:inttohex(Blocks/*[number($BLOCK_IDX)]/SecureBoot/Length_Secure_Boot_Verification)"!]
    {
        [!WS "8"!][!"$START_ADDRESS"!]U,[!WS "17"!]/* Start Address for the Secure Boot Verification */
        [!WS "8"!][!"$LENGTH"!]U,[!WS "17"!]/* Length of the block for the Secure Boot Verification */
        [!"$BLOCK_IDENT"!]U,[!WS "23"!]/* Block Identifier */
        [!WS "8"!][!IF "Blocks/*[number($BLOCK_IDX)]/SecureBoot/Verified_For_Secure_Boot='Block will be verified'"!]PROG_TRUE,[!WS "18"!][!ELSE!]PROG_FALSE,[!WS "17"!][!ENDIF!]/* Block will be verified by the Secure Boot */
        [!WS "8"!][!IF "Blocks/*[number($BLOCK_IDX)]/SecureBoot/Blocker_for_Software_execution='Will block software execution'"!]PROG_TRUE,[!WS "18"!][!ELSE!]PROG_FALSE,[!WS "17"!][!ENDIF!]/* Block will prevent the execution of software if Secure Boot verification is failed */
    },
    [!ENDFOR!]
};
[!ENDIF!]

[!ELSE!]
const tCfgSegmentType stConstConfigSegment[PROG_SEGMENT_NB] =
{
    [!VAR "NBR_PROT_CAL"="0"!]
    [!FOR "SEGMENT_IDX" = "1" TO "$SEGMENT_MAX"!]
        [!VAR "START_ADD"="num:inttohex(Segments/*[number($SEGMENT_IDX)]/Reprog_Start_Address)"!]
        [!VAR "END_ADD"="num:inttohex(Segments/*[number($SEGMENT_IDX)]/Reprog_End_Address)"!]
        [!VAR "ERASE_START_ADD"="num:inttohex(Segments/*[number($SEGMENT_IDX)]/Erase_Start_Address)"!]
        [!VAR "ERASE_END_ADD"="num:inttohex(Segments/*[number($SEGMENT_IDX)]/Erase_End_Address)"!]
        [!VAR "MEM_NAME" = "text:toupper(name(node:ref(Segments/*[number($SEGMENT_IDX)]/Memory)))"!]
        [!VAR "ACCESS_TYPE"="num:Segments/*[number($SEGMENT_IDX)]/Access_Type"!]
        [!FOR "MEMORY_IDX" = "1" TO "$MEMORY_MAX"!]
            [!IF "$MEM_NAME = text:toupper(name(Memory/*[number($MEMORY_IDX)]))"!]
                [!VAR "SELECTED_MEM_IDX" = "num:dectoint($MEMORY_IDX - 1)"!]
            [!ENDIF!]
        [!ENDFOR!]
    {
        [!"$START_ADD"!]U,
        [!"$END_ADD"!]U,
        [!"$ERASE_START_ADD"!]U,
        [!"$ERASE_END_ADD"!]U,
        [!"$SELECTED_MEM_IDX"!]U,
        PROG_MEM_ACCESS_TYPE_[!"$ACCESS_TYPE"!],
[!IF "node:exists(as:modconf('ProgGM'))"!]
        [!"Segments/*[number($SEGMENT_IDX)]/Partition_Type"!],
[!ENDIF!]
    },
    [!ENDFOR!]
};


tCfgSegmentType stConfigSegment[PROG_SEGMENT_NB];
[!ENDIF!]

[!IF "node:exists(as:modconf('ProgOEMInd'))"!]
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
[!ENDIF!]

[!IF "node:exists(as:modconf('ProgGM'))"!]
/* Pointer to App Sw Info */
u8* m_pubAppSwInfo = (u8*)PROG_APP_SW_INFO_ADDR;
/* Programmed PSI value */
const u8 m_aCfgPSIProgrammedValue[PROG_PSI_VAL_SIZE] =
{
    0x[!"substring(GM//PSI_Programmed,1,2)"!],
    0x[!"substring(GM//PSI_Programmed,3,2)"!],
    0x[!"substring(GM//PSI_Programmed,5,2)"!],
    0x[!"substring(GM//PSI_Programmed,7,2)"!],
    0x[!"substring(GM//PSI_Programmed,9,2)"!],
    0x[!"substring(GM//PSI_Programmed,11,2)"!],
    0x[!"substring(GM//PSI_Programmed,13,2)"!],
    0x[!"substring(GM//PSI_Programmed,15,2)"!],
};
/* Revoked PSI value */
const u8 m_aCfgPSIRevokedValue[PROG_PSI_VAL_SIZE] =
{
    0x[!"substring(GM//PSI_Revoked,1,2)"!],
    0x[!"substring(GM//PSI_Revoked,3,2)"!],
    0x[!"substring(GM//PSI_Revoked,5,2)"!],
    0x[!"substring(GM//PSI_Revoked,7,2)"!],
    0x[!"substring(GM//PSI_Revoked,9,2)"!],
    0x[!"substring(GM//PSI_Revoked,11,2)"!],
    0x[!"substring(GM//PSI_Revoked,13,2)"!],
    0x[!"substring(GM//PSI_Revoked,15,2)"!],
};

/* Bootloader information */
#define PROG_BOOT_INFO_START_SEC_CONST_UNSPECIFIED
#include <MemMap.h>
const tBootInfoBlock m_stBootInfoBlock =
{
    [!"num:inttohex(GM//BCID)"!]U, /*  BICD value */
[!IF "GM/EcuId_Source = 'Tresos_Configuration'"!]
    /* ECU ID */
    {
        0x[!"substring(GM//ECU_ID,1,2)"!],
        0x[!"substring(GM//ECU_ID,3,2)"!],
        0x[!"substring(GM//ECU_ID,5,2)"!],
        0x[!"substring(GM//ECU_ID,7,2)"!],
        0x[!"substring(GM//ECU_ID,9,2)"!],
        0x[!"substring(GM//ECU_ID,11,2)"!],
        0x[!"substring(GM//ECU_ID,13,2)"!],
        0x[!"substring(GM//ECU_ID,15,2)"!],
        0x[!"substring(GM//ECU_ID,17,2)"!],
        0x[!"substring(GM//ECU_ID,19,2)"!],
        0x[!"substring(GM//ECU_ID,21,2)"!],
        0x[!"substring(GM//ECU_ID,23,2)"!],
        0x[!"substring(GM//ECU_ID,25,2)"!],
        0x[!"substring(GM//ECU_ID,27,2)"!],
        0x[!"substring(GM//ECU_ID,29,2)"!],
        0x[!"substring(GM//ECU_ID,31,2)"!],
    },
[!ENDIF!]
    /* ECU name */
    {
        [!VAR "SEGMENT_MAX"="num:dectoint(string-length(GM/ECU_Name))"!]
        [!FOR "SEGMENT_IDX" = "1" TO "$SEGMENT_MAX"!]
        [!WS "8"!]'[!"substring(GM//ECU_Name,$SEGMENT_IDX,1)"!]',
        [!ENDFOR!]
        [!FOR "SEGMENT_IDX" = "$SEGMENT_MAX" TO "7"!]
        [!WS "8"!]0x00,
        [!ENDFOR!]
    },
    /* ECU subject name */
    {
        0x[!"substring(GM//Subject_Name,1,2)"!],
        0x[!"substring(GM//Subject_Name,3,2)"!],
        0x[!"substring(GM//Subject_Name,5,2)"!],
        0x[!"substring(GM//Subject_Name,7,2)"!],
        0x[!"substring(GM//Subject_Name,9,2)"!],
        0x[!"substring(GM//Subject_Name,11,2)"!],
        0x[!"substring(GM//Subject_Name,13,2)"!],
        0x[!"substring(GM//Subject_Name,15,2)"!],
        0x[!"substring(GM//Subject_Name,17,2)"!],
        0x[!"substring(GM//Subject_Name,19,2)"!],
        0x[!"substring(GM//Subject_Name,21,2)"!],
        0x[!"substring(GM//Subject_Name,23,2)"!],
        0x[!"substring(GM//Subject_Name,25,2)"!],
        0x[!"substring(GM//Subject_Name,27,2)"!],
        0x[!"substring(GM//Subject_Name,29,2)"!],
        0x[!"substring(GM//Subject_Name,31,2)"!],
    },
    /* Boot Part Number */
    {
        0x[!"substring(GM//BOOT_Part_Number,1,2)"!],
        0x[!"substring(GM//BOOT_Part_Number,3,2)"!],
        0x[!"substring(GM//BOOT_Part_Number,5,2)"!],
        0x[!"substring(GM//BOOT_Part_Number,7,2)"!],
    },
    /* Boot DLS */
    {
        '[!"substring(GM//BOOT_DLS,1,1)"!]',
        '[!"substring(GM//BOOT_DLS,2,1)"!]',
    },
    /* Number of Protected Calibrations*/
        [!VAR "NBR_PROT_CAL"="num:dectoint(0)"!]
[!FOR "SEGMENT_IDX" = "1" TO "$SEGMENT_MAX"!]
[!IF "'PROG_PROT_CALIBRATION_PARTITION' = Segments/*[number($SEGMENT_IDX)]/Partition_Type"!]
        [!VAR "NBR_PROT_CAL" = "num:dectoint($NBR_PROT_CAL + 1)"!]
[!ENDIF!]
[!ENDFOR!]
        [!"$NBR_PROT_CAL"!]U,
[!IF "$NBR_PROT_CAL > num:dectoint(0)"!]
    /*Protected Partition IDs*/
    {
[!VAR "PROT_CAL_PARTITION_ID"="num:dectoint(0)"!]
[!FOR "SEGMENT_IDX" = "1" TO "$SEGMENT_MAX"!]
[!IF "'PROG_PROT_CALIBRATION_PARTITION' = Segments/*[number($SEGMENT_IDX)]/Partition_Type"!]
[!VAR "PROT_CAL_PARTITION_ID"="num:dectoint(Segments/*[number($SEGMENT_IDX)]/Protected_Partition_ID)"!]
        [!"$PROT_CAL_PARTITION_ID"!]U,
[!ENDIF!]
[!ENDFOR!]
    },
[!ENDIF!]
};
#define PROG_BOOT_INFO_STOP_SEC_CONST_UNSPECIFIED
#include <MemMap.h>
[!ENDIF!]

