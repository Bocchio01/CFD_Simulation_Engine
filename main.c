#include <stdio.h>

#include "CFD.h"

int main(int argc, char *argv[])
{
    CFD_t *cfd = CFD_Init(argc, argv);

    // CFD_Solver_Solve(cfd);
    // CFD_Results_Save(cfd);

    return 0;
}