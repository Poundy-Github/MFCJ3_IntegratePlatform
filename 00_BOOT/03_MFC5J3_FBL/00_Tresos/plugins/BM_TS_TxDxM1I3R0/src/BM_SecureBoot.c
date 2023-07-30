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
/*%%   _____________________________   %%  \file BM_Prg.c                        */
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
/*
 * MISRA-C:2012 Deviation List
 *
 * MISRAC2012-1) Deviated Rule: 11.4 (advisory)
 * A cast shall not be performed between a pointer to object type and a pointer to a different
 * object type.
 *
 *   Reason:
 * The memory routines are optimized for dealing with aligned memory
 * and the correct alignment has been checked before converting
 * to different object types
 *
 * MISRAC2012-2) Deviated Rule: 8.4 (required)
 * A compatible declaration shall be visible when an object or function with external
 * linkage is defined
 *
 *   Reason:
 * This variable need to be used in test environment
 */
/* NOCOV List
 *
 * NOCOV-NOCOV-BMTIMEOUTCHECKONNOTSUPPORTED:
 *
 * Reason:
 * BM_TIMEOUT_CHECK_ON not yet supported
 */


/*=============================== FILE INCLUSION ================================*/
/*                                                                               */
/*-------------------------------------------------------------------------------*/
/* - Header Files: Variable Types                                                */


/*-------------------------------------------------------------------------------*/
/* - Header Files: BM                                                            */


/*                                                                               */
/*===============================================================================*/
#include "EB_Prj.h"
#include "BM_Priv.h"
#include <BM_Trace.h>

#if ((BM_AUTHENTICATED_BOOT_ENABLE == STD_ON) || (BM_SECURE_BOOT_ENABLE == STD_ON))

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

NCS_PRI_VAR u8 m_aubExpectedApplicationChecksum[BM_CHECKSUM_SIZE_IN_BYTES];

/*-------------------------------------------------------------------------------*/
/* - Private Macros                                                              */
#if (PROG_IMPL_VARIANT == PROG_IMPL_10)
#define BM_ESS_INDEX     0
#endif

/*-------------------------------------------------------------------------------*/
/* - Private Function Prototypes                                                 */

NCS_PRI_VAR tBMBoolean BM_VerifyESSIntegrity(void);

/*                                                                               */
/*===============================================================================*/


/*=============================== IMPLEMENTATION ================================*/
/*                                                                               */

/*-------------------------------------------------------------------------------*/
/* - Private Functions                                                           */

#if (PROG_IMPL_VARIANT == PROG_IMPL_10)
NCS_PRI_VAR tBMBoolean BM_VerifyESSIntegrity(void)
{
  tBMBoolean ubCheckOk = BM_TRUE;
  u32 ulStartAddress;
  u32 ulLength;

  /* Block index 0 is reserved for ESS */
  BM_CustomGetExpectedApplicationChecksum(&m_aubExpectedApplicationChecksum[0U], BM_ESS_INDEX);

  Prog_GetEssStartAddr(&ulStartAddress);
  Prog_GetEssLength(&ulLength);

  /* Verification of the MAC for ESS*/
  ubCheckOk = BM_VerifyMac(
          &m_aubExpectedApplicationChecksum[0U],
          (u8 const *)ulStartAddress,
          ulLength);

  return ubCheckOk;
}
#endif

/*-------------------------------------------------------------------------------*/
/* - Public Functions                                                            */

