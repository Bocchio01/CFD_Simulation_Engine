#ifndef MATRICES_H
#define MATRICES_H

typedef struct
{
    int rows;
    int cols;
    double **data;
} matrix_t;

/**
 * Initializes a matrix with the given number of rows and columns.
 *
 * @param rows The number of rows in the matrix.
 * @param cols The number of columns in the matrix.
 * @return A matrix_t struct with the specified number of rows and columns and all elements initialized to 0.
 */
matrix_t matInit(int rows, int cols);

/**
 * Transposes a given matrix.
 *
 * @param A The matrix to be transposed.
 * @return The transposed matrix.
 */
matrix_t matTranspose(matrix_t A);

/**
 * Multiplies a matrix by a scalar value.
 *
 * @param scalar The scalar value to multiply the matrix by.
 * @param A The matrix to be multiplied.
 * @return The resulting matrix after scalar multiplication.
 */
matrix_t matScalarMultiply(double scalar, matrix_t A);

/**
 * Calculates the sum of two matrices.
 *
 * @param A The first matrix to be added.
 * @param B The second matrix to be added.
 * @return The resulting matrix of the addition operation.
 */
matrix_t matSum(matrix_t A, matrix_t B);

/**
 * Multiplies two matrices A and B and returns the resulting matrix.
 *
 * @param A The first matrix to be multiplied.
 * @param B The second matrix to be multiplied.
 * @return The resulting matrix of the multiplication.
 */
matrix_t matMultiply(matrix_t A, matrix_t B);

/**
 * Calculates the inverse of a given matrix using Gauss-Jordan elimination method.
 *
 * @param A The matrix to calculate the inverse of.
 * @return The inverse of the given matrix.
 */
matrix_t matInverse(matrix_t A);

/**
 * Calculates the pivot matrix of a given matrix using Gauss-Jordan elimination method.
 *
 * @param A The matrix to calculate the pivot matrix of.
 * @return The pivot matrix of the given matrix.
 */
matrix_t matComputePivot(matrix_t A);

/**
 * Calculates the determinant of a given matrix using Gauss-Jordan elimination method.
 *
 * @param A The matrix to calculate the determinant of.
 * @return The determinant of the given matrix.
 */
double matComputeDeterminant(matrix_t A);

/**
 * Calculates the adjugate of a given matrix using Gauss-Jordan elimination method.
 *
 * @param A The matrix to calculate the adjugate of.
 * @return The adjugate of the given matrix.
 */
matrix_t matComputeAdjugate(matrix_t A);

/**
 * Calculates the minor of a given matrix using Gauss-Jordan elimination method.
 *
 * @param A The matrix to calculate the minor of.
 * @param row The row around which the minor is calculated.
 * @param col The column around which the minor is calculated.
 * @return The minor of the given matrix.
 */
matrix_t matComputeMinor(matrix_t A, int row, int col);

/**
 * Frees the memory allocated for the given matrix.
 *
 * @param A The matrix to be freed.
 */
void matFree(matrix_t A);

/**
 * Prints the given matrix A.
 *
 * @param A The matrix to be printed.
 */
void matPrint(matrix_t A);

#endif