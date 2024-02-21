#include "SCGS.h"

#include <windows.h>

typedef struct CFD_t CFD_t;

#include <stdlib.h>
#include <math.h>
#include "../../CFD.h"
#include "../schemes/schemes.h"
#include "../../utils/cALGEBRA/cMAT.h"
#include "../../utils/cALGEBRA/cVEC.h"
#include "../../utils/cLOG/cLOG.h"

void CFD_SCGS(CFD_t *cfd)
{
    SCGS_t *scgs;

    log_info("SCGS method\n");

    scgs = CFD_SCGS_Allocate(cfd);

    for (int iteration = 0; iteration < cfd->engine->method->maxIter; iteration++)
    {
        CFD_SCGS_Reset(scgs);

        for (cfd->engine->method->index->j = cfd->engine->mesh->n_ghosts;
             cfd->engine->method->index->j < cfd->engine->mesh->nodes->Ny + cfd->engine->mesh->n_ghosts;
             cfd->engine->method->index->j++)
        {
            for (cfd->engine->method->index->i = cfd->engine->mesh->n_ghosts;
                 cfd->engine->method->index->i < cfd->engine->mesh->nodes->Nx + cfd->engine->mesh->n_ghosts;
                 cfd->engine->method->index->i++)
            {

                CFD_SCGS_System_Compose(cfd, scgs);

                CFD_SCGS_BC_NoSlip_Normal(cfd, scgs);

                CFD_SCGS_System_Solve(scgs);

                CFD_SCGS_Apply_Correction(cfd, scgs);

                CFD_SCGS_Update_Residual(scgs);
            }
        }

        CFD_SCGS_BC_NoSlip_Tangetial(cfd, scgs);

        if (iteration % 50 == 0)
        {
            log_info("\nIteration:\t%d\nResidual:\t%.10f", iteration + 1, fmax(scgs->residual->u, fmax(scgs->residual->v, scgs->residual->p)));
            log_debug("Residuals: u = %f, v = %f, p = %f\n", scgs->residual->u, scgs->residual->v, scgs->residual->p);
        }

        if (fmax(scgs->residual->u, fmax(scgs->residual->v, scgs->residual->p)) < cfd->engine->method->tolerance &&
            iteration > 1)
        {
            log_info("Algorithm converged in %d iterations", iteration);

            log_info("\nIteration:\t%d\nResidual:\t%.10f", iteration + 1, fmax(scgs->residual->u, fmax(scgs->residual->v, scgs->residual->p)));
            log_debug("Residuals: u = %f, v = %f, p = %f\n", scgs->residual->u, scgs->residual->v, scgs->residual->p);

            log_debug("U matrix");
            MAT_Print_States(cfd->engine->method->state->u);

            log_debug("V matrix");
            MAT_Print_States(cfd->engine->method->state->v);

            log_debug("P matrix");
            MAT_Print_States(cfd->engine->method->state->p);

            break;
        }
    }
}

SCGS_t *CFD_SCGS_Allocate(CFD_t *cfd)
{
    SCGS_t *scgs;

    scgs = (SCGS_t *)malloc(sizeof(SCGS_t));

    if (scgs != NULL)
    {
        scgs->vanka = (Vanka_t *)malloc(sizeof(Vanka_t));
        scgs->residual = (residual_t *)malloc(sizeof(residual_t));

        if (scgs->vanka != NULL &&
            scgs->residual != NULL)
        {
            scgs->vanka->A = MAT_Init(5, 5);
            scgs->vanka->R = VEC_Init(5);
            scgs->vanka->x = VEC_Init(5);

            if (scgs->vanka->A != NULL &&
                scgs->vanka->R != NULL &&
                scgs->vanka->x != NULL &&
                scgs->residual != NULL)
            {
                return scgs;
            }
        }
    }

    log_fatal("Failed to allocate memory for SCGS method");
    exit(EXIT_FAILURE);
}

void CFD_SCGS_Free(SCGS_t *scgs)
{
    MAT_Free(scgs->vanka->A);
    VEC_Free(scgs->vanka->R);
    VEC_Free(scgs->vanka->x);
    free(scgs->residual);
    free(scgs->vanka);
    free(scgs);
}

void CFD_SCGS_Reset(SCGS_t *scgs)
{
    scgs->residual->u = 0.0;
    scgs->residual->v = 0.0;
    scgs->residual->p = 0.0;
}

