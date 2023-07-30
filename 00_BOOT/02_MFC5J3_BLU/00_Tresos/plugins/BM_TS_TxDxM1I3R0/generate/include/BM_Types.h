/*********************************************************************************/
/*                                                                               */
/*                               BOOT Layers                                     */
/*                                                                               */
/* ----------------------------------------------------------------------------- */
/*                                                                               */
/*                               BM layer                                        */
/*                                                                               */
/*********************************************************************************/
/*%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%                                        */
/*%%   _____________________________   %%  \file BM_Types.h                      */
/*%%  |                             |  %%  \brief BM layer include plugin file   */
/*%%  |   &&&&&   &&&&&             |  %%  Module version: 1.3.0 BL-3.X                */
/*%%  |   &       &    &            |  %%  Variant: OsekCore                  */
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




#ifndef BM_TYPES_H
#define BM_TYPES_H

[!IF "node:exists(as:modconf('BlPduR'))"!]
 	[!IF "as:modconf('BlPduR')/General/FlexRay_Protocol_Supported = 'true'"!]
typedef u16 tBMNetworkStatus;
#define BM_FR_NS_INIT               0x0000U
#define BM_FR_NS_NORMAL             0x0001U
#define BM_FR_NS_BOOT               0x1000U
#define BM_FR_NS_UNDEFINED          0x2000U

typedef u8 tBMFRStatus;
#define BM_FR_NOTHING_REQUESTED     0U
#define BM_FR_BOOT_REQUESTED        1U
#define BM_FR_APPLI_REQUESTED       2U

typedef u8 tBMCycleCount;
	[!ENDIF!]
[!ELSE!]
   [!IF "node:exists(as:modconf('EB'))"!]
 	 [!IF "(as:modconf('EB')/General/Protocol_Type = 'FLEXRAY')"!]
 typedef u16 tBMNetworkStatus;
 #define BM_FR_NS_INIT               0x0000U
 #define BM_FR_NS_NORMAL             0x0001U
 #define BM_FR_NS_BOOT               0x1000U
 #define BM_FR_NS_UNDEFINED          0x2000U

 typedef u8 tBMFRStatus;
 #define BM_FR_NOTHING_REQUESTED     0U
 #define BM_FR_BOOT_REQUESTED        1U
 #define BM_FR_APPLI_REQUESTED       2U

 typedef u8 tBMCycleCount;
 	 [!ENDIF!]
  [!ENDIF!]
[!ENDIF!]
typedef u8 tBMTimeout;

typedef u8 tBMBoolean;
#define BM_FALSE                    0U
#define BM_TRUE                     1U

#endif      /* BM_TYPES_H */

