/********************************************************************************
 *                                                                               *
 *                                 EB Layers                                     *
 *                                                                               *
 * ----------------------------------------------------------------------------- *
 *                                                                               *
 *                                   Board                                       *
 *                                                                               *
 *********************************************************************************
 *%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%                                        *
 *%%   _____________________________   %%  \file Board.c                         *
 *%%  |                             |  %%                                        *
 *%%  |   &&&&&   &&&&&             |  %%  Module version: 1.0.0                 *
 *%%  |   &       &    &            |  %%                                        *
 *%%  |   &&&&    &&&&&             |  %%                                        *
 *%%  |   &       &    &            |  %%                                        *
 *%%  |   &&&&&   &&&&&             |  %%                                        *
 *%%  |_____________________________|  %%                                        *
 *%%                                   %%                                        *
 *%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%                                        *
 *********************************************************************************
 * Copyright 2015 by Elektrobit Automotive GmbH                                  *
 * All rights exclusively reserved for Elektrobit Automotive GmbH,               *
 * unless expressly agreed to otherwise.                                         *
 ********************************************************************************/
/* Board.c file
 * !LINKSTO OsekCore.Platforms.Board.001, 1
 *          OsekCore.Platforms.Board.012, 1
 */

#ifndef I_KNOW_THAT_THIS_CODE_IS_NOT_FOR_PRODUCTION
#error "the program is not qualified for series production"
#endif

#include "TSAutosar.h"
#include "board.h"
#include <Platforms_asm_TRICORE.h>
#if defined( BOARD_ISR_CAN0 ) || defined( BOARD_ISR_LIN0 )
#include "EB_Prj.h"
#endif

#ifdef BOARD_ISR_FR0
void BoardFrInterrupt (void);
#endif

#ifdef BOARD_ISR_CAN0
void BoardCan0Interrupt0 (void);
void BoardCan0Interrupt1 (void);
void BoardCan0Interrupt2 (void);
void BoardCan0Interrupt3 (void);
void BoardCan0Interrupt4 (void);
void BoardCan0Interrupt5 (void);
void BoardCan0Interrupt6 (void);
void BoardCan0Interrupt7 (void);
void BoardCan0Interrupt8 (void);
void BoardCan0Interrupt9 (void);
void BoardCan0Interrupt10 (void);
void BoardCan0Interrupt11 (void);
void BoardCan0Interrupt12 (void);
void BoardCan0Interrupt13 (void);
void BoardCan0Interrupt14 (void);
void BoardCan0Interrupt15 (void);

/*void CAN_ErrorStatusInterrupt(unsigned int, unsigned int);
void CAN_TxInterrupt(unsigned int, unsigned int);
void CAN_RxInterrupt(unsigned int, unsigned int);*/
#endif

#ifdef BOARD_ISR_LIN0
void INTERRUPT_FUNC(BOARD_LIN_INT_VECT_TX) BoardLinTXInterrupt(void);
void INTERRUPT_FUNC(BOARD_LIN_INT_VECT_RX) BoardLinRXInterrupt(void);
void INTERRUPT_FUNC(BOARD_LIN_INT_VECT_ERR) BoardLinERRInterrupt(void);
#endif
/*
 * !LINKSTO OsekCore.Platforms.Board.101, 1
 */
#ifdef BOARD_ISR_TEST
void TestIsr (void);
#endif

#ifdef BOARD_ISR_FR0
void INTERRUPT_FUNC(BOARD_FR_INT_VECT) BoardFrInterrupt (void)
{

}
#endif

#ifdef BOARD_ISR_TEST
void INTERRUPT_FUNC(BOARD_TEST_INT_VECT) TestIsr(void)
{
    ubBoardIntLockNestingCounter++;
    isrCounter++;
  
    /* In order to verify that ISR handler will not be lost
     * if during the interrupt routine, another ISR was triggered
     */
    if(isrCounter == 3U)
    {
        TRIGGER_INT();
    }
    ubBoardIntLockNestingCounter--;
}
#endif

