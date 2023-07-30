/**
 * \file
 *
 * \brief simple Watchdog driver
 *
 * This file contains the declarations of the module Watchdog
 *
 * \author Elektrobit Automotive GmbH, 91058 Erlangen, Germany
 *
 * Copyright 2005 - 2013 Elektrobit Automotive GmbH
 * All rights exclusively reserved for Elektrobit Automotive GmbH,
 * unless expressly agreed to otherwise.
 */

#ifndef WATCHDOG_H_
#define WATCHDOG_H_


/*==================[macros]================================================*/

/*==================[type definitions]======================================*/

/*==================[external function declarations]========================*/

extern void Watchdog_Init(void);
extern void Watchdog_Trigger(void);
extern void Watchdog_Disable(void);
extern void Watchdog_WdgDeactivate(void);
extern void Watchdog_WdgActivate(void);


#endif /* WATCHDOG_H_ */

