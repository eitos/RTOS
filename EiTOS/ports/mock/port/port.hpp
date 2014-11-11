
#ifndef __PORT_HPP__
#define __PORT_HPP__

#include "TaskLowLevel.hpp"

typedef void ( * TaskHandler_t )();

void ContextSet(TaskLowLevel_t* Next) {
    // EMPTY MOCK FUNCTION
}

void ContextGet(TaskLowLevel_t* Current) {
    // EMPTY MOCK FUNCTION
}

void TriggerSysTick() {
    // EMPTY MOCK FUNCTION
}

void ResetSysTick() {
    // EMPTY MOCK FUNCTION
}

void InitSysTick() {
    // EMPTY MOCK FUNCTION
}

void ProcSysTick() {
    // EMPTY MOCK FUNCTION
}

void  ExecutePendingTask() {
    // EMPTY MOCK FUNCTION
}

TaskLowLevel_t TaskAllocate(TaskHandler_t Task, uint16_t StackSize) {
    // EMPTY MOCK FUNCTION
}






#endif /* __PORT_HPP__ */
