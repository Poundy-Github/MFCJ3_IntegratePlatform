/*===============================================================================*/
/*                                                                               */
/*                               BOOT Layers                                     */
/*                                                                               */
/* ----------------------------------------------------------------------------- */
/*                                                                               */
/*                               SA layer                                        */
/*                                                                               */
/*===============================================================================*/
/*%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%                                        */
/*%%   _____________________________   %%  \file SA_Cbk.c                        */
/*%%  |                             |  %%  \brief SA layer source plugin file    */
/*%%  |   &&&&&   &&&&&             |  %%  Module version: 1.19.0 BL3 */
/*%%  |   &       &    &            |  %%                                        */
/*%%  |   &&&&    &&&&&             |  %%                                        */
/*%%  |   &       &    &            |  %%                                        */
/*%%  |   &&&&&   &&&&&             |  %%                                        */
/*%%  |_____________________________|  %%                                        */
/*%%                                   %%                                        */
/*%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%                                        */
/*===============================================================================*/
/* Copyright 2015 by Elektrobit Automotive GmbH                                  */
/* All rights exclusively reserved for Elektrobit Automotive GmbH,               */
/* unless expressly agreed to otherwise.                                         */
/*===============================================================================*/

/*=============================== FILE INCLUSION ================================*/
/*                                                                               */
#include "EB_Prj.h"
#include "board.h"
#include "TSMem.h"

/*=============================== IMPLEMENTATION ================================*/
/*                                                                               */
static const u8 aubCoef[4] ={0x4B, 0x2D, 0x41, 0x62};
static const u8  APP_KEY[4] = {0x52, 0x7F, 0x63, 0x74};

#if (SA_SEED_TYPE != SA_SEED_CSM_RANDOM)
/** \brief API that calculates the security access key
 **
 ** This callback is called on reception of SecurityAccess service to perfom
 ** computation of the security key based on a random seed.
 **
 ** \param[in] aubSeed Address of the seed array
 ** \param[out] aubCalculatedKey Address where the calculated key will be copied
 **/
uint32 t_Key_ul = 0u;

extern void AES_CMAC(const unsigned char *key, const unsigned char *input, int length,
		unsigned char *mac);
