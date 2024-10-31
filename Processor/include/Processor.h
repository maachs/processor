#ifndef PROCESSOR_H_
#define PROCESSOR_H_

#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <stdint.h>
#include <sys\stat.h>
#include <string.h>
#include <math.h>

#include "Stack.h"
#include "StackFunc.h"
#include "Enum.h"

const int REGISTERS_NUM = 4;

const int LEN_RAM       = 121;

const int RAM_LINE_LEN  = 11;

struct SPU
{
    int     ip;
    int*    code;
    Stack_t stk;
    Stack_t ret;
    FILE*   out;
    int*    reg;
    int     ram[LEN_RAM];
};


#endif
