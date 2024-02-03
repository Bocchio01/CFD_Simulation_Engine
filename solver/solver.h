#ifndef SOLVER_H
#define SOLVER_H

#include <stdio.h>
#include <stdint.h>
#include "../types.h"

double residual[5];
double x[5];

void composeVankaMatrix(Ap_coefficients_t *Ap_coefficients, cell_size_t *cell_size);
void solveVankaMatrix();

#endif