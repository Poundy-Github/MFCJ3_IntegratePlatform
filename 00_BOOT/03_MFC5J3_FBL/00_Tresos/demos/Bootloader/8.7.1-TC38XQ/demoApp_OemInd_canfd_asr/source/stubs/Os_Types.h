#if (!defined OS_TYPES_H)
#define OS_TYPES_H

/*==================[inclusions]============================================*/

#include <Std_Types.h>

/*==================[macros]================================================*/

/*==================[type definitions]======================================*/

typedef boolean ObjectAccessType;
typedef uint8 AppModeType;
typedef uint8 AccessType;
typedef uint8 TaskType;
typedef uint8 TaskStateType;
typedef uint8 ResourceType;
typedef uint8 ScheduleTableType;
typedef uint8 RestartType;
typedef uint8 TrustedFunctionIndexType;
typedef uint8 ISRType;
typedef uint8 ApplicationType;
typedef uint8 os_coreid_t;
typedef uint16 AlarmType;
typedef uint32 EventMaskType;
typedef uint32 MemorySizeType;
typedef uint32 os_timestamp_t;

#if !defined(RTE_TYPE_CounterType) /* needed for RTE, see ASCTESTING-728 */
#define RTE_TYPE_CounterType
typedef uint8 CounterType;
#endif
#if !defined(RTE_TYPE_TickType)    /* needed for RTE, see ASCTESTING-728 */
#define RTE_TYPE_TickType
typedef uint32 TickType;
#endif

typedef void* AlarmBaseRefType;
typedef void* EventMaskRefType;
typedef void* TaskStateRefType;
typedef void* TaskRefType;
typedef void* TickRefType;
typedef void* ScheduleTableStatusRefType;
typedef void* TrustedFunctionParameterRefType;
typedef void* MemoryStartAddressType;

/*==================[external function declarations]========================*/

/*==================[internal function declarations]========================*/

/*==================[external constants]====================================*/

/*==================[internal constants]====================================*/

/*==================[external data]=========================================*/

/*==================[internal data]=========================================*/

/*==================[external function definitions]=========================*/

/*==================[internal function definitions]=========================*/

#endif /* if !defined( OS_TYPES_H ) */
/*==================[end of file]===========================================*/
