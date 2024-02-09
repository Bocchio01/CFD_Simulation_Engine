#ifndef SCGS_H
#define SCGS_H

typedef struct CFD_t CFD_t;

#include <stdio.h>
#include <stdint.h>

// typedef struct
// {
// } SCGS_t;

void methodSCGS(CFD_t *cfd);

// matrix_t composeVankaMatrix(CFD_t *cfd);
// state_t solveVankaMatrix(matrix_t *vankaMat);

// void boundaryConditions(CFD_t *cfd);

// void solve(settings_t *in, engine_t *engine);
// void composeVankaMatrix(Ap_coefficients_t *Ap_coefficients, element_size_t *cell_size);
// void solveVankaMatrix();

#endif