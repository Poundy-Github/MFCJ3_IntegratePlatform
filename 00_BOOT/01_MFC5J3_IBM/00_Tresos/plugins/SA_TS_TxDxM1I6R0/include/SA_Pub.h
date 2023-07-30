#ifndef SA_PUB_H
#define SA_PUB_H

/*===============================================================================*/
/*                                                                               */
/*                                 Sa LAYER                                      */
/*                                                                               */
/* ----------------------------------------------------------------------------- */
/*                                                                               */
/*                               Security Access                                 */
/*                                                                               */
/*===============================================================================*/
/*%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%                                        */
/*%%   _____________________________   %%  \file SA_Pub.h                        */
/*%%  |                             |  %%                                        */
/*%%  |   &&&&&   &&&&&             |  %%  Module version: 1.6.3 BL-3.X */
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

#include "SA_Types.h"
/*============================= PUBLIC DEFINITIONS ==============================*/
/*                                                                               */
/*-------------------------------------------------------------------------------*/
/* - Public Variables                                                            */

/*-------------------------------------------------------------------------------*/
/* - Public Function Prototypes                                                  */

/** \brief Initialize layer
 **
 ** This function initializes the SA layer, shall be called only once at ECU startup
 **
 **/
extern void SA_Init(void);

/** \brief Manage the SA layer periodic task
**
** This function is the periodic function managing the SA layer
**
**/
extern void SA_Manage(void);

/** \brief Compute the key from an static key and a random Seed
 **
 ** This function is called upon correct SA1 request
 ** It first call SA_GetRandomValue to get a random value.
 ** Then it computes the key following an algorithm from this random seed
 ** and a static key predefined.
 ** The random generated Seed is then send back to lower layer.
 **
 ** \return Result of GetSeed action
 ** \param[out] aubSeed Output buffer to send back the random Seed
 **
 **/
extern tSaStatus SA_GetSeed(u8* aubSeed);

/** \brief Compare the received and calcluated key
 **
 ** This function is called upon correct SA2 request
 ** It compare the received key from the diagnostic request to the one calculated into SA_ComputeSeed
 ** It then return the result
 **
 ** \param[in] aubReceivedKey input buffer with the received key from the network
 **
 ** \return Result of comparison
 ** \retval PROG_STATUS_OK Both key are the same
 ** \retval PROG_STATUS_NOT_OK Both key are different
 **
 **/
extern tProgStatus SA_CompareKey(const u8* aubReceivedKey);

#if ((SA_COMPRESSION_STATE == SA_COMPRESSION_ENABLED) && PROG_CAL_PRESENT == STD_OFF)

/** \brief Decompression variable initialization
 **
 ** This function is called at init and for each request Download
 ** to intialize all decompression variable.
 **
 **/
extern void SA_DecompressInit (void);

/** \brief reinit decompression input param
 **
 ** This function Reinitializes the input decompression parameter after each TD
 **
 **/
extern void SA_DecompInputParamInit(void);


/** \brief store the data to be decompress
 **
 ** This function is used to store the data received from the network to
 ** an input buffer. The decompression will be done asynchronously afterward.
 **
 ** \param[in] pubData Input buffer where the data to decompress are stored
 ** \param[in] uwDataLength Length of data to decompress from the buffer
 **
 **/
extern void SA_DecompressData(u8* pubData, u16 uwDataLength);

/** \brief decompress a byte of the input buffer
 **
 ** This function Decompress a byte of the input buffer data with LZSS algorithm.
 ** Each decompressed byte is then store into an Output buffer
 **
 **/
extern void SA_DecompressManage(void);

/** \brief Accessor to get the decompressed data
 **
 ** This function allows to get the decompressed data from the buffer
 **
 ** \param[out] pubDecompData Output buffer where the data decompressed are copied
 ** \param[out] puwDecompressLength Total length of data decompressed
 **
 **/
extern tDecompressStateType SA_GetDecompressedData(u8** pubDecompData, u16* puwDecompressLength);

/** \brief freed the written data from output buffer
 **
 ** This function allows to freed the written data from output buffer
 **
 ** \param[in] uwLength length written with sucess that shall be freed from output buffer
 **
 **/
extern void SA_DecompWriteDataConfirmation(u16 uwLength);
#endif

#if (SA_USE_CRYPTO == STD_ON)
/** \brief API is a unique callback called by CSM module to treat random generation, encryption, decryption, hash and signature verification
 **
 ** \param[in] eCsmResult Csm treatment result
 **
 **/
extern Std_ReturnType SA_CsmNotification(Csm_ReturnType eCsmResult);
#endif /*(SA_USE_CRYPTO == STD_ON)*/

/** \brief API called by PROG module to get the SecurityAccess status
**
**
**/
extern tSaStatus SA_GetStatus(void);


/*                                                                               */
/*-------------------------------------------------------------------------------*/

#endif      /* SA_PUB_H */
