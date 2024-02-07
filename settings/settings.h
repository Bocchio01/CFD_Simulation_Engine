#ifndef SETTINGS_H
#define SETTINGS_H

typedef struct state_t state_t;

#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>

// Domain and fluid settings
typedef struct
{
    float x;
    float y;
} data_domain_dimension_t;

typedef struct
{
    float mu;
    float Re;
} data_fluid_properties_t;

// problem_data_t
typedef struct
{
    float uLid;
    data_domain_dimension_t domain_dimension;
    data_fluid_properties_t fluid_properties;
} problem_data_t;

// problem_data_t

// setting_mesh_t
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
} mesh_size_t;

typedef struct
{
    element_type_t type;
    element_size_t size;
} mesh_element_t;

typedef struct
{
    mesh_type_t type;
    mesh_size_t size;
    mesh_element_t element;
} setting_mesh_t;
// setting_mesh_t

// setting_schemes_t
typedef struct
{
    double u[2];
    double v[2];
} Ap_coefficients_t;

typedef enum
{
    UDS,
    HYBRID,
    QUICK,
} convection_enum_t;

typedef Ap_coefficients_t (*convection_function_t)(state_t *state, element_size_t *element_size);

typedef enum
{
    SECOND_ORDER,
    FOURTH_ORDER,
} diffusion_enum_t;

typedef Ap_coefficients_t (*diffusion_function_t)(state_t *state, element_size_t *element_size);

typedef struct
{
    char *name;
    convection_enum_t type;
    convection_function_t callable;
} scheme_convection_t;

typedef struct
{
    char *name;
    diffusion_enum_t type;
    diffusion_function_t callable;
} scheme_diffusion_t;

typedef struct
{
    scheme_convection_t convection;
    scheme_diffusion_t diffusion;
} setting_schemes_t;
// setting_schemes_t

typedef struct
{
    float u;
    float v;
} under_relaxation_factors_t;

typedef struct
{
    int max_iterations;
    float tolerance;
    setting_mesh_t mesh;
    setting_schemes_t schemes;
    under_relaxation_factors_t under_relaxation_factors;
} solver_settings_t;

typedef enum
{
    CSV,
    TXT
} results_format_t;

typedef struct
{
    char *file_name;
    FILE *file_pointer;
    results_format_t format;
} results_settings_t;

typedef struct
{
    // simulation_data_t simulation; -> For future use and unsteady flow simulations
    problem_data_t problem_data;
    solver_settings_t solver;
    results_settings_t results;
} settings_t;

/**
 * @brief Function to initialize settings
 *
 * @return settings_t
 */
settings_t *CFD_Settings_Init();

/**
 * @brief Function to set default settings
 *
 * @param settings
 */
void CFD_Settings_Reset(settings_t *settings);

#endif