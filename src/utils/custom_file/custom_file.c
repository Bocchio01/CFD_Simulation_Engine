#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <stdbool.h>
#include "../log/log.h"

#include "custom_file.h"

custom_file_t *file_allocate()
{
    custom_file_t *file = (custom_file_t *)malloc(sizeof(custom_file_t));
    if (file != NULL)
    {
        file->name = NULL;
        file->buffer = NULL;
        file->pointer = NULL;
        file->path = NULL;
        return file;
    }

    log_fatal("Error: Could not allocate memory for file");
    exit(EXIT_FAILURE);
}

void file_free(custom_file_t *file)
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

bool file_read(custom_file_t *file)
{
    char full_path[100] = {0};

    strcpy(full_path, file->path);
    strcat(full_path, "/");
    strcat(full_path, file->name);
    strcat(full_path, ".");
    strcat(full_path, file_format_to_string(file->format));

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

bool file_write(custom_file_t *file)
{
    char full_path[100] = {0};

    strcpy(full_path, file->path);
    strcat(full_path, "/");
    strcat(full_path, file->name);
    strcat(full_path, ".");
    strcat(full_path, file_format_to_string(file->format));

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

char *file_format_to_string(format_t format)
{
    switch (format)
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

format_t file_string_to_format(char *format)
{
    if (strcasecmp(format, "csv") == 0)
    {
        return CSV;
    }
    else if (strcasecmp(format, "txt") == 0)
    {
        return TXT;
    }
    else if (strcasecmp(format, "json") == 0)
    {
        return JSON;
    }
    else
    {
        return false;
    }
}

partial_file_t *file_split_path(char *full_path)
{
    char *token;
    char *name;
    char *path;
    char *format;
    partial_file_t *partial_file = (partial_file_t *)malloc(sizeof(partial_file_t));
    if (partial_file != NULL)
    {
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
        format = token;

        partial_file->name = name;
        partial_file->path = path;
        partial_file->format = file_string_to_format(format);
        return partial_file;
    }

    log_fatal("Error: Could not allocate memory for partial file");
    exit(EXIT_FAILURE);
}
