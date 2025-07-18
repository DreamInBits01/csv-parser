#include "main.h"
void parse_args(char **argv)
{
    while (*argv)
    {
        printf("arugment %s\n", *argv);
        argv++;
    }
}
int main(int argc, char **argv)
{
    parse_args(argv);
    char **lines = NULL;
    char *file_path = NULL;
    printf("first arg: %s", *argv);
    if (argv[1] && strcmp(argv[1], "--filepath") == 0)
    {
        file_path = argv[2];
        printf("Filepath was provided, %s\n", file_path);
    };
    int capacity = INITIAL_CAPACITY;
    lines = malloc(capacity * sizeof(char *));
    lines[0] = "Test1";
    lines[1] = "Test2";
    lines[2] = "Test3";
    lines[3] = "Test4";
    // lines[0] = 1;
    // lines[1] = 2;
    // lines[2] = 3;
    // lines[3] = 3;
    while (*lines)
    {
        printf("Line:%c\n", **lines);
        lines++;
    };
    return 0;
}