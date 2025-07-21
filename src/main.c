#include "main.h"
int main(int argc, char **argv)
{
    UserArguments user_arugments = {0};
    parse_args(argc, argv, &user_arugments);
    printf("User arguments, file location:%s\n", user_arugments.file_location);
    printf("User arguments, output location:%s\n", user_arugments.output_location);
    FILE *csv_file = fopen(user_arugments.file_location, "r");
    if (csv_file == NULL)
    {
        printf("Error while opening the requested file!\n");
        exit(1);
    }
    int count = 0;
    char buffer[MAX_LINE_LENGTH];
    Headers headers = get_headers(csv_file);
    // int headers_capacity = 5;
    // char **headers = malloc(headers_capacity * sizeof(char *));
    // if (headers == NULL)
    // {
    //     printf("Headers allocation failed!");
    //     exit(1);
    // }
    // int headers_count = 0;
    // if (fgets(buffer, MAX_LINE_LENGTH, csv_file))
    // {
    //     buffer[strcspn(buffer, "\r\n")] = 0; // strip trailing newline
    //     char *token = strtok(buffer, ",");
    //     int current_token = 0;
    //     while (token != NULL)
    //     {
    //         // each token is a header string;

    //         if (headers_count >= headers_capacity)
    //         {
    //             headers_capacity += 5;
    //             headers = realloc(headers, headers_capacity * sizeof(char *));
    //             if (headers == NULL)
    //             {
    //                 printf("Headers allocation failed!");
    //                 exit(1);
    //             }
    //         }
    //         // malloc memory for the header
    //         headers[headers_count] = malloc(strlen(token) + 1);
    //         if (headers[headers_count] == NULL)
    //         {
    //             printf("Headers allocation failed!");
    //             exit(1);
    //         };
    //         // copy the header into the allocated memory
    //         strcpy(headers[headers_count], token);
    //         printf("Added header:%s\n", headers[headers_count]);
    //         token = strtok(NULL, ",");
    //         headers_count++;
    //     }
    // }

    int capacity = INITIAL_LINES_CAPACITY;
    char **lines = NULL;
    lines = malloc(capacity * sizeof(char *));
    // lines[0] = "Test1";
    // lines[1] = "Test2";
    // lines[2] = "Test3";
    // lines[3] = "Test4";

    // while (fgets(buffer, MAX_LINE_LENGTH, csv_file))
    // {
    //     // if (count >= capacity)
    //     // {
    //     //     capacity *= 2;
    //     //     lines = realloc(lines, capacity * sizeof(char *));
    //     // }
    //     // lines[count] = malloc(strlen(buffer) + 1);
    //     // if (!lines[count])
    //     // {
    //     //     fprintf(stderr, "Memory allocation failed\n");
    //     //     return 1;
    //     // }
    //     // strcpy(lines[count], buffer);
    //     char *token = strtok(buffer, ",");
    //     int field = 1;
    //     printf("line buffer:%s\n", buffer);
    //     while (token != NULL)
    //     {
    //         // get headers, loop over tokens, for each token create a field struct with the key and value, then push it to the row, finally push the row
    //         char *clean_token = remove_quotes(token);
    //         printf("Line:%s field:%d\n", clean_token, field);
    //         token = strtok(NULL, ",");
    //     }
    //     field++;
    //     // count++;
    // };
    free_headers(&headers);
    fclose(csv_file);
    return 0;
}