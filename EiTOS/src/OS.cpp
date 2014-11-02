/*
 * OS.cpp
 *
 * Created: 2014-11-02 23:18:32
 *  Author: Piotr
 */ 
#include "OS.hpp"

PriorityQueue_t<TaskLowLevel_t, 10> TaskQueue;

void InitOS(){
	InitSysTick();
	TaskLowLevel_t & t = TaskQueue.front();
	ContextSet(&t);
	TaskQueue.pop();  // first task pop

	// Now we will execute this task (jump to first task)
	ExecutePendingTask();  // This will also enable interrupts

	// This will never execute, aber zicher ist zicher!
	while(1) {}
}

void ProcSysTick(){
	TaskLowLevel_t now;
	ContextGet(&now);
	TaskQueue.push(now);
	now = TaskQueue.front();
	ContextSet(&now);
	TaskQueue.pop();
}