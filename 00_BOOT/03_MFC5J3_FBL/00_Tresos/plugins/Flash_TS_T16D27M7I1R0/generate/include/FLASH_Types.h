#ifndef FLASH_TYPES_H
#define FLASH_TYPES_H

/*===============================================================================*/
/*                                                                               */
/*                               FLASH layers                                    */
/*                                                                               */
/* ------------------------------------------------------------------------------*/
/*                                                                               */
/*                              FLASH  configuration                             */
/*                                                                               */
/*===============================================================================*/
/*%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%                                        */
/*%%   _____________________________   %%  \file FLASH_Types.h                   */
/*%%  |                             |  %%  \brief FLASH layer implementation     */
/*%%  |   &&&&&   &&&&&             |  %%  Module version: 7.1.6               */
/*%%  |   &       &    &            |  %%  TARGET: TRICORE                     */
/*%%  |   &&&&    &&&&&             |  %%  DERIVATE: TC38XQ                 */
/*%%  |   &       &    &            |  %%                                        */
/*%%  |   &&&&&   &&&&&             |  %%                                        */
/*%%  |_____________________________|  %%                                        */
/*%%                                   %%                                        */
/*%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%                                        */
/*===============================================================================*/
/* Copyright 2017 by Elektrobit Automotive GmbH                                  */
/* All rights exclusively reserved for Elektrobit Automotive GmbH,               */
/* unless expressly agreed to otherwise.                                         */
/*===============================================================================*/
[!AUTOSPACING!]

/*============================= PUBLIC DEFINITIONS ==============================*/
/*                                                                               */
/*===============================================================================*/
/* - Public Types                                                                */
/** \brief Define the use of COSMIC compiler*/
#define COSMIC  0U
/** \brief Define the use of GHS compiler*/
#define GHS     1U
/** \brief Define the use of IAR compiler*/
#define IAR     2U
/** \brief Define the use of TASKING compiler*/
#define TASKING 3U
/** \brief Define the use of WINDRIVER compiler*/
#define WINDRIVER 4U
/** \brief Define the use of HIGHTEC compiler*/
#define HIGHTEC 5U
/** \brief Define the use of Other compiler*/
#define Other   6U

/** \brief Define the compiler used*/
[!IF "General/ProjectCompiler = 'COSMIC'"!]
#define FLASH_COMPILER COSMIC
[!ELSEIF "General/ProjectCompiler = 'GHS'"!]
#define FLASH_COMPILER GHS
[!ELSEIF "General/ProjectCompiler = 'IAR'"!]
#define FLASH_COMPILER IAR
[!ELSEIF "General/ProjectCompiler = 'TASKING'"!]
#define FLASH_COMPILER TASKING
[!ELSEIF "General/ProjectCompiler = 'WINDRIVER'"!]
#define FLASH_COMPILER WINDRIVER
[!ELSEIF "General/ProjectCompiler = 'HIGHTEC'"!]
#define FLASH_COMPILER HIGHTEC
[!ELSE!]
[!/* ProjectCompiler field is "Other" */!]
#define FLASH_COMPILER Other
[!ENDIF!]

/** \brief Define how the pointers should be consider according the compiler*/
#if (FLASH_COMPILER == COSMIC)
    #define FLASH_FAR_POINTER *
    #define FLASH_FAR_ACCESS
#elif (FLASH_COMPILER == GHS)
    #define FLASH_FAR_POINTER *
    #define FLASH_FAR_ACCESS
#elif (FLASH_COMPILER == IAR)
    #define FLASH_FAR_POINTER *__far
    #define FLASH_FAR_ACCESS __far
#elif (FLASH_COMPILER == TASKING)
    #define FLASH_FAR_POINTER *
    #define FLASH_FAR_ACCESS
#elif (FLASH_COMPILER == WINDRIVER)
    #define FLASH_FAR_POINTER *
    #define FLASH_FAR_ACCESS
#elif (FLASH_COMPILER == HIGHTEC)
    #define FLASH_FAR_POINTER *
    #define FLASH_FAR_ACCESS
#else
    #define FLASH_FAR_POINTER *
    #define FLASH_FAR_ACCESS
#endif

