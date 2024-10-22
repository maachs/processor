#include "ProcFunc.h"

int main()
{
    SPU spu = {};
    struct stat buffer = {};

    stat(MACHINE_CODE, &buffer);

    InitCode(&spu, buffer.st_size);

    if(RunCode(&spu, buffer.st_size) != SUCCESS) return -1;

    DtorProc(&spu);

}

/*INSTRUCTION(5, ADD,  {
    StackElem var1 = pop();
    StackElem var2 = pop();

    push(var1 + var2)
})*/

void InitCode(SPU* spu, int code_size)
{
    assert(spu);

    FILE* asm_code = fopen(MACHINE_CODE, "r");

    if(asm_code == NULL){
        printf("Cannot open asm file");
        spu->stk.error_code = OPEN_FILE_ERROR;
    }

    spu->code = (int*) calloc(code_size, sizeof(int));

    if(spu->code == NULL){
        spu->stk.error_code = CALLOC_ERROR;
    }

    for(unsigned long int elem = 0; elem < code_size; elem++)
    {
        fscanf(asm_code, "%x", &spu->code[elem]);
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
            case PUSHR:
            {
                DoPushr(spu);
                break;
            }
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
            /*case IN:
            {
                DoIn(spu);
                break;
            }*/
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
                return SUCCESS;
                break;
            }
            default:
                spu->stk.error_code = COMAND_ERROR;
                return COMAND_ERROR;
        }
   }
}

ErrorCode DoPushr(SPU* spu)
{
    assert(spu);
    assert(spu->code);

    switch(spu->code[spu->ip+1]){
        case Ax:
        {
            StackElem elem1 = spu->reg[Ax];
            StackPush(&spu->stk, elem1);
            spu->ip += 2;
            break;
        }
        case Bx:
        {
            StackElem elem2 = spu->reg[Bx];
            StackPush(&spu->stk, elem2);
            spu->ip += 2;
            break;
        }
        case Cx:
        {
            StackElem elem3 = spu->reg[Cx];
            StackPush(&spu->stk, elem3);
            spu->ip += 2;
            break;
        }
        case Dx:
        {
            StackElem elem4 = spu->reg[Dx];
            StackPush(&spu->stk, elem4);
            spu->ip += 2;
            break;
        }
        default:
            printf("register error");
            spu->stk.error_code = COMAND_ERROR;
    }

    return SUCCESS;

}
ErrorCode DoPush(SPU* spu)
{
    assert(spu);
    assert(spu->code);

    int elem = spu->code[spu->ip+1];
    StackPush(&spu->stk, elem);
    spu->ip += 2;
    return SUCCESS;

    return SUCCESS;
}

ErrorCode DoPop(SPU* spu)
{
    assert(spu);
    assert(spu->code);

    switch(spu->code[spu->ip+1]){
        case Ax:
        {
            StackElem value = StackPop(&spu->stk);
            spu->reg[0] = value;
            spu->ip += 2;
            break;
        }
        case Bx:
        {
            StackElem value = StackPop(&spu->stk);
            spu->reg[1] = value;
            spu->ip += 2;
            break;
        }
        case Cx:
        {
            StackElem value = StackPop(&spu->stk);
            spu->reg[2] = value;
            spu->ip += 2;
            break;
        }
        case Dx:
        {
            StackElem value = StackPop(&spu->stk);
            spu->reg[3] = value;
            spu->ip += 2;
            break;
        }
        default:
            printf("Unknown POP comand");
            return COMAND_ERROR;
    }

    return SUCCESS;

}

ErrorCode DoAdd(SPU* spu)
{
    assert(spu);
    assert(spu->code);

    StackPush(&spu->stk, StackPop(&spu->stk) + StackPop(&spu->stk));

    spu->ip++;

    return SUCCESS;
}

ErrorCode DoSub(SPU* spu)
{
    assert(spu);
    assert(spu->code);

    StackPush(&spu->stk, StackPop(&spu->stk) + StackPop(&spu->stk));

    spu->ip++;

    return SUCCESS;
}

ErrorCode DoMul(SPU* spu)
{
    assert(spu);
    assert(spu->code);

    StackPush(&spu->stk, StackPop(&spu->stk) * StackPop(&spu->stk));

    spu->ip++;

    return SUCCESS;
}

ErrorCode DoDiv(SPU* spu)
{
    assert(spu);
    assert(spu->code);

    StackPush(&spu->stk, StackPop(&spu->stk) / StackPop(&spu->stk));

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
}

ErrorCode DoDump(SPU* spu, unsigned long int code_size)
{
    assert(spu);
    assert(spu->code);

    printf("----------------------------------------------------");
    printf("code: ");

    for(unsigned int num = 0; num < code_size; num++)
    {
        printf("%x ", num);
    }

    printf("\n");

    for(unsigned long int code_elem = 0; code_elem < code_size; code_elem++)
    {
        printf("%x ", spu->code[code_elem]);
    }
    printf("\n");

    for(int ip_elem = 0; ip_elem < spu->ip; ip_elem++)
    {
        printf("^");
    }
    printf(" ip = %d\n", spu->ip);

    printf("___registres___\n");
    printf("Ax = %d\n", spu->reg[Ax]);
    printf("Bx = %d\n", spu->reg[Bx]);
    printf("Cx = %d\n", spu->reg[Cx]);
    printf("Dx = %d\n", spu->reg[Dx]);

    StackDump(&spu->stk);

    printf("---------------------------------------------------");

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

