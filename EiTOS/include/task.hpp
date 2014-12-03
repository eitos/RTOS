#ifndef __TASK_HPP__
#define __TASK_HPP__

#include "port/port.hpp"
#include "EiTOSConfig.hpp"
#include "priorityQueue.hpp"

const uint8_t TASK_RUNNING = 0;

typedef enum {TASK_S_RUNNING, 
              TASK_S_MUTEX, 
              TASK_S_WAIT, 
              TASK_S_KILL} TaskState_t;

class TaskStruct_t {
 public:
    TaskLowLevel_t lowLevel;
    uint8_t priority;
    uint8_t blockingMutexNr;
    TaskState_t TaskState;
    uint8_t Norm() const {
        return this->priority;
    }
    bool operator<(const TaskStruct_t & second) const {
        if ( this->blockingMutexNr == second.blockingMutexNr ) {
            return (this->priority < second.priority);
        }
        return (this->blockingMutexNr > second.blockingMutexNr);
    }
 private:
};

extern PriorityQueue_t<TaskStruct_t, MAX_TASKS> TaskQueue;

#endif
