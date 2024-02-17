#include <stdlib.h>

#include "../utils/cLOG/cLOG.h"

#include "../utils/cFILE/cFILE.h"

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