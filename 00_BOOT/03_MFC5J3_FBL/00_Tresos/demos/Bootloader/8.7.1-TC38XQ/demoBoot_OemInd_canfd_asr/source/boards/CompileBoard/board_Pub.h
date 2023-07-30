#ifndef _BOARD_PUB_H_
#define _BOARD_PUB_H_

#include <Platforms_defs.h>
extern void BoardDisableInterrupts(void);
extern void BoardEnableInterrupts(void);
extern void BoardSetState(Platforms_PowerType ubState);
extern void BoardPerformReset(Platforms_ResetType ubResetType);
extern uint32 BoardGetRandom(void);
extern void BoardPerformSwReset();
extern Platforms_ResetType BoardIsSwReset();


#endif 
