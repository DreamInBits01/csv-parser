// #include "include/main.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
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
    char **lines = NULL;
    char *file_path = NULL;
    printf("first arg: %s", *argv);
    if (strcmp(argv[1], "--filepath") == 0)
    {
        file_path = argv[2];
        printf("Filepath was provided, %s\n", file_path);
    };
    int capacity = INITIAL_CAPACITY;
    lines = malloc(capacity * sizeof(char *));
    lines[0] = "Test1";
    lines[1] = "Test2";
    lines[2] = "Test3";
    lines[3] = "Test4";
    // lines[0] = 1;
    // lines[1] = 2;
    // lines[2] = 3;
    // lines[3] = 3;
    while (*lines)
    {
        printf("Line:%c\n", **lines);
        lines++;
    };
    return 0;
}