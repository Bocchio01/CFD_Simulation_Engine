/**
 * @file cVEC.c
 * @brief cVEC_t operations module
 * @details This module implements the basic vector operations.
 * @date 2024-02-13
 */

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <assert.h>

#include "cVEC.h"
#include "../cLOG/cLOG.h"

cVEC_t *VEC_Init(uint16_t length)
{
    cVEC_t *V = (cVEC_t *)malloc(sizeof(cVEC_t));
    if (V == NULL)
    {
        log_fatal("Failed to allocate memory for cVEC_t");
        exit(EXIT_FAILURE);
    }

    V->length = length;
    V->data = (double *)malloc(length * sizeof(double));
    if (V->data == NULL)
    {
        free(V);
        log_fatal("Failed to allocate memory for cVEC_t data");
        exit(EXIT_FAILURE);
    }

    for (uint16_t i = 0; i < length; i++)
    {
        V->data[i] = 0.0;
    }

    return V;
}

cVEC_t *VEC_Sum(cVEC_t *V1, cVEC_t *V2)
{
    assert(V1->length == V2->length);

    cVEC_t *result = VEC_Init(V1->length);

    for (uint16_t i = 0; i < V1->length; i++)
    {
        result->data[i] = V1->data[i] + V2->data[i];
    }

    return result;
}

cVEC_t *VEC_Multiply(double scalar, cVEC_t *V)
{
    cVEC_t *result = VEC_Init(V->length);

    for (uint16_t i = 0; i < V->length; i++)
    {
        result->data[i] = scalar * V->data[i];
    }

    return result;
}

cMAT_t *VEC_ToMatrix(cVEC_t *V)
{
    cMAT_t *result = MAT_Init(V->length, 1);

    for (uint16_t i = 0; i < V->length; i++)
    {
        result->data[i][0] = V->data[i];
    }

    return result;
}

void VEC_Free(cVEC_t *V)
{
    free(V->data);
    free(V);
}

void VEC_Print(cVEC_t *V)
{
    printf("[\n");
    for (uint16_t i = 0; i < V->length; i++)
    {
        printf("\t%f", V->data[i]);
        if (i < V->length - 1)
        {
            printf("\n");
        }
    }
    printf("\n]\n");
}
