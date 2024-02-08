#ifndef MESH_H
#define MESH_H

#include <stdint.h>

#include "../../utils/algebra/algebra.h"

typedef enum
{
    RECTANGULAR,
    TRIANGULAR
} element_type_t;

typedef struct
{
    float dx;
    float dy;
} element_size_t;

typedef enum
{
    STAGGERED,
    COLLOCATED
} mesh_type_t;

typedef struct
{
    uint8_t Nx;
    uint8_t Ny;
} mesh_nodes_t;

typedef struct
{
    element_type_t type;
    element_size_t size;
} mesh_element_t;

typedef struct
{
    vector_t x;
    vector_t y;
} mesh_data_t;

typedef struct
{
    int n_ghosts;
    mesh_type_t type;
    mesh_nodes_t nodes;
    mesh_element_t element;
    mesh_data_t data;
} mesh_t;

#endif