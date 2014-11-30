#include <stdarg.h>
#include <stdio.h>

class Serial {
 private:
    char buff[30];

 public:
    void init(uint16_t baudRate) {
        //TXD0 as output
        DDRD |= (1 << PD1);
        PORTD |= (1 << PD1);
        uint16_t ubrr;
        ubrr = ((F_CPU / 16) / (baudRate)) - 1;
        UBRR0H = static_cast<uint8_t>(ubrr >> 8);
        UBRR0L = static_cast<uint8_t>(ubrr);
        /* Enable receiver and transmitter */
        UCSR0B = (1 << RXEN0) | (1 << TXEN0);
        /* Set frame format: 8data, 1stop bit */
        UCSR0C =   (1 << UCSZ01) | (1 << UCSZ00);
    }
    void sendBuf(char * buf) {
        while (*buf) {
            UDR0 = *buf;
            buf++;
            while ( !(UCSR0A & (1 << UDRE0)) ) {}
        }
    }
uint8_t printf(const char* str, ...) {
        va_list arg;
        int count = 0;

        va_start(arg, str);
        count = vsprintf(this->buff, str, arg);
        this->sendBuf(this->buff);
        va_end(arg);
        return count;
    }
};
