#include <stdint.h>
#include "include/schedulerQueue.hpp"

SchedulerQueue_t::SchedulerQueue_t() {
    this->ActualSize = 0;
}

uint8_t SchedulerQueue_t::size() {
    return this->ActualSize;
}

void SchedulerQueue_t::push(const TaskStruct_t & task) {
	const int8_t LastPosition = this->size();
    int8_t InsertionPosition = LastPosition;
    for (int8_t i = 0; i < this->size(); ++i) {
        if ( this->TaskList[i].Norm() >= task.Norm() ) {
            InsertionPosition = i;
            break;
        }
    }
    /*if ( InsertionPosition == LastPosition ) {
        InsertionPosition = this->size();
    }*/
    for (int8_t i = this->size()-1; i >= InsertionPosition; --i) {
        this->TaskList[i+1] = this->TaskList[i];
    }
    this->TaskList[InsertionPosition] = task;
    this->ActualSize++;
}

TaskStruct_t & SchedulerQueue_t::front() {
    return this->TaskList[this->size()-1];
}

void SchedulerQueue_t::pop() {
    this->ActualSize--;
}
