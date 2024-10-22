#ifndef ASSEMBLER_FUNC_
#define ASSEMBLER_FUNC_

#include "Assembler.h"

const int MAX_COMMAND_LEN = 6;

//const char* CODE_FILE = "comands.txt";
//const char* MACHINE_CODE = "assembler_code.txt";
ErrorCode ScanCode(ASM* assm, char** argv);

void FillRegisters(ASM* assm, char* arg_reg, int com);

void CreateMarks(ASM* assm, char* arg_jmp);

#endif
