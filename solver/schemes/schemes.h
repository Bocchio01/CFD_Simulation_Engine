#ifndef SCHEMES_H
#define SCHEMES_H

#include "convection.h"
#include "diffusion.h"

typedef struct
{
    double u[2];
    double v[2];
} Ap_coefficients_t;

typedef struct
{
    scheme_convection_t convection;
    scheme_diffusion_t diffusion;
} schemes_t;

#endif