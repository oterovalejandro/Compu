#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "generador.h"

double f(double x){
	return 2*sqrt(1-x*x);
}

int main(){
	long long i,N; 
	
	double anchura;
	
	double tini, tend;
	double suma=0;
	double integral;
	
	double x,a,b;
	
	int j,ncalc; 
	double promedio=0;
	
	FILE *salida;
	
	printf("Numero de ensayos: \n");
	scanf ("%lld",&N);
	 
	printf("Intervalo de integracion [a,b]: \n");
	scanf ("%lf %lf",&a,&b);
	
	printf("Numero de veces que se calculara la integral: \n");
	scanf("%d",&ncalc);
	
	anchura=(b-a)/(double)N;
	
	salida=fopen("integral1D.dat","w");
	
	srand48(seed()); //semilla
	
	tini = timeinseconds();
	
	for (j=1;j<=ncalc;j++){
		suma =0 ;
		for (i=1;i<=N;i++){
			x=scalerandom(drand48(),a,b);
			suma = suma + f(x);
		}
		integral=suma*anchura;
		fprintf(salida,"%d %lf \n",j,integral);
		promedio=promedio+integral;
	}
	
	promedio = promedio/(double)ncalc;
	
	tend = timeinseconds();
	
	fclose(salida);
	
	printf("El valor promedio de la integral calculada es %lf \n",promedio);
	printf("El tiempo de calculo ha sido %lf s \n",tend-tini);
	
return 0;
}
		
