#ifndef SOLVER_H
#define SOLVER_H

// typedef struct CFD_t CFD_t;

#include <stdio.h>
#include <stdint.h>

#include "mesh/mesh.h"
#include "methods/methods.h"
#include "schemes/schemes.h"

typedef struct
{
    mesh_t *mesh;
    method_t *method;
    schemes_t *schemes;
} solver_t;

solver_t *CFD_Solver_Init();

mesh_t *CFD_InitSolverMesh();
method_t *CFD_InitSolverMethod();
schemes_t *CFD_InitSolverSchemes();

void CFD_FreeSolver(solver_t *solver);

#endif