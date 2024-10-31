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
