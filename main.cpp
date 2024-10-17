#include "Stack.h"
#include "StackFunc.h"
#include "Processor.h"
#include "ProcessorFunc.h"
#include "ErrorCode.h"

int main()
{
    SPU spu = {};
    struct stat buffer = {};

    stat(CODE_FILE, &buffer);

    if (SpuCtor(&spu) != SUCCESS)
    {
        StackDtor(&spu.stk);
        return CALLOC_ERROR;
    }

    ScanCode(&spu, buffer.st_size);

    DtorProc(&spu);

    return 0;
}

ErrorCode SpuCtor(SPU* spu)
{
    assert(spu);

    StackCtor(&spu->stk);

    spu->ip = 0;

    (spu->reg) = (int*) calloc(REGISTERS_NUM, sizeof(int));

    if (spu->stk.data == NULL || spu->reg == NULL)
    {
        return CALLOC_ERROR;
    }

    return SUCCESS;
}

ErrorCode ScanCode(SPU* spu, unsigned long int code_size)
{
    assert(spu);

    FILE* comands = fopen(CODE_FILE, "r");
    FILE* machine_code = fopen(MACHINE_CODE, "rw");

    if (comands == NULL)
    {
        printf("Cannot open file");
        return SCAN_CODE_ERROR;
    }

    char* scan_comands_char = (char*) calloc(code_size, sizeof(char));
    int arg = 0;

    while (fscanf(comands, "%s", scan_comands_char) != EOF)
    {
        const char* scan_comands = scan_comands_char;

        if(stricmp(scan_comands, "push") == 0)
        {
            fscanf(comands, "%d", &arg);
            fprintf(machine_code, "%x %x\n", PUSH, arg);
        }
        if(stricmp(scan_comands, "add") == 0)
        {
            fprintf(machine_code, "%x\n", ADD);
        }
        if(stricmp(scan_comands, "sub") == 0)
        {
            fprintf(machine_code, "%x\n", SUB);
        }
        if(stricmp(scan_comands, "div") == 0)
        {
            fprintf(machine_code, "%x\n", DIV);
        }
        if(stricmp(scan_comands, "mul") == 0)
        {
            fprintf(machine_code, "%x\n", MUL);
        }
        if(stricmp(scan_comands, "out") == 0)
        {
            fprintf(machine_code, "%x\n", OUT);
        }
        if(stricmp(scan_comands, "in") == 0)
        {
            fprintf(machine_code, "%x\n", IN);
        }
        if(stricmp(scan_comands, "hlt") == 0)
        {
            fprintf(machine_code, "%x\n", HLT);
        }
    }

    fclose(comands);

    free(scan_comands_char);
    scan_comands_char = NULL;

    spu->code = (int*) calloc(code_size, sizeof(int));

    for(unsigned long int elem = 0; elem < code_size; elem++)
    {
        fscanf(machine_code, "%x", &spu->code[elem]);
    }

    fclose(machine_code);

    return SUCCESS;
}

void DtorProc(SPU* spu)
{
    assert(spu);

    StackDtor(&spu->stk);

    free(spu->reg);
    spu->reg = NULL;
}
