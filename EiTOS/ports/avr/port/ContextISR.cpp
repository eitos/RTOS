#include <avr/interrupt.h>

#include <OS.hpp>

#include <port/ContextISR.hpp>
#include <port/StackStructure.hpp>
#include <port/consts.hpp>

// pointer to exchange data between Low Level & ProcSysTick
uint8_t * CurrentTaskStackAdress;

void ContextGet(TaskLowLevel_t * Current) {
    Current->StackStart = CurrentTaskStackAdress;
}

void ContextSet(TaskLowLevel_t * Next) {
    CurrentTaskStackAdress = Next->StackStart;
}

void __attribute__((naked)) TriggerSysTick() {
    SysTick();
    asm volatile("sei    \n\t"  // enable interrupts
    "ret                \n\t"); // return form function
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

void ProcSysTickWrapper() {
    sys::ProcSysTick();
}

ISR(TIMER0_COMPA_vect, ISR_NAKED) {
    SysTick();
    asm volatile("reti");
}
