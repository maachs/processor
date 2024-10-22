#include "Stack.h"
#include "StackFunc.h"
#include "Processor.h"
#include "ProcFunc.h"
#include "ErrorCode.h"
#include "ProcFunc.h"
#include "AssemblerFunc.h"

int main()
{
    //SPU spu = {};
    //struct stat buffer = {};

    stat(CODE_FILE, &buffer);

    if (SpuCtor(&spu) != SUCCESS)
    {
        StackDtor(&spu.stk);
        return -1;
    }

    ScanCode(&spu, buffer.st_size);


    return 0;
}

