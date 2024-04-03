#ifndef CMAT3D_H
#define CMAT3D_H

#include <stdint.h>

typedef struct
{
    uint16_t rows;
    uint16_t cols;
    uint16_t depth;
    double ***data;
} cMAT3D_t;

cMAT3D_t *MAT3D_Init(uint16_t rows, uint16_t cols, uint16_t depth);

cMAT3D_t *MAT3D_Transpose(cMAT3D_t *A);

cMAT3D_t *MAT3D_MultiplyScalar(double scalar, cMAT3D_t *A);

cMAT3D_t *MAT3D_Sum(cMAT3D_t *A, cMAT3D_t *B);

cMAT3D_t *MAT3D_Multiply(cMAT3D_t *A, cMAT3D_t *B);

void MAT3D_Free(cMAT3D_t *A);

void MAT3D_Copy(cMAT3D_t *A, cMAT3D_t *B);

void MAT3D_Print(cMAT3D_t *A);

#endif
