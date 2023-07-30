/*===============================================================================*/
/*                                                                               */
/*                               BOOT Layers                                     */
/*                                                                               */
/* ----------------------------------------------------------------------------- */
/*                                                                               */
/*                               BLUpdater layer                                 */
/*                                                                               */
/*===============================================================================*/
/*%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%                                        */
/*%%   _____________________________   %%  \file BLUpdater_Cbk.h                 */
/*%%  |                             |  %%                                        */
/*%%  |   &&&&&   &&&&&             |  %%  Module version: 1.3.0 BL3                */
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


#ifndef BLUPDATER_CBK_H
#define BLUPDATER_CBK_H

/** \brief Callback to set validity marker for New Bootloader
 **
 ** The validity of the New Bootloader shall be saved here
 **
 ** \param[in] eNewBootValidity status to write
 **
 ** \return Result application validation
 ** \retval BLU_TRUE finish successfully
 ** \retval BLU_FALSE Error happened during treatment (ErrorCode shall be filled in this case)
 **/
extern tBLUBoolean BLU_CustomSetValidityNewBootloader(tBLUBoolean eNewBootValidity);

/** \brief Callback to set validity marker pf the Bootloader Updater
 **
 ** The validity of the Bootloader Updater shall be saved here
 **
 ** \param[in] eBLUValidity status to write
 **
 ** \return Result application invalidation
 ** \retval BLU_TRUE Treatment finish successfully
 ** \retval BLU_FALSE Error happened during treatment 
 **/
extern tBLUBoolean BLU_CustomSetValidityBLUpdater(tBLUBoolean eBLUValidity);


/** \brief Callback to get Pdu ID
 ** Get the Rx Pdu Identifier on which the response after reset shall be sent
 **
 ** \param[out] pubRxPduId Rx Pdu Identifier pointer
 **
 **/
extern void BLU_CustomGetPduID(u16* pubRxPduId);


/** \brief Callback to trigger the Watchdog
 ** Watchdog can be triggered directly by using this callback.
 **
 **/
extern void BLU_CustomTriggerWatchdog(void);


/** \brief Initialization of modules of communication stack
 **
 **/
extern void BLU_Custom_Com_Init(void);



#endif 
