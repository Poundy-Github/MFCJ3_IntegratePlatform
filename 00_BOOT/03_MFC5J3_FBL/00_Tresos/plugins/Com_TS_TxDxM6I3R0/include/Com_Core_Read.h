/**
 * \file
 *
 * \brief AUTOSAR Com
 *
 * This file contains the implementation of the AUTOSAR
 * module Com.
 *
 * \author Elektrobit Automotive GmbH, 91058 Erlangen, Germany
 *
 * Copyright 2005 - 2019 Elektrobit Automotive GmbH
 * All rights exclusively reserved for Elektrobit Automotive GmbH,
 * unless expressly agreed to otherwise.
 */

#ifndef COM_CORE_READ_H_
#define COM_CORE_READ_H_

/*==================[inclusions]============================================*/

#include <TSAutosar.h>
#include <Com_Priv.h>

/*==================[macros]================================================*/

#ifndef COM_READFUNCS
#define COM_READFUNCS Com_ReadFuncs
#endif

#if (defined COM_CORE_READ_CORE_SIZE) /* To prevent double declaration */
#error COM_CORE_READ_CORE_SIZE already defined
#endif

/** \brief Define COM_CORE_READ_CORE_SIZE
 * Number of different implementations in function pointer array
 */
#define COM_CORE_READ_CORE_SIZE  (uint16)64U


#if (defined COM_CORE_READ_ARRAY_SIZE) /* To prevent double declaration */
#error COM_CORE_READ_ARRAY_SIZE already defined
#endif

/** \brief Define COM_CORE_READ_ARRAY_SIZE
 * Total number of entries in function pointer array
 */
#define COM_CORE_READ_ARRAY_SIZE (COM_CORE_READ_CORE_SIZE * 2U)


#if (defined COM_CORE_READ_CORE_MASK) /* To prevent double declaration */
#error COM_CORE_READ_CORE_MASK already defined
#endif

/** \brief Define COM_CORE_READ_CORE_MASK
 * Mask to access the core function (independent if an extension is configured)
 */
#define COM_CORE_READ_CORE_MASK (COM_CORE_READ_CORE_SIZE - 1U)


#if (defined COM_CORE_READ_EXTENDED_MASK) /* To prevent double declaration */
#error COM_CORE_READ_EXTENDED_MASK already defined
#endif

/** \brief Define COM_CORE_READ_EXTENDED_MASK
 * Mask to access the extended function (masks out flags which are not relevant for library)
 */
#define COM_CORE_READ_EXTENDED_MASK (COM_CORE_READ_ARRAY_SIZE - 1U)

/** \brief Define COM_CORE_READ_DUMMY_MASK
 * Mask to access the extended function (masks out flags which are not relevant for library)
 */
#define COM_CORE_READ_DUMMY_MASK ((uint16)(23U))

#if (defined COM_CORE_READ_CLEAR_LOCK_FLAG) /* To prevent double declaration */
#error COM_CORE_READ_CLEAR_LOCK_FLAG already defined
#endif

/** \brief Define COM_CORE_READ_CLEAR_LOCK_FLAG
 * Mask clears flag which defines if buffer shall be locked (3rd bit position)
 */
#define COM_CORE_READ_CLEAR_LOCK_FLAG ((uint16)0xFFF7U)


#if (defined COM_CORE_READ_CLEAR_SIGN_FLAG) /* To prevent double declaration */
#error COM_CORE_READ_CLEAR_SIGN_FLAG already defined
#endif

/** \brief Define COM_CORE_READ_CLEAR_SIGN_FLAG
 * Mask clears flag which defines if sign extension is done (4th bit position) 
 */
#define COM_CORE_READ_CLEAR_SIGN_FLAG ((uint16)0xFFEFU)


#if (defined COM_CORE_READ_CORE_MASK_NOLOCK) /* To prevent double declaration */
#error COM_CORE_READ_CORE_MASK_NOLOCK already defined
#endif

/** \brief Define COM_CORE_READ_EXTENDED_MASK
 * Mask to access (independent if an extension is configured)
 * - core function
 * - no buffer lock
 */
#define COM_CORE_READ_CORE_MASK_NOLOCK \
   (COM_CORE_READ_CORE_MASK \
            & COM_CORE_READ_CLEAR_LOCK_FLAG)


