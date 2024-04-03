#include <stdio.h>
#include <string.h>
#include <getopt.h>

#include "cmd.h"

#include "libs/cLOG/cLOG.h"

#include "../../CFD.h"

void CFD_CMD_Parse(CFD_t *cfd, int argc, char *argv[])
{
    int c;
    int option_index = 0;
    static struct option long_options[] = {
        {"help", no_argument, NULL, 'h'},
        {"version", no_argument, NULL, 'v'},
        {"input", required_argument, NULL, 'i'},
        {"output", required_argument, NULL, 'o'},
        {0, 0, 0, 0}};

    while ((c = getopt_long(argc, argv, "hvi:o:", long_options, &option_index)) != -1)
    {
        switch (c)
        {

        case 'h':
            CFD_CMD_Print_Help();
            exit(EXIT_SUCCESS);
            break;

        case 'v':
            CFD_CMD_Print_Version();
            exit(EXIT_SUCCESS);
            break;

        case 'i':
            CFD_CMD_Parse_i(cfd, optarg);
            break;

        case 'o':
            CFD_CMD_Parse_o(cfd, optarg);
            break;
        default:
            CFD_CMD_Parse_Invalid(optarg);
            exit(EXIT_FAILURE);
        }
    }
}

void CFD_CMD_Print_Help()
{
    printf("CFD Engine\n");
    printf("Author:\tTommaso Bocchietti\n");
    printf("Date:\t2024\n");
    printf("Version:\t0.1\n");
    printf("Description:\n");
    printf("\tThis program is a engine for the Navier-Stokes equations for compressible flow.\n");
    printf("\tDeveloped as a project for the course \"ME663 - Computational Fluid Dynamics\"\n");
    printf("\ttaught by Prof. Fue-Sang Lien at Univerity of Waterloo (CA), A.Y. 2023/2024\n");
    printf("\n");
    printf("Usage: ./main [OPTIONS]\n");
    printf("Options:\n");
    printf("\t-h, --help\tPrint this help message\n");
    printf("\t-v, --version\tPrint the version of the program\n");
    printf("\t-i, --input\tInput file path (relative or absolute). Default: -i simulations/input/input.json\n");
    printf("\t-o, --output\tOutput file path (relative or absolute). Default: -i simulations/input/output.json\n");
    printf("\n");
}

void CFD_CMD_Print_Version()
{
    printf("CFD Engine v0.1\n");
}

void CFD_CMD_Parse_i(CFD_t *cfd, char *arg)
{
    char full_path[100] = {0};
    cFILE_t *partial_file;

    if (sscanf(arg, "%s", full_path) != 1)
    {
        log_fatal("Invalid argument for input file name");
        exit(EXIT_FAILURE);
    }

    partial_file = FILE_Parse_Path(full_path);

    if (partial_file->extension == false)
    {
        log_fatal("Invalid file extension");
        exit(EXIT_FAILURE);
    }
    else if (partial_file->name != NULL &&
             partial_file->path != NULL &&
             partial_file->extension != false)
    {
        cfd->in->file->name = partial_file->name;
        cfd->in->file->path = partial_file->path;
        cfd->in->file->extension = partial_file->extension;
    }
}

void CFD_CMD_Parse_o(CFD_t *cfd, char *arg)
{
    char full_path[100] = {0};
    cFILE_t *partial_file;

    if (sscanf(arg, "%s", full_path) != 1)
    {
        log_fatal("Invalid argument for output file name");
        exit(EXIT_FAILURE);
    }

    partial_file = FILE_Parse_Path(full_path);

    if (partial_file->extension == false)
    {
        log_fatal("Invalid file extension");
        exit(EXIT_FAILURE);
    }
    else if (partial_file->name != NULL &&
             partial_file->path != NULL &&
             partial_file->extension != false)
    {
        cfd->in->file->name = partial_file->name;
        cfd->in->file->path = partial_file->path;
        cfd->in->file->extension = partial_file->extension;
    }
}

void CFD_CMD_Parse_Invalid(char *arg)
{
    printf("Invalid argument: \"%s\"\n", arg);
    printf("Use -h or --help for more information\n");
}