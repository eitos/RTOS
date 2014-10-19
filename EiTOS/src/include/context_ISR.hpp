/*
 * context_ISR.hpp
 *
 * Created: 2014-10-18 15:30:57
 *  Author: Piotr
 */ 
#ifndef context_ISR_HPP
#define context_ISR_HPP

	#include <inttypes.h>

	#define RAMEND_LOW (RAMEND%8)
	#define RAMEND_HIGH (RAMEND>>8)

	extern uint16_t TaskStack;

	typedef void ( * TaskFunctionType )();

	typedef enum {RUNNING, IDLE} TaskStateType;
	typedef enum {LOW, MEDIUM, HIGH} TaskPriorityType;
	typedef struct {
		TaskStateType State;
		TaskPriorityType Priority;
		uint16_t StackStart;
		}TaskType;

	void OsInit();

	void TaskAllocate(TaskFunctionType Task, uint16_t TaskStackStart);

#endif
