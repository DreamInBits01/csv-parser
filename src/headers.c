#include "headers.h"
Headers get_headers(FILE *csv_file_fd)
{
    int data_capacity = INITIAL_HEADERS_CAPACITY;
    char **data = malloc(data_capacity * sizeof(char *));
    if (data == NULL)
    {
        PRINT_ERROR(ALLOCATION_ERROR, "Headers");
        exit(1);
    };
    int headers_count = 0;
    char buffer[MAX_LINE_LENGTH];
    if (fgets(buffer, MAX_LINE_LENGTH, csv_file_fd))
    {
        buffer[strcspn(buffer, "\r\n")] = 0; // strip trailing newline
        char *token = strtok(remove_comma_between_quotes(buffer), ",");
        // int current_token = 0;
        while (token != NULL)
        {

            if (headers_count >= data_capacity)
            {
                data_capacity += INITIAL_HEADERS_CAPACITY;
                char **temp = realloc(data, data_capacity * sizeof(char *));
                if (temp == NULL)
                {
                    // clean up headers

                    PRINT_ERROR(ALLOCATION_ERROR, "Headers");
                    free(data);
                    exit(1);
                }
                data = temp;
            }
            // malloc memory for the header
            data[headers_count] = strdup(token);
            if (data[headers_count] == NULL)
            {
                PRINT_ERROR(ALLOCATION_ERROR, "Headers");
                // clean up headers
                exit(1);
            };
            // copy the header into the allocated memory
            // strcpy(data[headers_count], token);
            token = strtok(NULL, ",");
            headers_count++;
        }
    }
    Headers headers = {0};
    headers.data = data;
    headers.count = headers_count;
    return headers;
}
void write_headers(Headers *headers, FILE *output_fd)
{
    for (size_t i = 0; i < headers->count; i++)
    {
        fputs(headers->data[i], output_fd);
        if (i < headers->count - 1)
        {
            fputs(",", output_fd);
        }
    }
    fputs("\n", output_fd);
}
void free_headers(Headers *headers)
{
    if (headers && headers->data)
    {
        for (size_t i = 0; i < headers->count; i++)
        {
            free(headers->data[i]);
        }
    }
    else
    {
        printf("No headers were provided to be freed!\n");
        exit(1);
    };
    free(headers->data);
    headers->data = NULL;
    headers->count = 0;
}