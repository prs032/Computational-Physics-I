/*
 * SaturnRings.C: program to simulate ring of 10 objects around Saturn.
 */

#include <math.h>
#include <stdio.h>

#define ROW 10
#define COL 4

#define pi 3.14159
#define dt 0.001
#define N 10
#define gamma 2
#define Mass_saturn 5.686e26

double GM = 4*pi*pi*0.00028572864;
double Mass_body = (gamma*Mass_saturn)/pow(N,3);

double body_x[N];
double body_y[N];
	
double body_vx[N];
double body_vy[N];

double radius[N];

double force_x[N];
double force_y[N];

void velocityVerlet(int);
void acceleration(int);

void main(argc, argv)
int argc;
char *argv[];
{
	int i,j,row;
	double t_now = 0;				// setting initial time
	
	FILE *inFile;
	inFile = fopen("init.dat", "r");
 	if (inFile== NULL)
    {
    	printf("can not open init file \n");
    	return 1;
    }
    else{
   	for(row=0; row<ROW; row++)
		{
    		fscanf(inFile, "%lf", &body_x[row]);
    		fscanf(inFile, "%lf", &body_y[row]);
    		fscanf(inFile, "%lf", &body_vx[row]);
    		fscanf(inFile, "%lf", &body_vy[row]);
    		printf("%lf %lf %lf %lf \n",body_x[row], body_y[row], body_vx[row], body_vy[row]);
    	}
    }
    
 	for(i=0; i<N; i++)
	{
		body_vx[i] = body_vx[i]*sqrt(1-0.25);
		body_vy[i] = body_vy[i]*sqrt(1-0.25);
		radius[i] = sqrt(pow(body_x[i],2) + pow(body_y[i],2));
	}
	
	FILE *outFile;									// creating file object
	outFile = fopen("saturnStableRing_New.dat", "w");		// opening file stream
 
	while (t_now < 70)
	{	
		for(i=0; i<N; i++)
		{
			velocityVerlet(i);
			fprintf(outFile,"%f \t %f \t", body_x[i], body_y[i]);
		}
		fprintf(outFile,"\n");
		t_now += dt;				// update value of time
	} 
	fclose(outFile);				// closing file stream
}

void velocityVerlet(int i)
{
	/* Leapforg Algorithm for Step Integration */
	acceleration(i);
	body_vx[i] = body_vx[i] - force_x[i];
	body_vy[i] = body_vy[i] - force_y[i];
		
	body_x[i] = body_x[i] + (body_vx[i] * dt);
	body_y[i] = body_y[i] + (body_vy[i] * dt);
	
	acceleration(i);		
	body_vx[i] = body_vx[i] - force_x[i];
	body_vy[i] = body_vy[i] - force_y[i];
}

void acceleration(int body)
{
	int k;
	force_x[body] = (0.5*(GM*body_x[body]*dt))/pow(radius[body],3);
	force_y[body] = (0.5*(GM*body_y[body]*dt))/pow(radius[body],3);
	for(k=0; k<N; k++)
	{
		double x_diff = body_x[body]-body_x[k];
		double y_diff = body_y[body]-body_y[k];
		double r_diff = sqrt(pow(x_diff,2) + pow(y_diff,2));
		if(k!=body)
		{
			force_x[body] += 0.5*(GM*(Mass_body/Mass_saturn)*(x_diff*dt)/pow(r_diff,3));
			force_y[body] += 0.5*(GM*(Mass_body/Mass_saturn)*(y_diff*dt)/pow(r_diff,3));
		}
	}
}