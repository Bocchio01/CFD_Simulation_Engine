#include <stdlib.h>

#include "output.h"

output_t *CFD_Output_Init()
{
    output_t *output = (output_t *)malloc(sizeof(output_t));
    if (output != NULL)
    {
        output->file = (output_file_t *)malloc(sizeof(output_file_t));
        output->file->name = NULL;
        output->file->buffer = NULL;
        output->file->pointer = NULL;
        return output;
    }

    fprintf(stderr, "Error: Could not allocate memory for output\n");
    exit(EXIT_FAILURE);
}