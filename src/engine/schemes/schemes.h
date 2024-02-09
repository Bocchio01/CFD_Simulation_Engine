#ifndef SCHEMES_H
#define SCHEMES_H

typedef struct CFD_t CFD_t;

#include "convection.h"
#include "diffusion.h"

typedef struct
{
    scheme_convection_t *convection;
    scheme_diffusion_t *diffusion;
} schemes_t;

void CFD_Setup_Schemes(CFD_t *cfd);

#endif