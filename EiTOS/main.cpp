#include <avr/io.h>
#include <util/delay.h>
#include <stdio.h>

#include "OS.hpp"

extern "C" {
	#include "HD44780.h"
};
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
	LCD_Initalize();
	LCD_WriteText("Witaj EITOS");
	uint8_t i=0;
	while(1){
		char temp[20];
		sprintf(temp, "Iter: %03d", i++);
		LCD_GoTo(0,1);
		LCD_WriteText(temp);
		_delay_ms(250);
	}
}

int main() {
	// TP ONLY BEGIN
	DDRB = (1 << PB0)|(1 << PB1)|(1 << PB2)|(1 << PB3);
	PORTB = 0;

	sys::taskCreate(&Task1, 0, 0x10);
	sys::taskCreate(&Task2, 0, 0x10);
	sys::taskCreate(&Task3, 0, 0x10);
	sys::taskCreate(&Task4, 0, 0x50);


	// TP ONLY END

	sys::boot();

	return 0;
}
