/*
 * OS.hpp
 *
 * Created: 2014-11-02 23:17:25
 *  Author: Piotr
 */ 


#ifndef OS_HPP_
#define OS_HPP_

#include "port/port.hpp"
#include "priorityQueue.hpp"
#include "swapTable.hpp"
#include "task.hpp"

extern PriorityQueue_t<TaskLowLevel_t, 10> TaskQueue;


void ProcSysTick();

void InitOS();

#endif /* OS_HPP_ */
