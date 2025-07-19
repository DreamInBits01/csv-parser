#include "main.h"
void parse_args(int argc, char **argv, user_arugments *user_arugments)
{

    for (size_t i = 0; i < argc; i++)
    {
        if (strcmp(argv[i], "--file-location") == 0)
        {
            if (i + 1 < argc)
            {
                user_arugments->file_location = argv[++i];
            }
            else
            {
                printf("Error: --file-location requires a value");
                exit(1);
            }
        };
        if (strcmp(argv[i], "--output-location") == 0)
        {
            if (i + 1 < argc)
            {
                user_arugments->output_location = argv[++i];
            }
            else
            {
                printf("Error: --output-location requires a value");
                exit(1);
            }
        }
    }
}
int main(int argc, char **argv)
{
    user_arugments user_arugments = {0};
    parse_args(argc, argv, &user_arugments);
    printf("User arguments, file location:%s\n", user_arugments.file_location);
    printf("User arguments, output location:%s\n", user_arugments.output_location);
    char **lines = NULL;
    int capacity = INITIAL_CAPACITY;
    lines = malloc(capacity * sizeof(char *));
    lines[0] = "Test1";
    lines[1] = "Test2";
    lines[2] = "Test3";
    lines[3] = "Test4";
    while (*lines)
    {
        printf("Line:%c\n", **lines);
        lines++;
    };
    return 0;
}