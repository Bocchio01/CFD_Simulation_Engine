#ifndef CONVECTION_H
#define CONVECTION_H

#include <stdint.h>
#include "../../utils/cALGEBRA/cVEC.h"

typedef struct CFD_t CFD_t;
typedef struct F_coefficients_t F_coefficients_t;
typedef enum phi_t phi_t;

typedef cVEC_t *(*convection_function_t)(CFD_t *cfd, uint8_t i, uint8_t j, phi_t phi);

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

void CFD_Setup_Convection(CFD_t *cfd);

double getState(CFD_t *cfd, phi_t phi, int i, int j);

F_coefficients_t engineSchemeConvectionF(CFD_t *cfd, int i, int j, phi_t phi);

cVEC_t *engineSchemeConvectionUDS(CFD_t *cfd, uint8_t i, uint8_t j, phi_t phi);

cVEC_t *engineSchemeConvectionCDS(CFD_t *cfd, uint8_t i, uint8_t j, phi_t phi);

cVEC_t *engineSchemeConvectionQUICK(CFD_t *cfd, uint8_t i, uint8_t j, phi_t phi);

cVEC_t *engineSchemeConvectionHYBRID(CFD_t *cfd, uint8_t i, uint8_t j, phi_t phi);

#endif