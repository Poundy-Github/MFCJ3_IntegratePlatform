#ifndef CAN_TYPES_H
#define CAN_TYPES_H

#define CAN_CTRL_NB                     1U


#if (CAN_CTRL_NB > 1U)
    #define CTRLIDX         u8 ubCtrlIdx,
    #define CTRLIDX_VOID    u8 ubCtrlIdx
    #define IDXCTRL         ubCtrlIdx,
    #define IDXCTRL_VOID    ubCtrlIdx
#else
    #define CTRLIDX
    /* Deviation MISRA-1 */
    #define CTRLIDX_VOID    void
    #define IDXCTRL
    #define IDXCTRL_VOID
#endif


#endif      /* CAN_TYPES_H */

