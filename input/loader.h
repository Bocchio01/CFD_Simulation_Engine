#ifndef LOADER_H
#define LOADER_H

typedef struct CFD_t CFD_t;

// #include <cjson/cJSON.h>

void CFD_Load(CFD_t *cfd);

// void CFD_LoadInput(CFD_t *cfd, cJSON *input);
// void CFD_LoadSolver(CFD_t *cfd, cJSON *solver);
// void CFD_LoadOutput(CFD_t *cfd, cJSON *output);

#endif