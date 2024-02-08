#ifndef OUTPUT_H
#define OUTPUT_H

#include <stdio.h>
#include <stdint.h>

typedef enum
{
    CSV,
    TXT,
    JSON,
} output_format_t;

typedef struct
{
    char *name;
    char *buffer;
    FILE *pointer;
    output_format_t format;
} output_file_t;

typedef struct
{
    int data;
    output_file_t *file;
} output_t;

output_t *CFD_InitOutput();

#endif