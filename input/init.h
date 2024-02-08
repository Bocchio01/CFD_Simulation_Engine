#ifndef INIT_H
#define INIT_H

#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>

#include "parse.h"
#include "load.h"

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

input_t *CFD_Input_Init();

geometry_t *CFD_Input_InitGeometry();
fluid_t *CFD_Input_InitFluid();
input_file_t *CFD_Input_InitFile();

void CFD_Input_InitFree(input_t *input);

#endif