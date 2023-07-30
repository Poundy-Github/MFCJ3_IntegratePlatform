/**
 * \file
 *
 * \brief Autosar ApplTemplates
 *
 * This file contains the implementation of the Autosar
 * module ApplTemplates.
 *
 * \author Elektrobit Automotive GmbH, 91058 Erlangen, Germany
 *
 * Copyright 2005 - 2013 Elektrobit Automotive GmbH
 * All rights exclusively reserved for Elektrobit Automotive GmbH,
 * unless expressly agreed to otherwise.
 */

/*==================[inclusions]=============================================*/

/*==================[macros]=================================================*/

/*------------------[Autosar vendor identification]--------------------------*/

/*------------------[AUTOSAR module identification]-------------------------*/

/*------------------[AUTOSAR release version identification]----------------*/

/*------------------[AUTOSAR module version identification]------------------*/

/*------------------[MemMap error checking]----------------------------------*/

/*------------------[MemMap extensions]--------------------------------------*/
#if 0

/*------------------[Start of a module]--------------------------------------*/

/*****************************************************************************
**                                 BFX                                      **
******************************************************************************/

/*
 * To be used for mapping code to application block, boot block,
 * external flash etc
 */
#elif defined (BFX_START_SEC_CODE)
   #undef      BFX_START_SEC_CODE
   #undef MEMMAP_ERROR
#elif defined (BFX_STOP_SEC_CODE)
   #undef      BFX_STOP_SEC_CODE
   #undef MEMMAP_ERROR


/*****************************************************************************
**                                 CANTRCV_17_6250GV33                      **
******************************************************************************/

/*
 * To be used for mapping code to application block, boot block,
 * external flash etc
 */
#elif defined (CANTRCV_17_6250GV33_START_SEC_CODE)
   #undef      CANTRCV_17_6250GV33_START_SEC_CODE
   #undef MEMMAP_ERROR
#elif defined (CANTRCV_17_6250GV33_STOP_SEC_CODE)
   #undef      CANTRCV_17_6250GV33_STOP_SEC_CODE
   #undef MEMMAP_ERROR


#elif defined (CANTRCV_17_6250GV33_START_SEC_VAR_NOINIT_8BIT)
   #undef      CANTRCV_17_6250GV33_START_SEC_VAR_NOINIT_8BIT
   #undef MEMMAP_ERROR
#elif defined (CANTRCV_17_6250GV33_STOP_SEC_VAR_NOINIT_8BIT)
   #undef      CANTRCV_17_6250GV33_STOP_SEC_VAR_NOINIT_8BIT
   #undef MEMMAP_ERROR


#elif defined (CANTRCV_17_6250GV33_START_SEC_VAR_NOINIT_16BIT)
   #undef      CANTRCV_17_6250GV33_START_SEC_VAR_NOINIT_16BIT
   #undef MEMMAP_ERROR
#elif defined (CANTRCV_17_6250GV33_STOP_SEC_VAR_NOINIT_16BIT)
   #undef      CANTRCV_17_6250GV33_STOP_SEC_VAR_NOINIT_16BIT
   #undef MEMMAP_ERROR


#elif defined (CANTRCV_17_6250GV33_START_SEC_VAR_NOINIT_32BIT)
   #undef      CANTRCV_17_6250GV33_START_SEC_VAR_NOINIT_32BIT
   #undef MEMMAP_ERROR
#elif defined (CANTRCV_17_6250GV33_STOP_SEC_VAR_NOINIT_32BIT)
   #undef      CANTRCV_17_6250GV33_STOP_SEC_VAR_NOINIT_32BIT
   #undef MEMMAP_ERROR


#elif defined (CANTRCV_17_6250GV33_START_SEC_VAR_NOINIT_UNSPECIFIED)
   #undef      CANTRCV_17_6250GV33_START_SEC_VAR_NOINIT_UNSPECIFIED
   #undef MEMMAP_ERROR
#elif defined (CANTRCV_17_6250GV33_STOP_SEC_VAR_NOINIT_UNSPECIFIED)
   #undef      CANTRCV_17_6250GV33_STOP_SEC_VAR_NOINIT_UNSPECIFIED
   #undef MEMMAP_ERROR


#elif defined (CANTRCV_17_6250GV33_START_SEC_VAR_POWER_ON_INIT_8BIT)
   #undef      CANTRCV_17_6250GV33_START_SEC_VAR_POWER_ON_INIT_8BIT
   #undef MEMMAP_ERROR
#elif defined (CANTRCV_17_6250GV33_STOP_SEC_VAR_POWER_ON_INIT_8BIT)
   #undef      CANTRCV_17_6250GV33_STOP_SEC_VAR_POWER_ON_INIT_8BIT
   #undef MEMMAP_ERROR


#elif defined (CANTRCV_17_6250GV33_START_SEC_VAR_POWER_ON_INIT_16BIT)
   #undef      CANTRCV_17_6250GV33_START_SEC_VAR_POWER_ON_INIT_16BIT
   #undef MEMMAP_ERROR
#elif defined (CANTRCV_17_6250GV33_STOP_SEC_VAR_POWER_ON_INIT_16BIT)
   #undef      CANTRCV_17_6250GV33_STOP_SEC_VAR_POWER_ON_INIT_16BIT
   #undef MEMMAP_ERROR


#elif defined (CANTRCV_17_6250GV33_START_SEC_VAR_POWER_ON_INIT_32BIT)
   #undef      CANTRCV_17_6250GV33_START_SEC_VAR_POWER_ON_INIT_32BIT
   #undef MEMMAP_ERROR
#elif defined (CANTRCV_17_6250GV33_STOP_SEC_VAR_POWER_ON_INIT_32BIT)
   #undef      CANTRCV_17_6250GV33_STOP_SEC_VAR_POWER_ON_INIT_32BIT
   #undef MEMMAP_ERROR


#elif defined (CANTRCV_17_6250GV33_START_SEC_VAR_POWER_ON_INIT_UNSPECIFIED)
   #undef      CANTRCV_17_6250GV33_START_SEC_VAR_POWER_ON_INIT_UNSPECIFIED
   #undef MEMMAP_ERROR
#elif defined (CANTRCV_17_6250GV33_STOP_SEC_VAR_POWER_ON_INIT_UNSPECIFIED)
   #undef      CANTRCV_17_6250GV33_STOP_SEC_VAR_POWER_ON_INIT_UNSPECIFIED
   #undef MEMMAP_ERROR


#elif defined (CANTRCV_17_6250GV33_START_SEC_VAR_FAST_8BIT)
   #undef      CANTRCV_17_6250GV33_START_SEC_VAR_FAST_8BIT
   #undef MEMMAP_ERROR
#elif defined (CANTRCV_17_6250GV33_STOP_SEC_VAR_FAST_8BIT)
   #undef      CANTRCV_17_6250GV33_STOP_SEC_VAR_FAST_8BIT
   #undef MEMMAP_ERROR


#elif defined (CANTRCV_17_6250GV33_START_SEC_VAR_FAST_16BIT)
   #undef      CANTRCV_17_6250GV33_START_SEC_VAR_FAST_16BIT
   #undef MEMMAP_ERROR
#elif defined (CANTRCV_17_6250GV33_STOP_SEC_VAR_FAST_16BIT)
   #undef      CANTRCV_17_6250GV33_STOP_SEC_VAR_FAST_16BIT
   #undef MEMMAP_ERROR


#elif defined (CANTRCV_17_6250GV33_START_SEC_VAR_FAST_32BIT)
   #undef      CANTRCV_17_6250GV33_START_SEC_VAR_FAST_32BIT
   #undef MEMMAP_ERROR
#elif defined (CANTRCV_17_6250GV33_STOP_SEC_VAR_FAST_32BIT)
   #undef      CANTRCV_17_6250GV33_STOP_SEC_VAR_FAST_32BIT
   #undef MEMMAP_ERROR


#elif defined (CANTRCV_17_6250GV33_START_SEC_VAR_FAST_UNSPECIFIED)
   #undef      CANTRCV_17_6250GV33_START_SEC_VAR_FAST_UNSPECIFIED
   #undef MEMMAP_ERROR
#elif defined (CANTRCV_17_6250GV33_STOP_SEC_VAR_FAST_UNSPECIFIED)
   #undef      CANTRCV_17_6250GV33_STOP_SEC_VAR_FAST_UNSPECIFIED
   #undef MEMMAP_ERROR


#elif defined (CANTRCV_17_6250GV33_START_SEC_VAR_8BIT)
   #undef      CANTRCV_17_6250GV33_START_SEC_VAR_8BIT
   #undef MEMMAP_ERROR
#elif defined (CANTRCV_17_6250GV33_STOP_SEC_VAR_8BIT)
   #undef      CANTRCV_17_6250GV33_STOP_SEC_VAR_8BIT
   #undef MEMMAP_ERROR


#elif defined (CANTRCV_17_6250GV33_START_SEC_VAR_16BIT)
   #undef      CANTRCV_17_6250GV33_START_SEC_VAR_16BIT
   #undef MEMMAP_ERROR
#elif defined (CANTRCV_17_6250GV33_STOP_SEC_VAR_16BIT)
   #undef      CANTRCV_17_6250GV33_STOP_SEC_VAR_16BIT
   #undef MEMMAP_ERROR


#elif defined (CANTRCV_17_6250GV33_START_SEC_VAR_32BIT)
   #undef      CANTRCV_17_6250GV33_START_SEC_VAR_32BIT
   #undef MEMMAP_ERROR
#elif defined (CANTRCV_17_6250GV33_STOP_SEC_VAR_32BIT)
   #undef      CANTRCV_17_6250GV33_STOP_SEC_VAR_32BIT
   #undef MEMMAP_ERROR


#elif defined (CANTRCV_17_6250GV33_START_SEC_VAR_UNSPECIFIED)
   #undef      CANTRCV_17_6250GV33_START_SEC_VAR_UNSPECIFIED
   #undef MEMMAP_ERROR
#elif defined (CANTRCV_17_6250GV33_STOP_SEC_VAR_UNSPECIFIED)
   #undef      CANTRCV_17_6250GV33_STOP_SEC_VAR_UNSPECIFIED
   #undef MEMMAP_ERROR


#elif defined (CANTRCV_17_6250GV33_START_SEC_CONST_8BIT)
   #undef      CANTRCV_17_6250GV33_START_SEC_CONST_8BIT
   #undef MEMMAP_ERROR
#elif defined (CANTRCV_17_6250GV33_STOP_SEC_CONST_8BIT)
   #undef      CANTRCV_17_6250GV33_STOP_SEC_CONST_8BIT
   #undef MEMMAP_ERROR


#elif defined (CANTRCV_17_6250GV33_START_SEC_CONST_16BIT)
   #undef      CANTRCV_17_6250GV33_START_SEC_CONST_16BIT
   #undef MEMMAP_ERROR
#elif defined (CANTRCV_17_6250GV33_STOP_SEC_CONST_16BIT)
   #undef      CANTRCV_17_6250GV33_STOP_SEC_CONST_16BIT
   #undef MEMMAP_ERROR


#elif defined (CANTRCV_17_6250GV33_START_SEC_CONST_32BIT)
   #undef      CANTRCV_17_6250GV33_START_SEC_CONST_32BIT
   #undef MEMMAP_ERROR
#elif defined (CANTRCV_17_6250GV33_STOP_SEC_CONST_32BIT)
   #undef      CANTRCV_17_6250GV33_STOP_SEC_CONST_32BIT
   #undef MEMMAP_ERROR


#elif defined (CANTRCV_17_6250GV33_START_SEC_CONST_UNSPECIFIED)
   #undef      CANTRCV_17_6250GV33_START_SEC_CONST_UNSPECIFIED
   #undef MEMMAP_ERROR
#elif defined (CANTRCV_17_6250GV33_STOP_SEC_CONST_UNSPECIFIED)
   #undef      CANTRCV_17_6250GV33_STOP_SEC_CONST_UNSPECIFIED
   #undef MEMMAP_ERROR

/*****************************************************************************
**                                 CANTRCV_17_6251G                                      **
******************************************************************************/

/*
 * To be used for mapping code to application block, boot block,
 * external flash etc
 */
#elif defined (CANTRCV_17_6251G_START_SEC_CODE)
   #undef      CANTRCV_17_6251G_START_SEC_CODE
   #undef MEMMAP_ERROR
#elif defined (CANTRCV_17_6251G_STOP_SEC_CODE)
   #undef      CANTRCV_17_6251G_STOP_SEC_CODE
   #undef MEMMAP_ERROR


#elif defined (CANTRCV_17_6251G_START_SEC_VAR_NOINIT_8BIT)
   #undef      CANTRCV_17_6251G_START_SEC_VAR_NOINIT_8BIT
   #undef MEMMAP_ERROR
#elif defined (CANTRCV_17_6251G_STOP_SEC_VAR_NOINIT_8BIT)
   #undef      CANTRCV_17_6251G_STOP_SEC_VAR_NOINIT_8BIT
   #undef MEMMAP_ERROR


#elif defined (CANTRCV_17_6251G_START_SEC_VAR_NOINIT_16BIT)
   #undef      CANTRCV_17_6251G_START_SEC_VAR_NOINIT_16BIT
   #undef MEMMAP_ERROR
#elif defined (CANTRCV_17_6251G_STOP_SEC_VAR_NOINIT_16BIT)
   #undef      CANTRCV_17_6251G_STOP_SEC_VAR_NOINIT_16BIT
   #undef MEMMAP_ERROR


