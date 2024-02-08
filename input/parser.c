#include <stdio.h>
#include <string.h>
#include <getopt.h>

#include "parser.h"

#include "../CFD.h"

void CFD_ParseCMD(CFD_t *cfd, int argc, char *argv[])
{
    int c;
    int option_index = 0;
    static struct option long_options[] = {
        {"help", no_argument, NULL, 'h'},
        {"version", no_argument, NULL, 'v'},
        {"input", required_argument, NULL, 'i'},
        {"format", required_argument, NULL, 'f'},
        {0, 0, 0, 0}};

    while ((c = getopt_long(argc, argv, "hvi:f:", long_options, &option_index)) != -1)
    {
        switch (c)
        {

        case 'h':
            CFD_PrintHelp();
            exit(EXIT_SUCCESS);
            break;

        case 'v':
            CFD_PrintVersion();
            exit(EXIT_SUCCESS);
            break;

        case 'i':
            if (sscanf(optarg, "%s", cfd->input->file->name) != 1)
            {
                fprintf(stderr, "Invalid argument for input file name\n");
                exit(EXIT_FAILURE);
            }
            break;

        case 'f':
        {
            char format[5];

            if (sscanf(optarg, "%s", format) != 1 ||
                (strcmp(format, "TXT") != 0 &&
                 strcmp(format, "CSV") != 0 &&
                 strcmp(format, "JSON") != 0))
            {
                fprintf(stderr, "Invalid argument for output file format\n");
                exit(EXIT_FAILURE);
            }
            if (strcmp(format, "TXT") == 0)
            {
                cfd->output->file->format = TXT;
            }
            else if (strcmp(format, "CSV") == 0)
            {
                cfd->output->file->format = CSV;
            }
            else if (strcmp(format, "JSON") == 0)
            {
                cfd->output->file->format = JSON;
            }
            break;
        }
        default:
            CFD_PrintInvalidArgument(optarg);
            exit(EXIT_FAILURE);
        }
    }
}

void CFD_PrintHelp()
{
    printf("CFD Solver\n");
    printf("Author:\n\tTommaso Bocchietti\n");
    printf("Date:\n\t2024\n");
    printf("Version:\n\t0.1\n");
    printf("Description:\n");
    printf("\tThis program is a solver for the Navier-Stokes equations for compressible flow.\n");
    printf("\tDeveloped as a project for the course \"ME663 - Computational Fluid Dynamics\"\n");
    printf("\ttaught by Prof. Fue-Sang Lien at Univerity of Waterloo (CA), A.Y. 2023/2024\n");
    printf("\n");
    printf("Usage: ./main [OPTIONS]\n");
    printf("Options:\n");
    printf("\t-h, --help\tPrint this help message\n");
    printf("\t-v, --version\tPrint the version of the program\n");
    printf("\t-i, --input\tInput file path (relative or absolute)\n");
    printf("\t-f, --format\tOutput format (TXT | CSV | JSON)\n");
    printf("\n");
}

void CFD_PrintVersion()
{
    printf("CFD Solver v0.1\n");
}

void CFD_PrintInvalidArgument(char *arg)
{
    printf("Invalid argument: \"%s\"\n", arg);
    printf("Use -h or --help for more information\n");
}