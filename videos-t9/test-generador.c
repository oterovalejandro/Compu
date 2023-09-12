#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "generador.h"

int main(){
	long long i,N; 
	int x;
	
	printf("Numero de tiradas: \n");
	scanf ("%lld",&N);
	
	long long H[7];
	for (i=1;i<=6;i++){
		H[i] = 0;
	}
	
	srand48(seed());
	
	for (i=0;i<N;i++){
		x = scalerandom(drand48(),1,7);
		//printf("%.15lf \n",x) ;
		H[x]++;
	}
	
	double freq, rms=0.0;
	
	for (i=1;i<=6;i++){
		freq = (double)H[i]/(double)N;
		rms = rms + pow(freq-(1.0/6.0),2);
		printf("Numero %lld Tiradas: %lld Frecuencia: %lf \n",i,H[i],freq);
	}
	 
	 rms = sqrt(rms);
	 printf("Desviacion estadistica: %lf \n",rms);
return 0;
}
		