#ifdef BOARD_ISR_CAN0
void INTERRUPT_FUNC(BOARD_CAN_INT_VECT0) BoardCan0Interrupt0 (void)
{
    /* Error Status : Bus Off or Line opening */
#if (CAN_ERROR_STATUS_MODE == CAN_INTERRUPT_MODE)
    ubBoardIntLockNestingCounter++;
    Can_17_McmCan_IsrReceiveHandler(1, 0);
    ubBoardIntLockNestingCounter--;
#endif

}
void INTERRUPT_FUNC(BOARD_CAN_INT_VECT1) BoardCan0Interrupt1 (void)
{
    /* Tx */
#if (CAN_TX_MODE == CAN_INTERRUPT_MODE)
    ubBoardIntLockNestingCounter++;
    Can_17_McmCan_IsrTransmitHandler(1, 0);
    ubBoardIntLockNestingCounter--;
#endif
}
void INTERRUPT_FUNC(BOARD_CAN_INT_VECT2) BoardCan0Interrupt2 (void)
{
    /* Rx */
#if (CAN_RX_MODE == CAN_INTERRUPT_MODE)
    ubBoardIntLockNestingCounter++;
    Can_17_McmCan_IsrBusOffHandler(1, 0);
    ubBoardIntLockNestingCounter--;
#endif
}
void INTERRUPT_FUNC(BOARD_CAN_INT_VECT3) BoardCan0Interrupt3 (void)
{

}
void INTERRUPT_FUNC(BOARD_CAN_INT_VECT4) BoardCan0Interrupt4 (void)
{

}
void INTERRUPT_FUNC(BOARD_CAN_INT_VECT5) BoardCan0Interrupt5 (void)
{

}
void INTERRUPT_FUNC(BOARD_CAN_INT_VECT6) BoardCan0Interrupt6 (void)
{

}
void INTERRUPT_FUNC(BOARD_CAN_INT_VECT7) BoardCan0Interrupt7 (void)
{

}
void INTERRUPT_FUNC(BOARD_CAN_INT_VECT8) BoardCan0Interrupt8 (void)
{

}
void INTERRUPT_FUNC(BOARD_CAN_INT_VECT9) BoardCan0Interrupt9 (void)
{

}
void INTERRUPT_FUNC(BOARD_CAN_INT_VECT10) BoardCan0Interrupt10 (void)
{

}
void INTERRUPT_FUNC(BOARD_CAN_INT_VECT11) BoardCan0Interrupt11 (void)
{

}
void INTERRUPT_FUNC(BOARD_CAN_INT_VECT12) BoardCan0Interrupt12 (void)
{

}
void INTERRUPT_FUNC(BOARD_CAN_INT_VECT13) BoardCan0Interrupt13 (void)
{

}
void INTERRUPT_FUNC(BOARD_CAN_INT_VECT14) BoardCan0Interrupt14 (void)
{

}
void INTERRUPT_FUNC(BOARD_CAN_INT_VECT15) BoardCan0Interrupt15 (void)
{

}
#endif

#ifdef BOARD_ISR_LIN0
void INTERRUPT_FUNC(BOARD_LIN_INT_VECT_TX) BoardLinTXInterrupt(void)
{
    ubBoardIntLockNestingCounter++;
    LIN_TxInterrupt();
    ubBoardIntLockNestingCounter--;
}
void INTERRUPT_FUNC(BOARD_LIN_INT_VECT_RX) BoardLinRXInterrupt(void)
{
    ubBoardIntLockNestingCounter++;
    LIN_RxInterrupt();
    ubBoardIntLockNestingCounter--;
}
void INTERRUPT_FUNC(BOARD_LIN_INT_VECT_ERR) BoardLinERRInterrupt(void)
{
    ubBoardIntLockNestingCounter++;
    LIN_ErrInterrupt();
    ubBoardIntLockNestingCounter--;
}
#endif
