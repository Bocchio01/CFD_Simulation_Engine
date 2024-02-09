#include <stdlib.h>

#include "../utils/log/log.h"

#include "../utils/custom_file/custom_file.h"

#include "out.h"

out_t *CFD_Allocate_Out()
{
    out_t *out = (out_t *)malloc(sizeof(out_t));
    if (out != NULL)
    {
        out->file = file_allocate();
        return out;
    }

    log_fatal("Error: Could not allocate memory for out");
    exit(EXIT_FAILURE);
}

void CFD_Free_Out(out_t *out)
{
    if (out != NULL)
    {
        file_free(out->file);
        free(out);
    }
}