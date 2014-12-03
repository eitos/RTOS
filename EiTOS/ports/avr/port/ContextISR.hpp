#ifndef CONTEXT_ISR_HPP
#define CONTEXT_ISR_HPP

#include <inttypes.h>
#include "port/TaskLowLevel.hpp"

#if defined(__EITOS_PORT__) && !defined(__EITOS_AVR_PORT__)
#error "You are using two different ports."
#endif

extern uint8_t* CurrentTaskStackAdress;

TaskLowLevel_t TaskAllocate(TaskHandler_t Task, uint16_t StackSize);

void ContextGet(TaskLowLevel_t* Current);

void ContextSet(TaskLowLevel_t* Next);

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

inline void __attribute__((always_inline)) ExecutePendingTask() {
    ContextRestore();
    asm volatile("ret");
}

void ProcSysTickWrapper();

inline void __attribute__((always_inline)) SysTick() {
    ContextSave();
    SwitchToOsStack();

    ProcSysTickWrapper();

    ContextRestore();
}

void __attribute__((naked)) TriggerSysTick();

void ResetSysTick();

void InitSysTick();

extern void ProcSysTick();

#endif
