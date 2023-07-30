/*********************************************************************************/
/*                                                                               */
/*                                BOOT Layers                                    */
/*                                                                               */
/* ------------------------------------------------------------------------------*/
/*                                                                               */
/*                                 BM configuration                              */
/*                                                                               */
/*********************************************************************************/
/*%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%                                        */
/*%%   _____________________________   %%  \file BM_Cfg.c                        */
/*%%  |                             |  %%  \brief BM layer source plugin file    */
/*%%  |   &&&&&   &&&&&             |  %%  Module version: 1.3.0 BL-3.X              */
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
[!AUTOSPACING!]
[!NOCODE!]
[!/* Activate generation of BM_Cfg.c file */!]
[!IF "(as:modconf('BM')/Security/SecureBoot/SECURE_AUTHENTICATED_BOOT='Authenticated') or
    (as:modconf('BM')/Security/SecureBoot/SECURE_AUTHENTICATED_BOOT='Secure')"!]
[!ELSE!]
    [!SKIPFILE!]
[!ENDIF!]
[!ENDNOCODE!]

#include "EB_Prj.h"

[!IF "node:exists(as:modconf('Csm'))"!]
#include "Csm.h"
[!ENDIF!]


[!IF "((as:modconf('BM')/Security/SecureBoot/SECURE_AUTHENTICATED_BOOT='Authenticated') or
    (as:modconf('BM')/Security/SecureBoot/SECURE_AUTHENTICATED_BOOT='Secure')) and (not(node:exists(as:modconf('ProgVCC'))))"!]

[!VAR "BLOCK_MAX"="num:dectoint(count(as:modconf('Prog')/Blocks/*))"!]

/* Table of information for each Block needed for Authenticated/Secure Boot */
const tProg_BlockSecureBootInfo stCfgBMBlockSecureBootInfo[PROG_BLOCK_NB] =
{
    [!FOR "BLOCK_IDX" = "1" TO "$BLOCK_MAX"!]
        [!VAR "START_ADDRESS"="num:inttohex(as:modconf('Prog')/Blocks/*[number($BLOCK_IDX)]/SecureBoot/Start_Address_Secure_Boot_Verification)"!]
        [!VAR "LENGTH"="num:inttohex(as:modconf('Prog')/Blocks/*[number($BLOCK_IDX)]/SecureBoot/Length_Secure_Boot_Verification)"!]
        [!VAR "BLOCK_IDENT"="num:inttohex(as:modconf('Prog')/Blocks/*[number($BLOCK_IDX)]/Block_Identifier)"!]
    {
        [!WS "8"!][!"$START_ADDRESS"!]U,[!WS "17"!]/* Start Address for the Secure Boot Verification */
        [!WS "8"!][!"$LENGTH"!]U,[!WS "17"!]/* Length of the block for the Secure Boot Verification */
        [!"$BLOCK_IDENT"!]U,[!WS "21"!]/* Block Identifier */
        [!WS "8"!][!IF "as:modconf('Prog')/Blocks/*[number($BLOCK_IDX)]/SecureBoot/Verified_For_Secure_Boot='Block will be verified'"!]BM_TRUE,[!WS "18"!][!ELSE!]BM_FALSE,[!WS "17"!][!ENDIF!]/* Block will be verified by the Secure Boot */
        [!WS "8"!][!IF "as:modconf('Prog')/Blocks/*[number($BLOCK_IDX)]/SecureBoot/Blocker_for_Software_execution='Will block software execution'"!]BM_TRUE,[!WS "18"!][!ELSE!]BM_FALSE,[!WS "17"!][!ENDIF!]/* Block will prevent the execution of software if Secure Boot verification is failed */
    },
    [!ENDFOR!]
};
[!ENDIF!]