unsigned char k[16] = {0x1c,0x96,0x31,0x39,0x94,0xf0,0xbc,0xa8,0xdd,0x4f,0x55,0x1d,0x42,0x8a,0xb4,0x9c};
unsigned char d[16] = {0xF2,0xFE,0xF3,0xF4,0xF5,0xF6,0xF1,0xF2,0xF3,0xF4,0xF5,0xF6,0xF1,0xF2,0xF3,0xF4};
unsigned char aes_res[16] = {0};
void SA_CustomCalculateKey(u8 * aubSeed, u8 * aubCalculatedKey)
{
#if 0 // M18
    u8 aubSeed1[4];
    u8 aubSeed2[4];
    u8 aubSeed3[4];
    u8 aubKey1[4];

    aubSeed1[0] = aubSeed[0]<<5 | aubSeed[0]>>3;
    aubSeed1[1] = aubSeed[1]<<5 | aubSeed[1]>>3;
    aubSeed1[2] = aubSeed[2]<<5 | aubSeed[2]>>3;
    aubSeed1[3] = aubSeed[3]<<5 | aubSeed[3]>>3;

    aubSeed2[0] = (aubSeed1[0]<<1 & 0xAA) | (aubSeed1[0]>>1 & 0x55);
    aubSeed2[1] = (aubSeed1[1]<<1 & 0xAA) | (aubSeed1[1]>>1 & 0x55);
    aubSeed2[2] = (aubSeed1[2]<<1 & 0xAA) | (aubSeed1[2]>>1 & 0x55);
    aubSeed2[3] = (aubSeed1[3]<<1 & 0xAA) | (aubSeed1[3]>>1 & 0x55);

    aubSeed3[0] = aubSeed2[0]<<3 | aubSeed2[1]>>5;
    aubSeed3[1] = aubSeed2[1]<<3 | aubSeed2[0]>>5;
    aubSeed3[2] = aubSeed2[2]<<3 | aubSeed2[3]>>5;
    aubSeed3[3] = aubSeed2[3]<<3 | aubSeed2[2]>>5;

    aubKey1[0] = aubSeed3[0] ^ aubCoef[0];
    aubKey1[1] = aubSeed3[1] ^ aubCoef[1];
    aubKey1[2] = aubSeed3[2] ^ aubCoef[2];
    aubKey1[3] = aubSeed3[3] ^ aubCoef[3];

    aubCalculatedKey[0] = ~aubKey1[0];
    aubCalculatedKey[1] = ~aubKey1[1];
    aubCalculatedKey[2] = ~aubKey1[2];
    aubCalculatedKey[3] = ~aubKey1[3];
#else
    //C673
    /* temporary variables */
    uint32 t_Iteration_ul;
    uint32 t_Seed_ul = 0u;
	uint32 t_Seed2_ul = 0u;
	// uint32 
    uint32 t_Key1_ul = 0u;
	uint32 t_Key2_ul = 0u;
	static uint32 const App_Key_Const = 0x527F6374;
    t_Key_ul = 0u;

    t_Seed_ul = (uint32)(aubSeed[3] + (aubSeed[2]<<8) + (aubSeed[1]<<16) + (aubSeed[0]<<24));
    if (t_Seed_ul != 0)
    {
		t_Key1_ul = t_Seed_ul ^ App_Key_Const;
		for (t_Iteration_ul = 0u; t_Iteration_ul < 32; t_Iteration_ul++)
		{
			t_Seed2_ul |= ((t_Seed_ul >> t_Iteration_ul) & 0x1) << (31 - t_Iteration_ul);
		}
        t_Key2_ul = t_Seed2_ul ^ App_Key_Const;
		t_Key_ul = t_Key1_ul + t_Key2_ul;
    }
    else
    {
        /* do nothing*/
    }
    aubCalculatedKey[3] = t_Key_ul & 0xff;
    aubCalculatedKey[2] = t_Key_ul >>8 & 0xff;
    aubCalculatedKey[1] = t_Key_ul >> 16 & 0xff;
    aubCalculatedKey[0] = t_Key_ul >> 24& 0xff;

    TS_MemSet(aes_res,0,16);
    AES_CMAC((unsigned char*)k, d, 16, (unsigned char*)aes_res);
#endif
}
#endif /*(SA_SEED_TYPE != SA_SEED_CSM_RANDOM)*/


#if (SA_ANTISCANNING_ENABLED == STD_ON)
/** \brief API that stores the security access anti-scanning retry counter
 **
 ** This callback is called on reception of SecurityAccess service in case
 ** anti-scanning feature is activated. The counter value provided as parameter
 ** shall be stored in non-volatile memory.
 **
 ** \param[in] RetryCntValue Value of security access anti-scanning retry counter
 **/
void SA_CustomStoreAsRetryCnt(u8 RetryCntValue)
{
    OSC_PARAM_UNUSED(RetryCntValue);
}
#endif /*(PROG_SA_ANTISCANNING_ENABLE == STD_ON)*/


#if (SA_ANTISCANNING_ENABLED == STD_ON)
/** \brief API that restores the security access anti-scanning retry counter
 **
 ** This callback is called at Bootloader startup (if anti-scanning feature is
 ** activated) to get the retry counter value from non-volatile memory.
 **
 ** \return Value of security access anti-scanning retry counter
 **/
u8 SA_CustomRestoreAsRetryCnt(void)
{
    u8 RetAsRetryCnt = 0;
    /*Fetch from NVM*/
    return RetAsRetryCnt;
}
#endif /*(PROG_SA_ANTISCANNING_ENABLE == STD_ON)*/

