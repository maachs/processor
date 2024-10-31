#ifndef ASSEMBLER_FUNC_
#define ASSEMBLER_FUNC_

#include "Assembler.h"

ErrorCode ScanCode(ASM* assm, char** argv); // TODO assm - rename

void FillRegisters(ASM* assm, char* arg_reg);

void CreateMarks(ASM* assm, char* arg_jmp);

#endif
