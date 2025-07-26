#ifndef ROW_H
#define ROW_H
#include <stdlib.h>
#include <stdio.h>
#include "structs.h"
#include "headers.h"
#include "utils.h"
void free_rows(Row *rows, size_t rows_count);
void write_rows(Row *rows, size_t rows_count, FILE *output_fd);
void parse_row(CsvData *csv_data, char *token, size_t *token_index, FILE *csv_fd);
#endif