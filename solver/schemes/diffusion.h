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

#include "../../settings/settings.h"

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