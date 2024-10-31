#ifndef PROC_FUNC_
#define PROC_FUNC_

#include "Processor.h"

ErrorCode SpuCtor(SPU* spu);

void DtorProc(SPU* spu);

void InitCode(SPU* spu, int code_size, char** argv);

ErrorCode RunCode(SPU* spu, unsigned long int code_size, char** argv);

#endif
