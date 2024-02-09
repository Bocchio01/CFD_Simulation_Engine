#ifndef INIT_H
#define INIT_H

#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>

#include "../utils/custom_file/custom_file.h"

#include "parsers/cmd.h"
#include "parsers/json.h"

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
    float uLid;
    // problem_t problem;
    geometry_t *geometry;
    fluid_t *fluid;
    custom_file_t *file;
} in_t;

in_t *CFD_Allocate_In();

geometry_t *CFD_Allocate_In_Geometry();

fluid_t *CFD_Allocate_In_Fluid();

void CFD_Free_In(in_t *in);

void CFD_Free_In_Geometry(geometry_t *geometry);

void CFD_Free_In_Fluid(fluid_t *fluid);

#endif