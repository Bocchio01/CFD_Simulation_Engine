#ifndef METHODS_H
#define METHODS_H

typedef struct CFD_t CFD_t;

#include "SCGS.h"
#include "SIMPLE.h"

#include "../../utils/cALGEBRA/cMAT.h"

typedef void (*method_function_t)(CFD_t *cfd);

typedef enum
{
    SCGS,
    SIMPLE,
} method_type_t;

typedef struct
{
    uint8_t i;
    uint8_t j;
} method_index_t;

typedef struct method_state_t
{
    cMAT_t *u;
    cMAT_t *v;
    cMAT_t *p;
} method_state_t;

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
    method_index_t *index;
    method_state_t *state;
    method_state_t *state_old;
    method_function_t callable;
} method_t;

void CFD_Setup_Method(CFD_t *cfd);

void CFD_Run_Method(CFD_t *cfd);

#endif