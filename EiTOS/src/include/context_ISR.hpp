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

	typedef void ( * TaskType )();

	void OsInit();

	//void TaskCreate(TaskType Task, uint16_t);
	
#endif