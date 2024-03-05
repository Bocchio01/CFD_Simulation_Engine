#include "schemes.h"

#include "../../CFD.h"

void CFD_Setup_Schemes(CFD_t *cfd)
{
    CFD_Setup_Convection(cfd);
    CFD_Setup_Diffusion(cfd);
}