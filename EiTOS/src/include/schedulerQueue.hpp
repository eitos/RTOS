#ifndef __SCHEDULERQUEUE_HPP__
#define __SCHEDULERQUEUE_HPP__

#include "task.hpp"
#include "EiTOSConfig.hpp"

class SchedulerQueue_t {
 private:
    TaskStruct_t TaskList[TaskQueueSize];
    uint8_t ActualSize;
 public:
	SchedulerQueue_t();
    void init();
    uint8_t size();
    void push(const TaskStruct_t & task);
    TaskStruct_t & front();
    void pop();
};

#endif
