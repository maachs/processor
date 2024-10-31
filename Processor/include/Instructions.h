#ifndef INSTRUCTION_H_
#define INSTRUCTION_H_

#include "Processor.h"
#include "Stack.h"

ErrorCode DoPush(SPU* spu);

int GetArgPush(SPU* spu);

int* GetArgPop(SPU* spu);

ErrorCode DoSqrt(SPU* spu);

ErrorCode DoVis(SPU* spu);

ErrorCode DoAdd(SPU* spu);

ErrorCode DoIn(SPU* spu);

ErrorCode DoDiv(SPU* spu);

ErrorCode DoPop(SPU* spu);

ErrorCode DoSub(SPU* spu);

ErrorCode DoMul(SPU* spu);

ErrorCode DoOut(SPU* spu);

ErrorCode DoRet(SPU* spu);

ErrorCode DoCall(SPU* spu);

ErrorCode DoDump(SPU* spu, unsigned long int code_size);

ErrorCode DoJb(SPU* spu);

ErrorCode DoJmp(SPU* spu);

#endif
