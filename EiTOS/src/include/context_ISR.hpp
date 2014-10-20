/*
 * context_ISR.hpp
 *
 * Created: 2014-10-18 15:30:57
 *  Author: Piotr
 */ 
#ifndef context_ISR_HPP
#define context_ISR_HPP

	#include <inttypes.h>

	extern uint16_t TaskStack;

	typedef void ( * TaskFunctionType )();

	typedef enum {TASK_NOT_EXECUTED, TASK_EXECUTED} TaskExecutionLowLevelType;

	typedef struct {
		uint16_t StackStart;
		TaskExecutionLowLevelType TaskExecution;
	}TaskLowLevelType;

	// TP ONLY BEGIN
	extern volatile TaskLowLevelType TaskList[2];
	extern volatile uint8_t CurrentProc;
	// TP ONLY END

	void OsInit();

	uint16_t TaskAllocate(TaskFunctionType Task, uint16_t TaskStackStart);

	void SwitchContextInISR(TaskLowLevelType* Current, TaskLowLevelType* Next);

#endif
