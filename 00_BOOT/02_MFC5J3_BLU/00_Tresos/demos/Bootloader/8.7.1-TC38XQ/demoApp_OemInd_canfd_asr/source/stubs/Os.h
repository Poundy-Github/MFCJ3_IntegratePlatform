#if (!defined OS_H)
#define OS_H

/* This file contains declarations of a stub of the OS */

/*==================[inclusions]============================================*/

#include <Os_Types.h>

/*==================[macros]================================================*/

#define OS_GENERATION_ID_OS_H 1234567890UL

#define TASK(x)             void OS_TASK_##x(void)
#define ALARMCALLBACK(x)    void OS_ACB_##x(void)
#define ISR(x)              void OS_ISR_##x(void)

#define DeclareTask(x)      extern void OS_TASK_##x(void)
#define DeclareResource(x)  typedef uint8 os_0##x
#define DeclareEvent(x)     typedef uint8 os_0##x
#define DeclareAlarm(x)     typedef uint8 os_0##x

#define OS_TimeGetLo(t)     (t)
#define OS_TimeGetHi(t)     (t)

#define CoreIdType          os_coreid_t

#define OS_TimeZero(t)             \
  do {                             \
        *(t) = (os_timestamp_t)0U; \
     } while (0)

/*==================[type definitions]======================================*/

#if (!defined STATUSTYPEDEFINED)
#define STATUSTYPEDEFINED
typedef unsigned char StatusType; /* OSEK compliance */
#endif

/*==================[external function declarations]========================*/

/* OS API - as these are not implemented, use empty defines */
/* OSEK */

extern StatusType ActivateTask(TaskType Task);
extern StatusType TerminateTask(void);
extern StatusType ChainTask(TaskType Task);
extern StatusType Schedule(void);
extern StatusType GetTaskID(TaskRefType TaskRef);
extern StatusType GetTaskState(TaskType Task, TaskStateRefType TaskStateRef);

extern StatusType GetResource(ResourceType Resource);
extern StatusType ReleaseResource(ResourceType Resource);
extern StatusType SetEvent(TaskType Task, EventMaskType EventMask);
extern StatusType ClearEvent(EventMaskType EventMask);
extern StatusType GetEvent(TaskType Task, EventMaskRefType EventMaskRef);
extern StatusType WaitEvent(EventMaskType EventMask);
extern StatusType GetAlarmBase(AlarmType Alarm, AlarmBaseRefType AlarmBaseRef);
extern StatusType GetAlarm(AlarmType Alarm, TickRefType TickRef);
extern StatusType SetRelAlarm(AlarmType Alarm, TickType Tick1, TickType Tick2);
extern StatusType SetAbsAlarm(AlarmType Alarm, TickType Tick1, TickType Tick2);
extern StatusType CancelAlarm(AlarmType Alarm);
extern AppModeType GetActiveApplicationMode(void);

extern void DisableAllInterrupts(void);
extern void EnableAllInterrupts(void);
extern void SuspendAllInterrupts(void);
extern void ResumeAllInterrupts(void);
extern void SuspendOSInterrupts(void);
extern void ResumeOSInterrupts(void);
extern void ShutdownOS(StatusType Status);
extern void StartOS(AppModeType AppMode);

extern void OS_GetTimeStamp(os_timestamp_t *timestamp);

/* AUTOSAR OS */

StatusType IncrementCounter(CounterType Counter);
StatusType GetCounterValue(CounterType Counter, TickRefType TickRef);
StatusType GetElapsedValue(CounterType Counter, TickRefType TickRef1, TickRefType TickRef2);
StatusType GetElapsedCounterValue(CounterType Counter, TickRefType TickRef1, TickRefType TickRef2);
StatusType StartScheduleTableRel(ScheduleTableType ScheduleTable, TickType Tick);
StatusType StartScheduleTableAbs(ScheduleTableType ScheduleTable, TickType Tick);
StatusType StartScheduleTableSynchron(ScheduleTableType ScheduleTable);
StatusType NextScheduleTable(ScheduleTableType ScheduleTable1, ScheduleTableType ScheduleTable2);
StatusType StopScheduleTable(ScheduleTableType ScheduleTable);
StatusType SyncScheduleTable(ScheduleTableType ScheduleTable, TickType Tick);
StatusType SetScheduleTableAsync(ScheduleTableType ScheduleTable);
StatusType GetScheduleTableStatus(ScheduleTableType ScheduleTable, ScheduleTableStatusRefType ScheduleTableStatusRef);
StatusType TerminateApplication(RestartType Restart);
ApplicationType GetApplicationID(void);
StatusType CallTrustedFunction(TrustedFunctionIndexType TrustedFunctionIndex, TrustedFunctionParameterRefType TrustedFunctionParameterRef);
AccessType CheckISRMemoryAccess(ISRType ISR, MemoryStartAddressType MemoryStartAddress, MemorySizeType MemorySize);
AccessType CheckTaskMemoryAccess(TaskType Task, MemoryStartAddressType MemoryStartAddress, MemorySizeType MemorySize);

/*==================[internal function declarations]========================*/

/*==================[external constants]====================================*/

/*==================[internal constants]====================================*/

/*==================[external data]=========================================*/

/*==================[internal data]=========================================*/

#endif /* if !defined( OS_H ) */
/*==================[end of file]===========================================*/
