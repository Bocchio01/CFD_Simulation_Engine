#include <stdlib.h>

#include "methods.h"

#include "../../utils/cLOG/cLOG.h"
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

double CFD_Get_State(CFD_t *cfd, phi_t phi, int i, int j)
{

    uint8_t rows = cfd->engine->mesh->data->x->rows;
    uint8_t cols = cfd->engine->mesh->data->x->cols;

    switch (phi)
    {
    case u:
        return (i >= 0 && j >= 0 && i < cols && j < rows) ? cfd->engine->method->state->u->data[j][i] : 0.0;

    case v:
        return (i >= 0 && j >= 0 && i < cols && j < rows) ? cfd->engine->method->state->v->data[j][i] : 0.0;

    case p:
        return (i >= 0 && j >= 0 && i < cols && j < rows) ? cfd->engine->method->state->p->data[j][i] : 0.0;

    default:
        log_fatal("Error: CFD_Get_State phi not found");
        exit(EXIT_FAILURE);
        break;
    }
}