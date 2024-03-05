#ifndef METHODS_H
#define METHODS_H

typedef struct CFD_t CFD_t;

#include "SCGS.h"
#include "SIMPLE.h"

#include "libs/cALGEBRA/cMAT.h"

typedef void (*method_function_t)(CFD_t *cfd);

typedef enum
{
    SCGS,
    SIMPLE,
} method_type_t;

typedef struct
{
    uint16_t i;
    uint16_t j;
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
    uint16_t maxIter;
    uint16_t iteractions;
    double CPU_time;
    cVEC_t *residual;
    under_relaxation_factors_t *under_relaxation_factors;
    method_index_t *index;
    method_state_t *state;
    method_function_t callable;
} method_t;

void CFD_Setup_Method(CFD_t *cfd);

void CFD_Run_Method(CFD_t *cfd);

double CFD_Get_State(CFD_t *cfd, phi_t phi, int i, int j);

#endif