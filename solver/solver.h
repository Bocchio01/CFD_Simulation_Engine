#ifndef SOLVER_H
#define SOLVER_H

typedef struct CFD_t CFD_t;

#include <stdio.h>
#include <stdint.h>

#include "../utils/algebra/algebra.h"

// #include "mesh/mesh.h"
// #include "methods/methods.h"
// #include "schemes/schemes.h"

typedef struct
{
    int a;
    // mesh_t mesh;
    // method_t method;
    // schemes_t schemes;
} solver_t;

solver_t *CFD_InitSolver();

#endif