#ifndef PROCESSOR_H_
#define PROCESSOR_H_

#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <stdint.h>
#include <sys\stat.h>
#include <string.h>

const char* MACHINE_CODE = "assembler_code.txt";

const int REGISTERS_NUM = 4;

struct SPU
{
    int ip;
    int* code;
    Stack_t stk;
    int* reg;
};

enum Register
{
    Ax = 1,
    Bx = 2,
    Cx = 3,
    Dx = 4
};

enum Comands
{
    PUSH  = 1,
    POP   = 2,
    ADD   = 3,
    SUB   = 4,
    DIV   = 5,
    MUL   = 6,
    OUT   = 7,
    IN    = 8,
    DUMP  = 9,
    JMP   = 10,
    JB    = 11,
    HLT   = 12,
    PUSHR = 13
};

#endif
