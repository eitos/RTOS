/*
 * context_ISR.cpp
 *
 * Created: 2014-10-18 14:39:54
 *  Author: Piotr
 */ 
#include <avr/interrupt.h>
#include "context_ISR.hpp"
#include "StackStructure.hpp"
#include "priorityQueue.hpp"

uint8_t* CurrentTaskStackAdress;

uint8_t started = 0;  // TP ONLY

inline void __attribute__((always_inline)) ContextSave() {
	asm volatile("push r0			\n\t"  // save r0 on stack	
	"in r0, __SREG__				\n\t"  // load SREG into temp_reg (r0 just saved)
	"push r0						\n\t"  // save SREG on stack
	"cli							\n\t"  // clear interrupts (SREG just saved)
	"push r1						\n\t"  // save r1...31
	"push r2						\n\t"
	"push r3						\n\t"
	"push r4						\n\t"
	"push r5						\n\t"
	"push r6						\n\t"
	"push r7						\n\t"
	"push r8						\n\t"
	"push r9						\n\t"
	"push r10						\n\t"
	"push r11						\n\t"
	"push r12						\n\t"
	"push r13						\n\t"
	"push r14						\n\t"
	"push r15						\n\t"
	"push r16						\n\t"
	"push r17						\n\t"
	"push r18						\n\t"
	"push r19						\n\t"
	"push r20						\n\t"
	"push r21						\n\t"
	"push r22						\n\t"
	"push r23						\n\t"
	"push r24						\n\t"
	"push r25						\n\t"
	"push r26						\n\t"
	"push r27						\n\t"
	"push r28						\n\t"
	"push r29						\n\t"
	"push r30						\n\t"
	"push r31						\n\t");
	// operand passing will automatically load the address
	// into X register pairs (R27 & R26)
	asm volatile(
	"in r0, __SP_L__				\n\t"  // load Stack Pointer (LOW) to temp_reg (r0)
	"st x+, r0						\n\t"  // save one byte (half-pointer) at address stored in X & post increment X
	"in r0, __SP_H__				\n\t"  // load Stack Pointer (HIGH) to temp_reg (r0)
	"st x+, r0						\n\t"  // save one byte (half-pointer) at address stored in X & post increment X
	"clr __zero_reg__				\n\t"  // clear zero register (r1 - already saved)
	:: "x"(&CurrentTaskStackAdress));
}



inline void __attribute__((always_inline)) ContextRestore() {
	// operand passing will automatically load the address
	// into X register pairs (R27 & R26)
	asm volatile("ld r0, x+								\n\t"  // read one byte (half-pointer) from address stored in X & post increment X	
	"out __SP_L__, r0						\n\t"  // set Stack Pointer (LOW) to value of temp_reg (r0)
	"ld r0, x+								\n\t"  // read one byte (half-pointer) from address stored in X & post increment X
	"out __SP_H__, r0						\n\t"  // set Stack Pointer (HIGH) to value of temp_reg (r0)
	"pop r31								\n\t"  // restore registers r31...1
	"pop r30								\n\t"
	"pop r29								\n\t"
	"pop r28								\n\t"
	"pop r27								\n\t"
	"pop r26								\n\t"
	"pop r25								\n\t"
	"pop r24								\n\t"
	"pop r23								\n\t"
	"pop r22								\n\t"
	"pop r21								\n\t"
	"pop r20								\n\t"
	"pop r19								\n\t"
	"pop r18								\n\t"
	"pop r17								\n\t"
	"pop r16								\n\t"
	"pop r15								\n\t"
	"pop r14								\n\t"
	"pop r13								\n\t"
	"pop r12								\n\t"
	"pop r11								\n\t"
	"pop r10								\n\t"
	"pop r9									\n\t"
	"pop r8									\n\t"
	"pop r7									\n\t"
	"pop r6									\n\t"
	"pop r5									\n\t"
	"pop r4									\n\t"
	"pop r3									\n\t"
	"pop r2									\n\t"
	"pop r1									\n\t"
	"pop r0									\n\t"  // we have stored SREG as second value on stack
	"out __SREG__, r0						\n\t"  // so write the value to SREG and...
	"pop r0									\n\t"  // ...finally restore r0
	:: "x"(&CurrentTaskStackAdress));
}

inline void __attribute__((always_inline)) SwitchToOsStack() {
	asm volatile("ldi r16,0xFF	\n\t"
	"out __SP_L__,r16				\n\t"
	"ldi r16,0x10				\n\t"
	"out __SP_H__,r16			\n\t"
	);
}

uint8_t* TaskAllocate(TaskHandler_t Task, uint8_t* TaskStackStart) {
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

	return TaskStackStart-STACK_HEAP;  // return address of stack heap in ram copy
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

inline void __attribute__((always_inline)) ExecutePendingTask() {
	ContextRestore();
	asm volatile("ret");
}

extern PriorityQueue_t<TaskLowLevel_t, 10> TaskQueue;

void OsInit() {
	TCCR0A = (1 << WGM01);  // CTC
	OCR0A  = 250-1;  // 1 kHz
	TCCR0B = (1 << CS00)|(1 << CS01);  // presc 64
	TIMSK0 = (1 << OCIE0A);

	TaskLowLevel_t & t = TaskQueue.front();
	ContextSet(&t);
	TaskQueue.pop();  // first task pop

	// Now we will execute this task (jump to first task)
	ExecutePendingTask();  // This will also enable interrupts

	// This will never execute, aber zicher ist zicher!
	while(1) {}
}

ISR(TIMER0_COMPA_vect, ISR_NAKED) {
	ContextSave();
	SwitchToOsStack();

	// TP ONLY BEGIN
	PORTB |= (1 << PB3);
	TaskLowLevel_t now;
	ContextGet(&now);
	TaskQueue.push(now);
	now = TaskQueue.front();
	ContextSet(&now);
	TaskQueue.pop();

	PORTB &= ~(1 << PB3);
	// TP ONLY END

	ContextRestore();
	asm volatile("reti");
}