#elif defined (CANTRCV_17_6251G_START_SEC_VAR_NOINIT_32BIT)
   #undef      CANTRCV_17_6251G_START_SEC_VAR_NOINIT_32BIT
   #undef MEMMAP_ERROR
#elif defined (CANTRCV_17_6251G_STOP_SEC_VAR_NOINIT_32BIT)
   #undef      CANTRCV_17_6251G_STOP_SEC_VAR_NOINIT_32BIT
   #undef MEMMAP_ERROR


#elif defined (CANTRCV_17_6251G_START_SEC_VAR_NOINIT_UNSPECIFIED)
   #undef      CANTRCV_17_6251G_START_SEC_VAR_NOINIT_UNSPECIFIED
   #undef MEMMAP_ERROR
#elif defined (CANTRCV_17_6251G_STOP_SEC_VAR_NOINIT_UNSPECIFIED)
   #undef      CANTRCV_17_6251G_STOP_SEC_VAR_NOINIT_UNSPECIFIED
   #undef MEMMAP_ERROR


#elif defined (CANTRCV_17_6251G_START_SEC_VAR_POWER_ON_INIT_8BIT)
   #undef      CANTRCV_17_6251G_START_SEC_VAR_POWER_ON_INIT_8BIT
   #undef MEMMAP_ERROR
#elif defined (CANTRCV_17_6251G_STOP_SEC_VAR_POWER_ON_INIT_8BIT)
   #undef      CANTRCV_17_6251G_STOP_SEC_VAR_POWER_ON_INIT_8BIT
   #undef MEMMAP_ERROR


#elif defined (CANTRCV_17_6251G_START_SEC_VAR_POWER_ON_INIT_16BIT)
   #undef      CANTRCV_17_6251G_START_SEC_VAR_POWER_ON_INIT_16BIT
   #undef MEMMAP_ERROR
#elif defined (CANTRCV_17_6251G_STOP_SEC_VAR_POWER_ON_INIT_16BIT)
   #undef      CANTRCV_17_6251G_STOP_SEC_VAR_POWER_ON_INIT_16BIT
   #undef MEMMAP_ERROR


#elif defined (CANTRCV_17_6251G_START_SEC_VAR_POWER_ON_INIT_32BIT)
   #undef      CANTRCV_17_6251G_START_SEC_VAR_POWER_ON_INIT_32BIT
   #undef MEMMAP_ERROR
#elif defined (CANTRCV_17_6251G_STOP_SEC_VAR_POWER_ON_INIT_32BIT)
   #undef      CANTRCV_17_6251G_STOP_SEC_VAR_POWER_ON_INIT_32BIT
   #undef MEMMAP_ERROR


#elif defined (CANTRCV_17_6251G_START_SEC_VAR_POWER_ON_INIT_UNSPECIFIED)
   #undef      CANTRCV_17_6251G_START_SEC_VAR_POWER_ON_INIT_UNSPECIFIED
   #undef MEMMAP_ERROR
#elif defined (CANTRCV_17_6251G_STOP_SEC_VAR_POWER_ON_INIT_UNSPECIFIED)
   #undef      CANTRCV_17_6251G_STOP_SEC_VAR_POWER_ON_INIT_UNSPECIFIED
   #undef MEMMAP_ERROR


#elif defined (CANTRCV_17_6251G_START_SEC_VAR_FAST_8BIT)
   #undef      CANTRCV_17_6251G_START_SEC_VAR_FAST_8BIT
   #undef MEMMAP_ERROR
#elif defined (CANTRCV_17_6251G_STOP_SEC_VAR_FAST_8BIT)
   #undef      CANTRCV_17_6251G_STOP_SEC_VAR_FAST_8BIT
   #undef MEMMAP_ERROR


#elif defined (CANTRCV_17_6251G_START_SEC_VAR_FAST_16BIT)
   #undef      CANTRCV_17_6251G_START_SEC_VAR_FAST_16BIT
   #undef MEMMAP_ERROR
#elif defined (CANTRCV_17_6251G_STOP_SEC_VAR_FAST_16BIT)
   #undef      CANTRCV_17_6251G_STOP_SEC_VAR_FAST_16BIT
   #undef MEMMAP_ERROR


#elif defined (CANTRCV_17_6251G_START_SEC_VAR_FAST_32BIT)
   #undef      CANTRCV_17_6251G_START_SEC_VAR_FAST_32BIT
   #undef MEMMAP_ERROR
#elif defined (CANTRCV_17_6251G_STOP_SEC_VAR_FAST_32BIT)
   #undef      CANTRCV_17_6251G_STOP_SEC_VAR_FAST_32BIT
   #undef MEMMAP_ERROR


#elif defined (CANTRCV_17_6251G_START_SEC_VAR_FAST_UNSPECIFIED)
   #undef      CANTRCV_17_6251G_START_SEC_VAR_FAST_UNSPECIFIED
   #undef MEMMAP_ERROR
#elif defined (CANTRCV_17_6251G_STOP_SEC_VAR_FAST_UNSPECIFIED)
   #undef      CANTRCV_17_6251G_STOP_SEC_VAR_FAST_UNSPECIFIED
   #undef MEMMAP_ERROR


#elif defined (CANTRCV_17_6251G_START_SEC_VAR_8BIT)
   #undef      CANTRCV_17_6251G_START_SEC_VAR_8BIT
   #undef MEMMAP_ERROR
#elif defined (CANTRCV_17_6251G_STOP_SEC_VAR_8BIT)
   #undef      CANTRCV_17_6251G_STOP_SEC_VAR_8BIT
   #undef MEMMAP_ERROR


#elif defined (CANTRCV_17_6251G_START_SEC_VAR_16BIT)
   #undef      CANTRCV_17_6251G_START_SEC_VAR_16BIT
   #undef MEMMAP_ERROR
#elif defined (CANTRCV_17_6251G_STOP_SEC_VAR_16BIT)
   #undef      CANTRCV_17_6251G_STOP_SEC_VAR_16BIT
   #undef MEMMAP_ERROR


#elif defined (CANTRCV_17_6251G_START_SEC_VAR_32BIT)
   #undef      CANTRCV_17_6251G_START_SEC_VAR_32BIT
   #undef MEMMAP_ERROR
#elif defined (CANTRCV_17_6251G_STOP_SEC_VAR_32BIT)
   #undef      CANTRCV_17_6251G_STOP_SEC_VAR_32BIT
   #undef MEMMAP_ERROR


#elif defined (CANTRCV_17_6251G_START_SEC_VAR_UNSPECIFIED)
   #undef      CANTRCV_17_6251G_START_SEC_VAR_UNSPECIFIED
   #undef MEMMAP_ERROR
#elif defined (CANTRCV_17_6251G_STOP_SEC_VAR_UNSPECIFIED)
   #undef      CANTRCV_17_6251G_STOP_SEC_VAR_UNSPECIFIED
   #undef MEMMAP_ERROR


#elif defined (CANTRCV_17_6251G_START_SEC_CONST_8BIT)
   #undef      CANTRCV_17_6251G_START_SEC_CONST_8BIT
   #undef MEMMAP_ERROR
#elif defined (CANTRCV_17_6251G_STOP_SEC_CONST_8BIT)
   #undef      CANTRCV_17_6251G_STOP_SEC_CONST_8BIT
   #undef MEMMAP_ERROR


#elif defined (CANTRCV_17_6251G_START_SEC_CONST_16BIT)
   #undef      CANTRCV_17_6251G_START_SEC_CONST_16BIT
   #undef MEMMAP_ERROR
#elif defined (CANTRCV_17_6251G_STOP_SEC_CONST_16BIT)
   #undef      CANTRCV_17_6251G_STOP_SEC_CONST_16BIT
   #undef MEMMAP_ERROR


#elif defined (CANTRCV_17_6251G_START_SEC_CONST_32BIT)
   #undef      CANTRCV_17_6251G_START_SEC_CONST_32BIT
   #undef MEMMAP_ERROR
#elif defined (CANTRCV_17_6251G_STOP_SEC_CONST_32BIT)
   #undef      CANTRCV_17_6251G_STOP_SEC_CONST_32BIT
   #undef MEMMAP_ERROR


#elif defined (CANTRCV_17_6251G_START_SEC_CONST_UNSPECIFIED)
   #undef      CANTRCV_17_6251G_START_SEC_CONST_UNSPECIFIED
   #undef MEMMAP_ERROR
#elif defined (CANTRCV_17_6251G_STOP_SEC_CONST_UNSPECIFIED)
   #undef      CANTRCV_17_6251G_STOP_SEC_CONST_UNSPECIFIED
   #undef MEMMAP_ERROR

/*****************************************************************************
**                                 DMA                                      **
******************************************************************************/

/*
 * To be used for mapping code to application block, boot block,
 * external flash etc
 */
#elif defined (DMA_START_SEC_CODE)
   #undef      DMA_START_SEC_CODE
   #undef MEMMAP_ERROR
#elif defined (DMA_STOP_SEC_CODE)
   #undef      DMA_STOP_SEC_CODE
   #undef MEMMAP_ERROR


#elif defined (DMA_START_SEC_VAR_NOINIT_8BIT)
   #undef      DMA_START_SEC_VAR_NOINIT_8BIT
   #undef MEMMAP_ERROR
#elif defined (DMA_STOP_SEC_VAR_NOINIT_8BIT)
   #undef      DMA_STOP_SEC_VAR_NOINIT_8BIT
   #undef MEMMAP_ERROR


#elif defined (DMA_START_SEC_VAR_NOINIT_16BIT)
   #undef      DMA_START_SEC_VAR_NOINIT_16BIT
   #undef MEMMAP_ERROR
#elif defined (DMA_STOP_SEC_VAR_NOINIT_16BIT)
   #undef      DMA_STOP_SEC_VAR_NOINIT_16BIT
   #undef MEMMAP_ERROR


#elif defined (DMA_START_SEC_VAR_NOINIT_32BIT)
   #undef      DMA_START_SEC_VAR_NOINIT_32BIT
   #undef MEMMAP_ERROR
#elif defined (DMA_STOP_SEC_VAR_NOINIT_32BIT)
   #undef      DMA_STOP_SEC_VAR_NOINIT_32BIT
   #undef MEMMAP_ERROR


#elif defined (DMA_START_SEC_VAR_NOINIT_UNSPECIFIED)
   #undef      DMA_START_SEC_VAR_NOINIT_UNSPECIFIED
   #undef MEMMAP_ERROR
#elif defined (DMA_STOP_SEC_VAR_NOINIT_UNSPECIFIED)
   #undef      DMA_STOP_SEC_VAR_NOINIT_UNSPECIFIED
   #undef MEMMAP_ERROR


#elif defined (DMA_START_SEC_VAR_POWER_ON_INIT_8BIT)
   #undef      DMA_START_SEC_VAR_POWER_ON_INIT_8BIT
   #undef MEMMAP_ERROR
#elif defined (DMA_STOP_SEC_VAR_POWER_ON_INIT_8BIT)
   #undef      DMA_STOP_SEC_VAR_POWER_ON_INIT_8BIT
   #undef MEMMAP_ERROR


#elif defined (DMA_START_SEC_VAR_POWER_ON_INIT_16BIT)
   #undef      DMA_START_SEC_VAR_POWER_ON_INIT_16BIT
   #undef MEMMAP_ERROR
#elif defined (DMA_STOP_SEC_VAR_POWER_ON_INIT_16BIT)
   #undef      DMA_STOP_SEC_VAR_POWER_ON_INIT_16BIT
   #undef MEMMAP_ERROR


#elif defined (DMA_START_SEC_VAR_POWER_ON_INIT_32BIT)
   #undef      DMA_START_SEC_VAR_POWER_ON_INIT_32BIT
   #undef MEMMAP_ERROR
#elif defined (DMA_STOP_SEC_VAR_POWER_ON_INIT_32BIT)
   #undef      DMA_STOP_SEC_VAR_POWER_ON_INIT_32BIT
   #undef MEMMAP_ERROR


#elif defined (DMA_START_SEC_VAR_POWER_ON_INIT_UNSPECIFIED)
   #undef      DMA_START_SEC_VAR_POWER_ON_INIT_UNSPECIFIED
   #undef MEMMAP_ERROR
#elif defined (DMA_STOP_SEC_VAR_POWER_ON_INIT_UNSPECIFIED)
   #undef      DMA_STOP_SEC_VAR_POWER_ON_INIT_UNSPECIFIED
   #undef MEMMAP_ERROR


#elif defined (DMA_START_SEC_VAR_FAST_8BIT)
   #undef      DMA_START_SEC_VAR_FAST_8BIT
   #undef MEMMAP_ERROR
#elif defined (DMA_STOP_SEC_VAR_FAST_8BIT)
   #undef      DMA_STOP_SEC_VAR_FAST_8BIT
   #undef MEMMAP_ERROR


#elif defined (DMA_START_SEC_VAR_FAST_16BIT)
   #undef      DMA_START_SEC_VAR_FAST_16BIT
   #undef MEMMAP_ERROR
#elif defined (DMA_STOP_SEC_VAR_FAST_16BIT)
   #undef      DMA_STOP_SEC_VAR_FAST_16BIT
   #undef MEMMAP_ERROR


#elif defined (DMA_START_SEC_VAR_FAST_32BIT)
   #undef      DMA_START_SEC_VAR_FAST_32BIT
   #undef MEMMAP_ERROR
