#include <stdlib.h>
#include <math.h>

#include "libs/cALGEBRA/cVEC.h"
#include "libs/cLOG/cLOG.h"

#include "engine.h"
#include "mesh/mesh.h"
#include "methods/methods.h"
#include "schemes/schemes.h"

#include "../CFD.h"

void CFD_Setup_Engine(CFD_t *cfd)
{
    if (!isnan(cfd->in->fluid->Re))
    {
        cfd->in->fluid->nu = fabs(cfd->in->uLid) * cfd->in->geometry->x / cfd->in->fluid->Re;
    }

    CFD_Setup_Mesh(cfd);
    CFD_Setup_Method(cfd);
    CFD_Setup_Schemes(cfd);

    log_info("Engine setup complete");
    log_info("Input file:\t%s", cfd->in->file->name);

    switch (cfd->engine->method->type)
    {
    case SCGS:
        log_info("Solver method:\tSCGS");
        break;
    case SIMPLE:
        log_info("Solver method:\tSIMPLE");
        break;
    }

    log_info("Solver tolerance:\t%f", cfd->engine->method->tolerance);
    log_info("Solver max iterations:\t%d", cfd->engine->method->maxIter);

    switch (cfd->engine->schemes->convection->type)
    {
    case UDS:
        log_info("Scheme convection:\tUDS");
        break;
    case CDS:
        log_info("Scheme convection:\tCDS");
        break;
    case QUICK:
        log_info("Scheme convection:\tQUICK");
        break;
    case HYBRID:
        log_info("Scheme convection:\tHYBRID");
        break;
    }

    switch (cfd->engine->schemes->diffusion->type)
    {
    case SECOND:
        log_info("Scheme diffusion:\tSECOND");
        break;
    case FOURTH:
        log_info("Scheme diffusion:\tFOURTH");
        break;
    }

    log_info("Mesh grid elements:\t%d x %d", cfd->engine->mesh->nodes->Nx, cfd->engine->mesh->nodes->Ny);
    log_info("Fluid viscosity:\t%f", cfd->in->fluid->nu);
    log_info("Fluid Reynolds:\t%f", cfd->in->fluid->Re);
}

engine_t *CFD_Allocate_Engine()
{
    engine_t *engine = (engine_t *)malloc(sizeof(engine_t));
    if (engine != NULL)
    {
        engine->mesh = CFD_Allocate_Engine_Mesh();
        engine->method = CFD_Allocate_Engine_Method();
        engine->schemes = CFD_Allocate_Engine_Schemes();

        if (engine->mesh != NULL &&
            engine->method != NULL &&
            engine->schemes != NULL)
        {
            return engine;
        }
    }

    CFD_Free_Engine(engine);
    log_fatal("Error: Could not allocate memory for engine");
    exit(EXIT_FAILURE);
}

mesh_t *CFD_Allocate_Engine_Mesh()
{
    mesh_t *mesh = (mesh_t *)malloc(sizeof(mesh_t));
    if (mesh != NULL)
    {
        mesh->nodes = CFD_Allocate_Engine_Mesh_Nodes();
        mesh->element = CFD_Allocate_Engine_Mesh_Element();
        mesh->data = CFD_Allocate_Engine_Mesh_Data();

        if (mesh->nodes != NULL &&
            mesh->element != NULL &&
            mesh->data != NULL)
        {
            mesh->element->size = (element_size_t *)malloc(sizeof(element_size_t));
            if (mesh->element->size != NULL)
            {
                return mesh;
            }
        }
    }

    log_fatal("Error: Could not allocate memory for engine->mesh");
    exit(EXIT_FAILURE);
}

mesh_nodes_t *CFD_Allocate_Engine_Mesh_Nodes()
{
    mesh_nodes_t *nodes = (mesh_nodes_t *)malloc(sizeof(mesh_nodes_t));
    if (nodes != NULL)
    {
        return nodes;
    }

    log_fatal("Error: Could not allocate memory for engine->mesh->nodes");
    exit(EXIT_FAILURE);
}

