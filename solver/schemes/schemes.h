#ifndef SCHEMES_H
#define SCHEMES_H

#include "convection.h"
#include "diffusion.h"

typedef struct
{
    scheme_convection_t *convection;
    scheme_diffusion_t *diffusion;
} schemes_t;

#endif