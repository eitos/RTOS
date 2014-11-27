#ifndef __PRIORITYQUEUE_HPP__
#define __PRIORITYQUEUE_HPP__

#include <inttypes.h>
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
    T & operator[](uint8_t index);
    void pop();
    void remove(uint8_t index);
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
    const uint8_t LastPosition = this->size();
    uint8_t InsertionPosition = LastPosition;
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

template<class T, uint8_t MaxSize>
T & PriorityQueue_t<T, MaxSize>::operator[](uint8_t index) {
    return this->elements[index];
}

template<class T, uint8_t MaxSize>
void PriorityQueue_t<T, MaxSize>::remove(uint8_t index) {
    for (uint8_t i = index; i < this->ActualSize; i++) {
        this->elements[i] = this->elements[i+1];
    }
    this->ActualSize--;
}


#endif
