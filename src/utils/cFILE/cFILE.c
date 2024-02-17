/**
 * @file cFILE.c
 * @brief cFILE_t operations module
 * @details This module implements the basic file operations.
 * @date 2024-02-13
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#include "cFILE.h"

#include "../cLOG/cLOG.h"

cFILE_t *FILE_Init()
{
    cFILE_t *file = (cFILE_t *)malloc(sizeof(cFILE_t));
    if (file != NULL)
    {
        file->name = NULL;
        file->buffer = NULL;
        file->pointer = NULL;
        file->path = NULL;

        return file;
    }

    log_fatal("Error: Could not allocate memory for cFILE_t");
    exit(EXIT_FAILURE);
}

void FILE_Free(cFILE_t *file)
{
    if (file->name != NULL)
    {
        free(file->name);
    }
    if (file->buffer != NULL)
    {
        free(file->buffer);
    }
    if (file->pointer != NULL)
    {
        fclose(file->pointer);
    }
    if (file->path != NULL)
    {
        free(file->path);
    }
    free(file);
}

bool FILE_Read(cFILE_t *file)
{
    char full_path[100] = {0};

    strcpy(full_path, file->path);
    strcat(full_path, "/");
    strcat(full_path, file->name);
    strcat(full_path, ".");
    strcat(full_path, FILE_Extension_to_String(file->extension));

    file->pointer = fopen(full_path, "r");
    if (file->pointer == NULL)
    {
        log_error("Error: Unable to open file %s", full_path);
        return false;
    }

    fseek(file->pointer, 0, SEEK_END);
    file->size = ftell(file->pointer);
    fseek(file->pointer, 0, SEEK_SET);

    file->buffer = (char *)malloc(file->size + 1);

    fread(file->buffer, 1, file->size, file->pointer);
    file->buffer[file->size] = '\0';

    fclose(file->pointer);

    return true;
}

bool FILE_Write(cFILE_t *file)
{
    char full_path[100] = {0};

    strcpy(full_path, file->path);
    strcat(full_path, "/");
    strcat(full_path, file->name);
    strcat(full_path, ".");
    strcat(full_path, FILE_Extension_to_String(file->extension));

    file->pointer = fopen(full_path, "w");
    if (file->pointer == NULL)
    {
        log_error("Error: Unable to open file %s", file->name);
        return false;
    }

    fprintf(file->pointer, "%s", file->buffer);

    fclose(file->pointer);

    return true;
}

char *FILE_Extension_to_String(extension_t extension)
{
    switch (extension)
    {
    case CSV:
        return "csv";
    case TXT:
        return "txt";
    case JSON:
        return "json";
    default:
        return false;
    }
}

extension_t FILE_String_to_Extension(char *extension)
{
    if (strcasecmp(extension, "csv") == 0)
    {
        return CSV;
    }
    else if (strcasecmp(extension, "txt") == 0)
    {
        return TXT;
    }
    else if (strcasecmp(extension, "json") == 0)
    {
        return JSON;
    }
    else
    {
        return false;
    }
}

cFILE_t *FILE_Parse_Path(char *full_path)
{
    char *token;
    char *name;
    char *path;
    char *extension;

    cFILE_t *file = FILE_Init();

    token = strtok(full_path, "/");
    while (token != NULL)
    {
        name = token;
        token = strtok(NULL, "/");
    }

    token = strtok(name, ".");
    while (token != NULL)
    {
        name = token;
        token = strtok(NULL, ".");
    }

    token = strtok(full_path, name);
    path = token;
    token = strtok(name, ".");
    name = token;
    token = strtok(NULL, ".");
    extension = token;

    file->name = name;
    file->path = path;
    file->extension = FILE_String_to_Extension(extension);

    return file;
}
