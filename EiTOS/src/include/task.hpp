#ifndef __TASK_HPP__
#define __TASK_HPP__

#include "../../port/TaskLowLevel.hpp"
#include "../../include/EiTOSConfig.hpp"

class TaskStruct_t : TaskLowLevel_t {
 public:
    int val, id;
    uint8_t Norm() const {
        return this->val;
    }
 private:
};


class SchedulerQueue_t {
 private:
	SchedulerQueue_t();
    TaskStruct_t TaskList[TaskQueueSize];
    uint8_t ActualSize;
 public:
    void init();
    uint8_t size();
    void push(const TaskStruct_t & task);
    TaskStruct_t & front();
    void pop();
};

#endif
