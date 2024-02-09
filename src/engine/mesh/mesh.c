#include <stdlib.h>
#include "mesh.h"

#include "../../utils/algebra/matrices.h"

#include "../../CFD.h"

void CFD_Setup_Mesh(CFD_t *cfd)
{
    cfd->engine->mesh->n_ghosts = 1;
    cfd->engine->mesh->element->size->dx = cfd->in->geometry->x / cfd->engine->mesh->nodes->Nx;
    cfd->engine->mesh->element->size->dy = cfd->in->geometry->y / cfd->engine->mesh->nodes->Ny;
}

void CFD_Generate_Mesh(CFD_t *cfd)
{
    uint8_t grid_dimension_x = cfd->engine->mesh->nodes->Nx + 2 * cfd->engine->mesh->n_ghosts;
    uint8_t grid_dimension_y = cfd->engine->mesh->nodes->Ny + 2 * cfd->engine->mesh->n_ghosts;

    cfd->engine->mesh->data->x = matAllocate(
        grid_dimension_x,
        grid_dimension_y);

    cfd->engine->mesh->data->y = matAllocate(
        grid_dimension_x,
        grid_dimension_y);

    for (uint8_t i = 0; i < grid_dimension_x; i++)
    {
        for (uint8_t j = 0; j < grid_dimension_y; j++)
        {
            cfd->engine->mesh->data->x.data[i][j] = (i - cfd->engine->mesh->n_ghosts) * cfd->engine->mesh->element->size->dx;
            cfd->engine->mesh->data->y.data[i][j] = (j - cfd->engine->mesh->n_ghosts) * cfd->engine->mesh->element->size->dy;
        }
    }
}