#include "convection.h"

Ap_coefficients_t solverSchemeConvectionUDS(state_t *state, element_size_t *element_size)
{
    Ap_coefficients_t Ap;
    Ap.u[0] = 0.0;
    Ap.u[1] = 0.0;
    Ap.v[0] = 0.0;
    Ap.v[1] = 0.0;
    return Ap;
}

Ap_coefficients_t solverSchemeConvectionHYBRID(state_t *state, element_size_t *element_size)
{
    Ap_coefficients_t Ap;
    Ap.u[0] = 0.0;
    Ap.u[1] = 0.0;
    Ap.v[0] = 0.0;
    Ap.v[1] = 0.0;
    return Ap;
}

Ap_coefficients_t solverSchemeConvectionQUICK(state_t *state, element_size_t *element_size)
{
    Ap_coefficients_t Ap;
    Ap.u[0] = 0.0;
    Ap.u[1] = 0.0;
    Ap.v[0] = 0.0;
    Ap.v[1] = 0.0;
    return Ap;
}