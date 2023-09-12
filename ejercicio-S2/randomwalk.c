#include <stdlib.h> 
#include <stdio.h>
#include <math.h>
#include "generador.h"

int main(){
	long long i,N; 
	
	double tini, tend;
	
	double tita;
	
	double x=0,y=0;
	
	FILE *salida;
	salida = fopen("datos.dat","w");
	
	printf("Numero de interacciones: \n");
	scanf ("%lld",&N);
	
	srand48(seed()); //semilla
	
	tini = timeinseconds();
	
	for(i=1;i<=N;i++){
		tita = scalerandom(drand48(),0,2*M_PI);
		x = x + cos(tita);
		y = y + sin(tita);
		fprintf(salida,"%lf %lf \n",x,y);
	}
	
	tend = timeinseconds();
	
	printf("El valor de la distancia recorida por la particula es: %lf \n",sqrt(pow(x-0,2)+pow(y-0,2)));
	printf("El tiempo de calculo ha sido %lf s \n",tend-tini);
	
	fclose(salida);
	
return 0;
}
		
