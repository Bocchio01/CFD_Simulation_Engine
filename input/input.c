#include <stdlib.h>

#include "input.h"

input_t *CFD_InitInput()
{
    input_t *input = (input_t *)malloc(sizeof(input_t));
    if (input != NULL)
    {
        input->file = (input_file_t *)malloc(sizeof(input_file_t));
        input->file->name = NULL;
        input->file->buffer = NULL;
        input->file->pointer = NULL;
        return input;
    }

    fprintf(stderr, "Error: Could not allocate memory for input\n");
    exit(EXIT_FAILURE);
}