#elif defined (DMA_STOP_SEC_VAR_FAST_32BIT)
   #undef      DMA_STOP_SEC_VAR_FAST_32BIT
   #undef MEMMAP_ERROR


#elif defined (DMA_START_SEC_VAR_FAST_UNSPECIFIED)
   #undef      DMA_START_SEC_VAR_FAST_UNSPECIFIED
   #undef MEMMAP_ERROR
#elif defined (DMA_STOP_SEC_VAR_FAST_UNSPECIFIED)
   #undef      DMA_STOP_SEC_VAR_FAST_UNSPECIFIED
   #undef MEMMAP_ERROR


#elif defined (DMA_START_SEC_VAR_8BIT)
   #undef      DMA_START_SEC_VAR_8BIT
   #undef MEMMAP_ERROR
#elif defined (DMA_STOP_SEC_VAR_8BIT)
   #undef      DMA_STOP_SEC_VAR_8BIT
   #undef MEMMAP_ERROR


#elif defined (DMA_START_SEC_VAR_16BIT)
   #undef      DMA_START_SEC_VAR_16BIT
   #undef MEMMAP_ERROR
#elif defined (DMA_STOP_SEC_VAR_16BIT)
   #undef      DMA_STOP_SEC_VAR_16BIT
   #undef MEMMAP_ERROR


#elif defined (DMA_START_SEC_VAR_32BIT)
   #undef      DMA_START_SEC_VAR_32BIT
   #undef MEMMAP_ERROR
#elif defined (DMA_STOP_SEC_VAR_32BIT)
   #undef      DMA_STOP_SEC_VAR_32BIT
   #undef MEMMAP_ERROR


#elif defined (DMA_START_SEC_VAR_UNSPECIFIED)
   #undef      DMA_START_SEC_VAR_UNSPECIFIED
   #undef MEMMAP_ERROR
#elif defined (DMA_STOP_SEC_VAR_UNSPECIFIED)
   #undef      DMA_STOP_SEC_VAR_UNSPECIFIED
   #undef MEMMAP_ERROR


#elif defined (DMA_START_SEC_CONST_8BIT)
   #undef      DMA_START_SEC_CONST_8BIT
   #undef MEMMAP_ERROR
#elif defined (DMA_STOP_SEC_CONST_8BIT)
   #undef      DMA_STOP_SEC_CONST_8BIT
   #undef MEMMAP_ERROR


#elif defined (DMA_START_SEC_CONST_16BIT)
   #undef      DMA_START_SEC_CONST_16BIT
   #undef MEMMAP_ERROR
#elif defined (DMA_STOP_SEC_CONST_16BIT)
   #undef      DMA_STOP_SEC_CONST_16BIT
   #undef MEMMAP_ERROR


#elif defined (DMA_START_SEC_CONST_32BIT)
   #undef      DMA_START_SEC_CONST_32BIT
   #undef MEMMAP_ERROR
#elif defined (DMA_STOP_SEC_CONST_32BIT)
   #undef      DMA_STOP_SEC_CONST_32BIT
   #undef MEMMAP_ERROR


#elif defined (DMA_START_SEC_CONST_UNSPECIFIED)
   #undef      DMA_START_SEC_CONST_UNSPECIFIED
   #undef MEMMAP_ERROR
#elif defined (DMA_STOP_SEC_CONST_UNSPECIFIED)
   #undef      DMA_STOP_SEC_CONST_UNSPECIFIED
   #undef MEMMAP_ERROR

/*****************************************************************************
**                                 FLSLOADER                                      **
******************************************************************************/

/*
 * To be used for mapping code to application block, boot block,
 * external flash etc
 */
#elif defined (FLSLOADER_START_SEC_CODE)
   #undef      FLSLOADER_START_SEC_CODE
   #undef MEMMAP_ERROR
#elif defined (FLSLOADER_STOP_SEC_CODE)
   #undef      FLSLOADER_STOP_SEC_CODE
   #undef MEMMAP_ERROR


#elif defined (FLSLOADER_START_SEC_WRITE_CODE)
   #undef      FLSLOADER_START_SEC_WRITE_CODE
   #undef MEMMAP_ERROR
#elif defined (FLSLOADER_STOP_SEC_WRITE_CODE)
   #undef      FLSLOADER_STOP_SEC_WRITE_CODE
   #undef MEMMAP_ERROR


#elif defined (FLSLOADER_START_SEC_ERASE_CODE)
   #undef      FLSLOADER_START_SEC_ERASE_CODE
   #undef MEMMAP_ERROR
#elif defined (FLSLOADER_STOP_SEC_ERASE_CODE)
   #undef      FLSLOADER_STOP_SEC_ERASE_CODE
   #undef MEMMAP_ERROR


#elif defined (FLSLOADER_START_SEC_VAR_NOINIT_8BIT)
   #undef      FLSLOADER_START_SEC_VAR_NOINIT_8BIT
   #undef MEMMAP_ERROR
#elif defined (FLSLOADER_STOP_SEC_VAR_NOINIT_8BIT)
   #undef      FLSLOADER_STOP_SEC_VAR_NOINIT_8BIT
   #undef MEMMAP_ERROR


#elif defined (FLSLOADER_START_SEC_VAR_NOINIT_16BIT)
   #undef      FLSLOADER_START_SEC_VAR_NOINIT_16BIT
   #undef MEMMAP_ERROR
#elif defined (FLSLOADER_STOP_SEC_VAR_NOINIT_16BIT)
   #undef      FLSLOADER_STOP_SEC_VAR_NOINIT_16BIT
   #undef MEMMAP_ERROR


#elif defined (FLSLOADER_START_SEC_VAR_NOINIT_32BIT)
   #undef      FLSLOADER_START_SEC_VAR_NOINIT_32BIT
   #undef MEMMAP_ERROR
#elif defined (FLSLOADER_STOP_SEC_VAR_NOINIT_32BIT)
   #undef      FLSLOADER_STOP_SEC_VAR_NOINIT_32BIT
   #undef MEMMAP_ERROR


#elif defined (FLSLOADER_START_SEC_VAR_NOINIT_UNSPECIFIED)
   #undef      FLSLOADER_START_SEC_VAR_NOINIT_UNSPECIFIED
   #undef MEMMAP_ERROR
#elif defined (FLSLOADER_STOP_SEC_VAR_NOINIT_UNSPECIFIED)
   #undef      FLSLOADER_STOP_SEC_VAR_NOINIT_UNSPECIFIED
   #undef MEMMAP_ERROR


#elif defined (FLSLOADER_START_SEC_VAR_POWER_ON_INIT_8BIT)
   #undef      FLSLOADER_START_SEC_VAR_POWER_ON_INIT_8BIT
   #undef MEMMAP_ERROR
#elif defined (FLSLOADER_STOP_SEC_VAR_POWER_ON_INIT_8BIT)
   #undef      FLSLOADER_STOP_SEC_VAR_POWER_ON_INIT_8BIT
   #undef MEMMAP_ERROR


#elif defined (FLSLOADER_START_SEC_VAR_POWER_ON_INIT_16BIT)
   #undef      FLSLOADER_START_SEC_VAR_POWER_ON_INIT_16BIT
   #undef MEMMAP_ERROR
#elif defined (FLSLOADER_STOP_SEC_VAR_POWER_ON_INIT_16BIT)
   #undef      FLSLOADER_STOP_SEC_VAR_POWER_ON_INIT_16BIT
   #undef MEMMAP_ERROR


#elif defined (FLSLOADER_START_SEC_VAR_POWER_ON_INIT_32BIT)
   #undef      FLSLOADER_START_SEC_VAR_POWER_ON_INIT_32BIT
   #undef MEMMAP_ERROR
#elif defined (FLSLOADER_STOP_SEC_VAR_POWER_ON_INIT_32BIT)
   #undef      FLSLOADER_STOP_SEC_VAR_POWER_ON_INIT_32BIT
   #undef MEMMAP_ERROR


#elif defined (FLSLOADER_START_SEC_VAR_POWER_ON_INIT_UNSPECIFIED)
   #undef      FLSLOADER_START_SEC_VAR_POWER_ON_INIT_UNSPECIFIED
   #undef MEMMAP_ERROR
#elif defined (FLSLOADER_STOP_SEC_VAR_POWER_ON_INIT_UNSPECIFIED)
   #undef      FLSLOADER_STOP_SEC_VAR_POWER_ON_INIT_UNSPECIFIED
   #undef MEMMAP_ERROR


#elif defined (FLSLOADER_START_SEC_VAR_FAST_8BIT)
   #undef      FLSLOADER_START_SEC_VAR_FAST_8BIT
   #undef MEMMAP_ERROR
#elif defined (FLSLOADER_STOP_SEC_VAR_FAST_8BIT)
   #undef      FLSLOADER_STOP_SEC_VAR_FAST_8BIT
   #undef MEMMAP_ERROR


#elif defined (FLSLOADER_START_SEC_VAR_FAST_16BIT)
   #undef      FLSLOADER_START_SEC_VAR_FAST_16BIT
   #undef MEMMAP_ERROR
#elif defined (FLSLOADER_STOP_SEC_VAR_FAST_16BIT)
   #undef      FLSLOADER_STOP_SEC_VAR_FAST_16BIT
   #undef MEMMAP_ERROR


#elif defined (FLSLOADER_START_SEC_VAR_FAST_32BIT)
   #undef      FLSLOADER_START_SEC_VAR_FAST_32BIT
   #undef MEMMAP_ERROR
#elif defined (FLSLOADER_STOP_SEC_VAR_FAST_32BIT)
   #undef      FLSLOADER_STOP_SEC_VAR_FAST_32BIT
   #undef MEMMAP_ERROR


#elif defined (FLSLOADER_START_SEC_VAR_FAST_UNSPECIFIED)
   #undef      FLSLOADER_START_SEC_VAR_FAST_UNSPECIFIED
   #undef MEMMAP_ERROR
#elif defined (FLSLOADER_STOP_SEC_VAR_FAST_UNSPECIFIED)
   #undef      FLSLOADER_STOP_SEC_VAR_FAST_UNSPECIFIED
   #undef MEMMAP_ERROR


#elif defined (FLSLOADER_START_SEC_VAR_8BIT)
   #undef      FLSLOADER_START_SEC_VAR_8BIT
   #undef MEMMAP_ERROR
#elif defined (FLSLOADER_STOP_SEC_VAR_8BIT)
   #undef      FLSLOADER_STOP_SEC_VAR_8BIT
   #undef MEMMAP_ERROR


#elif defined (FLSLOADER_START_SEC_VAR_16BIT)
   #undef      FLSLOADER_START_SEC_VAR_16BIT
   #undef MEMMAP_ERROR
#elif defined (FLSLOADER_STOP_SEC_VAR_16BIT)
   #undef      FLSLOADER_STOP_SEC_VAR_16BIT
   #undef MEMMAP_ERROR


#elif defined (FLSLOADER_START_SEC_VAR_32BIT)
   #undef      FLSLOADER_START_SEC_VAR_32BIT
   #undef MEMMAP_ERROR
#elif defined (FLSLOADER_STOP_SEC_VAR_32BIT)
   #undef      FLSLOADER_STOP_SEC_VAR_32BIT
   #undef MEMMAP_ERROR


#elif defined (FLSLOADER_START_SEC_VAR_UNSPECIFIED)
   #undef      FLSLOADER_START_SEC_VAR_UNSPECIFIED
   #undef MEMMAP_ERROR
#elif defined (FLSLOADER_STOP_SEC_VAR_UNSPECIFIED)
   #undef      FLSLOADER_STOP_SEC_VAR_UNSPECIFIED
   #undef MEMMAP_ERROR


#elif defined (FLSLOADER_START_SEC_CONST_8BIT)
   #undef      FLSLOADER_START_SEC_CONST_8BIT
   #undef MEMMAP_ERROR
#elif defined (FLSLOADER_STOP_SEC_CONST_8BIT)
   #undef      FLSLOADER_STOP_SEC_CONST_8BIT
   #undef MEMMAP_ERROR


#elif defined (FLSLOADER_START_SEC_CONST_16BIT)
   #undef      FLSLOADER_START_SEC_CONST_16BIT
   #undef MEMMAP_ERROR
#elif defined (FLSLOADER_STOP_SEC_CONST_16BIT)
   #undef      FLSLOADER_STOP_SEC_CONST_16BIT
   #undef MEMMAP_ERROR


#elif defined (FLSLOADER_START_SEC_CONST_32BIT)
   #undef      FLSLOADER_START_SEC_CONST_32BIT
   #undef MEMMAP_ERROR
#elif defined (FLSLOADER_STOP_SEC_CONST_32BIT)
   #undef      FLSLOADER_STOP_SEC_CONST_32BIT
   #undef MEMMAP_ERROR


#elif defined (FLSLOADER_START_SEC_CONST_UNSPECIFIED)
   #undef      FLSLOADER_START_SEC_CONST_UNSPECIFIED
   #undef MEMMAP_ERROR
#elif defined (FLSLOADER_STOP_SEC_CONST_UNSPECIFIED)
   #undef      FLSLOADER_STOP_SEC_CONST_UNSPECIFIED
   #undef MEMMAP_ERROR

/*****************************************************************************
**                                 IRQ                                      **
******************************************************************************/

/*
 * To be used for mapping code to application block, boot block,
 * external flash etc
 */
