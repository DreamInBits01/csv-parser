#ifndef ROW_H
#define ROW_H
#include <stdlib.h>
#include <stdio.h>
typedef struct
{
    char *name;
    char *value;
} Field;
typedef struct
{
    size_t field_count;
    Field *fields;
} Row;
void free_rows(Row *rows, size_t rows_count);
void write_rows(Row *rows, size_t rows_count, FILE *output_fd);
#endif