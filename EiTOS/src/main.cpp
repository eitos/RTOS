/*
 * main.cpp
 *
 * Created: 2014-10-18 00:35:09
 *  Author: Piotr
 */ 

#include <avr/io.h>
#include <util/delay.h>
#include "include/context_ISR.hpp"

 void Task1(){
	while(1){
		PORTB ^= (1<<PB2);
		_delay_ms(100);
	}
}

void Task2(){
	while(1){
		PORTB ^= (1<<PB1);
		_delay_ms(200);
	}
}

int main(){
	DDRB = (1<<PB0)|(1<<PB1)|(1<<PB2);
	
	TaskAllocate(&Task1,0x1000);
	TaskAllocate(&Task2,0x0F9C);
	
	OsInit();
	/*while(1){
		PORTB ^= (1<<PB0);
		_delay_ms(500);
	}*/
	while(1);
	return 0;
}