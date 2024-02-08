#ifndef SETTINGS_H
#define SETTINGS_H

#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>

#include "parser.h"
#include "loader.h"

typedef enum
{
    EXTERNAL_FLOW,
    INTERNAL_FLOW
} problem_t;

typedef struct
{
    float x;
    float y;
} geometry_t;

typedef struct
{
    float mu;
    float Re;
} fluid_t;

typedef struct
{
    char *name;
    char *buffer;
    FILE *pointer;
} input_file_t;

typedef struct
{
    float uLid;
    // problem_t problem;
    geometry_t *geometry;
    fluid_t *fluid;
    input_file_t *file;
} input_t;

input_t *CFD_InitInput();

#endif