#ifndef ENGINE_H
#define ENGINE_H

typedef struct CFD_t CFD_t;

#include <stdio.h>
#include <stdint.h>

#include "mesh/mesh.h"
#include "methods/methods.h"
#include "schemes/schemes.h"

typedef struct
{
    mesh_t *mesh;
    method_t *method;
    schemes_t *schemes;
} engine_t;

void CFD_Setup_Engine(CFD_t *cfd);

void CFD_Engine_Solve(CFD_t *cfd);

engine_t *CFD_Allocate_Engine();

mesh_t *CFD_Allocate_Engine_Mesh();

mesh_nodes_t *CFD_Allocate_Engine_Mesh_Nodes();

mesh_element_t *CFD_Allocate_Engine_Mesh_Element();

mesh_data_t *CFD_Allocate_Engine_Mesh_Data();

element_size_t *CFD_Allocate_Engine_Mesh_Element_Size();

method_t *CFD_Allocate_Engine_Method();

under_relaxation_factors_t *CFD_Allocate_Engine_Method_UnderRelaxationFactors();

method_state_t *CFD_Allocate_Engine_Method_State();

schemes_t *CFD_Allocate_Engine_Schemes();

scheme_convection_t *CFD_Allocate_Engine_Schemes_Convection();

scheme_diffusion_t *CFD_Allocate_Engine_Schemes_Diffusion();

void CFD_Free_Engine(engine_t *engine);

void CFD_Free_Engine_Mesh(mesh_t *mesh);

void CFD_Free_Engine_Method(method_t *method);

void CFD_Free_Engine_Schemes(schemes_t *schemes);

void CFD_Free_Engine_Mesh_Nodes(mesh_nodes_t *nodes);

void CFD_Free_Engine_Mesh_Element(mesh_element_t *element);

void CFD_Free_Engine_Mesh_Data(mesh_data_t *data);

void CFD_Free_Engine_Mesh_Element_Size(element_size_t *size);

void CFD_Free_Engine_Method_UnderRelaxationFactors(under_relaxation_factors_t *under_relaxation_factors);

void CFD_Free_Engine_Method_State(method_state_t *state);

void CFD_Free_Engine_Schemes_Convection(scheme_convection_t *convection);

void CFD_Free_Engine_Schemes_Diffusion(scheme_diffusion_t *diffusion);

#endif