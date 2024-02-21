#include "convection.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "../../CFD.h"
#include "../../utils/cLOG/cLOG.h"
#include "../../utils/cALGEBRA/cVEC.h"
#include "schemes.h"

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

double getState(CFD_t *cfd, phi_t phi, int i, int j)
{

    uint8_t rows = cfd->engine->mesh->data->x->rows;
    uint8_t cols = cfd->engine->mesh->data->x->cols;

    switch (phi)
    {
    case u:
        return (i >= 0 && j >= 0 && i < cols && j < rows) ? cfd->engine->method->state->u->data[j][i] : 0.0;

    case v:
        return (i >= 0 && j >= 0 && i < cols && j < rows) ? cfd->engine->method->state->v->data[j][i] : 0.0;

    case p:
        return (i >= 0 && j >= 0 && i < cols && j < rows) ? cfd->engine->method->state->p->data[j][i] : 0.0;

    default:
        log_fatal("Error: getState phi not found");
        exit(EXIT_FAILURE);
        break;
    }
}

F_coefficients_t engineSchemeConvectionF(CFD_t *cfd, int i, int j, phi_t phi)
{
    F_coefficients_t F;

    double uPP = getState(cfd, u, i + 0, j + 0);
    double vPP = getState(cfd, v, i + 0, j + 0);

    double uPN = getState(cfd, u, i + 0, j + 1);
    double vPN = getState(cfd, v, i + 0, j + 1);

    double uEN = getState(cfd, u, i + 1, j + 1);
    double vEN = getState(cfd, v, i + 1, j + 1);

    double uEP = getState(cfd, u, i + 1, j + 0);
    double vEP = getState(cfd, v, i + 1, j + 0);

    double uES = getState(cfd, u, i + 1, j - 1);
    double vES = getState(cfd, v, i + 1, j - 1);

    double uPS = getState(cfd, u, i + 0, j - 1);
    double vPS = getState(cfd, v, i + 0, j - 1);

    double uWS = getState(cfd, u, i - 1, j - 1);
    double vWS = getState(cfd, v, i - 1, j - 1);

    double uWP = getState(cfd, u, i - 1, j + 0);
    double vWP = getState(cfd, v, i - 1, j + 0);

    double uWN = getState(cfd, u, i - 1, j + 1);
    double vWN = getState(cfd, v, i - 1, j + 1);

    double dx = cfd->engine->mesh->element->size->dx;
    double dy = cfd->engine->mesh->element->size->dy;

    switch (phi)
    {
    case u:

        F.w = 1.0 / 2.0 * (uWP + uPP) * dy;
        F.e = 1.0 / 2.0 * (uPP + uEP) * dy;
        F.s = 1.0 / 2.0 * (vPS + vES) * dx;
        F.n = 1.0 / 2.0 * (vPP + vEP) * dx;

        break;

    case v:

        F.w = 1.0 / 2.0 * (uWP + uWN) * dy;
        F.e = 1.0 / 2.0 * (uPP + uPN) * dy;
        F.s = 1.0 / 2.0 * (vPS + vPP) * dx;
        F.n = 1.0 / 2.0 * (vPP + vPN) * dx;

        break;

    default:
        log_fatal("Error: engineSchemeConvectionF phi not found");
        exit(EXIT_FAILURE);
        break;
    }

    return F;
}

cVEC_t *engineSchemeConvectionUDS(CFD_t *cfd, uint8_t i, uint8_t j, phi_t phi)
{

    F_coefficients_t F = engineSchemeConvectionF(cfd, i, j, phi);
    cVEC_t *Ap = VEC_Init(EENN + 1);

    Ap->data[WWSS] = 0.0;
    Ap->data[WWS] = 0.0;
    Ap->data[WWP] = 0.0;
    Ap->data[WWN] = 0.0;
    Ap->data[WWNN] = 0.0;
    Ap->data[WSS] = 0.0;
    Ap->data[WS] = 0.0;
    Ap->data[WP] = fmax(0.0, F.w);
    Ap->data[WN] = 0.0;
    Ap->data[WNN] = 0.0;
    Ap->data[PSS] = 0.0;
    Ap->data[PS] = fmax(0.0, F.s);
    Ap->data[PP] = fmax(0.0, F.e) + fmax(0.0, F.n) - fmin(0.0, F.s) - fmin(0.0, F.w);
    Ap->data[PN] = -fmin(0.0, F.n);
    Ap->data[PNN] = 0.0;
    Ap->data[ESS] = 0.0;
    Ap->data[ES] = 0.0;
    Ap->data[EP] = -fmin(0.0, F.e);
    Ap->data[EN] = 0.0;
    Ap->data[ENN] = 0.0;
    Ap->data[EESS] = 0.0;
    Ap->data[EES] = 0.0;
    Ap->data[EEP] = 0.0;
    Ap->data[EEN] = 0.0;
    Ap->data[EENN] = 0.0;

    return Ap;
}

