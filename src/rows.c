#include "rows.h"

void parse_row()
{
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