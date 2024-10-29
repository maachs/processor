#include "ProcFunc.h"

int main(int argc, char** argv)
{
    SPU spu = {};
    struct stat buffer = {};

    if(argc != 2)
    {
        printf("argc error");
        return -1;
    }

    stat(argv[1], &buffer);

    InitCode(&spu, buffer.st_size, argv);

    SpuCtor(&spu);

    if(RunCode(&spu, buffer.st_size) != SUCCESS) return -1;

    //DtorProc(&spu);

}

void InitCode(SPU* spu, int code_size, char** argv)
{
    assert(spu);

    FILE* asm_code = fopen(argv[1], "r");

    if(asm_code == NULL){
        printf("Cannot open asm file");
        spu->stk.error_code = OPEN_FILE_ERROR;
    }

    spu->code = (int*) calloc(code_size, sizeof(int));

    if(spu->code == NULL){
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
            case PUSH:
            {
                DoPush(spu);
                break;
            }
            case POP:
            {
                DoPop(spu);
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
                spu->stk.error_code = COMAND_ERROR;
                return COMAND_ERROR;
        }
   }
}

ErrorCode DoPush(SPU* spu)
{
    assert(spu);
    assert(spu->code);

    StackElem elem = GetArgPush(spu);

    StackPush(&spu->stk, elem);

    spu->ip += 2;

    return SUCCESS;
}

int GetArgPush(SPU* spu)
{
    assert(spu);

    //int operation_code = spu->code[spu->ip];
    spu->ip++;

    int arg_type = spu->code[spu->ip];
    spu->ip++;

    int result = 0;

    if(arg_type & IN_STACK)
    {
        result = spu->code[spu->ip];
        spu->ip++;
    }

    if(arg_type & IN_REG)
    {
        result += spu->reg[spu->code[spu->ip]];
        spu->ip++;
    }
    if(arg_type & IN_RAM)
    {
        result = spu->ram[result];
    }

    return result;
}

ErrorCode DoPop(SPU* spu)
{
    assert(spu);
    assert(spu->code);

    int* addr = GetArgPop(spu);

    StackElem value = StackPop(&spu->stk);

    *addr = value;

    spu->ip++;

    return SUCCESS;

}

int* GetArgPop(SPU* spu)
{
    assert(spu);

    //int operation_code = spu->code[spu->ip];
    spu->ip++;

    int arg_type = spu->code[spu->ip];
    spu->ip++;

    int result = 0;

    if(arg_type & IN_STACK)
    {
        result = spu->code[spu->ip];
    }
    if(arg_type & IN_REG)
    {
        return &spu->reg[spu->ip];
    }
    if(arg_type & IN_RAM)
    {
        return &spu->ram[result];
    }

    return NULL;
}

ErrorCode DoAdd(SPU* spu)
{
    assert(spu);
    assert(spu->code);

    StackElem val_1 = StackPop(&spu->stk);
    StackElem val_2 = StackPop(&spu->stk);

    StackPush(&spu->stk, val_1 + val_2);

    spu->ip++;

    return SUCCESS;
}

ErrorCode DoSub(SPU* spu)
{
    assert(spu);
    assert(spu->code);

    StackElem val_1 = StackPop(&spu->stk);
    StackElem val_2 = StackPop(&spu->stk);

    StackPush(&spu->stk, val_1 - val_2);

    spu->ip++;

    return SUCCESS;
}

ErrorCode DoMul(SPU* spu)
{
    assert(spu);
    assert(spu->code);

    StackElem val_1 = StackPop(&spu->stk);
    StackElem val_2 = StackPop(&spu->stk);

    StackPush(&spu->stk, val_1 * val_2);

    spu->ip++;

    return SUCCESS;
}

ErrorCode DoDiv(SPU* spu)
{
    assert(spu);
    assert(spu->code);

    StackElem val_1 = StackPop(&spu->stk);
    StackElem val_2 = StackPop(&spu->stk);
    StackPush(&spu->stk, val_1 / val_2);

    spu->ip++;

    return SUCCESS;
}

ErrorCode DoOut(SPU* spu)
{
    assert(spu);
    assert(spu->code);

    printf("%d\n", StackPop(&spu->stk));

    spu->ip++;

    return SUCCESS;
}

ErrorCode DoIn(SPU* spu)
{
    assert(spu);
    assert(spu->code);

    StackElem elem = 0;
    scanf("%d", &elem);

    StackPush(&spu->stk, elem);

    return SUCCESS;
}

ErrorCode DoDump(SPU* spu, unsigned long int code_size)
{
    assert(spu);
    assert(spu->code);

    printf("----------------------------------------------------\n");
    printf("code: \n");

    for(unsigned int num = 0; num < code_size; num++)
    {
        printf("%d  ", num);
    }

    printf("\n");

    for(unsigned long int code_elem = 0; code_elem < code_size; code_elem++)
    {
        printf("%d  ", spu->code[code_elem]);
    }
    printf("\n");

    for(int ip_elem = 0; ip_elem < spu->ip; ip_elem++)
    {
        printf("   ");
    }
    printf("^\n");

    printf(" ip = %d\n", spu->ip);

    printf("___registres___\n");
    printf("Ax = %d\n", spu->reg[Ax]);
    printf("Bx = %d\n", spu->reg[Bx]);
    printf("Cx = %d\n", spu->reg[Cx]);
    printf("Dx = %d\n", spu->reg[Dx]);

    StackDump(&spu->stk);

    printf("---------------------------------------------------\n");

    spu->ip++;

    return SUCCESS;

}
ErrorCode DoJmp(SPU* spu)
{
    assert(spu);
    assert(spu->code);

    spu->ip = spu->code[spu->ip + 1];

    return SUCCESS;
}

ErrorCode DoJb(SPU* spu)
{
    assert(spu);
    assert(spu->code);

    StackElem elem1 = StackPop(&spu->stk);
    StackElem elem2 = StackPop(&spu->stk);

    if(elem1 < elem2)
    {
        DoJmp(spu);
    }
    else
    {
        spu->ip ++;
    }

    return SUCCESS;
}

