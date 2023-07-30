/*********************************************************************************/
/*                                                                               */
/*                                  N  C  S                                      */
/*                                                                               */
/* ----------------------------------------------------------------------------- */
/*                                                                               */
/*                       Standard NCS include file list                          */
/*                                                                               */
/*********************************************************************************/
/*%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%                                        */
/*%%   _____________________________   %%                                        */
/*%%  |             ___       ___   |  %%  File          : ncs.h                 */
/*%%  |   |\   |   /      &  /      |  %%  Company       : NCS                   */
/*%%  |   | \  |  /       &  \___   |  %%  Author        : Antoine DAVID         */
/*%%  |   |  \ |  \       &      \  |  %%  File version  : 1.02                  */
/*%%  |   |   \|   \___   &   ___/  |  %%  Version date  : 2010/04/02            */
/*%%  |_____________________________|  %%  Creation date : 2010/04/02            */
/*%%                                   %%                                        */
/*%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%                                        */
/*********************************************************************************/
/* Version history:                                                              */
/* 1.01: Add ncs_sdf.h inclusion                                                 */
/* 1.02: Add ncs_cbk.h inclusion                                                 */
/*********************************************************************************/


#ifndef __NCS_H__
#define __NCS_H__



/******************************** FILE INCLUSION *********************************/
/*                                                                               */
/*-------------------------------------------------------------------------------*/
/* List of NCS include files automatically included into all prj source files    */
#include <Std_Types.h>
#include <Platform_Types.h>
/* EXACT type definition */
/* Deviation MISRA-1 */
typedef uint8                   u8;         /* Range : 0..255 */
/* Deviation MISRA-1 */
typedef uint16                  u16;        /* Range : 0..65535 */
/* Deviation MISRA-1 */
typedef uint32                  u32;        /* Range : 0..4294967295 */
/* Deviation MISRA-1 */
typedef signed char             s8;         /* Range : -128..127 */
/* Deviation MISRA-1 */
typedef signed short int        s16;        /* Range : -32768..32767 */
/* Deviation MISRA-1 */
typedef signed long int         s32;        /* Range : -2147483648..2147483647 */


/* AT LEAST type definition */
/* Deviation MISRA-1 */
typedef unsigned int            u8m;         /* Range : at least 0..255 */
/* Deviation MISRA-1 */
typedef unsigned int            u16m;        /* Range : at least 0..65535 */
/* Deviation MISRA-1 */
typedef unsigned long int       u32m;        /* Range : at least 0..4294967295 */
/* Deviation MISRA-1 */
typedef signed int              s8m;         /* Range : at least -128..127 */
/* Deviation MISRA-1 */
typedef signed int              s16m;        /* Range : at least -32768..32767 */
/* Deviation MISRA-1 */
typedef signed long int         s32m;        /* Range : at least -2147483648..2147483647 */

#ifndef TRUE
    #define TRUE    (1U)
#endif

#ifndef FALSE
    #define FALSE   (0U)
#endif

/* NULL pointer definition if not already defined */
#ifndef NULL
    /* Deviation MISRA-2 */
    #define NULL   (0)
#endif


/*#include "ncs_limits.h"*/
#define U8_MAX          0xFFU
#define S8_MIN          (-127-1)
#define S8_MAX          127

#define U16_MAX         0xFFFFU
#define S16_MIN         (-32767-1)
#define S16_MAX         32767

#define U32_MAX         0xFFFFFFFFU
#define S32_MIN         (-2147483647-1)
#define S32_MAX         2147483647

/*#include "ncs_macro.h"*/
/* To be abble to access simply private function or data during function unitary */
/* test step.                                                                    */
/* "NCS_UNITARY_TEST " should de defined only for this step by compiler command   */
/* line setting.                                                                 */

#ifdef NCS_UNITARY_TEST
    #define NCS_PRI_FCT
    #define NCS_PRI_VAR
#else
    #define NCS_PRI_FCT   static
    #define NCS_PRI_VAR   static
#endif
#ifndef BOARD_ASM

/***************************** BITFIELD MANIPULATION *****************************/
/* These 4 macros work on any size variable compatible with bitfield operations  */
/* Id est unsigned types such as u8, u16 or u32 types.                           */
/* Var       parameter stands for the variable used                              */
/* BitField  parameter stands for the list of bits to work on                    */
/* Type      parameter stands for the type of the variable used                  */


/* To set some bits into a variable (those set into BitField *
 * a read modify write operation is done here, be careful to *
 * be in critical section when using this macro              */
#define NCS_SET_BIT(Var,BitField,Type)      ((Var) |= (Type)(BitField))

/* To reset some bits into a variable (those set into BitField *
 * a read modify write operation is done here, be careful to  *
 * be in critical section when using this macro               */
#define NCS_RESET_BIT(Var,BitField,Type)    ((Var) &= (Type)~(Type)(BitField))

/* To test to 1 all selected bits into a variable (those set into BitField */
#define NCS_TST_BIT_SET(Var,BitField,Type)  (0U != ((Var) & (Type)(BitField)))

/* To test to 0 all selected bits into a variable (those set into BitField */
#define NCS_TST_BIT_RESET(Var,BitField,Type)  (0U == ((Var) & (Type)(BitField)))





