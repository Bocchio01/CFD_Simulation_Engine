#ifndef SCGS_H
#define SCGS_H

typedef struct CFD_t CFD_t;

#include <stdio.h>
#include <stdint.h>

#include "../../CFD.h"
#include "../../utils/algebra/matrices.h"
#include "../../utils/algebra/vector.h"

#include "SCGS_BC.h"

typedef struct
{
    uint8_t i;
    uint8_t j;
} index_t;

typedef struct
{
    index_t *index;
    vector_t *residual;
    vector_t *Uprime;
    matrix_t *vankaMat;

} SCGS_t;

void CFD_SCGS(CFD_t *cfd);

SCGS_t *CFD_SCGS_Allocate(CFD_t *cfd); // Mallocs for everything

void CFD_SCGS_Free(SCGS_t *scgs); // Frees everything

void CFD_SCGS_Reset(SCGS_t *scgs); // Resets everything (sets to 0 probably)

void CFD_SCGS_ComposeVankaMatrix(SCGS_t *scgs); // Composes the Vanka matrix -> Inside here we call our schemes

void CFD_SCGS_SolveVankaMatrix(SCGS_t *scgs); // Solves the Vanka matrix

void CFD_SCGS_Apply_Correction(SCGS_t *scgs); // Applies the correction to the Uprime

void CFD_SCGS_Update_Residual(SCGS_t *scgs); // Updates the residual

#endif