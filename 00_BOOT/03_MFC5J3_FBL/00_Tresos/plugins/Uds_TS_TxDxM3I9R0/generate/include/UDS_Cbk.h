/*********************************************************************************/
/*                                                                               */
/*                                  CAN Stack                                    */
/*                                                                               */
/* ------------------------------------------------------------------------------*/
/*                                                                               */
/*                                 UDS configuration                             */
/*                                                                               */
/*********************************************************************************/
/*%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%                                        */
/*%%   _____________________________   %%  \file UDS_Cbk.h                       */
/*%%  |                             |  %%                                        */
/*%%  |   &&&&&   &&&&&             |  %%  Module version: 3.9.2 BL-3.X                 */
/*%%  |   &       &    &            |  %%  Module variant: ISO           */
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

#ifndef UDS_CBK_H
#define UDS_CBK_H

/** \brief Notification for diagnostic session transition
 **
 ** It provides old and new sessions, with the reason for the transition.
 ** 
 ** \param[in] eUdsNewSessType new session
 ** \param[in] eUdsOldSessType old session
 ** \param[in] eUdsChangingCause explicit request (UDS_SESSION_CHANGE_REQUESTED) or session timeout (UDS_SESSION_TIMEOUT)
 ** 
 **/
extern void UDS_SessionStatusInd (tUdsSessionType eUdsNewSessType,tUdsSessionType eUdsOldSessType,tUdsChangeReason eUdsChangingCause);

[!IF "not(node:exists(as:modconf('BlPduR')))"!]
/** \brief Response pending management: request for intermediate NRC_78 or final response transmission.
 **
 ** Response pending is in progress.
 ** The UDS layer ensure cyclic NRC_78 transmissions and final response transmission.
 ** This callback is used to request transmission.
 ** 
 ** \param[in] uwLen final length for response
 ** \param[in,out] aubUdsData pointer on data
 ** 
 ** \return Diagnostic response status
 ** \retval UDS_ACK     Positive response: the transmission is pending
 ** \retval UDS_NRC_xxx Negative response code (just need to be different from UDS_ACK) : the transmission request is rejected for undetailed reason.
 **
 **/
extern tUdsStatus UDS_LongRequestResponseInd (u16 uwLen, u8 *aubUdsData);
[!ENDIF!]

/** \brief Notification just before the P2/P2_STAR timeout.
 **
 ** Notification in order to give possibility to the application
 ** to execute an action before P2/P2_STAR timeout.
 ** 
 **/
extern void UDS_P2AboutToExpireInd(void);

/** \brief Notification of positive answer.
 **
 ** Notification in order to give possibility to the user to
 ** execute an action before the positive answer transmission.
 ** 
 ** \param[in] puwLen received data length
 ** \param[in] aubUdsData received data pointer
 **
 **/
extern void UDS_CustomPositiveAnswerInd(const u16 *puwLen, const u8 *aubUdsData);



/* skip this code from DoxyGen */
#ifndef DOXYGEN_SHOULD_SKIP_THIS

/* Callback function prototype : Service */
[!VAR "TMP_CNT1" = "0"!][!AUTOSPACING!]
[!LOOP "Service/*"!][!AUTOSPACING!]
[!VAR "TMP_CNT1" = "$TMP_CNT1 + 1"!][!AUTOSPACING!]
[!IF "Callback != ''"!][!AUTOSPACING!]
[!VAR "TMP_CBK" = "Callback"!][!AUTOSPACING!]
[!VAR "TMP_CNT2" = "0"!][!AUTOSPACING!]
[!VAR "TMP_CNT" = "0"!][!AUTOSPACING!]
[!LOOP "../../Service/*"!][!AUTOSPACING!]
[!VAR "TMP_CNT2" = "$TMP_CNT2 + 1"!][!AUTOSPACING!]
[!IF "$TMP_CNT1 >= $TMP_CNT2"!][!AUTOSPACING!]
[!IF "Callback = $TMP_CBK"!][!AUTOSPACING!]
[!VAR "TMP_CNT" = "$TMP_CNT + 1"!][!AUTOSPACING!]
[!ENDIF!][!AUTOSPACING!]
[!ENDIF!][!AUTOSPACING!]
[!ENDLOOP!]
[!IF "$TMP_CNT > '1'"!][!AUTOSPACING!]
[!ELSE!]
/** \brief Callback for the diagnostic request (configuration) 
 **
 ** The diagnostic request is valid (filtering completed).
 ** The callback configured for this service is used.
 ** 
 ** \param[in,out] puwLen pointer on data length
 ** \param[in,out] aubUdsData pointer on data
 ** 
 ** \return Diagnostic response status
 ** \retval UDS_ACK     Positive response
 ** \retval UDS_NRC_xxx Negative response code.
 **
 **/
