/*
 * LeapFrog.C: program to simulate planetary orbits using leapfrog algorithm.
 */

#include <math.h>
#include <stdio.h>

#define pi 3.14159
#define dt 0.001

void leapFrogIntegrator(double*, double*, double*,
	double*, double*, double*, double);

void main(argc, argv)
int argc;
char *argv[];
{
	//const double pi = 3.14159;			// value of pi
	double GM = 4*pi*pi;				// G * Mass of Sun
	
	double a = 1.00004;					// semi-major axis
	double e = 0.016684;				// eccentricity
	
	double planet_x = a*(1+e);			// position x co-ordinate
	double planet_y = 0;				// position y co-ordinate
	double planet_z = 0;				// position z co-ordinate
	
	double planet_vx = 0;				// velocity x co-ordinate
	double planet_vy = sqrt((GM*(1-e))/planet_x);	// velocity y co-ordinate
	double planet_vz = 0;				// velocity z co-ordinate

	//double dt = 0.00001;				// timestep for integration
		
	double t_now = 0;				// setting initial time
	
	FILE *outFile;					// creating file object
	outFile = fopen("earth.dat", "a+");		// opening file stream
 
	while (t_now < 1)
	{	
		/* Leapforg Algorithm for Step Integration */
		leapFrogIntegrator(&planet_x, &planet_y, &planet_z,
	&planet_vx, &planet_vy, &planet_vz, GM);
		
		fprintf(outFile, "%f, %f, %f \n", planet_x, planet_y, planet_z);
		
		t_now += dt;				// update value of time
	} 
	fclose(outFile);				// closing file stream
}

void leapFrogIntegrator(double* planet_x, double* planet_y, double* planet_z,
	double* planet_vx, double* planet_vy, double* planet_vz, double GM)
	{
		double r = sqrt(pow(*planet_x,2) + pow(*planet_y,2) + pow(*planet_z,2));
		
		*planet_vx = *planet_vx - (0.5 * (GM*(*planet_x)*dt)/pow(r,3));
		*planet_vy = *planet_vy - (0.5 * (GM*(*planet_y)*dt)/pow(r,3));
		*planet_vz = *planet_vz - (0.5 * (GM*(*planet_z)*dt)/pow(r,3));
		
		*planet_x += (*planet_vx * dt);
		*planet_y += (*planet_vy * dt);
		*planet_z += (*planet_vz * dt);
		
		*planet_vx = *planet_vx - (0.5 * (GM*(*planet_x)*dt)/pow(r,3));
		*planet_vy = *planet_vy - (0.5 * (GM*(*planet_y)*dt)/pow(r,3));
		*planet_vz = *planet_vz - (0.5 * (GM*(*planet_z)*dt)/pow(r,3));
	}
	
	/* Code for directly calling gnuplot from C program.
	
	FILE *gnuplot = popen("gnuplot", "w");
	fprintf(gnuplot, "plot '-'\n");
	for (i = 0; i < count; i++)
    	fprintf(gnuplot, "%g %g\n", x[i], y[i]);
	fprintf(gnuplot, "e\n");
	fflush(gnuplot); 
	
	*/
