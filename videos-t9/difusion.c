#include <stdlib.h> 
#include <stdio.h>
#include <math.h>
#include "generador.h"

int main(){
	
	long long i,imax;
	
	int N,Ni;
	
	double r;
	
	double tini,tend;
	double pid;
	
	double x;
	
	FILE *salida;
	salida = fopen("difu.dat","w");
	
	printf("Introduce el factor de r (entre 0 y 1): \n");
	scanf("%lf",&r);
	printf("Introduce el numero de moleculas iniciales (lado izq): \n");
	scanf("%d",&N);
	Ni=N;
	
	srand48(seed());
	tini = timeinseconds();
	
	imax = 4.6*N/r;
	
	for(i=1;i<=imax;i++){	//bucle temporal
		x = drand48();
		pid=(double)Ni/(double)N*r;
		if(x<pid){
			Ni=Ni-1;
		}
		else {
			if(x<r){
				Ni=Ni+1;
			}
			else {
				Ni=Ni;
			}
		}
		fprintf(salida,"%lf %lf %lf \n",(double)i/1000,(double)Ni/1000,(double)(N-Ni)/1000);
	}
	
	tend = timeinseconds();
	
	fclose(salida);
	
	printf("%d moleculas %lld pasos de tiempo %lf s de calculo \n",N,imax,tend-tini);
	
return 0;
}
	
