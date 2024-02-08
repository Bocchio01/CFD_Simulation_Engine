#include <stdio.h>

#include "utils/cJSON/cJSON.h"
#include <getopt.h>

#include "CFD.h"

int main(int argc, char *argv[])
{
    printf("Starting\n");

    CFD_t *cfd = CFD_Init();

    // Input
    CFD_Input_Parse(cfd, argc, argv);
    CFD_Input_Load(cfd);

    // Solver
    CFD_SolverMesh(cfd);
    // CFD_SolverSolve(cfd);

    // Output
    // CFD_SaveResults(cfd);

    printf("Finished\n");

    return 0;
}
