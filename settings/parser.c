#include "parser.h"

#include <stdio.h>
#include <getopt.h>

void CFD_Settings_Parse(settings_t *settings, int argc, char *argv[])
{
    int c;
    int option_index = 0;
    static struct option long_options[] = {
        {"help", no_argument, NULL, 'h'},
        {"domain", required_argument, NULL, 'd'}, // nxn
        {"mu", required_argument, NULL, 'm'},
        {"velocity", required_argument, NULL, 'u'},
        {"schemes", required_argument, NULL, 's'},    // convective x diffusion
        {"relaxation", required_argument, NULL, 'r'}, // nxn
        {"iterations", required_argument, NULL, 'i'},
        {"tolerance", required_argument, NULL, 't'},
        {"grid", required_argument, NULL, 'g'}, // nxn
        {0, 0, 0, 0}};

    while ((c = getopt_long(argc, argv, "hs:r:i:t:o:q:x:y:u:m:", long_options, &option_index)) != -1)
    {
        switch (c)
        {
        case 'h':
            CFD_Settings_Help();
            exit(EXIT_SUCCESS);
            break;
        case 'd':
            if (sscanf(optarg, "%fx%f", &settings->problem_data.domain_dimension.x, &settings->problem_data.domain_dimension.y) != 1)
            {
                fprintf(stderr, "Invalid argument for the length of the domain\n");
                exit(EXIT_FAILURE);
            }
            if (settings->problem_data.domain_dimension.x <= 0 || settings->problem_data.domain_dimension.y <= 0)
            {
                printf("Invalid length of the domain: %s\n", optarg);
                exit(EXIT_FAILURE);
            }
            break;

        case 'm':
            if (sscanf(optarg, "%f", &settings->problem_data.fluid_properties.mu) != 1)
            {
                fprintf(stderr, "Invalid argument for the viscosity\n");
                exit(EXIT_FAILURE);
            }
            if (settings->problem_data.fluid_properties.mu <= 0)
            {
                printf("Invalid viscosity: %s\n", optarg);
                exit(EXIT_FAILURE);
            }
            break;

        case 'u':
            if (sscanf(optarg, "%f", &settings->problem_data.uLid) != 1)
            {
                fprintf(stderr, "Invalid argument for the velocity of the lid\n");
                exit(EXIT_FAILURE);
            }
            if (settings->problem_data.uLid <= 0)
            {
                printf("Invalid velocity of the lid: %s\n", optarg);
                exit(EXIT_FAILURE);
            }
            break;

        case 's':
            if (sscanf(optarg, "%ux%u", &settings->solver.schemes.convection.type, &settings->solver.schemes.diffusion.type) != 2)
            {
                fprintf(stderr, "Invalid argument for the convection scheme\n");
                exit(EXIT_FAILURE);
            }
            if (settings->solver.schemes.convection.type != UDS &&
                settings->solver.schemes.convection.type != HYBRID &&
                settings->solver.schemes.convection.type != QUICK)
            {
                printf("Invalid convection scheme: %s\n", optarg);
                exit(EXIT_FAILURE);
            }
            if (settings->solver.schemes.diffusion.type != SECOND_ORDER &&
                settings->solver.schemes.diffusion.type != FOURTH_ORDER)
            {
                printf("Invalid diffusion scheme: %s\n", optarg);
                exit(EXIT_FAILURE);
            }
            break;

        case 'r':
            if (sscanf(optarg, "%fx%f", &settings->solver.under_relaxation_factors.u, &settings->solver.under_relaxation_factors.v) != 2)
            {
                fprintf(stderr, "Invalid argument for the relaxation factor\n");
                exit(EXIT_FAILURE);
            }
            if (settings->solver.under_relaxation_factors.u < 0 || settings->solver.under_relaxation_factors.u > 1 ||
                settings->solver.under_relaxation_factors.v < 0 || settings->solver.under_relaxation_factors.v > 1)
            {
                printf("Invalid relaxation factor: %s\n", optarg);
                exit(EXIT_FAILURE);
            }
            break;

        case 'i':
            if (sscanf(optarg, "%d", &settings->solver.max_iterations) != 1)
            {
                fprintf(stderr, "Invalid argument for the maximum number of iterations\n");
                exit(EXIT_FAILURE);
            }
            break;

        case 't':
            if (sscanf(optarg, "%f", &settings->solver.tolerance) != 1)
            {
                fprintf(stderr, "Invalid argument for the tolerance\n");
                exit(EXIT_FAILURE);
            }
            break;

        case 'e':
            if (sscanf(optarg, "%ux%u", (unsigned int *)&settings->solver.mesh.size.Nx, (unsigned int *)&settings->solver.mesh.size.Ny) != 2)
            {
                fprintf(stderr, "Invalid argument for the number of elements\n");
                exit(EXIT_FAILURE);
            }
            if (settings->solver.mesh.size.Nx <= 0 || settings->solver.mesh.size.Ny <= 0)
            {
                printf("Invalid number of elements: %s\n", optarg);
                exit(EXIT_FAILURE);
            }
            break;

        default:
            CFD_Settings_Help();
            exit(EXIT_FAILURE);
        }
    }
}

void CFD_Settings_Help()
{
    printf("Usage: ./main [OPTIONS]\n");
    printf("Options:\n");
    printf("\t-h, --help\tPrint this help message\n");
    printf("\t-g, --grid\tNumber of elements (Nx x Ny)\n");
    printf("\t-s, --schemes\tConvection and diffusion schemes (convection x diffusion)\n");
    printf("\t\t\tConvection schemes: 0 (UDS), 1 (HYBRID), 2 (QUICK)\n");
    printf("\t\t\tDiffusion schemes: 0 (SECOND_ORDER), 1 (FOURTH_ORDER)\n");
    printf("\t-r, --relaxation\tUnder-relaxation factors (u x v)\n");
    printf("\t-i, --iterations\tMaximum number of iterations\n");
    printf("\t-t, --tolerance\tConvergence tolerance\n");
    printf("\t-d, --domain\tSize of the domain (Lx x Ly)\n");
    printf("\t-u, --velocity\tVelocity of the lid\n");
    printf("\t-m, --mu\tViscosity of the fluid\n");
    printf("\n");
}