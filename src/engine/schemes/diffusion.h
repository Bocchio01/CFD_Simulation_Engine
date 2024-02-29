#ifndef DIFFUSION_H
#define DIFFUSION_H

#include <stdint.h>
#include "../../utils/cALGEBRA/cVEC.h"

typedef struct CFD_t CFD_t;
typedef struct F_coefficients_t F_coefficients_t;
typedef enum phi_t phi_t;

typedef void (*diffusion_function_t)(CFD_t *cfd, uint8_t i, uint8_t j);

typedef enum
{
    SECOND_ORDER,
    FOURTH_ORDER,
} diffusion_type_t;

typedef struct
{
    diffusion_type_t type;
    diffusion_function_t callable;
    cVEC_t *coefficients;
} scheme_diffusion_t;

void CFD_Setup_Diffusion(CFD_t *cfd);

void CFD_Scheme_Diffusion_Second(CFD_t *cfd, uint8_t i, uint8_t j);

void CFD_Scheme_Diffusion_Fourth(CFD_t *cfd, uint8_t i, uint8_t j);

#endif