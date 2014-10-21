/*
 * context_ISR.hpp
 *
 * Created: 2014-10-18 15:30:57
 *  Author: Piotr
 */ 
#ifndef CONTEXT_ISR_HPP
#define CONTEXT_ISR_HPP

#include <inttypes.h>
#include "port/TaskLowLevel.hpp"

extern uint8_t* CurrentTaskStackAdress;

// TP ONLY BEGIN
extern TaskLowLevel_t TaskList[];
extern volatile uint8_t CurrentProc;
// TP ONLY END

void OsInit();

uint8_t* TaskAllocate(TaskHandler_t Task, uint8_t* TaskStackStart);

void ContextGet(TaskLowLevel_t* Current);

void ContextSet(TaskLowLevel_t* Next);

void TriggerSysTick();

void ResetSysTick();

#endif
