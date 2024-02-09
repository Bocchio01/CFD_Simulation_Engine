#include <stdlib.h>
#include <string.h>
#include "../../utils/cJSON/cJSON.h"
#include "../../utils/log/log.h"

#include "json.h"
#include "../../main.h"
#include "../../CFD.h"

void CFD_JSON_Parse(CFD_t *cfd)
{
    if (cfd->in->file->format != JSON)
    {
        log_fatal("Error: Invalid in file format. Only JSON accepted.");
        exit(EXIT_FAILURE);
    }

    cJSON *json = cJSON_Parse(cfd->in->file->buffer);
    if (json == NULL)
    {
        const char *error_ptr = cJSON_GetErrorPtr();
        if (error_ptr != NULL)
        {
            log_fatal("Error before: %s", error_ptr);
            exit(EXIT_FAILURE);
        }
    }

    CFD_JSON_Parse_In(cfd, cJSON_GetObjectItemCaseSensitive(json, "in"));
    CFD_JSON_Parse_Engine(cfd, cJSON_GetObjectItemCaseSensitive(json, "engine"));
    CFD_JSON_Parse_Out(cfd, cJSON_GetObjectItemCaseSensitive(json, "out"));

    // CFD_LoadInputChecher(cfd);
}

void CFD_JSON_Parse_In(CFD_t *cfd, cJSON *in)
{
    const cJSON *uLid = NULL;

    uLid = cJSON_GetObjectItemCaseSensitive(in, "uLid");
    cfd->in->uLid = cJSON_IsNumber(uLid) ? cJSON_GetNumberValue(uLid) : DEFAULT_IN_ULID;

    CFD_JSON_Parse_In_Geometry(cfd, cJSON_GetObjectItemCaseSensitive(in, "geometry"));
    CFD_JSON_Parse_In_Fluid(cfd, cJSON_GetObjectItemCaseSensitive(in, "fluid"));
}

void CFD_JSON_Parse_In_Geometry(CFD_t *cfd, cJSON *geometry)
{
    const cJSON *x = NULL;
    const cJSON *y = NULL;

    x = cJSON_GetObjectItemCaseSensitive(geometry, "x");
    cfd->in->geometry->x = cJSON_IsNumber(x) ? cJSON_GetNumberValue(x) : DEFAULT_IN_GEOMETRY_X;

    y = cJSON_GetObjectItemCaseSensitive(geometry, "y");
    cfd->in->geometry->y = cJSON_IsNumber(y) ? cJSON_GetNumberValue(y) : DEFAULT_IN_GEOMETRY_Y;
}

void CFD_JSON_Parse_In_Fluid(CFD_t *cfd, cJSON *fluid)
{
    const cJSON *mu = NULL;
    const cJSON *Re = NULL;

    mu = cJSON_GetObjectItemCaseSensitive(fluid, "mu");
    cfd->in->fluid->mu = cJSON_IsNumber(mu) ? cJSON_GetNumberValue(mu) : DEFAULT_IN_FLUID_MU;

    Re = cJSON_GetObjectItemCaseSensitive(fluid, "Re");
    cfd->in->fluid->Re = cJSON_IsNumber(Re) ? cJSON_GetNumberValue(Re) : DEFAULT_IN_FLUID_RE;
}

void CFD_JSON_Parse_Engine(CFD_t *cfd, cJSON *engine)
{
    CFD_JSON_Parse_Engine_Mesh(cfd, cJSON_GetObjectItemCaseSensitive(engine, "mesh"));
    CFD_JSON_Parse_Engine_Method(cfd, cJSON_GetObjectItemCaseSensitive(engine, "method"));
    CFD_JSON_Parse_Engine_Schemes(cfd, cJSON_GetObjectItemCaseSensitive(engine, "schemes"));
}

void CFD_JSON_Parse_Engine_Mesh(CFD_t *cfd, cJSON *mesh)
{
    const cJSON *type = NULL;
    const cJSON *nodes = NULL;
    const cJSON *elements = NULL;

    type = cJSON_GetObjectItemCaseSensitive(mesh, "type");
    if (strcasecmp(type->valuestring, "STAGGERED") == 0)
    {
        cfd->engine->mesh->type = STAGGERED;
    }
    else if (strcasecmp(type->valuestring, "COLLOCATED") == 0)
    {
        cfd->engine->mesh->type = COLLOCATED;
    }
    else
    {
        log_warn("Invalid mesh type. Permitted values: STAGGERED | COLLOCATED");
        log_info("Choosing default STAGGERED");
        cfd->engine->mesh->type = STAGGERED;
    }

    nodes = cJSON_GetObjectItemCaseSensitive(mesh, "nodes");
    const cJSON *Nx = cJSON_GetObjectItemCaseSensitive(nodes, "Nx");
    const cJSON *Ny = cJSON_GetObjectItemCaseSensitive(nodes, "Ny");
    cfd->engine->mesh->nodes->Nx = cJSON_IsNumber(Nx) ? cJSON_GetNumberValue(Nx) : DEFAULT_ENGINE_MESH_NODES_X;
    cfd->engine->mesh->nodes->Ny = cJSON_IsNumber(Ny) ? cJSON_GetNumberValue(Ny) : DEFAULT_ENGINE_MESH_NODES_Y;

    elements = cJSON_GetObjectItemCaseSensitive(mesh, "elements");
    const cJSON *element_type = cJSON_GetObjectItemCaseSensitive(elements, "type");
    if (strcasecmp(element_type->valuestring, "RECTANGULAR") == 0)
    {
        cfd->engine->mesh->element->type = RECTANGULAR;
    }
    else if (strcasecmp(element_type->valuestring, "TRIANGULAR") == 0)
    {
        cfd->engine->mesh->element->type = TRIANGULAR;
    }
    else
    {
        log_warn("Invalid element type. Permitted values: RECTANGULAR | TRIANGULAR");
        log_info("Choosing default RECTANGULAR");
        cfd->engine->mesh->element->type = RECTANGULAR;
    }
}

