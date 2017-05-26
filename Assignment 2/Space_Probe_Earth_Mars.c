/*
 * LeapFrog.C: program to simulate & calculate the transfer orbit of the NASA Odyssey spacecraft to Mars.
 */

#include <math.h>
#include <stdio.h>

void main(argc, argv)
int argc;
char *argv[];
{
	int i;
	double planet_x, planet_y, planet_vx, planet_vy;
	
	// value of pi
	const double pi = 3.14159;
	// G * Mass of Sun
	double GM = 4*pi*pi;
	
	//Semi-major axis & eccentricities
	double a_earth = 0.999987;				
	double e_earth = 0.016684;
	
	double a_mars = 1.523705;				
	double e_mars = 0.093404;
	
	double a_probe = (a_earth + a_mars)/2;
	double e_probe = 1 - (a_earth/a_probe);		
	
	//Earth
	double earth_x = a_earth*(1+e_earth);
	double earth_y = 0;	
	
	double earth_vx = 0;
	double earth_vy = sqrt(GM/earth_x);
	
	//Mars
	double mars_x = 1.5 * cos(44*(pi/180));
	double mars_y = 1.5 *sin(44*(pi/180));	
	
	double mars_vx = -1 * sqrt(GM/1.5) * sin(44*(pi/180));
	double mars_vy = sqrt(GM/1.5) * cos(44*(pi/180));
	
	//Probe
	double probe_x = a_earth*(1+e_earth);
	double probe_y = 0;	
	
	double probe_vx = 0;
	double probe_vy = earth_vy + 0.57;
	
	//timestep for integration
	double dt = 0.0001;	
	
	//Orbital Period
	double t_period = 0;
	
	FILE *outFile;
 
	for(i=0; i<3; i++)
	{
		//setting initial time
		double t_now = 0;
		if(i==0)
		{
			planet_x = earth_x;
			planet_y = earth_y;
			planet_vx = earth_vx;
			planet_vy = earth_vy;
			t_period = 2;
			outFile = fopen("earth_transferOrbit.dat", "w");
		}
		else if(i==1){
			planet_x = mars_x;
			planet_y = mars_y;
			planet_vx = mars_vx;
			planet_vy = mars_vy;
			t_period = 1.88;
			outFile = fopen("mars_transferOrbit.dat", "w");
		}
		else{
			planet_x = probe_x;
			planet_y = probe_y;
			planet_vx = probe_vx;
			planet_vy = probe_vy;
			t_period = 0.709;
			outFile = fopen("probe_transferOrbit.dat", "w");
		}
		while (t_now < t_period)
		{
			double r = sqrt(pow(planet_x,2) + pow(planet_y,2));
			
			/* Leapforg Algorithm for Step Integration */
			planet_vx = planet_vx - (0.5 * (GM*planet_x*dt)/pow(r,3));
			planet_vy = planet_vy - (0.5 * (GM*planet_y*dt)/pow(r,3));
			
			planet_x += (planet_vx * dt);
			planet_y += (planet_vy * dt);
			
			planet_vx = planet_vx - (0.5 * (GM*planet_x*dt)/pow(r,3));
			planet_vy = planet_vy - (0.5 * (GM*planet_y*dt)/pow(r,3));
			
			//if(fmod(t_now,10000))
			fprintf(outFile, "%f, %f \n", planet_x, planet_y);
			
			t_now += dt;				// update value of time
		}
		fclose(outFile);				// closing file stream
	}
}
