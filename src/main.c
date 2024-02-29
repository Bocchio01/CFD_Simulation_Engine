#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "utils/cLOG/cLOG.h"

#include "main.h"

#include "CFD.h"

int main(int argc, char *argv[])
{
    log_set_level(LOG_INFO);

    char fileNames[][50] = {
        "01_5_5_100_UDS_08",
        "02_129_129_1000_UDS_08",
        "03_40_40_1000_QUICK_08",
        "04_40_40_1000_UDS_05",
    };

    for (uint8_t i = 2; i < sizeof(fileNames) / sizeof(fileNames[0]); i++)
    {
        CFD_t *cfd = CFD_Allocate();

        log_info("#############################################");
        log_info("Simulation starting (%d)", i + 1);
        log_info("#############################################");

        sprintf(cfd->in->file->path, "%s", DEFAULT_IN_FILE_PATH);
        sprintf(cfd->in->file->name, "%s", fileNames[i]);
        cfd->in->file->extension = FILE_String_to_Extension(DEFAULT_IN_FILE_FORMAT);

        CFD_Prepare(cfd, argc, argv);

        CFD_Solve(cfd);

        CFD_Finalize(cfd);

        log_info("#############################################");
        log_info("Simulation ended");
        log_info("#############################################\n\n");

        CFD_Free(cfd);
    }

    return 0;
}