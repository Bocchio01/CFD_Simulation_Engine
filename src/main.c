#include <stdio.h>

#include "utils/log/log.h"

#include "main.h"

#include "CFD.h"

int main(int argc, char *argv[])
{
    log_set_level(LOG_INFO);

    CFD_t *cfd = CFD_Allocate();

    CFD_Prepare(cfd, argc, argv);

    CFD_Solve(cfd);

    CFD_Finalize(cfd);

    // CFD_Free(cfd);

    return 0;
}
