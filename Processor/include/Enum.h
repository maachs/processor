#ifndef ENUUMS_
#define ENUUMS_

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
    COMMAND_ERROR        = 8,
    OPEN_FILE_ERROR     = 9
};

enum Arg
{
    IN_STACK      = 1,
    IN_REG        = 2,
    STACK_REG     = 3,
    IN_RAM        = 4,
    RAM_STACK     = 5,
    RAM_REG       = 6,
    RAM_STACK_REG = 7
};

// TODO move the following code into Processor.h
enum Register
{
    Ax = 0,
    Bx = 1,
    Cx = 2,
    Dx = 3
};

enum Commands
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
    CALL  = 13,
    RET   = 14,
    SQRT  = 15,
    VIS   = 16
};

#endif
