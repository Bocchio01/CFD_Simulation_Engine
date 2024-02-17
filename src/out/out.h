#ifndef OUTPUT_H
#define OUTPUT_H

#include "../utils/cFILE/cFILE.h"

#include <stdio.h>
#include <stdint.h>

typedef struct
{
    int data;
    cFILE_t *file;
} out_t;

out_t *CFD_Allocate_Out();

void CFD_Free_Out(out_t *out);

#endif