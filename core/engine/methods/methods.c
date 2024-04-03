#include <stdlib.h>

#include "methods.h"

#include "libs/cLOG/cLOG.h"
#include "libs/cALGEBRA/cVEC.h"
#include "libs/cALGEBRA/cMAT2D.h"

#include "../../CFD.h"

void CFD_Setup_Method(CFD_t *cfd)
{
    switch (cfd->engine->method->type)
    {
    case SCGS:
        cfd->engine->method->callable = CFD_SCGS;
        break;
    case SIMPLE:
        cfd->engine->method->callable = CFD_SIMPLE;
        break;
    }

    uint16_t rows = cfd->engine->mesh->data->x->rows;
    uint16_t cols = cfd->engine->mesh->data->x->cols;
    uint16_t maxIter = cfd->engine->method->maxIter;

    cfd->engine->method->residual = VEC_Init(maxIter);

    cfd->engine->method->state->u = MAT2D_Init(rows, cols);
    cfd->engine->method->state->v = MAT2D_Init(rows, cols);
    cfd->engine->method->state->p = MAT2D_Init(rows, cols);

    // Already initialized to 0 in MAT2D_Init
    // for (uint16_t j = 0; j < rows; j++)
    // {
    //     for (uint16_t i = 0; i < cols; i++)
    //     {
    //         cfd->engine->method->state->u->data[j][i] = 0.0;
    //         cfd->engine->method->state->v->data[j][i] = 0.0;
    //         cfd->engine->method->state->p->data[j][i] = 0.0;
    //     }
    // }
}

void CFD_Run_Method(CFD_t *cfd)
{
    cfd->engine->method->callable(cfd);
}

double CFD_Get_State(CFD_t *cfd, phi_t phi, int i, int j)
{

    uint16_t rows = cfd->engine->mesh->data->x->rows;
    uint16_t cols = cfd->engine->mesh->data->x->cols;

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