#ifndef HEADERS_H
#define HEADERS_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "global.h"
#define INITIAL_HEADERS_CAPACITY 5
#define MAX_LINE_LENGTH 1012

typedef struct
{
    char **data;
    int count;
} Headers;
Headers get_headers(FILE *csv_file_fd);
void free_headers(Headers *headers);
#endif