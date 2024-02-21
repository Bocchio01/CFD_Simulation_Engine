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

    uint8_t rows = cfd->engine->mesh->data->x->rows;
    uint8_t cols = cfd->engine->mesh->data->x->cols;

    cfd->engine->method->state->u = MAT_Init(
        rows,
        cols);

    cfd->engine->method->state->v = MAT_Init(
        rows,
        cols);

    cfd->engine->method->state->p = MAT_Init(
        rows,
        cols);

    for (uint8_t j = 0; j < rows; j++)
    {
        for (uint8_t i = 0; i < cols; i++)
        {
            cfd->engine->method->state->u->data[j][i] = 0.0;
            cfd->engine->method->state->v->data[j][i] = 0.0;
            cfd->engine->method->state->p->data[j][i] = 0.0;
        }
    }
}

void CFD_Run_Method(CFD_t *cfd)
{
    cfd->engine->method->callable(cfd);
}