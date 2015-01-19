#ifndef STACKSTRUCTURE_HPP_
#define STACKSTRUCTURE_HPP_

#if defined(__EITOS_PORT__) && !defined(__EITOS_AVR_PORT__)
#error "You are using two different ports."
#endif

#define KILL_LOW_OFFSET      0
#define KILL_HIGH_OFFSET     1
#define RETI_LOW_OFFSET      2
#define RETI_HIGH_OFFSET     3
#define SREG_OFFSET          5
#define R0_OFFSET            4
#define R1_OFFSET            6
#define R2_OFFSET            7
#define R3_OFFSET            8
#define R4_OFFSET            9
#define R5_OFFSET            10
#define R6_OFFSET            11
#define R7_OFFSET            12
#define R8_OFFSET            13
#define R9_OFFSET            14
#define R10_OFFSET           15
#define R11_OFFSET           16
#define R12_OFFSET           17
#define R13_OFFSET           18
#define R14_OFFSET           19
#define R15_OFFSET           20
#define R16_OFFSET           21
#define R17_OFFSET           22
#define R18_OFFSET           23
#define R19_OFFSET           24
#define R20_OFFSET           25
#define R21_OFFSET           26
#define R22_OFFSET           27
#define R23_OFFSET           28
#define R24_OFFSET           29
#define R25_OFFSET           30
#define R26_OFFSET           31
#define R27_OFFSET           32
#define R28_OFFSET           33
#define R29_OFFSET           34
#define R30_OFFSET           35
#define R31_OFFSET           36
#define TASK_HEAP_OFFSET     37

#endif /* STACKSTRUCTURE_HPP_ */
