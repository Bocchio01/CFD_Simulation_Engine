#include <stdlib.h>
// #include <cjson/cJSON.h>

#include "loader.h"

#include "../CFD.h"

void CFD_Load(CFD_t *cfd)
{
    long file_size;

    if (cfd->input->file->name == NULL)
    {
        cfd->input->file->name = "data/input.json";
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

    // cJSON *json = cJSON_Parse(cfd->input->file->buffer);
    // if (json == NULL)
    // {
    //     const char *error_ptr = cJSON_GetErrorPtr();
    //     if (error_ptr != NULL)
    //     {
    //         fprintf(stderr, "Error before: %s\n", error_ptr);
    //         exit(EXIT_FAILURE);
    //     }
    // }

    // CFD_LoadInput(cfd, cJSON_GetObjectItemCaseSensitive(json, "input"));
    // CFD_LoadSolver(cfd, cJSON_GetObjectItemCaseSensitive(json, "solver"));
    // CFD_LoadOutput(cfd, cJSON_GetObjectItemCaseSensitive(json, "output"));
}

// void CFD_LoadInput(CFD_t *cfd, cJSON *input)
// {
//     const cJSON *uLid = NULL;
//     const cJSON *geometry = NULL;
//     const cJSON *x = NULL;
//     const cJSON *y = NULL;
//     const cJSON *fluid = NULL;
//     const cJSON *mu = NULL;

//     uLid = cJSON_GetObjectItemCaseSensitive(input, "uLid");
//     cfd->input->uLid = uLid->valuedouble;

//     geometry = cJSON_GetObjectItemCaseSensitive(input, "geometry");
//     cJSON *x = cJSON_GetObjectItemCaseSensitive(geometry, "x");
//     cJSON *y = cJSON_GetObjectItemCaseSensitive(geometry, "y");
//     cfd->input->geometry->x = x->valueint;
//     cfd->input->geometry->y = y->valueint;

//     fluid = cJSON_GetObjectItemCaseSensitive(input, "fluid");
//     cJSON *mu = cJSON_GetObjectItemCaseSensitive(fluid, "mu");
//     cfd->input->fluid->mu = mu->valuedouble;

//     cJSON_Delete(input);
// }

// void CFD_LoadSolver(CFD_t *cfd, cJSON *solver)
// {
//     // Load solver from file
//     // ...
// }

// void CFD_LoadOutput(CFD_t *cfd, cJSON *output)
// {
//     // Load output from file
//     // ...
// }