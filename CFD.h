#ifndef CFD_H
#define CFD_H

#include "settings/settings.h"
// #include "solver/solver.h"

typedef struct
{
    settings_t *settings;
    // solver_t *solver;
} CFD_t;

/**
 * @brief Function to initialize CFD
 *
 * @param argc
 * @param argv
 *
 * @return CFD_t
 */
CFD_t *CFD_Init(int argc, char *argv[]);

#endif
