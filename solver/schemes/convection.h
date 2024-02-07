#ifndef CONVECTION_H
#define CONVECTION_H

#include "../../settings/settings.h"

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