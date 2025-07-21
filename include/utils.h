#ifndef UTILS_H
#define UTILS_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
typedef struct
{
    char *file_location;
    char *output_location;
} UserArguments;
void parse_args(int argc, char **argv, UserArguments *user_arugments);
char *remove_quotes(char *buffer);

#endif