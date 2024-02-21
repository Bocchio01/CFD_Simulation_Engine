#include <stdlib.h>

#include "../utils/cLOG/cLOG.h"

#include "../utils/cFILE/cFILE.h"
#include "../utils/cALGEBRA/cMAT.h"

#include "../CFD.h"

#include "out.h"

out_t *CFD_Allocate_Out()
{
    out_t *out = (out_t *)malloc(sizeof(out_t));
    if (out != NULL)
    {
        out->file = FILE_Init();
        return out;
    }

    log_fatal("Error: Could not allocate memory for out");
    exit(EXIT_FAILURE);
}

void CFD_Free_Out(out_t *out)
{
    if (out != NULL)
    {
        FILE_Free(out->file);
        free(out);
    }
}

void CFD_Collocate_Fields(CFD_t *cfd)
{

    uint8_t rows = cfd->engine->mesh->data->x->rows;
    uint8_t cols = cfd->engine->mesh->data->x->cols;

    cMAT_t *UC = MAT_Init(rows, cols);
    cMAT_t *VC = MAT_Init(rows, cols);

    for (uint8_t j = cfd->engine->mesh->n_ghosts; j < rows - cfd->engine->mesh->n_ghosts; j++)
    {
        for (uint8_t i = cfd->engine->mesh->n_ghosts; i < cols - cfd->engine->mesh->n_ghosts; i++)
        {

            UC->data[j][i] = 1.0 / 2.0 * (cfd->engine->method->state->u->data[j][i] + cfd->engine->method->state->u->data[j][i - 1]);
            VC->data[j][i] = 1.0 / 2.0 * (cfd->engine->method->state->v->data[j][i] + cfd->engine->method->state->v->data[j - 1][i]);
        }
    }

    cfd->engine->method->state->u = UC;
    cfd->engine->method->state->v = VC;
}

void CFD_Save_Results(CFD_t *cfd)
{

    cfd->out->file->buffer = (char *)malloc(100 * sizeof(char));
    sprintf(cfd->out->file->buffer, "X,Y,U,V,P\n");
    FILE_Write(cfd->out->file, WRITE);

    uint8_t rows = cfd->engine->mesh->data->x->rows;
    uint8_t cols = cfd->engine->mesh->data->x->cols;

    for (uint8_t j = cfd->engine->mesh->n_ghosts; j < rows - cfd->engine->mesh->n_ghosts; j++)
    {
        for (uint8_t i = cfd->engine->mesh->n_ghosts; i < cols - cfd->engine->mesh->n_ghosts; i++)
        {

            sprintf(cfd->out->file->buffer, "%f,%f,%f,%f,%f\n",
                    cfd->engine->mesh->data->x->data[j][i],
                    cfd->engine->mesh->data->y->data[j][i],
                    cfd->engine->method->state->u->data[j][i],
                    cfd->engine->method->state->v->data[j][i],
                    cfd->engine->method->state->p->data[j][i]);

            FILE_Write(cfd->out->file, APPEND);
        }
    }
}