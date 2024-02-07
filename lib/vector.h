#ifndef VECTOR_H
#define VECTOR_H

#include <stdbool.h>
#include <stdint.h>

typedef struct
{
    int length;
    double *data;
} vector_t;

vector_t *vectorInit(uint8_t length);
// void vector_destroy(vector_t *vector);
// void vector_print(vector_t *vector);
// void vector_set(vector_t *vector, int index, double value);
// double vector_get(vector_t *vector, int index);
// void vector_add(vector_t *vector, vector_t *other);
// void vector_subtract(vector_t *vector, vector_t *other);
// void vector_multiply(vector_t *vector, double scalar);
// void vector_divide(vector_t *vector, double scalar);
// double vector_dot_product(vector_t *vector, vector_t *other);
// double vector_magnitude(vector_t *vector);
// void vector_normalize(vector_t *vector);
// void vector_copy(vector_t *vector, vector_t *other);
// bool vector_equals(vector_t *vector, vector_t *other);

#endif