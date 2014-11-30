#include <avr/io.h>
#include <util/delay.h>
#include <OS.hpp>
#include <avr/interrupt.h>
#include "drivers/serial.hpp"

Serial serial;

void Task1() {
    while (1) {
        static uint8_t i = 0;
        PORTB ^= (1 << PB2);
        _delay_ms(50);
        serial.printf("Test %d\r\n", i);
        i++;
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
    DDRB = (1 << PB0)|(1 << PB1)|(1 << PB2);
    PORTB = 0;

    sys::taskCreate(&Task1, 0, 0xFF);
    sys::taskCreate(&Task2, 0, 0x10);
    sys::taskCreate(&Task3, 0, 0x10);


    // TP ONLY END

    sys::boot();

    return 0;
}
