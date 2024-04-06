typedef struct CFD_t CFD_t;

#include "../SIMPLE.h"
#include "P_equation.h"
#include "../../../schemes/schemes.h"

#include "../../../../CFD.h"

#include <stdint.h>

void CFD_SIMPLE_P_Compute_Coefficients(CFD_t *cfd, SIMPLE_t *simple)
{
    uint16_t i;
    uint16_t j;

    for (simple->index->j = cfd->engine->mesh->n_ghosts;
         simple->index->j < cfd->engine->mesh->nodes->Ny + cfd->engine->mesh->n_ghosts;
         simple->index->j++)
    {
        for (simple->index->i = cfd->engine->mesh->n_ghosts;
             simple->index->i < cfd->engine->mesh->nodes->Nx + cfd->engine->mesh->n_ghosts;
             simple->index->i++)
        {
            i = simple->index->i;
            j = simple->index->j;

            // Check why they might take consider coefficients out of the MAT3D size
            simple->Ap_coefficients->pp->data[j][i][EP] = cfd->engine->mesh->element->size->dy * cfd->engine->mesh->element->size->dy / simple->Ap_coefficients->u->data[j + 0][i + 0][PP];
            simple->Ap_coefficients->pp->data[j][i][WP] = cfd->engine->mesh->element->size->dy * cfd->engine->mesh->element->size->dy / simple->Ap_coefficients->u->data[j + 0][i - 1][PP];
            simple->Ap_coefficients->pp->data[j][i][PN] = cfd->engine->mesh->element->size->dx * cfd->engine->mesh->element->size->dx / simple->Ap_coefficients->v->data[j + 0][i + 0][PP];
            simple->Ap_coefficients->pp->data[j][i][PS] = cfd->engine->mesh->element->size->dx * cfd->engine->mesh->element->size->dx / simple->Ap_coefficients->v->data[j - 1][i + 0][PP];

            simple->Ap_coefficients->pp->data[j][i][PP] = simple->Ap_coefficients->pp->data[j][i][EP] + simple->Ap_coefficients->pp->data[j][i][WP] + simple->Ap_coefficients->pp->data[j][i][PN] + simple->Ap_coefficients->pp->data[j][i][PS];
        }
    }
}

void CFD_SIMPLE_P_Apply_BC(CFD_t *cfd, SIMPLE_t *simple)
{
    for (uint16_t i = 0;
         i < cfd->engine->mesh->nodes->Nx + 2 * cfd->engine->mesh->n_ghosts;
         i++)
    {
        simple->Ap_coefficients->pp->data[cfd->engine->mesh->n_ghosts][i][PS] = 0.0;
        simple->Ap_coefficients->pp->data[cfd->engine->mesh->nodes->Ny + cfd->engine->mesh->n_ghosts - 1][i][PN] = 0.0;
    }

    for (uint16_t j = 0;
         j < cfd->engine->mesh->nodes->Ny + 2 * cfd->engine->mesh->n_ghosts;
         j++)
    {
        simple->Ap_coefficients->pp->data[j][cfd->engine->mesh->n_ghosts][WP] = 0.0;
        simple->Ap_coefficients->pp->data[j][cfd->engine->mesh->nodes->Nx + cfd->engine->mesh->n_ghosts - 1][EP] = 0.0;
    }
}

void CFD_SIMPLE_P_Compute_Residuals(CFD_t *cfd, SIMPLE_t *simple)
{
    uint16_t i;
    uint16_t j;

    for (simple->index->j = cfd->engine->mesh->n_ghosts;
         simple->index->j < cfd->engine->mesh->nodes->Ny + cfd->engine->mesh->n_ghosts;
         simple->index->j++)
    {
        for (simple->index->i = cfd->engine->mesh->n_ghosts;
             simple->index->i < cfd->engine->mesh->nodes->Nx + cfd->engine->mesh->n_ghosts;
             simple->index->i++)
        {
            i = simple->index->i;
            j = simple->index->j;
            simple->residual->p->data[j][i] = 0.0;

            simple->residual->p->data[j][i] = -((CFD_Get_State(cfd, u, i + 0, j + 0) - CFD_Get_State(cfd, u, i - 1, j + 0)) * cfd->engine->mesh->element->size->dy +
                                                (CFD_Get_State(cfd, v, i + 0, j + 0) - CFD_Get_State(cfd, v, i + 0, j - 1)) * cfd->engine->mesh->element->size->dx);
        }
    }
}

void CFD_SIMPLE_P_Compute_State(CFD_t *cfd, SIMPLE_t *simple)
{
    uint16_t i;
    uint16_t j;
    double sum;
    int nb_i;
    int nb_j;

    for (uint8_t sweep = 0; sweep < simple->number_of_sweeps->pp; sweep++)
    {
        for (simple->index->j = cfd->engine->mesh->n_ghosts;
             simple->index->j < cfd->engine->mesh->nodes->Ny + cfd->engine->mesh->n_ghosts;
             simple->index->j++)
        {
            for (simple->index->i = cfd->engine->mesh->n_ghosts;
                 simple->index->i < cfd->engine->mesh->nodes->Nx + cfd->engine->mesh->n_ghosts;
                 simple->index->i++)
            {
                i = simple->index->i;
                j = simple->index->j;

                sum = 0.0;

                for (uint8_t k = 0; k < simple->Ap_coefficients->pp->depth; k++)
                {
                    nb_i = i + ((k / 5) % 5) - 2;
                    nb_j = j + (k % 5) - 2;

                    if (k != PP &&
                        nb_i >= 0 && nb_i < cfd->engine->mesh->nodes->Nx + 2 * cfd->engine->mesh->n_ghosts &&
                        nb_j >= 0 && nb_j < cfd->engine->mesh->nodes->Ny + 2 * cfd->engine->mesh->n_ghosts)
                    {
                        sum += simple->Ap_coefficients->pp->data[j][i][k] * simple->state->pp->data[nb_j][nb_i];
                    }
                }

                sum += simple->residual->p->data[j][i];
                simple->state->pp->data[j][i] = (sum / simple->Ap_coefficients->pp->data[j][i][PP]);
            }
        }
    }
}

void CFD_SIMPLE_P_Compute_Correct_States(CFD_t *cfd, SIMPLE_t *simple)
{
    uint16_t i;
    uint16_t j;

    for (simple->index->j = cfd->engine->mesh->n_ghosts;
         simple->index->j < cfd->engine->mesh->nodes->Ny + cfd->engine->mesh->n_ghosts;
         simple->index->j++)
    {
        for (simple->index->i = cfd->engine->mesh->n_ghosts;
             simple->index->i < cfd->engine->mesh->nodes->Nx + cfd->engine->mesh->n_ghosts;
             simple->index->i++)
        {
            i = simple->index->i;
            j = simple->index->j;

            cfd->engine->method->state->p->data[j][i] = CFD_Get_State(cfd, p, i, j) + simple->under_relaxation->p * simple->state->pp->data[j][i];
        }
    }
}