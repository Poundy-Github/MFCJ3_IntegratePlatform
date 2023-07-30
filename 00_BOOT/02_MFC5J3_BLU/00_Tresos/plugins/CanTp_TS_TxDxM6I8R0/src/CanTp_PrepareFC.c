/**
 * \file
 *
 * \brief AUTOSAR CanTp
 *
 * This file contains the implementation of the AUTOSAR
 * module CanTp.
 *
 * \author Elektrobit Automotive GmbH, 91058 Erlangen, Germany
 *
 * Copyright 2005 - 2019 Elektrobit Automotive GmbH
 * All rights exclusively reserved for Elektrobit Automotive GmbH,
 * unless expressly agreed to otherwise.
 */

/*==================[inclusions]============================================*/

#include <CanTp_Trace.h>
#include <TSAutosar.h>         /* EB specific standard types */
#include <ComStack_Types.h>    /* typedefs for AUTOSAR com stack */
#include <CanTp_InternalLib.h> /* internal macros and variables */
#include <CanTp_InternalCfg.h> /* CanTp internal configuration */
#include <CanTp_Internal.h>    /* internal macros and variables */

/*==================[macros]================================================*/

/*==================[type definitions]======================================*/

/*==================[external function declarations]========================*/

/*==================[internal function declarations]========================*/

/*==================[external constants]====================================*/

/*==================[internal constants]====================================*/

/*==================[external data]=========================================*/

/*==================[internal data]=========================================*/

/*==================[external function definitions]=========================*/

#if(TS_MERGED_COMPILE == STD_OFF)
#define CANTP_START_SEC_CODE
#include <CanTp_MemMap.h>
#endif /* TS_MERGED_COMPILE == STD_OFF */

#if(CANTP_JUMPTABLE_MODE != CANTP_JUMPTABLE_CLIENT)

FUNC(void, CANTP_CODE) CanTp_PrepareFC
(
  P2VAR(CanTp_ChannelType, AUTOMATIC, CANTP_VAR) ChannelPtr,
  uint8 FcNPCI_Header
)
{
  /* Affected N-Sdu */
  const PduIdType NSduId = ChannelPtr->NSduId;
  uint8 DataIndex; /* Index to help prepare data */

  /* set N_TA/N_AE value on extended/mixed addressing */
  if(CANTP_CFG_GET_RXNSDU_CONFIG(NSduId).AddressingFormat != CANTP_STANDARD)
  {
    ChannelPtr->CanIfData[0U] = CANTP_CFG_GET_RXNSDU_CONFIG(NSduId).N_TA_AE;
    DataIndex = 1U;
  }
  else
  {
    DataIndex = 0U;
  }

  /* set N_PCI */
  ChannelPtr->CanIfData[DataIndex] = FcNPCI_Header;
  DataIndex++;

  /* set BS */
  ChannelPtr->CanIfData[DataIndex] = ChannelPtr->BlockSize;
  DataIndex++;

  /* set StMin */
  ChannelPtr->CanIfData[DataIndex] = CANTP_GET_RX_PDU_ST_MIN(NSduId);
  DataIndex++;
  ChannelPtr->CanIfDLC = DataIndex;

  /* Check and fill frame with padding bytes if required. */
#if(CANTP_CANFD_ENABLED == STD_ON)
  CanTp_PreparePadding(ChannelPtr, CANTP_CFG_GET_RXNSDU_CONFIG(NSduId).PaddingActivation, CANTP_CFG_GET_RXNSDU_CONFIG(NSduId).FcCanIdType);
#else
  CanTp_PreparePadding(ChannelPtr, CANTP_CFG_GET_RXNSDU_CONFIG(NSduId).PaddingActivation, CANTP_TX_INVALID_CANID);
#endif /* CANTP_CANFD_ENABLED == STD_ON */

  /* transmit frame */
  ChannelPtr->Ticks = CANTP_CFG_GET_RXNSDU_CONFIG(NSduId).N_Ar;

#if(CANTP_N_BR_WAIT_SUPPORT == STD_ON)
  if((CANTP_N_PCI_FC_WT == FcNPCI_Header) &&
     ((boolean)TRUE == CANTP_CFG_GET_RXNSDU_CONFIG(NSduId).NBrWTUsed))
  {
    /* set flag for WT status after first FC WT transmission */
    ChannelPtr->FcWaitRepeatedFlag = TRUE;
  }
  else
  {
    /* clear flag for WT status after CTS transmission */
    ChannelPtr->FcWaitRepeatedFlag = FALSE;
  }
#endif

  CanTp_TransmitFrame(ChannelPtr);
}


