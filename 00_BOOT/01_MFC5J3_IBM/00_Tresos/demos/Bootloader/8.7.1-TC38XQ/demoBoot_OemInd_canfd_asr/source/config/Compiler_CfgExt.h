#if (!defined COMPILER_CFGEXT_H)
#define COMPILER_CFGEXT_H

/*==================[inclusions]=============================================*/

/*==================[macros]=================================================*/

/*------------------[memory and pointer class of a module]-------------------*/
#if (defined PROG_CODE)
#error PROG_CODE already defined
#endif
#define PROG_CODE

#if (defined PROG_CONST)
#error PROG_CONST already defined
#endif
#define PROG_CONST

#if (defined PROG_VAR_NOINIT)
#error PROG_VAR_NOINIT already defined
#endif
#define PROG_VAR_NOINIT

#if (defined PROG_VAR)
#error PROG_VAR already defined
#endif
#define PROG_VAR


#if (defined CAN_CODE)
#error CAN_CODE already defined
#endif
#define CAN_CODE

#if (defined CAN_CONST)
#error CAN_CONST already defined
#endif
#define CAN_CONST

#if (defined CAN_VAR_NOINIT)
#error CAN_VAR_NOINIT already defined
#endif
#define CAN_VAR_NOINIT

#if (defined CAN_VAR)
#error CAN_VAR already defined
#endif
#define CAN_VAR


#endif /* if !defined( COMPILER_CFGEXT_H ) */
/*==================[end of file]============================================*/