mesh_element_t *CFD_Allocate_Engine_Mesh_Element()
{
    mesh_element_t *element = (mesh_element_t *)malloc(sizeof(mesh_element_t));
    if (element != NULL)
    {
        element->size = CFD_Allocate_Engine_Mesh_Element_Size();
        if (element->size != NULL)
        {
            return element;
        }
    }

    log_fatal("Error: Could not allocate memory for engine->mesh->element");
    exit(EXIT_FAILURE);
}

mesh_data_t *CFD_Allocate_Engine_Mesh_Data()
{
    mesh_data_t *data = (mesh_data_t *)malloc(sizeof(mesh_data_t));
    if (data != NULL)
    {
        // data->x = (cMAT2D_t *)malloc(sizeof(cMAT2D_t));
        // data->y = (cMAT2D_t *)malloc(sizeof(cMAT2D_t));
        return data;
    }

    log_fatal("Error: Could not allocate memory for engine->mesh->data");
    exit(EXIT_FAILURE);
}

element_size_t *CFD_Allocate_Engine_Mesh_Element_Size()
{
    element_size_t *size = (element_size_t *)malloc(sizeof(element_size_t));
    if (size != NULL)
    {
        return size;
    }

    log_fatal("Error: Could not allocate memory for engine->mesh->element->size");
    exit(EXIT_FAILURE);
}

method_t *CFD_Allocate_Engine_Method()
{
    method_t *method = (method_t *)malloc(sizeof(method_t));
    if (method != NULL)
    {
        method->state = CFD_Allocate_Engine_Method_State();
        method->index = CFD_Allocate_Engine_Method_Index();
        if (method->state != NULL &&
            method->index != NULL)
        {
            return method;
        }
    }

    log_fatal("Error: Could not allocate memory for engine->method");
    exit(EXIT_FAILURE);
}

// number_of_sweeps_t *CFD_Allocate_Engine_Method_NumberOfSweeps()
// {
//     number_of_sweeps_t *number_of_sweeps = (number_of_sweeps_t *)malloc(sizeof(number_of_sweeps_t));
//     if (number_of_sweeps != NULL)
//     {
//         return number_of_sweeps;
//     }

//     log_fatal("Error: Could not allocate memory for engine->method->number_of_sweeps");
//     exit(EXIT_FAILURE);
// }

method_state_t *CFD_Allocate_Engine_Method_State()
{
    method_state_t *state = (method_state_t *)malloc(sizeof(method_state_t));
    if (state != NULL)
    {
        return state;
    }

    log_fatal("Error: Could not allocate memory for engine->method->state");
    exit(EXIT_FAILURE);
}

method_index_t *CFD_Allocate_Engine_Method_Index()
{
    method_index_t *index = (method_index_t *)malloc(sizeof(method_index_t));
    if (index != NULL)
    {
        return index;
    }

    log_fatal("Error: Could not allocate memory for engine->method->index");
    exit(EXIT_FAILURE);
}

schemes_t *CFD_Allocate_Engine_Schemes()
{
    schemes_t *schemes = (schemes_t *)malloc(sizeof(schemes_t));
    if (schemes != NULL)
    {
        schemes->convection = CFD_Allocate_Engine_Schemes_Convection();
        schemes->diffusion = CFD_Allocate_Engine_Schemes_Diffusion();
        if (schemes->convection != NULL &&
            schemes->diffusion != NULL)
        {
            return schemes;
        }
    }

    log_fatal("Error: Could not allocate memory for engine->schemes");
    exit(EXIT_FAILURE);
}

scheme_convection_t *CFD_Allocate_Engine_Schemes_Convection()
{
    scheme_convection_t *convection = (scheme_convection_t *)malloc(sizeof(scheme_convection_t));
    if (convection != NULL)
    {
        convection->coefficients = VEC_Init(EENN + 1);
        convection->F = CFD_Allocate_Engine_Schemes_Convection_F();
        if (convection->coefficients != NULL &&
            convection->F != NULL)
        {
            return convection;
        }
    }

    log_fatal("Error: Could not allocate memory for engine->schemes->convection");
    exit(EXIT_FAILURE);
}

