#include <avr/io.h>
#include <util/delay.h>
#include <stdio.h>

#include "OS.hpp"

#include "../drivers/serial.hpp"

Serial serial;

extern "C" {
	#include "HD44780.h"
};

mutex LCD_mtx;
mutex serialMutex;

void Task1() {
	while (1) {
		PORTB ^= (1 << PB2);
		_delay_ms(50);
	}
}

void Task2() {
	while (1) {
		PORTB ^= (1 << PB1);
		_delay_ms(100);
	}
}

void Task3() {
	while (1) {
		PORTB ^= (1 << PB0);
		_delay_ms(200);
	}
}

void Task4(){
	LCD_mtx.take();
	LCD_Initalize();
	LCD_mtx.give();
	uint8_t i=0;
	while(1){
		char temp[20];
		sprintf(temp, "A Iter: %03d", i++);
		
		LCD_mtx.take();
		LCD_GoTo(0,1);
		LCD_WriteText(temp);
		LCD_mtx.give();
		
		serialMutex.take();
		serial.printf(temp);
		serial.printf("\r\n");
		serialMutex.give();
		
		_delay_ms(250);
	}
}

void Task5(){
	LCD_mtx.take();
	LCD_Initalize();
	LCD_mtx.give();
	uint8_t i=0;
	while(1){
		char temp[20];
		sprintf(temp, "B Iter: %03d", i++);
		
		LCD_mtx.take();
		LCD_GoTo(0,0);
		LCD_WriteText(temp);
		LCD_mtx.give();
		
		serialMutex.take();
		serial.printf(temp);
		serial.printf("\r\n");
		serialMutex.give();
		
		_delay_ms(250);
	}
}

int main() {
	// TP ONLY BEGIN
	DDRB = (1 << PB0)|(1 << PB1)|(1 << PB2)|(1 << PB3);
	PORTB = 0;
	serial.init(115200U);
	serial.printf("START\n\r");

	sys::taskCreate(&Task1, 0, 0x10);
	sys::taskCreate(&Task2, 0, 0x10);
	sys::taskCreate(&Task3, 0, 0x10);
	sys::taskCreate(&Task4, 0, 0x50);
	sys::taskCreate(&Task5, 0, 0x50);


	// TP ONLY END

	sys::boot();

	return 0;
}
