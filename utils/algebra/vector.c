#include <stdlib.h>

#include "vector.h"

vector_t *vectorInit(uint8_t length)
{
    vector_t *vector = (vector_t *)malloc(sizeof(vector_t));
    if (vector == NULL)
    {
        return NULL;
    }

    vector->length = length;
    vector->data = (double *)malloc(length * sizeof(double));

    if (vector->data == NULL)
    {
        free(vector);
        return NULL;
    }

    for (uint8_t i = 0; i < length; i++)
    {
        vector->data[i] = 0.0;
    }

    return vector;
}