#if (defined COM_CORE_READ_CORE_MASK_NOSIGN) /* To prevent double declaration */
#error COM_CORE_READ_CORE_MASK_NOSIGN already defined
#endif

/** \brief Define COM_CORE_READ_CORE_MASK_NOSIGN
 * Mask to access (independent if an extension is configured)
 * - core function
 * - no sign extension
 */
#define COM_CORE_READ_CORE_MASK_NOSIGN \
      (COM_CORE_READ_CORE_MASK \
            & COM_CORE_READ_CLEAR_SIGN_FLAG)


#if (defined COM_CORE_READ_CORE_MASK_NOLOCK_NOSIGN) /* To prevent double declaration */
#error COM_CORE_READ_CORE_MASK_NOLOCK_NOSIGN already defined
#endif

/** \brief Define COM_CORE_READ_CORE_MASK_NOLOCK_NOSIGN
 * Mask to access (independent if an extension is configured)
 * - core function
 * - no buffer lock
 * - no sign extension
 */
#define COM_CORE_READ_CORE_MASK_NOLOCK_NOSIGN \
      (COM_CORE_READ_CORE_MASK_NOLOCK \
            & COM_CORE_READ_CLEAR_SIGN_FLAG)


#if (defined Com_EB_Read_Get_Fptr) /* To prevent double declaration */
#error Com_EB_Read_Get_Fptr already defined
#endif

/** \brief Com_EB_Read_Get_Fptr
 * Provides a function pointer of from the function pointer array
 * \param[in] Com_EB_ReadPropPtr - configuration of a signal
 * \param[in] mask - mask which shall be applied for function pointer extraction
 * \param[out] fptr - calculated function pointer
 */
#define Com_EB_Read_Get_Fptr(Com_EB_ReadPropPtr, mask, fptr) \
   do{ \
      uint16 const index = ((Com_EB_ReadPropPtr)->ComRxSignalFlags & (mask)); \
      (fptr) =  COM_READFUNCS[index]; \
   }while(0)


#if (defined Com_EB_Read_Call_HLP) /* To prevent double declaration */
#error Com_EB_Read_Call_HLP already defined
#endif

/** \brief Com_EB_Read_Call_HLP
 * Invokes a library function
 * \param[in] SignalDataPtr - pointer to signal value
 * \param[in] dataPtr - buffer to which the data shall be read
 * \param[in] Com_EB_ReadPropPtr - configuration of a signal
 * \param[in] mask - mask which shall be applied for function pointer extraction
 */
#define Com_EB_Read_Call_HLP(SignalDataPtr, dataPtr, Com_EB_ReadPropPtr, mask, retval) \
   do{ \
      P2VAR(Com_ReadFuncType, AUTOMATIC, COM_CODE) fptr;  \
      Com_EB_Read_Get_Fptr(Com_EB_ReadPropPtr, mask, fptr); \
      fptr((SignalDataPtr), (dataPtr), (Com_EB_ReadPropPtr), (retval)); \
   }while(0)


#if (defined Com_EB_Read_Core) /* To prevent double declaration */
#error Com_EB_Read_Core already defined
#endif

/** \brief Com_EB_Read_Core
 * Invokes a library function (core part, independent from if extensions is configured)
 * \param[in] SignalDataPtr - pointer to signal value
 * \param[in] dataPtr - buffer to which the data shall be read
 * \param[in] Com_EB_ReadPropPtr - configuration of a signal
 */
#define Com_EB_Read_Core(SignalDataPtr, dataPtr, Com_EB_ReadPropPtr, retval) \
   Com_EB_Read_Call_HLP((SignalDataPtr), (dataPtr), (Com_EB_ReadPropPtr), COM_CORE_READ_CORE_MASK, (retval))


#if (defined Com_EB_Read_Ext) /* To prevent double declaration */
#error Com_EB_Read_Ext already defined
#endif

/** \brief Com_EB_Read_Ext
 * Invokes a library function
 * \param[in] SignalDataPtr - pointer to signal value
 * \param[in] dataPtr - buffer to which the data shall be read
 * \param[in] Com_EB_ReadPropPtr - configuration of a signal
 */
