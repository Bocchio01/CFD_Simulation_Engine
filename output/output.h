#ifndef OUTPUT_H
#define OUTPUT_H

#include <stdio.h>
#include <stdbool.h>
#include <stdint.h>

typedef struct
{
    // bool plot;
    bool print_residual;
    bool print_solution;

    bool overwrite_file;
    char *output_file;
    FILE *output_file_pointer;
} output_t;

#endif