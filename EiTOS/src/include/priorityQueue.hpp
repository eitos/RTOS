#ifndef __SCHEDULERQUEUE_HPP__
#define __SCHEDULERQUEUE_HPP__

#include "task.hpp"
#include "EiTOSConfig.hpp"


template<class T, uint8_t maxSize>
class PriorityQueue_t {
 private:
	T elements[maxSize];
	uint8_t ActualSize;
 public:
	PriorityQueue_t();
	void init();
	uint8_t size();
	void push(const T & task);
	T & front();
	void pop();
};


template<class T, uint8_t maxSize>
PriorityQueue_t<T, maxSize>::PriorityQueue_t() {
	this->ActualSize = 0;
}

template<class T, uint8_t maxSize>
uint8_t PriorityQueue_t<T, maxSize>::size() {
	return this->ActualSize;
}

template<class T, uint8_t maxSize>
void PriorityQueue_t<T, maxSize>::push(const T & task) {
	const int8_t LastPosition = this->size();
	int8_t InsertionPosition = LastPosition;
	for (int8_t i = 0; i < this->size(); ++i) {
		if ( !( this->elements[i] < task ) ) {
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

template<class T, uint8_t maxSize>
T & PriorityQueue_t<T, maxSize>::front() {
	return this->elements[this->size()-1];
}

template<class T, uint8_t maxSize>
void PriorityQueue_t<T, maxSize>::pop() {
	this->ActualSize--;
}


#endif