#define Com_EB_Read_Ext(SignalDataPtr, dataPtr, Com_EB_ReadPropPtr, retval) \
   Com_EB_Read_Call_HLP((SignalDataPtr), (dataPtr), (Com_EB_ReadPropPtr), COM_CORE_READ_EXTENDED_MASK, (retval))


#if (defined Com_EB_Read_Core_NoLock) /* To prevent double declaration */
#error Com_EB_Read_Core_NoLock already defined
#endif

/** \brief Com_EB_Read_Core_NoLock
 * Invokes a library function, independent from if extensions is configured:
 * - core part,
 * - no buffer lock,
 * \param[in] SignalDataPtr - pointer to signal value
 * \param[in] dataPtr - buffer to which the data shall be read
 * \param[in] Com_EB_ReadPropPtr - configuration of a signal
 */
#define Com_EB_Read_Core_NoLock(SignalDataPtr, dataPtr, Com_EB_ReadPropPtr, retval) \
   Com_EB_Read_Call_HLP((SignalDataPtr), (dataPtr), (Com_EB_ReadPropPtr), \
            COM_CORE_READ_CORE_MASK_NOLOCK, (retval))


#if (defined Com_EB_Read_Core_NoSign) /* To prevent double declaration */
#error Com_EB_Read_Core_NoSign already defined
#endif

/** \brief Com_EB_Read_Core_NoSign
 * Invokes a library function, independent from if extensions is configured:
 * - core part,
 * - no sign extension
 * \param[in] SignalDataPtr - pointer to signal value
 * \param[in] dataPtr - buffer to which the data shall be read
 * \param[in] Com_EB_ReadPropPtr - configuration of a signal
 */
#define Com_EB_Read_Core_NoSign(SignalDataPtr, dataPtr, Com_EB_ReadPropPtr, retval) \
   Com_EB_Read_Call_HLP((SignalDataPtr), (dataPtr), (Com_EB_ReadPropPtr), \
            COM_CORE_READ_CORE_MASK_NOSIGN, (retval))

#if (defined Com_EB_Read_Core_NoLock_NoSign) /* To prevent double declaration */
#error Com_EB_Read_Core_NoLock_NoSign already defined
#endif

/** \brief Com_EB_Read_Core_NoLock_NoSign
 * Invokes a library function, independent from if extensions is configured:
 * - core part,
 * - no buffer lock,
 * - no sign extension
 * \param[in] SignalDataPtr - pointer to signal value
 * \param[in] dataPtr - buffer to which the data shall be read
 * \param[in] Com_EB_ReadPropPtr - configuration of a signal
 */
#define Com_EB_Read_Core_NoLock_NoSign(SignalDataPtr, dataPtr, Com_EB_ReadPropPtr, retval) \
   Com_EB_Read_Call_HLP((SignalDataPtr), (dataPtr), (Com_EB_ReadPropPtr), \
            COM_CORE_READ_CORE_MASK_NOLOCK_NOSIGN, (retval))


/*==================[type definitions]======================================*/

/** \brief Define Com_ReadFuncType
 * signature of a library function for de-serialization
 */
typedef FUNC(void, COM_CODE) (Com_ReadFuncType)
(
   P2VAR(void, AUTOMATIC, COM_APPL_DATA) SignalDataPtr,
   P2CONST(uint8, AUTOMATIC, COM_VAR_NOINIT) dataPtr,
   P2CONST(ComSignalBaseType, AUTOMATIC, AUTOMATIC) Com_EB_ReadPropPtr,
   P2VAR(uint8, AUTOMATIC, COM_APPL_DATA) retvalPtr
);

/*==================[external function declarations]========================*/

/*==================[internal function declarations]========================*/

/*==================[external constants]====================================*/

#define COM_START_SEC_CONST_UNSPECIFIED
#include <Com_MemMap.h>

extern CONSTP2VAR(Com_ReadFuncType, AUTOMATIC, COM_CODE)
        COM_READFUNCS[COM_CORE_READ_ARRAY_SIZE];

#define COM_STOP_SEC_CONST_UNSPECIFIED
#include <Com_MemMap.h>

/*==================[internal constants]====================================*/

/*==================[external data]=========================================*/

/*==================[internal data]=========================================*/

/*==================[external function definitions]=========================*/

/*==================[internal function definitions]=========================*/


#endif /* COM_CORE_READ_H_ */