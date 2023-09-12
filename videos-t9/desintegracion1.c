#include <stdlib.h> 
#include <stdio.h>
#include <math.h>
#include "generador.h"

int main(){
	
	int i,imax;
	int j;
	
	int N0,Nvivos,Nt;
	double lam;
	
	FILE *salida;
	
	salida = fopen("Nt.dat","w");
	
	printf("Constante de desintegracion: \n");
	scanf("%lf",&lam);
	printf("Numero inicial de nucleos radiactivos: \n");
	scanf("%d",&N0);
	
	fprintf(salida,"%d %d \n",0,N0);
	
	imax = 5/lam;
	Nt = N0;
	
	srand48(seed());
	
	for(i=1;i<=imax;i++){	//bucle temporal
		Nvivos = Nt;
		for(j=1;j<=Nvivos;j++){	//bucle sobre nucleos
			if(drand48()<=lam){		//se desintegra
				Nt=Nt-1;
			}
		}
		fprintf(salida,"%d %d \n",i,Nt);
	}
	
	fclose(salida);
	
return 0;
}
	
