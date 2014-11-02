/*
 * main.cpp
 *
 * Created: 2014-10-18 00:35:09
 *  Author: Piotr
 */ 
#include <avr/io.h>
#include <util/delay.h>
#include "OS.hpp"

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

int main() {
	// TP ONLY BEGIN
	DDRB = (1 << PB0)|(1 << PB1)|(1 << PB2)|(1 << PB3);

	TaskLowLevel_t task;
	task.StackStart = TaskAllocate(&Task1, (uint8_t*)0x1000);
	TaskQueue.push(task);

	task.StackStart = TaskAllocate(&Task2, (uint8_t*)0x0F9C);
	TaskQueue.push(task);

	task.StackStart = TaskAllocate(&Task3, (uint8_t*)0x0F38);
	TaskQueue.push(task);
	// TP ONLY END

	InitOS();

	return 0;
}
