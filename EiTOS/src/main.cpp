/*
 * main.cpp
 *
 * Created: 2014-10-18 00:35:09
 *  Author: Piotr
 */ 

#include <avr/io.h>
#include <util/delay.h>

int main() {
	DDRB = (1 << PB0);
	while(1) {
		PORTB ^= (1 << PB0);
		_delay_ms(500);
	}
	return 0;
}
