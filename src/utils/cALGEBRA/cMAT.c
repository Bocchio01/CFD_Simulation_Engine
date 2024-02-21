/**
 * @file cMAT.c
 * @brief cMAT_t operations module
 * @details This module implements the basic matrix operations.
 * @date 2024-02-13
 */

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <assert.h>

#include "cMAT.h"
#include "../cLOG/cLOG.h"

cMAT_t *MAT_Init(uint8_t rows, uint8_t cols)
{
    cMAT_t *mat = (cMAT_t *)malloc(sizeof(cMAT_t));
    if (mat == NULL)
    {
        log_fatal("Failed to allocate memory for cMAT_t");
        exit(EXIT_FAILURE);
    }

    mat->rows = rows;
    mat->cols = cols;
    mat->data = (double **)malloc(rows * sizeof(double *));
    if (mat->data == NULL)
    {
        log_fatal("Failed to allocate memory for cMAT_t data");
        exit(EXIT_FAILURE);
    }

    for (uint8_t i = 0; i < rows; i++)
    {
        mat->data[i] = (double *)malloc(cols * sizeof(double));
        if (mat->data[i] == NULL)
        {
            log_fatal("Failed to allocate memory for cMAT_t data");
            exit(EXIT_FAILURE);
        }
    }

    for (uint8_t i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            mat->data[i][j] = 0.0;
        }
    }

    return mat;
}

cMAT_t *MAT_Transpose(cMAT_t *A)
{
    cMAT_t *result = MAT_Init(A->cols, A->rows);

    for (uint8_t i = 0; i < A->rows; i++)
    {
        for (int j = 0; j < A->cols; j++)
        {
            result->data[j][i] = A->data[i][j];
        }
    }

    return result;
}

cMAT_t *MAT_MultiplyScalar(double scalar, cMAT_t *A)
{
    cMAT_t *result = MAT_Init(A->rows, A->cols);

    for (uint8_t i = 0; i < A->rows; i++)
    {
        for (int j = 0; j < A->cols; j++)
        {
            result->data[i][j] = scalar * A->data[i][j];
        }
    }

    return result;
}

cMAT_t *MAT_Sum(cMAT_t *A, cMAT_t *B)
{
    assert(A->rows == B->rows && A->cols == B->cols);

    cMAT_t *result = MAT_Init(A->rows, A->cols);

    for (uint8_t i = 0; i < A->rows; i++)
    {
        for (int j = 0; j < A->cols; j++)
        {
            result->data[i][j] = A->data[i][j] + B->data[i][j];
        }
    }

    return result;
}

cMAT_t *MAT_Multiply(cMAT_t *A, cMAT_t *B)
{
    assert(A->cols == B->rows);

    cMAT_t *result = MAT_Init(A->rows, B->cols);

    for (uint8_t i = 0; i < A->rows; i++)
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

void MAT_Free(cMAT_t *A)
{
    for (uint8_t i = 0; i < A->rows; i++)
    {
        free(A->data[i]);
    }
    free(A->data);
}

void MAT_Copy(cMAT_t *A, cMAT_t *B)
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

void MAT_Print(cMAT_t *A)
{
    printf("cMAT_t %dx%d:\n", A->rows, A->cols);
    printf("[\n");

    for (int i = 0; i < A->rows; i++)
    {
        printf("\t");
        for (int j = 0; j < A->cols; j++)
        {
            printf("%.1f ", A->data[i][j]);
        }
        printf("\n");
    }

    printf("]\n");
}

void MAT_Print_States(cMAT_t *state)
{
    printf("cMAT_t %dx%d:\n", state->rows, state->cols);
    printf("[\n");

    for (int j = state->rows - 1; j >= 0; j--)
    {
        printf("\t");
        for (int i = 0; i < state->cols; i++)
        {
            printf("%.1f ", state->data[j][i]);
        }
        printf("\n");
    }

    printf("]\n");
}