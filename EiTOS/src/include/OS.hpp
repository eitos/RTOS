#ifndef OS_HPP_
#define OS_HPP_

#include "port/port.hpp"
#include "priorityQueue.hpp"
#include "swapTable.hpp"
#include "task.hpp"
#include "EiTOSConfig.hpp"

extern PriorityQueue_t<TaskStruct_t, MAX_TASKS> TaskQueue;



namespace sys {

	void ProcSysTick();
	void boot();
	void taskCreate(TaskHandler_t taskHandler, uint8_t priority, uint16_t StackSize);
};

#endif /* OS_HPP_ */
