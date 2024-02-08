#include <stdlib.h>

#include "init.h"

input_t *CFD_Input_Init()
{
    input_t *input = (input_t *)malloc(sizeof(input_t));
    if (input != NULL)
    {
        input->geometry = CFD_Input_InitGeometry();
        input->fluid = CFD_Input_InitFluid();
        input->file = CFD_Input_InitFile();

        if (input->geometry != NULL &&
            input->fluid != NULL &&
            input->file != NULL)
        {
            return input;
        }
    }

    CFD_Input_InitFree(input);
    fprintf(stderr, "Error: Could not allocate memory for input\n");
    exit(EXIT_FAILURE);
}

geometry_t *CFD_Input_InitGeometry()
{
    geometry_t *geometry = (geometry_t *)malloc(sizeof(geometry_t));
    if (geometry != NULL)
    {
        geometry->x = 0.0;
        geometry->y = 0.0;
        return geometry;
    }

    fprintf(stderr, "Error: Could not allocate memory for input->geometry\n");
    exit(EXIT_FAILURE);
}

fluid_t *CFD_Input_InitFluid()
{
    fluid_t *fluid = (fluid_t *)malloc(sizeof(fluid_t));
    if (fluid != NULL)
    {
        fluid->mu = 0.0;
        fluid->Re = 0.0;
        return fluid;
    }

    fprintf(stderr, "Error: Could not allocate memory for input->fluid\n");
    exit(EXIT_FAILURE);
}

input_file_t *CFD_Input_InitFile()
{
    input_file_t *file = (input_file_t *)malloc(sizeof(input_file_t));
    if (file != NULL)
    {
        file->name = NULL;
        file->buffer = NULL;
        file->pointer = NULL;
        return file;
    }

    fprintf(stderr, "Error: Could not allocate memory for input->file\n");
    exit(EXIT_FAILURE);
}

void CFD_Input_InitFree(input_t *input)
{
    free(input->geometry);
    free(input->fluid);
    free(input->file);
    free(input);
}