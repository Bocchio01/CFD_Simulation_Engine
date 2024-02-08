#include <stdio.h>
#include <stdlib.h>

#include "CFD.h"
#include "input/input.h"
// #include "solver/solver.h"
#include "output/output.h"

CFD_t *CFD_Init()
{
    CFD_t *cfd = (CFD_t *)malloc(sizeof(CFD_t));

    cfd->input = CFD_InitInput();
    cfd->solver = CFD_InitSolver();
    cfd->output = CFD_InitOutput();

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

void CFD_Config(CFD_t *cfd, int argc, char *argv[])
{
    CFD_ParseCMD(cfd, argc, argv);
    CFD_Load(cfd);
}
void CFD_Solve(CFD_t *cfd)
{
    // CFD_Start(cfd);
}

void CFD_Output(CFD_t *cfd)
{
    // CFD_SaveResults(cfd);
}