extern tUdsStatus [!"Callback"!](u16 *puwLen, u8 *aubUdsData);
[!ENDIF!][!AUTOSPACING!]
[!ENDIF!][!AUTOSPACING!]
[!ENDLOOP!][!AUTOSPACING!]

/* Callback function prototype : Service_DID */
[!VAR "TMP_CNT1" = "0"!][!AUTOSPACING!]
[!LOOP "Service_DID/*"!][!AUTOSPACING!]
[!VAR "TMP_CNT1" = "$TMP_CNT1 + 1"!][!AUTOSPACING!]
[!IF "Callback != ''"!][!AUTOSPACING!]
[!VAR "TMP_CBK" = "Callback"!][!AUTOSPACING!]
[!VAR "TMP_CNT2" = "0"!][!AUTOSPACING!]
[!VAR "TMP_CNT" = "0"!][!AUTOSPACING!]
[!LOOP "../../Service_DID/*"!][!AUTOSPACING!]
[!VAR "TMP_CNT2" = "$TMP_CNT2 + 1"!][!AUTOSPACING!]
[!IF "$TMP_CNT1 >= $TMP_CNT2"!][!AUTOSPACING!]
[!IF "Callback = $TMP_CBK"!][!AUTOSPACING!]
[!VAR "TMP_CNT" = "$TMP_CNT + 1"!][!AUTOSPACING!]
[!ENDIF!][!AUTOSPACING!]
[!ENDIF!][!AUTOSPACING!]
[!ENDLOOP!]
[!IF "$TMP_CNT > '1'"!][!AUTOSPACING!]
[!ELSE!]
/** \brief Callback for the diagnostic request (configuration) 
 **
 ** The diagnostic request is valid (filtering completed).
 ** The callback configured for this service is used.
 ** 
 ** \param[in,out] puwLen pointer on data length
 ** \param[in,out] aubUdsData pointer on data
 ** 
 ** \return Diagnostic response status
 ** \retval UDS_ACK     Positive response
 ** \retval UDS_NRC_xxx Negative response code.
 **
 **/
extern tUdsStatus [!"Callback"!](u16 *puwLen, u8 *aubUdsData);
[!ENDIF!][!AUTOSPACING!]
[!ENDIF!][!AUTOSPACING!]
[!ENDLOOP!][!AUTOSPACING!]

/* Callback function prototype : Routine_Control */
[!VAR "TMP_CNT1" = "0"!][!AUTOSPACING!]
[!LOOP "Routine_Control/*"!][!AUTOSPACING!]
[!VAR "TMP_CNT1" = "$TMP_CNT1 + 1"!][!AUTOSPACING!]
[!IF "Callback != ''"!][!AUTOSPACING!]
[!VAR "TMP_CBK" = "Callback"!][!AUTOSPACING!]
[!VAR "TMP_CNT2" = "0"!][!AUTOSPACING!]
[!VAR "TMP_CNT" = "0"!][!AUTOSPACING!]
[!LOOP "../../Routine_Control/*"!][!AUTOSPACING!]
[!VAR "TMP_CNT2" = "$TMP_CNT2 + 1"!][!AUTOSPACING!]
[!IF "$TMP_CNT1 >= $TMP_CNT2"!][!AUTOSPACING!]
[!IF "Callback = $TMP_CBK"!][!AUTOSPACING!]
[!VAR "TMP_CNT" = "$TMP_CNT + 1"!][!AUTOSPACING!]
[!ENDIF!][!AUTOSPACING!]
[!ENDIF!][!AUTOSPACING!]
[!ENDLOOP!]
[!IF "$TMP_CNT > '1'"!][!AUTOSPACING!]
[!ELSE!]
/** \brief Callback for the diagnostic request (configuration) 
 **
 ** The diagnostic request is valid (filtering completed).
 ** The callback configured for this service is used.
 ** 
 ** \param[in,out] puwLen pointer on data length
 ** \param[in,out] aubUdsData pointer on data
 ** 
 ** \return Diagnostic response status
 ** \retval UDS_ACK     Positive response
 ** \retval UDS_NRC_xxx Negative response code.
 **
 **/
