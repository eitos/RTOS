#ifndef __TASK_LOW_LEVEL_HPP__
#define __TASK_LOW_LEVEL_HPP__

#include <inttypes.h>

#if defined(__EITOS_PORT__) && !defined(__EITOS_AVR_PORT__)
#error "You are using two different ports."
#endif

typedef void ( * TaskHandler_t )();

struct TaskLowLevel_t {
    uint8_t* StackStart;
	uint16_t StackSize;
};

void ContextGet(TaskLowLevel_t* Current);

void ContextSet(TaskLowLevel_t* Next);

uint16_t TaskGetHeap(const TaskLowLevel_t* Task);
void TaskOffsetStack(TaskLowLevel_t* Task, uint16_t Offset);

#endif
