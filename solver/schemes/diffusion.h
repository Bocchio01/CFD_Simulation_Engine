/**
 * @file diffusion.h
 * @brief Header file for diffusion methods
 *
 * This file contains the definitions of the functions used to perform diffusion schemes.
 *
 * @author Tommaso Bocchietti
 * @date 2021-03-16
 */

#ifndef DIFFUSION_H
#define DIFFUSION_H

typedef struct state_t state_t;
typedef struct element_size_t element_size_t;
// typedef struct Ap_coefficients_t Ap_coefficients_t;

#include "schemes.h"

typedef Ap_coefficients_t (*diffusion_function_t)(state_t *state, element_size_t *element_size);

typedef enum
{
    SECOND_ORDER,
    FOURTH_ORDER,
} diffusion_enum_t;

typedef struct
{
    char *name;
    diffusion_enum_t type;
    diffusion_function_t callable;
} scheme_diffusion_t;

/**
 * @brief Function to return coefficients for the second order diffusion scheme
 *
 * @param state
 * @param cell_size
 * @return Ap_coefficients_t
 */
Ap_coefficients_t solverSchemeDiffusion2(state_t *state, element_size_t *element_size);

/** @brief Function to return coefficients for the fourth order diffusion scheme
 *
 * @param state
 * @param cell_size
 * @return Ap_coefficients_t
 */
Ap_coefficients_t solverSchemeDiffusion4(state_t *state, element_size_t *element_size);

#endif