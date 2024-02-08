#include "diffusion.h"

#include "../../CFD.h"

A_coefficients_diffusion_t solverSchemeDiffusion2(CFD_t *cfd)
{
    A_coefficients_diffusion_t Ap;
    Ap.u[0] = 0.0;
    Ap.u[1] = 0.0;
    Ap.v[0] = 0.0;
    Ap.v[1] = 0.0;
    return Ap;
}

A_coefficients_diffusion_t solverSchemeDiffusion4(CFD_t *cfd)
{
    A_coefficients_diffusion_t Ap;
    Ap.u[0] = 0.0;
    Ap.u[1] = 0.0;
    Ap.v[0] = 0.0;
    Ap.v[1] = 0.0;
    return Ap;
}