#ifndef MAIN_H
#define MAIN_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "global.h"
#include "utils.h"
#include "headers.h"
#include "rows.h"
#define INITIAL_LINES_CAPACITY 50
typedef struct
{
    char **headers;
    Row *rows;
    int header_count;
    int line_count;
} CsvData;
#endif