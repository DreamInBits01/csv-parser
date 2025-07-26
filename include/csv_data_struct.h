#ifndef CSV_DATA_STRUCT_H
#define CSV_DATA_STRUCT_H
#include "headers.h"
#include "rows.h"
typedef struct
{
    Headers headers;
    Row *rows;
    size_t rows_count;
} CsvData;
#endif