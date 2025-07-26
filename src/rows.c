#include "rows.h"

void parse_row(CsvData *csv_data, char *token, size_t *token_index, FILE *csv_fd)
{
    while (token != NULL && *token_index < csv_data->headers.count)
    {
        char *clean_token = remove_quotes(token);
        csv_data->rows[csv_data->rows_count].fields[*token_index].name = csv_data->headers.data[*token_index];
        csv_data->rows[csv_data->rows_count].fields[*token_index].value = strdup(clean_token);

        if (!csv_data->rows[csv_data->rows_count].fields[*token_index].value)
        {
            fprintf(stderr, "strdup failed for token: %s\n", clean_token);
            // free current field and it's tokens,
            for (int i = 0; i < *token_index; i++)
            {
                free(csv_data->rows[csv_data->rows_count].fields[i].value);
            }
            free(csv_data->rows[csv_data->rows_count].fields);
            free_rows(csv_data->rows, csv_data->rows_count);
            free_headers(&csv_data->headers);
            fclose(csv_fd);
            exit(1);
        }
        // get headers, loop over tokens, for each token create a field struct with the key and value, then push it to the row, finally push the row
        token = strtok(NULL, ",");
        *token_index += 1;
    }
    csv_data->rows[csv_data->rows_count].field_count = *token_index;
}
void write_rows(Row *rows, size_t rows_count, FILE *output_fd)
{
    if (!rows || !output_fd)
        return;
    printf("Rows count:%ld", rows_count);
    for (size_t i = 0; i < rows_count; i++)
    {
        // for each row

        for (size_t j = 0; j < rows[i].field_count; j++)
        {
            fputs(rows[i].fields[j].value, output_fd);
            if (j < rows[i].field_count - 1)
            {
                fputs(",", output_fd);
            }
        }
        fputs("\n", output_fd);
    }
}
void free_rows(Row *rows, size_t rows_count)
{
    for (size_t i = 0; i < rows_count; i++)
    {
        for (size_t j = 0; j < rows[i].field_count; j++)
        {
            free(rows[i].fields[j].value);
        }
        free(rows[i].fields);
    }
    free(rows);
};