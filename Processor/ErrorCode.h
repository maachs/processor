#ifndef ERRORS_
#define ERRORS_

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

#endif
