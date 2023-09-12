#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "generador.h"

int main(){
	long long i,N; 
	
	int j,nbins;
	double anchura;
	
	double tini, tend;
	
	double x,t,ft;
	 
	printf("Numero de ensayos: \n");
	scanf ("%lld",&N);
	
	printf("Introduce el número de subintervalos de [0,1) para la distribucion: \n");
	scanf("%d",&nbins);
	
	long long hist[nbins]; //array para almacenar el histograma
	
	tini = timeinseconds();
	
	for (j=0;j<nbins;j++){
		hist[j]=0;
	}
	
	anchura=(1.0-0.0)/(double)nbins;
	
	srand48(seed());
	
	for(i=1;i<=N;i++){
		x=drand48();
		j=x/anchura;
		hist[j]=hist[j]+1;
	}
	tend = timeinseconds();
	
	FILE*salida;
	salida=fopen("distribucion.dat","w");
	for(j=0;j<nbins;j++){
		t=j*anchura;
		ft=1.0/anchura*(double)hist[j]/(double)N;
		fprintf(salida,"%lf %le \n",t,ft);
	}
	
	fclose(salida);
	
	printf("Tiempo de calculo: %lf s \n" , tend - tini);

return 0;
}
		