#elif defined (IRQ_START_SEC_CODE)
   #undef      IRQ_START_SEC_CODE
   #undef MEMMAP_ERROR
#elif defined (IRQ_STOP_SEC_CODE)
   #undef      IRQ_STOP_SEC_CODE
   #undef MEMMAP_ERROR


#elif defined (IRQ_START_SEC_VAR_NOINIT_8BIT)
   #undef      IRQ_START_SEC_VAR_NOINIT_8BIT
   #undef MEMMAP_ERROR
#elif defined (IRQ_STOP_SEC_VAR_NOINIT_8BIT)
   #undef      IRQ_STOP_SEC_VAR_NOINIT_8BIT
   #undef MEMMAP_ERROR


#elif defined (IRQ_START_SEC_VAR_NOINIT_16BIT)
   #undef      IRQ_START_SEC_VAR_NOINIT_16BIT
   #undef MEMMAP_ERROR
#elif defined (IRQ_STOP_SEC_VAR_NOINIT_16BIT)
   #undef      IRQ_STOP_SEC_VAR_NOINIT_16BIT
   #undef MEMMAP_ERROR


#elif defined (IRQ_START_SEC_VAR_NOINIT_32BIT)
   #undef      IRQ_START_SEC_VAR_NOINIT_32BIT
   #undef MEMMAP_ERROR
#elif defined (IRQ_STOP_SEC_VAR_NOINIT_32BIT)
   #undef      IRQ_STOP_SEC_VAR_NOINIT_32BIT
   #undef MEMMAP_ERROR


#elif defined (IRQ_START_SEC_VAR_NOINIT_UNSPECIFIED)
   #undef      IRQ_START_SEC_VAR_NOINIT_UNSPECIFIED
   #undef MEMMAP_ERROR
#elif defined (IRQ_STOP_SEC_VAR_NOINIT_UNSPECIFIED)
   #undef      IRQ_STOP_SEC_VAR_NOINIT_UNSPECIFIED
   #undef MEMMAP_ERROR


#elif defined (IRQ_START_SEC_VAR_POWER_ON_INIT_8BIT)
   #undef      IRQ_START_SEC_VAR_POWER_ON_INIT_8BIT
   #undef MEMMAP_ERROR
#elif defined (IRQ_STOP_SEC_VAR_POWER_ON_INIT_8BIT)
   #undef      IRQ_STOP_SEC_VAR_POWER_ON_INIT_8BIT
   #undef MEMMAP_ERROR


#elif defined (IRQ_START_SEC_VAR_POWER_ON_INIT_16BIT)
   #undef      IRQ_START_SEC_VAR_POWER_ON_INIT_16BIT
   #undef MEMMAP_ERROR
#elif defined (IRQ_STOP_SEC_VAR_POWER_ON_INIT_16BIT)
   #undef      IRQ_STOP_SEC_VAR_POWER_ON_INIT_16BIT
   #undef MEMMAP_ERROR


#elif defined (IRQ_START_SEC_VAR_POWER_ON_INIT_32BIT)
   #undef      IRQ_START_SEC_VAR_POWER_ON_INIT_32BIT
   #undef MEMMAP_ERROR
#elif defined (IRQ_STOP_SEC_VAR_POWER_ON_INIT_32BIT)
   #undef      IRQ_STOP_SEC_VAR_POWER_ON_INIT_32BIT
   #undef MEMMAP_ERROR


#elif defined (IRQ_START_SEC_VAR_POWER_ON_INIT_UNSPECIFIED)
   #undef      IRQ_START_SEC_VAR_POWER_ON_INIT_UNSPECIFIED
   #undef MEMMAP_ERROR
#elif defined (IRQ_STOP_SEC_VAR_POWER_ON_INIT_UNSPECIFIED)
   #undef      IRQ_STOP_SEC_VAR_POWER_ON_INIT_UNSPECIFIED
   #undef MEMMAP_ERROR


#elif defined (IRQ_START_SEC_VAR_FAST_8BIT)
   #undef      IRQ_START_SEC_VAR_FAST_8BIT
   #undef MEMMAP_ERROR
#elif defined (IRQ_STOP_SEC_VAR_FAST_8BIT)
   #undef      IRQ_STOP_SEC_VAR_FAST_8BIT
   #undef MEMMAP_ERROR


#elif defined (IRQ_START_SEC_VAR_FAST_16BIT)
   #undef      IRQ_START_SEC_VAR_FAST_16BIT
   #undef MEMMAP_ERROR
#elif defined (IRQ_STOP_SEC_VAR_FAST_16BIT)
   #undef      IRQ_STOP_SEC_VAR_FAST_16BIT
   #undef MEMMAP_ERROR


#elif defined (IRQ_START_SEC_VAR_FAST_32BIT)
   #undef      IRQ_START_SEC_VAR_FAST_32BIT
   #undef MEMMAP_ERROR
#elif defined (IRQ_STOP_SEC_VAR_FAST_32BIT)
   #undef      IRQ_STOP_SEC_VAR_FAST_32BIT
   #undef MEMMAP_ERROR


#elif defined (IRQ_START_SEC_VAR_FAST_UNSPECIFIED)
   #undef      IRQ_START_SEC_VAR_FAST_UNSPECIFIED
   #undef MEMMAP_ERROR
#elif defined (IRQ_STOP_SEC_VAR_FAST_UNSPECIFIED)
   #undef      IRQ_STOP_SEC_VAR_FAST_UNSPECIFIED
   #undef MEMMAP_ERROR


#elif defined (IRQ_START_SEC_VAR_8BIT)
   #undef      IRQ_START_SEC_VAR_8BIT
   #undef MEMMAP_ERROR
#elif defined (IRQ_STOP_SEC_VAR_8BIT)
   #undef      IRQ_STOP_SEC_VAR_8BIT
   #undef MEMMAP_ERROR


#elif defined (IRQ_START_SEC_VAR_16BIT)
   #undef      IRQ_START_SEC_VAR_16BIT
   #undef MEMMAP_ERROR
#elif defined (IRQ_STOP_SEC_VAR_16BIT)
   #undef      IRQ_STOP_SEC_VAR_16BIT
   #undef MEMMAP_ERROR


#elif defined (IRQ_START_SEC_VAR_32BIT)
   #undef      IRQ_START_SEC_VAR_32BIT
   #undef MEMMAP_ERROR
#elif defined (IRQ_STOP_SEC_VAR_32BIT)
   #undef      IRQ_STOP_SEC_VAR_32BIT
   #undef MEMMAP_ERROR


#elif defined (IRQ_START_SEC_VAR_UNSPECIFIED)
   #undef      IRQ_START_SEC_VAR_UNSPECIFIED
   #undef MEMMAP_ERROR
#elif defined (IRQ_STOP_SEC_VAR_UNSPECIFIED)
   #undef      IRQ_STOP_SEC_VAR_UNSPECIFIED
   #undef MEMMAP_ERROR


#elif defined (IRQ_START_SEC_CONST_8BIT)
   #undef      IRQ_START_SEC_CONST_8BIT
   #undef MEMMAP_ERROR
#elif defined (IRQ_STOP_SEC_CONST_8BIT)
   #undef      IRQ_STOP_SEC_CONST_8BIT
   #undef MEMMAP_ERROR


#elif defined (IRQ_START_SEC_CONST_16BIT)
   #undef      IRQ_START_SEC_CONST_16BIT
   #undef MEMMAP_ERROR
#elif defined (IRQ_STOP_SEC_CONST_16BIT)
   #undef      IRQ_STOP_SEC_CONST_16BIT
   #undef MEMMAP_ERROR


#elif defined (IRQ_START_SEC_CONST_32BIT)
   #undef      IRQ_START_SEC_CONST_32BIT
   #undef MEMMAP_ERROR
#elif defined (IRQ_STOP_SEC_CONST_32BIT)
   #undef      IRQ_STOP_SEC_CONST_32BIT
   #undef MEMMAP_ERROR


#elif defined (IRQ_START_SEC_CONST_UNSPECIFIED)
   #undef      IRQ_START_SEC_CONST_UNSPECIFIED
   #undef MEMMAP_ERROR
#elif defined (IRQ_STOP_SEC_CONST_UNSPECIFIED)
   #undef      IRQ_STOP_SEC_CONST_UNSPECIFIED
   #undef MEMMAP_ERROR


/*****************************************************************************
**                                 SENT                                      **
******************************************************************************/

/*
 * To be used for mapping code to application block, boot block,
 * external flash etc
 */
#elif defined (SENT_START_SEC_POSTBUILDCFG)
   #undef      SENT_START_SEC_POSTBUILDCFG
   #undef MEMMAP_ERROR
#elif defined (SENT_STOP_SEC_POSTBUILDCFG)
   #undef      SENT_STOP_SEC_POSTBUILDCFG
   #undef MEMMAP_ERROR


#elif defined (SENT_START_SEC_VAR_32BIT)
   #undef      SENT_START_SEC_VAR_32BIT
   #undef MEMMAP_ERROR
#elif defined (SENT_STOP_SEC_VAR_32BIT)
   #undef      SENT_STOP_SEC_VAR_32BIT
   #undef MEMMAP_ERROR


#elif defined (SENT_START_SEC_VAR_8BIT)
   #undef      SENT_START_SEC_VAR_8BIT
   #undef MEMMAP_ERROR
#elif defined (SENT_STOP_SEC_VAR_8BIT)
   #undef      SENT_STOP_SEC_VAR_8BIT
   #undef MEMMAP_ERROR


#elif defined (SENT_START_SEC_CODE)
   #undef      SENT_START_SEC_CODE
   #undef MEMMAP_ERROR
#elif defined (SENT_STOP_SEC_CODE)
   #undef      SENT_STOP_SEC_CODE
   #undef MEMMAP_ERROR

/*****************************************************************************
**                                 IOM                                      **
******************************************************************************/

/*
 * To be used for mapping code to application block, boot block,
 * external flash etc
 */
#elif defined (IOM_START_SEC_POSTBUILDCFG)
   #undef      IOM_START_SEC_POSTBUILDCFG
   #undef MEMMAP_ERROR
#elif defined (IOM_STOP_SEC_POSTBUILDCFG)
   #undef      IOM_STOP_SEC_POSTBUILDCFG
   #undef MEMMAP_ERROR


#elif defined (IOM_START_SEC_CODE)
   #undef      IOM_START_SEC_CODE
   #undef MEMMAP_ERROR
#elif defined (IOM_STOP_SEC_CODE)
   #undef      IOM_STOP_SEC_CODE
   #undef MEMMAP_ERROR


#elif defined (IOM_START_SEC_VAR_8BIT)
   #undef      IOM_START_SEC_VAR_8BIT
   #undef MEMMAP_ERROR
#elif defined (IOM_STOP_SEC_VAR_8BIT)
   #undef      IOM_STOP_SEC_VAR_8BIT
   #undef MEMMAP_ERROR


#elif defined (IOM_START_SEC_VAR_32BIT)
   #undef      IOM_START_SEC_VAR_32BIT
   #undef MEMMAP_ERROR
#elif defined (IOM_STOP_SEC_VAR_32BIT)
   #undef      IOM_STOP_SEC_VAR_32BIT
   #undef MEMMAP_ERROR

/*****************************************************************************
**                                 ERU                                      **
******************************************************************************/

/*
 * To be used for mapping code to application block, boot block,
 * external flash etc
 */
#elif defined (ERU_START_SEC_CODE)
   #undef      ERU_START_SEC_CODE
   #undef MEMMAP_ERROR
#elif defined (ERU_STOP_SEC_CODE)
   #undef      ERU_STOP_SEC_CODE
   #undef MEMMAP_ERROR


#elif defined (ERU_START_SEC_VAR_NOINIT_8BIT)
   #undef      ERU_START_SEC_VAR_NOINIT_8BIT
   #undef MEMMAP_ERROR
#elif defined (ERU_STOP_SEC_VAR_NOINIT_8BIT)
   #undef      ERU_STOP_SEC_VAR_NOINIT_8BIT
   #undef MEMMAP_ERROR


#elif defined (ERU_START_SEC_VAR_NOINIT_16BIT)
   #undef      ERU_START_SEC_VAR_NOINIT_16BIT
   #undef MEMMAP_ERROR
#elif defined (ERU_STOP_SEC_VAR_NOINIT_16BIT)
   #undef      ERU_STOP_SEC_VAR_NOINIT_16BIT
   #undef MEMMAP_ERROR


#elif defined (ERU_START_SEC_VAR_NOINIT_32BIT)
   #undef      ERU_START_SEC_VAR_NOINIT_32BIT
   #undef MEMMAP_ERROR
#elif defined (ERU_STOP_SEC_VAR_NOINIT_32BIT)
   #undef      ERU_STOP_SEC_VAR_NOINIT_32BIT
   #undef MEMMAP_ERROR


#elif defined (ERU_START_SEC_VAR_NOINIT_UNSPECIFIED)
   #undef      ERU_START_SEC_VAR_NOINIT_UNSPECIFIED
   #undef MEMMAP_ERROR
#elif defined (ERU_STOP_SEC_VAR_NOINIT_UNSPECIFIED)
   #undef      ERU_STOP_SEC_VAR_NOINIT_UNSPECIFIED
   #undef MEMMAP_ERROR


#elif defined (ERU_START_SEC_VAR_POWER_ON_INIT_8BIT)
   #undef      ERU_START_SEC_VAR_POWER_ON_INIT_8BIT
   #undef MEMMAP_ERROR
