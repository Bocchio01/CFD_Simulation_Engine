#include <stdlib.h>
#include <string.h>
#include "../utils/cJSON/cJSON.h"

#include "load.h"

#include "../CFD.h"

void CFD_Input_Load(CFD_t *cfd)
{
    long file_size;
    size_t name_length;
    size_t suffix_length;

    if (cfd->input->file->name == NULL)
    {
        cfd->input->file->name = "data/input.json";
    }

    name_length = strlen(cfd->input->file->name);
    suffix_length = strlen(".json");
    if (name_length >= suffix_length && strcmp(cfd->input->file->name + name_length - suffix_length, ".json") != 0)
    {
        fprintf(stderr, "Error: Invalid input file format. Only JSON accepted.\n");
        exit(EXIT_FAILURE);
    }

    cfd->input->file->pointer = fopen(cfd->input->file->name, "r");
    if (cfd->input->file->pointer == NULL)
    {
        printf("Error: Unable to open file %s\n", cfd->input->file->name);
        exit(EXIT_FAILURE);
    }

    fseek(cfd->input->file->pointer, 0, SEEK_END);
    file_size = ftell(cfd->input->file->pointer);
    fseek(cfd->input->file->pointer, 0, SEEK_SET);

    cfd->input->file->buffer = (char *)malloc(file_size + 1);

    fread(cfd->input->file->buffer, 1, file_size, cfd->input->file->pointer);
    cfd->input->file->buffer[file_size] = '\0';

    fclose(cfd->input->file->pointer);

    cJSON *json = cJSON_Parse(cfd->input->file->buffer);
    if (json == NULL)
    {
        const char *error_ptr = cJSON_GetErrorPtr();
        if (error_ptr != NULL)
        {
            fprintf(stderr, "Error before: %s\n", error_ptr);
            exit(EXIT_FAILURE);
        }
    }

    CFD_Input_LoadInput(cfd, cJSON_GetObjectItemCaseSensitive(json, "input"));
    CFD_Input_LoadSolver(cfd, cJSON_GetObjectItemCaseSensitive(json, "solver"));
    CFD_Input_LoadOutput(cfd, cJSON_GetObjectItemCaseSensitive(json, "output"));

    // CFD_LoadInputChecher(cfd);
}

void CFD_Input_LoadInput(CFD_t *cfd, cJSON *input)
{
    const cJSON *uLid = NULL;

    uLid = cJSON_GetObjectItemCaseSensitive(input, "uLid");
    cfd->input->uLid = uLid->valuedouble;

    CFD_Input_LoadInputGeometry(cfd, cJSON_GetObjectItemCaseSensitive(input, "geometry"));
    CFD_Input_LoadInputFluid(cfd, cJSON_GetObjectItemCaseSensitive(input, "fluid"));

    // cJSON_Delete(input);
}

void CFD_Input_LoadInputGeometry(CFD_t *cfd, cJSON *geometry)
{
    const cJSON *x = NULL;
    const cJSON *y = NULL;

    x = cJSON_GetObjectItemCaseSensitive(geometry, "x");
    cfd->input->geometry->x = x->valueint;

    y = cJSON_GetObjectItemCaseSensitive(geometry, "y");
    cfd->input->geometry->y = y->valueint;

    // cJSON_Delete(geometry);
}

void CFD_Input_LoadInputFluid(CFD_t *cfd, cJSON *fluid)
{
    const cJSON *mu = NULL;

    mu = cJSON_GetObjectItemCaseSensitive(fluid, "mu");
    cfd->input->fluid->mu = mu->valuedouble;

    // cJSON_Delete(fluid);
}

void CFD_Input_LoadSolver(CFD_t *cfd, cJSON *solver)
{
    CFD_Input_LoadSolverMesh(cfd, cJSON_GetObjectItemCaseSensitive(solver, "mesh"));
    CFD_Input_LoadSolverMethod(cfd, cJSON_GetObjectItemCaseSensitive(solver, "method"));
    CFD_Input_LoadSolverSchemes(cfd, cJSON_GetObjectItemCaseSensitive(solver, "schemes"));

    // cJSON_Delete(solver);
}