cVEC_t *engineSchemeConvectionCDS(CFD_t *cfd, uint8_t i, uint8_t j, phi_t phi)
{
    F_coefficients_t F = engineSchemeConvectionF(cfd, i, j, phi);
    cVEC_t *Ap = VEC_Init(EENN + 1);

    log_fatal("CDS not implemented yet");
    exit(EXIT_FAILURE);

    return Ap;
}

cVEC_t *engineSchemeConvectionQUICK(CFD_t *cfd, uint8_t i, uint8_t j, phi_t phi)
{
    F_coefficients_t F = engineSchemeConvectionF(cfd, i, j, phi);
    cVEC_t *Ap = VEC_Init(EENN + 1);

    Ap->data[WWSS] = 0.0;
    Ap->data[WWS] = 0.0;
    Ap->data[WWP] = -1.0 / 8.0 * fmax(0.0, F.w);
    Ap->data[WWN] = 0.0;
    Ap->data[WWNN] = 0.0;
    Ap->data[WSS] = 0.0;
    Ap->data[WS] = 0.0;
    Ap->data[WP] = 1.0 / 8.0 * fmax(0.0, F.e) + 3.0 / 4.0 * fmax(0.0, F.w) + 3.0 / 8.0 * fmin(0.0, F.w);
    Ap->data[WN] = 0.0;
    Ap->data[WNN] = 0.0;
    Ap->data[PSS] = -1.0 / 8.0 * fmax(0.0, F.s);
    Ap->data[PS] = 1.0 / 8.0 * fmax(0.0, F.n) + 3.0 / 4.0 * fmax(0.0, F.s) + 3.0 / 8.0 * fmin(0.0, F.s);
    Ap->data[PP] = 3.0 / 4.0 * fmax(0.0, F.e) + 3.0 / 8.0 * fmin(0.0, F.e) + 3.0 / 4.0 * fmax(0.0, F.n) + 3.0 / 8.0 * fmin(0.0, F.n) - 3.0 / 8.0 * fmax(0.0, F.s) - 3.0 / 4.0 * fmin(0.0, F.s) - 3.0 / 8.0 * fmax(0.0, F.w) - 3.0 / 4.0 * fmin(0.0, F.w);
    Ap->data[PN] = 1.0 / 8.0 * (-3.0) * fmax(0.0, F.n) - 3.0 / 4.0 * fmin(0.0, F.n) - 1.0 / 8.0 * fmin(0.0, F.s);
    Ap->data[PNN] = 1.0 / 8.0 * fmin(0.0, F.n);
    Ap->data[ESS] = 0.0;
    Ap->data[ES] = 0.0;
    Ap->data[EP] = 1.0 / 8.0 * (-3.0) * fmax(0.0, F.e) - 3.0 / 4.0 * fmin(0.0, F.e) - 1.0 / 8.0 * fmin(0.0, F.w);
    Ap->data[EN] = 0.0;
    Ap->data[ENN] = 0.0;
    Ap->data[EESS] = 0.0;
    Ap->data[EES] = 0.0;
    Ap->data[EEP] = 1.0 / 8.0 * fmin(0.0, F.e);
    Ap->data[EEN] = 0.0;
    Ap->data[EENN] = 0.0;

    return Ap;
}

cVEC_t *engineSchemeConvectionHYBRID(CFD_t *cfd, uint8_t i, uint8_t j, phi_t phi)
{
    F_coefficients_t F = engineSchemeConvectionF(cfd, i, j, phi);
    cVEC_t *Ap = VEC_Init(EENN + 1);

    log_fatal("HYBRID not implemented yet");
    exit(EXIT_FAILURE);

    return Ap;
}