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
/*%%   _____________________________   %%  \file BM_Cbk.h                        */
/*%%  |                             |  %%  \brief BM layer include plugin file   */
/*%%  |   &&&&&   &&&&&             |  %%  Module version: 1.3.0 BL-3.X                */
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



#ifndef BM_CBK_H
#define BM_CBK_H
/*============================= PUBLIC DEFINITIONS ==============================*/
/*                                                                               */
/* - Public Callback Prototypes                                                  */

/** \brief Callback that shall disable ECC if needed
 ** Callback is called: When Bootloader perform read access on Flash that can be
 **                     unprogrammed and can cause ECC error
 **
 ** Callback shall implement: If needed, disabling of ECC check
 **                           Hardware specific)
 **/
extern void BM_DisableECCCheck(void);

/** \brief Callback that shall enable ECC if needed
 ** Callback is called: After Bootloader has performed a read access on Flash
 **                    that can be unprogrammed and can cause ECC error
 **
 ** Callback shall implement: If needed, enabling of ECC check
 **                          (Hardware specific)
 **/
extern void BM_EnableECCCheck(void);

/** \brief Software RAM initialization
 **
 ** This function is called at the very beginning of the Boot manager.
 ** It allows the application to do the minimum software initialization
 ** before the Boot manager start to check the application validity.
 **
 **/
extern void BM_SoftwareInit(void);

/** \brief Hardware initialization
 **
 ** This function is called at the very beginning of the Boot manager.
 ** It allows the application to do the minimum hardware initialization
 ** before the Boot manager start to check the application validity.
 **
 **/
extern void BM_HardwareInit (void);

/** \brief Get the diagnostic tester source address
 **
 ** This function is called when programming is requested by
 ** application (eBootFromAppli = BM_TRUE) and BM_SOURCE_ADDRESS_CHECK is set.
 ** This is a callback that get the tester address
 **
 ** \param[in,out] ubTesterAddress pointer on tester address
 **
 **/
#if (BM_SOURCE_ADDRESS_CHECK == STD_ON)
extern void BM_GetTesterAddress (u8 *ubTesterAddress);
#endif

[!IF "(as:modconf('BM')/Security/SecureBoot/SECURE_AUTHENTICATED_BOOT = 'Authenticated')"!]
/** \brief Get the last computed application checksum
 **
 ** This function is called at Bootloader startup to
 ** verify the application checksum before allowing
 ** the start of application. This checksum shall have been
 ** computed by application on configured application data range.
 **
 ** \param[out] pubChecksum address where the computed checksum shall be copied
 ** \param[in] uwBlockIdentifier Block Identifier
 **
 **/
extern void BM_CustomGetComputedApplicationChecksum (u8 *pubChecksum, u16 uwBlockIdentifier);
[!ENDIF!]

[!IF "((as:modconf('BM')/Security/SecureBoot/SECURE_AUTHENTICATED_BOOT = 'Authenticated') or
    (as:modconf('BM')/Security/SecureBoot/SECURE_AUTHENTICATED_BOOT = 'Secure'))"!]
/** \brief Get the expected application checksum
 **
 ** This function is called at Bootloader startup to
 ** verify the application checksum before allowing
 ** the start of application. It gets from non-volatile
 ** memory the checksum that had been computed during
 ** the last application download.
 **
 ** \param[out] pubChecksum address where the checksum shall be copied
 ** \param[in] uwBlockIdentifier Block Identifier
 **
 **/
extern void BM_CustomGetExpectedApplicationChecksum (u8 *pubChecksum, u16 uwBlockIdentifier);

/** \brief Notification that Application is invalid
 **
 ** This function is called when Application checksum
 ** verification failed and that Application cannot be started.
 ** This information shall be store in non-volatile memory.
 **
 ** \param[in] uwBlockIdentifier Identifier of invalid Block
 **
 **/
extern void BM_CustomSetInvalidAppli (u16 uwBlockIdentifier);

/** \brief Allow customer operation during long operation
 **
 ** This function is called during long operation (e.g. cryptography)
 ** allowing customer performing actions that cannot be stopped during
 ** a long time (e.g watchdog triggering).
 **
 **/
extern void BM_CustomBckOperation (void);
[!ENDIF!]

[!IF "((as:modconf('BM')/Security/SecureBoot/SECURE_AUTHENTICATED_BOOT = 'Authenticated') or (as:modconf('BM')/Security/SecureBoot/SECURE_AUTHENTICATED_BOOT = 'Secure'))
and (as:modconf('BM')/Security/SecureBoot/BOOT_VERIFICATION = 'ON')"!]
/** \brief Notification that Bootloader is invalid
 **
 ** This function is called when Bootloader checksum
 ** verification failed and that Bootloader cannot be started.
 ** By this callback application shall be informed that Bootloader
 ** cannot be executed anymore.
 **
 **/
extern void BM_CustomSetInvalidBoot (void);
[!ENDIF!]

[!IF "as:modconf('Prog')/General/Dual_Memory_Bank_Used = 'true'"!]
/** \brief Initialize the Dual Memory Bank
 **
 ** This function is called when Bootloader starts
 ** to prepare the usage of the dual memory banks.
 **
 **/
extern void BM_CustomDualBankInit(void);
[!ENDIF!]

#if (BM_CSM_MAC_USED == STD_ON)
/** \brief Get the mac key used in Mac verification (should be the same key used in the generation)
 **
 ** This function is called at the beginning of the Mac verification to get the key yo be used in the process
 **
 **/
extern void BM_CustomGetMacKey(const u8** paubKeyData, u32* pulKeyLength);
#endif
/*                                                                               */
/*===============================================================================*/


[!IF "General/BM_TIMEOUT_CHECK = 'true'"!]
/** \brief Request if ECU has started normally or not
 **
 ** This function is called at startup to know if normal or abnormal startup has been done.
 ** In case of abnormal startup ECU stay in Bootloader mode during a configured time
 ** before jumping to application (if valid).
 ** This time window allow the tester to send a programming session request to force the Boot mode
 **
 **/
tBMBoolean BM_CustomIsNormalStartup (void);
[!ENDIF!]

#endif      /* BM_CBK_H */
