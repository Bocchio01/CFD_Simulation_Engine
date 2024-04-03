#include "SIMPLE.h"

typedef struct CFD_t CFD_t;

#include <stdlib.h>
#include <math.h>
#include "../methods.h"
#include "../../../CFD.h"
#include "../../schemes/schemes.h"
#include "libs/cALGEBRA/cMAT3D.h"
#include "libs/cALGEBRA/cMAT2D.h"
#include "libs/cALGEBRA/cVEC.h"
#include "libs/cLOG/cLOG.h"
#include "P_equation.h"
#include "V_equation.h"
#include "U_equation.h"

void CFD_SIMPLE(CFD_t *cfd)
{
    SIMPLE_t *simple;

    simple = CFD_SIMPLE_Allocate(cfd);

    for (cfd->engine->method->iteractions = 0;
         cfd->engine->method->iteractions < cfd->engine->method->maxIter;
         cfd->engine->method->iteractions++)
    {

        CFD_SIMPLE_Compute_U(cfd, simple);
        CFD_SIMPLE_Compute_V(cfd, simple);
        CFD_SIMPLE_Compute_P(cfd, simple);

        MAT2D_Print_States(cfd->engine->method->state->u);
        MAT2D_Print_States(cfd->engine->method->state->v);
        MAT2D_Print_States(cfd->engine->method->state->p);

        cfd->engine->method->residual->data[cfd->engine->method->iteractions] = 0.0;
        for (uint16_t j = 0; j < simple->residual->p->rows; j++)
        {
            for (uint16_t i = 0; i < simple->residual->p->cols; i++)
            {
                cfd->engine->method->residual->data[cfd->engine->method->iteractions] = fmax(
                    cfd->engine->method->residual->data[cfd->engine->method->iteractions],
                    fmax(fmax(simple->residual->u->data[j][i], simple->residual->v->data[j][i]), simple->residual->p->data[j][i]));
            }
        }

        if (isnan(cfd->engine->method->residual->data[cfd->engine->method->iteractions]) ||
            isinf(cfd->engine->method->residual->data[cfd->engine->method->iteractions]))
        {
            log_fatal("Algorithm diverged at iteration %d", cfd->engine->method->iteractions);
            CFD_SIMPLE_Free(simple);
            exit(EXIT_FAILURE);
        }

        if (cfd->engine->method->iteractions % 100 == 0 ||
            cfd->engine->method->residual->data[cfd->engine->method->iteractions] < cfd->engine->method->tolerance)
        {
            log_info("\nIteration:\t%d\nResidual:\t%.10f",
                     cfd->engine->method->iteractions,
                     cfd->engine->method->residual->data[cfd->engine->method->iteractions]);
        }

        if (cfd->engine->method->residual->data[cfd->engine->method->iteractions] < cfd->engine->method->tolerance &&
            cfd->engine->method->iteractions > 1)
        {
            log_info("Algorithm converged in %d iterations", cfd->engine->method->iteractions);
            CFD_SIMPLE_Free(simple);
            break;
        }
    }
}

SIMPLE_t *CFD_SIMPLE_Allocate(CFD_t *cfd)
{
    SIMPLE_t *simple;
    uint16_t rows = cfd->engine->mesh->data->x->rows;
    uint16_t cols = cfd->engine->mesh->data->x->cols;

    simple = (SIMPLE_t *)malloc(sizeof(SIMPLE_t));

    if (simple != NULL)
    {
        simple->residual = (SIMPLE_residual_t *)malloc(sizeof(SIMPLE_residual_t));
        simple->state = (SIMPLE_state_t *)malloc(sizeof(SIMPLE_state_t));
        simple->Ap_coefficients = (SIMPLE_Ap_coefficients_t *)malloc(sizeof(SIMPLE_Ap_coefficients_t));
        simple->number_of_sweeps = (SIMPLE_number_of_sweeps_t *)malloc(sizeof(SIMPLE_number_of_sweeps_t));

        if (simple->residual != NULL &&
            simple->state != NULL &&
            simple->Ap_coefficients != NULL &&
            simple->number_of_sweeps != NULL)
        {
            simple->state->u = MAT2D_Init(rows, cols);
            simple->state->v = MAT2D_Init(rows, cols);
            simple->state->pp = MAT2D_Init(rows, cols);

            simple->residual->u = MAT2D_Init(rows, cols);
            simple->residual->v = MAT2D_Init(rows, cols);
            simple->residual->p = MAT2D_Init(rows, cols);

            simple->Ap_coefficients->u = MAT3D_Init(rows, cols, EENN + 1);
            simple->Ap_coefficients->v = MAT3D_Init(rows, cols, EENN + 1);
            simple->Ap_coefficients->pp = MAT3D_Init(rows, cols, EENN + 1);

            // TODO: load sweeps from configuration file
            simple->number_of_sweeps->u = 4;
            simple->number_of_sweeps->v = 4;
            simple->number_of_sweeps->pp = 8;

            return simple;
        }
    }

    log_fatal("Failed to allocate memory for SIMPLE method");
    exit(EXIT_FAILURE);
}

void CFD_SIMPLE_Free(SIMPLE_t *simple)
{
    MAT2D_Free(simple->state->u);
    MAT2D_Free(simple->state->v);
    MAT2D_Free(simple->state->pp);
    free(simple->residual);
    free(simple->state);
    free(simple);
}

void CFD_SIMPLE_Compute_U(CFD_t *cfd, SIMPLE_t *simple)
{
    CFD_SIMPLE_U_Compute_Coefficients(cfd, simple);
    CFD_SIMPLE_U_Apply_BC(cfd);
    CFD_SIMPLE_U_Compute_Residuals(cfd, simple);
    CFD_SIMPLE_U_Compute_State(cfd, simple);
}

void CFD_SIMPLE_Compute_V(CFD_t *cfd, SIMPLE_t *simple)
{
    CFD_SIMPLE_V_Compute_Coefficients(cfd, simple);
    CFD_SIMPLE_V_Apply_BC(cfd);
    CFD_SIMPLE_V_Compute_Residuals(cfd, simple);
    CFD_SIMPLE_V_Compute_State(cfd, simple);
}

void CFD_SIMPLE_Compute_P(CFD_t *cfd, SIMPLE_t *simple)
{
    CFD_SIMPLE_P_Compute_Coefficients(cfd, simple);
    CFD_SIMPLE_P_Apply_BC(cfd, simple);
    CFD_SIMPLE_P_Compute_Residuals(cfd, simple);
    CFD_SIMPLE_P_Compute_State(cfd, simple);

    CFD_SIMPLE_U_Compute_Correct_States(cfd, simple);
    CFD_SIMPLE_V_Compute_Correct_States(cfd, simple);
    CFD_SIMPLE_P_Compute_Correct_States(cfd, simple);
}