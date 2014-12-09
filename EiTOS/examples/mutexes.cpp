#include <avr/io.h>
#include <util/delay.h>
#include <OS.hpp>
#include <avr/interrupt.h>

#include "../drivers/serial.hpp"

Serial serial;

mutex mutex1;
mutex serialMutex;

void Task1() {
    static uint8_t count = 0;
    while (1) {
        PORTB ^= (1 << PB2);
        
        serialMutex.take();
        serial.printf("Test %d\r\n", count++);
        serialMutex.give();
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

void Task4() {
    mutex1.take();
    for(uint8_t i = 0; i < 10; ++i) {
        serialMutex.take();
        serial.printf("mutex taken %d!\n\r",i);
        serialMutex.give();
        
        PORTB ^= (1 << PB0);
        _delay_ms(200);
    }
    mutex1.take(); //can't take second time - will halt here!
    while(1) {
        serialMutex.take();
        serial.printf("error !\n\r");
        serialMutex.give();
    }
}


void mainTask() {
    mutex1.take();
    serialMutex.give();
    sys::taskCreate(&Task1, 1, 0xFF);
    sys::taskCreate(&Task2, 1, 0x20);
    sys::taskCreate(&Task3, 1, 0x20);
    sys::taskCreate(&Task4, 2, 0x20);
    
    for(uint8_t i = 20; i > 0; --i) {
        serialMutex.take();
        serial.printf("Waiting... %d\r\n", i);
        serialMutex.give();
        
        _delay_ms(50);
    }
    mutex1.give(); //will unlock Task4 - with higer priority
    
    while(1) {
        serialMutex.take();
        serial.printf("idle task\n\r");
        serialMutex.give();
    }
}

int main() {
    serial.init(115200U);
    serial.printf("START\n\r");
    DDRB = (1 << PB0)|(1 << PB1)|(1 << PB2);
    PORTB = 0;

    sys::taskCreate(&mainTask, 1, 0xFF);
    
    serial.printf("System BOOT\n\r");
    sys::boot();

    return 0;
}
