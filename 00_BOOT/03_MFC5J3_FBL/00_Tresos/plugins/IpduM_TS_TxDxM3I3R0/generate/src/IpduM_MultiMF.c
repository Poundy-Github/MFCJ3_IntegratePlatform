/**
 * \file
 *
 * \brief AUTOSAR IpduM
 *
 * This file contains the implementation of the AUTOSAR
 * module IpduM.
 *
 * \author Elektrobit Automotive GmbH, 91058 Erlangen, Germany
 *
 * Copyright 2005 - 2019 Elektrobit Automotive GmbH
 * All rights exclusively reserved for Elektrobit Automotive GmbH,
 * unless expressly agreed to otherwise.
 */

/** \addtogroup IpduM
 ** @{ */

[!INCLUDE "../include/IpduM_Macros.m"!]
[!AUTOSPACING!]
/*==================[inclusions]============================================*/
#include <IpduM_MultiMF.h>
/*==================[macros]================================================*/

/*==================[type definitions]======================================*/

/*==================[external function declarations]========================*/


/*==================[internal function declarations]========================*/

/*==================[internal constants]====================================*/

/*==================[internal data]=========================================*/

/*==================[external constants]====================================*/

/*==================[external data]=========================================*/

/*==================[external function definitions]=========================*/

/*==================[internal function definitions]=========================*/

[!IF "$IpduMMultiMF = 'true'"!]
[!CALL "createRXMFAlloc"!]
[!LOOP "text:split($mfRXalloc,';')"!]
[!VAR "shName" = "text:split(.,'#')[2]"!]
[!VAR "qName" = "text:split(.,'#')[3]"!]
[!CALL "createSegmentStr","shortName"="$shName"!]
#define [!"$secSTART"!]
#include <IpduM_MemMap.h>
/** \brief IpduM RX main function
 **
 ** Processes DEFERRED ContainerRxPdus
 **
 ** This function has to be called periodically by a task controlled by the
 ** BSW scheduler.
 **
 ** \ServiceID{0x11}
 ** \Reentrancy{Non-Reentrant}
 ** \Synchronicity{Synchronous}
 */
FUNC(void, [!"$segCODE"!]) [!"$qName"!](void)
{
  IpduM_MainFunctionRx_Generic([!"num:i(text:split(.,'#')[1])"!]U);
}
#define [!"$secSTOP"!]
#include <IpduM_MemMap.h>

[!ENDLOOP!][!//RX

[!CALL "createTXMFAlloc"!]
[!VAR "allocIdx" = "num:i(0)"!]
[!LOOP "text:split($mfTXalloc,';')"!]
[!VAR "shName" = "text:split(.,'#')[2]"!]
[!VAR "qName" = "text:split(.,'#')[3]"!]
[!VAR "numRef" = "num:i(count(text:split(text:split(.,'#')[4],'|')))"!]
[!CALL "createSegmentStr","shortName"="$shName"!]
#define [!"$secSTART"!]
#include <IpduM_MemMap.h>
/** \brief IpduM TX main function
 **
 ** Performs the processes of the activities that are not directly initiated by
 ** the calls from PDU-R. This includes at least the TxConfirmation time observation.
 **
 ** This function has to be called periodically by a task controlled by the
 ** BSW scheduler.
 **
 ** \ServiceID{0x12}
 ** \Reentrancy{Non-Reentrant}
 ** \Synchronicity{Synchronous}
 */
FUNC(void, [!"$segCODE"!]) [!"$qName"!](void)
{
  IpduM_MainFunctionTx_Generic([!"$allocIdx"!]U);
}
#define [!"$secSTOP"!]
#include <IpduM_MemMap.h>
[!VAR "allocIdx" = "num:i($allocIdx + $numRef + 1)"!][!//
[!ENDLOOP!][!//TX
[!ENDIF!][!//IpduMMultiMF
/*==================[end of file]===========================================*/
