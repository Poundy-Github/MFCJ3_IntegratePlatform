/**
 * \file
 *
 * \brief AUTOSAR Demo
 *
 * This file contains the implementation of the AUTOSAR
 * module Demo.
 *
 * \author Elektrobit Automotive GmbH, 91058 Erlangen, Germany
 *
 * Copyright 2005 - 2019 Elektrobit Automotive GmbH
 * All rights exclusively reserved for Elektrobit Automotive GmbH,
 * unless expressly agreed to otherwise.
 */

#include "TSAutosar.h"
#include <board.h>
extern int main (void);
 

 
void entry() {
  main();
}


void Mcal_ResetCpuEndInitProtection(void)
{
    
}


void Mcal_SetCpuEndInitProtection(void)
{
    
}
/* Editor settings - DO NOT DELETE
 * vi:set ts=4:
*/
