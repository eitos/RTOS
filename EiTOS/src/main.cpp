/*
 * main.cpp
 *
 * Created: 2014-10-18 00:35:09
 *  Author: Piotr
 */ 
#include <avr/io.h>
#include <util/delay.h>
#include "port/context_ISR.hpp"

// TP ONLY BEGIN
TaskLowLevel_t TaskList[3];
volatile uint8_t CurrentProc = 0;

void Task1() {
	while(1) {
		PORTB ^= (1 << PB2);
		_delay_ms(50);
	}
}

void Task2() {
	while(1) {
		PORTB ^= (1 << PB1);
		_delay_ms(100);
	}
}

void Task3() {
	while(1) {
		PORTB ^= (1 << PB0);
		_delay_ms(250);
	}
}
// TP ONLY END

int main() {
	DDRB = (1 << PB0)|(1 << PB1)|(1 << PB2);

	// TP ONLY BEGIN
	TaskList[0].StackStart = TaskAllocate(&Task1, (uint8_t*)0x1000);
	TaskList[1].StackStart = TaskAllocate(&Task2, (uint8_t*)0x0F9C);
	TaskList[2].StackStart = TaskAllocate(&Task3, (uint8_t*)0x0F38);
	// TP ONLY END

	OsInit();

	while(1) {}
	return 0;
}
