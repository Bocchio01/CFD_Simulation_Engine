#ifndef METHODS_H
#define METHODS_H

#include "SCGS.h"
#include "SIMPLE.h"

#include "../../utils/algebra/algebra.h"

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
    int max_iterations;
    float tolerance;
    under_relaxation_factors_t under_relaxation_factors;
} method_t;

#endif