#include <stdlib.h>

#include "solver.h"

solver_t *CFD_InitSolver()
{
    solver_t *solver = (solver_t *)malloc(sizeof(solver_t));
    if (solver != NULL)
    {
        return solver;
    }

    fprintf(stderr, "Error: Could not allocate memory for solver\n");
    exit(EXIT_FAILURE);
}