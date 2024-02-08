#ifndef CFD_H
#define CFD_H

#include "input/input.h"
#include "solver/solver.h"
#include "output/output.h"

typedef struct CFD_t
{
    input_t *input;
    solver_t *solver;
    output_t *output;
} CFD_t;

CFD_t *CFD_Init();

void CFD_Free(CFD_t *cfd);

void CFD_Config(CFD_t *cfd, int argc, char *argv[]);

void CFD_Solve(CFD_t *cfd);

void CFD_Output(CFD_t *cfd);

#endif
