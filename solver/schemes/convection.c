#include "convection.h"

#include "../../CFD.h"

A_coefficients_convection_t solverSchemeConvectionUDS(CFD_t *cfd)
{
    A_coefficients_convection_t Ap;
    Ap.u[0] = 0.0;
    Ap.u[1] = 0.0;
    Ap.v[0] = 0.0;
    Ap.v[1] = 0.0;
    return Ap;
}

A_coefficients_convection_t solverSchemeConvectionHYBRID(CFD_t *cfd)
{
    A_coefficients_convection_t Ap;
    Ap.u[0] = 0.0;
    Ap.u[1] = 0.0;
    Ap.v[0] = 0.0;
    Ap.v[1] = 0.0;
    return Ap;
}

A_coefficients_convection_t solverSchemeConvectionQUICK(CFD_t *cfd)
{
    A_coefficients_convection_t Ap;
    Ap.u[0] = 0.0;
    Ap.u[1] = 0.0;
    Ap.v[0] = 0.0;
    Ap.v[1] = 0.0;
    return Ap;
}