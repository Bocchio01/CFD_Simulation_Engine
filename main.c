#include <stdio.h>

#include <cjson/cJSON.h>
#include <getopt.h>

#include "CFD.h"

int main(int argc, char *argv[])
{
    CFD_t *cfd = CFD_Init();
    CFD_Config(cfd, argc, argv);

    // CFD_Input(cfd, argc, argv);
    // CFD_Solve(cfd);
    // CFD_Output(cfd);

    // CFD_Solver_Solve(cfd);
    // CFD_Results_Save(cfd);

    return 0;
}
