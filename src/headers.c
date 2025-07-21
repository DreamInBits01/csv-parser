#include "headers.h"
Headers get_headers(FILE *csv_file_fd)
{
    int headers_capacity = INITIAL_HEADERS_CAPACITY;
    char **data = malloc(headers_capacity * sizeof(char *));
    if (data == NULL)
    {
        printf("Headers allocation failed!");
        exit(1);
    };
    int headers_count = 0;
    char buffer[MAX_LINE_LENGTH];
    if (fgets(buffer, MAX_LINE_LENGTH, csv_file_fd))
    {
        buffer[strcspn(buffer, "\r\n")] = 0; // strip trailing newline
        char *token = strtok(buffer, ",");
        // int current_token = 0;
        while (token != NULL)
        {
            // each token is a header string;

            if (headers_count >= headers_capacity)
            {
                headers_capacity += INITIAL_HEADERS_CAPACITY;
                data = realloc(data, headers_capacity * sizeof(char *));
                if (data == NULL)
                {
                    printf("Headers allocation failed!");
                    exit(1);
                }
            }
            // malloc memory for the header
            data[headers_count] = malloc(strlen(token) + 1);
            if (data[headers_count] == NULL)
            {
                printf("Headers allocation failed!");
                exit(1);
            };
            // copy the header into the allocated memory
            strcpy(data[headers_count], token);
            printf("Added header:%s\n", data[headers_count]);
            token = strtok(NULL, ",");
            headers_count++;
        }
    }
    Headers headers_struct = {0};
    headers_struct.data = data;
    headers_struct.count = headers_count;
    return headers_struct;
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
    }
}