#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <assert.h>

#include "cMAT3D.h"
#include "libs/cLOG/cLOG.h"

cMAT3D_t *MAT3D_Init(uint16_t rows, uint16_t cols, uint16_t depth)
{
    cMAT3D_t *mat = (cMAT3D_t *)malloc(sizeof(cMAT3D_t));
    if (mat == NULL)
    {
        log_fatal("Failed to allocate memory for cMAT3D_t");
        exit(EXIT_FAILURE);
    }

    mat->rows = rows;
    mat->cols = cols;
    mat->depth = depth;

    mat->data = (double ***)malloc(rows * sizeof(double **));
    if (mat->data == NULL)
    {
        log_fatal("Failed to allocate memory for cMAT3D_t data");
        exit(EXIT_FAILURE);
    }

    for (uint16_t i = 0; i < rows; i++)
    {
        mat->data[i] = (double **)malloc(cols * sizeof(double *));
        if (mat->data[i] == NULL)
        {
            log_fatal("Failed to allocate memory for cMAT3D_t data");
            exit(EXIT_FAILURE);
        }

        for (uint16_t j = 0; j < cols; j++)
        {
            mat->data[i][j] = (double *)malloc(depth * sizeof(double));
            if (mat->data[i][j] == NULL)
            {
                log_fatal("Failed to allocate memory for cMAT3D_t data");
                exit(EXIT_FAILURE);
            }
        }
    }

    for (uint16_t i = 0; i < rows; i++)
    {
        for (uint16_t j = 0; j < cols; j++)
        {
            for (uint16_t k = 0; k < depth; k++)
            {
                mat->data[i][j][k] = 0.0;
            }
        }
    }

    return mat;
}

cMAT3D_t *MAT3D_Transpose(cMAT3D_t *A)
{
    cMAT3D_t *result = MAT3D_Init(A->cols, A->rows, A->depth);

    for (uint16_t i = 0; i < A->rows; i++)
    {
        for (uint16_t j = 0; j < A->cols; j++)
        {
            for (uint16_t k = 0; k < A->depth; k++)
            {
                result->data[j][i][k] = A->data[i][j][k];
            }
        }
    }

    return result;
}

cMAT3D_t *MAT3D_MultiplyScalar(double scalar, cMAT3D_t *A)
{
    cMAT3D_t *result = MAT3D_Init(A->rows, A->cols, A->depth);

    for (uint16_t i = 0; i < A->rows; i++)
    {
        for (uint16_t j = 0; j < A->cols; j++)
        {
            for (uint16_t k = 0; k < A->depth; k++)
            {
                result->data[i][j][k] = scalar * A->data[i][j][k];
            }
        }
    }

    return result;
}

cMAT3D_t *MAT3D_Sum(cMAT3D_t *A, cMAT3D_t *B)
{
    assert(A->rows == B->rows && A->cols == B->cols && A->depth == B->depth);

    cMAT3D_t *result = MAT3D_Init(A->rows, A->cols, A->depth);

    for (uint16_t i = 0; i < A->rows; i++)
    {
        for (uint16_t j = 0; j < A->cols; j++)
        {
            for (uint16_t k = 0; k < A->depth; k++)
            {
                result->data[i][j][k] = A->data[i][j][k] + B->data[i][j][k];
            }
        }
    }

    return result;
}

cMAT3D_t *MAT3D_Multiply(cMAT3D_t *A, cMAT3D_t *B)
{
    assert(A->cols == B->rows);

    cMAT3D_t *result = MAT3D_Init(A->rows, B->cols, A->depth);

    for (uint16_t i = 0; i < A->rows; i++)
    {
        for (uint16_t j = 0; j < B->cols; j++)
        {
            for (uint16_t k = 0; k < A->depth; k++)
            {
                result->data[i][j][k] = 0.0;
                for (uint16_t l = 0; l < A->cols; l++)
                {
                    result->data[i][j][k] += A->data[i][l][k] * B->data[l][j][k];
                }
            }
        }
    }

    return result;
}

void MAT3D_Free(cMAT3D_t *A)
{
    for (uint16_t i = 0; i < A->rows; i++)
    {
        for (uint16_t j = 0; j < A->cols; j++)
        {
            free(A->data[i][j]);
        }
        free(A->data[i]);
    }
    free(A->data);
}

void MAT3D_Copy(cMAT3D_t *A, cMAT3D_t *B)
{
    assert(A->rows == B->rows && A->cols == B->cols && A->depth == B->depth);

    for (uint16_t i = 0; i < A->rows; i++)
    {
        for (uint16_t j = 0; j < A->cols; j++)
        {
            for (uint16_t k = 0; k < A->depth; k++)
            {
                B->data[i][j][k] = A->data[i][j][k];
            }
        }
    }
}

void MAT3D_Print(cMAT3D_t *A)
{
    printf("cMAT3D_t %dx%dx%d:\n", A->rows, A->cols, A->depth);
    printf("[\n");

    for (uint16_t i = 0; i < A->rows; i++)
    {
        for (uint16_t j = 0; j < A->cols; j++)
        {
            printf("\t");
            for (uint16_t k = 0; k < A->depth; k++)
            {
                printf("%+.3f ", A->data[i][j][k]);
            }
            printf("\n");
        }
    }

    printf("]\n");
}