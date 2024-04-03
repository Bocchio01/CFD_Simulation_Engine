#ifndef SIMPLE_V_EQUATION_H
#define SIMPLE_V_EQUATION_H

typedef struct CFD_t CFD_t;
typedef struct SIMPLE_t SIMPLE_t;

#include "../SIMPLE.h"

void CFD_SIMPLE_V_Compute_Coefficients(CFD_t *cfd, SIMPLE_t *simple);

void CFD_SIMPLE_V_Apply_BC(CFD_t *cfd);

void CFD_SIMPLE_V_Compute_Residuals(CFD_t *cfd, SIMPLE_t *simple);

void CFD_SIMPLE_V_Compute_State(CFD_t *cfd, SIMPLE_t *simple);

void CFD_SIMPLE_V_Compute_Correct_States(CFD_t *cfd, SIMPLE_t *simple);

#endif