#elif defined (ERU_STOP_SEC_VAR_POWER_ON_INIT_8BIT)
   #undef      ERU_STOP_SEC_VAR_POWER_ON_INIT_8BIT
   #undef MEMMAP_ERROR


#elif defined (ERU_START_SEC_VAR_POWER_ON_INIT_16BIT)
   #undef      ERU_START_SEC_VAR_POWER_ON_INIT_16BIT
   #undef MEMMAP_ERROR
#elif defined (ERU_STOP_SEC_VAR_POWER_ON_INIT_16BIT)
   #undef      ERU_STOP_SEC_VAR_POWER_ON_INIT_16BIT
   #undef MEMMAP_ERROR


#elif defined (ERU_START_SEC_VAR_POWER_ON_INIT_32BIT)
   #undef      ERU_START_SEC_VAR_POWER_ON_INIT_32BIT
   #undef MEMMAP_ERROR
#elif defined (ERU_STOP_SEC_VAR_POWER_ON_INIT_32BIT)
   #undef      ERU_STOP_SEC_VAR_POWER_ON_INIT_32BIT
   #undef MEMMAP_ERROR


#elif defined (ERU_START_SEC_VAR_POWER_ON_INIT_UNSPECIFIED)
   #undef      ERU_START_SEC_VAR_POWER_ON_INIT_UNSPECIFIED
   #undef MEMMAP_ERROR
#elif defined (ERU_STOP_SEC_VAR_POWER_ON_INIT_UNSPECIFIED)
   #undef      ERU_STOP_SEC_VAR_POWER_ON_INIT_UNSPECIFIED
   #undef MEMMAP_ERROR


#elif defined (ERU_START_SEC_VAR_FAST_8BIT)
   #undef      ERU_START_SEC_VAR_FAST_8BIT
   #undef MEMMAP_ERROR
#elif defined (ERU_STOP_SEC_VAR_FAST_8BIT)
   #undef      ERU_STOP_SEC_VAR_FAST_8BIT
   #undef MEMMAP_ERROR


#elif defined (ERU_START_SEC_VAR_FAST_16BIT)
   #undef      ERU_START_SEC_VAR_FAST_16BIT
   #undef MEMMAP_ERROR
#elif defined (ERU_STOP_SEC_VAR_FAST_16BIT)
   #undef      ERU_STOP_SEC_VAR_FAST_16BIT
   #undef MEMMAP_ERROR


#elif defined (ERU_START_SEC_VAR_FAST_32BIT)
   #undef      ERU_START_SEC_VAR_FAST_32BIT
   #undef MEMMAP_ERROR
#elif defined (ERU_STOP_SEC_VAR_FAST_32BIT)
   #undef      ERU_STOP_SEC_VAR_FAST_32BIT
   #undef MEMMAP_ERROR


#elif defined (ERU_START_SEC_VAR_FAST_UNSPECIFIED)
   #undef      ERU_START_SEC_VAR_FAST_UNSPECIFIED
   #undef MEMMAP_ERROR
#elif defined (ERU_STOP_SEC_VAR_FAST_UNSPECIFIED)
   #undef      ERU_STOP_SEC_VAR_FAST_UNSPECIFIED
   #undef MEMMAP_ERROR


#elif defined (ERU_START_SEC_VAR_8BIT)
   #undef      ERU_START_SEC_VAR_8BIT
   #undef MEMMAP_ERROR
#elif defined (ERU_STOP_SEC_VAR_8BIT)
   #undef      ERU_STOP_SEC_VAR_8BIT
   #undef MEMMAP_ERROR


#elif defined (ERU_START_SEC_VAR_16BIT)
   #undef      ERU_START_SEC_VAR_16BIT
   #undef MEMMAP_ERROR
#elif defined (ERU_STOP_SEC_VAR_16BIT)
   #undef      ERU_STOP_SEC_VAR_16BIT
   #undef MEMMAP_ERROR


#elif defined (ERU_START_SEC_VAR_32BIT)
   #undef      ERU_START_SEC_VAR_32BIT
   #undef MEMMAP_ERROR
#elif defined (ERU_STOP_SEC_VAR_32BIT)
   #undef      ERU_STOP_SEC_VAR_32BIT
   #undef MEMMAP_ERROR


#elif defined (ERU_START_SEC_VAR_UNSPECIFIED)
   #undef      ERU_START_SEC_VAR_UNSPECIFIED
   #undef MEMMAP_ERROR
#elif defined (ERU_STOP_SEC_VAR_UNSPECIFIED)
   #undef      ERU_STOP_SEC_VAR_UNSPECIFIED
   #undef MEMMAP_ERROR


#elif defined (ERU_START_SEC_CONST_8BIT)
   #undef      ERU_START_SEC_CONST_8BIT
   #undef MEMMAP_ERROR
#elif defined (ERU_STOP_SEC_CONST_8BIT)
   #undef      ERU_STOP_SEC_CONST_8BIT
   #undef MEMMAP_ERROR


#elif defined (ERU_START_SEC_CONST_16BIT)
   #undef      ERU_START_SEC_CONST_16BIT
   #undef MEMMAP_ERROR
#elif defined (ERU_STOP_SEC_CONST_16BIT)
   #undef      ERU_STOP_SEC_CONST_16BIT
   #undef MEMMAP_ERROR


#elif defined (ERU_START_SEC_CONST_32BIT)
   #undef      ERU_START_SEC_CONST_32BIT
   #undef MEMMAP_ERROR
#elif defined (ERU_STOP_SEC_CONST_32BIT)
   #undef      ERU_STOP_SEC_CONST_32BIT
   #undef MEMMAP_ERROR


#elif defined (ERU_START_SEC_CONST_UNSPECIFIED)
   #undef      ERU_START_SEC_CONST_UNSPECIFIED
   #undef MEMMAP_ERROR
#elif defined (ERU_STOP_SEC_CONST_UNSPECIFIED)
   #undef      ERU_STOP_SEC_CONST_UNSPECIFIED
   #undef MEMMAP_ERROR

/*****************************************************************************
**                                 MSC                                      **
******************************************************************************/

/*
 * To be used for mapping code to application block, boot block,
 * external flash etc
 */
#elif defined (MSC_START_SEC_CODE)
   #undef      MSC_START_SEC_CODE
   #undef MEMMAP_ERROR
#elif defined (MSC_STOP_SEC_CODE)
   #undef      MSC_STOP_SEC_CODE
   #undef MEMMAP_ERROR


#elif defined (MSC_START_SEC_VAR_NOINIT_8BIT)
   #undef      MSC_START_SEC_VAR_NOINIT_8BIT
   #undef MEMMAP_ERROR
#elif defined (MSC_STOP_SEC_VAR_NOINIT_8BIT)
   #undef      MSC_STOP_SEC_VAR_NOINIT_8BIT
   #undef MEMMAP_ERROR


#elif defined (MSC_START_SEC_VAR_NOINIT_16BIT)
   #undef      MSC_START_SEC_VAR_NOINIT_16BIT
   #undef MEMMAP_ERROR
#elif defined (MSC_STOP_SEC_VAR_NOINIT_16BIT)
   #undef      MSC_STOP_SEC_VAR_NOINIT_16BIT
   #undef MEMMAP_ERROR


#elif defined (MSC_START_SEC_VAR_NOINIT_32BIT)
   #undef      MSC_START_SEC_VAR_NOINIT_32BIT
   #undef MEMMAP_ERROR
#elif defined (MSC_STOP_SEC_VAR_NOINIT_32BIT)
   #undef      MSC_STOP_SEC_VAR_NOINIT_32BIT
   #undef MEMMAP_ERROR


#elif defined (MSC_START_SEC_VAR_NOINIT_UNSPECIFIED)
   #undef      MSC_START_SEC_VAR_NOINIT_UNSPECIFIED
   #undef MEMMAP_ERROR
#elif defined (MSC_STOP_SEC_VAR_NOINIT_UNSPECIFIED)
   #undef      MSC_STOP_SEC_VAR_NOINIT_UNSPECIFIED
   #undef MEMMAP_ERROR


#elif defined (MSC_START_SEC_VAR_POWER_ON_INIT_8BIT)
   #undef      MSC_START_SEC_VAR_POWER_ON_INIT_8BIT
   #undef MEMMAP_ERROR
#elif defined (MSC_STOP_SEC_VAR_POWER_ON_INIT_8BIT)
   #undef      MSC_STOP_SEC_VAR_POWER_ON_INIT_8BIT
   #undef MEMMAP_ERROR


#elif defined (MSC_START_SEC_VAR_POWER_ON_INIT_16BIT)
   #undef      MSC_START_SEC_VAR_POWER_ON_INIT_16BIT
   #undef MEMMAP_ERROR
#elif defined (MSC_STOP_SEC_VAR_POWER_ON_INIT_16BIT)
   #undef      MSC_STOP_SEC_VAR_POWER_ON_INIT_16BIT
   #undef MEMMAP_ERROR


#elif defined (MSC_START_SEC_VAR_POWER_ON_INIT_32BIT)
   #undef      MSC_START_SEC_VAR_POWER_ON_INIT_32BIT
   #undef MEMMAP_ERROR
#elif defined (MSC_STOP_SEC_VAR_POWER_ON_INIT_32BIT)
   #undef      MSC_STOP_SEC_VAR_POWER_ON_INIT_32BIT
   #undef MEMMAP_ERROR


#elif defined (MSC_START_SEC_VAR_POWER_ON_INIT_UNSPECIFIED)
   #undef      MSC_START_SEC_VAR_POWER_ON_INIT_UNSPECIFIED
   #undef MEMMAP_ERROR
#elif defined (MSC_STOP_SEC_VAR_POWER_ON_INIT_UNSPECIFIED)
   #undef      MSC_STOP_SEC_VAR_POWER_ON_INIT_UNSPECIFIED
   #undef MEMMAP_ERROR


#elif defined (MSC_START_SEC_VAR_FAST_8BIT)
   #undef      MSC_START_SEC_VAR_FAST_8BIT
   #undef MEMMAP_ERROR
#elif defined (MSC_STOP_SEC_VAR_FAST_8BIT)
   #undef      MSC_STOP_SEC_VAR_FAST_8BIT
   #undef MEMMAP_ERROR


#elif defined (MSC_START_SEC_VAR_FAST_16BIT)
   #undef      MSC_START_SEC_VAR_FAST_16BIT
   #undef MEMMAP_ERROR
#elif defined (MSC_STOP_SEC_VAR_FAST_16BIT)
   #undef      MSC_STOP_SEC_VAR_FAST_16BIT
   #undef MEMMAP_ERROR


#elif defined (MSC_START_SEC_VAR_FAST_32BIT)
   #undef      MSC_START_SEC_VAR_FAST_32BIT
   #undef MEMMAP_ERROR
#elif defined (MSC_STOP_SEC_VAR_FAST_32BIT)
   #undef      MSC_STOP_SEC_VAR_FAST_32BIT
   #undef MEMMAP_ERROR


#elif defined (MSC_START_SEC_VAR_FAST_UNSPECIFIED)
   #undef      MSC_START_SEC_VAR_FAST_UNSPECIFIED
   #undef MEMMAP_ERROR
#elif defined (MSC_STOP_SEC_VAR_FAST_UNSPECIFIED)
   #undef      MSC_STOP_SEC_VAR_FAST_UNSPECIFIED
   #undef MEMMAP_ERROR


#elif defined (MSC_START_SEC_VAR_8BIT)
   #undef      MSC_START_SEC_VAR_8BIT
   #undef MEMMAP_ERROR
#elif defined (MSC_STOP_SEC_VAR_8BIT)
   #undef      MSC_STOP_SEC_VAR_8BIT
   #undef MEMMAP_ERROR


#elif defined (MSC_START_SEC_VAR_16BIT)
   #undef      MSC_START_SEC_VAR_16BIT
   #undef MEMMAP_ERROR
#elif defined (MSC_STOP_SEC_VAR_16BIT)
   #undef      MSC_STOP_SEC_VAR_16BIT
   #undef MEMMAP_ERROR


#elif defined (MSC_START_SEC_VAR_32BIT)
   #undef      MSC_START_SEC_VAR_32BIT
   #undef MEMMAP_ERROR
#elif defined (MSC_STOP_SEC_VAR_32BIT)
   #undef      MSC_STOP_SEC_VAR_32BIT
   #undef MEMMAP_ERROR


#elif defined (MSC_START_SEC_VAR_UNSPECIFIED)
   #undef      MSC_START_SEC_VAR_UNSPECIFIED
   #undef MEMMAP_ERROR
#elif defined (MSC_STOP_SEC_VAR_UNSPECIFIED)
   #undef      MSC_STOP_SEC_VAR_UNSPECIFIED
   #undef MEMMAP_ERROR


#elif defined (MSC_START_SEC_CONST_8BIT)
   #undef      MSC_START_SEC_CONST_8BIT
   #undef MEMMAP_ERROR
#elif defined (MSC_STOP_SEC_CONST_8BIT)
   #undef      MSC_STOP_SEC_CONST_8BIT
   #undef MEMMAP_ERROR


#elif defined (MSC_START_SEC_CONST_16BIT)
   #undef      MSC_START_SEC_CONST_16BIT
   #undef MEMMAP_ERROR
#elif defined (MSC_STOP_SEC_CONST_16BIT)
   #undef      MSC_STOP_SEC_CONST_16BIT
   #undef MEMMAP_ERROR


