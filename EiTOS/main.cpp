#include <avr/io.h>
#include <util/delay.h>
#include <OS.hpp>
#include <avr/interrupt.h>

#include "../drivers/serial.hpp"

Serial serial;

mutex mutex1;
mutex serialMutex;

void Task1() {
    while (1) {
        _delay_ms(250);
        PORTB ^= (1 << PB0)|(1 << PB1)|(1 << PB2);
    }
}

void Task2() {
    while (1) {
        serial.printf("JAM ODBLOKOWAN!\r\n");
        mutex1.take();
    }
}

int main() {
    serial.init(115200U);
    serial.printf("START\n\r");
    DDRB = (1 << PB0)|(1 << PB1)|(1 << PB2);
    PORTB = 0;

    TCCR1B |= (1 << WGM12)|(1 << CS12)|(1 << CS10);  // CTC, presc 1024
    OCR1A = 15625-1;  // interrupt 1s
    TIMSK1 |= (1 << OCIE1A);

    mutex1.take();
    sys::taskCreate(&Task1, 1, 0xFF);
    sys::taskCreate(&Task2, 1, 0xFF);

    serial.printf("System BOOT\n\r");
    sys::boot();

    return 0;
}

ISR(TIMER1_COMPA_vect) {
    mutex1.give();
}
