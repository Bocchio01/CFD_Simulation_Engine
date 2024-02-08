#ifndef PARSER_H
#define PARSER_H

typedef struct CFD_t CFD_t;

#include <stdlib.h>

void CFD_ParseCMD(CFD_t *cfd, int argc, char *argv[]);

void CFD_PrintHelp();

void CFD_PrintVersion();

void CFD_PrintInvalidArgument(char *optarg);

#endif