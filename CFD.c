#include <stdio.h>
#include <stdlib.h>

#include "CFD.h"
#include "input/init.h"
// #include "solver/solver.h"
#include "output/output.h"

CFD_t *CFD_Init()
{
    CFD_t *cfd = (CFD_t *)malloc(sizeof(CFD_t));

    cfd->input = CFD_Input_Init();
    cfd->solver = CFD_Solver_Init();
    cfd->output = CFD_Output_Init();

    if (cfd->input != NULL &&
        cfd->solver != NULL &&
        cfd->output != NULL)
    {
        return cfd;
    }

    CFD_Free(cfd);

    fprintf(stderr, "Error: Could not allocate memory for cfd\n");
    exit(EXIT_FAILURE);
}

void CFD_Free(CFD_t *cfd)
{
    free(cfd->input);
    free(cfd->solver);
    free(cfd->output);
    free(cfd);
}
