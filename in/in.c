#include <stdlib.h>

#include "../utils/log/log.h"
#include "../utils/custom_file/custom_file.h"

#include "in.h"

in_t *CFD_Allocate_In()
{
    in_t *in = (in_t *)malloc(sizeof(in_t));
    if (in != NULL)
    {
        in->geometry = CFD_Allocate_In_Geometry();
        in->fluid = CFD_Allocate_In_Fluid();
        in->file = file_allocate();

        if (in->geometry != NULL &&
            in->fluid != NULL &&
            in->file != NULL)
        {
            return in;
        }
    }

    CFD_Free_In(in);
    log_fatal("Error: Could not allocate memory for in");
    exit(EXIT_FAILURE);
}

geometry_t *CFD_Allocate_In_Geometry()
{
    geometry_t *geometry = (geometry_t *)malloc(sizeof(geometry_t));
    if (geometry != NULL)
    {
        return geometry;
    }

    log_fatal("Error: Could not allocate memory for in->geometry");
    exit(EXIT_FAILURE);
}

fluid_t *CFD_Allocate_In_Fluid()
{
    fluid_t *fluid = (fluid_t *)malloc(sizeof(fluid_t));
    if (fluid != NULL)
    {
        return fluid;
    }

    log_fatal("Error: Could not allocate memory for in->fluid");
    exit(EXIT_FAILURE);
}

void CFD_Free_In(in_t *in)
{
    if (in != NULL)
    {
        CFD_Free_In_Geometry(in->geometry);
        CFD_Free_In_Fluid(in->fluid);
        file_free(in->file);
        free(in);
    }
}

void CFD_Free_In_Geometry(geometry_t *geometry)
{
    if (geometry != NULL)
    {
        free(geometry);
    }
}

void CFD_Free_In_Fluid(fluid_t *fluid)
{
    if (fluid != NULL)
    {
        free(fluid);
    }
}