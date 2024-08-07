#ifndef MESH_H
#define MESH_H

typedef struct CFD_t CFD_t;

#include <stdint.h>

#include "libs/cALGEBRA/cMAT2D.h"

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
    uint16_t Nx;
    uint16_t Ny;
} mesh_nodes_t;

typedef struct
{
    element_type_t type;
    element_size_t *size;
} mesh_element_t;

typedef struct
{
    cMAT2D_t *x;
    cMAT2D_t *y;
} mesh_data_t;

typedef struct
{
    uint16_t n_ghosts;
    mesh_type_t type;
    mesh_nodes_t *nodes;
    mesh_element_t *element;
    mesh_data_t *data;
} mesh_t;

void CFD_Setup_Mesh(CFD_t *cfd);

void CFD_Generate_Mesh(CFD_t *cfd);

#endif