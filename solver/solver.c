#include <stdlib.h>

#include "solver.h"

solver_t *CFD_Solver_Init()
{
    solver_t *solver = (solver_t *)malloc(sizeof(solver_t));
    if (solver != NULL)
    {
        solver->mesh = CFD_InitSolverMesh();
        solver->method = CFD_InitSolverMethod();
        solver->schemes = CFD_InitSolverSchemes();

        if (solver->mesh != NULL &&
            solver->method != NULL &&
            solver->schemes != NULL)
        {
            return solver;
        }
    }

    CFD_FreeSolver(solver);
    fprintf(stderr, "Error: Could not allocate memory for solver\n");
    exit(EXIT_FAILURE);
}

mesh_t *CFD_InitSolverMesh()
{
    mesh_t *mesh = (mesh_t *)malloc(sizeof(mesh_t));
    if (mesh != NULL)
    {
        mesh->nodes = (mesh_nodes_t *)malloc(sizeof(mesh_nodes_t));
        mesh->element = (mesh_element_t *)malloc(sizeof(mesh_element_t));
        mesh->data = (mesh_data_t *)malloc(sizeof(mesh_data_t));

        if (mesh->nodes != NULL &&
            mesh->element != NULL &&
            mesh->data != NULL)
        {
            return mesh;
        }
    }

    fprintf(stderr, "Error: Could not allocate memory for solver->mesh\n");
    exit(EXIT_FAILURE);
}

method_t *CFD_InitSolverMethod()
{
    method_t *method = (method_t *)malloc(sizeof(method_t));
    if (method != NULL)
    {
        method->under_relaxation_factors = (under_relaxation_factors_t *)malloc(sizeof(under_relaxation_factors_t));
        if (method->under_relaxation_factors != NULL)
        {
            return method;
        }
    }

    fprintf(stderr, "Error: Could not allocate memory for solver->method\n");
    exit(EXIT_FAILURE);
}

schemes_t *CFD_InitSolverSchemes()
{
    schemes_t *schemes = (schemes_t *)malloc(sizeof(schemes_t));
    if (schemes != NULL)
    {
        schemes->convection = (scheme_convection_t *)malloc(sizeof(scheme_convection_t));
        schemes->diffusion = (scheme_diffusion_t *)malloc(sizeof(scheme_diffusion_t));
        if (schemes->convection != NULL &&
            schemes->diffusion != NULL)
        {
            return schemes;
        }
    }

    fprintf(stderr, "Error: Could not allocate memory for solver->schemes\n");
    exit(EXIT_FAILURE);
}

void CFD_FreeSolver(solver_t *solver)
{
    free(solver->mesh);
    free(solver->method);
    free(solver->schemes);
    free(solver);
}
