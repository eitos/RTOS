/*
 * OS.cpp
 *
 * Created: 2014-11-02 23:18:32
 *  Author: Piotr
 */
#include "OS.hpp"

PriorityQueue_t<TaskStruct_t, MAX_TASKS> TaskQueue;

void InitOS(){
	InitSysTick();
	TaskStruct_t & t = TaskQueue.front();
	ContextSet(&t.lowLevel);

	// Now we will execute this task (jump to first task)
	ExecutePendingTask();  // This will also enable interrupts

	// This will never execute, aber zicher ist zicher!
	while(1) {}
}

void ProcSysTick() {
	TaskStruct_t now;
	now = TaskQueue.front();
	TaskQueue.pop();
	TaskQueue.push(now);
	now = TaskQueue.front();
	ContextSet(&now.lowLevel);
}