#include "mesh.h"

// mesh_t *meshInit(
//     domain_dimension_t domain_dimension,
//     grid_dimension_t grid_dimension,
//     halo_size_t halo_size)
// {
//     mesh_t *mesh = (mesh_t *)malloc(sizeof(mesh_t));
//     if (mesh == NULL)
//     {
//         return NULL;
//     }

//     mesh->element_size = elementSize(domain_dimension, grid_dimension);
//     mesh->data = meshDataInit(mesh->element_size, grid_dimension, domain_dimension, halo_size);

//     return mesh;
// }

// element_size_t elementSize(
//     domain_dimension_t domain_dimension,
//     grid_dimension_t grid_dimension)
// {
//     element_size_t element_size;

//     element_size.dx = domain_dimension.Lx / grid_dimension.Nx;
//     element_size.dy = domain_dimension.Ly / grid_dimension.Ny;

//     return element_size;
// }

// mesh_data_t meshDataInit(
//     element_size_t element_size,
//     grid_dimension_t grid_dimension,
//     domain_dimension_t domain_dimension,
//     halo_size_t halo_size)
// {
//     mesh_data_t mesh_data;

//     mesh_data.X = *vectorInit(grid_dimension.Nx + 2 * halo_size.x);
//     mesh_data.Y = *vectorInit(grid_dimension.Ny + 2 * halo_size.y);

//     for (int i = -halo_size.x; i < grid_dimension.Nx + halo_size.x; i++)
//     {
//         mesh_data.X.data[i] = i * element_size.dx;
//     }

//     for (int i = -halo_size.y; i < grid_dimension.Ny + halo_size.y; i++)
//     {
//         mesh_data.Y.data[i] = i * element_size.dy;
//     }

//     return mesh_data;
// }