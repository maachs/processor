#ifndef PROCESSOR_H_
#define PROCESSOR_H_

#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <stdint.h>
#include <sys\stat.h>
#include <string.h>

const char* CODE_FILE = "comands.txt";
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
    Ax = 0x01,
    Bx = 0x02,
    Cx = 0x03,
    Dx = 0x04
};

enum Comands
{
    PUSH = 0x01,
    POP  = 0x02,
    ADD  = 0x03,
    SUB  = 0x04,
    DIV  = 0x05,
    MUL  = 0x06,
    OUT  = 0x07,
    IN   = 0x08,
    DUMP = 0x09,
    JMP  = 0x0A,
    JB   = 0x0B,
    HLT  = 0x0C
};

#endif
