#include "OS.hpp"
#include <port/port.hpp>

PriorityQueue_t<TaskStruct_t, MAX_TASKS> TaskQueue;
TaskStruct_t ActrualRunningTaskStruct;

void sys::boot() {
    InitSysTick();
    TaskStruct_t t = TaskQueue.front();
    ContextSet(&t.lowLevel);

    // Now we will execute this task (jump to first task)
    ExecutePendingTask();  // This will also enable interrupts

    // This will never execute, aber zicher ist zicher!
    while (1) {}
}

void sys::taskCreate(TaskHandler_t taskHandler,
                     uint8_t priority,
                     uint16_t StackSize) {
    TaskStruct_t task;
    task.priority = priority;
    task.lowLevel = TaskAllocate(taskHandler, StackSize);
    TaskQueue.push(task);
}


void sys::ProcSysTick() {
    ContextGet(&ActrualRunningTaskStruct.lowLevel);
    TaskQueue.push(ActrualRunningTaskStruct);
    ActrualRunningTaskStruct = TaskQueue.front();
    TaskQueue.pop();
    ContextSet(&ActrualRunningTaskStruct.lowLevel);
}
