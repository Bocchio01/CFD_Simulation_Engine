#ifndef PARSE_H
#define PARSE_H

typedef struct CFD_t CFD_t;

#include <stdlib.h>

void CFD_CMD_Parse(CFD_t *cfd, int argc, char *argv[]);

void CFD_CMD_Print_Help();

void CFD_CMD_Print_Version();

void CFD_CMD_Parse_i(CFD_t *cfd, char *optarg);

void CFD_CMD_Parse_o(CFD_t *cfd, char *optarg);

void CFD_CMD_Parse_Invalid(char *optarg);

#endif