#include <stdio.h>
#include <stdlib.h>

#include "CFD.h"

CFD_t *CFD_Init(int argc, char *argv[])
{
    CFD_t *cfd = (CFD_t *)malloc(sizeof(CFD_t));

    cfd->settings = CFD_Settings_Init(argc, argv);
    // cfd->solver = CFD_Solver_Init(cfd->settings);

    printf("CFD_Init\n");
    printf("cfd->settings->problem_data.uLid: %f\n", cfd->settings->problem_data.uLid);

    return cfd;
}