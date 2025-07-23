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
        if (buffer[buffer_length - 2] == '"')
        {
            buffer[buffer_length - 2] = '\0';
        }
    }
    return buffer;
}
char *remove_comma_between_quotes(char *buffer)
{
    bool inside_quotes = false;
    int buffer_length = strlen(buffer);
    for (size_t i = 0; i < buffer_length; i++)
    {
        if (buffer[i] == '"' && inside_quotes)
        {
            inside_quotes = false;
        }
        else if (buffer[i] == '"' && inside_quotes == false)
        {
            inside_quotes = true;
        };
        if (inside_quotes)
        {
            if (buffer[i] == ',')
            {
                buffer[i] = '.';
            }
        }
    };
    return buffer;
}
// void write_csv_row(FILE *fd, Row **rows, int rows_count)
// {
//     for (size_t i = 0; i < rows_count; i++)
//     {
//         for (size_t j = 0; j < rows[i]->field_count; j++)
//         {
//             fputs(rows[i]->fields[j].value, fd);
//             if (i < rows[i]->field_count - 1)
//             {
//                 fputs(",", fd);
//             }
//         }
//         fputs("\n", fd);
//     }
// }
void write_csv_row(FILE *fd, const Row *row)
{
    for (size_t i = 0; i < row->field_count; i++)
    {

        fputs(row->fields[i].value, fd);
        if (i < row->field_count - 1)
        {
            fputs(",", fd);
        }
    }
}
// char *remove_comma_between_quotes(char *buffer)
// {
//     bool inside_quotes = false;
//     int buffer_length = strlen(buffer);
//     for (size_t i = 0; i < buffer_length; i++)
//     {
//         if (buffer[i] == '"')
//         {
//             if (inside_quotes)
//             {
//                 if (buffer[i + 1] == '"')
//                 {
//                     i++; // Escaped quote: skip next
//                 }
//                 else
//                 {
//                     inside_quotes = false; // Closing quote
//                 }
//             }
//             else
//             {
//                 inside_quotes = true; // Opening quote
//             }
//         }
//         if (inside_quotes)
//         {
//             if (buffer[i] == ',')
//             {
//                 buffer[i] = '.';
//             }
//         }
//     };
//     return buffer;
// }