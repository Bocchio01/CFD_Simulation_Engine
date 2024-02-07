#include <stdio.h>
#include <stdlib.h>

#include "settings.h"
#include "../solver/schemes/convection.h"
#include "../solver/schemes/diffusion.h"

settings_t *CFD_Settings_Init()
{
    settings_t *settings = (settings_t *)malloc(sizeof(settings_t));
    if (settings == NULL)
    {
        fprintf(stderr, "Error: Could not allocate memory for settings\n");
        exit(EXIT_FAILURE);
    }

    CFD_Settings_Reset(settings);
    return settings;
}

void CFD_Settings_Reset(settings_t *settings)
{
    settings->problem_data = (problem_data_t){
        .uLid = 1.0,
        .domain_dimension = (data_domain_dimension_t){1.0, 1.0},
        .fluid_properties = (data_fluid_properties_t){1.0, 1.0},
    };

    settings->solver = (solver_settings_t){
        .max_iterations = 1000,
        .tolerance = 1e-4,
        .mesh = (setting_mesh_t){
            .type = STAGGERED,
            .size = (mesh_size_t){100, 100},
            .element = (mesh_element_t){
                .type = RECTANGULAR,
                .size = (element_size_t){0.01, 0.01},
            },
        },
        .schemes = (setting_schemes_t){
            .convection = (scheme_convection_t){
                .type = UDS,
                .name = "UDS",
                .callable = solverSchemeConvectionUDS,
            },
            .diffusion = (scheme_diffusion_t){
                .type = SECOND_ORDER,
                .name = "SECOND_ORDER",
                .callable = solverSchemeDiffusion2,
            },
        },
        .under_relaxation_factors = (under_relaxation_factors_t){
            .u = 0.7,
            .v = 0.7,
        },
    };

    settings->results = (results_settings_t){
        .format = CSV,
        .file_name = "results.csv",
        .file_pointer = NULL,
    };
}
