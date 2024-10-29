#ifndef STACK_FUNC_
#define STACK_FUNC_

#include "Stack.h"

ErrorCode StackCtor(Stack_t* stk);

void StackDtor(Stack_t* stk);

void PoisonData(Stack_t* stk);

void StackDump(Stack_t* stk);

void PrintError(Stack_t* stk);

ErrorCode StackPush(Stack_t* stk, StackElem value);

int StackPop(Stack_t* stk);

void ReallocPush(Stack_t* stk);

void ReallocPop(Stack_t* stk);

uint64_t CalcHash(char* data, int size);

ErrorCode VerifyStack(Stack_t* stk);
#endif