#elif defined (MSC_START_SEC_CONST_32BIT)
   #undef      MSC_START_SEC_CONST_32BIT
   #undef MEMMAP_ERROR
#elif defined (MSC_STOP_SEC_CONST_32BIT)
   #undef      MSC_STOP_SEC_CONST_32BIT
   #undef MEMMAP_ERROR


#elif defined (MSC_START_SEC_CONST_UNSPECIFIED)
   #undef      MSC_START_SEC_CONST_UNSPECIFIED
   #undef MEMMAP_ERROR
#elif defined (MSC_STOP_SEC_CONST_UNSPECIFIED)
   #undef      MSC_STOP_SEC_CONST_UNSPECIFIED
   #undef MEMMAP_ERROR


#elif defined (MSC_START_SEC_POSTBUILDCFG)
   #undef      MSC_START_SEC_POSTBUILDCFG
   #undef MEMMAP_ERROR
#elif defined (MSC_STOP_SEC_POSTBUILDCFG)
   #undef      MSC_STOP_SEC_POSTBUILDCFG
   #undef MEMMAP_ERROR

/*****************************************************************************
**                                 UART                                      **
******************************************************************************/

/*
 * To be used for mapping code to application block, boot block,
 * external flash etc
 */
#elif defined (UART_START_SEC_CODE)
   #undef      UART_START_SEC_CODE
   #undef MEMMAP_ERROR
#elif defined (UART_STOP_SEC_CODE)
   #undef      UART_STOP_SEC_CODE
   #undef MEMMAP_ERROR


#elif defined (UART_START_SEC_VAR_NOINIT_8BIT)
   #undef      UART_START_SEC_VAR_NOINIT_8BIT
   #undef MEMMAP_ERROR
#elif defined (UART_STOP_SEC_VAR_NOINIT_8BIT)
   #undef      UART_STOP_SEC_VAR_NOINIT_8BIT
   #undef MEMMAP_ERROR


#elif defined (UART_START_SEC_VAR_NOINIT_16BIT)
   #undef      UART_START_SEC_VAR_NOINIT_16BIT
   #undef MEMMAP_ERROR
#elif defined (UART_STOP_SEC_VAR_NOINIT_16BIT)
   #undef      UART_STOP_SEC_VAR_NOINIT_16BIT
   #undef MEMMAP_ERROR


#elif defined (UART_START_SEC_VAR_NOINIT_32BIT)
   #undef      UART_START_SEC_VAR_NOINIT_32BIT
   #undef MEMMAP_ERROR
#elif defined (UART_STOP_SEC_VAR_NOINIT_32BIT)
   #undef      UART_STOP_SEC_VAR_NOINIT_32BIT
   #undef MEMMAP_ERROR


#elif defined (UART_START_SEC_VAR_NOINIT_UNSPECIFIED)
   #undef      UART_START_SEC_VAR_NOINIT_UNSPECIFIED
   #undef MEMMAP_ERROR
#elif defined (UART_STOP_SEC_VAR_NOINIT_UNSPECIFIED)
   #undef      UART_STOP_SEC_VAR_NOINIT_UNSPECIFIED
   #undef MEMMAP_ERROR


#elif defined (UART_START_SEC_VAR_POWER_ON_INIT_8BIT)
   #undef      UART_START_SEC_VAR_POWER_ON_INIT_8BIT
   #undef MEMMAP_ERROR
#elif defined (UART_STOP_SEC_VAR_POWER_ON_INIT_8BIT)
   #undef      UART_STOP_SEC_VAR_POWER_ON_INIT_8BIT
   #undef MEMMAP_ERROR


#elif defined (UART_START_SEC_VAR_POWER_ON_INIT_16BIT)
   #undef      UART_START_SEC_VAR_POWER_ON_INIT_16BIT
   #undef MEMMAP_ERROR
#elif defined (UART_STOP_SEC_VAR_POWER_ON_INIT_16BIT)
   #undef      UART_STOP_SEC_VAR_POWER_ON_INIT_16BIT
   #undef MEMMAP_ERROR


#elif defined (UART_START_SEC_VAR_POWER_ON_INIT_32BIT)
   #undef      UART_START_SEC_VAR_POWER_ON_INIT_32BIT
   #undef MEMMAP_ERROR
#elif defined (UART_STOP_SEC_VAR_POWER_ON_INIT_32BIT)
   #undef      UART_STOP_SEC_VAR_POWER_ON_INIT_32BIT
   #undef MEMMAP_ERROR


#elif defined (UART_START_SEC_VAR_POWER_ON_INIT_UNSPECIFIED)
   #undef      UART_START_SEC_VAR_POWER_ON_INIT_UNSPECIFIED
   #undef MEMMAP_ERROR
#elif defined (UART_STOP_SEC_VAR_POWER_ON_INIT_UNSPECIFIED)
   #undef      UART_STOP_SEC_VAR_POWER_ON_INIT_UNSPECIFIED
   #undef MEMMAP_ERROR


#elif defined (UART_START_SEC_VAR_FAST_8BIT)
   #undef      UART_START_SEC_VAR_FAST_8BIT
   #undef MEMMAP_ERROR
#elif defined (UART_STOP_SEC_VAR_FAST_8BIT)
   #undef      UART_STOP_SEC_VAR_FAST_8BIT
   #undef MEMMAP_ERROR


#elif defined (UART_START_SEC_VAR_FAST_16BIT)
   #undef      UART_START_SEC_VAR_FAST_16BIT
   #undef MEMMAP_ERROR
#elif defined (UART_STOP_SEC_VAR_FAST_16BIT)
   #undef      UART_STOP_SEC_VAR_FAST_16BIT
   #undef MEMMAP_ERROR


#elif defined (UART_START_SEC_VAR_FAST_32BIT)
   #undef      UART_START_SEC_VAR_FAST_32BIT
   #undef MEMMAP_ERROR
#elif defined (UART_STOP_SEC_VAR_FAST_32BIT)
   #undef      UART_STOP_SEC_VAR_FAST_32BIT
   #undef MEMMAP_ERROR


#elif defined (UART_START_SEC_VAR_FAST_UNSPECIFIED)
   #undef      UART_START_SEC_VAR_FAST_UNSPECIFIED
   #undef MEMMAP_ERROR
#elif defined (UART_STOP_SEC_VAR_FAST_UNSPECIFIED)
   #undef      UART_STOP_SEC_VAR_FAST_UNSPECIFIED
   #undef MEMMAP_ERROR


#elif defined (UART_START_SEC_VAR_8BIT)
   #undef      UART_START_SEC_VAR_8BIT
   #undef MEMMAP_ERROR
#elif defined (UART_STOP_SEC_VAR_8BIT)
   #undef      UART_STOP_SEC_VAR_8BIT
   #undef MEMMAP_ERROR


#elif defined (UART_START_SEC_VAR_16BIT)
   #undef      UART_START_SEC_VAR_16BIT
   #undef MEMMAP_ERROR
#elif defined (UART_STOP_SEC_VAR_16BIT)
   #undef      UART_STOP_SEC_VAR_16BIT
   #undef MEMMAP_ERROR


#elif defined (UART_START_SEC_VAR_32BIT)
   #undef      UART_START_SEC_VAR_32BIT
   #undef MEMMAP_ERROR
#elif defined (UART_STOP_SEC_VAR_32BIT)
   #undef      UART_STOP_SEC_VAR_32BIT
   #undef MEMMAP_ERROR


#elif defined (UART_START_SEC_VAR_UNSPECIFIED)
   #undef      UART_START_SEC_VAR_UNSPECIFIED
   #undef MEMMAP_ERROR
#elif defined (UART_STOP_SEC_VAR_UNSPECIFIED)
   #undef      UART_STOP_SEC_VAR_UNSPECIFIED
   #undef MEMMAP_ERROR


#elif defined (UART_START_SEC_CONST_8BIT)
   #undef      UART_START_SEC_CONST_8BIT
   #undef MEMMAP_ERROR
#elif defined (UART_STOP_SEC_CONST_8BIT)
   #undef      UART_STOP_SEC_CONST_8BIT
   #undef MEMMAP_ERROR


#elif defined (UART_START_SEC_CONST_16BIT)
   #undef      UART_START_SEC_CONST_16BIT
   #undef MEMMAP_ERROR
#elif defined (UART_STOP_SEC_CONST_16BIT)
   #undef      UART_STOP_SEC_CONST_16BIT
   #undef MEMMAP_ERROR


#elif defined (UART_START_SEC_CONST_32BIT)
   #undef      UART_START_SEC_CONST_32BIT
   #undef MEMMAP_ERROR
#elif defined (UART_STOP_SEC_CONST_32BIT)
   #undef      UART_STOP_SEC_CONST_32BIT
   #undef MEMMAP_ERROR


#elif defined (UART_START_SEC_CONST_UNSPECIFIED)
   #undef      UART_START_SEC_CONST_UNSPECIFIED
   #undef MEMMAP_ERROR
#elif defined (UART_STOP_SEC_CONST_UNSPECIFIED)
   #undef      UART_STOP_SEC_CONST_UNSPECIFIED
   #undef MEMMAP_ERROR


#elif defined (UART_START_SEC_POSTBUILDCFG)
   #undef      UART_START_SEC_POSTBUILDCFG
   #undef MEMMAP_ERROR
#elif defined (UART_STOP_SEC_POSTBUILDCFG)
   #undef      UART_STOP_SEC_POSTBUILDCFG
   #undef MEMMAP_ERROR

/*****************************************************************************
**                                 CANTRCV6251G                                      **
******************************************************************************/

/*
 * To be used for mapping code to application block, boot block,
 * external flash etc
 */
#elif defined (CANTRCV6251G_START_SEC_CODE)
   #undef      CANTRCV6251G_START_SEC_CODE
   #undef MEMMAP_ERROR
#elif defined (CANTRCV6251G_STOP_SEC_CODE)
   #undef      CANTRCV6251G_STOP_SEC_CODE
   #undef MEMMAP_ERROR


#elif defined (CANTRCV6251G_START_SEC_VAR_NOINIT_8BIT)
   #undef      CANTRCV6251G_START_SEC_VAR_NOINIT_8BIT
   #undef MEMMAP_ERROR
#elif defined (CANTRCV6251G_STOP_SEC_VAR_NOINIT_8BIT)
   #undef      CANTRCV6251G_STOP_SEC_VAR_NOINIT_8BIT
   #undef MEMMAP_ERROR


#elif defined (CANTRCV6251G_START_SEC_VAR_NOINIT_16BIT)
   #undef      CANTRCV6251G_START_SEC_VAR_NOINIT_16BIT
   #undef MEMMAP_ERROR
#elif defined (CANTRCV6251G_STOP_SEC_VAR_NOINIT_16BIT)
   #undef      CANTRCV6251G_STOP_SEC_VAR_NOINIT_16BIT
   #undef MEMMAP_ERROR


#elif defined (CANTRCV6251G_START_SEC_VAR_NOINIT_32BIT)
   #undef      CANTRCV6251G_START_SEC_VAR_NOINIT_32BIT
   #undef MEMMAP_ERROR
#elif defined (CANTRCV6251G_STOP_SEC_VAR_NOINIT_32BIT)
   #undef      CANTRCV6251G_STOP_SEC_VAR_NOINIT_32BIT
   #undef MEMMAP_ERROR


#elif defined (CANTRCV6251G_START_SEC_VAR_NOINIT_UNSPECIFIED)
   #undef      CANTRCV6251G_START_SEC_VAR_NOINIT_UNSPECIFIED
   #undef MEMMAP_ERROR
#elif defined (CANTRCV6251G_STOP_SEC_VAR_NOINIT_UNSPECIFIED)
   #undef      CANTRCV6251G_STOP_SEC_VAR_NOINIT_UNSPECIFIED
   #undef MEMMAP_ERROR


#elif defined (CANTRCV6251G_START_SEC_VAR_POWER_ON_INIT_8BIT)
   #undef      CANTRCV6251G_START_SEC_VAR_POWER_ON_INIT_8BIT
   #undef MEMMAP_ERROR
#elif defined (CANTRCV6251G_STOP_SEC_VAR_POWER_ON_INIT_8BIT)
   #undef      CANTRCV6251G_STOP_SEC_VAR_POWER_ON_INIT_8BIT
   #undef MEMMAP_ERROR


#elif defined (CANTRCV6251G_START_SEC_VAR_POWER_ON_INIT_16BIT)
   #undef      CANTRCV6251G_START_SEC_VAR_POWER_ON_INIT_16BIT
   #undef MEMMAP_ERROR
#elif defined (CANTRCV6251G_STOP_SEC_VAR_POWER_ON_INIT_16BIT)
   #undef      CANTRCV6251G_STOP_SEC_VAR_POWER_ON_INIT_16BIT
   #undef MEMMAP_ERROR


#elif defined (CANTRCV6251G_START_SEC_VAR_POWER_ON_INIT_32BIT)
   #undef      CANTRCV6251G_START_SEC_VAR_POWER_ON_INIT_32BIT
   #undef MEMMAP_ERROR
#elif defined (CANTRCV6251G_STOP_SEC_VAR_POWER_ON_INIT_32BIT)
   #undef      CANTRCV6251G_STOP_SEC_VAR_POWER_ON_INIT_32BIT
   #undef MEMMAP_ERROR


