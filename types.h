#ifndef TYPES_H
#define TYPES_H

#include <stdio.h>
#include <stdbool.h>
#include <stdint.h>

typedef struct
{
    uint8_t Lx;
    uint8_t Ly;
} domain_dimension_t;

typedef struct
{
    float mu;
    // float rho;
    // bool is_incompressible;
} fluid_properties_t;

typedef struct
{
    float uLid;
    domain_dimension_t domain_dimension;
    fluid_properties_t fluid_properties;
} data_t;

// Mesh structures

typedef enum
{
    STAGGERED,
    COLLOCATED
} grid_type_t;

typedef struct
{
    uint8_t Nx;
    uint8_t Ny;
} grid_dimension_t;

typedef enum
{
    RECTANGULAR,
    TRIANGULAR
} cell_geometry_t;

typedef struct
{
    double dx;
    double dy;
} cell_size_t;

typedef struct
{
    grid_type_t type;
    grid_dimension_t dimension;
} grid_t;

typedef struct
{
    cell_geometry_t geometry;
    cell_size_t size;
} cell_t;

typedef struct
{
    grid_t grid;
    cell_t cell;
} mesh_properties_t;

// End of mesh structures

typedef enum
{
    UDS,
    HYBRID,
    QUICK,
} convection_scheme_t;

typedef Ap_coefficients_t (*convection_function_t)(state_t *state, cell_size_t *cell_size);

typedef enum
{
    SECOND_ORDER,
    FOURTH_ORDER,
} diffusion_scheme_t;

typedef Ap_coefficients_t (*diffusion_function_t)(state_t *state, cell_size_t *cell_size);

typedef struct
{
    double u[2];
    double v[2];
} Ap_coefficients_t;

typedef struct
{
    double U[100][100];
    double V[100][100];
    double P[100][100];
} state_t;

typedef struct
{
    uint8_t u;
    uint8_t v;
} under_relaxation_factors_t;

typedef struct
{
    int max_iterations;
    double convergence_tolerance;
    state_t state;
    mesh_properties_t mesh_properties;

    convection_scheme_t convection_scheme;
    diffusion_scheme_t diffusion_scheme;
    under_relaxation_factors_t under_relaxation_factors;
} solver_t;

typedef struct
{
    // bool plot;
    bool print_residual;
    bool print_solution;

    bool overwrite_file;
    char *output_file;
    FILE *output_file_pointer;
} output_t;

typedef struct
{
    data_t data;
    solver_t solver;
    output_t output;
} CFD_t;

#endif