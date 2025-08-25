#ifndef GLOBAL_H
#define GLOBAL_H
#define MAX_LINE_LENGTH 1024
typedef struct
{
    char **data;
    size_t count;
} Headers;
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
typedef struct
{
    Headers headers;
    Row *rows;
    size_t rows_count;
} CsvData;
#endif