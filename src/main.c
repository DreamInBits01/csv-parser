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
    int lines_count = 0;
    char buffer[MAX_LINE_LENGTH];
    Headers headers = get_headers(csv_file);
    int capacity = INITIAL_LINES_CAPACITY;
    Row *lines = NULL;
    lines = (Row *)malloc(capacity * sizeof(Row));
    while (fgets(buffer, MAX_LINE_LENGTH, csv_file))
    {
        if (lines_count >= capacity)
        {
            capacity *= 2;
            Row *temp = realloc(lines, capacity * sizeof(Row));
            if (!temp)
            {
                fprintf(stderr, "Failed to realloc lines array\n");
                free(lines);
                return 1;
            }
            lines = temp;
        }
        lines[lines_count].fields = malloc(headers.count * sizeof(Field));
        if (!lines[lines_count].fields)
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
            lines[lines_count].fields[token_place].name = headers.data[token_place];
            lines[lines_count].fields[token_place].value = strdup(clean_token);

            if (!lines[lines_count].fields[token_place].value)
            {
                fprintf(stderr, "strdup failed for token: %s\n", clean_token);
                free_headers(&headers);

                for (int k = 0; k < token_place; k++)
                {
                    free(lines[lines_count].fields[k].value);
                }
                free(lines[lines_count].fields);
                for (int i = 0; i < lines_count; i++)
                {
                    for (int j = 0; j < lines[i].field_count; j++)
                    {
                        free(lines[i].fields[j].value);
                    }
                    free(lines[i].fields);
                }
                free(lines);
                free_headers(&headers);
                fclose(csv_file);
                exit(1);
                free(lines);
                exit(1);
            }
            // get headers, loop over tokens, for each token create a field struct with the key and value, then push it to the row, finally push the row
            token = strtok(NULL, ",");
            token_place++;
        }
        lines[lines_count].field_count = token_place;
        token_place = 0;
        lines_count++;
    };

    for (size_t i = 0; i < lines_count; i++)
    {
        printf("Processing row %ld with %d fields\n", i, lines[i].field_count);
        for (size_t j = 0; j < lines[i].field_count; j++)
        {
            printf("  Field index:%ld, name:%s, value:%s\n", j, lines[i].fields[j].name, lines[i].fields[j].value);
            free(lines[i].fields[j].value);
        }
        free(lines[i].fields);
    }
    free(lines);
    free_headers(&headers);
    fclose(csv_file);
    return 0;
}