#ifndef DIFFUSION_H
#define DIFFUSION_H

#include <stdint.h>
#include "../../utils/cALGEBRA/cVEC.h"

typedef struct CFD_t CFD_t;
typedef struct F_coefficients_t F_coefficients_t;
typedef enum phi_t phi_t;

typedef cVEC_t *(*diffusion_function_t)(CFD_t *cfd, uint8_t i, uint8_t j);

typedef enum
{
    SECOND_ORDER,
    FOURTH_ORDER,
} diffusion_type_t;

typedef struct
{
    diffusion_type_t type;
    diffusion_function_t callable;
} scheme_diffusion_t;

void CFD_Setup_Diffusion(CFD_t *cfd);

cVEC_t *engineSchemeDiffusion2(CFD_t *cfd, uint8_t i, uint8_t j);

cVEC_t *engineSchemeDiffusion4(CFD_t *cfd, uint8_t i, uint8_t j);

#endif