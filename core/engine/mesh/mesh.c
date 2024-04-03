#include <stdlib.h>
#include "mesh.h"

#include "libs/cALGEBRA/cMAT2D.h"

#include "../../CFD.h"

void CFD_Setup_Mesh(CFD_t *cfd)
{
    cfd->engine->mesh->n_ghosts = 1;
    cfd->engine->mesh->element->size->dx = cfd->in->geometry->x / cfd->engine->mesh->nodes->Nx;
    cfd->engine->mesh->element->size->dy = cfd->in->geometry->y / cfd->engine->mesh->nodes->Ny;

    uint16_t rows = cfd->engine->mesh->nodes->Ny + 2 * cfd->engine->mesh->n_ghosts;
    uint16_t cols = cfd->engine->mesh->nodes->Nx + 2 * cfd->engine->mesh->n_ghosts;

    cfd->engine->mesh->data->x = MAT2D_Init(
        rows,
        cols);

    cfd->engine->mesh->data->y = MAT2D_Init(
        rows,
        cols);
}

void CFD_Generate_Mesh(CFD_t *cfd)
{
    uint16_t rows = cfd->engine->mesh->data->x->rows;
    uint16_t cols = cfd->engine->mesh->data->x->cols;

    for (uint16_t j = 0; j < rows; j++)
    {
        for (uint16_t i = 0; i < cols; i++)
        {
            cfd->engine->mesh->data->x->data[j][i] = (i - cfd->engine->mesh->n_ghosts + 0.5) * cfd->engine->mesh->element->size->dx;
            cfd->engine->mesh->data->y->data[j][i] = (j - cfd->engine->mesh->n_ghosts + 0.5) * cfd->engine->mesh->element->size->dy;
        }
    }
}