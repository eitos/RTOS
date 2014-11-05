#include <avr/interrupt.h>
#include "context_ISR.hpp"
#include "StackStructure.hpp"
#include "consts.h"

uint8_t* CurrentTaskStackAdress = (uint8_t *)(RAMEND - OS_STACK_SIZE);

TaskLowLevel_t TaskAllocate(TaskHandler_t Task, uint16_t StackSize) {
	uint8_t * TaskStackStart = CurrentTaskStackAdress;
	CurrentTaskStackAdress -= StackSize;
	*(TaskStackStart-RETI_ADDR_HI) = ((uint16_t)Task) >> 8;
	*(TaskStackStart-RETI_ADDR_LOW) = ((uint16_t)Task);
	// Set I-bit in order to have interrupts enabled
	*(TaskStackStart-SREG_CP) = (1 << 7);
	*(TaskStackStart-R0_C) = 0;
	*(TaskStackStart-R1_C) = 0;
	*(TaskStackStart-R2_C) = 0;
	*(TaskStackStart-R3_C) = 0;
	*(TaskStackStart-R4_C) = 0;
	*(TaskStackStart-R5_C) = 0;
	*(TaskStackStart-R6_C) = 0;
	*(TaskStackStart-R7_C) = 0;
	*(TaskStackStart-R8_C) = 0;
	*(TaskStackStart-R9_C) = 0;
	*(TaskStackStart-R10_C) = 0;
	*(TaskStackStart-R11_C) = 0;
	*(TaskStackStart-R12_C) = 0;
	*(TaskStackStart-R13_C) = 0;
	*(TaskStackStart-R14_C) = 0;
	*(TaskStackStart-R15_C) = 0;
	*(TaskStackStart-R16_C) = 0;
	*(TaskStackStart-R17_C) = 0;
	*(TaskStackStart-R18_C) = 0;
	*(TaskStackStart-R19_C) = 0;
	*(TaskStackStart-R20_C) = 0;
	*(TaskStackStart-R21_C) = 0;
	*(TaskStackStart-R22_C) = 0;
	*(TaskStackStart-R23_C) = 0;
	*(TaskStackStart-R24_C) = 0;
	*(TaskStackStart-R25_C) = 0;
	*(TaskStackStart-R26_C) = 0;
	*(TaskStackStart-R27_C) = 0;
	*(TaskStackStart-R28_C) = 0;
	*(TaskStackStart-R29_C) = 0;
	*(TaskStackStart-R30_C) = 0;
	*(TaskStackStart-R31_C) = 0;

	TaskLowLevel_t task;
	task.StackStart = (uint8_t *)(TaskStackStart-STACK_HEAP);
	return task;  // return address of stack heap in ram copy
}

void ContextGet(TaskLowLevel_t* Current) {
	Current->StackStart = CurrentTaskStackAdress;
}

void ContextSet(TaskLowLevel_t *Next) {
	CurrentTaskStackAdress = Next->StackStart;
}

void TriggerSysTick() {
	TCNT0 = OCR0A-1;
}

void ResetSysTick() {
	TCNT0 = 0;
	// GTCCR |= (1 << PSRSYNC);  // Reset T0 & T1 prescallers
}

void InitSysTick() {
	TCCR0A = (1 << WGM01);  // CTC
	OCR0A  = 250-1;  // 1 kHz
	TCCR0B = (1 << CS00)|(1 << CS01);  // presc 64
	TIMSK0 = (1 << OCIE0A);
}


ISR(TIMER0_COMPA_vect, ISR_NAKED) {
	ContextSave();
	SwitchToOsStack();

	ProcSysTick();

	ContextRestore();
	asm volatile("reti");
}
