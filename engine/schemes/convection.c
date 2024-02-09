#include "convection.h"

#include "../../CFD.h"

void CFD_Setup_Convection(CFD_t *cfd)
{
    switch (cfd->engine->schemes->convection->type)
    {
    case UDS:
        cfd->engine->schemes->convection->callable = engineSchemeConvectionUDS;
        break;
    case HYBRID:
        cfd->engine->schemes->convection->callable = engineSchemeConvectionHYBRID;
        break;
    case QUICK:
        cfd->engine->schemes->convection->callable = engineSchemeConvectionQUICK;
        break;
    }
}

A_coefficients_convection_t engineSchemeConvectionUDS(CFD_t *cfd)
{
    A_coefficients_convection_t Ap;
    Ap.u[0] = 0.0;
    Ap.u[1] = 0.0;
    Ap.v[0] = 0.0;
    Ap.v[1] = 0.0;
    return Ap;
}

A_coefficients_convection_t engineSchemeConvectionHYBRID(CFD_t *cfd)
{
    A_coefficients_convection_t Ap;
    Ap.u[0] = 0.0;
    Ap.u[1] = 0.0;
    Ap.v[0] = 0.0;
    Ap.v[1] = 0.0;
    return Ap;
}

A_coefficients_convection_t engineSchemeConvectionQUICK(CFD_t *cfd)
{
    A_coefficients_convection_t Ap;
    Ap.u[0] = 0.0;
    Ap.u[1] = 0.0;
    Ap.v[0] = 0.0;
    Ap.v[1] = 0.0;
    return Ap;
}