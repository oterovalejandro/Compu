#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "generador.h"

double f(double x){
	return x*(x-1)*(x+1);
}

int main(){
	long long i,N,Ninside; 
	double integral, x, y;
	double tini, tend;
	
	double fmax = f(1.2);
	double fmin = f(-1.2);
	 
	printf("Numero de ensayos: \n");
	scanf ("%lld",&N);
	
	srand48(seed());
	Ninside = 0;
	
	tini = timeinseconds();
	
	for (i=0;i<N;i++){
		x = scalerandom(drand48(),-1.2,1.2);
		y = scalerandom(drand48(),fmin,fmax);
		if(y>0&&y<f(x)) Ninside++;
		if(y<0&&y>f(x)) Ninside++;
	}
	integral = 2.4*(fmax-fmin)*(double)Ninside/(double)N;
	
	tend = timeinseconds();
	
	printf("Valor de integral: %.10lf \n", integral);
	printf("Tiempo de calculo: %lf s \n" , tend - tini);

return 0;
}
		
