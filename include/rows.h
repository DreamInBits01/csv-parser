#ifndef ROW_H
#define ROW_H
typedef struct
{
    char *name;
    char *value;
} Field;
typedef struct
{
    int field_count;
    Field *fields;
} Row;
void free_rows(Row **rows);
#endif