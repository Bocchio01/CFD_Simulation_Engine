#ifndef CFD_H
#define CFD_H

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
