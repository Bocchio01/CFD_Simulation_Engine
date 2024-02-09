#ifndef CUSTOM_FILE_H
#define CUSTOM_FILE_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

typedef enum
{
    CSV,
    TXT,
    JSON,
} format_t;

typedef struct
{
    char *name;
    char *path;
    format_t format;
} partial_file_t;

typedef struct
{
    int size;
    char *name;
    char *buffer;
    FILE *pointer;
    char *path;
    format_t format;
} custom_file_t;

custom_file_t *file_allocate();

void file_free(custom_file_t *file);

bool file_read(custom_file_t *file);

bool file_write(custom_file_t *file);

char *file_format_to_string(format_t format);
format_t file_string_to_format(char *format);

partial_file_t *file_split_path(char *full_path);

#endif