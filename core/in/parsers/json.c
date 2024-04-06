#include <stdlib.h>
#include <string.h>
#include "libs/cFILE/cFILE.h"
#include "libs/cJSON/cJSON.h"
#include "libs/cLOG/cLOG.h"

#include "json.h"
#include "../../CFD.h"

void CFD_JSON_Parse(CFD_t *cfd)
{
    if (cfd->in->file->extension != JSON)
    {
        log_fatal("Error: Invalid in file extension. Only JSON accepted.");
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
    cfd->in->geometry->x = (float)(cJSON_IsNumber(x) ? cJSON_GetNumberValue(x) : DEFAULT_IN_GEOMETRY_X);

    y = cJSON_GetObjectItemCaseSensitive(geometry, "y");
    cfd->in->geometry->y = (float)(cJSON_IsNumber(y) ? cJSON_GetNumberValue(y) : DEFAULT_IN_GEOMETRY_Y);
}

void CFD_JSON_Parse_In_Fluid(CFD_t *cfd, cJSON *fluid)
{
    const cJSON *nu = NULL;
    const cJSON *Re = NULL;

    nu = cJSON_GetObjectItemCaseSensitive(fluid, "nu");
    cfd->in->fluid->nu = cJSON_IsNumber(nu) ? cJSON_GetNumberValue(nu) : DEFAULT_IN_FLUID_NU;

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
    if (FILE_String_Compare_Insensitive(cJSON_IsString(type) ? type->valuestring : DEFAULT_ENGINE_MESH_TYPE, "STAGGERED") == 0)
    {
        cfd->engine->mesh->type = STAGGERED;
    }
    else if (FILE_String_Compare_Insensitive(type->valuestring, "COLLOCATED") == 0)
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
    cfd->engine->mesh->nodes->Nx = (uint16_t)(cJSON_IsNumber(Nx) ? cJSON_GetNumberValue(Nx) : DEFAULT_ENGINE_MESH_NODES_X);
    cfd->engine->mesh->nodes->Ny = (uint16_t)(cJSON_IsNumber(Ny) ? cJSON_GetNumberValue(Ny) : DEFAULT_ENGINE_MESH_NODES_Y);

    elements = cJSON_GetObjectItemCaseSensitive(mesh, "elements");
    const cJSON *element_type = cJSON_GetObjectItemCaseSensitive(elements, "type");
    if (FILE_String_Compare_Insensitive(cJSON_IsString(element_type) ? element_type->valuestring : DEFAULT_ENGINE_MESH_ELEMENTS_TYPE, "RECTANGULAR") == 0)
    {
        cfd->engine->mesh->element->type = RECTANGULAR;
    }
    else if (FILE_String_Compare_Insensitive(element_type->valuestring, "TRIANGULAR") == 0)
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
    const cJSON *args = NULL;

    type = cJSON_GetObjectItemCaseSensitive(method, "type");
    if (FILE_String_Compare_Insensitive(cJSON_IsString(type) ? type->valuestring : DEFAULT_ENGINE_METHOD_TYPE, "SCGS") == 0)
    {
        cfd->engine->method->type = SCGS;
    }
    else if (FILE_String_Compare_Insensitive(type->valuestring, "SIMPLE") == 0)
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
    cfd->engine->method->tolerance = (float)(cJSON_IsNumber(tolerance) ? cJSON_GetNumberValue(tolerance) : DEFAULT_ENGINE_METHOD_TOLERANCE);

    maxIter = cJSON_GetObjectItemCaseSensitive(method, "maxIter");
    cfd->engine->method->maxIter = (uint16_t)(cJSON_IsNumber(maxIter) ? cJSON_GetNumberValue(maxIter) : DEFAULT_ENGINE_METHOD_MAX_ITER);

    args = cJSON_GetObjectItemCaseSensitive(method, "args");
    cfd->engine->method->args = cJSON_IsObject(args) ? cJSON_Duplicate(args, 1) : NULL;
}

void CFD_JSON_Parse_Engine_Schemes(CFD_t *cfd, cJSON *schemes)
{
    const cJSON *convection = NULL;
    const cJSON *diffusion = NULL;

    convection = cJSON_GetObjectItemCaseSensitive(schemes, "convection");
    if (FILE_String_Compare_Insensitive(cJSON_IsString(convection) ? convection->valuestring : DEFAULT_ENGINE_SCHEMES_CONVECTION, "UDS") == 0)
    {
        cfd->engine->schemes->convection->type = UDS;
    }
    else if (FILE_String_Compare_Insensitive(convection->valuestring, "CDS") == 0)
    {
        cfd->engine->schemes->convection->type = CDS;
    }
    else if (FILE_String_Compare_Insensitive(convection->valuestring, "QUICK") == 0)
    {
        cfd->engine->schemes->convection->type = QUICK;
    }
    else if (FILE_String_Compare_Insensitive(convection->valuestring, "HYBRID") == 0)
    {
        cfd->engine->schemes->convection->type = HYBRID;
    }
    else
    {
        log_warn("Invalid convection scheme. Permitted values: UDS | UDS | QUICK | HYBRID");
        log_info("Choosing default UDS");
        cfd->engine->schemes->convection->type = UDS;
    }

    diffusion = cJSON_GetObjectItemCaseSensitive(schemes, "diffusion");
    if (FILE_String_Compare_Insensitive(cJSON_IsString(diffusion) ? diffusion->valuestring : DEFAULT_ENGINE_SCHEMES_DIFFUSION, "SECOND") == 0)
    {
        cfd->engine->schemes->diffusion->type = SECOND;
    }
    else if (FILE_String_Compare_Insensitive(diffusion->valuestring, "FOURTH") == 0)
    {
        cfd->engine->schemes->diffusion->type = FOURTH;
    }
    else
    {
        log_warn("Invalid diffusion scheme. Permitted values: SECOND | FOURTH");
        log_info("Choosing default SECOND");
        cfd->engine->schemes->diffusion->type = SECOND;
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
    const cJSON *extension = NULL;

    path = cJSON_GetObjectItemCaseSensitive(file, "path");
    sprintf(cfd->out->file->path, "%s", cJSON_IsString(path) ? path->valuestring : DEFAULT_OUT_FILE_PATH);

    name = cJSON_GetObjectItemCaseSensitive(file, "name");
    // sprintf(cfd->out->file->name, "%s", cJSON_IsString(name) ? name->valuestring : DEFAULT_OUT_FILE_NAME);
    sprintf(cfd->out->file->name, "%s", cJSON_IsString(name) ? name->valuestring : cfd->in->file->name);

    extension = cJSON_GetObjectItemCaseSensitive(file, "format");
    if (FILE_String_to_Extension(cJSON_IsString(extension) ? extension->valuestring : DEFAULT_OUT_FILE_FORMAT) != -1)
    {
        cfd->out->file->extension = FILE_String_to_Extension(cJSON_IsString(extension) ? extension->valuestring : DEFAULT_OUT_FILE_FORMAT);
    }
    else
    {
        log_warn("Invalid output file extension. Permitted values: DAT | TXT | JSON");
        log_info("Choosing default DAT");
        cfd->out->file->extension = DAT;
    }
}