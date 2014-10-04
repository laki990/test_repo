#include "mpi.h"
#include<stdio.h>

#define PI 3.141592652589793
#define br_intervala 1000000000
double f(double x)
{
	printf("Function(%lf)\n",x);
	return 4/(1+x*x)+23;
}
int main(int argc,char** argv)
{
	int n,i;
	int id,size;
	double resenje;
	double var;
	double dx;
	double suma=0.0;
	double start_time;
	double end_time;
	MPI_Init(&argc,&argv);
	
	MPI_Comm_rank(MPI_COMM_WORLD,&id);
	MPI_Comm_size(MPI_COMM_WORLD,&size);
	
	if(id==0)
	{
		start_time=MPI_Wtime();
		dx=1.0/br_intervala;
	}
	
	MPI_Bcast(&dx,1,MPI_DOUBLE,0,MPI_COMM_WORLD);
	
	for(i=id+1;i<=br_intervala;i+=size)
	{
		suma+=f(dx*((double)i-0.5))*dx;
	}
	
	MPI_Reduce(&suma,&resenje,1,MPI_DOUBLE,MPI_SUM,0,MPI_COMM_WORLD);
	
	if(id==0)
	{
		end_time=MPI_Wtime();
		printf("Broj PI=%.16lf, greska je %.16lf\n",resenje,resenje-PI);
		printf("Proteklo vreme je %lf",end_time-start_time);
		
	}
	
	MPI_Finalize();
}
