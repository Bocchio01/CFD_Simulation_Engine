#ifndef CONVECTION_H
#define CONVECTION_H

typedef struct CFD_t CFD_t;

typedef struct
{
    double u[2];
    double v[2];
} A_coefficients_convection_t;

typedef A_coefficients_convection_t (*convection_function_t)(CFD_t *cfd);

typedef enum
{
    UDS,
    HYBRID,
    QUICK,
} convection_type_t;

typedef struct
{
    convection_type_t type;
    convection_function_t callable;
} scheme_convection_t;

A_coefficients_convection_t solverSchemeConvectionUDS(CFD_t *cfd);

A_coefficients_convection_t solverSchemeConvectionHYBRID(CFD_t *cfd);

A_coefficients_convection_t solverSchemeConvectionQUICK(CFD_t *cfd);

#endif