#ifndef __TASK_LOW_LEVEL_HPP__
#define __TASK_LOW_LEVEL_HPP__

#include <inttypes.h>

typedef void ( * TaskHandler_t )();

struct TaskLowLevel_t {
    uint8_t* StackStart;
};

void ContextGet(TaskLowLevel_t* Current);

void ContextSet(TaskLowLevel_t* Next);

#endif
