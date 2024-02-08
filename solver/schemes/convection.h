#ifndef CONVECTION_H
#define CONVECTION_H

typedef struct state_t state_t;
typedef struct element_size_t element_size_t;
// typedef struct Ap_coefficients_t Ap_coefficients_t;

#include "schemes.h"

typedef Ap_coefficients_t (*convection_function_t)(state_t *state, element_size_t *element_size);

typedef enum
{
    UDS,
    HYBRID,
    QUICK,
} convection_enum_t;

typedef struct
{
    char *name;
    convection_enum_t type;
    convection_function_t callable;
} scheme_convection_t;

/**
 * @brief Function to return 'Ap' coefficients for UDS convection scheme
 *
 * @param state
 * @param cell_size
 *
 * @return Ap_coefficients_t
 */
Ap_coefficients_t solverSchemeConvectionUDS(state_t *state, element_size_t *element_size);

/**
 * @brief Function to return 'Ap' coefficients for HYBRID convection scheme
 *
 * @param state
 * @param cell_size
 *
 * @return Ap_coefficients_t
 */
Ap_coefficients_t solverSchemeConvectionHYBRID(state_t *state, element_size_t *element_size);

/**
 * @brief Function to return 'Ap' coefficients for QUICK convection scheme
 *
 * @param state
 * @param cell_size
 *
 * @return Ap_coefficients_t
 */
Ap_coefficients_t solverSchemeConvectionQUICK(state_t *state, element_size_t *element_size);

#endif