#ifndef CONSTS_H_
#define CONSTS_H_

#if defined(__EITOS_PORT__) && !defined(__EITOS_AVR_PORT__)
#error "You are using two different ports."
#endif

const uint16_t OS_STACK_SIZE = 0xFF;

#endif /* CONSTS_H_ */
