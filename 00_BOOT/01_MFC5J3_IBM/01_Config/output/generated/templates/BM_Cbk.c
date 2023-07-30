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
/*%%   _____________________________   %%  \file BM_Cbk.c                        */
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

/*=============================== FILE INCLUSION ================================*/
/*                                                                               */
/*-------------------------------------------------------------------------------*/
/* - Header Files                                                                */

#include "EB_Prj.h"

/*                                                                               */
/*===============================================================================*/




/*============================= PUBLIC DEFINITIONS ==============================*/
/*                                                                               */
/*-------------------------------------------------------------------------------*/
/* - Public Variables                                                            */

/*-------------------------------------------------------------------------------*/
/* - Public Function Prototypes                                                  */

/*-------------------------------------------------------------------------------*/
/* - Public Callback Prototypes                                                  */

/*                                                                               */
/*===============================================================================*/

/*============================ PRIVATE DEFINITIONS ==============================*/
/*                                                                               */
/*-------------------------------------------------------------------------------*/
/* - Private Constants                                                           */

/*-------------------------------------------------------------------------------*/
/* - Private Variables                                                           */

/*-------------------------------------------------------------------------------*/
/* - Private Macros                                                              */

/*-------------------------------------------------------------------------------*/
/* - Private Function Prototypes                                                 */

/*                                                                               */
/*===============================================================================*/


/*=============================== IMPLEMENTATION ================================*/
/*                                                                               */

/*-------------------------------------------------------------------------------*/
/* - Public Functions                                                            */



/*----------------------------{BM_CheckProgRequest}----------------------------------*/
extern tBMBoolean BM_CheckProgRequest(void)
{
    return BM_TRUE;
}
/*----------------------------{end BM_CheckProgRequest}------------------------------*/

/*----------------------------{BM_CustomCheckValidAppl}----------------------------------*/
extern tBMBoolean BM_CustomCheckValidAppl(void)
{
    return BM_TRUE;
}
/*----------------------------{end BM_CustomCheckValidAppl}------------------------------*/

/*----------------------------{BM_CustomCheckValidBLU}----------------------------------*/
extern tBMBoolean BM_CustomCheckValidBLU(void)
{
    return BM_TRUE;
}
/*----------------------------{end BM_CustomCheckValidBLU}------------------------------*/

/*----------------------------{BM_CustomCheckValidBL}----------------------------------*/
extern tBMBoolean BM_CustomCheckValidBL(void)
{
    return BM_TRUE;
}
/*----------------------------{end BM_CustomCheckValidBL}------------------------------*/

/*----------------------------{BM_JumpToApplication}----------------------------------*/
extern void BM_JumpToApplication(void)
{

}
/*----------------------------{end BM_JumpToApplication}------------------------------*/

/*----------------------------{BM_JumpToBLU}----------------------------------*/
extern void BM_JumpToBLU(void)
{

}
/*----------------------------{end BM_JumpToBLU}------------------------------*/

/*----------------------------{BM_JumpToBL}----------------------------------*/
extern void BM_JumpToBL(void)
{

}
/*----------------------------{end BM_JumpToBL}------------------------------*/





void BM_DisableECCCheck(void)
{

}

void BM_EnableECCCheck(void)
{

}



