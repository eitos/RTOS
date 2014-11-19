#ifndef __PRIORITYQUEUE_HPP__
#define __PRIORITYQUEUE_HPP__

#include "task.hpp"
#include "EiTOSConfig.hpp"


template<class T, uint8_t MaxSize>
class PriorityQueue_t {
 private:
    T elements[MaxSize];
    uint8_t ActualSize;
 public:
    PriorityQueue_t();
    void init();
    uint8_t size();
    void push(const T & task);
    T & front();
    void pop();
};


template<class T, uint8_t MaxSize>
PriorityQueue_t<T, MaxSize>::PriorityQueue_t() {
    this->ActualSize = 0;
}

template<class T, uint8_t MaxSize>
uint8_t PriorityQueue_t<T, MaxSize>::size() {
    return this->ActualSize;
}

template<class T, uint8_t MaxSize>
void PriorityQueue_t<T, MaxSize>::push(const T & task) {
    const int8_t LastPosition = this->size();
    int8_t InsertionPosition = LastPosition;
    for (int8_t i = 0; i < this->size(); ++i) {
        if (!(this->elements[i] < task)) {
            InsertionPosition = i;
            break;
        }
    }
    for (int8_t i = this->size()-1; i >= InsertionPosition; --i) {
        this->elements[i+1] = this->elements[i];
    }
    this->elements[InsertionPosition] = task;
    this->ActualSize++;
}

template<class T, uint8_t MaxSize>
T & PriorityQueue_t<T, MaxSize>::front() {
    return this->elements[this->size()-1];
}

template<class T, uint8_t MaxSize>
void PriorityQueue_t<T, MaxSize>::pop() {
    this->ActualSize--;
}


#endif
