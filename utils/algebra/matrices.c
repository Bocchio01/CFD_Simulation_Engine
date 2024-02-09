/**
 * @file matrices.c
 * @brief matrix_t operations module
 * @details This module implements the basic matrix operations.
 * @date 2023-09-29
 */

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "matrices.h"

matrix_t matAllocate(int rows, int cols)
{
    matrix_t mat;
    mat.rows = rows;
    mat.cols = cols;
    mat.data = (double **)malloc(rows * sizeof(double *));
    if (mat.data == NULL)
        exit(EXIT_FAILURE);

    for (int i = 0; i < rows; i++)
    {
        mat.data[i] = (double *)malloc(cols * sizeof(double));
        if (mat.data[i] == NULL)
            exit(EXIT_FAILURE);
    }

    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            mat.data[i][j] = 0;
        }
    }

    return mat;
}

matrix_t matTranspose(matrix_t A)
{
    matrix_t result = matAllocate(A.cols, A.rows);

    for (int i = 0; i < A.rows; i++)
    {
        for (int j = 0; j < A.cols; j++)
        {
            result.data[j][i] = A.data[i][j];
        }
    }

    return result;
}

matrix_t matScalarMultiply(double scalar, matrix_t A)
{
    matrix_t result = matAllocate(A.rows, A.cols);

    for (int i = 0; i < A.rows; i++)
    {
        for (int j = 0; j < A.cols; j++)
        {
            result.data[i][j] = scalar * A.data[i][j];
        }
    }

    return result;
}

matrix_t matSum(matrix_t A, matrix_t B)
{
    assert(A.rows == B.rows && A.cols == B.cols);

    matrix_t result = matAllocate(A.rows, A.cols);

    for (int i = 0; i < A.rows; i++)
    {
        for (int j = 0; j < A.cols; j++)
        {
            result.data[i][j] = A.data[i][j] + B.data[i][j];
        }
    }

    return result;
}

matrix_t matMultiply(matrix_t A, matrix_t B)
{
    assert(A.cols == B.rows);

    matrix_t result = matAllocate(A.rows, B.cols);

    for (int i = 0; i < A.rows; i++)
    {
        for (int j = 0; j < B.cols; j++)
        {
            result.data[i][j] = 0.0;
            for (int k = 0; k < A.cols; k++)
            {
                result.data[i][j] += A.data[i][k] * B.data[k][j];
            }
        }
    }

    return result;
}

matrix_t matInverse(matrix_t A)
{
    assert(A.rows == A.cols);
    assert(matComputeDeterminant(A) != 0);

    double temp;
    matrix_t Pivoting = matComputePivot(A);

    matrix_t I = matAllocate(A.rows, A.cols);
    for (int i = 0; i < A.rows; i++)
    {
        I.data[i][i] = 1;
    }

    I = matMultiply(Pivoting, I);
    A = matMultiply(Pivoting, A);
    matFree(Pivoting);

    for (int k = 0; k < A.rows; k++)
    {
        temp = A.data[k][k];

        for (int j = 0; j < A.cols; j++)
        {
            A.data[k][j] /= temp;
            I.data[k][j] /= temp;
        }

        for (int i = 0; i < A.rows; i++)
        {
            if (i == k)
                continue;
            temp = A.data[i][k];
            for (int j = 0; j < A.cols; j++)
            {
                A.data[i][j] -= A.data[k][j] * temp;
                I.data[i][j] -= I.data[k][j] * temp;
            }
        }
    }

    return I;
}

matrix_t matComputePivot(matrix_t A)
{

    assert(A.rows == A.cols);

    int maxRow;
    double maxVal;

    matrix_t P = matAllocate(A.rows, A.cols);
    for (int i = 0; i < A.rows; i++)
    {
        P.data[i][i] = 1;
    }

    for (int i = 0; i < A.rows; i++)
    {
        maxRow = i;
        maxVal = A.data[i][i];
        for (int j = i + 1; j < A.rows; j++)
        {
            if (A.data[j][i] > maxVal)
            {
                maxVal = A.data[j][i];
                maxRow = j;
            }
        }

        // Swap the current row with the row containing the maximum value
        if (maxRow != i)
        {
            double *temp = P.data[i];
            P.data[i] = P.data[maxRow];
            P.data[maxRow] = temp;
        }
    }

    return P;
}

double matComputeDeterminant(matrix_t A)
{
    assert(A.rows == A.cols);

    if (A.rows == 1)
        return A.data[0][0];

    if (A.rows == 2)
        return A.data[0][0] * A.data[1][1] - A.data[0][1] * A.data[1][0];

    double det = 0.0;
    for (int j = 0; j < A.rows; j++)
    {
        matrix_t minor = matComputeMinor(A, 0, j);
        double sign = (j % 2 == 0) ? 1.0 : -1.0;
        det += sign * A.data[0][j] * matComputeDeterminant(minor);
        matFree(minor);
    }

    return det;
}

matrix_t matComputeAdjugate(matrix_t A)
{
    assert(A.rows == A.cols);

    matrix_t adj = matAllocate(A.rows, A.cols);

    for (int i = 0; i < A.rows; i++)
    {
        for (int j = 0; j < A.cols; j++)
        {
            matrix_t minor = matComputeMinor(A, i, j);
            double sign = ((i + j) % 2 == 0) ? 1.0 : -1.0;
            adj.data[j][i] = sign * matComputeDeterminant(minor);
            matFree(minor);
        }
    }
    return adj;
}

matrix_t matComputeMinor(matrix_t A, int row, int col)
{
    matrix_t minor = matAllocate(A.rows - 1, A.cols - 1);

    int r = 0;
    for (int i = 0; i < A.rows; i++)
    {
        if (i == row)
            continue;
        int c = 0;
        for (int j = 0; j < A.cols; j++)
        {
            if (j == col)
                continue;
            minor.data[r][c] = A.data[i][j];
            c++;
        }
        r++;
    }
    return minor;
}

void matFree(matrix_t A)
{
    for (int i = 0; i < A.rows; i++)
    {
        free(A.data[i]);
    }
    free(A.data);
}

void matPrint(matrix_t A)
{
    printf("matrix_t %dx%d:\n", A.rows, A.cols);
    printf("[\n");
    for (int i = 0; i < A.rows; i++)
    {
        printf("\t");
        for (int j = 0; j < A.cols; j++)
        {
            printf("%.1f ", A.data[i][j]);
        }
        printf("\n");
    }
    printf("]\n");
}