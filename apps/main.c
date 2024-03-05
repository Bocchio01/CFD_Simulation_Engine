#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "libs/cLOG/cLOG.h"

#include "core/CFD.h"

int main(int argc, char *argv[])
{
    log_set_level(LOG_INFO);

    log_info("#############################################");
    log_info("Simulation starting");
    log_info("#############################################");

    CFD_t *cfd = CFD_Allocate();

    CFD_Prepare(cfd, argc, argv);

    CFD_Solve(cfd);

    CFD_Finalize(cfd);

    CFD_Free(cfd);

    log_info("#############################################");
    log_info("Simulation ended");
    log_info("#############################################");
    log_info("\n\n");

    return EXIT_SUCCESS;
}