F_coefficients_t *CFD_Allocate_Engine_Schemes_Convection_F()
{
    F_coefficients_t *F = (F_coefficients_t *)malloc(sizeof(F_coefficients_t));
    if (F != NULL)
    {
        return F;
    }

    log_fatal("Error: Could not allocate memory for engine->schemes->convection->F");
    exit(EXIT_FAILURE);
}

scheme_diffusion_t *CFD_Allocate_Engine_Schemes_Diffusion()
{
    scheme_diffusion_t *diffusion = (scheme_diffusion_t *)malloc(sizeof(scheme_diffusion_t));
    if (diffusion != NULL)
    {
        diffusion->coefficients = VEC_Init(EENN + 1);
        return diffusion;
    }

    log_fatal("Error: Could not allocate memory for engine->schemes->diffusion");
    exit(EXIT_FAILURE);
}

void CFD_Free_Engine(engine_t *engine)
{
    if (engine != NULL)
    {
        CFD_Free_Engine_Mesh(engine->mesh);
        CFD_Free_Engine_Method(engine->method);
        CFD_Free_Engine_Schemes(engine->schemes);
        free(engine);
    }
}

void CFD_Free_Engine_Mesh(mesh_t *mesh)
{
    if (mesh != NULL)
    {
        CFD_Free_Engine_Mesh_Nodes(mesh->nodes);
        CFD_Free_Engine_Mesh_Element(mesh->element);
        CFD_Free_Engine_Mesh_Data(mesh->data);
        free(mesh);
    }
}

void CFD_Free_Engine_Method(method_t *method)
{
    if (method != NULL)
    {
        CFD_Free_Engine_Method_State(method->state);
        CFD_Free_Engine_Method_Index(method->index);
        free(method);
    }
}

void CFD_Free_Engine_Schemes(schemes_t *schemes)
{
    if (schemes != NULL)
    {
        CFD_Free_Engine_Schemes_Convection(schemes->convection);
        CFD_Free_Engine_Schemes_Diffusion(schemes->diffusion);
        free(schemes);
    }
}

void CFD_Free_Engine_Mesh_Nodes(mesh_nodes_t *nodes)
{
    if (nodes != NULL)
    {
        free(nodes);
    }
}

void CFD_Free_Engine_Mesh_Element(mesh_element_t *element)
{
    if (element != NULL)
    {
        CFD_Free_Engine_Mesh_Element_Size(element->size);
        free(element);
    }
}

void CFD_Free_Engine_Mesh_Data(mesh_data_t *data)
{
    if (data != NULL)
    {
        free(data);
    }
}

// void CFD_Free_Engine_Method_UnderRelaxationFactors(under_relaxation_factors_t *under_relaxation_factors)
// {
//     if (under_relaxation_factors != NULL)
//     {
//         free(under_relaxation_factors);
//     }
// }

void CFD_Free_Engine_Method_State(method_state_t *state)
{
    if (state != NULL)
    {
        free(state);
    }
}

void CFD_Free_Engine_Method_Index(method_index_t *index)
{
    if (index != NULL)
    {
        free(index);
    }
}

void CFD_Free_Engine_Mesh_Element_Size(element_size_t *size)
{
    if (size != NULL)
    {
        free(size);
    }
}

void CFD_Free_Engine_Schemes_Convection(scheme_convection_t *convection)
{
    if (convection != NULL)
    {
        CFD_Free_Engine_Schemes_Convection_F(convection->F);
        free(convection);
    }
}

void CFD_Free_Engine_Schemes_Convection_F(F_coefficients_t *F)
{
    if (F != NULL)
    {
        free(F);
    }
}

void CFD_Free_Engine_Schemes_Diffusion(scheme_diffusion_t *diffusion)
{
    if (diffusion != NULL)
    {
        free(diffusion);
    }
}