void CFD_Input_LoadSolverMesh(CFD_t *cfd, cJSON *mesh)
{
    const cJSON *type = NULL;
    const cJSON *nodes = NULL;
    const cJSON *elements = NULL;

    type = cJSON_GetObjectItemCaseSensitive(mesh, "type");
    if (strcasecmp(type->valuestring, "STAGGERED") == 0)
    {
        cfd->solver->mesh->type = STAGGERED;
    }
    else if (strcasecmp(type->valuestring, "COLLOCATED") == 0)
    {
        cfd->solver->mesh->type = COLLOCATED;
    }
    else
    {
        printf("Error: Invalid mesh type\n");
        exit(EXIT_FAILURE);
    }

    nodes = cJSON_GetObjectItemCaseSensitive(mesh, "nodes");
    const cJSON *Nx = cJSON_GetObjectItemCaseSensitive(nodes, "Nx");
    const cJSON *Ny = cJSON_GetObjectItemCaseSensitive(nodes, "Ny");
    cfd->solver->mesh->nodes->Nx = Nx->valueint;
    cfd->solver->mesh->nodes->Ny = Ny->valueint;

    elements = cJSON_GetObjectItemCaseSensitive(mesh, "elements");
    const cJSON *element_type = cJSON_GetObjectItemCaseSensitive(elements, "type");
    if (strcasecmp(element_type->valuestring, "RECTANGULAR") == 0)
    {
        cfd->solver->mesh->element->type = RECTANGULAR;
    }
    else if (strcasecmp(element_type->valuestring, "TRIANGULAR") == 0)
    {
        cfd->solver->mesh->element->type = TRIANGULAR;
    }
    else
    {
        printf("Error: Invalid element type\n");
        exit(EXIT_FAILURE);
    }

    // cJSON_Delete(mesh);
}

void CFD_Input_LoadSolverMethod(CFD_t *cfd, cJSON *method)
{
    const cJSON *type = NULL;
    const cJSON *tolerance = NULL;
    const cJSON *maxIter = NULL;
    const cJSON *underRelaxation = NULL;

    type = cJSON_GetObjectItemCaseSensitive(method, "type");
    if (strcasecmp(type->valuestring, "SCGS") == 0)
    {
        cfd->solver->method->type = SCGS;
    }
    else if (strcasecmp(type->valuestring, "SIMPLE") == 0)
    {
        cfd->solver->method->type = SIMPLE;
    }

    tolerance = cJSON_GetObjectItemCaseSensitive(method, "tolerance");
    cfd->solver->method->tolerance = tolerance->valuedouble;

    maxIter = cJSON_GetObjectItemCaseSensitive(method, "maxIter");
    cfd->solver->method->maxIter = maxIter->valueint;

    underRelaxation = cJSON_GetObjectItemCaseSensitive(method, "underRelaxation");
    const cJSON *u = cJSON_GetObjectItemCaseSensitive(underRelaxation, "u");
    const cJSON *v = cJSON_GetObjectItemCaseSensitive(underRelaxation, "v");
    const cJSON *p = cJSON_GetObjectItemCaseSensitive(underRelaxation, "p");
    cfd->solver->method->under_relaxation_factors->u = u->valuedouble;
    cfd->solver->method->under_relaxation_factors->v = v->valuedouble;
    cfd->solver->method->under_relaxation_factors->p = p->valuedouble;

    // cJSON_Delete(method);
}

void CFD_Input_LoadSolverSchemes(CFD_t *cfd, cJSON *schemes)
{
    const cJSON *convection = NULL;
    const cJSON *diffusion = NULL;

    convection = cJSON_GetObjectItemCaseSensitive(schemes, "convection");
    if (strcasecmp(convection->valuestring, "UDS") == 0)
    {
        cfd->solver->schemes->convection->type = UDS;
    }
    else if (strcasecmp(convection->valuestring, "HYBRID") == 0)
    {
        cfd->solver->schemes->convection->type = HYBRID;
    }
    else if (strcasecmp(convection->valuestring, "QUICK") == 0)
    {
        cfd->solver->schemes->convection->type = QUICK;
    }
    else
    {
        printf("Error: Invalid convection scheme\n");
        exit(EXIT_FAILURE);
    }

    diffusion = cJSON_GetObjectItemCaseSensitive(schemes, "diffusion");
    if (strcasecmp(diffusion->valuestring, "SECOND_ORDER") == 0)
    {
        cfd->solver->schemes->diffusion->type = SECOND_ORDER;
    }
    else if (strcasecmp(diffusion->valuestring, "FOURTH_ORDER") == 0)
    {
        cfd->solver->schemes->diffusion->type = FOURTH_ORDER;
    }
    else
    {
        printf("Error: Invalid diffusion scheme\n");
        exit(EXIT_FAILURE);
    }

    // cJSON_Delete(schemes);
}

void CFD_Input_LoadOutput(CFD_t *cfd, cJSON *output)
{
    const cJSON *format = NULL;

    format = cJSON_GetObjectItemCaseSensitive(output, "format");
    if (strcasecmp(format->valuestring, "CSV") == 0)
    {
        cfd->output->file->format = CSV;
    }
    else if (strcasecmp(format->valuestring, "TXT") == 0)
    {
        cfd->output->file->format = TXT;
    }
    else if (strcasecmp(format->valuestring, "JSON") == 0)
    {
        cfd->output->file->format = JSON;
    }
    else
    {
        printf("Error: Invalid output format\n");
        exit(EXIT_FAILURE);
    }
}