void CFD_SCGS_System_Compose(CFD_t *cfd, SCGS_t *scgs)
{
    cVEC_t *A_coefficients;
    double Ap[4];

    uint8_t i = cfd->engine->method->index->i;
    uint8_t j = cfd->engine->method->index->j;

    typedef struct
    {
        int i;
        int j;
        phi_t phi;
    } position;

    position positions[] = {
        {-1, 0, u},
        {0, 0, u},
        {0, -1, v},
        {0, 0, v}};

    for (int el = 0; el < 4; el++)
    {
        A_coefficients = VEC_Sum(
            cfd->engine->schemes->convection->callable(cfd, i + positions[el].i, j + positions[el].j, positions[el].phi),
            cfd->engine->schemes->diffusion->callable(cfd, i + positions[el].i, j + positions[el].j));

        Ap[el] = A_coefficients->data[PP];
        scgs->vanka->R->data[el] = 0.0;

        for (uint8_t r = 0; r < A_coefficients->length; r++)
        {
            double phi = getState(cfd, positions[el].phi, i + positions[el].i + ((r / 5) % 5) - 2, j + positions[el].j + (r % 5) - 2);

            scgs->vanka->R->data[el] += ((r == PP) ? -1.0 : +1.0) * (A_coefficients->data[r]) * phi;
        }
    }

    scgs->vanka->R->data[0] += (getState(cfd, p, i - 1, j + 0) - getState(cfd, p, i + 0, j + 0)) * cfd->engine->mesh->element->size->dy;
    scgs->vanka->R->data[1] += (getState(cfd, p, i + 0, j + 0) - getState(cfd, p, i + 1, j + 0)) * cfd->engine->mesh->element->size->dy;
    scgs->vanka->R->data[2] += (getState(cfd, p, i + 0, j - 1) - getState(cfd, p, i + 0, j + 0)) * cfd->engine->mesh->element->size->dx;
    scgs->vanka->R->data[3] += (getState(cfd, p, i + 0, j + 0) - getState(cfd, p, i + 0, j + 1)) * cfd->engine->mesh->element->size->dx;
    scgs->vanka->R->data[4] = -((getState(cfd, u, i + 0, j + 0) - getState(cfd, u, i - 1, j + 0)) * cfd->engine->mesh->element->size->dy +
                                (getState(cfd, v, i + 0, j + 0) - getState(cfd, v, i + 0, j - 1)) * cfd->engine->mesh->element->size->dx);

    scgs->vanka->A->data[0][0] = Ap[0] / cfd->engine->method->under_relaxation_factors->u;
    scgs->vanka->A->data[1][1] = Ap[1] / cfd->engine->method->under_relaxation_factors->u;
    scgs->vanka->A->data[2][2] = Ap[2] / cfd->engine->method->under_relaxation_factors->v;
    scgs->vanka->A->data[3][3] = Ap[3] / cfd->engine->method->under_relaxation_factors->v;

    scgs->vanka->A->data[4][0] = -1.0 * cfd->engine->mesh->element->size->dy;
    scgs->vanka->A->data[4][1] = +1.0 * cfd->engine->mesh->element->size->dy;
    scgs->vanka->A->data[4][2] = -1.0 * cfd->engine->mesh->element->size->dx;
    scgs->vanka->A->data[4][3] = +1.0 * cfd->engine->mesh->element->size->dx;

    scgs->vanka->A->data[0][4] = +1.0 * cfd->engine->mesh->element->size->dy;
    scgs->vanka->A->data[1][4] = -1.0 * cfd->engine->mesh->element->size->dy;
    scgs->vanka->A->data[2][4] = +1.0 * cfd->engine->mesh->element->size->dx;
    scgs->vanka->A->data[3][4] = -1.0 * cfd->engine->mesh->element->size->dx;
}

void CFD_SCGS_System_Solve(SCGS_t *scgs)
{
    double DEN;
    double r1;
    double r2;
    double r3;
    double r4;

    r1 = scgs->vanka->A->data[4][0] / scgs->vanka->A->data[0][0];
    r2 = scgs->vanka->A->data[4][1] / scgs->vanka->A->data[1][1];
    r3 = scgs->vanka->A->data[4][2] / scgs->vanka->A->data[2][2];
    r4 = scgs->vanka->A->data[4][3] / scgs->vanka->A->data[3][3];

    DEN = r1 * scgs->vanka->A->data[0][4] +
          r2 * scgs->vanka->A->data[1][4] +
          r3 * scgs->vanka->A->data[2][4] +
          r4 * scgs->vanka->A->data[3][4];

    scgs->vanka->x->data[4] = (r1 * scgs->vanka->R->data[0] +
                               r2 * scgs->vanka->R->data[1] +
                               r3 * scgs->vanka->R->data[2] +
                               r4 * scgs->vanka->R->data[3] -
                               scgs->vanka->R->data[4]) /
                              DEN;

    scgs->vanka->x->data[0] = (scgs->vanka->R->data[0] - scgs->vanka->A->data[0][4] * scgs->vanka->x->data[4]) / scgs->vanka->A->data[0][0];
    scgs->vanka->x->data[1] = (scgs->vanka->R->data[1] - scgs->vanka->A->data[1][4] * scgs->vanka->x->data[4]) / scgs->vanka->A->data[1][1];
    scgs->vanka->x->data[2] = (scgs->vanka->R->data[2] - scgs->vanka->A->data[2][4] * scgs->vanka->x->data[4]) / scgs->vanka->A->data[2][2];
    scgs->vanka->x->data[3] = (scgs->vanka->R->data[3] - scgs->vanka->A->data[3][4] * scgs->vanka->x->data[4]) / scgs->vanka->A->data[3][3];
}

void CFD_SCGS_Apply_Correction(CFD_t *cfd, SCGS_t *scgs)
{
    uint8_t i = cfd->engine->method->index->i;
    uint8_t j = cfd->engine->method->index->j;

    cfd->engine->method->state->u->data[j + 0][i - 1] += scgs->vanka->x->data[0];
    cfd->engine->method->state->u->data[j + 0][i + 0] += scgs->vanka->x->data[1];
    cfd->engine->method->state->v->data[j - 1][i + 0] += scgs->vanka->x->data[2];
    cfd->engine->method->state->v->data[j + 0][i + 0] += scgs->vanka->x->data[3];
    cfd->engine->method->state->p->data[j + 0][i + 0] += scgs->vanka->x->data[4];
}

void CFD_SCGS_Update_Residual(SCGS_t *scgs)
{
    scgs->residual->u += (fabs(scgs->vanka->R->data[0]) + fabs(scgs->vanka->R->data[1])) / 2.0;
    scgs->residual->v += (fabs(scgs->vanka->R->data[2]) + fabs(scgs->vanka->R->data[3])) / 2.0;
    scgs->residual->p += fabs(scgs->vanka->R->data[4]);
}
