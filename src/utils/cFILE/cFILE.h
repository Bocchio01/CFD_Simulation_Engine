#ifndef CFILE_H
#define CFILE_H

#include <stdio.h>
#include <stdbool.h>

typedef enum
{
    CSV,
    TXT,
    JSON,
} extension_t;

typedef struct
{
    int size;
    char *name;
    char *buffer;
    FILE *pointer;
    char *path;
    extension_t extension;
} cFILE_t;

cFILE_t *FILE_Init();

void FILE_Free(cFILE_t *file);

bool FILE_Read(cFILE_t *file);

bool FILE_Write(cFILE_t *file);

char *FILE_Extension_to_String(extension_t extension);

extension_t FILE_String_to_Extension(char *extension);

cFILE_t *FILE_Parse_Path(char *full_path);

#endif