#include <avr/interrupt.h>

#include <OS.hpp>

#include <port/ContextISR.hpp>
#include <port/StackStructure.hpp>
#include <port/consts.hpp>

// pointer to exchange data between Low Level & ProcSysTick
uint8_t * CurrentTaskStackAdress;

// pointer to last created process stack
uint8_t * LastCreatedTaskStackAdress =
    reinterpret_cast<uint8_t *>(RAMEND - OS_STACK_SIZE);

TaskLowLevel_t TaskAllocate(TaskHandler_t taskHandler, uint16_t stackSize) {
    uint8_t * TaskStackStart = LastCreatedTaskStackAdress;

    // allocate memory for task
    LastCreatedTaskStackAdress -= (stackSize + TASK_HEAP_OFFSET);
    *(TaskStackStart - KILL_LOW_OFFSET) = ((uint16_t)(&TaskLowLevelKiller));
    *(TaskStackStart - KILL_HIGH_OFFSET) = ((uint16_t)(&TaskLowLevelKiller)) >> 8;
    *(TaskStackStart - RETI_LOW_OFFSET) = ((uint16_t)taskHandler);
    *(TaskStackStart - RETI_HIGH_OFFSET) = ((uint16_t)taskHandler) >> 8;
    // Set I-bit in order to have interrupts enabled
    *(TaskStackStart - SREG_OFFSET) = (1 << 7);
    *(TaskStackStart - R0_OFFSET) = 0;
    *(TaskStackStart - R1_OFFSET) = 0;
    *(TaskStackStart - R2_OFFSET) = 0;
    *(TaskStackStart - R3_OFFSET) = 0;
    *(TaskStackStart - R4_OFFSET) = 0;
    *(TaskStackStart - R5_OFFSET) = 0;
    *(TaskStackStart - R6_OFFSET) = 0;
    *(TaskStackStart - R7_OFFSET) = 0;
    *(TaskStackStart - R8_OFFSET) = 0;
    *(TaskStackStart - R9_OFFSET) = 0;
    *(TaskStackStart - R10_OFFSET) = 0;
    *(TaskStackStart - R11_OFFSET) = 0;
    *(TaskStackStart - R12_OFFSET) = 0;
    *(TaskStackStart - R13_OFFSET) = 0;
    *(TaskStackStart - R14_OFFSET) = 0;
    *(TaskStackStart - R15_OFFSET) = 0;
    *(TaskStackStart - R16_OFFSET) = 0;
    *(TaskStackStart - R17_OFFSET) = 0;
    *(TaskStackStart - R18_OFFSET) = 0;
    *(TaskStackStart - R19_OFFSET) = 0;
    *(TaskStackStart - R20_OFFSET) = 0;
    *(TaskStackStart - R21_OFFSET) = 0;
    *(TaskStackStart - R22_OFFSET) = 0;
    *(TaskStackStart - R23_OFFSET) = 0;
    *(TaskStackStart - R24_OFFSET) = 0;
    *(TaskStackStart - R25_OFFSET) = 0;
    *(TaskStackStart - R26_OFFSET) = 0;
    *(TaskStackStart - R27_OFFSET) = 0;
    *(TaskStackStart - R28_OFFSET) = 0;
    *(TaskStackStart - R29_OFFSET) = 0;
    *(TaskStackStart - R30_OFFSET) = 0;
    *(TaskStackStart - R31_OFFSET) = 0;

    TaskLowLevel_t task;
    task.StackStart = static_cast<uint8_t *>(TaskStackStart - TASK_HEAP_OFFSET);
	task.StackSize = stackSize + TASK_HEAP_OFFSET;
    return task;  // return address of stack heap in ram copy
}

uint16_t TaskDeallocate(TaskLowLevel_t* Task, uint16_t LowestBytes) {
	uint8_t* TargetRamAddress = Task->StackStart;
	uint8_t* SourceRamAddress = TargetRamAddress - Task->StackSize;
	while(SourceRamAddress>=(uint8_t*)LowestBytes) {
		*TargetRamAddress = *SourceRamAddress;
		TargetRamAddress--;
		SourceRamAddress--;
	}
	return Task->StackSize;
}

void TaskOffsetStack(TaskLowLevel_t* Task, uint16_t Offset){
	Task->StackStart-=Offset;
}

void ContextGet(TaskLowLevel_t * Current) {
    Current->StackStart = CurrentTaskStackAdress;
}

void ContextSet(TaskLowLevel_t * Next) {
    CurrentTaskStackAdress = Next->StackStart;
}

uint16_t TaskGetHeap(const TaskLowLevel_t* Task) {
	return (uint16_t)(Task->StackStart)-Task->StackSize;
}

void __attribute__((naked)) TriggerSysTick() {
    SysTick();
    asm volatile("sei	\n\t"  // enable interrupts
    "ret				\n\t"); // return form function
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

void TaskLowLevelKiller() {
	sys::ActualTaskKill();
    while(1) {}
}

ISR(TIMER0_COMPA_vect, ISR_NAKED) {
    SysTick();
    asm volatile("reti");
}
