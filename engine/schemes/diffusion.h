#ifndef DIFFUSION_H
#define DIFFUSION_H

typedef struct CFD_t CFD_t;

typedef struct
{
    double u[2];
    double v[2];
} A_coefficients_diffusion_t;

typedef A_coefficients_diffusion_t (*diffusion_function_t)(CFD_t *cfd);

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

A_coefficients_diffusion_t engineSchemeDiffusion2(CFD_t *cfd);

A_coefficients_diffusion_t engineSchemeDiffusion4(CFD_t *cfd);

#endif