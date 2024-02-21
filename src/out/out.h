#ifndef OUTPUT_H
#define OUTPUT_H

typedef struct CFD_t CFD_t;

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

void CFD_Collocate_Fields(CFD_t *cfd);

void CFD_Save_Results(CFD_t *cfd);

#endif