#include <stdio.h>
#include <math.h>

#define NX 100
#define NY 100

// define # of grid points
#define NI 80
#define NJ 80
#define RE 100

// define convergence criterion
#define SORMAX 0.0001

// define relaxation factors
#define URFU 0.5
#define URFV 0.5

// define maximum iterations
#define MAXIT 1000

void grid(float X[NX][NY], float Y[NX][NY]);
void init(float U[NX][NY], float V[NX][NY], float P[NX][NY]);
void SCGS(float U[NX][NY], float V[NX][NY], float P[NX][NY]);
void VANKA(double a11, double a15, double a22, double a25, double a33, double a35, double a44, double a45,
           double a51, double a52, double a53, double a54,
           double b1, double b2, double b3, double b4, double b5,
           float *x1, float *x2, float *x3, float *x4, float *x5);
void BCMOD(float U[NX][NY], float V[NX][NY]);

int main(int argc, char *argv[])
{
    float X[NX][NY], Y[NX][NY];
    float U[NX][NY], V[NX][NY], P[NX][NY];
    float UC[NX][NY], VC[NX][NY];

    grid(X, Y);
    init(U, V, P);
    SCGS(U, V, P);

    for (int I = 0; I < NI; I++)
    {
        for (int J = 0; J < NJ; J++)
        {
            UC[I][J] = 0.5 * (U[I][J] + U[I - 1][J]);
            VC[I][J] = 0.5 * (V[I][J] + V[I][J - 1]);
        }
    }

    return 0;
}

void grid(float X[NX][NY], float Y[NX][NY])
{
    // uniform grid in X and Y
    float DX = 1.0 / NI;
    float DY = 1.0 / NJ;

    int Ihalo = 2;
    int Jhalo = 2;

    int I, J;

    for (I = -Ihalo; I < NI + Ihalo; I++)
    {
        for (J = -Jhalo; J < NJ + Jhalo; J++)
        {
            X[I + Ihalo][J + Jhalo] = I * DX;
            Y[I + Ihalo][J + Jhalo] = J * DY;
        }
    }
}

void init(float U[NX][NY], float V[NX][NY], float P[NX][NY])
{
    int Ihalo = 2;
    int Jhalo = 2;

    int I, J;

    for (I = -Ihalo; I < NI + Ihalo; I++)
    {
        for (J = -Jhalo; J < NJ + Jhalo; J++)
        {
            U[I + Ihalo][J + Jhalo] = 0.0;
            V[I + Ihalo][J + Jhalo] = 0.0;
            P[I + Ihalo][J + Jhalo] = 0.0;
        }
    }
}

void SCGS(float U[NX][NY], float V[NX][NY], float P[NX][NY])
{
    double AEU[2], AWU[2], ANU[2], ASU[2], APU[2], BU[2];
    double AEV[2], AWV[2], ANV[2], ASV[2], APV[2], BV[2];
    double a11, a15, a22, a25, a33, a35, a44, a45;
    double a51, a52, a53, a54;
    double b1, b2, b3, b4, b5;
    float *x1, *x2, *x3, *x4, *x5;

    for (int IT = 1; IT < MAXIT; IT++)
    {
        int RESORU = 0;
        int RESORV = 0;
        int RESORM = 0;

        for (int J = 0; J < NJ; J++)
        {
            for (int I = 0; I < NI; I++)
            {
                AEU[1] = 0;
                AWU[1] = 0;
                ANU[1] = 0;
                ASU[1] = 0;
                APU[1] = 0;
                BU[1] = 0;

                AEU[0] = 0;
                AWU[0] = 0;
                ANU[0] = 0;
                ASU[0] = 0;
                APU[0] = 0;
                BU[0] = 0;

                AEV[1] = 0;
                AWV[1] = 0;
                ANV[1] = 0;
                ASV[1] = 0;
                APV[1] = 0;
                BV[1] = 0;

                AEV[0] = 0;
                AWV[0] = 0;
                ANV[0] = 0;
                ASV[0] = 0;
                APV[0] = 0;
                BV[0] = 0;

                a11 = 0;
                a15 = 0;
                a22 = 0;
                a25 = 0;
                a33 = 0;
                a35 = 0;
                a44 = 0;
                a45 = 0;

                a11 = a11 / URFU;
                a22 = a22 / URFU;
                a33 = a33 / URFV;
                a44 = a44 / URFV;

                a51 = 0;
                a52 = 0;
                a53 = 0;
                a54 = 0;

                b1 = 0;
                b2 = 0;
                b3 = 0;
                b4 = 0;
                b5 = 0;

                /*
                    Boundary conditions for u', v'
                */

                VANKA(a11, a15, a22, a25, a33, a35, a44, a45, a51, a52, a53, a54,
                      b1, b2, b3, b4, b5,
                      x1, x2, x3, x4, x5);

                // Correcting U, V and P
                U[I - 1][J] = U[I - 1][J] + *x1;
                U[I][J] = U[I][J] + *x2;
                V[I][J - 1] = V[I][J - 1] + *x3;
                V[I][J] = V[I][J] + *x4;
                P[I][J] = P[I][J] + *x5;

                // Calculate residuals at centroid of P-CV
                RESORU = RESORU + (abs(b1) + abs(b2)) / 2;
                RESORV = RESORV + (abs(b3) + abs(b4)) / 2;
                RESORM = RESORM + abs(b5);
            }
        }

        // Specify boundary conditions for U and V
        BCMOD(U, V);

        /*
            Output progress every 100 iterations
            IF(MOD(IT,100).EQ.0) THEN
            WRITE(6,51)IT,RESORU,RESORV,RESORM
            END IF
        */

        if (fmax(RESORU, fmax(RESORV, RESORM)) < SORMAX &&
            IT > 1)
        {
            break;
        }
    }
}

void VANKA(double a11, double a15, double a22, double a25, double a33, double a35, double a44, double a45,
           double a51, double a52, double a53, double a54,
           double b1, double b2, double b3, double b4, double b5,
           float *x1, float *x2, float *x3, float *x4, float *x5)
{
    double r1, r2, r3, r4, DEN;

    r1 = a51 / a11;
    r2 = a52 / a22;
    r3 = a53 / a33;
    r4 = a54 / a44;
    DEN = r1 * a15 + r2 * a25 + r3 * a35 + r4 * a45;
    *x5 = (float)(r1 * b1 + r2 * b2 + r3 * b3 + r4 * b4 - b5) / DEN;
    *x1 = (float)(b1 - a15 * (*x5)) / a11;
    *x2 = (float)(b2 - a25 * (*x5)) / a22;
    *x3 = (float)(b3 - a35 * (*x5)) / a33;
    *x4 = (float)(b4 - a45 * (*x5)) / a44;
}

void BCMOD(float U[NX][NY], float V[NX][NY])
{
    // int I, J;

    // for (I = 0; I < NI; I++)
    // {
    //     U[I][0] = 0.0;
    //     U[I][NJ] = 0.0;
    //     V[I][0] = 0.0;
    //     V[I][NJ] = 0.0;
    // }

    // for (J = 0; J < NJ; J++)
    // {
    //     U[0][J] = 0.0;
    //     U[NI][J] = 0.0;
    //     V[0][J] = 0.0;
    //     V[NI][J] = 0.0;
    // }
}