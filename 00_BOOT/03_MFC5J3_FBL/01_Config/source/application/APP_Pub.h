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

#ifndef APP_PUB_H
#define APP_PUB_H

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

/** \brief This API is called to do the application running area read treatment
 **
 ** \return Application running area
 **/
extern u8 APP_GetApplicationRunningArea(void);

/** \brief This API is called to do the application runningArea change treatment
 **
 ** \param[in] ubApplicationRunningArea The application runningArea for which the change was done
 **
 ** \return Change result
 ** \retval APP_TRUE Change success
 ** \retval APP_FALSE Change failure
 **/
extern tAppBoolean APP_ChangeToApplicationRunningArea(u8 ubApplicationRunningArea);

/** \brief This API is called to do the secure boot error write treatment
 **
 ** \param[in] ubApplicationRunningArea The application runningArea for which the write was done
 **
 ** \return Write result
 ** \retval APP_TRUE Write success
 ** \retval APP_FALSE Write failure
 **/
extern tAppBoolean APP_WriteSecureBootError(u8 ubApplicationRunningArea);

/** \brief This API is called to do the secure boot error erase treatment
 **
 ** \return Erase result
 ** \retval APP_TRUE Erase success
 ** \retval APP_FALSE Erase failure
 **/
extern tAppBoolean APP_EraseSecureBootError(void);

/** \brief This API is called to do the SecureUpdatingLog write treatment
 **
 ** \param[in] ubLogType The log type for which the write was done
 **
 ** \return Write result
 ** \retval APP_TRUE Write success
 ** \retval APP_FALSE Write failure
 **/
extern tAppBoolean APP_WriteSecureUpdatingLog(u8 ubLogType);

/** \brief This API is called to do the flash driver coherency check treatment
 **
 ** \return Check result
 ** \retval APP_TRUE Flash driver is coherency
 ** \retval APP_FALSE Flash driver is not coherency
 **/
extern tAppBoolean APP_CheckFlashDriverCoherency(void);

#endif      /* APP_PUB_H */
