#ifndef ASSEMBLER_
#define ASSEMBLER_

#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <string.h>
#include <sys\stat.h>

const int MAX_REG_LEN = 3;
const int MAX_LABLES_LEN = 7;
const int MAX_AMOUNT_MARKS = 10;

struct Marks
{
    char* lables;
    int address;
};

struct ASM
{
    FILE* commands;
    FILE* machine_code;
    int count_commands;
    int count_lables;
    Marks* mark[MAX_AMOUNT_MARKS];
};

enum ErrorCode
{
    READ_CODE_ERROR     = 1,
    SCAN_CODE_ERROR     = 2,
    STK_ERROR           = 3,
    SUCCESS             = 0,
    SIZE_ERROR          = 6,
    CAPACITY_ERROR      = 7,
    CAPACITY_EQUAL_SIZE = 5,
    CALLOC_ERROR        = 10,
    COMAND_ERROR        = 8,
    OPEN_FILE_ERROR     = 9
};

enum Register
{
    Ax = 1,
    Bx = 2,
    Cx = 3,
    Dx = 4
};

enum Comands
{
    PUSH  = 1,
    POP   = 2,
    ADD   = 3,
    SUB   = 4,
    DIV   = 5,
    MUL   = 6,
    OUT   = 7,
    IN    = 8,
    DUMP  = 9,
    JMP   = 10,
    JB    = 11,
    HLT   = 12,
    PUSHR = 13
};
#endif
