#include "utils.h"
void parse_args(int argc, char **argv, UserArguments *user_arugments)
{

    for (size_t i = 1; i < argc; i++)
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
    };
    if (strcmp(user_arugments->file_location, user_arugments->output_location) == 0)
    {
        PRINT_ERROR(SAME_INPUT_OUTPUT_LOCATION);
        exit(1);
    }
}
char *remove_quotes(char *buffer)
{
    if (buffer == NULL)
        return NULL;
    int buffer_length = strlen(buffer);
    if (*buffer == '"')
    {
        buffer++;
    };
    if (buffer_length > 0)
    {
        buffer[buffer_length - 1] = '\0';
    }
    return buffer;
}
char *remove_comma_between_quotes(char *buffer)
{
    bool possible_comma_between_quotes = false;
    int buffer_length = strlen(buffer);
    for (size_t i = 0; i < buffer_length; i++)
    {
        if (buffer[i] == '"' && possible_comma_between_quotes)
        {
            possible_comma_between_quotes = false;
        }
        else if (buffer[i] == '"' && possible_comma_between_quotes == false)
        {
            possible_comma_between_quotes = true;
        };
        if (possible_comma_between_quotes)
        {
            if (buffer[i] == ',')
            {
                buffer[i] = '.';
            }
        }
    };
    return buffer;
}