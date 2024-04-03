typedef struct CFD_t CFD_t;

#include "../SIMPLE.h"
#include "V_equation.h"
#include "../../../schemes/schemes.h"

#include "../../../../CFD.h"

#include <stdint.h>

void CFD_SIMPLE_V_Compute_Coefficients(CFD_t *cfd, SIMPLE_t *simple)
{
    uint16_t i;
    uint16_t j;

    for (cfd->engine->method->index->j = cfd->engine->mesh->n_ghosts;
         cfd->engine->method->index->j < cfd->engine->mesh->nodes->Ny + cfd->engine->mesh->n_ghosts - 1;
         cfd->engine->method->index->j++)
    {
        for (cfd->engine->method->index->i = cfd->engine->mesh->n_ghosts;
             cfd->engine->method->index->i < cfd->engine->mesh->nodes->Nx + cfd->engine->mesh->n_ghosts;
             cfd->engine->method->index->i++)
        {
            i = cfd->engine->method->index->i;
            j = cfd->engine->method->index->j;

            if (i == cfd->engine->mesh->n_ghosts ||
                j == cfd->engine->mesh->n_ghosts ||
                i == cfd->engine->mesh->nodes->Nx + cfd->engine->mesh->n_ghosts - 1 ||
                j == cfd->engine->mesh->nodes->Ny + cfd->engine->mesh->n_ghosts - 1)
            {
                CFD_Scheme_Convection_UDS(cfd, i, j, v);
                CFD_Scheme_Diffusion_SECOND(cfd);
            }
            else
            {
                cfd->engine->schemes->convection->callable(cfd, i, j, v);
                cfd->engine->schemes->diffusion->callable(cfd);
            }

            for (uint16_t k = 0; k < cfd->engine->schemes->convection->coefficients->length; k++)
            {
                simple->Ap_coefficients->v->data[j][i][k] = cfd->engine->schemes->convection->coefficients->data[k] + cfd->engine->schemes->diffusion->coefficients->data[k];
            }
        }
    }
}

void CFD_SIMPLE_V_Apply_BC(CFD_t *cfd)
{
    for (uint16_t j = 0;
         j < cfd->engine->mesh->nodes->Nx + 2 * cfd->engine->mesh->n_ghosts;
         j++)
    {
        cfd->engine->method->state->v->data[j][cfd->engine->mesh->n_ghosts - 1] = 0.0 * 0.0 - cfd->engine->method->state->v->data[j][cfd->engine->mesh->n_ghosts];
        cfd->engine->method->state->v->data[j][cfd->engine->mesh->n_ghosts + cfd->engine->mesh->nodes->Nx] = 0.0 * 0.0 - cfd->engine->method->state->v->data[j][cfd->engine->mesh->n_ghosts + cfd->engine->mesh->nodes->Nx - 1];
    }
}

void CFD_SIMPLE_V_Compute_Residuals(CFD_t *cfd, SIMPLE_t *simple)
{
    uint16_t i;
    uint16_t j;
    double phi;

    for (cfd->engine->method->index->j = cfd->engine->mesh->n_ghosts;
         cfd->engine->method->index->j < cfd->engine->mesh->nodes->Ny + cfd->engine->mesh->n_ghosts - 1;
         cfd->engine->method->index->j++)
    {
        for (cfd->engine->method->index->i = cfd->engine->mesh->n_ghosts;
             cfd->engine->method->index->i < cfd->engine->mesh->nodes->Nx + cfd->engine->mesh->n_ghosts;
             cfd->engine->method->index->i++)
        {
            i = cfd->engine->method->index->i;
            j = cfd->engine->method->index->j;
            simple->residual->v->data[j][i] = 0.0;

            for (uint16_t k = 0; k < simple->Ap_coefficients->v->depth; k++)
            {
                phi = CFD_Get_State(cfd, v, i + ((k / 5) % 5) - 2, j + (k % 5) - 2);
                if (k == PP)
                {
                    simple->residual->v->data[j][i] -= simple->Ap_coefficients->v->data[j][i][k] * phi;
                }
                else
                {
                    simple->residual->v->data[j][i] += simple->Ap_coefficients->v->data[j][i][k] * phi;
                }
            }

            simple->residual->v->data[j][i] += (CFD_Get_State(cfd, p, i, j) - CFD_Get_State(cfd, p, i, j + 1)) * cfd->engine->mesh->element->size->dx;
        }
    }
}

void CFD_SIMPLE_V_Compute_State(CFD_t *cfd, SIMPLE_t *simple)
{
    uint16_t i;
    uint16_t j;
    double sum;

    for (uint8_t sweep = 0; sweep < simple->number_of_sweeps->v; sweep++)
    {
        for (cfd->engine->method->index->j = cfd->engine->mesh->n_ghosts;
             cfd->engine->method->index->j < cfd->engine->mesh->nodes->Ny + cfd->engine->mesh->n_ghosts - 1;
             cfd->engine->method->index->j++)
        {
            for (cfd->engine->method->index->i = cfd->engine->mesh->n_ghosts;
                 cfd->engine->method->index->i < cfd->engine->mesh->nodes->Nx + cfd->engine->mesh->n_ghosts;
                 cfd->engine->method->index->i++)
            {
                i = cfd->engine->method->index->i;
                j = cfd->engine->method->index->j;

                sum = 0.0;

                for (uint8_t k = 0; k < simple->Ap_coefficients->v->depth; k++)
                {
                    if (k != PP)
                    {
                        sum += simple->Ap_coefficients->v->data[j][i][k] * CFD_Get_State(cfd, v, i + ((k / 5) % 5) - 2, j + (k % 5) - 2);
                    }
                }

                sum += (CFD_Get_State(cfd, p, i, j) - CFD_Get_State(cfd, p, i, j + 1)) * cfd->engine->mesh->element->size->dx;
                cfd->engine->method->state->v->data[j][i] = 0.5 * (sum / simple->Ap_coefficients->v->data[j][i][PP]) + (1.0 - 0.5) * CFD_Get_State(cfd, v, i, j);
            }
        }
    }
}

void CFD_SIMPLE_V_Compute_Correct_States(CFD_t *cfd, SIMPLE_t *simple)
{
    uint16_t i;
    uint16_t j;
    double v_prime;

    for (cfd->engine->method->index->j = cfd->engine->mesh->n_ghosts;
         cfd->engine->method->index->j < cfd->engine->mesh->nodes->Ny + cfd->engine->mesh->n_ghosts - 1;
         cfd->engine->method->index->j++)
    {
        for (cfd->engine->method->index->i = cfd->engine->mesh->n_ghosts;
             cfd->engine->method->index->i < cfd->engine->mesh->nodes->Nx + cfd->engine->mesh->n_ghosts;
             cfd->engine->method->index->i++)
        {
            i = cfd->engine->method->index->i;
            j = cfd->engine->method->index->j;

            v_prime = cfd->engine->mesh->element->size->dx / simple->Ap_coefficients->v->data[j][i][PP] * (CFD_Get_State(cfd, p, i, j) - CFD_Get_State(cfd, p, i, j + 1));
            cfd->engine->method->state->v->data[j][i] = CFD_Get_State(cfd, v, i, j) + 0.5 * v_prime;
        }
    }
}