#include <stdlib.h> 
#include <stdio.h>
#include <math.h>
#include "generador.h"

int main(){
	
	long long ch,chmax;
	
	int N,k;
	int i,j;
	
	double Eprom;
	double Eij;
	
	double Emax, dE;
	double dV;
	
	double nbins = 200;
	int histE[200];
	int histV[200];
	
	double tini,tend;
	
	FILE *salida;
	salida = fopen("distribV.dat","w");
	
	printf("Introduce el numero de moleculas a considerar: \n");
	scanf("%d",&N);
	printf("Introduce la energia cinetica promedio de las moleculas(unidades arbitrarias): \n");
	scanf("%lf",&Eprom);
	printf("Introduce el numero total de choques a simular: \n");
	scanf("%lld",&chmax);
	
	double E[N]; //energia de cada molecula
	
	for(k=0;k<N;k++){
		 E[k] = Eprom;
	}
	
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
	}
	
	//Calculo de la funcion de distribucion
	Emax = 8*Eprom;
	dE = Emax/nbins;
	dV = sqrt(Emax)/nbins;
	
	for(j=0;j<nbins;j++){
		histE[j]=0;
		histV[j]=0;
	}
	
	for(k=0;k<N;k++){
		i = E[k]/dE;
		j = sqrt(E[k])/dV;
		if(i<nbins) histE[i] = histE[i] + 1;
		if(j<nbins) histV[i] = histV[i] + 1;	
	}
	
	tend = timeinseconds();
	
	for(i=0;i<nbins;i++){
		fprintf(salida,"%lf %le %lf %le\n",dE*(i+0.5),1.0/dE*(double)histE[i]/(double)N,dV*(i+0.5),1.0/dV*(double)histV[i]/(double)N);
	}
	
	fclose(salida);
	
	printf("%d moleculas, %lld choques: %lf s de calulo \n",N,chmax,tend-tini);
	
return 0;
}
	
