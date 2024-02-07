#include "solver.h"

solver_t *init_solver(settings_t *settings)
{
    solver_t *solver = (solver_t *)malloc(sizeof(solver_t));

    solver->mesh = meshInit(settings->grid_dimension, settings->domain_dimension, settings->halo_size);
    solver->state = stateInit(solver->mesh->grid_dimension, solver->mesh->halo_size);

    return solver;
}