#include <avr/io.h>
#include <util/delay.h>
#include <OS.hpp>
#include "drivers/serial.hpp"

Serial serial;

void Task1() {
    while (1) {
        PORTB ^= (1 << PB2);
        _delay_ms(50);
        serial.sendBuf("test!");
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

int main() {
    // TP ONLY BEGIN
    serial.init(9600U);
    DDRA |= (1 << PA0);
    DDRB = (1 << PB0)|(1 << PB1)|(1 << PB2)|(1 << PB3);
    PORTB = 0;

    /*while(1) {
        serial.printf("test!\n\r");
        _delay_ms(100);
    }*/
    sys::taskCreate(&Task1, 0, 0x10);
    sys::taskCreate(&Task2, 0, 0x10);
    sys::taskCreate(&Task3, 0, 0x10);


    // TP ONLY END

    sys::boot();

    return 0;
    }