extern tUdsStatus [!"Callback"!](u16 *puwLen, u8 *aubUdsData);
[!ENDIF!][!AUTOSPACING!]
[!ENDIF!][!AUTOSPACING!]
[!ENDLOOP!][!AUTOSPACING!]

/* Callback function prototype : OBD */
[!VAR "TMP_CNT1" = "0"!][!AUTOSPACING!]
[!LOOP "Service_OBD/*"!][!AUTOSPACING!]
[!VAR "TMP_CNT1" = "$TMP_CNT1 + 1"!][!AUTOSPACING!]
[!IF "Callback != ''"!][!AUTOSPACING!]
[!VAR "TMP_CBK" = "Callback"!][!AUTOSPACING!]
[!VAR "TMP_CNT2" = "0"!][!AUTOSPACING!]
[!VAR "TMP_CNT" = "0"!][!AUTOSPACING!]
[!LOOP "../../Service_OBD/*"!][!AUTOSPACING!]
[!VAR "TMP_CNT2" = "$TMP_CNT2 + 1"!][!AUTOSPACING!]
[!IF "$TMP_CNT1 >= $TMP_CNT2"!][!AUTOSPACING!]
[!IF "Callback = $TMP_CBK"!][!AUTOSPACING!]
[!VAR "TMP_CNT" = "$TMP_CNT + 1"!][!AUTOSPACING!]
[!ENDIF!][!AUTOSPACING!]
[!ENDIF!][!AUTOSPACING!]
[!ENDLOOP!]
[!IF "$TMP_CNT > '1'"!][!AUTOSPACING!]
[!ELSE!]
/** \brief Callback for the diagnostic request (configuration) 
 **
 ** The diagnostic request is valid (filtering completed).
 ** The callback configured for this service is used.
 ** 
 ** \param[in,out] puwLen pointer on data length
 ** \param[in,out] aubUdsData pointer on data
 ** 
 ** \return Diagnostic response status
 ** \retval UDS_ACK     Positive response
 ** \retval UDS_NRC_xxx Negative response code.
 **
 **/
extern tUdsStatus [!"Callback"!](u16 *puwLen, u8 *aubUdsData);
[!ENDIF!][!AUTOSPACING!]
[!ENDIF!][!AUTOSPACING!]
[!ENDLOOP!][!AUTOSPACING!]

[!IF "General/SecurityCheck = 'true'"!]
extern u8 [!"General/SecurityFunction"!](void);
[!ENDIF!]

#endif /* DOXYGEN_SHOULD_SKIP_THIS */

[!IF "Supplier_Services/BA = 'true'"!]
/** \brief API that check if a supplier request has been received
 **
 ** Callback is called: receiving a BA supplier request.
 **
 ** Callback shall implement: BA supplier service
 **
 ** \param[in,out] puwLen received data length, response length (no response if 0)
 ** \param[in,out] aubUdsData received data pointer, data to transmit
 ** \param[in] eUdsAddrMode Addressing mode information (PHYSICAL 0x01U , FUNCTIONAL 0x02U , PHYSICAL_FUNCTIONAL 0x03U)
 ** \param[in] eUdsAddrType Addressing type information (DIAG 0x00U , OBD 0x01U , DIAG_OBD 0x02U)
 **
 ** \return Result of check
 ** \retval UDS_ACK BA supplier request has been received successfully
 ** \retval UDS_NRC_xxx Negative response code.
 ** \retval UDS_ERR_COHE SDF error detected (no response)
 **/
extern tUdsStatus UDS_CustomSupplier_BA (u16 *puwLen, u8 *aubUdsData, tUdsAddrMode eUdsAddrMode, tUdsAddrType eUdsAddrType);
[!ENDIF!]

