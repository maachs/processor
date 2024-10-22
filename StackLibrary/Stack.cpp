#include "StackFunc.h"

ErrorCode StackCtor(Stack_t* stk)
{
    assert(stk);

    stk->data = (StackElem*)calloc(CAPACITY_MIN + 2, sizeof(StackElem)) + 1;

    #ifdef DEBUG
        stk->canary2 = CANARY;
    #endif

    stk->size = 0;
    stk->capacity = CAPACITY_MIN;

    PoisonData(stk);

    #ifdef DEBUG
        stk->data[-1] = CANARY;
        stk->data[CAPACITY_MIN] = CANARY;
        CALC_HASH;
        stk->data_hash   = stk->buffer_data_hash; //first calc hash
        stk->struct_hash = stk->buffer_struct_hash;
    #endif
    return SUCCESS;
}

void StackDtor(Stack_t* stk)
{
    assert(stk);

    free(stk->data);
    stk->data = NULL;

    stk->capacity = CAPACITY_MIN;
    stk->size = 0;
}

void PoisonData(Stack_t* stk)
{
    for (int elem = stk->size; elem < stk->capacity; elem++)
    {
        stk->data[elem] = POISON;
    }
}

ErrorCode StackPush(Stack_t* stk, StackElem value)
{
    #ifdef DEBUG
    CALC_HASH;
    VERIFY_STACK(stk);
    stk->data_hash   = stk->buffer_data_hash;
    stk->struct_hash = stk->buffer_struct_hash;
    #endif

    if (stk->size == stk->capacity - 1)
    {
        printf("  ");
        ReallocPush(stk);
    }

    stk->data[stk->size] = value;
    stk->size++;
    #ifdef DEBUG
        CALC_HASH;
        stk->data_hash   = stk->buffer_data_hash;
        stk->struct_hash = stk->buffer_struct_hash;
    #endif

    return SUCCESS;
}
void ReallocPush(Stack_t* stk)
{
    assert(stk);

    stk->data = (StackElem*) realloc(stk->data - 1, stk->capacity * PUSH_STEP * sizeof(StackElem) + 2) + 1;

    if (stk->data == NULL)
    {
        stk->error_code = CALLOC_ERROR;
    }

    stk->data[stk->capacity] = POISON;

    stk->capacity *= 2;

    PoisonData(stk);

    stk->data[stk->capacity] = CANARY;
}

int StackPop(Stack_t* stk)
{
    assert(value);
    #ifdef DEBUG
        CALC_HASH;
        VERIFY_STACK(stk);
        stk->data_hash   = stk->buffer_data_hash;
        stk->struct_hash = stk->buffer_struct_hash;
    #endif

    StackElem value = stk->data[stk->size];
    stk->size--;

    stk->data[stk->size + 1] = POISON;

    if ((stk->size == stk->capacity / 4) && (stk->size > CAPACITY_MIN))
    {
        ReallocPop(stk);
    }
    #ifdef DEBUG
        CALC_HASH;
        stk->data_hash   = stk->buffer_data_hash;
        stk->struct_hash = stk->buffer_struct_hash;
        VERIFY_STACK(stk);
    #endif

    return value;
}

void ReallocPop(Stack_t* stk)
{
    stk->data = (StackElem*)realloc(stk->data - 1, (stk->capacity / POP_STEP) * sizeof(StackElem)) + 1;

    if (stk->data == NULL)
    {
        stk->error_code = CALLOC_ERROR;
    }

    stk->capacity /= 2;

    #ifdef DEBUG
        stk->data[stk->capacity] = CANARY;
    #endif
}

uint64_t CalcHash (char* data, int size)
{
    uint64_t hash = 5381;

    for (int elem = 0; elem < size; elem++)
    {
        hash += (hash * 33) ^ data[elem];
    }

    return hash;
}

void StackDump(Stack_t* stk)
{
    fprintf(stdout, "\nStk_t [0x%p]\n", stk);

    //fprintf(stdout, "called from %s : %d (%s)\n", file, line, func);

    //fprintf(stdout, "named \"%s\" born at %s:%d\n", stk->name, stk->file, stk->line);

    if (stk == NULL)
    {
        fprintf(stdout, "Dump stk = null");
    }
    else
    {

        if (stk->data != NULL)
        {
            printf("data\n{\n");
            for (int elem = 0; elem < stk->capacity + 2; elem++)
            {
                fprintf(stdout, "   [%d] = %d\n", elem - 1, stk->data[elem - 1]);
            }
            printf("}\n");
        }

        printf("capacity %d\n", stk->capacity);
        printf("size %d\n", stk->size);

        stk->error_code = VerifyStack(stk);

        if (stk->error_code != SUCCESS)
        {
            PrintError(stk);
        }
    }
}

void PrintError(Stack_t* stk)
{
    switch (stk->error_code)
    {
        case CAPACITY_EQUAL_SIZE:
            printf("\n<<<<<<<Capacity = size\n\n");
            break;
        case SIZE_ERROR:
            printf("\n<<<<<<<Size ERROR\n\n");
            break;
        case CAPACITY_ERROR:
            printf("\n<<<<<<<Capacity ERROR\n\n");
            break;
        case STK_ERROR:
            printf("\n<<<<<<<Stk = NULL\n\n");
            break;
        default:
            printf("\n<<<<<<<Unspecified ERROR\n\n");
    }
}

ErrorCode VerifyStack(Stack_t* stk)
{
    if (stk->capacity <= 0)
    {
        return CAPACITY_ERROR;
    }
    else if (stk->capacity < stk->size)
    {
        return CAPACITY_EQUAL_SIZE;
    }
    else if (stk == NULL)
    {
        return STK_ERROR;
    }
    else
    {
        return SUCCESS;
    }
}





