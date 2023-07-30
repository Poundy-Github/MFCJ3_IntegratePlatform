#ifndef BM_PRIV_H
#define BM_PRIV_H

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
/*%%   _____________________________   %%  \file BM_Priv.h                       */
/*%%  |                             |  %%  \brief BM layer source plugin file    */
/*%%  |   &&&&&   &&&&&             |  %%  Module version: 1.3.0 BL-3.X */
/*%%  |   &       &    &            |  %%                                        */
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

/*============================ PRIVATE DEFINITIONS ==============================*/

/*-------------------------------------------------------------------------------*/
/* - Private Variables                                                           */
/*                                                                               */

/*===============================================================================*/

/*-------------------------------------------------------------------------------*/
/* - Private Macros                                                              */

/*                                                                               */
/*===============================================================================*/

/*-------------------------------------------------------------------------------*/
/* - Private Function Prototypes                                                 */
/*                                                                               */

/*===============================================================================*/

/*============================= PUBLIC DEFINITIONS ==============================*/
/*                                                                               */
/*-------------------------------------------------------------------------------*/
/* - Public Variables                                                            */


/*-------------------------------------------------------------------------------*/
/* - Public Function Prototypes                                                  */


#if ((BM_AUTHENTICATED_BOOT_ENABLE == STD_ON) || (BM_SECURE_BOOT_ENABLE == STD_ON))

/** \brief This function loops on all blocks and verify their checksum
 **
 ** \param[in] void
 **
 ** \return Result of treatment
 ** \retval BM_TRUE  Application integrity test succeeded
 ** \retval BM_FALSE Application integrity test failed
 **/
extern tBMBoolean BM_VerifyApplicationIntegrity(void);

#if (BM_CSM_HASH_USED == STD_ON)
/** \brief Calculate the hash value on the given data
 **
 ** This function allow to set the address and size for the Hash calculation
 **
 ** \param[in] pubDataToSign Data on which hash will be calculated
 ** \param[in] uwDataLength length of data to calculate hash on
 ** \param[out] pubHashValue calculated hash value
 **
 ** \return Result of treatment
 ** \retval BM_TRUE  Operation succeeded
 ** \retval BM_FALSE Operation failed
 **/
extern tBMBoolean BM_ComputeHash(u8 const * pubDataToSign, u32 uwDataLength, u8 * pubHashValue);
#endif

#if (BM_CSM_MAC_USED == STD_ON)
/** \brief Calculate the MAC value on the given data and compare it to the expected MAC value
 ** Get from the memory
 **
 ** This function allow to set the address and size for the MAC calculation
 **
 ** \param[in] pubExpectedChecksum Expected MAC value get from the memory
 ** \param[in] pubDataToSign Data on which MAC will be calculated
 ** \param[in] uwDataLength length of data to calculate MAC on
 **
 ** \return Result of treatment
 ** \retval BM_TRUE  Operation succeeded
 ** \retval BM_FALSE Operation failed
 **/
extern tBMBoolean BM_VerifyMac(u8 const * pubExpectedChecksum, u8 const * pubDataToSign, u32 uwDataLength);
#endif

#endif

#endif      /* BM_PRIV_H */
