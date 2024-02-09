#ifndef SCGS_BC_H
#define SCGS_BC_H

typedef struct SCGS_t SCGS_t;

void CFD_SCGS_BC_Corrective_Term(SCGS_t *scgs); // Applies the boundary conditions
void CFD_SCGS_BC(SCGS_t *scgs);                 // Applies the boundary conditions

#endif