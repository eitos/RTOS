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

TaskLowLevel_t TaskAllocate(TaskHandler_t Task, uint16_t StackSize);

#endif
