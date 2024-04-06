#ifndef SCGS_H
#define SCGS_H

typedef struct CFD_t CFD_t;

#include <stdio.h>
#include <stdint.h>

#include "libs/cJSON/cJSON.h"
#include "libs/cALGEBRA/cMAT2D.h"
#include "libs/cALGEBRA/cVEC.h"

#include "../../schemes/schemes.h"
#include "../../methods/methods.h"
#include "SCGS_BC.h"

typedef struct
{
    uint16_t i;
    uint16_t j;
} SCGS_index_t;

typedef struct
{
    double u;
    double v;
    double p;
} SCGS_residual_t;

typedef struct
{
    int8_t i;
    int8_t j;
    phi_t phi;
} SCGS_position;

typedef struct
{
    cVEC_t *x;
    cVEC_t *R;
    cMAT2D_t *A;
} SCGS_vanka_t;

typedef struct
{
    float u;
    float v;
    float p;
} SCGS_under_relaxation_t;

typedef struct
{
    cMAT2D_t *u;
    cMAT2D_t *v;
    cMAT2D_t *p;
} SCGS_state_t;

typedef struct SCGS_t
{
    SCGS_index_t *index;
    SCGS_residual_t *residual;
    SCGS_vanka_t *vanka;
    cVEC_t *A_coefficients;
    SCGS_under_relaxation_t *under_relaxation;
    SCGS_state_t *state;
    SCGS_state_t *state_star;
} SCGS_t;

void CFD_SCGS(CFD_t *cfd, cJSON *args);

SCGS_t *CFD_SCGS_Allocate(CFD_t *cfd, cJSON *args);

void CFD_SCGS_Free(SCGS_t *scgs);

void CFD_SCGS_Reset(SCGS_t *scgs);

void CFD_SCGS_System_Compose(CFD_t *cfd, SCGS_t *scgs);

void CFD_SCGS_System_Solve(SCGS_t *scgs);

void CFD_SCGS_Apply_Correction(CFD_t *cfd, SCGS_t *scgs);

void CFD_SCGS_Update_Residual(SCGS_t *scgs);

#endif