#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "generador.h"

int main(){
	long long i,N,Ninside; 
	double pi, x, y;
	double tini, tend;
	
	printf("Numero de ensayos: \n");
	scanf ("%lld",&N);
	
	srand48(seed());
	Ninside = 0;
	
	tini = timeinseconds();
	
	for (i=0;i<N;i++){
		x = scalerandom(drand48(),-1,1);
		y = scalerandom(drand48(),-1,1);
		if(x*x+y*y<1) Ninside++;
		
	}
	pi = 4.0*(double)Ninside/(double)N;
	
	tend = timeinseconds();
	
	printf("Valor de pi: %.10lf \n", pi);
	printf("Tiempo de calculo: %lf s \n" , tend - tini);

return 0;
}
		
