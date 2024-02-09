#include "diffusion.h"

#include "../../CFD.h"

void CFD_Setup_Diffusion(CFD_t *cfd)
{
    switch (cfd->engine->schemes->diffusion->type)
    {
    case SECOND_ORDER:
        cfd->engine->schemes->diffusion->callable = engineSchemeDiffusion2;
        break;
    case FOURTH_ORDER:
        cfd->engine->schemes->diffusion->callable = engineSchemeDiffusion4;
        break;
    }
}

A_coefficients_diffusion_t engineSchemeDiffusion2(CFD_t *cfd)
{
    A_coefficients_diffusion_t Ap;
    Ap.u[0] = 0.0;
    Ap.u[1] = 0.0;
    Ap.v[0] = 0.0;
    Ap.v[1] = 0.0;
    return Ap;
}

A_coefficients_diffusion_t engineSchemeDiffusion4(CFD_t *cfd)
{
    A_coefficients_diffusion_t Ap;
    Ap.u[0] = 0.0;
    Ap.u[1] = 0.0;
    Ap.v[0] = 0.0;
    Ap.v[1] = 0.0;
    return Ap;
}