# \file
#
# \brief Autosar Flash
#
# This file contains the implementation of the Autosar
# module Flash.
#
# \author Elektrobit Automotive GmbH, 91058 Erlangen, Germany
#
# Copyright 2005 - 2010 Elektrobit Automotive GmbH
# All rights exclusively reserved for Elektrobit Automotive GmbH,
# unless expressly agreed to otherwise.

#################################################################
# DEFINITIONS

#################################################################
# REGISTRY

# TC277, TC275 and TC23X libraries
ifeq ($(DERIVATE), TC277)
Flash_src_FILES      := \
     $(Flash_CORE_PATH)\src\FLASH_Prg.c \
     $(Flash_OUTPUT_PATH)\src\FLASH_Cfg.c \
     $(Flash_CORE_PATH)\src\FLASH_LLD.c \
     $(Flash_CORE_PATH)\src\FLASH_RAM.c \
     $(Flash_CORE_PATH)\src\FlsLoader.c \
     $(Flash_CORE_PATH)\src\FlsLoader_Platform.c 
endif
ifeq ($(DERIVATE), TC275)
Flash_src_FILES      := \
     $(Flash_CORE_PATH)\src\FLASH_Prg.c \
     $(Flash_OUTPUT_PATH)\src\FLASH_Cfg.c \
     $(Flash_CORE_PATH)\src\FLASH_LLD.c \
     $(Flash_CORE_PATH)\src\FLASH_RAM.c \
     $(Flash_CORE_PATH)\src\FlsLoader.c \
     $(Flash_CORE_PATH)\src\FlsLoader_Platform.c 
endif
ifeq ($(DERIVATE), TC23XL)
Flash_src_FILES      := \
     $(Flash_CORE_PATH)\src\FLASH_Prg.c \
     $(Flash_OUTPUT_PATH)\src\FLASH_Cfg.c \
     $(Flash_CORE_PATH)\src\FLASH_LLD.c \
     $(Flash_CORE_PATH)\src\FLASH_RAM.c \
     $(Flash_CORE_PATH)\src\FlsLoader.c \
     $(Flash_CORE_PATH)\src\FlsLoader_Platform.c 
endif

# TC26XD libraries
ifeq ($(DERIVATE), TC26XD)
Flash_src_FILES      := \
     $(Flash_CORE_PATH)\src\FLASH_Prg.c \
     $(Flash_OUTPUT_PATH)\src\FLASH_Cfg.c \
     $(Flash_CORE_PATH)\src\FLASH_LLD.c \
     $(Flash_CORE_PATH)\src\FLASH_RAM.c \
     $(Flash_CORE_PATH)\src\FlsLoader.c \
     $(Flash_CORE_PATH)\src\FlsLoader_Platform.c 
endif

# TC1782 library
ifeq ($(DERIVATE), TC1782)
Flash_src_FILES      := \
     $(Flash_CORE_PATH)\src\FLASH_Prg.c \
     $(Flash_CORE_PATH)\src\Det.c \
     $(Flash_CORE_PATH)\src\Test_Print.c \
     $(Flash_CORE_PATH)\src\FlsLoader.c \
     $(Flash_CORE_PATH)\src\FLASH_LLD.c \
     $(Flash_CORE_PATH)\src\FLASH_RAM.c \
     $(Flash_OUTPUT_PATH)\src\FLASH_Cfg.c
endif
  
# TC39XX library
ifeq ($(DERIVATE), TC39XX)
Flash_src_FILES      := \
     $(Flash_CORE_PATH)\src\FLASH_Prg.c \
     $(Flash_OUTPUT_PATH)\src\FLASH_Cfg.c \
     $(Flash_CORE_PATH)\src\FLASH_LLD.c \
     $(Flash_CORE_PATH)\src\FLASH_RAM.c \
     $(Flash_CORE_PATH)\src\FlsLoader.c \
     $(Flash_CORE_PATH)\src\FlsLoader_Platform.c 
endif

# TC38XQ library
ifeq ($(DERIVATE), TC38XQ)
Flash_src_FILES      := \
     $(Flash_CORE_PATH)\src\FLASH_Prg.c \
     $(Flash_OUTPUT_PATH)\src\FLASH_Cfg.c \
     $(Flash_CORE_PATH)\src\FLASH_LLD.c \
     $(Flash_CORE_PATH)\src\FLASH_RAM.c \
     $(Flash_CORE_PATH)\src\FlsLoader.c \
     $(Flash_CORE_PATH)\src\FlsLoader_Platform.c 
endif
     
     
LIBRARIES_TO_BUILD += Flash_src

#################################################################
# DEPENDENCIES (only for assembler files)
#


#################################################################
# RULES




