#ifndef LOAD_H
#define LOAD_H

typedef struct CFD_t CFD_t;

#include "../../utils/cJSON/cJSON.h"

void CFD_JSON_Parse(CFD_t *cfd);

void CFD_JSON_Parse_In(CFD_t *cfd, cJSON *in);

void CFD_JSON_Parse_In_Geometry(CFD_t *cfd, cJSON *geometry);

void CFD_JSON_Parse_In_Fluid(CFD_t *cfd, cJSON *fluid);

// void CFD_LoadInputChecher(CFD_t *cfd);

void CFD_JSON_Parse_Engine(CFD_t *cfd, cJSON *engine);

void CFD_JSON_Parse_Engine_Mesh(CFD_t *cfd, cJSON *mesh);

void CFD_JSON_Parse_Engine_Method(CFD_t *cfd, cJSON *method);

void CFD_JSON_Parse_Engine_Schemes(CFD_t *cfd, cJSON *schemes);

void CFD_JSON_Parse_Out(CFD_t *cfd, cJSON *out);

void CFD_JSON_Parse_Out_File(CFD_t *cfd, cJSON *file);

#endif