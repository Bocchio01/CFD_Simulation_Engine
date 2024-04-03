#ifndef SIMPLE_H
#define SIMPLE_H

typedef struct CFD_t CFD_t;

#include <stdio.h>
#include <stdint.h>

#include "libs/cALGEBRA/cMAT3D.h"
#include "libs/cALGEBRA/cMAT2D.h"
#include "libs/cALGEBRA/cVEC.h"

#include "../../schemes/schemes.h"
#include "../../methods/methods.h"

typedef struct
{
    cMAT2D_t *u;
    cMAT2D_t *v;
    cMAT2D_t *p;
} SIMPLE_residual_t;

typedef struct
{
    cMAT3D_t *u;
    cMAT3D_t *v;
    cMAT3D_t *pp;
} SIMPLE_Ap_coefficients_t;

typedef struct
{
    cMAT2D_t *u;
    cMAT2D_t *v;
    cMAT2D_t *pp;
} SIMPLE_state_t;

typedef struct
{
    float u;
    float v;
    float pp;
} SIMPLE_number_of_sweeps_t;

typedef struct SIMPLE_t
{
    SIMPLE_residual_t *residual;
    // coefficient for all
    SIMPLE_Ap_coefficients_t *Ap_coefficients;
    SIMPLE_state_t *state;
    SIMPLE_number_of_sweeps_t *number_of_sweeps;
} SIMPLE_t;

void CFD_SIMPLE(CFD_t *cfd);

SIMPLE_t *CFD_SIMPLE_Allocate(CFD_t *cfd);

void CFD_SIMPLE_Free(SIMPLE_t *simple);

void CFD_SIMPLE_Compute_U(CFD_t *cfd, SIMPLE_t *simple);

void CFD_SIMPLE_Compute_V(CFD_t *cfd, SIMPLE_t *simple);

void CFD_SIMPLE_Compute_P(CFD_t *cfd, SIMPLE_t *simple);

#endif