#include "headers.h"
Headers get_headers(FILE *csv_file_fd)
{
    int headers_capacity = 5;
    char **headers = malloc(headers_capacity * sizeof(char *));
    if (headers == NULL)
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
                headers_capacity += 5;
                headers = realloc(headers, headers_capacity * sizeof(char *));
                if (headers == NULL)
                {
                    printf("Headers allocation failed!");
                    exit(1);
                }
            }
            // malloc memory for the header
            headers[headers_count] = malloc(strlen(token) + 1);
            if (headers[headers_count] == NULL)
            {
                printf("Headers allocation failed!");
                exit(1);
            };
            // copy the header into the allocated memory
            strcpy(headers[headers_count], token);
            printf("Added header:%s\n", headers[headers_count]);
            token = strtok(NULL, ",");
            headers_count++;
        }
    }
    Headers headers_struct = {0};
    headers_struct.data = headers;
    headers_struct.count = headers_count;
    return headers_struct;
}
void free_headers(Headers *headers)
{
    if (headers && headers->data)
    {
        for (size_t i = 0; i < headers->count; i++)
        {
            /* code */
            printf("Header:%s\n", headers->data[i]);
            free(headers->data[i]);
        }
    }
    else
    {
        printf("No headers were provided to be freed!");
    }
}