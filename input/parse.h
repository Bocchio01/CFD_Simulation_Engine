#ifndef PARSE_H
#define PARSE_H

typedef struct CFD_t CFD_t;

#include <stdlib.h>

void CFD_Input_Parse(CFD_t *cfd, int argc, char *argv[]);

void CFD_Input_ParseHelp();

void CFD_Input_ParseVersion();

void CFD_Input_ParseInput(CFD_t *cfd, char *optarg);

void CFD_Input_ParseFormat(CFD_t *cfd, char *optarg);

void CFD_Input_ParseInvalid(char *optarg);

#endif