/**
 * @file cMAT2D.c
 * @brief cMAT2D_t operations module
 * @details This module implements the basic matrix operations.
 * @date 2024-02-13
 */

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <assert.h>

#include "cMAT2D.h"
#include "libs/cLOG/cLOG.h"

cMAT2D_t *MAT2D_Init(uint16_t rows, uint16_t cols)
{
    cMAT2D_t *mat = (cMAT2D_t *)malloc(sizeof(cMAT2D_t));
    if (mat == NULL)
    {
        log_fatal("Failed to allocate memory for cMAT2D_t");
        exit(EXIT_FAILURE);
    }

    mat->rows = rows;
    mat->cols = cols;
    mat->data = (double **)malloc(rows * sizeof(double *));
    if (mat->data == NULL)
    {
        log_fatal("Failed to allocate memory for cMAT2D_t data");
        exit(EXIT_FAILURE);
    }

    for (uint16_t i = 0; i < rows; i++)
    {
        mat->data[i] = (double *)malloc(cols * sizeof(double));
        if (mat->data[i] == NULL)
        {
            log_fatal("Failed to allocate memory for cMAT2D_t data");
            exit(EXIT_FAILURE);
        }
    }

    for (uint16_t i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            mat->data[i][j] = 0.0;
        }
    }

    return mat;
}

cMAT2D_t *MAT2D_Transpose(cMAT2D_t *A)
{
    cMAT2D_t *result = MAT2D_Init(A->cols, A->rows);

    for (uint16_t i = 0; i < A->rows; i++)
    {
        for (int j = 0; j < A->cols; j++)
        {
            result->data[j][i] = A->data[i][j];
        }
    }

    return result;
}

cMAT2D_t *MAT2D_MultiplyScalar(double scalar, cMAT2D_t *A)
{
    cMAT2D_t *result = MAT2D_Init(A->rows, A->cols);

    for (uint16_t i = 0; i < A->rows; i++)
    {
        for (int j = 0; j < A->cols; j++)
        {
            result->data[i][j] = scalar * A->data[i][j];
        }
    }

    return result;
}

cMAT2D_t *MAT2D_Sum(cMAT2D_t *A, cMAT2D_t *B)
{
    assert(A->rows == B->rows && A->cols == B->cols);

    cMAT2D_t *result = MAT2D_Init(A->rows, A->cols);

    for (uint16_t i = 0; i < A->rows; i++)
    {
        for (int j = 0; j < A->cols; j++)
        {
            result->data[i][j] = A->data[i][j] + B->data[i][j];
        }
    }

    return result;
}

cMAT2D_t *MAT2D_Multiply(cMAT2D_t *A, cMAT2D_t *B)
{
    assert(A->cols == B->rows);

    cMAT2D_t *result = MAT2D_Init(A->rows, B->cols);

    for (uint16_t i = 0; i < A->rows; i++)
    {
        for (int j = 0; j < B->cols; j++)
        {
            result->data[i][j] = 0.0;
            for (int k = 0; k < A->cols; k++)
            {
                result->data[i][j] += A->data[i][k] * B->data[k][j];
            }
        }
    }

    return result;
}

void MAT2D_Free(cMAT2D_t *A)
{
    for (uint16_t i = 0; i < A->rows; i++)
    {
        free(A->data[i]);
    }
    free(A->data);
}

void MAT2D_Copy(cMAT2D_t *A, cMAT2D_t *B)
{
    assert(A->rows == B->rows && A->cols == B->cols);

    for (int i = 0; i < A->rows; i++)
    {
        for (int j = 0; j < A->cols; j++)
        {
            B->data[i][j] = A->data[i][j];
        }
    }
}

void MAT2D_Print(cMAT2D_t *A)
{
    printf("cMAT2D_t %dx%d:\n", A->rows, A->cols);
    printf("[\n");

    for (int i = 0; i < A->rows; i++)
    {
        printf("\t");
        for (int j = 0; j < A->cols; j++)
        {
            printf("%+.3f ", A->data[i][j]);
        }
        printf("\n");
    }

    printf("]\n");
}

void MAT2D_Print_States(cMAT2D_t *state)
{
    printf("cMAT2D_t %dx%d:\n", state->rows, state->cols);
    printf("[\n");

    for (int j = state->rows - 1; j >= 0; j--)
    {
        printf("\t");
        for (int i = 0; i < state->cols; i++)
        {
            printf("%+.1f ", state->data[j][i]);
        }
        printf("\n");
    }

    printf("]\n");
}