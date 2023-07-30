#ifndef BM_PUB_H
#define BM_PUB_H

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
/*%%   _____________________________   %%  \file BM_Pub.h                        */
/*%%  |                             |  %%  \brief BM layer include plugin file   */
/*%%  |   &&&&&   &&&&&             |  %%  Module version: 1.3.0 BL-3.X                */
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

#include "BM_Cfg.h"

#if ((BM_AUTHENTICATED_BOOT_ENABLE == STD_ON) || (BM_SECURE_BOOT_ENABLE == STD_ON))
#include "Csm.h"
#endif

/*============================= PUBLIC DEFINITIONS ==============================*/
/*                                                                               */
/*-------------------------------------------------------------------------------*/
/* - Public Variables                                                            */

/*-------------------------------------------------------------------------------*/
/* - Public Function Prototypes                                                  */
/** \brief Bootmanager startup
 **
 ** Because of the presence of the bootloader, at the very beginning of
 ** the ECU startup shall be the first one called.
 **
 ** This function handles:
 ** - The hardware initialization
 ** - The check of the boot flag
 ** - The validity of application
 ** - The initialization of all EB layer if bootloader shall be started
 **
 **/
extern void BM_StartUp(void);


/*-------------------------------------------------------------------------------*/
/* - Public Callback Prototypes                                                  */
#if (BM_TIMEOUT_CHECK == BM_TIMEOUT_CHECK_ON)
/** \brief Manage BM layer
 **
 ** This function will ensure the good behaviour of the startup timeout of 5ms
 ** requested before checking the application validity.
 **
 ** BM_Manage shall be called at the same period and after EB_Manage.
 **
 **/
extern void BM_Manage (void);
#endif

#if ((BM_AUTHENTICATED_BOOT_ENABLE == STD_ON) || (BM_SECURE_BOOT_ENABLE == STD_ON))
/** \brief CSM notification callback
 **
 ** \param[in] result Csm calculation result
 **
 ** \return status
 ** \retval E_OK
 **
 **/
extern Std_ReturnType BM_CsmNotification(Csm_ReturnType result);
#endif

/*===============================================================================*/

#endif      /* BM_PUB_H */
