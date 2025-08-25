#ifndef UTILS_H
#define UTILS_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "printf_macros.h"
#include "error_messages.h"
#include "rows.h"
#include "global.h"
typedef struct
{
    char *file_location;
    char *output_location;
} UserArguments;

void parse_args(int argc, char **argv, UserArguments *user_arugments);
char *remove_quotes(char *buffer);
char *remove_comma_between_quotes(char *buffer);
// void write_csv_row(FILE *fd, Row **rows, int rows_count);
void write_csv_row(FILE *fd, const Row *row);
#endif