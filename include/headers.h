#ifndef HEADERS_H
#define HEADERS_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "global.h"
#include "error_messages.h"
#include "printf_macros.h"
#include "utils.h"
#include "structs.h"

#define INITIAL_HEADERS_CAPACITY 5
#define MAX_LINE_LENGTH 1024

// typedef struct
// {
//     char **data;
//     size_t count;
// } Headers;
Headers get_headers(FILE *csv_file_fd);
void free_headers(Headers *headers);
void write_headers(Headers *headers, FILE *output_fd);
#endif