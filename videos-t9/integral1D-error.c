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
	double suma=0,suma2=0;
	
	double integral,error;
	
	double x,a,b;
	
	double fx;
	
	int j,ncalc; 
	double promedio=0,promerr=0;
	
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
		suma =0;
		suma2=0;
		for (i=1;i<=N;i++){
			x=scalerandom(drand48(),a,b);
			fx=f(x);
			suma = suma + fx;
			suma2=suma2+fx*fx;
		}
		integral=suma*anchura;
		error=suma2/(double)N-(suma/(double)N)*(suma/(double)N);
		error=(b-a)*sqrt(error/(double)N);
		fprintf(salida,"%d %lf \n",j,integral);
		promedio=promedio+integral;
		promerr=promerr+error;
	}
	
	promedio = promedio/(double)ncalc;
	promerr = promerr/(double)ncalc;
	
	tend = timeinseconds();
	
	fclose(salida);
	
	printf("El valor promedio de la integral calculada es %lf \n",promedio);
	printf("El error promedio estimado del cálculo es: %lf \n",promerr);
	printf("El tiempo de calculo ha sido %lf s \n",tend-tini);
	
return 0;
}
		
