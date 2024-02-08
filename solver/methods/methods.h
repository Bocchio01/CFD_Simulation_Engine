#ifndef METHODS_H
#define METHODS_H

#include "SCGS.h"
#include "SIMPLE.h"

#include "../../utils/algebra/matrices.h"

typedef enum
{
    SCGS,
    SIMPLE,
} method_type_t;

typedef struct
{
    matrix_t U;
    matrix_t V;
    matrix_t P;
} state_t;

typedef struct
{
    float u;
    float v;
    float p;
} under_relaxation_factors_t;

typedef struct
{
    method_type_t type;
    float tolerance;
    int maxIter;
    under_relaxation_factors_t *under_relaxation_factors;
} method_t;

#endif