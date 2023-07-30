/*===============================================================================*/
/*                                                                               */
/*                               BOOT Layers                                     */
/*                                                                               */
/* ----------------------------------------------------------------------------- */
/*                                                                               */
/*                               BM layer                                        */
/*                                                                               */
/*===============================================================================*/
/*%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%                                        */
/*%%   _____________________________   %%  \file BM_Cbk.h                        */
/*%%  |                             |  %%  \brief BM layer include plugin file   */
/*%%  |   &&&&&   &&&&&             |  %%  Module version: 1.15.0 BL3                */
/*%%  |   &       &    &            |  %%  Variant: OsekCore                  */
/*%%  |   &&&&    &&&&&             |  %%                                        */
/*%%  |   &       &    &            |  %%                                        */
/*%%  |   &&&&&   &&&&&             |  %%                                        */
/*%%  |_____________________________|  %%                                        */
/*%%                                   %%                                        */
/*%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%                                        */
/*===============================================================================*/
/* Copyright 2010 by Elektrobit Automotive GmbH                                  */
/* All rights exclusively reserved for Elektrobit Automotive GmbH,               */
/* unless expressly agreed to otherwise.                                         */
/*===============================================================================*/



#ifndef BM_CBK_H
#define BM_CBK_H
/*============================= PUBLIC DEFINITIONS ==============================*/
/*                                                                               */
/* - Public Callback Prototypes                                                  */


/** \brief API that check if a programming request has been received by the application
 **
 ** Callback is called: at Initial Boot startup to know if a programming request has
 **                     been received in Application
 **
 ** Callback shall implement: get information from application if a programming
 **                          request has been received (e.g: read a flag from
 **                          noinit RAM shared between Bootloader and
 **                           Application)
 **
 ** \return Result of check
 ** \retval TRUE Reprogramming request has been received
 ** \retval FALSE No reprogramming request received
 **/
extern tBMBoolean BM_CheckProgRequest(void);

/** \brief Callback checking if the application is valid or not
 **
 ** Callback is called: at Initial Boot startup.
 **
 ** Callback shall implement: It shall verify that the application
 ** with all its dependencies are correctly flashed
 ** and return the result of the check
 **
 ** \return Result of check
 ** \retval TRUE Application is valid
 ** \retval FALSE Application is not valid or not present
 **/
extern tBMBoolean BM_CustomCheckValidAppl(void);

/** \brief Callback checking if the Bootloader Updater Programm is valid or not
 **
 ** Callback is called: at Initial Boot startup.
 **
 ** Callback shall implement: It shall verify that the Bootloader Updater Programm
 ** is correctly flashed and return the result of the check
 **
 ** \return Result of check
 ** \retval TRUE BLU Updater Programm is valid
 ** \retval FALSE BLU is not valid or not present
 **/
extern tBMBoolean BM_CustomCheckValidBLU(void);

/** \brief Callback checking if the Bootloader is valid or not
 **
 ** Callback is called: at Initial Boot startup.
 **
 ** Callback shall implement: It shall verify that the Bootloader
 ** is correctly flashed and return the result of the check
 **
 ** \return Result of check
 ** \retval TRUE Bootloader is valid
 ** \retval FALSE Bootloader is not valid or not present
 **/
extern tBMBoolean BM_CustomCheckValidBL(void);

/** \brief Callback performing jump to application software
 **
 ** Callback is called: at Initial Boot startup if application is valid and shall
 **                    be executed
 **
 ** Callback shall implement: jump to application start address
 **
 **/
extern void BM_JumpToApplication(void);

/** \brief Callback performing jump to Bootloader Updater Programm
 **
 ** Callback is called: at Initial Boot startup if Bootloader Updater Programm is 
 ** valid and shall be executed
 **
 ** Callback shall implement: jump to BLU start address
 **
 **/
extern void BM_JumpToBLU(void);

/** \brief Callback performing jump to Bootloader
 **
 ** Callback is called: at Initial Boot startup if Bootloader is valid and shall
 **                    be executed
 **
 ** Callback shall implement: jump to Bootloader start address
 **
 **/
extern void BM_JumpToBL(void);




/** \brief Callback that shall disable ECC if needed
 ** Callback is called: When Bootloader perform read access on Flash that can be
 **                     unprogrammed and can cause ECC error
 **
 ** Callback shall implement: If needed, disabling of ECC check
 **                           Hardware specific)
 **/
extern void BM_DisableECCCheck(void);

/** \brief Callback that shall enable ECC if needed
 ** Callback is called: After Bootloader has performed a read access on Flash
 **                    that can be unprogrammed and can cause ECC error
 **
 ** Callback shall implement: If needed, enabling of ECC check
 **                          (Hardware specific)
 **/
extern void BM_EnableECCCheck(void);




#endif      /* BM_CBK_H */
