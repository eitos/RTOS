/*
 * context_ISR.cpp
 *
 * Created: 2014-10-18 14:39:54
 *  Author: Piotr
 */ 

#include "../src/include/context_ISR.hpp"
#include <avr/interrupt.h>

uint16_t TaskStack;
uint16_t* TaskStackPointer=&TaskStack;

#define ContextSave()																					\
	asm volatile(	"push r0						; save r0 on stack							\n\t"	\
					"in r0, __SREG__				; load SREG into temp_reg (r0 just saved)	\n\t"	\
					"push r0						; save SREG on stack						\n\t"	\
					"cli							; clear interrupts (SREG just saved)		\n\t"	\
					"push r1						; save r1...31								\n\t"	\
					"push r2					  \n\t"	\
					"push r3					  \n\t"	\
					"push r4					  \n\t"	\
					"push r5					  \n\t"	\
					"push r6					  \n\t"	\
					"push r7					  \n\t"	\
					"push r8					  \n\t"	\
					"push r9					  \n\t"	\
					"push r10					  \n\t"	\
					"push r11					  \n\t"	\
					"push r12					  \n\t"	\
					"push r13					  \n\t"	\
					"push r14					  \n\t"	\
					"push r15					  \n\t"	\
					"push r16					  \n\t"	\
					"push r17					  \n\t"	\
					"push r18					  \n\t"	\
					"push r19					  \n\t"	\
					"push r20					  \n\t"	\
					"push r21					  \n\t"	\
					"push r22					  \n\t"	\
					"push r23					  \n\t"	\
					"push r24					  \n\t"	\
					"push r25					  \n\t"	\
					"push r26					  \n\t"	\
					"push r27					  \n\t"	\
					"push r28					  \n\t"	\
					"push r29					  \n\t"	\
					"push r30					  \n\t"	\
					"push r31					  \n\t"	\
					"clr __zero_reg__				; clear zero register (r1 - already saved)											\n\t"	\
					"lds r26, TaskStackPointer		; load TaskPointer (LOW) from SRAM into X register									\n\t"	\
					"lds r27, TaskStackPointer + 1	; load TaskPointer (HIGH) from SRAM into X register (SRAM addres)					\n\t"	\
					"in r0, __SP_L__				; load Stack Pointer (LOW) to temp_reg (r0)											\n\t"	\
					"st x+, r0						; save one byte (half-pointer) at address stored in X & post increment X			\n\t"	\
					"in r0, __SP_H__				; load Stack Pointer (HIGH) to temp_reg (r0)										\n\t"	\
					"st x+, r0						; save one byte (half-pointer) at address stored in X & post increment X			\n\t"	\
	)
	
#define ContextRestore()\
	asm volatile(	"lds r26, TaskStackPointer		; load TaskPointer (LOW) from SRAM into X register									\n\t"	\
					"lds r27, TaskStackPointer + 1	; load TaskPointer (HIGH) from SRAM into X register (SRAM addres)					\n\t"	\
					"ld r0, x+						; read one byte (half-pointer) from address stored in X & post increment X			\n\t"	\
					"out __SP_L__, r0				; set Stack Pointer (LOW) to value of temp_reg (r0)									\n\t"	\
					"ld r0, x+						; read one byte (half-pointer) from address stored in X & post increment X			\n\t"	\
					"out __SP_H__, r0				; set Stack Pointer (HIGH) to value of temp_reg (r0)								\n\t"	\
					"pop r31						; restore registers r31...1															\n\t"	\
					"pop r30					  \n\t"	\
					"pop r29					  \n\t"	\
					"pop r28					  \n\t"	\
					"pop r27					  \n\t"	\
					"pop r26					  \n\t"	\
					"pop r25					  \n\t"	\
					"pop r24					  \n\t"	\
					"pop r23					  \n\t"	\
					"pop r22					  \n\t"	\
					"pop r21					  \n\t"	\
					"pop r20					  \n\t"	\
					"pop r19					  \n\t"	\
					"pop r18					  \n\t"	\
					"pop r17					  \n\t"	\
					"pop r16					  \n\t"	\
					"pop r15					  \n\t"	\
					"pop r14					  \n\t"	\
					"pop r13					  \n\t"	\
					"pop r12					  \n\t"	\
					"pop r11					  \n\t"	\
					"pop r10					  \n\t"	\
					"pop r9						  \n\t"	\
					"pop r8						  \n\t"	\
					"pop r7						  \n\t"	\
					"pop r6						  \n\t"	\
					"pop r5						  \n\t"	\
					"pop r4						  \n\t"	\
					"pop r3						  \n\t"	\
					"pop r2						  \n\t"	\
					"pop r1						  \n\t"	\
					"pop r0							; we have stored SREG as second value on stack	\n\t"	\
					"out __SREG__, r0				; so write the value to SREG and...				\n\t"	\
					"pop r0							; ...finally restore r0							\n\t"	\
	)

void OsInit(){
	TCCR0A = (1<<WGM01); // CTC
	OCR0A  = 250-1; // 1 kHz
	TCCR0B = (1<<CS00)|(1<<CS01); // presc 64
	TIMSK0 = (1<<OCIE0A);
	sei();	
}

ISR(TIMER0_COMPA_vect,ISR_NAKED){
	ContextSave();
	// some code - ex change tasks
	// ??warning - allocating too much local variables do can destroy stack of some taks??
	ContextRestore();
	asm volatile("reti");
}