#ifndef CVEC_H
#define CVEC_H

#include <stdint.h>

#include "libs/cALGEBRA/cMAT2D.h"

typedef struct
{
    uint16_t length;
    double *data;
} cVEC_t;

cVEC_t *VEC_Init(uint16_t length);

cVEC_t *VEC_Sum(cVEC_t *V1, cVEC_t *V2);

cVEC_t *VEC_Multiply(double scalar, cVEC_t *V);

cMAT2D_t *VEC_ToMatrix(cVEC_t *V);

void VEC_Free(cVEC_t *V);

void VEC_Print(cVEC_t *V);

#endif