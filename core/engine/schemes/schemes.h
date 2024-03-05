#ifndef SCHEMES_H
#define SCHEMES_H

typedef struct CFD_t CFD_t;

#include "convection.h"
#include "diffusion.h"

typedef enum Apu_index_t
{
    WWSS,
    WWS,
    WWP,
    WWN,
    WWNN,
    WSS,
    WS,
    WP,
    WN,
    WNN,
    PSS,
    PS,
    PP,
    PN,
    PNN,
    ESS,
    ES,
    EP,
    EN,
    ENN,
    EESS,
    EES,
    EEP,
    EEN,
    EENN,
} Apu_index_t;

typedef enum phi_t
{
    u,
    v,
    p
} phi_t;

typedef struct
{
    scheme_convection_t *convection;
    scheme_diffusion_t *diffusion;
} schemes_t;

void CFD_Setup_Schemes(CFD_t *cfd);

#endif