#ifndef MESH_H
#define MESH_H

#include <stdint.h>

#include "../lib/vector.h"
#include "../settings/settings.h"

typedef struct
{
    int x;
    int y;
} halo_size_t;

typedef struct
{
    double dx;
    double dy;
} element_size_t;

typedef struct
{
    vector_t X;
    vector_t Y;
} mesh_data_t;

typedef struct
{
    element_size_t element_size;
    mesh_data_t data;
} mesh_t;

mesh_t *meshInit(
    grid_dimension_t grid_dimension,
    domain_dimension_t domain_dimension,
    halo_size_t halo_size);

element_size_t elementSize(
    domain_dimension_t domain_dimension,
    grid_dimension_t grid_dimension);

mesh_data_t meshDataInit(
    element_size_t element_size,
    grid_dimension_t grid_dimension,
    domain_dimension_t domain_dimension,
    halo_size_t halo_size);
#endif