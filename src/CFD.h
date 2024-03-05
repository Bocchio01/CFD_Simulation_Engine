#ifndef CFD_H
#define CFD_H

#define VERSION_MAJOR @CFD_Simulation_Engine_VERSION_MAJOR @
#define VERSION_MINOR @CFD_Simulation_Engine_VERSION_MINOR @

#define DEFAULT_IN_FILE_PATH "datasets" // Input file path
#define DEFAULT_IN_FILE_NAME "input"    // Input file name
#define DEFAULT_IN_FILE_FORMAT "JSON"   // Input file format

#define DEFAULT_IN_ULID 1.0       // Lid velocity
#define DEFAULT_IN_GEOMETRY_X 1.0 // Geometry X
#define DEFAULT_IN_GEOMETRY_Y 1.0 // Geometry Y
#define DEFAULT_IN_FLUID_NU 1.0   // Fluid viscosity
#define DEFAULT_IN_FLUID_RE 1.0   // Reynolds number

#define DEFAULT_ENGINE_MESH_TYPE "STAGGERED"            // Mesh type
#define DEFAULT_ENGINE_MESH_NODES_X 100                 // Mesh nodes X
#define DEFAULT_ENGINE_MESH_NODES_Y 100                 // Mesh nodes Y
#define DEFAULT_ENGINE_MESH_ELEMENTS_TYPE "RECTANGULAR" // Elements type

#define DEFAULT_ENGINE_METHOD_TYPE "SCGS"            // Method type
#define DEFAULT_ENGINE_METHOD_TOLERANCE 1e-4         // Method tolerance
#define DEFAULT_ENGINE_METHOD_MAX_ITER 1000          // Method max iterations
#define DEFAULT_ENGINE_METHOD_UNDER_RELAXATION_U 0.5 // Method under relaxation u
#define DEFAULT_ENGINE_METHOD_UNDER_RELAXATION_V 0.5 // Method under relaxation v
#define DEFAULT_ENGINE_METHOD_UNDER_RELAXATION_P 0.3 // Method under relaxation p

#define DEFAULT_ENGINE_SCHEMES_CONVECTION "UDS"   // Schemes convection
#define DEFAULT_ENGINE_SCHEMES_DIFFUSION "SECOND" // Schemes diffusion

#define DEFAULT_OUT_FILE_PATH "results" // Output file path
#define DEFAULT_OUT_FILE_NAME "output"  // Output file name
#define DEFAULT_OUT_FILE_FORMAT "DAT"   // Output file format

#include "in/in.h"
#include "engine/engine.h"
#include "out/out.h"

typedef struct CFD_t
{
    in_t *in;
    engine_t *engine;
    out_t *out;
} CFD_t;

CFD_t *CFD_Allocate();

void CFD_Prepare(CFD_t *cfd, int argc, char **argv);

void CFD_Solve(CFD_t *cfd);

void CFD_Finalize(CFD_t *cfd);

void CFD_Free(CFD_t *cfd);

#endif
