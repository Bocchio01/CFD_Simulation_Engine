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

    uint16_t rows = cfd->engine->mesh->data->x->rows;
    uint16_t cols = cfd->engine->mesh->data->x->cols;

    cMAT_t *UC = MAT_Init(rows, cols);
    cMAT_t *VC = MAT_Init(rows, cols);

    for (uint16_t j = cfd->engine->mesh->n_ghosts; j < cfd->engine->mesh->nodes->Ny + cfd->engine->mesh->n_ghosts; j++)
    {
        for (uint16_t i = cfd->engine->mesh->n_ghosts; i < cfd->engine->mesh->nodes->Nx + cfd->engine->mesh->n_ghosts; i++)
        {

            UC->data[j][i] = 1.0 / 2.0 * (cfd->engine->method->state->u->data[j][i] + cfd->engine->method->state->u->data[j][i - 1]);
            VC->data[j][i] = 1.0 / 2.0 * (cfd->engine->method->state->v->data[j][i] + cfd->engine->method->state->v->data[j - 1][i]);
        }
    }

    MAT_Copy(UC, cfd->engine->method->state->u);
    MAT_Copy(VC, cfd->engine->method->state->v);
}

void CFD_Save_Results(CFD_t *cfd)
{
    cfd->out->file->buffer = (char *)malloc(100 * sizeof(char));
    sprintf(cfd->out->file->buffer, "%s\n", cfd->in->file->name);
    FILE_Write(cfd->out->file, WRITE);

    sprintf(cfd->out->file->buffer, "RE: %f\n", cfd->in->fluid->Re);
    FILE_Write(cfd->out->file, APPEND);

    sprintf(cfd->out->file->buffer, "ITERATIONS: %d\n", cfd->engine->method->iteractions + 1);
    FILE_Write(cfd->out->file, APPEND);

    sprintf(cfd->out->file->buffer, "RESIDUALS:");
    FILE_Write(cfd->out->file, APPEND);

    for (uint16_t i = 0; i < cfd->engine->method->iteractions; i += 50)
    {
        sprintf(cfd->out->file->buffer, " %f", cfd->engine->method->residual->data[i]);
        FILE_Write(cfd->out->file, APPEND);
    }

    sprintf(cfd->out->file->buffer, " %f", cfd->engine->method->residual->data[cfd->engine->method->iteractions - 1]);
    FILE_Write(cfd->out->file, APPEND);

    sprintf(cfd->out->file->buffer, "\n");
    FILE_Write(cfd->out->file, APPEND);

    sprintf(cfd->out->file->buffer, "VARIABLES = \"X\", \"Y\", \"U\", \"V\", \"P\"\n");
    FILE_Write(cfd->out->file, APPEND);

    sprintf(cfd->out->file->buffer, "ZONE F=POINT, I=%d, J=%d\n", cfd->engine->mesh->nodes->Nx, cfd->engine->mesh->nodes->Ny);
    FILE_Write(cfd->out->file, APPEND);

    for (uint16_t j = cfd->engine->mesh->n_ghosts; j < cfd->engine->mesh->nodes->Ny + cfd->engine->mesh->n_ghosts; j++)
    {
        for (uint16_t i = cfd->engine->mesh->n_ghosts; i < cfd->engine->mesh->nodes->Nx + cfd->engine->mesh->n_ghosts; i++)
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