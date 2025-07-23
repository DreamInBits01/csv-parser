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
    int rows_count = 0;
    char buffer[MAX_LINE_LENGTH];
    Headers headers = get_headers(csv_file);
    int capacity = INITIAL_LINES_CAPACITY;
    Row *rows = NULL;
    rows = (Row *)malloc(capacity * sizeof(Row));
    while (fgets(buffer, MAX_LINE_LENGTH, csv_file))
    {
        if (rows_count >= capacity)
        {
            capacity *= 2;
            Row *temp = realloc(rows, capacity * sizeof(Row));
            if (!temp)
            {
                fprintf(stderr, "Failed to realloc lines array\n");
                free(rows);
                return 1;
            }
            rows = temp;
        }
        rows[rows_count].fields = malloc(headers.count * sizeof(Field));
        if (!rows[rows_count].fields)
        {
            fprintf(stderr, "Memory allocation failed\n");
            return 1;
        }
        buffer[strcspn(buffer, "\r\n")] = 0; // strip trailing newline
        char *token = strtok(remove_comma_between_quotes(buffer), ",");
        int token_place = 0;
        while (token != NULL && token_place < headers.count)
        {
            char *clean_token = remove_quotes(token);
            rows[rows_count].fields[token_place].name = headers.data[token_place];
            rows[rows_count].fields[token_place].value = strdup(clean_token);

            if (!rows[rows_count].fields[token_place].value)
            {
                fprintf(stderr, "strdup failed for token: %s\n", clean_token);
                free_headers(&headers);

                for (int k = 0; k < token_place; k++)
                {
                    free(rows[rows_count].fields[k].value);
                }
                free(rows[rows_count].fields);
                for (int i = 0; i < rows_count; i++)
                {
                    for (int j = 0; j < rows[i].field_count; j++)
                    {
                        free(rows[i].fields[j].value);
                    }
                    free(rows[i].fields);
                }
                free(rows);
                free_headers(&headers);
                fclose(csv_file);
                exit(1);
                free(rows);
                exit(1);
            }
            // get headers, loop over tokens, for each token create a field struct with the key and value, then push it to the row, finally push the row
            token = strtok(NULL, ",");
            token_place++;
        }
        rows[rows_count].field_count = token_place;
        token_place = 0;
        rows_count++;
    };
    FILE *output_file = fopen(user_arugments.output_location, "w");
    if (output_file == NULL)
    {
        PRINT_ERROR(FILE_NOT_FOUND);
        exit(1);
    };
    CsvData csv_data = {0};
    csv_data.headers = headers.data;
    csv_data.header_count = headers.count;
    csv_data.rows = rows;
    csv_data.line_count = rows_count;
    for (size_t i = 0; i < rows_count; i++)
    {
        printf("Processing row %ld with %d fields\n", i, rows[i].field_count);
        write_csv_row(output_file, &csv_data.rows[i]);
        fputs("\n", output_file);
        for (size_t j = 0; j < csv_data.rows[i].field_count; j++)
        {
            printf("  Field index:%ld, name:%s, value:%s\n", j, rows[i].fields[j].name, rows[i].fields[j].value);
            free(rows[i].fields[j].value);
        }
        free(rows[i].fields);
    }
    free(rows);
    free_headers(&headers);
    fclose(csv_file);
    fclose(output_file);
    return 0;
}