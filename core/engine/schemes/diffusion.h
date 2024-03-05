#ifndef DIFFUSION_H
#define DIFFUSION_H

#include <stdint.h>
#include "libs/cALGEBRA/cVEC.h"

typedef struct CFD_t CFD_t;
typedef struct F_coefficients_t F_coefficients_t;
typedef enum phi_t phi_t;

typedef void (*diffusion_function_t)(CFD_t *cfd);

typedef enum
{
    SECOND,
    FOURTH,
} diffusion_type_t;

typedef struct
{
    diffusion_type_t type;
    diffusion_function_t callable;
    cVEC_t *coefficients;
} scheme_diffusion_t;

void CFD_Setup_Diffusion(CFD_t *cfd);

void CFD_Scheme_Diffusion_SECOND(CFD_t *cfd);

void CFD_Scheme_Diffusion_FOURTH(CFD_t *cfd);

#endif