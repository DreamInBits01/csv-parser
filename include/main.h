#ifndef MAIN_H
#define MAIN_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_LINE_LENGTH 1000
#define INITIAL_CAPACITY 10

typedef struct
{
    char *name;
    char *value;
} field_t;
typedef struct
{
    int field_count;
    field_t *fields; // array
} row_t;
typedef struct
{
    char **headers;
    row_t *rows;
    int header_count;
    int line_count;
} csv_data_t;
typedef struct
{
    char *file_location;
    char *output_location;
} user_arugments;
void parse_args(int argc, char **argv, user_arugments *user_arugments);
#endif