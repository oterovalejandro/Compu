#include <stdlib.h> 
#include <stdio.h>
#include <math.h>
#include "generador.h"

int main(){
	
	long long ch,chmax;
	
	int N,k;
	int NA,NB;
	int i,j;
	
	double TA,TB;
	double Eij;
	
	double tini,tend;
	
	FILE *salida;
	salida = fopen("tempermezcla.dat","w");
	
	printf("Introduce el numero de moleculas de tipo A a considerar: \n");
	scanf("%d",&NA);
	printf("Introduce el numero de moleculas de tipo B a considerar: \n");
	scanf("%d",&NB);
	printf("Introduce la temperatura inicial del gas A: \n");
	scanf("%lf",&TA);
	printf("Introduce la temperatura inicial del gas B: \n");
	scanf("%lf",&TB);
	
	printf("Introduce el numero total de choques a simular: \n");
	scanf("%lld",&chmax);
	
	N = NA + NB;
	
	double E[N]; //energia de cada molecula
	
	for(k=0;k<N;k++) E[k] = 1.5*TA;
	for(k=NA;k<N;k++) E[k] = 1.5*TB;
	
	srand48(seed());
	tini = timeinseconds();
	
	for(ch=1;ch<=chmax;ch++){
		i = scalerandom(drand48(),0,N);
		do{
			j = scalerandom(drand48(),0,N);
		}
		while(j==i);
		Eij = E[i]+E[j];
		E[i] = scalerandom(drand48(),0,Eij);
		E[j] = Eij - E[i];
		TA = 0;
		for(k=0;k<NA;k++) TA = TA + E[k];
		TB = 0;
		for(k=NA;k<N;k++) TB = TB + E[k];
		TA = TA/((double)NA*1.5);
		TB = TB/((double)NB*1.5);
		if(ch%1000==0) fprintf(salida,"%lld %lf %lf \n",ch,TA,TB);
	}
	
	tend = timeinseconds();
	
	printf("%d moleculas, %lld choques: %lf s de calulo \n",N,chmax,tend-tini);
	
return 0;
}
	
