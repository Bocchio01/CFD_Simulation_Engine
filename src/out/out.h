#ifndef OUTPUT_H
#define OUTPUT_H

#include "../utils/custom_file/custom_file.h"

#include <stdio.h>
#include <stdint.h>

typedef struct
{
    int data;
    custom_file_t *file;
} out_t;

out_t *CFD_Allocate_Out();

void CFD_Free_Out(out_t *out);

#endif