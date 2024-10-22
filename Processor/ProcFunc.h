#ifndef PROC_FUNC_
#define PROC_FUNC_

#include "Stack.h"
#include "StackFunc.h"
#include "Processor.h"
#include "ErrorCode.h"

const char* MACHINE_CODE = "assembler_code.txt";

ErrorCode SpuCtor(SPU* spu);

void DtorProc(SPU* spu);

ErrorCode RunCode(SPU* spu, unsigned long int code_size);

ErrorCode DoPush(SPU* spu);

ErrorCode DoAdd(SPU* spu);

ErrorCode DoDiv(SPU* spu);

ErrorCode DoPop(SPU* spu);

ErrorCode DoSub(SPU* spu);

ErrorCode DoMul(SPU* spu);

ErrorCode DoOut(SPU* spu);

//ErrorCode DoIn(SPU* spu);

ErrorCode DoDump(SPU* spu, unsigned long int code_size);

ErrorCode DoJb(SPU* spu);

ErrorCode DoJmp(SPU* spu);

ErrorCode DoPushr(SPU* spu);

#endif
