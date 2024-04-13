#include "SCGS_BC.h"

#include "SCGS.h"
#include "../../../CFD.h"
#include "libs/cALGEBRA/cMAT2D.h"
#include <math.h>

void CFD_SCGS_BC_NoSlip_Normal(CFD_t *cfd, SCGS_t *scgs)
{
    uint8_t dim = (int)(0.5 / 2 / cfd->engine->mesh->element->size->dx);
    uint8_t px = cfd->engine->mesh->n_ghosts + (int)(cfd->engine->mesh->nodes->Nx / 4);
    uint8_t py = cfd->engine->mesh->n_ghosts + (int)(cfd->engine->mesh->nodes->Ny / 2);

    if (cfd->engine->method->index->i == px + dim)
    {
        scgs->vanka->A->data[0][0] = 1.0;
        scgs->vanka->A->data[0][4] = 0.0;
        scgs->vanka->R->data[0] = 0.0;

        scgs->vanka->A->data[4][0] = 0.0;
    }

    if (cfd->engine->method->index->i == px - dim)
    {
        scgs->vanka->A->data[1][1] = 1.0;
        scgs->vanka->A->data[1][4] = 0.0;
        scgs->vanka->R->data[1] = 0.0;

        scgs->vanka->A->data[4][1] = 0.0;
    }

    if (cfd->engine->method->index->j == py + dim)
    {
        scgs->vanka->A->data[2][2] = 1.0;
        scgs->vanka->A->data[2][4] = 0.0;
        scgs->vanka->R->data[2] = 0.0;

        scgs->vanka->A->data[4][2] = 0.0;
    }

    if (cfd->engine->method->index->j == py - dim)
    {
        scgs->vanka->A->data[3][3] = 1.0;
        scgs->vanka->A->data[3][4] = 0.0;
        scgs->vanka->R->data[3] = 0.0;

        scgs->vanka->A->data[4][3] = 0.0;
    }
}

void CFD_SCGS_BC_NoSlip_Tangetial(CFD_t *cfd)
{
    float moduls = cfd->in->uLid;
    float angle = 0.0 * M_PI / 180.0;
    float u = moduls * cos(angle);
    float v = moduls * sin(angle);

    uint8_t dim = (int)(0.5 / 2 / cfd->engine->mesh->element->size->dx);
    uint8_t px = cfd->engine->mesh->n_ghosts + (int)(cfd->engine->mesh->nodes->Nx / 4);
    uint8_t py = cfd->engine->mesh->n_ghosts + (int)(cfd->engine->mesh->nodes->Ny / 2);

    for (uint16_t i = px - dim;
         i < px + dim;
         i++)
    {
        cfd->engine->method->state->u->data[py + dim - 1][i] = cfd->engine->method->state->u->data[py + dim][i];
        cfd->engine->method->state->u->data[py + dim - 1][i] = cfd->engine->method->state->u->data[py + dim][i];
        cfd->engine->method->state->v->data[py - dim + 1][i] = 0;
        cfd->engine->method->state->v->data[py - dim + 1][i] = 0;
    }

    for (uint16_t j = py - dim;
         j < py + dim;
         j++)
    {
        cfd->engine->method->state->v->data[j][px + dim - 1] = cfd->engine->method->state->v->data[j][px + dim];
        cfd->engine->method->state->v->data[j][px - dim + 1] = cfd->engine->method->state->v->data[j][px - dim];
        cfd->engine->method->state->u->data[j][px + dim - 1] = 0;
        cfd->engine->method->state->u->data[j][px - dim + 1] = 0;
    }

    // Horizontal walls
    for (uint16_t i = 0;
         i < cfd->engine->mesh->nodes->Nx + 2 * cfd->engine->mesh->n_ghosts;
         i++)
    {
        cfd->engine->method->state->u->data[cfd->engine->mesh->n_ghosts - 1][i] = u;
        cfd->engine->method->state->u->data[cfd->engine->mesh->n_ghosts + cfd->engine->mesh->nodes->Ny][i] = u;

        cfd->engine->method->state->v->data[cfd->engine->mesh->n_ghosts - 1][i] = v;
        cfd->engine->method->state->v->data[cfd->engine->mesh->n_ghosts + cfd->engine->mesh->nodes->Ny][i] = v;
    }

    // Vertical walls
    for (uint16_t j = 0;
         j < cfd->engine->mesh->nodes->Ny + 2 * cfd->engine->mesh->n_ghosts;
         j++)
    {
        cfd->engine->method->state->u->data[j][cfd->engine->mesh->n_ghosts - 1] = u;
        cfd->engine->method->state->u->data[j][cfd->engine->mesh->n_ghosts + cfd->engine->mesh->nodes->Nx] = u;

        cfd->engine->method->state->v->data[j][cfd->engine->mesh->n_ghosts - 1] = v;
        cfd->engine->method->state->v->data[j][cfd->engine->mesh->n_ghosts + cfd->engine->mesh->nodes->Nx] = v;
    }
}