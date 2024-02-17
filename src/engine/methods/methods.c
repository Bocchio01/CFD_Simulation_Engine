#include <stdlib.h>

#include "methods.h"

#include "../../utils/cALGEBRA/cMAT.h"

#include "../../CFD.h"

void CFD_Setup_Method(CFD_t *cfd)
{
    switch (cfd->engine->method->type)
    {
    case SCGS:
        cfd->engine->method->callable = CFD_SCGS;
        break;
    case SIMPLE:
        cfd->engine->method->callable = methodSIMPLE;
        break;
    }

    uint8_t grid_dimension_x = cfd->engine->mesh->data->x->rows;
    uint8_t grid_dimension_y = cfd->engine->mesh->data->x->cols;

    cfd->engine->method->state->u = MAT_Init(
        grid_dimension_x,
        grid_dimension_y);

    cfd->engine->method->state->v = MAT_Init(
        grid_dimension_x,
        grid_dimension_y);

    cfd->engine->method->state->p = MAT_Init(
        grid_dimension_x,
        grid_dimension_y);

    cfd->engine->method->state_old->u = MAT_Init(
        grid_dimension_x,
        grid_dimension_y);

    cfd->engine->method->state_old->v = MAT_Init(
        grid_dimension_x,
        grid_dimension_y);

    cfd->engine->method->state_old->p = MAT_Init(
        grid_dimension_x,
        grid_dimension_y);

    for (uint8_t i = 0; i < grid_dimension_x; i++)
    {
        for (uint8_t j = 0; j < grid_dimension_y; j++)
        {
            cfd->engine->method->state->u->data[i][j] = 0.0;
            cfd->engine->method->state->v->data[i][j] = 0.0;
            cfd->engine->method->state->p->data[i][j] = 0.0;

            cfd->engine->method->state_old->u->data[i][j] = 0.0;
            cfd->engine->method->state_old->v->data[i][j] = 0.0;
            cfd->engine->method->state_old->p->data[i][j] = 0.0;
        }
    }
}

void CFD_Run_Method(CFD_t *cfd)
{
    cfd->engine->method->callable(cfd);
}