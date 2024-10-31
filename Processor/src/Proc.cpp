#include "ProcFunc.h"
#include <Instructions.h>

int main(int argc, char** argv)
{
    SPU spu = {};
    struct stat buffer = {};

    if(argc != 3)
    {
        printf("argc error");
        return -1;
    }

    stat(argv[1], &buffer);

    InitCode(&spu, buffer.st_size, argv);

    SpuCtor(&spu);

    spu.out = fopen(argv[2], "w");

    if(RunCode(&spu, buffer.st_size) != SUCCESS) return -1;

    fclose(spu.out);

    return 0;

}

void InitCode(SPU* spu, int code_size, char** argv)
{
    assert(spu);

    FILE* asm_code = fopen(argv[1], "r");

    if(asm_code == NULL)
    {
        printf("Cannot open asm file");
        spu->stk.error_code = OPEN_FILE_ERROR;
    }

    spu->code = (int*) calloc(code_size, sizeof(int));

    if(spu->code == NULL)
    {
        spu->stk.error_code = CALLOC_ERROR;
    }

    for(long int elem = 0; elem < code_size; elem++)
    {
        fscanf(asm_code, "%d", &spu->code[elem]);
    }

    fclose(asm_code);
}

ErrorCode SpuCtor(SPU* spu)
{
    assert(spu);

    StackCtor(&spu->stk);

    StackCtor(&spu->ret);

    spu->ip = 0;

    (spu->reg) = (int*) calloc(REGISTERS_NUM, sizeof(int));

    if (spu->stk.data == NULL || spu->reg == NULL)
    {
        return CALLOC_ERROR;
    }

    return SUCCESS;
}

void DtorProc(SPU* spu)
{
    assert(spu);

    StackDtor(&spu->stk);

    free(spu->reg);
    spu->reg = NULL;

    free(spu->code);
    spu->code = NULL;
}

ErrorCode RunCode(SPU* spu, unsigned long int code_size)
{
    while(true)
    {
        switch(spu->code[spu->ip]){
            case CALL:
            {
                DoCall(spu);
                break;
            }
            case RET:
            {
                DoRet(spu);
                break;
            }
            case PUSH:
            {
                DoPush(spu);
                break;
            }
            case SQRT:
            {
                DoSqrt(spu);
                break;
            }
            case POP:
            {
                DoPop(spu);
                break;
            }
            case VIS:
            {
                DoVis(spu);
                break;
            }
            case ADD:
            {
                DoAdd(spu);
                break;
            }
            case SUB:
            {
                DoSub(spu);
                break;
            }
            case DIV:
            {
                DoDiv(spu);
                break;
            }
            case MUL:
            {
                DoMul(spu);
                break;
            }
            case OUT:
            {
                DoOut(spu);
                break;
            }
            case IN:
            {
                DoIn(spu);
                break;
            }
            case DUMP:
            {
                DoDump(spu, code_size);
                break;
            }
            case JMP:
            {
                DoJmp(spu);
                break;
            }
            case JB:
            {
                DoJb(spu);
                break;
            }
            case HLT:
            {
                DtorProc(spu);

                return SUCCESS;
                break;
            }
            default:
                spu->stk.error_code = COMMAND_ERROR;
                return COMMAND_ERROR;
        }
   }
}