void CFD_JSON_Parse_Engine_Method(CFD_t *cfd, cJSON *method)
{
    const cJSON *type = NULL;
    const cJSON *tolerance = NULL;
    const cJSON *maxIter = NULL;
    const cJSON *underRelaxation = NULL;

    type = cJSON_GetObjectItemCaseSensitive(method, "type");
    if (strcasecmp(type->valuestring, "SCGS") == 0)
    {
        cfd->engine->method->type = SCGS;
    }
    else if (strcasecmp(type->valuestring, "SIMPLE") == 0)
    {
        cfd->engine->method->type = SIMPLE;
    }
    else
    {
        log_warn("Invalid method type. Permitted values: SCGS | SIMPLE");
        log_info("Choosing default SCGS");
        cfd->engine->method->type = SCGS;
    }

    tolerance = cJSON_GetObjectItemCaseSensitive(method, "tolerance");
    cfd->engine->method->tolerance = cJSON_IsNumber(tolerance) ? cJSON_GetNumberValue(tolerance) : DEFAULT_ENGINE_METHOD_TOLERANCE;

    maxIter = cJSON_GetObjectItemCaseSensitive(method, "maxIter");
    cfd->engine->method->maxIter = cJSON_IsNumber(maxIter) ? cJSON_GetNumberValue(maxIter) : DEFAULT_ENGINE_METHOD_MAX_ITER;

    underRelaxation = cJSON_GetObjectItemCaseSensitive(method, "underRelaxation");
    const cJSON *u = cJSON_GetObjectItemCaseSensitive(underRelaxation, "u");
    const cJSON *v = cJSON_GetObjectItemCaseSensitive(underRelaxation, "v");
    const cJSON *p = cJSON_GetObjectItemCaseSensitive(underRelaxation, "p");
    cfd->engine->method->under_relaxation_factors->u = cJSON_IsNumber(u) ? cJSON_GetNumberValue(u) : DEFAULT_ENGINE_METHOD_UNDER_RELAXATION_U;
    cfd->engine->method->under_relaxation_factors->v = cJSON_IsNumber(v) ? cJSON_GetNumberValue(v) : DEFAULT_ENGINE_METHOD_UNDER_RELAXATION_V;
    cfd->engine->method->under_relaxation_factors->p = cJSON_IsNumber(p) ? cJSON_GetNumberValue(p) : DEFAULT_ENGINE_METHOD_UNDER_RELAXATION_P;
}

void CFD_JSON_Parse_Engine_Schemes(CFD_t *cfd, cJSON *schemes)
{
    const cJSON *convection = NULL;
    const cJSON *diffusion = NULL;

    convection = cJSON_GetObjectItemCaseSensitive(schemes, "convection");
    if (strcasecmp(convection->valuestring, "UDS") == 0)
    {
        cfd->engine->schemes->convection->type = UDS;
    }
    else if (strcasecmp(convection->valuestring, "HYBRID") == 0)
    {
        cfd->engine->schemes->convection->type = HYBRID;
    }
    else if (strcasecmp(convection->valuestring, "QUICK") == 0)
    {
        cfd->engine->schemes->convection->type = QUICK;
    }
    else
    {
        log_warn("Invalid convection scheme. Permitted values: UDS | HYBRID | QUICK");
        log_info("Choosing default UDS");
        cfd->engine->schemes->convection->type = UDS;
    }

    diffusion = cJSON_GetObjectItemCaseSensitive(schemes, "diffusion");
    if (strcasecmp(diffusion->valuestring, "SECOND_ORDER") == 0)
    {
        cfd->engine->schemes->diffusion->type = SECOND_ORDER;
    }
    else if (strcasecmp(diffusion->valuestring, "FOURTH_ORDER") == 0)
    {
        cfd->engine->schemes->diffusion->type = FOURTH_ORDER;
    }
    else
    {
        log_warn("Invalid diffusion scheme. Permitted values: SECOND_ORDER | FOURTH_ORDER");
        log_info("Choosing default SECOND_ORDER");
        cfd->engine->schemes->diffusion->type = SECOND_ORDER;
    }
}

void CFD_JSON_Parse_Out(CFD_t *cfd, cJSON *out)
{
    CFD_JSON_Parse_Out_File(cfd, cJSON_GetObjectItemCaseSensitive(out, "file"));
}

void CFD_JSON_Parse_Out_File(CFD_t *cfd, cJSON *file)
{
    const cJSON *name = NULL;
    const cJSON *path = NULL;
    const cJSON *format = NULL;

    path = cJSON_GetObjectItemCaseSensitive(file, "path");
    cfd->out->file->path = cJSON_IsString(path) ? path->valuestring : DEFAULT_OUT_FILE_PATH;

    name = cJSON_GetObjectItemCaseSensitive(file, "name");
    cfd->out->file->name = cJSON_IsString(name) ? name->valuestring : DEFAULT_OUT_FILE_NAME;

    format = cJSON_GetObjectItemCaseSensitive(file, "format");
    if (file_string_to_format(format->valuestring) != false)
    {
        cfd->out->file->format = file_string_to_format(format->valuestring);
    }
    else
    {
        log_warn("Invalid output file format. Permitted values: CSV | TXT | JSON");
        log_info("Choosing default JSON");
        cfd->out->file->format = JSON;
    }
}