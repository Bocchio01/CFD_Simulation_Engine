#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "utils/cLOG/cLOG.h"

#include "CFD.h"

// int bench(int argc, char *argv[])
// {
//     log_set_level(LOG_INFO);

//     char fileNames[][50] = {
//         "01_40_40_100_UDS_SECOND_08_08",
//         "02_40_40_400_UDS_SECOND_008_008",
//         "03_40_40_1000_UDS_SECOND_008_008",
//         "04_40_40_1000_CDS_SECOND_008_008",
//         "05_40_40_1000_QUICK_SECOND_008_008",
//         "06_80_80_1000_UDS_SECOND_008_008",
//         "07_80_80_1000_CDS_SECOND_008_008",
//         "08_80_80_1000_QUICK_SECOND_008_008",
//         "09_129_129_1000_QUICK_FOURTH_008_008",
//     };

//     for (uint16_t i = 0; i < sizeof(fileNames) / sizeof(fileNames[0]); i++)
//     {
//         CFD_t *cfd = CFD_Allocate();

//         log_info("#############################################");
//         log_info("Simulation starting (%d)", i + 1);
//         log_info("#############################################");

//         sprintf(cfd->in->file->path, "%s", DEFAULT_IN_FILE_PATH);
//         sprintf(cfd->in->file->name, "%s", fileNames[i]);
//         cfd->in->file->extension = FILE_String_to_Extension(DEFAULT_IN_FILE_FORMAT);

//         CFD_Prepare(cfd, argc, argv);

//         CFD_Solve(cfd);

//         CFD_Finalize(cfd);

//         log_info("#############################################");
//         log_info("Simulation ended");
//         log_info("#############################################");
//         log_info("\n\n");

//         CFD_Free(cfd);
//     }

//     return 0;
// }
