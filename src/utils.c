#include "utils.h"
void parse_args(int argc, char **argv, UserArguments *user_arugments)
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
char *remove_quotes(char *buffer)
{
    if (buffer == NULL)
        return NULL;
    int len = strlen(buffer);
    if (len >= 2 && buffer[0] == '"' && buffer[len - 1] == '"')
    {
        buffer[len - 1] = '\0';
        return buffer + 1;
    }
    return buffer;
}