FUNC(Std_ReturnType, CANTP_CODE) CanTp_CalculateBlockSize
(
  P2VAR(CanTp_ChannelType, AUTOMATIC, CANTP_VAR) ChannelPtr,
  P2VAR(uint8, AUTOMATIC, CANTP_VAR) BlockSizePtr
)
{
  const PduIdType NSduId = ChannelPtr->NSduId; /* affected N-Sdu */
  const PduLengthType RemainingBytes = ChannelPtr->TotalLength - ChannelPtr->ProcessedLength;
  PduLengthType BlockSizeTmp; /* Temporary block size value for calculation */
  Std_ReturnType Ret_BSCalc; /* Indication of the actual BS calculation */

  /* Pointer  to N-Sdu config */
  CONSTP2CONST(CanTp_RxNSduConfigType, AUTOMATIC, CANTP_APPL_CONST) RxNSduCfgPtr =
      &CANTP_CFG_GET_RXNSDU_CONFIG(ChannelPtr->NSduId);

  /* Data frame length for calculating block (depending on addressing format) */
  const uint8 NSduMaxSize = CANTP_CFG_GET_RXNSDU_CONFIG(NSduId).NPduMaxLength
                            - CANTP_GET_FIRST_N_PCI_BYTE(RxNSduCfgPtr)
                            - CANTP_CF_NPCI_SIZE;

  if(ChannelPtr->ActualBufferSize >= RemainingBytes)
  {
    /* Use configured value if whole frame fits in buffer. */
    BlockSizeTmp = CANTP_GET_RX_PDU_BLOCK_SIZE(NSduId);
    Ret_BSCalc = E_OK;
  }
  else
  {
    /* ------------- calculate BlockSize -------------- */
    /* BS = Number of frames that fit into UL buffer */
    BlockSizeTmp = (PduLengthType) (ChannelPtr->ActualBufferSize / NSduMaxSize);

    if(BlockSizeTmp > 0U)
    {
      /* Calculation returns valid result. There is enough UL buffer available */
      Ret_BSCalc = E_OK;

      /* if calculated BS is larger than configured BS */
      if(
          (BlockSizeTmp > CANTP_GET_RX_PDU_BLOCK_SIZE(NSduId))
          && (CANTP_GET_RX_PDU_BLOCK_SIZE(NSduId) != 0U)
        )
      {
        /* Use configured BS if configured BS is smaller and not 0U (no config limit). */
        BlockSizeTmp = CANTP_GET_RX_PDU_BLOCK_SIZE(NSduId);
      }

      /* BS must be an 8 bit value - if it's bigger than that, use the maximum */
      /* Note: To avoid compiler warning if PduLengthType = uint8 ">=" is used instead of ">". */
      if(BlockSizeTmp >= 0xFFU)
      {
        /* Limit the BS to the maximum */
        BlockSizeTmp = 0xFFU;
      }
    }
    else
    {
      /* Calculation result indicates that not enough UL buffer available */
      Ret_BSCalc = E_NOT_OK;
    }
  }

  (*BlockSizePtr) = (uint8) BlockSizeTmp;

  return Ret_BSCalc;
}


FUNC(boolean, CANTP_CODE) CanTp_VerifyBlockSize
(
  P2VAR(CanTp_ChannelType, AUTOMATIC, CANTP_VAR) ChannelPtr
)
{
  boolean Ret_BS_Ok;
  const PduLengthType RemainingBytes = ChannelPtr->TotalLength - ChannelPtr->ProcessedLength;

  if(ChannelPtr->ActualBufferSize >= RemainingBytes)
  {
    /* There is enough UL buffer available for the whole message. Continue sending. */
    Ret_BS_Ok = TRUE;
  }
  else
  {
    Std_ReturnType BSCalc_Ok; /* Indication of the actual BS calculation */
    uint8 ActualBlockSize; /* Actual upper layer BS */

    BSCalc_Ok = CanTp_CalculateBlockSize(ChannelPtr, &ActualBlockSize);

    if(BSCalc_Ok == E_OK)
    {
      if(ActualBlockSize >= ChannelPtr->BlockSize)
      {
        /* The UL buffer is big enough for receiving the next block. Continue sending. */
        Ret_BS_Ok = TRUE;
      }
      else
      {
        /* The UL buffer is not big enough for receiving the next block. */
        Ret_BS_Ok = FALSE;
      }
    }
    else
    {
      /* Not enough UL buffer available. The required BS is not reached for this block. */
      Ret_BS_Ok = FALSE;
    }
  }

  return Ret_BS_Ok;
}

FUNC(void, CANTP_CODE) CanTp_CheckAndHandleWaitFrameTimeOut
(
  P2VAR(CanTp_ChannelType, AUTOMATIC, CANTP_VAR) ChannelPtr
)
{

  if(ChannelPtr->WftCounter > 0U)
  {
    /* initial tick count is (N_Br+N_Ar). if tick count equals or is smaller
       than N_Ar, N_Br is elapsed -> send a wait frame
     */
    if(ChannelPtr->Ticks <= CANTP_GET_RX_PDU_N_AR
                             (
                               &CANTP_CFG_GET_RXNSDU_CONFIG(ChannelPtr->NSduId)
                             )
       )
    {
      DBG_CANTP_CHANNEL_STATE_GRP(
                                  DBG_CANTP_GET_CHANNEL_INDEX(ChannelPtr),
                                  ChannelPtr->State,
                                  CANTP_CH_RX_TRANSMIT_FC_WT
                                 );

      /* set new state, timeout remains */
      TS_AtomicAssign8(ChannelPtr->State, CANTP_CH_RX_TRANSMIT_FC_WT);

      CanTp_PrepareFC(ChannelPtr, CANTP_N_PCI_FC_WT);
    }
  } /* else timeout occurs which will be handled in main function */
}

#endif /* CANTP_JUMPTABLE_MODE != CANTP_JUMPTABLE_CLIENT */

#if(TS_MERGED_COMPILE == STD_OFF)
#define CANTP_STOP_SEC_CODE
#include <CanTp_MemMap.h>
#endif /* TS_MERGED_COMPILE == STD_OFF */

/*==================[internal function definitions]=========================*/

/*==================[end of file]===========================================*/
