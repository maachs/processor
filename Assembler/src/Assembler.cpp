#include "AssemblerFunc.h"

int main(int argc, char** argv)
{
    ASM assm = {};


    if(argc != 3)
    {
        printf("argc error");
        return -1;
    }

    ScanCode(&assm, argv);

    assm.count_commands = 0;

    ScanCode(&assm, argv);

    return 0;
}

ErrorCode ScanCode(ASM* assm, char** argv)
{
    assert(argv);

    assm->commands = fopen(argv[1], "rb");
    assm->machine_code = fopen(argv[2], "w");

    if (assm->commands == NULL || assm->machine_code == NULL)
    {
        printf("Error: cannot open file");

        fclose(assm->commands);
        fclose(assm->machine_code);

        return SCAN_CODE_ERROR;
    }

    char* scanf_commands = (char*) calloc(MAX_COMMAND_LEN, sizeof(char));

    int arg = 0, com = 0;
    char arg_chr[MAX_COMMAND_LEN] = {};
    char push_com[MAX_PUSH_ARG] = {};

    while(fscanf(assm->commands, "%s", scanf_commands) != EOF)
    {
        char* scan_comands = scanf_commands;

        if(stricmp(scan_comands, "push") == 0)
        {
            com = PUSH;

            if(fscanf(assm->commands, "%d", &arg) == 0)
            {
                fscanf(assm->commands, "%s", arg_chr);

                if(strchr(arg_chr, '[') != 0)
                {
                    if(fscanf(assm->commands, "%d", &arg) == 0)
                    {
                        fscanf(assm->commands, "%s", push_com); // arg register

                        fscanf(assm->commands, "%s", arg_chr); // next simbol

                        if(strchr(arg_chr, '+'))
                        {
                            fscanf(assm->commands, "%d", &arg);

                            fprintf(assm->machine_code, "%d %d ",com, RAM_STACK_REG);

                            fprintf(assm->machine_code, "%d ", arg);

                            FillRegisters(assm, push_com);

                            fprintf(assm->machine_code, "\n");

                            assm->count_commands += 4;

                            continue;
                        }
                        else
                        {
                            fprintf(assm->machine_code, "%d %d ",com , RAM_REG);

                            FillRegisters(assm, push_com);

                            fprintf(assm->machine_code, "\n");

                            assm->count_commands += 3;

                            continue;
                        }
                    }
                    else
                    {
                        fprintf(assm->machine_code, "%d %d %d\n", com, RAM_STACK, arg);

                        assm->count_commands += 3;

                        continue;
                    }
                }
                else
                {
                    fprintf(assm->machine_code, "%d %d ", com, IN_REG);

                    FillRegisters(assm, arg_chr);

                    fprintf(assm->machine_code, "\n");

                    assm->count_commands += 3;

                    continue;
                }
            }
            else
            {
                fprintf(assm->machine_code, "%d %d %d\n", com, IN_STACK, arg);

                assm->count_commands += 3;

                continue;
            }

        }
        if(stricmp(scan_comands, "pop") == 0)
        {
            com = POP;

            fscanf(assm->commands, "%s", arg_chr);

            if(strchr(arg_chr, '[') != 0)
            {
                fscanf(assm->commands, "%d", &arg);

                fprintf(assm->machine_code, "%d %d %d\n", com, RAM_STACK, arg);
            }
            else
            {
                fprintf(assm->machine_code, "%d %d ", com, IN_REG);

                FillRegisters(assm, arg_chr);

                fprintf(assm->machine_code, "\n");
            }

            assm->count_commands += 3;

            continue;
        }
        if(stricmp(scan_comands, "add") == 0)
        {
            fprintf(assm->machine_code, "%d\n", ADD);

            assm->count_commands++;

            continue;
        }
        if(stricmp(scan_comands, "sub") == 0)
        {
            fprintf(assm->machine_code, "%d\n", SUB);

            assm->count_commands++;

            continue;
        }
        if(stricmp(scan_comands, "div") == 0)
        {
            fprintf(assm->machine_code, "%d\n", DIV);

            assm->count_commands++;

            continue;
        }
        if(stricmp(scan_comands, "mul") == 0)
        {
            fprintf(assm->machine_code, "%d\n", MUL);

            assm->count_commands++;

            continue;
        }
        if(stricmp(scan_comands, "out") == 0)
        {
            fprintf(assm->machine_code, "%d\n", OUT);

            assm->count_commands++;

            continue;
        }
        if(stricmp(scan_comands, "in") == 0)
        {
            fprintf(assm->machine_code, "%d\n", IN);

            assm->count_commands++;

            continue;
        }
        if(stricmp(scan_comands, "dump") == 0)
        {
            fprintf(assm->machine_code, "%d\n", DUMP);

            assm->count_commands++;

            continue;
        }
        if(stricmp(scan_comands, "hlt") == 0)
        {
            fprintf(assm->machine_code, "%d\n", HLT);

            assm->count_commands++;

            continue;
        }
        if(stricmp(scan_comands, "jb") == 0)
        {
            fscanf(assm->commands, "%s", arg_chr);

            for(int label = 0; label < assm->count_lables; label++)
            {
                if(stricmp(arg_chr, assm->mark[label].lables) == 0)
                {
                    fprintf(assm->machine_code, "%d %d\n", JB, assm->mark[label].address);
                }
            }

            assm->count_commands += 2;

            continue;
        }
        if(stricmp(scan_comands, "jmp") == 0)
        {
            fscanf(assm->commands, "%s", arg_chr);

            for(int label = 0; label < assm->count_lables; label++)
            {
                if(stricmp(arg_chr, assm->mark[label].lables) == 0)
                {
                    fprintf(assm->machine_code, "%d %d\n", JMP, assm->mark[label].address);
                }
            }

            assm->count_commands += 2;

            continue;
        }
        if(strchr(scan_comands, ':') != NULL)
        {
            CreateMarks(assm, scan_comands);

            continue;
        }
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
    assert(assm);
    assert(assm->mark);

    int check_lables = 0;

    for(int check = 0; check < assm->count_lables; check++)
    {
        if(!strcmp(arg_jmp, assm->mark[check].lables))
        {
            check_lables++;
        }
    }

    if(check_lables == 0)
    {
        strcpy(assm->mark[assm->count_lables].lables, arg_jmp);

        assm->mark[assm->count_lables].address = assm->count_commands;

        assm->count_lables++;
    }
}

void FillRegisters(ASM* assm, char* arg_reg)
{
    assert(assm);
    assert(arg_reg);

    if(stricmp((const char*)arg_reg, "ax") == 0)
    {
        fprintf(assm->machine_code, "%d", Ax);
    }
    if(stricmp((const char*)arg_reg, "bx") == 0)
    {
        fprintf(assm->machine_code, "%d", Bx);
    }
    if(stricmp((const char*)arg_reg, "cx") == 0)
    {
        fprintf(assm->machine_code, "%d", Cx);
    }
    if(stricmp((const char*)arg_reg, "Dx") == 0)
    {
        fprintf(assm->machine_code, "%d", Dx);
    }
}

