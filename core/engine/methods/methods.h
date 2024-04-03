#ifndef METHODS_H
#define METHODS_H

typedef struct CFD_t CFD_t;

#include "SCGS/SCGS.h"
#include "SIMPLE/SIMPLE.h"

#include "libs/cALGEBRA/cMAT2D.h"

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
    cMAT2D_t *u;
    cMAT2D_t *v;
    cMAT2D_t *p;
} method_state_t;

typedef struct
{
    method_type_t type;
    float tolerance;
    uint16_t maxIter;
    uint16_t iteractions;
    double CPU_time;
    cVEC_t *residual;
    method_index_t *index;
    method_state_t *state;
    method_function_t callable;
} method_t;

void CFD_Setup_Method(CFD_t *cfd);

void CFD_Run_Method(CFD_t *cfd);

double CFD_Get_State(CFD_t *cfd, phi_t phi, int i, int j);

#endif