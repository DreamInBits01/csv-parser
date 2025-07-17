// #include "include/main.h"
#include <stdio.h>

void parse_args(char **argv)
{
    while (*argv)
    {
        printf("arugment %s\n", *argv);
        argv++;
    }
}
int main(int argc, char **argv)
{
    parse_args(argv);
    return 0;
}