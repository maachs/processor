#include "AssemblerFunc.h"


int main(int argc, char** argv)
{
    ASM assm = {};

    if(argc != 3){
        printf("argc error");
        return -1;
    }

    ScanCode(&assm, argv);

    return 0;
}

ErrorCode ScanCode(ASM* assm, char** argv)
{
    assert(argv);

    assm->commands = fopen(argv[1], "rb");
    assm->machine_code = fopen(argv[2], "w");

    if (assm->commands == NULL)
    {
        printf("Cannot open file");

        fclose(assm->commands);
        fclose(assm->machine_code);

        return SCAN_CODE_ERROR;
    }
    char* scanf_commands = (char*) calloc(MAX_COMMAND_LEN, sizeof(char));

    int arg = 0, com = 0;
    char arg_reg[MAX_COMMAND_LEN] = {};
    char arg_jmp[MAX_LABLES_LEN]  = {};


    while(fscanf(assm->commands, "%s", scanf_commands) != EOF)
    {
        const char* scan_comands = scanf_commands;

        if(stricmp(scan_comands, "push") == 0)
        {
            fscanf(assm->commands, "%d", &arg);
            fprintf(assm->machine_code, "%d %d\n", PUSH, arg);

            assm->count_commands ++;
        }
        else if(stricmp(scan_comands, "pop") == 0)
        {
            printf("hui\n");
            fscanf(assm->commands, "%s", arg_reg);

            printf("%s\n", arg_reg);

            com = POP;

            FillRegisters(assm, arg_reg, com);

            assm->count_commands++;
        }
        else if(stricmp(scan_comands, "add") == 0)
        {
            fprintf(assm->machine_code, "%d\n", ADD);
        }
        else if(stricmp(scan_comands, "sub") == 0)
        {
            fprintf(assm->machine_code, "%d\n", SUB);
        }
        else if(stricmp(scan_comands, "div") == 0)
        {
            fprintf(assm->machine_code, "%d\n", DIV);
        }
        else if(stricmp(scan_comands, "mul") == 0)
        {
            fprintf(assm->machine_code, "%d\n", MUL);
        }
        else if(stricmp(scan_comands, "out") == 0)
        {
            fprintf(assm->machine_code, "%d\n", OUT);
        }
        else if(stricmp(scan_comands, "in") == 0)
        {
            fprintf(assm->machine_code, "%d\n", IN);
        }
        else if(stricmp(scan_comands, "dump") == 0)
        {
            fprintf(assm->machine_code, "%d\n", DUMP);
        }
        else if(stricmp(scan_comands, "hlt") == 0)
        {
            fprintf(assm->machine_code, "%d\n", HLT);
        }
        else if(stricmp(scan_comands, "jb") == 0)
        {
            printf("HUI\n");
            fscanf(assm->commands, "%s", arg_jmp);
            printf("sosal\n");


            for(int label = 0; label < assm->count_lables; label++)
            {
                if(stricmp(arg_jmp, assm->mark[label]->lables) == 0)
                {
                    fprintf(assm->machine_code, "%d %d\n", JB, assm->mark[label]->address);
                }
            }
        }
        else if(stricmp(scan_comands, "jmp") == 0)
        {
            fscanf(assm->commands, "%s", arg_jmp);

            for(int label = 0; label < assm->count_lables; label++)
            {
                if(stricmp(arg_jmp, assm->mark[label]->lables) == 0)
                {
                    fprintf(assm->machine_code, "%d %d\n", JB, assm->mark[label]->address);
                }
            }
        }
        else if(stricmp(scan_comands, "pushr") == 0)
        {
            fscanf(assm->commands, "%s", arg_reg);

            com = PUSHR;

            FillRegisters(assm, arg_reg, com);
        }
        else if(strchr(scan_comands, ':') != NULL)
        {
            printf("hui1\n");
            CreateMarks(assm, arg_jmp);
            printf("sosal1\n");
        }
        else
        {
            printf("unknown commands\n");
        }

        assm->count_commands++;
    }

    fclose(assm->commands);

    free(scanf_commands);
    scanf_commands = NULL;

    fclose(assm->machine_code);

    return SUCCESS;
}

void CreateMarks(ASM* assm, char* arg_jmp)
{
    assert(arg_jmp);
    printf("-----\n");
    assm->mark[assm->count_lables]->address = assm->count_commands;
    printf("vda\n");
    assm->mark[assm->count_lables]->lables = arg_jmp;
}

void FillRegisters(ASM* assm, char* arg_reg, int com)
{
    assert(com);

    if(stricmp((const char*)arg_reg, "ax") == 0)
    {
        fprintf(assm->machine_code, "%x %x\n", com, Ax);
    }
    if(stricmp((const char*)arg_reg, "bx") == 0)
    {
        fprintf(assm->machine_code, "%x %x\n", com, Bx);
    }
    if(stricmp((const char*)arg_reg, "cx") == 0)
    {
        fprintf(assm->machine_code, "%x %x\n", com, Cx);
    }
    if(stricmp((const char*)arg_reg, "Dx") == 0)
    {
        fprintf(assm->machine_code, "%x %x\n", com, Dx);
    }
}

