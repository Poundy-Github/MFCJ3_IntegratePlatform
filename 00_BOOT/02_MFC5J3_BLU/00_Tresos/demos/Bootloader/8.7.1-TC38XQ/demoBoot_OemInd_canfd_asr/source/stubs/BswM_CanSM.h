#if (!defined BSWM_CANSM_H)
#define BSWM_CANSM_H

#include "CanSM.h"
#include <CanSM_BswM.h>         /* CanSM_BswMCurrentStateType */

extern FUNC(void, BSWM_CODE) BswM_CanSM_CurrentState
(
  NetworkHandleType Network,
  CanSM_BswMCurrentStateType CurrentState
);

#endif /* if !defined( BSWM_CANSM_H ) */

