#ifndef CONVECTION_H
#define CONVECTION_H

#include <stdint.h>
#include "../../utils/cALGEBRA/cVEC.h"

typedef struct CFD_t CFD_t;
typedef struct F_coefficients_t F_coefficients_t;
typedef enum phi_t phi_t;

typedef void (*convection_function_t)(CFD_t *cfd, uint8_t i, uint8_t j, phi_t phi);

typedef enum
{
    UDS,
    HYBRID,
    QUICK,
} convection_type_t;

typedef struct F_coefficients_t
{
    double w;
    double e;
    double s;
    double n;
} F_coefficients_t;

typedef struct
{
    convection_type_t type;
    convection_function_t callable;
    cVEC_t *coefficients;
    F_coefficients_t *F;
} scheme_convection_t;

void CFD_Setup_Convection(CFD_t *cfd);

void CFD_Scheme_Get_Flux(CFD_t *cfd, int i, int j, phi_t phi);

void CFD_Scheme_Convection_UDS(CFD_t *cfd, uint8_t i, uint8_t j, phi_t phi);

void CFD_Scheme_Convection_CDS(CFD_t *cfd, uint8_t i, uint8_t j, phi_t phi);

void CFD_Scheme_Convection_QUICK(CFD_t *cfd, uint8_t i, uint8_t j, phi_t phi);

void CFD_Scheme_Convection_HYBRID(CFD_t *cfd, uint8_t i, uint8_t j, phi_t phi);

#endif