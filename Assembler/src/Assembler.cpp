#include "AssemblerFunc.h"

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

    char* scanf_commands_first = (char*) calloc(MAX_COMMAND_LEN, sizeof(char));

    int arg = 0, com = 0;
    char arg_chr[MAX_COMMAND_LEN] = {};
    char push_com[MAX_PUSH_ARG] = {};

    while(fscanf(assm->commands, "%s", scanf_commands_first) != EOF)
    {
        char* scan_commands = scanf_commands_first;

        if(stricmp(scan_commands, "push") == 0)
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

                        fscanf(assm->commands, "%s", arg_chr); // next symbol

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
        if(stricmp(scan_commands, "pop") == 0)
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
        if(stricmp(scan_commands, "add") == 0)
        {
            fprintf(assm->machine_code, "%d\n", ADD);

            assm->count_commands++;

            continue;
        }
        if(stricmp(scan_commands, "sub") == 0)
        {
            fprintf(assm->machine_code, "%d\n", SUB);

            assm->count_commands++;

            continue;
        }
        if(stricmp(scan_commands, "vis") == 0)
        {
            fprintf(assm->machine_code, "%d\n", VIS);

            assm->count_commands++;

            continue;
        }
        if(stricmp(scan_commands, "div") == 0)
        {
            fprintf(assm->machine_code, "%d\n", DIV);

            assm->count_commands++;

            continue;
        }
        if(stricmp(scan_commands, "sqrt") == 0)
        {
            fprintf(assm->machine_code, "%d\n", SQRT);

            assm->count_commands++;

            continue;
        }
        if(stricmp(scan_commands, "mul") == 0)
        {
            fprintf(assm->machine_code, "%d\n", MUL);

            assm->count_commands++;

            continue;
        }
        if(stricmp(scan_commands, "out") == 0)
        {
            fprintf(assm->machine_code, "%d\n", OUT);

            assm->count_commands++;

            continue;
        }
        if(stricmp(scan_commands, "in") == 0)
        {
            fprintf(assm->machine_code, "%d\n", IN);

            assm->count_commands++;

            continue;
        }
        if(stricmp(scan_commands, "dump") == 0)
        {
            fprintf(assm->machine_code, "%d\n", DUMP);

            assm->count_commands++;

            continue;
        }
        if(stricmp(scan_commands, "hlt") == 0)
        {
            fprintf(assm->machine_code, "%d\n", HLT);

            assm->count_commands++;

            continue;
        }
        if(stricmp(scan_commands, "call") == 0)
        {
            fscanf(assm->commands, "%s", arg_chr);

            for(int label = 0; label < assm->count_labels; label++)
            {
                if(stricmp(arg_chr, assm->mark[label].labels) == 0)
                {
                    fprintf(assm->machine_code, "%d %d\n", CALL, assm->mark[label].address);
                }
            }

            assm->count_commands += 2;

            continue;
        }
        if(stricmp(scan_commands, "ret") == 0)
        {
            fprintf(assm->machine_code, "%d\n", RET);

            assm->count_commands++;

            continue;
        }
        if(stricmp(scan_commands, "jb") == 0)
        {
            fscanf(assm->commands, "%s", arg_chr);

            for(int label = 0; label < assm->count_labels; label++)
            {
                if(stricmp(arg_chr, assm->mark[label].labels) == 0)
                {
                    fprintf(assm->machine_code, "%d %d\n", JB, assm->mark[label].address);
                }
            }

            assm->count_commands += 2;

            continue;
        }
        if(stricmp(scan_commands, "jmp") == 0)
        {
            fscanf(assm->commands, "%s", arg_chr);

            for(int label = 0; label < assm->count_labels; label++)
            {
                if(stricmp(arg_chr, assm->mark[label].labels) == 0)
                {
                    fprintf(assm->machine_code, "%d %d\n", JMP, assm->mark[label].address);
                }
            }

            assm->count_commands += 2;

            continue;
        }
        if(strchr(scan_commands, ':') != NULL)
        {
            CreateMarks(assm, scan_commands);

            continue;
        }
    }

    fclose(assm->commands);

    free(scanf_commands_first);
    scanf_commands_first = NULL;

    fclose(assm->machine_code);

    return SUCCESS;
}

void CreateMarks(ASM* assm, char* arg_jmp)
{
    assert(arg_jmp);
    assert(assm);
    assert(assm->mark);

    int labels_check = 0; // TODO rename

    for(int check = 0; check < assm->count_labels; check++)
    {
        if(!strcmp(arg_jmp, assm->mark[check].labels))
        {
            labels_check++;
        }
    }

    if(labels_check == 0)
    {
        strcpy(assm->mark[assm->count_labels].labels, arg_jmp);

        assm->mark[assm->count_labels].address = assm->count_commands;

        assm->count_labels++;
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
    if(stricmp((const char*)arg_reg, "dx") == 0)
    {
        fprintf(assm->machine_code, "%d", Dx);
    }
}

