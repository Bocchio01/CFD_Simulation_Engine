#include "diffusion.h"

Ap_coefficients_t solverSchemeDiffusionUDS(state_t *state, cell_size_t *cell_size)
{
    Ap_coefficients_t Ap;
    Ap.u[0] = 0.0;
    Ap.u[1] = 0.0;
    Ap.v[0] = 0.0;
    Ap.v[1] = 0.0;
    return Ap;
}

Ap_coefficients_t solverSchemeDiffusionHYBRID(state_t *state, cell_size_t *cell_size)
{
    Ap_coefficients_t Ap;
    Ap.u[0] = 0.0;
    Ap.u[1] = 0.0;
    Ap.v[0] = 0.0;
    Ap.v[1] = 0.0;
    return Ap;
}