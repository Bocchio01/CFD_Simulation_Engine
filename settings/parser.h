#ifndef PARSER_H
#define PARSER_H

#include <stdlib.h>

#include "settings.h"

void CFD_Settings_Parse(settings_t *settings, int argc, char *argv[]);

void CFD_Settings_Help();

#endif