#elif defined (CANTRCV6251G_START_SEC_VAR_POWER_ON_INIT_UNSPECIFIED)
   #undef      CANTRCV6251G_START_SEC_VAR_POWER_ON_INIT_UNSPECIFIED
   #undef MEMMAP_ERROR
#elif defined (CANTRCV6251G_STOP_SEC_VAR_POWER_ON_INIT_UNSPECIFIED)
   #undef      CANTRCV6251G_STOP_SEC_VAR_POWER_ON_INIT_UNSPECIFIED
   #undef MEMMAP_ERROR


#elif defined (CANTRCV6251G_START_SEC_VAR_FAST_8BIT)
   #undef      CANTRCV6251G_START_SEC_VAR_FAST_8BIT
   #undef MEMMAP_ERROR
#elif defined (CANTRCV6251G_STOP_SEC_VAR_FAST_8BIT)
   #undef      CANTRCV6251G_STOP_SEC_VAR_FAST_8BIT
   #undef MEMMAP_ERROR


#elif defined (CANTRCV6251G_START_SEC_VAR_FAST_16BIT)
   #undef      CANTRCV6251G_START_SEC_VAR_FAST_16BIT
   #undef MEMMAP_ERROR
#elif defined (CANTRCV6251G_STOP_SEC_VAR_FAST_16BIT)
   #undef      CANTRCV6251G_STOP_SEC_VAR_FAST_16BIT
   #undef MEMMAP_ERROR


#elif defined (CANTRCV6251G_START_SEC_VAR_FAST_32BIT)
   #undef      CANTRCV6251G_START_SEC_VAR_FAST_32BIT
   #undef MEMMAP_ERROR
#elif defined (CANTRCV6251G_STOP_SEC_VAR_FAST_32BIT)
   #undef      CANTRCV6251G_STOP_SEC_VAR_FAST_32BIT
   #undef MEMMAP_ERROR


#elif defined (CANTRCV6251G_START_SEC_VAR_FAST_UNSPECIFIED)
   #undef      CANTRCV6251G_START_SEC_VAR_FAST_UNSPECIFIED
   #undef MEMMAP_ERROR
#elif defined (CANTRCV6251G_STOP_SEC_VAR_FAST_UNSPECIFIED)
   #undef      CANTRCV6251G_STOP_SEC_VAR_FAST_UNSPECIFIED
   #undef MEMMAP_ERROR


#elif defined (CANTRCV6251G_START_SEC_VAR_8BIT)
   #undef      CANTRCV6251G_START_SEC_VAR_8BIT
   #undef MEMMAP_ERROR
#elif defined (CANTRCV6251G_STOP_SEC_VAR_8BIT)
   #undef      CANTRCV6251G_STOP_SEC_VAR_8BIT
   #undef MEMMAP_ERROR


#elif defined (CANTRCV6251G_START_SEC_VAR_16BIT)
   #undef      CANTRCV6251G_START_SEC_VAR_16BIT
   #undef MEMMAP_ERROR
#elif defined (CANTRCV6251G_STOP_SEC_VAR_16BIT)
   #undef      CANTRCV6251G_STOP_SEC_VAR_16BIT
   #undef MEMMAP_ERROR


#elif defined (CANTRCV6251G_START_SEC_VAR_32BIT)
   #undef      CANTRCV6251G_START_SEC_VAR_32BIT
   #undef MEMMAP_ERROR
#elif defined (CANTRCV6251G_STOP_SEC_VAR_32BIT)
   #undef      CANTRCV6251G_STOP_SEC_VAR_32BIT
   #undef MEMMAP_ERROR


#elif defined (CANTRCV6251G_START_SEC_VAR_UNSPECIFIED)
   #undef      CANTRCV6251G_START_SEC_VAR_UNSPECIFIED
   #undef MEMMAP_ERROR
#elif defined (CANTRCV6251G_STOP_SEC_VAR_UNSPECIFIED)
   #undef      CANTRCV6251G_STOP_SEC_VAR_UNSPECIFIED
   #undef MEMMAP_ERROR


#elif defined (CANTRCV6251G_START_SEC_CONST_8BIT)
   #undef      CANTRCV6251G_START_SEC_CONST_8BIT
   #undef MEMMAP_ERROR
#elif defined (CANTRCV6251G_STOP_SEC_CONST_8BIT)
   #undef      CANTRCV6251G_STOP_SEC_CONST_8BIT
   #undef MEMMAP_ERROR


#elif defined (CANTRCV6251G_START_SEC_CONST_16BIT)
   #undef      CANTRCV6251G_START_SEC_CONST_16BIT
   #undef MEMMAP_ERROR
#elif defined (CANTRCV6251G_STOP_SEC_CONST_16BIT)
   #undef      CANTRCV6251G_STOP_SEC_CONST_16BIT
   #undef MEMMAP_ERROR


#elif defined (CANTRCV6251G_START_SEC_CONST_32BIT)
   #undef      CANTRCV6251G_START_SEC_CONST_32BIT
   #undef MEMMAP_ERROR
#elif defined (CANTRCV6251G_STOP_SEC_CONST_32BIT)
   #undef      CANTRCV6251G_STOP_SEC_CONST_32BIT
   #undef MEMMAP_ERROR


#elif defined (CANTRCV6251G_START_SEC_CONST_UNSPECIFIED)
   #undef      CANTRCV6251G_START_SEC_CONST_UNSPECIFIED
   #undef MEMMAP_ERROR
#elif defined (CANTRCV6251G_STOP_SEC_CONST_UNSPECIFIED)
   #undef      CANTRCV6251G_STOP_SEC_CONST_UNSPECIFIED
   #undef MEMMAP_ERROR


/*****************************************************************************
**                                 STM                                      **
******************************************************************************/

/*
 * To be used for mapping code to application block, boot block,
 * external flash etc
 */
#elif defined (STM_START_SEC_CODE)
   #undef      STM_START_SEC_CODE
   #undef MEMMAP_ERROR
#elif defined (STM_STOP_SEC_CODE)
   #undef      STM_STOP_SEC_CODE
   #undef MEMMAP_ERROR


#elif defined (STM_START_SEC_VAR_NOINIT_8BIT)
   #undef      STM_START_SEC_VAR_NOINIT_8BIT
   #undef MEMMAP_ERROR
#elif defined (STM_STOP_SEC_VAR_NOINIT_8BIT)
   #undef      STM_STOP_SEC_VAR_NOINIT_8BIT
   #undef MEMMAP_ERROR


#elif defined (STM_START_SEC_VAR_NOINIT_16BIT)
   #undef      STM_START_SEC_VAR_NOINIT_16BIT
   #undef MEMMAP_ERROR
#elif defined (STM_STOP_SEC_VAR_NOINIT_16BIT)
   #undef      STM_STOP_SEC_VAR_NOINIT_16BIT
   #undef MEMMAP_ERROR


#elif defined (STM_START_SEC_VAR_NOINIT_32BIT)
   #undef      STM_START_SEC_VAR_NOINIT_32BIT
   #undef MEMMAP_ERROR
#elif defined (STM_STOP_SEC_VAR_NOINIT_32BIT)
   #undef      STM_STOP_SEC_VAR_NOINIT_32BIT
   #undef MEMMAP_ERROR


#elif defined (STM_START_SEC_VAR_NOINIT_UNSPECIFIED)
   #undef      STM_START_SEC_VAR_NOINIT_UNSPECIFIED
   #undef MEMMAP_ERROR
#elif defined (STM_STOP_SEC_VAR_NOINIT_UNSPECIFIED)
   #undef      STM_STOP_SEC_VAR_NOINIT_UNSPECIFIED
   #undef MEMMAP_ERROR


#elif defined (STM_START_SEC_VAR_POWER_ON_INIT_8BIT)
   #undef      STM_START_SEC_VAR_POWER_ON_INIT_8BIT
   #undef MEMMAP_ERROR
#elif defined (STM_STOP_SEC_VAR_POWER_ON_INIT_8BIT)
   #undef      STM_STOP_SEC_VAR_POWER_ON_INIT_8BIT
   #undef MEMMAP_ERROR


#elif defined (STM_START_SEC_VAR_POWER_ON_INIT_16BIT)
   #undef      STM_START_SEC_VAR_POWER_ON_INIT_16BIT
   #undef MEMMAP_ERROR
#elif defined (STM_STOP_SEC_VAR_POWER_ON_INIT_16BIT)
   #undef      STM_STOP_SEC_VAR_POWER_ON_INIT_16BIT
   #undef MEMMAP_ERROR


#elif defined (STM_START_SEC_VAR_POWER_ON_INIT_32BIT)
   #undef      STM_START_SEC_VAR_POWER_ON_INIT_32BIT
   #undef MEMMAP_ERROR
#elif defined (STM_STOP_SEC_VAR_POWER_ON_INIT_32BIT)
   #undef      STM_STOP_SEC_VAR_POWER_ON_INIT_32BIT
   #undef MEMMAP_ERROR


#elif defined (STM_START_SEC_VAR_POWER_ON_INIT_UNSPECIFIED)
   #undef      STM_START_SEC_VAR_POWER_ON_INIT_UNSPECIFIED
   #undef MEMMAP_ERROR
#elif defined (STM_STOP_SEC_VAR_POWER_ON_INIT_UNSPECIFIED)
   #undef      STM_STOP_SEC_VAR_POWER_ON_INIT_UNSPECIFIED
   #undef MEMMAP_ERROR


#elif defined (STM_START_SEC_VAR_FAST_8BIT)
   #undef      STM_START_SEC_VAR_FAST_8BIT
   #undef MEMMAP_ERROR
#elif defined (STM_STOP_SEC_VAR_FAST_8BIT)
   #undef      STM_STOP_SEC_VAR_FAST_8BIT
   #undef MEMMAP_ERROR


#elif defined (STM_START_SEC_VAR_FAST_16BIT)
   #undef      STM_START_SEC_VAR_FAST_16BIT
   #undef MEMMAP_ERROR
#elif defined (STM_STOP_SEC_VAR_FAST_16BIT)
   #undef      STM_STOP_SEC_VAR_FAST_16BIT
   #undef MEMMAP_ERROR


#elif defined (STM_START_SEC_VAR_FAST_32BIT)
   #undef      STM_START_SEC_VAR_FAST_32BIT
   #undef MEMMAP_ERROR
#elif defined (STM_STOP_SEC_VAR_FAST_32BIT)
   #undef      STM_STOP_SEC_VAR_FAST_32BIT
   #undef MEMMAP_ERROR


#elif defined (STM_START_SEC_VAR_FAST_UNSPECIFIED)
   #undef      STM_START_SEC_VAR_FAST_UNSPECIFIED
   #undef MEMMAP_ERROR
#elif defined (STM_STOP_SEC_VAR_FAST_UNSPECIFIED)
   #undef      STM_STOP_SEC_VAR_FAST_UNSPECIFIED
   #undef MEMMAP_ERROR


#elif defined (STM_START_SEC_VAR_8BIT)
   #undef      STM_START_SEC_VAR_8BIT
   #undef MEMMAP_ERROR
#elif defined (STM_STOP_SEC_VAR_8BIT)
   #undef      STM_STOP_SEC_VAR_8BIT
   #undef MEMMAP_ERROR


#elif defined (STM_START_SEC_VAR_16BIT)
   #undef      STM_START_SEC_VAR_16BIT
   #undef MEMMAP_ERROR
#elif defined (STM_STOP_SEC_VAR_16BIT)
   #undef      STM_STOP_SEC_VAR_16BIT
   #undef MEMMAP_ERROR


#elif defined (STM_START_SEC_VAR_32BIT)
   #undef      STM_START_SEC_VAR_32BIT
   #undef MEMMAP_ERROR
#elif defined (STM_STOP_SEC_VAR_32BIT)
   #undef      STM_STOP_SEC_VAR_32BIT
   #undef MEMMAP_ERROR


#elif defined (STM_START_SEC_VAR_UNSPECIFIED)
   #undef      STM_START_SEC_VAR_UNSPECIFIED
   #undef MEMMAP_ERROR
#elif defined (STM_STOP_SEC_VAR_UNSPECIFIED)
   #undef      STM_STOP_SEC_VAR_UNSPECIFIED
   #undef MEMMAP_ERROR


#elif defined (STM_START_SEC_CONST_8BIT)
   #undef      STM_START_SEC_CONST_8BIT
   #undef MEMMAP_ERROR
#elif defined (STM_STOP_SEC_CONST_8BIT)
   #undef      STM_STOP_SEC_CONST_8BIT
   #undef MEMMAP_ERROR


#elif defined (STM_START_SEC_CONST_16BIT)
   #undef      STM_START_SEC_CONST_16BIT
   #undef MEMMAP_ERROR
#elif defined (STM_STOP_SEC_CONST_16BIT)
   #undef      STM_STOP_SEC_CONST_16BIT
   #undef MEMMAP_ERROR


#elif defined (STM_START_SEC_CONST_32BIT)
   #undef      STM_START_SEC_CONST_32BIT
   #undef MEMMAP_ERROR
#elif defined (STM_STOP_SEC_CONST_32BIT)
   #undef      STM_STOP_SEC_CONST_32BIT
   #undef MEMMAP_ERROR


#elif defined (STM_START_SEC_CONST_UNSPECIFIED)
   #undef      STM_START_SEC_CONST_UNSPECIFIED
   #undef MEMMAP_ERROR
#elif defined (STM_STOP_SEC_CONST_UNSPECIFIED)
   #undef      STM_STOP_SEC_CONST_UNSPECIFIED
   #undef MEMMAP_ERROR


