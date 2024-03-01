#ifndef SCGS_H
#define SCGS_H

typedef struct CFD_t CFD_t;

#include <stdio.h>
#include <stdint.h>

#include "../../utils/cALGEBRA/cMAT.h"
#include "../../utils/cALGEBRA/cVEC.h"

#include "../schemes/schemes.h"
#include "../methods/methods.h"
#include "SCGS_BC.h"

typedef struct residual_t
{
    double u;
    double v;
    double p;
} residual_t;

typedef struct
{
    cVEC_t *x;
    cVEC_t *R;
    cMAT_t *A;
} Vanka_t;

typedef struct SCGS_t
{
    residual_t *residual;
    Vanka_t *vanka;
    cVEC_t *A_coefficients;
} SCGS_t;

void CFD_SCGS(CFD_t *cfd);

SCGS_t *CFD_SCGS_Allocate();

void CFD_SCGS_Free(SCGS_t *scgs);

void CFD_SCGS_Reset(SCGS_t *scgs);

void CFD_SCGS_System_Compose(CFD_t *cfd, SCGS_t *scgs);

void CFD_SCGS_System_Solve(SCGS_t *scgs);

void CFD_SCGS_Apply_Correction(CFD_t *cfd, SCGS_t *scgs);

void CFD_SCGS_Update_Residual(SCGS_t *scgs);

#endif