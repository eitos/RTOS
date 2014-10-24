#ifndef __TASK_HPP__
#define __TASK_HPP__

#include "port/TaskLowLevel.hpp"
#include "EiTOSConfig.hpp"

class TaskStruct_t {
 public:
	TaskLowLevel_t lowLevelProperties;
	int val, id;
	uint8_t Norm() const {
		return this->val;
	}
	bool operator<(const TaskStruct_t & second) const {
		return (this->Norm() < second.Norm());
	}
 private:
};

#endif
