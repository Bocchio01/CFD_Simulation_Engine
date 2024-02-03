#include "parser.h"

#include <getopt.h>

/*
- `-h` or `--help` to get some help
- `-s` or `--scheme` to choose the convection scheme (`UDS`, `Hybrid` or `QUICK`)
- `-r` or `--relaxation` to choose the relaxation factor
- `-i` or `--iterations` to choose the maximum number of iterations
- `-t` or `--tolerance` to choose the tolerance for the residual
- `-o` or `--output` to choose the output file name
- `-p` or `--plot` to plot the results
- `-v` or `--verbose` to print the residual at each iteration
- `-d` or `--debug` to print some debug information
- `-c` or `--clean` to clean the output files
- `-f` or `--force` to force the execution of the code even if the output file already exists
- `-q` or `--quiet` to suppress the output
- `-a` or `--all` to run the code with all the convection schemes
- `-e` or `--error` to compute the error between the analytical and numerical solution
- `-n` or `--nodes` to choose the number of nodes in the x and y direction
- `-x` or `--xlength` to choose the length of the domain in the x direction
- `-y` or `--ylength` to choose the length of the domain in the y direction
- `-u` or `--velocity` to choose the velocity of the lid
- `-m` or `--mu` to choose the viscosity of the fluid
*/

void fill_defaults(CFD_t *cfd)
{
}

void print_help()
{
    printf("Usage: ./cfd [OPTIONS]\n");
    printf("Options:\n");
    printf("  -h, --help\t\t\t\tPrint this help message\n");
    printf("  -s, --scheme <scheme>\t\tChoose the convection scheme (UDS, Hybrid or QUICK)\n");
    printf("  -r, --relaxation <factor>\tChoose the relaxation factor\n");
    printf("  -i, --iterations <number>\tChoose the maximum number of iterations\n");
    printf("  -t, --tolerance <number>\tChoose the tolerance for the residual\n");
    printf("  -o, --output <file>\t\tChoose the output file name\n");
    printf("  -p, --plot\t\t\t\tPlot the results\n");
    printf("  -v, --verbose\t\t\tPrint the residual at each iteration\n");
    printf("  -d, --debug\t\t\tPrint some debug information\n");
    printf("  -c, --clean\t\t\tClean the output files\n");
    printf("  -f, --force\t\t\tForce the execution of the code even if the output file already exists\n");
    printf("  -q, --quiet\t\t\tSuppress the output\n");
    printf("  -a, --all\t\t\tRun the code with all the convection schemes\n");
    printf("  -e, --error\t\t\tCompute the error between the analytical and numerical solution\n");
    printf("  -n, --nodes <number>\t\tChoose the number of nodes in the x and y direction\n");
    printf("  -x, --xlength <length>\tChoose the length of the domain in the x direction\n");
    printf("  -y, --ylength <length>\tChoose the length of the domain in the y direction\n");
    printf("  -u, --velocity <velocity>\tChoose the velocity of the lid\n");
    printf("  -m, --mu <viscosity>\t\tChoose the viscosity of the fluid\n");
}

void parse_args(
    int argc,
    char *argv[])
{
    int c;
    int option_index = 0;
    static struct option long_options[] = {
        {"help", no_argument, 0, 'h'},
        {"scheme", required_argument, 0, 's'},
        {"relaxation", required_argument, 0, 'r'},
        {"iterations", required_argument, 0, 'i'},
        {"tolerance", required_argument, 0, 't'},
        {"output", required_argument, 0, 'o'},
        {"plot", no_argument, 0, 'p'},
        {"verbose", no_argument, 0, 'v'},
        {"debug", no_argument, 0, 'd'},
        {"clean", no_argument, 0, 'c'},
        {"force", no_argument, 0, 'f'},
        {"quiet", no_argument, 0, 'q'},
        {"all", no_argument, 0, 'a'},
        {"error", no_argument, 0, 'e'},
        {"nodes", required_argument, 0, 'n'},
        {"xlength", required_argument, 0, 'x'},
        {"ylength", required_argument, 0, 'y'},
        {"velocity", required_argument, 0, 'u'},
        {"mu", required_argument, 0, 'm'},
        {0, 0, 0, 0}};

    while ((c = getopt_long(argc, argv, "hs:r:i:t:o:pvdcfqan:x:y:u:m:", long_options, &option_index)) != -1)
    {
        switch (c)
        {
        case 'h':
            print_help();
            exit(0);
            break;
        case 's':
            strcpy(scheme, optarg);
            break;
        case 'r':
            *relaxation = atof(optarg);
            break;
        case 'i':
            *iterations = atoi(optarg);
            break;
        case 't':
            *tolerance = atof(optarg);
            break;
        case 'o':
            strcpy(output, optarg);
            break;
        case 'p':
            *plot = 1;
            break;
        case 'v':
            *verbose = 1;
            break;
        case 'd':
            *debug = 1;
            break;
        case 'c':
            *clean = 1;
            break;
        case 'f':
            *force = 1;
            break;
        case 'q':
            *quiet = 1;
            break;
        case 'a':

            *all = 1;
            break;

        case 'e':
            *error = 1;
            break;
        case 'n':
            *nodes = atoi(optarg);
            break;
        case 'x':
            *xlength = atof(optarg);
            break;

        case 'y':
            *ylength = atof(optarg);
            break;
        case 'u':

            *velocity = atof(optarg);
            break;

        case 'm':
            *mu = atof(optarg);
            break;
        default:
            print_help();
            exit(1);
        }
    }
}
