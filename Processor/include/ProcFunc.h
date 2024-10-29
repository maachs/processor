#ifndef PROC_FUNC_
#define PROC_FUNC_

#include "Processor.h"

ErrorCode SpuCtor(SPU* spu);

void DtorProc(SPU* spu);

int GetArgPush(SPU* spu);

int* GetArgPop(SPU* spu);

void InitCode(SPU* spu, int code_size, char** argv);

ErrorCode RunCode(SPU* spu, unsigned long int code_size);

ErrorCode DoPush(SPU* spu);

ErrorCode DoAdd(SPU* spu);

ErrorCode DoIn(SPU* spu);

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
