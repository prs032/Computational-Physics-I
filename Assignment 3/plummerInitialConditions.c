#include<stdio.h>
#include<math.h>
#include<stdlib.h>
#include<time.h>
#include<limits.h>
#include "mt19937.h"

#define pi 3.14159
#define G 4.498279e-3
#define M 1e11
#define R 1000
#define N 10000

double* mtRandNum(double *X);
unsigned time_seed();

int main(argc, argv)
int argc;
char *argv[];
{
    int i, j = 0;
    /* Mass of each particle */
    double m = M/N;
    /* Random Numbers */
    double X[7*N], Q;
    /* position & velocity coordinates */
    double x, y, z, u, v, w, V, Ve;
    /* radius of each particle */
    double r;

    FILE *outFile;
    outFile = fopen("plummerInitCoordinates.dat", "w");

    for(i=0; i<N; i++)
    {
    	//j=0;
    	mtRandNum(X);

		r = 1/sqrt((1/cbrt(pow(X[j+0],2))) - 1);
		printf("\nr: %10.8f \n", r);

		/* Generating position coordinates */
		z = (1-2*X[j+1])*r;
		x = sqrt(pow(r,2) - pow(z,2)) * cos(2*pi*X[j+2]);
		y = sqrt(pow(r,2) - pow(z,2)) * sin(2*pi*X[j+2]);

		Q = pow(X[j+3],2)*pow(sqrt((1-pow(X[j+3],2))),7);

		/* Generating velocity coordinates */
		do
		{
			Ve = sqrt(2) * 1/sqrt(sqrt((1 + pow(r,2))));
			V = Ve * X[j+3];
			printf("V: %lf \n", V);
			j++;
		}while(0.1*X[j+4] < Q);

		w = V * (1 - 2*X[j+5]);
		u = sqrt(pow(V,2) - pow(w,2)) * cos(2*pi*X[j+6]);
		v = sqrt(pow(V,2) - pow(w,2)) * sin(2*pi*X[j+6]);

		double VelMul = sqrt((G*M)/R);

		/* Scaling the co-ordinates */
		x = x * R;
		y = y * R;
		z = z * R;

		u = u * VelMul;
		v = v * VelMul;
		w = w * VelMul;

		printf("x, y, z: %f %f %f \n", x, y, z);
		printf("u, v, w: %f %f %f \n", u, v, w);

		fprintf(outFile, "%10.3f \t %10.3f \t %10.3f \t %10.3f \t %10.3f \t %10.3f \n", x, y, z, u, v, w);
    }
	return 1;
}

double* mtRandNum(double *X)
{
    int i;
    init_genrand(time_seed());
    printf("\n 7 outputs of genrand_real3()\n");
    for (i=0; i<10; i++) {
      X[i] = genrand_real1();
      printf("X[%d]: %10.3f \t", i, X[i]);
      if (i%4==3) printf("\n");
    }
    return X;
}

unsigned time_seed()
{
	size_t i;
    time_t now = time(0);
    unsigned char *p = (unsigned char *)&now;
    unsigned seed = 0;

    for (i = 0; i < sizeof now; i++)
    {
        seed = seed * (UCHAR_MAX + 2U) + p[i];
    }

    return seed;
}
