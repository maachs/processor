#ifndef STACK_GLOBALS_H_
#define STACK_GLOBALS_H_

#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <stdint.h>
#include "ErrorCode.h"

//#define DEBUG

typedef double StackElem;

const int CAPACITY_MIN = 10;

const StackElem POISON = -331272.2;

const StackElem CANARY = 0xDED;

struct  Stack_t
{
    #ifdef DEBUG
        StackElem canary1;
        const char* name;
        const char* file;
        const int   line;
    #endif

    StackElem* data;
    int size;
    int capacity;
    int error_code;

    #ifdef DEBUG
    uint64_t struct_hash;
    uint64_t data_hash;
    uint64_t buffer_data_hash;
    uint64_t buffer_struct_hash;
        StackElem canary2;
    #endif
};

enum Step
{
    POP_STEP  = 2,
    PUSH_STEP = 2
};


#ifdef DEBUG
    #define INIT(var) CANARY, #var, __FILE__, __LINE__,
    #define VERIFY_STACK(var1)                                    \
        if (VerifyStack(var1) != SUCCESS)                         \
        {                                                         \
            StackDump(var1, __FILE__, __LINE__, __func__);        \
            StackDtor(var1);                                      \
            assert(0);                                            \
        }
    #define CALC_HASH                                                                                                                                   \
            stk->buffer_struct_hash = CalcHash((char*) stk + sizeof(StackElem) + sizeof(char*) * 2 + sizeof(int), sizeof(StackElem*) + sizeof(int) * 3);\
            stk->buffer_data_hash   = CalcHash((char*) (stk->data), sizeof(double) * stk->capacity);
#else
    #define INIT(var)
    #define VERIFY_STACK(var1, var2)
    #define CALC_HASH
#endif

#endif