#elif defined (STM_START_SEC_POSTBUILDCFG)
   #undef      STM_START_SEC_POSTBUILDCFG
   #undef MEMMAP_ERROR
#elif defined (STM_STOP_SEC_POSTBUILDCFG)
   #undef      STM_STOP_SEC_POSTBUILDCFG
   #undef MEMMAP_ERROR



/*****************************************************************************
**                                 MCAL                                      **
******************************************************************************/

/*
 * To be used for mapping code to application block, boot block,
 * external flash etc
 */
#elif defined (MCAL_START_SEC_VAR_FAST_32BIT)
   #undef      MCAL_START_SEC_VAR_FAST_32BIT
   #undef MEMMAP_ERROR
#elif defined (MCAL_STOP_SEC_VAR_FAST_32BIT)
   #undef      MCAL_STOP_SEC_VAR_FAST_32BIT
   #undef MEMMAP_ERROR
#elif defined (MCAL_START_SEC_CONST_UNSPECIFIED)
   #undef      MCAL_START_SEC_CONST_UNSPECIFIED
   #undef MEMMAP_ERROR
#elif defined (MCAL_STOP_SEC_CONST_UNSPECIFIED)
   #undef      MCAL_STOP_SEC_CONST_UNSPECIFIED
   #undef MEMMAP_ERROR

/*****************************************************************************
** 																MCAL LIB  																**
******************************************************************************/

/*
* To be used for mapping code to application block, boot block,
* external flash etc
*/
#elif defined (MCAL_TCLIB_START_SEC_CODE)
   #undef      MCAL_TCLIB_START_SEC_CODE
   #undef MEMMAP_ERROR
#elif defined (MCAL_TCLIB_STOP_SEC_CODE)
   #undef      MCAL_TCLIB_STOP_SEC_CODE
   #undef MEMMAP_ERROR

#elif defined (MCAL_TCLIB_START_SEC_VAR_INIT_32BIT)
   #undef      MCAL_TCLIB_START_SEC_VAR_INIT_32BIT
   #undef MEMMAP_ERROR
#elif defined (MCAL_TCLIB_STOP_SEC_VAR_INIT_32BIT)
   #undef      MCAL_TCLIB_STOP_SEC_VAR_INIT_32BIT
   #undef MEMMAP_ERROR

#elif defined (MCAL_TCLIB_START_SEC_CONST_32BIT)
   #undef      MCAL_TCLIB_START_SEC_CONST_32BIT
   #undef MEMMAP_ERROR
#elif defined (MCAL_TCLIB_STOP_SEC_CONST_32BIT)
   #undef      MCAL_TCLIB_STOP_SEC_CONST_32BIT
   #undef MEMMAP_ERROR

#elif defined (MCAL_TCLIB_START_SEC_VAR_8BIT)
   #undef      MCAL_TCLIB_START_SEC_VAR_8BIT
   #undef MEMMAP_ERROR
#elif defined (MCAL_TCLIB_STOP_SEC_VAR_8BIT)
   #undef      MCAL_TCLIB_STOP_SEC_VAR_8BIT
   #undef MEMMAP_ERROR

#elif defined (MCAL_WDGLIB_START_SEC_CODE)
   #undef      MCAL_WDGLIB_START_SEC_CODE
   #undef MEMMAP_ERROR
#elif defined (MCAL_WDGLIB_STOP_SEC_CODE)
   #undef      MCAL_WDGLIB_STOP_SEC_CODE
   #undef MEMMAP_ERROR

#elif defined (MCAL_WDGLIB_START_SEC_VAR_32BIT)
   #undef      MCAL_WDGLIB_START_SEC_VAR_32BIT
   #undef MEMMAP_ERROR
#elif defined (MCAL_WDGLIB_STOP_SEC_VAR_32BIT)
   #undef      MCAL_WDGLIB_STOP_SEC_VAR_32BIT
   #undef MEMMAP_ERROR

#elif defined (MCAL_WDGLIB_START_SEC_VAR_INIT_32BIT)
   #undef      MCAL_WDGLIB_START_SEC_VAR_INIT_32BIT
   #undef MEMMAP_ERROR
#elif defined (MCAL_WDGLIB_STOP_SEC_VAR_INIT_32BIT)
   #undef      MCAL_WDGLIB_STOP_SEC_VAR_INIT_32BIT
   #undef MEMMAP_ERROR
   
#elif defined (MCAL_WDGLIB_START_SEC_VAR_8BIT)
   #undef      MCAL_WDGLIB_START_SEC_VAR_8BIT
   #undef MEMMAP_ERROR
#elif defined (MCAL_WDGLIB_STOP_SEC_VAR_8BIT)
   #undef      MCAL_WDGLIB_STOP_SEC_VAR_8BIT
   #undef MEMMAP_ERROR

#elif defined (MCAL_WDGLIB_START_SEC_CONST_32BIT)
   #undef      MCAL_WDGLIB_START_SEC_CONST_32BIT
   #undef MEMMAP_ERROR
#elif defined (MCAL_WDGLIB_STOP_SEC_CONST_32BIT)
   #undef      MCAL_WDGLIB_STOP_SEC_CONST_32BIT
   #undef MEMMAP_ERROR

#elif defined (MCAL_DMALIB_START_SEC_CODE)
   #undef      MCAL_DMALIB_START_SEC_CODE
   #undef MEMMAP_ERROR
#elif defined (MCAL_DMALIB_STOP_SEC_CODE)
   #undef      MCAL_DMALIB_STOP_SEC_CODE
   #undef MEMMAP_ERROR

#elif defined (MCAL_DMALIB_START_SEC_VAR_32BIT)
   #undef      MCAL_DMALIB_START_SEC_VAR_32BIT
   #undef MEMMAP_ERROR
#elif defined (MCAL_DMALIB_STOP_SEC_VAR_32BIT)
   #undef      MCAL_DMALIB_STOP_SEC_VAR_32BIT
   #undef MEMMAP_ERROR

#elif defined (MCAL_DMALIB_START_SEC_VAR_8BIT)
   #undef      MCAL_DMALIB_START_SEC_VAR_8BIT
   #undef MEMMAP_ERROR
#elif defined (MCAL_DMALIB_STOP_SEC_VAR_8BIT)
   #undef      MCAL_DMALIB_STOP_SEC_VAR_8BIT
   #undef MEMMAP_ERROR

/* -------------------------------------------------------------------------- */
/* End of module section mapping                                              */
/* -------------------------------------------------------------------------- */
	#elif defined (IRQ_START_SEC_IVT_CODE)
	   #undef      IRQ_START_SEC_IVT_CODE
	   #undef MEMMAP_ERROR
	#elif defined (IRQ_STOP_SEC_IVT_CODE)
	   #undef      IRQ_STOP_SEC_IVT_CODE
	   #undef MEMMAP_ERROR

	#elif defined (ADC_START_SEC_VAR_DMABUFFER)
	   #undef      ADC_START_SEC_VAR_DMABUFFER
	   #undef MEMMAP_ERROR
	#elif defined (ADC_STOP_SEC_VAR_DMABUFFER)
	   #undef      ADC_STOP_SEC_VAR_DMABUFFER
	   #undef MEMMAP_ERROR

	#elif defined (FEE_START_SEC_JOBENDNOTIF_CODE)
	   #undef   FEE_START_SEC_JOBENDNOTIF_CODE
	   #undef MEMMAP_ERROR
	#elif defined (FEE_STOP_SEC_JOBENDNOTIF_CODE)
	   #undef   FEE_STOP_SEC_JOBENDNOTIF_CODE
	   #undef MEMMAP_ERROR

	#elif defined (FEE_START_SEC_JOBERRNOTIF_CODE)
	   #undef   FEE_START_SEC_JOBERRNOTIF_CODE
	   #undef MEMMAP_ERROR
	#elif defined (FEE_STOP_SEC_JOBERRNOTIF_CODE)
	   #undef   FEE_STOP_SEC_JOBERRNOTIF_CODE
	   #undef MEMMAP_ERROR


/*
Fls_Write API : Section
*/
#elif defined (FLSLOADER_START_SEC_WRITE_CODE)
   #undef      FLSLOADER_START_SEC_WRITE_CODE
   #undef MEMMAP_ERROR
#elif defined (FLSLOADER_STOP_SEC_WRITE_CODE)
   #undef      FLSLOADER_STOP_SEC_WRITE_CODE
   #undef MEMMAP_ERROR
/*
Fls Erase API : Section
*/
#elif defined (FLSLOADER_START_SEC_ERASE_CODE)
   #undef      FLSLOADER_START_SEC_ERASE_CODE
   #undef MEMMAP_ERROR
#elif defined (FLSLOADER_STOP_SEC_ERASE_CODE)
   #undef      FLSLOADER_STOP_SEC_ERASE_CODE
   #undef MEMMAP_ERROR


/* -------------------------------------------------------------------------- */
/* End of module section mapping                                              */
/* -------------------------------------------------------------------------- */


   #elif defined (STM_START_SEC_CALLOUT_CODE)
   #undef      STM_START_SEC_CALLOUT_CODE
   #undef MEMMAP_ERROR
   #elif defined (STM_STOP_SEC_CALLOUT_CODE)
   #undef      STM_STOP_SEC_CALLOUT_CODE
   #undef MEMMAP_ERROR



/* -------------------------------------------------------------------------- */
/* End of module Notification function section mapping                        */
/* -------------------------------------------------------------------------- */
/* The Source and Destination pointers passed to the SPI are
   handled by the DMA in the asynchronous mode. It is necesarry
   that these variables fullfill the following addressing constarints.
   1. In case of transfer width > 8, the data type is 16bits. Therefore
      it is necesarry to have the source and destination pointers
      word aligned. (On a Even Boundary). Use of #pragma align 2 will
      ensure word alignment.
   2. DMA implements a Circular Buffer with a maximum width of 32KB.
      So the Src/Des Ptrs (Starting Address + Length Of data) should not
      span the 32KB Boundary if Sequential data are to be transferred.
      The start address of this section must be selected so that the
      variables donot exceed the 32KB boundary.
      [(DMA_Address & 0x00007FFFU) + Length <= 0x00008000U]

   So it has to be ensured that the section "SPI_START_SEC_VAR_DMA_ACCESS"
   fullfills the above stated criteria*/
#elif defined (SPI_START_SEC_VAR_DMA_ACCESS)
   #undef      SPI_START_SEC_VAR_DMA_ACCESS
#ifdef _DIABDATA_C_TRICORE_
   #undef MEMMAP_ERROR
#else
/* In the Demo App supplied with AUTOSAR_MCAL2,
   the section:DEFAULT_START_SEC_VAR_FAST_32BIT is sufficient to satisfy the
   memory requirements for DMA. This may not be true for other applications and
   the user should ensure this. */
   #undef MEMMAP_ERROR
#endif
#elif defined (SPI_STOP_SEC_VAR_DMA_ACCESS)
   #undef      SPI_STOP_SEC_VAR_DMA_ACCESS
#ifdef _DIABDATA_C_TRICORE_
   #undef MEMMAP_ERROR
#else
/* In the Demo App supplied with AUTOSAR_MCAL2,
   the section:DEFAULT_START_SEC_VAR_FAST_32BIT is sufficient to satisfy the
   memory requirements for DMA. This may not be true for other applications and
   the user should ensure this. */
   #undef MEMMAP_ERROR
#endif


/* The Source and Destination pointers passed to the SPI are
   handled by the DMA in the asynchronous mode. It is necesarry
   that these variables fullfill the following addressing constarints.
   1. In case of transfer width > 8, the data type is 16bits. Therefore
      it is necesarry to have the source and destination pointers
      word aligned. (On a Even Boundary). Use of #pragma align 2 will
      ensure word alignment.
   2. DMA implements a Circular Buffer with a maximum width of 32KB.
      So the Src/Des Ptrs (Starting Address + Length Of data) should not
      span the 32KB Boundary if Sequential data are to be transferred.
      The start address of this section must be selected so that the
      variables donot exceed the 32KB boundary.
      [(DMA_Address & 0x00007FFFU) + Length <= 0x00008000U]

   So it has to be ensured that the section "DMA_START_SEC_VAR_DMA_ACCESS"
   fullfills the above stated criteria*/
#elif defined (DMA_START_SEC_VAR_DMA_ACCESS)
   #undef      DMA_START_SEC_VAR_DMA_ACCESS
/* In the Demo App supplied with AUTOSAR_MCAL2,
   the section:DEFAULT_START_SEC_VAR_FAST_16BIT is sufficient to satisfy the
   memory requirements for DMA. This may not be true for other applications and
   the user should ensure this. */
   #undef MEMMAP_ERROR
#elif defined (DMA_STOP_SEC_VAR_DMA_ACCESS)
   #undef      DMA_STOP_SEC_VAR_DMA_ACCESS
   #undef MEMMAP_ERROR



#elif defined (BMD_HDR_START_SEC_CONST_UNSPECIFIED)
  #undef      BMD_HDR_START_SEC_CONST_UNSPECIFIED
  #undef MEMMAP_ERROR
#elif defined (BMD_HDR_STOP_SEC_CONST_UNSPECIFIED)
  #undef      BMD_HDR_STOP_SEC_CONST_UNSPECIFIED
  #undef MEMMAP_ERROR

/*------------------[End of all module]--------------------------------------*/
#endif