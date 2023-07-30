#if (!defined COMSTACK_CFG_H)
/* !LINKSTO Base.ASR403.COMTYPE016,1 */
#define COMSTACK_CFG_H

/**
 * \file
 *
 * \brief AUTOSAR Base
 *
 * This file contains the implementation of the AUTOSAR
 * module Base.
 *
 * \author Elektrobit Automotive GmbH, 91058 Erlangen, Germany
 *
 * Copyright 2005 - 2019 Elektrobit Automotive GmbH
 * All rights exclusively reserved for Elektrobit Automotive GmbH,
 * unless expressly agreed to otherwise.
 */
/* !LINKSTO Base.ASR403.COMTYPE003,1, Base.ASR403.COMTYPE015,1, Base.ASR403.COMTYPE029,1 */
    
/*==================[macros]=================================================*/

/*------------------[Size of Autosar Comstack Types]-------------------------*/

#if (defined TS_SIZE_PduIdType)
#error TS_SIZE_PduIdType already defined
#endif
/** \brief Size of AUTOSAR standard type PduIdType
 *
 * this value is fixed to 2U (see deviations of EcuC)
 */
#define TS_SIZE_PduIdType 2U

#if (defined TS_SIZE_PduLengthType)
#error TS_SIZE_PduLengthType already defined
#endif
/** \brief Size of AUTOSAR standard type PduLengthType
 *
 * this value depends on EcuC parameter PduLengthType (see deviations of EcuC)
 */
#define TS_SIZE_PduLengthType 2U

/*==================[type definitions]======================================*/

/* !LINKSTO Base.ASR403.COMTYPE030,1,Base.ASR403.COMTYPE005,1,Base.ASR403.COMTYPE006,1,Base.ASR403.COMTYPE007,1,Base.ASR403.COMTYPE014,1 */
/** \brief Type for a unique identifier for a PDU
 *
 * this type is fixed to uint16 (see deviations of EcuC)
 * - range: 0 .. PduIdmax
 */
typedef uint16 PduIdType;

/* !LINKSTO Base.ASR403.COMTYPE030,1,Base.ASR403.COMTYPE008,1,Base.ASR403.COMTYPE010,1,Base.ASR403.COMTYPE017,1 */
/** \brief Type for lengths information of a PDU
 *
 * this type is configureable to uint16 and uint32 (see deviations of EcuC)
 * - range: 0 .. PduLengthmax
 */
typedef uint16 PduLengthType;

#endif /* if !defined( COMSTACK_CFG_H ) */
/*==================[end of file]============================================*/
