/*
 * context_ISR.hpp
 *
 * Created: 2014-10-18 15:30:57
 *  Author: Piotr
 */ 
#ifndef CONTEXT_ISR_HPP
#define CONTEXT_ISR_HPP

	#include <inttypes.h>

	extern uint16_t CurrentTaskStackAdress;

	typedef void ( * TaskFunction_t )();

	typedef enum {TASK_NOT_EXECUTED, TASK_EXECUTED} TaskExecutionLowLevel_t;

	typedef struct {
		uint16_t StackStart;
		TaskExecutionLowLevel_t TaskExecution;
	}TaskLowLevel_t;

	// TP ONLY BEGIN
	extern TaskLowLevel_t TaskList[2];
	extern volatile uint8_t CurrentProc;
	// TP ONLY END

	void OsInit();

	uint16_t TaskAllocate(TaskFunction_t Task, uint16_t TaskStackStart);

	void SwitchContextInISR(TaskLowLevel_t &Current, TaskLowLevel_t &Next);

	void TriggerSysTick();

#endif
