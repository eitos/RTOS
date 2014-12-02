#ifndef __PORT_HPP__
#define __PORT_HPP__

#define __EITOS_PORT__
#define __EITOS_MOCK_PORT__

#include "TaskLowLevel.hpp"

#if defined(__EITOS_PORT__) && !defined(__EITOS_MOCK_PORT__)
#error "You are using two different ports."
#endif

typedef void ( * TaskHandler_t )();
void ContextSet(TaskLowLevel_t* Next);
void ContextGet(TaskLowLevel_t* Current);
void TriggerSysTick();
void ResetSysTick();
void InitSysTick();
void ProcSysTick();
void  ExecutePendingTask();
TaskLowLevel_t TaskAllocate(TaskHandler_t Task, uint16_t StackSize);

#endif /* __PORT_HPP__ */
