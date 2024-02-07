#ifndef SOLVER_H
#define SOLVER_H

#include <stdio.h>
#include <stdint.h>
#include "../lib/algebra.h"

double residual[5];
double x[5];

typedef struct
{
    int i;
    int j;
    // int k;
} index_t;

typedef struct
{
    matrix_t U;
    matrix_t V;
    matrix_t P;
} state_t;

typedef struct
{
    state_t state;
    mesh_t mesh;
} solver_t;

solver_t *init_solver(settings_t *settings);
state_t *stateInit(grid_dimension_t grid_dimension, halo_size_t halo_size);

void solve(settings_t *settings, solver_t *solver);
void composeVankaMatrix(Ap_coefficients_t *Ap_coefficients, element_size_t *cell_size);
void solveVankaMatrix();

#endif