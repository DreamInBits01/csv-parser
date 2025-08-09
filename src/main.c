#include "main.h"
int main(int argc, char **argv)
{
    UserArguments user_arugments = {0};
    parse_args(argc, argv, &user_arugments);
    FILE *csv_file = fopen(user_arugments.file_location, "r");
    if (csv_file == NULL)
    {
        PRINT_ERROR(FILE_NOT_FOUND);
        exit(1);
    }
    char buffer[MAX_LINE_LENGTH];
    size_t rows_capacity = INITIAL_LINES_CAPACITY;
    CsvData csv_data = {0};
    csv_data.headers = get_headers(csv_file);
    csv_data.rows = (Row *)malloc(rows_capacity * sizeof(Row));
    csv_data.rows_count = 0;
    while (fgets(buffer, MAX_LINE_LENGTH, csv_file))
    {
        if (csv_data.rows_count > rows_capacity)
        {
            rows_capacity *= 2;
            Row *temp = realloc(csv_data.rows, rows_capacity * sizeof(Row));
            if (!temp)
            {
                fprintf(stderr, "Failed to realloc lines array\n");
                free_rows(csv_data.rows, csv_data.rows_count);
                free_headers(&csv_data.headers);
                return 1;
            }
            csv_data.rows = temp;
        }
        csv_data.rows[csv_data.rows_count].fields = malloc(csv_data.headers.count * sizeof(Field));
        if (!csv_data.rows[csv_data.rows_count].fields)
        {
            PRINT_ERROR(ALLOCATION_ERROR, "Fields");
            // free memory
            free_rows(csv_data.rows, csv_data.rows_count);
            free_headers(&csv_data.headers);
            return 1;
        }
        buffer[strcspn(buffer, "\r\n")] = 0; // strip trailing newline
        char *token = strtok(remove_comma_between_quotes(buffer), ",");
        size_t token_index = 0;
        parse_row(&csv_data, token, &token_index, csv_file);
        // be ready for the next line
        token_index = 0;
        csv_data.rows_count++;
    };
    FILE *output_file = fopen(user_arugments.output_location, "w");
    if (output_file == NULL)
    {
        PRINT_ERROR(FILE_NOT_FOUND);
        exit(1);
    };
    write_headers(&csv_data.headers, output_file);
    write_rows(csv_data.rows, csv_data.rows_count, output_file);
    free_headers(&csv_data.headers);
    free_rows(csv_data.rows, csv_data.rows_count);
    fclose(csv_file);
    fclose(output_file);
    return 0;
}