tBMBoolean BM_VerifyApplicationIntegrity(void)
{
#if ((BM_AUTHENTICATED_BOOT_ENABLE == STD_ON) || (BM_CSM_HASH_USED == STD_ON))
    u16 uwLoopIndex;
    u8 aubComputedApplicationChecksum[BM_CHECKSUM_SIZE_IN_BYTES];
#endif
#if (PROG_IMPL_VARIANT == PROG_IMPL_10)
    u8 ubBlockIndex;
    u8 ubBlockCount;
    u32 ulStartAddress;
    u32 ulLength;
#else
    u16 uwBlockIndex;
    tBMBoolean ubCheckOk = BM_TRUE;
#endif
    tBMBoolean ubAppBootable = BM_TRUE;
#if (BM_SECURE_BOOT_ENABLE == STD_ON)
    tBMBoolean eOperationSuccess = BM_TRUE;
#endif

#if (PROG_IMPL_VARIANT == PROG_IMPL_10)


    /* Verify ESS first */
    ubAppBootable = BM_VerifyESSIntegrity();

    /* ESS is valid */
    if(BM_TRUE == ubAppBootable)
    {
      (void)Prog_GetEssLogicalBlockNbr(&ubBlockCount);

      /* Block index 0 is reserved for ESS */
      for (ubBlockIndex = 0U; ((ubBlockIndex < ubBlockCount) && (BM_TRUE == eOperationSuccess)); ubBlockIndex++)
      {

        (void)Prog_GetEssLogicalBlockStartAddr(ubBlockIndex, &ulStartAddress);
        (void)Prog_GetEssLogicalBlockLength(ubBlockIndex, &ulLength);

        /* Get Expected Application checksum of the corresponding Block identifier */
        /* add 1 because first index is reserved for the ESS */
        BM_CustomGetExpectedApplicationChecksum(&m_aubExpectedApplicationChecksum[0U], (u16)ubBlockIndex + 1);

          /* Computation of the MAC for the current block */
          /* Comparison to the MAC saved for the same block */
          eOperationSuccess = BM_VerifyMac(
                  &m_aubExpectedApplicationChecksum[0U],
                  (u8 const *)ulStartAddress,
                  ulLength);
      }


      if (BM_TRUE == eOperationSuccess)
      {
        ubAppBootable = BM_TRUE;
      }
      else
      {
        ubAppBootable = BM_FALSE;
        /* Block index 0 is reserved for ESS */
        BM_CustomSetInvalidAppli(ubBlockIndex);
      }
    }
    /* ESS integrity failed */
    else
    {
      /* Block index 0 is reserved for ESS */
      BM_CustomSetInvalidAppli(BM_ESS_INDEX);
    }
#else

    /* For each block to be verified for secure boot */
    for (uwBlockIndex = 0U; ((uwBlockIndex < PROG_BLOCK_NB) && (BM_TRUE == ubAppBootable)); uwBlockIndex++)
    {
        /* If the block shall be verified by Secure Boot */
        if (BM_TRUE == stCfgBMBlockSecureBootInfo[uwBlockIndex].ubBlockVerifiedInSecure)
        {
            /* Get Expected Application checksum of the corresponding Block identifier */
            BM_CustomGetExpectedApplicationChecksum(&m_aubExpectedApplicationChecksum[0U], uwBlockIndex);

#if (BM_AUTHENTICATED_BOOT_ENABLE == STD_ON)
            /* Verify application checksum before starting it */
            BM_CustomGetComputedApplicationChecksum(&aubComputedApplicationChecksum[0U], uwBlockIndex);
#elif (BM_SECURE_BOOT_ENABLE == STD_ON)
#if (BM_CSM_MAC_USED == STD_ON)
            /* Computation of the MAC for the current block */
            /* Comparison to the MAC saved for the same block */
            /* Deviation MISRAC2012-1 */
            eOperationSuccess = BM_VerifyMac(
                    &m_aubExpectedApplicationChecksum[0U],
                    (u8 const *)stCfgBMBlockSecureBootInfo[uwBlockIndex].ulStartAddressForSecureBoot,
                    stCfgBMBlockSecureBootInfo[uwBlockIndex].ulLengthForSecureBoot);
#endif

#if (BM_CSM_HASH_USED == STD_ON)
            /* Deviation MISRAC2012-1 */
            /* Computation of the Hash */
            eOperationSuccess = BM_ComputeHash((u8 const *)stCfgBMBlockSecureBootInfo[uwBlockIndex].ulStartAddressForSecureBoot,
                stCfgBMBlockSecureBootInfo[uwBlockIndex].ulLengthForSecureBoot,
                &aubComputedApplicationChecksum[0]);
#endif
            if (BM_TRUE == eOperationSuccess)
#endif

            {
                ubCheckOk = BM_TRUE;
#if ((BM_AUTHENTICATED_BOOT_ENABLE == STD_ON) || (BM_CSM_HASH_USED == STD_ON))

                for (uwLoopIndex = 0U; ((uwLoopIndex < BM_CHECKSUM_SIZE_IN_BYTES) && (BM_TRUE == ubCheckOk)); uwLoopIndex++)
                {
                    if (aubComputedApplicationChecksum[uwLoopIndex] != m_aubExpectedApplicationChecksum[uwLoopIndex])
                    {
                        ubCheckOk = BM_FALSE;
                    }
                }
#endif
            }
#if (BM_SECURE_BOOT_ENABLE == STD_ON)
            else
            {
                ubCheckOk = BM_FALSE;
            }
#endif

            if (BM_FALSE == ubCheckOk)
            {
                /* Notify that corresponding block identifier is not valid */
                BM_CustomSetInvalidAppli(uwBlockIndex);

                /* Test if the invalid Block shall block the execution of the software  */
                if (BM_TRUE == stCfgBMBlockSecureBootInfo[uwBlockIndex].ubBlockBlockerExecution)
                {
                    /* Set the flag to block the soft execution */
                  ubAppBootable = BM_FALSE;
                }
            }
        }
        else
        {
            /* Do nothing */
        }
    }
#endif

  return ubAppBootable;

}


#endif