[!IF "Supplier_Services/BB = 'true'"!]
/** \brief API that check if a supplier request has been received
 **
 ** Callback is called: receiving a BB supplier request.
 **
 ** Callback shall implement: BB supplier service
 **
 ** \param[in,out] puwLen received data length, response length (no response if 0)
 ** \param[in,out] aubUdsData received data pointer, data to transmit
 ** \param[in] eUdsAddrMode Addressing mode information (PHYSICAL 0x01U / FUNCTIONAL 0x02U / PHYSICAL_FUNCTIONAL 0x03U)
 ** \param[in] eUdsAddrType Addressing type information (DIAG 0x00U / OBD 0x01U / DIAG_OBD 0x02U)
 **
 ** \return Result of check
 ** \retval UDS_ACK BB supplier request has been received successfully
 ** \retval UDS_NRC_xxx Negative response code.
 ** \retval UDS_ERR_COHE SDF error detected (no response)
 **/
extern tUdsStatus UDS_CustomSupplier_BB (u16 *puwLen, u8 *aubUdsData, tUdsAddrMode eUdsAddrMode, tUdsAddrType eUdsAddrType);
[!ENDIF!]

[!IF "Supplier_Services/BC = 'true'"!]
/** \brief API that check if a supplier request has been received
 **
 ** Callback is called: receiving a BC supplier request.
 **
 ** Callback shall implement: BC supplier service
 **
 ** \param[in,out] puwLen received data length, response length (no response if 0)
 ** \param[in,out] aubUdsData received data pointer, data to transmit
 ** \param[in] eUdsAddrMode Addressing mode information (PHYSICAL 0x01U / FUNCTIONAL 0x02U / PHYSICAL_FUNCTIONAL 0x03U)
 ** \param[in] eUdsAddrType Addressing type information (DIAG 0x00U / OBD 0x01U / DIAG_OBD 0x02U)
 **
 ** \return Result of check
 ** \retval UDS_ACK BC supplier request has been received successfully
 ** \retval UDS_NRC_xxx Negative response code.
 ** \retval UDS_ERR_COHE SDF error detected (no response)
 **/
extern tUdsStatus UDS_CustomSupplier_BC (u16 *puwLen, u8 *aubUdsData, tUdsAddrMode eUdsAddrMode, tUdsAddrType eUdsAddrType);
[!ENDIF!]

[!IF "Supplier_Services/BD = 'true'"!]
/** \brief API that check if a supplier request has been received
 **
 ** Callback is called: receiving a BD supplier request.
 **
 ** Callback shall implement: BD supplier service
 **
 ** \param[in,out] puwLen received data length, response length (no response if 0)
 ** \param[in,out] aubUdsData received data pointer, data to transmit
 ** \param[in] eUdsAddrMode Addressing mode information (PHYSICAL 0x01U / FUNCTIONAL 0x02U / PHYSICAL_FUNCTIONAL 0x03U)
 ** \param[in] eUdsAddrType Addressing type information (DIAG 0x00U / OBD 0x01U / DIAG_OBD 0x02U)
 **
 ** \return Result of check
 ** \retval UDS_ACK BD supplier request has been received successfully
 ** \retval UDS_NRC_xxx Negative response code.
 ** \retval UDS_ERR_COHE SDF error detected (no response)
 **/
extern tUdsStatus UDS_CustomSupplier_BD (u16 *puwLen, u8 *aubUdsData, tUdsAddrMode eUdsAddrMode, tUdsAddrType eUdsAddrType);
[!ENDIF!]

[!IF "Supplier_Services/BE = 'true'"!]
/** \brief API that check if a supplier request has been received
 **
 ** Callback is called: receiving a BE supplier request.
 **
 ** Callback shall implement: BE supplier service
 **
 ** \param[in,out] puwLen received data length, response length (no response if 0)
 ** \param[in,out] aubUdsData received data pointer, data to transmit
 ** \param[in] eUdsAddrMode Addressing mode information (PHYSICAL 0x01U / FUNCTIONAL 0x02U / PHYSICAL_FUNCTIONAL 0x03U)
 ** \param[in] eUdsAddrType Addressing type information (DIAG 0x00U / OBD 0x01U / DIAG_OBD 0x02U)
 **
 ** \return Result of check
 ** \retval UDS_ACK BE supplier request has been received successfully
 ** \retval UDS_NRC_xxx Negative response code.
 ** \retval UDS_ERR_COHE SDF error detected (no response)
 **/
extern tUdsStatus UDS_CustomSupplier_BE (u16 *puwLen, u8 *aubUdsData, tUdsAddrMode eUdsAddrMode, tUdsAddrType eUdsAddrType);
[!ENDIF!]

#endif      /* UDS_CBK_H */
