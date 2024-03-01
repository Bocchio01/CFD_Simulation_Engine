#ifndef SCGS_BC_H
#define SCGS_BC_H

typedef struct CFD_t CFD_t;
typedef struct SCGS_t SCGS_t;

void CFD_SCGS_BC_NoSlip_Normal(CFD_t *cfd, SCGS_t *scgs);
void CFD_SCGS_BC_NoSlip_Tangetial(CFD_t *cfd);

#endif