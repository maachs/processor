#ifndef PROCESSOR_FUNC_
#define PROCESSOR_FUNC_

#include "Stack.h"
#include "Processor.h"
#include "ErrorCode.h"

ErrorCode SpuCtor(SPU* spu);

ErrorCode ScanCode(SPU* spu, unsigned long int code_size);

void DtorProc(SPU* spu);

void RunCode(SPU* spu);

#endif
