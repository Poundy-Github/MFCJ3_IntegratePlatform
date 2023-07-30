/*********************************************************************************/
/*                                                                               */
/*                               BOOT Layers                                     */
/*                                                                               */
/* ----------------------------------------------------------------------------- */
/*                                                                               */
/*                           BlPduR callbacks                                    */
/*                                                                               */
/*********************************************************************************/
/*%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%                                        */
/*%%   _____________________________   %%  \file BlPduR_Cbk.c                       */
/*%%  |                             |  %%                                        */
/*%%  |   &&&&&   &&&&&             |  %%  Module version: 0.13.0 BL-3.X                */
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
/******************************** FILE INCLUSION *********************************/
/*                                                                               */
/*-------------------------------------------------------------------------------*/
/* - Header Files: BlPduR                                                           */
#include "BlPduR_Prj.h"
#include "Base_Modules.h"   /* Module enable defines and standard config pointer names */
/*                                                                               */
/*********************************************************************************/

/****************************** PUBLIC DEFINITIONS *******************************/
/*                                                                               */
/*-------------------------------------------------------------------------------*/
/* - Public Variables                                                            */

/*-------------------------------------------------------------------------------*/
/* - Public Function Prototypes                                                  */

/*-------------------------------------------------------------------------------*/
/* - Public Callback Prototypes                                                  */
/*                                                                               */
/*********************************************************************************/
/*-------------------------------------------------------------------------------*/
/* - Private Macros                                                              */

/*-------------------------------------------------------------------------------*/
/* - Private Function Prototypes                                                 */

/*                                                                               */
/*********************************************************************************/

/******************************** IMPLEMENTATION *********************************/
/*                                                                               */

/*-------------------------------------------------------------------------------*/
/* - Public Functions                                                            */

/*-------------------------------------------------------------------------------*/
/* - Private Functions                                                           */

/*-------------------------------------------------------------------------------*/
/* - Public Callbacks                                                            */

/*                                                                               */
/*********************************************************************************/

/** \brief Get the Rx Pdu Identifier on which the response after reset shall be sent
 **
 ** \param[out] pubRxPduId Rx Pdu Identifier pointer
 **
 **/
void BlPduR_GetRxPduId(u8* pubRxPduId)
{
    *pubRxPduId = 0U;
}

/** \brief Store the Rx Pdu Identifier on which the request shall be responded after reset has been received
 **
 ** \param[in] pubRxPduId Rx Pdu Identifier
 **
 **/
void BlPduR_StoreRxPduId(u8 ubRxPduId)
{
    OSC_PARAM_UNUSED(ubRxPduId);
}


/** \brief Initialization of modules of communication stack and initialization of the stored PDUID of the active connection 
 **
 **/
void BlPduR_Custom_Com_Init(void)
{
#if (BLPDUR_USE_PDUR == STD_ON)
    /* If one of the ASR stack is configured initialize the PduR */
    PduR_Init(BASE_PDUR_CONFIG_PTR);
#endif

#if (BLPDUR_USE_CAN == STD_ON)
    /* Start Can Controller */
    Can_Init(&Can_17_McmCan_Config);
#endif

#if (BLPDUR_USE_CANIF == STD_ON)
    /* Start CanIf */
    CanIf_Init(BASE_CANIF_CONFIG_PTR);
#endif

#if (BLPDUR_USE_CANTP == STD_ON)
    /* Start CanTp */
    CanTp_Init(BASE_CANTP_CONFIG_PTR);
#endif

#if (BLPDUR_USE_CANSM == STD_ON)
    /* Start CanSM */
    CanSM_Init(BASE_CANSM_CONFIG_PTR);

    /* Request for FULL communication */
    (void)CanSM_RequestComMode(0U, COMM_FULL_COMMUNICATION);
#endif
}

/** \brief Deactivate the Communication
 **
 **/
void BlPduR_Custom_Com_Deactivate(void)
{
#if (BLPDUR_USE_CANSM == STD_ON)
    /* Request for NO communication */
    (void)CanSM_RequestComMode(0U, COMM_NO_COMMUNICATION);
#endif

#if (BLPDUR_USE_CAN == STD_ON)
    /* Stop Can Controller */
    Can_17_McmCan_DeInit();
#endif
}
