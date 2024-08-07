#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "libs/cLOG/cLOG.h"
#include "libs/cFILE/cFILE.h"

#include "CFD.h"
#include "in/in.h"
#include "out/out.h"

CFD_t *CFD_Allocate()
{
    CFD_t *cfd = (CFD_t *)malloc(sizeof(CFD_t));

    cfd->in = CFD_Allocate_In();
    cfd->engine = CFD_Allocate_Engine();
    cfd->out = CFD_Allocate_Out();

    if (cfd->in != NULL &&
        cfd->engine != NULL &&
        cfd->out != NULL)
    {
        return cfd;
    }

    CFD_Free(cfd);

    log_fatal("Error: Could not allocate memory for cfd");
    exit(EXIT_FAILURE);
}

void CFD_Prepare(CFD_t *cfd, int argc, char **argv)
{
    CFD_CMD_Parse(cfd, argc, argv);
    if (FILE_String_Compare_Insensitive(cfd->in->file->name, "") == 0)
    {
        sprintf(cfd->in->file->path, "%s", DEFAULT_IN_FILE_PATH);
        sprintf(cfd->in->file->name, "%s", DEFAULT_IN_FILE_NAME);
        cfd->in->file->extension = FILE_String_to_Extension(DEFAULT_IN_FILE_FORMAT);
    }

    if (FILE_Read(cfd->in->file))
    {
        CFD_JSON_Parse(cfd);
    }
    else
    {
        log_fatal("Error: Could not read file");
        exit(EXIT_FAILURE);
    }
}

void CFD_Solve(CFD_t *cfd)
{
    time(NULL);

    CFD_Setup_Engine(cfd);
    CFD_Generate_Mesh(cfd);

    clock_t tic = clock();
    CFD_Run_Method(cfd, cfd->engine->method->args);
    clock_t toc = clock();

    cfd->engine->method->CPU_time = (double)(toc - tic) / CLOCKS_PER_SEC;
}

void CFD_Finalize(CFD_t *cfd)
{
    CFD_Collocate_Fields(cfd);
    CFD_Save_Results(cfd);
}

void CFD_Free(CFD_t *cfd)
{
    if (cfd != NULL)
    {
        CFD_Free_In(cfd->in);
        CFD_Free_Engine(cfd->engine);
        CFD_Free_Out(cfd->out);
        free(cfd);
    }
}
