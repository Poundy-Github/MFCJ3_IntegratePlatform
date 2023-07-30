/**
 * \file
 *
 * \brief AUTOSAR Atomics
 *
 * This file contains the implementation of the AUTOSAR
 * module Atomics.
 *
 * \author Elektrobit Automotive GmbH, 91058 Erlangen, Germany
 *
 * Copyright 2017 - 2019 Elektrobit Automotive GmbH
 * All rights exclusively reserved for Elektrobit Automotive GmbH,
 * unless expressly agreed to otherwise.
 */

/* MISRA-C:2012 Deviation List
 *
 * MISRAC2012-1) Deviated Rule: 20.7 (required)
 *  Expressions resulting from the expansion of macro parameters shall be
 *  enclosed in parentheses.
 *
 * Reason:
 *  False positive. The parameter 'successaddr' is enclosed in paraentheses
 *  in the macros ATOMICS_USER_[UN]LOCK_OBJECT.
 */

/* This file contains the generic implementation of the compatibility functions
 * for atomic bit set/clear and interrupt control operations.
 */

#include <Os.h>
#include <Atomics.h>
#include <Atomics_TSPlatforms.h>
#include <Atomics_platform_types.h>
#include <TSAutosar.h>

/* The generic implementation of the atomic bit-set operation. */
#define TSP_GENERIC_SET_IMPL(addr, bitIdx, T)               \
    do {                                                    \
        VAR(boolean, AUTOMATIC) success;                    \
                                                            \
        ATOMICS_USER_THREAD_FENCE();                        \
        ATOMICS_USER_LOCK_OBJECT((addr), &success);         \
        if (success)                                        \
        {                                                   \
            *(addr) = *(addr) | (T)((T)1u << (bitIdx));     \
            ATOMICS_USER_UNLOCK_OBJECT((addr), &success);   \
            ATOMICS_USER_THREAD_FENCE();                    \
        }                                                   \
    } while (0)

/* The generic implementation of the atomic bit-clear operation. */
#define TSP_GENERIC_CLEAR_IMPL(addr, bitIdx, T)             \
    do {                                                    \
        VAR(boolean, AUTOMATIC) success;                    \
                                                            \
        ATOMICS_USER_THREAD_FENCE();                        \
        ATOMICS_USER_LOCK_OBJECT((addr), &success);         \
        if (success)                                        \
        {                                                   \
            *(addr) = *(addr) & (T)~((T)((T)1u << (bitIdx)));\
            ATOMICS_USER_UNLOCK_OBJECT((addr), &success);   \
            ATOMICS_USER_THREAD_FENCE();                    \
        }                                                   \
    } while (0)

#define ATOMICS_START_SEC_CODE
#include <Atomics_MemMap.h>

/* !LINKSTO Atomics.TS.BitSet, 1 */
FUNC(void, ATOMICS_CODE) TS_AtomicSetBit_8(
    volatile P2VAR(uint8, AUTOMATIC, ATOMICS_APPL_DATA) addr,
    VAR(uint32, AUTOMATIC) bitIdx)
{
    /* Deviation MISRAC2012-1 <1> */
    TSP_GENERIC_SET_IMPL(addr, bitIdx, uint8);
}

/* !LINKSTO Atomics.TS.BitClear, 1 */
FUNC(void, ATOMICS_CODE) TS_AtomicClearBit_8(
    volatile P2VAR(uint8, AUTOMATIC, ATOMICS_APPL_DATA) addr,
    VAR(uint32, AUTOMATIC) bitIdx)
{
    /* Deviation MISRAC2012-1 <1> */
    TSP_GENERIC_CLEAR_IMPL(addr, bitIdx, uint8);
}

/* !LINKSTO Atomics.TS.BitSet, 1 */
FUNC(void, ATOMICS_CODE) TS_AtomicSetBit_16(
    volatile P2VAR(uint16, AUTOMATIC, ATOMICS_APPL_DATA) addr,
    VAR(uint32, AUTOMATIC) bitIdx)
{
    /* Deviation MISRAC2012-1 <1> */
    TSP_GENERIC_SET_IMPL(addr, bitIdx, uint16);
}

/* !LINKSTO Atomics.TS.BitClear, 1 */
FUNC(void, ATOMICS_CODE) TS_AtomicClearBit_16(
    volatile P2VAR(uint16, AUTOMATIC, ATOMICS_APPL_DATA) addr,
    VAR(uint32, AUTOMATIC) bitIdx)
{
    /* Deviation MISRAC2012-1 <1> */
    TSP_GENERIC_CLEAR_IMPL(addr, bitIdx, uint16);
}

/* !LINKSTO Atomics.TS.BitSet, 1 */
FUNC(void, ATOMICS_CODE) TS_AtomicSetBit_32(
    volatile P2VAR(uint32, AUTOMATIC, ATOMICS_APPL_DATA) addr,
    VAR(uint32, AUTOMATIC) bitIdx)
{
    /* Deviation MISRAC2012-1 <1> */
    TSP_GENERIC_SET_IMPL(addr, bitIdx, uint32);
}

/* !LINKSTO Atomics.TS.BitClear, 1 */
FUNC(void, ATOMICS_CODE) TS_AtomicClearBit_32(
    volatile P2VAR(uint32, AUTOMATIC, ATOMICS_APPL_DATA) addr,
    VAR(uint32, AUTOMATIC) bitIdx)
{
    /* Deviation MISRAC2012-1 <1> */
    TSP_GENERIC_CLEAR_IMPL(addr, bitIdx, uint32);
}

#if CPU_TYPE == CPU_TYPE_64
/* !LINKSTO Atomics.TS.BitSet, 1 */
FUNC(void, ATOMICS_CODE) TS_AtomicSetBit_64(
    volatile P2VAR(uint64, AUTOMATIC, ATOMICS_APPL_DATA) addr,
    VAR(uint32, AUTOMATIC) bitIdx)
{
    /* Deviation MISRAC2012-1 <1> */
    TSP_GENERIC_SET_IMPL(addr, bitIdx, uint64);
}

/* !LINKSTO Atomics.TS.BitClear, 1 */
FUNC(void, ATOMICS_CODE) TS_AtomicClearBit_64(
    volatile P2VAR(uint64, AUTOMATIC, ATOMICS_APPL_DATA) addr,
    VAR(uint32, AUTOMATIC) bitIdx)
{
    /* Deviation MISRAC2012-1 <1> */
    TSP_GENERIC_CLEAR_IMPL(addr, bitIdx, uint64);
}
#endif /* CPU_TYPE == CPU_TYPE_64 */

/* !LINKSTO Atomics.TS.InterruptControl.Disable, 1 */
TS_IntStatusType TS_IntDisable(void)
{
    SuspendAllInterrupts();
    return 0u;
}

/* !LINKSTO Atomics.TS.InterruptControl.Restore, 1 */
void TS_IntRestore(VAR(TS_IntStatusType, AUTOMATIC) intStatus)
{
    TS_PARAM_UNUSED(intStatus);
    ResumeAllInterrupts();
}

#define ATOMICS_STOP_SEC_CODE
#include <Atomics_MemMap.h>
