#include "Instructions.h"

ErrorCode DoPush(SPU* spu)
{
    assert(spu);
    assert(spu->code);

    StackElem elem = GetArgPush(spu);

    StackPush(&spu->stk, elem);

    spu->ip += 2;

    return SUCCESS;
}
ErrorCode DoSqrt(SPU* spu)
{
    assert(spu);

    double arg_sqrt = (double) StackPop(&spu->stk);

    arg_sqrt = sqrt(arg_sqrt);

    StackPush(&spu->stk, StackElem(arg_sqrt));

    return SUCCESS;
}

ErrorCode DoVis(SPU* spu)
{
    assert(spu);

    for(int x = 0; x < RAM_LINE_LEN; x++)
    {
        for(int y = 0; y < RAM_LINE_LEN; y++)
        {
            if(spu->ram[x * RAM_LINE_LEN + y] == 0)
            {
                fprintf(spu->out, ".  " );
            }
            else
            {
                fprintf(spu->out, "*  ");
            }
        }
        fprintf(spu->out, "\n");
    }

    spu->ip++;

    return SUCCESS;
}

int GetArgPush(SPU* spu)
{
    assert(spu);

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
ErrorCode DoCall(SPU* spu)
{
    assert(spu);

    spu->ip++;

    StackElem addr = spu->code[spu->ip];

    StackPush(&spu->ret, addr);

    spu->ip++;

    return SUCCESS;
}

ErrorCode DoRet(SPU* spu)
{
    assert(spu);

    StackElem ret = StackPop(&spu->ret);

    spu->ip = ret;

    return SUCCESS;
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

    fprintf(spu->out, "%d\n", StackPop(&spu->stk));

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


