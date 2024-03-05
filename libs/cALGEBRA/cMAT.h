#ifndef MATRIX_H
#define MATRIX_H

#include <stdint.h>

typedef struct
{
    uint16_t rows;
    uint16_t cols;
    double **data;
} cMAT_t;

/**
 * Initialize a matrix with the given number of rows and columns.
 *
 * @param rows The number of rows in the matrix.
 * @param cols The number of columns in the matrix.
 * @return A cMAT_t struct with the specified number of rows and columns and all elements initialized to 0.
 */
cMAT_t *MAT_Init(uint16_t rows, uint16_t cols);

/**
 * Transposes a given matrix.
 *
 * @param A The matrix to be transposed.
 * @return The transposed matrix.
 */
cMAT_t *MAT_Transpose(cMAT_t *A);

/**
 * Multiplies a matrix by a scalar value.
 *
 * @param scalar The scalar value to multiply the matrix by.
 * @param A The matrix to be multiplied.
 * @return The resulting matrix after scalar multiplication.
 */
cMAT_t *MAT_MultiplyScalar(double scalar, cMAT_t *A);

/**
 * Calculates the sum of two matrices.
 *
 * @param A The first matrix to be added.
 * @param B The second matrix to be added.
 * @return The resulting matrix of the addition operation.
 */
cMAT_t *MAT_Sum(cMAT_t *A, cMAT_t *B);

/**
 * Multiplies two matrices A and B and returns the resulting matrix.
 *
 * @param A The first matrix to be multiplied.
 * @param B The second matrix to be multiplied.
 * @return The resulting matrix of the multiplication.
 */
cMAT_t *MAT_Multiply(cMAT_t *A, cMAT_t *B);

/**
 * Frees the memory allocated for the given matrix.
 *
 * @param A The matrix to be freed.
 */
void MAT_Free(cMAT_t *A);

/**
 * Copies the matrix A to the matrix B.
 *
 * @param A The matrix to be copied.
 * @param B The matrix to be copied to.
 */
void MAT_Copy(cMAT_t *A, cMAT_t *B);

/**
 * Prints the given matrix A.
 *
 * @param A The matrix to be printed.
 */
void MAT_Print(cMAT_t *A);
void MAT_Print_States(cMAT_t *state);

#endif