[!IF "General/UseSectorTab = 'true'"!]
/** \brief Define how many sectors are configured*/
#define FLASH_MAX_SECTOR        [!"num:dectoint(count(FlsSector/*))"!]U

 /** \brief Define the size of the sector info tab*/
#define FLASH_INFO_SIZE         [!"num:dectoint(count(FlsSector/*))"!]U
[!ELSE!]
/** \brief Define the base adress of the flash memory*/
#define FLASH_BASE_ADDR         [!"num:inttohex(General/Flash_Base_Addr)"!]U
/** \brief Define the size of every memory sectors*/
#define FLASH_SECTOR_SIZE       [!"num:inttohex(General/Flash_Sector_Size)"!]U
/** \brief Define the number of memory sectors configured*/
#define FLASH_MAX_SECTOR        [!"num:dectoint(General/Flash_Max_Sector)"!]U
/** \brief Define the size of the sector info tab*/
#define FLASH_INFO_SIZE        1U
[!ENDIF!]



[!IF "General/ActivateSecurityCheck = 'true'"!]
/** \brief Define how many sectors are configured*/
#define FLASH_MAX_PROTECTED_AREA_NB        [!"num:dectoint(count(FlashMemoryAreasProtection/*))"!]U
[!ENDIF!]
/* Different flash status */
/** \brief FLASH functions status is OK*/
#define FLASH_NO_ERROR          0x01U
/** \brief The flash memory cannot be accessed correctly*/
#define FLASH_ACCESS_ERROR      0x02U
/** \brief The flash memory cannot be accessed correctly due to protection error*/
#define FLASH_PROT_ERROR        0x03U
/** \brief The flash memory is blank so the data have not been written correctly*/
#define FLASH_BLANKCHEK_ERROR   0x04U
/** \brief The flash memory is busy*/
#define FLASH_BUSY              0x05U
/** \brief The function is not supported*/
#define FLASH_FUNC_NOT_SUPPORTED 0x06U

#define FLASH_PROCESS_WRITE     0x01U
#define FLASH_PROCESS_ERASE     0x02U

#define FLASH_MODE_SLICER_SYNC 1U
#define FLASH_MODE_BLOCKER_SYNC 2U
[!IF "General/Flash_Mode = 'Slicer_Sync'"!]
#define FLASH_MODE  FLASH_MODE_SLICER_SYNC
[!ELSEIF "General/Flash_Mode = 'Blocker_Sync'"!]
#define FLASH_MODE  FLASH_MODE_BLOCKER_SYNC
[!ENDIF!]

/** \brief Status of flash operations of data flash type */
typedef u8 tFlashStatus;

/** \brief Define the data flash type */
typedef u32 tFlashData;

/** \brief Define the flash address type*/
#if (FLASH_COMPILER == COSMIC)
    typedef volatile const @far @gpage tFlashData * tFlashAddress;
#elif (FLASH_COMPILER == GHS)
    typedef u32 tFlashAddress;
#elif (FLASH_COMPILER == TASKING)
    typedef u32 tFlashAddress;
#else
    typedef u32 tFlashAddress;
#endif

/** \brief FLASH layer FALSE define used for boolean actions in the layer*/
#define FLASH_FALSE   0U
/** \brief FLASH layer FALSE define used for boolean actions in the layer*/
#define FLASH_TRUE    1U
/** \brief Boolean for FLASH layer*/
typedef u8 tFlashBoolean;

[!IF "General/ActivateSecurityCheck = 'true'"!]
/** \brief Structure of protected memory areas containing adress and length information*/
typedef struct
{
    u32                  Start_Address; /* Start Address of the sector */
    u32                  Length;        /* Length of the sector */
}tFlashActivateSecurityCheck;
[!ENDIF!]

/** \brief Define the size of the temporary write buffer*/



#define FLASH_WRITE_BUFFER   (FLASH_PAGES_SIZE_BYTE)

[!IF "General/ActivateSecurityCheck = 'true'"!]
/** \brief Define if memory area protection shall be managed by the Flash driver */
#define FLASH_MANAGE_SECURITY_CHECK
[!ENDIF!]
#endif      /* FLASH_TYPES_H */
