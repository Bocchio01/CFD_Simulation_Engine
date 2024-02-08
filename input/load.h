#ifndef LOAD_H
#define LOAD_H

typedef struct CFD_t CFD_t;

#include "../utils/cJSON/cJSON.h"

void CFD_Input_Load(CFD_t *cfd);

void CFD_Input_LoadInput(CFD_t *cfd, cJSON *input);
void CFD_Input_LoadInputGeometry(CFD_t *cfd, cJSON *geometry);
void CFD_Input_LoadInputFluid(CFD_t *cfd, cJSON *fluid);
// void CFD_LoadInputChecher(CFD_t *cfd);

void CFD_Input_LoadSolver(CFD_t *cfd, cJSON *solver);
void CFD_Input_LoadSolverMesh(CFD_t *cfd, cJSON *mesh);
void CFD_Input_LoadSolverMethod(CFD_t *cfd, cJSON *method);
void CFD_Input_LoadSolverSchemes(CFD_t *cfd, cJSON *schemes);

void CFD_Input_LoadOutput(CFD_t *cfd, cJSON *output);

#endif