/***************** REMOVING UNUSED PARAMETER COMPILER WARNING ********************/
/* The macro OSC_PARAM_UNUSED shall be used in source code in order to avoid a    */
/* compiler warning like "warning: unused parameter 'my_variable'                */

#if (defined OSC_PARAM_UNUSED)
#error OSC_PARAM_UNUSED already defined
#endif

#if (defined EB_STATIC_CHECK)
/*  This macro can be used to avoid compiler warnings
 * It is left empty to not product a false positive for MISRA 14.2 */
#define OSC_PARAM_UNUSED(x)
#else
/* This macro can be used to avoid compiler warnings */
#define OSC_PARAM_UNUSED(x) ((void) (x))
#endif
/*#include "ncs_sdf.h"*/

#define SDF_UDS_SESSION_CODE 0x0000U /*Variable of the m_eSessionCode of the UDS layer */
#define SDF_UDS_SESSION_MASK 0x0001U /*Variable of the m_eSessionMask of the UDS layer */
#define SDF_COM_MODE		 0x0010U /*Variable of the m_eComMode of the COM layer */
#define SDF_NM_MODE			 0x0020U /*Variable of the m_eNmMode of the NM layer */
#define SDF_NM_MON_AUTHOR	 0x0021U /*Variable of the m_eMonAuthor of the NM layer */
#define SDF_NM_BUS_STATUS    0x0022U /*Variable of the m_aeBusStatus of the NM layer */
#define SDF_NM_BUSOFF_STATE  0x0023U /*Variable of the m_NmBusOffStateMachine of the NM layer */
#define SDF_NM_FAULT_STATUS  0x0024U /*Variable of the table m_eMonConfStatus of NM layer */
#define SDF_JDD_MODE		 0x0030U /*Variable of the m_eJddMode of the JDD layer */
#define SDF_JDD_MUTE_STATUS  0x0031U /*Variable of the m_eJddMuteStatus of the JDD layer */
#define SDF_OM_OPER_MODE	 0x0040U /*Variable of the m_eOperMode of the OM layer */
#define SDF_OM_OPER_MODE_OLD 0x0041U /*Variable of the m_eOperModeOld of the OM layer */
#define SDF_GAT_MODE		 0x0060U /*Variable of the m_eGatMode of the GAT layer */
#define SDF_GAT_CUR_FUNC_MODE 0x0061U /*Variable of the m_eGatCurFuncMode of the GAT layer */
#define SDF_LGHD_MODE   	 0x0070U /*Variable of the m_eJddMode of the LGHD layer */
#define SDF_LGHD_EVTX		 0x0071U /*Variable of m_ubEvTxOK and  m_eEvtDefTxInProgress of the LGHD layer */

/*SDF 8 bytes variables values*/
#define SDF_U8_VALUE1 0x69U
#define SDF_U8_VALUE2 0x96U
#define SDF_U8_VALUE3 0xC3U
#define SDF_U8_VALUE4 0x3CU
#define SDF_U8_VALUE5 0xAAU
#define SDF_U8_VALUE6 0x55U

/*SDF 16 bytes variables values*/
#define SDF_U16_VALUE1 0x6969U
#define SDF_U16_VALUE2 0x9669U
#define SDF_U16_VALUE3 0xC369U
#define SDF_U16_VALUE4 0x3C69U
#define SDF_U16_VALUE5 0xAA69U
#define SDF_U16_VALUE6 0x5569U
#define SDF_U16_VALUE7 0x6996U
#define SDF_U16_VALUE8 0x9696U
#define SDF_U16_VALUE9 0xC396U
#define SDF_U16_VALUE10 0x3C96U
#define SDF_U16_VALUE11 0xAA96U
#define SDF_U16_VALUE12 0x5596U
#define SDF_U16_VALUE13 0x69C3U
#define SDF_U16_VALUE14 0x96C3U
#define SDF_U16_VALUE15 0xC3C3U
#define SDF_U16_VALUE16 0x3CC3U
#define SDF_U16_VALUE17 0xAAC3U
#define SDF_U16_VALUE18 0x55C3U
#define SDF_U16_VALUE19 0x693CU
#define SDF_U16_VALUE20 0x963CU
#define SDF_U16_VALUE21 0xC33CU
#define SDF_U16_VALUE22 0x3C3CU
#define SDF_U16_VALUE23 0xAA3CU
#define SDF_U16_VALUE24 0x553CU
#define SDF_U16_VALUE25 0x69AAU
#define SDF_U16_VALUE26 0x96AAU
#define SDF_U16_VALUE27 0xC3AAU
#define SDF_U16_VALUE28 0x3CAAU
#define SDF_U16_VALUE29 0xAAAAU
#define SDF_U16_VALUE30 0x55AAU
#define SDF_U16_VALUE31 0x6955U
#define SDF_U16_VALUE32 0x9655U
#define SDF_U16_VALUE33 0xC355U
#define SDF_U16_VALUE34 0x3C55U
#define SDF_U16_VALUE35 0xAA55U
#define SDF_U16_VALUE36 0x5555U

/*#include "ncs_cbk.h"*/
/*critical section API                                                           */
extern void NCS_SdfVariableCoherencyError(u16 uwParam);
extern void NCS_SdfVariableRangeError(u16 uwParam);

#endif
#endif  /* __NCS_H__ */
/* End of file */
