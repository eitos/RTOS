/*
 * context_ISR.cpp
 *
 * Created: 2014-10-18 14:39:54
 *  Author: Piotr
 */ 
#include <avr/interrupt.h>
#include "../src/include/context_ISR.hpp"
#include "../src/include/StackStructure.hpp"


uint16_t TaskStack;

uint16_t ten_drugi;  // TP ONLY

uint16_t* TaskStackPointer=&TaskStack;

uint8_t task_no_set = 2;  // TP ONLY

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
	"push r31						\n\t"
	"clr __zero_reg__				\n\t"  // clear zero register (r1 - already saved)
	"lds r26, TaskStackPointer		\n\t"  // load TaskPointer (LOW) from SRAM into X register
	"lds r27, TaskStackPointer + 1	\n\t"  // load TaskPointer (HIGH) from SRAM into X register (SRAM addres)
	"in r0, __SP_L__				\n\t"  // load Stack Pointer (LOW) to temp_reg (r0)
	"st x+, r0						\n\t"  // save one byte (half-pointer) at address stored in X & post increment X
	"in r0, __SP_H__				\n\t"  // load Stack Pointer (HIGH) to temp_reg (r0)
	"st x+, r0						\n\t"  // save one byte (half-pointer) at address stored in X & post increment X
	);
}



inline void __attribute__((always_inline)) ContextRestore() {
	asm volatile("lds r26, TaskStackPointer	\n\t"  // load TaskPointer (LOW) from SRAM into X register
	"lds r27, TaskStackPointer + 1			\n\t"  // load TaskPointer (HIGH) from SRAM into X register (SRAM addres)
	"ld r0, x+								\n\t"  // read one byte (half-pointer) from address stored in X & post increment X	
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
	);
}

inline void __attribute__((always_inline)) StackRamEnd() {
	asm volatile("ldi r16,0xFF	\n\t"
	"out __SP_L__,r16				\n\t"
	"ldi r16,0x10				\n\t"
	"out __SP_H__,r16			\n\t"
	);
}

uint16_t TaskAllocate(TaskFunctionType Task, uint16_t TaskStackStart) {
	uint8_t* RamPtr = (uint8_t*)TaskStackStart;
	*(RamPtr-RETI_ADDR_HI) = ((uint16_t)Task) >> 8;
	*(RamPtr-RETI_ADDR_LOW) = ((uint16_t)Task);
	*(RamPtr-SREG_CP) = (1 << 7);  // Set I-bit in order to have interrupts enabled
	*(RamPtr-R0_C) = 0;
	*(RamPtr-R1_C) = 0;
	*(RamPtr-R2_C) = 0;
	*(RamPtr-R3_C) = 0;
	*(RamPtr-R4_C) = 0;
	*(RamPtr-R5_C) = 0;
	*(RamPtr-R6_C) = 0;
	*(RamPtr-R7_C) = 0;
	*(RamPtr-R8_C) = 0;
	*(RamPtr-R9_C) = 0;
	*(RamPtr-R10_C) = 0;
	*(RamPtr-R11_C) = 0;
	*(RamPtr-R12_C) = 0;
	*(RamPtr-R13_C) = 0;
	*(RamPtr-R14_C) = 0;
	*(RamPtr-R15_C) = 0;
	*(RamPtr-R16_C) = 0;
	*(RamPtr-R17_C) = 0;
	*(RamPtr-R18_C) = 0;
	*(RamPtr-R19_C) = 0;
	*(RamPtr-R20_C) = 0;
	*(RamPtr-R21_C) = 0;
	*(RamPtr-R22_C) = 0;
	*(RamPtr-R23_C) = 0;
	*(RamPtr-R24_C) = 0;
	*(RamPtr-R25_C) = 0;
	*(RamPtr-R26_C) = 0;
	*(RamPtr-R27_C) = 0;
	*(RamPtr-R28_C) = 0;
	*(RamPtr-R29_C) = 0;
	*(RamPtr-R30_C) = 0;
	*(RamPtr-R31_C) = 0;

	return TaskStackStart-STACK_HEAP;
}

void OsInit() {
	TCCR0A = (1 << WGM01);  // CTC
	OCR0A  = 250-1;  // 1 kHz
	TCCR0B = (1 << CS00)|(1 << CS01);  // presc 64
	TIMSK0 = (1 << OCIE0A);
	sei();
}

void SwitchContextInISR(volatile TaskLowLevelType* Current,
		volatile TaskLowLevelType* Next) {
	if(Current->TaskExecution == TASK_EXECUTED) Current->StackStart = TaskStack;
	TaskStack = Next->StackStart;
	if(Next->TaskExecution == TASK_NOT_EXECUTED)
		Next->TaskExecution = TASK_EXECUTED;
}

void TriggerSysTick() {
	TCNT0 = OCR0A-1;
}

ISR(TIMER0_COMPA_vect, ISR_NAKED) {
	ContextSave();
	StackRamEnd();

	// TP ONLY BEGIN
	SwitchContextInISR(&TaskList[CurrentProc], &TaskList[!CurrentProc]);
	CurrentProc=!CurrentProc;
	// TP ONLY END

	ContextRestore();
	asm volatile("reti");
}
